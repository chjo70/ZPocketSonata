/* 00comp_ipnet_link_layer.cdf - IPNet Link Layer configuration file */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
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
01e,03sep08,brg  Added INCLUDE_IPCOM_USE_LINK_STUB.
01d,27nov06,kch  Removed duplicate reference to ipppp.o from
                 INCLUDE_IPNET_USE_PPP module list.
01c,22sep06,tkf  Remove INCLUDE_IPMPLS_TUNNEL and INCLUDE_IPNET_USE_VLAN.
01b,18sep06,kch  Renamed INCLUDE_IPPPP to INCLUDE_IPNET_USE_PPP. Also moved
                 INCLUDE_IPPPPOE component to FOLDER_IPNET_PPP.
01a,22may06,kch  created.
*/

Component INCLUDE_IPCOM_USE_ETHERNET {
    NAME            Ethernet Interface support
    SYNOPSIS        Ethernet Interface support.
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    MODULES         iplite_eth.o
    REQUIRES        INCLUDE_IPLITE
#else
    MODULES         ipnet_eth.o
    LINK_SYMS       ipnet_eth_add_hdr
    REQUIRES        INCLUDE_IPNET
#endif
}

Component INCLUDE_IPCOM_USE_LINK_STUB {
    NAME            Link layer stub implementation support.
    SYNOPSIS        Link layer stub implementation support.
    MODULES         ipnet_link_stub.o
    LINK_SYMS       ipnet_link_stub_add_hdr
    REQUIRES        INCLUDE_IPNET
}

Component INCLUDE_IPNET_USE_PPP {
    NAME            PPP Interface support
    SYNOPSIS        PPP Interface support.
    MODULES         ipnet_ppp.o
    LINK_SYMS       ipcom_ppp_ioevent
    REQUIRES        INCLUDE_IPNET
}

Component INCLUDE_IPNET_USE_LOOPBACK {
    NAME            Loopback Interface support
    SYNOPSIS        Loopback Interface support.
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    MODULES         iplite_loopback.o
    REQUIRES        INCLUDE_IPLITE
#else
    MODULES         ipnet_loopback.o
    REQUIRES        INCLUDE_IPNET_LOOPBACK_CONFIG
#endif
}

Component INCLUDE_IPNET_USE_WLAN {
    NAME            Wireless Interface support
    SYNOPSIS        Wireless Interface support.
    MODULES         ipnet_wlan.o
    LINK_SYMS       ipnet_wlan_if_init
    REQUIRES        INCLUDE_IPNET
}

Component INCLUDE_IPNET_USE_SOCKDEV {
    NAME            Socket Interface support
    SYNOPSIS        Socket Interface support.
    MODULES         ipnet_sockdev.o
    LINK_SYMS       ipnet_sockdev_if_init
    REQUIRES        INCLUDE_IPNET
}

