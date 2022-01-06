/* vxbQorIQQmanPortal.h - Queue manager portal header for QorIQ */

/*
 * Copyright (c) 2008-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
DESCRIPTION

This file contains register definitions for the Freescale QorIQ
Queue Manager portal interface. There are 10 software accessible
portals, mapped within a 2MB local access window (LAW).
*/

/*
modification history
--------------------
05may17,wch  added support for ARM (F8333)
30jul15,msx  Fixing static analysis issue.
28dec14,fao  adopt PPC64 (US48435)  
21nov14,wap  Merge in multi-instance/multi-queue support
25apr14,fao  merged this file from vx6.9.3.3 and corrected the modify history 
20feb14,dlk  Correct QPORTAL_{PN,SN,SA,MN,MA} macros.
21feb13,dlk  Allow BSP to determine the job queue used for each portal.
25jan13,wap  Apply updates from review
16oct12,wap  Change ctxAHi argument in frame queue init API to 32 bits
13aug12,wap  Update Qman for T4240, merge in congestion group support
05apr11,tlu  Fix the order of bpid and offset defined in QPORTAL_SGLIST
             structure
07mar11,kxb  NAP 2.0 merge: QPORTAL_ORPWRS macro fix;
             export qportalOrpMrDequeue
12mar10,wap  Update enqueue API to support order restoration
10feb10,wap  Update frame descriptor structure to reflect rev 2.0 silicon
             layout
03nov09,wap  API mutual exclusion fixes, cleanups
13oct09,wap  Use contextB hints for event handling
06oct09,wap  Allow qportalFqInit() to specify intra-class scheduling
             credit value
03oct09,wap  Add APIs for handling message rings, add tag argument to
             qportalEnqueue()
07aug09,wap  Implement interrupt/event dispatching
06aug09,wap  Allow qportalDequeue() to return contextB info
16jul09,wap  Add definition for channel source bits for SDQCR
             register, add prototype for qportalDequeueSourceSelect()
             function.
23jun09,wap  Keep track of available enqueue descriptors
16jun09,wap  Add definition for scatter/gather table
20jan09,wap  Update filename
02dec08,wap  written
*/

#ifndef __INCvxbQorIQQmanPortalh
#define __INCvxbQorIQQmanPortalh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The CoreNet portal space is mapped within a local access window
 * that's 2 MB in size. That window is in turn divided into two 1MB
 * sections. The first 1MB is cache-enabled, and contains the main
 * portal command and response queues. The second half is
 * cache-inhibited, and contains the producer/consumer index,
 * configuration and interrupt registers.
 */

/* Cache enabled area */

/*
 * Channel assignments. Channels are dedicated to specific portals
 * (except for the pool channels, which can be processed by various
 * different portals). Each channel can also have up to 8 work queues.
 */

/* Software portal channel assignments */

#define QPORTAL_CHAN_SW0                0x0000
#define QPORTAL_CHAN_SW1                0x0001
#define QPORTAL_CHAN_SW2                0x0002
#define QPORTAL_CHAN_SW3                0x0003
#define QPORTAL_CHAN_SW4                0x0004
#define QPORTAL_CHAN_SW5                0x0005
#define QPORTAL_CHAN_SW6                0x0006
#define QPORTAL_CHAN_SW7                0x0007
#define QPORTAL_CHAN_SW8                0x0008
#define QPORTAL_CHAN_SW9                0x0009

/* Pool channels (starts at pool 1 for some reason) */

#define QPORTAL_CHAN_POOL1              0x0021
#define QPORTAL_CHAN_POOL2              0x0022
#define QPORTAL_CHAN_POOL3              0x0023
#define QPORTAL_CHAN_POOL4              0x0024
#define QPORTAL_CHAN_POOL5              0x0025
#define QPORTAL_CHAN_POOL6              0x0026
#define QPORTAL_CHAN_POOL7              0x0027
#define QPORTAL_CHAN_POOL8              0x0028
#define QPORTAL_CHAN_POOL9              0x0029
#define QPORTAL_CHAN_POOL10             0x002A
#define QPORTAL_CHAN_POOL11             0x002B
#define QPORTAL_CHAN_POOL12             0x002C
#define QPORTAL_CHAN_POOL13             0x002D
#define QPORTAL_CHAN_POOL14             0x002E
#define QPORTAL_CHAN_POOL15             0x002F

/* Direct portal channel assignments, frame manager 0 */

#define QPORTAL_CHAN_FM0_SP0            0x0040
#define QPORTAL_CHAN_FM0_SP1            0x0041
#define QPORTAL_CHAN_FM0_SP2            0x0042
#define QPORTAL_CHAN_FM0_SP3            0x0043
#define QPORTAL_CHAN_FM0_SP4            0x0044
#define QPORTAL_CHAN_FM0_SP5            0x0045
#define QPORTAL_CHAN_FM0_SP6            0x0046
#define QPORTAL_CHAN_FM0_SP7            0x0047
#define QPORTAL_CHAN_FM0_SP8            0x0048
#define QPORTAL_CHAN_FM0_SP9            0x0049
#define QPORTAL_CHAN_FM0_SP10           0x004A
#define QPORTAL_CHAN_FM0_SP11           0x004B

/* Direct portal channel assignments, frame manager 1 */

#define QPORTAL_CHAN_FM1_SP0            0x0060
#define QPORTAL_CHAN_FM1_SP1            0x0061
#define QPORTAL_CHAN_FM1_SP2            0x0062
#define QPORTAL_CHAN_FM1_SP3            0x0063
#define QPORTAL_CHAN_FM1_SP4            0x0064
#define QPORTAL_CHAN_FM1_SP5            0x0065
#define QPORTAL_CHAN_FM1_SP6            0x0066
#define QPORTAL_CHAN_FM1_SP7            0x0067
#define QPORTAL_CHAN_FM1_SP8            0x0068
#define QPORTAL_CHAN_FM1_SP9            0x0069
#define QPORTAL_CHAN_FM1_SP10           0x006A
#define QPORTAL_CHAN_FM1_SP11           0x006B

/* T4240 software portal channels */

#define QPORTAL_V3CHAN_SW0              QPORTAL_CHAN_SW0
#define QPORTAL_V3CHAN_SW1              QPORTAL_CHAN_SW1
#define QPORTAL_V3CHAN_SW2              QPORTAL_CHAN_SW2
#define QPORTAL_V3CHAN_SW3              QPORTAL_CHAN_SW3
#define QPORTAL_V3CHAN_SW4              QPORTAL_CHAN_SW4
#define QPORTAL_V3CHAN_SW5              QPORTAL_CHAN_SW5
#define QPORTAL_V3CHAN_SW6              QPORTAL_CHAN_SW6
#define QPORTAL_V3CHAN_SW7              QPORTAL_CHAN_SW7
#define QPORTAL_V3CHAN_SW8              QPORTAL_CHAN_SW8
#define QPORTAL_V3CHAN_SW9              QPORTAL_CHAN_SW9
#define QPORTAL_V3CHAN_SW10             0x000A
#define QPORTAL_V3CHAN_SW11             0x000B
#define QPORTAL_V3CHAN_SW12             0x000C
#define QPORTAL_V3CHAN_SW13             0x000D
#define QPORTAL_V3CHAN_SW14             0x000E
#define QPORTAL_V3CHAN_SW15             0x000F
#define QPORTAL_V3CHAN_SW16             0x0010
#define QPORTAL_V3CHAN_SW17             0x0011
#define QPORTAL_V3CHAN_SW18             0x0012
#define QPORTAL_V3CHAN_SW19             0x0013
#define QPORTAL_V3CHAN_SW20             0x0014
#define QPORTAL_V3CHAN_SW21             0x0015
#define QPORTAL_V3CHAN_SW22             0x0016
#define QPORTAL_V3CHAN_SW23             0x0017
#define QPORTAL_V3CHAN_SW24             0x0018
#define QPORTAL_V3CHAN_SW25             0x0019
#define QPORTAL_V3CHAN_SW26             0x001A
#define QPORTAL_V3CHAN_SW27             0x001B
#define QPORTAL_V3CHAN_SW28             0x001C
#define QPORTAL_V3CHAN_SW29             0x001D
#define QPORTAL_V3CHAN_SW30             0x001E
#define QPORTAL_V3CHAN_SW31             0x001F
#define QPORTAL_V3CHAN_SW32             0x0020
#define QPORTAL_V3CHAN_SW33             0x0021
#define QPORTAL_V3CHAN_SW34             0x0022
#define QPORTAL_V3CHAN_SW35             0x0023
#define QPORTAL_V3CHAN_SW36             0x0024
#define QPORTAL_V3CHAN_SW37             0x0025
#define QPORTAL_V3CHAN_SW38             0x0026
#define QPORTAL_V3CHAN_SW39             0x0027
#define QPORTAL_V3CHAN_SW40             0x0028
#define QPORTAL_V3CHAN_SW41             0x0029
#define QPORTAL_V3CHAN_SW42             0x002A
#define QPORTAL_V3CHAN_SW43             0x002B
#define QPORTAL_V3CHAN_SW44             0x002C
#define QPORTAL_V3CHAN_SW45             0x002D
#define QPORTAL_V3CHAN_SW46             0x002E
#define QPORTAL_V3CHAN_SW47             0x002F
#define QPORTAL_V3CHAN_SW48             0x0030
#define QPORTAL_V3CHAN_SW49             0x0031

/* T4240 pool channels */

#define QPORTAL_V3CHAN_POOL1            0x0401
#define QPORTAL_V3CHAN_POOL2            0x0402
#define QPORTAL_V3CHAN_POOL3            0x0403
#define QPORTAL_V3CHAN_POOL4            0x0404
#define QPORTAL_V3CHAN_POOL5            0x0405
#define QPORTAL_V3CHAN_POOL6            0x0406
#define QPORTAL_V3CHAN_POOL7            0x0407
#define QPORTAL_V3CHAN_POOL8            0x0408
#define QPORTAL_V3CHAN_POOL9            0x0409
#define QPORTAL_V3CHAN_POOL10           0x040A
#define QPORTAL_V3CHAN_POOL11           0x040B
#define QPORTAL_V3CHAN_POOL12           0x040C
#define QPORTAL_V3CHAN_POOL13           0x040D
#define QPORTAL_V3CHAN_POOL14           0x040E
#define QPORTAL_V3CHAN_POOL15           0x040F

/* T4240 direct connect portals */

#define QPORTAL_V3CHAN_FM0              0x0800    /* Frame manager 0 */
#define QPORTAL_V3CHAN_FM0_SP0          QPORTAL_V3CHAN_FM0
#define QPORTAL_V3CHAN_FM0_SP1          0x0801
#define QPORTAL_V3CHAN_FM0_SP2          0x0802
#define QPORTAL_V3CHAN_FM0_SP3          0x0803
#define QPORTAL_V3CHAN_FM0_SP4          0x0804
#define QPORTAL_V3CHAN_FM0_SP5          0x0805
#define QPORTAL_V3CHAN_FM0_SP6          0x0806
#define QPORTAL_V3CHAN_FM0_SP7          0x0807
#define QPORTAL_V3CHAN_FM0_SP8          0x0808
#define QPORTAL_V3CHAN_FM0_SP9          0x0809
#define QPORTAL_V3CHAN_FM0_SP10         0x080A
#define QPORTAL_V3CHAN_FM0_SP11         0x080B
#define QPORTAL_V3CHAN_FM0_SP12         0x080C
#define QPORTAL_V3CHAN_FM0_SP13         0x080D
#define QPORTAL_V3CHAN_FM0_SP14         0x080E
#define QPORTAL_V3CHAN_FM0_SP15         0x080F

#define QPORTAL_V3CHAN_FM1              0x0820    /* Frame manager 1 */
#define QPORTAL_V3CHAN_FM1_SP0          QPORTAL_V3CHAN_FM1
#define QPORTAL_V3CHAN_FM1_SP1          0x0821
#define QPORTAL_V3CHAN_FM1_SP2          0x0822
#define QPORTAL_V3CHAN_FM1_SP3          0x0823
#define QPORTAL_V3CHAN_FM1_SP4          0x0824
#define QPORTAL_V3CHAN_FM1_SP5          0x0825
#define QPORTAL_V3CHAN_FM1_SP6          0x0826
#define QPORTAL_V3CHAN_FM1_SP7          0x0827
#define QPORTAL_V3CHAN_FM1_SP8          0x0828
#define QPORTAL_V3CHAN_FM1_SP9          0x0829
#define QPORTAL_V3CHAN_FM1_SP10         0x082A
#define QPORTAL_V3CHAN_FM1_SP11         0x082B
#define QPORTAL_V3CHAN_FM1_SP12         0x082C
#define QPORTAL_V3CHAN_FM1_SP13         0x082D
#define QPORTAL_V3CHAN_FM1_SP14         0x082E
#define QPORTAL_V3CHAN_FM1_SP15         0x082F

#define QPORTAL_V3CHAN_SEC              0x0840    /* security engine */

#define QPORTAL_V3CHAN_PME              0x0860    /* pattern matching engine */

#define QPORTAL_V3CHAN_RMAN             0x0880    /* Rman */
#define QPORTAL_V3CHAN_RMAN_SP0         QPORTAL_V3CHAN_RMAN
#define QPORTAL_V3CHAN_RMAN_SP1         0x0881

#define QPORTAL_V3CHAN_DCE              0x08A0    /* compression/decompression engine */
#define QPORTAL_V3CHAN_DCE_SP0          QPORTAL_V3CHAN_DCE
#define QPORTAL_V3CHAN_DCE_SP1          0x08A1

#define QPORTAL_WQID(chan, wq)          (((chan) << 3) | ((wq) & 0x7))

/* There are a total of 10 software portals (and 4 direct connect portals) */

#if CPU_FAMILY==PPC
#define QPORTAL_CE_0                    0x00000000
#define QPORTAL_CE_1                    0x00004000
#define QPORTAL_CE_2                    0x00008000
#define QPORTAL_CE_3                    0x0000C000
#define QPORTAL_CE_4                    0x00010000
#define QPORTAL_CE_5                    0x00014000
#define QPORTAL_CE_6                    0x00018000
#define QPORTAL_CE_7                    0x0001C000
#define QPORTAL_CE_8                    0x00020000
#define QPORTAL_CE_9                    0x00024000
#endif /* CPU_FAMILY==PPC */

#if CPU_FAMILY==ARM
#define QPORTAL_CE_0                    0x00000000
#define QPORTAL_CE_1                    0x00010000
#define QPORTAL_CE_2                    0x00020000
#define QPORTAL_CE_3                    0x00030000
#define QPORTAL_CE_4                    0x00040000
#define QPORTAL_CE_5                    0x00050000
#define QPORTAL_CE_6                    0x00060000
#define QPORTAL_CE_7                    0x00070000
#define QPORTAL_CE_8                    0x00080000
#define QPORTAL_CE_9                    0x00090000
#endif /* CPU_FAMILY==ARM */

#define QPORTAL_CE_IDX(x, y)            ((y) + (QPORTAL_CE_1 * (x)))

/* Cached portion of portal space */

#define QPORTAL_EQCR                    0x00000000 /* Enqueue command rings */
#define QPORTAL_DQRR                    0x00001000 /* Dequeue response rings */
#define QPORTAL_MR                      0x00002000 /* Message ring */
#define QPORTAL_EQ_PRODIDX              0x00003000 /* Enqueue producer index */

#if CPU_FAMILY==PPC
#define QPORTAL_EQ_CONSIDX              0x00003100 /* Enqueue consumer index */
#define QPORTAL_DQ_PRODIDX              0x00003200 /* Dequeue producer index */
#define QPORTAL_DQ_CONSIDX              0x00003300 /* Dequeue producer index */
#define QPORTAL_MR_PRODIDX              0x00003400 /* Message producer index */
#define QPORTAL_MR_CONSIDX              0x00003500 /* Message consumer index */
#define QPORTAL_RO_IDX                  0x00003600 /* Read only indexes */
#endif /* CPU_FAMILY==PPC */

#if CPU_FAMILY==ARM
#define QPORTAL_EQ_CONSIDX              0x00003040 /* Enqueue consumer index */
#define QPORTAL_DQ_PRODIDX              0x00003100 /* Dequeue producer index */
#define QPORTAL_DQ_CONSIDX              0x00003140 /* Dequeue producer index */
#define QPORTAL_MR_PRODIDX              0x00003300 /* Message producer index */
#define QPORTAL_MR_CONSIDX              0x00003340 /* Message consumer index */
#define QPORTAL_RO_IDX                  0x00003400 /* Read only indexes */
#endif /* CPU_FAMILY==ARM */

#define QPORTAL_MCR                     0x00003800 /* Mgmt command register */
#define QPORTAL_MRR0                    0x00003900 /* Mgmt response register 0 */
#define QPORTAL_MRR1                    0x00003940 /* Mgmt response register 0 */

typedef struct qportal_roidx
    {
    volatile UINT32    qportalEqcrConsidx;
    volatile UINT32    qportalDqrrProdidx;
    volatile UINT32    qportalMrProdidx;
    volatile UINT32    qportalRsvd[13];
    } QPORTAL_ROIDX;

#define QPORTAL_EQCR0                   0x00000000 /* Enqueue command ring 0 */
#define QPORTAL_EQCR1                   0x00000040 /* Enqueue command ring 1 */
#define QPORTAL_EQCR2                   0x00000080 /* Enqueue command ring 2 */
#define QPORTAL_EQCR3                   0x000000C0 /* Enqueue command ring 3 */
#define QPORTAL_EQCR4                   0x00000100 /* Enqueue command ring 4 */
#define QPORTAL_EQCR5                   0x00000140 /* Enqueue command ring 5 */
#define QPORTAL_EQCR6                   0x00000180 /* Enqueue command ring 6 */
#define QPORTAL_EQCR7                   0x000001C0 /* Enqueue command ring 7 */

/* Response verb types */

#define QPORTAL_RSP_VERB_DEQUEUE        0x60
#define QPORTAL_RSP_VERB_REJECT         0x20    /* Enqueue rejection notification */
#define QPORTAL_RSP_VERB_FQRN           0x21    /* Retirement notification */
#define QPORTAL_RSP_VERB_FQRNI          0x22    /* Retirement notif. immediate */
#define QPORTAL_RSP_VERB_FQRL           0x23    /* Retirement notif. last */
#define QPORTAL_RSP_VERB_FQPN           0x24    /* Queue parked */

/* Management command verb types */

#define QPORTAL_CMD_VERB_INITPARK       0x40    /* Init queue and park */
#define QPORTAL_CMD_VERB_INITSCHED      0x41    /* Init queue and schedule */
#define QPORTAL_CMD_VERB_GETPFLDS       0x44    /* Get programmable fields */
#define QPORTAL_CMD_VERB_GETNPFLDS      0x45    /* Get non-programmable fields */
#define QPORTAL_CMD_VERB_GETWQLEN       0x46    /* Get WQ len in a channel */
#define QPORTAL_CMD_VERB_GETWQLEND      0x47    /* Get WQ len dedicated channel */
#define QPORTAL_CMD_VERB_SCHEDFQ        0x48    /* Schedule frame queue */
#define QPORTAL_CMD_VERB_FORCEELG       0x49    /* Force queue eligible */
#define QPORTAL_CMD_VERB_RETIREQ        0x4A    /* Retire frame queue */
#define QPORTAL_CMD_VERB_OUTOFSVC       0x4B    /* Take queue out of service */
#define QPORTAL_CMD_VERB_INITCGR        0x50    /* Initialize CGR */
#define QPORTAL_CMD_VERB_MODCGR         0x51    /* Modify CGR */
#define QPORTAL_CMD_VERB_TESTCGR        0x52    /* CGR test write */
#define QPORTAL_CMD_VERB_QUERYCGR       0x58    /* Query CGR */
#define QPORTAL_CMD_VERB_QUERYCSTS      0x59    /* Query congestion state */

/* Frame descriptor structure, used with enqueue/dequeue commands */

typedef struct qportal_fdesc
    {
    volatile UINT8      qportalDdLioLo;    /* Debug/LIODN bits 0-5 */
    volatile UINT8      qportalBpid;    /* Buffer pool ID */
    volatile UINT8      qportalLioHi;    /* LIODN bits 4-9 */
    volatile UINT8      qportalAddrHi;    /* Buffer address high bits */
    volatile UINT32     qportalAddrLo;    /* Buffer address low bits */
    volatile UINT32     qportalOffLen;    /* Offset/length for stashing */
    volatile UINT32     qportalCmd;    /* User command */
    } QPORTAL_FDESC;

#define QPORTAL_DDPID_DD                0xC0 /* Dynamic debug */
#define QPORTAL_DDPID_PID               0x3F /* Frame partition ID */

/* Debug marking points */

#define QPORTAL_FDESC_DD_OFF            0x00
#define QPORTAL_FDESC_DD_ON0            0x40
#define QPORTAL_FDESC_DD_ON1            0x80
#define QPORTAL_FDESC_DD_ON2            0xC0

#define QPORTAL_FDESC_OFFLEN_FMT        0xE0000000
#define QPORTAL_FDESC_OFFLEN_OFFSET     0x1FF00000
#define QPORTAL_FDESC_OFFLEN_LENGTH     0x000FFFFF
#define QPORTAL_FDESC_OFFLEN_CONGWEIGHT 0x1FFFFFFF

#define QPORTAL_FDESC_FMT_CONTIG        0x00000000
#define QPORTAL_FDESC_FMT_COMPOUND      0x20000000
#define QPORTAL_FDESC_FMT_LONG          0x40000000
#define QPORTAL_FDESC_FMT_SG            0x80000000
#define QPORTAL_FDESC_FMT_SG_LONG       0xC0000000

/*
 * Scatter/gather table element, used for frame descriptors with
 * 'compound' buffers. A scatter/gather table is made up of several
 * sglist entries in a contiguous block. An sglist entry with the
 * 'final' bit set indicates the end of the scatter/gather list.
 * An entry with the 'extention' bit set points to another
 * scatter/gather list.
 */

typedef struct qportal_sglist
    {
    volatile UINT32    qportalAddrHi;
    volatile UINT32    qportalAddrLo;
    volatile UINT32    qportalLength;
    volatile UINT16    qportalBpid;    /* bman pool to release to */
    volatile UINT16    qportalOffset;    /* data offset */
    } QPORTAL_SGLIST;

#define QPORTAL_SGLIST_EXTENSION        0x80000000
#define QPORTAL_SGLIST_FINAL            0x40000000


/*
 * Queue manager enqueue command
 */

typedef struct qportal_enqueue
    {
    volatile UINT8          qportalVerb;    /* Command verb */
    volatile UINT8          qportalDca;    /* Discrete consumption ack */
    volatile UINT16         qportalSeqNum;    /* Order restoration seqnum */
    volatile UINT32         qportalOrp;    /* Order restoration point ID */
    volatile UINT32         qportalFqId;    /* Frame Queue ID */
    volatile UINT32         qportalTag;    /* Enqueue command tag */
    volatile QPORTAL_FDESC  qportalFd;        /* Frame descriptor */
    volatile UINT32         qportalRsvd[8];    
    } QPORTAL_ENQUEUE;

/* Verb field */

#define QPORTAL_EQ_VERB_VALID           0x80
#define QPORTAL_EQ_VERB_COLOR           0x18
#define QPORTAL_EQ_VERB_INT             0x04
#define QPORTAL_EQ_VERB_ORDER           0x02
#define QPORTAL_EQ_VERB_ENQUEUE         0x01

#define QPORTAL_COLOR_GREEN             0x00
#define QPORTAL_COLOR_YELLOW            0x08
#define QPORTAL_COLOR_RED               0x10
#define QPORTAL_COLOR_OVERRIDE          0x18

/* DCA field */

#define QPORTAL_DCA_ENABLE              0x80
#define QPORTAL_DCA_PARK                0x40
#define QPORTAL_DCA_CONSIDX             0x0F

/* Order restoration sequence number field */

#define QPORTAL_SEQNUM_ORPTYPE          0x8000
#define QPORTAL_SEQNUM_NLIS             0x4000 /* Not last in sequence */
#define QPORTAL_SEQNUM_SEQNUM           0x3FFF

#define QPORTAL_ORPTYPE_DISCARD         0x0000
#define QPORTAL_ORPTYPE_ADVANCE         0x8000

/*
 * Queue manager dequeue response message
 */

typedef struct qportal_dequeue
    {
    volatile UINT8          qportalVerb;    /* Dequeue verb */
    volatile UINT8          qportalStat;    /* Status */
    volatile UINT16         qportalSeqNum;    /* Order restore seqnum */
    volatile UINT8          qportalTok;    /* Dequeue command token */
    volatile UINT8          qportalRsvd0[3];
    volatile UINT32         qportalFqId;    /* Frame queue ID */
    volatile UINT32         qportalCntxB;    /* Queue context B */
    volatile QPORTAL_FDESC  qportalFd;    /* Frame descriptor */
    volatile UINT32         qportalRsvd1[8];    
    } QPORTAL_DEQUEUE;

/* Verb field  */

#define QPORTAL_DQ_VERB_VALID           0x80
#define QPORTAL_DQ_VERB_DEQUEUE         0x60

/* Status field */

#define QPORTAL_DQ_STAT_EMPTY           0x80
#define QPORTAL_DQ_STAT_ACTIVE          0x40
#define QPORTAL_DQ_STAT_ELIGIBLE        0x20
#define QPORTAL_DQ_STAT_FRAMEDLVR       0x10
#define QPORTAL_DQ_STAT_PUSHTYPE        0x02
#define QPORTAL_DQ_STAT_EXPIRED         0x01

/*
 * Queue manager Enqueue Rejection Notification message
 */

typedef struct qportal_ern
    {
    volatile UINT8          qportalVerb;
    volatile UINT8          qportalDca;
    volatile UINT16         qportalSeqNum;
    volatile UINT32         qportalRejOrp; /* Rejection code/ORP */
    volatile UINT32         qportalFqId;
    volatile UINT32         qportalTag;
    volatile QPORTAL_FDESC  qportalFd;    /* Frame descriptor */
    volatile UINT32         qportalRsvd1[8];    
    } QPORTAL_ERN;

/* Verb field */

#define QPORTAL_ERN_VERB_VALID          0x80
#define QPORTAL_ERN_VERB_DC_ERN         0x20

/* Rejection code/ORP field */

#define QPORTAL_ERN_REJORP_RC           0xF0000000
#define QPORTAL_ERN_REJORP_ORP          0x0FFFFFFF

#define QPORTAL_ERN_RC_CG_TAILDROP      0x00000000
#define QPORTAL_ERN_RC_WRED             0x10000000
#define QPORTAL_ERN_RC_ERROR            0x20000000
#define QPORTAL_ERN_RC_EARLY            0x30000000
#define QPORTAL_ERN_RC_LATE             0x40000000
#define QPORTAL_ERN_RC_FQ_TAILDROP      0x50000000
#define QPORTAL_ERN_RC_RETIRED          0x60000000

/* Frame Queue State Change Notification Message Response */

typedef struct qportal_fqcn
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalFqs;
    volatile UINT16     qportalRsvd0[0];
    volatile UINT32     qportalRsvd1[1];
    volatile UINT32     qportalFqId;
    volatile UINT32     qportalCntxB;
    volatile UINT32     qportalRsvd2[12];    
    } QPORTAL_FQCN;

/* Verb field */

#define QPORTAL_FQCN_VERB_VALID         0x80
#define QPORTAL_FQCN_VERB_FQRN          0x21
#define QPORTAL_FQCN_VERB_FQRNI         0x22
#define QPORTAL_FQCN_VERB_FQRL          0x23
#define QPORTAL_FQCN_VERB_FQPN          0x24

/* Frame queue status field */

#define QPORTAL_FQCN_FQS_ORLP           0x02 /* ORL present */
#define QPORTAL_FQCN_FQS_NOTEMPTY       0x01 /* retired queue not empty */

/*
 * Management commands
 */

/* Generic command/result structures */

typedef struct qportal_mc
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRsvd0[3];
    volatile UINT32     qportalRsvd1[15];
    } QPORTAL_MGMTCMD;

typedef struct qportal_mr
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRslt;
    volatile UINT16     qportalRsvd0;
    volatile UINT32     qportalRsvd1[15];
    } QPORTAL_MGMTRESP;

#define QPORTAL_MR_RSLT_OK              0xF0
#define QPORTAL_MR_RSLT_BADCMD          0xFF

/* Initialize frame queue */

typedef struct qportal_initfq
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRsvd0;
    volatile UINT16     qportalWeMask;
    volatile UINT32     qportalFqId;
    volatile UINT16     qportalCount;
    volatile UINT8      qportalOrpc;
    volatile UINT8      qportalCgid;
    volatile UINT16     qportalFqCtrl;
    volatile UINT16     qportalDestWq;
    volatile UINT16     qportalIcsCred;
    volatile UINT16     qportalTdThresh;
    volatile UINT32     qportalCtxtB;
    volatile UINT16     qportalCtxtA;
    volatile UINT16     qportalCtxtA_AddrHi;
    volatile UINT32     qportalCtxtA_AddrLo;
    volatile UINT32     qportalRsvd[8];
    } QPORTAL_INITFQ;

/* Verb field */

#define QPORTAL_INITFQ_VERB_INITPARK    0x40    /* Init queue and park */
#define QPORTAL_INITFQ_VERB_INITSCHED   0x41    /* Init queue and schedule */
#define QPORTAL_INITFQ_VERB_VALID       0x80

/* WE mask field */

#define QPORTAL_INITFQ_WEMASK_CTXTA     0x0001    /* CTXTA valid */
#define QPORTAL_INITFQ_WEMASK_CTXTB     0x0002  /* CTXTB valid */
#define QPORTAL_INITFQ_WEMASK_TD_THR    0x0004
#define QPORTAL_INITFQ_WEMASK_ICS_CRED  0x0008
#define QPORTAL_INITFQ_WEMASK_DST_WQ    0x0010
#define QPORTAL_INITFQ_WEMASK_FQ_CTRL   0x0020
#define QPORTAL_INITFQ_WEMASK_CGID      0x0040
#define QPORTAL_INITFQ_WEMASK_ORPC      0x0080

/* ORPC field */

#define QPORTAL_INITFQ_ORPC_OLWS        0x03
#define QPORTAL_INITFQ_ORPC_OA          0x04
#define QPORTAL_INITFQ_ORPC_ORPRWS      0x38

/* Acceptable late window size */

#define QPORTAL_OLWS(x)                 ((x) & QPORTAL_INITFQ_ORPC_OLWS)

#define QPORTAL_OLWS_DISABLED           0x00
#define QPORTAL_OLWS_32                 0x01
#define QPORTAL_OLWS_ORPWRS             0x02
#define QPORTAL_OLWS_8192               0x03

/* Auto advance NESM window */

#define QPORTAL_OA(x)                   (((x) << 2) & QPORTAL_INITFQ_ORPC_OA)

#define QPORTAL_OA_DISABLED             0x0
#define QPORTAL_OA_ENABLED              0x1

/* Order restoration window size */

#define QPORTAL_ORPRWS(x)               (((x) << 3) & QPORTAL_INITFQ_ORPC_ORPRWS)

#define QPORTAL_ORPRWS_32               0
#define QPORTAL_ORPRWS_64               1
#define QPORTAL_ORPRWS_128              2
#define QPORTAL_ORPRWS_256              3
#define QPORTAL_ORPRWS_512              4
#define QPORTAL_ORPRWS_1024             5
#define QPORTAL_ORPRWS_2048             6
#define QPORTAL_ORPRWS_4096             7

/* Frame queue control field */

#define QPORTAL_INITFQ_FQCTRL_LCKCACHE  0x0001    /* Lock in cache */
#define QPORTAL_INITFQ_FQCTRL_HLDACTIVE 0x0002    /* Hold active in portal */
#define QPORTAL_INITFQ_FQCTRL_AVOIDBLK  0x0004    /* Don't block active */
#define QPORTAL_INITFQ_FQCTRL_FRCSFDR   0x0008    /* High prio SFDRs */
#define QPORTAL_INITFQ_FQCTRL_CPCSTASH  0x0040    /* CPC Stash enable */
#define QPORTAL_INITFQ_FQCTRL_CTXTASTSH 0x0080    /* ContextA stashing */
#define QPORTAL_INITFQ_FQCTRL_ORP       0x0100    /* Order restr. enable */
#define QPORTAL_INITFQ_FQCTRL_TDE       0x0200    /* Tail drop enable */
#define QPORTAL_INITFQ_FQCTRL_CGE       0x0400    /* Congestion grp enable */

/* TailDrop threshold field */

#define QPORTAL_TDTHRESH_EXP            0x001F    /* Exponent */
#define QPORTAL_TDTHRESH_MANT           0x1FE0    /* Mantissa */
#define QPORTAL_TDTHRESH_EXP_BITS       5
#define QPORTAL_TDTHRESH_MANT_BITS      8

#define QPORTAL_TD_EXP_VAL(x)           ((x) & QPORTAL_TDTHRESH_EXP)
#define QPORTAL_TD_MANT_VAL(x)          (((x) << 5) & QPORTAL_TDTHRESH_MANT)

/* Context A field */

#define QPORTAL_INITFQ_CTXTA_CS         0x0003    /* Context stash size */
#define QPORTAL_INITFQ_CTXTA_DS         0x000C    /* Data stash size */
#define QPORTAL_INITFQ_CTXTA_AS         0x0030    /* Annotation stash size */
#define QPORTAL_INITFQ_CTXTA_CE         0x0100    /* Context stash exclusive */
#define QPORTAL_INITFQ_CTXTA_DE         0x0200    /* Data stash exclusive */
#define QPORTAL_INITFQ_CTXTA_AE         0x0400    /* Annotation stash exclusive */

#define QPORTAL_CS_SIZE(x)              ((x) & QPORTAL_INITFQ_CTXTA_CS)
#define QPORTAL_DS_SIZE(x)              (((x) << 2) & QPORTAL_INITFQ_CTXTA_DS)
#define QPORTAL_AS_SIZE(x)              (((x) << 4) & QPORTAL_INITFQ_CTXTA_AS)

/* Initialize frame queue response */

typedef struct qportal_initfq_resp
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRslt;
    volatile UINT16     qportalRsvd0[0];
    volatile UINT32     qportalRsvd1[15];
    } QPORTAL_INITFQ_RESP;


/* Result field */

#define QPORTAL_INITFQ_RSLT_OK          0xF0
#define QPORTAL_INITFQ_RSLT_BADFQID     0xF1
#define QPORTAL_INITFQ_RSLT_BADSTATE    0xF2

/* Query FQ fields */

typedef struct qportal_queryfq
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRsvd0[3];
    volatile UINT32     qportalFqId;
    volatile UINT32     qportalRsvd2[14];
    } QPORTAL_QUERYFQ;

/* Verb field */

#define QPORTAL_QFIELDS_VALID           0x80
#define QPORTAL_QFIELDS_VERB_GETPFLDS   0x44    /* Get programmable fields */
#define QPORTAL_QFIELDS_VERB_GETNPFLDS  0x45    /* Get non-programmable fields */

/* Query FQ programmable fields response */

typedef struct qportal_queryfq_p_resp
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRslt;
    volatile UINT16     qportalRsvd0[4];
    volatile UINT8      qportalOrpc;
    volatile UINT8      qportalCgid;
    volatile UINT16     qportalFqCtrl;
    volatile UINT16     qportalDestWq;
    volatile UINT16     qportalIcsCred;
    volatile UINT16     qportalTdThresh;
    volatile UINT32     qportalCtxtB;
    volatile UINT32     qportalCtxtAHi;
    volatile UINT32     qportalCtxtALo;
    volatile UINT32     qportalRsvd1[8];
    } QPORTAL_QUERYFQ_P_RESP;

/* Query FQ non-programmable fields response */

typedef struct qportal_queryfq_np_resp
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRslt;
    volatile UINT8      qportalRsvd0;
    volatile UINT8      qportalState;
    volatile UINT32     qportalFqdLink;
    volatile UINT16     qportalOdpSeq;
    volatile UINT16     qportalOrpNesn;
    volatile UINT16     qportalOrpEaHseq;
    volatile UINT16     qportalOrpEaTseq;
    volatile UINT32     qportalOrpEaHptr;
    volatile UINT32     qportalOrpEaTptr;
    volatile UINT32     qportalPfdrHptr;
    volatile UINT32     qportalPfdrTptr;
    volatile UINT32     qportalRsvd2;
    volatile UINT8      qportalRsvd3;
    volatile UINT8      qportalIs;
    volatile UINT16     qportalIcsSurp;
    volatile UINT32     qportalByteCnt;
    volatile UINT32     qportalFrmCnt;
    volatile UINT32     qportalRsvd4;
    volatile UINT16     qportalRa1Sfdr;
    volatile UINT16     qportalRa2Sfdr;
    volatile UINT16     qportalRsvd5;
    volatile UINT16     qportalOd1Sfdr;
    volatile UINT16     qportalOd2Sfdr;
    volatile UINT16     qportalOd3Sfdr;
    } QPORTAL_QUERYFQ_NP_RESP;

/* Result field */

#define QPORTAL_QUERYFQ_RSLT_OK         0xF0
#define QPORTAL_QUERYFQ_RSLT_BADFQID    0xF1

/* Alter frame queue commands */

typedef struct qportal_alterfq
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRsvd0[3];
    volatile UINT32     qportalFqId;
    volatile UINT32     qportalRsvd1[3];
    volatile UINT32     qportalCtxtB;
    volatile UINT32     qportalRsvd2[10];
    } QPORTAL_ALTERFQ;

/* Verb field */

#define QPORTAL_ALTERFQ_VERB_VALID      0x80
#define QPORTAL_ALTERFQ_VERB_SCHEDFQ    0x48    /* Schedule frame queue */
#define QPORTAL_ALTERFQ_VERB_FORCEELG   0x49    /* Force queue eligible */
#define QPORTAL_ALTERFQ_VERB_RETIREQ    0x4A    /* Retire frame queue */
#define QPORTAL_ALTERFQ_VERB_OUTOFSVC   0x4B    /* Take queue out of service */
#define QPORTAL_ALTERFQ_VERB_RETIRECTXB 0x4C    /* Retire frame queue, specify context_B */

/* Alter frame queue response */

typedef struct qportal_alterfq_resp
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRslt;
    volatile UINT8      qportalFqs;
    volatile UINT8      qportalRsvd0;
    volatile UINT32     qportalRsvd1[15];
    } QPORTAL_ALTERFQ_RESP;

/* Result field */

#define QPORTAL_ALTERFQ_RSLT_OK         0xF0
#define QPORTAL_ALTERFQ_RSLT_BADFQID    0xF1
#define QPORTAL_ALTERFQ_RSLT_BADSTATE   0xF2
#define QPORTAL_ALTERFQ_RSLT_NOTEMPTY   0xF3
#define QPORTAL_ALTERFQ_RSLT_PENDING    0xF4

/* Frame queue state field */

#define QPORTAL_ALTERFQ_FQS_NOTEMPTY    0x01
#define QPORTAL_ALTERFQ_FQS_ORP_PENDING 0x02

/* Query WQ length */

typedef struct qportal_querywq
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRsvd0;
    volatile UINT16     qportalChan;
    volatile UINT32     qportalRsvd1[15];
    } QPORTAL_QUERYWQ;

/* Verb field */

#define QPORTAL_QUERYWQ_VERB_VALID      0x80
#define QPORTAL_QUERYWQ_VERB_LEN        0x46    /* Get len in a channel */
#define QPORTAL_QUERYWQ_VERB_LEN_DED    0x47    /* Get len dedicated channel */

/* Query WQ response */

typedef struct qportal_querywq_resp
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRslt;
    volatile UINT16     qportalChan;
    volatile UINT32     qportalRsvd0[7];
    volatile UINT32     qportalWq0Len;
    volatile UINT32     qportalWq1Len;
    volatile UINT32     qportalWq2Len;
    volatile UINT32     qportalWq3Len;
    volatile UINT32     qportalWq4Len;
    volatile UINT32     qportalWq5Len;
    volatile UINT32     qportalWq6Len;
    volatile UINT32     qportalWq7Len;
    } QPORTAL_QUERYWQ_RESP;

/* Result field */

#define QPORTAL_QUERYWQ_RSLT_OK         0xF0
#define QPORTAL_QUERYWQ_RSLT_BADCHAN    0xF4
#define QPORTAL_QUERYWQ_RSLT_INVALID    0xFF

/* Initialize/Modify Congestion Group Record */

typedef struct qportal_initmodcgr
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRsvd0;
    volatile UINT16     qportalWeMask;
    volatile UINT32     qportalWrParmG;
    volatile UINT32     qportalWrParmY;
    volatile UINT32     qportalWrParmR;
    volatile UINT8      qportalWrEnG;
    volatile UINT8      qportalWrEnY;
    volatile UINT8      qportalWrEnR;
    volatile UINT8      qportalCscnEn;
    volatile UINT32     qportalCscnTarg;
    volatile UINT8      qportalCstdEn;
    volatile UINT8      qportalRsvd1;
    volatile UINT16     qportalCsThres;
    volatile UINT8      qportalMode;
    volatile UINT8      qportalRsvd2[2];
    volatile UINT8      qportalCgid;
    volatile UINT32     qportalRsvd3[8];
    } QPORTAL_INITMODCGR;

#define QPORTAL_INITMODCGR_VERB_VALID       0x80
#define QPORTAL_INITMODCGR_INIT             0x50
#define QPORTAL_INITMODCGR_MODIFY           0x51

#define QPORTAL_INITMODCGR_WEMASK_MODE      0x0001
#define QPORTAL_INITMODCGR_WEMASK_CSTHRES   0x0002
#define QPORTAL_INITMODCGR_WEMASK_CSTD_EN   0x0004
#define QPORTAL_INITMODCGR_WEMASK_CSCN_TARG 0x0008
#define QPORTAL_INITMODCGR_WEMASK_CSCN_EN   0x0010
#define QPORTAL_INITMODCGR_WEMASK_WRENR     0x0020
#define QPORTAL_INITMODCGR_WEMASK_WRENY     0x0040
#define QPORTAL_INITMODCGR_WEMASK_WRENG     0x0080
#define QPORTAL_INITMODCGR_WEMASK_WRPARMR   0x0100
#define QPORTAL_INITMODCGR_WEMASK_WRPARMY   0x0200
#define QPORTAL_INITMODCGR_WEMASK_WRPARMG   0x0400

/* WRED Green Enable field */

#define QPORTAL_INITMODCGR_WRENG_DISABLE    0x00
#define QPORTAL_INITMODCGR_WRENG_ENABLE     0x01

/* WRED Yellow Enable field */

#define QPORTAL_INITMODCGR_WRENY_DISABLE    0x00
#define QPORTAL_INITMODCGR_WRENY_ENABLE     0x01

/* WRED Red Enable field */

#define QPORTAL_INITMODCGR_WRENR_DISABLE    0x00
#define QPORTAL_INITMODCGR_WRENR_ENABLE     0x01

/* Cong. State Change Notification field */

#define QPORTAL_INITMODCGR_CSCN_DISABLE     0x00
#define QPORTAL_INITMODCGR_CSCN_ENABLE      0x01

/* Cong. State Change Target field */

#define QPORTAL_INITMODCGR_CSCNTARG_PORTAL0 0x80000000
#define QPORTAL_INITMODCGR_CSCNTARG_PORTAL1 0x40000000
#define QPORTAL_INITMODCGR_CSCNTARG_PORTAL2 0x20000000
#define QPORTAL_INITMODCGR_CSCNTARG_PORTAL3 0x10000000
#define QPORTAL_INITMODCGR_CSCNTARG_PORTAL4 0x08000000
#define QPORTAL_INITMODCGR_CSCNTARG_PORTAL5 0x04000000
#define QPORTAL_INITMODCGR_CSCNTARG_PORTAL6 0x02000000
#define QPORTAL_INITMODCGR_CSCNTARG_PORTAL7 0x01000000
#define QPORTAL_INITMODCGR_CSCNTARG_PORTAL8 0x00800000
#define QPORTAL_INITMODCGR_CSCNTARG_PORTAL9 0x00400000
#define QPORTAL_INITMODCGR_CSCNTARG_FMAN0   0x00200000
#define QPORTAL_INITMODCGR_CSCNTARG_FMAN1   0x00100000

#define QPORTAL_INITMODCGR_CSCNTARG_PORTAL(x)   (0x80000000 >> (x))

/* Cong. State Tail Drop field */

#define QPORTAL_INITMODCGR_CSTD_DISABLE     0x00
#define QPORTAL_INITMODCGR_CSTD_ENABLE      0x01

/* Congestion State Threshold field */

#define QPORTAL_INITMODCGR_CSTHRESH_TA      0x1FE0
#define QPORTAL_INITMODCGR_CSTHRESH_TN      0x001F

#define QPORTAL_TN(x)                       ((x) & QPORTAL_INITMODCGR_CSTHRESH_TN)
#define QPORTAL_TA(x)                       (((x) << 5) & QPORTAL_INITMODCGR_CSTHRESH_TA)

/* Mode field bits */

#define QPORTAL_INITMODCGR_MODE_BYTE        0x00
#define QPORTAL_INITMODCGR_MODE_FRAME       0x01

/*
 * Red/Yellow/Green parameter fields
 * The WRED parameters are calculated as follows:
 *
 * MaxTH = MA * (2 ^ Mn)
 * Slope = SA / (2 ^ Mn)
 * MaxP = 4 * (Pn + 1)
 */

#define QPORTAL_INITMODCGR_WRPARM_PN        0x0000003F
#define QPORTAL_INITMODCGR_WRPARM_SN        0x00000FC0
#define QPORTAL_INITMODCGR_WRPARM_SA        0x0007F000 /* Must be 64-127 */
#define QPORTAL_INITMODCGR_WRPARM_MN        0x00F80000 /* Must be 7-63 */
#define QPORTAL_INITMODCGR_WRPARM_MA        0xFF000000

#define QPORTAL_PN(x)        ((x) & QPORTAL_INITMODCGR_WRPARM_PN)
#define QPORTAL_SN(x)        (((x) << 6) & QPORTAL_INITMODCGR_WRPARM_SN)
#define QPORTAL_SA(x)        (((x) << 12) & QPORTAL_INITMODCGR_WRPARM_SA)
#define QPORTAL_MN(x)        (((x) << 19) & QPORTAL_INITMODCGR_WRPARM_MN)
#define QPORTAL_MA(x)        (((x) << 24) & QPORTAL_INITMODCGR_WRPARM_MA)

/* Initialize/Modify Congestion Group Record response */

typedef struct qportal_initmodcgr_resp
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRslt;
    volatile UINT16     qportalRsvd0[0];
    volatile UINT32     qportalRsvd1[15];
    } QPORTAL_INITMODCGR_RESP;

/* Result field */

#define QPORTAL_INITMODCGR_RSLT_OK      0xF0
#define QPORTAL_INITMODCGR_RSLT_ERROR   0xFF

/* Congestion Group Record Test Write */

typedef struct qportal_cgrtest
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRsvd0[2];
    volatile UINT8      qportalIbcntHi;
    volatile UINT32     qportalIbcntLo;
    volatile UINT32     qportalRsvd1[14];
    } QPORTAL_CGRTEST;

#define QPORTAL_CGRTEST_VERB_VALID      0x80
#define QPORTAL_CGRTEST_WRITE           0x52

/* Congestion Group Record Test Write response */

typedef struct qportal_cgrtest_resp
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRsvd0;
    volatile UINT16     qportalRsvd1;
    volatile UINT32     qportalWrParmG;
    volatile UINT32     qportalWrParmY;
    volatile UINT32     qportalWrParmR;
    volatile UINT8      qportalWrEnG;
    volatile UINT8      qportalWrEnY;
    volatile UINT8      qportalWrEnR;
    volatile UINT8      qportalCscnEn;
    volatile UINT32     qportalCscnTarg;
    volatile UINT8      qportalCstdEn;
    volatile UINT8      qportalCs;
    volatile UINT16     qportalCsThres;
    volatile UINT8      qportalMode;
    volatile UINT8      qportalRsvd2[6];
    volatile UINT8      qportalIbcntHi;
    volatile UINT32     qportalIbcntLo;
    volatile UINT8      qportalRsvd3[3];
    volatile UINT8      qportalAbcntHi;
    volatile UINT32     qportalAbcntLo;
    volatile UINT16     qportalTimestamp;
    volatile UINT16     qportalProbG;
    volatile UINT16     qportalProbY;
    volatile UINT16     qportalProbR;
    volatile UINT32     qportalRsvd4[2];
    } QPORTAL_CGRTEST_RESP;

/* Result field */

#define QPORTAL_CGRTEST_RSLT_OK         0xF0
#define QPORTAL_CGRTEST_RSLT_ERROR      0xFF

/* Query Congestion Group Record */

typedef struct qportal_querycgr
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRsvd0[3];
    volatile UINT32     qportalRsvd1[6];
    volatile UINT8      qportalRsvd2[3];
    volatile UINT8      qportalCgid;
    volatile UINT32     qportalRsvd3[8];
    } QPORTAL_QUERYCGR;

#define QPORTAL_QUERYCGR_VERB_VALID     0x80
#define QPORTAL_QUERYCGR_VERB           0x58

/* Query CGR response */

typedef struct qportal_querycgr_resp
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRslt;
    volatile UINT16     qportalRsvd0;
    volatile UINT32     qportalWrParmG;
    volatile UINT32     qportalWrParmY;
    volatile UINT32     qportalWrParmR;
    volatile UINT8      qportalWrEnG;
    volatile UINT8      qportalWrEnY;
    volatile UINT8      qportalWrEnR;
    volatile UINT8      qportalCscnEn;
    volatile UINT32     qportalCscnTarg;
    volatile UINT8      qportalCstdEn;
    volatile UINT8      qportalCs;
    volatile UINT16     qportalCsThres;
    volatile UINT8      qportalMode;
    volatile UINT8      qportalRsvd1[6];
    volatile UINT8      qportalIbcntHi;
    volatile UINT32     qportalIbcntLo;
    volatile UINT8      qportalRsvd2[3];
    volatile UINT8      qportalAbcntHi;
    volatile UINT32     qportalAbcntLo;
    volatile UINT32     qportalRsvd3[4];
    } QPORTAL_QUERYCGR_RESP;

/* Result field */

#define QPORTAL_QUERYCGR_RSLT_OK        0xF0
#define QPORTAL_QUERYCGR_RSLT_ERROR     0xFF

/* Query congestion state */

typedef struct qportal_querycstate
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRsvd0[3];
    volatile UINT8      qportalRsvd1[15];
    } QPORTAL_QUERYCSTATE;

#define QPORTAL_QUERYCSTATE_VERB_VALID  0x80
#define QPORTAL_QUERYCSTATE_VERB        0x59

/* Query congestion state response */

typedef struct qportal_querycstate_resp
    {
    volatile UINT8      qportalVerb;
    volatile UINT8      qportalRslt;
    volatile UINT16     qportalRsvd0;
    volatile UINT32     qportalRsvd1[7];
    volatile UINT8      qportalCgs[32];
    } QPORTAL_QUERYCSTATE_RESP;

/* Result field */

#define QPORTAL_QUERYCSTATE_RSLT_OK     0xF0
#define QPORTAL_QUERYCSTATE_RSLT_ERROR  0xFF

/* Cache inhibited area */
    
#if CPU_FAMILY==PPC
#define QPORTAL_CI_0                    0x00000000
#define QPORTAL_CI_1                    0x00001000
#define QPORTAL_CI_2                    0x00002000
#define QPORTAL_CI_3                    0x00003000
#define QPORTAL_CI_4                    0x00004000
#define QPORTAL_CI_5                    0x00005000
#define QPORTAL_CI_6                    0x00006000
#define QPORTAL_CI_7                    0x00007000
#define QPORTAL_CI_8                    0x00008000
#define QPORTAL_CI_9                    0x00009000
#endif /* CPU_FAMILY==PPC */
    
#if CPU_FAMILY==ARM
#define QPORTAL_CI_0                    0x00000000
#define QPORTAL_CI_1                    0x00010000
#define QPORTAL_CI_2                    0x00020000
#define QPORTAL_CI_3                    0x00030000
#define QPORTAL_CI_4                    0x00040000
#define QPORTAL_CI_5                    0x00050000
#define QPORTAL_CI_6                    0x00060000
#define QPORTAL_CI_7                    0x00070000
#define QPORTAL_CI_8                    0x00080000
#define QPORTAL_CI_9                    0x00090000
#endif /* CPU_FAMILY==ARM */

#define QPORTAL_CI_IDX(x, y)            ((y) + (QPORTAL_CI_1 * (x)))

#define QPORTAL_CI_OFFSET               0x00100000

/* For Revision 3 Qman, the CI offset is 16MB, not 1MB */

#define QPORTAL_V3CI_OFFSET             0x01000000

#if CPU_FAMILY==PPC
#define QPORTAL_CI_EQ_PRODIDX           0x00000000 /* Enqueue producer idx */
#define QPORTAL_CI_EQ_CONSIDX           0x00000004 /* Enqueue consumer idx */
#define QPORTAL_CI_EQ_ITR               0x00000008 /* Enqueue intr thresh */
#define QPORTAL_CI_DQ_PRODIDX           0x00000040 /* Dequeue producer idx */
#define QPORTAL_CI_DQ_CONSIDX           0x00000044 /* Dequeue consumer idx */
#define QPORTAL_CI_DQ_ITR               0x00000048 /* Dequeue intr thresh */
#define QPORTAL_CI_DQ_DCAP              0x00000050 /* Discrete cons ack */
#define QPORTAL_CI_DQ_SDQCR             0x00000054 /* Static dequeue cmd */
#define QPORTAL_CI_DQ_VDQCR             0x00000058 /* Volatile dequeue cmd */
#define QPORTAL_CI_DQ_PDQCR             0x0000005C /* Pull dequeue cmd */
#define QPORTAL_CI_MR_PRODIDX           0x00000080 /* Msg ring prod idx */
#define QPORTAL_CI_MR_CONSIDX           0x00000084 /* Msg ring cons idx */
#define QPORTAL_CI_MR_ITR               0x00000088 /* Msg ring intr thresh */
#define QPORTAL_CI_CFG                  0x00000100 /* Configuration */
#define QPORTAL_CI_ISR                  0x00000E00 /* Interrupt status */
#define QPORTAL_CI_IER                  0x00000E04 /* Interrupt enable */
#define QPORTAL_CI_ISDR                 0x00000E08 /* Intr sts disable */
#define QPORTAL_CI_IIR                  0x00000E0C /* Intr inhibit reg */
#define QPORTAL_CI_ITPR                 0x00000E14 /* Intr timeout period */
#endif /* CPU_FAMILY==PPC */
    
#if CPU_FAMILY==ARM
#define QPORTAL_CI_EQ_PRODIDX           0x00003000 /* Enqueue producer idx */
#define QPORTAL_CI_EQ_CONSIDX           0x00003040 /* Enqueue consumer idx */
#define QPORTAL_CI_EQ_ITR               0x00003080 /* Enqueue intr thresh */
#define QPORTAL_CI_DQ_PRODIDX           0x00003100 /* Dequeue producer idx */
#define QPORTAL_CI_DQ_CONSIDX           0x00003140 /* Dequeue consumer idx */
#define QPORTAL_CI_DQ_ITR               0x00003180 /* Dequeue intr thresh */
#define QPORTAL_CI_DQ_DCAP              0x000031C0 /* Discrete cons ack */
#define QPORTAL_CI_DQ_SDQCR             0x00003200 /* Static dequeue cmd */
#define QPORTAL_CI_DQ_VDQCR             0x00003240 /* Volatile dequeue cmd */
#define QPORTAL_CI_DQ_PDQCR             0x00003280 /* Pull dequeue cmd */
#define QPORTAL_CI_MR_PRODIDX           0x00003300 /* Msg ring prod idx */
#define QPORTAL_CI_MR_CONSIDX           0x00003340 /* Msg ring cons idx */
#define QPORTAL_CI_MR_ITR               0x00003380 /* Msg ring intr thresh */
#define QPORTAL_CI_CFG                  0x00003500 /* Configuration */
#define QPORTAL_CI_ISR                  0x00003600 /* Interrupt status */
#define QPORTAL_CI_IER                  0x00003640 /* Interrupt enable */
#define QPORTAL_CI_ISDR                 0x00003680 /* Intr sts disable */
#define QPORTAL_CI_IIR                  0x000036C0 /* Intr inhibit reg */
#define QPORTAL_CI_ITPR                 0x00003740 /* Intr timeout period */
#endif /* CPU_FAMILY==ARM */

/* Static dequeue command register */

#define QPORTAL_CI_SDQCR_DQSRC          0x0000FFFF /* Dequeue source */
#define QPORTAL_CI_SDQCR_TOK            0x00FF0000 /* Token */
#define QPORTAL_CI_SDQCR_DCT            0x03000000 /* Dequeue command type */
#define QPORTAL_CI_SDQCR_DP             0x10000000 /* Ded chan preference */
#define QPORTAL_CI_SDQCR_FC             0x20000000 /* Frame count */
#define QPORTAL_CI_SDQCR_SS             0x40000000 /* Source select */

/* Dedicated channel sources */

#define QPORTAL_CI_SDQCR_DQSRC_DED      0x00008000
#define QPORTAL_CI_SDQCR_DQSRC_POOL1    0x00004000
#define QPORTAL_CI_SDQCR_DQSRC_POOL2    0x00002000
#define QPORTAL_CI_SDQCR_DQSRC_POOL3    0x00001000
#define QPORTAL_CI_SDQCR_DQSRC_POOL4    0x00000800
#define QPORTAL_CI_SDQCR_DQSRC_POOL5    0x00000400
#define QPORTAL_CI_SDQCR_DQSRC_POOL6    0x00000200
#define QPORTAL_CI_SDQCR_DQSRC_POOL7    0x00000100
#define QPORTAL_CI_SDQCR_DQSRC_POOL8    0x00000080
#define QPORTAL_CI_SDQCR_DQSRC_POOL9    0x00000040
#define QPORTAL_CI_SDQCR_DQSRC_POOL10   0x00000020
#define QPORTAL_CI_SDQCR_DQSRC_POOL11   0x00000010
#define QPORTAL_CI_SDQCR_DQSRC_POOL12   0x00000008
#define QPORTAL_CI_SDQCR_DQSRC_POOL13   0x00000004
#define QPORTAL_CI_SDQCR_DQSRC_POOL14   0x00000002
#define QPORTAL_CI_SDQCR_DQSRC_POOL15   0x00000001

/* Source select bit */

#define QPORTAL_SDQCR_SS_CHAN           0x00000000
#define QPORTAL_SDQCR_SS_WQ             0x40000000

/* Frame count bit */

#define QPORTAL_SDQCR_FC_ONE            0x00000000 /* Exactly one */
#define QPORTAL_SDQCR_FC_THREE          0x20000000 /* Up to three */

/* Dedicated channel preference bit */

#define QPORTAL_SDQCR_DP_NOPRED         0x00000000 /* pool pred = ded. pred */
#define QPORTAL_SDQCR_DP_PRED           0x10000000 /* ded. pred > pool pred */

/* Dequeue command type */

#define QPORTAL_SDQCR_DCT_NULL          0x00000000
#define QPORTAL_SDQCR_DCT_PRIO_QOS      0x01000000
#define QPORTAL_SDQCR_DCT_ACT_QOS       0x02000000
#define QPORTAL_SDQCR_DCT_ACT           0x03000000

#define QPORTAL_SDQCR_TOKEN(x)          (((x) << 16) & QPORTAL_CI_SDQCR_TOK)

#define QPORTAL_SDQCR_SOURCE(x)         ((x) & QPORTAL_CI_SDQCR_DQSRC)

/* Volatile Dequeue Command Register */

#define QPORTAL_CI_VDQCR_FQID           0x00FFFFFF
#define QPORTAL_CI_VDQCR_NUMFRAMES      0x3F000000
#define QPORTAL_CI_VDQCR_EXACT          0x40000000
#define QPORTAL_CI_VDQCR_PRECEDENCE     0x80000000

#define QPORTAL_VDQCR_FRAMES(x)         (((x) << 24) & QPORTAL_CI_VDQCR_NUMFRAMES)
#define QPORTAL_VDQCR_FQID(x)           ((x) & QPORTAL_CI_VDQCR_FQID)

/* Pull Dequeue Command Register */

#define QPORTAL_CI_PDQCR_DQSRC          0x00FFFFFF
#define QPORTAL_CI_PDQCR_DCT            0x03000000
#define QPORTAL_CI_PDQCR_DP             0x10000000 /* Ded chan preference */
#define QPORTAL_CI_PDQCR_FC             0x20000000 /* Frame count */
#define QPORTAL_CI_PDQCR_SS             0x40000000 /* Source select */
#define QPORTAL_CI_PDQCR_SU             0x80000000 /* scheduled/unscheduled */

#define QPORTAL_PDQCR_DCT_NULL          0x00000000
#define QPORTAL_PDQCR_DCT_PRIO_QOS      0x01000000
#define QPORTAL_PDQCR_DCT_ACT_QOS       0x02000000
#define QPORTAL_PDQCR_DCT_ACT           0x03000000

#define QPORTAL_PDQCR_SOURCE(x)         ((x) & QPORTAL_CI_PDQCR_DQSRC)

/* Portal configuration register */

#define QPORTAL_CI_CFG_SDEST            0x00000007 /* Stashing destination */
#define QPORTAL_CI_CFG_SP               0x00000010 /* Data stash priority */
#define QPORTAL_CI_CFG_SE               0x00000020 /* Data stash enable */
#define QPORTAL_CI_CFG_RP               0x00000040 /* DQRR stash priority */
#define QPORTAL_CI_CFG_RE               0x00000080 /* DQRR stash enable */
#define QPORTAL_CI_CFG_MM               0x00000100 /* Msg Consumption mode */
#define QPORTAL_CI_CFG_DCM              0x00030000 /* DQRR consumption mode */
#define QPORTAL_CI_CFG_DP               0x00040000 /* DQRR push/pull mode */
#define QPORTAL_CI_CFG_DQRR_MF          0x00F00000 /* DQRR max fill */
#define QPORTAL_CI_CFG_EPM              0x03000000 /* EQCR production mode */

#define QPORTAL_EPM_PICI                0x00000000 /* PI write, uncached */
#define QPORTAL_EPM_PICE                0x01000000 /* PI write, cached */
#define QPORTAL_EPM_VBIT                0x02000000 /* Valid bit mode */

#define QPORTAL_DQRRMF(x)               (((x) << 20) & QPORTAL_CI_CFG_DQRR_MF)

#define QPORTAL_DP_PUSH                 0x00000000
#define QPORTAL_DP_PULL                 QPORTAL_CI_CFG_DP

#define QPORTAL_DCM_CICI                0x00000000 /* CI write, uncached */
#define QPORTAL_DCM_CICE                0x00010000 /* CI write, cached */
#define QPORTAL_DCM_DCA                 0x00020000 /* discrete acknowledge */

#define QPORTAL_MM_CICI                 0x00000000 /* CI write uncached */
#define QPORTAL_MM_CICE                 QPORTAL_CI_CFG_MM /* CI write uncached */

/* Interrupt status register */

#define QPORTAL_CI_ISR_CSCI             0x00100000 /* Cong. state chng */
#define QPORTAL_CI_ISR_EQCI             0x00080000 /* Enqueue cmd disp. */
#define QPORTAL_CI_ISR_EQRI             0x00040000 /* Enqueue ring */
#define QPORTAL_CI_ISR_DQRI             0x00020000 /* Dequeue ring */
#define QPORTAL_CI_ISR_MRI              0x00010000 /* Message ring */
#define QPORTAL_CI_ISR_DQAVAIL          0x0000FFFF /* work avail */

#define QPORTAL_CI_DQAVAIL_PORTAL       0x00008000
#define QPORTAL_CI_DQAVAIL_POOL(x)      (0x8000 >> (x))

/*
 * For Revision 1 Qman, there can be as many as 10 software portals.
 * For Revision 2 Qman (T4240), there can be 50. Later revs may have
 * even more.
 */

#define QPORTAL_PORTAL_CNT              50

/*
 * The enqueue and message rings in a portal have 8 slots.
 * The dequeue ring has 16.
 */

#define QPORTAL_QUEUE_CNT               8
#define QPORTAL_DQ_QUEUE_CNT            16

/*
 * Enqueue indexes:
 * Only the lower 4 bits of all the produces/consumer indexes are valid.
 * The lower 3 bits represent the actual index value. The 4th bit is
 * the valid polarity bit that the qmanager is expecting to be written
 * upon the next update by host software. This bit toggles when the index
 * wraps from 7 back to 0.
 * De
 */

#define QPORTAL_IDX(x)                  ((x) & 0x7)
#define QPORTAL_DQ_IDX(x)               ((x) & 0xF)
#define QPORTAL_IDX_VP                  0x8
#define QPORTAL_DQ_IDX_VP               0x10

#define PORTAL_TIMEOUT                  10000

typedef void (*qportalIntFunc)(void *);
typedef void (*qportalCallout)(void *, QPORTAL_FDESC *, UINT32, UINT32);
typedef void (*qportalMrCallout)(void *, UINT8, QPORTAL_FDESC *, UINT32, UINT32);

#include <lstLib.h>
#include <semLib.h>
#include <vxAtomicLib.h>
#include <jobQueueLib.h>

typedef struct qportalIntList
    {
    qportalCallout      qInt_func;
    qportalMrCallout    qInt_mrfunc;
    void *              qInt_ctx;
    UINT32              qInt_fqId;
    UINT32              qInt_ctxB;
    } QPORTAL_INTLIST;

/* interrupt handling types */

#define QPORTAL_INTHANDLE_DEQUEUE    0x00000001
#define QPORTAL_INTHANDLE_MESSAGE    0x00000002

#define QPORTAL_CALLOUT_CNT         512

#define QPORTAL_ORP_DISCARD         0x00000001
#define QPORTAL_ORP_NESN            0x00000002
#define QPORTAL_ORP_NOTLAST         0x00000004

/* portal configuration flags */

#define QPORTAL_SET_DCA             1
#define QPORTAL_SET_CICE            2

typedef struct qportal
    {
    volatile void *             qportalCeBase;
    volatile void *             qportalCiBase;
    volatile QPORTAL_ENQUEUE *  qportalEqcr;      /* Enqueue command ring */
    volatile QPORTAL_DEQUEUE *  qportalDqrr;      /* Dequeue response ring */
    volatile QPORTAL_ERN *      qportalMr;        /* Message ring */
    volatile UINT32 *           qportalEqProdIdx; /* Enqueue producer idx */
    volatile UINT32 *           qportalEqConsIdx; /* Enqueue consumer idx */
    volatile UINT32 *           qportalDqProdIdx; /* Dequeue producer idx */
    volatile UINT32 *           qportalDqConsIdx; /* Dequeue consumer idx */
    volatile UINT32 *           qportalMrProdIdx; /* Msg ring producer idx */
    volatile UINT32 *           qportalMrConsIdx; /* Msg ring consumer idx */
    volatile void *             qportalRoIdx;     /* Combined RO idxes */
    volatile void *             qportalMcr;       /* Management cmd reg */
    volatile void *             qportalMrr0;      /* Management resp reg 0 */
    volatile void *             qportalMrr1;      /* Management resp reg 0 */
    volatile void *             qportalMrrCur;    /* Management resp current */
    VXB_DEV_ID                  qportalDev;       /* Owner */
    UINT8                       qportalMcPol;     /* Management polarity */
    UINT8                       qportalEqVbit;    /* Enqueue polarity */
    UINT8                       qportalDqVbit;    /* Dequeue polarity */
    UINT8                       qportalMrVbit;    /* Message ring polarity */
    int                         qportalIntCtx;
    int                         qportalEnqueueProdIdx;
    int                         qportalEnqueueConsIdx;
    int                         qportalEnqueueAvail;
    int                         qportalDequeueIdx;
    int                         qportalMessageIdx;
    int                         qportalRefcnt;
    int                         qportalIdx;
    SEM_ID                      qportalSem;
    QPORTAL_INTLIST *           qportalIntList[QPORTAL_CALLOUT_CNT];
    SEM_ID                      qportalListLock;
    JOB_QUEUE_ID                qportalJobQueue;
    QJOB                        qportalIntJob;
    atomic32_t                  qportalIntPending;
    BOOL                        qportalIntHandling;
    UINT32                      qportalIntMask;
    BOOL                        qportalDca;
    BOOL                        qportalUsed;
    VXB_RESOURCE *              intRes;
    } QPORTAL;

typedef JOB_QUEUE_ID (*QPORTAL_IDX_TO_JOB_Q_ID_FUNC) (unsigned portal_ix);

#define QPORTAL_INC(x, y)               (x) = ((x + 1) & (y - 1))

#define QPORTAL_CI_READ_4(p, addr)        qportalCiRead4(p, addr)
#define QPORTAL_CI_WRITE_4(p, addr, data) qportalCiWrite4(p, addr, data)

IMPORT STATUS qportalEnqueue (QPORTAL *, UINT32, UINT32, QPORTAL_FDESC *);
IMPORT STATUS qportalSafeEnqueue (QPORTAL *, UINT32, UINT32, QPORTAL_FDESC *);
IMPORT STATUS qportalLocalEnqueue (UINT32, UINT32, QPORTAL_FDESC *);

IMPORT STATUS qportalDequeue (QPORTAL *, UINT32 *, UINT32 *, QPORTAL_FDESC *);
IMPORT STATUS qportalSafeDequeue (QPORTAL *, UINT32 *, UINT32 *,
    QPORTAL_FDESC *);
IMPORT STATUS qportalLocalDequeue (UINT32 *, UINT32 *, QPORTAL_FDESC *);

IMPORT STATUS qportalOrpMrDequeue (QPORTAL *, UINT32 *, UINT8 *, UINT32 *,
    UINT32 *, UINT16 *, QPORTAL_FDESC *);
IMPORT STATUS qportalMrDequeue (QPORTAL *, UINT32 *, UINT8 *, UINT32 *,
    QPORTAL_FDESC *);
IMPORT STATUS qportalSafeMrDequeue (QPORTAL *, UINT32 *, UINT8 *,
    UINT32 *, QPORTAL_FDESC *);
IMPORT STATUS qportalLocalMrDequeue (UINT32 *, UINT8 *, UINT32 *,
    QPORTAL_FDESC *);

IMPORT STATUS qportalOrpEnqueue (QPORTAL *, UINT32, UINT32, UINT32,
    UINT16, UINT32, QPORTAL_FDESC *);
IMPORT STATUS qportalOrpSafeEnqueue (QPORTAL *, UINT32, UINT32,
    UINT32, UINT16, UINT32, QPORTAL_FDESC *);
IMPORT STATUS qportalOrpLocalEnqueue (UINT32, UINT32, UINT32,
    UINT16, UINT32, QPORTAL_FDESC *);

IMPORT STATUS qportalOrpDequeue (QPORTAL *, UINT32 *, UINT32 *,
    UINT16 *, QPORTAL_FDESC *);
IMPORT STATUS qportalOrpSafeDequeue (QPORTAL *, UINT32 *, UINT32 *,
    UINT16 *, QPORTAL_FDESC *);
IMPORT STATUS qportalOrpLocalDequeue (UINT32 *, UINT32 *, UINT16 *,
    QPORTAL_FDESC *);

IMPORT STATUS qportalFullDequeue (QPORTAL *, UINT32 *, UINT32 *, UINT16 *,
    UINT16 *, UINT8 *, UINT8 *, UINT8 *, QPORTAL_FDESC *);
IMPORT STATUS qportalFullEnqueue (QPORTAL *, UINT32, UINT32, UINT32,
    UINT16, UINT32, int, UINT8, QPORTAL_FDESC *);

IMPORT UINT16 qportalFqTdCalc (UINT32);
IMPORT STATUS qportalFqQuery (QPORTAL *, UINT32, QPORTAL_QUERYFQ_P_RESP *);
IMPORT STATUS qportalFqNpQuery (QPORTAL *, UINT32, QPORTAL_QUERYFQ_NP_RESP *);
IMPORT STATUS qportalFqInit (QPORTAL *, UINT32, int, int, UINT32, UINT32, UINT32, UINT16);
IMPORT STATUS qportalFqFullInit (QPORTAL *, UINT32, int, int, UINT32, UINT32,
    UINT32, UINT16, UINT16, int, UINT16);
IMPORT STATUS qportalFqShutdown (QPORTAL *, UINT32);

IMPORT STATUS qportalCgInit (QPORTAL *, UINT8, UINT32, UINT32, UINT32, UINT32,
    UINT16, BOOL, BOOL);
IMPORT STATUS qportalCgModify (QPORTAL *, UINT8, UINT32, UINT32, UINT32, UINT32,
    UINT16, BOOL, BOOL);
IMPORT STATUS qportalCgTestWrite (QPORTAL *, UINT64, QPORTAL_CGRTEST_RESP *);
IMPORT STATUS qportalCgQuery (QPORTAL *, UINT8, QPORTAL_QUERYCGR_RESP *);
IMPORT STATUS qportalCStateQuery (QPORTAL *, QPORTAL_QUERYCSTATE_RESP *);

IMPORT STATUS qportalCreate (VXB_DEV_ID, int);
IMPORT STATUS qportalDestroy (VXB_DEV_ID, int);
IMPORT STATUS qportalAcquire (int, QPORTAL **);
IMPORT STATUS qportalRelease (int, QPORTAL *);
IMPORT STATUS qportalSet (QPORTAL *, UINT32, void *);
IMPORT STATUS qportalIntConnect (QPORTAL *, qportalIntFunc, void *);
IMPORT STATUS qportalIntDisconnect (QPORTAL *, qportalIntFunc, void *);
IMPORT STATUS qportalIntEnable (QPORTAL *, qportalIntFunc, void *);
IMPORT STATUS qportalIntDisable (QPORTAL *, qportalIntFunc, void *);
IMPORT STATUS qportalDequeueSourceSelect (QPORTAL *, UINT16, int, int);

IMPORT STATUS qportalMrCalloutAdd (QPORTAL *, qportalMrCallout, void *, UINT32, UINT32 *);
IMPORT STATUS qportalCalloutAdd (QPORTAL *, qportalCallout, void *, UINT32, UINT32 *);
IMPORT STATUS qportalMrCalloutDelete (QPORTAL *, qportalMrCallout, void *, UINT32, UINT32);
IMPORT STATUS qportalCalloutDelete (QPORTAL *, qportalCallout, void *, UINT32, UINT32);
IMPORT STATUS qportalIntHandlingEnable (QPORTAL *);
IMPORT STATUS qportalIntHandlingDisable (QPORTAL *);
IMPORT STATUS qportalIntHandlingSelect (QPORTAL *, UINT32);

IMPORT UINT32 qportalCiRead4 (QPORTAL * pDrvCtrl, UINT32 addr);
IMPORT void   qportalCiWrite4 (QPORTAL * pDrvCtrl, UINT32 addr, UINT32 data);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbQorIQQmanPortalh */
