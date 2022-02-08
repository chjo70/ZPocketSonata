/* 00init_usrnetmib2.cdf - InitGroup configuration file */

/* Copyright 2001 - 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01g,13sep10,h_x  CQ: WIND00141200
01f,12apr08,zhr  Migratied to ipnet
01e,09jul04,rae  add INCLUDE_IFINDEX (SPR #98870)
01d,11oct02,ham  added MIB2_ALL/MIB2_IPV6ALL (SPR 83041).
01c,01oct02,ham  added SYSTEM.
01b,25sep02,ham  added IFMGT.
01a,26nov01,ham  wrote.
*/

#ifdef _WRS_CONFIG_COMPONENT_VXCOMPAT

InitGroup usrNetMib2Init {
	NAME		Initialize MIB2
	SYNOPSIS	Initialize MIB2
	INIT_RTN	usrNetMib2Init ();
	INIT_ORDER	INCLUDE_IFINDEX \
			INCLUDE_MIB2_ALL \
			INCLUDE_MIB2_IF	\
			INCLUDE_MIB2_IFMGT \
			INCLUDE_MIB2_SYSTEM \
			INCLUDE_MIB2_IP \
			INCLUDE_MIB2_UDP \
			INCLUDE_MIB2_TCP \
			INCLUDE_MIB2_ICMP 
}
#endif
