/* usrNullNvRam.c - null non-volatile RAM library */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,08may13,x_z  written based on src/drv/mem/nullNvRam.c.
*/

/*
DESCRIPTION
This library contains non-volatile RAM manipulation routines for targets lacking
non-volatile RAM.  Read and write routines that return ERROR are included.

The macro NV_RAM_SIZE should be defined as NONE for targets lacking non-volatile
RAM.
*/

/* includes */

#include <vxWorks.h>
#include <stdlib.h>

/*******************************************************************************
*
* sysNvRamGet - get the contents of non-volatile RAM
*
* This routine directly returns with ERROR status.
*
* RETURNS: ERROR always.
*
* ERRNO: N/A
*/

STATUS sysNvRamGet
    (
    char *  string,         /* where to copy non-volatile RAM    */
    int     strLen,         /* maximum number of bytes to copy   */
    int     offset          /* byte offset into non-volatile RAM */
    )
    {
    return (ERROR);
    }

/*******************************************************************************
*
* sysNvRamSet - write to non-volatile RAM
*
* This routine directly returns with ERROR status.
*
* RETURNS: ERROR always.
*
* ERRNO: N/A
*/

STATUS sysNvRamSet
    (
    char *  string,         /* string to be copied into non-volatile RAM */
    int     strLen,         /* maximum number of bytes to copy           */
    int     offset          /* byte offset into non-volatile RAM         */
    )
    {
    return (ERROR);
    }

#ifdef INCLUDE_SHOW_ROUTINES
/*******************************************************************************
*
* sysNvRamShow - show Flash driver information
*
* This routine prints the null NVRAM information.
*
* RETURNS: N/A
*/

void sysNvRamShow ()
    {
    printf ("NULL non-volatile RAM\n");
    }
#endif /* INCLUDE_SHOW_ROUTINES */

