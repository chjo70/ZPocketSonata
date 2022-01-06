/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPNET_TUNNEL_H
#define IPNET_TUNNEL_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/* IP over IP tunnel network interface for IPNET */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipnet_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_type.h>
#include <ipcom_cstyle.h>
#include <ipcom_sock.h>

#include "ipnet_h.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */
#define IPNET_GET_TUNNEL_PARAM(netif) (&((Ipnet_tunnel_plink *)(netif->ipcom.plink))->tp)

#define IPNET_TUNNEL_OUTPUT_SANITY_CHECK(netif, pkt) \
    do { \
        if (pkt->start < netif->ipcom.link_hdr_size) \
        { \
            ipcom_pkt_free(pkt); \
            return -IP_ERRNO_EMSGSIZE; \
        } \
        if (IP_BIT_ISFALSE(netif->ipcom.flags, IP_IFF_UP)) \
        { \
            ipcom_pkt_free(pkt); \
            return -IP_ERRNO_EHOSTDOWN; \
        } \
        if (IP_BIT_ISFALSE(netif->ipcom.flags, IP_IFF_RUNNING)) \
       { \
           ipcom_pkt_free(pkt); \
           return 0; \
       } \
    } while ((0))


/*
 * Updates of all packet flags before inputing the packet into the
 * stack output again
 */
#define IPNET_TUNNEL_PKT_FLAGS_OUTPUT_UPDATE(pkt) \
    IP_BIT_CLR((pkt)->flags, \
                 IPCOM_PKT_FLAG_HAS_IP_HDR \
               | IPCOM_PKT_FLAG_MORE_FRAG \
               | IPCOM_PKT_FLAG_BROADCAST \
               | IPCOM_PKT_FLAG_TUNNELED \
               | IPCOM_PKT_FLAG_FORWARDED \
               | IPCOM_PKT_FLAG_MULTICAST \
               | IPCOM_PKT_FLAG_IPSEC_OUT \
               | IPCOM_PKT_FLAG_HW_CHECKSUM \
               | IPCOM_PKT_FLAG_NAT);


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

#ifdef IPNET_USE_GRE
#define IPNET_GRE_MAX_HDR_SIZE     16 /* GRE header, checksum, key and sequence number */
#endif


/*
   The format of the minimal forwarding header is as follows:

    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   Protocol    |S|  reserved   |        Header Checksum        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                 Original Destination Address                  |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   :            (if present) Original Source Address               :
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

#include "ipcom_align16.h"
typedef IP_PACKED1 struct Ipnet_pkt_min_encap_struct
{
    Ip_u8  proto;
    Ip_u8  flags;
    Ip_u16 chksum;
    Ip_u16 original_dst_addr[2];
    Ip_u16 original_src_addr[2];
}
IP_PACKED2 Ipnet_pkt_min_encap;
#include "ipcom_align16.h"

/* Length of header when S flag is cleared */
#define IPNET_TUNNEL_MIN_ENCAP_S0_LEN  8
/* Length of header when S flag is set */
#define IPNET_TUNNEL_MIN_ENCAP_S1_LEN  12


/* Tunnel link information */
typedef struct Ipnet_tunnel_plink_struct
{
    struct Ip_ip_tunnel_param tp;
    Ipnet_ppp_peer            peer;
}
Ipnet_tunnel_plink;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

IP_GLOBAL Ip_u16 ipnet_tunnel_type(struct Ipnet_netif_struct   *netif);
IP_GLOBAL Ip_u16 ipnet_tunnel_get_basetype(Ip_u16 vr, char *name, Ip_size_t *sz);
IP_GLOBAL char *ipnet_tunnel_get_basename(Ip_u16 vr, Ip_u16 basetype, char *name);

IP_GLOBAL Ip_u16 ipnet_tunnel_get_type(char *name);
IP_GLOBAL int ipnet_tunnel_create_bsd(struct Ipnet_socket_struct *sock, struct Ip_ifreq *ifreq);
IP_GLOBAL int ipnet_tunnel_create_linux(struct Ipnet_socket_struct *sock, struct Ip_ifreq *ifreq);
IP_GLOBAL int ipnet_tunnel_add(struct Ipnet_socket_struct *sock, const char *name, Ip_u16 type, struct Ipnet_netif_struct **netifp);
IP_GLOBAL int ipnet_tunnel_setup(struct Ipnet_netif_struct *netif, Ip_u16 tunnel_type);
IP_GLOBAL void ipnet_tunnel_ip4_rfc3519_rx(Ipnet_dst_cache *dst, Ipcom_pkt *pkt);
IP_GLOBAL int ipnet_tunnel_dsmipv6_input(Ipnet_dst_cache *dst, Ipcom_pkt *pkt);
IP_GLOBAL void ipnet_tunnel_init(void);

IP_PUBLIC int ipnet_tunnel_if_init(struct Ipnet_netif_struct *netif);


/*
 *===========================================================================
 *                         GRE FUNCTIONS
 *===========================================================================
 *
 */

#ifdef IPNET_USE_GRE
IP_GLOBAL int ipnet_gre_setup(Ipnet_netif *netif);
IP_GLOBAL void ipnet_gre_destroy(Ipnet_netif *netif);
IP_GLOBAL int ipnet_gre_input(Ipnet_netif *netif, Ipcom_pkt *pkt);
IP_GLOBAL int ipnet_gre_output_append(Ipnet_netif *netif, struct Ip_ip_tunnel_param *tunnel_param, Ipcom_pkt *pkt);
#endif

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
