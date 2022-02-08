/* 00comp_net_arplib.cdf - Component configuration file */

/* Copyright 1984 - 2003 Wind River Systems, Inc. */

/*
modification history
--------------------
01f,31aug06,tkf  Change INCLUDE_ARP_API so that it depends on
                 INCLUDE_IPWRAP_ARP. Also removed all configuration
                 parameters.
01e,12sep03,vvv  updated configlette path
01d,14may03,vvv  added HDR_FILES
01c,16arp02,rvr  removed entry points and PREF_DOMAIN attribute
01b,01apr02,ham  added entry points.
01a,06feb02,ham  wrote.
*/


Component INCLUDE_ARP_API
	{
	NAME		arpLib
	SYNOPSIS	Address Resolution Protocol (ARP) table manipulation library 
    REQUIRES    INCLUDE_IPWRAP_ARP
}
