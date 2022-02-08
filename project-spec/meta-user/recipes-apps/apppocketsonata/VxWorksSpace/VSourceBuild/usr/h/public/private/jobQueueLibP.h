/* jobQueueLibP.h - private header file for jobQueueLib */

/*
 * Copyright (c) 2005, 2007-2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16mar16,kjn  Made it possible to use jobQueueLib in user-space
19jan16,dlk  Allow later job posts to awaken service task in case
             original posting task is deleted or preempted before
             giving semaphore (V7COR-3973).
20jan14,rjq  move JOBQUEUE to OS service
30jul09,dlk  WIND00168645 - use deterministic spin locks by default.
18jun08,jpb  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.  Added include path
             for kernel configurations options set in vsb.
16jan08,dlk  Rename spinLockFastLib --> spinlockIsrNdLib.
10dec07,dlk  Use fast spin locks.
20feb07,kch  Merged from base6_iter12_smp-dev - Use spinlocks instead of
             intLock.
13jul05,dlk  Added taskId member to JOB_QUEUE.
06may05,dlk  Written.
*/

/* Note, jobQueueLib.h should be included before this private header */

#ifndef __INCjobQueueLibPh
#define __INCjobQueueLibPh

#include <vsbConfig.h>

#include <semLib.h>
#include <setjmp.h>

#include <private/semLibP.h>

#ifdef _WRS_KERNEL
#ifdef _WRS_CONFIG_SMP
#ifdef _WRS_CONFIG_DETERMINISTIC
#include <spinLockLib.h>

typedef spinlockIsr_t 	QJOB_LOCK;

#define JOBQ_LOCK(pLock)                                \
    do { SPIN_LOCK_ISR_TAKE (pLock); } while ((0))
#define JOBQ_UNLOCK(pLock)                              \
    do { SPIN_LOCK_ISR_GIVE (pLock); } while ((0))
#define JOBQ_LOCK_INIT(pLock)                           \
    do { SPIN_LOCK_ISR_INIT (pLock, 0); } while ((0))
#else
#include <spinlockIsrNdLib.h>

typedef struct qjobLock
    {
    spinlockIsrNd_t	sl;
    int                 key;
    } QJOB_LOCK;

#define JOBQ_LOCK(pLock)				\
    do { (pLock)->key = spinLockIsrNdTake (&(pLock)->sl); } while ((0))
#define JOBQ_UNLOCK(pLock)                              \
    do { spinLockIsrNdGive (&(pLock)->sl, (pLock)->key); } while ((0))
#define JOBQ_LOCK_INIT(pLock)                   \
    do { spinLockIsrNdInit (&(pLock)->sl); (pLock)->key = 0; } while ((0))
#endif /* _WRS_CONFIG_DETERMINISTIC */

#else /* Uniprocessor */
#include <intLib.h>

typedef int		QJOB_LOCK;

#define JOBQ_LOCK(pLock)			\
    do { *(pLock) = INT_CPU_LOCK( ); } while ((0))
#define JOBQ_UNLOCK(pLock)                      \
    do { INT_CPU_UNLOCK((*pLock)); } while ((0))
#define JOBQ_LOCK_INIT(pLock) do { (*pLock) = 0; } while ((0))

#endif /* _WRS_CONFIG_SMP */
#else /* !_WRS_KERNEL */

typedef SEMAPHORE	QJOB_LOCK;

#define JOBQ_LOCK_OPTS SEM_Q_PRIORITY | SEM_DELETE_SAFE | SEM_INVERSION_SAFE
#define JOBQ_LOCK(pLock)                                                \
    do { (void)semUMTake (pLock, WAIT_FOREVER); } while ((0))
#define JOBQ_UNLOCK(pLock)                      \
    do { (void)semUMGive (pLock); } while ((0))
#define JOBQ_LOCK_INIT(pLock)                                   \
    do { (void)semMInit (pLock, JOBQ_LOCK_OPTS); } while ((0))

#endif/* !_WRS_KERNEL */

#ifdef __cplusplus
extern "C" {
#endif

#define QJOB_ENQUEUED	0x100
#define QJOB_POOL_ALLOC 0x200

typedef struct _QJOB_QUEUE_HEAD
    {
    QJOB * pHead;
    QJOB ** ppTail;
    } QJOB_QUEUE_HEAD;

typedef struct _QJOB_FREE_HEAD
    {
    QJOB_STANDARD * pHead;
    } QJOB_FREE_HEAD;

typedef QJOB_FREE_HEAD QJOB_BLOCK_HEAD; /* [;^] */

typedef struct _QJOB_STD_POOL
    {
    QJOB_FREE_HEAD  free;		/* The free list of standard jobs */
    QJOB_BLOCK_HEAD blocks;		/* The list of blocks of std. jobs */
    QJOB_LOCK *     pLock;
    UINT32          refCount;		/* How many attached job queues? */
    } QJOB_STD_POOL;

typedef struct _QUIT_QJOB
    {
    QJOB job;
    volatile int * pQuitValue;
    jmp_buf * pJmpBuf;
    VOIDFUNCPTR qFunc;
    void * arg1;
    void * arg2;
    } QUIT_QJOB;

typedef struct _JOB_QUEUE
    {
    QJOB_QUEUE_HEAD	jobs [32];	/* The enqueued jobs */
    UINT32		activePri;	/* which queues hold jobs? */
    UINT32		flags;		/* Is queue in use? */
#define JOBQ_FLG_RUNNING        0x1
#define JOBQ_FLG_CREATED        0x2
#define JOBQ_FLG_AWAKE          0x4
#ifdef JOBQ_PRI_MASKABLE
    UINT32		priMask;	/* which priorities are enabled? */
#endif
    QJOB_STD_POOL *	pStdPool;	/* pool for standard jobs */
    SEMAPHORE		sem;		/* binary semaphore */
    QJOB_BLOCK_HEAD	blocks;		/* list of blocks of standard jobs */
    TASK_ID		taskId;		/* Task currently running */
					/* jobQueueProcess(). */

    QUIT_QJOB		quitJob;
    void *		userVal;	/* reserved for queue creator */
    QJOB_LOCK           qLock;
    } JOB_QUEUE;

#define QUIT_JOB_TO_JOB_QUEUE(q) \
    ((JOB_QUEUE *)((char *)(q) - offsetof (JOB_QUEUE, quitJob)))

#ifdef __cplusplus
}
#endif

#endif /* __INCjobQueueLibPh */
