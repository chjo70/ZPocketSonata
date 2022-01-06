/* erfLibP.h - Event Reporting Framework Library Private header */

/* 
 * Copyright (c) 2005, 2010, 2017 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
25sep17,ghs  Clean build warning
29jan10,h_k  LP64 adaptation.
27jun05,jmt  written
*/

/*
DESCRIPTION
This file provides the private definitions for the Event Reporting Framework.

INCLUDE FILES: erfLib.h
*/ 

#ifndef INCerfLibPh
#define INCerfLibPh

#include "erfLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define ERF_EVENT_QUEUE_ERROR  ((struct erfQueueStruct *)(-1))

/* typedefs */

struct eventHandlerStruct                    /* Event Handler Info */
    {
    UINT16                      flags;       /* processing flags */
    erfHandlerPrototype *       pHandler;    /* handler function */
    void *                      pUserData;   /* User Data Pointer */
    struct eventHandlerStruct * next;        /* next in list */
    };
    
struct erfQueueElementStruct
    {
    UINT16    eventCat;        /* Event Category */
    UINT16    eventType;       /* Event Type */
    void *    pEventData;      /* Pointer to Event Data */
    erfFreePrototype * pFreeFunc;   /* Func to free Event Data when done */    
    };
    
struct erfQueueStruct
    {
    UINT16    queueSize;      /* number of elements */
    UINT16    firstElement;   /* index number of first element */    
    UINT16    firstFreeElement;    /* index number of last element */
    SEM_ID    queueCount;     /* Counting semaphore for handling elements */
    TASK_ID   eventTaskId;    /* Event Task ID */
    struct erfQueueElementStruct data[1];    /* List of Event Records */    
    };
    

/* forward declarations */

UINT16 erfMaxCategoriesGet (void);
UINT16 erfMaxTypesGet (void);
UINT16 erfQueueSizeGet (void);

#ifdef __cplusplus
}
#endif

#endif /* INCerfLibPh */
