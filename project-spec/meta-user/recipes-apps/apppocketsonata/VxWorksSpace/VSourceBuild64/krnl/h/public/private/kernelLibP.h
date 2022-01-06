/* kernelLibP.h - private header file for kernelLib.c */

/*
 * Copyright (c) 1992, 2003, 2005-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
02g,30mar10,pad  Moved declaration of extern C block for C++ after the
                 inclusion of header files. Added _ASMLANGUAGE protection.
02g,11feb10,cww  Updated usrSmpCpuEnableHook param name
02f,03feb10,cww  Fixed usrSmpCpuEnableHook parameter (WIND00190082)
02f,04feb10,d_c  Defect WIND190082: Fix prototype for usrSmpCpuEnableHook().
02e,17sep09,s_s  Added macro KERNEL_INT_CPU_LOCK/UNLOCK
02d,14jul09,s_s  moved KERNEL_INT_CPU_LOCK/UNLOCK definition to intMicroLibP.h
02c,06jun09,kk   added intLibP.h to pick up intCpuMicroLock
02b,04jun09,s_s  added macro definition for intCpuMicroLock()/Unlock()
02c,20feb09,pcs  Updated to add support for the LP64 data model.
02b,11feb09,zl   removed qLib.h inclusion
02a,27aug08,jpb  Renamed VSB header file
01z,08jul08,gls  added warning about inclusion in semLibInline.h
01y,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01x,17jun08,zl   added code barriers for UP kernel state macros.
01w,29apr08,zl   removal of SMP_Q_NODE, phase 2.
01v,19mar08,zl   removal of SMP_Q_NODE, phase 1.
01u,11mar08,to   include taskLibP.h first to use taskIdCurrent for UP
01t,12feb08,zl   moved ready queue macros to windReadyQClassP.h
01s,05sep07,jmg  Added vxcpuEnableTimeout, kernelCpuEnableInternal() and
                 usrSmpCpuEnableHook().
01r,31aug07,kk   added _WRS_KERNEL_IS_TASKING()
01q,06mar07,lei  added SMP_Q_NODE; updated PENDQ_NODE_PTR, READYQ_NODE_PTR and
                 NODE_PTR_TO_TCB.
01p,20feb07,lei  added PENDQ_NODE_PTR(), READYQ_NODE_PTR(), READYQ_NODE_TO_TCB
                 and PENDQ_NODE_TO_TCB(); renamed SCHEDULER_[ADD REMOVE] to
                 SCHEDULER_[ADD REMOVE]_ALL; removed smpchedulerAdd/Remove/Order.
01o,06dec06,jln  change KERNEL_ENTERED_ME() to use in task context
01n,29nov06,cjj  modified KERNEL_ENTERED_ME() for SMP
01m,15nov06,mmi  switched to kernelLock API's
01l,08nov06,lei  added kernelIdleTaskActivate()
01k,26sep06,pcs  Add macro KERNEL_ENTERED_ME
01j,30aug06,lei  added _WRS_ARCH_HAS_NEW_KERNEL_LOCK
01i,07aug06,pcs  Modify macro KERNEL_LOCK to reflect introduction of OBJ
                 locking/unlocking support.
01h,20jul06,lei  SMP clean up: renamed local and global ready queue;
                 removed the parameter for windExit
01g,17jul06,zl   use _WRS_CPU_INDEX_GET() for CPU index.
01f,11aug05,dbt  Added KERNEL_CONTEXT(), KERNEL_ENTER(), KERNEL_EXIT() macros.
01e,25may05,md   added SMP support
01d,04feb05,pch  SPR 102772: add usrKernelIntStkSizeAdj()
01c,07apr03,to   removed activeQHead.
01b,22sep92,rrr  added support for c++
01a,04jul92,jcf  created.
*/

#ifndef __INCkernelLibPh
#define __INCkernelLibPh

#include <vsbConfig.h>
#include <private/taskLibP.h>
#include <kernelLib.h>
#include <intLib.h>
#include <taskLib.h>
#include <vxLib.h>
#include <vxAtomicLib.h>
#include <private/windLibP.h>
#include <private/intMicroLibP.h>  

