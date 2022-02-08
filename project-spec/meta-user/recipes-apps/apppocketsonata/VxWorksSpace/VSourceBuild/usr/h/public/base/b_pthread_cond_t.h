/* b_pthread_cond_t.h - base type pthread_cond_t definition header */

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
01e,24jul06,jpb  Removed POSIX condition.
01d,14apr06,mil  Added condAttr member, removed include of sys/unistd.h.
01c,31mar06,pad  Minor changes in comments.
01b,22mar06,pad  Removed unnecessary condOwner field.
01a,18jal06,mil  Updated for POSIX namespace conformance (P2).
                 Created from pthread.h.
*/

#ifndef __INCb_pthread_cond_th
#define __INCb_pthread_cond_th

#include <types/vxWind.h>
#include <base/b_pthread_condattr_t.h>
#include <base/b_pthread_mutex_t.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef condSemId
#undef condValid
#undef condInitted
#undef condRefCount
#undef condMutex
#undef condAttr
#endif  /* _POSIX_xxx_SOURCE */

typedef struct
    {
    _Vx_SEM_ID  condSemId;      /* Vx sem associated with thread cond var */
    int         condValid;	/* PTHREAD_VALID_OBJ if condition variable is
				   ready to be used */
    int         condInitted;    /* PTHREAD_INITIALIZED_OBJ if condition
				   variable is initialized */
    int         condRefCount;
    pthread_mutex_t *   condMutex;      /* mutex protecting the cond var */
    pthread_condattr_t  condAttr;
    } pthread_cond_t;

#ifdef __cplusplus
}
#endif

#endif /* __INCb_pthread_cond_th */
