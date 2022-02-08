/* edrDefaultPolicy.c - ED&R default kernel fatal policy handler */

/*
 * Copyright (c) 2014, 2016, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01mar17,cww  added edrSystemFatalPolicyHandler (V7COR-3939)
25may16,pcs  Added code corresponding to INCLUDE_EDR_POLICY_HOOKS usage. Moved
             policy handler support code to edrStub.c
12may16,pfl  addressed compiler warnings (US81418)
12may16,pcs  Fixed build error caused due to the change in prototype of
             coreDumpGenerate(). (V7SP-1392)
18sep14,pcs  Created after splitting the contents of file edrStub.c . The kernel
             default fatal policy handlers are now in this file.
*/

/*
DESCRIPTION

This module is a Component that provides the kernel default fatal error
handling policies. It is pulled in when the Component INCLUDE_EDR_DEFAULT_POLICY
is included. It provides the following 4 fatal error handler routines.
edrKernelFatalPolicyHandler(), edrInterruptFatalPolicyHandler(), 
edrRtpFatalPolicyHandler() and edrInitFatalPolicyHandler(). 

If the user wants to implement their own fatal error handling policy, they can
include the component INCLUDE_EDR_CUSTOM_POLICY. That would result in the above
4 functions to be replaced with a identical set of stub functions in the VIP, in
the file edrCustomPolicy.c. The functions in the file edrUserPolicy.c are empty
stubs and the user can implement their own custom fatal error handling policy.
Note: The customer should make sure that these functions do not return back to
the kernel, since the kernel assumes that these functions do not return and so
does not handle that scenario.
*/

#include <vsbConfig.h>

#include <taskLib.h>
#include <intLib.h>
#include <rtpLib.h>
#include <rebootLib.h>
#include <sysLib.h>
#include <wait.h>
#include <logLib.h>
#include <private/edrLibP.h>
#ifdef _WRS_CONFIG_SHELL
#ifdef	INCLUDE_SHELL
#include <private/shellInOutLibP.h>
#endif	/* INCLUDE_SHELL */
#endif /* _WRS_CONFIG_SHELL */
#include <private/taskLibP.h>	/* for taskStopForce()	  */
#include <private/excLibP.h>	/* for _func_excPanicHook */
#include <private/intLibP.h>	/* intCnt */
#ifdef _WRS_CONFIG_CORE_DUMP
#include <coreDumpLib.h>
#include <private/coreDumpLibP.h>
#endif	/* _WRS_CONFIG_CORE_DUMP */

extern EDR_POLICY_HANDLER_HOOK edrPolicyHandlerHook;

#ifdef  INCLUDE_CORE_DUMP
extern void edrCoreDumpGenerate (void * info, CORE_DUMP_TYPE coreDumpType);
#endif  /* INCLUDE_CORE_DUMP */

#ifdef  INCLUDE_CORE_DUMP_RTP
extern void edrCoreDumpRtpGenerate (void * info);
#endif  /* INCLUDE_CORE_DUMP_RTP */

#if defined(INCLUDE_CORE_DUMP) || defined(INCLUDE_CORE_DUMP_RTP)
extern void edrCoreDumpRtpFaultHandle (void * info);
#endif /* INCLUDE_CORE_DUMP || INCLUDE_CORE_DUMP_RTP */

/* globals */

#ifdef	INCLUDE_EDR_ERRLOG
BOOL edrLibInstalled = FALSE;
#endif

/* locals */

#ifdef  INCLUDE_EDR_SYSDBG_FLAG
# define IS_LAB_FLAG_SET() (edrFlagsGet() & EDR_FLAG_DEBUG)
#else
# define IS_LAB_FLAG_SET() FALSE
#endif

/* define the shell notification command if the logging system is present */

#ifdef INCLUDE_LOGGING
# define SHELL_MSG(msg, id)						   \
		logMsg ((char *)(msg), (_Vx_usr_arg_t)(id), 0, 0, 0, 0, 0)
# define SHELL_SIG_MSG(msg, id, sig)					   \
	      logMsg ((char *)(msg), (_Vx_usr_arg_t)(id), (int)sig, 0, 0, 0, 0)

const char *taskStopMsg =
		"task 0x%lx has had a failure and has been stopped.\n";

const char *rtpDeleteMsg =
		"RTP 0x%lx has had a failure and has been deleted.\n";
const char *rtpSigDeleteMsg =
		"RTP 0x%lx has been deleted due to signal %d.\n";
const char *rtpStopMsg =
		"RTP 0x%lx has had a failure and has been stopped.\n";
const char *rtpSigStopMsg =
		"RTP 0x%lx has been stopped due to signal %d.\n";
#else
# define SHELL_MSG(msg, id)
# define SHELL_SIG_MSG(msg, id, sig)
#endif

/* define the shell printing function if the shell is included */

#if defined(_WRS_CONFIG_SHELL) && defined(INCLUDE_SHELL)
# define SHELL_PRINT(x)	shellPrint x
#else
# define SHELL_PRINT(x)
#endif /* _WRS_CONFIG_SHELL && INCLUDE_SHELL */

/* forward declarations */

/**************************************************************************
*
* edrKernelFatalPolicyHandler - handles fatal errors in kernel tasks
*
* This function is invoked by the exception handler, when kernel
* task-level code takes an exception. Its default policy is to suspend
* the task (in 'deployed' mode), but if the ED&R 'system debug flag'
* is set, in which case the system is considered to be in 'lab' mode,
* it also suspends the task.
*
* RETURNS: n/a
*/

void edrKernelFatalPolicyHandler
    (
    EDR_TASK_INFO *info		/* optional information for kernel fault */
    )
    {
#ifdef	INCLUDE_EDR_SYSDBG_FLAG
    if (IS_LAB_FLAG_SET())
	{
	/* In 'lab' mode, stop the task. */

	if ((info != NULL) && (info->taskId != 0))
	    {
	    SHELL_MSG (taskStopMsg, info->taskId);

	    /* display any text provided by the inject call */

	    if (info->msg != NULL)
		SHELL_MSG ("%s\n", info->msg);
	    
#ifdef	INCLUDE_CORE_DUMP
	    /* call core dump generator */

	    edrCoreDumpGenerate ((void *) info, CORE_DUMP_KERNEL_TASK);
#endif  /* INCLUDE_CORE_DUMP */

	    /* policy handler being called for a specific task */

#ifdef INCLUDE_EDR_POLICY_HOOKS
            if ((edrPolicyHandlerHook == NULL) ||
                ((edrPolicyHandlerHook != NULL) &&
                 (!edrPolicyHandlerHook (EDR_FACILITY_KERNEL, info, FALSE))))
#endif /* INCLUDE_EDR_POLICY_HOOKS */
            (void) taskStopForce (info->taskId);
	    }
	else
	    {
	    SHELL_MSG (taskStopMsg, taskIdCurrent);

	    /* display any text provided by the inject call */

	    if (info != NULL && info->msg != NULL)
		SHELL_MSG ("%s\n", info->msg);

#ifdef	INCLUDE_CORE_DUMP
	    /* call core dump generator */

	    edrCoreDumpGenerate ((void *) info, CORE_DUMP_KERNEL_TASK);
#endif  /* INCLUDE_CORE_DUMP */

	    /* policy handler being called by the current task */

#ifdef INCLUDE_EDR_POLICY_HOOKS
            if ((edrPolicyHandlerHook == NULL) ||
                ((edrPolicyHandlerHook != NULL) &&
                 (!edrPolicyHandlerHook (EDR_FACILITY_KERNEL, info, FALSE))))
#endif /* INCLUDE_EDR_POLICY_HOOKS */
            (void) taskStopForce(0);

	    taskIdCurrent->pExcRegSet = (REG_SET *) NULL;
	    }
	}
    else
#endif /* INCLUDE_EDR_SYSDBG_FLAG */
	{
	/* In 'deployed' mode, stop the task. */

	if ((info != NULL) && (info->taskId != 0))
	    {
	    SHELL_MSG (taskStopMsg, info->taskId);

	    /* display any text provided by the inject call */

	    if (info->msg != NULL)
		SHELL_MSG ("%s\n", info->msg);

#ifdef	INCLUDE_CORE_DUMP
	    /* call core dump generator */

	    edrCoreDumpGenerate ((void *) info, CORE_DUMP_KERNEL_TASK);
#endif  /* INCLUDE_CORE_DUMP */

	    /* policy handler being called for a specific task */

#ifdef  INCLUDE_EDR_POLICY_HOOKS
            if ((edrPolicyHandlerHook == NULL) ||
                ((edrPolicyHandlerHook != NULL) &&
                 (!edrPolicyHandlerHook (EDR_FACILITY_KERNEL, info, FALSE))))
#endif  /* INCLUDE_EDR_POLICY_HOOKS */
            (void) taskStopForce(info->taskId);
	    }
	else
	    {
	    SHELL_MSG (taskStopMsg, taskIdCurrent);

	    /* display any text provided by the inject call */

	    if (info != NULL && info->msg != NULL)
		SHELL_MSG ("%s\n", info->msg);

#ifdef	INCLUDE_CORE_DUMP
	    /* call core dump generator */

	    edrCoreDumpGenerate ((void *) info, CORE_DUMP_KERNEL_TASK);
#endif  /* INCLUDE_CORE_DUMP */

	    /* policy handler being called by the current task */

#ifdef  INCLUDE_EDR_POLICY_HOOKS
            if ((edrPolicyHandlerHook == NULL) ||
                ((edrPolicyHandlerHook != NULL) &&
                 (!edrPolicyHandlerHook (EDR_FACILITY_KERNEL, info, FALSE))))
#endif  /* INCLUDE_EDR_POLICY_HOOKS */
            (void) taskStopForce(0);

	    taskIdCurrent->pExcRegSet = (REG_SET *) NULL;
	    }
	}
    }

