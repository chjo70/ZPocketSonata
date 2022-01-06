/* usrIo.c - configlette for I/O system */

/*
 * Copyright (c) 2018 Wind River Systems
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03jan18,dlk  written (V7COR-5462)
*/

/*
DESCRIPTION
VIP configlette for the I/O system.
*/

#include <limits.h>
#include <private/iosLibP.h>

#ifndef FD_SETSIZE
#error "FD_SETSIZE is not defined."
#endif

#if NUM_FILES <= 0
#error "NUM_FILES is not properly defined."
#endif

/* RTP_FD_NUM_MAX might be 0 (undefined) if RTP support is not included */

#if RTP_FD_NUM_MAX < 0
#error "RTP_FD_NUM_MAX is not properly defined."
#endif

/*
 * Build-time detection of the problem specifically for the
 * kernel, and RTP default FD table size.
 */

#if defined (INCLUDE_SELECT) && ! SELECT_FDSET_OVERSIZE_ALLOW
#if NUM_FILES > FD_SETSIZE
#error "NUM_FILES exceeds FD_SETSIZE with INCLUDE_SELECT enabled."
#endif /* NUM_FILES > FD_SETSIZE */
#if RTP_FD_NUM_MAX > FD_SETSIZE
#error "RTP_FD_NUM_MAX exceeds FD_SETSIZE with INCLUDE_SELECT enabled."
#endif /* RTP_FD_NUM_MAX > FD_SETSIZE */
#endif /* defined (INCLUDE_SELECT) && ! SELECT_FDSET_OVERSIZE_ALLOW */

/***************************************************************************
*
* usrFdSetFdBound - return upper limit on file descriptors from FD_SETSIZE
*
* This function returns an upper bound on the size of the file descriptor
* table for an RTP (or the kernel).
*
* When support for select() is included in the image, and the parameter
* SELECT_FDSET_OVERSIZE_ALLOW is FALSE (the default), this function returns
* FD_SETSIZE. This limits file descriptor values to be less than FD_SETSIZE,
* so that select() can be used with ordinary fd_set structures.
*
* Otherwise, if select() support is not included, or if the special parameter
* SELECT_FDSET_OVERSIZE_ALLOW is nonzero, then this function returns
* INT_MAX, effectively imposing no practical upper limit on the size of the file
* descriptor tables (and file descriptors).
*
* Note that when INCLUDE_SELECT is enabled and the parameter
* SELECT_FDSET_OVERSIZE_ALLOW is TRUE, file descriptor values are allowed to
* be FD_SETSIZE or larger, which means such file descriptors do not fit
* in a normally sized fd_set structure used with select().
*
* The VxWorks select() implementation allows oversized (pseudo)fd_set structures,
* with a <width> parameter larger than FD_SETSIZE; however, applications attempting
* to make use of this feature need to allocate and initialize their own extra-large
* fd_set bitmaps.
*
* This configuration is also somewhat dangerous because some VxWorks applications
* using select() might assume that the I/O system will never provide them with a file
* descriptor greater than or equal to FD_SETSIZE. Such applications might blindly
* set, clear, or test bits (corresponding to the file descriptors used) in
* normal fd_set structures without checking that the descriptors are less than
* FD_SETSIZE. Therefore, these applications could make erroneous accesses outside of the
* fd_set structure, possibly leading to data corruption or exceptions.
*
* RETURNS: FD_SETSIZE or INT_MAX, depending upon the VIP configuration
*/

size_t usrFdSetFdBound (void)
    {
#if defined (INCLUDE_SELECT) && ! SELECT_FDSET_OVERSIZE_ALLOW
    return (size_t)(FD_SETSIZE);
#else
    /*
     * If select() support is not included, or SELECT_FDSET_OVERSIZE_ALLOW
     * is enabled, return INT_MAX (which is effectively no limit).
     */

    return (size_t)(INT_MAX);
#endif /* defined (INCLUDE_SELECT) && ! SELECT_FDSET_OVERSIZE_ALLOW */
    }
