/*
 * Copyright (c) 2014,2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
25apr16,rbo  Disable IPCOM_USE_AUTH_RADIUS
22dec15,rbo  Build fix for a VSB config where IPNET_COREIP and OPENSSL is enabled, but SEC_CRYPTO is disabled
23sep14,ljl  Move key db to security layer, US44321
22jun14,jsh  Correct key db dependency for vxworks-7 - V7NET-350
06mar14,jsh  Correct MD5 dependency for vxworks-7
*/

#ifndef IPCOM_CONFIG_H
#define IPCOM_CONFIG_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Generic IPCOM Configuration. Also see config/ipcom_config.c.
 *
 * Also see port/<rtos>/config/ipcom_pconfig.h for RTOS port specific config.
 */

/*
 ****************************************************************************
 * 2                    PORT CONFIGURATION
 ****************************************************************************
 * Port configuration reside in ipcom_pconfig.h.
 * Note:
 * Do not EDIT the macros in this section, they only reside here because
 * they must be defined before including ipcom_pconfig.h
 */

/* Valid IPCOM_USE_FILE, IPCOM_USE_SOCK, IPCOM_USE_SHELL #if values: */
#define IPCOM_FILE_NONE    1
#define IPCOM_FILE_IPCOM   2
#define IPCOM_FILE_NATIVE  3

#define IPCOM_SOCK_IPLITE   1
#define IPCOM_SOCK_IPNET    2
#define IPCOM_SOCK_IPCOM    3 /* IPNET or IPLITE */
#define IPCOM_SOCK_NATIVE   4
#define IPCOM_SOCK_NONE     5

#define IPCOM_SHELL_NONE    1
#define IPCOM_SHELL_MINI    2
#define IPCOM_SHELL_IPCOM   3
#define IPCOM_SHELL_NATIVE  4

#define IPCOM_NETIF_IPCOM   1
#define IPCOM_NETIF_NATIVE  2

#define IPCOM_ENV_NONE      1
#define IPCOM_ENV_IPCOM     2
#define IPCOM_ENV_NATIVE    3

/* Port specific configuration. */
#include "ipcom_pconfig.h"
#include "ipcom_clibmap.h"

#ifndef IPCOM_NO_SA_LEN
#define IPCOM_USE_SA_LEN    1
#endif

#ifndef IPCOM_USE_FILE
#define IPCOM_USE_FILE IPCOM_FILE_NATIVE
#endif
#if defined(IP_SIZE) && !defined(IPCRYPTO) && !defined(IPTFTPC) && !defined(IPTFTPS) && !defined(IPFTPC) && !defined(IPFTPS)
#undef IPCOM_USE_FILE
#define IPCOM_USE_FILE IPCOM_FILE_NONE
#endif

#ifndef IPCOM_USE_SOCK
#if defined(IPNET) && defined(IPLITE)
#error cant_define_IPNET_and_IPLITE___choose_one
#elif defined(IPNET)
#define IPCOM_USE_SOCK IPCOM_SOCK_IPNET
#elif defined(IPLITE)
#define IPCOM_USE_SOCK IPCOM_SOCK_IPLITE
#elif defined(IP_PORT_OSE5)
#define IPCOM_USE_SOCK IPCOM_SOCK_IPCOM
#else
#define IPCOM_USE_SOCK IPCOM_SOCK_NATIVE
#endif
#endif

#ifdef IP_PORT_LKM
#define IPCOM_USE_SHELL IPCOM_SHELL_NONE
#else
#ifndef IPCOM_USE_SHELL
#define IPCOM_USE_SHELL IPCOM_SHELL_IPCOM
#endif
#endif


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif


/*
 ****************************************************************************
 * 4                    FEATURES
 ****************************************************************************
 */

/* #define IP_ASSERT */

/*
 *===========================================================================
 *                         IP_LW_DEBUG
 *===========================================================================
 * Define to include Light Weight debug features
#define IP_LW_DEBUG
 */

#ifdef IP_LW_DEBUG
#define IPCOM_FWD_PKT_POOL_DEBUG
#endif

/*
 *===========================================================================
 *                         IPCOM_NAE_HW_TX_CHKSUM
 *===========================================================================
 * Define when hardware has the ability to calculate TCP chksum on transmit
#define IPCOM_NAE_HW_TX_CHKSUM
 */



#if defined(IPCOM_NAE_HW_TX_CHKSUM) && !defined(IPCOM_FORWARDER_NAE)
#define IPCOM_FORWARDER_NAE
#endif

