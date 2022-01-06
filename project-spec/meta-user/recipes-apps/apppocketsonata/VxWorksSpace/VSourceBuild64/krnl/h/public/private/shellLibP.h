/* shellLibP.h - private header file for the kernel shell module */

/*
 * Copyright (c) 2003-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * license agreement.
 */

/*
modification history
--------------------
09sep14,vhe  Fixed checked-return warnings (US44776)
28mar14,pad  Added 'userLogin' parameter to shellParserControl() and
             shellGenericCreate().
12feb14,jsh  Fixed IPNET dependency
28jan14,pad  Added support for the optional VxWorks user management facility
             (US19799)
13jan14,rlp  Fixed VXDBG build dependencies.
24may13,rlp  Added VxDBG public header file
21nov12,v_r  Added boolean marking shell startup (CQID Fix WIND00389134).
27jun12,rlp  CQ:WIND00357688. Added shellActivate() and shellGenericCreate()
                 prototypes.
14jan11,sdt  Update shellHostInitialize prototype
15dec10,v_r  Moved SHELL_DFLT_TID_KEY key from shellLib.c
23sep10,v_r  shellMaxSessionsSet() now returns a STATUS.
             Added SHELL_CFG_LOGIN_RTN_BYPASS shell session parameter.
             Removed shellSecureInit ().
13jul10,v_r  No more fiddling with user IDs within the shell anymore (req
             CQ:WIND00190686).
12may10,rlp  Added VxDBG client descriptor definition.
29apr10,pad  Moved extern C statement after include statements.
04feb10,v_r  Do not include vxDbg header on the host.
09nov09,jmp  Fixed merge failure.
08sep09,v_r  Added shellMaxSessionsSet() prototype (def CQ:WIND00155318,
             merged from 6.5 sustaining).
01jul09,jmp  Moved shell function pointers from funcBindP.h.
29may09,dlk  The sessionId passed to shellParserControl should be
             capable of holding a pointer in either ILP32 or LP64.
14may09,jmp  Adapted for 64-bit support
26feb09,v_r  Fixed issues brought up by the LP64 review process.
             Moved private routines from shellLib.h
30jan08,v_r  Do not fiddle with path handling in the shell contexts
             anymore (CQ:WIND00107329).
04apr07,v_r  Added shellLibInit prototype (req CQ:WIND00045277).
23feb07,v_r  Implemented shell output locking (req CQ:WIND00045277).
19feb07,v_r  Added semaphore-reclamation hooks routine and shell context
             list locking APIs for SMP (req CQ:WIND00045277).
04aug06,dbt  Moved shellInterpEvaluate() to shellInterpLib.h
             (CQ:WIND00060713 ).
23nov05,bpn  Added isLocked field (SPR#114137).
14feb05,bpn  Moved shellPromptFormatSet() prototype to shellPromptLib.h
01feb05,bpn  Added shellPromptFormatSet() prototype.
10jan05,bpn  Removed dependencies with dbgLib.o.
23sep04,bpn  Updated include files.
28jul04,bpn  Added APIs from shellLib.h.
25may04,bpn  Added SHELL_LKUP_PG_KEY string.
11may04,bpn  Added fgndShellId field to SHELL_CTX structure.
15apr04,bpn  Added isBackground field to SHELL_CTX structure.
07apr04,bpn  Export shellConsoleTaskId value.
26mar04,bpn  Added errnoValue field to SHELL_CTX structure.
28jan04,bpn  Added several fields to SHELL_CTX structure to fix I/O
             redirection bugs.
14jan04,bpn  Added inputLine field to SHELL_CTX structure to fix memory
             leaks.
28oct03,bpn  Moved SHELL_USER_DATA structure to shellDataLibP.h. Removed
             shellLedCompletion() prototype (local function now).
24oct03,bpn  Added shellLedCompletion() prototype.
22sep03,bpn  Added shellInterpEvaluate() prototype.
25jun03,bpn  Removed shellHistSize field from SHELL_CTX structure.
19may03,bpn  Add the user data structure definition.
17apr03,lcs  Add routines to configure shell environment.
08apr03,bpn  Added fields to the shell_ctx structure to detect a shell task
             restart and to avoid saving user/passwd several times.
12mar03,lcs  Added support for host shell.
10mar03,bpn  Added interpreter switch mechanism. Changed SHELL_CONTEXT
             structure name to SHELL_CTX.
20feb03,bpn  Written.
*/

#ifndef __INCshellLibPh
#define __INCshellLibPh

/* Includes */

#include <ioLib.h>
#ifdef _WRS_CONFIG_IPNET_COREIP
#include <remLib.h>
#endif /* _WRS_CONFIG_IPNET_COREIP */
#ifdef _WRS_CONFIG_VXDBG
#include <private/vxdbgLibP.h>
#endif	/* _WRS_CONFIG_VXDBG */

#include <ledLib.h>
#include <lstLib.h>

#include <shellInterpLib.h>
#include <shellLib.h>

#ifdef _WRS_CONFIG_USER_MANAGEMENT
#include <loginLib.h>
#endif

#include <private/shellInternalLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

#define SHELL_LKUP_PG_KEY	    "_WRS_lkupPgSz"
#define SHELL_DFLT_TID_KEY	    "_WRS_dftTask"

#define SHELL_CFG_LOGIN_RTN_BYPASS  "LOGIN_RTN_BYPASS"
#define LOGIN_RTN_BYPASS_SPEC	    (SHELL_CFG_LOGIN_RTN_BYPASS "=on")

/*
 * Ensure mutual exclusion when accessing the shell context list. This is
 * defined for the target only, as there is no need for it on the host now. It
 * can also be used as a debugging aid by adding checks for the return value.
 * Since the semaphore is static, we do not check the return values of the
 * semLib APIs (as a failure here would mean things are very wrong already).
 */

#define SHELL_CONTEXT_LIST_LOCK     (void) shellContextListLock ()
#define SHELL_CONTEXT_LIST_UNLOCK   (void) shellContextListUnlock ()

/* Typedefs */

typedef STATUS	(* SHELL_LOGIN_RTN)	(void * loginParam, UINT32 options,
					 char * pUserName, size_t nameLength,
					 char * pUserPasswd,
					 size_t passwdLength,
					 int fd);
typedef void	(* SHELL_LOGOUT_RTN)	(void * logoutParam);

typedef struct shell_inline_node
    {
    NODE	node;
    char *	inputLine;	/* buffer for the input line */
    } SHELL_INLINE_NODE;

typedef struct shell_ctx_login
    {
    SHELL_LOGIN_RTN	loginFunc;	/* shell login function */
    SHELL_LOGOUT_RTN	logoutFunc;	/* shell logout function */
    void *		loginParam;	/* param. passed to login function */
    void *		logoutParam;	/* param. passed to logout function */
    } SHELL_CTX_LOGIN;

typedef struct shell_ctx_io
    {
    int		    shellStdin;		/* standard stdin */
    int		    shellStdout;	/* standard stdout */
    int		    shellStderr;	/* standard stdout */
    } SHELL_CTX_IO;

typedef struct shell_ctx_values
    {
    const char *    config;		/* configuration string */
    SHELL_CTX_LOGIN login;		/* login stucture */
    SHELL_CTX_IO    io;			/* io structure */
    BOOL	    isInteractive;	/* interactive or script? */
    } SHELL_CTX_VALUES;

typedef struct shell_ctx_compat
    {
    SHELL_CTX_VALUES	initial;	/* initial values */
    SHELL_CTX_VALUES	current;	/* initial values */
    BOOL		loginAccess;	/* connection with a login? */
    } SHELL_CTX_COMPAT;

typedef void (* SHELL_RES_RELEASE_HOOK) (SHELL_ID shellId, BOOL force);

#ifdef _WRS_CONFIG_USER_MANAGEMENT
typedef struct shell_session_user_info
    {
    char  userName [MAX_LOGIN_NAME_LEN + 1];    /* session user name */
    uid_t userId;                               /* UNUSED - RESERVED */
    gid_t groupId;                              /* UNUSED - RESERVED */
    } SHELL_SESSION_USER_INFO;
#endif /* _WRS_CONFIG_USER_MANAGEMENT */

/* The shell context structure */

typedef struct shell_ctx
    {
    NODE	    node;
    const char *    taskName;		/* shell task name */
    SHELL_INTERP_CTX * pInterpCtx;	/* interpreter parameters */
    SHELL_INTERP *  pInterpSwitch;	/* next interpreter to use */
    SHELL_ID	    bgndShellId;	/* background session Id */
    SHELL_ID	    fgndShellId;	/* foreground session Id */
    LED_ID	    ledId;		/* line editor ID */
    TASK_ID	    taskId;		/* shell task ID */
    SEM_ID	    outputSemId;	/* output locking semaphore */
    LIST            userData;           /* list of the user data */
    LIST	    interpCtxLst;	/* list of interp context */
    LIST	    ioFileDescLst;	/* list of IO file descriptors */
    LIST	    inputLineLst;	/* list input line buffers */
    SHELL_CTX_VALUES	initial;	/* initial values */
    SHELL_CTX_VALUES	current;	/* initial values */
    SHELL_CTX_COMPAT	compatible;	/* for compatibility */
    BOOL	    loginAccess;	/* connection with a login? */
    int		    errnoValue;		/* errno value */
    size_t	    taskStackSize;	/* shell task stack size */
    BOOL	    isAbortReq;		/* abort requested? */
    BOOL	    isRestarted;	/* task restarted? */
    BOOL	    isBackground;	/* background session? */
    BOOL	    isLocked;		/* locked session? */
    BOOL            isShellStartup;     /* before interactive mode is enabled */
#ifdef _WRS_CONFIG_USER_MANAGEMENT
    SHELL_SESSION_USER_INFO shellSessionUser; /* logged-in user's info */
#endif
    } SHELL_CTX;

/* global variables */

extern TASK_ID	shellConsoleTaskId;

#ifdef _WRS_CONFIG_VXDBG
extern VXDBG_CLNT_ID   pDbgClnt;	/* VxDBG client descriptor for shell */
#endif	/* _WRS_CONFIG_VXDBG */

extern STATUS	(* _func_shellDbgStackTrace) (TASK_ID taskId,
					      const char * errorStr);
extern void	(* _func_shellDbgCallPrint) (INSTR * callAdrs, INSTR * funcAdrs,
                                            int nargs, _Vx_usr_arg_t * args,
					    TASK_ID taskId, BOOL isKernelAdrs);
extern void	(* _func_shellExcPrint)	(TASK_ID taskId, const char * fmt, ...);

/* Function Declarations */

extern STATUS	    shellLibInit	(void);
extern STATUS	    shellLogout2	(SHELL_ID shellId,
					 const char * errorStr);
extern STATUS	    shellScriptNoAbort	(void);
extern void	    shellPromptPrint	(SHELL_ID shellId);
extern STATUS       shellActivate (SHELL_ID shellId);
extern SHELL_ID	    shellBackgroundInit	(const char * interpName,
					 const char * evalString);
extern char *	    shellBackgroundRead	(LIST * pMemList, INT32 memFlags);
extern UINT	    shellLineLenGet	(void);
extern STATUS	    shellExec		(SHELL_CTX * pShellCtx);
extern void	    shellExitWrapper	(int code);
extern SHELL_ID     shellGenericCreate  (const char * config, size_t stackSize,
                                         const char * shellName,
                                         char ** pShellName, BOOL interactive,
                                         BOOL loginAccess, char * userLogin,
                                         int fdin, int fdout, int fderr);
extern STATUS	    shellConsoleInit	(const char * config, size_t stackSize,
					 const char * shellName,
					 char ** pShellName);
extern void	    shellContextFinalize (SHELL_CTX * pShellCtx);
extern SHELL_CTX *  shellContextInit	(const char * config, size_t stackSize,
					 const char * shellName,
					 BOOL isForEvaluation,
					 BOOL interactive);
extern void	    shellLoginInstall (SHELL_LOGIN_RTN logRtn, void * logVar);
extern void	    shellLogoutInstall (SHELL_LOGOUT_RTN logRtn, void * logVar);
extern STATUS	    shellLogout (SHELL_ID shellId);

extern STATUS	    shellContextListLock	    (void);
extern STATUS	    shellContextListUnlock	    (void);
extern SHELL_CTX *  shellFromTaskParentContextGet   (TASK_ID taskId);
extern STATUS	    shellResourceReleaseHookAdd	    (SHELL_RES_RELEASE_HOOK hk);
extern STATUS	    shellMaxSessionsSet (INT32 maxSessions);
extern STATUS	    shellParserControl (UINT32 remoteEvent, ULONG sessionId,
					UINT32 slaveFd, VOIDFUNCPTR logoutFunc,
                                        char * userLogin);

extern void     shellCompatibleSet (BOOL isCompatible);
extern void     shellTaskDefaultOptionsSet (int taskOpt);
extern int      shellTaskDefaultOptionsGet (void);
extern void     shellTaskDefaultStackSizeSet (size_t stackSize);
extern size_t	shellTaskDefaultStackSizeGet (void);
extern void     shellTaskDefaultPrioritySet (int priority);
extern int      shellTaskDefaultPriorityGet (void);
extern void     shellTaskDefaultBaseNameSet (const char * taskBaseName);
extern char *   shellTaskDefaultBaseNameGet (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCshellLibPh */
