/* 02comp_ipnet_mcast.cdf - IPNet Multicast Components configuration file */

/*
 * Copyright (c) 2006, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
28nov06,kch  Removed tunnel dependency from IPv6 multicast routing.
23sep06,kch  Created.
*/

Component INCLUDE_IPNET_USE_MCAST_ROUTING {
    NAME            IPv4 Multicast routing
    SYNOPSIS        IPv4 Multicast routing
    MODULES         ipnet_ip4_mcast.o
    LINK_SYMS       ipnet_ip4_mcast_input
    REQUIRES        INCLUDE_IPCOM_USE_INET
    _CHILDREN       FOLDER_NET_PRIVATE
}

Component INCLUDE_IPNET6_USE_MCAST_ROUTING {
    NAME            IPv6 Multicast routing
    SYNOPSIS        Ipv6 Multicast routing
    MODULES         ipnet_ip6_mcast.o
    LINK_SYMS       ipnet_ip6_mcast_input
    REQUIRES        INCLUDE_IPCOM_USE_INET6
    _CHILDREN       FOLDER_NET_PRIVATE
}

Component INCLUDE_IPMCP {
    NAME            Multicast proxy
    SYNOPSIS        Multicast proxy
    MODULES         ipmcp.o
    CONFIGLETTES    ipmcp_config.c
    CFG_PARAMS      MCP_UPSTREAM_IFNAME MCP_DOWNSTREAM_IFNAMES \
                    MCP_ROBUSTNESS_VAR MCP_QUERY_INTERVAL \
                    MCP_QUERY_RESP_INTERVAL MCP_LAST_LISTERNER_QUERY_INTERVAL \
                    MCP_TASK_PRIORITY MCP_DEBUG_ENABLE
}

Component INCLUDE_IPMCP_USE_IGMP {
    NAME            IPv4 IGMP
    SYNOPSIS        IPv4 Internet Group Management Protocol
    MODULES         ipmcp_igmp.o
    REQUIRES        INCLUDE_IPMCP \
                    INCLUDE_IPNET_USE_MCAST_ROUTING
}

Component INCLUDE_IPMCP_USE_MLD {
    NAME            IPv6 MLD
    SYNOPSIS        IPv6 Multicast Listener Discovery Protocol
    MODULES         ipmcp_mld.o
    REQUIRES        INCLUDE_IPMCP \
                    INCLUDE_IPNET6_USE_MCAST_ROUTING
}

Component INCLUDE_IPMCAST_PROXY_CMD {
    NAME        IPCOM mcastproxy commands
    SYNOPSIS    IPCOM Multicast proxy commands.
    MODULES     ipmcp_cmd.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPMCP
}

/*****************************************************************************/
/* INCLUDE_IPMCP configuration parameters */
Parameter MCP_UPSTREAM_IFNAME {
    NAME        Upstream interface name
    SYNOPSIS    The interface where all multicast packets arrive at. The \
                proxy is acting as a multicast host on this interface, \
                e.g "eth0".
    TYPE        char *
    DEFAULT     NULL
}

Parameter MCP_DOWNSTREAM_IFNAMES {
    NAME        Downstream interface names
    SYNOPSIS    Collection of interface to which multicast packets arriving \
                to the upstream inteface will be forwarded to if that \
                multicast group has at least one listener, e.g. "eth1,eth2"
    TYPE        char *
    DEFAULT     NULL
}

Parameter MCP_ROBUSTNESS_VAR {
    NAME        Multicast router robustness variable
    SYNOPSIS    Multicast router robustness variable. This variable allows \
                tuning for the expected packet loss on a link.
    TYPE        int
    DEFAULT     2
}

Parameter MCP_QUERY_INTERVAL {
    NAME        Multicast router query interval (seconds)
    SYNOPSIS    The interval between MLD general queries sent by multicast \
                proxy in querier.
    TYPE        int
    DEFAULT     125
}

Parameter MCP_QUERY_RESP_INTERVAL {
    NAME        Multicast router query response interval (milliseconds)
    SYNOPSIS    The maximum response delay allowed for a multicast client \
                to answer on a general MLD query.
    TYPE        int
    DEFAULT     10000
}

Parameter MCP_LAST_LISTERNER_QUERY_INTERVAL {
    NAME        Multicast last listener query interval (milliseconds)
    SYNOPSIS    The maximum response delay allowed for a multicast client \
                to answer on a group specific MLD query.
    TYPE        int
    DEFAULT     1000
}
Parameter MCP_TASK_PRIORITY {
    NAME        Task priority
    SYNOPSIS    This parameter sets the task priority of the MCP network service task. Changing the value may have risks.
    TYPE        char *
    DEFAULT     "50"
}


Parameter MCP_DEBUG_ENABLE {
    NAME        Enable debugging
    SYNOPSIS    Set the value to "1" to debug the task.
    TYPE        char *
    DEFAULT     "0"
}
