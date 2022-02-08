/* 00init_usrnetutils.cdf - InitGroup configuration file */

/*
 * Copyright (c) 2001-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01v,27sep06,tkf  Add INCLUDE_NET_HOST_SHOW.
01u,03aug06,kch  Removed unsupported components.
01t,11feb06,kch  Added INCLUDE_ALTQ_CONFIG.
01s,18aug05,kch  Added INCLUDE_L2CONFIG.
01r,20jul05,vvv  added INCLUDE_NETSTAT_SCTP
01q,09jun05,rp   added INCLUDE_ADDRCTL_POLICY
01p,04may05,kch  Added INCLUDE_NETSTAT_MROUTEV6.
01o,03mar05,wap  Add INCLUDE_INETLIB_SYSCTL
01n,19sep04,rae  add INCLUDE_IGMP_ROUTER
01m,24aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01l,09jul04,rae  add INCLUDE_OLDROUTE
01k,24nov03,ppp  added INCLUDE_INETLIB
01j,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01i,07apr03,ann  added all the components as a result of the netShow.c
                 split - SPR# 86899
01h,03apr03,vvv  added netstat components (SPR #87352)
01g,01mar03,pas  added IF6LIB
01f,20feb03,ann  added INCLUDE_IFCONFIG_PREFIX
01e,06aug02,ppp  added INCLUDE_PREFIXCMD
01d,24mar02,ham  fixed typo.
01c,06mar02,ham  added IFLIB, ARP_API.
01b,06feb02,ham  renamed to usrNetUtils, added utilities.
01a,26nov01,ham  wrote.
*/

InitGroup usrNetUtilsInit {
	NAME		Initialize network utility routines
	SYNOPSIS	Initialize network utility routines
	INIT_RTN	usrNetUtilsInit ();
	INIT_ORDER	INCLUDE_L2CONFIG  \
			INCLUDE_IFCONFIG \
            INCLUDE_NET_HOST_SHOW \
			INCLUDE_ROUTECMD
}
