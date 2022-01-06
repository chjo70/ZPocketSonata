/* arm.h - ARM-specific Context information. */

/* Copyright (c) 1999-2012, 2014-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */
/*
modification history
--------------------
13nov17,zli  Use _WRS_ASM instead of asm for inline assembler.(V7COR-5398)
14jul17,zli  support movw instruction before restore SP.(V7COR-5195)
28dec16,zli  add arm64 stacktrace support.(US90845)
21dec16,zli  fix arm64 compile warnings
12dec16,zli  arm64 support (US90845)
16jan15,wzc  ppc64 support.(US49903)
26jan15,wzc  fix static analysis warnings.(V7COR-2460)
19jun14,wzc  add INST_LOAD_FP.(WB4-3710)
06mar14,wzc  redefine the ST_current_regs.(WB4-2945)
*/
/*
  DESCRIPTION
  This file contains ARM-specific context code.
*/

#ifndef _CONTEXT_TARGET_H_
#define _CONTEXT_TARGET_H_

/* for REG_SET definition */
#if defined(__VXWORKS__)
#  include <regs.h>
#  include <vxWorks.h>
#else
#  include "arm_regs.h"
#endif
#include <st_inttypes.h>
#include "st_endian.h"  /* for _BYTE_ORDER-related definitions */

#ifndef _WRS_ASM
#define _WRS_ASM __asm__
#endif

#if defined(ARM_THUMB2) && ARM_THUMB2
#  define ST_SUPPORTS_ARM_THUMB2
#endif


/*
 * Architecture specific header files
 */
#define MIN_STACK_WIDTH (4)
#if defined(ST_SUPPORTS_ARM_THUMB2)
#  define MIN_INST_WIDTH  (2)
#else
#  define MIN_INST_WIDTH  (4)
#endif  /* if defined(ST_SUPPORTS_ARM_THUMB2) */

#ifdef _WRS_CONFIG_LP64
#define STACK_ALIGN     (16)
#define FRAME_ALIGN     (16)
#else
#define STACK_ALIGN     (4)
#define FRAME_ALIGN     (4)
#endif

#define INITIAL_STK_FRAME_SIZE  (MAX_TASK_ARGS * sizeof(int))

#ifdef _WRS_CONFIG_LP64
typedef uint64_t ST_TARGET_ADDR_T;
#define PRIa  "0x%"PRIx64
#else
typedef uint32_t ST_TARGET_ADDR_T;
#define PRIa  "0x%"PRIx32
#endif

#if defined(__VXWORKS__) && defined(_WRS_CONFIG_LP64) && (CPU_FAMILY == ARM)
/* for arm64, just use frame walk rather than frame crawl */
#define ST_USE_FRAME_WALK 1
#endif


/*
 *  Maxima
 */
#define MAX_FORWARD_SEARCH      2048
#define MAX_BACKWARD_SEARCH     2048
#define MAX_BKWD_PROLOG_SEARCH  16
#define MAX_BKWD_LDR_SEARCH     5

#define MAX_SEARCH_FOR_LDMIA    5

#define MAX_BACK_BRANCHES 16
#define MAX_EPILOGUE_LENGTH 16

/**
 *  Condition code definitions
 */
#define INST_MASK        (0x0fffffff) /* mask out the condition code */
#define COND_MASK        (0xf0000000) /* mask out all bits except the condition code */
#define COND_NEVER       (0xf0000000) /* never execute this instruction */
#define COND_ALWAYS      (0xe0000000) /* always execute this instruction */

/*
 *  Instruction values - define any instruction op-codes here
 */
#define INST_RTS          0xe1a0f00e    /** return to caller, mov pc,r14 **/
#define INST_COND_RTS    (0x01a0f00e)   /* return to caller, mov[cnd] pc,r14
                                           after masking out possible cond */

#define INST_INF_LOOP     0xeafffffe    /** branch to the current pc **/

#define INST_STORE_LR     0xe52de004    /** store lr on stack, str r14,[r13,#-4]! **/
#define INST_LOAD_LR      0xe49de004    /** load lr from stack, ldr r14,[r13],#4 **/

#define INST_STORE_FP     0xe52db004    /** store fp on stack, str r11,[r13,#-4]! **/
#define INST_LOAD_FP      0xe49db004    /** load fp from stack, ldr r11,[r13],#4 **/

#define INST_LOAD_PC      0xe49df004    /** load pc from stack, ldr pc,[r13],#4 **/
#define INST_LOAD_PC_IDX  0xe51df000    /* ldr pc,[r13,#-0] */

#define MASK_LOAD_PC_IP  (0xffff0000)  /* tests for ldr pc,[ip, #imm]! */
#define INST_LOAD_PC_IP  (0xe5bc0000)  /* this instruction loads the pc from an
                                          offset from the ip (intra-procedure
                                          call) register.  This is typically
                                          used in linux .plt entries. */

#define ANY_STMDB_MASK       0xffff0000
#define INST_ANY_STMDB       0xe92d0000  /* stmdb 13!,{any regs} */

#define RESERVE_MULTIPLE_STACK_MASK     0xffffc000
#define RESERVE_ANY_MULTI_STACK_MASK    0xffff0000
#define INST_RESERVE_MULTIPLE_STACK     0xe92d0000  /* stmdb 13!,{regs,!pc,!lr}*/

#define FRAME_CREATION_MASK 0xffff4000
#define INST_PUSH_FRAME 0xe92d4000      /** Checks for stmdb 13!,{regs,LR} **/

#define FRAME_FP_CREATE_MASK 0xffffc800
#define INST_PUSH_FP_FRAME   0xe92dc800 /** stmdb 13!,{regs,fp,LR,PC} **/

#define LOAD_LR_FROM_STACK_MASK 0xffffc000
#define INST_LOAD_LR_FROM_STACK 0xe8bd4000  /* ldmib r13!,{regs,lr,!sp,!pc} */

#define INST_MOVE_FP_TO_SP  0xe1a0d00b  /* mov  r13,r11    fp -> sp */
#define INST_MOVE_SP_TO_FP  0xe1a0b00d  /* mov  r11,r13    sp -> fp */
#define INST_MOVE_SP_TO_R12 0xe1a0c00d  /* mov  r12,r13    sp -> r12 */
#define MASK_MOV_SP_TO_RX   0xffff0fff  /* mask for mov  rx,r13  sp -> rx */
#define INST_MOVE_SP_TO_RX  0xe1a0000d  /* mov  r1x,r13    sp -> rx */
#define MASK_MOVE_IMM_TO_RX 0xfffff000  /* mask for mov rx,#imm */
#define MASK_MOVEW_IMM_TO_RX 0xfff0f000 /* mask for movw rx,#imm */
#define INST_MOV_IMM        0xe3a00000  /* mov rx,#imm */
#define INST_MOVW_IMM       0xe3000000  /* movw rx,#imm */
#define MASK_DEST_REG       0x0000f000  /* mask for destination register# */
#define MASK_SHIFTER_OP     0x00000fff  /* immediate shifter operand mask */

#define MASK_LDR_STR        0xffff0000  /* masks for ldr and str op codes */
#define INST_LDR_FP_REL     0xe59b0000  /* ldr rx,[r11,#imm] */
#define INST_STR_FP_REL     0xe58b0000  /* str rx,[r11,#imm] */
#define INST_STR_RX_SP_UP   0xe52d0000  /* str rx,[r13,#-imm]! */
#define INST_STR_LR_SP_UP   0xe52de000  /* str r14,[r13,#-imm]! */
#define INST_LDR_PC_REL     0xe59f0000  /* ldr rx,[pc,#offset] */
#define MASK_LDRSTR_IDX_OFST    0x00000fff  /* #imm in ldr/str rx,[ry,#imm] */
#define MASK_LDRSTR_RD_RN_REL   0xfffff000  /* mask: ldr/str rd,[rn,#imm] */
#define MASK_TRIREG_RN      0x000f0000  /* get rn from  <op> rd,rn,rm */
#define MASK_TRIREG_RD      0x0000f000  /* get rd from  <op> rd,rn,rm */
#define MASK_TRIREG_RM      0x0000000f  /* get rm from  <op> rd,rn,rm */
#define BSHFT_L_RM_TO_RD    12          /* #bits to shift rm left to rd pos */
#define MASK_LDRSTR_12B_OFFSET  0x00000fff  /* mask: 12-bit offset in ldr/str*/
#define MASK_OP_CODE_U_BIT  0x00800000  /* mask: U bit; u=1 => pos offset */
#define MASK_ARITH_8B_IMM   0x000000ff  /* mask: 8-bit arith immediate val */

