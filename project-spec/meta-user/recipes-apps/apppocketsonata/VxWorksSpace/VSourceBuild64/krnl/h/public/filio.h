/* filio.h - file-related ioctl definitions */

/* Copyright 2001-2003 Wind River Systems, Inc. */

/*-
 * Copyright (c) 1982, 1986, 1990, 1993, 1994
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
 *	@(#)filio.h	8.1 (Berkeley) 3/28/94
 * $FreeBSD: src/sys/sys/filio.h,v 1.7 1999/12/07 22:25:28 sos Exp $
 */

/*
modification history
--------------------
01f,05sep06,kch  Cleanup for IPNet integration.
01e,20nov03,niq  Remove copyright_wrs.h file inclusion
01d,04nov03,rlm  Ran batch header path update for header re-org.
01c,29apr03,syy  Added #ifdef for __cplusplus
01b,17sep01,ann  uncommenting the inclusion of ioccom.h
01a,15aug01,ann  ported to clarinet from freeBSD 4.3 ver 1.7
 */

#ifndef	_SYS_FILIO_H_
#define	_SYS_FILIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#define	FIOASYNC	_IOW('f', 125, int)	/* set/clear async i/o */

#ifdef __cplusplus
}
#endif

#endif /* !_SYS_FILIO_H_ */
