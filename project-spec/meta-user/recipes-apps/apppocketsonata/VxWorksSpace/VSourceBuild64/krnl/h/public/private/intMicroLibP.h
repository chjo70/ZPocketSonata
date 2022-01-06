/* intMicroLibP.h - private interrupt micro lock header file */

/* 
 * Copyright (c) 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01e,26may10,pad  Added 'extern C' statement and protection against multiple
		 inclusions of this header file.
01d,28oct09,cww  Update X86_64 include files
01c,02oct09,s_s  added _ASM_LANGUAGE references
01b,17sep09,s_s  moved KERNEL_INT_CPU_LOCK/UNLOCK to kernelLibP.h and added
                 INT_CPU_MICRO_LOCK/UNLOCK definition
01a,14jul09,s_s created 
*/

#ifndef __INCintMicroLibPh
#define __INCintMicroLibPh

#ifndef _ASMLANGUAGE

#include <vxInline.h>

#if     (CPU_FAMILY == ARM)
#include <arch/arm/intArmLib.h>
#endif  /* (CPU_FAMILY == ARM) */

#if     (CPU_FAMILY == I80X86)
#ifndef _WRS_CONFIG_LP64
#include <arch/i86/intI86Lib.h>
#else
#include <arch/i86/x86_64/intX86_64Lib.h>
#endif /* _WRS_CONFIG_LP64 */
#endif  /* (CPU_FAMILY == I80X86) */

#if     (CPU_FAMILY == MIPS)
#include <arch/mips/intMipsLib.h>
#endif /* CPU_FAMILY == MIPS */

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
* INT_CPU_MICRO_LOCK - lock out interrupts on local CPU ("micro version")
*
* This routine disables interrupts on the local CPU on which the task or ISR is 
* running.  The returned value is a lock-out key to be used in a subsequent 
* call to INT_CPU_MICRO_UNLOCK() to release the lock.  Execution of interrupts 
* on other CPUs in the SMP system is not affected by this routine.  Because of 
* this behaviour this routine is not a suitable mutual exclusion mechanism 
* unless all tasks and/or ISRs participating in the mutual exclusion scenario 
* have a single CPU affinity to the very same CPU.
*
* This macro disables interrupts at the master lock-out level on the local
* cpu. This means no interrupt can occur even if unmasked in the IntMask
* bits of the status register.
*
* NOTE: This routine will use _inline_intCpuMicroLock() if available and
* requested.
*
* RETURNS: An architecture-dependent lock-out key for the interrupt level 
* prior to the call.
*
* SEE ALSO: intCpuLock(), intCpuUnlock(), taskCpuLock(), intLockLevelSet()
*
* \NOMANUAL
*
*/

#ifdef _WRS_INLINE_intCpuMicroLock
# define INT_CPU_MICRO_LOCK()         _inline_intCpuMicroLock()
#else
# define INT_CPU_MICRO_LOCK()         intCpuMicroLock()
#endif /* _WRS_INLINE_intCpuMicroLock */

/********************************************************************************
* INT_CPU_MICRO_UNLOCK - cancel local CPU interrupt lock ("micro version")
*
* This routine removes the lock established using INT_CPU_LOCK().  It re-enables
* interrupts on the local CPU on which the  task or ISR is running.  Calling 
* this routine on the uniprocessor version of VxWorks is equivalent to calling 
* intUnlock().  The parameter <lockKey> is an architecture-dependent lock-out 
* key returned by a preceding INT_CPU_LOCK() call.
*
* NOTE: This routine will use  _inline_intCpuMicroLock() if available and 
* requested.
*
* RETURNS: N/A
*
* SEE ALSO: intCpuUnlock(), intCpuLock(), taskCpuUnlock()
*
* \NOMANUAL
*
*/

#ifdef _WRS_INLINE_intCpuMicroUnlock
# define INT_CPU_MICRO_UNLOCK(key)    _inline_intCpuMicroUnlock(key)
#else
# define INT_CPU_MICRO_UNLOCK(key)    intCpuMicroUnlock(key)
#endif /* _WRS_INLINE_intCpuMicroUnlock */

/* prototypes */

extern int intCpuMicroLock (void);
extern void intCpuMicroUnlock (int key);

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE*/

#endif /* __INCintMicroLibPh */
