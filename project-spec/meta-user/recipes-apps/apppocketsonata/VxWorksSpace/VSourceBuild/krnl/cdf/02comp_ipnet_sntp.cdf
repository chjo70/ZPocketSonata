/* 00comp_ipnet_sntp.cdf - IPNet SNTP configuration file */

/*
 * Copyright (c) 2010, 2015-2017 Wind River Systems, Inc.
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
27jan17,jbm  Fix capitalization for protocol names, general editing
25may16,rjq  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
03Aug10,rjq  New file for Networking Configuration VSB restructuring.
*/

#ifdef _WRS_CONFIG_COMPONENT_IPSNTP

Folder FOLDER_SNTP {
    NAME        SNTP 
    SYNOPSIS    This folder contains the components for the Simple Network Time \
                Protocol (SNTP).
    CHILDREN    INCLUDE_IPSNTP_COMMON \
                INCLUDE_IPSNTPC_API \
                INCLUDE_IPSNTPS_API \
                INCLUDE_IPSNTPC\
                INCLUDE_IPSNTPS \
                INCLUDE_IPSNTP_CMD
    _CHILDREN   FOLDER_NET_L5_APPLICATIONS
}

Component INCLUDE_IPSNTP_COMMON {
    NAME            SNTP common configurations
    SYNOPSIS        This component includes the Simple Network Time Protocol \
                    (SNTP) common configurations.
    CONFIGLETTES    ipsntp_config.c
    MODULES         ipsntp.o
    LINK_SYMS       ipsntp_create
    REQUIRES        INCLUDE_IPCOM
    CFG_PARAMS      SNTP_LISTENING_PORT \
                    SNTP_BIND_IPV6_ADDR \
                    SNTP_BIND_IPV4_ADDR \
                    SNTP_TASK_PRIORITY \
                    SNTP_DEBUG_ENABLE
}

Component INCLUDE_IPSNTPS {
    NAME            Server daemon
    SYNOPSIS        This component includes the Simple Network Time Protocol \
                    (SNTP) server daemon.
    REQUIRES        INCLUDE_IPSNTP_COMMON
    LINK_SYMS       ipsntp_set_reference
    EXCLUDES        INCLUDE_IPSNTPC
    CFG_PARAMS      SNTPS_STRATUM SNTPS_PRECISION SNTPS_MULTICAST_INTERVAL \
                    SNTPS_MULTICAST_TTL SNTPS_IPV4_MULTICAST_ADDR \
                    SNTPS_IPV6_MULTICAST_ADDR SNTPS_LEAP_SECOND_FILENAME
}

Component INCLUDE_IPSNTPC {
    NAME            Client daemon
    SYNOPSIS        This component includes the Simple Network Time Protocol \
                    (SNTP) client daemon.
    REQUIRES        INCLUDE_IPSNTP_COMMON
    LINK_SYMS       ipsntp_set_reference
    EXCLUDES        INCLUDE_IPSNTPS
    CFG_PARAMS      SNTPC_POLL_INTERVAL SNTPC_POLL_COUNT SNTPC_POLL_TIMEOUT \
                    SNTPC_PRIMARY_IPV4_ADDR SNTPC_BACKUP_IPV4_ADDR \
                    SNTPC_MULTICAST_MODE_IF SNTPC_MULTICAST_GROUP_ADDR \
                    SNTPC_PRIMARY_IPV6_ADDR SNTPC_BACKUP_IPV6_ADDR \
                    SNTPC_MULTICAST_MODE_IPV6_IF \
                    SNTPC_MULTICAST_GROUP_IPV6_ADDR
}

Component INCLUDE_IPSNTPC_API {
    NAME            Client API
    SYNOPSIS        This component includes the Simple Network Time Protocol \
                    (SNTP) client routines.
    LINK_SYMS       ipsntp_query_time
    REQUIRES        INCLUDE_IPSNTP_COMMON
}

Component INCLUDE_IPSNTPS_API {
    NAME            Server API
    SYNOPSIS        This component includes the Simple Network Time Protocol \
                    (SNTP) server routines.
    LINK_SYMS       ipsntp_server_nsec_to_fraction \
                    ipsntp_set_reference
    REQUIRES        INCLUDE_IPSNTP_COMMON \
                    INCLUDE_IPSNTPS
}

/******************** Configuration Parameters *****************************/

/* INCLUDE_IPSNTP_COMMON configuration parameters */
Parameter SNTP_LISTENING_PORT {
    NAME        Listening port
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                listening port.
    TYPE        char *
    DEFAULT     "123"
}

Parameter SNTP_BIND_IPV4_ADDR {
    NAME        IPv4 source address
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                IPv4 source address.
    TYPE        char *
    DEFAULT     ""
}

Parameter SNTP_BIND_IPV6_ADDR {
    NAME        IPv6 source address
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                IPv6 source address.
    TYPE        char *
    DEFAULT     ""
}

/* INCLUDE_IPSNTPS configuration parameters */
Parameter SNTPS_LEAP_SECOND_FILENAME {
    NAME        Leap second file name
    SYNOPSIS    This parameter specifies the name of leap second file to be read \
                by the Simple Network Time Protocol (SNTP) server \
                every day. The file contains the leap second to be adjusted \
                in NTP timestamp format. \
                For example, "3644697600    36    # 1 Jul 2015". \
                If there is a leap second adjustment, the SNTP server sets \
                the LI flag automatically in that day. Contents of this file \
                can be derived from leap-second bulletins posted by the \
                International Earth Rotation and Reference Systems Service (IERS).
    TYPE        char *
    DEFAULT     NULL
}

Parameter SNTPS_STRATUM {
    NAME        Server stratum
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                server stratum.
    TYPE        char *
    DEFAULT     "9"
}

Parameter SNTPS_PRECISION {
    NAME        Server precision
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                server precision. Precision, in seconds, is \
                2 ^ SNTPS_PRECISION.
    TYPE        char *
    DEFAULT     "-6"
}

Parameter SNTPS_MULTICAST_INTERVAL {
    NAME        Multicast mode send interval
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                multicast mode send interval in seconds. For unicast mode only, \
                set this value to zero.
    TYPE        char *
    DEFAULT     "3600"
}

Parameter SNTPS_MULTICAST_TTL {
    NAME        Multicast mode TTL
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                multicast mode time-to-live (TTL).
    TYPE        char *
    DEFAULT     "1"
}

Parameter SNTPS_IPV4_MULTICAST_ADDR {
    NAME        Multicast mode IPv4 destination address
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                server multicast mode IPv4 destination address.
    TYPE        char *
    DEFAULT     "10.1.255.255"
}

Parameter SNTPS_IPV6_MULTICAST_ADDR {
    NAME        Multicast mode IPv6 destination address
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                server multicast mode IPv6 destination address.
    TYPE        char *
    DEFAULT     "FF05::1"
}

/* INCLUDE_IPSNTPC configuration parameters */
Parameter SNTPC_POLL_INTERVAL {
    NAME        Unicast client mode poll interval
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                client unicast mode poll interval. For multicast mode only, set \
                this value to zero.
    TYPE        char *
    DEFAULT     "1024"
}

Parameter SNTPC_POLL_COUNT {
    NAME        Number of retransmissions
    SYNOPSIS    This parameter specifies the number of re-transmissions the client \
                attempts on each Simple Network Time Protocol (SNTP) server.
    TYPE        char *
    DEFAULT     "3"
}

Parameter SNTPC_POLL_TIMEOUT {
    NAME        Seconds between retransmissions
    SYNOPSIS    This parameter specifies the number of seconds between \
                re-transmission attempts. The default value is two seconds.
    TYPE        char *
    DEFAULT     "2"
}

Parameter SNTPC_PRIMARY_IPV4_ADDR {
    NAME        Primary server IPv4 address
    SYNOPSIS    This parameter specifies the IPv4 address of the primary Simple \
                Network Time Protocol (SNTP) server.
    TYPE        char *
    DEFAULT     "10.1.2.90"
}

Parameter SNTPC_BACKUP_IPV4_ADDR {
    NAME        Backup server IPv4 address
    SYNOPSIS    This parameter specifies the IPv4 address of the Simple Network \
                Time Protocol (SNTP) backup server.
    TYPE        char *
    DEFAULT     "10.1.2.40"
}

Parameter SNTPC_MULTICAST_MODE_IF {
    NAME        Multicast client mode interface
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                multicast client mode interface.
    TYPE        char *
    DEFAULT     ""
}

Parameter SNTPC_MULTICAST_GROUP_ADDR {
    NAME        Multicast client mode multicast group
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                multicast client mode multicast group.
    TYPE        char *
    DEFAULT     "224.0.1.1"
}

Parameter SNTPC_PRIMARY_IPV6_ADDR {
    NAME        Primary server IPv6 address
    SYNOPSIS    This parameter specifies the IPv6 address of the primary Simple \
                Network Time Protocol (SNTP) server.
    TYPE        char *
    DEFAULT     "2001::90"
}

Parameter SNTPC_BACKUP_IPV6_ADDR {
    NAME        Backup server IPv6 address
    SYNOPSIS    This parameter specifies the IPv6 address of the Simple Network \
                Time Protocol (SNTP) backup server.
    TYPE        char *
    DEFAULT     "2001::28"
}

Parameter SNTPC_MULTICAST_MODE_IPV6_IF {
    NAME        Multicast client mode IPv6 interface
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                multicast client mode IPv6 interface.
    TYPE        char *
    DEFAULT     ""
}

Parameter SNTPC_MULTICAST_GROUP_IPV6_ADDR {
    NAME        Multicast client mode IPv6 multicast group
    SYNOPSIS    This parameter specifies the Simple Network Time Protocol (SNTP) \
                multicast client mode IPv6 multicast group.
    TYPE        char *
    DEFAULT     "ff05::101"
}

Parameter SNTP_TASK_PRIORITY {
    NAME        Task priority
    SYNOPSIS    This parameter sets the task priority of the Simple Network \
                Time Protocol (SNTP) network service task. Changing the value \
                can have risks.
    TYPE        char *
    DEFAULT     "50"
}


Parameter SNTP_DEBUG_ENABLE {
    NAME        Enable debugging
    SYNOPSIS    This parameter enables debugging. To debug the Simple Network \
                Time Protocol (SNTP) network service task, set this value to "1".
    TYPE        char *
    DEFAULT     "0"
}
#endif

