/* b_pthread_mutex_t.h - base type pthread_mutex_t definition header */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01c,24jul06,jpb  Removed POSIX condition.
01b,31mar06,pad  Minor changes in comments.
01a,18jal06,mil  Updated for POSIX namespace conformance (P2).
                 Created from pthread.h.
*/

#ifndef __INCb_pthread_mutex_th
#define __INCb_pthread_mutex_th

#include <base/b_pthread_mutexattr_t.h>
#include <types/vxWind.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef mutexSemId
#undef mutexValid
#undef mutexInitted
#undef mutexCondRefCount
#undef mutexSavPriority
#undef mutexAttr
#endif  /* _POSIX_xxx_SOURCE */

typedef struct
    {
    _Vx_SEM_ID  mutexSemId;     /* Vx semaphore associated with pthread mutex */
    int         mutexValid;	/* PTHREAD_VALID_OBJ if the mutex is ready
				   to be used */
    int         mutexInitted;   /* PTHREAD_INITIALIZED_OBJ if mutex is
				   initialized */
    int         mutexCondRefCount;
    int         mutexSavPriority;
    pthread_mutexattr_t mutexAttr;
    } pthread_mutex_t;

#ifdef __cplusplus
}
#endif

#endif /* __INCb_pthread_mutex_th */
