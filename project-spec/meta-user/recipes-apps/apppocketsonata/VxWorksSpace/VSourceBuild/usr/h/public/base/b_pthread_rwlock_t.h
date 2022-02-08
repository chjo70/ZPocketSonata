/* b_pthread_rwlock_t.h - base type pthread_rwlock_t definition header */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
16jan15,pad  Fixed POSIX conformance issue (V7COR-2352).
03sep14,sas  Created (US46077).
 */

#ifndef __INCb_pthread_rwlock_th
#define __INCb_pthread_rwlock_th

#include <base/b_pthread_rwlockattr_t.h>
#include <types/vxWind.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef rwlockSemId
#undef rwlockReadersRefCount
#undef rwlockValid
#undef rwlockInitted
#undef rwlockAttr
#endif  /* _POSIX_xxx_SOURCE */

typedef struct
    {
    _Vx_SEM_ID rwlockSemId;    /* Vx semaphore associated with pthread rwlock */
    int rwlockReadersRefCount; /* Reference count of number of readers
                                  currently using the lock*/
    int rwlockValid;	       /* PTHREAD_VALID_OBJ if the rwlock is ready to
                                  be used */
    int rwlockInitted;         /* PTHREAD_INITIALIZED_OBJ if rwlock is
                                  initialized */
    pthread_rwlockattr_t rwlockAttr; /* rwlock object's attributes */
    } pthread_rwlock_t;

#ifdef __cplusplus
}
#endif

#endif /* __INCb_pthread_rwlock_th */
