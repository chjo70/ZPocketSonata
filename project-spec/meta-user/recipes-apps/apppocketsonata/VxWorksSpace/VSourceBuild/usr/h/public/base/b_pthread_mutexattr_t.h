/* b_pthread_mutexattr_t.h - base type pthread_mutexattr_t definition header */

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
01b,17oct06,pad  Removed conditional blocks related to
                 _POSIX_THREAD_PROCESS_SHARED because this macro requires the
                 inclusion of unistd.h, which is not allowed by POSIX.1
                 (defect #69419 / Fix #69420).
01a,18jal06,mil  Updated for POSIX namespace conformance (P2).
                 Created from pthread.h.
*/

#ifndef __INCb_pthread_mutexattr_th
#define __INCb_pthread_mutexattr_th

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef mutexAttrStatus
#undef mutexAttrPshared
#undef mutexAttrProtocol
#undef mutexAttrPrioceiling
#undef mutexAttrType
#endif  /* _POSIX_xxx_SOURCE */

typedef struct
    {
    int     mutexAttrStatus;                /* status flag          */
    int     mutexAttrProtocol;              /* inherit or protect   */
    int     mutexAttrPrioceiling;           /* priority ceiling     */
                                            /* (protect only)       */
    int     mutexAttrType;                  /* mutex type           */
    } pthread_mutexattr_t;

#ifdef __cplusplus
}
#endif

#endif /* __INCb_pthread_mutexattr_th */
