/*
 * Copyright (c) 2006-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_PCONFIG_H
#define IPCOM_PCONFIG_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */
#include <vsbConfig.h>           /* Include the VxWorks VSB configuration */
#include <ipcom_pautoconf.h>     /* Translate VSB configuration macros */

#ifdef __cplusplus
extern "C" {
#endif


/*
 *===========================================================================
 *                        IPCOM_USE_SMP
 *===========================================================================
 * Define IPCOM_USE_SMP if IPCOM is built against a SMP version of VxWorks.
 */
#if defined(_WRS_CONFIG_SMP) || defined(_WRS_VX_SMP)
# define IPCOM_USE_SMP
#endif


/*
 *===========================================================================
 *                         Port services
 *===========================================================================
 */

/* Valid values: IPCOM_FILE_IPCOM | IPCOM_FILE_NATIVE | IPCOM_FILE_NONE */
#ifndef IPCOM_USE_FILE
# ifdef IPBASIC
#  define IPCOM_USE_FILE IPCOM_FILE_NONE
# else
#  define IPCOM_USE_FILE IPCOM_FILE_NATIVE
# endif
#endif

/* Valid values: IPCOM_SHELL_IPCOM | IPCOM_SHELL_NATIVE | IPCOM_SHELL_NONE */
/* IPCOM_SHELL_NATIVE only supported on VxWorks-6.5 or later */
#ifndef IPCOM_USE_SHELL
#ifdef _WRS_CONFIG_SHELL
# ifdef IPBASIC
#  define IPCOM_USE_SHELL IPCOM_SHELL_NONE
# else
#   define IPCOM_USE_SHELL IPCOM_SHELL_NATIVE
# endif
#else
#  define IPCOM_USE_SHELL IPCOM_SHELL_NONE
#endif
#endif

/* IPCOM_USE_SOCK automatically set in ipcom_config.h */


/*
 *===========================================================================
 *                         IPCOM_USE_NATIVE_SOCK_API
 *===========================================================================
 * When this define is set, the ipcom_socket* API is mapped by the
 * pre-processor directly to the VxWorks sockLib.
 */
#define IPCOM_USE_NATIVE_SOCK_API

/*
 *===========================================================================
 *                         IPCOM_USE_SOCK_COMPAT
 *===========================================================================
 * Set this define if you want to register IPNET/IPLITE as a socket backend.
 * This makes Interpeak stacks binary compatible with windnet
 * (vxworks "default" stack), regarding basic socket calls.
 * This define must not be set when using the windnet stack.
 */
#if defined(IPNET) || defined(IPLITE)
#define IPCOM_USE_SOCK_COMPAT
#endif

/*
 *===========================================================================
 *                      IPNET_SO_WAKEUP_HOOK
 *===========================================================================
 * Set this define if you want to use legacy sowakeupHook.
 */
#if defined(IP_PORT_VXWORKS) && defined(IPCOM_USE_SOCK_COMPAT)
/* #define IPNET_SO_WAKEUP_HOOK */
#endif

/*
 *===========================================================================
 *                        IPCOM_USE_RAM_DISK
 *===========================================================================
 * Controls whether the ipcom initialization function should define and set
 * up a vxWorks RAM disk. This can thus only be used with
 * IPCOM_USE_FILE == IPCOM_FILE_NATIVE
 * and shall not be confused with IPCOM_FILE_IPCOM, which is the IPCOM RAM
 * file system.
 */
#ifdef _WRS_CONFIG_FS_DOSFS
#if IPCOM_USE_FILE == IPCOM_FILE_NATIVE
#define IPCOM_USE_RAM_DISK
#endif
#endif

/*
 *===========================================================================
 *                        IPCOM_RAM_DISK_xx
 *===========================================================================
 * Ram disk block size and number of blocks.
 */
#ifdef IPCOM_USE_RAM_DISK

/* Block size */
#ifndef IPCOM_RAM_DISK_BLOCK_SIZE
# define IPCOM_RAM_DISK_BLOCK_SIZE 512
#endif

/* Number of blocks */
#ifndef IPCOM_RAM_DISK_NO_BLOCK
# ifdef IPSSH
#  define IPCOM_RAM_DISK_NO_BLOCK   1024
# else
#  define IPCOM_RAM_DISK_NO_BLOCK   64
# endif
#endif /* IPCOM_RAM_DISK_NO_BLOCK */

#endif /* #ifdef IPCOM_USE_RAM_DISK */


/*
 *===========================================================================
 *                  IPCOM_FILE_NATIVE_ROOT
 *===========================================================================
 * File system root when using native file system.
 */
#define IPCOM_FILE_NATIVE_ROOT   "/ram/"


/*
 *===========================================================================
 *                  IPCOM_USE_HW_CHECKSUM
 *===========================================================================
 * Define if support for checksumming in hardware should be enabled.
 * It is safe to define this even if the target hardware does not support
 * checksumming in hardware.
 *
 */
#define IPCOM_USE_HW_CHECKSUM

/*
 *===========================================================================
 *                  IPCOM_USE_HW_VLAN_TAGGING
 *===========================================================================
 * Define if hardware supports VLAN tag insertion and stripping.
 * For driver that supports stripping VLAN tag from the received frame,
 * the VLAN tag will be stored in m_blk->mBlkPktHdr.vlan (in host-byte
 * order) and an untagged frame will be sent to the stack. Therefore, this
 * define must be enabled by default so that the stack can inter-operate
 * correctly with those vlan-capable driver. It is safe to define this even
 * if the driver does not support vlan offloading. Hardware vlan capability
 * will be determined when the interface is attached to the MUX.
 */
#ifdef IPNET
#ifdef IPNET_MSP_DISTRIBUTION
#define IPCOM_USE_HW_VLAN_TAGGING
#endif /* IPNET_MSP_DISTRIBUTION */
#endif

/*
 *===========================================================================
 *                  IPCOM_USE_HW_CAPS
 *===========================================================================
 * Define if hardware capabilities should be considered.
 * This is currently defined if hardware checksumming and/or vlan offloading
 * are enabled.
 */
#if defined(IPCOM_USE_HW_CHECKSUM) || defined(IPCOM_USE_HW_VLAN_TAGGING)
#define IPCOM_USE_HW_CAPS
#endif /* IPCOM_USE_HW_CHECKSUM || IPCOM_USE_HW_VLAN_TAGGING */

/*
 *===========================================================================
 *                  IPCOM_USE_JOB_QUEUE
 *===========================================================================
 * Define to make all stack processing be done by as a VxWorks netJob.
 */
#if IP_PORT_VXWORKS >= 67
#define IPCOM_USE_JOB_QUEUE
#endif

#ifdef _WRS_CONFIG_COMPONENT_IPFORWARDER
/*
 *===========================================================================
 *                  IPCOM_FORWARDER_NAE
 *                  IPCOM_FORWARDER_AMP
 *                  IPCOM_FORWARDER_SMP
 *===========================================================================
 * IPCOM_FORWARDER_NAE
 * Define to make a stack for an NAE (Network Acceleration Engine)
 * IPCOM_FORWARDER_AMP
 * Define to make a stack for an AMP forwarder
 * IPCOM_FORWARDER_SMP
 * Define to make a stack for an SMP forwarder
#define IPCOM_FORWARDER_AMP
#define IPCOM_FORWARDER_NAE
#define IPCOM_FORWARDER_SMP
 */

#if defined(_WRS_CONFIG_IPCOM_FORWARDER_AMP)
# define IPCOM_FORWARDER_AMP
#elif defined(_WRS_CONFIG_IPCOM_FORWARDER_NAE)
# define IPCOM_FORWARDER_NAE

#ifdef _WRS_MIPS_N32_ABI
#define IPCOM_USE_STANDARD_MIPC
#define IPCOM_MIPC_PRINTF
#define IPNET_USE_SHOW
#endif

#elif defined(_WRS_CONFIG_IPCOM_FORWARDER_SMP)
# define IPCOM_FORWARDER_SMP
#else
# error Missing forwarder selection, must be one of AMP, NAE or SMP
#endif

#ifdef _WRS_CONFIG_MAX_NAES
#define IPCOM_MAX_NAE _WRS_CONFIG_MAX_NAES
#endif

#ifdef IPCOM_FORWARDER_NAE
#ifdef IPCOM_USE_JOB_QUEUE
#undef IPCOM_USE_JOB_QUEUE
#endif
#endif

/* Defines for the P4080 port */
#define IPCOM_USE_P4080_ORP   	/* Enable Order Restoration */
#define IPCOM_USE_MANY_INPUT_FQ /* Spread traffic over multiple queues */
/* */

#endif /* _WRS_CONFIG_COMPONENT_IPFORWARDER */

#if defined(_WRS_MIPS_N32_ABI) && \
    (defined(_WRS_CONFIG_COMPONENT_IFPROXY) || \
     defined(_WRS_CONFIG_COMPONENT_IPFORWARDER))
#define IPCOM_USE_APPENDED_FWTAG
#define IPCOM_USE_2BYTE_ALIGN_PKT
#endif


#ifdef _WRS_CONFIG_COMPONENT_IPFORWARDER_IPSEC
/*
 *===========================================================================
 *                  IPCOM_USE_FORWARDER_IPSEC
 *===========================================================================
 * Define to enable the IP forwarder IPsec feature
 *
#define IPCOM_USE_FORWARDER_IPSEC
 */
#ifndef IPBASIC
#define IPCOM_USE_FORWARDER_IPSEC
#endif
#endif


/*
 *===========================================================================
 *                  IPCOM_SVCONFIG_CMD
 *===========================================================================
 * Define to compile the svconfig command.
 * The svconfig command is used by the Network Acceleration Platform (NAP) Management OS
 * to configure VLAN stacking.
#define IPCOM_SVCONFIG_CMD
 */

/*
 *===========================================================================
 *                   IPCOM_USE_VXSEM_SCALABLE
 *===========================================================================
 * Set IPCOM_USE_VXSEM_SCALABLE if you want ipcom to use scalable vxWorks
 * semaphores and mutexes.
 */
#if IP_PORT_VXWORKS >= 67 && defined (IPCOM_USE_SMP) && !defined (_WRS_CONFIG_DETERMINISTIC)
#define IPCOM_USE_VXSEM_SCALABLE
#endif

/*
 *===========================================================================
 *                   IPCOM_USE_VXSEM_INLINE
 *===========================================================================
 * Set IPCOM_USE_VXSEM_INLINE if you want ipcom to use inline vxWorks
 * semaphores and mutexes. This option is disabled by default since it
 * increases the text segment size by about 7kb for diab builds.  This
 * option is also incompatible with IPCOM_USE_VXSEM_SCALABLE.
 */
#if 0 && IP_PORT_VXWORKS >= 67 && defined (IPCOM_USE_SMP) && \
      !defined (IPCOM_USE_VXSEM_SCALABLE)
#define IPCOM_USE_VXSEM_INLINE
#endif

/*
 *===========================================================================
 *                   IPCOM_VXSEM_MUTEX_OPTS
 *===========================================================================
 * If scalable or inline VxWorks semaphores and mutexes are used, the inline
 * options used with the mutexes need to be configured.  The default choice
 * below does not provide priority inheritance (SEM_INVERSION_SAFE), and also
 * omits object ID validation, some error checking, and system viewer
 * instrumentation. SEM_DELETE_SAFE is however enabled to allow tasks to be
 * asynchronously killed while doing stack calls.
 * 
 */
#if defined (IPCOM_USE_VXSEM_INLINE) || defined (IPCOM_USE_VXSEM_SCALABLE)
#define IPCOM_VXSEM_MUTEX_OPTS \
    (SEM_DELETE_SAFE | \
     SEM_Q_PRIORITY | \
     SEM_NO_ID_VALIDATE | \
     SEM_NO_ERROR_CHECK | \
     SEM_NO_SYSTEM_VIEWER | \
     SEM_NO_EVENT_SEND)
#endif

/*
 *===========================================================================
 *                   IPCOM_USE_SPINLOCK_ISR_ND
 *===========================================================================
 * Set IPCOM_USE_SPINLOCK_ISR_ND if you want ipcom to use
 * nondeterministic ISR spinlocks.  These spinlocks are typically
 * faster than the standard ISR spinlocks, but do not guarantee fair,
 * deterministic access to a lock in the presence of strong
 * contention.
 */
#if IP_PORT_VXWORKS >= 67 && !defined (_WRS_CONFIG_DETERMINISTIC) && defined(IPCOM_USE_SMP)
#define IPCOM_USE_SPINLOCK_ISR_ND
#endif


/*
 *===========================================================================
 *                   IPCOM_SPINLOCK_BUSY_PERSIST
 *===========================================================================
 * Due to current limitations on which VxWorks kernel functions can be called
 * while holding a VxWorks spinlock, and due to other performance factors,
 * in the SMP build 'Ipcom_spinlock' spinlocks are presently implemented
 * based upon an atomic variable and a VxWorks binary semaphore.  This
 * implementation is likely to change in a future VxWorks release.
 *
 * Note that neither task preemption nor interrupts are locked during the
 * interval when a task either owns or attempts to acquire an Ipcom_spinlock.
 *
 * Define IPCOM_SPINLOCK_BUSY_PERSIST if you want ipcom_spinlock_lock() to
 * busy-wait for a bit when the spinlock is not immediately available,
 * before giving up and taking the VxWorks semaphore underlying
 * the 'Ipcom_spinlock' in the SMP build.  This improves stack performance
 * in most SMP scenarios.
 *
 * There is, however, a potential case in which the busy-wait choice will
 * hurt performance. If the task owning the 'spinlock' is preempted by another
 * task on the same CPU that tries to take the same spinlock, the busy-wait
 * done by the new taker degrades performance (although it does not cause
 * full deadlock since the number of busy-wait loops is bounded).
 *
 * When IPCOM_SPINLOCK_BUSY_PERSIST is defined, its value is the number
 * of busy wait loops for which the caller of ipcom_spinlock_lock()
 * will spin when the spinlock is not available, before giving up and
 * taking the semaphore. See ipcom_spinlock.c for the detailed algorithm.
 *
 * When IPCOM_SPINLOCK_BUSY_PERSIST is not defined, busy waiting is
 * not done.
 *
 * This macro does not affect the uniprocessor build.
 */
#define IPCOM_SPINLOCK_BUSY_PERSIST	(1024)


/*
 *===========================================================================
 *                    IPCOM_VXWORKS_STATS
 *===========================================================================
 * Controls whether statistic collection for the vxWorks ipcom port shall be
 * compiled in.
 */
#ifdef IP_DEBUG
#define IPCOM_VXWORKS_STATS
#endif


/*
 *===========================================================================
 *                    IPCOM_DRV_ETH_STATS
 *===========================================================================
 * Description:   Enable Ethernet driver statistics (drv_stats shell command)
 * Parameters:
 * Returns:
 *
 */
#if defined(IP_DEBUG) && (defined(IPNET) || defined(IPLITE))
#define IPCOM_DRV_ETH_STATS
#endif


/*
 *===========================================================================
 *                    IPCOM_HOST_FROM_LOCALTBL
 *===========================================================================
 * This macro controles whether host info is to be retrieved from the static
 * host database. If IPDNSC is defined, host info is to be searched in the
 * local host database before calling into IPDNSC.
 */
#define IPCOM_HOST_FROM_LOCALTBL


/*
 *===========================================================================
 *                         Stack sizes
 *===========================================================================
 * The stack size is defined as an Ip_u16. This means that the stack
 * definitions below must be updated with caution. Hence the max value for
 * IPCOM_PROC_STACK_MAX is currently 21845 with the IPCOM_STACK_ADJUST macro
 * has been accounted for. IPCOM_STACK_ADJUST can give a times 3 multiplication,
 * and 21845*3 = 65535.
 */
#if !defined(IPCOM_STACK_ADJUST)
# if !defined(CPU)
#  define IPCOM_STACK_ADJUST(x) x               /* User mode builds--stacksize never used */
# elif IP_PORT_VXWORKS < 60
#  define IPCOM_STACK_ADJUST(x) x               /* No need for big stacks in 5.x */
# elif IP_PORT_VXWORKS < 66
#  if _WRS_MIPS_64BIT_CPU
#   define IPCOM_STACK_ADJUST(x) (x * 2)        /* 64-bit CPUs get 2x stacks */
#  else
#   define IPCOM_STACK_ADJUST(x) x              /* Other CPUs get 1x */
#  endif
# else
#  if _WRS_MIPS_64BIT_CPU || defined(_WRS_CONFIG_LP64)
#   define IPCOM_STACK_ADJUST(x) (x * 3)        /* 64-bit on 6.6 and above get 3x */
#  else
#   define IPCOM_STACK_ADJUST(x) ((x * 3) / 2)  /* Other CPUs on 6.6 and above get 1.5x */
#  endif
# endif /* !defined(CPU) */
#endif /* !defined(IPCOM_STACK_ADJUST) */

#define IPCOM_PROC_STACK_MIN      IPCOM_STACK_ADJUST(1024)
#define IPCOM_PROC_STACK_SMALL    IPCOM_STACK_ADJUST(2048)
#define IPCOM_PROC_STACK_DEFAULT  IPCOM_STACK_ADJUST(4096)
#define IPCOM_PROC_STACK_LARGE    IPCOM_STACK_ADJUST(8192)
#define IPCOM_PROC_STACK_MAX      IPCOM_STACK_ADJUST(21845)


/*
 *===========================================================================
 *                         Process priorities
 *===========================================================================
 * IPCOM has seven process priorities where 7 is highest and 1 lowest.
 * Define the corresponding RTOS priorities below:
 * VxWorks 6.x uses different priorities for the nettask, compared to VxWorks
 * 5.x. The best network performance is obtained if Interpeak task priorities
 * are synchronized with the VxWorks priorities.
 * Please note, changing task priority is not officially supported on vxworks
 * 6.x, there may be undesired consequences, such as poor performance.
 */
#if IP_PORT_VXWORKS >= 60
#ifndef IPCOM_PROC_PRIO_1
#define IPCOM_PROC_PRIO_1   254 /* lowest */
#endif
#ifndef IPCOM_PROC_PRIO_2
#define IPCOM_PROC_PRIO_2    90
#endif
#ifndef IPCOM_PROC_PRIO_3
#define IPCOM_PROC_PRIO_3    80
#endif
#ifndef IPCOM_PROC_PRIO_4
#define IPCOM_PROC_PRIO_4    50
#endif
#ifndef IPCOM_PROC_PRIO_5
#define IPCOM_PROC_PRIO_5    40
#endif
#ifndef IPCOM_PROC_PRIO_6
#define IPCOM_PROC_PRIO_6    30
#endif
#ifndef IPCOM_PROC_PRIO_7
#define IPCOM_PROC_PRIO_7    20 /* highest */
#endif
#else
/* VxWorks 5.4 and 5.5 */
#define IPCOM_PROC_PRIO_1   254 /* lowest */
#define IPCOM_PROC_PRIO_2    90
#define IPCOM_PROC_PRIO_3    80
#define IPCOM_PROC_PRIO_4    70
#define IPCOM_PROC_PRIO_5    60
#define IPCOM_PROC_PRIO_6    50
#define IPCOM_PROC_PRIO_7    40 /* highest */
#endif

#define IPCOM_PROC_PRIO_BACKGROUND    255  /* EGD daemon (background proc) */


/*
 *===========================================================================
 *                        IPC
 *===========================================================================
 * IPSSH process names can be up to 51 characters.
 */
#define IPCOM_IPC_MAX_NAME    64

/*
 *  *===========================================================================
 *                       IPCOM_CCIVALIDATE_TEST_
 *   ===========================================================================
 *   Includes the command to include cci library validation tests thru the
 *    ipcom shell.
 *    #define IPCOM_CCIVALIDATE_TEST
 *
 */

/*
 *  *===========================================================================
 *                       IPCOM_CCIVALIDATE_TEST_
 *   ===========================================================================
 *   Includes the command to add cci provider performance benchmark cmd to the
 *    ipcom shell.
 *    #define IPCOM_CCIPERFORMANCE_TEST
 *
 */


/*
 ****************************************************************************
 * 3                    SYSTEM VIEWER
 ****************************************************************************
 */

/*
 *===========================================================================
 *                      IPCOM_WV_INSTRUMENTATION
 *===========================================================================
 * To build the stack without system viewer instrumentation, use OPT=-fr or
 * OPT=-inet6_fr on the Make command line; or add -D_FREE_VERSION to
 * the compiler flags; or undefine IPCOM_WV_INSTRUMENTATION below.
 *
 * For library builds we don't define INCLUDE_WINDVIEW and INCLUDE_WVNETD.
 * Those will be defined in VIP projects or BSP config files.
 */

#if IP_PORT_VXWORKS >= 65
# ifndef _WRS_CONFIG_SV_INSTRUMENTATION
#  ifndef _FREE_VERSION
#   define _FREE_VERSION
#  endif
# endif
# ifndef _FREE_VERSION
# ifdef _WRS_CONFIG_SYSTEMVIEWER
#  define IPCOM_WV_INSTRUMENTATION
# endif
# endif
# ifdef IPCOM_WV_INSTRUMENTATION
#  if defined(WRS_IPNET) || defined(IPBSPBUILD)
#   ifndef INCLUDE_WVNETD
#    define INCLUDE_WVNETD
#   endif
#  endif  /* defined(WRS_IPNET) || defined(IPBSPBUILD) */
# endif  /* #ifdef IPCOM_WV_INSTRUMENTATION */
#endif /* IP_PORT_VXWORKS >= 65 */

/*
 *===========================================================================
 *                    IPCOM_WV_INSTRUMENTATION_TEST
 *===========================================================================
 * Define to include system viewer test command.
#define IPCOM_WV_INSTRUMENTATION_TEST
 */

#if defined(IPCOM_WV_INSTRUMENTATION_TEST) && !defined(IPCOM_FILE_NATIVE)
#error 'IPCOM_WV_INSTRUMENTATION_TEST requires native file system'
#endif


/* Increase RAM disk size */
#if defined(IPCOM_WV_INSTRUMENTATION_TEST) && defined(IPCOM_USE_RAM_DISK)
# ifdef IPCOM_RAM_DISK_NO_BLOCK
#  undef IPCOM_RAM_DISK_NO_BLOCK
# endif
# define IPCOM_RAM_DISK_NO_BLOCK 1024
#endif


/*
 ****************************************************************************
 * 4                    IPCOM DRIVER CONFIGURATION
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    IPCOM_VXWORKS_DRV_NULLPOOL
 *===========================================================================
 * Support use of nullpool.
 */
#if IP_PORT_VXWORKS >= 65
#define IPCOM_VXWORKS_DRV_NULLPOOL
#endif

/*
 *===========================================================================
 *                    IPCOM_USE_MUX2
 *===========================================================================
 * Use MUX2 interface.
 */
#if IP_PORT_VXWORKS >= 67
#define IPCOM_USE_MUX2
#endif


/*
 *===========================================================================
 *                    IPCOM_VXWORKS_DRV_ETH_PROMISCUOUS
 *===========================================================================
 * Set driver in promiscuous mode (for Ethernet chips who have problems with
 * programming multicast groups).
#define IPCOM_VXWORKS_DRV_ETH_PROMISCUOUS
 */


/*
 *===========================================================================
 *                    IPCOM_USE_SYSVAR_EXT
 *===========================================================================
 * Used to set sets an array of values for interface-specific parameters.
 */
#define IPCOM_USE_SYSVAR_EXT


/*
 *===========================================================================
 *                    IPCOM_USE_VXSHELL_CMD
 *===========================================================================
 * Include vxshell command in IPCOM shell.
 */
#if IPCOM_USE_SHELL == IPCOM_SHELL_IPCOM && IP_PORT_VXWORKS >= 65
#define IPCOM_USE_VXSHELL_CMD
#endif


/*
 *===========================================================================
 *                    IPCOM_VXWORKS_USE_MUX_L2
 *===========================================================================
 * Define to enable VxWorks MUX-L2 IEEE 802.1Q VLAN support.
 *
 * #define IPCOM_VXWORKS_USE_MUX_L2
 */

#ifdef REMOVE_THIS_IFDEF_WHEN_SUPPORTING_IPBRIDGE
/*
 *===========================================================================
 *                    INCLUDE_IPFIREWALL_SUPPORT
 *===========================================================================
 * Define to enable Firewall support in the bridge.
 *
 */
#ifdef _WRS_CONFIG_COMPONENT_IPFIREWALL_SUPPORT
#define INCLUDE_IPFIREWALL_SUPPORT
#define IPCOM_STORE_PHYSICAL_IF
#define IPFIREWALL_PHYSICAL_IF_SUPPORT
#endif

/*
 *===========================================================================
 *                    INCLUDE_IPBRIDGE_VLAN_SUPPORT
 *===========================================================================
 * Define to enable 802.1Q Bridge support in the bridge.
 *
 */
#ifdef _WRS_CONFIG_COMPONENT_BRIDGE_VLAN_SUPPORT
#define INCLUDE_IPBRIDGE_VLAN_SUPPORT
#endif

/*
 *===========================================================================
 *                    IPBRIDGE_FILTERING_DB_SIZE
 *===========================================================================
 * Define to specify the maximum size of the bridge filtering database.
 *
 */
#ifdef _WRS_CONFIG_BRIDGE_STATS
#define IPBRIDGE_USE_STATS
#endif

/*
 *===========================================================================
 *                    IPBRIDGE_FILTERING_DB_SIZE
 *===========================================================================
 * Define to specify the maximum size of the bridge filtering database.
 *
 */
#ifdef _WRS_CONFIG_BRIDGE_FILTERING_DATABASE_SIZE
#define IPBRIDGE_FILTERING_DB_SIZE _WRS_CONFIG_BRIDGE_FILTERING_DATABASE_SIZE
#endif

/*
 *===========================================================================
 *                    IPBRIDGE_MAX_PORTS
 *===========================================================================
 * Define to specify the maximum number of allowed bridge ports.
 *
 */
#ifdef _WRS_CONFIG_BRIDGE_MAX_PORTS
#define IPBRIDGE_MAX_PORTS _WRS_CONFIG_BRIDGE_MAX_PORTS
#endif
#endif

/*
 *===========================================================================
 *                    IPCOM_ZEROCOPY
 *===========================================================================
 * Include the ZeroCopy API by default to enable it in GPP.
 */
#ifndef WRS_IPLITE
#ifndef IPCOM_ZEROCOPY
#define IPCOM_ZEROCOPY
#endif
#endif

/*
 *===========================================================================
 *                    IPCOM_SIMPLE_MEM_SIZE
 *===========================================================================
 * Define to specify the size of simple memory
 *
 */
#ifdef _WRS_CONFIG_IPCOM_SIMPLE_MEM_SIZE
#define IPCOM_SIMPLE_MEM_SIZE _WRS_CONFIG_IPCOM_SIMPLE_MEM_SIZE
#endif

/*
 *===========================================================================
 *                    IPCOM_SPINLOCK_USE_MUTEX
 *===========================================================================
 * Define to use mutex for ipcom_spinlock, ipcom_spinlock is using binary
 * sempahore in order to increase performance, binary sempahore  does not 
 * support priority inversion, if someone wants to support priority inversion
 * please enable this marco, a mutual-exclusion semaphore will be created
 * instead, and it supports priority inversion, this will make the 
 * lock/unlock operation for spinlocks more expensive and performance will
 * be decreased.
 */
#if defined(IPCOM_USE_SMP) && defined(_WRS_CONFIG_DETERMINISTIC)
/* #define IPCOM_SPINLOCK_USE_MUTEX */
#endif


#ifdef __cplusplus
}
#endif

#endif


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
