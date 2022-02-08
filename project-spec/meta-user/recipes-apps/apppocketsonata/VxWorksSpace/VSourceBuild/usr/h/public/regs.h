/* regs.h - CPU registers */

/* 
 * Copyright 1984-2006, 2009-2010, 2012, 2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jan14,vhe removed reference to SIMPENTIUM build 
01g,21mar12,jpb  Updated for POSIX namespace isolation conformance (part of 
                 Defect WIND000307800).
01f,29jul10,pad  Moved extern C statement after include statements.
01e,03dec09,scm  Adding 64-bit support
01d,18may06,jpb  Updated for POSIX namespace conformance.  
		 Changed C preprocessor macro CPU_FAMILY to _VX_CPU_FAMILY.
01c,22jun05,rec  add coldfire
01b,22oct04,md   add saveRegs() prototype
01a,05jul04,md   dervied from 03f kernel version.
*/

#ifndef __INCregsh
#define __INCregsh

#if     _VX_CPU_FAMILY==_VX_PPC
#include <arch/ppc/regsPpc.h>
#endif  /* _VX_CPU_FAMILY==_VX_PPC */

#if     _VX_CPU_FAMILY==_VX_I80X86
#ifndef _WRS_CONFIG_LP64
#include <arch/i86/regsI86.h>
#else
#include "arch/i86/x86_64/regsX86_64.h"
#endif  /* LP64 */
#endif	/* _VX_CPU_FAMILY==_VX_I80X86 */

#if	_VX_CPU_FAMILY==_VX_SH
#include <arch/sh/regsSh.h>
#endif	/* _VX_CPU_FAMILY==_VX_SH */

#if     _VX_CPU_FAMILY==_VX_ARM
#include <arch/arm/regsArm.h>
#endif  /* _VX_CPU_FAMILY==_VX_ARM */

#if     _VX_CPU_FAMILY==_VX_MIPS
#include <arch/mips/regsMips.h>
#endif	/* _VX_CPU_FAMILY==_VX_MIPS */

#if	_VX_CPU_FAMILY==_VX_SIMSPARCSOLARIS
#include <arch/simsolaris/regsSimsolaris.h>
#endif	/* _VX_CPU_FAMILY==_VX_SIMSPARCSOLARIS */

#if	(_VX_CPU_FAMILY==_VX_SIMNT) || (_VX_CPU_FAMILY==_VX_SIMLINUX) 
#include <arch/simcommon/regsSimpentium.h>
#endif	/* _VX_CPU_FAMILY==_VX_SIMNT || _VX_CPU_FAMILY==_VX_SIMLINUX*/

#if	_VX_CPU_FAMILY==_VX_COLDFIRE
#include <arch/coldfire/regsColdfire.h>
#endif	/* _VX_CPU_FAMILY==_VX_COLDFIRE */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE
/* function prototypes */

#if !defined (_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE) && \
    !defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern STATUS saveRegs(REG_SET *); /* function for saving task's registers */
#endif /* !_POSIX_xxx_SOURCE */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCregsh */
