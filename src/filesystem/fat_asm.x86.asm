[bits 16]

global getFatEntry

getFatEntry:
    push bp
    mov bp, sp
    mov ax, [bp + 0x2]
    mov si, [bp + 0x2]

    mov cx, ax
    mov dx, ax
    shr dx, 1
    add cx, dx
    mov bx, si
    add bx, cx
    mov dx, [bx]
    test ax, 1
    jnz .odd
.even:
    and dx, 0xfff
    jmp .exit
.odd:
    shr dx, 0x4
.exit:
    pop bp
    ret