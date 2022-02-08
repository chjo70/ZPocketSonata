/* 00folder_network.cdf - Folder configuration file */

/* Copyright 2001-2003, 2005-2006, 2010, 2012, 2014, 2016-2017
 * Wind River Systems, Inc.
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
19sep17,emj  Update to add two folder definition (V7COR-5358)
19jan17,mca  Moved INCLUDE_ETHERNET to FOLDER_NET_END_LIB
13jan17,ljl  FOLDER_LDAPC is unavailable (V7NET-1231)
07dec16,mca  Break hard dependency between END and IPNET (US85582)
10mar16,m_c  Removed KEY_DATABASE and FOLDER_CRYPTO from FOLDE_ENCRYPTION
05may14,rjq  Add FOLDER_NETWORK. (V7NET-365)
05may14,rjq  Decouple COREIP with END. (V7NET-105)
24apr14,h_x  Remove secure NDP and CGA US35689
27feb14,zan  move INCLUDE_APPL_LOG_UTIL out from networking, it is moved to OS
14feb14,zan  decouple cdf dependency, set FOLDER_NET_PPP's upper  node  in 00comp_ipnet_ppp.cdf
11feb14,pad  Removed all elements related to the IPCOM user authentication
             (issue VXW7-1677).
20zan14,zan  remove FOLDER_RPC, which is moved to FOLDER_NFS.
13jan14,h_s  Remove MPLS support. (US19989)
15jan14,jsh  Remove INCLUDE_IPCOM_USE_INET6_ONLY component for vx7
19apr12,fei  Added for TCPAO(RFC5925).
15nov10,sic  Added INCLUDE_IPCOM_USE_LINK_STUB
22sep06,tkf  Add FOLDER_NET_AUTH.
25aug06,kch  Removed unsupported components for IPNet integration.
03mar06,kch  Renamed FOLDER_NET_ALTQ to FOLDER_NET_QOS (SPR#118834).
13feb06,kch  Added FOLDER_NET_ALTQ.
27sep05,vvv  removed FOLDER_NET_MICRO_STACK (SPR #112929)
05aug05,wap  Add microstack folder
08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
15may03,spm  updated to Tornado 2.2 FCS release (added SPR #88460 fix)
19jul02,ham  removed obsolete folders
29feb02,ham  added FOLDER_NET_UTILS
28feb02,ham  removed FOLDER_NET_ROUTING
26nov01,ham  wrote from TOR3_1-FCS (01b)
*/

Folder FOLDER_NETWORK_ADVANCED {
    NAME        Advanced network
	SYNOPSIS	This folder contains advanced network components and parameters.
    CHILDREN	FOLDER_IPCOM_FS \
                FOLDER_NET_CORE \
                FOLDER_NET_PRIVATE \
                FOLDER_SHELLS
    DEFAULTS    FOLDER_IPCOM_FS \
                FOLDER_NET_CORE
    _CHILDREN   FOLDER_NETWORK
}

Folder FOLDER_CAN_NETWORK {
    NAME       CAN Network
    _CHILDREN  FOLDER_NOT_VISIBLE
}

Folder FOLDER_NET_L2_LINK {
    NAME        Layer 2 (link)
    SYNOPSIS    This folder contains components and parameters for layer 2 (link).
    CHILDREN    FOLDER_CAN_NETWORK \
                FOLDER_DOT11_END \
                INCLUDE_ARP_API \
                INCLUDE_BRIDGE \
                INCLUDE_IPCOM_USE_ETHERNET \
                INCLUDE_IPL2TP \
                INCLUDE_IPNET_USE_PPP \
                INCLUDE_IPNET_USE_SOCKDEV \
                INCLUDE_IPNET_USE_VLAN \
                INCLUDE_IPPROXYARP
    DEFAULTS    INCLUDE_IPCOM_USE_ETHERNET
    _CHILDREN   FOLDER_NETWORK
}


Folder FOLDER_NET_L2_LINK_ADVANCED {
    NAME        Advanced link layer
    SYNOPSIS	This folder contains advanced components and parameters for layer 2 (link).
    CHILDREN    INCLUDE_IPNET_LOOPBACK_CONFIG \
                INCLUDE_IPNET_USE_LOOPBACK \
                INCLUDE_IPNET_USE_VLAN_STACKING \
                INCLUDE_L2CONFIG \
                INCLUDE_MUX_L2 \
                INCLUDE_IPCOM_USE_LINK_STUB
    DEFAULTS    INCLUDE_IPNET_USE_LOOPBACK
    _CHILDREN   FOLDER_NET_L2_LINK
}


Folder FOLDER_NET_L3_NETWORK {
    NAME        Layer 3 (network)
    SYNOPSIS    This folder contains components and parameters for layer 3 (network).
    CHILDREN    FOLDER_AUTOCONF_PRIVACY \
                FOLDER_AUTOIP \
                FOLDER_NET_QOS \
                INCLUDE_IPCOM_USE_INET \
                INCLUDE_IPCOM_USE_INET6 \
                INCLUDE_IPNET_USE_NAT \
                SELECT_IPNET_ETHERNET_IFCONFIG
#ifdef _WRS_CONFIG_COMPONENT_NAT
    DEFAULTS    INCLUDE_IPCOM_USE_INET \
                INCLUDE_IPCOM_USE_INET6 \
                INCLUDE_IPNET_USE_NAT \
                SELECT_IPNET_ETHERNET_IFCONFIG
#else
    DEFAULTS    INCLUDE_IPCOM_USE_INET \
                INCLUDE_IPCOM_USE_INET6 \
                SELECT_IPNET_ETHERNET_IFCONFIG
#endif
    _CHILDREN   FOLDER_NETWORK
}

Folder FOLDER_NET_L3_NETWORK_ADVANCED {
    NAME        Advanced network layer
      SYNOPSIS    This folder contains advanced components and parameters for layer 3 (network).
    _CHILDREN   FOLDER_NET_L3_NETWORK
}


Folder FOLDER_NET_L4_TRANSPORT {
    NAME        Layer 4 (transport)
    SYNOPSIS    This folder contains components and parameters for layer 4 (transport).
    CHILDREN    FOLDER_ROHC \
                INCLUDE_IPTCP \
                INCLUDE_IPTCPAO_CMD
    DEFAULTS    INCLUDE_IPTCP
    _CHILDREN   FOLDER_NETWORK
}

Folder FOLDER_NET_L4_TRANSPORT_ADVANCED {
    NAME        Advanced transport layer
    SYNOPSIS	This folder contains advanced components and parameters for layer 4 (transport).
    _CHILDREN   FOLDER_NET_L4_TRANSPORT
}


Folder FOLDER_NET_L5_APPLICATIONS {
    NAME        Layer 5 (applications)
    SYNOPSIS	This folder contains advanced components and parameters for layer 5 (applications).
    CHILDREN    FOLDER_IPCOM_SHELL_CMD \
                FOLDER_IPRADIUS \
                FOLDER_MCAST_PROXY \
                FOLDER_MOBILITY \
                FOLDER_NET_HOST_UTILS \
                FOLDER_NET_SHOW \
                FOLDER_NET_SOCKET \
                FOLDER_NET_SYSCTL \
                FOLDER_PING \
                FOLDER_RADVD \
                FOLDER_REMOTE_ACCESS \
                FOLDER_SNMPD \
                FOLDER_SSL \
                FOLDER_TELNET \
                INCLUDE_IFCONFIG \
                INCLUDE_INETLIB \
                INCLUDE_INTERNET_KEY_EXCHANGE \
                INCLUDE_IPVRRPD \
                INCLUDE_NETSTAT \
                INCLUDE_ROUTECMD \
                INCLUDE_SSH \
                INCLUDE_WRNAD
    DEFAULTS    FOLDER_IPCOM_SHELL_CMD \
                FOLDER_NET_MIB2 \
                FOLDER_NET_SHOW \
                FOLDER_REMOTE_ACCESS \
                FOLDER_TELNET
    _CHILDREN   FOLDER_NETWORK
}

Folder FOLDER_NET_L5_APPLICATIONS_ADVANCED {
    NAME        Advanced applications layer
    SYNOPSIS	This folder contains advanced components and parameters for layer 5 (applications).
    _CHILDREN   FOLDER_NET_L5_APPLICATIONS
}

Folder FOLDER_DHCP {
    NAME        DHCP
    SYNOPSIS    This folder contains components relating to the Dynamic Host Configuration Protocol.
    _CHILDREN   FOLDER_NET_L5_APPLICATIONS
}

Folder FOLDER_CCI {
    NAME       CCI
    _CHILDREN  FOLDER_NOT_VISIBLE
}

Folder FOLDER_ENCRYPTION {
    NAME        Encryption
    SYNOPSIS    This folder contains components and parameters concerning encryption.
    CHILDREN    FOLDER_CCI
    _CHILDREN   FOLDER_NETWORK
}
