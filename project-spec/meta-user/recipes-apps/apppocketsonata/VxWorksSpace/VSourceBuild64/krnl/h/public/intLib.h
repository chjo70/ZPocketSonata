/* intLib.h - interrupt library header file */

/*
 * Copyright (c) 1990-2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02p,29apr10,pad  Moved extern C statement after include statements.
02o,19jun09,mze  replacing PAD64
02n,05mar09,cww  LP64 update
02m,20jan09,jb   Adding 64-bit support
02l,19jun07,zl   updated inlined build configuration for INT_CPU_LOCK and
                 INT_CPU_UNLOCK.
02k,19apr07,jmg  Moved intCnt to intLibP.h
02j,11apr07,jmg  Renamed _WRS_INT_LOCK()/_WRS_INT_UNLOCK() to
                 INT_CPU_LOCK()/INT_CPU_UNLOCK() and Enabled the 
                 __inlineIntLock()/__inLineUnlock() for archs that suport 
                 inLineIntLocks in SMP builds.
02i,17nov06,elp  fixed intCpuUnlock prototype.
02h,17jul06,zl   redefined INT_RESTRICT() and INT_CONTEXT() for public use.
02g,08may06,lei  added intCntTable[] for SMP
02f,12feb06,kk   fix prototype of intUnlock (SPR# 99116)
02f,25may05,md   Added SMP support
02e,04oct04,mdo  Documentation fixes for apigen
02d,22aug03,to   added _WRS_INT_LOCK()/_WRS_INT_UNLOCK() macros.
		         	deleted K&R style prototypes.
02c,07may03,pes  PAL conditional compilation cleanup. Phase 2.
02b,29aug01,hdn  included arch/i86/intI86Lib.h for arch specific stuff
02a,14dec00,pai  added intEnable and intDisable for all T2 arches (SPR #63046).
                 AM29XXX, SIMSPARCSUNOS, and TRON are explicitly excluded. 
01z,11sep00,hk   changed to include intShLib.h for Hitachi SH architecture.
01y,01sep00,hk   added intVBRSet() and _func_intConnectHook prototype for SH.
01x,03jun98,hdn  added intHandlerCreateX86() prototype.
01w,25nov97,cdp  moved ARM-specific things to arch/arm/intArmLib.h.
01v,28oct97,kkk  added INT_NON_PREEMPT_MODEL macro.
01u,19aug97,cdp  added intLibInit, INT_PREEMPT_MODEL and INT_HDWE_LOCK_LVL.
01t,27feb97,cdp  added intEnable and intDisable for ARM.
01s,13dec96,tpr  added #if/#endif arround intEnable() & intDisable() prototypes.
01r,09dec96,tpr  added intEnable() & intDisable() prototypes.
01q,29nov96,kkk  added prototypes for MIPS routines in the __STDC__ section.
		 took out intEnable & intDisable. (conflicts with PPC).
01p,25nov96,kkk  added prototypes for MIPS interrupt routines.
01o,15jun95,ms	 added intRegsLock, intRegsUnlock prototypes
01n,02dec93,tpr	 removed am29200Intr3Connect() and am29200Intr3Drv().
	    tpr  added am29200Intr3DeMuxConnect().
	    tpr  added am29200Intr3Connect() and am29200Intr3Drv() for am29200.
	    pad  added am29k family support.
01m,15oct92,jwt  added intVecTableWriteEnable() prototype for SPARC.
01l,22sep92,rrr  added support for c++
01k,27jul92,rdc  added S_intLib_VEC_TABLE_WP_UNAVAILABLE and
		 intVecTableWriteProtect ().
01j,04jul92,jcf  cleaned up.
01i,26may92,rrr  the tree shuffle
01h,10jan92,jwt  added intAckConfig(), intTBRSet() prototypes for SPARC.
01g,04oct91,rrr  passed through the ansification filter
		  -changed VOID to void
		  -changed copyright notice
01f,08apr91,jdi  added NOMANUAL to prevent mangen.
01e,23oct90,shl  fixed misspelling in intUnlock().
		 changed intConnect() to take a VOIDFUNCPTR.
01d,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01c,10aug90,dnw  added declaration of intVecSet().
01b,15jul90,dnw  added INT_CONTEXT()
01a,11apr90,jcf  written.
*/

#ifndef __INCintLibh
#define __INCintLibh

#include <vxWorks.h>
#include <vwModNum.h>
#include <regs.h>
#include <vxInline.h>

#if	(CPU_FAMILY == ARM)
#include <arch/arm/intArmLib.h>
#endif	/* (CPU_FAMILY == ARM) */

#if	(CPU_FAMILY == I80X86)
#ifndef _WRS_CONFIG_LP64
#include <arch/i86/intI86Lib.h>
#else
#include <arch/i86/x86_64/intX86_64Lib.h>
#endif  /* LP64 */
#endif	/* (CPU_FAMILY == I80X86) */

#if	(CPU_FAMILY == MIPS)
#include <arch/mips/intMipsLib.h>
#endif /* CPU_FAMILY == MIPS */

#if	(CPU_FAMILY == SH)
#include <arch/sh/intShLib.h>
#endif	/* (CPU_FAMILY == SH) */


#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

#define S_intLib_NOT_ISR_CALLABLE		(M_intLib | 1)
#define S_intLib_VEC_TABLE_WP_UNAVAILABLE	(M_intLib | 2)

#ifndef _ASMLANGUAGE

/* variable declarations */

/*******************************************************************************
*
* INT_CONTEXT - restrict access of a routine from interrupt use
*
* RETURNS: TRUE if called from interrupt level, or FALSE if called from task
*          level.
*
* \NOMANUAL
*/

#define INT_CONTEXT()							\
    (									\
    intContext()							\
    )

/*******************************************************************************
*
* INT_RESTRICT - restrict access of a routine from interrupt use
*
* RETURNS: OK if called from task level, or ERROR if called from interrupt
*          level.
*
* \NOMANUAL
*/

#define INT_RESTRICT()							\
    (									\
    /* to avoid extra function call, use intContext() */		\
									\
    intContext() ? errno = S_intLib_NOT_ISR_CALLABLE, ERROR : OK	\
    )

/*******************************************************************************
*
* INT_CPU_LOCK - lock out interrupts on local CPU
*
* This routine disables interrupts on the CPU the calling task or ISR is 
* running on.  The returned value is a lock-out key to be used in a subsequent 
* call to IT_CPU_UNLOCK() to release the lock.  Execution of interrupts on 
* other CPUs in the SMP system is not affected by this routine.  Because of 
* this behaviour this routine is not a suitable mutual exclusion mechanism 
* unless all tasks and/or ISRs participating in the mutual exclusion scenario 
* have a single CPU affinity to the very same CPU.
*
* NOTE: This routine will use  inline intLock() if available and requested.
*
* RETURNS: An architecture-dependent lock-out key for the interrupt level
* prior to the call.
*
* SEE ALSO: intCpuLock(), intCpuUnlock(), taskCpuLock(), intLockLevelSet()
* 
* \NOMANUAL
*/

#ifdef _WRS_INLINE_intCpuLock
# define INT_CPU_LOCK()		_inline_intCpuLock()
#else
# define INT_CPU_LOCK()		intCpuLock()
#endif /* _WRS_INLINE_intCpuLock */

/*******************************************************************************
*
* INT_CPU_UNLOCK - cancel local CPU interrupt lock
*
* This routine removes the lock established using INT_CPU_LOCK().  It re-enables
* interrupts on the CPU the calling task or ISR is running on.  Calling this
* routine on the uniprocessor version of VxWorks is equivalent to calling 
* intUnlock().  The parameter <lockKey> is an architecture-dependent lock-out 
* key returned by a preceding INT_CPU_LOCK() call.
*
* NOTE: This routine will use  inline intLock() if available and requested.
* 
* RETURNS: N/A
*
* SEE ALSO: intCpuUnlock(), intCpuLock(), taskCpuUnlock()
* 
* \NOMANUAL
*/

#ifdef _WRS_INLINE_intCpuUnlock
# define INT_CPU_UNLOCK(key)	_inline_intCpuUnlock(key)
#else
# define INT_CPU_UNLOCK(key)	intCpuUnlock(key)
#endif /* _WRS_INLINE_intCpuUnlock */

/* function declarations */

extern STATUS 	intConnect (VOIDFUNCPTR * vector, VOIDFUNCPTR routine,
		            _Vx_usr_arg_t parameter);
extern STATUS   intDisconnect (VOIDFUNCPTR * vector, VOIDFUNCPTR routine,
			    _Vx_usr_arg_t parameter);
extern FUNCPTR 	intHandlerCreate (FUNCPTR routine, int parameter);
extern void 	intLockLevelSet (int newLevel);
extern int 	intLockLevelGet (void);
extern BOOL 	intContext (void);
extern int 	intCount (void);
extern void 	intVecBaseSet (FUNCPTR *baseAddr);
extern FUNCPTR *intVecBaseGet (void);
extern void 	intVecSet (FUNCPTR *vector, FUNCPTR function);
extern FUNCPTR 	intVecGet (FUNCPTR *vector);
extern int 	intLevelSet (int level);
extern int 	intLock (void);
extern void 	intUnlock (int oldSR);
extern int 	intRegsLock (REG_SET *pRegs);
extern void 	intRegsUnlock (REG_SET *pRegs, int lockKey);
extern STATUS   intVecTableWriteProtect (void);
extern int 	intCpuLock (void);
extern void 	intCpuUnlock (int key);
extern int	intDisable (int);
extern int	intEnable (int);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCintLibh */
