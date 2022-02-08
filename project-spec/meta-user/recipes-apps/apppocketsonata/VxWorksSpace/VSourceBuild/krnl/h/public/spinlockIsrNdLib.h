/* spinlockIsrNdLib.h - non-deterministic ISR spinlock library header */

/*
 * Copyright (c) 2007-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */
                                                                             
/*
modification history
--------------------
01g,28apr10,cww  LP64 adaptation
01f,30oct09,gls  modified build warning when ND spinlocks used when 
                 DETERMINISTIC VSB used (WIND00188965)
01e,24jul09,kk   add warning on the use of ND spinlocks
01d,07nov08,kk   added SPIN_LOCK_ISR_ND_DECL() macro
01c,21oct08,kk   added spinLockIsrNdXXX() prototypes
01b,16jan08,dlk  Renamve as spinlockIsrNdLib.h. Move function
                 prototypes to private/spinlockIsrNdLibP.h for now.
01a,05dec07,dlk  Written
*/

#ifndef __INCspinlockIsrNdLibh
#define __INCspinlockIsrNdLibh

#include <vxWorks.h>
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* types */

typedef struct spinlockIsrNd_s
    {
    atomic32_t flag;
    } spinlockIsrNd_t;

/* macros */

#define SPIN_LOCK_ISR_ND_DECL(lock) \
	spinlockIsrNd_t lock = {0}

/* function prototypes */

#ifdef _WRS_CONFIG_DETERMINISTIC
extern void spinLockIsrNdInit (spinlockIsrNd_t * spin)
	_WRS_USAGE_WARNING("since system has been configured for " \
			   "determinism: VSB option DETERMINISTIC = 'y'");
extern int spinLockIsrNdTake (spinlockIsrNd_t * spin) 
	_WRS_USAGE_WARNING("since system has been configured for " \
			   "determinism: VSB option DETERMINISTIC = 'y'");
extern void spinLockIsrNdGive (spinlockIsrNd_t * spin, int key)
	_WRS_USAGE_WARNING("since system has been configured for " \
			   "determinism: VSB option DETERMINISTIC = 'y'");
#else
extern void spinLockIsrNdInit	(spinlockIsrNd_t * spin);
extern int spinLockIsrNdTake	(spinlockIsrNd_t * spin); 
extern void spinLockIsrNdGive	(spinlockIsrNd_t * spin, int key);
#endif /* _WRS_CONFIG_DETERMINISTIC */

#ifdef __cplusplus
}
#endif

#endif /* __INCspinlockIsrNdLibh */
