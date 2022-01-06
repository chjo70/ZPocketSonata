/* hEnd.h - The Hierarchical END Driver generic reusable System Level */

/*
 * Copyright (c) 1996-2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16apr08,h_k  added handle field in HEND_DRV_CTRL.
12dec06,wap  Add jumbo frame support
09sep06,kch  Added stdlib.h and string.h include statements.
17jan06,pmr  remove pollDone flag.
05jan06,wap  Add include of vxBusLib.h
18nov05,mdo  add VXB prefix
26sep05,dlk  Remove cacheFlush/cacheInvalidate declarations.
29jul05,rcs  initial checkin of file 
08aug05,rcs  fix for itn8frz11
*/


#ifndef __INChEndh
#define __INChEndh

/* includes */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include <net/ethernet.h>
#include <etherLib.h>
#include <end.h>
#include <netBufLib.h> 
#include <miiLib.h>
#include <jobQueueLib.h>
#include <hwif/vxBus.h>
#include <hwif/util/vxbDmaBufLib.h>

#ifndef HENDABBREVIATIONS
#define HENDABBREVIATIONS



#if 0
#ifdef  _ASMLANGUAGE
#define CAST(x)
#else /* _ASMLANGUAGE */
typedef volatile UCHAR VCHAR;   /* shorthand for volatile UCHAR */
typedef volatile INT32 VINT32; /* volatile unsigned word */
typedef volatile INT16 VINT16; /* volatile unsigned halfword */
typedef volatile INT8 VINT8;   /* volatile unsigned byte */
typedef volatile UINT32 VUINT32; /* volatile unsigned word */
typedef volatile UINT16 VUINT16; /* volatile unsigned halfword */
typedef volatile UINT8 VUINT8;   /* volatile unsigned byte */
#define CAST(x) (x)
#endif  /* _ASMLANGUAGE */
#endif
#endif /* HENDABBREVIATIONS */

/* enum declarations for argument passing */
enum hEndParams{HEND_PARAMS,        /* Device base address */
                HEND_RX_Q_PARAM,    /* Parameter holds an HEND_RX_QUEUE_PARAM pointer */
                HEND_TX_Q_PARAM};   /* Parameter holds an HEND_TX_QUEUE_PARAM pointer */

enum HEND_STATUS {HEND_NONE,    /* No work to be done */ 
                  HEND_CURRENT, /* This queue has highest priority work to be done */ 
                  HEND_HIGHER,  /* A higher priority queue has work to do */ 
                  HEND_LOWER};  /* Current queue has no work to do, but lower priority queue does */


enum STORAGE_TYPE {HEND_VALUE,
                   HEND_LVALUE,
                   HEND_VOID_PTR};

/* hEnd memory attributes */
#define HEND_DRV_MEM_ALLOC  0x0001
#define HEND_USR_MEM_ALLOC  0x0002
#define HEND_CACHABLE       0x0010
#define HEND_NON_CACHABLE   0x0020
#define HEND_FREEABLE       0x0040
#define HEND_NON_FREEABLE   0x0080


#define HEND_NET_POOL_INIT 0xfdcbbcdf

#define HEND_QUEUE_DISABLE       -1


typedef struct hend_inst_id
    {
    char name[20];
    int  unit; 
    } HEND_INST_ID;

typedef struct hend_inst_search
    {
    HEND_INST_ID * pHEndInstId;
    int counter;
    int count;
    } HEND_INST_SEARCH;

typedef struct ether_addr ENET_ADDR;


typedef struct hend_rx_queue_param
    {
    JOB_QUEUE_ID    jobQueId;    
    int             priority;           /* Priority relative to other rx queues */
    UINT16          rbdNum;             /* number of RX bd's */
    UINT16          rbdTupleRatio;      /* The ration of rbds to tuples for this queue */
    UINT32          rxBufSize;          /* MTU size */
    char *          pBufMemBase;        /* Externally allocated memory for queue's pool */
    UINT32          rxBufMemSize;       /* Amount of externally allocated pool memory */
    UINT16          rxBufMemAttributes;
    FUNCPTR         rxBufMemFreeMethod; /* method to free externally allocated memory */
    void *          pRxBdBase;          /* Externally allocated memory for queue's descriptors */
    UINT32          rxBdMemSize;        /* Amount of externally allocated pool memory */
    UINT16          rxBdMemAttributes;
    FUNCPTR         rxBdMemFreeMethod;  /* method to free externally allocated memory */
    } HEND_RX_QUEUE_PARAM;




typedef struct hend_tx_queue_param
    {
    JOB_QUEUE_ID    jobQueId;       /* scheduler to use for clean routine */   
    int             priority;       /* Priority relative to other tx queues */
    UINT16          tbdNum;         /* number of TX bd's */
    UINT16          allowedFrags;   /* number of fragment allowed before Coalescing */
    void *          pTxBdBase;        /* Externally allocated memory for queue's descriptors */
    UINT32          txBdMemSize;      /* Amount of externally allocated pool memory */
    UINT16          txBdMemAttributes;
    FUNCPTR         txBdMemFreeMethod;  /* method to free externally allocated memory */
    } HEND_TX_QUEUE_PARAM;   

typedef struct hend_queue_node
    {
    SL_NODE	node;
    HEND_RX_QUEUE_PARAM * pRxParam;
    HEND_TX_QUEUE_PARAM * pTxParam;
    } HEND_QUEUE_NODE;

typedef struct hend_inst_rec
    {
    SL_LIST * pList;
    int       unit;
    } HEND_INST_REC;

