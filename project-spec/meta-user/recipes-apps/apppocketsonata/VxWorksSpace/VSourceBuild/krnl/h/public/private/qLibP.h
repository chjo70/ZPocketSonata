/* qLibP.h - multi-way queue library header */

/*
 * Copyright (c) 2008-2011, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may17,dlk  Adding QUEUE_TASK_DELETION_WAKEUP (F5593)
19jan11,gls  added qPriDelta prototypes (WIND00200778)
17may10,kk   added QUEUE_KERNEL_INTERRUPTIBLE for (WND00193764)
29apr10,pad  Moved extern C statement after include statements.
29apr10,pad  Moved extern C statement after include statements.
01oct09,zl   removed qInit()
20feb09,zl   changed advanceRtn nTicks argument to ULONG.
17feb09,zl   included vsbConfig.h, fixed Q_PRI_NODE_KEY definiton.
11feb09,zl   moved queue class definitions from public header files
27aug08,zl   created.
*/

#ifndef __INCqLibPh
#define __INCqLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <dllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * qFifoGRemove returns a particular status called ALREADY_REMOVED
 * when the shared TCB has been removed on give side.
 */

#define ALREADY_REMOVED		1

#ifndef _ASMLANGUAGE

/* All queue class nodes must not exceed the sizeof (Q_NODE).  If larger data
 * structures must be used, use one of the private fields as pointer to provide
 * a level on indirection so the size of Q_NODE is not exceeded.
 */

typedef struct q_node		/* Q_NODE */
    {
    ULONG	qPriv1;			/* use is queue type dependent */
    ULONG	qPriv2;			/* use is queue type dependent */
    ULONG	qPriv3;			/* use is queue type dependent */
    ULONG	qPriv4;			/* use is queue type dependent */
    } Q_NODE;

typedef struct			/* Q_FIFO_NODE */
    {
    DL_NODE	node;			/* qPriv1/qPriv2 */
    ULONG	qPriv3;			/* unused for FIFO queues */
    ULONG	qPriv4;			/* unused for FIFO queues */
    } Q_FIFO_NODE;

typedef struct			/* Q_PRI_NODE */
    {
    DL_NODE	node;			/* priority doubly linked node */
    ULONG	key;			/* insertion key (ie. priority) */
    ULONG       qPriv4;			/* unused for priority queues */
    } Q_PRI_NODE;

/* priority bitmap lists */

/*
 * Q_PRI_BMAP_MAX_PRIORITIES must satisfy the following conditions:
 *   a) 288 <= Q_PRI_BMAP_MAX_PRIORITIES <= 1024
 *   b) Must be a multiple of 32
 */

#define Q_PRI_BMAP_MAX_PRIORITIES	288
#define BMAP_BITS			(8 * sizeof (UINT32))

/* typedefs */

typedef struct			/* BMAP_LIST */
    {
    UINT32	metaBMap;		/* lookup table for map array */
    UINT32	bMap [Q_PRI_BMAP_MAX_PRIORITIES / BMAP_BITS];
    DL_LIST	listArray [Q_PRI_BMAP_MAX_PRIORITIES];
    } BMAP_LIST;

/* All queue classes must not exceed the sizeof (Q_HEAD).  If larger data
 * structures must be used, use one of the private fields as pointer to provide
 * a level on indirection so the size of Q_HEAD is not exceeded.
 *
 * The first field in the Q_HEAD must contain the highest priority Q_NODE.
 * The routine qFirst () makes this assumption.  The scheduler does a qFirst
 * on the ready queue as part of its scheduling.
 */

typedef struct q_head		/* Q_HEAD */
    {
    Q_NODE *	pFirstNode;		/* first node in queue based on key */
    ULONG	qPriv1;			/* use is queue type dependent */
    ULONG	qPriv2;			/* use is queue type dependent */
    struct q_class *pQClass;		/* pointer to queue class */
    } Q_HEAD;

typedef struct			/* Q_FIFO_HEAD */
    {
    DL_LIST 	list;			/* pFirstNode/qPriv1 */
    ULONG	attr;			/* attributes (qPriv2) */
    struct q_class *pQClass;		/* pointer to queue class */
    } Q_FIFO_HEAD;

