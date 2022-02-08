/* shellLib.h - header for the kernel shell module */

/* 
 * Copyright (c) 2003-2010,2013, 2016-2017 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
06apr17,ljl  Add security events on login and logout (F8189)
29apr16,ply  add security event handler (F3805)
08oct13,elp  added shellIOStdSet()/shellIOStdGet() CQ:WIND00271256.
29apr10,pad  Moved extern C statement after include statements.
29apr10,rlp  Added SHELL_CFG_BP_SYM_ADDR configuration variable
                 (WIND00204361).
08sep09,v_r  Added new session limit errno (def CQ:WIND00155318).
26feb09,v_r  Fixed issues brought up by the LP64 review process.
		 Moved private routines into private header.
12mar08,v_r  Fixed incorrect defect reference in previous changelog entry.
07feb08,v_r  Removed unused history file configuration variable.
18jul07,v_r  Added SHELL_CFG_HISTORY_FILE configuration variable (req
                 CQ:WIND0005098).
07may07,v_r  Removed SHELL_PRINTF macro now that host and target sides are
		 unified via the shellPrint()/shellPrintErr() routines.
21feb07,lcs  Add SHELL_PRINTF macro.
21nov06,v_r  Implemented req CQ:WIND00068611 (remove obsoleted routines
                 from runtime code).
04aug06,dbt	 Moved some header files needed for public APIs
		 from shellInternalLibP.h (defect CQ:WIND00038942).
02aug06,v_r  Added new errno for defect CQ:WIND00040342 fix ('rtp attach'
                 error message not verbose enough).
08feb05,bpn  Moved shellPromptFmtStrAdd() API to shellPromptLib.h.
18aug04,bpn  Added CPLUS_SYM_MATCH configuration variable.
28jul04,bpn  Added _WRS_DEPRECATED attributes to obsolete routines.
                 Moved APIs to shellLibP.h
12jul04,bpn  Updated shellLogout() API.
28apr04,bpn  Added shellBackgroundInit() and shellBackgroundRead() 
                 prototypes.
26apr04,bpn  Added new configuration variable AUTOLOGOUT.
07apr04,bpn  Added new configuration variables.
26mar04,bpn  Added shellErrnoSet() and shellErrnoGet() prototypes.
26feb04,bpn  Added shellCompatibleCheck (), shellIdVerify() and 
                 shellTaskGet() prototypes.
25nov03,bpn  Added ALL_SHELL_SESSIONS and CURRENT_SHELL_SESSION definitions.
                 Added shellInOutBlock() and shellInOutUnblock() prototypes.
06nov03,bpn  Update shellXxxxInit() API to use configuration string.
                 Added default configuration variable name
28oct03,bpn  Moved shellDataXxx() API to shellDataLib.h.
23sep03,bpn  Moved structures to shellInternalLib.h. Added prototype
                 for shellPromptFmtStrAdd(). Updated API names.
22aug03,bpn  Added S_shellLib_MISSING_ARG, S_shellLib_UNKNOWN_OPT and 
                 S_shellLib_ARG_ERROR.
22jul03,bpn  Added S_shellLib_UNMATCHED_QUOTE.
26jun03,bpn  Added dummy functions shellRestart() and
                 shellIsRemoteConnectedSet() for rlogLib.
19may03,bpn  Moved structure definition to shellInterpLib.h.
17apr03,lcs  Add routines to configure shell environment.
08apr03,bpn  Added shellCompatibleSet() declaration.
20mar03,bpn  Added new errno value and shellLedModeSet() declaration.
14mar03,bpn  Changed long long to INT64.
13mar03,lcs  Integrate host shell host function call support.
12mar03,lcs	 Added support for host shell.
10mar03,bpn  Added interpreter switch mechanism. Changed SHELL_CONTEXT 
		 structure name to SHELL_CTX.
06mar03,bpn  Added definition of shellExitWrapper().
04mar03,bpn  Added definitions of shellInOutSet() and shellInOutGet().
28feb03,bpn  Added shellxxxPrint() routines declarations. Reworked APIs.
20feb03,bpn  Moved the SHELL_CONTEXT structure to shellLibP.h. Changed
		 SHELL_CTX_INTERP structure.
17feb03,bpn  Written.
*/

#ifndef __INCshellLibh
#define __INCshellLibh

/* Includes */
#ifndef HOST
#include <vwModNum.h>
#else
#include <host.h>
#include <shell.h>
#endif

#include <lstLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

/* Configuration variable names */

#define SHELL_CFG_LED_MODE	"LINE_EDIT_MODE"    /* for ledLib */
#define SHELL_CFG_INTERP	"INTERPRETER"	    /* current interpreter */
#define SHELL_CFG_INTERP_EVAL	"INTERPRETER_EVAL"
#define SHELL_CFG_LINE_LENGTH	"LINE_LENGTH"	    /* shell line length */
#define SHELL_CFG_EXC_PRINT	"EXC_PRINT"	    /* exception notification */
#define SHELL_CFG_BP_PRINT	"BP_PRINT"	    /* breakpoint notif. */
#define SHELL_CFG_BP_SYM_ADDR	"BP_SYMBOLIC_ADDR"  /* symbolic addr notif. */
#define SHELL_CFG_AUTOLOGOUT	"AUTOLOGOUT"	    /* inactivity timeout */
#define SHELL_CFG_CPLUS_MATCH	"CPLUS_SYM_MATCH"   /* cplus symbol matching */

