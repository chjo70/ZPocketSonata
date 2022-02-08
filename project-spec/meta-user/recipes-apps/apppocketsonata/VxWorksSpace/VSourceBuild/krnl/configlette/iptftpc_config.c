/*
 * Copyright (c) 2006-2013 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
26feb15,ljg  Fix check return defects
20feb15,ed   Added code to parse configuration file if it is used
03Aug10,rjq  New file for Networking Configuration VSB restructuring.
03jan07,kch  Updated CVS revision log entry for Jan 03 code drop.
01dec06,kch  Updated CVS revision log entry.
13sep06,kch  Refresh with Sept 08, 2006 code drop
28aug06,kch  Update based on Aug 22, 2006 code drop.
03aug06,kch  Renamed INCLUDE_TFTP_CLIENT_CMD to INCLUDE_IPTFTP_CLIENT_CMD.
*/

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * TFTP client configuration.
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
#include <ipcom_shell.h>
#include <ipcom_cfgfile.h>
#include <logLib.h>

/*
 ****************************************************************************
 * 3                    DEFINES
 ****************************************************************************
 */

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

#if defined(INCLUDE_IPTFTP_CLIENT_CMD) || !defined(IP_WB_BUILD)
IP_EXTERN int iptftp_cmd_tftp(int argc, char **argv);
#endif

IMPORT FUNCPTR _func_logMsg;

/*
 ****************************************************************************
 * 6                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC Ip_err iptftpc_configure(void);


/*
 ****************************************************************************
 * 7                    DATA
 ****************************************************************************
 */

IP_EXTERN IP_CONST Ipcom_sysvar iptftp_conf_sysvar[];


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
 *                    iptftpc_configure
 *===========================================================================
 * Description: Configure TFTP client.
 * Parameters:  none.
 * Returns:     nothing.
 */
IP_PUBLIC Ip_err
iptftpc_configure(void)
{
    Ip_err ret = IPCOM_SUCCESS;

    ret = ipcom_sysvar_setv(iptftp_conf_sysvar, IPCOM_SYSVAR_FLAG_OVERWRITE);
    if (ret != IPCOM_SUCCESS)
        return ret;

   /* If there is a config file, process it. Note, TFTP server and cleint 
    * share sysvars.  So if a configuration file is specified it applies 
    * to both 
    */
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

#if defined(INCLUDE_IPTFTP_CLIENT_CMD) || !defined(IP_WB_BUILD)
    ret = ipcom_shell_add_cmd("tftp", "tftp [-a] <get|put> <host> ...",
                              "Trivial FTP client",
                              iptftp_cmd_tftp,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
#endif

    return ret;
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
