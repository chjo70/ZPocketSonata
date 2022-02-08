/* shellInterpCmdLib.h -  header file of the command interpreter library */

/*
 * Copyright (c) 2003-2004, 2008-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01j,02mar09,v_r  Moved private routines into private header. 
01i,26feb08,v_r  Moved SHELL_OPTION from shellInternalLibP.h as it is mandatory
		 for customer-defined commands.
01h,09sep04,bpn  Updated some APIs.
01g,28jul04,bpn  Moved prototypes to shellInterpCmdLibP.h.
01f,11may04,bpn  Added shellCmdPreParse() prototype.
01e,28jan04,bpn  Added shellCmdTaskIdConvert(), shellCmdInfoGet() and
                 shellCmdLineConsume() prototypes.
01d,28jan04,bpn  Added shellCmdSymTabIdGet() prototype. Removed shellCmdInit().
01c,09oct03,bpn  Added definitions for the alias related routines.
01b,22aug03,bpn  Moved definitions to shellInternalLib.h and shellLib.h.
01a,22jul03,bpn  Written.
*/

#ifndef __INCshellInterpCmdLibh
#define __INCshellInterpCmdLibh

#ifndef HOST
#include <vwModNum.h>
#include <symLib.h>
#else
#include <host.h>

#ifndef SYMTAB_ID
#define	SYMTAB_ID	int	/* WRS_XXX bpn - to change */
#endif
#endif

#include <shellLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

#ifdef HOST
#define M_shellInterpCmdLib	(174 << 16)
#endif

#define SHELL_INTERP_CMD_NAME "Cmd"

/* Size of the PIPE buffer used by the 'more' command */

#define SHELL_PIPE_BUFFER	256

#define S_shellInterpCmdLib_UNKNOWN_CMD		(M_shellInterpCmdLib | 1)
#define S_shellInterpCmdLib_UNKNOWN_TOPIC	(M_shellInterpCmdLib | 2)
#define S_shellInterpCmdLib_WRONG_CMD		(M_shellInterpCmdLib | 3)

/* Typedefs */

typedef struct shell_cmd	/* a command description */
    {
    const char *    name;	/* complete command name */
    FUNCPTR	    func;	/* command routine */
    const char *    opt;	/* options string; may be NULL */
    const char *    shortDesc;  /* short description; may be NULL */
    const char *    fullDesc;   /* complete description; may be NULL */
    const char *    synopsis;   /* synopsis; may be NULL */
    } SHELL_CMD;

typedef struct shell_cmd_alias	/* a command alias */
    {
    const char *	alias;	    /* alias name */
    const char *	string;	    /* replacement string */
    } SHELL_CMD_ALIAS;

typedef struct shell_option     /* an option structure */
    {
    char *      string;         /* additional argument */
    BOOL        isSet;          /* TRUE if the option is defined */
    BOOL        isLast;         /* TRUE if it is the last array element */
    } SHELL_OPTION;

/* Functions */

extern STATUS	shellCmdAdd (const char * topic, const SHELL_CMD * pShellCmd);
extern STATUS	shellCmdArrayAdd (const char * topic,
				  const SHELL_CMD shellCmdArray[]);
extern STATUS	shellCmdTopicAdd (const char * topic, const char * desc);
extern STATUS	shellCmdAliasAdd (const char * aliasName, 
				  const char * string,
				  BOOL allocate);
extern STATUS	shellCmdAliasArrayAdd (const SHELL_CMD_ALIAS aliasArray[],
				       BOOL allocate);
extern STATUS	shellCmdAliasDelete (const char * alias);
extern STATUS	shellCmdPreParseAdd (const char * name,
				     char * (*preParseRtn) (char * line));

extern STATUS	shellCmdExec (const char * name, const char * args);

extern SYMTAB_ID	shellCmdSymTabIdGet (SHELL_ID shellId);

extern STATUS	shellCmdMemRegister (void * pMem, BOOL shellPool);
extern STATUS	shellCmdMemUnregister (void * pMem);

#ifdef __cplusplus
}
#endif

#endif /* __INCshellInterpCmdLibh */
