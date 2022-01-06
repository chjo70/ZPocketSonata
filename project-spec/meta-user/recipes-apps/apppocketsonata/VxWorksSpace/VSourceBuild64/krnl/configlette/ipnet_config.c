/*
 * Copyright (c) 2006-2013,2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* modification history
------------------------
23aug16,kjn  Removed old, now used, code-paths
18aug16,ljl  Add a configure option for ipv4 random id. (V7NET-898)
28jun16,rjq  Set the net daemons in runtime in SMP mode.  (V7NET-811)
05jul16,ghl  Support to set IPNET parameters(IPNET_CACHE_BUFSIZE, 
             IPNET_MAX_INPUT_PKTS, IPNET_REASSEMBLY_TIMOUT) in VIP.(V7NET-880)
12mar16,wfl  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
28jan16,h_x  Support to set NUM_NET_DAEMONS to 0 in VIP, V7NET-747
24apr14,h_x  Remove secure NDP and CGA US35689
*/

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * User IPNET configuration file.
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipnet_config.h"
#ifndef IP_PORT_VXWORKS
/*
 * Cannot be defined in VxWorks since the compiler declaration of
 * standard functions will be visible here
 */
#define IPCOM_USE_CLIB_PROTO
#endif

#include <ipcom_cstyle.h>
#include <ipcom_err.h>
#include <ipcom_pkt.h>
#include <ipcom_shell.h>
#include <ipcom_sysvar.h>
#include <ipcom_os.h>

#ifdef IP_PORT_VXWORKS
/*
 * Prevent warnings from redefining IPCOM_SYSLOG_PRIORITY and
 * IPCOM_SYSLOG_FACILITY in ipnet_h.h
 */
#undef IPCOM_SYSLOG_PRIORITY
#undef IPCOM_SYSLOG_FACILITY
#endif

#include "ipnet_cmd.h"
#include "ipnet_loopback.h"
#include "ipnet_netif.h"

#ifdef IPCOM_USE_ETHERNET
#include "ipnet_eth.h"
#endif

#ifdef IPNET_USE_WLAN
#include "ipnet_wlan.h"
#endif

#ifdef IPNET_USE_TUNNEL
#include "ipnet_tunnel.h"
#endif

#ifdef IPNET_USE_SOCKDEV
#include "ipnet_sockdev.h"
#endif

#ifdef IPNET_USE_PCAP
#include "ipnet_pcap.h"
#endif

#ifdef INCLUDE_IPNET_USE_VLAN_STACKING
#include "ipnet_svlan.h"
#endif /* INCLUDE_IPNET_USE_VLAN_STACKING */

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* Definition of default values */

#ifndef IPNET_SOCK_ANON_PORT_MIN
#define IPNET_SOCK_ANON_PORT_MIN "49152"
#endif
#ifndef IPNET_SOCK_ANON_PORT_MAX
#define IPNET_SOCK_ANON_PORT_MAX "65535"
#endif
#ifndef IPNET_SOCK_DEFAULT_SEND_BUFSIZE
#define IPNET_SOCK_DEFAULT_SEND_BUFSIZE "65536"
#endif
#ifndef IPNET_SOCK_DEFAULT_RECV_BUFSIZE
#define IPNET_SOCK_DEFAULT_RECV_BUFSIZE "65536"
#endif
#ifndef IPNET_SOCK_ADDR_NOTIFY
#define IPNET_SOCK_ADDR_NOTIFY "yes"
#endif
#ifndef IPNET_SOCK_ASSIGN_RANDOM
#define IPNET_SOCK_ASSIGN_RANDOM "no"
#endif

#ifndef IPNET_ROUTE_MAX_CLONE_COUNT
#define IPNET_ROUTE_MAX_CLONE_COUNT "50000"
#endif

#ifndef IPNET_ROUTE_NEIGH_STALE_CORRECT
#define IPNET_ROUTE_NEIGH_STALE_CORRECT "yes"
#endif

#ifndef INET_SOCK_STREAM_DONT_FRAG
#define INET_SOCK_STREAM_DONT_FRAG "yes"
#endif
#ifndef INET_MULTICAST_PER_INTERFACE_FILTER
#define INET_MULTICAST_PER_INTERFACE_FILTER "no"
#endif
#ifndef INET_UDP_CHECKSUM
#define INET_UDP_CHECKSUM "yes"
#endif
#ifndef INET_ICMP_RATE_LIMIT_BUCKET_SIZE
#define INET_ICMP_RATE_LIMIT_BUCKET_SIZE "100"
#endif
#ifndef INET_ICMP_RATE_LIMIT_INTERVAL
#define INET_ICMP_RATE_LIMIT_INTERVAL "1000"
#endif
#ifndef INET_IPAIP_IFNAME_LIST
#define INET_IPAIP_IFNAME_LIST ""
#endif

#ifndef INET_RANDOM_IP_ID
#define INET_RANDOM_IP_ID "0"
#endif

#ifndef INET_BASE_HOP_LIMIT
#define INET_BASE_HOP_LIMIT "64"
#endif
#ifndef INET_MAX_PKTS_PENDING
#define INET_MAX_PKTS_PENDING "3"
#endif
#ifndef INET_MAX_UNICAST_SOLICIT
#define INET_MAX_UNICAST_SOLICIT "1"
#endif
#ifndef INET_MAX_MULTICAST_SOLICIT
#define INET_MAX_MULTICAST_SOLICIT "9"
#endif
#ifndef INET_MAX_APP_SOLICIT
#define INET_MAX_APP_SOLICIT "1"
#endif
#ifndef INET_BASE_REACHABLE_TIME
#define INET_BASE_REACHABLE_TIME "30"
#endif
#ifndef INET_BASE_RETRANSMIT_TIME
#define INET_BASE_RETRANSMIT_TIME "1"
#endif
#ifndef INET_DELAY_FIRST_PROBE_TIME
#define INET_DELAY_FIRST_PROBE_TIME "5"
#endif
#ifndef INET_NBR_MIN_RANDOM_FACTOR
#define INET_NBR_MIN_RANDOM_FACTOR "50"
#endif
#ifndef INET_NBR_MAX_RANDOM_FACTOR
#define INET_NBR_MAX_RANDOM_FACTOR "150"
#endif
#ifndef INET_NBR_LINGER_TIME
#define INET_NBR_LINGER_TIME "0"
#endif
#ifndef INET_NBR_ALWAYS_PERM
#define INET_NBR_ALWAYS_PERM "no"
#endif
#ifndef INET_ENABLE_PATH_MTU_DISCOVERY
#define INET_ENABLE_PATH_MTU_DISCOVERY "yes"
#endif
#ifndef INET_NBR_CACHE_TO_LIVE_TIME
#define INET_NBR_CACHE_TO_LIVE_TIME "1200"
#endif
#ifndef INET_DST_CACHE_TO_LIVE_TIME
#define INET_DST_CACHE_TO_LIVE_TIME "600"
#endif
#ifndef INET_DST_CACHE_TRANSIENT_TO_LIVE_MSEC
#define INET_DST_CACHE_TRANSIENT_TO_LIVE_MSEC "30000"
#endif
#ifndef INET_DST_CACHE_TRANSIENT_CNT
#define INET_DST_CACHE_TRANSIENT_CNT "8"
#endif
#ifndef INET_ICMP_REDIRECT_SEND
#define INET_ICMP_REDIRECT_SEND "2"
#endif
#ifndef INET_ICMP_REDIRECT_RECEIVE
#define INET_ICMP_REDIRECT_RECEIVE "yes"
#endif
#ifndef INET_ICMP_IGNORE_ECHO_REQ
#define INET_ICMP_IGNORE_ECHO_REQ "no"
#endif
#ifndef INET_ICMP_IGNORE_TIMESTAMP_REQ
#define INET_ICMP_IGNORE_TIMESTAMP_REQ "no"
#endif
#ifndef INET_ICMP_SEND_TIME_EXCEEDED
#define INET_ICMP_SEND_TIME_EXCEEDED "yes"
#endif
#ifndef INET_ICMP_SEND_DST_UNREACHABLE
#define INET_ICMP_SEND_DST_UNREACHABLE "yes"
#endif
#ifndef INET_ICMP_SEND_ADDR_MASK
#define INET_ICMP_SEND_ADDR_MASK "no"
#endif
#ifndef INET_ICMP_IGNORE_BROADCAST
#define INET_ICMP_IGNORE_BROADCAST "yes"
#endif
#ifndef INET_IGMP_MAX_VERSION
#define INET_IGMP_MAX_VERSION "3"
#endif
#ifndef INET_DISABLE_BROADCAST_FWD
#define INET_DISABLE_BROADCAST_FWD "yes"
#endif
#ifndef INET_SEND_GRATUITOUS_ARP
#define INET_SEND_GRATUITOUS_ARP "yes"
#endif
#ifndef INET_DELETE_ADDR_ON_DUPLICATE_DETECT
#define INET_DELETE_ADDR_ON_DUPLICATE_DETECT "yes"
#endif
#ifndef INET_ENABLE_PROXY_ARP
#define INET_ENABLE_PROXY_ARP "no"
#endif
#ifndef INET_AUTO_PROXY_ARP
#define INET_AUTO_PROXY_ARP "no"
#endif
#ifndef INET_ACCEPT_SOURCE_ROUTE
#define INET_ACCEPT_SOURCE_ROUTE "no"
#endif
#ifndef INET_ALLOW_MCAST_SRC_MAC
#define INET_ALLOW_MCAST_SRC_MAC "no"
#endif
#ifndef INET_ADDRESS_CONFLICT_DETECT
#define INET_ADDRESS_CONFLICT_DETECT "no"
#endif
#ifndef INET_AUTO_CONFIG
# ifdef IP_PORT_VXWORKS
/* VxWorks uses INET_IPAIP_IFNAME_LIST */
#  define INET_AUTO_CONFIG "no"
# else
#  define INET_AUTO_CONFIG "yes"
# endif
#endif
#ifndef INET_IPAIP_PROBE_WAIT
#define INET_IPAIP_PROBE_WAIT "1"
#endif
#ifndef INET_IPAIP_PROBE_NUM
#define INET_IPAIP_PROBE_NUM "3"
#endif
#ifndef INET_IPAIP_PROBE_MIN
#define INET_IPAIP_PROBE_MIN "1"
#endif
#ifndef INET_IPAIP_PROBE_MAX
#define INET_IPAIP_PROBE_MAX "3"
#endif
#ifndef INET_IPAIP_ANNOUNCE_WAIT
#define INET_IPAIP_ANNOUNCE_WAIT "2"
#endif
#ifndef INET_IPAIP_ANNOUNCE_NUM
#define INET_IPAIP_ANNOUNCE_NUM "2"
#endif
#ifndef INET_IPAIP_ANNOUNCE_INTERVAL
#define INET_IPAIP_ANNOUNCE_INTERVAL "2"
#endif
#ifndef INET_IPAIP_MAX_CONFLICTS
#define INET_IPAIP_MAX_CONFLICTS "10"
#endif
#ifndef INET_IPAIP_RATE_LIMIT_INTERVAL
#define INET_IPAIP_RATE_LIMIT_INTERVAL "60"
#endif
#ifndef INET_IPAIP_DEFEND_INTERVAL
#define INET_IPAIP_DEFEND_INTERVAL "10"
#endif

#ifndef INET6_ICMP_RATE_LIMIT_BUCKET_SIZE
#define INET6_ICMP_RATE_LIMIT_BUCKET_SIZE "100"
#endif
#ifndef INET6_ICMP_RATE_LIMIT_INTERVAL
#define INET6_ICMP_RATE_LIMIT_INTERVAL "1000"
#endif

#ifndef INET6_BASE_HOP_LIMIT
#define INET6_BASE_HOP_LIMIT "64"
#endif
#ifndef INET6_ADD_AUTONOMOUS_ADDR
#define INET6_ADD_AUTONOMOUS_ADDR "yes"
#endif
#ifndef INET6_MAX_PKTS_PENDING
#define INET6_MAX_PKTS_PENDING "3"
#endif
#ifndef INET6_MAX_UNICAST_SOLICIT
#define INET6_MAX_UNICAST_SOLICIT "3"
#endif
#ifndef INET6_MAX_MULTICAST_SOLICIT
#define INET6_MAX_MULTICAST_SOLICIT "0"
#endif
#ifndef INET6_MAX_APP_SOLICIT
#define INET6_MAX_APP_SOLICIT "1"
#endif
#ifndef INET6_DAD_TRANSMITS
#define INET6_DAD_TRANSMITS "1"
#endif
#ifndef INET6_BASE_REACHABLE_TIME
#define INET6_BASE_REACHABLE_TIME "30"
#endif
#ifndef INET6_BASE_RETRANSMIT_TIME
#define INET6_BASE_RETRANSMIT_TIME "1"
#endif
#ifndef INET6_DELAY_FIRST_PROBE_TIME
#define INET6_DELAY_FIRST_PROBE_TIME "5"
#endif
#ifndef INET6_NBR_MIN_RANDOM_FACTOR
#define INET6_NBR_MIN_RANDOM_FACTOR "50"
#endif
#ifndef INET6_NBR_MAX_RANDOM_FACTOR
#define INET6_NBR_MAX_RANDOM_FACTOR "150"
#endif
#ifndef INET6_NBR_LINGER_TIME
#define INET6_NBR_LINGER_TIME "0"
#endif
#ifndef INET6_NBR_ALWAYS_PERM
#define INET6_NBR_ALWAYS_PERM "no"
#endif
#ifndef INET6_NBR_CACHE_TO_LIVE_TIME
#define INET6_NBR_CACHE_TO_LIVE_TIME "1200"
#endif
#ifndef INET6_DST_CACHE_TO_LIVE_TIME
#define INET6_DST_CACHE_TO_LIVE_TIME "600"
#endif
#ifndef INET6_DST_CACHE_TRANSIENT_TO_LIVE_MSEC
#define INET6_DST_CACHE_TRANSIENT_TO_LIVE_MSEC "30000"
#endif
#ifndef INET6_DST_CACHE_TRANSIENT_CNT
#define INET6_DST_CACHE_TRANSIENT_CNT "8"
#endif
#ifndef INET6_ROUTER_LIFETIME
#define INET6_ROUTER_LIFETIME "1800"
#endif
#ifndef INET6_RT_SOL_CNT
#define INET6_RT_SOL_CNT "3"
#endif
#ifndef INET6_RT_SOL_MIN_INTERVAL
#define INET6_RT_SOL_MIN_INTERVAL "4000"
#endif
#ifndef INET6_RT_SOL_MAX_INTERVAL
#define INET6_RT_SOL_MAX_INTERVAL "4500"
#endif
#ifndef INET6_MAX_RTR_SOLICITATION_DELAY
#define INET6_MAX_RTR_SOLICITATION_DELAY "1"
#endif
#ifndef INET6_MAX_DEFAULT_GW_FROM_RA
#define INET6_MAX_DEFAULT_GW_FROM_RA "10"
#endif
#ifndef INET6_MAX_PREFIXES_FROM_RA
#define INET6_MAX_PREFIXES_FROM_RA "10"
#endif
#ifndef INET6_ICMP_REDIRECT_SEND
#define INET6_ICMP_REDIRECT_SEND "2"
#endif
#ifndef INET6_ICMP_REDIRECT_RECEIVE
#define INET6_ICMP_REDIRECT_RECEIVE "yes"
#endif
#ifndef INET6_ICMP_IGNORE_ECHO_REQ
#define INET6_ICMP_IGNORE_ECHO_REQ "no"
#endif
#ifndef INET6_ICMP_SEND_TIME_EXCEEDED
#define INET6_ICMP_SEND_TIME_EXCEEDED "yes"
#endif
#ifndef INET6_ICMP_SEND_DST_UNREACHABLE
#define INET6_ICMP_SEND_DST_UNREACHABLE "yes"
#endif
#ifndef INET6_ACCEPT_RTADV
#define INET6_ACCEPT_RTADV "yes"
#endif
#ifndef INET6_MLD_MAX_VERSION
#define INET6_MLD_MAX_VERSION "2"
#endif
#ifndef INET6_AUTO_CONFIG
#define INET6_AUTO_CONFIG "enabled"
#endif
#ifndef INET6_RTHDR0
#define INET6_RTHDR0 "disabled"
#endif
#ifndef INET6_ENABLE_PRIVACY_EXTENSONS
#define INET6_ENABLE_PRIVACY_EXTENSONS "yes"
#endif
#ifndef INET6_TEMP_VALID_LIFETIME
#define INET6_TEMP_VALID_LIFETIME "604800"
#endif
#ifndef INET6_TEMP_PREFERRED_LIFETIME
#define INET6_TEMP_PREFERRED_LIFETIME "86400"
#endif
#ifndef INET6_REGEN_ADVANCE
#define INET6_REGEN_ADVANCE "30"
#endif
#ifndef INET6_TMP_IDGEN_RETRIES
#define INET6_TMP_IDGEN_RETRIES "3"
#endif

#ifndef IPNET_MAX_REASSEMBLY_LIST_LEN
#define IPNET_MAX_REASSEMBLY_LIST_LEN 10
#endif
#ifndef IPNET_MAX_DGRAM_FRAG_LIST_LEN
#define IPNET_MAX_DGRAM_FRAG_LIST_LEN 100
#endif
#ifndef INET_MIN_MTU_SIZE
#define INET_MIN_MTU_SIZE 576
#endif
#ifndef INET6_MIN_MTU_SIZE
#define INET6_MIN_MTU_SIZE 1280
#endif

#ifndef INET6_TREAT_MOBOPT_UNKNOWN
#define INET6_TREAT_MOBOPT_UNKNOWN "no"
#endif

#ifndef IPNET_SLAB_DESC_0
#define IPNET_SLAB_DESC_0 IPNET_ETH_MTU,              IPCOM_SLAB_F_AVERAGE, 2
#endif
#ifndef IPNET_SLAB_DESC_1
#define IPNET_SLAB_DESC_1 3000,                       IPCOM_SLAB_F_FEW,     4
#endif
#ifndef IPNET_SLAB_DESC_2
#define IPNET_SLAB_DESC_2 10000,                      IPCOM_SLAB_F_ONE,    12
#endif
#ifndef IPNET_SLAB_DESC_3
#define IPNET_SLAB_DESC_3 IPNET_PKT_POOL_MAX_MTU + 1, IPCOM_SLAB_F_ONE,     8
#endif
#ifndef IPNET_SLAB_DESC_4
#define IPNET_SLAB_DESC_4 0
#endif
#ifndef IPNET_SLAB_DESC_5
#define IPNET_SLAB_DESC_5 0
#endif

#ifndef IPNET_INTERCOM_CONGESTION_LIMIT
#define IPNET_INTERCOM_CONGESTION_LIMIT  128
#endif

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    EXTERN PROTOTYPES
 ****************************************************************************
 */
#ifdef REMOVE_THIS_IFDEF_WHEN_SUPPORTING_IPBRIDGE
#ifdef INCLUDE_BRIDGE
IP_EXTERN IP_CONST Ipcom_sysvar ipbridge_conf_sysvar[];
#endif
#endif

#ifdef INCLUDE_IPTCPAO_CMD
IP_EXTERN IP_GLOBAL Ip_err iptcp_ao_cmd_install();
#endif

/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                      INTERFACE CONFIGURATION
 *===========================================================================
 *
 *  Found interface will be configured during stack boot by a configuration
 *  daemon process.
 *
 *  It is possible to have 0 or more IPv4 (inet) or/and IPv6 (inet6)
 *  addresses per interface. Addresses must be specified together with
 *  network bits 'addr/netbits'. The exact meaning of specifying
 *  'driver' as the address is OS dependent, but means that the
 *  address must be provided by the system somehow. Most OS:es allows
 *  for setting an address in the boot monitor.
 *  inet6 specific information:
 *
 *  Only one interface can have a default gateway (gateway or gateway6).
 *  gateway6 specific information:
 *      * '::' tells IPNET to use routers announced on the link in
 *        router advertisement message
 *      * scoped addresses must be specified with scope (ex: 'fe80::1%lo0')
 */
#ifdef IP_PORT_VXWORKS
IP_CONST char *ipnet_conf_interfaces[] =
{
#ifdef INCLUDE_IPNET_LOOPBACK_CONFIG
    IFCONFIG_LOOPBACK,
	IP_NULL,
#endif /* INCLUDE_IPNET_LOOPBACK_CONFIG */

    /* Configuration parameter for Ethernet interface #1 */
#ifdef INCLUDE_IPNET_IFCONFIG_1
	IFCONFIG_1,
	IP_NULL,   /* Interface configuration end marker */
#endif /* INCLUDE_IPNET_IFCONFIG_1 */

     /* Configuration parameter for Ethernet interface #2 */
#ifdef INCLUDE_IPNET_IFCONFIG_2
	IFCONFIG_2,
	IP_NULL,   /* Interface configuration end marker */
#endif /* INCLUDE_IPNET_IFCONFIG_2 */

    /* Configuration parameter for Ethernet interface #3 */
#ifdef INCLUDE_IPNET_IFCONFIG_3
	IFCONFIG_3,
	IP_NULL,   /* Interface configuration end marker */
#endif /* INCLUDE_IPNET_IFCONFIG_3 */

    /* Configuration parameter for Ethernet interface #4 */
#ifdef INCLUDE_IPNET_IFCONFIG_4
	IFCONFIG_4,
	IP_NULL,   /* Interface configuration end marker */
#endif /* INCLUDE_IPNET_IFCONFIG_4 */

	IP_NULL                                 /* Structure end marker */
};


#else /* IP_PORT_VXWORKS */
IP_CONST char *ipnet_conf_interfaces[] =
{
#ifdef IPNET_USE_LOOPBACK
    "ifname       " IPNET_IF_LOOPBACK_NAME,
#ifdef IPCOM_USE_INET
    "inet           127.0.0.1/32",     /* IPv4 loopback address */
#endif /* IPCOM_USE_INET */
#ifdef IPCOM_USE_INET6
    "inet6          ::1/128",          /* IPv6 loopback address */
    "inet6          FF01::1/16",       /* IPv6 node local broadcast */
#endif /* IPCOM_USE_INET6 */
    IP_NULL,
#endif /* IPNET_USE_LOOPBACK */

    "ifname         eth0",             /* Name of the interface to configure */
#ifdef IPCOM_USE_INET
    "devname        driver",           /* MUX device */
    "inet           driver",           /* IPv4 address and subnet */
    "gateway        driver",           /* Default IPv4 gateway */
#endif /* IPCOM_USE_INET */
#ifdef IPCOM_USE_INET6
#ifdef IP_PORT_UNIX
    "inet6          driver",           /* IPv6 address, subnet and (optionally) flags */
#else
    /* Example: "inet6 fc00::12/64", */
#endif
#endif /* IPCOM_USE_INET6 */
    IP_NULL,

    IP_NULL                            /* Structure end marker */
};
#endif /* IP_PORT_VXWORKS */

/*
 *===========================================================================
 *                      BOOT CONFIGURATION
 *===========================================================================
 *
 * Specifies a list of shell commands to run at boot. This is run before
 * the addresses are set on the interfaces so pseudo interfaces could be
 * created here and be included in the 'ipnet_conf_interfaces' list.
 * Supported commands are currently 'route', 'ifconfig' and 'nat'
 */
IP_CONST char *ipnet_conf_boot_cmd[] =
{
    /* Ex: "qc queue add dev eth1 root handle 1 fifo limit 16", */
#ifdef IPNET_USE_LOOPBACK
#ifdef IPCOM_USE_INET
    "route add -inet -dev " IPNET_IF_LOOPBACK_NAME " -net -iface -nostatic -prefixlen 8 -reject 127.0.0.0 127.0.0.1",
#endif
#ifdef IPCOM_USE_INET6
    "route add -inet6 -dev " IPNET_IF_LOOPBACK_NAME " -host -reject ::",
#ifdef IPNET_USE_RFC3879
    /* RFC 3879 chapter 4
       ...
       However, router implementations SHOULD be configured to prevent
       routing of this prefix [fec0::/10] by default.
       ... */
    "route add -inet6 -dev " IPNET_IF_LOOPBACK_NAME " -net -prefixlen 10 -blackhole fec0::",
#endif
#endif /* IPCOM_USE_INET6 */
#endif /* IPNET_USE_LOOPBACK */
    /* Ex: "route add -inet -dev eth0 -net -netmask 255.255.0.0 14.1.0.0", */
    /* Ex: "route add -inet6 -net -prefixlen 64 3ffd:: fec0::1", */
    /* Ex: "ifconfig vlan0 create vlan 2 vlanif eth0 up", */
    /* Ex: "qc queue add dev eth0 fifo limit 10", */
#if defined(IPNET_USE_NAT)
    /* Ex: "nat map eth0 0/0 -> 0/32 proxy port ftp ftp/tcp", */
    /* Ex: "nat map eth0 0/0 -> 0/32 portmap tcp/udp 18000:18999", */
    /* Ex: "nat map eth0 0/0 -> 0/32 icmpidmap icmp 19000:19999", */
    /* Ex: "nat map eth0 0/0 -> 0/32", */
    /* Ex: "nat -f natrules.cfg", */
#ifdef IPNET_USE_NAT_PT
    /* Ex: "nat pt eth1 ::/0 -> 192.168.1.100 proxy port ftp ftp/tcp", */
    /* Ex: "nat pt eth1 ::/0 -> 192.168.1.100 portmap tcp/udp 18000:18999", */
    /* Ex: "nat pt eth1 ::/0 -> 192.168.1.100 icmpidmap icmp 19000:19999 ", */
    /* Ex: "nat pt eth1 ::/0 -> 192.168.1.100", */
    /* Ex: "nat -f natrules.cfg", */
#endif
#endif

    IP_NULL
};


IP_PUBLIC Ip_u16 ipnet_conf_cache_bufsiz = 0;

IP_CONST int ipnet_conf_inq_max = IPNET_MAX_INPUT_PKTS;

/* RFC reassembly timeout default is 60 seconds. */
IP_CONST int ipnet_conf_reassembly_timeout = IPNET_REASSEMBLY_TIMEOUT;

IP_CONST unsigned ipnet_conf_memory_limit = IPNET_MEMORY_LIMIT;
IP_CONST unsigned ipnet_dst_cache_number_limit = IPNET_DST_CACHE_LIMIT;

IP_CONST unsigned ipnet_conf_intercom_congestion_limit = IPNET_INTERCOM_CONGESTION_LIMIT;

/*
 *===========================================================================
 *                       IPNET slab cache configuration
 *===========================================================================
 */

struct Ipnet_pkt_pool_slab_desc ipnet_pkt_pool_slab_desc[] = {
    { IPNET_SLAB_DESC_0 },
    { IPNET_SLAB_DESC_1 },
    { IPNET_SLAB_DESC_2 },
    { IPNET_SLAB_DESC_3 },
    { IPNET_SLAB_DESC_4 },
    { IPNET_SLAB_DESC_5 },
    { 0 }
};


/*
 *===========================================================================
 *                       IPNET dynamic configuration
 *===========================================================================
 */

#define ipnet_offsetof(v) ip_offsetof(Ipnet_shared_data, conf.v)
#define netif_offsetof(v) ip_offsetof(Ipnet_netif, conf.v)

typedef struct Ipnet_conf_var_struct {
    /*
     * Basename of the sysvar. The full name is
     * <ifname|"ipnet">.<snd>.<name>
     */
    const char *name;

    /*
     * Function that can parse a string representation for this
     * variable.
     * ifname - interface name or IP_NULL for global variables. The
     *          global variables has a sysvar that starts with "ipnet"
     * snd - second part of the sysvar, will be "sock", "route",
     *       "inet" or "inet6"
     * varname - third and later part(s) of the sysvar.
     */
    void(*parse_val)(const char *ifname,
                     const char *snd,
                     const struct Ipnet_conf_var_struct *cv);

    /*
     * Offset to where this value should be stored. Is either an
     * offset from the beginning of the ipnet_shared() pointer (sysvars that
     * starts with "ipnet") or into a "Ipnet_netif" structure (for
     * network interface specific sysvars).
     */
    Ip_size_t   offset;

    /*
     * Default value for this variable
     */
    const char *default_val;
} Ipnet_conf_var;


typedef struct Ipnet_conf_vars_struct {
    /*
     * Name of the second part of the sysvar. Will be "sock", "route",
     * "inet" or "inet6".
     */
    const char           *snd;

    /*
     * IP_TRUE if the variables pointer to by "vars" is per network
     * interface (stored in Ipnet_netif). IP_FALSE for global
     * variables (stored in "Ipnet_data" pointer to by "ipnet").
     */
    Ip_bool               is_per_netif;

    /*
     * Array of variables which all share the same "snd" value in
     * their sysvar and share the "is_per_netif" status.
     */
    const Ipnet_conf_var *vars;
} Ipnet_conf_vars;



/*
 *===========================================================================
 *                             ipnet_get_var
 *===========================================================================
 * Description: Helper function that returns the address to where the
 *              configuration variable should be stored and reads its
 *              value from the sysvar database.
 * Parameters:  ifname - network interface name or IP_NULL (global config).
 *              snd - second part of the sysvar name
 *              varname - third and later part(s) of sysvar name
 *              offset - offset into "ipnet" (ifname == IP_NULL) or
 *                       offset into "Ipnet_netif" where the
 *                       configuration must be stored.
 *              default_val - default value in case the sysvar does
 *                             not exist.
 *              new_val - will contain the new value
 * Returns:     Pointer to where the configuration must be stored.
 *
 */
IP_STATIC void *
ipnet_get_var(const char *ifname,
              const char *snd,
              const char *varname,
              Ip_size_t offset,
              int default_val,
              int *new_val,
              IP_CONST Ipcom_cmd_int_str_map *map)
{

    Ipnet_netif *netif = IP_NULL;
    void        *var;
    Ipnet_data  *net = ipnet_ptr();

    (void)net; /* prevent warning in case IPCOM_VR_MAX == 1 */

    if (ifname == IP_NULL)
        var = ((char*)ipnet_shared() + offset);
    else
    {
        netif = ipnet_if_nametonetif(ipnet_get_effective_vr(net), ifname);
        if (netif == IP_NULL)
        {
                /* No such interface */
                return IP_NULL;
        }
        var = ((char*)netif + offset);
    }

    *new_val = ipnet_sysvar_get_as_int_vr(netif,
                                          snd,
                                          varname,
                                          default_val,
                                          map,
                                          (netif
                                           ? netif->vr_index
                                           : ipnet_get_effective_vr(net)));
    return var;
}


/*
 *===========================================================================
 *                              ipnet_int
 *===========================================================================
 * Description: Sets an integer IPNET configuration variable.
 * Parameters:  ifname - network interface or IP_NULL
 *              snd - second part of sysvar
 *              cv - variable description
 * Returns:
 *
 */
IP_STATIC void
ipnet_int(const char *ifname,
          const char *snd,
          const Ipnet_conf_var *cv)
{
    int  *var;
    int   new_val;
    int   default_val;
    char *endptr;

    default_val = (int)ipcom_strtol(cv->default_val, &endptr, 0);
    if (cv->default_val == endptr)
    {
        /*
         * The default value given for cv->name is not a number
         */
        IP_PANIC();
    }

    var = ipnet_get_var(ifname,
                        snd,
                        cv->name,
                        cv->offset,
                        default_val,
                        &new_val,
                        IP_NULL);
    if (var)
        *var = new_val;
}


/*
 *===========================================================================
 *                               ipnet_bool
 *===========================================================================
 * Description: Sets a boolean IPNET configuration variable.
 * Parameters:  ifname - network interface or IP_NULL
 *              snd - second part of sysvar
 *              cv - variable description
 * Returns:
 *
 */
IP_STATIC void
ipnet_bool(const char *ifname,
           const char *snd,
           const Ipnet_conf_var *cv)
{
    Ip_bool *var;
    int      new_val;
    int      default_val;

    if (ipcom_cmd_str_to_key2(ipnet_bool_map,
                              cv->default_val,
                              &default_val) < 0)
    {
        /*
         * cv->name contains an invalid string as default boolean
         * value
         */
        IP_PANIC();
    }

    var = ipnet_get_var(ifname,
                        snd,
                        cv->name,
                        cv->offset,
                        default_val,
                        &new_val,
                        ipnet_bool_map);
    if (var)
        *var = new_val;
}


/*
 *===========================================================================
 *                              ipnet_string
 *===========================================================================
 * Description: Set a string IPNET configuration variable.
 * Parameters:  ifname - must be IP_NULL (global option) for now
 *              snd - second part of the sysvar
 *              cv - variable specification.
 * Returns:
 *
 */
#if defined(IPCOM_USE_INET) && defined(IPNET_USE_RFC3927)
/* Nothing except RFC3927 uses string variables right now */
IP_STATIC void
ipnet_string(const char *ifname,
             const char *snd,
             const Ipnet_conf_var *cv)
{
    const char **pstr;
    char         sysvar_name[40];

    /* Only support for global variables for now */
    ip_assert(ifname == IP_NULL);

    if (ipcom_snprintf(sysvar_name,
                       sizeof(sysvar_name),
                       "ipnet.%s.%s",
                       snd, cv->name) >= (int)sizeof(sysvar_name))
        /*
         * The 'sysvar_name' buffer is too small.
         */
        IP_PANIC();

    pstr = (const char **) ((Ip_ptrdiff_t) &ipnet_shared()->conf + cv->offset);
    if (*pstr != cv->default_val)
        ipcom_free((void*)*pstr);

    *pstr = ipcom_sysvar_get(sysvar_name, IP_NULL, IP_NULL);
    if (*pstr == IP_NULL && ipcom_strlen(cv->default_val) > 0)
        *pstr = cv->default_val;
}
#endif /* IPCOM_USE_INET && IPNET_USE_RFC3927*/


/*
 * Socket specific configuration
 */
IP_STATIC IP_CONST Ipnet_conf_var ipnet_sock_conf_var[] =
{
    /*
     * Defines the lowest port number used as an ephemeral port number
     * (source port for sockets that has not been named with a call to
     * ipcom_bind()).
     */
    { "AnonPortMin", ipnet_int, ipnet_offsetof(sock.anon_port_min), IPNET_SOCK_ANON_PORT_MIN },

    /*
     * Defines the highest port number used as an ephemeral port
     * number (source port for sockets that has not been named with a
     * call to ipcom_bind()).
     */
    { "AnonPortMax", ipnet_int, ipnet_offsetof(sock.anon_port_max), IPNET_SOCK_ANON_PORT_MAX },

    /* The default size of the socket send buffer */
    { "DefaultSendBufSize", ipnet_int, ipnet_offsetof(sock.default_send_buf_size), IPNET_SOCK_DEFAULT_SEND_BUFSIZE },

    /* The default size of the socket receive buffer */
    { "DefaultRecvBufSize", ipnet_int, ipnet_offsetof(sock.default_recv_buf_size), IPNET_SOCK_DEFAULT_RECV_BUFSIZE },

    /*
     * Set to >0 to get notification on sockets bound to an address
     * that has just been removed
     */
    { "AddrNotify", ipnet_bool,ipnet_offsetof(sock.addr_notify), IPNET_SOCK_ADDR_NOTIFY },

    { "AssignRandom", ipnet_bool,ipnet_offsetof(sock.assign_random), IPNET_SOCK_ASSIGN_RANDOM },

    { IP_NULL, }
};


/*
 * Route/neighbor specific configuration
 */
IP_STATIC IP_CONST Ipnet_conf_var ipnet_route_conf_var[] =
{
    /*
     * Defines a system wide limit of the number of neighbor (ARP+NDP)
     * entries that can exist in the host to prevent a DoS attack.
     * MaxCloneCount should be set to a value higher that the total
     * number of ARP+NDP expected under normal conditions.
     */
    { "MaxCloneCount", ipnet_int, ipnet_offsetof(route.max_clone_count), IPNET_ROUTE_MAX_CLONE_COUNT },
    /*
     * When set, a packet sent on a non-primary stack instance using a
     * neighbor cache entry in STALE state causes the primary stack instance
     * to drive the STALE -> DELAY state transition.  The primary stack
     * will then start probing after the DELAY first probe time unless
     * it obtains a forward progress indication for the neighbor.  Assuming
     * the probe is successfully replied to, this allows the neighbor entry to
     * be continuously usable for all stack instances.
     *
     * When cleared, if a neighbor in (global) STALE state is sent to only by
     * non-primary network stack instances, the primary instance, which drives
     * all global neighbor state transitions, may time out and delete the
     * STALE neighbor entry even though other stack instances have been sending
     * to it. This may cause an interruption in traffic as the neighbor
     * becomes INCOMPLETE briefly after it is deleted, until some stack
     * instance sends to the neighbor again and probing (done by the primary
     * instance) completes.
     *
     * The behavior with NeighStaleCorrect set is more correct.  However,
     * we make this optional since the set behavior is not absolutely
     * necessary for operation and it does impose some additional load on the
     * primary stack instance; the amount of additional load is roughly
     * proportional to the total number of neighbors in use in the system.
     */

    { "NeighStaleCorrect", ipnet_bool, ipnet_offsetof(route.neigh_stale_correct), IPNET_ROUTE_NEIGH_STALE_CORRECT },

    { IP_NULL, }
};


#ifdef IPCOM_USE_INET
/*
 * Global IPv4 configuration
 */
IP_STATIC IP_CONST Ipnet_conf_var ipnet_inet_conf_var[] =
{
    /*
     * IcmpRatelimitBucketsize is the number of ICMP messages the
     * stack is allowed to per IcmpRatelimitInterval millisecond
     * interval. Set IcmpRatelimitInterval to 0 to disable the
     * ratelimiter
     */
    { "IcmpRatelimitBucketsize", ipnet_int, ipnet_offsetof(inet.icmp_rate_limit_bucket_size), INET_ICMP_RATE_LIMIT_BUCKET_SIZE },
    { "IcmpRatelimitInterval", ipnet_int, ipnet_offsetof(inet.icmp_rate_limit_interval), INET_ICMP_RATE_LIMIT_INTERVAL },

    /*
     * Controls if the don't frag bit be set in packets sent from
     * SOCK_STREAM and SOCK_SEQPACKET sockets. Default is "yes".
     * NOTE: enable this option and disable path MTU discovery is a
     * very bad idea since it might prevent traffic from being
     * delivered between the nodes.
     */
    { "StreamSockDontFrag", ipnet_bool, ipnet_offsetof(inet.sock_stream_dont_frag), INET_SOCK_STREAM_DONT_FRAG },

    /*
     * Controls if multicast packets can be filtered per interface.
     * Default is "no".
     */
    { "MuticastPerInterfaceFilter", ipnet_bool, ipnet_offsetof(inet.multicast_per_interface_filter), INET_MULTICAST_PER_INTERFACE_FILTER },

    /*
     * Controls if IPv4 UDP sockets should be configured to include
     * an Internet checksum on all generated UDP packets by default.
     * Default is "yes".
     */
    { "UdpChecksum", ipnet_bool, ipnet_offsetof(inet.udp_checksum), INET_UDP_CHECKSUM },

#ifdef IPNET_USE_RFC3927
    /*
     * List of interfaces that can configure a link-local IPv4
     * address. NOTE: the same thing can also be configured using
     * the network interface specific variable "AutoConf".
     */
    { "linklocal.interfaces",  ipnet_string, ipnet_offsetof(inet.ll_if_list), INET_IPAIP_IFNAME_LIST },
#endif

    /*
     * Controls if IPv4 packets ID should be random for security concern,
     * however that's not totally random.
     * Default is "no".
     */
    { "RandomIpId", ipnet_bool, ipnet_offsetof(inet.random_ip_id), INET_RANDOM_IP_ID },


    { IP_NULL, }
};


/*
 * Per-network-interface IPv4 configuration
 */
