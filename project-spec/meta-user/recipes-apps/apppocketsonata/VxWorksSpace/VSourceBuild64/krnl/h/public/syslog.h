/* syslog.h - the system message logger header file */

/*
 * Copyright (c) 2001, 2003-2006, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * Copyright (c) 1982, 1986, 1988, 1993
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
 *	@(#)syslog.h	8.1 (Berkeley) 6/2/93
 * $FreeBSD: src/sys/sys/syslog.h,v 1.19.2.2 2001/05/29 13:15:08 dwmalone Exp $
 */

/*
modification history
--------------------
30mar15,h_k  added closelog(), openlog(), setlogmask(), syslog(), vsyslog(),
             syslogFdSet(). 
             re-defined LOG_XXX macros. (F2865)
             removed dependency to applUtilLib.
25oct06,kch  Removed unused defines that were previously commented out.
07feb05,vvv  _KERNEL cleanup
03sep04,dlk  Reimplement in terms of applUtilLib.
20nov03,niq  Remove copyright_wrs.h file inclusion
05nov03,cdw  Removal of unnecessary _KERNEL guards.
04nov03,rlm  Ran batch header path update for header re-org.
29apr03,syy  Added #ifdef for __cplusplus
12oct01,ppp  undef'd log temporarily for board bringup
05sep01,ham  renamed printf to PRINTF.
05sep01,ham  created from FreeBSD4.3-RELEASE(July-17-01).
*/

#ifndef _SYS_SYSLOG_H_
#define _SYS_SYSLOG_H_

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	_PATH_LOG	"/var/run/log"
#define	_PATH_OLDLOG	"/dev/log"	/* backward compatibility */


#define	LOG_PRIMASK	0x07	/* mask to extract priority part (internal) */
				/* extract priority */
#define	LOG_PRI(p)	((p) & LOG_PRIMASK)
#define	LOG_MAKEPRI(fac, pri)	((fac) | (pri))

/* priority codes */

#define LOG_EMERG	0		/* panic condition */
#define LOG_ALERT	1		/* condition that should be corrected
					 * immediately
					 */
#define LOG_CRIT	2		/* critical condition */
#define LOG_ERR		3		/* error */
#define LOG_WARNING	4		/* warning message */
#define LOG_NOTICE	5		/* condition that is not error
					 * condition, but that may require
					 * special handling
					 */
#define LOG_INFO	6		/* informational message */
#define LOG_DEBUG	7		/* message that contains information
					 * normally of use only when debugging
					 * a program
					 */

/* facility codes */

#define	LOG_KERN	(0 << 3)	/* kernel messages */
#define	LOG_USER	(1 << 3)	/* random user-level messages */
#define	LOG_MAIL	(2 << 3)	/* mail system */
#define	LOG_DAEMON	(3 << 3)	/* system daemons */
#define	LOG_AUTH	(4 << 3)	/* authorization messages */
#define	LOG_SYSLOG	(5 << 3)        /* generated internally by syslogd */
#define	LOG_LPR		(6 << 3)	/* line printer subsystem */
#define	LOG_NEWS	(7 << 3)	/* network news subsystem */
#define	LOG_UUCP	(8 << 3)	/* UUCP subsystem */
#define	LOG_CRON	(9 << 3)	/* clock daemon */
#define	LOG_AUTHPRIV	(10 << 3)	/* authorization messages (private) */
				/* Facility #10 clashes in DEC UNIX, where */
				/* it's defined as LOG_MEGASAFE for AdvFS  */
				/* event logging.                          */
#define	LOG_FTP		(11 << 3)	/* ftp daemon */

/* other codes through 15 reserved for system use */

#define	LOG_LOCAL0	(16 << 3)	/* reserved for local use */
#define	LOG_LOCAL1	(17 << 3)	/* reserved for local use */
#define	LOG_LOCAL2	(18 << 3)	/* reserved for local use */
#define	LOG_LOCAL3	(19 << 3)	/* reserved for local use */
#define	LOG_LOCAL4	(20 << 3)	/* reserved for local use */
#define	LOG_LOCAL5	(21 << 3)	/* reserved for local use */
#define	LOG_LOCAL6	(22 << 3)	/* reserved for local use */
#define	LOG_LOCAL7	(23 << 3)	/* reserved for local use */

/* current number of facilities */

#define	LOG_NFACILITIES	64		/* 0-62 are used by ipcom_syslog */
#define	LOG_FACMASK	0x3f8		/* mask to extract facility part */
					/* facility of pri */
#define	LOG_FAC(p)	(((p) & LOG_FACMASK) >> 3)

/*
 * arguments to setlogmask.
 */

#define	LOG_MASK(pri)	(1 << (pri))		/* mask for one priority */

/*
 * Option flags for openlog.
 *
 * LOG_ODELAY, LOG_NDELAY, LOG_NOWAIT, LOG_PERROR no longer does anything.
 */

#define	LOG_PID		0x01	/* log the pid with each message */
#define	LOG_CONS	0x02	/* log on the console if errors in sending */
#define	LOG_ODELAY	0x04	/* delay open until first syslog() */
#define	LOG_NDELAY	0x08	/* don't delay open */
#define	LOG_NOWAIT	0x10	/* don't wait for console forks */
#define	LOG_PERROR	0x20	/* log to stderr as well */

extern void syslog (int priority, const char * message, ...);

extern void vsyslog (int priority, const char * message, va_list vaList);

extern void openlog (const char * ident, int logopt, int facility);

extern void closelog (void);

extern int setlogmask (int maskpri);

extern void syslogFdSet (int fd);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_SYSLOG_H_ */
