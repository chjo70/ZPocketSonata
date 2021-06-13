/* sysALib.s - Freescale T2/T4 board Assembly support file */

/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
30aug16,l_z  add synopsis content. (V7PRO-3289)
15aug16,emj  fix apigen synopsis tags
09jul15,l_z  add fast warm boot support. (F3387)
11nov14,syt  add LP64 support and changed the boot flag to BOOT_COLD. (US15027)
18mar15,d_l  pass BOOT_COLD to usrInit. (V7PRO-738)
10may14,ylu  added SMT (multi-threading) support to BSP for PPCE6500.
             (US34958)
10apr14,ylu  added support for SMP.(US34480)
28feb14,ylu  created.
*/

/*
DESCRIPTION
This module contains system-dependent routines written in assembly
language.  It contains the entry code, sysInit(), for VxWorks images
that start running from RAM, such as 'vxWorks'.  These images are
loaded into memory by some external program (e.g., a boot ROM) and then
started.  The routine sysInit() must come first in the text segment.
Its job is to perform the minimal setup needed to call the generic C
routine usrInit().
*/

#define _ASMLANGUAGE
#include <vxWorks.h>
#include <sysLib.h>
#include <vsbConfig.h>
#include <asm.h>
#include <arch/ppc/private/adrSpaceArchLibP.h>
#include <prjParams.h>

/* globals */

FUNC_IMPORT(vxCpuInit)
FUNC_IMPORT(vxMmuEarlyInit)
FUNC_IMPORT(usrInit)

#ifdef _WRS_CONFIG_SMP
FUNC_EXPORT(sysSecCpuInit)
#endif /* _WRS_CONFIG_SMP */

FUNC_EXPORT(sysInit)
FUNC_EXPORT(_sysInit)

    .data
#ifdef _WRS_CONFIG_STANDALONE_DTB
#define TO_STRING(exp)      #exp
#define DTS_ASM_FILE(file)  TO_STRING (file.s)
#include DTS_ASM_FILE (DTS_FILE)
#endif /* _WRS_CONFIG_STANDALONE_DTB */

#define KERNEL_ENTRY_OFFSET 	0x0

#ifndef _WRS_CONFIG_LP64
#define KERNEL_STACK_OFFSET 	0x4
#define KERNEL_LOOP_OFFSET     	0x8
#define PHYS_CPU_INDEX_OFFSET   0xc
#else
#define KERNEL_STACK_OFFSET 	0x8
#define KERNEL_LOOP_OFFSET     	0x10
#define PHYS_CPU_INDEX_OFFSET   0x18
#endif /* _WRS_CONFIG_LP64 */

    _WRS_TEXT_SEG_START

DATA_IMPORT (gpDtbInit)

#if   defined(_GNU_TOOL)
    .section .text.entry, "ax", @progbits
#elif defined(_DIAB_TOOL)
    .section .text.entry, 4, "rx"
#else
#error "Please add a correctly spelled .section directive for your toolchain."
#endif

/*******************************************************************************
*
* sysInit - start from boot loader
*
* This routine is the system start-up entry point for VxWorks in RAM, the first
* code executed after being loaded by boot loader.  It saves the arguments,
* initializes the primary CPU, configures the MMU for the initialoatin process,
* saves the DTB area, sets up the stack, and jumps to the C routine usrInit().
*
* By default, the initial register values of the primary CPU must be set as
* described in Chapter 5.4 of ePAPR v1.0.
*
*
* MSR:
*
*   PR=0 supervisor state
*   EE=0 interrupts disabled
*   ME=0 machine check interrupt disabled
*   IS=0,DS=0 address space 0
*
* r3:
*   Effective address of the device tree image. Note: This address shall be 8
*   bytes aligned in memory.
*
* r4, r5: 0
*
* r6:
*   0x45504150, ePAPR magic value used to distinguish from non-ePAPR-compliant
*   firmware
*
* r7:
*   shall be the size of IMA(Initial Mapped Area) in bytes
*
* r8, r9: 0
*
* TCR;
*   WRC=0, no watchdog timer reset will occur
*
* NOTE:
*   1. This routine should not be called by the user;
*   2. <pOf> is unused because bootng from Open Firmware is unsupported now;
*   3. The initial stack is placeed in .data section, and mapped with the entire
*   image vxWorks.
*
* If Embedded FDT mode is enabled, the legacy boot mode is used and the input
* arguments are ignored, and IMA size is from CDF.
*
* SYNOPSIS
* \ss
* VOID sysInit
*     (
*     void * pDtb,      /@ Effective address of the device tree image @/
*     UINT32 reserved1, /@ shall be 0 @/
*     UINT32 reserved2, /@ shall be 0 @/
*     UINT32 magic,     /@ magic number, should be 0x45504150 @/
*     size_t imaSize    /@ shall be the size of IMA @/
*     )
* \se
*
* RETURNS: N/A
*/

FUNC_LABEL(_sysInit)
FUNC_BEGIN(sysInit)
    li      r29, BOOT_CLEAR
    bl      cold

    li      r29, BOOT_NORMAL
cold:
#ifdef _WRS_CONFIG_STANDALONE_DTB
    /* save IMA size */

    lis     r31, HI(IMA_SIZE)
    ori     r31, r31, LO(IMA_SIZE)
#else /* !_WRS_CONFIG_STANDALONE_DTB */
    /* save DTB address and IMA size */

    mr      r30, r3
    mr      r31, r7
#endif /* _WRS_CONFIG_STANDALONE_DTB */

#ifdef INCLUDE_WARM_BOOT
    cmpwi   r29, BOOT_CLEAR
    bne     skipBackup

    bl      vxSdaInit
    /* get frame stack */

    LOADPTR(sp, RAM_LOW_ADRS)
    LOADPTR(r3, KERNEL_SYS_MEM_RGN_BASE)
    sub     sp, sp, r3
    addi    sp, sp, -FRAMEBASESZ

    bl      warmBootBackup
skipBackup:
#endif /* INCLUDE_WARM_BOOT */

    /* initialize CPU */

    bl      vxCpuInit

    /* obtain runtime address */

    bl      rtAddr
rtAddr:
    mflr    r3      /* runtime address */

    /* calculate offset from link address */

    LOADPTR(r4, LOCAL_MEM_LOCAL_ADRS)
    LOADPTR(r5, rtAddr)
    sub     r5, r5, r4

    /* calculate runtime address base */

    sub     r3, r3, r5

    /* adjust DTB address */

#ifndef _WRS_CONFIG_STANDALONE_DTB
    sub     r30, r30, r3    /* get offset */
    add     r30, r30, r4
#endif /* !_WRS_CONFIG_STANDALONE_DTB */

    /* initialize MMU early */

    mr      r5, r31
    bl      vxMmuEarlyInit

    /* save DTB address */

#ifdef _WRS_CONFIG_STANDALONE_DTB
    LOADPTR(r30, dt_blob_start)
#endif /* _WRS_CONFIG_STANDALONE_DTB */

    STOREVAR_LP(r30, r6, gpDtbInit)

    /* get frame stack */

    LOADPTR(sp, RAM_LOW_ADRS)
    addi    sp, sp, -FRAMEBASESZ

    /* jump to C routine */

    mr      r3, r29   /* resotre the boot type */
    b       usrInit
FUNC_END(sysInit)


#ifdef _WRS_CONFIG_SMP

/*******************************************************************************
*
* sysSecCpuInit - start from boot loader
*
* This routine is the start-up entry point for secondary CPU in RAM. For CPUs
* in an SMP configuration, one CPU shall be designated the boot CPU and
* initialized as described in Chapter 5.4 of ePAPR v1.0. A boot program passes
* control to a client program on the boot CPU only. At the time the client 
* program is started, all secondary CPUs shall be in a quiescent state.
* Secondary CPUs may be started using the spin table or implementation-specific
* mechanisms.
*
* The ePAPR defines a spin table mechanism for starting secondary CPUs. The boot
* program places all secondary CPUs into a loop where each CPU spins until the
* branch_address field in the spin table is updated specifying that the
* core is released.
*
* When a secondary CPU is released from its spin loop, its state shall be
* identical to the state of boot CPUs (see 5.4.1 of ePAPR v1.0, Boot CPU
* Initial Register State) except as noted here:
*
* R3 contains the value of the r3 field from the spin table
*  (only for the first thread of the CPU).
* R6 shall be 0.
* If the CPU has a programmable PIR register, the PIR shall contain the value
* of the pir field from the spin table.
* No I/O device mappings (see 5.4.3, Initial I/O Mappings (IIO)) are required.
* The Secondary IMA (SIMA) mapping (described in 5.3, Initial Mapped Areas) in 
* the MMU shall map effective address to the entry_addr field in the spin table, 
* aligned down to the SIMA size.
* R7 shall contain the size of the SIMA.
* The SIMA shall have a minimum size of 1MiB.
* Other mappings may be present in Address Space (AS) 0.
* No mappings shall be present in Address Space (AS) 1.
* The MMU mapping for the SIMA shall be such that the TLBs can accommodate a
* reasonable number of additional mappings.
* The SIMA mapping shall not be affected by any actions taken by any other CPU.
*
* To activate a secondary CPU, the client program (running on the boot cpu) may
* write the pir field value, may write the r3 value, may write the most 
* significant 32 bits of the entry_addr value, and shall write the least 
* significant 32 bits of the entry_addr value.
*
* SYNOPSIS
* \ss
* VOID sysSecCpuInit
*    (
*    void * pBootInfo, /@ SMP boot info @/
*    UINT32 reserved1, /@ unused @/
*    UINT32 reserved2, /@ unused @/
*    UINT32 reserved3, /@ shall be 0 @/
*    size_t imaSize	/@ shall be the size of IMA @/
*    )
* \se
*
* RETURNS: N/A
*/

FUNC_LABEL(_sysSecCpuInit)
FUNC_BEGIN(sysSecCpuInit)

    mr      r30, r3

    /* save IMA size */

#ifdef _WRS_CONFIG_STANDALONE_DTB
    lis     r31, HI(IMA_SIZE)
    ori     r31, r31, LO(IMA_SIZE)
#else /* !_WRS_CONFIG_STANDALONE_DTB */
    mr      r31, r7
#endif /* _WRS_CONFIG_STANDALONE_DTB */

    /* initialize CPU */

    bl      vxCpuInit

    /* fake a TLB1 entry#0 mapping */

    lis     r3, HI(_PPC_MAS0_TLBSEL(1) | _PPC_MAS0_ESEL(0))
    mtspr   MAS0, r3

    lis     r3, HI(_PPC_MAS1_V | _PPC_MAS1_IPROT)
    ori     r4, r3, _PPC_MAS1_TSIZE(19)
    mtspr   MAS1, r4

    li      r3, _PPC_MAS2_M
    mtspr   MAS2, r3

    li      r3, _PPC_MAS3_SX | _PPC_MAS3_SW | _PPC_MAS3_SR
    mtspr   MAS3, r3

    li      r3, 0
    mtspr   MAS7, r3

    tlbwe
    isync

    /* switch to TS 0 */

    mfmsr   r7
    rlwinm  r7, r7, 0, _PPC_MSR_BIT_DS + 1, _PPC_MSR_BIT_IS - 1
    mtmsr   r7
    isync

    /* obtain runtime address */

    bl      rtAddrSmp
rtAddrSmp:
    mflr    r3      /* runtime address */

    /* calculate offset from link address */

    LOADPTR(r4, LOCAL_MEM_LOCAL_ADRS)
    LOADPTR(r5, rtAddrSmp)
    sub     r5, r5, r4

    /* calculate runtime address base */

    sub     r3, r3, r5

    /* initialize MMU early */

    mr      r5, r31
    bl      vxMmuEarlyInit

    nop
    nop

    /* get frame stack */

    LDLP    sp, KERNEL_STACK_OFFSET(r30)	/* kernel stack start address */
    addi    sp, sp, -FRAMEBASESZ

    /* get the C function param of kernelCpuEntry */

    LDLP    r3, KERNEL_ENTRY_OFFSET(r30)	/* kernel function start address */

    /* get the C function param of physCpuIndex */

    LDLP    r4, PHYS_CPU_INDEX_OFFSET(r30)	/* core physical index */

    /* jump to C routine cpuE500SmpLoop */

    LDLP    r6, KERNEL_LOOP_OFFSET(r30)	/* core initialization call routine */

    mtctr   r6
    bctr

FUNC_END(sysSecCpuInit)
#endif /* _WRS_CONFIG_SMP */

