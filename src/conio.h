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

#ifndef _CONIO2_H
#define _CONIO2_H

void blitShift(unsigned char sx, unsigned char sy, unsigned char dx, unsigned char dy, unsigned char w, unsigned char h);
void blitFill(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char character);

void clrscr(void);
void gotoxy(unsigned char x, unsigned char y);
void gotox(unsigned char x);
void gotoy(unsigned char y);

unsigned char wherex(void);
unsigned char wherey(void);

void cputc(char c);
void cputs(char *s);
char cgetc(void);

void cputc2(char c);
void cdelc(void);

#endif // !defined _CONIO2_H