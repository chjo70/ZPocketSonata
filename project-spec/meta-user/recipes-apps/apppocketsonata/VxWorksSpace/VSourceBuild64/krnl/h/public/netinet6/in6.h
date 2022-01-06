/* in6.c - in6 header file */

/*
 * Copyright (c) 2001-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*	$KAME: in6.h,v 1.159 2005/03/19 07:28:59 suz Exp $	*/
/*	$KAME: in6.h,v 1.155 2004/06/02 05:53:14 itojun Exp $	*/
/*	$FreeBSD: src/sys/netinet6/in6.h,v 1.7.2.7 2002/08/01 19:38:50 ume Exp $ */
/*	$KAME: in6.h,v 1.89 2001/05/27 13:28:35 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
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
 *	The Regents of the University of California.  All rights reserved.
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
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
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
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)in.h	8.3 (Berkeley) 1/3/94
 */

/*
modification history
--------------------
02d,01dec11,rjq  Add IPV6_X_VRID
02c,11sep08,kjn  Add IPV6_PREFER_SRC_xxx flags
02b,02jul08,kjn  Add back in6addr_any and in6addr_loopback
02a,30nov06,kch  Changed ipi6_ifindex in in6_pktinfo structure from unsigned
                 int to u_int32_t.
01z,20nov06,kch  Corrected comments for IPV6_JOIN_GROUP and IPV6_LEAVE_GROUP.
                 Also updated in6_addr structure declarations and macros.
01y,27oct06,kch  Restore some non-standard macros that are removed previously.
01x,25oct06,kch  Removed Kame specific non-standard macros. Added new
                 IPV6_RECVSAINFO, IPV6_ADDR_PREFERENCES, IPV6_FW and
                 IPV6_RECVIF socket options.
01w,04oct06,kch  Updated the values assigned to the IPV6 options. Also removed
                 the unsupported IPV6CTL defines.
01v,10sep06,kch  Cleanup for IPNet integration
01u,06aug05,dlk  Added in6_pseudo() declaration.
01t,04jun05,dlk  Make inet6_opt* functions from RFCs 2292 and 3542 visible in
                 user space.
01s,31may05,tlu  Added IN6_IS_ADDR_GLOBAL
01r,09may05,kch  Merged from Kame v 1.159.
01q,19apr05,rp   merged from comp_wn_ipv6_mld_interim-dev
01p,23feb05,dlk  Make functions from rthdr.c visible in user space.
01o,07feb05,vvv  _KERNEL cleanup
01n,24jan05,vvv  osdep.h cleanup
01m,20jan05,sar  Removal of divert, dummynet and fw code.
01l,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01k,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
01j,20nov03,niq  Remove copyright_wrs.h file inclusion
01i,04nov03,rlm  Ran batch header path update for header re-org.
01h,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01g,27oct03,rlm  update include statements post header re-org.
01f,11aug03,nee  Merging from label ACCORDION_BASE6_MERGE_BASELINE in
                 accordion codeline to Base6
01e,09may03,vvv  fixed check for in.h
01d,30apr03,syy  Added #ifdef for __cplusplus
01c,01feb03,pas  merge from FreeBSD 4.7 - added faithprefix_p
01b,30sep02,sar  IFDEF out the KAME IPsec mflags
01a,03feb02,ham  changes for tornado.
*/

#ifndef _NETINET_IN_H_
#error "do not include netinet6/in6.h directly, include netinet/in.h.  see RFC2553"
#endif

#ifndef _NETINET6_IN6_H_
#define _NETINET6_IN6_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Identification of the network protocol stack
 * for *BSD-current/release: http://www.kame.net/dev/cvsweb.cgi/kame/COVERAGE
 * has the table of implementation/integration differences.
 */
#define __KAME__
#define __KAME_VERSION		"SNAP 20050404"

