/* 00comp_net_mux.cdf - MUX Component configuration file */

/* Copyright 2014, 2016-2017 Wind River Systems, Inc. */

/*
modification history
--------------------
19jan17,mca  Moved INCLUDE_ETHERNET to 01comp_net_end_vx.cdf
07dec16,mca  Break hard dependency between END and IPNET (US85582)
05may14,rjq  New. (V7NET-105)
*/

Folder FOLDER_NET_MUX {
    NAME        Network MUX Components
    SYNOPSIS    Support for network multiplexer.
    CHILDREN    INCLUDE_MUX_COMMON \
                INCLUDE_MUX \
                INCLUDE_MUXTK \
                INCLUDE_MUXTK_OVER_END \
                INCLUDE_MUX_IF_FUNC_DBASE
    _CHILDREN   FOLDER_NETWORK
    DEFAULTS    INCLUDE_MUX_COMMON \
                INCLUDE_MUX \
                INCLUDE_MUXTK
}

Component INCLUDE_MUX_COMMON {
    NAME        MUX common support (all service and device styles)
    SYNOPSIS    MUX common support (all protocol and device styles)
    INIT_RTN    muxCommonInit();
    HDR_FILES   muxLib.h
    MODULES     muxCommon.o
    REQUIRES    INCLUDE_NETWORK
}

Component INCLUDE_MUX {
	NAME		MUX muxBind() service
	SYNOPSIS	Support muxBind() protocols and their APIs
	INIT_RTN	muxLibInit();
	HDR_FILES	muxLib.h
	MODULES		muxLib.o
	REQUIRES	INCLUDE_END_ETHER_HDR
}

Component INCLUDE_MUXTK {
	NAME		MUX muxTkBind() service
	SYNOPSIS	Support muxTkBind() protocols and their APIs
	INIT_RTN	muxTkLibInit();
	HDR_FILES	muxTkLib.h
	MODULES		muxTkLib.o
	REQUIRES	INCLUDE_END_ETHER_HDR
}

Component INCLUDE_MUXTK_OVER_END {
	NAME		MUX muxTkBind() service / END-style device
  SYNOPSIS	Support muxTkBind() protocols over END-style devices
  INIT_RTN	muxTkOverEndInit();
  HDR_FILES	muxLib.h
  MODULES		muxTkOverEnd.o
  INCLUDE_WHEN	INCLUDE_MUXTK INCLUDE_END
}

Component INCLUDE_MUX_IF_FUNC_DBASE {
	NAME		MUX interface function database (obsolete)
	SYNOPSIS	MUX interface function database (obsolete)
	INIT_RTN	muxIfFuncBaseInit();
	HDR_FILES	muxLib.h
	MODULES		muxIfFuncBase.o
}
