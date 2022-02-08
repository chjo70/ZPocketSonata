/* altivecPpcLib.h - PowerPC Altivec coprocessor support library header */

/* Copyright 1984-2010, 2014 Wind River Systems, Inc. */
/*
modification history
--------------------
20nov14,w_x  LP64 adaptation to support PPC64(F2518)
29apr10,pad  Moved extern C statement after include statements.
18sep09,pmr  add VSCR definitions
01jun06,pch  consolidate vector offset definitions in excPpcLib.h
21feb05,asa  Fix SPR#102393: removed #if def 0 around altivec register
	 tables
04oct01,yvp  Fix SPR69306: Changed Altivec context pointer from spare4 to
	 pCoprocCtx.
29mar01,pcs  Implement code review suggestions.
*/

#ifndef __INCaltivecPpcLibh
#define __INCaltivecPpcLibh

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VRSAVE_REG                      256  /* VRSAVE Register */

/* number of floating-point data registers */

#define	ALTIVEC_NUM_REGS	32

#ifndef	_ASMLANGUAGE

typedef UINT32 VEC_REG[4];              /* 128 bit vector register */

typedef struct altivecContext
    {
    VEC_REG  vrfile[ALTIVEC_NUM_REGS];  /* VRFILE: 32 Vector Registers */
    UINT32   vscr[4];                   /* VSCR: vec status and control reg */
    UINT32   vrsave;                    /* VRSAVE: SPR 256 */
    UINT32   pad1;                      /* pad to 16 byte boundary.    */ 
    UINT32   pad2;  
    UINT32   pad3;  
    } ALTIVEC_CONTEXT;

#define ALTIVECREG_SET ALTIVEC_CONTEXT

#define ALTIVEC_CONTEXT_GET(pTcb)       (ALTIVEC_CONTEXT *)(pTcb->pCoprocCtx)
#define ALTIVEC_CONTEXT_SET(pTcb,X)     (pTcb->pCoprocCtx = (ULONG)(X))

/* variable declarations */
extern REG_INDEX altivecRegName[];		/* altivec data register table */
extern REG_INDEX altivecCtlRegName[];	/* altivec control register table */

extern WIND_TCB *pAltivecTaskIdPrevious;	/* task id for deferred exceptions */
extern FUNCPTR	 altivecCreateHookRtn;	/* arch dependent create hook routine */
extern FUNCPTR	 altivecDisplayHookRtn;	/* arch dependent display routine */

/* function declarations */

IMPORT void	altivecArchInit (void);
IMPORT void	altivecArchTaskCreateInit (ALTIVEC_CONTEXT *pAltivecContext);
IMPORT void	altivecSetNonJava (void);

#endif	/* _ASMLANGUAGE */

/* define offsets in ALTIVEC_CONTEXT structure */

#define	AVX		0x0
#define AVX_OFFSET(n)	(AVX + (n)*16)
#define VSCR_OFFSET     (AVX + (ALTIVEC_NUM_REGS)*16)   /* offset == 0x200 */
#define VRSAVE_OFFSET   (VSCR_OFFSET + 16)              /* offset == 0x210 */
#define AVCONTEXT_SIZE	16*(ALTIVEC_NUM_REGS + 2)

/* VSCR definitions */
#define VSCR_CONFIG_WORD	3		/* VSCR word with below bits */
#define VSCR_NJ			0x00010000	/* Non-Java mode */
#define VSCR_SAT		0x00000001	/* Vector Saturation */

#ifdef __cplusplus
}
#endif

#endif /* __INCaltivecPpcLibh */
