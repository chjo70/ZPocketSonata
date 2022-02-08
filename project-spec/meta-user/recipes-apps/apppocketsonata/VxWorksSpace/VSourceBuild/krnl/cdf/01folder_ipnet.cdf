/* 00folder_net_ipnet.cdf - IPNet Top-Level Folder configuration file */

/*
 * Copyright (c) 2006-2007, 2009-2010, 2014-2015 Wind River Systems, Inc.
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
13mar15,zan  Add INCLUDE_NETSMP_CMD to folder FOLDER_IPCOM_SHELL_CMD
18feb14,zan  move INCLUDE_IPNSLOOKUP_CMD to 02comp_ipnet_appl_dnsc.cdf (DNSC layer)
14feb14,zan  decouple cdf dependency, move FOLDER_NET_PPP to 00comp_ipnet_ppp.cdf
11feb14,pad  Removed all elements related to the IPCOM user authentication
             (issue VXW7-1677).
13okt10,sic  Added INCLUDE_IPNET_PCAP_CMD
23sep09,tlu  Added INCLUDE_VCONFIG_CMD
29jul09,ten  Added FOLDER_NET_L2TP.
07sep07,rme  Replaced INCLUDE_IPCOM_FS_SELECTION with SELECT_IPCOM_FS in
             FOLDER_IPCOM_FS 
27jun07,mcarlste Added INCLUDE_IPCOM_USE_MIB2_CMD
27feb07,kch  Added INCLUDE_IPCOM_USE_TIME_CMD to FOLDER_IPCOM_SHELL_CMD
             (WIND00089286).
29jan07,tkf  Remove INCLUDE_IPCOM_SYSVAR_CMD and INCLUDE_IPIFCONFIG_CMD
             from DEFAULTS list.
13dec06,tkf  Add INCLUDE_IPCOM_USE_VXSHELL_CMD (WIND00085813).
06dec06,kch  Moved INCLUDE_IPSYSCTL_CMD from FOLDER_IPCOM_SHELL_CMD to
             FOLDER_NET_SYSCTL.
18nov06,kch Corrected default configurations for FOLDER_IPCOM_SHELL_CMD.
310ct06,kch  Corrected typo for ipecho components.
23sep06,kch Moved application folders to 00folder_net_apps.cdf. Also
            moved various shell commands to different folder. Renamed 
            FOLDER_IPNET_SHELL_CMD to FOLDER_IPCOM_SHELL_CMD and changed
            its parent folder from FOLDER_NETWORK to FOLDER_NET_UTILS.
22sep06,kch Moved component folders out; cleaned up folder names.
21sep06,kch Changed FOLDER_SNTP, FOLDER_DHCP and FOLDER_RIP parent folder
            from FOLDER_NETWORK to FOLDER_NET_APP. Moved mobility folder 
            and firewall components to 01folder_ipnet_advance.cdf. Also
            moved all Qos related folders to 01folder_ipnet_qos.cdf.
18sep06,kch Added FOLDER_IPNET_PPP folder and INCLUDE_IPPPP_CMD. Also 
            renamed INCLUDE_IPPPP in FOLDER_IPNET_LINK_LAYER to 
            INCLUDE_IPNET_USE_PPP.
15sep06,tkf Added IPDHCPC6 and IPDHCPS6 fo FOLDER_IPNET_DHCP.
            Added INCLUDE_IPDHCPS6_CMD.
01sep06,tlu Rename IPRIPNG to RIPNG for the backward compatiblity
28aug06,kch Added INCLUDE_IPSYSCTL_CMD to FOLDER_IPNET_SHELL_CMD. Also
            added FOLDER_IPNET_AUTOIP and INCLUDE_IPPROXYARP to
            FOLDER_IPNET_APPS, as well as FOLDER_IPNET6_AUTOCONF_PRIVACY
            to FOLDER_IPNET_PROTOCOLS.
28aug06,kch Added SELECT_IPCOM_AUTHENTICATION to FOLDER_IPCOM.
12aug06,kch Added INCLUDE_IPNET_USE_VRRPD to FOLDER_IPNET_PROTOCOLS.
10aug06,kch Added new FOLDER_IPNET_DHCP, FOLDER_IPNET_TFTP and 
            FOLDER_IPNET_SNTP to FOLDER_IPNET_APPS.
10aug06,kch Removed INCLUDE_IPCOM_USE_SYSLOGD from FOLDER_IPCOM. Added 
            INCLUDE_IPCOM_SYSLOGD_CMD and INCLUDE_IPCOM_SYSVAR_CMD
            to FOLDER_IPNET_SHELL_CMD.
03aug06,kch Renamed INCLUDE_Xxx_CMD to INCLUDE_IPXxx_CMD for consistency.
28jul06,tlu Added INCLUDE_IPRIPNG_CTRL_CMD
22jul06,kch Added INCLUDE_IPRIP_CTRL_CMD to FOLDER_IPNET_SHELL_CMD.
            Moved INCLUDE_IPRIP and INCLUDE_IPRIPNG from FOLDER_IPNET_APPS 
            to a new FOLDER_IPNET_RIP. Also added SELECT_IPRIP_IFCONFIG 
            and SELECT_IPRIP_STATIC_ROUTES.
18jul06,tlu Added INCLUDE_RIPNG
17jul06,kch Renamed IPNET_ROUTE_CMD to INCLUDE_ROUTE_CMD and 
            IPNET_SCALETEST_CMD to INCLUDE_IPNET_SCALETEST_CMD.
13jul06,dlk Added FOLDER_IPWRAP.
02jul06,kch Assigned INCLUDE_IPNET_CTRL_CMD and INCLUDE_IPNET_CLASSIFIER
            to a parenet folder. Removed INCLUDE_IPNET_DIFFSERV_BA
            component from FOLDER_IPNET_DIFFSERV and added new 
            INCLUDE_IPNET_USE_PACKET_POOL component to FOLDER_IPNET. Also 
            corrected typo in various folders - changed 'DEFAULT' to 
            'DEFAULTS'. 
02jul06,kch Added INCLUDE_IPCOM_USE_SYSLOGD to FOLDER_IPCOM.
22may06,kch created.
*/


Folder FOLDER_AUTOCONF_PRIVACY {
    NAME        IPv6 autoconf privacy extensions
    SYNOPSIS    IPv6 autoconf privacy extensions
    CHILDREN    INCLUDE_IPNET6_AUTOCONF_PRIVACY_EXT \
                SELECT_IPNET6_AUTOCONF_PRIVACY_CONFIG
}


Folder FOLDER_IPCOM_SHELL_CMD {
    NAME        IPCOM Shell Command Components
    SYNOPSIS    IPCOM Shell Command Components
    CHILDREN    INCLUDE_IPARP_CMD \
                INCLUDE_IPCOM_SHELL_CMD \
                INCLUDE_IPCOM_SYSLOGD_CMD \
                INCLUDE_IPCOM_SYSVAR_CMD \
                INCLUDE_IPCOM_USE_TIME_CMD \
                INCLUDE_IPECHO_CLIENT_CMD \
                INCLUDE_IPECHO_SERVER_CMD \
                INCLUDE_IPIFCONFIG_CMD \
                INCLUDE_IPD_CMD \
                INCLUDE_IPNET_CTRL_CMD \
                INCLUDE_IPMEM_DEBUG_CMD \
                INCLUDE_IPNAT_CMD \
                INCLUDE_IPNDP_CMD \
                INCLUDE_IPNETSTAT_CMD \
                INCLUDE_IPROUTE_CMD \
                INCLUDE_IPNET_SCALETEST_CMD \
                INCLUDE_IPSOCKPERF_CMD \
                INCLUDE_IPSOCKTEST_CMD \
                INCLUDE_IPSVCONFIG_CMD \
                INCLUDE_IPTRACE_ROUTE_CMD \
                INCLUDE_IPTCP_TEST_CMD \
                INCLUDE_IPVCONFIG_CMD \
                INCLUDE_IPVERSION_CMD \
                INCLUDE_IPCOM_USE_VXSHELL_CMD \
                INCLUDE_IPCOM_USE_MIB2_CMD \
                INCLUDE_IPCOM_CPU_CMD \
                INCLUDE_IPCOM_SYSLOGD_USE_LOG_FILE   \
                INCLUDE_USER_CMD \
                INCLUDE_IPNET_PCAP_CMD \
                INCLUDE_NETSMP_CMD
}

Folder FOLDER_IPCOM_FS {
    NAME        IPCOM File System Components
    SYNOPSIS    IPCOM File System
    CHILDREN    INCLUDE_IPCOM_USE_RAM_DISK \
                SELECT_IPCOM_FS
}

