/*
#  FAT12 functions for the RPOS Kernel
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

#ifndef _FILESYSTEM_FAT_H
#define _FILESYSTEM_FAT_H

typedef struct {
    unsigned long entryPoint : 24;
    char oemID[8]; // non zero terminated string
    unsigned short bytesPerSector;
    unsigned char sectorsPerCluster;
    unsigned short reservedSectors;
    unsigned char fatCopies;
    unsigned short rootEntries;
    unsigned short smallNumberOfSectors;
    unsigned char mediaDescriptor;
    unsigned short sectorsPerFat;
    unsigned short sectorsPerTrack;
    unsigned short numberOfHeads;
    unsigned long hiddenSectors;
    unsigned long largeNumberOfSectors;
    unsigned char driveNumber;
    unsigned char reserved;
    unsigned char extendedBootSignature;
    unsigned long serial;
    char lable[11]; // non zero terminated string
    char type[8]; // non zero terminated string
    unsigned char bootCode[448];
    unsigned short bootSignature;
} fatBootSector;

#endif