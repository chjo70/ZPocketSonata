/* vxbFslQoriqLaw.h - Freescale Qoriq LAW resource management driver header */

/*
 * Copyright (c) 2013, 2017-2018 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------
01feb18,lyx  fixed incorrect output from lawShow() when a window is 4GB
             or larger.(V7PRO-4084)
05jul17,syt  add macros CORENET_LAW_TGT_ID_SHIFT, CORENET_LAW_BASE_HIGH_SHIFT.
22may14,fao  add islawInit.(US34958)
14feb14,syt  updated the driver to support DDR Interleaved.(V7PRO-742)
12mat14,syt  add a macro CORENET_DDR_ITLV_ID. (US35016)
12aug13,syt  created
*/

#ifndef __INCvxbFslQoriqLawh
#define __INCvxbFslQoriqLawh

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#ifndef UINT64
#   define UINT64 unsigned long long
#endif /* UINT64 */

/* defines */

#define ECM_DDR_ID                  0x0f    /* DDR controller target ID of ECM LAWs */
#define ECM_ELBC_ID                 0x04    /* eLBC controller target ID of ECM LAWs */
#define ECM_LAW_DEFAULT_NUM         12      /* ECM LAW number */

#define CORENET_DDR0_ID             0x10    /* DDR controller 0 target ID of ECM LAWs */
#define CORENET_DDR1_ID             0x11    /* DDR controller 1 target ID of ECM LAWs */
#define CORENET_DDR2_ID             0x12    /* DDR controller 2 target ID of ECM LAWs */
#define CORENET_DDR_12_ITLV_ID      0x14    /* DDR Interleaved Memory Complex 1-2 ID */
#define CORENET_DDR_13_ITLV_ID      0x17    /* DDR Interleaved Memory Complex 1-3 ID */
#define CORENET_ELBC_ID             0x1f    /* eLBC controller target ID of CORENET LAWs */
#define CORENET_LAW_DEFAULT_NUM     32      /* CoreNet LAW number */

#define CORENET_LAW_TGTID_SHIFT     20
#define CORENET_LAW_BASE_HIGH_SHIFT 24
#define CORENET_LAW_BASE_LOW_SHIFT  12

/* minimum LAW size is 4 Kbytes, so 12 lowest bits can't be specified */

#define QORIQ_LAWBAR_VAL(adrs)  ((adrs) >> 12)

#define GET_CS_SIZE(size)       (UINT64)(2ULL << size)

/* CoreNet LAW BAR register access derfines */

#define CORENET_LAW_BARHI_WRITE(n, value)   \
            vxbWrite32(pDrvCtrl->lawHandle, (UINT32 *)((char *)pDrvCtrl->lawBar+0xc00+0x10*n), value)
#define CORENET_LAW_BARLO_WRITE(n, value)   \
            vxbWrite32(pDrvCtrl->lawHandle, (UINT32 *)((char *)pDrvCtrl->lawBar+0xc04+0x10*n), value)
#define CORENET_LAW_AR_WRITE(n, value)      \
            vxbWrite32(pDrvCtrl->lawHandle, (UINT32 *)((char *)pDrvCtrl->lawBar+0xc08+0x10*n), value)
#define CORENET_LAW_BARHI_READ(n)   \
            vxbRead32(pDrvCtrl->lawHandle, (UINT32 *)((char *)pDrvCtrl->lawBar+0xc00+0x10*n))
#define CORENET_LAW_BARLO_READ(n)   \
            vxbRead32(pDrvCtrl->lawHandle, (UINT32 *)((char *)pDrvCtrl->lawBar+0xc04+0x10*n))
#define CORENET_LAW_AR_READ(n)      \
            vxbRead32(pDrvCtrl->lawHandle, (UINT32 *)((char *)pDrvCtrl->lawBar+0xc08+0x10*n))

/* ECM LAW BAR register access derfines */

#define ECM_LAW_BAR_WRITE(n, value) \
            vxbWrite32(pDrvCtrl->lawHandle, (UINT32 *)((char *)pDrvCtrl->lawBar+0xc08+0x20*n), value)
#define ECM_LAW_AR_WRITE(n, value)  \
            vxbWrite32(pDrvCtrl->lawHandle, (UINT32 *)((char *)pDrvCtrl->lawBar+0xc10+0x20*n), value)
#define ECM_LAW_BAR_READ(n)         \
            vxbRead32(pDrvCtrl->lawHandle, (UINT32 *)((char *)pDrvCtrl->lawBar+0xc08+0x20*n))
#define ECM_LAW_AR_READ(n)          \
            vxbRead32(pDrvCtrl->lawHandle, (UINT32 *)((char *)pDrvCtrl->lawBar+0xc10+0x20*n))

/* type defines */

/* 
 * The Local access window attribute setting, these parameters
 * should be provided in DTS node.
 */

typedef struct lawAttr
    {
    UINT32  trgtId;
    UINT32  csdId;
    UINT64  lawBase;
    UINT64  lawSize;
    } _WRS_PACK_ALIGN(4) LAW_ATTR;

/* ECM LAWn base address register low format */

typedef union
    {
    UINT32 regVal;
    struct                      /* Bit field description */
        {
        UINT32  :8;             /* Reserved field */
        UINT32  baseAddr:24;    /* BASE_ADDR_LOW */
        } field;
    } ECM_LAWBAR;

/* ECM LAWn attribute register format */

typedef union
    {
    UINT32 regVal;
    struct                      /* Bit field description */
        {
        UINT32  en:1;           /* Enable */
        UINT32  :6;             /* Reserved field */
        UINT32  trgetId:5;      /* Target identifier */
        UINT32  :14;            /* Reserved field */           
        UINT32  size:6;         /* Size of the window */
        } field;
    } ECM_LAWAR;

/* Corenet LAWn base address register high format */

typedef union
    {
    UINT32 regVal;
    struct                      /* Bit field description */
        {
        UINT32  :24;            /* Reserved field */
        UINT32  baseAddrHi:8;   /* BASE_ADDR_HI */
        } field;
    } CORENET_LAWBAR_H;

/* Corenet LAWn base address register low format */

typedef union
    {
    UINT32 regVal;
    struct                      /* Bit field description */
        {
        UINT32  baseAddrLow:20; /* BASE_ADDR_LOW */
        UINT32  :12;            /* Reserved field */
        } field;
    } CORENET_LAWBAR_L;

/* Corenet LAWn attribute register format */

typedef union
    {
    UINT32 regVal;
    struct                      /* Bit field description */
        {
        UINT32  en:1;           /* Enable */
        UINT32  :3;             /* Reserved field */             
        UINT32  trgetId:8;      /* Target identifier */
        UINT32  csdId:8;        /* Coherency subdomain identifier */
        UINT32  :6;             /* Reserved field */
        UINT32  size:6;         /* Size of the window */
        } field;
    } CORENET_LAWAR;


BOOL  islawInit ();

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* __INCvxbFslQoriqLawh */
