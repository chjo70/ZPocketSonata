/* excArchLibP.h - PowerPC exception library private exports */

/*
 * Copyright (c) 2003-2005, 2008, 2009, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/* Definitions for use only by PPC excArchLib.c and syscallArchLib.c */

/*
modification history
--------------------
20nov14,ylu  LP64 adaptation to support PPC64.(F2518)
01mar13,h_k  added T4_ERRATUM_CPU6198 for e6500.
18nov09,to   GUEST: _VB_PISA_EHV support
12may09,rec  move guestOs ENT_OFF definition here
23may08,pch  CQ118100: clean up SMP support in critical-exception handling
17oct05,pch  SPR 113899: exc/intConnectCode must restore 32-bit mode
                 before calling exc/intEnt
22sep04,pch  Add debug/trace capabilities (under #ifdef)
06aug04,pch  SPR's 78780 & 100398: support use of standard exception 
		 vectors in MMU and syscall
05may04,pch  SPR 92997: use correct symbol name in multiple-include
                 protection
08Dec03,pch  extracted from excArchLib.c vn 02z
*/

#ifndef __INCexcArchLibPh
#define __INCexcArchLibPh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/*
 * The following typedefs are used within excArchLib.c in the interest
 * of clarity, to keep from making matters worse than they already are.
 * (Several existing published API's are defined with types that are just
 * plain wrong for the PowerPC port, however, we are stuck with them.)
 */
typedef	ULONG	vecTblOffset;	/* Offset in vector table, e.g. _EXC_OFF_* */
typedef	char *	codeBase;	/* Base address in normal code space */
typedef	char *	vectorBase;	/* Base address in vector execution space */
typedef	char *	codePtr;	/* Pointer into normal code space */
typedef	char *	vectorPtr;	/* Pointer into vector execution space */

/*
 * Convert a (vectorPtr) into a (codePtr), allowing for any difference
 * between excVecBase and excVecBaseAltAdrs.  The distinction is critical
 * during initialization, when vector execution space may not be accessible
 * because the MMU has not yet been set up.
 */
#define	CODE_PTR_FROM_VECTOR_PTR(vecp)	\
	(codePtr)((((vectorPtr)(vecp)) - excVecBase) + excVecBaseAltAdrs)

#endif /* _ASMLANGUAGE */

/*
 * Word offsets to the branch instructions in
 * the exc*ConnectCode arrays in excArchLib.c
 *
 * Changes affecting ENT_OFF or ENT_CRT_OFF will require corresponding
 * changes in excALib.s:excEnt() and excCrtEnt() when calculating the
 * original vector address from the LR value.
 */

#ifdef	_WRS_CONFIG_LP64
#define ENT_COMMON_OFF		2
#define ISR_COMMON_OFF		5
#define EXIT_COMMON_OFF	7
#define EXT_ENT_COMMON_OFF	3
#define EXT_ISR_COMMON_OFF	12
#define EXT_EXIT_COMMON_OFF	20
# ifdef	_EXC_OFF_CRTL
#define CE_CLEAR_INST_NUM	3
#define	ENT_CRT_OFF	 ENT_COMMON_OFF
#define	ISR_CRT_OFF	 ISR_COMMON_OFF
#define	EXIT_CRT_OFF	 EXIT_COMMON_OFF
#define	EXT_ENT_CRT_OFF	 EXT_ENT_COMMON_OFF
#define	EXT_ISR_CRT_OFF	 EXT_ISR_COMMON_OFF
#define	EXT_EXIT_CRT_OFF EXT_EXIT_COMMON_OFF
# else
#define CE_CLEAR_INST_NUM	0
# endif	/* _EXC_OFF_CRTL */
#define	ENT_OFF		 (ENT_COMMON_OFF + CE_CLEAR_INST_NUM)
#define	ISR_OFF		 (ISR_COMMON_OFF + CE_CLEAR_INST_NUM)
#define	EXIT_OFF	 (EXIT_COMMON_OFF + CE_CLEAR_INST_NUM)
#define	EXT_ENT_OFF	 (EXT_ENT_COMMON_OFF + CE_CLEAR_INST_NUM)
#define	EXT_ISR_OFF	 (EXT_ISR_COMMON_OFF + CE_CLEAR_INST_NUM)
#define	EXT_EXIT_OFF	 (EXT_EXIT_COMMON_OFF + CE_CLEAR_INST_NUM)
#elif	defined(_EXC_OFF_CRTL) || defined(_WRS_PPC_64BIT)
# if	defined(T4_ERRATUM_CPU6198) && defined(_WRS_CONFIG_SMP)
#define	T4_LIS_OFF	 4	/* offset for lis p0,HI(mtmsrwa) */
#define	T4_ORI_OFF	 5	/* offset for ori p0,p0,LO(mtmsrwa) */
#define	T4_LABEL_OFF	 8	/* offset for RMCI to */
#define	ENT_OFF		 9	/* offset for intEnt/excEnt */
#define	ISR_OFF		 12	/* offset for ISR or exc. handler */
#define	EXIT_OFF	 14	/* offset for intExit/excExit */
#define	EXT_ENT_OFF	 10	/* offset for ext intEnt/excEnt */
#define	EXT_ISR_OFF	 15	/* offset for ext ISR or exc handler */
#define	EXT_EXIT_OFF	 22	/* offset for ext intExit/excExit */
#define	EXT_ENT_CRT_OFF	 6	/* offset for ext intEnt/excEnt */
#define	EXT_ISR_CRT_OFF	 11	/* offset for ext ISR or exc handler */
#define	EXT_EXIT_CRT_OFF 18	/* offset for ext intExit/excExit */
#define	ENT_CRT_OFF	 2	/* offset for intEnt/excEnt */
#define	ISR_CRT_OFF	 5	/* offset for ISR or exc. handler */
#define	EXIT_CRT_OFF	 7	/* offset for intCrtExit/excCrtExit */
# else
#define	ENT_OFF		 6	/* offset for intEnt/excEnt */
#define	ISR_OFF		 9	/* offset for ISR or exc. handler */
#define	EXIT_OFF	 11	/* offset for intExit/excExit */
#define	EXT_ENT_OFF	 7	/* offset for ext intEnt/excEnt */
#define	EXT_ISR_OFF	 12	/* offset for ext ISR or exc handler */
#define	EXT_EXIT_OFF	 19	/* offset for ext intExit/excExit */
#  ifdef _EXC_OFF_CRTL
#define	EXT_ENT_CRT_OFF	 3	/* offset for ext intEnt/excEnt */
#define	EXT_ISR_CRT_OFF	 8	/* offset for ext ISR or exc handler */
#define	EXT_EXIT_CRT_OFF 15	/* offset for ext intExit/excExit */
#define	ENT_CRT_OFF	 2	/* offset for intEnt/excEnt */
#define	ISR_CRT_OFF	 5	/* offset for ISR or exc. handler */
#define	EXIT_CRT_OFF	 7	/* offset for intCrtExit/excCrtExit */
#  endif /* _EXC_OFF_CRTL */
# endif	/* T4_ERRATUM_CPU6198 && _WRS_CONFIG_SMP */

# if	defined(_EXC_OFF_CRTL) && defined(LOG_FRAMELESS)
/*
 * Logging of "frameless nesting" occurences, used only for testing purposes.
 *
 * Each log record consists of one word, with the record type (exit case) in
 * the most-significant byte and the interrupted vector offset in the least-
 * significant halfword.  The round-robin log buffer pointer, and the counts
 * for the three record types, are stored at addresses 0x80-0x8f.
 *
 * CRT_COUNT_061C is used when TRAP_DISPATCH_ADDR is also set, for debugging.
 */

/* offsets from address zero */
#define LOG_FML_PTR	0x80	/* where to store next log record */
#define RIV_COUNT	0x84	/* count of resume-in-vector cases */
#define ESF_COUNT	0x88	/* count of copy-ESF cases */
#define STM_COUNT	0x8c	/* count of syscall/TLB-miss cases */
#define	CRT_COUNT_ENT	0x90	/* count of all critical interrupt entries */
#define	CRT_COUNT_EXIT	0x94	/* count of all critical interrupt exits */
#define	CRT_COUNT_RESC	0x98	/* calls of reschedule from intCrtExit */
#define	CRT_COUNT_061C	0x9c	/* dispatches of PC==0x061C in windALib */
#define	CRT_COUNT_RESV	0xa0	/* reserved for future use */

/* log record types */
#define RIV_TYPE	0x5000	/* resume-in-vector */
#define ESF_TYPE	0x6000	/* copy-ESF */
#define STM_TYPE	0x7000	/* syscall/TLB-miss */

/* size of log record in bytes */
#define LOG_FML_SIZE	4

/* size of log buffer in bytes, must be a power of 2 */
#define LOG_FML_BUF_SIZE	0x1000

/* bit number corresponding to buffer size, used to wrap log pointer */
#define LOG_FML_BIT	19
# endif	/* _EXC_OFF_CRTL && LOG_FRAMELESS */

#else	/* _EXC_OFF_CRTL || _WRS_PPC_64BIT */
#define	ENT_OFF		 2	/* offset for intEnt/excEnt */
#define	ISR_OFF		 5	/* offset for ISR or exc. handler */
#define	EXIT_OFF	 7	/* offset for intExit/excExit */
#define	EXT_ENT_OFF	 3	/* offset for ext intEnt/excEnt */
#define	EXT_ISR_OFF	 8	/* offset for ext ISR or exc handler */
#define	EXT_EXIT_OFF	 15	/* offset for ext intExit/excExit */
#endif	/* _EXC_OFF_CRTL || _WRS_PPC_64BIT */

#if defined(_WRS_CONFIG_WRHV_GUEST) && !defined(_WRS_CONFIG_VBI_PPC_E500MC)
# undef	 ENT_OFF
# define ENT_OFF	3	/* 3 words in for guest OS */
#endif /* _WRS_CONFIG_WRHV_GUEST && !_WRS_CONFIG_VBI_PPC_E500MC */

#ifdef	LOG_DISPATCH
/* logging of dispatch (rfi/rfci) operations, used only for debugging */

/* offsets from address zero */
#define LOG_DISP_PTR	0xec	/* where to store next log record */
#define LOG_DISP_SAVE	0xe8	/* last LOG_DISP_PTR when logging suspended */

/* offsets in log record */
#define	LOG_DISP_ID	0x00	/* record type = dispatcher ID */
#define	LOG_DISP_LR	0x04	/* LR value (who called dispatcher) */
#define	LOG_DISP_SP_IN	0x08	/* SP value when dispatcher called */
#define	LOG_DISP_CTX	0x0c	/* address context loaded from */
#define	LOG_DISP_PC	0x10	/* PC value to be loaded */
#define	LOG_DISP_MSR	0x14	/* MSR value to be loaded */
#define	LOG_DISP_SP_OUT	0x18	/* SP value to be loaded */
#define	LOG_DISP_NXT_FL	0x1c	/* current value of LOG_FML_PTR */

/* size of log record in bytes */
#define LOG_DISP_SIZE	32

/* size of log buffer in bytes, must be a power of 2 */
#define LOG_DISP_BUF_SIZE	0x2000

/* bit number corresponding to buffer size, used to wrap log pointer */
#define LOG_DISP_BIT	18

/* log record types */
#define	DISP_WIND	0x01	/* windLoadContext */
#define	DISP_CTXL	0x02	/* _sigCtxLoad */
#define	DISP_EXCN	0x03	/* excExit */
#define	DISP_EXCC	0x04	/* excCrtExit */
#define	DISP_INTN	0x05	/* intExit, normal case */
#define	DISP_INTP	0x06	/* intExit, preempting (reschedule) */
#define	DISP_INTI	0x07	/* intExit, idle case */
#define	DISP_INTC	0x08	/* intCrtExit, normal case */
#define	DISP_INCR	0x09	/* intCrtExit, frameless RIV case */
#define	DISP_INCI	0x0a	/* intCrtExit, idle case */
#define	DISP_INCP	0x0b	/* intCrtExit, preempting (reschedule) */
#define	DISP_INCF	0x0c	/* intCrtExit, frameless preempting (copyESF) */
#define	DISP_DTLB	0x0d	/* data TLB miss handled */
#define	DISP_ITLB	0x0e	/* insn TLB miss handled */
#define	DISP_RTPI	0x0f	/* rtpUserModeSwitch */
#define DISP_SYSC	0x10	/* resume after syscall */
#define	DISP_EXCM	0x11	/* excMchkExit */
#define	DISP_POW	0x12	/* vxC1StateSet */
#endif	/* LOG_DISPATCH */

#ifdef __cplusplus
}
#endif

#endif /* __INCexcArchLibPh */
