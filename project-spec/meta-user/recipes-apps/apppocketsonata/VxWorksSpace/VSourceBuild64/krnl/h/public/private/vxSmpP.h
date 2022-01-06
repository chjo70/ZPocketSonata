/* vxSmpP.h - select appropriate SMP definitions based on CPU_FAMILY */

/*
 * Copyright (c) 2006-2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Any compilation using definitions from this file will not *
 * be binary-compatible between the UP and SMP environments. *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

/*
modification history
--------------------
01i,29apr10,pad  Moved extern C statement after include statements.
01h,19jun09,mze  replacing PAD64
01g,21jan09,jb   Adding 64-bit support
01f,03may07,m_h  Add ARM SMP
01e,17apr07,kk  move VX_MAX_SMP_CPUS from here to vxWorksCommon.h
01d,21sep06,elp  added simulators
01c,21aug06,jb  Enabling i86
01b,12aug06,pes  Enable include of smpMipsP.h.
01a,31jul06,pch  written.
*/

#ifndef __INCvxSmpPh
#define __INCvxSmpPh

#if	(CPU_FAMILY == PPC)
#include <arch/ppc/private/smpPpcP.h>
#endif	/* (CPU_FAMILY == PPC) */

#if     CPU_FAMILY==MIPS
#include <arch/mips/private/smpMipsP.h>
#endif	/* MIPS */

#if     CPU_FAMILY==I80X86
#ifndef _WRS_CONFIG_LP64
#include <arch/i86/private/smpI86P.h>
#else
#include <arch/i86/x86_64/private/smpX86_64P.h>
#endif  /* LP64 */
#endif  /* CPU_FAMILY==I80X86 */

#if     CPU_FAMILY==ARM
#include <arch/arm/private/smpArmP.h>
#endif  /* CPU_FAMILY==ARM */

#if 0
#if	(CPU_FAMILY == SH)
#include <arch/sh/private/smpShP.h>
#endif	/* (CPU_FAMILY == SH) */

#if CPU_FAMILY==COLDFIRE
#include <arch/coldfire/private/smpColdfireP.h>
#endif  /* CPU_FAMILY==COLDFIRE */
#endif	/* 0 */

#if CPU_FAMILY==SIMLINUX
#include <arch/simlinux/private/smpSimlinuxP.h>
#endif	/* CPU_FAMILY==SIMLINUX */

#if	CPU_FAMILY==SIMNT
#include <arch/simnt/private/smpSimntP.h>
#endif	/* CPU_FAMILY==SIMLINUX */

#if	CPU_FAMILY==SIMSPARCSOLARIS
#include <arch/simsolaris/private/smpSimsolarisP.h>
#endif	/* CPU_FAMILY==SIMSPARCSOLARIS */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCvxSmpPh */
