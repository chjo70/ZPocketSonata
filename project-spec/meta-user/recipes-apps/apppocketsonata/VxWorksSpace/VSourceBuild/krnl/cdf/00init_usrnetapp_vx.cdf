/* 00init_usrnetapp.cdf - InitGroup configuration file */

/*
 * Copyright (c) 1999-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */


/*
modification history
--------------------
02i,24nov10,rjq  move INCLUDE_FTP to 00init_usrnetremote.cdf
02h,22nov06,kch  Removed INCLUDE_TELNET.
02g,30aug06,kch  Removed unsupported components for IPNet integration.
02f,19jan06,xli  add SNMP component for SSI compliant
02e,28oct05,tlu  add INCLUDE_MIP_HA before RTADV
02d,09sep05,xli  move INCLUDE_MIP_MN before RTSOL
02c,04may05,kch  Added INCLUDE_MLD6_ROUTER component.
02b,29mar05,vvv  added INCLUDE_DHCP6C_SHOW (SPR #98613)
02a,27jan05,vvv  removed IPv4-only FTP server; added missing component
                 INCLUDE_FTPD6_GUEST_LOGIN
01z,27aug04,vvv  removed INCLUDE_FTPD_LINGER_SECONDS (not required)
01y,24aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01x,07jul04,kc   Removed references to INCLUDE_OSPF and INCLUDE_OSPFV3.
01w,28jun04,kc   Added initialization for INCLUDE_AIP component.
01v,23jun04,kc   Added initialization for INCLUDE_OSPF and INCLUDE_OSPFV3
                 components.
01u,14may04,syy  Add initialization for DHCPv6 components
01t,12apr04,vvv  added INCLUDE_PROXY_SERVER (SPR #95263)
01s,09apr04,rp   merged from accordion
01r,31mar04,asr  Added anonymous FTP component
01q,28jan04,zhr  Added TELNET client
01p,10oct03,msc  Added NFS server and Client
01o,08sep03,htm  Added SNTP client and server.
01n,08aug03,ggg  remove INCLUDE_SNMPD as it is now a folder and not a component
01m,18oct02,ann  added SNMP components. Envoy tries to install them
                 in 00network.cdf and will fail as this init group
                 no longer resides there.
01l,25aug02,ham  back-merged to 01j&01i changes.
01k,23aug02,ham  removed LOGIN and SECURE_SHELL
01j,23aug02,kal  added RIP and RIPng
01i,22aug02,kal  added RTSOL and RTADV
01h,13jun02,ann  added RLOGIN component
01g,06jun02,ant  added INCLUDE_FTP and INCLUDE_FTP6
01f,12mar02,hgo  removed RLOGIN
01e,07may01,ham  fixed initialization misorder (SPR #66853).
01d,11sep00,fmk  added INCLUDE_LOGIN and INCLUDE_SECURE_SHELL
01c,10aug00,spm  added proxy ARP components
01b,17apr00,ham  removed STREAMS, SNMP.
01a,05may99,cym  re-organized.
*/

InitGroup usrNetAppInit {
	NAME		initialize network application protocols
	INIT_RTN	usrNetAppInit ();
	INIT_ORDER	INCLUDE_RPC \
         		INCLUDE_NFS2_CLIENT \
         		INCLUDE_NFS3_CLIENT \
         		INCLUDE_NFS_MOUNT_ALL \
         		INCLUDE_NFS2_SERVER \
         		INCLUDE_NFS3_SERVER \
                        INCLUDE_NFS_DEBUG \
         		INCLUDE_NFS_SERVER_INSTALL \
			INCLUDE_TELNET_CLIENT \
			INCLUDE_FTP6 \
			INCLUDE_RLOGIN \
                        INCLUDE_SNMP_STATIC_INIT \
                        INCLUDE_SNMP_DYNAMIC_INIT \
                        INCLUDE_SNMP_MANAGER
}
