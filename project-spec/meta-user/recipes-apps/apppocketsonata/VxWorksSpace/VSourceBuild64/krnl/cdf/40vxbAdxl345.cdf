/* 40vxbAdxl345.cdf - ADXL345 accelerometer Driver */

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
14aug14,yya  created. (US43304)
*/

Component DRV_ADXL345 {
    NAME            ADXL345 accelerometer
    SYNOPSIS        This component provides the VxBus compliant ADXL345 accelerometer driver. When the probing matches, this \
                    driver installs a device on the IO system, with the name of "/accelerometer". 
    MODULES         vxbAdxl345.o
    LINK_SYMS       vxbAdxl345Drv
    REQUIRES        DRV_BUS_FDT_ROOT    \
                    INCLUDE_GPIO_SYS
    _CHILDREN       FOLDER_DRIVERS_OTHER
}
