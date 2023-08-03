OUTPUT_FORMAT(binary)
ENTRY(start)
SECTIONS {
    .text 0x8000 : AT(0x8000) {
        code = .;
        *(.text)
    }
    .data : AT(0x8000 + (data - code)) {
        data = .;
        *(.data)
    }
    .rodata : AT(0x8000 + (rodata - code)) {
        rodata = .;
        *(.rodata)
    }
    .bss : AT(0x8000 + (bss - code)) {
        bss = .;
        *(COMMON)
        *(.bss)
    }
    end = .;
}
