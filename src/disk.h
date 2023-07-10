/*
#  Disk access functions for the RPOS Kernel
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

#ifndef _DISK_H
#define _DISK_H

unsigned char* readSector(char letter, unsigned short sector, unsigned char* buffer);
unsigned char* writeSector(char letter, unsigned short sector, unsigned char* buffer);

char* readDiskName(char letter, char* buffer);
char* writeDiskName(char letter, char *name);

char* readDiskSerial(char letter, char* buffer);

#endif