/* b_blksize_t.h - base type blksize_t definition header */

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

#ifndef __INCb_blksize_th
#define __INCb_blksize_th

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_blksize_t
#define _DEFINED_blksize_t
/* POSIX requires blksize_t to be a signed int type */
typedef long blksize_t;
#endif  /* _DEFINED_blksize_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_blksize_th */


