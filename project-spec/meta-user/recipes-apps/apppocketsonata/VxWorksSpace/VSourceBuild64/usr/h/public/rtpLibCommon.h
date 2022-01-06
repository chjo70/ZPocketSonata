/* rtpLibCommon.h - common RTP management definitions */

/* 
 * Copyright (c) 2003-2004, 2007, 2009-2010, 2017 Wind River Systems, Inc. 
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
09may17,npc  fixed PC checking for RTP in memEdrTrcPcValidate() (V7COR-5080)
25may10,cww  Added RTP_ID_ERROR
28apr10,pad  Moved extern C statement after include statements.
28dec09,jpb  Updated RTP_DESC.
03dec09,cww  LP64 adaptation
05apr07,pad  Added RTP_CPU_AFFINITY_NONE option (SMP).
16nov04,kk   increase VX_RTP_LENGTH to 255, removed pArg & pEnv
             from RTP_DESC (SPR# 102911)
27sep04,ans  code inspection comments.
22sep04,ans  renamed S_rtpLib_INVALID_OPTION to
             S_rtpLib_INVALID_TASK_OPTION
04jun04,job  Added RTP_LOADED_WAIT option
05may04,yvp  Added taskOptions parameter to rtpSpawn.
30apr04,tam  added RTP_BUFFER_VAL_OFF
27apr04,ans  Added RTP state and status.
08apr04,kk   remove mmList & sharedDataNode from RTP_DESC
11mar04,job  Added ACCESS_DENIED error value & changes error range
             to more sensibly start from 1.
19mar04,pad  Replaced option RTP_WITH_SYMBOLS with more complete set of
             options.
12mar04,pad  Added error numbers (shared library support).
22sep03,kk   moved rtpSpawn here, added rtpInfoGet()
15sep03,kk   created based on rtpLib.h
*/

#ifndef __INCrtpLibCommonh
#define __INCrtpLibCommonh

#include <vxWorks.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* creation mode options */

#define RTP_GLOBAL_SYMBOLS	0x01	/* register global symbols for RTP */
#define RTP_LOCAL_SYMBOLS	0x02	/* idem for local symbols */
#define RTP_ALL_SYMBOLS		(RTP_GLOBAL_SYMBOLS | RTP_LOCAL_SYMBOLS)
#define RTP_DEBUG		0x10	/* set RTP in debug mode when created */
#define RTP_BUFFER_VAL_OFF	0x20    /* disable buffer validation for all */
			    		/* system calls issued from the RTP  */
#define RTP_LOADED_WAIT         0x40    /* Wait until the RTP is loaded */ 
#define RTP_CPU_AFFINITY_NONE	0x80	/* Remove any CPU affinity (SMP) */

/* Error Status codes */

#define S_rtpLib_INVALID_FILE                   (M_rtpLib | 1)
#define S_rtpLib_INVALID_OPTION                 (M_rtpLib | 2)
#define S_rtpLib_ACCESS_DENIED                  (M_rtpLib | 3)
#define S_rtpLib_INVALID_RTP_ID			(M_rtpLib | 4)
#define S_rtpLib_NO_SYMBOL_TABLE		(M_rtpLib | 5)
#define S_rtpLib_INVALID_SEGMENT_START_ADDRESS	(M_rtpLib | 6)
#define S_rtpLib_INVALID_SYMBOL_REGISTR_POLICY	(M_rtpLib | 7)
#define S_rtpLib_INSTANTIATE_FAILED             (M_rtpLib | 8)
#define S_rtpLib_INVALID_TASK_OPTION            (M_rtpLib | 9)
#define S_rtpLib_RTP_NAME_LENGTH_EXCEEDED	(M_rtpLib | 10)	/* rtpInfoGet */

#define VX_RTP_NAME_LENGTH	255	/* max name length for diplay */

