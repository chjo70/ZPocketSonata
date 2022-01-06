/* semLibP.h - private user semaphore library header file */

/*
 * Copyright (c) 2003-2010, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
09jan17,dlk  Quiet a CHECKED_RETURN static analysis warning (F972)
02sep10,s_s  fixed compiler warnings
16jun10,pcs  change the data type of timeout from an int to _Vx_ticks_t
07may10,gls  made semRWInit() global
18jan10,cww  LP64 adaptation
01may09,gls  Added use semaphore support for SMP
27jul07,gls  Added SEM_OWNER_GET()
27jul07,gls  added check for NULL semId in IS_SEM_VALID()
20jul07,jmg  Added SEM_DECL().
24jul06,jpb  Removed duplicate definition of SEMAPHORE.
22sep04,md   CI changes
22mar04,dcc  added SEM_TYPE_NAMED
11feb04,hya  made user event changes.
30oct03,md   created.
*/

#ifndef __INCsemLibPh
#define __INCsemLibPh

#include <vxWorks.h>
#include <semLib.h>
#include <private/semULibP.h>
#include <vxAtomicLib.h>
#include <private/base/b_struct_vx_semaphore.h>  /* needed for _Vx_SEMAPHORE */
#include <private/vxSysInfoCommonP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* semaphore types */

#define MAX_SEM_TYPE		8	/* maximum # of sem classes */

#define SEM_TYPE_MASK		0x7	/* semaphore class mask */

#define SEM_TYPE_USER		0x10	/* semaphore lives in user space */
#define SEM_TYPE_KERNEL		0x00	/* semaphore lives in kernel space */
#define SEM_TYPE_NAMED		0x20	/* semaphore was created by semOpen().
					 * Must follow the close+unlink model
					 * for deletion */

#define SEM_SPACE_MASK		0x10	/* semaphore address space mask */

					/* magic number to identify sem struct*/
#define SEM_MAGIC		0xBABEF00D

/* macro to check if semaphore structure is valid */

#define	IS_SEM_VALID(x) if ((x == NULL) || ((x)->magic != SEM_MAGIC)) \
			    {					      \
			    errno = S_objLib_OBJ_ID_ERROR;	      \
			    return (ERROR);			      \
			    }

#define SEM_DECL(x) SEMAPHORE x = {0, 0, 0, 0, 0, 0, {0}, {0}}

/*
 * NOTE:  semId is not verified.  Do not pass in an invalid semaphore!
 *
 * See the entry for _wrs_semOwnerGet().
 */

#define SEM_OWNER_GET(semId) _wrs_semOwnerGet(semId)

/*******************************************************************************
*
* _wrs_semOwnerGet - return ID of task that owns a semaphore
*
* This routine returns the TASK_ID of the owner of semaphore <semId>.  If
* <semId> is free NULL will be returned.
*
* Note, this routine does not verify that <semId> is a valid semaphore.  It
* is critical that the caller does not call this routine with an invalid
* semaphore ID.
*
* INTERNAL
* This routine is designated __inline__, meaning its code will be replicated
* for each use.
*
* RETURNS: TASK_ID of semaphore owner, else TASK_ID_NULL
*
* ERRNO: N/A
*
* \NOMANUAL
*/

_WRS_INLINE TASK_ID _wrs_semOwnerGet
    (
    SEM_ID semId
    )
    {
    /*
     * If the semaphore is a kernel semaphore, perform a system call to
     * get the owner (if any).
     */

    if ((semId->semType & SEM_TYPE_USER) == 0)
	{
        /* 0 = TASK_ID_NULL = SEM_USER_NO_OWNER in case there is no owner... */
        TASK_ID ownerId = (TASK_ID)0;

	(void)semCtl ((SEM_ID_KERNEL) semId->semId_k, VX_SEM_CTL_SEM_OWNER,
                      &ownerId, NULL);

	return (ownerId);
	}

    /* this is a user level semaphore, return the semOwner field */

    if (_VX_IS_SYS_MODE_UP)
	{
	return ((TASK_ID) semId->state.owner);
	}
    else
	{
	return ((TASK_ID)
		(vxAtomic32Get ((atomic32_t *) &semId->state.owner) &
		 ~SEM_USER_K_OWNED));
	}
    }

#if !defined(_ASMLANGUAGE)

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
typedef _Vx_SEMAPHORE SEMAPHORE;
#endif

#define semCount	state.count
#define semOwner	state.owner

/* function declarations */

extern STATUS	semTerminate	(SEM_ID semId);
extern STATUS	semDestroy	(SEM_ID semId, BOOL dealloc);
extern STATUS	semBInit	(SEMAPHORE *pSem, int options,
				 SEM_B_STATE initialState);
extern STATUS	semUBGive	(SEM_ID semId);
extern STATUS	semUBTake	(SEM_ID semId, _Vx_ticks_t timeout);
extern STATUS	semMInit	(SEMAPHORE *pSem, int options);
extern STATUS	semUMGive	(SEM_ID semId);
extern STATUS	semUMTake	(SEM_ID semId, _Vx_ticks_t timeout);
extern STATUS	semCInit	(SEMAPHORE *pSem, int options,
				 int initialCount);
extern STATUS	semUCGive	(SEM_ID semId);
extern STATUS	semUCTake	(SEM_ID semId, _Vx_ticks_t timeout);

extern STATUS   semRWInit       (SEMAPHORE * pSem, int options,
				 int maxReaders);

#endif /* !defined(_ASMLANGUAGE) */

#ifdef __cplusplus
}
#endif

#endif /* __INCsemLibPh */
