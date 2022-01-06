/* semRWLibInlineP.h - inline reader/writer semaphore library header file */

/*
 * Copyright (c) 2013-2014, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
26may16,wqi  Remove compiling warnings.
10nov14,jpb  fixed static analysis warnings
27jun13,dlk  written.
*/

/*
 * This module is experimental and private.  The interfaces it defines
 * are subject to change without notice.
 *
 * Inline implementation of reader/writer semaphores, (somewhat) scalable
 * according to provided semaphore options.  Initially only "minimal" and
 * "fully featured" option combinations may be supported.
 *
 * These inline reader/writer semaphore APIs are supported only in the
 * kernel, not from RTPs.
 */

#ifndef __INCsemRWLibInlinePh
#define __INCsemRWLibInlinePh

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

/*
 * Additional pseudo-options (not stored in semId->options).
 * These must not conflict in value with the options defined in semLibCommon.h.
 * Start from the most-significant bit and work down.
 */

#define SEM_RW_WRITER_CALL	((int)0x80000000)
#define SEM_RW_READER_CALL      (0x40000000)

/* option masks for Reader-Writer semaphores*/

#define SEM_RW_OPTIONS_MASK_INLINE	(SEM_Q_FIFO | 			      \
				         SEM_Q_PRIORITY | 		      \
                                         SEM_DELETE_SAFE |                    \
                                         SEM_INVERSION_SAFE |                 \
				         SEM_EVENTSEND_ERR_NOTIFY |           \
				         SEM_INTERRUPTIBLE |                  \
                                         SEM_NO_ID_VALIDATE |                 \
                                         SEM_NO_ERROR_CHECK |                 \
                                         SEM_NO_EVENT_SEND  |                 \
                                         SEM_NO_SYSTEM_VIEWER |               \
                                         SEM_NO_RECURSE)

/*
 * 'Minimal' reader-writer semaphores have a fast-path that allows
 * them to be given or taken (under certain conditions) without entering
 * the kernel and without fetching the current task ID, but they do not
 * support deletion safety, inversion safety, recursive taking, or VxWorks
 * event sending. Some positive options must be disallowed, and some
 * 'negative' options must be enabled.
 */
#define SEM_RW_OPTIONS_MIN_DISALLOWED   (SEM_DELETE_SAFE |                    \
                                         SEM_INVERSION_SAFE |                 \
                                         SEM_EVENTSEND_ERR_NOTIFY)
/*
 * Required (negative) options for minimal implementation.
 * - Supporting recursion requires the reader task table (or a different API)
 * - Object ID validation requires object lock (entering the kernel in SMP)
 * - Don't want to support EVENT_SEND.
 */
#define SEM_RW_OPTIONS_MIN_REQUIRED     (SEM_NO_RECURSE |                     \
                                         SEM_NO_EVENT_SEND |                  \
                                         SEM_NO_ID_VALIDATE)

#define SEM_RW_OPTIONS_ARE_MINIMAL(x) \
    (((x) & SEM_RW_OPTIONS_MIN_DISALLOWED) == 0 && \
	((x) & SEM_RW_OPTIONS_MIN_REQUIRED) == SEM_RW_OPTIONS_MIN_REQUIRED)

#if !defined (_ASMLANGUAGE)

enum SEM_RW_MODE
    {
    SEM_RW_MODE_UNOWNED = 0,
    SEM_RW_MODE_READ,
    SEM_RW_MODE_WRITE
    };

#define SEM_RW_INLINE_NDEBUG

#ifdef SEM_RW_INLINE_NDEBUG
#define semrw_kassert(ignore)	((void) 0)
#else /* turn debugging on */

#include <logLib.h>
#include <taskLib.h>

#define _SEMRW_KASSERT_STR(z) _SEMRW_KASSERT_TMP(z)
#define _SEMRW_KASSERT_TMP(z) #z

extern void __semrw_kassert (const char *msg);

