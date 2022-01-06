/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Reverts the IPCOM API back to standard IPCOM functions again.
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


#ifdef IPCOM_IPCOM2BSD

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* Remove all defines done by ipcom_ipcom2bsd.h */
#undef IPCOM_FD_CLR
#undef IP_FD_ISSET
#undef IP_FD_SET
#undef IP_FD_ZERO

#undef bzero

#undef Ip_cmsghdr
#undef Ip_fd_set
#undef Ip_iovec
#undef Ip_msghdr
#undef Ip_sockaddr
#undef Ip_sockaddr_in
#undef Ip_sockaddr_in6
#undef Ip_socklen_t
#undef Ip_timeval

#undef ipcom_accept
#undef ipcom_bind
#undef ipcom_connect
#undef ipcom_getpeername
#undef ipcom_getsockname
#undef ipcom_getsockopt
#undef ipcom_listen
#undef ipcom_recv
#undef ipcom_recvfrom
#undef ipcom_recvmsg
#undef ipcom_send
#undef ipcom_sendmsg
#undef ipcom_sendto
#undef ipcom_setsockopt
#undef ipcom_shutdown
#undef ipcom_socket
#undef ipcom_socketclose
#undef ipcom_socketioctl
#undef ipcom_socketread
#undef ipcom_socketselect
#undef ipcom_socketwrite


#undef IP_FD_SET_TYPE
#undef IPCOM_IPCOM2BSD


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */


#ifdef __cplusplus
}
#endif

#endif /* IPCOM_IPCOM2BSD */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
