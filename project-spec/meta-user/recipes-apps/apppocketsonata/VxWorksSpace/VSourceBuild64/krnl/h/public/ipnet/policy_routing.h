/* policy_routing.h - policy routing header file */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
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
01a,30nov06,kch  Guarded inet6 definitions with INET6. Also replaced IP_IOWR
                 with VX_IOWR and added ipnet/ipioctl.h include.
*/

#ifndef __INCpolicy_routingh
#define __INCpolicy_routingh

/* includes */
#include <ipnet/ipioctl.h>
#include "netinet/in.h"
#ifdef INET6
#include "netinet6/in6.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Policy routing i/o controls
 */

#define PR_BASE 20

#define SIOCGPRRULE     VX_IOWR(POLICY_RT, 0, R, struct policy_routing_rule)
#define SIOCSPRRULE     VX_IOWR(POLICY_RT, 1, W, struct policy_routing_rule)
#define SIOCDPRRULE     VX_IOWR(POLICY_RT, 2, W, struct policy_routing_rule)
#define SIOCEPRRULE     VX_IOWR(POLICY_RT, 3, R, struct policy_routing_rule)

/*
 * Rules are processed by descending priority, rules with same priority
 * are processed in the order they where added (added first is processed first)
 */
#define PR_PRIO_MIN   (-32768)
#define PR_PRIO_MAX   (32767)

#define PR_ID_NONE   0


/*
 * in_addr_union
 */
#ifndef IN_ADDR_UNION_TYPE
#define IN_ADDR_UNION_TYPE
union in_addr_union
{
    struct in_addr    in;
#ifdef INET6    
    struct in6_addr   in6;
#endif /* INET6 */    
};
#endif /* !IN_ADDR_UNION_TYPE */

/*
 * policy_routing_rule
 */
struct policy_routing_rule
{
    u_long                table;           /* The table ID of the routing table to use if this rule matches */
    BOOL                  last;            /* Set to TRUE if no other rules should consider if the
                                              routing table with policy ID 'policy' does not give a match */
    u_long                id;              /* Unique identifier of this rule (SIOCSPRRULE set this) */
    short                 prio;            /* The index of this rule or one of the PR_IDX_xxx macros */
    u_short               mask;            /* Set PR_RULE_xxx bit for each field that must match */
    u_char                af;              /* Address family for this rule */
    u_char                ds;              /* Traffic class (IPv6) or TOS (IPv4) (== DS field for DiffServ) */
    u_char                proto;           /* Protocol in the IP header */
    u_char                saddr_prefixlen; /* Source prefixlen, set to 0 for exact match of 'saddr' */
    u_char                daddr_prefixlen; /* Destination prefixlen, set to 0 for exact match of 'daddr' */
    union in_addr_union   saddr;           /* Source address or source network */
    union in_addr_union   daddr;           /* Destination address or destination network */
    u_long                flow;            /* IPv6 flow ID in host byte order */
    u_long                ifindex;         /* Interface index in host byte order (bound if for sending, incoming if for forwarding) */
    u_long                scope;           /* The scope of the destination        */
    u_long                pkt_mask;        /* The mask to apply to the packet     */
    u_long                pkt_result;      /* The result when masking the flags   */
};

/*
 * PR_xx
 */

#define PR_RULE_DS            (1 << 0)
#define PR_RULE_PROTO         (1 << 1)
#define PR_RULE_SADDR         (1 << 2)
#define PR_RULE_FLOW          (1 << 3)
#define PR_RULE_IFINDEX       (1 << 4)
#define PR_RULE_SCOPE         (1 << 5)
#define PR_RULE_DADDR         (1 << 7)
#define PR_RULE_PKTFLAGS      (1 << 8)

/* Do the route lookup based on the source (not destination)
 * address in the matching route table
 */
#define PR_RULE_RTKEYSADDR    (1 << 15)

#ifdef __cplusplus
}
#endif

#endif /* !__INCpolicy_routingh */

