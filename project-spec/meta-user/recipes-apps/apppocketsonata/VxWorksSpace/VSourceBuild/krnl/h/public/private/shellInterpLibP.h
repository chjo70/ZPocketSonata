/* shellInterpLibP.h - private header file for the interpreters management */

/*
 * Copyright (c) 2003-2005, 2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement.
 */

/*
modification history
--------------------
01i,29apr10,pad  Moved extern C statement after include statements.
01h,22sep09,sdt  Removed shellInterpEventDispatch (moved to host code side)
01g,10jul07,v_r  Cleanup for shell persistent history implementation 
		 (req CQ:WIND00005098).
01f,08feb05,bpn  Added shellInterpPromptDftSet() prototype, changed
                 shellInterpPromptSet() (SPR#106114).
01e,28jul04,bpn  Removed shellInterpNameFromCtxGet() and shellInterpCtxCreate()
                 prototypes.
01d,26feb04,bpn  Added shellInterpRestart() and shellInterpEventDispatch()
                 prototypes.
01c,21jan04,bpn  Added shellInterpDelete() prototype.
01b,25jun03,bpn  Added shellInterpHistorySave() prototype.
01a,17feb03,bpn  Written.
*/

#ifndef __INCshellInterpLibPh
#define __INCshellInterpLibPh

/* Includes */

#include <shellLib.h>
#include <shellInterpLib.h>
#include <private/shellLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Typedefs */

/* Function declarations */

extern SHELL_INTERP_CTX *   shellInterpCtxCreate (const char * interpName, 
						  BOOL isForEvaluation);
extern void	    shellInterpDelete (SHELL_CTX * pShellCtx);
extern const char * shellInterpPromptGet (SHELL_INTERP_CTX * pInterpCtx);
extern STATUS	    shellInterpPromptSet (SHELL_ID shellId,
					  const char * interp,
					  const char * promptFmt);
extern STATUS	    shellInterpPromptDftSet (const char * interp,
					     const char * promptFmt);

extern void	    shellInterpRestart (SHELL_CTX * pShellCtx);
extern STATUS	    shellInterpSet (SHELL_CTX * pShellCtx,
				    const char * interpreterName);
extern STATUS	    shellInterpSwitch (SHELL_CTX * pShellCtx);

#ifdef __cplusplus
}
#endif

#endif /* __INCshellInterpLibPh */
