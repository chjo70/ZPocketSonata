/* 40vxbFdtZynqmpRtc.cdf  - Xilinx Zynqmp Real Time Clock */

/*
 * Copyright (c) 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
29aug17,mpc  created (F9286)
*/

Component   DRV_RTC_FDT_ZYNQMP {
    NAME        Xilinx Zynqmp RTC device driver
    SYNOPSIS    This component provides the Xilinx Zynqmp RTC VxBus device driver.
    MODULES     vxbFdtZynqmpRtc.o
    LINK_SYMS   vxbZynqmpRtcDrv
    _CHILDREN   FOLDER_DRIVERS_TIMER
    REQUIRES    INCLUDE_VXBUS \
                DRV_BUS_FDT_ROOT
}