IP_STATIC IP_CONST Ipnet_conf_var ipnet_inet_if_conf_var[] =
{
    /* The default hop limit for IPv4 packets */
    { "BaseHopLimit", ipnet_int, netif_offsetof(inet.base_hop_limit), INET_BASE_HOP_LIMIT },

    /*
     * Number of packets that can be waiting for IPv4 to link layer
     * resolution to finish
     */
    { "MaxPending", ipnet_int, netif_offsetof(inet.max_pending),  INET_MAX_PKTS_PENDING },

    /*
     * Number of unicast ARP request messages shall be sent before
     * starting to use multicast solicits
     */
    { "MaxUnicastSolicit", ipnet_int, netif_offsetof(inet.max_unicast_solicit), INET_MAX_UNICAST_SOLICIT },

    /*
     * Number of ARP request messages that shall be sent before
     * starting to use application probes
     */
    { "MaxMulticastSolicit", ipnet_int, netif_offsetof(inet.max_multicast_solicit), INET_MAX_MULTICAST_SOLICIT },

    /*
     * Number of resolve message that is sent to routing/netlink
     * sockets if ARP probes failed (or is disabled)
     */
    { "MaxApplicationSolicit", ipnet_int, netif_offsetof(inet.max_application_solicit), INET_MAX_APP_SOLICIT },

    /*
     * Duration, in seconds, that an entry in the ARP cache is in
     * reachable state RFC 1122 chapter 2.3.2.1 recommends a value in
     * the order of minutes and the equivalent feature in IPv6 (NDP)
     * requires it to be 30 seconds.
     */
    { "BaseReachableTime", ipnet_int, netif_offsetof(inet.base_reachable_time), INET_BASE_REACHABLE_TIME },

    /* Number of seconds to wait between retransmits */
    { "BaseRetransmitTime", ipnet_int, netif_offsetof(inet.base_retransmit_time), INET_BASE_RETRANSMIT_TIME },

    /*
     * Duration, in seconds, to wait for a stale ARP entry to become
     * reachable before forcing a probe, packets will be sent using
     * the stale entry during this time
     */
    { "DelayFirstProbeTime", ipnet_int, netif_offsetof(inet.delay_first_probe_time), INET_DELAY_FIRST_PROBE_TIME },

    /*
     * Duration, in seconds, that can pass before a stale entry in the
     * ARP cache is deleted
     */
    { "NeighborCacheToLive", ipnet_int, netif_offsetof(inet.neigh_cache_to_live), INET_NBR_CACHE_TO_LIVE_TIME },

    /*
     * RFC 4891 requires that the reachable time should be uniformly
     * distributed between MIN_RANDOM_FACTOR and MAX_RANDOM_FACTOR
     * times BaseReachableTime. MinRandomFactor and MaxRandomFactor
     * contains that multiplier as a percent value with default value
     * of 50 and 150 respectively. RFC 4891 applies to IPv6 and no
     * corresponding RFC exists for IPv4, so RFC 4891 values are used
     * for IPv4 as well.
     */
    { "MinRandomFactor", ipnet_int, netif_offsetof(inet.neigh_min_random_factor), INET_NBR_MIN_RANDOM_FACTOR },
    { "MaxRandomFactor", ipnet_int, netif_offsetof(inet.neigh_max_random_factor), INET_NBR_MAX_RANDOM_FACTOR },

    /*
     * Time that a neighbor will linger in state incomplete or probe
     * if all proble fails. Default value is 0 (do not linger). A
     * non-zero linger time allows for some time where an user-made
     * application can try to resolve the link layer address.
     */
    { "LingerTime", ipnet_int, netif_offsetof(inet.neigh_linger_time), INET_NBR_LINGER_TIME },

    /*
     * Enable this option if neighbors should stay in reachable state
     * forever. This can be useful in certain throughput measurement
     * scenarios where neighbor probes might get lost or not being
     * answered at all. This option is disabled by default.
     */
    { "SmartbitNdMode", ipnet_bool, netif_offsetof(inet.neigh_always_perm), INET_NBR_ALWAYS_PERM },

    /*
     * Enable/disable path MTU discovery. This option is enabled by
     * default.
     */
    { "EnablePathMtuDiscovery", ipnet_bool, netif_offsetof(inet.enable_path_mtu_discovery), INET_ENABLE_PATH_MTU_DISCOVERY },

    /*
     * Duration, in seconds, that can pass before an entry in the
     * destination cache is deleted, this lifetime is used by on
     * entries created as a response to redirect and packet too big
     * ICMP messages
     */
    { "DstCacheToLive", ipnet_int, netif_offsetof(inet.dst_cache_to_live), INET_DST_CACHE_TO_LIVE_TIME },

    /*
     * Duration, in msec, that the destination cache entry is
     * considered transient and uses a short lifetime.
     */
    { "DstCacheTransientToLiveMsec", ipnet_int, netif_offsetof(inet.dst_cache_transient_to_live_msec), INET_DST_CACHE_TRANSIENT_TO_LIVE_MSEC },

    /*
     * Number of times the destination cache entry can be used and
     * still be considered transient. The lifetime is set to
     * DstCacheToLive seconds if the entry is used more times during
     * DstCacheTransientToLiveMsec milliseconds.
     */
    { "DstCacheTransientCnt", ipnet_int, netif_offsetof(inet.dst_cache_transient_cnt), INET_DST_CACHE_TRANSIENT_CNT },

    /*
     *  2 if a redirect shall be sent and the original message shall
     *    be forwarded (default)
     *  1 if a redirect shall be sent but the original message shall
     *    be discarded
     *  0 if no redirect shall be sent but the original message shall
     *    be forwarded
     * -1 if no redirect shall be sent and the original message shall
     *    be discarded
     */
    { "IcmpRedirectSend", ipnet_int, netif_offsetof(inet.icmp_redirect_send), INET_ICMP_REDIRECT_SEND },

    /* != 0 if redirect messages shall be accepted and processed */
    { "IcmpRedirectReceive", ipnet_bool, netif_offsetof(inet.icmp_redirect_receive), INET_ICMP_REDIRECT_RECEIVE },

    /* == 0 if the stack shall answer to echo requests */
    { "IcmpIgnoreEchoRequest", ipnet_bool, netif_offsetof(inet.icmp_ignore_echo_req), INET_ICMP_IGNORE_ECHO_REQ },

    /* == 0 if the stack shall answer to timestamp requests */
    { "IcmpIgnoreTimestampRequest", ipnet_bool, netif_offsetof(inet.icmp_ignore_timestamp_req), INET_ICMP_IGNORE_TIMESTAMP_REQ },

    /* != 0 if the stack shall send time exceeded messages */
    { "IcmpSendTimeExceeded", ipnet_bool, netif_offsetof(inet.icmp_send_time_exceeded), INET_ICMP_SEND_TIME_EXCEEDED },

    /* != 0 if the stack shall send destination unreachable */
    { "IcmpSendDestinationUnreachable", ipnet_bool, netif_offsetof(inet.icmp_send_dst_unreach), INET_ICMP_SEND_DST_UNREACHABLE },

    /* != 0 if the stack shall respond to RFC 950 address mask requests */
    { "IcmpSendAddrMask", ipnet_bool, netif_offsetof(inet.icmp_send_addr_mask), INET_ICMP_SEND_ADDR_MASK },

    /* == 0 if the stack should process ICMPs with src addr =
     * broadcast (SMURF attack disable)  */
    { "IcmpIgnoreBroadcast", ipnet_bool, netif_offsetof(inet.icmp_ignore_broadcast), INET_ICMP_IGNORE_BROADCAST },

    /* Highest IGMP version that this node will use (1, 2 or 3) */
    { "IgmpVersion", ipnet_int, netif_offsetof(inet.igmp_max_version), INET_IGMP_MAX_VERSION },

    /* == 1 if the stack shouldnt forward broadcasts(directed or otherwise)  */
    { "DontForwardBroadcast", ipnet_bool, netif_offsetof(inet.dont_forward_broadcast), INET_DISABLE_BROADCAST_FWD },

    /* != 0 if the stack shall send */
    { "SendGratuitousArp", ipnet_bool, netif_offsetof(inet.send_gratuitous_arp), INET_SEND_GRATUITOUS_ARP },

    /*
     * != 0 if the stack shall automatically remove a configured
     * address upon duplicate address detection (Gratuitous ARP)
     */
    { "DeleteAddressOnDuplicateDetect", ipnet_bool, netif_offsetof(inet.delete_addr_on_duplicate_detect), INET_DELETE_ADDR_ON_DUPLICATE_DETECT },

    /*
     * != 0 if the stack shall do proxy arping for network routes
     * tagged with the proxy arp flag.
     */
    { "EnableNetworkProxyArp", ipnet_bool, netif_offsetof(inet.network_proxy_arp), INET_ENABLE_PROXY_ARP },

    /*
     * != 0 if the stack automatically shall tag all interface address
     * network routes as proxy arp.
     */
    { "AutoProxyArp", ipnet_bool, netif_offsetof(inet.auto_proxy_arp), INET_AUTO_PROXY_ARP },

    /*
     * != 0 if the stack automatically shall tag all interface address
     * network routes as proxy arp.
     */
    { "AcceptSourceRoute", ipnet_bool, netif_offsetof(inet.accept_source_route), INET_ACCEPT_SOURCE_ROUTE },

    /*
     * Determines if the node should accept Ethernet frames with a
     * multicast source MAC. Default is "no".
     */
    { "AllowMcastSrcMac", ipnet_bool, netif_offsetof(inet.allow_mcast_src_mac), INET_ALLOW_MCAST_SRC_MAC },

#ifdef IPNET_USE_RFC5227
    /*
     * Address conflict detection according to RFC5227 on all IPv4 addresses.
     * This configuration can also be set per interface by replacing
     * "ipnet." with "ifname." (ex: eth0.inet.AddressConflictDetect)
     */
    { "AddressConflictDetect", ipnet_bool, netif_offsetof(inet.address_conflict_detect),  INET_ADDRESS_CONFLICT_DETECT },
#endif

#ifdef IPNET_USE_RFC3927
    /*
     * Autoconfigure a link-local IPv4 address.  Currently only
     * implemented for Ethernet interfaces This configuration can also
     * be set per interface by replacing "ipnet." with "ifname." (ex:
     * eth0.inet.AutoConf)
     */
    { "AutoConf", ipnet_bool, netif_offsetof(inet.auto_conf),  INET_AUTO_CONFIG },

#endif
#if defined(IPNET_USE_RFC3927) || defined(IPNET_USE_RFC5227)
    /*
     * The host will wait [0..PROBE_WAIT] seconds before creating a
     * link local IPv4 and start checking it for uniqueness
     */
    { "linklocal.PROBE_WAIT", ipnet_int, netif_offsetof(inet.ll_probe_wait), INET_IPAIP_PROBE_WAIT },

    /*
     * Number of times a link local address is checked for uniqueness
     * before being assigned
     */
    { "linklocal.PROBE_NUM", ipnet_int, netif_offsetof(inet.ll_probe_num), INET_IPAIP_PROBE_NUM },

    /* The next probe is sent after [PROBE_MIN..PROBE_MAX] seconds */
    { "linklocal.PROBE_MIN", ipnet_int, netif_offsetof(inet.ll_probe_min), INET_IPAIP_PROBE_MIN },
    { "linklocal.PROBE_MAX", ipnet_int, netif_offsetof(inet.ll_probe_max), INET_IPAIP_PROBE_MAX },

    /*
     * Time to wait (in seconds) before starting to announce the
     * selected address.  The address will not be defended if another
     * announcement is heard during this period
     * The address has been assigned to the interface when the annouce
     * period starts
     */
    { "linklocal.ANNOUNCE_WAIT", ipnet_int, netif_offsetof(inet.ll_announce_wait), INET_IPAIP_ANNOUNCE_WAIT },

    /* The number of announcements to send */
    { "linklocal.ANNOUNCE_NUM", ipnet_int, netif_offsetof(inet.ll_announce_num), INET_IPAIP_ANNOUNCE_NUM },

    /* Seconds between announcements */
    { "linklocal.ANNOUNCE_INTERVAL", ipnet_int, netif_offsetof(inet.ll_announce_interval), INET_IPAIP_ANNOUNCE_INTERVAL },

    /*
     * Maximum number of address collisions that is allowed before
     * rate limiting is applied to creation of next address
     */
    { "linklocal.MAX_CONFLICTS", ipnet_int, netif_offsetof(inet.ll_max_conflicts), INET_IPAIP_MAX_CONFLICTS },

    /*
     * Delay between successive address regeneration attempts when the
     * regeneration is rate limited.
     */
    { "linklocal.RATE_LIMIT_INTERVAL", ipnet_int, netif_offsetof(inet.ll_rate_limit_interval), INET_IPAIP_RATE_LIMIT_INTERVAL },

    /* Minimum interval between defensive ARPs */
    { "linklocal.DEFEND_INTERVAL", ipnet_int, netif_offsetof(inet.ll_defend_interval), INET_IPAIP_DEFEND_INTERVAL },
#endif /* defined(IPNET_USE_RFC3927) || defined(IPNET_USE_RFC5227) */

    { IP_NULL, }
};
#endif /* IPCOM_USE_INET */


#ifdef IPCOM_USE_INET6
/*
 * Global IPv6 configuration
 */
IP_STATIC IP_CONST Ipnet_conf_var ipnet_inet6_conf_var[] =
{
    /*
     * IcmpRatelimitBucketsize is the number of ICMPv6 messages the
     * stack is allowed to per IcmpRatelimitInterval millisecond
     * interval. Set IcmpRatelimitInterval to 0 to disable the
     * ratelimiter
     */
    { "IcmpRatelimitBucketsize", ipnet_int, ipnet_offsetof(inet6.icmp_rate_limit_bucket_size), INET6_ICMP_RATE_LIMIT_BUCKET_SIZE },
    { "IcmpRatelimitInterval", ipnet_int, ipnet_offsetof(inet6.icmp_rate_limit_interval), INET6_ICMP_RATE_LIMIT_INTERVAL },

    { IP_NULL, }
};


/*
 * Per-network-interface IPv6 configuration
 */
IP_STATIC IP_CONST Ipnet_conf_var ipnet_inet6_if_conf_var[] =
{
    /* The default hop limit for IPv6 packets */
    { "BaseHopLimit", ipnet_int, netif_offsetof(inet6.base_hop_limit), INET6_BASE_HOP_LIMIT },

    /*
     * Should this node create addresses from router advertisement
     * messages
     */
    { "AddAutonomousAddr", ipnet_bool, netif_offsetof(inet6.add_autonomous_addr), INET6_ADD_AUTONOMOUS_ADDR },

    /*
     * Number of packets that can be waiting for IPv6 to link layer
     * resolution to finish
     */
    { "MaxPending", ipnet_int, netif_offsetof(inet6.max_pending), INET6_MAX_PKTS_PENDING },

    /*
     * Number of unicast neighbor discovery messages shall be sent for
     * ND entry update before starting to use multicast solicit
     */
    { "MaxUnicastSolicit", ipnet_int, netif_offsetof(inet6.max_unicast_solicit), INET6_MAX_UNICAST_SOLICIT },

    /*
     * Number of neighbor discovery messages shall be resent before
     * staring to use application solicit. setting this !=0 will cause
     * IPv6 ready tests to fail, so change it only if you know what
     * you are doing
     */
    { "MaxMulticastSolicit", ipnet_int, netif_offsetof(inet6.max_multicast_solicit), INET6_MAX_MULTICAST_SOLICIT },

    /*
     * Number of resolve message that is sent to routing/netlink
     * sockets if ND probes failed (or is disabled)
     */
    { "MaxApplicationSolicit", ipnet_int, netif_offsetof(inet6.max_application_solicit), INET6_MAX_APP_SOLICIT },

    /*
     * Number of times the node shall test the address for uniqueness
     * before assigning it to the interface (set to 0 to turn of
     * Duplicate Address Detection)
     */
    { "DupAddrDetectTransmits", ipnet_int, netif_offsetof(inet6.dad_transmits), INET6_DAD_TRANSMITS },

    /*
     * Duration, in seconds, that an entry in the NDP cache is in
     * reachable state
     */
    { "BaseReachableTime", ipnet_int, netif_offsetof(inet6.base_reachable_time), INET6_BASE_REACHABLE_TIME },

    /*  Number of seconds to wait between retransmits */
    { "BaseRetransmitTime", ipnet_int, netif_offsetof(inet6.base_retransmit_time), INET6_BASE_RETRANSMIT_TIME },

    /*
     * Duration, in seconds, to wait for a stale ND entry to become
     * reachable before forcing a probe, packets will be sent using
     * the stale entry during this time
     */
    { "DelayFirstProbeTime", ipnet_int, netif_offsetof(inet6.delay_first_probe_time), INET6_DELAY_FIRST_PROBE_TIME },

    /*
     * Duration, in seconds, that can pass before a stale entry in the neighbor
     * cache is deleted
     */
    { "NeighborCacheToLive", ipnet_int, netif_offsetof(inet6.neigh_cache_to_live), INET6_NBR_CACHE_TO_LIVE_TIME },

    /*
     * RFC 4891 requires that the reachable time should be uniformly
     * distributed between MIN_RANDOM_FACTOR and MAX_RANDOM_FACTOR
     * times BaseReachableTime. MinRandomFactor and MaxRandomFactor
     * contains that multiplier as a percent value with default value
     * of 50 and 150 respectivly.
     */
    { "MinRandomFactor", ipnet_int, netif_offsetof(inet6.neigh_min_random_factor), INET6_NBR_MIN_RANDOM_FACTOR },
    { "MaxRandomFactor", ipnet_int, netif_offsetof(inet6.neigh_max_random_factor), INET6_NBR_MAX_RANDOM_FACTOR },

    /*
     * Time that a neighbor will linger in state incomplete or probe
     * if all proble fails. Default value is 0 (do not linger). A
     * non-zero linger time allows for some time where an user-made
     * application can try to resolve the link layer address.
     */
    { "LingerTime", ipnet_int, netif_offsetof(inet6.neigh_linger_time), INET6_NBR_LINGER_TIME },

    /*
     * Enable this option if neighbors should stay in reachable state
     * forever. This can be useful in certain throughput measurement
     * scenarios where neighbor probes might get lost or not being
     * answered at all. This option is disabled by default.
     */
    { "SmartbitNdMode", ipnet_bool, netif_offsetof(inet6.neigh_always_perm), INET6_NBR_ALWAYS_PERM },

    /*
     * Duration, in seconds, that can pass before an entry in the
     * destination cache is deleted, this lifetime is used by on
     * entries created as a response to redirect and need frag ICMP
     * messages
     */
    { "DstCacheToLive", ipnet_int, netif_offsetof(inet6.dst_cache_to_live),  INET6_DST_CACHE_TO_LIVE_TIME },

    /*
     * Duration, in msec, that the destination cache entry is
     * considered transient and uses a short lifetime.
     */
    { "DstCacheTransientToLiveMsec", ipnet_int, netif_offsetof(inet6.dst_cache_transient_to_live_msec), INET6_DST_CACHE_TRANSIENT_TO_LIVE_MSEC },

    /*
     * Number of times the destination cache entry can be used and
     * still be considered transient. The lifetime is set to
     * DstCacheToLive seconds if the entry is used more times during
     * DstCacheTransientToLiveMsec milliseconds.
     */
    { "DstCacheTransientCnt", ipnet_int, netif_offsetof(inet6.dst_cache_transient_cnt), INET6_DST_CACHE_TRANSIENT_CNT },

    /*
     * The number of seconds this router can be used as gateway after
     * a router advertisement had been sent, only used when configured
     * as a router
     */
    { "RouterLifetime", ipnet_int, netif_offsetof(inet6.router_lifetime), INET6_ROUTER_LIFETIME },

    /*
     * Maximum number of router solicitation that will sent when the
     * node is attached to a link. Set to 0 to disable router
     * solicitations.
     */
    { "RtSolicitationCount", ipnet_int, netif_offsetof(inet6.rt_sol_cnt), INET6_RT_SOL_CNT },

    /*
     * Minimum duration, in milliseconds, between two router
     * solicitations messages sent to the same link
     */
    { "RtSolicitationMinInterval", ipnet_int, netif_offsetof(inet6.rt_sol_min_interval), INET6_RT_SOL_MIN_INTERVAL },

    /*
     * Maximum duration, in milliseconds, between two router
     * solicitations messages sent to the same link
     */
    { "RtSolicitationMaxInterval",  ipnet_int, netif_offsetof(inet6.rt_sol_max_interval), INET6_RT_SOL_MAX_INTERVAL },

    /*
     * RFC 4862 chapter 5.4.2
     * Even if the Neighbor Solicitation is not going to be the first
     * message sent, the node SHOULD delay joining the solicited-node
     * multicast address by a random delay between 0 and
     * MAX_RTR_SOLICITATION_DELAY if the address being checked is
     * configured by a router advertisement message sent to a
     * multicast address.  The delay will avoid similar congestion
     * when multiple nodes are going to configure addresses by
     * receiving the same single multicast router advertisement.
     */
    { "MaxRtrSolicitationDelay", ipnet_int, netif_offsetof(inet6.max_rt_sol_delay), INET6_MAX_RTR_SOLICITATION_DELAY },

    /*
     * Maximum number of default gateways that can be added as a
     * result of receiving router advertisement message on the link.
     * Default is 10.
     */
    { "MaxDefaultGwFromRa", ipnet_int, netif_offsetof(inet6.max_default_gw_from_ra), INET6_MAX_DEFAULT_GW_FROM_RA },

    /*
     * Maximum number of prefixes that can he added as a result of
     * receiving router advertisement message on the link.
     * Default is 10.
     */
    { "MaxPrefixesFromRa", ipnet_int, netif_offsetof(inet6.max_prefixes_from_ra), INET6_MAX_PREFIXES_FROM_RA },

   /*
     *  2 if a redirect shall be sent and the original message shall
     *    be forwarded (default)
     *  1 if a redirect shall be sent but the original message shall
     *    be discarded
     *  0 if no redirect shall be sent but the original message shall
     *    be forwarded
     * -1 if no redirect shall be sent and the original message shall
     *    be discarded
     */
    { "IcmpRedirectSend", ipnet_int, netif_offsetof(inet6.icmp_redirect_send), INET6_ICMP_REDIRECT_SEND },

    /* != 0 if redirect messages shall be accepted and processed */
    { "IcmpRedirectReceive", ipnet_bool, netif_offsetof(inet6.icmp_redirect_receive), INET6_ICMP_REDIRECT_RECEIVE },

    /* == 0 if the stack shall answer to echo requests */
    { "IcmpIgnoreEchoRequest", ipnet_bool, netif_offsetof(inet6.icmp_ignore_echo_req), INET6_ICMP_IGNORE_ECHO_REQ },

    /* != 0 if the stack shall send time exceeded messages */
    { "IcmpSendTimeExceeded", ipnet_bool, netif_offsetof(inet6.icmp_send_time_exceeded), INET6_ICMP_SEND_TIME_EXCEEDED },

    /* != 0 if the stack shall send destination unreachable */
    { "IcmpSendDestinationUnreachable", ipnet_bool, netif_offsetof(inet6.icmp_send_dst_unreach), INET6_ICMP_SEND_DST_UNREACHABLE },

    /* Enable/disable processing of router advertisements message */
    { "AcceptRtAdv", ipnet_bool, netif_offsetof(inet6.accept_rt_adv), INET6_ACCEPT_RTADV },

    /* Highest MLD protocol version this node will use. 1 or 2 */
    { "MldVersion", ipnet_int, netif_offsetof(inet6.mld_max_version), INET6_MLD_MAX_VERSION },

    /* Enable/disable automatic address configuration */
    { "AutoConf", ipnet_bool, netif_offsetof(inet6.auto_conf), INET6_AUTO_CONFIG },

    /*
     * Enable to allow processing of IPv6 Routing Header type 0, its
     * disabled by default since it is a potential security problem
     */
    { "RtHdr0", ipnet_bool, netif_offsetof(inet6.rt_hdr0), INET6_RTHDR0 },

#ifdef IPNET_USE_RFC3041
    /* Enable/disable privacy extensions */
    { "EnablePrivacyExtensions", ipnet_bool, netif_offsetof(inet6.privacy_extensions), INET6_ENABLE_PRIVACY_EXTENSONS },

    /*
     * Maximum lifetime, in seconds, of temporary addresses
     * default: 1 week
     */
    { "TempValidLifetime", ipnet_int, netif_offsetof(inet6.tmp_valid_lifetime), INET6_TEMP_VALID_LIFETIME },

    /*
     * Maximum preferred time, in seconds, of temporary addresses
     * default: 1 day
     */
    { "TempPreferredLifetime", ipnet_int, netif_offsetof(inet6.tmp_preferred_lifetime), INET6_TEMP_PREFERRED_LIFETIME },

    /*
     * Number of seconds before the current temporary address goes
     * non-preferred, that a new address will be generated.
     * default: 5 seconds by RFC, but that is very tight so 30 seconds
     * is used instead
     */
    { "RegenAdvance", ipnet_int, netif_offsetof(inet6.tmp_regen_advance), INET6_REGEN_ADVANCE },

    /*
     * Maximum number of times the node is allowed to regenerate the
     * host ID as a consequence of duplicate address detection failure.
     */
    { "TempIdgenRetries", ipnet_int, netif_offsetof(inet6.tmp_idgen_retries), INET6_TMP_IDGEN_RETRIES },
#endif /* IPNET_USE_RFC3041 */

    /*
     * Maximum number of times the node is allowed to regenerate the
     * host ID as a consequence of duplicate address detection failure.
     */
    { "TreatMobilityOptionsAsUnknown", ipnet_bool, netif_offsetof(inet6.treat_mobopt_unknown), INET6_TREAT_MOBOPT_UNKNOWN },

    { IP_NULL, }
};
#endif /* IPCOM_USE_INET6 */


IP_STATIC IP_CONST Ipnet_conf_vars ipnet_conf_vars[] =
{
    /* ipnet.sock.<name> variables */
    { "sock",  IP_FALSE, ipnet_sock_conf_var },

    /* ipnet.route.<name> variables */
    { "route", IP_FALSE, ipnet_route_conf_var },

#ifdef IPCOM_USE_INET
    /* ipnet.inet.<name> variables */
    { "inet",  IP_FALSE, ipnet_inet_conf_var },

    /* <ifname>.inet.<name> variables */
    { "inet",  IP_TRUE,  ipnet_inet_if_conf_var },
#endif /* IPCOM_USE_INET */

#ifdef IPCOM_USE_INET6
    /* <name> variables */
    { "inet6", IP_FALSE, ipnet_inet6_conf_var },

    /* <ifname>.inet6.<name> variables */
    { "inet6", IP_TRUE,  ipnet_inet6_if_conf_var },
#endif /* IPCOM_USE_INET6 */

    { IP_NULL, }
};


/*
 *===========================================================================
 *                           ipnet_conf_update
 *===========================================================================
 * Description: Updates a configuration variable.
 * Parameters:  fst - first part of sysvar
 *              snd - second part of sysvar
 *              name - third and later part(s) of sysvar
 * Returns:
 *
 */
IP_GLOBAL void
ipnet_conf_update(const char *fst,
                  const char *snd,
                  const char *name)
{
    IP_CONST Ipnet_conf_vars *conf_vars;
    IP_CONST Ipnet_conf_var *conf_var;

    for (conf_vars = ipnet_conf_vars;
         conf_vars->snd != IP_NULL;
         conf_vars++)
    {
        if (snd == IP_NULL
            || ipcom_strcmp(conf_vars->snd, snd) == 0)
        {
            for (conf_var = conf_vars->vars;
                 conf_var->name != IP_NULL;
                 conf_var++)
            {
                if (name == IP_NULL
                    || ipcom_strcmp(conf_var->name, name) == 0)
                {
                    if (conf_vars->is_per_netif == IP_FALSE)
                        conf_var->parse_val(IP_NULL,
                                            conf_vars->snd,
                                            conf_var);
                    else if (ipcom_strcmp("ipnet", fst))
                        conf_var->parse_val(fst,
                                            conf_vars->snd,
                                            conf_var);
                    else
                    {
                        Ipnet_netif *netif;
                        Ip_u32       i;
                        Ip_u16       vr = ipnet_get_effective_vr(ipnet_ptr());

                        IPNET_NETIF_FOR_EACH_ON_VR(netif,
                                                   vr,
                                                   i)
                            conf_var->parse_val(netif->ipcom.name,
                                                conf_vars->snd,
                                                conf_var);
                    }
                }
            }
        }
    }
}



