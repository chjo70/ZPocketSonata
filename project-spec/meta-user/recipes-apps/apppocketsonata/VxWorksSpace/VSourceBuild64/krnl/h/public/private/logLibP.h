/* logLibP.h - private header for logLib logging facility */

/*
 * Copyright (c) 2004, 2008, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/* modification history
--------------------
07may15,h_k  added pend log message type. (V7COR-2909)
03apr15,h_k  added syslog support. (F2865)
15sep08,rlp  Added logFdFromRlogin definition (CQ:WIND00116711).
17sep04,dlk  written,
*/

#ifndef __INClogLibPh
#define __INClogLibPh

#include <vxWorks.h>
#include <logLib.h>
#include <private/semLibP.h>
#include <private/syslogLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* definitions */

#define LOG_MSG_TYPE		0
#define SYSLOG_MSG_TYPE		1

#ifdef	_WRS_CONFIG_IPCOM_DEFAULT_SYSLOG_PRIORITY
#define IPCOM_SYSLOG_MSG_TYPE	2
#endif	/* _WRS_CONFIG_IPCOM_DEFAULT_SYSLOG_PRIORITY */

#define PEND_LOG_MSG_TYPE	3

/*
 * These two should arguably be in a public header, as
 * they refer to the public API.
 */

#define MAX_LOGARGS	6	/* max args to log message */
#define MAX_LOGFDS	5	/* max log fds */

/* types */

/* pend log message structure, used between usrBanner() */

typedef struct  pendLogMsg		/* PEND_LOG_MSG */
    {
    int		msgType;		/* type of the message */
    SEM_ID	semId;			/* ID of binary semaphore */
    } PEND_LOG_MSG;

/*
 * The FD array and the semaphore which guards it are made
 * external since they are shared by nbioLogLib.
 */

extern SEMAPHORE logFdSem;

extern MSG_Q_ID logMsgQId;
extern int logFd [MAX_LOGFDS];
extern int numLogFds;

extern int logTaskPriority;

extern int logFdFromRlogin;

extern void (*_func_syslogEarlyMsgHandle) (void);

extern STATUS (*_func_syslogMsgHandle) (SYSLOG_MSG * pSyslogMsg,
					ssize_t msgLen);

extern STATUS (*_func_syslogInit) (int fd, int maxMsgs);

#ifdef __cplusplus
    }
#endif

#endif /* __INClogLibPh */

