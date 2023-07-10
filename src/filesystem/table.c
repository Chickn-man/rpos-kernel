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
    if (input->head >= 255 || input->sector >= 63) return 1UL << 24; // return 2^24 (an impossible chs value)
    
    return (255 * 63 * input->cylinder) + (255 * input->head) + input->sector - 1;
}

chs *lbatochs(unsigned long input) {
    chs ret;

    ret.cylinder = (unsigned short)(input / (255 * 63));
    ret.head = (unsigned char)((ret.cylinder * (255 * 63)) / 63);
    ret.sector = ret.cylinder * (255 * 63) - ret.head * 63 + 1;

    return &ret;
}