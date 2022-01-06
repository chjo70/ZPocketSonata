/* 00comp_net_netstat.cdf - Component configuration file */

/*
 * Copyright (c) 2002-2006 Wind River Systems, Inc.
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
01e,31jul06,kch  Simplified INCLUDE_NETSTAT for backward compatibility to
                 support IPNet stack.
01d,03mar05,wap  Add NET_SYSCTL dependency
01c,03apr03,vvv  modified for componentization (SPR #87352)
01b,24apr02,ppp  adding the entry point for netstat ,adding netstat_if.o,
                 netstat_mroute.o , netstat_mroute6.o
01a,02feb02,ham  wrote.
*/


Component INCLUDE_NETSTAT
	{
	NAME		netstat
	SYNOPSIS	netstat
	REQUIRES	INCLUDE_IPWRAP_NETSTAT
}
