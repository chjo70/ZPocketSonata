/* inet.h - Internet header */

/* Copyright 1986 - 2005 Wind River Systems, Inc. */

/*
 * Copyright (c) 1983 Regents of the University of California.

 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *      @(#)inet.h      5.2 (Berkeley) 6/27/88
 */

/*
modification history
--------------------
01r,09jan12,h_x  Move extern "C" after last header file include.
01q,22jun10,h_x  Fix WIND00219346
01p,27mar08,nlu  WIND00108893
01o,08nov06,kch  Removed prototypes not specified in Posix specification.
01n,29jun05,vvv  added inet_ntop() and inet_pton() for RFC3542
01m,04mar04,ann  Removed #ifndef _KERNEL protection for including in.h
                 as this file is required for defining struct in_addr.
01l,20nov03,niq  Remove copyright_wrs.h file inclusion
01k,04nov03,rlm  Ran batch header path update for header re-org.
01j,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01i,13jun03,syy  Added prototype for inet_ntoa_b() (SPR#88384)
01h,09may03,vvv  included in.h
01g,26jul99,spm  added ansi/c++ prototypes for routines (SPR #5307)
01f,22sep92,rrr  added support for c++
01e,26may92,rrr  the tree shuffle
01d,04oct91,rrr  passed through the ansification filter
                  -changed copyright notice
01c,05oct90,shl  added copyright notice.
                 added title.
01b,16apr89,gae  updated to new 4.3BSD.
01a,22dec86,rdc  created.
*/

#ifndef __INCineth
#define __INCineth

#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * External definitions for
 * functions in inet(3N)
 */

extern  uint32_t        inet_addr (const char *);
extern  char *          inet_ntoa (struct in_addr);
extern const char *     inet_ntop (int af, const void *src, char *dst,
                                   size_t size);
extern int              inet_pton (int af, const char *src, void *dst);
extern int              inet_aton (const char * cp, struct in_addr * addrPtr);

#ifdef __cplusplus
}
#endif

#endif /* __INCafh */
