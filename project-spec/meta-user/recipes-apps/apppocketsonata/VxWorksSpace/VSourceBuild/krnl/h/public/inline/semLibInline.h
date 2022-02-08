/* semLibInline.h - inline semaphore library header file */

/*
 * Copyright (c) 2008-2010, 2014, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
09nov15,h_k  fixed typos in comments. (V7COR-3673)
16jul15,h_k  updated semMGive_inline() and semMTake_inline() to improve
             fast path performance in the case SEM_NO_ID_VALIDATE option is
             not set in SMP. (V7COR-2775)
06nov14,jpb  static analysis defects
20may14,jpb  V7COR-1084: Fixed typo of semaphore.
07jul10,pcs  change the data type of timeout from an int to _Vx_ticks_t
06may10,cww  64-bit SMP update
23mar10,gls  fixed build warnings
14dec09,kk   fix user build warnings (WIND00194092)
21sep09,s_s  changed INT_CPU_LOCK() and INT_CPU_UNLOCK() to
                 KERNEL_INT_CPU_LOCK() and KERNEL_INT_CPU_UNLOCK()
		 (WIND00181479)
26aug09,gls  removed duplicate documentation (WIND00179315)
06aug09,jpb  Fixed build warnings.
28may09,kk   fix doc for SEM_INVERSION_SAFE
15may09,gls  removed memory barrier for recursive mutex give
12mar09,jpb  VSB consideration.
29may09,cww  Changed 3rd param in workQAdd2
18mar09,cww  LP64 update
27feb09,cww  update workQAdd for LP64
11feb09,zl   removed qLib.h inclusion
11sep08,gls  moved check for consistent options to after ID validation
                 added SEM_EVENTSEND_ERR_NOTIFY to options mask (Defect #132659)
27aug08,jpb  Renamed VSB header file
04aug08,gls  added check for interrupt context before event send
04jul08,gls  written
*/

#ifndef __INCsemLibInlineh
#define __INCsemLibInlineh

#include <vxWorks.h>
#include <semLib.h>

#ifndef _ASMLANGUAGE
#include <vsbConfig.h>
#include <stdarg.h>
#include <intLib.h>
#include <errnoLib.h>

/*
 * The following private header files are necessary for the implementation of
 * the inline APIs.  The contents of these files are subject to change without
 * notice.
 */

#include <private/qLibP.h>
#include <private/semLibP.h>
#include <private/windLibP.h>
#include <private/kernelLibP.h>

#ifndef _WRS_CONFIG_SMP
#include <private/sigLibP.h>
#include <private/intLibP.h>
#endif /* WRS_CONFIG_SMP */

#endif /* _ASMLANGUAGE */

/* option masks for the types of semaphores */

#define SEM_BIN_OPTIONS_MASK_INLINE	(SEM_Q_FIFO | 			      \
				         SEM_Q_PRIORITY | 		      \
				         SEM_INTERRUPTIBLE |                  \
				         SEM_EVENTSEND_ERR_NOTIFY |           \
                                         SEM_NO_ID_VALIDATE |                 \
                                         SEM_NO_ERROR_CHECK |                 \
                                         SEM_NO_EVENT_SEND  |                 \
                                         SEM_NO_SYSTEM_VIEWER)

#define SEM_MUT_OPTIONS_MASK_INLINE	(SEM_BIN_OPTIONS_MASK_INLINE |        \
                                         SEM_DELETE_SAFE |                    \
                                         SEM_INVERSION_SAFE |                 \
                                         SEM_NO_RECURSE)


#if !defined (_ASMLANGUAGE)

/*******************************************************************************
*
* semMGive_inline - give a mutex semaphore (inline version)
*
* This routine gives a mutex semaphore.
*
* The behavior of this routine is similar to that of semGive() on a mutex 
* semaphore, differing only in that an additional parameter, <options>, must 
* be specified.  The semaphore specified by <semId> must be of mutex type.
*/

#ifndef _WRS_CONFIG_SMP

/* begin UP version of semMGive_inline() */

_WRS_INLINE STATUS semMGive_inline
    (
    SEM_ID	semId,               /* semaphore ID to give */
    int		options              /* semaphore options */
    )
    {
    int		level;
    int         kernWork = 0;
    STATUS      retStatus;
    WIND_TCB *  tCurrent;

    if (options & ~SEM_MUT_OPTIONS_MASK_INLINE)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

#ifdef  _WRS_CONFIG_SV_INSTRUMENTATION
    if ((options & SEM_NO_SYSTEM_VIEWER) == 0)
	{
        /* system viewer - level 1 event logging */
        EVT_OBJ_3 (semId, semClassId, EVENT_SEMGIVE,
                   semId, SEM_OWNER(semId), semId->recurse);
	}
#endif  /* _WRS_CONFIG_SV_INSTRUMENTATION */

    if ((options & SEM_NO_ERROR_CHECK) == 0)
	{
	if (_WRS_INT_RESTRICT () != OK)		/* restrict isr use */
	    return (ERROR);
	}

    tCurrent = taskIdCurrent;

    OBJ_LOCK (semClassId, level);

#ifdef _WRS_CONFIG_OBJECT_VERIFICATION
    if ((options & SEM_NO_ID_VALIDATE) == 0)
	{
	if (OBJ_VERIFY (semId, semClassId) != OK)	/* check validity */
	    {
	    OBJ_UNLOCK (semClassId, level);
	    return (ERROR);
	    }
	}
#endif

    if ((options & SEM_NO_ERROR_CHECK) == 0)
	{
	/* 
	 * Verify that both SEM_DELETE_SAFE and SEM_INVERSION safe are
	 * specified consistently between the <options> parameter and the
	 * options passed at creation/initialization of this semaphore.
	 *
	 * NOTE:  This is done after the semaphore ID is validated, if
	 *        object validation is enabled.
	 */

	if ((semId->options & (SEM_DELETE_SAFE | SEM_INVERSION_SAFE)) !=
	    (options & (SEM_DELETE_SAFE | SEM_INVERSION_SAFE)))
	    {
	    OBJ_UNLOCK (semClassId, level);
	    errno = S_semLib_INVALID_OPTION;
	    return (ERROR);
	    }

	if (SEM_OWNER (semId) != tCurrent)	/* check for ownership */
	    {
	    OBJ_UNLOCK (semClassId, level);
	    (void) errnoSet (S_semLib_INVALID_OPERATION);
	    return (ERROR);
	    }
	}

    if ((options & SEM_NO_RECURSE) == 0)
	{
	if (semId->recurse > 0)			/* check recurse count */
	    {
	    semId->recurse--;			/* decrement recurse count */
	    OBJ_UNLOCK (semClassId, level);
	    return (OK);
	    }
	}

    /*
     * If this semaphore was involved in the owner's priority inheritance,
     * then we can try to restore its normal priority after all contributing
     * semaphores have been given.  However, if a task tried to manually lower
     * the normal priority of the task while inheritance was in progress, then
     * the priority can only be dropped to the original normal priorirty level
     * saved in <priDrop>.
     */

    if ((semId->options & SEM_INVERSION_SAFE) != 0)
	{
	if (semId->priInheritFlag)
	    {
	    semId->priInheritFlag = FALSE;

	    if (--tCurrent->priInheritCnt == 0)
		kernWork |= SEM_M_PRI_RESORT;
	    }

	tCurrent->priMutexCnt--;

	if (tCurrent->priInheritCnt == tCurrent->priMutexCnt)
	    {
	    tCurrent->priDrop = tCurrent->priNormal;

	    if ((tCurrent->priMutexCnt == 0) && 
		(tCurrent->priority != (UINT) tCurrent->priDrop))
		{
		kernWork |= SEM_M_PRI_RESORT;
		}
	    }
	}

    if (Q_FIRST (&semId->qHead) == NULL)
	{
	semId->semOwner = NULL;

	if ((options & SEM_NO_EVENT_SEND) == 0)
	    {
	    if (semId->events.taskId != (TASK_ID) NULL)
		kernWork |= SEM_M_SEND_EVENTS;
	    }
	}
    else
	{
	kernWork |= SEM_M_Q_GET;
	}

    if ((semId->options & SEM_DELETE_SAFE) &&
	(TASK_SAFE_DEC (tCurrent) == TASK_SAFE_PEND))
	{
	TASK_SAFE_PEND_CLEAR (tCurrent);

	if (Q_FIRST (&tCurrent->safetyQHead) != NULL)
	    kernWork |= SEM_M_SAFE_Q_FLUSH;
	}

    if (kernWork == 0)
	{
	OBJ_UNLOCK (semClassId, level);
	return (OK);
	}

    KERNEL_LOCK_OBJ_UNLOCK (semClassId, level);

    retStatus = semMGiveKernWork (semId, kernWork, tCurrent);

    KERNEL_UNLOCK ();

    return (retStatus);
    }

#else /* _WRS_CONFIG_SMP */

/* begin SMP version of semMGive_inline() */

_WRS_INLINE STATUS semMGive_inline
    (
    SEM_ID	semId,               /* semaphore ID to give */
    int		options              /* semaphore options */
    )
    {
    int 	level;
    WIND_TCB *  tCurrent;
    UINT        cpuid;
    STATUS	retStatus;

    if (options & ~SEM_MUT_OPTIONS_MASK_INLINE)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

#ifdef  _WRS_CONFIG_SV_INSTRUMENTATION
    if ((options & SEM_NO_SYSTEM_VIEWER) == 0)
	{
        /* system viewer - level 1 event logging */
        EVT_OBJ_3 (semId, semClassId, EVENT_SEMGIVE,
                   semId, SEM_OWNER(semId), semId->recurse);
	}
#endif  /* _WRS_CONFIG_SV_INSTRUMENTATION */

    level = KERNEL_INT_CPU_LOCK ();
    cpuid = _WRS_CPU_INDEX_GET ();

    if ((options & SEM_NO_ERROR_CHECK) == 0)
	{
	if (_WRS_KERNEL_CPU_GLOBAL_GET (cpuid, intCnt) != 0)
	    {
	    _WRS_KERNEL_CPU_GLOBAL_SET (cpuid, errno, 
					S_intLib_NOT_ISR_CALLABLE);
	    KERNEL_INT_CPU_UNLOCK (level);

	    return (ERROR);
	    }

	/* 
	 * Verify that both SEM_DELETE_SAFE and SEM_INVERSION safe are
	 * specified consistently between the <options> parameter and the
	 * options passed at creation/initialization of this semaphore.
	 *
	 * NOTE:  If SEM_NO_ID_VALIDATE is not specified this is performed
	 *        after object validation.
	 */

	if ((options & SEM_NO_ID_VALIDATE) &&
	    ((semId->options & (SEM_DELETE_SAFE | SEM_INVERSION_SAFE)) !=
	     (options & (SEM_DELETE_SAFE | SEM_INVERSION_SAFE))))
	    {
	    KERNEL_INT_CPU_UNLOCK (level);
	    errno = S_semLib_INVALID_OPTION;
	    return (ERROR);
	    }
	}

    tCurrent = _WRS_KERNEL_CPU_GLOBAL_GET (cpuid, taskIdCurrent);

    KERNEL_INT_CPU_UNLOCK (level);

#ifdef _WRS_CONFIG_OBJECT_VERIFICATION
    if ((options & SEM_NO_ID_VALIDATE) == 0)
	{
# ifdef	_WRS_ARCH_HAS_OBJ_SAFE
	if (OBJ_VERIFY_AND_PROTECT (semId, semClassId, &level) != OK)
	    {
	    return (ERROR);
	    }
# else
	/* 
	 * If semaphore validation is specified, then it is necessary to exit
	 * the fast path.  
	 */

	return (semMGiveHard (semId, tCurrent, options));
# endif	/* _WRS_ARCH_HAS_OBJ_SAFE */
	}
#endif	/* _WRS_CONFIG_OBJECT_VERIFICATION */

    if ((options & SEM_NO_ERROR_CHECK) == 0)
	{
	WIND_TCB * currentOwner;

	currentOwner = (WIND_TCB *) vxAtomicGet_inline ((atomic_t *) 
							(void *) 
							&semId->semOwner);

	if ((WIND_TCB *)((ULONG) currentOwner & ~((long) SEMM_PENDED_TASK)) 
		!= tCurrent)
	    {
#if	defined(_WRS_CONFIG_OBJECT_VERIFICATION) && \
	defined(_WRS_ARCH_HAS_OBJ_SAFE)
	    if ((options & SEM_NO_ID_VALIDATE) == 0)
		{
		OBJ_UNPROTECT (semId, semClassId, level);
		}
#endif	/* _WRS_CONFIG_OBJECT_VERIFICATION && _WRS_ARCH_HAS_OBJ_SAFE */

	    (void) errnoSet (S_semLib_INVALID_OPERATION);
	    return (ERROR);
	    }
	}

    /*
     * The primary fast path in this implementation occurs if there is no 
     * recursion, the caller owns the semaphore, and there are no other tasks
     * pended on that semaphore.
     *
     * If the caller owns the semaphore the recurse count will not change.  If
     * the caller does not own the semaphore, or if there are tasks pended on
     * the semaphore, the vxCas() call will fail.  It is necessary to verify
     * ownership below.
     *
     * While this implementation involves replication of the owner validation
     * code it saves the overhead of that code during the fast path.  It is
     * also worth noting that there is a secondary fast path in the case that
     * the caller owns the semaphore recursively.  It is not necessary to enter
     * the kernel in that case either, and for both fast paths only a single
     * atomic operation is necessary. 
     */

    if ((semId->recurse == 0) || (options & SEM_NO_RECURSE))
	{
	/* 
	 * Perform a full memory barrier operation in the event the fast
	 * path is executed.  If a task is currently pending (or about to
	 * pend) on the mutex semaphore, i.e. the SEMM_PEND_TASK bit is set,
	 * the kernel will be entered.  The process of entering/exiting the
	 * kernel constitues a full memory barrier, and thus the following
	 * full memory fence will be redundant in that case.
	 */

	VX_MEM_BARRIER_RW ();

	if (vxCas_inline ((atomic_t *) (void *) &semId->semOwner, 
			  (atomicVal_t) tCurrent, 
			  (atomicVal_t) SEMM_NO_OWNER))
	    {
	    int kernWork = 0;
	    
	    /*
	     * If safeCnt drops to zero and an attempt has been made to
	     * delete the caller it is necessary to exit the fast path
	     * to flush the safety queue.
	     */

	    if ((options & SEM_DELETE_SAFE) &&
		(TASK_SAFE_DEC (tCurrent) == TASK_SAFE_PEND))
		{
		kernWork = SEM_M_SAFE_Q_FLUSH;
		}

	    if ((options & SEM_INVERSION_SAFE) != 0)
		{
		int priMutexCnt;
		int priDrop;
		int priNormal;

		/*
		 * It is worth noting that there is no need to check if this
		 * semaphore was involved in priority inheritance.
		 *
		 * The 'fast path' for give only occurs if no other task 
		 * has attempted to acquire the semaphore the caller is giving.
		 * Without an attempt by another task to acquire this 
		 * semaphore it could not have been involved in priority
		 * inheritence.
		 *
		 * It is, however, necessary to check if this is the last
		 * semaphore with the SEM_INVERSION_SAFE option held by
		 * the task.  In this case it may be necessary to drop the
		 * caller's priority back if it were raised due to priority
		 * inheritence involving another semaphore.
		 *
		 * This must be performed atomically because semMTakeByProxy()
		 * can increment this count externally.
		 */

		priMutexCnt = 
		    vxAtomic32Dec_inline((atomic32_t *) &tCurrent->priMutexCnt);

		/* 
		 * The vxAtomicDec() routine returns the previous value, so 
		 * it is necessary to decrement to get the current value
		 */

		priMutexCnt--;
		

		/*
		 * It is possible that a task may have performed a 
		 * taskPrioritySet() upon the current task while it was
		 * involved in priority inheritance. If that was the case, the
		 * current task's <priNormal> and <priDrop> may differ.  They 
		 * can only be be re-sync'ed when <priMutexCnt> matches 
		 * <priInheritCnt>.  Such a condition indicates that all the
		 * inversion safe mutexes that the task has are involved in
		 * priority inheritance.
		 *
		 * It is worth noting that the task's priInheritCnt can
		 * be incremented externally, but not decremented.  It is
		 * sufficient to perform an atomic 'get' operation to 
		 * retrieve the value.
		 * 
		 * It is unfortunately possible that the value of priMutexCnt
		 * can be incremented externally by semMTakeByProxy().  If this
		 * occurs *after* getting the value here then it is possible
		 * that this call will exit the fast path without cause.  This
		 * should be a rare occurence.
		 */

		if (vxAtomic32Get_inline (
			(atomic32_t *) &tCurrent->priInheritCnt) == priMutexCnt)
		    {
		    /* 
		     * Because both priNormal and priDrop can be set by 
		     * another task (in the kernel) it is necessary to get 
		     * these atomically.
		     */

		    priNormal = vxAtomic32Get_inline (
					(atomic32_t *) &tCurrent->priNormal);
		    priDrop = vxAtomic32Get_inline (
					(atomic32_t *) &tCurrent->priDrop);
		    
		    if (priDrop != priNormal)
			{
			/*
			 * Update of the priDrop value must be done in the
			 * kernel.  
			 *
			 * It is possibly that priMutexCnt has been incremented
			 * externally by a call to  semMTakeByProxy().  It is
			 * possible that priDrop and priNormal could have been
			 * changed externally by a call to taskPrioritySet().  
			 * It is possible that these changing conditions could 
			 * make the exit of the fast path unncessary, but this 
			 * should be rare.
			 *
			 * What is of greater concern is if changing values
			 * cause a situation where entrance into the kernel
			 * does not occur but it should.  This would require
			 * that priDrop and priNormal change from equal to
			 * non-equal.  This can *only* occur if priInheritCnt
			 * does not equal priMutexCnt.  In this case nothing
			 * is to be done in the kernel upon give.
			 */

			kernWork = SEM_M_INLINE_PRI_RESORT;
			}
		    else if ((priMutexCnt == 0) && 
			     (vxAtomic32Get_inline ((atomic32_t *) 
					  &tCurrent->priority) != priDrop))
			{
			/*
			 * The caller had its priority bumped due to priority
			 * inheritence on another mutex.  It is necessary
			 * to exit the 'fast path' to restore its original
			 * priority.
			 *
			 * Again, changing conditions could cause an 
			 * unnecessary entry into the kernel.  For example,
			 * if a call to taskPrioritySet() on the caller is
			 * made after acquiring the values above (or if a 
			 * call to semMTakeByProxy() is made to assign a new
			 * semaphore to the caller).  These conditions should
			 * be rare.
			 *
			 * For the unacceptable case, where conditions require
			 * entry into the kernel but it does not occur, the
			 * priMutexCnt must remain zero, the value of priDrop
			 * used here must equal the current running priority,
			 * but either the *current* priDrop or *current*
			 * priNormal must be different from the running
			 * priority.  
			 *
			 * The values of priDrop and priNormal are only
			 * different from the running priority if an
			 * inheritance enabled mutex is held, meaning that
			 * priMutexCnt must be greater than zero. 
			 */

			kernWork = SEM_M_INLINE_PRI_RESORT;
			}
		    }
		}

	    if ((options & SEM_NO_EVENT_SEND) == 0)
		{
		if (semId->events.taskId != (TASK_ID) NULL)
		    kernWork |= SEM_M_SEND_EVENTS;
		}

#if	defined(_WRS_CONFIG_OBJECT_VERIFICATION) && \
	defined(_WRS_ARCH_HAS_OBJ_SAFE)
	    if ((options & SEM_NO_ID_VALIDATE) == 0)
		{
		OBJ_UNPROTECT (semId, semClassId, level);
		}
#endif	/* _WRS_CONFIG_OBJECT_VERIFICATION && _WRS_ARCH_HAS_OBJ_SAFE */

	    /*
	     * If there is no work to be done in the kernel then the fast 
	     * path is kept.
	     *
	     * The semaphore has been given, so simply return OK.
	     */

	    if (kernWork == 0)
		{
		return (OK);
		}

	    /*
	     * Unfortunately it is necessary to enter the kernel to either
	     * adjust the caller's priority or to flush its safety queue.
	     *
	     * Exit the fast path and perform the kernel work.
	     */

	    KERNEL_ENTER ();

#if	defined(_WRS_CONFIG_OBJECT_VERIFICATION) && \
	defined(_WRS_ARCH_HAS_OBJ_SAFE)
	    if ((options & SEM_NO_ID_VALIDATE) == 0)
		{
		if (OBJ_VERIFY (semId, semClassId) != OK)
		    {
		    KERNEL_EXIT ();

		    return (ERROR);
		    }
		}
#endif	/* _WRS_CONFIG_OBJECT_VERIFICATION && _WRS_ARCH_HAS_OBJ_SAFE */

	    retStatus = semMGiveKernWork (semId, kernWork, tCurrent);

	    KERNEL_EXIT ();

	    return (retStatus);
	    }

#if	defined(_WRS_CONFIG_OBJECT_VERIFICATION) && \
	defined(_WRS_ARCH_HAS_OBJ_SAFE)
	if ((options & SEM_NO_ID_VALIDATE) == 0)
	    {
	    OBJ_UNPROTECT (semId, semClassId, level);
	    }
#endif	/* _WRS_CONFIG_OBJECT_VERIFICATION && _WRS_ARCH_HAS_OBJ_SAFE */

	/*
	 * No verification that the caller does in fact own the semaphore.  This
	 * routine should not be called by a task that does not own the
	 * semaphore!
	 */
	}
    else /* if (semId->recurse > 0) */
	{
	/*
	 * It is assumed that the caller does own the semaphore, so  simply 
	 * decrement the recurse count and return OK.
	 *
	 * NOTE:  if the option SEM_NO_RECURSE is passed the previous 'if' will
	 *        always be true and this statement will be compiled out.
	 */

	semId->recurse--;

#if	defined(_WRS_CONFIG_OBJECT_VERIFICATION) && \
	defined(_WRS_ARCH_HAS_OBJ_SAFE)
	if ((options & SEM_NO_ID_VALIDATE) == 0)
	    {
	    OBJ_UNPROTECT (semId, semClassId, level);
	    }
#endif	/* _WRS_CONFIG_OBJECT_VERIFICATION && _WRS_ARCH_HAS_OBJ_SAFE */

	return (OK);
	}

    /*
     * The 'semOwner' field was _not_  taskIdCurrent, i.e. a task has
     * requested the semaphore and is pending on the semaphore (or is
     * currently in the process of pending on the semaphore) and thus the
     * SEMM_PENDED_TASK flag has been set.  Enter the kernel to unpend the
     * task (or make the semaphore available if there are actually no
     * pending tasks by the time the kernel is entered).
     *
     * If the current task is deleted before it enters the kernel, a pended
     * task will remain pended. However, the effect in that case is just
     * the same as if this task was deleted just before calling 
     * semMMGive().
     */

    return (semMGiveHard (semId, tCurrent, options));
    }
#endif /* _WRS_CONFIG_SMP */

/*******************************************************************************
*
* semMTake_inline - take a mutex semaphore (inline version)
*
* This routine takes a mutex semaphore.
*
* The behavior of this routine is similar to that of semTake() on a mutex 
* semaphore, differing only in that an additional parameter, <options>, must 
* be specified.  The semaphore specified by <semId> must be of mutex type.
*/

#ifndef _WRS_CONFIG_SMP

/* begin UP version of semMTake_inline() */

_WRS_INLINE STATUS semMTake_inline
    (
    SEM_ID	semId,               /* semaphore ID to take */
    _Vx_ticks_t	timeout,             /* timeout in ticks */
    int		options              /* semaphore options */
    )
    {
    int		level;
    int	        status;
    WIND_TCB *  tCurrent;

    if (options & ~SEM_MUT_OPTIONS_MASK_INLINE)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

#ifdef  _WRS_CONFIG_SV_INSTRUMENTATION
    if ((options & SEM_NO_SYSTEM_VIEWER) == 0)
	{
        /* system viewer - level 1 event logging */
        EVT_OBJ_3 (semId, semClassId, EVENT_SEMTAKE,
                   semId, SEM_OWNER(semId), semId->recurse);
	}
#endif /* _WRS_CONFIG_SV_INSTRUMENTATION */

    if ((options & SEM_NO_ERROR_CHECK) == 0)
	{
	if (_WRS_INT_RESTRICT () != OK)			/* restrict isr use */
	    return (ERROR);
	}

    tCurrent = taskIdCurrent;

again:

    OBJ_LOCK (semClassId, level);

#ifdef _WRS_CONFIG_OBJECT_VERIFICATION
    if ((options & SEM_NO_ID_VALIDATE) == 0)
	{
	if (OBJ_VERIFY (semId, semClassId) != OK)
	    {
	    OBJ_UNLOCK (semClassId, level);
	    return (ERROR);
	    }
	}
#endif

    if ((options & SEM_NO_ERROR_CHECK) == 0)
	{
	/* 
	 * Verify that both SEM_DELETE_SAFE and SEM_INVERSION safe are
	 * specified consistently between the <options> parameter and the
	 * options passed at creation/initialization of this semaphore.
	 *
	 * NOTE:  This is done after the semaphore ID is validated, if
	 *        object validation is enabled.
	 */

	if ((semId->options & (SEM_DELETE_SAFE | SEM_INVERSION_SAFE)) !=
	    (options & (SEM_DELETE_SAFE | SEM_INVERSION_SAFE)))
	    {
	    OBJ_UNLOCK (semClassId, level);
	    errno = S_semLib_INVALID_OPTION;
	    return (ERROR);
	    }
	}

    if (semId->semOwner == NULL)
	{
	semId->semOwner = tCurrent;	/* update semaphore state */

	if (semId->options & SEM_INVERSION_SAFE)
	    {
	    tCurrent->priMutexCnt++;  /* update inherit count */
	    }

	if (semId->options & SEM_DELETE_SAFE)
	    TASK_SAFE_INC(tCurrent);             /* update safety count */


        OBJ_UNLOCK (semClassId, level);
	return (OK);
	}

    if ((options & SEM_NO_RECURSE) == 0)
	{
	if (SEM_OWNER(semId) == tCurrent)	/* check for recursion */
	    {
	    semId->recurse++;			/* keep recursion count */
	    OBJ_UNLOCK (semClassId, level);
	    return (OK);
	    }
	}

    if (timeout == NO_WAIT)			/* NO_WAIT = no block */
	{
        OBJ_UNLOCK (semClassId, level);
	(void) errnoSet (S_objLib_OBJ_UNAVAILABLE);
	return (ERROR);
	}

    KERNEL_LOCK_OBJ_UNLOCK (semClassId, level);

    if (semMPendQPut (semId, timeout, tCurrent) != OK)
	{
	KERNEL_UNLOCK ();			/* windPendQPut failed */
	return (ERROR);
	}

    if ((status = KERNEL_UNLOCK ()) == RESTART)	
	{
	timeout = SIG_TIMEOUT_RECALC (timeout);
	goto again;				/* we got signalled */
	}

    return (status);
    }
