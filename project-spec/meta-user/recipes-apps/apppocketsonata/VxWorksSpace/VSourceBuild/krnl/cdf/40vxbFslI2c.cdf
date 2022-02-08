/* 40vxbFslI2c.cdf - Component Definition file for Freescale IIC */

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

Component       DRV_FSL_I2C {
    NAME        Freescale I2C bus controller vxBus
    SYNOPSIS    This component implements a driver for the I2C controller presented on many\
                Freescale PPC/ARM processors. The controller is capable of acting as a master\
                or a slave, and each I2C module instance has two completely independent\
                channels. Some Freescale processors may have only one I2C module, while\
                others (such as the P4080/P5020) have two. The ones with two modules will\
                have four completely independent I2C channels. This I2C controller doesn't\
                support 10 bit addressing, only 7 bit addressing is supported.
    MODULES     vxbFslI2c.o
    LINK_SYMS   vxbOfFslI2cCtlrDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_DRIVERS_BUS
}
