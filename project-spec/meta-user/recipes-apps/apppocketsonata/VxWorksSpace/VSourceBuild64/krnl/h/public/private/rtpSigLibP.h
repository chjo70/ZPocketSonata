 /* rtpSigLibP.h - private RTP signal library header */

/*
 * Copyright (c) 2003-2005, 2007, 2010, 2012-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20apr15,gls  removed rtpChildHandleGet()
23sep14,gls  made RTP signals a component
15may13,cww  Extended isInSigHandler() from sigLibP.h (WIND00417069)
29jun12,jpb  Finished merge for Defect WIND00307800.
29feb12,jpb  Defect WIND00307800.  Updated RTP_SIG_CTX structure to 
             maintain ucontext_t info.
01sep10,jpb  Added function pointer _func_rtpTaskSigCheck.
02mar10,cww  LP64 adaptation
17sep07,gls  moved public APIs to rtpLib.h (Defect #00102843)
11may05,gls  added OBJ_HANDLE to rtpChildWait() (SPR #109170)
             added rtpChildIdGet() (SPR #106428)
             added rtpChildHandleGet() (SPR #109349)
             updated copyright notice
29sep04,ans  added _rtpSigqueue ()
24sep04,ans  Added RTP_TASK_MINI_SIG_CB to RTP_SIG_CB
18may04,ans  alternate signal stack support.
17may04,ans  added parent signal mask inheritance support.
11feb04,ans  added support for sigwait() related calls.
01dec03,nrj  coding std changes
25nov03,nrj  code review mods
27oct03,nrj  added support for waitpid
22oct03,nrj  added extern defs for API
16oct03,nrj  added syscall state save in sigctx
15oct03,nrj  added extern decl and fixed sigsuspend mask issue
11oct03,nrj  created.
*/

#ifndef	__INCrtpSigLibPh
#define	__INCrtpSigLibPh

#ifdef	_ASMLANGUAGE
#else	/* _ASMLANGUAGE */

/* includes */

#include <vxWorks.h>
#include <sigLib.h>
#include <dllLib.h>
#include <private/sigLibP.h>
#include <ucontext.h>		/* ucontext_t */

#ifdef __cplusplus
extern "C" {
#endif

/* macros */

/*
 * Following macros are used by Signal delivery mechanism.
 * When signal is delivered (carving user handler ctx) these
 * macros values are stored with saved ctx. When the Sig handler
 * returns, One of these is set and return takes action further on.
 */

#define		SIG_DELIVERED_IN_WINDCTX	0x0000
#define		SIG_DELIVERED_IN_EXCEPTION	0x0010
#define		SIG_DELIVERED_IN_SYSCALL	0x0100
#define		SIG_DELIVERED_SYSCALL_RESTART	0x0001
#define		SIG_DELIVERED_WITH_SYSCALL_RESTART         \
			(SIG_DELIVERED_IN_SYSCALL |        \
			SIG_DELIVERED_SYSCALL_RESTART)

/*
 * Following macros are used when task wishes to wait for
 * a child RTP to die or wait for some signal.
 * When task initiates wait for signal/child it is added to the
 * wait List with RTP control block.
 * When a signal arrives, the task is woken
 * up and based on these macro value, it is unqueued from RTP
 */

#define         SIG_TASK_NOT_QUEUED             0
#define         SIG_TASK_QUEUED_SIGWAIT         1
#define         SIG_TASK_QUEUED_CHILDWAIT       2
#define         SIG_TASK_QUEUED_SYNCSIG         3

/* typedefs */

/* To deliver a RTP signal we do following
 * a) Save the current context
 * b) create new context to run user-mode signal handler
 * c) Resume to new context and run sig handler
 * d) After signal handler finishes resume to saved context
 *
 * Following sigctx is used in step (a) and (d). The mem for
 * this is allocated from tasks's user-mode stack.
 */

typedef struct rtpSigCtx
    {
    int                 type;           /* one of above macros */
    int                 scn;            /* intrptd syscall number */
    long                args[8];        /* args of intrptd syscall */
    siginfo_t           info;           /* signal info, passed to handler */
    ucontext_t          ctx;            /* information on context */
    } RTP_SIG_CTX;

/*
 * The signal can be generated for RTP and task . So both have
 * signal control blocks in addition to their own control 
 * block.
 * The Signal control block (SIG_CB) for both share some
 * common properties and differ in some other.
 * For signal-internal users like timer/IO/child-die, it is desired
 * to provide uniform interface. (see sigpend struct in sigLibP.h)
 * Sigpend data struct and TCB only provides one "pointer" to for
 * Signal-Control-block. Signal lib internally cast these pointer as
 * per its own allocated data struct (SIG_CB).
 */

typedef enum rtpTcbCmnType 
    {
    SIG_CB_TCB,
    SIG_CB_RTP
    } RTP_TCB_CMN_TYPE;


typedef struct rtpTaskMiniSigCb
   {
   BOOL                 isSigCbInitialized;
#ifdef _WRS_CONFIG_LP64
   int                  pad;
#endif /* _WRS_CONFIG_LP64 */
   sigset_t             parentSigMask;
   } RTP_TASK_MINI_SIG_CB;
 
/*
 * Common data struct for RTP and Task SIGnal control block
 */

typedef struct rtpSigTcbRtpCmn
    {
    /* sigMini should be the first item of this structure */

    RTP_TASK_MINI_SIG_CB sigMini;                        /* minimal signal CB */
    DL_NODE		cmnRtpSigWaitNode;		/* node for tasks */
    struct sigq		cmnSigQHead[_NSIGS + 1];	/* qed signals */
    sigset_t		cmnKillSigs;			/* which kill sigs */
    sigset_t		cmnQueuedSigs;			/* if qed, which */
    union
	{
	struct wind_rtp	* pRtpId;
	WIND_TCB	* pTid;
        } cmnOwnerId;

#define sigCmnRtpId cmnOwnerId.pRtpId
#define sigCmnTid cmnOwnerId.pTid

    RTP_TCB_CMN_TYPE    cmnRtpOrTcb;            /* is it RTP or TCB */
#ifdef _WRS_CONFIG_LP64
   int                  pad;
#endif /* _WRS_CONFIG_LP64 */
    } RTP_SIG_TCB_RTP_CMN;

/*
 * RTP signal control block.
 * static part of WIND_RTP & not allocated dynamically
 */

typedef struct rtpSigCB
    {
    /* sigCmnControlBlock should be the first item of this structure */

    RTP_SIG_TCB_RTP_CMN	sigCmnControlBlock;
    struct sigpend	* pSigQ;		/* pool for Sigqueue */
    struct sigaction	sigVector[_NSIGS + 1];	/* Sigaction user handlers */
    } RTP_SIG_CB;

typedef struct sigwait_
    {
    sigset_t            waitsigs;               /* wait signal mask */
    siginfo_t           waitinfo;               /* wait signal info */
    } SIG_WAIT;

/*
 * TASK signal control block.
 * "pTcb->pSignalInfo "
 *
 * IMPORTANT - do not confuse it with **Kernel task's** sigtcb
 *
 * NOTE that for kernel task pSignalInfo--> points to sigtcb
 * and for RTP task pSignalInfo--> points to rtpsigtcb
 * It is allocated dynamically only when required.
 */

typedef struct rtpTaskSigCB
    {
    /* sigCmnControlBlock should be the first item of this structure */

    RTP_SIG_TCB_RTP_CMN	sigCmnControlBlock;	/* common part of SIG_CB */
    sigset_t		blockedSigs;		/* Mask of Task */
    sigset_t		savedBlockedSigs;	/* temp storage for mask */
    INT32		qState;			/* qued for sig/child */
    int			nestedCount;		/* sanity check sigreturn */
    SIG_WAIT          * pSigwait;               /* task signal wait info */
    struct wind_rtp   * childRtpId;		/* child rtpId to wait for */
    stack_t             signalStack;            /* alternate signal stack */
    } RTP_TASK_SIG_CB;

/*
 * struct sigpend is defined in sigLibP.h, it is used by many services
 * including timer, posix message, aio drivers ...
 * We use the same struct for easy porting of those services
 * to RTP universe.
 */

typedef struct sigpend RTP_SIG_PEND;

/*
 * For ease of source code reading 
 */

#define sigQHead	sigCmnControlBlock.cmnSigQHead
#define killSigs	sigCmnControlBlock.cmnKillSigs
#define queuedSigs	sigCmnControlBlock.cmnQueuedSigs
#define rtpOrTcb	sigCmnControlBlock.cmnRtpOrTcb
#define sigCBRtpId	sigCmnControlBlock.cmnOwnerId.pRtpId
#define sigCBTid	sigCmnControlBlock.cmnOwnerId.pTid
#define rtpSigwaitNode	sigCmnControlBlock.cmnRtpSigWaitNode

/* externs */

/* RTP childWait function pointer */

extern RTP_ID (*_func_rtpChildWait)
    (
    struct wind_rtp * pChildRtp,    /* which child to wait for */
    OBJ_HANDLE      * pObjHandle,   /* returned handle of child */
    int             * pRetStatus,   /* return status of child */
    int               options       /* how to wait/status options */
    );

/* RTP parentDeleteNotify function pointer */

extern STATUS (*_func_rtpParentDeleteNotify)
    (
    struct wind_rtp * pRtp,       /* notify parent of this RTP */
    int               delStatus
    );

/* RTP pause function pointer */

extern int (*_func_rtpPause) (void);

/* RTP sigaction function pointer */

extern int (*_func_rtpSigaction) (int signo, const struct sigaction * pAct, 
                                  struct sigaction * pOact, void * retAddr);

/* RTP task signal exception processing */

extern STATUS (*_func_rtpSigExcKill)
    (
    int       signalNum,        /* POSIX signal number */
    int       signalSubcode,    /* POSIX "si_code" */
    int       faultType,        /* hardware exception vector or type */
    void *    faultAddr,        /* address where the exception occured */
    REG_SET * pRegs             /* architecture's register set */
    );

/* RTP Signal pend dest function pointer */

extern int (*_func_rtpSigPendDestroy) (RTP_SIG_PEND  * pSigPend);

/* RTP sigpending function pointer */

extern int (*_func_rtpSigpending) (sigset_t  * pSet);

/* RTP Signal pend init function pointer */

extern STATUS (*_func_rtpSigPendInit) (RTP_SIG_PEND * pSigPend);

/* RTP Signal RTP Kill function pointer */

extern STATUS (*_func_rtpSigPendKill) (RTP_ID pRtpId, RTP_SIG_PEND * pSigPend);

/* RTP sigprocmask function pointer */

extern int (*_func_rtpSigprocmask) (int how, const sigset_t * pSet,
                                    sigset_t *pOset );

/* RTP sigqueue function pointer */

extern int (*_func_rtpSigqueue) (RTP_ID rtpId, int signo, 
                                 const union sigval value);

/* RTP sigQueueDelete function pointer */

extern void (*_func_rtpSigQueueDelete) (struct wind_rtp * pRtp);

/* RTP sigQueueInit function pointer */

extern STATUS (*_func_rtpSigQueueInit) (struct wind_rtp * pRtp, int nQueues);

/* RTP sigsuspend function pointer */

extern int (*_func_rtpSigsuspend) (const sigset_t   *pSet);

/* RTP sigtimedwait function pointer */

extern int (*_func_rtpSigtimedwait) (const sigset_t * pSet,
                                     struct siginfo * pInfo,
                                     const struct timespec * pTimeout);

/* RTP Signal system call check function pointer */

extern BOOL	(*_func_rtpSyscallSigCheck) (void);

/* RTP Signal system call sigDeliver function pointer */

extern void	(*_func_rtpSyscallSigDeliver) (REG_SET * pRegs);

/* RTP Signal RTP Task Kill function pointer */

extern int (*_func_rtpTaskKill)        (TASK_ID tid, int signo);
extern int (*_func_rtpTaskSigPendKill) (WIND_TCB * pTcb,
                                        RTP_SIG_PEND * pSigPend);

/* RTP Signal RTP Kill function pointer */

extern int (*_func_rtpKill)        (RTP_ID rtpId, int signo);

/* RTP Signal RTP Task queue function pointer */

extern int (*_func_rtpTaskSigqueue)  (TASK_ID tid, int signo,
                                     const union sigval value);
extern void (*_func_rtpTaskSigBlock) (WIND_TCB * pTcb);

/* RTP Signal RTP Task signal check function pointer */

extern STATUS (*_func_rtpTaskSigCheck)(WIND_TCB * pTcb);

/* RTP zombieCleanup function pointer */

extern STATUS (*_func_rtpZombieCleanup) (RTP_ID rtpId);

/* RTP _rtpSigqueue function pointer */

extern int    (*_func__rtpSigqueue)    (RTP_ID rtpId, int signo,
                                        const union sigval value, 
                                        int sigCode);

/* RTP _rtpTaskSigqueue function pointer */

extern int    (*_func__rtpTaskSigqueue)   (WIND_TCB * pTcb, int signo,
                                           const union sigval value, 
                                           int sigCode);
/* RTP sigReturn function pointer */

extern void   (*_func_rtpSigReturn) (void);

/* RTP childIdGet function pointer */

extern struct wind_rtp * (*_func_rtpChildIdGet) (OBJ_HANDLE objHandle);

/* RTP sigaltstack function pointer */

extern STATUS     (*_func_rtpSigaltstack) (const stack_t * ss, stack_t * oss);

/* RTP _rtpSyscallSigCheck function pointer */

extern BOOL	  (*_func__rtpSyscallSigCheck) (void);

/* RTP _rtpSyscallSigDeliverfunction pointer */

extern void	  (*_func__rtpSyscallSigDeliver) (REG_SET * pRegs);

/* exported functionality - not all are system call */

extern STATUS     rtpSigLibInit      (void);
extern STATUS     rtpSigQueueInit    (RTP_ID rtpId, int nQueues);
extern void       rtpSigQueueDelete  (RTP_ID rtpId);
extern STATUS     rtpSigaction       (int signo, const struct sigaction * pAct,
				      struct sigaction * pOact, void * retAddr);
extern STATUS     rtpSigprocmask     (int how, const sigset_t * pSet,
                                      sigset_t * pOset);
extern STATUS     rtpSigaltstack     (const stack_t * ss, stack_t * oss);
extern STATUS     rtpSigpending      (sigset_t * pSet);
extern int        rtpSigsuspend      (const sigset_t * pSet);
extern int        rtpPause           (void);
extern STATUS     _rtpTaskSigqueue   (WIND_TCB * pTcb, int signo,
                                      const union sigval value, int sigCode);
extern STATUS     rtpTaskSigPendKill (WIND_TCB * pTcb,
                                      struct sigpend * pSigPend);
extern STATUS     _rtpSigqueue       (RTP_ID rtpId, int signo,
                                      const union sigval value, int sigCode);
extern STATUS     rtpSigPendKill     (RTP_ID rtpId, struct sigpend * pSigPend);
extern STATUS     rtpSigPendInit     (RTP_SIG_PEND * pSigPend);
extern STATUS     rtpSigPendDestroy  (RTP_SIG_PEND * pSigPend);
extern void       rtpSigReturn (void);
extern RTP_ID     rtpChildIdGet      (OBJ_HANDLE objHandle);
extern RTP_ID     rtpChildWait       (RTP_ID childRtpId,
                                      OBJ_HANDLE * pObjHandle,
                                      int * pRetStatus, int options);
extern int        rtpSigtimedwait    (const sigset_t * pSet,
                                      struct siginfo * pInfo,
                                      const struct timespec * pTimeout);
extern int        rtpSigwaitinfo     (const sigset_t * pSet,
                                      struct siginfo * pInfo);
extern int rtpSigwait (const sigset_t *pSet, int *pSig);

extern BOOL       rtpSyscallSigCheck (void);
extern void       rtpSyscallSigDeliver (REG_SET * pRegs);
extern STATUS     rtpParentDeleteNotify (RTP_ID rtpId, int delStatus);
extern STATUS     rtpZombieCleanup   (RTP_ID rtpId);

/*****************************************************************************
*
* isInSigHandler - check if in signal context
*
* Check if executing in signal context.
*
* RETURNS: TRUE if in signal context, FALSE otherwise
*
* ERRNO:  N/A
*
* \NOMANUAL
*/

_WRS_INLINE BOOL isInSigHandler
    (
    WIND_TCB * pTcb
    )
    {
    if (IS_KERNEL_TASK (pTcb))
	{
	if (pTcb->pSignalInfo != NULL &&
	    pTcb->pSignalInfo->pSigContext != NULL)
	    {
	    return TRUE;
	    }
	}
    else
	{
	RTP_TASK_SIG_CB * pSigCb = (RTP_TASK_SIG_CB *) pTcb->pSignalInfo;

	if (pSigCb->sigCmnControlBlock.sigMini.isSigCbInitialized &&
	    pSigCb->nestedCount != 0)
	    {
	    return TRUE;
	    }
	}
    return FALSE;
    }

#ifdef __cplusplus
}
#endif

#endif	/* _ASMLANGUAGE */

#endif	/* __INCrtpSigLibPh */
