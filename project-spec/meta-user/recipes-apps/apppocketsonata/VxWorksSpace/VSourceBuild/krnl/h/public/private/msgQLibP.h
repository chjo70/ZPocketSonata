/* msgQLibP.h - private message queue library header file */

/*
 * Copyright (c) 1984-2004, 2007-2011, 2014, 2016-2017
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind RIver License agreement.
 */

/*
modification history
--------------------
20may17,dlk  Adding MSG_Q_TASK_DELETION_WAKEUP to MSG_Q_OPTIONS_MASK (F5593)
20sep16,dlk  Adding msgQWritable().
25feb14,cww  added forward declaration for struct windTcb
05feb14,h_k  cleaned up unsupported msgQSm.
10jan11,gls  removed msgQBeingDeleted field (WIND00139322)
13oct10,jpb  Adjusted MSG_Q offsets
06may10,cww  Changed numMsg type params to size_t
29apr10,pad  Moved extern C statement after include statements.
25aug09,jpb  Updated for LP64 support.
11may09,cww  Add LP64 support
11feb09,zl   removed qLib.h inclusion
27aug08,jpb  Renamed VSB header file
24jun08,jpb  Added include path for kernel configurations options set in
             vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
29aug07,jmg  Added notes to MSG_Q and MSG_NODE structures and removed
             ifdef _WRS_VX_SMP from MSG_Q.
13aug07,lei  added safeCntFlag parameter to msgQObjUnsafe()
24jul07,jmg  Added parameters to msgQObjUnsafe() and msgQObjSafe()
17jul07,lei  changed refMsgQId to "void*"
19jun07,gls  split union in MSGQ_TCB (Defect #00096894)
15jun07,lei  moved refMsgQId from WIND_SMP_INFO to MSGQ_TCB.
14oct06,jln  added refCnt and deleterPendQ to msg_q for SMP
04oct04,aeg  added #ifndef _ASMLANGUAGE.
31aug04,pcm  integrated qJobLib.h
28sep04,fr   removed vMsgQCreate prototype (SPR 101349)
22mar04,dcc  added vMsgQCreate prototype.
26aug03,tcr  remove WindView InstClassId
06sep01,bwa  Added VxWorks events support.
19may98,drm  merged 3rd party code which added external declarations
             of distributed msgQ routines.
             - merged code was originally based on version 01d
17apr98,rlp  canceled MSG_Q modification for backward compatibility.
04nov97,rlp  modified MSG_Q structure for tracking messages sent.
16jan94,c_s  added extern declaration for msgQInstClassId.
22sep92,rrr  added support for c++
19jul92,pme  added external declaration of shared msgQ show routine.
04jul92,jcf  created.
*/

#ifndef __INCmsgQLibPh
#define __INCmsgQLibPh

#ifndef _ASMLANGUAGE
#include <vxWorks.h>
#include <vsbConfig.h>
#include <vwModNum.h>
#include <sllLib.h>
#include <msgQLib.h>
#include <classLib.h>

#include <private/qLibP.h>
#include <private/objLibP.h>
#include <private/eventLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
    {
    SL_LIST	list;		/* 0x00/0x00 */
    size_t	count;		/* 0x08/0x10 */
    Q_HEAD	pendQ;		/* 0x0c/0x18 */
    } MSG_Q_HEAD;		/* 0x1c/0x38 sizeof MSQ_Q_HEAD  */

/* If the size of MSG_Q changes please update VX_MSG_Q_SIZE in types/vxWind.h */

typedef struct msg_q		  /* MSG_Q */
    {
    OBJ_CORE	objCore;	  /* 0x00/0x00  object management */
    MSG_Q_HEAD	msgQ;		  /* 0x44/0x80  message queue head */
    MSG_Q_HEAD	freeQ;		  /* 0x60/0xb8  free message queue head */
    size_t	maxMsgs;	  /* 0x7c/0xf0  max number of messages in */
				  /* 		queue */
    size_t	maxMsgLength;	  /* 0x80/0xf8  max length of message */
    int		sendTimeouts;	  /* 0x84/0x100 number of send timeouts */
    int		recvTimeouts;	  /* 0x88/0x104 number of receive timeouts */
    EVENTS_RSRC	events;		  /* 0x8c/0x108 VxWorks events */
    Q_HEAD      deleterPendQ;     /* 0x98/0x118 deleter pend queue (SMP) */
    int		options;	  /* 0xa8/0x138 message queue options */
    atomic32_t 	refCnt;           /* 0xac/0x13c reference count for SMP */
    } MSG_Q;			  /* 0xb0/0x140 sizeof MSG_Q */

/*
 * If the size of MSG_NODE  changes please update VX_MSG_NODE_SIZE
 * in types/vxWind.h
 */

typedef struct				/* MSG_NODE */
    {
    SL_NODE		node;		/* 0x00/0x00 queue node */
    size_t		msgLength;	/* 0x04/0x08 number of bytes of data */
    MSG_Q *		pMsgQ;		/* 0x08/0x10 node's message queue */
    } MSG_NODE;				/* 0x0c/0x18 MSG_NODE size */

typedef struct				/* This structure is embedded */
    {					/* into the WIND_TCB structure. */
    char *		buffer;		/* 0x00/0x00 */
    MSG_NODE *	        node;		/* 0x04/0x08 */
    size_t		size;		/* 0x08/0x10 */

    /* shared by msgQ and POSIX mq */

    void *              refMsgQId;     /* 0x0c/0x18 msgQ/mq object being used */
    } MSGQ_TCB;			       /* 0x10/0x20 MSGQ_TCB size */

/* message priority hidden to public */

#define MSG_PRI_DONT_CARE       MSG_PRI_URGENT  /* head is faster */

#define	MSG_Q_RESTRICT_UNPEND	0x80000000
#define	MSG_Q_OPTIONS_MASK	(MSG_Q_TYPE_MASK |		\
				 MSG_Q_EVENTSEND_ERR_NOTIFY |	\
				 MSG_Q_INTERRUPTIBLE |          \
                                 MSG_Q_TASK_DELETION_WAKEUP)

/* macros */

#define MSG_NODE_DATA(pNode)   (((char *) pNode) + sizeof (MSG_NODE))

/* variable definitions */

extern CLASS_ID msgQClassId;		/* message queue class id */

/* function declarations */

extern STATUS	msgQTerminate	(MSG_Q_ID msgQId);
extern STATUS	msgQInit	(MSG_Q * pMsgQ, size_t maxMsgs,
				 size_t maxMsgLength, int options,
				 void * pMsgPool);
extern BOOL     msgQWritable    (MSG_Q_ID msgQId);

#ifdef _WRS_CONFIG_SMP

struct windTcb;

extern STATUS   msgQObjSafe	(MSG_Q_ID msgQId, BOOL isIntContext,
				 struct windTcb * pTcbCurrent);
extern void	msgQObjUnsafe	(MSG_Q_ID msgQId, BOOL flag, BOOL isIntContext,
				 BOOL safeCntFlag,
				 struct windTcb * pTcbCurrent);
#endif /* _WRS_CONFIG_SMP */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmsgQLibPh */
