/* Copyright (c) 2005-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef mips_regs_h
#define mips_regs_h


/* registers are 32 bits on 32-bit machines and 64 bits on 64-bit machines */
typedef unsigned long _RType;

#define MIPS_NO_REGS                 (32)


typedef struct		/* REG_SET - MIPS architecture register set */
{
    unsigned long gpreg[MIPS_NO_REGS]; /* data registers */
    void *pc;			       /* program counter - really epc! */
} REG_SET;

#define RS_PC               offset(REG_SET, pc)
#define RS_REG(n)           offset(REG_SET, gpreg[n])

#define REG_SET_SIZE        sizeof(REG_SET)

#define spReg               gpreg[29]	/* stack pointer */
#define fpReg               gpreg[30]   /* gcc says this is frame pointer */
#define raReg               gpreg[31]	/* return address */

#define reg_pc              pc          /* program counter */
#define reg_sp              spReg       /* stack pointer */
#define reg_fp              fpReg       /* frame pointer */	
#define reg_ra              raReg       /* return address */

// TD: discover register size correctly
#define _WRS_FP_REGISTER_SIZE      4

/* 32 bit FP support */
#if (_WRS_FP_REGISTER_SIZE == 4)

/* number of fp registers on coprocessor */
#  define	FP_NUM_DREGS	16

/* 64 bit FP support */
#elif (_WRS_FP_REGISTER_SIZE == 8)

/* number of fp registers on coprocessor */
#  define	FP_NUM_DREGS	32

#else	/* _WRS_FP_REGISTER_SIZE */
#  error "invalid _WRS_FP_REGISTER_SIZE value"
#endif	/* _WRS_FP_REGISTER_SIZE */


/* extra space for expansion: e.g., vr5400 ACC */
#define FP_EXTRA	8


typedef struct fpContext	/* FP_CONTEXT */
{
    double fpx[FP_NUM_DREGS];	/* fp registers */
    int fpcsr;			/* control/statu */
    int pad;			/* padding */
    int fpxtra[FP_EXTRA];	/* ACC, etc */
} FPREG_SET;

#endif /* ifndef mips_regs_h */
