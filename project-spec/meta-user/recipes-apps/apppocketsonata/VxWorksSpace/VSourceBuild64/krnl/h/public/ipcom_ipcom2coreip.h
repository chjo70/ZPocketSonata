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
 * Make ipcom socket calls go through the socket library when IPLITE/IPNET
 * is included. This is used to test the socket backend using the socktest
 * shell command.
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

#include <ipcom_pconfig.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#ifdef IPCOM_VXWORKS_TEST_SOCKET_BACKEND
/* Direct all ipcom socket calls to the socketlib via ipcom_psock.c */
#define ipcom_accept       ipcom_socklib_accept
#define ipcom_bind         ipcom_socklib_bind
#define ipcom_connect      ipcom_socklib_connect
#define ipcom_getpeername  ipcom_socklib_getpeername
#define ipcom_getsockname  ipcom_socklib_getsockname
#define ipcom_getsockopt   ipcom_socklib_getsockopt
#define ipcom_listen       ipcom_socklib_listen
#define ipcom_recv         ipcom_socklib_recv
#define ipcom_recvfrom     ipcom_socklib_recvfrom
#define ipcom_recvmsg      ipcom_socklib_recvmsg
#define ipcom_send         ipcom_socklib_send
#define ipcom_sendto       ipcom_socklib_sendto
#define ipcom_sendmsg      ipcom_socklib_sendmsg
#define ipcom_setsockopt   ipcom_socklib_setsockopt
#define ipcom_shutdown     ipcom_socklib_shutdown
#define ipcom_socket       ipcom_socklib_socket
#define ipcom_socketclose  ipcom_socklib_close
#define ipcom_socketioctl  ipcom_socklib_ioctl
#define ipcom_socketread   ipcom_socklib_read
#define ipcom_socketselect ipcom_socklib_select
#define ipcom_socketwrite  ipcom_socklib_write
#endif

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */


#ifdef __cplusplus
}
#endif


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