/*
 *===========================================================================
 *                         SYSTEM VARIABLES
 *===========================================================================
 */
IP_STATIC IP_CONST Ipcom_sysvar ipnet_conf_sysvar[] =
{
#if defined(IPNET_USE_NAT) && !defined(IP_PORT_VXWORKS) || defined(INCLUDE_IPNET_USE_NAT)
    /* The timeout until an icmp mapping expires */
    IP_SYSVAR("ipnet.nat.timeout.icmp",         "10", IPNAT_ICMP_MAPPING_TIMEOUT),

    /* The timeout until an udp mapping expires */
    IP_SYSVAR("ipnet.nat.timeout.udp",          "60", IPNAT_UDP_MAPPING_TIMEOUT),

    /* The timeout until a tcp mapping expires */
    IP_SYSVAR("ipnet.nat.timeout.tcp",          "432000", IPNAT_TCP_MAPPING_TIMEOUT),

    /* The timeout until other mappings expires */
    IP_SYSVAR("ipnet.nat.timeout.other",        "60", IPNAT_OTHER_MAPPING_TIMEOUT),

    /* The maximum number of active NAT mappings */
    IP_SYSVAR("ipnet.nat.capacity.mappings",    "1000", IPNAT_MAX_MAPPING),

    /* Start of the automatically NATed ports interval */
    IP_SYSVAR("ipnet.nat.autoport.start",       "29000", IPNAT_AUTOPORT_START_INTERVAL),

    /* End of the automatically NATed ports interval */
    IP_SYSVAR("ipnet.nat.autoport.end",         "29999", IPNAT_AUTOPORT_END_INTERVAL),
#endif  /* IPCOM_USE_NAT */

#ifdef IPNET_USE_VLAN_STACKING
#ifdef INCLUDE_IPNET_USE_VLAN_STACKING
    /* The service VLAN tag protocol ID */
    IP_SYSVAR("ipnet.svlan.tpid", 		"34984", IPNET_VLAN_S_VLAN_TPID),
#endif /* INCLUDE_IPNET_USE_VLAN_STACKING */
#endif /* IPNET_USE_VLAN_STACKING */

    { IP_NULL, IP_NULL }
};


/*
 * Maximum number of stack instances that can be created
 */
#ifdef IP_PORT_VXWORKS
#if (NUM_NET_DAEMONS !=0)
#define IPNET_CONF_MAX_INSTANCES NUM_NET_DAEMONS
#else
#define IPNET_CONF_MAX_INSTANCES 1
#endif
#elif defined(IP_PORT_LXI)
#define IPNET_CONF_MAX_INSTANCES 1
#else
#define IPNET_CONF_MAX_INSTANCES 2
#endif

int ipnet_conf_max_instances = IPNET_CONF_MAX_INSTANCES;


/*
 *===========================================================================
 *                         SOCKET
 *===========================================================================
 */
IP_CONST int ipnet_conf_max_sockets = IP_FD_SETSIZE;

/*
 *===========================================================================
 *                         LINK
 *===========================================================================
 */
IP_CONST Ipnet_conf_link_layer_init ipnet_conf_link_layer[] =
{
#ifdef IPCOM_USE_ETHERNET
    { IP_IFT_ETHER,     ipnet_eth_if_init },
#ifdef IPCOM_USE_NON_ETHERNET
    { IP_IFT_OTHER,     ipnet_noeth_if_init },
#endif
#ifdef IPNET_USE_VLAN
    { IP_IFT_L2VLAN,    ipnet_vlan_if_init },
#endif
#endif /* IPCOM_USE_ETHERNET */
#if defined(IPPPP) && !defined (IP_PORT_VXWORKS) || defined(INCLUDE_IPNET_USE_PPP)
    { IP_IFT_PPP,       ipnet_ppp_if_init },
#endif
    { IP_IFT_LOOP,      ipnet_loopback_if_init },
#ifdef IPNET_USE_TUNNEL
    { IP_IFT_TUNNEL,    ipnet_tunnel_if_init },
#endif
#ifdef IPNET_USE_WLAN
    { IP_IFT_IEEE80211, ipnet_wlan_if_init },
#endif
#ifdef IPNET_USE_SOCKDEV
    { IP_IFT_SOCKDEV,    ipnet_sockdev_if_init },
#endif
#ifdef IPBRIDGE
    { IP_IFT_L2BRIDGE,    ipnet_bridge_if_init },
#ifdef INCLUDE_IPBRIDGE_VLAN_SUPPORT
    { IP_IFT_L2BRIDGE_PV, ipnet_bridge_if_init },
    { IP_IFT_L2BRIDGE_TV, ipnet_bridge_if_init },
#endif
#endif
    { 0,            IP_NULL  }
};


/*
 *===========================================================================
 *                         NETIF
 *===========================================================================
 */

/*
 * RFC 1191 chapter 3 p4
 * A host MUST never reduce its estimate of the Path MTU below 68
 * octets.
 *
 * NOTE: 576 has been the lowest MTU that any IPv4 node supports for a
 * long time. RFC 791 also states: "All hosts must be prepared
 * to accept datagrams of up to 576 octets (whether they arrive whole
 * or in fragments)."
 */
IP_CONST Ip_u16 ipnet_conf_ip4_min_mtu = INET_MIN_MTU_SIZE;
IP_CONST Ip_u16 ipnet_conf_ip6_min_mtu = INET6_MIN_MTU_SIZE;

/*
 * Maximum number of partially reassembled fragmentation chains that
 * is allowed to be present at any time. The oldest fragmentation list
 * will be dropped if this this limit is exceeded.
 */
IP_CONST unsigned ipnet_conf_max_reassembly_list_len = IPNET_MAX_REASSEMBLY_LIST_LEN;

/*
 * Maximum number of fragments each IP datagram can consist of. The
 * partly reassembled IP-datagrams will be dropped if it exceeds this
 * limit.
 */
IP_CONST unsigned ipnet_conf_max_dgram_frag_list_len = IPNET_MAX_DGRAM_FRAG_LIST_LEN;


/*
 *===========================================================================
 *           per network interface configuration from kernel configurator
 *===========================================================================
 */

/*
 * Default values
 */
#ifndef INET_IPAIP_IFLIST_PROBE_WAIT
#define INET_IPAIP_IFLIST_PROBE_WAIT          ""
#endif
#ifndef INET_IPAIP_IFLIST_PROBE_NUM
#define INET_IPAIP_IFLIST_PROBE_NUM           ""
#endif
#ifndef INET_IPAIP_IFLIST_PROBE_MIN
#define INET_IPAIP_IFLIST_PROBE_MIN           ""
#endif
#ifndef INET_IPAIP_IFLIST_PROBE_MAX
#define INET_IPAIP_IFLIST_PROBE_MAX           ""
#endif
#ifndef INET_IPAIP_IFLIST_ANNOUNCE_WAIT
#define INET_IPAIP_IFLIST_ANNOUNCE_WAIT       ""
#endif
#ifndef INET_IPAIP_IFLIST_ANNOUNCE_NUM
#define INET_IPAIP_IFLIST_ANNOUNCE_NUM        ""
#endif
#ifndef INET_IPAIP_IFLIST_ANNOUNCE_INTERVAL
#define INET_IPAIP_IFLIST_ANNOUNCE_INTERVAL   ""
#endif
#ifndef INET_IPAIP_IFLIST_MAX_CONFLICTS
#define INET_IPAIP_IFLIST_MAX_CONFLICTS       ""
#endif
#ifndef INET_IPAIP_IFLIST_RATE_LIMIT_INTERVAL
#define INET_IPAIP_IFLIST_RATE_LIMIT_INTERVAL ""
#endif
#ifndef INET_IPAIP_IFLIST_DEFEND_INTERVAL
#define INET_IPAIP_IFLIST_DEFEND_INTERVAL     ""
#endif
#ifndef INET_IFLIST_ENABLE_PROXY_ARP
#define INET_IFLIST_ENABLE_PROXY_ARP          ""
#endif
#ifndef INET_IFLIST_AUTO_PROXY_ARP
#define INET_IFLIST_AUTO_PROXY_ARP            ""
#endif
#ifndef INET6_IFLIST_ENABLE_PRIVACY_EXTENSONS
#define INET6_IFLIST_ENABLE_PRIVACY_EXTENSONS ""
#endif
#ifndef INET6_IFLIST_TEMP_VALID_LIFETIME
#define INET6_IFLIST_TEMP_VALID_LIFETIME      ""
#endif
#ifndef INET6_IFLIST_TEMP_PREFERRED_LIFETIME
#define INET6_IFLIST_TEMP_PREFERRED_LIFETIME  ""
#endif
#ifndef INET6_IFLIST_REGEN_ADVANCE
#define INET6_IFLIST_REGEN_ADVANCE            ""
#endif

/*
 * Per interface system variable sysvar suffix and the per interface
 * value(s) for this sysvar.
 */
struct Ipnet_conf_iflist {
    const char *sysvar_name;
    const char *ifvals;
};


/*
 *===========================================================================
 *                     ipnet_config_set_iflist_sysvar
 *===========================================================================
 * Description: Handles a single sysvar.
 * Parameters:  name - <ifname>.<name> forms the full sysvar name
 *              val_list - zero or more interface specific values
 * Returns:
 *
 */
IP_STATIC void
ipnet_config_set_iflist_sysvar(const char *name, const char *val_list)
{
    char sysvar[60];
    char *ifvals;
    char *ifvals_ptr;
    char *ifname;
    char *ifval;
    char *saveptr;

    ifvals = ifvals_ptr = ipcom_strdup(val_list);
    for (;;)
    {
        ifname = ipcom_strtok_r(ifvals, "=", &saveptr);
        ifval = ipcom_strtok_r(IP_NULL, " ;", &saveptr);
        if (ifname == IP_NULL || ifval == IP_NULL)
            break;
        ifvals = IP_NULL;
        ipcom_snprintf(sysvar, sizeof(sysvar), "%s.%s", ifname, name);
        (void)ipcom_sysvar_set(sysvar, ifval, 0);
    }
    ipcom_free(ifvals_ptr);
}


/*
 *===========================================================================
 *                    ipnet_config_set_iflist_sysvars
 *===========================================================================
 * Description: Translates VxWorks interface specific kernel parameters
 *              to their corresponding sysvars.
 * Parameters:
 * Returns:
 *
 */
IP_STATIC void
ipnet_config_set_iflist_sysvars()
{
    static struct Ipnet_conf_iflist iflist[] = {
        { "inet.linklocal.PROBE_WAIT",          INET_IPAIP_IFLIST_PROBE_WAIT          },
        { "inet.linklocal.PROBE_NUM",           INET_IPAIP_IFLIST_PROBE_NUM           },
        { "inet.linklocal.PROBE_MIN",           INET_IPAIP_IFLIST_PROBE_MIN           },
        { "inet.linklocal.PROBE_MAX",           INET_IPAIP_IFLIST_PROBE_MAX           },
        { "inet.linklocal.ANNOUNCE_WAIT",       INET_IPAIP_IFLIST_ANNOUNCE_WAIT       },
        { "inet.linklocal.ANNOUNCE_NUM",        INET_IPAIP_IFLIST_ANNOUNCE_NUM        },
        { "inet.linklocal.ANNOUNCE_INTERVAL",   INET_IPAIP_IFLIST_ANNOUNCE_INTERVAL   },
        { "inet.linklocal.MAX_CONFLICTS",       INET_IPAIP_IFLIST_MAX_CONFLICTS       },
        { "inet.linklocal.RATE_LIMIT_INTERVAL", INET_IPAIP_IFLIST_RATE_LIMIT_INTERVAL },
        { "inet.linklocal.DEFEND_INTERVAL",     INET_IPAIP_IFLIST_DEFEND_INTERVAL     },
        { "inet.EnableNetworkProxyArp",         INET_IFLIST_ENABLE_PROXY_ARP          },
        { "inet.AutoProxyArp",                  INET_IFLIST_AUTO_PROXY_ARP            },
        { "inet6.EnablePrivacyExtensions",      INET6_IFLIST_ENABLE_PRIVACY_EXTENSONS },
        { "inet6.TempValidLifetime",            INET6_IFLIST_TEMP_VALID_LIFETIME      },
        { "inet6.TempPreferredLifetime",        INET6_IFLIST_TEMP_PREFERRED_LIFETIME  },
        { "inet6.RegenAdvance",                 INET6_IFLIST_REGEN_ADVANCE            },
        { IP_NULL,                              IP_NULL                               },
    };
    int i;

    for (i = 0; iflist[i].ifvals; i++)
        ipnet_config_set_iflist_sysvar(iflist[i].sysvar_name, iflist[i].ifvals);
}


/*
 ****************************************************************************
 * 7                    PUBLIC FUNCTIONS
 ****************************************************************************
 */

#ifdef IP_PORT_VXWORKS
/*
*===========================================================================
*                    ipnet_get_conf_max_instances
*===========================================================================
* Description: Get configured max instances in VIP
* Parameters:
* Returns:
*
*/
IP_GLOBAL int
ipnet_get_conf_max_instances(void)
{
    if (NUM_NET_DAEMONS == 0)
    {
#ifdef _WRS_CONFIG_SMP
        return ipcom_num_configured_cpus();
#else
        return 1;
#endif
    }
    return ipnet_conf_max_instances;
}
#endif

/*
 *===========================================================================
 *                    ipnet_register_shell_commands
 *===========================================================================
 * Description: Registers all IPNET shell commands
 * Parameters:
 * Returns:
 *
 */
IP_STATIC Ip_err
ipnet_register_shell_commands(void)
{
    Ip_err err;

#ifndef IP_PORT_OSE5
#if defined(INCLUDE_IPIFCONFIG_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("ifconfig", "ifconfig [ options ] <modifier...>",
                              "IPNET interface configuration", ipnet_cmd_ifconfig,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
    if (err < 0) return err;
#endif

#if defined(INCLUDE_IPSYSCTL_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("sysctl", "sysctl [ options ] <variable...>",
                              "IPNET sysctl configuration", ipnet_cmd_sysctl,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
    if (err < 0) return err;
#endif

#if defined(INCLUDE_IPQUEUE_CONFIG_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("qc", "qc [ options ]",
                              "IPNET output queue configuration", ipnet_cmd_qc,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
    if (err < 0) return err;
#endif

#if defined(INCLUDE_IPQOS_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("qos", "qos [ options ]",
                              "IPNET Quality of Service configuration", ipnet_cmd_qos,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
    if (err < 0) return err;
#endif

#if defined(INCLUDE_IPROUTE_CMD) || !defined(IP_PORT_VXWORKS)
#ifdef IPNET_USE_ROUTESOCK
    err = ipcom_shell_add_cmd("route", "route [ options ] <modifier...>",
                              "IPNET route table control", ipnet_cmd_route,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
    if (err < 0) return err;
#endif /* IPNET_USE_ROUTESOCK */
#endif

#if defined(INCLUDE_IPIP_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("ip", "ip [ options ] <modifier...>",
                              "IPNET network configuration and state control", ipnet_cmd_ip,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
    if (err < 0) return err;
#endif /* IPNET_USE_NETLINKSOCK */


#if defined(INCLUDE_IPNETSTAT_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("netstat", "netstat [ options ]",
                              "IPNET socket and route stats", ipnet_cmd_netstat,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
    if (err < 0) return err;
#endif

#ifdef IPNET_DEBUG
#if defined(INCLUDE_IPNET_CTRL_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("ipnet_ctrl", "ipnet_ctrl [ options ]",
                              "IPNET runtime debugger util", ipnet_cmd_ctrl,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_LARGE);
    if (err < 0) return err;
#endif
#endif /* IPNET_DEBUG */

#ifdef IPCOM_USE_INET
#if defined(INCLUDE_IPARP_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("arp", "arp [ options ] <modifier...>",
                              "IPNET arp control", ipnet_cmd_arp,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
    if (err < 0) return err;
#endif

#ifdef IPCOM_USE_TIME
#if defined(INCLUDE_IPPING_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("ping", "ping [ options ] <modifier...>",
                              "IPNET ping utility", ipnet_cmd_ping,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
    if (err < 0) return err;
#endif
#endif /* IPCOM_USE_TIME */
#endif /* IPCOM_USE_INET */

#ifdef IPCOM_USE_INET6
#if defined(INCLUDE_IPNDP_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("ndp", "ndp [ options ] <modifier...>",
                              "IPNET ndp control", ipnet_cmd_ndp,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
    if (err < 0) return err;
#endif
#ifdef IPCOM_USE_TIME
#if defined(INCLUDE_IPPING6_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("ping6", "ping6 [ options ] <modifier...>",
                              "IPNET ping6 utility", ipnet_cmd_ping6,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
    if (err < 0) return err;
#endif
#endif /* IPCOM_USE_TIME */
#endif /* IPCOM_USE_INET6 */


#ifdef IPNET_USE_NAT
#if defined(INCLUDE_IPNAT_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("nat", "nat [ options ] <modifier...>",
                              "NAT control", ipnet_cmd_nat,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_SMALL);
    if (err < 0) return err;
#endif
#endif /* #ifdef IPNET_USE_NAT */

#ifdef IPNET_INCLUDE_CMD_SCALETEST
#if defined(INCLUDE_IPNET_SCALETEST_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("scaletest", "scaletest [ options ] <modifier...>",
                              "Algorithm scaling test utility", ipnet_cmd_scaletest,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_SMALL);
    if (err < 0) return err;
#endif
#endif

#ifdef IPNET_USE_PCAP
#if defined(INCLUDE_IPNET_PCAP_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("pcap", "pcap [ options ] start|stop",
                              "Packet capture utility", ipnet_cmd_pcap,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_SMALL);
    if (err < 0) return err;
#endif
#endif

#ifdef IPNET_USE_VLAN_STACKING
#if defined(INCLUDE_IPVCONFIG_CMD) || !defined(IP_PORT_VXWORKS)
    err = ipcom_shell_add_cmd("vconfig", "vconfig [ options ] <modifier...>",
                              "VLAN stacking configuration",
                              ipnet_cmd_vconfig,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_SMALL);
    if (err < 0) return err;
#endif
#endif  /* IPNET_USE_VLAN_STACKING */

#ifdef INCLUDE_IPSVCONFIG_CMD
    err = ipcom_shell_add_cmd("svconfig", "svconfig [ options ] <modifier...>",
                              "VLAN stacking configuration command for Management OS",
                              ipnet_cmd_svconfig,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_SMALL);
    if (err < 0) return err;
#endif

#ifdef INCLUDE_IPTCPAO_CMD
    err = iptcp_ao_cmd_install();
    if (err < 0) return err;
#endif
#endif /* IP_PORT_OSE5 */

    err = IPCOM_SUCCESS;
    return err;
}


/*
 *===========================================================================
 *                    ipnet_configure
 *===========================================================================
 * Description: Configure IPNET
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipnet_configure(void)
{
    Ip_err  retval;

    /* Set IPNET system variables. */
    (void)ipcom_sysvar_setv(ipnet_conf_sysvar, 0);
#ifdef REMOVE_THIS_IFDEF_WHEN_SUPPORTING_IPBRIDGE
#ifdef INCLUDE_BRIDGE
    retval = ipbridge_configure0();
    if (retval != 0) {
    	return IPCOM_ERR_FAILED;
    }
#endif
#endif

    /* Translate interface specific kernel parameters into snarfs */
    ipnet_config_set_iflist_sysvars();

    /* Add IPNET shell commands: */
    retval = ipnet_register_shell_commands();

    return retval;
}


#ifdef INCLUDE_IPNET_IFQUEUE_FIFO_DEFAULT
/*
 *===========================================================================
 *                    ipnet_qc_min
 *===========================================================================
 * Description: minimal interface queue configuration (root fifo queues only)
 * Parameters:
 * Returns:
 *
 */
#ifdef INCLUDE_IPQUEUE_CONFIG_CMD
IP_PUBLIC int
ipnet_qc_min(const char * ifname, int qlimit)
{
    char * argv [10];
    char numbuf [24];
    int argc;

    if (ifname == IP_NULL || qlimit < 0)
	return -1;

    argv[0] = "qc";
    argv[1] = "queue";
    argv[3] = "dev";
    argv[4] = (char *)ifname; /* ipnet_cmd_qc won't modify the characters */
    argv[5] = "root";

    if (qlimit == 0)
    {
        argv[2] = "del";
	argv[6] = IP_NULL;
	argc = 6;
    }
    else
    {
        argv[2] = "add";
	argv[6] = "fifo";
	argv[7] = "limit";
	ipcom_sprintf (numbuf, "%d", qlimit);
	argv[8] = numbuf;
	argv[9] = IP_NULL;
	argc = 9;
    }
    return ipnet_cmd_qc (argc, argv);
}

#else

IP_PUBLIC int
ipnet_qc_min(const char * ifname, int qlimit)
{
    int fd;
    struct Ipnet_ifqueue ifq;
    int ret;

    if (ifname == IP_NULL || qlimit < 0)
	return -1;

    ipcom_memset (&ifq, 0, sizeof (ifq));

    if (ipcom_strlcpy (ifq.ifq_name, ifname, sizeof (ifq.ifq_name)) >=
	sizeof (ifq.ifq_name))
	return -1;

#ifdef IPCOM_USE_INET
    fd = ipcom_socket(IP_AF_INET, IP_SOCK_DGRAM, 0);
#else
    fd = ipcom_socket(IP_AF_INET6, IP_SOCK_DGRAM, 0);
#endif
    if (fd == IP_SOCKERR)
	return -1;

    ipcom_strcpy (ifq.ifq_type, qlimit == 0 ? "none" : "fifo");

    ifq.ifq_id = IP_IFQ_ID_NONE;
    ifq.ifq_parent_id = IP_IFQ_ID_NONE;
    ifq.ifq_data.fifo.fifo_limit = qlimit;

    ret = ipcom_socketioctl(fd, IPNET_SIOCSIFQUEUE, &ifq);

    ipcom_socketclose (fd);
    return ret;
}

#endif

IP_PUBLIC int
ipnet_qc_unif_fifo_config(const char * ifname)
{
    int i;
    static char * excludes[] = IFQUEUE_FIFO_EXCLUDE_IFACES;

    /* Don't add a queue for the excluded interfaces (usually lo0) */
    for (i = 0; i < NELEMENTS (excludes); ++i)
	if (ipcom_strcmp (ifname, excludes[i]) == 0)
	    return 0;
    /*
     * We could potentially more add logic here to set different queue
     * configurations based upon the interface name. For now,
     * we support only setting the same root fifo configuration by default
     * for all non-excluded interfaces.
     */
    return ipnet_qc_min(ifname, IFQUEUE_FIFO_QLIMIT);
}
#endif /* INCLUDE_IPNET_IFQUEUE_FIFO_DEFAULT */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
