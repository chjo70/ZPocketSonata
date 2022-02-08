/* 00init_usrnethost.cdf - InitGroup configuration file */

/* Copyright 1984 - 2003 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01a,03sep02,ism  wrote
*/

InitGroup usrNetHostInit {
	NAME		initialize host table
	INIT_RTN	usrNetHostInit ();
	INIT_ORDER	INCLUDE_HOST_TBL \
                        INCLUDE_GETADDRINFO \
                        INCLUDE_GETNAMEINFO \
                        INCLUDE_GETSERVBYNAME \
			INCLUDE_NET_HOST_SETUP
}
