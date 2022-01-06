/* 00comp_socklib.cdf - Component configuration file */

/* Copyright 1984 - 2004, 2016 Wind River Systems, Inc. */

/*
modification history
--------------------
14jul16,dlk  Adding HDR_FILES sockLib.h.
21apr16,emj  CERT: Update to produce partially linked objects (US79607)
01f,29jun04,niq  Remove the UNIXLIB component
01e,28may04,dlk  removed obsolete SOCK_FD_MAX parameter
01d,20feb04,vvv  added dependency on INCLUDE_UNIXLIB
01c,14may03,vvv  removed adv_net.h
01b,16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01a,26nov01,ham  wrote.
*/

Component INCLUDE_SOCKLIB {
	NAME		Socket API
	SYNOPSIS	Socket API
        HDR_FILES       sockLib.h
	INIT_RTN	sockLibInit ();
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		sockLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
}

