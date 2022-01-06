/* ifconfig.h - interface configuation */

/* Copyright 2002 - 2006, 2014 Wind River Systems, Inc. */

/*
 * Copyright (c) 1997 Peter Wemm.
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
 *      This product includes software developed for the FreeBSD Project
 *	by Peter Wemm.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * so there!
 *
 * $FreeBSD: src/sbin/ifconfig/ifconfig.h,v 1.5.2.2 2001/07/04 20:49:20 brooks Exp $
 */

/*
modification history
--------------------
01n,09jan12,h_x  Move extern "C" after last header file include.
01m,04oct06,kch  Removed unsupported prefix prototype.
01l,07sep05,kch  Removed prototypes for vlan pseudo interface.
01k,27aug05,kch  Added setvlanpriority() prototype.
01j,23aug05,dlk  Fix compiler warning.
01i,04aug05,kch  Added ifconfig_vlan.c prototypes.
01h,20nov03,niq  Remove copyright_wrs.h file inclusion
01g,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01f,04nov03,rlm  Ran batch header path update for header re-org.
01e,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01d,10jun03,vvv  include netVersion.h
01c,14may03,vvv  added ifconfig()
01b,29apr03,syy  Added #ifdef's for inclusion and __cplusplus
01a,23jan02,deg  ported from FreeBSD
*/

#ifndef __INCifconfigh
#define __INCifconfigh


#ifdef __cplusplus
extern "C" {
#endif

extern int  ifconfig (char *);

#ifdef __cplusplus
}
#endif

#endif /* ! __INCifconfigh */

