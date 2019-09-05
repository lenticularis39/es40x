/* ES40x Alpha machine emulator.
 * Copyright (C) 2007-2008 by the ES40 Emulator Project
 * Copyright (C) 2019 Tomas Glozar
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 * Although this is not required, the author would appreciate being notified of, 
 * and receiving any modifications you may make to the source code that might
 * serve the general public.
 */

#include "StdAfx.h"
#include "System.h"
#include "Error.h"
#include "Flash.h"
#include "DPR.h"

#include "lockstep.h"

#if defined(HAVE_SDL)
#include "SDL.h"
#endif

/// "standard" locations for a configuration file.  This will be port specific.
const char* path[] ={
#if defined(_WIN32)
  ".\\es40.cfg",
  "c:\\es40.cfg",
  "c:\\windows\\es40.cfg",
#elif defined(__VMS)
  "[]ES40.CFG",
#else
  "./es40.cfg",
  "/etc/es40.cfg",
  "/usr/etc/es40.cfg",
  "/usr/local/etc/es40.cfg",
#endif
  0
};

#ifdef DEBUG_BACKTRACE
#ifdef __GNUG__
#include <execinfo.h>
#include <signal.h>
#define HAS_BACKTRACE

#define BTCOUNT 100
void*   btbuffer[BTCOUNT];

void segv_handler(int signum)
{
  int     nptrs = backtrace(btbuffer, BTCOUNT);
  char **  strings;

  printf("%%SYS-F-SEGFAULT: The Alpha Simulator has Segfaulted.\n");
  printf("-SYS-F-SEGFAULT: Backtrace follows.\n");

  printf("backtrace() returned %d addresses.\n", nptrs);
  strings = backtrace_symbols(btbuffer, nptrs);
  if(strings == NULL)
  {
    perror("backtrace_symbols");
    exit(1);
  }

  for(int i = 0; i < nptrs; i++)
  {
    printf("%3d %s\n", nptrs - i, strings[i]);
  }

  free(strings);
  if(signum == SIGSEGV)
    _exit(1);
}

#else
#warning "Your compiler isn't configured to support backtraces."
#endif // __GNUG__
#endif

/**
 * Entry point for the application.
 *
 * Does the following:
 *  - Try to find the configuration file.
 *  - Reads the configuration file, and uses the configurator to instantiate all
 *    system components.
 *  - Creates the trace-engine if in debug mode.
 *  - Runs the emulator.
 *  - Cleans up.
 *  .
 **/
int main (int argc, char*argv[])
{
  const char *confFileName;
  FILE *confFile;

#ifdef HAS_BACKTRACE
  signal(SIGSEGV, &segv_handler);
  signal(SIGUSR1, &segv_handler);
#endif
  try
  {
#if defined(IDB) && (defined(LS_MASTER) || defined(LS_SLAVE))
    lockstep_init();
#endif
#if defined(IDB)
    if((argc == 2 || argc == 3) && argv[1][0] != '@')
#else
      if (argc == 2)
#endif
      {
        confFileName = argv[1];
      }
      else
      {
        for (int i = 0; path[i]; i++)
        {
          confFileName = path[i];
          confFile = fopen(path[i], "r");

          if (confFile)
          {
            fclose(confFile);
            confFileName = path[i];
            break;
          }
        }
        if (!confFileName)
          FAILURE(FileNotFound, "configuration file");
      }

    char *confFileBuffer;
    size_t confFileLength;

    // Open configuration file end measure its length.
    confFile = fopen(confFileName, "rb");
    if (!confFile)
      FatalError("cannot open configuration file");

    fseek(confFile, 0, SEEK_END);
    confFileLength = ftell(confFile);
    fseek(confFile, 0, SEEK_SET);

    // Load file contents into buffer and load the buffer into the configurator
    // object.
    confFileBuffer = (char *) calloc(confFileLength, 1);
    confFileLength = fread(confFileBuffer, 1, confFileLength, confFile);
    CConfigurator *Config = new CConfigurator(0, 0, 0, confFileBuffer,
                                              confFileLength);
    fclose(confFile);
    free(confFileBuffer);

    if(!theSystem)
      FAILURE(Configuration, "no system initialized");

#if defined(IDB)
    trc = new CTraceEngine(theSystem);
#endif
    theSystem->LoadROM();
    theDPR->init();

#if defined(PROFILE)
    {
      u64 p_i;
      for(p_i = PROFILE_FROM; p_i < PROFILE_TO; p_i += (4 * PROFILE_BUCKSIZE))
        PROFILE_BUCKET(p_i) = 0;
      profiled_insts = 0;
    }
#endif
#if defined(IDB)
    if(argc > 1 && argc < 4 && argv[argc - 1][0] == '@')
      trc->run_script(argv[argc - 1] + 1);
    else
      trc->run_script(NULL);
#else
    theSystem->Run();
#endif
  }
  catch(CGracefulException & e)
  {
    printf("Exiting gracefully: %s\n", e.displayText().c_str());

    theSystem->stop_threads();

    // save flash and dpr rom only if not terminated with a fatal error
    theSROM->SaveStateF();
    theDPR->SaveStateF();

#if defined(PROFILE)
    {
      FILE*   p_fp;
      u64     p_max = 0;
      u64     p_i;
      int     p_j;

      printf("Writing profile to profile.txt");

      p_fp = fopen("profile.txt", "w");
      for(p_i = PROFILE_FROM; p_i < PROFILE_TO; p_i += (4 * PROFILE_BUCKSIZE))
      {
        if(PROFILE_BUCKET(p_i) > p_max)
          p_max = PROFILE_BUCKET(p_i);
      }
      fprintf
        (
          p_fp, "p_max = %10"LL "d; %10"LL "d profiled instructions.\n\n", p_max,
            profiled_insts
        );
      for(p_i = PROFILE_FROM; p_i < PROFILE_TO; p_i += (4 * PROFILE_BUCKSIZE))
      {
        if(PROFILE_BUCKET(p_i))
        {
          fprintf(p_fp, "%016"LL "x: %10"LL "d ", p_i, PROFILE_BUCKET(p_i));
          for(p_j = 0; p_j < (((float) PROFILE_BUCKET(p_i) / (float) p_max) * 100);
              p_j++)
            fprintf(p_fp, "*");
          fprintf(p_fp, "\n");
        }
      }
      fclose(p_fp);
    }
#endif
    delete theSystem;
  }
  catch(CException & e)
  {
    printf("Emulator Failure: %s\n", e.displayText().c_str());
    if(theSystem)
    {
      theSystem->stop_threads();
      delete theSystem;
    }
  }
  return 0;
}