#define LOAD_LR_FROM_FRAME_COND_MASK 0xffffc000
#define INST_LOAD_LR_FROM_FRAME_COND_EQ 0x091b4000  /* ldmeqib r11!,{regs,LR}*/

#define LOAD_LR_MULTIPLE_MASK    (0xffffe000)
#define INST_LR_SP_FROM_FRAME    (0xe91b6000)  /* ldmdb r11,{regs,sp,lr, !pc}*/
#define INST_LR_SP_MULTIPLE_LOAD (0xe89d6000)  /* ldmia sp,{regs,sp,lr, !pc} */

#define LDST_MULT_FLOAT_MASK    0xffbf0f00
#define FLOAT_REG_CNT_MASK      0x000000ff  /* #fpr's loaded or stored */
#define INST_FLDMIAS            0xecbd0a00  /* fldmias r13!,{fpr's} sngl prec*/
#define INST_FLDMIAD            0xecbd0b00  /* fldmiad r13!,{fpr's} dbl prec */
#define INST_FSTMDBS            0xed2d0a00  /* fstmdbs r13!,{fpr's} sngl prec*/
#define INST_FSTMDBD            0xed2d0b00  /* fstmdbd r13!,{fpr's} dbl prec */

/* Intel's MMX (MultiMedia eXtensions) for Xscale use some op codes that
 * are also recognized by ARM as floating point instructions.  Of the
 * many instructions, only a few are of interest and only those forms
 * of them which alter the stack pointer:
 *
 *  XScale MMX Instructions         Interpretations of MMX Op Codes
 *                                  ARM4                        ARM5
 *  -------------------------   -------------------------------------------
 *  wldrw   wRx,[r13,#immed]!   ldfs   fx,[r13,#immed]!     "
 *  wldrw   wCx,[r13,#immed]!   ldfnvs fx,[r13,#immed]!     "
 *  wldrd   wRx,[r13,#immed]!   ldfe   fx,[r13,#immed]!   ldfd fx,[r13,#immed]!
 *
 *  wstrw   wRx,[r13,#immed]!   stfs    fx,[r13,#immed]!    "
 *  wstrw   wCx,[r13,#immed]!   stfnvs  fx,[r13,#immed]!    "
 *  wstrd   wRx,[r13,#immed]!   stfe    fx,[r13,#immed]!  stfd fx,[r13,#immed]!
 */
#define MASK_MMX            0xff7f0f00  /* for checking wldr/wstr forms */
#define INST_WLDRW_WREG     0xed3d0100  /* wldrw  wRx,[r13,#immed]! */
#define INST_WLDRW_CREG     0xfd3d0100  /* wldrw  wCx,[r13,#immed]! */
#define INST_WLDRD          0xed7d0100  /* wldrd  wRx,[r13,#immed]! */
#define INST_WSTRW_WREG     0xed2d0100  /* wstrw  wRx,[r13,#immed]! */
#define INST_WSTRW_CREG     0xfd2d0100  /* wstrw  wCx,[r13,#immed]! */
#define INST_WSTRD          0xed6d0100  /* wstrd  wRx,[r13,#immed]! */

#define RTS_VIA_LDM_MASK 0xffff8000
#define INST_LDMIA_RTS     0xe8bd8000     /** rts via ldmia 13!,{regs,PC} **/
#define INST_LDMDB_RTS     0xe91b8000     /** rts via ldmdb 11,{regs,PC} **/

#define RECLAIM_STACK_MASK  0xfffff000
#define INST_RECLAIM_STACK  0xe28dd000  /** add r13,r13,#imm **/
#define INST_RCLM_BIG_STACK 0xe08dd000  /** add r13,r13,rx   **/
#define INST_RCLM_FP_STACK  0xe08bd000  /** add r13,r11,rx   **/
#define INST_RECLAIM_FP     0xe28db000  /** add r11,r13,#imm **/

#define ANY_LDMIA_MASK      0xffff0000
#define INST_ANY_LDMIA      0xe8bd0000  /* ldmia 13!,{any regs} */
#define MASK_REG_MAP        0x0000ffff  /* ldm/stm register map mask */

#define RECLAIM_MULTIPLE_STACK_MASK   0xffffc000
#define INST_RECLAIM_MULTIPLE_STACK   0xe8bd0000  /* ldmia 13!,{regs,!lr,!pc}*/
#define INST_RESTORE_LR_MULTIPLE      0xe8bd4000  /* ldmia 13!,{regs,lr,!pc} */

#define RECLAIM_FP_MULTI_STACK_MASK   0xffffe800
#define INST_RECLAIM_FP_MULTI_STACK   0xe89da800  /* ldmia 13,{regs,fp,sp,!lr,pc}*/
#define RET_STACK_MASK                0xffffa800
#define INST_RET_STACK                0xe89da800  /* ldmia r13,{regs,r11,r13,pc}*/

#define LDMIA_SP_RTS_MASK  0xffffe000
#define INST_LDMIA_SP_RTS  0xe89da000  /* ldmia 13,{regs,sp,!lr,pc} */
#define INST_LDMIA_SP_LR   0xe89d6000  /* ldmia 13,{regs,sp,lr,!pc} */

#define RESERVE_STACK_MASK   0xfffff000
#define INST_RESERVE_STACK   0xe24dd000     /** sub r13,r13,#imm **/
#define INST_RSRV_BIG_STACK  0xe04dd000     /** sub r13,r13,rx **/
#define INST_FP_SUB_SET_SP   0xe24bd000     /** sub r13,r11,#imm **/
#define MASK_SET_FP          0xfff0f000     /** mask for sub r11,rx,imm */
#define INST_SET_FP_SUB      0xe240b000     /** sub r11,rx,#imm */
#define INST_SET_FP_ADD      0xe280b000     /** add r11,rx,#imm */
#define MASK_12B_IMMEDIATE   0x00000fff     /** mask for #imm */

#define BRANCH_MASK         0xff000000
#define BRANCH_OFFSET_MASK  0x00ffffff
#define INST_BRANCH         0xea000000  /** unconditional B inst **/
#define INST_BRANCH_LINK    0xeb000000  /** branch and link BL inst **/
#define ANY_BRANCH_MASK     0x0f000000
#define INST_COND_BRANCH    0x0a000000  /** any conditional B inst **/

#define BX_LR_MASK          0xfff000ff
#define INST_BX_LR          0xe120001e  /* bx lr  [bx r14] */
#define BRANCH_EXCHANGE_MASK    (0xfff000f0)
#define INST_BRANCH_EXCHANGE    (0xe1200010)  /* matches a branch and exchange
                                                 instruction, bx */

#define COND_BRANCH_MASK 0xfe000000     /** conditional branch */
#define INST_COND_BRANCH_EQ 0x0a000000     /** beq: branch if equal */

#define INST_RTN_FROM_EXC_HANDLER 0xe9d2800f  /** occurs upon returning from an
                                                  exception handler.
                                                  ldmib r2,{r0-r3,pc}^ **/

#define MASK_REGISTER_SET (0x0000ffff)
#define MASK_REGISTER_R11 (0x00000800)  /** frame pointer **/
#define MASK_REGISTER_R13 (0x00002000)  /** stack pointer **/
#define MASK_REGISTER_R14 (0x00004000)  /** link register **/


#if defined(ST_SUPPORTS_ARM_THUMB2)

#define CPSR_T_BIT        (0x00000020)
#define LR_0_BIT          (0x00000001)


/**
 *  Test to see whether the "T"humb bit is set.
 */
static inline
bool st_is_thumb2(uint32_t cpsr)
{
    return (cpsr & CPSR_T_BIT);
}


/* add or sub sp immediately */
#define MASK_ADD_SUB_SP            (0xff80)
#define INSTR_ADD_SP               (0xb000)
#define INSTR_SUB_SP               (0xb080)
#define MASK_ADD_SUB_SP_IMM        (0x007f)

/* add or sub sp immediately */
#define MASK_ADDW_SUB_SP           (0xfbef8f00)
#define INSTR_ADDW_SP              (0xf10d0d00)
#define INSTR_SUBW_SP              (0xf1ad0d00)

/* pop */
#define MASK_POP                   (0xfe00)
#define INSTR_POP                  (0xbc00)
#define POP_PC_BIT                 (0x0100)

/* push */
#define MASK_PUSH                  (0xfe00)
#define INSTR_PUSH                 (0xb400)
#define PUSH_PC_BIT                (0x0100)

/* push lr */
#define INSTR_PUSH_LR              (0xb500)

/* mov pc, lr */
#define INSTR_MOV_LR_TO_PC         (0x46f7)

/* bx, lr */
#define INSTR_BX_LR                (0x4770)

/* unconditional B */
#define MASK_UNCOND_B              (0xf800)
#define INSTR_UNCOND_B             (0xe000)
#define MASK_UNCOND_B_IMM          (0x07ff)

/* add.w  sp, sp, ip */
#define INSTR_ADDW_SP_SP_IP        (0xeb0d0d0c)

/* ldr.w {} or pop<c>.w <register> */
#define MASK_LDRW_SP_WBACK         (0xffff0fff)
#define INSTR_LDRW_SP_WBACK        (0xf85d0b04)
#define MASK_LDRW_SP_WBACK_REG     (0x0000f000)
#define LDRW_SP_WBACK_PC_REG       (0x0000f000)
#define LDRW_SP_WBACK_LR_REG       (0x0000e000)

/*ldr<c>.w <rt>,[<rn>,<rm>{,lsl #<imm2>}] */
#define MASK_LDRW_PC               (0xfff0f000)
#define INSTR_LDRW_PC              (0xf850f000)

/* ldmia.w  sp!, {} or pop */
#define MASK_LDMIA_SP_WBACK        (0xffff0000)
#define INSTR_LDMIA_SP_WBACK       (0xe8bd0000)
#define LDMIA_SP_WBACK_PC_BIT      (0x00008000)
#define LDMIA_SP_WBACK_LR_BIT      (0x00004000)

/* fldmias  sp!, {s31} */
#define MASK_FLDMIAS_SP_WBACK      (0xffbf0f00)
#define INSTR_FLDMIAS_SP_WBACK     (0xecbd0a00)
#define FLDMIAS_SP_WBACK_IMM       (0x000000ff)


/* mov  pc, lr */
#define INSTR_MOVW_LR_TO_PC        (0xe1a0f00e)

/* mov.w  ip, #imm  */
#define MASK_MOV_IP_IMM            (0xfbff8f00)
#define INSTR_MOV_IP_IMM           (0xf04f0c00)

/* movw  ip, #imm  */
#define MASK_MOVW_IP_IMM           (0xfbf08f00)
#define INSTR_MOVW_IP_IMM          (0xf2400c00)

/* stmdb.w  sp!, {} or push */
#define MASK_STMDB_SP_WBACK        (0xffff0000)
#define INSTR_STMDB_SP_WBACK       (0xe92d0000)
#define STMDB_SP_WBACK_LR_BIT      (0x00004000)

