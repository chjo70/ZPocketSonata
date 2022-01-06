/* b_blkcnt_t.h - base type blkcnt_t definition header */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
09nov10,jxu  Changed type of blkcnt_t to signed per POSIX. 
16feb06,pes  Created.
*/

#ifndef __INCb_blkcnt_th
#define __INCb_blkcnt_th

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_blkcnt_t
#define _DEFINED_blkcnt_t
typedef long blkcnt_t;
#endif  /* _DEFINED_blkcnt_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_blkcnt_th */


