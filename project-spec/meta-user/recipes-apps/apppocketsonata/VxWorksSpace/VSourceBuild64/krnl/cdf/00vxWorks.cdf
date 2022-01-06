/* 00vxWorks.cdf - VxWorks components */

/*
 * Copyright (c) 1998-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
16nov17,dlk  Added usrRtpBaseLib.c as a configlette for INCLUDE_KERNEL.
07nov17,sub  Added missing prototypes (V7COR-5334)
18oct17,wap  Make sure idle task startup occurs after boardInit()
             is called (V7COR-5320)
19sep17,emj  Update to add folder definition (V7COR-5358)
25apr17,jla  Enhance clarity of synopses. Remove redundancy in names. (F8862)
11apr17,own  Removed redundancy from component and parameter NAME values.
             Created FOLDER_APPLICATION_INITIALIZATION  folder under FOLDER_APPLICATION.
	     Improved SYNOPSIS content. Child components of FOLDER_NOT_VISIBLE
	     were excluded from improvements (F8862).
22mar17,rjq  Add PROTOTYPE in INCLUDE_USER_PRE_NETWORK_APPL_INIT (V7NET-1285)
07feb17,brk  Whitespace cleanup
02feb17,jbm  Minor editing for name and synopsis, corrected synopsis for
             INCLUDE_EXC_HANDLING
25jan17,dlk  adding INCLUDE_GETPAGESIZE (V7COR-4799)
15dec16,cww  moved INCLUDE_EXC_SIGNALS from ARM layer
16dec16,cfm  removed INCLUDE_PROTECT_VEC_TABLE in usrKernelExtraInit, added
             INCLUDE_DATA_NO_EXEC in INCLUDE_KERNEL_HARDENING and moved
             INCLUDE_KERNEL_HARDENING to FOLDER_KERNEL_HARDENING (F7142)
05dec16,y_h  added power hook component, support ACPI event feature (F6446)
09aug16,l_l  Added DKM_TLS_SIZE (US80079)
17nov16,dlk  Increase VX_MAX_TASK_CREATE_RTNS default from 20 to 40 (F7384).
15jun16,ajt  Replace INIT_RTN objShowInit() with LINK_SYMS objShowAll
             in Component INCLUDE_OBJECT_SHOW (V7COR-2194)
25may16,pcs  Added back Component INCLUDE_EDR_POLICY_HOOKS.
21apr16,emj  CERT: Update to produce partially linked objects (US79607)
04apr16,jxy  Rename FOLDER_SECURITY
15jun15,gls  added LINK_SYMS to INCLUDE_BMPLIB
24jul15,rr   Added  INCLUDE_MEM_PART_CACHE under usrRoot for non
             _WRS_CONFIG_VXBUS_LEGACY (V7COR-3305)
11jun15,rr   updated INCLUDE_DEBUG_KWRITE_USER init_order (V7COR-2868)
29apr15,gls  added LINK_SYMS to INCLUDE_DLL_CREATE_DELETE and
             INCLUDE_SLL_CREATE_DELETE
24apr15,gls  added INCLUDE_SC_SEM_READ_WRITE, INCLUDE_SC_CONDVAR
             and INCLUDE_SC_SEM_EXCHANGE
16apr15,h_k  added INCLUDE_SYSLOG. (F2865)
14apr15,h_k  removed dependency to INCLUDE_HOOKS from
             INCLUDE_TASK_CREATE_HOOKS. (V7COR-2832)
06apr15,gls  added init routine to INCLUDE_POSIX_DIRLIB for CERT
23mar15,txu  add INCLUDE_POSIX_UMASK component (US55492)
08jan15,rlp  Removed Debug Agent from tools folder (V7COR-2302).
08jan15,jpb  Added missing RNG components (US34996)
24oct14,kk   updated SYNOPSIS of MAX_ISR_JOBS with more info (V7COR-2120)
20oct14,pcs  Added REQUIRES INCLUDE_PMAP_LIB to Component INCLUDE_EDR_PM
16oct14,jpb  V7COR-1665: Missing dependancy for INCLUDE_ENV_VARS
16oct14,jpb  Added TASK_KERNEL_EXC_STACK_SIZE parameter.  (Req:
             WIND00195513)
08oct14,gls  Added INCLUDE_RTP_SIGNALS
30sep14,clt  changed INIT_RTN hashLibInit to LINK_SYMS hashTblInit
26sep14,cww  added parameter POSIX_CLOCK_TIMER (V7COR-1677)
18sep14,pcs  Added Selection SELECT_EDR_POLICY to select between Components
             INCLUDE_EDR_DEFAULT_POLICY and INCLUDE_EDR_CUSTOM_POLICY and
             removed Component INCLUDE_EDR_POLICY_HOOKS.
17sep14,cww  removed unnecessary dependency for INCLUDE_ENV_VARS
03sep14,kk   fixed V7COR-1561 to associate VX_MAX_TASK_CREATE_RTNS to
             INCLUDE_TASK_CREATE_HOOKS
26aug14,yjw  fix cortexm build error (US40548)
25aug14,ljl  Add FOLDER_SECURITY to FOLDER_ROOT, US44321
14aug14,jpb  renamed random number generator components
13aug14,pad  Added INCLUDE_POSIX_USER_GROUP component (US38499)
13aug14,wap  Fix defect V7COR-1263, INCLUDE_OBJ_OWNERSHIP should not be
             available for a VIP if _WRS_CONFIG_OBJECT_OWNERSHIP is not
             enabled in the VSB.
31jul14,pcs  Added Component INCLUDE_EDR_USER_POLICY
16jul14,jpb  US34996: INCLUDE_RANDOM updates
03jul14,j_l  US41956 - Implement GEN2 bootApp network boot
27jun14,pcs  Added HDR_FILES private/memPartLibP.h form components
             INCLUDE_MEM_MGR_FULL INCLUDE_MEM_MGR_BASIC INCLUDE_MEM_MGR_INFO.
             (V7COR-1257)
25jun14,jpb  US34996: INCLUDE_RANDOM
24jun14,dlk  Removing whitespace at end of lines (V7COR-1328).
24jun14,cww  delayed initialization of INCLUDE_APPL_LOG_UTIL (V7COR-1381)
20jun14,pee  removed trailing blank that affected usrRoot init group for legacy
             BSPs (V7COR-1328)
09may14,cww  added CERT restrictions
29may14,zan  Fixing V7NET-385, moving INCLUDE_APPL_LOG_UTIL init to usrRoot()
27may14,m_y  move INCLUDE_ERF in usrRoot group (V7STO-15)
21may14,cww  added BOOT_LINE related params from 00bsp.cdf
13may14,pcs  Fixed minor documentation issues.
09may14,cww  added CERT restrictions
21apr14,cww  removed strSearchLib (US34935)
03apr14,h_k  added INCLUDE_PROTECT_INTERRUPT_STACK_NON_CORE0 internal
             component for SMP. (VXW6-19208)
06mar14,j_l  US18115 - additional changes for IA
27feb14,dlk  Moving main network stack initialization after INCLUDE_SMP_INIT.
25feb14,ten  Removed legacy header file usrConfig.h
27feb14,zan  add INCLUDE_APPL_LOG_UTIL to usrInit
20feb14,s_z  move INCLUDE_SYSCTL before usrNetworkInit0 in VxBus mode(VXW7-572)
18feb14,ghs  add FOLDER_STORAGE to FOLDER_ROOT
14feb14,zan  adding FOLDER_SERVICE to FOLDER_OS
11feb14,jmp  INCLUDE_TASK_TOOLS_UTIL is no longer SMP specific (VXW7-1528).
11feb14,rlp  added development tool folder
10feb14,pcs  VXW7-1597 - POSIX components cleanup
07feb14,scm  US18115 - add wrapper IA implementation of board system
05feb14,h_k  corrected HDR_FILES for INCLUDE_CONDVAR and removed HDR_FILES from
             INCLUDE_CONDVAR_SHOW.
04feb14,cww  Updated name for WIND_JOBS_MAX (VXW7-1418)
31jan14,pcs  added missing INCLUDE_PMAP_LIB to InitGroup usrRoot when config
             macro _WRS_CONFIG_VXBUS_LEGACY is defined.
17jan14,cww  Added Parameter HIGH_RES_POSIX_CLOCK
20jan14,pcs  added INCLUDE_PMAP_LIB
30jan14,h_k  corrected a merge error to remove INCLUDE_TIME_PART_SCHEDULER,
             INCLUDE_TIME_PART_SWITCH_HOOKS, INCLUDE_TIME_PART_HOOKS_SHOW
             components that now reside in the core safety layer.
29jan14,wap  Only include INCLUDE_SYSCLK_INIT in the usrRoot InitGroup for
             legacy VxBus builds.
24jan14,ylu  fixed coverity and compling issues.
23jan14,ghs  move INCLUDE_ERF to FOLDER_SERVICE
23jan14,x_z  add default OS profiles.
17jan14,tlu  Moved I/O related components to 00core_io.cdf
27jan14,wap  Correct typo (INCLUDE_SYSHW_INIT1 -> INCLUDE_SYSHW_INIT_1)
20dec13,cww  init order cleanup after componentization
23jan14,x_z  add default OS profiles.
17jan14,hll  Add _CHILDREN in Folder FOLDER_KERNEL_DEBUG.(VXW7-1382)
15jan14,x_z  add default boot line fields.
07jan14,hll  Add initialization order for INCLUDE_DEBUG_KPRINTF.(VXW7-1263)
15jan14 s_z  remove INCLUDE_USB_HOST_CLASS_INIT and INCLUDE_USB_TGT_FUNC_INIT
             to 40usb.cdf
14jan14,zan  create SERVICE group.
20jan14,cww  fixed merge error with usrBootLine
13jan14,h_k  created layer for core safety.
06nov13,h_k  added INCLUDE_TIME_PART_SCHEDULER,
             INCLUDE_TIME_PART_SWITCH_HOOKS, INCLUDE_TIME_PART_HOOKS_SHOW
             components.
05dec13,r_y  remove INCLUDE_DEBUG_KWRITE_SIO in vxbus GEN2(WIND00446237).
31oct13,j_l  US18115 - IA implementation of board system
18oct13,h_k  removed funcBindP.h header inclusion.
             cleaned up obsoleted SOURCE attribute.
             moved INCLUDE_RTP_DEBUG_COMMAND to 01rtpdebug.cdf.
             moved INCLUDE_POSIX_TRACE_TIMESTAMP and INCLUDE_POSIX_TRACE to
             01systemviewer.cdf.
08oct13,h_k  moved INCLUDE_POSIX_ADVISORY_FILE_LOCKING to 01comp_vnode.cdf.
16oct13,x_z  moved initialization order for usrNetWorkInit out.
08oct13,cww  Removed duplicate prototype of checksum()
27sep13,rfr  added INCLUDE_CONDVAR_OPEN
26sep13,h_k  moved tlsLoadLib to utils pkg.
             moved INCLUDE_ISR_DEFER to vxbus pkg.
             moved INCLUDE_SYSDBG_FLAG from debug pkg.
13sep13,x_z  added INCLUDE_CPU_INIT and adjusted initialization process.
04sep13,jxu  Added FTL components
03sep13,x_z  removed SOURCE for INCLUDE_ISR_DEFER.
29aug13,cww  Fix init ordering issue with INCLUDE_BANNER (WIND00431749)
21aug13,rfr  added INCLUDE_CONDVAR and INCLUDE_CONDVAR_SHOW
07aug13,cww  merge from 6.9.3.1
02aug13,pcs  updated to use config option _WRS_CONFIG_COMPAT69_ADR_SPACE
16jul13,cww  added INCLUDE_BANNER
03jun13,cww  removed non-CORE components
22aug12,mze  INTRINSIC work
17apr13,elp  added RUNTIME_CREATION_TIME parameter (WIND00295975)
26mar13,cww  made task create/delete hook table size configurable
             (WIND00395617)
27mar13,s_z  Add INCLUDE_BOOT_HW_INIT component (WIND00390768)
19mar13,y_y  reordering INCLUDE_SM_OBJ and INCLUDE_ERF init order
             in usrIosExtraInit (WIND00408192)
06nov12,pee  WIND00110061
19oct12,cww  updated taskCreateHookInit() for SMP hooks
18sep12,l_z  Update SYNOPSIS of INCLUDE_PCI_CFGSHOW. (WIND00108357)
22aug12,mze  WIND00371707 - limit INTRINSICS to those built by VSB tools
28feb12,kk   fix typo in ENABLE_ALL_CPUS (WIND00253761)
18nov11,cww  Ensure sysExcMsg is updated when ED&R is invoked prior to
             usrRoot (WIND00111567)
             Moved usrSmpInit() before usrToolsInit() (WIND00309413)
07feb12,l_z  Add INCLUDE_EEPROMDRV for EEPROM driver init
29sep11,sem  WIND00307699 - Move pwr mgmt folder from hardware to os
27sep11,pcs  Added initialization of components INCLUDE_MEM_EDR and
             INCLUDE_MEM_EDR2 to the InitGroup usrRoot.
20jul11,jlv  WIND00255352, add power policy manager
27jun11,jxu  added PIPE_MAX_OPEN_FDS parameter (WIND00271309).
15jun11,rec  change INCLUDE_POWER_MGMT_CPU_BSP_SUPPORT to
             INCLUDE_TICKLESS_IDLE
08jun11,zl   added INCLUDE_JITTER_TOOL
03jun11,rec  WIND00255358 add device power management
26may11,pcs  Add components corresponding to the boot sequence hook
             callout mechanism.
04may11,jpb  Added module & link sym to INCLUDE_STRING_SEARCH.
15jun11,rec  change INCLUDE_POWER_MGMT_CPU_BSP_SUPPORT to
             INCLUDE_TICKLESS_IDLE
16feb11,v_r  Updated XXX_INTRINSICS synopsis for better clarity
             (CQ:WIND00253540).
25jan11,vhe  Fixed VSB/VIP compatibility (WIND00251938)
23dec10,d_c  WIND00238183 - Move usrDebugKWriteInit() call after
             sysHwInit()
10nov10,dlk  Remove backslash-whitespace-newline and similar issues that
             vxprj warns about.
13jan11,w_x  Initial USB OTG support changes (WIND00211541)
07dec10,ghs  Change USB component group name (WIND00245236)
23nov10,rec  add INCLUDE_CPU_ODG_POLICY_MGMT component
26nov10,ebh  added WRIFT init routine
05jul10,liu  change fppShowInit to aimFppShowInit. (WIND00192339)
13nov10,mze  replace _WRS_VX_SMP with _WRS_CONFIG_SMP
12nov10,gvm  Fix for WIND00239961
22oct10,rlp  Added INCLUDE_SYSDBG_FLAG component
21oct10,jmp  added missing init order rule for INCLUDE_CORE_DUMP_RTP
             (CQ:WIND00237388).
20oct10,cww  Updated TASK_USER_EXC_STACK_SIZE for LP64
29oct10,cww  added INIT_AFTER constraint for usrDebugKWriteInit
19oct10,ghs  Combine USB class driver initialization into one group
             (WIND00235953)
18oct10,mze  remove trailing space
08oct10,kk   remove INCLUDE_NBIO_LOG component, no longer used
29sep10,gls  added INCLUDE_EDR_POLICY_HOOKS (WIND00234560)
30sep10,ggz  Add password SHA256 hasing and salt support
29sep10,pee  init order change for INCLUDE_USB_KEYBOARD_INIT
22sep10,gvm  CPLUS component has addditional sources
16sep10,gls  made FUNCPTR_OBJ_MEMALLOC_RTN default to memPartAlignedAlloc
22sep10,gvm  CPLUS component has addditional sources
13sep10,cww  Removed kprintf from usrInit group
06sep10,vhe  Diab now compiles analysis DKMs. WB_RUNTIME_SUPPORT
             no longer requires GNU_INTRINSICS (WIND00230168)
18aug10,pee  update init order for INCLUDE_SYSCTL
09aug10,cww  Added INCLUDE_CACHE_COMPACT_DMA_SUPPORT to usrRoot
27jul10,cww  Delayed kprintf initialization for 64-bit
01jul10,cww  Delayed initialization of idle tasks
15jun10,h_k  removed the ifndef conditions from INIT_ORDER in
             usrIosExtraInit() which were added by mistake.
08jun10,jxu  Removed the components (INCLUDE_PROCFS INCLUDE_TFFS
             INCLUDE_TFFS_MOUNT) from LP64 build.
26may10,pee  adding standard List objects
20may10,h_w  Add INCLUDE_AF_MIPC_SOCKETS component.
18may10,pcs  Add support for device memory object.
20may10,jpb  Fixed header file location for pthreadLibInit.
26apr10,rec  CPU performance management update
27apr10,sem  Adjust KERNEL_COMMON_HEAP_INIT_SIZE default value
07apr10,gvm  break the link between icc and WB
01apr10,jpb  Added user-reserved memory to init order.
10mar10,gvm  updates for icc
19feb10,zl   added INCLUDE_POSIX_SHM_API
             INCLUDE_IO_MISC (WIND00167739)
             initialization order for mmmap() components
18feb10,rlp  Added INCLUDE_VXDBG component initialization.
17feb10,pch  small footprint
30jan10,h_w  Add INCLUDE_AF_MIPC_SOCKETS component
26jan10,d_c  SMP M-N updates: add INCLUDE_VXCPULIB component.
21jan10,zly  remove "REQUIRES INCLUDE_IO_RTP" from Component
08jan10,s_s  Adding INCLUDE_ENV_VARS in usrRoot Init group after the memory
             initialization and dropping it from usrKernelExtraInit Init
             group (defect CQ:WIND00194940)
30dec09,jpb  Remove INCLUDE_TASK_VARS from LP64 build.
16dec09,zl   use objMemAllot() for FUNCPTR_OBJ_MEMALLOC_RTN.
04nov09,pcs  Updated to reflect the name changes to the 64bit heaps.
04nov09,h_k  added INCLUDE_VXBUS_DISK in usrIosExtraInit.
             (WIND00189354)
08oct09,cww  Added INCLUDE_DEFERRED_INTERRUPT_ENABLE and
             INCLUDE_SYSHW_INIT_1
07oct09,rlp  Modified INCLUDE_GNU_INTRINSICS dependency (CQ:WIND00183905).
28sep09,cww  Delayed coredump init due to sysctl dependency
25sep09,pcs  Replace memInit2 with memSysHeapCreate
24sep09,jpb  Changed return value of clockLibInit.
25aug09,cww  Added InitGroup usrKernelCreateInit
08sep09,pcs  Updated to add support for multiple heaps for 64bit vxWorks.
11aug09,cww  Updated ordering in usrRoot
01apr09,zl   added INCLUDE_JOB_DEFER component.
27feb09,zl   updated objLibInit() arguments.
10feb09,zl   removed multi-way queue create/delete and qLib components
08sep09,gls  added synopsis to VX_SMP_NUM_CPUS (WIND00160676)
04sep09,s_s  Added INCLUDE_GETOPT component
28aug09,gls  removed minimal semaphore components (WIND00179395)
17aug09,hui  WIND00176466 - Fail to build VIP using max performance VSB
14aug09,jpb  Defect# 161788. Removed INCLUDE_SET.
12aug09,hui  WIND00176503 - workbench cant display FOLDER_HRFS
07aug09,hui  WIND174908 - INCLUDE_IO_REMOVABLE require the wrong component
13jul09,pch  Add support for INCLUDE_TM_TIMING_FRAMEWORK
03jul09,x_s  added component INCLUDE_SYSHW_INIT2.
17jun09,tcr  remove spinlock dependency from WindView
11jun09,h_k  added default baud setting in kwriteSioInit(). (CQ:166577)
08jun09,zly  remove "REQUIRES INCLUDE_IO_RTP" from Component
             INCLUDE_IO_MISC
02jun09,h_w  Added usrTipcInit to usrRoot if TIPC present (WIND00162024).
13jul09,pch  Add support for INCLUDE_TM_TIMING_FRAMEWORK
22apr09,jpb  Replaced setLib.h with setLibP.h.
21apr09,s_s  Modifying the prototype declaration of the component
             INCLUDE_DEBUG_KWRITE_USER
21apr09,s_s  Added the PROTOTYPE field for the component
             INCLUDE_DEBUG_KWRITE_USER. (Defect - WIND00162050)
17apr09,kk   fix CQ:WIND00161840, add spinLockIsrNdInit to
             INCLUDE_SPINLOCK_ISR_ND LINK_SYMS
15apr09,h_k  cleaned up a compiler warning for kwriteSioInit.
27mar09,s_s  Corrected typo Defect #WIND00160968. Also made the
             Selection visible in the workbench.
24mar09,gls  added INCLUDE_SPINLOCK_ND_TIMED
18mar09,s_s  Added kernel-write components
03feb09,cww  Add VX_SMP_CPU_EXPLICIT_RESERVE parameter
23jan09,h_k  fixed REQUIRES attribute in INCLUDE_OBJECT_SHOW.
12jan09,s_s  Added INCLUDE_OBJECT_SHOW component
14nov08,zl   added missing multi-line terminator for SYNOPSIS
10nov08,tcr  update INCLUDE_RBUFF to require INCLUDE_SPINLOCK_ISR_ND
             (WIND00136245)
24oct08,jpb  Defect WIND00136345.  Adding INCLUDE_SHOW_ROUTINES pulled in
             components INCLUDE_POSIX_TIMER_SHOW and INCLUDE_CLASS_SHOW
             when class list support not include.
23oct08,zl   added VXEVENTS_OPTIONS configuration parameter.
21oct08,kk   rename spinlockIsrNdLib to spinLockIsrNdLib
20oct08,jpb  Defect 139871.  Added requirement on
             INCLUDE_POSIX_TIMER_SHOW.
13oct08,jpb  Added requirement on INCLUDE_TASK_OPEN for
             INCLUDE_POSIX_PTHREADS.  This is because pthreadCreate calls
             taskOpen.
23sep08,kab  Fix CQ:133672 - AMP IPI init must follow CPC
25sep08,v_r  Decoupled tip from shell and network (def CQ:WIND00134830).
23sep08,jmp  Added the max number of tasks that can be spied to
             INCLUDE_SPY component (CQ:WIND00106559).
18sep08,jmp  Added INCLUDE_VXDBG_CPU_CONTROL initialization to usrRoot()
             (CQ:WIND00134567).
11sep08,v_r  Added INCLUDE_TIP component (req CQ:WIND00114857).
04sep08,gls  divided INCLUDE_TASK_HOOKS component
29aug08,zl   added TASK_PRIORITY_SET_COMPATIBLE
03sep08,jpb  Removed LAYER from components.
24apr08,tcr  update with eventpoints
14aug08,jpb  Removed INCLUDE_TASK_LIST dependancy on INCLUDE_OBJ_INFO
09jun08,s_z  Reorder initialization of USB Keyboard (Defect WIND00119420)
07jul08,gls  began deprecation of minimal semaphores
27jun08,cwu  insert INCLUDE_SM_OBJ in InitGroup of usrIosExtraInit for
             111681
15may08,zl   changed INCLUDE_ENABLE_ALL_CPUS to INCLUDE_SMP_INIT.
06may08,dtr  Add usrMultiosInit routine call if group present in usrRoot.
26mar08,v_r  Added the RTP debug command facility component (req
             CQ:WIND00004496).
08jan08,dlk  Rename INCLUDE_SPINLOCK_FAST --> INCLUDE_SPINLOCK_ISR_ND.
07jan08,gls  fast semaphores renamed to minimal semaphores
21nov07,gls  added INCLUDE_SEM_FAST_BINARY and INCLUDE_SEM_FAST_MUTEX
             added INCLUDE_SEM_FAST_BINARY_CREATE
             added INCLUDE_SEM_FAST_MUTEX_CREATE
11dec07,dlk  Added INCLUDE_SPINLOCK_FAST.
09jan08,pcs  In InitGroup usrRoot, move INCLUDE_PROTECT_TEXT to after
             INCLUDE_EDR_XXX (WIND00057363).
04oct07,mze  fix for 104829
27sep07,dcc  fixed defect WIND00105766: "The New IO Components Do Not Show
             Up in WorkBench".
13sep07,jpb  Added whitespace after "Name" in
             INCLUDE_Q_PRI_BMAP_CREATE_DELETE.  Defect# 104480.
07sep07,jmg  Added VX_SMP_NUM_CPUS.
06sep07,act  fix typo in INCLUDE_IO_FILE_SYSTEM
31aug07,pee  WIND101680. rename rand to stdrand.
31aug07,act  io footprint work (from pcm, modified)
31aug07,mmi  disable spinlock debugging by default
27aug07,kk   fix INCLUDE_TASK_VARS and usage of #ifdef SMP on the
             component
27aug07,jmg  Added VX_ENABLE_CPU_TIMEOUT
16aug07,pch  remove INCLUDE_TASK_VARS from SMP build
15aug07,dlk  Accomodate relocation of spin lock code.
08aug07,jmg  Added INCLUDE_TASK_ROTATE to FOLDER_KERNEL defect
             #WIND00100884
20jul07,kk   make ENABLE_ALL_CPUS a param of INCLUDE_KERNEL
17jul07,kk   surround SMP components with ifdef SMP
03jul07,rlp  Removed INCLUDE_BUF_MGR component.
19jun07,gls  added INCLUDE_SEM_EXCHANGE
11may07,jmg  Added INCLUDE_ATOMIC_OPERATORS to INCLUDE_LOGGING
17may07,jlk  removed sfs components
11may07,gls  added INCLUDE_TASK_TOOLS_UTIL
07may07,h_k  added ISR_DEFER_MODE parameter.
02may07,dbt  Enabled TLS support for MKL images.
27apr07,kk   add requires on ATOMIC_OPERATORS for INCLUDE_TASK_CREATE_DELETE
26apr07,pee  add source mode support with SMP
06apr07,zl   added INCLUDE_OBJ_INFO, INCLUDE_CLASS_LIST and
             INCLUDE_TASK_LIST components.
06apr07,v_r  Enforced dependency between loader hooks and TLS loader
             support (req CQ:WIND00045277)
04apr07,mmi  add spinLock API and Components
16mar07,gls  added CFG_PARAMS to INCLUDE_SEM_READ_WRITE
09mar07,pad  Removed a trailing backslash in INCLUDE_ANSI_STDLIB's
             required component list.
07mar07,gls  added INCLUDE_SEM_READ_WRITE
07mar07,jmg  Added component INCLUDE_ATOMIC_OPERATORS
14feb07,kk   moved INCLUDE_CPC to 10smp.cdf, added ENABLE_ALL_CPUS param
23feb07,h_k  added INCLUDE_ISR_DEFER.
12feb07,jmg  Added poolLibInit to INCLUDE_POOL, removed INCLUDE_WHEN from
             INCLUDE_POOL_SHOW, fixed typo in INCLUDE_IO_SYSTEM.
30jan07,jmg  Added INCLUDE_TASK_ROTATE (Req WIND00071010).
30jan07,jmg  Added VX_GLOBAL_NO_STACK_FILL (Req WIND00083667)
24jan07,jmg  In Requiers list of INCLUDE_ANSI_STDIO, INCLUDE_ENV_VARS
             and INCLUDE_POSIX_DIRLIB changed INCLUDE_MEM_MGR_FULL to
             INCLUDE_MEM_MGR_BASIC and removed INCLUDE_MEM_MGR_FULL from
             INCLUDE_ANSI_STDLIB (Req WIND00083666).
23jan07,zhr  Fixed the defect WIND00035897
08jan07,bwa  added usrDshmInit().
08dec06,jpb  Removed layer 1 capability for INCLUDE_GNU_INTRINSICS and
             INCLUDE_DIAB_INTRINSICS (Defect #82229).  Removed layer 1
             capability for INCLUDE_BOOT_LINE_INIT (Defect #114234).
08dec06,jpb  Fixed warning being issued that parameter has bad value.
             Type needs to be 'BOOL' and not 'bool' (Defect #37172).
02dec06,jpb  Corrected typo error.
07nov06,dbt  Added INCLUDE_TLS component.
25oct06,jmg  Created INCLUDE_POSIX_TIMER_SHOW as part of defect WIND00039293
28sep06,jmg  Changed the type define of objLibInit to (void *)
22sep06,slk  add INCLUDE_VXMEMPROBE_INIT Component
28sep06,jmg  Changed the type define of objLibInit to (void *)
05sep06,tcr  change init order of POSIX_TRACE and POSIX_TRACE_TIMESTAMP
06sep06,jln  Add SELECT_PX_SCHED_POLICY/INCLUDE_POSIX_TRACE to FOLDER_POSIX
24aug06,gls  changed value of MAX_ISR_JOBS (Defect #00059580)
             added PROTOTYPE for sigeventLibInit() (Defect #00062775)
23aug06,pcm  added INCLUDE_UTF
22aug06,pcm  added INCLUDE_DOSFS_SHOW
25jul06,dcc  Added SFS components.
16aug06,mze  added REQUIRES INCLUDE_WINDVIEW to INCLUDE_WVNETD component
14aug06,tcr  INCLUDE_POSIX_TRACE_TIMESTAMP requires INCLUDE_SYS_TIMESTAMP
10jul06,mmi  add INCLUDE_CPC and update usrRoot initGroup
02aug06,gga  added TIPC WV instrumentation component
01aug06,agf  change init group of INCLUDE_BOOT_LINE_INIT (WIND00056565)
18jul06,md   Add SYNOPSIS for rawfs (WIND00044787)
20jun06,pee  typos.
10jul06,gls  added INIT_RTN sigeventLibInit to INCLUDE_SIGEVENT component
             added INCLUDE_SIGEVENT to FOLDER_POSIX
29jun06,jln  modified for SCHED_SPORADIC support
15jun06,tcr  INCLUDE_SYS_TIMESTAMP should not require INCLUDE_WINDVIEW
             Add INCLUDE_POSIX_TRACE
09jun06,pcs  Updated to add obj/class lib support in MKL.
16jun06,zl   added INCLUDE_MEM_MGR_INFO, MEM_PART_DEFAULT_OPTIONS.
10may06,tfo  removed FOLDER_BUNDLES
25apr06,mcm  Fix for SPR#117934 - adding strcasecmp (and strncasecmp)
03apr06,pcm  fixed typo in INCLUDE_FORMATTED_OUT_BASIC (SPR 114558)
31mar06,kk   added REQUIRES to kernel components to ensure clean removal
             (SPR# 115349)
01Mar06,pee  Fixed multiple declarations of wvLib.o
08feb06,dlk  Replace INCLUDE_NET_STACK_START with its opposite,
             INCLUDE_NET_INIT_SKIP, for backwards compat. (SPR 117553)
23feb06,jlk  Added INCLUDE_HRFS_ACCESS_TIMESTAMP to FOLDER_IO_SYSTEM folder
10feb06,jlk  Removed INCLUDE_POSIX_GENERAL. Added IOS_POSIX_PSE52_MODE
             parameter
09feb06,kk   replace INCLUDE_VX_NATIVE_SCHEDULER with
             INCLUDE_VX_TRADITIONAL_SCHEDULER
09feb06,gls  added parameter to sigInit()
06feb06,agf  add BSP components to INCLUDE_KERNEL requires
03feb06,jlk  Added INCLUDE_POSIX_GENERAL
03feb06,pcm  add synopsis to INCLUDE_CDROMFS component
             is not dependent on stack anymore
19jan06,xli  add the INCLUDE_SOCKLIB to usrRoot init group since
             INCLUDE_SOCKLIB
18jan06,pad  Changed synopsis of the INCLUDE_POSIX_SCHED and
             INCLUDE_POSIX_PTHREADS components.
        kk   Improved name string for INCLUDE_WATCHDOG_CREATE_DLETE
             component (SPR #115952).
17jan06,bpn  Moved symbol table components to 01loader.cdf.
12jan06,act  add component INCLUDE_POSIX_ADVISORY_FILE_LOCKING
30dec05,yvp  Removed INIT_RTN for semaphore components.
             INCLUDE_POSIX_SEM requires INCLUDE_SEM_COUNTING.
21dec05,rfr  Added INCLUDE_VRFS
19dec05,pcm  added parameter to INCLUDE_CDROMFS to control default number
             of sectors to read in a single access
09oct05,dlk  Support INCLUDE_NET_STACK_START.
             Ensure that INCLUDE_TASK_VARS initialization routine
             is called if the component is included (SPR #112537).
17nov05,yvp  SPR 113975: INCLUDE_SIGNALS requires INCLUDE_ANSI_LONGJMP
             SPR 114233: TASK_UTIL had an incorrect SOURCE path
             SPR 114234: BOOT_LINE_INIT no longer a an MKL component
             SPR 114246: ANSI_TIME had incorrect LAYER value (is now 3)
             SPR 114254: added INCLUDE_ANSI_STRLCPY
             SPR 114259: incorrect modules list in INCLUDE_NBIO_LOG
             SPR 114910: GNU_INTRINSICS no longer an MKL component
             SPR 115086: corrected dependencies for INCLUDE_SET
             SPR 115088: corrected dependencies for ANSI_ASSERT
             SPR 115090: corrected dependencies for ENV_VARS
             SPR 115092: corrected dependencies for INCLUDE_NBIO_LOG
             SPR 115094: corrected dependencies for INCLUDE_PIPES
             SPR 115095: corrected dependencies for POSIX_DIRLIB
             SPR 115202: corrected dependencies for INCLUDE_FORMATTED_*
14oct05,kk   fixed typo in POSIX_DIRLIB component
10oct05,yvp  SPR 112547: INCLUDE_TASK_VARS inits in usrKernelExtraInit
             SPR 112942: ANSI_STDLIB_NUMBERS doesnt use floating point
             SPR 113423: new components for Sem/MsgQ event support.
                         corrected dependencies for ANSI_ABORT, LOGGING etc
             SPR 113654: Made POSIX_PTHREAD_SCHEDULER visible in the IDE
             SPR 113775: LINK_SYMS missing fro several ANSI components
             SPR 113809: Added INCLUDE_SIMPLE_BANNER.
07oct05,pcm  changed INCLUDE_XBD_PARTLIB to INCLUDE_XBD_PART_LIB. SPR 113236
07oct05,h_k  created INCLUDE_FP_TYPE. (SPR #113210)
             added IO_SYSTEM as a required comp for FORMATTED_IO.
             added MSG_Q as a required comp for VXEVENTS.
28sep05,yvp  Removed ISR objects from the default build (SPR 112909).
28sep05,kk   fixed dependency on FORMATTED_OUT_BASIC
26sep05,zl   removed folder definition for INCLUDE_MEM_ALLOT.
14sep05,jmt  Add source info for INCLUDE_BOOT_LINE_INIT
15sep05,pcm  added many components to the FOLDER_IO_SYSTEM folder
13sep05,pcm  added INCLUDE_RAM_DISK to usrIosExtraInit()
13sep05,pcm  added INCLUDE_TFFS_MOUNT (SPR# 112219)
13sep05,yvp  Updated ANSI_STDIO, ANSI_TIME, ANSI_STRERROR, POSIX_CLOCKS,
             TASK_RESTART etc. Added ANSI_LONGJMP, SIGNAL_ARCH etc
14sep05,h_k  moved modules for ANSI_MATH to arch dependent CDF.
             (SPR #112320)
13sep05,kk   remove OBJ_OWNERSHIP from default (SPR# 110865)
08sep05,dcc  removed INCLUDE_TAPEFS component (SPR# 111788).
08sep05,yvp  Fixed ANSI_STDLIB CDF definition (SPR 112003).
             Added INIT_RTN for TASK_VARS (SPR 109661).
             Corrected typo in CDF for INCLUDE_VXEVENTS.
07sep05,h_k  cleaned up BLIB_ARCH dependency. (SPR #111769)
01sep05,yvp  Scalability modifications:
             - split many INCLUDE_ANSI_xxx routines into seperate components
             - updated MODULES, REQUIRES & SOURCE for layers 1-3
31aug05,jmt  Move windPwrLib.o from INCLUDE_KERNEL to INCLUDE_KERNEL_ARCH
31aug05,gls  added INCLUDE_TASK_UTIL
30aug05,zl   created selector for memory allocator.
26aug05,pee  Corrected usage of invisible folder
18aug05,act  init XBD_TRANS before DOSFS, not after
18aug05,act  add INCLUDE_XBD_TRANS to usriosExtraInit group
09aug05,dcc  added dosFsCache initialization.
04aug05,aeg  added cdromFsFsmLib.o to INCLUDE_CDROMFS
28jul05,pcm  removed Component INCLUDE_DOSFS as it exists elsewhere
27jul05,jmp  added INCLUDE_CORE_DUMP to usrRoot InitGroup.
15jul05,jlk  fixed a bug where INCLUDE_XBD_BLK_DEV was dropped from
             usrIosExtraInit
18aug05,yvp  Added INCLUDE_REBOOT_HOOKS to FOLDER_KERNEL.
16aug05,gls  added objOwnerLib.o to INCLUDE_OBJ_OWNERSHIP component
16aug05,yvp  Added INIT_RTN for Q_XXX_CREATE_DELETE components.
             Added INCLUDE_FORMATTED_OUT_BASIC.
12aug05,zl   added INCLUDE_MMU_GLOBAL_MAP to usrRoot group; created
             INCLUDE_MEM_ALLOT component.
10aug05,yvp  Added INCLUDE_CLASS_LIB as an explicit dependency of
             INCLUDE_OBJ_LIB. Also added it to defaults of FOLDER_KERNEL.
             Added FOLDER_NOT_VISIBLE for the q*Lib components.
09aug05,pee  Added LAYER to EDR_STUB
06aug05,jln  Added SELECT_KERNEL_SCHEDULER
04aug05,yvp  Corrected typosin component names.
03aug05,yvp  Added newly created components (sem, msgQ & wd create/delete).
03aug05,pee  Added LAYER information
18jul05,pee  fixed some dependencies.
16jul05,jln  Added INCLUDE_POSIX_PTHREAD_SCHED component
15jul05,jlk  fixed a bug where INCLUDE_XBD_BLK_DEV was dropped from
             usrIosExtraInit
09jul05,yvp  Added INCLUDE_SEM_LIB to FOLDER_HIDDEN, excLibP.h to kernel
             headers, PROTOTYPE for INCLUDE_TASK_CREATE_DELETE. Added more
             description to synopsis for INCLUDE_ENV_VARS.
             Added INCLUDE_HOOKS and INCLUDE_HOOK_SHOW.
08jul05,pee  Added SOURCE for a bunch of component
07jul05,yvp  Added INCLUDE_REBOOT_HOOKS to the defaults for FOLDER_KERNEL.
04jul05,pcm  fixed up DEFAULTS list in FOLDER_KERNEL
23jun05,jlk  added INCLUDE_FS_EVENT_UTIL to usrIosExtraInit.
22jun05,yvp  Added components INCLUDE_TASK_CREATE_DELETE and
             INCLUDE_TASK_RESTART.
21jun05,pee  removed obsolete INCLUDE_CODETEST (SPR #110121)
15jun05,yvp  Mutex semaphore initalization moved into the usrInit group.
09jun05,yvp  New components INCLUDE_ISR_OBJECTS (no longer default),
             INCLUDE_SEM_LIB, INCLUDE_REBOOT_HOOKS.
             INCLUDE_EXC_TASK and INCLUDE_JOB_TASK now decoupled.
03jun05,pcm  added INCLUDE_ERF, INCLUDE_DEVICE_MANAGER, INCLUDE_XBD, and
             INCLUDE_FS_MONITOR to usrIosExtraInit
03jun05,pcm  added INCLUDE_DEVICE_MANAGER
02jun05,pcm  added INCLUDE_ERF
01jun05,pcm  added INCLUDE_HRFS_READONLY
26may05,pcm  added FS_MONITOR as RAWFS requirement; removed XBD_BLK_DEV
             from usrIosExtraInit()
25apr05,yvp  added LINK_SYMS attribute to INCLUDE_VXEVENTS
20apr05,gls  added INCLUDE_OBJ_OWNERSHIP (SPR #106150)
04apr05,svk  Add INCLUDE_STRING_SEARCH component
09mar05,pcm  added INCLUDE_HRFS_FORMAT
08mar05,pcm  added INCLUDE_HRFS and INCLUDE_XBD_BLK_DEV to usrIosExtraInit
22mar05,mcm  Fix for SPR#105016 - removing obselete C++ components.
07mar04,pcm  added INCLUDED_TAPEFS
26feb05,pcs  Changes to reflect different stack overflow and underflow
             sizes.
07feb05,zl   enable kernel text protection early.
04feb05,pch  SPR 102772: add INCLUDE_PROTECT_INTERRUPT_STACK
18jan05,yvp  Removed INCLUDE_VXEVENTS from the default configuration.
13jan05,tcr  Fix SPR 101137: WindView upload task priority and stacksize
             should be parameters
15dec04,md   Moved ED&R stub init to be after clock is initialised
11nov04,job  Added usrScInit init group for system call initialization
11nov04,aeg  moved INCLUDE_KERNEL to FOLDER_KERNEL (SPR #104076).
26oct04,fr   added INCLUDE_OBJ_OPEN, INCLUDE_SEM_OPEN, INCLUDE_MSG_Q_OPEN,
             INCLUDE_TASK_OPEN, and INCLUDE_TIMER_OPEN (SPR 101491)
13oct04,dlk  Added NBIO_LOG.
12oct04,kk   renamed kernelBaseLib.h to private/kernelBaseLibP.h
11oct04,jn   Change name of INCLUDE_ABS_SYMBOLS to INCLUDE_OFFSET_SYMBOLS
08oct04,yvp  Added INCLUDE_SET to FOLDER_UTILITIES (SPR 102389).
01oct04,fr   added component INCLUDE_HANDLE_SHOW (SPR 99750)
30sep04,job  Renamed INCLUDE_RTP_KERNEL to INCLUDE_BASE_KERNEL
30sep04,tam  replaced INCLUDE_EDR_KH by INCLUDE_KERNEL_HARDENING
29sep04,zl   removed MMU_MPU component.
29sep04,jn   Fix problem with symbol table config param
23sep04,jn   Make INCLUDE_NET_SYM_TBL require INCLUDE_NET_INIT
20sep04,bwa  added usrDsiInit to usrRoot init order.
13sep04,kk   renamed rtpBaseLib components
31aug04,fr   added component INCLUDE_SEM_INFO (SPR 100038)
06sep04,jmp  Added missing MAX_ISR_JOBS parameter declaration.
             Fixed typo in usrIosExtraInit InitGroup.
06sep04,dbt  Added JOB_TASK_STACK_SIZE parameter declaration in
             components.
03sep04,ans  added INCLUDE_JOB_TASK and updated excInit () parameter list
26aug04,md   Added EDR_RECORD_SIZE
08sep04,jyo  Fixing SPR 100119: Removing references to RT11.
23aug04,job  Prototype better POSIX system call scalability.
             Prototype of no symbol table when INCLUDE_RTP
28jul04,md   removed INCLUDE_EDR_SYMBOLIC, make INCLUDE_EDR_STUB hidden
06jul04,dtr  Adding in AIM configuration and optimization.
30jun04,job  Added prototypes to INCLUDE_POSIX_CLOCKS and INCLUDE_SC_POSIX
             INCLUDE_SC_POSIX is include when INCLUDE_POSIX_CLOCKS
             as this component fundamentally relies on the init routine
             being called.
28jun04,kk   add SIGEVENT to FOLDER_NOT_VISIBLE
24jun04,zl   added INCLUDE_POOL to utilities folder
24jun04,elg  Fix typo (SPR #98363).
22jun04,pad  Made INCLUDE_SC_POSIX included when both INCLUDE_RTP and
             INCLUDE_POSIX_TIMERS are included (SPR 98349).
21jun04,md   re-arrange ED&R components
11jun04,dcc  added INIT_RTN to INCLUDE_POSIX_CLOCKS (SPR 97847)
09jun04,zl   renamed INCLUDE_MMU_FULL_SHOW to INCLUDE_VM_SHOW.
06may04,lei  added component INCLUDE_MSG_Q_INFO (SPR 81966).
07jun04,elg  Remove call to usrWdbInit init group.
02jun04,bpn  Moved loader component to 01loader.cdf.
12may04,dbt  Added support for WDB Modules & Symbols Synchronization.
29apr04,elg  Include ED&R policies when WDB exception notification is
             included.
02may04,jkf  fixed SPR#90062
27apr04,tcr  change references to WindView to 'System Viewer'
29apr04,h_k  removed DSP component.
02may04,jkf  fixed SPR#90062
27apr04,tcr  change references to WindView to 'System Viewer'
21apr04,dat  moving selectInit after iosInit. Moved HW_FP, SW_FP, DSP, and
             SET out of usrIosCoreInit, and into usrRoot. (96540)
01apr04,dat  adding MEMDRV, PTYDRV, TYLIB (93390, 6294)
18mar04,dat  adding components for poolLib, poolShow, and setLib
21apr04,cjj  Added WIND_JOBS_MAX parameter.  Cleaned up history version
             numbers back to 04d.
06mar04,dat  adding absSymbols to linkSyms, remove underscore (95052)
25feb04,yvp  Added INCLUDE_RTP_APPL to InitGroup usrRoot.
12feb04,dat  chg init order for POSIX_AIO, to IosExtraInit
11feb04,bpn  Moved the shell components to shell CDF files.
28jan04,elg  Move WDB components to 00wdb.cdf.
23jan04,fle  Made INCLUDE_SHOW_ROUTINES belong to the FOLDER_SHOW_ROUTINES
             folder
16jan04,syy  replaced WVNET component with WVNETD
15dec03,rp   corrected password
08dec03,m_s  added SC_POSIX to FOLDER_POSIX
06dec03,dat  making select support component invisible to users
02dec03,bwa  removed all MsgC/S references
10nov03,kk   added INCLUDE_SHOW_ROUTINES component, clean up inclusion
             of show routines and model after BSP build.
30oct03,dat  new posix dirLib component, sprs 22056/74198
22oct03,ans  added INIT_RTN to INCLUDE_POSIX_TIMERS
22oct03,dat  moved SC_xxx comps to 01rtp.cdf. Cleanup of RTP comp
             attributes Created FOLDER_NOT_VISIBLE as a placeholder for
             components that are not visible to the user. New RTP_KERNEL,
             CLASS_LIB components for startup requirements.
22oct03,ans  added INIT_RTN to INCLUDE_POSIX_TIMERS
16oct03,ans  added INCLUDE_SC_POSIX , INCLUDE_SIGEVENT; INCLUDE_POSIX_TIMERS
             intialized in usrKernelExtraInit.
14oct03,dbs  force INCLUDE_TEXT_PROTECT when EDR KH is included
10oct03,bpn  Moved kernel shell components to 00shell.cdf.
08oct03,tam  moved usrRtpInit before INCLUDE_MMU_BASIC; moved
             INCLUDE_OBJ_LIB to usrKernelInit()
06oct03,tcr  change trigger init func; limit number of WV logs
03oct03,dbs  add ED&R KH support
29sep03,pad  Reworked the inclusion logic for INCLUDE_SC_MMAN and
26sep03,dbs  add ED&R policies
25sep03,rp   merging from bas6_itn2_networking to base6_itn2
25sep03,rp   merging from bas6_itn2_networking to base6_itn2
             INCLUDE_SC_KERNEL. They no longer appear as individually
             selectable components and are now automatically dragged in
             when INCLUDE_RTP is selected.
22sep03,bpn  Updated shell components. Added command folder,
             INCLUDE_RTP_SHELL_CMD and INCLUDE_DISK_UTIL_SHELL_CMD
             components. Set default shell line length to 256 characters.
             Added SHELL_CONFIG parameter. Set vi as the default editing
             mode.
19sep03,pad  Added Parameters TASK_USER_EXC_STACK_SIZE,
             TASK_STACK_OVERFLOW_SIZE and TASK_STACK_UNDERFLOW_SIZE. Moved
             usrRtpInit earlier in the initialization sequence.
12sep03,dbs  move ED&R init as early as possible
10sep03,dbs  add ED&R config params and edrStub component
05sep03,tcr  change initialization of WindView upload
03sep03,elg  added WDB_END_DEVICE_NAME and WDB_END_DEVICE_UNIT parameters.
21aug03,zl   added INCLUDE_SC_MMAN component.
21aug03,dcc  added INCLUDE_SC_KERNEL component.
19aug03,kk   added INCLUDE_RTP_SHOW to SHOW folder.
27aug03,elg  Add INCLUDE_WDB_RTP component.
18aug03,dbs  rework ED&R show routines
08aug03,dbs  add enhanced ED&R show routines
04aug03,dbs  ensure pmLib has no globals
31jul03,dbs  add separate edrShow component
22jul03,jmp  added INCLUDE_PASSFS_SYM_TBL to usrToolsInit().
22jul03,bpn  Added INCLUDE_SHELL_INTERP_CMD component.
16jul03,dbs  add edrLib initialization
14jul03,dbs  rename phpLib to pmLib
09jul03,dbs  add ED&R components
09jul03,bpn  Updated shellInterpRegister() API.
08jul03,bpn  Updated shell components.
02jul03,md   Added INCLUDE_ROMFS components.
27jun03,bwa  added filename comment; corrected typos;
             updated following code review
10apr03,elg  Add WDB_COMM_PORT to configure WDB port.
31mar03.bpn  Added a new parameter SHELL_COMPATIBLE to the shell, for
             compatibility with vxWorks 5.5.
20mar03.bpn  Changed ledRegister() to ledModeRegister().
17mar03,lcs  Modified ledLib initialization code.
05mar03,bpn  Modified the C interpreter registering name.
18feb03,bpn  Modified the target shell component. Added new components for
             the interpreter and for the line editing mode. Added new
             parameters for the shell.
31jan03,tor  Mount filesystems at boot time (spr #69254)
08nov02,dbt  Improved dependencies between WDB components (SPR #79259)
22jun02,gls  reversed order of INCLUDE_MEM_MGR_FULL and
             INCLUDE_MEM_MGR_BASIC in usrRoot() (SPR #78999)
29may02,dat  Fix header file for SELECT, 78096
15may02,j_s  make INCLUDE_SPY require INCLUDE_AUX_CLK
08may02,sn   SPR 76322 - pull in demangler if C++ and the symbol table are
             included
27mar02,jkf  SPR#74716, moved INCLUDE_DISK_UTIL from DOSFS into IO folder
19mar02,sn   SPR 71699 - remove cplusLoad.o from INCLUDE_CPLUS_DEMANGLER
             (cplusLoad.o and cplusUsr.o are part of the targe loader)
19mar02,j_s  Delist bufLib.o as a module of INCLUDE_WDB, add INCLUDE_BUF_MGR
             to REQUIRES of INCLUDE_WDB (SPR #73477)
13mar02,rbl  fixing bug where EXC_SHOW component appeared in two folders
12mar02,jkf  SPR#74178, adding CDROMFS to iosextra init group.
11mar02,sn   Wind Foundation classes no longer supported (SPR #73967)
06mar02,sn   Removed INCLUDE_GNU_64BIT (obsoleted by INCLUDE_GNU_INTRINSICS)
04mar02,j_s  fix the typo 'SELECT_SYMTBL_INIT', should be
             'SELECT_SYM_TBL_INIT'
05feb02,sn   Added SELECT_COMPILER_INTRINSICS
29jan02,g_h  Add INCLUDE_WDB_COMM_VTMD to SELECT_WDB_COMM_TYPE
28jan02,sn   added (); to cplusCtorsLink; added INCLUDE_CTORS_DTORS to InitGroup
25jan02,zl   removed cplusGlob.o from INCLUDE_CTORS_DTORS
21jan02,sn   added INCLUDE_CTORS_DTORS
09dec01,jac  added INCLUDE_CDROMFS component
30nov01,sbs  Synopsis to NUM_FILES about FD_SETSIZE (SPR 9377)
20nov01,bwa  Changed INCLUDE_EVENTS to INCLUDE_VXEVENTS
12nov01,mas  made new components for SM_OBJ, SM_NET, and SM_COMMON
05nov01,gls  added INCLUDE_POSIX_PTHREADS
06nov01,sn   moved toolchain specific C++ stuff to toolchain subdirectories
31oct01,tcr  add Windview network instrumentation component
22oct01,sn   Added catch-all compiler intrinsics components
11oct01,bwa  Corrected MODULE field for VxWorks events.
11oct01,mas  cfg params: added new ones to, and deleted duplicates from,
             INCLUDE_SM_OBJ (SPR 4547, 62128)
10oct01,fmk  add configlette to INCLUDE_CPLUS and change name of init
             routine to match
09oct01,bwa  Added VxWorks events module
26sep01,jws  changed default for SM_OBJ_MAX_TRIES to 5000 (SPR 68418)
20sep01,aeg  added the INCLUDE_SELECT_SUPPORT component.
13sep01,pcm  added INCLUDE_EXC_SHOW (SPR 7333), INCLUDE_LSTLIB (SPR 20698)
09may01,ros  fix codetest
17may01,rec  SPR 63492 - cache not enabled from project
10jan01,sn   Specify configlettes for toolchain related/C++ components
             Changed C++ stdlib defaults to exclude complex and include STL
             extract core iostreams modules from full iostreams
05dec00,sn   Fix definition of INCLUDE_CPLUS_STL
11oct00,sn   Use modules instead of linksyms for the C++ comps
01dec00,cmf  changed name of INCLUDE_PCI_SHOW to INCLUDE_PCI_CFGSHOW to
             match T3 naming
24aug00,pai  corrected INCLUDE_PCI_SHOW component fix (SPR #27759).
19may00,pai  added INCLUDE_PCI_SHOW component (SPR #27759).
11oct99,pai  changed software and hardware floating point init order (SPR
             28624).
16nov00,zl   added DSP related components.
18oct00,rsh  remove obsolete ctOperateroNew.o reference
27jul00,rsh  fix up MODULES define for CodeTEST component to reflect that
             fact that we are now archiving in the individual .o's instead
             of a single relatively linked .o (.a)
14jun00,mnd  Changed INCLUDE_CODETEST MODULES from ctLib to libctSwic.a.
20apr00,mnd  Changed CodeTEST include component to ctLib. Removed older
             modules cttXdr.o, cttOperatorNew.o, cttTargetLib.o, no longer
             needed. Updating the file for CodeTEST 2.11 integration with
             Tornado 2.0.
01apr99,cjs  Correct symbol table initialization logic so that removing
             the symtab init component removes the selection as well
24mar99,cjs  broke apart symbol table initialization so that symbol
             table can be included w/o initialization
17mar99,pr   added ataShow routines (SPR #25777)
10mar99,pr   added trgShow and rBuffShow components (SPR #25417)
26feb99,cjs  Fix defaults for SELECT_WDB_COMM_TYPE, SELECT_WDB_MODE
23feb99,cth  reordering init order in usrIosExtraInit (SPR 24297)
             added INCLUDE_MEM_SHOW component (SPR 24371)
             removed extra PROTOTYPE from usrInit
19jan99,pr   deleted INCLUDE_WHEN entry in INCLUDE_SEQ_TIMESTAMP (SPR 23630)
15jan99,dbt  added some help references for WDB components.
24nov98,pr   added dependencies between INCLUDE_WVUPLOAD_TSFSSOCK and
             INCLUDE_WDB_TSFS
19nov98,pr   added INCLUDE_WVUPLOAD_TSFSSOCK to windview upload defaults
04nov98,ms   changed some LINK_SYMS to LINK_DATASYMS so SIMHP works.
21oct98,ms   added INCLUDE_CODETEST component
20oct98,ms   added INCLUDE_WHEN for SEQ_TIMESTAMP and RBUFF components
11oct98,ms   cplusUsr.o no longer part of INCLUDE_CPLUS_MANGLER
30sep98,pr   added TRIGGERING component descriptor
30sep98,ms   folded in pr's WINDVIEW component descriptors
15sep98,ms   fixed errors uncovered by new cxrDocValidate
14sep98,ms   removed INCLUDE_EXC_SHOW (it's now part of EXC_HANDLING)
08sep98,sn   removed TRAP_DEBUG parameter
02sep98,sn   Fixed up C++ dependencies
19aug98,ms   Fixed INCLUDE_CPLUS_STRING - append "_" to _cstringi_o
19aug98,sut  Moved BSP components to 00bsp.cdf
19aug98,jmp  fixed typo in INCLUDE_WDB_VIO_LIB SYNOPSIS.
23aug98,ms   INCLUDE_SHELL now REQUIRES SELECT_SYMTBL_INIT.
23aug98,sut  changed some BSP components
14aug98,ms   added proper DEFAULTS to most folders
12aug98,ms   fixed initialization order of WDB agent
07aug98,cjs  fixed a spelling mistake in a component synopsis
03jun98,ms   lots of cleanup.
03jun98,sn   updated C++ components
03jun98,dbt  completed WDB components
21may98,ms   SYM_TBL_INIT and SYM_TBL are now only under one folder
09apr98,ms   written
*/

/*
DESCRIPTION
This file contains descriptions for some VxWorks components.
The configuration tool searches for .cdf files in four
places; here, arch/<arch>, config/<bsp>, and the project directory.
This file describes "generic" components which are available
to all CPU architectures and BSPs.
If a new component is released, a new .cdf file should be deposited
in the appropriate directory, rather than modifying existing files.

INTERNAL
add in windview
"Precious" Components (like the kernel!) that can't be deleted.
Folder-precious components (like wdbCore), that can't be deleted
without deleting the whole folder.
*/

Profile PROFILE_OS_DEFAULT {
        NAME            Default operating system profile
        SYNOPSIS        This profile includes the default operating system \
                        components and parameters.
        COMPONENTS      INCLUDE_BANNER
        PROFILES        PROFILE_OS_PARAMETER_VALUES
}

#ifdef _WRS_CONFIG_SMP
#ifndef _WRS_CONFIG_CERT
Profile PROFILE_OS_DEFAULT {
    COMPONENTS  +=  INCLUDE_SPINLOCK_ISR_ND
}
#endif /* !_WRS_CONFIG_CERT */
#endif /* _WRS_CONFIG_SMP */

Profile PROFILE_OS_PARAMETER_VALUES {
        NAME            Default operating system parameter profile
        SYNOPSIS        This profile includes the default operating system \
                        parameters.
        PARAMETER_VALUES { MAX_REBOOT_HOOKS 8 } { TYLIB_WRT_THRESHLD 20 }
}

Component INCLUDE_CPU_INIT {
        NAME            CPU library support
        SYNOPSIS        This component includes CPU library support.
        CONFIGLETTES    usrAimCpu.c
        PROTOTYPE       void usrAimCpuInit (void);
        INIT_RTN        usrAimCpuInit ();
}

List    UNAVAILABLE_LIST {
        NAME List of components that are not available
}

List    ERROR_LIST {
        NAME List of components that have errors
}

Component INCLUDE_VXCPULIB {
        NAME            CPU identification initialization
        SYNOPSIS        This component enables the initialization of the CPU \
                        identification functions.
        PROTOTYPE       extern void vxCpuLibInit (void);
        INIT_RTN        vxCpuLibInit ();
        _CHILDREN       FOLDER_KERNEL
}

Component INCLUDE_OFFSET_SYMBOLS {
        NAME            Absolute symbol offsets for host tools
        SYNOPSIS        This component includes the symbol offsets required by \
                        the host tools.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         offsets.o
#endif
        HDR_FILES       private/offsetsP.h
        LINK_SYMS       absSymbols_Common
/* Can't use _WRS_ABS_SYMBOL, because linkSyms doesn't include headers */
}

Selection SELECT_EDR_POLICY {
        NAME            Fatal policy handler
        SYNOPSIS        Selects a fatal error handling policy. This allows you \
                        to select the kernel-provided default fatal error \
                        handling policy or a custom user-defined fatal error \
                        handling policy.
        COUNT           1-1
        CHILDREN        INCLUDE_EDR_DEFAULT_POLICY \
                        INCLUDE_EDR_CUSTOM_POLICY
#ifdef _WRS_CONFIG_CERT
        DEFAULTS        INCLUDE_EDR_CUSTOM_POLICY
#else
        DEFAULTS        INCLUDE_EDR_DEFAULT_POLICY
#endif
}

Component INCLUDE_EDR_STUB {
        NAME            ED&R stub
        SYNOPSIS        This component provides the error detection and \
                        reporting (ED&R) error-injection stub.
        INIT_RTN        edrStubInit ();
        REQUIRES        SELECT_EDR_POLICY
        CONFIGLETTES    edrStub.c
}

Component INCLUDE_EDR_DEFAULT_POLICY {
        NAME            Error handler
        SYNOPSIS        This component adds the default set of fatal policy \
                        handlers defined by the kernel.
        CONFIGLETTES    edrDefaultPolicy.c
}

Component INCLUDE_EDR_CUSTOM_POLICY {
        NAME            Custom error handler
        SYNOPSIS        This component includes a custom fatal error handler \
                        policy. When this component is selected, the fatal \
                        errors are no longer handled by the kernel. The kernel \
                        default fatal policy handler functions are replaced by a \
                        similar set of stub fatal policy handler functions \
                        available to you in the edrCustomPolicy.c file in \
                        the VxWorks image project (VIP). It is your \
                        responsibility to add code that handles the \
                        fatal errors. Note: The features provided by the \
                        components INCLUDE_CORE_DUMP, INCLUDE_CORE_DUMP_RTP, and \
                        INCLUDE_INCLUDE_STOP_MODE_AGENT are no longer \
                        available by default. If you need these features, \
                        then the code corresponding to those features from the \
                        default fatal policy handlers (in the edrDefaultPolicy.c \
                        configlette file) needs to be ported into the \
                        custom policy handlers in the edrCustomPolicy.c file.
        USR_CONFIGLETTE edrCustomPolicy.usrConfig
}

Component INCLUDE_EDR_POLICY_HOOKS {
        NAME            ED&R policy hooks
        SYNOPSIS        This component provides policy hooks function support \
                        for error detection and reporting.
        REQUIRES        INCLUDE_EDR_STUB
}

Component INCLUDE_SYS_START {
        NAME            System startup code
        SYNOPSIS        This component clears BSS and sets up the vector table \
                        base address.
        INIT_RTN        sysStart (startType);
        CONFIGLETTES    usrStartup.c
        CFG_PARAMS      CLEAR_BSS
        HDR_FILES       intLib.h string.h
        INCLUDE_WHEN    INCLUDE_KERNEL
}

Parameter CLEAR_BSS {
        NAME            Clear BSS at system startup (recommended)
        TYPE            exists
        DEFAULT         TRUE
}

/* Invisible component folder. exists only to suppress warnings */

Folder  FOLDER_HIDDEN {
        NAME            Hidden, invisible components
}

Folder  FOLDER_NOT_VISIBLE {
        NAME            Invisible, unremovable components
        CHILDREN        INCLUDE_BASE_KERNEL             \
                        INCLUDE_SYS_START               \
                        INCLUDE_SELECT_SUPPORT          \
                        INCLUDE_OFFSET_SYMBOLS          \
                        INCLUDE_CLASS_LIB               \
                        INCLUDE_CLASS_LIST              \
                        INCLUDE_EDR_STUB                \
                        INCLUDE_PROCFS                  \
                        INCLUDE_SEM_LIB                 \
                        INCLUDE_CBIO                    \
                        INCLUDE_DISK_PART               \
                        INCLUDE_CHECKSUM                \
                        INCLUDE_TASK_SWAP_HOOKS
        DEFAULTS        INCLUDE_BASE_KERNEL             \
                        INCLUDE_OFFSET_SYMBOLS          \
                        INCLUDE_CLASS_LIB               \
                        INCLUDE_EDR_STUB                \
                        INCLUDE_SEM_LIB                 \
                        INCLUDE_TASK_SWAP_HOOKS
}

Folder  FOLDER_ROOT {
        NAME            All components
        CHILDREN        FOLDER_APPLICATION      \
                        FOLDER_TOOLS            \
                        FOLDER_NETWORK          \
                        FOLDER_SECURITY         \
                        FOLDER_CPLUS            \
                        FOLDER_OS               \
                        FOLDER_OBSOLETE         \
                        FOLDER_HARDWARE         \
                        FOLDER_SSI              \
                        FOLDER_STORAGE
        DEFAULTS        FOLDER_TOOLS            \
                        FOLDER_NETWORK          \
                        FOLDER_SECURITY         \
                        FOLDER_OS               \
                        FOLDER_HARDWARE
}

Folder FOLDER_SECURITY {
        NAME            Security
        SYNOPSIS        This folder contains components and parameters \
                        concerning the security for your VxWorks project.
}

Folder FOLDER_STORAGE {
        NAME            Storage
        SYNOPSIS        This folder contains components and parameters related \
                        to storage, such as file systems and device management.
}

Folder  FOLDER_OS {
        NAME            Operating system
        SYNOPSIS        This folder contains components and parameters related \
                        to the operating system.
        CHILDREN        FOLDER_IO_SYSTEM        \
                        FOLDER_KERNEL           \
                        FOLDER_EDR              \
                        FOLDER_ANSI             \
                        FOLDER_POSIX            \
                        FOLDER_RANDOM_NUM_GEN   \
                        FOLDER_UTILITIES        \
                        FOLDER_SERVICE          \
                        FOLDER_PWR_MGMT
        DEFAULTS        FOLDER_IO_SYSTEM        \
                        FOLDER_KERNEL           \
                        FOLDER_EDR              \
                        FOLDER_ANSI             \
                        FOLDER_SERVICE          \
                        FOLDER_UTILITIES
}

Folder  FOLDER_OBSOLETE {
        NAME            Obsolete components
        SYNOPSIS        Will be removed next release
        CHILDREN        INCLUDE_TYCODRV_5_2
}

Folder  FOLDER_TOOLS {
        NAME            Development tools
        SYNOPSIS        This folder contains components and parameters used to \
                        configure different development tools.
        CHILDREN        FOLDER_SHOW_ROUTINES    \
                        INCLUDE_SPY             \
                        INCLUDE_TIP             \
                        INCLUDE_TIMEX           \
                        INCLUDE_VXDBG           \
                        FOLDER_SYSTEMVIEWER     \
                        SELECT_COMPILER_INTRINSICS \
                        FOLDER_KERNEL_DEBUG
        DEFAULTS
}

