/* 00folder_ipnet_firewall.cdf - IPNet Firewall configuration file */

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
01a,23sep06,kch  Created.
*/

#ifdef _WRS_CONFIG_COMPONENT_IPFIREWALL
Folder FOLDER_FIREWALL {
    NAME        Firewall Components
    SYNOPSIS    Firewall Components
    _CHILDREN   FOLDER_NET_L3_NETWORK
}
#endif
