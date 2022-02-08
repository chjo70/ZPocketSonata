/*
 * Copyright (c) 2006-2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPNET_PEER_INFO_H
#define IPNET_PEER_INFO_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 *
 * Peer information is data that has to be kept between packet
 * transmissions/receptions to/from a specific IP node. The only
 * information required right now are the next fragmentation ID (TX)
 * and the fragmentation reassembly queue (RX).
 *
 * Note that peer information entries are shared by all CPU cores
 * used for network acceleration (only applies when running in the
 * stack as a NAE (Network Acceleration Engine) in an AMP system).
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

#include <ipcom_atomic.h>
#include <ipcom_cstyle.h>
#include <ipcom_list.h>
#include <ipcom_pkt.h>
#include <ipcom_sock.h>
#include <ipcom_type.h>

#include "ipnet_timeout.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */
#define IPNET_PEER_INFO_ID_CNT          128

#define IPNET_PEER_INFO_ATOMIC_FLAGS

#ifdef IPNET_PEER_INFO_ATOMIC_FLAGS

#define IPNET_PEER_INFO_FLAG_CHECK_PMTU	(0x1)
#define IPNET_PEER_INFO_FLAG_ZERO_PMTU  (0x2)

#define IPNET_PEER_INFO_CHECK_PMTU(pi)  \
  (ipcom_atomic_get(&(pi)->flags) & IPNET_PEER_INFO_FLAG_CHECK_PMTU)
#define IPNET_PEER_INFO_ZERO_PMTU(pi)  \
  (ipcom_atomic_get(&(pi)->flags) & IPNET_PEER_INFO_FLAG_ZERO_PMTU)
#define IPNET_PEER_INFO_CHECK_PMTU_SET(pi) \
  do { ipcom_atomic_or(&(pi)->flags, IPNET_PEER_INFO_FLAG_CHECK_PMTU); } while ((0))
#define IPNET_PEER_INFO_ZERO_PMTU_SET(pi) \
  do { ipcom_atomic_or(&(pi)->flags, IPNET_PEER_INFO_FLAG_ZERO_PMTU); } while ((0))
#define IPNET_PEER_INFO_FLAGS_CLEAR(pi) \
  do { ipcom_atomic_set(&(pi)->flags, 0); } while ((0))

#else

#define IPNET_PEER_INFO_CHECK_PMTU(pi)  ((pi)->check_pmtu)
#define IPNET_PEER_INFO_ZERO_PMTU(pi)   ((pi)->zero_mtu)
#define IPNET_PEER_INFO_CHECK_PMTU_SET(pi) do { (pi)->check_pmtu = 1; } while ((0))
#define IPNET_PEER_INFO_ZERO_PMTU_SET(pi)  do { (pi)->zero_pmtu = 1; } while ((0))
#define IPNET_PEER_INFO_FLAGS_CLEAR(pi) \
  do { (pi)->check_pmtu = 0; (pi)->zero_pmtu = 0; } while ((0))


#endif /* IPNET_PEER_INFO_ATOMIC_FLAGS */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

struct Ipnet_data_struct;

/*
 * Long living information about a peer node. These entries does not
 * have their own timer that controls their lifetime. Their lifetime
 * are bound by the lifetime of the destination cache entries using
 * them.
 */
typedef struct Ipnet_peer_info_struct
{
    /* List of peer information entries that hash to the same bucket */
    Ipcom_list             list;

    /*
     * Number of references to this entry. Will be deleted when it
     * reaches 0. Doesn't have to be an atomic variable since this
     * value is only accessed/modified with a critical region
     */
    int                    refcnt;

    /* Virtual router index */
    Ip_u16                 vr;

    /*
     * Low order 15 bits: hash bucket index.
     * High order bit: a timeout is scheduled if set.
     */
    Ip_u16                 idx_tmr;
#define IPNET_PEER_INFO_IDXTMR_HINDEX_BITS  (0x7fff)
#define IPNET_PEER_INFO_IDXTMR_TMRSCHED_BIT (0x8000)

    /* Either IP_AF_INET or IP_AF_INET6 */
    int                    domain;

    /* Address of the peer node */
    union Ip_in_addr_union addr;

#ifdef IPNET_PEER_INFO_ATOMIC_FLAGS

    Ipcom_atomic_t         flags;

#else
    /*
     * Packets sent to this host has generated at least one ICMP need
     * frag / ICMPv6 too big response.
     */
    unsigned               check_pmtu:1;

    /*
     * RFC 1191, p7:
     *   The simplest thing for a host to do in response to such a
     *   message is to assume that the PMTU is the minimum of its
     *   currently-assumed PMTU and 576, and to stop setting the DF
     *   bit in datagrams sent on that path.
     */
    unsigned               zero_pmtu:1;
#endif

    /* Next fragmentation ID that */
    Ipcom_atomic_t         id;

    /* IDs for different combination of {ip-source-address, ip-protocol}  */
    Ipcom_atomic_t         ids[IPNET_PEER_INFO_ID_CNT];

    /*
     * Number of ICMPv4/ICMPv6 messages that can be sent before
     * throttled
     */
    Ip_u32 icmp_send_limit;
    /*
     * Timeout that will reseed the 'icmp_send_limit' counter
     */
    struct Ipnet_timeout_struct *icmp_send_limit_tmo;


    /*
     * Fragmentation reassembly list, the list is sorted on the order
     * the first fragment was received. Oldest fragmentation (oldest
     * first)
     */
    Ipcom_pkt             *reassembly_list;
} Ipnet_peer_info;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

IP_INLINE Ip_bool
ipnet_peer_info_timer_scheduled(Ipnet_peer_info *peer_info)
{
    return (0 != (peer_info->idx_tmr & IPNET_PEER_INFO_IDXTMR_TMRSCHED_BIT));
}


IP_INLINE void
ipnet_peer_info_set_timer_scheduled(Ipnet_peer_info *peer_info, Ip_bool set)
{
    if (set)
        peer_info->idx_tmr = (Ip_u16)(peer_info->idx_tmr |
                                      IPNET_PEER_INFO_IDXTMR_TMRSCHED_BIT);
    else
        peer_info->idx_tmr = (Ip_u16)(peer_info->idx_tmr &
                                      ~IPNET_PEER_INFO_IDXTMR_TMRSCHED_BIT);
}

IP_INLINE Ip_u16
ipnet_peer_info_hash_idx(Ipnet_peer_info *peer_info)
{
    return (Ip_u16)(peer_info->idx_tmr & IPNET_PEER_INFO_IDXTMR_HINDEX_BITS);
}

IP_GLOBAL Ipnet_peer_info *
ipnet_peer_info_get(Ip_u16 vr, int domain, const void *addr);

IP_GLOBAL void
ipnet_peer_info_addref(Ipnet_peer_info *peer_info);

IP_GLOBAL void
ipnet_peer_info_release(Ipnet_peer_info *peer_info);

IP_GLOBAL int
ipnet_peer_info_init(void);

IP_GLOBAL void
ipnet_peer_info_timeout_schedule(struct Ipnet_data_struct *net,
                                 Ipnet_peer_info *peer_info,
                                 Ip_s64 msec);
IP_GLOBAL void
ipnet_peer_info_lock(Ipnet_peer_info *peer_info);

IP_GLOBAL void
ipnet_peer_info_unlock(Ipnet_peer_info *peer_info);

#if defined(IPCOM_FORWARDER_NAE)
IP_GLOBAL void
ipnet_peer_info_timeout_process(void);
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
