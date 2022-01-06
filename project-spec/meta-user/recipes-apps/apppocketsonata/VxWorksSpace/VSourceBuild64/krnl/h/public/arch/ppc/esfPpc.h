/* esfPpc.h - PowerPC exception stack frames */

/*
 * Copyright (c) 1994-1996, 2000-2004, 2008-2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20nov14,ylu  LP64 adaptation to support PPC64.(F2518)
05jul12,cww  Fix _PPC_ESF_ESR macro for PPC465 and PPC476 (WIND00360186)
06apr12,cww  add esr field for PPC4xx
03dec12,pcs  Decouple macro PPC_e500mc for e6500 core.
05jul12,cww  Fix _PPC_ESF_ESR macro for PPC465 and PPC476 (WIND00360186)
06apr12,cww  add esr field for PPC4xx
20aug10,syt  add support for PPC465.
20aug10,x_z  add support for PPC476.
29apr10,pad  Moved extern C statement after include statements.
24nov09,pmr  remove extra word in e500mc ESF
29oct08,pmr  conditionalize SPEFSCR on _WRS_SPE_SUPPORT
11sep08,pmr  Fix WIND00134134
03sep08,pmr  e500mc hard floating point
13feb08,pch  CQ116232: mention DBSR overloading in 4xx ESF comments
23aug04,pch  SPR 78780: split vecOffset into two UINT16's to make space
		 to handle CI frameless nesting case
09jun04,pch  add support for PPC440 with hard FP
12feb04,jtp  Apply _WRS_MMU_CLASS_* macros.
13aug03,mil  Consolidated esr and mcsr as well as dear and mcar for e500.
11nov02,mil  Added E500 registers to ESF.
03oct02,dtr  Adding spefscr register offset to regset in ESF.
01dec03,jtp  PPC440/405 context switching support; size & offset cleanup
09oct03,pcs  Add the context related register offset on exception stack.
14jan03,pch  Add support for 440x5 core (PPC440GX)
22aug01,pch  Replace "sizeof(UINT32)" with SIZ_UINT32 because the
		 assembler barfs on the former.
15aug01,pch  Add PPC440, remove an old "#if 0" block
25oct00,s_m  renamed PPC405 cpu types
31aug00,sm   added cases for PPC405 and PPC405F
04mar96,tam  added support for PPC403. 
20apr95,yao  add padding word that esf stack size are same
		 for all cpu variations.
06oct94,yao  changed to put sp on the top of the stack.
29sep94,yao  fixed register offset on the exception stack in 
		 correct order.
07jul94,yao  written.
*/

#ifndef __INCesfPpch
#define __INCesfPpch

#include "regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * excALib.s treats resumeOffset and vecOffset together as a 32-bit fullword,
 * thereby setting resumeOffset to zero.  The only time when resumeOffset
 * is non-zero is when intCrtEnt detects frameless nesting of a critical
 * interrupt within the first few instructions of a normal event vector; in
 * this case resumeOffset is used to record the offset of the interrupted
 * normal vector so that it can be resumed properly after the critical
 * interrupt has been serviced.  See comments in intCrtEnt for further
 * details.
 *
 * All C code now accesses vecOffset as a 16-bit halfword.  Only assembly
 * code uses resumeOffset.
 */

#ifndef	_ASMLANGUAGE

typedef	struct 
    {
    _RType	spCopy;		/* unused - redundant copy of regSet.gpr[1] */ 
    UINT16	resumeOffset;	/* resume offset for CI frameless nesting */
    UINT16	vecOffset;	/* vector offset */
    UINT32	_errno;		/* error number */

# if     ((CPU == PPC403) || (CPU == PPC405) || (CPU == PPC405F))
    _RType      dear;		/* data exception address register */
    UINT32      bear;           /* bus error address register */
    UINT32      besr;           /* bus error syndrome register, or DBSR */
# elif	((CPU == PPC440) || (CPU == PPC476) || (CPU == PPC465))
    _RType      dear;		/* data exception address register */
#  ifdef  _PPC_MSR_FP
    UINT32      fpcsr;		/* floating-point control and status register */
#  else  /* _PPC_MSR_FP */
    UINT32      pad3;
#  endif /* _PPC_MSR_FP */
    UINT32	mcsr;		/* machine check status reg, ESR, or DBSR */
# elif	(defined (_WRS_CONFIG_PPC_E500))
    _RType      dear;		/* data exception address register and MCAR */
    _RType      esr;            /* exception syndrome register and MCSR/DBSR */
    _RType      iarr;           /* instruction address resume register */
# else	/* CPU == PPC4xx/PPC85xx */
    _RType      dar;		/* data address register */
    UINT32      dsisr;		/* data storage interrupt status register */
    UINT32      fpcsr;		/* floating-point control and status register */
# endif	/* CPU == PPC4xx/PPC85xx */

    REG_SET	regSet;		/* register set */

# if	(CPU == PPC440 && defined(PPC_440x5))
    UINT32	besr;		/* bus error syndrome register */
    UINT32	bear_h;		/* bus error address register (high) */
    UINT32	bear_l;		/* bus error address register (low) */
# else	/* PPC440 && PPC_440x5 */
#  if 	(CPU == PPC405F) || defined (PPC_e500mc) || defined (PPC_e6500)
    UINT32      fpcsr;		/* floating-point control and status register */
#  else   /* CPU == PPC405F */
    UINT32	pad0;
#  endif  /* CPU == PPC405F */
    UINT32	pad1;
#ifndef	_WRS_CONFIG_LP64
    UINT32	pad2;
#endif	/* !_WRS_CONFIG_LP64 */
# endif	/* PPC440 && PPC_440x5 */

#if ((CPU == PPC403) || (CPU == PPC405) || (CPU == PPC405F) || \
     (CPU == PPC440) || (CPU == PPC476) || (CPU == PPC465))
    UINT32	esr;		/* exception syndrome register */
#else /* PPC4xx */
    UINT32	pad4;
#endif /* PPC4xx */
    } ESFPPC;

#endif	/* _ASMLANGUAGE */

/* _PPC_ESF_SIZE provides sizeof(ESFPPC) for assembly language code */
#ifdef	_WRS_CONFIG_LP64
#define _PPC_ESF_SIZE		((4 * _PPC_REG_SIZE) + (2 * SIZ_UINT16) + \
				 (3 * SIZ_UINT32) + _PPC_REG_SET_SIZE)
#else
#define _PPC_ESF_SIZE		(10 * _PPC_REG_SIZE + _PPC_REG_SET_SIZE)
#endif

/* _PPC_ESF_STK_SIZE provides a stack-aligned ESFPPC allocation size */
#define _PPC_ESF_STK_SIZE	((_PPC_ESF_SIZE + _STACK_ALIGN_SIZE - 1) & \
				 ~(_STACK_ALIGN_SIZE - 1))

/* register offset on exception stack */

/* Assembler barfs on sizeof(), so do it this way instead */
#define	SIZ_UINT64	8	/* sizeof(UINT64) */
#define	SIZ_UINT32	4	/* sizeof(UINT32) */
#define	SIZ_UINT16	2	/* sizeof(UINT16) */

