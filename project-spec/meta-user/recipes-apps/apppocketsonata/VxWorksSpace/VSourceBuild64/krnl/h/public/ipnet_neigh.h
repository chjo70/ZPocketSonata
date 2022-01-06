/*
 * Copyright (c) 2006-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* modification history
-------------------------
24apr14,h_x Remove secure NDP and CGA US35689
*/

#ifndef IPNET_NEIGH_H
#define IPNET_NEIGH_H

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
 * Maximum link layer address length the stack can handle
 */
#define IPNET_NEIGH_MAX_LINK_ADDR_LEN 8

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_type.h>
#include <ipcom_cstyle.h>
#include <ipcom_netlink.h>

#include <ipnet.h>
#include "ipcom_observer.h"
#include "ipnet_route.h"
#include "ipnet_signal.h"
#include "ipnet_timeout.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 * Extracts the destination cache used to transmit the packet.
 */
#define IPNET_NEIGH_DST_FROM_PKT(pkt) ((Ipnet_dst_cache *) (pkt)->link_cookie)

#ifdef IPCOM_FORWARDER_NAE
struct Ipnet_neigh_struct;
#define ipnet_neigh_route_cache(n)      ipnet_neigh_forwarder_route_cache_update((n), ipnet->route_cache_id)
#define ipnet_neigh_is_route_cache(n)   (ipnet_neigh_is_complete(n) && ((n)->nae_route_cache_id == ipnet->route_cache_id))
#else
#define ipnet_neigh_route_cache(n)      (void)0
#define ipnet_neigh_is_route_cache(n)   (ipnet_neigh_is_complete(n))
#endif


#define IPNET_NEIGH_AF_LINK             (0x80000000)
#define IPNET_NEIGH_AF_LINK_SET(family)   (IPNET_NEIGH_AF_LINK|(family))
#define IPNET_NEIGH_AF_LINK_CLR(family)   ((family) & ~IPNET_NEIGH_AF_LINK)
#define IPNET_NEIGH_AF_LINK_ISSET(family) IP_BIT_ISSET((family),IPNET_NEIGH_AF_LINK)

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* Forward declarations */
struct Ipnet_data_struct;
struct Ipnet_neigh_struct;
struct Ipnet_netif_struct;

/*
 *===========================================================================
 *                       neighbor entry states
 *===========================================================================
 */

/*
 *===========================================================================
 *                      Ipnet_neigh_probecb
 *===========================================================================
 * Description: Callback that will send neighbor solicitation
 *              probe. This function must be implemented by every network
 *              interface type that supports IPv4 and must be accessable
 *              via the "ip4_neigh_probe" member of the Ipnet_netif
 *              instance for the interface.
 *              There is no equivalent for IPv6 since this
 *              operation is performed by the ICMPv6 protocol.
 * Parameters:  neigh - neighbor entry to send probe for.
 *              unicast_probe - IP_TRUE = send unicast probe
 *                              IP_FALSE = send multicast/broadcast probe
 * Returns:
 *
 */
typedef void (*Ipnet_neigh_probecb) (struct Ipnet_neigh_struct *neigh,
                                     Ip_bool unicast_probe);


/*
 *===========================================================================
 *                    Ipnet_neigh_foreach_func
 *===========================================================================
 * Description: Function that will be run for every neighbor in the
 *              neighbor cache.
 * Parameters:  neigh - a neighbor entry
 *              user_data - user defined data passed to ipnet_neigh_foreach()
 * Returns:
 *
 */
typedef void (*Ipnet_neigh_foreach_func)(struct Ipnet_neigh_struct *neigh,
                                         void *user_data);


/*
 *===========================================================================
 *                    Ipnet_neigh_tx
 *===========================================================================
 * Description: Handles transmission of an IPv4 or IPv6 packet.
 * Parameters:  neigh - neighbor entry to send probe for.
 *              pkt - packet to transmit, must not contain a link header yet.
 * Returns:
 *
 */
typedef int (*Ipnet_neigh_tx) (struct Ipnet_neigh_struct *neigh,
                               Ipcom_pkt *pkt);

/*
 *===========================================================================
 *                    Ipnet_neigh_dropcb
 *===========================================================================
 * Description: Function that will be called if a packet has to be dropped.
 * Parameters:  pkt - A packet in the pending list.
 * Returns:
 *
 */
typedef void (*Ipnet_neigh_dropcb) (struct Ipcom_pkt_struct *pkt);


/*
 *===========================================================================
 *                    Ipnet_neigh_free_data
 *===========================================================================
 * Description: Free neigh data associated with this neigh entry
 * Parameters:  neigh - neighbor entry to send probe for.
 * Returns:
 *
 */
typedef void (*Ipnet_neigh_free_data) (struct Ipnet_neigh_struct *neigh);


/*
 * Kind of change that just occurred on the neighbor
 */
enum Ipnet_neigh_observer_hint {
    IPNET_NEIGH_NEW_STATE
};

/*
 *===========================================================================
 *                  Ipnet_neigh_observer_action
 *===========================================================================
 * Description: This function will be called each time the state changes
 *              on a neighbor
 * Parameters:  neigh - the neighbor being observed
 *              ctx - user defined context specific data
 * Returns:
 *
 */
typedef void (*Ipnet_neigh_observer_action) (struct Ipnet_neigh_struct *neigh,
                                             const enum Ipnet_neigh_observer_hint *hint,
                                             void *observer_ctx);


/*
 * Used by ARP and NDP to store packets that are waiting for IP
 * to link layer address resolution
 */
typedef struct Ipnet_neigh_res_wait_list_struct
{
    Ip_u8               max;      /* Maximum number of packets that can be waiting for
                                     IP to link address resoution */
    Ip_u8               num;      /* Number of packets that are waiting for IP to link
                                     address resoution */
    Ip_u8               linger;   /* IP_TRUE if this ND should linger after failure */
    Ipcom_pkt          *pkt_list; /* Packet to send when status -> IPNET_ND_REACHABLE */
    Ipnet_neigh_dropcb  dropcb;   /* Function to call if a packet must be dropped */
} Ipnet_neigh_res_wait_list;


enum Ipnet_neigh_create {
    /* May only return an existing entry */
    IPNET_NEIGH_NO_CREATE,

    /* Can create a new entry without doing santiy checks first */
    IPNET_NEIGH_CAN_CREATE_NO_CHECK,

    /* Can create a new entry if it passes sanity checks */
    IPNET_NEIGH_CAN_CREATE,

    /* Can create, and allow creation of singleton discard neighbor
       entry if a good route cannot be found. */
    IPNET_NEIGH_CAN_CREATE_ALLOW_DISCARD
};


union Ipnet_neigh_key_union
{
    struct Ip_in_addr    in;
#ifdef IPCOM_USE_INET6
    struct Ip_in6_addr   in6;
#endif
    Ip_u8                lladdr[IPNET_NEIGH_MAX_LINK_ADDR_LEN];
    Ip_u32               key;
};

/*
 * IPNET_NEIGH_KEY_UNION_SIZE is defined in ipnet_signal.h without
 * including this header.  Check at compile time that it is defined correctly.
 */
enum _check_neigh_key_union_size
{
    neigh_key_union_size_ok = 1 / (sizeof (union Ipnet_neigh_key_union) ==
                                   IPNET_NEIGH_KEY_UNION_SIZE)
};

/*
 *===========================================================================
 *                         Ipnet_neigh
 *===========================================================================
 * Neighbor cache entry
 */
typedef struct Ipnet_neigh_struct
{
    /*
     * Address domain for this entry.
     */
    int                domain;
    int                key_domain;

    /*
     * State of this neighbor entry
     */
    Ipnet_nd_state_t   state;

    /*
     * IP_ATF_xxx or:ed together.
     */
    Ip_u32             flags;

#ifdef IPCOM_FORWARDER_NAE
    /*
     * Route Cache ID for this neighbour. Does it have
     * any DST CACHE entries that were created with
     * this routing ID.
     */
    int                             nae_route_cache_id;
    int                             nae_fw_ix;
    Ip_u8                           nae_refresh;

    /**/
    Ip_u8                           __nae_unused1;
    Ip_u16                          __nae_unused2;
#endif

    /*
     * Function that knows how to transmit a packet to this
     * neighbor. This is the function that is actually used.
     */
    Ipnet_neigh_tx     tx;

    /*
     * Will always be equal to 'tx' unless the interface has a non
     * IP_NULL 'neigh_tx' function. 'tx' will then always be equal to
     * 'neigh_tx', but 'tx_action' will still be the neighbor state
     * specific function. A custom neighbor handler might want take
     * care of part of the neighbor handling and then leave the final
     * part to the generic implementation, 'tx_action' can be used in
     * those cases to call the generic path.
     */
    Ipnet_neigh_tx     tx_action;

    /*
     * The stack instance this neighbor belongs to
     */
    struct Ipnet_data_struct *net;

    /*
     * The interface associated with this neighbor
     */
    struct Ipnet_netif_struct *netif;

    /*
     * IPv4/IPv6 address of for this neighbor
     */
    union Ipnet_neigh_key_union addr;

    /*
     * The link layer address for this neighbor
     */
    Ip_u8              lladdr[IPNET_NEIGH_MAX_LINK_ADDR_LEN];

    /*
     * Timer for this neighbor, != IP_NULL if timer is currently
     * running
     */
    Ipnet_timeout     *tmo;

    /*
     * Number of remaining unicast probes to be done, unless an answer
     * is received
     */
    Ip_s8              remaining_ucast_probes;

    /*
     * Number of remaining multicast (broadcast on IPv4) probes to be
     * done, unless an answer is received
     */
    Ip_s8              remaining_mcast_probes;

    /*
     * Number of remaining probes to be done, unless an answer is
     * received
     */
    Ip_s8              remaining_app_probes;

    /*
     * Is set to IP_TRUE if the upper layer is seeing forward
     * progress in a session using this neighbor.
     */
    Ip_u8              is_making_forward_progress;

    /*
     * List of packets waiting for this nighbor entry to be resolved
     */
    Ipnet_neigh_res_wait_list pending;

    /*
     * Number of referecens to this entry
     */
    unsigned           refcnt;

    /*
     * Collection of observers that want to get notified about changes
     * to this neighbor.
     */
    Ipcom_observer_collection observers;

    /*
     * Used for deferred operations like initiate probing and cleanup
     * of dead entries.
     */
    Ipnet_softirq      softirq;

 #ifdef IPCOM_USE_INET6
    /*
     * Does this entry correspond to a router or host
     */
    Ip_bool            is_router;
#endif /* IPCOM_USE_INET6 */

#ifdef IPCOM_STORE_PHYSICAL_IF
    Ip_u32             physical_ifindex;
#endif

    /* */
    void                   *neigh_data;
    Ipnet_neigh_free_data   neigh_data_free;
#ifdef IPCOM_USE_MIB2_NEW
    Ip_u32                  lastchange;
#endif
}
Ipnet_neigh;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/*
 * Transmits a packet to the destination represented by the 'dst' entry.
 */
IP_INLINE int
ipnet_neigh_tx(Ipnet_neigh *neigh, Ipnet_dst_cache *dst, Ipcom_pkt *pkt)
{
    ipnet_neigh_route_cache(neigh);
    pkt->link_cookie = (Ip_ptrdiff_t) dst;
    neigh->is_making_forward_progress = (Ip_u8)
      (neigh->is_making_forward_progress |
       IP_BIT_ISTRUE(pkt->flags, IPCOM_PKT_FLAG_PROGRESS));
    return neigh->tx(neigh, pkt);
}


IP_INLINE Ip_size_t
ipnet_neigh_keylen(int domain)
{
    IPCOM_UNUSED_ARG(domain);

    if (IPNET_NEIGH_AF_LINK_ISSET((unsigned)domain))
        return IPNET_NEIGH_MAX_LINK_ADDR_LEN;

#ifdef IPCOM_USE_INET6
    if (domain == IP_AF_INET6)
        return sizeof(struct Ip_in6_addr);
#endif

    return sizeof(struct Ip_in_addr);
}


IP_GLOBAL Ipnet_neigh *
ipnet_neigh_get(int domain,
                IP_CONST void *addr, /* struct Ip_in_addr or struct
                                        Ip_in6_addr */
                struct Ipnet_netif_struct *netif,
                enum Ipnet_neigh_create create);

IP_GLOBAL void
ipnet_neigh_release(Ipnet_neigh *neigh);

IP_GLOBAL void
ipnet_neigh_set_state(Ipnet_neigh *neigh, Ipnet_nd_state_t new_state);

IP_GLOBAL void
ipnet_neigh_set_lladdr(Ipnet_neigh *neigh, IP_CONST void *link_addr);

IP_INLINE void
ipnet_neigh_observer_add(Ipnet_neigh *neigh,
                         Ipcom_observer *observer,
                         void *addr_entry,
                         Ipnet_neigh_observer_action action)
{
    ipcom_observer_add(&neigh->observers,
                       observer,
                       addr_entry,
                       (Ipcom_observer_action)action);
}

IP_GLOBAL void
ipnet_neigh_probe(Ipnet_neigh *neigh, Ip_bool unicast_probe);

IP_GLOBAL void
ipnet_neigh_dad(Ipnet_neigh *neigh);

IP_INLINE Ip_bool
ipnet_neigh_is_blackhole(const Ipnet_neigh *neigh)
{
    return IP_BIT_ISSET(neigh->flags, IP_ATF_BLACKHOLE);
}

IP_GLOBAL void
ipnet_neigh_set_blackhole(Ipnet_neigh *neigh, Ip_bool on);

IP_INLINE Ip_bool
ipnet_neigh_is_complete(const Ipnet_neigh *neigh)
{
    return IP_BIT_ISSET(neigh->flags, IP_ATF_COM);
}

IP_INLINE Ip_bool
ipnet_neigh_is_perm(const Ipnet_neigh *neigh)
{
    return IP_BIT_ISSET(neigh->flags, IP_ATF_PERM);
}

IP_INLINE Ip_bool
ipnet_neigh_is_gateway(const Ipnet_neigh *neigh)
{
    return IP_BIT_ISSET(neigh->flags, IP_ATF_GATEWAY);
}

IP_INLINE Ip_bool
ipnet_neigh_is_external(const Ipnet_neigh *neigh)
{
    return IP_BIT_ISSET(neigh->flags, IP_ATF_EXTERNAL);
}

IP_GLOBAL void
ipnet_neigh_set_perm(Ipnet_neigh *neigh, Ip_bool on);

IP_INLINE Ip_bool
ipnet_neigh_is_publ(const Ipnet_neigh *neigh)
{
    return IP_BIT_ISSET(neigh->flags, IP_ATF_PUBL);
}

IP_INLINE Ip_bool
ipnet_neigh_is_silent(const Ipnet_neigh *neigh)
{
    return IP_BIT_ISSET(neigh->flags, IP_ATF_SILENT);
}

IP_GLOBAL void
ipnet_neigh_set_lifetime(Ipnet_neigh *neigh, Ip_u32 msec);

IP_GLOBAL void
ipnet_neigh_set_publ(Ipnet_neigh *neigh, Ip_bool on);

IP_GLOBAL Ip_bool
ipnet_neigh_is_probing(Ipnet_neigh *neigh);

IP_GLOBAL void
ipnet_neigh_set_silent(Ipnet_neigh *neigh);

IP_GLOBAL void
ipnet_neigh_set_report(Ipnet_neigh *neigh);

IP_GLOBAL void
ipnet_neigh_set_gateway(Ipnet_neigh *neigh);

IP_GLOBAL void
ipnet_neigh_set_local(Ipnet_neigh *neigh);

IP_GLOBAL void
ipnet_neigh_set_external(Ipnet_neigh *neigh);

IP_GLOBAL void
ipnet_neigh_flush(int domain,
                  struct Ipnet_netif_struct *netif,
                  void *addr,
                  void *mask);

IP_GLOBAL void
ipnet_neigh_flush_all(int domain,
                      struct Ipnet_netif_struct *netif,
                      void *addr,
                      void *mask);

IP_GLOBAL void
ipnet_neigh_foreach(struct Ipnet_data_struct *net,
                    Ipnet_neigh_foreach_func foreach_func,
                    void *user_data);

IP_GLOBAL struct Ipnet_netif_struct *ipnet_neigh_netif_discard(void);

IP_GLOBAL int
ipnet_neigh_init_addr_observer(int family,
                               void *addr_entry,
                               IP_CONST void *addr,
                               struct Ipnet_netif_struct *netif,
                               Ipnet_neigh **pneigh,
                               Ipcom_observer *neigh_observer,
                               Ipnet_neigh_observer_action action);

IP_GLOBAL void ipnet_neigh_invalidate(Ipnet_neigh *neigh);

IP_GLOBAL void ipnet_neigh_sig_resolve(Ipnet_sig *sig);
IP_GLOBAL void ipnet_neigh_sig_update(struct Ipnet_data_struct *net, Ipnet_sig *sig);

IP_GLOBAL int ipnet_neigh_init(struct Ipnet_data_struct *net);

#ifdef IPCOM_FORWARDER_NAE
IP_GLOBAL void ipnet_neigh_forwarder_route_cache_update(Ipnet_neigh *neigh, int value);
IP_GLOBAL void ipnet_neigh_forwarder_update(Ipnet_neigh *neigh, Ip_u32 fw_ix);
IP_GLOBAL Ip_bool ipnet_neigh_nae_verify_use(Ipnet_neigh *neigh, Ip_u8 fail_state);
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
