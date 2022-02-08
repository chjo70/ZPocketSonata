/*
 * Copyright (c) 2006-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
30apr14,jxy  Add _WRS_CONFIG_USER_MANAGEMENT for V7NET-1 
10mar14,d_z  Remove unnecessary inclusion of loginLibP.h VXW7-2501  
08oct13,qsn  Usage update for WIND00420146 
26jul12,h_x  Fix WIND00362583
03aug10,rjq  New file for Networking Configuration VSB restructuring.
01dec09,rjq  Fix for defect WIND00185613.
02oct07,uol  Remove default ftp/interpeak username/password.
03jan07,kch  Updated CVS revision log entry for Jan 03 code drop.
28dec06,tkf  Remove debug statements.
11dec06,kch  Integrated to VxWorks build infrastructure.
*/

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

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#ifdef IP_PORT_UNIX
#define IPCOM_USE_CLIB_PROTO
#elif defined(IPCOM_USE_CLIB_PROTO)
#undef IPCOM_USE_CLIB_PROTO
#endif
#include <ipcom.h>
#include <ipcom_config.h>
#include <ipcom_os.h>
#include <ipcom_auth.h>

#include "ipftps.h"

#ifdef IP_PORT_VXWORKS
#include <vxWorks.h>
/*#include <private/loginLibP.h>*/
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* typedef to make compiler happy... */
typedef int (*ipftps_cb)(Ipftps_session *session, char *password);

#if defined(IP_WB_BUILD)
	/*
	 * forward declarations for the user-defined ftp server authentication
	 * callback hook to satisfy the compiler.
	 */
#ifdef FTPS_AUTH_CALLBACK_HOOK
int FTPS_AUTH_CALLBACK_HOOK (Ipftps_session *, char *);
#else
#undef FTPS_AUTH_CALLBACK_HOOK
#define FTPS_AUTH_CALLBACK_HOOK IP_NULL
#endif
#endif


/*
 ****************************************************************************
 * 6                    EXTERN PROTOTYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */

int
ipftps_authenticate_default_callback(Ipftps_session *session, char *password);


/*
 ****************************************************************************
 * 8                    DATA
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 9                    LOCAL FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 10                    PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * ipftps_authenticate_default_callback - default ftps callback routine
 *
 * This is an example implementation of the ftp server authentication
 * callback routine. It is called if no ftp server callback routine is
 * assigned to the macro FTPS_AUTH_CALLBACK_HOOK.
 *
 * NOMANUAL
 */
int
ipftps_authenticate_default_callback(Ipftps_session *session, char *password)
{
    /*
    ** This is a simple authentication skeleton,
    ** please modify to suit your purposes.
    */
    if (systemSecurityIsEnabled == FALSE)
    {
        if (ipcom_strcmp(session->username, "anonymous") == 0)
        {
            /* IPCOM_LOG1(INFO, "Anonymous login with password %s", password); */

            /* Access restrictions apply for anonymous users */
            session->readonly = 1;
        }
    }
    else if (ipcom_auth_ctx_login(session->username, password, IP_NULL, IP_NULL,
                                  IP_NULL, IPCOM_AUTH_LOGIN_IF_FTP, 
                                  session->csock.fd) != IPCOM_SUCCESS)
    {
        /* IPCOM_LOG2(WARNING, "Login attempt with user: %s, pw: %s",
                   session->username, password); */
        return 1;
    }

#if 0

    /*
    ** Set security parameters individually for the session if the
    ** default values defined as sysvars aren't appropriate:
    **
    ** readonly:  Write commands disallowed.
    ** proxy:     Allow that data and control connections
    **            use different IP addresses.
    ** lportbase: Use local ports above this value.
    **            Set to 0 to use port 20.
    ** pportbase: Refuse to connect to peer ports <= this value.
    **            Set to 65535 to entirely disable PORT and EPRT commands.
    ** root:      Root directory for the session.
    */

    session->readonly = 1;      /* Readonly mode */
    session->proxy = 0;         /* Disable proxy FTP */
    session->lportbase = 49151; /* Use local ports from lportbase+1 */
    session->pportbase = 1023;  /* Reject peer ports <= pportbase */

    /* Limit access to the filesystem */
    /* Note: using ipcom_strdup is necessary here, internally session->root 
     * points to a buffer that can only hold default/configured content. 
     */
    ipftps_free(session->root);
    if ((session->root = ipcom_strdup("/pub")) == IP_NULL)
    {
        IPCOM_LOG(ERR, "Out of memory") IPCOM_END;
        return 1;
    }
    /* Note: session->cwd points to an internally allocated buffer which you can use directly */
    ipcom_strcpy(session->cwd, "/pub");

#endif

    /* IPCOM_LOG1(INFO, "User %s logged in", session->username); */

    return 0;
}


/*****************************************************************************
 *
 * ipftps_authenticate - ftp server authentication callback routine
 *
 * The FTP sessions may be configured individually by setting session options.
 * This is done after the authentication is complete, and enables clients to
 * be given permissions according to general policies, local databases or
 * even a RADIUS request to a remote host. The options are normally set in
 * the ipftps_authenticate() routine and are accessed through the session
 * pointer.
 *
 * .IP <session>
 * Session descriptor.
 * .IP <password>
 * Password.
 *
 * RETURNS:
 * 0 for successful authentication, 1 otherwise.
 *
 * NOMANUAL
 */
IP_PUBLIC int
ipftps_authenticate(Ipftps_session *session, char *password)
{
    ipftps_cb ftps_cb;

	/*eliminate warning when compiling with gnu*/
#if defined(IP_WB_BUILD) && defined(FTPS_AUTH_CALLBACK_HOOK)
    ftps_cb = FTPS_AUTH_CALLBACK_HOOK;
#else
    ftps_cb = ipftps_authenticate_default_callback;
#endif

    return ftps_cb(session, password);
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
