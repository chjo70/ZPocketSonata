/* usrPosixAdvLock.c - POSIX advisory file locking */

/*
 * Copyright 2006, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,14jan14,ghs  Clean up header file reference
01d,01jan14,ghs  Modify lock function type (US29308)
01c,11jul06,pcm  removed redundant code
01b,09may06,pcm  made _func_lf_advlock extern; see funcBind.c
01a,12Jan06,act  written.
*/

/*
DESCRIPTION
*/

/* includes */

#include <vxWorks.h>

/* defines */

/* typedefs */

/* globals */

/* pointer to vnode operator tables used by HRFS */

extern int lf_advlock (void *, void *, int, void *,
                       int64_t, int);

extern int (*_func_lf_advlock) (void *, void *, int, void *,
                                int64_t, int);

/* externs */

/***************************************************************************
*
* usrPosixAdvLockInit -
*/

STATUS usrPosixAdvLockInit
    (
    void
    )
    {
    _func_lf_advlock = (int (*) (void *, void *, int, void *, int64_t, int)) 
                       lf_advlock;

    return (OK);
    }
