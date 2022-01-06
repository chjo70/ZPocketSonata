/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_PSOCK_H
#define IPCOM_PSOCK_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * VxWorks WindNet TCP/IP stack defines.
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

#if IPCOM_USE_SOCK != IPCOM_SOCK_NATIVE
#error ipcom_psock_h_only_used_with_native_stack
#endif

#include "ipcom_type.h"

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
 *                         setsockopt
 *===========================================================================
 */

/* Standard option flags per-socket.  */
#define IP_SO_DEBUG        0x0001          /* Turn on debugging info recording. */
#undef IP_SO_KEEPALIVE
#define IP_SO_KEEPALIVE    0x0008          /* Keep TCP connections alive. */


/*
 *===========================================================================
 *                         select
 *===========================================================================
 */
#undef IP_FD_SETSIZE
#define IP_FD_SETSIZE     256              /* Default value for vxWorks */


#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

