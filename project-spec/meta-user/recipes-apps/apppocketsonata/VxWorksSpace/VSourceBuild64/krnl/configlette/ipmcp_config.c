/*
 * Copyright (c) 2006-2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
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

#include "ipmcp_config.h"

#include <ipcom_cstyle.h>
#include <ipcom_err.h>
#include <ipcom_shell.h>
#include <ipcom_sysvar.h>

/*
 ****************************************************************************
 * 3                    DEFINES
 ****************************************************************************
 */

/*
 * Default values.
 */
#ifndef MCP_UPSTREAM_IFNAME
#define MCP_UPSTREAM_IFNAME ""
#endif
#ifndef MCP_DOWNSTREAM_IFNAMES
#define MCP_DOWNSTREAM_IFNAMES ""
#endif
#ifndef MCP_ROBUSTNESS_VAR
#define MCP_ROBUSTNESS_VAR 2
#endif
#ifndef MCP_QUERY_INTERVAL
#define MCP_QUERY_INTERVAL 125
#endif
#ifndef MCP_QUERY_RESP_INTERVAL
#define MCP_QUERY_RESP_INTERVAL 10000
#endif
#ifndef MCP_LAST_LISTERNER_QUERY_INTERVAL
#define MCP_LAST_LISTERNER_QUERY_INTERVAL 1000
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

IP_PUBLIC Ip_err ipmcp_configure(void);
IP_PUBLIC int ipmcp_cmd(int argc, char **argv);

/*
 ****************************************************************************
 * 6                    LOCAL PROTOTYPES
 ****************************************************************************
 */

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
IP_STATIC IP_CONST Ipcom_sysvar ipmcp_conf_sysvar[] =
{
    /*
     * Upstream interface, this is the interface where all multicast
     * packets arrive at. The proxy is acting as a multicast HOST on
     * this interface.
     * Ex: "eth0"
     */
    { "ipmcp.UpstreamIf", MCP_UPSTREAM_IFNAME },

    /*
     * Downstream interface, this is the collection of interface to
     * which multicast packets arriving to the upstream inteface will
     * be forwarded to if that multicast group has at least one
     * listener. The proxy is acting as multicast router on these
     * link(s).
     * Ex: "eth1, eth2"
     */
    { "ipmcp.DownstreamIfs", MCP_DOWNSTREAM_IFNAMES },

    /*
     * Multicast router robustness variable
     */
    { "ipmcp.RobustnessVariable", IPCOM_MAKE_STR(MCP_ROBUSTNESS_VAR) },

    /*
     * Multicast router query interval (seconds)
     */
    { "ipmcp.QueryInterval", IPCOM_MAKE_STR(MCP_QUERY_INTERVAL) },

    /*
     * Multicast router query response interval (milliseconds)
     */
    { "ipmcp.QueryResponseInterval", IPCOM_MAKE_STR(MCP_QUERY_RESP_INTERVAL) },

    /*
     * Multicast last listener query interval (milliseconds)
     */
    { "ipmcp.LastListenerQueryInterval", IPCOM_MAKE_STR(MCP_LAST_LISTERNER_QUERY_INTERVAL) },

    /*
     * End marker
     */
	/* the priority of the task */
	{"ipmcp.priority", MCP_TASK_PRIORITY},

    /*enable debugging or not*/
    {"ipmcp.debug", MCP_DEBUG_ENABLE},

    { IP_NULL, IP_NULL  }
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
 *                    ipmcp_configure
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipmcp_configure(void)
{
#if defined(INCLUDE_IPMCAST_PROXY_CMD) || !defined(IP_PORT_VXWORKS)
    Ip_err ret = IPCOM_SUCCESS;

    ret = ipcom_shell_add_cmd("mcastproxy",
                              "mcastproxy [-4|-6] [-r|-i]",
                              "Interpeak multicast proxy",
                              ipmcp_cmd,
                              IPCOM_SHELL_PRIO_SAME,
                              IPCOM_PROC_STACK_DEFAULT);
    if(ret != IPCOM_SUCCESS)
        return ret;
#endif /* INCLUDE_IPMCAST_PROXY_CMD || !IP_PORT_VXWORKS */

    return ipcom_sysvar_setv(ipmcp_conf_sysvar, 0);
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

