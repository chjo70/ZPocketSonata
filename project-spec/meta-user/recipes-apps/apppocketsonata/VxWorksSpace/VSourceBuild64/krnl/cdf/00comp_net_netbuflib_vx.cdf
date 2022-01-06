/* 00comp_net_netbuflib.cdf - Component configuration file */

/* Copyright 2002-2008, 2012, 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
05may14,rjq  Move netbuf to base layer. (V7NET-105)
18apr12,dhe  Increased leading pad space for IPsec enabled builds.
06jun08,dlk  Correct for renaming of vxmux components.
21feb07,dlk  netBufLibInit() -> netBufLibInitialize(). WIND00088386.
02jan07,dlk  Added INCLUDE_MBUF_UTIL1 and INCLUDE_MBUF_UTIL2.
12jun06,dlk  Added INCLUDE_NULLBUFPOOL.
25jul05,dlk  Added INCLUDE_NETBUFADVLIB and INCLUDE_NETPOOLSHOW.
14apr04,rhe  Corrected names for netBufPool and linkBufPool SPR:96248
18Nov03 rhe  Added components netBufPool and linkBufPool
14may03,vvv  removed adv_net.h
16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
05mar02,ham  wrote.
*/

Component INCLUDE_VXMUX_NULLBUFPOOL {
	NAME		nullBufPool
	SYNOPSIS	Minimal clusterless network pool implementation \
for IPCOM
	HDR_FILES	netBufLib.h
	INIT_RTN	vxmux_null_buf_init ();
	MODULES		vxmux_null_buf.o 
	REQUIRES	INCLUDE_NETBUFLIB
	_CHILDREN FOLDER_NET_CORE
}

