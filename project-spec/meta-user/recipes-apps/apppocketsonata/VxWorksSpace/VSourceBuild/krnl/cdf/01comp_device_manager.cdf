/* 01comp_device_manager.cdf - Device Manager component */

/*
 * Copyright 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
24jan14,ghs  create
*/

/*
DESCRIPTION
This file contains the description for the Device Manager component.
*/

Component INCLUDE_DEVICE_MANAGER
    {
    NAME                Device Manager
    SYNOPSIS            Device Manager
    MODULES             device.o
    HDR_FILES           drv/manager/device.h
    INIT_RTN            devInit (DEVICE_MANAGER_MAX_NUM_DEVICES);
    CFG_PARAMS          DEVICE_MANAGER_MAX_NUM_DEVICES
    INCLUDE_WHEN        INCLUDE_XBD
    _CHILDREN           FOLDER_STORAGE
    }

Parameter DEVICE_MANAGER_MAX_NUM_DEVICES 
    {
    NAME                max # of devices
    TYPE                uint16_t
    DEFAULT             255
    }

