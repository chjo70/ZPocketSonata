/* 00comp_ipnet_ppp.cdf - IPNet PPP configuration file */

/*
 * Copyright (c) 2006-2008, 2014-2016 Wind River Systems, Inc.
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
24may16,h_x  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
14feb14,zan  decouple cdf dependency, move FOLDER_NET_PPP to 00comp_ipnet_ppp.cdf
23apr08,rme  General misspelled words
19sep07,rme  Added missing backslash (line: 194)
22jan07,kch  Added configuration parameters for PPP username and password
                 (WIND00085576).
10jan07,kch  Updated default value for PPP_IPCP_PEER_IPV4_ADDRESS and
                 PPP_IPCP_PEER_IPV4_ADDRESS_POOL.
04jan07,kch  Updated default value for PPP_DEFAULT_BAUDRATE,
                 PPP_AUTH_MODES, PPPOE_SERVER and PPPOE_SERVICE_NAME. Removed
                 PPPOE_IF_MAX_SESSIONS_LIST configuration parameter.
12dec06,kch  Added PPP_INSTALL_CALLBACK_HOOK configuration parameter
                 to INCLUDE_IPPPP.
01dec06,kch  Added PPP_ACTION_CALLBACK_HOOK parameter and ipppp_example.c
                 configlette  to INCLUDE_IPPPP.
27nov06,kch  Only define ipppp configlette once in INCLUDE_IPPPP.
23sep06,kch  Fixed IPCOM shell commands description.
17sep06,kch  created.
*/


Folder FOLDER_NET_PPP {
    NAME        PPP Components
    SYNOPSIS    Point-to-Point Protocol (PPP) allows the establishment, authentication, and control of PPP connections and PPP over Ethernet (PPPoE) implementations. Formore information, please refer to the VxWorks 7 PPP Programmer's Guide.
    CHILDREN    INCLUDE_IPPPP \
                INCLUDE_IPPPPOE \
                INCLUDE_IPPPPMP \
                INCLUDE_IPPPP_VJCOMP \
                SELECT_IPPPP_OPTIONAL_CONFIG \
                INCLUDE_IPPPP_CMD
    _CHILDREN   FOLDER_NET_L2_LINK			
}

Component INCLUDE_IPPPP {
    NAME            PPP
    SYNOPSIS        PPP
    MODULES         ipppp.o
    REQUIRES        INCLUDE_IPNET_USE_PPP
    CONFIGLETTES    ipppp_config.c ipppp_example.c
    CFG_PARAMS      PPP_DEFAULT_BAUDRATE PPP_RUNMODE PPP_FLAGS PPP_AUTH_MODES \
                    PPP_LCP_MRU PPP_LCP_MTU PPP_LCP_ECHO_REQ_INTERVAL \
                    PPP_LCP_ECHO_REQ_FAILURE PPP_IPCP_IPV4_ADDRESS \
                    PPP_IPCP_PEER_IPV4_ADDRESS PPP_IPCP_PEER_IPV4_POOL_NAME \
                    PPP_IPCP_PEER_IPV4_ADDRESS_POOL \
                    PPP_USERNAME PPP_PASSWD \
                    PPP_IPCP_PRIMARY_DNS_ADDRESS \
                    PPP_IPCP_SECONDARY_DNS_ADDRESS \
                    PPP_IPCP_PRIMARY_NBNS_ADDRESS \
                    PPP_IPCP_SECONDARY_NBNS_ADDRESS \
                    PPP_L2TP_LNS_ADDRESS_DEFAULT \
                    PPP_INSTALL_CALLBACK_HOOK PPP_ACTION_CALLBACK_HOOK \
                    PPP_LCP_CLOSE_IF_NO_NCP_OPENED \
                    PPP_TASK_PRIORITY PPP_DEBUG_ENABLE
}

Selection SELECT_IPPPP_OPTIONAL_CONFIG {
    NAME            Optional IPPP configurations
    SYNOPSIS        Optional IPPP configurations
    COUNT           0-
    CHILDREN        INCLUDE_IPPPP_INTERFACE_CONFIG \
                    INCLUDE_IPPPP_USERS_CONFIG
}

Component INCLUDE_IPPPP_INTERFACE_CONFIG {
    NAME            Per-interface configurations
    SYNOPSIS        Include the interface configuration parameters for PPP.
    REQUIRES        INCLUDE_IPPPP
    CFG_PARAMS      PPP_IF_DEFAULT_BAUDRATE_LIST PPP_IF_RUNMODE_LIST \
                    PPP_IF_FLAGS_LIST PPP_IF_AUTH_MODES_LIST \
                    PPP_IF_USERNAME PPP_IF_PASSWD \
                    PPP_IF_LCP_MRU_LIST PPP_IF_LCP_MTU_LIST \
                    PPP_IF_LCP_ECHO_REQ_INTERVAL_LIST \
                    PPP_IF_LCP_ECHO_REQ_FAILURE_LIST \
                    PPP_IF_IPCP_IPV4_ADDRESS_LIST \
                    PPP_IF_IPCP_PEER_IPV4_ADDRESS_LIST \
                    PPP_IF_IPCP_PEER_IPV4_ADDRESS_POOL_LIST \
                    PPP_IF_IPCP_PRIMARY_DNS_ADDRESS_LIST \
                    PPP_IF_IPCP_SECONDARY_DNS_ADDRESS_LIST
}

Component INCLUDE_IPPPP_USERS_CONFIG {
    NAME            Per-user configurations
    SYNOPSIS        Per-user configurations
    REQUIRES        INCLUDE_IPPPP
    CFG_PARAMS      PPP_USERS_LCP_ECHO_REQ_INTERVAL_LIST \
                    PPP_USERS_IPCP_IPV4_ADDRESS_LIST \
                    PPP_USERS_IPCP_PEER_IPV4_ADDRESS_LIST \
                    PPP_USERS_IPCP_PEER_IPV4_ADDRESS_POOL_LIST \
                    PPP_USERS_IPCP_PRIMARY_DNS_ADDRESS_LIST \
                    PPP_USERS_IPCP_SECONDARY_DNS_ADDRESS_LIST
}

Component INCLUDE_IPPPPOE {
    NAME            PPPoE
    SYNOPSIS        Include the point-to-point protocol over Ethernet.
    REQUIRES        INCLUDE_IPNET_USE_PPP INCLUDE_IPCOM_USE_ETHERNET \
                    INCLUDE_IPPPP
    MODULES         ipppp_pppoe.o
    LINK_SYMS       ipppp_pppoe_input
    CFG_PARAMS      PPPOE_SERVER PPPOE_SECRET_NAME PPPOE_MAX_SESSIONS \
                    PPPOE_MAX_ETH_SESSIONS PPPOE_AC_NAME PPPOE_SERVICE_NAME \
                    PPPOE_IF_MAX_ETH_SESSIONS_LIST \
                    PPPOE_IF_SERVICE_NAME_LIST
}

Component INCLUDE_IPPPP_CMD {
    NAME        PPP IPCOM commands
    SYNOPSIS    Include the PPP configuration shell command
(pppconfig).
    MODULES     ipppp_cmd_pppconfig.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPPPP
}

Component INCLUDE_IPPPPMP {
    NAME            PPP Multilink Protocol
    SYNOPSIS        Include PPP multilink protocol in your VIP.
    REQUIRES        INCLUDE_IPPPP
    MODULES         ipppp_pppmp.o
    LINK_SYMS       ipppp_pppmp_input
    CFG_PARAMS      PPPMP_ENABLE PPPMP_MRRU PPPMP_SSN PPPMP_FRAG_DISABLE PPPMP_PPPOE_LINKS
}

Component INCLUDE_IPPPP_VJCOMP {
    NAME            PPP Van Jacobson Compression
    SYNOPSIS        This provides PPP TCP/IP header compression from RFC 1144. 
    REQUIRES        INCLUDE_IPPPP
    MODULES         ipppp_vjcomp.o
    LINK_SYMS       ipppp_vjcomp_init
    CFG_PARAMS      PPPVJC_ENABLE
}

