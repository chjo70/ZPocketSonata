/* 40vxbFdtFslVybridADC.cdf - Component configuration file */

/* Copyright (c) 2014, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
22jan16,sye  moved to vxbus_drv to support i.MX6 SoloX (US74226)
04aug14,yya  created. (US43305)
*/

Component DRV_FSL_VYBRID_ADC {
    NAME            Freescale Vybrid ADC
    SYNOPSIS        This component provides the Freescale Vybrid Analog to Digital Converter (ADC) driver. When the probing matches, this driver \
                    installs a device on the IO system, with the name of "/adcX", where \
                    X is the zero-based unit index of the device.
    MODULES         vxbFdtFslVybridADC.o
    LINK_SYMS       vxbFdtFslVybridADCDrv
    REQUIRES        DRV_BUS_FDT_ROOT
    _CHILDREN       FOLDER_DRIVERS_ADC
}
