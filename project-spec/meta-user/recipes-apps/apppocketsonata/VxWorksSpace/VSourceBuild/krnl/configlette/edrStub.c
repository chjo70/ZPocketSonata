/* edrStub.c - ED&R error-injection stub */

/*
 * Copyright (c) 2003-2010, 2013-2017 Wind River Systems, Inc.
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
01mar17,h_k  added CORE_DUMP_INTERRUPT case at edrCoreDumpGenerate().
             (V7COR-4879)
08jun16,jmp  Fixed Core Dump build on MMU less config.
25may16,pcs  Added code corresponding to Component INCLUDE_EDR_POLICY_HOOKS. 
             Moved policy handler support code from edrDefaultPolicy.c to here.
18sep14,pcs  Moved the kernel fatal error handling policy handlers to a new file
             edrDefaultPolicy.c
31jul14,pcs  Updated to add support for user fatal policy handling.
24mar16,cma  remove extern <sysStartType> (V7COR-3894)
31jul15,h_k  cleaned up compiler warnings in Diab PPC64. (F2518)
24dec14,jmp  Fixed build warnings.
24dec14,jmp  Added posix signal information to core dump facility (V7COR-2400).
04mar14,cww  fix incorrect parameter passed to rtpDeleteForce() from
	     edrRtpFatalPolicyHandler()
27jan14,elp  Fixed _WRS_CONFIG_SHELL dependencies.
18oct13,h_k  excluded shellInOutLibP.h header inclusion unless
             INCLUDE_SHELLL is defined.
27aug13,rlp  Fixed build when Core Dump is disabled.
05jul13,jmp  Added edrCoreDumpRtpFaultHandle() wrapper to handle core dump
	     generation for RTP fault, and decide which kind of Core Dump
	     to generate (CQID Fix WIND00425385).
15mar13,pad  In deployed mode, force-delete the RTP if the regular RTP
             deletion failed (side-effect of fix for defect WIND00402989).
16nov10,jpb  Replaced funcBindP.h with excLibP.h
27sep10,rlp  Invoked context's stop API if handlerHook() returns FALSE.
29sep10,gls  made EDR_POLICY_HOOKS a component (WIND00234560)
05may10,rlp  Invoked either edrPolicyHandlerHook() or context's stop API.
08jun09,pcs  Updated to add support for LP64 data model.
27aug08,jpb  Renamed VSB config file.
10jul08,jmp  updated coreDumpRtpGenerate() call to pass rtpId and taskId
             to RTP core dump generator.
05jul08,jpb  Renamed INCLUDE_EDR_TASK_HOOKS to _WRS_CONFIG_EDR_TASK_HOOKS.
             Added include path for kernel configurations options set in
             vsb.  Added ifdefs around edrPolicyHandlerHook calls.
21may08,jmp  added edrCoreDumpRtpGenerate() for RTP core dump generation
             (REQ CQ:WIND00005075).
20sep07,jmp  Updated edrCoreDumpGenerate() to pass the EDR string to core
             dump generator (CQ:WIND00104805).
17may07,mcm  Fixing build issue seen with GCC 4.1.2 due to incorrect
             declaration of rtpName.
20apr07,jmg  Added include for intLibP.h
17jul06,zl   abstract intCnt access via macros.
02may06,lei  added SMP support
09sep05,jmp  updated core dump types.
26aug05,dbt  Completed core dump hooks support.
11aug05,dbt  Include coreDumpLibP.h to get coreDumpGenerate() prototype.
09aug05,dbt  Added handling of FATAL_SYSTEM_CORE_DUMP_ENABLE and
             KERNEL_APPL_CORE_DUMP_ENABLE parameters.
18jul05,md   scale stubs a bit more
03aug05,jmp  added core dump support.
01nov04,md   update messages for failed rtp/task failures
27oct04,md   fixed warning
27sep04,md   added callout to _func_excPanicHook
23sep04,bpn  Changed shellInOutLib.h to shellInOutLibP.h.
10sep04,md   display injection message for kernel and RTP failures
29jul04,md   always include policies and add shell messages
16jul04,job  Fix for SPR #99384 - call taskSuspend() if taskStop()
	     fails (ie. for VX_UNBREAKABLE tasks)
30jun04,md   fix warning when building bootroms (SPR 98727)
26apr04,elg  Add exception hooks so that WDB Agent can notify exceptions
             to host.
22apr04,md   added paramter to edrInterruptFatalPolicyHandler
18mar04,md   put tasks in stopped mode instead of suspend mode
12feb04,md   change edrUserFatalPolicyHandler to edrRtpFatalPolicyHandler
26nov03,dbs  correct the name of the debug-flag-get routine
20nov03,dbs  fully implement EDR policy handling
11nov03,dbs  update policy handlers
25sep03,dbs  implement ED&R system policies
10sep03,dbs  written
*/

/*
DESCRIPTION

This module is an 'always included' component that provides a
forwarding stub for ED&R error injection. It provides a single
function, edrErrorInjectStub(), which is conditionally compiled to
either forward all calls to the real implementation of
edrErrorInject(), if INCLUDE_EDR_ERRLOG is defined, or otherwise to
simply return OK.

This allows other components and subsystems to be written as though
ED&R were always present, and so they can inject errors at any time,
even in the early boot sequence.

This is a preferable solution to the alternative of having a FUNCPTR
to edrErrorInject(), since errors occuring prior to the initialization
of the funcptr would be missed, and this would defeat some of the
purpose of ED&R.
*/

#ifndef  __INCedrStub_c
#define  __INCedrStub_c

#ifdef INCLUDE_EDR_ERRLOG
#include <sysLib.h>
#include <regs.h>
#include <edrLib.h>
#endif
#ifdef _WRS_CONFIG_CORE_DUMP
#include <coreDumpLib.h>
#include <private/coreDumpLibP.h>
#endif  /* _WRS_CONFIG_CORE_DUMP */
#include <private/edrLibP.h>
#include <private/taskLibP.h>   /* for taskStopForce()    */

#ifdef  INCLUDE_CORE_DUMP
void edrCoreDumpGenerate (void * info, CORE_DUMP_TYPE coreDumpType);
#endif  /* INCLUDE_CORE_DUMP */

#ifdef INCLUDE_RTP
#ifdef  INCLUDE_CORE_DUMP_RTP
void edrCoreDumpRtpGenerate (void * info);
#endif  /* INCLUDE_CORE_DUMP_RTP */

#if defined(INCLUDE_CORE_DUMP) || defined(INCLUDE_CORE_DUMP_RTP)
void edrCoreDumpRtpFaultHandle (void * info);
#endif /* INCLUDE_CORE_DUMP || INCLUDE_CORE_DUMP_RTP */
#endif /* INCLUDE_RTP */

/* globals */

#ifdef  INCLUDE_EDR_POLICY_HOOKS
EDR_POLICY_HANDLER_HOOK  edrPolicyHandlerHook = NULL;
#endif  /* INCLUDE_EDR_POLICY_HOOKS */

/* locals */

/* forward static declarations */


/**************************************************************************
*
* edrStubInit - inserts a BOOT record
*
* NOMANUAL
*/

void edrStubInit (void)
    {
#ifdef	INCLUDE_EDR_ERRLOG
    const char *msg;

    /* set appropriate system boot message */

    switch (sysStartType & 
	    (BOOT_NORMAL | BOOT_NO_AUTOBOOT | BOOT_CLEAR | BOOT_QUICK_AUTOBOOT))
	{
	case BOOT_NORMAL:
	    msg = "System Booted - normal boot";
	    break;
	case BOOT_NO_AUTOBOOT:
	    msg = "System Booted - no autoboot";
	    break;
	case BOOT_QUICK_AUTOBOOT:
	    msg = "System Booted - quick autoboot";
	    break;
	case BOOT_CLEAR:
	    msg = "System Booted - cold boot";
	    break;
	case BOOT_CLEAR | BOOT_NO_AUTOBOOT:
	    msg = "System Booted - cold no autoboot";
	    break;
	case BOOT_CLEAR | BOOT_QUICK_AUTOBOOT:
	    msg = "System Booted - cold quick autoboot";
	    break;
	default:
	    msg = "System Booted";
	    break;
	}

    EDR_BOOT_INJECT (msg);
#endif  /* INCLUDE_EDR_ERRLOG */
    }

/**************************************************************************
*
* edrErrorInjectStub - ED&R stub/forwarding function
*
* This function is linked into all error-injection points, so that
* error injection will work at any time once the image is booted
* (using a FUNCPTR would mean that errors occuring before the funcptr
* was initialized would be missed).  However, to allow ED&R to be
* compiled out if necessary, it's body is conditionally compiled to
* call the real edrErrorInject() only if the error-log component has
* been included in the system build.
*
* NOMANUAL
*/

STATUS edrErrorInjectStub
    (
    int			kind,		/* severity | facility		*/
    const char *	fileName,	/* name of source file		*/
    int			lineNumber,	/* line number of source code	*/
    const REG_SET *	pRegSet,	/* current register values	*/
    const EXC_INFO *	pExcInfo,	/* CPU-specific exception info	*/
    void*		addr,		/* faulting address (e.g. PC)	*/
    const char *	textPayload	/* additional text string	*/
    )
    {
#ifdef INCLUDE_EDR_ERRLOG
    return edrErrorInject (kind,
			   fileName,
			   lineNumber,
			   pRegSet,
			   pExcInfo,
			   addr,
			   textPayload);
#else /* INCLUDE_EDR_ERRLOG */
    return OK;
#endif /* INCLUDE_EDR_ERRLOG */
    }


#ifdef  INCLUDE_EDR_POLICY_HOOKS
/******************************************************************************
*
* edrPolicyHandlerHookAdd - add a hook in to the EDR policy handlers
*
* This routine adds a hook to be called from the EDR policy handlers.
*
* RETURNS: OK if there is no existing hook, and the hook is added
* correctly, or if the existing hook is the same as the one
* supplied; ERROR if there is already an existing, but different, hook
* in place
*
* SEE ALSO: edrErrorPolicyHookRemove, edrPolicyHandlerHookGet
*/

STATUS edrPolicyHandlerHookAdd
    (
    EDR_POLICY_HANDLER_HOOK     hook            /* hook address */
    )
    {
    if ((edrPolicyHandlerHook != NULL) && (edrPolicyHandlerHook != hook))
        return (ERROR);

    edrPolicyHandlerHook = hook;

    return (OK);
    }

/**************************************************************************
*
* edrErrorPolicyHookRemove - removes the existing policy handler hook
*
* This function removes a hook which was added using edrPolicyHandlerHookAdd().
*
* RETURNS: OK if there was an existing hook, ERROR if the hook was
* already NULL
*
* SEE ALSO: edrPolicyHandlerHookAdd, edrPolicyHandlerHookGet
*/

STATUS edrErrorPolicyHookRemove (void)
    {
    if (edrPolicyHandlerHook == NULL)
        return (ERROR);

    edrPolicyHandlerHook = NULL;

    return (OK);
    }

/**************************************************************************
*
* edrPolicyHandlerHookGet - returns the existing error-injection hook
*
* This function returns a pointer to the hook function which was added using
* edrPolicyHandlerHookAdd().  If no hook has been added, the value returned
* is NULL.
*
* RETURNS: the hook function pointer, which may be NULL
*
* SEE ALSO: edrPolicyHandlerHookAdd, edrErrorPolicyHookRemove
*/

EDR_POLICY_HANDLER_HOOK edrPolicyHandlerHookGet (void)
    {
    return (edrPolicyHandlerHook);
    }

#endif /* INCLUDE_EDR_POLICY_HOOKS */

#if defined (INCLUDE_RTP) && defined (INCLUDE_SHELL)

/**************************************************************************
*
* rtpName - returns a string denoting the name of an RTP
*
* This function returns a string representing the base name (name of RTP file
* without the path) of the specified RTP.  
*
* RETURNS: a string representing the name of the RTP
*
* NOMANUAL
*/

char *rtpName
    (
    RTP_ID rtpId	/* RTP id to examine */
    )
    {
    char  *p;
    int    i;

    /* map NULL to current RTP id */

    if (rtpId == NULL)
	rtpId = taskIdCurrent->rtpId;

    /* traverse pathname from reverse stopping at first "/" */

    i = (int) strlen(rtpId->pPathName);
    p = rtpId->pPathName + i;

    for (;(*p != '/') && (i > 0); p--,i--);

    if (*p == '/')
	p++;

    return (p);
    }

#endif /* INCLUDE_RTP && INCLUDE_SHELL */

#ifdef	INCLUDE_CORE_DUMP
/**************************************************************************
*
* edrCoreDumpGenerate - call core dump generation routine
*
* This routine calls core dump generation routine when necessary (according
* to core dump configuration). It extracts necessary information from
* ED&R structure given in parameter.
*
* RETURNS: N/A
*
* SEE ALSO: coreDumpLib
*/

void edrCoreDumpGenerate
    (
    void *		info,		/* optional information for fault */
    CORE_DUMP_TYPE	coreDumpType	/* coreDump type */
    )
    {
    int		vector = 0;		/* exception vector number */
    char *	pEsf = NULL;		/* exception frame pointer */
    REG_SET *	pRegs = NULL;		/* exception register set */
    EXC_INFO *	pExcInfo = NULL;	/* exception information */
    BOOL	isException = FALSE;	/* are we handling an exception? */
    char *	pEdrString = NULL;	/* ptr to ED&R record optional msg */
    int         signalNum = 0;          /* POSIX signal number */
    int         signalSubcode = 0;      /* POSIX "si_code" */

#if	(KERNEL_APPL_CORE_DUMP_ENABLE == FALSE)
    if (coreDumpType == CORE_DUMP_KERNEL_TASK)
	{
	/* Don't generate core dump for kernel task level exceptions */

	return;
	}
#endif	/* KERNEL_APPL_CORE_DUMP_ENABLE == FALSE */

#if	(FATAL_SYSTEM_CORE_DUMP_ENABLE == FALSE)
    if (coreDumpType != CORE_DUMP_KERNEL_TASK)
	{
	/* Don't generate core dump for fatal kernel errors */

	return;
	}
#endif	/* FATAL_SYSTEM_CORE_DUMP_ENABLE == FALSE */

    if (info != NULL)
    	{
	switch (coreDumpType)
	    {
#if	(KERNEL_APPL_CORE_DUMP_ENABLE == TRUE)
	    case CORE_DUMP_KERNEL_TASK:
		vector		= ((EDR_TASK_INFO *)info)->vector;
		pEsf		= ((EDR_TASK_INFO *)info)->pEsf;
		pRegs		= ((EDR_TASK_INFO *)info)->pRegs;
		pExcInfo	= ((EDR_TASK_INFO *)info)->pExcInfo;
		isException	= ((EDR_TASK_INFO *)info)->isException;
		pEdrString	= (char *)((EDR_TASK_INFO *)info)->msg;
                signalNum       = ((EDR_TASK_INFO *)info)->signalNum;
                signalSubcode   = ((EDR_TASK_INFO *)info)->signalSubcode;
		break;
#endif	/* KERNEL_APPL_CORE_DUMP_ENABLE == TRUE */

#if	(FATAL_SYSTEM_CORE_DUMP_ENABLE == TRUE)
	    case CORE_DUMP_KERNEL_INIT:
		vector		= ((EDR_INIT_INFO *)info)->vector;
		pEsf		= ((EDR_INIT_INFO *)info)->pEsf;
		pRegs		= ((EDR_INIT_INFO *)info)->pRegs;
		pExcInfo	= ((EDR_INIT_INFO *)info)->pExcInfo;
		isException	= ((EDR_INIT_INFO *)info)->isException;
		pEdrString	= (char *)((EDR_INIT_INFO *)info)->msg;
                signalNum       = ((EDR_INIT_INFO *)info)->signalNum;
                signalSubcode   = ((EDR_INIT_INFO *)info)->signalSubcode;
		break;

	    case CORE_DUMP_INTERRUPT:
		vector		= ((EDR_INTERRUPT_INFO *)info)->vector;
		pEsf		= ((EDR_INTERRUPT_INFO *)info)->pEsf;
		pRegs		= ((EDR_INTERRUPT_INFO *)info)->pRegs;
		pExcInfo	= ((EDR_INTERRUPT_INFO *)info)->pExcInfo;
		isException	= ((EDR_INTERRUPT_INFO *)info)->isException;
		pEdrString	= (char *)((EDR_INTERRUPT_INFO *)info)->msg;
                signalNum       = ((EDR_INTERRUPT_INFO *)info)->signalNum;
                signalSubcode   = ((EDR_INTERRUPT_INFO *)info)->signalSubcode;
		break;

	    case CORE_DUMP_KERNEL:
		vector		= ((EDR_SYSTEM_INFO *)info)->vector;
		pEsf		= ((EDR_SYSTEM_INFO *)info)->pEsf;
		pRegs		= ((EDR_SYSTEM_INFO *)info)->pRegs;
		pExcInfo	= ((EDR_SYSTEM_INFO *)info)->pExcInfo;
		isException	= ((EDR_SYSTEM_INFO *)info)->isException;
		pEdrString	= (char *)((EDR_SYSTEM_INFO *)info)->msg;
                signalNum       = ((EDR_SYSTEM_INFO *)info)->signalNum;
                signalSubcode   = ((EDR_SYSTEM_INFO *)info)->signalSubcode;
		break;
#endif	/* FATAL_SYSTEM_CORE_DUMP_ENABLE == TRUE */

	    default:
	    	/* Keep generating core dump but do not fill information */

	    	break;
	    }
	}

    coreDumpGenerate (vector, pEsf, pRegs, pExcInfo, coreDumpType,
		      pEdrString, isException, signalNum, signalSubcode);
    }
