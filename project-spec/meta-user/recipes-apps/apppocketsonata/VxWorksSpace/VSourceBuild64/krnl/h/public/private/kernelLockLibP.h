/* kernelLockLibP.h - kernel lock library definitions header */

/*
 * Copyright (c) 2006-2008, 2010, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * License agreement.
 */
                                                                             
/*
modification history
--------------------
26jan15,h_k  added INTLOCKED_KERNEL_STATE VSB option. (US41383)
13aug10,cww  Use dynamically generated offsets in offset macros
17may10,cww  LP64 adaptation
17sep08,gls  added _WRS_KERNEL_LOCK_OFFSET_ assembly offsets 
             (Defect #1240649)
03sep07,mmi  Turn-off KERNEL_LOCK_TRACE
18apr07,mmi  add KERNEL_LOCK_TRACE to kernelLockTry
01mar07,v_r  Added kernelLockOwnerGet() prototype API for req
             CQ:WIND00088695).
04dec06,pes  Implement kernel lock tracing facility.
01nov06,mmi  written
*/

#ifndef __INCkernelLockLibPh
#define __INCkernelLockLibPh

/* 
 * Abstract the underline API to dynamically expand the appropriate code if
 * debugging is enabled for kernellock libraries. 
 */

/*
 * The following definition can be uncommented to add useful debugging
 * information to the kernel lock data structure. Currently, this
 * information includes the file and line number from which the kernelLockTake
 * was invoked.
 *
 * Three caveats:
 * 1. Use of this facility requires support at the architecture level in
 * assembly code, specifically where kernelLockTake is invoked in intExitIdle
 * and saveIntContext.
 *
 * 2. This facility can be enabled by either uncommenting the macro below
 * or by defining it (i.e., add ADDED_CFLAGS+=-DKERNEL_LOCK_TRACE) on the
 * command line when building the kernel libraries. If the facility is
 * enabled by uncommenting the define below, it is required that
 * kernelLockLibP.h is included in the architecture-specific assembly
 * language module implied by 1) above.
 *
 * 3. It is assumed that C code never invokes kernelLockTake directly. Use
 * of the macros below ensures that kernelLockTake will be called with
 * the correct parameters.
 */
   
/* Replace the "0" with 1 to enable KERNEL_LOCK_TRACE */

#if 0
#define KERNEL_LOCK_TRACE
#endif

#include <vxWorks.h>

/*
 * _WRS_KERNEL_LOCK_VAR_ALIGN must be defined to a minimum size that is equal
 * to or larger than the largest cache line size of an architecture.  Because
 * of this we can use it to set the alignment for the tkt_ctr member of the
 * kernel lock structure.
 */

#define _WRS_KERNEL_LOCK_ALIGN_tkt_ctr    (_WRS_KERNEL_LOCK_VAR_ALIGN)

#ifdef _ASMLANGUAGE
/*
 * offset macros need to be in an ASM section due to a circular dependency
 * when compiling offsets.c
 *
 * WARNING: the old offset macros are provided temporarily only for a
 * transitionary phase.  They will be removed once existing references are
 * updated to use the dynamically generated offsets.
 */

#ifndef _WRS_CONFIG_LP64
#include <private/offsetMacrosP.h>

#define _WRS_KERNEL_LOCK_OFFSET_svc_ctr   VX_KERNEL_LOCK_svc_ctr_OFFSET
#define _WRS_KERNEL_LOCK_OFFSET_cpuIndex  VX_KERNEL_LOCK_cpuIndex_OFFSET
#endif /* _WRS_CONFIG_LP64 */

#else  /* _ASMLANGUAGE */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef KERNEL_LOCK_TRACE

#define KERNEL_LOCK_TAKE()		(kernelLockTake (__FILE__, __LINE__))
#define KERNEL_LOCK_TRY()		(kernelLockTry (__FILE__, __LINE__))

#else /* KERNEL_LOCK_TAKE */

#define KERNEL_LOCK_TAKE()		(kernelLockTake ())
#define KERNEL_LOCK_TRY()		(kernelLockTry ())

#endif /* KERNEL_LOCK_TAKE */


#define KERNEL_LOCK_GIVE()		(kernelLockGive ())
#define KERNEL_LOCK_OWNED_BY_ME()	(kernelLockOwnedByMe ())
#define KERNEL_LOCK_OWNER_GET()		(kernelLockOwnerGet ())

/* ISR calleable spinLocks functions */

#ifdef KERNEL_LOCK_TRACE
extern void	    kernelLockTake	(char * file, int line);
extern BOOL	    kernelLockTry	(char * file, int line);
#else
extern BOOL	    kernelLockTry	(void);
extern void	    kernelLockTake	(void);
#endif /* KERNEL_LOCK_TRACE */
extern void	    kernelLockGive	(void);
extern BOOL	    kernelLockOwnedByMe	(void);
extern unsigned int kernelLockOwnerGet	(void);
extern void	    kernelLockInit	(void);

#ifdef	_WRS_CONFIG_INTLOCKED_KERNEL_STATE
extern int	    kernelLockIntStateGet (void);
extern void	    kernelLockIntStateSet (int intState);
#endif	/* _WRS_CONFIG_INTLOCKED_KERNEL_STATE */

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */

#endif /* __INCkernelLockLibPh */
