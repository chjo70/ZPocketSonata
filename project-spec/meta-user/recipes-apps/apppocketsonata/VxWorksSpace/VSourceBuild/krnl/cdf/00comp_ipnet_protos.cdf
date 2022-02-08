/* 00comp_ipnet_protos.cdf - IPNet Protocols Component configuration file */

/*
 * Copyright (c) 2006-2008, 2011-2017 Wind River Systems, Inc.
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
27jan17,jbm  Removed "protocol" from INCLUDE_IPNET_USE_NAT component, 
             editing for consistency, capitalization issues.
07dec16,mca  Break hard dependency between END and IPNET (US85582)
23aug16,kjn  Changed some default values to pass Achilles by default
             (V7NET-1096)
18aug16,ljl  Add a configure option for ipv4 random id. (V7NET-898)
28jun16,rjq  Incorrect synopsis about TCP_DELAY_ACK_TIME. (V7NET-861)
15may15,h_x  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
15dec15,h_x  TCP delay ack time configurable, US71092
08jan15,ljl  Add parameter TCP_USE_RFC6528_SECURE_ISN for INCLUDE_IPTCP (V7NET-499).
05mar14,dlk  Merge multi-instance stack work.
15jan14,jsh  Remove INCLUDE_IPCOM_USE_INET6_ONLY component for vx7
01mar13,xhs  Fix WIND00405569, adding some missed parameters.
25may12,ggz  Deleted param IPNET_ROUTE_MAX_CLONE_COUNT. Defect WIND00340576.
19apr12,fei  Added for TCPAO(RFC5925).
24aug11,h_s  Added the support for tcp keep alive parameters.
25jan11,dlk  Changing default IPNET_ROUTE_MAX_CLONE_COUNT to 50000.
20jan11,dlk  Adding IPNET_ROUTE_MAX_CLONE_COUNT parameter.
02oct08,jre  Added INET_DELETE_ADDR_ON_DUPLICATE_DETECT
23sep08,rme  Misspelled words corrected
19sep07,rme  Added missing backslashes
07sep07,rme  Replaced SELECTION_IPCOM_FS with SELECT_IPCOM_FS in INCLUDE_IPNET_USE_NAT
13jul07,dlk  Make existing INET6_RTHDR0 a parameter of INCLUDE_IPCOM_USE_INET6.
25apr07,tkf  Add INCLUDE_IPCOM_USE_INET6_ONLY component to support
             Pv6-Only Build.
06mar07,kch  Changed IPNAT_ICMP_MAPPING_TIMEOUT default value from 5 to
             10 seconds (WIND00089895).
07feb07,tkf  Add INCLUDE_IPNET_USE_NAT dependency on
             SELECTION_IPCOM_FS.
03jan07,kch  Updated default value for IPNET_CACHE_BUFSIZE,
             INET6_MAX_MULTICAST_SOLICIT and TCP_USE_TIMESTAMP. Also
             removed duplicate ipnet_config.c configlette property from
             INCLUDE_IPCOM_USE_INET, INCLUDE_IPCOM_USE_INET6 and
             INCLUDE_IPNET6_AUTOCONF_PRIVACY_EXT.
20dec06,kch   Changed INET_MAX_MULTICAST_SOLICIT default value from 0 to 9.
01dec06,kch  Changed INET_MIN_MTU_SIZE default value to 68. Also added
             additional configuration parameters for tcp.
23sep06,kch  Moved multicast routing and proxy components to
             02comp_ipnet_mcast.cdf. Also moved INCLUDE_IPNET_USE_VRRPD to
             02comp_ipnet_vrrp.cdf and INCLUDE_IPRADIUS to
             02comp_ipnet_radius.cdf.
20sep06,tkf  Add INCLUDE_IPV4 and INCLUDE_IPV6 for backwards compatibility.
07sep06,kch  Removed ipnet_nat_proxy_dns symbol from INCLUDE_IPNET_USE_NAT.
23aug06,kch  Updated default values for INET_BASE_REACHABLE_TIME and
             INET_MAX_MULTICAST_SOLICIT. Also added support for
             autoconf privacy extensions and NAT configurations. Moved
             proxyArp configuration parameters to INCLUDE_IPPROXYARP.
12aug06,kch  Added INCLUDE_IPNET_USE_VRRPD.
02jul06,kch  Corrected dependency problems for INCLUDE_IPMCP_USE_IGMP,
             INCLUDE_IPMCP_USE_MLD and INCLUDE_IPMCP components.
26jun06,dlk  Remove ipnet_radvd.o as a module of INCLUDE_IPCOM_USE_INET6;
             it belongs to INCLUDE_IPRADVD.
22may06,kch  created.
*/

Component INCLUDE_IPNET {
    NAME            IPNET support
    SYNOPSIS        This component includes core VxWorks 7 network stack (IPNET) support.
    REQUIRES        SELECT_IPNET_ETHERNET_IFCONFIG \
                    INCLUDE_IPCOM \
                    INCLUDE_NETWORK
    MODULES         ipnet.o
    CONFIGLETTES    ipnet_config.c
    CFG_PARAMS      IPNET_MAX_INPUT_PKTS \
                    IPNET_REASSEMBLY_TIMEOUT \
                    IPNET_MEMORY_LIMIT \
                    IPNET_DST_CACHE_LIMIT \
                    IPNET_MAX_REASSEMBLY_LIST_LEN \
                    IPNET_MAX_DGRAM_FRAG_LIST_LEN \
                    IPNET_SLAB_DESC_0 \
                    IPNET_SLAB_DESC_1 \
                    IPNET_SLAB_DESC_2 \
                    IPNET_SLAB_DESC_3 \
                    IPNET_SLAB_DESC_4 \
                    IPNET_SLAB_DESC_5 \
                    IPNET_INTERCOM_CONGESTION_LIMIT
}

Component INCLUDE_IPCOM_USE_INET {
    NAME            IPv4 configuration
    SYNOPSIS        This component provides the IPv4 network protocol and \
                    enables network connectivity with IPv4 addressing.
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    MODULES         iplite_ip4.o
    LINK_SYMS       iplite_ip4_input
    REQUIRES        INCLUDE_IPLITE
#else
    MODULES         ipnet_ip4.o
    LINK_SYMS       ipnet_ip4_input
    REQUIRES        INCLUDE_IPNET
#endif
    CFG_PARAMS      INET_MIN_MTU_SIZE INET_BASE_HOP_LIMIT \
                    INET_SEND_GRATUITOUS_ARP \
                    INET_DELETE_ADDR_ON_DUPLICATE_DETECT \
                    INET_MAX_PKTS_PENDING INET_MAX_UNICAST_SOLICIT \
                    INET_MAX_MULTICAST_SOLICIT INET_MAX_APP_SOLICIT \
                    INET_BASE_REACHABLE_TIME INET_BASE_RETRANSMIT_TIME \
                    INET_DELAY_FIRST_PROBE_TIME INET_NBR_CACHE_TO_LIVE_TIME \
                    INET_DST_CACHE_TO_LIVE_TIME \
                    INET_NBR_MIN_RANDOM_FACTOR INET_NBR_MAX_RANDOM_FACTOR \
                    INET_DISABLE_BROADCAST_FWD \
                    INET_ICMP_RATE_LIMIT_BUCKET_SIZE \
                    INET_ICMP_RATE_LIMIT_INTERVAL INET_ICMP_REDIRECT_SEND \
                    INET_ICMP_REDIRECT_RECEIVE INET_ICMP_IGNORE_ECHO_REQ \
                    INET_ICMP_IGNORE_TIMESTAMP_REQ \
                    INET_ICMP_SEND_TIME_EXCEEDED \
                    INET_ICMP_SEND_DST_UNREACHABLE \
                    INET_ICMP_IGNORE_BROADCAST \
                    INET_UDP_CHECKSUM \
                    INET_RANDOM_IP_ID
}

Component INCLUDE_IPV4 {
    NAME            Network stack IPv4 support
    SYNOPSIS        This component provides VxWorks 7 network stack IPv4 support. \
                    For more information, refer to the VxWorks 7 network stack \
                    programmer's guide.
    INCLUDE_WHEN    INCLUDE_IPCOM_USE_INET
}

Component INCLUDE_IPCOM_USE_INET6 {
    NAME            IPv6 configuration
    SYNOPSIS        This component provides the IPv6 network protocol and enables \
                    network connectivity with IPv6 addressing.
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    LINK_SYMS       iplite_ip6_input
    REQUIRES        INCLUDE_IPLITE
#else
    LINK_SYMS       ipnet_ip6_input
    REQUIRES        INCLUDE_IPNET
#endif
    CFG_PARAMS      INET6_MIN_MTU_SIZE INET6_BASE_HOP_LIMIT \
                    INET6_MAX_PKTS_PENDING INET6_MAX_UNICAST_SOLICIT \
                    INET6_MAX_MULTICAST_SOLICIT INET6_MAX_APP_SOLICIT \
                    INET6_DAD_TRANSMITS INET6_BASE_REACHABLE_TIME \
                    INET6_BASE_RETRANSMIT_TIME INET6_DELAY_FIRST_PROBE_TIME \
                    INET6_NBR_CACHE_TO_LIVE_TIME INET6_DST_CACHE_TO_LIVE_TIME \
                    INET6_ROUTER_LIFETIME INET6_ICMP_RATE_LIMIT_BUCKET_SIZE \
                    INET6_ICMP_RATE_LIMIT_INTERVAL INET6_ICMP_REDIRECT_SEND \
                    INET6_ICMP_REDIRECT_RECEIVE INET6_ICMP_IGNORE_ECHO_REQ \
                    INET6_ICMP_SEND_TIME_EXCEEDED \
                    INET6_ICMP_SEND_DST_UNREACHABLE INET6_ACCEPT_RTADV \
                    INET6_AUTO_CONFIG INET6_ADD_AUTONOMOUS_ADDR \
                    INET6_RTHDR0
}

Component INCLUDE_IPV6 {
    NAME            Network stack IPv6 support
    SYNOPSIS        This component provides VxWorks 7 network stack IPv6 support. \
                    For more information, refer to the VxWorks 7 network stack \
                    programmer's guide.
    INCLUDE_WHEN    INCLUDE_IPCOM_USE_INET6
}

Component INCLUDE_IPNET6_AUTOCONF_PRIVACY_EXT {
    NAME            Autoconf privacy extensions
    SYNOPSIS        This component includes autoconf privacy extensions support \
                    for RFC 3401, Privacy Extensions for Stateless Address Auto \
                    Configuration in IPv6. This requires that the network stack \
                    be compiled with IPNET_USE_RFC3041 directive.
    REQUIRES        INCLUDE_IPCOM_USE_INET6 \
                    SELECT_IPNET6_AUTOCONF_PRIVACY_CONFIG
}

Selection SELECT_IPNET6_AUTOCONF_PRIVACY_CONFIG {
    NAME            Autoconf privacy configurations
    SYNOPSIS        This component includes the configurations for the autoconf \
                    privacy extensions.
    COUNT           1-
    CHILDREN        INCLUDE_IPNET6_PRIVACY_GLOBAL_CONFIGS \
                    INCLUDE_IPNET6_PRIVACY_INTERFACE_CONFIGS
}

Component INCLUDE_IPNET6_PRIVACY_GLOBAL_CONFIGS {
    NAME            Global configurations
    SYNOPSIS        This component includes the global configurations for the IPv6 \
                    autoconf privacy extensions.
    REQUIRES        INCLUDE_IPNET6_AUTOCONF_PRIVACY_EXT
    CFG_PARAMS      INET6_ENABLE_PRIVACY_EXTENSONS INET6_TEMP_VALID_LIFETIME \
                    INET6_TEMP_PREFERRED_LIFETIME INET6_REGEN_ADVANCE
}

Component INCLUDE_IPNET6_PRIVACY_INTERFACE_CONFIGS {
    NAME            Per-interface configurations
    SYNOPSIS        This component includes the per-interface autoconf privacy \
                    configurations.
    REQUIRES        INCLUDE_IPNET6_AUTOCONF_PRIVACY_EXT
    CFG_PARAMS      INET6_IFLIST_ENABLE_PRIVACY_EXTENSONS \
                    INET6_IFLIST_TEMP_VALID_LIFETIME \
                    INET6_IFLIST_TEMP_PREFERRED_LIFETIME \
                    INET6_IFLIST_REGEN_ADVANCE
}

Component INCLUDE_IPNET_USE_NAT {
    NAME            NAT
    SYNOPSIS        This component includes Network Address Translation (NAT) \
                    support.
    LINK_SYMS       ipnet_nat_output_hook
    REQUIRES        INCLUDE_IPCOM_USE_INET
    CFG_PARAMS      IPNAT_ICMP_MAPPING_TIMEOUT IPNAT_UDP_MAPPING_TIMEOUT \
                    IPNAT_TCP_MAPPING_TIMEOUT IPNAT_OTHER_MAPPING_TIMEOUT \
                    IPNAT_MAX_MAPPING IPNAT_AUTOPORT_START_INTERVAL \
                    IPNAT_AUTOPORT_END_INTERVAL
}

#ifndef _WRS_CONFIG_COMPONENT_IPLITE
Component INCLUDE_IPTCP {
    NAME            TCP
    SYNOPSIS        This component includes Transmission Control Protocol (TCP) \
                    support.
    REQUIRES        INCLUDE_IPCOM INCLUDE_IPNET
    MODULES         iptcp.o
    CONFIGLETTES    iptcp_config.c
    CFG_PARAMS      TCP_CONN_TIMEOUT TCP_MAX_RETRANSMITS TCP_MSL TCP_DELAY_ACK_TIME \
                    IPTCP_MAX_RETRAMSMITS_IN_TRANSIENT TCP_IMMEDIATE_ACK_FOR_PSH \
                    IPTCP_MAX_TRANSIENT IPTCP_TRANSIENT_THRESH \
                    TCP_MAX_MSS TCP_USE_TIMESTAMP  \
                    TCP_USE_RFC1122_URGENT_DATA \
                    TCP_SEGMENT_MULTIPLIER \
                    TCP_LAND_ATTACK_PROTECTION \
                    TCP_ALLOW_ZERO_WINDOW \
                    TCP_ALLOW_TINY_WINDOW \
                    TCP_PERSIST_TMO \
                    TCP_CLAMP_MSS \
                    TCP_DEFAULT_BACKLOG_SIZE \
                    TCP_KEEP_IDLE \
                    TCP_KEEP_INTVL \
                    TCP_KEEP_CNT \
                    TCP_USE_RFC6528_SECURE_ISN
}
#endif

Component INCLUDE_IPTCPAO_CMD {
    NAME        IP TCP authentication option (tcpao) commands
    SYNOPSIS    This component includes IP TCP authentication option commands.
    MODULES     iptcp_cmd_ao.o
    LINK_SYMS   iptcp_ao_cmd
    REQUIRES    INCLUDE_IPCOM INCLUDE_IPNET
}

Component INCLUDE_IPTCPAO_CMD {
    NAME        IP TCP authentication option (tcpao) commands
    SYNOPSIS    This component includes IP TCP authentication option commands.
    MODULES     iptcp_cmd_ao.o
    LINK_SYMS   iptcp_ao_cmd
    REQUIRES    INCLUDE_IPCOM INCLUDE_IPNET
}

/******************** Configuration Parameters *****************************/
/* INCLUDE_IPNET configuration parameters */

Parameter IPNET_MEMORY_LIMIT {
    NAME        Memory limit
    SYNOPSIS    This parameter specifies the maximum amount of dynamic memory \
                the stack is allowed to use.
    TYPE        uint
    DEFAULT     16777216
}

Parameter IPNET_DST_CACHE_LIMIT {
    NAME        Destination cache number limit
    SYNOPSIS    This parameter specifies the maximum amount of destination cache \
                number the stack is allowed to use. When set to 0, there is no \
                limit (default).
    TYPE        uint
    DEFAULT     0
}

Parameter IPNET_SLAB_DESC_0 {
    NAME        Slab cache descriptor 0
    SYNOPSIS    This parameter specifies descriptor 0 in the slab cache \
                configuration array. The fields are: \
                mtu - The maximum MTU this buffer can hold. \
                flags - The IPCOM_SLAB_F_xxx flags for this buffer. \
                empty_lim - Maximum empty slabs in the cache before \
                quick garbage collection.
    TYPE        struct Ipnet_pkt_pool_slab_desc
    DEFAULT     IPNET_ETH_MTU,              IPCOM_SLAB_F_AVERAGE, 2
}

Parameter IPNET_SLAB_DESC_1 {
    NAME        Slab cache descriptor 1
    SYNOPSIS    This parameter specifies descriptor 1 in the slab cache \
                configuration array. The fields are: \
                mtu - The maximum MTU this buffer can hold. \
                flags - The IPCOM_SLAB_F_xxx flags for this buffer. \
                empty_lim - Maximum empty slabs in the cache before \
                quick garbage collection.
    TYPE        struct Ipnet_pkt_pool_slab_desc
    DEFAULT     3000,                       IPCOM_SLAB_F_FEW,     4
}

Parameter IPNET_SLAB_DESC_2 {
    NAME        Slab cache descriptor 2
    SYNOPSIS    This parameter specifies descriptor 2 in the slab cache \
                configuration array. The fields are: \
                mtu - The maximum MTU this buffer can hold. \
                flags - The IPCOM_SLAB_F_xxx flags for this buffer. \
                empty_lim - Maximum empty slabs in the cache before \
                quick garbage collection.
    TYPE        struct Ipnet_pkt_pool_slab_desc
    DEFAULT     10000,                      IPCOM_SLAB_F_ONE,    12
}

Parameter IPNET_SLAB_DESC_3 {
    NAME        Slab cache descriptor 3
    SYNOPSIS    This parameter specifies descriptor 3 in the slab cache \
                configuration array. The fields are: \
                mtu - The maximum MTU this buffer can hold. \
                flags - The IPCOM_SLAB_F_xxx flags for this buffer. \
                empty_lim - Maximum empty slabs in the cache before \
                quick garbage collection.
    TYPE        struct Ipnet_pkt_pool_slab_desc
    DEFAULT     IPNET_PKT_POOL_MAX_MTU + 1, IPCOM_SLAB_F_ONE,     8
}

Parameter IPNET_SLAB_DESC_4 {
    NAME        Slab cache descriptor 4
    SYNOPSIS    This parameter specifies descriptor 4 in the slab cache \
                configuration array. The fields are: \
                mtu - The maximum MTU this buffer can hold. \
                flags - The IPCOM_SLAB_F_xxx flags for this buffer. \
                empty_lim - Maximum empty slabs in the cache before \
                quick garbage collection.
    TYPE        struct Ipnet_pkt_pool_slab_desc
    DEFAULT     0
}

Parameter IPNET_SLAB_DESC_5 {
    NAME        Slab cache descriptor 5
    SYNOPSIS    This parameter specifies descriptor 5 in the slab cache \
                configuration array. The fields are: \
                mtu - The maximum MTU this buffer can hold. \
                flags - The IPCOM_SLAB_F_xxx flags for this buffer. \
                empty_lim - Maximum empty slabs in the cache before \
                quick garbage collection.
    TYPE        struct Ipnet_pkt_pool_slab_desc
    DEFAULT     0
}

Parameter IPNET_MAX_REASSEMBLY_LIST_LEN {
    NAME        Reassembly list length
    SYNOPSIS    This parameter specifies the maximum number of partially \
                reassembled fragmentation chains that are allowed to be \
                present at any given time. The oldest fragmentation list \
                is dropped if this limit is exceeded.
    TYPE        uint
    DEFAULT     4
}

Parameter IPNET_MAX_DGRAM_FRAG_LIST_LEN {
    NAME        IP-datagram fragment list length
    SYNOPSIS    This parameter specifies the maximum number of fragments \
                an individual IP-datagram is allowed to consist of. The partly \
                reassembled IP-datagram is dropped if this limit is exceeded.
    TYPE        uint
    DEFAULT     54
}

Parameter IPNET_MAX_INPUT_PKTS {
    NAME        Max input queue length
    SYNOPSIS    This parameter specifies the maximum number of packets that can \
                be stored in the packet input queue.
    TYPE        uint
    DEFAULT     100
}

Parameter IPNET_REASSEMBLY_TIMEOUT {
    NAME        Reassembly timeout
    SYNOPSIS    This parameter specifies the number of seconds IPNET keeps \
                incomplete datagram fragments in the reassembly list before \
                discarding them. The default is 60 seconds per RFC 2460.
    TYPE        uint
    DEFAULT     60
}

/* INCLUDE_IPCOM_USE_INET configuration parameters */
Parameter INET_MIN_MTU_SIZE {
    NAME        Minimum MTU size
    SYNOPSIS    This parameter sets the minimum MTU size, meaning the smallest \
                path MTU expected in any route. All Internet routers should be \
                able to handle 576 octets. This value is used by some Internet \
                Control Message Protocol (ICMP) messages that include data from \
                the packet that caused an ICMP message to be sent.
    TYPE        uint
    DEFAULT     576
}

Parameter INET_BASE_HOP_LIMIT {
    NAME        Base hop limit
    SYNOPSIS    This parameter specifies the default value for the time-to-live \
                (TTL) field for IPv4 unicast datagram packets.
    TYPE        char *
    DEFAULT     "64"
}

Parameter INET_SEND_GRATUITOUS_ARP {
    NAME        Gratuitous ARP
    SYNOPSIS    This parameter specifies whether or not to send a gratuitous ARP \
                when addresses are added.
    TYPE        char *
    DEFAULT     "yes"
}

Parameter INET_DELETE_ADDR_ON_DUPLICATE_DETECT {
    NAME        Delete address on duplicate detect
    SYNOPSIS    When enabled, this parameter automatically removes a configured \
                IPv4 address upon duplicate address detection (gratuitous ARP).
    TYPE        char *
    DEFAULT     "yes"
}

Parameter INET_MAX_PKTS_PENDING {
    NAME        Maximum pending packets
    SYNOPSIS    This parameter specifies the maximum number of packets that can \
                be waiting before IPv4 to link layer resolution is finished.
    TYPE        char *
    DEFAULT     "3"
}

Parameter INET_MAX_UNICAST_SOLICIT {
    NAME        Maximum unicast solicit
    SYNOPSIS    This parameter specifies the maximum number of unicast ARP request \
                messages that the stack should send before starting to use \
                multicast solicits.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET_MAX_MULTICAST_SOLICIT {
    NAME        Maximum multicast solicit
    SYNOPSIS    This parameter specifies the maximum number of ARP request \
                messages the stack should resend before staring to use \
                application probes.
    TYPE        char *
    DEFAULT     "9"
}

Parameter INET_MAX_APP_SOLICIT {
    NAME        Maximum application solicitations
    SYNOPSIS    This parameter specifies the number of resolve messages that are \
                sent to routing/netlink sockets if the ARP probes fail (or are \
                disabled).
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET_BASE_REACHABLE_TIME {
    NAME        Base reachable time
    SYNOPSIS    This parameter specifies the duration, in seconds, that an entry \
                in the Address Resolution Protocol (ARP) cache is in a reachable \
                state.
    TYPE        char *
    DEFAULT     "30"
}

Parameter INET_BASE_RETRANSMIT_TIME {
    NAME        Base retransmit time
    SYNOPSIS    This parameter specifies the number of seconds to wait between \
                retransmits.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET_DELAY_FIRST_PROBE_TIME {
    NAME        Delay first probe time
    SYNOPSIS    This parameter specifies the duration, in seconds, to wait \
                for a stale Address Resolution Protocol (ARP) entry to become \
                reachable before forcing a probe. Packets are sent using the \
                stale entry during this time.
    TYPE        char *
    DEFAULT     "5"
}

Parameter INET_NBR_CACHE_TO_LIVE_TIME {
    NAME        Neighbor cache to live
    SYNOPSIS    This parameter specifies the duration, in seconds, that can pass \
                before a stale entry in the ARP cache is deleted.
    TYPE        char *
    DEFAULT     "1200"
}

Parameter INET_NBR_MIN_RANDOM_FACTOR {
    NAME        Minimum random factor
    SYNOPSIS    This parameter specifies the minimum value of a random factor.
    TYPE        char *
    DEFAULT     "50"
}

Parameter INET_NBR_MAX_RANDOM_FACTOR {
    NAME        Maximum random factor
    SYNOPSIS    This parameter specifies the maximum value of a random factor.
    TYPE        char *
    DEFAULT     "150"
}

Parameter INET_DISABLE_BROADCAST_FWD {
    NAME        Disable forwarding of broadcasts
    SYNOPSIS    This parameter controls the forwarding of broadcasts. Set to 1 \
                to disable the forwarding of broadcasts or set to 0 to enable.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET_DST_CACHE_TO_LIVE_TIME {
    NAME        Destination cache to live
    SYNOPSIS    This parameter specifies the number of seconds an entry is kept \
                in the destination cache. The destination cache contains \
                forwarding information base (FIB) entries created in response to \
                redirect and need-frag Internet Control Message Protocol (ICMP) \
                messages.
    TYPE        char *
    DEFAULT     "600"
}

Parameter INET_ICMP_RATE_LIMIT_BUCKET_SIZE {
    NAME        ICMP rate limit bucket size
    SYNOPSIS    This parameter specifies the number of Internet Control Message \
                Protocol (ICMP) messages that the stack is allowed to send in the \
                interval specified by INET_ICMP_RATE_LIMIT_INTERVAL.
    TYPE        char *
    DEFAULT     "25000"
}

Parameter INET_ICMP_RATE_LIMIT_INTERVAL {
    NAME        ICMP rate limit interval
    SYNOPSIS    This parameter sets the Internet Control Message Protocol (ICMP) \
                rate limit interval in milliseconds.
    TYPE        char *
    DEFAULT     "1000"
}

Parameter INET_ICMP_REDIRECT_SEND {
    NAME        ICMP redirect send
    SYNOPSIS    Set this parameter to 2 if the stack should send a redirect and \
                forward the original message (default). \
                Set this parameter to 1 if the stack should send a redirect but \
                discard the original message. \
                Set this parameter to 0 if the stack should not send a redirect \
                but should still forward the original message. \
                Set this parameter to -1 if the stack should not send a redirect \
                but should discard the original message.
    TYPE        char *
    DEFAULT     "2"
}

Parameter INET_ICMP_REDIRECT_RECEIVE {
    NAME        ICMP redirect receive
    SYNOPSIS    To accept and process redirect messages, do NOT set this parameter \
                to 0.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET_ICMP_IGNORE_ECHO_REQ {
    NAME        ICMP ignore echo request
    SYNOPSIS    This parameter controls if the stack should answer to Internet \
                Control Message Protocol (ICMP) echo request messages. When set \
                to 0, the stack answers echo requests.
    TYPE        char *
    DEFAULT     "0"
}

Parameter INET_ICMP_IGNORE_TIMESTAMP_REQ {
    NAME        ICMP ignore timestamp request
    SYNOPSIS    This parameter controls if the stack should answer to Internet \
                Control Message Protocol (ICMP) timestamp request messages. When \
                set to "0", the stack answers timestamp requests.
    TYPE        char *
    DEFAULT     "0"
}

Parameter INET_ICMP_SEND_TIME_EXCEEDED {
    NAME        ICMP send time exceeded
    SYNOPSIS    If the stack should send time exceeded messages, do NOT set this \
                parameter to 0.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET_ICMP_SEND_DST_UNREACHABLE {
    NAME        ICMP send destination unreachable
    SYNOPSIS    If the stack should send destination unreachable messages, do NOT \
                set this parameter to 0.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET_ICMP_IGNORE_BROADCAST {
    NAME        ICMP ignore broadcast
    SYNOPSIS    If the network stack should ignore Internet Control Message \
                Protocol (ICMP) requests from broadcast addresses, set this \
                parameter to 1.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET_UDP_CHECKSUM {
    NAME        UDP checksum for IPv4
    SYNOPSIS    Set this parameter to 0 to disable UDP checksum for IPv4.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET_RANDOM_IP_ID {
    NAME        Random IP ID for IPv4
    SYNOPSIS    Set this parameter to 1 to enable random IP ID for IPv4.
    TYPE        char *
    DEFAULT     "0"
}

/* INCLUDE_IPCOM_USE_INET6 configuration parameters */
Parameter INET6_MIN_MTU_SIZE {
    NAME        Minimum MTU size
    SYNOPSIS    This parameter specifies the smallest path MTU expected in any \
                route. All Internet routers should be able to handle 1280 octets. \
                This value is used by some Internet Control Message Protocol \
                (ICMP) messages that include data from the packet that caused an \
                ICMP message to be sent.
    TYPE        uint
    DEFAULT     1280
}

Parameter INET6_BASE_HOP_LIMIT {
    NAME        Base hop limit
    SYNOPSIS    This parameter specifies the default hop limit for IPv6 packets.
    TYPE        char *
    DEFAULT     "64"
}

Parameter INET6_MAX_PKTS_PENDING {
    NAME        Maximum pending packets
    SYNOPSIS    This parameter specifies the number of packets that can be waiting \
                for IPv6 to link layer resolution to finish.
    TYPE        char *
    DEFAULT     "3"
}

Parameter INET6_MAX_UNICAST_SOLICIT {
    NAME        Maximum unicast solicit
    SYNOPSIS    This parameter specifies the number of unicast neighbor discovery \
                messages that should be sent for a neighbor discovery entry \
                update before starting to use multicast solicit.
    TYPE        char *
    DEFAULT     "3"
}

Parameter INET6_MAX_MULTICAST_SOLICIT {
    NAME        Maximum multicast solicit
    SYNOPSIS    This parameter specifies the number of neighbor discovery messages \
                that should be present before starting to use application solicit. \
                Setting this parameter to a non-zero value causes IPv6 ready tests \
                to fail. Change this value only if needed.
    TYPE        char *
    DEFAULT     "0"
}

Parameter INET6_MAX_APP_SOLICIT {
    NAME        Maximum application solicit
    SYNOPSIS    This parameter specifies the number of resolve messages that are \
                sent to routing/netlink sockets if the neighbor discovery probe \
                fails (or is disabled).
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET6_DAD_TRANSMITS {
    NAME        Number of duplicate address detection transmits
    SYNOPSIS    This parameter specifies the number of times the node should test \
                the address for uniqueness before assigning it to the interface. \
                (To turn off duplicate address detection, set this value to 0).
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET6_BASE_REACHABLE_TIME {
    NAME        Base reachable time
    SYNOPSIS    This parameter specifies the duration, in seconds, that an entry \
                in the Neighbor Discovery Protocol (NDP) cache is in a reachable \
                state.
    TYPE        char *
    DEFAULT     "30"
}

Parameter INET6_BASE_RETRANSMIT_TIME {
    NAME        Base retransmit time
    SYNOPSIS    This parameter specifies the number of seconds to wait between \
                retransmits.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET6_DELAY_FIRST_PROBE_TIME {
    NAME        Delay first probe time
    SYNOPSIS    This parameter specifies the duration, in seconds, to wait for \
                a stale neighbor discovery entry to become reachable before \
                forcing a probe. Packets are sent using the stale entry during \
                this time.
    TYPE        char *
    DEFAULT     "5"
}

Parameter INET6_NBR_CACHE_TO_LIVE_TIME {
    NAME        Neighbor cache to live
    SYNOPSIS    This parameter specifies the duration, in seconds, that can pass \
                before a stale entry in the neighbor cache is deleted.
    TYPE        char *
    DEFAULT     "1200"
}

Parameter INET6_DST_CACHE_TO_LIVE_TIME {
    NAME        Destination cache to live
    SYNOPSIS    This parameter specifies the duration, in seconds, that can pass \
                before an entry in the destination cache is deleted. This lifetime \
                is used on entries created as a response to redirect and need frag \
                Internet Control Message Protocol (ICMP) messages.
    TYPE        char *
    DEFAULT     "600"
}

Parameter INET6_ROUTER_LIFETIME {
    NAME        Router lifetime
    SYNOPSIS    This parameter specifies the number of seconds this router can be \
                used as a gateway after a router advertisement is sent. This \
                parameter is only used when configured as a router.
    TYPE        char *
    DEFAULT     "1800"
}

Parameter INET6_ICMP_RATE_LIMIT_BUCKET_SIZE {
    NAME        ICMP rate limit bucket size
    SYNOPSIS    This parameter specifies the number of ICMPv6 messages the stack \
                is allowed per Internet Control Message Protocol (ICMP) rate \
                limit interval which is measured in milliseconds.
    TYPE        char *
    DEFAULT     "100"
}

Parameter INET6_ICMP_RATE_LIMIT_INTERVAL {
    NAME        ICMP rate limit interval
    SYNOPSIS    Use this parameter to set the Internet Control Message Protocol \
                (ICMP) rate limit interval. The interval is measured in \
                milliseconds. To disable the rate limiter, set this value to 0.
    TYPE        char *
    DEFAULT     "1000"
}

Parameter INET6_ICMP_REDIRECT_SEND {
    NAME        ICMP redirect send
    SYNOPSIS    Set this parameter to 2 if a redirect should be sent and the \
                original message should be forwarded (default). \
                Set this parameter to 1 if a redirect should be sent but the \
                original message should be discarded. \
                Set this parameter to 0 if no redirect should be sent but the \
                original message should be forwarded. \
                Set this parameter to -1 if no redirect should be sent and the \
                original message should be discarded.
    TYPE        char *
    DEFAULT     "2"
}

Parameter INET6_ICMP_REDIRECT_RECEIVE {
    NAME        ICMP redirect receive
    SYNOPSIS    To accept and process redirect messages, set this parameter \
                to != 0.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET6_ICMP_IGNORE_ECHO_REQ {
    NAME        ICMP ignore echo request
    SYNOPSIS    If you want the stack to answer echo requests, set this parameter \
                to 0.
    TYPE        char *
    DEFAULT     "0"
}

Parameter INET6_ICMP_SEND_TIME_EXCEEDED {
    NAME        ICMP send time exceeded
    SYNOPSIS    If the stack should send time exceeded messages, set this \
                parameter to != 0.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET6_ICMP_SEND_DST_UNREACHABLE {
    NAME        ICMP send destination unreachable
    SYNOPSIS    Is the stack should send destination unreachable messages, set \
                this parameter to != 0.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET6_ACCEPT_RTADV {
    NAME        Accept router advertisement messages
    SYNOPSIS    To enable processing of router advertisement messages, set \
                this parameter to 1. To disable this option, set to 0.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET6_AUTO_CONFIG {
    NAME        Auto configure IPv6 addresses
    SYNOPSIS    To enable IPv6 address auto configuration, set this parameter \
                to 1. To disable this option, set this value to 0.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET6_ADD_AUTONOMOUS_ADDR {
    NAME        Add autonomous address
    SYNOPSIS    When this parameter is set to "yes", this node creates addresses \
                from router advertisement messages.
    TYPE        char *
    DEFAULT     "yes"
}

Parameter INET6_RTHDR0 {
    NAME        Routing header type processing
    SYNOPSIS    Use this parameter to enable or disable processing of routing \
                header type 0. Due to potential security problems, this option \
                is disabled by default.
    TYPE        char *
    DEFAULT     "0"
}

/* INCLUDE_IPNET6_AUTOCONF_PRIVACY_EXT configuration parameters */

/*
 * The following configuration parameters support RFC3041, Privacy Extensions
 * for Stateless Address Autoconfiguration in IPv6. These configuration
 * parameters are only meaningful if IPNET is compiled with the
 * IPNET_USE_RFC3401 directive.
 */

Parameter INET6_ENABLE_PRIVACY_EXTENSONS {
    NAME        Enable privacy extensions
    SYNOPSIS    Use this parameter to enable or disable privacy extensions.
    TYPE        char *
    DEFAULT     "1"
}

Parameter INET6_TEMP_VALID_LIFETIME {
    NAME        Maximum lifetime
    SYNOPSIS    This parameter specifies the maximum lifetime, in seconds, of \
                temporary addresses. The default value is 1 week.
    TYPE        char *
    DEFAULT     "604800"
}

Parameter INET6_TEMP_PREFERRED_LIFETIME {
    NAME        Maximum preferred time
    SYNOPSIS    This parameter specifies the maximum preferred time, in seconds, \
                of temporary addresses. The default value is 1 day.
    TYPE        char *
    DEFAULT     "86400"
}

Parameter INET6_REGEN_ADVANCE {
    NAME        Expired time
    SYNOPSIS    This parameter specifies the number of seconds before a current \
                temporary address becomes non-preferred and a new address is \
                generated. The RFC recommends a default value of 5 seconds. \
                However, this implementation uses 30 seconds as the default value.
    TYPE        char *
    DEFAULT     "30"
}

/* INCLUDE_IPNET6_PRIVACY_INTERFACE_CONFIGS configuration parameters */
Parameter INET6_IFLIST_ENABLE_PRIVACY_EXTENSONS {
    NAME        Enable privacy extensions
    SYNOPSIS    Use this parameter to enable or disable privacy extensions. \
                This parameter can be configured on a per-interface basis \
                using a form of "<ifparam>=<value>". For example, "eth0=1". \
                Each pair of "<ifparam>=<value>" values is semicolon separated.
    TYPE        char *
    DEFAULT     ""
}

Parameter INET6_IFLIST_TEMP_VALID_LIFETIME {
    NAME        Maximum lifetime
    SYNOPSIS    This parameter specifies the maximum lifetime, in seconds, of \
                temporary addresses. The default value is 1 week. This parameter \
                can be configured on a per-interface basis using a form of \
                "<ifparam>=<value>". For example, "eth0=604800". Each pair of \
                "<ifparam>=<value>" is semicolon separated.
    TYPE        char *
    DEFAULT     ""
}

Parameter INET6_IFLIST_TEMP_PREFERRED_LIFETIME {
    NAME        Maximum preferred time
    SYNOPSIS    This parameter specifies the maximum preferred time, in seconds, \
                for temporary addresses. The default value is 1 day. This parameter \
                can be configured on a per-interface basis using a form of \
                "<ifparam>=<value>". For example, "eth0=86400". Each pair of \
                "<ifparam>=<value>" is semicolon separated.
    TYPE        char *
    DEFAULT     ""
}

Parameter INET6_IFLIST_REGEN_ADVANCE {
    NAME        Expired time
    SYNOPSIS    This parameter specifies the number of seconds before the current \
                temporary address goes non-preferred and a new address is \
                generated. The RFC recommends a default value of 5 seconds. \
                However, this implementation uses 30 seconds as the default value. \
                This parameter can be configured on a per-interface basis using \
                a form of "<ifparam>=<value>". For example, "eth0=30". Each pair \
                of "<ifparam>=<value>" is semicolon separated.
    TYPE        char *
    DEFAULT     ""
}

/* INCLUDE_IPNET_USE_NAT configuration parameters */
Parameter IPNAT_ICMP_MAPPING_TIMEOUT {
    NAME        ICMP mapping timeout
    SYNOPSIS    This parameter specifies the timeout value in seconds until an \
                Internet Control Message Protocol (ICMP) mapping \
                expires.
    TYPE        char *
    DEFAULT     "10"
}

Parameter IPNAT_UDP_MAPPING_TIMEOUT {
    NAME        UDP mapping timeout
    SYNOPSIS    This parameter specifies the timeout value in seconds until a UDP \
                mapping expires.
    TYPE        char *
    DEFAULT     "60"
}

Parameter IPNAT_TCP_MAPPING_TIMEOUT {
    NAME        TCP mapping timeout
    SYNOPSIS    This parameter specifies the timeout value in seconds until a TCP \
                mapping expires.
    TYPE        char *
    DEFAULT     "432000"
}

Parameter IPNAT_OTHER_MAPPING_TIMEOUT {
    NAME        Other mapping timeout
    SYNOPSIS    This parameter specifies the timeout value in seconds until other \
                mappings expire.
    TYPE        char *
    DEFAULT     "60"
}

Parameter IPNAT_MAX_MAPPING {
    NAME        Maximum active mappings
    SYNOPSIS    This parameter specifies the maximum number of active NAT mappings.
    TYPE        char *
    DEFAULT     "1000"
}

Parameter IPNAT_AUTOPORT_START_INTERVAL {
    NAME        Auto port start interval
    SYNOPSIS    This parameter specifies the start of the automatically NATed \
                ports interval.
    TYPE        char *
    DEFAULT     "29000"
}

Parameter IPNAT_AUTOPORT_END_INTERVAL {
    NAME        Auto port end interval
    SYNOPSIS    This parameter specifies the end of the automatically NATed \
                ports interval.
    TYPE        char *
    DEFAULT     "29999"
}

/* INCLUDE_IPTCP configuration parameters */
#ifndef _WRS_CONFIG_COMPONENT_IPLITE
Parameter TCP_CONN_TIMEOUT {
    NAME        Connection timeout
    SYNOPSIS    This parameter defines the number of seconds IPNET tries to \
                create a TCP connection before giving up.
    TYPE        int
    DEFAULT     75
}

Parameter TCP_MAX_RETRANSMITS {
    NAME        Maximum retransmits
    SYNOPSIS    This parameter specifies the maximum number of times a TCP \
                segment is resent before giving up with an IPTCP_ERRNO_ETIMEDOUT \
                error. Exponential back off is applied before each resend (the \
                maximum time between two resends is 1 minute).
    TYPE        int
    DEFAULT     10
}

Parameter IPTCP_MAX_RETRAMSMITS_IN_TRANSIENT {
    NAME        Maximum retransmits transient states
    SYNOPSIS    This parameter specifies the maximum number of resend attempts \
                to use when the number of sessions in the transient state exceeds \
                the transient threshold set with iptcp.TransientTresh.
    TYPE        int
    DEFAULT     2
}

Parameter IPTCP_MAX_TRANSIENT {
    NAME        Maximum transient
    SYNOPSIS    This parameter specifies the maximum number of sessions that can \
                be in a transient state. Once the value is reached, the session \
                with the longest transient state period is dropped and the session \
                is set to the CLOSED state. The session is then removed from \
                the list of sessions in a transient state.
    TYPE        int
    DEFAULT     20
}

Parameter IPTCP_TRANSIENT_THRESH {
    NAME        Transient threshold
    SYNOPSIS    This threshold value refers to the number of sessions in a \
                transient state. When this threshold is exceeded, the number of \
                resend attempts is reduced to a value set by \
                iptcp.MaxRetransmitsTransientStates.
    TYPE        int
    DEFAULT     5
}

Parameter TCP_MSL {
    NAME        Maximum segment lifetime
    SYNOPSIS    TCP sockets that enter the TIME_WAIT state are in that \
                state for 2 times this value. Per RFC 793, this value should \
                be 120 sec (2 minutes), but most TCP/IP stacks (including this \
                implementation) set this value to 30 seconds.
    TYPE        int
    DEFAULT     30
}

Parameter TCP_MAX_MSS {
    NAME        Maximum segment size
    SYNOPSIS    This parameter specifies the largest maximum segment size (MSS) \
                that TCP will ever suggest. The actual MSS suggested can be \
                smaller than this number if it is depending on the MTU for the \
                interface. To use the largest MSS allowed by the MTU, set this \
                parameter to 0.
    TYPE        int
    DEFAULT     0
}

Parameter TCP_USE_TIMESTAMP {
    NAME        Use timestamp
    SYNOPSIS    This parameter determines if the timestamp option should be \
                included in all segments for peers that support it. If the \
                timestamp option should never be used, set the parameter to 0.
    TYPE        int
    DEFAULT     1
}

Parameter TCP_USE_RFC1122_URGENT_DATA {
    NAME        Use RFC1122 urgent data
    SYNOPSIS    Set this parameter to "1" to use urgent data as described in \
                RFC 1122. \
                Set this parameter to "0" to use urgent data as described in \
                RFC 793. \
                In general, set this value to 0 because that is how most \
                stacks work. To successfully pass Ixia ANVL TCP-CORE group 19 \
                tests, it must be set to 1.
    TYPE        int
    DEFAULT     0
}

Parameter TCP_SEGMENT_MULTIPLIER {
    NAME        Segment size multiplier
    SYNOPSIS    This parameter specifies the size multiplier that is used \
                on outgoing segments when the outgoing interface supports TCP \
                segmentation offload. Higher values generally give \
                better performance, but any factor higher than 2 is not \
                guaranteed to work on all network cards.
    TYPE        int
    DEFAULT     2
}

Parameter TCP_LAND_ATTACK_PROTECTION {
    NAME        LAND attack protection on TCP
    SYNOPSIS    Use this parameter to enable or disable LAND attack protection \
                on TCP. Set the value to 1 to prevent LAND attacks on a TCP \
                implementation.
    TYPE        int
    DEFAULT     1
}

Parameter TCP_ALLOW_ZERO_WINDOW
{
    NAME        Allow zero window
    SYNOPSIS    Use this parameter to enable or disable acceptance of the peer \
                window being set to zero in the ACK of the SYN/ACK. An attacker \
                can use zero window to keep the node persistent for an extended \
                time.
    TYPE        int
    DEFAULT     0
}

Parameter TCP_ALLOW_TINY_WINDOW
{
    NAME        Allow tiny window
    SYNOPSIS    Use this parameter to enable or disable acceptance of the peer \
                window being set to a value less that one maximum segment size \
                (MSS) in the ACK of the SYN/ACK. An attacker can use a tiny window \
                to keep the node persistent for an extended time. Enabling this \
                option can sometimes cause connection trouble in environments that \
                contain traffic shapers that modify the peer windows of TCP \
                segments. This is why it is allowed by default.
    TYPE        int
    DEFAULT     1
}

Parameter TCP_PERSIST_TMO
{
    NAME        Persist probe timeout
    SYNOPSIS    This parameter specifies the maximum duration, in seconds, a peer \
                can keep announcing a receive window of size zero. \
                The default value is "0" which means "infinite".
    TYPE        int
    DEFAULT     0
}

Parameter TCP_CLAMP_MSS
{
    NAME        Clamp MSS for session that goes through a gateway
    SYNOPSIS    This parameter specifies the maximum MSS that is used for TCP \
                sessions to nodes that are not link local. \
                The default value is 0 which means that path MTU \
                is used to calculate the MSS.
    TYPE        int
    DEFAULT     0
}

Parameter TCP_DEFAULT_BACKLOG_SIZE
{
    NAME        Size of the default listen backlog
    SYNOPSIS    This parameter specifies the default backlog size. This is the \
                value that is used when 0 is passed as the second argument to \
                listen( ).
    TYPE        int
    DEFAULT     5
}

Parameter TCP_KEEP_IDLE
{
    NAME        Keep alive idle time
    SYNOPSIS    This parameter specifies the default time a TCP connection must be \
                idle before the first keep-alive packet is sent (in seconds).
    TYPE        int
    DEFAULT     7200
}

Parameter TCP_KEEP_INTVL
{
    NAME        Keep alive interval
    SYNOPSIS    This parameter specifies the time between each keep-alive probe.
    TYPE        int
    DEFAULT     75
}

Parameter TCP_KEEP_CNT
{
    NAME        Number of keep alive packets
    SYNOPSIS    This parameter specifies the number of unsuccessful keep-alive \
                probes that are sent before dropping the connection.
    TYPE        int
    DEFAULT     10
}

Parameter TCP_USE_RFC6528_SECURE_ISN
{
    NAME        Use RFC6528 secure Initial Sequence Number (ISN)
    SYNOPSIS    The secure ISN described in RFC 6528 is used in a TCP three-way \
                handshake, which mitigates sequence number guessing attacks.\
                To use secure ISN, set this parameter to "1". Otherwise, set to "0".
    TYPE        int
    DEFAULT     1
}

Parameter TCP_DELAY_ACK_TIME {
    NAME        Delay ACK time
    SYNOPSIS    This parameter defines the number of milliseconds a receiver will \
                reply to a peer with a delay ACK.
    TYPE        int
    DEFAULT     200
}

Parameter TCP_IMMEDIATE_ACK_FOR_PSH {
    NAME        Immediate ACK for PSH
    SYNOPSIS    When this parameter is set to 1, there is an immediate ACK reply \
                for PSH.
    TYPE        int
    DEFAULT     1
}
#endif /* !_WRS_CONFIG_COMPONENT_IPLITE */

Parameter IPNET_INTERCOM_CONGESTION_LIMIT
{
    NAME        Congestion limit for relaying signals between stack instances
    SYNOPSIS    This parameter specifies the number of signals in the queue of \
                signals that have been relayed to a stack instance by other \
                instances, at which the relay queue (intercom) is considered \
                congested. When congested, some signals corresponding to certain \
                packets to be relayed can be dropped instead. At present this \
                applies only to TCP initial SYN segments only.
    TYPE        UINT
    DEFAULT     128
}
