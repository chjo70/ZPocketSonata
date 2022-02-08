# Makefile generated by the project manager
#


# GENERATED: Sun Jan 23 15:48:53 +0900 2022
# DO NOT EDIT - file is regenerated whenever the project changes


## core information

ifeq ($(wildcard Makefile.mk),)
PRJ_DIR        = ..
else
PRJ_DIR        = .
endif
PRJ_FILE       = VBootShell.wpj
PRJ_FULL_PATH  = D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VBootShell
PRJ_TYPE       = vxWorks
PRJ_OBJS       = usrAppInit.o usrRtpAppInit.o prjConfig.o linkSyms.o BootShellMain.o asp.o balloc.o base64.o cgi.o default.o ejlex.o ejparse.o emfdb.o form.o h.o handler.o main.o md5c.o mime.o misc.o mocana_ssl.o page.o ringq.o rom.o security.o sock.o sockGen.o strdup.o strncasecmp.o sym.o uemf.o um.o umui.o url.o value.o webrom.o webs.o websda.o websuemf.o BootShell.o ManSbc.o FileTar.o
USER_OBJS      = 
PRJ_MAKEFILE   = $(PRJ_DIR)/Makefile.mk
BOOT_OBJS      =  $(BOOT_EXTRA)
BUILD_SPEC     = default
BSP_DIR        = D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VBootShell/hmt_t2080vpx3u_1_0_0_0
VSB_DIR        = D:/VirtualBoxVMs/Git/ZPocketSonataT/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild
VXBUILD        = SMP
OPT            = -inet6



## set searching directories for dependencies

vpath %.c $(BSP_DIR)
vpath %.cpp $(BSP_DIR)
vpath %.cxx $(BSP_DIR)
vpath %.s $(BSP_DIR)


## build-configuration info

CPU            = PPCE6500
TOOL           = gnu
TOOL_FAMILY    = gnu
TOOL_VERSION   = gnu_4_8_1_8
_CC_VERSION    = gnu_4_8_1_10
ifeq ($(BUILD_SPEC),default)
DEFAULT_RULE   = uVxWorks
endif


## Memory adresses variables

RAM_LOW_ADRS = 01000000
RAM_HIGH_ADRS = 80000000
LOCAL_MEM_LOCAL_ADRS = KERNEL_SYS_MEM_RGN_BASE
DATA_SEG_ALIGN = 1
KERNEL_LOAD_ADRS = 01000000

## component-configuration info

COMPONENTS = DRV_BUS_FDT_ROOT \
	DRV_BUS_FDT_SIMPLE \
	DRV_CORENET_L2_CACHE \
	DRV_CORENET_L3_CACHE \
	DRV_FPGA_FDT_FSL_QORIQ \
	DRV_FSL_LAW \
	DRV_FSL_QIXIS \
	DRV_INTCTLR_FDT_MPIC \
	DRV_NEXUS_GENERIC \
	DRV_QORIQDTSEC_MDIO \
	DRV_QORIQMEMAC_MDIO \
	DRV_QORIQ_CLK \
	DRV_RESOURCE_QORIQBMAN \
	DRV_RESOURCE_QORIQFMAN \
	DRV_RESOURCE_QORIQQMAN \
	DRV_SIO_FDT_NS16550 \
	DRV_TIMER_FSL_BOOKE \
	DRV_TIMER_OPENPIC \
	DRV_VXBEND_QORIQMEMAC \
	DRV_VXB_NORFLASH \
	DRV_VXB_NORFLASH_CMDSET_AMD \
	INCLUDE_ADR_SPACE_LIB \
	INCLUDE_ADR_SPACE_SHELL_CMD \
	INCLUDE_ADR_SPACE_SHOW \
	INCLUDE_AIM_CACHE \
	INCLUDE_ALTIVEC \
	INCLUDE_ALTIVEC_MREGS \
	INCLUDE_ALTIVEC_SHOW \
	INCLUDE_ANALYSIS_AGENT \
	INCLUDE_ANALYSIS_AUX_CLOCK \
	INCLUDE_ANALYSIS_DEBUG_SUPPORT \
	INCLUDE_ANALYSIS_SCRIPT \
	INCLUDE_ANSI_ABORT \
	INCLUDE_ANSI_ABS \
	INCLUDE_ANSI_ASSERT \
	INCLUDE_ANSI_ATOF \
	INCLUDE_ANSI_BSEARCH \
	INCLUDE_ANSI_CTYPE \
	INCLUDE_ANSI_LOCALE \
	INCLUDE_ANSI_LONGJMP \
	INCLUDE_ANSI_MATH \
	INCLUDE_ANSI_MEMCHR \
	INCLUDE_ANSI_MEMCMP \
	INCLUDE_ANSI_MEMCPY \
	INCLUDE_ANSI_MEMMOVE \
	INCLUDE_ANSI_MEMSET \
	INCLUDE_ANSI_STDIO \
	INCLUDE_ANSI_STDIO_EXTRA \
	INCLUDE_ANSI_STDLIB \
	INCLUDE_ANSI_STDLIB_NUMBERS \
	INCLUDE_ANSI_STRCASECMP \
	INCLUDE_ANSI_STRCAT \
	INCLUDE_ANSI_STRCMP \
	INCLUDE_ANSI_STRCPY \
	INCLUDE_ANSI_STRDUP \
	INCLUDE_ANSI_STRERROR \
	INCLUDE_ANSI_STRING \
	INCLUDE_ANSI_STRLCAT \
	INCLUDE_ANSI_STRLCPY \
	INCLUDE_ANSI_STRLEN \
	INCLUDE_ANSI_STRNCASECMP \
	INCLUDE_ANSI_STRNCAT \
	INCLUDE_ANSI_STRNCMP \
	INCLUDE_ANSI_STRNCPY \
	INCLUDE_ANSI_STRTOD \
	INCLUDE_ANSI_TIME \
	INCLUDE_APPL_LOG_UTIL \
	INCLUDE_ARPAINETLIB \
	INCLUDE_ATOMIC_OPERATORS \
	INCLUDE_AUX_CLK \
	INCLUDE_AVL_TREES \
	INCLUDE_AVL_UINT_TREES \
	INCLUDE_BANNER \
	INCLUDE_BASE_KERNEL \
	INCLUDE_BLIB \
	INCLUDE_BLIB_ARCH \
	INCLUDE_BMPLIB \
	INCLUDE_BOARD_INIT \
	INCLUDE_BOARD_LIB_INIT \
	INCLUDE_BOOTAPP_GENERIC_NVRAM \
	INCLUDE_BOOTAPP_NVRAM_SUPPORT \
	INCLUDE_BOOT_APP \
	INCLUDE_BOOT_LINE_INIT \
	INCLUDE_BSP_MACROS \
	INCLUDE_CACHE_ENABLE \
	INCLUDE_CACHE_SUPPORT \
	INCLUDE_CAFE_EP_AGGREGATOR \
	INCLUDE_CAFE_EP_AUX_CLOCK \
	INCLUDE_CAFE_EP_CAFE_NAMESPACE \
	INCLUDE_CAFE_EP_ELOG \
	INCLUDE_CAFE_EP_PERFORMANCE_PROFILER \
	INCLUDE_CAFE_EP_PRINT \
	INCLUDE_CAFE_EP_REALTIME \
	INCLUDE_CAFE_EP_STREAM_READER \
	INCLUDE_CAFE_EP_STREAM_WRITER \
	INCLUDE_CAFE_EP_SYSINFO \
	INCLUDE_CAFE_EP_SYS_CLOCK \
	INCLUDE_CAFE_EP_TCF_UPLOAD \
	INCLUDE_CAFE_EP_TIMER \
	INCLUDE_CAFE_EP_TIMESTAMP_NORMALIZER \
	INCLUDE_CAFE_EP_VXWORKS \
	INCLUDE_CAFE_EP_VXWORKS_POLLING \
	INCLUDE_CAFE_PRINT \
	INCLUDE_CAFE_RTP \
	INCLUDE_CAFE_TCF_SERVICE \
	INCLUDE_CAFE_VX_TIMESTAMP \
	INCLUDE_CHECKSUM \
	INCLUDE_CLASS_LIB \
	INCLUDE_CLASS_LIST \
	INCLUDE_CLASS_SHOW \
	INCLUDE_CONDVAR \
	INCLUDE_CONDVAR_OPEN \
	INCLUDE_CONDVAR_SHOW \
	INCLUDE_COPROCESSOR \
	INCLUDE_COPROCESSOR_SHOW \
	INCLUDE_CORE_NFS_CLIENT \
	INCLUDE_CPC \
	INCLUDE_CPLUS \
	INCLUDE_CPLUS_DEMANGLER \
	INCLUDE_CPLUS_IOSTREAMS \
	INCLUDE_CPLUS_LANG \
	INCLUDE_CPU_INIT \
	INCLUDE_CTORS_DTORS \
	INCLUDE_DATACOLLECTOR \
	INCLUDE_DEBUG \
	INCLUDE_DEBUG_AGENT \
	INCLUDE_DEBUG_AGENT_BANNER \
	INCLUDE_DEBUG_AGENT_HOSTFS \
	INCLUDE_DEBUG_KPRINTF \
	INCLUDE_DEBUG_SHELL_CMD \
	INCLUDE_DEFERRED_INTERRUPT_ENABLE \
	INCLUDE_DEVCLK_SYS \
	INCLUDE_DEVICE_MANAGER \
	INCLUDE_DIAB_INTRINSICS \
	INCLUDE_DISK_UTIL \
	INCLUDE_DISK_UTIL_SHELL_CMD \
	INCLUDE_DLL \
	INCLUDE_DMA_SYS \
	INCLUDE_DOSFS \
	INCLUDE_DOSFS_CHKDSK \
	INCLUDE_DOSFS_DIR_FIXED \
	INCLUDE_DOSFS_DIR_VFAT \
	INCLUDE_DOSFS_FAT \
	INCLUDE_DOSFS_FMT \
	INCLUDE_DOSFS_MAIN \
	INCLUDE_DOSFS_PRTMSG_LEVEL \
	INCLUDE_DOSFS_SHOW \
	INCLUDE_DOSFS_VOL_BIO_BUFFER_SIZE \
	INCLUDE_EDR_DEFAULT_POLICY \
	INCLUDE_EDR_POLICY_HOOKS \
	INCLUDE_EDR_STUB \
	INCLUDE_EDR_SYSDBG_FLAG \
	INCLUDE_END \
	INCLUDE_END_COMMON \
	INCLUDE_END_ETHER_HDR \
	INCLUDE_ENV_VARS \
	INCLUDE_ERF \
	INCLUDE_ETHERNET \
	INCLUDE_EVENTPOINT \
	INCLUDE_EVENTPOINT_STUB \
	INCLUDE_EXC_HANDLING \
	INCLUDE_EXC_SHOW \
	INCLUDE_EXC_SIGNALS \
	INCLUDE_EXC_TASK \
	INCLUDE_FDT_LIB \
	INCLUDE_FLOATING_POINT \
	INCLUDE_FORMATTED_IO \
	INCLUDE_FORMATTED_OUT_BASIC \
	INCLUDE_FP_TYPE \
	INCLUDE_FSL_SGMII_PHY \
	INCLUDE_FS_EVENT_UTIL \
	INCLUDE_FS_MONITOR \
	INCLUDE_FTP \
	INCLUDE_GENERICPHY \
	INCLUDE_GENERIC_MMD_PHY \
	INCLUDE_GETADDRINFO_SYSCTL \
	INCLUDE_GETOPT \
	INCLUDE_GETSERVBYNAME \
	INCLUDE_GETSERVBYPORT \
	INCLUDE_GNU_INTRINSICS \
	INCLUDE_HANDLE_SHOW \
	INCLUDE_HASH \
	INCLUDE_HOOKS \
	INCLUDE_HOOK_SHOW \
	INCLUDE_HOST_TBL \
	INCLUDE_HOST_TBL_SYSCTL \
	INCLUDE_HW_FP \
	INCLUDE_HW_FP_MREGS \
	INCLUDE_HW_FP_SHOW \
	INCLUDE_IDLE_TASKS \
	INCLUDE_INETLIB \
	INCLUDE_INT_LIB_INIT \
	INCLUDE_IO_BASIC \
	INCLUDE_IO_FILE_SYSTEM \
	INCLUDE_IO_MISC \
	INCLUDE_IO_POSIX \
	INCLUDE_IO_REMOVABLE \
	INCLUDE_IO_RTP \
	INCLUDE_IO_SYSTEM \
	INCLUDE_IPATTACH \
	INCLUDE_IPCOM \
	INCLUDE_IPCOM_SHELL_CMD \
	INCLUDE_IPCOM_USE_ETHERNET \
	INCLUDE_IPCOM_USE_INET \
	INCLUDE_IPCOM_USE_INET6 \
	INCLUDE_IPCOM_USR \
	INCLUDE_IPNET \
	INCLUDE_IPNET6_USE_MCAST_ROUTING \
	INCLUDE_IPNET_IFCONFIG_1 \
	INCLUDE_IPNET_LOOPBACK_CONFIG \
	INCLUDE_IPNET_SOCKET \
	INCLUDE_IPNET_SYSCTL \
	INCLUDE_IPNET_USE_LOOPBACK \
	INCLUDE_IPNET_USE_MCAST_ROUTING \
	INCLUDE_IPNET_USE_NETLINKSOCK \
	INCLUDE_IPNET_USE_ROUTESOCK \
	INCLUDE_IPNET_USE_SOCK_COMPAT \
	INCLUDE_IPNET_USE_VLAN \
	INCLUDE_IPPING_CMD \
	INCLUDE_IPRADVD \
	INCLUDE_IPTCP \
	INCLUDE_IPV4 \
	INCLUDE_IPV6 \
	INCLUDE_IPWRAP_GETADDRINFO \
	INCLUDE_IPWRAP_GETIFADDRS \
	INCLUDE_IPWRAP_GETSERVBYNAME \
	INCLUDE_IPWRAP_GETSERVBYPORT \
	INCLUDE_IPWRAP_INETLIB \
	INCLUDE_IPWRAP_IPPROTO \
	INCLUDE_IPWRAP_PING \
	INCLUDE_ISR_DEFER \
	INCLUDE_ISR_HANDLER_INIT \
	INCLUDE_ISR_OBJECTS \
	INCLUDE_JOB_DEFER \
	INCLUDE_JOB_QUEUE \
	INCLUDE_JOB_TASK \
	INCLUDE_KERNEL \
	INCLUDE_KERNEL_ARCH \
	INCLUDE_KERNEL_COMMON_HEAP \
	INCLUDE_KERNEL_PROXIMITY_HEAP \
	INCLUDE_LINKBUFPOOL \
	INCLUDE_LOADER \
	INCLUDE_LOADER_CODE \
	INCLUDE_LOADER_HOOKS \
	INCLUDE_LOGGING \
	INCLUDE_LSTLIB \
	INCLUDE_MBUF_UTIL1 \
	INCLUDE_MEMORY_CONFIG \
	INCLUDE_MEM_DESC \
	INCLUDE_MEM_MGR_BASIC \
	INCLUDE_MEM_MGR_FULL \
	INCLUDE_MEM_MGR_INFO \
	INCLUDE_MEM_RTP \
	INCLUDE_MEM_SHOW \
	INCLUDE_MIB2_IF \
	INCLUDE_MII_FDT_SYS \
	INCLUDE_MII_MONITOR_TASK \
	INCLUDE_MII_SYS \
	INCLUDE_MMAP \
	INCLUDE_MMU_ARCH_COMMON_ALIB \
	INCLUDE_MMU_BASIC \
	INCLUDE_MMU_GLOBAL_MAP \
	INCLUDE_MODULE_MANAGER \
	INCLUDE_MODULE_SHELL_CMD \
	INCLUDE_MSG_Q \
	INCLUDE_MSG_Q_CREATE_DELETE \
	INCLUDE_MSG_Q_EVENTS \
	INCLUDE_MSG_Q_INFO \
	INCLUDE_MSG_Q_OPEN \
	INCLUDE_MSG_Q_SHOW \
	INCLUDE_MTD \
	INCLUDE_MTD_VXBFLASH \
	INCLUDE_MUX \
	INCLUDE_MUX2 \
	INCLUDE_MUX2_OVER_END \
	INCLUDE_MUX_COMMON \
	INCLUDE_NETBUFLIB \
	INCLUDE_NETBUFPOOL \
	INCLUDE_NETMASK_GET \
	INCLUDE_NETWORK \
	INCLUDE_NET_BOOT \
	INCLUDE_NET_DAEMON \
	INCLUDE_NET_DRV \
	INCLUDE_NET_HOST_SETUP \
	INCLUDE_NET_REM_IO \
	INCLUDE_NET_SYSCTL \
	INCLUDE_NFS2_CLIENT \
	INCLUDE_NFS3_CLIENT \
	INCLUDE_NFS_CLIENT_ALL \
	INCLUDE_NFS_DEBUG \
	INCLUDE_NFS_MOUNT_ALL \
	INCLUDE_NVRAM_NULL \
	INCLUDE_OBJECT_SHOW \
	INCLUDE_OBJ_INFO \
	INCLUDE_OBJ_LIB \
	INCLUDE_OBJ_LIB_ARCH \
	INCLUDE_OBJ_OPEN \
	INCLUDE_OBJ_OWNERSHIP \
	INCLUDE_OFFSET_SYMBOLS \
	INCLUDE_OSM \
	INCLUDE_PG_MGR_BASIC \
	INCLUDE_PG_MGR_LIB \
	INCLUDE_PG_MGR_SHOW \
	INCLUDE_PG_POOL_LIB \
	INCLUDE_PG_POOL_PHYS_LIB \
	INCLUDE_PG_POOL_SHOW \
	INCLUDE_PG_POOL_VIRT_LIB \
	INCLUDE_PING \
	INCLUDE_PIPES \
	INCLUDE_PMAP_LIB \
	INCLUDE_POOL \
	INCLUDE_POSIX_CLOCKS \
	INCLUDE_POSIX_DIRLIB \
	INCLUDE_POSIX_FS \
	INCLUDE_POSIX_FTRUNC \
	INCLUDE_POSIX_PTHREADS \
	INCLUDE_POSIX_SCHED \
	INCLUDE_POSIX_SEM \
	INCLUDE_POSIX_SEM_SHOW \
	INCLUDE_POSIX_TIMERS \
	INCLUDE_POSIX_TIMER_SHOW \
	INCLUDE_POSIX_UMASK \
	INCLUDE_POSIX_USER_GROUP \
	INCLUDE_PROTECT_TASK_STACK \
	INCLUDE_PTYDRV \
	INCLUDE_Q_FIFO \
	INCLUDE_Q_PRI_BMAP \
	INCLUDE_Q_PRI_DELTA \
	INCLUDE_Q_PRI_LIST \
	INCLUDE_RANDOM_NUM_GEN \
	INCLUDE_RAWFS \
	INCLUDE_RBUFF \
	INCLUDE_RBUFF_SHOW \
	INCLUDE_REBOOT_HOOKS \
	INCLUDE_REMLIB \
	INCLUDE_REMLIB_SYSCTL \
	INCLUDE_RNG_BUF \
	INCLUDE_ROMFS \
	INCLUDE_ROMFS_DRV \
	INCLUDE_RPC \
	INCLUDE_RTP \
	INCLUDE_RTP_APPL_INIT_BOOTLINE \
	INCLUDE_RTP_APPL_INIT_CMD_SHELL_SCRIPT \
	INCLUDE_RTP_APPL_USER \
	INCLUDE_RTP_ARCH \
	INCLUDE_RTP_DEBUG \
	INCLUDE_RTP_DEBUG_COMMAND \
	INCLUDE_RTP_HOOKS \
	INCLUDE_RTP_SHELL_C \
	INCLUDE_RTP_SHELL_CMD \
	INCLUDE_RTP_SHOW \
	INCLUDE_RTP_SHOW_SHELL_CMD \
	INCLUDE_RTP_SIGNALS \
	INCLUDE_RTP_SYMBOL_TABLE \
	INCLUDE_SC_CONDVAR \
	INCLUDE_SC_IOS \
	INCLUDE_SC_KERNEL \
	INCLUDE_SC_MMAN \
	INCLUDE_SC_PIPE \
	INCLUDE_SC_POSIX \
	INCLUDE_SC_RTP_LIMITS \
	INCLUDE_SC_SD \
	INCLUDE_SC_SEM_EXCHANGE \
	INCLUDE_SC_SEM_READ_WRITE \
	INCLUDE_SC_SHL \
	INCLUDE_SC_SOCKLIB \
	INCLUDE_SC_SYSCTL \
	INCLUDE_SEC_HASH_MD5 \
	INCLUDE_SEC_HASH_MD5_OPENSSL \
	INCLUDE_SEC_HASH_SHA1 \
	INCLUDE_SEC_HASH_SHA1_OPENSSL \
	INCLUDE_SEC_HASH_SHA256 \
	INCLUDE_SEC_HASH_SHA256_OPENSSL \
	INCLUDE_SELECT \
	INCLUDE_SELECT_SUPPORT \
	INCLUDE_SEM_BINARY \
	INCLUDE_SEM_BINARY_CREATE \
	INCLUDE_SEM_COUNTING \
	INCLUDE_SEM_COUNTING_CREATE \
	INCLUDE_SEM_DELETE \
	INCLUDE_SEM_EVENTS \
	INCLUDE_SEM_EXCHANGE \
	INCLUDE_SEM_INFO \
	INCLUDE_SEM_LIB \
	INCLUDE_SEM_MUTEX \
	INCLUDE_SEM_MUTEX_CREATE \
	INCLUDE_SEM_OPEN \
	INCLUDE_SEM_READ_WRITE \
	INCLUDE_SEM_READ_WRITE_CREATE \
	INCLUDE_SEM_SHOW \
	INCLUDE_SHARED_DATA \
	INCLUDE_SHARED_DATA_SHOW \
	INCLUDE_SHARED_DATA_SHOW_SHELL_CMD \
	INCLUDE_SHELL \
	INCLUDE_SHELL_BANNER \
	INCLUDE_SHELL_CORE \
	INCLUDE_SHELL_EMACS_MODE \
	INCLUDE_SHELL_INTERP_C \
	INCLUDE_SHELL_INTERP_CMD \
	INCLUDE_SHELL_VI_MODE \
	INCLUDE_SHL \
	INCLUDE_SHL_SHELL_CMD \
	INCLUDE_SHL_SHOW \
	INCLUDE_SHOW_ROUTINES \
	INCLUDE_SIGEVENT \
	INCLUDE_SIGNALS \
	INCLUDE_SIGNAL_ARCH \
	INCLUDE_SIO \
	INCLUDE_SLL \
	INCLUDE_SMP_INIT \
	INCLUDE_SMP_SCHED_SMT_POLICY \
	INCLUDE_SOCKLIB \
	INCLUDE_SPINLOCK \
	INCLUDE_SPINLOCK_ISR_ND \
	INCLUDE_STACKTRACE \
	INCLUDE_STACKTRACE_MODULE \
	INCLUDE_STACKTRACE_SHD \
	INCLUDE_STANDALONE_SYM_TBL \
	INCLUDE_STARTUP_SCRIPT \
	INCLUDE_STAT_SYM_TBL \
	INCLUDE_STDIO \
	INCLUDE_STDIO_SHOW \
	INCLUDE_STOP_MODE_AGENT \
	INCLUDE_STOP_MODE_AGENT_BANNER \
	INCLUDE_STOP_MODE_AGENT_END \
	INCLUDE_SV_DATACOLLECTOR \
	INCLUDE_SW_RANDOM_NUM_GEN \
	INCLUDE_SYM_SHELL_CMD \
	INCLUDE_SYM_TBL \
	INCLUDE_SYM_TBL_INIT \
	INCLUDE_SYM_TBL_SHOW \
	INCLUDE_SYSCALL_HOOKS \
	INCLUDE_SYSCLK_INIT \
	INCLUDE_SYSCTL \
	INCLUDE_SYSCTL_HW \
	INCLUDE_SYSDBG_FLAG \
	INCLUDE_SYSLOG \
	INCLUDE_SYSTEMVIEWER_AGENT \
	INCLUDE_SYS_START \
	INCLUDE_SYS_TIMESTAMP \
	INCLUDE_TASK_CREATE_DELETE \
	INCLUDE_TASK_CREATE_HOOKS \
	INCLUDE_TASK_HOOKS \
	INCLUDE_TASK_HOOKS_SHOW \
	INCLUDE_TASK_INFO \
	INCLUDE_TASK_LIST \
	INCLUDE_TASK_OPEN \
	INCLUDE_TASK_RESTART \
	INCLUDE_TASK_SHELL_CMD \
	INCLUDE_TASK_SHOW \
	INCLUDE_TASK_STACK_ALLOC \
	INCLUDE_TASK_STACK_NO_EXEC \
	INCLUDE_TASK_SWAP_HOOKS \
	INCLUDE_TASK_SWITCH_HOOKS \
	INCLUDE_TASK_TOOLS_UTIL \
	INCLUDE_TFFS \
	INCLUDE_TFFS_MOUNT \
	INCLUDE_TFFS_SHOW \
	INCLUDE_TIMER_OPEN \
	INCLUDE_TIMER_SYS \
	INCLUDE_TIMESTAMP \
	INCLUDE_TIMEX \
	INCLUDE_TIP \
	INCLUDE_TIP_CMD \
	INCLUDE_TLS \
	INCLUDE_TLS_LOADER_SUPPORT \
	INCLUDE_TL_FTL \
	INCLUDE_TRIGGERING \
	INCLUDE_TRIGGER_SHOW \
	INCLUDE_TRIG_DATACOLLECTOR \
	INCLUDE_TTY_DEV \
	INCLUDE_TYLIB \
	INCLUDE_UNLOADER \
	INCLUDE_UNLOADER_SHELL_CMD \
	INCLUDE_USER_APPL \
	INCLUDE_USER_RESERVED_MEMORY \
	INCLUDE_USE_NATIVE_SHELL \
	INCLUDE_VM_INVTBL \
	INCLUDE_VM_RTP \
	INCLUDE_VM_SHOW \
	INCLUDE_VM_SHOW_SHELL_CMD \
	INCLUDE_VXBUS \
	INCLUDE_VXBUS_PARAMS \
	INCLUDE_VXB_AUX_CLK \
	INCLUDE_VXB_SYS_CLK \
	INCLUDE_VXB_TIMESTAMP \
	INCLUDE_VXCPULIB \
	INCLUDE_VXDBG \
	INCLUDE_VXDBG_CPU_CONTROL \
	INCLUDE_VXDBG_HOOK \
	INCLUDE_VXDBG_MODULE \
	INCLUDE_VXDBG_RTP \
	INCLUDE_VXDBG_RUNCTRL \
	INCLUDE_VXEVENTS \
	INCLUDE_VXIPI \
	INCLUDE_VXMEMPROBE_INIT \
	INCLUDE_VXMUX_MBLK \
	INCLUDE_VXMUX_NULLBUFPOOL \
	INCLUDE_VX_NATIVE_SCHEDULER \
	INCLUDE_VX_TRADITIONAL_SCHEDULER \
	INCLUDE_WATCHDOGS \
	INCLUDE_WATCHDOGS_CREATE_DELETE \
	INCLUDE_WATCHDOGS_SHOW \
	INCLUDE_WINDVIEW \
	INCLUDE_WINDVIEW_CLASS \
	INCLUDE_WINDVIEW_MODULE_CLASS \
	INCLUDE_WVUPLOAD_FILE \
	INCLUDE_XBD \
	INCLUDE_XDR

SUBPROJECTS = BSP 

SUBPROJECT_DIR_BSP = $(BSP_DIR)
MANAGED_LIBS = librqdef.a librqfept.a librqsmt.a libspl.a libsplDbg.a
COMPONENT_LIBS = librqsmt.a libspl.a

PROJECT_LINK_SYMDEFS = 


include $(WIND_KRNL_MK)/defs.project.mk


## project-configuration info


## build-configuration info

ifeq ($(BUILD_SPEC),default)
CFLAGS_OPTIONS_ALL = -std=c99 -DLIGNEX1 -DUEMF -DWEBS -DDIGEST_ACCESS_SUPPORT -DUSER_MANAGEMENT_SUPPORT1
EXTRA_MODULES    = $(SUB_TARGETS)
POST_BUILD_RULE  = echo "$(WIND_BASE)/host/x86-win32/bin/mkimage -O vxworks -T kernel -C none -n vxworks -A ppc -a 01000000 -e 01000000 -d vxWorks.bin d:/tftpboot/uVxWorks"
POST_HEX_BUILD_RULE = ls
endif

# override make definitions only below this line


# override make definitions only above this line

include $(WIND_KRNL_MK)/rules.project.mk


## build-configuration info

ifeq ($(BUILD_SPEC),default)

usrAppInit.o:  $(PRJ_DIR)/usrAppInit.c 
	$(RM) usrAppInit.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/usrAppInit.c

usrRtpAppInit.o:  $(PRJ_DIR)/usrRtpAppInit.c 
	$(RM) usrRtpAppInit.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/usrRtpAppInit.c

BootShellMain.o:  $(PRJ_DIR)/BootShellMain.c 
	$(RM) BootShellMain.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/BootShellMain.c

asp.o:  $(PRJ_DIR)/WebServer/asp.c 
	$(RM) asp.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/asp.c

balloc.o:  $(PRJ_DIR)/WebServer/balloc.c 
	$(RM) balloc.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/balloc.c

base64.o:  $(PRJ_DIR)/WebServer/base64.c 
	$(RM) base64.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/base64.c

cgi.o:  $(PRJ_DIR)/WebServer/cgi.c 
	$(RM) cgi.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/cgi.c

default.o:  $(PRJ_DIR)/WebServer/default.c 
	$(RM) default.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/default.c

ejlex.o:  $(PRJ_DIR)/WebServer/ejlex.c 
	$(RM) ejlex.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/ejlex.c

ejparse.o:  $(PRJ_DIR)/WebServer/ejparse.c 
	$(RM) ejparse.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/ejparse.c

emfdb.o:  $(PRJ_DIR)/WebServer/emfdb.c 
	$(RM) emfdb.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/emfdb.c

form.o:  $(PRJ_DIR)/WebServer/form.c 
	$(RM) form.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/form.c

h.o:  $(PRJ_DIR)/WebServer/h.c 
	$(RM) h.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/h.c

handler.o:  $(PRJ_DIR)/WebServer/handler.c 
	$(RM) handler.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/handler.c

main.o:  $(PRJ_DIR)/WebServer/main.c 
	$(RM) main.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/main.c

md5c.o:  $(PRJ_DIR)/WebServer/md5c.c 
	$(RM) md5c.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/md5c.c

mime.o:  $(PRJ_DIR)/WebServer/mime.c 
	$(RM) mime.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/mime.c

misc.o:  $(PRJ_DIR)/WebServer/misc.c 
	$(RM) misc.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/misc.c

mocana_ssl.o:  $(PRJ_DIR)/WebServer/mocana_ssl.c 
	$(RM) mocana_ssl.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/mocana_ssl.c

page.o:  $(PRJ_DIR)/WebServer/page.c 
	$(RM) page.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/page.c

ringq.o:  $(PRJ_DIR)/WebServer/ringq.c 
	$(RM) ringq.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/ringq.c

rom.o:  $(PRJ_DIR)/WebServer/rom.c 
	$(RM) rom.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/rom.c

security.o:  $(PRJ_DIR)/WebServer/security.c 
	$(RM) security.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/security.c

sock.o:  $(PRJ_DIR)/WebServer/sock.c 
	$(RM) sock.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/sock.c

sockGen.o:  $(PRJ_DIR)/WebServer/sockGen.c 
	$(RM) sockGen.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/sockGen.c

strdup.o:  $(PRJ_DIR)/WebServer/strdup.c 
	$(RM) strdup.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/strdup.c

strncasecmp.o:  $(PRJ_DIR)/WebServer/strncasecmp.c 
	$(RM) strncasecmp.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/strncasecmp.c

sym.o:  $(PRJ_DIR)/WebServer/sym.c 
	$(RM) sym.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/sym.c

uemf.o:  $(PRJ_DIR)/WebServer/uemf.c 
	$(RM) uemf.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/uemf.c

um.o:  $(PRJ_DIR)/WebServer/um.c 
	$(RM) um.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/um.c

umui.o:  $(PRJ_DIR)/WebServer/umui.c 
	$(RM) umui.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/umui.c

url.o:  $(PRJ_DIR)/WebServer/url.c 
	$(RM) url.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/url.c

value.o:  $(PRJ_DIR)/WebServer/value.c 
	$(RM) value.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/value.c

webrom.o:  $(PRJ_DIR)/WebServer/webrom.c 
	$(RM) webrom.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/webrom.c

webs.o:  $(PRJ_DIR)/WebServer/webs.c 
	$(RM) webs.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/webs.c

websda.o:  $(PRJ_DIR)/WebServer/websda.c 
	$(RM) websda.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/websda.c

websuemf.o:  $(PRJ_DIR)/WebServer/websuemf.c 
	$(RM) websuemf.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/WebServer/websuemf.c

BootShell.o:  $(PRJ_DIR)/BootShell.cpp 
	$(RM) BootShell.o
	$(CXX) $(C++FLAGS) $(CC_SDA_FLAGS) $(C++FLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/BootShell.cpp

ManSbc.o:  $(PRJ_DIR)/ManSbc.cpp 
	$(RM) ManSbc.o
	$(CXX) $(C++FLAGS) $(CC_SDA_FLAGS) $(C++FLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/ManSbc.cpp

FileTar.o:  $(PRJ_DIR)/Untar/FileTar.cpp 
	$(RM) FileTar.o
	$(CXX) $(C++FLAGS) $(CC_SDA_FLAGS) $(C++FLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/Untar/FileTar.cpp
endif


## user defined rules

prjConfig.o : $(PRJ_DIR)/prjConfig.c
	$(CC) $(OPTION_OBJECT_ONLY) $(CFLAGS) $(CFLAGS_OPTIONS_ALL) $(PROJECT_BSP_FLAGS_EXTRA) $(PRJ_DIR)/prjConfig.c -o $@

linkSyms.o : $(PRJ_DIR)/linkSyms.c
	$(CC) $(OPTION_OBJECT_ONLY) $(CFLAGS) $(CFLAGS_OPTIONS_ALL) $(PROJECT_BSP_FLAGS_EXTRA) $(PRJ_DIR)/linkSyms.c -o $@


src_build :

src_depend :

$(PRJ_FULL_PATH)/compObjs.lst : $(PRJ_MAKEFILE)
	@ $(RM) $@
	@ touch $@

src_clean :
	@ $(RM) compObjs.lst
