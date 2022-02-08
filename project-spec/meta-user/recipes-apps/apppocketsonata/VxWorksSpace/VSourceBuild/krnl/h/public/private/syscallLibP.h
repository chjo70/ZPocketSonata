/* syscallLibP.h - System Call Infrastructure library private header */

/* 
 * Copyright (c) 2003-2005, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
08sep14,pee      decouple syscall.h for offset generation (V7COR-1604)
01t,26may10,pad  Moved extern C statement after include statements.
01s,18dec09,cww  Added syscallShowInit
01r,03dec09,cww  LP64 adaptation
01q,19jun09,mze  replacing PAD64
01p,21jan09,jb   Adding 64-bit support
01o,05may05,rec  add syscallColdfire.h
01n,07apr05,scm  correct syscall macros for ARM/XScale...
01m,11jun04,dcc  modified SYSCALL_USER_* macros to use
                 sizeof(SYSCALL_ENTRY_STATE).
01l,15apr04,yvp  Added SYSCALL_USER_XXX_GET macros.
01k,29dec03,jeg  added simsolaris support
01j,03dec03,jb	 Adding syscall and RTP support for i86
01i,18nov03,yvp  Added typedefs for syscall hook functions.
01h,05nov03,jmp  Added include for SIMNT & SIMLINUX.
01g,15oct03,scm  add ARM link...
01f,26sep03,h_k  Added include for SH specific header.
01e,24sep03,pes  Correct conditional test for MIPS
01d,22sep03,yvp  Uncommented #include for syscall.h.
01d,19sep03,pes  Add #include for syscallMips.h
01c,15sep03,yvp  Added includes for arch-specific headers.
                 Added prototype for syscallDispatch().
01b,03sep03,yvp  Added extern for syscallGroupTbl.
01a,26aug03,yvp	 written.
*/

#ifndef __INCsyscallLibPh
#define __INCsyscallLibPh

/* includes */

#include <vxWorks.h>
#include <syscallLib.h>
#ifndef __WRS_INTERNAL_OFFSETS_ONLY
#include <syscall.h>
#endif

/*
 * Include the architecture-specific definition for SYSCALL_ENTRY_STATE 
 *
 * - NOTE -
 * Whenever a new architectures is implemented it must define a 
 * SYSCALL_ENTRY_STATE structure for itself.
 */

#if     (CPU_FAMILY==PPC)
#include <arch/ppc/syscallPpc.h>
#elif	(CPU_FAMILY==ARM)
#include <arch/arm/syscallArm.h>
#elif	(CPU_FAMILY==MIPS)
#include <arch/mips/syscallMips.h>
#elif	(CPU_FAMILY==SH)
#include <arch/sh/syscallSh.h>
#elif   (CPU_FAMILY==SIMNT)
#include <arch/simnt/syscallSimnt.h>
#elif   (CPU_FAMILY==SIMLINUX)
#include <arch/simlinux/syscallSimlinux.h>
#elif   (CPU_FAMILY==SIMSPARCSOLARIS)
#include <arch/simsolaris/syscallSimsolaris.h>
#elif   (CPU_FAMILY==I80X86)
#ifndef _WRS_CONFIG_LP64
#include <arch/i86/syscallI86.h>
#else
#include <arch/i86/x86_64/syscallX86_64.h>
#endif  /* LP64 */
#elif   (CPU_FAMILY==COLDFIRE)
#include <arch/coldfire/syscallColdfire.h>
#endif  /* CPU_FAMILY */

/* defines */

#define MAX_VALUE(N)	(1 << (N))	 /* Highest number represented by a 
					    bit-field N bits wide */

#define RA_MASK(N)	(MAX_VALUE(N)-1) /* Mask for a right-aligned 
					    bit-field N bits wide */

#define SYSCALL_GROUPS_MAX		MAX_VALUE(SYSCALL_GROUP_NUM_BITS)
#define SYSCALL_ROUTINES_MAX		MAX_VALUE(SYSCALL_ROUTINE_NUM_BITS)

    /* derived bit-field constants and shift counts */

#define SYSCALL_ROUTINE_NO_BIT_END	(SYSCALL_ROUTINE_NUM_BITS - 1)

#define SYSCALL_GROUP_NO_BIT_END	(SYSCALL_GROUP_NO_BIT_START + \
					 SYSCALL_GROUP_NUM_BITS - 1)

#define SYSCALL_ROUTINE_FIELD_MASK	RA_MASK(SYSCALL_ROUTINE_NUM_BITS)

#define SYSCALL_GROUP_FIELD_MASK	(RA_MASK(SYSCALL_GROUP_NUM_BITS) << \
					 SYSCALL_GROUP_NO_BIT_START)

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* typedefs */

/* a group table entry */

typedef struct syscall_group_entry	
    {
    SYSCALL_RTN_TBL_ENTRY * pRoutineTbl;
    int			    numRoutines; 
#ifdef _WRS_CONFIG_LP64
    UINT32		    pad;
#endif
    } SYSCALL_GROUP_ENTRY;

/* externals */

extern SYSCALL_GROUP_ENTRY syscallGroupTbl [];

#ifndef SYSCALL_USER_SP_GET
#define SYSCALL_USER_SP_GET(tid) (char *) \
	(((SYSCALL_ENTRY_STATE *) ((((WIND_TCB *)(tid))->pExcStackBase) - \
				   sizeof(SYSCALL_ENTRY_STATE)))->pUStack)
#endif /* SYSCALL_USER_SP_GET */

#ifndef SYSCALL_USER_PC_GET
#define SYSCALL_USER_PC_GET(tid) (void *) \
	(((SYSCALL_ENTRY_STATE *) ((((WIND_TCB *)(tid))->pExcStackBase) - \
				   sizeof(SYSCALL_ENTRY_STATE)))->pc)
#endif /* SYSCALL_USER_PC_GET */

#ifndef SYSCALL_USER_SCN_GET
#define SYSCALL_USER_SCN_GET(tid) (int) \
	(((SYSCALL_ENTRY_STATE *) ((((WIND_TCB *)(tid))->pExcStackBase) - \
				   sizeof(SYSCALL_ENTRY_STATE)))->scn)
#endif /* SYSCALL_USER_SCN_GET */

/* typedefs */

typedef STATUS (* SYSCALL_ENTRY_HOOK) (const SYSCALL_ENTRY_STATE *);

typedef void   (* SYSCALL_EXIT_HOOK)  (long);

typedef STATUS (* SYSCALL_REGISTER_HOOK) (int, char *, int, 
					  SYSCALL_RTN_TBL_ENTRY **);

extern int			syscallHookTblSize;
extern SYSCALL_ENTRY_HOOK * 	pSyscallEntryHookTbl;
extern SYSCALL_EXIT_HOOK *	pSyscallExitHookTbl;
extern SYSCALL_REGISTER_HOOK *	pSyscallRegisterHookTbl;

/* function declarations */

STATUS syscallLibInit			(const int hookTblSize);
long   syscallDispatch			(SYSCALL_ENTRY_STATE * pState);
void   syscallHookLibInit 		(void);
STATUS syscallRegisterHookAdd		(SYSCALL_REGISTER_HOOK hook,
					 BOOL addToHead);
STATUS syscallRegisterHookDelete	(SYSCALL_REGISTER_HOOK hook);
STATUS syscallEntryHookAdd		(SYSCALL_ENTRY_HOOK hook,
					 BOOL addToHead);
STATUS syscallEntryHookDelete		(SYSCALL_ENTRY_HOOK hook);
STATUS syscallExitHookAdd		(SYSCALL_EXIT_HOOK hook,
					 BOOL addToHead);
STATUS syscallExitHookDelete		(SYSCALL_EXIT_HOOK hook);

void   syscallShowInit			(void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsyscallLibPh */
