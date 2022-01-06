/* dsmLib.h - disassembler library header */

/*
 * Copyright (c) 1984-2003, 2009-2010, 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
31jan14,to   include types/vxCpu.h for CPU definitions
02k,10oct13,h_k  moved S_dsmLib_UNKNOWN_INSTRUCTION from arch headers.
                 removed unsupported arches header inclusions.
02j,22oct10,ggm  Removed 64 bit header file for x86 CPU. Now it uses 32 bit
                 version for both builds.
02i,29apr10,pad  Moved extern C statement after include statements.
02h,19jun09,mze  replacing PAD64
02g,20jan09,jb   Adding 64-bit support
02f,17apr03,dbt  Added SIMLINUX support.
02e,03mar03,jeg  Updated simsolaris header file
02d,22oct01,dee  Merge from T2.1.0 ColdFire
02c,01mar00,frf  Add SH4 support for T2.
02b,23apr97,hk   added SH support.
02b,14aug97,cym  added SIMNT support.
02b,28nov96,cdp  added ARM support.
02a,14sep94,caf  added PPC support.
01s,12jul95,ism  added simsolaris support
01r,19mar95,dvs  removed #ifdef TRON - tron no longer supported.
01q,02dec93,pad  added Am29k family support.
01p,11aug93,gae  vxsim hppa.
01o,20jun93,gae  vxsim.
01n,09jun93,hdn  added support for I80X86
01m,22sep92,rrr  added support for c++
01l,04jul92,jcf  cleaned up.
01k,26may92,rrr  the tree shuffle
		  -changed includes to have absolute path from h/
01j,09jan92,jwt  converted CPU==SPARC to CPU_FAMILY==SPARC.
01i,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01h,10seo91,wmd  fixed typo in comments.
01g,02aug91,ajm  added MIPS support
01f,19jul91,gae  renamed architecture specific include file to be xx<arch>.h.
01e,29apr91,hdn  added defines and macros for TRON architecture.
01d,25oct90,shl  fixed CPU_FAMILY logic so 68k and sparc won't clash when
		 compiling for sparc.
01c,05oct90,shl  added copyright notice.
                 made #endif ANSI style.
01b,28sep90,del  include i960/dsmLib.h.
01a,07aug89,gae  written.
*/

#ifndef __INCdsmLibh
#define __INCdsmLibh

#include <types/vxCpu.h>
#include <vwModNum.h>
#include <stdio.h>

#if     CPU_FAMILY==ARM
#include "arch/arm/dsmArmLib.h"
#endif  /* CPU_FAMILY==ARM */

#if     CPU_FAMILY==I80X86
#include "arch/i86/dsmI86Lib.h"
#endif	/* CPU_FAMILY==I80X86 */

#if     CPU_FAMILY==PPC
#include "arch/ppc/dsmPpcLib.h"
#endif  /* CPU_FAMILY==PPC */

#if	CPU_FAMILY==SIMLINUX
#include "arch/simlinux/dsmSimlinuxLib.h"
#endif	/* CPU_FAMILY==SIMLINUX */

#if	CPU_FAMILY==SIMNT
#include "arch/simnt/dsmSimntLib.h"
#endif	/* CPU_FAMILY==SIMNT */

#ifdef __cplusplus
extern "C" {
#endif

/* dsmLib status codes */

#define S_dsmLib_UNKNOWN_INSTRUCTION    (M_dsmLib | 1)

typedef void (*NPRTADDRESS_OUTPUT_FUNCPTR)
        (_Vx_usr_arg_t, OPRINTF_OUTPUT_FUNCPTR, _Vx_usr_arg_t);

#ifdef __cplusplus
}
#endif

#endif /* __INCdsmLibh */
