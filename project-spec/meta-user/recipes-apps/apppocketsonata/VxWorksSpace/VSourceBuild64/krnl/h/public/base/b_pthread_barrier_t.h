/* b_pthread_barrier_t.h - base type pthread_barrier_t definition header */

/*
 * Copyright (c) 2008, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
19jun12 krz Fixed serialization and integrated.
22aug08 brk created
*/

#ifndef __INCb_pthread_barrier_th
#define __INCb_pthread_barrier_th

#include <types/vxWind.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int pthread_barrierattr_t;

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef serializationGrab
#undef waitingCount
#undef userCount
#undef sessionCount
#undef barrierAttr
#undef barrierMutex
#undef barrierSem

typedef struct
    {
    unsigned serializationGrab; /* Must be aligned for vxAtomic32Cas */
    unsigned waitingCount;
    unsigned userCount;
    unsigned sessionCount;
    pthread_barrierattr_t barrierAttr;
    _Vx_SEM_ID  barrierMutex;
    _Vx_SEM_ID  barrierSem;
    } pthread_barrier_t;

#else

typedef struct
    {
    unsigned serializationGrab; /* Must be aligned for vxAtomic32Cas */
    unsigned waitingCount;
    unsigned userCount;
    unsigned sessionCount;
    pthread_barrierattr_t barrierAttr;
    SEM_ID  barrierMutex;
    SEM_ID  barrierSem;
    } pthread_barrier_t;

#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_pthread_barrier_th */
