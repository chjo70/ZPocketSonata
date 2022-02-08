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

#ifndef IPNET_RTNETLINK_H
#define IPNET_RTNETLINK_H

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
#include "ipnet_netlink.h"

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

struct Ip_rtnl_link_ops;
struct Ip_rtnl_link_stats;
struct Ipnet_netif_struct;
struct Ipnet_socket_struct;

typedef int (*Ipnet_rtnetlink_do_t)   (Ipnet_netlink_mem_t  *mem,
                                       struct Ip_nlmsghdr   *nlmsg,
                                       struct Ip_rtattr     **rta,
                                       int                  family);

/* Basic callback */
/**/
typedef struct Ipnet_rtnetlink_func_table
{
    Ip_size_t                   nl_rta_max;
    Ip_size_t                   nl_size_min;
    Ipnet_netlink_dump_t        nl_dump;
    Ipnet_rtnetlink_do_t        nl_do;
} Ipnet_rtnetlink_func_table_t;

typedef struct Ipnet_rtnetlink_table
{
    int                             nl_cmd;
    Ipnet_rtnetlink_func_table_t    nl_func_table;
} Ipnet_rtnetlink_table_t;

typedef struct Ipnet_rtnetlink_config
{
    struct Ipnet_rtnetlink_table    **family_event[IP_AF_MAX];
} Ipnet_rtnetlink_config_t;

/*
 ****************************************************************************
 * 6                    PROTOTYPES
 ****************************************************************************
 */
#ifdef IPCOM_USE_INET6
IP_GLOBAL Ip_u8     ipnet_rtnetlink_ip6_get_addr_flags(Ipnet_ip6_addr_entry *addr);
IP_GLOBAL Ip_u32    ipnet_rtnetlink_ip6_get_addr_x_flags(Ipnet_ip6_addr_entry *addr);
IP_GLOBAL Ip_u32    ipnet_rtnetlink_ip6_rtscope_to_scope(Ip_u32 scope);
IP_GLOBAL Ip_u32    ipnet_rtnetlink_ip6_scope_to_rtscope(Ip_u32 scope);
#endif /* IPCOM_USE_INET6 */

IP_GLOBAL Ip_u16 ipnet_rtnetlink_neigh_nc2nud(Ipnet_neigh *neigh);
IP_GLOBAL int ipnet_rtnetlink_neigh_nud2nc(Ip_u16 ndm_state);

IP_PUBLIC int
ipnet_netlink_rtm_newrule (Ip_u8 *data, Ip_size_t len,
                           struct Ip_nlmsghdr *nlh, void *arg, int vr);

IP_PUBLIC int
ipnet_netlink_rtm_delrule (Ip_u8 *data, Ip_size_t len,
                           struct Ip_nlmsghdr *nlh, void *arg);

IP_PUBLIC int
ipnet_netlink_rtm_dumprule (Ip_u8 *data, Ip_size_t len,
                            struct Ipnet_netlink_callback *cb);

IP_GLOBAL void
ipnet_rtnetlink_broadcast(Ipcom_pkt *pkt, int msg_group);

#ifdef IPCOM_USE_INET
IP_GLOBAL int
ipnet_rtnetlink_ip4_addr_dump(Ipnet_netlink_mem_t *mem,
                              struct Ip_nlmsghdr  *nlmsg,
                              int                 req_addr_type,
                              Ip_ptrdiff_t        *args);

IP_GLOBAL int
ipnet_rtnetlink_ip4_getroute(Ipnet_netlink_mem_t  *mem,
                             struct Ip_nlmsghdr *nlh,
                             struct Ip_rtattr   **rta);

IP_GLOBAL int
ipnet_rtnetlink_ip4_newaddr(Ipnet_netlink_mem_t *mem,
                            struct Ip_nlmsghdr  *nlh,
                            struct Ip_rtattr    **rta);

IP_GLOBAL int
ipnet_rtnetlink_ip4_deladdr(Ipnet_netlink_mem_t *mem,
                            struct Ip_nlmsghdr  *nlh,
                            struct Ip_rtattr    **rta);


#endif /* IPCOM_USE_INET */

#ifdef IPCOM_USE_INET6
IP_GLOBAL int
ipnet_rtnetlink_ip6_addr_dump(Ipnet_netlink_mem_t *mem,
                              struct Ip_nlmsghdr  *nlmsg,
                              int                 req_addr_type,
                              Ip_ptrdiff_t        *args);

IP_GLOBAL int
ipnet_rtnetlink_ip6_getroute(Ipnet_netlink_mem_t  *mem,
                             struct Ip_nlmsghdr   *nlh,
                             struct Ip_rtattr     **rta);

IP_GLOBAL int
ipnet_rtnetlink_ip6_deladdr(Ipnet_netlink_mem_t *mem,
                            struct Ip_nlmsghdr  *nlh,
                            struct Ip_rtattr    **rta);

IP_GLOBAL int
ipnet_rtnetlink_ip6_newaddr(Ipnet_netlink_mem_t *mem,
                            struct Ip_nlmsghdr  *nlh,
                            struct Ip_rtattr    **rta);

#endif /* IPCOM_USE_INET6 */

IP_GLOBAL int
ipnet_rtnetlink_addr_dump_family(Ipnet_netlink_mem_t *mem,
                                 struct Ip_nlmsghdr  *nlh,
                                 int                  family,
                                 Ip_ptrdiff_t         *args);



IP_GLOBAL int
ipnet_rtnetlink_addr_newaddr_family(Ipnet_netlink_mem_t *mem,
                                    struct Ip_nlmsghdr  *nlh,
                                    struct Ip_rtattr   **rta,
                                    int                  family);

IP_GLOBAL int
ipnet_rtnetlink_addr_deladdr_family(Ipnet_netlink_mem_t *mem,
                                    struct Ip_nlmsghdr  *nlh,
                                    struct Ip_rtattr   **rta,
                                    int                  family);


IP_GLOBAL int
ipnet_rtnetlink_route_dump_family(Ipnet_netlink_mem_t               *mem,
                                  struct Ip_nlmsghdr                *nlmsg,
                                  int                               family,
                                  Ip_ptrdiff_t                      *args);

IP_GLOBAL int
ipnet_rtnetlink_route_newroute_family(Ipnet_netlink_mem_t   *mem,
                                      struct Ip_nlmsghdr    *nlh,
                                      struct Ip_rtattr      **rta,
                                      int                   family);
IP_GLOBAL int
ipnet_rtnetlink_route_delroute_family(Ipnet_netlink_mem_t   *mem,
                                      struct Ip_nlmsghdr    *nlh,
                                      struct Ip_rtattr      **rta,
                                      int                   family);

IP_GLOBAL int
ipnet_rtnetlink_route_getroute_family(Ipnet_netlink_mem_t  *mem,
                                      struct Ip_nlmsghdr   *nlh,
                                      struct Ip_rtattr     **rta,
                                      int                  family);


IP_GLOBAL int
ipnet_rtnetlink_neigh_get_family(Ipnet_netlink_mem_t  *mem,
                                 struct Ip_nlmsghdr   *nlh,
                                 struct Ip_rtattr     **rta,
                                 int                  family);

IP_GLOBAL int
ipnet_rtnetlink_neigh_dump_family(Ipnet_netlink_mem_t             *mem,
                                  struct Ip_nlmsghdr              *nlmsg,
                                  int                             family,
                                  Ip_ptrdiff_t                    *args);

IP_GLOBAL int
ipnet_rtnetlink_neigh_newneigh_family(Ipnet_netlink_mem_t  *mem,
                                      struct Ip_nlmsghdr   *nlmsg,
                                      struct Ip_rtattr     **rta,
                                      int                  family);
IP_GLOBAL int
ipnet_rtnetlink_neigh_delneigh_family(Ipnet_netlink_mem_t  *mem,
                                      struct Ip_nlmsghdr   *nlmsg,
                                      struct Ip_rtattr     **rta,
                                      int                  family);

IP_GLOBAL int
ipnet_rtnetlink_rule_dump_family(Ipnet_netlink_mem_t *mem,
                                 struct Ip_nlmsghdr  *nlmsg,
                                 int                 family,
                                 Ip_ptrdiff_t        *args);

IP_GLOBAL int
ipnet_rtnetlink_rule_newrule_family(Ipnet_netlink_mem_t *mem,
                                    struct Ip_nlmsghdr  *nlmsg,
                                    struct Ip_rtattr    **rta,
                                    int                 family);
IP_GLOBAL int
ipnet_rtnetlink_rule_delrule_family(Ipnet_netlink_mem_t *mem,
                                    struct Ip_nlmsghdr  *nlmsg,
                                    struct Ip_rtattr    **rta,
                                    int                 family);


IP_GLOBAL int
ipnet_rtnetlink_vr_newvr_family(Ipnet_netlink_mem_t  *mem,
                                struct Ip_nlmsghdr   *nlh,
                                struct Ip_rtattr     **rta,
                                int                  family);
IP_GLOBAL int
ipnet_rtnetlink_vr_delvr_family(Ipnet_netlink_mem_t  *mem,
                                struct Ip_nlmsghdr   *nlh,
                                struct Ip_rtattr     **rta,
                                int                  family);
IP_GLOBAL int
ipnet_rtnetlink_vr_changevr_family(Ipnet_netlink_mem_t  *mem,
                                   struct Ip_nlmsghdr   *nlh,
                                   struct Ip_rtattr     **rta,
                                   int                  family);
IP_GLOBAL int
ipnet_rtnetlink_vr_dump_family(Ipnet_netlink_mem_t *mem,
                               struct Ip_nlmsghdr  *nlmsg,
                               int                 family,
                               Ip_ptrdiff_t        *args);

#ifdef IPCOM_FORWARDER_NAE
IP_GLOBAL int
ipnet_rtnetlink_fwcache_dump_family(Ipnet_netlink_mem_t             *mem,
                                    struct Ip_nlmsghdr              *nlmsg,
                                    int                             family,
                                    Ip_ptrdiff_t                    *args);
IP_GLOBAL int
ipnet_rtnetlink_fwcache_delfwcache_family(Ipnet_netlink_mem_t   *mem,
                                          struct Ip_nlmsghdr    *nlh,
                                          struct Ip_rtattr      **rta,
                                          int                   family);
IP_GLOBAL int
ipnet_rtnetlink_nae_getnae_family(Ipnet_netlink_mem_t   *mem,
                                  struct Ip_nlmsghdr    *nlh,
                                  struct Ip_rtattr      **rta,
                                  int                   family);

IP_GLOBAL int
ipnet_rtnetlink_nae_setnae_family(Ipnet_netlink_mem_t   *mem,
                                  struct Ip_nlmsghdr    *nlh,
                                  struct Ip_rtattr      **rta,
                                  int                   family);

#endif

#ifdef IPCOM_USE_FORWARDER_IPSEC
IP_GLOBAL int
ipnet_rtnetlink_sacache_dump_family(Ipnet_netlink_mem_t *mem,
                                    struct Ip_nlmsghdr  *nlmsg,
                                    int                  family,
                                    Ip_ptrdiff_t        *args);


IP_GLOBAL int
ipnet_rtnetlink_sacache_delsacache_family(Ipnet_netlink_mem_t   *mem,
                                          struct Ip_nlmsghdr    *nlh,
                                          struct Ip_rtattr      **rta,
                                          int                   family);
#endif

IP_GLOBAL void
ipnet_rtnetlink_register_ops(struct Ip_rtnl_link_ops *ops);

IP_GLOBAL struct Ip_rtnl_link_ops *
ipnet_rtnetlink_get_ops(const char *kind);

IP_GLOBAL Ipnet_rtnetlink_func_table_t *
ipnet_rtnetlink_family_get_dump(struct Ipnet_rtnetlink_table    ***table,
                                int                             family,
                                int                             cmd);

IP_GLOBAL Ipnet_rtnetlink_func_table_t *
ipnet_rtnetlink_family_get_do(struct Ipnet_rtnetlink_table    ***table,
                              int                             family,
                              int                             cmd);


#ifdef __cplusplus
}
#endif

#endif	/* IPNET_NETLINK_H */


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

