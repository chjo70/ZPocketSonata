/* 00folder_net_show.cdf - Folder configuration file */

/* Copyright 1984 - 2003 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,08sep06,tkf  Remove INCLUDE_NET_IF_SHOW, INCLUDE_IGMP_SHOW,
                 INCLUDE_NET_ROUTE_SHOW, INCLUDE_NET_SHOW, INCLUDE_TCP_SHOW.
                 SELECT_NET_ROUTE_SHOW_BUFFERING, INCLUDE_UDP_SHOW
01d,06sep06,tkf  Remove INCLUDE_ICMPXXX components.
01c,28jul05,dlk  Added INCLUDE_NETPOOLSHOW.
01b,30sep04,dlk  Add SELECT_NET_ROUTE_SHOW_BUFFERING.
01a,07apr03,ann  written - SPR# 86899
*/

Folder FOLDER_NET_SHOW {
	NAME		Show Routine
	SYNOPSIS	This folder contains the network show functions. See the Wind River \
			Network Stack for VxWorks 7 Programmer's Guide.
	CHILDREN	FOLDER_AF_LOCAL_SHOW \
                        INCLUDE_NETPOOLSHOW \
                        INCLUDE_NET_HOST_SHOW
        DEFAULTS        INCLUDE_NETPOOLSHOW
}
