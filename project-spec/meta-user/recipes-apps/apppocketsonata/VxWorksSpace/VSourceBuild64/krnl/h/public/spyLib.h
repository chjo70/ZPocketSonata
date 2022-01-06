/* spyLib.h - header file for spyLib.c */

/* 
 * Copyright (c) 1990-1992,1995,2003,2008-2009 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
02f,27may09,jmp  Removed non-public prototypes.
02e,23sep08,jmp  Added the max number of tasks that can be spied to
                 spyLibInit() (CQ:WIND00106559).
02d,09may03,pes  PAL conditional compilation cleanup. Phase 2.
02c,27may95,p_m  added spyLibInit() and allow decoupling of the result printing.
02b,22sep92,rrr  added support for c++
02a,04jul92,jcf  cleaned up.
01c,26may92,rrr  the tree shuffle
01b,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01a,05oct90,shl created.
*/

#ifndef __INCspyLibh
#define __INCspyLibh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#if !defined (_WRS_SPY_TASK_SIZE)
#define _WRS_SPY_TASK_SIZE	6000	/* Default: may be overridden by arch */
#endif /* _WRS_SPY_TASK_SIZE */

/* function declarations */

extern void 	spyLibInit (int spyTasksMax);

#ifdef __cplusplus
}
#endif

#endif /* __INCspyLibh */
