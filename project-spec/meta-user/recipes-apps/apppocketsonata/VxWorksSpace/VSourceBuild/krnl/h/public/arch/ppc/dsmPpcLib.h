/* dsmPpc.h - PowerPC disassembler header */

/*
 * Copyright 1994-1998, 2000-2004, 2006-2007, 2010-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17dec14,w_x  Added instructions for PPC64 support (F2518).
20nov14,ylu  LP64 adaptation to support PPC64.(F2518)
10oct13,h_k  moved S_dsmLib_UNKNOWN_INSTRUCTION definition to dsmLib.h.
09apr13,d_l  fixed build warnings. (WIND00358283)
16nov12,pcs  Add support for e6500
25oct11,kab  Fix integer conversion warnings
14sep11,syt  added support for PPC465.
01mar11,x_z  added support for PPC476 and fixed support for MPC85XX.
29jul10,pad  Moved extern C statement after include statements.
18jul07,pch  CQ87449: blrl & bctrl are function calls; renumber from 19feb03
26jun07,tbu  Added 64 bit support
	   +p_b  completed support
17jan06,mmi  Add dsmFindByName() and dsmFindByInst() prototypes
19oct04,to   fix SPR#75831
18dec03,elg  Add definition of sc instruction.
19feb03,x_p  Fix host build
08oct03,mil  Fixed typo for _ESOP on host.
16jun03,mil  Added E500 instructions.
23jan03,pch  Add isel for 440x5 core (440GX)
05dec02,pch  SPR 84100: correctly decode WS field for 4xx tlbre/tlbwe
18sep01,pch  created by merging target/h/arch/ppc/dsmPpcLib.h vn 01o
		 and host/src/tgtsvr/disassembler/dsmPpc.h vn 02j
		 Also added selective handling of processor-specific SPR's
		 and instructions in the host disassembler based on the
		 cpuType of the currently-connected target.

Following are the history entries from the merged files

    07sep01,pch  Improve comments, cleanup; remove MAX_SPR_LEN (no longer used)
    01jun01,dtr  Adding IFORM_VA1B which is needed because input vectors
                 swapped in PIM for two instructions vmaddfp,vnmsubfp.
    29may01,dtr  IFORM_VA_1&2 in the wrong place.
    02may01,kab  Fix duplicate case after merge.
    30apr01,dtr  Correcting merge problems.
    14dec00,s_m  changed IFIELD_WS4 to IFIELD_WS
    09dec00,jrs  Fix WS field.
    07dec00,dtr  Support for Altivec Instruction set.
    05dec00,jrs  Add field type for 405 TLB instructions.
    30nov00,jrs  Add IBM 405 MAC and TLB instructions.
    17nov00,jrs  Add PPC405GP changes.
    20apr98,fle  functions renaming
    03sep97,fle  Modified for being used by the WTX_MEM_DISASSEMBLE service.
    26jul96,tam  added definition for MAX_SPR_LEN, DSTRING_BUF_MAX_SIZE
		 and _IFORM_D_9.
    18jun96,tam  added definition for MAX_SPR_LEN and _IFORM_D_9.
    07jun96,kkk  added endian argument to dsmXXXInst and dsmXXXNbytes
    02feb96,ms   fixed INST_STWU_SP.
    02jan96,elp	 adapted for Tornado.
    13feb95,caf  added sign extension to branch displacement (_IFIELD_BD).
    10feb95,caf  added PPC403 support.
    31jan95,yao  added more macros for branch instructions.
    07nov94,yao  added macros for instructions used by dbgLib and trcLib.
    19aug94,caf  created.
*/

#ifdef	HOST
#include "wtxtypes.h"
#endif	/* HOST */

#ifndef __INCdsmPpch
#define __INCdsmPpch

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef struct	/* instruction descriptor */
    {
    char *	name;	/* mnemonic				      */
    UINT32	op;	/* fixed bits				      */
    UINT16	form;	/* form:  major classifier, index into mask[] */
    UINT16	flags;	/* classification flags:  _IFLAG_*	      */
    } INST;

typedef struct	/* SPR/DCR/PMR descriptor */
    {
    int		code;	/* number */
    char *	name;	/* name   */
    } SPR;

/* defines */

#  define _OP(opcd, xo)       ((UINT32) (((opcd) << 26) + ((xo) << 1)))
#  define _VOP(opcd, xo)      ((UINT32) (((opcd) << 26) + (xo)))    /* altivec/spe */
#  define _ESOP(opcd, xo)     ((UINT32) (((opcd) << 26) + ((xo) << 3)))   /* evsel */
#  define _DMOP(opcd, xo)     ((UINT32) (((opcd) << 26) + ((xo) << 2)))
#  define _DSOP(opcd, xo)     ((UINT32) (((opcd) << 26) + ((xo) << 0)))

/* instruction forms */

#define _IFORM_I_1      0
#define _IFORM_B_1      1
#define _IFORM_SC_1     2
#define _IFORM_D_1      3
#define _IFORM_D_2      4
#define _IFORM_D_3      5
#define _IFORM_D_4      6
#define _IFORM_D_5      7
#define _IFORM_D_6      8
#define _IFORM_D_7      9
#define _IFORM_D_8      10
#define _IFORM_X_1      11
#define _IFORM_X_2      12
#define _IFORM_X_3      13
#define _IFORM_X_4      14
#define _IFORM_X_5      15
#define _IFORM_X_6      16
#define _IFORM_X_7      17
#define _IFORM_X_8      18
#define _IFORM_X_9      19
#define _IFORM_X_10     20
#define _IFORM_X_11     21
#define _IFORM_X_12     22
#define _IFORM_X_13     23
#define _IFORM_X_14     24
#define _IFORM_X_15     25
#define _IFORM_X_16     26
#define _IFORM_X_17     27
#define _IFORM_X_18     28
#define _IFORM_X_19     29
#define _IFORM_X_20     30
#define _IFORM_X_21     31
#define _IFORM_X_22     32
#define _IFORM_X_23     33
#define _IFORM_X_24     34
#define _IFORM_X_25     35
#define _IFORM_X_26     36
#define _IFORM_X_27     37
#define _IFORM_XL_1     38
#define _IFORM_XL_2     39
#define _IFORM_XL_3     40
#define _IFORM_XL_4     41
#define _IFORM_XFX_1    42
#define _IFORM_XFX_2    43
#define _IFORM_XFX_3    44
#define _IFORM_XFX_4    45
#define _IFORM_XFL_1    46
#define _IFORM_XO_1     47
#define _IFORM_XO_2     48
#define _IFORM_XO_3     49
#define _IFORM_A_1      50
#define _IFORM_A_2      51
#define _IFORM_A_3      52
#define _IFORM_A_4      53
#define _IFORM_M_1      54
#define _IFORM_M_2      55
#define _IFORM_D_9	56
#define _IFORM_400_1	57	/*  mfdcr  (PPC4xx only) */
#define _IFORM_400_2	58	/*  mtdcr  (PPC4xx only) */
#define _IFORM_400_3	59	/*  wrteei (PPC4xx only) */
#define	_IFORM_405_TLB	60	/*  tlbre, tlbwe (PPC405/440 only) */
#define	_IFORM_405_SX	61	/*  tlbsx (PPC405/440 only) */
#define _IFORM_VA_1	62	/*  altivec only */
#define _IFORM_VA_2	63	/*  altivec only */
#define _IFORM_VX_1	64	/*  altivec only */
#define _IFORM_VX_2	65	/*  altivec only */
#define _IFORM_VX_3	66	/*  altivec only */
#define _IFORM_VX_4	67	/*  altivec only */
#define _IFORM_VX_5	68	/*  altivec only */
#define _IFORM_VX_6	69	/*  altivec only */
#define _IFORM_X_28	70	/*  altivec only */
#define _IFORM_X_29	71	/*  altivec only */
#define _IFORM_X_30	72	/*  altivec only */
#define _IFORM_X_31	73	/*  altivec only */
#define _IFORM_X_32	74	/*  altivec only */
#define _IFORM_X_33	75	/*  altivec only */
#define _IFORM_VXR_1	76	/*  altivec only */
#define _IFORM_VA_1B	77	/*  altivec only */
#define _IFORM_M_3	78	/*  isel (440x5/85xx) */
#define _IFORM_X_34	79	/*  e500 mbar with MO field */
#define _IFORM_X_35	80      /*  e500 wrteei   */
#define _IFORM_X_36	81      /*  e500 tlbivax  */
#define _IFORM_X_37	82      /*  e500 tlbsx    */
#define _IFORM_X_38	83      /*  e500 tlbre    */
#define _IFORM_XFX_5    84      /*  e500 mfpmr    */
#define _IFORM_XFX_6	85      /*  e500 mtpmr    */
#define _IFORM_EVS_1	86	/*  evsel (e500 spe version of isel) */
#define _IFORM_EFX_1	87	/*  e500 spe only */
#define _IFORM_EFX_2	88	/*  e500 spe only */
#define _IFORM_EFX_3	89	/*  e500 spe only */
#define _IFORM_EFX_4	90	/*  e500 spe only */
#define _IFORM_EVX_1	91	/*  e500 spe only */
#define _IFORM_EVX_2	92	/*  e500 spe only */
#define _IFORM_EVX_3	93	/*  e500 spe only */
#define _IFORM_EVX_4	94	/*  e500 spe only */
#define _IFORM_EVX_5	95	/*  e500 spe only */
#define _IFORM_EVX_6	96	/*  e500 spe only */
#define _IFORM_EVX_7	97	/*  e500 spe only */
#define _IFORM_EVX_8	98	/*  e500 spe only */
#define _IFORM_EVX_9	99	/*  e500 spe only */
#define _IFORM_EVX_10  100	/*  e500 spe only */
#define _IFORM_EVX_11  101	/*  e500 spe only */
#define _IFORM_EVX_12  102	/*  e500 spe only */
#define _IFORM_EVX_13  103	/*  e500 spe only */
#define _IFORM_EVX_14  104	/*  e500 spe only */

/* cache instructions with CT field for PPCE500 and PPC476 */

#define _IFORM_X_39    105	/*  dci/ici/dccci/iccci with CT field */
#define _IFORM_X_40    106	/*  other cache instructions with CT field */

/* DCR extend instructions for PPC46x/PPC47x */

#define _IFORM_400_DCRX 107	/*  mfdcrx/mfdcrux/mtdcrx/mtdcrux (PPC4xx only) */

#define _IFORM_XFX_7    108   /* mttmr */
#define _IFORM_XFX_8    109   /* mftmr */
#define _IFORM_X_41     110   /* wait WC, WH */
#define _IFORM_MD_1     111   /* rldicl */
#define _IFORM_MDS_1    112   /* rldcl */
#define _IFORM_DS_1     113   /* ld */
#define _IFORM_XS_1     114   /* sradi */
#define _IFORM_X_42     115   /* ldarx */
#define _IFORM_DQ_1     116   /* lq */

/* instruction classification flags:  append char to opcode if bit is set */

#define _IFLAG_OE	0x0001	/* includes XER bit		'o' */
#define _IFLAG_RC	0x0002	/* includes record bit		'.' */
#define _IFLAG_AA	0x0004	/* includes absolute bit	'a' */
#define _IFLAG_LK	0x0008	/* includes link bit		'l' */
#define _IFLAG_VRC	0x0200	/* includes altivec record bit	'.' */

/* Flags for processor-specific instructions */
#define _IFLAG_601_SPEC 0x0010		/* 601-specific          */
#define _IFLAG_603_SPEC 0x0020		/* 603-specific          */
#define _IFLAG_604_SPEC 0x0040		/* 604-specific          */
#define _IFLAG_403_SPEC 0x0080		/* 403-specific          */
#define	_IFLAG_405_SPEC	0x0100		/* 405-specific          */
#define	_IFLAG_AV_SPEC	0x0400		/* altivec-specific      */
#define	_IFLAG_440_SPEC	0x0800		/* 440-specific          */
#define	_IFLAG_FP_SPEC	0x1000		/* floating point        */
#define	_IFLAG_E500_SPEC 0x2000		/* E500-specific         */
#define	_IFLAG_476_SPEC	0x4000		/* 476-specific          */
#define	_IFLAG_465_SPEC	0x8000		/* 465-specific          */

/* shorthand for table construction */
#define	_IFLAG_6XX_SPEC	(_IFLAG_601_SPEC | _IFLAG_603_SPEC | _IFLAG_604_SPEC)
#define	_IFLAG_4XX_SPEC	(_IFLAG_403_SPEC | _IFLAG_405_SPEC | _IFLAG_440_SPEC | \
    _IFLAG_476_SPEC | _IFLAG_465_SPEC)

/* TLB handling as in 405, 440 and 465 */
#define	_IFLAG_4XTLB	(_IFLAG_405_SPEC | _IFLAG_440_SPEC | _IFLAG_465_SPEC)

/* MAC instructions as in 405, 440 and 465 */
#define	_IFLAG_MAC	(_IFLAG_405_SPEC | _IFLAG_440_SPEC | _IFLAG_465_SPEC)

/* If any are set, instruction is not generic */
#define	_IFLAG_SPEC	(_IFLAG_4XX_SPEC | _IFLAG_6XX_SPEC | _IFLAG_AV_SPEC | \
			 _IFLAG_E500_SPEC | _IFLAG_FP_SPEC)

/* instruction fields */

#define _IFIELD_AA(x)	((0x00000002 & x) >>  1)    /* absolute address      */
#define _IFIELD_BD(x)	((0x00008000 & x) ? (0xffff0000 | (x & ~3)) : \
                                            (0x0000fffc & x))
                                                    /* ^ signed branch displ */
#define _IFIELD_BI(x)   ((0x001f0000 & x) >> 16)    /* branch condition      */
#define _IFIELD_BO(x)   ((0x03e00000 & x) >> 21)    /* branch options        */
#define _IFIELD_CRBA(x) ((0x001f0000 & x) >> 16)    /* source CR bit         */
#define _IFIELD_CRBB(x) ((0x0000f800 & x) >> 11)    /* source CR bit         */
#define _IFIELD_CRBD(x) ((0x03e00000 & x) >> 21)    /* dest [FPS]CR bit      */
#define _IFIELD_CRFD(x) ((0x03800000 & x) >> 23)    /* dest [FPS]CR field    */
#define _IFIELD_CRFS(x) ((0x001c0000 & x) >> 18)    /* source [FPS]CR field  */
#define _IFIELD_CRM(x)  ((0x000ff000 & x) >> 12)    /* CR field mask         */
#define _IFIELD_D(x)    ((0x0000ffff & x))	    /* ^ signed 16b integer  */
#define _IFIELD_D_S(x)	((0x00008000 & x) ? (0xffff0000 | x) : \
					    (0x0000ffff & x))
						    /* ^ signed 16b integer  */
#define _IFIELD_FM(x)   ((0x01fe0000 & x) >> 17)    /* FPSCR field mask      */
#define _IFIELD_FRA(x)  ((0x001f0000 & x) >> 16)    /* source FPR            */
#define _IFIELD_FRB(x)  ((0x0000f800 & x) >> 11)    /* source FPR            */
#define _IFIELD_FRC(x)  ((0x000007c0 & x) >>  6)    /* source FPR            */
#define _IFIELD_FRD(x)  ((0x03e00000 & x) >> 21)    /* dest FPR              */
#define _IFIELD_FRS(x)  ((0x03e00000 & x) >> 21)    /* source FPR            */
#define _IFIELD_IMM(x)  ((0x0000f000 & x) >> 12)    /* data for FPSCR        */
#define _IFIELD_L(x)    ((0x00200000 & x) >> 21)    /* 64-bit flag (ignored) */
#define _IFIELD_LI(x)	((0x02000000 & x) ? ((0xf6000000 | x) & ~3) : \
                                            ((0x03fffffc & x) & ~3))
                                                    /* ^ signed 24b integer  */
