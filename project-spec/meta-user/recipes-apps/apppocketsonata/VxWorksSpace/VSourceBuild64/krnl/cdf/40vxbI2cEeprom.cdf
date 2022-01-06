/* 40vxbI2cEeprom.cdf - Component Definition file for I2C EEPROM */

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
23may13,y_y  created
*/

Component       DRV_I2C_EEPROM {
    NAME        I2C EEPROM
    SYNOPSIS    This component provides the VxBus driver for I2C EEPROM. The driver simply supplies two access routines, \
                one for reading EEPROM and the  other one for writing EEPROM. The upper layer \
                software can make use of the two low level APIs to implement such features.
    MODULES     vxbI2cEeprom.o
    LINK_SYMS   vxbOfI2cEepromDrv
    REQUIRES    INCLUDE_VXBUS INCLUDE_EEPROMDRV
    _CHILDREN   FOLDER_DRIVERS_EEPROM
}
