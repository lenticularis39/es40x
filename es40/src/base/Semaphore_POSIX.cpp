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

#include "Semaphore_POSIX.h"
#include <sys/time.h>

CSemaphoreImpl::CSemaphoreImpl(int n, int max)
{
  sem_init(&mutex, 1, n);
}

CSemaphoreImpl::~CSemaphoreImpl()
{
  sem_destroy(&mutex);
}

void CSemaphoreImpl::setImpl()
{
  sem_post(&mutex);
}

void CSemaphoreImpl::waitImpl()
{
  sem_wait(&mutex);
}

bool CSemaphoreImpl::waitImpl(long milliseconds)
{
  struct timespec interval;
  interval.tv_nsec = milliseconds * 1000;
  return sem_timedwait(&mutex, &interval);
}
