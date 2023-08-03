;#
;#  x86 real mode disk driver
;#
;##############################################################################
;#
;#  Copyright (C) 2023 Keegan Powers
;#
;#  This file is part of the RPOS Kernel
;#
;#  The RPOS Kernel is free software: you can redistribute it
;#  and/or modify it under the terms of the GNU General Public
;#  License as published by the Free Software Foundation, either
;#  version 3 of the License, or (at your option) any later version.
;#
;#  This program is distributed in the hope that it will be useful,
;#  but WITHOUT ANY WARRANTY without even the implied warranty of
;#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
;#  GNU General Public License for more details.
;#
;#  You should have received a copy of the GNU General Public License
;#  along with this program. If not, see <https://www.gnu.org/licenses/>.
;#
;#############################################################################

[bits 16]

global readSector

readSector:
    push bp
    mov bp, sp
    mov ax, [bp + 0x4]
    mov bx, [bp + 0x6]
    mov cx, 1

    mov di, 5
.loop:
    push bx
    push cx
    call lba_to_chs
    pop ax
    pop bx
    mov ah, 2 ; read sectors
    mov dl, 0
    int 13h
    jnc .exit
    dec di
    jz .error
    jmp .loop
.error:
    mov ax, 2
    pop bp
    ret
.exit:
    pop bp
    mov bx, [bp + 0x6]
    ret

; convert lba AX to chs CH,DH,CL
lba_to_chs:
    push ax ; save for later
    xor dx, dx
    mov bx, 18
    div bx
    inc dl
    push dx ; sectors

    xor dx, dx
    mov bx, 2
    div bx
    push dx ; heads

    mov ax, 2
    mov bx, 18
    mul bx
    xchg bx, ax

    pop dx ; pops heads
    pop cx ; pops sectors

    pop ax ; initial lba value

    ; push heads and sectors back on to the stack
    push cx
    push dx

    xor dx, dx
    div bx

    pop dx ; pop heads
    mov dh, dl
    pop cx ; pop sectors

    xchg al, ch ; move cylinders to ch

    ret