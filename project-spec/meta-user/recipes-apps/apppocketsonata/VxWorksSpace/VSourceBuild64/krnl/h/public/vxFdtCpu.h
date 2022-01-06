/* vxFdtCpu.h -  VxWorks FDT EPAPR CPU library defines */

/*
 * Copyright (c) 2013-2015,2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
28nov11,syt  Enable EPAPR_SPIN_TABLE define for UP.(V7PRO-4121) 
02mar15,l_z  Add vxFdtCpuAvail. (V7PRO-770)
10may14,ylu  moved SMP_BOARD_INFO to smpPpcP.h.(US34958)
29apr14,ylu  fixed SMP task schedule issue.(V7PRO-743)
21apr14,ylu  added support for PPC E6500 SMP.(US34480)
19dec13,ylu  added support for PPC E500V2 SMP.
06aug13,x_z  Created.
*/

#ifndef __INCvxFdtCpuLibh
#define __INCvxFdtCpuLibh

#ifdef __cplusplus
extern "C" {
#endif

/* includes */

#ifndef _ASMLANGUAGE

#include <vxFdtLib.h>

/* CPU node structure */

#define FDT_CPU_NODE_NUM    32

#if (CPU_FAMILY==PPC)
typedef struct fdtCpuTlbInfo
    {
    BOOL            bTlbSplit; /* TLB has a split configuration */
    UINT32          uTlbSize;  /* number of entries in TLB */
    UINT32          uTlbsets;  /* number of associativity sets in the TLB */
    UINT32          uDTlbSize; /* number of entries in data TLB */
    UINT32          uDTlbSet;  /* number of associativity sets in data TLB */
    UINT32          uITlbSize; /* number of entries in instruction TLB */
    UINT32          uITlbSet;  /* number of associativity sets in instruction */
                               /* TLB */
    } FDT_CPU_TLB_INFO;

typedef struct fdtCpuCacheInfo
    {
    BOOL            bCacheUnified;   /* cache has a unified organization */
    UINT32          uCacheSize;      /* size in bytes of a unified cache */
    UINT32          uCacheSets;      /* number of associativity sets in a */
                                     /* unified cache */
    UINT32          uCacheBlkSize;   /* lock size in bytes of a unified cache */
    UINT32          uCacheLineSize;  /* line size in bytes of a unified cache */
    UINT32          uICacheSize;     /* size in bytes of the instruction */
                                     /* cache */
    UINT32          uICacheSets;     /* number of associativity sets in */
                                     /* instruction cache */
    UINT32          uICacheBlkSize;  /* block size in bytes of instruction */
                                     /* cache */
    UINT32          uICacheLineSize; /* line size in bytes of instruction */
                                     /* cache */
    UINT32          uDCacheSize;     /* size in bytes of data cache */
    UINT32          uDCacheSets;     /* number of associativity sets in data */
                                     /* cache */
    UINT32          uDCacheBlkSize;  /* block size in bytes of data cache */
    UINT32          uDCacheLineSize; /* line size in bytes of data cache */
    UINT32          uNextLvlCache;   /* <next-level-cache>, phandle type */
    } FDT_CPU_CACHE_INFO;

typedef struct fdtCpuNode
    {
    /*
     * <reg> desribes the CPU/threads represented by the CPU node:
     *
     * 1. If a CPU supports more than one thread (i.e. multiple streams of
     * execution) the reg property is an array with 1 element per thread. The
     * <#address-cells> on the /cpus node specifies how many cells each element
     * of the array takes. Software can determine the number of threads by
     * dividing the size of reg by the parent node's <#address-cells>.
     *
     * 2. If a CPU/thread can be the target of an external interrupt the "reg"
     * property value must be a unique CPU/thread id that is addressable by the
     * interrupt controller.
     *
     * 3. If a CPU/thread cannot be the target of an external interrupt, then
     * "reg" must be unique and out of bounds of the range addressed by the
     * interrupt controller
     *
     * If a CPU/thread's PIR is modifiable, Kernel should modify PIR to match
     * the "reg" property value. If PIR cannot be modified and the PIR value is
     * distinct from the interrupt controller numberspace, the CPUs binding may
     * define a binding-specific representation of PIR values if desired.
     */

    UINT32 *        pReg;
    UINT32          uRegLen;

    UINT32          uClkFreq;        /* clock speed of CPU in Hertz */
    UINT32          uTimeBaseFreq;   /* timebase and decrementer frequency */
                                     /* in Hertz */
    UINT32          uCacheOpBlkSize; /* block size in bytes upon which cache */
                                     /* block instructions operate */
    UINT32          uResvGranSize;   /* reservation granule size supported by */
                                     /* this processor in bytes */

    char *          status;          /* status of a CPU (SMP only) */

    /*
     * method by which a CPU in a disabled state is enabled, that should be
     * "spin-table" or "[vendor],[method]", such as "fsl,MPC8572DS"  If
     * "spin-table" method is used, the spin table address is required.
     */

    char *              enableMethod; /* enable method list */
    ULONG               uReleaseAddr; /* spin table address */

    /*
     * <power-isa-version> is a string that specifies the numerical portion of
     * the Power ISA version string. For example, for an implementation
     * complying with Power ISA Version 2.06, the value of this property would
     * be "2.06".
     */

    char *              pPowerIsaVer;

    FDT_CPU_TLB_INFO    tlbInfo;
    FDT_CPU_CACHE_INFO  cacheInfo;
    } FDT_CPU_NODE;

/*
 * A disabled CPU is in a state where it cannot interfere with the normal
 * operation of other CPUs, nor can its state be affected by the normal
 * operation of other running CPUs, except by an explicit method for enabling or
 * reenabling the quiescent CPU (see the enable-method property).
 *
 * In particular, a running CPU shall be able to issue broadcast TLB invalidates
 * without affecting a quiescent CPU, such as, it could be in a spin loop, held
 * in reset, and electrically isolated from the system bus or in another
 * implementation dependent state.
 */

#define FDT_CPU_STATE_OK        "okay"
#define FDT_CPU_STATE_DISABLE   "disabled"

#define FDT_CPU_ENA_METHOD      "spin-table"
#else /* !PPC */
typedef struct fdtCpuNode
    {
    /*
     * <compatible> is one string list to define programming model of device,
     * such as "fsl, ns16550", "ns16550". Note that the first string of
     * <compatible> is for the most matched driver;
     */

    char *              pCompat;
    UINT32              uCompatLen;

    /* <reg> desribes the CPU represented by the CPU node */

    UINT32              uReg;

    UINT32              uNextLvlCache;   /* <next-level-cache>, phandle type */
    } FDT_CPU_NODE;
#endif /* PPC */

typedef struct fdtCpuInfo
    {
    FDT_CPU_NODE cpuNode[FDT_CPU_NODE_NUM];
    } FDT_CPU_INFO;

/* FDT CPU information obtain routine */

IMPORT STATUS vxFdtCpuInfoGet
    (
    FDT_CPU_INFO *  pFdtCpuInfo
    );

/* Get available CPU number */

IMPORT UINT32 vxFdtCpuAvail ();

/* ePAPR defines spin table */

/* The spin table fields are defined as follows:
 * addr: specifies the physical address of the client entry point for
 * the spin table code to branch to. The boot program's spin loop must wait
 * until the least significant bit of entry_addr is zero.
 * r3: contains the value to put in the r3 register at secondary cpu entry.
 * The high 32-bits are ignored on 32-bit chip implementations. 64-bit chip
 * implementations however shall load all 64-bits.
 * pir: contains a value to load into the PIR (processor identification)
 * register for those CPUs with writable PIR.
 */

typedef struct ePaprSpinTable {
    UINT64 addr;
    UINT64 r3;
    UINT32 reserved;
    UINT32 pir;
    UINT8  pad[8];  /* pad the spin table 32 bytes alignment */
} EPAPR_SPIN_TABLE;

#endif /* !_ASMLANGUAGE */

#define FDT_SPIN_TABLE_OFFSET 5
#define FDT_ENTRY_ADDR_UPPER  0
#define FDT_ENTRY_ADDR_LOWER  4
#define FDT_ENTRY_R3_UPPER    8
#define FDT_ENTRY_R3_LOWER    12
#define FDT_ENTRY_RESV  16
#define FDT_ENTRY_PIR   20
#define FDT_ENTRY_SIZE  32
#define RELEASE_ADDR_MAPSIZE   0x1000

#ifdef __cplusplus
}
#endif

#endif /* __INCvxFdtCpuLibh */


