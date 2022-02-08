/* xbd.h - Extended Block Device Header File */

/*
 * Copyright (c) 2004-2007, 2009-2010, 2012-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
15sep17,ghs  clean build warning
19may16,y_f  added disk encryption support (F6718)
06sep15,hma  add S.M.A.R.T support (V7STO-463)
13may15,txu  fix V7STO-358 : wrong include after extern "C"
12mar15,jsp  create accessors for xbd_max_blocks and xbd_max_reqs
21jan14,m_y  remove xbd block cache parameter (US15841)
31dec13,m_y  modify to component the xbd block cache module
06dec13,m_y  re-design the xbd blk cache
19nov13,m_y  add flag to sync the request (WIND00441663)
22oct13,m_y  add function declaration to remove compile warning
16oct13,m_y  disable the debug information
15aug13,m_y  add code to support gpt
30nov12,w_x  add code to support xbd sched policy
04jun10,jxu  LP64: added void to xbdInit prototype as parameter.
29apr10,pad  Moved extern C statement after include statements.
10jul09,lyc  LP64 support
03jul09,hps  check-in for WIND00142042
03may07,pcm  added XBD_GETINFO ioctl (WIND00091025)
12apr06,dee  SPR 119990, WIND00037359 - add cplusplus construct
25aug05,pcm  added XBD_STACK_COMPLETE ioctl and xbdEventInstantiated
12aug05,rfr  Added media changed event
08aug05,rfr  Added XBD_TEST ioctl command
01jul05,rfr  Added XBD_GETBASENAME ioctl() command
24jun05,rfr  Added total block count to struct xbd_geometry
24jun05,rfr  Fixed name collision in XBD_GEOMETRY
23may05,rfr  Added ioctl commands
14apr05,rfr  Added event and category types
25mar05,rfr  Adapting to the new device.h
10feb05,rfr  Changed block_t to sector_t
04feb05,rfr  Added initialization function.
03feb05,pcm  formatting changes
*/

#ifndef __INCxbdh
#define __INCxbdh

/* includes */
#include <vxWorks.h>
#include <lstLib.h>
#include <hashLib.h>
#include <avlLib.h>

#include <drv/manager/device.h>
#include <drv/xbd/bio.h>
#include <drv/xbd/xbdRequestCache.h>
#include <logLib.h>     /* _func_logMsg */

#ifdef __cplusplus
extern "C" {
#endif


extern UINT16 xbdEventCategory;
extern UINT16 xbdEventPrimaryInsert;
extern UINT16 xbdEventRemove;
extern UINT16 xbdEventSecondaryInsert;
extern UINT16 xbdEventSoftInsert;
extern UINT16 xbdEventMediaChanged;
extern UINT16 xbdEventInstantiated;
extern int xbdSchedDebug;

struct xbd;
struct xbd_request;

struct xbd_funcs
    {
    int (*xf_ioctl) (struct xbd * dev, int cmd, void * arg);
    int (*xf_strategy) (struct xbd * dev, struct bio * bio);
    int (*xf_dump) (struct xbd * dev, sector_t pos, void * data, size_t size);
    int (*xf_request) (struct xbd * dev, struct xbd_request * req);
    };

#define XBD_EXT_MAGIC       0xABCDDCBA

#define BIO_SCHED_FIFO      0
#define BIO_SCHED_ELEVATOR  1
#define BIO_SCHED_DIRECT    2
#define BIO_SCHED_SSD       3
#define BIO_SCHED_DEADLINE  4
#define BIO_SCHED_NOOP      5

struct xbd_ext
    {
    int         sched;
    SEM_ID      biomutex;
    SEM_ID      biordy;
    struct bio  **bioqh;
    struct bio  **bioqt;
    void        (*f_biodo) (struct xbd *xbd, struct bio *bio);
    int         (*f_rmvtst) (struct xbd *xbd, struct bio *bio);

    int         biocnt;
    /*
     * below for elevator-sched use, and
     * they are also protected by biomutex
     */
    BOOL        direction;
    sector_t    curpos;
    struct bio  *bioqt1;
    struct bio  *bioqh2;
    };

#define XBD_IOSCHED_FLUSHING (1 << 0)
struct xbd_biosched_class;

typedef struct xbd_request
    {
    HASH_NODE    backMergeNode; /* Used for merge requests */
    HASH_NODE    frontMergeNode;/* Used for merge requests */
    NODE         sortNode;      /* Used for sort the requests */
    NODE         listNode;      /* Used for dispatch requests */
    atomic_t     numBios;       /* Number of bios in this request */
    int          reqPriority;   /* Max priority of bios in this request */
    unsigned     reqStauts;     /* The last finished bio status in this request */
    struct bio * pBioHead;      /* Head of the bios for this request */
    struct bio * pBioTail;      /* Tail of the bios for this request */
    unsigned     reqflags;      /* Flags such as BIO_READ or BIO_WRITE */
    sector_t     reqFirstBlk;   /* First block for this request */
    sector_t     reqNextBlk;    /* Last block for this request */
    sector_t     reqNumBlks;    /* Total # of blocks for this request */
    void *       drvSpecific;   /* Driver privite for this request */
    struct xbd * pXbd;          /* Pointer to our xbd */
    struct xbd_request * pNext; /* Next request in the request chain */
    }XBD_REQUEST, * pXBD_REQUEST;

#define SORT_NODE_TO_XBD_REQUEST(pNode)  \
    (XBD_REQUEST *) ((long) (pNode) - OFFSET (XBD_REQUEST, sortNode))
#define LIST_NODE_TO_XBD_REQUEST(pNode)  \
        (XBD_REQUEST *) ((long) (pNode) - OFFSET (XBD_REQUEST, listNode))
#define BACKMERGE_NODE_TO_XBD_REQUEST(pNode)  \
            (XBD_REQUEST *) ((long) (pNode) - OFFSET (XBD_REQUEST, backMergeNode))
#define FRONTMERGE_NODE_TO_XBD_REQUEST(pNode)  \
                (XBD_REQUEST *) ((long) (pNode) - OFFSET (XBD_REQUEST, frontMergeNode))

typedef struct xbd_sched_request_avl_node
    {
    AVL_NODE    avlNode;       /* Used for sort requests using AVL_TREE */
    LIST        avlList;       /* Links all the requests with same key */
    }XBD_SCHED_REQUEST_AVL_NODE, * pXBD_SCHED_REQUEST_AVL_NODE;

#define XBD_INIT_NODE(next, previous)       \
    {                                       \
    /* .next =   */     next,               \
    /* .previous */     previous            \
    }

typedef struct xbd_biosched_policy
    {
    NODE                node;
    const char *        name; /* Scheduler policy Name */
    int                 id;   /* Scheduler policy ID */
    STATUS              (* attach)(struct xbd * pXbd);
    STATUS              (* detach)(struct xbd * pXbd);
    STATUS              (* bioenq)(struct xbd * pXbd,
                                   struct bio * pBio);
    STATUS              (* reqenq)(struct xbd * pXbd,
                                   pXBD_REQUEST pReq);
    pXBD_REQUEST        (* reqdeq)(struct xbd * pXbd);
    STATUS              (* reqdone)(struct xbd * pXbd,
                                    pXBD_REQUEST pReq);
    pXBD_REQUEST        (* reqget)(struct xbd * pXbd);
    STATUS              (* reqput)(struct xbd * pXbd,
                                   pXBD_REQUEST pReq);
    pXBD_REQUEST        (* reqnext)(struct xbd * pXbd,
                                      pXBD_REQUEST pReq);
    pXBD_REQUEST        (* reqprev)(struct xbd * pXbd,
                                      pXBD_REQUEST pReq);
    void                (* reqmerged)(struct xbd * pXbd,
                                      pXBD_REQUEST pReq1,
                                      pXBD_REQUEST pReq2);
    pXBD_REQUEST        (* frontmerge)(struct xbd * pXbd,
                                      struct bio * pBio);
    pXBD_REQUEST        (* backmerge)(struct xbd * pXbd,
                                      struct bio * pBio);
    pXBD_REQUEST        (* dispatch)(struct xbd * pXbd,
                                     BOOL byForce);
    void                (* show)(struct xbd * pXbd,
                                     int level);
    }XBD_BIOSCHED_POLICY, * pXBD_BIOSCHED_POLICY;

#define NODE_TO_BIOSCHED_POICY(pNode)  \
    (XBD_BIOSCHED_POLICY *) ((long) (pNode) - OFFSET (XBD_BIOSCHED_POLICY, node))

#define XBD_MAX_BIOS_PER_REQ_DEF (256)
#define XBD_MAX_ACTIVE_REQ_DEF   (1)
#define XBD_MAX_BLKS_PER_BIO_DEF (8192)
#define XBD_MAX_BLKS_PER_REQ_DEF (1024 * 4) /* 2MB on 512B devices */
#define XBD_SCHED_SWITCH_FLAG    (1 << 0)
#define XBD_SCHED_SYNC_FLAG      (1 << 1)

typedef struct xbd_biosched_class
    {
    XBD_BIOSCHED_POLICY *   pSchedPolicy;
    void *                  pSchedContext;
    HASH_ID                 reqBackMergeHash;
    HASH_ID                 reqFrontMergeHash;
    AVL_TREE                xbdRequestTree;
    POOL_ID                 avlNodePool;
    SEM_ID                  mutexLock;
    UINT32                  maxBiosPerReq;
    UINT32                  maxBlksPerReq;
    UINT32                  maxBlksPerBio;
    UINT32                  maxActiveReqs;
    atomic_t                activeReqCount;
    atomic_t                pendingReqCount;
    atomic_t                completeReqCount;

    atomicVal_t             maxPendingReqCount;
    atomicVal_t             maxActiveReqCount;
    atomicVal_t             totalEnqReqCount;
    atomicVal_t             totalDeqReqCount;
    atomic_t                totalBackBioMerges;
    atomic_t                totalFrontBioMerges;
    atomic_t                totalReqMerges;
    atomic_t                totalBiosSubmitted;
    UINT32                  schedFlags;
    struct bio *            bioHead;            /* head of bio queue */
    struct bio *            bioTail;            /* tail of bio queue */
    }XBD_BIOSCHED_CLASS, * pXBD_BIOSCHED_CLASS;

STATUS xbdReqSchedComplete
    (
    pXBD_REQUEST pReq
    );
pXBD_REQUEST xbdBioSchedReqDeq
    (
    struct xbd * pXbd
    );

XBD_REQUEST *xbdBioSchedFindBackMergeByHash
    (
    struct xbd *    pXbd,
    struct bio *    pBio
    );

XBD_REQUEST *xbdBioSchedFindFrontMergeByHash
    (
    struct xbd *    pXbd,
    struct bio *    pBio
    );

STATUS xbdBioSchedStrategy
    (
    struct xbd * pXbd,
    struct bio * pBio
    );

VOID xbdBioSchedMergeAdd
    (
    struct xbd *    pXbd,
    XBD_REQUEST *   pReq
    );

VOID xbdBioSchedMergeRemove
    (
    struct xbd *    pXbd,
    XBD_REQUEST *   pReq
    );

STATUS xbdBioSchedAvlShow
    (
    struct xbd *    pXbd,
    AVL_TREE        avlTree
    );

STATUS xbdBioSchedAvlInsert
    (
    struct xbd *            pXbd,
    AVL_TREE *              pAvlTree,
    XBD_REQUEST *           pRequest,
    void *                  pKey,
    AVL_COMPARE             compare
    );

XBD_REQUEST * xbdBioSchedAvlMinGet
    (
    struct xbd *            pXbd,
    AVL_TREE *              pAvlTree,
    void *                  pKey,
    AVL_COMPARE             compare
    );

STATUS xbdBioSchedAvlDelete
    (
    struct xbd *            pXbd,
    AVL_TREE *              pAvlTree,
    XBD_REQUEST *           pRequest,
    void *                  pKey,
    AVL_COMPARE             compare
    );

XBD_SCHED_REQUEST_AVL_NODE * xbdBioSchedAvlSearch
    (
    struct xbd *            pXbd,
    AVL_TREE *              pAvlTree,
    void *                  pKey,
    AVL_COMPARE             compare
    );

XBD_SCHED_REQUEST_AVL_NODE * xbdBioSchedAvlSuccessorGet
    (
    struct xbd *            pXbd,
    AVL_TREE *              pAvlTree,
    void *                  pKey,
    AVL_COMPARE             compare
    );

XBD_SCHED_REQUEST_AVL_NODE * xbdBioSchedAvlPredecessorGet
    (
    struct xbd *            pXbd,
    AVL_TREE *              pAvlTree,
    void *                  pKey,
    AVL_COMPARE             compare
    );
STATUS xbdBioSchedFlush
    (
    struct xbd * pXbd
    );

STATUS xbdBioSchedMaxBiosPerReqSet
    (
    struct xbd * pXbd,
    UINT32       uMaxBiosPerReq
    );

STATUS xbdBioSchedMaxBlksPerReqSet
    (
    struct xbd * pXbd,
    UINT32       uMaxBlksPerReq
    );

STATUS xbdBioSchedMaxBlksPerBioSet
    (
    struct xbd * pXbd,
    UINT32      uMaxBlksPerBio
    );

STATUS xbdBioSchedMaxActiveReqsSet
    (
    struct xbd * pXbd,
    UINT32      uMaxActiveReqs
    );
STATUS xbdBioSchedPolicyAdd
    (
    XBD_BIOSCHED_POLICY * pSchedPolicy
    );

STATUS xbdBioSchedPolicyRemove
    (
    XBD_BIOSCHED_POLICY * pSchedPolicy
    );
STATUS xbdBioSchedMergeBio
    (
    struct xbd *    pXbd,
    struct bio *    pBio
    );
STATUS xbdAttachSchecdPolicyById
    (
    struct xbd *   pXbd,
    int            policyId
    );
STATUS xbdAttachSchecdPolicyByName
    (
    struct xbd *   pXbd,
    char *         policyName
    );
STATUS xbdBioSchedReqPut
    (
    struct xbd *    pXbd,
    XBD_REQUEST *   pReq
    );

#define XBD_NONE_DEBUG                 0   /* Show NONE msgs       */
#define XBD_ERROR_DEBUG                1   /* Show ERROR msgs      */
#define XBD_WARNING_DEBUG              2   /* Show WARNING msgs    */
#define XBD_NORMAL_DEBUG               3   /* Show NORMAL msgs     */
#define XBD_VERBOSE_DEBUG              4   /* Show VERBOSE msgs    */

#ifdef XBD_DEBUG_ENABLE

#define XBD_DBG_INT2SYM(x)      #x
#define XBD_DBG_INT2STR(x)      XBD_DBG_INT2SYM(x)
#define XBD_DBG_LOCATION        __FILE__ "[" XBD_DBG_INT2STR(__LINE__) "]: "

#define XBD_ERR(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    do {                                                         \
        if (((class##Debug) >= XBD_ERROR_DEBUG) &&               \
            (_func_logMsg != NULL))                              \
            {                                                    \
            _func_logMsg(                                        \
                    "ERROR: " #class " - " XBD_DBG_LOCATION fmt, \
                    (_Vx_usr_arg_t)(arg1),                       \
                    (_Vx_usr_arg_t)(arg2),                       \
                    (_Vx_usr_arg_t)(arg3),                       \
                    (_Vx_usr_arg_t)(arg4),                       \
                    (_Vx_usr_arg_t)(arg5),                       \
                    (_Vx_usr_arg_t)(arg6));                      \
            }                                                    \
    } while (FALSE)

#define XBD_WARN(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6) \
    do {                                                         \
        if (((class##Debug) >= XBD_WARNING_DEBUG) &&             \
            (_func_logMsg != NULL))                              \
            {                                                    \
            _func_logMsg("WARN: " #class " - " fmt,              \
                    (_Vx_usr_arg_t)(arg1),                       \
                    (_Vx_usr_arg_t)(arg2),                       \
                    (_Vx_usr_arg_t)(arg3),                       \
                    (_Vx_usr_arg_t)(arg4),                       \
                    (_Vx_usr_arg_t)(arg5),                       \
                    (_Vx_usr_arg_t)(arg6));                      \
            }                                                    \
    } while (FALSE)

#define XBD_DBG(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    do {                                                         \
        if (((class##Debug) >= XBD_NORMAL_DEBUG) &&              \
            (_func_logMsg != NULL))                              \
            {                                                    \
            _func_logMsg("DBG: " #class " - " fmt,               \
                    (_Vx_usr_arg_t)(arg1),                       \
                    (_Vx_usr_arg_t)(arg2),                       \
                    (_Vx_usr_arg_t)(arg3),                       \
                    (_Vx_usr_arg_t)(arg4),                       \
                    (_Vx_usr_arg_t)(arg5),                       \
                    (_Vx_usr_arg_t)(arg6));                      \
            }                                                    \
    } while (FALSE)

#define XBD_VDBG(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6) \
    do {                                                         \
        if (((class##Debug) >= XBD_VERBOSE_DEBUG) &&             \
            (_func_logMsg != NULL))                              \
            {                                                    \
            _func_logMsg("VDBG: " #class " - " fmt,              \
                    (_Vx_usr_arg_t)(arg1),                       \
                    (_Vx_usr_arg_t)(arg2),                       \
                    (_Vx_usr_arg_t)(arg3),                       \
                    (_Vx_usr_arg_t)(arg4),                       \
                    (_Vx_usr_arg_t)(arg5),                       \
                    (_Vx_usr_arg_t)(arg6));                      \
            }                                                    \
    } while (FALSE)

#define XBD_INFO(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6) \
    do {                                                         \
        if (_func_logMsg != NULL)                                \
            {                                                    \
            _func_logMsg("INFO: " #class " - " fmt,              \
                    (_Vx_usr_arg_t)(arg1),                       \
                    (_Vx_usr_arg_t)(arg2),                       \
                    (_Vx_usr_arg_t)(arg3),                       \
                    (_Vx_usr_arg_t)(arg4),                       \
                    (_Vx_usr_arg_t)(arg5),                       \
                    (_Vx_usr_arg_t)(arg6));                      \
            }                                                    \
    } while (FALSE)

#else

#define XBD_ERR(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define XBD_DBG(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define XBD_VDBG(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define XBD_INFO(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define XBD_WARN(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#endif

/* XBD_SCHED DEBUG */

#define XBD_SCHED_ERR(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    XBD_ERR(xbdSched, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_SCHED_DBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    XBD_DBG(xbdSched, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_SCHED_VDBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    XBD_VDBG(xbdSched, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_SCHED_INFO(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    XBD_INFO(xbdSched, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_SCHED_WARN(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    XBD_WARN(xbdSched, fmt, arg1, arg2, arg3, arg4, arg5, arg6)


#define XBD_SCHED_SSD_ERR(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    XBD_ERR(xbdSchedSSD, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_SCHED_SSD_DBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    XBD_DBG(xbdSchedSSD, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_SCHED_SSD_VDBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    XBD_VDBG(xbdSchedSSD, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_SCHED_SSD_INFO(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    XBD_INFO(xbdSchedSSD, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_SCHED_SSD_WARN(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    XBD_WARN(xbdSchedSSD, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

/* XBD_BLK_CACHE DEBUG */

#define XBD_BLK_CACHE_ERR(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    XBD_ERR(xbdBlkCache, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_BLK_CACHE_DBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    XBD_DBG(xbdBlkCache, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_BLK_CACHE_VDBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    XBD_VDBG(xbdBlkCache, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_BLK_CACHE_INFO(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    XBD_INFO(xbdBlkCache, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define XBD_BLK_CACHE_WARN(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    XBD_WARN(xbdBlkCache, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

typedef struct xbd_blk_cache_node
    {
    BOOL     valid; /* cache valid */
    sector_t blkNo;
    void *   pBuf;
    UINT32   uBufSize;
    UINT32   index;
    SEM_ID   mutex;
    SEM_ID   event;
    UINT32   hit; /* hit */
} XBD_BLK_CACHE_NODE, *pXBD_BLK_CACHE_NODE;

typedef struct xbd_blk_cache
    {
    device_t                xbdDev;
    sector_t                nodeMask;
    SEM_ID                  cacheMutex;
    unsigned int            uNodeSize;
    unsigned int            uNodeBlks;
    unsigned int            uNumNodes;
    pXBD_BLK_CACHE_NODE     pCacheList1;
    pXBD_BLK_CACHE_NODE     pCacheList2;
    } XBD_BLK_CACHE, *pXBD_BLK_CACHE;

IMPORT STATUS (* funcXbdBlkCacheAttach) (struct xbd *   pXbd,
                                  UINT32  uNumNodes,
                                  UINT32  uNodeSize);
IMPORT STATUS (* funcXbdBlkCacheDetach) (struct xbd * pXbd);
IMPORT int (* funcXbdBlkCacheStrategy) (device_t  dev,
                                 struct bio *  pBio);

/* typedefs */

typedef struct xbd
    {
    struct device       xbd_dev;
    struct xbd_funcs *  xbd_funcs;
    unsigned            xbd_blocksize;
    sector_t            xbd_nblocks;

    /* Max number of blocks in a single bio the hardware can allow */

    unsigned            xbd_max_blocks;

    /* Max number of simultaneous requests the hardware can allow */

    unsigned            xbd_max_reqs;

    /* Any flags necessary */

    unsigned int        xbd_flags;

    /* XBD_BIOSCHED_POLICY instance we are attached */

    XBD_BIOSCHED_POLICY * xbd_sched_policy;
    XBD_BIOSCHED_CLASS * xbd_sched_class;
    void *              xbd_sched_context;
    struct xbd *        xbd_root;
    XBD_BLK_CACHE *     xbd_cache;
    UINT32              uCacheNumNodes;
    UINT32              uCacheNodeSize;
    LIST                mapList;
    int                 xbd_ext_magic;
    struct xbd_ext *    xbd_ext;
    } XBD, * XBD_ID;

typedef struct xbd_geometry
    {
    unsigned heads;
    unsigned long long cylinders;
    sector_t total_blocks;
    unsigned secs_per_track;
    unsigned blocksize;
    } XBD_GEOMETRY;

typedef struct xbd_info
    {
    XBD_GEOMETRY  xbdGeometry;   /* Media geometry */
    uint32_t      properties;    /* Bit fields for device properties */
    uint32_t      reserved[4];   /* Reserved for future expansion */
    } XBD_INFO;

typedef enum xbd_level {XBD_TOP=0, XBD_PART=1, XBD_BASE=2} XBD_LEVEL;

STATUS xbdInit(void);

int xbdAttach (XBD * xbd, struct xbd_funcs * funcs, const char * name,
                   unsigned blocksize, sector_t nblocks, device_t * result);
void xbdDetach (XBD * xbd);

/* These functions access the driver */

int xbdIoctl (device_t d, int cmd, void * arg);
int xbdStrategy (device_t d, struct bio * bio);
int xbdDump (device_t d, sector_t pos, void * data, size_t size);
int xbdSize (device_t d, long long * result);

int xbdNBlocks (device_t d, sector_t * result);
int xbdBlockSize (device_t d, unsigned * result);
int xbdMaxBlocks (device_t d, unsigned * result);
int xbdMaxRequests (device_t d, unsigned * result);
struct xbd * xbdRoot
    (
    device_t   d
    );
LIST * xbdMapGet
    (
    device_t d
    );
int xbdAttachExt (XBD        *xbd,
                  int        sched,
                  SEM_ID     biomutex,
                  SEM_ID     biordy,
                  struct bio **bioqh,
                  struct bio **bioqt,
                  void       (*f_biodo) (XBD *xbd, struct bio *bio),
                  int        (*f_rmvtst) (XBD *xbd, struct bio *bio));
int xbdStrategyGeneric (XBD *xbd, struct bio *bio);
struct bio * xbdGetNextBioGeneric (XBD *xbd);
void xbdSrvTaskGeneric (XBD *xbd);
int xbdGetBioSched (XBD *xbd, int *retarg);
int xbdSetBioSched (XBD *xbd, int sched);

STATUS xbdBioSchedInit(void);

/* ioctl commands */

#define XBD_GETGEOMETRY	   0xbd000001	/* Extract disk Geometry */
#define XBD_SYNC	   0xbd000002	/* Flush Block device */
#define XBD_SOFT_EJECT	   0xbd000003	/* Eject and raise SoftInsert */
#define XBD_HARD_EJECT	   0xbd000004	/* Eject and raise Insert */
#define XBD_GETBASENAME    0xbd000005	/* Retrieve name of base XBD */
#define XBD_TEST	   0xbd000006	/* Request XBD test its validity */
#define XBD_STACK_COMPLETE 0xbd000007   /* XBD stack is initialized */
#define XBD_GETINFO        0xbd000008   /* Obtain XBD information */

#define XBD_GET_BIOSCHED   0xbd000009   /* Get bio scheduler */
#define XBD_SET_BIOSCHED   0xbd00000a   /* Set bio scheduler */
#define XBD_GET_DEVTYPE    0xbd00000b

#define XBD_SMART_ENABLE            0xbd000011
#define XBD_SMART_DISABLE           0xbd000012
#define XBD_SMART_SAVEATTR          0xbd000013
#define XBD_SMART_ISENABLED         0xbd000014
#define XBD_SMART_AUTOSAVEENABLE    0xbd000015
#define XBD_SMART_AUTOSAVEDISABLE   0xbd000016
#define XBD_SMART_OFFLINEDIAG       0xbd000017
#define XBD_SMART_RETURNSTATUS      0xbd000018
#define XBD_SMART_READDATA          0xbd000019
#define XBD_SMART_READTHRESHOLDS    0xbd00001a

#define XBD_SATA_PARMSGET           0xbd00001b
#define XBD_CFG_ENCRYPTION          0xbd00001c

/* device properties */

#define XBD_INFO_READONLY  0x00000001   /* Device is read-only */
#define XBD_INFO_DISCARD   0x00000002   /* Device supports discard interface */

typedef enum xbd_type
    {
    XBD_FDD = 1,
    XBD_HDD = 2
    }XBD_TYPE;

#ifdef __cplusplus
}
#endif

#endif /* __INCxbdh */
