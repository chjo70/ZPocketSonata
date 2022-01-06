/* Copyright (c) 2001-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#if !defined(_CONTEXT_M68K_H_)
#define _CONTEXT_M68K_H_

/*
 * Architecture specific header files
 */
#define MIN_STACK_WIDTH (4)
#define MIN_INST_WIDTH  (2)

/*
 *  Types - define instruction and stack types here (?)
 */
#define INST_PUSH_FP   (0x4856)
#define INST_SP_TO_FP  (0x2c4f)
#define INST_RTS       (0x4e75)

/*
 *  Instruction values - define any instruction op-codes here
 */

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

#endif  /* if !defined(_CONTEXT_M68K_H_) */
