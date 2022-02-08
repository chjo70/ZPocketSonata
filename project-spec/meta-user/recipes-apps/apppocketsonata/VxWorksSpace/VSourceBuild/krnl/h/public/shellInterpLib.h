/* shellInterpLib.h - header file for the interpreters management module */

/*
 * Copyright (c) 2003-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01o,29apr10,pad  Moved extern C statement after include statements.
01n,19jan10,pad  Removed usage of _WRS_KEEP_USING_FUNCPTR.
01m,27jul09,sdt  Host only - added cmdAbortHook field to interpreter structure
01m,27feb09,v_r  Fixed issues brought up by the LP64 review process.
01l,28feb08,sdt  Added ability to tune last command repeat (req CQ:WIND00065497)
		 Whether line should be added to history (req CQ:WIND00116229)
01k,11jul07,v_r  Removed useless history field of interpreter structure (req
                 CQ:WIND00005098).
01j,04aug06,dbt  Moved shellInterpEvaluate() from shellLibP.h
		 (Defect CQ:WIND00060713).
01i,08feb05,bpn  Added dfltPrompt field to interpreter structure (SPR#106114).
01h,28jul04,bpn  Added shellInterpCtxGet() prototypes.
01g,26feb04,bpn  Added ctxRestart field to SHELL_INTERP.
01f,10feb04,lcs  Add host routine to handle DFW asynchronous events.
01e,06nov03,bpn  Added shellInterpDefaultNameGet() and shellInterpNameGet()
                 prototypes.
01d,24oct03,bpn  Added completion field to SHELL_INTERP structure.
01c,23sep03,bpn  Added prototypes of the initialization functions of the
                 C and command interpreters.
01b,24jun03,bpn  Added history list to each interpreter.
01a,17feb03,bpn  Written.
*/

#ifndef __INCshellInterpLibh
#define __INCshellInterpLibh

/* Includes */

#include <ledLib.h>
#include <lstLib.h>

#include <shellLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

/* The interpreter data structure */

typedef struct shell_interp
    {
    NODE	    node;
    const char *    name;	/* interpreter name */
    FUNCPTR	    ctxInit;	/* interpreter ctx init routine */
    VOIDFUNCPTR	    ctxRestart;	/* interpreter ctx restart routine */
    FUNCPTR	    ctxFinalize;/* interpreter ctx terminate routine */
    FUNCPTR	    parser;	/* interpreter parser routine */
    FUNCPTR	    evaluate;	/* interpreter evaluation routine */
    FUNCPTR	    completion;	/* interpreter input completion routine */
    const char *    prompt;	/* original prompt of the interpreter */
    /* BELOW IS Wind River RESERVED INFO */
    char *	    dfltPrompt;	/* default interpreter prompt (malloc-ed) */
#ifdef HOST
    FUNCPTR	    asyncEvtDispatch;	/* called when a DFW msg is recvd */
    FUNCPTR	    cmdRepeatHook;	/* says whether last cmd is replayed */
    FUNCPTR	    cmdAbortHook;	/* called when CTRL+C is received */
#endif /* HOST */
    } SHELL_INTERP;

typedef struct shell_interp_ctx
    {
    NODE	    node;
    SHELL_INTERP *  pInterp;		/* interpreter used */
    void *	    pInterpParam;	/* internal data of the interpreter */
    char *	    currentPrompt;	/* prompt to use (malloc()-ed) */
    LED_HIST	    history;		/* commands history list */
    void *	    reserved;		/* FOR INTERNAL USE ONLY */
#ifdef HOST
    BOOL	    cmdToHistAdd;	/* add command to history ? */
#endif /* HOST */
    } SHELL_INTERP_CTX;

/* Function declarations */

extern STATUS	shellInterpRegister (STATUS (* interpInitRtn)
						(SHELL_INTERP * pInterp));
extern const char *	shellInterpDefaultNameGet	(void);
extern const char *	shellInterpNameGet	(SHELL_ID shellId);
extern SHELL_INTERP_CTX * shellInterpCtxGet	(SHELL_ID shellId);
extern STATUS		shellInterpEvaluate	(char * arg,
						 const char * interpreterName,
						 SHELL_EVAL_VALUE * pValue);
extern SHELL_INTERP *	shellInterpByNameFind	(const char * interpName);
extern STATUS		shellInterpCInit	(SHELL_INTERP * pInterp);
extern STATUS		shellInterpCmdInit	(SHELL_INTERP * pInterp);

#ifdef __cplusplus
}
#endif

#endif /* __INCshellInterpLibh */
