/*
 * Copyright (c) 2006-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01jun17,dlk  remove no-longer-used ipcom_vxworks_rtp_del_hook_add() (F5593)
07dec16,mca  Break hard dependency between END and IPNET (US85582)
09jun16,kjn  Renamed the Safe network stack to Real-time network stack,
             INCLUDE_SAFE_NETWORK_KERNEL and
             INCLUDE_SAFE_NETWORK_RTP_AUTOSTART becomes INCLUDE_RTNET_KERNEL
             and INCLUDE_RTNET_RTP_AUTOSTART
08jun16,mca  do not create IPCOM when INCLUDE_SAFE_NETWORK_KERNEL
             or INCLUDE_SAFE_NETWORK_RTP_AUTOSTART are defined
12mar16,wfl  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
12nov15,mca  change CERT_NET to SAFE_NETWORK
27oct14,lzq  Fix compile errors. (V7NET-369)
03jun14,rjq  Fix compile errors. (V7NET-391)
*/


/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    INCLUDE FILES
 ****************************************************************************
 */

#if !defined(IP_PORT_INTEGRITY)
#ifndef IPCOM_KERNEL
#define IPCOM_KERNEL
#endif
#endif
#include "ipcom_config.h"

#ifndef IP_PORT_VXWORKS
#define IPCOM_USE_CLIB_PROTO
#endif
#include "ipcom_clib.h"
#include "ipcom_auth.h"
#include "ipcom_syslog.h"
#include "ipcom_err.h"
#include "ipcom_sock.h"
#include "ipcom_sock2.h"
#include "ipcom_shell.h"
#include "ipcom_ipd.h"
#include "ipcom_os.h"
#include "ipcom_sysvar.h"

#ifdef IPLITE
#include "iplite.h"
#endif

#ifdef IPCOM_USE_FORWARDER
#include "ipcom_forwarder.h"
#endif

#ifdef IP_PORT_VXWORKS
#include "errnoLib.h"
#ifdef _WRS_CONFIG_SHELL
#include <shellInterpCmdLib.h> /* Needed for BSP builds */
#endif /* _WRS_CONFIG_SHELL */
/* #include <private/vxCpuLibP.h> */
#include <private/rtpLibP.h>
#include <taskHookLib.h>
#ifdef	_WRS_CONFIG_WRLOAD
#include <wrload.h>
#endif

#if 0
#ifdef INCLUDE_OCTEON_VXB_FORWARDER
#if !defined(IPCOM_USE_SMP) && !defined(INCLUDE_OCTEON_VXB_MASTER_FORWARDER)
#include "cvmx-warn.c"
#endif
#endif
#endif

#if defined(IPCOM_USE_FORWARDER) && defined(_WRS_CONFIG_WRHV_GUEST)
#include <wrhv/vbi.h>
#endif

#ifdef INCLUDE_OCTEON_IPCOM_NAE_PRIORITY_QUEUE
#include "executive-config.h"
#endif

#ifdef INCLUDE_POSIX_DIRLIB
#include <dirent.h>
#endif
#endif /* IP_PORT_VXWORKS */

/*
 ****************************************************************************
 * 3                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC Ip_err ipcom_configure(void);


/*
 ****************************************************************************
 * 4                    EXTERN PROTOTYPES
 ****************************************************************************
 */
#if defined(INCLUDE_IPCOM_USE_VXSHELL_CMD) && IPCOM_USE_SHELL == IPCOM_SHELL_IPCOM
IP_GLOBAL int ipcom_cmd_vxshell(int argc, char **argv);
#endif

IP_PUBLIC int ipcom_cmd_syslog(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_sysvar(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_user(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_mem(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_ipd(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_version(int argc, char **argv);

IP_PUBLIC int ipcom_cmd_errno(int argc, char **argv);

IP_PUBLIC int ipcom_cmd_echoclient(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_echoserver(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_mib2(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_netsmp(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_smptest(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_sockperf(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_socktest(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_tracert(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_ttcp(int argc, char **argv);
IP_PUBLIC int ipcom_cmd_cpu(int argc, char **argv);
IP_PUBLIC int ipnet_cmd_route(int argc, char** argv);
IP_PUBLIC int ipnet_cmd_qc(int argc, char** argv);
IP_PUBLIC int ipnet_cmd_ifconfig(int argc, char ** arg);


#ifdef INCLUDE_IPWLAN_CMD
IP_EXTERN int ipwlan_cmd_wlan(int argc, char **argv);
#endif

#ifdef IP_PORT_VXWORKS
IP_EXTERN STATUS ipcom_mcmd_ifconfig(int argc, char ** arg);
IP_EXTERN STATUS ipcom_mcmd_route(int argc, char ** arg);
IP_PUBLIC Ip_err ipcom_create(void); /* avoid ipcom_h.h */
IP_PUBLIC void ipcom_config_create(void);
#endif

#ifdef IPROUTE2
IP_PUBLIC int iproute2_cmd(int argc, char **argv);
#endif

#ifdef INCLUDE_IPCOM_USE_RAM_DISK
#if IPCOM_USE_FILE == IPCOM_FILE_NATIVE && defined(IPCOM_USE_RAM_DISK)
IP_EXTERN void vxfs_ramdisk_init();
#endif
#endif

#ifdef INCLUDE_IPCOM_USR
IP_PUBLIC Ip_err ipcom_usr_create(void);
IP_PUBLIC void ipcom_config_usr_create(void);
#endif

#ifdef INCLUDE_IPCRYPTO_USE_KEY_DB_EXAMPLE_KEYS
void ipcrypto_key_db_install_example_keys(void);
#endif

/*
 ****************************************************************************
 * 4                    DEFINE
 ****************************************************************************
 */

/* Translates a macro from its symbolic name to a string containing its
   numerical for.
   Must evaluate x in 2 steps so that the pre-processor replaces
   the macro "x" with its numerical form
   ex: IPASCII(IPCOM_LOG_INFO) -> IPASCII2(5) -> "5"
*/
#define IPASCII(x)   IPASCII2(x)
#define IPASCII2(x) #x

#ifndef IPCOM_SYSLOG_LOGFILE
#define IPCOM_SYSLOG_LOGFILE  IP_NULL /*IPCOM_FILE_ROOT "syslog"*/
#endif

#ifdef IPCOM_SYSLOG_PRIORITY
#undef IPCOM_SYSLOG_PRIORITY
#endif
#define IPCOM_SYSLOG_PRIORITY    IPCOM_SYSLOG_IPCOM_PRIORITY

#ifdef IPCOM_SYSLOG_FACILITY
#undef IPCOM_SYSLOG_FACILITY
#endif
#define IPCOM_SYSLOG_FACILITY    IPCOM_LOG_IPCOM


#if defined(IPCOM_ENABLE_USER_SHELL) && (IPCOM_ENABLE_USER_SHELL == IP_TRUE)
#ifdef IPCOM_START_SHELL
IP_PUBLIC Ip_err
IPCOM_START_SHELL(Ip_fd *stdio_sock, const Ipcom_shell_ctx* sh_ctx);
#else
#define IPCOM_START_SHELL   IP_NULL
#endif
#else
#undef IPCOM_START_SHELL
#endif


/*
 ****************************************************************************
 * 5                    SYSTEM VARIABLES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    AUTHENTICATION
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         IPCOM AUTH - RADIUS AUTHENTICATION
 *===========================================================================
 * RADIUS client configuration for IPCOM authentication - ipcom_auth.h.
 */
#if defined(IPCOM_USE_AUTH_RADIUS) || defined(INCLUDE_IPCOM_USE_AUTH_RADIUS)

#ifndef IPCOM_AUTH_RADIUS_SERVER_DOMAIN
#define IPCOM_AUTH_RADIUS_SERVER_DOMAIN 2 /* RADIUS server domain: IP_AF_INET=2 or IP_AF_INET6=24. */
#endif
IP_GLOBAL IP_CONST int ipcom_auth_radius_server_domain =
                                    IPCOM_AUTH_RADIUS_SERVER_DOMAIN;

#ifndef IPCOM_AUTH_RADIUS_SERVER_IPV4_ADDRESS
#define IPCOM_AUTH_RADIUS_SERVER_IPV4_ADDRESS "10.1.2.1"
#endif
/* RADIUS server IPv4/IPv6 address: */
IP_GLOBAL IP_CONST char *ipcom_auth_radius_server_address =
                                    IPCOM_AUTH_RADIUS_SERVER_IPV4_ADDRESS;

#ifndef IPCOM_AUTH_RADIUS_SERVER_PORT
#define IPCOM_AUTH_RADIUS_SERVER_PORT 1812
#endif
/* RADIUS server port in host endian: */
IP_GLOBAL IP_CONST Ip_u16 ipcom_auth_radius_server_port =
                                    IPCOM_AUTH_RADIUS_SERVER_PORT;

/* RADIUS server shared secret: */
#ifndef IPCOM_AUTH_RADIUS_SERVER_SHARE_SECRET
#define IPCOM_AUTH_RADIUS_SERVER_SHARE_SECRET "kallekula123"
#endif
IP_GLOBAL IP_CONST char *ipcom_auth_radius_server_secret =
                                    IPCOM_AUTH_RADIUS_SERVER_SHARE_SECRET;

/* RADIUS server password type (1=PAP, 2=CHAP): */
#define IPRADIUS_PAP_Password       1
#define IPRADIUS_CHAP_Password      2
#ifndef IPCOM_AUTH_RADIUS_SERVER_PASSWD_TYPE
#define IPCOM_AUTH_RADIUS_SERVER_PASSWD_TYPE IPRADIUS_PAP_Password
#endif
IP_GLOBAL IP_CONST Ip_u32 ipcom_auth_radius_server_pwdtype =
                                    IPCOM_AUTH_RADIUS_SERVER_PASSWD_TYPE;

#endif /* defined(IPCOM_USE_AUTH_RADIUS) || defined(INCLUDE_IPCOM_USE_AUTH_RADIUS) */


/*
 ****************************************************************************
 * 7                   DATA
 ****************************************************************************
 */

/*
 * These 2 functions are used for data buffer in ipcom_pkt to be allcated/freed
 */
void *(*ipcom_sys_malloc)(Ip_size_t size) = IP_NULL;
void (*ipcom_sys_free)(void *ptr) = IP_NULL;

#ifdef IP_PORT_VXWORKS
/*
 *===========================================================================
 *                         IPCOM Config Function pointers
 *===========================================================================
 * This function pointer variables are used to scale in and out modules at
 * VxWorks image build time.
 */
/* ramdisk init routine. Set to NULL if use of RAMDISK is disabled (default) */
FUNCPTR vxfs_ramdisk_init_hook = NULL;

/* VxWorks Shell command add routine. NULL if no VxWorks shell (default) */
FUNCPTR ipcom_vxshell_add_cmd_hook = NULL;

/* Shell command add routine. Set to NULL if no shell (default) */
struct Ipcom_shell_cmd_struct;
struct Ipcom_shell_cmd_struct * (*ipcom_shell_find_cmd_hook)(const char *) = NULL;

/* IPNET route command routine. Set to ipcom_mcmd_route() if no shell cmd
   (default) */
FUNCPTR ipnet_cmd_route_hook = (FUNCPTR)NULL;

/* IPNET ifconfig command routine. Set to ipcom_mcmd_ifconfig() if no shell
   cmd (default) */
FUNCPTR ipnet_cmd_ifconfig_hook = (FUNCPTR)NULL;

/* IPNET qc command routine. */
FUNCPTR ipnet_cmd_qc_hook = (FUNCPTR)NULL;

#endif /* IP_PORT_VXWORKS */

#ifdef INCLUDE_OCTEON_VXB_FORWARDER
IP_PUBLIC void *ipcom_forwarder_shm_start = (void *)0x84800000;
IP_PUBLIC int ipcom_forwarder_ipsec_sa_cache_size = OCTEON_FORWARDER_IPSEC_SA_CACHE_SIZE;
IP_PUBLIC int ipcom_forwarder_ipsec_single_output_queue = OCTEON_FORWARDER_IPSEC_SINGLE_OUTPUT_QUEUE;
IP_EXTERN void *ipcom_forwarder_alloc_aligned(unsigned alignment, unsigned size);
#elif (defined (INCLUDE_NEHALEM_VXB_FORWARDER) || defined(INCLUDE_NEHALEM_FORWARDER_AMP_DATAPLANE))

#include <cpuset.h>
#include <vxCpuLib.h>

IP_PUBLIC int ipcom_forwarder_ipsec_sa_cache_size = 256;
IP_PUBLIC int ipcom_forwarder_ipsec_single_output_queue = 0;

IP_PUBLIC cpuset_t  ipcom_forwarder_cpus;
#else
IP_PUBLIC int ipcom_forwarder_ipsec_sa_cache_size = 0;
IP_PUBLIC int ipcom_forwarder_ipsec_single_output_queue = 0;
#endif /* INCLUDE_OCTEON_VXB_FORWARDER */


/*
 ****************************************************************************
 * 8                   FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipcom_register_shell_commands
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
/*lint -efunc(429,ipcom_shell_add_cmd)  Custodial pointer 'ptr' (line X) has not been freed or returned*/
#ifndef IP_PORT_OSE5
#if defined(INCLUDE_IPCOM_SHELL_CMD) || !defined(IP_PORT_VXWORKS)
IP_STATIC void
ipcom_register_shell_commands(void)
{
#if IPCOM_USE_SHELL != IPCOM_SHELL_NONE

#if defined(INCLUDE_ERRNOS_CMD)
    (void)ipcom_shell_add_cmd("errnos", "errnos", "Dump generic errno strings",
                              ipcom_cmd_errno,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_SMALL);
#endif

#if defined(INCLUDE_IPVERSION_CMD) || !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("ipversion", "ipversion", "Show interpeak product versions",
                              ipcom_cmd_version,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_SMALL);
#endif

#if defined(INCLUDE_IPD_CMD) || !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("ipd", "ipd <command> [ -options ]", "ipd - Interpeak daemon control",
                              ipcom_cmd_ipd,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
#endif

#if defined(INCLUDE_IPCOM_CPU_CMD) || !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("cpu", "cpu", "Set/Get CPU affinity",
                              ipcom_cmd_cpu,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
#endif

#if defined(INCLUDE_IPCOM_SYSLOGD_CMD) || defined(IPCOM_USE_SYSLOG) && !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("syslog", "syslog <command> [ -options ]", "syslog",
                              ipcom_cmd_syslog,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
#endif

#if defined(INCLUDE_IPCOM_SYSVAR_CMD) || defined(IPCOM_USE_SYSVAR) && !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("sysvar", "sysvar <command> [name] [value]", "System variable tool",
                              ipcom_cmd_sysvar,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
#endif


#if defined(INCLUDE_IPMEM_DEBUG_CMD) || defined(IPCOM_USE_DMALLOC) && !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("mem", "mem <command> [ options ]", "Memory debug tool",
                              ipcom_cmd_mem,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
#endif

#if defined(INCLUDE_IPTCP_TEST_CMD) || !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("ttcp", "ttcp [ options ] <modifier...>", "ttcp - standard performance test",
                              ipcom_cmd_ttcp,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
    (void)ipcom_shell_add_cmd("ttcp1", "ttcp1 [ options ] <modifier...>", "ttcp - min priority",
                              ipcom_cmd_ttcp,
                              IPCOM_PRIORITY_MIN, IPCOM_PROC_STACK_DEFAULT);
    (void)ipcom_shell_add_cmd("ttcp7", "ttcp7 [ options ] <modifier...>", "ttcp - max priority",
                              ipcom_cmd_ttcp,
                              IPCOM_PRIORITY_MAX, IPCOM_PROC_STACK_DEFAULT);
#endif

#if defined(INCLUDE_IPSOCKPERF_CMD) || !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("sockperf", "sockperf [options] [addr]", "Network performance test tool",
                              ipcom_cmd_sockperf,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
#endif

#if defined(INCLUDE_IPSOCKTEST_CMD) || !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("socktest", "socktest [ options ] <modifier...>", "Socket API test tool",
                              ipcom_cmd_socktest,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_LARGE);
#endif


#if defined(INCLUDE_IPTRACE_ROUTE_CMD) || !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("traceroute", "traceroute <peer>", "Trace route command for IPv4",
                              ipcom_cmd_tracert,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
#endif

#if defined(INCLUDE_IPECHO_SERVER_CMD) || !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("echoserver", "echoserver [ options ]", "TCP/UDP echo server",
                              ipcom_cmd_echoserver,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
#endif

    /* echoclient */
#if defined(INCLUDE_IPECHO_CLIENT_CMD) || !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("echoclient", "send [ options ]", "TCP/UDP echo client",
                              ipcom_cmd_echoclient,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
#endif

#if IPCOM_USE_ENV != IPCOM_ENV_NONE
    (void)ipcom_shell_add_cmd("setenv", "setenv [name] [value]", "Set an environment variable",
                              ipcom_cmd_setenv,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);

    (void)ipcom_shell_add_cmd("getenv", "getenv [name]", "Get an environment variable",
                              ipcom_cmd_getenv,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
#endif

#if IPCOM_VR_MAX > 1
    (void)ipcom_shell_add_cmd("chvr", "chvr [vr]/get", "Set/Get vr value of shell process",
                              ipcom_cmd_chvr,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
#endif

#if defined(INCLUDE_IPCOM_USE_TIME_CMD) || defined(IPCOM_USE_TIME) && !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("date", "date [yyyy-mm-dd]", "Show/Set current date",
                              ipcom_cmd_date,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);

    (void)ipcom_shell_add_cmd("time", "time [hh:mm:ss]", "Show/Set current time",
                              ipcom_cmd_time,
                              IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
#endif


#if defined(INCLUDE_IPCOM_USE_MIB2_CMD) || defined(IPCOM_USE_MIB2_CMD) && !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("mib2", "mib2 <cmd>", "Print MIB-2 statistics",
                              ipcom_cmd_mib2,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
#endif

#if defined(INCLUDE_NETSMP_CMD)
    (void)ipcom_shell_add_cmd("netsmp", "netsmp {-n | -c | -e | -r | -a NET_IX}",
                              "Show SMP-related information",
                              ipcom_cmd_netsmp,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_SMALL);
#endif

#ifdef IPCOM_USE_SMPTEST_CMD
    (void)ipcom_shell_add_cmd("smptest", "smptest <cmd>", "Do a SMP stresstest",
                              ipcom_cmd_smptest,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
#endif

#ifdef IPROUTE2
    (void)ipcom_shell_add_cmd("ip", "ip <command>", "iproute2 command utility",
                              iproute2_cmd,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
#endif


#if defined(INCLUDE_USER_CMD) || defined(IPCOM_USE_AUTH) && !defined(IP_PORT_VXWORKS)
    (void)ipcom_shell_add_cmd("user", "user <command> [name] [value]", "User admin command",
                              ipcom_cmd_user,
                              IPCOM_PRIORITY_DEFAULT, IPCOM_PROC_STACK_DEFAULT);
#endif


#if defined(INCLUDE_IPCOM_USE_VXSHELL_CMD) && IPCOM_USE_SHELL == IPCOM_SHELL_IPCOM
    (void)ipcom_shell_add_cmd("vxshell", "vxshell",
                              "Enter VxWorks target shell",
                              ipcom_cmd_vxshell, IPCOM_PRIORITY_DEFAULT,
                              IPCOM_PROC_STACK_DEFAULT);
#endif /* INCLUDE_IPCOM_USE_VXSHELL_CMD */

#ifdef INCLUDE_IPWLAN_CMD
    (void)ipcom_shell_add_cmd("wifi", "wifi",
                              "Wireless LAN config command",
                              ipwlan_cmd_wlan, IPCOM_PRIORITY_DEFAULT,
                              IPCOM_PROC_STACK_DEFAULT);
#endif /* INCLUDE_IPWLAN_CMD */

#endif /* IPCOM_USE_SHELL != IPCOM_SHELL_NONE */
}
#endif
#endif /* IP_PORT_OSE5 */


/*
 *===========================================================================
 *                         ipcom_configure
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipcom_configure(void)
{
#ifndef IP_PORT_VXWORKS
    (void)ipcom_sethostname("iptarget", 8);
#endif

#ifndef IP_PORT_OSE5

#if defined(INCLUDE_IPCOM_SHELL_CMD) || !defined(IP_PORT_VXWORKS)
    ipcom_register_shell_commands();
#endif

#ifdef IPCOM_START_SHELL
    ipcom_set_start_shell_ptr(IPCOM_START_SHELL);
#else
#if IPCOM_USE_SHELL == IPCOM_SHELL_IPCOM
    ipcom_set_start_shell_ptr(ipcom_start_shell_ipcom);
#elif (IPCOM_USE_SHELL == IPCOM_SHELL_NATIVE) && defined(INCLUDE_SHELL)
    ipcom_set_start_shell_ptr(ipcom_start_shell_native);
#endif
#endif

#ifndef IP_PORT_VXWORKS
#ifdef IPCOM_USE_AUTH
    /* Add some default users. */
    (void)ipcom_auth_useradd("root", "iamroot", 0);
    (void)ipcom_auth_useradd("olli", "bolli", 1000);
    (void)ipcom_auth_useradd("telnet", "interpeak", 1001);
    (void)ipcom_auth_useradd("ftp", "interpeak", 1002);
    (void)ipcom_auth_useradd("ppp", "kallekula", 1003);
    (void)ipcom_auth_useradd("ipssh", "interpeak", 1004);
#endif /* IPCOM_USE_AUTH */

#endif /* !IP_PORT_VXWORKS */
#endif /* !IP_PORT_OSE5 */

#ifdef IPCOM_USE_SYSLOG
#  ifdef IPCOM_SYSLOGD_QUEUE_MAX
    (void)ipcom_sysvar_set("ipcom.syslogd.queue.max",
			   IPASCII(IPCOM_SYSLOGD_QUEUE_MAX), 0);
#  else
    (void)ipcom_sysvar_set("ipcom.syslogd.queue.max", "256", 0);
#  endif

    /* Default runtime syslog priority (change with shell command syslog) */
#  ifdef IPCOM_SYSLOGD_DEFAULT_PRIORITY
    (void)ipcom_sysvar_set("ipcom.syslogd.default_priority",
			   IPASCII(IPCOM_SYSLOGD_DEFAULT_PRIORITY), 0);
#  else
#    ifdef IP_DEBUG
    (void)ipcom_sysvar_set("ipcom.syslogd.default_priority", IPASCII(IPCOM_SYSLOG_PRIO_DEFAULT), 0);
#    else
    (void)ipcom_sysvar_set("ipcom.syslogd.default_priority", IPASCII(IPCOM_LOG_ERR), 0);
#    endif
#  endif

#   ifdef IPCOM_SYSLOGD_LOG_FILE
    /* Set logfile name. Note: Set filename to IP_NULL to disable. */
    (void)ipcom_setlogfile(IPCOM_SYSLOGD_LOG_FILE);
#   else
    (void)ipcom_setlogfile(IPCOM_SYSLOG_LOGFILE);
#   endif

    /* Set UDP log host and port. Note: Set port to 0 to disable.
#ifdef IPCOM_USE_INET
    (void)ipcom_setlogudp("255.255.255.255", 000);
#else
    (void)ipcom_setlogudp("FF02::1%2", 4000);
#endif
    */

#endif /* IPCOM_USE_SYSLOG */

#ifdef INCLUDE_IPCRYPTO_USE_KEY_DB_EXAMPLE_KEYS
    ipcrypto_key_db_install_example_keys();
#endif

    return IPCOM_SUCCESS;
}


#ifdef IP_PORT_VXWORKS
/*
 *===========================================================================
 *                         ipcom_config_create
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC void
ipcom_config_create(void)
{
    ipcom_create ();
}

/*
 *===========================================================================
 *                         ipcom_config_usr_create
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC void
ipcom_config_usr_create(void)
{
    ipcom_usr_create ();
}

/*
 *===========================================================================
 *                         ipcom_init_config_vars
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC void
ipcom_init_config_vars(void)
{
#if defined(INCLUDE_IPCOM_USE_RAM_DISK)
#if IPCOM_USE_FILE == IPCOM_FILE_NATIVE && defined(IPCOM_USE_RAM_DISK)
    vxfs_ramdisk_init_hook = (FUNCPTR)vxfs_ramdisk_init;
#endif
#endif

#if defined(INCLUDE_IPCOM_SHELL_CMD)
    ipcom_shell_find_cmd_hook = ipcom_shell_find_cmd;

#if IPCOM_USE_SHELL != IPCOM_SHELL_NONE
    /* Add the "network" topic. */
    (void)shellCmdTopicAdd ("network", "Network commands");
    ipcom_vxshell_add_cmd_hook = shellCmdAdd;
#endif

#endif /* INCLUDE_IPCOM_SHELL_CMD */

#ifdef IPLITE
    ipnet_cmd_route_hook = iplite_cmd_route;
    ipnet_cmd_ifconfig_hook = iplite_cmd_ifconfig;
#else
#if defined(INCLUDE_IPROUTE_CMD)
    ipnet_cmd_route_hook = ipnet_cmd_route;
#else
    ipnet_cmd_route_hook = (FUNCPTR)ipcom_mcmd_route;
#endif

#if defined(INCLUDE_IPIFCONFIG_CMD)
    ipnet_cmd_ifconfig_hook = ipnet_cmd_ifconfig;
#else
    ipnet_cmd_ifconfig_hook = (FUNCPTR)ipcom_mcmd_ifconfig;
#endif
#endif /* #ifdef IPLITE */

#if defined(INCLUDE_IPQUEUE_CONFIG_CMD)
    ipnet_cmd_qc_hook = (FUNCPTR)ipnet_cmd_qc;
#endif

#ifdef INCLUDE_SYS_MEM_MGMT
#ifdef SYS_MALLOC
    {
        IP_EXTERN void *SYS_MALLOC(Ip_size_t size);
        ipcom_sys_malloc = (void *(*)(Ip_size_t size))SYS_MALLOC;
    }
#endif /* SYS_MALLOC */
#ifdef SYS_FREE
    {
        IP_EXTERN void SYS_FREE(void *ptr);
        ipcom_sys_free = (void (*)(void *ptr))SYS_FREE;
    }
#endif /* SYS_FREE */
#endif /* INCLUDE_SYS_MEM_MGMT */
}


/*
 *===========================================================================
 *                    ipcom_configure_reserved_cpus
 *===========================================================================
 * Description: Configure the set of CPUs to be reserved and excluded from
 *              normal scheduling. Must be called prior to schedule start.
 * Parameters:  num - number of CPUs to exclude
 * Returns:     IPCOM_SUCCESS    = success
 *              IPCOM_ERR_FAILED = failure
 */
IP_PUBLIC Ip_err
ipcom_configure_reserved_cpus(int num)
{
    (void)num;
#ifdef IPCOM_USE_SMP
#if 0
    cpuset_t cpuset;
    int      i, count = 0;

    /* Get the current set of reserved CPUs */
    cpuset = vxCpuReservedGet();

    /* Traverse the set of CPUs from the top and select unreserved CPUs.
       Avoid CPU#0 */
    if (num > 0)
    {
        for (i = ipcom_num_configured_cpus() - 1; i > 0; i--)
        {
            if (!CPUSET_ISSET(cpuset, i))
            {
                CPUSET_SET(cpuset, i);
                if (++count == num)
                    break;
            }
        }
    }

    /* Check that CPUs were available */
    if (count < num)
        return IPCOM_ERR_FAILED;

    /* Update the set of reserved CPUs */
    if (vxCpuReservedSet(cpuset) == ERROR)
       return IPCOM_ERR_FAILED;
#endif /* if 0 */
    return IPCOM_SUCCESS;
#else
    return IPCOM_ERR_FAILED;
#endif
}

/*
 *===========================================================================
 *                    ipcom_forwarder support
 *===========================================================================
 */

#ifdef IPCOM_USE_FORWARDER

#if defined (INCLUDE_NEHALEM_VXB_FORWARDER) || \
    defined (INCLUDE_P4080_VXB_FORWARDER)
/* avoid including ipcom_vxworks_<platform>_forwarder.h */
#define IPCOM_FW_CPU_MEM_ALLOC_SHARED   2
IP_EXTERN void * ipcom_fw_cpu_mem_alloc(unsigned int cpu, Ip_size_t size,
                                        Ip_size_t align, unsigned int flags);
#endif

#ifdef INCLUDE_OCTEON_VXB_FORWARDER
IP_EXTERN int ipcom_forwarder_get_fw_cnt(void);
IP_EXTERN void ipcom_forwarder_reset_statistics(void *port_cookie);
IP_EXTERN void vxbOcteon_get_nonfw_stats(void *pdrv, Ip_u32 *frames, Ip_u32 *bytes, int reset);
IP_EXTERN void *ipcom_forwarder_get_tx_queue(void *end);
IP_EXTERN void ipcom_forwarder_pkt_pool(void *p, int num, int size);
IP_EXTERN void *vxbOcteon_get_fwd(void *);
IP_EXTERN uint32_t vxbOcteon_get_ports_for_interface (uint32_t iface);
IP_EXTERN int vxbOcteon_get_port_index(END_OBJ *end);
IP_EXTERN int vxbOcteon_get_mac(void *pDrv, void *mac);
IP_EXTERN int vxbOcteon_set_mac(void *pDrv, void *mac);
IP_EXTERN void *ipcom_get_regs_print_area(void);
#endif

#ifndef FWCACHE_USE_LEVEL_LIMIT
#define FWCACHE_USE_LEVEL_LIMIT (25)
#endif


IP_PUBLIC int
ipcom_forwarder_get_fwcache_util_level_limit(void)
{
    return FWCACHE_USE_LEVEL_LIMIT;
}


IP_PUBLIC Ip_u32
ipcom_forwarder_get_ports_for_interface (Ip_u32 iface)
{
#ifdef INCLUDE_OCTEON_VXB_FORWARDER
 #if defined(IPCOM_USE_SMP) || defined(INCLUDE_AMP_CPU_00) || defined(INCLUDE_AMP_CPU_01)
    return vxbOcteon_get_ports_for_interface(iface);
 #else
    return 0;
 #endif
#else
    return 0;
#endif
}

IP_PUBLIC void
ipcom_forwarder_get_nonfw_stats(void *end, Ip_u32 *frames, Ip_u32 *bytes, int reset)
{
#ifdef INCLUDE_OCTEON_VXB_FORWARDER
 #if defined(IPCOM_USE_SMP) || defined(INCLUDE_AMP_CPU_00)
    vxbOcteon_get_nonfw_stats(end, frames, bytes, reset);
 #else
    (void)end;
    (void)frames;
    (void)bytes;
    (void)reset;
 #endif
#else
    (void)end;
    (void)frames;
    (void)bytes;
    (void)reset;
#endif
}

IP_PUBLIC void *
ipcom_forwarder_get_tx_queue(void *end)
{
#ifdef INCLUDE_OCTEON_VXB_FORWARDER
 #if defined(IPCOM_USE_SMP) || defined(INCLUDE_AMP_CPU_00)
    return vxbOcteon_get_fwd(end);
 #else
    (void)end;
    return IP_NULL;
 #endif
#else
    (void)end;
    return IP_NULL;
#endif
}

IP_PUBLIC void *
ipcom_forwarder_get_tx_queue_cf(void *end)
{
#ifdef INCLUDE_OCTEON_VXB_FORWARDER
    return ipcom_forwarder_get_tx_queue(end);
#else
    return IP_NULL;
#endif
}

IP_PUBLIC int
ipcom_forwarder_get_hw_ix(void *end)
{
#if defined(INCLUDE_OCTEON_VXB_MASTER_FORWARDER)
    return vxbOcteon_get_port_index(end);
#elif defined(INCLUDE_OCTEON_VXB_FORWARDER) && defined(IPCOM_USE_SMP)
    return vxbOcteon_get_port_index(end);
#else
    return -1;
#endif
}

IP_PUBLIC void
ipcom_forwarder_reset_statistics_cf(int port)
{
#ifdef INCLUDE_OCTEON_VXB_FORWARDER
    ipcom_forwarder_reset_statistics(ipcom_forwarder_get_port_cookie(port));
#endif
}

#if defined(IPCOM_FORWARDER_SMP) || defined(IPCOM_FORWARDER_NAE)
IP_PUBLIC int
ipcom_forwarder_transmit_pkt_cf(void *pkt, void *netif)
{
#if defined (INCLUDE_OCTEON_VXB_FORWARDER) || \
    defined (INCLUDE_NEHALEM_VXB_FORWARDER) || \
    defined (INCLUDE_NEHALEM_FORWARDER_AMP_DATAPLANE) || \
    defined (INCLUDE_P4080_VXB_FORWARDER) || \
    defined (INCLUDE_P4080_FORWARDER_AMP_DATAPLANE)
    return ipcom_forwarder_transmit_pkt(pkt, netif);
#else
    return 1; /* Did not transmit packet */
#endif
}
#endif /* IPCOM_USE_FORWARDER && IPCOM_FORWARDER_LOCAL_STACK */

IP_PUBLIC int
ipcom_forwarder_create_cf(void)
{
    /* Called from ipnet_start() */
#if defined (INCLUDE_OCTEON_VXB_FORWARDER) || \
    defined (INCLUDE_NEHALEM_VXB_FORWARDER)|| \
    defined (INCLUDE_P4080_VXB_FORWARDER)
    return ipcom_forwarder_create();
#else
    return 0;
#endif
}

IP_PUBLIC void
ipcom_forwarder_master_tick_cf(void)
{
#ifdef INCLUDE_OCTEON_VXB_FORWARDER
#ifndef IPCOM_USE_SMP
/*     ipcom_forwarder_master_tick(); */
#endif
#endif
}

IP_PUBLIC void
ipcom_forwarder_pkt_pool_cf(void *p, int num, int size)
{
#ifdef INCLUDE_OCTEON_VXB_FORWARDER
#ifdef IP_LW_DEBUG
    ipcom_forwarder_pkt_pool(p, num, size);
#endif
#endif
}

IP_PUBLIC void
ipcom_forwarder_startup_delay(void)
{
#ifdef VX_ENABLE_CPU_TIMEOUT
    ipcom_sleep(VX_ENABLE_CPU_TIMEOUT);
#endif
}

IP_PUBLIC int
ipcom_reserve_fw_cpu(void)
{
#ifdef INCLUDE_OCTEON_VXB_FORWARDER
    return ipcom_configure_reserved_cpus(ipcom_forwarder_get_fw_cnt());
#elif defined (INCLUDE_NEHALEM_VXB_FORWARDER)
#ifdef IPCOM_FORWARDER_SMP
    cpuset_t obtained;
    CPUSET_ZERO(obtained);
    if (vxCpuReserve (ipcom_forwarder_cpus, &obtained) != OK)
        {
        if (_func_logMsg)
            _func_logMsg ("Failed to reserve CPUs 0x%x for forwarding!\n",
                          ipcom_forwarder_cpus);
        return IPCOM_ERR_FAILED;
        }
#endif
    return IPCOM_SUCCESS;
#else
    return IPCOM_SUCCESS;
#endif
}

#define IPCOM_TAG_BITS (16)

IP_PUBLIC int
ipcom_forwarder_config_cache_size(void)
{
#ifdef INCLUDE_OCTEON_VXB_FORWARDER
    Ip_u32 nsize = OCTEON_FORWARDER_CACHE_SIZE;
#elif defined (INCLUDE_NEHALEM_VXB_FORWARDER)
    Ip_u32 nsize = NEHALEM_FORWARDER_CACHE_SIZE;
#elif defined (INCLUDE_P4080_VXB_FORWARDER)
    Ip_u32 nsize = P4080_FORWARDER_CACHE_SIZE;
#else
    return 0;
#endif

#if defined (INCLUDE_OCTEON_VXB_FORWARDER) || \
    defined (INCLUDE_NEHALEM_VXB_FORWARDER) || \
    defined (INCLUDE_P4080_VXB_FORWARDER)
    int i;


    /*
     * At this point nsize has a nominal number of cache entries.
     * In case IPCOM_FORWARDER_TRUE_CACHE_WAYS is greater than 1,
     * this routine returns the number of cache _sets_.  It returns
     * N, the smallest power of two no less than 16 such that either
     * the total number of entries is at least the requested number,
     * or else N == 65536.
     */

    nsize += IPCOM_FORWARDER_TRUE_CACHE_WAYS - 1; /* round up */

    for (i = 4; i < IPCOM_TAG_BITS; i++)
    {
        if (((nsize / IPCOM_FORWARDER_TRUE_CACHE_WAYS - 1) >> i) == 0)
        {
            break;
        }
    }
    return 1 << i;
#endif
}


/*
 *===========================================================================
 *                    ipcom_allocate_fw_cache
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC void *
ipcom_allocate_fw_cache(int entry_size, int *entries)
{
#if defined (INCLUDE_OCTEON_VXB_FORWARDER) || \
    defined (INCLUDE_NEHALEM_VXB_FORWARDER)  || \
    defined (INCLUDE_P4080_VXB_FORWARDER)
#define IPCOM_CACHELINE_SZ (128)

    void *p;
    int csize = ipcom_forwarder_config_cache_size();
    size_t memsize;

    IPCOM_LOG3(DEBUG, "ipcom_allocate_fw_cache() :: cache entries: %d, buckets: %d, ways: %d",
           csize * IPCOM_FORWARDER_TRUE_CACHE_WAYS,
           csize,
           IPCOM_FORWARDER_TRUE_CACHE_WAYS);

    memsize = entry_size * (csize * IPCOM_FORWARDER_TRUE_CACHE_WAYS + IPCOM_FORWARDER_CACHE_WAYS);

#if !defined(IPCOM_FORWARDER_SMP)

#if defined (INCLUDE_OCTEON_VXB_FORWARDER)
    p = ipcom_forwarder_alloc_aligned(IPCOM_CACHELINE_SZ, memsize);
#elif defined(INCLUDE_NEHALEM_VXB_FORWARDER) || defined(INCLUDE_P4080_VXB_FORWARDER)
    p = ipcom_fw_cpu_mem_alloc (ipcom_forwarder_master_core(), /* for now */
                                memsize, IPCOM_CACHELINE_SZ,
                                IPCOM_FW_CPU_MEM_ALLOC_SHARED);
#endif
    memset(p, 0, memsize);
#else
    memsize += IPCOM_CACHELINE_SZ; /* for alignment */
    p = malloc(memsize);
    memset(p, 0, memsize);
    p = (void *)((((Ip_ptrdiff_t)p) + IPCOM_CACHELINE_SZ - 1) & ~(IPCOM_CACHELINE_SZ - 1));
#endif

    if (entries)
    {
        *entries = csize;
    }
    return p;
#else
    (void)entry_size;
    (void)entries;
    return IP_NULL;
#endif
}


IP_PUBLIC int
ipcom_forwarder_config_fw_max(void)
{
#ifdef _WRS_CONFIG_OCTEON_NUM_FORWARDERS
    return _WRS_CONFIG_OCTEON_NUM_FORWARDERS;
#else
    return 0;
#endif
}

IP_PUBLIC int
ipcom_forwarder_fw_per_port(void)
{
#if OCTEON_BIND_INPUT_PORT_TO_FORWARDER == TRUE
    return IP_TRUE;
#else
    return IP_FALSE;
#endif
}


IP_PUBLIC void *
ipcom_get_regs_print_area_cf(void)
{
#if defined(INCLUDE_OCTEON_VXB_FORWARDER) && defined(IPCOM_NAE_DEBUG)
    return ipcom_get_regs_print_area();
#else
    return IP_NULL;
#endif
}


#if defined(IPCOM_FORWARDER_SMP)
IP_PUBLIC int
ipcom_fw_register_netif_cf(void *netif)
{
#if defined (INCLUDE_OCTEON_VXB_FORWARDER) || \
    defined (INCLUDE_NEHALEM_VXB_FORWARDER) || \
    defined (INCLUDE_P4080_VXB_FORWARDER)
    return ipcom_fw_register_netif(netif);
#else
    return 0;
#endif
}

IP_PUBLIC void
ipcom_fw_deregister_netif_cf(void *netif)
{
#if defined (INCLUDE_OCTEON_VXB_FORWARDER) || \
    defined (INCLUDE_NEHALEM_VXB_FORWARDER) || \
    defined (INCLUDE_P4080_VXB_FORWARDER)
    ipcom_fw_deregister_netif(netif);
#endif
}

IP_PUBLIC Ip_err
ipcom_forwarder_ioctl_cf(void *netif, int code, void *fwreq)
{
#if defined (INCLUDE_OCTEON_VXB_FORWARDER) || \
    defined (INCLUDE_NEHALEM_VXB_FORWARDER) || \
    defined (INCLUDE_P4080_VXB_FORWARDER)
    return ipcom_forwarder_ioctl(netif, code, fwreq);
#else
    return -1;
#endif
}
#endif /* IPCOM_USE_FORWARDER && IPCOM_FORWARDER_LOCAL_STACK */

/* Limits nominal MTU for all forwarder network devices */
IP_PUBLIC int
ipcom_forwarder_mtu(void)
{
#if defined (INCLUDE_NEHALEM_VXB_FORWARDER)
    return NEHALEM_FORWARDER_MTU;
#else
    return 1500;
#endif
}


IP_PUBLIC unsigned int
ipcom_forwarder_current_core(void)
{
    /*
     * Note that under SMP, this result of this function may
     * be obsolete unless CPU migration is prevented.
     */
#if defined(IPCOM_FORWARDER_SMP)
    return vxCpuIndexGet();
#else /* AMP/NAE case */
#if defined (INCLUDE_NEHALEM_VXB_FORWARDER) || \
    defined (INCLUDE_NEHALEM_FORWARDER_AMP_DATAPLANE) || \
    defined (INCLUDE_P4080_VXB_FORWARDER) || \
    defined (INCLUDE_P4080_FORWARDER_AMP_DATAPLANE)
    unsigned int cpu;
    extern BOOL _procNumWasSet;

    /*
     * We presently depend upon the sysProcNum boot
     * parameter being set in the bootline for this VB by the
     * hypervisor configuration to indicate the physical
     * CPU core that this board runs on. Would like a better
     * method.
     */
    if(!_procNumWasSet)
    {
        BOOT_PARAMS p;
        char *pEndStr;
        pEndStr = bootStringToStruct(sysBootLine, &p);
        if (*pEndStr != EOS)
        {
            (void)errnoSet(EINVAL);
            bootParamsErrorPrint(sysBootLine, pEndStr);
            return 0;
        }
        sysProcNumSet(p.procNum);
        _procNumWasSet = TRUE;
    }
    cpu = sysProcNumGet();

    return cpu;
#elif defined(INCLUDE_OCTEON_VXB_FORWARDER)
#if defined(INCLUDE_AMP_CPU_00)
    return 0;
#elif defined(INCLUDE_AMP_CPU_01)
    return 1;
#elif defined(INCLUDE_AMP_CPU_02)
    return 2;
#elif defined(INCLUDE_AMP_CPU_03)
    return 3;
#elif defined(INCLUDE_AMP_CPU_04)
    return 4;
#elif defined(INCLUDE_AMP_CPU_05)
    return 5;
#elif defined(INCLUDE_AMP_CPU_06)
    return 6;
#elif defined(INCLUDE_AMP_CPU_07)
    return 7;
#elif defined(INCLUDE_AMP_CPU_08)
    return 8;
#elif defined(INCLUDE_AMP_CPU_09)
    return 9;
#elif defined(INCLUDE_AMP_CPU_10)
    return 10;
#elif defined(INCLUDE_AMP_CPU_11)
    return 11;
#elif defined(INCLUDE_AMP_CPU_12)
    return 12;
#elif defined(INCLUDE_AMP_CPU_13)
    return 13;
#elif defined(INCLUDE_AMP_CPU_14)
    return 14;
#elif defined(INCLUDE_AMP_CPU_15)
    return 15;
#else
#error No INCLUDE_AMP_CPU_<n> defined
    return -1;
#endif
/*    return cvmx_get_core_num(); */
#else
    return 0;
#endif
#endif /* defined(IPCOM_FORWARDER_SMP) */
}

#if defined(IPCOM_FORWARDER_NAE)
IP_PUBLIC unsigned int
ipcom_nae_extra_packets(void)
{
#ifdef IPCOM_NAE_EXTRA_PACKETS
    return IPCOM_NAE_EXTRA_PACKETS;
#else
    return 0;
#endif
}
#endif /* defined(IPCOM_FORWARDER_NAE) */


#if defined(IPCOM_FORWARDER_NAE) || defined (IPCOM_FORWARDER_AMP)

/*
 * Return CPU ID of master forwarder core / control NAE
 */
IP_PUBLIC unsigned int
ipcom_forwarder_master_core(void)
{
#if defined (INCLUDE_NEHALEM_VXB_FORWARDER) || \
    defined (INCLUDE_NEHALEM_FORWARDER_AMP_DATAPLANE) || \
    defined (INCLUDE_P4080_VXB_FORWARDER) ||  \
    defined (INCLUDE_P4080_FORWARDER_AMP_DATAPLANE)

    char * name;
    char * endptr;
    unsigned int i;
    static unsigned int master_core = ~0U;

    if (master_core != ~0U)
	return master_core;

    name = (char *)VBI_BOARD_NAME_GET();

    /*
     * Format of the board name is prefix:cpu:mgmt_cpu:ctrl_nae_cpu,
     * where the prefix is "mgmt", "ctrl", or "nae" for the
     * management board, control NAE, or regular NAE respectively.
     * The cpus are decimal numbers.
     */
    i = 0;
    while (*name != '\0')
	if (*name++ == ':' && ++i == 3)
	    break;
    i = (unsigned int)strtoul(name, &endptr, 10);
    if (name == endptr)
	i = 1; /* default */

    master_core = i;
    return i;
#else
    return 1;
#endif
}


/*
 *===========================================================================
 *                    ipcom_forwarder_is_master
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_bool
ipcom_forwarder_is_master(void)
{
#if defined (INCLUDE_OCTEON_VXB_MASTER_FORWARDER) || \
    defined (INCLUDE_NEHALEM_VXB_FORWARDER) || \
    defined (INCLUDE_P4080_VXB_FORWARDER)
    return IP_TRUE;
#else
    return IP_FALSE;
#endif
}


/*
 *===========================================================================
 *                   ipcom_forwarder_has_serial_console
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_bool
ipcom_forwarder_has_serial_console(void)
{
#if defined (INCLUDE_SIO)
    return IP_TRUE;
#else
    return IP_FALSE;
#endif
}

#if defined (INCLUDE_NEHALEM_FORWARDER_AMP_DATAPLANE)
IP_PUBLIC void
ipcom_forwarder_core_start(void)
{
    char tname [32];
    unsigned int cpu = ipcom_forwarder_current_core();
    extern int ipcom_fw_task (void);
    extern void ipcom_shm_init(void);

    ipcom_shm_init();

    ipcom_sprintf(tname, "ipfwdr%u", cpu);

    taskSpawn (tname, 100, 0, 20000, (FUNCPTR)ipcom_fw_task,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
#endif

#if defined (INCLUDE_P4080_FORWARDER_AMP_DATAPLANE)

extern void ipcom_forwarder(void);

/*
 *===========================================================================
 *                    ipcom_forwarder_core_start
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC void
ipcom_forwarder_core_start(void)
{
	TASK_ID tid;
    char tname [32];
    unsigned int cpu = ipcom_forwarder_current_core();

	ipcom_shm_init();

    sprintf (tname, "ipfwdr%u", cpu);

    tid = taskSpawn (tname, 254, 0, 20000, (FUNCPTR)ipcom_forwarder,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
#endif

#if defined (INCLUDE_P4080_VXB_FORWARDER)
IP_EXTERN void ipcom_forwarder_setup_portals(int, int);
#endif


/*
 *===========================================================================
 *                    ipcom_forwarder_setup_portals_cf
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC void
ipcom_forwarder_setup_portals_cf(void)
{
#if defined (INCLUDE_P4080_VXB_FORWARDER)
	ipcom_forwarder_setup_portals(0, 0);
#endif
}

#if defined (INCLUDE_P4080_VXB_FORWARDER) || defined (INCLUDE_P4080_FORWARDER_AMP_DATAPLANE)
/*
 *===========================================================================
 *                    ipcom_forwarder_init
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC unsigned int
ipcom_forwarder_init(void)
{
#if defined (INCLUDE_P4080_VXB_FORWARDER)
	ipcom_forwarder_retrieve_ports();
	ipcom_forwarder_ifproxy_init();
#endif
	return 1;
}
#endif


#if defined (INCLUDE_P4080_VXB_FORWARDER) || defined (INCLUDE_P4080_FORWARDER_AMP_DATAPLANE)
/*
 *===========================================================================
 *                    ipcom_fw_packet_send_cf
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC int
ipcom_fw_packet_send_cf(void *hdr, void *free_arg)
{
#if defined (INCLUDE_P4080_VXB_FORWARDER)
	return ipcom_fw_packet_send(hdr, free_arg);
#else
	return 0;
#endif
}
#endif


int * ipcom_route_cache_id_ptr = IP_NULL;

/*
 *===========================================================================
 *                    ipcom_route_cache_id_alloc_cf
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC int *
ipcom_route_cache_id_alloc_cf(void)
{
    if (ipcom_route_cache_id_ptr == IP_NULL)
    {
#if defined (INCLUDE_NEHALEM_VXB_FORWARDER) || \
    defined (INCLUDE_NEHALEM_FORWARDER_AMP_DATAPLANE) || \
    defined (INCLUDE_P4080_VXB_FORWARDER) || \
    defined (INCLUDE_P4080_FORWARDER_AMP_DATAPLANE)
        if (ipcom_forwarder_is_master())
        {
            /* caller ensures shared memory pools are created */
            ipcom_route_cache_id_ptr =
                ipcom_fw_cpu_mem_alloc(ipcom_forwarder_master_core(),
                                       sizeof (int),
                                       _CACHE_ALIGN_SIZE,
                                       IPCOM_FW_CPU_MEM_ALLOC_SHARED);
        }
        else
        {
            ipcom_route_cache_id_ptr =
                memalign(_CACHE_ALIGN_SIZE, _CACHE_ALIGN_SIZE);
        }
#elif defined(INCLUDE_OCTEON_VXB_FORWARDER)
        if (ipcom_forwarder_is_master())
            ipcom_route_cache_id_ptr =  ipcom_shm_calloc(1, sizeof(int));
        else
            ipcom_route_cache_id_ptr =  ipcom_calloc(1, sizeof(int));
#endif /* INCLUDE_OCTEON_VXB_FORWARDER */

        *ipcom_route_cache_id_ptr = 0;
    }
    return ipcom_route_cache_id_ptr;
}

#endif /* defined (IPCOM_FORWARDER_NAE) || defined  (IPCOM_FORWARDER_AMP) */


/*
 *===========================================================================
 *                    ipcom_forwarder_load_and_boot
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipcom_forwarder_load_and_boot(Ip_bool first, char **cpuctx, char **imagectx)
{
#ifdef INCLUDE_OCTEON_VXB_MASTER_FORWARDER
    char *cpu, *image;
    char cmd[128];

    if (first)
    {
        cpu   = strtok_r(OCTEON_VXB_SLAVE_FORWARDER_CPU_LIST, ",", cpuctx);
        image = strtok_r(OCTEON_VXB_SLAVE_FORWARDER_IMAGE_LIST, ",", imagectx);
    }
    else
    {
        cpu   = strtok_r(IP_NULL, ",", cpuctx);
        image = strtok_r(IP_NULL, ",", imagectx);
    }

    if (cpu == IP_NULL || image == IP_NULL)
        return IPCOM_ERR_FAILED;

    sprintf(cmd, "-f %s -cpu %s", image, cpu);
#ifdef FW_DEBUG
    printf("wrload (\"%s\")\n", cmd);
#endif
    return wrload(cmd) == OK ? IPCOM_SUCCESS : IPCOM_ERR_FAILED;
#else
    return IPCOM_SUCCESS;
#endif
}

/*
 * For a hash key of width IPCOM_TAG_BITS,  this routine tells
 * how many bits should we shift right if we want to use the
 * uppermost bits of the hash key rather than the lowermost bits.
 */
IP_PUBLIC int
ipcom_forwarder_get_key_shift(void)
{
    int n;
    int csize = ipcom_forwarder_config_cache_size();

    for (n = 4; n < IPCOM_TAG_BITS; n++)
    {
        if (csize & (1 << n))
        {
           return IPCOM_TAG_BITS - n;
        }
    }
    return 0;
}

#endif /* IPCOM_USE_FORWARDER */

#define NAE_RAMLOG_SIZE (1024)
#define END_OF_TEXT (3)
#define TEXT_WRAP (12)

IP_PUBLIC int
nae_log(char *log)
{
	int i = 0;

	if (log[0] == TEXT_WRAP)
	{
		for (i = 0; i < NAE_RAMLOG_SIZE; i++)
		{
			if (log[i] == END_OF_TEXT)
			{
				puts(log + i);
			}
		}
		i = 1;
	}
	puts(log + i);

	return 0;
}

#ifdef INCLUDE_POSIX_DIRLIB
/*
 *===========================================================================
 *                    ipcom_fstat
 *===========================================================================
 * Description:
 * VxWork's struct stat is of a different size, compared to struct Ip_stat.
 * Furthermore the struct members come in a different order.
 *
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC int
ipcom_fstat(int fildes, struct Ip_stat *buf)
{
    struct stat vxworks_stat;
    int rc;
    rc = fstat((int)fildes, &vxworks_stat);
    if (rc == OK)
    {
        buf->st_mode = vxworks_stat.st_mode;
        buf->st_ino = (Ip_ino_t)vxworks_stat.st_ino;
        buf->st_dev = vxworks_stat.st_dev;
        buf->st_nlink = (Ip_nlink_t)vxworks_stat.st_nlink;
        buf->st_uid = vxworks_stat.st_uid;
        buf->st_gid = vxworks_stat.st_gid;
        buf->st_size = (int)vxworks_stat.st_size;
        buf->st_atime = vxworks_stat.st_atime;
        buf->st_mtime = vxworks_stat.st_mtime;
        buf->st_ctime = vxworks_stat.st_ctime;
    }
    return rc;
}

/*
 *===========================================================================
 *                    ipcom_stat
 *===========================================================================
 * Description:
 * VxWork's struct stat is of a different size, compared to struct Ip_stat.
 * Furthermore the struct members come in a different order.
 *
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC int
ipcom_stat(const char *pathname, struct Ip_stat *buf)
{
    struct stat vxworks_stat;
    int rc;

    rc = stat((char*) pathname, &vxworks_stat);
    if (rc == OK)
    {
        buf->st_mode = vxworks_stat.st_mode;
        buf->st_ino = (Ip_ino_t)vxworks_stat.st_ino;
        buf->st_dev = vxworks_stat.st_dev;
        buf->st_nlink = (Ip_nlink_t)vxworks_stat.st_nlink;
        buf->st_uid = vxworks_stat.st_uid;
        buf->st_gid = vxworks_stat.st_gid;
        buf->st_size = (int)vxworks_stat.st_size;
        buf->st_atime = vxworks_stat.st_atime;
        buf->st_mtime = vxworks_stat.st_mtime;
        buf->st_ctime = vxworks_stat.st_ctime;
    }
    return rc;
}

/*
 *===========================================================================
 *                    ipcom_opendir
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC IP_DIR *
ipcom_opendir(const char *dirname)
{
    return (IP_DIR *)opendir( (char*) dirname);
}

/*
 *===========================================================================
 *                    ipcom_readdir
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC struct Ip_dirent *
ipcom_readdir(IP_DIR *dirp)
{
    static struct Ip_dirent dir_entry;
    struct dirent *tmp;

    tmp = readdir((DIR *)dirp);
    if (tmp != IP_NULL)
    {
        dir_entry.d_namlen = (Ip_u32)ipcom_strlen(tmp->d_name);
        ipcom_strcpy(dir_entry.d_name, tmp->d_name);
        return &dir_entry;
    }
    else
        return IP_NULL;
}

/*
 *===========================================================================
 *                    ipcom_closedir
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC int
ipcom_closedir(IP_DIR *dirp)
{
    return closedir((DIR *)dirp);
}

/*
 *===========================================================================
 *                    ipcom_rmdir
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC int
ipcom_rmdir(const char *dirName)
{
    /*
     * Hmm. This duplicates code in usrFsLib.c to avoid bringing the
     * whole of usrFsLib.c into the image.
     */
    int           fd;
    int           error;
    STATUS        status;
    struct stat   stat;

    if ((fd = open (dirName, O_RDONLY, 0)) == ERROR)
        return (ERROR);

    if (fstat (fd, &stat) != OK)        /* Obtain file stats on <dirName>. */
    {
        error = errnoGet ();
        close (fd);
        (void)errnoSet (error);
        return (ERROR);
    }

    if (!S_ISDIR (stat.st_mode))        /* If it is not a directory, then  */
    {                               /* set <errno> and return ERROR.   */
        close (fd);
        (void)errnoSet (ENOTDIR);
        return (ERROR);
    }

    status = ioctl (fd, FIORMDIR, dirName);
    error = errnoGet ();
    close (fd);

    if ((status != OK) && ((error == ENOTSUP) || (error == ENOSYS)))
        return (remove (dirName));

    return (status);
}

/*
 *===========================================================================
 *                    ipcom_chdir
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC int
ipcom_chdir(const char *path)
{
    DIR *dir;

    /*
     * VxWorks filesystem does not check that the destination dir is valid--
     * this must be done by the clients.
     */
    if ((dir = opendir(path)) == NULL)
        return -1;

    (void)closedir(dir);

    return chdir((char*)path);
}
#endif /* INCLUDE_POSIX_DIRLIB */

#endif /* IP_PORT_VXWORKS */


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
