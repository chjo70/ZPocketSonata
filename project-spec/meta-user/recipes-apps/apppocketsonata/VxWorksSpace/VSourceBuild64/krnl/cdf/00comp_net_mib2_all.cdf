/* 00comp_net_mib2_all.cdf - Component configuration file */

/* Copyright 1984 - 2002 Wind River Systems, Inc. */

/*
modification history
--------------------
01g,13sep10,h_x  CQ: WIND00141200
01f,12apr02,zhr  migrated to ipnet
01g,11oct02,ham  added INIT_RTN (SPR 83041).
01f,01oct02,ham  ported from AE.
01e,07may01,ham  fixed initialization misorder (SPR #66853).
01d,04jun00,pad  Addition of PREF_DOMAIN attribute
01c,17mar00,ham  revised.
01b,14jan00,ham  added missing stuffs.
01a,05may99,cym  re-organized.
*/

#ifdef _WRS_CONFIG_COMPONENT_VXCOMPAT

Component INCLUDE_MIB2_ALL {
	NAME		All MIB2 IPv4 Management Components
	SYNOPSIS	Includes all MIB2 IPv4 management components.
	HDR_FILES	m2Lib.h 
	INIT_RTN	m2LibInit();
	MODULES		m2Lib.o 
}
#endif