#else /* _WRS_CONFIG_SMP */

/* begin SMP version of semMTake_inline () */

_WRS_INLINE STATUS semMTake_inline
    (
    SEM_ID	semId,               /* semaphore ID to take */
    _Vx_ticks_t	timeout,             /* timeout in ticks */
    int		options              /* semaphore options */
    )
    {
    int		level;
    WIND_TCB *  tCurrent;
    WIND_TCB *  currentOwner;
    UINT        cpuid;

    if (options & ~SEM_MUT_OPTIONS_MASK_INLINE)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

#ifdef  _WRS_CONFIG_SV_INSTRUMENTATION
    if ((options & SEM_NO_SYSTEM_VIEWER) == 0)
	{
        /* system viewer - level 1 event logging */
        EVT_OBJ_3 (semId, semClassId, EVENT_SEMTAKE,
                   semId, SEM_OWNER(semId), semId->recurse);
	}
#endif /* _WRS_CONFIG_SV_INSTRUMENTATION */

    level = KERNEL_INT_CPU_LOCK ();
    cpuid = _WRS_CPU_INDEX_GET ();

    if ((options & SEM_NO_ERROR_CHECK) == 0)
	{
	if (_WRS_KERNEL_CPU_GLOBAL_GET (cpuid, intCnt) != 0)
	    {
	    _WRS_KERNEL_CPU_GLOBAL_SET (cpuid, errno, 
					S_intLib_NOT_ISR_CALLABLE);
	    KERNEL_INT_CPU_UNLOCK (level);

	    return (ERROR);
	    }

	/* 
	 * Verify that both SEM_DELETE_SAFE and SEM_INVERSION safe are
	 * specified consistently between the <options> parameter and the
	 * options passed at creation/initialization of this semaphore.
	 *
	 * NOTE:  If SEM_NO_ID_VALIDATE is not specified this is performed
	 *        after object validation.
	 */
	
	if ((options & SEM_NO_ID_VALIDATE) &&
	    ((semId->options & (SEM_DELETE_SAFE | SEM_INVERSION_SAFE)) !=
	     (options & (SEM_DELETE_SAFE | SEM_INVERSION_SAFE))))
	    {
	    KERNEL_INT_CPU_UNLOCK (level);
	    errno = S_semLib_INVALID_OPTION;

	    return (ERROR);
	    }
	}

    tCurrent = _WRS_KERNEL_CPU_GLOBAL_GET (cpuid, taskIdCurrent);

    KERNEL_INT_CPU_UNLOCK (level);

#ifdef _WRS_CONFIG_OBJECT_VERIFICATION
    if ((options & SEM_NO_ID_VALIDATE) == 0)
	{
# ifdef	_WRS_ARCH_HAS_OBJ_SAFE
	if (OBJ_VERIFY_AND_PROTECT (semId, semClassId, &level) != OK)
	    {
	    return (ERROR);
	    }
# else
	/* 
	 * If semaphore validation is specified, then it is necessary to exit
	 * the fast path.  
	 *
	 * Note:
	 *
	 * If an atomic object locking mechanism is implemented this will
	 * no longer be the case.
	 */

	return (semMTakeHard (semId, timeout, tCurrent, options));
# endif	/* _WRS_ARCH_HAS_OBJ_SAFE */
	}
#endif	/* _WRS_CONFIG_OBJECT_VERIFICATION */

    /*
     * If the semaphore was created with the SEM_DELETE_SAFE option it is 
     * necessary to increment the safeCnt before attempting to acquire
     * the semaphore.  This is necessary to prevent a window during which
     * the task could be deleted while holding the semaphore.
     *
     * If the task does not acquire the semaphore on the fast path it will
     * be necessary to decrement the safeCnt.
     */

    if (options & SEM_DELETE_SAFE)
	TASK_SAFE_INC (tCurrent);

    /*
     * The acquisition of a mutex semaphore is optimized for the common
     * case: The semaphore is currently full, i.e. there is no contention
     * for ownership of a resource.  For SMP, a CAS operation is performed
     * to atomically update the 'semOwner' field, and thus an OBJ_LOCK()
     * and OBJ_UNLOCK() operation is skipped.
     */

    if (vxCas_inline ((atomic_t *) (void *) &semId->semOwner, 
                      (atomicVal_t) SEMM_NO_OWNER, 
		      (atomicVal_t) tCurrent))
        {
	/*
	 * The semaphore give operation performs a RW memory barrier operation.
	 * This will ensure that all memory writes prior to the release of 
	 * the semaphore complete.  
	 *
	 * This does not, however, affect the order of memory reads by the 
	 * caller of this routine.  It may be possible that a memory access 
	 * that occurs programmatically after this routine could be performed 
	 * prior to the memory write accesses associated with the give 
	 * operation, while the read access of this routine are performed after 
	 * those write accesses of the give operation.
	 *
	 * Because of this an instruction barrier is performed here.  This will
	 * guarantee that no speculative execution of any load instructions
	 * after the conditional branch in vxCas() will occur before that
	 * conditional branch.
	 */

	VX_INSTR_BARRIER ();

#if	defined(_WRS_CONFIG_OBJECT_VERIFICATION) && \
	defined(_WRS_ARCH_HAS_OBJ_SAFE)
	if ((options & SEM_NO_ID_VALIDATE) == 0)
	    {
	    OBJ_UNPROTECT (semId, semClassId, level);
	    }
#endif	/* _WRS_CONFIG_OBJECT_VERIFICATION && _WRS_ARCH_HAS_OBJ_SAFE */

	/*
	 * Increment the number of inversion safe mutexes held by the caller.
	 *
	 * Note, if the semaphore was created with the SEM_DELETE_SAFE option
	 * the safeCnt of the caller was already incremented before the
	 * attempt to acquire the semaphore.
	 */

	if (options & SEM_INVERSION_SAFE)
	    {
	    /* 
	     * This must be atomic because semMTakeByProxy() can increment 
	     * the priMutexCnt externally.
	     */

	    (void) vxAtomic32Inc_inline((atomic32_t *) &tCurrent->priMutexCnt);
	    }

        return (OK);
        }

    if ((options & SEM_NO_RECURSE) == 0)
	{
	/* check for recursion */

	currentOwner = (WIND_TCB *) vxAtomicGet_inline ((atomic_t *) 
							(void *) 
							&semId->semOwner);

	if ((WIND_TCB *)((ULONG) currentOwner & ~((long)SEMM_PENDED_TASK))
		== tCurrent)
	    {
	    /*
	     * Because the semaphore must already be held by the caller its
	     * safeCnt can not possibly reach zero, thus, it will never need
	     * to flush its safety queue here.
	     */

	    if (options & SEM_DELETE_SAFE)
		(void) TASK_SAFE_DEC (tCurrent);

	    semId->recurse++;

#if	defined(_WRS_CONFIG_OBJECT_VERIFICATION) && \
	defined(_WRS_ARCH_HAS_OBJ_SAFE)
	    if ((options & SEM_NO_ID_VALIDATE) == 0)
		{
		OBJ_UNPROTECT (semId, semClassId, level);
		}
#endif	/* _WRS_CONFIG_OBJECT_VERIFICATION && _WRS_ARCH_HAS_OBJ_SAFE */

	    return (OK);
	    }
	}

#if	defined(_WRS_CONFIG_OBJECT_VERIFICATION) && \
	defined(_WRS_ARCH_HAS_OBJ_SAFE)
    if ((options & SEM_NO_ID_VALIDATE) == 0)
	{
	OBJ_UNPROTECT (semId, semClassId, level);
	}
#endif	/* _WRS_CONFIG_OBJECT_VERIFICATION && _WRS_ARCH_HAS_OBJ_SAFE */

    /*
     * Decrement the caller's safeCnt.  If the safeCnt reaches zero and an 
     * attempt to delete (or restart) the caller has been made it is 
     * necessary to enter the kernel and flush the safety queue. 
     *
     * Note:  
     *
     * It is possible that the caller could enter the kernel twice:  once here
     * and once in the semMTakeHard() call.  This would be a very rare
     * occurence requiring that an attempt to delete (or restart) the caller
     * occured during the period where its safeCnt was incremented, but that
     * the deleter task was itself deleted before the decrement occurs here (or
     * the deleter used the unpublished taskDestroy() routine and timed out).
     *
     * Given the highly unlikely nature of such a scenario the safe count is
     * decremented here to preserve code clarity in the semMTakeHard()
     * routine.
     */

    if ((options & SEM_DELETE_SAFE) &&
	(TASK_SAFE_DEC (tCurrent) == TASK_SAFE_PEND))
	{
	KERNEL_ENTER ();

	TASK_SAFE_PEND_CLEAR (tCurrent);

	if (Q_FIRST (&tCurrent->safetyQHead) != NULL)
	    {
	    windPendQFlush (&tCurrent->safetyQHead);
	    }

	KERNEL_EXIT ();
	}

    /* 
     * The mutex semaphore could not be acquired via vxCas(); return ERROR if
     * called with a timeout of NO_WAIT.
     */
  
   if (timeout == NO_WAIT)
       {
       (void) errnoSet (S_objLib_OBJ_UNAVAILABLE);
       return (ERROR);
       }

    return (semMTakeHard (semId, timeout, tCurrent, options));
    }
#endif /* _WRS_CONFIG_SMP */

/*******************************************************************************
*
* semBGive_inline - give a binary semaphore (inline version)
*
* This routine gives a binary semaphore.
*
* The behavior of this routine is similar to that of semGive() on a binary 
* semaphore, differing only in that an additional parameter, <options>, must 
* be specified.  The semaphore specified by <semId> must be of binary type.
*/

#ifndef _WRS_CONFIG_SMP

/* begin UP version of semBGive_inline () */

_WRS_INLINE STATUS semBGive_inline
    (
    SEM_ID	semId,               /* semaphore ID to give */
    int		options              /* semaphore options */
    )
    {
    int		level;
    Q_NODE *	pNode;

    if (options & ~SEM_BIN_OPTIONS_MASK_INLINE)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

#ifdef  _WRS_CONFIG_SV_INSTRUMENTATION
    if ((options & SEM_NO_SYSTEM_VIEWER) == 0)
	{
        /* system viewer - level 1 event logging */
        EVT_OBJ_3 (semId, semClassId, EVENT_SEMGIVE,
                   semId, SEM_OWNER(semId), semId->recurse);
	}
#endif  /* _WRS_CONFIG_SV_INSTRUMENTATION */

    if (KERNEL_ENTERED_ME ())
	{
	workQAdd1 ((WORK_Q_ADD_1_FUNC) semBGiveDefer, semId);
	return (OK);
	}

    OBJ_LOCK (semClassId,level);

#ifdef _WRS_CONFIG_OBJECT_VERIFICATION
    if ((options & SEM_NO_ID_VALIDATE) == 0)
	{
	if (OBJ_VERIFY (semId, semClassId) != OK)
	    {
	    OBJ_UNLOCK (semClassId,level);
	    return (ERROR);
	    }
	}
#endif

    pNode = Q_FIRST (&semId->qHead);

    if (pNode == NULL)
	{
	WIND_TCB * pOwner;

	if (options & SEM_NO_EVENT_SEND)
	    {
	    semId->semOwner = NULL;
	    OBJ_UNLOCK (semClassId,level);
	    return (OK);
	    }

	pOwner = semId->semOwner;
	semId->semOwner = NULL;

	/* check change of state; if so, send events */

	if ((semId->events.taskId == (TASK_ID) NULL) || (pOwner == NULL))
	    {
	    OBJ_UNLOCK (semClassId,level);
	    return (OK);
	    }
	else
	    {
	    int     oldErrno;
	    STATUS  evStatus;
	    STATUS  retStatus;

	    retStatus = OK;

	    KERNEL_LOCK_OBJ_UNLOCK (semClassId,level);

	    oldErrno = errnoGet ();

	    /*
	     * We will be here only if semId->events.taskId is non-null (i.e.
	     * the event library has been configured). Hence we can eliminate
	     * the null-check for _func_eventRsrcSend.
	     */

	    evStatus = (*_func_eventRsrcSend) (semId->events.taskId,
					       semId->events.registered);

	    if (evStatus != OK)
		{
		if ((semId->options & SEM_EVENTSEND_ERR_NOTIFY) != 0x0)
		    {
		    retStatus = ERROR;
		    oldErrno = S_eventLib_EVENTSEND_FAILED;
		    }
		    
		semId->events.taskId = (TASK_ID) NULL;
		}
	    else if ((semId->events.options & EVENTS_SEND_ONCE) != 0x0)
		semId->events.taskId = (TASK_ID) NULL;
		
	    KERNEL_UNLOCK ();

	    (void) errnoSet (oldErrno);
	    return (retStatus);
	    }
	}
    else
	{
	/* set semOwner to the top of WIND_TCB structure */

	semId->semOwner = NODE_PTR_TO_TCB (pNode);

	KERNEL_LOCK_OBJ_UNLOCK (semClassId,level);

#ifdef _WRS_CONFIG_SV_INSTRUMENTATION
	/* system viewer - level 2 event logging */
	EVT_TASK_1 (EVENT_OBJ_SEMGIVE, semId);
#endif /* _WRS_CONFIG_SV_INSTRUMENTATION */
	windPendQGet (&semId->qHead);		/* unblock a task */

	KERNEL_UNLOCK ();			

	return (OK);
	}
    }

#else /* _WRS_CONFIG_SMP */

/* begin SMP version of semBGive_inline () */

_WRS_INLINE STATUS semBGive_inline
    (
    SEM_ID	semId,               /* semaphore ID to give */
    int		options              /* semaphore options */
    )
    {
    atomicVal_t	prevState;

    if (options & ~SEM_BIN_OPTIONS_MASK_INLINE)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

#ifdef  _WRS_CONFIG_SV_INSTRUMENTATION
    if ((options & SEM_NO_SYSTEM_VIEWER) == 0)
	{
        /* system viewer - level 1 event logging */
        EVT_OBJ_3 (semId, semClassId, EVENT_SEMGIVE,
                   semId, SEM_OWNER(semId), semId->recurse);
	}
#endif  /* _WRS_CONFIG_SV_INSTRUMENTATION */

#ifdef _WRS_CONFIG_OBJECT_VERIFICATION
    if ((options & SEM_NO_ID_VALIDATE) == 0)
	{
	return (semBGiveHard (semId, options));
	}
#endif

    /* 
     * Perform a full memory barrier operation in the event the fast
     * path is executed.  If a task is currently pending (or about to
     * pend) on the binary semaphore, i.e. the SEMB_PEND_TASK bit is set,
     * the kernel will be entered.  The process of entering/exiting the
     * kernel constitues a full memory barrier, and thus the following
     * full memory fence will be redundant in that case.
     */

    VX_MEM_BARRIER_RW ();

    /*
     * The fast path for releasing a binary semaphore occurs when
     * the SEMB_PENDED_TASK bit it not set, i.e. no other task has
     * attempted to acquire the semaphore while empty.  Note that releasing
     * a binary semaphore that is already full should execute the fast
     * path, and thus vxCas() cannot be used below.
     */

     prevState = vxAtomicAnd_inline ((atomic_t *) (void *) &semId->semOwner, 
				     ~SEMB_EMPTY_STATE);

     if ((prevState & SEMB_PENDED_TASK) == 0)
	 {
	 if ((options & SEM_NO_EVENT_SEND) == 0)
	     {
	     if ((semId->events.taskId != (TASK_ID) NULL) &&
		 (prevState != (atomicVal_t) SEMB_FULL_STATE))
		 {
		 int          oldErrno;
		 STATUS       evStatus;
		 STATUS       retStatus;
		 int	      level;
		 unsigned int cpuIx;
    		 
		 retStatus = OK;

		 level = KERNEL_INT_CPU_LOCK ();
		 cpuIx = _WRS_CPU_INDEX_GET ();

		 if (_WRS_KERNEL_CPU_GLOBAL_GET (cpuIx, intCnt) != 0)
		     {
		     KERNEL_INT_CPU_UNLOCK (level); 

		     if (!KERNEL_LOCK_TRY ())
			 {
			 workQAdd2 ((WORK_Q_ADD_2_FUNC) _func_eventRsrcSend,
				    (void *) semId->events.taskId,
				    (_Vx_usr_arg_t) semId->events.registered);

			 return (OK);
			 }
		     }
		 else
		     {
		     KERNEL_INT_CPU_UNLOCK (level);
		     KERNEL_ENTER ();
		     }

		 oldErrno = errnoGet ();

		 /*
		  * We will be here only if semId->events.taskId is non-null 
		  * (i.e.the event library has been configured). Hence we can 
		  * eliminate the null-check for _func_eventRsrcSend.
		  */

		 evStatus = (*_func_eventRsrcSend) (semId->events.taskId,
						    semId->events.registered);

		 if (evStatus != OK)
		     {
		     if ((semId->options & SEM_EVENTSEND_ERR_NOTIFY) != 0x0)
			 {
			 retStatus = ERROR;
			 oldErrno = S_eventLib_EVENTSEND_FAILED;
			 }
		    
		     semId->events.taskId = (TASK_ID) NULL;
		     }
		 else if ((semId->events.options & EVENTS_SEND_ONCE) != 0x0)
		     semId->events.taskId = (TASK_ID) NULL;
		
		 KERNEL_EXIT();

		 (void) errnoSet (oldErrno);
		 return (retStatus);
		 }
	     }

	 return (OK);
	 }

     return (semBGiveHard (semId, options));
    }
