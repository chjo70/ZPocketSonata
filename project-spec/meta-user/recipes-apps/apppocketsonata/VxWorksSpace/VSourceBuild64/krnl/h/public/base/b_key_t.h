/* b_key_t.h - base type key_t definition header */

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

#ifndef __INCb_key_th
#define __INCb_key_th

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_key_t
#define _DEFINED_key_t
typedef	long		key_t;		/* IPC key (for Sys V IPC) */
#endif /* _DEFINED_key_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_key_th */


