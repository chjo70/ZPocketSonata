/* mips.h - MIPS-specific Context information. */

/* Copyright (c) 1999-2011, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
16jan15,wzc  ppc64 support.(US49903)
06mar14,wzc  redefine the ST_current_regs.(WB4-2945)
*/

/*
DESCRIPTION
This file contains MIPS-specific context code.  It supports both the o32 and
n32 ABIs.

The MIPS n32 ABI was developed by Silicon Graphics Incorporated (SGI) for
ease in porting 32-bit operating systems and applications to 64-bit MIPS
processors.  This entails the following issues.

+ The n32 ABI supports 32-bit addresses and integers, sign extending them
to 64 bits before being placed in the 64-bit registers.  The original ABI
from MIPS is designated o32 and has no support for 64-bit registers,
restricts the number of floating point (FP) registers to 16 instead of 32,
and makes inefficient use of the FP registers.  Unlike o32 which allows
passing of up to 4 values in general purpose (GP) and FP registers
(r4-r7, f12-f15), n32 supports 8 registers each (r4-r11, f12-f19).

+ The 64-bit internal representation of data necessitates stack region
alignment to quad-words (16 bytes) and all stack entries must be aligned to
double-word (8-byte) addresses, even values occupying 32 bits or less.

+ Within each 64-bit stack slot non-FP values requiring less than 64 bits are
right justified, i.e., occupy the highest order bytes, in big-endian systems.
(MIPS is a native little-endian architecture that supports big-endian
operation.  So, for example, given a stack entry address of 0x40080, the
starting address of a byte, short, int, and double are as follows for the
different endian systems:

Type    Little      Big
------  --------    --------
byte    0x400080    0x400087
short   0x400080    0x400086
int32   0x400080    0x400084
float   0x400080    0x400084
double  0x400080    0x400080

+ Integers of 32 bits are always sign-extended before being passed in a
register, regardless of whether the integer is signed or not.

+ Quad-precision (128-bit) FP values (C long double) are passed in 16-byte
aligned stack slots and even-odd pairs of FP registers, even if doing so
skips a 64-bit stack slot or a register assignment.

+ FP values are passed in FP registers whenever possible, irrespective of any
integer values preceding them in an argument list, unlike o32.

    - Variable (varargs) arguments are an exception to this rule.  Any FP
    values in a varargs part of the argument list are passed in GP registers.
    NOTE: functions accepting variable numbers of FP arguments MUST be
    prototyped!

+ C99 complex types are passed in multiple FP registers, as available:

Type                    Passed as
-------------------     --------------
float complex           2 floats
double complex          2 doubles
long double complex     2 long doubles

This has an impact on stack slots.  Because the size of a float complex is
8 bytes (2 4-byte floats) but two float argument registers take 16 bytes
of stack space, the float complex stack entry is padded with an extra 8 bytes.
For example, if a float complex argument is passed in f14 and f15 and the next
argument in f16, the corresponding stack locations for a slot at 0x400080
would be the first float at 0x400080 and the second float at 0x400084, but
the following argument would be in a slot starting at 0x400090.

+ Structures, unions or other composite types are regarded as a series of
64-bit values and are passed into functions as a number of GP registers and/or
FP registers as they fit and any excess passed on the stack according to the
composition of the type and the stack alignment rules.  This means:

    - Regardless of the structure layout, it is treated by the compiler as a
    series of 64-bit parts.  If a part is a double float and not part of a
    union, it is passed in a FP register while all other parts as passed in
    GP registers.

    - All unions are treated as a series of integer double-words as far as
    GP register assignment is concerned.  NOTE: no attempt is made to
    differentiate FP members from integer for passing in FP registers!

    - Array members of structures are passed like unions while array arguments
    are passed by reference.  (Applies to C and C++, but others may differ.)

    - Despite right-justifying small scalar values in their stack slots,
    structure parameters are always left-justified, which applies to
    structures smaller than 64-bits as well as any remaing parts of a
    structure not passed in registers, whether or not it is an integral number
    of 64-bit parts.  In other words, the remaining part is stored on the
    stack exactly as laid out in regular memory.

+ Return values from functions are passed back in r2 (and r3 if needed) or
f0 (and f2 if needed), as specified by the type.  Note that the f0/f2 rule
allows for even/odd pairing.  Composite return types (structure, union, etc.)
have strange rules that say they must be returned as follows:

    - A structure with only one or two FP members returns them with f0 holding
    the first and and f2 the second.

    - Any other structure or union members of at most 128 bits are returned
    with r2 holding the first 64 bits, r3 holding the second 64 bits.

    - Composite return types larger than 128 bits are passed back transparently
    in a memory location reserved by the caller.  A pointer to the area is
    passed implicitly as the first argument to the function.

+ The callee function saves any non-volatile registers it uses, ranging from
GP registers r24 to r31 and the even FP registers from f20 to f30.

+ Unlike o32, routines are NOT restricted to a single exit block (epilogue).

+ Unlike o32, the gp (global pointer registr r28) is saved by the callee,
rather than the caller.  This gives the following saving scheme:

Reg#        Name    Use                     Saver
---------   -----   ----------------------  -------------
$0          zero    HW zero                 N/A
$1          at      assembler temporary     CALLER
$2-$3       v0-v1   function results        CALLER
$4-$11      a0-a7   function input args     CALLER
$12-$15     t4-t7   temporaries             CALLER
$16-$23     s0-s7   always saved if used    callee
$24-$25     t8-t9   temporaries             CALLER
$26-$27     k0-k1   reserved for kernel     N/A
$28         gp      global pointer          callee
$29         sp      stack pointer           callee
$30         s8/fp   frame pointer, if used  callee
$31         ra      return address          CALLER
hi,lo               mult/div special regs   CALLER
$f0,$f2             FP results              CALLER
$f1,$f3             FP temporaries          CALLER
$f4-$f11            FP temporaries          CALLER
$f12-$f19           FP input args           CALLER
$f20-$f23 (32-bit)  FP temporaries          CALLER
$f24-$f31 (64-bit)  FP temporaries          callee
$f20-$f31 (even, n32) FP temporaries        callee
$f20-$f31 (odd, n32)  FP temporaries        CALLER

+ At most 8 registers are used for passing input arguments, whether all FP,
all GP, or a combination thereof.  Any remaining arguments are passed on the
stack.  The function passing the arguments (the caller) is not required to
allocate space on the stack for the registers nor is the called function (the
callee), unlike o32.  In the following examples of register/stack assignment,
's' is a single precision FP, 'd' is a double precision FP, and 'n' is an
integer.

Argument List               N32 Register and Stack Assignments
--------------------------  ----------------------------------------------
n1,n2                       r4,r5
s1,s2                       f12,f13
d1,d2                       f12,f13
s1,d1                       f12,f13
d1,s1                       f12,f13
n1,d1                       r4,f13
d1,n1,d2                    f12,r5,f14
n1,n2,d1                    r4,r5,f14
d1,n1,n2                    f12,r5,r6
s1,n1,n2                    f12,r5,r6
d1,s1,s2                    f12,f13,f14
s1,s2,d1                    f12,f13,f14
n1,n2,n3,n4,n5,n6,n7,n8     r4,r5,r6,r7,r8,r9,r10,r11
n1,n2,n3,d1                 r4,r5,r6,f15
n1,n2,n3,s1                 r4,r5,r6,f15
s1,s2,s3,s4,s5,s6,s7,s8     f12,f13,f14,f15,f16,f17,f18,f19
s1,n1,s2,n2                 f12,r5,f14,r7
n1,s1,n2,s2                 r4,f13,r6,f15
n1,s1,n2,n3                 r4,f13,r6,r7
d1,d2,d3,d4,d5,d6,d7,d8     f12,f13,f14,f15,f16,f17,f18,f19
d1,d2,d3,d4,d5,s1,s2,s3,s4  f12,f13,f14,f15,f16,f17,f18,f19,stack
d1,d2,d3,s1,s2,s3,n1,n2,n3  f12,f13,f14,f15,f16,f17,r10,r11,stack

+ The bit sizes for o32, n32, and 64-bit model C types:

C Type          032 and n32         64-bit
--------------  ------------------  ------
char             8                   8
short int       16                  16
int             32                  32
long int        32                  64
long long int   64                  64
pointer         32                  64
float           32                  32
double          64                  64
long double     64 (128 in n32)     128
-----------------------------------------------------------------------------*/

#ifndef _CONTEXT_TARGET_H_
#define _CONTEXT_TARGET_H_

/* for REG_SET definition */
#if defined(__VXWORKS__)
#  include <regs.h>
#else
#  include "mips_regs.h"
#endif
#include <st_inttypes.h>
#include "st_endian.h"
#include "st_compiler_shims.h"  /* for win32 inline */


/*
 * Architecture specific defines
 */

/*
 * Instruction search range from the original input PC is limited to + or -
 * RTITOOLS_CONTEXT_MAX_FN_LENGTH instructions.
 */
#define RTITOOLS_CONTEXT_MAX_FN_LENGTH (2048)

typedef unsigned long tAddr;   /* Address type */

#define MIPS_ABI_O32    (1)
#define MIPS_ABI_N32    (2)

#if defined(__VXWORKS__)
#  if defined(_WRS_MIPS_64BIT_CPU) && _WRS_MIPS_64BIT_CPU
#    define MIPS_ABI    MIPS_ABI_N32
#  else
#    define MIPS_ABI    MIPS_ABI_O32
#  endif
#elif defined(__unix__) || defined(WIN32)
#  define MIPS_ABI      MIPS_ABI_O32
#else
#  error unknown MIPS ABI
#endif

#if (MIPS_ABI==MIPS_ABI_O32)
typedef uint32_t ST_TARGET_ADDR_T;
#  define PRIa  "0x%"PRIx32
#  define STACK_ALIGN     (4)
#  define FRAME_ALIGN     (4)
#  define MIN_STACK_WIDTH (4)
#elif (MIPS_ABI==MIPS_ABI_N32)
typedef uint64_t ST_TARGET_ADDR_T;
#  define PRIa  "0x%"PRIx64
/* 64-bit N32 stack alignment is 8 bytes, but VxWorks only
 * supports 32-bit addresses, so allow 4-byte alignment.
 */
