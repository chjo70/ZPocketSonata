/* 00comp_ipnet_apps.cdf - IPNet Applications configuration file */

/*
 * Copyright (c) 2013-2015, 2018 Wind River Systems, Inc.
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
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
20feb15,ed   Made configuration file shared by client & server 
11dec14,ed   Added ability to configure TFTPS from a file (F2848)
01jun13,xhs  Created
*/

#ifdef _WRS_CONFIG_COMPONENT_IPAPPL_TFTP

SubProject TFTP_CFGFILE_EXAMPLE {
    NAME        TFTP configuration file example
    SYNOPSIS    Provides the TFTP configuration file example.
    DIRECTORY   tftp_etc
}


Folder FOLDER_TFTP {
    NAME        TFTP
    SYNOPSIS    This folder contains the components for the Trivial File \
                Transfer Protocol (TFTP).
    CHILDREN    INCLUDE_IPTFTP_COMMON \
                INCLUDE_IPTFTPC \
                INCLUDE_IPTFTP_CLIENT_CMD \
                INCLUDE_IPTFTPS \
                INCLUDE_TFTP_CLIENT
    _CHILDREN   FOLDER_NET_L5_APPLICATIONS
}

Component INCLUDE_IPTFTP_COMMON {
    NAME            TFTP common configurations
    SYNOPSIS        Includes common configurations for the Trivial File \
                    Transfer Protocol (TFTP).
    MODULES         iptftp_common.o
    REQUIRES        INCLUDE_IPCOM TFTP_CFGFILE_EXAMPLE
    CONFIGLETTES    iptftps_config.c
    CFG_PARAMS      TFTPS_DIRS TFTPS_RETRANSMIT_TIMEOUT TFTPS_RETRIES \
                    TFTP_CFGFILE TFTPS_DELAYEDSTART \
                    TFTPS_TASK_PRIORITY TFTPS_DEBUG_ENABLE
}

Component INCLUDE_IPTFTPC {
    NAME            TFTP client
    SYNOPSIS        Includes the Trivial File Transfer Protocol (TFTP) client.
    MODULES         iptftpc.o
    REQUIRES        INCLUDE_IPCOM INCLUDE_IPTFTP_COMMON \
                    SELECT_IPCOM_FS
    CONFIGLETTES    iptftpc_config.c
}

Component INCLUDE_IPTFTPS {
    NAME            TFTP server
    SYNOPSIS        Includes the Trivial File Transfer Protocol (TFTP) server.
    MODULES         iptftps.o
    REQUIRES        INCLUDE_IPCOM INCLUDE_IPTFTP_COMMON 
}

/******************** Configuration Parameters *****************************/

/* INCLUDE_IPTFTPS configuration parameters */
Parameter TFTPS_DIRS {
    NAME        TFTP server working directory
    SYNOPSIS    Specifies the working directory for the TFTP server.
    TYPE        char *
    DEFAULT     IPCOM_FILE_ROOT "tftpdir"
}

Parameter TFTPS_RETRANSMIT_TIMEOUT {
    NAME        TFTP retransmit timeout
    SYNOPSIS    Specifies the time until the first retry is sent (in seconds). \
                Further retries use an exponential back-off algorithm.
    TYPE        char *
    DEFAULT     "5"
}

Parameter TFTPS_RETRIES {
    NAME        TFTP number of retries
    SYNOPSIS    Specifies the number of times a TFTP message is \
                retried if an acknowledgment is not received from the peer.
    TYPE        char *
    DEFAULT     "2"
}

Parameter TFTPS_TASK_PRIORITY {
    NAME        Task priority
    SYNOPSIS    This parameter sets the task priority of the Trivial File \
                Transport Protocol (TFTP) server network service task. Changing \
                the value can have risks.
    TYPE        char *
    DEFAULT     "50"
}


Parameter TFTPS_DEBUG_ENABLE {
    NAME        Enable debugging
    SYNOPSIS    To debug the TFTP server network service task, set this value \
                to "1".
    TYPE        char *
    DEFAULT     "0"
}
Parameter TFTP_CFGFILE {
    NAME        TFTP configuration file
    SYNOPSIS    The full path to a target file containing the TFTP  \
                configuration parameters to be processed during system boot \
                or an empty string, which disables this capability.
    TYPE        char *
    DEFAULT     ""
}

Parameter TFTPS_DELAYEDSTART {
    NAME        Delay starting the TFTP server
    SYNOPSIS    Normally, the TFTP server starts when the operating system boots.\
                Setting this parameter to TRUE delays the start of the TFTP \
                server until an "ipd" command is issued.
    TYPE        BOOL
    DEFAULT     FALSE
}


#endif
