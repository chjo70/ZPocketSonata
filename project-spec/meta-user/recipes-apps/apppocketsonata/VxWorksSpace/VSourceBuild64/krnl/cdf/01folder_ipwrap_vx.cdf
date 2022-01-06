/* 01folder_ipwrap.cdf - backwards compatibility wrappers for coreip APIs */
/*
 * Copyright 2006-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
01n,17nov09,rjq  Added INCLUDE_IPWRAP_SNTPSCLOCKSET and
                 INCLUDE_IPWRAP_SNTPSNSECTOFRACTION.
01m,20nov08,ggz  Added INCLUDE_IPWRAP_IFSHOW
01l,01jun08,spw  Added IFLIB, OLDROUTELIB wrappers
01k,27feb07,dlk  Added INCLUDE_IPWRAP_GETHOSTBYNAME, 
                 INCLUDE_IPWRAP_GETHOSTBYADDR.
01j,08jan07,kch  Added FOLDER_IPUTILSLIB and FOLDER_IPLIBC.
01i,28nov06,kch  Added INCLUDE_IPWRAP_INETLIB.
01h,25nov06,kch  Added support for INCLUDE_IPWRAP_GETIFADDRS and 
                 INCLUDE_IPWRAP_SNTPCTIMEGET.
01g,12sep06,kch  Added INCLUDE_IPWRAP_IFNAME.
01f,31aug06,tkf  Added INCLUDE_IPWRAP_ARP.
01e,03aug06,kch  Added INCLUDE_IPWRAP_PING.
01d,02aug06,kch  Added INCLUDE_IPWRAP_PING6.
01c,27jul06,kch  Added INCLUDE_IPWRAP_ROUTECMD and INCLUDE_IPWRAP_NETSTAT.
01b,27jun06,tkf  Added INCLUDE_IPWRAP_GETADDRINFO, INCLUDE_IPWRAP_GETNAMEINFO,
                 INCLUDE_IPWRAP_GETSERVBYNAME, INCLUDE_IPWRAP_GETSERVBYPORT.
                 Also shortened NAME for FOLDER_IPWRAP.
01a,07jun06,dlk  Written.
*/

Folder FOLDER_IPLIBC {
    NAME        libc wrappers
    SYNOPSIS    This folder contains components which provide various APIs \
                available in older versions of the VxWorks networking stack \
                for which close alternatives are available in the IPNET \
                stack, and for which 'wrapper' functions matching the \
                original APIs are provided as a backwards compatibility aid. \
                The components in this folder cause inclusion of the wrappers.
    CHILDREN    INCLUDE_IPWRAP_ARP \
                INCLUDE_IPWRAP_GETADDRINFO \
                INCLUDE_IPWRAP_GETIFADDRS \
                INCLUDE_IPWRAP_GETNAMEINFO \
                INCLUDE_IPWRAP_GETHOSTBYNAME \
                INCLUDE_IPWRAP_GETHOSTBYADDR \
                INCLUDE_IPWRAP_GETSERVBYNAME \
                INCLUDE_IPWRAP_GETSERVBYPORT \
                INCLUDE_IPWRAP_IFNAME \
                INCLUDE_IPWRAP_INETLIB \
                INCLUDE_IPWRAP_SNTPCTIMEGET \
                INCLUDE_IPWRAP_SNTPSCLOCKSET \
                INCLUDE_IPWRAP_SNTPSNSECTOFRACTION \
                INCLUDE_IPWRAP_IFLIB \
                INCLUDE_IPWRAP_IF6LIB
}

Folder FOLDER_IPUTILSLIB {
    NAME        utilslib wrappers
    SYNOPSIS    This folder contains components which provide various utility \
                APIs available in older versions of the VxWorks networking \
                stack for which close alternatives are available in the IPNET \
                stack, and for which 'wrapper' functions matching the \
                original APIs are provided as a backwards compatibility aid. \
                The components in this folder cause inclusion of the wrappers.
    CHILDREN    INCLUDE_IPWRAP_IPPROTO \
                INCLUDE_IPWRAP_IFCONFIG \
                INCLUDE_IPWRAP_IFSHOW \
                INCLUDE_IPWRAP_ROUTECMD \
                INCLUDE_IPWRAP_NETSTAT \
                INCLUDE_IPWRAP_PING \
                INCLUDE_IPWRAP_PING6 \
                INCLUDE_IPWRAP_OLDROUTELIB
}

Folder FOLDER_IPWRAP {
    NAME        Backwards compatibiilty wrapper routines
    SYNOPSIS    This folder contains components which provide various APIs \
                available in older versions of the VxWorks networking stack \
                for which close alternatives are available in the IPNET \
                stack, and for which 'wrapper' functions matching the \
                original APIs are provided as a backwards compatibility aid. \
                The components in this folder cause inclusion of the wrappers.
    CHILDREN    FOLDER_IPLIBC \
                FOLDER_IPUTILSLIB
}
