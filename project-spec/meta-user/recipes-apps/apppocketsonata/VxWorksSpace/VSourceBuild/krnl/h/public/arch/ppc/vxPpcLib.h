/* vxPpcLib.h - header for board dependent library routines for the PowerPC */

/*
 * Copyright (c) 1996-1997, 2000-2004, 2006-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20nov14,ylu  LP64 adaptation to support PPC64.(F2518)
12jul14,syt  added support for _WRS_CONFIG_PPC_60x.(F2505)
03dec12,pcs  Decouple macro PPC_e500mc for e6500 core.
03may11,syt  add support for PPC465.
09oct10,x_z  add support for PPC476.
26apr10,pmr  add L1CSR2 funcs
10seo09,x_z  add vxSvrGet()
20nov08,pmr  remove vxHid1Get/Set for e500mc
04sep08,pmr  e500mc hard float
13jun07,mmi  import vxIctcSet() and vxIctcGet(), vxC1StateSet(), removed
		 deprecated API, added copyright notice
02may07,dcc  added declaration of vxSdaSet().
26oct06,to   SMP: moved vxCpuIndexGet to vxCpuLib.h
24aug06,to   SMP: added vxCpuIndexGet
09jun04,rec  add 32-bit access routines for PPC970 HID registers
22apr04,to   delete K&R prototypes.
18mar04,rec  PPC970 merges
25mar04,dtr  Add vxIvor1Set.
31mar03,dtr  Adding vxHid1Set function.
12nov02,mil  Updated support for PPCE500.
02aug02,pcs  Add support for PPCE500 and make it the same as PPC603 for
             the present.
28jan02,rcs  added vxImmrIsbGet() and vxImmrDevGet()
24oct01,jtp  Add support for 440 decrementer
22oct01,dtr  Inclusion of vxKeyedDecReload function for some 860 bsps.
             SPR65678.
08oct01,mil  added comments to various prototypes (SPR 9221).
15aug01,pch  Add support for PPC_NO_REAL_MODE & PPC440
02may01,dat  65984, Portable C Code, added vxDecReload, vxHid1Get
25oct00,s_m  renamed PPC405 cpu types
12jun00,alp  Added PPC405 support
22mar00,tam  added missing prototypes for PPC860
14jul97,mas  prototypes for accessing DAR, DSISR, SRR0, SRR1 (SPR 8918).
31mar97,tam  added prototypes for DMA register access routines. 
10feb97,tam  added prototypes for vxFpscrGet/Set()
29oct96,tam  added prototypes for vxPowerDown() , vxPowerModeSet() and
		 vxPowerModeGet(); added power management mode macros.
18jun96,tam  added prototypes for PPC403 debug register access routines.
17jun96,tpr  added vxDerGet(), vxDerSet(), vxImmrGet() and
		 vxImmrSet() prototypes.
29may96,tam  added prototypes for vxTimeBaseSet/Get (spr #6604).
28feb96,tam  added some PPC403 declarations.
23feb96,tpr  written.
*/

#ifndef __INCvxPpcLibh
#define __INCvxPpcLibh

