/* semPxLibP.h - private POSIX semaphore library header */

/* 
 * Copyright 1984-2010, 2015, 2016 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17jun16,lau  For SEM_PX_CNT_DEC, updated count's type from int to atomicVal_t
27may16,dlk  Fixed 64-bit build warning in SEM_PX_CNT_DEC() macro.
05mar15,cww  Fixed reference counting in destroy routines (V7COR-2495)
29apr10,pad  Moved extern C statement after include statements.
02oct09,zl   include qLibP.h instead of qLib.h
27aug08,jpb  Renamed VSB header file
24jun08,jpb  Added include path for kernel configurations options set in
             vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
27jun07,mfj  Making SMP safe
13nov06,jpb  include base/b_struct_timespec.h, needed by _sem_timedwait()
07dec05,yvp  Added _sem_timedwait.
29sep04,dcc  updated _sem_destroy API to accept a dealloc parameter.
28sep04,fr   removed semPxCreateRtn prototype (SPR 101349)
30mar04,dcc  updated to use posixated object management.
05dec03,m_s  code-inspection changes
31oct03,m_s  moved the semaphore descriptor definition from semaphore.h
             and ported to Base 6
12jan94,kdl  changed semaphoreInit() to semPxLibInit().
17dec93,dvs  added semPxClassId
29nov93,dvs  written
*/

#ifndef __INCsemPxLibPh
#define __INCsemPxLibPh


#include <vsbConfig.h>
#include <stdarg.h>
#include <private/qLibP.h>
#include <private/objLibP.h>
#include <private/classLibP.h>
#include <base/b_struct_timespec.h>

#ifdef __cplusplus
extern "C" {
#endif

extern CLASS_ID semPxClassId;            /* POSIX sem class ID */

/* posix semaphore descriptor */

typedef struct sem_des          /* sem_t */
    {
    OBJ_CORE         objCore;   /* object core */
    SEM_ID           wSemId;    /* Wind semaphore identifier */
    struct sem_des * pSelf;     /* pointer to self */

#ifdef _WRS_CONFIG_SMP
    atomic_t         refCnt;    /* reference count for SMP */
    Q_HEAD      deleterPendQ;   /* deleter pend queue */
#endif

    } PSEMAPHORE;

#ifdef _WRS_CONFIG_SMP

/* These two macros are used to lock / unlock access to posix semaphores */

#define SEM_PX_LOCK()   SPIN_LOCK_ISR_TAKE(&semPxIsrSpinLock)
#define SEM_PX_UNLOCK() SPIN_LOCK_ISR_GIVE(&semPxIsrSpinLock)

/* SEMPX_CNT_INC increments the access counter for the semaphore */

#define SEM_PX_CNT_INC(semId)  vxAtomicInc (&semId->refCnt)

/*
 * After decrementing low enough that there are no other tasks
 * currently using the semaphore, we let the first task from the
 * pendQ go.
 */

#define SEM_PX_CNT_DEC(semId)						\
    do									\
    {									\
    atomicVal_t count;							\
sempxdecunlucky:							\
    count = vxAtomicGet (&semId->refCnt);				\
    if (count == 1)							\
	{								\
	KERNEL_ENTER ();						\
	if (vxAtomicDec (&semId->refCnt) == 1)				\
	    {								\
	    if (Q_FIRST (&semId->deleterPendQ) != NULL)			\
		windPendQGet (&semId->deleterPendQ);			\
	    }								\
	KERNEL_EXIT ();							\
	}								\
    else								\
	if (vxAtomicCas (&semId->refCnt, count, count - 1) == FALSE)	\
	    goto sempxdecunlucky;					\
    } while (0)

#endif /* _WRS_CONFIG_SMP */

/* function declarations */

extern STATUS        semPxLibInit (void);
extern int           _sem_destroy  (PSEMAPHORE * pxSemId, BOOL dealloc);
extern int           _sem_close    (PSEMAPHORE * pxSemId);
extern int           _sem_wait     (PSEMAPHORE * pxSemId);
extern int           _sem_trywait  (PSEMAPHORE * pxSemId);
extern int           _sem_post     (PSEMAPHORE * pxSemId);
extern int           _sem_getvalue (PSEMAPHORE * pxSemId, int * sval);
extern int           _sem_timedwait (PSEMAPHORE * pxSemId,
				     const struct timespec * absTimeout);

#ifdef __cplusplus
}
#endif

#endif /* __INCsemPxLibPh */
