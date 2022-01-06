/* sigeventCommon.h - sigevent structure, needed by several header files */

/*
 * Copyright (c) 2003, 2005-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01g,26mar10,cww  LP64 adaptation
01f,12jun06,gls  added sigev_id and sigev_notifier_id to sigevent
01e,22feb06,pes  Get pthread_attr_t def from base/b_pthread_attr_t.h
                 instead of pthreadCommon.h.
01d,26jan06,mil  Moved union sigval into base type file.
01c,07dec05,gls  added additional sigevent members for SIGEV_THREAD support
01b,07dec05,gls  added SIGEV_THREAD
01a,29sep03,ans  written.
*/

#ifndef __INCsigeventcommonh
#define __INCsigeventcommonh

#include <base/b_pthread_attr_t.h>  /* for pthread_attr_t for sigevent */
#include <base/b_union_sigval.h>    /* for sigval */

#ifdef __cplusplus
extern "C" {
#endif

#define SIGEV_NONE              0x0
#define SIGEV_SIGNAL            0x1
#define SIGEV_TASK_SIGNAL       0x2
#define SIGEV_TIMER_SIGNAL      0x4
#define SIGEV_TIMER_TASK_SIGNAL 0x8
#define SIGEV_THREAD            0x10
#define SIGEV_TIMER_THREAD      0x20
#define SIGEV_MASK              0x3f

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#define IS_SIGEV_TYPE_SUPPORTED(notify) ((notify) & SIGEV_MASK || !(notify)) 
#define IS_SIGEV_SIGNAL_TASK(notify) ((notify) & \
        (SIGEV_TASK_SIGNAL | SIGEV_TIMER_TASK_SIGNAL))
#define IS_SIGEV_THREAD(notify) ((notify) & \
        (SIGEV_THREAD | SIGEV_TIMER_THREAD))
#define IS_SIGEV_TIMER(notify) ((notify) & \
        (SIGEV_TIMER_SIGNAL | SIGEV_TIMER_TASK_SIGNAL | SIGEV_TIMER_THREAD))

#endif  /* _POSIX_xxx_SOURCE */

struct sigevent
    {
    int                 sigev_notify; /*  notification type */
    int                 sigev_signo;  /*  signal number */  
    union sigval        sigev_value;  /*  signal value */

    void (* sigev_notify_function)(union sigval); /*  notification function */
    pthread_attr_t *    sigev_notify_attributes;  /*  notification type */

    /* the following are not POSIX defined */

    void *              sigev_notifier_id;        /*  notification task id */
    void *              sigev_id;                 /*  sigevent id */
   };

#ifdef __cplusplus
}
#endif

#endif /* __INCsigeventcommonh */
