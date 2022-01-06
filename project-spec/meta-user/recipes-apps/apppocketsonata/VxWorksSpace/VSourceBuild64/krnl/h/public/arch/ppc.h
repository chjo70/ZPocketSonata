/* ppc.h - ppc-specific values for stacktrace. */

/* Copyright (c) 1999-2012, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */
/*
modification history
--------------------
16jul15,wzc  ignore unexpected stw instr. 
05feb15,wzc  add stdu process.
16jan15,wzc  ppc64 support.(US49903)
18dec14,gxu  fix ppc64 asm build error.(V7CORE-2362)
16dec14,wzc  fix ST_trace_error.(V7COR-2351)
14aug14,wzc  fix stack trace error.(WB4-3745)
10jun14,wzc  fix the building failure of tcf-tools.(WB4-3703)
13may14,wzc  support frame pointer.(US34220)
06mar14,wzc  redefine the ST_current_regs.(WB4-2945)
*/
/*
  DESCRIPTION
  This file contains ppc-specific context code.
*/

#ifndef _CONTEXT_PPC_H_
#define _CONTEXT_PPC_H_

#include <st_inttypes.h>
#include <arch/ppc_regs.h>  /* for ppc_reg_t */
#if defined(__VXWORKS__)
#  include <regs.h>  /* for REG_SET definition */
#endif


#define ST_TARGET_BIG_ENDIAN

/*
 *  Types - define instruction and stack types here
 */
#if defined(PPC_CRAWL_ADDRESS_SIZE)
#  if (PPC_CRAWL_ADDRESS_SIZE == 4)
#    define PRIa  "0x%"PRIx32
typedef uint32_t ST_TARGET_ADDR_T;
#  elif (PPC_CRAWL_ADDRESS_SIZE == 8)
#    define PRIa  "0x%"PRIx64
typedef uint64_t ST_TARGET_ADDR_T;
#  endif
#elif defined(__SIZEOF_POINTER__)
#  if (__SIZEOF_POINTER__ == 4)
#    define PRIa  "0x%"PRIx32
typedef uint32_t ST_TARGET_ADDR_T;
#  elif (__SIZEOF_POINTER__ == 8)
#    define PRIa  "0x%"PRIx64
typedef uint64_t ST_TARGET_ADDR_T;
#  endif
#elif defined(__VXWORKS__)
#  ifdef _WRS_CONFIG_LP64
#    define PRIa  "0x%"PRIx64
typedef uint64_t ST_TARGET_ADDR_T;
#  else
#    define PRIa  "0x%"PRIx32
typedef uint32_t ST_TARGET_ADDR_T;
#  endif
#else
/* default to 32-bit logic */
#  define PRIa  "0x%"PRIx32
typedef uint32_t ST_TARGET_ADDR_T;
#endif

#define MIN_STACK_WIDTH (4)
#define MIN_INST_WIDTH  (4)
#define MAX_INST_LENGTH (4)
#define STACK_ALIGN     (4)
#define FRAME_ALIGN     (4)

/*
 *  Instruction values - define any instruction op-codes here
 */

#define MAX_BRANCHES 50  /* Too high and you get bad functions */

#define OP_CODE_MASK    (0xfc000000)  /* mask for PPC 6-bit op code */
#define OP_WORD_MASK    (0xffff0000)  /* Use to see op code w/no disp */
#define DISP_MASK       (0x0000ffff)  /* to derive d in d(rA) */
#define NEG_DISP_SIGN   (0x00008000)  /* tests for negative displacement */
#define DISP_NEG        (0xffff0000)  /* for sign-extending neg disp */

#define BNSLR_INSTR     (0x4ca30020)
#define SC_INSTR        (0x44000002)

#define BCTR_MASK       (0xfc00ffff)
#define BCTR_INSTR      (0x4e800420)

#define BL_MASK         (0xfc000001)
#define BL_INSTR        (0x48000001)

#define BLR_INSTR       (0x4e800020)
#define BEQLR_INSTR     (0x4c820020)

#define BRA_MASK        (0xfe800000)
#define BRA_INSTR       (0x42800000)

