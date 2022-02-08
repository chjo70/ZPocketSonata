/* 40vxbMpicIntCtlr.cdf - Component Definition file for MPIC interrupt controller */

/*
 * Copyright (c) 2007-2008, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
01a,23oct13,syt  created
*/

Component       DRV_INTCTLR_FDT_MPIC {
    NAME        MPIC interrupt controller
    SYNOPSIS    This component provides the VxBus driver for MPIC interrupt controller. This driver contains support for\
                non-critical and critical interrupts. It provides support for connecting, enabling\
                and disabling interrupt handlers to specific MPIC vectors.  Two generic MPIC interrupt\
                handlers are provided, one for non-critical interrupts (vxbMpicIntHandler) and the other\
                one for critical interrupts (vxbMpicCrtIntHandler).
    MODULES     vxbMpicIntCtlr.o
    LINK_SYMS   vxbMpicIntCtlrDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_DRIVERS_INTERRUPT
}
