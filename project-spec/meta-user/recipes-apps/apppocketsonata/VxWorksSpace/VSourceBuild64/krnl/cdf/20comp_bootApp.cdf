/* 20comp_bootApp.cdf - Boot Application components */

/*
 * Copyright 2005-2015, 2018 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08mar18,zl   made start delay configurable (V7PRO-4367). Removed obsolete
             INCLUDE_BOOT_DELAYED_INIT.
10mar15,yya  Add NVRAM support (US55212)
07jul14,p_x  Add parameters BOOT_FS_DEV_MOUNT_CHECK BOOT_FS_CHECK_ATTEMPTS
             BOOT_FS_ATTEMPT_DELAY and do bootFsDevCheckConfig() (VXW6-25020)
14feb14,to   remove INCLUDE_BOOT_FD_LOADER component (VXW7-1860)
05nov13,j_x  replace USB GEN1 bulk class driver with GEN2 (WIND00442106).
15oct13,x_z  added MODULES attribute for some components.
16sep13,rlp  Removed BOOT_TSFS_LOADER and TSFS_BOOT_VIO_CONSOLE components.
25jul13,cww  added INCLUDE_BANNER component
09may13,d_l  fix a migration issue by adding a hidden component
             INCLUDE_BOOT_VXBUS. (WIND00416816)
09apr13,x_s  Change INCLUDE_USR_MACADDR component to be invisible.
08jan13,wyt  Add INCLUDE_USR_MACADDR component
22aug12,mpc  Remove MODULES field from INCLUDE_BOOT_USB_FS_LOADER.
             (WIND00360066)
26apr12,mpc  Remove fix for INCLUDE_BOOT_DELAYED_INIT (WIND00347629)
11apr12,rbc  WIND00344190 - Fix build failure with
             INCLUDE_BOOT_USB_FS_LOADER
10jan12,pgh  Fix INCLUDE_BOOT_DELAYED_INIT component
04jan12,d_c  Defect WIND00202474 Fix WIND00318218: Remove
             INCLUDE_BOOT_VXBUS component.
17aug11,rlg  fix for wind00290585 -need INIT_BEFORE and INIT_AFTER
             due to initialization order problem. Only the INIT_AFTER
             needed to be added, the INIT_BEFORE was already in place.
11nov10,pgh  Fixing USB components
27jul10,pgh  Add ELF memory mapping component for bootroms.
11dec09,pgh  Remove LOCAL_MEM_LOCAL_ADRS from bootAppInit().
11jun09,pgh  Add INCLUDE_TSFS_BOOT_VIO_CONSOLE support.
04jun09,pgh  Exclude INCLUDE_NET_SYM_TBL from the boot loader application.
27apr09,pgh  Fix the INCLUDE_BOOT_VXBUS definition.
05feb09,pgh  Remove unused boot components
23oct08,pgh  Add parameters to USB init routine.
26aug08,jpb  Removed LAYER from components.
07may08,pgh  Break default MAC into three bytes.
07jul08,pgh  Fix component name for timer system.
05oct07,mze  fix for 104829
11sep07,pgh  Add DHCP boot support to bootapp.
02aug07,h_k  made SCSI components invisible in SMP
09mar07,mdo  Fix spelling of SYNOPSIS for vxtest V2
12mar07,jmt  Defect 90387- Allow for default Filesystem components
05mar07,jmt  Fix typo in INCLUDE_BOOT_EDR_SUPPORT component
28feb07,jmt  Add INCLUDE_BOOT_EDR_SUPPORT component
24feb07,jmt  Fix problem with ATA support in bootrom
22feb07,jmt  Defect 88750 - Fix problem with network boot device CDF
             defines
06feb07,jmt  Modify components due to component optimizations.
17jan07,jmt  Add USB bootApp components
28nov06,h_k  added INCLUDE_BOOT_ETH_ADR_SET. (CQ:81271)
14nov06,jmt  Defect 81462: Need to disable MMU before booting new image 
             for some BSPs
24oct06,jmt  Add INCLUDE_BOOT_ETH_MAC_HANDLER
08sep06,jmt  Add Test functions component
07aug06,jmt  Updated to fix Coldfire INCLUDE_ELF problem.
             Added SELECT_BOOT_NET_DEVICES to pull in BSP drivers.
             This define needs to be modified for each BSP.
27jul05,jmt  Updated to fix PowerPC compile problem.
07jul05,jmt  Written from version 01a,31jan05,bpn of 01shell_commands.cdf.


DESCRIPTION

This file contains the definition for the components for the Boot Application.

*/

/* Folders */

Folder          FOLDER_BOOT_APP {
    NAME        Boot application 
    SYNOPSIS    This folder contains the components needed to create bootrom images.
    _CHILDREN   FOLDER_TOOLS
}

Folder          FOLDER_BOOT_APP_NETWORK {
    NAME        boot application network 
    SYNOPSIS    The components to boot images over the network
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
}

Folder          FOLDER_BOOT_APP_FILESYSTEMS {
    NAME        boot application filesystem 
    SYNOPSIS    The components to boot images from a filesystem
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
}

Folder          FOLDER_BOOT_APP_SHELL {
    NAME        Boot application shell 
    SYNOPSIS    The components to allow user I/O
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
}

/*
 * Boot App Basic Components
 */

Component       INCLUDE_BOOT_APP {
    NAME        Boot Application
    SYNOPSIS    Base component for creating boot applications
    PROTOTYPE   IMPORT void bootApp ();
    INIT_RTN    bootApp();
    MODULES     bootApp.o
    INIT_BEFORE INCLUDE_USER_APPL
    REQUIRES    INCLUDE_BOOT_LINE_INIT \
                INCLUDE_MEM_MGR_BASIC \
                SELECT_BOOT_NET_DEVICES \
                SELECT_BOOT_FS_DEVICES
    EXCLUDES    INCLUDE_NET_SYM_TBL
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
#ifdef _WRS_CONFIG_FDT
    CONFIGLETTES bootAppNvRam.c
#endif
}

Component       INCLUDE_BOOT_EXC_HANDLER {
    NAME        Boot Application Exception Handler
    SYNOPSIS    Exception Handling for Boot Application
    PROTOTYPE   IMPORT STATUS bootAppExcInit ();
    INIT_RTN    bootAppExcInit ();
    MODULES     bootAppExc.o
    REQUIRES    INCLUDE_TASK_SHOW
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
}

Component       INCLUDE_BOOT_RAM_IMAGE {
    NAME        Boot Application RAM Image
    SYNOPSIS    Use RAM link address for Boot Application
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
}

Component       INCLUDE_BOOT_TEST_FUNCS {
    NAME        Boot application test functions
    SYNOPSIS    Include test functions for Boot Application
    MODULES     bootAppTestFuncs.o
    PROTOTYPE   IMPORT STATUS bootAppTestFuncsInit ( BOOL disableAutoBoot);
    INIT_RTN    bootAppTestFuncsInit ( BOOT_TEST_DISABLE_AUTOBOOT );
    CFG_PARAMS  BOOT_TEST_DISABLE_AUTOBOOT
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
}

/* NOTE: The following default for BOOT_TEST_DISABLE_AUTOBOOT is coupled
 * to the INCLUDE_BOOT_TEST_FUNCS.  It is used to disable autoboot when
 * this component is included.
 */
Parameter	BOOT_TEST_DISABLE_AUTOBOOT {
    	NAME        Disable autoboot 
    	SYNOPSIS    This parameter disables autoboot when set to true. 
	DEFAULT		TRUE
}


/*
 * Boot App Initialization Components
 */

#ifdef _WRS_CONFIG_FDT

Component       INCLUDE_BOOTAPP_NVRAM_SUPPORT {
    NAME        Enable NVRAM support in BootApp
    SYNOPSIS    If this component is included, the BootApp's Bootline is loaded \
                from NVRAM, and is saved to NVRAM after modification.
    REQUIRES    INCLUDE_BOOT_APP
    PROTOTYPE   IMPORT void bootAppNvRamSupportInit(STATUS (*set)(char *, int, int), STATUS (*get)(char *, int, int));
    INIT_RTN    bootAppNvRamSupportInit(NULL, NULL);
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
}

Component       INCLUDE_BOOTAPP_GENERIC_NVRAM {
    NAME        Generic NVRAM implementation on top of IO file
    SYNOPSIS    generic NVRAM implementation on top of IO file.
    REQUIRES    INCLUDE_BOOT_APP
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
    CFG_PARAMS  BOOTAPP_GENERIC_NVRAM_NAME   \
                BOOTAPP_GENERIC_NVRAM_OFFSET \
                BOOTAPP_GENERIC_NVRAM_SIZE
}

Parameter BOOTAPP_GENERIC_NVRAM_NAME 
    {
    NAME        File name used as NVRAM
    SYNOPSIS    file name used as NVRAM
    TYPE        string
    DEFAULT     "/null"
    }

Parameter BOOTAPP_GENERIC_NVRAM_OFFSET 
    {
    NAME        Offset in file to the start of NVRAM space
    SYNOPSIS    Offset in file to the start of NVRAM space (bytes)
    DEFAULT     0x0
    }

Parameter BOOTAPP_GENERIC_NVRAM_SIZE 
    {
    NAME        NVRAM size
    SYNOPSIS    NVRAM size (bytes)
    DEFAULT     0x100
    }

#endif

Component       INCLUDE_BOOT_INIT {
    NAME        Boot app initialization
    SYNOPSIS    Initialize boot devices on bootrom initialization
    PROTOTYPE   IMPORT STATUS bootAppInit (BOOL disableMmuBeforeEntry, \
                                           UINT startDelayTime);
    INIT_RTN    bootAppInit (BOOT_DISABLE_MMU_BEFORE_ENTRY, \
                             BOOT_START_DELAY);
    REQUIRES    INCLUDE_BOOT_APP
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
    CFG_PARAMS  BOOT_DISABLE_MMU_BEFORE_ENTRY \
                BOOT_START_DELAY
}

/* NOTE: The following default for BOOT_DISABLE_MMU_BEFORE_ENTRY is coupled 
 * to the INCLUDE_BOOT_INIT.  It is used to disable the MMU prior to jumping
 * to the entry point for a downloaded module.
 * A BSP can override this value in its config.h or CDF file.
 */
Parameter	BOOT_DISABLE_MMU_BEFORE_ENTRY {
    NAME	MMU disable
    SYNOPSIS 	Disables the MMU prior to jumping to the entry point of a boot \
		application image. The default is TRUE.
    DEFAULT	TRUE
}

Parameter	BOOT_START_DELAY {
    NAME        Time before starting loaded OS
    SYNOPSIS    Delay time after the executable image is loaded, and before \
                jumping to the entry point. This can be useful to ensure \
                that the loader completes deferred work (for example in the \
                network in stack). Time is expressed in milliseconds. The \
                default is one second.
    DEFAULT     1000
}

Component       INCLUDE_BOOT_MMU_BASIC {
    NAME        Enable INCLUDE_MMU_BASIC for boot app 
    SYNOPSIS    This component include MMU Basic for the boot app
    REQUIRES    INCLUDE_MMU_BASIC
    _CHILDREN   FOLDER_BOOT_APP
}

/*
 * Boot File Formats
 */

Selection       SELECT_BOOT_IMAGE_FORMAT {
    NAME        Select boot file image format
    SYNOPSIS    By default, ELF formatted boot files are booted.
    COUNT       1-
    CHILDREN    INCLUDE_BOOT_ELF
    DEFAULTS    INCLUDE_BOOT_ELF
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
}

Component       INCLUDE_BOOT_ELF {
    NAME        Boot ELF file loader
    SYNOPSIS    Loader for ELF formatted boot files
    PROTOTYPE   IMPORT STATUS bootElfInit ();
    MODULES     bootElfLib.o
    INIT_RTN    bootElfInit();
}

/*
* The following component activates the optional memory mapping routines
* used by the ELF loader.  If the elfMemMap.o file is not present in the
* arch library, then this component will be greyed out.  These routines 
* map and unmap the memory space that the ELF file will be loaded into.
*/

Component INCLUDE_ELF_MEMORY_MAP {
    NAME        ELF loader memory mapping
    SYNOPSIS    ELF loader physical to virtual memory mapping.
    MODULES     elfMemMap.o
    PROTOTYPE   void elfMemMapInit(void);
    INIT_RTN    elfMemMapInit();
    _CHILDREN   FOLDER_BOOT_APP
    _DEFAULTS   FOLDER_BOOT_APP
}

/*
 * Boot App Shell Components
 */

Component       INCLUDE_BOOT_SHELL {
    NAME        Boot Application Shell
    SYNOPSIS    User Input processing for Boot Application
    PROTOTYPE   IMPORT STATUS bootAppShellInit ();
    MODULES     bootAppShell.o
    INIT_RTN    bootAppShellInit ();
    REQUIRES    INCLUDE_BOOT_APP    \
                INCLUDE_FORMATTED_OUT_BASIC \
                INCLUDE_SELECT 
    EXCLUDES    INCLUDE_SHELL \
                INCLUDE_BANNER
    _CHILDREN   FOLDER_BOOT_APP_SHELL
    _DEFAULTS   FOLDER_BOOT_APP_SHELL
}

Component       INCLUDE_BOOT_MEM_CMDS {
    NAME        Boot Application Memory Commands
    SYNOPSIS    Memory Commands for Boot Application Shell
    PROTOTYPE   IMPORT STATUS bootAppMemInit (void *);
    MODULES     bootMemCmds.o
    INIT_RTN    bootAppMemInit ((void *)LOCAL_MEM_LOCAL_ADRS);
    CFG_PARAMS  LOCAL_MEM_LOCAL_ADRS
    REQUIRES    INCLUDE_BOOT_APP    \
                INCLUDE_BOOT_SHELL
    _CHILDREN   FOLDER_BOOT_APP_SHELL
    _DEFAULTS   FOLDER_BOOT_APP_SHELL
}

Component       INCLUDE_BOOT_EDR_SUPPORT {
    NAME        Boot Application EDR Support Commands
    SYNOPSIS    EDR Commands for Boot Application Shell
    PROTOTYPE   IMPORT STATUS bootAppEdrInit (void);
    MODULES     bootEdrSupport.o
    INIT_RTN    bootAppEdrInit (); \
                edrSystemDebugModeSet (FALSE);
    REQUIRES    INCLUDE_BOOT_SHELL \
                INCLUDE_EDR_ERRLOG \
                INCLUDE_EDR_SHOW
    _CHILDREN   FOLDER_BOOT_APP_SHELL
    _DEFAULTS   FOLDER_BOOT_APP_SHELL
}

/*
 * Boot App Network Components
 */

Component       INCLUDE_BOOT_NETWORK {
    NAME        Boot Application Network Support
    SYNOPSIS    Support for booting over a network connection
    PROTOTYPE   IMPORT STATUS bootNetLoadInit ();
    MODULES     bootNetLoad.o
    INIT_RTN    bootNetLoadInit ();
    REQUIRES    INCLUDE_BOOT_APP    \
                INCLUDE_NETWORK \
                INCLUDE_NET_BOOT_CONFIG
    _CHILDREN   FOLDER_BOOT_APP_NETWORK
    _DEFAULTS   FOLDER_BOOT_APP_NETWORK
}

/* Network Boot Devices selection
 * Allows user to remove network devices from a bootApp build
 */
Selection	SELECT_BOOT_NET_DEVICES {
    NAME        Boot Devices for BSP
    SYNOPSIS    Selection of available boot devices
    COUNT       0-
    CHILDREN    INCLUDE_BOOT_NET_DEVICES
    DEFAULTS    INCLUDE_BOOT_NET_DEVICES
    _CHILDREN   FOLDER_BOOT_APP_NETWORK
    _DEFAULTS   FOLDER_BOOT_APP_NETWORK
}

/* Network Boot Devices for a BSP
 * The REQUIRES line should be modified by a BSP.
 */
Component       INCLUDE_BOOT_NET_DEVICES {
    NAME        Boot Application Network Boot Devices
    SYNOPSIS    Required boot devices
    REQUIRES
}

Component       INCLUDE_BOOT_FTP_LOADER {
    NAME        Boot Application FTP Loader
    SYNOPSIS    File loading using FTP for Boot Application
    PROTOTYPE   IMPORT STATUS bootFtpLoadInit ();
    MODULES     bootFtpLoad.o
    INIT_RTN    bootFtpLoadInit ();
    REQUIRES    INCLUDE_BOOT_NETWORK    \
                INCLUDE_FTP
    _CHILDREN   FOLDER_BOOT_APP_NETWORK
    _DEFAULTS   FOLDER_BOOT_APP_NETWORK
}

Component       INCLUDE_BOOT_TFTP_LOADER {
    NAME        Boot Application TFTP Loader
    SYNOPSIS    File loading using TFTP for Boot Application
    PROTOTYPE   IMPORT STATUS bootTftpLoadInit ();
    MODULES     bootTftpLoad.o
    INIT_RTN    bootTftpLoadInit ();
    REQUIRES    INCLUDE_BOOT_NETWORK    \
                INCLUDE_TFTP_CLIENT
    _CHILDREN   FOLDER_BOOT_APP_NETWORK
    _DEFAULTS   FOLDER_BOOT_APP_NETWORK
}

Component       INCLUDE_BOOT_RSH_LOADER {
    NAME        Boot Application RSH Loader
    SYNOPSIS    File loading using RSH for Boot Application
    PROTOTYPE   IMPORT STATUS bootRshLoadInit ();
    MODULES     bootRshLoad.o
    INIT_RTN    bootRshLoadInit ();
    REQUIRES    INCLUDE_BOOT_NETWORK \
                INCLUDE_REMLIB
    _CHILDREN   FOLDER_BOOT_APP_NETWORK
    _DEFAULTS   FOLDER_BOOT_APP_NETWORK
}

Component       INCLUDE_BOOT_END {
    NAME        Boot Application END Device Support
    SYNOPSIS    Support using END device for Booting Application
    PROTOTYPE   IMPORT STATUS bootEndSupportInit ();
    MODULES     bootEndSupport.o
    INIT_RTN    bootEndSupportInit ();
    REQUIRES    INCLUDE_BOOT_NETWORK    \
                INCLUDE_END
    _CHILDREN   FOLDER_BOOT_APP_NETWORK
    _DEFAULTS   FOLDER_BOOT_APP_NETWORK
}

Component       INCLUDE_BOOT_ETH_MAC_HANDLER {
    NAME        Boot Application Ethernet MAC Support
    SYNOPSIS    Support for setting MAC Address in boot application. \
                NOTE: When upgrading the boot loader from VxWorks version 6.6 \
                or older, you will need to reprogram the MAC addresses.  The \
                byte order of how the MAC address is stored changed beginning \
                with VxWorks version 6.7.  Prior to updating a VxWorks 6.6, or \
                older, boot loader, display and save the current MAC values \
                for the target board.  Once the new VxWorks boot loader has \
                been installed, reprogram the MAC addresses of the target \
                board using the values saved from the older boot load MAC \
                address display.
    PROTOTYPE   IMPORT STATUS bootEthMacHandlerInit (int, int, UINT8, UINT8, \
                                                     UINT8, int);
    INIT_RTN    bootEthMacHandlerInit (MAX_MAC_ADRS, MAX_MAC_DEVS, \
                   ENET_DEFAULT0, ENET_DEFAULT1, ENET_DEFAULT2, MAC_ADRS_LEN);
    CFG_PARAMS  MAX_MAC_ADRS \
                MAX_MAC_DEVS \
                ENET_DEFAULT0 \
                ENET_DEFAULT1 \
                ENET_DEFAULT2 \
                MAC_ADRS_LEN
    MODULES     bootEthMacHandler.o
    REQUIRES    INCLUDE_BOOT_NETWORK 
    EXCLUDES    INCLUDE_BOOT_ETH_ADR_SET
    _CHILDREN   FOLDER_BOOT_APP_NETWORK
}

Component       INCLUDE_BOOT_ETH_ADR_SET {
    NAME        Boot Application Ethernet Address Set Support
    SYNOPSIS    Support for setting MAC Address in boot application. \
                NOTE: When upgrading the boot loader from VxWorks version 6.6 \
                or older, you will need to reprogram the MAC addresses.  The \
                byte order of how the MAC address is stored changed beginning \
                with VxWorks version 6.7.  Prior to updating a VxWorks 6.6, or \
                older, boot loader, display and save the current MAC values \
                for the target board.  Once the new VxWorks boot loader has \
                been installed, reprogram the MAC addresses of the target \
                board using the values saved from the older boot load MAC \
                address display.
    PROTOTYPE   IMPORT STATUS bootEthAdrSetInit (UINT8, UINT8, UINT8);
    INIT_RTN    bootEthAdrSetInit (ENET_DEFAULT0, ENET_DEFAULT1, ENET_DEFAULT2);
    CFG_PARAMS  ENET_DEFAULT0 \
                ENET_DEFAULT1 \
                ENET_DEFAULT2
    MODULES     bootEthAdrSet.o
    REQUIRES    INCLUDE_BOOT_NETWORK 
    EXCLUDES    INCLUDE_BOOT_ETH_MAC_HANDLER
    _CHILDREN   FOLDER_BOOT_APP_NETWORK
}

Component       INCLUDE_USR_MACADDR {
    NAME        User Mac Address Save and Get
    SYNOPSIS    Support for saving and getting MAC address
    CONFIGLETTES    usrMacAddr.c
    _CHILDREN   FOLDER_NOT_VISIBLE
}

/* 
 * NOTE: The following default for MAX_MAC_ADRS, MAX_MAC_DEVS,
 * and MAC_ADRS_LEN are coupled to the INCLUDE_BOOT_ETH_MAC_HANDLER component.  
 * The BSP that uses the component should set these values properly.
 */

Parameter	MAX_MAC_ADRS {
	DEFAULT		1
}

Parameter	MAX_MAC_DEVS {
	DEFAULT		1
}

/* 
 * NOTE: The default ENET_DEFAULT0, ENET_DEFAULT1, and ENET_DEFAULT2 are also 
 * coupled to the INCLUDE_BOOT_ETH_ADR_SET component.
 * The BSP that uses the component should set the value properly.
 */

Parameter	ENET_DEFAULT0 {
	DEFAULT		0x00
}

Parameter	ENET_DEFAULT1 {
	DEFAULT		0x00
}

Parameter	ENET_DEFAULT2 {
	DEFAULT		0x01
}

Parameter	MAC_ADRS_LEN {
	DEFAULT		6
}

Component       INCLUDE_BOOT_DHCPC {
    NAME            Boot Application DHCP Client Support
    SYNOPSIS        Using DHCP Client for Booting Application
    PROTOTYPE       IMPORT STATUS bootDhcpcLoadInit ();
    MODULES         bootDhcpcLoad.o
    INIT_RTN        bootDhcpcLoadInit ();
    INCLUDE_WHEN    INCLUDE_BOOT_NETWORK    \
                    INCLUDE_IPDHCPC
    REQUIRES        INCLUDE_BOOT_NETWORK    \
                    INCLUDE_IPDHCPC
    _CHILDREN       FOLDER_BOOT_APP_NETWORK
    CFG_PARAMS      BOOTAPP_DHCPC_REQ_OPTS BOOTAPP_DHCPC_IF_REQ_OPTS_LIST
}

/*
 * Boot App Filesystem Components
 */

Component       INCLUDE_BOOT_FILESYSTEMS {
    NAME        Boot Application FILESYSTEM Support
    SYNOPSIS    Support for booting from a filesystem
    PROTOTYPE   IMPORT STATUS bootFsLoadInit (); \
                IMPORT STATUS bootFsDevCheckConfig (BOOL, UINT32, UINT32);
    SOURCE      {$(TGT_DIR)/src/boot bootFsLoad.o }
    MODULES     bootFsLoad.o
    INIT_RTN    bootFsLoadInit (); \
                bootFsDevCheckConfig (BOOT_FS_DEV_MOUNT_CHECK, \
                                      BOOT_FS_CHECK_ATTEMPTS, \
                                      BOOT_FS_ATTEMPT_DELAY);
    REQUIRES    INCLUDE_BOOT_APP \
                INCLUDE_IO_SYSTEM
    CFG_PARAMS  BOOT_FS_DEV_MOUNT_CHECK \
                BOOT_FS_CHECK_ATTEMPTS \
                BOOT_FS_ATTEMPT_DELAY
    _CHILDREN   FOLDER_BOOT_APP_FILESYSTEMS
    _DEFAULTS   FOLDER_BOOT_APP_FILESYSTEMS
}

/* enable checking whether mounting is ready for boot FS dev */

Parameter	BOOT_FS_DEV_MOUNT_CHECK {
    NAME        check boot FS device mounting
    SYNOPSIS    Enable checking mount status for boot FS device \
                before loading image file from it.
    TYPE        BOOL
	DEFAULT		TRUE
}

/* Number of attempts at mounting check on FS boot device */

Parameter	BOOT_FS_CHECK_ATTEMPTS {
    NAME        FS device mounting check attempts
    SYNOPSIS    Number of times an attempt will be made to \
                check FS boot device mounting.
	DEFAULT		30
}

/* Ticks to delay between mounting checks on FS boot device */

Parameter	BOOT_FS_ATTEMPT_DELAY {
    NAME        delay between mounting check attempts
    SYNOPSIS    Amount of time in system ticks to delay between attempts to \
                check mounting FS boot device.
	DEFAULT		60
}

/* Filesystem Boot Devices selection
 * Allows user to remove filesystem devices from a bootApp build
 */
Selection	SELECT_BOOT_FS_DEVICES {
    NAME        Boot Filesystem Devices for BSP
    SYNOPSIS    Selection of available boot devices
    COUNT       0-
    CHILDREN    INCLUDE_BOOT_FS_DEVICES
    DEFAULTS    INCLUDE_BOOT_FS_DEVICES
    _CHILDREN   FOLDER_BOOT_APP_FILESYSTEMS
    _DEFAULTS   FOLDER_BOOT_APP_FILESYSTEMS
}

/* Filesystem Boot Devices for a BSP
 * The REQUIRES line should be modified by a BSP.
 */
Component       INCLUDE_BOOT_FS_DEVICES {
    NAME        Boot Application Filesystem Boot Devices
    SYNOPSIS    Required boot devices
    REQUIRES
}

Component       INCLUDE_BOOT_USB_FS_LOADER {
    NAME        Boot Application USB Disk Loader
    SYNOPSIS    File loading from USB Disk for Boot Application
    PROTOTYPE   IMPORT STATUS bootUsbFsLoadInit (int, int, char *);
    INIT_RTN    bootUsbFsLoadInit (BOOT_USB_OPEN_ATTEMPTS, \
                                   BOOT_USB_ATTEMPT_DELAY, \
                                   USB2_MSC_DRIVE_NAME);
    REQUIRES    INCLUDE_BOOT_FILESYSTEMS \
                INCLUDE_USB_GEN2_STORAGE_INIT
    CFG_PARAMS  BOOT_USB_OPEN_ATTEMPTS \
                BOOT_USB_ATTEMPT_DELAY \
                USB2_MSC_DRIVE_NAME
    _CHILDREN   FOLDER_BOOT_APP_FILESYSTEMS
}

/* Number of attempts at an open() call on a USB boot device. */

Parameter	BOOT_USB_OPEN_ATTEMPTS {
    NAME        USB device open attempts.
    SYNOPSIS    Number of times an attempt will be made to \
                open the USB boot device.
	DEFAULT		10
}

/* Ticks to delay between attempted open() calls on a USB boot device. */

Parameter	BOOT_USB_ATTEMPT_DELAY {
    NAME        Delay between USB device open attempts.
    SYNOPSIS    Amount of time in system ticks to delay between attempts to \
                open the USB boot device.
	DEFAULT		60
}

Component       INCLUDE_BOOT_USB_SHOW {
    NAME        Boot Application USB device show routine
    SYNOPSIS    Boot application show routine for USB devices.
    PROTOTYPE   IMPORT void bootUsbShowInit (void);
    MODULES     bootUsbShow.o
    INIT_RTN    bootUsbShowInit ();
    REQUIRES    INCLUDE_USB_SHOW \
                INCLUDE_BOOT_APP
    INCLUDE_WHEN INCLUDE_BOOT_APP    \
                INCLUDE_USB
    _CHILDREN   FOLDER_BOOT_APP_FILESYSTEMS
}

/*
 * Boot App Initialization Group
 */

InitGroup       usrBootAppInit {
    INIT_RTN    usrBootAppInit ();
    SYNOPSIS    The Boot App initialization sequence
    INIT_ORDER  INCLUDE_BOOTAPP_NVRAM_SUPPORT \
                INCLUDE_BOOT_INIT \
                INCLUDE_BOOT_ELF \
                INCLUDE_ELF_MEMORY_MAP \
                INCLUDE_BOOT_EXC_HANDLER \
                INCLUDE_BOOT_TEST_FUNCS \
                INCLUDE_BOOT_SHELL \
                INCLUDE_BOOT_MEM_CMDS \
                INCLUDE_BOOT_EDR_SUPPORT \
                INCLUDE_BOOT_FILESYSTEMS \
                INCLUDE_BOOT_USB_FS_LOADER \
                INCLUDE_BOOT_USB_SHOW \
                INCLUDE_BOOT_DHCPC \
                INCLUDE_BOOT_NETWORK \
                INCLUDE_BOOT_TFTP_LOADER \
                INCLUDE_BOOT_FTP_LOADER \
                INCLUDE_BOOT_RSH_LOADER \
                INCLUDE_BOOT_END \
                INCLUDE_BOOT_ETH_MAC_HANDLER \
                INCLUDE_BOOT_ETH_ADR_SET
    _INIT_ORDER usrToolsInit
}


InitGroup       usrBootAppStart {
    INIT_RTN    usrBootAppStart ();
    SYNOPSIS    Starts the boot application after initialization is complete.
    INIT_ORDER  INCLUDE_BOOT_APP
    INIT_BEFORE INCLUDE_USER_APPL
    INIT_AFTER  usrToolsInit
    _INIT_ORDER usrRoot
}

/*
 * Add this hidden component for migration issues.
 * The real function of this component is not supported.
 */

Component       INCLUDE_BOOT_VXBUS {
	_CHILDREN	FOLDER_NOT_VISIBLE
}
