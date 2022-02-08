/* ip6_mroute.h - IPv6 mroute header file */

/*	$KAME: ip6_mroute.h,v 1.29 2004/05/21 08:17:58 itojun Exp $	*/
/*	$FreeBSD: src/sys/netinet6/ip6_mroute.h,v 1.2.2.3 2002/04/28 05:40:27 suz Exp $	*/
/*	$KAME: ip6_mroute.h,v 1.19 2001/06/14 06:12:55 suz Exp $	*/

/*
 * Copyright (c) 2001-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * Copyright (C) 1998 WIDE Project.
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

/*	BSDI ip_mroute.h,v 2.5 1996/10/11 16:01:48 pjd Exp	*/

/*
 * Definitions for IP multicast forwarding.
 *
 * Written by David Waitzman, BBN Labs, August 1988.
 * Modified by Steve Deering, Stanford, February 1989.
 * Modified by Ajit Thyagarajan, PARC, August 1993.
 * Modified by Ajit Thyagarajan, PARC, August 1994.
 * Modified by Ahmed Helmy, USC, September 1996.
 *
 * MROUTING Revision: 1.2
 */

/*
modification history
--------------------
01i,09jan12,h_x  Move extern "C" after last header file include.
01h,12jul07,kch  Re-integrated to support multicast forwarding for IPNET
                 (WIND00102340).
01g,20may05,kch  Redefined cfg_privInitSysctl as function pointer. Moved
                 ip6MrouteSysctlInit() prototype to sysctlLib.h.
01f,26apr05,kch  Allow ip6 mrouter to be scaled out.
01e,19apr05,rp   merged from comp_wn_ipv6_mld_interim-dev
01d,28jan05,kc   Redefined IF_COPY and IF_ZERO macros.
01c,28dec04,kc   Added ipm6_config_params structure. Also added
                 ip6MrouteSysctlInit() prototype.
01b,23dec04,kc   Added pim6_input() and ip6MrouterInstInit() prototypes.
01a,08dec04,kc   Integrated Kame changes.
*/

#ifndef _NETINET6_IP6_MROUTE_H_
#define _NETINET6_IP6_MROUTE_H_

#include <netinet6/in6.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Multicast Routing set/getsockopt commands.
 */
#define MRT6_BASE      0x60000000    

#define MRT6_INIT       (MRT6_BASE + 0)  /* initialize mrouted */
#define MRT6_DONE       (MRT6_BASE + 1)  /* shut down mrouted */
#define MRT6_ADD_MIF    (MRT6_BASE + 2)	/* add multicast interface */
#define MRT6_DEL_MIF    (MRT6_BASE + 3)  /* delete multicast interface */
#define MRT6_ADD_MFC    (MRT6_BASE + 4)  /* add forwarding cache entry */
#define MRT6_DEL_MFC    (MRT6_BASE + 5)  /* delete forwarding cache entry */
#define MRT6_PIM        (MRT6_BASE + 6)  /* enable pim code */

/*
 * Types and macros for handling bitmaps with one bit per multicast interface.
 */
typedef u_short mifi_t;		/* type of a mif index */
#define MAXMIFS		64      /* Maximum number of multicast interfaces */

#ifndef	IF_SETSIZE
#define	IF_SETSIZE	256
#endif

typedef	u_int32_t	if_mask;
#define	NIFBITS	(sizeof(if_mask) * 8)	/* bits per mask */

typedef	struct if_set {
    if_mask ifs_bits[(((IF_SETSIZE)+((NIFBITS)-1))/(NIFBITS))];    
} if_set;

/* Macros to operate on the mf6cc_ifset bit array */
#define	IF_SET(n, p)	\
((p)->ifs_bits[(n)/NIFBITS] |= (1 << ((n) % NIFBITS)))
#define	IF_CLR(n, p)	\
((p)->ifs_bits[(n)/NIFBITS] &= ~(1 << ((n) % NIFBITS)))
#define	IF_ISSET(n, p) \
((p)->ifs_bits[(n)/NIFBITS] & (1 << ((n) % NIFBITS)))
#define	IF_COPY(f, t)	bcopy(f, t, sizeof(struct if_set))
#define	IF_ZERO(p)	bzero(p, sizeof(struct if_set))

/*
 * Argument structure for MRT6_ADD_MIF and MRT6_DEL_MIF.
 */
struct mif6ctl {
	mifi_t      mif6c_mifi;     /* the index of the mif to be added  */
	u_char      mif6c_flags;    /* MIFF_ flags defined below         */
	u_short     mif6c_pifi;     /* the index of the physical IF */
};

#define	MIFF_REGISTER	0x1	/* mif represents a register end-point */

/*
 * Argument structure for MRT6_ADD_MFC and MRT6_DEL_MFC
 */
struct mf6cctl {
	struct sockaddr_in6 mf6cc_origin;	/* IPv6 origin of mcasts */
	struct sockaddr_in6 mf6cc_mcastgrp; /* multicast group associated */
	mifi_t  mf6cc_parent;	/* incoming ifindex */
	struct if_set  mf6cc_ifset;	/* set of forwarding ifs */
};

/*
 * Argument structure for SIOCGETSGCNT_IN6
 * Used by a multicast routing daemon to get src-grp packet counts
 */
struct sioc_sg_req6 {
    struct sockaddr_in6 src;    /* Source address */
    struct sockaddr_in6 grp;    /* Multicast group address */
    u_int64_t pktcnt;   /* No of packets routed */
    u_int64_t bytecnt;  /* No of bytes routed */
    u_int64_t wrong_if; /* No of packets arrived on wrong interface */
};

/*
 * Argument structure for SIOCGETMIFCNT_IN6
 * Used by a multicast routing daemon to get multicast interface packet 
 * counts.
 */
struct sioc_mif_req6 {
    mifi_t      mifi;       /* mif number */
    u_int64_t   icount;     /* Input packet count */
    u_int64_t   ocount;     /* Output packet count */
    u_int64_t   ibytes;     /* Input byte count */
    u_int64_t   obytes;     /* Output byte count */
};

#ifdef __cplusplus
}
#endif

#endif /* !_NETINET6_IP6_MROUTE_H_ */
