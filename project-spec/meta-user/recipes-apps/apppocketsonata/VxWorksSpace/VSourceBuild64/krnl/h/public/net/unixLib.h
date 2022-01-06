/* unixLib.h - UNIX kernel compatability library header file */

/*
 * Copyright (c) 1984-2006, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01v,09jan12,h_x  Move extern "C" after last header file include.
01u,06sep06,kch  Removed unsupported prototypes for IPNet integration.
01t,19jun06,jpb  Removed I960 check
01s,26aug05,dlk  Add section tags.
01r,12jul05,kch  Removed _netMalloc() and _netFree() prototypes.
01q,07jul05,dlk  Balance parenthesis in wakeup_one().
01p,18may05,rp   moved ppsratecheck from icmp6.c to unixLib
01o,19apr05,rp   merged from comp_wn_ipv6_mld_interim-dev
01n,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01m,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
01l,03dec03,asr  Fix compile errors after dinkum libc check-in
01k,20nov03,niq  Remove copyright_wrs.h file inclusion
01j,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01i,04nov03,rlm  Ran batch header path update for header re-org.
01h,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01g,10jun03,vvv  include netVersion.h
01f,09may03,vvv  included semLib.h and times.h
01e,09oct01,hsh  add phashinit routine
01d,26sep01,qli  chaning the prototype for "panic"
01c,18sep01,ann  adding the prototype of tvToTicks
01b,05sep01,ham  corrected microtime's prototype.
01a,01sep01,ann  ported to clarinet from AE1.1 version 01f,
                 added the prototypes for microtime()
*/

#ifndef __INCunixLibh
#define __INCunixLibh

#ifdef _WRS_KERNEL
#include <sys/times.h>
#else
#include <sys/time.h> /* For RTP, it is sys/time.h */
#endif
#include <semLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MALLOC(space, cast, size, type, flags) { \
    (space) = (cast) netClusterGet (_pNetSysPool,                 \
                                    netClPoolIdGet (_pNetSysPool, \
				                    size, TRUE)); \
}						 

#define FREE(addr, type) { \
    netClFree (_pNetSysPool, (unsigned char *) addr); \
}			   

#define DATA_TO_MBLK(pBuf)	\
     (*((struct mbuf **)((char *)(pBuf) - sizeof(struct mbuf **))))
            
/* Function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern void	panic(const char *, ...);

#else	/* __STDC__ */

extern void 	panic ();

#endif	/* __STDC__ */

/*
 * BSD defines wakeup() to wake up all tasks sleeping on
 * the specified channel. wakeup_one() wakes up a single process
 * (more or less). VxWorks' tsleep() and ksleep() have been modified to
 * give up splSemId and take the awaited semaphore atomically, which is
 * necessary whether semFlush() or semGive() is used.
 * Note, VxWorks has in the past incorrectly made wakeup() equivalent
 * to semGive() rather than semFlush().
 */

#define wakeup(semId) ((void)semFlush((semId)))
#define wakeup_one(semId) ((void)semGive((semId)))

#ifdef __cplusplus
}
#endif

#endif /* __INCunixLibh */
