/*
 * Copyright (c) 2010, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
15jun15,rjq  Upgrade ntp version to 4.2.8p2. (V7NET-498)
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
17sep14,rjq  Support for NTP crypto. (V7NET-430)
06apr10,rjq  written
*/

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * NTP configuration
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
#include "ipntp_config.h"
#include "ipcom_config.h"
#include "ipcom_cstyle.h"
#include "ipcom_err.h"
#include "ipcom_sysvar.h"
#include "ipcom_shell.h"
#include "ipcom_os.h"
#include "ipntp.h"


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

/*
 ****************************************************************************
 * 6                    EXTERN PROTOTYPES
 ****************************************************************************
 */
#if defined(INCLUDE_IPNTP_CMD) || !defined(IP_WB_BUILD)
IP_EXTERN int ipntp_cmd_ntp(int argc, char **argv);
#endif

#ifdef OPENSSL
IP_GLOBAL int ipntp_cmd_ntpkey(int argc, char **argv);
#endif


/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */
IP_PUBLIC Ip_err ipntp_configure(void);

/*
 ****************************************************************************
 * 8                    DATA
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         SYSVAR CONFIGURATION
 *===========================================================================
 */
IP_STATIC IP_CONST Ipcom_sysvar ipntp_conf_sysvar[] =
{
	IP_SYSVAR("ipntp.config.filename", IP_NULL, NTP_CONFIG_FILENAME),
	IP_SYSVAR("ipntp.config.param", "server 10.10.10.1; disable auth", NTP_CONFIG_PARAM),
	IP_SYSVAR("ipntp.init.param", IP_NULL, NTP_INIT_PARAM),

	IP_SYSVAR("ipntp.priority", 50, NTP_TASK_PRIORITY),

	IP_SYSVAR("ipntp.debug", 0, NTP_DEBUG_ENABLE),
	{ IP_NULL, IP_NULL }
};

/*
 ****************************************************************************
 * 9                    PUBLIC FUNCTIONS
 ****************************************************************************
 */


/*
 *===========================================================================
 *                    ipntp_configure
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipntp_configure(void)
{
#if defined(INCLUDE_IPNTP_CMD) || !defined(IP_WB_BUILD)
    Ip_err ret;

    ret = ipcom_shell_add_cmd("ntp", "ntp [ options | <modifier..>",
                              "NTP tool",
                              (Ipcom_shell_cmd_type)ipntp_cmd_ntp,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_SMALL);
    if(ret != IPCOM_SUCCESS)
        return ret;

#ifdef OPENSSL
    ret = ipcom_shell_add_cmd("ntpkey", "ntpkey [ options | <modifier..>",
                              "NTPKEY tool",
                              (Ipcom_shell_cmd_type)ipntp_cmd_ntpkey,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_SMALL);
    if(ret != IPCOM_SUCCESS)
        return ret;
#endif
#endif

    /* Initialize NTP system variables. */
    return ipcom_sysvar_setv(ipntp_conf_sysvar, 0);
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

