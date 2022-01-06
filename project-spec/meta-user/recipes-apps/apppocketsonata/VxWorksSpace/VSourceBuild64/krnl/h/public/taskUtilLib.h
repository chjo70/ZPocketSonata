/* taskUtilLib.h - kernel utility interface header */

/*
 * Copyright (c) 2005, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
01g,14jan11,cww  Fix compiler warnings (WIND00241209)
01f,05may10,cww  64-bit SMP update
01e,29apr10,pad  Moved extern C statement after include statements.
01d,22apr09,pcs  Updated to add support for LP64 data model.
01c,10oct05,kk   fix TASK_SCHED_INFO_SET macro
01b,31aug05,gls  updated for checkin
01a,04mar05,kk   written 
*/

#ifndef __INCtaskUtilLibh
#define __INCtaskUtilLibh

#include <vxWorks.h>
#include <taskLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typdef */

typedef UINT32	SPARE_NUM;	/* allotted number for TCB spare field */

/* defines */

/*******************************************************************************
*
* TASK_SCHED_INFO_GET - get the pSchedInfo field in the TCB
*
* This macro gets the value of the pSchedInfo field in the TCB.
*
* PROTOTYPE: void * TASK_SCHED_INFO_GET(TASK_ID tid)
*
* RETURNS: N/A
*
* \NOMANUAL
*/

#define TASK_SCHED_INFO_GET(tid)					\
    (									\
    ((WIND_TCB *)(tid))->pSchedInfo					\
    )

/*******************************************************************************
*
* TASK_SCHED_INFO_SET - set the pSchedInfo field in the TCB
*
* This macro sets the value of the pSchedInfo field in the TCB.
*
* PROTOTYPE: void TASK_SCHED_INFO_SET(TASK_ID tid, void * schedInfo)
*
* RETURNS: N/A
*
* \NOMANUAL
*/

#define TASK_SCHED_INFO_SET(tid, schedInfo)				\
    (									\
    ((WIND_TCB *)(tid))->pSchedInfo = (void *) schedInfo		\
    )

/* function declarations */

extern void		taskSpareNumAllot (TASK_ID tid,
					   SPARE_NUM * numAllotted);
extern _Vx_usr_arg_t	taskSpareFieldGet (TASK_ID tid, SPARE_NUM num);
extern STATUS		taskSpareFieldSet (TASK_ID tid, SPARE_NUM num,
					   _Vx_usr_arg_t value);

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskUtilLibh */
