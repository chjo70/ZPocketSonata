/* 00comp_ipnet_ntp.cdf - IPNet NTP configuration file */

/*
 * Copyright (c) 2010, 2015, 2017 Wind River Systems, Inc.
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
27jan17,jbm  Editing for consistency, fix protocol names to be uppercase.
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
03Aug10,rjq  New file for Networking Configuration VSB restructuring.
*/

#ifdef _WRS_CONFIG_COMPONENT_IPNTP

Folder FOLDER_NTP {
    NAME            NTP 
    SYNOPSIS        This folder contains components and parameters \
                    that can be used to configure the Network Time Protocol (NTP).
    CHILDREN        INCLUDE_IPNTP \
                    INCLUDE_IPNTP_CMD
    _CHILDREN       FOLDER_NET_L5_APPLICATIONS
}

Component INCLUDE_IPNTP {
    NAME            Network Time Protocol (NTP)
    SYNOPSIS        Adds the NTPv4 module to your system.
    CONFIGLETTES    ipntp_config.c
    _INIT_ORDER     usrNetAppInit
    EXCLUDES        INCLUDE_IPSNTPC INCLUDE_IPSNTPS
    CFG_PARAMS      NTP_INIT_PARAM NTP_CONFIG_PARAM NTP_CONFIG_FILENAME \
                    NTP_TASK_PRIORITY NTP_DEBUG_ENABLE
    REQUIRES        INCLUDE_GETSERVBYNAME INCLUDE_GETADDRINFO INCLUDE_GETNAMEINFO \
                    INCLUDE_IPSNTPC_API INCLUDE_IPSNTP_COMMON
}

/******************** Configuration Parameters *****************************/

/* INCLUDE_IPNTP configuration parameters */
Parameter NTP_INIT_PARAM {
    NAME            Startup parameters
    SYNOPSIS        This parameter specifies the Network Time Protocol (NTP) \
                    startup parameters. \
                    For example, "-c /ram/ntp.conf -g -A".
    TYPE            string
    DEFAULT         NULL
    }

Parameter NTP_CONFIG_PARAM {
    NAME            Configuration parameters
    SYNOPSIS        This parameter specifies the Network Time Protocol (NTP) \
                    configuration parameters typically specified in the \
                    configuration file (for example, /ram0/ntp.conf). This macro \
                    is not used if the configuration file is defined with the \
                    "-c" parameter in NTP_INIT_PARAM, or NTP_CONFIG_FILENAME is \
                    defined. Each parameter must be separated by a semicolon. \
                    For example: \
                    "driftfile /ram/ntp.drift; server 1.debian.pool.ntp.org iburst; \
                    server 2.debian.pool.ntp.org iburst; disable auth"
    TYPE            string
    DEFAULT         NULL
    }

Parameter NTP_CONFIG_FILENAME {
    NAME            Configuration file name
    SYNOPSIS        This parameter specifies the Network Time Protocol (NTP) \
                    configuration file name. This macro is not used if the \
                    configuration file is defined with the "-c" parameter in \
                    NTP_INIT_PARAM. Otherwise, if NTP_CONFIG_FILENAME is defined, \
                    the NTP server reads configuration parameters from this file. \
                    If it is NULL, the NTP server uses NTP_CONFIG_PARAM to boot up.
    TYPE            string
    DEFAULT         NULL
    }

Parameter NTP_TASK_PRIORITY {
    NAME            Task priority
    SYNOPSIS        This parameter sets the task priority of the Network Time \
                    Protocol (NTP) network service task. Changing the value can \
                    have risks.
    TYPE            char *
    DEFAULT         "50"
}


Parameter NTP_DEBUG_ENABLE {
    NAME            Enable debugging
    SYNOPSIS        This parameter enables debugging. To debug the task, set the \
                    value to "1".
    TYPE            char *
    DEFAULT         "0"
}
#endif

