/* usrLib.h - header for user interface subroutines */

/*
 * Copyright (c) 1984, 1986, 1988-1992, 1995, 2001, 2003-2004, 
 * 2008-2010, 2013-2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
26jul17,saj  Added prototypes for iam() and whoami()
29jan14,elp  Removed LOADER dependencies.
02x,31dec13,ghs  Remove reference of usrFsLib.h (US29308)
02w,29apr10,pad  Moved extern C statement after include statements.
02v,28apr09,jmp  Adapted for 64-bit support.
02u,11sep08,v_r  Added tip() prototype (req CQ:WIND00114857).
02t,10nov04,dbt  Added reld() prototype (SPR #103739).
02s,02oct04,bpn  Exported sp() variables.
02r,18sep04,jn   Move unld from unldLib to usrLib
02q,09sep04,bpn  Added w() and tw() prototypes.
02p,03aug04,bpn  Added shConfig() prototype.
02o,18may04,bpn  Moved function prototypes to usrLibP.h.
02n,07apr04,bpn  Changed shStrFree() to strFree().
02m,01apr04,bpn  Added showCoreRtn() prototype.
02l,12mar04,bpn  Added shStrFree() prototype.
02k,09apr04,dat  mv usrFsLib stuff to separate header
02j,22sep03,bpn  Cleaned up. Added usrFsShellCmdInit() prototype.
02i,09may03,pes  PAL conditional compilation cleanup. Phase 2.
02h,17oct01,jkf  added prototypes for usrFsLib.c functions, SPR#74904
02g,24sep01,jkf  added const to prototypes cd(), rm(), disk*(), copy().
02f,27may95,p_m  added spy routines prototypes.
02e,22sep92,rrr  added support for c++
02d,18sep92,smb  moved mkdir and rmdir prototype to sys/stat.h and
		 unistd.h repecatively and included sys/stat.h and unistd.h
02c,29jul92,smb  changed parameter to printErrno from errno to errNo.
02b,15jul92,jmm  changed ld() to return MODULE_ID rather than STATUS
02a,04jul92,jcf  cleaned up.
01v,25jun92,yao  added ANSI definition for pc().
01u,16jun92,yao  changed declaration for mRegs().
01t,26may92,rrr  the tree shuffle
01s,20jan92,yao  removed ANSI definition for register displaying routines.
		 removed conditional CPU_FAMILY != I960.  changed ANSI
		 propotype definition for d(), m() and mRegs().
01r,09jan92,jwt  converted CPU==SPARC to CPU_FAMILY==SPARC.
01q,07nov91,hdn  added defines F0 - F15, FPMCR, FPSR, FPQR for G200.
01p,07nov91,wmd  conditionalized declaration of d() with BYTE_ORDER.
01o,29oct91,shl  removed duplicate rename() prototype -- SPR #927.
01n,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01m,20aug91,ajm  added MIPS_R3k support.
01l,14aug91,del  (intel) added FPx regs for I960KB support.
01k,29apr91,hdn  added defines and macros for TRON architecture.
01j,03feb90,del  added I960 support.
01i,05oct90,dnw  deleted private functions.
		 changed spawn, etc, to take var args.
01h,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01g,20aug89,gae  changed ifdef to CPU_FAMILY.
01f,16jul88,ecs  added SPARC register codes.
01e,24dec86,gae  changed stsLib.h to vwModNum.h.
01d,20aug86,llk  added register codes.
01c,10feb86,dnw  deleted obsolete definition of S_usrLib_NO_FREE_TID.
01b,13aug84,dnw  changed name to usrLib.
01a,06aug84,ecs  written
*/

#ifndef __INCusrLibh
#define __INCusrLibh

#include <vwModNum.h>
#include <regs.h>
#include <fppLib.h>
#ifdef _WRS_CONFIG_LOADER
#include <moduleLib.h>
#endif /* _WRS_CONFIG_LOADER */
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined _WRS_TASK_REG_WIDTH
#ifdef _WRS_CONFIG_LP64
#define _WRS_TASK_REG_WIDTH	8
#else	/* !_WRS_CONFIG_LP64 */
#define _WRS_TASK_REG_WIDTH	4
#endif	/* !_WRS_CONFIG_LP64 */
#endif /* _WRS_TASK_REG_WIDTH */

#if !defined _WRS_FPCTL_REG_WIDTH
#define _WRS_FPCTL_REG_WIDTH	4
#endif /* _WRS_FPCTL_REG_WIDTH */

/* usrLib status codes */

#define S_usrLib_NOT_ENOUGH_ARGS	(M_usrLib | 1)

/* Global variables */

extern int	spTaskPriority;
extern int	spTaskOptions;
extern size_t	spTaskStackSize;

/* Function declarations */

extern void 	help		(void);
extern void 	netHelp		(void);
extern void	tw		(long taskNameOrId);
extern void	w		(long taskNameOrId);
extern void	shConfig	(const char * config);
extern void	strFree		(char * string);
extern void 	bootChange	(void);
extern void 	periodRun	(int sec, FUNCPTR rtn, long arg1, long arg2,
				 long arg3, long arg4, long arg5, long arg6,
				 long arg7, long arg8);
extern long 	period		(int secs, FUNCPTR func, long arg1, long arg2, 
				 long arg3, long arg4, long arg5, long arg6,
				 long arg7, long arg8);
extern void 	repeatRun	(int n, FUNCPTR func, long arg1, long arg2,
				 long arg3, long arg4, long arg5, long arg6,
				 long arg7, long arg8);
extern long 	repeat		(int n, FUNCPTR func,long arg1, long arg2,
				 long arg3, long arg4, long arg5, long arg6,
				 long arg7, long arg8);
extern long 	sp		(FUNCPTR func, long arg1, long arg2, long arg3,
				 long arg4, long arg5, long arg6, long arg7,
				 long arg8, long arg9);
extern void 	checkStack	(long taskNameOrId);
extern void 	i		(long taskNameOrId);
extern void 	ts		(long taskNameOrId);
extern void 	tr		(long taskNameOrId);
extern void 	td		(long taskNameOrId);
extern void 	ti		(long taskNameOrId);
extern void 	version		(void);
extern void 	m		(void *adrs, int width);
extern void 	d		(void *adrs, int nwords, int width);
extern STATUS 	squeeze		(char *devName);
extern STATUS	iam		();
extern void	whoami		(void);
#ifdef _WRS_CONFIG_LOADER
extern MODULE_ID ld		(int syms, BOOL noAbort, char *name);
extern STATUS   unld		(void *name, int options);
extern MODULE_ID reld		(void * nameOrId, int options);
#endif /* _WRS_CONFIG_LOADER */
extern STATUS 	lsOld		(char *dirName);
extern void 	devs		(void);
extern void 	lkup		(char *substr);
extern void 	lkAddr		(unsigned long addr);
extern STATUS 	mRegs		(char * regName, long taskNameOrId);
extern void 	printErrno	(int errNo);
extern void 	printLogo	(void);
extern void 	logout		(void);
extern void 	h		(int size);
extern long 	pc		(long taskId);
extern void 	show		(long objId, int level);
extern STATUS	spyClkStart	(int intsPerSec);
extern void	spyClkStop	(void);
extern void	spy		(int freq, int ticksPerSec);
extern void	spyStop		(void);
extern void	spyHelp		(void);
extern void	spyReport	(void);
extern void	spyTask		(int freq);
extern void	tip		(char * dev1Str, ...);
extern void	tipHelp		(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCusrLibh */
