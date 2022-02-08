/* sh.h - SH-specific C-code for Context. */

/* Copyright (c) 1999-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
  DESCRIPTION
  This file contains SH-specific context code.
*/

#ifndef _CONTEXT_SH_H_
#define _CONTEXT_SH_H_


#define ST_TARGET_BIG_ENDIAN

/* 
 * Architecture specific header files 
 */


/*
 *  Types - define instruction and stack types here
 */
#define MIN_STACK_WIDTH (4)
#define MIN_INST_WIDTH  (2)
#define MAX_INST_LENGTH (4)
#define STACK_ALIGN     (4)
#define FRAME_ALIGN     (8)

#if !defined(__VXWORKS__)
#  include <stdint.h>
#endif


typedef uint32_t ST_TARGET_ADDR_T;
typedef int32_t  tOffset; /* Offset type */


/* number of instructions we parse before giving up */
#define RTITOOLS_MAX_FORWARD_SEARCH   (8192)

/* How many instructions to look backwards */
#define RTITOOLS_MAX_BACKWARD_SEARCH  (8192)

/* Max #instructions to check looking backward during debug epilogue check */
#define MAX_DBG_BACKWORD_SEARCH       (16)

/* Max #instructions to check looking backward during epilogue check */
#define MAX_RECONNOITER               (4)

/* Max #instructions to check looking backward during epilogue start check */
#define MAX_BKWD_EPILOGUE_SEARCH      (32)

/* Max #instructions to check looking forward during prolog end check */
#define MAX_FRWD_PROLOG_SEARCH        (16)

/* Max #instructions to check looking backward during prolog check */
#define MAX_BKWD_PROLOG_SEARCH        (32)

/* Max #instructions to check looking backward in close proximity to PC */
#define MAX_BKWD_PROXIMITY_SEARCH     (64)

/*
 *  Instruction values
 */
#define INST_UNKNOWN                (0x0000)
#define INST_STORE_PR               (0x4f22)  /* sts.l pr,@-sp */
#define INST_STORE_FP               (0x2fe6)  /* mov.l fp,@-sp */
#define INST_RESTORE_PR             (0x4f26)  /* lds.l @sp+,pr */
#define INST_RESTORE_FP             0x6ef6    /* mov.l @sp+,fp */
#define INST_SP_TO_FP               0x6ef3    /* mov   sp,fp   */
#define INST_FP_TO_SP               0x6fe3    /* mov   fp,sp   */
#define INST_ADD_TO_SP              0x7f00    /* add   #immed,sp */
#define INST_ADD_TO_FP              0x7e00    /* add   #immed,fp */
#define MASK_ADD_IMM                0xff00
#define MASK_IMM                    0x00ff
#define MOV_IMM                     0xe000
#define INST_ADD_TO_SP_HI           0x7f
#define INST_ADD_TO_FP_HI           0x7e
#define INST_ADD_REG_TO_FP_MASK     0x3e0c
#define MASK_REG_ARITHMETIC         0xff0f
#define MASK_SRC_REG                0x00f0    /* Rm in MOV/ADD/SUB Rm,Rn */
#define MASK_DEST_REG               0x0f00    /* Rn in MOV/ADD/SUB Rm,Rn */
#define INST_ADD_REG_TO_FP          0x3e0c    /* add   rx,fp   */
#define INST_ADD_REG_TO_SP          0x3f0c    /* add   rx,sp   */
#define INST_SUB_REG_FROM_SP        0x3f08    /* sub   rx,sp   */
#define INST_SP_AND                 0x2f09    /* and   rx,sp   */
#define INST_OFFSET_W_TO_REG_HI     0x9
#define INST_OFFSET_L_TO_REG_HI     0xd
#define MASK_BTBF_DISP              0x00ff    /* 8-bit displacement mask */
#define INST_BF_HI                  0x8b      /* bf   Branch if F,   no delay*/
#define INST_BF_2                   0x8b01    /* bf +2 */
#define INST_BFS_HI                 0x8f      /* bf/s Branch if F,   delay   */
#define INST_BT_HI                  0x89      /* bt   Branch if T,   no delay*/
#define INST_BT_2                   0x8901    /* bt +2 */
#define INST_BTS_HI                 0x8d      /* bt/s Branch if T,   delay   */
#define MASK_BRABSR_DISP            0x0fff    /* 12-bit displacement mask */
#define INST_BRA_HI                 0xa       /* bra  Branch always, delay   */
#define MASK_ADDRES_REG             0x0f00    /* mask for reg holding adrs */
#define INST_JMP_REG                0x402b    /* jmp @rx */
#define MASK_JMP_REG                0xf0ff
#define INST_JSR_REG                0x400b    /* jsr @rx */
#define MASK_JSR_REG                0xf0ff
#define INST_BRAF                   0x0023    /* Uncond. branch to reg */
#define MASK_BRAF                   0xf0ff
#define INST_BSRF                   (0x0003)  /* uncon. br to reg. offset */
#define MASK_BSRF                   (0xf0ff)
#define MASK_POPFLOAT               (0xf0ff)
#define INST_POPFLOAT               (0xf0f9)  /* fmov[.s] @sp+,drx[frx] */
#define MASK_PUSHFLOAT              (0xff0f)
#define INST_PUSHFLOAT              (0xff0b)  /* fmov[.s] drx[frx],@-sp */
#define INST_RTS                    (0x000b)
#define INST_MOVUA                  (0x4fe9)  /* movua.l @r15+,r0 SH4a only */
#define MASK_POPREG                 (0xf0ff)
#define INST_POPREG                 (0x60f6)  /* mov.l @sp+,rx */
#define MASK_PUSHREG                (0xff0f)
#define INST_PUSHREG                (0x2f06)  /* mov.l rx,@-sp */

