/* mcf.h - Motorola ColdFire-specific C-code for Context. */

/* Copyright (c) 1999-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
16jan15,wzc  ppc64 support.(US49903)
*/

/*
DESCRIPTION
This file contains Motorola ColdFire-specific context code.
*/

#ifndef _CONTEXT_CF_H_
#define _CONTEXT_CF_H_

#include <st_inttypes.h>

#define ST_TARGET_BIG_ENDIAN

/*
 * Architecture specific defines
 */

typedef uint32_t ST_TARGET_ADDR_T;

#define MIN_STACK_WIDTH (4)
#define MIN_INST_WIDTH  (2)
#define STACK_ALIGN     (4)
#define FRAME_ALIGN     (4)


typedef uint32_t tAddr;   /* Address type */
typedef int32_t  tOffset; /* Offset type */
#define PRIa  "0x%"PRIx32


/*
 * Maxima
 */
#define RTITOOLS_MAX_FORWARD_SEARCH 2000
#define MAX_ABS_BRANCHES            20
#define MAX_BRANCH_INST_TO_RTS      10
#define MAX_INST_TO_LINK            11

/*
 *  Defined instructions and masks
 */
#define D0_REG   0
#define D1_REG   1
#define D2_REG   2
#define D3_REG   3
#define D4_REG   4
#define D5_REG   5
#define D6_REG   6
#define D7_REG   7
#define A0_REG   8
#define A1_REG   9
#define A2_REG  10
#define A3_REG  11
#define A4_REG  12
#define A5_REG  13
#define A6_REG  14
#define A7_REG  15

#define A6_REG_MASK     (1<<A6_REG) /* mask for a6 in multiple register list*/
#define PUSH_MULTIPLE       (0x48d7) /* movem.l dx/dy.../ax/ay,(a7) */
#define POP_MULTIPLE        (0x4cd7) /* movem.l (a7),dx/dy.../ax/ay */

#define PUSH_TO_STACK_INST  (0x0f00) /* move.x yyy,-(a7) */
#define PUSH_TO_STACK_MASK  (0xcfc0)
#define PUSH_TO_STACK_A6    (0x2f0e) /* move.l a6,-(a7) */
#define POP_FROM_STACK_INST (0x201f) /* move.l (a7)+,yyy */
#define POP_FROM_STACK_MASK (0xf03f)
#define POP_FROM_STACK_A6   (0x2c5f) /* movea.l (a7)+,a6 */
#define BRA_INST            (0x6000)
#define BRA_MASK            (0xff00)
#define BCC_INST            (0x6000) /* Must check for BCC_COND != 0, 1 */
#define BCC_MASK            (0xf000)
#define BCC_COND_MASK       (0x0f00)
#define SIZEOF_BCC_W        4
#define SIZEOF_BCC_B        2
#define ADDQ_STACK_INST     (0x508f) /* addq.l #immed,a7 */
#define ADDQ_STACK_MASK     (0xf1ff)
#define ADDA_SP_INST        (0xdffc) /* adda.l #imm,a7 */
#define SUBA_SP_INST        (0x9ffc) /* suba.l #imm,a7 */
#define LEA_SP_INST         (0x4fef) /* lea (disp,a7),a7 */
#define PEA_SP_INST         (0x4840) /* pea xxx */
#define PEA_MODE_MASK       (0x003f)
#define PEA_SP_MASK         (0xffc0)
#define CLR_SP_INST         (0x42a7) /* clr.l -(a7) */
#define PUSH_FP_INST        (0x4e56) /* link.w a6.#-immed */
#define POP_FP_INST         (0x4e5e) /* unlk a6 */
#define RTS_INST            (0x4e75) /* rts */
#define RTE_INST            (0x4e73) /* rte */
#define NOP_INST            (0x4e71) /* nop */
#define MOVW_IX_D0_INST     (0x303b) /* move.w (disp8,pc,d0.l*scale),d0 */
#define EXTL_D0_INST        (0x48c0) /* ext.l d0                        */
#define JMP_IX_D0_INST      (0x4efb) /* jmp (disp8,pc,d0.l)             */

#define OP_CODE_MASK        (0xf000) /* primary op code is first 4 bits */
#define OP_MODE_MASK        (0x01c0)
#define MOVE_DEST_MODE_MASK (0x01c0)
#define MOVE_DEST_REG_MASK  (0x0e00)
#define MOVE_SIZE_MASK      (0x3000)
#define MEM_EFF_ADRS_MASK   (0x003f) /* memory effective address mask */
#define MEM_IMMEDIATE       (0x003c) /* mode = 111b, reg = 100b */
#define MEM_MODE_MASK       (0x0038) /* memory effective address mode mask */
#define MEM_REG_MASK        (0x0007) /* memory effective address reg mask */
#define MOVE_LW_TO_STK_MASK (0xffc0)
#define MOVE_LW_TO_STK_INST (0x2f00) /* MOVE.L xx,-(A7) */

/* MCF5400-only instructions */
#define MOV3Q_SP_MASK       (0xf1ff)
#define MOV3Q_SP_INST       (0xa167) /* mov3q #immed,-(a7) */
#define SP_FLT_PT_SIZE      4
#define DP_FLT_PT_SIZE      8
#define FLT_PT_MASK         (0xffc0) /* mask for generic flt point insts */
#define FLT_PT_INST         (0xf200) /* 1st word generic floating point inst */
#define FBCC_LONG_MASK      (0x00c0)
#define FBCC_LONG_INST      (0x00c0) /* FBcc .+d32 */
#define FPOP_D16_MASK       (0xfff8)
#define FPOP_D16_INST       (0xf228) /* 1st word: Flt Pt op, (d16,Ax) mode */
#define FMOVE_TO_STK_INST   (0xf227) /* 1st word: FMOVE Fx,-(A7) */
#define FMOVE_FROM_STK_INST (0xf21f) /* 1st word: FMOVE (A7)+,Fx */
#define FLT_PT_OP_CODE_MASK (0x007f) /* 2nd word op code mask */
#define FMOVE_FPCR_PREC     (0x0000) /* FPCR sets FMOVE.X precision */
#define FMOVE_S             (0x0040) /* FMOVE.S single precision */
#define FMOVE_D             (0x0044) /* FMOVE.D double precision */
#define FMOVE_DIR_MASK      (0x4000) /* 0: mem->reg, 1: reg->mem */
#define FMOVE_STK_TO_REG    (0x001f) /* fmove (A7)+,fx */
#define FMOVE_REG_TO_STK    (0x0027) /* fmove fx,-(A7) */
#define FMOVE_DATA_FRMT_MASK (0x1c00) /* fmove data format */
#define FMOVE_FRMT_LONGWORD (0x0000) /* 000b: 32-bit longword format */
#define FMOVE_FRMT_S        (0x0001) /* 001b: 32-bit single precision format */
#define FMOVE_FRMT_WORD     (0x0004) /* 100b: 16-bit word format */
#define FMOVE_FRMT_D        (0x0005) /* 101b: 64-bit double precision format */
#define FMOVE_FRMT_BYTE     (0x0006) /* 110b: 8-bit byte format */
#define FMOVE_REG_MASK      (0x0380) /* mask for Fx in fmove inst */

/*
 * Macros
 */
#define OFF16_TO_INT(offset) \
  (((offset) & 0x8000) ? ((offset) | 0xffff0000) : (offset))

#define OFF8_TO_INT(offset)   \
  (((offset) & 0x80) ? ((offset) | 0xffffff00) : (offset))

/*
 *  Context flags - define arch specific context package flags here
 */

/* CHECK_TOP_FIRST if you want to call RtiTools_ContextTopDiscover at the
 * beginning of ST_CallingContextGet; CHECK_TOP_LAST if you want to call it at
 * the end.  You can use both, don't unless you have to.
 */
#define RTITOOLS_CONTEXT_CHECK_TOP_FIRST        (1)
#define RTITOOLS_CONTEXT_CHECK_TOP_LAST         (0)

#define RTITOOLS_CONTEXT_USES_SP        (1)   /* Does context package use sp? */
#define RTITOOLS_CONTEXT_USES_FP        (1)   /* Does context package use fp? */


typedef enum {
    REG_LR,
    NUM_GPREGS,
    REG_SP,
    REG_FP,
    REG_PC
} RegisterName;

#endif /* _CONTEXT_CF_H_ */