/* 
 * The 'status' field (32 bit integer) of a RTP holds the RTP state and status.
 *
 * NOTE: RTP_STATE_GET()   : read the RTP state(s)
 *       RTP_STATE_PUT()   : write the RTP state(s)
 *       RTP_STATE_SET()   : set a RTP state
 *       RTP_STATE_UNSET() : unset a RTP state
 *
 *       RTP_STATUS_GET()   : read the RTP status
 *       RTP_STATUS_PUT()   : write the RTP status
 *       RTP_STATUS_SET()   : set a RTP status
 *       RTP_STATUS_UNSET() : unset a RTP status
 *
 * The PUT/SET/UNSET macros are available only in the kernel headers.
 */

/* RTP states */

#define RTP_STATE_CREATE           0x0001     /* RTP is under construction */
#define RTP_STATE_NORMAL           0x0002     /* RTP is ready */
#define RTP_STATE_DELETE           0x0004     /* RTP is being deleted */

#define RTP_STATUS_STOP            0x0100 /* RTP has recieved stopped signal */
#define RTP_STATUS_ELECTED_DELETER 0x0200 /* RTP delete has started */

#define RTP_STATE_MASK            (RTP_STATE_CREATE | RTP_STATE_NORMAL | \
                                   RTP_STATE_DELETE)
#define RTP_STATUS_MASK           (RTP_STATUS_STOP | RTP_STATUS_ELECTED_DELETER)

#define RTP_STATE_GET(value) ((value) & RTP_STATE_MASK)
#define RTP_STATUS_GET(value) ((value) & RTP_STATUS_MASK)

/* Indicates that the RTP_ID returned is not valid. */

#define RTP_ID_ERROR ((RTP_ID)(-1))

/* IS_RTP_ macros */

#define IS_RTP_STATE_NORMAL(value) ((RTP_STATE_GET (value) & RTP_STATE_NORMAL) \
                                == RTP_STATE_NORMAL)
#define IS_RTP_STATE_CREATE(value) ((RTP_STATE_GET (value) & RTP_STATE_CREATE) \
                                == RTP_STATE_CREATE)
#define IS_RTP_STATE_DELETE(value) ((RTP_STATE_GET (value) & RTP_STATE_DELETE) \
                                == RTP_STATE_DELETE)
#define IS_RTP_STATUS_STOP(value) ((RTP_STATUS_GET (value) & \
                                      RTP_STATUS_STOP) == RTP_STATUS_STOP)
#define IS_RTP_STATUS_ELECTED_DELETER(value) ((RTP_STATUS_GET (value) & \
                      RTP_STATUS_ELECTED_DELETER) == RTP_STATUS_ELECTED_DELETER)

/* typedefs */

#ifndef _ASMLANGUAGE

/* 
 * Since the size of RTP_DESC is different in user & kernel space for 64bit
 * builds, we must have two different definitions for the kernel-side.  In this
 * definition of RTP_DESC, we want to define the task id & rtp id as being an id.  
 * On the user-side, we want to define the task id & rtp id as being handles.  
 * The other kernel definition is located in rtpLibP.h named RTP_USER_DESC.
 */ 

#define RTP_DESC_FIELDS(tidType, rtpType)				      \
    int		status;         /* the status field of the RTP */	      \
    UINT32	options;        /* option bits, e.g. debug, symtable */       \
    void *	entrAddr;       /* entry point of ELF file */                 \
    tidType	initTaskId;     /* the initial task ID */		      \
    rtpType	parentId;       /* RTP ID of the parent */		      \
    char        pathName[VX_RTP_NAME_LENGTH + 1]; /* path to RTP executable */\
    INT32	taskCnt;        /* number of tasks in the RTP */	      \
    void *	textStart;      /* start of text section */		      \
    void *	textEnd;        /* end of text section */

typedef struct 
    {
    RTP_DESC_FIELDS(TASK_ID, RTP_ID)
    } RTP_DESC;

/* forward declarations */

extern RTP_ID   rtpSpawn (const char * rtpFileName, const char * argv[], 
			  const char * envp[], int priority, size_t uStackSize, 
			  int options, int taskOptions);

extern STATUS	rtpInfoGet (RTP_ID rtpId, 
			    RTP_DESC * rtpStruct); 

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCrtpLibCommonh */
