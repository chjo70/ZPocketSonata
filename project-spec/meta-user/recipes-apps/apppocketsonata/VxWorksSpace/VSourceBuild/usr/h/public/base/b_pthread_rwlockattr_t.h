/* b_pthread_rwlockattr_t.h - base type pthread_rwlock_t definition header */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
03sep14,sas  Created (US46077).
 */

#ifndef __INCb_pthread_rwlockattr_th
#define __INCb_pthread_rwlockattr_th

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef rwlockAttrStatus
#undef rwlockAttrMaxReaders
#endif  /* _POSIX_xxx_SOURCE */

typedef struct
    {
    int          rwlockAttrStatus;             /* status flag */
    unsigned int rwlockAttrMaxReaders;         /* Maximum number of readers */
    } pthread_rwlockattr_t;

#ifdef __cplusplus
}
#endif

#endif /* __INCb_pthread_rwlockattr_th */
