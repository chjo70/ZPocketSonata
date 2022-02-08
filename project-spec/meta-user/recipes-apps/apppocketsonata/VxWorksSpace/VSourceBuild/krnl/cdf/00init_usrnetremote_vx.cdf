/* 00init_usrnetremote.cdf - InitGroup configuration file */

/* Copyright 1984 - 2003 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,24nov10,rjq  move INCLUDE_FTP from 00init_usrnetapp.cdf to
                 00init_usrnetremote.cdf
01d,03mar05,wap  Add INCLUDE_REMLIB_SYSCTL
01c,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01b,06mar02,ham  removed DNS_RESOLVER.
01a,06mar02,ham  ported from TOR3_1-FCS (01b).
*/

InitGroup usrNetRemoteInit {
	NAME		initialize network remote I/O access
	INIT_RTN	usrNetRemoteInit ();
	INIT_ORDER	INCLUDE_REMLIB \
			INCLUDE_REMLIB_SYSCTL \
			INCLUDE_FTP \
			INCLUDE_NET_DRV \
			INCLUDE_NET_REM_IO
}
