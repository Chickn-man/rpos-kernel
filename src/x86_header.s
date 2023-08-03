[bits 16]

global start, reboot

extern bootDisk, main

    db 0xfd, "RPOS"

start:
    mov [bootDisk], bl
    call main
    ret      

reboot:
    jmp 0xffff:0000