#endif /* _WRS_CONFIG_SMP */

/*******************************************************************************
*
* semBTake_inline - take a binary semaphore (inline version)
*
* This routine takes a binary semaphore.
*
* The behavior of this routine is similar to that of semTake() on a binary 
* semaphore, differing only in that an additional parameter, <options>, must 
* be specified.  The semaphore specified by <semId> must be of binary type.
*/

#ifndef _WRS_CONFIG_SMP

/* begin UP version of semBTake_inline() */

_WRS_INLINE STATUS semBTake_inline
    (
    SEM_ID	semId,               /* semaphore ID to take */
    _Vx_ticks_t	timeout,             /* timeout in ticks */
    int		options              /* semaphore options */
    )
    {
    int		level;
    int		status;

    if (options & ~SEM_BIN_OPTIONS_MASK_INLINE)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

#ifdef  _WRS_CONFIG_SV_INSTRUMENTATION
    if ((options & SEM_NO_SYSTEM_VIEWER) == 0)
	{
        /* system viewer - level 1 event logging */
        EVT_OBJ_3 (semId, semClassId, EVENT_SEMTAKE,
                   semId, SEM_OWNER(semId), semId->recurse);
	}
#endif /* _WRS_CONFIG_SV_INSTRUMENTATION */

    if ((options & SEM_NO_ERROR_CHECK) == 0)
	{
	if (_WRS_INT_RESTRICT () != OK)			/* restrict isr use */
	    return (ERROR);
	}

again:

    OBJ_LOCK (semClassId, level);

#ifdef _WRS_CONFIG_OBJECT_VERIFICATION
    if ((options & SEM_NO_ID_VALIDATE) == 0)
	{
	if (OBJ_VERIFY (semId, semClassId) != OK)
	    {
	    OBJ_UNLOCK (semClassId, level);
	    return (ERROR);
	    }
	}
#endif

    if (semId->semOwner == NULL)
	{
	semId->semOwner = taskIdCurrent;	/* update semaphore state */
	OBJ_UNLOCK (semClassId, level);
	return (OK);
	}

    if (timeout == NO_WAIT)			/* NO_WAIT = no block */
	{
	OBJ_UNLOCK (semClassId, level);
	(void) errnoSet (S_objLib_OBJ_UNAVAILABLE);
	return (ERROR);
	}

    KERNEL_LOCK_OBJ_UNLOCK (semClassId, level);

#ifdef _WRS_CONFIG_SV_INSTRUMENTATION
    /* system viewer - level 2 event logging */
    EVT_TASK_1 (EVENT_OBJ_SEMTAKE, semId);
#endif /* _WRS_CONFIG_SV_INSTRUMENTATION */

    if (windPendQPut (&semId->qHead, timeout) != OK)
	{
	KERNEL_UNLOCK ();			
	return (ERROR);
	}

    if ((status = KERNEL_UNLOCK ()) == RESTART)	
	{
	timeout = SIG_TIMEOUT_RECALC (timeout);
	goto again;
	}

    return (status);
    }

#else /* _WRS_CONFIG_SMP */

/* begin SMP version of semBTake_inline() */

_WRS_INLINE STATUS semBTake_inline
    (
    SEM_ID	semId,               /* semaphore ID to take */
    _Vx_ticks_t	timeout,             /* timeout in ticks */
    int		options              /* semaphore options */
    )
    {
    if (options & ~SEM_BIN_OPTIONS_MASK_INLINE)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

#ifdef  _WRS_CONFIG_SV_INSTRUMENTATION
    if ((options & SEM_NO_SYSTEM_VIEWER) == 0)
	{
        /* system viewer - level 1 event logging */
        EVT_OBJ_3 (semId, semClassId, EVENT_SEMTAKE,
                   semId, SEM_OWNER(semId), semId->recurse);
	}
#endif /* _WRS_CONFIG_SV_INSTRUMENTATION */

    if ((options & SEM_NO_ERROR_CHECK) == 0)
	{
	int  level;
	UINT cpuid;

	level = KERNEL_INT_CPU_LOCK ();
	cpuid = _WRS_CPU_INDEX_GET ();

	if (_WRS_KERNEL_CPU_GLOBAL_GET (cpuid, intCnt) != 0)
	    {
	    _WRS_KERNEL_CPU_GLOBAL_SET (cpuid, errno, 
					S_intLib_NOT_ISR_CALLABLE);

	    KERNEL_INT_CPU_UNLOCK (level);

	    return (ERROR);
	    }

	KERNEL_INT_CPU_UNLOCK (level);
	}

#ifdef _WRS_CONFIG_OBJECT_VERIFICATION
    if ((options & SEM_NO_ID_VALIDATE) == 0)
	{
	return (semBTakeHard (semId, timeout, options));
	}
#endif

    /*
     * The acquisition of a binary semaphore is optimized for the common
     * case: The semaphore is currently full, i.e. there is no contention
     * for ownership of a resource.  For SMP, a CAS operation is performed
     * to atomically update the 'semOwner' field, and thus an OBJ_LOCK()
     * and OBJ_UNLOCK() operation is skipped.
     */

    if (vxCas_inline ((atomic_t *) (void *) &semId->semOwner, 
		      (atomicVal_t) SEMB_FULL_STATE, 
		      (atomicVal_t) SEMB_EMPTY_STATE))
        {
	/*
	 * The semaphore give operation performs a RW memory barrier operation.
	 * This will ensure that all memory writes prior to the release of 
	 * the semaphore complete.  
	 *
	 * This does not, however, affect the order of memory reads by the 
	 * caller of this routine.  It may be possible that a memory access 
	 * that occurs programmatically after this routine could be performed 
	 * prior to the memory write accesses associated with the give 
	 * operation, while the read access of this routine are performed after 
	 * those write accesses of the give operation.
	 *
	 * Because of this an instruction barrier is performed here.  This will
	 * guarantee that no speculative execution of any load instructions
	 * after the conditional branch in vxCas() will occur before that
	 * conditional branch.
	 */

	VX_INSTR_BARRIER ();

        return (OK);
        }

    /* 
     * The binary semaphore could not be acquired via vxCas(); return ERROR if
     * called with a timeout of NO_WAIT.
     */
  
    if (timeout == NO_WAIT)
	{
	(void) errnoSet (S_objLib_OBJ_UNAVAILABLE);
	return (ERROR);
	}
   
    return (semBTakeHard (semId, timeout, options));
    }

#endif /* _WRS_CONFIG_SMP */

#endif /* !defined (_ASMLANGUAGE) */

#endif /* __INCsemLibInlineh */
