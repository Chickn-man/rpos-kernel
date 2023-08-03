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

#include "../target.h"
#include "table.h"

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

} packed fatBootSector;

typedef struct {
    char name[8]; // non zero terminated string
    char extension[3]; // non zero terminated string
    unsigned char attributes;
    unsigned char reserved;
    unsigned char createMilli;
    unsigned short createTime;
    unsigned short createDate;
    unsigned short lastReadData;
    unsigned short reserved1;
    unsigned short writeTime;
    unsigned short writeDate;
    unsigned short cluster;
    unsigned long size;
} packed fatDirEntry;

unsigned short getFatEntry(unsigned short entry, unsigned char *fatTable);
unsigned short setFatEntry(unsigned short entry, unsigned short value, unsigned char *fatTable);
void initFat(tableEntry *partitionEntry, fatBootSector *fatBoot, fatDirEntry *dirBuffer);
unsigned char *fatReadClusterChain(char drive, unsigned short cluster, unsigned char *fatTable, unsigned char *buffer);

#define FAT_ATTR_READ_ONLY 0x1
#define FAT_ATTR_HIDDEN    0x2
#define FAT_ATTR_SYSTEM    0x4
#define FAT_ATTR_LABLE     0x8
#define FAT_ATTR_DIRECTORY 0x16
#define FAT_ATTR_ARCHIVE   0x32

#if TARGET == t_rpc8e

#define FILE_ALLOCATION_TABLE 0xf000
#define FAT_DIRECTORY 0xf400

#elif TARGET == t_x86

#define FILE_ALLOCATION_TABLE 0x6800
#define FAT_DIRECTORY 0x4c00

#endif

#define fileAllocationTable ((unsigned char *)FILE_ALLOCATION_TABLE)
#define fatDirectory ((fatDirEntry *)FAT_DIRECTORY)

#endif // defined _FILESYSTEM_FAT_H