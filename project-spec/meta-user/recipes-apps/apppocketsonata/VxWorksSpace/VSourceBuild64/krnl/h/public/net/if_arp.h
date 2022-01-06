/* if_arp.h - network interface address resolution protocol header file */
 
/* Copyright 2001-2005 Wind River Systems, Inc. */

/*
 * Copyright (c) 1986, 1993
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
 *	@(#)if_arp.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD: src/sys/net/if_arp.h,v 1.14.2.3 2002/02/20 23:34:09 fjoe Exp $
 */

/*
modification history
--------------------
01r,20nov06,kch  Removed unused arcbroadcastaddr extern declaration.
01q,24oct06.kch  Changed arp_ha in arpreq strcture from sockaddr to 
                 sockaddr_dl. Removed unsupported ATF flags and added
                 ATF_GRAT and ATF_BLACKHOLE.
01p,09sep06,kch  Cleanup for IPNet integration.
01o,07feb05,vvv  _KERNEL cleanup
01n,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01m,20nov03,niq  Remove copyright_wrs.h file inclusion
01l,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01k,04nov03,rlm  Ran batch header path update for header re-org.
01j,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01i,27oct03,rlm  update include statements post header re-org.
01h,06aug03,niq  Merging from Accordion label ACCORDION_BASE6_MERGE_BASELINE
01g,09may03,vvv  included socket.h and if.h
01h,07mar03,spm  merged from CLARINET-1_1-KAME-UPDATE (ver 01f,01feb03,pas)
01g,02dec02,spm  merged from WINDNET_IPV6-1_0-FCS label (ver 01e,09sep02,hsh)
01f,27aug02,kal  inclusion of in.h for struct in_addr (in arpcom)
01e,23aug02,vlk  added ac_ipaddr item into "arpcom" struct
                 and ATF_INCOMPLETE definition
01d,03feb02,ham  changes for tornado build.
01c,09dec01,ppp  adding ATF_PROXY flag
01b,20aug01,qli  moving the element to protos/arp
01a,12aug01,ham  created from FreeBSD4.3-RELEASE(July-17-01).
*/

#ifndef _NET_IF_ARP_H_
#define	_NET_IF_ARP_H_

/* includes */

#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if_dl.h>
#include <net/if.h>

#ifdef __cplusplus
 extern "C" {
#endif
     

/*
 * Address Resolution Protocol.
 *
 * See RFC 826 for protocol description.  ARP packets are variable
 * in size; the arphdr structure defines the fixed-length portion.
 * Protocol type values are the same as those for 10 Mb/s Ethernet.
 * It is followed by the variable-sized fields ar_sha, arp_spa,
 * arp_tha and arp_tpa in that order, according to the lengths
 * specified.  Field names used correspond to RFC 826.
 */
struct	arphdr {
	u_short	ar_hrd;		/* format of hardware address */
#define ARPHRD_ETHER 	   1	/* ethernet hardware format */
#define ARPHRD_EETHER 	   2	/* experimental ethernet format */
#define ARPHRD_AX25        3    /* AX.25 Level 2 */
#define ARPHRD_PRONET      4    /* PROnet token ring */
#define ARPHRD_CHAOS       5    /* Chaosnet */
#define ARPHRD_IEEE802	   6	/* token-ring hardware format */
#define ARPHRD_ARCNET	   7	/* arcnet hardware format */
#define ARPHRD_HYPERCH     8    /* Hyper channel */
#define ARPHRD_LANSTAR     9    /* LanStar */
#define ARPHRD_ULTRALINK  13    /* UltraLink */
#define ARPHRD_FRELAY 	  15	/* frame relay hardware format */
#define ARPHRD_DLCI 	  ARPHRD_FRELAY
#define ARPHRD_ATM        19    /* ATM */
#define ARPHRD_METRICOM   23    /* Metricom STRIP (new IANA id) */
#define ARPHRD_IEEE1394   24    /* IEEE 1394 IPv4 - RFC 2734 */
#define ARPHRD_EUI64      27    /* EUI-64 */
	u_short	ar_pro;		/* format of protocol address */
	u_char	ar_hln;		/* length of hardware address */
	u_char	ar_pln;		/* length of protocol address */
	u_short	ar_op;		/* one of: */
#define	ARPOP_REQUEST	1	/* request to resolve address */
#define	ARPOP_REPLY	2	/* response to previous request */
#define	ARPOP_REVREQUEST 3	/* request protocol address given hardware */
#define	ARPOP_REVREPLY	4	/* response giving protocol address */
#define ARPOP_INVREQUEST 8 	/* request to identify peer */
#define ARPOP_INVREPLY	9	/* response identifying peer */
/*
 * The remaining fields are variable in size,
 * according to the sizes above.
 */
#ifdef COMMENT_ONLY
	u_char	ar_sha[];	/* sender hardware address */
	u_char	ar_spa[];	/* sender protocol address */
	u_char	ar_tha[];	/* target hardware address */
	u_char	ar_tpa[];	/* target protocol address */
#endif
};

#define ar_sha(ap)	(((caddr_t)((ap)+1)) +   0)
#define ar_spa(ap)	(((caddr_t)((ap)+1)) +   (ap)->ar_hln)
#define ar_tha(ap)	(((caddr_t)((ap)+1)) +   (ap)->ar_hln + (ap)->ar_pln)
#define ar_tpa(ap)	(((caddr_t)((ap)+1)) + 2*(ap)->ar_hln + (ap)->ar_pln)

#define arphdr_len2(ar_hln, ar_pln)					\
	(sizeof(struct arphdr) + 2*(ar_hln) + 2*(ar_pln))
#define arphdr_len(ap)	(arphdr_len2((ap)->ar_hln, (ap)->ar_pln))

/*
 * ARP ioctl request
 */
struct arpreq {
	struct	sockaddr arp_pa;		/* protocol address */
	struct	sockaddr_dl arp_ha;		/* hardware address */
	int	arp_flags;			/* flags */
};
/*  arp_flags and at_flags field values */
#define ATF_COM		0x02	/* completed entry (enaddr valid) */
#define	ATF_PERM	0x04	/* permanent entry */
#define	ATF_PUBL	0x08	/* publish entry (respond for other host) */
#define ATF_GRAT	0x100	/* send gratuitous ARP request */
#define ATF_BLACKHOLE	0x200	/* set blackhole flag on entry */

extern u_char	etherbroadcastaddr[6];

#ifdef __cplusplus
}
#endif
    
#endif /* !_NET_IF_ARP_H_ */
