/* 00folder_net_sysctl.cdf - Folder configuration file */

/* Copyright 1984 - 2004, 2007 Wind River Systems, Inc. */

/*
modification history
--------------------
04jul16,ghl  Fix INCLUDE_IPSYSCTL_CMD is not visible in Kernel Configuration
             on workbench for vxworks-7.(V7NET-877) 
17aug07,mwv  remove trailing whitespace after backslash
13feb07,dlk  Added auxiliary sysctl components.
31aug04,vvv  updated sysctl component
24aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
20nov03,vvv  added INCLUDE_SC_SYSCTL
10jan03,ann  written.
*/

Folder FOLDER_NET_SYSCTL {
	NAME		SYSCTL
	SYNOPSIS	This folder contains components and parameters concerning SYSCTL. \
			SYSCTL is a C shell utility that you can use to retrieve and configure run time parameters.
	CHILDREN	INCLUDE_NET_SYSCTL \
			INCLUDE_IPSYSCTL_CMD  \
			INCLUDE_IPNET_SYSCTL \
			INCLUDE_HOST_TBL_SYSCTL \
			INCLUDE_GETADDRINFO_SYSCTL \
			INCLUDE_GETNAMEINFO_SYSCTL \
			INCLUDE_REMLIB_SYSCTL
	DEFAULTS	INCLUDE_NET_SYSCTL
}