#define INST_MOV_R0_TO_R0           (0x6002)
#define INST_LOAD_R0_TO_GBR         (0x401e)
#define INST_TRAPA                  (0xc3)
#define INST_NOP                    (0x0009)
#define MASK_OP_CODE                (0xf000)
#define INST_MOV_TO_RX_OFF_PC       (0xd000)    /* mov.l @(#imm,pc),rx */
#define INST_MOVW_TO_RX_OFF_PC      (0x9000)    /* mov.w @(#imm,pc),rx */
#define MASK_MOV_PC_OFFSET          (0x00ff)
#define MASK_PC_OFFSET_SIGN         (0x0080)

#define MASK_FMOV_FROM_STK          (0xf0ff)
#define INST_FMOV_FROM_STK          (0xf0f9)
#define INST_LDS_FPUL               (0x4f56)    /* lds.l @r15+,fpul  */
#define INST_LDS_FPSCR              (0x4f66)    /* lds.l @r15+,fpcsr */
#define INST_STS_FPUL               (0x4f52)    /* sts.l fpul,@-r15  */
#define INST_STS_FPSCR              (0x4f62)    /* sts.l fpscr,@-r15 */
#define MASK_FMOV_TO_STK            (0xff0f)
#define INST_FMOV_TO_STK            (0xff0b)

/*
 *  Context flags - define arch specific context package flags here
 */

/*
 * CHECK_TOP_FIRST if you want to call RTI_ContextTopDiscover at the 
 * beginning of ST_CallingContextGet; CHECK_TOP_LAST if you want to call it at
 * the end.  You can use both, don't unless you have to.
 */
#define RTITOOLS_CONTEXT_CHECK_TOP_FIRST        (1)
#define RTITOOLS_CONTEXT_CHECK_TOP_LAST         (0)

#define RTITOOLS_CONTEXT_USES_SP        (1)      /* context package uses sp? */

#define RTITOOLS_CONTEXT_USES_FP        (1)      /* context package uses fp? */
 

typedef enum {
    REG_LR,
    NUM_GPREGS,
    REG_SP,
    REG_FP,
    REG_PC
} RegisterName;

#endif  /* ifndef _CONTEXT_SH_H_ */
