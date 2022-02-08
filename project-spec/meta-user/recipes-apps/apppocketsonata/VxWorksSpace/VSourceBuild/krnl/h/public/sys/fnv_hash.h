/* fnv_hash.h */

/* Copyright 2001-2005, 2014 Wind River Systems, Inc. */

/*
 * Fowler / Noll / Vo Hash (FNV Hash)
 * http://www.isthe.com/chongo/tech/comp/fnv/
 *
 * This is an implementation of the algorithms posted above.
 * This file is placed in the public domain by Peter Wemm.
 *
 * $FreeBSD: src/sys/sys/fnv_hash.h,v 1.2.2.1 2001/03/21 10:50:59 peter Exp $
 */

/*
modification history
--------------------
01n,09jan12,h_x  Move extern "C" after last header file include.
01m,07feb05,vvv  _KERNEL cleanup
01l,17jan05,vvv  osdep.h cleanup
01k,16jul04,vvv  moved function definitions to fnvHash.c to fix compiler
		 warnings
01j,20nov03,niq  Remove copyright_wrs.h file inclusion
01i,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01h,04nov03,rlm  Ran batch header path update for header re-org.
01g,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01f,23jul03,vvv  added _KERNEL protection to fix warnings (SPR #89813)
01e,10jun03,vvv  include netVersion.h
01d,15may03,pas  changed u_int64_t (from internal types.h) to uint64_t
                 (from Tornado types.h)
01c,05may03,ppp  adding inclusion of clarinet.h for non-coreip build
01b,29apr03,syy  Added #ifdef for __cplusplus
01a,01jan03,pas  Ported from FreeBSD 4.7
*/

#ifndef __INCfnv_hashh
#define __INCfnv_hashh

#ifdef _WRS_KERNEL

#include <vxWorks.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t Fnv32_t;
typedef uint64_t Fnv64_t;

#define FNV1_32_INIT ((Fnv32_t) 33554467UL)
#define FNV1_64_INIT ((Fnv64_t) 0xcbf29ce484222325ULL)

#define FNV_32_PRIME ((Fnv32_t) 0x01000193UL)
#define FNV_64_PRIME ((Fnv64_t) 0x100000001b3ULL)

extern __inline Fnv32_t fnv_32_buf(const void *buf, size_t len, Fnv32_t hval);

extern __inline Fnv32_t fnv_32_str(const char *str, Fnv32_t hval);

extern __inline Fnv64_t fnv_64_buf(const void *buf, size_t len, Fnv64_t hval);

extern __inline Fnv64_t fnv_64_str(const char *str, Fnv64_t hval);

#ifdef __cplusplus
}
#endif

#endif

#endif /* ! __INCfnv_hashh */