/* branch conditional instructions (bc) */
#define BR_MASK         (0xfc000001)
#define BR_INSTR        (0x40000000)
#define BR_OFFSET_MASK  (0x0000fffc)
#define BR_OFFSET_SIGN  NEG_DISP_SIGN
#define BR_OFFSET_NEG   DISP_NEG

/* vanilla Branch instructions (b); always branch to the given 
   target */
#define B_MASK          (0xfc000001)
#define B_INSTR         (0x48000000)
#define B_INSTR_ABSBIT  (0x00000002)
#define B_OFFSET_MASK   (0x03fffffc)  /* Use to derive 26-bit offset in BL */
#define B_OFFSET_SIGN   (0x02000000)  /* For sign-extending 26-bit offset */
#define B_OFFSET_NEG    (0xfc000000)

/* all jump instruction */
#define B_BL_MASK       (0xfc000000)
#define B_BL_INSTR      (0x48000000)
#define BR_BRL_MASK     (0xfc000000)
#define BR_BRL_INSTR    (0x40000000)

#define STWU_INSTR      (0x94210000) /* stwu r1, d(r1) */
#define STDU_INSTR      (0xf8210000) /* stdu r1, d(r1) */
#define STWU_MASK       (0xffff0000)
#define STWU_OFFSET_MASK DISP_MASK
#define STWU_OFFSET_SIGN (0x00008000)
#define STWU_OFFSET_NEG  (0xffff0000)

#define MTSPR_MASK      (0xfc1fffff) /* matches all mtspr LR,rx instructions,
                                        regardless of source register */
#define MTLR_INSTR      (0x7c0803a6) /* mtlr r0 */
#define MTSPR_INSTR     (0x7c0803a6) /* mtspr LR,r0 */

#define MFSPR_MASK      (0xfc1fffff) /* matches all mfspr rx,LR instructions,
                                        regardless of destination register */
#define MFSPR_INSTR     (0x7c0802a6) /* mfspr  r0,LR */
#define MFLR_INSTR      (0x7c0802a6) /* mflr   r0 */

#define STW_INSTR       (0x90010000) /* stw  r0, d(r1) */

#define SRC_REG_MASK    (0x03e00000)  /* to derive src register number */
#define STW_R0_MASK     (0xffff0000)  /* Use to see if STW is storing r0 */
#define STW_R1_MASK     (0xfc1f0000)  /* Use to see if STW Rx,d(Ry) */
#define STW_R0_OFFSET   (0x0000ffff)
#define STW_R0_R11_X    (0x900b0000)  /* stw  r0, x(r11) */
#define STW_R31_R11_X   (0x93eb0000)  /* stw  r31, x(r11) */
#define STW_R30_R11_X   (0x93cb0000)  /* stw  r30, x(r11) */
#define STW_R31_R1_X    (0x93e10000)  /* stw  r31, x(r1)  */
#define ADDI_INSTR      (0x38210000)  /* addi r1, r1, immed */
#define ADDI_R1_R11_X   (0x382b0000)  /* addi r1,r11, immed */
#define ADDI_R11_R1_X   (0x39610000)  /* addi r11, r1, immed */
#define ADDI_R11_R11_X  (0x396b0000)  /* addi r11, r11, immed */
#define ADDI_R11_R31_X  (0x397f0000)  /* addi r11,r31, immed */
#define ADDI_R1_R31_0   (0x383f0000)  /* addi r1,r31,0  [move FP to SP] */
#define ADDI_R1_R31_X   (0x383f0000)  /* addi r1,r31,immd */
#define ADDI_R31_R1_0   (0x3be10000)  /* addi r31,r1,0  [move SP to FP] */
#define ADDI_MASK       (0xffff0000)
#define ADDI_OFFSET_MASK (0x0000ffff)
#define ADDI_OFFSET_SIGN (0x00008000)
#define ADDIC_INSTR     (0x30210000)  /* addic, r1, r1, immed */
#define ADDIC_MASK      (0xffff0000)
#define LI_RX_MASK      (0xffe00000)  /* li rx,val || addi rx,ry,val  any x,y*/
#define LI_R0_INSTR     (0x38000000)  /* li r0,val || addi r0,ry,val */
#define LIS_R0_INSTR    (0x3c000000)  /* lis r0,val */
#define LI_R14_INSTR    (0x39c00000)  /* li r14,val || addi r14,ry,val */
#define LI_RX_NEGMASK   (0xfc1f8000)  /* li rx,val  any x, val < 0 */
#define LI_RX_NEGVAL    (0x38008000)  /* li rx,#-val  [addi rx,r0,#-val] */

#define ORI_MASK        (0xffff0000)  /* test for any ORI Rx,Ry,immed */
#define OR_R1_R11_R11   (0x7d615b78)  /* OR  R1,R11,R11  [mr r1,r11] */
#define MR_R31_R1       (0x7c3f0b78)  /* or  r31,r1,r1   [mr r31,r1] */
#define MR_R11_R1       (0x7c2b0b78)  /* mr  r11,r1  */
#define MR_R1_R31       (0x7fe1fb78)  /* mr r1,r31 */
#define ORI_R1_R11_0    (0x61610000)  /* ORI R1,R11,#0  */
#define MR_R1_MASK      (0xfc1f0000)  /* mask: or r1,rx,rx  [mr  r1, rx] */
#define MR_R1_INSTR     (0x7c010000)  /* mr   r1, rx */
#define MR_R0_INSTR     (0x7c000000)  /* mr   r0, rx */
#define MR_R1_R11_INSTR (0x7d615b78)  /* mr   r1, r11 */
#define MR_R1_ALT_MASK  (0xffe0ffff)  /* mask for addi r1, rx, #0 */
#define MR_R1_ALT_INSTR (0x38200000)  /* addi r1, rx, #0 */

#define CMP_OP_CODE     (0x7c000000)  /* cmp */
#define CMPI_OP_CODE    (0x2c000000)  /* cmpi */

#define LWZ_MASK         (0xfc000000)
#define LWZ_INSTR        (0x80000000)
#define LWZ_R0_RX_INSTR  (0x80000000)  /* lwz r0,d(rx) */
#define LWZ_R0_MASK      (0xffff0000)  /* mask: lwz rx,d(r1)  any x */
#define LWZ_R0_INSTR     (0x80010000)  /* lwz r0, d(r1) -- from frame */
#define LWZ_RX_RY_MASK   (0xffe00000)  /* mask: lwz rx,d(ry)  any x, y */
#define LWZ_R1_RX_INSTR  (0x80200000)  /* lwz r1, d(rx) -- from frame */
#define LWZ_R1_MASK      (0xfc1f0000)  /* restore rx from stack frame */
#define LWZ_R1_INSTR     (0x80010000)  /* lwz  rx,d(r1) */
#define LWZ_R11_R1_MASK  (0xffff0000)  /* lwz r11,0(r1) -- from frame */
#define LWZ_R11_R1_INSTR (0x81610000)  /* lwz r11,0(r1) -- from frame */
#define LWZ_R0_R11_MASK  (0xffff0000)  /* lwz r0,d(r11) mask */
#define LWZ_RX_R11_MASK  (0xfc1f0000)  /* lwz rx,d(r11) mask */
#define LWZ_R0_R11_INSTR (0x800b0000)  /* lwz r0,d(r11) or lwz rx,d(r11) */
#define LWZ_R31_R1_INSTR  0x83e10000   /* lwz r31,d(r1) */
#define LWZ_R31_R11_INSTR 0x83eb0000   /* lwz r31,d(r11) */
#define LWZ_R30_R11_INSTR 0x83cb0000   /* lwz r30,d(r11) */
#define LWZ_R0_R11_OFF_MASK  (0xffff8000) /* lwz r0,+-d(r11) mask */
#define LWZ_R0_R11_POS_INSTR (0x800b0000) /* lwz r0,+d(r11) or lwz rx,+d(r11)*/
#define LWZ_R0_R11_NEG_INSTR (0x800b8000) /* lwz r0,-d(r11) or lwz rx,-d(r11)*/
#define LWZ_OFFSET       (0x0000ffff)
#define LWZ_OFFSET_SIGN  (0x00008000)

