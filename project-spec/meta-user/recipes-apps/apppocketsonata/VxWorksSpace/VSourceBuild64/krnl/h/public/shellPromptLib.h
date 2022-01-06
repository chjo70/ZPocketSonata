/* shellPromptLib.h - header for the shell prompt module */

/*
 * Copyright (c) 2003-2005, 2007-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01e,02feb11,jmp  Added shellLib.h inclusion for SHELL_ID definition
		 (CQ:WIND00247209).
01d,29apr10,pad  Moved extern C statement after include statements.
01c,19jan10,pad  Removed usage of _WRS_KEEP_USING_FUNCPTR.
01b,25feb09,v_r  Fixed issues brought up by the LP64 review process.
01a,08feb05,bpn  Written.
*/

#ifndef __INCshellPromptLibh
#define __INCshellPromptLibh

/* Includes */
#ifdef HOST
#include <host.h>
#include <shell.h>
#else
#include <shellLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

/* Structures */

/* Functions */

extern STATUS	shellPromptFmtStrAdd (char fmt, 
				      void (* fmtRtn) (SHELL_ID shellId), 
				      BOOL force);
extern STATUS	shellPromptFmtSet (SHELL_ID shellId, const char * interp,
				   const char * promptFmt);
extern STATUS	shellPromptFmtDftSet (const char * interp,
				      const char * promptFmt);

#ifdef __cplusplus
}
#endif

#endif /* __INCshellPromptLibh */
