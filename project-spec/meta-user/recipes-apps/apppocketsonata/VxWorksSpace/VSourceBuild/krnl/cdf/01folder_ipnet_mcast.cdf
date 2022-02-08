/* 01older_ipnet_mcast.cdf - IPNet Multicast Proxy configuration file */

/*
 * Copyright (c) 2006, 2015 Wind River Systems, Inc.
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
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757. 
23sep06,kch  Created.
*/

Folder FOLDER_MCAST_PROXY {
    NAME        Multicast Proxy Components
    SYNOPSIS    Multicast Proxy Components
    CHILDREN    INCLUDE_IPMCP \
                INCLUDE_IPMCP_USE_IGMP \
                INCLUDE_IPMCP_USE_MLD \
                INCLUDE_IPMCAST_PROXY_CMD
}
