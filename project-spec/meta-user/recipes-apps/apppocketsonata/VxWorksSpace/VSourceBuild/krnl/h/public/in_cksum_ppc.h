/* in_cksum.h - ppc version in_cksum routines */

/* Copyright 2001-2002, 2014 Wind River Systems, Inc. */
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
 * $FreeBSD: src/sys/ppc/include/in_cksum.h,v 1.5 2000/05/06 18:18:31 jlemon Exp $
 */
/*
modification history
--------------------
13feb14,ylu  moved this file from h/arch/ppc to here and renamed it. (VXW7-1325) 
01e,25aug05,dlk  Add section tags.
01d,24mar04,m_h  Internet Checksum
01c,17mar04,m_h  move to h/arch/ppc, move misc funcs from in_cksum.c
01b,05nov03,rlm  Ran batch header update for header re-org.
01a,11jul02,hsh  Created from BSD 4.3
*/

#ifndef _MACHINE_IN_CKSUM_H_
#define	_MACHINE_IN_CKSUM_H_	1

#include <sys/cdefs.h>

union in_cksum_l_util {
	u_int16_t s[2];
	u_int32_t l;
};

union in_cksum_q_util {
	u_int16_t s[4];
	u_int32_t l[2];
	u_int64_t q;
};

#define IN_CKSUM_ADDCARRY(x)  (x > 65535 ? x -= 65535 : x)

#define IN_CKSUM_REDUCE16                                                 \
    {									  \
	in_cksum_q_util.q = sum;                                          \
	in_cksum_l_util.l = in_cksum_q_util.s[0] + in_cksum_q_util.s[1] + \
		in_cksum_q_util.s[2] + in_cksum_q_util.s[3];              \
	sum = in_cksum_l_util.s[0] + in_cksum_l_util.s[1];                \
	IN_CKSUM_ADDCARRY(sum);                                           \
    }

#define IN_CKSUM_REDUCE2 {in_cksum_l_util.l = sum;                           \
                          sum = in_cksum_l_util.s[0] + in_cksum_l_util.s[1]; \
                          IN_CKSUM_ADDCARRY(sum);}

/*
 * in_addword - Add two 16-bit workd
 *
 * Add the two 16-bit network-order values, carry, and return.
 */

static __inline
u_short in_addword
    (
    u_short a,
    u_short b
    )
    {
    u_int64_t sum = a + b;

    IN_CKSUM_ADDCARRY(sum);
    return (sum);
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

static __inline
u_short in_pseudo
    (
    u_int32_t a,
    u_int32_t b,
    u_int32_t c
    )
    {
    u_int64_t sum;
    union in_cksum_q_util in_cksum_q_util;
    union in_cksum_l_util in_cksum_l_util;
    
    sum = (u_int64_t) a + b + c;
    IN_CKSUM_REDUCE16;
    return (sum);
    }


/*
 * in_cksum_update
 */

static __inline
void in_cksum_update
    (
    struct ip *ip
    )
    {
    int __tmpsum;
    __tmpsum = (int)ntohs(ip->ip_sum) + 256;
    ip->ip_sum = htons(__tmpsum + (__tmpsum >> 16));
    }

/*
 * in_cksum_hdr - checksum on header only
 *
 * It is useful to have an Internet checksum routine which is inlineable
 * and optimized specifically for the task of computing IP header checksums
 * in the normal case (where there are no options and the header length is
 * therefore always exactly five 32-bit words.
 */

static __inline
u_int in_cksum_hdr
    (
    const struct ip *ip
    )
    {
    register u_int sum = 0;
    register u_short *w;
    union in_cksum_l_util in_cksum_l_util;
	
    w = (u_short*) ip;

    sum += w[0]; 
    sum += w[1]; 
    sum += w[2]; 
    sum += w[3]; 
    sum += w[4];

    IN_CKSUM_REDUCE2;

    sum += w[5];	
    sum += w[6];
    sum += w[7];
    sum += w[8];
    sum += w[9]; 

    IN_CKSUM_REDUCE2;

    return ~sum & 0xffff;

    }

_WRS_FASTTEXT
u_short	in_cksum_skip(struct mbuf *m, int len, int skip);

#endif /* _MACHINE_IN_CKSUM_H_ */
