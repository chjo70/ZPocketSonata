/* 00comp_net_routecmd.cdf - Component configuration file */

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
01h,14sep10,h_x CQ:WIND00141200
01g,31jul06,kch  Fixed INCLUDE_ROUTECMD for backward compatibility to
                 support IPNet stack.
01f,03mar05,wap  Add NET_SYSCTL dependency
01e,01mar05,spm  added routing socket dependency
01d,12sep03,vvv  updated configlette path
01c,14may03,ppp  added routeCmd.h
01b,16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01a,02feb02,ham  wrote.
*/

Component INCLUDE_ROUTECMD
	{
	NAME		routec
	SYNOPSIS	routec command
	HDR_FILES       net/utils/routeCmd.h
	CONFIGLETTES	usrNetRouteCmd.c
	INIT_RTN	usrNetRouteCmdInit ();
	CFG_PARAMS      ROUTE_ENTRY_1 \
                        ROUTE_ENTRY_2 \
                        ROUTE_ENTRY_3 \
                        ROUTE_ENTRY_4 \
                        ROUTE_ENTRY_5
	REQUIRES 	INCLUDE_IPWRAP_ROUTECMD
}

Parameter ROUTE_ENTRY_1 {
        NAME            Route Command String 1
        SYNOPSIS        Route Command String 1
        DEFAULT         NULL
        TYPE            string
}

Parameter ROUTE_ENTRY_2 {
        NAME            Route Command String 2
        SYNOPSIS        Route Command String 2
        DEFAULT         NULL
        TYPE            string
}

Parameter ROUTE_ENTRY_3 {
        NAME            Route Command String 3
        SYNOPSIS        Route Command String 3
        DEFAULT         NULL
        TYPE            string
}

Parameter ROUTE_ENTRY_4 {
        NAME            Route Command String 4
        SYNOPSIS        Route Command String 4
        DEFAULT         NULL
        TYPE            string
}

Parameter ROUTE_ENTRY_5 {
        NAME            Route Command String 5
        SYNOPSIS        Route Command String 5
        DEFAULT         NULL
        TYPE            string
}
