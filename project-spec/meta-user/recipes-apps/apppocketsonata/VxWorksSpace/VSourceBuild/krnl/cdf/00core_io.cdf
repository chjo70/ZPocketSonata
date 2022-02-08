/* 00core_io.cdf - VxWorks Core I/O components */

/*
 * Copyright (c) 2014-2016, 2018 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
03jan18,dlk  Add usrIo.c configlette with usrFdSetFdBound(); add
             SELECT_FDSET_OVERSIZE_ALLOW parameter to INCLUDE_SELECT (V7COR-5462)
21apr16,emj  CERT: Update to produce partially linked objects (US79607)
28mar16,dlk  Added INCLUDE_MVARDRV.
01sep15,clt  added INCLUDE_ROMFS_DRV (F4862)
23jul15,h_k  added TYLIB_MON_TRAP_DISABLE parameter to INCLUDE_TYLIB. (US58664)
24mar15,h_k  added INCLUDE_SYSLOG. (F2865)
08apr15,jmz  V7COR-2857 Set the initialization order correctly for the
             INCLUDE_PC_CONSOLE component
03feb15,ymz  added INCLUDE_IO_POSIX to CERT
23jan15,gls  removed INCLUDE_TASK_INFO from INCLUDE_IO_BASIC
12mar15,dcc  moved VDFS initialization spot
17feb15,dcc  added INCLUDE_VDFS initialization
16dec14,ymz  modified INCLUDE_IO_FILE_SYSTEM INCLUDE_IO_MISC and
             INCLUDE_SELECT and INCLUDE_IO_BASIC for CERT profile
17oct14,ten  Move boot line init from ios core to extra (V7PRO-1236)
17sep14,cww  exclude INCLUDE_IO_POSIX and INCLUDE_IO_REMOVABLE from CERT
12aug14,gpa  Merge with vx7-mainline
27may14,m_y  remove INCLUDE_ERF in usrIosExtraInit group (V7STO-15)
14may14,h_k  added POSIX pipes support. (US35006)
09may14,ghs  Integrate CDROM FS into VxWorks 7 (US38573)
05may14,m_y  add xbd block cache init (US15841)
19mar14,j_l  US32795 - restore INCLUDE_BOOT_LINE_INIT order for IA
25feb14,d_z  Correct bootline init order for legacy vxbus. VXW7-2156
21feb14,d_z  Adjust initialization order for INCLUDE_BOOT_LINE_INIT
17feb14,ghs  Move out file system components
10feb14,pcs  VXW7-1597 - POSIX components cleanup
28jan14,wap  Adjust previous change so that it only takes effect when
             not using legacy VxBus support
28jan14,wap  Set the initialization order correctly for the INCLUDE_SIO
             component so that it's done at the right time for the new
             style BSPs (must be done after VxBus init).
17jan14,tlu  created
*/

/*
DESCRIPTION
This file contains descriptions for VxWorks core I/O components.
The configuration tool searches for .cdf files in four
places; here, arch/<arch>, config/<bsp>, and the project directory.
This file describes "generic" components which are available
to all CPU architectures and BSPs.
If a new component is released, a new .cdf file should be deposited
in the appropriate directory, rather than modifying existing files.

INTERNAL
add in windview
"Precious" Components (like the kernel!) that can't be deleted.
Folder-precious components (like wdbCore), that can't be deleted
without deleting the whole folder.
*/


Component INCLUDE_POSIX_AIO {
	NAME		Asynchronous I/O
	SYNOPSIS	POSIX asynchronous I/O
	MODULES		aioPxLib.o
	INIT_RTN	aioPxLibInit (MAX_LIO_CALLS);
	CFG_PARAMS	MAX_LIO_CALLS
	HDR_FILES	aio.h
	REQUIRES	INCLUDE_PIPES
	INIT_AFTER	INCLUDE_PIPES
}

Parameter MAX_LIO_CALLS {
        NAME            Maximum outstanding LIO calls
        SYNOPSIS        This parameter sets the maximum number of lio calls. \
						By default, it is set to zero.
        TYPE            uint
        DEFAULT         0
}

Component INCLUDE_POSIX_AIO_SYSDRV {
	NAME		Asynchronous I/O driver
	SYNOPSIS	Provides AIO functionality to non-AIO drivers
	MODULES		aioSysDrv.o
	INIT_RTN	aioSysInit (MAX_AIO_SYS_TASKS, \
				AIO_TASK_PRIORITY, AIO_TASK_STACK_SIZE);
	CFG_PARAMS	MAX_AIO_SYS_TASKS \
			AIO_TASK_PRIORITY \
			AIO_TASK_STACK_SIZE
	HDR_FILES	aioSysDrv.h
}

Parameter MAX_AIO_SYS_TASKS {
        NAME            Number of tasks spawned to support AIO
		SYNOPSIS		Sets the number of tasks spawned during the \
						initialization of the AIO system driver. The default is zero.
        TYPE            uint
        DEFAULT         0
}

Parameter AIO_TASK_PRIORITY {
        NAME            AIO task priority
		SYNOPSIS		Sets the priority level of the tasks spawned during \
						the initialization of the AIO system driver. The default is zero.
        TYPE            uint
        DEFAULT         0
}

Parameter AIO_TASK_STACK_SIZE {
        NAME            AIO tasks stack size
		SYNOPSIS		Sets the initial stack size. The default is zero.
        TYPE            uint
        DEFAULT         0
}

Component INCLUDE_POSIX_FTRUNC {
	NAME		ftruncate()
	SYNOPSIS	POSIX ftruncate
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		ftruncate.o
#endif
	LINK_SYMS	ftruncate
	HDR_FILES	unistd.h
}

Component INCLUDE_POSIX_AIO_SHOW {
	NAME		Asynchronous IO show routine
	SYNOPSIS	This component provides the aioPxShow library. This library \
				implements the show routine for aioPxLib. It includes the \
				routine aioShow() that displays the outstanding AIO requests.
	MODULES		aioPxShow.o
	LINK_SYMS	aioShow
	INCLUDE_WHEN	INCLUDE_POSIX_AIO \
			INCLUDE_SHOW_ROUTINES
}

Folder	FOLDER_IO_SYSTEM {
	NAME		IO system
	SYNOPSIS	This folder contains components and parameters related to the IO system.
	CHILDREN	INCLUDE_IO_SYSTEM	\
			FOLDER_IO_SUBSYSTEM	\
			FOLDER_HRFS             \
                        FOLDER_FTL              \
			INCLUDE_STDIO		\
			INCLUDE_FLOATING_POINT	\
			INCLUDE_FORMATTED_IO	\
			INCLUDE_FORMATTED_OUT_BASIC	\
			INCLUDE_LOGGING		\
			INCLUDE_SYSLOG		\
			INCLUDE_PIPES		\
			INCLUDE_SELECT		\
			INCLUDE_RAMDRV		\
			INCLUDE_MEMDRV		\
                        INCLUDE_MVARDRV         \
			INCLUDE_PTYDRV		\
			INCLUDE_TYLIB		\
			INCLUDE_TTY_DEV		\
			INCLUDE_POSIX_PIPES
#ifndef _WRS_CONFIG_CERT
	DEFAULTS	INCLUDE_IO_SYSTEM		\
			INCLUDE_STDIO			\
			INCLUDE_FLOATING_POINT		\
			INCLUDE_FORMATTED_IO		\
			INCLUDE_FORMATTED_OUT_BASIC	\
			INCLUDE_PIPES			\
			INCLUDE_LOGGING			\
			INCLUDE_SELECT			\
			INCLUDE_TTY_DEV
#else
	DEFAULTS	INCLUDE_IO_SYSTEM		\
			INCLUDE_STDIO			\
			INCLUDE_FLOATING_POINT		\
			INCLUDE_FORMATTED_IO		\
			INCLUDE_FORMATTED_OUT_BASIC	\
			INCLUDE_LOGGING			\
			INCLUDE_SELECT			\
			INCLUDE_TTY_DEV
#endif
}

Component INCLUDE_TTY_DEV {
	NAME		Terminal driver
	SYNOPSIS	Provides terminal device access to serial channels.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		ttyDrv.o
#endif
	INIT_RTN	ttyDrv ();
	REQUIRES	INCLUDE_IO_BASIC        \
			INCLUDE_TYLIB           \
			INCLUDE_MEM_MGR_BASIC
	HDR_FILES	ttyLib.h
}

Component INCLUDE_POSIX_FS {
	NAME		Posix APIs for file systems
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		fsPxLib.o
#endif
	REQUIRES	INCLUDE_IO_SYSTEM
	INCLUDE_WHEN	INCLUDE_IO_SYSTEM
	_CHILDREN	FOLDER_NOT_VISIBLE
}

Parameter IOS_POSIX_PSE52_MODE {
        NAME            POSIX PSE52 mode for VxWorks I/O subsystem
        SYNOPSIS        Enables POSIX PSE52 behavior for the VxWorks I/O subsystem
        TYPE            BOOL
        DEFAULT         (INCLUDE_RTP_POSIX_PSE52)::(TRUE) FALSE
}

Component INCLUDE_IO_BASIC {
      NAME            Basic IO System
	SYNOPSIS	Basic IO system component

	REQUIRES	INCLUDE_KERNEL           \
			INCLUDE_OBJ_LIB		 \
			INCLUDE_SEM_INFO	 \
			INCLUDE_LSTLIB		 \
			INCLUDE_DLL              \
			INCLUDE_POOL		 \
			INCLUDE_SEM_MUTEX_CREATE \
			INCLUDE_ANSI_CTYPE	 \
			INCLUDE_ANSI_STRLEN	 \
			INCLUDE_ANSI_STRCAT	 \
			INCLUDE_ANSI_STRNCAT	 \
			INCLUDE_ANSI_STRNCMP     \
			INCLUDE_MEM_MGR_BASIC

        CONFIGLETTES    usrIo.c

#ifndef _WRS_CONFIG_CERT
        MODULES         ioLib.o iosLib.o iosDrvLib.o pathCatLib.o
#else
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         ioLib.o iosLib.o iosMemPoolLib.o iosDrvLib.o \
                        pathCatLib.o
#endif
#endif

#ifdef _WRS_CONFIG_CERT
	INIT_RTN	iosInit (NUM_DRIVERS, NUM_FILES, NUM_IO_CONCURRENT, "/null");
	CFG_PARAMS	NUM_DRIVERS NUM_FILES NUM_IO_CONCURRENT
#else
	INIT_RTN	iosInit (NUM_DRIVERS, NUM_FILES, "/null");
	CFG_PARAMS	NUM_DRIVERS NUM_FILES
#endif
	HDR_FILES	iosLib.h
}

Component INCLUDE_IO_FILE_SYSTEM {
        NAME            File System IO
	SYNOPSIS	File System IO component
#ifdef _WRS_CONFIG_CERT
        REQUIRES        INCLUDE_IO_BASIC
#else
        REQUIRES        INCLUDE_IO_BASIC \
			INCLUDE_IO_REMOVABLE
#endif
	INCLUDE_WHEN	INCLUDE_IO_SYSTEM
#ifdef _WRS_CONFIG_CERT

#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         fsIoLib.o iosPathLib.o
#endif

#else
        MODULES         fsIoLib.o iosPathLib.o pathLib.o
#endif
        INIT_RTN        iosPathLibInit ();
        HDR_FILES       iosLib.h
}

Component INCLUDE_IO_REMOVABLE {
        NAME            Removable IO
	SYNOPSIS	Removable IO component
	REQUIRES        INCLUDE_IO_BASIC
#ifndef _WRS_CONFIG_CERT
	INCLUDE_WHEN	INCLUDE_IO_SYSTEM
#endif
        MODULES         iosRmvLib.o
        INIT_RTN        iosRmvLibInit ();
}

Component INCLUDE_IO_POSIX {
        NAME            POSIX IO
	SYNOPSIS	POSIX IO component
#ifndef _WRS_CONFIG_CERT
        REQUIRES        INCLUDE_IO_BASIC       \
                        INCLUDE_IO_FILE_SYSTEM \
                        INCLUDE_IO_REMOVABLE
#else
        REQUIRES        INCLUDE_IO_BASIC       \
                        INCLUDE_IO_FILE_SYSTEM
#endif
#ifndef _WRS_CONFIG_CERT
	INCLUDE_WHEN	INCLUDE_IO_SYSTEM
#endif
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         ioPxLib.o iosPxLib.o
#endif
        INIT_RTN        iosPxLibInit (IOS_POSIX_PSE52_MODE);
	CFG_PARAMS	IOS_POSIX_PSE52_MODE
        HDR_FILES       iosLib.h
}

Component INCLUDE_IO_RTP {
        NAME            RTP IO
	SYNOPSIS	RTP IO component
#ifndef _WRS_CONFIG_CERT
        REQUIRES        INCLUDE_IO_BASIC       \
                        INCLUDE_IO_FILE_SYSTEM \
                        INCLUDE_IO_REMOVABLE   \
                        INCLUDE_IO_POSIX
#else
        REQUIRES        INCLUDE_IO_BASIC       \
                        INCLUDE_IO_POSIX
#endif
	INCLUDE_WHEN	INCLUDE_IO_SYSTEM
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         iosRtpLib.o
#endif
        INIT_RTN        iosRtpLibInit ();
        HDR_FILES       iosLib.h
}

Component INCLUDE_IO_MISC {
        NAME            Miscellaneous IO
	SYNOPSIS	Miscellaneous IO component
#ifndef _WRS_CONFIG_CERT
	INCLUDE_WHEN	INCLUDE_IO_SYSTEM
#endif
        MODULES         iosMiscLib.o
        HDR_FILES       iosLib.h
}

Component INCLUDE_IO_SYSTEM {
	NAME		IO system
	SYNOPSIS	IO system component
	REQUIRES	INCLUDE_IO_BASIC
}

Folder FOLDER_IO_SUBSYSTEM
	{
	NAME		IO subsystem
	SYNOPSIS	IO System related components
	_CHILDREN	FOLDER_IO_SYSTEM
	CHILDREN	INCLUDE_IO_BASIC \
			INCLUDE_IO_FILE_SYSTEM \
			INCLUDE_IO_REMOVABLE \
			INCLUDE_IO_POSIX \
			INCLUDE_IO_RTP \
			INCLUDE_IO_MISC
	}

Component INCLUDE_PIPES {
	NAME		Pipes
	SYNOPSIS	This component enables the use of pipes. Pipes provide an alternative \
			interface to the message queue facility that goes through the \
			VxWorks I/O system. Pipe devices are managed by the pipeDrv virtual \
			I/O device, and use the kernel message queue facility to bear the \
			actual message traffic. Tasks write messages to pipes, which are then \
			read by other tasks. This allows you to implement a client-server \
			model of intertask communications. For more information about pipes, \
			see the ioLib entry in the VxWorks 7 Application COREOS API Reference, \
			and the pipeDrv entry in the VxWorks 7 Kernel COREOS API Reference.
	MODULES		pipeDrv.o
	INIT_RTN	pipeDrv (PIPE_MAX_OPEN_FDS);
	CFG_PARAMS      PIPE_MAX_OPEN_FDS
	HDR_FILES	pipeDrv.h
	REQUIRES        INCLUDE_KERNEL            \
			INCLUDE_MSG_Q_INFO        \
			INCLUDE_SEM_INFO          \
			INCLUDE_IO_BASIC          \
			INCLUDE_MEM_MGR_BASIC     \
			INCLUDE_SELECT            \
			INCLUDE_MSG_Q_CREATE_DELETE
}

Parameter PIPE_MAX_OPEN_FDS {
	NAME            maximum open fds for each pipe device
        SYNOPSIS        maximum open fds for each pipe device
	TYPE            uint
        DEFAULT         16
}

Component INCLUDE_POSIX_PIPES {
	NAME		POSIX pipes and FIFOs
	SYNOPSIS	POSIX pipe(), pipe2() and mkfifo() support
	MODULES		pxPipeDrv.o virtFsDrv.o
	PROTOTYPE	STATUS pxPipeDrv (const char * devName, size_t size);
	INIT_RTN	pxPipeDrv (FIFOS_DEV_NAME, PX_PIPE_BUFFER_SIZE);
	REQUIRES        INCLUDE_CONDVAR \
			INCLUDE_POSIX_DIRLIB \
			INCLUDE_POSIX_FS \
			INCLUDE_RNG_BUF \
			INCLUDE_SELECT \
			INCLUDE_SIGNALS
	CFG_PARAMS	FIFOS_DEV_NAME \
			PX_PIPE_BUFFER_SIZE
}

Parameter FIFOS_DEV_NAME {
	NAME		POSIX pipes and FIFOs device name
	SYNOPSIS	Name of POSIX pipes and FIFOs object device
	TYPE		string
	DEFAULT		"/fifos"
}

Parameter PX_PIPE_BUFFER_SIZE {
	NAME		buffer size used by POSIX pipe
	SYNOPSIS	buffer size used by POSIX pipe
	TYPE		size_t
	DEFAULT		4096
}

Component INCLUDE_RAMDRV {
	NAME		RAM disk driver
	SYNOPSIS	allows a filesystem to be put on top of RAM
	MODULES		ramDrv.o
	INIT_RTN	ramDrv ();
	HDR_FILES	ramDrv.h
}

Component INCLUDE_MEMDRV {
	NAME		MEM disk driver
	SYNOPSIS	allows a filesystem to be put on top of memory
	MODULES		memDrv.o
	INIT_RTN	memDrv ();
	HDR_FILES	memDrv.h
}

Component INCLUDE_MVARDRV {
        NAME            MVar driver
        SYNOPSIS        test/demo driver for 1-ULONG message channel device
        MODULES         mvarDrv.o
        INIT_RTN        mvarDrv ();
        HDR_FILES       mvarDrv.h
}

Component INCLUDE_PTYDRV {
	NAME		Pseudo terminal driver
	SYNOPSIS	Allows communication between processes
	MODULES		ptyDrv.o
	INIT_RTN	ptyDrv ();
	HDR_FILES	ptyDrv.h
}

Component INCLUDE_TYLIB {
	NAME		terminal driver support
	SYNOPSIS	Allows communication between processes
	REQUIRES	INCLUDE_BLIB		\
			INCLUDE_SEM_BINARY        \
			INCLUDE_SEM_MUTEX         \
			INCLUDE_RNG_BUF
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		tyLib.o
#endif
	PROTOTYPE	STATUS tyLibInit (int xoffThresh, int xonThresh, size_t wrtThresh, BOOL monTrapDisable);
	INIT_RTN	tyLibInit (TYLIB_XOFF_PCNT, TYLIB_XON_PCNT, \
				TYLIB_WRT_THRESHLD, TYLIB_MON_TRAP_DISABLE);
	HDR_FILES	tyLib.h
	CFG_PARAMS	TYLIB_XOFF_PCNT \
			TYLIB_XON_PCNT \
			TYLIB_WRT_THRESHLD \
			TYLIB_MON_TRAP_DISABLE
}

Parameter TYLIB_XOFF_PCNT {
	NAME		XOFF buffer threshold
	SYNOPSIS	Send XOFF when rcv buff exceeds this level (%).
	TYPE		uint
	DEFAULT		85
}

Parameter TYLIB_XON_PCNT {
	NAME		XON buffer threshold
	SYNOPSIS	Send XON when rcv buff drops below this level (%).
	TYPE		uint
	DEFAULT		50
}

Parameter TYLIB_WRT_THRESHLD {
	NAME		Write buffer threshold
	SYNOPSIS	Wakeup tty writer tasks when tx buffer has this much available space (chars).
	TYPE		uint
	DEFAULT		50
}

Parameter TYLIB_MON_TRAP_DISABLE {
	NAME		OPT_MON_TRAP is always disabled
	SYNOPSIS	Ignore OPT_MON_TRAP option.
	TYPE		BOOL
#ifdef	_WRS_CONFIG_CERT
	DEFAULT		TRUE
#else
	DEFAULT		FALSE
#endif	/* _WRS_CONFIG_CERT */
}

/* Select is really one component with two different init routines */

Component INCLUDE_SELECT {
	NAME		Select
	SYNOPSIS	This provides the kernel selectLib library which includes select() \
			and related functions.
#ifdef _WRS_CONFIG_CERT
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		selectLib.o
#endif
	INIT_RTN	selectInit (NUM_DEV_SELECT_CONCURRENT);
        CFG_PARAMS      NUM_DEV_SELECT_CONCURRENT \
                        SELECT_FDSET_OVERSIZE_ALLOW
#else
	MODULES		selectLib.o selectTyLib.o
	INIT_RTN	selectInit (NUM_FILES);
        CFG_PARAMS      SELECT_FDSET_OVERSIZE_ALLOW
#endif
	HDR_FILES	selectLib.h
	REQUIRES	INCLUDE_IO_BASIC	       \
			INCLUDE_SEM_BINARY	       \
			INCLUDE_SEM_MUTEX              \
			INCLUDE_EXC_TASK	       \
			INCLUDE_TASK_CREATE_HOOKS      \
			INCLUDE_LSTLIB                 \
			INCLUDE_MEM_MGR_BASIC          \
			INCLUDE_OBJ_LIB                \
			INCLUDE_RNG_BUF                \
			INCLUDE_SELECT_SUPPORT
	INCLUDE_WHEN	INCLUDE_IO_SYSTEM
	INIT_BEFORE	INCLUDE_SELECT_SUPPORT
	HELP		selectLib
}

/*
 * This is the second init routine for select. This is because
 * the select delete hook must be called before the RPC delete hook when
 * a task is deleted.
 * The task create hook is installed as part of selectInit() above.
 */

Component INCLUDE_SELECT_SUPPORT {
	NAME		selectInit, part 2, install task delete hook
	INIT_RTN	selTaskDeleteHookAdd ();
	REQUIRES	INCLUDE_SELECT
	HDR_FILES	selectLib.h
}

Parameter SELECT_FDSET_OVERSIZE_ALLOW {
        NAME            Allow FD tables larger than FD_SETSIZE
        SYNOPSIS        Normally, the kernel and RTP file descriptor tables \
                        should be no larger than FD_SETSIZE when select() \
                        support is included. When this parameter is TRUE, \
                        RTP file descriptor tables are allowed to be larger \
                        than FD_SETSIZE descriptors. Some applications using \
                        select() may not expect this, and any that do will need \
                        to manually allocate and initialize extra-large fd_set \
                        structures.
        TYPE            BOOL
        DEFAULT         FALSE
}

Parameter NUM_FILES {
        SYNOPSIS        Limit to FD_SETSIZE (2048) when using selectLib
        NAME            max # open files in the system
        TYPE            uint
        DEFAULT         50
}

#ifdef _WRS_CONFIG_CERT

Parameter NUM_DEV_SELECT_CONCURRENT {
        SYNOPSIS        Limit to Concurrent select to devices in the system
        NAME            max # selection on devices in parallel
        TYPE            uint
        DEFAULT         30
}


Parameter NUM_IO_CONCURRENT {
        SYNOPSIS        Limit of concurrent IO operation
        NAME            max # IO operation in parallel
        TYPE            uint
        DEFAULT         30
}

#endif /* _WRS_CONFIG_CERT */

InitGroup usrIosCoreInit {
	INIT_RTN	usrIosCoreInit ();
	SYNOPSIS	core I/O system
#ifdef _WRS_CONFIG_VXBUS_LEGACY
	INIT_ORDER	INCLUDE_IO_BASIC       \
                        INCLUDE_IO_FILE_SYSTEM \
                        INCLUDE_IO_REMOVABLE   \
                        INCLUDE_IO_POSIX       \
                        INCLUDE_IO_RTP         \
                        INCLUDE_IO_MISC        \
			INCLUDE_SELECT \
			INCLUDE_ISR_DEFER \
			INCLUDE_TYLIB \
			INCLUDE_TTY_DEV \
			INCLUDE_TYCODRV_5_2 \
			INCLUDE_SIO \
			INCLUDE_PC_CONSOLE
#else /* _WRS_CONFIG_VXBUS_LEGACY */
	INIT_ORDER	INCLUDE_IO_BASIC       \
                        INCLUDE_IO_FILE_SYSTEM \
                        INCLUDE_IO_REMOVABLE   \
                        INCLUDE_IO_POSIX       \
                        INCLUDE_IO_RTP         \
                        INCLUDE_IO_MISC        \
			INCLUDE_SELECT \
			INCLUDE_ISR_DEFER \
			INCLUDE_TYLIB \
			INCLUDE_TTY_DEV \
			INCLUDE_TYCODRV_5_2
#endif /* !_WRS_CONFIG_VXBUS_LEGACY */
    _INIT_ORDER     usrRoot
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    INIT_AFTER      INCLUDE_IDLE_TASKS
    INIT_BEFORE     INCLUDE_VXBUS
#else /* _WRS_CONFIG_VXBUS_LEGACY */
    INIT_AFTER      INCLUDE_PX_SCHED_SPORADIC_POLICY
    INIT_BEFORE     INCLUDE_MMAP
#endif /* !_WRS_CONFIG_VXBUS_LEGACY */
	}

InitGroup usrIosExtraInit {
	INIT_RTN	usrIosExtraInit ();
	SYNOPSIS	extended I/O system
	INIT_ORDER	INCLUDE_JOB_TASK \
			INCLUDE_EXC_TASK \
			INCLUDE_SM_OBJ \
			INCLUDE_SYSLOG \
			INCLUDE_LOGGING \
			INCLUDE_PIPES \
			INCLUDE_POSIX_ADVISORY_FILE_LOCKING \
			INCLUDE_POSIX_AIO \
			INCLUDE_POSIX_AIO_SYSDRV  \
			INCLUDE_STDIO \
			INCLUDE_FORMATTED_IO \
			INCLUDE_FLOATING_POINT \
			INCLUDE_DEVICE_MANAGER \
			INCLUDE_XBD \
			INCLUDE_XBD_BLK_DEV \
			INCLUDE_XBD_BLK_CACHE \
			INCLUDE_FS_MONITOR \
			INCLUDE_FS_EVENT_UTIL \
			INCLUDE_XBD_TRANS \
			INCLUDE_CDROMFS \
			INCLUDE_DOSFS_MAIN \
			INCLUDE_DOSFS_CACHE \
			INCLUDE_DOSFS_SHOW \
			INCLUDE_HRFS \
			INCLUDE_HRFS_READONLY	\
			INCLUDE_RAWFS \
			INCLUDE_VDFS \
			INCLUDE_HRFS_FORMAT	\
			INCLUDE_UTF \
			INCLUDE_RAMDRV \
			INCLUDE_MEMDRV \
			INCLUDE_MVARDRV \
			INCLUDE_PTYDRV \
			INCLUDE_ROMFS_DRV \
			INCLUDE_ROMFS \
			INCLUDE_RAM_DISK   \
			INCLUDE_LPT \
			INCLUDE_PCMCIA      \
			INCLUDE_TFFS        \
			INCLUDE_TFFS_MOUNT  \
			INCLUDE_EEPROMDRV   \
			INCLUDE_FTL_CACHE   \
			INCLUDE_FTL         \
			INCLUDE_FTL_FORMAT  \
			INCLUDE_FTL_DISCARD \
			INCLUDE_FTL_SHOW \
			INCLUDE_POSIX_PIPES \
			INCLUDE_BOOT_LINE_INIT
}
