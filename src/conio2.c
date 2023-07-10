/*
#  Conio functions for the RPOS Kernel
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

#include "target.h"

#include "conio2.h"
#include "globals.h"

#if TARGET == t_rpc8e

#include "window.h"
#include "asm/asm.h"
#include <mmu.h>

void blitShift(unsigned char sx, unsigned char sy, unsigned char dx, unsigned char dy, unsigned char w, unsigned char h) {
    setMappedRedbusDev(screenID);

    blitX = sx;
    blitY = sy;

    blitXOffset = dx;
    blitYOffset = dy;

    blitWidth = w;
    blitHeight = h;

    blitMode = BLIT_SHIFT;
    
    while (blitMode == BLIT_SHIFT) {
        wait(); 
    }
}

void blitFill(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char character) {
    setMappedRedbusDev(screenID);

    blitChar = character;

    blitXOffset = x;
    blitYOffset = y;

    blitWidth = w;
    blitHeight = h;

    blitMode = BLIT_FILL;
    
    while (blitMode == BLIT_FILL) {
        wait(); 
    }
}

void clrscr(void) {
    blitFill(0, 0, 80, 50, ' ');
    gotoxy(0, 0);
}

void gotoxy(unsigned char x, unsigned char y) {
    setMappedRedbusDev(screenID);

    cursorX = x;
    cursorY = y;
}
void gotox(unsigned char x) {
    setMappedRedbusDev(screenID);

    cursorX = x;
}
void gotoy(unsigned char y) {
    setMappedRedbusDev(screenID);

    cursorY = y;
}

unsigned char wherex(void) {
    setMappedRedbusDev(screenID);

    return cursorX;
}
unsigned char wherey(void) {
    setMappedRedbusDev(screenID);

    return cursorY;
}

/* puts a character c at the cursor position */
void cputc(char c) {
    setMappedRedbusDev(screenID);

    screenRow = cursorY;

    if (c != '\n' && c != '\r') screenBuffer[cursorX] = c;

    cursorX = cursorX + 1;

    if (c == '\n') if (cursorY >= 49) {
        /* scroll terminal */
        blitShift(0, 1, 0, 0, 80, 49);

        blitFill(0, 49, 80, 1, ' ');
    } else cursorY = cursorY + 1;

    if (c == '\r') cursorX = 0;

    if (cursorX > 79) {
        cursorX = 0;

        if (cursorY >= 49) {
            /* scroll terminal */
            blitShift(0, 1, 0, 0, 80, 49);

            blitFill(0, 49, 80, 1, ' ');
        } else {
            cursorY = cursorY + 1;
        }
    }
}

/* gets a character from the keyboard */
// waits if no charater is available
// i have no clue how this works
char cgetc(void) {
    char key;

    setMappedRedbusDev(screenID);

    cursorMode = CURSOR_BLINK;
    
    while (!(keyBuffer != keyPosition)) wait();

    key = keyStart;

    keyBuffer = keyBuffer + 1;
    if (keyBuffer > 0x10) keyBuffer = 0;

    cursorMode = CURSOR_HIDDEN;
    return key;
}

#endif

/* puts a character c at the cursor position ignoring \n and \r */
void cputc2(char c) {
    if (c == '\n' || c == '\r') return;

    cputc(c);
   
}

void cputs(char *s) {
    while (*s != 0) {
        cputc(*s++);
    }
}

void cbkspc(void) {
    if (wherex() == 0 && wherey() == 0) return;

    gotox(wherex() - 1);
    if (wherex() == 255) gotoxy(79, wherey() - 1);

    cputc(' ');
    gotox(wherex() - 1);
}

void cdelc(void) {
    cputc(' ');

    gotox(wherex() - 1);
}