/* archPpc.h - Ppc architecture specific header */

/*
* Copyright (c) 2003-2004, 2006-2007, 2010, 2013, 2015 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
19jan15,my_  LP64 support (F2518)
22aug13,d_l  fix setjmp issue building with e500v2 tools. (WIND00246811)
29jul10,pad  Moved extern C statement after include statements.
04may07,zl   updated portable library build configuration.
08may06,zl   fixed JMP_BUF macros to match modified jmp_buf.
02feb06,mil  Updated for POSIX namespace conformance.
05jul04,md   add register type defintions
23mar04,zl   added macros for getting FP and return PC from jmp_buf.
05dec03,kk   define swap_PORTABLE for bLib swab()
11nov03,pes  written
*/

#ifndef __INCarchPpch
#define __INCarchPpch

#include <vsbConfig.h>
#include <arch/ppc/archPpcCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * Macros to obain FP and return PC from jmp_buf[] array.
 * On the user side, these macros are dependent on the setjmp() 
 * implementation in the compiler library.
 *
 * The frame pointer represents the SP (gpr1) at the entry of setjmp(), and
 * the return PC is the next instruction address from where setjmp() 
 * was called.
 */

/*
 * __EVEC__ stands for the e500v2 tools. When building setjmp.s using e500v2
 * tools on RTP side, it will save 64 bits GPRs using evstdd instruction.
 * The evstdd instruction stores the lower 32 bit register value to the higher
 * 4 bytes address for big endian mode.
 */

#ifdef __EVEC__
#define _WRS_FRAMEP_FROM_JMP_BUF(env)	((char *) (((long *)(env))[5]))  /* sp */
#else
#define _WRS_FRAMEP_FROM_JMP_BUF(env)	((char *) (((long *)(env))[3]))  /* sp */
#endif

#define _WRS_RET_PC_FROM_JMP_BUF(env)	((INSTR *) (((long *)(env))[2])) /* lr */


#ifndef _ASMLANGUAGE

typedef unsigned long _RType;		/* default register type */

#endif  /* _ASMLANGUAGE */

#ifdef _WRS_CONFIG_LP64
#define _PPC_REG_SIZE		8	/* default register size */
#else
#define _PPC_REG_SIZE		4	/* default register size */
#endif

#define _PPC_TEXT_SEG_ALIGN	4	/* 4 byte text segment alignment */

#ifdef __cplusplus
}
#endif

#include <arch/ppc/toolPpc.h>

#endif /* __INCarchPpch */