#endif	/* INCLUDE_CORE_DUMP */

#ifdef INCLUDE_RTP
#if defined(INCLUDE_CORE_DUMP) || defined(INCLUDE_CORE_DUMP_RTP)
/*******************************************************************************
*
* edrCoreDumpRtpFaultHandle - handle core dump generation for RTP fault
*
* This routine handles core dump generation for RTP faults.
* If we are in supervisor mode, then we generate a Kernel Core Dump.
* Otherwise, we generate an RTP Core Dump.
*
* RETURNS: N/A
*/

void edrCoreDumpRtpFaultHandle
    (
    void *	info		/* optional information for fault */
    )
    {
    BOOL supervisorMode = FALSE;	/* User or supervisor mode ? */

    if ((info != NULL) && (((EDR_RTP_INFO *)info)->pExcInfo != NULL))
	{
#ifdef _WRS_CONFIG_VXSIM
        /* Retrieve pRegs: Required by _WRS_IS_SUPV_EXC() macro on vxsim arch */
        REG_SET * pRegs = ((EDR_RTP_INFO *)info)->pRegs;
#else   /* _WRS_CONFIG_VXSIM */
        /* Retrieve excInfo: Required by _WRS_IS_SUPV_EXC macro on other arch */
        EXC_INFO excInfo = *((EDR_RTP_INFO *)info)->pExcInfo;
#endif  /* !_WRS_CONFIG_VXSIM */

	supervisorMode = _WRS_IS_SUPV_EXC();
	}

    /* User or supervisor mode ? */

    if (supervisorMode)
	{
	/*
	 * Supervisor mode: Generate a Kernel Core Dump if support is included.
	 */

#ifdef INCLUDE_CORE_DUMP
	EDR_TASK_INFO kernelInfo;

	if (info != NULL)
	    {
	    kernelInfo.vector		= ((EDR_RTP_INFO *)info)->vector;
	    kernelInfo.pEsf		= ((EDR_RTP_INFO *)info)->pEsf;
	    kernelInfo.pRegs		= ((EDR_RTP_INFO *)info)->pRegs;
	    kernelInfo.pExcInfo		= ((EDR_RTP_INFO *)info)->pExcInfo;
	    kernelInfo.isException	= ((EDR_RTP_INFO *)info)->isException;
	    kernelInfo.msg		= (char *)((EDR_RTP_INFO *)info)->msg;

	    edrCoreDumpGenerate ((void *)&kernelInfo, CORE_DUMP_KERNEL_TASK);
	    }
	else
	    edrCoreDumpGenerate ((void *)NULL, CORE_DUMP_KERNEL_TASK);
#endif
	}
#ifdef	INCLUDE_CORE_DUMP_RTP
    else
	{
	/*
	 * User Mode: Generate an RTP Core Dump.
	 */

	edrCoreDumpRtpGenerate (info);
	}
#endif	/* INCLUDE_CORE_DUMP_RTP */
    }
