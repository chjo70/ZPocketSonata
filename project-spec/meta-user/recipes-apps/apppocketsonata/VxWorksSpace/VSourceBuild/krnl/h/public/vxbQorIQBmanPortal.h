/* vxbQorIQBmanPortal.h - header file for QorIQ Buffer Manager portal driver */

/*
 * Copyright (c) 2009-2010, 2012-2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
DESCRIPTION

This file contains register definitions for the Freescale QorIQ
Buffer Manager portal interface. There are 10 software accessible
portals, mappted within a 2MB local access window (LAW). 
*/

/*
modification history
--------------------
02may17,wch  added support for ARM (F8333)
28dec14,fao  adopt PPC64 (US48435)
12mar14,fao  corrected the modify history
25jan13,wap  Apply updates from review
13aug12,wap  Update Bman for T4240
22feb10,wap  Add APIs to allow allocating/releasing multiple buffers at
             once
27jan10,wap  Add missing bportalSafeAlloc() and bportalSafeFree() function
             prototypes
17nov09,wap  Adapt API to handle 36-bit addressing
03nov09,wap  API mutual exclusion fixes, cleanups
16oct09,wap  Add local API for SMP use
13sep09,wap  Keep track of RCR produder/consumer indices
27aug09,wap  Add bportalCountGet() routine
07dec09,wap  written
*/

#ifndef __INCvxbQorIQBmanPortalh
#define __INCvxbQorIQBmanPortalh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The CoreNet portal space is mapped within a local access window
 * that's 2 MB in size. That window is in turn divided into two 1MB
 * sections. The first 1MB is cache-enabled, and contains the main
 * portal command and response queues. The second half is
 * cache-inhibited, and contains the producer/consimer index,
 * configuration and interrupt registers.
 */

/* Cache enabled area */

/* There are a total of 10 software portals (and 4 direct connect portals) */

#define BPORTAL_CE_0            0x00000000
#define BPORTAL_CE_1            0x00004000
#define BPORTAL_CE_2            0x00008000
#define BPORTAL_CE_3            0x0000C000
#define BPORTAL_CE_4            0x00010000
#define BPORTAL_CE_5            0x00014000
#define BPORTAL_CE_6            0x00018000
#define BPORTAL_CE_7            0x0001C000
#define BPORTAL_CE_8            0x00020000
#define BPORTAL_CE_9            0x00024000

/* Revision 2 of the Bman has 50 portals */

#define BPORTAL_V2CE_0          BPORTAL_CE_0
#define BPORTAL_V2CE_1          BPORTAL_CE_1
#define BPORTAL_V2CE_2          BPORTAL_CE_2
#define BPORTAL_V2CE_3          BPORTAL_CE_3
#define BPORTAL_V2CE_4          BPORTAL_CE_4
#define BPORTAL_V2CE_5          BPORTAL_CE_5
#define BPORTAL_V2CE_6          BPORTAL_CE_6
#define BPORTAL_V2CE_7          BPORTAL_CE_7
#define BPORTAL_V2CE_8          BPORTAL_CE_8
#define BPORTAL_V2CE_9          BPORTAL_CE_9
#define BPORTAL_V2CE_10         0x00028000
#define BPORTAL_V2CE_11         0x0002C000
#define BPORTAL_V2CE_12         0x00030000
#define BPORTAL_V2CE_13         0x00034000
#define BPORTAL_V2CE_14         0x00038000
#define BPORTAL_V2CE_15         0x0003C000
#define BPORTAL_V2CE_16         0x00040000
#define BPORTAL_V2CE_17         0x00044000
#define BPORTAL_V2CE_18         0x00048000
#define BPORTAL_V2CE_19         0x0004C000
#define BPORTAL_V2CE_20         0x00050000
#define BPORTAL_V2CE_21         0x00054000
#define BPORTAL_V2CE_22         0x00058000
#define BPORTAL_V2CE_23         0x0005C000
#define BPORTAL_V2CE_24         0x00060000
#define BPORTAL_V2CE_25         0x00064000
#define BPORTAL_V2CE_26         0x00068000
#define BPORTAL_V2CE_27         0x0006C000
#define BPORTAL_V2CE_28         0x00070000
#define BPORTAL_V2CE_29         0x00074000
#define BPORTAL_V2CE_30         0x00078000
#define BPORTAL_V2CE_31         0x0007C000
#define BPORTAL_V2CE_32         0x00080000
#define BPORTAL_V2CE_33         0x00084000
#define BPORTAL_V2CE_34         0x00088000
#define BPORTAL_V2CE_35         0x0008C000
#define BPORTAL_V2CE_36         0x00090000
#define BPORTAL_V2CE_37         0x00094000
#define BPORTAL_V2CE_38         0x00098000
#define BPORTAL_V2CE_39         0x0009C000
#define BPORTAL_V2CE_40         0x000A0000
#define BPORTAL_V2CE_41         0x000A4000
#define BPORTAL_V2CE_42         0x000A8000
#define BPORTAL_V2CE_43         0x000AC000
#define BPORTAL_V2CE_44         0x000B0000
#define BPORTAL_V2CE_45         0x000B4000
#define BPORTAL_V2CE_46         0x000B8000
#define BPORTAL_V2CE_47         0x000BC000
#define BPORTAL_V2CE_48         0x000C0000
#define BPORTAL_V2CE_49         0x000C4000

#define BPORTAL_CE_IDX(x, y)    ((y) + (BPORTAL_CE_1 * (x)))

/* Cached portion of portal space */

#define BPORTAL_CR              0x00000000 /* Command ring */
#define BPORTAL_RR0             0x00000100 /* Response ring 0 */
#define BPORTAL_RR1             0x00000140 /* Response ring 1 */
#define BPORTAL_RR              BPORTAL_RR0
#define BPORTAL_RCR             0x00001000 /* Release command ring */
#define BPORTAL_RCR_PRODIDX     0x00003000 /* Release producer index */
#define BPORTAL_RCR_CONSIDX     0x00003100 /* Release consumer index */

#define BPORTAL_RCR0            0x00001000 /* Release command ring 0 */
#define BPORTAL_RCR1            0x00001040 /* Release command ring 1 */
#define BPORTAL_RCR2            0x00001080 /* Release command ring 2 */
#define BPORTAL_RCR3            0x000010C0 /* Release command ring 3 */
#define BPORTAL_RCR4            0x00001100 /* Release command ring 4 */
#define BPORTAL_RCR5            0x00001140 /* Release command ring 5 */
#define BPORTAL_RCR6            0x00001180 /* Release command ring 6 */
#define BPORTAL_RCR7            0x000011C0 /* Release command ring 7 */

/*
 * Release command ring
 */

typedef struct bportal_release
    {
    volatile UINT8      bportalVerb;
    volatile UINT8      bportalBpid0;
    volatile UINT16     bportalBufAddr0Hi;
    volatile UINT32     bportalBufAddr0;
    volatile UINT8      bportalRsvd0;
    volatile UINT8      bportalBpid1;
    volatile UINT16     bportalBufAddr1Hi;
    volatile UINT32     bportalBufAddr1;
    volatile UINT8      bportalRsvd1;
    volatile UINT8      bportalBpid2;
    volatile UINT16     bportalBufAddr2Hi;
    volatile UINT32     bportalBufAddr2;
    volatile UINT8      bportalRsvd2;
    volatile UINT8      bportalBpid3;
    volatile UINT16     bportalBufAddr3Hi;
    volatile UINT32     bportalBufAddr3;
    volatile UINT8      bportalRsvd3;
    volatile UINT8      bportalBpid4;
    volatile UINT16     bportalBufAddr4Hi;
    volatile UINT32     bportalBufAddr4;
    volatile UINT8      bportalRsvd4;
    volatile UINT8      bportalBpid5;
    volatile UINT16     bportalBufAddr5Hi;
    volatile UINT32     bportalBufAddr5;
    volatile UINT8      bportalRsvd5;
    volatile UINT8      bportalBpid6;
    volatile UINT16     bportalBufAddr6Hi;
    volatile UINT32     bportalBufAddr6;
    volatile UINT8      bportalRsvd6;
    volatile UINT8      bportalBpid7;
    volatile UINT16     bportalBufAddr7Hi;
    volatile UINT32     bportalBufAddr7;
    } BPORTAL_RELEASE;

#define BPORTAL_RC_VERB_VALID       0x80
#define BPORTAL_RC_VERB_USE_BPID0   0x20    /* Use only bpid0's pool */
#define BPORTAL_RC_VERB_USE_BPIDBUF 0x30    /* Use all of the bpid fields*/
#define BPORTAL_RC_VERB_NBUF        0x0F

#define BPORTAL_NBUF_0              0x00
#define BPORTAL_NBUF_1              0x01
#define BPORTAL_NBUF_2              0x02
#define BPORTAL_NBUF_3              0x03
#define BPORTAL_NBUF_4              0x04
#define BPORTAL_NBUF_5              0x05
#define BPORTAL_NBUF_6              0x06
#define BPORTAL_NBUF_7              0x07
#define BPORTAL_NBUF_8              0x08

/*
 * Management commands
 */

/* Generic command/result structures */

typedef struct bportal_mc
    {
    volatile UINT8      bportalVerb;
    volatile UINT8      bportalRsvd0[3];
    volatile UINT32     bportalRsvd1[15];
    } BPORTAL_MGMTCMD;

typedef struct bportal_mr
    {
    volatile UINT8      bportalVerb;
    volatile UINT8      bportalRslt;
    volatile UINT16     bportalRsvd0;
    volatile UINT32     bportalRsvd1[15];
    } BPORTAL_MGMTRESP;

/* Acquire buffer */

typedef struct bportal_acquire
    {
    volatile UINT8      bportalVerb;    /* Command verb */
    volatile UINT8      bportalBpid;    /* Buffer pool ID */
    volatile UINT16     bportalRsvd0;
    volatile UINT32     bportalRsvd1[15];    
    } BPORTAL_ACQUIRE;

/* Verb field */

#define BPORTAL_AQ_VERB_VALID       0x80
#define BPORTAL_AQ_VERB_QUERY       0x40
#define BPORTAL_AQ_VERB_ACQUIRE     0x10
#define BPORTAL_AQ_VERB_NBUF        0x0F


/* Buffer acquire response */

typedef struct bportal_acquire_resp
    {
    volatile UINT8      bportalVerb;
    volatile UINT8      bportalBpid;
    volatile UINT16     bportalBufAddr0Hi;
    volatile UINT32     bportalBufAddr0;
    volatile UINT16     bportalRsvd0;
    volatile UINT16     bportalBufAddr1Hi;
    volatile UINT32     bportalBufAddr1;
    volatile UINT16     bportalRsvd1;
    volatile UINT16     bportalBufAddr2Hi;
    volatile UINT32     bportalBufAddr2;
    volatile UINT16     bportalRsvd2;
    volatile UINT16     bportalBufAddr3Hi;
    volatile UINT32     bportalBufAddr3;
    volatile UINT16     bportalRsvd3;
    volatile UINT16     bportalBufAddr4Hi;
    volatile UINT32     bportalBufAddr4;
    volatile UINT16     bportalRsvd4;
    volatile UINT16     bportalBufAddr5Hi;
    volatile UINT32     bportalBufAddr5;
    volatile UINT16     bportalRsvd5;
    volatile UINT16     bportalBufAddr6Hi;
    volatile UINT32     bportalBufAddr6;
    volatile UINT16     bportalRsvd6;
    volatile UINT16     bportalBufAddr7Hi;
    volatile UINT32     bportalBufAddr7;
    } BPORTAL_ACQUIRE_RESP;

#define BPORTAL_AQR_VERB_VALID      0x80
#define BPORTAL_AQR_VERB_ACQUIRE    0x10
#define BPORTAL_AQR_VERB_BADCMD     0x60
#define BPORTAL_AQR_VERB_ECC_ERR    0x70

/* Buffer pool query response */

typedef struct bportal_query_resp
    {
    volatile UINT8      bportalVerb;
    volatile UINT8      bportalRsvd0;
    volatile UINT16     bportalRsvd1[1];
    volatile UINT32     bportalRsvd2[9];
    volatile UINT32     bportalBpAsHi;        /* Availability state */
    volatile UINT32     bportalBpAsLo;
    volatile UINT32     bportalRsvd3[2];
    volatile UINT32     bportalBpDsHi;        /* Depletion state */
    volatile UINT32     bportalBpDsLo;
    } BPORTAL_QUERY_RESP;

#define BPORTAL_AQR_VERB_VALID      0x80
#define BPORTAL_AQR_VERB_QUERY      0x20

/* Cache inhibited area */

#define BPORTAL_CI_0                0x00000000
#define BPORTAL_CI_1                0x00001000
#define BPORTAL_CI_2                0x00002000
#define BPORTAL_CI_3                0x00003000
#define BPORTAL_CI_4                0x00004000
#define BPORTAL_CI_5                0x00005000
#define BPORTAL_CI_6                0x00006000
#define BPORTAL_CI_7                0x00007000
#define BPORTAL_CI_8                0x00008000
#define BPORTAL_CI_9                0x00009000

#define BPORTAL_CI_IDX(x, y)        ((y) + (BPORTAL_CI_1 * (x)))

#define BPORTAL_CI_OFFSET           0x00100000

/* For Revision 2 Bman, the CI offset is 16MB, not 1MB */

#define BPORTAL_V2CI_OFFSET         0x01000000

#if CPU_FAMILY==PPC
    
#define BPORTAL_CI_RCR_PRODIDX      0x00000000 /* Release producer idx */
#define BPORTAL_CI_RCR_CONSIDX      0x00000004 /* Release consumer idx */
#define BPORTAL_CI_RCR_ITR          0x00000008 /* Release intr thresh */
#define BPORTAL_CI_CFG              0x00000100 /* Configuration */
#define BPORTAL_CI_SCN0             0x00000200 /* State change notification */
#define BPORTAL_CI_SCN1             0x00000204 /* State change notification */
#define BPORTAL_CI_ISR              0x00000E00 /* Interrupt status */
#define BPORTAL_CI_IER              0x00000E04 /* Interrupt enable */
#define BPORTAL_CI_ISDR             0x00000E08 /* Intr sts disable */
#define BPORTAL_CI_IIR              0x00000E0C /* Intr inhibit reg */
#define BPORTAL_CI_ITPR             0x00000E14 /* Intr timeout period */
    
#endif /* CPU_FAMILY==PPC */
    
#if CPU_FAMILY==ARM
    
#define BPORTAL_CI_RCR_PRODIDX      0x00003000 /* Release producer idx */
#define BPORTAL_CI_RCR_CONSIDX      0x00003100 /* Release consumer idx */
#define BPORTAL_CI_RCR_ITR          0x00003200 /* Release intr thresh */
#define BPORTAL_CI_CFG              0x00003300 /* Configuration */
#define BPORTAL_CI_SCN0             0x00003400 /* State change notification */
#define BPORTAL_CI_SCN1             0x00003440 /* State change notification */
#define BPORTAL_CI_ISR              0x00003E00 /* Interrupt status */
#define BPORTAL_CI_IER              0x00003E40 /* Interrupt enable */
#define BPORTAL_CI_ISDR             0x00003E80 /* Intr sts disable */
#define BPORTAL_CI_IIR              0x00003EC0 /* Intr inhibit reg */
#define BPORTAL_CI_ITPR             0x00003740 /* Intr timeout period */
    
#endif /* CPU_FAMILY==ARM */
    
/* Portal configuration register */

#define BPORTAL_CI_CFG_BPM          0x00000003 /* RCR production mode */

#define BPORTAL_EPM_PICI            0x00000000 /* PI write, uncached */
#define BPORTAL_EPM_PICE            0x00000001 /* PI write, cached */
#define BPORTAL_EPM_VBIT            0x00000002 /* Valid bit mode */

/* Interrupt status register */

#define BPORTAL_CI_ISR_DSCN         0x00000001 /* State change notif. */
#define BPORTAL_CI_ISR_RCRI         0x00000002 /* Release cmd thr. */

/*
 * For Revision 1 Bman, there can be as many as 10 software portals.
 * For Revision 2 Bman (T4240), there can be 50. Later revs may have
 * even more.
 */

#define BPORTAL_PORTAL_CNT          50
    
/* Buffer Pool Number */

#define BUFFER_POOL_CNT             64
    
/*
 * The release command ring has 8 slots.
 */

#define BPORTAL_QUEUE_CNT           8

/*
 * Enqueue indexes:
 * Only the lower 4 bits of all the produces/consumer indexes are valid.
 * The lower 3 bits represent the actual index value. The 4th bit is
 * the valid polarity bit that the qmanager is expecting to be written
 * upon the next update by host software. This bit toggles when the index
 * wraps from 7 back to 0.
 * De
 */

#define BPORTAL_IDX(x)              ((x) & 0x7)
#define BPORTAL_IDX_VP              0x8

#define PORTAL_TIMEOUT              10000

