/* 00comp_net_ping6.cdf - Component configuration file */

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
01g,02aug06,kch  Simplified INCLUDE_PING6 to support IPNet stack.
01f,16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01e,04jun00,pad  Addition of PREF_DOMAIN attribute
01d,14jan00,ham  added missing stuffs
01c,04nov99,ham  added ENTRY_POINTS
01b,24aug99,cym  adding pingLib.h (tor2_0_x merge)
01a,25jan02,ger  new for clarinet
*/

Component INCLUDE_PING6 {
	NAME		PING6 client
	SYNOPSIS	ICMP (ping6) client
	HDR_FILES	ping6Lib.h
	REQUIRES	INCLUDE_IPWRAP_PING6
}

