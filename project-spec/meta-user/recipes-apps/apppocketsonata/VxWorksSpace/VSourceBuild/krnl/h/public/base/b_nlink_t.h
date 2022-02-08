/* b_nlink_t.h - base type nlink_t definition header */

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

#ifndef __INCb_nlink_th
#define __INCb_nlink_th

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_nlink_t
#define _DEFINED_nlink_t
/* POSIX requires nlink_t to be an int type, signedness not specified. */
typedef unsigned long   nlink_t;
#endif /* _DEFINED_nlink_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_nlink_th */


