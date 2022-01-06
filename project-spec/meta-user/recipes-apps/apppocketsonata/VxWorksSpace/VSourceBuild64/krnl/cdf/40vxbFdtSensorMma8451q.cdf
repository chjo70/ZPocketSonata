/* 40vxbFdtSensorMma8451q.cdf - MMA8451Q accelerometer Driver */

/*
 * Copyright (c) 2014, 2016-2017 Wind River Systems, Inc.
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
27jan16,sye  removed dependency of DRV_GPIO_FDT_KINETIS (US74710)
18nov14,g_x  created. (US48533)
*/

Component DRV_SENSOR_FDT_MMA8451Q {
    NAME            MMA8451Q accelerometer
    SYNOPSIS        This component provides the MMA8451Q accelerometer driver. When the probing matches, this driver installs a device on the IO system, with \
                    the name of "/accelerometer". 
    MODULES         vxbFdtSensorMma8451q.o
    LINK_SYMS       vxbFdtMma8451qDrv
    REQUIRES        DRV_BUS_FDT_ROOT    \
                    INCLUDE_GPIO_SYS
    _CHILDREN       FOLDER_DRIVERS_OTHER
}
