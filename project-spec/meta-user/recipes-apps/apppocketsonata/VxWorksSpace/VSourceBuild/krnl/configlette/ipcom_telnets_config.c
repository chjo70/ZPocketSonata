/*
 * Copyright (c) 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* modification history
-------------------------
09jul16,rjq  Add telnet idle timeout parameter.  (V7NET-862)
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
26feb15,ljg  Fix check return defects
20feb15,ed   Added a mod history and more robust handling of config 
             file parse errors
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

#include "ipcom_config.h"

/* 
 * We need IPCOM_USE_CLIB_PROTO defined here to ensure proper preprocessing of
 * the subsequently included IPCOM header files.
 */

#define IPCOM_USE_CLIB_PROTO

#include "ipcom_type.h"
#include "ipcom_cstyle.h"
#include "ipcom_err.h"
#include "ipcom_sysvar.h"
#include "ipcom_cfgfile.h"
#include <logLib.h>

/*
 ****************************************************************************
 * 3                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC Ip_err iptelnets_configure(void);

/*
 ****************************************************************************
 *                      DEFINES
 ****************************************************************************
 */

#ifndef CONFIG_FILE_LOGMSG
#define CONFIG_FILE_LOGMSG "Error processing configutation file %s. Errno=%d\n"
#endif

/*
 ****************************************************************************
 *                      EXTERN PROTOTYPES
 ****************************************************************************
 */

IMPORT FUNCPTR _func_logMsg;

/*
 ****************************************************************************
 * 5                    DATA
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         SYSTEM VARIABLES
 *===========================================================================
 */
IP_STATIC IP_CONST Ipcom_sysvar iptelnets_conf_sysvar[] =
{
    /* Telnet port */
#if defined(IPCOM_TELNET_PORT)
    { "ipcom.telnet.port", IPCOM_TELNET_PORT },
#else
    { "ipcom.telnet.port", "2323" },
#endif

#if IPCOM_USE_SHELL == IPCOM_SHELL_IPCOM
    /* Shell greeting. */
    { "ipcom.shell.greeting", "Copyright (c) 2006-2013 Wind River (http://www.windriver.com). All rights reserved.\n\nWelcome to IPCOM SHELL. Type help for a list of commands.\n\n" },

    /* Shell prompt. Supported special characters are:
     *     \p - shell process name
     *     \P - shell process id
     *     \i - the IP address of the target
     *     \w - the current working directory
     *     \W - the basename of the current working directory
     *     \V - ipcom_getenv("VR")
     */
    /*{ "ipcom.shell.prompt", "\\i$\\w> " },*/
    { "ipcom.shell.prompt", "\\i#\\V> " },
#endif /* IPCOM_USE_SHELL == IPCOM_SHELL_IPCOM */

#ifdef IPCOM_USE_AUTH
    /* Require telnet users to authenticate (1 = enabled, 0 = disabled) */
    { "ipcom.telnet.authenticate", "0" },
#endif
#ifdef IPCOM_TELNET_MAX_CLIENTS
    { "ipcom.telnet.max_sessions", IPCOM_TELNET_MAX_CLIENTS },
#endif
#ifdef IPCOM_TELNET_IDLE_TIMEOUT
    { "ipcom.telnet.idle_timeout", IPCOM_TELNET_IDLE_TIMEOUT },
#endif
#ifdef IP_PORT_VXWORKS
    /* 
     * Priority of ipcom_telnetd task, from 1 - 7,
     *  1 - IPCOM_PROC_PRIO_1
     *  2 - IPCOM_PROC_PRIO_2
     *  3 - IPCOM_PROC_PRIO_3
     *  4 - IPCOM_PROC_PRIO_4
     *  5 - IPCOM_PROC_PRIO_5
     *  6 - IPCOM_PROC_PRIO_6
     *  7 - IPCOM_PROC_PRIO_7
     */
    { "ipcom.telnet.priority", IPCOM_TELNET_TASK_PRIORITY},
#endif

    /*enable debugging or not*/
    {"ipcom.telnet.debug",IPCOM_TELNET_DEBUG_ENABLE},


    { IP_NULL, IP_NULL }
};


/*
 ****************************************************************************
 * 6                   FUNCTIONS
 ****************************************************************************
 */


/*
 *===========================================================================
 *                         iptelnets_configure
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
iptelnets_configure(void)
{
    /* Set IPTELNETS system variables. */
    (void)ipcom_sysvar_setv(iptelnets_conf_sysvar, 0);

    /* If there is a config file, process it */
    if (strlen(IPCOM_TELNET_CFGFILE) != 0)
        {
        int rval;
        rval = ipcom_cfgfile_parse(IPCOM_TELNET_CFGFILE, iptelnets_conf_sysvar,
              (Ipcom_sysvar_ext *)0 );

        if (rval != 0)
            {
            if (_func_logMsg)
                {
                char msg[100];
                (void)snprintf(msg, 100, CONFIG_FILE_LOGMSG, IPCOM_TELNET_CFGFILE, 
                         errno);
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

