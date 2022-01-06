/* shellConfigLib.h - header for the shell configuration management module */

/* Copyright 2003-2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01f,03aug04,bpn  Simplified APIs.
01c,15apr04,bpn  Added shellConfigGet2().
01b,07apr04,bpn  Added shellConfigValueGet2() prototype.
01a,29oct03,bpn  Written.
*/

#ifndef __INCshellConfigLibh
#define __INCshellConfigLibh

/* Includes */

#ifdef HOST
#include <host.h>
#endif

#include <shellLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

/* Possible errnos */

/* Structures */

/* Function declarations */

extern STATUS	shellConfigDefaultSet (const char * config);
extern STATUS	shellConfigSet (SHELL_ID shellId, const char * config);
extern char *	shellConfigDefaultGet (void);
extern char *	shellConfigGet (SHELL_ID shellId);

extern STATUS	shellConfigDefaultValueSet (const char * name,
					    const char * value);
extern STATUS	shellConfigValueSet (SHELL_ID shellId, const char * name,
				     const char * value);

extern const char *	shellConfigDefaultValueGet (const char * name);
extern const char *	shellConfigValueGet (SHELL_ID shellId,
					     const char * name);

extern void	shellConfigDefaultValueUnset (const char * name);
extern STATUS	shellConfigValueUnset (SHELL_ID shellId, const char * name);

#ifdef HOST
extern char **	shellConfigListGet (void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCshellConfigLibh */
