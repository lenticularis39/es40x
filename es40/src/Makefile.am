# ES40x Alpha machine emulator.
# Copyright (C) 2007-2008 by the ES40 Emulator Project
# Copyright (C) 2019 Tomas Glozar
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
# and receiving any modifications you may make to the source code that might
# serve the general public.

AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = es40x es40x-idb es40x-lss es40x-lsm es40x-config

es40x_SOURCES = AliM1543C.cpp \
       AliM1543C_ide.cpp \
       AliM1543C_usb.cpp \
       AlphaCPU.cpp \
       AlphaCPU_ieeefloat.cpp \
       AlphaCPU_vaxfloat.cpp \
       AlphaCPU_vmspal.cpp \
       AlphaSim.cpp \
       Cirrus.cpp \
       Configurator.cpp \
       DEC21143.cpp \
       Disk.cpp \
       DiskController.cpp \
       DiskDevice.cpp \
       DiskFile.cpp \
       DiskRam.cpp \
       DMA.cpp \
       DPR.cpp \
       es40_debug.cpp \
       Ethernet.cpp \
       Error.cpp \
       Flash.cpp \
       FloppyController.cpp \
       Keyboard.cpp \
       lockstep.cpp \
       PCIDevice.cpp \
       Port80.cpp \
       S3Trio64.cpp \
       SCSIBus.cpp \
       SCSIDevice.cpp \
       Serial.cpp \
       StdAfx.cpp \
       Sym53C810.cpp \
       Sym53C895.cpp \
       SystemComponent.cpp \
       System.cpp \
       TraceEngine.cpp \
       VGA.cpp \
       gui/gui.cpp \
       gui/gui_x11.cpp \
       gui/keymap.cpp \
       gui/scancodes.cpp \
       gui/sdl.cpp \
       base/Bugcheck.cpp \
	base/ErrorHandler.cpp \
	base/Event.cpp \
	base/Exception.cpp \
	base/Mutex.cpp \
	base/NumberFormatter.cpp \
	base/RefCountedObject.cpp \
	base/Runnable.cpp \
	base/RWLock.cpp \
	base/Semaphore.cpp \
	base/SignalHandler.cpp \
	base/ThreadLocal.cpp \
	base/Thread.cpp \
	base/Timestamp.cpp

es40x_idb_SOURCES = $(es40x_SOURCES)
es40x_lss_SOURCES = $(es40x_SOURCES)
es40x_lsm_SOURCES = $(es40x_SOURCES)

es40x_idb_CXXFLAGS = -DIDB
es40x_lss_CXXFLAGS = -DIDB -DLSS
es40x_lsm_CXXFLAGS = -DIDB -DLSM

es40x_config_SOURCES = es40-cfg.cpp \
    base/Exception.cpp

