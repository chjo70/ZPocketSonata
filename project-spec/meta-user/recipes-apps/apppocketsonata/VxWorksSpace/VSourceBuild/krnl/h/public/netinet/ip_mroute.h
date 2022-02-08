/* ip_mroute.h - multicast forwarding header file */

/*
 * Copyright (c) 1984-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
 * Copyright (c) 1989 Stephen Deering.
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Stephen Deering of Stanford University.
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
 *	@(#)ip_mroute.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/netinet/ip_mroute.h,v 1.17 1999/12/29 04:41:01 peter Exp $
 */

/*
modification history
--------------------
01j,09jan12,h_x  Move extern "C" after last header file include.
01i,12jul07,kch  Re-integrated to support IP multicast source forwarding
                 for IPNET (WIND00102340).
01h,16jul05,dlk  Added tbf_timeo member to struct tbf for timer cancellation
                 when shutting down mrouter in virtual stack destructor.
01g,25feb05,niq  add support for router alert
01f,31jan05,niq  merge mroute changes from comp_wn_ipv6_multicast_interim-dev
                 branch  (ver 1)
01e,20sep04,rae  fix compiler warnings
01d,24jun03,rae  add #include netVersion.h
01c,10oct01,rae  merge from truestack ver 01k (v2 upgrade)
01b,08apr97,vin  removed declarations for ip_mforward and ip_mrouter_done.
		 implemented ip_mforward as a hook for scalability.
01a,03mar96,vin  created from BSD4.4lite2.
*/

#ifndef _NETINET_IP_MROUTE_H_
#define _NETINET_IP_MROUTE_H_

#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Definitions for IP multicast forwarding.
 *
 * Written by David Waitzman, BBN Labs, August 1988.
 * Modified by Steve Deering, Stanford, February 1989.
 * Modified by Ajit Thyagarajan, PARC, August 1993.
 * Modified by Ajit Thyagarajan, PARC, August 1994.
 * Modified by Ahmed Helmy, SGI, June 1996.
 * Modified by Pavlin Radoslavov, ICSI, October 2002.
 *
 * MROUTING Revision: 3.3.1.3
 * and PIM-SMv2 and PIM-DM support, advanced API support,
 * bandwidth metering and signaling.
 */


/***** IP_IPPROTO_IP level multicast socket options: *****/
#define MRT_BASE      0x40000000
    
/*
 * Multicast Routing set/getsockopt commands.
 */
#define	MRT_INIT    (MRT_BASE + 0)  /* initialize mrouted */    
#define	MRT_DONE    (MRT_BASE + 1)  /* shut down mrouted */
#define	MRT_ADD_VIF (MRT_BASE + 2)  /* create virtual interface */
#define	MRT_DEL_VIF (MRT_BASE + 3)  /* delete virtual interface */
#define MRT_ADD_MFC (MRT_BASE + 4)  /* insert forwarding cache entry */
#define MRT_DEL_MFC (MRT_BASE + 5)  /* delete forwarding cache entry */
#define MRT_VERSION (MRT_BASE + 6)  /* get kernel version number */
#define MRT_ASSERT  (MRT_BASE + 7)  /* enable assert processing */
#define MRT_PIM		MRT_ASSERT /* enable PIM processing */

#define	MAXVIFS 32          /* Maximum number of virtual interfaces */
typedef u_short vifi_t;     /* Virtual interface index type */    


/*
 * Structure used for IPv4 multicast routing
 */

/*
 * Argument structure for MRT_ADD_VIF.
 * (MRT_DEL_VIF takes a single vifi_t argument.)
 */
struct vifctl {
	vifi_t          vifc_vifi;          /* the index of the vif to be added */
	u_char          vifc_flags;         /* VIFF_ flags defined below */
	u_char          vifc_threshold;     /* min ttl required to forward on vif */
	u_int32_t       vifc_rate_limit;    /* max rate */
	struct in_addr  vifc_lcl_addr;      /* local interface address */
	struct in_addr  vifc_rmt_addr;      /* remote address (tunnels only) */
};

#define	VIFF_TUNNEL     0x1     /* vif represents a tunnel end-point */
#define VIFF_REGISTER   0x4     /* used for PIM Register encap/decap */

/*
 * Argument structure for MRT_ADD_MFC and MRT_DEL_MFC
 */
struct mfcctl {
    struct in_addr  mfcc_origin;		/* ip origin of mcasts       */
    struct in_addr  mfcc_mcastgrp; 		/* multicast group associated*/
    vifi_t          mfcc_parent;   		/* incoming vif              */
    u_char          mfcc_ttls[MAXVIFS]; /* forwarding ttls on vifs   */
};

/* Structure used by SIOCGETSGCNT ioctl
 * Holds statistsic for the route matching 'src' and 'grp'
 */
struct sioc_sg_req
{
    struct in_addr   src;        /* The source address */
    struct in_addr   grp;        /* The destination group address */
    u_int32_t        pktcnt;     /* Packets sent along this route */
    u_int32_t        bytecnt;    /* Bytes sent along this route */
    u_int32_t        wrong_if;   /* Number of packet received on the wrong
                                  * VIF matching this route 
                                  */
};

/* Structure used by SIOCGETVIFCNT ioctl.
 * Hold statistics for the virtual interface
 */
struct sioc_vif_req
{
    vifi_t         vifi;   /* Virtual interface index */
    u_int32_t      icount; /* Number of packets received on this interface */
    u_int32_t      ocount; /* Number of packets sent on this interface */
    u_int32_t      ibytes; /* Number of bytes received on this interface */
    u_int32_t      obytes; /* Number of bytes sent on this interface */
};


#ifdef __cplusplus
}
#endif
    
#endif /* _NETINET_IP_MROUTE_H_ */
