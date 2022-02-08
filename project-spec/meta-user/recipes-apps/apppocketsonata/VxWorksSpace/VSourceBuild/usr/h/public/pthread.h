/* pthread.h - header for POSIX threads (pthreads) */
 
/*
* Copyright (c) 2003-2007, 2010, 2012-2014, 2016 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/
 
/*
modification history
--------------------
02mar16,cww  fix namespace pollution issue (V7COR-2784)
04nov14,pad  Reworked PTHREAD_RWLOCK_INITIALIZER macro (US44415). Added
             declaration of pthread_rwlockattr_setmaxreaders().
09oct14,sas  Added declarations for rwlocks API's (US47320).
18sep14,sas  Added rwlocks headerfiles and macros (US46077).
11jun13,krz  Integrated pthread barriers.
16mar12,pad  Fixed PTHREAD_MUTEX_INITIALIZER macro (defect 339489).
29jul10,pad  Moved extern C statement after include statements.
08aug07,jpb  Changed PTHREAD_ONCE_INIT to reflect the re-introduction
             of the mutex field in the pthread_once_t structure type.
             Also replaced the non-POSIX FALSE macro with simple zeros.
19jul07,jpb  Changed initialized PTHREAD_ONCE_INIT.
17oct06,pad  Removed conditional blocks related to
             _POSIX_THREAD_PROCESS_SHARED because this macro requires the
             inclusion of unistd.h, which is not allowed by POSIX.1
             (defect #69419 / Fix #69420).
18apr06,mil  Changed PTHREAD_COND_INITIALIZER to add condAttr member.
21mar06,pad  Fixed a couple of function prototypes for conformance (SPR
	     117227). Added PTHREAD_VALID_OBJ and PTHREAD_INVALID. Renamed
	     PTHREAD_INITIALIZED and PTHREAD_DESTROYED into
	     PTHREAD_INITIALIZED_OBJ and PTHREAD_DESTROYED_OBJ.
18feb06,mcm  Hide 'restrict' from compilers that do not support C99.
16feb06,pes  Protect typedefs against multiple definition. Get def
             of pthread_attr_t from base/b_pthread_attr_t.h instead
	     of pthreadCommon.h
09feb06,pad  Added 'restrict' keyword in API where needed. Added
	     _CondAttrClockId field in pthread_condattr_t structure type.
	     Now use a magic number for PTHREAD_INITIALIZED.
26jan06,mil  Pulled out common types into base type files.
11jan06,gls  moved pthread_attr_t to pthreadCommon.h
29nov05,mil  Added condattr_setclock, getclock, and getcpuclockid.
14nov05,rp   added prototypes for pthread_mutexattr_settype and
             pthread_mutexattr_gettype
08nov05,rp   added prototypes for pthread_attr_getstack,
             pthread_attr_setstack, pthread_attr_getguardsize,
             pthread_attr_setguardsize and pthread_mutex_timedlock
01nov05,rp   added prototype for pthread_getconcurrency and
             pthread_setconcurrency
24aug05,kk   move pthread_kill() and pthread_sigmask() to signal.h per
             POSIX
12aug05,pcs  add prototype for pthread_attr_getschedprio
12aug05,pad  Removed field mutexOwner from pthread_mutex_t structure (SPR
             111002).
12aug05,pcs  add prototype for pthread_attr_getschedprio
21jul05,pad  Added inclusion of unistd.h and limits.h. Removed unnecessary
	     inclusion of VxWorks.h.
03jun05,pad  Added prototype of pthread_atfork() for SCA AEP. Moved some
	     macro definitions to limits.h and unistd.h.
25sep04,pad  Added the onceMutex, onceMyTid and onceDone fields to the
	     pthread_once_t structure (fix to SPR #98589).
09sep04,pad  PTHREAD_CANCEL_ASYNCHRONOUS and PTHREAD_CANCEL_DEFERRED macros
             are now defined in pthreadCommon.h
18jun04,pad  Changed value of PTHREAD_CANCELED constant so as to avoid
             confusion with VxWorks ERROR.
04jun04,pad  Added a threadAttrOptions field to the pthread_attr_t
             structure so that task options can be set for threads
	     (SPR 92417).
07may04,pad  Re-instated the _POSIX_THREAD_PRIO_INHERIT and
             _POSIX_THREAD_PRIO_PROTECT macros since they are part of the
             POSIX standard.
19mar04,pad  Provided macro definitions to make all supported routine
             prototypes visible (SPR 94829).
04nov03,pad  created (based on kernel version "01c,22oct01,jgn").
*/
 
#ifndef __INCpthreadh
#define __INCpthreadh

/* includes */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include <unistd.h>
#include <limits.h>
#include <semLib.h>
#endif  /* _POSIX_xxx_SOURCE */
#include <time.h>
#include <sched.h>
#include <pthreadCommon.h>
#include <base/b_pthread_t.h>
#include <base/b_pthread_attr_t.h>
#include <base/b_pthread_mutexattr_t.h>
#include <base/b_pthread_mutex_t.h>
#include <base/b_pthread_condattr_t.h>
#include <base/b_pthread_cond_t.h>
#include <base/b_pthread_rwlockattr_t.h>
#include <base/b_pthread_rwlock_t.h>
#include <base/b_pthread_key_t.h>
#include <base/b_pthread_once_t.h>
#include <base/b_pthread_barrier_t.h>
#include <sys/cdefs.h>          /* for _Restrict */	

/* defines */

#define	PTHREAD_INHERIT_SCHED		0	/* implementation default */
#define	PTHREAD_EXPLICIT_SCHED		1
#define PTHREAD_SCOPE_PROCESS		2
#define PTHREAD_SCOPE_SYSTEM		3	/* implementation default */


#define PTHREAD_ONCE_INIT		{0, 0, 0, NULL, 0}

#define PTHREAD_INITIALIZED_OBJ		0xF70990EF /* object is initialized */
#define PTHREAD_DESTROYED_OBJ		-1	   /* object is destroyed */
#define PTHREAD_VALID_OBJ		0xEC542A37 /* object is valid */
#define PTHREAD_INVALID_OBJ		-1	   /* object is not valid */
#define PTHREAD_UNUSED_YET_OBJ		-1	   /* obj hasn't been used yet*/

#define PTHREAD_MUTEX_INITIALIZER	{NULL, PTHREAD_VALID_OBJ,	\
					PTHREAD_UNUSED_YET_OBJ, 0, 0,	\
					{PTHREAD_INITIALIZED_OBJ,	\
					PTHREAD_PRIO_NONE, 0,		\
					PTHREAD_MUTEX_DEFAULT}}

#define PTHREAD_COND_INITIALIZER	{NULL, PTHREAD_VALID_OBJ,	\
					PTHREAD_UNUSED_YET_OBJ, 0,	\
					NULL, {0, CLOCK_REALTIME}}

#define PTHREAD_RWLOCK_INITIALIZER	{NULL, 0, PTHREAD_VALID_OBJ,	\
					PTHREAD_UNUSED_YET_OBJ,	        \
					{PTHREAD_INITIALIZED_OBJ, 0}}

#define	PTHREAD_CREATE_DETACHED		0
#define	PTHREAD_CREATE_JOINABLE		1   /*.4a and implementation default */

#define PTHREAD_CANCEL_ENABLE		0
#define PTHREAD_CANCEL_DISABLE		1

#define PTHREAD_CANCELED		((void *)-2)

/* values for mutexAttrProtocol */

#define PTHREAD_PRIO_NONE       0
#define PTHREAD_PRIO_INHERIT	1
#define PTHREAD_PRIO_PROTECT	2

/* values for mutexAttrType */

#define PTHREAD_MUTEX_NORMAL		0
#define PTHREAD_MUTEX_ERRORCHECK	1
#define PTHREAD_MUTEX_RECURSIVE		2
#define PTHREAD_MUTEX_DEFAULT		PTHREAD_MUTEX_NORMAL

/* value for pthread_barrier_wait */

#define PTHREAD_BARRIER_SERIAL_THREAD  1

#if defined(__cplusplus)
extern "C" {
#endif	/* __cplusplus */

/*
 * Section 3 Process Primitives	
 */

/* pthread_kill() and pthread_sigmask() are in signal.h.  */

int pthread_atfork (void (*)(void), void (*)(void), void (*)(void));

/* Section 11.3 Mutexes */

int pthread_mutexattr_init    (pthread_mutexattr_t *);
int pthread_mutexattr_destroy (pthread_mutexattr_t *);

int pthread_mutex_init        (pthread_mutex_t * _Restrict,
                               const pthread_mutexattr_t * _Restrict);
int pthread_mutex_destroy     (pthread_mutex_t *);

int pthread_mutex_lock        (pthread_mutex_t *);
int pthread_mutex_timedlock   (pthread_mutex_t * _Restrict,
			       const struct timespec * _Restrict);
int pthread_mutex_trylock     (pthread_mutex_t *);
int pthread_mutex_unlock      (pthread_mutex_t *);

/* Section 11.4 Condition variables */

int pthread_condattr_init     (pthread_condattr_t *);
int pthread_condattr_destroy  (pthread_condattr_t *);

int pthread_cond_init         (pthread_cond_t * _Restrict,
		               const pthread_condattr_t * _Restrict);
int pthread_cond_destroy      (pthread_cond_t *);

int pthread_cond_signal       (pthread_cond_t *);
int pthread_cond_broadcast    (pthread_cond_t *);

int pthread_cond_wait         (pthread_cond_t * _Restrict,
                               pthread_mutex_t * _Restrict);
int pthread_cond_timedwait    (pthread_cond_t * _Restrict,
			       pthread_mutex_t * _Restrict,
			       const struct timespec * _Restrict);

int pthread_condattr_getclock (const pthread_condattr_t * _Restrict,
			       clockid_t * _Restrict);
int pthread_condattr_setclock (pthread_condattr_t *, clockid_t);

int pthread_getcpuclockid     (pthread_t, clockid_t *);

/* Section 11.5 Read Write locks */

int pthread_rwlockattr_init          (pthread_rwlockattr_t *);
int pthread_rwlockattr_destroy       (pthread_rwlockattr_t *);
int pthread_rwlockattr_setmaxreaders (pthread_rwlockattr_t *, 
                                      unsigned int);
int pthread_rwlock_init              (pthread_rwlock_t * _Restrict,
    			              const pthread_rwlockattr_t * _Restrict);
int pthread_rwlock_destroy           (pthread_rwlock_t *);
int pthread_rwlock_rdlock            (pthread_rwlock_t *);
int pthread_rwlock_tryrdlock         (pthread_rwlock_t *);
int pthread_rwlock_timedrdlock       (pthread_rwlock_t * _Restrict,
                                      const struct timespec * _Restrict); 
int pthread_rwlock_wrlock            (pthread_rwlock_t *);
int pthread_rwlock_trywrlock         (pthread_rwlock_t *);
int pthread_rwlock_timedwrlock       (pthread_rwlock_t * _Restrict,
                                      const struct timespec * _Restrict); 
int pthread_rwlock_unlock            (pthread_rwlock_t *);

/* Section 13.5 Thread scheduling */

int pthread_attr_setscope            (pthread_attr_t *, int);
int pthread_attr_getscope            (const pthread_attr_t * _Restrict,
                                      int * _Restrict);

int pthread_attr_setinheritsched     (pthread_attr_t *, int);
int pthread_attr_getinheritsched     (const pthread_attr_t * _Restrict,
				      int * _Restrict);

int pthread_attr_setschedpolicy      (pthread_attr_t *, int);
int pthread_attr_getschedpolicy      (const pthread_attr_t * _Restrict,
				      int * _Restrict);

int pthread_attr_setschedparam       (pthread_attr_t * _Restrict,
				      const struct sched_param * _Restrict);
int pthread_attr_getschedparam       (const pthread_attr_t * _Restrict,
				      struct sched_param * _Restrict);

int pthread_getschedparam            (pthread_t, int * _Restrict,
			              struct sched_param * _Restrict);
int pthread_setschedparam            (pthread_t, int,
                                      const struct sched_param *);
int pthread_setschedprio             (pthread_t, int);

int pthread_mutexattr_setprotocol    (pthread_mutexattr_t *, int);
int pthread_mutexattr_getprotocol    (const pthread_mutexattr_t * _Restrict,
				      int * _Restrict);

int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *, int);
int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t * _Restrict,
				      int * _Restrict);

int pthread_mutexattr_gettype        (const pthread_mutexattr_t * _Restrict,
				      int * _Restrict);
int pthread_mutexattr_settype        (pthread_mutexattr_t *, int);

int pthread_mutex_setprioceiling     (pthread_mutex_t * _Restrict, int,
				      int * _Restrict);
int pthread_mutex_getprioceiling     (const pthread_mutex_t * _Restrict,
				      int * _Restrict);

/* Section 16 Thread management */

int pthread_attr_init           (pthread_attr_t *);
int pthread_attr_destroy        (pthread_attr_t *);

int pthread_attr_setstacksize   (pthread_attr_t *, size_t);
int pthread_attr_getstacksize   (const pthread_attr_t * _Restrict,
                                 size_t * _Restrict);

int pthread_attr_setstackaddr   (pthread_attr_t *, void *);
int pthread_attr_getstackaddr   (const pthread_attr_t * _Restrict,
                                 void ** _Restrict);

int pthread_attr_getstack       (const pthread_attr_t * _Restrict,
			         void ** _Restrict, size_t * _Restrict);
int pthread_attr_setstack       (pthread_attr_t *, void *, size_t);

int pthread_attr_getguardsize   (const pthread_attr_t * _Restrict,
			         size_t * _Restrict);
int pthread_attr_setguardsize   (pthread_attr_t *, size_t);

int pthread_attr_setdetachstate (pthread_attr_t *, int);
int pthread_attr_getdetachstate (const pthread_attr_t *, int *);

int pthread_attr_setopt         (pthread_attr_t *, int);
int pthread_attr_getopt         (pthread_attr_t *, int *);
int pthread_attr_setname        (pthread_attr_t *, char *);
int pthread_attr_getname        (pthread_attr_t *, char **);

void pthread_exit               (void *);
int pthread_create              (pthread_t * _Restrict,
                                 const pthread_attr_t * _Restrict,
			         void * (*)(void *), void * _Restrict);
int pthread_join                (pthread_t, void **);
int pthread_detach              (pthread_t);
pthread_t pthread_self          (void);
int pthread_equal               (pthread_t, pthread_t);
int pthread_once                (pthread_once_t *, void (*)(void));

/* Section 17 Thread-specific data */

int pthread_key_create    (pthread_key_t *, void (*)(void *));
int pthread_key_delete    (pthread_key_t);

int pthread_setspecific   (pthread_key_t, const void *);
void *pthread_getspecific (pthread_key_t);

/* Section 18 Thread cancellation */

int pthread_cancel         (pthread_t);
int pthread_setcancelstate (int, int *);
int pthread_setcanceltype  (int, int *);
void pthread_testcancel    (void);

void pthread_cleanup_push  (void (*)(void *), void *);
void pthread_cleanup_pop   (int);

int pthread_getconcurrency (void);
int pthread_setconcurrency (int);

/* Thread Barriers */

int pthread_barrier_destroy	(pthread_barrier_t *);
int pthread_barrier_init	(pthread_barrier_t * _Restrict,
				 const pthread_barrierattr_t * _Restrict,
				 unsigned);
int pthread_barrier_wait	(pthread_barrier_t *);
int pthread_barrierattr_init	(pthread_barrierattr_t *);
int pthread_barrierattr_destroy	(pthread_barrierattr_t *);

#if defined(__cplusplus)
}
#endif	/* __cplusplus */

#endif /* __INCpthreadh */
