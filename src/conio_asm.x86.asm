;#
;#  x86 real mode conio functions
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

global cputc, cputs, cgetc, clrscr, cputc2

cputc:
    push bp
    mov bp, sp
    mov ax, [bp + 0x4]
    mov ah, 0x0e ; print char and move cursor to the right
    mov bx, 0x07 ; set color to grey on black
    int 10h
    pop bp
    ret

cputs:
    push bp
    mov bp, sp
    mov si, [bp + 0x4]

    xor ax, ax

.loop:
    mov al, [si]
    inc si
    or al, al
    jz .exit

    push ax
    call cputc
    add sp, 0x2

    jmp .loop
.exit:
    pop bp
    ret

cgetc: ; get char from keyboard if no key is pressed it will wait indefinitely
    mov ah, 0
    int 16h
    ret

clrscr:
    push es
    mov ax, 0xb800
    mov es, ax
    xor di, di

    mov cx, 2000

    mov al, ' '
    mov ah, 0b00000111

.loop:
    mov es:[di], ax
    add di, 2
    loop .loop
.exit:
    mov ah, 0x2
    xor dx, dx
    xor bh, bh
    int 10h
    pop es
    ret