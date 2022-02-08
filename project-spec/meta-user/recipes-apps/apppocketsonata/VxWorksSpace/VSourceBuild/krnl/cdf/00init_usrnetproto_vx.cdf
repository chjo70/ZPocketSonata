/* 00init_usrnetproto.cdf - InitGroup configuration file */

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
01z,12apr08,zhr  Removed usrNetMib2Init for m2Lib migration.
01y,10sep06,tkf  Remove INCLUDE_ROUTING_SOCKET.
01x,07sep06,tkf  Remove INCLUDE_FASTUDP, INCLUDE_FASTUDP6.
01w,06sep06,tkf  Remove INCLUDE_SCTP.
01v,25aug06,kch  Removed unsupported components for IPNet integration.
01u,02mar06,dlk  Remove INCLUDE_IPFLOW (SPR #104107).
01t,11aug05,kch  Added INCLUDE_IFCLONE.
01s,03aug05,vvv  removed INCLUDE_SCTPV6
01r,20jul05,vvv  added SCTP components
01q,20may05,kch  Added INCLUDE_MIPV6 component for mobility support.
01p,02may05,kch  Added INCLUDE_MROUTEV6.
01o,23mar05,vvv  removed reference to INCLUDE_IPFW
01n,25feb05,niq  merge mroute changes from comp_wn_ipv6_multicast_interim-dev
                 branch  (ver 1)
01m,20sep04,sar  Remove dummynet and ipv6 fw
01l,03sep04,vvv  removed INCLUDE_IPDIVERT
01k,24aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01j,22apr04,vvv  removed ENCAP components (SPR #96452)
01i,21apr04,niq  Merge from base6_itn4_networking_perf-dev.al branch
01h,18mar04,spm  merged from Orion for MSP 3.0 baseline
01g,22sep02,asr  removed INCLUDE_MROUTE
01f,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01e,10apr03,vvv  added INCLUDE_IPFW (SPR #87544)
01d,07mar03,pas  added INCLUDE_TCP_DEBUG
01c,07jan03,ann  split IPV4 into multiple components
01b,19mar02,ham  added ROUTING_SOCKET.
01a,26nov01,ham  wrote.
*/

InitGroup usrNetProtoInit {
	NAME		Initialize network protocol stacks
	SYNOPSIS	Initialize the network protocol stacks
	INIT_RTN	usrNetProtoInit ();
	INIT_ORDER	INCLUDE_IPSEC 
}
