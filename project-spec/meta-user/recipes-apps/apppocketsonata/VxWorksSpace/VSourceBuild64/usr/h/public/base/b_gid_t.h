/* b_gid_t.h - base type gid_t definition header */

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

#ifndef __INCb_gid_th
#define __INCb_gid_th

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_gid_t
#define _DEFINED_gid_t
/* POSIX requires gid_t to be an 'int' type, signedness not specified. */
typedef unsigned short  gid_t;
#endif /* _DEFINED_gid_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_gid_th */