/******************** Configuration Parameters *****************************/

/* INCLUDE_IPPPP configuration parameters */
Parameter PPP_DEFAULT_BAUDRATE {
    NAME        Initial baudrate
    SYNOPSIS    THis sets the initial baud rate for the PPP RS232 serial driver.
    TYPE        char *
    DEFAULT     "9600"
}

Parameter PPP_RUNMODE {
    NAME        Runmode
    SYNOPSIS    Specifies one or more runmode options on an interface. \
                The possible runmode options are "start", "passive" , "exit" \
                "wincompat".
    TYPE        char *
    DEFAULT     "start,passive,wincompat"
}

Parameter PPP_FLAGS {
    NAME        PPP flags
    SYNOPSIS    Sets behaviors and options on an interface. The parameter value is an ASCII string with one or more flag options. There are two flag options \
                defined: \
                defaultroute \
                This adds a default route to the system routing tables using the peer as the gateway, when the IPCP/IPV6CP negotiation is \
                successfully completed.\
                proxyarp \
                This adds a proxy ARP route flag ( RTF_PROTO2) to the peer host route when IPCP negotiation is successfully completed. When this is set, the target will act as proxy for the host. One or more additional interfaces on the target must have proxy ARP enabled. ARP requests for the host address that come in on these interfaces will be processed by the target. See the Wind River Network Stack for VxWorks 7 Programmer's  Guide for information about enabling proxy ARP.
    TYPE        char *
    DEFAULT     "proxyarp"
}

Parameter PPP_AUTH_MODES {
    NAME        Authentication mode
    SYNOPSIS    Sets the authentication requirements on a PPP \
                interface. The parameter value is an ASCII string with one or \
                more authentication options. \
                There are six options defined. \
                auth \
                This requires the peer to authenticate itself before allowing \
                sending or receiving of IPCP or IPV6CP.\
                noauth \
                This does not require the peer to authenticate itself (that is,\
                do not ask for authentication.) \
                pap \
                The peer must authenticate using the PAP protocol. \
                refuse-pap \
                Do not agree to authenticate using PAP. \
                chap \
                The peer must authenticate using the CHAP protocol. \
                refuse-chap \
                Do not agree to authenticate using CHAP.
    TYPE        char *
    DEFAULT     "noauth"
}

Parameter PPP_LCP_MRU {
    NAME        LCP maximum receive unit
    SYNOPSIS    Specifies LCP Maximum receive unit.
    TYPE        char *
    DEFAULT     "1500"
}

Parameter PPP_LCP_MTU {
    NAME        LCP maximum transmit unit
    SYNOPSIS    Specifies LCP maximum transmit unit.
    TYPE        char *
    DEFAULT     "1500"
}

Parameter PPP_LCP_ECHO_REQ_INTERVAL {
    NAME        LCP echo requests interval
    SYNOPSIS    LCP EchoReq output interval in seconds. 0 to disable.
    TYPE        char *
    DEFAULT     "60"
}

Parameter PPP_LCP_ECHO_REQ_FAILURE {
    NAME        Echo failure
    SYNOPSIS    Max echo request failures before link termination.
    TYPE        char *
    DEFAULT     "5"
}

Parameter PPP_IPCP_IPV4_ADDRESS {
    NAME        Local IPv4 address
    SYNOPSIS    Specifies the desired local IPv4 address. Setting local IPv4 \
                address to 0.0.0.0 means asking the peer to suggest our IPv4 \
                address.
    TYPE        char *
    DEFAULT     "0.0.0.0"
}

Parameter PPP_IPCP_PEER_IPV4_ADDRESS {
    NAME        Peer IPv4 address
    SYNOPSIS    Set a suggested peer IPv4 address. Note that the peer \
                IPv4 address will only get suggested to the peer if it asks \
                for it by requesting IP address 0.0.0.0.
    TYPE        char *
    DEFAULT     "10.1.4.1"
}

Parameter PPP_IPCP_PEER_IPV4_POOL_NAME {
    NAME        Peer IPv4 address pool name
    SYNOPSIS    Defines the name of the address pool used to supply peers \
                with IPv4 addresses when running as a PPP or PPPoE server. \
                The configuration consists of two steps. First a pool must be \
                defined with a name with PPP_IPCP_PEER_IPV4_POOL_NAME. The \
                start and end IPv4 addresses pool are then defined with \
                PPP_IPCP_PEER_IPV4_ADDRESS_POOL. E.g. "default".
    TYPE        char *
    DEFAULT     "default"
}

Parameter PPP_IPCP_PEER_IPV4_ADDRESS_POOL {
    NAME        Peer IPv4 address pool
    SYNOPSIS    Configures a IPv4 address pool associated with the pool name \
                defined by PPP_IPCP_PEER_IPV4_POOL_NAME. This address pool \
                is used to supply peers with IPv4 addresses when running as \
                a PPP or PPPoE server. E.g., "10.1.3.1-10.1.3.255".
    TYPE        char *
    DEFAULT     "10.1.3.1-10.1.3.255"
}

Parameter PPP_USERNAME {
    NAME        PPP username
    SYNOPSIS    PPP username.
    TYPE        char *
    DEFAULT     "ppp"
}

Parameter PPP_PASSWD {
    NAME        PPP password
    SYNOPSIS    PPP password
    TYPE        char *
    DEFAULT     "kallekula"
}

