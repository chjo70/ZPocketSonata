/* qos.h - quality of service header file */

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


#ifndef __INCqosh
#define __INCqosh

/* includes */
#include <ipnet/ipioctl.h>
#include "net/if.h"
#include "netinet/in.h"
#ifdef INET6
#include "netinet6/in6.h"
#endif /* INET6 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Quality of service i/o controls
 */
#define IFQ_BASE     192

/* Add a filter for differentiated services meter/marker */
#define SIOCXADSFILTER   VX_IOWR(DS, 0, W, struct ds_filter)

/* Delete a filter for differentiated services meter/marker */
#define SIOCXDDSFILTER   VX_IOWR(DS, 1, W, struct ds_filter)

/* Create a new differentiated services meter/marker entity */
#define SIOCXDSCREATE    VX_IOWR(DS, 2, W, struct ds)

/* Destroys a differentiated services meter/marker entity */
#define SIOCXDSDESTROY   VX_IOWR(DS, 3, W, struct ds)

/* Add a filter for differentiated services meter/marker */
#define SIOCXADSMAP      VX_IOWR(DS, 4, W, struct ds_map)

/* Delete a filter for differentiated services meter/marker */
#define SIOCXDDSMAP      VX_IOWR(DS, 5, W, struct ds_map)

/* Get the queue type for an interface */
#define SIOCGIFQUEUE     VX_IOWR(NETIF, (IFQ_BASE + 0), R, struct ifqueue_qos)

/* Set the queue type for an interface */
#define SIOCSIFQUEUE     VX_IOWR(NETIF, (IFQ_BASE + 1), W, struct ifqueue_qos)

/* Add a filter to an interface queue */
#define SIOCXAIFQFILTER  VX_IOWR(NETIF, (IFQ_BASE + 2), W, struct ifqueue_filter)

/* Delete a filter from an interface queue */
#define SIOCXDIFQFILTER  VX_IOWR(NETIF, (IFQ_BASE + 3), W, struct ifqueue_filter)


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
 * CLASSIFIER DEFINES
 */

/*
 * classifier_rule
 */
struct classifier_rule
{
    u_short          mask;            /* Set CLS_RULE_xxx bit for each field that must match */
    u_char           ds;              /* Traffic class (IPv6) or TOS (IPv4) (== DS field for DiffServ) */
    u_char           proto;           /* Protocol in the IP header */
    u_short          sport_low;       /* Source port for UDP and TCP protocols [low..high] */
    u_short          sport_high;      /* Source port for UDP and TCP protocols */
    u_short          dport_low;       /* Destination port for UDP and TCP protocols [low..high] */
    u_short          dport_high;      /* Destination port for UDP and TCP protocols */
    u_char           af;              /* Address family of the addresses (AF_INET or AF_INET6) */
    u_char           saddr_prefixlen; /* Source prefixlen, set to 0 for exact match of 'saddr' */
    u_char           daddr_prefixlen; /* Destination prefixlen, set to 0 for exact match of 'daddr' */
    union in_addr_union  saddr;       /* Source address or source network */
    union in_addr_union  daddr;       /* Destination address or destination network */
};

#define CLS_RULE_DS      (1 << 0)
#define CLS_RULE_PROTO   (1 << 1)
#define CLS_RULE_SADDR   (1 << 2)
#define CLS_RULE_DADDR   (1 << 3)
#define CLS_RULE_SPORT   (1 << 4)
#define CLS_RULE_DPORT   (1 << 5)



/*
 * DIFFERENTIATE SERVICES
 */

/*
 * Connects a DS rule with a DS meter/marker.
 * Each meter/marker can be pointed to by more than one rule
 */
struct ds_map
{
    int filter_id; /* The filter ID when running in DiffServ Multi-Field mode.
                      The value of the DS (i.e. TOS or TCLASS) field when running in
                      Behavior Aggregate mode */
    int ds_id;     /* The ID of the Differentiated Services handler to apply for
                      traffic matching the filter */
};


