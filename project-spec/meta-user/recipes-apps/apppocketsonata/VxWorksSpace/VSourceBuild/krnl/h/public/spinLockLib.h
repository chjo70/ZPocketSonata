/* spinLockLib.h - spin lock library definitions header */

/*
 * Copyright (c) 2006-2007, 2009-2010, 2012, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */
                                                                             
/*
modification history
--------------------
31jan14,to   include vxWorks.h for _WRS_USAGE_WARNING
01q,23may12,cww  Removed unnecessary spinLockCpuState arrays from UP systems
		 (WIND00350319)
01p,27apr10,cww  LP64 adaptation
01o,30oct09,gls  added build warning when ND spinlocks used when DETERMINISTIC
                 VSB used (WIND00188965)
01n,01sep09,gls  aligned nextTicket to the architecture defined value
                 for atomic operations (WIND00136154)
01m,11feb09,gls  added non-deterministic, timed spinlock support
01l,29nov07,h_k  added SPIN_LOCK_ACKNOWLEDGED. (CQ:111571)
01l,30nov07,bha  merge for Q3 release
01k,26oct07,dlk  Address WIND00109150.
01j,14aug07,dlk  In SPIN_LOCK_TRACE case, pass file/line arguments after
                 lock to lessen problems with modules that don't know about
		 these arguments. Also, add one layer of braces in
		 SPIN_LOCK_ISR_DECL initializer to avoid compiler warning.
		 Also, add pTcb member to struct rtSpinlock for optimization.
01i,13aug07,mmi  update spinLockTask structure for ticket-lock implementation
01h,27jun07,gls  added S_spinLockLib_NOT_SPIN_LOCK_CALLABLE
                 added SPIN_LOCK_RESTRICT()
01g,14jun07,rfr  Optimize size of ISR spinlocks
01f,04apr07,rfr  Added Realtime Spinlocks
01e,29mar07,h_k  removed spinLockIsrSingleTake and Give.
01d,08mar07,mmi  add SPIN_LOCK_TRACE
01c,10jan07,h_k  added spinLockIsrSingleTake and spinLockIsrSingleGive.
01b,15dec06,mmi	 fixed SPIN_LOCK_ISR_DECL 
01b,11dec06,mmi	 add trace utility
01a,01nov06,mmi  written
*/

#ifndef __INCspinLockLibh
#define __INCspinLockLibh

#include <vsbConfig.h>
#include <vxWorks.h>	/* to include toolMacros.h for _WRS_USAGE_WARNING */
#include <vwModNum.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define S_spinLockLib_NOT_SPIN_LOCK_CALLABLE    (M_spinLockLib | 1)
#define S_spinLockLib_INVALID_OPERATION         (M_spinLockLib | 2)
#define S_spinLockLib_LOCK_IN_RECOVERY          (M_spinLockLib | 3)
#define S_spinLockLib_LOCK_UNAVAILABLE          (M_spinLockLib | 4)
#define S_spinLockLib_LOCK_TIMEOUT              (M_spinLockLib | 5)

/* 
 * Return ERROR and set errno if a spinlock is held in the context of the
 * running CPU.
 */

#define SPIN_LOCK_RESTRICT() spinLockRestrict()

/*
 * The following definition SPIN_LOCK_TRACE can be uncommented to add useful
 * debugging information to the spinlock data structure. Currently, this
 * information includes the file and line number from which the 
 * spinLockIsrTake () or spinLockTaskTake () was invoked.
 *
 * IMPORTANT: Note that all archives must be rebuilt if SPIN_LOCK_TRACE is
 * defined.  
 */

#if 0
#define SPIN_LOCK_TRACE
#endif

/* 
 * Abstract the underline API to dynamically expand the appropriate code if
 * debugging is enabled for spinLock libraries. 
 *
 * It is assumed that C code never invokes spinLockTaskTake () nor
 * spinLockIsrTake ()  directly. Use of the macros below ensures that
 * spinLockXXXTake will be called with the correct parameters.
 */
   

#define SPIN_LOCK_ISR_INIT(x, y)    (spinLockIsrInit(x, y))

#ifdef SPIN_LOCK_TRACE /* trace the file and line number for debugging */
# define SPIN_LOCK_ISR_TAKE(x)	    (spinLockIsrTake (x, __FILE__, __LINE__))
#else
# define SPIN_LOCK_ISR_TAKE(x)	    (spinLockIsrTake (x) )
#endif /* SPIN_LOCK_TRACE */

#define SPIN_LOCK_ISR_GIVE(x)	    (spinLockIsrGive (x) )

#define SPIN_LOCK_TASK_INIT(x, y)   (spinLockTaskInit(x, y))
#ifdef SPIN_LOCK_TRACE /* trace the file and line number for debugging */
#define SPIN_LOCK_TASK_TAKE(x)	    (spinLockTaskTake (x, __FILE__, __LINE__))
#else
#define SPIN_LOCK_TASK_TAKE(x)	    (spinLockTaskTake (x) )
#endif /* SPIN_LOCK_TRACE */
#define SPIN_LOCK_TASK_GIVE(x)	    (spinLockTaskGive (x) )

/* 
 * Note that these macros are not doing any error checking when SPIN_LOCK_TRACE
 * It's recommended to use the SPIN_LOCK_XXX_INIT () instead if error checking
 * is required
 */ 

#ifdef SPIN_LOCK_TRACE

#define SPIN_LOCK_TASK_DECL(x, flag)			    \
    spinlockTask_t x = { {{0}}, 0, NULL, -1, flag, NULL, 0}

#ifdef _WRS_CONFIG_SMP    
#define SPIN_LOCK_ISR_DECL(x,flag)			    \
    spinlockIsr_t x = { {-1, 0, NULL, 0, {{0}}}, flag, NULL, 0}
#else
#define SPIN_LOCK_ISR_DECL(x,flag)			    \
    spinlockIsr_t x = { {-1, 0}, flag, NULL, 0}
#endif /* _WRS_CONFIG_SMP */

#else /* SPIN_LOCK_TRACE */

#define SPIN_LOCK_TASK_DECL(x, flag)			    \
    spinlockTask_t x = { {{0}}, 0, NULL, -1, flag}

#ifdef _WRS_CONFIG_SMP
#define SPIN_LOCK_ISR_DECL(x, flag)			    \
    spinlockIsr_t x = { {-1, 0, NULL, 0, {{0}}}, flag}
#else
#define SPIN_LOCK_ISR_DECL(x, flag)			    \
    spinlockIsr_t x = { {-1, 0}, flag}
#endif /* _WRS_CONFIG_SMP */

#endif /* SPIN_LOCK_TRACE */

/* Realtime spinlocks */

#define SPIN_LOCK_EMPTY		0
#define SPIN_LOCK_BUSY		1
#define SPIN_LOCK_INTERESTED	2
#define SPIN_LOCK_ACKNOWLEDGED	3

#define SPIN_LOCK_NOBODY	-1

typedef struct
    {
    atomic32_t   flag;	 /* State of this CPU's take of this spinlock */
    unsigned int misses; /* The number of times this CPU has been missed */
    unsigned int nest;   /* number entities attempting a take on this CPU */
#ifdef _WRS_CONFIG_LP64
    UINT32	 pad;	 /* explicit pad for 64-bit alignment */
#endif
    } spinLockCpuState;

typedef struct
    {
    atomic32_t		owner;	   /* CPU index of owner */
    int			key;	   /* The int key for this lock */
#ifdef _WRS_CONFIG_SMP
    void *		pTcb;
    int			intsDone;  /* This CPU processed interrupts during */
				   /* its take */
    spinLockCpuState	cpu[VX_MAX_SMP_CPUS];
#endif
    } rtSpinlock;

/* time limited spin lock */

#define SPINLOCK_OPERATION_OK         0
#define SPINLOCK_OPERATION_ABORTED   -1
#define SPINLOCK_TAKE_RECOVERY       -2

typedef struct spinLockNdTimedKey_s
    {
    UINT64          iterCnt64;
    atomic32_t      state;
    int             key;
    UINT16          prevOwnerId;
    } spinLockNdTimedKey_t;

typedef struct spinLockNdTimed_s
    {
    atomic32_t      state;
    int             options;
    UINT64          iterCnt64;
    UINT64          timeLimitSec;
    UINT64          timeLimitNsec;
    } spinLockNdTimed_t;

/* ISR-callable spinlock data type */

typedef struct spinlockIsr 
    {
    rtSpinlock	lock;
    int		flags;	  /* Reserved for system use  */
#ifdef SPIN_LOCK_TRACE
    int		line;
    char *	file;
#endif
    } spinlockIsr_t;

/* 
 * ATOMIC_ALIGN_SIZE should be defined by the architecture as the alignment
 * value necessary to prevent disruption of an atomic operation due to
 * access to memory locations other than the atomic value aligned to this
 * value.  For many load reserved/store conditional architectures this is
 * simply the cache line size.
 *
 * Currently this defaults to 128 if ATOMIC_ALIGN_SIZE is not defined.  This
 * value is the largest cache line size on all supported architectures.
 */

#ifndef ATOMIC_ALIGN_SIZE
#define _WRS_LOCK_ALIGN_ticket 128
#else
#define _WRS_LOCK_ALIGN_ticket ATOMIC_ALIGN_SIZE
#endif

/* task-only spinLock data type */

typedef struct spinlockTask 
    {
    union
	{
         /*
	  * WIND00136154
	  *
	  * Added alignment of the ticket to the architecture defined value
	  * that ensures atomic operations are not disturbed by access to other
	  * locations.  For many load reserved/store conditional architectures
	  * this is simply a cache line.
	  */

	 char pad [_WRS_LOCK_ALIGN_ticket];
         atomic_t	nextTicket;	    /* ticket for next canditate     */
	} nextTicketAligned;	    

    atomic_t		ticketInService;    /* current ticket being served   */
    void *              pTcb;
    atomic32Val_t	cpuIndex;	    /* cached cpu ID		     */
    int			flags;		    /* Reserved for system use	     */
# ifdef SPIN_LOCK_TRACE
    char *		file;		    /* cache which file we take lock */
    int			line;		    /* cache the line number	     */
# endif
    } spinlockTask_t;

#ifdef SPIN_LOCK_TRACE
typedef void (*SPIN_LOCK_ISR_TAKE_FUNC)  (spinlockIsr_t * lock, char * file,
					  int line);
typedef void (*SPIN_LOCK_TASK_TAKE_FUNC) (spinlockTask_t * lock, char * file,
					  int line);
#else
typedef void (*SPIN_LOCK_ISR_TAKE_FUNC)  (spinlockIsr_t * lock);
typedef void (*SPIN_LOCK_TASK_TAKE_FUNC) (spinlockTask_t * lock);
#endif /* SPIN_LOCK_TRACE */


/* Function prototypes */

extern STATUS spinLockRestrict (void);

/* ISR callable spinLocks functions */

extern void spinLockIsrInit (spinlockIsr_t * lock, int flags);
extern void spinLockIsrGive (spinlockIsr_t * lock);
#ifdef SPIN_LOCK_TRACE
extern void spinLockIsrTake (spinlockIsr_t * lock, char * file, int line);
#else
extern void spinLockIsrTake (spinlockIsr_t * lock);
#endif

/* task callable spinLock functions */

extern void spinLockTaskInit (spinlockTask_t * lock, int flags);
extern void spinLockTaskGive (spinlockTask_t * lock);
#ifdef SPIN_LOCK_TRACE
extern void spinLockTaskTake (spinlockTask_t * lock, char * file, int line);
#else
extern void spinLockTaskTake (spinlockTask_t * lock);
#endif /* SPIN_LOCK_TRACE */

/* time limited spin lock */

#ifdef _WRS_CONFIG_DETERMINISTIC

extern void spinLockNdTimedInit (spinLockNdTimed_t * lock, 
				 struct timespec * pTimeLimit,
				 int options)
	_WRS_USAGE_WARNING("since system has been configured for " \
			   "determinism: VSB option DETERMINISTIC = 'y'");

extern int spinLockNdTimedGive (spinLockNdTimed_t * lock, UINT16 nodeId, 
				spinLockNdTimedKey_t * pKey)
	_WRS_USAGE_WARNING("since system has been configured for " \
			   "determinism: VSB option DETERMINISTIC = 'y'");

extern int spinLockNdTimedTake (spinLockNdTimed_t * lock, UINT16 nodeId, 
				struct timespec * pTimeout, 
				spinLockNdTimedKey_t * pKey)
	_WRS_USAGE_WARNING("since system has been configured for " \
			   "determinism: VSB option DETERMINISTIC = 'y'");

extern UINT16 spinLockNdTimedPrevOwnerGet (spinLockNdTimedKey_t * pKey)
	_WRS_USAGE_WARNING("since system has been configured for " \
			   "determinism: VSB option DETERMINISTIC = 'y'");

#else

extern void spinLockNdTimedInit (spinLockNdTimed_t * lock, 
				 struct timespec * pTimeLimit,
				 int options);

extern int spinLockNdTimedGive (spinLockNdTimed_t * lock, UINT16 nodeId, 
				spinLockNdTimedKey_t * pKey);

extern int spinLockNdTimedTake (spinLockNdTimed_t * lock, UINT16 nodeId, 
				struct timespec * pTimeout, 
				spinLockNdTimedKey_t * pKey);

extern UINT16 spinLockNdTimedPrevOwnerGet (spinLockNdTimedKey_t * pKey);

#endif /* _WRS_CONFIG_DETERMINISTIC */

#ifdef __cplusplus
}
#endif
#endif /* __INCspinLockLibh */
