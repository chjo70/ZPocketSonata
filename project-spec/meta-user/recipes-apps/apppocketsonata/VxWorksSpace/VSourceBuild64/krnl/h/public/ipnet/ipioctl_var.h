/* ipioctl_var.h - IP ioctl variable header file */

/*
 * Copyright (c) 2007 Wind River Systems, Inc.
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
01c,12jul07,kch  Moved sioc_vif_req and sioc_sg_req struct to ip_mroute.h.
                 Also moved sioc_sg_req6 and sioc_mif_req6 struct to
                 ip6_mroute.h (WIND00102340).
01b,24apr07,tkf  Add IPv6-Only build support.
01a,30nov06,kch  Created.
*/

#ifndef __INCipioctl_varh
#define	__INCipioctl_varh

/* includes */
#include <net/if.h>
#ifdef INET
#include <netinet/in.h>
#endif
#ifdef INET6
#include <netinet6/in6.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*if_eventcb)(char *ifname, u_int32_t ifindex, u_int32_t ifflags,
                          int event, void *data);

/* The maximum length of route table name */
#define RTNAMSIZ        16

/* This VR ID tells the stack to choose an unused ID and also choose the
   default route table ID */
#define VR_ANY               0xffff

/* This table ID tells the stack to choose an unused ID on the specified VR */
#define ROUTE_TABLE_ANY      0xffffffff

/*
 * Structure used by SIOCADDROUTETAB, SIOCDELROUTETAB, SIOCGETROUTETAB,
 * SIOCSROUTETABNAME and SIOCGROUTETABNAME for manipulating route tables
 * for an existing (virtual) router.
 */
struct sioc_route_table {

    /* (Virtual) router index, 0 == default, VR_ANY can be used to let the
     * stack choose a virtual router ID
     */
    u_int16_t   vr;

    /* The ID of this table. Table 0 is always present and cannot be deleted.
     * Setting table to ROUTE_TABLE_ANY in an add operation will result in
     * the stack choosing a free ID
     */
    u_int32_t   table;
    char     name[RTNAMSIZ]; /* The (optional) name of the route table */
};

union sockaddr_union
{
    struct sockaddr         sa;
#ifdef INET
    struct sockaddr_in      sin;
#endif /* INET */
#ifdef INET6
    struct sockaddr_in6     sin6;
#endif /* INET6 */
};

/*
 * Tunnel parameter struct used with SIOCGETTUNNEL and SIOCCHGTUNNEL ioctls.
 */
struct ip_tunnel_param
{
    char    ifr_name[IFNAMSIZ];   /* if name, e.g. "gif1", "gre1" */

     /* The address to use as source address for outgoing packets, must
      * be the address of a local interface
      */
    union sockaddr_union   local_addr;

    /* The address to use as destination address for outgoing packets */
    union sockaddr_union   remote_addr;

    u_int8_t   ttl;        /* Value to put in time to live field */

    /* These fields are read only (returned by IP_SIOCGETTUNNEL) */
    /* Tunnel protocol: IP_IPPROTO_IPIP or IP_IPPROTO_GRE. */
    u_int8_t   protocol;

    u_int16_t  o_flags;    /* Output flags (tunnel protocol specific). */
    u_int16_t  i_flags;    /* Input flags (tunnel protocol specific). */
};

#ifdef INET6
/*
 * used when communicating with the MIP6 subsystem
 */
struct mip6
{
    u_int32_t  pad[40];     /* Large enough to deal with the MIP stuff */
};
#endif /* INET6 */

#ifdef __cplusplus
}
#endif

#endif /* __INCipioctl_varh */
