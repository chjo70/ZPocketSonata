/* simso.h - SimSolaris-specific C-code for Context. */

/* Copyright (c) 1999-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
DESCRIPTION
This file contains SimSolaris-specific context code.
*/

#ifndef _CONTEXT_TARGET_H_
#define _CONTEXT_TARGET_H_

#include <stdint.h>

#define ST_TARGET_BIG_ENDIAN


/*
 * Architecture specific header files
 */

/*
 *  Types - define instruction and stack types here (?)
 */
#define MIN_STACK_WIDTH (4)
#define MIN_INST_WIDTH  (2)
#define STACK_ALIGN     (4)
#define FRAME_ALIGN     (4)

typedef uint32_t ST_TARGET_ADDR_T;

/*
 *  Instruction values - define any instruction op-codes here
 */
#define INST_RETL        (0x81c3e008)
#define INST_SAVE        (0x9de3b000)
#define MASK_SAVE        (0xfffff000)
#define INST_RESTORE     (0x81e80000)

#define INST_RET         (0x81c7e008)
#define INST_BA          (0x10800000)
#define INST_BR          (0xc1c00000)
#define MASK_DISPL       (0x003FFFFF)
#define SIGN_DISPL       (0x00200000)

/*
 *  Context flags - define arch specific context package flags here
 */
/* CHECK_TOP_FIRST if you want to call RtiTools_ContextTopDiscover at the
 * beginning of ST_CallingContextGet; CHECK_TOP_LAST if you want to call it at
 * the end.  You can use both, don't unless you have to.
 */
#define RTITOOLS_CONTEXT_CHECK_TOP_FIRST        (0)
#define RTITOOLS_CONTEXT_CHECK_TOP_LAST         (1)

#define RTITOOLS_CONTEXT_USES_SP        (1)   /* Does context package use sp? */
#define RTITOOLS_CONTEXT_USES_FP        (0)   /* Does context package use fp? */

/* enumerate all registers needed for tracing simsolaris call stack contexts.
   Note that NUM_GPREGS is used to bound accesses to the gpregs array and so
   must be placed after all gpreg names, but before all "special" registers. */
typedef enum {
    REG_LR,
    NUM_GPREGS,
    REG_SP,
} RegisterName;

#endif  /* _CONTEXT_TARGET_H_ */