/* ppc 64bit instructions */
#define LD_R0_R1_INSTR     (0xe8010000)   /* ld r0,d(r1) */
#define LD_R31_R1_INSTR    (0xebe10000)  /* ld r31,d(r1) */

#define STD_R0_R1_INSTR    (0xf8010000)  /* std  r0, x(r1) */
#define STD_R31_R1_INSTR   (0xfbe10000)  /* std  r31, x(r1) */

#define LFD_MASK        (0xfc000000)
#define LFD_INSTR       (0xc8000000)  /* lfd  frx,disp(ry) */
#define STFX_RY_MASK    (0xfc1f0000)  /* mask: stfd/stfs fx,d(ry) */
#define STFD_R1_INSTR   (0xd8010000)  /* stfd fx, d(r1)    any x */
#define STFD_R11_INSTR  (0xd80b0000)  /* stfd fx, d(r11)   any x */
#define STFS_R11_INSTR  (0xd00b0000)  /* stfs fx, d(r11)   any x */
#define LFD_R1_INSTR    (0xc8010000)  /* lfd  fx, d(r1) */
#define LFDU_MASK       (0xff000000)  /* mask for any lfdu fx, d(rx) */
#define LFDU_INSTR      (0xcc000000)  /* lfdu fx, d(rx) */
#define LFX_RY_MASK     (0xfc1f0000)  /* lfd/lfs  fx,d(ry) */
#define LFD_R11_INSTR   (0xc80b0000)  /* lfd fx,d(r11) */
#define LFS_R11_INSTR   (0xc00b0000)  /* lfs fx,d(r11) */
#define MTFSF_FF_MASK   (0xffff07fe)  /* mtfsf #xx,frx   any x */
#define MTFSF_FF_INSTR  (0xfdfe058e)  /* mtfsf #ff,frx   any x */

#define MW_R1_MASK      (0xfc1f0000)  /* lmw/stmw rx,d(ry) */
#define LMW_R1_INSTR    (0xb8010000)  /* lmw  rx, d(r1) */
#define STMW_R1_INSTR   (0xbc010000)  /* stmw rx, d(r1) */
#define LWSTW_RX_MASK   (0x03e00000)  /* mask for x in lmw/stmw rx,d(r1) */

#define STMW_INSTR      (0xbc000000)  /* any stmw */
#define STMW_MASK       (0xfc000000)

/* E500v2 SPE/DPFP support */
#define EVLST_MASK      (0xfc0007ff)  /* any ev load/store op code */
#define EVLDD_INSTR     (0x10000301)  /* any evldd  rD,ofst(rA) */
#define EVLDDX_INSTR    (0x10000300)  /* any evlddx rD,rA,rB */
#define EVSTDD_INSTR    (0x10000321)  /* any evstdd rD,ofst(rA) */
#define EVLSTDD_rX_rA_MASK   (0xffff07ff) /* evldd rD,0(rA)/evstdd rS,0(rA) */
#define EVLSTDD_OFST_MASK    (0x0000f800) /* long word ofst */
#define EVLDD_R31_R11_INSTR  (0x13eb0301) /* evldd  r31,0(r11) [diab] */
#define EVLDD_R31_R1_INSTR   (0x13e10301) /* evldd  r31,0(r1) [diab] */
#define EVSTDD_R31_R11_INSTR (0x13eb0321) /* evstdd r31,0(r11) [diab] */
#define EVSTDD_R31_R1_INSTR  (0x13e10321) /* evstdd r31,0(r1) [gnu] */
#define EVLDDX_R31_R11_R14_INSTR (0x13eb7300) /* evlddx r31,r11,r14 [gnu] */

#define RFI_INSTR       (0x4c000064) /* Return from interrupt */

/*  mtspr LR,r3.  Used to identify PatchArchTrapReturn, kinda hackishly */
#define R3_TO_LR        (0x7c6803a6)

/* ALTIVEC Instructions */
#define VEC_VX_RY_RZ_MASK   (0xfc1fffff) /* lvx/stvx vX,ry,rz    any X,y,z */
#define LVX_R12_R0_INSTR    (0xfc0c00ce) /* lvx  vX,r12,r0   any X */
#define STVX_R12_R0_INSTR   (0xfc0c01ce) /* stvx vX,r12,r0   any X */

#define MAX_INSTR_TO_SEARCH      (19*1024)
#define MAX_SEARCH_FOR_BLR            (6) /* between ADDI and BLR */
#define MAX_SEARCH_FOR_R11_BLR        (22) /* between LWZ R14,d(R11) and BLR */
#define MAX_SEARCH_FOR_MTSPR          (33) /* between LWZ_R0 and MTSPR */
#define MAX_SEARCH_FOR_MFSPR          (20) /* between STW_R0 and MFSPR */
#define MAX_SEARCH_FOR_LWZ            (20) /* between MTSPR and LWZ */
#define MAX_SEARCH_FOR_STWU           (10) /* between MFSPR and STWU */
#define MAX_SEARCH_FOR_STW            (10) /* between MFLR and STW */
#define MAX_SEARCH_FOR_BL_STWU_MFSPR  (3) /* BETWEEN BL and STWU/MFSPR, tail
                                              function */
#define MAX_SEARCH_FOR_BLR_R11        (30) /* BETWEEN BL and STWU/MFSPR, tail
                                              function */
#define MAX_SEARCH_FOR_BL_STW_R0_R11  (33) /* BETWEEN BL and STW R0,y(R11) */
#define MAX_SEARCH_FOR_R11_RESTORE    (40) /* lwz  r11,0(r1) ---> blr */
#define MAX_SEARCH_FOR_ADDI           (10) /* max between mtlr and addi if
                                              mtlr is sampled */
#define MAX_SEARCH_FOR_LWZ_R0         (3)  /* max between lwz r11,d(r1) and
                                              lwz r0,0(r11) */
#define MAX_MTLR_BLR                  (33)

#define MAX_PAGE_JUMP                  (5) /* max pages to skip in reverse
                                              search */
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


/* enumerate all registers needed for trcing ppc call stack contexts.  Note that
   NUM_GPREGS is used to bound accesses to the gpregs array and so must be
   placed after all gpreg names, but before all "special" registers. */
typedef enum {
    REG_LR = 0,
    REG_R0,
    REG_R11,
    REG_R12,
    NUM_GPREGS,
    REG_SP,
    REG_FP
} RegisterName;


#if !defined(CRAWL_IS_HOST_NATIVE)
#  if defined(__DCC__)
//#include <diab/asm.h>
asm volatile unsigned long get_sp(void)
{
!
    addi  r3, r1, 0
$$noadjust
}

asm volatile unsigned long get_fp(void)
{
!
    addi  r3, r31, 0
$$noadjust
}
asm volatile unsigned long get_lr(void)
{
!
    mflr  r3
}


asm volatile unsigned long get_pc(void)
{
% lab 1
!
    bl   1
    1:
    mflr  r3
}


#define ST_current_regs(regs)                   \
    do {                                        \
        (regs)->reg_sp = get_sp();              \
        (regs)->reg_fp = get_fp();              \
        (regs)->lr = get_lr();                  \
        (regs)->pc = get_pc();                  \
    } while(0);

#  else

static __inline__
void ST_current_regs(REG_SET * regs) __attribute__((always_inline));

static __inline__
void ST_current_regs(REG_SET * regs)
{
    register unsigned long pc, lr;
    register long sp __asm("r1");
    register long fp __asm("r31");
    __asm("mflr %0;"
        "bl 1f;"
        "1:"
        "mflr %1" : "=r" (lr), "=r" (pc));

    regs->pc = pc;
    regs->lr = lr;
    regs->reg_sp = sp;
    regs->reg_fp = fp;
}
#  endif  /* */
#endif  /* if !defined(CRAWL_IS_HOST_NATIVE) */


#endif  /* ifndef _CONTEXT_PPC_H_ */
