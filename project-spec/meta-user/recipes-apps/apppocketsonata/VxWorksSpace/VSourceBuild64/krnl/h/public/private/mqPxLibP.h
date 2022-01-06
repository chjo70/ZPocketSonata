/* mqPxLibP.h - private POSIX message queue library header */

/*
 * Copyright (c) 1993-1994, 2003-2004, 2006-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement
 */

/*
modification history
--------------------
01v,23mar11,gls  modified mq_work to allow node parameter for SMP (WIND0259894)
01u,09aug10,cww  Updated mq_create nMsgs param
01t,04may10,jpb  Added prototypes from mqPxShow.  Changed msgq_bmap type to
                 UINT32.
01s,29apr10,pad  Moved extern C statement after include statements.
01r,23dec09,jpb  Updated for LP64 adaptation.
01q,02oct09,zl   include qLibP.h instead of qLib.h
01p,27aug08,jpb  Renamed VSB header file
01o,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01n,13aug07,lei  added safeCntFlag/isIntContext parameters to mqPxObjUnsafe;
                 added isIntContext parameter to _mq_send.
01m,10jul07,lei  added refCnt/deleterPendQ/pSendNode to msg_que; 
                 added mqPxObjSafe/Unsafe APIs.
01l,26apr06,kk   added the MQ_FLAG_XXX flags from mqPxLib.c
01k,12feb06,kk   remove unused routine _mq_close()
01j,03jan06,yvp  Added timeout parameter to _mq_send and _mq_receive to
                 support mq_timed(send/receive).
01i,28sep04,fr   removed mqPxCreateRtn prototype (SPR 101349)
01h,30mar04,dcc  updated to use posixated objLib.
01g,05dec03,m_s  code-inspection changes
01f,31oct03,m_s  removed symLib and added extern for class id
                 moved mq_des definition to public header file for Base 6
01e,20jun03,ymz  moved OBJ_CORE from mq_des to msg_que.
01d,24mar99,elg  mqLibInit() must be in mqueue.h (SPR 20532).
01c,03feb94,kdl  moved structure definitions from mqPxLib.c.
01b,12jan94,kdl  changed mqLibInit() to mqPxLibInit(); added defines for
		 default queue and message size.
01a,02dec93,dvs  written
*/

#ifndef __INCmqPxLibPh
#define __INCmqPxLibPh

#include <vsbConfig.h>
#include <stdarg.h>
#include <mqueue.h>
#include <private/qLibP.h>
#include <private/sigLibP.h>
#include <private/objLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

extern CLASS_ID mqClassId;             /* POSIX message queue class ID */

/* defines */

/* bit setting for the descriptor flags */

#define MQ_FLAG_READ          0x1    /* message queue open for reading */
#define MQ_FLAG_WRITE         0x2    /* message queue open for writing */
#define MQ_FLAG_NONBLOCK      0x4    /* message queue operations do not block */

/* message queue object */

struct msg_que
    {
    OBJ_CORE		 objCore;
    Q_HEAD		 msgq_cond_read;
    Q_HEAD		 msgq_cond_data;
    TASK_ID		 msgq_sigTask;
    struct sigpend	 msgq_sigPend;
    struct mq_sll_node * msgq_data_list[MQ_PRIO_MAX];
    struct mq_sll_node * msgq_free_list;
    struct mq_attr	 msgq_attr;
    UINT32		 msgq_bmap;
#ifdef _WRS_CONFIG_SMP
    atomic32_t           refCnt;           /* reference count for SMP */
    Q_HEAD               deleterPendQ;     /* deleter pend queue */
    BOOL                 msgQBeingDeleted; /* flag when mq being deleted */
#endif /* _WRS_CONFIG_SMP */
    };

/* message queue descriptor for kernel applications */

struct mq_des
    {
    struct msg_que * f_data;
    int              f_flag;
    };

/* a node to manage message buffer lists */

struct mq_sll_node
    {
    struct mq_sll_node * mq_sll_next;
    size_t	         mq_sll_size;
    unsigned int         mq_sll_node_prio;
    };

/* function declarations */

extern STATUS	mqPxLibInit	 (int hashSize);
extern ssize_t	_mq_receive	 (struct msg_que *	  pMq,
				  void *		  pMsg,
                                  size_t		  msgLen,
				  unsigned int *	  pMsgPrio,
				  BOOL			  nonBlock,
				  const struct timespec * abs_timeout);
extern int	_mq_send	 (struct		  msg_que * pMq,
				  const void *		  pMsg,
                                  size_t		  msgLen,
				  unsigned int		  msgPrio,
                                  BOOL			  nonBlock,
				  const struct timespec * abs_timeout,
                                  BOOL			  intContext);
extern int	_mq_notify	 (struct msg_que *	  pMq,
                                  const struct sigevent * pNotification);

extern OBJ_ID	mqPxDescObjIdGet (mqd_t  mqdes);
extern mqd_t	mq_create	 (size_t nMsgs, size_t msgSize);

#ifdef _WRS_CONFIG_SMP
extern STATUS   mqPxObjSafe	 (struct msg_que * pMq, BOOL isIntContext);
extern void     mqPxObjUnsafe	 (struct msg_que * pMq , BOOL deferFlag, 
				  BOOL isIntContext, BOOL safeCntFlag);
#endif /* _WRS_CONFIG_SMP */

/* show */

extern STATUS	mqPxShow	 (mqd_t mqDesc, int level);
extern STATUS	mqPxShowInit	 (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCmqPxLibPh */
