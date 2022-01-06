/* 00comp_net_host_tbl.cdf - Component configuration file */

/*
 * Copyright (c) 1999-2007,2010,2016 Wind River Systems, Inc.
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
30aug16,rjq  INCLUDE_HOST_TBL should depend on INCLUDE_NETWORK.
14sep10,h_x  CQ:WIND00141200
12feb07,dlk  Add INIT_RTN to INCLUDE_HOST_TBL_SYSCTL.
26dec06,kch  Changed INCLUDE_HOST_TBL init routine to usrNetHostTblSetup().
23sep06,tlu  Restore INCLUDE_HOST_TBL_SYSCTL component
24aug06,kch  Removed unsupported INCLUDE_HOST_TBL_SYSCTL component.
02mar05,wap  handle NET_SYSCTL dependency
19sep04,spm  update host table initialization for virtual stack startup
20feb04,vvv  removed reference to hostUtils.o
12sep03,vvv  updated configlette path
08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
14mar03,ann  renamed hostentUtils.o to hostUtils.o
13aug02,ham  removed REQUIRES to be independent from DNS_RESOLVER.
16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
29jan02,hgo  due to IPv6
14jan02,ger	 due to IPv6
04jun00,pad  Addition of PREF_DOMAIN attribute
17apr00,ham  revised.
15sep99,jgn  add missing entry point information
05may99,cym  re-organized.
*/

Component INCLUDE_HOST_TBL {
	NAME		host table
	SYNOPSIS	host table support
	REQUIRES	INCLUDE_NETWORK
	CONFIGLETTES   usrNetHostTblCfg.c
	HDR_FILES	hostLib.h 
	INIT_RTN	usrNetHostTblSetup ();
	MODULES		hostLib.o
}

Component INCLUDE_HOST_TBL_SYSCTL {
        NAME            host table sysctl support
        SYNOPSIS        network sysctl tree support for host tables
        REQUIRES        INCLUDE_NET_SYSCTL \
			INCLUDE_HOST_TBL
	INIT_RTN	rtpHostLibInit ();
	MODULES		rtpHostLib.o
        INCLUDE_WHEN    INCLUDE_RTP \
                        INCLUDE_HOST_TBL
}