/*
 * Local port number conventions:
 *
 * Ports < IPPORT_RESERVED are reserved for privileged processes (e.g. root),
 * unless a kernel is compiled with IPNOPRIVPORTS defined.
 *
 * When a user does a bind(2) or connect(2) with a port number of zero,
 * a non-conflicting local port address is chosen.
 *
 * The default range is IPPORT_ANONMIN to IPPORT_ANONMAX, although
 * that is settable by sysctl(3); net.inet.ip.anonportmin and
 * net.inet.ip.anonportmax respectively.
 *
 * A user may set the IPPROTO_IP option IP_PORTRANGE to change this
 * default assignment range.
 *
 * The value IP_PORTRANGE_DEFAULT causes the default behavior.
 *
 * The value IP_PORTRANGE_HIGH is the same as IP_PORTRANGE_DEFAULT,
 * and exists only for FreeBSD compatibility purposes.
 *
 * The value IP_PORTRANGE_LOW changes the range to the "low" are
 * that is (by convention) restricted to privileged processes.
 * This convention is based on "vouchsafe" principles only.
 * It is only secure if you trust the remote host to restrict these ports.
 * The range is IPPORT_RESERVEDMIN to IPPORT_RESERVEDMAX.
 */

#define	IPV6PORT_RESERVED	1024
#define	IPV6PORT_ANONMIN	49152
#define	IPV6PORT_ANONMAX	65535
#define	IPV6PORT_RESERVEDMIN	600
#define	IPV6PORT_RESERVEDMAX	(IPV6PORT_RESERVED-1)

/*
 * IPv6 address
 */
struct in6_addr {
	union {
		u_int8_t   addr8[16];
		u_int16_t  addr16[8];
		u_int32_t  addr32[4];
	} in6;			/* 128-bit IP6 address */
};

#ifndef s6_addr
#define s6_addr   in6.addr8
#endif
#ifdef _WRS_KERNEL	/* XXX nonstandard */
#ifndef s6_addr8
#define s6_addr8  in6.addr8
#endif
#ifndef s6_addr16
#define s6_addr16 in6.addr16
#endif
#ifndef s6_addr32
#define s6_addr32 in6.addr32
#endif
#endif /* _WRS_KERNEL */

#define INET6_ADDRSTRLEN	46

/*
 * Socket address for IPv6
 */
#ifndef _XOPEN_SOURCE
#define SIN6_LEN
#endif
struct sockaddr_in6 {
	u_int8_t	sin6_len;	/* length of this struct(sa_family_t)*/
	u_int8_t	sin6_family;	/* AF_INET6 (sa_family_t) */
	u_int16_t	sin6_port;	/* Transport layer port # (in_port_t)*/
	u_int32_t	sin6_flowinfo;	/* IP6 flow information */
	struct in6_addr	sin6_addr;	/* IP6 address */
	u_int32_t	sin6_scope_id;	/* scope zone index */
};

/*
 * Local definition for masks
 */
#ifdef _WRS_KERNEL	/* XXX nonstandard */
#define IN6MASK0	{{{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }}}
#define IN6MASK32	{{{ 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, \
			    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}
#define IN6MASK64	{{{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, \
			    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}
#define IN6MASK96	{{{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, \
			    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00 }}}
#define IN6MASK128	{{{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, \
			    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }}}

/*
 * Macros started with IPV6_ADDR is KAME local
 */

#if _BYTE_ORDER == _BIG_ENDIAN
#define IPV6_ADDR_INT32_ONE	1
#define IPV6_ADDR_INT32_TWO	2
#define IPV6_ADDR_INT32_MNL	0xff010000
#define IPV6_ADDR_INT32_MLL	0xff020000
#define IPV6_ADDR_INT32_SMP	0x0000ffff
#define IPV6_ADDR_INT16_ULL	0xfe80
#define IPV6_ADDR_INT16_USL	0xfec0
#define IPV6_ADDR_INT16_MLL	0xff02
#elif _BYTE_ORDER == _LITTLE_ENDIAN
#define IPV6_ADDR_INT32_ONE	0x01000000
#define IPV6_ADDR_INT32_TWO	0x02000000
#define IPV6_ADDR_INT32_MNL	0x000001ff
#define IPV6_ADDR_INT32_MLL	0x000002ff
#define IPV6_ADDR_INT32_SMP	0xffff0000
#define IPV6_ADDR_INT16_ULL	0x80fe
#define IPV6_ADDR_INT16_USL	0xc0fe
#define IPV6_ADDR_INT16_MLL	0x02ff
#endif
#endif /* _WRS_KERNEL */

/*
 * Definition of some useful macros to handle IP6 addresses
 */
#define IN6ADDR_ANY_INIT \
	{{{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}
#define IN6ADDR_LOOPBACK_INIT \
	{{{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }}}
#define IN6ADDR_NODELOCAL_ALLNODES_INIT \
	{{{ 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }}}
#define IN6ADDR_INTFACELOCAL_ALLNODES_INIT \
	{{{ 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }}}
#define IN6ADDR_LINKLOCAL_ALLNODES_INIT \
	{{{ 0xff, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }}}
#define IN6ADDR_LINKLOCAL_ALLROUTERS_INIT \
	{{{ 0xff, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 }}}
#ifdef MLDV2
#define IN6ADDR_LINKLOCAL_ALLV2ROUTERS_INIT \
	{{{ 0xff, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16 }}}
#endif

extern const struct in6_addr in6addr_any;
extern const struct in6_addr in6addr_loopback;

/* Equality */

#define IN6_ARE_ADDR_EQUAL(a, b)			\
    (bcmp ((char *) &(a)->s6_addr[0], (char *) &(b)->s6_addr[0], \
	   sizeof(struct in6_addr)) == 0)

#ifdef _WRS_KERNEL			/* non standard */
#if 0
/* see if two addresses are equal in a scope-conscious manner. */
#define SA6_ARE_ADDR_EQUAL(a, b) \
	(((a)->sin6_scope_id == 0 || (b)->sin6_scope_id == 0 || \
	  ((a)->sin6_scope_id == (b)->sin6_scope_id)) && \
	 (bcmp ((char *) &(a)->sin6_addr, (char *) &(b)->sin6_addr, \
		sizeof (struct in6_addr)) == 0))
#endif
#endif

/*
 * Unspecified
 */
#define IN6_IS_ADDR_UNSPECIFIED(a) \
  ((a)->in6.addr32[0] == 0 && (a)->in6.addr32[1] == 0 && (a)->in6.addr32[2] == 0 && \
   (a)->in6.addr32[3] == 0)

/*
 * Loopback
 */
#define IN6_IS_ADDR_LOOPBACK(a) \
  ((a)->in6.addr32[0] == 0 && (a)->in6.addr32[1] == 0 && (a)->in6.addr32[2] == 0 && \
   (a)->in6.addr32[3] == ntohl(1))

/*
 * IPv4 compatible
 */
#define IN6_IS_ADDR_V4COMPAT(a) \
  ((a)->in6.addr32[0] == 0 && (a)->in6.addr32[1] == 0 && (a)->in6.addr32[2] == 0 && \
   (a)->in6.addr32[3] != 0 && (a)->in6.addr32[3] != ntohl(1))

/*
 * Mapped
 */
#define IN6_IS_ADDR_V4MAPPED(a)	\
  ((a)->in6.addr32[0] == 0 && (a)->in6.addr32[1] == 0 && (a)->in6.addr32[2] == ntohl(0x0000ffff))

/*
 * KAME Scope Values
 */

#ifdef _WRS_KERNEL	/* XXX nonstandard */
#define IPV6_ADDR_SCOPE_NODELOCAL	0x01
#define IPV6_ADDR_SCOPE_INTFACELOCAL	0x01
#define IPV6_ADDR_SCOPE_LINKLOCAL	0x02
#define IPV6_ADDR_SCOPE_SITELOCAL	0x05
#define IPV6_ADDR_SCOPE_ORGLOCAL	0x08	/* just used in this file */
#define IPV6_ADDR_SCOPE_GLOBAL		0x0e
#else
#define __IPV6_ADDR_SCOPE_NODELOCAL	0x01
#define __IPV6_ADDR_SCOPE_INTFACELOCAL	0x01
#define __IPV6_ADDR_SCOPE_LINKLOCAL	0x02
#define __IPV6_ADDR_SCOPE_SITELOCAL	0x05
#define __IPV6_ADDR_SCOPE_ORGLOCAL	0x08	/* just used in this file */
#define __IPV6_ADDR_SCOPE_GLOBAL	0x0e
#endif

/*
 * Unicast Scope
 * Note that we must check topmost 10 bits only, not 16 bits (see RFC2373).
 */
#define IN6_IS_ADDR_LINKLOCAL(a)	\
	(((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))
#define IN6_IS_ADDR_SITELOCAL(a)	\
	(((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0xc0))

/*
 * Multicast
 */
#define IN6_IS_ADDR_MULTICAST(a)	((a)->s6_addr[0] == 0xff)

/*
 * Global Scope
 */
#define IN6_IS_ADDR_GLOBAL(adr) \
        ((!IN6_IS_ADDR_MULTICAST(adr)) && \
         (!IN6_IS_ADDR_LINKLOCAL(adr)) && \
         (!IN6_IS_ADDR_SITELOCAL(adr)))

#ifdef _WRS_KERNEL	/* XXX nonstandard */
#define IPV6_ADDR_MC_SCOPE(a)		((a)->s6_addr[1] & 0x0f)
#else
#define __IPV6_ADDR_MC_SCOPE(a)		((a)->s6_addr[1] & 0x0f)
#endif

/*
 * Multicast Scope
 */
#ifdef _WRS_KERNEL	/* refers nonstandard items */
#define IN6_IS_ADDR_MC_NODELOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (IPV6_ADDR_MC_SCOPE(a) == IPV6_ADDR_SCOPE_NODELOCAL))
#define IN6_IS_ADDR_MC_INTFACELOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (IPV6_ADDR_MC_SCOPE(a) == IPV6_ADDR_SCOPE_INTFACELOCAL))
#define IN6_IS_ADDR_MC_LINKLOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (IPV6_ADDR_MC_SCOPE(a) == IPV6_ADDR_SCOPE_LINKLOCAL))
#define IN6_IS_ADDR_MC_SITELOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) && 	\
	 (IPV6_ADDR_MC_SCOPE(a) == IPV6_ADDR_SCOPE_SITELOCAL))
#define IN6_IS_ADDR_MC_ORGLOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (IPV6_ADDR_MC_SCOPE(a) == IPV6_ADDR_SCOPE_ORGLOCAL))
#define IN6_IS_ADDR_MC_GLOBAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (IPV6_ADDR_MC_SCOPE(a) == IPV6_ADDR_SCOPE_GLOBAL))
#else
#define IN6_IS_ADDR_MC_NODELOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_NODELOCAL))
#define IN6_IS_ADDR_MC_LINKLOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_LINKLOCAL))
#define IN6_IS_ADDR_MC_SITELOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) && 	\
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_SITELOCAL))
#define IN6_IS_ADDR_MC_ORGLOCAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_ORGLOCAL))
#define IN6_IS_ADDR_MC_GLOBAL(a)	\
	(IN6_IS_ADDR_MULTICAST(a) &&	\
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_GLOBAL))
#endif

#ifdef _WRS_KERNEL	/* nonstandard */
/*
 * KAME Scope
 */
#define IN6_IS_SCOPE_LINKLOCAL(a)	\
	((IN6_IS_ADDR_LINKLOCAL(a)) ||	\
	 (IN6_IS_ADDR_MC_LINKLOCAL(a)))

#define IFA6_IS_DEPRECATED(a) \
	((a)->ia6_lifetime.ia6t_pltime != ND6_INFINITE_LIFETIME && \
	 (u_int32_t)((time_second - (a)->ia6_updatetime)) > \
	 (a)->ia6_lifetime.ia6t_pltime)
#define IFA6_IS_INVALID(a) \
	((a)->ia6_lifetime.ia6t_vltime != ND6_INFINITE_LIFETIME && \
	 (u_int32_t)((time_second - (a)->ia6_updatetime)) > \
	 (a)->ia6_lifetime.ia6t_vltime)
#endif /* _WRS_KERNEL */

/*
 * Options for use with [gs]etsockopt at the IPV6 level.
 * First word of comment is data type; bool is stored in int.
 */
#define IPV6_V6ONLY		    1  /* bool; make AF_INET6 sockets v6 only */
#define IPV6_SOCKOPT_RESERVED1	3  /* reserved for future use */
#define IPV6_UNICAST_HOPS	4  /* int; IP6 hops */
#define IPV6_CHECKSUM		7  /* int; checksum offset for raw socket */
#define IPV6_MULTICAST_IF	9  /* u_int; set/get IP6 multicast i/f  */
#define IPV6_MULTICAST_HOPS	10 /* int; set/get IP6 multicast hops */
#define IPV6_MULTICAST_LOOP	11 /* u_int; set/get IP6 multicast loopback */
#define IPV6_JOIN_GROUP		12 /* ipv6_mreq; join a group membership */
#define IPV6_LEAVE_GROUP	13 /* ipv6_mreq; leave a group membership */

#define IPV6_PKTINFO		20 /* in6_pktinfo; send if, src addr */
#define IPV6_TCLASS		    22 /* int; send traffic class value */
#define IPV6_NEXTHOP		23 /* sockaddr; next hop addr */
#define IPV6_RTHDR		    24 /* ip6_rthdr; send routing header */
#define IPV6_HOPOPTS		25 /* ip6_hbh; send hop-by-hop option */
#define IPV6_DSTOPTS		26 /* ip6_dest; send dst option befor rthdr */

/* new socket options introduced in RFC2292bis */
#define IPV6_RTHDRDSTOPTS	27 /* ip6_dest; send dst option before rthdr */
#define IPV6_RECVPKTINFO	30 /* bool; recv if, dst addr */
#define IPV6_RECVHOPLIMIT	31 /* bool; recv hop limit */
#define IPV6_RECVTCLASS		32 /* bool; recv traffic class values */
#define IPV6_RECVRTHDR		34 /* bool; recv routing header */
#define IPV6_RECVHOPOPTS	35 /* bool; recv hop-by-hop option */
#define IPV6_RECVDSTOPTS	36 /* bool; recv dst option after rthdr */
#define IPV6_RECVSAINFO		37 /* int; get the SA information */
#define IPV6_ADDR_PREFERENCES	38 /* int; set/get sticky address preference flags (IPV6_PREFER_SRC_xxx) */

#define IPV6_FW				51 /* Ipfirewall_ctrl; Firewall control */
#define IPV6_RECVIF			100 /* int; turn "get link layer address (as a struct sockaddr_dl) */
#define IPV6_X_SENDERLINKADDR 101  /* int; ipcom_recvmsg() returns a struct
                                      sockaddr_dl that will contain the link
                                      address of the sender */
#define IPV6_X_VRID           103   /* Ip_u8; specify the virtual router ID as ancillary data */

#define IPV6_HOPLIMIT		21 /* int; send hop limit */

/* IPPROTO_ICMPV6 level socket options. */
#define ICMP6_FILTER		1 /* icmp6_filter; icmp6 filter */

/* Flags for IPV6_ADDR_PREFERENCES option */
#define IPV6_PREFER_SRC_HOME       (1u << 0) /* Prefer Home Address as source (not implemented) */
#define IPV6_PREFER_SRC_COA        (1u << 1) /* Prefer Care-Of_address as source (not implemented) */
#define IPV6_PREFER_SRC_TMP        (1u << 2) /* Prefer Temporary address as source */
#define IPV6_PREFER_SRC_PUBLIC     (1u << 3) /* Prefer Public address as source */
#define IPV6_PREFER_SRC_CGA        (1u << 4) /* Prefer CGA address as source */
#define IPV6_PREFER_SRC_NONCGA     (1u << 5) /* Prefer a non-CGA address as source (not implemented) */
#define IPV6_PREFER_SRC_LARGESCOPE (1u << 6) /* Prefer larger scope source */
#define IPV6_PREFER_SRC_SMALLSCOPE (1u << 7) /* Prefer smaller scope source */

/*
 * Argument structure for IPV6_JOIN_GROUP and IPV6_LEAVE_GROUP.
 */
struct ipv6_mreq {
	struct in6_addr	ipv6mr_multiaddr;  /* IPv6 multicast addr */
	unsigned int	ipv6mr_interface;  /* interface index, or 0 */
};

/*
 * IPV6_PKTINFO: Packet information(RFC2292 sec 5)
 */
struct in6_pktinfo {
	struct in6_addr	ipi6_addr;	/* src/dst IPv6 address */
	u_int32_t	ipi6_ifindex;	/* send/recv interface index */
};

#ifdef __cplusplus
}
#endif

#endif /* !_NETINET6_IN6_H_ */
