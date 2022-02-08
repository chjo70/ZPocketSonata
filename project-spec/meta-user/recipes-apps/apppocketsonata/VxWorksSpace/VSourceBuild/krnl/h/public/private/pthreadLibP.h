/* pthreadLibP.h - private header for POSIX threads (pthreads) */
 
/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */
 
/*
modification history
--------------------
01e,17jan11,pad  Added lockedPthread and joinedPthread fields in pthreadCB
		 (defect 242878). Renamed a couple of other fields for clarity.
		 For robustness, made the VALID status flag a magic number.
01d,11nov10,pad  Moved internal types from pthread.h in here.
01c,02nov10,pad  Removed _pthreadSetCancelType() declaration as it is now an
		 inline routine, renamed pthread_setcanceltype_inline(), in
		 pthreadLib.c (part of defect 233318).
01b,14may10,jpb  Added pthreadLibInit prototype.
01a,17apr10,jpb  created 
*/
 
#ifndef __INCpthreadLibPh
#define __INCpthreadLibPh

/* includes */

#include <vxWorks.h>
#include <base/b_pthread_attr_t.h>
#include <base/b_pthread_t.h>
#include <pthread.h>

#if defined(__cplusplus)
extern "C" {
#endif	/* __cplusplus */

/* Defines */

#define _RETURN_PTHREAD_SUCCESS	0	/* make fcn returns more readable */

#define SIGCANCEL SIGCNCL		/* just for readibility */

/* Thread's internal status flags */

#define VALID                   0xE38E38E0	/* pthread is valid. This
						   magic number keeps 5 LSBs
						   zeroed out to hold any of
						   the other status flags. */
#define DETACHED	        0x02	/* pthread is detached - NOT USED */
#define JOINABLE                0x04	/* pthread may be joined */
#define JOINER_WAITING          0x08	/* pthread has been joined */
#define TASK_EXITED             0x10	/* pthread's VxWorks task has exited */

/* Typedefs */

typedef struct cleanup
    {
    struct cleanup *next;
    void(*routine)(void *);
    void *arg;
    } cleanupHandler;
 
typedef struct posix_thread_control_block
    {
    const void **       privateData;	/* pthread specific data */
    int                 privateDataCount; /* num of pthread specific data */
    TASK_ID             vxTaskId;	/* VxWorks task under this pthread */
    unsigned long       flags;		/* thread's internal status flags */
    SEM_ID              exitJoinSemId;	/* joiner pthread pends on this */
    struct posix_thread_control_block *
			joinedPthread;	/* thread being joined by this one */
    SEM_ID              lock;		/* pthread CB protection mutex */
    struct posix_thread_control_block *
			lockedPthread;	/* thread being locked by this one */
    int                 priority;	/* thread's POSIX priority */
    int                 cancelstate;	/* thread's cancellation state */
    int                 canceltype;	/* thread's cancellation type */
    int                 cancelrequest;	/* != 0 if cancel requests pending */
    void *              exitStatus;	/* pthread's exit status */
    cleanupHandler *    handlerBase;	/* list of cleanup handlers */
    pthread_cond_t *    cvcond;		/* cond var associated to this thread */
    pthread_once_t *	pOnceControl;	/* for pthread_once() cancellations */
    } pthreadCB;

/* Kernel support routine prototypes */

extern STATUS   _pthreadLibInit (void (*deleteUserTaskEntry)(pthreadCB *));
extern int      _pthreadCreate (pthread_t *pThread,
                                const pthread_attr_t *pAttr,
                                void * (*wrapperFunc)(void *),
                                void * (*start_routine)(void *),
                                void *arg,
                                int priNumMode);
extern TASK_ID  _pthreadSemOwnerGet (SEM_ID semId);
extern int      _pthreadSemStateGet (SEM_ID semId);

/* externs */

extern void pthreadLibInit (void);

/* function pointer prototypes */

extern int (*_func_pthread_testandset_canceltype)(int type, int * oldType);

/* Non published pthread routines */

int pthread_testandset_canceltype (int type, int * oldtype);

#if defined(__cplusplus)
}
#endif	/* __cplusplus */

#endif /* __INCpthreadLibPh */
