/* 00folder_net_socket.cdf - Folder configuration file */

/*
 * Copyright (c) 2001-2006, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
15feb14,zan  Add FOLDER_NET_SOCKET which is missed in prior modification.
01k,18nov06,kch  Corrected default configurations for FOLDER_IPNET_SOCKET.
01j,22sep06,tkf  Move IPNET Socket components into here.
01i,10sep06,tkf  Remove INCLUDE_ROUTING_SOCKE.
01h,07sep06,tkf  Remove INCLUDE_ZBUF_SOCKET.
01g,25aug06,kch  Removed unsupported components for IPNet integration.
01f,02dec03,vvv  added INCLUDE_SC_SOCKLIB
01e,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01d,21feb02,ham  added ROUTING_SOCKET
01c,26nov01,ham  revised.
*/

Folder FOLDER_NET_SOCKET {
        NAME        Network socket
	  SYNOPSIS    This folder contains components related to network sockets.
}

Folder FOLDER_IPNET_SOCKET {
    NAME        Network sockets
    SYNOPSIS    This folder contains components related to network sockets.
    CHILDREN    INCLUDE_IPNET_USE_ROUTESOCK \
                INCLUDE_IPNET_USE_SOCK_COMPAT \
                INCLUDE_IPNET_USE_NETLINKSOCK \
                INCLUDE_IPNET_SOCKET
    _CHILDREN   FOLDER_NET_SOCKET
    DEFAULTS    INCLUDE_IPNET_USE_ROUTESOCK \
                INCLUDE_IPNET_USE_SOCK_COMPAT \
                INCLUDE_IPNET_SOCKET
}

