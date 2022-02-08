/* vxbIsrDeferLib.h - Task-level support for ISR deferral */

/*
 * Copyright (c) 2007, 2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
25apr16,pmr  make ISR deferral task stack size configurable (V7SP-978)
22oct13,x_z  merged isrDeferLibP.h and renamed to vxbIsrDeferLib.h
09oct13,x_z  fixed VxBus header path.
07may07,h_k  added an extra arg isrDeferQueueGet() for a future support.
             added a global mode arg to isrDeferLibInit();
20mar07,sru  factor into public and private headers
02feb07,sru  written
*/

#ifndef __INCvxbIsrDeferLibh
#define __INCvxbIsrDeferLibh

#include <vxWorks.h>
#include <lstLib.h>
#include <hwif/vxBus.h>
#include <spinLockLib.h>
#include <private/semLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/*
 * There are two ways to implement deferral.  A shared queue for each CPU,
 * or an individual queue for each interrupt source.  This is global mode
 * for the SMP system.
 */

#define ISR_DEFER_MODE_PER_CPU      0
#define ISR_DEFER_MODE_PER_SOURCE   1


/* typedefs */

typedef struct isrDeferQueue
    {
    LIST            list;      /* list of pending work */
    SEMAPHORE       syncSem;  /* given by ISR, taken by task */
    spinlockIsr_t   lock;     /* for list maintenance operations */
    TASK_ID         tid;      /* deferral task id */
    int             cpuIdx;      /* CPU for task handling this queue */
    } ISR_DEFER_QUEUE;

typedef struct isrDeferJob
    {
    NODE node;            /* for chaining deferred work */
    void (*func)(void *);    /* deferral function */
    void *pData;         /* pointer to driver-specific data */
    } ISR_DEFER_JOB;

typedef struct isrDeferQueue * ISR_DEFER_QUEUE_ID;

/* function declarations */

STATUS isrDeferLibInit
    (
    int             mode,           /* global deferral queue mode */
    size_t          stackSize       /* global deferral task stack size */
    );

ISR_DEFER_QUEUE_ID isrDeferQueueGet 
    (
    VXB_DEV_ID      pInst,    /* VxBus device ID of requester, or NULL */
    int             intIdx,    /* interrupt source index */
    int             cpuIdx,    /* CPU index for deferral task */
    int             mode    /* deferral queue mode (for future use) */
    );

void isrDeferJobAdd 
    (
    ISR_DEFER_QUEUE_ID  queueId,    /* deferral queue handling these jobs */
    ISR_DEFER_JOB *     pJob    /* work to defer */
    );

ISR_DEFER_QUEUE_ID isrDeferIsrReroute
    (
    ISR_DEFER_QUEUE_ID  queueId,    /* queue allocated by isrDeferQueueGet */
    int                 cpuIdx    /* CPU to handle this queue's interrerupts */
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbIsrDeferLibh */
