/* ipnetlink.h - public netlink structures and definitions */

/*
 * Copyright (c) 2012,2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
/*
modification history
--------------------
24apr14,h_x  Remove secure NDP and CGA US35689
30aug12,fei  Created.
*/

#ifndef __INCipnetlinkh
#define __INCipnetlinkh

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
#ifdef __cplusplus
extern "C" {
#endif

#include <vxWorks.h>

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    NETLINK DEFINITIONS
 *===========================================================================
 */
#define NETLINK_ROUTE                    0       /* Routing/device hook                          */
#define NETLINK_SECY                     1       /* MACsec hook                                  */
#define NETLINK_ROUTE_LINUX_COMPAT       20      /* Internal Netlink Compat Hook                 */

struct sockaddr_nl
{
    u_char            nl_len;
    u_char            nl_family;
    u_short           nl_pad;         /* zero         */
    uint32_t          nl_pid;         /* process pid  */
    uint32_t          nl_groups;      /* multicast groups mask */
    uint32_t          __nl_pad_to_sockaddr_size;
};

struct nlmsghdr
{
    uint32_t          nlmsg_len;      /* Length of message including header */
    u_short          nlmsg_type;     /* Message content */
    u_short          nlmsg_flags;    /* Additional flags */
    uint32_t          nlmsg_seq;      /* Sequence number */
    uint32_t          nlmsg_pid;      /* Sending process PID */
};

/* Flags values */

#define NLM_F_REQUEST           1       /* It is request message.       */
#define NLM_F_MULTI             2       /* Multipart message, terminated by NLMSG_DONE */
#define NLM_F_ACK               4       /* Reply with ack, with zero or error code */
#define NLM_F_ECHO              8       /* Echo this request            */

/* Modifiers to GET request */
#define NLM_F_ROOT      0x100   /* specify tree root    */
#define NLM_F_MATCH     0x200   /* return all matching  */
#define NLM_F_ATOMIC    0x400   /* atomic GET           */
#define NLM_F_DUMP      (NLM_F_ROOT|NLM_F_MATCH)

/* Modifiers to NEW request */
#define NLM_F_REPLACE   0x100   /* Override existing            */
#define NLM_F_EXCL      0x200   /* Do not touch, if it exists   */
#define NLM_F_CREATE    0x400   /* Create, if it does not exist */
#define NLM_F_APPEND    0x800   /* Add to end of list           */

/* Modifiers to ignore VR */
#define NLM_F_VR_UNSPEC 0x8000

/* Linux Compat */
#define NLM_F_LINUX     0x4000

#define NLMSG_ALIGNTO	        4
#define NLMSG_ALIGN(len)      (((len)+NLMSG_ALIGNTO-1) & ~(NLMSG_ALIGNTO-1))
#define NLMSG_LENGTH(len)     ((len) + NLMSG_ALIGN(sizeof(struct nlmsghdr)))
#define NLMSG_SPACE(len)      NLMSG_ALIGN(NLMSG_LENGTH(len))
#define NLMSG_DATA(nlh)       ((void*)(((char*)nlh) + NLMSG_LENGTH(0)))
#define NLMSG_NEXT(nlh,len)   ((len) -= NLMSG_ALIGN((nlh)->nlmsg_len), \
                                  (struct nlmsghdr*)(((char*)(nlh)) + NLMSG_ALIGN((nlh)->nlmsg_len)))
#define NLMSG_OK(nlh,len)     ((len) > 0 \
                                     && (nlh)->nlmsg_len >= sizeof(struct nlmsghdr) \
                                     && (nlh)->nlmsg_len <= (len))
#define NLMSG_PAYLOAD(nlh,len) ((nlh)->nlmsg_len - NLMSG_SPACE((len)))

#define NLMSG_NOOP		    0x1	/* Nothing */
#define NLMSG_ERROR		    0x2	/* Error */
#define NLMSG_DONE		    0x3	/* End of a dump */
#define NLMSG_OVERRUN		0x4	/* Data lost */

/* NLMSG_ERROR */
struct nlmsgerr
{
	int		                error;
	struct nlmsghdr      msg;
};

#define NETLINK_ADD_MEMBERSHIP  1
#define NETLINK_DROP_MEMBERSHIP 2
#define NETLINK_PKTINFO         3

struct nl_pktinfo
{
        uint32_t   group;
};

#define NETLINK_UNCONNECTED  0
#define NETLINK_CONNECTED    1

struct nlattr
{
        u_short           nla_len;
        u_short           nla_type;
};

#define NLA_ALIGNTO             4
#define NLA_ALIGN(len)          (((len) + NLA_ALIGNTO - 1) & ~(NLA_ALIGNTO - 1))
#define NLA_HDRLEN              ((int) NLA_ALIGN(sizeof(struct nlattr)))


/*
 *===========================================================================
 *                    RTNETLINK DEFINITIONS
 *===========================================================================
 */

enum {
        RTNLM_BASE        = 16,
        RTNLM_NEWLINK     = 16,
        RTNLM_DELLINK,
        RTNLM_GETLINK,
        RTNLM_SETLINK,

        RTNLM_NEWADDR     = 20,
        RTNLM_DELADDR,
        RTNLM_GETADDR,

        RTNLM_NEWROUTE    = 24,
        RTNLM_DELROUTE,
        RTNLM_GETROUTE,

        RTNLM_NEWNEIGH    = 28,
        RTNLM_DELNEIGH,
        RTNLM_GETNEIGH,

        RTNLM_NEWRULE     = 32,
        RTNLM_DELRULE,
        RTNLM_GETRULE,

        RTNLM_NEWQDISC    = 36,
        RTNLM_DELQDISC,
        RTNLM_GETQDISC,

        RTNLM_NEWTCLASS   = 40,
        RTNLM_DELTCLASS,
        RTNLM_GETTCLASS,

        RTNLM_NEWTFILTER  = 44,
        RTNLM_DELTFILTER,
        RTNLM_GETTFILTER,

        RTNLM_NEWACTION   = 48,
        RTNLM_DELACTION,
        RTNLM_GETACTION,
        RTNLM_NEWPREFIX   = 52,
        RTNLM_GETPREFIX   = 54,

        RTNLM_GETMULTICAST = 58,

        RTNLM_GETANYCAST  = 62,

        RTNLM_NEWNEIGHTBL = 64,
        RTNLM_GETNEIGHTBL = 66,
        RTNLM_SETNEIGHTBL,

        /* CONFIG INTERPEAK >>> */
        RTNLM_NEWVR       = 100,
        RTNLM_DELVR,
        RTNLM_GETVR,
        RTNLM_CHANGEVR,

        RTNLM_NEWMIP      = 104,
        RTNLM_DELMIP,
        RTNLM_GETMIP,
        RTNLM_SETMIP,

        RTNLM_NEWSEND     = 112,
        RTNLM_GETSEND     = 114,
        RTNLM_SEND_SIGN_REQ     = 115,

        /* proprietary VLAN stacking netlink msgs */
        RTNLM_SETSVLAN    = 120,
        RTNLM_DELSVLAN,

        /* <<< CONFIG INTERPEAK */

        __RTNLM_MAX
};
#define RTNLM_MAX         (((__RTNLM_MAX + 3) & ~3) - 1)

#define RTNLM_NR_MSGTYPES (RTNLM_MAX + 1 - RTNLM_BASE)
#define RTNLM_NR_FAMILIES (RTNLM_NR_MSGTYPES >> 2)
#define RTNLM_FAM(cmd)    (((cmd) - RTNLM_BASE) >> 2)

struct rtattr
{
        u_short  rta_len;
        u_short  rta_type;
};

#define RTA_ALIGNTO              4
#define RTA_ALIGN(len)           ( ((len)+RTA_ALIGNTO-1) & ~(RTA_ALIGNTO-1) )
#define RTA_OK(rta,len)          ((len) >= (int)sizeof(struct rtattr) && \
                                  (rta)->rta_len >= sizeof(struct rtattr) && \
                                  (rta)->rta_len <= (len))
#define RTA_NEXT(rta,attrlen)    ((attrlen) -= (size_t)RTA_ALIGN((rta)->rta_len), \
                                  (struct rtattr*)(((char*)(rta)) + RTA_ALIGN((rta)->rta_len)))
#define RTA_LENGTH(len)          (RTA_ALIGN(sizeof(struct rtattr)) + (len))
#define RTA_SPACE(len)           RTA_ALIGN(RTA_LENGTH(len))
#define RTA_DATA(rta)            ((void*)(((char*)(rta)) + RTA_LENGTH(0)))
#define RTA_PAYLOAD(rta)         ((int)((rta)->rta_len) - RTA_LENGTH(0))

struct rtmsg
{
        u_char           rtm_family;
        u_char           rtm_dst_len;
        u_char           rtm_src_len;
        u_char           rtm_tos;

        u_char           rtm_table;      /* Routing table id */
        u_char           rtm_protocol;   /* Routing protocol; see below  */
        u_char           rtm_scope;      /* See below */
        u_char           rtm_type;       /* See below    */

        uint32_t          rtm_flags;
};

enum
{
        RTN_UNSPEC,
        RTN_UNICAST,            /* Gateway or direct route      */
        RTN_LOCAL,              /* Accept locally               */
        RTN_BROADCAST,          /* Accept locally as broadcast,
                                   send as broadcast */
        RTN_ANYCAST,            /* Accept locally as broadcast,
                                   but send as unicast */
        RTN_MULTICAST,          /* Multicast route              */
        RTN_BLACKHOLE,          /* Drop                         */
        RTN_UNREACHABLE,        /* Destination is unreachable   */
        RTN_PROHIBIT,           /* Administratively prohibited  */
        RTN_THROW,              /* Not in this table            */
        RTN_NAT,                /* Translate this address       */
        RTN_XRESOLVE,           /* Use external resolver        */


        /* CONFIG INTERPEAK >>> */
    	RTN_PROXY        = 32,  /* Proxy ARP route */
        RTN_CLONE,              /* Cloning route */
        /* <<< CONFIG INTERPEAK */

        __RTN_MAX
};

#define RTN_MAX (__RTN_MAX - 1)

#define RTPROT_UNSPEC   0
#define RTPROT_REDIRECT 1       /* Route installed by ICMP redirects;
                                   not used by current IPv4 */
#define RTPROT_KERNEL   2       /* Route installed by kernel            */
#define RTPROT_BOOT     3       /* Route installed during boot          */
#define RTPROT_STATIC   4       /* Route installed by administrator     */

#define RTPROT_GATED    8       /* Apparently, GateD */
#define RTPROT_RA       9       /* RDISC/ND router advertisements */
#define RTPROT_MRT      10      /* Merit MRT */
#define RTPROT_ZEBRA    11      /* Zebra */
#define RTPROT_BIRD     12      /* BIRD */
#define RTPROT_DNROUTED 13      /* DECnet routing daemon */
#define RTPROT_XORP     14      /* XORP */
#define RTPROT_NTK      15      /* Netsukuku */

enum rt_scope_t
{
        RT_SCOPE_UNIVERSE=0,
        RT_SCOPE_SITE=200,
        RT_SCOPE_LINK=253,
        RT_SCOPE_HOST=254,
        RT_SCOPE_NOWHERE=255
};

#define RTM_F_NOTIFY            0x100   /* Notify user of route change  */
#define RTM_F_CLONED            0x200   /* This route is cloned         */
#define RTM_F_EQUALIZE          0x400   /* Multipath equalizer: NI      */
#define RTM_F_PREFIX            0x800   /* Prefix addresses             */

enum rt_class_t
{
        RT_TABLE_UNSPEC=0,
        RT_TABLE_DEFAULT=253,
        RT_TABLE_MAIN=254,
        RT_TABLE_LOCAL=255,
        __RT_TABLE_MAX
};
#define RT_TABLE_MAX (__RT_TABLE_MAX - 1)


enum rtattr_type_t
{
        RTNLA_UNSPEC,
        RTNLA_DST,
        RTNLA_SRC,
        RTNLA_IIF,
        RTNLA_OIF,
        RTNLA_GATEWAY,
        RTNLA_PRIORITY,
        RTNLA_PREFSRC,
        RTNLA_METRICS,
        RTNLA_MULTIPATH,
        RTNLA_PROTOINFO,
        RTNLA_FLOW,
        RTNLA_CACHEINFO,
        RTNLA_SESSION,
        RTNLA_MP_ALGO,
        RTNLA_TABLE,

        /* CONFIG INTERPEAK >>> */
        /* 6 * unsigned char. For storing MAC address in proxy arp routes */
        RTNLA_PROXY_ARP_LLADDR,
        /* unsigned long. Virtual router index. */
        RTNLA_VR,
        /* string (max 16 characters). Route table name */
        RTNLA_TABLE_NAME,
        /* <<< CONFIG INTERPEAK */

        __RTNLA_MAX
};

#define RTNLA_MAX (__RTNLA_MAX - 1)

#define RTNLM_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct rtmsg))))
#define RTNLM_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct rtmsg))


/* CONFIG INTERPEAK >>> */

/* <<< CONFIG INTERPEAK */


struct rtnexthop
{
        u_short          rtnh_len;
        u_char           rtnh_flags;
        u_char           rtnh_hops;
        int          rtnh_ifindex;
};

#define RTNH_F_DEAD             1       /* Nexthop is dead (used by multipath)  */
#define RTNH_F_PERVASIVE        2       /* Do recursive gateway lookup  */
#define RTNH_F_ONLINK           4       /* Gateway is forced on link    */

#define RTNH_ALIGNTO         4
#define RTNH_ALIGN(len)      ( ((len)+RTNH_ALIGNTO-1) & ~(RTNH_ALIGNTO-1) )
#define RTNH_OK(rtnh,len)    ((rtnh)->rtnh_len >= sizeof(struct rtnexthop) && \
                                 ((int)(rtnh)->rtnh_len) <= (len))
#define RTNH_NEXT(rtnh)      ((struct rtnexthop*)(((char*)(rtnh)) + RTNH_ALIGN((rtnh)->rtnh_len)))
#define RTNH_LENGTH(len)     (RTNH_ALIGN(sizeof(struct rtnexthop)) + (len))
#define RTNH_SPACE(len)      RTNH_ALIGN(RTNH_LENGTH(len))
#define RTNH_DATA(rtnh)      ((struct rtattr*)(((char*)(rtnh)) + RTNH_LENGTH(0)))

struct rta_cacheinfo
{
        uint32_t   rta_clntref;
        uint32_t   rta_lastuse;
        int   rta_expires;
        uint32_t   rta_error;
        uint32_t   rta_used;

#define RTNETLINK_HAVE_PEERINFO 1
        uint32_t   rta_id;
        uint32_t   rta_ts;
        uint32_t   rta_tsage;
};

enum
{
        RTNLAX_UNSPEC,
        RTNLAX_LOCK,
        RTNLAX_MTU,
        RTNLAX_WINDOW,
        RTNLAX_RTT,
        RTNLAX_RTTVAR,
        RTNLAX_SSTHRESH,
        RTNLAX_CWND,
        RTNLAX_ADVMSS,
        RTNLAX_REORDERING,
        RTNLAX_HOPLIMIT,
        RTNLAX_INITCWND,
        RTNLAX_FEATURES,
        RTNLAX_RTO_MIN,
        __RTNLAX_MAX
};

#define RTNLAX_MAX (__RTNLAX_MAX - 1)

#define RTNLAX_FEATURE_ECN        0x00000001
#define RTNLAX_FEATURE_SACK       0x00000002
#define RTNLAX_FEATURE_TIMESTAMP  0x00000004
#define RTNLAX_FEATURE_ALLFRAG    0x00000008
struct rta_session
{
        u_char    proto;
        u_char    pad1;
        u_short   pad2;

        union {
                struct {
                        u_short   sport;
                        u_short   dport;
                } ports;

                struct {
                        u_char    type;
                        u_char    code;
                        u_short   ident;
                } icmpt;

                uint32_t           spi;
        } u;
};


/*********************************************************
 *              Interface address.
 ****/

struct ifaddrmsg
{
        u_char   ifa_family;
        u_char   ifa_prefixlen;  /* The prefix length            */
        u_char   ifa_flags;      /* Flags                        */
        u_char   ifa_scope;      /* See above                    */
        int  ifa_index;      /* Link index                   */
};

enum
{
        IFA_UNSPEC,
        IFA_ADDRESS,
        IFA_LOCAL,
        IFA_LABEL,
        IFA_BROADCAST,
        IFA_ANYCAST,
        IFA_CACHEINFO,
        IFA_MULTICAST,

        /* CONFIG_INTERPEAK >>> */
     	IFA_VR       = 32,
     	IFA_TABLE,
     	IFA_TABLE_NAME,
     	IFA_X_INFO,
        /* <<< CONFIG_INTERPEAK */

        __IFA_MAX
};

#define IFA_MAX (__IFA_MAX - 1)

#define IFA_F_SECONDARY         0x01
#define IFA_F_TEMPORARY         IFA_F_SECONDARY

#define IFA_F_NODAD             0x02
#define IFA_F_OPTIMISTIC        0x04
#define IFA_F_CGA               0x08
#define IFA_F_HOMEADDRESS       0x10

#define IFA_F_DEPRECATED        0x20
#define IFA_F_TENTATIVE         0x40
#define IFA_F_PERMANENT         0x80

struct ifa_x_info
{
    uint32_t  ifa_x_flags;
};

#define IFA_F_X_AUTONOM      0x01
#define IFA_F_X_ONLINK       0x02
#define IFA_F_X_AUTOMATIC    0x04
#define IFA_F_X_INACCESSIBLE 0x08
#define IFA_F_X_PREFERRED    0x10

struct ifa_cacheinfo
{
        uint32_t   ifa_prefered;
        uint32_t   ifa_valid;
        uint32_t   cstamp; /* created timestamp, hundredths of seconds */
        uint32_t   tstamp; /* updated timestamp, hundredths of seconds */
};
#define IFA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ifaddrmsg))))
#define IFA_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct ifaddrmsg))


struct ndmsg
{
        u_char   ndm_family;
        u_char   ndm_pad1;
        u_short  ndm_pad2;
        int  ndm_ifindex;    /* Link index                   */
        u_short  ndm_state;
        u_char   ndm_flags;
        u_char   ndm_type;
};

enum
{
        NDA_UNSPEC,
        NDA_DST,
        NDA_LLADDR,
        NDA_CACHEINFO,
        NDA_PROBES,

        /* CONFIG_INTERPEAK >>>*/
        NDA_VR   = 32,
        NDA_TABLE,
        NDA_TABLE_NAME,
        NDA_REALIFINDEX,
        /* <<< CONFIG_INTERPEAK */

        __NDA_MAX
};

#define NDA_MAX (__NDA_MAX - 1)

#define NDA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ndmsg))))
#define NDA_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct ndmsg))

#define NTF_PROXY       0x08    /* == ATF_PUBL */
#define NTF_ROUTER      0x80
/* CONFIG INTERPEAK >>>*/
#define NTF_GRAT        0x10
/* <<< CONFIG INTERPEAK */

#define NUD_INCOMPLETE  0x01
#define NUD_REACHABLE   0x02
#define NUD_STALE       0x04
#define NUD_DELAY       0x08
#define NUD_PROBE       0x10
#define NUD_FAILED      0x20

/* Dummy states */
#define NUD_NOARP       0x40
#define NUD_PERMANENT   0x80
#define NUD_NONE        0x00


struct nda_cacheinfo
{
        uint32_t           ndm_confirmed;
        uint32_t           ndm_used;
        uint32_t           ndm_updated;
        uint32_t           ndm_refcnt;
};
struct ndt_stats
{
        uint64_t           ndts_allocs;
        uint64_t           ndts_destroys;
        uint64_t           ndts_hash_grows;
        uint64_t           ndts_res_failed;
        uint64_t           ndts_lookups;
        uint64_t           ndts_hits;
        uint64_t           ndts_rcv_probes_mcast;
        uint64_t           ndts_rcv_probes_ucast;
        uint64_t           ndts_periodic_gc_runs;
        uint64_t           ndts_forced_gc_runs;
};

enum {
        NDTPA_UNSPEC,
        NDTPA_IFINDEX,                  /* __u32, unchangeable */
        NDTPA_REFCNT,                   /* __u32, read-only */
        NDTPA_REACHABLE_TIME,           /* __u64, read-only, msecs */
        NDTPA_BASE_REACHABLE_TIME,      /* __u64, msecs */
        NDTPA_RETRANS_TIME,             /* __u64, msecs */
        NDTPA_GC_STALETIME,             /* __u64, msecs */
        NDTPA_DELAY_PROBE_TIME,         /* __u64, msecs */
        NDTPA_QUEUE_LEN,                /* __u32 */
        NDTPA_APP_PROBES,               /* __u32 */
        NDTPA_UCAST_PROBES,             /* __u32 */
        NDTPA_MCAST_PROBES,             /* __u32 */
        NDTPA_ANYCAST_DELAY,            /* __u64, msecs */
        NDTPA_PROXY_DELAY,              /* __u64, msecs */
        NDTPA_PROXY_QLEN,               /* __u32 */
        NDTPA_LOCKTIME,                 /* __u64, msecs */
        __NDTPA_MAX
};
#define NDTPA_MAX (__NDTPA_MAX - 1)

struct ndtmsg
{
        u_char            ndtm_family;
        u_char            ndtm_pad1;
        u_short           ndtm_pad2;
};

struct ndt_config
{
        u_short           ndtc_key_len;
        u_short           ndtc_entry_size;
        uint32_t           ndtc_entries;
        uint32_t           ndtc_last_flush;        /* delta to now in msecs */
        uint32_t           ndtc_last_rand;         /* delta to now in msecs */
        uint32_t           ndtc_hash_rnd;
        uint32_t           ndtc_hash_mask;
        uint32_t           ndtc_hash_chain_gc;
        uint32_t           ndtc_proxy_qlen;
};

enum {
        NDTA_UNSPEC,
        NDTA_NAME,                      /* char *, unchangeable */
        NDTA_THRESH1,                   /* __u32 */
        NDTA_THRESH2,                   /* __u32 */
        NDTA_THRESH3,                   /* __u32 */
        NDTA_CONFIG,                    /* struct ndt_config, read-only */
        NDTA_PARMS,                     /* nested TLV NDTPA_* */
        NDTA_STATS,                     /* struct ndt_stats, read-only */
        NDTA_GC_INTERVAL,               /* __u64, msecs */
        __NDTA_MAX
};
#define NDTA_MAX (__NDTA_MAX - 1)

#define NDTA_RTA(r) ((struct rtattr*)(((char*)(r)) + \
                     NLMSG_ALIGN(sizeof(struct ndtmsg))))
#define NDTA_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct ndtmsg))


struct rtgenmsg
{
        u_char           rtgen_family;
};

struct ifinfomsg
{
        u_char   ifi_family;
        u_char   __ifi_pad;
        u_short  ifi_type;               /* ARPHRD_* */
        int  ifi_index;              /* Link index   */
        uint32_t  ifi_flags;              /* IFF_* flags  */
        uint32_t  ifi_change;             /* IFF_* change mask */
};

/********************************************************************
 *              prefix information
 ****/

struct prefixmsg
{
        u_char   prefix_family;
        u_char   prefix_pad1;
        u_short  prefix_pad2;
        int  prefix_ifindex;
        u_char   prefix_type;
        u_char   prefix_len;
        u_char   prefix_flags;
        u_char   prefix_pad3;
};
enum
{
        PREFIX_UNSPEC,
        PREFIX_ADDRESS,
        PREFIX_CACHEINFO,

    /* CONFIG_INTERPEAK >>> */
        PREFIX_VR    = 16,
    /* <<< CONFIG_INTERPEAK */

        __PREFIX_MAX
};

#define PREFIX_MAX      (__PREFIX_MAX - 1)

struct prefix_cacheinfo
{
        uint32_t   preferred_time;
        uint32_t   valid_time;
};

struct rtnl_link_stats
{
        uint32_t   rx_packets;             /* total packets received       */
        uint32_t   tx_packets;             /* total packets transmitted    */
        uint32_t   rx_bytes;               /* total bytes received         */
        uint32_t   tx_bytes;               /* total bytes transmitted      */
        uint32_t   rx_errors;              /* bad packets received         */
        uint32_t   tx_errors;              /* packet transmit problems     */
        uint32_t   rx_dropped;             /* no space in linux buffers    */
        uint32_t   tx_dropped;             /* no space available in linux  */
        uint32_t   multicast;              /* multicast packets received   */
        uint32_t   collisions;

        /* detailed rx_errors: */
        uint32_t   rx_length_errors;
        uint32_t   rx_over_errors;         /* receiver ring buff overflow  */
        uint32_t   rx_crc_errors;          /* recved pkt with crc error    */
        uint32_t   rx_frame_errors;        /* recv'd frame alignment error */
        uint32_t   rx_fifo_errors;         /* recv'r fifo overrun          */
        uint32_t   rx_missed_errors;       /* receiver missed packet       */

        /* detailed tx_errors */
        uint32_t   tx_aborted_errors;
        uint32_t   tx_carrier_errors;
        uint32_t   tx_fifo_errors;
        uint32_t   tx_heartbeat_errors;
        uint32_t   tx_window_errors;

        /* for cslip etc */
        uint32_t   rx_compressed;
        uint32_t   tx_compressed;
};

struct rtnl_link_ifmap
{
        uint64_t   mem_start;
        uint64_t   mem_end;
        uint64_t   base_addr;
        u_short   irq;
        u_char    dma;
        u_char    port;
};

enum
{
        IFLA_UNSPEC,
        IFLA_ADDRESS,
        IFLA_BROADCAST,
        IFLA_IFNAME,
        IFLA_MTU,
        IFLA_LINK,
        IFLA_QDISC,
        IFLA_STATS,
        IFLA_COST,
        IFLA_PRIORITY,
        IFLA_MASTER,
        IFLA_WIRELESS,          /* Wireless Extension event - see wireless.h */
        IFLA_PROTINFO,          /* Protocol specific information for a link */
        IFLA_TXQLEN,
        IFLA_MAP,
        IFLA_WEIGHT,
        IFLA_OPERSTATE,
        IFLA_LINKMODE,
        IFLA_LINKINFO,

        /* CONFIG_INTERPEAK >>>*/
        IFLA_VR = 32,
        /* <<< CONFIG_INTERPEAK */
        __IFLA_MAX
};


#define IFLA_MAX (__IFLA_MAX - 1)

#define IFLA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct ifinfomsg))))
#define IFLA_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct ifinfomsg))

enum
{
        IFLA_INET6_UNSPEC,
        IFLA_INET6_FLAGS,       /* link flags                   */
        IFLA_INET6_CONF,        /* sysctl parameters            */
        IFLA_INET6_STATS,       /* statistics                   */
        IFLA_INET6_MCAST,       /* MC things. What of them?     */
        IFLA_INET6_CACHEINFO,   /* time values and max reasm size */
        IFLA_INET6_ICMP6STATS,  /* statistics (icmpv6)          */
        __IFLA_INET6_MAX
};

#define IFLA_INET6_MAX  (__IFLA_INET6_MAX - 1)

struct ifla_cacheinfo
{
        uint32_t   max_reasm_len;
        uint32_t   tstamp;         /* ipv6InterfaceTable updated timestamp */
        uint32_t   reachable_time;
        uint32_t   retrans_time;
};

enum
{
        IFLA_INFO_UNSPEC,
        IFLA_INFO_KIND,
        IFLA_INFO_DATA,
        IFLA_INFO_XSTATS,
        __IFLA_INFO_MAX
};

#define IFLA_INFO_MAX   (__IFLA_INFO_MAX - 1)

/* BOND section */
enum
{
    IFLA_BOND_UNSPEC,
    IFLA_BOND_XMIT_POLICY,
    IFLA_BOND_LAG_MEMBER,
	__IFLA_BOND_MAX
};

#define IFLA_BOND_MAX   (__IFLA_BOND_MAX - 1)

struct ifla_bond_lag {
    uint32_t ifindex;
    uint32_t enabled;
};

enum
{
        IFLA_VLAN_UNSPEC,
        IFLA_VLAN_ID,
        IFLA_VLAN_FLAGS,
        IFLA_VLAN_EGRESS_QOS,
        IFLA_VLAN_INGRESS_QOS,
        __IFLA_VLAN_MAX
};

#define IFLA_VLAN_MAX   (__IFLA_VLAN_MAX - 1)

struct ifla_vlan_flags {
        uint32_t   flags;
        uint32_t   mask;
};

enum
{
        IFLA_VLAN_QOS_UNSPEC,
        IFLA_VLAN_QOS_MAPPING,
        __IFLA_VLAN_QOS_MAX
};

#define IFLA_VLAN_QOS_MAX       (__IFLA_VLAN_QOS_MAX - 1)

struct ifla_vlan_qos_mapping
{
        uint32_t from;
        uint32_t to;
};


/*****************************************************************
 *              Traffic control messages.
 ****/

struct tcmsg
{
        u_char   tcm_family;
        u_char   tcm__pad1;
        u_short  tcm__pad2;
        int  tcm_ifindex;
        uint32_t  tcm_handle;
        uint32_t  tcm_parent;
        uint32_t  tcm_info;
};

enum
{
        TCA_UNSPEC,
        TCA_KIND,
        TCA_OPTIONS,
        TCA_STATS,
        TCA_XSTATS,
        TCA_RATE,
        TCA_FCNT,
        TCA_STATS2,
        __TCA_MAX
};

#define TCA_MAX (__TCA_MAX - 1)

#define TCA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct tcmsg))))
#define TCA_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct tcmsg))

/* RTnetlink multicast groups - backwards compatibility for userspace */
#define NLMSG_GROUP_MASK(group)  ((group)? (1 << ((group) - 1)) : 0)

/* RTnetlink multicast groups */
enum rtnetlink_groups {
        RTNLGRP_NONE,
        RTNLGRP_LINK,
        RTNLGRP_NOTIFY,
        RTNLGRP_NEIGH,
        RTNLGRP_TC,
        RTNLGRP_IPV4_IFADDR,
        RTNLGRP_IPV4_MROUTE,
        RTNLGRP_IPV4_ROUTE,
        RTNLGRP_IPV4_RULE,
        RTNLGRP_IPV6_IFADDR,
        RTNLGRP_IPV6_MROUTE,
        RTNLGRP_IPV6_ROUTE,
        RTNLGRP_IPV6_IFINFO,
        RTNLGRP_DECnet_IFADDR,
        RTNLGRP_NOP2,
        RTNLGRP_DECnet_ROUTE,
        RTNLGRP_DECnet_RULE,
/* CONFIG INTERPEAK >>> */
        RTNLGRP_RTAB,
/* <<< CONFIG INTERPEAK */
        RTNLGRP_NOP4,
        RTNLGRP_IPV6_PREFIX,
        RTNLGRP_IPV6_RULE,
        __RTNLGRP_MAX
};
#define RTNLGRP_MAX     (__RTNLGRP_MAX - 1)


#define RTMGRP_LINK             NLMSG_GROUP_MASK(RTNLGRP_LINK)
#define RTMGRP_NOTIFY           NLMSG_GROUP_MASK(RTNLGRP_NOTIFY)
#define RTMGRP_NEIGH            NLMSG_GROUP_MASK(RTNLGRP_NEIGH)
#define RTMGRP_TC               NLMSG_GROUP_MASK(RTNLGRP_TC)

#define RTMGRP_IPV4_IFADDR      NLMSG_GROUP_MASK(RTNLGRP_IPV4_IFADDR)
#define RTMGRP_IPV4_MROUTE      NLMSG_GROUP_MASK(RTNLGRP_IPV4_MROUTE)
#define RTMGRP_IPV4_ROUTE       NLMSG_GROUP_MASK(RTNLGRP_IPV4_ROUTE)
#define RTMGRP_IPV4_RULE        NLMSG_GROUP_MASK(RTNLGRP_IPV4_RULE)

#define RTMGRP_IPV6_IFADDR      NLMSG_GROUP_MASK(RTNLGRP_IPV6_IFADDR)
#define RTMGRP_IPV6_MROUTE      NLMSG_GROUP_MASK(RTNLGRP_IPV6_MROUTE)
#define RTMGRP_IPV6_ROUTE       NLMSG_GROUP_MASK(RTNLGRP_IPV6_ROUTE)
#define RTMGRP_IPV6_IFINFO      NLMSG_GROUP_MASK(RTNLGRP_IPV6_IFINFO)

#define RTMGRP_DECnet_IFADDR    NLMSG_GROUP_MASK(RTNLGRP_DECnet_IFADDR)
#define RTMGRP_DECnet_ROUTE     NLMSG_GROUP_MASK(RTNLGRP_DECnet_ROUTE)

#define RTMGRP_IPV6_PREFIX      NLMSG_GROUP_MASK(RTNLGRP_IPV6_PREFIX)
/* CONFIG INTERPEAK >>> */
#define RTMGRP_RTAB             NLMSG_GROUP_MASK(RTNLGRP_RTAB)
/* <<< CONFIG INTERPEAK */


/* TC action piece */
struct tcamsg
{
        u_char   tca_family;
        u_char   tca__pad1;
        u_short  tca__pad2;
};
#define TA_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct tcamsg))))
#define TA_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct tcamsg))
#define TCA_ACT_TAB 1 /* attr type must be >=1 */
#define TCAA_MAX 1

/* RULE handling */

#define FIB_RULE_PERMANENT	    0x00000001
#define FIB_RULE_INVERT		    0x00000002
#define FIB_RULE_UNRESOLVED	    0x00000004
#define FIB_RULE_DEV_DETACHED	0x00000008

#define FIB_RULE_FIND_SADDR	    0x00010000

struct fib_rule_hdr
{
	u_char		family;
	u_char		dst_len;
	u_char		src_len;
	u_char		tos;

	u_char		table;
	u_char		res1;	/* reserved */
	u_char		res2;	/* reserved */
	u_char		action;

	uint32_t	    flags;
};

enum
{
	FRA_UNSPEC,
	FRA_DST,
	FRA_SRC,
	FRA_IFNAME,
	FRA_GOTO,
	FRA_UNUSED2,
	FRA_PRIORITY,
	FRA_UNUSED3,
	FRA_UNUSED4,
	FRA_UNUSED5,
	FRA_FWMARK,
	FRA_FLOW,
	FRA_UNUSED6,
	FRA_UNUSED7,
	FRA_UNUSED8,
	FRA_TABLE,
	FRA_FWMASK,

/* CONFIG INTERPEAK >>> */
    FRA_PROTOCOL     = 32,
    FRA_SCOPE,
    FRA_EXTACT,
    FRA_VR,
    FRA_ID,
/* <<< CONFIG INTERPEAK */

	__FRA_MAX
};

#define FRA_MAX (__FRA_MAX - 1)

/* CONFIG INTERPEAK >>> */
#define FRA_PKT_TUNNELED     0x00000001
#define FRA_PKT_FORWARDED    0x00000002

#define FRA_EXT_RT_SRC_ADDR  0x00000001
/* <<< CONFIG INTERPEAK */

enum
{
	FR_ACT_UNSPEC,
	FR_ACT_TO_TBL,
	FR_ACT_GOTO,
	FR_ACT_NOP,
	FR_ACT_RES3,
	FR_ACT_RES4,
	FR_ACT_BLACKHOLE,
	FR_ACT_UNREACHABLE,
	FR_ACT_PROHIBIT,
	__FR_ACT_MAX
};


/* CONFIG INTERPEAK >>> */
/* VR attributes */
struct vrmsg
{
        u_char   vr_family;
        u_char   __vr_pad1;
        u_short  __vr_pad2;
        uint32_t  vr_vr;
};

enum vrattr_type_t
{
    VR_UNSPEC,
    VR_VR,
    VR_IFNAME,
    VR_TABLE,
    VR_TABLE_NAME,
    VR_IFNAMES,
    VR_TABLES,
    __VR_MAX
};
#define VR_MAX (__VR_MAX - 1)

enum vrxattr_type_t
{
    VRX_UNSPEC,
    VRX_IFNAME,
    VRX_TABLE,
    VRX_TABLE_NAME,
    __VRX_MAX
};

#define VRX_MAX (__VRX_MAX - 1)
#define VR_RTA(r)  ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct vrmsg))))
#define VR_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct vrmsg))

struct mipmsg
{
        u_char   mip_family;
        u_char   mip_flags;
        u_short  mip_type;
};

enum mipattr_type_t
{
    MIP_UNSPEC,
    MIP_ENCAP,
    __MIP_MAX
};

#define MIP_MAX (__MIP_MAX - 1)

#define MIP_RTA(r)     ((struct rtattr*)(((char*)(r)) + NLMSG_ALIGN(sizeof(struct mipmsg))))
#define MIP_PAYLOAD(n) NLMSG_PAYLOAD(n,sizeof(struct rtgenmsg))


/* <<< CONFIG INTERPEAK */


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
