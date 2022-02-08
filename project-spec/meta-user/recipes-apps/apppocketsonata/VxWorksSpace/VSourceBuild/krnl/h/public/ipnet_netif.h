/*
 * Copyright (c) 2006-2013,2014-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/* modification history
-----------------------
14aug15,ply change the ifconfig bytes stat to 64bit, V7NET-569
20jul14,chm Qos advenced components.(US36943)
*/
 
#ifndef IPNET_NETIF_H
#define IPNET_NETIF_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/* Types and function for network interface support in IPNET */

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

#include <ipcom_netif.h>
#include <ipcom_os.h>

#include "ipnet.h"
#ifdef IPCOM_USE_INET
#include "ipnet_ip4.h"
#endif
#ifdef IPCOM_USE_INET6
#include "ipnet_ip6.h"
#endif
#include "ipnet_neigh.h"
#ifdef IPNET_USE_IFQUEUE
#include "ipnet_pkt_queue.h"
#endif

#ifdef IPCOM_USE_JOB_QUEUE
#include <ipcom_job_queue.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#define IPNET_IF_UNSPECIFIED_INDEX     0
#define IPNET_IF_UNSPECIFIED_NAME      IP_NULL
#define IPNET_IF_END                   ((IP_CONST char *) -1)

/* ipnet_pif_notify(netif, event) values: */
#define IPNET_IF_NOTIFY_UP    1       /* Interface was brough up */
#define IPNET_IF_NOTIFY_DOWN  2       /* Interface was taken down */

/*
 * Iterate over all attached interfaces, the netif parameter will be
 * IP_NULL if all elements has been visited.
 */
#define IPNET_NETIF_FOR_EACH(netif_, i)                                  \
    for (i = 0; i < ipnet_shared()->netif.db->size || IP_NULL != ((netif_) = IP_NULL); i++) \
        if (((netif_) = (Ipnet_netif *) ipnet_shared()->netif.db->table[i]) != IP_NULL)

#define IPNET_NETIF_FOR_EACH_ON_VR(netif_, vr, i)                       \
    for (i = 0; i < ipnet_shared()->netif.db->size || IP_NULL != ((netif_) = IP_NULL); i++) \
        if (((netif_) = (Ipnet_netif *) ipnet_shared()->netif.db->table[i]) != IP_NULL \
            && ((vr) == (netif_)->vr_index || (vr) == IPCOM_VR_ANY))

/*
 * Same as above but will only use the one matching "ifindex" if that
 * variable is != 0
 */
#define IPNET_NETIF_FOR_EACH_OR_SPECIFIC_ON_VR(netif_, vr, ifindex, i)  \
    for (i = 0;                                                         \
         i < ipnet_shared()->netif.db->size || IP_NULL != ((netif_) = IP_NULL); \
         (ifindex) ? (i = ipnet_shared()->netif.db->size) : i++)        \
        if (((netif_) = (ifindex)                                       \
             ? ipnet_if_indextonetif((vr), (ifindex))                   \
             : (Ipnet_netif *) ipnet_shared()->netif.db->table[i]) != IP_NULL \
            && ((vr) == (netif_)->vr_index || (vr) == IPCOM_VR_ANY))

#define IPNET_NETIF_NUM_ATTACHED (ipnet_shared()->netif.db->elem)

/*
 * Returns a pointer to the next packet in the network interface
 * fast-FIFO queue.
 */
#define IPNET_NETIF_SND_Q_NEXT(pkt) ((pkt)->link_cookie_u.pktp)

/*
 *===========================================================================
 *                         IPNET_IF_LOCK/UNLOCK
 *===========================================================================
 */
#ifdef IP_PORT_LKM
# define IPCOM_PORT_IF_LOCK(netif)   ipcom_if_lock(&(netif)->ipcom)
# define IPCOM_PORT_IF_UNLOCK(netif) ipcom_if_unlock(&(netif)->ipcom)
#else
# define IPCOM_PORT_IF_LOCK(netif)   IP_NOOP
# define IPCOM_PORT_IF_UNLOCK(netif) IP_NOOP
#endif

#define IPNET_IF_LOCK(netif) \
    do { \
        ip_assert(netif); \
        ipcom_atomic_inc(&(netif)->ipcom.ref_count);  \
        IPCOM_PORT_IF_LOCK(netif); \
    } \
    while ((0))

#define IPNET_IF_UNLOCK(netif) \
    do { \
        ip_assert(netif); \
        IPCOM_PORT_IF_UNLOCK(netif); \
        if (IP_UNLIKELY(ipcom_atomic_sub_and_return(&(netif)->ipcom.ref_count, 1) < 0)) \
            ipnet_if_free(netif); \
    } \
    while ((0))


/*
 * Access to domain specific configuration
 */
#ifdef IPCOM_USE_INET
#ifdef IPCOM_USE_INET6
#define IPNET_NETIF_CONF(domain, netif, var)     \
    ((domain) == IP_AF_INET                      \
     ? (netif)->conf.inet.var                    \
     : (netif)->conf.inet6.var)
#else
#define IPNET_NETIF_CONF(domain, netif, var) (netif)->conf.inet.var
#endif
#else
#define IPNET_NETIF_CONF(domain, netif, var) (netif)->conf.inet6.var
#endif

/* initial number of slots in the softix table */
#define IPNET_NETIF_SOFTIX_SIZE_START  (32)   /* must be multiple of 32 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* Forward declaration */
struct Ipnet_data_struct;
struct Ipnet_flow_spec_struct;
struct Ipnet_ip4_data_struct;
struct Ipnet_ip6_dr_entry_struct;
struct Ipnet_ip6_nc_entry_struct;
struct Ipnet_ipsec_tdb_struct;
struct Ipnet_neigh_struct;
struct Ipnet_netif_eth_struct;
struct Ipnet_netif_ppp_struct;
struct Ipnet_netif_struct;
struct Ipnet_netif_wlan_struct;
struct Ipnet_route_entry_struct;

/*
 *===========================================================================
 *                      Ipnet_link_input
 *===========================================================================
 * Description: Process the link header and dispatch IPv4 packets to
 *              ipnet_ip4_input() and IPv6 packets to ipnet_ip6_input().
 *              The pkt->start must be changed to be the offset to the
 *              IPv4 or IPv6 header for IPv4 and IPv6 packets.
 * Parameters:  netif - A pointer to the network interface structure for this
 *              driver.
 *              pkt - The received packet. pkt->start is the offset to the
 *              link header.
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_link_input)(struct Ipnet_netif_struct *netif, Ipcom_pkt *pkt);

/*
 *===========================================================================
 *                      Ipnet_link_output
 *===========================================================================
 * Description: Adds the link header to a packet and calls the
 *              Ipnet_drv_output function for the interface.
 * Parameters:  neigh - information about the link-local node the
 *                      packet should be sent to. A pointer to the
 *                      Ipnet_netif structure and the link layer
 *                      address to use is all stored within the
 *                      neighbor entry.
 *              pkt - The packet to send. pkt->start is the offset to the
 *              IP header. pkt->start must be updated to be the offset to
 *              the link layer before calling netif->drv_output().
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_link_output)(Ipnet_neigh *neigh,
                                 Ipcom_pkt *pkt);

/*
 *===========================================================================
 *                      Ipnet_link_ip6_create_addr
 *===========================================================================
 * Description: Creates an IPv6 address based on the prefix and
 *              information from the network interface.
 * Parameters:  netif - A pointer to the network interface structure for this
 *              driver.
 *              prefix - The prefix to use (the topmost
 *              128 - netif->inet6_if_id_bits is used).
 *              in6_addr - Will contain the auto address if the call is
 *              successful.
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_link_ip6_create_addr)(struct Ipnet_netif_struct *netif,
                                          IP_CONST struct Ip_in6_addr* prefix,
                                          struct Ip_in6_addr* in6_addr);


/*
 *===========================================================================
 *                   Ipnet_link_ip6_mcast_to_link_addr
 *===========================================================================
 * Description: Returns the Ethernet address corresponding to a
 *              specific IPv6 multicast address.
 * Parameters:  netif - network interface the mapping should be done for
 *              in6_addr - an IPv6 multicast address.
 *              link_maddr - will contain the link layer multicast
 *              address corresponding to the IPv6 multicast address.
 *
 * Returns:
 *
 */
typedef void (*Ipnet_link_ip6_mcast_to_link_addr)(struct Ipnet_netif_struct *netif,
                                                  IP_CONST struct Ip_in6_addr* in6_addr,
                                                  Ip_u8 *link_maddr);



/*
 *===========================================================================
 *                   Ipnet_netif_neigh_create
 *===========================================================================
 * Description: Returns the neighbor entry for a specific flow/route combo,
 *              based on the interface's neighbour create routine.
 * Parameters:  domain    - INET domain
 *              netif     - Netif used for neigh creation
 *              flow_spec - Flow specification
 *              rt        - Route entry
 * Returns: A neighbour entry if successful, IP_NULL otherwise.
 *
 */
typedef struct Ipnet_neigh_struct *(*Ipnet_netif_neigh_create)(int domain,
                                                               struct Ipnet_netif_struct            *netif,
                                                               const struct Ipnet_flow_spec_struct  *flow_spec,
                                                               struct Ipnet_route_entry_struct      *rt);

/*
 *===========================================================================
 *                      Ipnet_link_ioctl
 *===========================================================================
 * Description: IO control function for the link layer.
 * Parameters:  netif - A pointer to the network interface structure for this
 *              driver.
 *              command - IPNET_IP4_SIOCxxx or IPNET_IP6_SIOCxxx style command.
 *              data - Depends on command.
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_link_ioctl)(struct Ipnet_netif_struct *netif,
                                Ip_u32 command,
                                void *data);


/*
 *===========================================================================
 *                      Ipnet_link_raw_output
 *===========================================================================
 * Description: Adds a link layer header and outputs the frame to the driver
 *              ARP (or similar) is bypassed.
 * Parameters:  netif - A pointer to the network interface structure for this
 *              driver.
 *              to - The link layer address of the recipient of this frame.
 *              pkt - The packet which should have a link layer header appended.
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_link_raw_output)(struct Ipnet_netif_struct *netif,
                                     IP_CONST struct Ip_sockaddr_ll *to,
                                     Ipcom_pkt *pkt);

/*
 *===========================================================================
 *                      Ipnet_link_get_frame_info
 *===========================================================================
 * Description: Gets header information from the frame header.
 * Parameters:  netif - A pointer to the network interface structure for this
 *              driver.
 *              frame - A complete link layer frame. pkt->start is the offset
 *              to the link layer header.
 *              pkt_type - Will be set to one of the IP_PACKET_xxx type,
 *              can be IP_NULL if this value is not needed.
 *              frame_type - Will be set to the frame type (i.e. one of the
 *              IPNET_ETH_P_xxx constants for Ethernet). can be IP_NULL if
 *              this information is not needed.
 *              src - Points to a buffer to where the source link address
 *              will be copied. Can be IP_NULL if not needed.
 *              dst - Points to a buffer to where the destination link address
 *              will be copied. Can be IP_NULL if not needed.
 * Returns:     0 = success, <0 = error code (-IPNET_ERRNO_xxx)
 *
 */
typedef int (*Ipnet_link_get_frame_info)(struct Ipnet_netif_struct *netif,
                                         Ipcom_pkt *frame,
                                         Ip_u8 *pkt_type,
                                         Ip_u16 *frame_type,
                                         Ip_u8 *src,
                                         Ip_u8 *dst);

/*
 *===========================================================================
 *                          Ipnet_set_link_addr
 *===========================================================================
 * Description: Setss the link address to use for the specified
 *              local address.
 * Parameters:  neigh - a neighbor entry
 * Returns:
 *
 */
typedef void (*Ipnet_set_link_addr)(Ipnet_neigh *neigh);


#ifdef IPNET_USE_NETLINKSOCK
struct Ipnet_netlink_mem;
struct Ip_rtnl_link_ops
{
    struct Ip_rtnl_link_ops *next;

    const char              *kind;

    Ip_size_t               maxtype;
    Ip_u16                  ift_type;
    void                    (*setup)(struct Ipnet_netif_struct *netif);
    int                     (*validate)(struct Ip_nlattr *tb[],
                                        struct Ip_nlattr *data[]);

    int                     (*newlink)(struct Ipnet_netif_struct *netif,
                                       struct Ip_nlattr *tb[],
                                       struct Ip_nlattr *data[]);

    int                     (*changelink)(struct Ipnet_netif_struct *netif,
                                          struct Ip_nlattr *tb[],
                                          struct Ip_nlattr *data[]);

    void                    (*dellink)(struct Ipnet_netif_struct *netif);

    Ip_size_t               (*get_size)(struct Ipnet_netif_struct *netif);

    int                     (*fill_info)(struct Ipnet_netlink_mem   *mem,
                                         struct Ipnet_netif_struct *netif);

    Ip_size_t               (*get_xstats_size)(struct Ipnet_netif_struct *netif);

    int                     (*fill_xstats)(struct Ipnet_netlink_mem   *mem,
                                           struct Ipnet_netif_struct *netif);

    int                     (*fill_link)(struct Ipnet_netlink_mem   *mem,
                                         struct Ipnet_netif_struct *netif);
};
#endif


/*
 *===========================================================================
 *                         Ipnet_portif
 *===========================================================================
 */
#ifdef IPNET_USE_CP
typedef enum
{
    IP_PORTIF_ADMIN_PTP_MAC_FORCE_AUTO = 0,
    IP_PORTIF_ADMIN_PTP_MAC_FORCE_TRUE,
    IP_PORTIF_ADMIN_PTP_MAC_FORCE_FALSE
} Ip_portif_admin_ptp_mac_val;

typedef struct Ipnet_portif_stats_struct
{
    Ip_u64 ifInOctets;
    Ip_u64 ifInUcastPkts, ifInMulticastPkts, ifInBroadcastPkts;
    Ip_u64 ifInDiscards, ifInErrors;
    Ip_u64 ifOutOctets;
    Ip_u64 ifOutUcastPkts, ifOutMulticastPkts, ifOutBroadcastPkts;
    Ip_u64 ifOutErrors;
} Ipnet_portif_stats;

typedef struct Ipnet_portif_struct
{
    int (*update_status) (struct Ipnet_netif_struct *); /* If it doesn't return 0, then status may not have been properly updated */
    struct
    {
        Ip_bool mac_enabled; /* MAC_Enabled */
        Ip_bool mac_oper; /* MAC_Operational */
        Ip_bool oper_ptp_mac; /* operPointToPointMAC */
        Ip_portif_admin_ptp_mac_val admin_ptp_mac; /* adminPointToPointMAC (for controlled ports ONLY) */
    } status;
    int (*update_stats) (struct Ipnet_netif_struct *); /* If it doesn't return 0, then stats will have been kept/updated */
    Ipnet_portif_stats stats; /* Updated by PAC or SecY. Must call update_stats first to get accurate counts. */
    struct
    {
        Ip_bool cp_enabled; /* ControlledPortEnabled */
    } ctrl; /* Updated by PAE or KaY. Read only values for others. */
} Ipnet_portif;
#endif

/*
 *===========================================================================
 *                       Ipnet_netif_conf
 *===========================================================================
 */

#ifdef IPCOM_USE_INET
struct Ipnet_netif_inet_conf
{
    int base_hop_limit;
    int max_pending;
    int max_unicast_solicit;
    int max_multicast_solicit;
    int max_application_solicit;
    int base_reachable_time;
    int base_retransmit_time;
    int delay_first_probe_time;
    int neigh_min_random_factor;
    int neigh_max_random_factor;
    int neigh_linger_time;
    Ip_bool neigh_always_perm;
    int neigh_cache_to_live;
    int dst_cache_to_live;
    int dst_cache_transient_cnt;
    int dst_cache_transient_to_live_msec;
    int icmp_redirect_send;
    Ip_bool icmp_redirect_receive;
    Ip_bool icmp_ignore_echo_req;
    Ip_bool icmp_ignore_timestamp_req;
    Ip_bool icmp_send_time_exceeded;
    Ip_bool icmp_send_dst_unreach;
    Ip_bool icmp_send_addr_mask;
    Ip_bool icmp_ignore_broadcast;
    int igmp_max_version;
    Ip_bool dont_forward_broadcast;
    Ip_bool enable_path_mtu_discovery;
    Ip_bool send_gratuitous_arp;
    Ip_bool delete_addr_on_duplicate_detect;
    Ip_bool network_proxy_arp;
    Ip_bool auto_proxy_arp;
    Ip_bool accept_source_route;
    Ip_bool allow_mcast_src_mac;
#ifdef IPNET_USE_RFC5227
    Ip_bool address_conflict_detect;
#endif /* IPNET_USE_RFC5227 */
#ifdef IPNET_USE_RFC3927
    Ip_bool auto_conf;
#endif
#if defined(IPNET_USE_RFC5227) || defined(IPNET_USE_RFC3927)
    int ll_probe_wait;
    int ll_probe_num;
    int ll_probe_min;
    int ll_probe_max;
    int ll_announce_wait;
    int ll_announce_num;
    int ll_announce_interval;
    int ll_max_conflicts;
    int ll_rate_limit_interval;
    int ll_defend_interval;
#endif /* #if defined(IPNET_USE_RFC5227) || defined(IPNET_USE_RFC3927) */
};
#endif /* IPCOM_USE_INET */

#ifdef IPCOM_USE_INET6
struct Ipnet_netif_inet6_conf
{
    int base_hop_limit;
    Ip_bool add_autonomous_addr;
    int max_pending;
    int max_unicast_solicit;
    int max_multicast_solicit;
    int max_application_solicit;
    int dad_transmits;
    int base_reachable_time;
    int base_retransmit_time;
    int delay_first_probe_time;
    int neigh_min_random_factor;
    int neigh_max_random_factor;
    int neigh_linger_time;
    Ip_bool neigh_always_perm;
    int neigh_cache_to_live;
    int dst_cache_to_live;
    int dst_cache_transient_cnt;
    int dst_cache_transient_to_live_msec;
    int router_lifetime;
    int rt_sol_cnt;
    int rt_sol_min_interval;
    int rt_sol_max_interval;
    int max_rt_sol_delay;
    int max_default_gw_from_ra;
    int max_prefixes_from_ra;
    int icmp_redirect_send;
    Ip_bool icmp_redirect_receive;
    Ip_bool icmp_ignore_echo_req;
    Ip_bool icmp_send_time_exceeded;
    Ip_bool icmp_send_dst_unreach;
    Ip_bool accept_rt_adv;
    int mld_max_version;
    Ip_bool auto_conf;
    Ip_bool rt_hdr0;
#ifdef IPNET_USE_RFC3041
    Ip_bool privacy_extensions;
    unsigned tmp_valid_lifetime;
    unsigned tmp_preferred_lifetime;
    int tmp_regen_advance;
    int tmp_idgen_retries;
#endif /* IPNET_USE_RFC3041 */
    Ip_bool treat_mobopt_unknown;
};
#endif /* IPCOM_USE_INET6 */

struct Ipnet_netif_conf
{
#ifdef IPCOM_USE_INET
    struct Ipnet_netif_inet_conf  inet;
#endif
#ifdef IPCOM_USE_INET6
    struct Ipnet_netif_inet6_conf inet6;
#endif
};

#if defined(IPNET_USE_RFC5227) || defined(IPNET_USE_RFC3927)
/*
 *===========================================================================
 *                         Ipnet_netif_acd
 *===========================================================================
 */
typedef struct Ipnet_netif_acd_struct
{
    Ip_u8             conflicts;       /* Number of address conflicts seen on this interface */
    Ip_time_t         last_probe_time; /* Last time an ARP probe sequence was started on this interface */
}
Ipnet_netif_acd;
#endif

struct Ipnet_netif_stats_struct
{
    /* Statistics, do not change the order since IP_SIOCXRESETSTAT make assumptions on order */
    Ip_u32     ipackets;    /* Packets received on interface */
    Ip_u32     ierrors;     /* Input errors on interface */
    Ip_u32     opackets;    /* Packets sent on interface */
    Ip_u32     oerrors;     /* Output errors on interface */
    Ip_u32     collisions;  /* Collisions on csma interfaces */
    Ip_u64     ibytes;      /* Total number of octets received */
    Ip_u64     obytes;      /* Total number of octets sent */
    Ip_u32     imcasts;     /* Packets received via multicast */
    Ip_u32     omcasts;     /* Packets sent via multicast */
    Ip_u32     iqdrops;     /* Dropped on input, this interface */
    Ip_u32     noproto;     /* Destined for unsupported protocol */
} IP_ALIGNED(IP_NOMINAL_CACHE_LINE);

typedef struct Ipnet_netif_stats_struct Ipnet_netif_stats;

/*
 *===========================================================================
 *                         Ipnet_netif
 *===========================================================================
 */
typedef struct Ipnet_netif_struct
{
    /*
     * IPCOM Ipcom_netif structure.  See IPCOM/include/ipcom_netif.h
     */
    Ipcom_netif   ipcom;
    /*
     * Index of the stack instance packets will be queued to by
     * ipcom_pkt_input_queue(). This value can be change via the
     * IP_SIOCSIFRXIDX ioctl.
     */
    Ip_u16        default_rx_idx;
    /*
     * The ID of the virtual router this interface is assigned to
     */
    Ip_u16        vr_index;
    Ip_u32        flags2;         /* IPNET_FLAG_IFF2_xxx flags */

    /*
     * Additional interface data, can only be used by link layers
     * implemented inside IPNET. External link layer protocols (like
     * PPP) must use the "plink" member in Ipcom_netif.
     */
    void                           *private_data;
    /* Pointer to Ethernet info. IP_NULL if not Eth if */
    struct Ipnet_netif_eth_struct  *eth;
#ifdef IPNET_USE_WLAN
    struct Ipnet_netif_wlan_struct *wlan;  /* Pointer to WLAN. */
#endif

#ifdef IPCOM_USE_INET
    struct Ipnet_ip4_addr_entry_struct *inet4_addr_list;    /* List of IPv4 addresses */

    Ipnet_timeout    *igmpv1_querier_present_tmo; /* Timer for IGMPv1 mode */
#ifdef IPNET_USE_SOURCE_SPECIFIC_MCAST
    Ipnet_timeout    *igmpv2_querier_present_tmo; /* Timer for IGMPv2 mode */
#endif
    Ip_u16            igmp_query_interval;        /* The last seen query interval */
    Ip_u8             igmp_robustness_variable;   /* The last seen robustness value */

#ifdef IPNET_USE_RFC1256
    Ipnet_timeout    *inet4_rfc1256_tmo;      /* Timeout structure for RFC1256 RT ADV/SOL timeout */
    Ip_u8             inet4_rfc1256_flags;    /* State for RFC1256                                */
    Ip_u8             inet4_rfc1256_num;      /* Number of advertisements; solicitations left     */
    Ip_u8             inet4_rfc1256_state;    /* Current state                                    */
    Ip_u8             inet4_rfc1256_mode;     /* Mode of operation                                */
#endif

#ifdef IPNET_USE_RFC3927
    struct Ip_in_addr inet4_lladdr;          /* The current link local address */
#endif

#if defined(IPNET_USE_RFC5227) || defined(IPNET_USE_RFC3927)
    struct Ipnet_netif_acd_struct acd;       /* Address conflict detection */
#endif
#endif /* IPCOM_USE_INET */

#ifdef IPCOM_USE_INET6
    struct Ipnet_ip6_addr_entry_struct *inet6_addr_list; /* All addresses on this interface */

    Ipnet_neigh_probecb inet6_neigh_probe;   /* inet6 specific probe function */
    Ip_u32         inet6_nd_reachable_time;  /* 0 = use default, else the neighbor reachable time (msec) */
    Ip_u32         inet6_nd_retransmit_time; /* 0 = use default, else the ND retransmit time (msec) */
    Ip_u8          inet6_nd_curhoplimit;     /* default hop limit on packages as specified by
                                                on-link router via router advertisement
                                                or 0 in which case conf.inet6.base_hop_limit is used */
    Ip_u8          inet6_rs_retrans_count;   /* Number of route solicitations left to send */
    Ip_u8          inet6_if_id_bits;   /* Number of bits that should be used for host id
                                          when creating a IPv6 from the link address */
    Ip_u8          mld_robustness_variable;   /* The last seen robustness value */
    Ip_u16         mld_query_interval;        /* The last seen query interval */
#ifdef IPNET_USE_SOURCE_SPECIFIC_MCAST
    Ipnet_timeout *mldv1_querier_present_tmo; /* Timer for MLDv1 mode */
#endif
    Ipnet_timeout *inet6_rs_tmo;
#endif /* IPCOM_USE_INET6 */

    /***** IPNET to link layer functions (downcall) *****/
    Ipnet_link_input      link_input;     /* Parse packet in link layer. */
    Ipnet_link_output     link_output;    /* The "output" member of
                                             Ipnet_neigh will
                                             point to this function
                                             when the link layer
                                             address of the next hop
                                             is known */
    Ipnet_link_ioctl      link_ioctl;
    Ipnet_neigh_tx        neigh_tx;       /* Link layer specific
                                           * neighbor transmission
                                           * function. May be IP_NULL
                                           * if the standard neighbor
                                           * functions should be
                                           * used
                                           */
    Ipnet_set_link_addr   set_lladdr;     /*
                                           * Sets the link layer
                                           * address of on a neighbor
                                           * for a local address.
                                           */
#ifdef IPCOM_USE_INET
    Ipnet_neigh_probecb   inet4_neigh_probe; /* Handler to learn link
                                                address of peer node */
#endif
#ifdef IPCOM_USE_INET6
    Ipnet_link_ip6_create_addr link_ip6_create_addr;
    Ipnet_link_ip6_mcast_to_link_addr ip6_mcast_to_link_addr;
#endif /* IPCOM_USE_INET6 */

    Ipnet_netif_neigh_create    neigh_create;

    /* IPNET to link layer packet functions. */
#ifdef IPCOM_USE_PACKET
    Ipnet_link_raw_output       link_raw_output;
#endif
    Ipnet_link_get_frame_info   link_get_frame_info;

#ifdef IPNET_USE_NETLINKSOCK
    struct Ip_rtnl_link_ops     *rtnetlink_ops;
    Ip_u32                      rtnetlink_last_iflags;
#endif
#ifdef IPNET_USE_VRRP
    /*
     * List of VRRP address that this node is master for on this link.
     */
    Ipcom_list                  vrrp_addr_list;
#endif
#ifdef IPNET_USE_SECY
    struct Ipnet_secy_struct    *secy; /* MAC Security Entity */
#endif
#ifdef IPNET_USE_CP
    /* Controlled and Uncontrolled port interfaces are associated with
     * a Secure MAC Entity (SecY) or a Port Access Controller (PAC).
     * When one of those entities is initialized, it installs its
     * handles here.
     */
    Ipnet_portif                *controlled_port, *uncontrolled_port;
#endif
#ifdef IPBRIDGE
    /***** Bridge specific fields *****/
    struct Ipbridge_portmap_st *portmap; /* Port map associated with this bridge I/F (NULL if this is not a bridge I/F) */
    Ip_u16 bridge_port_index; /* Port index in the Bridge for this interface (meaningless if not a bridged I/f) */
#endif
    /***** Interface output queue *****/
    Ipcom_spinlock       snd_q_lock;
    Ipcom_pkt            *snd_head;  /* Head of output queue */
    Ipcom_pkt            *snd_tail;  /* Tail of output queue */
#ifdef IPNET_USE_IFQUEUE
    Ipnet_pkt_queue      *snd_queue; /* QoS queue */
#endif
#ifndef IPCOM_USE_JOB_QUEUE
    /* Used to detected fast driver restart, i.e. that the driver calls output_done before the
       send call returns */
    Ipcom_atomic_t        snd_id;
#endif

    /* Dynamic configuration */
    struct Ipnet_netif_conf conf;

    Ipnet_netif_stats    *stats; /* array, one entry per stack instance */
}
Ipnet_netif;

/* Packets received on this interface will not be forwarded if set */
#define IPNET_IFF2_NO_IPV4_FORWARD    (1 << 0)
/* Packets received on this interface will not be forwarded if set */
#define IPNET_IFF2_NO_IPV6_FORWARD    (1 << 1)
/* Set if this interface cannot handle IPv4 traffic */
#define IPNET_IFF2_NO_IPV4_SUPPORT    (1 << 3)
/* Included in random seed */
#define IPNET_IFF2_RANDOM_SEED        (1 << 4)
/* Disabled all IPv6 processing since duplicate address detection
   failed for the automatically assigned link local address */
#define IPNET_IFF2_IPV6_DISABLED      (1 << 5)
/* Do not select global addresses */
#define IPNET_IFF2_NO_GLOBAL_SRC      (1 << 6)
/* No DAD has been sent since this link was bought up and running */
#define IPNET_IFF2_FIRST_NS           (1 << 7)
/* RTNETLINK event needs be sent on this interface  */
#define IPNET_IFF2_RTNETLINK_EVENT    (1 << 8)

/*
 *===========================================================================
 *                        Ipnet_ppp_peer
 *===========================================================================
 * Keeps track of the peer address on a PPP interface.
 */
typedef struct Ipnet_ppp_peer_struct
{
    Ipnet_netif       *netif;
#ifdef IPCOM_USE_INET
    /* The peer address of an PPP interface */
    struct Ip_in_addr  peer4;
#endif
#ifdef IPCOM_USE_INET6
    /* The peer address of an PPP interface */
    struct Ip_in6_addr peer6;
#endif
}
Ipnet_ppp_peer;

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */


/*
 *===========================================================================
 *                         internal funcs
 *===========================================================================
 */
IP_GLOBAL void  ipnet_if_update_mib2_ifLastChange(Ipnet_netif *netif);
IP_GLOBAL Ip_u32 * ipnet_if_get_index_array(Ip_u16 vr, Ip_u32 ifindex, unsigned *array_len);

IP_GLOBAL void ipnet_if_free(Ipnet_netif *netif);
IP_GLOBAL void ipnet_if_clean(Ipnet_netif *netif, Ip_bool clean_ip4, Ip_bool clean_ip6);
IP_GLOBAL int ipnet_if_detach(Ipnet_netif *netif);
IP_GLOBAL Ip_bool ipnet_if_can_detach(Ipcom_netif *netif);

IP_FASTTEXT IP_GLOBAL int ipnet_if_output(Ipnet_netif *netif, Ipcom_pkt *pkt);
IP_FASTTEXT IP_GLOBAL int ipnet_if_drv_output(Ipnet_netif *netif, Ipcom_pkt *pkt);

IP_GLOBAL void ipnet_if_clean_snd_queue(Ipnet_netif *netif);

IP_GLOBAL int ipnet_if_drv_ioctl(Ipnet_netif *netif, Ip_u32 command, void *data);
IP_GLOBAL int ipnet_if_link_ioctl(Ipnet_netif *netif, Ip_u32 command, void *data);
IP_GLOBAL int ipnet_if_link_lock_ioctl_unlock(Ipnet_netif *netif, Ip_u32 command, void *data);
IP_GLOBAL Ip_size_t ipnet_if_to_sockaddr_dl(Ipnet_netif *netif, struct Ip_sockaddr_dl *dl);
IP_GLOBAL Ipnet_netif *ipnet_if_indextonetif(Ip_u16 vr, Ip_u32 ifindex);
IP_GLOBAL Ipnet_netif *ipnet_if_nametonetif(Ip_u16 vr, IP_CONST char *ifname);

IP_GLOBAL int ipnet_netif_change_flags(Ipnet_netif **netif, Ip_u32 flags, Ip_u32 change);

#ifdef IPPPP
IP_PUBLIC int ipnet_ppp_if_init(Ipnet_netif *netif);
#endif

#ifdef IPBRIDGE
IP_GLOBAL int ipnet_bridge_if_init(Ipnet_netif *netif);
#endif

IP_GLOBAL void ipnet_if_init_ppp_peer(Ipnet_netif *netif, Ipnet_ppp_peer *p);
IP_GLOBAL void ipnet_if_clean_ppp_peer(Ipnet_ppp_peer *p);
#ifdef IPCOM_USE_INET
IP_GLOBAL int ipnet_if_set_ipv4_ppp_peer(Ipnet_ppp_peer *p, IP_CONST struct Ip_in_addr *peer4);
#endif
#ifdef IPCOM_USE_INET6
IP_GLOBAL int ipnet_if_set_ipv6_ppp_peer(Ipnet_ppp_peer *p, IP_CONST struct Ip_in6_addr *peer6);
IP_GLOBAL Ip_bool ipnet_netif_has_valid_inet6_unicast_addr(Ipnet_netif* netif);
#endif

IP_GLOBAL Ipnet_neigh *ipnet_netif_neigh_create(int                             domain,
                                                Ipnet_netif                     *netif,
                                                const Ipnet_flow_spec           *flow_spec,
                                                struct Ipnet_route_entry_struct *rt);

IP_GLOBAL Ip_bool ipnet_netif_is_ifproxy(Ipnet_netif *netif);
IP_GLOBAL void    ipnet_netif_snd_queue_push_cb(void *arg);
IP_GLOBAL Ip_bool ipnet_netif_push_bitmap_expand(struct Ipnet_data_struct *net,
                                                 Ip_u32 oldsize, Ip_u32 newsize);

IP_GLOBAL int ipnet_if_init_once(void);



/*
 *===========================================================================
 *                     Ipnet_if_attach_handler
 *===========================================================================
 * Description: Function that knows how to locate and attach a physical
 *              network device.
 * Parameters:  devname_and_unit - name of the driver and the unit number
 *                                 ex: "gei0" -> drivername "gei" unit "0"
 *              ifname - may be IP_NULL if the
 *                       interface name == devname_and_unit
 *                       or the name of the interface to attach.
 * Returns:     0 success
 *              0 < error code
 */
typedef int (*Ipnet_if_attach_handler)(const char *devname_and_unit, const char *ifname);
IP_GLOBAL void ipnet_register_if_attach_handler(Ipnet_if_attach_handler f);

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
