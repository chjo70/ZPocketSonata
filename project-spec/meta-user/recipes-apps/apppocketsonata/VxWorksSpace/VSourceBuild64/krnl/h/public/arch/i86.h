/* i86.h - x86 dependent header file for context tools */

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
DESCRIPTION:
Architecture specific header file for Intel x86, PentiumX.
*/

#ifndef _CONTEXT_TARGET_H_
#define _CONTEXT_TARGET_H_

/* for REG_SET definition */
#if defined(__VXWORKS__)
#  include <regs.h>
#else
#  include "i86_regs.h"
#endif
#include <st_inttypes.h>

#define ST_TARGET_LITTLE_ENDIAN


/*
 *  Types - define instruction and stack types here
 */
#define MIN_STACK_WIDTH (4)
#define MIN_INST_WIDTH  (1)
#define STACK_ALIGN     (4)
#define FRAME_ALIGN     (4)

#if defined(X86_CRAWL_ADDRESS_SIZE)
#  if (X86_CRAWL_ADDRESS_SIZE == 4)
#    define PRIa  "0x%"PRIx32
typedef uint32_t ST_TARGET_ADDR_T;
#  elif (X86_CRAWL_ADDRESS_SIZE == 8)
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
#else
/* default to 32-bit logic */
#  define PRIa  "0x%"PRIx32
typedef uint32_t ST_TARGET_ADDR_T;
#endif


/* This value affects checking offset (wrt. current pc) for existance
   of pages in memory */
#define MAX_INST_LENGTH (18)
/*
 *  Instruction values - define any instruction op-codes here
 */
#define INST_PUSH_EBP                   (0x55)    /* PUSH EBP         */
#define INST_PUSH_EAX                   (0x50)    /* PUSH EAX         */
#define INST_MOVE_ESP_2_EBP             (0xe589)  /* MOV EBP, ESP     */
#define INST_MOVE_ESP_2_EBP_ICC         (0xec8b)  /* MOV EBP, ESP ; alternate*/
#define INST_MOVE_EBP_2_ESP             (0xec89)  /* MOV ESP, EBP     */
#define INST_LEA_EBP_2_ESP              (0x658d)  /* LEA #offset(EBP), ESP */
#define INST_POP_EBP                    (0x5d)    /* POP EBP          */
#define INST_MOVE_ESPOFF1_2_EAX         (0x0424448b) /* MOV 0x4(ESP,1) EAX */
#define INST_ADD_2_ESP_1                (0xc481)
#define INST_ADD_2_ESP_2                (0xc483)
#define INST_MOVE_ESP_D8_EBP            (0x6c8b)
#define INST_MOVE_ESP_D32_EBP           (0xac8b)
#define SIB_ESP_OFFSET                  (0x24)

#define INST_RET                        (0xc3)    /* RET              */
#define INST_RET_OFFSET                 (0xc2)    /* RET $offset      */
#define INST_RET_FAR                    (0xcb)    /* RET FAR          */
#define INST_RET_FAR_OFFSET             (0xca)    /* RET FAR $offset  */
#define INST_RET_4                      (0x04c2)  /* RET $4           */
#define INST_IRET                       (0xcf)    /* IRET             */
#define INST_LEAVE                      (0xc9)    /* LEAVE            */
#define INST_CALL                       (0xe8)    /* CALL             */

#define INST_PUSHF                      (0x9c)    /* PUSHF            */
#define INST_POPF                       (0x9d)    /* POPF             */

#define INST_SUB_ESP_BYTE               (0xec83)  /* SUB #byte, ESP   */
#define INST_SUB_ESP_WORD               (0xec81)  /* SUB #word, ESP   */
#define INST_SUB_REG_FRM_ESP1           (0xc429)  /* SUB %reg, ESP    */
#define INST_SUB_REG_FRM_ESP2           (0xe02b)  /* SUB ESP, %reg    */
#define MOD_RM_MASK                     (0x07ff)
#define MOD_REG_MASK                    (0x38ff)
#define MOD_DISP_MASK                   (0x07ff)
#define MOD_MOD_MASK                    (0xc0ff)

#define INST_JMP_EBX                    (0x03ff)  /* JMP #word(%EBX)  */
#define INST_JMP_MEM                    (0x05ff)  /* JMP *(#imme)     */
#define INST_UD2A                       (0x0b0f)
#define INST_HLT                        (0xf4)    /* HLT              */

/* operand sizes */
#define byteSzB (1)      /* size of a byte operand */
#define wordSzB (2)      /* size of a word operand */
#define dwordSzB (4)     /* size of a dword operand */

#define READ_AHEAD (12)  /* byte offset to read ahead from current
                            pcRegister */
#define PAGE_4MB_MASK   (0xffc00000)
#define PAGE_4KB_MASK   (0xfffff000)

/* The following values are or'ed together to form an instruction type
   descriptor */
/* the instruction types of interest */
#define IS_CALL (1<<1)   /* call instruction */
#define IS_RET  (1<<2)   /* near return instruction */
#define IS_RETF (1<<3)   /* far return instruction */
#define IS_JUMP (1<<4)   /* jump instruction */
#define IS_JCC  (1<<5)   /* conditional jump instruction */
#define ILLEGAL (1<<6)   /* illegal instruction */

/* addressing modes for calls and jumps */
#define REL_B   (1<<10)  /* relative address, byte offset */
#define REL_W   (1<<11)  /* relative address, word offset */
#define REL_D   (1<<12)  /* relative address, dword offset */
#define REL_X   (1<<13)  /* relative address, word or dword offset */
#define INDIR   (1<<14)  /* indirect (register or memory) address */
#define PTR_WW  (1<<15)  /* 4-byte pointer */
#define PTR_WD  (1<<16)  /* 6-byte pointer */
#define PTR_WX  (1<<17)  /* 4 or 6-byte pointer */

/* prefixes */
#define PREFIX_INST (1<<20) /* instruction prefix */
#define PREFIX_SEG  (1<<21) /* segment override prefix */
#define PREFIX_OPR  (1<<22) /* operand size override */
#define PREFIX_ADDR (1<<23) /* address size override */
/* end of instruction type descriptor values */

/* number of instructions we parse before giving up */
#define RTITOOLS_MAX_FORWARD_SEARCH     (4098)
#define RTITOOLS_MAX_FORWARD_POP_SEARCH (20)

/* Number of back branches before we stop taking them */
#define RTITOOLS_MAX_BACK_BRANCHES      (50)


/*
 *  Context flags - define arch specific context package flags here
 */


 /* Does context package use sp?   By default, VxWorks targets will use
    frame-pointer-based crawls, other targets will do a more traditional crawl.
 */
#if !defined(RTITOOLS_CONTEXT_USES_SP)
#  if defined(__VXWORKS__)
#    define RTITOOLS_CONTEXT_USES_SP        (0)
#  else
#    define RTITOOLS_CONTEXT_USES_SP        (1)
#  endif
#endif
  
/* CHECK_TOP_FIRST if you want to call RtiTools_ContextTopDiscover at the
 * beginning of ST_CallingContextGet; CHECK_TOP_LAST if you want to call it at
 * the end.  You can use both, don't unless you have to.
 */
#if (RTITOOLS_CONTEXT_USES_SP == 0)
#  define RTITOOLS_CONTEXT_CHECK_TOP_FIRST        (1)
#  define RTITOOLS_CONTEXT_CHECK_TOP_LAST         (0)
#else
#  define RTITOOLS_CONTEXT_CHECK_TOP_FIRST        (0)
#  define RTITOOLS_CONTEXT_CHECK_TOP_LAST         (1)
#endif

#define RTITOOLS_CONTEXT_USES_FP        (1) /* Does context package use fp? */


/* enumerate all registers needed for tracing x86 call stack contexts.  Note 
   that NUM_GPREGS is used to bound accesses to the gpregs array and so must be
   placed after all gpreg names, but before all "special" registers.

   Vx support defines the SP as a gpreg because it's only ever needed to trace
   out of the first frame */
typedef enum {
    REG_LR = 0,
#if (!RTITOOLS_CONTEXT_USES_SP)
    REG_SP,
#endif
    NUM_GPREGS,
#if (RTITOOLS_CONTEXT_USES_SP)
    REG_SP,
#endif
    REG_FP
} RegisterName;


#if !defined(CRAWL_IS_HOST_NATIVE)
/**
 *  Populate the given REG_SET with values from "now" in the current thread of
 * execution.
 */
#ifdef __DCC__
asm volatile unsigned long get_sp(void)
{
!
 mov %esp, %eax
$$noadjust
}

asm volatile unsigned long get_fp(void)
{
!
 mov %ebp, %eax
}

asm volatile unsigned long get_pc(void)
{
% lab 1
!
 call 1;
 1:
 pop %eax
}

#define ST_current_regs(regs) \
do { \
(regs)->pc = get_pc(); \
(regs)->reg_fp = get_fp(); \
(regs)->reg_sp = get_sp(); \
} while(0)

#else
static __inline__
void ST_current_regs(REG_SET * regs) __attribute__((always_inline));

static __inline__
void ST_current_regs(REG_SET * regs)
{
/*does no support diab compiler*/
    register unsigned char *eip;
    /* coverity[var_decl] */
    register long esp __asm__("esp");
    /* coverity[var_decl] */
    register long ebp __asm__("ebp");

    __asm__("call 1f;"
        "1:"
        "pop %0" : "=r" (eip));

    regs->pc = eip;
    regs->reg_sp = esp;
    regs->reg_fp = ebp;

    /* this little hack could use some explaining: when we perform a stack
     * crawl from a register set generated by this routine, the "pop"
     * instruction from the inline assembly above is accounted for, even though
     * it isn't included in the stack pointer we gathered, so we need to
     * adjust for it here.  Since we use a stack walk (frame-pointer based) on
     * VxWorks targets, we only need this adjustment for linux targets. */
#if defined(__linux__)
    regs->reg_sp -= sizeof(unsigned long);
#endif
}
#endif
#endif  /* if !defined(CRAWL_IS_HOST_NATIVE) */


#endif /* _CONTEXT_TARGET_H_ */