Parameter PPP_IPCP_PRIMARY_DNS_ADDRESS {
    NAME        Primary DNS Address
    SYNOPSIS    Configures the PPP client IPv4 primary DNS address. The \
                configured IPv4 address will be given to the peer (i.e. the \
                client) if the peer requests a primary DNS address. \
                E.g. "10.1.2.3".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IPCP_SECONDARY_DNS_ADDRESS {
    NAME        Secondary DNS Address
    SYNOPSIS    Configures the PPP client IPv4 secondary DNS address. The \
                configured IPv4 address will be given to the peer (the \
                client) if the peer requests a secondary DNS address. \
                E.g. "195.42.198.5".
    TYPE        char *
    DEFAULT     ""
}

/* INCLUDE_IPPPP_INTERFACE_CONFIG configuration parameters */
Parameter PPP_IPCP_PRIMARY_NBNS_ADDRESS {
    NAME        Primary NBNS Address
    SYNOPSIS    Configures PPP client IPv4 primary NBNS address. The \
                configured IPv4 address will be given to the peer (i.e. the \
                client) if the peer requests a primary NBNS (WINS) address. \
                E.g., "10.1.2.2".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IPCP_SECONDARY_NBNS_ADDRESS {
    NAME        Secondary NBNS Address
    SYNOPSIS    Configures the PPP client IPv4 secondary DNS address. The \
                configured IPv4 address will be given to the peer (the \
                client) if the peer requests a secondary DNS address. \
                E.g. "195.42.198.4".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_L2TP_LNS_ADDRESS_DEFAULT {
    NAME        Default Address for L2TP Network Server
    SYNOPSIS    Configures a default address for PPP over L2TPv2 for a \
                Network Server.  This address will be used by PPP when \
                establishing a PPP over L2TPv2 connection, when no another \
                address has been assigned.  \
                E.g. "195.42.198.4".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_LCP_CLOSE_IF_NO_NCP_OPENED {
    NAME        Close LCP link if no ncp is opened
    SYNOPSIS    Close LCP link if there is no more ncp is in opened state.
    TYPE        char *
    DEFAULT     "yes"
}

Parameter PPP_INSTALL_CALLBACK_HOOK {
    NAME        Install ppp callback routine
    SYNOPSIS    Determines if the user-defined PPP action callback routine \
                as specified by the macro PPP_ACTION_CALLBACK_HOOK should \
                be installed. If FALSE, the PP_ACTION_CALLBACK_HOOK \
                configuration is not applicable.
    TYPE        BOOL
    DEFAULT     FALSE
}

Parameter PPP_ACTION_CALLBACK_HOOK {
    NAME        PPP action callback routine
    SYNOPSIS    User-defined PPP action callback routine. In order for \
                PPP to function, this callback function used by PPP must \
                be implemented to handle various PPP actions like initialization, \
                startup, peer IPv4 address requests, Peer authentication \
                login etc. If not specified, the internal PPP action \
                callback routine will be used. The \
                PPP_INSTALL_CALLBACK_HOOK must also be set to TRUE in \
                order to install this callback hook.
    TYPE        FUNCPTR
    DEFAULT     NULL
}

Parameter PPP_IF_DEFAULT_BAUDRATE_LIST {
    NAME        Initial baudrate
    SYNOPSIS    PPP RS232 serial driver baudrate. This parameter is \
                configurable on a per-interface basis in the form of \
                "<ifparam>=<value>", each separated from the other by a \
                semicolon. E.g, "ppp0=38400;ppp1=38400".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_RUNMODE_LIST {
    NAME        Interface runmode
    SYNOPSIS    Specifies one or more runmode options on an interface. \
                Possible runmode options are "start", "passive" and "exit". \
                This parameter is configurable on a per-interface basis in \
                the form of "<ifparam>=<value>", each separated from the \
                other by a semicolon. E.g, "ppp0=start,passive".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_FLAGS_LIST {
    NAME        PPP flags
    SYNOPSIS    Specifies one or more flag behavioural options on an \
                interface. Possible flags options are "defaultroute" \
                and "proxyarp". This parameter is configurable on a \
                per-interface basis in the form of "<ifparam>=<value>", \
                each separated from the other by a semicolon. E.g, \
                "ppp0=proxyarp;ppp1=proxyarp".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_AUTH_MODES_LIST {
    NAME        Authentication mode
    SYNOPSIS    Configures the required authentication modes. There are \
                six authentication modes - "auth", \
                "noauth", "pap", "refuse-pap", "chap", and "refuse-chap". \
                This parameter is configurable on a per-interface basis in \
                the form of "<ifparam>=<value>", each separated from the \
                other by a semicolon. E.g. "ppp0=chap;ppp1=pap".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_USERNAME {
    NAME        PPP username per interface
    SYNOPSIS    Configures the username for this interface. This parameter \
                is configurable on a per-interface basis in the form of \
                "<ifparam>=<value>", each separated from the other by a \
                semicolon. E.g. "ppp0=PPP1;ppp1=PPP2".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_PASSWD {
    NAME        PPP password per interface
    SYNOPSIS    Configures the password for this interface. This parameter \
                is configurable on a per-interface basis in the form of \
                "<ifparam>=<value>", each separated from the other by a \
                semicolon. E.g. "ppp0=PAS1;ppp1=PAS2".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_LCP_MRU_LIST {
    NAME        LCP maximum receive unit
    SYNOPSIS    Specifies interface LCP maximum receive unit. This parameter \
                is configurable on a per-interface basis in the form of \
                "<ifparam>=<value>", each separated from the other by a \
                semicolon. E.g, "ppp0=1500;ppp1=1500".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_LCP_MTU_LIST {
    NAME        LCP maximum transmit unit
    SYNOPSIS    Specifies interface LCP maximum transmit unit. This parameter \
                is configurable on a per-interface basis in the form of \
                "<ifparam>=<value>", each separated from the other by a \
                semicolon.. E.g, "ppp0=1500;ppp1=1500".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_LCP_ECHO_REQ_INTERVAL_LIST {
    NAME        Interface LCP echo requests interval
    SYNOPSIS    LCP echo request output interval in seconds. 0 to disable. \
                This parameter is configurable on a per-interface basis in \
                the form of "<ifparam>=<value>", each separated from the \
                other by a semicolon.. E.g, "ppp0=60;ppp1=60".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_LCP_ECHO_REQ_FAILURE_LIST {
    NAME        Echo failure
    SYNOPSIS    Max echo request failures before link termination. This \
                parameter is configurable on a per-interface basis in the \
                form of "<ifparam>=<value>", each separated from the other \
                by a semicolon. E.g, "ppp0=5;ppp1=5".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_IPCP_IPV4_ADDRESS_LIST {
    NAME        local IPv4 address list
    SYNOPSIS    Specifies the desired local IPv4 address. Setting local IPv4 \
                address to 0 means asking the peer to suggest our IPv4 \
                address. This parameter is configurable on a per-interface \
                basis in the form of "<ifparam>=<value>", each separated \
                from the other by a semicolon. \
                E.g, "ppp0=12.0.0.100;ppp1=12.1.0.100".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_IPCP_PEER_IPV4_ADDRESS_LIST {
    NAME        Peer IPv4 address list
    SYNOPSIS    Suggest peer IPv4 address if asked for. Note that the peer \
                IPv4 address will only get suggested to the peer if it ask \
                for it by requesting IP address 0. This parameter is \
                configurable on a per-interface basis in the form of \
                "<ifparam>=<value>", each separated from the other by a \
                semicolon. E.g, "ppp0=10.1.4.1;ppp1=10.2.4.1".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_IPCP_PEER_IPV4_ADDRESS_POOL_LIST {
    NAME        IPv4 peer address pool list
    SYNOPSIS    Configure a IPv4 address pool used for the interface to \
                supply peers with IPv4 addresses when running as a PPP or \
                PPPoE server. This parameter is configurable on a per-\
                interface basis in the form of "<ifparam>=<value>". Each \
                pair of "<ifparam>=<value>" is semicolon separated. \
                E.g., "ppp0=10.1.3.1-10.1.3.255".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_IPCP_PRIMARY_DNS_ADDRESS_LIST {
    NAME        Primary DNS Address list
    SYNOPSIS    Configures the PPP client IPv4 primary DNS address. The \
                configured IPv4 address will be given to the peer (the \
                client) if the peer requests a primary DNS address. This \
                parameter is configurable on a per-interface basis in the \
                form of "<ifparam>=<value>", each separated from the other \
                by a semicolon. E.g. "ppp0=10.1.2.3;ppp1=10.2.2.3".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_IF_IPCP_SECONDARY_DNS_ADDRESS_LIST {
    NAME        Secondary DNS Address list
    SYNOPSIS    Configures the PPP client IPv4 secondary DNS address. The \
                configured IPv4 address will be given to the peer (the \
                client) if the peer requests a secondary DNS address. This \
                parameter is configurable on a per-interface basis in the \
                form of "<ifparam>=<value>", each separated from the other \
                by a semicolon. E.g. "ppp0=195.42.198.5;ppp1=195.43.198.5".
    TYPE        char *
    DEFAULT     ""
}

/* INCLUDE_IPPPP_USERS_CONFIG configuration parameters */
Parameter PPP_USERS_LCP_ECHO_REQ_INTERVAL_LIST {
    NAME        Users LCP echo requests interval
    SYNOPSIS    LCP echo request output interval in seconds. 0 to disable. \
                This parameter is configurable on a per-user basis in \
                the form of "<username>=<value>", each separated from the \
                other by a semicolon. E.g, "user1=60;user2=60".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_USERS_IPCP_IPV4_ADDRESS_LIST {
    NAME        Users local IPv4 address list
    SYNOPSIS    Specifies the desired local IPv4 address. Setting local IPv4 \
                address to 0.0.0.0 means asking the peer to suggest our IPv4 \
                address. This parameter is configurable on a per-user \
                basis in the form of "<username>=<value>", each separated \
                from the other by a semicolon. \
                E.g, "user1=12.0.0.100;user2=12.1.0.100".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_USERS_IPCP_PEER_IPV4_ADDRESS_LIST {
    NAME        Users Peer IPv4 address list
    SYNOPSIS    Suggest peer IPv4 address if asked for. Note that the peer \
                IPv4 address will only get suggested to the peer if it ask \
                for it by requesting IP address 0.0.0.0. This parameter is \
                configurable on a per-user basis in the form of \
                "<username>=<value>" each separated from the other by a \
                semicolon. E.g, "user1=10.1.4.1;user2=10.2.4.1".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_USERS_IPCP_PEER_IPV4_ADDRESS_POOL_LIST {
    NAME        Users IPv4 peer address pool list
    SYNOPSIS    Configure a IPv4 address pool used for a user to supply \
                peers with IPv4 addresses when running as a PPP or PPPoE \
                server. This parameter is configurable on a per-user \
                basis in the form of "<username>=<value>", each separated \
                from the other by a semicolon. E.g., \
                "user1=10.1.3.1-10.1.3.255;user2=10.2.3.1-10.2.3.255"
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_USERS_IPCP_PRIMARY_DNS_ADDRESS_LIST {
    NAME        Users primary DNS Address list
    SYNOPSIS    Configures the PPP client IPv4 primary DNS address. The \
                configured IPv4 address will be given to the peer (the \
                client) if the peer requests a primary DNS address. This \
                parameter is configurable on a per-user basis in the \
                form of "<username>=<value>", each separated from the other \
                by a semicolon. E.g. "user1=10.1.2.3;user2=10.2.2.3".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPP_USERS_IPCP_SECONDARY_DNS_ADDRESS_LIST {
    NAME        Users secondary DNS Address list
    SYNOPSIS    Configures the PPP client IPv4 secondary DNS address. The \
                configured IPv4 address will be given to the peer (the \
                client) if the peer requests a secondary DNS address. This \
                parameter is configurable on a per-user basis in the \
                form of "<username>=<value>", each separated from the other \
                by a semicolon. E.g. "user1=195.42.198.5;user2=195.43.198.5".
    TYPE        char *
    DEFAULT     ""
}

/* INCLUDE_IPPPPOE configuration parameters */
Parameter PPPOE_SERVER {
    NAME        Enable(1) /disable(0) PPPoE server
    SYNOPSIS    Enable(1) /disable(0) PPPoE server. If the option is set \
                to "1", PPPoE server is enabled, a value of "0" disabled \
                it for the whole device or for a specific interface.
    TYPE        char *
    DEFAULT     "0"
}

Parameter PPPOE_SECRET_NAME {
    NAME        PPPoE Secret
    SYNOPSIS    Sets the secret name for the PPPoE cookie. It is used in a MD5 checksum \
                calculation to thwart DOS (denial-of-service) attacks. The \
                definition of the string need not match any remote \
                configuration! The value should be changed from its factory \
                default.
    TYPE        char *
    DEFAULT     "puttoanythinghere"
}

Parameter PPPOE_MAX_SESSIONS {
    NAME        PPPoE sessions
    SYNOPSIS    Maximum total number of PPPoE sessions allowed before \
                incoming PPPoE PADI packets are ignored, i.e. the PPPoE \
                server will not accept any additional connections.
    TYPE        char *
    DEFAULT     "16"
}

Parameter PPPOE_MAX_ETH_SESSIONS {
    NAME        PPPoE sessions per interface
    SYNOPSIS    Maximum number of PPPoE sessions per Ethernet interface. \
                Note that the interface name used is the Ethernet interface \
                name and not the pppoe interface name.
    TYPE        char *
    DEFAULT     "8"
}

Parameter PPPOE_AC_NAME {
    NAME        Access concentrator
    SYNOPSIS    This sets the PPPoE access concentrator name (AC-Name).
    TYPE        char *
    DEFAULT     "Windriver PPPoE Server"
}

Parameter PPPOE_SERVICE_NAME  {
    NAME        Service name
    SYNOPSIS    This parameter specifies the service name to accept. Do not set it to \
                accept "any" service name.
    TYPE        char *
    DEFAULT     "myservice"
}

Parameter PPPOE_IF_MAX_ETH_SESSIONS_LIST {
    NAME        PPPoE Sessions list per Interface
    SYNOPSIS    Maximum number of PPPoE sessions per Ethernet interface. \
                Note that the interface name used is the Ethernet interface \
                name and not the PPPoE interface name. This parameter is \
                configurable on a per-interface basis in the form of \
                "<ifparam>=<value>", each separated from the other by a \
                semicolon. E.g. "eth0=8;eth1=8".
    TYPE        char *
    DEFAULT     ""
}

Parameter PPPOE_IF_SERVICE_NAME_LIST {
    NAME        Service name list
    SYNOPSIS    This parameter sets the list of service names to accept. Do not set to "any".\
                This parameter is configurable on \
                a per-interface basis in the form of "<ifparam>=<value>", \
                where each are separated from the other by a semicolon. \
                E.g. "eth0=myservicename1;eth1=myservicename2".
    TYPE        char *
    DEFAULT     IP_NULL
}

/* INCLUDE_IPPPPMP configuration parameters */
Parameter PPPMP_ENABLE {
    NAME        PPP multilink
    SYNOPSIS    If the option is set \
                to "1", the PPP multilink protocol(MP) is enabled. A value of "0" disables \
                it for the whole device or for a specific interface.
    TYPE        char *
    DEFAULT     "0"
}

Parameter PPPMP_MRRU {
    NAME        Maximum Reconstructed Receive Unit 
    SYNOPSIS    Maximum size for packets received using the multilink protocol \
                after being reconstructed, if necessary, from fragments received \
                over multiple links.
    TYPE        char *
    DEFAULT     "1500"
}

Parameter PPPMP_SSN {
    NAME        PPP MP Short Sequence Number header Enable(1) / Disable(0)  
    SYNOPSIS    Controls Short Sequence numbers. In PPP multilink, packets are transferred as multilink fragments, each one having a sequence number to aid in reconstruction. By default sequence numbers are 24 bits, but 16-bits can be negotiated to save packet overhead. The PPPMP_SSN parameter enables this negotiation, which is described in RFC 1990.
To enable short sequence negotiation, set this parameter to 1. If this option is set to "0", the PPP MP Short Sequence \
Number headers option will not be proposed as an option \
for the negotiation, but if the peer will offer it then \
it will be accepted.\
Note, that RFC1990 specifies that default value has to \
be "0" and in the case device doesn't succeed to negotiate \
with peer Short Sequence Number option then \
Long Sequence Number will be used.
    TYPE        char *
    DEFAULT     "0"
}

Parameter PPPMP_FRAG_DISABLE {
    NAME        PPP MP PDU Fragmentation Disable (1) or Enable (0)  
    SYNOPSIS    If this option is set to "1", the PPP MP stack will try \
                to prevent protocol data unit (PDU) fragmentation. \
                If the PDU is smaller then the link's maximum transmission unit (MTU), \
                it will be sent unfragmented. \
                If the PDU is bigger then the link's MTU, \
                it will be fragmented.\
                Note, that default value is 0 - it means that all MTUs \
                will be fragmented.
    TYPE        char *
    DEFAULT     "0"
}

Parameter PPPMP_PPPOE_LINKS {
    NAME        PPPoE links
    SYNOPSIS    Number of links which will be started for multilink use when a PPPoE \
                interface is started. 
    TYPE        char *
    DEFAULT     "1"
}

Parameter PPPVJC_ENABLE {
    NAME        Van Jacobson TCP/IP header compression
    SYNOPSIS    Controls if VJC negotiation is initiated on each new connection. The default is 0 (disabled). Set to 1 to enable.
    TYPE        char *
    DEFAULT     "0"
}
Parameter PPP_TASK_PRIORITY {
    NAME        PPP task priority
    SYNOPSIS    This parameter sets the priority of the task. Changing its value may have risks.
    TYPE        char *
    DEFAULT     "50"
}


Parameter PPP_DEBUG_ENABLE {
    NAME        Enable debugging
    SYNOPSIS    Set the value to "1" to debug the task.
    TYPE        char *
    DEFAULT     "0"
}
