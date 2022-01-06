/* 00comp_net_host_setup.cdf - Component configuration file */

/*
 * Copyright (c) 2001-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 */

/*
modification history
--------------------
01n,22jan07,tkf  Add missing comment terminator characters (CQ:WIND00085885).
01m,26dec06,kch  Removed usrNetHostCfg.c configlette and changed init
                 routine to hostnameSetup().
01l,19oct04,syy  Fix to SPR# 102505
01k,19sep04,spm  cleanup hostname initialization: update virtual stack startup
01j,18nov03,rp   updating header file paths
01i,12sep03,vvv  updated path for configlette and hostSetup.h
01h,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01g,13may03,ppp  removed inclusion of adv_net.h
01f,16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01e,28feb02,ham  changed usrNetHostSetup's parameters.
01d,06dec01,ham  revised from TOR3_1-FCS (01c).
*/

Component INCLUDE_NET_HOST_SETUP {
	NAME		public hostname setup
	SYNOPSIS	assign local hostname to target
	PROTOTYPE	IMPORT STATUS hostnameSetup (char * );
	INIT_RTN	hostnameSetup (pTgtName);
	MODULES		hostSetup.o
	REQUIRES	INCLUDE_NET_BOOT
}
