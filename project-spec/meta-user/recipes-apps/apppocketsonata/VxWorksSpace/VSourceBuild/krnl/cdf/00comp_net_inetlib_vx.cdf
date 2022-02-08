/* 00comp_net_inetlib.cdf - Component configuration file */

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
01f,28nov06,kch  Added INCLUDE_IPWRAP_INETLIB dependency for backward
                 compatibility.
01e,24aug06,kch  Removed unsupported INCLUDE_INETLIB_SYSCTL component.
01d,03mar05,wap  Deal with NET_SYSCTL dependency
01c,21nov03,ppp  added init routine for inetlib
01b,16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01a,01apr02,ham  ported from TOR3_1-FCS(01c), added inet_ntop/inet_pton.
*/

Component INCLUDE_INETLIB {
        NAME            inetLib
        SYNOPSIS        BSD INET address manipulation routines
        REQUIRES        INCLUDE_IPWRAP_INETLIB
}
