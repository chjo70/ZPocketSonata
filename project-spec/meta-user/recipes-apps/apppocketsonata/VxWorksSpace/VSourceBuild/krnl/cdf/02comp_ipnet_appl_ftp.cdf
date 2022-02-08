/* 00comp_ipnet_apps.cdf - IPNet Applications configuration file */

/*
 * Copyright (c) 2013-2018 Wind River Systems, Inc.
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
22Jan18,rjq  Correct SubProject errors. (V7NET-1518)
17may17,rjq  Add new VIP config parameter FTPS_DATABUF_SIZE. (V7NET-1346)
02feb17,jbm  Editing name and synopsis
12oct16,rjq  Support to set priority of FTP session task. (V7NET-1113)
06jun16,rjq  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
22oct15,ljl  Get FTPS TLS private key from secure key db, V7NET-496
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
11dec14,ed   Added ability to configure FTP at runtime from a file (F2848)
01jun13,xhs  Created
*/

#ifdef _WRS_CONFIG_COMPONENT_IPAPPL_FTP

/*
 This uses the KERNEL_SUBPROJECTS capability to copy a sample
 FTP Server config file to the VSB and eventually the VIP
*/

SubProject FTPS_CFGFILE_EXAMPLE {
    NAME        FTP server configuration file example
    SYNOPSIS    Provides the File Transfer Protocol (FTP) server configuration \
                file example.
    DIRECTORY   ftps_etc
}

Folder FOLDER_FTP {
    NAME        FTP 
    SYNOPSIS    This folder includes the components and parameters for File \
                Transfer Protocol (FTP) support. 
    CHILDREN    INCLUDE_FTP \
                INCLUDE_FTP6 \
                INCLUDE_IPFTPC \
                INCLUDE_IPFTPS \
                INCLUDE_IPFTP_CMD \
                INCLUDE_IPFTPS_TLS
    _CHILDREN   FOLDER_NET_L5_APPLICATIONS
}

Component INCLUDE_IPFTPC {
    NAME            FTP client
    SYNOPSIS        This component includes File Transfer Protocol (FTP) client \
                    support. 
    MODULES         ipftpc.o
    REQUIRES        INCLUDE_IPCOM
    CFG_PARAMS      FTPC_BIND_ADDRESS
    CONFIGLETTES    ipftpc_config.c
}

Component INCLUDE_IPFTPS {
    NAME            FTP server
    SYNOPSIS        This component includes File Transfer Protocol (FTP) server \
                    support.
    MODULES         ipftps.o
    REQUIRES        INCLUDE_IPCOM FTPS_CFGFILE_EXAMPLE
    CONFIGLETTES    ipftps_config.c ipftps_example.c
    CFG_PARAMS      FTPS_CFGFILE FTPS_DELAYEDSTART FTPS_AUTH_ATTEMPTS \
                    FTPS_SLEEP_TIME FTPS_LOCAL_PORT_BASE \
                    FTPS_PEER_PORT_BASE FTPS_ENABLE_PROXY FTPS_MODE \
                    FTPS_ROOT_DIR FTPS_INITIAL_DIR FTPS_MAX_SESSIONS \
                    FTPS_PORT_NUM FTPS_RECV_TIMEOUT FTPS_SEND_TIMEOUT \
                    FTPS_INACTIVITY_TIMEOUT FTPS_SOCKET_BACKLOG FTPS_SYS_TYPE \
                    FTPS_AUTH_CALLBACK_HOOK FTPS_TASK_PRIORITY FTPS_DEBUG_ENABLE \
                    FTPS_SESSION_TASK_PRIORITY FTPS_DATABUF_SIZE
}

#ifdef _WRS_CONFIG_IPFTP_USE_TLS
Component INCLUDE_IPFTPS_TLS {
    NAME            FTP server with TLS
    SYNOPSIS        This component includes support for a File Transfer Protocol \
                    (FTP) server with Transport Layer Security (TLS).
    MODULES         ipftps_tls.o
    REQUIRES        INCLUDE_IPFTPS INCLUDE_IPSSL
    CFG_PARAMS      FTPS_TLS FTPS_TLS_CERT_FILE FTPS_TLS_KEY_FILE FTPS_TLS_SECRECT_KEY \
                    ENABLE_ADVANCE_FTPS_KEY_PRIVACY FTPS_TLS_KEY_ID 
    _CHILDREN       FOLDER_FTP
}
#endif
/******************** Configuration Parameters *****************************/
Parameter FTPC_BIND_ADDRESS {
    NAME        Client bind address
    SYNOPSIS    This parameter specifies the bind address for the File Transfer \
                Protocol (FTP) client.
    TYPE        char *
    DEFAULT     NULL
}

/* INCLUDE_IPFTPS configuration parameters */
Parameter FTPS_AUTH_ATTEMPTS {
    NAME        Authentication attempts before disconnect
    SYNOPSIS    This parameter specifies the number of authentication attempts \
                that are allowed before the server disconnects.
    TYPE        char *
    DEFAULT     "3"
}

Parameter FTPS_SLEEP_TIME {
    NAME        Time to sleep after authentication fail
    SYNOPSIS    This parameter defines how many seconds the server sleeps for \
                before replying to an unsuccessful authentication.
    TYPE        char *
    DEFAULT     "5"
}

Parameter FTPS_LOCAL_PORT_BASE {
    NAME        Local port base number
    SYNOPSIS    This parameter specifies the local port base which defines the \
                port range the server uses for the data connection. A value of 0 \
                instructs the server to use port 20.
    TYPE        char *
    DEFAULT     "49151"
}

Parameter FTPS_PEER_PORT_BASE {
    NAME        Peer port base number
    SYNOPSIS    This parameter specifies the peer port base which defines the \
                port range that the client is allowed to use when setting up the \
                data connection.
    TYPE        char *
    DEFAULT     "1023"
}

Parameter FTPS_ENABLE_PROXY {
    NAME        Enable proxy FTP support
    SYNOPSIS    This parameter specifies whether or not to enable proxy File \
                Transfer Protocol (FTP) support.
    TYPE        char *
    DEFAULT     "0"
}

Parameter FTPS_MODE {
    NAME        Read/write mode
    SYNOPSIS    Read-only mode disables write access to the file system, \
                which means that only read commands are accepted. \
                The default value is 0, which allows read/write access.
    TYPE        char *
    DEFAULT     "0"
}

Parameter FTPS_ROOT_DIR {
    NAME        Root directory
    SYNOPSIS    This parameter defines the top-most directory that the client \
                can see.
    TYPE        char *
    DEFAULT     ""
}

Parameter FTPS_INITIAL_DIR {
    NAME        Initial directory
    SYNOPSIS    This parameter defines the initial directory for a File Transfer \
                Protocol (FTP) session.
    TYPE        char *
    DEFAULT     IPCOM_FILE_ROOT
}

Parameter FTPS_CFGFILE {
    NAME        Server configuration file
    SYNOPSIS    This parameter specifies the full pathname to a target file \
                containing the File Transfer Protocol (FTP) server \
                configuration parameters to be processed during system \
                boot, or an empty string to disable this capability. 
    TYPE        char *
    DEFAULT     ""
}

Parameter FTPS_DELAYEDSTART {
    NAME        Delay starting the FTP server
    SYNOPSIS    Normally, the File Transfer Protocol (FTP) server starts when \
                the operating system boots. Setting this parameter to TRUE delays \
                starting the FTP server until a "ipd" command is issued.
    TYPE        BOOL
    DEFAULT     FALSE
}

Parameter FTPS_MAX_SESSIONS {
    NAME        Maximum number of simultaneous sessions
    SYNOPSIS    This parameter specifies the maximum number of simultaneous File \
                Transfer Protocol (FTP) sessions.
    TYPE        char *
    DEFAULT     "8"
}

Parameter FTPS_PORT_NUM {
    NAME        Server port number
    SYNOPSIS    This parameter specifies the server port number.
    TYPE        char *
    DEFAULT     "21"
}

Parameter FTPS_RECV_TIMEOUT {
    NAME        Data receive timeout
    SYNOPSIS    This parameter specifies the timeout in seconds when receiving \
                data from the client.
    TYPE        char *
    DEFAULT     "30"
}

Parameter FTPS_SEND_TIMEOUT {
    NAME        Data send timeout
    SYNOPSIS    This parameter specifies the timeout in seconds when sending data \
                to the client.
    TYPE        char *
    DEFAULT     "30"
}

Parameter FTPS_INACTIVITY_TIMEOUT {
    NAME        User inactivity timeout
    SYNOPSIS    This parameter specifies the timeout in seconds when waiting for \
                a command from the client.
    TYPE        char *
    DEFAULT     "300"
}

Parameter FTPS_SOCKET_BACKLOG {
    NAME        Control socket backlog queue
    SYNOPSIS    This parameter determines the backlog queue length of the File \
                Transfer Protocol (FTP) server control socket. The default value \
                is 0.
    TYPE        char *
    DEFAULT     "0"
}

Parameter FTPS_SYS_TYPE {
    NAME        Reported system type
    SYNOPSIS    This parameter specifies the operating system name.
    TYPE        char *
    DEFAULT     "UNIX"
}

Parameter FTPS_AUTH_CALLBACK_HOOK {
    NAME        Authentication callback routine
    SYNOPSIS    This parameter specifies a user-defined authentication callback \
                routine to be used by the File Transfer Protocol (FTP) server. If \
                not specified, the internal authentication callback routine, \
                ipftps_authenticate_default_callback, is used. 
    TYPE        FUNCPTR
    DEFAULT     ipftps_authenticate_default_callback
}

Parameter FTPS_TASK_PRIORITY {
    NAME        Task priority
    SYNOPSIS    This parameter sets the task priority of the File Transfer \
                Protocol (FTP) server network service task. Changing the value \
                can have risks.
    TYPE        char *
    DEFAULT     "50"
}

Parameter FTPS_SESSION_TASK_PRIORITY {
    NAME        FTPS session task priority
    SYNOPSIS    This parameter sets the priority of the File Transfer Protocol \
                (FTP) session task. Changing this value can have risks. 
    TYPE        char *
    DEFAULT     "50"
}

Parameter FTPS_DEBUG_ENABLE {
    NAME        Enable debugging
    SYNOPSIS    This parameter enables debugging. To debug the task, set the \
                value to "1".
    TYPE        char *
    DEFAULT     "0"
}

Parameter FTPS_DATABUF_SIZE {
    NAME        Data transfer buffer size
    SYNOPSIS    Data transfer buffer size used in each FTP session
    TYPE        char *
    DEFAULT     "4096"
}

#ifdef _WRS_CONFIG_IPFTP_USE_TLS

Parameter ENABLE_ADVANCE_FTPS_KEY_PRIVACY {
    NAME        Enable the advance option for FTPS key privacy 
    SYNOPSIS    If this value is set to "1", get the private key from a secure \
                key database using the key ID defined in FTPS_TLS_KEY_ID. If set \
                to "0", get the private key from FTPS_TLS_KEY_FILE, which is \
                stored in clear-text. If you want to use the key database, you \
                must include INCLUDE_IPCOM_USE_KEY_DB.
    REQUIRES    
    TYPE        char *
    DEFAULT     "0"
}

Parameter FTPS_TLS_KEY_ID {
    NAME        TLS key ID
    SYNOPSIS    This parameter specifies the key ID used to fetch the server \
                Transport Layer Security (TLS) key from a secure key database. \
                To use this feature, ENABLE_ADVANCE_FTPS_KEY_PRIVACY must be set \
                to "1".
    REQUIRES    INCLUDE_IPCOM_USE_KEY_DB
    TYPE        char *
    DEFAULT     ""
}

Parameter FTPS_TLS_KEY_FILE {
    NAME        TLS key file
    SYNOPSIS    This parameter specifies the Transport Layer Security (TLS) file. \
                To use this feature, ENABLE_ADVANCE_FTPS_KEY_PRIVACY must be set \
                to "0".
    REQUIRES    INCLUDE_IPSSL
    TYPE        char *
    DEFAULT     ""
}

Parameter FTPS_TLS_CERT_FILE {
    NAME        TLS certificate file
    SYNOPSIS    This parameter specifies the file name of the Transport Layer \
                Security (TLS) certificate file.
    REQUIRES    INCLUDE_IPSSL
    TYPE        char *
    DEFAULT     ""
}

Parameter FTPS_TLS {
    NAME        Enable FTP server with TLS
    SYNOPSIS    This parameter enables a File Transfer Protocol (FTP) server with \
                Transport Layer Security (TLS) support.
    REQUIRES    INCLUDE_IPSSL
    TYPE        char *
    DEFAULT     "0"
}

Parameter FTPS_TLS_SECRECT_KEY {
    NAME        TLS secret key
    SYNOPSIS    This parameter specifies the file name for the Transport Layer \
                Security (TLS) secret key file.
    REQUIRES    INCLUDE_IPSSL
    TYPE        char *
    DEFAULT     ""
}

#endif

#endif
