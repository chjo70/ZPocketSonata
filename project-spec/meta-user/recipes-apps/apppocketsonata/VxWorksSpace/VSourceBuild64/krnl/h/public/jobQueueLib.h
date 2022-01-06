/* jobQueueLib.h - header file for the prioritized job queueing library */

/*
 * Copyright (c) 2005-2007, 2014, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */


/*
modification history
--------------------
20mar17,jsp  Added support for jobQueueIsRunning() (F8638)
16mar16,kjn  Added support for using jobQueueLib in user-space.
20jan14,rjq  move JOBQUEUE to OS service
10nov10,dlk  Move extern "C" after last header file include. WIND00240828.
11oct07,dlk  Added _func_netDaemonIxToQId and _func_netDaemonQIdToIx
             declarations.
22jun06,dlk  Add jobQueueUtilInit() prototype.
25aug05,dlk  Add section tags.
13jul05,dlk  Added member_to_object() and QJOB_IS_BUSY() definitions.
             Added 'extern' on prototypes, and jobQueueTask() prototype.
14may05,dlk  Written.
*/

#ifndef __INCjobQueueLibh
#define __INCjobQueueLibh

#include <taskLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* macros */

#define member_to_object(pMember, type, memberName) \
    ((type *)((char *)(pMember) - offsetof (type, memberName)))

#define JOBQ_PRI_MASKABLE   /* enable priority masking */

/*
 * The QJOB_BUSY bit in the priInfo member of a pre-allocated QJOB may be
 * used for any purpose by the jobLib client.  jobLib does not modify this
 * bit, and is not affected by it.
 */

#define QJOB_BUSY	0x20 /* managed by client */

#define QJOB_IS_BUSY(pJob) ((pJob)->priInfo & QJOB_BUSY)
#define QJOB_SET_BUSY(pJob) ((pJob)->priInfo |= QJOB_BUSY)
#define QJOB_CLEAR_BUSY(pJob) ((pJob)->priInfo &= ~QJOB_BUSY)

#define QJOB_PRI_LOWEST	0	/* minimum, least urgent priority */
#define QJOB_PRI_HIGHEST 31	/* maximum, most urgent priority */
#define QJOB_NUM_PRI  32	/* Number of prioritiies */
#define QJOB_PRI_MASK 0x1f	/* Mask for priority bits */

#define QJOB_SET_PRI(pJob, pri) \
    ((pJob)->priInfo = ((pJob)->priInfo & ~QJOB_PRI_MASK) | \
     ((pri) & QJOB_PRI_MASK))

#define QJOB_GET_PRI(pJob) ((pJob)->priInfo & QJOB_PRI_MASK)

/* types */

typedef void (* QJOB_FUNC) (void *);


/*
 * A QJOB is typically a member of a larger structure with information
 * used by the handler function 'func'. func() is passed a pointer to
 * the QJOB as its only argument.
 */

typedef struct _QJOB
    {
    struct _QJOB *	pNext;
    UINT32		priInfo;	/* modify with QJOB_SET_PRI () */
    QJOB_FUNC		func;		/* function to execute */
    } QJOB;

typedef struct _QJOB_STANDARD
    {
    QJOB job;
    void * arg1;
    void * arg2;
    void * arg3;
    void * arg4;
    void * arg5;
    } QJOB_STANDARD;

struct _JOB_QUEUE;

typedef struct _JOB_QUEUE * JOB_QUEUE_ID;

struct _QJOB_STD_POOL;

typedef struct _QJOB_STD_POOL * QJOB_STD_POOL_ID;

/*
 * Functions to convert network daemon index to a job queue ID,
 * and vice-versa.
 * Set by daemon.c or possibly other facility.
 */

extern JOB_QUEUE_ID (*_func_netDaemonIxToQId) (int index);

/* This one returns -1 for failure: */
extern int (*_func_netDaemonQIdToIx) (JOB_QUEUE_ID qId);

/*
 * Variant of jobQueueProcess() to use. By default this
 * function pointer points at jobQueueProcess(), but if
 * jobQueueAdvLib() is included, it may be
 * point at jobQueueProcessWrapper().
 */
extern int (* jobQueueProcessFunc) (JOB_QUEUE_ID pJobQ);

/* function declarations */

_WRS_INITTEXT
extern void	jobQueueLibInit (void);
_WRS_FASTTEXT
extern STATUS	jobQueuePost (JOB_QUEUE_ID jobQueueId, QJOB * pJob);
_WRS_FASTTEXT
extern STATUS	jobQueueStdPost (JOB_QUEUE_ID jobQueueId, int pri,
				 VOIDFUNCPTR pFunc, void * arg1, void * arg2,
				 void * arg3, void * arg4, void * arg5);

extern JOB_QUEUE_ID	jobQueueCreate (QJOB_STD_POOL_ID stdPoolId);
extern STATUS		jobQueueInit (JOB_QUEUE_ID jobQueueId,
				      QJOB_STD_POOL_ID stdPoolId);

_WRS_FASTTEXT
extern int	jobQueueProcess (JOB_QUEUE_ID jobQId);
extern TASK_ID	jobQueueTask (JOB_QUEUE_ID jobQueueId);


#ifdef JOBQ_PRI_MASKABLE
extern UINT32	jobQueuePriorityMask (JOB_QUEUE_ID jobQId, UINT32 disablePri,
				      UINT32 enablePri);
#endif /* JOBQ_PRI_MASKABLE */

/* standard pools */
extern STATUS	jobQueueStdPoolInit (QJOB_STD_POOL_ID stdPoolId);
extern STATUS	jobQueueStdJobsAlloc (QJOB_STD_POOL_ID stdPoolId,
				      int nStdJobs);

/* in jobQueueUtilLib */

extern void	jobQueueUtilInit (void);
extern STATUS	jobQueueQuit (JOB_QUEUE_ID jobQId, int pri, int quitValue,
			      VOIDFUNCPTR pFunc, void * arg1, void * arg2);
extern int	jobQueueProcessWrapper (JOB_QUEUE_ID jobQId);

extern STATUS	jobQueueDelete (JOB_QUEUE_ID jobQId);
extern STATUS	jobQueueTerminate (JOB_QUEUE_ID jobQId);

extern STATUS	jobQueueStdPoolJobsFree (QJOB_STD_POOL_ID pStdPool);

extern BOOL	jobQueueIsRunning (JOB_QUEUE_ID jobQId);

#ifdef __cplusplus
}
#endif

#endif /* __INCjobQueueLibh */
