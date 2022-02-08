/* 01folder_net_mib2.cdf - Folder configuration file */

/* Copyright 2001,2002,2004,2008,2010,2014 Wind River Systems, Inc. */

/*
modification history
--------------------
08oct14,rjq  FOLDER_NET_MIB2 is not seen in VIP. (V7NET-462)
13sep10,h_x  CQ: WIND00141200
01apr08,zhr  Migrated to ipnet
01jul04,rae  add INCLUDE_IFINDEX (SPR #98870)
18oct02,ann  added the SNMP component into FOLDER_NET_MIB2
01oct02,ham  added SYSTEM, ALL and IPV6ALL.
25sep02,ham  added IFMGT
18Jun02,ism  Added IPv6 components
26nov01,ham  revised.
*/

#ifdef _WRS_CONFIG_COMPONENT_VXCOMPAT

Folder FOLDER_NET_MIB2 {
	NAME		Network components for MIB2
	SYNOPSIS	This folder contains network components and parameters related to the Management Information Base 2 (MIB2)
	_CHILDREN   FOLDER_NET_L5_APPLICATIONS
	CHILDREN	INCLUDE_MIB2_IF \
			INCLUDE_MIB2_IFMGT \
			INCLUDE_MIB2_ALL \
			INCLUDE_MIB2_IPV6ALL \
			INCLUDE_MIB2_IP \
			INCLUDE_MIB2_UDP \
			INCLUDE_MIB2_TCP \
			INCLUDE_MIB2_ICMP \
			INCLUDE_MIB2_SYSTEM \
			INCLUDE_MIB2_MLD \
			INCLUDE_IFINDEX \
	DEFAULTS	INCLUDE_MIB2_IF \
			INCLUDE_MIB2_IP \
			INCLUDE_MIB2_UDP \
			INCLUDE_MIB2_TCP \
			INCLUDE_MIB2_ICMP \
			INCLUDE_IFINDEX
}
#endif
