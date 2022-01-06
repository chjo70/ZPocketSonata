/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef IPNET_NETLINK_H
#define IPNET_NETLINK_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * This is the header file for the Linux compatible NETLINK interface
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
#include <ipcom_netlink.h>
#include "ipnet_route.h"

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

struct Ipnet_netif_struct;
struct Ip_rtattr;

/*
 *===========================================================================
 *                         Ipnet_netlink_callback
 *===========================================================================
 */
struct Ipnet_netlink_callback
{
    Ip_u8               *buf;
	struct Ip_nlmsghdr  *nlh;
	int		     (*dump)(Ip_u8 *buf, Ip_size_t len, struct Ipnet_netlink_callback *cb);
	int		     (*done)(struct Ipnet_netlink_callback *cb);
	int		     family;
	Ip_ptrdiff_t args[4];
};


typedef struct Ipnet_netlink_mem
{
    /* Pointer to start of data */
    char        *ptr;

    /* Total size */
    Ip_size_t   size;

    /* Working offset */
    Ip_size_t   offset;

    /* Current used size */
    Ip_size_t   used;

    /* Ancillary data */
    Ip_pid_t    pid;
    Ip_u16       vr;

} Ipnet_netlink_mem_t;


/**/
typedef int (*Ipnet_netlink_dump_t) (Ipnet_netlink_mem_t *mem,
                                     struct Ip_nlmsghdr *nlmsg,
                                     int                 family,
                                     Ip_ptrdiff_t        *args);


/*
 ****************************************************************************
 * 6                    PROTOTYPES
 ****************************************************************************
 */

IP_GLOBAL int ipnet_netlink_parse(Ip_size_t           maxattr,
                                  struct Ip_rtattr    *atttr,
                                  Ip_size_t           attrlen,
                                  struct Ip_rtattr    ***rtap);

#ifdef IP_PORT_LKM
IP_PUBLIC void
ipcom_netlink_post(Ipcom_pkt *pkt, int msg_group);
#endif /* IP_PORT_LKM */

#ifdef __cplusplus
}
#endif

#endif	/* IPNET_NETLINK_H */


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

