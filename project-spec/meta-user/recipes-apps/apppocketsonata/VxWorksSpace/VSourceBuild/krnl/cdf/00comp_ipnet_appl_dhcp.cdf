/* 00comp_ipnet_apps.cdf - IPNet Applications configuration file */

/*
 * Copyright (c) 2013-2015, 2017-2018 Wind River Systems, Inc.
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
23jan17,jbm  Fixing BOOTP references (change to BOOTP), minor clean up, 
             removed "DHCP" from parameter descriptions for better UI display
05Jan16,wjf  Dhcp use uuid as client id, US71086
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
15dec14,ed   Added ability to read DHCPC config from a file  (F2848)
             Added ability to delay starting the DHCP Client
01jun13,xhs  Created
*/

#ifdef _WRS_CONFIG_COMPONENT_IPAPPL_DHCP

Folder FOLDER_DHCP {
    NAME        DHCP components
    SYNOPSIS    This folder includes the components and parameters required for \
                adding Dynamic Host Configuration Protocol (DHCP) support to your \
                project.
    _CHILDREN   FOLDER_NET_L5_APPLICATIONS
}

SubProject DHCPC_CFGFILE_EXAMPLE {
    NAME        DHCP client configuration file example
    SYNOPSIS    Includes the DHCP client configuration file example.
    DIRECTORY   dhcpc_etc
}

Component INCLUDE_IPDHCPC {
    NAME            DHCP client
    SYNOPSIS        This component includes a DHCP client for your project.
    MODULES         ipdhcpc.o
    CONFIGLETTES    ipdhcpc_config.c ipdhcpc_example.c
    REQUIRES        INCLUDE_IPCOM DHCPC_CFGFILE_EXAMPLE
    CFG_PARAMS      DHCPC_CLIENT_PORT DHCPC_SERVER_PORT DHCPC_REQ_OPTS \
                    DHCPC_CLIENT_ID DHCPC_CLIENT_UUID DHCPC_RFC2131_INIT_DELAY \
                    DHCPC_RFC2131_EXP_BACKOFF DHCPC_DISCOVER_RETRIES \
                    DHCPC_OFFER_TIMEOUT DHCPC_IF_REQ_OPTS_LIST \
                    DHCPC_IF_CLIENT_ID_LIST \
                    DHCPC_INSTALL_OPTION_CALLBACK_HOOK \
                    DHCPC_INSTALL_REPLY_CALLBACK_HOOK \
                    DHCPC_OPTION_CALLBACK_HOOK DHCPC_REPLY_CALLBACK_HOOK \
                    DHCPC_BOOTP_MODE DHCPC_BOOT_FILENAME \
                    DHCPC_SERVER_HOSTNAME DHCPC_OPTION_HOSTNAME \
                    DHCPC_OPTION_NETMASK DHCPC_OPTION_VENDOR_CLASS_ID \
                    DHCPC_OPTION_IPADDRESS_LEASE_TIME \
                    DHCPC_OPTION_VI_VENDOR_CLASS \
                    DHCPC_REMOVE_EXISTING_ADDRESSES \
                    DHCPC_REMOVE_LEASED_ADDRESS \
                    DHCPC_AUTO_DISABLE \
                    DHCPC_TTL \
                    DHCPC_OPTION_MAX_MESSAGE_SIZE \
                    DHCPC_OPTION_USER_SPECIFIED  \
                    DHCPC_IF_INFORMATION_ONLY_LIST \
                    DHCPC_FLAGS_BIT_BROADCAST \
                    DHCPC_TASK_PRIORITY \
                    DHCPC_DEBUG_ENABLE \
                    DHCPC_CFGFILE
    _CHILDREN       FOLDER_DHCP
}

/******************** Configuration Parameters *****************************/

/* INCLUDE_IPDHCPC configuration parameters */
Parameter DHCPC_CLIENT_PORT {
    NAME        Client port
    SYNOPSIS    This parameter specifies the DHCP client port as a quoted string. \
                For example: "68"
    TYPE        char *
    DEFAULT     "68"
}

Parameter DHCPC_SERVER_PORT {
    NAME        Server port
    SYNOPSIS    This parameter specifies the DHCP server port as a quoted string. \
                For example: "67"
    TYPE        char *
    DEFAULT     "67"
}

Parameter DHCPC_RFC2131_INIT_DELAY {
    NAME        RFC 2131 initialization delay identifier
    SYNOPSIS    When set to "1", this parameter enables an RFC 2131 initialization \
                delay identifier. To disable the identifier, set the value to "0".
    TYPE        char *
    DEFAULT     "1"
}

Parameter DHCPC_RFC2131_EXP_BACKOFF {
    NAME        RFC2131 exponential back-off delay
    SYNOPSIS    When set to "1", this parameter enables an RFC 2131 exponential \
                back-off delay. To disable the delay, set the value to "0".
    TYPE        char *
    DEFAULT     "1"
}

Parameter DHCPC_DISCOVER_RETRIES {
    NAME        Client retries
    SYNOPSIS    This parameter sets the number of DHCP client retries.
    TYPE        char *
    DEFAULT     "4"
}

Parameter DHCPC_OFFER_TIMEOUT {
    NAME        Offer time-out
    SYNOPSIS    This parameter sets the DHCP offer time-out value in milliseconds.
    TYPE        char *
    DEFAULT     "2000"
}

Parameter DHCPC_INSTALL_OPTION_CALLBACK_HOOK {
    NAME        Install client option callback routine
    SYNOPSIS    This parameter determines if the user-defined DHCP client \
                callback routine, as specified by the DHCPC_OPTION_CALLBACK_HOOK \
                macro, is installed. If FALSE, the DHCPC_OPTION_CALLBACK_HOOK \
                configuration is not applicable.
    TYPE        BOOL
    DEFAULT     FALSE
}

Parameter DHCPC_OPTION_CALLBACK_HOOK {
    NAME        Option callback routine
    SYNOPSIS    This user-defined DHCP option processing callback routine \
                is called once for each option prior to IPDHCPC acting \
                on the option. That is, this callback can be used to change \
                the contents of the DHCP server reply (caution!). If not \
                specified, the internal option callback routine is \
                used. To install this callback routine, \
                DHCPC_INSTALL_OPTION_CALLBACK_HOOK must also be set to \
                TRUE.
    TYPE        FUNCPTR
    DEFAULT     ipdhcpc_option_default_callback
}

Parameter DHCPC_INSTALL_REPLY_CALLBACK_HOOK {
    NAME        Install client reply callback routine
    SYNOPSIS    This parameter determines if the user-defined DHCP client \
                callback routine, as specified by the DHCPC_REPLY_CALLBACK_HOOK \
                macro, is installed. If FALSE, the DHCPC_REPLY_CALLBACK_HOOK \
                configuration is not applicable.
    TYPE        BOOL
    DEFAULT     FALSE
}

Parameter DHCPC_REPLY_CALLBACK_HOOK {
    NAME        Reply callback routine
    SYNOPSIS    This callback is used to change the contents of the DHCP \
                server reply (caution!). If not specified, the internal reply \
                callback routine is used. To install this callback \
                routine, DHCPC_INSTALL_REPLY_CALLBACK_HOOK must also be \
                set to TRUE.
    TYPE        FUNCPTR
    DEFAULT     ipdhcpc_reply_default_callback
}

Parameter DHCPC_BOOTP_MODE {
    NAME        BOOTP mode
    SYNOPSIS    This parameter indicates that the DHCP client should operate \
                as a BOOTP client only. That is, a DHCP "message type" option \
                is not appended to requests. Set to "1" to enable, "0" to disable.
    TYPE        char *
    DEFAULT     "0"
}

Parameter DHCPC_BOOT_FILENAME {
    NAME        Boot file name
    SYNOPSIS    This parameter specifies an optional file name to use in \
                DHCP/BOOTP requests.
    TYPE        char *
    DEFAULT     ""
}

Parameter DHCPC_SERVER_HOSTNAME {
    NAME        Server host name
    SYNOPSIS    Specifies an optional server host name to use in DHCP/BOOTP \
                requests.
    TYPE        char *
    DEFAULT     ""
}

Parameter DHCPC_IF_REQ_OPTS_LIST {
    NAME        Interface specific option: parameter request list (55)
    SYNOPSIS    This parameter provides An interface name followed by \
                a comma separated list of DHCP option numbers that the \
                DHCP client wants the server to provide in the format \
                <ifparam>=<opts>. Each pair of <ifparam>=<opts> is semicolon \
                separated. For example: "eth0=1,2,3,4;eth1=2,3,4,5".
    TYPE        char *
    DEFAULT     ""
}

Parameter DHCPC_IF_CLIENT_ID_LIST {
    NAME        Interface specific option: client identifier (61)
    SYNOPSIS    This parameter provides a string of characters that the DHCP \
                client wants the server to identify it by in the format \
                <ifparam>=<id>. Each pair of <ifparam>=<id> is semicolon \
                separated. For example: "eth0=my_red_computer_eth0" or \
                "eth0=my_red_computer_eth0;eth1=my_blue_computer_eth1".
    TYPE        char *
    DEFAULT     ""
}

Parameter DHCPC_REQ_OPTS {
    NAME        Global option: parameter request list (55)
    SYNOPSIS    This parameter provides a comma separated list of DHCP option \
                numbers that the DHCP client wants the server to provide. For \
                example: "1,2,3,4"
    TYPE        char *
    DEFAULT     NULL
}

Parameter DHCPC_CLIENT_ID {
    NAME        Global option: client identifier (61)
    SYNOPSIS    This parameter provides a string of characters that the DHCP \
                client wants the server to identify it by. For example: \
                "my_red_computer". If DHCPC_CLIENT_UUID is set "true", it should \
                be defined similar to "4c:5f:00:ff".
    TYPE        char *
    DEFAULT     NULL
}

Parameter DHCPC_CLIENT_UUID {
    NAME        Global option: client identifier type
    SYNOPSIS    This parameter determines if the DHCP client identifier type is \
                uuid. If "false", the DHCPC_CLIENT_ID parameter is treated as a \
                string. If "true", the DHCPC_CLIENT_ID parameter is treated as a \
                character array.
    TYPE        char *
    DEFAULT     "false"
}

Parameter DHCPC_OPTION_HOSTNAME {
    NAME        Global option: hostname (12)
    SYNOPSIS    This parameter defines the hostname option to use in requests.
    TYPE        char *
    DEFAULT     ""
}

Parameter DHCPC_OPTION_NETMASK {
    NAME        Global option: netmask (1)
    SYNOPSIS    This parameter defines the subnet mask option to use in requests.
    TYPE        char *
    DEFAULT     ""
}

Parameter DHCPC_OPTION_IPADDRESS_LEASE_TIME {
    NAME        IP address lease time
    SYNOPSIS    This parameter provides an option that is used in a client \
                request to allow the client to request a lease time for the IP \
                address. A 0 value means no lease time is specified. The time \
                is in units of seconds. 
    TYPE        char *
    DEFAULT     "0"
}

Parameter DHCPC_OPTION_VENDOR_CLASS_ID {
    NAME        Global option: vendor class ID (60)
    SYNOPSIS    This parameter defines the vendor class ID option.
    TYPE        char *
    DEFAULT     ""
}

Parameter DHCPC_OPTION_VI_VENDOR_CLASS {
    NAME        Global option: vendor identifying vendor class (124)
    SYNOPSIS    This parameter defines the vendor identifying vendor class \
                option. Expected format: \
                enterprise_number1=data1;enterprise_number2=data2;... \
                All data fields are specified in network byte order
    TYPE        char *
    DEFAULT     ""
}

Parameter DHCPC_OPTION_MAX_MESSAGE_SIZE {
    NAME        Global option: maximum DHCP message size (57)
    SYNOPSIS    This parameter defines the maximum message size this client is \
                prepared to accept. Per RFC 2131, the value must be at least 576.
    TYPE        char *
    DEFAULT     "576"
}

Parameter DHCPC_OPTION_USER_SPECIFIED {
    NAME        Global option: user-specified list
    SYNOPSIS    This parameter defines a list of options and associated data \
                that are not supported explicitly by other option configuration \
                parameters. Expected format: <option>=<option_data>. \
                Each pair of <option_number>=<option_data> is semicolon separated. \
                In addition, <option_data> must be specified in hex with network \
                byte order. For example, "3=C0A80101;4=C0A80102" specifies a \
                router option (3) with an address at 192.168.1.1 and a time \
                server option (4) with an address at 192.168.1.2.
    TYPE        char *
    DEFAULT     ""
}

Parameter DHCPC_REMOVE_EXISTING_ADDRESSES {
    NAME        Remove existing addresses before negotiation
    SYNOPSIS    This parameter is used to remove all unicast addresses from the \
                interface before negotiation begins. Set to "1" to remove \
                addresses or "0" to retain addresses. 
    TYPE        char *
    DEFAULT     "1"
}

Parameter DHCPC_REMOVE_LEASED_ADDRESS {
    NAME        Remove leased address after expiration
    SYNOPSIS    This parameter is used to remove any leased address from the \
                interface if the lease expires or DHCP is manually disabled. \
                Set to "1" to remove addresses or "0" to retain addresses.
    TYPE        char *
    DEFAULT     "1"
}

Parameter DHCPC_AUTO_DISABLE {
    NAME        Auto disable
    SYNOPSIS    This parameter is used to disable DHCP on the specified interface \
                if another address is subsequently added using manual configuration. \
                Set to "1" to turn on this feature, "0" to turn it off. 
    TYPE        char *
    DEFAULT     "0"
}

Parameter DHCPC_TTL {
    NAME        Time-to-live (TTL)
    SYNOPSIS    This parameter sets the time-to-live for DHCP packets. You can \
                increase this value to interoperate with certain relay agents.
    TYPE        char *
    DEFAULT     "128"
} 

Parameter DHCPC_IF_INFORMATION_ONLY_LIST {
    NAME        Information only interface
    SYNOPSIS    This parameter specifies an interface that only receives \
                information.
    TYPE        char *
    DEFAULT     ""
}

Parameter DHCPC_FLAGS_BIT_BROADCAST {
    NAME        Flag field broadcast bit
    SYNOPSIS    This parameter sets the value of the broadcast bit.
    TYPE        char *
    DEFAULT     "0"
}

Parameter DHCPC_TASK_PRIORITY {
    NAME        Task priority
    SYNOPSIS    This parameter sets the task priority of the \
                Dynamic Host Configuration Protocol version 4 \
                (DHCPv4) client network service task. Changing \
                the value can have risks.
    TYPE        char *
    DEFAULT     "50"
}

Parameter DHCPC_DEBUG_ENABLE {
    NAME        Enable debugging
    SYNOPSIS    This parameter is used to enable debugging. To debug the task, \
                set the value to "1".
    TYPE        char *
    DEFAULT     "0"
}
Parameter DHCPC_CFGFILE {
    NAME        Client configuration file
    SYNOPSIS    This parameter provides the full pathname to a target file \
                containing the DHCP client configuration parameters to be \
                processed during system boot. To disable this capability, \
                set to an empty string. 
    TYPE        char *
    DEFAULT     ""
}

#endif