/*
 * Rule to match traffic
 */

struct ds_filter
{
    int                    id;   /* Id for this filter. Read only for add operation */
    struct classifier_rule rule; /* The rule for this filter */
};


/*
 * name="SimpleMarker" - Structure for the simple marker
 * Matching traffic will be assigned the specified DS field
 * and the specified drop_precedence
 */
struct ds_sm
{
    u_char    mask;            /* DS_SM_xxx bits that determines if what should be done
                                 with matching packets */
    u_char    ds_value;        /* Differentiated Services Field to set (if DS_SM_DS_VAL is set) */
    u_char    drop_precedence; /* The drop precedence, which has to be one of the
                                 IPCOM_PKT_DROP_PRECEDENCE_xxx constants (if DS_SM_DROP_P is set) */
};

#define DS_SM_DS_VAL ((u_char)(1 << 0))
#define DS_SM_DROP_P ((u_char)(1 << 1))


/*
 * name="srTCM" - Structure for the single rate Three Color Marker
 */
struct ds_srtcm
{
    u_char   mode;      /* Mode this meter is operating in, one of the
                           DS_SRTCM_MODE_xxx constants */
    u_long   CIR;       /* Committed Information Rate (bytes/second) */
    u_long   CBS;       /* Committed Burst Size (bytes) */
    u_long   EBS;       /* Excess Burst Size (bytes) */
    u_char   ds_green;  /* Differentiated Services Field to set for green packets */
    u_char   ds_yellow; /* Differentiated Services Field to set for yellow packets */
    u_char   ds_red;    /* Differentiated Services Field to set for red packets */
};

/* The mode that the srTCM can operate in */
#define DS_SRTCM_MODE_COLOR_BLIND 1
#define DS_SRTCM_MODE_COLOR_AWARE 2


/*
 * Differentiated Services ID structure
 */
#define DS_NAME_SIZE  16
struct ds
{
    int  id;                 /* ID of the diffserv handler. Read only for create operation */
    char name[DS_NAME_SIZE]; /* The name of the diffserv handler */
    union ds_data
    {
        struct ds_sm    sm;
        struct ds_srtcm srtcm;
    } d;
};


/*
 * LEAF NETWORK INTERFACE QUEUES
 */

/*
 * ifqueue_fifo
 * Parameter struct used for "fifo" type queue.
 */
struct ifqueue_fifo
{
    u_long fifo_limit; /* Max number of packets that can be queued */
};


/*
 * ifqueue_dpaf
 * Parameter struct used for the Drop Precedence Aware FIFO queue type.
 * This queue type uses more memory and is a little slower compared to the
 * FIFO queue.
 */
struct ifqueue_dpaf
{
    u_long dpaf_limit; /* Max number of packets (regardless of drop
                          precedence) that can be queued */
};


/*
 * ifqueue_netemu
 * Parameter struct used for "netemu" type queue.
 */
struct ifqueue_netemu
{
    u_long  netemu_limit;               /* Max number of packets that can be queued */
    u_long  netemu_min_latency;         /* Minimum latency added to packets in milliseconds */
    u_long  netemu_max_latency;         /* Maximum latency added to packets in milliseconds */
    BOOL    netemu_random_drop;         /* FALSE -> drop every drop_probability packet
                                           TRUE  -> there is 1/every drop_probability
                                           chance that at packet is dropped */
    u_long  netemu_drop_probability;    /* 1 means every packet dropped, 10 means that
                                           every 10 packet is dropped */
    u_long  netemu_drop_pattern;        /* Bit patter where set bit means drop packet
                                           ex: Bit 0 and bit 2 set, all other cleared */
    u_char  netemu_drop_pattern_len;    /* Number of valid bits in "netemu_drop_pattern",
                                           setting the length to zero will have the same effect
                                           as setting bit 0 in the pattern and the length to 1 */
    BOOL    netemu_random_corrupt;      /* FALSE -> corrupt every corrupt_probability packet
                                           TRUE  -> there is 1/every corrupt_probability
                                           chance that a packet is corrupted */
    u_long  netemu_corrupt_probability; /* 1 means every packet corrupted, 10 means tha
                                           every 10 packet is corrupted */
};



/*
 * CONTAINER NETWORK INTERFACE QUEUES
 */

/*
 * ifqueue_filter
 * Determines which interface queue a packet will be queued at in the
 * container queue identified by the filter ID.
 * Diffserv traffic should only use the 'ds' field in the rule, but it is
 * possible to use all supported fields.
 */
struct ifqueue_filter
{
    char   filter_ifname[IFNAMSIZ]; /* Interface name, e.g. "gif1", "gre1" */
    int    filter_id;                  /* Will be set to the ID of the filter for add
                                          and is used to identify the filter on delete */
    int    filter_queue_id;            /* The ID of the queue this filter should
                                          be attached to */
    /* Following fields are only needed for filter add operations */
    int    filter_child_queue_id;      /* The ID of the child that packet matching
                                          this rule should be queued at */
    struct classifier_rule filter_rule;
};



/*
 * ifqueue_container
 * Read only structure that will be filled in by SIOCGIFQUEUE operation.
 */
#define IFQ_CONTAINER_MAX_COUNT 64
struct ifqueue_container
{
    int child_count; /* Number of valid entries in the 'child_ids' array */
    int child_ids[IFQ_CONTAINER_MAX_COUNT]; /* ID of the childs */
};


/*
 * ifqueue_mbc
 * Parameter struct used for "mbc" type queues.
 * This container queue type has 2 or more "bands", filter rules determines
 * which band is used when enqueueing. The rule for dequeueing works like
 * this; packet will be dequeued from band 0 until empty,
 * packets will then be dequeued from band 1 until empty, etc.
 */
struct ifqueue_mbc
{
    struct ifqueue_container mbc_container; /* Read only */
    u_long mbc_bands;        /* Number of bands, must be 2 or more */
    u_long mbc_default_band; /* Index of the band to use for packets that
                                do not match any rule [0..prio_bands) */
};


/*
 * ifqueue_htbc
 * Parameter struct used for "htbc" type queues.
 * The default queue will get all traffic that does not match some other
 * classify rule.
 * Dequeueing is done in by Round-Robin through all childs.
 */
struct ifqueue_htbc
{
    struct ifqueue_container htbc_container; /* Read only */
    u_long  htbc_byterate;    /* Maximum bitrate for this queue */
    u_long  htbc_token_limit; /* Maximum number of tokens this queue
                                 can have, MUST be >MTU of the interface */
    int     htbc_default_id;  /* The ID of the default queue (read-only) */
};


/*
 * ifqueue_qos - ioctl
 * struct used with SIOCxIFQUEUE ioctls.
 */
struct ifqueue_qos
{
    char ifq_name[IFNAMSIZ];   /* if name, e.g. "gif1", "gre1" */
    char ifq_type[IFNAMSIZ];   /* queue type e.g. "fifo", "red" */
    int  ifq_id;               /* Must be an ID that unique on the specified interface or
                                  IFQ_ID_NONE for get operation when the root queue should be returned */
    int ifq_parent_id;         /* ID of the parent queue or IFQ_ID_NONE
                                  if this is directly attached to the interface */
    int ifq_count;             /* Will contain the current number of queued packets
                                  after a SIOCGIFQUEUE call */
    union ifqueue_data
    {
        struct ifqueue_fifo   fifo;
        struct ifqueue_dpaf   dpaf;
        struct ifqueue_netemu netemu;
        struct ifqueue_htbc   htbc;
        struct ifqueue_mbc    mbc;
    } ifq_data;
};

#define IFQ_ID_NONE    0 /* Must be used as parent ID if the queue is a root queue */
#define IFQ_ID_DEFAULT 1 /* Default ID, should be used on root queues where no specific ID is required */


#ifdef __cplusplus
}
#endif

#endif /* !__INCqosh */
