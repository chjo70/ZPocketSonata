/* spePpcLib.h - PowerPC E500 sipgnal processing engine support library 
 *               header 
 */

/* Copyright 1984-2001 Wind River Systems, Inc. */
/*
modification history
--------------------
01b,03oct02,dtr  Removing _PPC_MSR_SPE from here adding to ppc85xx.h.
01a,02sep02,dtr  Created.
*/

#ifndef __INCspePpcLibh
#define __INCspePpcLibh

#ifdef __cplusplus
extern "C" {
#endif


#define SPE_OFFSET(x) (4*x)
#define ACC_SIZE  2     /* UINT32 */   
#define SPE_NUM_REGS 32

#ifndef	_ASMLANGUAGE

/* This structure should be aligned to the size of a cache block */ 
typedef struct		/* SPE_REG_SET */
    {
    UINT32 gpr[SPE_NUM_REGS];	/* general pourpose registers */
    UINT32 acc[ACC_SIZE];
    } SPE_CONTEXT;

#define SPEREG_SET SPE_CONTEXT

extern void speSave (SPE_CONTEXT *spePtr);
extern void speRestore (SPE_CONTEXT *spePtr);


#define SPE_CONTEXT_GET(pTcb)       (SPE_CONTEXT *)(pTcb->pCoprocCtx)
#define SPE_CONTEXT_SET(pTcb,X)     (pTcb->pCoprocCtx=(int)(X))

/* variable declarations */
#if 0
extern REG_INDEX speRegName[];		/* spe data register table */
extern REG_INDEX speCtlRegName[];	/* spe control register table */
#endif

extern WIND_TCB *pSpeTaskIdPrevious;	/* task id for deferred exceptions */
extern FUNCPTR	 speCreateHookRtn;	/* arch dependent create hook routine */
extern FUNCPTR	 speDisplayHookRtn;	/* arch dependent display routine */

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

IMPORT void	speArchInit (void);
IMPORT void	speArchTaskCreateInit (SPE_CONTEXT *pFpContext);

#else	/* __STDC__ */

IMPORT void	speArchInit ();
IMPORT void	speArchTaskCreateInit ();

#endif	/* __STDC__ */


#endif	/* _ASMLANGUAGE */

/* define offsets in SPE_CONTEXT structure */



#ifdef __cplusplus
}
#endif

#endif  /* INCspePpcLibh */
