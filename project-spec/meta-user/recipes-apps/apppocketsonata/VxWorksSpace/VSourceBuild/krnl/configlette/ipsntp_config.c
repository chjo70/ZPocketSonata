/*
 * Copyright (c) 2006-2007, 2010, 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
25may16,rjq  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
03Aug10,rjq  Networking Configuration VSB restructuring.
03jan07,kch  Added precision and mcast.ttl sysvars for sntp server.
01dec06,kch  Added additional configuration parameters.
13sep06,kch  Refresh with Sept 08, 2006 code drop
28aug06,kch  Update based on Aug 22, 2006 code drop.
11aug06,kch  Updated sntp configuration parameters.
03aug06,kch  Renamed INCLUDE_SNTP_CMD to INCLUDE_IPSNTP_CMD.
*/

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * SNTP configuration
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
 
#include "ipcom_config.h"
#include "ipcom_cstyle.h"
#include "ipcom_err.h"
#include "ipcom_sysvar.h"
#include "ipcom_shell.h"
#include "ipcom_os.h"
#include "ipsntp_config.h"
#include "ipsntp.h"


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
#if defined(INCLUDE_IPSNTP_CMD) || !defined(IP_WB_BUILD)
IP_EXTERN int ipsntp_cmd_sntp(int argc, char **argv);
#endif

/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC Ip_err ipsntp_configure(void);


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
IP_STATIC IP_CONST Ipcom_sysvar ipsntp_conf_sysvar[] =
{
#if defined(IP_WB_BUILD)
    /* SNTP daemon mode: "client" or "server" */
#if defined(INCLUDE_IPSNTPC)
    { "ipsntp.daemon.mode", "client" },
#elif defined(INCLUDE_IPSNTPS)
    { "ipsntp.daemon.mode", "server" },
#endif

    /* SNTP server's listening port and SNTP client's destination port */
    { "ipsntp.udp.port", SNTP_LISTENING_PORT},

    /*IPv4 source address*/
    { "ipsntp.bind.addr", SNTP_BIND_IPV4_ADDR},

    /*IPv6 source address*/
    { "ipsntp.bind.addr6", SNTP_BIND_IPV6_ADDR},

    /* the priority of the task*/
    { "ipsntp.priority", SNTP_TASK_PRIORITY},

    /*enable debugging or not */
    { "ipsntp.debug", SNTP_DEBUG_ENABLE},

#ifdef INCLUDE_IPSNTPS
    /* SNTP server leap second filename */
    { "ipsntp.server.leapsecond_filename", SNTPS_LEAP_SECOND_FILENAME},

    /* SNTP server stratum */
    { "ipsntp.server.stratum", SNTPS_STRATUM},

    /* SNTP server precision */
    { "ipsntp.server.precision", SNTPS_PRECISION},

    /* SNTP multicast mode send interval (0 = unicast mode only) */
    { "ipsntp.server.mcast.interval", SNTPS_MULTICAST_INTERVAL},

    /* SNTP multicast mode TTL */
    { "ipsntp.server.mcast.ttl", SNTPS_MULTICAST_TTL},

#ifdef INCLUDE_IPCOM_USE_INET
    /* SNTP multicast mode IPv4 destination address */
    { "ipsntp.server.mcast.addr",  SNTPS_IPV4_MULTICAST_ADDR},
#endif
#ifdef INCLUDE_IPCOM_USE_INET6
    /* SNTP multicast mode IPv6 destination address */
    { "ipsntp.server.mcast.addr6", SNTPS_IPV6_MULTICAST_ADDR },
#endif
#endif /* INCLUDE_IPSNTPS */

#ifdef INCLUDE_IPSNTPC
    /* SNTP unicast client mode poll interval (0 = multicast mode only )*/
    { "ipsntp.client.poll.interval",  SNTPC_POLL_INTERVAL},

    /* Number of retransmissions */
    { "ipsntp.client.poll.count",  SNTPC_POLL_COUNT},

    /* Seconds between retransmissions */
    { "ipsntp.client.poll.timeout", SNTPC_POLL_TIMEOUT},

#ifdef INCLUDE_IPCOM_USE_INET
    /* Primary server IPv4 address */
    { "ipsntp.client.primary.addr",  SNTPC_PRIMARY_IPV4_ADDR},

    /* Backup server IPv4 address */
    { "ipsntp.client.backup.addr",  SNTPC_BACKUP_IPV4_ADDR},

    /* SNTP multicast client mode interface */
    { "ipsntp.client.multi.if", SNTPC_MULTICAST_MODE_IF},

    /* SNTP multicast client mode multicast group */
    { "ipsntp.client.multi.addr", SNTPC_MULTICAST_GROUP_ADDR},
#endif
#ifdef INCLUDE_IPCOM_USE_INET6
    /* Primary server IPv6 address */
    { "ipsntp.client.primary.addr6", SNTPC_PRIMARY_IPV6_ADDR },

    /* Backup server IPv6 address */
    { "ipsntp.client.backup.addr6",  SNTPC_BACKUP_IPV6_ADDR},

    /* SNTP multicast client mode IPv6 interface */
    { "ipsntp.client.multi.if6",   SNTPC_MULTICAST_MODE_IPV6_IF },

    /* SNTP multicast client mode IPv6 multicast group */
    { "ipsntp.client.multi.addr6", SNTPC_MULTICAST_GROUP_IPV6_ADDR},
#endif
#endif /* INCLUDE_IPSNTPC */

#else
    /* SNTP daemon mode: "client" or "server" */
    { "ipsntp.daemon.mode",             "client" },

    /* SNTP server's listening port and SNTP client's destination port */
    { "ipsntp.udp.port",                "123" },

    /* SNTP server leap second filename */
    { "ipsntp.server.leapsecond_filename", ""},

    /* SNTP server stratum */
    { "ipsntp.server.stratum",          "9" },
    /* SNTP server precision */
    { "ipsntp.server.precision",         "-6" },
    /* SNTP multicast mode send interval (0 = unicast mode only) */
    { "ipsntp.server.mcast.interval",   "1024" },
    /* SNTP multicast mode TTL */
    { "ipsntp.server.mcast.ttl",         "1" },
    /* SNTP multicast mode IPv4 destination address */
#ifdef IPCOM_USE_INET
    { "ipsntp.server.mcast.addr",       "224.0.1.1%eth0" },
#endif
#ifdef IPCOM_USE_INET6
    /* SNTP multicast mode IPv6 destination address */
    { "ipsntp.server.mcast.addr6",      "ff05::101%eth0" },
#endif

    /* SNTP unicast client mode poll interval (0 = multicast mode) */
    { "ipsntp.client.poll.interval",    "1024" },
    /* Number of retransmissions */
    { "ipsntp.client.poll.count",       "3" },
    /* Seconds between retransmissions */
    { "ipsntp.client.poll.timeout",     "2" },
#ifdef IPCOM_USE_INET
    /* Primary server IPv4 address */
    { "ipsntp.client.primary.addr",     "10.1.2.90" },
    /* Backup server IPv4 address */
    { "ipsntp.client.backup.addr",      "10.1.2.40" },
    /* SNTP multicast client mode interface */
    { "ipsntp.client.multi.if",         "eth0" },
    /* SNTP multicast client mode multicast group */
    { "ipsntp.client.multi.addr",       "224.0.1.1" },
#endif
#ifdef IPCOM_USE_INET6
    /* Primary server IPv6 address */
    { "ipsntp.client.primary.addr6",    "2001::90" },
    /* Backup server IPv6 address */
    { "ipsntp.client.backup.addr6",     "2001::28" },
    /* SNTP multicast client mode IPv6 interface */
    { "ipsntp.client.multi.if6",        "eth0" },
    /* SNTP multicast client mode IPv6 multicast group */
    { "ipsntp.client.multi.addr6",      "ff05::101" },
#endif
#endif
    { IP_NULL, IP_NULL }
};


/*
 ****************************************************************************
 * 9                    PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipsntp_configure
 *===========================================================================
 * Description: SNTP configure routine.
 * Parameters:  none.
 * Returns:     IPCOM_SUCCESS = ok
 *              IPCOM_ERR_XXX = error code.
 */
IP_PUBLIC Ip_err
ipsntp_configure(void)
{
#if defined(INCLUDE_IPSNTP_CMD) || !defined(IP_WB_BUILD)
    Ip_err ret;

    ret = ipcom_shell_add_cmd("sntp", "sntp [ options | <modifier..>",
                              "(S)NTP tool",
                              (Ipcom_shell_cmd_type)ipsntp_cmd_sntp,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_SMALL);
    if(ret != IPCOM_SUCCESS)
        return ret;
#endif

	/* Initialize IPSNTP system variables. */
    return ipcom_sysvar_setv(ipsntp_conf_sysvar, 0);
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
