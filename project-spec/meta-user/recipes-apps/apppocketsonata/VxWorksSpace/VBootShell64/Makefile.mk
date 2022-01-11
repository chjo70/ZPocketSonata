# Makefile generated by the project manager
#


# GENERATED: Thu Nov 18 11:01:18 +0900 2021
# DO NOT EDIT - file is regenerated whenever the project changes


## core information

ifeq ($(wildcard Makefile.mk),)
PRJ_DIR        = ..
else
PRJ_DIR        = .
endif
PRJ_FILE       = VBootShell64.wpj
PRJ_FULL_PATH  = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VBootShell64
PRJ_TYPE       = vxWorks
PRJ_OBJS       = usrAppInit.o usrRtpAppInit.o prjConfig.o linkSyms.o BootShell.o BootShellMain.o ManSbc.o FileTar.o asp.o balloc.o base64.o cgi.o default.o ejlex.o ejparse.o emfdb.o form.o h.o handler.o main.o md5c.o mime.o misc.o mocana_ssl.o page.o ringq.o rom.o security.o sock.o sockGen.o strdup.o strncasecmp.o sym.o uemf.o um.o umui.o url.o value.o webrom.o webs.o websda.o websuemf.o
USER_OBJS      = 
PRJ_MAKEFILE   = $(PRJ_DIR)/Makefile.mk
BOOT_OBJS      =  $(BOOT_EXTRA)
BUILD_SPEC     = default
BSP_DIR        = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VBootShell64/hmt_t2080vpx3u_1_0_0_0
VSB_DIR        = D:/VirtualBoxVMs/Git/ZPocketSonata1/project-spec/meta-user/recipes-apps/apppocketsonata/VxWorksSpace/VSourceBuild64
VXBUILD        = LP64 SMP
OPT            = -inet6



## set searching directories for dependencies

vpath %.c $(BSP_DIR)
vpath %.cpp $(BSP_DIR)
vpath %.cxx $(BSP_DIR)
vpath %.s $(BSP_DIR)


## build-configuration info

CPU            = PPCE6500
TOOL           = diab
TOOL_FAMILY    = diab
TOOL_VERSION   = diab_5_9_6_1
_CC_VERSION    = diab_5_9_6_5
ifeq ($(BUILD_SPEC),default)
DEFAULT_RULE   = uVxWorks
endif


## Memory adresses variables

RAM_LOW_ADRS = ffffffff80100000
RAM_HIGH_ADRS = ffffffff90000000
LOCAL_MEM_LOCAL_ADRS = KERNEL_SYS_MEM_RGN_BASE
DATA_SEG_ALIGN = 1
KERNEL_LOAD_ADRS = 00100000

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
	INCLUDE_ADR_SPACE_DIRECT_MAP \
	INCLUDE_ADR_SPACE_LIB \
	INCLUDE_AIM_CACHE \
	INCLUDE_ALTIVEC \
	INCLUDE_ANSI_ABORT \
	INCLUDE_ANSI_ABS \
	INCLUDE_ANSI_ASSERT \
	INCLUDE_ANSI_ATOF \
	INCLUDE_ANSI_BSEARCH \
	INCLUDE_ANSI_CTYPE \
	INCLUDE_ANSI_LONGJMP \
	INCLUDE_ANSI_MATH \
	INCLUDE_ANSI_MEMCHR \
	INCLUDE_ANSI_MEMCMP \
	INCLUDE_ANSI_MEMCPY \
	INCLUDE_ANSI_MEMMOVE \
	INCLUDE_ANSI_MEMSET \
	INCLUDE_ANSI_STDIO \
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
	INCLUDE_BOOT_LINE_INIT \
	INCLUDE_BSP_MACROS \
	INCLUDE_CACHE_ENABLE \
	INCLUDE_CACHE_SUPPORT \
	INCLUDE_CHECKSUM \
	INCLUDE_CLASS_LIB \
	INCLUDE_CLASS_LIST \
	INCLUDE_CONDVAR \
	INCLUDE_CONDVAR_OPEN \
	INCLUDE_COPROCESSOR \
	INCLUDE_COPROCESSOR_SHOW \
	INCLUDE_CORE_NFS_CLIENT \
	INCLUDE_CPC \
	INCLUDE_CPU_INIT \
	INCLUDE_CTORS_DTORS \
	INCLUDE_DATACOLLECTOR \
	INCLUDE_DEBUG \
	INCLUDE_DEBUG_KPRINTF \
	INCLUDE_DEFERRED_INTERRUPT_ENABLE \
	INCLUDE_DEVCLK_SYS \
	INCLUDE_DEVICE_MANAGER \
	INCLUDE_DIAB_INTRINSICS \
	INCLUDE_DLL \
	INCLUDE_DMA_SYS \
	INCLUDE_DOSFS_DIR_VFAT \
	INCLUDE_DOSFS_FAT \
	INCLUDE_DOSFS_MAIN \
	INCLUDE_DOSFS_PRTMSG_LEVEL \
	INCLUDE_DOSFS_SHOW \
	INCLUDE_DOSFS_VOL_BIO_BUFFER_SIZE \
	INCLUDE_EDR_DEFAULT_POLICY \
	INCLUDE_EDR_STUB \
	INCLUDE_END \
	INCLUDE_END_COMMON \
	INCLUDE_END_ETHER_HDR \
	INCLUDE_ENV_VARS \
	INCLUDE_ERF \
	INCLUDE_ETHERNET \
	INCLUDE_EVENTPOINT \
	INCLUDE_EVENTPOINT_STUB \
	INCLUDE_EXC_HANDLING \
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
	INCLUDE_GENERICPHY \
	INCLUDE_GENERIC_MMD_PHY \
	INCLUDE_HANDLE_SHOW \
	INCLUDE_HASH \
	INCLUDE_HOOKS \
	INCLUDE_HOST_TBL \
	INCLUDE_HW_FP \
	INCLUDE_IDLE_TASKS \
	INCLUDE_INT_LIB_INIT \
	INCLUDE_IO_BASIC \
	INCLUDE_IO_FILE_SYSTEM \
	INCLUDE_IO_MISC \
	INCLUDE_IO_POSIX \
	INCLUDE_IO_REMOVABLE \
	INCLUDE_IO_RTP \
	INCLUDE_IO_SYSTEM \
	INCLUDE_IPCOM \
	INCLUDE_IPCOM_USE_ETHERNET \
	INCLUDE_IPCOM_USE_INET \
	INCLUDE_IPCOM_USE_INET6 \
	INCLUDE_IPCOM_USR \
	INCLUDE_IPNET \
	INCLUDE_IPNET6_USE_MCAST_ROUTING \
	INCLUDE_IPNET_IFCONFIG_1 \
	INCLUDE_IPNET_LOOPBACK_CONFIG \
	INCLUDE_IPNET_SOCKET \
	INCLUDE_IPNET_USE_LOOPBACK \
	INCLUDE_IPNET_USE_MCAST_ROUTING \
	INCLUDE_IPNET_USE_NETLINKSOCK \
	INCLUDE_IPNET_USE_ROUTESOCK \
	INCLUDE_IPNET_USE_SOCK_COMPAT \
	INCLUDE_IPNET_USE_VLAN \
	INCLUDE_IPRADVD \
	INCLUDE_IPTCP \
	INCLUDE_IPV4 \
	INCLUDE_IPV6 \
	INCLUDE_IPWRAP_GETADDRINFO \
	INCLUDE_ISR_DEFER \
	INCLUDE_ISR_HANDLER_INIT \
	INCLUDE_JOB_DEFER \
	INCLUDE_JOB_QUEUE \
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
	INCLUDE_MEM_SHOW \
	INCLUDE_MII_FDT_SYS \
	INCLUDE_MII_MONITOR_TASK \
	INCLUDE_MII_SYS \
	INCLUDE_MMU_ARCH_COMMON_ALIB \
	INCLUDE_MMU_BASIC \
	INCLUDE_MMU_GLOBAL_MAP \
	INCLUDE_MODULE_MANAGER \
	INCLUDE_MSG_Q \
	INCLUDE_MSG_Q_CREATE_DELETE \
	INCLUDE_MSG_Q_EVENTS \
	INCLUDE_MSG_Q_OPEN \
	INCLUDE_MTD \
	INCLUDE_MTD_VXBFLASH \
	INCLUDE_MUX2 \
	INCLUDE_MUX2_OVER_END \
	INCLUDE_MUX_COMMON \
	INCLUDE_NETBUFLIB \
	INCLUDE_NETBUFPOOL \
	INCLUDE_NETMASK_GET \
	INCLUDE_NETWORK \
	INCLUDE_NET_BOOT \
	INCLUDE_NET_DAEMON \
	INCLUDE_NET_HOST_SETUP \
	INCLUDE_NFS2_CLIENT \
	INCLUDE_NFS_DEBUG \
	INCLUDE_OBJ_INFO \
	INCLUDE_OBJ_LIB \
	INCLUDE_OBJ_LIB_ARCH \
	INCLUDE_OBJ_OPEN \
	INCLUDE_OFFSET_SYMBOLS \
	INCLUDE_PG_MGR_BASIC \
	INCLUDE_PG_POOL_LIB \
	INCLUDE_PG_POOL_PHYS_LIB \
	INCLUDE_PG_POOL_VIRT_LIB \
	INCLUDE_PMAP_LIB \
	INCLUDE_POOL \
	INCLUDE_POSIX_CLOCKS \
	INCLUDE_POSIX_DIRLIB \
	INCLUDE_POSIX_FS \
	INCLUDE_POSIX_TIMERS \
	INCLUDE_POSIX_UMASK \
	INCLUDE_POSIX_USER_GROUP \
	INCLUDE_PTYDRV \
	INCLUDE_Q_FIFO \
	INCLUDE_Q_PRI_BMAP \
	INCLUDE_Q_PRI_DELTA \
	INCLUDE_Q_PRI_LIST \
	INCLUDE_RANDOM_NUM_GEN \
	INCLUDE_RAWFS \
	INCLUDE_RBUFF \
	INCLUDE_REBOOT_HOOKS \
	INCLUDE_REMLIB \
	INCLUDE_RNG_BUF \
	INCLUDE_RPC \
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
	INCLUDE_SEM_INFO \
	INCLUDE_SEM_LIB \
	INCLUDE_SEM_MUTEX \
	INCLUDE_SEM_MUTEX_CREATE \
	INCLUDE_SEM_OPEN \
	INCLUDE_SEM_READ_WRITE \
	INCLUDE_SEM_READ_WRITE_CREATE \
	INCLUDE_SEM_SHOW \
	INCLUDE_SEQ_TIMESTAMP \
	INCLUDE_SHELL \
	INCLUDE_SHELL_BANNER \
	INCLUDE_SHELL_CORE \
	INCLUDE_SHELL_INTERP_C \
	INCLUDE_SHELL_VI_MODE \
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
	INCLUDE_STANDALONE_SYM_TBL \
	INCLUDE_STDIO \
	INCLUDE_SV_DATACOLLECTOR \
	INCLUDE_SW_RANDOM_NUM_GEN \
	INCLUDE_SYM_TBL \
	INCLUDE_SYM_TBL_INIT \
	INCLUDE_SYM_TBL_SHOW \
	INCLUDE_SYSCLK_INIT \
	INCLUDE_SYSLOG \
	INCLUDE_SYS_START \
	INCLUDE_TASK_CREATE_DELETE \
	INCLUDE_TASK_CREATE_HOOKS \
	INCLUDE_TASK_INFO \
	INCLUDE_TASK_LIST \
	INCLUDE_TASK_OPEN \
	INCLUDE_TASK_RESTART \
	INCLUDE_TASK_SHOW \
	INCLUDE_TASK_SWAP_HOOKS \
	INCLUDE_TASK_SWITCH_HOOKS \
	INCLUDE_TASK_TOOLS_UTIL \
	INCLUDE_TFFS \
	INCLUDE_TFFS_MOUNT \
	INCLUDE_TIMER_OPEN \
	INCLUDE_TIMER_SYS \
	INCLUDE_TIP \
	INCLUDE_TLS \
	INCLUDE_TLS_LOADER_SUPPORT \
	INCLUDE_TL_FTL \
	INCLUDE_TTY_DEV \
	INCLUDE_TYLIB \
	INCLUDE_UNLOADER \
	INCLUDE_USER_APPL \
	INCLUDE_VXBUS \
	INCLUDE_VXBUS_PARAMS \
	INCLUDE_VXB_AUX_CLK \
	INCLUDE_VXB_SYS_CLK \
	INCLUDE_VXCPULIB \
	INCLUDE_VXDBG \
	INCLUDE_VXDBG_CPU_CONTROL \
	INCLUDE_VXDBG_HOOK \
	INCLUDE_VXDBG_MODULE \
	INCLUDE_VXDBG_RUNCTRL \
	INCLUDE_VXEVENTS \
	INCLUDE_VXIPI \
	INCLUDE_VXMEMPROBE_INIT \
	INCLUDE_VXMUX_MBLK \
	INCLUDE_VXMUX_NULLBUFPOOL \
	INCLUDE_VX_TRADITIONAL_SCHEDULER \
	INCLUDE_WATCHDOGS \
	INCLUDE_WATCHDOGS_CREATE_DELETE \
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
C++FLAGS_OPTIONS_ALL = -std=c99 -DLIGNEX1 -DUEMF -DWEBS -DDIGEST_ACCESS_SUPPORT -DUSER_MANAGEMENT_SUPPORT1
CFLAGS_OPTIONS_ALL = -std=c99 -DLIGNEX1 -DUEMF -DWEBS -DDIGEST_ACCESS_SUPPORT -DUSER_MANAGEMENT_SUPPORT1
EXTRA_MODULES    = $(SUB_TARGETS)
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

BootShell.o:  $(PRJ_DIR)/../VBootShell/BootShell.cpp 
	$(RM) BootShell.o
	$(CXX) $(C++FLAGS) $(CC_SDA_FLAGS) $(C++FLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/BootShell.cpp

BootShellMain.o:  $(PRJ_DIR)/../VBootShell/BootShellMain.c 
	$(RM) BootShellMain.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/BootShellMain.c

ManSbc.o:  $(PRJ_DIR)/../VBootShell/ManSbc.cpp 
	$(RM) ManSbc.o
	$(CXX) $(C++FLAGS) $(CC_SDA_FLAGS) $(C++FLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/ManSbc.cpp

FileTar.o:  $(PRJ_DIR)/../VBootShell/Untar/FileTar.cpp 
	$(RM) FileTar.o
	$(CXX) $(C++FLAGS) $(CC_SDA_FLAGS) $(C++FLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/Untar/FileTar.cpp

asp.o:  $(PRJ_DIR)/../VBootShell/WebServer/asp.c 
	$(RM) asp.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/asp.c

balloc.o:  $(PRJ_DIR)/../VBootShell/WebServer/balloc.c 
	$(RM) balloc.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/balloc.c

base64.o:  $(PRJ_DIR)/../VBootShell/WebServer/base64.c 
	$(RM) base64.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/base64.c

cgi.o:  $(PRJ_DIR)/../VBootShell/WebServer/cgi.c 
	$(RM) cgi.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/cgi.c

default.o:  $(PRJ_DIR)/../VBootShell/WebServer/default.c 
	$(RM) default.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/default.c

ejlex.o:  $(PRJ_DIR)/../VBootShell/WebServer/ejlex.c 
	$(RM) ejlex.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/ejlex.c

ejparse.o:  $(PRJ_DIR)/../VBootShell/WebServer/ejparse.c 
	$(RM) ejparse.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/ejparse.c

emfdb.o:  $(PRJ_DIR)/../VBootShell/WebServer/emfdb.c 
	$(RM) emfdb.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/emfdb.c

form.o:  $(PRJ_DIR)/../VBootShell/WebServer/form.c 
	$(RM) form.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/form.c

h.o:  $(PRJ_DIR)/../VBootShell/WebServer/h.c 
	$(RM) h.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/h.c

handler.o:  $(PRJ_DIR)/../VBootShell/WebServer/handler.c 
	$(RM) handler.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/handler.c

main.o:  $(PRJ_DIR)/../VBootShell/WebServer/main.c 
	$(RM) main.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/main.c

md5c.o:  $(PRJ_DIR)/../VBootShell/WebServer/md5c.c 
	$(RM) md5c.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/md5c.c

mime.o:  $(PRJ_DIR)/../VBootShell/WebServer/mime.c 
	$(RM) mime.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/mime.c

misc.o:  $(PRJ_DIR)/../VBootShell/WebServer/misc.c 
	$(RM) misc.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/misc.c

mocana_ssl.o:  $(PRJ_DIR)/../VBootShell/WebServer/mocana_ssl.c 
	$(RM) mocana_ssl.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/mocana_ssl.c

page.o:  $(PRJ_DIR)/../VBootShell/WebServer/page.c 
	$(RM) page.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/page.c

ringq.o:  $(PRJ_DIR)/../VBootShell/WebServer/ringq.c 
	$(RM) ringq.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/ringq.c

rom.o:  $(PRJ_DIR)/../VBootShell/WebServer/rom.c 
	$(RM) rom.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/rom.c

security.o:  $(PRJ_DIR)/../VBootShell/WebServer/security.c 
	$(RM) security.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/security.c

sock.o:  $(PRJ_DIR)/../VBootShell/WebServer/sock.c 
	$(RM) sock.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/sock.c

sockGen.o:  $(PRJ_DIR)/../VBootShell/WebServer/sockGen.c 
	$(RM) sockGen.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/sockGen.c

strdup.o:  $(PRJ_DIR)/../VBootShell/WebServer/strdup.c 
	$(RM) strdup.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/strdup.c

strncasecmp.o:  $(PRJ_DIR)/../VBootShell/WebServer/strncasecmp.c 
	$(RM) strncasecmp.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/strncasecmp.c

sym.o:  $(PRJ_DIR)/../VBootShell/WebServer/sym.c 
	$(RM) sym.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/sym.c

uemf.o:  $(PRJ_DIR)/../VBootShell/WebServer/uemf.c 
	$(RM) uemf.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/uemf.c

um.o:  $(PRJ_DIR)/../VBootShell/WebServer/um.c 
	$(RM) um.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/um.c

umui.o:  $(PRJ_DIR)/../VBootShell/WebServer/umui.c 
	$(RM) umui.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/umui.c

url.o:  $(PRJ_DIR)/../VBootShell/WebServer/url.c 
	$(RM) url.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/url.c

value.o:  $(PRJ_DIR)/../VBootShell/WebServer/value.c 
	$(RM) value.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/value.c

webrom.o:  $(PRJ_DIR)/../VBootShell/WebServer/webrom.c 
	$(RM) webrom.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/webrom.c

webs.o:  $(PRJ_DIR)/../VBootShell/WebServer/webs.c 
	$(RM) webs.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/webs.c

websda.o:  $(PRJ_DIR)/../VBootShell/WebServer/websda.c 
	$(RM) websda.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/websda.c

websuemf.o:  $(PRJ_DIR)/../VBootShell/WebServer/websuemf.c 
	$(RM) websuemf.o
	$(CC) $(CFLAGS) $(CC_SDA_FLAGS) $(CFLAGS_OPTIONS_ALL) -c $(PRJ_DIR)/../VBootShell/WebServer/websuemf.c
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