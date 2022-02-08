/* systm.h */

/* Copyright 2001-2005,2014 Wind River Systems, Inc. */

/*-
 * Copyright (c) 1982, 1988, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
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
 *	@(#)systm.h	8.7 (Berkeley) 3/29/95
 * $FreeBSD: src/sys/sys/systm.h,v 1.111.2.5 2001/01/16 12:26:21 phk Exp $
 */

/*
modification history
--------------------
13jan14,h_s      Remove GTF support. (US19989)
01u,09jan12,h_x  Move extern "C" after last header file include.
01t,11apr05,sar  Use gtfTimeout and gtfUntimeout directly instead of via
                 macros and replace global tm with gtfTimerMangaerCB
                 Removed timeout and untimeout.
01s,06apr05,vvv  restored copyin/copyout to macros to fix warnings
                 (SPR #106982)
01r,09feb05,sar  Move gtf include files per GTF code inspection of 10/26/2004
01q,07feb05,vvv  _KERNEL cleanup
01p,17mar04,rp   updated to build for 5.5
01o,20nov03,niq  Remove copyright_wrs.h file inclusion
01n,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01m,04nov03,rlm  Ran batch header path update for header re-org.
01l,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01k,27oct03,cdw  update include statements post header re-org.
01j,02jul03,vvv  added _KERNEL protection for copyin and copyout
01i,14may03,vvv  included taskLib.h
01h,09may03,vvv  included string.h
01g,24apr03,syy  Make copyin() and copyout() static to avoid duplicated
                 symbols
01f,18apr03,syy  Fixed compiler warnings
01e,10sep02,hsh  add c++ protection
01d,28mar02,ppp  changing it for tornado build environment
01c,17sep01,ppp  adding the macro for lmin
01b,13sep01,ann  un commenting certain defines that will be needed
01a,06jun01,deg  ported.
*/


#ifndef _SYS_SYSTM_H_
#define	_SYS_SYSTM_H_

#include <string.h>

#include "taskLib.h"
#include "semLib.h"

#ifdef __cplusplus
 extern "C" {
#endif 

#ifdef _WRS_KERNEL

#define ovbcopy         bcopy                   /* overlapped buffer copy */

#define copyout(from, to, len)  (bcopy (from, to, len), OK)
#define copyin(from, to, len)   (bcopy (from, to, len), OK)

#define imin(a,b)       (((a) < (b)) ? (a) : (b))       /* interger min */
#define lmin(a,b)       ((a) < (b) ? (a) : (b))         /* long min */

#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif
    
#endif /* !_SYS_SYSTM_H_ */
