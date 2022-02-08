/* mqueue.h - user level header for POSIX message queues */

/*
 * Copyright (c) 2003, 2005-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01i,29jul10,pad  Moved extern C statement after include statements.
01h,13mar06,kk   added _Restrict to POSIX APIs
01g,22feb06,pad  Added forward declaration of timespec structure.
01f,01feb06,mil  Updated for POSIX namespace conformance (P1).
01e,25jan06,yvp  mq_timedreceive, mq_timedsend prototypes changed to conform
                 to Posix std.
01d,09jan06,yvp  Added prototypes for mq_timedsend and mq_timedreceive.
01c,22aug05,kk   moved user specific prototypes here
01b,05dec03,m_s  code-inspection changes
01a,31oct03,m_s  Written
*/

#ifndef __INCmqueueh
#define __INCmqueueh


/* includes */

#include <sys/cdefs.h>		/* for _Restrict */
#include <sys/types.h>          /* for ssize_t */
#include <mqueueCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

struct timespec;

/* function declarations */

/* other prototypes in mqueueCommon.h */

extern int      mq_send         (mqd_t, const char *, size_t, unsigned);
extern int      mq_timedsend    (mqd_t, const char *, size_t, unsigned,
				 const struct timespec *);
extern ssize_t  mq_receive      (mqd_t, char *, size_t, unsigned *);
extern ssize_t  mq_timedreceive (mqd_t, char * _Restrict, size_t, 
                                 unsigned * _Restrict,
				 const struct timespec * _Restrict);

#ifdef __cplusplus
}
#endif

#endif	/* INCmqueueh */
