/* excPpcLib.h - PowerPC exception library header */

/*
 * Copyright (c) 1984-2008, 2010-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
11sep15,d_l  remove COMPAT69 condition for _EXC_SAVE_AREA_OFF macros.
11aug15,syt  added _EXC_SAVE_AREA_OFF_LR and _EXC_SAVE_AREA_OFF_DEAR.(V7PRO-2297)
06jul15,w_x  Update exception handling with regard to SMP/r13 usage (F2518) 
12dec14,w_x  Update _PPC_IMISS_SAVE_AREA/_PPC_DMISS_SAVE_AREA for PPC64 (F2518)
20nov14,ylu  LP64 adaptation to support PPC64.(F2518)
12oct14,syt  extended the _EXC_SAVE_AREA_SIZE and adjusted _EXC_SAVE_AREA_SHIFT.(F2505)
01oct14,h_k  changed the offset comments in EXC_INFO to relative.
             added offset comments to pad5 and total size in EXC_INFO.
12mar14,x_z  added _EXC_SAVE_AREA_SIZE and adjusted _EXC_SAVE_AREA_SHIFT. 
             (VXW7-2538)
14jan14,ylu  added _EXC_SAVE_AREA_OFF_XXX macro for excSaveArea and mchSaveArea.
09apr13,d_l  fix build warnings. (WIND00358283)
26mar13,h_k  added missing fpcsr for PPC465.
21feb13,h_k  added _EXC_ALTIVEC_UNAVAILABLE and _EXC_ALTIVEC_ASSIST for
             e6500. (WIND00404757)
20nov12,pcs  Fix compiler warning corresponding to macro _OP.
05sep12,h_k  moved _PPC_IMISS_SAVE_AREA and _PPC_DMISS_SAVE_AREA
             from mmuE500ALib.s.
06apr12,cww  add esr for PPC4xx
30aug12,jpb  Renamed _WRS_CONFIG_MILS_VDK_1_1 to _WRS_CONFIG_MILS_VBI.
28nov11,h_k  updated comments for offset in EXC_INFO.
04nov11,kab  Fix multiple def of _OP compiler warnings
15jun11,kab  Add MILS VDK support
03may11,syt  Add support for PPC465.
08oct10,x_z  Rework mcsr field of EXC_INFO for PPC476.
20aug10,x_z  Add support for PPC476.
22mar10,wap  Add alternate direct interrupt vector for e500mc guest mode
03sep08,pmr  e500mc hard floating point
05jan07,pch  Add _EXC_OFF_SYSTIMER (abstraction of _DECR and _PIT);
	 renumber history from 10dec03.
01jun06,pch  consolidate vector offset definitions in excPpcLib.h
15jul05,mil  General clean up.
22apr04,to   PPC970 cleanup
18mar04,rec  merge PPC970 changes
26aug04,pch  SPR 78780: add notes concerning vector locations.
09jun04,pch  add support for PPC440 with hard FP
03may04,dtr  Add exception message exchandler install struct.
24mar04,dtr  Adding in new struct to support generic TLB and parity
	 exception handlers.
25feb04,pch  SPR 92351: define _EXC_OFF_END for all PPC
07nov02,mil  Added support for PPCE500.
10dec03,jtp  Code inspection update: 405 TLB Miss handler relocation
26nov03,pes  Correct _WRS_IS_SUPV_EXC macro.
18nov03,pes  Add _WRS_IS_SUPV_EXC macro.
10jun03,pch  move 440x5 MC handler & save area to not clobber bootline
08jan03,pch  Add support for 440x5 core (PPC440GX)
13nov01,yvp  Changed _EXC_NEW_OFF_FIT to 0x01180 to make room for extended
	 vectors.
27aug01,pch  Only define _EXC_INFO_* if the corresponding members of
	 EXC_INFO exist; utilize IVPR/IVOR where available.
15aug01,pch  Add PPC440; cleanup
30nov00,s_m  fixed bus error handling for 405
25oct00,s_m  renamed PPC405 cpu types
13oct00,sm   removed bear and besr from EXC_INFO for 405 since it doesn't
	 have these regs
30aug00,sm   added cases for PPC405 and PPC405F
12mar99,zl   added PowerPC 509 and PowerPC 555 support
18aug98,tpr  added PowerPC EC 603 support.
06aug97,tam  added macro _EXC_NEW_OFF_PIT and _EXC_NEW_OFF_FIT.
20mar97,tam  added prototype for excIntCrtConnect (PPC403 specific).
26feb97,tam  added support for the 403GC and 403GCX cpus.
20apr96,tpr  added excConnect(), excIntConnect(),excVecSet(),excVecGet(),
	 excVecBaseSet() and excVecBaseGet() prototype.
04mar96,tam  added PPC403 support.
14feb96,tpr  added PPC604 support.
09feb95,yao  added excCrtStub () for PPC403.
07nov94,yao  changed PPC403GA to PPC403.  cleanup.
07jul94,yao  written.
*/

#ifndef __INCexcPcLibh
#define __INCexcPcLibh

#ifdef __cplusplus
extern "C" {
#endif

/* exception information valid bits */

#define _EXC_INFO_VEC	0x001	/* vector offset valid */
#define _EXC_INFO_CIA	0x002	/* curent exception address(pc) valid */
#define _EXC_INFO_MSR	0x004	/* machine status register valid */

#if	((CPU == PPC403) || (CPU == PPC405) || (CPU == PPC405F) || \
	 (CPU == PPC440) || (defined (_WRS_CONFIG_PPC_E500)) || (CPU == PPC476) || (CPU == PPC465))
#define _EXC_INFO_DEAR	0x008	/* data exception address register valid */
#else	/* CPU == PPC4xx, PPCE500 */
#define _EXC_INFO_DAR	0x008	/* data access register valid */
#endif	/* CPU == PPC4xx, PPCE500 */

#define _EXC_INFO_XER	0x010	/* fixed point register valid */
#define _EXC_INFO_CR	0x020	/* condition register valid */

#if	((CPU == PPC403) || (CPU == PPC405))
#define _EXC_INFO_BEAR	0x040	/* bus error address register valid */
#define _EXC_INFO_BESR	0x080	/* bus error syndrome register valid */
#define _EXC_INFO_ESR	0x100	/* error syndrome register valid */
#elif	(CPU == PPC405F)
	/* This setting of _EXC_INFO_BEAR is a change from that used in
	 * the 405F release, where it was the same as _EXC_INFO_FPCSR
	 * (clearly broken).
	 */
#define _EXC_INFO_FPCSR	0x040	/* fp status register valid */
#define _EXC_INFO_BEAR	0x080	/* bus error address register valid */
#define _EXC_INFO_ESR	0x100	/* error syndrome register valid */
#elif	((CPU == PPC440) || (CPU == PPC476) || (CPU == PPC465))
	/* Just padding for the 440, unless it has hard FP or is an x5. */
# ifdef  _PPC_MSR_FP
# define _EXC_INFO_FPCSR 0x040	/* fp status register valid */
# endif /* _PPC_MSR_FP */
# ifdef	PPC_440x5
# define _EXC_INFO_MCSR	0x080	/* machine check status register valid */
# define _EXC_INFO_BESR	0x100	/* bus error syndrome register valid */
# define _EXC_INFO_BEAR	0x200	/* bus error address register valid */
# endif	/* PPC_440x5 */
#define _EXC_INFO_ESR	0x400	/* error syndrome register valid */
#elif	(defined (_WRS_CONFIG_PPC_E500))
#ifdef _WRS_SPE_SUPPORT
#define _EXC_INFO_SPEFSCR	0x040	/* SPE fp status valid */
#else
#define _EXC_INFO_FPCSR	0x040	/* fp status register valid */
#endif /* _WRS_SPE_SUPPORT */
#define _EXC_INFO_ESR           0x080   /* exception syndrome valid */
#define _EXC_INFO_MCSR          0x100   /* machine chk syndrome valid */
#else	/* CPU == PPC4xx */
#define _EXC_INFO_FPCSR	0x040	/* fp status register valid */
#define _EXC_INFO_DSISR	0x080	/* data storage interrupt status reg valid */
#endif	/* CPU == PPC4xx */

#define _EXC_INFO_NIA	0x8000	/* pc saved in cia is nia */

#define _EXC_INFO_DEFAULT	(_EXC_INFO_VEC|_EXC_INFO_CIA|_EXC_INFO_MSR| \
				 _EXC_INFO_CR)

#ifndef _ASMLANGUAGE

typedef struct
    {
    UINT32	valid;		/* 0x00: indicators that following fields
				 *       are valid */
    UINT32	vecOff;		/* 0x04: vector offset */
    _RType	cia;		/* 0x08: save/restore reg0 - exception
				 *       address */
    _RType	msr;		/* 0x0c: save/restore register1 - msr */

#ifdef	_EXC_INFO_DEAR
    _RType	dear;		/* data exception address register */
				/* 440x5 MC uses this for bear_l */
#else	/* _EXC_INFO_DEAR */
    _RType	dar;		/* 0x10: data access register */
#endif	/* _EXC_INFO_DEAR */

    ULONG       cr;		/* 0x14: condition register */
    ULONG	xer;		/* 0x18: fixed point exception reg */
				/* 440x5 MC uses this for bear_h */
#if ((CPU == PPC403) || (CPU == PPC405))
    UINT32	bear;		/* bus error address register */
    UINT32	besr;		/* bus error syndrome register */
    /* XXX - handling of bus errors is implementation specific on the PPC405 */
#elif (CPU == PPC405F)
    UINT32	fpcsr;		/* floating point status reg */
    UINT32	bear;
#elif (CPU == PPC440)
    UINT32	pad3;		/* 440x5 MC uses this for besr */
    			/* 440 w/ FPU uses it for fpcsr unless handling an MC */
# if defined(PPC_440x5)
    UINT32	mcsr;
# else /* PPC_440x5 */
    UINT32	pad4;
# endif /* PPC_440x5 */
#elif ((CPU == PPC465) || (CPU == PPC476))
    UINT32	fpcsr;		/* floating point status reg */
    UINT32	mcsr;
#elif (defined (_WRS_CONFIG_PPC_E500) || defined (_WRS_CONFIG_LP64))        	/* excluding MCSR */
# ifdef _WRS_SPE_SUPPORT
    UINT32	spefscr;	/* SPE float-pt status reg */
# else
    _RType	fpcsr;		/* floating point status reg */
# endif
    _RType	mcsr;		/* MCSR syndrome reg */
#else	/* CPU == PPC4xx */
    UINT32	fpcsr;		/* 0x1c: floating point status reg */
    UINT32	dsisr;		/* 0x20: data storage interrupt
				 * status reg */
#endif	/* CPU == PPC4xx */

#if ((CPU == PPC403) || (CPU == PPC405) || (CPU == PPC405F) || \
     (CPU == PPC440) || (CPU == PPC476) || (CPU == PPC465) || defined (_WRS_CONFIG_LP64) || (defined (_WRS_CONFIG_PPC_E500)))
    UINT32	esr;		/* exception syndrome register */
#else /* PPC4xx */
    ULONG	pad5;
#endif /* PPC4xx */
    } EXC_INFO;			/* 0x28: total size */

#define _WRS_IS_SUPV_EXC() \
    (((excInfo.msr & _PPC_MSR_PR) == _PPC_MSR_PR) ? FALSE : TRUE)

typedef struct genericLayeredExcInstallDesc {
    UINT32      excOffset;
    UINT32      errExcOffset;
    VOIDFUNCPTR funcStart;
    VOIDFUNCPTR funcEnd;
    char        * hdlrCodeBase;
    char        * hdlrBase;
    BOOL        forceBase;
    char        * excMsg;
} GENERIC_LAYERED_EXC_INSTALL_DESC;

STATUS genericLayeredExcHdlrInstall (
    GENERIC_LAYERED_EXC_INSTALL_DESC * installDesc);

#endif 	/* _ASMLANGUAGE */

#define _EXC_CODE_SIZE	16	/* size of exc code */

#define EXC_VEC_LOW	0x00000	/* lowest vector entry */
#define EXC_VEC_HIGH	0x02fff	/* highest vector entry */

#define _PPC_EXC_VEC_BASE_LOW	0x00000000
#define _PPC_EXC_VEC_BASE_HIGH	0xfff00000

/* exception vector offset */

#ifdef	IVPR
/*
 * This processor implements the Book E Interrupt Vector Prefix Register
 * and Interrupt Vector Offset Registers, instead of the Exception Vector
 * Prefix Register used (with fixed offsets) in older designs.  The new
 * architecture enables us to locate exception vectors "anywhere".
 *
 * NOTE:  The frameless nesting code in intALib.s requires that "normal"
 * (as opposed to "critical") vectors on processors which implement critical
 * interrupts be at addresses divisible by 0x0080.
 */
#define	_EXC_OFF_CRTL		0x0100	/* Critical Input */
#define	_EXC_OFF_MACH		0x0200	/* Machine Check */
#define	_EXC_OFF_DATA		0x0300	/* Data Storage */
#define	_EXC_OFF_INST		0x0400	/* Instruction Storage */
#define	_EXC_OFF_INTR		0x0500	/* External Input */
#define	_EXC_OFF_ALIGN		0x0600	/* Alignment */
#define	_EXC_OFF_PROG		0x0700	/* Program */
#define	_EXC_OFF_FPU		0x0800	/* Floating Point Unavailable */
#define	_EXC_OFF_SYSCALL	0x0900	/* System Call */
#define	_EXC_OFF_APU		0x0a00	/* Auxiliary Processor Unavailable */
#define	_EXC_OFF_DECR		0x0b00	/* Decrementer */
#define	_EXC_OFF_FIT		0x0c00	/* Fixed Interval Timer */
#define	_EXC_OFF_WD		0x0d00	/* Watchdog Timer */
#define	_EXC_OFF_DATA_MISS	0x0e00	/* Data TLB Error */
#define	_EXC_OFF_INST_MISS	0x0f00	/* Instruction TLB Error */
#define	_EXC_OFF_DBG		0x1000	/* Debug exception */
#if (defined (_WRS_CONFIG_PPC_E500))
#ifdef _WRS_SPE_SUPPORT
#define _EXC_OFF_SPE		0x1100	/* SPE */
#define _EXC_OFF_VEC_DATA	0x1200	/* vect fp data */
#define _EXC_OFF_VEC_RND	0x1300	/* vect fp round */
#elif	defined(_WRS_ALTIVEC_SUPPORT)
#define _EXC_ALTIVEC_UNAVAILABLE 0x1100	/* altivec unavailable */
#define _EXC_ALTIVEC_ASSIST	0x1200	/* altivec assist */
#endif /* _WRS_SPE_SUPPORT */
#define _EXC_OFF_PERF_MON	0x1400	/* performance monitor */
#define	_EXC_OFF_L1_PARITY     	0x1500	/* modify IVOR1 here for L1 parity */
#if defined(_WRS_CONFIG_WRHV_GUEST) && !defined(_WRS_CONFIG_MILS_VBI)
#define _EXC_OFF_DIRECT_INTR	0x2000
#define _EXC_OFF_END		0x2100
#else /* _WRS_CONFIG_WRHV_GUEST && !_WRS_CONFIG_MILS_VBI */
#define	_EXC_OFF_END		0x1600	/* end of vectors */
#endif /* _WRS_CONFIG_WRHV_GUEST */
#else	/* PPCE500 */
#define	_EXC_OFF_END		0x1100	/* end of vectors */
#endif	/* PPCE500 */

#if (defined (_WRS_CONFIG_PPC_E500)) && defined(_WRS_CONFIG_SMP)
#ifdef	PPC_e6500
/* use 0x2400-0x2Bff for ITLB miss temp storage area for upto 32 cores */

#define _PPC_IMISS_SAVE_AREA	0x2400

/* use 0x2C00-0x33ff for DTLB miss temp storage area for upto 32 cores */

#define _PPC_DMISS_SAVE_AREA	0x2C00
#else
/* use 0x1d00-0x20ff for ITLB miss temp storage area for upto 8 cores */

#define _PPC_IMISS_SAVE_AREA	0x1d00

/* use 0x2100-0x24ff for DTLB miss temp storage area for upto 8 cores */

#define _PPC_DMISS_SAVE_AREA	0x2100
#endif	/* PPC_e6500 */
#endif	/* defined (_WRS_CONFIG_PPC_E500) && _WRS_CONFIG_SMP */

#if ((defined PPC_440x5) || (CPU == PPC465))
/*
 * Put the handler for the 440x5 core's recoverable Machine Checks at 24KB,
 * and its save area at 26KB, so they can be in a different page than the
 * other handlers.  (16KB -- 0x4000 -- is already in use for the bootline,
 * SM anchor, and message area.)  Unrecoverable Machine Checks will continue
 * to be serviced by the previous handler at 0x0200.
 */
#define	_EXC_OFF_MCRECOV	0x6000	/* recoverable Machine Check */
#define	_EXC_OFF_MCHSA		0x6800	/* Machine Check Handler Save Area */
#endif	/* PPC_440x5 || PPC465 */

/* Mappings between vector names and corresponding IVORs, for excALib.s */
#define	IVOR0_VAL   _EXC_OFF_CRTL	/* Critical Input */
#if ((defined  PPC_440x5) || (CPU == PPC465))
#define	IVOR1_VAL   _EXC_OFF_MCRECOV	/* recoverable Machine Check */
#else	/* PPC_440x5 || PPC465 */
#define	IVOR1_VAL   _EXC_OFF_MACH	/* Machine Check */
#endif	/* PPC_440x5 || PPC465 */
#define	IVOR2_VAL   _EXC_OFF_DATA	/* Data Storage */
#define	IVOR3_VAL   _EXC_OFF_INST	/* Instruction Storage */
#define	IVOR4_VAL   _EXC_OFF_INTR	/* External Input */
#define	IVOR5_VAL   _EXC_OFF_ALIGN	/* Alignment */
#define	IVOR6_VAL   _EXC_OFF_PROG	/* Program */
#define	IVOR7_VAL   _EXC_OFF_FPU	/* Floating Point Unavailable */
#define	IVOR8_VAL   _EXC_OFF_SYSCALL	/* System Call */
#define	IVOR9_VAL   _EXC_OFF_APU	/* Auxiliary Processor Unavailable */
#define	IVOR10_VAL  _EXC_OFF_DECR	/* Decrementer */
#define	IVOR11_VAL  _EXC_OFF_FIT	/* Fixed Interval Timer */
#define	IVOR12_VAL  _EXC_OFF_WD		/* Watchdog Timer */
#define	IVOR13_VAL  _EXC_OFF_DATA_MISS	/* Data TLB Error */
#define	IVOR14_VAL  _EXC_OFF_INST_MISS	/* Instruction TLB Error */
#define	IVOR15_VAL  _EXC_OFF_DBG	/* Debug exception */

#ifdef	_WRS_CONFIG_PPC_ALTIVEC
#define IVOR32_VAL  _EXC_ALTIVEC_UNAVAILABLE /* altivec unav */
#define IVOR33_VAL  _EXC_ALTIVEC_ASSIST /* altivec asst */
#endif	/* _WRS_CONFIG_PPC_ALTIVEC */

#ifdef _WRS_SPE_SUPPORT
#define IVOR32_VAL  _EXC_OFF_SPE	/* SPE */
#define IVOR33_VAL  _EXC_OFF_VEC_DATA	/* vect fp data */
#define IVOR34_VAL  _EXC_OFF_VEC_RND	/* vect fp round */
#endif /* _WRS_SPE_SUPPORT */

#ifdef _WRS_CONFIG_PPC_E500
#define IVOR35_VAL  _EXC_OFF_PERF_MON	/* performance monitor */
#endif  /* CPU == PPC85xx */

#else	/* IVPR */

#define _EXC_OFF_RES0	 	0x00000		/* reserved */
#define _EXC_OFF_RESET	 	0x00100		/* system reset */
#define _EXC_OFF_MACH	 	0x00200		/* machine check */
#define _EXC_OFF_DATA	 	0x00300		/* data access */
#define _EXC_OFF_INST	 	0x00400		/* instruction access */
#define _EXC_OFF_INTR	 	0x00500		/* external interrupt */
#define _EXC_OFF_ALIGN	 	0x00600		/* alignment */
#define _EXC_OFF_PROG	 	0x00700		/* program */
#define _EXC_OFF_FPU	 	0x00800		/* floating point unavailable */
#define _EXC_OFF_DECR	 	0x00900		/* decrementer */
#define _EXC_OFF_RES1	 	0x00a00		/* reserved */
#define _EXC_OFF_RES2	 	0x00b00		/* reserved */
#define _EXC_OFF_SYSCALL 	0x00c00		/* system call */
#define _EXC_OFF_TRACE	 	0x00d00		/* trace */
#define _EXC_OFF_RES3	 	0x00e00		/* reserved */
						/* exception for PPC601) */
# if	(CPU == PPC860)
#define _EXC_OFF_SW_EMUL	0x01000		/* Software Emulation */
#define _EXC_OFF_INST_MISS	0x01100		/* Instruction TLB Miss */
#define _EXC_OFF_DATA_MISS	0x01200		/* Data TLB Miss */
#define _EXC_OFF_INST_ERROR	0x01300		/* Instruction TLB Error */
#define _EXC_OFF_DATA_ERROR	0x01400		/* Data TLB Error */
#define _EXC_OFF_DATA_BKPT	0x01c00		/* Data Breakpoint */
#define _EXC_OFF_INST_BKPT	0x01d00		/* Instruction Breakpoint */
#define	_EXC_OFF_PERI_BKPT	0x01e00		/* Peripheral Breakpoint */
#define _EXC_OFF_NM_DEV_PORT	0x01f00		/* Non Maskable Develop. Port */
#define	_EXC_OFF_END		0x02000	/* end of vectors */
# endif	/* (CPU == PPC860) */

# if	(CPU == PPC970)
#define _EXC_OFF_DATA_SEG	0x00380	/* data segment fault */
#define _EXC_OFF_INST_SEG	0x00480	/* instruction segment fault */
#define _EXC_OFF_HYPV_DECR	0x00980	/* hypervisor decrementer */
#define _EXC_OFF_INST_BRK	0x01300	/* instruction breakpoint */
#define _EXC_OFF_SYS_MNG	0x01400	/* system management exception */
#define _EXC_OFF_SOFT_PATCH	0x01500	/* soft patch */
#define _EXC_OFF_MAINTENANCE	0x01600	/* maintenance */
#define _EXC_OFF_VMX_ASSIST	0x01700	/* VMX assist */
#define _EXC_OFF_THERMAL	0x01800	/* thermal interrupt */
#define _EXC_OFF_INSTRUMENT	0x02000	/* instrumentation interrupt */
#define _EXC_OFF_END		0x02100	/* end of vectors */
# endif	/* (CPU == PPC970) */

# if	((CPU == PPC604) || (CPU == PPC970))
#define _EXC_OFF_PERF		0x00f00	/* performance monitor */
#define	_EXC_OFF_PERF_MON	_EXC_OFF_PERF		/* variant spelling */
#define	_EXC_ALTIVEC_UNAVAILABLE    0x00f20	/* altivec unavailable */
/*
 * the PERF excExtConnectCode stub (extended vector) won't fit at the
 * assigned location 0xf00 because _EXC_ALTIVEC_UNAVAILABLE is at 0x0f20,
 * so we need to put it where we've got some available space and jump
 * to it from _EXC_OFF_PERF.  The stub being 22 long words max currently
 * (including 64-bit fixup and extended vectors), 0x0f80 - 0x0f20
 * = 0x60 = 96 >= 88 = 22 * 4 has enough room for _EXC_ALTIVEC_UNAVAILABLE.
 */
#define	_EXC_NEW_OFF_PERF	0x00f80	/* relocated perf monitor */
# endif	/* 604/970 */

# if	(CPU == PPC509)
#undef  _EXC_OFF_DATA
#undef  _EXC_OFF_INST
#undef  _EXC_OFF_RES3
#define _EXC_OFF_FPA	 	0x00e00	/* floating point assist */
#define _EXC_OFF_SW_EMUL	0x01000	/* Software Emulation */
#define _EXC_OFF_DATA_BKPT	0x01c00	/* Data Breakpoint */
#define _EXC_OFF_INST_BKPT	0x01d00	/* Instruction Breakpoint */
#define	_EXC_OFF_PERI_BKPT	0x01e00	/* Maskable Dev. Port or
					   Peripheral Breakpoint */
#define _EXC_OFF_NM_DEV_PORT	0x01f00	/* Non Maskable develop. port */
#define	_EXC_OFF_END		0x02000	/* end of vectors */
# endif	/* (CPU == PPC509) */

# if	(CPU == PPC555)
#undef  _EXC_OFF_DATA
#undef  _EXC_OFF_INST
#undef  _EXC_OFF_RES3
#define _EXC_OFF_FPA		0x00e00	/* floating point assist */
#define _EXC_OFF_SW_EMUL	0x01000	/* Software Emulation */
#define _EXC_OFF_IPE		0x01300 /* Instruction protection error */
#define _EXC_OFF_DPE		0x01400 /* Data protection error */
#define _EXC_OFF_DATA_BKPT	0x01c00	/* Data Breakpoint */
#define _EXC_OFF_INST_BKPT	0x01d00	/* Instruction Breakpoint */
#define	_EXC_OFF_PERI_BKPT	0x01e00	/* Maskable Dev. Port or */
					/* Peripheral Breakpoint */
#define _EXC_OFF_NM_DEV_PORT	0x01f00	/* Non Maskable develop. port */
#define	_EXC_OFF_END		0x02000	/* end of vectors */
# endif	/* (CPU == PPC555) */

# if	(CPU == PPC601)
#undef	_EXC_OFF_RES1
#define _EXC_OFF_IOERR	 	0x00a00	/* I/O controller interface error */
#undef 	_EXC_OFF_TRACE
#define _EXC_OFF_RES4	 	0x00d00		/* reserved for mpc601 */
#define _EXC_OFF_RUN_TRACE 	0x02000		/* run-mode/trace exception */
#define	_EXC_OFF_END		0x02100	/* end of vectors */
# endif	/* (CPU == PPC601) */

# if	((CPU == PPC603) || (CPU == PPCEC603))
#define _EXC_OFF_INST_MISS	0x01000	/* instruction translation miss */
#define _EXC_OFF_LOAD_MISS	0x01100	/* data load translation miss */
#define _EXC_OFF_STORE_MISS	0x01200	/* data store translation miss */
# endif	/* ((CPU == PPC603) || (CPU == PPCEC603)) */

# if	((CPU == PPC603) || (CPU == PPCEC603) || (CPU == PPC604))
#define _EXC_OFF_INST_BRK	0x01300 /* instruction breakpoint exception */
#define	_EXC_OFF_INST_BKPT	_EXC_OFF_INST_BRK	/* variant spelling */
#define _EXC_OFF_SYS_MNG	0x01400	/* system management exception */
#  if	(CPU == PPC604)
#define	_EXC_ALTIVEC_ASSIST	0x01600	/* altivec assist */
#define	_EXC_OFF_THERMAL	0x01700	/* thermal interrupt */
#define	_EXC_OFF_END		0x01800	/* end of vectors */
#  else	/* 604 */
#define	_EXC_OFF_END		0x01500	/* end of vectors */
#  endif  /* 604 */
# endif	/* ((CPU == PPC603) || (CPU == PPCEC603) || (CPU == PPC604)) */

# if	((CPU == PPC403) || (CPU == PPC405) || (CPU == PPC405F))
#undef 	_EXC_OFF_RESET
#undef  _EXC_OFF_DATA
#undef 	_EXC_OFF_DECR
#undef 	_EXC_OFF_TRACE

#define _EXC_OFF_CRTL	 	0x00100	/* critical interrupt */
#define _EXC_OFF_PROT	 	0x00300	/* protection violation exception */
#define _EXC_OFF_PIT		0x01000	/* programmable interval timer */
#define _EXC_OFF_FIT		0x01010	/* fixed interval timer */
#define _EXC_OFF_WD		0x01020	/* watchdog timer */
#define _EXC_OFF_DBG		0x02000	/* debug exception */
#define _EXC_OFF_DATA_MISS	0x01100	/* data translation miss */
#define _EXC_OFF_INST_MISS	0x01200	/* instruction translation miss */
#define _EXC_OFF_END		0x01300	/* end of vectors */

/*
 * The FIT and PIT excConnectCode stubs won't fit at their assigned locations
 * so we need to put them where we've got some available space and jump to
 * them from _EXC_OFF_PIT and _EXC_OFF_FIT.
 *
 * NOTE:  The frameless nesting code in intALib.s contains special-case
 * handling for relocated "normal" (as opposed to "critical") vectors.
 * All relocated normal vectors on processors which implement critical
 * interrupts must be handled individually there, and their relocated
 * stubs must be at addresses divisible by 0x0080.
 */

#define _EXC_NEW_OFF_PIT	0x01080	/* programmable interval timer */
#define _EXC_NEW_OFF_FIT	0x01180	/* fixed interval timer */
# endif	/* CPU == PPC40x */

#endif	/* IVPR */

/*
 * At the entrance of the non-MMU exception handler, SRR0, SRR1, P0 and P1 
 * need be saved to the global array to reduce the SPRG usage. These macros 
 * define the respective storage locations.
 */

#define _EXC_SAVE_AREA_OFF_P0	0
#define _EXC_SAVE_AREA_OFF_P1	\
    (_EXC_SAVE_AREA_OFF_P0  + _EXC_SAVE_AREA_REG_SIZE)
#define _EXC_SAVE_AREA_OFF_SRR0	\
    (_EXC_SAVE_AREA_OFF_P1 + _EXC_SAVE_AREA_REG_SIZE)
#define _EXC_SAVE_AREA_OFF_SRR1	\
    (_EXC_SAVE_AREA_OFF_SRR0 + _EXC_SAVE_AREA_REG_SIZE)
#define _EXC_SAVE_AREA_OFF_LR   \
    (_EXC_SAVE_AREA_OFF_SRR1 + _EXC_SAVE_AREA_REG_SIZE)
#define _EXC_SAVE_AREA_OFF_DEAR   \
    (_EXC_SAVE_AREA_OFF_LR + _EXC_SAVE_AREA_REG_SIZE)
#define _EXC_SAVE_AREA_OFF_ESR   \
    (_EXC_SAVE_AREA_OFF_DEAR + _EXC_SAVE_AREA_REG_SIZE)
#define _EXC_SAVE_AREA_OFF_P2   \
        (_EXC_SAVE_AREA_OFF_ESR + _EXC_SAVE_AREA_REG_SIZE)
   
#define CRT_LR_OFFSET _EXC_SAVE_AREA_OFF_SRR0
#define CRT_SPRG3_OFFSET _EXC_SAVE_AREA_OFF_P0

#   ifdef _WRS_CONFIG_LP64
#       define _EXC_SAVE_AREA_REG_SIZE  8
#       define _EXC_SAVE_AREA_SIZE      128
#       define _EXC_SAVE_AREA_SHIFT     7
#   else /* !_WRS_CONFIG_LP64 */
#       define _EXC_SAVE_AREA_REG_SIZE  4
#       define _EXC_SAVE_AREA_SIZE      64
#       define _EXC_SAVE_AREA_SHIFT     6
#   endif /* _WRS_CONFIG_LP64 */

/*
 * Decrementer and PIT are by and large functionally equivalent,
 * except that the _DECR vector does not need to be relocated.
 */
#if	defined(_EXC_OFF_DECR)
#define	_EXC_OFF_SYSTIMER	_EXC_OFF_DECR
#define	_EXC_NEW_OFF_SYSTIMER	_EXC_OFF_DECR
#elif	defined(_EXC_OFF_PIT)
#define	_EXC_OFF_SYSTIMER	_EXC_OFF_PIT
#define	_EXC_NEW_OFF_SYSTIMER	_EXC_NEW_OFF_PIT
#else
#undef	_EXC_OFF_SYSTIMER
#undef	_EXC_NEW_OFF_SYSTIMER
#endif

#ifndef	_EXC_OFF_TRACE
/* Processors having no Trace exception handle single step differently */

#define BRANCH_MASK             0xF0000000
#define OP_BRANCH               0x40000000
#define BCCTR_MASK              0xFC0007FE
#define BCLR_MASK               0xFC0007FE
#define AA_MASK                 0x00000002

#define BO_NB_BIT               5               /* nb bits of BO field    */
#define CR_NB_BIT               32              /* nb bits of CR register */

#define _OP(opcd, xo)           ((UINT32) (((opcd) << 26) + ((xo) << 1)))

#define INST_BCCTR              _OP(19, 528)    /* BCCTR instruction opcode */
#define INST_BCLR               _OP(19, 16)     /* BCLR instruction opcode */

#define _IFIELD_LI(x)           ((0x02000000 & x) ? ((0xf6000000 | x) & ~3) : \
						    ((0x03fffffc & x) & ~3))
#define _IFIELD_BD(x)           ((0x00008000 & x) ? (0xffff0000 | (x & ~3)) : \
						    (0x0000fffc & x))
						/* ^ signed branch displ */
#define _IFIELD_BO(x)           ((0x03e00000 & x) >> 21)  /* branch options */
#define _IFIELD_BI(x)           ((0x001f0000 & x) >> 16)  /* branch condition */

#define _REG32_BIT(reg, no)     (0x00000001 & (reg >> (no)))
			/* value of no th bit of the 32 bits register reg */
			/* bit 0 is the LSB */
#endif	/* _EXC_OFF_TRACE */

/* SRR1 bit definition for program exception */

#ifdef  _PPC_MSR_FP
# define _EXC_PROG_SRR1_FPU	0x00100000	/* floating-point enabled */
#endif /* _PPC_MSR_FP */
#define _EXC_PROG_SRR1_ILL	0x00080000	/* illegal instruction */
#define _EXC_PROG_SRR1_PRIV	0x00040000	/* privileged instruction */
#define _EXC_PROG_SRR1_TRAP	0x00020000	/* trap exception */
#define _EXC_PROG_SRR1_NIA	0x00010000	/* SRR0 has nia (else cia) */

#ifdef	_PPC_MSR_CE
/*
 * This processor implements "critical" exceptions,
 * which use different SRR's than other exceptions.
 * Abstract the names of those registers, since they are
 * different in the 440 and 85XX than in previous 40x processors.
 */
# ifdef	CSRR0
#  define	SRR_CI_PC	CSRR0
# else	/* CSRR0 */
#  define	SRR_CI_PC	SRR2
# endif	/* CSRR0 */

# ifdef	CSRR1
#  define	SRR_CI_MSR	CSRR1
# else	/* CSRR1 */
#  define	SRR_CI_MSR	SRR3
# endif	/* CSRR1 */

/* Retain earlier names for compatibility */
# define CRIT_SAVE_PC	SRR_CI_PC
# define CRIT_SAVE_MSR	SRR_CI_MSR

#endif	/* _PPC_MSR_CE */

#ifndef _ASMLANGUAGE

/* variable declarations */

extern FUNCPTR  excExcepHook;   /* add'l rtn to call when exceptions occur */

/* function declarations */

extern STATUS		excConnect (VOIDFUNCPTR *, VOIDFUNCPTR);
extern STATUS  		excIntConnect (VOIDFUNCPTR *, VOIDFUNCPTR);
extern void		excVecSet (FUNCPTR *, FUNCPTR);
extern FUNCPTR		excVecGet (FUNCPTR *);
extern void		excVecBaseSet (FUNCPTR *);
extern FUNCPTR *	excVecBaseGet (void);

#  ifdef _PPC_MSR_CE
extern STATUS		excCrtConnect (VOIDFUNCPTR *, VOIDFUNCPTR);
extern STATUS		excIntCrtConnect (VOIDFUNCPTR *, VOIDFUNCPTR);
extern STATUS  		excIntConnectTimer (VOIDFUNCPTR *, VOIDFUNCPTR);

#  ifdef _PPC_MSR_MCE
extern STATUS		excMchkConnect (VOIDFUNCPTR *, VOIDFUNCPTR);
#  endif  /* _PPC_MSR_MCE */
#  endif  /* _PPC_MSR_CE */


#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCexcPpcLibh */
