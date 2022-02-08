/*
 * Copyright (c) 2006-2010, 2014-2017  Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17may17,rjq  Add new VIP config parameter FTPS_DATABUF_SIZE. (V7NET-1346)
12oct16,rjq  Support to set priority of FTP session task. (V7NET-1113)
06jun16,rjq  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
22oct15,ljl  Get FTPS TLS private key from secure key db, V7NET-496
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
26feb15,ljg  Fix check return defects
20feb15,ed   More robust handling of config file parse errors.
19Nov14,ed   Added FTPS config file parsing (F2848)
03Aug10,rjq  New file for Networking Configuration VSB restructuring.
19dec09,ggz  Added ipftps data socket linger time to sysvar.Defect WIND00127796.
08dec08,ggz  Added FTPS_SOCKET_BACKLOG parameter for FTP control socket
27feb07,kch  ipftps.versionstr should not be made configurable 
             (WIND00089286).
03jan07,kch  Updated CVS revision log entry for Jan 03 code drop.
01dec06,kch  Updated CVS revision log entry.
13sep06,kch  Refresh with Sept 08, 2006 code drop
28aug06,kch  Update based on Aug 22, 2006 code drop.
*/

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_type.h>
#include <ipcom_cstyle.h>
#include <ipcom_err.h>
#include <ipcom_sysvar.h>
#include <ipcom_cfgfile.h>
#include <logLib.h>
#include <ipftps_config.h>

/*
 ****************************************************************************
 * 3                    DEFINES
 ****************************************************************************
 */

#ifndef CONFIG_FILE_LOGMSG
#define CONFIG_FILE_LOGMSG "Error processing configutation file %s. Errno=%d\n"
#endif

#ifndef IPCOM_IPFTPS_ROOT
#define IPCOM_IPFTPS_ROOT IPCOM_FILE_ROOT
#endif

#ifndef FTPS_DATA_SOCKET_LINGER
#define FTPS_DATA_SOCKET_LINGER   "10"  /* Data socket linger time */
#endif

#ifndef FTPS_DATABUF_SIZE
#define FTPS_DATABUF_SIZE   "4096"  /* Data transfer buffer size */
#endif

#ifdef IPFTP_TLS

#ifndef FTPS_TLS
#define FTPS_TLS    "0"
#endif

#ifndef ENABLE_ADVANCE_FTPS_KEY_PRIVACY
#define ENABLE_ADVANCE_FTPS_KEY_PRIVACY    "0"
#endif

#ifndef FTPS_TLS_KEY_FILE
#define FTPS_TLS_KEY_FILE   ""
#endif

#ifndef FTPS_TLS_KEY_ID
#define FTPS_TLS_KEY_ID   ""
#endif


#ifndef FTPS_TLS_CERT_FILE
#define FTPS_TLS_CERT_FILE  ""
#endif

#ifndef FTPS_TLS_SECRECT_KEY
#define FTPS_TLS_SECRECT_KEY  ""
#endif

#endif


/*
 ****************************************************************************
 * 4                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    EXTERN PROTOTYPES
 ****************************************************************************
 */

IMPORT FUNCPTR _func_logMsg;

/*
 ****************************************************************************
 * 6                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC Ip_err ipftps_configure(void);


/*
 ****************************************************************************
 * 7                    DATA
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         ipftps_conf_sysvar
 *===========================================================================
 * FTP Server Configuration Variables
 */

IP_CONST Ipcom_sysvar ipftps_conf_sysvar[] =
{
    /* Defaults for new sessions */

    /* Auth attempts before disconnect */
    IP_SYSVAR("ipftps.authentications", "3", FTPS_AUTH_ATTEMPTS),
    
    /* Time to sleep after auth fail */
    IP_SYSVAR("ipftps.authsleep",  "5", FTPS_SLEEP_TIME),

    /* Use local ports from lportbase+1 */
    IP_SYSVAR("ipftps.lportbase", "49151", FTPS_LOCAL_PORT_BASE),

    /* Reject peer ports <= pportbase */
    IP_SYSVAR("ipftps.pportbase",  "1023",  FTPS_PEER_PORT_BASE),
    IP_SYSVAR("ipftps.proxy",  "0",  FTPS_ENABLE_PROXY),    /* Disable proxy FTP */
    IP_SYSVAR("ipftps.readonly",  "0",  FTPS_MODE),      /* Read/write mode */
    IP_SYSVAR("ipftps.root",  "/",     FTPS_ROOT_DIR),      /* Directory root */
    IP_SYSVAR("ipftps.dir",  IPCOM_IPFTPS_ROOT,   FTPS_INITIAL_DIR), /* Initial directory */

    /* General defaults */
    /* Max no of simultaneous sessions */
    IP_SYSVAR("ipftps.max_sessions", "8", FTPS_MAX_SESSIONS),
    IP_SYSVAR("ipftps.port_number",  "21",  FTPS_PORT_NUM),     /* Server port number */
    IP_SYSVAR("ipftps.receive_timeout", "30", FTPS_RECV_TIMEOUT), /* Data receive timeout */
    IP_SYSVAR("ipftps.send_timeout", "30",  FTPS_SEND_TIMEOUT),     /* Data send timeout */
    
    /* Socket backlog queue number set by listen */
    IP_SYSVAR("ipftps.socket_backlog", IP_NULL,   FTPS_SOCKET_BACKLOG),

    /* Data socket linger time */
    IP_SYSVAR("ipftps.dsock_linger", IP_NULL, FTPS_DATA_SOCKET_LINGER),

    /* Data transfer buffer size */
    IP_SYSVAR("ipftps.databuf_size", "4096", FTPS_DATABUF_SIZE),

    /* User inactivity timeout */
    IP_SYSVAR("ipftps.session_timeout", "300", FTPS_INACTIVITY_TIMEOUT),
    IP_SYSVAR("ipftps.system",  "UNIX",     FTPS_SYS_TYPE),   /* Reported system type */
    IP_SYSVAR("ipftps.versionstr",  "6.8",   "6.8"),  /* Reported version */
#ifdef IPFTP_TLS
    IP_SYSVAR("ipftps.tls.enable","0",FTPS_TLS),
#ifdef IPFTPS_USE_PRIVACY
    IP_SYSVAR("ipftps.tls.private.enable","0",ENABLE_ADVANCE_FTPS_KEY_PRIVACY),
    IP_SYSVAR("ipftps.tls.key_id",IP_NULL,FTPS_TLS_KEY_ID),
#endif
    IP_SYSVAR("ipftps.tls.secret.key",IP_NULL,FTPS_TLS_SECRECT_KEY),
    IP_SYSVAR("ipftps.tls.key_file",IP_NULL,FTPS_TLS_KEY_FILE),
    IP_SYSVAR("ipftps.tls.cert_file",IP_NULL,FTPS_TLS_CERT_FILE),
#endif
    IP_SYSVAR("ipftps.priority", "50", FTPS_TASK_PRIORITY),
    IP_SYSVAR("ipftps.session_priority", "50", FTPS_SESSION_TASK_PRIORITY),

    IP_SYSVAR("ipftps.debug", "0", FTPS_DEBUG_ENABLE),
    {IP_NULL, IP_NULL}
};


/*
 ****************************************************************************
 * 8                    STATIC FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 9                   GLOBAL FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 10                   PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipftps_configure
 *===========================================================================
 * Description: Configure FTP server.
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipftps_configure(void)
{
    /* Set the FTPS sysvars based on CDF parameters */
    (void)ipcom_sysvar_setv(ipftps_conf_sysvar, 0);

    /* If there is a config file, process it */
    if (strlen(FTPS_CFGFILE) != 0)
        {
        int rval;
        rval = ipcom_cfgfile_parse(FTPS_CFGFILE, ipftps_conf_sysvar,
               (Ipcom_sysvar_ext *)0 );
        if (rval != 0)
            {
            if (_func_logMsg)
                {
                char msg[100];
                (void)snprintf(msg, 100, CONFIG_FILE_LOGMSG, FTPS_CFGFILE, errno);
                _func_logMsg(msg, 0,0,0,0,0,0);
                }
            }
           return(rval);
        }

    return IPCOM_SUCCESS;
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
