/*
 * Copyright (c) 2006-2013, 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
24may16,h_x  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
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

#ifdef IP_PORT_VXWORKS

#include "ipppp_config.h"
#include <ipcom_type.h>
#include <ipcom_cstyle.h>
#include <ipcom_sysvar.h>
#include <ipcom_err.h>
#include <ipcom_shell.h>

#else

#include <ipcom_type.h>
#include <ipcom_sysvar.h>
#include <ipcom_err.h>
#include <ipcom_shell.h>
#include "ipppp_config.h"

#endif

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

IP_PUBLIC int ipppp_cmd_pppconfig(int argc, char **argv);


/*
 ****************************************************************************
 * 6                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC Ip_err ipppp_configure(void);


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
 *                         ipppp_conf_sysvar
 *===========================================================================
 */
IP_STATIC IP_CONST Ipcom_sysvar ipppp_conf_sysvar[] =
{
    /* Device driver name. */
#ifdef IP_PORT_VXWORKS
#if defined(NUM_TTY) && (NUM_TTY>1)
    { "ipcom.if.ppp0.devname", "/tyCo/1" },  /* COM2 */
#endif
#else
    { "ipcom.if.ppp0.devname", "/dev/ttyS0" }, /* UNIX default */
#endif

    /* Default baudrate. */
     IP_SYSVAR("ipppp.baudrate", "9600", PPP_DEFAULT_BAUDRATE),

    /* PPP runmode
     * Supported modes: start, passive, exit, wincompat
     */
    IP_SYSVAR("ipppp.runmode", "passive,wincompat", PPP_RUNMODE),

    /* PPP flags
     * Supported flags: defaultroute, proxyarp
     */
    IP_SYSVAR("ipppp.flags", "proxyarp", PPP_FLAGS),

    /* Authentication mode.
     * Supported modes: auth, noauth, pap, refuse-pap, chap, refuse-chap
     */
    IP_SYSVAR("ipppp.auth", "chap", PPP_AUTH_MODES),

    /* LCP maximum receive unit */
    IP_SYSVAR("ipppp.lcp.mru", "1500", PPP_LCP_MRU),

    /* LCP maximum transmit unit */
    IP_SYSVAR("ipppp.lcp.mtu", "1500", PPP_LCP_MTU),

    /* Close LCP link when no ncp is opened */
    IP_SYSVAR("ipppp.lcp.autoclose", "yes", PPP_LCP_CLOSE_IF_NO_NCP_OPENED),

    /* Default LCP echo requests interval in seconds (0 to disable) */
    IP_SYSVAR("ipppp.lcp.echo_interval",  "60", PPP_LCP_ECHO_REQ_INTERVAL),

    /* Max LCP EchoReq failures before link termination. */
    IP_SYSVAR("ipppp.lcp.echo_failure", "5", PPP_LCP_ECHO_REQ_FAILURE),

    /* Local IPv4 address. */
    IP_SYSVAR("ipppp.ipcp.addr", "12.0.0.100", PPP_IPCP_IPV4_ADDRESS),

    /* Peer IPv4 address */
    IP_SYSVAR("ipppp.ipcp.dstaddr", "10.1.4.1", PPP_IPCP_PEER_IPV4_ADDRESS),

    /* IPv4 local address. 0.0.0.0 = let peer suggest one. */
    IP_SYSVAR("ipppp.ipcp.pool", "default", PPP_IPCP_PEER_IPV4_POOL_NAME),

    /* IPv4 peer address pool (examples only!). */
#ifdef IP_PORT_VXWORKS
    { "ipppp.ipcp.pool." PPP_IPCP_PEER_IPV4_POOL_NAME, PPP_IPCP_PEER_IPV4_ADDRESS_POOL },
#else
    { "ipppp.ipcp.pool.default", "10.1.3.1-10.1.3.255" },
#endif
    { "ipcom.if.ppp0.ipppp.ipcp.dstaddr", "10.1.4.1" },

#ifndef IP_PORT_VXWORKS
    { "ipcom.users.olli.ipppp.ipcp.dstaddr", "10.1.5.1" },
#endif

    /* PPP 'client' username and password. */
    IP_SYSVAR("ipppp.username", "ppp", PPP_USERNAME),
    IP_SYSVAR("ipppp.password", "kallekula", PPP_PASSWD),

#ifdef IPPPP_USE_RFC1877_SERVER
    /* Primary and secondary DNS and NBNS(WINS) addresses */
    IP_SYSVAR("ipppp.ipcp.primary_dns_address",    "10.1.2.3", PPP_IPCP_PRIMARY_DNS_ADDRESS),
    IP_SYSVAR("ipppp.ipcp.secondary_dns_address",  "195.42.198.5", PPP_IPCP_SECONDARY_DNS_ADDRESS),
    IP_SYSVAR("ipppp.ipcp.primary_nbns_address",   "10.1.2.2", PPP_IPCP_PRIMARY_NBNS_ADDRESS),
    IP_SYSVAR("ipppp.ipcp.secondary_nbns_address", "195.42.198.4", PPP_IPCP_SECONDARY_NBNS_ADDRESS),
#endif

#ifdef IPPPP_USE_PPPOE
    /* Enable(1) /disable(0) PPPoE server */
    IP_SYSVAR("ipppp.pppoe.server", "0", PPPOE_SERVER),

    /* Access Concentrator Name (AC-Name) */
    IP_SYSVAR("ipppp.pppoe.ac_name", "Interpeak PPPoE Server", PPPOE_AC_NAME),

    /* Secret name (for PPPoE cookie). This macro is used in a MD5 checksum
     * calculation to thwart DOS (denial-of-service) attacks. The definition of
     * the string need not match any remote configuration! The value should be
     * changed from its factory default.
     */
    IP_SYSVAR("ipppp.pppoe.secret_name", "puttoanythinghere", PPPOE_SECRET_NAME),

    /* Maximum total number of PPPoE sessions. */
    IP_SYSVAR("ipppp.pppoe.max_sessions", "16", PPPOE_MAX_SESSIONS),

    /* Maximum number of PPPoE sessions per Ethernet interface. */
    IP_SYSVAR("ipppp.pppoe.max_eth_sessions", "8", PPPOE_MAX_ETH_SESSIONS),

#ifndef IP_PORT_VXWORKS
    { "ipcom.if.eth1.ipppp.pppoe.max_eth_sessions", "4" },
#endif

    /* Service name we request/accept. Undefine to accept any service name. */
    IP_SYSVAR("ipppp.pppoe.service_name", "myservice", PPPOE_SERVICE_NAME),

    /* Example of how to lower the MRU/MTU for PPPoE using eth0:
       { "ipcom.if.eth0.ipppp.lcp.mru", "1024" },
       { "ipcom.if.eth0.ipppp.lcp.mtu", "512" },
    */
#endif /* IPPPP_USE_PPPOE */

#ifdef IPPPP_USE_PPPMP
    /* Sysvars for PPP MULTILINK */

    /* Enable(1) / disable(0) PPP multilink protocol */
    IP_SYSVAR("ipppp.mp.enable",      "0", PPPMP_ENABLE),

    /* Set the maximum reconstructed received unit */
    IP_SYSVAR("ipppp.mp.mrru",        "1500", PPPMP_MRRU),

    /* Enable(1) / Disable(0) PPP MP Short Sequence Number usage*/
    IP_SYSVAR("ipppp.mp.ssn",         "0", PPPMP_SSN),
	
    /* Disable(1) / Enable (0) PPP MP PDU Fragmentation */
    IP_SYSVAR("ipppp.mp.frag_disable", "0", PPPMP_FRAG_DISABLE),

#ifdef IPPPP_USE_PPPOE
    IP_SYSVAR("ipppp.pppoe.mp_links", "1", PPPMP_PPPOE_LINKS),
#endif /* IPPPP_USE_PPPOE */
#endif /* IPPPP_USE_PPPMP */

#ifdef IPPPP_USE_VJCOMP
    IP_SYSVAR("ipppp.vjc.enable",     "0", PPPVJC_ENABLE),
#endif /* IPPPP_USE_VJCOMP */

#ifdef IPPPP_USE_PPPL2TP
     IP_SYSVAR("ipppp.l2tp.lnsAddrDefault", "0.0.0.0", PPP_L2TP_LNS_ADDRESS_DEFAULT),
#ifdef IPPPP_USE_PPPL2TP_LNS
     { "ipppp.l2tp.server", "0"},
#endif
#endif
	/* the priority of the task */
	{"ipppp.priority", PPP_TASK_PRIORITY},

    /*enable debugging or not*/
    {"ipppp.debug", PPP_DEBUG_ENABLE},


    { IP_NULL, IP_NULL }
};

#ifdef IP_PORT_VXWORKS
/* Interface specific list configurations */
IP_CONST Ipcom_sysvar_ext ipppp_conf_sysvar_ext[] =
{
#ifdef INCLUDE_IPPPP_INTERFACE_CONFIG
    /*
     * Interface initial baudrate. This parameter is configurable on a
     * per-interface basis in the form of "<ifparam>=<value>", each separated
     * from the other by a semicolon. E.g, "ppp0=38400".
     */
    {"ipcom.if", "ipppp.baudrate", PPP_IF_DEFAULT_BAUDRATE_LIST},

    /*
     * Interface runmode. Specifies one or more runmode options on an
     * interface. Possible runmode options are "start", "passive" and "exit".
     * This parameter is configurable on a per-interface basis in the form
     * of "<ifparam>=<value>", each separated from the other by a semicolon.
     * E.g, "ppp0=start,passive".
     */
    {"ipcom.if", "ipppp.runmode", PPP_IF_RUNMODE_LIST},

    /*
     * Interface PPP flags. Specifies one or more flag behavioural options
     * on an interface. Possible flags options are "defaultroute" and
     * "proxyarp". This parameter is configurable on a per-interface basis
     * in the form of "<ifparam>=<value>", each separated from the other by
     * a semicolon. E.g, "ppp0=proxyarp".
     */
    {"ipcom.if", "ipppp.flags", PPP_IF_FLAGS_LIST},

    /*
     * Configures the required authentication modes. There are currently
     * six authentication options defined - "auth", "noauth", "pap",
     * "refuse-pap", "chap", and "refuse-chap". This parameter is configurable
     * on a per-interface basis in the form of "<ifparam>=<value>", each
     * separated from the other by a semicolon. E.g. "ppp0=chap;ppp1=pap".
     */
    { "ipcom.if", "ipppp.auth", PPP_IF_AUTH_MODES_LIST},

    /*
     * Configures the username for this interface. This parameter is configurable
     * on a per-interface basis in the form of "<ifparam>=<value>", each
     * separated from the other by a semicolon. E.g. "ppp0=PPP1;ppp1=PPP2".
     */
    { "ipcom.if", "ipppp.username", PPP_IF_USERNAME},

    /*
         * Configures the password for this interface. This parameter is configurable
         * on a per-interface basis in the form of "<ifparam>=<value>", each
         * separated from the other by a semicolon. E.g. "ppp0=PAS1;ppp1=PAS2".
         */
    { "ipcom.if", "ipppp.password", PPP_IF_PASSWD},

    /*
     * Interface LCP maximum receive unit. This parameter is configurable
     * on a per-interface basis in the form of "<ifparam>=<value>", each
     * separated from the other by a semicolon. E.g, "ppp0=1500".
     */
    {"ipcom.if", "ipppp.lcp.mru", PPP_IF_LCP_MRU_LIST},

    /*
     * Interface LCP maximum transmit unit. This parameter is configurable
     * on a per-interface basis in the form of "<ifparam>=<value>", each
     * separated from the other by a semicolon. E.g, "ppp0=1500".
     */
    {"ipcom.if", "ipppp.lcp.mtu", PPP_IF_LCP_MTU_LIST},

    /*
     * LCP echo request output interval in seconds. 0 to disable. This
     * parameter is configurable on a per-interface basis in the form of
     * "<ifparam>=<value>", each separated from the other by a semicolon.
     * E.g, "ppp0=60".
     */
    {"ipcom.if", "ipppp.lcp.echo_interval", PPP_IF_LCP_ECHO_REQ_INTERVAL_LIST},

    /*
     * Max echo request failures before link termination. This parameter can
     * be configured on a per-interface basis in the form of
     * "<ifparam>=<value>", each separated from the other by a semicolon.
     * E.g, "ppp0=5"
     */
    {"ipcom.if", "ipppp.lcp.echo_failure", PPP_IF_LCP_ECHO_REQ_FAILURE_LIST},

    /*
     * Local IPv4 address list
     * Specifies the desired local IPv4 address. Setting local IPv4 address
     * to 0 means asking the peer to suggest our IPv4 address. This parameter
     * is configurable on a per-interface basis in the form of
     * "<ifparam>=<value>", each separated from the other by a semicolon.
     * E.g, "ppp0=12.0.0.100".
     */
    {"ipcom.if", "ipppp.ipcp.addr", PPP_IF_IPCP_IPV4_ADDRESS_LIST},

    /*
     * Peer IPv4 address list
     * Suggest peer IPv4 address if asked for. Note that the peer IPv4
     * address will only get suggested to the peer if it ask for it by
     * requesting IP address 0. This parameter is configurable on a
     * per-interface basis in the form of "<ifparam>=<value>", each separated
     * from the other by a semicolon. E.g, "ppp0=10.1.4.1".
     */
    { "ipcom.if", "ipppp.ipcp.dstaddr", PPP_IF_IPCP_PEER_IPV4_ADDRESS_LIST},

    /*
     * Interface IPv4 peer address pool list
     * Configure a IPv4 address pool used for the interface to supply peers
     * with IPv4 addresses when running as a PPP or PPPoE server. This
     * parameter is configurable on a per-interface basis in the form of
     * "<ifparam>=<value>", each separated from the other by a semicolon.
     * E.g., "ppp0=10.1.3.1-10.1.3.255".
     */
    { "ipcom.if", "ipppp.ipcp.pool",
      PPP_IF_IPCP_PEER_IPV4_ADDRESS_POOL_LIST},

    /*
     * Configures the PPP client IPv4 primary DNS address. The configured
     * IPv4 address will be given to the peer (the client) if the peer
     * requests a primary DNS address. This parameter is configurable on
     * a per-interface basis in the form of "<ifparam>=<value>", each
     * separated from the other by a semicolon.
     * E.g. "ppp0=10.1.2.3;ppp1=10.2.2.3".
     */
    { "ipcom.if", "ipppp.ipcp.primary_dns_address",
      PPP_IF_IPCP_PRIMARY_DNS_ADDRESS_LIST },

    /*
     * Configures the PPP client IPv4 secondary DNS address. The configured
     * IPv4 address will be given to the peer (the client) if the peer
     * requests a secondary DNS address. This parameter is configurable on
     * a per-interface basis in the form of "<ifparam>=<value>", each
     * separated from the other by a semicolon.
     * E.g. "ppp0=195.42.198.5;ppp1=195.43.198.5".
     */
    { "ipcom.if", "ipppp.ipcp.secondary_dns_address",
      PPP_IF_IPCP_SECONDARY_DNS_ADDRESS_LIST },

#endif /* INCLUDE_IPPPP_INTERFACE_CONFIG */

#ifdef  INCLUDE_IPPPP_USERS_CONFIG
    /*
     * LCP echo request output interval in seconds. 0 to disable. This
     * parameter is configurable on a per-user basis in the form of
     * "<username>=<value>", each separated from the other by a semicolon.
     * E.g, "user1=60;user2=60".
     */
    {"ipcom.users", "ipppp.lcp.echo_interval",
      PPP_USERS_LCP_ECHO_REQ_INTERVAL_LIST},

    /*
     * user local IPv4 address list
     * Specifies the desired local IPv4 address. Setting local IPv4 address
     * to 0 means asking the peer to suggest our IPv4 address. This parameter
     * is configurable on a per-user basis in the form of
     * "<username>=<value>". Each pair of "<username>=<value>" is semicolon
     * separated. E.g, "user1=12.0.0.100;user2=12.1.0.100".
     */
    {"ipcom.users", "ipppp.ipcp.addr", PPP_USERS_IPCP_IPV4_ADDRESS_LIST},

    /*
     * Users Peer IPv4 address list
     * Suggest peer IPv4 address if asked for. Note that the peer IPv4
     * address will only get suggested to the peer if it ask for it by
     * requesting IP address 0. This parameter is configurable on a
     * per-user basis in the form of "<username>=<value>". Each pair
     * of "<username>=<value>" is semicolon separated.
     * E.g, "user1=10.1.4.1;user2=10.2.4.1"
     */
    { "ipcom.users", "ipppp.ipcp.dstaddr",
      PPP_USERS_IPCP_PEER_IPV4_ADDRESS_LIST},

    /*
     * Users IPv4 peer address pool list
     * Configure a IPv4 address pool used for a user  to supply peers with
     * IPv4 addresses when running as a PPP or PPPoE server. This parameter
     * is configurable on a per-user basis in the form of
     * "<username>=<value>". Each pair of "<username>=<value>" is semicolon
     * separated. E.g., "user1=10.1.3.1-10.1.3.255;user2=10.2.3.1-10.2.3.255".
     */
    { "ipcom.users", "ipppp.ipcp.pool",
      PPP_USERS_IPCP_PEER_IPV4_ADDRESS_POOL_LIST},

    /*
     * Configures the PPP client IPv4 primary DNS address. The configured
     * IPv4 address will be given to the peer (the client) if the peer
     * requests a primary DNS address. This parameter is configurable on
     * a per-user basis in the form of "<ifparam>=<value>", each separated
     * from the other by a semicolon.
     * E.g. "user1=10.1.2.3;user2=10.2.2.3"
     */
    { "ipcom.users", "ipppp.ipcp.primary_dns_address",
      PPP_USERS_IPCP_PRIMARY_DNS_ADDRESS_LIST },

    /*
     * Configures the PPP client IPv4 secondary DNS address. The configured
     * IPv4 address will be given to the peer (the client) if the peer
     * requests a secondary DNS address. This parameter is configurable on
     * a per-user basis in the form of "<ifparam>=<value>", each separated
     * from the other by a semicolon.
     * E.g. "user1=195.42.198.5;user2=195.43.198.5".
     */
    { "ipcom.users", "ipppp.ipcp.secondary_dns_address",
      PPP_USERS_IPCP_SECONDARY_DNS_ADDRESS_LIST },

#endif /* INCLUDE_IPPPP_USERS_CONFIG */

#ifdef INCLUDE_IPPPPOE
    /*
     * Maximum number of PPPoE sessions per Ethernet interface. Note that the
     * interface name used is the Ethernet interface name and not the pppoe
     * interface name. This parameter is configurable on a per-interface basis
     * in the form of "<ifparam>=<value>", each separated from the other by
     * a semicolon. E.g. "eth0=8;eth1=8".
     */
    { "ipcom.if", "ipppp.pppoe.max_eth_sessions",
      PPPOE_IF_MAX_ETH_SESSIONS_LIST},

    /*
     * Service name to accept. Do not set the service name to accept any
     * service name. This parameter is configurable on a per-interface basis
     * in the form of "<ifparam>=<value>", each separated from the other by
     * a semicolon. E.g. "ppp0=myservicename1;ppp1=myservicename2".
     */
    { "ipcom.if", "ipppp.pppoe.service_name", PPPOE_IF_SERVICE_NAME_LIST},
#endif /* INCLUDE_IPPPPOE */

    { IP_NULL, IP_NULL, IP_NULL }
};
#endif /* IP_PORT_VXWORKS */

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
 *                    ipppp_configure
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipppp_configure(void)
{
    /* Set IPPPP system variables. */
    
    (void)ipcom_sysvar_setv(ipppp_conf_sysvar, 0);

#ifndef IP_PORT_OSE5

#ifdef IP_PORT_VXWORKS
    /* now configure the interface-specific sysvars */
    (void)ipcom_sysvar_ext_setv(ipppp_conf_sysvar_ext, 0);
#endif

    (void)ipcom_shell_add_cmd("pppconfig", "pppconfig <ifname> [options]", "ppp config",
                              ipppp_cmd_pppconfig,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_SMALL);
#endif

    return IPCOM_SUCCESS;
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */