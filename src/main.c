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
#include "conio2.h"
#include "string2.h"
#include "disk.h"
#include "asm/asm.h"
#include "filesystem/table.h"
#include "filesystem/fat.h"

#include <stdint.h>
#include <string.h>
#include <memory.h>

char input[128];
char command[64];
char buffer[64];

int main(void) {
    unsigned char i;
    char c;

    tableEntry *mbr = (void *)0x6be;

    fatBootSector *fatBoot = (void *)0xfc00;

    for (i = 0; i < 4; i++) {
        if (mbr[i].systemID == MBR_FAT) goto EARLY_DETECT;
    }

    if (mbr[i].systemID != MBR_FAT) cputs("extensivly checking for filesystem\n");

    for (i = 0; i < 4; i++) {
        if (readSector('a', mbr[i].lbaStart, (unsigned char *)fatBoot) == (unsigned char *)2) continue;
        memcpy(fatBoot->type, buffer, 8);
        buffer[5] = 0;

        if (strcmp(buffer, "FAT  ") == 0) goto FOUND_FS;
    }

EARLY_DETECT:

    readSector('a', mbr[i].lbaStart, (unsigned char *)fatBoot);

FOUND_FS:

    cputs("Detected FAT filesystem at sector ");
    cputs(itoa(mbr[i].lbaStart, buffer, 10));
    cputs(" (mbr entry ");
    cputs(itoa(i, buffer, 10));
    cputs(")\n\r");

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

    goto VERSION;

    while (1) {
        c = cgetc();
        if (c == '\b') strdelc(input), cbkspc(), c = 0; else cputc(c);

        if (c == '\r' || c == '\n') {
            if (c == '\r') cputc('\n');
            gotox(0);

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
                    cputs(itohex(*(unsigned char*)hextoi(strtok(0, " "))));
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
                    ((void (*)(void))0x500)();
                    
                } else if (strcmp(command, "poweroff") == 0) {
                    return 0;

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