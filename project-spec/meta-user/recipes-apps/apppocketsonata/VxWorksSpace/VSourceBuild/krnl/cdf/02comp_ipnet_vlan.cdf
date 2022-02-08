/* 02comp_ipnet_vlan.cdf - IPNet VLAN configuration file */

/*
 * Copyright (c) 2006-2007 Wind River Systems, Inc.
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
01c,24jun09,tlu  Add new VLAN stacking component and S-VLAN tag protocol 
	         ID as configuration parameter
01b,08jan07,kch  Removed duplicate ipnet_config.c configlette property.
01a,23sep06,kch  created.
*/

Component INCLUDE_IPNET_USE_VLAN {
    NAME            VLAN Pseudo Interface support
    SYNOPSIS        VLAN Pseudo Interface support.
    MODULES         ipnet_vlan.o
    LINK_SYMS       ipnet_vlan_if_init
    REQUIRES        INCLUDE_IPCOM_USE_ETHERNET
}


Component INCLUDE_IPNET_USE_VLAN_STACKING {
    NAME            VLAN stacking support
    SYNOPSIS        This component provides support for VLAN stacking. It requires the component INCLUDE_IPCOM_USE_ETHERNET.
    MODULES         ipnet_svlan.o
    REQUIRES        INCLUDE_IPCOM_USE_ETHERNET
    CFG_PARAMS      IPNET_VLAN_S_VLAN_TPID
}


/******************** Configuration Parameters *****************************/
/* INCLUDE_IPNET_USE_VLAN_STACKING configuration parameters */

Parameter IPNET_VLAN_S_VLAN_TPID {
    NAME        Service VLAN tag protocol ID 
    SYNOPSIS    Identifies the service VLAN tag, refer to IEEE802.1ad. \
                The default value is 0x88a8 as defined in IEEE802.1ad. \
		The S-VLAN TPID must be a difference value than the C-VLAN \
		TPID value 0x8100.
    TYPE        char *
    DEFAULT     "34984"
}
