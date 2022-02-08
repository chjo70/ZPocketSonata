/* pthreadLibP.h - private header for POSIX threads (pthreads) */
 
/* 
 * Copyright (c) 2003-2006, 2010-2011, 2015 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */
 
/*
modification history
--------------------
02mar15,jpb  removed pthread dependency by creating function ptr (V7COR-1225)
17jan11,pad  Added lockedPthread and joinedPthread fields in pthreadCB
	     (defect 242878). Renamed a couple of other fields for clarity.
	     For robustness, made the VALID status flag a magic number.
11nov10,pad  Renamed internalPthread into pthreadCB.
10sep10,jpb  Added function pointers.
21sep06,pad  Added boolean field to the thread's internal data structure
	     indicating that the thread acquired a priority ceiling mutex
	     (defect #66491 / fix #66536).
27feb06,v_r  Added reference to control variable in thread's internal data
             structures (for SPR#117700 fix).
09sep04,pad  Moved definition of _RETURN_PTHREAD_SUCCESS in
             rtpPthreadLibP.h
10nov03,pad  Created to isolate internal types and macros from public POSIX
	     header pthread.h
*/
 
#ifndef __INCpthreadLibPh
#define __INCpthreadLibPh

#if defined(__cplusplus)
extern "C" {
#endif	/* __cplusplus */

/* defines */

#define SIGCANCEL SIGCNCL	/* just for readibility */

/* Thread's internal status flags */

#define VALID			0xE38E38E0	/* pthread is valid. This
						   magic number keeps 5 LSBs
						   zeroed out to hold any of
						   the other status flags. */
#define DETACHED		0x02	/* pthread is detached - NOT USED */
#define JOINABLE		0x04	/* pthread may be joined */
#define JOINER_WAITING		0x08	/* pthread has been joined */
#define TASK_EXITED		0x10	/* pthread's VxWorks task has exited */

/* typedefs */

typedef struct cleanup
    {
    struct cleanup * next;
    void	     (*routine)(void *);
    void *	     arg;
    } cleanupHandler;
 
typedef struct posix_thread_control_block
    {
    const void **	privateData;	/* pthread specific data */
    int			privateDataCount; /* num of pthread specific data */
    TASK_ID		vxTaskId;	/* VxWorks task under this pthread */
    unsigned long       flags;		/* thread's internal status flags */
    SEM_ID              exitJoinSemId;	/* joiner pthread pends on this */
    struct posix_thread_control_block *
			joinedPthread;	/* thread being joined by this one */
    SEM_ID              lock;		/* pthread CB protection mutex */
    struct posix_thread_control_block *
			lockedPthread;	/* thread being locked by this one */
    int			priority;	/* thread's POSIX priority */
    int                 cancelstate;	/* thread's cancellation state */
    int                 canceltype;	/* thread's cancellation type */
    int                 cancelrequest;	/* != 0 if cancel requests pending */
    void *              exitStatus;	/* pthread's exit status */
    cleanupHandler *    handlerBase;	/* list of cleanup handlers */
    pthread_cond_t *    cvcond;		/* cond var associated to this thread */
    pthread_once_t *    pOnceControl;	/* for pthread_once() cancellations */
    BOOL		isElevated;	/* TRUE if thread acquired a priority
					   ceiling mutex */
    } pthreadCB;

/* function pointers */

extern int     (*_func_pthread_testandset_canceltype)(int type, int * oldtype);
extern STATUS  (*_func_pthread_isvalid)(pthreadCB * pThread);
extern int     (*_func_pthread_create)(pthread_t * _Restrict pThread,
				       const pthread_attr_t * _Restrict pAttr,
				       void * (*startRoutine)(void *),
				       void * _Restrict arg);

#if defined(__cplusplus)
}
#endif	/* __cplusplus */

#endif /* __INCpthreadLibPh */

