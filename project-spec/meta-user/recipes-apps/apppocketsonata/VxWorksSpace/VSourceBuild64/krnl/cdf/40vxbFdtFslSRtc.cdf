/* 40vxbFdtFslSRtc.cdf  - Freescale Secure Real Time Clock */

/*
 * Copyright (c) 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
29aug14,yjw  created (US40550)
*/

Component   DRV_SRTC_FDT_FSL {
    NAME        Freescale SRTC VxBus
    SYNOPSIS    This component provides the Freescale SRTC VxBus driver.
    MODULES     vxbFdtFslSRtc.o
    LINK_SYMS   vxbFslSRtcDrv
    _CHILDREN   FOLDER_DRIVERS_TIMER
    REQUIRES    INCLUDE_VXBUS \
                DRV_BUS_FDT_ROOT
}
