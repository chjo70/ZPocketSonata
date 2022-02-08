/* 00comp_net_tftp_client.cdf - Component configuration file */

/*
 * Copyright (c) 1999-2006, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02feb17,jbm  Editing name and synopsis
02oct06,tkf  Remove unnecessary requirement.
22sep06,tkf  Cleaned up component names.
29aug06,kch  Replaced INCLUDE_BSD_SOCKET dependency with INCLUDE_IPCOM
             and INCLUDE_IPNET_USE_SOCK_COMPAT.
22apr02,rvr  added LINK_SYMS attribute (teamf1)
16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
04jun00,pad  Addition of PREF_DOMAIN attribute
14jan00,ham  added missing stuffs.
05may99,cym  re-organized.
*/

Component INCLUDE_TFTP_CLIENT {
    NAME        TFTP client APIs
    SYNOPSIS    This component includes the Trivial File Transfer Protocol (TFTP) \
                client routines.
    MODULES     tftpLib.o 
    LINK_SYMS   tftpCopy
}