/*
 *===========================================================================
 *                         IPCOM_MAX_NAE
 *===========================================================================
 * Maximum number of NAE:s that is supported.
 */
#ifndef IPCOM_MAX_NAE
#define IPCOM_MAX_NAE 8
#endif

/*
 *===========================================================================
 *                         IPCOM_NAE_UTIL
 *===========================================================================
 * Define to include nae utility functions:
 *  nae_ping
 *  nae_util
 *  nae_topple
 *  nae_enable
 *  nae_disable
 */
#ifndef IP_PORT_UNIX
#define IPCOM_NAE_UTIL
#endif

/*
 *===========================================================================
 *                         IPCOM_NAE_RAMLOG
 *===========================================================================
 * Define to enable "per NAE" ramlog. Use 'nae_ramlog <nae id>' to display log
#define IPCOM_NAE_RAMLOG
 */

/*
 *===========================================================================
 *                         MIPC_POW_DEBUG
 *===========================================================================
 * Define to enable MIPC over Cavium POW debug printouts
#define MIPC_POW_DEBUG
 */

/*
 *===========================================================================
 *                         IPCOM_MIPS_CALLSTACK
 *===========================================================================
 * Define to enable callstack evaluator for MIPS targets
#define IPCOM_MIPS_CALLSTACK
 */


/* Automatically define IPCOM_NAE_DEBUG if sub-defines are set */
#if defined(IPCOM_NAE_RAMLOG) || defined(IPCOM_MIPS_CALLSTACK)
#ifndef IPCOM_NAE_DEBUG
#define IPCOM_NAE_DEBUG
#endif
#endif

/*
 *===========================================================================
 *                         IPCOM_USE_FORWARDER
 *===========================================================================
 * Define to include Multi-core polling forwarders.
#define IPCOM_USE_FORWARDER
 */

/* Enable automatically if a forwarder type's been defined */
#if defined(IPCOM_FORWARDER_NAE) || defined(IPCOM_FORWARDER_AMP) || defined(IPCOM_FORWARDER_SMP)
#define IPCOM_USE_FORWARDER
#define IPCOM_USE_FORWARDER_CACHE_WAYS
#endif

/*
 *===========================================================================
 *                         IPCOM_USE_FORWARDER_VLAN
 *===========================================================================
 * Define to include VLAN (Virtual LAN) support for Multi-core polling forwarders
#define IPCOM_USE_FORWARDER_VLAN
 */

/*
 *===========================================================================
 *                         IPCOM_USE_FORWARDER_VLAN_STACKING
 *===========================================================================
 * Define to include VLAN stacking support for Multi-core polling forwarders
#define IPCOM_USE_FORWARDER_VLAN_STACKING
 */
#ifdef _WRS_CONFIG_COMPONENT_VLAN_STACKING_FORWARDER
#define IPCOM_USE_FORWARDER_VLAN_STACKING
#endif


/*
 *===========================================================================
 *                         SVLAN_SC_FWD_TABLE
 *===========================================================================
 * Define to enable establishing fast forward table on a SC VLAN port
#define SVLAN_SC_FWD_TABLE
 */
#ifdef IPCOM_USE_FORWARDER_VLAN_STACKING
#define SVLAN_SC_FWD_TABLE
#endif


/*
 *===========================================================================
 *                         IPCOM_USE_FORWARDER_CACHE_WAYS
 *===========================================================================
 * Define to use ways in the forwarding cache.
 *
 * Cache ways are used to handle collisions, i.e. when two or more flows use
 * the same cache entry. When more than one cache way is configured there are
 * alternative entries for colliding flows. Three definitions control how
 * cache ways are used. Only one of these should typically be defined.
 *
 * IPCOM_USE_FORWARDER_CACHE_WAYS
 * When defined 6 consecutive cache entries are avalaible to colliding flows
 * This works for most application. The other defines are available for
 * experimental use only.
 *
 * IPCOM_FORWARDER_CACHE_WAYS
 * Define when more or less entries should be available to colliding flows.
 *
 * IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT
 * A variant of cache ways is called "true cache ways". This reserves a number
 * of cache entries for a set of flows. This is just a variant the would potentially
 * allow a larger forwarding cache.

Define one of the three below to use cache ways
#define IPCOM_USE_FORWARDER_CACHE_WAYS
#define IPCOM_FORWARDER_CACHE_WAYS (4)
#define IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT (2)

Define this to use upper bits rather than lower bits (experimental use only)
#define IPCOM_FORWARDER_USE_UPPER_TAG_BITS
 */

/* #define IPCOM_USE_FORWARDER_CACHE_WAYS */
/* #define IPCOM_FORWARDER_CACHE_WAYS (3) */
/* #define IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT (2) */

#if defined(IPCOM_FORWARDER_CACHE_WAYS) && defined(IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT)
#if IPCOM_FORWARDER_CACHE_WAYS != (1<<IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT)
#error "IPCOM_FORWARDER_CACHE_WAYS != (1<<IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT)"
#endif
#endif

#if defined(IPCOM_USE_FORWARDER_CACHE_WAYS) && !defined(IPCOM_FORWARDER_CACHE_WAYS)
#define IPCOM_FORWARDER_CACHE_WAYS (6)
#endif

#if defined(IPCOM_FORWARDER_CACHE_WAYS) && !defined(IPCOM_USE_FORWARDER_CACHE_WAYS)
#define IPCOM_USE_FORWARDER_CACHE_WAYS
#endif

#ifndef IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT
#define IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT (0)
#endif

#if IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT > 0
#ifndef IPCOM_USE_FORWARDER_CACHE_WAYS
#define IPCOM_USE_FORWARDER_CACHE_WAYS
#undef IPCOM_FORWARDER_CACHE_WAYS
#define IPCOM_FORWARDER_CACHE_WAYS (1 << IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT)
#endif
#endif

#define IPCOM_FORWARDER_TRUE_CACHE_WAYS (1 << IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT)

/* The multi-core polling forwarders are supported only in MSP installations */
#if !defined (IPNET_MSP_DISTRIBUTION)
#undef IPCOM_USE_FORWARDER
#undef IPCOM_USE_FORWARDER_VLAN
#undef IPCOM_USE_FORWARDER_IPSEC
#undef IPCOM_USE_FORWARDER_CACHE_WAYS
#undef IPCOM_USE_FORWARDER_VLAN_STACKING
#endif

#ifndef IPCOM_USE_FORWARDER
#if defined(IPCOM_USE_FORWARDER_VLAN) || \
    defined(IPCOM_USE_FORWARDER_IPSEC) || \
    defined(IPCOM_USE_FORWARDER_CACHE_WAYS) || \
    defined(IPCOM_USE_FORWARDER_VLAN_STACKING)
#define IPCOM_USE_FORWARDER
#endif
#endif

#ifdef IPCOM_USE_FORWARDER

#if defined(IP_PORT_VXWORKS)
#if defined (__i386) || defined (__386)
#define IPCOM_USE_NEHALEM_FORWARDER
#define IPCOM_USE_NEHALEM_HYPERTHREAD

/* Use a common transmit routine for both forwarder and NAE */
#define ipcom_forwarder_tx_fw ipcom_forwarder_tx

 /* The selective invalidation mechanism doesn't support VLAN forwarding */
#ifndef IPCOM_USE_FORWARDER_VLAN
#define IPCOM_FORWARDER_SELECTIVE_INVAL
#endif

#elif defined(_WRS_MIPS_N32_ABI)
#define IPCOM_USE_OCTEON_FORWARDER

#else
/* else, assume p4080 */
#define IPCOM_USE_P4080_FORWARDER
#define IPCOM_PORTABLE_IPC_SPINLOCK
#endif /* defined (__i386) || defined (__386) */

#endif /* defined(IPCOM_PORT_VXWORKS) */

/*
 * For now, we assume an AMP forwarder in uniprocessor builds,
 * and a non-AMP forwarder in SMP builds.
 */
#if !defined(IPCOM_FORWARDER_SMP) && !defined(IPCOM_FORWARDER_AMP) && !defined(IPCOM_FORWARDER_NAE)
#ifdef IPCOM_USE_SMP
#define IPCOM_FORWARDER_SMP
#else /* IPCOM_USE_SMP */
#define IPCOM_FORWARDER_AMP
#endif /* IPCOM_USE_SMP */
#endif /* !defined(IPCOM_FORWARDER_SMP) && !defined(IPCOM_FORWARDER_AMP) && !defined(IPCOM_FORWARDER_NAE) */

#if defined(IPCOM_USE_NEHALEM_FORWARDER) || defined(IPCOM_USE_P4080_FORWARDER)
#define IPCOM_FORWARDER_AMP
#endif


#define IPCOM_USE_HW_CHECKSUM_TX_DISABLED

#ifndef IPCOM_USE_FORWARDER_CACHE_WAYS
#define IPCOM_USE_FORWARDER_CACHE_WAYS
#define IPCOM_FORWARDER_CACHE_WAYS (6)
#define IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT (0)
#define IPCOM_FORWARDER_TRUE_CACHE_WAYS (1 << IPCOM_FORWARDER_TRUE_CACHE_WAYS_SHIFT)
#endif /* IPCOM_USE_FORWARDER_CACHE_WAYS */

#endif /* IPCOM_USE_FORWARDER */

#ifdef IPCOM_USE_FORWARDER
/* #define IPCOM_USE_STANDARD_MIPC */
#endif /* IPCOM_USE_FORWARDER */


/*
 *===========================================================================
 *                         IPCOM_NAE_MULTICAST_MULTISEG
 *===========================================================================
 * Define to include multi-segment multi-port packet transmission on
 * Intel Nehalem/Westmere forwarder
#define IPCOM_NAE_MULTICAST_MULTISEG
 */
#if defined(IPCOM_USE_FORWARDER_VLAN_STACKING) && defined(IPCOM_USE_NEHALEM_FORWARDER)
#define IPCOM_NAE_MULTICAST_MULTISEG
#endif


/*
 *===========================================================================
 *                         IPCOM_USE_FLOAT
 *===========================================================================
 * Define if want to support floating point and math operations.
 */
#if defined(IPSSL) || \
    defined(IPCRYPTO) || \
    defined(IPSSLPROXY) || \
    defined(IPIKE) || \
    defined(IPNTP) || \
    defined(IPNGC) || \
    defined(IPNETSNMP) || \
    defined(IPNETPERF) || \
    defined(ZEBOS)
#define IPCOM_USE_FLOAT
#endif


/*
 *===========================================================================
 *                         IPCOM_USE_TIME
 *===========================================================================
 * Define if your RTOS port has implemented port/<rtos>/src/ipcom_time.c.
 */
#define IPCOM_USE_TIME


/*
 *===========================================================================
 *                         IPCOM_USE_INET
 *===========================================================================
 * Define if your stack supports IPv4 and you want IPCOM IPv4 support.
 */
#ifndef IPCOM_EXCLUDE_INET
#define IPCOM_USE_INET
#endif


/*
 *===========================================================================
 *                         IPCOM_USE_INET6
 *===========================================================================
 * Define if your stack supports IPv6 and you want IPCOM IPv6 support.
 * Note: IPNET and IPLITE set this define in the makefile if IPv6 is
 *       included in the release (e.g. see ipnet2/make/ipnet6.mk)
 *
 */
#if defined(IP_PORT_UNIX) && IPCOM_USE_SOCK == IPCOM_SOCK_NATIVE \
  && defined(IP_PORT_LINUX)
#define IPCOM_USE_INET6
#endif

/*
 *===========================================================================
 *                         IPCOM_USE_SYSVAR
 *===========================================================================
 * Define for system variables.
 */
#define IPCOM_USE_SYSVAR

/*
 *===========================================================================
 *                         IPCOM_USE_MD5
 *===========================================================================
 * Define for MD5 support to IPRIP, IPTCP, IPPPP and IPNET.
 */
#ifndef IP_PORT_LKM
# if defined(_WRS_CONFIG_SEC_HASH) || defined(IP_PORT_OSE5)
#  define IPCOM_USE_MD5
# endif
#endif /* #ifndef IP_PORT_LKM */

/*
 *===========================================================================
 *                         IPCOM_USE_MIB2
 *===========================================================================
 * Define for mib-2 support
#define IPCOM_USE_MIB2
 */
#if defined(VXCOMPAT) || (defined(IPSNMP) || defined(IPEMANATE) || defined(WRSNMP)) && (defined(IPNET) || defined(IPLITE))
#define IPCOM_USE_MIB2
#endif



/*===========================================================================
 *                         IPCOM_USE_MIB2_NEW
 *===========================================================================
 * Define to include support for the new IP version independent MIBs:
 * RFC4022, RFC4113, RFC4292 and RFC4293
#define IPCOM_USE_MIB2_NEW
 */
#if (defined(VXCOMPAT) || defined(WRSNMP)) && defined(IPNET)
#define IPCOM_USE_MIB2_NEW
#endif

/* IPCOM_USE_MIB2_NEW requires IPCOM_USE_MIB2 */
#if defined(IPCOM_USE_MIB2_NEW) && !defined(IPCOM_USE_MIB2)
#undef IPCOM_USE_MIB2_NEW
#endif


/*
 *===========================================================================
 *                         IPCOM_USE_MIB2_CMD
 *===========================================================================
 * Define to include MIB-2 test command
 */
#ifdef IPCOM_USE_MIB2_NEW
#define IPCOM_USE_MIB2_CMD
#endif

/* IPCOM_USE_MIB2_CMD requires IPCOM_USE_MIB2_NEW */
#if defined(IPCOM_USE_MIB2_CMD) && !defined(IPCOM_USE_MIB2_NEW)
#undef IPCOM_USE_MIB2_CMD
#endif

/*
 *===========================================================================
 *                         IPCOM_USE_SMPTEST_CMD
 *===========================================================================
 * Define to include SMP test command
#define IPCOM_USE_SMPTEST_CMD
 */


/*
 *===========================================================================
 *                         IPCOM_VR_MAX
 *===========================================================================
 * Maximum number of virtualized entries, e.g. sysvars, routes etc.
 * Not relevant on the LKM port.
 */
#if defined(_WRS_CONFIG_COMPONENT_VIRTUAL_ROUTER) || !defined(IP_PORT_VXWORKS)
#define IPCOM_VR_MAX  8
#else
#define IPCOM_VR_MAX  1
#endif


/*
 *===========================================================================
 *                         IPCOM_USE_ENV
 *===========================================================================
 * Define for process specific environment variables. If set to IPCOM_ENV_NONE,
 * environment variables are implemented using sysvars, i.e. global.
 */
#if !defined(IPCOM_USE_ENV)
#if defined(IP_PORT_VXWORKS) || defined(IP_PORT_OSE) || defined(IP_PORT_OSE5)
#define IPCOM_USE_ENV  IPCOM_ENV_NATIVE
#else
#define IPCOM_USE_ENV  IPCOM_ENV_IPCOM
#endif
#endif

/*
 *===========================================================================
 *                         IPCOM_USE_KEY_DB
 *===========================================================================
 * Define to enable a key database that provides basic protection for public
 * keys and pre-shared keys.
 */
#if defined(_WRS_CONFIG_OPENSSL) && defined(_WRS_CONFIG_SEC_CRYPTO)
# define IPCOM_USE_KEY_DB
# define IPCOM_USE_KEY_DB_CMD
# define IPCOM_USE_KEY_DB_CMD_VERIFY
#endif

/*
 ****************************************************************************
 * 5                    SERVICES
 ****************************************************************************
 */


/*
 *===========================================================================
 *                         IPCOM_SYSLOG_PRIO_DEFAULT
 *===========================================================================
 * Initial syslog system build-time priority. Changing these levels change
 * the compiled in log level for all products.
 */
#if defined(_WRS_CONFIG_IPCOM_DEFAULT_SYSLOG_PRIORITY)
# define IPCOM_SYSLOG_PRIO_DEFAULT _WRS_CONFIG_IPCOM_DEFAULT_SYSLOG_PRIORITY
#elif defined(IP_DEBUG)
# define IPCOM_SYSLOG_PRIO_DEFAULT   7 /* IPCOM_LOG_DEBUG2 */
#else
# define IPCOM_SYSLOG_PRIO_DEFAULT   3 /* IPCOM_LOG_WARNING */
#endif


/*
 *===========================================================================
 *                         IPCOM_SYSLOG_IPCOM_PRIORITY
 *===========================================================================
 * Initial IPCOM syslog build-time priority.
 */
#define IPCOM_SYSLOG_IPCOM_PRIORITY IPCOM_SYSLOG_PRIO_DEFAULT


/*
 *===========================================================================
 *                         IPCOM_LOG_USE_OF_DEPRECATED_API
 *===========================================================================
 * Log use of deprecated APIs. Only first call will be logged.
 */
#ifdef IP_DEBUG
#define IPCOM_LOG_USE_OF_DEPRECATED_API
#endif


/*
 *===========================================================================
 *                         IPCOM SYSLOG
 *===========================================================================
 * Define to enable use of syslogs using the syslog daemon.
 */
#if !defined(IPCOM_SYSLOG) \
    && !defined(IP_PORT_OSECK) \
    && !defined(IP_PORT_LKM) \
    && !defined(IP_SIZE) \
    && !defined(IPBASIC) \
    && !defined(IPCOM_FORWARDER_NAE) \
    && !defined(IPCOM_FORWARDER_AMP) \
    && !defined(IPLITE)
#define IPCOM_USE_SYSLOG
#endif


/*
 *===========================================================================
 *                         IPCOM AUTH
 *===========================================================================
 * Enable IPCOM authentication - ipcom_auth.h
 */
#if defined(IPSSH) /* So IPSSH can use the default AUTH function */ \
    || (!defined(IP_PORT_OSECK) \
     && !defined(IP_PORT_LKM) \
     && !defined(IPBASIC) \
     && !defined(IPCOM_FORWARDER_NAE) \
     && !defined(IPCOM_FORWARDER_AMP))
#define IPCOM_USE_AUTH
#endif

/* Use RADIUS client to lookup user & password. */
#if defined(IPCOM_USE_AUTH) && defined(IPRADIUS) && (defined(IPNET) || defined(IPLITE))
/* #define IPCOM_USE_AUTH_RADIUS */
#endif


/*
 *===========================================================================
 *                         IPCOM TELNET
 *===========================================================================
 * IPCOM telnet server. Also see ipcom_telnets_config.c for telnet port.
 */

/* Define to start the interpeak telnet server. */
#if (IPCOM_USE_SHELL == IPCOM_SHELL_IPCOM || IPCOM_USE_SHELL == IPCOM_SHELL_NATIVE) \
    && (defined(IPTCP) || IPCOM_USE_SOCK == IPCOM_SOCK_NATIVE || defined(IPLITE)) \
    && !defined(IP_PORT_OSE5) \
    && !defined(OSE_REFSYS) \
    && !defined(IP_PORT_INTEGRITY)
#define IPTELNETS
#endif


/*
 *===========================================================================
 *                         IPCOM FILE
 *===========================================================================
 * Interpeak memory file system.
 */

/* Maximum number of open files with IPCOM memory filesystem: ipcom_file.c.
 * (used if compiled with IPCOM_USE_FILE == IPCOM_FILE_IPCOM
 * Note: the actual max is three lower due to unused 0-2 slots.
 */
#define IPCOM_FILE_FD_SETSIZE   64


/*
 *===========================================================================
 *                         IPCOM_DRV
 *===========================================================================
 * Generic IPCOM PPP and Ethernet driver configuration.
 */

/* Default PPP baudrate in ipcom_drv_ppp.c used by IPNET/IPLITE. */
#define IPCOM_DRV_PPP_BAUDRATE      38400

/*
 *===========================================================================
 *                  IPCOM_GETLINE_HISTORY_FILENAME
 *===========================================================================
 * Filename where the IPCOM getline will save the history when an IPCOM
 * shell exits.
 */
#define IPCOM_GETLINE_HISTORY_FILENAME   ".ipcom_getline_history"


/*
 ****************************************************************************
 * 6                    AUTO configuration
 ****************************************************************************
 */

#include "ipcom_autoconf.h"


/*
 ****************************************************************************
 * 7                    MORE configuration
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         IPCOM_STDIO_BUFSIZE
 *===========================================================================
 * Maximum I/O bufsize, e.g. for ipcom_prinf(), ipcom_fprintf() etc.
 */
#define IPCOM_STDIO_BUFSIZE   3000


/*
 *===========================================================================
 *                         IPCOM SHELL
 *===========================================================================
 * IPCOM login shell config macro. Also see config/ipcom_config.c for additional
 * shell configuration constants.
 */

/* Maximum length of current working directory */
#define IPCOM_SHELL_MAX_PATH     256


/* Define if you want alias expansion in the IPCOM Shell */
#if IPCOM_USE_SHELL == IPCOM_SHELL_IPCOM
/* #define IPCOM_USE_ALIAS 1 */
#endif
#ifdef __cplusplus
}
#endif


/*
 *===========================================================================
 *                         IPCOM_USE_BITARRAY
 *===========================================================================
 * Define for including bitarray.
 */
#define IPCOM_USE_BITARRAY

/*
 *===========================================================================
 *                         IPCOM_USE_MUX_DRV
 *===========================================================================
 * Define for using the mux driver
 */
#define IPCOM_USE_MUX_DRV

/*
 *===========================================================================
 *                         IPCOM_USE_NON_ETHERNET
 *===========================================================================
 * Define for support non-ethernet interface
 */
#if defined(IPCOM_USE_INET) || defined(IPCOM_USE_INET6)
#define IPCOM_USE_NON_ETHERNET
#endif


#endif
/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
