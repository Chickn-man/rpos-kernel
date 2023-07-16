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

#include "string2.h"
#include <string.h>

void strcatc(char *dst, char c) {
    unsigned short len = strlen(dst);

    dst[len++] = c;
    dst[len] = 0;

}

void strdelc(char *str) {
    unsigned short len = strlen(str);

    if (!len) return;

    str[len - 1] = 0;

}

unsigned int hextoi(char *str) {
    unsigned int val = 0;
    unsigned char i;

    for (i = 0; str[i]; i++) {
        if (str[i] >= '0' && str[i] <= '9') str[i] = str[i] - '0';
        else if (str[i] >= 'a' && str[i] <= 'f') str[i] = str[i] - 'a' + 10;
        val = (val << 4) | (str[i] & 0xf);
    }
    
    return val;
        
}

char *itohex(unsigned int num) {
    unsigned char i = 7;
    unsigned char s = 0;
    unsigned int n = num;
    char buffer[8];

    while (n > 0) {
        buffer[i] = "0123456789abcdef"[n % 16];
        i--;
        n = n / 16;

    }

    while (++i < 8) {
        buffer[s++] = buffer[i];

    }

    buffer[s] = 0;

    return buffer;

}

#if TARGET == t_rpc8e
/*
char *strupper(char *s) {
    unsigned int i;

    for (i = 0; i < strlen(s); i++) {
        s[i] = s[i] + (('a' - 'A') * (s[i] >= 'a' && s[i] <= 'z'));

    }

    return s;

}

char *strlower(char *s) {
    unsigned int i;

    for (i = 0; i < strlen(s); i++) {
        s[i] = s[i] + (('A' - 'a') * (s[i] >= 'A' && s[i] <= 'Z'));

    }

    return s;

}
*/
#endif