#define _PPC_ESF_SP_OFF		(0)
#define _PPC_ESF_VEC_OFF	(_PPC_ESF_SP_OFF + _PPC_REG_SIZE) /* fullword */
#define _PPC_ESF_RES_OFF_H	(_PPC_ESF_VEC_OFF  + 0)		  /* halfword */
#define _PPC_ESF_VEC_OFF_H	(_PPC_ESF_VEC_OFF  + SIZ_UINT16)  /* halfword */
#define _PPC_ESF_ERRNO		(_PPC_ESF_VEC_OFF  + SIZ_UINT32)
#if     ((CPU == PPC403) || (CPU == PPC405) || (CPU == PPC405F))
# define _PPC_ESF_DEAR		(_PPC_ESF_ERRNO    + SIZ_UINT32)
# define _PPC_ESF_BEAR		(_PPC_ESF_DEAR     + _PPC_REG_SIZE)
# define _PPC_ESF_BESR		(_PPC_ESF_BEAR     + SIZ_UINT32)
# define _PPC_ESF_REG_BASE	(_PPC_ESF_BESR     + SIZ_UINT32)
#elif	((CPU == PPC440) || (CPU == PPC476) || (CPU == PPC465))
# define _PPC_ESF_DEAR		(_PPC_ESF_ERRNO    + SIZ_UINT32)
# ifdef  _PPC_MSR_FP
#  define _PPC_ESF_FPCSR	(_PPC_ESF_DEAR     + _PPC_REG_SIZE)
# else  /* _PPC_MSR_FP */
#  define _PPC_ESF_PAD3		(_PPC_ESF_DEAR     + _PPC_REG_SIZE)
# endif /* _PPC_MSR_FP */
# define _PPC_ESF_MCSR		(_PPC_ESF_DEAR     + _PPC_REG_SIZE + SIZ_UINT32)
# define _PPC_ESF_REG_BASE	(_PPC_ESF_MCSR     + SIZ_UINT32)
#elif	(defined (_WRS_CONFIG_PPC_E500))
# define _PPC_ESF_DEAR		(_PPC_ESF_ERRNO    + SIZ_UINT32)
# define _PPC_ESF_ESR		(_PPC_ESF_DEAR     + _PPC_REG_SIZE)
# define _PPC_ESF_IARR		(_PPC_ESF_ESR      + _PPC_REG_SIZE)
# define _PPC_ESF_REG_BASE	(_PPC_ESF_IARR     + _PPC_REG_SIZE)
#else	/* CPU == PPC4xx/PPC85xx */
# define _PPC_ESF_DAR		(_PPC_ESF_ERRNO    + SIZ_UINT32)
# define _PPC_ESF_DSISR		(_PPC_ESF_DAR	   + _PPC_REG_SIZE)
# define _PPC_ESF_FPCSR		(_PPC_ESF_DSISR	   + SIZ_UINT32)
# define _PPC_ESF_REG_BASE	(_PPC_ESF_FPCSR    + SIZ_UINT32)
#endif	/* CPU == PPC4xx/PPC85xx */
#if	(CPU == PPC440 && defined(PPC_440x5))
# define _PPC_ESF_BESR		(_PPC_ESF_REG_BASE + _PPC_REG_SET_SIZE)
# define _PPC_ESF_BEAR_H	(_PPC_ESF_BESR     + SIZ_UINT32)
# define _PPC_ESF_BEAR_L	(_PPC_ESF_BEAR_H   + SIZ_UINT32)
#else	/* PPC440 && PPC_440x5 */
# if	(CPU == PPC405F) || defined (PPC_e500mc) || defined (PPC_e6500)
#  define _PPC_ESF_FPCSR	(_PPC_ESF_REG_BASE + _PPC_REG_SET_SIZE)
#  define _PPC_ESF_PAD1		(_PPC_ESF_FPCSR    + SIZ_UINT32)
# else	/* CPU == PPC405F */
#  define _PPC_ESF_PAD0		(_PPC_ESF_REG_BASE + _PPC_REG_SET_SIZE)
#  define _PPC_ESF_PAD1		(_PPC_ESF_PAD0     + SIZ_UINT32)
# endif	/* CPU == PPC405F */
#ifndef	_WRS_CONFIG_LP64
# define _PPC_ESF_PAD2		(_PPC_ESF_PAD1     + SIZ_UINT32)
#endif	/* !_WRS_CONFIG_LP64 */
#endif 	/* PPC440 && PPC_440x5*/

#if ((CPU == PPC403) || (CPU == PPC405) || (CPU == PPC405F) || 	\
     (CPU == PPC440) || (CPU == PPC476) || (CPU == PPC465))
# ifdef PPC_440x5
#  define _PPC_ESF_ESR		(_PPC_ESF_BEAR_L   + SIZ_UINT32)
# else
#  define _PPC_ESF_ESR		(_PPC_ESF_PAD2	   + SIZ_UINT32)
# endif
#else
# define _PPC_ESF_PAD4		(_PPC_ESF_PAD2	   + SIZ_UINT32)
#endif

#define _PPC_ESF_R(n)		(_PPC_ESF_REG_BASE + (n) * _PPC_REG_SIZE)

#define _PPC_ESF_MSR		_PPC_ESF_R(GREG_NUM)
#define _PPC_ESF_LR		_PPC_ESF_R(GREG_NUM + 1)
#define _PPC_ESF_CTR		_PPC_ESF_R(GREG_NUM + 2)
#define _PPC_ESF_PC		_PPC_ESF_R(GREG_NUM + 3)
#define _PPC_ESF_CR		_PPC_ESF_R(GREG_NUM + 4)
#define _PPC_ESF_XER		(_PPC_ESF_CR + _SIZE_OF_LONG)
#if	(CPU == PPC601)
#define _PPC_ESF_MQ		(_PPC_ESF_XER + 4)	
#else	/* (CPU == PPC601) */
#define _PPC_ESF_PG_TBL_PTR     (_PPC_ESF_XER + _SIZE_OF_LONG)
#endif	/* (CPU == PPC601) */

#if	defined(_WRS_MMU_CLASS_SR_REGS)
#define _PPC_ESF_SC_SR_TBL_PTR  (_PPC_ESF_PG_TBL_PTR + 4)
#define _PPC_ESF_SR_TBL_PTR     (_PPC_ESF_SC_SR_TBL_PTR + 4)
#elif	defined(_WRS_MMU_CLASS_PID_REG)
#define _PPC_ESF_ASID           (_PPC_ESF_PG_TBL_PTR + _SIZE_OF_LONG)
#if	defined(_WRS_SPE_SUPPORT)
#define _PPC_ESF_SPEFSCR	(_PPC_ESF_ASID + 4)	
#endif	/* _WRS_SPE_SUPPORT */
#endif	/* _WRS_MMU_CLASS_* */

