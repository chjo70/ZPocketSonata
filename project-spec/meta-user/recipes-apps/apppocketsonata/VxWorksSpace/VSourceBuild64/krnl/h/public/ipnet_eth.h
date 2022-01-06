/*
 * Copyright (c) 2006-2013,2014,2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
/*
modification history
--------------------
20Oct16,xxy  Add TSN/QBV layer2 support. (F6820)
*/
#ifndef IPNET_ETH_H
#define IPNET_ETH_H

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

#include "ipnet_config.h"

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_hash.h>
#include "ipnet_h.h"
#include "ipnet_neigh.h"
#include "ipnet_timeout.h"

#ifdef IPNET_USE_VLAN_STACKING
#include "ipnet_svlan.h"
#endif /* IPNET_USE_VLAN_STACKING */

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */
#if defined(IPNET_USE_VLAN) || defined(IPNET_USE_VLAN_STACKING)
#define IPNET_VLAN_TAG_SIZE  4u  /* The length of the vlan tag */
#endif /* IPNET_USE_VLAN || IPNET_USE_VLAN_STACKING */


/*
 *===========================================================================
 *                         Frame Values
 *===========================================================================
 * Note: Also used for 3:rd argument to when creating packet sockets.
 */
#define IPNET_ETH_P_ALL            0
#define IPNET_ETH_P_IP             0x0800
#define IPNET_ETH_P_ARP            0x0806
#define IPNET_ETH_P_RARP           0x8035
#define IPNET_ETH_P_IPV6           0x86DD
#define IPNET_ETH_P_PPPOE_DIS      0x8863
#define IPNET_ETH_P_PPPOE_SES      0x8864
#define IPNET_ETH_P_8021Q_VLAN     0x8100
#define IPNET_ETH_P_8021Q_SVLAN    0x88a8   /* default S-VLAN TPID */
#define IPNET_ETH_P_MACSEC         0x88E5
#define IPNET_ETH_P_EAPOL          0x888e
#define IPNET_ETH_P_SLOW	       0x8809		/* LACP */
/* IEEE 802a OUI Extended Ethertype for TSN */
#define IPNET_ETH_P_802A_OUI_QAV   0x88b7


/* Ethernet types: */
#define IPNET_ETHFRAME_IP              ip_htons(IPNET_ETH_P_IP)
#define IPNET_ETHFRAME_IPV6            ip_htons(IPNET_ETH_P_IPV6)
#define IPNET_ETHFRAME_ARP             ip_htons(IPNET_ETH_P_ARP)
#define IPNET_ETHFRAME_RARP            ip_htons(IPNET_ETH_P_RARP)
#define IPNET_ETHFRAME_PPPOE_DIS       ip_htons(IPNET_ETH_P_PPPOE_DIS)
#define IPNET_ETHFRAME_PPPOE_SES       ip_htons(IPNET_ETH_P_PPPOE_SES)
#define IPNET_ETHFRAME_8021Q_VLAN      ip_htons(IPNET_ETH_P_8021Q_VLAN)
#define IPNET_ETHFRAME_8021Q_SVLAN     ip_htons(IPNET_ETH_P_8021Q_SVLAN)
#define IPNET_ETHFRAME_MACSEC          ip_htons(IPNET_ETH_P_MACSEC)
#define IPNET_ETHFRAME_EAPOL           ip_htons(IPNET_ETH_P_EAPOL)
#define IPNET_ETHFRAME_SLOW            ip_htons(IPNET_ETH_P_SLOW)

/* Add IEEE 802a OUI Extended Ethertype for TSN */
#define IPNET_ETHFRAME_802A_OUI_QAV   ip_htons(IPNET_ETH_P_802A_OUI_QAV)


/* Ethernet MTU/MRU. */
#define IPNET_ETH_MTU          1500

/* Size of Ethernet address */
#define IPNET_ETH_ADDR_SIZE    6

/* Size of Ethernet link header. */
#define IPNET_ETH_HDR_SIZE     14

/* Size of Ethernet link trailer (not used by IP layers) */
#define IPNET_ETH_TRL_SIZE     6

/* Number of bits in the host part (EUI-64) when using the
   ethernet MAC to create a IPv6 address (RFC 2464) */
#define IPNET_ETH_IP6_ID_BITS  64

/*
 * ISO PDTR 10178 contains among others
 */
#define IPNET_LLC_SNAP_LSAP	0xaa

/*
 * Returns if the specified MAC address is multicast or not
 */
#define IPNET_IS_ETHADDR_MCAST(mac) (0x01 & mac[0])

#define IPNET_SET_ETHTYPE(eth, eth_type) (eth)->d.type = eth_type

/* ARP pkt header values: */
#define IPNET_ARP_HRD_ETHER   ip_htons(0x0001)
#define IPNET_ARP_PRO_IP      IPNET_ETHFRAME_IP
#define IPNET_ARP_HLN_PLN     ip_htons(0x0604)

#define IPNET_ARP_OP_REQUEST  ip_htons(0x0001)
#define IPNET_ARP_OP_REPLY    ip_htons(0x0002)
#define IPNET_RARP_OP_REQUEST ip_htons(0x0003)
#define IPNET_RARP_OP_REPLY   ip_htons(0x0004)

/*
 * DEPRECATED, do not use.
 * Macros for set and get the VLAN tag associate with a packet
 */
#define IPNET_ETH_PKT_SET_VLAN_TAG(pkt, tag) \
    ipnet_vlan_set_tag(pkt, tag)

#define IPNET_ETH_PKT_GET_VLAN_TAG(pkt) \
    ipnet_vlan_get_tag(pkt)

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

IP_EXTERN const Ip_u8 *ipnet_eth_addr_broadcast;


/* Forward declarations */
struct Ipnet_route_entry_struct;
struct Ipnet_netif_struct;


/*
 *===========================================================================
 *                         Ipnet_pkt_eth
 *===========================================================================
 */

#include "ipcom_align16.h"

typedef IP_PACKED1 struct Ipnet_eth_addr_6u8_struct
{
    Ip_u16 u8[6];
}
IP_PACKED2 Ipnet_eth_addr_6u8;

    typedef IP_PACKED1 struct Ipnet_eth_addr_3u16_struct
{
    Ip_u16 u16[3];
}
IP_PACKED2 Ipnet_eth_addr_3u16;

typedef IP_PACKED1 struct Ipnet_eth_addr_u32u16_struct
{
    Ip_u32 u32;
    Ip_u16 u16;
}
IP_PACKED2 Ipnet_eth_addr_u32u16;

typedef IP_PACKED1 struct Ipnet_eth_addr_u16u32_struct
{
    Ip_u16 u16;
    Ip_u32 u32;
}
IP_PACKED2 Ipnet_eth_addr_u16u32;

typedef IP_PACKED1 union Ipnet_eth_addr_union
{
    Ipnet_eth_addr_6u8    u8;
    Ipnet_eth_addr_3u16   u16;
    Ipnet_eth_addr_u32u16 u32_16;
    Ipnet_eth_addr_u16u32 u16_32;

} IP_PACKED2 Ipnet_eth_addr_u;

IP_INLINE void
IPNET_SET_ETHADDR(void *dst, const void *src)
{
    Ipnet_eth_addr_u *d = (Ipnet_eth_addr_u *)dst;
    const Ipnet_eth_addr_u *s = (Ipnet_eth_addr_u *)src;
#ifdef IPCOM_32ON16_OK
    d->u32_16.u32 = s->u32_16.u32;
    d->u32_16.u16 = s->u32_16.u16;
#else
    d->u16.u16[0] = s->u16.u16[0];
    d->u16.u16[1] = s->u16.u16[1];
    d->u16.u16[2] = s->u16.u16[2];
#endif
}

IP_INLINE void
IPNET_CLR_ETHADDR(void * dst)
{
    Ipnet_eth_addr_u *d = (Ipnet_eth_addr_u *)dst;
#ifdef IPCOM_32ON16_OK
    d->u32_16.u32 = 0;
    d->u32_16.u16 = 0;
#else
    d->u16.u16[0] = 0;
    d->u16.u16[1] = 0;
    d->u16.u16[2] = 0;
#endif
}

IP_INLINE void
IPNET_SET_ETHADDR_BROADCAST(void *dst)
{
    Ipnet_eth_addr_u *d = (Ipnet_eth_addr_u *)dst;
    d->u16.u16[0] = 0xffff;
    d->u16.u16[1] = 0xffff;
    d->u16.u16[2] = 0xffff;
}

IP_INLINE Ip_bool
IPNET_ARE_ETHADDR_EQUAL(const void *addr1, const void *addr2)
{
    const Ipnet_eth_addr_u *e1 = (Ipnet_eth_addr_u *)addr1;
    const Ipnet_eth_addr_u *e2 = (Ipnet_eth_addr_u *)addr2;
    return (e1->u16.u16[0] == e2->u16.u16[0] &&
            e1->u16.u16[1] == e2->u16.u16[1] &&
            e1->u16.u16[2] == e2->u16.u16[2]);
}

#if defined(IPNET_USE_VLAN) || defined(IPNET_USE_VLAN_STACKING)
typedef IP_PACKED1 struct Ipnet_pkt_eth_vlan_struct
{
    Ip_u16   tag_type;                    /* Must be IPNET_ETHFRAME_8021Q_VLAN */
    Ip_u16   pri_cif_vid;                 /* 3 bits priority,
                                             1 bit canonical format indicator for C-VLAN,
                                              or 1 bit drop eligible indicator for S-VLAN,
                                             12 bits VLAN identifier */
    Ip_u16   type;                        /* Ethernet frame type */
}
IP_PACKED2 Ipnet_pkt_eth_vlan;

#define IPNET_ETH_VLAN_GET_VID(pri_cif_vid)      (Ip_u16)(ip_ntohs(pri_cif_vid) & 0x0fff)
#define IPNET_ETH_VLAN_GET_VPRI(pri_cif_vid)     (Ip_u8)((ip_ntohs(pri_cif_vid) & 0xe000) >> 13)
#define IPNET_ETH_VLAN_GET_VCFI(pri_cif_vid)     (Ip_u8)((ip_ntohs(pri_cif_vid) & 0x1000) >> 12)
#define IPNET_ETH_VLAN_SET_VID(pri_cif_vid, vid) ((pri_cif_vid) = (pri_cif_vid) & ip_htons(0x0fff) | ip_htons(vid))
#endif /* IPNET_USE_VLAN || IPNET_USE_VLAN_STACKING */


typedef IP_PACKED1 struct Ipnet_pkt_eth_struct
{
    Ip_u8    dst[IPNET_ETH_ADDR_SIZE];    /* Destination address of the frame */
    Ip_u8    src[IPNET_ETH_ADDR_SIZE];    /* Source address of the fram */
    union {
        Ip_u16             type;
#if defined(IPNET_USE_VLAN) || defined(IPNET_USE_VLAN_STACKING)
        Ipnet_pkt_eth_vlan vlan;
#endif
    } d;
}
IP_PACKED2 Ipnet_pkt_eth;


/*
 *===========================================================================
 *                         Ipnet_pkt_arp
 *===========================================================================
 */
typedef IP_PACKED1 struct Ipnet_pkt_arp_struct
{
    /* ARP header, names taken from RFC 826 */
    Ip_u16    hrd;    /* Hardware address space (e.g. Ethernet,
                         Packet Radio Net.) */
    Ip_u16    pro;    /* Protocol address space. For Ethernet
                         hardware, this is from the set of Ethernet
                         types */
    Ip_u8     hln;    /* Hardware address length, 6 for Ethernet */
    Ip_u8     pln;    /* Protocol address length, 4 for IPv4 */
    Ip_u16    op;     /* Opcodes, IPNET_ARP_OP_REQUEST or
                         IPNET_ARP_OP_REPLY */

    Ip_u8     eth_src[IPNET_ETH_ADDR_SIZE];
    Ip_u8     ip_src[4];

    Ip_u8     eth_dst[IPNET_ETH_ADDR_SIZE];
    Ip_u8     ip_dst[4];
}
IP_PACKED2 Ipnet_pkt_arp;
#include "ipcom_align16.h"



#if defined(IPNET_USE_VLAN) || defined (IPNET_USE_VLAN_STACKING)

/*
 *===========================================================================
 *                         Port VLAN types
 *===========================================================================
 */
typedef enum {
    IPNET_VLAN_NOT_DEFINED =      0,  /* VLAN type not defined */
    IPNET_VLAN_CS_VLAN,               /* customer edge/network port on provider edge */
    IPNET_VLAN_SC_VLAN,               /* provider network port on provider edge */
    IPNET_VLAN_S_VLAN,                /* provider network port on S-VLAN node */
    IPNET_VLAN_C_VLAN,                /* customer VLAN */
    IPNET_VLAN_8021_Q				  /* 802.1Q VLAN */
} Ipnet_vlan_type;

/*
 *===========================================================================
 *                         Ipnet_netif_eth_vlan
 *===========================================================================
 */
typedef struct Ipnet_netif_eth_vlan_struct
{
    Ip_bool                    tag_required; /* tagged egress frames */
    int                        id;     /* Virtual LAN ID 1-4095 */
				       /* VID on a subnet-based VLAN pseudo IF */
				       /* PVID on a VLAN stacking eth IF */
    Ip_u16                     pri;    /* 3 bit vlan priority, 0-7 */


#if defined(IPNET_USE_VLAN_STACKING) || defined(INCLUDE_IPBRIDGE_VLAN_SUPPORT)
    Ipnet_vlan_type	       vlan_type;  /* VLAN type */

    /*
     * Port VLAN membership - a bit map structure to represent all possible
     * VIDs on the port. The first 32-bits specifies VID 0 through 31, the
     * second 32-bits specifying VID 32 through 63, etc.  Within each 32-bit,
     * the most significant bit represents the highest numbered VID.
     * Thus, each VID is represented by a single bit. If that bit has a
     * value of 1, then this port is the member for that VID;
     * the port is not a member its bit has a value of 0.
     */
    Ip_u32		       vids[128];

    Ipnet_vlan_ingress_type    ingress_rule; /* VLAN ingress rule */
					   /* Admit-all/Admit-tag/Admit-other */
    Ipnet_vlan_egress_type     egress_rule;  /* VLAN egress rule */
					     /* tagged/untagged */
#endif
#ifdef INCLUDE_IPBRIDGE_VLAN_SUPPORT
    Ip_bool		ingress_vlan_check;	/* If set, only allow frames with a VID == id, otherwise allow all */
    Ip_u8		*egress_rules;  /* Pointer to VLAN egress tag rule bitmap per VID */
#endif
#ifdef IPNET_USE_VLAN_STACKING
    /*
     * VLAN forwarding mapping:
     *  For a customer edge/network port, mapping an incoming C-VID and
     *    priority to an outgoing S-VID, priority, and ports.
     *  For a provider network port on a provider edge node, mapping an
     *    incoming S-VID and C-VID to an outgoing C-VID and ports.
     *  For a provider network port on an S-VLAN node, mapping an incoming
     *    S-VID to outgoing ports with same S-VID.
     */
    Ipcom_hash                *vlan_fwd;   /* VLAN forwarding mapping */
#endif

    int                        promisc_count;
}
Ipnet_netif_eth_vlan;
#endif


/*
 *===========================================================================
 *                         Ipnet_netif_eth
 *===========================================================================
 * Ethernet specific data
 */
typedef struct Ipnet_netif_eth_struct
{
#if defined(IPNET_USE_VLAN) || defined (IPNET_USE_VLAN_STACKING)
    union
    {
        Ipcom_hash           *ifs;     /* All virtual interfaces that has this interface as parent */
        struct Ipnet_netif_struct *parent;   /* Parent Ethernet interface */
    } vlan;
    Ipnet_netif_eth_vlan     vlan_param;  /* Virtual LAN parameters */
#endif
#ifdef IPNET_USE_BOND
    union
    {
        void                      *priv;     /* Bonding private data */
        struct Ipnet_netif_struct *master;   /* Master Bonding interface */
    } bond;
#endif
#ifdef IPPPP_USE_PPPOE
    int            pppoe_num_sessions;  /* Used by ethX */
    void          *pppoe_tmo_handle;    /* Used by ethX  (tmo_handle or pppif) */
    Ip_u32         pppoe_ppp_ifindex;   /* Interface index. */
#endif
#ifdef IPNET_USE_RARP
    Ip_u32         rarp_interval;   /* RARP interval, 2,4,8, etc. */
    Ipnet_timeout *rarp_tmo;
#endif
#if !(defined(IPNET_USE_RARP) || defined(IPNET_USE_VLAN) \
   || defined(IPPPP_USE_PPPOE) || defined(IPNET_USE_VRRP))
    int   dummy;
#endif
}
Ipnet_netif_eth;


/*
 ****************************************************************************
 * 6                    PROTOTYPES
 ****************************************************************************
 */

IP_GLOBAL void ipnet_eth_sig_rx(Ipnet_data *net, Ipnet_sig *sig);

IP_GLOBAL void ipnet_eth_add_hdr(Ipcom_pkt *pkt,
                                 struct Ipnet_netif_struct *netif,
                                 const Ip_u8 *dst,
                                 const Ip_u8 *src,
                                 Ip_u16 frame_type_n);

IP_PUBLIC int ipnet_eth_if_init(struct Ipnet_netif_struct *netif);
#ifdef IPCOM_USE_NON_ETHERNET
IP_PUBLIC int ipnet_noeth_if_init(struct Ipnet_netif_struct *netif);
#endif

#if defined(IPNET_USE_VLAN) || defined(IPNET_USE_VLAN_STACKING)
IP_PUBLIC int ipnet_vlan_if_init(struct Ipnet_netif_struct *netif);
IP_GLOBAL int ipnet_vlan_create(struct Ipnet_socket_struct *sock, struct Ip_ifreq *ifreq);
IP_GLOBAL int ipnet_vlan_compact_create(Ipnet_socket *sock, struct Ip_ifreq *ifreq);
IP_INLINE Ip_u16
ipnet_vlan_get_tag(Ipcom_pkt *pkt)
{
    if (IP_BIT_ISFALSE(pkt->flags, IPCOM_PKT_FLAG_VLAN_TAG))
        return 0;
    return ipcom_pkt_get_int(pkt, IPCOM_PKT_INFO_VLAN_TAG, Ip_u16);
}
IP_GLOBAL void ipnet_vlan_set_tag(Ipcom_pkt *pkt, Ip_u16 tag);
#ifdef IPNET_USE_PER_SOCKET_VLAN_TAG
IP_GLOBAL Ipnet_pkt_eth *ipnet_vlan_add_hdr(Ipcom_pkt *pkt,
                                            struct Ipnet_netif_struct *netif,
                                            Ip_u16 *frame_type_n);
#endif
#ifdef IPNET_USE_NETLINKSOCK
IP_GLOBAL void ipnet_vlan_rtnetlink_init(void);
#endif
#else
#define ipnet_vlan_get_tag(pkt)      0
#define ipnet_vlan_set_tag(pkt, tag) IP_NOOP
#endif /* IPNET_USE_VLAN || IPNET_USE_VLAN_STACKING */

#ifdef IPNET_USE_VLAN_STACKING
IP_PUBLIC Ipnet_pkt_eth *ipnet_svlan_add_svtag(Ipnet_netif *netif,
                                               Ip_u16 sock_vtag,
                                               Ip_u16 eth_type,
                                               Ipcom_pkt *pkt);
IP_PUBLIC void * ipnet_svlan_set_eth_type(Ipnet_netif *netif,
                                          Ipnet_pkt_eth *eth,
                                          Ip_bool set_eth_type,
                                          Ip_u16 eth_type,
                                          Ipcom_pkt *pkt);
#endif /* IPNET_USE_VLAN_STACKING */

#ifdef IPNET_USE_BOND
IP_GLOBAL int ipnet_bond_if_enslave(Ipnet_netif *bondif, Ipnet_netif *netif);
IP_GLOBAL int ipnet_bond_if_release(Ipnet_netif *netif);
IP_GLOBAL Ipnet_netif* ipnet_bond_get_master(Ipnet_netif *netif);
IP_GLOBAL Ipcom_netif* ipnet_bond_get_tx_slave(Ipcom_pkt *pkt, Ipcom_netif *bondif);
#ifdef IPNET_USE_NETLINKSOCK
IP_GLOBAL void ipnet_bond_rtnetlink_init(void);
#endif
#endif /* IPNET_USE_BOND */

#ifdef IPCOM_USE_INET
IP_GLOBAL void ipnet_arp_set_state(struct Ipnet_route_entry_struct *rt,
                                   Ipnet_nd_state_t state,
                                   IP_CONST void *link_addr);
#endif /* IPCOM_USE_INET */
#ifdef __cplusplus
}
#endif

#endif


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
