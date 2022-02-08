/* sigLibP.h - private signal facility library header */

/* 
 * Copyright (c) 1984-1997, 2006, 2008-2010, 2012-2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
22sep14,gls  Added check for NULL function pointer in SIG_TIMEOUT_RECALC()
01oct14,jpb  V7COR-1690: Removed sigEvtRtn which is not used anywhere
15may13,cww  Moved isInSigHandler() to rtpSigLibP.h (WIND00417069)
19apr13,cww  Added pSigContext field to sigtcb (WIND00408461)
21jun12,pad  Moved the definition of the sigcontext type to signal.h since
             this type is documented (defect 315689).
16jun10,pcs  change the data type of timeout from an int to _Vx_ticks_t
29apr10,pad  Moved extern C statement after include statements.
06apr10,jpb  Updated sigpend struct.
10sep09,cww  LP64 adaptation
08jul08,gls  added warning about inclusion in semLibInline.h
21dec06,aeg  added _WRS_FUNC_NORETURN attribute to _sigCtxLoad
06mar06,gls  added queuedPend to sigpend
07feb06,gls  added SIGFAULT_POSIX_SIGNUM and SIGFAULT_VXWORKS_SIGNUM
             added parameter to sigInit()
31jan06,pes  Define SIGFAULTVEC macro.
13jan06,gls  added sigFfsMsb function prototype
             removed K&R style function prototypes
19may97,jpd  made RESTART available from ASMLANGUAGE.
06jul94,rrr  added sc_resumption for I960KB.
28jan94,kdl  marked sigEvtRtn pointer declaration extern.
12jan94,kdl  added sigqueueInit() prototype.
09jan94,c_s  applied rrr's patch for SPR #955.
10dec93,smb  added event logging routine.
22sep92,rrr  added support for c++
22aug92,rrr  added some prototypes.
30jul92,rrr  backed out 02d (we are now back to 02c)
30jul92,kdl  backed out 02c changes pending rest of exc handling.
29jul92,rrr  added fault table for exceptions
08jul92,rrr  added all the _sigCtx* function prototypes.
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
27apr92,rrr  written.
*/

#ifndef __INCsigLibPh
#define __INCsigLibPh

#ifndef _ASMLANGUAGE
#include <signal.h>
#include <excLib.h>
#include <regs.h>

#ifdef __cplusplus
extern "C" {
#endif

#endif /* !_ASMLANGUAGE */

    /*
     *  ***** WARNING *****
     *
     * This private header file is included by the public header file(s):
     *   - h/inline/semLibInline.h 
     *
     * Ensure that no usage of a VSB source configuration macro is made 
     * by any structure or macro in this file that is also used(directly or 
     * indirectly) by the above list of public header files.
     */

#define RESTART		1	/* must be different from OK and ERROR */

#ifndef _ASMLANGUAGE

/* 
 * SIGFAULTVEC is used to encode POSIX signals along with legacy VxWorks 
 * signals in _sigfaulttable. 
 */

#define SIGFAULTVEC(vector,vxSig,posixSig) {(vector),((vxSig)|((posixSig)<<16))}

/* 
 * SIGFAULT_POSIX_SIGNUM and SIGFAULT_VXWORKS_SIGNUM are use to extract the
 * appropriate signal number on fault depending on the mode of the system.
 */

#define SIGFAULT_POSIX_SIGNUM(sig) ((0xffff0000 & sig) >> 16)

#define SIGFAULT_VXWORKS_SIGNUM(sig) (0x0000ffff & sig)

#define SIG_TIMEOUT_RECALC(t)	((_func_sigTimeoutRecalc == NULL) ? (t) : \
                                 (*_func_sigTimeoutRecalc)(t))

struct sigq			/* (Not posix) */
    {
    struct sigq		*sigq_next;
    struct sigq		*sigq_prev;
    };

struct sigstack			/* (Not posix) */
    {
    void		*ss_sp;
    int			ss_onstack;
    };

struct sigtcb			/* (Not posix) */
    {
    struct sigaction	sigt_vec[_NSIGS + 1];
    struct sigq		sigt_qhead[_NSIGS + 1];
    struct sigstack	sigt_stack;
    struct sigwait	*sigt_wait;
    sigset_t		sigt_kilsigs;
    sigset_t		sigt_blocked;
    sigset_t		sigt_pending;
    sigset_t		sigt_ignored;
    struct sigcontext *	pSigContext;
    };

struct sigpend			/* (Not posix) */
    {
    struct sigq		sigp_q;
    struct siginfo	sigp_info;
    int  		sigp_overruns;
    int 		sigp_active_overruns;
    REG_SET		*sigp_pregs;
    struct sigtcb	*sigp_tcb;
	BOOL		queuedPend;  /* temporary */
    };

struct sigfaulttable
    {
    int sigf_fault;
    int sigf_signo;
    };

extern STATUS (*_func_sigExcKill)
    (
    int       signalNum,        /* POSIX signal number */
    int       signalSubcode,    /* POSIX "si_code" */
    int       faultType,        /* hardware exception vector or type */
    void *    faultAddr,        /* address where the exception occured */
    REG_SET * pRegSet           /* architecture's register set */
    );

extern int  (*_func_sigprocmask)        (int how, const sigset_t *pSet,
                                         sigset_t *pOset);
extern _Vx_ticks_t  (*_func_sigTimeoutRecalc)   (_Vx_ticks_t timeout);
extern int  (*_func_sigfillset)         (sigset_t *pSet);

extern void 	_sigCtxRtnValSet   (REG_SET *regs, int val);
extern void *	_sigCtxStackEnd    (const REG_SET *regs);
extern int 	_sigCtxSave        (REG_SET *regs);
extern _WRS_FUNC_NORETURN 
       void 	_sigCtxLoad        (const REG_SET *regs);
extern void 	_sigCtxSetup       (REG_SET *regs, void *pStackBase, 
				    void (*taskEntry)(), _Vx_usr_arg_t *args);

extern STATUS	sigInit 	   (BOOL posixMode);
extern void	sigPendInit 	   (struct sigpend *__pSigPend);
extern STATUS	sigPendDestroy 	   (struct sigpend *__pSigPend);
extern STATUS	sigPendKill 	   (TASK_ID __tid, struct sigpend *__pSigPend);
extern STATUS	sigqueueInit 	   (int nQueues);
extern int	sigFfsMsb 	   (sigset_t mask);

#endif /* ! _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsigLibPh */
