/* vxbClkLib.h - vxbus clock interfaces header file */

/*
 * Copyright (c) 2013-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04may16,m_w  optimize code logic. (F7158)
04mar16,pmr  add drvSpecLen field to vxb_clk_fdt struct (V7SP-920)
04nov15,yjw  add VXB_CLK_MULTIPILER (US64532)
09jul14,m_w  add VXB_CLK_DIVIDER,VXB_CLK_GATE,VXB_CLK_PLL.(V7PRO-1247)
11apr14,sye  updated to support dynamic clock rate.
27jun13,c_t  written.
*/

/*
DESCRIPTION

For modern SOCs, most included component has its input clock to drive
this component runing. This library intends to supply public interfaces 
to manage those clocks.
*/

#ifndef __INCvxbClkLibh
#define __INCvxbClkLibh

#include <vxWorks.h>
#include <hwif/vxBus.h>
#include <dllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VXB_CLOCK_SUPPORT_STATIC_DEFINE 1

#define DOMAIN_NAME_MAX                 (64)
#define CLOCK_NAME_MAX                  (64)

/* clock status */

#define CLOCK_STATUS_UNKNOWN            (0)
#define CLOCK_STATUS_ENABLED            (1)
#define CLOCK_STATUS_GATED              (2)

/* clock rate */

#define CLOCK_RATE_INVALID              (0)

struct vxb_clk_domain;
struct vxb_clk;
struct vxb_clk_fdt;

typedef enum vxb_clk_type
    {
    VXB_CLK_FIX_RATE    = 0,        /* rate is constant */
    VXB_CLK_FIX_FACTOR  = 1,        /* divider or mutiplier */
    VXB_CLK_MUX         = 2,        /* clock selector */
    VXB_CLK_PLL         = 3,        /* PLL clock, drive device */
    VXB_CLK_FAKE        = 4,        /* fake clock */
    VXB_CLK_DIVIDER     = 5,        /* divider */
    VXB_CLK_GATE        = 6,        /* gate */
    VXB_CLK_FLL         = 7,        /* Frequency Lock Loop */
    VXB_CLK_MULTIPLIER  = 8,        /* multiplier */
    } VXB_CLK_TYPE;

typedef struct vxb_clk_funcs
    {
    STATUS (*clkEnable)
        (
        struct vxb_clk * clk
        );

    STATUS (*clkDisable)
        (
        struct vxb_clk * clk
        );
    STATUS (*clkRateSet)
        (
        struct vxb_clk * clk,
        UINT64 rate
        );

    UINT64 (*clkRateGet)
        (
        struct vxb_clk * clk,
        UINT64 parentRate
        );

    UINT32 (*clkStatusGet)
        (
        struct vxb_clk * clk
        );

    STATUS (*clkParentSet)
        (
        struct vxb_clk * cclk,
        struct vxb_clk * pclk
        );

    STATUS (*clkInit)
        (
        struct vxb_clk * clk
        );

    STATUS (*clkExtCtrl)
        (
        struct vxb_clk * clk,
        UINT32           ctrl,
        void *           context
        );
    }VXB_CLK_FUNC;

typedef struct vxb_clk_domain_funcs
    {
    STATUS (*clkDomainEnable)
        (
        struct vxb_clk_domain * clkDomain
        );

    STATUS (*clkDomainDisable)
        (
        struct vxb_clk_domain * clkDomain
        );

    STATUS (*clkDomainInit)
        (
        struct vxb_clk_domain * clkDomain
        );

    STATUS (*clkDomainClkInit)
        (
        struct vxb_clk_domain * clkDomain,
        struct vxb_clk *        clk
        );

    STATUS (*clkDomainExtCtrl)
        (
        struct vxb_clk_domain * clkDomain,
        UINT32                  ctrl,
        void *                  context
        );
    }VXB_CLK_DOMAIN_FUNC;

/* 
 * this function accep 3 parameter:
 * void*    param,                      /@ param from FDT, exclude phandle. @/
 * int      paramNum,                   /@ param number, the clock-cells @/
 * struct   vxb_clk_fdt * clkData       /@ the whole fdt clk data @/
 */
 
typedef struct vxb_clk* (*funcClkGet) (void*, int, struct vxb_clk_fdt *);

typedef struct vxb_clk
    {
    DL_NODE                     clkNode;        /* connect point to domain list */
    DL_NODE                     rootClkNode;    /* connect point to clkInitList */

    char                      * clkName;
    UINT64                      clkRate;
    UINT32                      clkStatus;
    UINT32                      clkRefs;
    VXB_CLK_TYPE                clkType;        /* type of this clock */
    char                      * parentName;     /* parent info */
    char                     ** parentNames;    /* parent name array */
    struct vxb_clk            * parentClock;
    struct vxb_clk           ** parentClocks;
    UINT32                      parentNum;      /* parent number */
    UINT32                      parentIdx;      /* current parent's index */

    DL_NODE                     parentNode;     /* connect point to parent's child list */
    DL_LIST                     childClkList;
 
    struct vxb_clk_domain     * clkDomain;
    struct vxb_clk_funcs      * clkFuncs;
    void                      * clkContext;

    VXB_DEV_ID                  pDev;
    }VXB_CLK;

typedef struct vxb_clk * VXB_CLK_ID;

typedef struct vxb_clk_reg_data
    {
    VXB_DEV_ID          pDev;        /* clock controller pdev */
    char*               name;
    char*               domainName; 
    char*               parentName; 
    char**              parentsName; 
    UINT32              parentNum; 
    VXB_CLK_TYPE        clkType; 
    VXB_CLK_FUNC *      pFuncs; 
    funcClkGet          clkGet;
    void*               pClkData;
    int                 offset;      /* clock node offset */
    } VXB_CLK_REG;

/* use for static define clock */

#define DEFINE_VXB_CLOCK(name, rate, parent, clkdom, funcs, ctx)\
LOCAL struct vxb_clk name =                  \
    {                                        \
    {NULL, NULL},       /* nodeToDm */       \
    {NULL, NULL},       /* nodeToInit */     \
    #name,              /* clkName */        \
    rate,               /* clkRate */        \
    0,                  /* clkStatus */      \
    0,                  /* clkRefs */        \
    0,                  /* clkType */        \
    NULL,               /* parentName */     \
    NULL,               /* parentNames */    \
    parent,             /* parentClock */    \
    NULL,               /* parentClocks*/    \
    1,                  /* parentNum */      \
    0,                  /* parentIdx */      \
    {NULL, NULL},       /* nodeToParent */   \
    {NULL, NULL},       /* childClkList */   \
    clkdom,             /* clkDomain */      \
    funcs,              /* clkFuncs */       \
    (void *)ctx,        /* clkContext */     \
    NULL                /* pDev */           \
    };

typedef struct vxb_clk_domain
    {
    DL_NODE    domainNode;    /* clock domain node */
    char*      domainName;    /* clock domain name */
    DL_LIST    domainClkList; /* Contained Devices list of this domain */
    struct vxb_clk_domain_funcs * domainFuncs;
    void *                        domainContext;
    }VXB_CLK_DOMAIN;

typedef struct vxb_clk_domain_reg_data
    {
    char* name;
    VXB_CLK_DOMAIN_FUNC* pFuncs;
    void* pContext;
    } VXB_CLK_DOMAIN_REG;

#define DEFINE_VXB_CLOCK_DOMAIN(name, parent, pwrDom, funcs, ctx)\
LOCAL struct vxb_clk_domain name =          \
    {                                       \
    {NULL, NULL},                              \
    #name,         /* domainName */            \
    {NULL, NULL},  /* domainClkList */         \
    funcs,         /* domainFuncs */           \
    (void *)ctx    /* domainContext */         \
    };

typedef struct vxb_clk_fdt
    {
    DL_NODE    clkFdtNode;
    int        offset;          /* clock source FDT node offset */
    void*      pDrvSpec;        /* driver specific data */
    int        drvSpecLen;      /* driver specific data length */
    funcClkGet clkGet;          /* driver supplied clk get routine */
    } VXB_CLK_FDT;

VXB_CLK_ID vxbClkRegister (VXB_CLK_REG *);
VXB_CLK_DOMAIN* vxbClkDomainRegister (VXB_CLK_DOMAIN_REG *);
VXB_CLK_ID vxbClkGet (VXB_DEV_ID pDev, const char * pClkName);
STATUS   vxbClkEnable (VXB_CLK_ID pClk);
STATUS   vxbClkDisable (VXB_CLK_ID pClk);
UINT32   vxbClkStatusGet (VXB_CLK_ID pClk);
STATUS   vxbClkEnableAll (VXB_DEV_ID pDev);
STATUS   vxbClkDisableAll (VXB_DEV_ID pDev);
STATUS   vxbClkRateSet (VXB_CLK_ID pClk, UINT64 rate);
UINT64   vxbClkRateGet (VXB_CLK_ID pClk);
STATUS   vxbClkParentSet (VXB_CLK_ID pChildClk, VXB_CLK_ID pParentClk);

#ifdef VXB_CLOCK_SUPPORT_STATIC_DEFINE
STATUS   vxbClksInit(VXB_DEV_ID, VXB_CLK **, funcClkGet);
STATUS   vxbClkDomainInit(VXB_CLK_DOMAIN **);
STATUS   vxbClkStaticDataSet (VXB_CLK ** ppClk, VXB_CLK_DOMAIN ** ppDomain);
STATUS   vxbClkStaticDataGet (VXB_CLK *** pppClk, VXB_CLK_DOMAIN *** pppDomain);
#endif /* VXB_CLOCK_SUPPORT_STATIC_DEFINE */

#ifdef __cplusplus
    }
#endif
    
#endif /* __INCvxbClkLibh */