#define semrw_kassert(test) \
    ((void) \
     ((test) ? ((void) 0) : \
               __semrw_kassert("Assertion failed: "#test", file " 	\
                               __FILE__ ", line "_SEMRW_KASSERT_STR(__LINE__)"\n")))
#endif /* SEM_RW_INLINE_NDEBUG */

/* function declarations (support routines in semRWMinLib.c) */

extern STATUS semRMinTakeHard (SEM_ID semId, int options);
extern STATUS semWMinTakeHard (SEM_ID semId, int options);
extern STATUS semRMinGiveHard (SEM_ID semId, int options);
extern STATUS semWMinGiveHard (SEM_ID semId, int options);


/***************************************************************************
*
* _semRWIsrCheck - return ERROR if called from an ISR
*
* Returns OK if not called from an ISR, otherwise sets cpu-specific
* errno value and returns ERROR.
*
* RETURNS: OK or ERROR
* ERRNO: S_intLib_NOT_ISR_CALLABLE
* NOMANUAL
*/
_WRS_INLINE STATUS _semRWIsrCheck (void)
    {
#ifdef _WRS_CONFIG_SMP

    int cpuid;
    int intCnt;
    int level;

    level = KERNEL_INT_CPU_LOCK();
    cpuid = _WRS_CPU_INDEX_GET ();
    intCnt = _WRS_KERNEL_CPU_GLOBAL_GET (cpuid, intCnt);
    if (intCnt != 0)
	{
	_WRS_KERNEL_CPU_GLOBAL_SET (cpuid, errno, S_intLib_NOT_ISR_CALLABLE);
	}
    KERNEL_INT_CPU_UNLOCK(level);

    return intCnt ? ERROR : 0;

#else /* ! _WRS_CONFIG_SMP */

    return _WRS_INT_RESTRICT ();

#endif /* !_WRS_CONFIG_SMP */
    }

/*******************************************************************************
*
* _semRMinGive_inline - give a minimal reader/writer semaphore in read mode
*
* This routine is internal and should not be called directly.
*
* It handles the case of a call to semRWGive_inline() with 'minimal'
* options by a reader task owning the semaphore.
*
* RETURNS: OK
* ERRNO: N/A
* \is
* \ie
* NOMANUAL
*/

_WRS_INLINE STATUS _semRMinGive_inline
    (
    SEM_ID      semId,                  /* semaphore ID to give */
    int         options                 /* semaphore options */
    )
    {
    atomic32_t *pSemVal = &SEM_RWMIN_VALUE(semId);
    atomic32Val_t v;

    /* Note, the required memory barrier was done in semRWGive_inline(). */

    while (TRUE)
	{
	v = vxAtomic32Get_inline (pSemVal);

	semrw_kassert ((v & SEM_RWMIN_VAL_W_OWNS) == 0);
	semrw_kassert ((v & ~SEM_RWMIN_VAL_PEND) != 0);

	/*
	 * Note, this is the only case were *pSemVal may be legitimately
	 * modified outside of obj/kernel lock when SEM_RWMIN_VAL_PEND is set:
	 * a reader-owner other than the last reader-owner may decrement the
	 * reader count when giving the semaphore.
	 */
	if (v == (SEM_RWMIN_VAL_R_INC | SEM_RWMIN_VAL_PEND))
	    break;
	if (vxAtomic32Cas (pSemVal, v, v - SEM_RWMIN_VAL_R_INC))
	    return OK;
	}

    /*
     * This is the last reader-owner and there are tasks pended.
     * Have to enter the kernel.
     */
    return semRMinGiveHard (semId, options);
    }

/*******************************************************************************
*
* _semWMinGive_inline - give a minimal reader/writer semaphore in write mode
*
* This routine is internal and should not be called directly.
*
* It handles the case of a call to semRWGive_inline() with 'minimal'
* options by a writer task owning the semaphore.
*
* RETURNS: OK
* ERRNO: N/A
* \is
* \ie
* NOMANUAL
*/

_WRS_INLINE STATUS _semWMinGive_inline
    (
    SEM_ID	semId,			/* semaphore ID to give */
    int         options                 /* semaphore options */
    )
    {
    atomic32_t *pSemVal = &SEM_RWMIN_VALUE(semId);
    atomic32Val_t v;

    /* The required memory barrier was done in semRWGive_inline() */

    while (TRUE)
	{
	v = vxAtomic32Get_inline (pSemVal);

	semrw_kassert ((v & SEM_RWMIN_VAL_W_OWNS) != 0);
	semrw_kassert ((v & ~(SEM_RWMIN_VAL_PEND|SEM_RWMIN_VAL_W_OWNS)) == 0);

	if ((v & SEM_RWMIN_VAL_PEND) != 0)
	    break;
	if (vxAtomic32Cas (pSemVal, v, 0))
	    return OK;
	}

    /* There are tasks pended. Have to enter the kernel. */

    return semWMinGiveHard (semId, options);
    }

/*******************************************************************************
*
* semRWGive_inline - give a reader/writer semaphore (inline version)
*
* This routine gives a reader/writer semaphore.
*
* The behavior of this routine is similar to that of semRWGive() on a
* reader/writer semaphore, differing in that an additional parameter,
* <options>, must  be specified.  The <options> parameter allows scaling
* support for particular semaphore features out of the call to this routine.
*
* The semaphore specified by <semId> must be of the reader/writer type.
*
* The options specified by <options> are called 'minimal' if the following
* options are not enabled:
*    SEM_DELETE_SAFE
*    SEM_INVERSION_SAFE
*    SEM_EVENTSEND_ERR_NOTIFY
* and the following (negative) options are enabled:
*    SEM_NO_RECURSE
*    SEM_NO_EVENT_SEND
*    SEM_NO_ID_VALIDATE
*
* If the options are 'minimal', one of the special pseudo-options
* SEM_RW_READER_CALL or SEM_RW_WRITER_CALL may also be specified to omit
* (compile out) the dynamic test of whether the semaphore is currently
* reader-owned or writer-owned, provided the calling code knows this.
*
* For best scalability, this inline routine should be called with
* a compile-time-constant options value, so that the compiler may optimize
* away inapplicable code branches.
*/

_WRS_INLINE STATUS semRWGive_inline
    (
    SEM_ID      semId,                  /* semaphore ID to give */
    int         options                 /* semaphore options */
    )
    {
    atomic32_t *pSemVal;
    atomic32Val_t val;

    if ((options & ~(SEM_RW_OPTIONS_MASK_INLINE |
		     SEM_RW_WRITER_CALL | SEM_RW_READER_CALL)) != 0)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

#ifdef  _WRS_CONFIG_SV_INSTRUMENTATION
    if ((options & SEM_NO_SYSTEM_VIEWER) == 0)
	{
	_Vx_usr_arg_t owner;
	_Vx_usr_arg_t recurse;

	if (SEM_RW_OPTIONS_ARE_MINIMAL(options))
	    {
	    /*
	     * Note: We replace semId->semOwner with *pSemVal,
	     * and replace semId->recurse with 0xabadcafe
	     * for minimal semaphores. Hopefully sticking
	     * with EVT_OBJ_3 (used by semGive()) will lead to less
	     * confusion on the system-viewer host side and still
	     * provide useful information, even if a couple of the
	     * event fields are mislabelled in the display.
	     * An alternative might be to introduce a new event type...
	     */
	    pSemVal = &SEM_RWMIN_VALUE(semId);
	    owner = (_Vx_usr_arg_t)vxAtomic32Get_inline(pSemVal);
	    recurse = (_Vx_usr_arg_t)0xabadcafe;
	    }
	else
	    {
	    /*
	     * In the full-featured case, the generic semGive() code
	     * would emit the object-level EVENT_SEMGIVE. Since
	     * we call semRWGive() directly, we must do it here.
	     */
	    owner = (_Vx_usr_arg_t)semId->semOwner;
	    recurse = (_Vx_usr_arg_t)semId->recurse;
	    }

	/* system viewer - level 1 event logging */
	EVT_OBJ_3 (semId, semClassId, EVENT_SEMGIVE, semId, owner, recurse);
	}
#endif  /* _WRS_CONFIG_SV_INSTRUMENTATION */


    if (SEM_RW_OPTIONS_ARE_MINIMAL(options))
	{
	if ((options & SEM_NO_ERROR_CHECK) == 0)
	    {
	    if (_semRWIsrCheck() != OK)
		return ERROR;
	    if (! SEM_IS_MINIMAL (semId))
		{
		(void) errnoSet (S_semLib_INVALID_OPERATION);
		return ERROR;
		}
	    }

	/*
	 * Ensure that loads or stores done while holding the lock
	 * are globally seen as occurring before the stores that release
	 * the lock.
	 */
	VX_MEM_BARRIER_RW();

	if ((options & (SEM_RW_READER_CALL | SEM_RW_WRITER_CALL)) == 0)
	    {
	    /*
	     * Will have to determine if the caller is a reader or writer
	     * dynamically.
	     */
	    pSemVal = &SEM_RWMIN_VALUE(semId);
	    val = vxAtomic32Get_inline(pSemVal);
	    if ((options & SEM_NO_ERROR_CHECK) == 0)
		{
		if (0 == (val & ~SEM_RWMIN_VAL_PEND))
		    {
		    /* The semaphore appears unowned. */
		    (void) errnoSet (S_semLib_INVALID_OPERATION);
		    return ERROR;
		    }
		}
	    }
	else
	    val = 0;

	if ((options & SEM_RW_WRITER_CALL) != 0
            || (val & SEM_RWMIN_VAL_W_OWNS) != 0)
	    return _semWMinGive_inline (semId, options & ~SEM_RW_WRITER_CALL);
	else
	    return _semRMinGive_inline (semId, options & ~SEM_RW_READER_CALL);
	}
    else /* non-minimal options */
	{
	/*
	 * For now, we handle only the full-featured case by calling
	 * semRWGive().
	 */
	if ((options & SEM_NO_ERROR_CHECK) == 0)
	    {
	    if (SEM_IS_MINIMAL (semId))
		{
		(void) errnoSet (S_semLib_INVALID_OPERATION);
		return ERROR;
		}
	    }
	return semRWGive (semId);
	}
    }

/*******************************************************************************
*
* semWTake_inline - take a reader/writer semaphore in write mode (inline version)
*
* This routine takes a reader/writer semaphore in write mode.
*
* The behavior of this routine is similar to that of semWTake() on a
* reader/writer semaphore, differing in that an additional parameter,
* <options>, must  be specified.  The <options> parameter allows scaling
* support for particular semaphore features out of the call to this routine.
*
* The semaphore specified by <semId> must be of the reader/writer type.
*/

_WRS_INLINE STATUS semWTake_inline
    (
    SEM_ID      semId,                  /* semaphore ID to take */
    _Vx_ticks_t timeout,                /* timeout in ticks */
    int         options                 /* semaphore options */
    )
    {
    if ((options & ~SEM_RW_OPTIONS_MASK_INLINE) != 0)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

    if (SEM_RW_OPTIONS_ARE_MINIMAL(options))
	{
	atomic32_t *pSemVal = &SEM_RWMIN_VALUE(semId);
	atomic32Val_t v;

#ifdef	_WRS_CONFIG_SV_INSTRUMENTATION
	if (0 == (options & SEM_NO_SYSTEM_VIEWER))
	    {
	    /* system viewer - level 1 event logging */
	    /*
	     * Note: We replace semId->semOwner with *pSemVal,
	     * and replace semId->recurse with 0xabadcafe
	     * for minimal semaphores. Hopefully sticking
	     * with EVT_OBJ_3 (used by semWTake()) will lead to less
	     * confusion on the system-viewer host side and still
	     * provide useful information, even if a couple of the
	     * event fields are mislabelled in the display.
	     * An alternative might be to introduce a new event type...
	     */
	    EVT_OBJ_3 (semId, semClassId, EVENT_SEMWTAKE,
		       semId, *pSemVal, 0xabadcafe);
	    }
#endif /* _WRS_CONFIG_SV_INSTRUMENTATION */

	if ((options & SEM_NO_ERROR_CHECK) == 0)
	    {
	    if (_semRWIsrCheck() != OK)
		return ERROR;
	    if (timeout != WAIT_FOREVER || !SEM_IS_MINIMAL (semId))
		{
		(void) errnoSet (S_semLib_INVALID_OPERATION);
		return ERROR;
		}
	    }

	while (TRUE)
	    {
	    v = vxAtomic32Get_inline (pSemVal);
	    semrw_kassert ((v & SEM_RWMIN_VAL_W_OWNS) == 0 ||
			   (v & ~(SEM_RWMIN_VAL_W_OWNS | SEM_RWMIN_VAL_PEND)) == 0);

	    if (v != 0)
		break;

	    if (vxAtomic32Cas (pSemVal, 0, SEM_RWMIN_VAL_W_OWNS))
		{
		VX_INSTR_BARRIER();
		return OK;
		}
	    }

	/* The semaphore appears to be owned; must enter the kernel. */
	return semWMinTakeHard (semId, options);
	}
    else /* non-minimal options */
	{
	/*
	 * For now, we handle only the full-featured case by calling
	 * semWTake().
	 */
	if ((options & SEM_NO_ERROR_CHECK) == 0)
	    {
	    if (SEM_IS_MINIMAL (semId))
		{
		(void) errnoSet (S_semLib_INVALID_OPERATION);
		return ERROR;
		}
	    }
	return semWTake (semId, timeout);
	}
    }

/*******************************************************************************
*
* semRTake_inline - take a reader/writer semaphore in read mode (inline version)
*
* This routine takes a reader/writer semaphore in read mode.
*
* The behavior of this routine is similar to that of semRTake() on a
* reader/writer semaphore, differing in that an additional parameter,
* <options>, must  be specified.  The <options> parameter allows scaling
* support for particular semaphore features out of the call to this routine.
*
* The semaphore specified by <semId> must be of the reader/writer type.
*/

_WRS_INLINE STATUS semRTake_inline
    (
    SEM_ID      semId,                 /* semaphore ID to take */
    _Vx_ticks_t timeout,               /* timeout in ticks */
    int         options                /* semaphore options */
    )
    {
    if ((options & ~SEM_RW_OPTIONS_MASK_INLINE) != 0)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

    if (SEM_RW_OPTIONS_ARE_MINIMAL(options))
	{
	atomic32_t *pSemVal = &SEM_RWMIN_VALUE(semId);
	atomic32Val_t v;

#ifdef	_WRS_CONFIG_SV_INSTRUMENTATION
	if (0 == (options & SEM_NO_SYSTEM_VIEWER))
	    {
	    /* system viewer - level 1 event logging */
	    /*
	     * Note: We replace semId->semOwner with *pSemVal,
	     * and replace semId->recurse with 0xabadcafe
	     * for minimal semaphores. Hopefully sticking
	     * with EVT_OBJ_3 (used by semRTake()) will lead to less
	     * confusion on the system-viewer host side and still
	     * provide useful information, even if a couple of the
	     * event fields are mislabelled in the display.
	     * An alternative might be to introduce a new event type...
	     */
	    EVT_OBJ_3 (semId, semClassId, EVENT_SEMRTAKE,
		       semId, *pSemVal, 0xabadcafe);
	    }
#endif /* _WRS_CONFIG_SV_INSTRUMENTATION */

	if ((options & SEM_NO_ERROR_CHECK) == 0)
	    {
	    if (_semRWIsrCheck() != OK)
		return ERROR;
	    if (timeout != WAIT_FOREVER	|| !SEM_IS_MINIMAL (semId))
		{
		(void) errnoSet (S_semLib_INVALID_OPERATION);
		return ERROR;
		}
	    }

	while (TRUE)
	    {
	    v = vxAtomic32Get_inline (pSemVal);
	    semrw_kassert ((v & SEM_RWMIN_VAL_W_OWNS) == 0 ||
			   (v & ~(SEM_RWMIN_VAL_W_OWNS | SEM_RWMIN_VAL_PEND)) == 0);

	    if ((v & (SEM_RWMIN_VAL_W_OWNS | SEM_RWMIN_VAL_PEND)) != 0)
		break;

	    if (vxAtomic32Cas (pSemVal, v, v + SEM_RWMIN_VAL_R_INC))
		{
		VX_INSTR_BARRIER();
		return OK;
		}
	    }
	/*
	 * A writer owns the semaphore, or there are pended tasks. Enter
	 * the kernel. Note that the minimal case code does not
	 * implement timeouts.
	 */
	return semRMinTakeHard (semId, options);
	}
    else /* non-minimal options */
	{
	/* For now, handle the full-featured case by calling semRTake(). */
	if ((options & SEM_NO_ERROR_CHECK) == 0)
	    {
	    if (SEM_IS_MINIMAL (semId))
		{
		(void) errnoSet (S_semLib_INVALID_OPERATION);
		return ERROR;
		}
	    }
	return semRTake (semId, timeout);
	}
    }

/***************************************************************************
*
* semRWMinOwner_inline - return the owner type of a mimimal reader-writer semaphore
*
* This function returns a value that indicates whether the semaphore
* is currently unowned, held by readers, or owned by a single writer.
*
* WARNING:
* The value returned is only valid and stable if the caller is in fact
* a task currently owning the semaphore as either a reader or a writer.
*
* RETURNS:
* \is
* \i 'SEM_RW_MODE_UNOWNED'
* if the semaphore is currently unheld.
*
* \i 'SEM_RW_MODE_READ'
* if the semaphore is held by one or more reader tasks.
*
* \i 'SEM_RW_MODE_WRITE'
* if the semaphore is owned by a writer task.
* \ie
*/
_WRS_INLINE int semRWOwner_inline
    (
    SEM_ID semId,               /* the RW semaphore */
    int options                 /* semaphore options */
    )
    {
    if ((options & ~SEM_RW_OPTIONS_MASK_INLINE) != 0)
	{
	errno = S_semLib_INVALID_OPTION;
	return (ERROR);
	}

    if (SEM_RW_OPTIONS_ARE_MINIMAL(options))
	{
	atomic32_t *pSemVal = &SEM_RWMIN_VALUE(semId);
	atomicVal_t v = vxAtomic32Get_inline (pSemVal);

	if ((options & SEM_NO_ERROR_CHECK) == 0)
	    {
	    if (! SEM_IS_MINIMAL (semId))
		{
		(void) errnoSet (S_semLib_INVALID_OPERATION);
		return ERROR;
		}
	    }

	if (v == 0)    /* PEND bit will not be set if un-owned... */
	    return SEM_RW_MODE_UNOWNED;  /* no-one owns it */
	if (v & SEM_RWMIN_VAL_W_OWNS)
	    return SEM_RW_MODE_WRITE;    /* writer owns it */
	return SEM_RW_MODE_READ;         /* reader owns it */
	}
    else
	{
	if ((options & SEM_NO_ERROR_CHECK) == 0)
	    {
	    if (SEM_IS_MINIMAL (semId))
		{
		(void) errnoSet (S_semLib_INVALID_OPERATION);
		return ERROR;
		}
	    }

	/*
	 * If this task is an owner (either read or write) of the semaphore,
	 * then semId->semOwner is stable, even though we have not entered the
	 * kernel.
	 */
	if (semId->semOwner != NULL)
	    return SEM_RW_MODE_WRITE;
	/*
	 * If this task is a read-owner of the semaphore, then
	 * SEMRW_READ_CNT(semId) is stably non-zero.
	 */
	if (SEMRW_READ_CNT(semId) != 0)
	    return SEM_RW_MODE_READ;

	return SEM_RW_MODE_UNOWNED;
	}
    }


#endif /* !defined (_ASMLANGUAGE) */

#endif /* __INCsemRWLibInlinePh */

