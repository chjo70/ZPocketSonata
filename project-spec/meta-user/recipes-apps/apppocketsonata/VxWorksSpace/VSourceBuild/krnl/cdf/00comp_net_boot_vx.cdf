/* 00comp_net_boot.cdf - Component configuration file */

/* Copyright 1984-2003, 2007, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,07feb12,dlk  Fix defect WIND00331675.
01f,25aug07,tkf  Add INCLUDE_NET_BOOT_IPV6_CFG as part of the fix for
                 CQ:WIND00102553.
01e,12sep03,vvv  updated configlette path
01d,17jun03,vvv  added dependency on INCLUDE_NETMASK_GET (SPR #88786)
01c,16arp02,rvr  removed  PREF_DOMAIN attribute
01c,06mar02,ham  removed usrNetBootUtil.c
01b,28feb02,ham  added usrNetBootUtil.c for usrNetmaskGet().
01a,26nov01,ham  wrote.
*/

Component INCLUDE_NET_BOOT {
	NAME		Boot parameter process
	SYNOPSIS	Copy boot parameters for futher use by network
	CONFIGLETTES    usrNetBoot.c
        INIT_RTN        usrNetBoot ();
	REQUIRES        INCLUDE_NETMASK_GET
	HDR_FILES	private/fioLibP.h
}

Component INCLUDE_NET_BOOT_IPV6_CFG {
	NAME            Boot device IPv6 parameter configuration
	SYNOPSIS        Configure the boot network device with IPv6 parameters.
	CONFIGLETTES    usrNetBootConfig.c
	INIT_RTN        usrCheckNetBootIpv6Config();
	REQUIRES        INCLUDE_IPCOM_USE_INET6
	EXCLUDES        INCLUDE_IPCOM_USE_INET
	HDR_FILES	private/fioLibP.h
}
