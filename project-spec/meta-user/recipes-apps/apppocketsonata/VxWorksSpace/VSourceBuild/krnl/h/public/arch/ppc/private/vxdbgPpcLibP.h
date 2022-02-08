/* vxdbgPpcLibP.h - private PPC VxWorks debug library (VxDBG) header file */

/*
 * Copyright (c) 2007-2008, 2010-2011, 2014-2015 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
25feb15,f_l  Updated alignment constraint for ppc64
29sep14,jmp  Added VXDBG_CPU_REG_SET.
01g,09feb11,rlp  Defined VXDBG_INT_LOCK_LEVEL_COMPUTE macro for both UP and
                 SMP (CQ:WIND00253870).
01f,29apr10,pad  Moved extern C statement after include statements.
01e,27aug08,jpb  Renamed VSB header file
01d,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01c,26oct07,rlp  Added the VXDBG_INT_LOCK_LEVEL_COMPUTE macro (CQ:WIND00109321).
01b,11oct07,rlp  Added the VXDBG_INT_REGS_IS_LOCKED macro (CQ:WIND00107725).
01a,01jun07,jmp  Written
*/

#ifndef __INCvxdbgPpcLibPh
#define __INCvxdbgPpcLibPh

	
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE
typedef struct                  /* VxDBG register set */
    {
    REG_SET                     vxRegs;
    } VXDBG_CPU_REG_SET;
#endif /* _ASMLANGUAGE */

/*
 * This macro returns the <level> parameter modified with the interrupt lock
 * level defined into the <value> parameter. The <level> parameter must be
 * previously get with either intCpuLock() or intRegsLock() API.
 *
 * We have to define a dummy VXDBG_INT_LOCK_LEVEL_COMPUTE macro since
 * _PPC_MSR_EE is not defined when we build the VxDBG code with CPU==PPC32.
 */

#ifdef	_PPC_MSR_EE
#ifdef	_PPC_MSR_CE
#define	VXDBG_INT_LOCK_LEVEL_COMPUTE(level, value) \
		((level & ~(_PPC_MSR_EE | _PPC_MSR_CE)) | \
			(value & (_PPC_MSR_EE | _PPC_MSR_CE)))
#else	/* _PPC_MSR_CE */
#define	VXDBG_INT_LOCK_LEVEL_COMPUTE(level, value) \
		((level & ~_PPC_MSR_EE) | (value & _PPC_MSR_EE))
#endif	/* _PPC_MSR_CE */
#else	/* _PPC_MSR_EE */
#define	VXDBG_INT_LOCK_LEVEL_COMPUTE(level, value)	(level)
#endif	/* _PPC_MSR_EE */

#ifdef	_WRS_CONFIG_SMP

/*
 * return TRUE if interrupts are locked in specified register set.
 *
 * We have to define a dummy VXDBG_INT_REGS_IS_LOCKED macro since _PPC_MSR_EE
 * is not defined when we build the VxDBG code with CPU==PPC32.
 */

#ifdef	_PPC_MSR_EE
#define	VXDBG_INT_REGS_IS_LOCKED(pRegs)	(((pRegs->msr & _PPC_MSR_EE) == \
		_PPC_MSR_EE) ? FALSE : TRUE)
#else	/* _PPC_MSR_EE */
#define	VXDBG_INT_REGS_IS_LOCKED(pRegs)	(FALSE)
#endif	/* _PPC_MSR_EE */

/*
 * _WRS_VXDBG_CPU_CTRL_VARS_ALIGN sets the alignment constraint for
 * vxdbgCpuCtrlVars array.
 * The value must be:
 *   a power of two no smaller than sizeof(vxdbgCpuCtrlVars), and
 *   a multiple of the cache line size on every PPC variant that supports SMP.
 */
#ifdef  _WRS_CONFIG_LP64
#define _WRS_VXDBG_CPU_CTRL_VARS_ALIGN          512
#define _WRS_VXDBG_CPU_CTRL_VARS_ALIGN_SHIFT    9
#else
#define _WRS_VXDBG_CPU_CTRL_VARS_ALIGN          256
#define _WRS_VXDBG_CPU_CTRL_VARS_ALIGN_SHIFT    8
#endif

#ifdef _CPU_CACHE_ALIGN_SIZE
/*
 * Validate _WRS_VXDBG_CPU_CTRL_VARS_ALIGN vs current build's
 *  _CPU_CACHE_ALIGN_SIZE
 *
 * If any SMP-enabled variant fails this test, _WRS_VXDBG_CPU_CTRL_VARS_ALIGN
 * must be increased. Since this limit also applies to any subsequent arch-only
 * release against the same generic binary release, it may be desirable to
 * allow for growth.
 */

#if (_CPU_CACHE_ALIGN_SIZE > _WRS_VXDBG_CPU_CTRL_VARS_ALIGN)
#error Must increase "_WRS_VXDBG_CPU_CTRL_VARS_ALIGN" to at least _CPU_CACHE_ALIGN_SIZE
#endif  /* _CPU_CACHE_ALIGN_SIZE > _WRS_VXDBG_CPU_CTRL_VARS_ALIGN */
#endif /* _CPU_CACHE_ALIGN_SIZE */

#endif	/* _WRS_CONFIG_SMP */

#ifdef __cplusplus
}
#endif

#endif	/* __INCvxdbgLibPh */