#define _PPC_ESF_R0		_PPC_ESF_R(0)
#define _PPC_ESF_R1		_PPC_ESF_R(1)
#define _PPC_ESF_R2		_PPC_ESF_R(2)
#define _PPC_ESF_R3		_PPC_ESF_R(3)
#define _PPC_ESF_R4		_PPC_ESF_R(4)
#define _PPC_ESF_R5		_PPC_ESF_R(5)
#define _PPC_ESF_R6		_PPC_ESF_R(6)
#define _PPC_ESF_R7		_PPC_ESF_R(7)
#define _PPC_ESF_R8		_PPC_ESF_R(8)
#define _PPC_ESF_R9		_PPC_ESF_R(9)
#define _PPC_ESF_R10		_PPC_ESF_R(10)
#define _PPC_ESF_R11		_PPC_ESF_R(11)
#define _PPC_ESF_R12		_PPC_ESF_R(12)
#define _PPC_ESF_R13		_PPC_ESF_R(13)
#define _PPC_ESF_R14		_PPC_ESF_R(14)
#define _PPC_ESF_R15		_PPC_ESF_R(15)
#define _PPC_ESF_R16		_PPC_ESF_R(16)
#define _PPC_ESF_R17		_PPC_ESF_R(17)
#define _PPC_ESF_R18		_PPC_ESF_R(18)
#define _PPC_ESF_R19		_PPC_ESF_R(19)
#define _PPC_ESF_R20		_PPC_ESF_R(20)
#define _PPC_ESF_R21		_PPC_ESF_R(21)
#define _PPC_ESF_R22		_PPC_ESF_R(22)
#define _PPC_ESF_R23		_PPC_ESF_R(23)
#define _PPC_ESF_R24		_PPC_ESF_R(24)
#define _PPC_ESF_R25		_PPC_ESF_R(25)
#define _PPC_ESF_R26		_PPC_ESF_R(26)
#define _PPC_ESF_R27		_PPC_ESF_R(27)
#define _PPC_ESF_R28		_PPC_ESF_R(28)
#define _PPC_ESF_R29		_PPC_ESF_R(29)
#define _PPC_ESF_R30		_PPC_ESF_R(30)
#define _PPC_ESF_R31		_PPC_ESF_R(31)

#define	_PPC_ESF_P0		_PPC_ESF_R3
#define	_PPC_ESF_P1		_PPC_ESF_R4
#define	_PPC_ESF_P2		_PPC_ESF_R5
#define	_PPC_ESF_P3		_PPC_ESF_R6
#define	_PPC_ESF_P4		_PPC_ESF_R7
#define	_PPC_ESF_P5		_PPC_ESF_R8
#define	_PPC_ESF_P6		_PPC_ESF_R9
#define	_PPC_ESF_P7		_PPC_ESF_R10

#define	_PPC_ESF_T0		_PPC_ESF_R14
#define	_PPC_ESF_T1		_PPC_ESF_R15
#define	_PPC_ESF_T2		_PPC_ESF_R16
#define	_PPC_ESF_T3		_PPC_ESF_R17
#define	_PPC_ESF_T4		_PPC_ESF_R18
#define	_PPC_ESF_T5		_PPC_ESF_R19
#define	_PPC_ESF_T6		_PPC_ESF_R20
#define	_PPC_ESF_T7		_PPC_ESF_R21
#define	_PPC_ESF_T8		_PPC_ESF_R22
#define	_PPC_ESF_T9		_PPC_ESF_R23
#define	_PPC_ESF_T10		_PPC_ESF_R24
#define	_PPC_ESF_T11		_PPC_ESF_R25
#define	_PPC_ESF_T12		_PPC_ESF_R26
#define	_PPC_ESF_T13		_PPC_ESF_R27
#define	_PPC_ESF_T14		_PPC_ESF_R28
#define	_PPC_ESF_T15		_PPC_ESF_R29
#define	_PPC_ESF_T16		_PPC_ESF_R30
#define	_PPC_ESF_T17		_PPC_ESF_R31

#define _PPC_ESF_SP		_PPC_ESF_R1	

#ifdef	_AIX_TOOL
#define _PPC_ESF_RTOC		_PPC_ESF_R(2)
#endif	/* _AIX_TOOL */

#ifdef __cplusplus
}
#endif

#endif /* __INCesfPpch */
