/* 00comp_net_ping.cdf - Component configuration file */

/*
 * Copyright (c) 1999-2006 Wind River Systems, Inc.
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
01g,03aug06,kch  Simplified INCLUDE_PING to support IPNet stack.
01f,16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01e,04jun00,pad  Addition of PREF_DOMAIN attribute
01d,14jan00,ham  added missing stuffs
01c,04nov99,ham  added ENTRY_POINTS
01b,24aug99,cym  adding pingLib.h (tor2_0_x merge)
01a,05may99,cym  re-organized.
*/

Component INCLUDE_PING {
	NAME		PING client
	SYNOPSIS	ICMP (ping) client
	HDR_FILES	pingLib.h
	REQUIRES	INCLUDE_IPWRAP_PING
}

