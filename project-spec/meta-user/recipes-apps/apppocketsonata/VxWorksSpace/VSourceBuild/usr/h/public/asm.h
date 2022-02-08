/* asm.h - assembler definitions header file */

/* Copyright 2004-2006, 2010, 2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jan14,vhe removed reference to SIMPENTIUM build
01d,29jul10,pad  Moved extern C statement after include statements.
01c,03dec09,scm  Adding 64-bit support...
01b,18may06,jpb  Updated for POSIX namespace conformance.  
		 Changed C preprocessor macro CPU_FAMILY to _VX_CPU_FAMILY.
01a,05jul04,md   written
*/

#ifndef __INCasmh
#define __INCasmh

#if _VX_CPU_FAMILY==_VX_PPC
#include "arch/ppc/asmPpc.h"
#endif  /* PPC */

#if _VX_CPU_FAMILY==_VX_I80X86
#ifndef  _WRS_CONFIG_LP64
#include "arch/i86/asmI86.h"
#else
#include "arch/i86/x86_64/asmX86_64.h"
#endif /* LP64 */
#endif	/* I86 */

#if	_VX_CPU_FAMILY==_VX_SH
#include "arch/sh/asmSh.h"
#endif	/* SH */

#if _VX_CPU_FAMILY==_VX_ARM
#include "arch/arm/asmArm.h"
#endif  /* ARM */

#if _VX_CPU_FAMILY==_VX_MIPS
#include "arch/mips/asmMips.h"
#endif	/* MIPS */

#if	_VX_CPU_FAMILY==_VX_SIMSPARCSOLARIS
#include "arch/simsolaris/asmSimsolaris.h"
#endif	/* SIMSPARCSUNOS */

#if	(_VX_CPU_FAMILY==_VX_SIMNT) || (_VX_CPU_FAMILY==_VX_SIMLINUX)
#include "arch/simcommon/asmSimpentium.h"
#endif	/* SIMNT || SIMLINUX */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCasmh */
