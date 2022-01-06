/* mqueueCommon.h - POSIX usr/kernel shared message queue header file */

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
01g,28apr10,pad  Moved extern C statement after include statements.
01f,13mar06,kk   added _Restrict keyword to mq_setattr() in user land
01e,12feb06,kk   make mq_attr POSIX conformant (SPR# 114488)
01d,05jan06,jln  added definition of _VX_PX_MQ_NAME_MAX and _VX_PX_MQ_PATH_MAX
01c,22aug05,kk   moved RTP or kernel specific prototypes to mqueue.h
01b,07jul05,kk   move MQ_PRIO_MAX into kernel, user level has it in limits.h
01a,14nov03,m_s  code-inspection changes
01a,31oct03,m_s  Written
*/

#ifndef __INCmqueueCommonh
#define __INCmqueueCommonh


/* includes */

#include <fcntl.h>
#include <sigevent.h>

#ifndef _WRS_KERNEL
#include <sys/cdefs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define MQ_NUM_MSGS_DEFAULT	16	/* default messages per queue */
#define MQ_MSG_SIZE_DEFAULT	16	/* default message size in bytes */

/*
 * _VX_PX_MQ_NAME_MAX is the maximum number of bytes in a
 * filename (not including terminating null)
 */
                                                                                               
#define _VX_PX_MQ_NAME_MAX	255 
                                                                                               
/*
 * _VX_PX_MQ_PATH_MAX is the maximum number of bytes in a
 * pathname, including the terminating null character
 */

#define _VX_PX_MQ_PATH_MAX	255

/* typedefs */

/* message queue attributes */

struct mq_attr
    {
    long	mq_maxmsg;
    long	mq_msgsize;
    long	mq_flags;
    long	mq_curmsgs;
    };

/* message queue descriptor for applications */

struct mq_des;
typedef struct mq_des * mqd_t;

/* function declarations */

/* mq_receive() and mq_send() are in mqueue.h */

extern mqd_t mq_open    (const char *, int, ...);
extern int   mq_close   (mqd_t);
extern int   mq_unlink  (const char *);
extern int   mq_notify  (mqd_t, const struct sigevent *);
extern int   mq_getattr (mqd_t, struct mq_attr *);

#ifdef _WRS_KERNEL
extern int   mq_setattr (mqd_t, const struct mq_attr *, struct mq_attr *);
#else /* for user land */
extern int   mq_setattr (mqd_t, 
                         const struct mq_attr * _Restrict, 
			 struct mq_attr * _Restrict);
#endif

#ifdef __cplusplus
}
#endif

#endif	/* INCmqueueCommonh */
