/* speLib.h - SPE coprocessor support library header */

/* Copyright 1984-1997, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,29apr10,pad  Moved extern C statement after include statements.

*/

#ifndef __INCspeLibh
#define __INCspeLibh

#ifndef _ASMLANGUAGE
#include "taskLib.h"
#endif	/* _ASMLANGUAGE */

#if     CPU_FAMILY==PPC
#include "arch/ppc/spePpcLib.h"

#ifdef __cplusplus
extern "C" {
#endif

#endif  /* CPU_FAMILY==PPC */

/* function declarations */

#ifndef _ASMLANGUAGE

#if defined(__STDC__) || defined(__cplusplus)

extern void 	speInit (void);
extern void	speShowInit (void);
extern void 	speTaskRegsShow (int task);
extern STATUS 	speTaskRegsGet (int task, SPEREG_SET *pSpeRegSet);
extern STATUS 	speTaskRegsSet (int task, SPEREG_SET *pSpeRegSet);
extern STATUS 	speProbe (void);
extern void 	speRestore (SPE_CONTEXT *pSpeContext);
extern void 	speSave (SPE_CONTEXT *pSpeContext);
extern void	speRegsToCtx (SPEREG_SET *pSpeRegSet, SPE_CONTEXT *pSpeContext);
extern void	speCtxToRegs (SPE_CONTEXT *pSpeContext, SPEREG_SET *pSpeRegSet);

#else

extern void 	speInit ();
extern void	speShowInit ();
extern void 	speTaskRegsShow ();
extern STATUS 	speTaskRegsGet ();
extern STATUS 	speTaskRegsSet ();
extern STATUS 	speProbe ();
extern void 	speRestore ();
extern void 	speSave ();
extern void	speRegsToCtx ();
extern void	speCtxToRegs ();

#endif	/* __STDC__ */
#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCspeLibh */
