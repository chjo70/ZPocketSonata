/* usrShell.c - shell module */

/*
 * Copyright (c) 2003-2005, 2009-2011, 2013-2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
26may16,ghl  Fix bootloader build fails with ping. (F6988)
25jun14,pad  Introduced console login daemon (US40199).
21may14,rlp  Fixed build warning (V7COR-1145).
29apr14,rlp  Fixed IPNET dependency (V7COR-1073).
22apr14,rlp  Fixed static analysis issue.
25feb14,rlp  Replaced SHELL_SECURE parameter by INCLUDE_SHELL_SECURITY
29aug13,cww  Fix init ordering issue with INCLUDE_BANNER (WIND00431749)
19aug13,cww  updated to use new banner infrastructure
18mar11,jmp  renamed SHELL_SP_* parameters to SHELL_SPAWNED_TASK_*.
16mar11,jmp  Added support for SHELL_SP_STACK_SIZE, SHELL_SP_PRIORITY,
             SHELL_SP_OPTIONS parameters (CQ:WIND00235451).
09jul10,v_r  Added warning when SHELL_SECURE is set without
             INCLUDE_SECURITY (req CQ:WIND00190686).
08sep09,v_r  Added shell session limitation system (def CQ:WIND00155318,
             merged from 6.5 sustaining).
16jun09,jmp  Completed 64-bit support.
06mar09,v_r  LP64 early mods: fixed some build warnings. Commented out
             shellRemoteConfigStr as it is not included in the 64 bits build
             yet.
06sep05,bpn  Added new component parameters to configure the shell tasks
             spawning options (SPR#106622).
04jun04,bpn  Fixed SPR#97937: the compatible mode was broken. Fixed also the
             interaction of the compatible mode with the shell security.
26apr04,bpn  For secure shell on the console, spawn a task to launch the
             shell, and so do not prevent initialization of other components.
13nov03,bpn  Use configuration variables.
13oct03,bpn  Removed build warning.
31mar03,bpn  Changed the initialisation of the configlet. Added unique
             shell session compatibility.
14feb03,bpn  Written.
*/

/*
DESCRIPTION
This file is used to intialize the VxWorks kernel shell component.
This file is included by usrConfig.c.

NOMANUAL
*/

/* Includes */

#include <private/shellLibP.h>
#include <private/usrLibP.h>
#include <shellConfigLib.h>

#ifdef INCLUDE_SHELL_BANNER
#include <usrLib.h>
#endif

#ifdef INCLUDE_IPWRAP_PING
#include <pingLib.h>

extern Vxcoreip_shellTaskGet_ptr     vxcoreip_shellTaskGet_ptr;
extern Vxcoreip_shellFromTaskGet_ptr vxcoreip_shellFromTaskGet_ptr;
#endif

/* Some configuration sanity testing to avoid running into trouble at runtime */

#if defined(INCLUDE_SHELL_SECURITY) 
#ifndef _WRS_CONFIG_USER_IDENTIFICATION_INHERITANCE
#error "When including INCLUDE_SHELL_SECURITY the USER_IDENTIFICATION_INHERITANCE VSB option of the CORE_KERNEL layer must be enabled. Aborting."
#endif
#endif

/* externs */

#ifdef INCLUDE_SHELL_BANNER
extern void (*_func_bannerLogo)(void);
#endif

#if defined(_WRS_CONFIG_USER_MANAGEMENT)
IMPORT MSG_Q_ID msgQShellSessionLogoutEvent;
IMPORT int (* _func_consoleLogin) (SHELL_CTX * pShellCtx);
#endif  /* _WRS_CONFIG_USER_MANAGEMENT */

/* Local declarations */

#if (SHELL_START_AT_BOOT == TRUE) && defined(INCLUDE_SHELL_SECURITY)
static int usrShellConsoleLogin (int fdIn, int fdOut, int fdErr);
#endif
static void usrShellConfigure (void);

#ifdef	INCLUDE_SHELL_SECURITY
static void usrLoginDaemon (void);
#endif

/* 
 * Handle incompatible components. We cannot break the message lines or that
 * break will be reproduced on the warning line. Using a #define for the message
 * is not possible either as it does not work through file inclusion (as does
 * the project facility).
 */

#if (SHELL_COMPATIBLE == TRUE) && (SHELL_MAX_SESSIONS != -1)
    #warning "Compatible mode detected. Shell session limit system disabled."
    #undef SHELL_MAX_SESSIONS
    #define SHELL_MAX_SESSIONS -1
#endif /* (SHELL_COMPATIBLE == TRUE) && (SHELL_MAX_SESSIONS != -1) */


#if (SHELL_COMPATIBLE == TRUE) && defined(INCLUDE_SHELL_SECURITY)
    #warning "Compatible mode detected. Secure console shell disabled."
    #undef INCLUDE_SHELL_SECURITY
#endif /* (SHELL_COMPATIBLE == TRUE) && defined(INCLUDE_SHELL_SECURITY) */

#if (SHELL_COMPATIBLE == TRUE) && (SHELL_START_AT_BOOT == FALSE)
    #warning "Compatible mode detected. Forcing shell startup to boot time."
    #undef SHELL_START_AT_BOOT
    #define SHELL_START_AT_BOOT TRUE
#endif /* (SHELL_COMPATIBLE == TRUE) && (SHELL_START_AT_BOOT == FALSE) */

/* 
 * Handle backward compatibility for the SHELL_MAX_SESSIONS parameter. This
 * avoids build breakage for existing projects which did not have the parameter
 * defined.
 */

#ifndef SHELL_MAX_SESSIONS
#define SHELL_MAX_SESSIONS  -1
#endif

/******************************************************************************
*
* usrShell - initialize the kernel shell
*
* This routine launches an initial shell session task attached to the console
* if SHELL_START_AT_BOOT is defined to TRUE. If SHELL_COMPATIBLE is defined to
* TRUE, the shell session is launched with a VxWorks 5.5 compatible 
* behavior.
*
* When the shell's security (INCLUDE_SHELL_SECURITY) is activated the shell
* session task is started, after the successful user authentication, by a login
* session task, itself spawned by the login daemon.
*
* \NOMANUAL
*/

void usrShell ()
    {
#if SHELL_START_AT_BOOT == TRUE
    int		    fdIn;
    int		    fdOut;
    int		    fdErr;
#ifdef	INCLUDE_SHELL_SECURITY
    TASK_ID	    taskId;
#endif
#endif

#ifdef INCLUDE_IPWRAP_PING
	vxcoreip_shellTaskGet_ptr = (Vxcoreip_shellTaskGet_ptr)shellTaskGet;
	vxcoreip_shellFromTaskGet_ptr = (Vxcoreip_shellFromTaskGet_ptr)shellFromTaskGet;
#endif

    usrShellConfigure ();

#if SHELL_START_AT_BOOT == TRUE
#if SHELL_COMPATIBLE == TRUE
    /* 
     * WRS_XXX bpn - Using the standard I/O (STD_IN, STD_OUT, STD_ERR), this
     * "attaches" the target shell to the console. Any changes of the 
     * global standard I/O modified also the I/O of the shell task.
     */

    fdIn = STD_IN;
    fdOut = STD_OUT;
    fdErr = STD_ERR;
#else
    /* 
     * WRS_XXX bpn - Using the file descriptor behind the standard I/O, this
     * "detach" the target shell on the console from changes of the 
     * global standard I/O.
     */

    
    fdIn = ioGlobalStdGet (STD_IN);
    fdOut = ioGlobalStdGet (STD_OUT);
    fdErr = ioGlobalStdGet (STD_ERR);
#endif /* SHELL_COMPATIBLE == TRUE */

#ifdef INCLUDE_SHELL_BANNER
    /* Replace the banner logo */

    _func_bannerLogo = printLogo;
#endif

#ifdef	INCLUDE_SHELL_SECURITY
    /*
     * Spawn the shell login session and the login daemon. The shell login
     * session task will, after successful user authentication, acquire the
     * logged-in user's identity and spawn the console shell session task. The
     * login daemon stays owned by root and will spawn a new shell login
     * session task each time the current console shell session task exits.
     */

    taskId = taskSpawn ("tLoginTask", shellTaskDefaultPriorityGet (),
			shellTaskDefaultOptionsGet(),
			shellTaskDefaultStackSizeGet (),
			usrShellConsoleLogin,
			fdIn, fdOut, fdErr, 0, 0 ,0 ,0, 0, 0, 0);

    if (taskId == TASK_ID_ERROR)
        printErr ("Error: unable to launch the shell login session for "
                  "authentication via the console.\n");

    taskId = taskSpawn ("tLogind", shellTaskDefaultPriorityGet (),
                        shellTaskDefaultOptionsGet (), 0x1000,
                        (FUNCPTR) usrLoginDaemon,
                        0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L);

    if (taskId == TASK_ID_ERROR)
        printErr ("Error: unable to launch the login daemon.\n");
#else /* !INCLUDE_SHELL_SECURITY */
    (void) shellGenericInit (SHELL_FIRST_CONFIG, (size_t) SHELL_STACK_SIZE,
			     NULL, NULL, TRUE, FALSE, fdIn, fdOut, fdErr);
#endif	/* INCLUDE_SHELL_SECURITY */
#endif	/* SHELL_START_AT_BOOT == TRUE */
    }
    
/******************************************************************************
*
* usrShellConfigure - configure the kernel shell parameters
*
* This routine initializes the kernel shell parameters.
*
* \NOMANUAL
*/
static void usrShellConfigure (void)
    {
#ifdef  _WRS_CONFIG_IPNET_COREIP
    IMPORT char *   shellRemoteConfigStr;
#endif
    static BOOL	    isShellConfigured = FALSE;

    if (isShellConfigured)
	return;

#if SHELL_COMPATIBLE == TRUE
    /* Remove private env feature of the kernel shell task */

    shellTaskDefaultOptionsSet ((int)(SHELL_TASK_OPTIONS & ~VX_PRIVATE_ENV));
#else
    shellTaskDefaultOptionsSet ((int)SHELL_TASK_OPTIONS);
#endif	/* SHELL_COMPATIBLE == TRUE */

    shellTaskDefaultStackSizeSet ((size_t) SHELL_STACK_SIZE);
    shellTaskDefaultPrioritySet (SHELL_TASK_PRIORITY);
    shellTaskDefaultBaseNameSet (SHELL_TASK_NAME_BASE);
    shellMaxSessionsSet (SHELL_MAX_SESSIONS);

    shellConfigDefaultSet (SHELL_DEFAULT_CONFIG);
    shellCompatibleSet (SHELL_COMPATIBLE);

#ifdef  _WRS_CONFIG_IPNET_COREIP
    /* Set the remote configuration string for a later use */

    shellRemoteConfigStr = SHELL_REMOTE_CONFIG;
#endif

    /* Initialize the user interface library */

    usrLibInit (SHELL_SPAWNED_TASK_STACK_SIZE, SHELL_SPAWNED_TASK_PRIORITY,
		SHELL_SPAWNED_TASK_OPTIONS);

    isShellConfigured = TRUE;
    }

#if (SHELL_START_AT_BOOT == TRUE) && defined(INCLUDE_SHELL_SECURITY)
/******************************************************************************
*
* usrShellConsoleLogin - login to the console
*
* This routine is executed to ask the user to logs into a shell session
* attached to the console.
*
* RETURNS: 0
*
* ERRNO: N/A
*
* \NOMANUAL
*/

static int usrShellConsoleLogin
    (
    int	fdIn,
    int	fdOut,
    int	fdErr
    )
    {
    /* Wait until a valid session is launched */

    while (shellGenericInit (SHELL_FIRST_CONFIG, (size_t) SHELL_STACK_SIZE, 
			     NULL, NULL, TRUE, TRUE, fdIn, fdOut, 
			     fdErr) != OK)
	taskDelay (sysClkRateGet () / 4);

    return 0;
    }
#endif

#ifdef INCLUDE_SHELL_BANNER
/******************************************************************************
*
* usrShellBannerInit - register the shell banner with usrBanner
*
* This routine replaces the logo that is printed with the VxWorks banner
*
* RETURNS : N/A
*
* NOMANUAL
*/

void usrShellBannerInit (void)
    {
    _func_bannerLogo = printLogo;
    }
#endif

#ifdef	INCLUDE_SHELL_SECURITY
/******************************************************************************
*
* usrLoginDaemon - console login daemon
*
* This routine is spawned as a task after the initial shell login session task
* is created. It will then do nothing but wait for a "logout" event sent by
* the console shell session task when it exits. When this event is received
* the console login daemon immediately re-spawn a shell login session task.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

static void usrLoginDaemon (void)
    {
    SHELL_CTX *	pShellCtx;
    int (* funcLogin) (SHELL_CTX * pShellCtx);

    FOREVER
	{
	pShellCtx = NULL;

	/* receive the pointer points to the shell ctx from logged out shell */

	if (msgQReceive (msgQShellSessionLogoutEvent, (char *)&pShellCtx,
                         sizeof (pShellCtx), WAIT_FOREVER) == ERROR)
            {
            printErr ("tLogind: unable to receive logout event, Exiting...\n");
	    break;
            }

	if (pShellCtx == NULL)
	    {
	    /*
	     * If the reception fails, that should never happen, this task
	     * cannot do much but just continue.
	     */

            printErr ("tLogind: unexpected null shell context session info\n");
	    continue;
	    }

	if (pShellCtx->taskName == NULL)
	    {
	    /*
	     * The shell context is a dummy one if it is passed by su command.
	     */

	    /*funcLogin = usrSuLogin;*/
            printErr ("tLogind: unexpected null login session task name\n");
            continue;
	    }
	else
	    {
	    funcLogin = _func_consoleLogin;
	    }

	if (funcLogin != NULL)
	    {
	    char taskName [VX_TASK_NAME_LENGTH];

	    /* create a login session task name */

	    snprintf (taskName, sizeof (taskName), "tLogin" "%p",
		      pShellCtx->taskId);

	    /* login and start new shell session */

	    if (taskSpawn (taskName, shellTaskDefaultPriorityGet(),
			   shellTaskDefaultOptionsGet(),
			   shellTaskDefaultStackSizeGet(),
			   funcLogin, (_Vx_usr_arg_t)pShellCtx,
			   0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L) == TASK_ID_ERROR)
		printErr ("tLogind: unable to launch a secure shell login "
                          "session on the console.\n");
	    }
	}
    }
#endif /* INCLUDE_SHELL_SECURITY */
