/* 40vxbIaPinmux.cdf - Component configuration file */

/* Copyright (c) 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04jul17,hcl  written (US103359)
*/

Component DRV_PINMUX_IA {
    NAME            Intel pinmux support
    SYNOPSIS        Pinmux support for Intel iomux compatible devices
    MODULES         vxbIaPinmux.o
#ifndef _WRS_CONFIG_FDT
    LINK_SYMS       vxbIaAcpiPinmuxDrv
#else
    LINK_SYMS       vxbIaFdtPinmuxDrv
#endif /* _WRS_CONFIG_FDT */
    REQUIRES        DRV_BUS_FDT_ROOT INCLUDE_PINMUX_SYS
    _CHILDREN       FOLDER_DRIVERS
}
