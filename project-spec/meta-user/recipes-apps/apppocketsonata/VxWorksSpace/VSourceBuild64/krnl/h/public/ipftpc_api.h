/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPFTPC_API_H
#define IPFTPC_API_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include "ipcom.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* Select level of verbosity for syslog messages */
#ifdef IPCOM_SYSLOG_PRIORITY
#undef IPCOM_SYSLOG_PRIORITY
#endif
#if defined(_WRS_CONFIG_IPFTPC_SYSLOG_PRIORITY)
#define IPCOM_SYSLOG_PRIORITY    _WRS_CONFIG_IPFTPC_SYSLOG_PRIORITY
#else
#define IPCOM_SYSLOG_PRIORITY    IPCOM_LOG_WARNING
#endif


/* Transport protocol for FTPC */
#ifdef IPFTPC_USE_SCTP
#define IPFTPC_PROTO IP_IPPROTO_SCTP
#else
#define IPFTPC_PROTO 0
#endif

/* Error classes */
#define IPFTPC_CFTPS            0       /* FTP server error (RFC 959) */
#define IPFTPC_CFTPC            1000    /* FTP client error (IPFTPC_Exxx) */
#define IPFTPC_CACCEPT          2000    /* Accept failed */
#define IPFTPC_CBIND            3000    /* Bind failed */
#define IPFTPC_CCONNECT         4000    /* Connect failed */
#define IPFTPC_CLISTEN          5000    /* Listen failed */
#define IPFTPC_COPEN            6000    /* Open failed */
#define IPFTPC_CREAD            7000    /* Read failed */
#define IPFTPC_CMUTEX           8000    /* Read failed */
#define IPFTPC_CSCLOSE          9000    /* Socket close failed */
#define IPFTPC_CSELECT          10000   /* Select failed */
#define IPFTPC_CSOCKET          11000   /* Socket failed */
#define IPFTPC_CWRITE           12000   /* Write failed */

#define IPFTPC_GET_C(x) ((x) - IPFTPC_GET_E(x))

/* Error codes */
#define IPFTPC_ESUCCESS         299     /* Success (in the FTP server group
                                           so that x / 100 == 2) */
#define IPFTPC_EBUSY            901     /* Session is busy */
#define IPFTPC_ECONSOLE         902     /* Console write error */
#define IPFTPC_EID              903     /* Invalid ID */
#define IPFTPC_EINVHOST         904     /* Invalid host */
#define IPFTPC_ENOMEM           905     /* Out of memory */
#define IPFTPC_EPORT            906     /* Invalid port */
#define IPFTPC_ESESSIONMAX      907     /* No more sessions allowed */
#define IPFTPC_ETIMEOUT         908     /* Timeout */

#ifdef IPFTP_TLS
#define IPFTPC_ETLS				909
#endif

#define IPFTPC_GET_E(x) ((x) % 1000)

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* Session ID */
typedef Ip_u16 Ipftpc_id;

/* Generic IP address */
typedef union
{
    struct Ip_sockaddr sa;              /* Generic address */
    struct Ip_sockaddr_in sin;          /* IPv4 address */
#ifdef IPCOM_USE_INET6
    struct Ip_sockaddr_in6 sin6;        /* IPv6 address */
#endif
}
Ipftpc_addr;

/* Session attributes */
typedef struct Ipftpc_attr
{
    Ip_bool extended;                   /* Use extended addressing */
    Ip_bool passive;                    /* Passive mode */
    Ip_bool ipcheck;                    /* Disable proxy FTP */
    Ip_bool verbose;                    /* Enable verbose printouts */
    Ip_bool fb_extended;                /* Allow fallback extended->normal */
    Ip_bool fb_passive;                 /* Allow fallback passive->active */
    Ip_u16 pportbase;                   /* Reject peer ports <= pportbase */
    Ip_u16 lportbase;                   /* Use local ports from lportbase+1 */
    void *data;                         /* User data */
    int (*conout)(struct Ipftpc_attr *attr, const char *buf, int len);
                                        /* Console input */
    void (*ctrlin)(struct Ipftpc_attr *attr, const char *buf, int len);
                                        /* Control input (if debug) */
    void (*ctrlout)(struct Ipftpc_attr *attr, const char *buf, int len);
                                        /* Control output (if debug) */
#ifdef IPFTP_TLS
	Ip_bool	 tlsenble;
	char 	*certfile;
	char 	*keyfile;
	void 	*tls;
	Ip_bool  ccc;
	char	 prot[4];
#endif
}
Ipftpc_attr;

/*
 ****************************************************************************
 * 6                    LOCAL FUNCTIONS
 ****************************************************************************
 */

#ifdef __cplusplus
}
#endif

/*
 ****************************************************************************
 * 10                   PUBLIC FUNCTIONS
 ****************************************************************************
 */

#ifndef IPFTPC_API_C
#include "ipftpc_api_proto.h"
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
