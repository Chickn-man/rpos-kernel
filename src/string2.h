/*
#  Extra string functions for the RPOS Kernel
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

#ifndef _STRING2_H
#define _STRING2_H

void strcatc(char *ds, char c);
void strdelc(char *str);
unsigned int hextoi(char *str);
char *itohex(unsigned int num);

int atoi(char *str);
char *itoa(int num, char *buffer, int radix);

#if TARGET == t_rpc8e

//char *strupper(char *s);
//char *strlower(char *s);

#endif

#endif 