#define _IFIELD_LK(x)   ((0x00000001 & x) >>  0)    /* link                  */
#define _IFIELD_MB(x)   ((0x000007c0 & x) >>  6)    /* mask begin (split)    */
#define _IFIELD_ME(x)   ((0x0000003e & x) >>  1)    /* mask end (split)      */
#define _IFIELD_NB(x)   ((0x0000f800 & x) >> 11)    /* number of bytes       */
#define _IFIELD_OE(x)   ((0x00000400 & x) >> 10)    /* enable setting OV, SO */
#define _IFIELD_OPCD(x) ((0xfc000000 & x) >> 26)    /* primary opcode        */
#define _IFIELD_RA(x)   ((0x001f0000 & x) >> 16)    /* source or dest GPR    */
#define _IFIELD_VA(x)   ((0x001f0000 & x) >> 16)    /* source VR    */
#define _IFIELD_MB6(x)  (((0x000007c0 & x) >>  6) | (x & 0x20))    /* mask begin (split)    */

#define _IFIELD_RB(x)   ((0x0000f800 & x) >> 11)    /* source GPR            */
#define	_IFIELD_WS(x)	((0x0000f800 & x) >> 11)   /* 4xx tlbre/tlbwe WS fld */
#define _IFIELD_VB(x)   ((0x0000f800 & x) >> 11)    /* source VR             */
#define _IFIELD_VC(x)   ((0x000007c0 & x) >>  6)    /* source VR             */
#define _IFIELD_RC(x)   ((0x00000001 & x) >>  0)    /* record                */
#define _IFIELD_VRC(x)  ((0x00000400 & x) >> 10)    /* record                */
#define _IFIELD_RD(x)   ((0x03e00000 & x) >> 21)    /* dest GPR              */
#define _IFIELD_VD(x)   ((0x03e00000 & x) >> 21)    /* destination VR	     */
#define _IFIELD_RS(x)   ((0x03e00000 & x) >> 21)    /* source GPR            */

/* RT for mfdcrx/mfdcrux and RA for mtdcrx/mtdcrux */

#define _IFIELD_RTA(x)   ((0x03e00000 & x) >> 21)

/* RA for mfdcrx/mfdcrux and RS for mtdcrx/mtdcrux */

#define _IFIELD_RAS(x)   ((0x001f0000 & x) >> 16)

#define _IFIELD_VS(x)   ((0x03e00000 & x) >> 21)    /* source VR	     */
#define _IFIELD_SH(x)   ((0x0000f800 & x) >> 11)    /* shift amount (split)  */
#define _IFIELD_SH6(x)  (_IFIELD_SH(x)) | ((0x00000002 & x) << 4)    /* shift amount (split)  */
#define _IFIELD_VSH(x)  ((0x000003c0 & x) >>  6)   /* shift amount for vector */
#define _IFIELD_SIMM(x) ((0x0000ffff & x))
#define _IFIELD_SIMM_S(x) ((0x00008000 & x) ? (0xffff0000 | x) : \
                                            (0x0000ffff & x))
                                                    /* ^ signed 16b integer  */
#define _IFIELD_VSIMM(x) ((0x00100000 & x) ? (0xffffffe0 | (x>>16)) : \
                                            (0x0000001f & (x>>16)))
                                                    /* ^ signed 5b integer   */
#define _IFIELD_SPR(x)  (((0x001f0000 & x) >> 16) |   \
                         ((0x0000f800 & x) >>  6))  /* mtspr, mfspr (split)  */
#define _IFIELD_SR(x)   ((0x000f0000 & x) >> 16)    /* segment register      */
#define _IFIELD_TBR(x)  ((0x001ff800 & x) >> 11)    /* TBL, TBU (split)      */
#define _IFIELD_TO(x)   ((0x03e00000 & x) >> 21)    /* trap conditions       */
#define _IFIELD_UIMM(x) ((0x0000ffff & x) >>  0)    /* unsigned 16b integer  */
#define _IFIELD_VUIMM(x) ((0x001f0000 & x)>> 16)    /* unsigned 5b integer   */

#define _IFIELD_XO_1(x) ((0x000007fe & x) >>  1)    /* extended op 1 (21-30) */
#define _IFIELD_XO_2(x) ((0x000003fe & x) >>  1)    /* extended op 2 (22-30) */
#define _IFIELD_XO_3(x) ((0x0000003e & x) >>  1)    /* extended op 3 (26-30) */

#define _IFIELD_STRM(x) ((0x00600000 & x) >> 21)    /* Data stream ID */

