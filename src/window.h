/*
#  Redbus window pointers for the RPOS Kernel on the RPC8e
#
##############################################################################
#
#  Copyright (C) 2023 Keegan Powers
#
#  This file is part of the RPOS Kernel
#
#  The RPOS Kernel is free software: you can redistribute it
#  and/or modify it under the terms of the GNU General Public
#  License as published by the Free Software Foundation, either
#  version 3 of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see <https://www.gnu.org/licenses/>.
#
#############################################################################
*/

#ifndef _WINDOW_H
#define _WINDOW_H

#include "target.h"

#if TARGET == t_rpc8e

/* pointers */

#define WINDOW 0xff00
#define SCREEN_ROW WINDOW + 0x0
#define CURSOR_X WINDOW + 0x1
#define CURSOR_Y WINDOW + 0x2
#define CURSOR_MODE WINDOW + 0x3
#define KEY_BUFFER WINDOW + 0x4
#define KEY_POSITION WINDOW + 0x5
#define KEY_START WINDOW + 0x6
#define BLIT_MODE WINDOW + 0x7
#define BLIT_X WINDOW + 0x8
#define BLIT_Y WINDOW + 0x9
#define BLIT_X_OFFSET WINDOW + 0xa
#define BLIT_Y_OFFSET WINDOW + 0xb
#define BLIT_WIDTH WINDOW + 0xc
#define BLIT_HEIGHT WINDOW + 0xd
#define SCREEN_BUFFER WINDOW + 0x10

#define IO_BUFFER WINDOW + 0x0
#define IO_LATCH WINDOW + 0x2

#define DISK_BUFFER WINDOW + 0x0
#define DISK_SECTOR 0xff80 // this is supposed to defined as "WINDOW + 0x80" but that doesn't work for some reason, it compiles to 0x0000, it's prolly a bug with cc65.
#define DISK_COMMAND WINDOW + 0x82

/* variable macros */

#define screenRow *((unsigned char *)SCREEN_ROW)
#define cursorX *((unsigned char *)CURSOR_X)
#define cursorY *((unsigned char *)CURSOR_Y)
#define cursorMode *((unsigned char *)CURSOR_MODE)
#define keyBuffer *((unsigned char *)KEY_BUFFER)
#define keyPosition *((unsigned char *)KEY_POSITION)
#define keyStart *((unsigned char *)KEY_START)
#define blitMode *((unsigned char *)BLIT_MODE)
#define blitChar *((unsigned char *)BLIT_X)
#define blitX *((unsigned char *)BLIT_X)
#define blitY *((unsigned char *)BLIT_Y)
#define blitXOffset *((unsigned char *)BLIT_X_OFFSET)
#define blitYOffset *((unsigned char *)BLIT_Y_OFFSET)
#define blitWidth *((unsigned char *)BLIT_WIDTH)
#define blitHeight *((unsigned char *)BLIT_HEIGHT)
#define screenBuffer ((unsigned char *)SCREEN_BUFFER)

#define ioExpanderBuffer *((unsigned short *)IO_BUFFER)
#define ioExpanderLatch *((unsigned short *)IO_LATCH)

#define diskBuffer ((unsigned char *)DISK_BUFFER)
#define diskSector *((unsigned short *)DISK_SECTOR)
#define diskCommand *((unsigned char *)DISK_COMMAND)

/* command defines */

#define CURSOR_HIDDEN 0
#define CURSOR_SOLID 1
#define CURSOR_BLINK 2

#define BLIT_IDLE 0
#define BLIT_FILL 1
#define BLIT_INVERT 2
#define BLIT_SHIFT 3

#define DISK_IDLE 0
#define DISK_READ_NAME 1
#define DISK_WRITE_NAME 2
#define DISK_READ_SERIAL 3
#define DISK_READ 4
#define DISK_WRITE 5
#define DISK_FAILURE 0xff

#endif // TARGET == t_rpc8e
#endif // defined _WINDOW_H