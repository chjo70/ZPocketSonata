/* ipnet_svlan.h - VLAN stacking head file */

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
01b,22apr10,tlu  Modify function prototyping
01a,23jun09,tlu  Created.
*/

#ifndef IPNET_SVLAN_H
#define IPNET_SVLAN_H

#ifdef IPNET_USE_VLAN_STACKING


/*
 ****************************************************************************
 *                     INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_tags.h>
#include <ipcom_type.h>
#include <ipcom_sock.h>
#include <ipcom_sock6.h>
#include <ipcom_list.h>
#include <ipcom_netif.h>
#include <ipcom_pkt.h>
#include <ipcom_inet.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 ****************************************************************************
 *                     DEFINES
 ****************************************************************************
 */

#define IPNET_VLAN_MAX_PWD_PORTS  10     /* Max forwarding ports for a VLAN */
#define IPNET_VLAN_MAX_VLANs      50     /* Max VLANs on a port */
#define IPNET_VLAN_DEFAULT_PVID   1      /* The default port VID */
#define IPNET_VLAN_MAC_EXPIRE     (5*60) /* The learned MAC expiring seconds */

#define IPCOM_PKT_FLAG_LINK_VLAN        IPCOM_PKT_FLAG_LINK3
                /* Indicate the pkt has been output by VLAN forwarding */


/*
 *===========================================================================
 *                         Service VLAN tag protocol ID
 *===========================================================================
 */
#define IPNET_VLAN_SVLAN_TPID_DEF       0x88a8



/*
 *===========================================================================
 *                         Ingress rules
 *===========================================================================
 */
typedef enum {
    IPNET_VLAN_INGRESS_ADMIT_ALL =  0,  /* Default: Admit all frames */
    IPNET_VLAN_INGRESS_ADMIT_TAG,       /* Admit only VLAN-tagged frames */
    IPNET_VLAN_INGRESS_ADMIT_OTHER      /* Admit only Untagged and
                                           Priority-tagged frames */
} Ipnet_vlan_ingress_type;

/*
 *===========================================================================
 *                         Egress rules
 *===========================================================================
 */
typedef enum {
    IPNET_VLAN_EGRESS_TAGGED =      0,      /* default */
    IPNET_VLAN_EGRESS_UNTAGGED
} Ipnet_vlan_egress_type;


/*
 *===========================================================================
 *                         MAC address types
 *===========================================================================
 */
typedef enum {
    IPNET_VLAN_ADDR_UNICAST =      1,
    IPNET_VLAN_ADDR_MULTICAST,
    IPNET_VLAN_ADDR_BROADCAST
} Ipnet_vlan_addr_type;


/*
 *===========================================================================
 *                         Ipnet_vlan_station_cache
 *===========================================================================
 *  VLAN MAC station structure
 */
typedef struct Ipnet_vlan_station_cache_struct
{
    Ip_time_t    last_used_time;
    Ip_u8        macAddr[6];            /* MAC address */
    Ipnet_netif *netif;                 /* station's rcv I/F */
    Ip_u16       svid;
}
Ipnet_vlan_station_cache;


/*
 *===========================================================================
 *                         Ipnet_vlan_fwd_port
 *===========================================================================
 *  VLAN forwarding port structure
 */
typedef struct Ipnet_vlan_fwd_port_struct
{
    Ipcom_list   next;
    Ipnet_netif *netif;
}
Ipnet_vlan_fwd_port;


/*
 *===========================================================================
 *                         Ipnet_vlan_scfwd
 *===========================================================================
 *  S-VLAN to C-VLAN forwarding port list structure
 */
typedef struct Ipnet_vlan_scfwd_struct
{
    Ip_u16       vid;                   /* C-VID */
    Ipcom_list  *port_list;
}
Ipnet_vlan_scfwd;


/*
 *===========================================================================
 *                         Ipnet_vlan_fwd
 *===========================================================================
 *  VLAN forwarding port list structure
 */
typedef struct Ipnet_vlan_fwd_struct
{
    Ip_u16       vid;                   /* VID: C-VID for C/CS-VLAN port */
                                        /*      S-VID for S/SC-VLAN port */
    Ip_u16       svid;                  /* S-VID for CS-VLAN */
    Ip_u8        pri_mapping[8];        /* priority mapping for CS-VLAN */
    union
    {
        Ipcom_list  *port_list;         /* port list */
        Ipcom_hash  *c_ports;           /* C-VLAN ports for SC-VLAN */
    } ports;
}
Ipnet_vlan_fwd;



/*
 ****************************************************************************
 *                      Functions
 ****************************************************************************
 */

IP_PUBLIC int ipnet_vlan_stacking_ioctl(unsigned long request,
                                        void *req,
                                        Ipnet_netif *netif);
IP_PUBLIC void ipnet_svlan_free_all(Ipnet_netif *netif);
IP_PUBLIC int ipnet_svlan_ingress_filter(Ipnet_netif *netif,
                                         Ip_u16 vid,
                                         Ip_u16 svid);
IP_PUBLIC Ip_bool ipnet_svlan_to_forward(Ipnet_netif *netif,
                                         Ipcom_pkt *pkt,
                                         int vid);
IP_PUBLIC int ipnet_svlan_output(Ipnet_netif *netif,
                                 Ipcom_pkt *pkt,
                                 int frame_type,
                                 int tag,
                                 int ctag,
                                 Ip_u8 vpri,
                                 Ip_u16 link_hdr_size);
IP_PUBLIC Ip_u16 ipnet_get_svlan_stpid(void);
IP_PUBLIC Ip_u16 ipnet_get_svlan_stpid_net(void);

#ifdef __cplusplus
}
#endif

#endif   /* IPNET_USE_VLAN_STACKING */

#endif   /* #ifndef IPNET_SVLAN_H */


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
