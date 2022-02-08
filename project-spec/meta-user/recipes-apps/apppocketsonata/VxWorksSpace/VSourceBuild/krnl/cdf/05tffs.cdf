/* 05tffs.cdf - True Flash File System component description */

/*
 * Copyright (c) 1999, 2001-2003, 2005, 2009-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
21nov16,ffu  add LP64 support in TFFS layer (F4496)
30dec15,zly  Fix VXW6-84728: tffs driver performance slow since
                 vxbUsDelay() call the last-ditch delay vxbSwUsDelay()
10feb14,ywu  fix improper use of _WRS_CONFIG_FDT
16jan14,ywu  added INCLUDE_MTD_VXBFLASH to adopt to vxBus gen2
16jan13,x_z  added INCLUDE_TFFS_STUB_VXBFLASH.
28jun12,zly  Fix WIND00341863: adding INCLUDE_TFFS_START_SECTOR_ZERO to 
                 config if compatible with old format.
11aug11,zly  fix WIND00292424:update module list for INCLUDE_TFFS
10jun10,jxu  Removed tffs component from LP64 build.
16jul09,wqi  changed INCLUDE_MTD_WAMDMTD to INCLUDE_MTD_WAMD. (WIND00076463)
13sep05,pcm  changed INCLUDE_TFFS_DOSFS to INCLUDE_TFFS_MOUNT
21jun05,pcm  removed INCLUDE_DOSFS dependency
22oct03,dat  Move folder components here.
20nov03,kk   updated INCLUDE_XXX_SHOW components to depend on
                 INCLUDE_SHOW_ROUTINES 
30jan03,tor  Mount TFFS filesystem at boot time (spr #69254)
26feb02,yp   adding INCLUDE_MTD_CFIAMD component
05dec01,nrv  add INCLUDE_TFFS_SHOW component
13nov01,nrv  re-written to configure MTDs and TL through project
22apr99,pr   added dependency on DOSFS
20apr99,pr   removed reference to ftllite.h msyscard.h ssfdc.h (SPR 26910)
03feb99,yp   written
*/

/*
This file contains descriptions for the TrueFFS Flash file system
components. This file describes the "generic" component which is available
to all CPU architectures and BSPs.  MTD and "Socket" configuration must
be done in sysTffs.c.
*/

/* TFFS is attached in the FOLDER_PERIPHERALS folder */

Folder  FOLDER_TFFS {
        NAME          TrueFFS
        SYNOPSIS      This folder contains components and parameters concerning \
				TrueFFS. TrueFFS is a flash management facility that provides \
				access to flash memory by emulating disk access.
        _CHILDREN     FOLDER_FLASH
        CHILDREN      INCLUDE_TFFS         \
                      INCLUDE_TFFS_MOUNT   \
                      INCLUDE_TFFS_SHOW    \
                      INCLUDE_TFFS_START_SECTOR_ZERO \
                      FOLDER_TFFS_DRIVERS  \
                      FOLDER_TFFS_TL
}


Folder  FOLDER_TFFS_DRIVERS {
        NAME                  TrueFFS drivers
	  SYNOPSIS			This folder contains the different drivers for TrueFFS.
        CHILDREN              INCLUDE_MTD_AMD \
                              INCLUDE_MTD_I28F008 \
                              INCLUDE_MTD_I28F008BAJA \
                              INCLUDE_MTD_I28F016 \
                              INCLUDE_MTD_WAMD \
                              INCLUDE_MTD_CFIAMD \
                              INCLUDE_MTD_VXBFLASH \
                              INCLUDE_MTD_CFISCS
}


Folder  FOLDER_TFFS_TL {
        NAME             TrueFFS translation layer
        SYNOPSIS         This folder contains components and parameters that can \
				be used to configure the translation layer of the TrueFFS.
        CHILDREN         INCLUDE_TL_FTL \
                         INCLUDE_TL_SSFDC
}

Component INCLUDE_TFFS {
        NAME             TrueFFS flash file system
        SYNOPSIS         This component is the core TrueFFS Component. \
				Including this component triggers the correct sequence of events, \
				at boot time, for initializing this product. It also ensures \
				that the socket driver is included in your system. It allows a \
				DOS file system to placed in Flash memory.
        INIT_RTN         tffsDrv ();
        CONFIGLETTES     usrTffs.c
#ifdef _WRS_CONFIG_VXBUS_LEGACY
        BSP_STUBS       sysTffs.c
#endif
        MODULES         backgrnd.o \
                        fatlite.o \
                        flbase.o \
                        flflash.o \
                        flsocket.o \
                        fltl.o \
                        tffsDrv.o \
                        tffsLib.o
        HDR_FILES       tffs/backgrnd.h tffs/dosformt.h tffs/fatlite.h \
                        tffs/flbase.h tffs/flbuffer.h tffs/flcustom.h  \
                        tffs/flflash.h tffs/flsocket.h tffs/flsysfun.h \
                        tffs/flsystem.h tffs/fltl.h tffs/pcic.h \
                        tffs/reedsol.h tffs/stdcomp.h tffs/tffsDrv.h
#if (_VX_CPU_FAMILY==_VX_PPC) && (defined _WRS_CONFIG_SMP)
        REQUIRES        INCLUDE_AUX_CLK
#endif
        _INIT_ORDER     usrIosExtraInit
}

Component INCLUDE_TFFS_START_SECTOR_ZERO {
        NAME                 Starting sector of file system
        SYNOPSIS             This component is compatible with the old format. \
					When included, it make flFileSysSectorStart=0 for dosfs, \
					flFileSysSectorStart=1 for reliance.
        REQUIRES             INCLUDE_TFFS
}

/*
 * NOTE: Show routines can be connected in the show routines folder too.
 * The system allows components to exist in more than one folder, but
 * I'm not sure if that was a design feature, or just luck. 
 */

Component INCLUDE_TFFS_SHOW {
        NAME                 TrueFFS show routines
        SYNOPSIS             Including this component adds two TrueFFS configuration \
					display utilities, tffsShow() and tffsShowAll() for use from the \
					shell. The tffsShow() function prints device information for \
					a specified socket interface. It is particularly useful when trying \
					to determine the number of erase units required to write a boot \
					image (see Reserving a Region in Flash for a Boot Image in the \
					VxWorks 7 File System Programmers guide). The tffsShowAll() \
					function provides the same information for all socket interfaces \
					registered with VxWorks. The tffsShowAll() function can be \
					used from the shell to list the drives in the system. The drives \
					are listed in the order in which they were registered. 
        INCLUDE_WHEN         INCLUDE_TFFS \
                             INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_MTD_AMD {
        NAME            Amdmtd
        SYNOPSIS        AMD, Fujitsu: 29F0{40,80,16} 8-bit devices
        MODULES         amdmtd.o
        HDR_FILES       tffs/flflash.h tffs/backgrnd.h
        REQUIRES        INCLUDE_TFFS \
                        INCLUDE_TL_FTL
}

Component INCLUDE_MTD_CFIAMD {
        NAME            Cfiamdmtd
        SYNOPSIS        CFI driver for AMD Flash Part
        MODULES         cfiamd.o
        HDR_FILES       tffs/flflash.h tffs/backgrnd.h
        REQUIRES        INCLUDE_TFFS \
                        INCLUDE_TL_FTL
}

Component INCLUDE_MTD_I28F008 {
        NAME            i28f008
        SYNOPSIS        Intel 28f008 devices
        MODULES         i28f008.o
        HDR_FILES       tffs/flflash.h tffs/backgrnd.h
        REQUIRES        INCLUDE_TFFS \
                        INCLUDE_TL_FTL
}

Component INCLUDE_MTD_I28F008BAJA {
        NAME            i28f008Baja
        SYNOPSIS        Intel 28f008 on the Heurikon Baja 4000
        MODULES         i28f008Baja.o
        HDR_FILES       tffs/flflash.h tffs/backgrnd.h
        REQUIRES        INCLUDE_TFFS \
                        INCLUDE_TL_FTL
}

Component INCLUDE_MTD_I28F016 {
        NAME            i28f016
        SYNOPSIS        Intel 28f016 devices
        MODULES         i28f016.o
        HDR_FILES       tffs/flflash.h tffs/backgrnd.h
        REQUIRES        INCLUDE_TFFS \
                        INCLUDE_TL_FTL
}

Component INCLUDE_MTD_WAMD {
        NAME            Wamdmtd
        SYNOPSIS        AMD, Fujitsu 29F0{40,80,16} 16-bit devices
        MODULES         wamdmtd.o
        HDR_FILES       tffs/flflash.h tffs/backgrnd.h
        REQUIRES        INCLUDE_TFFS \
                        INCLUDE_TL_FTL
}

Component INCLUDE_MTD_CFISCS {
        NAME            Cfiscs
        SYNOPSIS        CFI/SCS devices
        MODULES         cfiscs.o
        HDR_FILES       tffs/flflash.h tffs/backgrnd.h
        REQUIRES        INCLUDE_TFFS \
                        INCLUDE_TL_FTL
}

#ifndef _WRS_CONFIG_VXBUS_LEGACY
Component INCLUDE_MTD_VXBFLASH {
        NAME            VxBus flash stub driver
        SYNOPSIS        stub for vxbus NOR/SPI flash driver
        MODULES         vxbFlashStub.o
        REQUIRES        INCLUDE_TFFS \
                        INCLUDE_TL_FTL \
                        INCLUDE_MTD
        PROTOTYPE       void vxbFlashStubInit (char *);
        INIT_RTN        vxbFlashStubInit (VXBFLASH_CFG_STR);
        CFG_PARAMS      VXBFLASH_CFG_STR
        _INIT_ORDER     usrIosExtraInit
        INIT_BEFORE     INCLUDE_TFFS

}

Parameter VXBFLASH_CFG_STR {
    NAME            Config string for VxBus driver based TFFS partitions
    SYNOPSIS        Specifies the configuration for tffs partitions, and is \
                    composed of Flash chip strings - \
                        "<Flash chip 0 string>;<Flash chip 1 string>...".\
                    And Flash chip string is composed of following information \
                        "$<Flash instance name>#<index>:\
                         <start address>,<length>,<boot size>,<partition name>".
    TYPE            char *
    DEFAULT         "$norflash0#0:0x0,0x400000,0x0,rfa0"
}
#endif

Component INCLUDE_TL_FTL {
        NAME            Ftllite
        SYNOPSIS        NOR Logic Translation Layer
        MODULES         ftllite.o
        HDR_FILES       tffs/fltl.h
        REQUIRES        INCLUDE_TFFS
}


Component INCLUDE_TL_SSFDC {
        NAME            SSFDC
        SYNOPSIS        Translation Layer Solid State Floppy Disk Card
        MODULES         ssfdc.o
        HDR_FILES       tffs/fltl.h
        REQUIRES        INCLUDE_TFFS
}

Component INCLUDE_TFFS_MOUNT {
        NAME            Mounted TFFS filesystem
        SYNOPSIS        Including this component adds automatic detection (on booting) \
				and mounting of existing formatted TrueFFS drives.
        CFG_PARAMS      TFFS_DRIVE_NUMBER TFFS_REMOVABLE TFFS_MOUNT_POINT
        REQUIRES        INCLUDE_TFFS             \
                        INCLUDE_FS_MONITOR
        _INIT_ORDER     usrIosExtraInit
        INIT_RTN        usrTffsConfig (TFFS_DRIVE_NUMBER, TFFS_REMOVABLE, TFFS_MOUNT_POINT );
}

Parameter TFFS_DRIVE_NUMBER {
        NAME            TFFS drive number
	  SYNOPSIS		Specifies the drive number of the TFFS flash drive. Valid values \
				are 0 through N-1, where N is the number of socket interfaces provided by the BSP.
        TYPE            int
        DEFAULT         0
}

Parameter TFFS_REMOVABLE {
        NAME            Removable flash device
	  SYNOPSIS		When set to FALSE, flash devices are not removable.
        TYPE            bool
        DEFAULT         FALSE
}

Parameter TFFS_MOUNT_POINT {
        NAME            TFFS mount point
	  SYNOPSIS		Specifies the mount point, for example, /tffs0/.
        TYPE            string
        DEFAULT         "/tffs0"
}

Component INCLUDE_TFFS_STUB_VXBFLASH {
        NAME            TFFS stub to VxBus Flash interface
        SYNOPSIS        TFFS stub to vxBus Flash interface
        _CHILDREN       FOLDER_NOT_VISIBLE
}
