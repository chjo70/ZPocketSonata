/* taskPxLibCommonP.h - common header for POSIX support in VxWorks task */
 
/*
 * Copyright (c) 2005-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
01d,28apr10,pad  Moved extern C statement after include statements.
01c,24may06,jln  added VX_POSIX_SCHED_SPORADIC
01b,09jul05,jln  removed VX_POSIX_INSERT_HEAD_CHECK
01a,26jun05,jln  created.
*/
 
#ifndef __INCtaskPxLibCommonPh
#define __INCtaskPxLibCommonPh

/* includes */

#include <vwModNum.h>
#include <private/timerLibP.h>

#if defined(__cplusplus)
extern "C" {
#endif	/* __cplusplus */

/* general status code */

#define S_taskPxLib_ILLEGAL_PRIORITY		(M_taskPxLib | 101)
#define S_taskPxLib_ILLEGAL_POLICY		(M_taskPxLib | 102)
#define S_taskPxLib_NOT_ENOUGH_ATTRS            (M_taskPxLib | 103)
#define S_taskPxLib_INVALID_INITBUDGET          (M_taskPxLib | 104)
#define S_taskPxLib_INVALID_MAXREPL		(M_taskPxLib | 105)
#define S_taskPxLib_NOT_SPECIFY_POLICY		(M_taskPxLib | 106)
#define S_taskPxLib_CHANGE_SS_POLICY            (M_taskPxLib | 107)
#define S_taskPxLib_NOT_CONFIG_SCHED_SPORADIC   (M_taskPxLib | 108)

/* POSIX "schedInfo" definition for VxWorks task */

#define VX_POSIX_SCHED_FIFO			0x0001
#define VX_POSIX_SCHED_RR			0x0002
#define VX_POSIX_SCHED_OTHER			0x0004
#define VX_POSIX_SCHED_SPORADIC			0x0008

#define VX_POSIX_INSERT_HEAD                    0x80000000

#define VX_POSIX_SCHED_MASK			(VX_POSIX_SCHED_FIFO | \
						 VX_POSIX_SCHED_RR   | \
						 VX_POSIX_SCHED_OTHER | \
						 VX_POSIX_SCHED_SPORADIC)

/* flag: bit def for "flag" in TASK_PX_ATTR passed to VxWorks kernel */

#define VX_POSIX_FLAG_SETSCHEDPRIO	0x0001	/* pthread_setschedprio() */
#define VX_POSIX_FLAG_PRIORITY          0x0002  /* set/get priority       */
#define VX_POSIX_FLAG_POLICY            0x0004  /* set/get policy         */
#define VX_POSIX_FLAG_SS_LOWPRIO        0x0008  /* set/get SS low priority */
#define VX_POSIX_FLAG_SS_REPLPERIOD     0x0010  /* set/get SS repl period */
#define VX_POSIX_FLAG_SS_INITBUDGET     0x0020  /* set/get SS init budget */
#define VX_POSIX_FLAG_SS_MAXREPL        0x0040  /* set/get SS max repl num */

#define VX_POSIX_FLAG_SS_ATTRS		(VX_POSIX_FLAG_SS_LOWPRIO | \
  				  	 VX_POSIX_FLAG_SS_REPLPERIOD | \
					 VX_POSIX_FLAG_SS_INITBUDGET | \
					 VX_POSIX_FLAG_SS_MAXREPL)
/* typedef */

/* For application binary compatibility, only append new members if needed */
  
typedef struct task_px_attr 
     {
     UINT	flag;		/* bits to specify which attr to set/get */
     int        priority;	/* priority attribute */
     int        policy;		/* policy attribute */

     /* Members below are for SCHED_SPORADIC threads */

     int             	ssLowPrio;	/* sched_ss_low_priority */ 
     struct timespec 	ssReplPeriod;	/* sched_ss_repl_period */
     struct timespec 	ssInitBudget;	/* sched_ss_init_budget */
     int             	ssMaxRepl;	/* sched_ss_max_repl */

     /* add new members from here */

     } TASK_PX_ATTR;

#if defined(__cplusplus)
}
#endif	/* __cplusplus */

#endif /* __INCtaskPxLibCommonPh */

