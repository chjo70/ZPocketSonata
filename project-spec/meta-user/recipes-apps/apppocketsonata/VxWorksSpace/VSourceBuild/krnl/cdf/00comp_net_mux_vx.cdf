/* 00comp_net_mux.cdf - Component configuration file */

/*
 * Copyright (c) 2001-2003, 2006, 2008, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05may14,rjq  Decouple COREIP with END. (V7NET-105)
06jun08,dlk  Correct for ipcom --> vxmux renaming.
             Add INCLUDE_VXMUX_MBLK component for better scalability.
22mar08,dlk  MUX2 redesign.
02jul06,kch  Removed if_subr.o.
14may03,vvv  removed adv_net.h
16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01apr02,ham  fixed typo
01apr02,ham  added if_subr.o
21feb02,ham  deleted MUX_MAX_BINDS_CFG.
26nov01,ham  wrote.
*/

Component INCLUDE_MUX2 {
	NAME		MUX mux2Bind() service
	SYNOPSIS	Support mux2Bind() protocols and their APIs
	INIT_RTN	mux2LibInit();
	HDR_FILES	mux2Lib.h
	MODULES		vxmux_mux2.o
}

Component INCLUDE_MUX2_OVER_END {
	NAME		MUX mux2Bind() service / END-style device
        SYNOPSIS	Support mux2Bind() protocols over END-style devices
        INIT_RTN	mux2OverEndInit();
        HDR_FILES	muxLib.h
        MODULES		vxmux_mux2_over_end.o
        INCLUDE_WHEN	INCLUDE_MUX2 INCLUDE_END
}

Component INCLUDE_MUX_OVER_END2 {
	NAME		MUX muxBind() service / END2-style device
        SYNOPSIS	Support muxBind() protocols over END2-style devices
        INIT_RTN	muxOverEnd2Init();
        HDR_FILES	muxLib.h
        MODULES		vxmux_mux_over_end2.o
        INCLUDE_WHEN	INCLUDE_MUX INCLUDE_END2
}

Component INCLUDE_MUXTK_OVER_END2 {
	NAME		MUX muxTkBind() service / END2-style device
        SYNOPSIS	Support muxTkBind() protocols over END2-style devices
        INIT_RTN	muxTkOverEnd2Init();
        HDR_FILES	muxLib.h
        MODULES		vxmux_muxtk_over_end2.o
        INCLUDE_WHEN	INCLUDE_MUXTK INCLUDE_END2
}

Component INCLUDE_VXMUX_MBLK {
	NAME		MUX private support for M_BLK/Ipcom_pkt conversion
	SYNOPSIS	MUX private support for M_BLK/Ipcom_pkt conversion
	MODULES		vxmux_mux_mblk.o
	PROTOTYPE	void vxmux_mux_mblk_init (void);
	INIT_RTN	vxmux_mux_mblk_init ();
	REQUIRES	INCLUDE_VXMUX_NULLBUFPOOL	
}
