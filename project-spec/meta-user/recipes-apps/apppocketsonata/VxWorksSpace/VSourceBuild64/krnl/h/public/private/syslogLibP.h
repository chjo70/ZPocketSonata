/* syslogLibP.h - private header for syslogLib logging facility */

/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
24mar16,dlk  syslog wrapper function takes const char * buffer argument.
09jul15,jpb  removed dependency on hostLib (V7PRO-2239)
25mar15,h_k  created. (F2865)
*/

#ifndef __INCsyslogLibPh
#define __INCsyslogLibPh

#include <vxWorks.h>
#include <taskLib.h>
#include <stdarg.h>
#include <time.h>
#ifdef	_WRS_CONFIG_IPNET_COREIP
#include <hostLib.h>
#endif /* _WRS_CONFIG_IPNET_COREIP */

#ifdef __cplusplus
extern "C" {
#endif

/* definitions */

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 	64
#endif /* !MAXHOSTNAMELEN */

#define SYSLOG_MAX_IDENT	128	/* Maximum length of identification.
					 * RFC5425 stipulates that this
					 * maximum length should be exactly 128
					 * bytes.
					 */

#define SYSLOG_MAX_MESSAGE_LEN  480     /* Maximum length of a fully formatted
					 * message.
					 * RFC5424 stipulates that this
					 * maximum length should be at least
					 * 480 bytes.
                                         */

#define SYSLOG_MSG_Q_NAME	"/logMsgQueue"

#define SYSLOG_OUTPUT_FORMAT                                            \
        "<%d>1 %04d-%02d-%02dT%02d:%02d:%02d.%06dZ %s %s %s - - %s\n"

/*
 * max output string size:
 *
 * Adjust sizes of PRI(+1), DATE-FULLYEAR(+0), DATE-MONTH(-2), DATE-MDAY(-2),
 * TIME-HOUR(-2), TIME-MINUTE(-2), TIME-SECOND(-2), TIME-SECFRAC(+2), HOSTNAME,
 * APP-NAME, PROCID, MSG and end of string(-1).
 */

#define SYSLOG_MAX_OUTPUT                                               \
        (sizeof(SYSLOG_OUTPUT_FORMAT) + 1 + 0 - 2 - 2 - 2 - 2 - 2 + 2 +	\
         (MAXHOSTNAMELEN - sizeof("%s")) +				\
	 ((VX_TASK_NAME_LENGTH + 1) - sizeof("%s")) +			\
         (SYSLOG_MAX_IDENT - sizeof("%s")) +				\
	 (SYSLOG_MAX_MESSAGE_LEN - sizeof("%s")) - 1)

extern STATUS syslogFdAndWrapperSet (int fd,
				     ssize_t (*wrapper) (int, const char *, size_t));

/* types */

/* syslog message structure */

typedef struct syslogMsg
    {
    int         msgType;                        /* type of the message */
    struct timespec tp;                         /* timestamp */
    int         priority;                       /* priority */
    int         log_stat;                       /* log option */
    char        name [VX_TASK_NAME_LENGTH + 1]; /* application name */
    char        ident [SYSLOG_MAX_IDENT];       /* identification */
    char        msgBody [SYSLOG_MAX_MESSAGE_LEN]; /* formatted message body */
    } SYSLOG_MSG;

/* IPCOM syslog message structure */

typedef struct ipcom_syslogMsg
    {
    int         msgType;                        /* type of the message */
    void *	se;				/* pointer to IPCOM syslog
						 * entry
						 */
    } IPCOM_SYSLOG_MSG;

extern void (* _func_ipcom_syslogd) (void * se);

extern void (* _func_syslogMsgSendFromIpcom) (void * se);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* __INCsyslogLibPh */
