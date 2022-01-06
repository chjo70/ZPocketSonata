/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef IPNET_ROUTE_H
#define IPNET_ROUTE_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 *
 * The route table state is protected by a single lock which can be
 * acquired/released using ipnet_route_lock()/ipnet_route_unlock(). The
 * lock can be acquired recursively. All functions with a '_l' suffix
 * requires the lock to be taken before calling the function.
 *
 * It is suggested that any function outside of this module that must
 * be called with the route lock held uses a '_rtl' suffix
 * (route_lock).
 *
 * Note! that any pointer to a returned Ipnet_route_entry must be
 * considered stale as soon as the route lock is released.
 *
 * Make sure that you do not call any functions in this module in the
 * packet transmission/reception path unless absolutely necessary. The
 * destination cache is a lot faster and scales better across multiple
 * CPU-cores since it is local to each stack instance, while the route
 * table/FIB is shared.
 *
 */

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include "ipnet_config.h"

#include <ipcom_list.h>
#include <ipcom_route.h>

#include "ipnet_policy_routing.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* IPNET internal route flags */
#define IPNET_RTF_X_MCAST_RO    0x00100000 /* Read only multicast route */
#define IPNET_RTF_X_BCAST_RO    0x00200000 /* Read only broadcast route */
#define IPNET_RTF_X_AUTO        0x00800000 /* Added automatically by the stack since
                                              a router advertisment was received with
                                              this prefix */
#define IPNET_RTF_X_IGNORE_PREF 0x01000000 /* Do not put this route first even if
                                              IPNET_RTF_PREF is set, used when more than
                                              one route has that flag set */
#define IPNET_RTF_X_SILENT      0x02000000 /* Do not report changes on routing sockets */
#define IPNET_RTF_X_HIDDEN      0x04000000 /* Do not list route in sysctl() */
#define IPNET_RTF_X_NEIGH_ACK   0x08000000 /* This neighbor has been ACK:ed */

#define IPNET_RTF_PUBLIC_FLAGS  0x000FFFFF

/* IPNET internal route flags using the "iflag" field */
#define IPNET_RTI_FLAG_CLEAN     (1 << 0) /* Delete the route on the next timeout */
#define IPNET_RTI_FLAG_FRAG_HDR  (1 << 1) /* Always add a fragmentation header */
#define IPNET_RTI_FLAG_MULTIPATH (1 << 2) /* May be a multipath route */


/*
 * macros for getting and setting tos values in Ipnet_sockaddr_in
 * structures. A new sockaddr structure is defined for this
 * purpose as shown below. Note that the members beyond
 * srt_tos are irrelevant in this type.
 */
struct Ipnet_sockaddr_rt {
    Ip_u8	srt_len;
    Ip_u8	srt_family;
    Ip_u8	srt_proto;
    Ip_u8	srt_tos;
    Ip_u32      srt_addr;    /* unused */
    char        sin_zero[8]; /* unused */
    };

#define M2_ipRouteProto_rip             		8

#ifndef TOS_GET
#define TOS_GET(pSockaddr) (((struct Ipnet_sockaddr_rt *)(pSockaddr))->srt_tos)
#endif

#ifndef TOS_SET
#define TOS_SET(pSockaddr, tosVal) \
    (((struct Ipnet_sockaddr_rt *)(pSockaddr))->srt_tos = tosVal)
#endif

#ifndef RT_PROTO_GET
#define RT_PROTO_GET(pSockaddr) (((struct Ipnet_sockaddr_rt *)(pSockaddr))->srt_proto)
#endif

#ifndef RT_PROTO_SET
#define RT_PROTO_SET(pSockaddr, proto) \
    (((struct Ipnet_sockaddr_rt *)(pSockaddr))->srt_proto = proto)
#endif


/* Hopcount to be added to automatically added entries such as the broadcast
   and multicast for IPv4 */
#define IPNET_ROUTE_AUTOMATIC_ENTRY_HOPCOUNT 10000


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

struct Ipnet_data_struct;
struct Ipnet_neigh_struct;
struct Ipnet_netif_struct;
struct Ipnet_timeout_struct;

/* Get/set the family for a route table */
#define IPNET_ROUTE_GET_FAMILY(rtab)     ((rtab)->user1)
#define IPNET_ROUTE_SET_FAMILY(rtab, af) ((rtab)->user1 = (Ip_u16) af)
/* Get/set virtual router index of a route table */
#define IPNET_ROUTE_GET_VR(rtab)         ((rtab)->user2)
#define IPNET_ROUTE_SET_VR(rtab, index)  ((rtab)->user2 = (Ip_u16) index)
/* Get/set the table ID of a route table */
#define IPNET_ROUTE_GET_TABLE(rtab)      ((rtab)->user3)
#define IPNET_ROUTE_SET_TABLE(rtab, p)   ((rtab)->user3 = (Ip_u32) p)

#define IPNET_USE_ROUTE_COOKIES
#ifdef IPNET_USE_ROUTE_COOKIES
/*
 *===========================================================================
 *                         Ipnet_rt_cookie
 *===========================================================================
 * Used for tagging a certain route entry or route table with a user
 * supplied finger print.
 */
typedef struct Ipnet_rt_cookie_struct
{
    Ip_u32 d1;
    Ip_u32 d2;
}
Ipnet_rt_cookie;

#endif /* IPNET_USE_ROUTE_COOKIES */


struct Ipnet_route_entry_struct;
struct Ipcom_pkt_struct;
struct Ipnet_dst_cache_struct;
struct Ipnet_flow_spec_struct;

typedef int (*Ipnet_route_entry_func_t) (struct Ipnet_route_entry_struct    **rtentry,
                                         struct Ipcom_pkt_struct            *pkt,
                                         void                               *fparam,
                                         Ip_bool                            *dont_route);

typedef Ip_bool (*Ipnet_route_compare_func_t) (struct Ipnet_route_entry_struct    *rtentry,
                                               struct Ipcom_pkt_struct            *pkt);

typedef Ip_bool (*Ipnet_route_flow_spec_cmp_t) (struct Ipnet_route_entry_struct    *rtentry,
                                                struct Ipnet_dst_cache_struct      *dst);

struct Ipnet_route_func_info
{
    Ip_size_t                       rt_info_size; /* Size of this struct */
    Ipnet_route_entry_func_t        rt_info;      /* Callback */
    Ipnet_route_compare_func_t      rt_compare;

    Ipnet_route_flow_spec_cmp_t     rt_flow_cmp;
};


/*
 *===========================================================================
 *                   Ipnet_route_timedoutcb
 *===========================================================================
 * Description: Timeout/cleanup handler for a route entry.
 * Parameters:  rt - The route entry that timed-out.
 *              is_timeout - Is IP_TRUE if this is a timeout, IP_FALSE if
 *              this route is beeing deleted.
 * Returns:
 *
 */
typedef void (*Ipnet_route_timedoutcb) (struct Ipnet_route_entry_struct *rt,
                                        Ip_bool is_timeout);

/*
 *===========================================================================
 *                         Ipnet_route_entry
 *===========================================================================
 */

/* Internal nodes in the Patricia tree contains parent, on, off, bit, flags and netmask */
typedef struct Ipnet_route_entry_struct
{
    /* The header required by the route package */
    Ipcom_route_entry               hdr;
    /* Head of the route table */
    Ipcom_route                     *head;
    /* Internal route flags */
    Ip_u16                          iflags;

    /* Protocol and scope */
    Ip_u8                           protocol;
    Ip_u8                           scope;

    /* pid of the process that added this route (or 0 for IPNET) */
    Ip_pid_t                        pid;
    /* seq value of the message that added this route */
    Ip_u32                          seq;
    /* Number of times this entry has been used. Consider unsigned. */
    Ipcom_atomic_t                  use;

    /* Number of clients that have locked this entry to prevent it
       from beeing freed. NOTE: the entry can still be removed from the FIB */
    Ip_u32                     lockcnt;
    /* Number of references to this route entry */
    Ip_s32                     ref_count;
    /* Timeout handle, will be != IP_NULL if this entry has a finite lifetime */
    struct Ipnet_timeout_struct *tmo;
    /* Route metric */
    struct Ipnet_rt_metrics    metrics;

    /* Pointer to the network interface for this route */
    struct Ipnet_netif_struct *netif;

    /* First hop address or link layer data if
       IPNET_RTF_LLINFO is set in hdr.flags */
    struct Ip_sockaddr        *gateway;

    /* Source MAC address to be matched */

    /* Opaque data for a routing entry process function */
    /* To be invoked by forward/lookup function with required data */
    struct Ipnet_route_func_info    *rt_func_info;

    /* Additional route data that can be used by link-layer
       This buffer is used by NDP for IPv6 and exist only
       on entries with the IPNET_RTF_LLINFO flag set
       (IP_NULL on all other entries).
       The length is IPNET_ROUTE_ENTRY_DATA_LEN  */
    void                      *data;

    /* Will be called when the entry times out if != IP_NULL  */
    Ipnet_route_timedoutcb     timedout_cb;

#ifdef IPNET_USE_NETLINKSOCK
    /* Reference id used when dumping routes via netlink */
    Ip_pid_t                   netlink_pid;
#endif
#ifdef IPNET_USE_ROUTE_COOKIES
    Ipnet_rt_cookie            cookie;
#endif

#ifdef IPCOM_USE_MIB2_NEW
    Ip_u32                     msec_changed;
#endif

#ifdef IPNET_USE_RFC4941
    /* Number of times DAD for address generated for this prefix has failed */
    int                        temp_idgen_retries;
#endif

    /* The template route entry this route entry was cloned from or
       IP_NULL if this is not a cloned route */
    struct Ipnet_route_entry_struct *rt_template;

    /* The next route entry using the same key, but the prefixlen is larger */
    struct Ipnet_route_entry_struct *narrow;
    /* The next route entry using the same key, but the prefixlen is smaller */
    struct Ipnet_route_entry_struct *widen;
    /* The next route with the same key and mask */
    struct Ipnet_route_entry_struct *next;
    /* The previous route with the same key and mask */
    struct Ipnet_route_entry_struct *prev;
}
Ipnet_route_entry;

