/* vxbI2cLib.h - I2C bus header file for vxBus */

/*
 * Copyright (c) 2013-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05apr16,sye  added vxbI2cDevRead()/vxbI2cDevWrite() (US76156)
07jul15,sye  added I2C_M_READ_LEN for SMBUS block read. (V7PRO-2146)
27may14,y_y  change len in struct i2c_msg from UINT16 to UINT32(V7PRO-774).
22nov13,hll  Remove not necessary definiton of vxbFdtLib.h(WIND00445019).
01nov13,y_y  Fix defect WIND00441308 for I2C.
25aug13,y_y  created
*/

#ifndef __INCvxbI2cLibh
#define __INCvxbI2cLibh

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

/* defines */

#define I2C_READ            0x01
#define I2C_WRITE           0x00

#define FAST_MODE           400000
#define STD_MODE            100000

/* I2C message flags */

#define I2C_M_WR            0x0000      /* write data, from master to slave */
#define I2C_M_RD            0x0001      /* read data, from slave to master */
#define I2C_M_TEN           0x0010      /* ten bit chip address */

/* 
 * The real bytes to read is got from the first byte received, this is
 * needed for SMBUS block read. When this flag is set, the "len" field of the
 * I2C_MSG should be set to: oneByte + extraBytes.
 * oneByte      - the first byte received from the slave and its value equals
 *                to extraBytes.
 * extraBytes   - the extra bytes after the real bytes to be read, example,
 *                when PEC is needed, the extraBytes is 1.
 */

#define I2C_M_READ_LEN      0x0020

/* struct i2c_msg */

typedef struct i2c_msg
    {
    UINT16 addr;    /* Slave address, either seven or ten bits. When this is */
                    /* a ten bit address, I2C_M_TEN must be set in flags */
                    /* field and the driver must support ten bits */
    UINT32 len;     /* number of data bytes in buf being read from or written */
                    /* to the I2C slave device */
    UINT8 * buf;    /* the buffer into which data is read, or from which */
                    /* it's written */
    UINT32 flags;   /* flags for the message */
    UINT32 wrTime;  /* Write Cycle Time if necessary */
    UINT32 scl;     /* SCL Clock Frequency, 0 means use controller's default */
    } I2C_MSG;

IMPORT STATUS vxbI2cDevXfer (VXB_DEV_ID  pDev, I2C_MSG * msgs, int num);
IMPORT STATUS vxbI2cDevRead (VXB_DEV_ID pDev, UINT8 * pAddrBuf, size_t addrLen,
                             UINT8 * pDataBuf, size_t dataLen);
IMPORT STATUS vxbI2cDevWrite (VXB_DEV_ID pDev, UINT8 * pAddrBuf, size_t addrLen,
                              UINT8 * pDataBuf, size_t dataLen);
IMPORT STATUS vxbI2cByNameRead (char * devName, UINT32 unit, UINT8 * pAddrBuf,
                                size_t addrLen, UINT8 * pDataBuf,
                                size_t dataLen);
IMPORT STATUS vxbI2cByNameWrite (char * devName, UINT32 unit, UINT8 * pAddrBuf,
                                 size_t addrLen, UINT8 * pDataBuf,
                                 size_t dataLen);

#include <hwif/methods/vxbI2cMethod.h>

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* __INCvxbI2cLibh */
