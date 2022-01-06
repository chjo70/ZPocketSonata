/* erfLib.h - Event Reporting Framework Library */

/*
 * Copyright (c) 2005, 2010, 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
25sep17,ghs  Clean build warning
17nov14,yjl  Provide a VSB or cdf parameter to change the stack size of
             "tErfTask" task (V7STO-205)
29jan10,h_k  LP64 adaptation.
24jun05,jmt  Allow multiple tasks and auto unregistration
01sep05,mil  Fixed build warning on useless keyword/empty declaration.
17may05,jmt  Update after Design review
23mar05,jmt  Continue implementation after initial review
16mar05,jmt  written
*/

/*
DESCRIPTION
This module provides an Event Reporting Framework for use by other
libraries.

INCLUDE FILES: vwModNum.h
*/

#ifndef INCerfLibh
#define INCerfLibh

#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* erfHandlerRaise "procType" defines */
#define ERF_ASYNC_PROC              0    /* Asynchronous (delayed) proc */
#define ERF_SYNC_PROC               1    /* Synchronous (immediate) proc */
#define ERF_PROC_TYPE_MAX           ERF_SYNC_PROC    /* for range checking */

/* erfHandlerRegister Event Processing flags Defines */
#define ERF_FLAG_NONE               0    /* No options needed */
#define ERF_FLAG_AUTO_UNREG         1    /* Auto Unregister after event */
#define ERF_FLAG_MAX                ERF_FLAG_AUTO_UNREG /* for range checking */

/* Event Category and Type Defines */
#define ERF_NUM_SYSTEM_CATEGORIES   1
#define ERF_MAX_NUM_SYSTEM_TYPES    3    /* must include T_erfLib_ALL_TYPES */

/* Globally defined Types */
#define T_erfLib_ALL_TYPES          0

/* Test Event Category and related types */
#define C_erfLib_TEST_CATEGORY      0
#define T_erfLib_TEST_0_TYPE        1
#define T_erfLib_TEST_1_TYPE        2

/* errno defines */
#define S_erfLib_INVALID_PARAMETER      (M_erfLib | 0x0001)
#define S_erfLib_MEMORY_ERROR           (M_erfLib | 0x0002)
#define S_erfLib_INIT_ERROR             (M_erfLib | 0x0003)
#define S_erfLib_TOO_MANY_USER_CATS     (M_erfLib | 0x0004)
#define S_erfLib_TOO_MANY_USER_TYPES    (M_erfLib | 0x0005)
#define S_erfLib_HANDLER_NOT_FOUND      (M_erfLib | 0x0006)
#define S_erfLib_QUEUE_EMPTY            (M_erfLib | 0x0007)
#define S_erfLib_QUEUE_FULL             (M_erfLib | 0x0008)
#define S_erfLib_QUEUE_ALREADY_CREATED  (M_erfLib | 0x0009)
#define S_erfLib_AUTO_UNREG_ERROR       (M_erfLib | 0x000A)


/* typedefs */

typedef void erfHandlerPrototype (UINT16 maxUserCat, UINT16 maxUserType,
                                  void * pEventData, void * pUserData);

typedef void erfFreePrototype (void * __ptr);

/* forward declarations */

STATUS erfLibInit (UINT16 maxUserCat, UINT16 maxUserType, size_t taskStackSize);
UINT16 erfMaxCategoriesGet(void);
UINT16 erfMaxTypesGet(void);
UINT16 erfQueueSizeGet(void);
STATUS erfHandlerRegister(UINT16 eventCat, UINT16 eventType,
                          erfHandlerPrototype * pEventHandler,
                          void * pUserData, UINT16 flags);
STATUS erfHandlerUnregister(UINT16 eventCat, UINT16 eventType,
                            erfHandlerPrototype * pEventHandler,
                            void * pUserData);

STATUS erfCategoryAllocate(UINT16 * pEventCat);
STATUS erfCategoryQueueCreate(UINT16 pEventCat, size_t queueSize, int priority);
STATUS erfTypeAllocate(UINT16 eventCat, UINT16 * pEventType);
UINT16 erfCategoriesAvailable(void);
UINT16 erfTypesAvailable(UINT16 eventCat);

STATUS erfEventRaise(UINT16 eventCat, UINT16 eventType, int procType,
                     void * pEventData, erfFreePrototype * pFreeFunc);

#ifdef __cplusplus
}
#endif

#endif /* INCerfLibh */
