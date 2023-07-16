#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "target.h"

extern char cwd[];

#if TARGET == t_rpc8e

extern unsigned char screenID;
extern unsigned char driveA_ID;

#endif

#endif //defined _GLOBALS_H