/* 00comp_net_init.cdf - Component configuration file */

/*
 * Copyright (c) 2001-2004, 2006, 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07dec16,mca  Break hard dependency between END and IPNET (US85582)
27may14,rjq  SELECT_IPNET_ETHERNET_IFCONFIG should be added
             by default. (V7NET-373)
06oct06,kch  Cleanup INCLUDE_NET_INIT properties.
20sep04,spm  updated virtual stack startup: stop packing and unpacking
              configuration parameters
30aug04,dlk  Make INCLUDE_NET_INIT require INCLUDE_NETWORK (SPR #101382).
09jul04,rae  remove REQUIRES INCLUDE_MIB2_IF (scalability bug)
12sep03,vvv  updated configlette path
08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
14may03,vvv  removed adv_net.h
26aug02,ham  removed MAXHOSTNAMELEN_CFG
13aug02,ham  change usrNetInit's API for Veloce merge.
19jul02,ann  changed usrNetInitClarinet to usrNetInit
06jun02,rvr  removed the parameter INCLUDE_NETWORK (teamf1)
06jun02,rvr  added component INCLUDE_NETWORK (teamf1)
03may02,mk   renamed usrNetInit to usrNetInitCLarinet
16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
28feb02,ham  reverted 01c
21feb02,ham  moved routing stuff here.
15feb02,ham  moved GTF stuffs to INCLUDE_GTF.
26nov01,ham  wrote.
*/

Component INCLUDE_NET_INIT {
	NAME		network init
	SYNOPSIS	Initialize tables for network stack
	CFG_PARAMS	IP_MAX_UNITS
	REQUIRES	INCLUDE_NETWORK
}

/*
 * In the traditional build, INCLUDE_NETWORK governs whether the
 * network stack is included in the image, while INCLUDE_NET_INIT
 * governs whether the initialization routine usrNetInit() should run.
 * In the project build, INCLUDE_NET_INIT governs both (ugh) and
 * INCLUDE_NETWORK needs to be defined whenever INCLUDE_NET_INIT is,
 * since many BSPs have conditional code depending on INCLUDE_NETWORK.
 */

Parameter IP_MAX_UNITS {
        NAME            IP Driver Control Limit
        SYNOPSIS        Maximum number of interfaces attached to IP layer. \
                        It remains here for backward compatibility since \
                        BSPs still using it. The IPNet stack does not use \
                        this parameter.
        DEFAULT         4
        TYPE            uint
}
