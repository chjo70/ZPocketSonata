/*
 * Copyright (c) 2006-2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
28mar17,ljl  Stop generating atomic fragments (V7NET-1307)
21arp14,h_x  remove mip US35691
*/

#ifndef IPNET_DST_CACHE_H
#define IPNET_DST_CACHE_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 *
 * A destination cache entry contains information about a specific
 * flow between a specific address on the local node to a specific
 * address on a peer node. Information that is relevant to a specific
 * flow is stored here. An example of that information is the value of
 * the path-MTU between the local node and the peer. ICMP messages
 * like MTU-too-big and redirect will only affect the destination
 * cache and not the FIB.
 *
 * The destination cache is also a cache for some information that
 * costs CPU cycles to compute and stays constant within a specific
 * flow of traffic between two nodes. Such information includes which
 * local IP address to use, which neighbor entry to used and which
 * egress interface to use.
 *
 * The current implementation of the destination cache is flushed each
 * time the FIB is changed, interface is brought up/down or if IP
 * addresses are added/removed to an interface. It is possible to be
 * more smart about what to flush; that is a possible future
 * enhancement of the destination cache.
 *
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

#include <ipcom_cstyle.h>
#include <ipcom_hash.h>
#include <ipcom_pkt.h>
#include <ipcom_sock.h>
#include <ipcom_type.h>

#include "ipnet.h"
#include "ipnet_peer_info.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* Forward declarations */
struct Ipnet_data_struct;
struct Ipnet_dst_cache_struct;
struct Ipnet_flow_spec_struct;
struct Ipnet_neigh_struct;
struct Ipnet_route_entry_struct;
struct Ipnet_sig_struct;
struct Ipnet_socket_struct;

/*
 *===========================================================================
 *                    Ipnet_dst_cache_tx_func
 *===========================================================================
 * Description: Handler that will transmit the packet via the IP
 *              transmit handler.
 * Parameters:  dst - destination cache entry
 *              pkt - packet to transmit
 * Returns:     0 = success
 *             <0 = error code
 */
typedef int (*Ipnet_dst_cache_tx_func)(struct Ipnet_dst_cache_struct *dst,
                                        Ipcom_pkt *pkt);

/*
 *===========================================================================
 *                    Ipnet_dst_cache_rx_func
 *===========================================================================
 * Description: Handler that will deliver the packet to the IP
 *              protocol receive handler.
 * Parameters:  dst - destination cache entry
 *              pkt - packet to transmit
 * Returns:     0 = success
 *             <0 = error code
 */
typedef int (*Ipnet_dst_cache_rx_func)(struct Ipnet_dst_cache_struct *dst,
                                       Ipcom_pkt *pkt);

/*
 *===========================================================================
 *                    Ipnet_dst_cache_foreach_func
 *===========================================================================
 * Description: Function that will be run for every destination in the
 *              destination cache.
 * Parameters:  dst - a destination cache entry
 *              user_data - user defined data passed to ipnet_dst_cache_foreach()
 * Returns:
 *
 */
typedef void (*Ipnet_dst_cache_foreach_func)(struct Ipnet_dst_cache_struct *dst,
                                             void *user_data);



/*
 *===========================================================================
 *                    Ipnet_dst_cache_domain_ctor
 *===========================================================================
 * Description: Domain specific destination cache constructor. This
 *              function must initialize the transmission and reception
 *              handlers. It must also assign the local address to be
 *              used for the entry.
 * Parameters:  dst - destination cache entry
 *              rt - FIB entry that matched the flow specification
 *                    used to create 'dst'
 * Returns:
 */
typedef int (*Ipnet_dst_cache_domain_ctor)(struct Ipnet_dst_cache_struct *dst,
                                           struct Ipnet_route_entry_struct *rt);


/*
 *===========================================================================
 *                 Ipnet_flow_spec_from_pkt_domain_func
 *===========================================================================
 * Description: Handler that knows how to extract information from the
 *              IP packet.
 * Parameters:  storage - pointer to where flow information should be stored.
 *              pkt - packet that contains either an IPv4 or IPv6 header.
 * Returns:
 *
 */
typedef void
    (*Ipnet_flow_spec_from_pkt_domain_func)(struct Ipnet_flow_spec_struct *storage,
                                            Ipcom_pkt *pkt);


/*
 *===========================================================================
 *                 Ipnet_flow_spec_from_sock_domain_func
 *===========================================================================
 * Description: Handler that knows how to extract information from the
 *              socket.
 * Parameters:  storage - pointer to where flow information should be stored.
 *              sock - socket created for IP_AF_INET or IP_AF_INET6.
 *              domain_data - pointer to domain specific data.
 * Returns:     0 = success
 *             <0 = error code
 *
 */
typedef int (*Ipnet_flow_spec_from_sock_domain_func)(struct Ipnet_flow_spec_struct *storage,
                                                     struct Ipnet_socket_struct *sock,
                                                     const void *domain_data);


