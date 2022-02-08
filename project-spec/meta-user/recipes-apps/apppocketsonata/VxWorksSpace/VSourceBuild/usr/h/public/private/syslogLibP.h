/* syslogLibP.h - private header for syslogLib logging facility */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
25mar15,h_k  created. (F2865)
*/

#ifndef __INCsyslogLibPh
#define __INCsyslogLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* definitions */

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

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* __INCsyslogLibPh */
