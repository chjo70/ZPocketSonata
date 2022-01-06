/* spinlockIsrNdLibP.h - private non-deterministic ISR spinlock header */

/*
 * Copyright (c) 2007-2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */
                                                                             
/*
modification history
--------------------
01b,21oct08,kk   move prototypes to h/spinlockIsrNdLib.h
01a,16jan08,dlk  Written.
*/

#ifndef __INCspinlockIsrNdLibPh
#define __INCspinlockIsrNdLibPh

#include <vxWorks.h>
#include <spinlockIsrNdLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* functions */

/*
 * These function defines are kept here as wrappers for the networking
 * code and should be cleaned up once networking move to using the
 * new spinLockIsrNdXXX() APIs.
 */

#define spinlockIsrNdInit spinLockIsrNdInit
#define spinlockIsrNdTake spinLockIsrNdTake
#define spinlockIsrNdGive spinLockIsrNdGive

#ifdef __cplusplus
}
#endif

#endif /* __INCspinlockIsrNdLibPh */

