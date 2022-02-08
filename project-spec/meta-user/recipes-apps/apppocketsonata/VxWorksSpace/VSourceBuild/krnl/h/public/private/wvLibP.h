/* wvLibP.h - WindView lib private header */

/*
 * Copyright (c) 1997-2007, 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may14,sdt  Move wvObjNameCurrentBuffAdd to wvLibSP.h
10feb10,tcr  update for 64bit
19jun07,tcr  add parameter to taskname event
19dec06,tcr  update for SMP-safe
22nov05,tcr  move hashtbl definitions out for use by POSIX trace
12mar04,tcr  postMortem features
09oct03,tcr  tidy up
17jul03,tcr  make hash table more generic
20apr98,cth  changed WV_LOG_HEADER def, reverted uploadTaskPriority to 01b
17apr98,cth  added type WV_LOG_HEADER, removed prototype of wvUpload
15apr98,cth  removed wvUploadTaskPriority, added wvUploadTaskPriorityCont
		 and wvUploadPathPriorityOnce
18dec97,cth  updated includes
16nov97,cth  created, derived from wvLib.h
*/

#ifndef __INCwvlibph
#define __INCwvlibph

#include <wvLib.h>
#include <sllLib.h>

#include <dataCollectorLib.h>
#include <private/wvUploadPathP.h>
#include <private/wvHashTblLibP.h>
#include <private/wvBufferP.h>
#include <private/eventDefsP.h>

#ifdef __cplusplus
extern "C" {
#endif


/* globals */

extern int      wvUploadTaskPriority;	   /* upload task priority */
extern size_t   wvUploadTaskStackSize;     /* upload task stack size (bytes) */
extern int      wvUploadTaskOptions;       /* upload task options */

/* defines */
 
#define WV_LOG_LIST_MAGIC               0x57764f6b
    

/*
 * This struct is the root of the WindView logs on the target
 */

typedef struct wvLogList
    {
    struct
        {
        SL_LIST         wvLogListHead;  /* List of wind View logs */
        PART_ID         memPart;        /* Partition logs are created in */
        int             numLogs;        /* Maximum number of logs in the list */
        UINT32          magic;          /* Should be WV_LOG_LIST_MAGIC */
        } hdr;
    VX_MUTEX_SEMAPHORE(listSem);        /* protect list */
    UINT32      checksum;
    } WV_LOG_LIST;


/*
 * This struct describes a single WindView log.
 */

typedef struct wvLog
    {
    SL_NODE             node;           /* list node */
    PART_ID             memPart;        /* mem partition log created in */
    BUFFER_ID           pEvtBuffer;     /* associated event buffer */
    char *              pConfigEvent;   /* config event, with log revision */
    size_t              configEventSize;
    WV_HASH_TBL *       pHashTbl;       /* hast table tasknames, rtp etc. */
    } WV_LOG;
    

typedef struct wvUploadTaskDescriptor
    {
    TASK_ID     uploadTaskId;           /* task id of this upload task */
    SEMAPHORE   uploadCompleteSem;      /* given iff buffers are emptied */
    BOOL        exitWhenEmpty;          /* if true task exits when buf empty */
    UPLOAD_ID	uploadPathId;		/* id of the upload path to host */
    WV_LOG *	pWvLog;		        /* id of the log to upload from */
    int		status;			/* indicate errors in up task */
    } WV_UPLOADTASK_DESC;


/* function declarations */

extern STATUS wvLogListValidate (WV_LOG_LIST * pLogList);


#ifdef __cplusplus
}
#endif

#endif /* __INCwvlibph*/
