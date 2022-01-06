/* 00comp_net_rem_io.cdf - Component configuration file */

/* Copyright 1984-2003, 2016 Wind River Systems, Inc. */

/*
modification history
--------------------
07dec16,mca  Break hard dependency between END and IPNET (US85582)
12sep03,vvv  updated configlette path
16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
06mar02,ham  removed REMLIB from REQUIRES
06mar02,ham  ported from TOR3_1-FCS (01f).
*/

Component INCLUDE_NET_REM_IO {
	NAME			network remote I/O access
	SYNOPSIS		Allows access to file system on boot host
	CONFIGLETTES		usrNetRemoteCfg.c
	INIT_RTN		usrNetRemoteCreate ();
	REQUIRES		INCLUDE_BOOT_LINE_INIT \
				INCLUDE_NET_BOOT       \
				INCLUDE_NET_DRV        \
				INCLUDE_NET_HOST_SETUP \
				INCLUDE_IPNET
}
