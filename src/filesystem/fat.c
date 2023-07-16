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

#include "fat.h"
#include "table.h"
#include "../disk.h"

#include "../conio2.h"
#include <stdlib.h>

tableEntry *partition;
fatDirEntry *dir;
fatBootSector *boot;
unsigned short dataRegion;
unsigned short root;

unsigned short setFatEntry(unsigned short entry, unsigned short value, unsigned char *fatTable);

void initFat(tableEntry *partitionEntry, fatBootSector *fatBoot, fatDirEntry *dirBuffer) {
    partition = partitionEntry;
    boot = fatBoot;
    dir = dirBuffer;
    root = (partitionEntry->lbaStart + fatBoot->reservedSectors) + (fatBoot->fatCopies * fatBoot->sectorsPerFat);
    readSector('a', root, (unsigned char *)dirBuffer);
    dataRegion = root + ((fatBoot->rootEntries * 32) / fatBoot -> bytesPerSector) - 2;
}

unsigned char *fatReadClusterChain(char drive, unsigned short cluster, unsigned char *fatTable, unsigned char *buffer) {
    unsigned short i;

    for (i = 0;; i++) {
        readSector(drive, dataRegion + cluster, buffer + (512 * i));
        cluster = getFatEntry(cluster, fatTable);
        if (cluster >= 0xff8) break;
        
    }
}