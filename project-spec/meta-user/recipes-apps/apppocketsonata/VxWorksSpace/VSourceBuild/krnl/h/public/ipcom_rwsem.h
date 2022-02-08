/* ipcom_rwsem.h - reader/writer semaphore API */

/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_RWSEM_H
#define IPCOM_RWSEM_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
DESCRIPTION
This library contains the API for IPCOM reader/writer semaphores.
INCLUDE FILES: ipcom_rwsem.h
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
 *                         RWSEM INVALID
 *===========================================================================
 */
#define IPCOM_RWSEM_INVALID       IP_NULL


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* Read/write semaphore types */
typedef enum Ipcom_rwsem_lock_mode_enum
{
    IPCOM_RWSEM_UNLOCKED = 0,
    IPCOM_RWSEM_READ,
    IPCOM_RWSEM_WRITE
}
Ipcom_rwsem_lock_mode;

typedef void * Ipcom_rwsem;


/*
 ****************************************************************************
 * 6                 PUBLIC FUNCTIONS
 ****************************************************************************
 */

/******************************************************************************
*
* ipcom_rwsem_create - create a read/write semaphore and initialize its counter
*
* This routine creates a read/write semaphore and initializes its counter to 1,
* i.e the semaphore is initially unlocked.
* semaphore handle is obtained in the location pointed to by <sem>.
*
* Parameters:
* \is
* \i <sem>
* Pointer to a location to store the semaphore handle in.
* \ie
*
* RETURNS: 'IPCOM_SUCCESS', or an error value defined in 'include/ipcom_err.h'.
*
* ERRNO: \&'IPCOM_ERR_FAILED'
*/
IP_PUBLIC Ip_err ipcom_rwsem_create
(
    Ipcom_rwsem *sem
);


/******************************************************************************
*
* ipcom_rwsem_delete - delete a read/write semaphore
*
* This routine deletes a semaphore.
*
* Parameter:
* \is
* \i <sem>
* Pointer to semaphore handle.
* \ie
*
* RETURNS: 'IPCOM_SUCCESS', or an error value defined in 'include/ipcom_err.h'.
*
* ERRNO: \&'IPCOM_ERR_FAILED'
*/
IP_PUBLIC Ip_err ipcom_rwsem_delete
(
    Ipcom_rwsem *sem
);


/******************************************************************************
*
* ipcom_sem_lock_mode - get the current lock mode of the read/write semaphore
*
* This routine gets the current lock mode which can be one of
* unlocked, read or write.
*
* Parameter:
* \is
* \i <sem>
* Semaphore handle.
* \ie
*
* RETURNS: The lock mode of the read/write semaphore.
*
* ERRNO: None.
*/
IP_PUBLIC Ipcom_rwsem_lock_mode ipcom_rwsem_lock_mode
(
    Ipcom_rwsem sem
);

#ifdef IPCOM_RWSEM_MODE_SPLIT
IP_PUBLIC void ipcom_rwsem_wait_rd (Ipcom_rwsem sem);
IP_PUBLIC void ipcom_rwsem_wait_wr (Ipcom_rwsem sem);
IP_PUBLIC void ipcom_rwsem_post_rd (Ipcom_rwsem sem);
IP_PUBLIC void ipcom_rwsem_post_wr (Ipcom_rwsem sem);
#endif

/******************************************************************************
*
* ipcom_rwsem_wait - acquire the read/write semaphore
*
* This routine acquires the reader/writer semaphore <sem>. The caller will
* be blocked if
* \ms
* \m -
* there is at least one writer already holding or waiting for the lock
* \m -
* there is at least one reader already holding the lock and the caller
* tries to acquire it in write mode
* \me
* Parameter:
* \is
* \i <sem>
* Semaphore handle.
* \i <mode>
* Semaphore lock type.
* \ie
*
* Do not attempt to aquire recursively a read/write semaphore that is
* already held; doing so has undefined results.
*
* RETURNS: N/A
* ERRNO: None.
*/
#ifdef IPCOM_RWSEM_MODE_SPLIT
IP_INLINE void ipcom_rwsem_wait
(
     Ipcom_rwsem sem,
     Ipcom_rwsem_lock_mode mode
)
{
    if (mode == IPCOM_RWSEM_READ)
	ipcom_rwsem_wait_rd(sem);
    else if (mode == IPCOM_RWSEM_WRITE)
	ipcom_rwsem_wait_wr(sem);
    else
    {
	IP_PANIC();
    }
}
#else
IP_FASTTEXT IP_PUBLIC void ipcom_rwsem_wait
(
     Ipcom_rwsem sem,
     Ipcom_rwsem_lock_mode mode
);
#endif /* IPCOM_RWSEM_MODE_SPLIT */

/******************************************************************************
*
* ipcom_rwsem_post - release the read/write semaphore
*
* This routine releases the read/write semaphore. It must be called
* in a thread that currently holds the semaphore, having acquired in in
* an earlier call to ipcom_rwsem_wait().
* When the writer (or all readers, if locked in read mode) have released
* the semaphore:
* \ms
* \m -
* If there are any waiting writers, the first will be awakened and will
* aquire the semaphore.
* \m -
* Otherwise, all waiting readers will be awakened and will jointly acquire
* the semaphore.
* \me
*
* Parameter:
* \is
* \i <sem>
* Semaphore handle.
* \ie
*
* RETURNS: N/A.
* ERRNO: None.
*/
#ifdef IPCOM_RWSEM_MODE_SPLIT
IP_INLINE void ipcom_rwsem_post
(
    Ipcom_rwsem sem
)
{
    Ipcom_rwsem_lock_mode mode = ipcom_rwsem_lock_mode (sem);
    if (mode == IPCOM_RWSEM_READ)
	ipcom_rwsem_post_rd(sem);
    else if (mode == IPCOM_RWSEM_WRITE)
	ipcom_rwsem_post_wr(sem);
    else
    {
	IP_PANIC();
    }
}
#else
IP_FASTTEXT IP_PUBLIC void ipcom_rwsem_post
(
    Ipcom_rwsem sem
);
#endif /* IPCOM_RWSEM_MODE_SPLIT */


/******************************************************************************
*
* ipcom_rwsem_wait_rd - acquire the read/write semaphore in read mode
*
* This routine acquires the reader/writer semaphore <sem> in read mode.
* The caller will be blocked if
* - there is at least one writer already holding or waiting for the lock
* Parameter:
* \is
* \i <sem>
* Semaphore handle.
* \ie
*
* Calling this routine is equivalent to calling ipcom_rwsem_wait() with
* the IPCOM_RWSEM_READ mode.
*
* Do not attempt to aquire recursively a read/write semaphore that is
* already held; doing so has undefined results.
*
* RETURNS: N/A
* ERRNO: None.
*/
#ifdef IPCOM_RWSEM_MODE_SPLIT
IP_PUBLIC void ipcom_rwsem_wait_rd
(
     Ipcom_rwsem sem
);
#else
IP_INLINE void ipcom_rwsem_wait_rd
(
     Ipcom_rwsem sem
)
{
    ipcom_rwsem_wait(sem, IPCOM_RWSEM_READ);
}
#endif /* IPCOM_RWSEM_MODE_SPLIT */

/******************************************************************************
*
* ipcom_rwsem_wait_wr - acquire the read/write semaphore in write mode
*
* This routine acquires the reader/writer semaphore <sem> in read mode.
* The caller will be blocked if:
* \ms
* \m -
* there is at least one writer already holding or waiting for the lock
* \m -
* there is at least reader already holding the lock
* \me
* Parameter:
* \is
* \i <sem>
* Semaphore handle.
* \ie
*
* Calling this routine is equivalent to calling ipcom_rwsem_wait() with
* the IPCOM_RWSEM_WRITE mode.
*
* Do not attempt to aquire recursively a read/write semaphore that is
* already held; doing so has undefined results.
*
* RETURNS: N/A
* ERRNO: None.
*/
#ifdef IPCOM_RWSEM_MODE_SPLIT
IP_PUBLIC void ipcom_rwsem_wait_wr
(
     Ipcom_rwsem sem
);
#else
IP_INLINE void ipcom_rwsem_wait_wr
(
     Ipcom_rwsem sem
)
{
    ipcom_rwsem_wait(sem, IPCOM_RWSEM_WRITE);
}
#endif /* IPCOM_RWSEM_MODE_SPLIT */


/******************************************************************************
*
* ipcom_rwsem_post_rd - release the read/write semaphore held in read mode
*
* This routine releases the read/write semaphore.
* It must be called in a thread that currently holds the semaphore in read
* mode.
* When all readers have released the semaphore:
* \ms
* \m -
* If there are any waiting writers, the first will be awakened and will
* aquire the semaphore.
* \me
*
* Parameter:
* \is
* \i <sem>
* Semaphore handle.
* \ie
*
* Calling this routine is equivalent to calling ipcom_rwsem_post()
* when the semaphore is held in read mode.
*
* RETURNS: N/A
* ERRNO: None.
*/
#ifdef IPCOM_RWSEM_MODE_SPLIT
IP_PUBLIC void ipcom_rwsem_post_rd
(
    Ipcom_rwsem sem
);
#else
IP_INLINE void ipcom_rwsem_post_rd
(
    Ipcom_rwsem sem
)
{
    ipcom_rwsem_post(sem);
}
#endif /* IPCOM_RWSEM_MODE_SPLIT */

/******************************************************************************
*
* ipcom_rwsem_post_wr - release the read/write semaphore held in write mode
*
* This routine releases the read/write semaphore.
* It must be called in a thread that currently holds the semaphore in write
* mode. When this routine is called:
* \ms
* \m -
* If there are any waiting writers, the first will be awakened and will
* aquire the semaphore.
* \m -
* Otherwise, all waiting readers are awakened and jointly acquire the
* semaphore.
* \me
*
* Parameter:
* \is
* \i <sem>
* Semaphore handle.
* \ie
*
* Calling this routine is equivalent to calling ipcom_rwsem_post()
* when the semaphore is held in write mode.
*
* RETURNS: N/A
* ERRNO: None.
*/
#ifdef IPCOM_RWSEM_MODE_SPLIT
IP_PUBLIC void ipcom_rwsem_post_wr
(
    Ipcom_rwsem sem
);
#else
IP_INLINE void ipcom_rwsem_post_wr
(
    Ipcom_rwsem sem
)
{
    ipcom_rwsem_post(sem);
}
#endif /* IPCOM_RWSEM_MODE_SPLIT */


#ifdef __cplusplus
}
#endif

#endif /* IPCOM_RWSEM_H */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

