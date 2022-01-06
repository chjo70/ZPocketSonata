/* vxdbgCpuLibP.h - private vxdbg CPU control library header file */

/*
 * Copyright (c) 2007-2008, 2010-2011, 2013-2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */
                                                                                                          
/*
modification history
--------------------
11may16,jmp  Code adaptation to ease code sharing with VxWorks 6.x.
28aug14,jmp  Coverity fixes.
20may13,rlp  Moved vxdbgCpuLibInit prototype to vxdbgLibInit header
20dec11,rlp  CQID: Fix WIND00323889 - Updated vxdbgCpuAllSuspend()
             prototype.
27may10,pad  Moved extern C statement after include statements.
27aug08,jpb  Renamed VSB header file
24jun08,jpb  Added include path for kernel configurations options set in
             vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
08feb08,jmp  changed vxdbgCpuXxx() return values to VXDBG_STATUS
             (CQ:WIND00116500).
31oct07,jmp  made vxdbgCpuCtrlEnabled an atomic variable.
24oct07,jmp  moved VXDBG_MARK_CPU_CTRL_REGSET_VALID() to vxdbgCpuCtrLoop(),
             made regSetIsValid an atomic variable (CQ:WIND00109057).
19jul07,jmp  added vxdbgCpuLibInit() (CQ:WIND00099255).
22jun07,rlp  Modified vxdbgCpuAllSuspend() prototype.
             Modified VXDBG_CPU_CTRL_VARS to check validity of register set.
05hun07,jmp  forced VXDBG_CPU_CTRL_VARS alignement only if
             _WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT is defined.
             Removed default value for _WRS_VXDBG_CPU_CTRL_VARS_ALIGN
             macro, but raise an error if not defined.
01jun07,jmp  moved errnos to vxdbgLibP.h.
16mar07,jmp  written
*/

#ifndef __INCvxdbgCpuLibPh
#define __INCvxdbgCpuLibPh

#include <vsbConfig.h>

#ifdef	_WRS_CONFIG_SMP

/* include */

#include <vxCpuLib.h>
#include <vxdbgLib.h>
#include <string.h>
#include <private/vxdbgLibP.h>
#include <private/vxSmpP.h>

