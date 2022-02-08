/* 00comp_net_getnameinfo.cdf - Component configuration file */

/*
 * Copyright (c) 2003 - 2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01h,14sep10,h_x CQ:WIND00141200
01g,12feb07,dlk  Add INIT_RTN for INCLUDE_GETNAMEINFO_SYSCTL.
01f,28sep06,tlu  Restore INCLUDE_GETNAMEINFO_SYSCTL
01e,31jul06,kch  Removed the unsupported INCLUDE_GETNAMEINFO_SYSCTL.
01d,31jul06,tkf  Make INCLUDE_GETNAMEINFO dependent on
                 INCLUDE_IPWRAP_GETNAMEINFO.
01c,03mar05,wap  handle NET_SYSCTL dependency
01b,05dec03,vvv  updated for RTP support
01a,15jan03,ann  re-organized.
*/

Component INCLUDE_GETNAMEINFO {
	NAME		get name info
	SYNOPSIS	utility to map host address to name
        CONFIGLETTES    usrGetnameinfo.c
	REQUIRES	INCLUDE_IPWRAP_GETNAMEINFO
}

Component INCLUDE_GETNAMEINFO_SYSCTL {
        NAME            RTP getnameinfo() sysctl support
        SYNOPSIS        network sysctl tree support for RTP getnameinfo()
	HDR_FILES	netdb.h
        INIT_RTN        rtpGetnameinfoInit ();
	MODULES		rtpGetnameinfo.o
        REQUIRES        INCLUDE_NET_SYSCTL \
                        INCLUDE_IPWRAP_GETNAMEINFO
        INCLUDE_WHEN    INCLUDE_RTP \
                        INCLUDE_IPWRAP_GETNAMEINFO
}