/* Special shell session identifier */

#define ALL_SHELL_SESSIONS	((SHELL_ID)-1)
#define CURRENT_SHELL_SESSION	((SHELL_ID)0)

/* Possible errnos */

#define S_shellLib_NO_INTERP		(M_shellLib | 1)
#define S_shellLib_INTERP_EXISTS	(M_shellLib | 2)
#define S_shellLib_NOT_SHELL_TASK	(M_shellLib | 3)
#define S_shellLib_SHELL_TASK_EXISTS	(M_shellLib | 4)
#define S_shellLib_SHELL_TASK_MAX	(M_shellLib | 5)
#define S_shellLib_NO_SHELL_CMD		(M_shellLib | 6)
#define S_shellLib_NO_USER_DATA		(M_shellLib | 7)
#define S_shellLib_NO_LED_MODE		(M_shellLib | 8)
#define S_shellLib_INTERP_INIT_ERROR	(M_shellLib | 9)
#define S_shellLib_TOO_MANY_SESSIONS	(M_shellLib | 10)

#define S_shellLib_LEX_ERROR		(M_shellLib | 20)
#define S_shellLib_SYNTAX_ERROR		(M_shellLib | 21)
#define S_shellLib_INTERNAL_ERROR	(M_shellLib | 22)

#define S_shellLib_UNMATCHED_QUOTE	(M_shellLib | 30)
#define S_shellLib_MISSING_ARG		(M_shellLib | 31)
#define S_shellLib_UNKNOWN_OPT		(M_shellLib | 32)
#define S_shellLib_ARG_ERROR		(M_shellLib | 33)

#define S_shellLib_CONFIG_ERROR		(M_shellLib | 40)
#define S_shellLib_CTX_ALREADY_ATTACHED	(M_shellLib | 41)

#define SEC_EVENT_SHELL_EXECUTE_FAILED      (M_shellLib | 1)
#define SEC_EVENT_SHELL_SET_DISPLAY_FAILED  (M_shellLib | 2)
#define SEC_EVENT_SHELL_LOGOUT              (M_shellLib | 3) 


/* Structures */

typedef struct shell_ctx * SHELL_ID;

typedef enum shell_value_type
    {
    /*
     * The order of the types is important. Don't change it! It is ordered 
     * according to the size of the data type, and according to the number
     * digit that can be coded.
     */
    SHELL_CHAR = 1,
    SHELL_SHORT,
    SHELL_FLOAT,
    SHELL_INT,
    SHELL_LONG,
    SHELL_POINTER,
    SHELL_DOUBLE,
    SHELL_LLONG,
    SHELL_HOST
    } SHELL_VALUE_TYPE;

typedef union shell_type_val	/* different value type formats */
    {
    void *	pointer;	/* for SHELL_POINTER */
    char	charVal;	/* for SHELL_CHAR */
    short	shortVal;	/* for SHELL_SHORT */
    int		intVal;		/* for SHELL_INT */
    long	longVal;	/* for SHELL_LONG */
    INT64	lLongVal;	/* for SHELL_LLONG */
    float	floatVal;	/* for SHELL_FLOAT */
    double	doubleVal;	/* for SHELL_DOUBLE */
    } SHELL_TYPE_VAL;

typedef struct shell_eval_value	/* value for argument evaluation */
    {
    SHELL_TYPE_VAL *	pSymbolVal;
    SHELL_VALUE_TYPE	type;
    SHELL_TYPE_VAL	value;
    BOOL		isUnsigned;
    } SHELL_EVAL_VALUE;

/* Function declarations */

extern BOOL	shellLock (BOOL request);
extern STATUS	shellScriptAbort (void);
extern STATUS	shellHistory (int size);
extern STATUS	shellPromptSet (const char * newPrompt);

/* New shell functions */

extern STATUS	shellGenericInit (const char * config, size_t stackSize,
				  const char * shellName, char ** pShellName,
				  BOOL interactive, BOOL loginAccess,
				  int fdin, int fdout, int fderr);

extern BOOL	shellCompatibleCheck (void);

extern STATUS	shellRestart (SHELL_ID shellId);
extern STATUS	shellAbort (SHELL_ID shellId);
extern TASK_ID	shellTaskIdDefault (SHELL_ID shellId, TASK_ID taskId);
extern void	shellTerminate (SHELL_ID shellId);

extern STATUS	shellIdVerify (SHELL_ID shellId);
extern TASK_ID	shellTaskGet (SHELL_ID shellId);
extern SHELL_ID	shellFromTaskGet (TASK_ID taskId);
extern SHELL_ID	shellFromNameGet (const char * taskName);
extern SHELL_ID	shellFirst (void);
extern SHELL_ID	shellNext (SHELL_ID shellId);

extern void	shellErrnoSet (SHELL_ID shellId, int errNo);
extern int	shellErrnoGet (SHELL_ID shellId);

extern STATUS	shellIOStdSet (SHELL_ID shellId, int inFd, int outFd,
			       int errFd);
extern STATUS	shellIOStdGet (SHELL_ID shellId, int * pInFd, int * pOutfd,
			       int * pErrFd);
#ifdef __cplusplus
}
#endif

#endif /* __INCshellLibh */

