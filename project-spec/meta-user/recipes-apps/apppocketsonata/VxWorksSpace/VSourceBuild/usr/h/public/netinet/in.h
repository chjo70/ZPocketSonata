/* in.h - internet header file */

/*
 * Copyright (c) 1984-2007, 2009-2010, 2012, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
 * Copyright (c) 2002 INRIA. All rights reserved.
 *
 * Implementation of Internet Group Management Protocol, Version 3.
 * Developed by Hitoshi Asaeda, INRIA, February 2002.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of INRIA nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1982, 1986, 1990, 1993
 *      The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SER Added IP_MULTICAST_IF structure definition.VICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      @(#)in.h        8.3 (Berkeley) 1/3/94
 * $FreeBSD: src/sys/netinet/in.h,v 1.48.2.12 2004/06/16 06:57:49 ru Exp $
 * $FreeBSD: src/sys/netinet/in.h,v 1.48.2.11 2003/09/09 19:09:22 bms Exp $
 */

/*
modification history
--------------------
05nov15,kjn  Replaced u_char, u_short and u_int32_t with VxWorks types UINT8,
             UINT16 and UINT32. Added explicit cast to htons(), htonl(),
             ntohs() and ntohl() to UINT16 for the short and UINT32 for the
             long as that is the signature specified by POSIX.1-2001.
27aug15,kjn  Including <netinet/in.h> must result in struct in6_addr being
             defined, this header now includes <netinet6/in6.h>
13jan15,dlk  Adding IPPROTO_SCTP.
09jan12,h_x  Move extern "C" after last header file include.
22jun10,h_x  Fix WIND00219346
07may09,kjn  Added definition of struct in_pktinfo.
12jul07,kch  Restore multicast sockopts number and the required group_req
             and group_source_req argument structures (WIND00102340).
20nov06,kch  Removed unsupported group_filter structure and related
             defines. Added ip_mreqn structure definition.
25oct06,kch  Removed Kame specific ip_msfilter and ip_mreq_source
             structures. Added new socket options for IP_RECVTTL,
             IP_RECVTOS, IP_UDP_XCHKSUM, IP_NAT, IP_FW, IP_NEXTHOP,
             IP_X_SENDERLINKADDR and IP_X_VRID.
12sep06,kch  Removed obsolete prototypes and unsupported proto defines
             for IPNet integration.
03feb06,spw  Correct IN_ADDR_IS_LINKLOCAL macro
25aug05,dlk  Add section tags.
18may05,kch  Merged from FreeBSD v 1.48.2.12.
19apr05,rp   merged from comp_wn_ipv6_mld_interim-dev
18apr05,vvv  included in6.h for user-space
03mar05,vvv  removed reference to _KERNEL
25feb05,niq  merge from niqbal.tor3.mroute for IP router alert changes
17feb05,dlk  NTOHL() etc. only usable as statements, not expressions.
07feb05,vvv  _KERNEL cleanup
24jan05,vvv  osdep.h cleanup
20jan05,sar  Removal of divert, dummynet and fw code.
14oct04,nee  include osdep.h and machdep.h when _KERNEL is defined
             (SPR #102593)
31may04,nee  Adding macro IN_ADDR_IS_LINKLOCAL
25nov03,ppp  added a comment before the inclusion of in6.h
21nov03,ppp  rtp work
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
23oct03,rlm  updated #includes for header re-org
07aug03,niq  Merging from Accordion label ACCORDION_BASE6_MERGE_BASELINE
13jun03,syy  Added declaration for inet_ntoa_b() (SPR#88384)
15may03,vvv  included mbuf.h
09may03,vvv  included vxWorks.h
01feb03,pas  merge from FreeBSD 4.7 - moved satosin() etc here
09sep02,hsh  add c++ protection
15jul02,ann  moved the early declaration of some structures to avoid
             compilation warnings
08feb02,nee  making in_socktrim non static
02oct01,ppp  Removing the INET6 guard fot in6.h
18sep01,qli  fixed a header inclusion error
18sep01,ppp  guarding the inclusion of in6.h by INET6 for the link
             temporarily
23aug01,ppp  Adding the WindRiver copyright
08aug01,ppp  Created from FreeBSD 4.3
*/

#ifndef _NETINET_IN_H_
#define _NETINET_IN_H_

#include <vxWorks.h>

/*
 * According to IEEE Std 1003.1, 2004 Edition
 *
 * The <netinet/in.h> header shall define the sockaddr_in6 structure...
 */
#include <netinet6/in6.h>

#ifdef _WRS_KERNEL
#include <net/mbuf.h>
#endif

#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981, and numerous additions.
 */

/*
 * Protocols (RFC 1700)
 * Also http://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml
 */
#define IPPROTO_IP      0       /* dummy for IP */
#define IPPROTO_HOPOPTS 0       /* IP6 hop-by-hop options */
#define IPPROTO_ICMP    1       /* control message protocol */
#define IPPROTO_IGMP    2       /* group mgmt protocol */
#define IPPROTO_IPV4    4       /* IPv4 encapsulation */
#define IPPROTO_IPIP    IPPROTO_IPV4    /* for compatibility */
#define IPPROTO_TCP     6       /* tcp */
#define IPPROTO_UDP     17      /* user datagram protocol */
#define IPPROTO_IPV6    41      /* IP6 header */
#define IPPROTO_RSVP    46      /* resource reservation */
#define IPPROTO_GRE     47      /* General Routing Encap. */
#define IPPROTO_ESP     50      /* IP6 Encap Sec. Payload */
#define IPPROTO_AH      51      /* IP6 Auth Header */
#define IPPROTO_MOBILE  55      /* IP Mobility */
#define IPPROTO_ICMPV6  58      /* ICMP6 */
#define IPPROTO_OSPFIGP 89      /* OSPFIGP */
#define IPPROTO_PIM     103     /* Protocol Independent Mcast */
#define IPPROTO_L2TP    115     /* L2TP   */
#define IPPROTO_SCTP    132     /* Stream Control Transmission Protocol  */
#define IPPROTO_MH      135     /* IPv6 Mobility Header */
#define IPPROTO_UDPLITE 136     /* UDP-Lite (RFC3828) */
/* 255: Reserved */
/* BSD Private, local use, namespace incursion */
#define IPPROTO_RAW     255     /* raw IP packet */
#define IPPROTO_MAX     256

/* last return value of *_input(), meaning "all job for this pkt is done".  */
#define IPPROTO_DONE    257

/*
 * Local port number conventions:
 *
 * When a user does a bind(2) or connect(2) with a port number of zero,
 * a non-conflicting local port address is chosen.
 * The default range is IPPORT_RESERVED through
 * IPPORT_USERRESERVED, although that is settable by sysctl.
 *
 * A user may set the IPPROTO_IP option IP_PORTRANGE to change this
 * default assignment range.
 *
 * The value IP_PORTRANGE_DEFAULT causes the default behavior.
 *
 * The value IP_PORTRANGE_HIGH changes the range of candidate port numbers
 * into the "high" range.  These are reserved for client outbound connections
 * which do not want to be filtered by any firewalls.
 *
 * The value IP_PORTRANGE_LOW changes the range to the "low" are
 * that is (by convention) restricted to privileged processes.  This
 * convention is based on "vouchsafe" principles only.  It is only secure
 * if you trust the remote host to restrict these ports.
 *
 * The default range of ports and the high range can be changed by
 * sysctl(3).  (net.inet.ip.port{hi,low}{first,last}_auto)
 *
 * Changing those values has bad security implications if you are
 * using a a stateless firewall that is allowing packets outside of that
 * range in order to allow transparent outgoing connections.
 *
 * Such a firewall configuration will generally depend on the use of these
 * default values.  If you change them, you may find your Security
 * Administrator looking for you with a heavy object.
 *
 * For a slightly more orthodox text view on this:
 *
 *            ftp://ftp.isi.edu/in-notes/iana/assignments/port-numbers
 *
 *    port numbers are divided into three ranges:
 *
 *                0 -  1023 Well Known Ports
 *             1024 - 49151 Registered Ports
 *            49152 - 65535 Dynamic and/or Private Ports
 *
 */

/*
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).         (IP_PORTRANGE_LOW)
 * Ports > IPPORT_USERRESERVED are reserved
 * for servers, not necessarily privileged.  (IP_PORTRANGE_DEFAULT)
 */
#define IPPORT_RESERVED         1024
#define IPPORT_USERRESERVED     5000

/*
 * Default local port range to use by setting IP_PORTRANGE_HIGH
 */
#define IPPORT_HIFIRSTAUTO      49152
#define IPPORT_HILASTAUTO       65535

/*
 * Scanning for a free reserved port return a value below IPPORT_RESERVED,
 * but higher than IPPORT_RESERVEDSTART.  Traditionally the start value was
 * 512, but that conflicts with some well-known-services that firewalls may
 * have a fit if we use.
 */
#define IPPORT_RESERVEDSTART    600

/*
 * Internet address (a structure for historical reasons)
 */

typedef UINT32  in_addr_t;

struct in_addr {
    in_addr_t s_addr;
};

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */
#define IN_CLASSA(i)            (((UINT32)(i) & 0x80000000) == 0)
#define IN_CLASSA_NET           0xff000000
#define IN_CLASSA_NSHIFT        24
#define IN_CLASSA_HOST          0x00ffffff
#define IN_CLASSA_MAX           128

#define IN_CLASSB(i)            (((UINT32)(i) & 0xc0000000) == 0x80000000)
#define IN_CLASSB_NET           0xffff0000
#define IN_CLASSB_NSHIFT        16
#define IN_CLASSB_HOST          0x0000ffff
#define IN_CLASSB_MAX           65536

#define IN_CLASSC(i)            (((UINT32)(i) & 0xe0000000) == 0xc0000000)
#define IN_CLASSC_NET           0xffffff00
#define IN_CLASSC_NSHIFT        8
#define IN_CLASSC_HOST          0x000000ff

#define IN_CLASSD(i)            (((UINT32)(i) & 0xf0000000) == 0xe0000000)
#define IN_CLASSD_NET           0xf0000000      /* These ones aren't really */
#define IN_CLASSD_NSHIFT        28              /* net and host fields, but */
#define IN_CLASSD_HOST          0x0fffffff      /* routing needn't know.    */
#define IN_MULTICAST(i)         IN_CLASSD(i)

#define IN_EXPERIMENTAL(i)      (((UINT32)(i) & 0xf0000000) == 0xf0000000)
#define IN_BADCLASS(i)          (((UINT32)(i) & 0xf0000000) == 0xf0000000)

#define IN_LOCAL_GROUP(i)       (((UINT32)(i) & 0xffffff00) == 0xe0000000)

#define INADDR_ANY                      (UINT32)0x00000000
#define INADDR_LOOPBACK         (UINT32)0x7f000001
#define INADDR_BROADCAST        (UINT32)0xffffffff      /* must be masked */
#define INADDR_NONE                     0xffffffff              /* -1 return */

#define INADDR_UNSPEC_GROUP                     (UINT32)0xe0000000      /* 224.0.0.0 */
#define INADDR_ALLHOSTS_GROUP           (UINT32)0xe0000001      /* 224.0.0.1 */
#define INADDR_ALLRTRS_GROUP            (UINT32)0xe0000002      /* 224.0.0.2 */
#define INADDR_NEW_ALLRTRS_GROUP        (UINT32)0xe0000016      /* 224.0.0.22 */
#define INADDR_MAX_LOCAL_GROUP          (UINT32)0xe00000ff      /* 224.0.0.255 */

#define IN_LOOPBACKNET          127                     /* official! */

#define INADDR_LINKLOCAL                0xA9FE0000      /* 169.254 */
#define IN_ADDR_IS_LINKLOCAL(i) (((UINT32)(i) & 0xFFFF0000) == INADDR_LINKLOCAL)

#if _BYTE_ORDER == _BIG_ENDIAN

#define ntohl(x)        (UINT32)(x)
#define ntohs(x)        (UINT16)(x)
#define htonl(x)        (UINT32)(x)
#define htons(x)        (UINT16)(x)

#define NTOHL(x)        do {} while (FALSE)
#define NTOHS(x)        do {} while (FALSE)
#define HTONL(x)        do {} while (FALSE)
#define HTONS(x)        do {} while (FALSE)

#else

#define ntohl(x)        (UINT32)((((x) & 0x000000ff) << 24) | \
                                 (((x) & 0x0000ff00) <<  8) | \
                                 (((x) & 0x00ff0000) >>  8) | \
                                 (((x) & 0xff000000) >> 24))

#define htonl(x)        (UINT32)((((x) & 0x000000ff) << 24) | \
                                 (((x) & 0x0000ff00) <<  8) | \
                                 (((x) & 0x00ff0000) >>  8) | \
                                 (((x) & 0xff000000) >> 24))

#define ntohs(x)        (UINT16)((((x) & 0x00ff) << 8) |      \
                                 (((x) & 0xff00) >> 8))

