/* condVarLib.h - condition variable library header file */

/*
 * Copyright (c) 2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may17,dlk  Added CONDVAR_TASK_DELETION_WAKEUP (F5593)
30sep13,rfr  added function from condVarOpen.c
21aug13,rfr  updated to match draft HLD
04jun13,zl   written.
*/

#ifndef __INCcondVarLibh
#define __INCcondVarLibh

#include <vxWorks.h>
#include <semLib.h>
#include <vwModNum.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

#define CONDVAR_Q_FIFO		SEM_Q_FIFO
#define CONDVAR_Q_PRIORITY	SEM_Q_PRIORITY
#define CONDVAR_Q_MASK		SEM_Q_MASK

#define CONDVAR_INTERRUPTIBLE	SEM_INTERRUPTIBLE
#define CONDVAR_KERNEL_INTERRUPTIBLE SEM_KERNEL_INTERRUPTIBLE
#define CONDVAR_TASK_DELETION_WAKEUP SEM_TASK_DELETION_WAKEUP

#define S_condVarLib_INVALID_QUEUE_TYPE		(M_condVarLib | 101)
#define S_condVarLib_INVALID_OPERATION		(M_condVarLib | 102)

#ifndef _WRS_CONFIG_LP64
#define VX_CONDVAR_SIZE (0x60)
#else
#define VX_CONDVAR_SIZE (0xb0)
#endif


#define VX_CONDVAR(name) \
    _WRS_DATA_ALIGN_BYTES(VX_OBJ_ALIGN_SIZE) char name[VX_CONDVAR_SIZE];

#define CONDVAR_ID_NULL NULL


CONDVAR_ID	condVarCreate (int options);
CONDVAR_ID	condVarInitialize (char *condVar, int options);
STATUS		condVarDelete (CONDVAR_ID condVar);
STATUS		condVarDestroy (CONDVAR_ID condVar, BOOL dealloc );
STATUS		condVarTerminate (CONDVAR_ID condVar);
STATUS		condVarSignal (CONDVAR_ID condVar);
STATUS		condVarBroadcast (CONDVAR_ID condVar);
STATUS		condVarWait (CONDVAR_ID	condVar, SEM_ID	mutexId, 
			     _Vx_ticks_t ticks);
STATUS		condVarShow(CONDVAR_ID condVar, int level);

void		condVarOpenInit(void);
CONDVAR_ID	condVarOpen(const char *name, int options, int mode, 
			    void *context);
STATUS		condVarClose(CONDVAR_ID condVar);
STATUS		condVarUnlink(const char *name);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCcondVarLibh */
