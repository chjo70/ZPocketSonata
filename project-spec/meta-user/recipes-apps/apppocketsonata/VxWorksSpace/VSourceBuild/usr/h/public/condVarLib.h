/* condVarLib.h - user-level condition variable library header file */

/*
 * Copyright (c) 2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
*/

/*
modification history
--------------------
20may17,dlk  added CONDVAR_TASK_DELETION_WAKEUP (F5593)
23sep13,rfr  written
*/

#ifndef __INCcondVarLibh
#define __INCcondVarLibh

#include <vxWorks.h>
#include <semLib.h>
#include <condVarSysCall.h>

#ifdef __cplusplus
extern "C" {
#endif


#define CONDVAR_Q_FIFO		SEM_Q_FIFO
#define CONDVAR_Q_PRIORITY	SEM_Q_PRIORITY
#define CONDVAR_Q_MASK		SEM_Q_MASK

#define CONDVAR_INTERRUPTIBLE	SEM_INTERRUPTIBLE
#define CONDVAR_KERNEL_INTERRUPTIBLE SEM_KERNEL_INTERRUPTIBLE
#define CONDVAR_TASK_DELETION_WAKEUP SEM_TASK_DELETION_WAKEUP

#define S_condVarLib_INVALID_QUEUE_TYPE		(M_condVarLib | 101)
#define S_condVarLib_INVALID_OPERATION		(M_condVarLib | 102)

#define CONDVAR_ID_NULL ((CONDVAR_ID) 0)

CONDVAR_ID	condVarCreate (int options);
STATUS		condVarSignal (CONDVAR_ID condVar);
STATUS		condVarBroadcast (CONDVAR_ID condVar);
STATUS		condVarWait (CONDVAR_ID	condVar, SEM_ID	mutexId,
			     _Vx_ticks_t ticks);
CONDVAR_ID	condVarOpen(const char *name, int options, int mode,
			    void *context);
STATUS		condVarClose(CONDVAR_ID condVar);
STATUS		condVarDelete(CONDVAR_ID condVar);
STATUS		condVarUnlink(const char *name);


#ifdef __cplusplus
}
#endif

#endif /* __INCcondVarLibh */