#ifdef __cplusplus
extern "C" {
#endif

/* DMA channel definition for the vxDmaXXGet/Set() routines */

#define	DMA_CHANNEL_0		0
#define	DMA_CHANNEL_1		1
#define	DMA_CHANNEL_2		2
#define	DMA_CHANNEL_3		3

/* function declarations */

#ifndef	_ASMLANGUAGE

IMPORT void	vxMsrSet (_RType);          /* machine status reg */
IMPORT _RType	vxMsrGet (void);
IMPORT void     vxSdaSet (void * pRegs);

#if	(defined (_WRS_CONFIG_PPC_E500))
IMPORT UINT32   vxDearGet (void);           /* data exc addr reg */
IMPORT void     vxDearSet (UINT32);
IMPORT UINT32	vxCsrr0Get (void);          /* save/restore reg 0 */
IMPORT void	vxCsrr0Set (UINT32);
IMPORT UINT32	vxCsrr1Get (void);          /* save/restore reg 1 */
IMPORT void	vxCsrr1Set (UINT32);
IMPORT UINT32	vxMcsrr0Get (void);         /* save/restore reg 0 */
IMPORT void	vxMcsrr0Set (UINT32);
IMPORT UINT32	vxMcsrr1Get (void);         /* save/restore reg 1 */
IMPORT void	vxMcsrr1Set (UINT32);
#ifdef _WRS_SPE_SUPPORT
IMPORT UINT32	vxSpefscrGet (void);        /* FP status control reg */
IMPORT void	vxSpefscrSet (UINT32);
#endif /* _WRS_SPE_SUPPORT */
IMPORT void	vxDecarSet (UINT32);        /* dec auto reload reg */
IMPORT UINT32	vxL1CSR0Get (void);         /* L1 control status reg 0 */
IMPORT void	vxL1CSR0Set (UINT32);
IMPORT UINT32	vxL1CSR1Get (void);         /* L1 control status reg 1 */
IMPORT void	vxL1CSR1Set (UINT32);
#ifdef L1CSR2
IMPORT UINT32	vxL1CSR2Get (void);         /* L1 control status reg 2 */
IMPORT void	vxL1CSR2Set (UINT32);
#endif /* L1CSR2 */
IMPORT UINT32	vxL1CFG0Get (void);         /* L1 config reg 0 */
IMPORT UINT32	vxL1CFG1Get (void);         /* L1 config reg 1 */
IMPORT void	vxIvor1Set (UINT32);        /* Set Mchk exception offset */
#else	/* defined (_WRS_CONFIG_PPC_E500) */
IMPORT void     vxDarSet (UINT32);          /* data addr reg */
IMPORT UINT32   vxDarGet (void);
IMPORT void	vxDsisrSet (UINT32);        /* DSI source reg */
IMPORT UINT32	vxDsisrGet (void);
#endif	/* defined (_WRS_CONFIG_PPC_E500) */

IMPORT void	vxSrr0Set (UINT32);         /* save/restore reg 0 */
IMPORT UINT32	vxSrr0Get (void);
IMPORT void	vxSrr1Set (UINT32);         /* save/restore reg 1 */
IMPORT UINT32	vxSrr1Get (void);
IMPORT UINT32	vxFirstBit (UINT32);        /* get 1st bit set using cntlzw */
IMPORT UINT32	vxPvrGet (void);            /* processor version reg */

#if (CPU == PPC603) || (CPU == PPC604) || (defined (_WRS_CONFIG_PPC_E500))
IMPORT UINT32	vxSvrGet (void);            /* system version reg */
#endif

IMPORT UINT32 (*_func_vxSvrGet) (void);
#define _PPC_VX_SVR_GET ((_func_vxSvrGet == NULL) ? 0 : (_func_vxSvrGet) ())

IMPORT void	vxDecSet (UINT32);          /* decrementer reg */
IMPORT UINT32	vxDecGet (void);
IMPORT UINT32	vxDecReload (UINT32);       /* reload with lantency skew adj */

# if	(CPU == PPC970)
IMPORT void	vxHid0Set (UINT64 *);       /* hardware imp dependent reg 0 */
IMPORT void	vxHid1Set (UINT64 *);       /* hardware imp dependent reg 1 */
IMPORT void	vxHid4Set (UINT64 *);       /* hardware imp dependent reg 4 */
IMPORT void	vxHid5Set (UINT64 *);       /* hardware imp dependent reg 5 */

IMPORT void	vxHid0Get (UINT64 *);       /* hardware imp dependent reg 0 */
IMPORT void	vxHid1Get (UINT64 *);       /* hardware imp dependent reg 1 */
IMPORT void	vxHid4Get (UINT64 *);       /* hardware imp dependent reg 4 */
IMPORT void	vxHid5Get (UINT64 *);       /* hardware imp dependent reg 5 */

IMPORT UINT32	vxHid0LGet (void);      /* hardware imp dependent reg 0 Low */
IMPORT UINT32	vxHid1LGet (void);      /* hardware imp dependent reg 1 Low */
IMPORT UINT32	vxHid4LGet (void);      /* hardware imp dependent reg 4 Low */
IMPORT UINT32	vxHid5LGet (void);      /* hardware imp dependent reg 5 Low */
IMPORT UINT32	vxHid0HGet (void);      /* hardware imp dependent reg 0 High */
IMPORT UINT32	vxHid1HGet (void);      /* hardware imp dependent reg 1 High */
IMPORT UINT32	vxHid4HGet (void);      /* hardware imp dependent reg 4 High */
IMPORT UINT32	vxHid5HGet (void);      /* hardware imp dependent reg 5 High */
#else	/* CPU == PPC970 */
IMPORT void	vxHid0Set (UINT32);         /* hardware imp dependent reg 0 */
IMPORT UINT32	vxHid0Get (void);
# if (!defined(PPC_e500mc) && !defined(PPC_e6500))
IMPORT void	vxHid1Set (UINT32);         /* hardware imp dependent reg 1 */
IMPORT UINT32	vxHid1Get (void);            
# endif /* !PPC_e500mc && !PPCe6500 */

# if (defined(PPC_e500mc) || defined(PPC_e6500))
IMPORT void	vxEpcrSet (UINT32);	/* embedded processor control reg */
IMPORT UINT32	vxEpcrGet (void);	/* embedded processor control reg */
# endif /* PPC_e500mc */

#if (CPU == PPC603)
IMPORT void     vxHid2Set (UINT32);     /* hardware imp dependent reg 2 */
IMPORT UINT32   vxHid2Get (void);            
#endif /* CPU == PPC603 */

# ifdef _PPC_745x
IMPORT UINT32	vxIctcGet (void);           /* Get Instruction cache throttling reg */
IMPORT void	vxIctcSet (UINT32);         /* Set hardware cache throttling reg    */ 
# endif /* _PPC_745x */
#endif	/* CPU == PPC970 */
# ifdef _WRS_ARCH_HAS_DPM
IMPORT void	vxDpmSet (BOOL setDpmBit);
# endif /* _WRS_ARCH_HAS_DPM */
IMPORT void	vxC1StateSet (void);
IMPORT void	vxTimeBaseSet (UINT32 tbu, UINT32 tbl); /* time base up/lower */
IMPORT void	vxTimeBaseGet (UINT32 * pTbu, UINT32 * pTbl);
IMPORT void	vxFpscrSet (UINT32);        /* FP status control reg */
IMPORT UINT32	vxFpscrGet (void);

#if 	((CPU == PPC403) || (CPU == PPC405) || (CPU == PPC405F) || \
	 (CPU == PPC440) || (defined (_WRS_CONFIG_PPC_E500)) || (CPU == PPC476) || (CPU == PPC465))

# if	((CPU == PPC440) || (defined (_WRS_CONFIG_PPC_E500)) || (CPU == PPC476) || (CPU == PPC465))
IMPORT void     vxDecIntEnable (void);
IMPORT void     vxDecIntAck (void);
#else	/* CPU == PPC440, PPCE500, PPC476 , PPC465 */
IMPORT UINT32	vxExierEnable (UINT32);     /* ext interrupt enable reg */
IMPORT UINT32	vxExierDisable (UINT32);
IMPORT void     vxPitSet (UINT32);          /* prog interval timer */
IMPORT UINT32   vxPitGet (void);
IMPORT void     vxPitIntEnable (void);      /* timer ctrl reg set PIT int en */
IMPORT void     vxPitIntAck (void);         /* clear TSR PIT pending bit */
# endif	/* CPU == PPC440, PPCE500, PPC476, PPC465 */

IMPORT void     vxFitIntEnable (void);      /* timer ctrl reg set FIT int en */
IMPORT void     vxFitIntDisable (void);
IMPORT void     vxFitIntAck (void);         /* clear TSR FIT pending bit */

# if	!((CPU == PPC440) || (defined (_WRS_CONFIG_PPC_E500)) || (CPU == PPC476) || (CPU == PPC465))
IMPORT UINT32   vxExisrGet (void);          /* ext interrupt status reg */
IMPORT void     vxExisrClear (UINT32);
IMPORT UINT32   vxExierGet (void);          /* ext interrupt enable reg */
IMPORT void     vxExierSet (UINT32);
# endif	/* CPU != PPC440, PPCE500, PPC476, PPC465 */

