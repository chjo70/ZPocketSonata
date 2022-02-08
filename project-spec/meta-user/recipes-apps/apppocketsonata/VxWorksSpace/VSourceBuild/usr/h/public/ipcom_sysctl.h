/* ipcom_sysctl.h - IPCOM sysctl library */

/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_SYSCTL_H
#define IPCOM_SYSCTL_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
DESCRIPTION
Public API for ipcom sysctl library.
INCLUDE FILES: ipcom_type.h, ipcom_sock.h
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

#include <ipcom_type.h>
#include <ipcom_cstyle.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
    1:st level
        2:nd level
            3:rd level
                4:th level
                    5:th level
                        6:th level
    IP_CTL_NET
        IP_AF_ROUTE
            0
                0 | IP_AF_INET | IP_AF_INET6 (which af to return, 0=all)
                    IP_NET_RT_DUMP
                        0   (dump all route table entries)
                    IP_NET_RT_FLAGS
                        IPNET_RTF_xxx (dump route entries that has this flag set)
                    IP_NET_RT_IFLIST
                        0       (dump address information for all interfaces)
                        netif   (dump address information for this interface)
        IP_AF_INET
            IP_IPPROTO_IP
                IP_IPCTL_FORWARDING      (forward IPv4 packets between interfaces)
                IP_IPCTL_SENDREDIRECTS   (enable/disable sending of ICMP redirect)
                IP_IPCTL_MTUDISC         (enable/disable path MTU discovery)
            IP_IPPROTO_UDP
                IP_UDPCTL_CHECKSUM       (enable/disable UDP checksum when sending)
        IP_AF_INET6
            IP_IPPROTO_IPV6
                IP_IPV6CTL_FORWARDING    (forward IPv6 packets between interfaces)
                IP_IPV6CTL_ACCEPT_RTADV  (enable/disable router advertisment processing)
                    netif
                IP_IPV6CTL_ENABLED       (enable/disable IPv6 processing on interface)
                    netif
                IP_IPV6CTL_ND_CURHOPLIMIT (hop-limit as specified by on-link router(s))
                    netif
*/

#define IP_CTL_MAXNAME   6   /* Max name length */

#if defined(IP_PORT_VXWORKS) && IP_PORT_VXWORKS >= 65
#define IP_CTL_NET   4   /* Networking */
#else
#define IP_CTL_NET   3   /* Networking */
#endif


/* Networking */
#define IP_NET_RT_DUMP    1   /* Dump all route entries */
#define IP_NET_RT_FLAGS   2   /* Dump all route entries with a specific flag set */
#define IP_NET_RT_IFLIST  3   /* Dump interface address information */
#define IP_NET_RT_MAXID   4

/* IPv4 */
#define IP_IPCTL_FORWARDING      1   /* IPv4 packet forwardning on/off */
#define IP_IPCTL_SENDREDIRECTS   2   /* Send ICMP redirect if in- and out interface is the same */
#define IP_IPCTL_STAT            3   /* IP protocol statistics show or clear*/
#define IP_IPCTL_MTUDISC         9   /* Enable/disable path MTU discovery */

/* IPv6 */
#define IP_IPV6CTL_FORWARDING    1   /* IPv6 packet forwardning on/off */
#define IP_IPV6CTL_ACCEPT_RTADV  2   /* IPv6 router advertisment processing on/off */
#define IP_IPV6CTL_MIP6          3   /* MIP6 sysctl */
#define IP_IPV6CTL_ENABLED       4   /* IPv6 processing enabled/disabled */
#define IP_IPV6CTL_ND_CURHOPLIMIT 5  /* hop-limit from router advertisement */

/* UDP */
#define IP_UDPCTL_CHECKSUM       1   /* Calculate checksum on outgoing UDP packets */


/*
 *===========================================================================
 *            User library support
 *===========================================================================
 */
#if (!defined(IPCOM_KERNEL) && defined(IPCOM_USRLIB)) || defined(IPCOM_USE_REMOTE_STACK)
#define ipcom_sysctl   ipcom_sysctl_usr
#endif


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
/*******************************************************************************
* 
* ipcom_sysctl - This routine is used to set or get kernel parameters at runtime. 
*
* DESCRIPTION
* Set or get kernel parameters at runtime. The parameters available are described in the 'name' parameter.
*
* Parameters:
* \is
* \i <name>
* This parameter is an array which defines the operation of sysctl function.
*    1:st level
*        2:nd level
*            3:rd level
*                4:th level
*                    5:th level
*                        6:th level
*    IP_CTL_NET
*        IP_AF_ROUTE
*            0
*                0 | IP_AF_INET | IP_AF_INET6 (which af to return, 0=all)
*                    IP_NET_RT_DUMP
*                        0   (dump all route table entries)
*                    IP_NET_RT_FLAGS
*                        IPNET_RTF_xxx (dump route entries that has this flag set)
*                    IP_NET_RT_IFLIST
*                        0           (dump address information for all interfaces)
*                        netif  index (dump address information for this interface)
*        IP_AF_INET
*            IP_IPPROTO_IP
*                IP_IPCTL_FORWARDING      (forward IPv4 packets between interfaces)
*                IP_IPCTL_SENDREDIRECTS   (enable/disable sending of ICMP redirect)
*                IP_IPCTL_MTUDISC         (enable/disable path MTU discovery)
*            IP_IPPROTO_UDP
*                IP_UDPCTL_CHECKSUM       (enable/disable UDP checksum when sending)
*        IP_AF_INET6
*            IP_IPPROTO_IPV6
*                IP_IPV6CTL_FORWARDING    (Enable forward IPv6 packets globally,'namelen' = 4)
*                    netif index             (Enable IPv6 packets forwarding on this interface)
*                IP_IPV6CTL_ACCEPT_RTADV  (Enable/disable router advertisment processing, 'namelen' = 4 for all the interfaces)
*                    netif index             (Specially for this interface if index defined)
*                IP_IPV6CTL_ENABLED        (Enable/disable IPv6 processing on interface,'namelen' = 4 for all the interfaces)
*                    netif index             (Specially for this interface if index defined)
*                IP_IPV6CTL_ND_CURHOPLIMIT (Set hop-limit as specified by on-link router(s),'namelen' = 4 for all the interfaces. This setting will be reset when interface down/up.)
*                    netif index             (Specially for this interface if index defined)
* \i <namelen>
* The array length of name parameter. e.g. 6 for name[6].
* \i <oldp>
* The buffer which is used to store the information of  kernel parameters for 'get' operation.
* \i <oldlenp>
* The buffer length for oldp.
* \i <newp>
* The buffer which stores the new value for kernel parameters for 'set' operation.
* \i <newlen>
* The buffer length for newp.
* \ie
* EXAMPLE
* Setting hoplimit for all interfaces:
*    int hoplimit = 32;
*    name[0] = IP_CTL_NET;
*    name[1] = IP_AF_INET6;
*    name[2] = IP_IPPROTO_IPV6;
*    name[3] = IP_IPV6CTL_ND_CURHOPLIMIT;
*
*    ipcom_sysctl(name, 4, NULL, NULL, &hoplimit, sizeof(hoplimit));
*
* Setting hoplimit for a specific interface (index = 1):
*    int hoplimit = 32;
*    name[0] = IP_CTL_NET;
*    name[1] = IP_AF_INET6;
*    name[2] = IP_IPPROTO_IPV6;
*    name[3] = IP_IPV6CTL_ND_CURHOPLIMIT;
*    name[4] = 1;
*
*    ipcom_sysctl(name, 5, NULL, NULL, &hoplimit, sizeof(hoplimit));
*
* RETURNS:
* 0 for success or -1 for failure.
*
* ERRNO: 
*/
IP_PUBLIC int ipcom_sysctl
(
    int *name, 
    unsigned int namelen,
    void *oldp, 
    Ip_size_t *oldlenp,
    void *newp, 
    Ip_size_t newlen
    );


#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