Component INCLUDE_BLIB {
        NAME            Buffer manipulation function library
        SYNOPSIS        This component includes the buffer manipulation \
                        function library.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         bLib.o
#endif
        REQUIRES        INCLUDE_ANSI_STRLEN
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_BMPLIB {
        NAME            Bit first get function
        SYNOPSIS        This component includes the bit first get function. \
                        The bitFirstGet() function generalizes the ability to \
                        "find the first set bit" in a machine word by \
                        supporting an arbitrarily large number of bits.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         bmpLib.o
#endif
        LINK_SYMS       bitFirstGet
        REQUIRES        INCLUDE_KERNEL
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Folder  FOLDER_POSIX {
        NAME            POSIX
        SYNOPSIS        This folder contains components and parameters that \
                        can be used to include and configure different \
                        Portable Operating System Interface (POSIX) \
                        facilities in your project.
        CHILDREN        INCLUDE_POSIX_AIO       \
                        INCLUDE_POSIX_AIO_SYSDRV \
                        INCLUDE_POSIX_FTRUNC    \
                        INCLUDE_POSIX_MEM       \
                        INCLUDE_POSIX_MQ        \
                        INCLUDE_POSIX_PTHREADS  \
                        INCLUDE_POSIX_SCHED     \
                        INCLUDE_POSIX_SEM       \
                        INCLUDE_POSIX_SIGNALS   \
                        INCLUDE_POSIX_TIMERS    \
                        INCLUDE_POSIX_DIRLIB    \
                        INCLUDE_POSIX_CLOCKS    \
                        INCLUDE_SIGEVENT        \
                        INCLUDE_POSIX_UMASK     \
                        INCLUDE_POSIX_USER_GROUP
        DEFAULTS        INCLUDE_POSIX_AIO               \
                        INCLUDE_POSIX_AIO_SYSDRV        \
                        INCLUDE_POSIX_FTRUNC            \
                        INCLUDE_POSIX_MQ                \
                        INCLUDE_POSIX_SEM               \
                        INCLUDE_POSIX_SIGNALS           \
                        INCLUDE_POSIX_TIMERS            \
                        INCLUDE_POSIX_CLOCKS            \
                        INCLUDE_POSIX_DIRLIB            \
                        INCLUDE_POSIX_PTHREADS
}

Component INCLUDE_POSIX_USER_GROUP {
        NAME            User and group support
        SYNOPSIS        This component adds support for POSIX users and groups \
                        in the kernel environment.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         pxUserGroupLib.o
#endif
        PROTOTYPE       extern STATUS pxUserGroupLibInit (void);
        INIT_RTN        pxUserGroupLibInit();
}

Component INCLUDE_POSIX_UMASK {
        NAME           File mode creation mask support
        SYNOPSIS       This component adds support for the POSIX file mode \
                       creation mask in the kernel environment. That is, it \
                       supports the unmask() function.
        MODULES        umaskLib.o
        PROTOTYPE      extern STATUS umaskLibInit (int);
        CFG_PARAMS     UMASK_DEFAULT
        INIT_RTN       umaskLibInit(UMASK_DEFAULT);
}

Parameter UMASK_DEFAULT {
        NAME        Default value of umask
        SYNOPSIS    The parameter specifies the default value of the file \
                    mode creation mask.
        DEFAULT     022
}

Component INCLUDE_POSIX_MEM {
        NAME            Memory paging functions
        SYNOPSIS        This component provides the null-wrappers for the \
                        POSIX memory paging functions.
        MODULES         mmanPxLib.o
        LINK_SYMS       mlockall
        HDR_FILES       sys/mman.h
}

Component INCLUDE_POSIX_MQ {
        NAME            Message queues
        SYNOPSIS        This is the primary component for support of the \
                        message queue POSIX facility for both the kernel and \
                        RTPs. POSIX message queues are similar to VxWorks \
                        message queues, except that POSIX message queues \
                        provide messages with a range of priorities. For \
                        more information, see the POSIX facilities section \
                        in the VxWorks 7 Programmer's Guide.
        MODULES         mqPxLib.o
        INIT_RTN        mqPxLibInit (MQ_HASH_SIZE);
        CFG_PARAMS      MQ_HASH_SIZE
        HDR_FILES       private/mqPxLibP.h
        REQUIRES        INCLUDE_OBJ_OPEN
}

Component INCLUDE_POSIX_PTHREADS {
        NAME            Threads
        SYNOPSIS        This component includes support for POSIX threads in \
                        the kernel.
        MODULES         pthreadLib.o _pthreadLib.o
        INIT_RTN        pthreadLibInit ();
        HDR_FILES       private/pthreadLibP.h
        REQUIRES        INCLUDE_TASK_OPEN
}

Component INCLUDE_POSIX_SCHED {
        NAME            Process scheduling
        SYNOPSIS        This component provides kernel-only emulation of the \
                        process scheduling API. This component \
                        is used to include the schedPxLib library.
        MODULES         schedPxLib.o
        LINK_SYMS       sched_setparam
        HDR_FILES       sched.h
}

Component INCLUDE_POSIX_SEM {
        NAME            Semaphores
        SYNOPSIS        This component provides support for the POSIX semaphore functions \
                        provided by semPxLib. sem_init() initializes an unnamed semaphore. \
                        sem_destroy() destroys an unnamed semaphore. sem_open() initializes \
                        or opens a named semaphore. sem_close() closes a named semaphore. \
                        sem_unlink() removes a named semaphore. sem_wait() locks a semaphore. \
                        sem_trywait() locks a semaphore only if it was not already locked. \
                        sem_post() unlocks a semaphore. sem_getvalue() gets the value of a semaphore. \
                        sem_timedwait() locks a semaphore with a timeout. The timeout \
                        is based on the CLOCK_REALTIME clock.
        MODULES         semPxLib.o
        INIT_RTN        semPxLibInit ();
        HDR_FILES       classLib.h private/semPxLibP.h
        REQUIRES        INCLUDE_OBJ_OPEN \
                        INCLUDE_SEM_COUNTING_CREATE
}

Component INCLUDE_POSIX_SIGNALS {
        NAME            Signals
        SYNOPSIS        This component automatically initializes POSIX queued \
                        signals with sigqueueInit(). The sigqueueInit() \
                        function allocates buffers for use by sigqueue(), \
                        which requires a buffer for each currently queued \
                        signal. A call to sigqueue() fails if no buffer is \
                        available.
        INIT_RTN        sigqueueInit (NUM_SIGNAL_QUEUES);
        CFG_PARAMS      NUM_SIGNAL_QUEUES
        HDR_FILES       private/sigLibP.h
}

Component INCLUDE_SIGEVENT {
        NAME            Asynchronous events notification library
        SYNOPSIS        This component provides kernel signal event support. \
                        This is required for SIGEV_THREAD support in an RTP.
        MODULES         sigeventLib.o
        PROTOTYPE       extern int sigeventLibInit (void);
        INIT_RTN        sigeventLibInit ();
        HDR_FILES       sigevent.h
        REQUIRES        INCLUDE_SIGNALS
        _CHILDREN       FOLDER_POSIX
}

Component INCLUDE_POSIX_TIMERS {
        NAME            Timers
        SYNOPSIS        This component provides support for POSIX timers.
        MODULES         timerLib.o
        INIT_RTN        timerLibInit ();
        LINK_SYMS       nanosleep
        HDR_FILES       time.h private/timerLibP.h
        REQUIRES        INCLUDE_SIGEVENT INCLUDE_SIGNALS INCLUDE_POSIX_CLOCKS
}

Component INCLUDE_POSIX_CLOCKS {
        NAME            Clocks
        SYNOPSIS        This component includes support for POSIX clocks.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         clockLib.o
#endif
        HDR_FILES       private/timerLibP.h
        CFG_PARAMS      HIGH_RES_POSIX_CLOCK    \
                        POSIX_CLOCK_TIMER
        INIT_RTN        clockLibInit (HIGH_RES_POSIX_CLOCK, POSIX_CLOCK_TIMER);
        REQUIRES        INCLUDE_KERNEL   \
                        INCLUDE_FORMATTED_OUT_BASIC
}

Parameter HIGH_RES_POSIX_CLOCK {
        NAME            High resolution clock
        SYNOPSIS        Use the native timer frequency for CLOCK_REALTIME \
                        instead of system ticks. This option is not supported \
                        on simulators and has no effect.
        TYPE            BOOL
        DEFAULT         FALSE
}

Parameter POSIX_CLOCK_TIMER {
        NAME            Timer used with the high resolution POSIX clock
        SYNOPSIS        This parameter specifies the timer to use in \
                        association with HIGH_RES_POSIX_CLOCK. If left NULL, \
                        the next available timer with the highest frequency is \
                        used.
        TYPE            char *
        DEFAULT         NULL
}

Component INCLUDE_POSIX_DIRLIB {
        NAME            Directory utilities
        SYNOPSIS        Includes the POSIX directory utilities.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         dirLib.o
#endif /* !_WRS_CONFIG_CERT_KERNEL_OBJECT */
#ifndef _WRS_CONFIG_CERT
        LINK_SYMS       opendir
#else /* _WRS_CONFIG_CERT */
        INIT_RTN        dirLibInit (NUM_FILES);
#endif /* _WRS_CONFIG_CERT */
        REQUIRES        INCLUDE_IO_SYSTEM \
                        INCLUDE_MEM_MGR_BASIC
}

Component INCLUDE_POSIX_TIMER_SHOW {
        NAME            POSIX timer show routine
        SYNOPSIS        This component includes a utility that allows the user to display \
                        a snap shot of the selected timer. It provides the timer_show() \
                        function which shows information on a specified timer. It \
                        requires INCLUDE_POSIX_TIMERS.
        MODULES         timerShow.o
        INIT_RTN        timerShowInit();
        HDR_FILES       time.h
        INCLUDE_WHEN    INCLUDE_OBJ_INFO \
                        INCLUDE_SHOW_ROUTINES
        REQUIRES        INCLUDE_POSIX_TIMERS \
                        INCLUDE_OBJ_INFO
}

/* default show routine are class and task show routines */

Component INCLUDE_SHOW_ROUTINES {
        NAME            Show routine
        SYNOPSIS        This component enables show routines for configured \
                        features including the generic object show utility, \
                        show().
}

Folder  FOLDER_SHOW_ROUTINES {
        NAME            Show routines
        SYNOPSIS        This folder contains different show routines that you \
                        can include in your project.
        CHILDREN        INCLUDE_CLASS_SHOW      \
                        INCLUDE_MEM_SHOW        \
                        INCLUDE_VM_SHOW         \
                        INCLUDE_MSG_Q_SHOW      \
                        INCLUDE_POSIX_AIO_SHOW  \
                        INCLUDE_POSIX_MQ_SHOW   \
                        INCLUDE_POSIX_SEM_SHOW  \
                        INCLUDE_POSIX_TIMER_SHOW\
                        INCLUDE_SEM_SHOW        \
                        INCLUDE_CONDVAR_SHOW    \
                        INCLUDE_STDIO_SHOW      \
                        INCLUDE_TASK_HOOKS_SHOW \
                        INCLUDE_TASK_SHOW       \
                        INCLUDE_WATCHDOGS_SHOW  \
                        INCLUDE_TRIGGER_SHOW    \
                        INCLUDE_RBUFF_SHOW      \
                        INCLUDE_DATACOLLECTOR_SHOW \
                        INCLUDE_HW_FP_SHOW      \
                        INCLUDE_EXC_SHOW        \
                        INCLUDE_EDR_SHOW        \
                        INCLUDE_ISR_SHOW        \
                        INCLUDE_POOL_SHOW       \
                        INCLUDE_HANDLE_SHOW     \
                        INCLUDE_OBJECT_SHOW     \
                        INCLUDE_SHOW_ROUTINES
        DEFAULTS        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_HW_FP_SHOW {
        NAME            Floating-point show routine
        SYNOPSIS        This component includes the fppArchShow library. This \
                        library provides the fppCtxShow() function that prints \
                        the contents of a task's floating-point registers.
        MODULES         aimFppShow.o
        INIT_RTN        aimFppShowInit ();
        HDR_FILES       fppLib.h
        INCLUDE_WHEN    INCLUDE_HW_FP \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_MSG_Q_SHOW {
        NAME            Message queue show routine
        SYNOPSIS        This component includes the msgQShow library in your \
                        project. This library provides functions to show \
                        message queue statistics, such as the task queuing \
                        method, messages queued, and receivers blocked. The \
                        msgQShowInit() function links the message queue show \
                        facility into the VxWorks system. It is called \
                        automatically when you include this component in your \
                        project. The msgQShow() function displays information \
                        about message queues.
        MODULES         msgQShow.o
        INIT_RTN        msgQShowInit ();
        REQUIRES        INCLUDE_MSG_Q_INFO
        INCLUDE_WHEN    INCLUDE_MSG_Q \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_SEM_SHOW {
        NAME            Semaphore show routine
        SYNOPSIS        This component includes the semShow library in your \
                        project. This library provides functions to show \
                        semaphore statistics, such as semaphore type, \
                        semaphore queuing method, tasks pended, and so forth. \
                        Functions in this library are meant to be used as \
                        debugging aids that display semaphore information to \
                        standard output. Due to the dynamic nature of \
                        semaphore operations, the information displayed may no \
                        longer be accurate by the time it is provided.
        MODULES         semShow.o
        INIT_RTN        semShowInit ();
        REQUIRES        INCLUDE_SEM_INFO
        INCLUDE_WHEN    INCLUDE_SEM_BINARY \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_CONDVAR_SHOW {
        NAME            Condition variable show routine
        SYNOPSIS        This component provides the conVarShow() function. This \
                        function can be used to show information about a \
                        conditional variable.
        MODULES         condVarShow.o
        INIT_RTN        condVarShowInit ();
        REQUIRES        INCLUDE_CONDVAR
        INCLUDE_WHEN    INCLUDE_SHOW_ROUTINES
}


Component INCLUDE_TASK_HOOKS_SHOW {
        NAME            Task hook show routine
        SYNOPSIS        This component provides support for the task hook show functions: \
                        taskHookShowInit() initializes the task hook show facility. \
                        taskCreateHookShow() shows the list of task create functions. \
                        taskDeleteHookShow() shows the list of task delete functions. \
                        taskSwitchHookShow() shows the list of task switch functions.
        MODULES         taskHookShow.o
        INIT_RTN        taskHookShowInit ();
        HDR_FILES       taskHookLib.h
        INCLUDE_WHEN    INCLUDE_TASK_HOOKS \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_WATCHDOGS_SHOW {
        NAME            Watchdog timer show routine
        SYNOPSIS        This component provides the wdShow library. This \
                        library provides functions to show watchdog statistics, \
                        such as watchdog activity, a watchdog function, and so \
                        forth. The wdShowInit() function links the watchdog \
                        show facility into the VxWorks system. It is called \
                        automatically when this component is included in your \
                        project. The wdShow() function shows information about \
                        a watchdog.
        MODULES         wdShow.o
        INIT_RTN        wdShowInit ();
        INCLUDE_WHEN    INCLUDE_WATCHDOGS \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_TASK_SHOW {
        NAME            Task show routine
        SYNOPSIS        This component provides functions to show task-related \
                        information, such as task status, register values, and \
                        so forth. Task information is crucial as a debugging \
                        aid and user-interface convenience during the \
                        development cycle of an application. The taskShow() \
                        and taskRegsShow() functions are used to display task \
                        information. It is important to keep in mind that \
                        tasks may change their state or even get deleted \
                        between the time the information is gathered and the \
                        time it is utilized. Information provided by these \
                        functions should therefore be viewed as a snapshot of \
                        the system, and not relied upon unless the task is \
                        consigned to a known state, such as suspended.
        MODULES         taskShow.o
        INIT_RTN        taskShowInit ();
        REQUIRES        INCLUDE_TASK_LIST
}

Component INCLUDE_MEM_SHOW {
        NAME            Memory show routine
        SYNOPSIS        This component includes the memShow library. This \
                        library contains memory partition information display \
                        functions. The memShow() function shows blocks and \
                        statistics for the current heap partition. The \
                        memPartShow() function shows available and allocated \
                        memory in the specified partition.
        MODULES         memShow.o
        INIT_RTN        memShowInit ();
        REQUIRES        INCLUDE_MEM_MGR_BASIC \
                        INCLUDE_MEM_MGR_INFO
        INCLUDE_WHEN    INCLUDE_MEM_MGR_BASIC \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_CLASS_SHOW {
        NAME            Class show routine
        SYNOPSIS        This component provides the classShow library which \
                        provides functions to show class-related information.
        MODULES         classShow.o
        INIT_RTN        classShowInit ();
        REQUIRES        INCLUDE_CLASS_LIST
        INCLUDE_WHEN    INCLUDE_CLASS_LIST \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_POSIX_MQ_SHOW {
        NAME            POSIX message queue show routine
        SYNOPSIS        This component provides the mqPxShow library. This \
                        library provides a show routine for displaying \
                        information on POSIX message queue objects. The \
                        information displayed is for debugging purposes and is \
                        intended to be a snapshot of the system at the time \
                        the call is made. The mqPxShow() function displays \
                        message queue internals. The mqPxShowInit() function \
                        initializes the POSIX message queue show facility.
        MODULES         mqPxShow.o
        INIT_RTN        mqPxShowInit ();
        HDR_FILES       mqPxShow.h
        INCLUDE_WHEN    INCLUDE_POSIX_MQ \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_POSIX_SEM_SHOW {
        NAME            POSIX semaphore show routine
        SYNOPSIS        When VxWorks is configured with this component, you \
                        can use the show() function from the shell (with the C \
                        interpreter) to display information about a POSIX \
                        semaphore. The show() function takes the semaphore ID \
                        as the argument.
        MODULES         semPxShow.o
        INIT_RTN        semPxShowInit ();
        HDR_FILES       semPxShow.h
        INCLUDE_WHEN    INCLUDE_POSIX_SEM \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_EDR_SHOW {
        NAME            ED&R show routine
        MODULES         edrShow.o
        INIT_RTN        edrShowInit ();
        HDR_FILES       edrLib.h
        REQUIRES        INCLUDE_EDR_ERRLOG
        INCLUDE_WHEN    INCLUDE_EDR_ERRLOG \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_ISR_SHOW {
        NAME            ISR object show routine
        SYNOPSIS        This component provides support for the isrShow() \
                        function. It shows information about an ISR object.
        PROTOTYPE       STATUS isrShowInit (void);
        INIT_RTN        isrShowInit ();
        MODULES         isrShow.o
}

Component INCLUDE_HANDLE_SHOW {
        NAME            Handle show routine
        SYNOPSIS        This component provides the handleShow library. This \
                        library provides functions to show handle information.
        MODULES         handleShow.o
        INCLUDE_WHEN    INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_OBJECT_SHOW {
        NAME            Object show routine
        SYNOPSIS        This component includes the objShow library. This \
                        library provides the objShowAll() function to show the \
                        contents of Wind objects. The generic object \
                        information is displayed directly by objShowAll(), \
                        while the class-specific information is displayed by \
                        the show routine registered for the class. The \
                        objShow() function is invoked to display the \
                        class-specific information. The objHandleShow() \
                        function shows information on the object referenced by \
                        an object handle. The objHandleTblShow() function \
                        shows information on an RTP's handle table.
        MODULES         objShow.o
        LINK_SYMS       objShowAll
        REQUIRES        INCLUDE_CLASS_LIST      \
                        INCLUDE_OBJ_LIB
        INCLUDE_WHEN    INCLUDE_CLASS_LIST      \
                        INCLUDE_OBJ_LIB         \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_JITTER_TOOL {
        NAME            Jitter measurement tool
        SYNOPSIS        This component provides a utility to measure task and \
                        interrupt response jitter.
        MODULES         jitterLib.o
        INIT_RTN        jitterLibInit ();
        PROTOTYPE       STATUS jitterLibInit (void);
        REQUIRES        INCLUDE_AUX_CLK INCLUDE_SYS_TIMESTAMP
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Folder  FOLDER_APPLICATION {
        NAME            Startup
        CHILDREN        FOLDER_RTP_STARTUP_FACILITY \
                        FOLDER_APPLICATION_INITIALIZATION
}

Folder  FOLDER_APPLICATION_INITIALIZATION {
        NAME            Application initialization
        CHILDREN        INCLUDE_USER_APPL \
                        INCLUDE_USER_PRE_KERNEL_APPL_INIT \
                        INCLUDE_USER_POST_KERNEL_APPL_INIT \
                        INCLUDE_USER_PRE_NETWORK_APPL_INIT
        DEFAULTS        INCLUDE_USER_APPL                        
}

Component INCLUDE_USER_APPL {
        NAME            4. Kernel entry point (default)
        SYNOPSIS        This component calls the initialization function for \
                        your application, usrAppInit() in your usrAppInit.c \
                        project file, after system start up.
        PROTOTYPE       extern void usrAppInit (void);
        INIT_RTN        usrAppInit ();
}

Component INCLUDE_USER_PRE_KERNEL_APPL_INIT {
        NAME            1. Pre-kernel initialization
        SYNOPSIS        This component calls the usrPreKernelAppInit() \
                        function in your usrAppInit.c project file. usrPreKernelAppInit() \
                        is called at the beginning of usrInit(), right after \
                        cacheLibInit(). That is, right after the board boots \
                        and before kernel initialization starts.
        PROTOTYPE       extern void usrPreKernelAppInit (void);
        INIT_RTN        usrPreKernelAppInit ();
}

Component INCLUDE_USER_POST_KERNEL_APPL_INIT {
        NAME            2. Post-kernel initialization
        SYNOPSIS        This component calls the usrPostKernelAppInit() function \
                        in your usrAppInit.c project file. usrPostKernelAppInit() is \
                        called right after usrKernelCreateInit(). That is, \
                        right after most of the kernel core features are \
                        enabled. The I/O system and network are not available \
                        at this point.
        PROTOTYPE       extern void usrPostKernelAppInit (void);
        INIT_RTN        usrPostKernelAppInit ();
}

Component INCLUDE_USER_PRE_NETWORK_APPL_INIT {
        NAME            3. Pre-network initialization
        SYNOPSIS        This component calls the usrPreNetworkAppInit() function \
                        in your usrAppInit.c project file. usrPreNetworkAppInit() is \
                        called right before the network is initialized. At \
                        this point, most of the core kernel features including \
                        the I/O system are available.
        PROTOTYPE       extern void usrPreNetworkAppInit (void); 
        INIT_RTN        usrPreNetworkAppInit ();
}

Component INCLUDE_BANNER {
        NAME            VxWorks banner
        SYNOPSIS        This component displays the Wind River banner on startup.
        CONFIGLETTES    usrBanner.c
        INIT_RTN        usrBanner ();
        REQUIRES        INCLUDE_FORMATTED_OUT_BASIC
}

Parameter BOOT_LINE_SIZE {
        NAME            Boot line size (bytes)
        SYNOPSIS        This parameter specifies the boot line size in bytes.
        DEFAULT         255
}

Parameter BOOT_LINE_ADRS {
        NAME            Boot line address
        SYNOPSIS        This parameter specifies the boot line (memory region) \
                        address.
        DEFAULT         (LOCAL_MEM_LOCAL_ADRS + BOOT_LINE_OFFSET)
}

Parameter BOOT_LINE_OFFSET {
        NAME            Boot line offset
        SYNOPSIS        This parameter specifies the boot line offset.
        DEFAULT         0x700
}

Parameter DEFAULT_BOOT_LINE {
        NAME            Default boot line
        SYNOPSIS        This parameter provides the default boot \
                        line string. It sets the default boot parameters at \
                        configuration time.
        TYPE            string
        DEFAULT         "ei(0,0)host:/usr/vw/config/bsp/vxWorks \
                        h=90.0.0.3 e=90.0.0.50 u=target"
}

Folder  FOLDER_KERNEL {
        NAME            Kernel
        SYNOPSIS        This folder contains the components and \
                        parameters used to configure the kernel environment.
        CHILDREN        INCLUDE_KERNEL          \
                        INCLUDE_BOOT_LINE_INIT  \
                        INCLUDE_EXC_HANDLING    \
                        INCLUDE_ISR_OBJECTS     \
                        SELECT_MEM_ALLOC        \
                        INCLUDE_MEM_MGR_FULL    \
                        INCLUDE_MEM_MGR_INFO    \
                        INCLUDE_OBJ_LIB         \
                        INCLUDE_OBJ_INFO        \
                        INCLUDE_OBJ_OWNERSHIP   \
                        INCLUDE_VXMEMPROBE_INIT \
                        INCLUDE_VXEVENTS        \
                        INCLUDE_SEM_BINARY      \
                        INCLUDE_SEM_MUTEX       \
                        INCLUDE_SEM_COUNTING    \
                        INCLUDE_SEM_READ_WRITE  \
                        INCLUDE_SEM_DELETE      \
                        INCLUDE_SEM_EXCHANGE    \
                        INCLUDE_SEM_BINARY_CREATE               \
                        INCLUDE_SEM_MUTEX_CREATE                \
                        INCLUDE_SEM_COUNTING_CREATE             \
                        INCLUDE_SEM_READ_WRITE_CREATE           \
                        INCLUDE_SEM_INFO        \
                        INCLUDE_SIGNALS         \
                        INCLUDE_MSG_Q           \
                        INCLUDE_MSG_Q_CREATE_DELETE     \
                        INCLUDE_MSG_Q_INFO              \
                        INCLUDE_WATCHDOGS               \
                        INCLUDE_WATCHDOGS_CREATE_DELETE \
                        INCLUDE_TASK_HOOKS              \
                        INCLUDE_TASK_CREATE_HOOKS       \
                        INCLUDE_TASK_SWITCH_HOOKS       \
                        INCLUDE_TASK_INFO       \
                        INCLUDE_TASK_LIST       \
                        INCLUDE_TASK_ROTATE     \
                        INCLUDE_TASK_UTIL       \
                        INCLUDE_ENV_VARS        \
                        INCLUDE_JOB_TASK        \
                        SELECT_KERNEL_SCHEDULER \
                        INCLUDE_REBOOT_HOOKS    \
                        INCLUDE_EXC_TASK        \
                        INCLUDE_TLS             \
                        INCLUDE_BANNER          \
                        INCLUDE_CONDVAR         \
                        INCLUDE_CPU_INIT        \
                        INCLUDE_POWER_OFF_HOOKS
        DEFAULTS        INCLUDE_KERNEL                  \
                        INCLUDE_EXC_HANDLING            \
                        INCLUDE_MEM_MGR_FULL            \
                        INCLUDE_MEM_MGR_INFO            \
                        INCLUDE_OBJ_LIB                 \
                        INCLUDE_SEM_BINARY              \
                        INCLUDE_SEM_MUTEX               \
                        INCLUDE_SEM_COUNTING            \
                        INCLUDE_SEM_BINARY_CREATE       \
                        INCLUDE_SEM_COUNTING_CREATE     \
                        INCLUDE_SEM_MUTEX_CREATE        \
                        INCLUDE_SEM_DELETE              \
                        INCLUDE_SIGNALS                 \
                        INCLUDE_MSG_Q                   \
                        INCLUDE_MSG_Q_CREATE_DELETE     \
                        INCLUDE_TASK_HOOKS              \
                        INCLUDE_TASK_UTIL               \
                        INCLUDE_WATCHDOGS               \
                        INCLUDE_WATCHDOGS_CREATE_DELETE \
                        INCLUDE_ENV_VARS                \
                        INCLUDE_EXC_TASK                \
                        INCLUDE_JOB_TASK                \
                        INCLUDE_TASK_CREATE_DELETE      \
                        INCLUDE_TASK_RESTART            \
                        INCLUDE_HOOKS                   \
                        INCLUDE_REBOOT_HOOKS            \
                        SELECT_KERNEL_SCHEDULER         \
                        INCLUDE_VXMEMPROBE_INIT         \
                        INCLUDE_BANNER
}

Component INCLUDE_KERNEL {
        NAME            Kernel
        SYNOPSIS        Context switch and interrupt handling. This is a \
                        required component. DO NOT REMOVE
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         kernelLib.o taskLib.o windLib.o schedLib.o workQLib.o \
                        tickLib.o rebootLib.o intLib.o ffsLib.o errnoLib.o
#endif
        CONFIGLETTES    usrKernel.c usrKernelStack.c usrRtpBaseLib.c
        INIT_RTN        usrKernelInit (VX_GLOBAL_NO_STACK_FILL);
        CFG_PARAMS      ROOT_STACK_SIZE         \
                        ISR_STACK_SIZE          \
                        INT_LOCK_LEVEL          \
                        TASK_USER_EXC_STACK_SIZE        \
                        TASK_KERNEL_EXC_STACK_SIZE      \
                        TASK_USER_EXC_STACK_OVERFLOW_SIZE       \
                        TASK_USER_EXEC_STACK_OVERFLOW_SIZE      \
                        TASK_USER_EXEC_STACK_UNDERFLOW_SIZE     \
                        TASK_KERNEL_EXEC_STACK_OVERFLOW_SIZE    \
                        TASK_KERNEL_EXEC_STACK_UNDERFLOW_SIZE   \
                        TASK_PRIORITY_SET_COMPATIBLE            \
                        WIND_JOBS_MAX                           \
                        VX_GLOBAL_NO_STACK_FILL
        REQUIRES        INCLUDE_DLL             \
                        INCLUDE_KERNEL_ARCH     \
                        INCLUDE_EXC_HANDLING    \
                        INCLUDE_FORMATTED_OUT_BASIC     \
                        SELECT_KERNEL_SCHEDULER \
                        INCLUDE_Q_FIFO          \
                        INCLUDE_Q_PRI_LIST      \
                        INCLUDE_Q_PRI_BMAP      \
                        INCLUDE_Q_PRI_DELTA     \
                        INCLUDE_OFFSET_SYMBOLS  \
                        INCLUDE_EDR_STUB        \
                        INCLUDE_ANSI_STRCPY
        HDR_FILES       sysLib.h private/kernelLibP.h         \
                        private/workQLibP.h                   \
                        private/qLibP.h taskLib.h                       \
                        private/isrLibP.h private/excLibP.h
}

#ifdef _WRS_CONFIG_CERT_KERNEL_OBJECT
Component INCLUDE_KERNEL {
        REQUIRES +=     INCLUDE_OFFSET_SYMBOLS \
                        INCLUDE_BLIB \
                        INCLUDE_BMPLIB \
                        INCLUDE_POSIX_USER_GROUP \
                        INCLUDE_POSIX_CLOCKS \
                        INCLUDE_POSIX_DIRLIB
}
#endif /* _WRS_CONFIG_CERT_KERNEL_OBJECT */

Component INCLUDE_BASE_KERNEL {
        NAME            Early kernel object support
        SYNOPSIS        This is a required component. DO NOT REMOVE.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         kernelBaseLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        kernelBaseInit ();
        REQUIRES        INCLUDE_KERNEL    \
                        INCLUDE_OBJ_LIB   \
                        INCLUDE_SEM_MUTEX
        HDR_FILES       private/kernelBaseLibP.h
}

Component INCLUDE_TASK_CREATE_DELETE {
        NAME            Dynamic creation and deletion of tasks
        SYNOPSIS        This component provides the capability to \
                        dynamically instantiate and delete tasks.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         taskCreateLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        taskCreateLibInit ();
        PROTOTYPE       void taskCreateLibInit (void);
        REQUIRES        INCLUDE_KERNEL                  \
                        SELECT_MEM_ALLOC                \
                        INCLUDE_OBJ_LIB                 \
                        INCLUDE_ANSI_STRCPY             \
                        INCLUDE_ANSI_STRLEN             \
                        INCLUDE_FORMATTED_OUT_BASIC     \
                        INCLUDE_ATOMIC_OPERATORS
}

Component INCLUDE_TASK_RESTART {
        NAME            Restart/reset tasks
        SYNOPSIS        This component provides the ability to \
                        restart or reset tasks.
        MODULES         taskRestartLib.o
        LINK_SYMS       taskRestart
        REQUIRES        INCLUDE_KERNEL        \
                        INCLUDE_OBJ_LIB       \
                        INCLUDE_ANSI_STRCPY   \
                        INCLUDE_ANSI_STRLEN   \
                        INCLUDE_TASK_CREATE_DELETE
}

Component INCLUDE_REBOOT_HOOKS {
        NAME            Reboot hooks
        SYNOPSIS        This component provides support for reboot hooks with \
                        the rebootHookLib library. When the reboot() function \
                        is executed, reboot hooks are called in the order they \
                        were added. Reboot hooks must follow similar \
                        restrictions as with interrupt service routines \
                        (ISRs). Reboot hooks must not invoke kernel service \
                        functions that can block. For example, calling free() \
                        or semTake() while the semaphore is not available \
                        causes the caller to block. Blocking calls within the \
                        reboot hooks can cause the reboot process to \
                        reschedule or hang, potentially leaving the system \
                        in an undefined state. The rebootHookAdd() function \
                        adds the specified function to a list of functions to be \
                        called when VxWorks is rebooted.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         rebootHookLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        CFG_PARAMS      MAX_REBOOT_HOOKS
        REQUIRES        INCLUDE_HOOKS
}

#ifdef _WRS_CONFIG_SYS_PWR_OFF

Component INCLUDE_POWER_OFF_HOOKS {
        NAME            Support for power hooks
        MODULES         powerOffHookLib.o
        CFG_PARAMS      MAX_POWER_OFF_HOOKS
        REQUIRES        INCLUDE_HOOKS
}

#endif

Folder  FOLDER_EDR {
        NAME            ED&R
        SYNOPSIS        This folder contains components and parameters \
                        concerning error detection and reporting (ED&R).
        CHILDREN        INCLUDE_EDR_PM        \
                        INCLUDE_EDR_SYSDBG_FLAG \
                        INCLUDE_EDR_ERRLOG \
                        SELECT_EDR_POLICY
        DEFAULTS        SELECT_EDR_POLICY
}

Component INCLUDE_ENV_VARS {
        NAME            UNIX-compatible environment variables
        SYNOPSIS        This component provides the envLib library. This \
                        library provides a UNIX-compatible environment \
                        variable facility. Environment variables are created \
                        or modified with a call to putenv(): \
                        putenv ("variableName=value"); . The value of a \
                        variable can be retrieved with a call to getenv(), \
                        which returns a pointer to the value string. Tasks can \
                        share a common set of environment variables, or they \
                        can optionally create their own private environments, \
                        either automatically when the task create hook is \
                        installed, or by an explicit call to envPrivateCreate(). \
                        The task must be spawned with the VX_PRIVATE_ENV option \
                        set to receive a private set of environment variables. \
                        Private environments created by the task creation hook \
                        inherit the values of the environment of the task that \
                        called taskSpawn() (because task create hooks run in the \
                        context of the calling task).
        MODULES         envLib.o
        INIT_RTN        envLibInit (ENV_VAR_USE_HOOKS);
        CFG_PARAMS      ENV_VAR_USE_HOOKS
        HDR_FILES       envLib.h
        REQUIRES        INCLUDE_KERNEL                \
                        INCLUDE_TASK_CREATE_HOOKS     \
                        INCLUDE_ANSI_STRCPY           \
                        INCLUDE_ANSI_STRLEN           \
                        INCLUDE_ANSI_STRNCMP          \
                        INCLUDE_MEM_MGR_BASIC         \
                        INCLUDE_SEM_READ_WRITE
}

Component INCLUDE_EXC_TASK {
        NAME            Exception task
        SYNOPSIS        This component includes the excLib facility. This \
                        generic exception handling facility includes the \
                        following functions: excInit(), which initializes the \
                        exception handling package; excJobAdd(), which requests \
                        a task-level function call from the interrupt level; \
                        excJobAddDefer(), which requests a deferred task-level \
                        function call; and excHookAdd(), which specifies a \
                        function to be called with exceptions.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         excLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        REQUIRES        INCLUDE_KERNEL          \
                        INCLUDE_SEM_BINARY
        CFG_PARAMS      MAX_ISR_JOBS
        INIT_RTN        excInit (MAX_ISR_JOBS);
        HDR_FILES       excLib.h
}

Component INCLUDE_JOB_TASK {
        NAME            Job task
        SYNOPSIS        This component provides task-level work deferral.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         jobTaskLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        jobTaskLibInit (JOB_TASK_STACK_SIZE);
        CFG_PARAMS      JOB_TASK_STACK_SIZE
        HDR_FILES       private/jobLibP.h
        REQUIRES        INCLUDE_KERNEL              \
                        INCLUDE_OBJ_LIB             \
                        INCLUDE_SEM_MUTEX           \
                        INCLUDE_ANSI_STRNCPY        \
                        INCLUDE_TASK_CREATE_DELETE  \
                        INCLUDE_FORMATTED_OUT_BASIC
}

Component INCLUDE_JOB_DEFER {
        NAME            Job deferral
        SYNOPSIS        This component provides abstracted work deferral.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         jobLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       jobAdd
        HDR_FILES       private/jobLibP.h
        REQUIRES        INCLUDE_EXC_TASK
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_ISR_OBJECTS {
        NAME            Interrupt service routine object library
        SYNOPSIS        This component provides objects describing interrupt \
                        service routines (ISRs).
        MODULES         isrLib.o
        HDR_FILES       private/isrLibP.h
        REQUIRES        INCLUDE_KERNEL              \
                        INCLUDE_OBJ_LIB             \
                        INCLUDE_OBJ_INFO            \
                        INCLUDE_ANSI_STRNCPY
}

Parameter FUNCPTR_OBJ_MEMALLOC_RTN {
        NAME            Pointer to objMemAllocRtn()
        SYNOPSIS        This parameter specifies the function pointer to the \
                        objMemAllocRtn() function.
        TYPE            void *
        DEFAULT         (INCLUDE_MEM_ALLOT)::(objMemAllot) memPartAlignedAlloc
}

Parameter FUNCPTR_OBJ_MEMFREE_RTN {
        NAME            Pointer to objMemFreeRtn()
        SYNOPSIS        This parameter specifies the function pointer to the \
                        objMemFreeRtn() function.
        TYPE            FUNCPTR
        DEFAULT         (INCLUDE_MEM_ALLOT)::(NULL) memPartFree
}

Parameter OBJ_MEM_POOL_ID {
        NAME            Memory pool ID
        SYNOPSIS        This parameter specifies the object memory pool ID.
        TYPE            void *
        DEFAULT         (INCLUDE_MEM_ALLOT)::(NULL) memSysPartId
}

Component INCLUDE_OBJ_LIB {
        NAME            Object management
        SYNOPSIS        This component provides the objLib library. This \
                        library provides the interface to the VxWorks user \
                        object management facilities.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         objLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        REQUIRES        INCLUDE_ANSI_STRNCPY \
                        INCLUDE_ANSI_STRCMP  \
                        INCLUDE_ANSI_STRLEN  \
                        INCLUDE_CLASS_LIB    \
                        INCLUDE_KERNEL       \
                        INCLUDE_SEM_MUTEX
        INIT_RTN        objLibInit ((OBJ_ALLOC_FUNC)FUNCPTR_OBJ_MEMALLOC_RTN, \
                                    (OBJ_FREE_FUNC)FUNCPTR_OBJ_MEMFREE_RTN,   \
                                    OBJ_MEM_POOL_ID,                          \
                                    OBJ_LIBRARY_OPTIONS);
        CFG_PARAMS      FUNCPTR_OBJ_MEMALLOC_RTN    \
                        FUNCPTR_OBJ_MEMFREE_RTN     \
                        OBJ_MEM_POOL_ID             \
                        OBJ_LIBRARY_OPTIONS
        HDR_FILES       objLib.h
}

Component INCLUDE_OBJ_INFO {
        NAME            Object information
        SYNOPSIS        This component provides object management functions \
                        that require lookup in a list of objects, such as \
                        the objNameToId() function.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         objInfo.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        REQUIRES        INCLUDE_OBJ_LIB                \
                        INCLUDE_CLASS_LIST
        INIT_RTN        objInfoInit ();
        PROTOTYPE       STATUS objInfoInit (void);
}

#ifdef _WRS_CONFIG_OBJECT_OWNERSHIP
Component INCLUDE_OBJ_OWNERSHIP {
        NAME            Object management ownership
        SYNOPSIS        This component provides the objOwnerLib library which \
                        includes object ownership functions.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         objOwnerLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        objOwnershipInit ();
        HDR_FILES       objLib.h
        INCLUDE_WHEN    INCLUDE_RTP
        REQUIRES        INCLUDE_OBJ_LIB
}
#endif

Component INCLUDE_CLASS_LIB {
        NAME            Class management
        SYNOPSIS        This component provides object class management.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         classLib.o           \
                        handleLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        classLibInit ();
        HDR_FILES       classLib.h
        REQUIRES        INCLUDE_KERNEL       \
                        INCLUDE_SEM_MUTEX    \
                        SELECT_MEM_ALLOC
}

Component INCLUDE_CLASS_LIST {
        NAME            Class list management
        SYNOPSIS        This component provides object class list management.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         classListLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        classListLibInit ();
        REQUIRES        INCLUDE_CLASS_LIB
}

Component INCLUDE_VXEVENTS {
        NAME            VxWorks events
        SYNOPSIS        This component provides event facilities. VxWorks \
                        events provide a means of communication and \
                        synchronization between tasks and other tasks, \
                        interrupt service routines (ISRs) and tasks, \
                        semaphores and tasks, and message queues and tasks. \
                        Events can be sent explicitly by tasks and ISRs, \
                        and can be sent when message queues or semaphores \
                        are free. Only tasks can receive events. Events can \
                        be used as a lighter-weight alternative to binary \
                        semaphores for task-to-task and ISR-to-task \
                        synchronization (because no object must be created). \
                        They can also be used to notify a task that a semaphore \
                        has become available, or that a message has arrived on \
                        a message queue. The events facility provides a \
                        mechanism for coordinating the activity of a task using \
                        up to thirty-two events that can be sent to it explicitly \
                        by other tasks and ISRs, or when semaphores and message \
                        queues are free. A task can wait on multiple events from \
                        multiple sources. Events thereby provide a means for \
                        coordination of a complex matrix of activity without \
                        allocation of additional system resources.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         eventLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        eventLibInit (VXEVENTS_OPTIONS);
        REQUIRES        INCLUDE_KERNEL \
                        INCLUDE_Q_FIFO
        HDR_FILES       eventLib.h
        CFG_PARAMS      VXEVENTS_OPTIONS
}

Parameter VXEVENTS_OPTIONS {
        NAME            VxWorks events configuration options
        SYNOPSIS        This parameter specifies the configuration for VxWorks \
                        events. For a list of support options and a \
                        more detailed description, see the reference \
                        information for eventLib.
        TYPE            UINT
        DEFAULT         EVENTS_NONINTERRUPTIBLE
}

Component INCLUDE_MSG_Q {
        NAME            Message queues
        SYNOPSIS        This component provides message queue support using the \
                        msgQLib library. This library contains functions for \
                        creating and using message queues, the primary inter-task \
                        communication mechanism in VxWorks. Message queues allow \
                        a variable number of messages (varying in length) to be \
                        queued in first-in-first-out (FIFO) order. Any task or \
                        interrupt service routine (ISR) can send messages to a \
                        message queue. Any task can receive messages from a \
                        message queue. Multiple tasks can send to, and receive \
                        from, the same message queue. Full-duplex communication \
                        between two tasks generally requires two message queues, \
                        one for each direction. For more information, see the \
                        reference information for msgQLib.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         msgQLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        msgQLibInit ();
        HDR_FILES       msgQLib.h
        REQUIRES        INCLUDE_KERNEL       \
                        INCLUDE_Q_FIFO       \
                        INCLUDE_Q_PRI_LIST   \
                        INCLUDE_SLL          \
                        INCLUDE_TASK_CREATE_HOOKS
}

Component INCLUDE_MSG_Q_CREATE_DELETE {
        NAME            Message queue creation and deletion
        SYNOPSIS        This component provides the msgQCreateLib library. This \
                        library contains functions for creating and deleting \
                        message queues. The functions to initialize and operate \
                        on message queues are implemented in msgQLib.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         msgQCreateLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        REQUIRES        INCLUDE_MSG_Q \
                        INCLUDE_OBJ_LIB
        INIT_RTN        msgQCreateLibInit ();
        HDR_FILES       msgQLib.h
}

Component INCLUDE_MSG_Q_EVENTS {
        NAME            Send/receive events from message queue operations
        SYNOPSIS        This component provides a library that is an extension \
                        to eventLib, the VxWorks events library. Its purpose is \
                        to support events for message queues. The functions in \
                        this library are used to control registration of tasks \
                        on a message queue. The msgQEvStart() function \
                        registers a task and starts the notification process. \
                        The msgQEvStop() function un-registers the task, which \
                        stops the notification mechanism. When a task is \
                        registered and a message arrives on the queue, the \
                        events specified are sent to that task, on the \
                        condition that no other task is pending on that \
                        message queue. However, if a msgQReceive() is to be \
                        done afterwards to get the message, there is no \
                        guarantee that it will still be available.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         msgQEvLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       msgQEvStart
        INCLUDE_WHEN    INCLUDE_VXEVENTS \
                        INCLUDE_MSG_Q
        REQUIRES        INCLUDE_VXEVENTS \
                        INCLUDE_MSG_Q
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_MSG_Q_INFO {
        NAME            Message queue information
        SYNOPSIS        This component provides the msgQInfo library. This \
                        library provides functions to show message queue \
                        statistics, such as the task queuing method, messages \
                        queued, and receivers blocked. The msgQInfoGet() \
                        function gets information about message queues, \
                        such as the task queuing method, messages queued, \
                        and receivers blocked. This component is required by \
                        pipe and message queue show functions.
        MODULES         msgQInfo.o
        REQUIRES        INCLUDE_MSG_Q
}

Component INCLUDE_SEM_LIB {
        NAME            Semaphore support infrastructure
        SYNOPSIS        This component provides the semaphore support infrastructure. \
                        Semaphores are the basis for synchronization and mutual \
                        exclusion in VxWorks. They are powerful in their \
                        simplicity and form the foundation for numerous VxWorks \
                        facilities. Different semaphore types serve different \
                        needs, and while the behavior of the types differs, \
                        their basic interface is the same. This library provides \
                        semaphore functions common to all VxWorks semaphore types. \
                        For all types, the two basic operations are semTake() \
                        and semGive(), the acquisition or relinquishing of a \
                        semaphore. Mutex semaphores offer the greatest speed \
                        while binary semaphores offer the broadest applicability. \
                        The semLib library provides all of the semaphore \
                        operations, including functions for semaphore control, \
                        deletion, and information. Semaphores must be validated \
                        before any semaphore operation can be undertaken. An \
                        invalid semaphore ID results in ERROR, and an \
                        appropriate `errno' is set.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        semLibInit ();
        HDR_FILES       semLib.h
        CONFIGLETTES    usrSemLib.c
        REQUIRES        INCLUDE_KERNEL \
                        INCLUDE_Q_FIFO
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_SEM_DELETE {
        NAME            Semaphore deletion functions
        SYNOPSIS        This component provides the semDeleteLib library that \
                        contains functions that terminate and delete semaphores. \
                        The semDelete() call terminates a semaphore and \
                        deallocates any associated memory. The deletion of a \
                        semaphore unblocks tasks pended on that semaphore; the \
                        functions that were pended return ERROR. Take care when \
                        deleting semaphores, particularly those used for mutual \
                        exclusion, to avoid deleting a semaphore out from under \
                        a task that already has taken (owns) that semaphore. \
                        Applications should adopt the protocol of only deleting \
                        semaphores that the deleting task has successfully taken.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semDeleteLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        semDeleteLibInit ();
        HDR_FILES       semLib.h
        REQUIRES        INCLUDE_SEM_LIB \
                        INCLUDE_OBJ_LIB
}

Component INCLUDE_SEM_BINARY {
        NAME            Binary semaphores
        SYNOPSIS        This component provides a library that provides the \
                        interface to VxWorks binary semaphores. Binary \
                        semaphores are the most versatile, efficient, and \
                        conceptually simple type of semaphore. They can be \
                        used to control mutually exclusive access to shared \
                        devices or data structures, or synchronize multiple \
                        tasks, or task-level and interrupt-level processes. \
                        Binary semaphores form the foundation of numerous \
                        VxWorks facilities.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semBLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        HDR_FILES       semLib.h
        REQUIRES        INCLUDE_SEM_LIB
}

Component INCLUDE_SEM_MUTEX {
        NAME            Mutex semaphores
        SYNOPSIS        This component provides a library that provides the interface to VxWorks \
                        mutual-exclusion semaphores. Mutual-exclusion semaphores \
                        offer convenient options suited for situations requiring \
                        mutually exclusive access to resources. Typical \
                        applications include sharing devices and protecting \
                        data structures. Mutual-exclusion semaphores are used \
                        by many higher-level VxWorks facilities. The \
                        mutual-exclusion semaphore is a specialized version of \
                        the binary semaphore, designed to address issues inherent \
                        in mutual exclusion, such as recursive access to resources, \
                        priority inversion, and deletion safety. The fundamental \
                        behavior of the mutual-exclusion semaphore is \
                        identical to the binary semaphore (see the reference entry \
                        for semBLib), except for the following restrictions: it \
                        can only be used for mutual exclusion; it can only be \
                        given by the task that took it; it may not be taken or \
                        given from interrupt level; and the semFlush() operation is \
                        illegal. These last two operations have no meaning in \
                        mutual-exclusion situations.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semMLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        HDR_FILES       semLib.h
        REQUIRES        INCLUDE_SEM_LIB
}

Component INCLUDE_SEM_COUNTING {
        NAME            Counting semaphores
        SYNOPSIS        This component provides the semCLib library. This \
                        library provides the interface to VxWorks counting \
                        semaphores. Counting semaphores are useful for \
                        guarding multiple instances of a resource. A counting \
                        semaphore can be viewed as a cell in memory whose \
                        contents keep track of a count.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semCLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        HDR_FILES       semLib.h
        REQUIRES        INCLUDE_SEM_LIB
}

Component INCLUDE_SEM_READ_WRITE {
        NAME            Reader/writer semaphores
        SYNOPSIS        This component provides the semRWLib and windSemRWLib \
                        libraries. semRWLib provides the interface to VxWorks \
                        reader/writer semaphores. Reader/writer semaphores \
                        provide a method of synchronizing groups of tasks that \
                        can be granted concurrent access to a resource with \
                        those tasks that require mutually exclusive access to \
                        that resource. Typically, this correlates to those tasks \
                        that intend to modify a resource and those which intend \
                        only to view it. windSemRWLib contains the \
                        implementation of the windSemRWDelete() function. A call \
                        to windSemRWDelete() unblocks any tasks pending on \
                        a read/write semaphore. If the deletion safety option is \
                        enabled, any and all owners have their safety count \
                        decremented. If the inversion safe option is enabled, \
                        any and all owners have their priority inheritance \
                        information updated.
        MODULES         semRWLib.o windSemRWLib.o
        HDR_FILES       semLib.h
        REQUIRES        INCLUDE_SEM_LIB
        CFG_PARAMS      SEM_RW_MAX_CONCURRENT_READERS
}

Component INCLUDE_SC_SEM_READ_WRITE {
        NAME            Reader/writer semaphore system calls
        SYNOPSIS        This component provides the reader/writer semaphore \
                        system call library, which includes the handlers \
                        that get invoked by the system call infrastructure \
                        (SCI) when an application makes a semRWLib system call.
        MODULES         semRWScLib.o
        HDR_FILES       semLib.h
        INCLUDE_WHEN    INCLUDE_RTP \
                        INCLUDE_SEM_READ_WRITE
}

Component INCLUDE_CONDVAR {
        NAME            Condition variables
        SYNOPSIS        This component provides support for condition variables. \
                        Condition variables allow tasks to wait on both an \
                        event to occur, and to acquire a mutex that protects \
                        an object associated with that event. Thus, condition \
                        variables are acquired by taking a mutex, and waiting \
                        on the condition variable. When the event is signaled, \
                        a task is unblocked and the mutex given to that task, \
                        which can then access the protected resource. Note \
                        that signaling a condition variable only unblocks a \
                        waiting resource - if a condition variable is signaled \
                        before a task waits on that condition variable, then \
                        the waiting task must wait until the condition variable \
                        is signaled again. A condition variable can only be \
                        associated with one mutex at a time (if there are \
                        waiters, all waiters must have held the same mutex \
                        when the condition variable was waited on. No condition \
                        variable function is callable from an ISR. For detailed \
                        descriptions of the functions provided in this \
                        component, see the reference entry for condVarLib.
        MODULES         condVarLib.o
        HDR_FILES       private/condVarLibP.h
        REQUIRES        INCLUDE_SEM_BINARY \
                        INCLUDE_SEM_MUTEX \
                        INCLUDE_MEM_MGR_BASIC
        INIT_RTN        condVarLibInit ();
}

Component INCLUDE_SC_CONDVAR {
        NAME            Condition variable system calls
        MODULES         condVarScLib.o
        HDR_FILES       private/condVarLibP.h
        INCLUDE_WHEN    INCLUDE_RTP \
                        INCLUDE_CONDVAR \
                        INCLUDE_CONDVAR_OPEN
}


Component INCLUDE_SEM_BINARY_CREATE {
        NAME            Binary semaphore creation
        SYNOPSIS        This component provides the semBCreateLib library which \
                        implements semBCreate(), the function that creates \
                        binary semaphores.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semBCreateLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        HDR_FILES       semLib.h
        REQUIRES        INCLUDE_SEM_BINARY \
                        INCLUDE_OBJ_LIB
        PROTOTYPE       void semBCreateLibInit (void);
}

Component INCLUDE_SEM_COUNTING_CREATE {
        NAME            Counting semaphore creation
        SYNOPSIS        This component provides semCCreate(), the function that \
                        creates counting semaphores.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semCCreateLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        HDR_FILES       semLib.h
        REQUIRES        INCLUDE_SEM_COUNTING \
                        INCLUDE_OBJ_LIB
        PROTOTYPE       void semCCreateLibInit (void);
}

Component INCLUDE_SEM_READ_WRITE_CREATE {
        NAME            Reader/writer semaphore creation
        SYNOPSIS        This component provides the semRWCreateLib library which \
                        implements semRWCreate(), the function that creates \
                        read/write semaphores.
        MODULES         semRWCreateLib.o
        HDR_FILES       semLib.h
        REQUIRES        INCLUDE_SEM_READ_WRITE \
                        INCLUDE_OBJ_LIB
}

Component INCLUDE_SEM_MUTEX_CREATE {
        NAME            Mutex semaphore creation
        SYNOPSIS        This component provides the semMCreate() function. This \
                        function creates mutual-exclusion semaphores.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semMCreateLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        HDR_FILES       semLib.h
        REQUIRES        INCLUDE_SEM_MUTEX \
                        INCLUDE_OBJ_LIB
        PROTOTYPE       void semMCreateLibInit (void);
}

Component INCLUDE_SEM_EVENTS {
        NAME            Send/receive events from semaphore operations
        SYNOPSIS
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semEvLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       semEvStart
        INCLUDE_WHEN    INCLUDE_VXEVENTS \
                        INCLUDE_SEM_LIB
        REQUIRES        INCLUDE_VXEVENTS \
                        INCLUDE_SEM_LIB
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_SEM_INFO {
        NAME            Semaphore information
        SYNOPSIS        This component provides functions to retrieve information \
                        about a semaphore. The semInfo() function returns \
                        information about tasks blocked on the semaphore. Given \
                        a SEM_INFO structure, the semInfoGet() function returns \
                        the type and state of the semaphore, as well as the \
                        options used to create the semaphore, the number of \
                        blocked tasks, and the pending task IDs.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semInfo.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       semInfo
        REQUIRES        INCLUDE_SEM_LIB
}

Component INCLUDE_SEM_EXCHANGE {
        NAME            Semaphore exchange
        SYNOPSIS        This component provides the semExchange library. This \
                        library provides the semExchange() function. This \
                        function atomically gives one semaphore and takes \
                        another. Currently, only the binary and mutex semaphore \
                        types support the semExchange() operation.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semExchange.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        HDR_FILES       semLib.h
        LINK_SYMS       semExchange
        REQUIRES        INCLUDE_SEM_LIB
        INCLUDE_WHEN    INCLUDE_RTP
}

Component INCLUDE_SC_SEM_EXCHANGE {
        NAME            Semaphore exchange
        SYNOPSIS
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         semExchangeScLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        HDR_FILES       semLib.h
        INCLUDE_WHEN    INCLUDE_RTP \
                        INCLUDE_SEM_EXCHANGE
}

Component INCLUDE_TASK_INFO {
        NAME            Task information
        SYNOPSIS        This component provides the taskInfo library. This \
                        library provides a programmatic interface for \
                        obtaining task information. Task information is crucial \
                        as a debugging aid and user-interface convenience \
                        during the development cycle of an application. The \
                        taskOptionsGet(), taskRegsGet(), taskName(), \
                        taskNameToId(), taskIsReady(), taskIsSuspended(), \
                        taskInfoGet(), and taskIdListGet() functions are used \
                        to obtain task information. Three functions -- \
                        taskOptionsSet(), taskRegsSet(), and taskIdDefault() \
                        -- provide programmatic access to debugging features. \
                        The chief drawback of using task information is that \
                        tasks can change their state between the time the \
                        information is gathered and the time it is utilized. \
                        Information provided by these functions should therefore \
                        be viewed as a snapshot of the system, and not relied \
                        upon unless the task is consigned to a known state, \
                        such as suspended. Task management and control \
                        functions are provided by taskLib. Higher-level task \
                        information display functions are provided by taskShow.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         taskInfo.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       taskOptionsGet
        REQUIRES        INCLUDE_KERNEL
}

Component INCLUDE_TASK_LIST {
        NAME            Task list management
        SYNOPSIS        This component provides the task utility functions that \
                        depend on lookup in a task list, taskIdListGet() and \
                        taskNameToId().
        MODULES         taskListLib.o
        LINK_SYMS       taskIdListGet
        REQUIRES        INCLUDE_KERNEL
}

Component INCLUDE_TASK_HOOKS {
        NAME            Task hooks
        SYNOPSIS        This component provides user callouts on task creation, \
                        deletion, and context switch.
        HDR_FILES       taskHookLib.h
        REQUIRES        INCLUDE_KERNEL \
                        INCLUDE_HOOKS  \
                        INCLUDE_TASK_CREATE_HOOKS \
                        INCLUDE_TASK_SWAP_HOOKS   \
                        INCLUDE_TASK_SWITCH_HOOKS
}

Component INCLUDE_TASK_CREATE_HOOKS {
        NAME            Task create hooks
        SYNOPSIS        This component provides user callouts on task creation \
                        and deletion. It is required to use the task hook library.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         taskCreateHookLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        taskCreateHookInit ();
        HDR_FILES       taskHookLib.h
        REQUIRES        INCLUDE_KERNEL
        CFG_PARAMS      VX_MAX_TASK_CREATE_RTNS
}

Parameter VX_MAX_TASK_CREATE_RTNS {
        NAME            Task create/delete hooks table size
        SYNOPSIS        This parameter specifies the size of the task \
                        create and delete hook tables. By default, it is set to 40.
        TYPE            UINT
        DEFAULT         40
}

Component INCLUDE_TASK_SWAP_HOOKS {
        NAME            Task swap hooks
        SYNOPSIS        This component provides user callouts on task context \
                        switches.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         taskSwapHookLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       taskSwapHookAdd
        HDR_FILES       taskHookLib.h
        REQUIRES        INCLUDE_KERNEL \
                        INCLUDE_HOOKS
        INCLUDE_WHEN    INCLUDE_TASK_HOOKS
}

Component INCLUDE_TASK_SWITCH_HOOKS {
        NAME            Task switch hooks
        SYNOPSIS        This component provides user callouts on task context \
                        switches.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         taskSwitchHookLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       taskSwitchHookAdd
        HDR_FILES       taskHookLib.h
        REQUIRES        INCLUDE_KERNEL \
                        INCLUDE_HOOKS
        INCLUDE_WHEN    INCLUDE_TASK_HOOKS
}

Component INCLUDE_TASK_ROTATE {
        NAME            Task rotate functions
        SYNOPSIS        This component rotates the task ready queue for a \
                        given priority. To make taskRotate() available, you \
                        must include this component in your configuration.
        MODULES         taskRotate.o windRotate.o
        LINK_SYMS       taskRotate windRotate
        HDR_FILES       taskLib.h
        REQUIRES        INCLUDE_VX_TRADITIONAL_SCHEDULER
}

Component INCLUDE_TASK_TOOLS_UTIL {
        NAME            Task tools utility functions
        MODULES         taskToolsUtilLib.o
        HDR_FILES       taskLib.h
        LINK_SYMS       taskStatusString
        REQUIRES        INCLUDE_KERNEL
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_TASK_UTIL {
        NAME            Task utility functions
        SYNOPSIS        This component provides a programmatic interface \
                        for modifying task information.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         taskUtilLib.o
        LINK_SYMS       taskSpareNumAllot
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        HDR_FILES       taskUtilLib.h
        REQUIRES        INCLUDE_KERNEL
}

#if (!defined _WRS_CONFIG_SMP) && (!defined _WRS_CONFIG_LP64)
Component INCLUDE_TASK_VARS {
        NAME            Task variables
        SYNOPSIS        This component allows global variables to be made \
                        private to a task.
        MODULES         taskVarLib.o
        INIT_RTN        taskVarInit ();
        HDR_FILES       taskVarLib.h
        REQUIRES        INCLUDE_KERNEL            \
                        INCLUDE_SEM_DELETE        \
                        INCLUDE_SEM_MUTEX         \
                        INCLUDE_TASK_CREATE_HOOKS \
                        INCLUDE_TASK_SWITCH_HOOKS \
                        INCLUDE_MEM_MGR_BASIC
        _CHILDREN       FOLDER_KERNEL
        _DEFAULTS       FOLDER_KERNEL
}
#endif    /* !_WRS_CONFIG_SMP && !_WRS_CONFIG_LP64 */

Component INCLUDE_WATCHDOGS {
        NAME            Watchdog timers
        SYNOPSIS        This component provides a general watchdog timer facility. \
                        Any task can create a watchdog timer and use it to run a \
                        specified function in the context of the system-clock ISR, \
                        after a specified delay. Once a timer has been created \
                        with wdCreate(), it can be started with wdStart(). The \
                        wdStart() function specifies what function to run, a \
                        parameter for that function, and the amount of time (in \
                        ticks) before the function is to be called. The timeout \
                        value is in ticks as determined by the system clock; \
                        see sysClkRateSet() for more information. After the \
                        specified delay ticks have elapsed, unless wdCancel() \
                        is called first to cancel the timer, the timeout function \
                        is invoked with the parameter specified in the wdStart() \
                        call. The timeout function is invoked whether the task \
                        which started the watchdog is running, suspended, or \
                        deleted. The timeout function executes only once per \
                        wdStart() invocation; there is no need to cancel a timer \
                        with wdCancel() after it has expired, or in the \
                        expiration callback itself. Note that the timeout \
                        function is invoked at interrupt level, rather than in \
                        the context of the task. Thus, there are restrictions \
                        on what the function can do. Watchdog functions are \
                        constrained to the same rules as interrupt service \
                        routines. For example, they cannot take semaphores, \
                        issue other calls that can block, or use I/O system \
                        functions like printf(). Note: You can defer watchdog \
                        function invocation. As such, isrIdCurrent is either \
                        a valid ISR_ID or is NULL in the case of deferral.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         wdLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        wdLibInit ();
        HDR_FILES       wdLib.h
        REQUIRES        INCLUDE_KERNEL
}

Component INCLUDE_WATCHDOGS_CREATE_DELETE {
        NAME            Watchdog timer creation and deletion
        SYNOPSIS        This component provides wdCreateLib. This library \
                        provides creation and deletion functions for the \
                        watchdog facility. The functions to initialize and \
                        operate on watchdogs are implemented in wdLib.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         wdCreateLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        REQUIRES        INCLUDE_WATCHDOGS INCLUDE_OBJ_LIB
        INIT_RTN        wdCreateLibInit ();
        HDR_FILES       wdLib.h
}

Component INCLUDE_HOOKS {
        NAME            Hook function table support
        SYNOPSIS        This component allows adding and removing of hook \
                        functions.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         hookLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        HDR_FILES       hookLib.h
        LINK_SYMS       hookAddToTail
}

Component INCLUDE_HOOK_SHOW {
        NAME            Hook function table show support
        SYNOPSIS        This component includes the hookShow library which \
                        provides routines which summarize the installed kernel \
                        hook routines in a given hook table. These routines \
                        are generic, and can be used to display any kind of \
                        hook.
        MODULES         hookShow.o
        REQUIRES        INCLUDE_HOOKS
        LINK_SYMS       hookShow
        INCLUDE_WHEN    INCLUDE_HOOKS \
                        INCLUDE_SHOW_ROUTINES
}

Selection SELECT_MEM_ALLOC {
        NAME            Memory allocator selection
        SYNOPSIS        Use this selection to choose between a basic memory \
                        allocator and a memory allot allocator.
        COUNT           1-1
        CHILDREN        INCLUDE_MEM_ALLOT \
                        INCLUDE_MEM_MGR_BASIC
        DEFAULTS        INCLUDE_MEM_ALLOT
}

Component INCLUDE_MEM_ALLOT {
        NAME            Memory allot allocator
        SYNOPSIS        This component provides a primitive memory allocator, \
                        without free.
        MODULES         memAllotLib.o
        INIT_RTN        memAllotLibInit (pMemPoolStart, memPoolSize);
        REQUIRES        INCLUDE_KERNEL
}

Component INCLUDE_MEM_MGR_BASIC {
        NAME            Basic memory allocator
        SYNOPSIS        This component includes the core memory partition \
                        manager.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         memPartLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        memPartLibInit (pMemPoolStart, memPoolSize);
        HDR_FILES       private/memPartLibP.h
#ifdef _WRS_CONFIG_COMPAT69_ADR_SPACE
        REQUIRES        INCLUDE_SLL             \
                        INCLUDE_AVL_UINT_TREES  \
                        INCLUDE_SEM_MUTEX       \
                        INCLUDE_SEM_DELETE      \
                        INCLUDE_OBJ_LIB         \
                        INCLUDE_ANSI_STRCPY     \
                        INCLUDE_ANSI_STRLEN     \
                        INCLUDE_FORMATTED_OUT_BASIC
#else
        REQUIRES        INCLUDE_SLL             \
                        INCLUDE_AVL_UINT_TREES  \
                        INCLUDE_SEM_MUTEX       \
                        INCLUDE_SEM_DELETE      \
                        INCLUDE_OBJ_LIB         \
                        INCLUDE_ANSI_STRCPY     \
                        INCLUDE_ANSI_STRLEN     \
                        INCLUDE_KERNEL_PROXIMITY_HEAP \
                        INCLUDE_KERNEL_COMMON_HEAP    \
                        INCLUDE_FORMATTED_OUT_BASIC
#endif
}

Component INCLUDE_MEM_MGR_FULL {
        NAME            Full featured memory allocator
        SYNOPSIS        This component provides the memLib library. This \
                        library provides the API for allocating and freeing \
                        blocks of memory of arbitrary size from an RTP heap. \
                        This library implements an RTP heap as a dedicated \
                        memory partition. One private heap is created \
                        automatically for every RTP. The library provides \
                        ANSI allocation functions and enhanced memory management \
                        features, including error handling and aligned \
                        allocation. Most of the memLib functions are simple \
                        wrappers to the memory partition management functions \
                        which implement the actual memory management \
                        functionalty. For more information about the \
                        memory partition management facility, see the reference \
                        entry for memPartLib.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         memLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        memInit (pMemPoolStart, memPoolSize, \
                                 MEM_PART_DEFAULT_OPTIONS);
        HDR_FILES       private/memPartLibP.h
        REQUIRES        INCLUDE_MEM_MGR_BASIC
        CFG_PARAMS      MEM_PART_DEFAULT_OPTIONS
}

Parameter MEM_PART_DEFAULT_OPTIONS {
        NAME            Default memory partition options
        SYNOPSIS        This component provides the default memory partition \
                        options when the full featured memory allocator is \
                        present.
        TYPE            UINT
        DEFAULT         (MEM_ALLOC_ERROR_LOG_FLAG      | \
                         MEM_ALLOC_ERROR_EDR_WARN_FLAG | \
                         MEM_BLOCK_ERROR_LOG_FLAG      | \
                         MEM_BLOCK_ERROR_EDR_WARN_FLAG | \
                         MEM_BLOCK_ERROR_SUSPEND_FLAG  | \
                         MEM_BLOCK_CHECK)
}

Component INCLUDE_MEM_MGR_INFO {
        NAME            Memory allocator information functions
        SYNOPSIS        This component provides the memInfo library. This library \
                        provides functions for obtaining information about a \
                        memory partition or the kernel heap.
        MODULES         memInfo.o
        INIT_RTN        memInfoInit ();
        HDR_FILES       private/memPartLibP.h
        REQUIRES        INCLUDE_MEM_MGR_BASIC
}

#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
Component INCLUDE_KERNEL_PROXIMITY_HEAP {
        NAME            Kernel proximity heap
        SYNOPSIS        This component provides the kProxHeapLib library. \
                        This library provides the function that initializes the \
                        kernel proximity heap partition. The kernel proximity \
                        heap is a memory partition created in the kernel system \
                        memory region.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         memLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        kProxHeapInit (pMemPoolStart, memPoolSize);
        REQUIRES        INCLUDE_MEM_MGR_BASIC
        _CHILDREN       FOLDER_KERNEL
        CFG_PARAMS      KERNEL_PROXIMITY_HEAP_SIZE
}

Parameter KERNEL_PROXIMITY_HEAP_SIZE {
        NAME            Kernel proximity heap size
        SYNOPSIS        This parameter specifies the kernel proximity heap size.
        TYPE            ULONG
#ifdef _WRS_CONFIG_LP64
        DEFAULT         0x10000000
#else
        DEFAULT         0x1000000
#endif
}

Component INCLUDE_KERNEL_COMMON_HEAP {
        NAME            Kernel common heap
        SYNOPSIS        This component includes the kernel common heap which \
                        is the memory partition used by the kernel and kernel \
                        applications for dynamic memory allocation. Physical \
                        memory is allocated from the global RAM pool and \
                        virtual memory is allocated from the kernel virtual \
                        memory pool region. The heap is managed using the \
                        standard ANSI memory allocation functions, malloc(), \
                        free(), and so on. For more information, see the \
                        reference entries for memPartLib and memLib.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         memLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        kCommonHeapInit (KERNEL_COMMON_HEAP_INIT_SIZE, KERNEL_COMMON_HEAP_INCR_SIZE);
        REQUIRES        INCLUDE_MEM_MGR_BASIC
        _CHILDREN       FOLDER_KERNEL
        CFG_PARAMS      KERNEL_COMMON_HEAP_INIT_SIZE \
                        KERNEL_COMMON_HEAP_INCR_SIZE
}

Parameter KERNEL_COMMON_HEAP_INIT_SIZE {
        NAME            Kernel common heap initial size
        SYNOPSIS        This parameter specifies the initial size of the heap. \
                        It should not be set to a value larger than the \
                        available largest physically contiguous block of RAM. \
                        Take into account the size of a page and other \
                        bookkeeping information, which reduces the actual \
                        maximum value that can be used with this parameter.
        TYPE            ULONG
#ifdef _WRS_CONFIG_LP64
        DEFAULT         0x20000000
#else
        DEFAULT         0x2000000
#endif
}

Parameter KERNEL_COMMON_HEAP_INCR_SIZE {
        NAME            Kernel common heap increment size
        SYNOPSIS        This parameter helps support auto-growth of the kernel \
                        common heap. When the current heap content cannot \
                        satisfy the requested allocation, the operating system \
                        automatically adds more memory which is allocated from \
                        the kernel virtual memory pool region and the global \
                        RAM pool. Growth is subject to available free RAM in \
                        the pool. The amount of heap growth is a multiple of \
                        this parameter. Setting this parameter to zero \
                        disables auto-growth.
        TYPE            ULONG
        DEFAULT         0x200000
}

#endif

Component INCLUDE_SIGNALS {
        NAME            Signals
        SYNOPSIS        This component provides the sigLib library. This \
                        library provides the signal interfaces in the RTP \
                        environment. The signal model in user-mode is designed \
                        to follow the POSIX process model. Signals alter the \
                        flow of control of tasks by communicating asynchronous \
                        events within or between task contexts. Using the APIs \
                        provided by this library, signals can be sent from an \
                        RTP task to either another RTP or a public task in \
                        another RTP. Signals can be sent to an RTP using the \
                        kill() or raise() functions, and will be caught by any \
                        task in that RTP which has unmasked that signal. \
                        Signals can also be sent to specific tasks in the \
                        current or another RTP using the taskKill() function. \
                        Tasks that receive signals can either be waiting \
                        synchronously for the signal, or can have their \
                        signal mask setup to unblock that signal. If there \
                        is no such task waiting for the signal, the signal \
                        remains pended in the RTP and is delivered when \
                        one such task becomes available.
        MODULES         sigLib.o
        INIT_RTN        sigInit (POSIX_SIGNAL_MODE);
        HDR_FILES       sigLib.h
        REQUIRES        INCLUDE_KERNEL                  \
                        INCLUDE_EXC_TASK                \
                        INCLUDE_Q_FIFO                  \
                        INCLUDE_TASK_CREATE_HOOKS       \
                        INCLUDE_MEM_MGR_BASIC           \
                        INCLUDE_SIGNAL_ARCH             \
                        INCLUDE_ANSI_LONGJMP            \
                        INCLUDE_EXC_SIGNALS
        CFG_PARAMS      POSIX_SIGNAL_MODE
}

Parameter POSIX_SIGNAL_MODE {
        NAME            POSIX signal mode
        SYNOPSIS        If this parameter is set to TRUE, signals sent on \
                        fault are POSIX conformant.
        TYPE            BOOL
        DEFAULT         (INCLUDE_RTP_POSIX_PSE52)::(TRUE) FALSE
}

Component INCLUDE_EXC_SIGNALS {
        NAME            Exception handling signal support   
        SYNOPSIS        This component enables signal generation on an \
                        exception.
        INIT_RTN        excSigLibInit();
        HDR_FILES       private/excLibP.h
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_EDR_PM {
        NAME            Persistent memory
        SYNOPSIS        This component includes a reboot-safe protected memory \
                        region manager.
        MODULES         pmLib.o
        CONFIGLETTES    usrPmInit.c
        INIT_RTN        usrPmInit ();
        HDR_FILES       pmLib.h
        CFG_PARAMS      EDR_PM_ARENA \
                        PM_RESERVED_MEM
#ifdef _WRS_CONFIG_COMPAT69
        REQUIRES        INCLUDE_KERNEL          \
                        INCLUDE_CHECKSUM        \
                        INCLUDE_ANSI_STRING     \
                        INCLUDE_FORMATTED_OUT_BASIC
#else
        REQUIRES        INCLUDE_KERNEL          \
                        INCLUDE_PMAP_LIB        \
                        INCLUDE_CHECKSUM        \
                        INCLUDE_ANSI_STRING     \
                        INCLUDE_FORMATTED_OUT_BASIC
#endif
}

Component INCLUDE_EDR_ERRLOG {
        NAME            Persistent error log
        SYNOPSIS        This component includes a reboot-safe protected error \
                        log.
        MODULES         edrLib.o
        CONFIGLETTES    usrEdrInit.c
        INIT_RTN        usrEdrInit ();
        HDR_FILES       edrLib.h
        CFG_PARAMS      EDR_ERRLOG_SIZE \
                        EDR_RECORD_SIZE
        REQUIRES        INCLUDE_KERNEL          \
                        INCLUDE_EDR_PM          \
                        INCLUDE_CPLUS_DEMANGLER \
                        INCLUDE_DLL             \
                        INCLUDE_HOOKS           \
                        INCLUDE_ANSI_STRING     \
                        INCLUDE_ANSI_STRLEN     \
                        INCLUDE_SEM_MUTEX       \
                        INCLUDE_FORMATTED_OUT_BASIC
}

Component INCLUDE_EDR_SYSDBG_FLAG {
        NAME            ED&R system debug flag
        SYNOPSIS        This component includes a flag that indicates the \
                        ED&R system is in 'debug' mode.
        MODULES         edrSysDbgLib.o
        HDR_FILES       edrLib.h
        REQUIRES        INCLUDE_SYSDBG_FLAG
}

Component INCLUDE_SC_POSIX {
        NAME            POSIX system call handlers
        SYNOPSIS        This component includes system call handlers for \
                        POSIX-based calls.
        PROTOTYPE       extern void usrPosixScInit (void);
        CONFIGLETTES    usrPosixSc.c
        INIT_RTN        usrPosixScInit ();
        INCLUDE_WHEN    INCLUDE_RTP
        REQUIRES        INCLUDE_RTP
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_PX_SCHED_DEF_POLICIES {
        NAME            POSIX scheduling policies support in RTPs
        SYNOPSIS        This component provides support for the POSIX SCHED_FIFO, \
                        SCHED_RR, and SCHED_OTHER policies in RTPs. Selecting \
                        this component pulls in the INCLUDE_POSIX_PTHREAD_SCHEDULER \
                        component.
        MODULES         qPxPriBMapLib.o
        REQUIRES        INCLUDE_POSIX_PTHREAD_SCHEDULER
        }

Component INCLUDE_PX_SCHED_SPORADIC_POLICY {
        NAME            POSIX scheduling support including the SCHED_SPORADIC policy in RTPs
        SYNOPSIS        This component provides support for the POSIX SCHED_FIFO, SCHED_RR, \
                        SCHED_OTHER, and SCHED_SPORADIC policies in RTPs. \
                        Selecting this component pulls in the \
                        INCLUDE_POSIX_PTHREAD_SCHEDULER component.
        MODULES         qPxSSPriBMapLib.o
        INIT_RTN        pxSSThreadLibInit ();
        HDR_FILES       private/taskPxLibP.h
        REQUIRES        INCLUDE_POSIX_PTHREAD_SCHEDULER
        }

Selection SELECT_PX_SCHED_POLICIES {
        NAME            Scheduling policy
        SYNOPSIS        Select the POSIX scheduling policy support in RTPs.
        COUNT           1-1
        CHILDREN        INCLUDE_PX_SCHED_DEF_POLICIES \
                        INCLUDE_PX_SCHED_SPORADIC_POLICY
        DEFAULTS        INCLUDE_PX_SCHED_DEF_POLICIES
        _CHILDREN       FOLDER_POSIX
    }

Component INCLUDE_POSIX_PTHREAD_SCHEDULER {
        NAME            POSIX thread scheduler in RTPs
        SYNOPSIS        This component provides POSIX thread scheduling \
                        behavior in RTPs.
        MODULES         taskPxLib.o
        INIT_RTN        taskPxLibInit ();
        EXCLUDES        INCLUDE_TASK_ROTATE
        HDR_FILES       private/taskPxLibP.h
        CFG_PARAMS      POSIX_PTHREAD_RR_TIMESLICE
        REQUIRES        INCLUDE_RTP \
                        INCLUDE_Q_PRI_BMAP \
                        SELECT_PX_SCHED_POLICIES
        }

Component INCLUDE_CUSTOM_SCHEDULER {
        NAME            User-specified kernel scheduler
        SYNOPSIS        This component includes a user-specified kernel scheduler.
        CONFIGLETTES    usrCustomScheduler.c
        INIT_RTN        usrCustomSchedulerInit ();
        EXCLUDES        INCLUDE_TASK_ROTATE
        }

Component INCLUDE_VX_NATIVE_SCHEDULER {
        NAME            VxWorks traditional scheduler (obsoleted - replaced by INCLUDE_VX_TRADITIONAL_SCHEDULER)
        SYNOPSIS        (Obsoleted) This component is replaced by INCLUDE_VX_TRADITIONAL_SCHEDULER.
        CFG_PARAMS      VX_NATIVE_SCHED_CONSTANT_RDY_Q
        REQUIRES        INCLUDE_VX_TRADITIONAL_SCHEDULER
        }

Component INCLUDE_VX_TRADITIONAL_SCHEDULER {
        NAME            VxWorks traditional kernel scheduler
        SYNOPSIS        This component includes the VxWorks traditional \
                        kernel scheduler.
        CFG_PARAMS      VX_TRAD_SCHED_CONSTANT_RDY_Q
        REQUIRES        INCLUDE_Q_PRI_BMAP
        }

Selection SELECT_KERNEL_SCHEDULER {
        NAME            Kernel scheduler selection
        SYNOPSIS        Select a kernel scheduler. Choose the POSIX thread \
                        scheduler, the VxWorks traditional kernel scheduler, \
                        the time partition scheduler, or a user-specified \
                        kernel scheduler.
        COUNT           1-1
        CHILDREN        INCLUDE_VX_TRADITIONAL_SCHEDULER \
                        INCLUDE_POSIX_PTHREAD_SCHEDULER \
                        INCLUDE_CUSTOM_SCHEDULER
        DEFAULTS        INCLUDE_VX_TRADITIONAL_SCHEDULER
}

Parameter VX_NATIVE_SCHED_CONSTANT_RDY_Q {
        NAME            Constant-time kernel ready queue (obsoleted)
        SYNOPSIS        (Obsoleted) This parameter is replaced by VX_TRAD_SCHED_CONSTANT_RDY_Q.
        TYPE            BOOL
        DEFAULT         VX_TRAD_SCHED_CONSTANT_RDY_Q
}

Parameter VX_TRAD_SCHED_CONSTANT_RDY_Q {
        NAME            Constant-time kernel ready queue
        SYNOPSIS        The traditional scheduler requires this parameter to \
                        be set to TRUE, which is the default.
        TYPE            BOOL
        DEFAULT         TRUE
}

Parameter POSIX_PTHREAD_RR_TIMESLICE {
        NAME            User POSIX thread time slice in ticks
        SYNOPSIS        This parameter can be used to configure the default \
                        time slicing interval for pthreads started with the \
                        SCHED_RR policy. To modify the time slice at run time, \
                        call kernelTimeSlice() with a different time slice \
                        value. The new time slice value only affects pthreads \
                        created after the kernelTimeSlice() call.
        TYPE            uint
        DEFAULT         10
}

Folder FOLDER_KERNEL_HARDENING {
        NAME            Kernel hardening features
        _CHILDREN       FOLDER_SECURITY
}

Component INCLUDE_KERNEL_HARDENING {
        NAME            Enable all kernel hardening features
        SYNOPSIS        This component applies protection to certain kernel \
                        components (text segment write protection, write \
                        protection of the exception vector table, task stack \
                        overflow and underflow detection, non-executable task \
                        stacks, non-executiable heap and data sections, and \
                        NULL pointer dereference detection for kernel tasks).
        _CHILDREN       FOLDER_KERNEL_HARDENING
        REQUIRES        INCLUDE_PROTECT_TEXT       \
                        INCLUDE_PROTECT_VEC_TABLE  \
                        INCLUDE_PROTECT_TASK_STACK \
                        INCLUDE_TASK_STACK_NO_EXEC
}

Component INCLUDE_LOGGING {
        NAME            Message logging
        SYNOPSIS        This component provides the logLib library. This \
                        library handles message logging. It is usually used to \
                        display error messages on the system console, but such \
                        messages can also be sent to a disk file or printer. \
                        The logMsg() and logTask() functions are the basic \
                        components of the logging system. The logMsg() \
                        function has the same calling sequence as printf(), \
                        but instead of formatting and outputting the message \
                        directly, it sends the format string and arguments to \
                        a message queue. The logTask() task waits for messages \
                        on this message queue. It formats each message \
                        according to the format string and arguments in the \
                        message, prepends the ID of the sender, and writes it \
                        on one or more file descriptors that have been \
                        specified as logging output streams (by logInit() \
                        or subsequently set by logFdSet() or logFdAdd()).
        MODULES         logLib.o
        INIT_RTN        logInit (consoleFd, MAX_LOG_MSGS, LOG_TASK_PRIORITY);
        PROTOTYPE       extern STATUS logInit (int, int, int);
        CFG_PARAMS      MAX_LOG_MSGS               \
                        LOG_TASK_PRIORITY
        HDR_FILES       logLib.h                   \
                        private/logLibP.h
        REQUIRES        INCLUDE_MSG_Q              \
                        INCLUDE_ANSI_STDIO         \
                        INCLUDE_SEM_MUTEX          \
                        INCLUDE_ANSI_STRNCPY       \
                        INCLUDE_TASK_CREATE_DELETE \
                        INCLUDE_MSG_Q_CREATE_DELETE\
                        INCLUDE_ATOMIC_OPERATORS
}

Component INCLUDE_SYSLOG {
        NAME            System logging (syslog)
        SYNOPSIS        This component provides the system logging facility. \
                        The syslogLib facility can be configured to log \
                        messages before it is initialized. These messages are \
                        stored in static memory until initialization is complete \
                        and the system logger has started (tLogTask). As the \
                        POSIX clocks facility is also not yet initialized \
                        when log messages are written to static memory, the \
                        timestamp assigned to these messages is not accurate \
                        (it starts from 1970-01-01T00:00:00.000000Z).
        MODULES         syslogLib.o
        INIT_RTN        syslogLibInit ();
        PROTOTYPE       extern void syslogLibInit (void);
        CFG_PARAMS      NUM_EARLY_SYSLOG_MSGS
        CONFIGLETTES    usrSyslog.c
        HDR_FILES       syslog.h                        \
                        private/logLibP.h
        REQUIRES        INCLUDE_LOGGING                 \
                        INCLUDE_POOL                    \
                        INCLUDE_ANSI_TIME               \
                        INCLUDE_POSIX_CLOCKS
#ifdef    _WRS_CONFIG_IPNET
        _REQUIRES       INCLUDE_IPCOM_SYSLOGD_CMD       \
                        INCLUDE_IPCOM_SYSLOGD_USE_LOG_FILE
#endif    /* _WRS_CONFIG_IPNET */
#ifdef    _WRS_CONFIG_IPCOM_DEFAULT_SYSLOG_PRIORITY
        INCLUDE_WHEN    INCLUDE_IPCOM
#endif    /* _WRS_CONFIG_IPCOM_DEFAULT_SYSLOG_PRIORITY */
}

Folder  FOLDER_UTILITIES {
        NAME            Utilities
        SYNOPSIS        This folder contains components and parameters that \
                        can be used to include and configure utilities in \
                        your project.
        CHILDREN        INCLUDE_HASH            \
                        INCLUDE_DLL             \
                        INCLUDE_RNG_BUF         \
                        INCLUDE_LSTLIB          \
                        INCLUDE_POOL            \
                        INCLUDE_STRING_SEARCH   \
                        INCLUDE_GETPAGESIZE
}

Folder  FOLDER_SERVICE {
        NAME            Service
        SYNOPSIS        This folder contains components and parameters that \
                        can be used to include and configure services in \
                        your project.
}

Component INCLUDE_HASH {
        NAME            Hash library
        SYNOPSIS        This component includes the hash library. This \
                        library supports the creation and maintenance of a \
                        chained hash table. Hash tables efficiently store hash \
                        nodes for fast access. They are frequently used for \
                        symbol tables, or other name-to-identifier functions. \
                        A chained hash table is an array of singly-linked list \
                        heads, with one list head per element of the hash table. \
                        During creation, a hash table is passed two \
                        user-definable functions, the hashing function, and the \
                        hash node comparator. The hashTblCreate( ) function \
                        creates a hash table. The hashTblInit( ) function \
                        initializes a hash table. The hashTblDelete() function \
                        deletes a hash table. The hashTblTerminate() function \
                        terminates a hash table. The hashTblDestroy() function \
                        destroys a hash table. The hashTblPut() function puts a \
                        hash node into the specified hash table. The \
                        hashTblFind() function finds a hash node that matches \
                        the specified key. The hashTblRemove() function removes \
                        a hash node from a hash table. The hashTblEach() \
                        function calls a function for each node in a hash table. \
                        The hashFuncIterScale() function provides an iterative \
                        scaling hashing function for strings. The hashFuncModulo() \
                        function provides a hashing function using a remainder \
                        technique. The hashFuncMultiply() function is a \
                        multiplicative hashing function. The hashKeyCmp() function \
                        compares keys as 32-bit identifiers. The hashKeyStrCmp() \
                        function compares keys based on strings they point to.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         hashLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       hashTblInit
        HDR_FILES       hashLib.h
        REQUIRES        INCLUDE_MEM_MGR_BASIC \
                        INCLUDE_SLL           \
                        INCLUDE_ANSI_STRCMP
}

Component INCLUDE_DLL {
        NAME            Doubly-linked lists
        SYNOPSIS        This component supports the creation and \
                        maintenance of doubly-linked lists. A doubly-linked \
                        list is a list that contains links to the next and \
                        previous nodes. Unlike singly-linked lists where \
                        traversal is only one way, doubly-linked lists allow \
                        traversals both ways. The user supplies a \
                        list descriptor (type DL_LIST) that contains pointers \
                        to the first and last nodes in the list. The nodes in \
                        the list can be any user-defined structure but they \
                        must reserve space for a pointer as their first \
                        element. The forward chain is terminated with a \
                        NULL pointer. This library, in conjunction with \
                        dllALib.s and the macros defined in dllLib.h, provides \
                        a reduced version of the functions offered in lstLib(1). \
                        For efficiency, the count field has been eliminated \
                        and enqueuing and dequeuing functions have been \
                        hand-optimized.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         dllLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       dllInit
}

Component INCLUDE_SLL {
        NAME            Single-linked lists
        SYNOPSIS        This component includes the sslLib library. This \
                        library supports the creation and \
                        maintenance of a singly-linked list. You must \
                        supply a list descriptor (type SL_LIST) that \
                        contains pointers to the first and last nodes \
                        in the list. The nodes in the list can be any \
                        user-defined structure, but they must reserve space \
                        for a pointer as their first element. The forward \
                        chain is terminated with a NULL pointer.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         sllLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       sllInit
}

Component INCLUDE_LSTLIB {
        NAME            Linked list library
        SYNOPSIS        This component provides the lstLib library. This \
                        library supports the creation and maintenance of a \
                        doubly-linked list. You must supply a list descriptor \
                        (type LIST) that contains pointers to the first and last \
                        nodes in the list, and a count of the number of nodes in \
                        the list. The nodes in the list can be any user-defined \
                        structure, but they must reserve space for two pointers \
                        as their first elements. Both the forward and backward \
                        chains are terminated with a NULL pointer. The \
                        linked-list library simply manipulates the linked-list \
                        data structures; no kernel functions are invoked. In \
                        particular, linked lists by themselves provide no task \
                        synchronization or mutual exclusion. If multiple tasks \
                        access a single linked list, that list must be guarded \
                        with some mutual-exclusion mechanism (such as a \
                        mutual-exclusion semaphore).
        REQUIRES        INCLUDE_ANSI_ABS    \
                        SELECT_MEM_ALLOC
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         lstLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       lstInit
        HDR_FILES       lstLib.h
}

Component INCLUDE_RNG_BUF {
        NAME            Ring buffers
        SYNOPSIS        This component provides the rngLib library. This library \
                        provides functions for creating and using ring buffers, \
                        which are first-in-first-out circular buffers. The \
                        functions simply manipulate the ring buffer data \
                        structure; no kernel functions are invoked. In particular, \
                        ring buffers by themselves provide no task synchronization \
                        or mutual exclusion.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         rngLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       rngCreate
        REQUIRES        INCLUDE_BLIB \
                        SELECT_MEM_ALLOC
}

Component INCLUDE_STRING_SEARCH {
        NAME            String search library
        SYNOPSIS        This component provides the memmem library. This library \
                        provides a string search to find the first occurrence of \
                        a substring within another string.
        MODULES         memmem.o
        LINK_SYMS       memmem memimem
}

Component INCLUDE_GETPAGESIZE {
        NAME            getpagesize support
        SYNOPSIS        This component links the getpagesize() function into the kernel.
        MODULES         getpagesize.o
        LINK_SYMS       getpagesize
}

Component INCLUDE_EXC_HANDLING {
        NAME            Exception handling
        SYNOPSIS        This component provides architecture-dependent facilities \
                        for handling processor exceptions.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         excArchLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        excVecInit ();
        HDR_FILES       excLib.h
        REQUIRES        INCLUDE_KERNEL
}

Component INCLUDE_EXC_SHOW {
        NAME            Exception show routines
        SYNOPSIS        This component provides detailed descriptions of exceptions \
                        in the error logs.
        MODULES         excArchShow.o
        INIT_RTN        excShowInit ();
        HDR_FILES       excLib.h
        INCLUDE_WHEN    INCLUDE_EXC_HANDLING \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_VM_SHOW {
        NAME            Virtual memory (VM) library show routines
        SYNOPSIS        This component provides support for the virtual memory show \
                        routines for the shell C interpreter.
        MODULES         vmShow.o
        INIT_RTN        vmShowInit ();
        HDR_FILES       vmLib.h
        INCLUDE_WHEN    INCLUDE_MMU_BASIC \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_BOOT_LINE_INIT {
        NAME            Read the boot line
        SYNOPSIS        This component provides support to parse some boot device \
                        configuration information.
        CONFIGLETTES    usrBootLine.c
        INIT_RTN        usrBootLineParse ((char *)BOOT_LINE_ADRS);
        HDR_FILES       sysLib.h string.h
        CFG_PARAMS      HOST_NAME_DEFAULT       \
                        TARGET_NAME_DEFAULT     \
                        HOST_USER_DEFAULT       \
                        HOST_PASSWORD_DEFAULT   \
                        SCRIPT_DEFAULT          \
                        OTHER_DEFAULT           \
                        BOOT_LINE_ADRS          \
                        DEFAULT_BOOT_LINE       \
                        BOOT_LINE_SIZE
}

Parameter HOST_NAME_DEFAULT {
        NAME            Default host name for the boot line
        SYNOPSIS        This parameter specifies the default value for the \
                        host name field of the VxWorks boot line.
        TYPE            string
        DEFAULT         "bootHost"
}

Parameter TARGET_NAME_DEFAULT {
        NAME            Default target name for the boot line
        SYNOPSIS        This parameter specifies the default value for the \
                        target name field of the VxWorks boot line (tn).
        TYPE            string
        DEFAULT         "vxTarget"
}

Parameter HOST_USER_DEFAULT {
        NAME            Default host user for the boot line
        SYNOPSIS        This parameter specifies the default value for the \
                        host user field of the VxWorks boot line (u).
        TYPE            string
        DEFAULT         "target"
}

Parameter HOST_PASSWORD_DEFAULT {
        NAME            Default host password for the boot line
        SYNOPSIS        This parameter specifies the default value for the \
                        host password field of the VxWorks boot line.
        TYPE            string
        DEFAULT         ""
}

Parameter SCRIPT_DEFAULT {
        NAME            Default script for the boot line
        SYNOPSIS        This parameter specifies the default value for the \
                        script field of the VxWorks boot line (s).
        TYPE            string
        DEFAULT         ""
}

Parameter OTHER_DEFAULT {
        NAME            Default other field for the boot line
        SYNOPSIS        This parameter specifies the default value for the \
                        other field of the VxWorks boot line (o).
        TYPE            string
        DEFAULT         ""
}

Component INCLUDE_ATOMIC_OPERATORS {
        NAME            Atomic operator support
        SYNOPSIS        This component provides support for atomic operators, \
                        such as vxAtomicAdd() and vxAtomicInc().
        MODULES         vxAtomicLib.o
        _CHILDREN       FOLDER_KERNEL
        LINK_SYMS       vxAtomicAdd
        HDR_FILES       vxAtomicLib.h
}

Component INCLUDE_POOL {
        NAME            Pool allocation
        SYNOPSIS        This component includes the Memory Pool library. Pools \
                        provide a fast and efficient memory management when an \
                        application uses a large number of identically sized \
                        memory blocks (for example, structures and objects) \
                        by minimizing the number of allocations from a memory \
                        partition. The use of pools also reduces possible \
                        fragmentation caused by frequent memory allocation and \
                        freeing. A pool is a dynamic set of statically sized \
                        memory blocks. All blocks in a pool are of the same \
                        size. The size of blocks are specified at pool \
                        creation and all the blocks are aligned on the \
                        block size; the block size must be a power of 2.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         poolLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        poolLibInit ();
        HDR_FILES       private/poolLibP.h
        REQUIRES        INCLUDE_KERNEL      \
                        INCLUDE_LSTLIB      \
                        INCLUDE_SEM_MUTEX   \
                        INCLUDE_MEM_MGR_BASIC
}

Component INCLUDE_POOL_SHOW {
        NAME            Pool allocation show routines
        SYNOPSIS        This component provides the poolShow library. This \
                        library provides functions that display information \
                        about memory pools in the system, and detailed \
                        statistics about individual memory pools.
        MODULES         poolShow.o
        LINK_SYMS       poolShow
        REQUIRES        INCLUDE_POOL
}

Component INCLUDE_SLL_CREATE_DELETE {
        NAME            Dynamic creation and destruction of a single-linked list
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         sllCreateLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        LINK_SYMS       sllCreate
        REQUIRES        INCLUDE_MEM_MGR_BASIC INCLUDE_SLL
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_DLL_CREATE_DELETE {
        NAME            Dynamic creation and destruction of a double-linked list
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         dllCreateLib.o
#else
        _REQUIRES       INCLUDE_KERNEL
#endif
        LINK_SYMS       dllCreate
        REQUIRES        INCLUDE_MEM_MGR_BASIC INCLUDE_DLL
		_CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_Q_FIFO {
        NAME            First-in, first-out (FIFO) queue
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         qFifoLib.o
#else
        _REQUIRES       INCLUDE_KERNEL
#endif
        REQUIRES        INCLUDE_DLL
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_Q_PRI_LIST {
        NAME            Queue library
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         qPriListLib.o
#else
        _REQUIRES       INCLUDE_KERNEL
#endif
        REQUIRES        INCLUDE_DLL   \
                        INCLUDE_KERNEL
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_Q_PRI_BMAP {
        NAME            Bit-mapped priority queue management library
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         qPriBMapLib.o
#else
        _REQUIRES       INCLUDE_KERNEL
#endif
        REQUIRES        INCLUDE_DLL
        CHILDREN        FOLDER_NOT_VISIBLE
}

Component INCLUDE_Q_PRI_DELTA {
        NAME            Priority queue with relative priority sorting library
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         qPriDeltaLib.o
#else
        _REQUIRES       INCLUDE_KERNEL
#endif
        REQUIRES        INCLUDE_KERNEL \
						INCLUDE_DLL
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_AVL_TREES {
        NAME            AVL tree library
        SYNOPSIS        AVL tree library with generic key.
        MODULES         avlLib.o
		_CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_AVL_UINT_TREES {
        NAME            UAVL tree library
        SYNOPSIS        AVL tree library with unsigned integer key.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         avlUintLib.o
#else
        _REQUIRES       INCLUDE_KERNEL
#endif
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_CHECKSUM {
        NAME            Checksum function
        SYNOPSIS        This component provides the portable internet checksum \
                        calculation function.
        MODULES         cksumLib.o
        HDR_FILES       vxLib.h
        LINK_SYMS       checksum
}

/*
 * Definition is generic, but not necessarily available on all arch.  Those
 * which support it will specify the INIT_ORDER, and override _CHILDREN to
 * make it visible/selectable.  The configlette, usrKernelStack.c, is listed
 * above under INCLUDE_KERNEL because it is always required (even on arch
 * which do not support the capability, where it is a no-op).
 */

Component INCLUDE_PROTECT_INTERRUPT_STACK {
        NAME            Enable guard pages for interrupt stack
        SYNOPSIS        Insert underflow and overflow guard pages on interrupt \
                        stack.
        _CHILDREN       FOLDER_NOT_VISIBLE
        CFG_PARAMS      INTERRUPT_STACK_OVERFLOW_SIZE        \
                        INTERRUPT_STACK_UNDERFLOW_SIZE
        REQUIRES        INCLUDE_MMU_BASIC
        PROTOTYPE       void usrKernelIntStkProtect (void);
        INIT_RTN        usrKernelIntStkProtect ();
}

Parameter INTERRUPT_STACK_OVERFLOW_SIZE {
        NAME            Interrupt stack overflow protection size
        SYNOPSIS        This parameter defines the size (in bytes) of the \
                        protected area above the interrupt stack.
        TYPE            uint
        DEFAULT         4096
}

Parameter INTERRUPT_STACK_UNDERFLOW_SIZE {
        NAME            Interrupt stack underflow protection size
        SYNOPSIS        This parameter defines the size (in bytes) of the \
                        protected area below the interrupt stack.
        TYPE            uint
        DEFAULT         4096
}

/* initialize vxMemProbe support in exc Handler hook */

Component INCLUDE_VXMEMPROBE_INIT {
        NAME            vxMemProbe initializer for exception handler support
        SYNOPSIS        This component initializes vxMemProbe( ) exception \
                        handler support.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         vxMemProbeLib.o
#else
        _REQUIRES       INCLUDE_KERNEL
#endif
        INIT_RTN        vxMemProbeInit ();
        HDR_FILES       vxLib.h private/vxMemProbeLibP.h
        REQUIRES        INCLUDE_EXC_HANDLING
}

/* Thread Local Storage (__thread variables) support */

Parameter DKM_TLS_SIZE {
        NAME            DKM TLS size
        SYNOPSIS        This parameter specifies the size of the extra thread \
                        local storage (TLS) block that is reserved for \
                        allocating thread local variables in downloadable \
                        kernel modules (DKMs).
        TYPE            int
        DEFAULT         0
}

Component INCLUDE_TLS {
        NAME            Thread variables support
        SYNOPSIS        This component provides thread-local storage, a \
                        compiler facility that allows for allocation of a \
                        variable such that there are unique instances of the \
                        variable for each thread (or task, in VxWorks terms).
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         tlsLib.o
#else
        _REQUIRES       INCLUDE_KERNEL
#endif
        HDR_FILES       private/tlsLibP.h
        CFG_PARAMS      DKM_TLS_SIZE
        REQUIRES        INCLUDE_TASK_CREATE_HOOKS
        INIT_BEFORE     INCLUDE_KERNEL
}

Component INCLUDE_GETOPT {
        NAME            getopt facility
        SYNOPSIS        This component provides the getopt facility which \
                        includes the getopt() function, a POSIX compliant, \
                        command-line parser that decodes arguments passed in \
                        the argc/argv vectors.
        MODULES         getopt.o
        HDR_FILES       unistd.h
        LINK_SYMS       getoptInit
        REQUIRES        INCLUDE_ANSI_STRING
        INCLUDE_WHEN    INCLUDE_SYSCTL_CLI
        _CHILDREN       FOLDER_UTILITIES
}

Folder FOLDER_RANDOM_NUM_GEN {
        NAME            Random number generator
        SYNOPSIS        This folder contains components and parameters that \
                        can be used to include and configure a random number \
                        generator in your project.
        CHILDREN        INCLUDE_RANDOM_NUM_GEN \
                        SELECT_RANDOM_NUM_GEN
}

Component INCLUDE_RANDOM_NUM_GEN {
        NAME            Random number generator
        SYNOPSIS        This component provides the randomNumGenLib library \
                        which provides the facility needed to generate a \
                        random number. For more information on the available \
                        functions, see the randomNumGenLib reference entry.
        MODULES         randomNumGenLib.o
        LINK_SYMS       randBytes
        REQUIRES        SELECT_RANDOM_NUM_GEN
}

Selection SELECT_RANDOM_NUM_GEN {
        NAME            Random number generator selection
        SYNOPSIS        Select a random number generator.
        COUNT           1-1
        CHILDREN        INCLUDE_SW_RANDOM_NUM_GEN
        DEFAULTS        INCLUDE_SW_RANDOM_NUM_GEN
}

Component INCLUDE_SW_RANDOM_NUM_GEN {
        NAME            Software random number generator
        SYNOPSIS        This component provides the randomSWNGenLib library. \
                        This library provides the implementation to generate \
                        a software random number. When an application requests \
                        random bytes, the content of the destination buffer is \
                        first used as random seed. Thereafter, the random \
                        state buffer is hashed and the hash output is returned \
                        as random bytes. If more bytes are requested than the \
                        hash output size, the hash output is used as seed and \
                        thereafter the random state buffer is hashed again. \
                        This process is repeated until the requested number \
                        of random bytes has been generated.
        MODULES         randomSWNumGenLib.o
        INIT_RTN        randomSWNumGenInit ();
        HDR_FILES       private/randomNumGenP.h
}


/* INITIALIZATION ORDER */

InitGroup usrInit {
        PROTOTYPE       void usrInit (int startType)
        SYNOPSIS        Pre-kernel initialization
#if (defined _WRS_CONFIG_ARCH_i86) && (defined _WRS_CONFIG_BOARDLIB) && (defined _WRS_CONFIG_DELAYED_HW_INIT)
        INIT_ORDER      INCLUDE_SYS_START    \
                        INCLUDE_CACHE_SUPPORT    \
                        INCLUDE_CPU_INIT      \
                        INCLUDE_USER_PRE_KERNEL_APPL_INIT       \
                        INCLUDE_EXC_SHOW    \
                        INCLUDE_EXC_HANDLING    \
						INCLUDE_VXCPULIB        \
                        INCLUDE_SYSHW_INIT    \
                        INCLUDE_CACHE_ENABLE    \
                        INCLUDE_OBJ_OWNERSHIP    \
                        INCLUDE_OBJ_INFO    \
                        INCLUDE_OBJ_LIB        \
                        INCLUDE_VXMEMPROBE_INIT \
                        INCLUDE_WINDVIEW_CLASS    \
                        INCLUDE_CLASS_LIST    \
                        INCLUDE_SEM_LIB     \
                        INCLUDE_SEM_MUTEX     \
                        INCLUDE_SEM_MUTEX_CREATE \
                        INCLUDE_CONDVAR        \
                        INCLUDE_CLASS_LIB     \
                        INCLUDE_BASE_KERNEL     \
                        INCLUDE_TASK_CREATE_HOOKS \
                        INCLUDE_CUSTOM_SCHEDULER \
                        INCLUDE_TLS         \
                        INCLUDE_SYSDBG_FLAG    \
                        INCLUDE_POSIX_UMASK \
                        INCLUDE_KERNEL
#else
        INIT_ORDER      INCLUDE_SYS_START    \
                        INCLUDE_CPU_INIT      \
                        INCLUDE_CACHE_SUPPORT    \
                        INCLUDE_USER_PRE_KERNEL_APPL_INIT       \
                        INCLUDE_EXC_SHOW    \
                        INCLUDE_EXC_HANDLING    \
                        INCLUDE_VXCPULIB        \
                        INCLUDE_SYSHW_INIT    \
                        INCLUDE_CACHE_ENABLE    \
                        INCLUDE_OBJ_OWNERSHIP    \
                        INCLUDE_OBJ_INFO    \
                        INCLUDE_OBJ_LIB        \
                        INCLUDE_VXMEMPROBE_INIT \
                        INCLUDE_WINDVIEW_CLASS    \
                        INCLUDE_CLASS_LIST    \
                        INCLUDE_SEM_LIB     \
                        INCLUDE_SEM_MUTEX     \
                        INCLUDE_SEM_MUTEX_CREATE \
                        INCLUDE_CONDVAR        \
                        INCLUDE_CLASS_LIB     \
                        INCLUDE_BASE_KERNEL     \
                        INCLUDE_TASK_CREATE_HOOKS \
                        INCLUDE_CUSTOM_SCHEDULER \
                        INCLUDE_TLS         \
                        INCLUDE_SYSDBG_FLAG    \
                        INCLUDE_POSIX_UMASK \
                        INCLUDE_KERNEL
#endif /* (defined _WRS_CONFIG_ARCH_i86) &&     */
       /* (defined _WRS_CONFIG_BOARDLIB) &&     */
       /* (defined _WRS_CONFIG_DELAYED_HW_INIT) */
}

InitGroup usrShowInit {
		INIT_RTN        usrShowInit ();
        SYNOPSIS        Enable object show routines
        INIT_ORDER      INCLUDE_TASK_SHOW            \
                        INCLUDE_CLASS_SHOW           \
                        INCLUDE_ISR_SHOW             \
                        INCLUDE_MEM_SHOW             \
                        INCLUDE_TASK_HOOKS_SHOW      \
                        INCLUDE_SEM_SHOW             \
                        INCLUDE_CONDVAR_SHOW         \
                        INCLUDE_MSG_Q_SHOW           \
                        INCLUDE_WATCHDOGS_SHOW       \
                        INCLUDE_VM_SHOW              \
                        INCLUDE_POSIX_MQ_SHOW        \
                        INCLUDE_POSIX_SEM_SHOW       \
						INCLUDE_HW_FP_SHOW           \
                        INCLUDE_ATA_SHOW             \
                        INCLUDE_TRIGGER_SHOW         \
                        INCLUDE_RBUFF_SHOW           \
                        INCLUDE_STDIO_SHOW           \
                        INCLUDE_EDR_SHOW             \
                        INCLUDE_HANDLE_SHOW          \
                        INCLUDE_POSIX_TIMER_SHOW     \
                        INCLUDE_DATACOLLECTOR_SHOW
}

InitGroup usrToolsInit {
        INIT_RTN        usrToolsInit ();
        SYNOPSIS        Software development tools
        INIT_ORDER      INCLUDE_SPY                  \
                        INCLUDE_JITTER_TOOL          \
                        INCLUDE_TIMEX                \
                        INCLUDE_EVENTPOINT_STUB      \
                        INCLUDE_EVENTPOINT           \
                        INCLUDE_DATACOLLECTOR        \
                        INCLUDE_SV_DATACOLLECTOR     \
                        INCLUDE_TRIGGERING           \
                        INCLUDE_VXDBG                \
                        usrWindviewInit              \
                        INCLUDE_DEBUG_AGENT          \
                        INCLUDE_POSIX_TRACE_TIMESTAMP \
                        INCLUDE_POSIX_TRACE          \
                        INCLUDE_TLS_LOADER_SUPPORT   \
                        INCLUDE_RTP_DEBUG_COMMAND    \
                        INCLUDE_TIP                  \
                        usrShowInit
}

InitGroup usrKernelCreateInit {
        INIT_RTN        usrKernelCreateInit ();
        SYNOPSIS        Object creation functions
        INIT_ORDER      INCLUDE_SEM_DELETE           \
                        INCLUDE_TASK_CREATE_DELETE   \
                        INCLUDE_TASK_STACK_ALLOC     \
                        INCLUDE_MSG_Q_CREATE_DELETE  \
                        INCLUDE_WATCHDOGS_CREATE_DELETE
}

InitGroup usrRtpInit {
        INIT_RTN        usrRtpInit ();
        SYNOPSIS        RTP init functions
        INIT_ORDER      INCLUDE_RTP_HOOKS            \
                        INCLUDE_RTP                  \
                        INCLUDE_RTP_SIGNALS          \
                        INCLUDE_SHARED_DATA          \
                        INCLUDE_SHL
}

InitGroup usrKernelCoreInit {
        INIT_RTN        usrKernelCoreInit ();
        SYNOPSIS        Core kernel facilities
        INIT_ORDER      INCLUDE_VXEVENTS             \
                        INCLUDE_SEM_BINARY           \
                        INCLUDE_SEM_COUNTING         \
                        INCLUDE_SEM_READ_WRITE       \
                        INCLUDE_SEM_OPEN             \
                        INCLUDE_CONDVAR_OPEN         \
                        INCLUDE_MSG_Q                \
                        INCLUDE_MSG_Q_OPEN           \
                        INCLUDE_WATCHDOGS            \
                        INCLUDE_TASK_OPEN            \
                        INCLUDE_WDB_TASK_HOOKS       \
                        INCLUDE_VXDBG_HOOK
}

InitGroup usrKernelExtraInit {
        INIT_RTN        usrKernelExtraInit ();
        SYNOPSIS        Extended kernel facilities
        INIT_ORDER      INCLUDE_HASH                 \
                        INCLUDE_TASK_VARS            \
                        INCLUDE_EXC_SIGNALS          \
                        INCLUDE_SIGNALS              \
                        INCLUDE_SIGEVENT             \
                        INCLUDE_POSIX_DIRLIB         \
                        INCLUDE_POSIX_USER_GROUP     \
                        INCLUDE_POSIX_MQ             \
                        INCLUDE_POSIX_PTHREADS       \
                        INCLUDE_POSIX_SEM            \
                        INCLUDE_POSIX_SIGNALS        \
                        INCLUDE_POSIX_CLOCKS         \
                        INCLUDE_POSIX_TIMERS         \
                        INCLUDE_TIMER_OPEN           \
                        INCLUDE_SW_RANDOM_NUM_GEN
}

InitGroup usrRoot {
        PROTOTYPE       void usrRoot (char *pMemPoolStart, unsigned memPoolSize)
        SYNOPSIS        Entry point for post-kernel initialization
#ifdef _WRS_CONFIG_VXBUS_LEGACY
        INIT_ORDER      INCLUDE_TM_TIMING_FRAMEWORK  \
                        usrKernelCoreInit            \
                        INCLUDE_MEM_ALLOT            \
                        INCLUDE_POOL                 \
                        INCLUDE_MEM_EDR              \
                        INCLUDE_MEM_MGR_FULL         \
                        INCLUDE_MEM_MGR_BASIC        \
                        INCLUDE_KERNEL_PROXIMITY_HEAP \
                        INCLUDE_MEM_PART_CACHE       \
                        INCLUDE_MEM_EDR2             \
                        INCLUDE_AIM_MMU_CONFIG       \
                        INCLUDE_PG_POOL_LIB          \
                        INCLUDE_PG_POOL_VIRT_LIB     \
                        INCLUDE_PG_POOL_PHYS_LIB     \
                        INCLUDE_MMU_BASIC            \
                        INCLUDE_TM_TIMING_FRAMEWORK_PRE_MMU_INIT \
                        INCLUDE_MMU_GLOBAL_MAP       \
                        INCLUDE_TM_TIMING_FRAMEWORK_POST_MMU_INIT \
                        INCLUDE_PMAP_LIB             \
                        INCLUDE_KERNEL_COMMON_HEAP   \
                        usrKernelCreateInit          \
                        INCLUDE_APPL_LOG_UTIL        \
                        INCLUDE_USER_POST_KERNEL_APPL_INIT      \
                        INCLUDE_MEM_MGR_INFO         \
                        INCLUDE_USER_RESERVED_MEMORY \
                        INCLUDE_ENV_VARS             \
                        INCLUDE_EDR_PM               \
                        INCLUDE_EDR_ERRLOG           \
                        INCLUDE_EDR_STUB             \
                        INCLUDE_CACHE_COMPACT_DMA_SUPPORT    \
                        INCLUDE_PROTECT_TEXT         \
                        INCLUDE_PROTECT_TASK_STACK   \
                        INCLUDE_TASK_STACK_NO_EXEC   \
                        INCLUDE_SYSHW_INIT_1         \
                        INCLUDE_IDLE_TASKS           \
                        INCLUDE_DEFERRED_INTERRUPT_ENABLE    \
                        INCLUDE_SYSHW_INIT2          \
                        INCLUDE_SYSCLK_INIT          \
                        usrClkInit                   \
                        INCLUDE_CPC                  \
                        usrDshmInit                  \
                        usrMultiosInit               \
                        INCLUDE_VXDBG_CPU_CONTROL    \
                        INCLUDE_SW_FP                \
                        INCLUDE_HW_FP                \
                        INCLUDE_PG_MGR_BASIC         \
                        INCLUDE_PG_MGR_LIB           \
                        INCLUDE_SYSCTL               \
                        INCLUDE_ERF                  \
                        usrRtpInit                   \
                        INCLUDE_CORE_DUMP            \
                        INCLUDE_CORE_DUMP_RTP        \
                        INCLUDE_POSIX_PTHREAD_SCHEDULER     \
                        INCLUDE_PX_SCHED_SPORADIC_POLICY     \
                        INCLUDE_MMAP                 \
                        INCLUDE_POSIX_MAPPED_FILES   \
                        INCLUDE_POSIX_SHM            \
                        INCLUDE_POSIX_SHM_API        \
                        INCLUDE_DEVMEM               \
                        usrKernelExtraInit           \
                        usrIosExtraInit              \
                        INCLUDE_SOCKLIB              \
                        INCLUDE_AF_MIPC_SOCKETS      \
                        INCLUDE_CNS                  \
                        INCLUDE_SSI                  \
                        INCLUDE_DSI_DYNAMIC_INIT     \
                        INCLUDE_USER_PRE_NETWORK_APPL_INIT    \
                        INCLUDE_AF_MIPC_SOCKETS      \
                        INCLUDE_SELECT_SUPPORT       \
                        INCLUDE_ACPI                 \
                        INCLUDE_ACPI_SHOW            \
                        INCLUDE_ACPI_CPU_CONFIG      \
                        INCLUDE_CPU_PWR_ARCH         \
                        INCLUDE_DEV_PWR_MGMT         \
                        INCLUDE_CPU_TURBO            \
                        INCLUDE_CPU_PERFORMANCE_MGMT \
                        INCLUDE_CPU_ODG_POLICY_MGMT  \
                        INCLUDE_PWR_POLICY_MGR       \
                        INCLUDE_CPU_LIGHT_PWR_MGR    \
                        INCLUDE_TICKLESS_IDLE        \
                        INCLUDE_CTORS_DTORS          \
                        INCLUDE_CPLUS                \
                        INCLUDE_CPLUS_DEMANGLER      \
                        usrScInit                    \
                        INCLUDE_PROTECT_INTERRUPT_STACK_NON_CORE0 \
                        INCLUDE_SMP_INIT             \
                        usrTipcInit                  \
                        INCLUDE_DSI_STATIC_INIT      \
                        INCLUDE_HTTP                 \
                        INCLUDE_BANNER               \
                        usrToolsInit                 \
                        usrWriftInit                 \
                        INCLUDE_MMU_OPTIMIZE         \
                        INCLUDE_TM_TIMING_FRAMEWORK_END        \
                        INCLUDE_USER_APPL
#else /* _WRS_CONFIG_VXBUS_LEGACY */
        INIT_ORDER      INCLUDE_TM_TIMING_FRAMEWORK  \
                        usrKernelCoreInit            \
                        INCLUDE_MEM_ALLOT            \
                        INCLUDE_POOL                 \
                        INCLUDE_MEM_EDR              \
                        INCLUDE_MEM_MGR_FULL         \
                        INCLUDE_MEM_MGR_BASIC        \
                        INCLUDE_KERNEL_PROXIMITY_HEAP        \
                        INCLUDE_MEM_PART_CACHE       \
                        INCLUDE_MEM_EDR2             \
                        INCLUDE_AIM_MMU_CONFIG       \
                        INCLUDE_PG_POOL_LIB          \
                        INCLUDE_PG_POOL_VIRT_LIB     \
                        INCLUDE_PG_POOL_PHYS_LIB     \
                        INCLUDE_MMU_BASIC            \
                        INCLUDE_TM_TIMING_FRAMEWORK_PRE_MMU_INIT \
                        INCLUDE_MMU_GLOBAL_MAP       \
                        INCLUDE_TM_TIMING_FRAMEWORK_POST_MMU_INIT \
                        INCLUDE_PMAP_LIB             \
                        INCLUDE_KERNEL_COMMON_HEAP   \
                        usrKernelCreateInit          \
                        INCLUDE_APPL_LOG_UTIL        \
                        INCLUDE_USER_POST_KERNEL_APPL_INIT      \
                        INCLUDE_MEM_MGR_INFO         \
                        INCLUDE_USER_RESERVED_MEMORY \
                        INCLUDE_ENV_VARS             \
                        INCLUDE_EDR_PM               \
                        INCLUDE_EDR_ERRLOG           \
                        INCLUDE_EDR_STUB             \
                        INCLUDE_CACHE_COMPACT_DMA_SUPPORT    \
                        INCLUDE_PROTECT_TEXT         \
                        INCLUDE_PROTECT_TASK_STACK   \
                        INCLUDE_TASK_STACK_NO_EXEC   \
                        INCLUDE_SYSHW_INIT_1         \
                        INCLUDE_BOARD_INIT           \
                        INCLUDE_SYSCTL               \
                        INCLUDE_ERF                  \
                        INCLUDE_IDLE_TASKS           \
                        INCLUDE_DEFERRED_INTERRUPT_ENABLE    \
                        INCLUDE_SYSHW_INIT2          \
                        usrClkInit                   \
                        INCLUDE_CPC                  \
                        usrDshmInit                  \
                        usrMultiosInit               \
                        INCLUDE_VXDBG_CPU_CONTROL    \
                        INCLUDE_SW_FP                \
                        INCLUDE_HW_FP                \
                        INCLUDE_PG_MGR_BASIC         \
                        INCLUDE_PG_MGR_LIB           \
                        usrRtpInit                   \
                        INCLUDE_CORE_DUMP            \
                        INCLUDE_CORE_DUMP_RTP        \
                        INCLUDE_POSIX_PTHREAD_SCHEDULER     \
                        INCLUDE_PX_SCHED_SPORADIC_POLICY     \
                        INCLUDE_MMAP                 \
                        INCLUDE_POSIX_MAPPED_FILES   \
                        INCLUDE_POSIX_SHM            \
                        INCLUDE_POSIX_SHM_API        \
                        INCLUDE_DEVMEM               \
                        usrKernelExtraInit           \
                        usrIosExtraInit              \
                        INCLUDE_SOCKLIB              \
                        INCLUDE_AF_MIPC_SOCKETS      \
                        INCLUDE_CNS                  \
                        INCLUDE_SSI                  \
                        INCLUDE_DSI_DYNAMIC_INIT     \
                        INCLUDE_USER_PRE_NETWORK_APPL_INIT      \
                        INCLUDE_AF_MIPC_SOCKETS      \
                        INCLUDE_SELECT_SUPPORT       \
                        INCLUDE_ACPI                 \
                        INCLUDE_ACPI_SHOW            \
                        INCLUDE_ACPI_CPU_CONFIG      \
                        INCLUDE_CPU_PWR_ARCH         \
                        INCLUDE_DEV_PWR_MGMT         \
                        INCLUDE_CPU_TURBO            \
                        INCLUDE_CPU_PERFORMANCE_MGMT \
                        INCLUDE_CPU_ODG_POLICY_MGMT  \
                        INCLUDE_PWR_POLICY_MGR       \
                        INCLUDE_CPU_LIGHT_PWR_MGR    \
                        INCLUDE_TICKLESS_IDLE        \
                        INCLUDE_CTORS_DTORS          \
                        INCLUDE_CPLUS                \
                        INCLUDE_CPLUS_DEMANGLER      \
                        usrScInit                    \
                        INCLUDE_PROTECT_INTERRUPT_STACK_NON_CORE0 \
                        INCLUDE_SMP_INIT             \
                        usrTipcInit                  \
                        INCLUDE_DSI_STATIC_INIT      \
                        INCLUDE_HTTP                 \
                        INCLUDE_BANNER               \
                        usrToolsInit                 \
                        usrWriftInit                 \
                        INCLUDE_MMU_OPTIMIZE         \
                        INCLUDE_TM_TIMING_FRAMEWORK_END  \
                        INCLUDE_USER_APPL
#endif /* ! _WRS_CONFIG_VXBUS_LEGACY */
}

InitGroup usrScInit {
        INIT_RTN        usrScInit ();
        SYNOPSIS        The system call initialization sequence
        INIT_ORDER      INCLUDE_SC_POSIX
}

Parameter TASK_USER_EXC_STACK_SIZE {
        NAME            User task exception stack size
        SYNOPSIS        This parameter defines the size (in bytes) of the \
                        exception stack for the user tasks.
        TYPE            uint
#ifdef _WRS_CONFIG_LP64
        DEFAULT         16384
#else
        DEFAULT         8192
#endif
}

Parameter TASK_KERNEL_EXC_STACK_SIZE {
        NAME            Kernel task exception stack size
        SYNOPSIS        This parameter defines the size of the exception \
                        stack for kernel tasks.
        TYPE            size_t
        DEFAULT         KERNEL_TASK_EXC_STACK_SIZE
}

Parameter TASK_USER_EXC_STACK_OVERFLOW_SIZE {
        NAME            User task exception stack overflow protection size
        SYNOPSIS        This parameter defines the size (in bytes) of the \
                        protected area above the task stacks.
        TYPE            uint
        DEFAULT         4096
}

Parameter TASK_USER_EXEC_STACK_OVERFLOW_SIZE {
        NAME            User task execution stack overflow protection size
        SYNOPSIS        This parameter defines the size (in bytes) of the \
                        protected area above the task stacks.
        TYPE            uint
        DEFAULT         4096
}

Parameter TASK_USER_EXEC_STACK_UNDERFLOW_SIZE {
        NAME            User task execution stack underflow protection size
        SYNOPSIS        This parameter defines the size (in bytes) of the \
                        protected area below the task stacks.
        TYPE            uint
        DEFAULT         4096
}

Parameter TASK_KERNEL_EXEC_STACK_OVERFLOW_SIZE {
        NAME            Kernel task execution stack overflow protection size
        SYNOPSIS        This parameter defines the size (in bytes) of the \
                        protected area above the task stacks.
        TYPE            uint
        DEFAULT         4096
}

Parameter TASK_KERNEL_EXEC_STACK_UNDERFLOW_SIZE {
        NAME            Kernel task execution stack underflow protection size
        SYNOPSIS        This parameter defines the size (in bytes) of the \
                        protected area below the task stacks.
        TYPE            uint
        DEFAULT         4096
}

Parameter TASK_PRIORITY_SET_COMPATIBLE {
        NAME            Enable compatible mode for task priority setting
        SYNOPSIS        This configuration parameter is used to enable \
                        the backward compatible (but incorrect) way of \
                        handling task priority changes. When set to TRUE, \
                        a running task may be preempted when its priority \
                        is lowered to a level at which other ready tasks \
                        are waiting. This configuration option will be \
                        removed in a future release.
        TYPE            BOOL
        DEFAULT         FALSE
}

Parameter INT_LOCK_LEVEL {
        NAME            Interrupt lock level
        SYNOPSIS        This parameter sets the interrupt lock level.
}

Parameter ROOT_STACK_SIZE {
        NAME            Root stack size
        SYNOPSIS        This parameter sets the root task stack size in bytes.
}

Parameter ISR_STACK_SIZE {
        NAME            ISR stack size
        SYNOPSIS        This parameter sets the interrupt service routine \
                        (ISR) stack size in bytes.
}

Parameter WIND_JOBS_MAX  {
        NAME            Kernel work queue size
        SYNOPSIS        This parameter sets the kernel work queue size (number \
                        of entries). It must be a power of 2. If it is set to \
                        a value below 64, it can cause work queue panics in \
                        the system. 
        TYPE            UINT32
        DEFAULT         64
}

Parameter SEM_RW_MAX_CONCURRENT_READERS {
        NAME            Maximum number of concurrent RW semaphore readers
        SYNOPSIS        This parameter sets the maximum number of concurrent \
                        RW semaphore readers.
        TYPE            UINT32
        DEFAULT         32
}

Parameter MAX_ISR_JOBS {
        NAME            Maximum number of jobs posted from ISR level
        SYNOPSIS        This parameter defines the maximum number of jobs that \
                        can be posted to tExcTask from the interrupt service \
                        routine (ISR) level. In most applications, the default \
                        value is sufficient to handle the jobs posted from the \
                        ISR level. If the number of jobs posted exceeds \
                        MAX_ISR_JOBS, an overflow error occurs. Before \
                        increasing the value of MAX_ISR_JOBS, Wind River \
                        recommends that you review the ISRs that are posting \
                        jobs to ensure the ISR is not improperly posting more \
                        jobs than the system can handle at any one time.
        TYPE            UINT32
        DEFAULT         16
}

Parameter JOB_TASK_STACK_SIZE {
        NAME            Job task stack size
        SYNOPSIS        This parameter specifies the job task stack size.
        TYPE            UINT32
        DEFAULT         8000
}

Parameter USER_I_MMU_ENABLE {
        NAME            Instruction MMU
        SYNOPSIS        This parameter enables the instruction MMU.
        TYPE            exists
        DEFAULT         TRUE
}

Parameter USER_D_MMU_ENABLE {
        NAME            Data MMU
        SYNOPSIS        This parameter enables the data MMU.
        TYPE            exists
        DEFAULT         TRUE
}

Parameter MAX_LOG_MSGS {
        NAME            Maximum number of queued messages
        SYNOPSIS        This parameter specifies the maximum number of queued \
                        messages. The default value is 50.
        TYPE            uint
        DEFAULT         50
}

Parameter LOG_TASK_PRIORITY {
        NAME            Logging daemon task priority
        SYNOPSIS        This parameter defines the priority with which the \
                        logging task, tLogTask, is spawned. The default value \
                        is zero.
        TYPE            int
        DEFAULT         0
}

Parameter NUM_EARLY_SYSLOG_MSGS {
        NAME            Maximum number of early messages for syslog
        SYNOPSIS        This parameter defines the number of messages that can \
                        be logged before the logging facility is initialized. \
                        The default value is zero.
        TYPE            uint
        DEFAULT         0
}

Parameter NUM_DRIVERS {
        NAME            Maximum number of drivers
        SYNOPSIS        This parameter sets the maximum number of drivers. By \
                        default, it is set to 20.
        TYPE            uint
        DEFAULT         20
}

Parameter MQ_HASH_SIZE {
        NAME            POSIX message queue hash table size
        SYNOPSIS        This parameter sets the size for the POSIX message \
                        queue hash table size. By default it is set to zero.
        TYPE            uint
        DEFAULT         0
}

Parameter NUM_SIGNAL_QUEUES {
        NAME            POSIX queued signal count
        SYNOPSIS        This parameter sets the maximum number of queued \
                        signals in the kernel. The default is 16.
        TYPE            uint
        DEFAULT         16
}

Parameter ENV_VAR_USE_HOOKS {
        NAME            Install environment variable task create/delete hooks
        SYNOPSIS        This parameter controls installHooks. If installHooks \
                        is TRUE, task create and delete hooks are installed \
                        that can optionally create and destroy private \
                        environments for the task being created or destroyed, \
                        depending on the state of VX_PRIVATE_ENV in the task \
                        options word. If installHooks is FALSE and a task \
                        requires a private environment, the application must \
                        create and destroy the private environment using \
                        envPrivateCreate( ) and envPrivateDestroy( ).
        TYPE            bool
        DEFAULT         TRUE
}

Parameter OBJ_LIBRARY_OPTIONS {
        NAME            Default option for the object library
        SYNOPSIS        This parameter specifies global options for the object \
                        library.
        TYPE            int
        DEFAULT         0
}

Parameter EDR_PM_ARENA {
        NAME            ED&R PM arena definition
        SYNOPSIS        By default, the error detection and reporting \
                        persistent memory arena is defined by the function \
                        'pmDefaultArena'. It can be over-ridden in usrPmInit.c \
                        if necessary, for example, to place the default PM \
                        arena in non-volatile memory for a specific BSP.
        DEFAULT         pmDefaultArena
}

Parameter EDR_ERRLOG_SIZE {
        NAME            ED&R error log size
        SYNOPSIS        This parameter sets the size of the persistent memory \
                        area reserved for error records (in bytes). By \
                        default, it is set to one-half of the persistent \
                        memory available.
        DEFAULT         (pmFreeSpace (EDR_PM_ARENA) / 2)
}

Parameter EDR_RECORD_SIZE {
        NAME            Size of each ED&R record
        SYNOPSIS        This parameter is used to change the default size \
                        (in bytes) of error records. Note that, for \
                        performance reasons, all records are the same size.
        DEFAULT         4096
}

Parameter PM_RESERVED_MEM {
        NAME            Persistent memory region size
        SYNOPSIS        This parameter sets the size of the persistent memory \
                        region (in bytes). By default, it is set to six pages \
                        of memory.
#ifdef _WRS_CONFIG_UNSUPPORTS_MMU
        DEFAULT         (24576)
#else
        DEFAULT         (6 * VM_PAGE_SIZE)
#endif
}

Parameter MAX_REBOOT_HOOKS {
        NAME            Maximum number of reboot hooks
        SYNOPSIS        This parameter sets the maximum number of reboot hooks \
                        that can be set. The default value is 5.
        TYPE            int
        DEFAULT         5
}

Parameter MAX_POWER_OFF_HOOKS {
        NAME            Maximum number of power off hooks
        SYNOPSIS        This parameter sets the maximum number of power off \
                        hooks that can be set. The default value is 5.
        TYPE            int
        DEFAULT         5
}

Parameter VX_GLOBAL_NO_STACK_FILL {
        NAME            Disable stack fill on all tasks
        SYNOPSIS        This parameter is used to disable the stack fill. When \
                        set to TRUE, stack fill is disabled.
        TYPE            BOOL
        DEFAULT         FALSE
}

#ifdef _WRS_CONFIG_SMP
Parameter VX_SMP_NUM_CPUS {
        NAME            Number of CPUs to be enabled for SMP
        SYNOPSIS        This parameter sets the number of CPUs that you wish \
                        to enable for symmetric multiprocessing (SMP). This \
                        value must be greater than zero. 
        TYPE            UINT
        DEFAULT         2
        _CFG_PARAMS     INCLUDE_KERNEL
}

Parameter ENABLE_ALL_CPUS {
        NAME            Enable all configured CPUs for SMP
        SYNOPSIS        This parameter enables all configured CPUs for \
                        symmetric multiprocessing (SMP).
        TYPE            BOOL
        DEFAULT         TRUE
        _CFG_PARAMS     INCLUDE_KERNEL
}

Parameter VX_ENABLE_CPU_TIMEOUT {
        NAME            Timeout for enabling additional CPUs in SMP
                        This parameter sets the timeout (in seconds) for \
                        enabling additional CPUs in symmetric multiprocessing \
                        (SMP). 
        TYPE            int
        DEFAULT         5
        _CFG_PARAMS     INCLUDE_KERNEL
}

Parameter VX_SMP_CPU_EXPLICIT_RESERVE {
        NAME            SMP CPUs to be excluded from indiscriminate reservation
        SYNOPSIS        This parameter specifies the CPUs that are excluded \
                        from the indiscriminate reservation pool. They are \
                        not, however, prevented from being explicitly reserved.
        TYPE            string
        DEFAULT         ""
        _CFG_PARAMS     INCLUDE_KERNEL
}
#endif /* _WRS_CONFIG_SMP */

/* spinLock library API */

Api API_SPINLOCK {
        NAME            Spinlock libraries API
        SYNOPSIS        Spinlock libraries API selection
        _CHILDREN       FOLDER_KERNEL
        _REQUIRES       INCLUDE_KERNEL
        DEFAULTS        INCLUDE_SPINLOCK
}

/* spinLock component that offers debugging code at runtime */

#ifdef _WRS_CONFIG_SMP
Component INCLUDE_SPINLOCK_DEBUG {
        NAME            Spinlock with debugging
        SYNOPSIS        This component provides support for spinlocks with \
                        debugging capabilities.
        MODULES         spinLockSmpDbgLib.o
        PROVIDES        API_SPINLOCK
        ARCHIVE         libsplDbg.a
}
#endif /* _WRS_CONFIG_SMP */

/* spinLock component without debugging */

Component INCLUDE_SPINLOCK {
        NAME            Spinlock
        SYNOPSIS        This component provides support for spinlocks without \
                        debugging capabilities.
#ifdef _WRS_CONFIG_SMP
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         spinLockSmpLib.o
        ARCHIVE         libspl.a
#else
        _REQUIRES       INCLUDE_KERNEL
#endif
#else
        MODULES         spinLockUpLib.o
#endif
        PROVIDES        API_SPINLOCK
}

Component INCLUDE_SPINLOCK_ISR_ND {
        NAME            Fast, non-deterministic, ISR callable spinlocks
        SYNOPSIS        This component provides fast, simple, ISR-usable, \
                        test-and-test-and-set spinlocks.
        MODULES         spinLockIsrNdLib.o
        LINK_SYMS       spinLockIsrNdTake spinLockIsrNdInit
        _CHILDREN       FOLDER_KERNEL
}

Component INCLUDE_SPINLOCK_ND_TIMED {
        NAME            AMP/SMP safe, ISR-callable, time-limited spinlocks
        SYNOPSIS        This component provides time-limited spinlocks that \
                        are usable in any VxWorks configuration: \
                        uniprocessor, symmetric multiprocessor, or asymmetric \
                        multiprocessor.
        MODULES         spinLockNdTimedLib.o
        LINK_SYMS       spinLockNdTimedTake
        _CHILDREN       FOLDER_KERNEL
}

Component INCLUDE_SYSDBG_FLAG {
        NAME            System debug flag
        SYNOPSIS        This component provides a flag indicating the system \
                        is in 'debug' mode.
        MODULES         sysDbgLib.o
        INIT_RTN        sysDebugModeInit ();
        HDR_FILES       private/sysDbgLibP.h
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_DEBUG_KPRINTF {
        NAME            kprintf support
        SYNOPSIS        This component provides the kprintf( ) function that \
                        performs formatted output. This is similar to \
                        printf( ) except that the output characters are sent \
                        to the target's console port (not the STD_OUT file \
                        descriptor) in polled mode.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         kprintfLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        HDR_FILES       stdio.h private/kwriteLibP.h
        INIT_RTN        _func_kprintf = kprintf;
#ifdef _WRS_CONFIG_VXBUS_LEGACY
        REQUIRES        SELECT_DEBUG_KWRITE
#else
        _INIT_ORDER     usrInit
        INIT_BEFORE     INCLUDE_BOARD_LIB_INIT
        INIT_AFTER      INCLUDE_SYS_START
#endif /* ! _WRS_CONFIG_VXBUS_LEGACY */
}

#ifdef _WRS_CONFIG_VXBUS_LEGACY
Folder FOLDER_KERNEL_DEBUG {
        NAME            Kernel debug console
        SYNOPSIS        This folder contains components and parameters related \
                        to kernel write such as kprintf( ), kputs( ), and \
                        kwrite( ).
        CHILDREN        INCLUDE_DEBUG_KPRINTF \
                        INCLUDE_DEBUG_KPUTS   \
                        SELECT_DEBUG_KWRITE
        DEFAULT         INCLUDE_DEBUG_KPRINTF \
                        INCLUDE_DEBUG_KPUTS
}

Selection SELECT_DEBUG_KWRITE {
        NAME            Kernel write facility
        SYNOPSIS        Select the component to provide the output function \
                        for the kernel write facility.
        COUNT           1-1
        CHILDREN        INCLUDE_DEBUG_KWRITE_SIO \
                        INCLUDE_DEBUG_KWRITE_USER
        DEFAULTS        INCLUDE_DEBUG_KWRITE_SIO
}

Component INCLUDE_DEBUG_KPUTS {
        NAME           kputs support
        SYNOPSIS       This component provides the kputs( ) function that \
                       performs unformatted string output to the target's \
                       console port (not the STD_OUT file descriptor) in \
                       polled mode.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES        kputsLib.o
#else
        _REQUIRES      INCLUDE_KERNEL
#endif
       LINK_SYMS       kputs
       REQUIRES        SELECT_DEBUG_KWRITE
}

Component INCLUDE_DEBUG_KWRITE_SIO {
        NAME            kwrite serial I/O
        SYNOPSIS        This component provides the polled mode serial I/O \
                        function for kprintf( ) and kputs( ).
        MODULES         kwriteSioLib.o
        PROTOTYPE       extern void kwriteSioInit (int numTty, int baud);
        INIT_RTN        kwriteSioInit (CONSOLE_TTY, CONSOLE_BAUD_RATE);
        REQUIRES        INCLUDE_SIO_POLL
}

Component INCLUDE_DEBUG_KWRITE_USER {
        NAME            User-provided kwrite function
        SYNOPSIS        This component enables the selection of a user \
                        provided output function for kprintf( ) and kputs( ).
        CONFIGLETTES    usrDebugKwrite.c
        PROTOTYPE       STATUS DEBUG_KWRITE_USR_RTN (char * pBuf, size_t len);
        INIT_RTN        usrKwriteInit (DEBUG_KWRITE_USR_RTN);
        CFG_PARAMS      DEBUG_KWRITE_USR_RTN
}

Parameter DEBUG_KWRITE_USR_RTN {
        NAME            usrKwriteInit function
        SYNOPSIS        This configuration paramater defines the output \
                        function for use with kprintf( ) and kputs( ).
        TYPE            void *
        DEFAULT         NULL
}

InitGroup usrDebugKWriteInit {
        INIT_RTN        usrDebugKWriteInit ();
        SYNOPSIS        Kernel printf initialization
        INIT_ORDER      INCLUDE_DEBUG_KWRITE_SIO    \
                        INCLUDE_DEBUG_KWRITE_USER    \
                        INCLUDE_DEBUG_KPRINTF
#ifdef _WRS_CONFIG_DELAYED_HW_INIT
        _INIT_ORDER     usrRoot
        INIT_AFTER      INCLUDE_SYSHW_INIT_1
        INIT_BEFORE     INCLUDE_IDLE_TASKS
#else /* _WRS_CONFIG_DELAYED_HW_INIT */

#ifdef _WRS_CONFIG_BOARDLIB
        _INIT_ORDER     usrRoot
        INIT_AFTER      INCLUDE_SYSHW_INIT_1
        INIT_BEFORE     INCLUDE_IDLE_TASKS
#else /* !_WRS_CONFIG_BOARDLIB */
       _INIT_ORDER     usrInit
        INIT_AFTER      INCLUDE_SYSHW_INIT
        INIT_BEFORE     INCLUDE_CACHE_ENABLE
#endif /* _WRS_CONFIG_BOARDLIB */
#endif /* _WRS_CONFIG_DELAYED_HW_INIT */
}

#else /* _WRS_CONFIG_VXBUS_LEGACY */
Folder FOLDER_KERNEL_DEBUG {
        NAME            Early kernel initialization debug messages
        CHILDREN        INCLUDE_DEBUG_KPUTS        \
                        INCLUDE_DEBUG_KWRITE_USER    \
                        INCLUDE_DEBUG_KPRINTF
        DEFAULT         INCLUDE_DEBUG_KPUTS
}

Component INCLUDE_DEBUG_KPUTS {
        NAME            kputs support
        SYNOPSIS        This component provides the kputs( ) function that \
                        performs unformatted string output to the target's \
                        console port (not the STD_OUT file descriptor) in \
                        polled mode.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         kputsLib.o
#else
        _REQUIRES       INCLUDE_KERNEL 
#endif
        LINK_SYMS       kputs
}

Component INCLUDE_DEBUG_KWRITE_USER {
        NAME            User-provided kwrite function
        SYNOPSIS        This component enables the selection of a user \
                        provided output function for kprintf( ) and kputs( ).
        CONFIGLETTES    usrDebugKwrite.c
        PROTOTYPE       STATUS DEBUG_KWRITE_USR_RTN(char * pBuf, size_t len);
        INIT_RTN        usrKwriteInit (DEBUG_KWRITE_USR_RTN);
        CFG_PARAMS      DEBUG_KWRITE_USR_RTN
        _INIT_ORDER     usrRoot
        INIT_AFTER      INCLUDE_SYSHW_INIT2
        INIT_BEFORE     usrClkInit
}

Parameter DEBUG_KWRITE_USR_RTN {
        NAME            usrKwriteInit function
        SYNOPSIS        This configuration parameter defines the output \
                        function for use with kprintf( ) and kputs( ).
        TYPE            void *
        DEFAULT         NULL
}

#endif /* _WRS_CONFIG_VXBUS_LEGACY */
