/* 40vxbI2cPcfRtc.cdf - Component configuration file */

/*
 * Copyright (c) 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
02jan14,mpc written (US22546)
*/

Component   DRV_I2C_PCFRTC {
    NAME        PCF8564 I2C RTC vxBus
    SYNOPSIS    This component provides the PCF8564 I2C RTC vxBus driver. Other I2C real-time\
                clock devices with identical registers such as PCF8563 should also be able to\
                use this driver. 
    MODULES     vxbI2cPcfRtc.o
    LINK_SYMS   vxbFdtI2cPcfRtcDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_DRIVERS_TIMER
}
