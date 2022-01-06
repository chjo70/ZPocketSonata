/* ipnet_svlan_netlink.h - VLAN stacking netlink head file */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01a,29jan10,tlu  Created.
*/

#ifndef IPNET_SVLAN_NETLINK_H
#define IPNET_SVLAN_NETLINK_H

#ifdef IPCOM_USE_FORWARDER_VLAN_STACKING


/*
 ****************************************************************************
 *                     INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_type.h>
#include <ipcom_netlink.h>

#include "ipnet_eth.h"
#include "ipnet_svlan.h"


#ifdef __cplusplus
extern "C" {
#endif


/*
 ****************************************************************************
 *                     DEFINES
 ****************************************************************************
 */
#define IFNAMESIZE 	     16


/*
 *===========================================================================
 *                         VLAN stacking netlink cmd types
 *===========================================================================
 */
typedef enum {
    VLAN_SET_STPID =         1,   /* Set service VLAN TPID */
    VLAN_SET_SVLAN,               /* Set VLAN stacking on an eth interface */
    VLAN_SET_PVID,                /* Set PVID */
    VLAN_SET_PRI_MAP,             /* Set VLAN priority map */
    VLAN_SET_INGRESS,             /* Set VLAN ingress rule */
    VLAN_SET_EGRESS,              /* Set VLAN egress rule */
    __IP_SVLAN_MAX
} Ipnet_vlan_cmd_type;

#define IP_SVLAN_MAX (__IP_SVLAN_MAX - 1)


/*
 *===========================================================================
 *                    vlanreq - VLAN stacking netlink config structure
 *===========================================================================
 * VLAN stacking netlink config structure.
 */
typedef struct Ip_vlannetreq_struct
{
    unsigned char        family;
    Ip_u32		 ifindex;
    Ipnet_vlan_cmd_type  cmd;     /* VLAN stacking configuration cmd */
    Ipnet_vlan_type      type;    /* VLAN stacking port type */
    unsigned short int   tag;     /* 12-bit C-VID, 1..4094, 0 for undefined */
    unsigned short int   stag;    /* 12-bit S-VID, 1..4094, 0 for undefined */
    Ipnet_vlan_ingress_type   inrule;  /* VLAN ingress rule */
    Ipnet_vlan_egress_type    outrule; /* VLAN egress rule */
    unsigned char        pri;     /* 3-bit rcv VLAN priority, 0..7 */
    unsigned char        spri;    /* 3-bit service pri mapped from rcv pri */
    unsigned short int   stpid;   /* 16 bit service TPID */
}
Ip_vlannetreq;


/*
 *===========================================================================
 *                    Ip_vlannetlink - netlink msg
 *===========================================================================
 * Configuration structure for VLAN netlink.
 */
typedef struct Ip_vlannetlink_struct
{
    struct Ip_nlmsghdr  nlh;
    Ip_vlannetreq       vlan_conf;
}
Ip_vlannetlink;


/*
 ****************************************************************************
 *                      Functions 
 ****************************************************************************
 */

IP_GLOBAL void ipnet_svlan_rtnetlink_init(void);


#ifdef __cplusplus
}
#endif

#endif   /* IPCOM_USE_FORWARDER_VLAN_STACKING */

#endif   /* #ifndef IPNET_SVLAN_NETLINK_H */


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
