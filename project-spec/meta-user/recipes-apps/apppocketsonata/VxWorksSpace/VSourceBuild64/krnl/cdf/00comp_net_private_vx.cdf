/* 00comp_net_private.cdf - Component configuration file */

/*
 * Copyright (c) 1984-2006, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02k,07feb12,dlk  Fix defect WIND00331675.
02j,06oct06,kch  Cleanup INCLUDE_NET_BOOT_CONFIG properties.
02i,24aug06,kch  Removed unsupported components for IPNet integration.
02h,24jul06,tkf  Change INCLUDE_IP6ATTACH/INCLUDE_IPATTACH requirement to be
                 INCLUDE_IPWRAP_IPPROTO.
                 Also changed INCLUDE_GETIFADDRS requirement to be
                 INCLUDE_IPWRAP_GETIFADDRS.
02g,26aug05,spm  updated sysctl dependencies (SPR #106702)
02f,29mar05,vvv  removed INCLUDE_SNPRINTF (SPR #98613)
02e,03mar05,vvv  added dependency on INCLUDE_ROUTING_SOCKET for
                 INCLUDE_GETIFADDRS
02d,03mar05,niq  Remove NET_GETOPT
02c,03mar05,wap  Add NET_SYSCL dependency
02b,21sep04,dlk  Remove INCLUDE_NET_APPUTIL, superseded by
		 INCLUDE_APPL_LOG_UTIL.
02a,30aug04,dlk  Add net/if.h and sys/sockio.h to HDR_FILES for
                 INCLUDE_NET_BOOT_CONFIG.
01z,24aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01y,02jul04,rae  IPATTACH does not require INCLUDE_MIB2_IF
01y,29jun04,niq  Move the call to splSemInit to netCoreInstInit - Remove
                 INCLUDE_UNIXLIB
01x,18may04,snd  Fixing SPR 89215, DHCP client unable to obtain lease 
                 when booting from non-network device 
01w,14apr04,elp  passed pDevName and uNum as usrNetIpv6Attach() parameters.
01v,20feb04,vvv  added INCLUDE_UNIXLIB
01u,14jan04,pas  include IP[6]ATTACH when IPv[46] is included and
                 NET_INIT is selected (SPR #92787)
01t,12sep03,vvv  updated configlette path
01s,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01r,23jun03,vvv  include IP6ATTACH when IPv6 is included (SPR #88983)
01q,20jun03,ann  removed INCLUDE_ZLIB
01p,17jun03,vvv  added INCLUDE_NETMASK_GET (SPR #88786)
01o,15may03,vvv  modified for INCLUDE_DEFER_NET_INIT
01n,14may03,vvv  removed adv_net.h
01m,02oct02,ham  removed md5.o from INCLUDE_NET_MD5.
01l,13aug02,ham  added MIB2_IF to IPATTCH/IP6ATTACH (SPR#80545)
01k,27jun02,ppp  merged with the t3 cdfs
01j,06jun02,rvr  removed INCLUDE_BUFFER and INCLUDE_OS_IOLIB
01i,16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01h,01apr02,ham  removed INETLIB.
01g,24mar02,ham  added INCLUDE_WHEN for private components.
01f,06mar02,ham  removed space char at component name.
01e,28feb02,ham  changed in response to reverse of usrNetBoot.c change.
01d,19feb02,ham  moved XDR to 00comp_net_rpc.cdf.
01c,13feb02,ham  changed IP6ATTACH for adding ip6_init2 call. 
01b,05feb02,ham  renamed IFCOFIG to BOOT_CONFIG, added GETIFADDRS, IFNAME
01a,26nov01,ham  wrote.
*/

Component INCLUDE_NET_BOOT_CONFIG {
    NAME            network boot device configuration
    SYNOPSIS        network boot device configuration with boot parameters
    CONFIGLETTES    usrNetBootConfig.c
    INIT_RTN        usrCheckNetBootConfig (pDevName, uNum, pAddrString,\
                    netmask, sysBootParams.gad);
    INCLUDE_WHEN    INCLUDE_NET_BOOT \
                    INCLUDE_NET_INIT
    REQUIRES        INCLUDE_NET_BOOT \
                    INCLUDE_SOCKLIB \
                    INCLUDE_NET_INIT
    HDR_FILES       private/fioLibP.h
}

Component INCLUDE_IPATTACH {
	NAME		Attach END to IPv4
	SYNOPSIS	Attach boot END device to IPv4
	REQUIRES	INCLUDE_IPWRAP_IPPROTO
}


Component INCLUDE_IP6ATTACH {
	NAME		Attach END to ipv6
	SYNOPSIS	Attach boot END device to IPv6
	REQUIRES	INCLUDE_IPWRAP_IPPROTO INCLUDE_IPCOM_USE_INET6
}

Component INCLUDE_NETMASK_GET {
	NAME            network device netmask setup
	SYNOPSIS        Extracts netmask value from address field
	CONFIGLETTES    usrNetBoot.c
	INIT_RTN        usrNetmaskGet ();
}
