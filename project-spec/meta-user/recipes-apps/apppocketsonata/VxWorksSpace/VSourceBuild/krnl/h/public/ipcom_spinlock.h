/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_SPINLOCK_H
#define IPCOM_SPINLOCK_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
DESCRIPTION
API for IPCOM spinlocks
*/

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include "ipcom_os.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    SPINLOCK INVALID
 *===========================================================================
 */
#define IPCOM_SPINLOCK_INVALID       IP_NULL


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* Spinlock types */
typedef void * Ipcom_spinlock;

/*
 ****************************************************************************
 * 6                 PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*******************************************************************************
 *
 * ipcom_spinlock_create - create a spinlock
 *
 * This routine creates a new unlocked spinlock.
 *
 * Parameters:
 * \is
 * \i <sl>
 * Pointer to a location to store the spinlock handle in.
 * \ie
 *
 * RETURNS: 'IPCOM_SUCCESS', or an error value defined in 'include/ipcom_err.h'.
 *
 * ERRNO: \&'IPCOM_ERR_FAILED'
 */
IP_PUBLIC Ip_err ipcom_spinlock_create
(
    Ipcom_spinlock *sl
);
#if defined(IPCOM_USE_DMALLOC) && defined(IP_PORT_UNIX)
IP_PUBLIC Ip_err ipcom_dspinlock_create(Ipcom_spinlock *sl,
                                        const char *file,
                                        Ip_u32 line);
#define ipcom_spinlock_create(sl) \
    ipcom_dspinlock_create(sl, __FILE__, __LINE__)
#endif



/*******************************************************************************
 *
 * ipcom_spinlock_delete - delete a spinlock
 *
 * This routine deletes a spinlock.
 *
 * Parameter:
 * \is
 * \i <sl>
 * Pointer to spinlock handle.
 * \ie
 *
 * RETURNS: 'IPCOM_SUCCESS', or an error value defined in 'include/ipcom_err.h'.
 *
 * ERRNO: \&'IPCOM_ERR_FAILED'
 */
IP_PUBLIC Ip_err ipcom_spinlock_delete
(
    Ipcom_spinlock *sl
);


/*******************************************************************************
 *
 * ipcom_spinlock_lock - grab the spinlock.
 *
 * This routine will lock the task-only spinlock <sl>.
 * Such spinlocks may be held locked across calls VxWorks kernel functions
 * unlike the ISR-allowed spinlocks.
 *
 * Parameter:
 * \is
 * \i <sl>
 * Pointer to spinlock handle.
 * \ie
 *
 * RETURNS: \&N/A.
 *
 * ERRNO: None.
 */
IP_FASTTEXT IP_PUBLIC void ipcom_spinlock_lock
(
     Ipcom_spinlock *sl
);


/*******************************************************************************
 *
 * ipcom_spinlock_unlock - release the spinlock
 *
 * This routine releases a spinlock grabbed with ipcom_spinlock_lock().
 *
 * Parameter:
 * \is
 * \i <sl>
 * Pointer to spinlock handle.
 * \i <key>
 *
 * RETURNS: \&N/A.
 *
 * ERRNO: None.
 */
IP_FASTTEXT IP_PUBLIC void ipcom_spinlock_unlock
(
    Ipcom_spinlock *sl
);

#ifdef IP_PORT_VXWORKS
/*******************************************************************************
 *
 * ipcom_spinlock_restricted_create - create a restricted spinlock
 *
 * This routine creates a new, unlocked, restricted spinlock.
 *
 * Restricted spinlocks have some usage restrictions, originating in VxWorks.
 * Typically non-VxWorks ports will implement restricted spinlocks identically
 * to unrestricted spinlocks; but the usage restrictions still apply whenever
 * the restricted spinlock APIs are used in non-port-specific code.
 *
 * Generally, restricted spinlocks should be used in preference to unrestricted
 * spinlocks if the usage restrictions can be observed.
 * 
 * The task holding a locked restricted spinlock may not:
 * \ms
 * \m 1.
 * Call any routine that affects scheduling, either blocking the task itself
 * or changing the readiness of any other task. In VxWorks, this restriction
 * is specifically that the task holding the locked spinlock may not enter
 * the kernel.
 * \m 2.
 * Lock any other spinlock, or call any routine that does so.
 * \me
 *
 * Parameters:
 * \is
 * \i <sl>
 * Pointer to a location in which to store the restricted spinlock handle.
 * \ie
 *
 * RETURNS: 'IPCOM_SUCCESS', or an error value defined in 'include/ipcom_err.h'.
 *
 * ERRNO: \&'IPCOM_ERR_FAILED'
 */
IP_PUBLIC Ip_err ipcom_spinlock_restricted_create
(
    Ipcom_spinlock *sl
);


/*******************************************************************************
 *
 * ipcom_spinlock_restricted_delete - delete a restricted spinlock
 *
 * This routine deletes a restricted spinlock, previously created with
 * ipcom_spinlock_restricted_create().
 *
 * Parameter:
 * \is
 * \i <sl>
 * Pointer to spinlock handle.
 * \ie
 *
 * RETURNS: 'IPCOM_SUCCESS', or an error value defined in 'include/ipcom_err.h'.
 *
 * ERRNO: \&'IPCOM_ERR_FAILED'
 */
IP_PUBLIC Ip_err ipcom_spinlock_restricted_delete
(
    Ipcom_spinlock *sl
);


/*******************************************************************************
 *
 * ipcom_spinlock_restricted_lock - acquire a restricted spinlock
 *
 * This routine will lock the restricted task-only spinlock <sl>.
 * The spinlock must have been created earlier using 
 * ipcom_spinlock_restricted_create().
 *
 * There are restrictions on what a task may do while holding a locked
 * restricted spinlock; see the discussion in the reference entry
 * for ipcom_spinlock_restricted_create().
 *
 * Unlike ipcom_spinlock_lock(), this routine returns a value that must
 * be saved and provided as the second argument to 
 * ipcom_spinlock_restricted_unlock() in order to unlock the spinlock.
 *
 * Parameter:
 * \is
 * \i <sl>
 * Pointer to spinlock handle.
 * \ie
 *
 * RETURNS: \&N/A.
 *
 * ERRNO: None.
 *
 * SEE ALSO: ipcom_spinlock_restricted_create().
 */
IP_FASTTEXT IP_PUBLIC int ipcom_spinlock_restricted_lock
(
     Ipcom_spinlock *sl
);


/*******************************************************************************
 *
 * ipcom_spinlock_restricted_unlock - release the restricted spinlock
 *
 * This routine releases a spinlock acquired with 
 * ipcom_spinlock_restricted_lock().
 *
 * Parameter:
 * \is
 * \i <sl>
 * Pointer to spinlock handle.
 * \i <key>
 * Value returned from ipcom_spinlock_restricted_lock.
 * \ie
 * RETURNS: \&N/A.
 *
 * ERRNO: None.
 */
IP_FASTTEXT IP_PUBLIC void ipcom_spinlock_restricted_unlock
(
    Ipcom_spinlock *sl,
    int             key
);


#else  /* IP_PORT_VXWORKS */

IP_INLINE Ip_err 
ipcom_spinlock_restricted_create(Ipcom_spinlock *sl)
{
    return ipcom_spinlock_create(sl);
}

IP_INLINE Ip_err
ipcom_spinlock_restricted_delete(Ipcom_spinlock *sl)
{
    return ipcom_spinlock_delete(sl);
}

IP_INLINE int
ipcom_spinlock_restricted_lock(Ipcom_spinlock *sl)
{
    ipcom_spinlock_lock(sl);
    return 0;
}

IP_INLINE void
ipcom_spinlock_restricted_unlock(Ipcom_spinlock *sl, int key)
{
    (void)key; /* unused */
    ipcom_spinlock_unlock(sl);
}

#endif /* IP_PORT_VXWORKS */

#ifdef __cplusplus
}
#endif

#endif /* IPCOM_SPINLOCK_H */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

