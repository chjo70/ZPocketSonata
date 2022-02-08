/* usrRtpBaseLib.c - kernel/user-space RTP facilities */

/*
 * Copyright (c) 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16nov17,dlk  created
*/

/*
DESCRIPTION

The functions in this configlette support RTP locking.
In cases where RTP support is not enabled in either the
VSB or the VIP, locking the RTP just reduces to taking
the kernel RTP mutex semaphore.  Otherwise, the locking
functions perform more elaborate checks to avoid certain
deadlock conditions that could otherwise occur when an
RTP is being deleted or stopped.

These functions are defined here to avoid linking with
rtpLib in the case that INCLUDE_RTP is not enabled in
the VIP.
*/

#include <private/rtpLibP.h>  /* for WIND_RTP */

/*******************************************************************************
*
* usrRtpLock - lock the RTP unless it is being deleted
*
* This function takes the mutex guarding the RTP <rtpId>. However, if the
* RTP deletion process has started (that is, if a deleter task has been
* elected), and if the calling task is not the deleter task, this function
* immediately releases the mutex and returns ERROR, with errno either
* <S_rtpLib_ACCESS_DENIED> or EDOOM. (EDOOM is returned if the calling task
* belongs to the RTP.)
*
* The function may also fail if the RTP deletion process has completed
* (so that the RTP mutex has been destroyed).
*
* This function should never fail if <rtpId> is the kernel RTP ID.
*
* If this function returns OK, the RTP has been locked and a later
* call to RTP_UNLOCK() should be made to unlock the RTP.
*
* If a pointer to the calling task's WIND_TCB is already available
* in a local variable, calling usrRtpLockWithCallerTcb() may be
* slightly more efficient than calling this function.
*
* SMP CONSIDERATIONS
* This API is spinlock and intCpuLock restricted.
*
* RETURNS: OK if the RTP is successfully locked. ERROR otherwise
*
* ERRNOS: EDOOM, S_rtpLib_ACCESS_DENIED, S_objLib_OBJ_ID_ERROR
*
* SEE ALSO: usrRtpLockWithCallerTcb()
*
* \NOMANUAL
*/

STATUS usrRtpLock
    (
    WIND_RTP *  rtpId        /* pointer to RTP to be locked */
    )
    {
#if defined(_WRS_CONFIG_RTP) && defined(INCLUDE_RTP)
    return rtpLockWithCallerTcb (rtpId, taskIdCurrent);
#else
    return semTake (rtpId->semId, WAIT_FOREVER);
#endif
    }

/*******************************************************************************
*
* usrRtpLockWithCallerTcb - lock the RTP unless it is being deleted
*
* This function takes the mutex guarding the RTP <rtpId>, for the calling
* task <pCallerTcb>. However, if the RTP deletion process has started
* (that is, if a deleter task has been elected), and if the calling task is
* not the deleter task, this function immediately releases the mutex and
* returns ERROR, with errno either <S_rtpLib_ACCESS_DENIED> or EDOOM.
* (EDOOM is returned if the calling task belongs to the RTP.)
*
* The function may also fail if the RTP deletion process has completed
* (so that the RTP mutex has been destroyed).
*
* This function should never fail if <rtpId> is the kernel RTP ID.
*
* If this function returns OK, the RTP has been locked and a later
* call to RTP_UNLOCK() should be made to unlock the RTP.
*
* Calling this function is essentially equivalent to calling
* RTP_LOCK (rtpId) or usrRtpLock(), except that it may be more efficient
* if the caller's TCB pointer is already known and available in a local
* variable.
*
* SMP CONSIDERATIONS
* This API is spinlock and intCpuLock restricted.
*
* RETURNS: OK if the RTP is successfully locked. ERROR otherwise
*
* ERRNOS: EDOOM, S_rtpLib_ACCESS_DENIED, S_objLib_OBJ_ID_ERROR
*
* SEE ALSO: usrRtpLock()
*
* \NOMANUAL
*/

STATUS usrRtpLockWithCallerTcb
    (
    WIND_RTP * rtpId,
    WIND_TCB * pCallerTcb
    )
    {
#if defined(_WRS_CONFIG_RTP) && defined(INCLUDE_RTP)
    return rtpLockWithCallerTcb (rtpId, pCallerTcb);
#else
    return semTake (rtpId->semId, WAIT_FOREVER);
#endif
    }

