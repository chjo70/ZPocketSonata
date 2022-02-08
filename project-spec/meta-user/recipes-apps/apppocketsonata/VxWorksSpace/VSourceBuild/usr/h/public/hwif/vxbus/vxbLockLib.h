/* vxbLockLib.h - VxBus lock library header file */

/*
 * Copyright (c) 2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02oct15,wap  Update vxbLockLib to use semaphores when build for
             user-space since there are no spinlocks there
29sep15,wap  Add support for user-space VxBus interface (F2165)
17jul13,l_z  Created
*/

#ifndef _INC_VXBLOCKLIB_H
#define _INC_VXBLOCKLIB_H

#ifdef __cplusplus
extern "C" {
#endif

/* VxBus locks */

typedef struct vxBusLock
    {
    FUNCPTR             lockFunc;
    FUNCPTR             unlockFunc;
    BOOL                locksEnabled;
#ifdef _WRS_KERNEL
    spinlockIsr_t       lock;
#else
    SEM_ID		lock;
#endif /* _WRS_KERNEL */
    } VXBUS_LOCK;

typedef VXBUS_LOCK * VXBUS_LOCK_ID;

#define VXB_LOCK(lock)  \
        (lock)->lockFunc == NULL ? OK : \
        ((lock)->lockFunc)(lock)

#define VXB_UNLOCK(lock)        \
        (lock)->unlockFunc == NULL ? OK : \
        ((lock)->unlockFunc)(lock)

#ifdef __cplusplus
}
#endif

#endif /* _INC_VXBLOCKLIB_H */
