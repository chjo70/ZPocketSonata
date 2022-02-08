/* IPNET socket ioctl header file */

/*
 * Copyright (c) 2016 Wind River Systems, Inc.
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
# 29Dec16,ghl  change SIOCXGIFADDR_IN6 to readable (V7NET-1149)
# 06Sep16,rjq  add shareh in coreip/utils.
*/

#ifndef __INCipioctlh
#define __INCipioctlh

#ifdef __cplusplus
extern "C" {
#endif

/* IOCTL types: */
#define VX_IOC_VOID  0x20000000
#define VX_IOC_OUT   0x40000000
#define VX_IOC_IN    0x80000000
#define VX_IOC_INOUT (VX_IOC_IN | VX_IOC_OUT)
#define VX_IOC_READ(a) (((0x40 << 24) & (a)) == VX_IOC_OUT)
#define VX_IOC_WRITE(a) (((0x80 << 24) & (a)) == VX_IOC_IN)
#define VX_IOC_RW(a) (((0xc0 << 24) & (a)) == VX_IOC_INOUT)

/* IOCTL size: */
#define VX_IOCPARM_MASK    0x1fff      /* Parameter length 13 bits */
#define VX_IOCPARM_LEN(r)  (VX_IOCPARM_MASK & ((r) >> 16))

/* IOCTL flags. */
#define VX_IOCF_R       0x00000000   /* read. */
#define VX_IOCF_W       0x00001000   /* write bit. */

/* IOCTL groups: */
#define VX_IOC_GROUP(c)  (((c) & 0x00000f00) >> 8)
#define VX_IOCG_BASE        1
#define VX_IOCG_SOCK        2
#define VX_IOCG_NETIF       3
#define VX_IOCG_ARP         4
#define VX_IOCG_INET        5
#define VX_IOCG_INET6       6
#define VX_IOCG_ETH         7
#define VX_IOCG_PPP         8
#define VX_IOCG_WLAN        9
#define VX_IOCG_MCAST       10
#define VX_IOCG_MCAST_IN6   11
#define VX_IOCG_RTAB        13
#define VX_IOCG_DS          14
#define VX_IOCG_POLICY_RT   15

#define VX_IOX(g,i,f,t)   (((sizeof(t) & VX_IOCPARM_MASK) << 16) | (VX_IOCF_ ## f) | ((VX_IOCG_ ## g) << 8) | (i & 0xff))

#define VX_IO(g,i,f,t)    (VX_IOC_VOID  | /* no parameter */ \
        (((sizeof(t) & VX_IOCPARM_MASK) << 16) | (VX_IOCF_ ## f) | ((VX_IOCG_ ## g) << 8) | (i & 0xff)))

#define VX_IOR(g,i,f,t)   (VX_IOC_OUT   | /* out-parameter */ \
        (((sizeof(t) & VX_IOCPARM_MASK) << 16) | (VX_IOCF_ ## f) | ((VX_IOCG_ ## g) << 8) | (i & 0xff)))

#define VX_IOW(g,i,f,t)   (VX_IOC_IN    | /* in-parameter */ \
        (((sizeof(t) & VX_IOCPARM_MASK) << 16) | (VX_IOCF_ ## f) | ((VX_IOCG_ ## g) << 8) | (i & 0xff)))

#define VX_IOWR(g,i,f,t)  (VX_IOC_INOUT | /* in- and out-parameter */ \
        (((sizeof(t) & VX_IOCPARM_MASK) << 16) | (VX_IOCF_ ## f) | ((VX_IOCG_ ## g) << 8) | (i & 0xff)))

/* SOCK ioctls (others elsewhere, e.g. sys/ioctl.h): */
#define SIOCSNDASYNC     VX_IOW(SOCK, 15, W, int)

/* AF_INET ioctls: */
/* Get interface primary address. */
#define SIOCGIFADDR      VX_IOWR(INET,  1, R, struct ifreq)

/* Set interface primary address. */
#define SIOCSIFADDR      VX_IOWR(INET,  2, W, struct ifreq)

/* Get broadcast address. */
#define SIOCGIFBRDADDR   VX_IOWR(INET,  3, R, struct ifreq)

/* Set broadcast address. */
#define SIOCSIFBRDADDR   VX_IOWR(INET,  4, W, struct ifreq)

/* Get (sub)net address mask. */
#define SIOCGIFNETMASK   VX_IOWR(INET,  5, R, struct ifreq)

/* Set (sub)net address mask. */
#define SIOCSIFNETMASK   VX_IOWR(INET,  6, W, struct ifreq)

/* Get point-to-point IPv4 address. */
#define SIOCGIFDSTADDR   VX_IOWR(INET,  7, R, struct ifreq)

/* Set point-to-point IPv4 address. */
#define SIOCSIFDSTADDR   VX_IOWR(INET,  8, W, struct ifreq)

/* Add interface alias/address. */
#define SIOCAIFADDR      VX_IOWR(INET,  9, W, struct in_aliasreq)

/* Delete interface address. */
#define SIOCDIFADDR      VX_IOWR(INET, 10, W, struct ifreq)

/* Deprecated (BSD 4.3 compat): add route. */
#define SIOCADDRT        VX_IOWR(INET, 11, W, struct ortentry)

/* Deprecated (BSD 4.3 compat): remove route. */
#define SIOCDELRT        VX_IOWR(INET, 12, W, struct ortentry)

/* Proprietary (BSD 4.3 compat): get route. */
#define SIOCXGETRT       VX_IOWR(INET, 13, R, struct ortentry)

/* Proprietary AF_INET MIP ioctls */
/* Add a home address */
#define SIOCAHOMEADDR    VX_IOWR(INET,  14, W, struct in_aliasreq)

/* AF_INET6 ioctls: */
#ifdef INET6
/* Add interface IPv6 address */
#define SIOCAIFADDR_IN6    VX_IOWR(INET6, 1, W, struct in6_aliasreq)

/* Delete interface IPv6 address. */
#define SIOCDIFADDR_IN6    VX_IOWR(INET6, 2, W, struct in6_ifreq)

/* Get destination IPv6 address. */
#define SIOCGIFDSTADDR_IN6 VX_IOWR(INET6, 3, R, struct in6_ifreq)

/* proprietary AF_INET6 MIP6 ioctl */
#define SIOCMIP6           VX_IOWR(INET6, 4, W, struct mip6)  /* MIP6  */

/* Get interface IPv6 address prefix  */
#define SIOCGIFPREFIX_IN6  VX_IOWR(INET6, 5, R, struct in6_ifreq)

/* Get interface IPv6 address */
#define SIOCXGIFADDR_IN6   VX_IOWR(INET6, 6, R, struct in6_aliasreq)

/* Get inerface IPv6 address prefix  */
#define SIOCGIFPREFIX_IN6  VX_IOWR(INET6, 5, R, struct in6_ifreq)
#endif /* INET6 */

/* ARP ioctls: */
/* Create/modify ARP entry. */
#define SIOCSARP         VX_IOWR(ARP, 1, W, struct arpreq)

/* Get ARP entry. */
#define SIOCGARP         VX_IOWR(ARP, 2, R, struct arpreq)

/* Delete ARP entry */
#define SIOCDARP         VX_IOWR(ARP, 3, W, struct arpreq)

/* interface ioctls: */
/* Get interface flags. */
#define SIOCGIFFLAGS     VX_IOWR(NETIF,  1, R, struct ifreq)

/* Set interface flags. */
#define SIOCSIFFLAGS     VX_IOWR(NETIF,  2, W, struct ifreq)

/* Get interface MTU. */
#define SIOCGIFMTU       VX_IOWR(NETIF,  3, R, struct ifreq)

/* Set interface MTU. */
#define SIOCSIFMTU       VX_IOWR(NETIF,  4, W, struct ifreq)

/* Get link level address.  */
#define SIOCGIFLLADDR    VX_IOWR(NETIF, 13, R, struct ifreq)

/* Set link level address.  */
#define SIOCSIFLLADDR    VX_IOWR(NETIF, 14, W, struct ifreq)

/* Get interface list. */
#define SIOCGIFCONF      VX_IOWR(NETIF, 21, R, struct ifconf)

/* Get interface index */
#define SIOCGIFINDEX     VX_IOWR(NETIF, 22, R, struct ifreq)

/* Get interface capabilities */
#define SIOCGIFCAP       VX_IOWR(NETIF, 23, R, struct ifreq)

/* Get interface name */
#define SIOCGIFNAME       VX_IOWR(NETIF, 24, R, struct ifreq)

/* Get TX queue length */
#define SIOCGIFTXQLEN        VX_IOWR(NETIF, 25, R, struct ifreq)

/* Set TX queue length */
#define SIOCSIFTXQLEN        VX_IOWR(NETIF, 26, R, struct ifreq)

/* Set interface name */
#define SIOCSIFNAME          VX_IOWR(NETIF, 27, R, struct ifreq)

/* Set HW broadcast */
#define SIOCSIFHWBROADCAST   VX_IOWR(NETIF, 28, R, struct ifreq)

/* Add multicast address */
#define SIOCADDMULTI         VX_IOWR(NETIF, 29, W, struct sockaddr)

/* Delete multicast address */
#define SIOCDELMULTI         VX_IOWR(NETIF, 30, W, struct sockaddr)

/* Set interface hardware address */
#define SIOCGIFHWADDR        VX_IOWR(NETIF, 31, R, struct ifreq)

/* proprietary ioctls: */
/* Detach interface. */
#define SIOCXDETACH       VX_IOWR(NETIF, 50, W, struct ifreq)

/* Attach interface. */
#define SIOCXATTACH       VX_IOWR(NETIF, 51, W, struct ifreq)

/* Get DHCP status. */
#define SIOCXGDHCPRUNNING VX_IOWR(NETIF, 52, R, struct ifreq)

/* Enable(1)/Disable(0) DHCP. */
#define SIOCXSDHCPRUNNING VX_IOWR(NETIF, 53, W, struct ifreq)

/* Get private interface data */
#define SIOCGIFPRIVATE    VX_IOWR(NETIF, 54, R, struct ifreq)

/* Set private interface data */
#define SIOCSIFPRIVATE    VX_IOWR(NETIF, 55, W, struct ifreq)

/* Set interface callback. */
#define SIOCXSIFFEVENTCB  VX_IOW(BASE,   74, W, if_eventcb)

/* Delete interface callback. */
#define SIOCXDIFFEVENTCB  VX_IOW(BASE,   75, W, if_eventcb)

/* Pretend to be a TTY. */
#define SIOCBEATTY	  ((int)VX_IOW(BASE,   76, W, int))

#ifdef INET6
/* Proprietary : get IPv6 gateway. */
#define SIOCXGETGW_IN6    VX_IOWR(BASE,  53, R, struct sockaddr_in6)

/* Proprietaty : set IPv6 gateway. */
#define SIOCXSETGW_IN6    VX_IOWR(BASE,  54, W, struct sockaddr_in6)
#endif /* INET6 */

/* IPSEC ioctls */
#define SIOCXIPSEC_CTL       VX_IOWR(BASE, 55, W, void *)
#define SIOCXIPSEC_SA_CTL    VX_IOWR(BASE, 56, W, void *[2])
#define SIOCXIPSEC_CONF_CTL  VX_IOWR(BASE, 57, W, void *)

/* Multicast ioctls: */
/* get VIF statistics */
#define SIOCGETVIFCNT    VX_IOWR(MCAST,  0, R, struct sioc_vif_req)

/* get mcast route statistics */
#define SIOCGETSGCNT     VX_IOWR(MCAST,  1, R, struct sioc_sg_req)

#ifdef INET6
/* AF_INET6 multicast ioctls: */
/* get MIF statistics */
#define SIOCGETMIFCNT_IN6 VX_IOWR(MCAST_IN6,  0, R, struct sioc_mif_req6)

/* get mcast6 route statistics */
#define SIOCGETSGCNT_IN6  VX_IOWR(MCAST_IN6,  1, R, struct sioc_sg_req6)
#endif /* INET6 */

/* route table ioctls */
/* Add a new virtual router and creates a route table with table ID == 0 */
#define SIOCADDVR        VX_IOWR(RTAB, 0, W, u_int16_t)

/* Delete a virtual router and all tables owned by it */
#define SIOCDELVR        VX_IOWR(RTAB, 1, W, u_int16_t)

/* Add a route table to a (virtual) router */
#define SIOCADDROUTETAB  VX_IOWR(RTAB, 2, W, struct sioc_route_table)

/* Delete a route table to a (virtual) router */
#define SIOCDELROUTETAB  VX_IOWR(RTAB, 3, W, struct sioc_route_table)

/* Get/create a route table by name */
#define SIOCGETROUTETAB  VX_IOWR(RTAB, 4, W, struct sioc_route_table)

/* Set a name for a route table. */
#define SIOCSROUTETABNAME VX_IOWR(RTAB, 5, W, struct sioc_route_table)

/* Map a route table name to VR and table ID */
#define SIOCGROUTETABNAME VX_IOWR(RTAB, 6, R, struct sioc_route_table)

/* interface ioctls: */
/* Get interface metric. */
#define SIOCGIFMETRIC    VX_IOWR(NETIF,  5, R, struct ifreq)

/* Set interface metric. */
#define SIOCSIFMETRIC    VX_IOWR(NETIF,  6, W, struct ifreq)

/* Get the route table index for an interface. */
#define SIOCGIFVR        VX_IOWR(NETIF,  7, R, struct ifreq)

/* Set an interface to a specific route table. */
#define SIOCSIFVR        VX_IOWR(NETIF,  8, W, struct ifreq)

/* Get tunnel parameter. */
#define SIOCGETTUNNEL    VX_IOWR(NETIF, 10, R, struct ip_tunnel_param)

/* Change tunnel parameters. */
#define SIOCCHGTUNNEL    VX_IOWR(NETIF, 12, W, struct ip_tunnel_param)

/* Get information about a virtual LAN interface,
 * 'ifru_data' must point to a struct vlanreq
 */
#define SIOCGETVLAN      VX_IOWR(NETIF, 15, R, struct ifreq)

/* Set information about a virtual LAN interface,
 * 'ifru_data' must point to a struct vlanreq
 */
#define SIOCSETVLAN      VX_IOWR(NETIF, 16, W, struct ifreq)

/* Create a pseudo interface (like vlan) */
#define SIOCIFCREATE     VX_IOWR(NETIF, 17, W, struct ifreq)

/* Destroy a pseudo interface (like vlan) */
#define SIOCIFDESTROY    VX_IOWR(NETIF, 18, W, struct ifreq)

/* Set vlan priority for a virtual LAN interface */
#define SIOCSETVLANPRI   VX_IOWR(NETIF, 19, W, struct ifreq)

#define SIOCGIFRXIDX     VX_IOWR(NETIF, 32, R, struct ifreq)   /* Get default RX stack instance */
#define SIOCSIFRXIDX     VX_IOW(NETIF, 33, W, struct ifreq)    /* Set default RX stack instance */

/* bool: Activate/deactivate promiscuous mode. 'bool'is stored in int. */
#define SIOCXPROMISC     VX_IOW(NETIF, 102, W, int)

/* proprietary ioctls: */
/* Reset interface statistics counter */
#define SIOCXRESETSTAT   VX_IOWR(NETIF, 60, W, struct ifreq)


#ifdef __cplusplus
}
#endif

#endif /* __INCipioctlh */