#  define STACK_ALIGN     (4)
#  define FRAME_ALIGN     (8)
#  define MIN_STACK_WIDTH (8)
#endif

/* big endian 64-bit targets require a 4-byte register offset. */
#if defined(ST_TARGET_BIG_ENDIAN) && (MIPS_ABI == MIPS_ABI_N32)
#  define REGISTER_OFFSET (4)
#else
#  define REGISTER_OFFSET (0)
#endif

#define MIN_INST_WIDTH  (4)


/* Number of back branches before we stop taking them */
#define MAX_ARB_BRANCHES         10
    
typedef uint32_t tInst;   /* Instruction type */
typedef int  rOffset; /* instruction register offset field */
#define INST_SIZE (4)   /* Size of instr -- avoid sizeof() overhead */

/*
 *  Parameters - define context parameters here
 */

/* How many instructions to look backwards */
#define MAX_BACKWARD_SEARCH      10

/* Instructions before we assume we're not in the prologue.  This typically
   includes just the instructions between the stack push 
   (addiu    sp,sp,-96) and saving the link register (sw     ra,56(sp)).*/
#define MAX_PROLOGUE_LENGTH      24

/* How long is the epilogue? [until restore fp] */
#define MAX_EPILOGUE_LENGTH      35

#if (MAX_PROLOGUE_LENGTH > MAX_BACKWARD_SEARCH)
    #if (MAX_PROLOGUE_LENGTH > MAX_EPILOGUE_LENGTH)
    #define MAX_BACKWARD_LENGTH      (MAX_PROLOGUE_LENGTH * INST_SIZE)
    #else
    #define MAX_BACKWARD_LENGTH      (MAX_EPILOGUE_LENGTH * INST_SIZE)
    #endif
#else
    #if (MAX_BACKWARD_SEARCH > MAX_EPILOGUE_LENGTH)
    #define MAX_BACKWARD_LENGTH      (MAX_BACKWARD_SEARCH * INST_SIZE)
    #else
    #define MAX_BACKWARD_LENGTH      (MAX_EPILOGUE_LENGTH * INST_SIZE)
    #endif
#endif

#define MAX_FORWARD_LENGTH           (4 * INST_SIZE)
#define MAX_SEARCH_LENGTH            (MAX_BACKWARD_LENGTH + \
                                      MAX_FORWARD_LENGTH)


/*
 *  Instruction values - define any instruction op-codes here
 */
#define INST_UNKNOWN       (0xffffffff)

#define INST_ADD_TO_SP     (0x27bd0000) /* addiu sp,sp,immed */
#define MASK_ADD_OFFSET    (0x0000ffff) /* Signed 16-bit offset added to SP */
#define MASK_NEG_OFFSET    (0x00008000)
#define NEG_SIGN_EXTEND     0xffff0000
#define MASK_ADD_OPCODE    (0xffff0000)

#define MASK_OPCODE         0xfc000000  /* MIPS major op codes are 1st 6 bits*/
#define INST_ADDIU          0x24000000  /* addiu rd,rs,immed */
#define INST_LUI            0x3c000000  /* lui   rd,immed    */

#define MASK_BASIC_OPCODE   0xfc0007ff  /* add, sub, mult, div, jr, mov, etc.*/
#define INST_ADDU           0x00000021  /* addu  rd,rs,rt    */
#define INST_NOP            0x00000000

/* Convert mips' signed 16-bit immediate instruction-embedded values
 * into signed int (32-bit) values. Note that ints are still 32 bits
 * for MIPS64.
 */
static inline
int32_t IMM_TO_INT(tInst instruction)
{
    if (instruction & MASK_NEG_OFFSET) {
        return (instruction & MASK_ADD_OFFSET) | NEG_SIGN_EXTEND;
    }
    return instruction & MASK_ADD_OFFSET;
}


#define INST_STORE_RA_64   (0xffbf0000) /* sd  ra,offset(sp) */
#define INST_RESTORE_RA_64 (0xdfbf0000) /* ld  ra,offset(sp) */
#define INST_STORE_RA_32   (0xafbf0000) /* sw  ra,offset(sp) */
#define INST_RESTORE_RA_32 (0x8fbf0000) /* lw  ra,offset(sp) */

#define MASK_SWLW_OFFSET   (0x0000ffff) /* Store/load word offset */
#define MASK_SWLW_OPCODE   (0xffff0000)
#define MASK_SWLW_FP_SP    (0xffff8000)
#define INST_SW_FP_SP      (0xafbe0000) /* sw  fp,+d(sp) */
#define INST_LW_FP_SP      (0x8fbe0000) /* lw  fp,+d(sp) */
#define INST_FP_TO_SP      (0x03c0e821) /* move sp,fp  [move sp,s8] */
#define INST_SP_TO_FP      (0x03a0f021) /* move fp,sp  [move s8,sp] */
#define MASK_LX_OPCODE     (0xfc0007ff)
#define INST_LBUX          (0x7c00018a) /* LBUX Rd,Rindx(Rbase) DSP ASE only */
#define INST_LHX           (0x7c00010a) /* LHX  Rd,Rindx(Rbase) DSP ASE only */
#define INST_LWX           (0x7c00000a) /* LWX  Rd,Rindx(Rbase) DSP ASE only */

#define MASK_NEG_OFFSET    (0x00008000) /* for all 16-bit signed offsets */

/* Unconditional branch instructions */
#define INST_JR_REG        (0x00000008)       /* jr t1, for example */
#define INST_JR_T9_REG     (0x03200008)       /* jr   t9 */
#define MASK_JR_REG        (0xfc1ff83f)       /* ick */
#define INST_J             (0x08000000)       /* First six bits */
#define INST_JAL           (0x0c000000)       /* First six bits */
#define MASK_JUMP_OFFSET   (0x03ffffff) /* Mask off the first six bits */
#define MASK_JUMP_OPCODE   (0xfc000000)

/* Conditional branch instructions */
#define INST_BEQ           (0x10000000) /* All branches execute the delay slot */
#define INST_B             (0x10000000) /* B is BEQ 0, 0, offset */
#define INST_BNE           (0x14000000)
#define INST_BLEZ          (0x18000000)
#define INST_BGTZ          (0x1c000000)
#define INST_BPOSGE32      (0x041c0000) /* BPOSGE32  (DSP ASE only) */
#define MASK_BRANCH_OFFSET (0x0000ffff) /* Branch offset */
#define MASK_BRANCH_OPCODE (0xfc000000)
#define MASK_B_OPCODE      (0xffff0000)

#define INST_RTS           (0x03e00008) /* jr ra */

#define INST_BRANCH_SELFPT (0x1000ffff)

/* eret instruction */
#define INST_ERET          (0x42000018)

#define CAUSE_EXCCODE_MASK (0x0000007c)
#define CAUSE_INTRPT_CODE  (0)
#define CAUSE_SYSCL_CODE   (8)


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


#if defined(__VXWORKS__) && (_WRS_INT_REGISTER_SIZE == 8)
typedef union {
    unsigned long long ull;
    void *             ptr;
    unsigned long      ul[2];
    void *             ptr32[2];
} SZ_XLATE;

#  if defined(ST_TARGET_BIG_ENDIAN)
#    define ULL_HI    0
#    define ULL_LO    1
#  else          /* ST_TARGET_LITTLE_ENDIAN */
#    define ULL_HI    1
#    define ULL_LO    0
#  endif /* ST_TARGET_*_ENDIAN */
#endif /* _WRS_INT_REGISTER_SIZE */


#if !defined(CRAWL_IS_HOST_NATIVE)
#  if defined(__DCC__)
asm volatile unsigned long get_sp(void)
{
!
    move  v0, sp
}


asm volatile unsigned long get_ra(void)
{
!
    move  v0, ra
}


asm volatile void *get_pc(void)
{
!
% lab 1
    jal  1
    1:
    move  v0, ra
}


#define ST_current_regs(regs)                   \
    do {                                        \
        (regs)->spReg = get_sp();               \
        (regs)->raReg = get_ra();               \
        (regs)->pc = get_pc();                  \
    } while(0);

#  endif  /* if __DCC__ */
#endif  /* if !defined(CRAWL_IS_HOST_NATIVE) */


#endif  /* ifndef _CONTEXT_TARGET_H_ */