typedef struct			/* Q_PRI_HEAD */
    {
    DL_LIST 	list;			/* pFirstNode/qPriv1 */
    ULONG	attr;			/* qPriv2 */
    struct q_class *pQClass;		/* pointer to queue class */
    } Q_PRI_HEAD;

typedef struct			/* Q_PRI_BMAP_HEAD */
    {
    Q_PRI_NODE * highNode;		/* highest priority node */
    BMAP_LIST *	 pBMapList;		/* pointer to mapped list */
    ULONG 	 nPriority;		/* priorities in queue (1,288) */
    struct q_class *pQClass;		/* pointer to queue class */
    } Q_PRI_BMAP_HEAD;

typedef struct q_fifo_g_head	/* Q_FIFO_G_HEAD */
    {
    ULONG	  first;		/* NOT USED */
    UINT32 * 	  pLock;		/* NULL if already acquired */
    struct sm_dl_list * pFifoQ;		/* shared memory pend queue */
    struct q_class *pQClass;		/* pointer to class */
    } Q_FIFO_G_HEAD;

typedef void (*QCLASS_RESORT_FUNC) (Q_HEAD *pQHead, Q_NODE *pQNode, ULONG key);
typedef BOOL (*QEACH_USR_FUNC) (Q_NODE * pQNode, void * arg);

typedef struct q_class		/* Q_CLASS */
    {
    void     (*putRtn) 			/* insert a node into q  */
		(
		Q_HEAD * pQHead,
		Q_NODE * pQNode,
		ULONG    key
		);
    Q_NODE * (*getRtn)			/* return and remove lead node */
		(
		Q_HEAD * pQHead
		);
    STATUS   (*removeRtn)		/* remove routine */
		(
		Q_HEAD * pQHead,
		Q_NODE * pQNode
		);
    void     (*resortRtn)		/* resort node to new priority */
		(
		Q_HEAD * pQHead,
		Q_NODE * pQNode,
		ULONG    key
		);
    void     (*advanceRtn)		/* advance queue */
		(
		Q_HEAD * pQHead,
		ULONG	 nTicks
		);
    Q_NODE * (*getExpiredRtn)		/* return and remove expired Q_NODE */
		(
		Q_HEAD * pQHead
		);
    ULONG    (*keyRtn)			/* return insertion key of node */
		(
		Q_NODE * pQNode
		);
    int      (*infoRtn)			/* return array of nodes in queue */
		(
		Q_HEAD * pQHead,
		Q_NODE * nodeArray[],
		int      maxNodes
		);
    Q_NODE * (*eachRtn)			/* call a user routine for each node */
		(
		Q_HEAD * pQHead,
		QEACH_USR_FUNC routine,
		void *	 routineArg
		);
    void     (*restoreRtn)		/* restore a node position in queue */
		(
		Q_HEAD * pQHead,
		Q_NODE * pQNode,
		ULONG    key
		);
    Q_NODE * (*nextRtn) 		/* return next node in a queue */
		(
		Q_HEAD * pQHead,
		Q_NODE * pNode
		);
    struct q_class * valid;		/* valid == pointer to queue class */
    } Q_CLASS;

typedef Q_CLASS * Q_CLASS_ID;	/* Q_CLASS_ID */

/* private queue classes */

IMPORT Q_CLASS_ID		qFifoClassId;
IMPORT Q_CLASS_ID		qFifoGClassId;
IMPORT Q_CLASS_ID		qPriListClassId;
IMPORT Q_CLASS_ID		qPriListFromTailClassId;
IMPORT Q_CLASS_ID		qPriDeltaClassId;
IMPORT Q_CLASS_ID		qPriBMapClassId;
IMPORT Q_CLASS_ID		qTradPriListClassId;
IMPORT Q_CLASS_ID		qTradPriBMapClassId;
IMPORT Q_CLASS_ID		qPxPriBMapClassId;
IMPORT Q_CLASS_ID		qPxSSPriBMapClassId;

/* private queue types */

#define Q_FIFO			qFifoClassId
#define Q_FIFO_G		qFifoGClassId
#define Q_PRI_LIST		qPriListClassId
#define Q_PRI_LIST_FROM_TAIL	qPriListFromTailClassId
#define Q_PRI_DELTA		qPriDeltaClassId
#define Q_PRI_BMAP		qPriBMapClassId
#define Q_TRAD_PRI_LIST		qTradPriListClassId
#define Q_TRAD_PRI_BMAP		qTradPriBMapClassId
#define Q_PX_PRI_BMAP		qPxPriBMapClassId
#define Q_PX_SS_PRI_BMAP	qPxSSPriBMapClassId

/*
 * Queue can have attributes. The qPriv2 member of Q_HEAD represents the
 * queue attribute. The attributes supported are
 * 1) Queue interruptibiliy
 *     QUEUE_INTERRUPTIBLE implies that the task pended on this queue can
 *     be made ready by a signal. QUEUE_NONINTERRUPTIBLE is the negate of
 *     QUEUE_INTERRUPTIBLE. By default, queue interrupt-ability attribute for
 *     a queue is QUEUE_NONINTERRUPTIBLE.
 *     QUEUE_INTERRUPTIBLE allows an RTP task pended on this queue to
 *     be made ready by a signal.
 *     QUEUE_KERNEL_INTERRUPTIBLE allows a kernel task pended on this
 *     queue to be made ready by a signal.
 *     QUEUE_NONINTERRUPTIBLE prevents any task pended on this queue from
 *     being made ready by a signal.
 *
 *     By default, queue interrupt-ability attribute for a queue is
 *     QUEUE_NONINTERRUPTIBLE.
 *
 *2) Queue task deletion wakeup.
 *     If the QUEUE_TASK_DELETION_WAKEUP attribute is set, a task pended
 *     on the queue (or about to pend) may be awakened (or fail to pend)
 *     with the error EDOOM, provided the task is currently deletion safe
 *     and some other task is attempting to delete the task. Note that only
 *     one early EDOOM return from a pending call will occur per deletion
 *     attempt in this case; subsequent attempts to pend on the same
 *     queue will not be terminated early unless another deletion attempt
 *     is made.  The QUEUE_TASK_DELETION_WAKEUP attribute is not set
 *     by default.
 *
 * Currently only Q_PRI_LIST , Q_FIFO_HEAD, Q_PRI_LIST_FROM_TAIL have
 * the queue attribute support.
 */

#define QUEUE_INTERRUPTIBLE           0x01
#define QUEUE_KERNEL_INTERRUPTIBLE    0x02
#define QUEUE_TASK_DELETION_WAKEUP    0x04
#define QUEUE_NONINTERRUPTIBLE        0x00
#define QUEUE_ATTRIBUTE_MASK          0x07

#define Q_ATTRIBUTE_GET(qHead)		(((Q_HEAD *)(qHead))->qPriv2)
#define Q_ATTRIBUTE_SET(qHead, value)	(((Q_HEAD *)(qHead))->qPriv2 = \
							(ULONG)(value))
#define IS_Q_ATTRIBUTE_OK(value) 	(((value) & ~QUEUE_ATTRIBUTE_MASK) == 0)
/*******************************************************************************
*
* Q_CLASS_VERIFY - check the validity of an queue class pointer
*
* This macro verifies the existence of the specified queue class by comparing
* the queue classes valid field to the pointer to the queue class.
*
* RETURNS: OK or ERROR if invalid class pointer
*
* \NOMANUAL
*/

#define Q_CLASS_VERIFY(pQClass)						\
    (									\
    (((Q_CLASS *)(pQClass))->valid == (Q_CLASS *) pQClass) ?		\
	    OK								\
	:								\
	    ERROR							\
    )

/*******************************************************************************
*
* Q_FIRST - return first node in multi-way queue
*
* This routine returns a pointer to the first node in the specified multi-way
* queue head.  If the queue is empty, NULL is returned.
*
* RETURNS
*  Pointer to first queue node in queue head, or
*  NULL if queue is empty.
*
* \NOMANUAL
*/

#define Q_FIRST(pQHead)							\
    ((Q_NODE *)(((Q_HEAD *)(pQHead))->pFirstNode))

/*******************************************************************************
*
* Q_NEXT - return the next node in the queue
*
* This routine returns a pointer to the next node in the specified queue. For
* the last node, Q_NEXT() returns NULL.
*
* \NOMANUAL
*/