#endif	/* INCLUDE_CORE_DUMP || INCLUDE_CORE_DUMP_RTP */

#ifdef	INCLUDE_CORE_DUMP_RTP
/**************************************************************************
*
* edrCoreDumpRtpGenerate - call RTP core dump generation routine
*
* This routine calls RTP core dump generation routine when necessary. It
* extracts necessary information from ED&R structure given in parameter.
*
* RETURNS: N/A
*
* SEE ALSO: coreDumpLib
*/

void edrCoreDumpRtpGenerate
    (
    void *	info		/* optional information for fault */
    )
    {
    RTP_ID	rtpId = 0;		/* RTP's id */
    TASK_ID	taskId = 0;		/* task id within RTP */
    int		vector = 0;		/* exception vector number */
    char *	pEsf = NULL;		/* exception frame pointer */
    REG_SET *	pRegs = NULL;		/* exception register set */
    EXC_INFO *	pExcInfo = NULL;	/* exception information */
    BOOL	isException = FALSE;	/* are we handling an exception? */
    char *	pEdrString = NULL;	/* ptr to ED&R record optional msg */
    int         signalNum = 0;          /* POSIX signal number */
    int         signalSubcode = 0;      /* POSIX "si_code" */

    if (info != NULL)
    	{
	rtpId		= ((EDR_RTP_INFO *)info)->rtpId;
	taskId		= ((EDR_RTP_INFO *)info)->taskId;
	vector		= ((EDR_RTP_INFO *)info)->vector;
	pEsf		= ((EDR_RTP_INFO *)info)->pEsf;
	pRegs		= ((EDR_RTP_INFO *)info)->pRegs;
	pExcInfo	= ((EDR_RTP_INFO *)info)->pExcInfo;
	isException	= ((EDR_RTP_INFO *)info)->isException;
	pEdrString	= (char *)((EDR_RTP_INFO *)info)->msg;
        signalNum       = ((EDR_RTP_INFO *)info)->signalNum;
        signalSubcode   = ((EDR_RTP_INFO *)info)->signalSubcode;
	}

    coreDumpRtpGenerate (rtpId, taskId, vector, pEsf, pRegs, pExcInfo,
			 CORE_DUMP_RTP, pEdrString, isException,
                         signalNum, signalSubcode);
    }
#endif	/* INCLUDE_CORE_DUMP_RTP */
#endif	/* INCLUDE_RTP */

#endif  /* __INCedrStub_c */

