/* fslQoriq.h - Freescale QORIQ processor header */

/*
 * Copyright (c) 2013-2018 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
19jan18,lyx  fix ctrl+x can not reset board for t1024(F4843)
28dec17,lyx  supported new version of dpaa for t1024(F4843)
12aug16,fao  add more SVR ID define (V7PRO-3013)
28jul16,ply  enable the PAMU bypass after secure boot (F7369)
18may16,d_l  add BSTAR_TGTIF_INTERLEAVEDSDRAM. (V7PRO-3041)
19dec15,hcl  access unmapped register error. (V7PRO-2462)
18dec15,xms  add BSTAR related bits definition (V7PRO-1314)
25jan15,fao  add QORIQ_BSTAR_OFFSET (US: 53064)
15jan15,fao  add QORIQ_GURDEVDISR2_OFFSET (US: 48637)
11nov14,syt  added LP64 support. (US15027)
15sep14,l_z  correct the PSL abbreviation. (V7PRO-1243)
14jul14,ylu  added the inline function cpuMask. (US40503)
15may14,l_z  fix typo. (V7PRO-793)
14may14,x_z  added SVR bit defines. (US35954)
22apr14,syt  removed qoriqUsDelay() and added
             qoriqSysClkFreqFix() (US34957).
21apr14,ylu  added support for PPC E6500 SMP.(US34480)
22feb14,x_z  removed qoriqVirtTop(). (VXW7-1838)
19feb14,ylu  added global utilities and mpic register definitions.
13jan14,x_z  exported qoriqCpuEnable() and qoriqCpuAvailGet().
13aug13,x_z  reanmed.
12jul13,x_z  cleaned.
26jun13,l_z  created.
*/

#ifndef __INCfslQoriqh
#define __INCfslQoriqh

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#include <vmLib.h>
#include <boardLib.h>
#include <hwif/vxBus.h>

/* CPLD register base adress on IFC */

#define CONFIG_SYS_CPLD_BASE        0xffdf0000
#define CONFIG_SYS_CPLD_BASE_PHYS   (0xf00000000ull | CONFIG_SYS_CPLD_BASE)

/* CPLD register offset */

#define QORIQ_CPLD_RST_CTL1__OFFSET 0x10

/* CPLD register mask value */

#define QORIQ_CPLD_LBMAP_RESET    0xFF

/* SVR bit defines */

#define QORIQ_SVR_ID(svr)   (((svr) >> 8) & 0xFFF7FF)   /* ID          */
#define QORIQ_SVR_SEC(svr)  (svr & 0x80000)             /* with/without SEC */
#define QORIQ_SVR_MAJ(svr)  (((svr) >> 4) & 0xF)        /* major revision   */
#define QORIQ_SVR_MIN(svr)  ((svr) & 0xF)               /* minor revision   */

#define QORIQ_SVR_ID_T2080  0x853000
#define QORIQ_SVR_ID_T2081  0x853100
#define QORIQ_SVR_ID_T4240  0x824000

#define QORIQ_SVR_ID_T1040  0x852000
#define QORIQ_SVR_ID_T1041  0x852001
#define QORIQ_SVR_ID_T1042  0x852002

#define QORIQ_SVR_ID_T1024  0x854000

#define QORIQ_SVR_ID_P4080  0x820000

/* register defines for debug console */

#define QORIQ_DBGCON_THR        	 0x00    /* transmit holding register        */
#define QORIQ_DBGCON_LSR        	  0x05    /* line status register             */
#define QORIQ_DBGCON_LSR_THRE   0x20    /* transmit holding register empty  */

/* register defines for Qoriq Global Utilities */

#define QORIQ_GURDEVDISR_OFFSET        0x70
#define QORIQ_GURDEVDISR2_OFFSET       0x74
#define QORIQ_DEVDISR_TB0              0x00004000
#define QORIQ_DEVDISR_TB1              0x00001000
#define QORIQ_GUR_BRR_OFFSET           0xe4

#define QORIQ_DEVCFG_PAMUBYPENR_OFFSET    0x604    /*Enable PAMU bypass*/

/* register defines for Qoriq MPIC */

#define QORIQ_MPICPIR_OFFSET           0x1090
#define QORIQ_MPICWHO_OFFSET           0x90
#define QORIQ_MPICPIR_HRST_CORE0       0x00000001
#define QORIQ_MPICPIR_HRST_CORE1       0x00000002

/* coherency module memory offset */

#define QORIQ_ECM_OFFSET 0x1000
#define QORIQ_ECM_EEBPCR_OFFSET 0x10

/* run and control management module memory offset */

#define QORIQ_RCPM_OFFSET 0xe2000

/* for p3p4p5 series processor */

#define QORIQ_CTBENRL_OFFSET 0x084

/* for t1/t2t4 series processor*/

#define QORIQ_PCTBENR_OFFSET 0x1A0

/* Boot page translation register offset */

#define QORIQ_BPTR_OFFSET  0x20
#define QORIQ_BSTRL_OFFSET 0x24
#define QORIQ_BSTAR_OFFSET 0x28

#define BSTAR_EN                        0x80000000
#define BSTAR_4KB                       0x0000000b
#define BSTAR_TGTIF_DDRSDRAM            0x01000000
#define BSTAR_TGTIF_INTERLEAVEDSDRAM    0x01700000

/* board descriptor flag defines */

#define QORIQ_BOARD_DESC_FLAG_CORENET   0x0001  /* freescale CORENET soc */

#define QORIQ_PAMUBYPENR_ENABLE_ALL           0xffff0000 

/* IO access methods */

#define QORIQ_IO_RD8(addr)                 \
    vxbRead8 ((void *) VXB_HANDLE_ORDERED, (UINT8 *) (addr))

#define QORIQ_IO_WR8(addr, val)            \
    vxbWrite8 ((void *) VXB_HANDLE_ORDERED, (UINT8 *) (addr), (val))

#define QORIQ_IO_RD16(addr)                  \
    vxbRead16 ((void *) VXB_HANDLE_ORDERED, (UINT16 *) (addr))

#define QORIQ_IO_WR16(addr, val)            \
    vxbWrite16 ((void *) VXB_HANDLE_ORDERED, (UINT16 *) (addr), (val))

#define QORIQ_IO_SWAP_RD16(addr)            \
    vxbRead16 ((void *) VXB_HANDLE_SWAP (VXB_HANDLE_ORDERED ), (UINT16 *) (addr))

#define QORIQ_IO_SWAP_WR16(addr, val)       \
    vxbWrite16 ((void *) VXB_HANDLE_SWAP (VXB_HANDLE_ORDERED ), \
                (UINT16 *) (addr), (val))

#define QORIQ_IO_RD32(addr)                 \
    vxbRead32 ((void *) VXB_HANDLE_ORDERED, (UINT32 *) (addr))

#define QORIQ_IO_WR32(addr, val)            \
    vxbWrite32 ((void *) VXB_HANDLE_ORDERED, (UINT32 *) (addr), (val))

#define QORIQ_IO_RD64(addr)                 \
    vxbRead64 ((void *) VXB_HANDLE_ORDERED, (UINT64 *) (addr))

#define QORIQ_IO_WR64(addr, val)            \
    vxbWrite64 ((void *) VXB_HANDLE_ORDERED, (UINT64 *) (addr), (val))

#define QORIQ_IO_SWAP_RD32(addr)            \
    vxbRead32 ((void *) VXB_HANDLE_SWAP (VXB_HANDLE_ORDERED), (UINT32 *) (addr))

#define QORIQ_IO_SWAP_WR32(addr, val)       \
    vxbWrite32 ((void *) VXB_HANDLE_SWAP (VXB_HANDLE_ORDERED),  \
                (UINT32 *) (addr), (val))

/* board function default table */

BOARD_FUNC_TBL qoriqFuncTbl;

/* board function routines */

BOOL    qoriqProbe (char * compat);

/* qoriqPorbe() is a typo, obsolete it. The below define used for compatibility */

#define qoriqPorbe qoriqProbe

void    qoriqEarlyInit ();
void    qoriqInit (void);
void    qoriqReset (int startType);
char *  qoriqModel (void);
#ifdef _WRS_CONFIG_SMP
#ifdef _WRS_CONFIG_STANDALONE_DTB
/*******************************************************************************
*
* cpuMask - the CPU mask function.
*
* This routine returns the CPU num which is activated by the primary physical CPU.
*
* RETURNS: the physical CPU num.
*
* ERRNO: N/A
*
* NOMANUAL
*/
_WRS_INLINE UINT32 cpuMask
    (
    int cpu,
    UINT mask
    )
    {
    for (cpu++; !((1 << cpu) & mask); cpu++)
        ;
    return cpu;
    }
#endif /* _WRS_CONFIG_STANDALONE_DTB */

STATUS  qoriqCpuEnable (unsigned int physCpuIndex, /* physical cpu index */
                        WIND_CPU_STATE  * pCpuState);
UINT32  qoriqCpuAvailGet (void);
STATUS  qoriqCpuDisable (void);
#endif /* _WRS_CONFIG_SMP */

STATUS  qoriqDebug (char * pBuffer, size_t len);
void    qoriqEarlyDebugInit ();
void    qoriqDebugInit ();
int     qoriqPhysMemInfoGet
    (
    PHYS_MEM_DESC * pPhysMemDesc,
    int             physMemDescNum
    );

/* utility routines */

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* __INCfslQoriqh */
