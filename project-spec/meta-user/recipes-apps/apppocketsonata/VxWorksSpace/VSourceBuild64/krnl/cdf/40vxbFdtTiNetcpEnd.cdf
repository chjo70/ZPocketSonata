/* 40vxbFdtTiNetcpEnd.cdf - TI NetCP Network Driver */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
DESCRIPTION
There is two modes of ti netcp network driver: switch mode and independent
port mode, also there are two different drivers for each mode.

vxbFdtTiNetcpEndSw.c - switch mode
vxbFdtTiNetcpEndIp.c - independent port mode

DRV_END_TI_NETCP is used for switch mode, DRV_END_TI_NETCP_IP is used for
independent port mode.
*/

/*
modification history
--------------------
04jun15,m_w  added TI_NETCP_END_SELECTION/DRV_END_TI_NETCP_IP. (US60415)
25feb14,y_c  created. (US34091)
*/

Component DRV_END_TI_NETCP {
        NAME            TI NetCP network driver in switch mode
        SYNOPSIS        Select this component to use the TI NetCP \
                        network driver in switch mode.
        MODULES         vxbFdtTiNetcpEndSw.o
        LINK_SYMS       tiNetcpDrvSw
        REQUIRES        INCLUDE_END
}

Component DRV_END_TI_NETCP_IP {
        NAME            TI NetCP network driver in independent mode
        SYNOPSIS        Select this component to use the TI NetCP \
                        network driver in independent port mode.
        MODULES         vxbFdtTiNetcpEndIp.o
        LINK_SYMS       tiNetcpDrvIp
        REQUIRES        INCLUDE_END
}

Selection TI_NETCP_END_SELECTION {
        NAME            NetCP selection
        SYNOPSIS        Select the mode of the NetCP network interface:\
                        switch mode or independent port mode.
        COUNT           1-1
        CHILDREN        DRV_END_TI_NETCP       \
                        DRV_END_TI_NETCP_IP
        _CHILDREN       FOLDER_NET_END_DRV
        DEFAULTS        DRV_END_TI_NETCP
}