/*
 *===========================================================================
 *                 Ipnet_flow_spec_from_info_domain_func
 *===========================================================================
 * Description: Handler to build the flow info based on information and domain
 * Parameters:  storage - pointer to where flow information should be stored.
 *              domain_data - pointer to domain specific data.
 * Returns:     0 = success
 *             <0 = error code
 *
 */
typedef int (*Ipnet_flow_spec_from_info_domain_func)(struct Ipnet_flow_spec_struct *storage,
                                                     const void                 *src,
                                                     const void                 *dst);


/*
 * This structure holds all fields that is used to distinguish one
 * flow from another, i.e. this is what specifies a specific flow.
 * The minimum information is domain and "to" + "from" addresses. Note
 * that the source address of the flow specification might be the ANY
 * address for flows that originates from the local host. This would
 * be the case for any transmission done via a socket that is
 * implicitly bound or explicitly bound to the ANY address.
 *
 * Do not initialize this structure "by hand", use one of the
 * ipnet_flow_spec_from_xxx() functions declared below,
 * ipnet_ip4_flow_spec_from_pkt() (ipnet_ip4.c) or,
 * ipnet_ip6_flow_spec_from_pkt() (ipnet_ip6.c).
 */
typedef struct Ipnet_flow_spec_struct
{
    Ip_u32                 flags;  /* IPNET_FSF_xxx flags */
    union Ip_in_addr_union to;     /* IP address this flow is
                                      directed to */
    union Ip_in_addr_union from;   /* IP address specified as the
                                      source address, might be ANY */
    Ip_u32                 egress_ifindex; /* index of the egress
                                      network interface for this flow
                                      or 0 if unspecified */
    Ip_u32                 ingress_ifindex; /* index of the ingress
                                      network interface 0 if
                                      unspecified */
    Ip_u32                 zone_id; /* Id of the zone this flow
                                      operates within. Only used by
                                      IPv6, always zero for IPv4 */
    Ip_u16                 vr;     /* Virtual router index */
    Ip_u8                  ds;     /* TOS (IPv4) or traffic class
                                     (IPv6) field. */
} Ipnet_flow_spec;


/*
 * Set if flow is IPv6, cleared if flow is IPv4
 */
#define IPNET_FSF_IPV6          (1u << 31)
/*
 * Set if flow was created using the MSG_DONTROUTE flag, cleared
 * otherwise
 */
#define IPNET_FSF_DONTROUTE     (1u << 30)

/*
 * No discard neigh management on this flow.
 */
#define IPNET_FSF_DONTDISCARD   (1u << 29)

/*
 * Set/get the  IPV6_PREFER_SRC_xxx flags in a flow specification
 */
#define IPNET_FS_PREFER_SRC_MASK    0x0000ffffu
#define IPNET_FS_GET_PREFER_SRC(fs) ((fs)->flags & IPNET_FS_PREFER_SRC_MASK)
#define IPNET_FS_SET_PREFER_SRC(fs, x)                         \
    do {                                                       \
        Ip_u32 x_ = (Ip_u32)(x);                               \
        ip_assert(!(x_ & ~IPNET_FS_PREFER_SRC_MASK));          \
        (fs)->flags |= x_;                                     \
    } while (0)

/*
 * A destination cache contains all information required to receive or
 * transmit an IP packet that belongs to this flow.
 * It is forbidden to keep a pointer to the destination cache between
 * two different packet reception/transmission, i.e. whatever that
 * ipnet_dst_cache_get() returns is only valid for the current packet!
 *
 * Once created, all fields in this structure should be considered
 * read-only by anything that uses it. All modifications should be
 * done by the ipnet_dst_cache.c module.
 *
 */
typedef struct Ipnet_dst_cache_struct
{
    Ipnet_flow_spec      flow_spec; /* Lookup key for this entry */

    Ip_u32               use;       /* Count uses (lookups) of this entry. */

    Ipnet_dst_cache_tx_func tx;     /* Current transmission handler */
    Ipnet_dst_cache_tx_func real_tx;/* Transmission handler set with
                                     * ipnet_dst_cache_set_tx_handler */
    Ipnet_dst_cache_rx_func rx;     /* Current reception handler */
    Ipnet_dst_cache_rx_func real_rx;/* Reception handler set with
                                     * ipnet_dst_cache_set_rx_handler */
    int transient_cnt;              /* Number of times this still has
                                     * to be used before moved out of
                                     * transient state.
                                     */

    enum Ipnet_addr_type to_type;   /* Address type of the 'to'
                                       address */
    union Ip_in_addr_union laddr;  /* Local address used in this
                                      flow. This field will be the ANY
                                      address for flows that does not
                                      terminate on this node,
                                      i.e. flows routed through this
                                      node. It is the source address
                                      for egress flows and the
                                      destination address for ingress
                                      flows */
    Ip_u32              path_mtu;  /* The path-MTU of this flow */

    struct Ipnet_data_struct *net; /* Stack instance this cache
                                    * belongs to */
    struct Ipnet_netif_struct *ingress_netif; /* Network interface
                                      pointer of the ingress
                                      interface. Never IP_NULL for
                                      ingress or forwarding flows. */
    struct Ipnet_neigh_struct *neigh; /* Cached neighbor entry, Points to
                                      the neighbor entry that must be
                                      used when transmitting traffic
                                      along this flow. Is never
                                      IP_NULL for egress or forwarding
                                      flows. */
    Ipnet_peer_info    *peer_info; /* Cached peer information. */
    Ipnet_timeout       tmo;       /* static timeout for this entry */
    struct Ipnet_route_entry_struct  *rt; /* The route entry created from,
                                      for use count transfer. If rt != IP_NULL,
                                      this entry holds a lockcnt reference
                                      to the route. */
} Ipnet_dst_cache;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/*
 * Destination cache functions
 */

IP_GLOBAL Ipnet_dst_cache *
ipnet_dst_cache_get(struct Ipnet_data_struct *net,
                    const Ipnet_flow_spec *flow_spec);

#define ipnet_dst_cache_tx(dst, pkt) (dst)->tx(dst, pkt)
#define ipnet_dst_cache_rx(dst, pkt) (dst)->rx(dst, pkt)

IP_GLOBAL struct Ipnet_route_entry_struct *
ipnet_dst_cache_select_best_rt(int domain,
                               const Ipnet_flow_spec *flow_spec,
                               struct Ipnet_route_entry_struct *rt);
IP_GLOBAL int
ipnet_dst_cache_new(struct Ipnet_data_struct *net,
                    const Ipnet_flow_spec *flow_spec,
                    Ipnet_dst_cache_domain_ctor domain_ctor,
                    Ipnet_dst_cache **pdst);

IP_GLOBAL void
ipnet_dst_cache_set_rx_handler(Ipnet_dst_cache *dst,
                               Ipnet_dst_cache_rx_func rx_func);
IP_GLOBAL void
ipnet_dst_cache_set_tx_handler(Ipnet_dst_cache *dst,
                               Ipnet_dst_cache_tx_func tx_func);

IP_GLOBAL void
ipnet_dst_cache_set_path_mtu(Ipnet_dst_cache *dst, Ip_u32 mtu);

IP_GLOBAL Ipnet_dst_cache *
ipnet_dst_cache_blackhole_flow_spec(struct Ipnet_data_struct *net,
                                    const Ipnet_flow_spec *flow_spec);

IP_GLOBAL Ipnet_dst_cache *
ipnet_dst_cache_blackhole(struct Ipnet_data_struct *net);

IP_GLOBAL void
ipnet_dst_cache_flush(Ip_u16 vr, int domain);

IP_GLOBAL void
ipnet_dst_cache_flush_where_neigh_is(const struct Ipnet_neigh_struct *neigh);

IP_GLOBAL void
ipnet_dst_cache_flush_local(Ip_u16 vr, int domain, struct Ipnet_data_struct *net);

IP_GLOBAL void
ipnet_dst_cache_foreach(struct Ipnet_data_struct *net,
                        Ipnet_dst_cache_foreach_func foreach_func,
                        void *user_data);

IP_GLOBAL int
ipnet_dst_cache_init(struct Ipnet_data_struct *net);

IP_GLOBAL int
ipnet_dst_cache_start(struct Ipnet_data_struct *net);


/*
 * Flow specification creation functions
 */

IP_GLOBAL int
ipnet_flow_spec_domain(const Ipnet_flow_spec *flow_spec);

IP_GLOBAL int
ipnet_flow_spec_from_sock(Ipnet_flow_spec *storage,
                          struct Ipnet_socket_struct *sock,
                          const void *domain_data,
                          Ipnet_flow_spec_from_sock_domain_func domain_func);
IP_GLOBAL int
ipnet_flow_spec_from_info(Ipnet_flow_spec                       *flow_spec,
                          Ip_u16                                vr,
                          const void                            *src,
                          const void                            *dst,
                          Ip_u32                                zone_id,
                          Ip_u8                                 tos_tclass,
                          struct Ipnet_netif_struct             *iif,
                          struct Ipnet_netif_struct             *oif,
                          Ipnet_flow_spec_from_info_domain_func domain_func);

IP_GLOBAL void
ipnet_dst_sig_rx(struct Ipnet_data_struct *net, struct Ipnet_sig_struct *sig);

IP_GLOBAL Ip_bool
ipnet_dst_do_on_stack_idx(int stack_idx,
                          const Ipnet_flow_spec *flow_spec,
                          Ipcom_pkt *pkt,
                          Ipnet_dst_cache_rx_func rx_fun,
                          Ipnet_dst_cache_domain_ctor dst_rx_ctor);

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
