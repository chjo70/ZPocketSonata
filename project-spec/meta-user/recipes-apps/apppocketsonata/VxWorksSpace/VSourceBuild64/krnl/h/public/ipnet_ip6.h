/*
 * Copyright (c) 2006-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* modification history
------------------------
05may14,hax fix V7NET-6 to remove mip code
24apr14,h_x Remove secure NDP and CGA US35689
*/

#ifndef IPNET_IP6_H
#define IPNET_IP6_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Internal IPv6 header file.
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

#include <ipcom_cstyle.h>
#include <ipcom_hash.h>
#include <ipcom_list.h>
#include <ipcom_observer.h>
#include <ipcom_os.h>
#include <ipcom_slab.h>
#include <ipcom_type.h>

#include "ipnet_dst_cache.h"
#include "ipnet_mcast.h"
#include "ipnet_neigh.h"
#include "ipnet_route.h"
#include "ipnet_timeout.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                IPv6 macros (non-standard, use internally only)
 *===========================================================================
 */

/*
 * Set address where the source and/or the destination might be on a
 * word boundary
 */
#define IPNET_IP6_SET_ADDR(dst, src) ipcom_memcpy(dst, src, sizeof(struct Ip_in6_addr))

#define IPNET_IP6_MC_SCOPE(mc_addr)    ((enum Ipnet_ip6_scope) ((mc_addr)->in6.addr8[1] & 0x0f))

/* Reserved address types */
#define IPNET_IP6_SET_SOLICITED_ADDR(dst, src) do { \
        IP_SET_HTONL(&(dst)->in6.addr32[0], 0xff020000); \
        IP_SET_HTONL(&(dst)->in6.addr32[1], 0x00000000); \
        IP_SET_HTONL(&(dst)->in6.addr32[2], 0x00000001); \
        (dst)->in6.addr8[12] = 0xff; \
        (dst)->in6.addr8[13] = (src)->in6.addr8[13]; \
        (dst)->in6.addr16[7] = (src)->in6.addr16[7]; \
    } while((0))

#define IPNET_IP6_SET_ALL_NODES_ADDR(addr) do { \
        IP_SET_HTONL(&(addr)->in6.addr32[0], 0xff020000); \
        IP_SET_32ON16((void *)&(addr)->in6.addr32[1], 0); \
        IP_SET_32ON16((void *)&(addr)->in6.addr32[2], 0); \
        IP_SET_HTONL(&(addr)->in6.addr32[3], 0x00000001); \
    } while((0))

#define IPNET_IP6_SET_ALL_ROUTERS_ADDR(addr) do { \
        IP_SET_HTONL(&(addr)->in6.addr32[0], 0xff020000); \
        IP_SET_32ON16((void *)&(addr)->in6.addr32[1], 0); \
        IP_SET_32ON16((void *)&(addr)->in6.addr32[2], 0); \
        IP_SET_HTONL(&(addr)->in6.addr32[3], 0x00000002); \
    } while((0))

#define IPNET_IP6_IS_SCOPE_LINK_LOCAL(addr) \
    (IP_IN6_IS_ADDR_LINK_LOCAL(addr) || IP_IN6_IS_ADDR_MC_LINKLOCAL(addr))

    /* Unspecified address */
#define IPNET_IP6_IS_ADDR_UNSPECIFIED(addr) \
    (IP_GET_32ON16((void *)&(addr)->in6.addr32[3]) ==0x00000000 && \
    IP_GET_32ON16((void *)&(addr)->in6.addr32[2]) == 0x00000000 && \
    IP_GET_32ON16((void *)&(addr)->in6.addr32[1]) == 0x00000000 && \
    IP_GET_32ON16((void *)&(addr)->in6.addr32[0]) == 0x00000000)

#define IPNET_IP6_IS_ADDR_6TO4(addr) \
    ((addr)->in6.addr16[0] == ip_htons(0x2002))


/* Multicast address types */
#define IPNET_IP6_IS_ADDR_SOLICITED(addr) \
    (IP_GET_32ON16((void *)&(addr)->in6.addr32[0]) == ip_htonl(0xff020000) && \
     IP_GET_32ON16((void *)&(addr)->in6.addr32[1]) == 0x00000000 && \
     IP_GET_32ON16((void *)&(addr)->in6.addr32[2]) == ip_htonl(0x00000001) && \
    (addr)->in6.addr8[12] == 0xff)

#define IPNET_IP6_IS_ADDR_ALL_NODES(addr) \
    (IP_GET_32ON16((void *)&(addr)->in6.addr32[3]) == ip_htonl(0x00000001) && \
    IP_GET_32ON16((void *)&(addr)->in6.addr32[2]) == 0x00000000 && \
    IP_GET_32ON16((void *)&(addr)->in6.addr32[1]) == 0x00000000 && \
    IP_GET_32ON16((void *)&(addr)->in6.addr32[0]) == ip_htonl(0xff020000))


#define IPNET_IP6_CONTINUE_PROCESSING    0
#define IPNET_IP6_STOP_PROCESSING        1


/*
 * Packet flag that might be set on egress ICMPv6 packets to specify
 * the the 'from' address must be the unspecified "::" address.
 */
#define IPNET_IP6_PKT_UNSPECIFIED_SRC_ADDR IPCOM_PKT_FLAG_LINK1

/* Flags that affect source address selection */
#define IPNET_IPV6_REQUIRE_SRC_LINKLOCAL    (1 << 8)  /* The source address must be link local */
#define IPNET_IPV6_EXPLICIT_NETIF           (1 << 9)  /* Explicit netif has been specified     */
#define IPNET_IPV6_REQUIRE_SRC_HOMEADDRESS  (1 << 10) /* Select only home addresses            */

/* Enable legacy support for old RFC2292 sockopt API on linux */
#define IPNET_RFC2292_LEGACY_SUPPORT

/* Old sockopt values used for RFC2292 legacy support */
#define IP_IPV6_2292PKTINFO   2
#define IP_IPV6_2292HOPOPTS   3
#define IP_IPV6_2292DSTOPTS   4
#define IP_IPV6_2292RTHDR     5
#define IP_IPV6_2292HOPLIMIT  8


/* RFC 4007, chapter 6
   ...
   An implementation should also support the concept of a "default"
   zone for each scope.  And, when supported, the index value zero at
   each scope SHOULD be reserved to mean "use the default zone".
   ...
*/
#define IPNET_IP6_DEFAULT_ZONE  0


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         forward declarations
 *===========================================================================
 */
struct Ipnet_data_struct;
struct Ipnet_netif_struct;
struct Ipnet_peer_info_struct;
struct Ipnet_route_policy_selector_struct;
struct Ipnet_socket_struct;


/*
 *===========================================================================
 *                         enum Ipnet_ip6_scope
 *===========================================================================
 * Possible address scopes.
 */
enum Ipnet_ip6_scope {
    IPNET_IP6_SCOPE_MIN         = 0x0,
    IPNET_IP6_SCOPE_NODE_LOCAL  = 0x1,
    IPNET_IP6_SCOPE_LINK_LOCAL  = 0x2,
    IPNET_IP6_SCOPE_SUBNET_LOCAL= 0x3,
    IPNET_IP6_SCOPE_ADMIN_LOCAL = 0x4,
    IPNET_IP6_SCOPE_SITE_LOCAL  = 0x5,
    IPNET_IP6_SCOPE_ORG_LOCAL   = 0x8,
    IPNET_IP6_SCOPE_GLOBAL      = 0xe,
    IPNET_IP6_SCOPE_MAX         = 0xf
};


/*
 *===========================================================================
 *                         Ipnet_ip6_addr_entry
 *===========================================================================
 * IPv6 address entry
 */
typedef struct Ipnet_ip6_addr_entry_struct
{
    /* THIS MEMBER MUST BE FIRST! A list of sockets using this address */
    struct Ipnet_socket_struct         *socket_list;
    /* THIS MEMBER MUST BE SECOND! Next address list */
    struct Ipnet_ip6_addr_entry_struct *next;
    /* Next duplicate address (but on a different network interface) */
    struct Ipnet_ip6_addr_entry_struct *next_dup_addr;
    /* Scope address list */
    struct Ipnet_ip6_addr_entry_struct *scope_prev;
    struct Ipnet_ip6_addr_entry_struct *scope_next;

    /* The interface this address belongs to */
    struct Ipnet_netif_struct          *netif;
    /* The neighbor entry for this address. != IP_NULL on unicast
     * addresses */
    Ipnet_neigh                        *neigh;
    /* The IPv6 address */
    struct Ip_in6_addr                  addr;
    /* Number of bits that represents the network */
    unsigned                            prefixlen;
    /* Number of references to this address */
    int                                 ref_count;
    /* One of the IPNET_ADDR_TYPE_xxx constants */
    enum Ipnet_addr_type                type;
    /* Number of duplicate address detection that has to be done before
       assigning this address */
    int                                 dad_count;
    /* Address flags */
    Ip_u32                              flags;
    /* The address is a preferred address until this time is reached */
    Ip_u32                              preferred_sec;
    /* Time when the address expires */
    Ip_u32                              expires_sec;
#ifdef IPNET_USE_RFC4941
    Ip_u32                              added_sec;
#endif
    /* The timeout structure or IP_NULL if this address does not have a timeout */
    struct Ipnet_timeout_struct        *tmo;

    /*
     * Must observe the state of the neighbor entry that is used to
     * response to ARP requests on this address
     */
    Ipcom_observer                      neigh_observer;

    /* NOTE! This field will only be present if the mode is IPNET_ADDR_TYPE_MULTICAST */
    Ipnet_mcast_addr                    mcast;
}
Ipnet_ip6_addr_entry;

#define IPNET_IP6_ADDR_FLAG_RW_MASK      0xFFFF0000 /* Mask to filter away read only flags */

#define IPNET_IP6_ADDR_FLAG_LOOPBACK_RT  (1 << 0)  /* (read-only) A loopback route was added for
                                                      this address */
#define IPNET_IP6_ADDR_FLAG_NETWORK_RT   (1 << 1)  /* (read-only) A network route was added for
                                                      this address */
#define IPNET_IP6_ADDR_FLAG_MCAST        (1 << 2)  /* (read-only) This address was used to join a
                                                      link layer multicast group */
#define IPNET_IP6_ADDR_FLAG_SOL_MCAST    (1 << 3)  /* (read-only) This address was used to join the
                                                      solicitated multicast group */
#define IPNET_IP6_ADDR_FLAG_DEPRECATED   (1 << 4)  /* (read-only) This use of this address is depricated */
#define IPNET_IP6_ADDR_FLAG_NEWADDR_DONE (1 << 5)  /* (read-only) New address message has been sent for this address */
#define IPNET_IP6_ADDR_FLAG_SUBNET_ANYCAST (1 << 6)  /* (read-only) This unicast address assigned a subnetwork anycast address */

#define IPNET_IP6_ADDR_FLAG_AUTOMATIC    (1 << 16) /* Create with automatic addresses configuration */
#define IPNET_IP6_ADDR_FLAG_AUTONOMOUS   (1 << 17) /* Create as a result of a prefix option with autonomous
                                                      flag set in a router advertisment */
#define IPNET_IP6_ADDR_FLAG_DONT_ADD_NETWORK_RT (1 << 18) /* Do not add the corresponding network route for this address */
#define IPNET_IP6_ADDR_FLAG_HOMEADDRESS  (1 << 19) /* This is a homeaddress */
#define IPNET_IP6_ADDR_FLAG_TEMPORARY    (1 << 20) /* RFC4941 temporary address */
#define IPNET_IP6_ADDR_FLAG_TENTATIVE    (1 << 21) /* This address is a tentative address */
#define IPNET_IP6_ADDR_FLAG_ANYCAST      (1 << 22) /* This is an anycast address */
#define IPNET_IP6_ADDR_FLAG_CGA          (1 << 23) /* Cryptographically Generated Address, used with Secure NDP */
#define IPNET_IP6_ADDR_FLAG_SIT          (1 << 24) /* IPv6-compatibility-IPv4 added by SIT tunnel */
#define IPNET_IP6_ADDR_FLAG_FIRST_NS     (1 << 25) /* Neighbor Solicitation needs to be delayed at
                                                      random RFC 2662, chapter 5.4.2 */

#define IPNET_IP6_ADDR_FLAG_NEXT_TMP_DONE (1 << 30)/* A new temporary address has been generated to take over when
                                                      this address is no longer preferred */
#define IPNET_IP6_ADDR_FLAG_UPDATE_DONE  (1u << 31)/* This address has been processed during a
                                                      batch update */

/*
 *===========================================================================
 *                      ICMPv6 header & types
 *===========================================================================
 */
#include "ipcom_align16.h"
typedef IP_PACKED1 struct Ipnet_icmp6_hdr
{
    Ip_u8   icmp6_type;   /* type field */
    Ip_u8   icmp6_code;   /* code field */
    Ip_u16  icmp6_cksum;  /* checksum field */
    union
    {
        Ip_u32  icmp6_un_data32[1]; /* type-specific field */
        Ip_u16  icmp6_un_data16[2]; /* type-specific field */
        Ip_u8   icmp6_un_data8[4];  /* type-specific field */
    } icmp6_dataun;
}
IP_PACKED2 Ipnet_pkt_icmp6;

#define ipnet_icmp6_data32      icmp6_dataun.icmp6_un_data32
#define ipnet_icmp6_data16      icmp6_dataun.icmp6_un_data16
#define ipnet_icmp6_data8       icmp6_dataun.icmp6_un_data8
#define ipnet_icmp6_pptr        ipnet_icmp6_data32[0]  /* parameter prob */
#define ipnet_icmp6_mtu         ipnet_icmp6_data32[0]  /* packet too big */
#define ipnet_icmp6_id          ipnet_icmp6_data16[0]  /* echo request/reply */
#define ipnet_icmp6_seq         ipnet_icmp6_data16[1]  /* echo request/reply */
#define ipnet_icmp6_maxdelay    ipnet_icmp6_data16[0]  /* mcast group membership */


#define IPNET_ICMPV6_HDR_SIZE  (2 * sizeof(Ip_u32))

/* ICMPv6 error type field, RFC 2463 and RFC 4443 */
#define IPNET_ICMP6_DST_UNREACH         1
#define IPNET_ICMP6_PACKET_TOO_BIG      2
#define IPNET_ICMP6_TIME_EXCEEDED       3
#define IPNET_ICMP6_PARAM_PROB          4

/* ICMPv6 error type field, RFC 4443 only */
#define IPNET_ICMP6_ERR_PRIVATE_1       100
#define IPNET_ICMP6_ERR_PRIVATE_2       101

#define IPNET_ICMP6_ERR_RESERVED        127


/* ICMPv6 information type field, RFC 2463 and RFC 4443 */
#define IPNET_ICMP6_INFOMSG_MASK        0x80 /* all informational messages */

#define IPNET_ICMP6_ECHO_REQUEST        128
#define IPNET_ICMP6_ECHO_REPLY          129

/* ICMPv6 information type field, RFC 4443 only */
#define IPNET_ICMP6_INFO_PRIVATE_1      200
#define IPNET_ICMP6_INFO_PRIVATE_2      201

#define IPNET_ICMP6_INFO_RESERVED       255

/* RFC 4433, chapter 2.1
   ...
   Type values 100, 101, 200, and 201 are reserved for private
   experimentation.  They are not intended for general use.  It is
   expected that multiple concurrent experiments will be done with the
   same type values.  Any wide-scale and/or uncontrolled usage should
   obtain real allocations as defined in Section 6.

   Type values 127 and 255 are reserved for future expansion of the type
   value range if there is a shortage in the future.  The details of
   this are left for future work.  One possible way of doing this that
   would not cause any problems with current implementations is that if
   the type equals 127 or 255, the code field should be used for the new
   assignment.  Existing implementations would ignore the new
   assignments as specified in Section 2.4, (b).  The new messages using
   these expanded type values could assign fields in the message body
   for its code values.
   ...
*/


/*
 *===========================================================================
 *                    ICMPv6 codes for error messages
 *===========================================================================
 */

/* Destination unreachable codes, RFC 2463 and RFC 4443 */
#define IPNET_ICMP6_DST_UNREACH_NOROUTE          0
#define IPNET_ICMP6_DST_UNREACH_ADMIN            1
#define IPNET_ICMP6_DST_UNREACH_BEYONDSCOPE      2
#define IPNET_ICMP6_DST_UNREACH_ADDR             3
#define IPNET_ICMP6_DST_UNREACH_NOPORT           4
/* The following codes are only present in RFC 4443 */
#define IPNET_ICMP6_DST_UNREACH_SRC_ADDR_FAILED  5
#define IPNET_ICMP6_DST_UNREACH_REJECT_DST       6

/* Time Exceeded codes */
#define IPNET_ICMP6_TIME_EXCEEDED_HLIM      0
#define IPNET_ICMP6_TIME_EXCEEDED_FRAG      1

/* Parameter Problem codes */
#define IPNET_ICMP6_PARAM_PROB_ERR_HDR      0
#define IPNET_ICMP6_PARAM_PROB_NXT_HDR      1
#define IPNET_ICMP6_PARAM_PROB_OPT          2



/*
 *===========================================================================
 *                ICMPv6 Multicast Listener Discovery types
 *===========================================================================
 */

/* Multicast Listener Discovery Definitions */
#define IPNET_MLD_LISTENER_QUERY        130
#define IPNET_MLD_V1_LISTENER_REPORT    131
#define IPNET_MLD_V2_LISTENER_REPORT    143
#define IPNET_MLD_LISTENER_REDUCTION    132

typedef IP_PACKED1 struct Ipnet_mld_hdr
{
    Ipnet_pkt_icmp6     mld_icmp6_hdr;
    struct Ip_in6_addr  mcast_addr;
    Ip_u8               s_qrv;
    Ip_u8               qqic;
    Ip_u16              number_of_sources;
    struct Ip_in6_addr  source_addr[1];
}
IP_PACKED2 Ipnet_pkt_mld_hdr;

typedef IP_PACKED1 struct Ipnet_pkt_mldv2_group_record_struct
{
    Ip_u8              record_type;
    Ip_u8              aux_data_len;
    Ip_u16             number_of_sources;
    struct Ip_in6_addr multicast_addr;
    struct Ip_in6_addr source_addr[1];
}
IP_PACKED2 Ipnet_pkt_mldv2_group_record;


typedef IP_PACKED1 struct Ipnet_pkt_mldv2_report_struct
{
    Ip_u8  type;
    Ip_u8  reserved1;
    Ip_u16 checksum;
    Ip_u16 reserved2;
    Ip_u16 number_of_group_records;
    Ipnet_pkt_mldv2_group_record group_records[1];
}
IP_PACKED2 Ipnet_pkt_mldv2_report;

#define IPNET_MLDV1_QUERY_SIZE     24
#define IPNET_MLDV2_MIN_QUERY_SIZE 28

#define ipnet_mld_type          mld_icmp6_hdr.icmp6_type
#define ipnet_mld_code          mld_icmp6_hdr.icmp6_code
#define ipnet_mld_cksum         mld_icmp6_hdr.icmp6_cksum
#define ipnet_mld_maxdelay      mld_icmp6_hdr.ipnet_icmp6_data16[0]
#define ipnet_mld_reserved      mld_icmp6_hdr.ipnet_icmp6_data16[1]

/*
 *===========================================================================
 *           ICMPv6 Multicast Listener Discovery Version 2 types
 *===========================================================================
 */

#define IPNET_MLDV2_LISTENER_REPORT     143

/* MLDv2 query header */
typedef IP_PACKED1 struct Ipnet_mldv2_query_hdr
{
    Ipnet_pkt_icmp6    mld_icmp6_hdr;
    struct Ip_in6_addr mld_addr;    /* Multicast address       */
    Ip_u8              rtval;       /* Reserved + S Flag + QRV */
    Ip_u8              qqic;        /* Queriers query interval */
    Ip_u16             n_src;       /* Number of sources       */
    struct Ip_in6_addr src[1];      /* Source address list     */
}
IP_PACKED2 Ipnet_pkt_mldv2_query_hdr;

/* MLDv2 Query bit field operator macros */
#define IPNET_MLDV2_QRESV(p) (((p->rtval) >> 4) & 0x0f) /* Reserved            */
#define IPNET_MLDV2_SFLAG(p) (((p->rtval) >> 3) & 0x01) /* S flag              */
#define IPNET_MLDV2_QRV(p)   (((p->rtval) & 0x07)       /* robustness variable */

/* MLDv2 Maximum Response Code macros */
#define IPNET_MLDV2_MRC_EXP(p) ((ip_ntohs(p->ipnet_mld_maxdelay) >> 12) & 0x0007)
#define IPNET_MLDV2_MRC_MANT(p) (ip_ntohs(p->ipnet_mld_maxdelay) & 0x0fff)

/* MLDv2 QQIC query interval macros */
#define IPNET_MLDV2_QQIC_EXP(p) (((p->qqic) >> 4) & 0x07)
#define IPNET_MLDV2_QQIC_MAN(p) ((p->qqic) & 0x0f)

/* MLDv2 Query Types */
#define IPNET_MLDV1_QUERY              0
#define IPNET_MLDV2_GENERAL_QUERY      1
#define IPNET_MLDV2_GROUP_QUERY        2
#define IPNET_MLDV2_GROUP_SOURCE_QUERY 3

#define IPNET_MLDV2_REPORT_MIN_SIZE 28

/* MLD minimum query message sizes */
#define IPNET_MLD_QUERY_MINLEN 24
#define IPNET_MLDV2_QUERY_MINLEN 28


/* MLDv2 listener report record */
typedef IP_PACKED1 struct Ipnet_mldv2_report_record
{
    Ip_u8              record_type; /* Record types for membership */
    Ip_u8              auxlen;      /* Length of auxilliary data   */
    Ip_u16             n_src;       /* Number of sources           */
    struct Ip_in6_addr group;       /* Multicast address           */
    struct Ip_in6_addr src[1];      /* Source address list         */
}
IP_PACKED2 Ipnet_pkt_mldv2_report_record;

/* MLDv2 group Record Types in the Membership Report */
#define IPNET_MLDV2_MODE_IS_INCLUDE   1
#define IPNET_MLDV2_MODE_IS_EXCLUDE   2
#define IPNET_MLDV2_CHANGE_TO_INCLUDE 3
#define IPNET_MLDV2_CHANGE_TO_EXCLUDE 4
#define IPNET_MLDV2_ALLOW_NEW_SOURCES 5
#define IPNET_MLDV2_BLOCK_OLD_SOURCES 6


/* MLDv2 listener report header */
typedef IP_PACKED1 struct Ipnet_mldv2_report_hdr
{
    Ipnet_pkt_icmp6     mld_icmp6_hdr;
    struct Ipnet_mldv2_report_record record[1]; /* Multicast address record list */
}
IP_PACKED2 Ipnet_mldv2_report_hdr;

#define ipnet_mldv2_report_reserved    mld_icmp6_hdr.ipnet_icmp6_data16[0]
#define ipnet_mldv2_report_n_record    mld_icmp6_hdr.ipnet_icmp6_data16[1]

/*
 *===========================================================================
 *                ICMPv6 Neighbor Discovery messages
 *===========================================================================
 */

/* Neighbor Discovery ICMPv6 Types */
#define IPNET_ND_ROUTER_SOLICIT         133
#define IPNET_ND_ROUTER_ADVERT          134
#define IPNET_ND_NEIGHBOR_SOLICIT       135
#define IPNET_ND_NEIGHBOR_ADVERT        136
#define IPNET_ND_REDIRECT               137
#define IPNET_ND_CERT_PATH_SOLICIT      148
#define IPNET_ND_CERT_PATH_ADVERT       149

/* Router Advertisement Message */
typedef IP_PACKED1 struct Ipnet_nd_router_advert
{
    Ipnet_pkt_icmp6 nd_ra_hdr;
    Ip_u32          nd_ra_reachable;    /* Reachable time. */
    Ip_u32          nd_ra_retransmit;   /* Retransmission time. */
    /* could be followed by options. */
}
IP_PACKED2 Ipnet_nd_router_advert;

#define ipnet_nd_ra_type                nd_ra_hdr.icmp6_type
#define ipnet_nd_ra_code                nd_ra_hdr.icmp6_code
#define ipnet_nd_ra_cksum               nd_ra_hdr.icmp6_cksum
#define ipnet_nd_ra_curhoplimit         nd_ra_hdr.ipnet_icmp6_data8[0]
#define ipnet_nd_ra_flags_reserved      nd_ra_hdr.ipnet_icmp6_data8[1]
#define IPNET_ND_RA_FLAG_MANAGED        0x80
#define IPNET_ND_RA_FLAG_OTHER          0x40
#define IPNET_ND_RA_FLAG_HOME_AGENT     0x20        /* RFC 3775 */
#define ipnet_nd_ra_router_lifetime     nd_ra_hdr.ipnet_icmp6_data16[1]


/* Neighbor Solicit. */
typedef IP_PACKED1 struct Ipnet_nd_neighbor_solicit
{
    Ipnet_pkt_icmp6     nd_ns_hdr;
    struct Ip_in6_addr  nd_ns_target;   /* target address. */

    /* could be followed by options. */
}
IP_PACKED2 Ipnet_pkt_nd_neighbor_solicit;

#define ipnet_nd_ns_type        nd_ns_hdr.icmp6_type
#define ipnet_nd_ns_code        nd_ns_hdr.icmp6_code
#define ipnet_nd_ns_cksum       nd_ns_hdr.icmp6_cksum
#define ipnet_nd_ns_reserved    nd_ns_hdr.ipnet_icmp6_data32[0]



/* Neighbor Advertisment */
typedef IP_PACKED1 struct Ipnet_nd_neighbor_advert
{
    Ipnet_pkt_icmp6     nd_na_hdr;
    struct Ip_in6_addr  nd_na_target;   /* target address. */

    /* could be followed by options. */
}
IP_PACKED2 Ipnet_pkt_nd_neighbor_advert;

#define ipnet_nd_na_type               nd_na_hdr.icmp6_type
#define ipnet_nd_na_code               nd_na_hdr.icmp6_code
#define ipnet_nd_na_cksum              nd_na_hdr.icmp6_cksum
#define ipnet_nd_na_flags_reserved     nd_na_hdr.ipnet_icmp6_data32[0]

#define IPNET_ND_SET_IS_ROUTER(adv) \
    (adv)->nd_na_hdr.ipnet_icmp6_data16[0] |= ip_htons(0x8000)
#define IPNET_ND_IS_ROUTER(adv) \
    ((adv)->nd_na_hdr.ipnet_icmp6_data16[0] & ip_htons(0x8000))
#define IPNET_ND_SET_SOLICATED_FLAG(adv) \
    (adv)->nd_na_hdr.ipnet_icmp6_data16[0] |= ip_htons(0x4000)
#define IPNET_ND_IS_SOLICATED(adv) \
    ((adv)->nd_na_hdr.ipnet_icmp6_data16[0] & ip_htons(0x4000))
#define IPNET_ND_SET_OVERRIDE_FLAG(adv) \
    (adv)->nd_na_hdr.ipnet_icmp6_data16[0] |= ip_htons(0x2000)
#define IPNET_ND_IS_OVERRIDE(adv) \
    ((adv)->nd_na_hdr.ipnet_icmp6_data16[0] & ip_htons(0x2000))


/* Redirect */
typedef IP_PACKED1 struct Ipnet_nd_redirect
{
    Ipnet_pkt_icmp6         nd_rd_hdr;
    struct Ip_in6_addr      nd_rd_target;   /* Address of better first hop */
    struct Ip_in6_addr      nd_rd_dst;      /* Address of the final host */

    /* could be followed by options. */
}
IP_PACKED2 Ipnet_pkt_nd_redirect;

#define ipnet_nd_rd_type              nd_rd_hdr.icmp6_type
#define ipnet_nd_rd_code              nd_rd_hdr.icmp6_code
#define ipnet_nd_rd_cksum             nd_rd_hdr.icmp6_cksum
#define ipnet_nd_rd_reserved          nd_rd_hdr.icmp6_data32[0]


/*
 *===========================================================================
 *                ICMPv6 Neighbor Discovery options
 *===========================================================================
 */
#define IPNET_ND_OPT_SOURCE_LINKADDR        1
#define IPNET_ND_OPT_TARGET_LINKADDR        2
#define IPNET_ND_OPT_PREFIX_INFORMATION     3
#define IPNET_ND_OPT_REDIRECTED_HEADER      4
#define IPNET_ND_OPT_MTU                    5
#define IPNET_ND_OPT_ADV_INTERVAL           7
#define IPNET_ND_OPT_HOME_AGENT_INFO        8
#define IPNET_ND_OPT_FLAGS_EXPANSION       26

/* ICMPv6 Neighbor Discovery Options Types */
typedef IP_PACKED1 struct Ipnet_nd_opt_hdr
{
    Ip_u8  nd_opt_type;
    Ip_u8  nd_opt_len;
    Ip_u8  nd_opt_data[1];
}
IP_PACKED2 Ipnet_pkt_nd_opt_hdr;

/* Prefix Extension Header Options */
typedef IP_PACKED1 struct Ipnet_nd_opt_prefix_info
{
    Ip_u8  nd_opt_pi_type;
    Ip_u8  nd_opt_pi_len;
    Ip_u8  nd_opt_pi_prefix_len;
    Ip_u8  nd_opt_pi_flags_reserved;
    Ip_u32 nd_opt_pi_valid_time;
    Ip_u32 nd_opt_pi_preferred_time;
    Ip_u32 nd_opt_pi_reserved2;
    struct Ip_in6_addr nd_opt_pi_prefix;
}
IP_PACKED2 Ipnet_pkt_nd_opt_prefix_info;

#define IPNET_ND_OPT_PI_FLAG_ONLINK         0x80
#define IPNET_ND_OPT_PI_FLAG_AUTO           0x40
#define IPNET_ND_OPT_PI_FLAG_ROUTER_ADDRESS 0x20 /* Router Address, RFC 3775 */

/* Redirected Header Options */
typedef IP_PACKED1 struct Ipnet_nd_opt_rh
{
    Ip_u8  nd_opt_rh_type;
    Ip_u8  nd_opt_rh_len;
    Ip_u16 nd_opt_rh_reserved;
    Ip_u32 nd_opt_rh_reserved2;
    /*
     * The original packet truncated to ensure that the size of the
     * redirect message does not exceed 1280 octets.
     */
}
IP_PACKED2 Ipnet_pkt_nd_opt_rh;


/* MTU Header Options */
typedef IP_PACKED1 struct Ipnet_nd_opt_mtu
{
    Ip_u8  nd_opt_mtu_type;
    Ip_u8  nd_opt_mtu_len;
    Ip_u16 nd_opt_mtu_reserved;
    Ip_u32 nd_opt_mtu_mtu;
}
IP_PACKED2 Ipnet_pkt_nd_opt_mtu;


/* RFC 3775: Advertisement Interval Options */
typedef IP_PACKED1 struct Ipnet_nd_opt_adv_interval
{
    Ip_u8  nd_opt_adv_int_type;
    Ip_u8  nd_opt_adv_int_len;
    Ip_u16 nd_opt_adv_int_reserved;
    Ip_u32 nd_opt_adv_int_interval;
}
IP_PACKED2 Ipnet_pkt_nd_opt_adv_interval;

/* RFC 3775: Home Agent Options */
typedef IP_PACKED1 struct Ipnet_nd_opt_home_agent
{
    Ip_u8  nd_opt_ha_type;
    Ip_u8  nd_opt_ha_len;
    Ip_u16 nd_opt_ha_reserved;
    Ip_u16 nd_opt_ha_preference;
    Ip_u16 nd_opt_ha_lifetime;
}
IP_PACKED2 Ipnet_pkt_nd_opt_home_agent;
#   define IPNET_ND_OPT_HOME_AGENT_INFO_MOBILE_ROUTER  0x8000

/* RFC 5175: Flags Expansion Option */
typedef IP_PACKED1 struct Ipnet_nd_opt_flags_expansion
{
    Ip_u8  nd_opt_fe_type;
    Ip_u8  nd_opt_fe_len;
    Ip_u8  nd_opt_fe_flags[6];
}
IP_PACKED2 Ipnet_pkt_nd_opt_flags_expansion;

#define IPNET_ND_OPT_FE_PRIV_0     54  /* Private Experimentation */
#define IPNET_ND_OPT_FE_PRIV_1     55  /* Private Experimentation */

#define _IPNET_ND_OPT_FE_OP(op, opt, bit) \
    op((opt)->nd_opt_fe_flags[(bit - 8) >> 3], 1 << (7 - ((bit - 8) & 7)))

#define IPNET_ND_OPT_FE_BIT_ISSET(opt, bit) _IPNET_ND_OPT_FE_OP(IP_BIT_ISSET, opt, bit)
#define IPNET_ND_OPT_FE_BIT_SET(opt, bit)   _IPNET_ND_OPT_FE_OP(IP_BIT_SET, opt, bit)
#define IPNET_ND_OPT_FE_BIT_CLR(opt, bit)   _IPNET_ND_OPT_FE_OP(IP_BIT_CLR, opt, bit)

/*
 *===========================================================================
 *                         Ipnet_pkt_ip6
 *===========================================================================
 * 40 bytes large IPv6 packet header.
 */
typedef IP_PACKED1 struct Ipnet_pkt_ip6_struct
{
    Ip_u32   ver_class_flow;  /* 4 bit version, 8 bit class, 20 bit flow. */
    Ip_u16   plen;            /* Payload length. */
    Ip_u8    nxt;             /* Next Header. */
    Ip_u8    hlim;            /* Hop limit. */

    struct Ip_in6_addr  src;  /* IPv6 source address. */
    struct Ip_in6_addr  dst;  /* IPv6 destination address. */
}
IP_PACKED2 Ipnet_pkt_ip6;
#include "ipcom_align16.h"

#define IPNET_IP6_HDR_SIZE   (40) /* IPv6 header is 40 octes long */

#define IPNET_IP6_GET_VER(ip6)      (IP_GET_NTOHL(&(ip6)->ver_class_flow) >> 28)
#define IPNET_IP6_SET_VER(ip6,val) \
    do { \
        Ip_u32 ver_class_flow; \
        ver_class_flow = (IP_GET_NTOHL(&(ip6)->ver_class_flow) & 0x0fffffffu) | \
            ((val & 0x0fu) << 28); \
        IP_SET_HTONL(&(ip6)->ver_class_flow, ver_class_flow); \
    } while ((0))
#define IPNET_IP6_GET_CLASS(ip6)   ((Ip_u8) ((IP_GET_NTOHL(&(ip6)->ver_class_flow) >> 20) & 0xff))
#define IPNET_IP6_SET_CLASS(ip6,val) \
    do { \
        Ip_u32 ver_class_flow; \
        ver_class_flow =  (IP_GET_NTOHL(&(ip6)->ver_class_flow) & 0xf00fffffu) | \
            ((val & 0xffu) << 20); \
        IP_SET_HTONL(&(ip6)->ver_class_flow, ver_class_flow); \
    } while ((0))
#define IPNET_IP6_GET_FLOW(ip6)    (IP_GET_NTOHL(&(ip6)->ver_class_flow) & 0xfffff)
#define IPNET_IP6_SET_FLOW(ip6,val) \
    do { \
        Ip_u32 ver_class_flow; \
        ver_class_flow = (IP_GET_NTOHL(&(ip6)->ver_class_flow) & 0xfff00000u) | \
            (val & 0xfffffu); \
        IP_SET_HTONL(&(ip6)->ver_class_flow, ver_class_flow); \
    } while ((0))
#define IPNET_IP6_SET_VER_CLASS_FLOW(ip6,ver,class,flow) \
    IP_SET_HTONL(&(ip6)->ver_class_flow, ((ver) << 28) | ((class) << 20) | (flow))


/*
 *===========================================================================
 *                         Ipnet_ip6_socket
 *===========================================================================
 */

typedef struct Ipnet_ip6_sock_mcast_data_struct
{
    struct Ipnet_ip6_sock_mcast_data_struct *next;
    struct Ipnet_netif_struct               *netif;
    struct Ip_in6_addr                       maddr;
#ifdef IPNET_USE_SOURCE_SPECIFIC_MCAST
    Ipcom_set                               *sources;
#endif
}
Ipnet_ip6_sock_mcast_data;

typedef struct Ipnet_ip6_socket_struct
{
    struct Ip_in6_addr  saddr;        /* source IP address */
    struct Ip_in6_addr  daddr;        /* destination IP address */
    Ip_u32              multicast_if; /* Interface to use for outgoing packets */
    Ip_u16              flags;        /* IPv6 specific socket flags (IPNET_SOCKET_FLAG_IP6_xxx) */
    Ip_u8               tclass;       /* Traffic class to use in IPv6 header when sending */
    Ip_u8               prefer_src_flags; /* IP_IPV6_PREFER_SRC_xxx flags to use in address selection */
    Ip_u32              iscope_id;    /* Internal scope id (in host byte order) */
    Ip_u32              flowinfo;     /* Flow information (in host byte order) */

    struct Ip_in6_pktinfo  *pktinfo;  /* Packet info for sent packet (source address and outgoing interface) */
    struct Ip_sockaddr_in6 *nexthop;  /* The address of the next hop (regardless of the routing table) */

    Ip_pkt_ip6_hbh   *exthdr_hbh;     /* Hop by hop or IP_NULL if no such exist */
    Ip_pkt_ip6_dest  *exthdr_dst;     /* Destination option or IP_NULL if no such exist */
    Ip_pkt_ip6_rthdr *exthdr_rthdr;   /* Routing header or IP_NULL if no such exist */
    Ip_pkt_ip6_dest  *exthdr_rthdrdst;/* Destination option to be placed after routing header or IP_NULL if no such exist */

    /* Multicast addresses joined by this socket */
    Ipnet_ip6_sock_mcast_data *multicast_addr_list;

    struct Ip_icmp6_filter *icmp6_filter;  /* Pointer to the ICMPv6 filter
                                               (!= IP_NULL only for sockets where proto=ICMPv6) */
}
Ipnet_ip6_socket;

#define IPNET_SOCKET_FLAG_IP6_RECVHOPLIMIT  0x0001 /* Return the packet hoplimit of the received packet */
#define IPNET_SOCKET_FLAG_IP6_RECVTCLASS    0x0002 /* Return the packet transport class */
#define IPNET_SOCKET_FLAG_IP6_RECVRTHDR     0x0004 /* Return the packet route header */
#define IPNET_SOCKET_FLAG_IP6_RECVHOPOPTS   0x0008 /* Return the packet hop-by-hop header */
#define IPNET_SOCKET_FLAG_IP6_RECVDSTOPTS   0x0010 /* Return the packet destination header */
#define IPNET_SOCKET_FLAG_IP6_V6ONLY        0x0020 /* Do not accept IPv4 packets using IPv6
                                                      mapped IPv4 addresses on this socket */
#define IPNET_SOCKET_FLAG_IP6_BYPASS_FLOW   0x0080 /* IPSEC bypass flow; don't encrypt */
#define IPNET_SOCKET_FLAG_IP6_RECVENCAP     0x0100 /* Retrieve outer source for tunneled / UDP encap */

/*
 *===========================================================================
 *                    Ipnet_ip6_param
 *===========================================================================
 */

/* Pointer to extension headers */
typedef struct Ipnet_ip6_ext_hdrs_struct
{
    /*WARNING: Do not change order or contents of this structure or IPIPSEC will fail! */
    Ip_size_t        total_len; /* The total length of all extension headers */
    Ip_pkt_ip6_hbh   *hbh;      /* Hop by hop or IP_NULL if no such exist */
    Ip_pkt_ip6_dest  *dst;      /* Destination option or IP_NULL if no such exist */
    Ip_pkt_ip6_rthdr *rthdr0;   /* Routing header type 0 or IP_NULL if no such exist */
    Ip_pkt_ip6_rthdr *rthdr2;   /* Routing Header type 2 or IP_NULL If no such exists */
    Ip_pkt_ip6_dest  *rthdrdst; /* Destination option to be placed after routing header or IP_NULL if no such exist */
}
Ipnet_ip6_ext_hdrs;

typedef struct Ipnet_ip6_output_param_struct
{
    IP_CONST struct Ip_in6_addr *from;
    IP_CONST struct Ip_in6_addr *to;
    IP_CONST struct Ip_in6_addr *final_to;      /* Final destination, != 'to' when using routing header ext.  */
    IP_CONST struct Ip_in6_addr *real_from;     /* Usually same as 'from', may differ when using home option  */

    Ipnet_route_entry   *nexthop;        /* Forced next hop entry */

    /* Mobile Node v6 binding information */
    struct Ipnet_netif_struct   *netif;    /* Interface to use (overrides route entry) or IP_NULL */
    Ip_u16              *chksum_ptr;    /* The pseudo header checksum will be calculated and added to pkt->chk
                                         and stored at this address if != IP_NULL */
    Ip_u32              flowinfo;      /* The flowinfo value in host byte order*/
    Ip_u32              scope_id;      /* The scope ID in host byte order */
    Ip_u8               nxt_hdr;       /* The type of header that was last written */
    Ip_u8               hlim;          /* The hoplimit */
    Ip_u8               tclass;        /* The traffic class */
    Ip_u8               send_icmp6_redirect;  /* != 0 if an ICMPv6 redirect message should be sent
                                                if the input and output interface are the same */
    Ip_u8               has_exthdr;    /* IP_TRUE if 'ext_hdrs' is initialized */
    Ip_u16              src_flags;     /* IP_IPV6_PREFER_SRC_xxx and/or IPNET_IPV6_REQUIRE_SRC_xxx flags*/
    Ipnet_ip6_ext_hdrs  exthdrs;       /* Extension headers to include, only valid if 'has_ext_hdr_data' is IP_TRUE */
}
Ipnet_ip6_output_param;

/* Let the stack select the hop limit */
#define IPNET_IP6_OUTPUT_PARAM_USE_DEFAULT_HLIM  0



/*
 *===========================================================================
 *                     Ipnet_ip6_layer_info
 *===========================================================================
 * This structure holds information that is only valid while the
 * call stack has not exited the IPv6 layer.
 */
typedef struct Ipnet_ip6_layer_info_struct
{
    Ip_u8              nxt;        /* Layer 4 (IP payload) type */
    Ip_u8              hlim;       /* Hop limit */
    Ip_u8              has_frag_hdr; /* !=0 if a fragmentation header
                                      has been added */
    Ip_u32             flowinfo;   /* Flow information (host byte order) */
    Ip_u16            *chksum_ptr; /* Pointer to where the checksum
                                      should be written or IP_NULL */
    Ipnet_neigh       *nexthop;    /* Pointer to the neighbor entry of
                                      the next hop or IP_NULL if the
                                      stack should find the best next
                                      hop */
    Ipnet_ip6_ext_hdrs exthdrs;    /* Extension headers to apply */
}
Ipnet_ip6_layer_info;

/*
 * Macros to store/fetch IPv6 packet information to/from a packet
 */
#define IPNET_IP6_SET_LAYER_INFO(pkt, pinfo) \
    ((pkt)->link_cookie = (Ip_ptrdiff_t) pinfo)
#define IPNET_IP6_GET_LAYER_INFO(pkt) \
    ((Ipnet_ip6_layer_info *) (pkt)->link_cookie)



/* Collection of all local addresses ordered by address scope */
struct Ipnet_ip6_addr_scope
{
    struct Ipnet_ip6_addr_entry_struct *node_local;
    struct Ipnet_ip6_addr_entry_struct *link_local;
    struct Ipnet_ip6_addr_entry_struct *site_local;
    struct Ipnet_ip6_addr_entry_struct *global;

};

/*
 * IPv6 specific data shared by all stack instances.  All data stored
 * here is read-only in the normal case.  All stack instances except
 * the primary one must be suspended before any structure here can be
 * updated unless the member is protected by some other means.
 */
typedef struct Ipnet_ip6_shared_data_struct
{
    /*
     * Maps unicast or multicast address, interface and virtual route
     * tab index to the Ipnet_ip6_addr_entry of the matching local
     * address entry
     */
    Ipcom_hash    *addrs;
    /*
     * Same as above except for that two addresses on different
     * interfaces will occupy the same slot
     */
    Ipcom_hash    *addrs_ignore_if;
    /*
     * Slab cache for IPv6 addresses
     */
    Ipcom_memory_cache *addr_slab;

    /* Local addresses stored according to thier scope */
    struct Ipnet_ip6_addr_scope scope;

#ifdef IPNET_USE_TUNNEL
    /*
     * Hash table of available tunnel interfaces over IPv6
     */
    Ipcom_hash    *tunnel_ifs;
#endif

#ifdef IPNET_USE_RFC4941
    /* The lower 64-bits of the IPv6 address */
    Ip_u8          randomized_if_id[8];
    /* Seed for the next randomized interface identifier */
    Ip_u8          history_value[8];
    /* Random value between [0..MAX_DESYNC_FACTOR] */
    Ip_u32         desync_factor;
#endif
}
Ipnet_ip6_shared_data;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */
IP_GLOBAL int
ipnet_ip6_get_first_nonexthdr(const Ipnet_pkt_ip6 *ip6_hdr,
                              Ip_u8 **noneexthdr);

IP_GLOBAL enum Ipnet_ip6_scope ipnet_ip6_get_addr_scope(IP_CONST struct Ip_in6_addr *addr);
IP_GLOBAL Ipnet_ip6_addr_entry **ipnet_ip6_get_addr_scope_head(enum Ipnet_ip6_scope scope,
                                                               Ipnet_ip6_addr_entry **ae);
IP_GLOBAL void ipnet_ip6_if_configure(struct Ipnet_netif_struct *netif);
IP_GLOBAL void ipnet_ip6_if_unconfigure(struct Ipnet_netif_struct *netif);
IP_GLOBAL Ip_u16 ipnet_ip6_checksum(IP_CONST struct Ip_in6_addr *src,
                                    IP_CONST struct Ip_in6_addr *dst,
                                    Ip_u16 proto,
                                    Ipcom_pkt *pkt);

IP_GLOBAL int  ipnet_ip6_init_once(void);

IP_GLOBAL enum Ipnet_addr_type ipnet_ip6_get_addr_type(IP_CONST struct Ip_in6_addr *ipaddr,
                                                       Ip_u16 vr,
                                                       struct Ipnet_netif_struct *netif);
IP_GLOBAL enum Ipnet_addr_type ipnet_ip6_get_addr_type2(IP_CONST struct Ip_in6_addr *ipaddr,
                                                        struct Ipnet_netif_struct *netif);
IP_GLOBAL Ipnet_ip6_addr_entry *ipnet_ip6_get_addr_entry(IP_CONST struct Ip_in6_addr* ipaddr,
                                                         Ip_u16 vr,
                                                         struct Ipnet_netif_struct *netif);

IP_GLOBAL int ipnet_ip6_input(struct Ipnet_netif_struct *netif, Ipcom_pkt *pkt);
IP_GLOBAL int ipnet_ip6_output(Ipnet_ip6_output_param *param, Ipcom_pkt *pkt);

IP_GLOBAL int ipnet_ip6_sendto(struct Ipnet_socket_struct *sock, IP_CONST struct Ip_msghdr *msg, Ipcom_pkt *pkt);
IP_GLOBAL int ipnet_ip6_tx(struct Ipnet_data_struct *net,
                           Ip_u8 tclass,
                           Ip_u8 hlim,
                           Ip_u8 nxt,
                           Ip_u32 flowinfo,
                           IP_CONST struct Ip_in6_addr *src,
                           IP_CONST struct Ip_in6_addr *dst,
                           Ip_u32 zone_id,
                           Ip_u32 ifindex,
                           Ipcom_pkt *pkt);
IP_GLOBAL Ip_u32 ipnet_ip6_get_mss(struct Ipnet_socket_struct *sock,
                                   Ip_bool *is_link_local);
IP_GLOBAL int ipnet_ip6_get_transport_proto(Ipcom_pkt *pkt);
IP_GLOBAL void ipnet_ip6_transport_rx(Ipnet_dst_cache *dst, Ipcom_pkt *pkt, Ip_u8 proto);


IP_GLOBAL int ipnet_ip6_dst_cache_rx_ctor(Ipnet_dst_cache *dst,
                                          Ipnet_route_entry *rt);

IP_GLOBAL void ipnet_ip6_flow_spec_from_pkt(Ipnet_flow_spec *flow_spec,
                                            const Ipcom_pkt *pkt,
                                            const Ipnet_pkt_ip6 *ip6_hdr,
                                            Ip_bool is_ingress);
IP_GLOBAL int ipnet_ip6_flow_spec_from_info(Ipnet_flow_spec *flow_spec,
                                            const void        *src,
                                            const void        *dst);

IP_GLOBAL Ipnet_dst_cache * ipnet_ip6_dst_cache_get_tx(struct Ipnet_data_struct *net,
                                                       const Ipnet_flow_spec *flow_spec);
IP_GLOBAL int ipnet_ip6_socket2param(struct Ipnet_socket_struct   *sock,
                                     IP_CONST struct Ip_msghdr    *msg,
                                     struct Ip_sockaddr_in6       *to,
                                     Ipnet_ip6_output_param       *param);

IP_GLOBAL const struct Ip_in6_addr *ipnet_ip6_get_src_addr(Ip_u16 vr,
                                                           const struct Ip_in6_addr *dst_addr,
                                                           int scope_id,
                                                           Ipnet_route_entry *rt,
                                                           struct Ipnet_netif_struct *netif,
                                                           Ip_u16 flags);
IP_GLOBAL const struct Ip_in6_addr *ipnet_ip6_get_src_addr_ext(Ip_u16                       vr,
                                                               const struct Ip_in6_addr    *dst_addr,
                                                               int                          scope_id,
                                                               Ipnet_route_entry           *rt,
                                                               struct Ipnet_netif_struct   *arg_netif,
                                                               Ip_u16                       flags,
                                                               Ip_src_addr_filter           filter,
                                                               void *                       filter_arg);

IP_GLOBAL int ipnet_ip6_add_route_table(Ip_u16 vr, Ip_u32 table);
IP_GLOBAL int ipnet_ip6_configure_route_table(Ip_u16 vr, Ip_u32 table);

IP_GLOBAL Ip_u32 ipnet_ip6_pseudo_header_checksum_update(IP_CONST struct Ip_in6_addr *src,
                                                         IP_CONST struct Ip_in6_addr *dst,
                                                         Ip_u16 proto,
                                                         Ip_u16 len);
IP_GLOBAL int ipnet_sock_ip6_flow_spec_from_sock(Ipnet_flow_spec *flow_spec,
                                                 struct Ipnet_socket_struct *sock,
                                                 const void *unused);
IP_GLOBAL Ipnet_ip6_sock_mcast_data ** ipnet_sock_ip6_get_mcast_data(struct Ipnet_socket_struct *sock,
                                                                     struct Ipnet_netif_struct *netif,
                                                                     IP_CONST struct Ip_in6_addr *maddr);
IP_GLOBAL int ipnet_sock_ip6_mcast_delete_data(struct Ipnet_socket_struct *sock,
                                               struct Ipnet_netif_struct *netif,
                                               struct Ip_in6_addr *maddr);
IP_GLOBAL struct Ipnet_socket_struct * ipnet_sock_ip6_lookup(Ip_u16 vr, int proto,
                                                             IP_CONST struct Ip_in6_addr *local_addr, Ip_u16 local_port,
                                                             IP_CONST struct Ip_in6_addr *peer_addr, Ip_u16 peer_port);
IP_GLOBAL int ipnet_ip6_insert_addr_cache(Ipnet_ip6_addr_entry *addr);
IP_GLOBAL void ipnet_ip6_remove_addr_cache(Ipnet_ip6_addr_entry *addr);
IP_GLOBAL int ipnet_ip6_add_addr(struct Ipnet_netif_struct *netif, IP_CONST struct Ip_in6_addr *addr,
                                 Ip_u32 flags, Ip_u32 preferred, Ip_u32 valid, int prefixlen);
IP_GLOBAL int ipnet_ip6_remove_addr(struct Ipnet_netif_struct *netif, IP_CONST struct Ip_in6_addr *addr);
IP_GLOBAL void ipnet_ip6_neigh_state_change(Ipnet_neigh *neigh);
IP_GLOBAL Ip_u32 ipnet_ip6_get_zone(Ip_u32 ifindex, IP_CONST struct Ip_in6_addr *addr);
IP_GLOBAL Ip_bool ipnet_ip6_is_scoped_addr(IP_CONST struct Ip_in6_addr* addr);
IP_GLOBAL Ip_bool ipnet_ip6_is_link_local_addr(IP_CONST struct Ip_in6_addr* addr);
IP_GLOBAL void ipnet_ip6_extract_scoped_addr(struct Ip_sockaddr *sa, Ip_u32 ifindex);

IP_GLOBAL struct Ip_sockaddr * ipnet_ip6_create_sockaddr(struct Ip_sockaddr_in6 *sin6,
                                                         IP_CONST struct Ip_in6_addr *addr,
                                                         Ip_u32 ifindex);
IP_GLOBAL void ipnet_ip6_create_mapped_addr(IP_CONST struct Ip_in_addr *ipv4_addr,
                                            struct Ip_in6_addr *ipv4_mapped_ipv6_addr);

IP_GLOBAL Ip_bool ipnet_ip6_is_part_of_same_pkt(Ipcom_pkt *frag1, Ipcom_pkt *frag2);

IP_GLOBAL void ipnet_ip6_kioevent(struct Ipnet_netif_struct *netif, int command);

IP_GLOBAL int ipnet_ip6_addr_set_timeout(Ipnet_ip6_addr_entry *addr_entry,
                                         Ip_u32 next_timeout_sec,
                                         Ip_bool is_range);

IP_GLOBAL void ipnet_ip6_fragment_timeout(Ipcom_pkt *frag_head);

#ifdef IPNET_USE_MCAST_ROUTING
IP_GLOBAL int ipnet_ip6_mcast_add_mif(struct Ipnet_socket_struct *sock, struct Ip_mif6ctl *mifctl);
IP_GLOBAL int ipnet_ip6_mcast_del_mif(struct Ipnet_socket_struct *sock, Ip_mifi_t mifi);
IP_GLOBAL int ipnet_ip6_mcast_add_mfc(struct Ipnet_socket_struct *sock, struct Ip_mf6cctl *mfcctl);
IP_GLOBAL int ipnet_ip6_mcast_del_mfc(struct Ipnet_socket_struct *sock, struct Ip_mf6cctl *mfcctl);
IP_GLOBAL int ipnet_ip6_mcast_mrt_done(struct Ipnet_socket_struct *sock);
IP_GLOBAL void ipnet_ip6_mcast_set_pim(struct Ipnet_socket_struct *sock, Ip_bool val);
IP_GLOBAL int ipnet_ip6_mcast_getsockopt(struct Ipnet_socket_struct *sock, int optname,
                                         void *optval, Ip_socklen_t *optlen);
IP_GLOBAL int ipnet_ip6_mcast_setsockopt(struct Ipnet_socket_struct *sock, int optname,
                                         IP_CONST void *optval, Ip_socklen_t optlen);
IP_GLOBAL void ipnet_ip6_mcast_input(struct Ipnet_netif_struct *netif, Ipcom_pkt *pkt);
IP_GLOBAL int ipnet_ip6_mcast_ioctl(struct Ipnet_socket_struct *sock, unsigned long request, void *data);
IP_GLOBAL void ipnet_pim_ip6_rx(Ipnet_dst_cache *dst, Ipcom_pkt *pkt);
#endif /* IPNET_USE_MCAST_ROUTING */

IP_GLOBAL void ipnet_sockopt_release_sticky_ip6opts(struct Ipnet_socket_struct *sock);

#ifdef __cplusplus
}
#endif

#endif


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
