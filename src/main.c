/*
#  main.c
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

#include "globals.h"
#include "window.h"
#include "conio.h"
#include "string.h"
#include "memory.h"
#include "disk.h"
#include "asm/asm.h"
#include "filesystem/table.h"
#include "filesystem/fat.h"
#include "api/api.h"

char input[128];
char command[64];
char buffer[64];
char buffer1[64];
char buffer2[64];
unsigned char mbrEntry;

unsigned char bootDisk;

extern void reboot(void);

int main(void) {
    unsigned short i;
    unsigned short j;
    char c;

#if TARGET == t_rpc8e
    tableEntry *mbr = (void *)0x6be;

    fatBootSector *fatBoot = (void *)0xfc00;

    bootDisk = 80;
#elif TARGET == t_x86
    tableEntry fakembr = {
        MBR_BOOTABLE,
        0,
        1,
        0,
        MBR_FAT,
        1,
        18,
        80,
        0,
        2880,
    };

    i = 0;

    tableEntry *mbr = &fakembr;

    fatBootSector *fatBoot = (void *)0x7c00;

    if (bootDisk < 80) goto FOUND_FS;

    mbr = (void *)0x7c00 + 0x1be;

    fatBoot = (void *)0x4a00;
#endif
 
    for (i = 0; i < 4; i++) {
        if (mbr[i].systemID == MBR_FAT) goto EARLY_DETECT;
    }

    if (mbr[i].systemID != MBR_FAT) cputs("extensivly checking for filesystem\n");

    for (i = 0; i < 4; i++) {
        if (readSector('a', mbr[i].lbaStart, (unsigned char *)fatBoot) == (unsigned char *)2) continue; // load the fat boot sector, if a disk error occured then continue to the next entry
        memcpy(fatBoot->type, buffer, 8);
        buffer[5] = 0;

        if (strcmp(buffer, "FAT  ") == 0) goto FOUND_FS;
    }

EARLY_DETECT:

    readSector('a', mbr[i].lbaStart, (unsigned char *)fatBoot); // load the fat boot sector

FOUND_FS:

    cputs("Detected FAT filesystem at sector ");
    cputs(itoa(mbr[i].lbaStart, buffer, 10));
    cputs(" (mbr entry ");
    cputs(itoa(i, buffer, 10));
    cputs(")\n\r");

    mbrEntry = i;

    /*if (mbr[i].lbaStart != chstolba((chs *)&mbr[i].startHead)) { // this does nothing and I dont feel like fixing it
        cputs("CHS doesnt match LBA - correct this? Y/n");
        if (cgetc() == 'y') {
            *((chs *)&mbr[i].startHead) = *lbatochs(mbr[i].lbaStart);
            *((chs *)&mbr[i].endHead) = *lbatochs(mbr[i].lbaEnd);
            writeSector('a', 0, (unsigned char*)0x500);
        } else return 1;

        cputc('\n');
        cputc('\r');
    }*/

    for (i = 0; i < fatBoot->sectorsPerFat; i++) {
        readSector('a', (mbr[mbrEntry].lbaStart + fatBoot->reservedSectors) + i, (unsigned char *)((unsigned short)fileAllocationTable + (512 * i))); // wizardry : loads the fat into ram
    }

    initFat(&mbr[mbrEntry], fatBoot, fatDirectory);
    strcpy(cwd, "/");

    //initApi();

    goto VERSION; // prints version on startup

    while (1) {
        c = cgetc();
        if (c == '\b') strdelc(input), cputs("\b \b"), c = 0; else cputc(c);

        if (c == '\r' || c == '\n') {
            if (c == '\r') cputc('\n');
            cputc('\r');

            if (strlen(input) != 0) {
                strcpy(command, strtok(input, " "));
ANDAND:
                if (strcmp(command, "cls") == 0) {
                    clrscr();

                } else if (strcmp(command, "ascii") == 0) {
                    for (i = 0; i < 255; i++) cputc2(i);
                    cputc('\n');
                    cputc('\r');

                } else if (strcmp(command, "version") == 0) {
VERSION:            cputs("RedPower Operating System ");
                    cputs(itoa(VERSION_REL, buffer, 10));
                    cputc('.');
                    cputs(itoa(VERSION_MAJ, buffer, 10));
                    cputc('.');
                    cputs(itoa(VERSION_MIN, buffer, 10));
                    cputc('.');
                    cputs(itoa(VERSION_FIX, buffer, 10));
                    cputc('\n');
                    cputc('\r');

                } else if (strcmp(command, "ver") == 0) {
                    goto VERSION;

                } else if (strcmp(command, "peek") == 0) {
                    // grab address from input, read value at addr and print value in hex
                    cputs(itoa(*(unsigned char*)hextoi(strtok(0, " ")), buffer, 16));
                    cputc('\n');
                    cputc('\r');

                } else if (strcmp(command, "poke") == 0) {
                    // grab address from input, grab hex value from input, and write value to address
                    *(unsigned char *)hextoi(strtok(0, " ")) = (unsigned char)hextoi(strtok(0, " "));

                } else if (strcmp(command, "jump") == 0) {
                    // grab address from input, jump to address (jsr)
                    void (*jump)(void) = (void (*)(void))(hextoi(strtok(0, " ")));
                    (*jump)();

                } else if (strcmp(command, "reboot") == 0) {
#if TARGET == t_rpc8e
                    ((void (*)(void))0x500)();
#elif TARGET == t_x86
                    reboot();
#endif        
                } else if (strcmp(command, "poweroff") == 0) {
                    return 0;

                } else if (strcmp(command, "pwd") == 0) {
                    cputs(cwd);
                    cputs("\n\r");

                } else if (strcmp(command, "dir") == 0) {
                    cputs("Contents of ");
                    cputs(cwd);
                    cputs("\n\n\r");
                    cputs("  NAME   | EXT | ATTR | SIZE\n\r");
                    for (i = 0; i < 10; i++) {
                        if (*(fatDirectory[i].name) == '\0') continue;
                        if (fatDirectory[i].attributes & FAT_ATTR_HIDDEN) continue;
                        if (fatDirectory[i].attributes & FAT_ATTR_LABLE) continue;

                        memcpy(buffer, fatDirectory[i].name, 8);
                        buffer[8] = 0;
                        strlwr(buffer);
                        cputs(buffer);
                        cputs(" | ");
                        memcpy(buffer, fatDirectory[i].extension, 3);
                        buffer[3] = 0;
                        strlwr(buffer);
                        cputs(buffer);
                         
                        cputs(" | ");
                        if (fatDirectory[i].attributes & FAT_ATTR_READ_ONLY) cputc('r'); else cputc('-');
                        if (fatDirectory[i].attributes & FAT_ATTR_SYSTEM) cputc('s'); else cputc('-');
                        if (fatDirectory[i].attributes & FAT_ATTR_DIRECTORY) cputc('d'); else cputc('-');
                        if (fatDirectory[i].attributes & FAT_ATTR_ARCHIVE) cputc('a'); else cputc('-');
                        cputs(" | ");
                        cputs(itoa(fatDirectory[i].size, buffer, 10));
                        cputs("\n\r");
                    }

                } else if (strcmp(command, "cd") == 0) {
                    strcpy(buffer, strtok(0, " "));
                    strcpy(buffer2, buffer);
                    strlwr(buffer2);
                    strupr(buffer);
                    for (i = strlen(buffer); i < 11; i++) buffer[i] = ' ';

                    for (i = 0; i < 16; i++) {
                        if (*buffer != *(fatDirectory[i].name)) continue; // skip entry if first characters do not match
                        if (!(fatDirectory[i].attributes & FAT_ATTR_DIRECTORY)) continue;

                        memcpy(buffer1, fatDirectory[i].name, 11);
                        buffer1[11] = 0; // zero terminate
                        if (strcmp(buffer1, buffer) == 0) {
                            if (fatDirectory[i].cluster) {
                                fatReadClusterChain('a', fatDirectory[i].cluster, fileAllocationTable, (unsigned char *)fatDirectory);
                                strcat(cwd, buffer2);
                                strcatc(cwd, '/');
                                i = 17;
                                break;
                            }
                            readSector('a', (mbr[mbrEntry].lbaStart + fatBoot->reservedSectors) + (fatBoot->fatCopies * fatBoot->sectorsPerFat), (unsigned char *)fatDirectory);
                            strcpy(cwd, "/");
                            i = 17;
                            break;
                        }
                    }

                    if (i != 17) cputs("No such directory\n\r");

                } else if (strcmp(command, "type") == 0) {
                    strcpy(buffer, strtok(0, " "));
                    
                    for (i = 0; buffer[i] != '.' && i < 9; i++);
                    buffer[i] = 0;

                    strcpy(buffer1, buffer);
                    strupr(buffer1);
                    for (i = strlen(buffer1); i < 8; i++) buffer1[i] = ' ';

                    strcpy(buffer2, buffer + strlen(buffer) + 1);
                    strupr(buffer2);
                    for (i = strlen(buffer2); i < 3; i++) buffer2[i] = ' ';

                    strcpy(buffer, buffer1);
                    strcat(buffer, buffer2);
                    buffer[11] = 0;
                    
                    for (i = 0; i < 16; i++) {
                        if (*buffer != *(fatDirectory[i].name)) continue; // skip entry if first characters do not match
                        if (fatDirectory[i].attributes & FAT_ATTR_DIRECTORY) continue;
                        if (fatDirectory[i].attributes & FAT_ATTR_LABLE) continue;

                        memcpy(buffer1, fatDirectory[i].name, 11);
                        buffer1[11] = 0; // zero terminate

                        if (strcmp(buffer, buffer1) == 0) {
                            fatReadClusterChain('a', fatDirectory[i].cluster, fileAllocationTable, (unsigned char *)0x8000);

                            for (j = 0; j < fatDirectory[i].size; j++) {
                                if (((unsigned char *)0x8000)[j] == '\n') cputs("\n\r");
                                else cputc(((unsigned char *)0x8000)[j]);
                            }

                            i = 17;
                            break;
                        }
                    }

                    if (i != 17) cputs("File not found\n\r");

                } else if (strcmp(command, "load") == 0) {
                    strcpy(buffer, strtok(0, " "));
                    
                    for (i = 0; buffer[i] != '.' && i < 9; i++);
                    buffer[i] = 0;

                    strcpy(buffer1, buffer);
                    strupr(buffer1);
                    for (i = strlen(buffer1); i < 8; i++) buffer1[i] = ' ';

                    strcpy(buffer2, buffer + strlen(buffer) + 1);
                    strupr(buffer2);
                    for (i = strlen(buffer2); i < 3; i++) buffer2[i] = ' ';

                    strcpy(buffer, buffer1);
                    strcat(buffer, buffer2);
                    buffer[11] = 0;

                    strcpy(buffer2, strtok(0, " "));
                    if (*buffer2 == *((unsigned char *)0)) {
                        cputs("No address specified\n\r");
                        i = 17;
                    } else // this else is for the loop
                    
                    for (i = 0; i < 16; i++) {
                        if (*buffer != *(fatDirectory[i].name)) continue; // skip entry if first characters do not match
                        if (fatDirectory[i].attributes & FAT_ATTR_DIRECTORY) continue;
                        if (fatDirectory[i].attributes & FAT_ATTR_LABLE) continue;

                        memcpy(buffer1, fatDirectory[i].name, 11);
                        buffer1[11] = 0; // zero terminate

                        if (strcmp(buffer, buffer1) == 0) {
                            fatReadClusterChain('a', fatDirectory[i].cluster, fileAllocationTable, (unsigned char *)hextoi(buffer2));
                            i = 17;
                            break;
                        }
                    }

                    if (i != 17) cputs("File not found\n\r");
                
                } else {
                    cputs("command not found\n\r");

                }
                
                if (strcmp(strtok(0, " "), "&&") == 0) {strcpy(command, strtok(0, " ")); goto ANDAND;}

            }
            for (i = 0; i < 128; i++) input[i] = 0;
            for (i = 0; i < 64; i++) command[i] = 0;

            cputc('>');

        } else strcatc(input, c);

    }
    
    return 0;

}