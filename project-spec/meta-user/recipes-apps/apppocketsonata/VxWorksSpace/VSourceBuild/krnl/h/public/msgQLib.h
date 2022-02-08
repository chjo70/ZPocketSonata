/* msgQLib.h - message queue library header file */

/*
 * Copyright (c) 1984-2005, 2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02y,06may10,cww  Changed numMsg type params to size_t
02x,29apr10,pad  Moved extern C statement after include statements.
02w,11may09,cww  Add LP64 support
02v,29aug07,jmg  Use VX_MSG_NODE_SIZE rather then sizeof(MSG_NODE).
02u,07oct05,yvp  Used VX_OBJ_ALIGN_SIZE to align statically instantiated
                 objects (SPR 113405).
02t,30aug05,yvp  Reworked VX_MSG_Q macro to undo struct workaround.
02s,08aug05,yvp  Added VX_MSG_Q macro for static instantiation of MsgQ's.
                 Added prototype for msgQInitialize().
                 Updated copyright. #include now with angle brackets.
02r,04aug05,yvp  Added prototype for create/delete library init.
02q,26oct04,fr	 added msgQOpenInit() routine (SPR 101491)
02p,24oct03,aeg  moved common definitions with user side to msgQLibCommon.h
02o,20jun03,ymz  updated year of copyright.
02n,14mar03,dcc  moved MSG_Q_ID definition to types/vxWind.h.
02m,19oct01,bwa  Added MSG_Q_EVENTSEND_ERR_NOTIFY option.
02l,17apr98,rlp  canceled MSG_Q_INFO modification for backward compatibility.
02k,04nov97,rlp  modified MSG_Q_INFO structure for tracking messages sent.
02j,13jul93,wmd  use MEM_ROUND_UP to determine MSG_NODE_SIZE.
02i,22sep92,rrr  added support for c++
02h,04jul92,jcf  cleaned up.
01g,26may92,rrr  the tree shuffle
01f,04oct91,rrr  passed through the ansification filter
		  -changed copyright notice
01e,05oct90,dnw  changed MSG_Q_INFO structure.
01d,05oct90,dnw  changed function declarations for new interface.
01c,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01b,07aug90,shl  moved function declarations to end of file.
01a,10may90,dnw  written
*/

#ifndef __INCmsgQLibh
#define __INCmsgQLibh

#include <vxWorks.h>
#include <msgQLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE
/* macros */

/* 
 * The following macro determines the number of bytes needed to buffer
 * a message of the specified length.  The node size is rounded up for
 * efficiency.  The total buffer space required for a pool for
 * <maxMsgs> messages each of up to <maxMsgLength> bytes is:
 *
 *    maxMsgs * MSG_NODE_SIZE (maxMsgLength)
 * 
 * VX_MSG_NODE_SIZE is hardcoded in vxWind.h. Any time the size of MSG_NODE 
 * changes the value of VX_MSG_NODE_SIZE should be updated.
 */

#define MSG_NODE_SIZE(msgLength) \
	(MEM_ROUND_UP((VX_MSG_NODE_SIZE + msgLength)))

/* macros used to statically declare message queues */

/*******************************************************************************
*
* VX_MSG_Q - declare storage for a message queue
*
* This macro declares storage for a message queue with name <name>, that
* will have <max_msgs> messages, each of length <max_msg_len>. This macro 
* only generates data declarations for the message queue. To fully instantiate
* the message queue and make it ready for use, function msgQInitialize() must
* be called after using this macro. This macro is useful for declaring message 
* queues statically (i.e. at compile time, without using any dynamic memory 
* allocation at runtime).
*
* Sample usage of this macro is as follows:
* \cs
*      #include <vxWorks.h>
*      #include <msgQLib.h>
* 
*      VX_MSG_Q(myMsgQ,100,16);         /@ declare the msgQ @/
*      MSG_Q_ID myMsgQId;               /@ MsgQ ID to send/receive messages @/
* 
*      STATUS initializeFunction (void)
*          {
*          if ((myMsgQId = msgQInitialize (myMsgQ, 100, 16, options)) == NULL)
*               return (ERROR);      /@ initialization failed @/
*          else 
*               return (OK);
*          }
* \ce
* 
* SEE ALSO: msgQInitialize()
* \NOMANUAL
*/

#define VX_MSG_Q(name, max_msgs, max_msg_len)				\
    _WRS_DATA_ALIGN_BYTES(VX_OBJ_ALIGN_SIZE)                        	\
        char name [VX_MSG_Q_SIZE + ((max_msgs)*(MSG_NODE_SIZE(max_msg_len)))];

/* function declarations */

extern STATUS 	msgQLibInit		(void);
extern void	msgQCreateLibInit	(void);
extern MSG_Q_ID msgQInitialize		(char * pMsgQMem, size_t maxMsgs,
					 size_t maxMsgLength, int options);
extern void 	msgQShowInit		(void);
extern void	msgQOpenInit		(void);
extern STATUS 	msgQShow		(MSG_Q_ID msgQId, int level);
#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmsgQLibh */
