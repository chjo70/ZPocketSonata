/* 00folder_net_apps.cdf - Folder configuration file for network applications */

/*
 * Copyright (c) 1999-2010, 2016 Wind River Systems, Inc.
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
04mar16,m_c  Fixed name of FOLDER_SYSTEM_SECURITY and reparented to FOLDER_SECURITY
05jul10,lzq  updated FOLDER_DHCP
25jun10,rjq  added FOLDER_IPNTP
20nov09,rjq  added INCLUDE_IPSNTPS_API
16feb09,mca  added INCLUDE_IPSNTPC_API
26jan07,tkf  INCLUDE_USE_IPCOM_SHELL should not be included by default.
05jan07,kch  Removed INCLUDE_FTP6_SERVER from FOLDER_FTP.
19dec06,mwv  Correct typo (WIND00083105)
24nov06,kch  Corrected default configuration for various folders.
22nov06,kch  Removed INCLUDE_TELNET.
23sep06,kch  Added numerous application folders.
22sep06,tkf  Moved IPNET application components to here.
21sep06,kch  Added FOLDER_DHCP, FOLDER_SNTP and FOLDER_RIP.
01sep06,tlu  remove INCLUDE_RIPNG
24jul06,mwv  remove FOLDER_NFS
09feb06,dlk  Add INCLUDE_DNS_RESOLVER_DEBUG.
23aug05,xli  Added FOLDER_NET_MIP6_APP folder
04may05,kch  Added INCLUDE_MLD6_ROUTER component.
27jan05,vvv  removed IPv4-only FTP server; added missing component
             INCLUDE_FTPD6_GUEST_LOGIN
27aug04,vvv  removed INCLUDE_FTPD_LINGER_SECONDS (not required)
24aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
07jul04,kc   Removed references to INCLUDE_OSPF and INCLUDE_OSPFV3.
28jun04,syy  Add DHCPv6 folder
28jun04,kc   Added INCLUDE_AIP component.
23jun04,kc   Added INCLUDE_OSPF and INCLUDE_OSPFV3 components.
12apr04,vvv  added INCLUDE_PROXY_SERVER (SPR #95263)
09apr04,rp   merged from accordion
31mar04,asr  Added anonymous FTP component
28jan04,zhr  Added TELNET client
10oct03,msc  Added NFS server and client folders
08sep03,htm  Added SNTP client and server components.
15may03,spm  updated to Tornado 2.2 FCS release (added SPR #88460 fix)
19aug02,ham  removed unsupported components
22jul02,ham  added RIP
10jun02,rvr  added INCLUDE_SECURITY
09apr02,qli  include RIPng
14mar02,hgo  added FTPD_SECURITY
25jan02,ger  added PING6
20dec00,ham  re-organized (SPR#63208).
11sep00,fmk  added INCLUDE_LOGIN and INCLUDE_SECURE_SHELL
10aug00,spm  added proxy ARP components
24nov99,spm  added Berkeley Packet Filter component
05may99,cym  re-organized.
*/

Folder FOLDER_AUTOIP {
    NAME        IPv4 autoIP 
    SYNOPSIS    This folder contains components and parameters related to IPv4 autoIP.
    CHILDREN    INCLUDE_IPAIP \
                SELECT_IPAIP_CONFIG
}

Folder FOLDER_PING {
    NAME        PING 
    SYNOPSIS    This folder contains components and parameters related to PING.
    CHILDREN    INCLUDE_IPPING_CMD \
                INCLUDE_IPPING6_CMD \
                INCLUDE_PING \
                INCLUDE_PING6
}

Folder FOLDER_RADVD {
    NAME        IPv6 RADVD 
    SYNOPSIS    This folder contains components and parameters related to IPv6 RADVD.
    CHILDREN    INCLUDE_IPRADVD \
                INCLUDE_IPRADVD_CMD
}

Folder FOLDER_REMOTE_ACCESS {
    NAME        Remote Access 
    SYNOPSIS    This folder contains components and parameters that can \
			be included and modified to configure remote access.
    CHILDREN    INCLUDE_NET_DRV \
                INCLUDE_NET_REM_IO \
                INCLUDE_REMLIB \
                INCLUDE_RLOGIN
    DEFAULTS    INCLUDE_NET_DRV \
                INCLUDE_NET_REM_IO \
                INCLUDE_REMLIB
}

Folder FOLDER_TELNET {
    NAME        Telnet 
    SYNOPSIS    This folder contains components related to Telnet. 
    CHILDREN    INCLUDE_TELNET_CLIENT \
                INCLUDE_IPTELNETS \
                INCLUDE_IPCOM_SHELL_SELECTION
}

Folder FOLDER_SYSTEM_SECURITY {
    NAME        Credentials based login
    SYNOPSIS	This folder contains components related to system security.
    CHILDREN    INCLUDE_SECURITY
    _CHILDREN	FOLDER_SECURITY
}
