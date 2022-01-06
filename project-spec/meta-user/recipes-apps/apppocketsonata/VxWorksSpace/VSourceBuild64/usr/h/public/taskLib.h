/* taskLib.h - VxWorks user tasking library interface header */

/*
 * Copyright (c) 2003-2004, 2006, 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01m,07dec11,jpb  Added taskWait prototype.
01l,29jul10,pad  Moved extern C statement after include statements.
01k,01jul10,jpb  Changed prototype for taskExit.
01j,31mar10,gls  removed taskRtpLock/Unlock()
01i,07jan10,jpb  Updated for LP64 adaptation.
01h,28oct09,kk   make taskRtpLock/Unlock() Deprecated (WIND00187151)
01g,01aug06,kk   fix Defect# 59472 - remove taskSafe() & taskUnSafe() 
                 prototypes, already in taskLibCommon.h
01f,22jan04,aeg  removed task option bit defines.
01e,04nov03,md   changed taskULock/taskUUnlock to taskRtpLock/taskRtpUnlock
01d,09oct03,aeg  moved TASK_UXXX() macros to taskLibP.h;
		 added taskExit() function prototype.
01c,25sep03,aeg  changed TASK_USAFE() to TLS key changes.
01b,05sep03,aeg  changed WRS_ASM to _WRS_ASM
01a,12aug03,aeg  written based on v05b of kernel version of taskLib.h
*/

#ifndef __INCtaskLibh
#define __INCtaskLibh

#include <vxWorks.h>		/* common definitions for all VxWorks libs */

#include <taskLibCommon.h>	/* common between kernel and user 	   */
#include <taskSysCall.h>

#ifdef __cplusplus
extern "C" {
#endif

/* provided for backwards compatibility */

#define taskIdCurrent  taskIdSelf()

/*******************************************************************************
*
* TASK_ID_VERIFY - check the validity of a task
*
* This macro verifies the existence of the specified task.  If the specified
* taskId is not valid, errno is set with the appropriate invalid id status.
*
* RETURNS: OK or ERROR if invalid task id
*
* \NOMANUAL
*/

#define TASK_ID_VERIFY(tid)						      \
    (									      \
    taskIdVerify (tid)							      \
    )

/* function declarations */

#ifndef _ASMLANGUAGE
extern STATUS   taskNameGet	(TASK_ID tid, char *pBuf, size_t bufSize);
extern void	taskExit	(_Vx_exit_code_t code);
extern STATUS	taskWait	(TASK_ID tid, _Vx_ticks_t timeout);

extern STATUS 	taskCreateHookAdd 	(STATUS (* createHook)(TASK_ID));
extern STATUS 	taskCreateHookDelete 	(STATUS (* createHook)(TASK_ID));
extern STATUS 	taskDeleteHookAdd 	(STATUS (* deleteHook)(TASK_ID));
extern STATUS 	taskDeleteHookDelete 	(STATUS (* deleteHook)(TASK_ID));

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}

extern STATUS 	taskCreateHookAdd 	(FUNCPTR createHook)
        _WRS_DEPRECATED ("use fully qualified function pointer version of API");
extern STATUS 	taskCreateHookDelete 	(FUNCPTR createHook)
        _WRS_DEPRECATED ("use fully qualified function pointer version of API");
extern STATUS 	taskDeleteHookAdd 	(FUNCPTR deleteHook)
        _WRS_DEPRECATED ("use fully qualified function pointer version of API");
extern STATUS 	taskDeleteHookDelete 	(FUNCPTR deleteHook)
        _WRS_DEPRECATED ("use fully qualified function pointer version of API");

/* inlined C++ wrapper for the old-style FUNCPTR */

inline STATUS taskCreateHookAdd
    (
    FUNCPTR createHook
    )
    {
    return taskCreateHookAdd ((STATUS (*)(TASK_ID))createHook);
    }

inline STATUS taskCreateHookDelete
    (
    FUNCPTR createHook
    )
    {
    return taskCreateHookDelete ((STATUS (*)(TASK_ID))createHook);
    }

inline STATUS taskDeleteHookAdd
    (
    FUNCPTR deleteHook
    )
    {
    return taskDeleteHookAdd ((STATUS (*)(TASK_ID))deleteHook);
    }

inline STATUS taskDeleteHookDelete
    (
    FUNCPTR deleteHook
    )
    {
    return taskDeleteHookDelete ((STATUS (*)(TASK_ID))deleteHook);
    }

#endif /* __cplusplus */
#endif /* __INCtaskLibh */
