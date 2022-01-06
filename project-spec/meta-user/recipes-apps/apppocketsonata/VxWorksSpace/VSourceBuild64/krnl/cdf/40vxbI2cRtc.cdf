/* 40vxbI2cRtc.cdf - Component Definition file for I2C RTC */

/*
 * Copyright (c) 2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
01a,23may13,y_y  created
*/

Component   DRV_I2C_RTC {
    NAME        I2C RTC vxBus
    SYNOPSIS    This component provides the I2c RTC vxBus driver. This driver can support all Maxim/Dallas\
                I2C RTC device. Other I2C real-time clock devices with identical\
                registers should also be able to use this driver.
    MODULES     vxbI2cRtc.o
    LINK_SYMS   vxbOfI2cRtcDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_DRIVERS_TIMER
}