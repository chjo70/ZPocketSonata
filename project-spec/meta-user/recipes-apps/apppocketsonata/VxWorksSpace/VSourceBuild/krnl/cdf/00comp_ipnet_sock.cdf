/* 00comp_ipnet_sock.cdf - IPNet Socket configuration file */

/*
 * Copyright (c) 2006-2008, 2010, 2012, 2014, 2016 Wind River Systems, Inc.
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
23aug16,kjn  Changed some default values to pass Achilles by default
             (V7NET-1096)
12mar16,wfl  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
15jan14,dlk  Added IPNET_ROUTE_NEIGH_STALE_CORRECT.
09aug12,rjq  move IPNET_MAX_SOCK from VIP to VSB config for WIND00363851.
15sep10,xhs  support IPLITE
05mar08,kjn  LINK_SYMS for netlink was changed from
                 ipnet_netlink_rtm_dumpaddr to ipnet_sock_netlink_register
                 since the former symbol has been removed.
08jan07,kch  Fixed INCLUDE_IPNET_SOCKET dependencies.
22sep06,tkf  Correct module name.
22may06,kch  created.
*/

Component INCLUDE_IPNET_SOCKET {
    NAME            Socket support
    SYNOPSIS        IPNET socket support
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    REQUIRES        INCLUDE_IPCOM INCLUDE_IPLITE
    MODULES         iplite_sock.o
#else
    REQUIRES        INCLUDE_IPCOM INCLUDE_IPNET
    MODULES         ipnet_sock.o
#endif
    CFG_PARAMS      IPNET_SOCK_ANON_PORT_MIN \
                    IPNET_SOCK_ANON_PORT_MAX IPNET_SOCK_DEFAULT_SEND_BUFSIZE \
                    IPNET_SOCK_DEFAULT_RECV_BUFSIZE IPNET_SOCK_ADDR_NOTIFY \
                    IPNET_SOCK_ASSIGN_RANDOM \
                    IPNET_ROUTE_MAX_CLONE_COUNT \
                    IPNET_ROUTE_NEIGH_STALE_CORRECT
}

Component INCLUDE_IPNET_USE_ROUTESOCK {
    NAME            Routing socket support
    SYNOPSIS        Routing socket support
    MODULES         ipnet_routesock.o
    LINK_SYMS       ipnet_sock_route_register
    REQUIRES        INCLUDE_IPNET_USE_SOCK_COMPAT INCLUDE_IPNET_SOCKET
}

Component INCLUDE_IPNET_USE_SOCK_COMPAT {
    NAME            Socket backend
    SYNOPSIS        Socket backend
    MODULES         ipcom_windnet_compat.o
    REQUIRES        INCLUDE_SOCKLIB INCLUDE_IPNET_SOCKET
}

Component INCLUDE_IPNET_USE_NETLINKSOCK {
    NAME            Netlink socket
    SYNOPSIS        Netlink socket
    MODULES         ipnet_netlink.o
    LINK_SYMS       ipnet_sock_netlink_register
}

/******************** Configuration Parameters *****************************/
/* INCLUDE_IPNET_SOCKET configuration parameters */
Parameter IPNET_SOCK_ANON_PORT_MIN {
    NAME        AnonPortMin
    SYNOPSIS    Defines the lowest port number used as an ephemeral port \
                number.
    TYPE        char *
    DEFAULT     "49152"
}

Parameter IPNET_SOCK_ANON_PORT_MAX {
    NAME        AnonPortMax
    SYNOPSIS    Defines the highest port number used as an ephemeral port \
                number.
    TYPE        char *
    DEFAULT     "65535"
}

Parameter IPNET_SOCK_DEFAULT_SEND_BUFSIZE {
    NAME        Default socket send buffer size
    SYNOPSIS    The default size of the socket send buffer. \
                The value must be greater than 2000.
    TYPE        char *
    DEFAULT     "100000"
}

Parameter IPNET_SOCK_DEFAULT_RECV_BUFSIZE {
    NAME        Default socket receive buffer size
    SYNOPSIS    The default size of the socket receive buffer. \
                The value must be greater than 2000.
    TYPE        char *
    DEFAULT     "60000"
}

Parameter IPNET_SOCK_ADDR_NOTIFY {
    NAME        Address Notify
    SYNOPSIS    Set to >0 to get notification on sockets bound to an \
                address that has just been removed
    TYPE        char *
    DEFAULT     "1"
}

Parameter IPNET_ROUTE_MAX_CLONE_COUNT {
    NAME        Maximal clone count
    SYNOPSIS    Defines the maximum number of cloned route entries \
                that might be present at any time. Most common usage \
                of cloned routes are ARP and NDP entries.
    TYPE        char *
    DEFAULT     "256"
}

Parameter IPNET_ROUTE_NEIGH_STALE_CORRECT {
    NAME        More-correct but more-expensive handling of STALE state
    SYNOPSIS    Ensures that even when sent to only by non-primary stack \
                instances, a neighbor in STALE state globally transitions \
                to DELAY state when any stack instance sends to the \
                neighbor. This correct behavior can prevent brief \
                interruption in traffic to the neighbor in some cases, \
                but is not absolutely necessary and does impose additional \
                CPU load on the primary stack instance. Use "yes" or "no".
    TYPE        char *
    DEFAULT     "yes"
}

Parameter IPNET_SOCK_ASSIGN_RANDOM {
    NAME        Pseudo-random assignment of new sockets to stack instances
    SYNOPSIS    Use "yes" or "no".  When this parameter is "no", new sockets \
                are always assigned to the primary network stack instance \
                (tNet0).  When this parameter is "yes", each new sockets is \
                assigned pseudo-randomly to one of the network stack \
                instances.
    TYPE        char *
    DEFAULT     "no"
}
