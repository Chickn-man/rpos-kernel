#ifndef _API_API_H
#define _API_API_H

#include "../target.h"

typedef struct packed {
    unsigned short screenWidth;
    unsigned short screemHeight;
    unsigned char screenAttributes;
    void (*blitShift)(unsigned char sx, unsigned char sy, unsigned char dx, unsigned char dy, unsigned char w, unsigned char h);
    void (*blitFill)(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char character);
    void (*clrscr)(void);
    void (*gotoxy)(unsigned char x, unsigned char y);
    void (*gotox)(unsigned char x);
    void (*gotoy)(unsigned char y);
    unsigned char (*wherex)(void);
    unsigned char (*wherey)(void);
    void (*cputc)(char c);
    void (*cputs)(char *s);
    char (*cgetc)(void);
    void (*cputc2)(char c);
    void (*cbkspc)(void);
    void (*cdelc)(void);
    int (*fload)(char *name, unsigned char *addr);
    unsigned short (*fstat)(char *name);
} API;

#define SCREEN_BLIT_SUPPORTED 0x1


extern API api;

void initApi(void); // why

#endif