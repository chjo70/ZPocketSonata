/* b_swab.h - base function swab definition header */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01a,14foct11,jpb  Created.
*/

#ifndef __INCb_SWABh
#define __INCb_SWABh

#ifdef __cplusplus
extern "C" {
#endif

extern void  swab  (const void * source, void * dest, size_t nbytes);

#ifdef __cplusplus
}
#endif

#endif /* __INCb_SWABh */


