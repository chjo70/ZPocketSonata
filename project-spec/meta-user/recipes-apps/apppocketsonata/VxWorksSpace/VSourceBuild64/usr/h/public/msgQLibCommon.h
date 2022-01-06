/* msgQLibCommon.h - common message queue library header file */

/*
 * Copyright 2003-2004, 2009-2010, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may17,dlk  Added MSG_Q_TASK_DELETION_WAKEUP (F5593)
09nov10,zl   added MSG_Q_ID_NULL definition.
16jun10,pcs  change the data type of timeout from an int to _Vx_ticks_t
06may10,cww  Changed numMsg type params to size_t
28apr10,pad  Moved extern C statement after include statements.
25aug09,jpb  Updated for LP64 support.
11may09,cww  Add LP64 support
03sep04,bwa  added S_msgQLib_INVALID_MSG_COUNT errno.
22apr04,dcc  added 'context' to msgQOpen() parameters.
30mar04,ans  added MSG_Q_INTERRUPTIBLE  option.
22mar04,dcc  added msgQClose() and msgQUnlink() prototypes.
25nov03,aeg  removed fields from MSG_Q_INFO in user-space.
31oct03,aeg  added S_msgQLib_ILLEGAL_OPTIONS, S_msgQLib_ILLEGAL_PRIORITY
		 and S_msgQLib_UNSUPPORTED_OPERATION errnos.
01a,24oct03,aeg  written (based on kernel version 02o).
*/

#ifndef __INCmsgQLibCommonh
#define __INCmsgQLibCommonh

#include <vxWorks.h>
#include <vwModNum.h>
#include <objLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* generic status codes */

#define S_msgQLib_INVALID_MSG_LENGTH		(M_msgQLib | 1)
#define S_msgQLib_NON_ZERO_TIMEOUT_AT_INT_LEVEL	(M_msgQLib | 2)
#define S_msgQLib_INVALID_QUEUE_TYPE		(M_msgQLib | 3)
#define S_msgQLib_ILLEGAL_OPTIONS		(M_msgQLib | 4)
#define S_msgQLib_ILLEGAL_PRIORITY		(M_msgQLib | 5)
#define S_msgQLib_UNSUPPORTED_OPERATION		(M_msgQLib | 6)
#define S_msgQLib_INVALID_MSG_COUNT	        (M_msgQLib | 7)

/* return value for unsuccessful msgQCreate() and msgQOpen() */

#define MSG_Q_ID_NULL	((MSG_Q_ID) 0)

/* message queue options */

#define MSG_Q_TYPE_MASK            0x01 /* mask for pend queue type in options */
#define MSG_Q_FIFO                 0x00 /* tasks wait in FIFO order */
#define MSG_Q_PRIORITY             0x01 /* tasks wait in PRIORITY order */
#define MSG_Q_EVENTSEND_ERR_NOTIFY 0x02 /* notify when eventRsrcSend fails */
#define MSG_Q_INTERRUPTIBLE        0x04 /* interruptible on RTP signal */
#define MSG_Q_TASK_DELETION_WAKEUP 0x08 /* early wakeup on task deletion attempt */

/* message send priorities */

#define MSG_PRI_NORMAL	0	/* normal priority message */
#define MSG_PRI_URGENT	1	/* urgent priority message */

/* message queue typedefs */

typedef struct			/* MSG_Q_INFO */
    {
    size_t    numMsgs;		/* OUT: number of messages queued */
    int       numTasks;		/* OUT: number of tasks waiting on msg q */

    int       sendTimeouts;	/* OUT: count of send timeouts */
    int       recvTimeouts;	/* OUT: count of receive timeouts */

    int       options;		/* OUT: options with which msg q was created */
    size_t    maxMsgs;		/* OUT: max messages that can be queued */
    size_t    maxMsgLength;	/* OUT: max byte length of each message */

#ifdef _WRS_KERNEL
    int	      taskIdListMax;	/* IN: max tasks to fill in taskIdList */
    int       msgListMax;	/* IN: max msgs to fill in msg lists */

    TASK_ID * taskIdList;	/* PTR: array of task ids waiting on msg q */
    char **   msgPtrList;	/* PTR: array of msg ptrs queued to msg q */
    size_t *  msgLenList;	/* PTR: array of lengths of msgs */
#endif /* _WRS_KERNEL */
    } MSG_Q_INFO;

/* function declarations */

extern MSG_Q_ID msgQCreate  (size_t maxMsgs, size_t maxMsgLength, int options);
extern STATUS 	msgQDelete  (MSG_Q_ID msgQId);
extern STATUS 	msgQSend    (MSG_Q_ID msgQId, char * buffer, size_t nBytes,
			     _Vx_ticks_t timeout, int priority);
extern ssize_t 	msgQReceive (MSG_Q_ID msgQId, char * buffer, size_t maxNBytes,
			     _Vx_ticks_t timeout);
extern STATUS 	msgQInfoGet (MSG_Q_ID msgQId, MSG_Q_INFO *pInfo);
extern ssize_t 	msgQNumMsgs (MSG_Q_ID msgQId);
extern MSG_Q_ID msgQOpen    (const char * name, size_t maxMsgs,
			     size_t maxMsgLength, int options, int mode,
			     void * context);
extern STATUS 	msgQClose   (MSG_Q_ID msgQId);
extern STATUS 	msgQUnlink  (const char * name);

#ifdef __cplusplus
}
#endif

#endif /* __INCmsgQLibCommonh */
