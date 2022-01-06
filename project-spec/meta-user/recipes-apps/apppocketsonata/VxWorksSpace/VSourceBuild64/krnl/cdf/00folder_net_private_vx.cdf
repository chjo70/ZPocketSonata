/* 00folder_net_private.cdf - Folder configuration file */

/*
 * Copyright (c) 2001-2007, 2010, 2014 Wind River Systems, Inc.
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
05may14,rjq  Decouple END with COREIP. (V7NET-105)
27feb14,zan  fix FOLDER_NET_PRIVATE issue-lost CHILDREN key word
20jan14,rjq  move JOBQUEUE to OS service
13jan14,h_s  Remove GTF support. (US19989)
16sep10,xhs  support IPLITE
25aug07,tkf  Add INCLUDE_NET_BOOT_IPV6_CFG as a part of the fix for
             CQ:WIND00102553.
28nov06,kch  Corrected default configurations.
27oct06,kch  Removed unsupported INCLUDE_TUNNEL_MUX_REG.
23sep06,kch  Added INCLUDE_IPNET.
10sep06,tkf  Remove INCLUDE_IF.
07sep06,tkf  Remove INCLUDE_FASTUDP, INCLUDE_FASTUDP6.
06sep06,tkf  Remove INCLUDE_DOMAIN_INIT.
24aug06,kch  Removed unsupported components for IPNet integration.
11aug05,kch  Added ifclone component.
18jul05,dlk  Added INCLUDE_IFMEDIA.
07jul05,dlk  Added INCLUDE_JOB_QUEUE and INCLUDE_JOB_QUEUE_UTIL.
29mar05,vvv  removed INCLUDE_SNPRINTF (SPR #98613)
03mar05,niq  Remove NET_GETOPT
21sep04,dlk  Remove INCLUDE_NET_APPUTIL, superseded by 
		 INCLUDE_APPL_LOG_UTIL.
29jun04,niq  Remove the UNIXLIB component
20feb04,vvv  added INCLUDE_UNIXLIB
08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
20jun03,ann  removed INCLUDE_ZLIB
17jun03,vvv  added INCLUDE_NETMASK_GET (SPR #88786)
27jun02,ppp  merged changes from t3
06may02,ham  back to old netBufLib.
05mar02,ham  removed NETBUFLIB from DEFAULTS
05mar02,ham  added NETBUFLIB
29feb02,ham  added ROUTE
21feb02,ham  moved DAEMON and deleted DAEMON_START
26nov01,ham  revised.
*/

Folder FOLDER_NET_PRIVATE {
    NAME        Network Private Components
    CHILDREN    INCLUDE_IPATTACH         \
                INCLUDE_IP6ATTACH        \
                INCLUDE_NET_BOOT         \
                INCLUDE_NET_BOOT_CONFIG  \
                INCLUDE_NETMASK_GET      \
                INCLUDE_NET_HOST_SETUP   \
                INCLUDE_NET_BOOT_IPV6_CFG \
                INCLUDE_IPLITE           \
                INCLUDE_IPNET
    DEFAULTS    INCLUDE_NET_BOOT         \
                INCLUDE_NETMASK_GET      \
                INCLUDE_NET_HOST_SETUP   \
                INCLUDE_IPNET
}
