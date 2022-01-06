/* in_cksum.h - x86 version in_cksum header file */

/* Copyright 2001-2005, 2014 Wind River Systems, Inc. */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
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
 *	from tahoe:	in_cksum.c	1.2	86/01/05
 *	from:		@(#)in_cksum.c	1.3 (Berkeley) 1/19/91
 *	from: Id: in_cksum.c,v 1.8 1995/12/03 18:35:19 bde Exp
 * $FreeBSD: src/sys/i386/include/in_cksum.h,v 1.7.2.1 2000/05/05 13:37:00 jlemon Exp $
 */

/*
modification history
--------------------
13feb14,ylu  moved this file from h/arch/i86 to here and renamed it. (VXW7-1325) 
22jan14,jmz  US25084 - Fix compiler warnings
25aug05,dlk  Add section tags.
24mar04,m_h  Internet Checksum
18mar04,m_h  moved to arch/i86
20nov03,niq  Remove copyright_wrs.h file inclusion
18nov03,rp   updated header file path
25jul02,rvr  removed DCC specific code
13sep01,hsh  Created from BSD 4.3
*/
 
 
#ifndef _MACHINE_IN_CKSUM_H_
#define	_MACHINE_IN_CKSUM_H_	1

#include <sys/cdefs.h>

/*
 * in_cksum_hdr - checksum on header only
 *
 * It is useful to have an Internet checksum routine which is inlineable
 * and optimized specifically for the task of computing IP header checksums
 * in the normal case (where there are no options and the header length is
 * therefore always exactly five 32-bit words.
 */

static __inline u_int
in_cksum_hdr
    (
    const struct ip *ip
    )
    {
    register u_int sum = 0;
    int hlen = sizeof (struct ip);
    register u_short *w = (u_short *) ip;
    u_short remaining = 0;
        
    while (hlen > 1)
        {
        sum += *w++;
        hlen -= 2;
        }

    if (hlen == 1)
        {
        *(u_char *) (&remaining) = *(u_char *) w;
        sum += remaining;
        }
        
    sum = (sum & 0xffff) + (sum >> 16);
    if (sum > 0xffff)
        sum -= 0xffff;

    return ~sum & 0xffff;
    }

/*
 * in_cksum_update
 */

static __inline void
in_cksum_update
    (
    struct ip *ip
    )
    {
    int __tmpsum;
    __tmpsum = (int)ntohs(ip->ip_sum) + 256;
    ip->ip_sum = (u_short) htons(__tmpsum + (__tmpsum >> 16));
    }

/*
 * in_pseudo - pre-checksum parts of pseudo-header
 *
 * Compute significant parts of the IPv4 checksum pseudo-header * for use in a
 * delayed TCP/UDP checksum calculation.
 *
 * Args:
 *
 *  src	     Source IP address
 *  dst	     Destination IP address
 *  lenproto htons(proto-hdr-len + proto-number)
 */

static __inline u_int16_t in_pseudo
    (
    u_int32_t src,
    u_int32_t dst,
    u_int32_t lenproto
    )
    {
    u_int32_t sum;

    sum = lenproto +
        (u_int16_t)(src >> 16) +
        (u_int16_t)(src /*& 0xffff*/) +
        (u_int16_t)(dst >> 16) +
        (u_int16_t)(dst /*& 0xffff*/);
    
    sum = (u_int16_t)(sum >> 16) + (u_int16_t)(sum /*& 0xffff*/);

    if (sum > 0xffff)
        sum -= 0xffff;
    
    return ((u_int16_t) sum);
    }

/*
 * in_addword - Add two 16-bit workd
 *
 * Add the two 16-bit network-order values, carry, and return.
 */

static __inline u_int16_t in_addword
    (
    u_int16_t a,
    u_int16_t b
    )
    {
    u_int32_t sum = a + b;

    if (sum > 0xffff)
        sum -= 0xffff;

    return ((u_int16_t) sum);
    }

_WRS_FASTTEXT
u_short	in_cksum_skip(struct mbuf *m, int len, int skip); 

#endif /* _MACHINE_IN_CKSUM_H_ */
 

