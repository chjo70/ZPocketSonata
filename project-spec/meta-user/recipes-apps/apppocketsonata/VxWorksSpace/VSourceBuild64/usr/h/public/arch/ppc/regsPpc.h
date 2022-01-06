/* regsPpc.h - PowerPC registers */

/*
 * Copyright (c) 2004, 2012, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
10feb15,my_  add LP64 support(F2518)
21mar12,jpb  Updated for POSIX namespace isolation conformance (part of 
             defect Defect WIND000307800).
22oct04,md   move saveRegs() prototype to regs.h
05jul04,md   derived from kernel 01j version
*/

#ifndef __INCregsPpch
#define __INCregsPpch

#ifdef __cplusplus
extern "C" {
#endif

#define _Vx_GREG_NUM        32      /* has 32 32/64-bit data registers */

#ifndef	_ASMLANGUAGE
typedef struct _Vx_register_set
    {
    _RType gpr[_Vx_GREG_NUM];	/* general pourpose registers */
    _RType msr;			/* machine state register */
    _RType lr;			/* link register */
    _RType ctr;			/* count register */
    _RType pc;			/* program counter */
    _RType cr;			/* condition register */
    _RType xer;			/* fixed-point exception register */

    /* the following fields keep this structure compatible with the kernel */

    _RType spare0;		/* MQ/base of page table */
    _RType spare1;		/* SR regs */
    _RType spare2;		/* SR regs */
    _RType spare3;		/* keeps struct size consistent */
    _RType spare4;		/* keeps struct size consistent */
    } _Vx_REGISTER_SET;

#if !defined (_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE) && \
    !defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
/* some common names for registers */

#undef	spReg
#define spReg	gpr[1]	/* stack pointer */
#undef	fpReg
#define	fpReg	gpr[31]	/* frame pointer */
#define reg_pc	pc	/* program counter */
#define reg_sp	spReg	/* stack pointer */
#define reg_fp	fpReg	/* frame pointer */

#endif  /* !_POSIX_xxx_SOURCE */
#endif	/* !_ASMLANGUAGE */

#if !defined (_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE) && \
    !defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#define GREG_NUM        _Vx_GREG_NUM

#define PPC_ARG0_REG		3	/* params start at register 3 */
#define PPC_MAX_ARG_REGS	8	/* max # of params passed in register */

#define REG_SET_GRBASE	0x00	/* general purpouse register base */
#define REG_SET_GR(n)	(REG_SET_GRBASE + _PPC_REG_SIZE*(n))
#define REG_SET_MSR	(REG_SET_GR(GREG_NUM))
#define REG_SET_LR	(REG_SET_MSR + _PPC_REG_SIZE)
#define REG_SET_CTR	(REG_SET_LR + _PPC_REG_SIZE)
#define REG_SET_PC	(REG_SET_CTR + _PPC_REG_SIZE)
#define REG_SET_CR	(REG_SET_PC + _PPC_REG_SIZE)
#define REG_SET_XER	(REG_SET_CR + _PPC_REG_SIZE)
#define REG_SET_SPARE0	(REG_SET_XER + _PPC_REG_SIZE)
#define REG_SET_SPARE1	(REG_SET_SPARE0 + _PPC_REG_SIZE)
#define REG_SET_SPARE2	(REG_SET_SPARE1 + _PPC_REG_SIZE)
#define REG_SET_SPARE3	(REG_SET_SPARE2 + _PPC_REG_SIZE)
#define REG_SET_SPARE4	(REG_SET_SPARE3 + _PPC_REG_SIZE)

#define	PC_OFFSET	REG_SET_PC

/* size of the full REG_SET structure, including spare bytes */

#define _PPC_REG_SET_SIZE       (_PPC_REG_SIZE * (GREG_NUM + 9))

#endif /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCregsPpch */
