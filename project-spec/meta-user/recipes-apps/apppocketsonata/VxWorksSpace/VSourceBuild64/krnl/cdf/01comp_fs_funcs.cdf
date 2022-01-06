/* 01comp_fs_funcs.cdf - Kernel FS components */

/*
 * Copyright (c) 2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
27jul17,ghs  add file system information show routines (F9150)
19nov15,ffu  fix V7STO-370,modify the synopsis of INCLUDE_FS_DEVICE_MOUNT_VALIDATE
22may15,jdw  Created
*/

/*
DESCRIPTION

This file contains descriptions for VxWorks file system components used
to rename file system IOS devices and validate device availability at boot time.

*/

Folder FOLDER_FILESYSTEM_UTILS {
    NAME            File System Utility functions
    SYNOPSIS        File System Utility functions
    _CHILDREN	    FOLDER_FILESYSTEM
    CHILDREN        INCLUDE_FS_DEVICE_MOUNT_VALIDATE \
                    INCLUDE_FS_DEVICE_RENAME \
                    INCLUDE_FSINFO_SHOW          
}

Component INCLUDE_FS_DEVICE_MOUNT_VALIDATE {
	NAME		File system IOS device mounting validation
        SYNOPSIS        Validate the specified block device has been mounted, waiting for up to N seconds
	HDR_FILES	fsUtilityFuncs.h
        CFG_PARAMS      FS_ORIGIN_DEVICE_NAME \
                        FS_MOUNT_VALIDATE_TIMEOUT
        _INIT_ORDER     usrIosExtraInit
	REQUIRES        INCLUDE_IO_SYSTEM
	INIT_RTN        fsDeviceValidateMount (FS_ORIGIN_DEVICE_NAME, FS_MOUNT_VALIDATE_TIMEOUT);
        INIT_AFTER      INCLUDE_VRFS
        INIT_BEFORE     INCLUDE_BOOT_LINE_INIT
}

Component INCLUDE_FS_DEVICE_RENAME {
	NAME		File system IOS device renaming
        SYNOPSIS        Change the default name of a VxWorks FS device at boot time
	HDR_FILES	fsUtilityFuncs.h
        CFG_PARAMS      FS_ORIGIN_DEVICE_NAME \
                        FS_TARGET_DEVICE_NAME \
			FS_MOUNT_VALIDATE_TIMEOUT
	INIT_RTN        fsDeviceRename (FS_ORIGIN_DEVICE_NAME, FS_TARGET_DEVICE_NAME, FS_MOUNT_VALIDATE_TIMEOUT);
	REQUIRES        INCLUDE_FS_DEVICE_MOUNT_VALIDATE \
                        INCLUDE_XBD
        _INIT_ORDER     usrIosExtraInit
        INIT_AFTER      INCLUDE_FS_DEVICE_MOUNT_VALIDATE
        INIT_BEFORE     INCLUDE_BOOT_LINE_INIT
}

Parameter FS_MOUNT_VALIDATE_TIMEOUT
{
	NAME		Mounting validation timeout
	SYNOPSIS	Sets the maximum time to wait (in seconds) for a file system IOS device to be mounted. \
			A value of 0 means no waiting.
	TYPE		uint
	DEFAULT		5
}

Parameter FS_ORIGIN_DEVICE_NAME {
	NAME		VxWorks file system IOS device name
	SYNOPSIS	Sets the default VxWorks file system IOS device name.
	TYPE		string
	DEFAULT		""
}

Parameter FS_TARGET_DEVICE_NAME {
	NAME		File system IOS device name used for renamed devices
	SYNOPSIS	Sets the default file system IOS device name used for renamed devices.
	TYPE		string
	DEFAULT		""
}

Component INCLUDE_FSINFO_SHOW {
    NAME        File system information show routine
    SYNOPSIS    Show file system name and basic information of device
    REQUIRES    INCLUDE_IO_SYSTEM \
                INCLUDE_POSIX_DIRLIB
    LINK_SYMS   deviceFsInfoShow
}
