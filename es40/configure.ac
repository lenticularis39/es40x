################################################################################
# ES40 emulator.
# Copyright (C) 2007-2008 by the ES40 Emulator Project
#
# Website: http://sourceforge.net/projects/es40
# E-mail : camiel@camicom.com
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 
# 02110-1301, USA.
# 
# Although this is not required, the author would appreciate being notified of, 
# and receiving any modifications you may make to the source code that might serve
# the general public.
#
################################################################################
#
# $Id$
#
# X-1.1	     Camiel Vanderhoeven                      20-MAR-2008
#      File Created.
#
################################################################################
#
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(es40, 0.18, iamcamiel@gmail.com)
AC_CONFIG_SRCDIR([src/Flash.cpp])
AM_CONFIG_HEADER([src/config.h])
AM_INIT_AUTOMAKE(es40, 0.18)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

SDL_VERSION=1.2.0
AM_PATH_SDL($SDL_VERSION,
  CXXFLAGS="$CXXFLAGS $SDL_CFLAGS -DHAVE_SDL"
  LIBS="$LIBS $SDL_LIBS"
  ,:)

AM_PATH_PCAP(
  CXXFLAGS="$CXXFLAGS $PCAP_CFLAGS -DHAVE_PCAP"
  LIBS="$LIBS $PCAP_LIBS"
  ,:)

AM_PATH_X11(
  CXXFLAGS="$CXXFLAGS $X11_CFLAGS -DHAVE_X11"
  LIBS="$LIBS $X11_LIBS"
  ,:)

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h fcntl.h inttypes.h malloc.h netinet/in.h stdint.h stdlib.h string.h sys/param.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_HEADER_TIME
AC_STRUCT_TM
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_CHECK_FUNCS([alarm atexit memset pow select socket sqrt strcasecmp strchr strdup strncasecmp strspn])

AC_OUTPUT(Makefile doc/Makefile m4/Makefile src/Makefile)