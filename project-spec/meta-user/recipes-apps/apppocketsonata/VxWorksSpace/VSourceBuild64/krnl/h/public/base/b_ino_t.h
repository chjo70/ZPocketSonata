/* b_ino_t.h - base type ino_t definition header */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01c,10may06,pcm  undid changes from version 01b
01b,05may06,pcm  added ino32_t for backward compatibilty and made ino_t 64 bits
01a,16feb06,pes  Created.
*/

#ifndef __INCb_ino_th
#define __INCb_ino_th

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_ino_t
#define _DEFINED_ino_t
/* POSIX requires ino_t to be an unsigned int type. */
typedef unsigned long   ino_t;
#endif /* _DEFINED_ino_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_ino_th */