# ifndef  PPC_NO_REAL_MODE
IMPORT UINT32   vxDccrGet (void);           /* data cache ctrl reg */
IMPORT void     vxDccrSet (UINT32);
IMPORT UINT32   vxIccrGet (void);           /* instr cache ctrl reg */
IMPORT void     vxIccrSet (UINT32);
# endif  /* PPC_NO_REAL_MODE */

# if	((CPU == PPC440) || (defined (_WRS_CONFIG_PPC_E500)) || (CPU == PPC476) || (CPU == PPC465))
IMPORT ULONG   vxIvprGet (void);
IMPORT void     vxIvprSet (ULONG);
# else	/* CPU == PPC440, PPCE500, PPC476, PPC465 */
IMPORT UINT32   vxEvprGet (void);           /* exception prefix reg */
IMPORT void     vxEvprSet (UINT32);
IMPORT UINT32   vxIocrGet (void);           /* input/ouput config reg */
IMPORT void     vxIocrSet (UINT32);
# endif	/* CPU == PPC440, PPCE500, PPC476, PPC465 */

IMPORT UINT32   vxTcrGet (void);            /* timer ctrl reg */
IMPORT void     vxTcrSet (UINT32);
IMPORT UINT32   vxTsrGet (void);            /* timer status reg */
IMPORT void     vxTsrSet (UINT32);

# if	((CPU == PPC440) || (defined (_WRS_CONFIG_PPC_E500)) || (CPU == PPC476) || (CPU == PPC465))
IMPORT UINT32   vxDbcr0Get (void);
IMPORT void     vxDbcr0Set (UINT32);
IMPORT UINT32   vxDbcr1Get (void);
IMPORT void     vxDbcr1Set (UINT32);
IMPORT UINT32   vxDbcr2Get (void);
IMPORT void     vxDbcr2Set (UINT32);
#	if ((CPU == PPC440) || (CPU == PPC476) || (CPU == PPC465))
IMPORT UINT32   vxDbdrGet (void);
IMPORT void     vxDbdrClear (UINT32);
#	endif  /* CPU == PPC440, PPC476, PPC465 */
# else	/* CPU == PPC440, PPCE500, PPC476, PPC465 */
IMPORT void     vxBesrSet (UINT32);         /* bus error syndrome reg */
IMPORT UINT32   vxDbcrGet (void);           /* debug ctrl reg */
IMPORT void     vxDbcrSet (UINT32);
# endif	/* CPU == PPC440, PPCE500, PPC476, PPC465 */

IMPORT UINT32   vxDbsrGet (void);           /* debug status reg */
IMPORT void     vxDbsrClear (UINT32);
IMPORT UINT32   vxDac1Get (void);           /* data addr cmp reg 1 */
IMPORT void     vxDac1Set (UINT32);
IMPORT UINT32   vxDac2Get (void);           /* data addr cmp reg 2 */
IMPORT void     vxDac2Set (UINT32);
IMPORT UINT32   vxIac1Get (void);           /* instr addr cmp reg 1 */
IMPORT void     vxIac1Set (UINT32);
IMPORT UINT32   vxIac2Get (void);           /* instr addr cmp reg 2 */
IMPORT void     vxIac2Set (UINT32);