typedef  union  hend_param
    {    
    UINT32  value;
    UINT64  lvalue;
    void *  pValue;
    } HEND_PARAM;

typedef struct param_container
   {
   SL_NODE      node;
   UINT32       paramType;
   UINT32       paramLength;
   HEND_PARAM   param;
   } PARAM_CONTAINER;


typedef struct hend_param_vessel
    {
    char               pName[20];
    int                unit;
    PARAM_CONTAINER *  pParam;
    } HEND_PARAM_VESSEL;

typedef struct hend_event_record
    {
    QJOB            job;
    JOB_QUEUE_ID    jobQueId;
    BOOL            interLock;
    int             index;
    } HEND_EVENT_REC;

typedef struct hend_isr_record
    {
    UINT32      handle;
    VOIDFUNCPTR isr;
    }HEND_ISR_REC;

typedef struct hend_rx_control
    {
    char *       type;        /* union type "rx", "tx", "error" */
    UINT32       rbdIndex;    /* ring index */
    UINT16       rbdNum;      /* number of RX bd's */
    M_BLK_ID *   pMblkList;   /* associated tuples */
    UINT32       rbdMask;     /* mask to wrap index around the ring */ 
    NET_POOL_ID  pNetPool;    /* net pool for this ring */ 
    UINT16       rbdTupleRatio;
    UINT32       rxBufSize;   /* The size of MTU */
    UINT32       initType; 
    char *       pBufMemBase; /* pointer to externally allocated net pool base */
    UINT32       rxBufMemSize;
    UINT16       rxBufMemAttributes;
    FUNCPTR      rxBufMemFreeMethod; /* method to free externally allocated memory */
    char *       pRxBdBase;     /* pointer to descriptor base */
    char *       pRxBdPhysBase;     /* pointer to descriptor base */
    UINT32       rxBdMemSize;  
    UINT16       rxBdMemAttributes;  
    FUNCPTR      rxBdMemFreeMethod;  /* method to free externally allocated memory */    
    }HEND_RX_CONTROL;


typedef struct hend_tx_control
    {
    char *              type;
    UINT16              tbdNum;
    M_BLK_ID *          pMblkRing;
    volatile UINT32     next;
    UINT32              free;
    UINT32              freeCnt;
    UINT16              allowedFrags;   /* number of fragment allowed before Coalescing */    
    UINT32              capacity;
    void *              pTxBdBase;
    void *              pTxBdPhysBase;
    UINT32              txBdMemSize;      /* Amount of externally allocated pool memory */    
    UINT16              txBdMemAttributes;
    FUNCPTR             txBdMemFreeMethod;  /* method to free externally allocated memory */
    UINT32              tbdMask;
    UINT16              txUnStallThresh; /* tx reclaim threshold */
    UINT16              txStallThresh;   /* tx low water threshold */
    BOOL                txStall;         /* tx handler stalled - no Tbd */    
    }HEND_TX_CONTROL;


typedef union hend_reg_value
    {
    UINT8   v8;
    UINT16  v16;
    UINT32  v32;
    UINT64  v64;
    } HEND_REG_VALUE;
 
typedef struct hend_reg_desc
    {
    char *          name;
    UINT64          offset;
    int             width;
    HEND_REG_VALUE  value;
    } HEND_REG_DESC;

/* The definition of the driver control structure */

typedef struct hend_drv_ctrl
    {
    END_OBJ         endObj;      /* base class */
    UINT32          unit;        /* unit number */
    
    VXB_DEV_ID*     pInst;       /* pointer to instance structure */
    void *          handle;
    VXB_DMA_TAG_ID  vxbDmaBufDescTag;
    UINT            vxbDmaBufFlags; /* flags for controlling vxbDmaAlloc */
    VXB_DMA_MAP_ID  vxbDmaBufDescMap;
    VXB_DMA_TAG_ID  vxbDmaBufParentTag;
    void *          pDevBaseAddr;
    ENET_ADDR       enetAddr;    /* current Ethernet Address */
    BOOL            attached;    /* driver has been attached */
    
    /* receive outer ring control */
    UINT32          pollCnt;     /* polling counter */
    UINT32          pollLoops;   /* polling limit */
    
    /* fair access limit */
    UINT            maxRxFrames; /* max frames to Receive in one job */
    
    int             initType;   /* netPoolInit() or netPoolCreate() */
    NETBUF_CFG *    pNetBufCfg;
    

    volatile    JOB_QUEUE_ID    rxJobQueId;  /* Default RX jobQueueId */
    volatile    JOB_QUEUE_ID    txJobQueId;  /* Default TX jobQueueId */

    /* interrupt interlock flags */
    volatile BOOL   rxJobQued;
    volatile BOOL   tbdFreeQued;
    volatile UINT32 txHandlerQued;
 
    volatile QJOB *          pJob;         /* Current Rx job */
    volatile JOB_QUEUE_ID   jobQueId;     /* Current RX jobQueueId */
 
    BOOL            pollingModeState;        /* Polling or Free running */
   
    UCHAR *         pTxPollBuf;      /* cluster pointer for poll mode */
    M_BLK_ID        pTxPollMblk;
 
    BOOL            txStall;         /* tx handler stalled - no Tbd */
    
    END_IFDRVCONF   endStatsConf;
    END_IFCOUNTERS  endStatsCounters;

    int             maxMtu;
    } HEND_DRV_CTRL;

#ifdef __cplusplus
}
#endif

#endif /* __INChEndh */

