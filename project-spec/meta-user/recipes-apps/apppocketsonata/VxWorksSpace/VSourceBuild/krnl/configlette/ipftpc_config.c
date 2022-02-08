/*
 * Copyright (c) 2006-2013,2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06jun16,rjq  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
03Aug10,rjq  New file for Networking Configuration VSB restructuring.
03jan07,kch  Updated CVS revision log entry for Jan 03 code drop.
01dec06,kch  Updated CVS revision log entry.
13sep06,kch  Refresh with Sept 08, 2006 code drop
28aug06,kch  Update based on Aug 22, 2006 code drop.
03aug06,kch  Renamed INCLUDE_FTP_CMD to INCLUDE_IPFTP_CMD.
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
#include <ipcom_shell.h>


/*
 ****************************************************************************
 * 3                    DEFINES
 ****************************************************************************
 */

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
#if defined(INCLUDE_IPFTP_CMD) || !defined(IP_WB_BUILD)
IP_EXTERN int ipftpc_cmd_main(int argc, char *argv[]);
#endif


/*
 ****************************************************************************
 * 6                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC Ip_err ipftpc_configure(void);


/*
 ****************************************************************************
 * 7                    DATA
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         ipftpc_conf_sysvar
 *===========================================================================
 * FTP Client Configuration Variables
 */

IP_CONST Ipcom_sysvar ipftpc_conf_sysvar[] =
{
    /* The FTP client src IPvX address */
    IP_SYSVAR("ipftpc.bindaddress", IP_NULL, FTPC_BIND_ADDRESS),

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
 *                    ipftpc_configure
 *===========================================================================
 * Description: Configure FTP client.
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipftpc_configure(void)
{
    Ip_err ret = IPCOM_SUCCESS;

	(void)ipcom_sysvar_setv(ipftpc_conf_sysvar, 0);

#if defined(INCLUDE_IPFTP_CMD) || !defined(IP_WB_BUILD)
    ret = ipcom_shell_add_cmd("ftp", "ftp [options] [host]", "FTP client",
                              ipftpc_cmd_main,
                              IPCOM_SHELL_PRIO_SAME,
                              IPCOM_PROC_STACK_DEFAULT);
#endif

    return ret;
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