# if	(CPU == PPC403)
IMPORT void	vxDmacrSet (UINT32 regVal, UINT32 dmaRegNo);
IMPORT UINT32	vxDmacrGet (UINT32 dmaRegNo);
IMPORT void	vxDmasrSet (UINT32 regVal);
IMPORT UINT32	vxDmasrGet (void);
IMPORT void	vxDmaccSet (UINT32 regVal, UINT32 dmaRegNo);
IMPORT UINT32	vxDmaccGet (UINT32 dmaRegNo);
IMPORT void	vxDmactSet (UINT32 regVal, UINT32 dmaRegNo);
IMPORT UINT32	vxDmactGet (UINT32 dmaRegNo);
IMPORT void	vxDmadaSet (UINT32 regVal, UINT32 dmaRegNo);
IMPORT UINT32	vxDmadaGet (UINT32 dmaRegNo);
IMPORT void	vxDmasaSet (UINT32 regVal, UINT32 dmaRegNo);
IMPORT UINT32	vxDmasaGet (UINT32 dmaRegNo);
# elif	(!defined (_WRS_CONFIG_PPC_E500))	/* i.e. non-403/non-85XX */
IMPORT UINT32   vxIac3Get (void);
IMPORT void     vxIac3Set (UINT32);
IMPORT UINT32   vxIac4Get (void);
IMPORT void     vxIac4Set (UINT32);
# endif	/* CPU == PPC403 : PPCE500 */

#endif	/* CPU == PPC4xx, PPCE500 */

#if 	((CPU == PPC603) || (CPU == PPC604))
IMPORT  UINT32  vxImmrDevGet (void);        /* Get PART/MASK bits of IMMR */
IMPORT  UINT32  vxImmrIsbGet (void);        /* Get ISB bits of IMMR */
#endif	/* (CPU == PPC603) || (CPU == PPC604) */

#if	(CPU == PPC860)
IMPORT	void	vxImmrSet (UINT32);         /* internal mem map reg */
IMPORT	UINT32	vxImmrGet (void);
IMPORT	UINT32	vxImmrDevGet (void);        /* Get PART/MASK bits of IMMR */
IMPORT	UINT32	vxImmrIsbGet (void);        /* Get ISB bits of IMMR */
IMPORT	void	vxDerSet (UINT32);          /* debug enable reg */
IMPORT	UINT32	vxDerGet (void);
IMPORT  UINT32	vxKeyedDecReload (UINT32);  /* vxDecReload a locked DEC */
IMPORT	void	vxMTwbSet (UINT32);         /* MMU table walk base reg */
IMPORT	UINT32	vxMTwbGet (void);
IMPORT	void	vxMdCtrSet (UINT32);        /* data MMU ctrl reg */
IMPORT	UINT32	vxMdCtrGet (void);
IMPORT	void	vxMiCtrSet (UINT32);        /* instr MMU ctrl reg */
IMPORT	UINT32	vxMiCtrGet (void);
IMPORT	void	vxIcCstSet (UINT32);        /* instr cache ctrl status reg */
IMPORT	UINT32	vxIcCstGet (void);
IMPORT	void	vxIcAdrSet (UINT32);        /* instr cache addr reg */
IMPORT	UINT32	vxIcAdrGet (void);
IMPORT	UINT32	vxIcDatGet (void);          /* instr cache data port */
IMPORT	void	vxDcCstSet (UINT32);        /* data cache ctrl status reg */
IMPORT	UINT32	vxDcCstGet (void);
IMPORT	void	vxDcAdrSet (UINT32);        /* data cache addr reg */
IMPORT	UINT32	vxDcAdrGet (void);
#endif	/* (CPU == PPC860) */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxPpcLibh */
