/* usrMmuInit.c - memory management unit initialization */

/*
 * Copyright (c) 1992-1996, 1998-2011, 2013-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
07aug17,pcs  Changes corresponding to making the kernel virtual memory pool
             region size configurable using configuration parameter 
             KERNEL_VIRT_POOL_REGION_SIZE.(V7COR-5102)
18mar16,md   add mapping of shadow interrupt table for VM direct interrupts
06sep15,l_z  fix capital issue in debug message. (V7PRO-2314)
03may15,pcs  Added call to adrSpaceDirectMapInit()
18apr14,elp  Fixed build warning.
12oct13,x_z  Fixed merge conflict.
25sep13,pcs  Moved arch specific code to a new file usrMmuArchInit.c
18jul13,x_z  add debug information.
04may11,syt  add support for PPC465.
01oct10,sem  Add new IA cpus. Remove pentium2/3
08sep10,pcs  Updated to pass the configuration parameter
             GLOBAL_VIRT_MEM_REGION_SIZE to adrSpaceLibInit.
20sep10,jpb  Replaced private header file, aimMmuLibP.h with extern because
             aimMmuLibP.h was causing a redefinition of a struct when 
             building images.
09sep10,jpb  Added header file for _func_aimMmuLockRegionsImport.
20aug10,x_z  add support for PPC476.
02jul10,zl   set page optimization flag for 64-bit
29jun10,slk  updates for parameter passing to mmuMipsLibInit
09mar10,pad  Removed settings of the RTP region for VxWorks 64-bit.
10feb10,zl   64-bit VxWorks require true MMU support
01nov09,pcs  Pass rtpRgnBase and rtpRgnSize to adrSpaceLibInit
             unconditionally, since the component INCLIDE_ADR_SPACE_LIB is
             included by default in a 64bit system.
26oct09,pcs  Updated to pass the RTP private region info to
             adrSpaceLibInit for LP64.
04sep09,zl   removed usage of sysPhysMemDesc[] for 64-bit.
31jul09,jb   Adding 64bit MMU support
24jun09,zl   updated address space initialization
30apr09,zl   removed unused vmBaseLibInit() argument
25aug08,jpb  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
23jun08,pad  Now pass the RTP_OVERLAPPED_ADDRESS_SPACE parameter to
             adrSpaceLibInit().
07may08,pad  Now passes RTP_CODE_REGION_SIZE and RTP_CODE_REGION_START
	     parameters to adrSpaceLibInit().
15oct07,zl   SMP kernel requires MMU support included.
21feb07,pes  Add support for new MIPS lib structure.
31mar06,pch  SPR 119828: SW_MMU_ENABLE must disable D-cache on PPC
19jan06,rec  change mmu548xLib to mmuV4eLib
28oct05,rec  add Coldfire MMU support
23aug05,rec  leave SW_MMU_ENABLE=FALSE for Coldfire
31oct05,zl   added INCLUDE_VM_INVTBL.
09aug05,zl   make global map support separate component. Fix warnings
             from #else (SPR#111044).
19aug05,md   fixed parameters being passed to ED&R macro
13jul05,h_k  added ifdef INCLUDE_EDR_STUB.
24feb05,pch  adjust PPC970 support
22apr04,to   PPC970 support
13dec04,h_k  renamed mmuSh77xxLibInit to mmuShLibInit.
22nov04,zl   test KERNEL_HEAP_SIZE parameter against sysMemTop().
16nov04,zl   fixed warning for mmuSoftLibInit() parameter
10nov04,dtr  SPR #103997.
10nov04,scm  remove osm init for i86 to comply with new API...
02nov04,to   SPR#102918 enable I&D MMU for PPC if adrSpaceLib is included.
28oct04,pes  Added conditional definition of SW_MMU_ENABLE for MIPS.
12oct04,kk   updated kernelBaseLib.h to private/kernelBaseLibP.h
12oct04,pcs  Replace vmBaseGlobalMapInit with vmGlobalMapInit.
03oct04,tam  commented out call to sysOSMTaskGateInit (PENTIUM Specific)
29sep04,tam  replaced EDR_KH by PROTECT_TASK_STACK
29sep04,pcs  Add 2 more parameters to mmuPpcLibInit.
20sep04,zl   avoid using printExc(); fixed MMU-less init without RTPs.
15sep04,zl   replaced adrSpaceLib.h with private version. Removed 
             obsolete sections.
10aug04,kk   renamed rtpBaseLib kernelBaseLib
08aug04,sru  Added call to _func_aimMmuLockRegionsImport.
19jul04,tam  moved vmContextUnionInit() to pgMgrLibInit()
02jun04,mem  remove arguments to MIPS MMU lib init.
09jun04,zl   replaced INCLUDE_MMU_FULL with INCLUDE_VM_RTP.
18may04,kk   replaced rtpIdSelf() with MY_CTX_ID()
29apr04,gls  added vmInvTblLibInit()
08apr04,zl   added software MMU simulation support.
05apr04,yp   reworking adrSpaceLibInit call
24feb04,jtp  SPR 92581 detect config error if RTP support enabled
             with I- or D-MMU disabled.
03dec03,jmp  added VxSim MMU header files.
18dec03,jtp  SPR 92700 guard against cache disabled cases
18dec03,jtp  SPR 92700 vmBaseLib must honor USER_D_CACHE_MODE
09dec03,jmt  Change call for MIPS MMU init
01dec03,yp   fixing compiler warning resulting from address type change
24nov03,zmm  Revome i86 specific vmArchLibInit calls.
19nov03,tam  added kernel ctx union initialization
17nov03,jtp  Add variable minimum page size to PPC405 & 440 MMU.
10nov03,jmt  Updated as part of MIPS AIM MMU rewrite
23oct03,tam  simplified call to adrSpaceLibInit()
17oct03,gls  added adrSpaceLibInit()
08oct03,tam  fixed dependencies between MMU_BASIC and MMU_FULL
30sep03,jmp  added support for VxSim.
19sep03,pcs  Change the paramer to vmBaseLib from pageSize to
             cacheDefault.
04sep03,pcs  Add support for MMU_FULL.
03sep03,jmt  Add MIPS R4k Library init
30jun03,tam  initialized vmShow with BASIC MMU support instead of FULL
07jan03,dtr  Adding support for static TLB entries for E500.
25nov02,dtr  Modify for E500.
02aug02,pcs  Add support for PPC85XX and make it the same as PPC603 for
             the present.
05jun02,hdn  added 36bit MMU support for P6 and P7
17apr02,jtp  support PPC440 MMU
27aug01,hdn  renamed mmuLibInit to mmuI86LibInit for PENTIUM2/3/4
14aug01,hdn  added PENTIUM2/3/4 support
26apr01,scm  remove xscale debug LED code...
20jan99,cdp  prevent MMU initialisation when ARM_HAS_NO_MMU defined;
	     removed support for old ARM libraries.
16nov98,cdp  added BSP selection of MMU for ARM. Added INCLUDE_MMU_MPU.
10nov00,s_m  PPC405 support
02mar00,zl   merged SH support into T2
24aug98,tpr  added PowerPC EC 603 support.
09apr98,hdn  added support for PentiumPro.
28nov96,cdp  added ARM support.
17jun96,tpr  added PowerPC 860 support.
19sep95,tpr  added PowerPC support.
06nov94,tmk  added MC68LC040 support.
16jun94,tpr  added MC68060 cpu support.
13nov93,hdn  added support for I80X86.
02dec93,pme  added Am29K family support.
30jul93,jwt  changed CPU to CPU_FAMILY for SPARC; include sun4.h to BSP.
27feb93,rdc  removed check for both BASIC and FULL (done in usrDepend.c).
13feb93,jcf  changed SPARC mmu initialization to utilize sysMmuLibInit.
16oct92,jwt  included sun4.h to pull in prototype for mmuSun4LibInit().
08oct92,rdc  ensured that both BASIC and FULL aren't set simultaneously.
29sep92,ccc  renamed mmu1eLibInit() to mmuSun4LibInit().
22sep92,rdc  cleanup, added support for sun1e.
18sep92,jcf  written.
*/

/*
DESCRIPTION
This file is used to initialize the memory management unit.  This file is
included by usrConfig.c.

SEE ALSO: usrExtra.c

NOMANUAL
*/

#ifndef  __INCusrMmuInitc
#define  __INCusrMmuInitc

#include <vsbConfig.h>
#include <private/kwriteLibP.h> /* _func_kprintf */
#include <cacheLib.h>   /* CACHE_DISABLED */

#define MMU_DEBUG_MSG(fmt, args...)                 \
    do                                              \
        {                                           \
        if (_func_kprintf != NULL)                  \
            _func_kprintf (fmt, ##args);            \
        } while (FALSE)
        
/* 
 * include the architecture portion of the memory management unit initialization
 * configlette. 
 */

#include <usrMmuArchInit.c>

#if (defined INCLUDE_ADR_SPACE_LIB)
#include <private/adrSpaceLibP.h>
#include <private/kernelBaseLibP.h>
#include <private/rtpLibP.h>
#endif

#if (defined INCLUDE_VM_INVTBL)
#include <private/vmInvTblLibP.h>
#endif

/* defines */

/*
 * arrange for default cache mode to track USER_D_CACHE_MODE if
 * cache is supported, enabled, and USER_D_CACHE_MODE exists.
 * Otherwise, the VM will leave cache disabled by default.
 */

#if (defined(INCLUDE_CACHE_SUPPORT) && defined(USER_D_CACHE_ENABLE) && \
     defined(USER_D_CACHE_MODE))
# define MMU_DEFAULT_CACHE_MODE		USER_D_CACHE_MODE
#else
# define MMU_DEFAULT_CACHE_MODE		CACHE_DISABLED
#endif

/* externals */

IMPORT PHYS_MEM_DESC * pAsMemDesc;
IMPORT int asMemDescNumEnt;
IMPORT char * memPoolEndAdrs;

IMPORT PHYS_MEM_DESC sysPhysMemDesc [];
IMPORT int sysPhysMemDescNumEnt;

#ifdef INCLUDE_ADR_SPACE_LIB
LOCAL ADR_SPACE_INIT_PARAMS asInitParam;
#endif

/*******************************************************************************
*
* usrMmuInit - initialize the memory management unit
*
* NOMANUAL
*/

void usrMmuInit (void)
    {
    UINT          err;
    UINT          ix;
    char *        pMsg;
    static char * pErrorMsg = 
		    "usrRoot: MMU configuration failed, errno = 0x00000000\n";
    static char   digits[] = "0123456789abcdef";
    
    MMU_DEBUG_MSG ("initialize MMU\r\n");

    /* call the architecture MMU library initialization function. */

    if (usrMmuArchInit() != OK)
	goto usrMmuPanic;

#ifdef INCLUDE_MMU_BASIC
    MMU_DEBUG_MSG ("initialize base virtual memory support\r\n");
    if (vmBaseLibInit() != OK)
	goto usrMmuPanic;
#endif

#ifdef INCLUDE_VM_RTP			/* VM support for RTPs */
    MMU_DEBUG_MSG ("initialize virtual memory support module\r\n");
    if (vmLibInit () != OK)
	goto usrMmuPanic;

#endif	/* INCLUDE_VM_RTP */

#ifdef INCLUDE_VM_INVTBL
    MMU_DEBUG_MSG ("initialize inverse translation library\r\n");
    if (vmInvTblLibInit() != OK)
	goto usrMmuPanic;
#endif

#ifdef	INCLUDE_ADR_SPACE_LIB

#ifdef _WRS_CONFIG_USE_MEMDESC
#ifndef _WRS_CONFIG_VXSIM
    /*
     * Validate the configuration parameter KERNEL_VIRT_POOL_REGION_SIZE
     * provided by the user. It should be less than or equal to the value 
     * that is fixed by the architecture (KERNEL_VIRT_POOL_RGN_SIZE).
     */

#if (KERNEL_VIRT_POOL_REGION_SIZE > KERNEL_VIRT_POOL_RGN_SIZE)
#error kernel virtual pool region size configuration parameter (KERNEL_VIRT_POOL_REGION_SIZE) should be  <= KERNEL_VIRT_POOL_RGN_SIZE
#endif

    asInitParam.kernelVirtPoolRgnSize  = KERNEL_VIRT_POOL_REGION_SIZE;
#else
    /*
     * for VXSIM architecture the kernel virtual memory pool region size is 
     * already configurable via VXSIM_KERNEL_VIRT_POOL_RGN_SIZE and is 
     * reflected in the macro KERNEL_VIRT_POOL_RGN_SIZE.
     */

    asInitParam.kernelVirtPoolRgnSize  = KERNEL_VIRT_POOL_RGN_SIZE;
#endif /* !VXSIM */

    asInitParam.localMemLocalAdrs  = LOCAL_MEM_LOCAL_ADRS;
#else /* _WRS_CONFIG_USE_MEMDESC */
    asInitParam.pPhysMemDesc       = sysPhysMemDesc;
    asInitParam.physMemDescNumEnt  = sysPhysMemDescNumEnt;
    asInitParam.localMemLocalAdrs  = LOCAL_MEM_LOCAL_ADRS;
    asInitParam.kernelMemTop       = (VIRT_ADDR) memPoolEndAdrs;
    asInitParam.globalVirtMemRgnSize = GLOBAL_VIRT_MEM_REGION_SIZE;
#ifdef INCLUDE_RTP
    asInitParam.rtpRgnBase         = RTP_CODE_REGION_START;
    asInitParam.rtpRgnSize         = RTP_CODE_REGION_SIZE;
    asInitParam.rtpRgnIsOverlapped = RTP_OVERLAPPED_ADDRESS_SPACE;
#else
    asInitParam.rtpRgnBase         = 0;
    asInitParam.rtpRgnSize         = 0;
    asInitParam.rtpRgnIsOverlapped = FALSE;
#endif /* RTP */
#endif /* _WRS_CONFIG_USE_MEMDESC */

    MMU_DEBUG_MSG ("initialize address space library\r\n");
    if (adrSpaceLibInit (&asInitParam) != OK)
	goto usrMmuPanic;

#ifdef _WRS_CONFIG_LP64

#ifdef INCLUDE_ADR_SPACE_DIRECT_MAP
    (void) adrSpaceDirectMapInit();
#endif

    /* 
     * For 64-bit VxWorks page optimization is enabled or disabled globally.
     * When enabled, all mappings performed in either kernel or RTP context
     * will be performed automatically with page optimization.
     */

#ifdef INCLUDE_PAGE_SIZE_OPTIMIZATION
    VM_PG_OPTIMIZE = TRUE;
#endif
    
#endif /* _WRS_CONFIG_LP64 */

    MMU_DEBUG_MSG ("initialize global mapping\r\n");
    if (vmGlobalMapInit (pAsMemDesc, asMemDescNumEnt, TRUE,
			 MMU_DEFAULT_CACHE_MODE) == NULL)
	goto usrMmuPanic;

#else  /* INCLUDE_ADR_SPACE_LIB */

    MMU_DEBUG_MSG ("initialize global mapping\r\n");
    if (vmGlobalMapInit (sysPhysMemDesc, sysPhysMemDescNumEnt, TRUE,
			 MMU_DEFAULT_CACHE_MODE) == NULL)
	goto usrMmuPanic;

#endif  /* INCLUDE_ADR_SPACE_LIB */

#ifdef INCLUDE_SHADOW_IDT

    /* map the shadow interrupt table for VM direct interrupt delivery */

    if (vmMap ((VM_CONTEXT_ID)NULL, (VIRT_ADDR)SHADOW_IDT_ADDRESS,
	       (PHYS_ADDR)SHADOW_IDT_ADDRESS,
	       ROUND_UP(SHADOW_IDT_SIZE, VM_PAGE_SIZE)) != OK)
	{
	goto usrMmuPanic;
	}

#endif /* INCLUDE_SHADOW_IDT */

#if defined (INCLUDE_SHOW_ROUTINES) || defined (INCLUDE_VM_SHOW)
    vmShowInit ();
#endif /* INCLUDE_SHOW_ROUTINES */

    return;

usrMmuPanic:

    /* save error message with errno in system exception msg area */

    pMsg = pErrorMsg + strlen (pErrorMsg) - 2;
    err  = errno;

    for (ix = 0; ix < 8; ix++)
	{
	*pMsg-- = digits[err & 0xf];
	err >>= 4;
	}

    pMsg = pErrorMsg;

    while ((*(sysExcMsg++) = *(pMsg++)) != EOS)
	;

    /* 
     * Use ED&R to inject an error. In case ED&R is not included or not yet 
     * initialized, the policy stub still will be called.
     */

    EDR_INIT_FATAL_INJECT (NULL, NULL, NULL, NULL, pErrorMsg);

    /* if EDR stub returned somehow... */

    reboot (BOOT_WARM_NO_AUTOBOOT);
    }

#endif	/* __INCusrMmuInitc */
