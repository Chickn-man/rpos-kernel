#include "memory.h"

#include "target.h"

#if TARGET != t_rpc8e

void memcpy(unsigned char *dst, unsigned char *src, int len) {
    int i;

    for (i = 0; i < len; i++) dst[i] = src[i]; 
}

#endif