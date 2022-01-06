/* b_pthread_condattr_t.h - base type pthread_condattr_t definition header */

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
01d,17oct06,pad  Removed conditional blocks related to
                 _POSIX_THREAD_PROCESS_SHARED because this macro requires the
                 inclusion of unistd.h, which is not allowed by POSIX.1
                 (defect #69419 / Fix #69420).
01c,21feb06,pes  Add include to pick up typedef for clockid_t.
01b,09feb06,pad  Added _CondAttrClockId field in pthread_condattr_t
                 structure type.
01a,18jal06,mil  Updated for POSIX namespace conformance (P2).
                 Created from pthread.h.
*/

#ifndef __INCb_pthread_condattr_th
#define __INCb_pthread_condattr_th

/* typedef clockid_t */
#include <base/b_clockid_t.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef condAttrStatus
#undef condAttrPshared
#endif  /* _POSIX_xxx_SOURCE */

typedef struct
    {
    int         condAttrStatus;             /* status flag          */
    clockid_t   _CondAttrClockId;           /* clock ID for timed cond var*/
    } pthread_condattr_t;

#ifdef __cplusplus
}
#endif

#endif /* __INCb_pthread_condattr_th */
