/* signal.h - signal facility library header */

/*
 * Copyright (c) 1992-1994, 2000, 2003-2006, 2009-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
03o,21jun12,pad  Moved the definition of the sigcontext type from sigLibP.h to
                 here since this type is documented (defect 315689).
03n,21mar12,jpb  Moved stack_t and sigset_t definition into their own base 
                 header file (part of defect Defect WIND000307800).
03m,06feb12,kk   fix comment to avoid issues with refgen (WIND00259043)
03l,16nov11,yjw  Add si_code FPE_FLTINV.(WIND00310152) 
            pad  Modified values of non-signal-specific subcodes so that they
	         are unique, in agreement with POSIX.1 specs (defect 310142).
03k,26jan11,pad  Use underscored parameter names in function prototypes as
		 non-prefixed names violate the POSIX namespace rules (defect
		 #248649).
03j,08sep10,cww  Fixed stack_t ss_sp type
03i,15mar10,cww  User side LP64 adaptation
03h,28dec09,jpb  Updated ss_sp field.
03g,10sep09,cww  Kernel side LP64 adaptation
03f,18jun06,gls  added reserved signal definitions
03e,12jun06,pcm  made modifications for pthread cancellation points
03d,14apr06,gls  updated signal number documentation
03c,14mar06,nld  Used macro instead of hard-coded value 64 in sigmask & SIGMASK
                 (fix for SPR 119258)
03b,09mar06,gls  added check for 0 in sigmask() and SIGMASK() for performance
03a,17feb06,pes  Move typedef of pid_t and pthread_t. Note that pid_t has
                 changed from unsigned short to int by this change.
02z,28jan06,mil  Updated for POSIX namespace conformance.
02z,15feb06,scm  correct sigmask macros...
02y,08dec05,gls  added support for additional POSIX signals
02x,07dec05,gls  added missing POSIX signal definitions
02w,22aug05,kk   updated prototype of sigtimedwait() and sigwaitinfo()
02v,19aug05,kk   updated prototype for RTP sigqueue() to conform to POSIX
02u,04aug05,kk   added sys/types.h to get pid_t for POSIX
02t,07feb05,hya  added missing prototype
02s,30sep04,ans  added _rtpSigqueue()
02r,27sep04,ans  updated job control signals documentation.
02q,13sep04,yvp  Added aliases for posix functions to get API uniformity across
                 both kernel/userland.
02p,19may04,ans  alternate signal stack support.
02o,04may04,ans  added SIG_NODEFER
02n,27oct03,nrj  added support for waitpid
02m,17oct03,nrj  added SA_RESTART
02l,14oct03,ans  Moved SIGEV_NONE SIGEV_SIGNAL to sigeventCommon.h
02k,09nov00,jgn  remove inaccurate comment from SIGKILL (SPR #35996)
02j,19jul00,jgn  add thread cancellation signal for pthreads support +
		 update the sigwait prototype to match the POSIX version
02i,11nov94,kdl  provide paramless func ptrs in structs, for non-ANSI (SPR 3742)
02h,10nov94,caf  adjusted placement of _ASMLANGUAGE conditional.
02g,06oct93,yao  added _ASMLANGUAGE conditional.
02h,12jan94,kdl  added sigqueue() prototype.
02g,09nov93,rrr  update to posix 1003.4 draft 14
02f,05feb93,rrr  fixed spr 1986 (SIG_ERR ... prototype) and
		 spr 1906 (signal numbers to match sun os)
02e,15oct92,rrr  silenced warnings
02d,22sep92,rrr  added support for c++
02c,22aug92,rrr  added bsd prototypes.
02b,27jul92,smb  added prototype for raise().
02a,04jul92,jcf  cleaned up.
01b,26may92,rrr  the tree shuffle
01a,19feb92,rrr  written from posix spec
*/

