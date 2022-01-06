/* vxLib.h - header file for vxLib.c */

/*
 * Copyright (c) 1991-1994, 1996-1997, 2000-2001, 2003, 2006-2007,
 *               2009-2011, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03h,26sep13,cww  update len argument type for checksum()
03g,22jul13,yjw  Adding ARMARCH7M
03f,14aug11,j_l  Fix XSCALE build issue
03e,01aug11,rbc  WIND00238999 - Add VSB _WRS_CONFIG_PWR_MGMT
03d,07jul11,j_l  WIND00255353 PwrMgmt: VxWorks Tickless operating mode for IA
03c,29apr10,pad  Moved extern C statement after include statements.
03b,19jun09,mze  replacing PAD64
03a,20jan09,jb   Adding 64-bit support
02z,15aug07,mmi  declare legacy power management only if necessary, update
		 Copyright year
02y,01nov06,slk  add vxMemProbeInit prototype
02x,28oct06,lei  added inclusion of vxCpuLib.h 
02w,17aug06,kk   added vxMemArchProbe()
02v,19jul06,mmi  add CPUSET_ZERO() and relocated macros to b_cpuset_t.h 
02u,19jun06,mmi  add MACROs to access cpuset_t and fixed copyright 
02t,26aug03,rec  remove SYS_PWR_MGMT conditional
02s,18aug03,dbt  Added inclusion of vxSimlinuxLib.h file for Linux VxSim.
		 Renamed vxSimnt.h in vxSimntLib.h
02r,15jul03,kam  rebased to Base6 integration branch
02q,10jul03,rec  fix archPwrDown data type
02p,01jul03,rec  code review comments
02o,28may03,rec  Power management, added vxArchPowerDownSet, vxArchPowerDown, archPwrDown
02n,02apr03,jmp  Added inclusion of vxSimnt.h file for Windows VxSim.
02m,25mar03,dbt  Added inclusion of vxSimsolarisLib.h file for Solaris VxSim.
02l,14nov01,ahm  added vxI86Lib.h for I80x86 family
02k,11oct01,cjj  removed Am29K support
02j,17apr00,hk   added #include for sh/vxShLib.h.
02i,04jun97,dat  added _func_vxMemProbeHook and vxMemArchProbe, SPR 8658
		 removed sysMemProbe.
02h,22oct96,spm  added comment specifying location of checksum() definition
02g,28feb96,tam	 added #include for ppc/vxPpcLib.h.
02f,04jul94,tpr	 added #include for mc68k/vx68kLib.h.
02e,02dec93,pme  added Am29K family support.
02d,26jul94,jwt  added vxMemProbeAsi() prototype for SPARC; copyright '94.
02c,24sep92,yao  added missing arg in vxTas() declaration.
02b,22sep92,rrr  added support for c++
02a,04jul92,jcf  cleaned up.
01f,30jun92,jmm  moved checksum() declarations to here from icmpLib.h
01e,26may92,rrr  the tree shuffle
		  -changed includes to have absolute path from h/
01d,21apr92,ccc  added vxTas.
01c,27feb92,wmd  added #include for i960/vx960Lib.h.
01b,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01a,05oct90,shl created.
*/

#ifndef __INCvxLibh
#define __INCvxLibh

#if	(CPU_FAMILY == MC680X0)
#include <arch/mc68k/vx68kLib.h>
#endif	/* (CPU_FAMILY == MC680X0) */

#if	CPU_FAMILY==I960
#include <arch/i960/vxI960Lib.h>
#endif  /* CPU_FAMILY==I960 */

#if     CPU_FAMILY==PPC
#include <arch/ppc/vxPpcLib.h>
#endif  /* CPU_FAMILY==PPC */

#if     CPU_FAMILY==SH
#include <arch/sh/vxShLib.h>
#endif  /* CPU_FAMILY==SH */

#if     CPU_FAMILY==I80X86
#ifndef _WRS_CONFIG_LP64
#include <arch/i86/vxI86Lib.h>
#else
#include <arch/i86/x86_64/vxX86_64Lib.h>
#endif  /* LP64 */
#endif  /* CPU_FAMILY==I80X86 */

#if     CPU_FAMILY==SIMSPARCSOLARIS
#include <arch/simsolaris/vxSimsolarisLib.h>
#endif  /* CPU_FAMILY==SIMSPARCSOLARIS */

#if     CPU_FAMILY==SIMLINUX
#include <arch/simlinux/vxSimlinuxLib.h>
#endif  /* CPU_FAMILY==SIMLINUX */

#if     CPU_FAMILY==SIMNT
#include <arch/simnt/vxSimntLib.h>
#endif  /* CPU_FAMILY==SIMNT */

#include <vxCpuLib.h>  /* vxCpu[Index Enabled Configured]Get  */

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef void (*VX_PWR_DOWN)(void);

/* function declarations */

extern STATUS 	vxMemProbe (char * adrs, int mode, int length, char * pVal);
extern STATUS 	vxMemProbeInit (void);
extern BOOL 	vxTas (void * address);
extern STATUS 	vxMemArchProbe (void * adrs, int mode, int length, void * pVal);
extern STATUS 	(* _func_vxMemProbeHook)(void *, int, int, void *);

#if defined(_WRS_CONFIG_PWR_MGMT) || ((CPU==XSCALE) || (CPU==ARMARCH7M))
extern void             vxArchPowerDownSet (VX_PWR_DOWN powerDownRtn);
extern VX_PWR_DOWN      vxArchPowerDown;
extern void             archPwrDown (void);
#endif /* defined(_WRS_CONFIG_PWR_MGMT) || (CPU==XSCALE) */

/* checksum is defined in ./target/src/util/cksumLib.c */

extern u_short	checksum (u_short * pAddr, size_t len);

#if	(CPU_FAMILY == SPARC)
extern STATUS 	vxMemProbeAsi (char * adrs, int mode, int length, char * pVal,
			       int asi);
#endif	/* CPU_FAMILY == SPARC */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxLibh */
