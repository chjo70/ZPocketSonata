/* archPpc.h - PowerPC specific header */

/*
 * Copyright (c) 1984-2018 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08mar18,syt  add some SPIN TABLE related definitions for PPC.
07jul17,l_z  add _WRS_SUPPORT_CACHE_XLATE support. (V7PRO-3850)
27jun16,l_z  Fix wrong comment. (V7PRO-3136)
15may15,pcs  Removed referenced to macro _ARCH_MULTIPLE_CACHELIB
06feb16,dee  cast taskMsrDefault in intUnlock to (int) to eliminate warning
02sep15,d_l  add _WRS_ARCH_HAS_CPU_PWR_MGMT for 32bit build. (V7PRO-2181)
16jul15,w_x  Merge Core OS MMU changes, assume _WRS_ARCH_USES_DIRECT_MAP_REGION
             default as defined for LP64 (F2518)
15jun15,wyt  redefine _WRS_VA_ADDR for LP64. (F2518)
21may15,syt  enable macro _WRS_ARCH_USES_DIRECT_MAP_REGION for LP64. (F2518) 
24mar15,syt  remove the temporary WIND_TCB offset defines for LP64.(US50763)
20nov14,ylu  LP64 adaptation to support PPC64.(F2518)
10oct14,d_l  remove PPC32 condition build for MSR and FPSCR bit definition.
             (VXPRO-1399)
12jul14,syt  replaced the ppc85xx.h with vxPpc.h to support PPC60x.(F2505)
29sep13,x_z  moved CPU_INFO to vxfdt library.
19jul13,x_z  added CPU_INFO defines and ME_MASK macros.
24jul12,h_k  increased VX_MAX_SMP_CPUS to 32 for T4240 and future coming
             CPUs. (WIND00364728)
03may11,syt  added support for PPC465
15dec10,pch  CQ239447: add _WRS_ARCH_DEFERS_KERNEL_UNLOCK
14dec10,gls  made VX_OBJ_ALIGN_SIZE constant across all variants
             (WIND00246452)
16sep10,gls  added VX_OBJ_ALIGN_SIZE.
20aug10,x_z  added support for PPC476.
29jul10,pad  Moved extern C statement after include statements.
01oct09,pgh  Remove _WRS_CHECK_MACHINE_TYPE macro.
28sep09,pgh  Fix _WRS_CHECK_MACHINE_TYPE
08jul09,b_m  added _PPC_WORD_SIZE.
31jul08,tcr  change macro for compatibility
19may08,tcr  update SV interrupt macro
25mar08,pch  Limit VX_MAX_SMP_CPUS to 1 if LOG_FRAMELESS || LOG_DISPATCH
13mar08,rlp  Removed obsolete _WRS_ARCH_HAS_DBG_IPI macro.
25feb08,pch  Move SMP-dependent settings to private/smpPpcP.h
13sep07,pch  CQ102745: add _ARCH_SUPPORTS_PROTECT_IDLE_TASK_STACK
16aug07,pch  rename spinlockApiAvailable to spinLockApiAvailable
15aug07,mmi  add _WRS_ARCH_HAS_CPU_PWR_MGMT and POW_MASK()
07aug07,pch  CQ100667: define _WRS_ARCH_HAS_SPINLOCK_API_AVAILABLE
             in SMP build
01jun07,jmp  Defined _WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT for PPC.
04may07,zl   updated portable library build configuration.
25apr07,kk   move VX_MAX_SMP_CPUS to here
13apr07,rlp  Added _WRS_ARCH_HAS_DBG_IPI macro.
21feb07,jmg  Added include vxPortableP.h
11dec06,kk   removed references to _WRS_BASE6_SCHEDULER, no longer needed
17oct06,lei  removed _WRS_ARCH_HAS_RESCHEDULE_STACK;
             added _WRS_ARCH_HAS_IDLE_TASK
11oct06,mmi  added _WRS_VX_NO_GLOBAL_ERRNO
12sep06,lei  added _WRS_ARCH_HAS_NEW_KERNEL_LOCK
04aug06,pch  move SMP support to private/smpPpcP.h
             move kernel-only definitions here from asmPpc.h
28jul06,lei  added _WRS_ARCH_HAS_RESCHEDULE_STACK
19jun06,pch  SMP support
11apr05,kk   removed _WRS_OBJLIB_SUPPORT_VERIFY_TRAP macro (SPR# 106486)
10feb05,pch  SPR 102772: add _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
22apr04,to   define RFI only for _ASMLANGUAGE
18mar04,rec  merge in PPC970 changes
01nov04,pch  SPR 92598: Add _WRS_OSM_INIT
01oct04,tam  moved definition of _TYPE_PHYS_ADDR from shared file to
             kernel header
23aug04,aeg  added _WRS_OBJLIB_SUPPORT_VERIFY_TRAP
11aug04,pch  cleanup
11may04,tam  removed _WRS_KERNEL_TEXT_START_ADRS definition
22mar04,zl   moved trcLib_PORTABLE and INSTR definitions to archPpcCommon.h;
             added _WRS_FRAMEP_FROM_JMP_BUF and _WRS_RET_PC_FROM_JMP_BUF.
18feb04,zl   defined trcLib_PORTABLE
03feb04,aeg  moved _WRS_PAL_COPROC_LIB to archPpcCommon.h
27jan04,gls  moved _TYPE_PHYS_ADDR definition to archPpcCommon.h
18dec03,dat  temp fix for va_addr macro
14nov03,job  Moved some blib stuff to archPpcCommon.h
             Added missing include of archPpcCommon.h
13nov03,pes  Added include of archPpcCommon.h
14oct03,sru  define 64-bit PHYS_ADDR type
10sep03,cjj  removed dual definition of _WRS_ENABLE_IDLE_INTS
23apr03,pch  Add generic PPC32 support
07may03,pes  More conditional compilation cleanups.
02may03,pes  PAL conditional compilation cleanup.
11apr03,pes  Add define to trigger PAL Coprocessor Abstraction
09jul03,tam  added macro _WRS_KERNEL_TEXT_START_ADRS
03dec02,mil  Removed inclusion of ppc603.h for PPCE500.
04sep02,dtr  Adding 85XX header file.
02aug02,pcs  Add support for PPCE500 and make it the same as PPC603 for
             the present.
13mar02,sn   SPR 73723 - define supported toolchains
25sep01,yvp  SPR62760 fix: Added default text segment alignment.
14aug01,pch  Add PPC440 support
25oct00,s_m  renamed PPC405 cpu types
12jun00,alp  Added PPC405 support
12mar99,zl   added PPC509 and PPC555 support.
18aug98,tpr  added PowerPC EC 603 support.
10feb97,tam  added FPSCR bit definition macros.
08oct96,tam  added MSR bit definition macros.
11apr96,tpr  added PPC505, PPC602 and PPC860.
14feb96,tpr  added PPC604.
21mar95,caf  moved _STACK_ALIGN_SIZE to toolPpc.h.
07nov94,yao  changed PPC403GA to PPC403.
17mar94,yao  written.
*/

#ifndef __INCarchPpch
#define __INCarchPpch

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* temporary define */

#define _WRS_VX_NO_GLOBAL_ERRNO 

/* cache virt-phys translate */

#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
#define _WRS_SUPPORT_CACHE_XLATE
#endif /*_WRS_CONFIG_COMPAT69_ADR_SPACE */

/* arch supports deferred kernel unlock when configured for SMP and RTPs */

#if defined(_WRS_CONFIG_SMP) && defined(_WRS_CONFIG_VM_MULTIPLE_CONTEXT)
#define _WRS_ARCH_DEFERS_KERNEL_UNLOCK
#endif	/* _WRS_CONFIG_SMP && _WRS_CONFIG_VM_MULTIPLE_CONTEXT */

/* define for LP64 */

#ifdef	_WRS_CONFIG_LP64

/* disable stmw since it stores only 32-bit value */

#define _WRS_PPC_STMW_SLOW

#define _WRS_MMU_HAS_BLOCK_INFO_API

/* AIM MMU region level depth is 3 */

#define AIM_MMU_REGION_LEVEL	3

#else
/* AIM MMU region level depth is 1 */

#define AIM_MMU_REGION_LEVEL	1
#endif	/* _WRS_CONFIG_LP64 */

/* define for SMP */

#undef VX_MAX_SMP_CPUS
#if defined(LOG_FRAMELESS) || defined(LOG_DISPATCH)
#define VX_MAX_SMP_CPUS 1       /* maximum processors in SMP configuration */
#else	/* LOG_FRAMELESS || LOG_DISPATCH */
#define VX_MAX_SMP_CPUS 32      /* maximum processors in SMP configuration */
#endif	/* LOG_FRAMELESS || LOG_DISPATCH */

#define _ARCH_SUPPORTS_GCC
#define _ARCH_SUPPORTS_DCC

#if	(CPU != PPC403)
/* Used in usrKernel.c and usrKernelStack.c */
#define	_ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
#endif	/* PPC403 */

#ifdef	_WRS_CONFIG_LP64
#define _PPC_MSR_CM	0x80000000	/* sixty-four bit computation mode  */
#endif	/* _WRS_CONFIG_LP64 */

/* upper Machine State Register (MSR) mask */

#define _PPC_MSR_CM_U		0x8000	/* sixty-four bit mode (not 
					 * implemented for 32-bit machine) */
#define _PPC_MSR_POW_U		0x0004	/* power managemnet enable */ 
#define _PPC_MSR_ILE_U		0x0001	/* little endian mode */

/* lower Machine State Register (MSR) mask */

#define	_PPC_MSR_EE		0x8000	/* external interrupt enable */
#define _PPC_MSR_PR		0x4000	/* privilege level */
#define _PPC_MSR_FP		0x2000	/* floating-point available */
#define _PPC_MSR_ME		0x1000	/* machine check enable  */
#define _PPC_MSR_FE0		0x0800	/* floating-point exception mode 0 */
#define _PPC_MSR_SE		0x0400	/* single-step trace enable */
#define _PPC_MSR_BE		0x0200	/* branch trace enable */
#define _PPC_MSR_FE1		0x0100	/* floating-point exception mode 1 */
#define _PPC_MSR_IP		0x0040	/* exception prefix */
#define _PPC_MSR_IR		0x0020	/* instruction address translation */
#define _PPC_MSR_DR		0x0010	/* data address translation */
#define _PPC_MSR_RI		0x0002	/* recoverable interrupt */
#define _PPC_MSR_LE		0x0001	/* little-endian mode */

#define _PPC_MSR_POWERUP	0x0040	/* state of MSR at powerup */

/* MSR bit definitions common to all PPC arch. */

#define _PPC_MSR_BIT_EE		16	/* MSR Ext. Intr. Enable bit - EE */
#define _PPC_MSR_BIT_PR		17	/* MSR Privilege Level bit - PR */
#define _PPC_MSR_BIT_ME		19	/* MSR Machine Check Enable bit - ME */
#define _PPC_MSR_BIT_LE		31	/* MSR Little Endian mode bit - LE */

/* FPSCR bit definitions (valid for the PPC60X familly) */

#define _PPC_FPSCR_FX           0x80000000 /* FP exception summary */
#define _PPC_FPSCR_FEX          0x40000000 /* FP enabled exception summary */
#define _PPC_FPSCR_VX           0x20000000 /* FP invalid exception summary */
#define _PPC_FPSCR_OX           0x10000000 /* FP overflow exception */
#define _PPC_FPSCR_UX           0x08000000 /* FP underflow exception */
#define _PPC_FPSCR_ZX           0x04000000 /* FP divide by zero exception */
#define _PPC_FPSCR_XX           0x02000000 /* FP inexact exception */
#define _PPC_FPSCR_VXSNAN       0x01000000 /* FP invalid exception for SNAN */
#define _PPC_FPSCR_VXISI        0x00800000 /* FP invalid exc. for INF-INF */
#define _PPC_FPSCR_VXIDI        0x00400000 /* FP invalid exc. for INF/INF */
#define _PPC_FPSCR_VXZDZ        0x00200000 /* FP invalid exc. for 0/0 */
#define _PPC_FPSCR_VXIMZ        0x00100000 /* FP invalid exc. for INF*0 */
#define _PPC_FPSCR_VXVC         0x00080000 /* FP inval. exc. for invalid comp.*/
#define _PPC_FPSCR_FR           0x00040000 /* FP fraction rounded */
#define _PPC_FPSCR_FI           0x00020000 /* FP fraction inexact */
#define _PPC_FPSCR_FPRF         0x0001F000 /* FP result flags */
#define _PPC_FPSCR_VXSOFT       0x00000400 /* FP inval. exc. for soft. request*/
#define _PPC_FPSCR_VXSQRT       0x00000200 /* FP inval. exc. for sqrt */
#define _PPC_FPSCR_VXCVI        0x00000100 /* FP inval. exc. for int convert */
#define _PPC_FPSCR_VE           0x00000080 /* FP invalid exc. enable */
#define _PPC_FPSCR_OE           0x00000040 /* FP overflow exc. enable */
#define _PPC_FPSCR_UE           0x00000020 /* FP underflow exc. enable */
#define _PPC_FPSCR_ZE           0x00000010 /* FP divide by zero exc. enable */
#define _PPC_FPSCR_XE           0x00000008 /* FP iinexact exc. enable */
#define _PPC_FPSCR_NI           0x00000004 /* FP non-IEEE mode enable */
#define _PPC_FPSCR_RN(n)        (n)        /* FP rounding control value */

#define _PPC_FPSCR_RN_MSK       0x00000003 /* FP rounding control bits mask */
#define _PPC_FPSCR_EXC_MASK     0x1ff80700 /* FP exception status bits mask */
#define _PPC_FPSCR_CTRL_MASK    0x000000ff /* FP exception control bits mask */

/* FPSCR init value for tasks spawned with VX_FP_TASK (PPC60X only) */

#define _PPC_FPSCR_INIT         (_PPC_FPSCR_OE | _PPC_FPSCR_UE | _PPC_FPSCR_ZE \
				 | _PPC_FPSCR_RN(0))

#ifdef	_ASMLANGUAGE

#ifdef	_WRS_CONFIG_LP64
#define CLRRLPI	clrrdi
#define CMPLLPI	cmpldi
#define CMPLLP  cmpld
#define CMPLP	  cmpd
#define CMPLPI	 cmpdi
#define LDLP    ld
#define LDLPU   ldu
#define LDLPX   ldx
#define SLLPI	  sldi
#define SRLPI	  srdi
#define STLP    std
#define STLPU   stdu
#define	RFI	    rfi
#define LDARX   ldarx
#define STDCX   stdcx
#else
#define CLRRLPI	clrrwi
#define CMPLLPI	cmplwi
#define CMPLLP  cmplw
#define CMPLP	  cmpw
#define CMPLPI	 cmpwi
#define LDLP    lwz
#define LDLPU   lwzu
#define LDLPX   lwzx
#define SLLPI	  slwi
#define SRLPI	  srwi
#define STLP    stw
#define STLPU   stwu
#define	RFI	    rfi
#define LDARX   lwarx
#define STDCX   stwcx
#endif	/* _WRS_CONFIG_LP64 */

#if	(CPU != PPC32)
#define DSISR		18	/* data storage interrupt status */
#define	DAR		19	/* data address register */
#define	DEC		22	/* decrement register */
#define SDR1		25	/* storage description register 1 */
#endif	/* CPU != PPC32 */

#define SRR0		26	/* save and restore register 0 */
#define SRR1		27	/* save and restore register 1 */

#define SPRG0		272	/* software program register 0 */
#define SPRG1		273	/* software program register 1 */
#define SPRG2		274	/* software program register 2 */
#define	SPRG3		275	/* software program register 3 */

#if	(CPU != PPC32)
#define ASR		280	/* address space register
				 * (64 bit implementation only) */
#define EAR		282	/* external address register */

#define TBL		284	/* lower time base register */
#define TBU		285	/* upper time base register */
#endif	/* CPU != PPC32 */

#define PVR		287	/* processor version register */

#if	(CPU != PPC32)
#define IBAT0U		528	/* instruction BAT register */
#define IBAT0L		529	/* instruction BAT register */
#define IBAT1U		530	/* instruction BAT register */
#define IBAT1L		531	/* instruction BAT register */
#define IBAT2U		532	/* instruction BAT register */
#define IBAT2L		533	/* instruction BAT register */
#define IBAT3U		534	/* instruction BAT register */
#define IBAT3L		535	/* instruction BAT register */

#define DBAT0U		536	/* data BAT register */
#define DBAT0L		537	/* data BAT register */
#define DBAT1U		538	/* data BAT register */
#define DBAT1L		539	/* data BAT register */
#define DBAT2U		540	/* data BAT register */
#define DBAT2L		541	/* data BAT register */
#define DBAT3U		542	/* data BAT register */
#define DBAT3L		543	/* data BAT register */

#define IBAT4U		560	/* instruction BAT register */
#define IBAT4L		561	/* instruction BAT register */
#define IBAT5U		562	/* instruction BAT register */
#define IBAT5L		563	/* instruction BAT register */
#define IBAT6U		564	/* instruction BAT register */
#define IBAT6L		565	/* instruction BAT register */
#define IBAT7U		566	/* instruction BAT register */
#define IBAT7L		567	/* instruction BAT register */

#define DBAT4U		568	/* data BAT register */
#define DBAT4L		569	/* data BAT register */
#define DBAT5U		570	/* data BAT register */
#define DBAT5L		571	/* data BAT register */
#define DBAT6U		572	/* data BAT register */
#define DBAT6L		573	/* data BAT register */
#define DBAT7U		574	/* data BAT register */
#define DBAT7L		575	/* data BAT register */


/* macros to mask off particular bits of an MSR value */

#define ME_MASK(src, des) \
    rlwinm  des, src, 0, _PPC_MSR_BIT_ME+1, _PPC_MSR_BIT_ME-1

#ifndef	INT_MASK
#define INT_MASK(src, des) \
	rlwinm	des, src, 0, _PPC_MSR_BIT_EE+1, _PPC_MSR_BIT_EE-1
#endif	/* INT_MASK */
#define POW_MASK(src, des) \
	rlwinm	des, src, 0, _PPC_MSR_BIT_POW+1, _PPC_MSR_BIT_POW-1
#ifndef	MMU_MASK
/* Using bit #s here because names vary [DS,IS] vs [DR,IR] */
#define MMU_MASK(src, des)	rlwinm	des, src, 0, 28, 25
#endif	/* MMU_MASK */

#define RI_MASK(src, des) \
	rlwinm	des, src, 0, _PPC_MSR_BIT_RI+1, _PPC_MSR_BIT_RI-1

#define SE_MASK(src, des) \
	rlwinm	des, src, 0, _PPC_MSR_BIT_SE+1, _PPC_MSR_BIT_SE-1
#endif	/* CPU != PPC32 */

/* SPIN TABLE defines */

#define PPC_FDT_SPIN_TABLE_OFFSET       5
#define PPC_FDT_ENTRY_ADDR_UPPER        0
#define PPC_FDT_ENTRY_ADDR_LOWER        4
#define PPC_FDT_ENTRY_R3_UPPER          8
#define PPC_FDT_ENTRY_R3_LOWER          12
#define PPC_FDT_ENTRY_RESV              16
#define PPC_FDT_ENTRY_PIR               20
#define PPC_FDT_ENTRY_SIZE              32

#else	/* _ASMLANGUAGE */

typedef	unsigned long	_RType;		/* default register type */

/* macros for getting frame and return PC from a jmp_buf */

#define _WRS_FRAMEP_FROM_JMP_BUF(env)	((char *) (env)[0].reg.spReg)
#define _WRS_RET_PC_FROM_JMP_BUF(env)	((INSTR *) (env)[0].reg.lr)

/* physical addresses are represented on 64-bit for all PowerPC CPUs */

#define _TYPE_PHYS_ADDR		typedef UINT64 PHYS_ADDR
#endif 	/* _ASMLANGUAGE */

#define _WRS_PHYS_ADDR_IS_64_BITS

#define	_DYNAMIC_BUS_SIZING	FALSE	/* require alignment for swap */

/* default register size */

#ifdef	_WRS_CONFIG_LP64
#define _SIZE_OF_LONG_BITS	3
#define _PPC_REG_SIZE_BITS	3
#else
#define _SIZE_OF_LONG_BITS	2
#define _PPC_REG_SIZE_BITS	2
#endif	/* _WRS_CONFIG_LP64 */

#define _SIZE_OF_LONG		(1 << _SIZE_OF_LONG_BITS)

#define	_PPC_REG_SIZE		(1 << _PPC_REG_SIZE_BITS)

#define _PPC_WORD_SIZE		32	/* number of bits in a word */

#define _PPC_TEXT_SEG_ALIGN     4       /* 4 byte text segment alignment */


#define	RFI_OPCODE		0x4c000064

/* PAL additions */

/* moved here from h/private/eventP.h */

/*
 * Macro for event logging of intEnt events for PPC architechtures.
 * The PPC architecture is different in that there is only one external
 * interrupt line coming into the CPU. At the time of the intEnt, the
 * external interrupt number is unknown, meaning that logging cannot
 * take place at this time. In this architechture, the logging of an
 * intEnt event is deferred until the interrupt controller driver
 * is exectued.
 * Since the logging has to take place in drivers and/or BSP world files,
 * the details of how the logging to be done has been deferred to a macro 
 * which is defined here.
 *
 * Note: This replaces the previous technique of saving the timestamp
 * during the intEnt code to be used later, when the logging was done.
 * SPR 21868 refers to a problem in which this can give rise to out-of-order
 * timestamps in the event log.
 */
#define WV_EVT_INT_ENT(intNum)	    EVT_CTX_1(EVENT_INT_ENTER, intNum);



/* moved here from h/private/javaLibP.h */

#define JAVA_C_SYM_PREFIX	""

/* moved here from h/private/loadElfLibP.h */

#define LOW24_INSERT(buf,value) INSERT ((buf), (value), 0x03fffffc)

/* define to pick up sysI/O function declarations in sysLib.h */

#define _WRS_SYS_IO

/* define to insert the evtLogT1_noTS() function into evtLogLib.c */

#define _WRS_EVTLOGT1_NOTS

/* temp fix for va_addr support (See SPR 92721) */

#ifdef _WRS_CONFIG_LP64
#define _WRS_VA_ADDR(x)	 ((va_list *)&x)
#else
#define _WRS_VA_ADDR(x)	 ((va_list *)x)
#endif

/* from loadElfLib.c */

#define _WRS_USE_ELF_LOAD_FORMAT

/* from xdr_float.c */

#define FLOAT_NORM

/* from schedLib.c */

#define _WRS_TASK_MSR_DEFAULT
#define _WRS_VXLIB_SUPPORT

/* used by reschedule() when the kernel is idle */
#define _WRS_ENABLE_IDLE_INTS {intUnlock ((int) taskMsrDefault);}

/* PPC arch always requires OSM init if stack guard pages are enabled */

#define _WRS_OSM_INIT

/* temporary macro to indicate PPC uses the type II kernel lock */

#define _WRS_ARCH_HAS_NEW_KERNEL_LOCK

/* temporary macro to indicate PPC has idle task */

#define _WRS_ARCH_HAS_IDLE_TASK

/* indicates that PPC has VxDBG CPU control support */

#define _WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT

/* indicates that PPC support cpu Power managment framework */

#ifndef _WRS_CONFIG_LP64
#   define  _WRS_ARCH_HAS_CPU_PWR_MGMT
#endif

/* End PAL */

#ifdef __cplusplus
}
#endif

#include <arch/ppc/vxPpc.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Use constant size if known (when building for a specific CPU type)
 * else fetch from a global variable (when building for generic PPC32)
 */
#undef	_CACHE_ALIGN_SIZE
#ifdef	_CPU_CACHE_ALIGN_SIZE
#define	_CACHE_ALIGN_SIZE	_CPU_CACHE_ALIGN_SIZE
#else	/* _CPU_CACHE_ALIGN_SIZE */
# ifndef _ASMLANGUAGE
# define  _CACHE_ALIGN_SIZE	_ppcCacheLineSize
  extern  int	_ppcCacheLineSize;
# endif   /* _ASMLANGUAGE */
#endif	/* _CPU_CACHE_ALIGN_SIZE */

#ifdef	_WRS_CONFIG_LP64
/* override the symbols name */

#define vxSdaInit	vxTocInit
#endif	/* _WRS_CONFIG_LP64 */

#ifdef __cplusplus
}
#endif

#include <arch/ppc/archPpcCommon.h>

#include <arch/ppc/toolPpc.h>

/*
 * VX_OBJ_ALIGN_SIZE is the default allocation boundary for kernel objects.  
 * This is used for both statically and dynamically allocated objects.
 */

#define VX_OBJ_ALIGN_SIZE	8

#endif /* __INCarchPpch */
