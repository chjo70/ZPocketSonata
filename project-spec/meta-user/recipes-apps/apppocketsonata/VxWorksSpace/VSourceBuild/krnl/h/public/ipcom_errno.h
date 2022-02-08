/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_ERRNO_H
#define IPCOM_ERRNO_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include "ipcom_cstyle.h"
#include "ipcom_perrno.h"

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
 *                   process specific 'errno' variable
 *===========================================================================
 */
#define ipcom_errno (*ipcom_errno_get())


/*
 *===========================================================================
 *                   default errnos.
 *===========================================================================
 */
#ifndef IP_ERRNO_ENOMEDIUM
#define IP_ERRNO_ENOMEDIUM      123     /* No medium found */
#endif
#ifndef IP_ERRNO_EMEDIUMTYPE
#define IP_ERRNO_EMEDIUMTYPE    124     /* Wrong medium type */
#endif
#ifndef IP_ERRNO_ENODATA
#define IP_ERRNO_ENODATA        200
#endif
#ifndef IP_ERRNO_ECOMM
#define IP_ERRNO_ECOMM          201
#endif


/*
 *===========================================================================
 *                   interpeak errno extensions
 *===========================================================================
 */

#define IP_ERRNO_EINTERNAL	        1000
#define IP_ERRNO_ENOSUPPORT         1001
#define IP_ERRNO_EINITFAILED        1002
#define IP_ERRNO_ECONFIG            1003
#define IP_ERRNO_ENOTOME            1004
#define IP_ERRNO_ENOTFOUND          1005
#define IP_ERRNO_EFIREWALL          1006
#define IP_ERRNO_ENAT               1007
#define IP_ERRNO_EIPSEC             1008
#define IP_ERRNO_EROHC              1009


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipcom_errno_get
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC int *
ipcom_errno_get(void);


/*
 *===========================================================================
 *                    ipcom_errno_set
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:      -1
 *
 */
IP_PUBLIC int
ipcom_errno_set(int errcode);


#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
