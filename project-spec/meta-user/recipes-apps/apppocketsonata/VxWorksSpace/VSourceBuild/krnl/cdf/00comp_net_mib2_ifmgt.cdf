/* 00comp_mib2_ifmgt.cdf - Component configuration file */

/* Copyright 1984 - 2002 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,12jan11,h_x  Fix WIND00249267
01d,13sep10,h_x  CQ: WIND00141200
01c,12apr02,zhr  Migrated to ipnet
01b,13may03,ppp  removed inclusion of adv_net.h
01a,25sep02,ham  wrote.
*/

#ifdef _WRS_CONFIG_COMPONENT_VXCOMPAT

Component INCLUDE_MIB2_IFMGT {
	NAME		MIB2 IF Management APIs
	SYNOPSIS	MIB2 IF Management APIs
        INIT_RTN	m2IfMgtLibInit ();
	MODULES		m2IfMgtLib.o 
#if defined(_WRS_CONFIG_COMPONENT_SNMP)
	REQUIRES INCLUDE_WINDMANAGE_SNMP_CORE
#endif
}

#endif