#define htons(x)        (UINT16)((((x) & 0x00ff) << 8) |      \
                                 (((x) & 0xff00) >> 8))

#define NTOHL(x)        do {(x) = ntohl((UINT32)(x)); } while (FALSE)
#define NTOHS(x)        do {(x) = ntohs((UINT16)(x)); } while (FALSE)
#define HTONL(x)        do {(x) = htonl((UINT32)(x)); } while (FALSE)
#define HTONS(x)        do {(x) = htons((UINT16)(x)); } while (FALSE)

#endif /* _BYTE_ORDER */


/*
 * Socket address, internet style.
 */
    struct sockaddr_in {
        UINT8   sin_len;
        UINT8   sin_family;
        UINT16  sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8];
    };

#define INET_ADDRSTRLEN                 16

/*
 * Options for use with [gs]etsockopt at the IP level.
 * First word of comment is data type; bool is stored in int.
 */
#define IP_OPTIONS          1    /* char[0..40]; set/get IP options */
#define IP_HDRINCL          2    /* int; header is included with data */
#define IP_TOS              3    /* int; IP type of service and preced. */
#define IP_TTL              4    /* int; IP time to live */
#define IP_RECVDSTADDR      7    /* int; receive IP dst addr w/dgram */
#define IP_PKTINFO          8    /* int; turn packet information ancillary
                                  * data" on/off
                                  */
#define IP_MULTICAST_IF     9    /* struct in_addr or struct ip_mreq or
                                  * struct ip_mreqn. Which one is used
                                  * is determined by size of argument.
                                  * Controls which interface multicast
                                  * packets sent from this socket should
                                  * use
                                  */
#define IP_MULTICAST_TTL    10   /* UINT8; set/get IP multicast ttl */
#define IP_MULTICAST_LOOP   11   /* UINT8; set/get IP multicast loopback */
#define IP_ADD_MEMBERSHIP   12   /* struct ip_mreq or struct ip_mreqn.
                                  * Which one that is used is determiend
                                  * by size of argument. drop an IPv4
                                  * group membership
                                  */
#define IP_JOIN_GROUP       IP_ADD_MEMBERSHIP
#define IP_DROP_MEMBERSHIP  13   /* struct ip_mreq or struct ip_mreqn.
                                  * Which one that is used is determiend
                                  * by size of argument. drop an IPv4
                                  * group membershi
                                  */
#define IP_LEAVE_GROUP      IP_DROP_MEMBERSHIP
#define IP_RECVIF           20   /* int; receive reception if w/dgram */

#define IP_ROUTER_ALERT     21   /* UINT8; accept router alert packets */
#define IP_DONTFRAG         22   /* UINT8; set the DF bit on each packet
                                  * sent from this socket
                                  */
#define IP_NOLOCALFRAG      23   /* int; enable/disable support for
                                  * local fragmentation (default off,
                                  * which means that local
                                  * fragmentation is allowed)
                                  */
#define IP_RECVTTL          31   /* int; turn "get the time-to-live
                                  * ancillary data" on/off
                                  */
#define IP_RECVTOS          32   /* int; turn "get the type-of-service ancillary data" on/off */
#define IP_UDP_XCHKSUM      40   /* int; Turn on/off checksum for outgoing
                                  * UDP packages (default on)
                                  */
/* NOTE: 42-47 is used by MCAST_xxx macros */
#define IP_NAT              50   /* Ipnet_nat_ctrl; Network address translation control */
#define IP_FW               51   /* Ipfirewall_ctrl; Firewall control */
#define IP_NEXTHOP          52   /* struct sockaddr_in; specify the next
                                  * hop router as ancillary data
                                  */
#define IP_X_SENDERLINKADDR 100  /* int; recvmsg() returns a struct
                                  * sockaddr_dl that will contain the link
                                  * address of the sender
                                  */
#define IP_X_VRID           101  /* UINT8; specify the virtual router ID
                                  * as ancillary data
                                  */

/* MCAST_* sockopts number should not be duplicated with IPv6-level sockopts */
/*
 * Any-Source Multicast API; cannot be mixed with Source-Specific
 * Multicast API
 */
#define MCAST_JOIN_GROUP           42  /* join an any-source group */
#define MCAST_BLOCK_SOURCE         43  /* block a given source */
#define MCAST_UNBLOCK_SOURCE       44  /* unblock a given source */
#define MCAST_LEAVE_GROUP          45  /* leave an any-source group */

/*
 * Source-Specific Multicast API; cannot be mixed with Any-Source
 * Multicast API
 */
#define MCAST_JOIN_SOURCE_GROUP     46  /* join a source-specific group */
#define MCAST_LEAVE_SOURCE_GROUP    47  /* leave a source-specific grou */


/*
 * Defaults and limits for options
 */
#define IP_DEFAULT_MULTICAST_TTL     1  /* normally limit m'casts to 1 hop  */
#define IP_DEFAULT_MULTICAST_LOOP    1  /* normally hear sends if a member  */
#define IP_MAX_MEMBERSHIPS          20  /* per socket */
#define IP_MAX_SOURCE_FILTER       128  /* max number of MSF per group */
#define SO_MAX_SOURCE_FILTER        64  /* max number of MSF per socket */

/*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
 */
    struct ip_mreq {
        struct  in_addr imr_multiaddr;  /* IP multicast address of group */
        struct  in_addr imr_interface;  /* local IP address of interface */
    };

#define MCAST_INCLUDE           0       /* Exclude filter mode */
#define MCAST_EXCLUDE           1       /* Include filter mode */

/*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHI.
 */
    struct ip_mreqn
    {
        struct  in_addr   imr_multiaddr;   /* IPv4 class D multicast addr */
        struct  in_addr   imr_interface;   /* IPv4 address of local interface */
        UINT32            imr_ifindex;     /* Interface index of local interface */
    };

/*
 * Argument structure for MCAST_JOIN_GROUP and MCAST_LEAVE_GROUP
 */
    struct group_req {
        UINT32                  gr_interface;   /* interface index */
        struct sockaddr_storage gr_group;       /* group address */
    };

/*
 * Argument structure for MCAST_BLOCK_SOURCE, MCAST_UNBLOCK_SOURCE,
 * MCAST_JOIN_SOURCE_GROUP and MCAST_LEAVE_SOURCE_GROUP
 */
    struct group_source_req {
        UINT32                          gsr_interface;  /* interface index */
        struct  sockaddr_storage        gsr_group;      /* group address */
        struct  sockaddr_storage        gsr_source;     /* source address */
    };

/*
 * Ancillary data for IP_PKTINFO. It can be use toghether with
 * sendmsg() to specify egress interface and/or source address. It
 * will be returned by recvmsg() if reception of packet information
 * has been enabled via the IP_PKTINFO socket option.
 */
    struct in_pktinfo {
        UINT32         ipi_ifindex; /* egress/ingress interface index */
        struct in_addr ipi_addr;    /* local address of packet */
    };

/*
 * Argument for IP_PORTRANGE:
 * - which range to search when port is unspecified at bind() or connect()
 */
#define IP_PORTRANGE_DEFAULT    0       /* default range */
#define IP_PORTRANGE_HIGH       1       /* "high" - request firewall bypass */
#define IP_PORTRANGE_LOW        2       /* "low" - vouchsafe security */

/* Packet reassembly stuff */
#define IPREASS_NHASH_LOG2      6
#define IPREASS_NHASH           (1 << IPREASS_NHASH_LOG2)
#define IPREASS_HMASK           (IPREASS_NHASH - 1)
#define IPREASS_HASH(x,y)                                               \
        (((((x) & 0xF) | ((((x) >> 8) & 0xF) << 4)) ^ (y)) & IPREASS_HMASK)

#define RTQ_TIMEOUT     60*10   /* run no less than once every ten minutes */

/*
 * Definitions for inet sysctl operations.
 *
 * Third level is protocol number.
 * Fourth level is desired variable within that protocol.
 */
#define IPPROTO_MAXID   (IPPROTO_AH + 1)        /* don't list to IPPROTO_MAX */

/* INET6 stuff, temporary workaround */
#define __KAME_NETINET_IN_H_INCLUDED_
#include <netinet6/in6.h>
#undef __KAME_NETINET_IN_H_INCLUDED_

#ifdef _WRS_KERNEL

void     inet_ntoa_b __P((struct in_addr, char *));
char    *inet_ntoa __P((struct in_addr)); /* in libkern */

#if 0
#define satosin(sa)     ((struct sockaddr_in *)(sa))
#define sintosa(sin)    ((struct sockaddr *)(sin))
#define ifatoia(ifa)    ((struct in_ifaddr *)(ifa))
#endif

#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif
