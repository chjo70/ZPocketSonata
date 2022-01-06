/* 00comp_ipcom.cdf - IPCom Component configuration file */

/*
 * Copyright (c) 2006-2010, 2012, 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
07dec16,mca  Break hard dependency between END and IPNET. (US85582)
09jul16,rjq  Add telnet idle timeout parameter.  (V7NET-862)
29jun16,jxy  Change default value of ipcom.telnet.max_sessions to 10, (V7NET-858)
26may16,dlk  Adapt for RTNET stack.
10mar16,r_w  Move ipcom_cfgfile.c out of prjConfig.c compiler unit to ipcom(V7COR-4114)
30mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
24nov14,ed   Added ability to read TELNET configuration from file. (F2848)
18nov14,ed   Added ipcom_cfgfile.c to INCLUDE_IPCOM for sysvar config file
             parser.
27feb14,dlk  The network stack now requires INCLUDE_TLS.
11feb14,pad  Removed all elements related to the IPCOM user authentication
             (issue VXW7-1677).
13mar08,rjq Detach INCLUDE_SHELL from TELNETS and SSH
12nov12,j_y Added IPCOM_USER_SHELL_FUNCTION
12nov12,rjq Change the default user ID to be 0xFFFFFFFF.
02feb12,lzq Added INCLUDE_USE_WAITIF
19aug10,ggz Added SHA256 hash and salt support
08jun09,ggz Fix for defect WIND00167365
01may09,ggz Added hashing capability for ipcom auth
17apr09,rme Removed INCLUDE_USE_NATIVE_SHELL dependency on
            INCLUDE_SHELL_INTERP_CMD.
03Sep08,brg Added ipcom_drv_mux.o for custom ARP hook support.
10sep07,mze INCLUDE_IPCOM_FS_SELECTION changed to SELECT_IPCOM_FS
04jul07,rme Replaced INCLUDE_IPCOM_SHELL_SELECTION with FOLDER_SHELLS
            Also updated 00comp_ipnet_apps.cdf INCLUDE_IPTELNETS
07feb07,tkf Added INCLUDE_USE_NATIVE_SHELL dependency on
            INCLUDE_SHELL_INTERP_CMD.
29jan07,tkf Added INCLUDE_USE_NATIVE_SHELL and INCLUDE_IPCOM_SHELL_SELECTION.
            Also changed some component attributes of INCLUDE_USE_IPCOM_SHELL.
20jan07,tkf Remove dependency on INCLUDE_XBD_RAMDRV Not required (WIND00085813).
19jan07,tkf Add INCLUDE_IPCOM_USE_RAM_DISK (WIND00085813).
08jan07,kch Added ipcom_ipd_config.c configlette to INCLUDE_IPCOM.
08jan07,kch Removed duplicate ipcom_config.c configlette from
            INCLUDE_IPCOM_USE_AUTH.
07jan07,tkf Adjust INCLUDE_IPCOM_USE_VXSHELL_CMD component to accomodate
            changes in latest code drop.
13dec06,tkf INCLUDE_IPCOM_USE_VXSHELL_CMD.
23sep06,kch Moved INCLUDE_IPCOM_USE_AUTH_RADIUS to 02comp_ipnet_radius.cdf.
28aug06,kch Added SELECT_IPCOM_AUTHENTICATION to corrected IPCom
            authentication configuration support.
11aug06,tkf Remove INCLUDE_USE_IPCOM_SHELL dependency requirement on
            INCLUDE_IPTELNETS.
10aug06,kch Moved syslogd to 'IPNet Shell Commands' folder.
02jul06,kch Added ipcom_drv_eth.o module to INCLUDE_IPCOM component.
30jun06,dlk Added INCLUDE_IPCOM_USE_SYSLOGD.
25jun06,dlk Make INCLUDE_IPCOM require INCLUDE_SOCKLIB and
            INCLUDE_COMMON_NET. Specify initialization order for
            INCLUDE_IPCOM in 00init_usernetwork.cdf, not here.
22may06,kch created.
*/

Component INCLUDE_IPCOM {
    NAME            VxWorks IPCOM
    SYNOPSIS        Includes VxWorks IPCOM support.
    MODULES         ipcom_vxworks.o ipcom_drv_eth.o ipcom_drv_mux.o ipcom_cfgfile.o
    CONFIGLETTES    ipcom_config.c ipcom_ipd_config.c
    LINK_SYMS       ipcom_register_dev_name_mapping ipcom_cfgfile_parse
    INIT_RTN	    ipcom_config_create ();
    REQUIRES	    INCLUDE_IPCOM_USR \
                    INCLUDE_IPNET \
                    INCLUDE_TLS
    CFG_PARAMS      IPCOM_ENABLE_USER_SHELL \
                    IPCOM_START_SHELL
}

Parameter IPCOM_ENABLE_USER_SHELL {
    NAME        IPCOM user shell
    SYNOPSIS    Use this Boolean parameter to enable the IPCOM user shell. It is set to false by default.
    TYPE        BOOL
    DEFAULT     FALSE
}

Parameter IPCOM_START_SHELL {
    NAME        IPCOM user start shell function
    SYNOPSIS    Specifies the IPCOM user start shell function.
    TYPE        FUNCPTR
    DEFAULT     NULL
}

Component INCLUDE_USE_IPCOM_SHELL {
    NAME            IPCOM-specific shell
    SYNOPSIS        Specifies the use of the IPCOM-specific shell.
    MODULES         ipcom_shell.o
    LINK_SYMS       ipcom_start_shell
    REQUIRES        INCLUDE_IPCOM
    CFG_PARAMS      IPCOM_SHELL_PROMPT
}

Component INCLUDE_USE_NATIVE_SHELL {
    NAME            Native VxWorks shell
    SYNOPSIS        Specifies the use of the native VxWorks shell.
    MODULES         ipcom_pshell.o
    LINK_SYMS       ipcom_start_shell_native
    REQUIRES        INCLUDE_IPCOM INCLUDE_SHELL INCLUDE_SHELL_INTERP_CMD
    CFG_PARAMS      IPCOM_SHELL_PROMPT
}

Component INCLUDE_IPCOM_USE_VXSHELL_CMD {
    NAME            IPCOM VxShell command
    SYNOPSIS        Includes the IP shell command to enter the VxWorks shell. The command blocks \
                    until the VxWorks shell exits.
    MODULES         ipcom_cmd_vxshell.o
    LINK_SYMS       ipcom_cmd_vxshell
    REQUIRES        INCLUDE_SHELL
}

Selection SELECT_IPCOM_SHELL {
        NAME            Select the shell type
        SYNOPSIS        Selects the shell type to use, either the native or the IPCOM shell.
        COUNT           1-1
        CHILDREN        INCLUDE_USE_IPCOM_SHELL \
                        INCLUDE_USE_NATIVE_SHELL
        DEFAULTS        INCLUDE_USE_NATIVE_SHELL
}

Component INCLUDE_IPCOM_USE_RAM_DISK {
    NAME            IPCOM RAM disk support
    SYNOPSIS        Initializes the VxWorks RAM disk.
    MODULES         ipcom_ramdisk.o
    LINK_SYMS       vxfs_ramdisk_init
}

Component INCLUDE_IPCOM_FS_IPCOM {
    NAME            IPCOM-specific file system
    SYNOPSIS        Specifies that IPCOM uses the IPCOM-specific file system.
    MODULES         ipcom_file.o
    LINK_SYMS       ipcom_file_proc_exit
}

Component INCLUDE_IPCOM_FS_NATIVE {
    NAME            Native VxWorks file system
    SYNOPSIS        Specifies that IPCOM uses the native VxWorks file system.
    REQUIRES        INCLUDE_IPCOM_USE_RAM_DISK
}

Selection SELECT_IPCOM_FS {
        NAME            IPCOM file system type
        SYNOPSIS        Selects which file system IPCOM uses.
        COUNT           1-1
        CHILDREN        INCLUDE_IPCOM_FS_NATIVE \
                        INCLUDE_IPCOM_FS_IPCOM
        DEFAULTS        INCLUDE_IPCOM_FS_NATIVE
}

SubProject TELNETS_CFGFILE_EXAMPLE {
    NAME        Telnet server configuration file example
    SYNOPSIS    Provides the telnet server configuration file example.
    DIRECTORY   etc
}

Component INCLUDE_IPTELNETS {
    NAME            Telnet server
    SYNOPSIS        Includes the telnet server components.
    MODULES         ipcom_telnet.o
    REQUIRES        INCLUDE_IPCOM INCLUDE_IPNET TELNETS_CFGFILE_EXAMPLE
    _CHILDREN       FOLDER_TELNET
    CONFIGLETTES    ipcom_telnets_config.c
    CFG_PARAMS      IPCOM_TELNET_PORT IPCOM_TELNET_MAX_CLIENTS \
                    IPCOM_TELNET_CFGFILE IPCOM_TELNET_DELAYEDSTART \
                    IPCOM_TELNET_TASK_PRIORITY IPCOM_TELNET_DEBUG_ENABLE \
                    IPCOM_TELNET_IDLE_TIMEOUT
}


Component INCLUDE_IPCOM_USR {
    NAME            IPCOM user side functions
    SYNOPSIS        Includes the IPCOM user-side functions.
    INIT_RTN        ipcom_config_usr_create ();
    _CHILDREN       FOLDER_NOT_VISIBLE
}


Component INCLUDE_USE_WAITIF {
    NAME        Wait for an available address
    SYNOPSIS    Waits for an address at VxWorks startup.
    MODULES     ipcom_waitif.o
    INIT_RTN    ipcom_waitif_address ();
    REQUIRES    INCLUDE_IPCOM
    _CHILDREN   FOLDER_NET_CORE
}


/******************** Configuration Parameters *****************************/

/* INCLUDE_USE_IPCOM_SHELL configuration parameters */

Parameter IPCOM_SHELL_PROMPT {
    NAME        IPCOM shell prompt
    SYNOPSIS    The prompt displayed by the shell when it is waiting for \
                commands. Supported special characters are: \
                "\p" - shell process name \
                "\P" - shell process ID \
                "\i" - the IP address of the target \
                "\w" - the current working directory \
                "\W" - the basename of the current working directory \
                "\V" - ipcom_getenv("VR")
    TYPE        char *
    DEFAULT     "\\i$\\w>"
}

/* INCLUDE_IPTELNETS configuration parameters */
Parameter IPCOM_TELNET_PORT {
    NAME        IPCOM telnet port
    SYNOPSIS    Specifies the telnet server port in the host endian.
    TYPE        char *
    DEFAULT     "23"
}

Parameter IPCOM_TELNET_MAX_CLIENTS {
    NAME        Maximum number of simultaneous telnet clients
    SYNOPSIS    IPCOM_TELNET_MAX_CLIENTS controls the maximum number of simultaneous \
                telnet clients. If set to 0, the number is unlimited.
    TYPE        char *
    DEFAULT     "10"
}
Parameter IPCOM_TELNET_TASK_PRIORITY {
    NAME        Task priority
    SYNOPSIS    This parameter sets the task priority of the telnet network service \
                task. Changing the value can have risks.
    TYPE        char *
    DEFAULT     "50"
}


Parameter IPCOM_TELNET_DEBUG_ENABLE {
    NAME        Enable debugging
    SYNOPSIS    To debug the telnet network service task, set the value to "1".
    TYPE        char *
    DEFAULT     "0"
}

Parameter IPCOM_TELNET_CFGFILE {
    NAME        Telnet configuration file
    SYNOPSIS    The full pathname to a file containing telnet configuration  \
                parameters to be processed during system boot, or an empty string, \
                which disables this capability.
    TYPE        char *
    DEFAULT     ""
}

Parameter IPCOM_TELNET_DELAYEDSTART {
    NAME        Delays telnet server start
    SYNOPSIS    Normally, the telnet server starts when the operating system boots.\
                Setting this value to TRUE delays starting the telnet server \
                until an "ipd" command is issued.
    TYPE        BOOL
    DEFAULT     FALSE
}

Parameter IPCOM_TELNET_IDLE_TIMEOUT {
    NAME        Telnet client idle timeout
    SYNOPSIS    Specifies the idle timeout, in minutes, for a telnet client. A telnet \
                client is automatically logged out if no input is detected for the \
                specified amount of time. Specifying a timeout value of 0 dictates that
                the telnet client never times out due to inactivity.
    TYPE        char *
    DEFAULT     "360"
}
