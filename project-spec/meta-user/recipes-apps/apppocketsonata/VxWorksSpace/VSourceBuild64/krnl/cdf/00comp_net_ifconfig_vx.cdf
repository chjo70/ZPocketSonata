/* 00comp_net_ifconfig.cdf - Component configuration file */

/*
 * Copyright (c) 2002-2005 Wind River Systems, Inc.
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
01k,14sep10,h_x CQ:WIND00141200
01j,31jul06,kch  Fixed INCLUDE_IFCONFIG for backward compatibility to support
                 IPNet stack. Removed unsupported INCLUDE_IFCONFIG_PREFIX.
01i,26aug05,spm  updated sysctl dependencies (SPR #106702)
01h,21jul05,vvv  fixed typos (SPR #108328)
01g,17may05,vvv  added dependency on INCLUDE_ROUTING_SOCKET
01f,03mar05,wap  Add NET_SYSCTL dependency
01e,12sep03,vvv  updated configlette path
01d,14may03,ppp  added ifconfig.h
01c,20feb03,ann  created a separate component for prefix
01b,16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01a,02feb02,ham  wrote.
*/


Component INCLUDE_IFCONFIG
	{
	NAME		ifconfig
	SYNOPSIS	ifconfig
	HDR_FILES       net/utils/ifconfig.h
	CONFIGLETTES	usrNetIfconfig.c
	INIT_RTN	usrNetIfconfigInit ();
	CFG_PARAMS	IFCONFIG_ENTRY_1  \
                        IFCONFIG_ENTRY_2  \
                        IFCONFIG_ENTRY_3  \
                        IFCONFIG_ENTRY_4  \
                        IFCONFIG_ENTRY_5  \
                        IFCONFIG_ENTRY_6  \
                        IFCONFIG_ENTRY_7  \
                        IFCONFIG_ENTRY_8  \
                        IFCONFIG_ENTRY_9  \
                        IFCONFIG_ENTRY_10
	REQUIRES	INCLUDE_IPWRAP_IFCONFIG
}

Parameter IFCONFIG_ENTRY_1 {
        NAME            ifconfig Command String 1
        SYNOPSIS        ifconfig Command String 1
        DEFAULT         NULL
        TYPE            string
}

Parameter IFCONFIG_ENTRY_2 {
        NAME            ifconfig Command String 2
        SYNOPSIS        ifconfig Command String 2
        DEFAULT         NULL
        TYPE            string
}

Parameter IFCONFIG_ENTRY_3 {
        NAME            ifconfig Command String 3
        SYNOPSIS        ifconfig Command String 3
        DEFAULT         NULL
        TYPE            string
}

Parameter IFCONFIG_ENTRY_4 {
        NAME            ifconfig Command String 4
        SYNOPSIS        ifconfig Command String 4
        DEFAULT         NULL
        TYPE            string
}

Parameter IFCONFIG_ENTRY_5 {
        NAME            ifconfig Command String 5
        SYNOPSIS        ifconfig Command String 5
        DEFAULT         NULL
        TYPE            string
}

Parameter IFCONFIG_ENTRY_6 {
        NAME            ifconfig Command String 6
        SYNOPSIS        ifconfig Command String 6
        DEFAULT         NULL
        TYPE            string
}

Parameter IFCONFIG_ENTRY_7 {
        NAME            ifconfig Command String 7
        SYNOPSIS        ifconfig Command String 7
        DEFAULT         NULL
        TYPE            string
}

Parameter IFCONFIG_ENTRY_8 {
        NAME            ifconfig Command String 8
        SYNOPSIS        ifconfig Command String 8
        DEFAULT         NULL
        TYPE            string
}

Parameter IFCONFIG_ENTRY_9 {
        NAME            ifconfig Command String 9
        SYNOPSIS        ifconfig Command String 9
        DEFAULT         NULL
        TYPE            string
}

Parameter IFCONFIG_ENTRY_10 {
        NAME            ifconfig Command String 10
        SYNOPSIS        ifconfig Command String 10
        DEFAULT         NULL
        TYPE            string
}
