/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------- 
10feb14,tlu  Ported to Vx-7
23aug13,tlu  Created.
*/

#ifndef IPCOM_EPOLL_H
#define IPCOM_EPOLL_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * The benefit of epoll vs. select is that the epoll is more efficient
 * in systems where the number of sockets one want to monitor is quite
 * large.
 *
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"


#ifdef _WRS_CONFIG_EPOLL
/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include "ipcom_type.h"
#include "ipcom_cstyle.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#define IPCOM_EPOLLIN       (1u << 0)   /* 0x001, Socket is readable */
#define IPCOM_EPOLLPRI      (1u << 1)   /* 0x002, Urgent data present */
#define IPCOM_EPOLLOUT      (1u << 2)   /* 0x004, Socket is writable */
#define IPCOM_EPOLLERR      (1u << 3)   /* 0x008, Pending error condition */
#define IPCOM_EPOLLHUP      (1u << 4)   /* 0x010, unused by IPNET */

#define IPCOM_EPOLLRDHUP    (1u << 13)  /* 0x2000, Peer closed its write end */

#define IPCOM_EPOLLONESHOT  (1u << 30)  /* Set one-shot behavior */
#define IPCOM_EPOLLET       (1u << 31)  /* Edge triggered poll */


/* The maximum number of the epoll instances that monitor a socket */
#define  IPCOM_EPOLL_MAX_INSTANCES        10

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

#ifdef _WRS_CONFIG_EOLL_IPNET_SOCK_USE_SIGNALS
IP_PUBLIC int ipcom_epoll_sig_handler(Ip_fd fd, 
                                      unsigned long request, 
                                      void *argp);
#endif


#ifdef __cplusplus
}
#endif

#endif /* _WRS_CONFIG_EPOLL */

#endif

/*
****************************************************************************
*                      END OF FILE
****************************************************************************
*/
