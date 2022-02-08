/* vxbFdtI2CLib.h - Fdt bus header file for vxBus I2C bus*/

/*
 * Copyright (c) 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
11may16,sye  added I2C_BUS_SPEED_CFG_NAME to get the default configured I2C BUS
             speed for the controller when I2C_MSG does not set SCL (US76156)
31jul14,y_y  added i2cDevInfo structure. (US40503)
*/

#ifndef __INCvxbFdtI2cLibh
#define __INCvxbFdtI2cLibh

/* includes */

#include <hwif/buslib/vxbFdtLib.h>
#include <hwif/buslib/vxbI2cLib.h>

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

/* defines */

#define I2C_BUS_SPEED_CFG_NAME      "def-bus-frequency"

/* typedef */

typedef struct i2cDevInfo
    {
    struct vxbFdtDev  vxbFdtDev;
    VXB_RESOURCE_LIST vxbResList;
    } I2C_DEV_INFO;

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* __INCvxbFdtI2cLibh */