/**************************************************************************
*
* edrSystemFatalPolicyHandler - handles system fatal errors
*
* It can be over-ridden to implement any other policy, as required.
*
* RETURNS: n/a
*/

void edrSystemFatalPolicyHandler
    (
    EDR_SYSTEM_INFO * pInfo	/* optional information for system fault */
    )
    {
    int key;

#ifdef	INCLUDE_EDR_POLICY_HOOKS
    /* call any policy hooks which have been installed */

    if (edrPolicyHandlerHook != NULL)
	{
	edrPolicyHandlerHook (EDR_FACILITY_SYSTEM, pInfo,
			      IS_LAB_FLAG_SET() ? TRUE : FALSE);
	}
#endif /* INCLUDE_EDR_POLICY_HOOKS */

    /* call any panic hooks which have been installed */

    if ((_func_excPanicHook != NULL) && (pInfo != NULL))
	{
	/* increment intCnt so printExc() will put the message in sysExcMsg */

	key = KERNEL_INT_CPU_LOCK ();
	_WRS_KERNEL_GLOBAL_ACCESS (intCnt)++;

	(*_func_excPanicHook) (pInfo->vector, pInfo->pEsf, pInfo->pRegs,
			       pInfo->pExcInfo);

	_WRS_KERNEL_GLOBAL_ACCESS (intCnt)--;
	KERNEL_INT_CPU_UNLOCK (key);
	}

#ifdef	INCLUDE_CORE_DUMP
    /* call core dump generator */

    edrCoreDumpGenerate ((void *) pInfo, CORE_DUMP_KERNEL);
#endif  /* INCLUDE_CORE_DUMP */

    reboot (BOOT_NORMAL);
    }

/**************************************************************************
*
* edrRtpFatalPolicyHandler - handles fatal errors in User-mode (RTP) code
*
* This function is called by the exception handler, when user-level (RTP)
* code takes an exception, or when an RTP FATAL ED&R message is injected
* from the RTP (via the _edrErrorInject system call). Its default policy is
* to destroy the RTP in 'deployed' mode, but if the ED&R 'system debug flag'
* is set, in which case the system is considered to be in 'lab' mode,
* it suspends the RTP.
*
* It can be over-ridden to implement any other policy, as required.
*
* RETURNS: n/a
*/

#ifdef INCLUDE_RTP
 #ifdef INCLUDE_SHELL
extern char *rtpName(RTP_ID rtpId);
 #endif
#endif

void edrRtpFatalPolicyHandler
    (
    EDR_RTP_INFO *info		/* optional information for RTP fault */
    )
    {
    /* no need to do anything if RTP's are not included */

#ifdef INCLUDE_RTP

#ifdef	INCLUDE_EDR_SYSDBG_FLAG
    if (IS_LAB_FLAG_SET())
	{
	/* In 'lab' mode, suspend the RTP */

	extern STATUS rtpTaskAllStop(RTP_ID);

	/* stop all tasks within the RTP */

	if ((info != NULL) && (info->rtpId != NULL))
	    {
	    /* check if being called due to a signal delivery */

	    if (WIFSIGNALED(info->status))
		SHELL_SIG_MSG (rtpSigStopMsg, info->rtpId,
			       WTERMSIG(info->status));
	    else
		SHELL_MSG (rtpStopMsg, info->rtpId);

#if defined(INCLUDE_CORE_DUMP) || defined(INCLUDE_CORE_DUMP_RTP)
	    /* call core dump generator */

	    edrCoreDumpRtpFaultHandle ((void *) info);
#endif /* INCLUDE_CORE_DUMP || INCLUDE_CORE_DUMP_RTP */

	    /* policy handler being called for a specific RTP */

#ifdef INCLUDE_EDR_POLICY_HOOKS
            if ((edrPolicyHandlerHook == NULL) ||
                ((edrPolicyHandlerHook != NULL) &&
                 (!edrPolicyHandlerHook (EDR_FACILITY_RTP, info, FALSE))))
#endif /* INCLUDE_EDR_POLICY_HOOKS */
            rtpTaskAllStop (info->rtpId);
	    }
	else
	    {
	    /* display any text provided by the inject syscall */

	    if (info != NULL && info->msg != NULL)
		SHELL_PRINT ((ALL_SHELL_SESSIONS, "%s: %s\n", rtpName(0),
			      info->msg));

	    SHELL_MSG (rtpStopMsg, taskIdCurrent->rtpId);

#if defined(INCLUDE_CORE_DUMP) || defined(INCLUDE_CORE_DUMP_RTP)
	    /* call core dump generator */

	    edrCoreDumpRtpFaultHandle ((void *) info);
#endif /* INCLUDE_CORE_DUMP || INCLUDE_CORE_DUMP_RTP */

	    /* policy handler being called by the current RTP */

#ifdef INCLUDE_EDR_POLICY_HOOKS
            if ((edrPolicyHandlerHook == NULL) ||
                ((edrPolicyHandlerHook != NULL) &&
                 (!edrPolicyHandlerHook (EDR_FACILITY_RTP, info, FALSE))))
#endif /* INCLUDE_EDR_POLICY_HOOKS */
            rtpTaskAllStop (taskIdCurrent->rtpId);
	    }
	}
    else
#endif /* INCLUDE_EDR_SYSDBG_FLAG */
	{
	/* In 'deployed' mode, kill the RTP */

	if ((info != NULL) && (info->rtpId != NULL))
	    {
            /* policy handler being called for a specific RTP */

#ifdef  INCLUDE_EDR_POLICY_HOOKS
            if (edrPolicyHandlerHook != NULL)
                edrPolicyHandlerHook (EDR_FACILITY_RTP, info, FALSE);
#endif /* INCLUDE_EDR_POLICY_HOOKS */

	    /* check if being called due to a signal delivery */

	    if (WIFSIGNALED(info->status))
		SHELL_SIG_MSG (rtpSigDeleteMsg, info->rtpId,
			       WTERMSIG(info->status));
	    else
		SHELL_MSG (rtpDeleteMsg, info->rtpId);

#if defined(INCLUDE_CORE_DUMP) || defined(INCLUDE_CORE_DUMP_RTP)
	    /* call core dump generator */

	    edrCoreDumpRtpFaultHandle ((void *) info);
#endif	/* INCLUDE_CORE_DUMP || INCLUDE_CORE_DUMP_RTP */

            /*
             * If the RTP that triggered the exception holds a task that
             * happens to be delete-safe, and Core Dump support for RTP has
             * stopped all the RTP's tasks, the RTP deletion will not be
             * allowed. So we force-delete the RTP if ever rtpDelete() returns
             * an error.
             */

	    if (rtpDelete (info->rtpId, info->options, info->status) == ERROR)
                (void)rtpDeleteForce (info->rtpId);
	    }
	else
	    {
            /* policy handler being called by the current RTP */

#ifdef  INCLUDE_EDR_POLICY_HOOKS
            if (edrPolicyHandlerHook != NULL)
                edrPolicyHandlerHook (EDR_FACILITY_RTP, info, FALSE);
#endif  /* INCLUDE_EDR_POLICY_HOOKS */

	    /* display any text provided by the inject syscall */

	    if (info != NULL && info->msg != NULL)
		SHELL_PRINT ((ALL_SHELL_SESSIONS, "%s: %s\n", rtpName(0),
			     info->msg));

	    SHELL_MSG (rtpDeleteMsg, taskIdCurrent->rtpId);

#if defined(INCLUDE_CORE_DUMP) || defined(INCLUDE_CORE_DUMP_RTP)
	    /* call core dump generator */

	    edrCoreDumpRtpFaultHandle ((void *) info);
#endif /* INCLUDE_CORE_DUMP || INCLUDE_CORE_DUMP_RTP */

            /*
             * If the RTP that triggered the exception holds a task that
             * happens to be delete-safe, and Core Dump support for RTP has
             * stopped all the RTP's tasks, the RTP deletion will not be
             * allowed. So we force-delete the RTP if ever rtpDelete() returns
             * an error.
             */

	    if (rtpDelete (taskIdCurrent->rtpId, 0,
                           SET_TERMSIG(SIGKILL)) == ERROR)
                (void) rtpDeleteForce (taskIdCurrent->rtpId);
	    }
	}
#endif /* INCLUDE_RTP */
    }

