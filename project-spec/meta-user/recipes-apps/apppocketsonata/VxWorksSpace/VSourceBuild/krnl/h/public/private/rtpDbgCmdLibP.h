/* rtpDbgCmdLibP.h - RTP debug command facility private header */

/*
 * Copyright (c) 2008,2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01e,16dec10,v_r  Now sharing message queues options (def CQ:WIND00236124);
01d,01sep10,jpb  Added global variable pRtpDbgCmdSvc.
01c,24jun10,jmp  LP64 adaptation.
01c,28apr10,pad  Moved extern C statement after include statements.
01b,09apr08,v_r  Removed obsolete define leftovers.
01a,17jan08,dbt	 Written. Contains the private routine and interface prototypes
	  + v_r	 of the RTP debug command library (req CQ:WIND00004496).
*/

#ifndef __INCrtpDbgCmdLibPh
#define __INCrtpDbgCmdLibPh

#include <vxWorks.h>
#include <rtpLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

/* Supported command codes */

#define RTP_DBG_SPAWN_TASK	0
#define RTP_DBG_MALLOC		1
#define RTP_DBG_DIRECT_CALL	2
#define RTP_DBG_FUNC_CALL	3

/* Shared message queues options */

#define MSG_Q_CREATE_MODE           (OM_CREATE | OM_DELETE_ON_LAST_CLOSE)
#define MSG_Q_CREATE_OPTS           (MSG_Q_INTERRUPTIBLE | MSG_Q_FIFO)

#define RTP_DBG_CMD_LIB_NAME	    "RTP Debug Command"

/* Protocol error codes */

typedef enum rtp_dbg_cmd_status
    {
    RTP_DBG_CMD_ERR_RT = -1,		/* runtime error */
    RTP_DBG_CMD_OK,			/* all is fine */
    RTP_DBG_CMD_ERR_CANNOT_CREATE_TASK,	/* cannot create a new task */
    RTP_DBG_CMD_ERR_MISSING_RTP_SUPPORT,/* RTP dbg cmd not available in RTP */
    RTP_DBG_CMD_ERR_CALL_IN_PROGRESS,	/* function call already in progress */
    RTP_DBG_CMD_ERR_UNSUPPORTED_CMD,	/* the given cmd is unsupported */
    RTP_DBG_CMD_ERR_MALLOC_FAILED,	/* userspace malloc returned NULL */
    RTP_DBG_CMD_ERR_RTP_STOPPED,	/* RTP is stopped, cannot process cmd */
    RTP_DBG_CMD_ERR_INVALID_RTP,	/* the RTP is not a valid one */
    RTP_DBG_CMD_ERR_TIMEOUT 		/* timeout when recv. userspace reply */
    } RTP_DBG_CMD_STATUS;

/* Macros to easily use the facility services */

#define RTP_DBG_CMD_MALLOC	    ((RTP_DBG_CMD_SVC *) pRtpDbgCmdSvc)->malloc
#define RTP_DBG_CMD_FUNC_CALL	    ((RTP_DBG_CMD_SVC *) pRtpDbgCmdSvc)->funcCall
#define RTP_DBG_CMD_TASK_SPAWN	    ((RTP_DBG_CMD_SVC *) pRtpDbgCmdSvc)->taskSpawn
#define RTP_DBG_CMD_IS_AVAILABLE    (pRtpDbgCmdSvc != NULL)

/* Length of the buffer reserved for future commands/extensions */

#define RTP_DBG_CMD_BUF_SIZE	2048

/* Typedefs */

typedef enum rtp_dbg_cmd_opts
    {
    FORCED_CALL = 1
    } RTP_DBG_CMD_OPT;

/* 
 * This structure contains the list of services provided by the RTP debug
 * command facility. Combined with its pointer in funcBind{c,h}, it allows
 * decoupling while still allowing easy scalability (the modifications only need
 * to be done here, funcBind-related files being left untouched).
 */

typedef struct rtp_dbg_cmd_svc
    {
    RTP_DBG_CMD_STATUS	(* malloc)	(RTP_ID rtpId, size_t size, 
					 void ** pAddr, int timeout);
    RTP_DBG_CMD_STATUS	(* taskSpawn)	(RTP_ID rtpId, int priority, 
					 int options, size_t stackSize, 
					 FUNCPTR entryPt,
					 OBJ_HANDLE * pTaskHandle,
					 int timeout, _Vx_usr_arg_t arg1,
					 _Vx_usr_arg_t arg2,
					 _Vx_usr_arg_t arg3,
					 _Vx_usr_arg_t arg4,
					 _Vx_usr_arg_t arg5,
					 _Vx_usr_arg_t arg6,
					 _Vx_usr_arg_t arg7,
					 _Vx_usr_arg_t arg8,
					 _Vx_usr_arg_t arg9,
					 _Vx_usr_arg_t arg10);
    RTP_DBG_CMD_STATUS  (* funcCall)    (RTP_ID rtpId, FUNCPTR entryPt,
					 RTP_DBG_CMD_OPT opts, int timeout, 
					 _Vx_usr_arg_t arg1,
					 _Vx_usr_arg_t arg2,
					 _Vx_usr_arg_t arg3,
					 _Vx_usr_arg_t arg4,
					 _Vx_usr_arg_t arg5,
					 _Vx_usr_arg_t arg6,
					 _Vx_usr_arg_t arg7,
					 _Vx_usr_arg_t arg8,
					 _Vx_usr_arg_t arg9,
					 _Vx_usr_arg_t arg10);
    } RTP_DBG_CMD_SVC;

/* Function prototypes */

extern STATUS		    rtpDbgCmdLibInit    (void);
extern void		    rtpDbgCmdEnable	(void);
extern RTP_DBG_CMD_STATUS   rtpDbgCmdMemAlloc   (RTP_ID rtpId, size_t size, 
						 void ** pAddr, int timeout);
extern RTP_DBG_CMD_STATUS   rtpDbgCmdTaskSpawn  (RTP_ID rtpId, int priority, 
						 int options, size_t stackSize, 
						 FUNCPTR entryPt,
						 OBJ_HANDLE * pTaskHandle,
						 int timeout,
						 _Vx_usr_arg_t arg1, 
						 _Vx_usr_arg_t arg2,
						 _Vx_usr_arg_t arg3,
						 _Vx_usr_arg_t arg4,
						 _Vx_usr_arg_t arg5,
						 _Vx_usr_arg_t arg6,
						 _Vx_usr_arg_t arg7,
						 _Vx_usr_arg_t arg8,
						 _Vx_usr_arg_t arg9,
						 _Vx_usr_arg_t arg10);
extern RTP_DBG_CMD_STATUS   rtpDbgCmdFuncCall   (RTP_ID rtpId, FUNCPTR entryPt,
						 RTP_DBG_CMD_OPT opts,
						 int timeout, 
						 _Vx_usr_arg_t arg1,
						 _Vx_usr_arg_t arg2,
						 _Vx_usr_arg_t arg3, 
						 _Vx_usr_arg_t arg4,
						 _Vx_usr_arg_t arg5,
						 _Vx_usr_arg_t arg6, 
						 _Vx_usr_arg_t arg7,
						 _Vx_usr_arg_t arg8,
						 _Vx_usr_arg_t arg9, 
						 _Vx_usr_arg_t arg10);

/* Pointer on the RTP Debug Command Facility service array */

extern void * pRtpDbgCmdSvc;

#ifdef __cplusplus
}
#endif

#endif /* __INCrtpDbgCmdLibPh */
