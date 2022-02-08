/* fppLib.h - floating-point coprocessor support library header */

/*
 * Copyright (c) 1984-2005, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02l,06oct10,pad  Fixed wrongly placed closing brace for C++ extern C
                 statement (defect #230174).
02k,28sep10,scm  use TASK_ID for 64 bit compatibility...
02j,29apr10,pad  Moved extern C statement after include statements.
02i,19jun09,mze  replacing PAD64
02h,29may09,cww  Removed fppLib
02g,20jan09,jb   Adding 64-bit support
02f,19apr05,dr   Cleanup
02e,17apr03,dbt  Added SIMLINUX support.
02d,22oct01,dee  Merge from T2.1.0 ColdFire
02c,01mar00,frf  Add SH4 support for T2.
02b,23apr97,hk   added SH support.
02b,15aug97,cym  added SIMNT support.
02b,28nov96,cdp  added ARM support.
02a,26may94,yao  added PPC support.
01u.26may95,ms	 added prototypes for fppRegsToCtx and fppCtxToRegs.
01u,12jul95,ism  added simsolaris support
01t,19mar95,dvs  removed #ifdef TRON - tron no longer supported.
01s,02dec93,pme  added Am29K family support
01r,11aug93,gae  vxsim hppa.
01q,20jun93,gae  vxsim.
01p,09jun93,hdn  added support for I80X86
01o,22sep92,rrr  added support for c++
01n,19sep92,jcf  ifdef _ASMLANGUAGE of taskLib.h
01m,19sep92,smb  added include of taskLib.h
01l,04jul92,jcf  cleaned up.
01k,26may92,rrr  the tree shuffle
		  -changed includes to have absolute path from h/
01j,20feb92,yao  changed ANSI function propotype declaration for
		 fppTaskRegs{S,G}et() and removed CPU_FAMILY conditionals.
01i,09jan92,jwt  converted CPU==SPARC to CPU_FAMILY==SPARC.
01h,01nov91,wmd  modified prototype of fpregs in fppTaskRegsGet() to be double.
01g,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed ASMLANGUAGE to _ASMLANGUAGE
		  -changed copyright notice
01f,20aug91,ajm  added MIPS support.
01e,14aug91,del  added include for I960KB support.
01d,19jul91,gae  renamed architecture specific include file to be xx<arch>.h.
01c,29apr91,hdn  added defines and macros for TRON architecture.
01b,05oct90,shl  added copyright notice.
                 made #endif ANSI style.
01a,07aug89,gae  written.
*/

#ifndef __INCfppLibh
#define __INCfppLibh

#ifndef _ASMLANGUAGE
#include <taskLib.h>
#endif	/* _ASMLANGUAGE */

#if     CPU_FAMILY==COLDFIRE
#include "arch/coldfire/fppColdfireLib.h"
#endif	/* CPU==COLDFIRE */

#if     CPU_FAMILY==MIPS
#include "arch/mips/fppMipsLib.h"
#endif	/* MIPS */

#if     CPU_FAMILY==PPC
#include "arch/ppc/fppPpcLib.h"
#endif  /* CPU_FAMILY==PPC */

#if	CPU_FAMILY==SIMSPARCSOLARIS
#include "arch/simsolaris/fppSimsolarisLib.h"
#endif	/* CPU_FAMILY==SIMSPARCSOLARIS */

#if	CPU_FAMILY==SIMNT
#include "arch/simnt/fppSimntLib.h"
#endif	/* CPU_FAMILY==SIMNT */

#if	CPU_FAMILY==SIMLINUX
#include "arch/simlinux/fppSimlinuxLib.h"
#endif	/* CPU_FAMILY==SIMLINUX */

#if     CPU_FAMILY==I80X86
#ifndef _WRS_CONFIG_LP64
#include "arch/i86/fppI86Lib.h"
#else
#include "arch/i86/x86_64/fppX86_64Lib.h"
#endif  /* LP64 */
#endif	/* CPU_FAMILY==I80X86 */

#if	CPU_FAMILY==SH
#include "arch/sh/fppShLib.h"
#endif	/* CPU_FAMILY==SH */

#if     CPU_FAMILY==ARM
#include "arch/arm/fppArmLib.h"
#endif  /* CPU_FAMILY==ARM */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* function declarations */

extern void     fppRestore (FP_CONTEXT *pFpContext);
extern void     fppSave (FP_CONTEXT *pFpContext);
extern STATUS   fppProbe (void);
extern void     fppRegsToCtx (FPREG_SET *pFpRegSet, FP_CONTEXT *pFpContext);
extern void     fppCtxToRegs (FP_CONTEXT *pFpContext, FPREG_SET *pFpRegSet);
extern STATUS   fppTaskRegsGet (TASK_ID task, FPREG_SET *pFpRegSet);
extern STATUS   fppTaskRegsSet (TASK_ID task, FPREG_SET *pFpRegSet);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCfppLibh */
