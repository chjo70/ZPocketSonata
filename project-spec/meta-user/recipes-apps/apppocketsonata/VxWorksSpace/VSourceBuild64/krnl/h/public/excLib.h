/* excLib.h - exception library header */

/*
 * Copyright (c) 1984-2005, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
02q,30mar10,pad  Moved 'extern "C"' statement and applied C++ inline scheme for
		 excHookAdd().
02p,19jan10,pad  Removed usage of _WRS_KEEP_USING_FUNCPTR.
02o,19jun09,mze  replacing PAD64
02n,26mar09,zl   updated for LP64 build. Removed unused EXC_FAULT_TAB. Removed
                 duplicate printExc() declaration (it is in fioLib.h).
02m,20jan09,jb   Adding 64-bit support
02l,28sep05,kk   remove deprecated message in excJobAdd()
02k,08feb05,pch  SPR 102772: add errno S_excLib_INTERRUPT_STACK_OVERFLOW
02j,22oct04,pch  SPR 92598: add errno S_excLib_EXCEPTION_STACK_OVERFLOW
02i,04sep04,dbt  Fixed excJobAdd() declaration.
02h,02sep04,ans  Deprecate excJobAdd
02g,09oct03,pcm  corrected declaration of printExc()
02f,17apr03,dbt  Added SIMLINUX support.
02e,13nov01,yvp  Added excExtendedVectors - support for extended branch
                 vectors. Also moved private functions into the newly created
                 h/privare/excLibP.h.
02d,22oct01,dee  Merge from T2.1.0 ColdFire
02c,01mar00,frf  Add SH4 support for T2.
02b,23apr97,hk   added SH support.
02b,15aug97,cym  added SIMNT support.
02b,28nov96,cdp  added ARM support.
02a,26may94,yao  added PPC support.
01y,12jul95,ism  added simsolaris support
01x,19mar95,dvs  removed #ifdef TRON - tron no longer supported.
01w,29jan94,gae  added ASMLANGUAGE around typedef.
01v,02dec93,pme  added Am29K family support
01u,15oct93,cd   added #ifndef _ASMLANGUAGE.
01t,11aug93,gae  vxsim hppa.
01s,20jun93,gae  vxsim.
01r,09jun93,hdn  added support for I80X86
01q,22sep92,rrr  added support for c++
01p,02aug92,jcf  removed excDeliverHook decl/added excShowInit.
01o,27jul92,rrr  added excDeliverHook decl
01n,04jul92,jcf  cleaned up.
01m,26may92,rrr  the tree shuffle
		  -changed includes to have absolute path from h/
01l,20jan92,yao  added ANSI function prototype for excInfoShow(), printExc().
		 added EXC_FAULT_TAB.
01k,09jan92,jwt  added ANSI function prototype for excJobAdd().
01j,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01i,02aug91,ajm  added MIPS support
01h,19jul91,gae  renamed architecture specific include file to be xx<arch>.h.
01g,22may91,wmd  made to include "CPU/excLib.h".
01f,29apr91,hdn  added TRON defines and macros.
01e,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01d,29sep90,del  added include i960/exc960Lib.h for I960 CPU_FAMILY
01c,01aug90,jcf  padded EXC_INFO to four byte boundary.
		 changed USHORT to UINT16.
01b,28apr89,mcl  added SPARC.
01a,28may88,dnw  written
*/

#ifndef __INCexcLibh
#define __INCexcLibh

#include <vwModNum.h>
#define	S_excLib_EXCEPTION_STACK_OVERFLOW	(M_excLib | 1)
#define	S_excLib_INTERRUPT_STACK_OVERFLOW	(M_excLib | 2)

#if 	CPU_FAMILY==I960
#include <arch/i960/excI960Lib.h>
#endif	/* CPU_FAMILY==I960 */

#if     CPU_FAMILY==MC680X0
#include <arch/mc68k/excMc68kLib.h>
#endif  /* CPU_FAMILY==MC680X0 */

#if     CPU_FAMILY==COLDFIRE
#include <arch/coldfire/excColdfireLib.h>
#endif  /* CPU_FAMILY==COLDFIRE */

#if     CPU_FAMILY==MIPS
#include <arch/mips/excMipsLib.h>
#endif	/* CPU_FAMILY==MIPS */

#if     CPU_FAMILY==PPC
#include <arch/ppc/excPpcLib.h>
#endif  /* CPU_FAMILY==PPC */

#if	CPU_FAMILY==SPARC
#include <arch/sparc/excSparcLib.h>
#endif	/* CPU_FAMILY==SPARC */

#if	CPU_FAMILY==SIMSPARCSOLARIS
#include <arch/simsolaris/excSimsolarisLib.h>
#endif	/* CPU_FAMILY==SIMSPARCSOLARIS */

#if	CPU_FAMILY==SIMLINUX
#include <arch/simlinux/excSimlinuxLib.h>
#endif	/* CPU_FAMILY==SIMLINUX */

#if	CPU_FAMILY==SIMNT
#include <arch/simnt/excSimntLib.h>
#endif	/* CPU_FAMILY==SIMNT */

#if     CPU_FAMILY==I80X86
#ifndef _WRS_CONFIG_LP64
#include <arch/i86/excI86Lib.h>
#else
#include <arch/i86/x86_64/excX86_64Lib.h>
#endif  /* LP64 */
#endif	/* CPU_FAMILY==I80X86 */

#if     CPU_FAMILY==AM29XXX
#include <arch/am29k/excAm29kLib.h>
#endif	/* CPU_FAMILY==AM29XXX */

#if	CPU_FAMILY==SH
#include <arch/sh/excShLib.h>
#endif	/* CPU_FAMILY==SH */

#if     CPU_FAMILY==ARM
#include <arch/arm/excArmLib.h>
#endif  /* CPU_FAMILY==ARM */

#ifndef	_ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern STATUS excShowInit (void);
extern STATUS excJobAdd   (VOIDFUNCPTR func, 
			   _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2, 
			   _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4, 
			   _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6);
extern void   excHookAdd  (void (*excepHook)   /* new declaration */
				  (
				  TASK_ID tid, 
				  int vecNum, 
				  void * pEsf
				  ));
#ifdef __cplusplus
}

/*
 * Inlined C++ wrapper for the old-style FUNCPTR based excHookAdd() function
 * prototype.
 */

extern void excHookAdd (FUNCPTR excepHook) \
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");

inline void excHookAdd
    (
    FUNCPTR excepHook
    )
    {
    return excHookAdd  ((void (*)(TASK_ID, int, void *))excepHook);
    }
#endif /* __cplusplus */

#endif /* _ASMLANGUAGE */

#endif /* __INCexcLibh */