#define _IFIELD_CRFE(x) ((0x00000007 & x))          /* crfS for evsel */
#define _IFIELD_MO(x)   ((0x03e00000 & x) >> 21)    /* MO for mbar */
#define _IFIELD_EE(x)   ((0x00008000 & x) >> 15)    /* EE bit 16 for wrtee */
#define _IFIELD_CT(x)   ((0x01e00000 & x) >> 21)
#define _IFIELD_L_SYNC(x) ((0x00600000 & x) >> 21)  /* L field for sync */
#define _IFIELD_E_SYNC(x) ((0x000f0000 & x) >> 16)  /* E field for sync */
#define _IFIELD_WC_WAIT(x) ((0x00600000 & x) >> 21)  /* WC field for wait */
#define _IFIELD_WH_WAIT(x) ((0x00100000 & x) >> 20)  /* WH field for wait */
#define _IFIELD_EH(x) ((0x00000001 & x))          /* EH for ldarx */
#define _IFIELD_DQ(x) ((0x0000fff0 & x) >>  4)    /* DQ for lq */

#define INST_B         	_OP(18, 0)
#define INST_BC        	_OP(16, 0)
#define INST_BCCTR      _OP(19, 528)
#define INST_BCLR      	_OP(19, 16)
#define INST_BL         (_OP(18, 0) | 1)
#define INST_BCL        (_OP(16, 0) | 1)
#define	INST_SC		_OP(17, 1)
#define INST_B_MASK     0xfc000000
#define INST_BL_MASK    0xfc000001
#define INST_BCR_MASK	0xfc00fffe
#define INST_BCLRL	0x4c000021
#define INST_BCLRL_MASK	0xfc00ffff
#define	INST_SC_MASK	0xfc000002
/* to match either blrl or bctrl */
#define INST_BC_RL	0x4c000021
#define INST_BC_RL_MASK	0xfc00fbff

#define INST_MFLR       0x7c0802a6
#define INST_MFLR_R0    INST_MFLR
#define INST_MTLR       0x7c0803a6
#define INST_ADDI_SP    0x38210000
#define INST_STWU_SP    0x94210000
#define INST_STW_SP     0x90010000
#define INST_STW_R0_SP  INST_STW_SP
#define INST_LWZ_SP     0x80010000
#define INST_LWZU_SP    0x84010000

#define INST_MTSPR_MASK 0xfc1fffff
#define INST_HIGH_MASK  0xffff0000
#define INST_BCLR_MASK  0xfc00ffff
#define INST_STW_SP_MASK 0xfc1f0000
#define INST_STDU_SP     0xf8210000
#define INST_STD_SP      0xf8010000
#define INST_STD_R0_SP   INST_STW_SP
#define INST_LD_SP       0xe8010000
#define INST_LDU_SP      0xe8010000
#define INST_STD_SP_MASK 0xffff0000

#ifdef	HOST
/* function declarations */

extern DLL_EXPORT int dsmPpcInstGet
    (
    UINT32 *	 binInst,		/* Pointer to the instruction        */
    int		 endian,		/* endianness of data in buffer      */
    TGT32_ADDR_T address, 		/* Address prepended to instruction  */
    VOIDFUNCPTR	 prtAddress,		/* printing function address         */
    char *	 pString,		/* where to write disassembled inst. */
    BOOL32	 printAddr,		/* if address has to be appened      */
    BOOL32	 printOpcodes		/* if opcodes have to be appened     */
    );

extern DLL_EXPORT int dsmPpcInstSizeGet
    (
    UINT32 *	binInst,	/* pointer to the instruction                */
    int		endian		/* endianness of data in buffer              */
    );
#endif	/* HOST */

#ifndef	HOST
typedef struct	/* instruction descriptor */
    {
    char *	name;	/* mnemonic				      */
    UINT32	op;	/* fixed bits				      */
    UINT32	mask;	/* mask bits                                  */
    } INSTM;

extern int dsmFindByInst
    (
    void *binInst,      /* pointer to the instruction */
    INSTM *im		/* pointer to where result should go */
    );

extern int dsmFindByName
    (
    char *instName,     /* pointer to the instruction name */
    INSTM *im		/* pointer to where result should go */
    );
#endif	/* HOST */

#ifdef __cplusplus
}
#endif

#endif /* __INCdsmPpch */