/*str.w  reg, [sp,#imm]!  */
#define MASK_STRW_SP_WBACK         (0xffff0fff)
#define INSTR_STRW_SP_WBACK        (0xf84d0d04)
#define MASK_STRW_SP_REG           (0x0000f000)
#define STRW_SP_LR_REG             (0x0000e000)

/* unconditional B.w*/
#define MASK_UNCOND_BW             (0xf800d000)
#define INSTR_UNCOND_BW            (0xf0009000)

/* conditional b*/
#define MASK_COND_B                (0xf000)
#define INSTR_COND_B               (0xd000)

/* conditional b.w*/
#define MASK_COND_BW               (0xf800d000)
#define INSTR_COND_BW              (0xf0008000)
#endif  /* if defined(ST_SUPPORTS_ARM_THUMB2) */


/*
 *  Context flags - define arch specific context package flags here
 */
/* CHECK_TOP_FIRST if you want to call RtiTools_ContextTopDiscover at the
 * beginning of ST_CallingContextGet; CHECK_TOP_LAST if you want to call it at
 * the end.  You can use both, don't unless you have to.
 */
#if defined(__linux__)
#  define RTITOOLS_CONTEXT_CHECK_TOP_FIRST        (0)
#  define RTITOOLS_CONTEXT_CHECK_TOP_LAST         (1)
#else
#  define RTITOOLS_CONTEXT_CHECK_TOP_FIRST        (1)
#  define RTITOOLS_CONTEXT_CHECK_TOP_LAST         (0)
#endif

#define RTITOOLS_CONTEXT_USES_SP        (1)   /* Does context package use sp? */
#define RTITOOLS_CONTEXT_USES_FP        (1)   /* Does context package use fp? */


typedef enum {
    REG_LR,
    NUM_GPREGS,
    REG_SP,
#if RTITOOLS_CONTEXT_USES_FP
    REG_FP,
#endif
    REG_PC
} RegisterName;


#if !defined(CRAWL_IS_HOST_NATIVE)
#  if defined(__DCC__)
asm unsigned long get_sp(void)
{
!
    mov  r0, sp
$$noadjust
}


asm unsigned long get_fp(void)
{
!
    mov  r0, fp
}


asm unsigned long get_ra(void)
{
!
    mov  r0, lr
}


asm void *get_pc(void)
{
!
    mov  r0, pc
}


/**
 *  Populate the given REG_SET with values from "now" in the current thread of
 * execution.
 */
#define ST_current_regs(regs)                   \
    do {                                        \
        (regs)->reg_sp = get_sp();              \
        (regs)->reg_fp = get_fp();              \
        (regs)->reg_lr = get_ra();              \
        (regs)->pc = get_pc();                  \
    } while(0);


#  elif defined(__GNUC__)

static inline
void ST_current_regs(REG_SET * regs) __attribute__((always_inline));

/**
 *  Populate the given REG_SET with values from "now" in the current thread of
 * execution.
 */
static inline
void ST_current_regs(REG_SET * regs)
{
#ifndef     _WRS_CONFIG_LP64
    register long sp _WRS_ASM("sp");
    register long fp _WRS_ASM("fp");
    register long lr _WRS_ASM("lr");
    register long pc _WRS_ASM("pc");
#else
    long sp = 0;
    long fp = 0;
    long lr = 0;

    __asm__ volatile ("mov %0, sp\n\t"
            "mov %1, fp\n\t"
            "mov %2, lr\n\t"
            : "=r" (sp), "=r" (fp), "=r" (lr)
            : /* no inputs*/);
    
#endif

    regs->reg_lr = lr;
    regs->reg_sp = sp;
    regs->reg_fp = fp;
#ifndef     _WRS_CONFIG_LP64
    regs->pc = (void *) pc;
#else
    _get_pc_label:
    regs->pc = && _get_pc_label;
#endif
}
#  endif  /* if __DCC__ || __GCC__ */
#endif  /* if !defined(CRAWL_IS_HOST_NATIVE) */

#endif  /* _CONTEXT_TARGET_H_ */
