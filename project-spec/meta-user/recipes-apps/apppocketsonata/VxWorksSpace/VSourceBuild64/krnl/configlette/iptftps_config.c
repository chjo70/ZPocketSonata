/*
 * Copyright (c) 2006-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
26feb15,ljg  Fix check return defects
20feb15,ed   More robust handling of config file parse errors
24Nov14,ed   Added TFTPS config file parsing (F2848)
03Aug10,rjq  New file for Networking Configuration VSB restructuring.
03jan07,kch  Updated CVS revision log entry for Jan 03 code drop.
01dec06,kch  Updated CVS revision log entry.
03sep06,kch  Refresh with Sept 08, 2006 code drop
28aug06,kch  Update based on Aug 22, 2006 code drop.
*/


/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * TFTP server configuration
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

/*
 ****************************************************************************
 * 3                    DEFINES
 ****************************************************************************
 */

#define  TFTPS_PORT      "69   " /* TFTP server listening port */
#define  TFTPC_PEER_PORT "69   " /* TFTP port used by client to send packets */

#ifndef CONFIG_FILE_LOGMSG
#define CONFIG_FILE_LOGMSG "Error processing configutation file %s. Errno=%d\n"
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

IP_PUBLIC Ip_err iptftps_configure(void);


/*
 ****************************************************************************
 * 7                    DATA
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         SYSTEM VARIABLES
 *===========================================================================
 */

/*
 *===========================================================================
 *                         iptftp_conf_sysvar
 *===========================================================================
 * TFTP Configuration Variables. Both client and server.
 */
IP_CONST Ipcom_sysvar iptftp_conf_sysvar[] =
{
    /* TFTP server working directory */
    IP_SYSVAR( "iptftp.dir", IPCOM_FILE_ROOT "tftpdir",  TFTPS_DIRS ),

    /* TFTP retransmit timeout in seconds */
    IP_SYSVAR( "iptftp.timeout", "5", TFTPS_RETRANSMIT_TIMEOUT),

    /* TFTP number of retries */
    IP_SYSVAR( "iptftp.retries", "2", TFTPS_RETRIES),

    /* TFTP server listening port */
    IP_SYSVAR( "iptftp.srvPort", TFTPS_PORT, TFTPS_PORT),

    /* TFTP port used by client to send packets */
    IP_SYSVAR( "iptftp.clntSrvPort", TFTPC_PEER_PORT, TFTPC_PEER_PORT),

    /* TFTP server task priority*/
    IP_SYSVAR( "iptftp.priority", "50", TFTPS_TASK_PRIORITY),

    /*TFTP server debugging or not*/
    IP_SYSVAR( "iptftp.debug", "0", TFTPS_DEBUG_ENABLE),

    { IP_NULL, IP_NULL }
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
 *                    iptftps_configure
 *===========================================================================
 * Description: Configure TFTP server
 * Parameters:  none.
 * Returns:     nothing.
 */
IP_PUBLIC Ip_err
iptftps_configure(void)
{

   int ret;

    ret = ipcom_sysvar_setv(iptftp_conf_sysvar, IPCOM_SYSVAR_FLAG_OVERWRITE);
    if (ret != IPCOM_SUCCESS)
        (void)printf("TFTP Server Config returned %d/%x\n", ret, ret);

    /* If there is a config file, process it */
    if (strlen(TFTP_CFGFILE) != 0)
        {
        int rval;
        rval = ipcom_cfgfile_parse(TFTP_CFGFILE, iptftp_conf_sysvar,
               (Ipcom_sysvar_ext *)0 );
    
         if (rval != 0)
            {
            if (_func_logMsg)
                {
                char msg[100];
                (void)snprintf(msg, 100, CONFIG_FILE_LOGMSG, TFTP_CFGFILE, errno);
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
