/* 01comp_net_layer2.cdf - Layer 2 components configuration file */

/*
 * Copyright (c) 2004-2006, 2012,2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
27may14,hax  Fix V7NET-384 to change l2config.h path
07feb12,dlk  Fix defect WIND00331675.
06sep06,tkf  Remove INCLUDE_SUBNET_VLAN.
18aug05,kch  Added INCLUDE_L2CONFIG component.
11aug05,kch  Added INCLUDE_MUX_L2 and INCLUDE_SUBNET_VLAN components.
14sep04,kc   Removed configlette property and modified INIT_RTN to 
                 reference to vlanTagLibInit().
21may04,kc   written
*/

Component INCLUDE_MUX_L2 {
    NAME            MUX Layer 2 support
    SYNOPSIS        The INCLUDE_MUX_L2 (MUX Layer 2 support) component pulls in the MUX network interface library for layer 2. Including this component initializes the MUX-L2 infrastructure for virtual local area network (VLAN) support.
    HDR_FILES       muxL2Lib.h \
                    private/fioLibP.h
    CONFIGLETTES    usrNetLayer2Init.c
    INIT_RTN        usrNetMuxL2Init ();
    CFG_PARAMS      MUX_L2_NUM_PORTS_CFG \
                    MUX_L2_MAX_VLANS_CFG
    MODULES         muxL2Lib.o
    REQUIRES        INCLUDE_MUX \
                    INCLUDE_END \
                    INCLUDE_ETHERNET
}

Component INCLUDE_L2CONFIG {
    NAME            l2config
    SYNOPSIS        The INCLUDE_L2CONFIG (l2config) component provides support for the layer 2 configuration utility. Including this component initializes the L2 command-line configuration utility. This component requires the INCLUDE_MUX_L2 component.
    INIT_RTN        l2configInit();
    HDR_FILES       l2config.h
    MODULES         l2config.o
    REQUIRES        INCLUDE_MUX_L2
}

Parameter MUX_L2_NUM_PORTS_CFG {
    NAME            Number of available ports
    SYNOPSIS        This parameter specifies the maximum number of physical ports available to the target.
    DEFAULT         16
    TYPE            uint
}

Parameter MUX_L2_MAX_VLANS_CFG {
    NAME            Maximum number of 802.1Q VLANs
    SYNOPSIS        This parameters specifies the maximum number of 802.1Q virtual LANs supported on the target.
    DEFAULT         16
    TYPE            uint
}
