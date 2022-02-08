/* 01comp_ipcom_wrapper.cdf - backwards compatibility wrapper APIs */

/*
 * Copyright 2006-2008, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16aug16,mca  Change LINK_SYMS in INCLUDE_IPWRAP_IFNAME to if_nameindex
26may16,ghl  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
18jul13,rjq  Detach INCLUDE_PING from INCLUDE_SHELL
15sep10,xhs  support IPLITE
17nov09,rjq  Added INCLUDE_IPWRAP_SNTPSCLOCKSET and
             INCLUDE_IPWRAP_SNTPSNSECTOFRACTION.
16feb09,mca  changed dependency of INCLUDE_IPWRAP_SNTPCTIMEGET to
             INCLUDE_IPSNTPC_API
20nov08,ggz  Added INCLUDE_IPWRAP_IFSHOW.
04jun08,spw  Update ifLib, oldRouteLib REQUIRES, add ifLib_test
01jun08,spw  Added IFLIB, OLDROUTELIB wrapper components
23jan07,kch  Corrected INCLUDE_IPWRAP_SNTPCTIMEGET dependencies.
28nov06,kch  Added INCLUDE_IPWRAP_INETLIB.
27nov06,kch  Corrected INCLUDE_IPWRAP_SNTPCTIMEGET dependency.
25nov06,kch  Added support for INCLUDE_IPWRAP_GETIFADDRS and
             INCLUDE_IPWRAP_SNTPCTIMEGET.
12sep06,kch  Added INCLUDE_IPWRAP_IFNAME.
31aug06,tkf  Added INCLUDE_IPWRAP_ARP.
03aug06,kch  Added INCLUDE_IPWRAP_PING.
02aug06,kch  Added INCLUDE_IPWRAP_PING6.
31jul06,kch  Added INCLUDE_IPWRAP_ROUTECMD and INCLUDE_IPWRAP_NETSTAT.
27jul06,tkf  Added INCLUDE_IPWRAP_GETADDRINFO, INCLUDE_IPWRAP_GETNAMEINFO,
             INCLUDE_IPWRAP_GETSERVBYNAME, INCLUDE_IPWRAP_GETSERVBYPORT.
             Also shortened the component names for INCLUDE_IPWRAP_IPPROTO
             and INCLUDE_IPWRAP_IFCONFIG.
14jun06,tkf  Added INCLUDE_IPWRAP_IFCONFIG.
07jun06,dlk  Written.
*/


Component INCLUDE_IPWRAP_IPPROTO {
    NAME            ipProto wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routines such as ipAttach(), ip6Attach(), ipDetach(), and \
                    ip6Detach().
    REQUIRES        INCLUDE_IPCOM
    MODULES         ipProto.o
    LINK_SYMS       ipAttach
}

Component INCLUDE_IPWRAP_IFCONFIG {
    NAME            ifconfig wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for ifconfig().
    REQUIRES        INCLUDE_IPCOM
    MODULES         ifconfig.o
    LINK_SYMS       ifconfig
}

Component INCLUDE_IPWRAP_IFSHOW {
    NAME            ifShow wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for ifShow().
    REQUIRES        INCLUDE_IPCOM
    MODULES         ifShow.o
    LINK_SYMS       ifShow
}

Component INCLUDE_IPWRAP_ROUTECMD {
    NAME            routec wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for routec().
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    REQUIRES        INCLUDE_IPLITE
#else
    REQUIRES        INCLUDE_IPNET INCLUDE_IPNET_USE_ROUTESOCK
#endif
    MODULES         routeCmd.o
    LINK_SYMS       routec
}

Component INCLUDE_IPWRAP_NETSTAT {
    NAME            netstat wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for netstat().
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    REQUIRES        INCLUDE_IPLITE
#else
    REQUIRES        INCLUDE_IPNET
#endif
    MODULES         netstat.o
    LINK_SYMS       netstat
}

Component INCLUDE_IPWRAP_PING {
    NAME            Ping wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for ping().
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    REQUIRES        INCLUDE_IPLITE INCLUDE_IPCOM_USE_INET
#else
    REQUIRES        INCLUDE_IPNET INCLUDE_IPCOM_USE_INET
#endif
    MODULES         pingLib.o
    LINK_SYMS       ping
}

Component INCLUDE_IPWRAP_PING6 {
    NAME            Ping6 wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for ping6().
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    REQUIRES        INCLUDE_IPLITE INCLUDE_IPCOM_USE_INET6
#else
    REQUIRES        INCLUDE_IPNET INCLUDE_IPCOM_USE_INET6
#endif
    MODULES         ping6Lib.o
    LINK_SYMS       ping6
}

Component INCLUDE_IPWRAP_GETADDRINFO {
    NAME            getaddrinfo wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for getaddrinfo().
    REQUIRES        INCLUDE_IPCOM
    MODULES         getaddrinfo.o
    LINK_SYMS       getaddrinfo
}

Component INCLUDE_IPWRAP_GETNAMEINFO {
    NAME            getnameinfo wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for getnameinfo().
    REQUIRES        INCLUDE_IPCOM
    MODULES         getnameinfo.o
    LINK_SYMS       getnameinfo
}

Component INCLUDE_IPWRAP_GETHOSTBYNAME {
    NAME            gethostbyname wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for gethostbyname().
    REQUIRES        INCLUDE_IPCOM
    MODULES         gethostbyname.o
    LINK_SYMS       gethostbyname
}

Component INCLUDE_IPWRAP_GETHOSTBYADDR {
    NAME            gethostbyaddr wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for gethostbyaddr().
    REQUIRES        INCLUDE_IPCOM
    MODULES         gethostbyaddr.o
    LINK_SYMS       gethostbyaddr
}

Component INCLUDE_IPWRAP_GETSERVBYNAME {
    NAME            getservbyname wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for getservbyname().
    REQUIRES        INCLUDE_IPCOM
    MODULES         getservbyname.o
    LINK_SYMS       getservbyname
}

Component INCLUDE_IPWRAP_GETSERVBYPORT {
    NAME            getservbyport wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for getservbyport().
    REQUIRES        INCLUDE_IPCOM
    MODULES         getservbyport.o
    LINK_SYMS       getservbyport
}

Component INCLUDE_IPWRAP_ARP {
    NAME            Arp utility wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routines for arp utilities such as arpAdd() and arpDelete().
    REQUIRES        INCLUDE_IPARP_CMD INCLUDE_IPNET
    MODULES         arpLib.o
    LINK_SYMS       arpAdd
}

Component INCLUDE_IPWRAP_IFNAME {
    NAME            ifname wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routines for ifname utilities such as if_nameindex() \
                    and if_freenameindex().
    MODULES         ifname.o
    LINK_SYMS       if_nameindex
}

Component INCLUDE_IPWRAP_INETLIB {
    NAME            inetLib wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routines for internet address manipulation routines \
                    such as inet_network() etc.
    REQUIRES        INCLUDE_IPCOM
    MODULES         inetLib.o
    LINK_SYMS       inet_network
}

Component INCLUDE_IPWRAP_GETIFADDRS {
    NAME            getifaddrs wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routines for getifaddrs() and freeifaddrs().
    REQUIRES        INCLUDE_IPCOM
    MODULES         getifaddrs.o
    LINK_SYMS       getifaddrs
}

Component INCLUDE_IPWRAP_SNTPCTIMEGET {
    NAME            sntpcTimeGet wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for sntpcTimeGet().
    REQUIRES        INCLUDE_IPSNTPC_API
    MODULES         sntpcLib.o
    LINK_SYMS       sntpcTimeGet
}

Component INCLUDE_IPWRAP_SNTPSCLOCKSET {
    NAME            sntpsClockSet wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for sntpsClockSet().
    REQUIRES        INCLUDE_IPSNTPS_API \
                    INCLUDE_IPSNTPS
    MODULES         sntpsLib.o
    LINK_SYMS       sntpsClockSet
}

Component INCLUDE_IPWRAP_SNTPSNSECTOFRACTION {
    NAME            sntpsNsecToFraction wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routine for sntpsNsecToFraction().
    REQUIRES        INCLUDE_IPSNTPS_API
    MODULES         sntpsLib.o
    LINK_SYMS       sntpsNsecToFraction
}

Component INCLUDE_IPWRAP_IFLIB {
    NAME            ifLib wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routines for the network interface library routines \
                    such as ifRouteDelete(), ifAddrAdd(), ifFlagSet(), \
                    etc.
    REQUIRES        INCLUDE_IPCOM_USE_INET \
                    INCLUDE_SOCKLIB
    MODULES         ifLib.o
    LINK_SYMS       ifRouteDelete \
                    ifAddrAdd \
                    ifFlagSet
}


Component INCLUDE_IPWRAP_IFLIB_TEST {
    NAME            ifLib test routines
    SYNOPSIS        ifLib test routines
    LINK_SYMS       ifLib_test
    REQUIRES        INCLUDE_IPWRAP_IFLIB
}

Component INCLUDE_IPWRAP_IF6LIB {
    NAME            if6Lib wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routines for network interface library routines \
                    such as if6AddrAdd(), if6AddrGet(), if6FlagSet(), \
                    etc.
    REQUIRES        INCLUDE_IPCOM_USE_INET6 \
                    INCLUDE_SOCKLIB
    MODULES         if6Lib.o
    LINK_SYMS       if6AddrAdd \
                    if6AddrGet \
                    if6FlagSet
}

Component INCLUDE_IPWRAP_IF6LIB_TEST {
    NAME            if6Lib test routines
    SYNOPSIS        if6Lib test routines
    LINK_SYMS       if6Lib_test
    REQUIRES        INCLUDE_IPWRAP_IF6LIB
}

Component INCLUDE_IPWRAP_OLDROUTELIB {
    NAME            oldRouteLib wrapper
    SYNOPSIS        This component provides the backwards compatibility \
                    routines for old route lib compatibility routines \
                    such as mRouteAdd(), routeDelete(), routeNetAdd() \
                    etc.
    REQUIRES        INCLUDE_IPCOM_USE_INET \
                    INCLUDE_SOCKLIB
    MODULES         oldRouteLib.o
    LINK_SYMS       mRouteAdd \
                    routeDelete \
                    routeNetAdd
}
