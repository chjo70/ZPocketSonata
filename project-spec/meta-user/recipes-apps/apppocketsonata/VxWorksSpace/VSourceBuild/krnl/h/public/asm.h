/* asm.h - assembler definitions header file */

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
02m,29apr10,pad  Moved extern C statement after include statements.
02l,19jun09,mze  replacing PAD64
02k,20jan09,jb   Adding 64-bit support
02j,05oct07,gls  moved _WRS_ASM_EXTERN_KERNEL_GLOBALS to windLibP.h
                 (defect #00106175)
02i,11apr07,jmg  Removed vxSchedStackBase and vxSchedStackEnd from
                 _WRS_ASM_EXTERN_KERNEL_GLOBALS
02h,13dec06,kk   remove references to table based CPU globals
02g,02aug06,pch  Fix syntax errors in _WRS_ASM_EXTERN_KERNEL_GLOBALS expansion
02f,17jul06,zl   added _WRS_ASM_EXTERN_KERNEL_GLOBALS definition
02e,17apr03,dbt  Added SIMLINUX support.
02d,22oct01,dee  Merge from T2.1.0 ColdFire
02c,01mar00,frf  Add SH4 support for T2
02p,23apr97,hk   added support for SH.
02b,15aug97,cym  added support for SIMNT
02b,28nov96,cdp  added ARM support.
021,29jun95,ism  added support for SIMSPARCSOLARIS
01n,19mar95,dvs  removed #ifdef TRON - tron no longer supported.
01m,18jun93,hdn  added support for I80X86
01l,02dec93,pme  added Am29K support 
01k,11aug93,gae  vxsim hppa.
01j,20jun93,gae  vxsim.
01i,22sep92,rrr  added support for c++
01h,04jul92,jcf  cleaned up.
01g,26may92,rrr  the tree shuffle
		  -changed includes to have absolute path from h/
01f,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01e,02aug91,ajm  added MIPS support
01d,19jul91,gae  renamed architecture specific include file to be xx<arch>.h.
01c,29apr91,hdn  added defines and macros for TRON architecture.
01b,05oct90,shl  added copyright notice.
                 made #endif ANSI style.
01a,07may90,gae  written.
*/

#ifndef __INCasmh
#define __INCasmh

#if	CPU_FAMILY==MC680X0
#include "arch/mc68k/asmMc68k.h"
#endif	/* MC680X0 */

#if	CPU_FAMILY==COLDFIRE
#include "arch/coldfire/asmColdfire.h"
#endif	/* COLDFIRE */

#if	CPU_FAMILY==SPARC
#include "arch/sparc/asmSparc.h"
#endif	/* SPARC */

#if	CPU_FAMILY==SIMSPARCSUNOS
#include "arch/simsparc/asmSimsparc.h"
#endif	/* SIMSPARCSUNOS */

#if	CPU_FAMILY==SIMSPARCSOLARIS
#include "arch/simsolaris/asmSimsolaris.h"
#endif	/* SIMSPARCSUNOS */

#if	CPU_FAMILY==SIMHPPA
#include "arch/simhppa/asmSimhppa.h"
#endif	/* SIMHPPA */

#if	CPU_FAMILY==SIMLINUX
#include "arch/simlinux/asmSimlinux.h"
#endif	/* SIMLINUX */

#if	CPU_FAMILY==SIMNT
#include "arch/simnt/asmSimnt.h"
#endif	/* SIMNT */

#if     CPU_FAMILY==MIPS
#include "arch/mips/asmMips.h"
#endif	/* MIPS */

#if     CPU_FAMILY==PPC
#include "arch/ppc/asmPpc.h"
#endif  /* PPC */

#if     CPU_FAMILY==I80X86
#ifndef  _WRS_CONFIG_LP64 
#include "arch/i86/asmI86.h"
#else
#include "arch/i86/x86_64/asmX86_64.h"
#endif /* LP64 */
#endif	/* I80X86 */

#if     CPU_FAMILY==AM29XXX
#include "arch/am29k/asmAm29k.h"
#endif	/* AM29XXX */

#if	CPU_FAMILY==SH
#include "arch/sh/asmSh.h"
#endif	/* SH */

#if     CPU_FAMILY==ARM
#include "arch/arm/asmArm.h"
#endif  /* ARM */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCasmh */
