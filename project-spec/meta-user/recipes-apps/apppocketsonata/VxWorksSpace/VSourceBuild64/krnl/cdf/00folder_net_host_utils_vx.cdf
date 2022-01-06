/* 00folder_net_host_utils.cdf - Folder configuration file for host utils */

/*
 * Copyright (c) 2003-2006 Wind River Systems, Inc.
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
01c,28nov06,kch  Corrected default configurations.
01b,31jul06      Add INCLUDE_GETSERVBYPORT.
01a,15jan03      written.
*/

Folder FOLDER_NET_HOST_UTILS {
    NAME        Network Host Utilities
    SYNOPSIS    Host Utilities for Applications
    CHILDREN    INCLUDE_HOST_TBL \
                INCLUDE_GETADDRINFO \
                INCLUDE_GETNAMEINFO \
                INCLUDE_GETSERVBYNAME \
                INCLUDE_GETSERVBYPORT
    DEFAULTS    INCLUDE_HOST_TBL
}