/* The key for IPv4 is (32-bit) */
#ifdef IPCOM_USE_INET
struct Ipnet_ipv4_key
{
    struct Ip_in_addr   addr;
};
#endif

/* The key for IPv6 is (160-bit) */
#ifdef IPCOM_USE_INET6
struct Ipnet_ipv6_key
{
    struct Ip_in6_addr  addr;
    Ip_u32              scope_id;       /* Scope ID in host byte order */
};
#endif


union Ipnet_route_key
{
#ifdef IPCOM_USE_INET
    struct Ipnet_ipv4_key ipv4;
#endif
#ifdef IPCOM_USE_INET6
    struct Ipnet_ipv6_key ipv6;
#endif
};


struct Ipnet_route_add_param
{
    int                     domain;          /* Domain where the route should be added
                                            (IP_AF_INET or IP_AF_INET6) */
    Ip_u16                  vr;              /* Virtual router index (0 = default route table) */
    Ip_u32                  table;           /* The route table ID (0 = default) */
    struct Ipnet_netif_struct *netif;    /* The interface used to send packets along this route,
                                            can be IP_NULL if a gateway is specified */
    IP_CONST void           *key;            /* Pointer to the destination key */
    IP_CONST void           *netmask;        /* The network mask (set to IP_NULL if all bits == 1) */
    struct Ip_sockaddr      *gateway;        /* The gateway to use */

    Ip_u32                  flags;           /* IPNET_RTF_xxx flags for this route */
    struct Ipnet_rt_metrics *metrics;    /* The route metrics */
    Ip_pid_t                pid;             /* The PID of the process that last modified this entry */
    Ip_u32                  seq;             /* The seq number on the message that last modified
                                                this route */
    Ip_u16                  iflags;          /* IPNET_RTF_xxx flags for this route */
    Ip_u8                   protocol;       /* Routing protocol; see below  */
    Ip_u8                   scope;          /* See below */

    struct Ipnet_route_func_info    *rtinfo;    /* Opaque info; I need this to deal with various routing requirements */

    Ip_bool                 no_ref_count;    /* Set to IP_TRUE if no reference counting should be used. */
    Ipnet_route_entry       *rt_template;     /* The route entry this entry is cloned from */
#ifdef IPNET_USE_ROUTE_COOKIES
    Ipnet_rt_cookie         *cookie;
#endif
};

typedef struct Ipnet_route_policy_rule_struct
{
    Ipcom_list                        list;
    struct Ipnet_policy_routing_rule  rule;
}
Ipnet_route_policy_rule;


/* Parameters to identify the router being deleted */
typedef struct Ipnet_route_delete_for_each_data_struct
{
    struct Ipnet_netif_struct   *netif;   /* The interface routes must points to */
    IP_CONST struct Ip_sockaddr *gateway; /* The address of the gateway or
                                             IP_NULL if gateway should be ignored */
    Ip_u32                       has_not_flags; /* Matching entries must not have these flags set */
}
Ipnet_route_delete_for_each_data;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/* None of the following function can be called by a user application */
IP_GLOBAL void ipnet_route_init_once(void);
IP_GLOBAL void ipnet_route_cache_invalidate(void);
IP_GLOBAL int ipnet_route_add(IP_CONST struct Ipnet_route_add_param *param);
IP_GLOBAL int ipnet_route_delete(int domain, Ip_u16 vr, IP_CONST void *key);
IP_GLOBAL int ipnet_route_delete2(int domain, Ip_u16 vr, Ip_u32 table,
                                  IP_CONST void *key, IP_CONST void *mask,
                                  struct Ip_sockaddr *gw, Ip_u32 ifindex,
                                  Ip_pid_t pid, Ip_u32 seq, Ip_bool use_ref_count);

IP_GLOBAL int ipnet_route_set_rtab(int domain, Ip_u16 vr, Ip_u32 table, Ipcom_route *rt_head);

/* Flags */
#define IPNET_RTL_FLAG_DONTCLONE    0x1      /* Do not clone the route even if the IPNET_RTF_CLONING flag is set */
#define IPNET_RTL_FLAG_LINK_LOCAL   0x2      /* The returned route must have the IPNET_RTF_LLINFO set */
#define IPNET_RTL_FLAG_DONTRECURSE  0x1000   /* Internal use only. Do not make recurive calls to lookup */
#define IPNET_RTL_FLAG_DOWN_OK      0x2000   /* Internal use only. Return routes even if IPNET_RTF_UP is not set */

/* Success return values */
#define IPNET_ROUTE_PERFECT_MATCH   0
#define IPNET_ROUTE_MASK_MATCH      1

#ifdef IPNET_DEBUG
IP_GLOBAL Ip_bool ipnet_route_is_guarded(void);
#define ipnet_route_lock() ipnet_route_lock_dbg(__FILE__, __LINE__)
IP_GLOBAL void ipnet_route_lock_dbg(const char *file, int line);
#define ipnet_route_unlock() ipnet_route_unlock_dbg(__FILE__, __LINE__)
IP_GLOBAL void ipnet_route_unlock_dbg(const char *file, int line);
#else
IP_GLOBAL void ipnet_route_lock(void);
IP_GLOBAL void ipnet_route_unlock(void);
#endif

IP_GLOBAL void ipnet_route_addref(Ipnet_route_entry *rt);
IP_GLOBAL Ip_bool ipnet_route_delref(Ipnet_route_entry *rt);
IP_GLOBAL Ip_bool ipnet_route_has_expired(Ipnet_route_entry *rt);


IP_PUBLIC void ipnet_route_create_mask(void *mask, unsigned netbits);
IP_GLOBAL void ipnet_route_apply_mask(void *net, IP_CONST void *mask, int bitcount);
IP_GLOBAL Ip_bool ipnet_route_key_cmp(IP_CONST void *key1, IP_CONST void *key2, Ip_u8 key_len);
IP_GLOBAL void ipnet_route_key_to_sockaddr(int domain, IP_CONST void *key, struct Ip_sockaddr *sa);

IP_GLOBAL int ipnet_route_get_table_ids(Ip_u16 vr, Ip_u32 *table_ids, unsigned *num_tables);
IP_GLOBAL void ipnet_route_remove_all(int domain, struct Ipnet_netif_struct *netif);


#ifdef IPNET_USE_ROUTESOCK
IP_GLOBAL void ipnet_route_sockaddr_to_key(int domain, IP_CONST struct Ip_sockaddr *sa, void *key);
#endif

IP_GLOBAL int ipnet_route_add_table(Ip_u16 vr, Ip_u32 table, Ip_u16 *pvr, Ip_u32 *ptable);
IP_GLOBAL int ipnet_route_delete_table(Ip_u16 vr, Ip_u32 table);
IP_GLOBAL int ipnet_route_delete_vr(Ip_u16 vr);
IP_GLOBAL Ip_bool ipnet_route_is_virtual_router_valid(Ip_u16 vr);

#ifdef IPNET_USE_ROUTE_TABLE_NAMES
IP_GLOBAL int   ipnet_route_set_name(Ip_u16 vr, Ip_u32 table, char *rtab_name);
IP_GLOBAL char *ipnet_route_get_name(Ip_u16 vr, Ip_u32 table, char *name_buf);
IP_GLOBAL void  ipnet_route_delete_name(char *rtab_name);
IP_GLOBAL int   ipnet_route_vr_and_table_from_name(char *rtab_name, Ip_u16 *vr, Ip_u32 *table);
#endif /* IPNET_USE_ROUTE_TABLE_NAMES */

#ifdef IPNET_USE_ROUTE_COOKIES
IP_GLOBAL int ipnet_route_get_cookie(Ip_u16 vr, Ip_u32 table, Ipnet_rt_cookie *cookie);
IP_GLOBAL int ipnet_route_set_cookie(Ip_u16 vr, Ip_u32 table, Ipnet_rt_cookie *rtab_cookie);
IP_GLOBAL void ipnet_route_delete_cookie(Ip_u16 vr, Ip_u32 table);
#endif /* IPNET_USE_ROUTE_COOKIES */

#ifdef IPCOM_USE_INET
IP_GLOBAL Ip_bool
ipnet_route_ip4_is_mcast_or_bcast(IP_CONST struct Ip_in_addr *dst, Ip_u32 ifindex, Ip_u16 vr);
#endif

IP_GLOBAL int ipnet_route_policy_ioctl(Ip_pid_t pid, Ip_u16 vr, Ip_u32 request, struct Ipnet_policy_routing_rule* rule);
IP_GLOBAL void ipnet_route_remove_dynamic_rt_with_gw(struct Ipnet_neigh_struct *gw_neigh);
IP_GLOBAL void ipnet_route_for_each_data_init(Ipnet_route_delete_for_each_data *d,
                                              struct Ipnet_netif_struct *netif,
                                              IP_CONST struct Ip_sockaddr *gateway,
                                              Ip_u32 has_not_flags);

/*
 * All functions below must be called with the route lock held or
 * called with all stack instances suspended (debug function
 * ipnet_route_is_guarded() must return IP_TRUE)). Note that the lock
 * must be held as long as a returned Ipcom_route or Ipnet_route_entry
 * instance is used by the caller.
 *
 * All functions that need to hold the route lock has a '_l' suffix.
 */
IP_GLOBAL void ipnet_route_notify_func_l(Ipcom_route *rtab, Ipcom_route_entry *entry, int code);

IP_GLOBAL int ipnet_route_lookup_l(int domain, Ip_u16 vr, Ip_u32 table, int flags,
                                   IP_CONST void *dst, Ip_u32 scope_id,
                                   Ip_u32 ifindex,
                                   Ipnet_route_entry **rt);
IP_GLOBAL int ipnet_route_lookup_ecmp_l(int domain, Ip_u16 vr, int flags,
                                        IP_CONST void *dst, Ip_u32 scope_id,
                                        Ip_u32 ifindex,
                                        struct Ipnet_dst_cache_struct *dcache,
                                        const struct Ipnet_flow_spec_struct *flow_spec,
                                        Ipnet_route_entry **rt);
IP_GLOBAL int ipnet_route_raw_lookup_l(int domain, Ip_u16 vr, Ip_u32 table, int flags,
                                       IP_CONST void *dst, Ip_u32 scope_id,
                                       Ip_u32 ifindex,
                                       Ipnet_route_entry **rt);
IP_GLOBAL int ipnet_route_raw_lookup2_l(int domain, Ip_u16 vr, Ip_u32 table, int flags,
                                        IP_CONST void *dst, Ip_u32 scope_id,
                                        IP_CONST void *mask, struct Ip_sockaddr *gw, Ip_u32 ifindex,
                                        Ipnet_route_entry **rt);

IP_GLOBAL Ipnet_route_policy_rule *ipnet_route_policy_get_rule_chain_l(int domain, Ip_u16 vr);
IP_GLOBAL int ipnet_route_get_rtab_l(int domain, Ip_u16 vr, Ip_u32 table, Ipcom_route **rtab);
IP_GLOBAL void ipnet_route_set_lifetime_l(Ipnet_route_entry *rt, Ip_u32 lifetime_sec);
IP_GLOBAL void ipnet_route_has_changed_l(Ipnet_route_entry *rt);

IP_GLOBAL Ipnet_route_entry *ipnet_route_first_entry_l(int domain, Ip_u16 vr, Ip_u32 table);
IP_GLOBAL Ipnet_route_entry *ipnet_route_next_entry_l(Ipnet_route_entry *rt);

IP_GLOBAL Ip_bool ipnet_route_remove_all_cb_for_each_entry_l(Ipnet_route_entry *rt,
                                                             Ipnet_route_delete_for_each_data *d);

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
