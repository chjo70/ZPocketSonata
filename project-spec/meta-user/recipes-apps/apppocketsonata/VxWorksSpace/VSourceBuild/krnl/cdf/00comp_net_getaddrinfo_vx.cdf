/* 00comp_net_getaddrinfo.cdf - Component configuration file */

/*
 * Copyright (c) 2002-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01g,14sep10,h_x CQ:WIND00141200
01f,12feb07,dlk  Add INIT_RTN for INCLUDE_GETADDRINFO_SYSCTL.
01e,29sep06,tlu  Added INCLUDE_GETADDRINFO_SYSCTL, and configlettes and init
		 function 
01d,31jul06,tkf  Made it dependent on INCLUDE_IPWRAP_GETADDRINFO. Removed the
                 IGNORE_LINKLOCAL parameter.
01c,24jul06,tkf  Removed MODULE gethostbyname.o. Replaced INIT_RTN
                 gethostbynameInit() with getaddrinfoInit().
01b,28jun05,vvv  added IGNORE_LINKLOCAL
01a,15jan03,ann  re-organized.
*/

Component INCLUDE_GETADDRINFO {
	NAME		getaddrinfo
	SYNOPSIS	utility to map host name to address
        CONFIGLETTES    usrGetaddrinfo.c
    	REQUIRES	INCLUDE_IPWRAP_GETADDRINFO
}

Component INCLUDE_GETADDRINFO_SYSCTL {
        NAME            RTP getaddrinfo() sysctl support
        SYNOPSIS        network sysctl tree support for RTP getaddrinfo()
	HDR_FILES	netdb.h
	INIT_RTN	rtpGetaddrinfoInit ();
	MODULES		rtpGetaddrinfo.o
        REQUIRES        INCLUDE_NET_SYSCTL \
                        INCLUDE_IPWRAP_GETADDRINFO
        INCLUDE_WHEN    INCLUDE_RTP \
                        INCLUDE_IPWRAP_GETADDRINFO
}
