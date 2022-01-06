/* if_types.h - interface types header file */
 
/* Copyright 2001 - 2005, 2012-2014 Wind River Systems, Inc. */
 
/*
 * Copyright (c) 1989, 1993, 1994
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
 *	@(#)if_types.h	8.3 (Berkeley) 4/28/95
 * $FreeBSD: src/sys/net/if_types.h,v 1.8.2.4 2002/12/23 23:02:21 kbyanc Exp $
 * $FreeBSD: src/sys/net/if_types.h,v 1.8.2.3 2001/07/03 11:01:41 ume Exp $
 */

/*
modification history
--------------------
13jan14,h_s      Remove GTF support. (US19989)
01o,09jan12,h_x  Move extern "C" after last header file include.
01n,20nov06,kch  Updated interface types.
01m,25oct06,kch  Removed unsupported interface types. Also corrected macro
                 mismatched for certain interface types.
01l,24may05,kch  Comment out IFT_IST define for now.
01k,13may05,kch  Merged from FreeBSD v 1.8.2.4.
01j,20nov03,niq  Remove copyright_wrs.h file inclusion
01i,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01h,04nov03,rlm  Ran batch header path update for header re-org.
01g,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01f,08aug03,nee  Merging from label ACCORDION_BASE6_MERGE_BASELINE in
                 accordion codeline to Base6
01e,10jun03,vvv  include netVersion.h
01d,15may03,spm  Tornado 2.2 FCS merge (SPR #76443; ver 01d,16may02,vvv:
                 TOR2_2-FCS-COPY label, tor2 branch, /wind/river VOB)
01c,09may03,spm  T2.2 FCS merge.
01b,09sep02,hsh  add c++ protection
01a,16jul01,ham  created from FreeBSD4.3-RELEASE(July-17-01).
 */

#ifndef _NET_IF_TYPES_H_
#define _NET_IF_TYPES_H_


#ifdef __cplusplus
extern "C" {
#endif

/*
 * Interface types for benefit of parsing media address headers.
 * This list is derived from the SNMP list of ifTypes, originally
 * documented in RFC1573, now maintained as:
 *
 * 	ftp.isi.edu/in-notes/iana/assignments/smi-numbers
 */

#define	IFT_OTHER       0x1     /* none of the following */
#define	IFT_ETHER       0x6     /* Ethernet CSMA/CD */
#define	IFT_PPP         0x17    /* RFC 1331 */
#define	IFT_LOOP        0x18    /* loopback */
#define IFT_IEEE80211   0x47    /* Radio spread spectrum */

#define IFT_L2VLAN      0x87    /* Layer 2 Virtual LAN using 802.1Q */
#define	IFT_PPPOE       0xf0    /* PPPoE */
#define IFT_TUNNEL      0xf1    /* IP over IP tunnel */
#define IFT_SOCKDEV     0xf2	/* Device that has a 1-to-1 mapping to a
                                   socket in the IP_AF_SOCKDEV domain */

#ifdef __cplusplus
}
#endif

#endif /* __INCif_typesh */
