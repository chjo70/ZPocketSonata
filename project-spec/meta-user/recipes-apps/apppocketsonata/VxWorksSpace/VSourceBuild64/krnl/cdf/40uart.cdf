/* 40uart.cdf - Component configuration file */

/*
 * Copyright (c) 2013-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
07may15,jmz  US55875 - Update DRV_SIO_IA_NS16550 component for FDT based driver
26feb15,ten  US50798 - Choose SIO interrupt trigger type and level
18jun14,mpc  added Kinetis SIO support (US40535)
06may14,jmz  US35979 - Add configlette support to DRV_SIO_IA_NS16550
29apr14,j_l  US37556 - Convert *MPT* names to *IADT*
24mar14,l_z  add PCI ns16550 support. (US35018)
04mar14,scm  TA42438 - add 16550 support for IA
30dec13,cww  removed dependency on console
04jul13,l_z  created from 02b 40uart.cdf
*/

Component DRV_SIO_FDT_NS16550 {
    NAME            UART support for ns16550-compatible FDT devices
    SYNOPSIS        This component enables ns16550 SIO support for flat device tree devices.
    MODULES         vxbNs16550Sio.o vxbFdtNs16550Sio.o
    LINK_SYMS       vxbFdtNs16550Drv
    REQUIRES        DRV_BUS_FDT_ROOT  \
                    INCLUDE_ISR_DEFER \
                    INCLUDE_SIO
    _CHILDREN       FOLDER_DRIVERS_SERIAL
}

Component DRV_SIO_PCI_NS16550 {
    NAME            UART support for ns16550-compatible PCI devices
    SYNOPSIS        This component enables ns16550 SIO support for PCI device via modules that provide the PCI \
                    adapt interfaces and the non-FDT adapter interface for the vxbNs16550 driver.
    MODULES         vxbNs16550Sio.o vxbPciNs16550Sio.o
    LINK_SYMS       vxbPciNs16550Drv
    REQUIRES        INCLUDE_ISR_DEFER \
                    INCLUDE_SIO
    _CHILDREN       FOLDER_DRIVERS_SERIAL
}

Component DRV_SIO_FDT_KINETIS {
    NAME            UART support for Freescale Kinetis FDT devices
    SYNOPSIS        This component provides Freescale Kinetis SIO support for flat device tree devices. 
    MODULES         vxbFdtKinetisSio.o
    LINK_SYMS       vxbFdtKinetisSioDrv
    REQUIRES        INCLUDE_ISR_DEFER \
                    DRV_BUS_FDT_ROOT  \
                    INCLUDE_SIO
    _CHILDREN       FOLDER_DRIVERS_SERIAL
}

Component DRV_SIO_IA_NS16550 {
    NAME            UART support for ns16550-compatible devices
    SYNOPSIS        This component provides ns16550 SIO support.
    MODULES         vxbNs16550Sio.o vxbIaNs16550Sio.o
#ifndef _WRS_CONFIG_FDT
    LINK_SYMS       iaNs16550DrvRegistration
    CONFIGLETTES    usrIaNs16550Sio.c
    PROTOTYPE       void usrIaNs16550Init \
                    ( \
                    int index, \
                    void * baseAddr, \
                    UINT16 regDelta, \
                    UINT32 intNum, \
                    UINT32 intLevel, \
                    UINT16 fifoLen, \
                    unsigned long clkFreq, \
                    unsigned long baudRate, \
                    UINT32 trigger, \
                    UINT32 polarity \
                    );
    _INIT_ORDER     usrRoot
    INIT_BEFORE     INCLUDE_VXBUS
#else
    LINK_SYMS       iaFdtNs16550DrvRegistration
#endif /* _WRS_CONFIG_FDT */
    REQUIRES        INCLUDE_ISR_DEFER \
                    INCLUDE_SIO
    _CHILDREN       FOLDER_DRIVERS_SERIAL
}