/**************************************************************************
*
* edrInitFatalPolicyHandler - handles fatal errors in init phase
*
* It can be over-ridden to implement any other policy, as required.
*
* RETURNS: n/a
*/

void edrInitFatalPolicyHandler
    (
    EDR_INIT_INFO *info		/* optional information on init fault */
    )
    {
    /* call any policy hooks which have been installed */

#ifdef  INCLUDE_EDR_POLICY_HOOKS
    if (edrPolicyHandlerHook != NULL)
        edrPolicyHandlerHook (EDR_FACILITY_INIT, info,
                              IS_LAB_FLAG_SET() ? TRUE : FALSE);
#endif /* INCLUDE_EDR_POLICY_HOOKS */

    /* call any panic hooks which have been installed */

    if ((_func_excPanicHook != NULL) && (info != NULL))
	{
	/* increment intCnt so printExc() will put the message in sysExcMsg */

	_WRS_KERNEL_GLOBAL_ACCESS (intCnt)++;

	(*_func_excPanicHook) (info->vector, info->pEsf, info->pRegs,
			       info->pExcInfo);

	_WRS_KERNEL_GLOBAL_ACCESS (intCnt)--;
	}

#ifdef	INCLUDE_CORE_DUMP
    /* call core dump generator */

    edrCoreDumpGenerate ((void *) info, CORE_DUMP_KERNEL_INIT);
#endif  /* INCLUDE_CORE_DUMP */

#ifdef  INCLUDE_EDR_SYSDBG_FLAG
    if (IS_LAB_FLAG_SET())
	{
	/* In 'lab' mode, reboot the system. */

	reboot (BOOT_NO_AUTOBOOT);
	}
    else
#endif  /* INCLUDE_EDR_SYSDBG_FLAG */
	{
	/* In 'deployed' mode, reboot the system. */

	reboot (BOOT_NO_AUTOBOOT);
	}
    }

/**************************************************************************
*
* edrInterruptFatalPolicyHandler - handles fatal errors in interrupts
*
* It can be over-ridden to implement any other policy, as required.
*
* RETURNS: n/a
*/

void edrInterruptFatalPolicyHandler
    (
    EDR_INTERRUPT_INFO *info	/* optional information for interrupt fault */
    )
    {
    /* call any policy hooks which have been installed */

#ifdef  INCLUDE_EDR_POLICY_HOOKS
    if (edrPolicyHandlerHook != NULL)
        edrPolicyHandlerHook (EDR_FACILITY_INTERRUPT, info,
                              IS_LAB_FLAG_SET() ? TRUE : FALSE);
#endif /* INCLUDE_EDR_POLICY_HOOKS */

    /* call any panic hooks which have been installed */

    if ((_func_excPanicHook != NULL) && (info != NULL))
	(*_func_excPanicHook) (info->vector, info->pEsf, info->pRegs,
			       info->pExcInfo);

#ifdef	INCLUDE_CORE_DUMP
    /* call core dump generator */

    edrCoreDumpGenerate ((void *) info, CORE_DUMP_INTERRUPT);
#endif  /* INCLUDE_CORE_DUMP */

#ifdef	INCLUDE_EDR_SYSDBG_FLAG
    if (IS_LAB_FLAG_SET())
	{
	/* In 'lab' mode, reboot the system. */

	reboot (BOOT_NORMAL);
	}
    else
#endif  /* INCLUDE_EDR_SYSDBG_FLAG */
	{
	/* In 'deployed' mode, reboot the system. */

	reboot (BOOT_NORMAL);
	}
    }
