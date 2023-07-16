/*
#  MBR functions for the RPOS Kernel
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

#include "table.h"
#include <stdlib.h>

unsigned long chstolba(chs *input) {
    unsigned long ret = 0;
    
    ret = input->sector - 1;
    ret = (unsigned long)input->head << 6;
    ret = (unsigned long)input->cylinder << 14;

    return ret;
}

chs *lbatochs(unsigned long input) {
    chs ret;

    chs max = {0xff, 0x3f, 0x3ff};

    if (input > (1UL << 24) - 1) return &max;

    ret.sector = input & 0x3f + 1;
    ret.head = input & 0x3fc0;
    ret.cylinder = input & 0xffc000;

    return &ret;
}