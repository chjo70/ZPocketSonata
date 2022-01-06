/*
 * Copyright (c) 2006-2013, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06apr17,ljl  Add security events on login and logout (F8189)
17may16,ljl  added definition of security event IDs (F3805)
*/

#ifndef IPFTPS_H
#define IPFTPS_H

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

#include "ipftps_config.h"
#include "ipcom_config.h"
#include "ipcom_list.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */
/*security event ID*/
#define SEC_EVENT_FTP_LOGIN_FAILED (M_ftpLib | 1)
#define SEC_EVENT_FTP_LOGIN_OK     (M_ftpLib | 2)
#define SEC_EVENT_FTP_LOGOUT       (M_ftpLib | 3)

/*
 *===========================================================================
 *                         release
 *===========================================================================
 */

#define IPFTPS_RELEASE 060004

/* Transport protocol for FTPS */
#ifdef IPFTPS_USE_SCTP
#define IPFTPS_PROTO IP_IPPROTO_SCTP
#else
#define IPFTPS_PROTO 0
#endif

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* dummy, see below for real struct */
struct Ipftps_session;

/* Socket control block */
typedef struct
{
    union Ip_sockaddr_union paddr;      /* Peer address */
    union Ip_sockaddr_union laddr;      /* Local address */
    Ip_fd fd;                           /* File descriptor */
}
Ipftps_sockcb;

/* Command descriptor */
typedef struct
{
    const char *name;                   /* Command name */
    void (*func)(struct Ipftps_session *, int argc, char *argv[]);
                                        /* Command handler */
    Ip_u8 min;                          /* Min no of arguments */
    Ip_u8 max;                          /* Max no of arguments */
    Ip_u8 argtype;                      /* Command argument. 1 if string */        
    Ip_bool login;                      /* Requires login */
    const char *help;                   /* Help text */
}
Ipftps_cmd;

/* Session descriptor */
typedef struct Ipftps_session
{
    Ipcom_list head;                    /* List header */
    Ipftps_sockcb csock;                /* Control socket */
    Ipftps_sockcb dsock;                /* Data socket */
    const Ipftps_cmd *last;             /* Last command */
    char *username;                     /* Username */
    char *rnfr;                         /* Rename from this name */
    char *root;                         /* Directory root */
    char *cwd;                          /* Current working directory */
    Ip_u32 trnow;                       /* Transferred bytes*/
    Ip_u32 trtotal;                     /* Total bytes */
    Ip_u16 pportbase;                   /* Reject peer ports <= pportbase */
    Ip_u16 lportbase;                   /* Use local ports from lportbase+1 */
    Ip_bool occupied;                   /* Session has a handler */
    Ip_bool login;                      /* Login performed */
    Ip_bool cwdroot;                    /* Use root as next CWD */
    Ip_bool epsvonly;                   /* Use only extended passive mode */
    Ip_bool passive;                    /* Passive mode */
    Ip_bool binary;                     /* Binary mode */
    Ip_bool readonly;                   /* Readonly mode */
    Ip_bool proxy;                      /* Enable proxy FTP */
    int authentications;                /* Number of authentications */
    int cmdlen;                         /* Length of current command */
    int cmdbuflen;                      /* Length of all commands */
    char cmdbuf[IPFTPS_CMDBUFSIZE + 1]; /* Command buffer */
    char name[20];                      /* Session name */
#ifdef IPFTP_TLS
	void * tlsopt;
#endif
}
Ipftps_session;


/*
 ****************************************************************************
 * 6                    LOCAL FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 10                   PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *      ipftps_authenticate
 *===========================================================================
 * Description:
 *      Authenticate user.
 *
 * Parameters:
 *      session         Session descriptor.
 *      password        Password.
 *
 * Returns:
 *      0 if successful authentication, 1 otherwise.
 */
IP_PUBLIC int
ipftps_authenticate(Ipftps_session *session, char *password);


/*******************************************************************************
*
* ipftps_get_activesession - Get the current active session number of ftp server
*
* Get the current active session number of ftp server.
*
* Parameters:
* \is
* \ie
*
* RETURNS: The current active session number
*
* ERRNO:
*/
IP_PUBLIC int
ipftps_get_activesession(void);


#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
