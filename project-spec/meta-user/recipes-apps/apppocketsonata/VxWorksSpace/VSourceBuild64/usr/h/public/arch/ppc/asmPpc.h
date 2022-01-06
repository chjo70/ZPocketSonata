/* asmPpc.h - PowerPC assembler definitions header file */

/* 
 * Copyright 1984-2007, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20jan15,my_  added LP64 support(F2518)
03mar14,gvm  added macros to support SVr4 shared libraries ABI
05oct07,kk   added macros to support SHL GOT table access
19jul06,pch  move kernel-only definitions to kernel-only archPpc.h file
06jun06,jpb  Updated for POSIX namespace conformance.  
		 Changed C preprocessor macro CPU to _VX_CPU.
01nov04,pch  SPR 83004: move SPRG[4-7] definitions from asmPpc.h to ppc405.h
10dec03,pch  TEMPORARY HACK for msync/mbar in PPC440gnu
03dec03,jtp  Add MMU_MASK operation
09sep03,yvp  Removed definition of the SYSCALL_PROLOG macro.
03sep03,yvp  Added system call trap stub definition.
12dec02,pch  Add generic PPC32 support
26mar02,pcs  Add defines for I & D BAT's 4-7.
02may01,pch  Documentation cleanup
25oct00,s_m  renamed PPC405 cpu types
12jun00,alp  Added PPC405 Support
18mar97,tam  made INT_MASK definition conditional.
08apr96,tpr  move implementation specific definition in ppcXXX.h.
04mar96,tam  added some SPR definitions for the PPC403.
26feb96,kkk  added HID0 for PPC601.
14feb96,tpr  added PPC604 support.
09feb95,yao  added RFCI, MTBESR_P0 macro for PPC403.
30jan95,yao  added DBCR for PPC403.  fixed mtdcr macros for PPC403.
06jan95,vin  corrected HID0 (was 8, now 1008).
15nov94,caf  moved register defines to toolPpc.h.
04nov94,yao  changed PPC403GA to PPC403.  moved tool related macros
		 to tools.h.
25may94,yao  written.
*/

#ifndef __INCasmPpch
#define __INCasmPpch

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TEMPORARY HACK for msync/mbar in PPC440gnu */
#if	(_VX_CPU == _VX_PPC440 && defined(_GNU_TOOL))
#define	msync	sync
#define	mbar	eieio
#endif

/* special purpose register encoding */

#define XER		1	/* external exception register */
#define LR		8	/* link register (return address) */
#define	CTR		9	/* counter register */

#define	BO_dCTR_NZERO_AND_NOT	0
#define BO_dCTR_ZERO_AND_NOT	2
#define BO_IF_NOT		4
#define BO_dCTR_ZERO_AND	10
#define BO_IF			12
#define BO_dCTR_NZERO		16
#define BO_dCTR_ZERO		18
#define BO_ALWAYS		20
#define CR0_LT			8

/* macros for globals via the Global Offset table for SHLs in assembly code */

#ifndef	_WRS_KERNEL
# ifdef	__SO_PICABIRTP__
/*
 * Shared-library globals must be accessed via the Global Offset
 * Table for the current instance (attachment) of the shared library.
 * Used by vxAtomicALib.s.
 */

#  ifdef _WRS_CONFIG_LP64
#define	_PPC_RTP_GLOBAL_GET(globalName, reg,temp)		     \
	lis	 reg, HIT(__GOTT_BASE__);				     \
	ori	 reg, reg, HIR(__GOTT_BASE__);				     \
    rldicr reg,reg,32,31;                            \
	oris reg, reg, HI(__GOTT_BASE__);				     \
	ld	 reg, LO(__GOTT_BASE__)(reg);	/* reg = &GOT[] */	     \
	ld	 reg, __GOTT_INDEX__(reg);	/* reg = &GOT[myInstance] */ \
	ld	 reg, globalName@got(reg);	/* reg = &globalName */	     \
	lwz	 reg, 0(reg)			/* reg = globalName */
#  else
#define	_PPC_RTP_GLOBAL_GET(globalName, reg,temp)		     \
	lis	reg, HIADJ(__GOTT_BASE__);				     \
	lwz	reg, LO(__GOTT_BASE__)(reg);	/* reg = &GOT[] */	     \
	lwz	reg, __GOTT_INDEX__(reg);	/* reg = &GOT[myInstance] */ \
	lwz	reg, globalName@got(reg);	/* reg = &globalName */	     \
	lwz	reg, 0(reg)			/* reg = globalName */
#  endif /* _WRS_CONFIG_LP64 */
# elif	defined(__SO_PICABILINUX__)
#  ifdef _WRS_CONFIG_LP64
#define	_PPC_RTP_GLOBAL_GET(globalName, reg, temp)			    \
	mflr temp;		/* save incoming lr in temp */			\
	bcl	20,31,1f;											\
1:															\
	mflr reg;		/* reg now has &L1 */					\
	mtlr temp;												\
	lis  reg,reg,(_GLOBAL_OFFSET_TABLE_-1b)@highest;			\
	ori  reg,reg,(_GLOBAL_OFFSET_TABLE_-1b)@higher;			\
    rldicr reg,reg,32,31;                            \
	oris reg,reg,(_GLOBAL_OFFSET_TABLE_-1b)@h;			\
	ori  reg,reg,(_GLOBAL_OFFSET_TABLE_-1b)@l;			\
	ld	 reg, globalName@got(reg);	/* reg = &globalName */	\
	lwz	 reg, 0(reg)			/* reg = globalName */
#  else
#define	_PPC_RTP_GLOBAL_GET(globalName, reg, temp)			    \
	mflr temp;		/* save incoming lr in temp */			\
	bcl	20,31,1f;											\
1:															\
	mflr reg;		/* reg now has &L1 */					\
	mtlr temp;												\
	addis reg,reg,(_GLOBAL_OFFSET_TABLE_-1b)@ha;			\
	addi  reg,reg,(_GLOBAL_OFFSET_TABLE_-1b)@l;			\
	lwz	reg, globalName@got(reg);	/* reg = &globalName */	\
	lwz	reg, 0(reg)			/* reg = globalName */
#  endif /*_WRS_CONFIG_LP64 */
# else	/* __SO_PICABIRTP__ */
#  ifdef _WRS_CONFIG_LP64
#define	_PPC_RTP_GLOBAL_GET(globalName, reg,temp)	\
	lis	 reg, HIT(globalName);		\
	ori	 reg, reg, HIR(globalName);		\
    rldicr reg,reg,32,31;                            \
	oris reg, reg, HI(globalName);		\
	lwz	 reg, LO(globalName)(reg);
#  else
#define	_PPC_RTP_GLOBAL_GET(globalName, reg,temp)	\
	lis	reg, HIADJ(globalName);		\
	lwz	reg, LO(globalName)(reg);
#  endif /* _WRS_CONFIG_LP64 */
# endif	/* __SO_PICABIRTP__ */
#endif	/* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCasmPpch */
