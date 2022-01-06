/* 00comp_net_sysctl.cdf - Component configuration file */

/* Copyright 1984-2007 Wind River Systems, Inc. */

/*
modification history
--------------------
01m,13feb07,dlk  Add INCLUDE_IPNET_SYSCTL to separate IPNet sysctl subtree
                 creation from main network sysctl node creation.
01l,09dec06,tkf  Change module dependency.
01k,20sep06,tlu  removed rtsock_sysctl.o for IPNET integration
01j,26aug05,spm  fixed dependencies
01i,31aug04,vvv  updated component name
01h,24aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01g,12sep03,vvv  updated configlette path
01f,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01e,14may03,vvv  removed adv_net.h
01d,10jan03,ann  split SYSCTL into Sysctl and sysctl components
01c,16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01b,14feb02,ham  removed CONFIGLETTES.
01a,26nov01,ham  wrote.
*/

Component INCLUDE_NET_SYSCTL {
	NAME		NETWORK SYSCTL
	SYNOPSIS	Networking System control support
	HDR_FILES       sysctlLib.h
	CONFIGLETTES    usrNetSysctl.c
	INIT_RTN	usrNetSysctlInit();
	MODULES	    	netCoreSysctl.o 
 	REQUIRES 	INCLUDE_SYSCTL
}

Component INCLUDE_IPNET_SYSCTL {
	NAME		IPNet sysctl integration
	SYNOPSIS	Integrates IPNet sysctl nodes into VxWorks sysctl tree.
	INIT_RTN	netSysctlInit (TRUE);
	MODULES	    	netSysctl.o 
 	REQUIRES 	INCLUDE_NET_SYSCTL
	INCLUDE_WHEN	INCLUDE_NET_SYSCTL \
			INCLUDE_IPNET
}