#define Q_NEXT(pQHead,pQNode)						\
    ((Q_NODE *)((*(((Q_HEAD *)(pQHead))->pQClass->nextRtn))		\
     (((Q_HEAD *)(pQHead)), ((Q_NODE *)(pQNode)))))

/*******************************************************************************
*
* Q_PUT - insert a node into a multi-way queue
*
* This routine inserts a node into a multi-way queue.  The insertion is based
* on the key and the underlying queue class.
*
* \NOMANUAL
*/

#define Q_PUT(pQHead,pQNode,key)					\
    (*(((Q_HEAD *)(pQHead))->pQClass->putRtn))				\
    (((Q_HEAD *)(pQHead)), ((Q_NODE *)(pQNode)), (ULONG)(key))

/*******************************************************************************
*
* Q_RESTORE - restore a node position in multi-way queue
*
* This routine inserts a node into a multi-way queue and restores its position.
* The insertion is based on the key and the underlying queue class.
*
* \NOMANUAL
*/

#define Q_RESTORE(pQHead,pQNode,key)			        \
    (*(((Q_HEAD *)(pQHead))->pQClass->restoreRtn))		\
    (((Q_HEAD *)(pQHead)), ((Q_NODE *)(pQNode)), (ULONG)(key))

/*******************************************************************************
*
* Q_GET - remove and return first node in multi-way queue
*
* This routine removes and returns the first node in a multi-way queue.  If
* the queue is empty, NULL is returned.
*
* RETURNS
*  Pointer to first queue node in queue head, or
*  NULL if queue is empty.
*
* \NOMANUAL
*/

#define Q_GET(pQHead)							\
    ((Q_NODE *)((*(((Q_HEAD *)(pQHead))->pQClass->getRtn))		\
     ((Q_HEAD *)(pQHead))))

/*******************************************************************************
*
* Q_REMOVE - remove a node from a multi-way queue
*
* This routine removes a node from the specified multi-way queue.
*
* \NOMANUAL
*/

#define Q_REMOVE(pQHead,pQNode)						\
    (*(((Q_HEAD *)(pQHead))->pQClass->removeRtn))			\
    (((Q_HEAD *)(pQHead)), ((Q_NODE *)(pQNode)))

/*******************************************************************************
*
* Q_RESORT - resort a node to a new position based on a new key
*
* This routine resorts a node to a new position based on a new key.  It can
* be used to change the priority of a queued element, for instance.
*
* \NOMANUAL
*/

#define Q_RESORT(pQHead,pQNode,newKey)					\
    (*(((Q_HEAD *)(pQHead))->pQClass->resortRtn))			\
    (((Q_HEAD *)(pQHead)), ((Q_NODE *)(pQNode)), ((ULONG)(newKey)))

/*******************************************************************************
*
* Q_ADVANCEN - advance a queues concept of time by N tick (timer queues only)
*
* Time queues that keep nodes prioritized by time-to-fire utilize this
* routine to advance time by N tick after e.g., a power save sleep.
*
* \NOMANUAL
*/

#define Q_ADVANCEN(pQHead, n)						\
    (*(((Q_HEAD *)(pQHead))->pQClass->advanceRtn))			\
     ((Q_HEAD *)(pQHead), (ULONG)(n))

/*******************************************************************************
*
* Q_GET_EXPIRED - return a time-to-fire expired node
*
* This routine returns a time-to-fire expired node in a multi-way timer queue.
* Expired nodes result from a qAdvance(2) advancing a node beyond its delay.
* As many nodes may expire on a single qAdvance(2), this routine should be
* called inside a while loop until NULL is returned.  NULL is returned when
* there are no expired nodes.
*
* RETURNS
*  Pointer to first queue node in queue head, or
*  NULL if queue is empty.
*
* \NOMANUAL
*/

#define Q_GET_EXPIRED(pQHead)						\
    ((Q_NODE *)((*(((Q_HEAD *)(pQHead))->pQClass->getExpiredRtn))	\
     ((Q_HEAD *)(pQHead))))

/*******************************************************************************
*
* Q_KEY - return the key of a node
*
* This routine returns the key of a node currently in a multi-way queue.  The
* keyType determines key style on certain queue classes.
*
* RETURNS
*  Node's key.
*
* \NOMANUAL
*/

