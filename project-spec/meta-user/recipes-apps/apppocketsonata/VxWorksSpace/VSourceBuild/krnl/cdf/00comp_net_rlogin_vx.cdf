/* 00comp_net_rlogin.cdf - Component configuration file */

/*
 * Copyright (c) 2002-2006 Wind River Systems, Inc.
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
01h,27may11,rjq  Added new parameter RLOGIN_MAXCLIENTS.
01g,26dec06,kch  Removed usrNetRloginCfg.c configlette and changed init 
                 routine to rlogInit().
01f,14aug06,tkf  Remove dependecy on host library.
01e,12sep03,vvv  updated configlette path
01d,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01c,18jun02,rvr  fixed REQUIRES dependency
01b,18jun02,rvr  port to tor22 (teamf1)
01a,07jun02,ann  ported to clarinet from AE1.1.
*/

Component INCLUDE_RLOGIN {
	NAME		RLOGIN 
	SYNOPSIS	Allows remote access to and from the target
	HDR_FILES	rlogLib.h ptyDrv.h
	INIT_RTN	rlogInit (RLOGIN_MAXCLIENTS); rlogcInit(RLOGIN_CLIENT_NUMBERS);
	CFG_PARAMS	RLOGIN_MAXCLIENTS RLOGIN_CLIENT_NUMBERS
	MODULES		rlogLib.o 
}

Parameter  RLOGIN_MAXCLIENTS {
        NAME            RLOGIN_MAXCLIENTS 
        SYNOPSIS        value specifies default limit for simultaneous sessions
        DEFAULT         2
        TYPE            long
}

Parameter RLOGIN_CLIENT_NUMBERS {
        NAME            rlogin client numbers
        SYNOPSIS        Number of rlogin client to be approved to create 
        TYPE            int
        DEFAULT         1
}
