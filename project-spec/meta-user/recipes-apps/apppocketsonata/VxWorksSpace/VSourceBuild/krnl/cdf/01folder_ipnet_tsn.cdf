/* 01folder_ipnet_tsn.cdf - IPNet tsn configuration file */

/*
 * Copyright (c) 2017 Wind River Systems, Inc.
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
09feb17,xxy  Created.
*/

#ifdef _WRS_CONFIG_IPNET_TSN
Folder FOLDER_TSN {
NAME      TSN    
SYNOPSIS  Time Sensitive Networking
_CHILDREN FOLDER_NET_L2_LINK
}
#endif

