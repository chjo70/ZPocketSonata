/* spinLockLibP.h - WRS-private spinlock definitions */

/*
 * Copyright (c) 2007-2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind RIver License agreement.
 */

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Caution:  The definitions in this file are to be used only within   *
 * the VxWorks kernel, and only under carefully-controlled conditions. *
 * Improper usage increases the risk of livelocks.                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
                                                                             
/*
modification history
--------------------
01p,15feb12,cww  Added spinLockDbgDisable (WIND00332462)
01o,29apr10,pad  Moved extern C statement after include statements.
01n,21sep09,s_s  changed INT_CPU_LOCK() and INT_CPU_UNLOCK() to
                 KERNEL_INT_CPU_LOCK() and KERNEL_INT_CPU_UNLOCK()
		 (WIND00181479)
01m,27aug08,jpb  Renamed VSB header file
01l,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01k,09jul07,gls  split SPIN_LOCK_CPU_RESTRICT() into task and ISR versions
01j,01jul07,gls  added include of intLib.h and vxCpuLib.h for SMP
01i,11jun07,gls  added SPIN_LOCK_CPU_RESTRICT()
                 added _wrs_spinLockRestrict()
01h,29may07,pch  strengthen warning about use of lock levels
01g,14may07,mmi  move rtSpinLockLib defintions to rtSpinLockLibP.h
01f,11may07,mmi  included required header file for data type referenced in this
		 file
01e,18apr07,rfr  Added Realtime Spinlock inline functions
01d 08mar07,mmi  move SPIN_LOCK_TRACE to spinLockLib.h
01c,05mar07,pch  add spinLockIsrHeld()
01b,01mar07,mmi  add SPIN_LOCK_TRACE and SPIN_LOCK_IS_HELD()
01a,15feb07,pch  written
*/

#ifndef __INCspinLockLibPh
#define __INCspinLockLibPh


#include <vsbConfig.h>
#include <spinLockLib.h>
#include <private/windLibP.h>
#include <private/kernelLibP.h>

#ifdef _WRS_CONFIG_SMP
#include <intLib.h>
#include <vxCpuLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Lock levels are meaningful only in conjunction with the debug version
 * of the spinlock library, since the optimized version does not check
 * for usage violations.
 *
 * Locks with non-zero levels are used during error handling and reboot,
 * when it would be counterproductive to check for improper spinlock usage
 * (e.g. it would not be helpful to re-initiate a reboot sequence upon
 * detecting an error in the reboot sequence).
 *
 * Uncontrolled use of non-zero lock levels will impair the diagnostic
 * capabilities of the spinlock debug facilities, increasing the risk of
 * livelocks arising in deployed systems.  Usage of the following option in
 * WR code must be approved by the Architect of the associated Technology
 * Group (TG).
 */

#define	_WRS_PRIVATE_LOCK_LEVEL_1	1	/* internal use only */

/* determine if a spinLock is held. Macro is used by SPIN_LOCK_IS_HELD only */

#define SPIN_LOCK_READ_WINVAR  ((_WRS_KERNEL_GLOBAL_ACCESS(spinLockIsrCnt))| \
			        (_WRS_KERNEL_GLOBAL_ACCESS(spinLockTaskCnt)))

/* 
 * Return TRUE if any spinLock is held in the context of the running CPU.
 */

#define SPIN_LOCK_IS_HELD()    (SPIN_LOCK_READ_WINVAR == 0 ? FALSE : TRUE)

#ifdef _WRS_CONFIG_SMP

/* 
 * Return ERROR if spinlock is held in the context of the specified CPU.
 * Note that interrupts must be disabled to prevent task migration. 
 *
 * SPIN_LOCK_TASK_CPU_RESTRICT() verifies that no task level or ISR level 
 * spin locks are held.  It is to be called from task level.
 *
 * SPIN_LOCK_ISR_CPU_RESTRICT() verifies only that no ISR level spin locks
 * are held.  It is to be called from ISR level.
 */

#define SPIN_LOCK_TASK_CPU_RESTRICT(cpuid) \
                 ((_WRS_KERNEL_CPU_GLOBAL_GET(cpuid, spinLockTaskCnt) |      \
		   _WRS_KERNEL_CPU_GLOBAL_GET(cpuid, spinLockIsrCnt)) != 0 ? \
                  ERROR : OK)

#define SPIN_LOCK_ISR_CPU_RESTRICT(cpuid) \
                 ((_WRS_KERNEL_CPU_GLOBAL_GET(cpuid, spinLockIsrCnt)) != 0 ? \
                  ERROR : OK)

#define _WRS_SPIN_LOCK_RESTRICT() _wrs_spinLockRestrict()

/*******************************************************************************
*
* _wrs_spinLockRestrict - return ERROR if a spinlock is held by the current CPU
*
* This routine returns ERROR and sets errno if a spinlock is currently held by
* the calling CPU.  This routine returns OK if no spinlock is held by the
* calling CPU.
*
* Note, this routine must verify that no task level or ISR level spin locks
* are held when called at task level, and only that no ISR level spin locks are
* held when called at ISR level.  Because it is a programming error to attempt
* to take a task level spin lock at ISR level this is not checked here.
*
* INTERNAL 
* This routine is designated __inline__, meaning its code will be replicated
* for each use.
*
* RETURNS: ERROR if a spinLock is held by the calling CPU, else OK
*
* ERRNO:
* \is
* \i S_spinLockLib_NOT_SPIN_LOCK_CALLABLE
* Spin lock is held by the calling CPU
* \ie
*
* SEE ALSO: SPIN_LOCK_RESTRICT
*
* \NOMANUAL
*/

_WRS_INLINE STATUS _wrs_spinLockRestrict (void)
    {
    int  key;             /* local copy of interrupts key */
    int  cpuid;           /* CPU identifier */
    STATUS status = OK;   /* return value */

    /* lock interrupts to atomically access the spinlock data structure */

    key = KERNEL_INT_CPU_LOCK ();

    cpuid = _WRS_CPU_INDEX_GET ();

    /* 
     * Check if the current CPU holds a lock.
     *
     * If in interrupt context (ie, intCnt is greater than zero) then
     * return error if the ISR spin lock count is greater than zero.  It is
     * worth noting that if a task holds a task level spin lock an ISR could
     * run, and should not be spin lock restricted based on that task level
     * spin lock.
     *
     * If at task level check for task level spin locks and ISR level
     * spin locks.
     */

    if (_WRS_KERNEL_CPU_GLOBAL_GET (cpuid, intCnt) != 0)
	{
	if (_WRS_KERNEL_GLOBAL_ACCESS(spinLockIsrCnt) != 0)
	    {
	    _WRS_KERNEL_CPU_GLOBAL_SET (cpuid, errno, 
                                        S_spinLockLib_NOT_SPIN_LOCK_CALLABLE);

	    status = ERROR;
	    }
        }
    else if ((_WRS_KERNEL_GLOBAL_ACCESS(spinLockTaskCnt) |
	      _WRS_KERNEL_GLOBAL_ACCESS(spinLockIsrCnt)) != 0)
        {
	WIND_TCB * tCurrent = 
	    _WRS_KERNEL_CPU_GLOBAL_GET (cpuid, taskIdCurrent);

	tCurrent->errorStatus = S_spinLockLib_NOT_SPIN_LOCK_CALLABLE;

        status = ERROR;
        }

    KERNEL_INT_CPU_UNLOCK (key);

    return (status);
    }

extern void spinLockDbgDisable (void);
#endif /* _WRS_CONFIG_SMP */

/*
 * Testing whether a particular lock is held does not, in itself,
 * create a risk of livelock, however algorithms which need to do
 * so are suspect because spinlocks should ordinarily be held for
 * short and deterministic periods.  Observing this policy should
 * result in lock usage patterns which are established when the
 * code is designed and need not be tested at runtime.  The most
 * likely legitimate exception is a fault handler, which might get
 * invoked at arbitrary times.
 */

IMPORT BOOL spinLockIsrHeld(spinlockIsr_t *pLock);

#ifdef __cplusplus
}
#endif

#endif /* __INCspinLockLibPh */
