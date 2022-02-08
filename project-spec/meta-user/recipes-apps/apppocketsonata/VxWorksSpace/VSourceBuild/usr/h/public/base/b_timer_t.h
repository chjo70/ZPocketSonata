/* b_timer_t.h - base type timer_t definition header */

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
01d,16mar10,cww  Made timer_t a long type in user space
01c,09jun06,jmg  Added _WRS_KERNEL test macro and chaned timer_t's type to
                 int for posix and TIMER * for the kernel.
01b,21mar06,mil  Added protection macro _TIMER_T.
01a,16feb06,pes  Created.
*/

#ifndef __INCb_timer_th
#define __INCb_timer_th

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_DEFINED_timer_t) && !defined(_TIMER_T)
#define _DEFINED_timer_t
#define _TIMER_T
struct __timer;
 
#ifdef _WRS_KERNEL			/* posix timer_t type is an integer */
typedef struct __timer * timer_t; 	/* and in vxworks is a pointer to a */
#else					/* timer structure		    */
typedef unsigned long timer_t;

#endif /* _WRS_KERNEL */

#endif /* !defined(_DEFINED_timer_t) */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_timer_th */


