/*
#  MMU opcode wrappers for cc65
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

#ifndef _MMU_H
#define _MMU_H

void __fastcall__ setMappedRedbusDev(unsigned char device);
unsigned char __fastcall__ getMappedRedbusDev();
void __fastcall__ setRedbusWindowOffset(unsigned short offset);
unsigned short getRedbusWindowOffset(void);
void enableRedbus(void);
void disableRedbus(void);
void __fastcall__ setMemoryMappedWindow(unsigned short offset);
unsigned short getMemoryMappedWindow(void);
void __fastcall__ setBrkAddress(void (*fcnAddr)(void));
void (*getBrkAddress(void))(void);
void __fastcall__ setPorAddress(void (*fcnAddr)(void));
void (*getPorAddress(void))(void);
void _logRegisterA(void);

#endif