/*
 * ############################### IMPORTANT NOTE ###########################
 *
 * This is a POSIX header file. Any changes to this file must be done with care
 * to maintain the POSIX conformance. Symbols (macros, types, parameter names,
 * etc.) must all follow the POSIX naming conventions (symbol names prefixed
 * with one underscore followed with an upper case letter, or two underscores
 * followed with a lower case letter).
 *
 * Ideally, NO VxWorks-native symbols should be defined here and NO VxWorks-
 * native header files should be included in this header file. If it turns
 * impractical to avoid using VxWorks-native elements then make sure to use the
 * following exclusion logic around the offending elements:
 *
 * #if !defined (_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE) && \
 *     !defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
 * ...
 * #endif  /@ _POSIX_xxx_SOURCE @/
 *
 */

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCsignalh
#define __INCsignalh

#ifndef	_ASMLANGUAGE

#include <base/b_stack_t.h>     /* stack_t */
#include <base/b_sigset_t.h>    /* sigset_t */

#include <sigevent.h>		/* for sigevent structure */

#if !defined (_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE) && \
    !defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#include <sys/types.h>		/* for pid_t for POSIX */
#include <regs.h>		/* for REG_SET */

#define _Siginfo siginfo

struct timespec;

#else   /* _POSIX_xxx_SOURCE */

#include <time.h>		/* for timespec structure */
#include <base/b_pid_t.h>	/* typedef pid_t */

#define _Siginfo

#endif  /* !_POSIX_xxx_SOURCE */

#ifndef _WRS_KERNEL
#include <sys/cdefs.h>          /* for _Restrict */
#include <base/b_pthread_t.h>   /* typedef pthread_t */
#endif /* _WRS_KERNEL */

#endif	/* !_ASMLANGUAGE */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Signal Numbers:
 * 	Required signals	    1-16, 32-38
 * 	Job Control signals	   17-22
 *        These are not implemented for kernel tasks. The default action in
 *        this case is SIG_IGN.
 *        For RTP tasks, these are implemented as per the below signal number
 *        definition.
 *      VxWorks Reserved signals   23-29, 39-47
 *      User Reserved signals      30-31
 * 	Realtime signals	   48-63
 */

#define	SIGHUP	   1	/* hangup */
#define	SIGINT	   2	/* interrupt */
#define	SIGQUIT	   3	/* quit */
#define	SIGILL	   4	/* illegal instruction (not reset when caught) */
#define	SIGTRAP	   5	/* trace trap (not reset when caught) */
#define	SIGABRT    6	/* used by abort, replace SIGIOT in the future */
#define	SIGEMT	   7	/* EMT instruction */
#define	SIGFPE	   8	/* floating point exception */
#define	SIGKILL	   9	/* kill */
#define	SIGBUS	   10	/* bus error */
#define	SIGSEGV	   11	/* segmentation violation */
#define SIGFMT	   12	/* STACK FORMAT ERROR (not posix) */
#define	SIGPIPE	   13	/* write on a pipe with no one to read it */
#define	SIGALRM	   14	/* alarm clock */
#define	SIGTERM	   15	/* software termination signal from kill */
#define SIGCNCL    16	/* pthreads cancellation signal */
#define	SIGSTOP	   17	/* sendable stop signal not from tty */
#define	SIGTSTP	   18	/* stop signal from tty */
#define	SIGCONT	   19	/* continue a stopped process */
#define	SIGCHLD	   20	/* to parent on child stop or exit */
#define	SIGTTIN	   21	/* to readers pgrp upon background tty read */
#define	SIGTTOU	   22	/* like TTIN for output if (tp->t_local&LTOSTOP) */

#define SIGRES1    23   /* reserved signal number (Not POSIX) */
#define SIGRES2    24   /* reserved signal number (Not POSIX) */
#define SIGRES3    25   /* reserved signal number (Not POSIX) */
#define SIGRES4    26   /* reserved signal number (Not POSIX) */
#define SIGRES5    27   /* reserved signal number (Not POSIX) */
#define SIGRES6    28   /* reserved signal number (Not POSIX) */
#define SIGRES7    29   /* reserved signal number (Not POSIX) */

#define	SIGUSR1    30	/* user defined signal 1 */
#define	SIGUSR2    31	/* user defined signal 2 */

#define	SIGPOLL    32	/* pollable event */
#define	SIGPROF    33	/* profiling timer expired */
#define	SIGSYS     34	/* bad system call */
#define	SIGURG     35	/* high bandwidth data is available at socket */
#define	SIGVTALRM  36	/* virtual timer expired */
#define	SIGXCPU    37	/* CPU time limit exceeded */
#define	SIGXFSZ    38	/* file size time limit exceeded */

#define SIGEVTS    39   /* signal event thread send */
#define SIGEVTD    40   /* signal event thread delete */

#define SIGRTMIN   48	/* Realtime signal min */
#define SIGRTMAX   63	/* Realtime signal max */

#define _NSIGS     63

#ifndef _ASMLANGUAGE

/*
 * ANSI Args and returns from signal()
 */

#define SIG_ERR         (void (*)(int))-1
#define SIG_DFL         (void (*)(int))0
#define SIG_IGN         (void (*)(int))1

/*
 * The sa_flags in struct sigaction
 */

#define SA_NOCLDSTOP	0x0001	/* Do not generate SIGCHLD when child stops */
#define SA_SIGINFO	0x0002	/* Pass additional siginfo structure */
#define SA_ONSTACK	0x0004	/* Run on sigstack */
#define SA_INTERRUPT	0x0008	/* (Not posix) Don't restart the function */
#define SA_RESETHAND	0x0010	/* (Not posix) Reset the handler, like sysV */
#define SA_RESTART	0x0020	/* (Not posix) restart the system call */
#define SA_NODEFER      0x0040  /*
                                 * signal not automatically blocked on entry
                                 * to signal handler
                                 */
#define SA_NOCLDWAIT    0x0080  /* no zombie created on child death */

/*
 * The how in sigprocmask()
 */

#define SIG_BLOCK	1
#define SIG_UNBLOCK	2
#define SIG_SETMASK	3

/*
 * The non-signal-specific si_code returned in siginfo
 */

#define SI_SYNC		0	/* (Not posix) gernerated by hardware */
#define SI_USER		-1 	/* signal from kill() function */
#define SI_QUEUE	-2	/* signal from sigqueue() function */
#define SI_TIMER	-3	/* signal from expiration of a timer */
#define SI_ASYNCIO	-4	/* signal from completion of async I/O */
#define SI_MESGQ	-5	/* signal from arrival of a message */
#define SI_CHILD	-6	/* signal from child, stopped or terminated */
#define SI_KILL		SI_USER	/* signal from kill() function */

/*
 * The signal-specific si_code returned in siginfo
 *
 * These macros are not to be made visible to the POSIX-conforming
 * applications when _POSIX_C_SOURCE is set to 200112L.
 */

#if (_POSIX_C_SOURCE != 200112L) || defined (_XOPEN_SOURCE) || \
    defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)  /* XSI options */

/* SIGILL codes */

#define ILL_ILLOPC      1	/* Illegal opcode */
#define ILL_ILLOPN      2	/* Illegal operand */
#define ILL_ILLADR      3	/* Illegal addressing mode */
#define ILL_ILLTRP      4	/* Illegal trap */
#define ILL_PRVOPC      5	/* Priviledged instruction */
#define ILL_PRVREG      6	/* Priviledged register */
#define ILL_COPROC      7	/* Coprocessor error */
#define ILL_BADSTK      8	/* Internal stack error */

/* SIGFPE codes */

#define FPE_INTDIV      1	/* Integer divide by zero */
#define FPE_INTOVF      2	/* Integer overflow */
#define FPE_FLTDIV      3	/* Floating-point divide by zero */
#define FPE_FLTOVF      4	/* Floating-point overflow */
#define FPE_FLTUND      5	/* Floating-point underflow */
#define FPE_FLTRES      6	/* Floating-point inexact result */
#define FPE_FLTINV      7   /* Invalid floating-point operation */
#define FPE_FLTSUB      8	/* Subscript out of range */

/* SIGSEGV codes */

#define SEGV_MAPERR     1	/* Address not mapped to object */
#define SEGV_ACCERR     2	/* Invalid permissions for mapped object */

/* SIGBUS codes */

#define BUS_ADRALN      1	/* Invalid address alignment */
#define BUS_ADRERR      2	/* Nonexistent physical memory */
#define BUS_OBJERR      3	/* Object-specific hardware error */

/* SIGTRAP codes */

#define TRAP_BRKPT      1	/* Process breakpoint */
#define TRAP_TRACE      2	/* Process trap trace */

/* SIGCHLD codes */

#define CLD_EXITED      1	/* Child has exited */
#define CLD_KILLED      2	/* Child has terminated abnormally (no core) */
#define CLD_DUMPED      3	/* Child has terminated abnormally */
#define CLD_TRAPPED     4	/* Traced child has trapped */
#define CLD_STOPPED     5	/* Child has stopped */
#define CLD_CONTINUED   6	/* Stopped child has continued */

/* SIGPOLL codes */

#define POLL_IN         1	/* Data input available */
#define POLL_OUT        2	/* Output buffers available */
#define POLL_MSG        3	/* Input message available */
#define POLL_ERR        4	/* I/O error */
#define POLL_PRI        5	/* High priority input available */
#define POLL_HUP        6	/* Device disconnected */

#endif  /* _POSIX_xxx_SOURCE */

typedef unsigned char sig_atomic_t;

typedef struct _Siginfo
    {
    int			si_signo;
    int			si_code;
    union sigval	si_value;
    } siginfo_t;

struct sigaction
    {
    union
	{
	void		(*__sa_handler)(int);
	void		(*__sa_sigaction)(int, siginfo_t *, void *);
	}		sa_u;
#define sa_handler	sa_u.__sa_handler
#define sa_sigaction	sa_u.__sa_sigaction
    sigset_t		sa_mask;
    int			sa_flags;
    };


/*
 * From here to the end is not posix, it is for bsd compatibility.
 */

#if !defined (_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE) && \
    !defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#define SV_ONSTACK      SA_ONSTACK
#define SV_INTERRUPT    SA_INTERRUPT
#define SV_RESETHAND    SA_RESETHAND

/*
 * If the signal number is greater than (_NSIGS + 1) or less than or equal to
 * 0 then the mask is empty.  Immediately return 0.  This is an optimization.
 */

#define sigmask(m) (((m <= 0) || (m > (_NSIGS + 1))) ? \
                    (sigset_t) 0 : ((sigset_t) 1 << ((m) - 1)))

#define SIGMASK(m) (((m <= 0) || (m > (_NSIGS + 1))) ? \
                    (sigset_t) 0 : ((sigset_t) 1 << ((m) - 1)))

struct sigvec
    {
    void (*sv_handler)(int);    /* signal handler */
    sigset_t sv_mask;                /* signal mask to apply */
    int      sv_flags;               /* see signal options */
    };

struct sigcontext
    {
    int			sc_onstack;
    int			sc_restart;
    sigset_t		sc_mask;
    struct siginfo	sc_info;
    REG_SET		sc_regs;
    REG_SET		*sc_pregs;
    };

/* end for bsd compatibilty */

struct rtpSigCtx;

#endif  /* _POSIX_xxx_SOURCE */

/* Bit definitions for ss_flags */

#define SS_DISABLE 0x1
#define SS_ONSTACK 0x2

#define MINSIGSTKSZ 1024
#define SIGSTKSZ  MINSIGSTKSZ * 4

/* prototypes */

extern void 	(*signal (int __sig, void (*__handler)(int)))(int);

extern int      raise (int __signo);
extern int 	sigemptyset (sigset_t * __set);
extern int 	sigfillset (sigset_t * __set);
extern int 	sigaddset (sigset_t * __set, int __signo);
extern int 	sigdelset (sigset_t * __set, int __signo);
extern int 	sigismember (const sigset_t * __set, int __signo);
extern int 	sigpending (sigset_t * __set);
extern int 	sigsuspend (const sigset_t * __sigmask);


#if !defined (_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE) && \
    !defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

extern int 	sigvec (int __sig, const struct sigvec * __vec,
		        struct sigvec * __ovec);
extern int      sigaltstack     (const stack_t * __ss, stack_t * __oss);
extern int 	sigsetmask (int __mask);
extern int 	sigblock (int __mask);
extern STATUS	_sigqueue	(RTP_ID rtpId, int signo,
				 const union sigval * pValue, int sigCode);
extern int 	_sigsuspend	(const sigset_t * __sigmask);
extern int 	_sigtimedwait (const sigset_t * __set, siginfo_t * __value,
			       const struct timespec *);
#endif  /* _POSIX_xxx_SOURCE */

#ifndef _WRS_KERNEL		/* user-mode API's */

extern int	kill		(pid_t __pid, int __signo);
extern int	sigqueue	(pid_t __pid, int __signo,
				 const union sigval __value);
extern int      sigaction       (int __sig,
                                 const struct sigaction *_Restrict __act,
                                 struct sigaction *_Restrict __oact);
extern int      sigprocmask     (int __how, const sigset_t *_Restrict __set,
                                 sigset_t *_Restrict __oset);
extern int      sigwait         (const sigset_t *_Restrict __set,
                                 int *_Restrict __signo);
extern int      sigwaitinfo     (const sigset_t *_Restrict __set,
                                 siginfo_t *_Restrict __value);
extern int      sigtimedwait    (const sigset_t *_Restrict __set,
                                 siginfo_t *_Restrict __value,
                                 const struct timespec *_Restrict __timeout);

#if !defined (_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE) && \
    !defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern int	taskKill	(TASK_ID taskId, int signo);
extern int	taskSigqueue	(TASK_ID taskId, int signo,
				 const union sigval value);
extern int	_taskSigqueue	(TASK_ID taskId, int signo,
				 const union sigval * pValue, int sigCode);
#endif  /* _POSIX_xxx_SOURCE */

/* thread APIs */

int pthread_sigmask	(int __how, const sigset_t * __set, sigset_t * __oset);
int pthread_kill	(pthread_t __athread, int __sig);

/* These aliases provide consistent meaning in both kernel & user modes */

#if !defined (_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE) && \
    !defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#define rtpKill(rtpId, signo)		kill((rtpId), (signo))
#define rtpSigqueue(rtpId, signo, value)	\
                                    sigqueue((rtpId), (signo), (value))
#define _rtpSigqueue(rtpId, signo, value, code)	\
                                    _sigqueue((rtpId), (signo), (value), (code))
#define taskRaise(signo)		taskKill(taskIdCurrent, (signo))
#define rtpRaise(signo)			raise((signo))
#endif  /* _POSIX_xxx_SOURCE */

#else  /* _WRS_KERNEL */

extern int	kill		(TASK_ID __tid, int __signo);
extern int	sigqueue	(TASK_ID tid, int signo,
				 const union sigval value);
extern int      sigaction       (int __sig,
                                 const struct sigaction * __act,
                                 struct sigaction * __oact);
extern int      sigprocmask     (int __how, const sigset_t * __set,
                                 sigset_t * __oset);
extern int      sigwait         (const sigset_t * __set,
                                 int * __signo);
extern int      sigwaitinfo     (const sigset_t * __set,
                                 siginfo_t * __value);
extern int      sigtimedwait    (const sigset_t * __set,
                                 siginfo_t * __value,
                                 const struct timespec * __timeout);

/* These aliases provide consistent meaning in both kernel & user modes */

#define taskKill(tid, signo)		kill((tid), (signo))
#define taskRaise(signo)		raise((signo))
#define taskSigqueue(tid, signo, value)	sigqueue((tid), (signo), (value))

#endif /* _WRS_KERNEL */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsignalh */
