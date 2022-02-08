/* b_mode_t.h - base type mode_t definition header */

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
01a,16feb06,pes  Created.
*/

#ifndef __INCb_mode_th
#define __INCb_mode_th

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_mode_t
#define _DEFINED_mode_t
/* POSIX requires mode_t to be an 'int' type. */
typedef int             mode_t;
#endif /* _DEFINED_mode_t */


#ifdef __cplusplus
}
#endif

#endif /* __INCb_mode_th */


