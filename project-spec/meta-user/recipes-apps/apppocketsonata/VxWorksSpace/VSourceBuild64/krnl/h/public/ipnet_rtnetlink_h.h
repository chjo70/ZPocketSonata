
/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPNET_RTNETLINK_H_H
#define IPNET_RTNETLINK_H_H

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

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */
#include "ipnet_neigh.h"
#include "ipnet_rtnetlink.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef IPNET_USE_NETLINK

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
struct Ipnet_socket_struct;
struct Ipnet_netif_struct;
struct Ipnet_rt_metrics;
struct Ipnet_route_entry_struct;
struct Ipnet_ip6_addr_entry_struct;
struct Ipnet_ip4_addr_entry_struct;
struct Ipnet_policy_routing_rule;


typedef union Ipnet_rtnetlink_key
{
#ifdef IPCOM_USE_INET
    struct
    {
        struct Ipnet_ipv4_key         key;
        struct Ipnet_ipv4_key         mask;
    } v4;
#endif
#ifdef IPCOM_USE_INET6
    struct
    {
        struct Ipnet_ipv6_key         key;
        struct Ipnet_ipv6_key         mask;
    } v6;
#endif
} Ipnet_rtnetlink_key_t;

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */
IP_PUBLIC void ipcom_netlink_respond(int proto,
                                     void *data,
                                     Ip_size_t len,
                                     int msg_group,
                                     Ip_u16 vr);
IP_PUBLIC void ipcom_netlink_post(int unit,
                                  void *data,
                                  Ip_size_t len,
                                  int msg_group,
                                  Ip_u16 vr);
IP_GLOBAL void  ipnet_rtnetlink_register_family_event(int                           family,
                                                      int                           cmd,
                                                      Ip_size_t                     maxattr,
                                                      Ip_size_t                     nl_min_size,
                                                      Ipnet_rtnetlink_do_t          doit,
                                                      Ipnet_netlink_dump_t          dumpit);

#ifdef IPCOM_USE_INET
IP_GLOBAL void ipnet_rtnetlink_ip4_init(void);
IP_GLOBAL int ipnet_rtnetlink_ip4_route_fill_info(Ipnet_netlink_mem_t *mem,
                                                  Ipnet_route_entry   *rt,
                                                  Ip_u32              seq,
                                                  int                 event,
                                                  Ip_u16              eflags);
IP_GLOBAL int ipnet_rtnetlink_ip4_neigh_fill_info(Ipnet_netlink_mem_t *mem,
                                                  Ipnet_neigh         *neigh,
                                                  Ip_u32              seq,
                                                  int                 event,
                                                  Ip_u16              eflags);
IP_GLOBAL int ipnet_rtnetlink_ip4_route_key_setup(Ipnet_rtnetlink_key_t   *ukey,
                                                  Ip_u32                  ifindex,
                                                  void                    **maskp,
                                                  unsigned                mask_len,
                                                  struct Ip_rtattr        *dst);
IP_GLOBAL int ipnet_rtnetlink_ip4_route_gw_setup(Ip_u32                     ifindex,
                                                 union Ip_sockaddr_union    *ugw,
                                                 struct Ip_sockaddr         **gw,
                                                 struct Ip_rtattr           *rta);
IP_GLOBAL void ipnet_rtnetlink_ip4_addr_add(struct Ipnet_netif_struct *netif,
                                            struct Ipnet_ip4_addr_entry_struct *addr);
IP_GLOBAL void ipnet_rtnetlink_ip4_addr_del(struct Ipnet_netif_struct *netif,
                                            struct Ipnet_ip4_addr_entry_struct *addr);
IP_GLOBAL void ipnet_rtnetlink_ip4_addr_conflict(struct Ipnet_netif_struct *netif,
                                                 struct Ipnet_ip4_addr_entry_struct *addr);
#endif

#ifdef IPCOM_USE_INET6
IP_GLOBAL void ipnet_rtnetlink_ip6_init(void);
IP_GLOBAL int ipnet_rtnetlink_ip6_route_fill_info(Ipnet_netlink_mem_t *mem,
                                                  Ipnet_route_entry   *rt,
                                                  Ip_u32              seq,
                                                  int                 event,
                                                  Ip_u16              eflags);

IP_GLOBAL int ipnet_rtnetlink_ip6_neigh_not_local(Ipnet_neigh         *neigh);

IP_GLOBAL int ipnet_rtnetlink_ip6_neigh_fill_info(Ipnet_netlink_mem_t *mem,
                                                  Ipnet_neigh         *neigh,
                                                  Ip_u32              seq,
                                                  int                 event,
                                                  Ip_u16              eflags);
IP_GLOBAL int ipnet_rtnetlink_ip6_route_key_setup(Ipnet_rtnetlink_key_t   *ukey,
                                                  Ip_u32                  ifindex,
                                                  void                    **maskp,
                                                  unsigned                mask_len,
                                                  struct Ip_rtattr        *dst);
IP_GLOBAL int ipnet_rtnetlink_ip6_route_gw_setup(Ip_u32                     ifindex,
                                                 union Ip_sockaddr_union    *ugw,
                                                 struct Ip_sockaddr         **gw,
                                                 struct Ip_rtattr           *rta);
IP_GLOBAL void ipnet_rtnetlink_ip6_addr_add(struct Ipnet_netif_struct *netif,
                                            struct Ipnet_ip6_addr_entry_struct *addr);
IP_GLOBAL void ipnet_rtnetlink_ip6_addr_del(struct Ipnet_netif_struct *netif,
                                            struct Ipnet_ip6_addr_entry_struct *addr);
#endif

IP_GLOBAL int ipnet_rtnetlink_route_sz_fill_metrics(Ipnet_netlink_mem_t       *mem,
                                                    struct Ipnet_rt_metrics   *metrics,
                                                    Ip_u32                    mtu);



IP_GLOBAL int ipnet_rtnetlink_route_key_setup(int                   family,
                                              Ipnet_rtnetlink_key_t *ukey,
                                              Ip_u32                ifindex,
                                              void                  **maskp,
                                              unsigned              mask_len,
                                              struct Ip_rtattr      *dst);

IP_GLOBAL int ipnet_rtnetlink_route_gw_setup(int                        family,
                                             Ip_u32                     ifindex,
                                             union Ip_sockaddr_union    *ugw,
                                             struct Ip_sockaddr         **gw,
                                             struct Ip_rtattr           *rta);
IP_GLOBAL void ipnet_rtnetlink_route_add(Ipnet_route_entry *rt);
IP_GLOBAL void ipnet_rtnetlink_route_del(Ipnet_route_entry *rt);
IP_GLOBAL void ipnet_rtnetlink_route_change(Ipnet_route_entry *rt);
IP_GLOBAL void ipnet_rtnetlink_route_miss(Ipcom_route *rtab, IP_CONST void *key);
IP_GLOBAL void ipnet_rtnetlink_route_redirect(Ipcom_route *rtab, Ip_u32 ifindex,
                                           IP_CONST void *dst, IP_CONST void *new_gw);
IP_GLOBAL void ipnet_rtnetlink_rule_event(struct Ipnet_policy_routing_rule *mpr,
                                          Ip_u16                           vr,
                                          Ip_pid_t                         pid,
                                          int                              event);

IP_GLOBAL void ipnet_rtnetlink_init_once(void);
IP_GLOBAL void ipnet_rtnetlink_link_init(void);
IP_GLOBAL void ipnet_rtnetlink_vr_init(void);


IP_GLOBAL void ipnet_rtnetlink_neigh_change(Ipnet_neigh *neigh);
IP_GLOBAL void ipnet_rtnetlink_neigh_del(Ipnet_neigh *neigh);


IP_GLOBAL void *ipnet_rtnetlink_rta_sz_put(Ipnet_netlink_mem_t  *mem,
                                           Ip_u16               atype,
                                           Ip_size_t            alen,
                                           IP_CONST void        *data);
IP_GLOBAL void *ipnet_rtnetlink_rta_sz_put_u32(Ipnet_netlink_mem_t  *mem,
                                               Ip_u16               atype,
                                               Ip_u32               val);
IP_GLOBAL void *ipnet_rtnetlink_rta_sz_nested_begin(Ipnet_netlink_mem_t *mem,
                                                    Ip_u16              attrtype);
IP_GLOBAL void ipnet_rtnetlink_rta_sz_nested_end(Ipnet_netlink_mem_t    *mem,
                                                 void                   *nested);
IP_GLOBAL int
ipnet_rtnetlink_sock_send(struct Ipnet_socket_struct    *sock,
                          Ip_bool                       non_blocking,
                          struct Ip_nlmsghdr            *nlmsg);

/* Notifications */
IP_GLOBAL void ipnet_rtnetlink_link_change(struct Ipnet_netif_struct *netif);
IP_GLOBAL void ipnet_rtnetlink_link_add(struct Ipnet_netif_struct *netif);
IP_GLOBAL void ipnet_rtnetlink_link_delete(struct Ipnet_netif_struct *netif);

IP_GLOBAL void ipnet_netlinksock_vrtab_add(Ip_u16 vr, Ip_u32 table);
IP_GLOBAL void ipnet_netlinksock_vrtab_del(Ip_u16 vr, Ip_u32 table);
IP_GLOBAL void ipnet_netlinksock_vrtab_change(Ip_u16 vr, const char *ifname, Ip_u16 newvr);


IP_GLOBAL Ip_u16 ipnet_rtnetlink_vr(struct Ip_rtattr *rta, Ip_u16 vr);

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
