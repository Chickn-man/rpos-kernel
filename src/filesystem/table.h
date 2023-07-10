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

#ifndef _FILESYSTEM_TABLE_H
#define _FILESYSTEM_TABLE_H

typedef struct {
    unsigned char boot;
    unsigned char startHead;
    unsigned char startSector : 6;
    unsigned short startCylinder : 10;
    unsigned char systemID;
    unsigned char endHead;
    unsigned char endSector : 6;
    unsigned short endCylinder : 10;
    unsigned long lbaStart;
    unsigned long lbaEnd;
} tableEntry;

#define MBR_NOT_BOOTABLE 0x0
#define MBR_BOOTABLE 0x80

// System id values valid in rpos

#define MBR_FAT 0x01 // not implemented
#define MBR_FAT_16_SMALL 0x04 // not implemented
#define MBR_FAT_16_BIG 0x06 // not implemented
#define MBR_FAT_32 0x0b // not implemented
#define MBR_FAT_32_LBA 0x0c // not implementedbg
#define MBR_FAT_16_LBA 0x0e // not implemented

typedef struct {
    unsigned char head;
    unsigned char sector : 6;
    unsigned short cylinder : 10;
} chs;

unsigned long chstolba(chs *input);
chs *lbatochs(unsigned long input);

#endif