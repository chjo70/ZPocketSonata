/* 00comp_ipnet_apps.cdf - IPNet Applications configuration file */

/*
 * Copyright (c) 2006-2010, 2015-2017 Wind River Systems, Inc.
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
24jan17,jbm  Additional CDF clean up, removed wayward blank lines
16jan17,brk  CDF text improvements (F8336)
22aug16,rjq  Got panic with wrong default value in INET_ENABLE_PROXY_ARP.  (V7NET-1085)
09jul16,rjq  Remove redundant telnet parameters.  (V7NET-862)
29jun16,jxy  Change default value of ipcom.telnet.max_sessions to 10, (V7NET-858)
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
15sep10,xhs  support IPLITE
25jun10,rjq  Added new component IPNTP.
01dec09,rjq  Fix for defect WIND00185613.
16oct09,rjq  Added INCLUDE_IPSNTPS_API parameters.
08dec08,ggz  Added FTPS_SOCKET_BACKLOG parameter for FTP control socket
23sep08,rme  Misspelled words corrected
07sep07,rme  Replaced in SELECTION_IPCOM_FS with SELECT_IPCOM_FS in INCLUDE_IPTFTPC
04jul07,rme  Replaced INCLUDE_IPCOM_SHELL_SELECTION with FOLDER_SHELLS
                 Also updated 00comp_ipcom.cdf
07feb07,tkf  Add INCLUDE_IPTFTPC dependency on SELECTION_IPCOM_FS.
29jan07,tkf  Added INCLUDE_IPTELNETS dependncy on INCLUDE_IPCOM_SHELL_SELECTION.
23jan07,kch  Updated INCLUDE_IPSNTP_COMMON, INCLUDE_IPSNTPS and
                 INCLUDE_IPSNTPC dependencies.
04jan07,kch  Added SNTPS_PRECISION and SNTPS_MULTICAST_TTL configuration
                 parameters. Also updated default value for SNTPC_POLL_INTERVAL
                 SNTPC_PRIMARY_IPV4_ADDR, SNTPC_PRIMARY_IPV6_ADDR and
                 SNTPC_BACKUP_IPV6_ADDR. Also removed duplicate ipnet_config.c
                 configlette from INCLUDE_IPAIP and INCLUDE_IPPROXYARP.
19dec06,tkf  Change default TELNET port to 23.
11dec06,kch  Added configuration parameters for ftp server callback hooks
                 and ipnet/ipftps_example.c configlette to INCLUDE_IPFTPS.
01dec06,kch  Added additional configuration parameters for dhcp6 client,
                 dns client and sntp client/server.
21nov06,kch  Added IPCOM_TELNET_AUTH_ENABLED for TELNET server.
22sep06,tkf  Cleanup Component Names.
21sep06,kch  Moved INCLUDE_IPFIREWALL to 00comp_ipnet_firewall.cdf.
15sep06,tkf  Added FOLDER_IPNET_DHCP.
28aug06,kch  Added IPF_FWMAC_RULE_FILE, DHCPS_DO_ICMP_ADDRESS_CHECK
                 and DHCPS_AUTHORIZED_AGENTS configuration parameters.
                 Also added IPv4 AutoIP and ProxyArp components.
25aug06,kch  Fixed Workbench warnings.
12aug06,kch  Updated INCLUDE_IPRADVD configuration parameters.
09aug06,kch  Updated INCLUDE_IPDHCPC and INCLUDE_IPDNSC configuration
                 parameters. Added INCLUDE_IPTFTP_COMMON and corrected
                 INCLUDE_IPTFTPS and INCLUDE_IPTFTPC dependencies.
11aug06,tkf  Add INCLUDE_IPTELNETS dependency requirement on
                 INCLUDE_USE_IPCOM_SHELL.
22jul06,kch  Moved INCLUDE_IPRIP and INCLUDE_IPRIPNG components to
                 00comp_ipnet_rip.cdf.
18jul06,tlu  Added INCLUDE_IPRIPNG component.
05jul06,kch  Added missing SNTPC_POLL_COUNT configuration parameter to
                 INCLUDE_IPSNTP_CLIENT component.
26jun06,dlk  Make INCLUDE_IPRADVD INCLUDE_WHEN INCLUDE_IPCOM_USE_INET6.
22may06,kch  created.
*/

#ifndef _WRS_CONFIG_COMPONENT_IPLITE
Component INCLUDE_IPAIP {
    NAME            IPv4 Auto IP (or APIPA) address configuration
    SYNOPSIS        This component enables IPv4 address configuration with Auto \
                    IP, also called Automatic Private IP Addressing (APIPA).\
                    This functionality requires the IPNet stack to be compiled \
                    with the IPNET_USE_RFC3927 directive.
    REQUIRES        INCLUDE_IPNET INCLUDE_IPCOM_USE_ETHERNET
    CFG_PARAMS      INET_IPAIP_IFNAME_LIST
}

Selection SELECT_IPAIP_CONFIG {
    NAME            IPv4 Auto IP configurations
    SYNOPSIS        Selects the IPv4 Auto IP address configuration, either global \
                    or per-interface.
    COUNT           1-
    CHILDREN        INCLUDE_IPAIP_GLOBAL_CONFIGS \
                    INCLUDE_IPAIP_INTERFACE_CONFIGS
    DEFAULTS        INCLUDE_IPAIP_GLOBAL_CONFIGS
}

Component INCLUDE_IPAIP_GLOBAL_CONFIGS {
    NAME            Global configurations
    SYNOPSIS        This component lets you configure Auto IP globally. If you \
                    do not include this component, the system uses its default \
                    values, which are taken from RFC 5227.
    REQUIRES        INCLUDE_IPAIP
    CFG_PARAMS      INET_IPAIP_PROBE_WAIT INET_IPAIP_PROBE_NUM \
                    INET_IPAIP_PROBE_MIN INET_IPAIP_PROBE_MAX \
                    INET_IPAIP_ANNOUNCE_WAIT INET_IPAIP_ANNOUNCE_NUM \
                    INET_IPAIP_ANNOUNCE_INTERVAL \
                    INET_IPAIP_MAX_CONFLICTS \
                    INET_IPAIP_RATE_LIMIT_INTERVAL \
                    INET_IPAIP_DEFEND_INTERVAL
}

Component INCLUDE_IPAIP_INTERFACE_CONFIGS {
    NAME            Per-interface configurations
    SYNOPSIS        This component enables per-interface IPv4 Auto IP \
                    configurations.
    REQUIRES        INCLUDE_IPAIP
    CFG_PARAMS      INET_IPAIP_IFLIST_PROBE_WAIT \
                    INET_IPAIP_IFLIST_PROBE_NUM \
                    INET_IPAIP_IFLIST_PROBE_MIN \
                    INET_IPAIP_IFLIST_PROBE_MAX \
                    INET_IPAIP_IFLIST_ANNOUNCE_WAIT \
                    INET_IPAIP_IFLIST_ANNOUNCE_NUM \
                    INET_IPAIP_IFLIST_ANNOUNCE_INTERVAL \
                    INET_IPAIP_IFLIST_MAX_CONFLICTS \
                    INET_IPAIP_IFLIST_RATE_LIMIT_INTERVAL \
                    INET_IPAIP_IFLIST_DEFEND_INTERVAL
}
#endif

Component INCLUDE_IPPROXYARP {
    NAME            Proxy ARP
    SYNOPSIS        This component supplies configuration parameters to define how \
                    proxy ARP works over the network.
    REQUIRES        INCLUDE_IPCOM INCLUDE_IPCOM_USE_INET INCLUDE_IPNET
    CFG_PARAMS      INET_ENABLE_PROXY_ARP INET_AUTO_PROXY_ARP \
                    INET_ACCEPT_SOURCE_ROUTE \
                    INET_IFLIST_ENABLE_PROXY_ARP INET_IFLIST_AUTO_PROXY_ARP
}

Component INCLUDE_IPRADVD {
    NAME            Router advertisement
    SYNOPSIS        This component provides router advertisement.
    MODULES         ipnet_radvd.o
    REQUIRES        INCLUDE_IPCOM INCLUDE_IPCOM_USE_INET6 INCLUDE_IPNET
#ifdef _WRS_CONFIG_COMPONENT_IPNET
    INCLUDE_WHEN    INCLUDE_IPCOM_USE_INET6
#endif
    CONFIGLETTES    ipnet_radvd_config.c
    CFG_PARAMS      RADVD_IFNAME_LIST RADVD_IFLIST_ADV_MANAGED_FLAG \
                    RADVD_IFLIST_ADV_OTHER_CONFIG_FLAG \
                    RADVD_IFLIST_ADV_LINK_MTU \
                    RADVD_IFLIST_ADV_REACHABLE_TIME \
                    RADVD_IFLIST_ADV_RETRANS_TIMER \
                    RADVD_IFLIST_ADV_CUR_HOP_LIMIT \
                    RADVD_IFLIST_ADV_HA_FLAG \
                    RADVD_IFLIST_ADV_INTERVAL_OPT \
                    RADVD_IFLIST_ADV_HA_OPT \
                    RADVD_IFLIST_HA_OPT_LIFETIME \
                    RADVD_IFLIST_HA_OPT_PREFERENCE \
                    RADVD_IFLIST_HA_OPT_MOBILE_ROUTER \
                    RADVD_IFLIST_MIN_RTR_ADV_INTERVAL \
                    RADVD_IFLIST_MAX_RTR_ADV_INTERVAL \
                    RADVD_IFLIST_ADV_DEFAULT_LIFETIME \
                    RADVD_IFLIST_ADV_PREFIX \
                    RADVD_IFLIST_PREFIX \
                    RADVD_IFLIST_MIN_DELAY_BETWEEN_RAS \
                    RADVD_IFLIST_PREFIX_ADV_ONLINK_FLAG \
                    RADVD_IFLIST_PREFIX_ADV_AUTONOMOUS_FLAG \
                    RADVD_IFLIST_PREFIX_ADV_RTR_ADDR_FLAG \
                    RADVD_IFLIST_PREFIX_ADV_VALID_LIFETIME \
                    RADVD_IFLIST_PREFIX_ADV_PREFERRED_LIFETIME \
                    RADVD_IFLIST_PREFIX_ADV_VALID_LIFETIME_DECREMENT \
                    RADVD_IFLIST_PREFIX_ADV_PREFERRED_LIFETIME_DECREMENT \
                    RADVD_TASK_PRIORITY \
                    RADVD_DEBUG_ENABLE
}


/******************** Configuration Parameters *****************************/

#ifndef _WRS_CONFIG_COMPONENT_IPLITE
/* INCLUDE_IPAIP configuration parameters */
Parameter INET_IPAIP_IFNAME_LIST {
    NAME        Auto IP interface list
    SYNOPSIS    This parameter specifies a space-separated list of interfaces \
                that can configure a link-local IPv4 address. For example, \
                "eth0 eth1".
    TYPE        char *
    DEFAULT     ""
}

/* INCLUDE_IPAIP_GLOBAL_CONFIGS configuration parameters */

/*
 * The following configuration parameters support RFC3927, Dynamic
 * Configuration of IPv4 Link-Local Addresses. These configuration
 * parameters are only meaningful if IPNET is compiled with the
 * IPNET_USE_RFC3927 directive.
 */

Parameter INET_IPAIP_PROBE_WAIT {
    NAME        Auto IP probe wait time
    SYNOPSIS    This parameter specifies the time (in seconds) the target waits \
                before creating a link-local IPv4 address and checking it for \
                uniqueness.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET_IPAIP_PROBE_NUM {
    NAME        Auto IP probe count
    SYNOPSIS    This parameter specifies the number of ARP requests the target \
                sends to check a link-local address for uniqueness before it \
                accepts the address.
    TYPE        char *
    DEFAULT     "3"
}

Parameter INET_IPAIP_PROBE_MIN {
    NAME        Auto IP minimum probe time
    SYNOPSIS    This parameter specifies the minimum time (in seconds) to wait \
                before sending the next probe. Auto IP sends the next probe \
                between PROBE_MIN and PROBE_MAX seconds after the previous one.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET_IPAIP_PROBE_MAX {
    NAME        Auto IP maximum probe time
    SYNOPSIS    This parameter specifies the maximum time (in seconds) to wait \
                before sending the next probe. Auto IP sends the next probe \
                between PROBE_MIN and PROBE_MAX seconds after the previous one.
    TYPE        char *
    DEFAULT     "3"
}

Parameter INET_IPAIP_ANNOUNCE_WAIT {
    NAME        Auto IP announce wait time
    SYNOPSIS    This parameter specifies the time (in seconds) that Auto IP waits \
                before it starts to announce the address it selected. It does \
                not defend the address if it hears another announcement during \
                this period.
    TYPE        char *
    DEFAULT     "2"
}

Parameter INET_IPAIP_ANNOUNCE_NUM {
    NAME        Auto IP number of announcements
    SYNOPSIS    This parameter specifies the number of announcements for Auto IP \
                to send.
    TYPE        char *
    DEFAULT     "2"
}

Parameter INET_IPAIP_ANNOUNCE_INTERVAL {
    NAME        Auto IP announcements interval
    SYNOPSIS    This parameter specifies the number of seconds between Auto IP \
                announcements.
    TYPE        char *
    DEFAULT     "2"
}

Parameter INET_IPAIP_MAX_CONFLICTS {
    NAME        Auto IP maximum conflicts
    SYNOPSIS    This parameter specifies the maximum number of address collisions \
                that Auto IP allows before it applies rate-limiting when it \
                creates the next address.
    TYPE        char *
    DEFAULT     "10"
}

Parameter INET_IPAIP_RATE_LIMIT_INTERVAL {
    NAME        Auto IP rate limit interval
    SYNOPSIS    This parameter specifies the delay between successive address \
                regeneration attempts when the regeneration is rate-limited.
    TYPE        char *
    DEFAULT     "60"
}

Parameter INET_IPAIP_DEFEND_INTERVAL {
    NAME        Auto IP defensive interval
    SYNOPSIS    This parameter specifies the minimum interval between defensive \
                ARPs.
    TYPE        char *
    DEFAULT     "10"
}

/* INCLUDE_IPAIP_INTERFACE_CONFIGS configuration parameters */
Parameter INET_IPAIP_IFLIST_PROBE_WAIT {
    NAME        Auto IP probe wait time
    SYNOPSIS    This parameter specifies the number of seconds a host waits \
                before creating a link-local IPv4 address and checking it for \
                uniqueness. This parameter can be specified for each interface \
                specified in INET_IPAIP_IFNAME_LIST in the form of \
                "<ifparam>=<value>". For example, "eth0=1". Each pair of \
                "<ifparam>=<value>" is separated by a semicolon. 
    TYPE        char *
    DEFAULT     ""
}

Parameter INET_IPAIP_IFLIST_PROBE_NUM {
    NAME        Auto IP probe count
    SYNOPSIS    This parameter specifies the number of times a link-local address \
                is checked for uniqueness before being assigned. This parameter \
                can be specified for each interface specified in \
                INET_IPAIP_IFNAME_LIST in the form of "<ifparam>=<value>". For \
                example, "eth0=3". Each pair of "<ifparam>=<value>" is separated \
                by a semicolon. 
    TYPE        char *
    DEFAULT     ""
}

Parameter INET_IPAIP_IFLIST_PROBE_MIN {
    NAME        Auto IP minimum probe time
    SYNOPSIS    This parameter specifies the minimum number of seconds to wait \
                before sending the next probe. This parameter can be specified \
                for each interface specified in INET_IPAIP_IFNAME_LIST in the \
                form of "<ifparam>=<value>". For example, "eth0=1". Each pair of \
                "<ifparam>=<value>" is separated by a semicolon. 
    TYPE        char *
    DEFAULT     ""
}

Parameter INET_IPAIP_IFLIST_PROBE_MAX {
    NAME        Auto IP maximum probe time
    SYNOPSIS    This parameter specifies the maximum number of seconds to wait \
                before sending the next probe. This parameter can be specified \
                for each interface specified in INET_IPAIP_IFNAME_LIST in the \
                form of "<ifparam>=<value>". For example, "eth0=3". Each pair of \
                "<ifparam>=<value>" is separated by a semicolon. 
    TYPE        char *
    DEFAULT     ""
}

Parameter INET_IPAIP_IFLIST_ANNOUNCE_WAIT {
    NAME        Auto IP announce wait time
    SYNOPSIS    This parameter specifies the time to wait (in seconds) before \
                the selected IPv4 address is announced. The address is not \
                defended if another announcement is heard during this period. \
                The address is assigned to the interface when the announce \
                period starts. This parameter can be specified for each interface \
                specified in INET_IPAIP_IFNAME_LIST in the form of \
                "<ifparam>=<value>". For example, "eth0=2". Each pair of \
                "<ifparam>=<value>" is separated by a semicolon. 
    TYPE        char *
    DEFAULT     ""
}

Parameter INET_IPAIP_IFLIST_ANNOUNCE_NUM {
    NAME        Auto IP number of announcements
    SYNOPSIS    This parameter specifies the number of announcements to send. \
                This parameter can be specified for each interface specified in \
                INET_IPAIP_IFNAME_LIST in the form of "<ifparam>=<value>". For \
                example, "eth0=2". Each pair of "<ifparam>=<value>" is separated \
                by a semicolon.
    TYPE        char *
    DEFAULT     ""
}

Parameter INET_IPAIP_IFLIST_ANNOUNCE_INTERVAL {
    NAME        Auto IP announcements interval
    SYNOPSIS    This parameter specifies the number of seconds between \
                announcements. This parameter can be specified for each interface \
                specified in INET_IPAIP_IFNAME_LIST in the form of \
                "<ifparam>=<value>". For example, "eth0=2". Each pair of \
                "<ifparam>=<value>" is separated by a semicolon.
    TYPE        char *
    DEFAULT     ""
}

Parameter INET_IPAIP_IFLIST_MAX_CONFLICTS {
    NAME        Auto IP maximum conflicts
    SYNOPSIS    This parameter specifies the maximum number of address collisions \
                that are allowed before applying rate-limiting to the creation \
                of the next address. This parameter can be specified for each \
                interface specified in INET_IPAIP_IFNAME_LIST in the form of  \
                "<ifparam>=<value>". For example, "eth0=10". Each pair of \
                "<ifparam>=<value>" is separated by a semicolon. 
    TYPE        char *
    DEFAULT     ""
}

Parameter INET_IPAIP_IFLIST_RATE_LIMIT_INTERVAL {
    NAME        Auto IP rate limit interval
    SYNOPSIS    This parameter specifies the delay between successive Auto IP \
                attempts. This parameter can be specified for each interface \
                specified in INET_IPAIP_IFNAME_LIST in the form of \
                "<ifparam>=<value>". For example, "eth0=60". Each pair of \
                "<ifparam>=<value>" is separated by a semicolon.
    TYPE        char *
    DEFAULT     ""
}

Parameter INET_IPAIP_IFLIST_DEFEND_INTERVAL {
    NAME        Auto IP defensive interval
    SYNOPSIS    This parameter specifies the minimum interval between defensive \
                ARPs. This parameter can be specified for each interface specified \
                in INET_IPAIP_IFNAME_LIST in the form of "<ifparam>=<value>". \
                For example, "eth0=10". Each pair of "<ifparam>=<value>" is \
                separated by a semicolon. 
    TYPE        char *
    DEFAULT     ""
}
#endif

/* INCLUDE_IPPROXYARP configuration parameters */
Parameter INET_ENABLE_PROXY_ARP {
    NAME        Enable network proxy ARP
    SYNOPSIS    When this parameter is set to "yes" the stack does proxy ARP \
                for network routes tagged with the proxy arp flag.
    TYPE        char *
    DEFAULT     "yes"
}

Parameter INET_AUTO_PROXY_ARP {
    NAME        Auto proxy ARP
    SYNOPSIS    When this parameter is set to "yes" the stack automatically \
                tags all interface address network routes as proxy arp.
    TYPE        char *
    DEFAULT     "no"
}

Parameter INET_ACCEPT_SOURCE_ROUTE {
    NAME        Accept source routed rrames
    SYNOPSIS    When this parameter is set to "yes", the stack accepts source \
                routed frames.
    TYPE        char *
    DEFAULT     "no"
}

Parameter INET_IFLIST_ENABLE_PROXY_ARP {
    NAME        Enable network proxy ARP
    SYNOPSIS    When this parameter is set to 1, the stack does proxy arping for \
                network routes tagged with the proxy arp flag. This parameter can \
                be configured on a per-interface basis in the form of \
                "<ifparam>=<value>". For example, "eth0=1". Each pair of \
                "<ifparam>=<value>" is separated by a semicolon.
    TYPE        char *
    DEFAULT     ""
}

Parameter INET_IFLIST_AUTO_PROXY_ARP {
    NAME        Auto proxy ARP
    SYNOPSIS    When this parameter is set to 1, the stack automatically tags all \
                interface address network routes as proxy arp. This parameter \
                can be configured on a per-interface basis in the form of \
                "<ifparam>=<value>". For example, "eth0=1". Each pair of \
                "<ifparam>=<value>" is separated by a semicolon.
    TYPE        char *
    DEFAULT     ""
}

/* INCLUDE_IPRADVD configuration parameters */

/*
 * don't specify default value so that workbench can prompt user to
 * enter the interface name
 */
Parameter  RADVD_IFNAME_LIST {
    NAME        Router advertisement daemon (radvd) interface name list
    SYNOPSIS    This parameter specifies the name of the interface on which the \
                radvd sends router advertisements and listens for router \
                solicitation messages. The format is a space-separated list of \
                interface names. For example, "eth0 eth1". The default is an \
                empty list.
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_ADV_MANAGED_FLAG {
    NAME        Managed flag
    SYNOPSIS    This parameter specifies the TRUE(=1)/FALSE(=0) value to be \
                placed in the "Managed address configuration" flag field in the \
                router advertisement. This parameter can be specified for each \
                interface that is listed in RADVD_IFNAME_LIST in the \
                form of "<ifparam>=<value>". Each pair of "<ifparam>=<value>" \
                is separated by a semicolon. For example, "eth0=0" \
                or "eth0=0;eth1=0". Default: "0" (=FALSE). 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_ADV_OTHER_CONFIG_FLAG {
    NAME        Other configuration flag
    SYNOPSIS    This parameter specifies the TRUE(=1)/FALSE(=0) value to be \
                placed in the "Other stateful configuration" flag field in the \
                router advertisement. This parameter can be specified for each \
                interface that is listed in RADVD_IFNAME_LIST in the form of \
                "<ifparam>=<value>". Each pair of "<ifparam>=<value>" is \
                separated by a semicolon. For example, "eth0=0" or \
                "eth0=0;eth1=0". Default: "0" (=FALSE). 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_ADV_LINK_MTU {
    NAME        Advertisement link MTU size
    SYNOPSIS    This parameter specifies the value to be placed in MTU options \
                sent by the router. A value of zero indicates that no MTU \
                options are sent, which means that the MTU of the interface is \
                used by all hosts. This parameter can be specified for each \
                interface that is listed in RADVD_IFNAME_LIST in the form \
                of "<ifparam>=<value>". Each pair of "<ifparam>=<value>" \
                is separated by a semicolon. For example, "eth0=0" or \
                "eth0=0;eth1=0". Default: "0". 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_ADV_REACHABLE_TIME  {
    NAME        Advertisement reachable time
    SYNOPSIS    This parameter specifies the value to be placed in the Reachable \
                Time field in the router advertisement messages sent by the \
                router. A value of zero means it is unspecified (by this router). \
                The value MUST be no greater than 3,600,000 milliseconds \
                (1 hour). This parameter can be specified for each interface \
                that is listed in RADVD_IFNAME_LIST in the form of \
                "<ifparam>=<value>". Each pair of "<ifparam>=<value>" is \
                separated by a semicolon. For example, "eth0=0" or "eth0=0;eth1=0". \
                Default: "0". 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_ADV_RETRANS_TIMER {
    NAME        Advertisement retransmit timer
    SYNOPSIS    This parameter specifies the value to be placed in the Retrans \
                Timer field in the router advertisement messages sent by this \
                router. A value of zero means it is unspecified (by this router). \
                This parameter can be specified for each interface that is listed \
                in RADVD_IFNAME_LIST in the form of "<ifparam>=<value>". Each \
                pair of "<ifparam>=<value>" is separated by a semicolon. \
                For example, "eth0=0" or "eth0=0;eth1=0". Default: "0". 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_ADV_CUR_HOP_LIMIT {
    NAME        Advertisement current hop limit
    SYNOPSIS    This parameter specifies the default value to be placed in the \
                Cur Hop Limit field in the router advertisement messages sent by \
                this router. The value should be set to the current diameter \
                of the Internet. A value of zero means it is unspecified (by this \
                router). This parameter can be specified for each interface \
                that is listed in RADVD_IFNAME_LIST in the form of \
                "<ifparam>=<value>". Each pair of "<ifparam>=<value>" is separated \
                by a semicolon. For example, "eth0=64" or "eth0=64;eth1=64". \
                Default: "64". 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_ADV_HA_FLAG {
    NAME        Mobile IP home agent flag
    SYNOPSIS    This parameter specifies the TRUE(=1)/FALSE(=0) value to be \
                placed in the "home agent" flag field in the router advertisement. \
                If this flag is set, it indicates that the router in question also \
                serves as a home agent. This parameter can be specified for each \
                interface that is listed in RADVD_IFNAME_LIST in the form of \
                "<ifparam>=<value>". Each pair of "<ifparam>=<value>" is \
                separated by a semicolon. For example, "eth0=0" or \
                "eth0=0;eth1=0". Default: "0" (=FALSE). 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_ADV_INTERVAL_OPT  {
    NAME        Advertisement interval option
    SYNOPSIS    If this parameter is set to TRUE(=1), the router advertisement \
                daemon appends a router advertisement interval option to the \
                router advertisement. This option is specified in RFC 3775. \
                This parameter can be specified for each interface that is \
                listed in RADVD_IFNAME_LIST in the form of "<ifparam>=<value>". \
                Each pair of "<ifparam>=<value>" is separated by a semicolon. \
                For example, "eth0=0" or "eth0=0;eth1=0". Default: "0" (=FALSE). 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_ADV_HA_OPT {
    NAME        Home agent information option
    SYNOPSIS    If this parameter is set to TRUE(=1), the router advertisement \
                daemon appends a home agent information option to its router \
                advertisement. This parameter can be specified for each interface \
                that is listed in RADVD_IFNAME_LIST in the form of \
                "<ifparam>=<value>". Each pair of "<ifparam>=<value>" is separated \
                by a semicolon. For example, "eth0=0" or "eth0=0;eth1=0". Default: \
                "0" (=FALSE).
    TYPE        char *
    DEFAULT     ""
}


Parameter RADVD_IFLIST_HA_OPT_MOBILE_ROUTER {
    NAME        Mobile IP home agent mobile router support option
    SYNOPSIS    This parameter specifies whether or not the home agent has mobile \
                router support. If not specified, Dynamic Home Agent Address \
                Discovery (DHAAD) for Mobile Routers does not succeed. This \
                parameter can be specified for each interface that is listed in \
                RADVD_IFNAME_LIST in the form of "<ifparam>=<value>". Each pair \
                of "<ifparam>=<value>" is separated by a semicolon. For example, \
                "eth0=0" or "eth0=0;eth1=1". The default value is \
                RADVD_IFLIST_HA_OPT_MOBILE_ROUTER set to "0". 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_HA_OPT_LIFETIME {
    NAME        Mobile IP home agent lifetime
    SYNOPSIS    This parameter specifies the home agent's lifetime (in seconds), \
                ranging between 1 and 65535. This parameter can be specified \
                for each interface that is listed in RADVD_IFNAME_LIST in the \
                form of "<ifparam>=<value>". Each pair of "<ifparam>=<value>" is \
                separated by a semicolon. For example, "eth0=18000" or \
                "eth0=18000;eth1=18000". The default value is the value of \
                RADVD_IFLIST_ADV_DEFAULT_LIFETIME expressed in seconds.
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_HA_OPT_PREFERENCE {
    NAME        Mobile IP home agent preference
    SYNOPSIS    This parameter specifies the home agent's preference. This \
                parameter can be specified for each interface that is listed in \
                RADVD_IFNAME_LIST in the form of "<ifparam>=<value>". Each pair \
                of "<ifparam>=<value>" is separated by a semicolon. For example, \
                "eth0=0" or "eth0=0;eth1=0". Default: "0".
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_MIN_RTR_ADV_INTERVAL {
    NAME        Minimum router advertisement interval
    SYNOPSIS    This parameter specifies the minimum time allowed (in seconds) \
                between sending unsolicited multicast router advertisements from \
                the interface. MUST be no less than 30 milliseconds and no \
                greater than 75% of MaxRtrAdvInterval. The interval limitations \
                are set according to RFC 3775. This parameter can be specified \
                for each interface that is listed in RADVD_IFNAME_LIST in the \
                form of "<ifparam>=<value>". Each pair of "<ifparam>=<value>" is \
                separated by a semicolon. For example, "eth0=200000" or \
                "eth0=200000;eth1=200000". Default: "200000" (MaxRtrAdvInterval / 3).
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_MAX_RTR_ADV_INTERVAL {
    NAME        Maximum router advertisement interval
    SYNOPSIS    This parameter specifies the maximum time (in seconds) allowed \
                between sending unsolicited multicast router advertisements from \
                the interface. MUST be no less than 70 milliseconds and no \
                greater than 1800000 seconds. This parameter can be specified for \
                each interface that is listed in RADVD_IFNAME_LIST in the form \
                of "<ifparam>=<value>". Each pair of "<ifparam>=<value>" is \
                separated by a semicolon. For example, "eth0=600000" or \
                "eth0=600000;eth1=600000". Default: "600000". 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_MIN_DELAY_BETWEEN_RAS {
    NAME        Minimum delay between solicited router advertisements
    SYNOPSIS    This parameter specifies the minimum delay between solicited \
                router advertisements. If not specified, the value defaults to \
                MinRtrAdvInterval. This configuration variable is defined in \
                RFC 3775 and can be specified for each interface that is listed \
                in RADVD_IFNAME_LIST in the form of "<ifparam>=<value>". Each \
                pair of "<ifparam>=<value>" is separated by a semicolon. For \
                example, "eth0=200000" or "eth0=200000;eth0=200000". Default: \
                "200000" (MinRtrAdvInterval). 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_ADV_DEFAULT_LIFETIME {
    NAME        Advertisement default lifetime
    SYNOPSIS    This parameter specifies the value (in seconds) to be placed in \
                the Router Lifetime field of router advertisements sent from this \
                interface. This parameter must be set to either zero or between \
                1000 and 9000000 milliseconds. A value of zero indicates that the \
                router is not to be used as a default router. This parameter can \
                be specified for each interface that is listed in RADVD_IFNAME_LIST \
                in the form of "<ifparam>=<value>". Each pair of "<ifparam>=<value>" \
                is separated by a semicolon. For example, "eth0=1800000" or \
                "eth0=1800000;eth1=1800000". Default: 3 * MaxRtrAdvInterval, but \
                at least 1000 milliseconds. 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_ADV_PREFIX {
    NAME        Advertisement prefixes
    SYNOPSIS    This parameter specifies a list of prefixes to add to the router \
                advertisement messages. The elements are an identifier for the \
                prefix, not the actual prefix. This parameter can be specified \
                for each interface that is listed in RADVD_IFNAME_LIST in the \
                form of "<ifparam>=<value>". Each pair of "<ifparam>=<value>" \
                is separated by a semicolon. For example, "eth0=6to4net" or \
                "eth0=6to4net;eth1=devnet". The default value is an empty list. 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_PREFIX {
    NAME        List of prefixes in advertisements
    SYNOPSIS    This parameter specifies the prefix and prefix length. The prefix \
                length must be between 1 and 127 and must be 64 for Ethernet if it \
                is used for automatic address configuration. This parameter can \
                be specified for each interface that is listed in RADVD_IFNAME_LIST \
                in the form of "<ifparam>=<value>". Each pair of \
                "<ifparam>=<value>" is separated by a semicolon. For example, \
                "eth0.prefix.6to4net=2002:0a01:0264::/64" or \
                "eth0.prefix.6to4net=2002:0a01:0264::/64;eth1.prefix.devnet= \
                2002:a01:201:1::/64". Default: "" (not specified). 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_PREFIX_ADV_ONLINK_FLAG {
    NAME        Advertisement on-link determination option
    SYNOPSIS    This parameter specifies the value to be placed in the On-Link \
                flag field in the prefix information option. This parameter can \
                be specified for each interface that is listed in RADVD_IFNAME_LIST \
                in the form of "<ifparam>=<value>". Each pair of "<ifparam>=<value>" \
                is separated by a semicolon. For example, "eth0.prefix.6to4net=1" \
                or "eth0.prefix.6to4net=1;eth1.prefix.devnet=1". Default: 1 (TRUE).
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_PREFIX_ADV_AUTONOMOUS_FLAG  {
    NAME        Advertisement automatic address configuration
    SYNOPSIS    This parameter specifies the value to be placed in the Autonomous \
                flag field in the prefix information option. This parameter can \
                be specified for each interface that is listed in RADVD_IFNAME_LIST \
                in the form of "<ifparam>=<value>". Each pair of "<ifparam>=<value>" \
                is separated by a semicolon. For example, "eth0.prefix.6to4net=1" \
                or "eth0.prefix.6to4net=1;eth1.prefix.devnet=1". Default: 1 (TRUE). 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_PREFIX_ADV_RTR_ADDR_FLAG {
    NAME        Advertisement router address flag
    SYNOPSIS    This parameter specifies the value to be placed in the Router \
                Address flag field in the prefix information option. This \
                indicates that the specified prefix is also a complete, global \
                address for the router. This flag is specified in RFC 3775 and \
                can be specified for each interface that is listed in \
                RADVD_IFNAME_LIST in the form of "<ifparam>=<value>". Each \
                pair of "<ifparam>=<value>" is separated by a semicolon. \
                For example, "eth0.prefix.6to4net=0" or \
                "eth0.prefix.6to4net=0;eth1.prefix.devnet=0". Default: 0 (FALSE).
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_PREFIX_ADV_VALID_LIFETIME {
    NAME        Advertisement valid lifetime
    SYNOPSIS    This parameter specifies the value (in seconds) to be placed in \
                the Valid Lifetime field in the prefix information option. The \
                designated value of all is (-1) which represents infinity. \
                This parameter can be specified for each interface that is \
                listed in RADVD_IFNAME_LIST in the form of "<ifparam>=<value>". \
                Each pair of "<ifparam>=<value>" is separated by a semicolon. \
                For example, "eth0.prefix.6to4net=-1" or \
                "eth0.prefix.6to4net=-1;eth1.prefix.devnet=-1". \
                Default: "-1" (infinite). 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_PREFIX_ADV_PREFERRED_LIFETIME {
    NAME        Advertisement preferred time
    SYNOPSIS    This parameter specifies the value (in seconds) to be placed in \
                the Preferred Lifetime field in the prefix information option. \
                The designated value of all is (-1) which represents infinity. \
                This parameter can be specified for each interface that is \
                listed in RADVD_IFNAME_LIST in the form of "<ifparam>=<value>". \
                Each pair of "<ifparam>=<value>" is separated by a semicolon. \
                For example, "eth0.prefix.6to4net=-1" or \
                "eth0.prefix.6to4net=-1;eth1.prefix.devnet=-1". Default: "-1" \
                (infinite). 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_PREFIX_ADV_VALID_LIFETIME_DECREMENT {
    NAME        Advertisement valid time auto-decrement
    SYNOPSIS    This parameter enables or disables the valid lifetime \
                auto-decrementing feature. For example, \
                "eth0.prefix.6to4net.AdvValidLifetimeDecrement=1". The default \
                is "0" (no auto-decrement). 
    TYPE        char *
    DEFAULT     ""
}

Parameter RADVD_IFLIST_PREFIX_ADV_PREFERRED_LIFETIME_DECREMENT {
    NAME        Advertisement preferred time auto-decrement
    SYNOPSIS    This parameter enables or disables the preferred lifetime \
                auto-decrementing feature. For example, \
                "eth0.prefix.6to4net.AdvValidLifetimeDecrement=1". The default is \
                "0" (no auto-decrement). 
    TYPE        char *
    DEFAULT     ""
}
Parameter RADVD_TASK_PRIORITY {
    NAME        Task priority
    SYNOPSIS    This parameter sets the task priority of the router advertisement \
                daemon (radvd) network service task. Changing the value can have \
                risks.
    TYPE        char *
    DEFAULT     "50"
}


Parameter RADVD_DEBUG_ENABLE {
    NAME        Enable debugging
    SYNOPSIS    To debug the router advertisement daemon (radvd) network service task, \
                set the value to "1".
    TYPE        char *
    DEFAULT     "0"
}