#ifdef _WRS_CONFIG_SMP
#include <private/kernelLockLibP.h>
#endif /* _WRS_CONFIG_SMP */
    
    /*
     *  ***** WARNING *****
     *
     * This private header file is included by the public header file(s):
     *   - h/inline/semLibInline.h 
     *
     * Ensure that no usage of a VSB source configuration macro is made 
     * by any structure or macro in this file that is also used(directly or 
     * indirectly) by the above list of public header files.
     */

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

/* variable declarations */

extern BOOL	roundRobinOn;		/* state of round robin scheduling */
extern ULONG	roundRobinSlice;	/* round robin task slice in ticks */
extern TASK_ID	rootTaskId;		/* root task id */
extern char *	pRootMemStart;		/* bottom of root task's memory */
extern size_t   rootMemNBytes;		/* actual root task memory size */
extern Q_HEAD	tickQHead;		/* queue for timeouts/delays/wdogs */

#ifdef	_WRS_CONFIG_SMP
extern int vxCpuEnableTimeout;		/* timeout for enabling CPUs */
#else /* _WRS_CONFIG_SMP */
extern BOOL	kernelIsIdle;		/* boolean reflecting idle state */
extern BOOL	kernelState;		/* mutex to enter kernel state */
#endif /* _WRS_CONFIG_SMP */


/* prototypes */
#ifdef _WRS_CONFIG_SMP
extern STATUS   kernelCpuEnableInternal (unsigned int cpuToEnable);
extern STATUS   usrSmpCpuEnableHook (UINT logicalCpuIndex);
#endif

extern void usrKernelIntStkSizeAdj(unsigned *, unsigned *, unsigned *,
				   unsigned *);
					/* stack calculation configlette */

extern void kernelIdleTaskActivate (void);

/*
 * Macro for determining whether the kernel is ready for tasking.
 * For SMP, bootstrap processor is always 0, hence, passing 0 as the
 * cpuid to get taskIdCurrent. For UP, simply access taskIdCurrent.
 */

#define _WRS_KERNEL_IS_TASKING() \
    (_WRS_KERNEL_CPU_GLOBAL_GET(0, taskIdCurrent) == NULL ? FALSE : TRUE)

/* macros for entering and exiting the kernel */

#ifdef	_WRS_CONFIG_SMP

# define KERNEL_ENTER()	        (KERNEL_LOCK_TAKE ())
# define KERNEL_EXIT()		( windExit () )

# define KERNEL_LOCK()
# define KERNEL_UNLOCK()        ( KERNEL_EXIT() )

# define KERNEL_ENTERED_ME()	(KERNEL_LOCK_OWNED_BY_ME())

#else /* _WRS_CONFIG_SMP */

# define KERNEL_LOCK()							\
    do									\
	{								\
	VX_CODE_BARRIER();						\
	kernelState = TRUE;						\
	VX_CODE_BARRIER();						\
	} while ((0))

# define KERNEL_UNLOCK()	windExit ()

# define KERNEL_ENTER()		KERNEL_LOCK()
# define KERNEL_EXIT()		windExit ()

# define KERNEL_ENTERED_ME()	(kernelState == TRUE)
# define KERNEL_ENTERED()	(KERNEL_ENTERED_ME())

#endif /* _WRS_CONFIG_SMP */


/*
 * macros translating queue node pointers to/from TCB pointers. Note that
 * starting with the 6.7 release these are the same for UP and SMP builds.
 */

#define PENDQ_NODE_PTR(pTcb)   (&pTcb->qNode)

#define NODE_PTR_TO_TCB(pNode)  \
          (WIND_TCB *) ((long) (pNode) - OFFSET (WIND_TCB, qNode))


#define KERNEL_INT_CPU_LOCK()           INT_CPU_MICRO_LOCK()
#define KERNEL_INT_CPU_UNLOCK(key)      INT_CPU_MICRO_UNLOCK(key)


#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */

#endif /* __INCkernelLibPh */
