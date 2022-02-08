/* altivecLib.h - ALTIVEC coprocessor support library header */

/* Copyright 1984-1997, 2010, 2016 Wind River Systems, Inc. */

/*
modification history
--------------------
04jan16,xms  fix missing prototype issue. (V7PRO-1966)
20nov14,w_x  LP64 adaptation to support PPC64(F2518)
29apr10,pad  Moved extern C statement after include statements.

*/

#ifndef __INCaltivecLibh
#define __INCaltivecLibh

#ifndef _ASMLANGUAGE
#include "taskLib.h"
#endif	/* _ASMLANGUAGE */

#if     CPU_FAMILY==PPC
#include "arch/ppc/altivecPpcLib.h"

#ifdef __cplusplus
extern "C" {
#endif

#endif  /* CPU_FAMILY==PPC */

/* function declarations */

#ifndef _ASMLANGUAGE

IMPORT int  (* _func_altivecProbeRtn) ();

#if defined(__STDC__) || defined(__cplusplus)

extern void 	altivecInit (void);
extern void	altivecShowInit (void);
extern void 	altivecTaskRegsShow (TASK_ID task);
extern STATUS 	altivecTaskRegsGet (TASK_ID task, ALTIVECREG_SET *pAltivecRegSet);
extern STATUS 	altivecTaskRegsSet (TASK_ID task, ALTIVECREG_SET *pAltivecRegSet);
extern STATUS 	altivecProbe (void);
extern void 	altivecRestore (ALTIVEC_CONTEXT *pAltivecContext);
extern void 	altivecSave (ALTIVEC_CONTEXT *pAltivecContext);
extern void	altivecRegsToCtx (ALTIVECREG_SET *pAltivecRegSet, ALTIVEC_CONTEXT *pAltivecContext);
extern void	altivecCtxToRegs (ALTIVEC_CONTEXT *pAltivecContext, ALTIVECREG_SET *pAltivecRegSet);

#else

extern void 	altivecInit ();
extern void	altivecShowInit ();
extern void 	altivecTaskRegsShow ();
extern STATUS 	altivecTaskRegsGet ();
extern STATUS 	altivecTaskRegsSet ();
extern STATUS 	altivecProbe ();
extern void 	altivecRestore ();
extern void 	altivecSave ();
extern void	altivecRegsToCtx ();
extern void	altivecCtxToRegs ();

#endif	/* __STDC__ */
#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCaltivecLibh */
