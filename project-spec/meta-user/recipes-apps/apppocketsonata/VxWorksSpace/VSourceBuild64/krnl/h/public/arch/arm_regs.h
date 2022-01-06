/* Copyright (c) 2005-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef arm_regs_h
#define arm_regs_h

#ifdef __cplusplus
    extern "C" {
#endif

typedef struct {                /* REG_SET - ARM register set */
    unsigned long  r[15];	/* general purpose registers 0-14 */
    unsigned int   *pc;		/* program counter */
    unsigned long  cpsr;	/* current PSR */
} REG_SET;

#define reg_pc          pc   /* frame pointer */
#define reg_fp          r[11]   /* frame pointer */
#define reg_sp          r[13]   /* stack pointer */
#define reg_lr          r[14]   /* return pointer */

#ifdef __cplusplus
    }   /* extern "C" */
#endif

#endif /* arm_regs_h */