#ifdef __cplusplus
extern "C" {
#endif
	
/* defines */

#ifdef _WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT

/*
 * _WRS_VXDBG_CPU_CTRL_VARS_ALIGN is architecture specific; it should be defined
 * for the common CPU build variants (e.g. PPC32, MIPS32, XSCALE, etc),
 * representing the maximum cache line size of the variants of the respective
 * arch.
 *
 * Another consideration for _WRS_VXDBG_CPU_CTRL_VARS_ALIGN is that, from
 * compiler and assembler optimization point of view, the alignment
 * should force the size of VXDBG_CPU_CTRL_VARS structure to be a power of 2
 * value.
 *
 * This macro must be defined in <arch/<ARCH>/private/vxdbg<ARCH>LibP.h>, it
 * is only required for architectures providing VxDBG architecture specific
 * support (_WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT).
 */

#ifndef _WRS_VXDBG_CPU_CTRL_VARS_ALIGN
#error "_WRS_VXDBG_CPU_CTRL_VARS_ALIGN not defined for this architecture"
#endif  /* !_WRS_VXDBG_CPU_CTRL_VARS_ALIGN */
#endif	/* _WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT */

#if (_WRS_VXWORKS_MAJOR == 7)
#define VXDBG_CPU_CTRL_IS_ENABLED()	\
	(vxAtomicGet (&vxdbgCpuCtrlEnabled) == TRUE)
#else
#define VXDBG_CPU_CTRL_IS_ENABLED()	\
	((_func_vxdbgCpuCtrlIsEnabled != NULL) && \
	(_func_vxdbgCpuCtrlIsEnabled() == TRUE))
#endif

#define VXDBG_CPU_CTRL_REGSET_IS_VALID(cpuIndex) \
	(vxAtomicGet (&vxdbgCpuCtrlVars[cpuIndex].vars.regSetIsValid))
#define VXDBG_MARK_CPU_CTRL_REGSET_VALID(cpuIndex) \
    ((void)vxAtomicSet (&vxdbgCpuCtrlVars[cpuIndex].vars.regSetIsValid, TRUE))

#define VXDBG_MARK_CPU_CTRL_REGSET_INVALID(cpuIndex) \
    ((void)vxAtomicSet (&vxdbgCpuCtrlVars[cpuIndex].vars.regSetIsValid, FALSE))

#if (_WRS_VXWORKS_MAJOR == 7)
#define VXDBG_CPU_CTRL_REGSET_SAVE(pRegSet)			\
    {								\
    if (VXDBG_CPU_CTRL_IS_ENABLED ())				\
	{							\
	int	cpuIndex = _WRS_CPU_INDEX_GET();		\
								\
	bcopy ((void *)pRegSet,					\
	       (void *)&vxdbgCpuCtrlVars[cpuIndex].vars.regSet,	\
	       sizeof (REG_SET));				\
	vxdbgCpuCtrlLoop();					\
	}							\
    }
#else
#define VXDBG_CPU_CTRL_REGSET_SAVE(pRegSet)			\
    {								\
    if (VXDBG_CPU_CTRL_IS_ENABLED ())				\
	{							\
	int	cpuIndex = _WRS_CPU_INDEX_GET();		\
								\
	bcopy ((void *)pRegSet,					\
	       (void *)&vxdbgCpuCtrlVars[cpuIndex].vars.regSet,	\
	       sizeof (REG_SET));				\
	vxdbgArchCpuCtrlLoop();					\
	}							\
    }
#endif

/* typedefs */

/*
 * WARNING: If the _VXDBG_CPU_CTRL_VARS structure is extended, then the
 * _WRS_VXDBG_CPU_CTRL_VARS_ALIGN and _WRS_VXDBG_CPU_CTRL_VARS_ALIGN_SHIFT
 * macros defined in <arch/<ARCH>/private/vxdbg<ARCH>LibP.h> for architectures
 * providing VxDBG arch specific support (_WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT)
 * must be double-checked to make sure that they still respect the alignment
 * constraints.
 */

typedef struct _vxdbg_cpu_ctrl_vars
    {
    REG_SET	regSet;		/* register set of the interrupted context */
    atomicVal_t	regSetIsValid;	/* indicate if the register set is valid */
    }
#ifdef _WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT
    _VXDBG_CPU_CTRL_VARS _WRS_DATA_ALIGN_BYTES (_WRS_VXDBG_CPU_CTRL_VARS_ALIGN);
#else	/* !_WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT */
    _VXDBG_CPU_CTRL_VARS;
#endif	/* !_WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT */

typedef struct vxdbg_cpu_ctrl_vars
    {
    _VXDBG_CPU_CTRL_VARS	vars;
    } VXDBG_CPU_CTRL_VARS;

/* externals */

extern atomicVal_t vxdbgCpuCtrlEnabled;/* Is CPU control enabled ? */
extern VXDBG_CPU_CTRL_VARS vxdbgCpuCtrlVars [];	/* Per-CPU VxDBG array */

#if (_WRS_VXWORKS_MAJOR < 7)
/* function pointers declarations */

extern void     (*_func_vxdbgCpuCtrlLoop) (void);
extern void     (*_func_vxdbgCpuCtrlEnableFlagSet) (void);
extern void     (*_func_vxdbgCpuCtrlEnableFlagClear) (void);
extern BOOL     (*_func_vxdbgCpuCtrlIsEnabled) (void);
extern VXDBG_STATUS (*_func_vxdbgCpuAllSuspend) (int timeout, REG_SET * pRegs,
                                                 BOOL multiCall);
extern VXDBG_STATUS (*_func_vxdbgCpuAllResume)  (void);
extern VXDBG_STATUS (*_func_vxdbgCpuSuspendHookAdd)     (void (*hook) ());
extern VXDBG_STATUS (*_func_vxdbgCpuResumeHookAdd)      (void (*hook) ());

#endif  /* _WRS_VXWORKS_MAJOR < 7 */

/* Forward declarations */

extern VXDBG_STATUS	vxdbgCpuAllSuspend	(int timeout, REG_SET * pRegs,
						 BOOL multiCall);
extern VXDBG_STATUS	vxdbgCpuAllResume	(void);
extern BOOL		vxdbgCpuIsSuspended	(int cpuIndex);
extern VXDBG_STATUS	vxdbgCpuRegsGet		(int cpuIndex,
						 REG_SET ** ppRegsSet);
extern VXDBG_STATUS	vxdbgCpuSuspendHookAdd	(void (*hook) ());
extern VXDBG_STATUS	vxdbgCpuResumeHookAdd	(void (*hook) ());
extern void		vxdbgCpuCtrlLoop	(void);
#if (_WRS_VXWORKS_MAJOR < 7)
extern void             vxdbgArchCpuCtrlLoop    (void);
#endif  /* _WRS_VXWORKS_MAJOR < 7 */
extern VXDBG_STATUS	vxdbgCpuCtrlEnable	(void);
extern VXDBG_STATUS	vxdbgCpuCtrlDisable	(void);

#ifdef __cplusplus
}
#endif

#endif	/* _WRS_CONFIG_SMP */

#endif /* __INCvxdbgCpuLibPh */