typedef struct bportal
    {
    volatile void *             bportalCeBase;
    volatile void *             bportalCiBase;
    volatile BPORTAL_RELEASE *  bportalRcr;    /* Release command ring */
    volatile UINT32 *           bportalRcrCeProdIdx; /* Release producer idx */
    volatile UINT32 *           bportalRcrCeConsIdx; /* Release consumer idx */
    volatile void *             bportalCr;    /* Management cmd reg */
    volatile void *             bportalRr0;    /* Management resp reg 0 */
    volatile void *             bportalRr1;    /* Management resp reg 0 */
    volatile void *             bportalRrCur;    /* Management resp current */
    VXB_DEV_ID                  bportalDev;    /* Owner */
    UINT8                       bportalMcPol;    /* Management polarity */
    UINT8                       bportalAcVbit;    /* Allocate polarity */
    UINT8                       bportalRcVbit;    /* Release polarity */
    int                         bportalIntCtx;
    int                         bportalRcrProdIdx;
    int                         bportalRcrConsIdx;
    int                         bportalRcrAvail;
    int                         bportalRefcnt;
    int                         bportalIdx;
    SEM_ID                      bportalSem;
    VXB_RESOURCE *              intRes;
    } BPORTAL;

#define BPORTAL_INC(x, y)           (x) = ((x + 1) & (y - 1))

#define BPORTAL_CI_READ_4(p, addr)          bportalCiRead4(p, addr)
#define BPORTAL_CI_WRITE_4(p, addr, data)   bportalCiWrite4(p, addr, data)

typedef void (*bportalIntFunc)(void *);

#define BM_ADDR_LO(y)  ((UINT32)(((UINT64) (y)) & 0xFFFFFFFF))
#define BM_ADDR_HI(y)  (((UINT32)(((UINT64) (y)) >> 32) & 0xFFFFFFFF))

IMPORT STATUS bportalAlloc (BPORTAL *, UINT8, UINT64 *);
IMPORT STATUS bportalFree (BPORTAL *, UINT8, UINT64);
IMPORT STATUS bportalLocalAlloc (UINT8, UINT64 *);
IMPORT STATUS bportalLocalFree (UINT8, UINT64);
IMPORT STATUS bportalSafeAlloc (BPORTAL *, UINT8, UINT64 *);
IMPORT STATUS bportalSafeFree (BPORTAL *, UINT8, UINT64);
IMPORT STATUS bportalMultiAlloc (BPORTAL *, UINT8, UINT64 *, UINT64 *, UINT64 *,
    UINT64 *, UINT64 *, UINT64 *, UINT64 *, UINT64 *, UINT8);
IMPORT STATUS bportalMultiFree (BPORTAL *, UINT8, UINT64, UINT64, UINT64,
    UINT64, UINT64, UINT64, UINT64, UINT64, UINT8);
IMPORT STATUS bportalLocalMultiAlloc (UINT8, UINT64 *, UINT64 *, UINT64 *,
    UINT64 *, UINT64 *, UINT64 *, UINT64 *, UINT64 *, UINT8);
IMPORT STATUS bportalLocalMultiFree (UINT8, UINT64, UINT64, UINT64, UINT64,
    UINT64, UINT64, UINT64, UINT64, UINT8);
IMPORT STATUS bportalSafeMultiAlloc (BPORTAL *, UINT8, UINT64 *, UINT64 *,
    UINT64 *, UINT64 *, UINT64 *, UINT64 *, UINT64 *, UINT64 *, UINT8);
IMPORT STATUS bportalSafeMultiFree (BPORTAL *, UINT8, UINT64, UINT64, UINT64,
    UINT64, UINT64, UINT64, UINT64, UINT64, UINT8);
IMPORT STATUS bportalQuery (BPORTAL *, BPORTAL_QUERY_RESP *);
IMPORT STATUS bportalCreate (VXB_DEV_ID, int);
IMPORT STATUS bportalDestroy (VXB_DEV_ID, int);
IMPORT STATUS bportalAcquire (int, BPORTAL **);
IMPORT STATUS bportalRelease (int, BPORTAL *);
IMPORT STATUS bportalIntConnect (BPORTAL *, bportalIntFunc, void *);
IMPORT STATUS bportalIntDisconnect (BPORTAL *, bportalIntFunc, void *);
IMPORT STATUS bportalIntEnable (BPORTAL *, bportalIntFunc, void *);
IMPORT STATUS bportalIntDisable (BPORTAL *, bportalIntFunc, void *);
IMPORT int bportalCountGet (BPORTAL *, UINT8);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbQorIQBmanPortalh */
