/* 40vxbI2cGpioFdtMax731x.cdf - Component Definition file for I2C GPIO */

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
05aug14,sye  Created. (US42489)
*/

Component       DRV_I2C_GPIO_FDT_MAX_731X {
    NAME        MAX731X I2c GPIO 
    SYNOPSIS    This component provides the VxBus driver for Maxim I2C GPIO controller MAX731X.
    MODULES     vxbI2cGpioFdtMax731x.o
    LINK_SYMS   vxbI2cGpioFdtMax731xDrv
    REQUIRES    INCLUDE_VXBUS    \
                INCLUDE_GPIO_SYS \
                DRV_BUS_FDT_ROOT
    _CHILDREN   FOLDER_DRIVERS_GPIO
}
