/* rBuffLib.h - ring of buffers library header file */

/*
 * Copyright (c) 1997-2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01s,29apr10,pad  Moved extern C statement after include statements.
01s,10feb10,tcr  update for 64bit
01r,30jun09,tcr  remove surplus includes
01q,07jun07,tcr  make ring buffer doubly-linked
01p,02jan07,tcr  update for SMP, add support for callback
01o,13jan05,tcr  Fix SPR 101137: rBuff mgr priority should be configurable
                 Fix SPR 105850: missing prototype for wvRBuffMgrPrioritySet 
01n,15apr04,tcr  add error codes
01m,17sep03,tcr  remove surplus semaphore
01l,14oct98,pr   added rBuffShowInit
01k,23jul98,cjtc defined new structure for windview ring buffer manager
		 structure (SPR 21752)
01j,04may98,nps  rework msg passing for rBuff maintenance.
01i,19mar98,nps  added new rBuff option which indicates whether to give
                 threshold sempahore.
01h,18dec97,cth  changed include buffer.h to private/wvBufferP.h
01g,02dec97,nps  Added field to store peak utilisation.
01f,20nov97,nps  put the OBJ_CORE in BUFFER_DESC (the work described in
                 the previous coment).
01e,16nov97,cth  changed interface to include BUFFER_DESC as hdr of struct rBuff
                 OBJ_CORE vs BUFFER_DESC still needs work
01d,21oct97,nps  include semLibP.h.
01c,16sep97,nps  modified interface to support generic upload path.
                 split off those fields returned by rBuffInfoGet into
                 separate structure.
                 added RBUFF_MAX_AVAILABLE.
01b,28jul97,nps  further implementation/testing.
                 rBuffReset returns STATUS type.
01a,14jul97,nps  written
*/

#ifndef __INCrBuffLibh
#define __INCrBuffLibh

#include <vxWorks.h>
#include <memLib.h>
#include <msgQLib.h>
#include <objLib.h>
#include <semLib.h>
#include <private/wvBufferP.h>

#ifdef __cplusplus
extern "C" {
#endif

    
/* defines */

/* rBuffMgr Msg Queue Configuration */

#define RBUFF_MSGQ_MAX_MSGS        50
#define RBUFF_MSGQ_OPTIONS         (MSG_Q_FIFO)

#define RBUFF_MGR_OPTIONS           VX_UNBREAKABLE

/* WindView rBuffMgr Configuration */

#define WV_RBUFF_MGR_OPTIONS        VX_UNBREAKABLE
#define WV_RBUFF_MGR_MSGQ_MAX       50
#define WV_RBUFF_MGR_MSGQ_OPTIONS   (MSG_Q_FIFO)

#define RBUFF_MAX_AVAILABLE     -1

#define RBUFF_ERR_UPLOAD        0
#define RBUFF_ERR_FULL          1
    
#if USE_RBUFF_SEM

#define RBUFF_LOCK(RBUFF)                                      \
if (!INT_CONTEXT())                                            \
    {                                                          \
        semTake(RBUFF->access,WAIT_FOREVER);                   \
    }

#define RBUFF_UNLOCK(RBUFF)                                    \
if (!INT_CONTEXT())                                            \
    {                                                          \
        semGive(RBUFF->access);                                \
    }

#else

#define RBUFF_LOCK(RBUFF)
#define RBUFF_UNLOCK(RBUFF)

#endif /* USE_RBUFF */

#define RBUFF_UPLOAD_SEM(RBUFF)   (&(RBUFF->buffDesc.hasDataSem))

#define RBUFF_EMPTY_KEEP        1

/* rBuff Manager Msg Defines */

#define RBUFF_MAX_MSGS          10

#define RBUFF_MSG_LEN           12

#define RBUFF_MSG_ADD           1
#define RBUFF_MSG_FREE          2
#define RBUFF_MSG_FULL		-1
#define RBUFF_MSG_THRESHX       3
#define NUM_NEW_BUFF_CALLBACKS  8
    

/* types */

/* Individual buffer control structure */

typedef struct rbuff_buff
    {
    struct rbuff_buff *next;        /* ptr to the next buffer in the ring */
    size_t            spaceAvail;   /* num of bytes of free space in buff */
    unsigned char     *dataStart;   /* ptr to the actual buffer region */
    unsigned char     *dataEnd;     /* ptr to the last actual byte of buff area */
    size_t            dataLen;      /* length of valid data in bytes */
    BOOL              uncommitedRead;   /* read of buffer data in progress */
    struct rbuff_buff *prev;        /* ptr to previous buffer in ring */
    } RBUFF_BUFF_TYPE;

typedef RBUFF_BUFF_TYPE *RBUFF_PTR;

typedef struct rbuff_stats {
    PART_ID       srcPart;          /* source partition specified on creation */
    UINT32        options;          /* options selected */
    size_t        buffSize;         /* size of each buffer in bytes */
    UINT32        currBuffs;        /* current num of buffs in the ring */
    size_t        threshold;        /* threshold at which upload will begin */
    UINT32        minBuffs;         /* min num of buffs specified */
    UINT32        maxBuffs;         /* max num of buffs specified */
    UINT32        maxBuffsActual;   /* max num of buffs actually used */
    UINT32        emptyBuffs;       /* num of buffs to hold empty */
    size_t        dataContent;      /* num of bytes of data currently in the buff */
    UINT32        writesSinceReset; /* num of write accesses since the last reset */
    UINT32        readsSinceReset;  /* num of read accesses since the last reset */
    UINT32        timesExtended;    /* num of times the buffer had to be extended */
    UINT32        timesXThreshold;  /* num of times the threshold was crossed */
    size_t        bytesWritten;     /* bytes written since reset */
    size_t        bytesRead;        /* bytes read since reset */
    size_t        bytesPeak;        /* Peak buffer content */
} RBUFF_INFO_TYPE;

/*
 * In the new ring buffer scheme, the message list is held in the ring buffer
 * manager's control structure, not in the ring buffer itself. For WV 2.0, it
 * is being left here so that the structure offsets will not change, so as not
 * to require a chage to the host side. For WV 2.2, the message queue here may
 * be removed - i.e. the following fields will no longer be required:
 * 	msgSem
 *	msg
 *	msgWriteIndex
 *	msgReadIndex
 * When removed, the host side tcl offsets will need to be changed to reflect
 * the new structure.
 *
 * msgOutstanding is still required in this structure, since it is buffer-
 * specific, but in reality its name
 * should be changed to more closely reflect its function...to
 * rBuffAddMsgOutstanding, for example
 */

/* Ring control structure */
typedef struct rbuff
    {
    BUFFER_DESC   buffDesc;         /* generic buffer descriptor */ 
    RBUFF_PTR     buffRead;         /* buff from which next data read */
    RBUFF_PTR     buffWrite;        /* buff to hold next data read */
    UINT8         *dataRead;        /* abs ptr from where data next read */
    UINT8         *dataWrite;       /* abs ptr to where data next written */
    int           fd;               /* the fd of the upload device */
    STATUS	  (*errorHandler)();     /* fn to call is fd write returns error */
    UINT32        nestLevel;        /* the level to which rBuff calls are nested */
    RBUFF_INFO_TYPE info;           /* Info that is returned by rBuffInfo */
    struct wv_rbuff_mgr_type * 	rBuffMgrId;
    unsigned int  msgOutstanding;

    int           numCallbacks;
    STATUS (*callbackList [NUM_NEW_BUFF_CALLBACKS])(BUFFER_ID bufferId);
    int           inCallback;   /* set if in new buff hook */
    } RBUFF_TYPE;

typedef struct rBuffCreateParams
    {
    PART_ID sourcePartition;
    long  	minimum;
    long   	maximum;
    size_t  	buffSize;
    size_t  	threshold;
    STATUS 	(*errorHandler)();
    long  	options;
    } rBuffCreateParamsType;

#ifndef GENERIC_RBUFF

/* ring buffer manager types - for windview */

/*
 * these types have been defined especially for windview. For truly generic
 * ring buffers, a vxWorks message queue may be used rather than the home-
 * grown one which is needed for windview (to prevent the messages for the
 * windview ring buffer manager themselves generating events)
 */

typedef struct wv_rbuff_mgr_msg_type {
    RBUFF_TYPE *	ringId;		/* id of ring for message */
    int  		msgType;        /* message type */
    _Vx_usr_arg_t 	arg;            /* argument */
} WV_RBUFF_MGR_MSG_TYPE;

typedef struct wv_rbuff_mgr_type {
    TASK_ID	  	    tid;		/* tid of tWvRBuffMgr task */
    int		  	    priorityDefault; 	/* default priority of task */
    unsigned int  	    msgWriteIndex;	/* message q write index */
    unsigned int  	    msgReadIndex;	/* message q read index */
    WV_RBUFF_MGR_MSG_TYPE   msg [WV_RBUFF_MGR_MSGQ_MAX]; /* msg queue */
} WV_RBUFF_MGR_TYPE;

typedef WV_RBUFF_MGR_TYPE * WV_RBUFF_MGR_ID;

#endif /* GENERIC_RBUFF */



#ifndef _ASMLANGUAGE

typedef RBUFF_TYPE *RBUFF_ID;

#endif /* ~ _ASMLANGUAGE */

/* ring of buffer options */

#define RBUFF_WRAPAROUND		0x1
#define RBUFF_WRITE_BLOCK               0x2
#define RBUFF_READ_BLOCK                0x4
#define RBUFF_UP_DEFERRED               0x8

#ifndef _ASMLANGUAGE

/* variable declarations */

extern CLASS_ID rBuffClassId;
extern MSG_Q_ID rBuffMgrMsgQId;

extern int      wvRBuffMgrPriorityDefault;
    
/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS rBuffLibInit(void);

extern BUFFER_ID rBuffCreate (void *rBuffParams);

extern UINT8 *rBuffWrite (BUFFER_ID buffId, UINT8 * dataSrc, size_t numOfBytes);

extern size_t rBuffRead (BUFFER_ID buffId, UINT8 *dataDest, size_t numOfBytes);

extern ssize_t rBuffReadReserve (BUFFER_ID buffId, UINT8 **src);

extern STATUS rBuffReadCommit (BUFFER_ID buffId, size_t numOfBytes);

extern STATUS rBuffFlush (BUFFER_ID buffId);

extern STATUS rBuffReset (BUFFER_ID buffId);

extern ssize_t rBuffNBytes (BUFFER_ID buffId);

extern int rBuffUpload (BUFFER_ID buffId, int fd);

extern STATUS rBuffSetFd (BUFFER_ID buffId, int fd);

extern void rBuffShowInit (void);

extern STATUS rBuffShow (BUFFER_ID buffId, UINT32 type);

extern STATUS rBuffDestroy (BUFFER_ID buffId);

extern STATUS wvRBuffMgrPrioritySet (int priority);

extern int wvRBuffMgr(WV_RBUFF_MGR_TYPE * rBuffMgrId);

#else	/* __STDC__ */

extern STATUS rBuffLibInit();
extern BUFFER_ID rBuffCreate();
extern UINT8 *rBuffWrite();
extern INT32  rBuffRead();
extern INT32  rBuffNBytesContig();
extern STATUS rBuffMoveAhead();
extern INT32  rBuffFlush();
extern STATUS rBuffReset();
extern INT32  rBuffNBytes();
extern STATUS rBuffUpload();
extern STATUS rBuffSetFd();
extern STATUS rBuffShow();
extern void   rBuffShowInit ();
extern STATUS rBuffDestroy();
extern STATUS wvRBuffMgrPrioritySet();

#endif	/* __STDC__ */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCrBuffLibh */
