/* Copyright (c) 2005-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */


#ifndef i86_regs_h
#define i86_regs_h

#ifdef __cplusplus
    extern "C" {
#endif

typedef struct			/* REG_SET - 80x86 register set */
{
    unsigned long edi;			/* general register */
    unsigned long esi;			/* general register */
    unsigned long ebp;			/* frame pointer register */
    unsigned long esp;			/* stack pointer register */
    unsigned long ebx;			/* general register */
    unsigned long edx;			/* general register */
    unsigned long ecx;			/* general register */
    unsigned long eax;			/* general register */
    unsigned long eflags;		/* status register */
    void * pc;				/* program counter (must be last) */
} REG_SET;


#define reg_sp     esp
#define reg_fp     ebp
#define reg_pc     pc

#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* i86_regs_h */
