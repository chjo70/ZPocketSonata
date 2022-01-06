/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_DRV_ETH_FILTER_H
#define IPCOM_DRV_ETH_FILTER_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */
/* Functions for filtering Ethernet unicast and multicast addresses that the
   local not is not listening on.
   The functions here should only be used by targets where the hardware
   filtering for Ethernet multicast is broken or not not implemented.
   The Ethernet chip must be placed in promiscuous mode when this
   using this module.
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

#include <ipcom_cstyle.h>
#include <ipcom_hash.h>
#include <ipcom_sock.h>
#include <ipcom_type.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#define IPCOM_DRV_ETH_ADDR_SIZE  6

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         Ipcom_eth_hdr
 *===========================================================================
 */

/* Ethernet header */
typedef struct Ipcom_eth_hdr_struct
{
    Ip_u8     dst[IPCOM_DRV_ETH_ADDR_SIZE]; /* Destination address of the frame */
    Ip_u8     src[IPCOM_DRV_ETH_ADDR_SIZE]; /* Source address of the fram */
    Ip_u16    type;                         /* Ethernet frame type */
    Ip_u8     data[1];
}
Ipcom_eth_hdr;


/* Filter structure */
typedef struct Ipcom_drv_eth_filter_struct
{
    /* Collection of Ethernet addresses that should be allowed to pass
       through this filter */
    Ipcom_hash *addr_memberships;

#ifndef IP_PORT_VXWORKS
    /* The unicast address that should be accepted */
    Ip_u8   unicast_addr[IPCOM_DRV_ETH_ADDR_SIZE];

    /* Number of clients that has set this filter in promiscuous mode
     * or 0 if not in promiscuous mode */

#ifdef IPCOM_USE_INET
    /* Specific IPv4 address to block. This is required on some OS:es
       (like Solaris) to drop all packets that should be delivered to
       the host OS. */
    struct Ip_in_addr  in_block_addr;    /* IPv4 address to block. */
#endif
    /* Promiscuous status. All frames will be accepted if this filed
       is !=0 */
    int     promisc;
#endif /* IP_PORT_VXWORKS */
}
Ipcom_drv_eth_filter;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

IP_PUBLIC void
ipcom_drv_eth_filter_init(Ipcom_drv_eth_filter *filter);

IP_PUBLIC void
ipcom_drv_eth_filter_exit(Ipcom_drv_eth_filter *filter);

IP_PUBLIC Ip_bool
ipcom_drv_eth_filter_pkt_to_me(Ipcom_drv_eth_filter *filter,
                               Ipcom_eth_hdr *frame);

IP_PUBLIC void
ipcom_drv_eth_filter_set_unicast_addr(Ipcom_drv_eth_filter *filter,
                                      Ip_u8 eth_unicast_addr[IPCOM_DRV_ETH_ADDR_SIZE]);

IP_PUBLIC int
ipcom_drv_eth_filter_add_mcast_addr(Ipcom_drv_eth_filter *filter,
                                    Ip_u8 eth_mcast_addr[IPCOM_DRV_ETH_ADDR_SIZE]);

IP_PUBLIC int
ipcom_drv_eth_filter_remove_mcast_addr(Ipcom_drv_eth_filter *filter,
                                       Ip_u8 eth_mcast_addr[IPCOM_DRV_ETH_ADDR_SIZE]);

IP_PUBLIC Ip_bool
ipcom_drv_eth_filter_is_promiscuous(Ipcom_drv_eth_filter *filter);

IP_PUBLIC void
ipcom_drv_eth_filter_set_promiscuous(Ipcom_drv_eth_filter *filter);

IP_PUBLIC void
ipcom_drv_eth_filter_clr_promiscuous(Ipcom_drv_eth_filter *filter);

IP_PUBLIC void
ipcom_drv_eth_filter_block_inet_addr(Ipcom_drv_eth_filter *filter,
                                     struct Ip_in_addr *addr);

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
