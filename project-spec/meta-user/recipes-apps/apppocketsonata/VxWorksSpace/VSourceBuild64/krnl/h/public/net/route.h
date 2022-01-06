/* route.h - routing table */

/* Copyright 2001-2005, 2014 Wind River Systems, Inc. */

/*
 * Copyright (c) 1980, 1986, 1993
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
 *	@(#)route.h	8.4 (Berkeley) 1/9/95
 * $FreeBSD: src/sys/net/route.h,v 1.36.2.5 2002/02/01 11:48:01 ru Exp $
 */

/*
modification history
--------------------
02d,09jan12,h_x  Move extern "C" after last header file include.
02c,25oct06,kch  Removed route structure as well as unsupported members from 
                 rt_metrics.
02b,04oct06,kch  Updated rt_msghdr structure for IPNet integration.
02a,05sep06,kch  Cleanup for IPNet integration.
01z,19may05,rp   added RTM_ADDRINFO
01y,01mar05,niq  Include in6.h
01x,24feb05,spm  removed unneeded route format storage (SPR #100995)
01w,24feb05,spm  performance updates and code cleanup (SPR #100995)
01v,08feb05,vvv  _KERNEL cleanup
01u,17sep04,niq  Scale out routing sockets
01t,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01s,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/2)
01r,06dec03,niq  Add the RTF_PRIMARY flag
01q,24nov03,vvv  updated for RTP support
01p,20nov03,niq  Remove copyright_wrs.h file inclusion
01o,10nov03,cdw  Rebase from base6 iteration 1 view
01n,04nov03,rlm  Ran batch header path update for header re-org.
01m,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01l,27sep03,vvv  moved RTFREE out of #ifdef _KERNEL
01k,23sep03,asr  Moved the #include <route/ipRouteLib.h> outside of #ifdef _KERNEL 
01j,06aug03,niq  Merge from Accordion into Base6 Iteration 1 branch
01i,10jun03,vvv  include netVersion.h
01h,01feb03,pas  merge from FreeBSD 4.7 - added rt_getifa(),
                 rt_ifannouncemsg(), rtrequest1()
01g,05sep02,hsh  add cplusplus protection
01f,16may02,ant  field rmx_filler[4] in the struct rt_metrics expand to 
		 rmx_filler[5]. New definitions rt_mod and RTF_MGMT
01e,11mar02,ham  reverted previous checkin 01d
01d,27feb02,nee  extending the rt_metrics for rip
01c,02feb02,ham  changed for tornado build.
01b,19dec01,nee  Adding multipath capability
01a,08sep01,qli  1st round of porting
*/


#ifndef _NET_ROUTE_H_
#define _NET_ROUTE_H_

#include <sys/socket.h>


#ifdef __cplusplus
extern "C" {
#endif

/*
 * Kernel resident routing tables.
 *
 * The routing tables are initialized when interface addresses
 * are set by making entries for all directly connected interfaces.
 */

/*
 * We distinguish between routes to hosts and routes to networks,
 * preferring the former if available.  For each route we infer
 * the interface to use from the gateway address supplied when
 * the route was entered.  Routes that forward packets through
 * gateways are marked so that the output routines know to address the
 * gateway rather than the ultimate destination.
 */

/*
 * Following structure necessary for 4.3 compatibility;
 * We should eventually move it to a compat file.
 */
struct ortentry {
	struct	sockaddr ort_dst;	/* key */
	struct	sockaddr ort_gateway;	/* value */
	short	ort_flags;		/* up/down?, host/net */
};

/*
 * These numbers are used by reliable protocols for determining
 * retransmission behavior and are included in the routing structure.
 */
struct rt_metrics {
	u_long	rmx_mtu;	/* MTU for this path */
	u_long	rmx_hopcount;	/* max hops expected */
	u_long	rmx_expire;	/* lifetime for route, e.g. redirect */
	u_long	rmx_rtt;	/* estimated round trip time */
	u_long	rmx_rttvar;	/* estimated rtt variance */
};

/*
 * rmx_rtt and rmx_rttvar are stored as microseconds;
 * RTTTOPRHZ(rtt) converts to a value suitable for use
 * by a protocol slowtimo counter.
 */
#define	RTM_RTTUNIT	1000000	/* units for rtt, rttvar, as units per sec */
#define	RTTTOPRHZ(r)	((r) / (RTM_RTTUNIT / PR_SLOWHZ))

/*
 * XXX kernel function pointer `rt_output' is visible to applications.
 */

/* Values for rt_flags */
#define RTF_UP		0x1		/* route usable */
#define RTF_GATEWAY	0x2		/* destination is a gateway */
#define RTF_HOST	0x4		/* host entry (net otherwise) */
#define RTF_REJECT	0x8		/* host or net unreachable */
#define RTF_DYNAMIC	0x10		/* created dynamically (by redirect) */
#define RTF_MODIFIED	0x20		/* modified dynamically (by redirect)*/
#define RTF_DONE	0x40		/* message confirmed */
#define RTF_MASK        0x80            /* Subnet mask present */
#define RTF_CLONING	0x100		/* generate new routes on use */
#define RTF_XRESOLVE	0x200		/* external daemon resolves name */
#define RTF_LLINFO	0x400		/* generated by link layer (e.g. ARP)*/
#define RTF_STATIC	0x800		/* manually added */
#define RTF_BLACKHOLE	0x1000		/* just discard pkts (during updates)*/
#define RTF_LOCAL 	0x2000		/* route represents a local address */
#define RTF_PROTO2	0x4000		/* protocol specific routing flag */
#define RTF_PROTO1	0x8000		/* protocol specific routing flag */
#define RTF_PREF	0x10000 	/* Add route first, no ECMP */
#define RTF_SRCADDR	0x20000 /* The gateway field specifies the default source address */
#define RTF_MBINDING	0x40000 /* This route is part of multiple binding */
#define RTF_SKIP	0x80000 /* Treat this route as a routing lookup failure */

/*
 * Structures for routing messages.
 */
struct rt_msghdr {
	u_short	rtm_msglen;	/* to skip over non-understood messages */
	u_char	rtm_version;	/* future binary compatibility */
	u_char	rtm_type;	/* message type */
	u_long	rtm_index;	/* index for associated ifp */
	int	rtm_flags;	/* flags, incl. kern & message, e.g. DONE */
	int	rtm_addrs;	/* bitmask identifying sockaddrs in msg */
	pid_t	rtm_pid;	/* identify sender */
	int	rtm_seq;	/* for sender to identify action */
	int	rtm_errno;	/* why failed */
	int	rtm_use;	/* from rtentry */
	u_long	rtm_inits;	/* which metrics we are initializing */
	u_long  rtm_table;      /* Route table index (IPCOM_ROUTE_TABLE_DEFAULT = default) */
	struct	rt_metrics rtm_rmx; /* metrics themselves */
};

/*
 * Message types. The message numbers should be continous as their
 * values are used as array indices
 */
#define RTM_ADD		0x1	/* Add Route */
#define RTM_DELETE	0x2	/* Delete Route */
#define RTM_CHANGE	0x3	/* Change Metrics or flags */
#define RTM_GET		0x4	/* Report Metrics */
#define RTM_LOSING	0x5	/* Kernel Suspects Partitioning */
#define RTM_REDIRECT	0x6	/* Told to use different route */
#define RTM_MISS	0x7	/* Lookup failed on this address */
#define RTM_LOCK	0x8	/* fix specified metrics */
#define RTM_OLDADD	0x9	/* caused by SIOCADDRT */
#define RTM_OLDDEL	0xa	/* caused by SIOCDELRT */
#define RTM_RESOLVE	0xb	/* req to resolve dst to LL addr */
#define RTM_NEWADDR	0xc	/* address being added to iface */
#define RTM_DELADDR	0xd	/* address being removed from iface */
#define RTM_IFINFO	0xe	/* iface going up/down etc. */
#define RTM_IFANNOUNCE	0x10	/* iface arrival/departure */

/* IPNet extension for Virtual Router */
#define RTM_NEWVR     0xf1  /* TF1 Add a new virtual router */
#define RTM_DELVR     0xf2  /* TF1 Delete a virtual router, the default (0)
                               route table cannot be remmoved  */

/*
 * Bitmask values for rtm_addrs.
 */
#define RTA_DST		0x1	/* destination sockaddr present */
#define RTA_GATEWAY	0x2	/* gateway sockaddr present */
#define RTA_NETMASK	0x4	/* netmask sockaddr present */
#define RTA_GENMASK	0x8	/* cloning mask sockaddr present */
#define RTA_IFP		0x10	/* interface name sockaddr present */
#define RTA_IFA		0x20	/* interface addr sockaddr present */
#define RTA_AUTHOR	0x40	/* sockaddr for author of redirect */
#define RTA_BRD		0x80	/* for NEWADDR, broadcast or p-p dest addr */

/*
 * Index offsets for sockaddr array for alternate internal encoding.
 */
#define RTAX_DST	0	/* destination sockaddr present */
#define RTAX_GATEWAY	1	/* gateway sockaddr present */
#define RTAX_NETMASK	2	/* netmask sockaddr present */
#define RTAX_GENMASK	3	/* cloning mask sockaddr present */
#define RTAX_IFP	4	/* interface name sockaddr present */
#define RTAX_IFA	5	/* interface addr sockaddr present */
#define RTAX_AUTHOR	6	/* sockaddr for author of redirect */
#define RTAX_BRD	7	/* for NEWADDR, broadcast or p-p dest addr */
#define RTAX_MAX	8	/* size of array to allocate */

#ifdef __cplusplus
}
#endif

#endif /* _NET_ROUTE_H_ */