#define Q_KEY(pQHead,pQNode,keyType)					\
    (*(((Q_HEAD *)(pQHead))->pQClass->keyRtn)) ((Q_NODE *)(pQNode))

/*******************************************************************************
*
* Q_INFO - gather information on a multi-way queue
*
* This routine fills up to maxNodes elements of a nodeArray with nodes
* currently in a multi-way queue.  The actual number of nodes copied to the
* array is returned.  If the nodeArray is NULL, then the number of nodes in
* the multi-way queue is returned.
*
* RETURNS
*  Number of node pointers copied into the nodeArray, or
*  Number of nodes in multi-way queue if nodeArray is NULL
*
* \NOMANUAL
*/

#define Q_INFO(pQHead,nodeArray,maxNodes)				\
    (*(((Q_HEAD *)(pQHead))->pQClass->infoRtn))				\
    (((Q_HEAD *)(pQHead)),((Q_NODE **)(nodeArray)),((int)(maxNodes)))

/*******************************************************************************
*
* Q_EACH - call a routine for each node in a queue
*
* This routine calls a user-supplied routine once for each node in the
* queue.  The routine should be declared as follows:
* \cs
*  BOOL routine (pQNode, arg)
*      Q_NODE	*pQNode;	* pointer to a queue node          *
*      long	arg;		* arbitrary user-supplied argument *
* \ce
* The user-supplied routine should return TRUE if qEach (2) is to continue
* calling it for each entry, or FALSE if it is done and qEach can exit.
*
* RETURNS: NULL if traversed whole queue, or pointer to Q_NODE that
*          qEach ended with.
*
* \NOMANUAL
*/

#define Q_EACH(pQHead,routine,routineArg)				\
    ((Q_NODE *)((*(((Q_HEAD *)(pQHead))->pQClass->eachRtn))		\
    (((Q_HEAD *)(pQHead)),(QEACH_USR_FUNC)(routine),(void *)(routineArg))))

extern STATUS qFifoInit (Q_HEAD *pQHead, Q_CLASS_ID qClass, UINT attribute);
extern STATUS qPriListInit (Q_HEAD *pQHead, Q_CLASS_ID qClass, UINT attr);
extern STATUS qPriDeltaInit (Q_HEAD *pQHead, Q_CLASS_ID qClass);
extern STATUS qPriBMapInit (Q_HEAD *pQHead, Q_CLASS_ID qClassId,
			    BMAP_LIST *pBMapList, UINT maxPriority);
extern STATUS qFifoGInit (Q_FIFO_G_HEAD * pQHead);

extern Q_NODE * qPriDeltaEach (Q_HEAD * pQHead, QEACH_USR_FUNC routine,
			       void * pArg);
extern Q_NODE * qPriDeltaGet (Q_HEAD * pQHead);
extern Q_NODE * qPriDeltaGetExpired (Q_HEAD * pQHead);
extern ULONG 	qPriDeltaKey (Q_NODE * pQNode);
extern int 	qPriDeltaInfo (Q_HEAD * pQHead, Q_NODE * nodes [],
			       int maxNodes);
extern void 	qPriDeltaAdvance (Q_HEAD * pQHead, ULONG nTicks);
extern void 	qPriDeltaPut (Q_HEAD * pQHead, Q_NODE * pQNode, ULONG key);
extern STATUS 	qPriDeltaRemove (Q_HEAD * pQHead, Q_NODE * pQNode);
extern void 	qPriDeltaResort (Q_HEAD * pQHead, Q_NODE * pQNode,
				 ULONG newKey);
extern Q_NODE * qPriDeltaNext (Q_HEAD * pQHead, Q_NODE * pQNode);

/* for migration, provided for a limited time */

extern void qTradPriListSetCompatible (void);
extern void qTradPriBMapSetCompatible (void);

#else /* _ASMLANGUAGE */

#ifdef _WRS_CONFIG_LP64
# define Q_PRI_NODE_KEY		0x10	/* queue insertion key, LP64 */
#else
# define Q_PRI_NODE_KEY		0x08	/* queue insertion key, ILP32 */
#endif

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCqLibh */
