/* eventP.h - user-level event definitions */

/*
 * Copyright (c) 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01nov14,wzc  add share_h directory.(US46321)
23oct14,wzc  support RTP for Memory Analyzer.(US46321)
21oct10,tcr  created
*/

#ifndef __eventPh
#define __eventPh

#include <private/rtpEvtDefsP.h>
#include <private/eventPointLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int wvEvtAction;
extern unsigned int wvEvtActionInitialized;

/* We keep it until it is removed in memPartLib.c */
enum
    {
    svEventSetMemPartLib,
    svEventSetNumClasses
    };

#define EVENT_POINT_ACTION_INIT(ARG1)                   \
do {                                                    \
    SV_RTP_INST_INIT_T evt;                             \
    evt.wvEvtActionAddr = (unsigned int *)ARG1;         \
    (void)eventPointSwHandle(EVENT_RTP_INSTRUMENTED_INIT, &evt, sizeof evt); \
} while (0)
/* Usually it is called in RTP init routine. It does not meet race condition */
#define SV_RTP_ACTION_IS_SET(evtClass)                              \
    if (_WRS_UNLIKELY(wvEvtActionInitialized == 0))                 \
        {                                                           \
        EVENT_POINT_ACTION_INIT((&wvEvtAction));                    \
        wvEvtActionInitialized = 1;                                 \
        }                                                           \
    if (_WRS_UNLIKELY(wvEvtAction != 0))

/*
*
* SV_RTP_EVT_0 - SV event logging with no arguments
*
*/

#define SV_RTP_EVT_0(evtId, evtClass)                   \
do {                                                    \
     SV_RTP_ACTION_IS_SET(evtClass)                     \
        {                                               \
        (void)eventPointSwHandle(evtId, NULL, 0);       \
        }                                               \
} while ((0))


/*
*
* SV_RTP_EVT_1 - SV event logging with one argument
*
*/

typedef struct
    {
    unsigned long      	args [1];
    } SV_RTP_EVT_1_T;

#define SV_RTP_EVT_1(evtId, evtClass, ARG1)                     \
do {                                                            \
     SV_RTP_ACTION_IS_SET(evtClass)                             \
        {                                                       \
        SV_RTP_EVT_1_T evt;                                     \
        evt.args [0] = (_Vx_usr_arg_t)ARG1;                     \
        (void)eventPointSwHandle(evtId, &evt, sizeof evt);      \
        }                                                       \
} while ((0))

/*
*
* SV_RTP_EVT_2 - SV event logging with two arguments
*
*/

typedef struct
    {
    unsigned long      	args [2];
    } SV_RTP_EVT_2_T;

#define SV_RTP_EVT_2(evtId, evtClass, ARG1, ARG2)              \
do {                                                           \
     SV_RTP_ACTION_IS_SET(evtClass)                            \
        {                                                      \
        SV_RTP_EVT_2_T evt;                                    \
        evt.args [0] = (_Vx_usr_arg_t)ARG1;                    \
        evt.args [1] = (_Vx_usr_arg_t)ARG2;                    \
        (void)eventPointSwHandle(evtId, &evt, sizeof evt);     \
        }                                                      \
} while ((0))

/*
*
* SV_RTP_EVT_3 - SV event logging with three arguments
*
*/

typedef struct
    {
    unsigned long      	args [3];
    } SV_RTP_EVT_3_T;

#define SV_RTP_EVT_3(evtId, evtClass, ARG1, ARG2, ARG3)      \
do {						             \
     SV_RTP_ACTION_IS_SET(evtClass)		             \
        {						     \
        SV_RTP_EVT_3_T evt;				     \
        evt.args [0] = (_Vx_usr_arg_t)ARG1;		     \
        evt.args [1] = (_Vx_usr_arg_t)ARG2;		     \
        evt.args [2] = (_Vx_usr_arg_t)ARG3;		     \
        (void)eventPointSwHandle(evtId, &evt, sizeof evt);   \
        }						     \
} while ((0))


/*
*
* SV_RTP_EVT_4 - SV event logging with four arguments
*
*/

typedef struct
    {
    unsigned long      	args [4];
    } SV_RTP_EVT_4_T;

#define SV_RTP_EVT_4(evtId, evtClass, ARG1, ARG2, ARG3, ARG4)	\
do {								\
     SV_RTP_ACTION_IS_SET(evtClass)			\
        {							\
        SV_RTP_EVT_4_T evt;					\
        evt.args [0] = (_Vx_usr_arg_t)ARG1;			\
        evt.args [1] = (_Vx_usr_arg_t)ARG2;			\
        evt.args [2] = (_Vx_usr_arg_t)ARG3;			\
        evt.args [3] = (_Vx_usr_arg_t)ARG4;			\
        (void)eventPointSwHandle(evtId, &evt, sizeof evt);	\
        }							\
} while ((0))

/*
*
* SV_RTP_EVT_5 - SV event logging with five arguments
*
*/

typedef struct
    {
    unsigned long      	args [5];
    } SV_RTP_EVT_5_T;

#define SV_RTP_EVT_5(evtId, evtClass, ARG1, ARG2, ARG3, ARG4, ARG5)	\
do {									\
     SV_RTP_ACTION_IS_SET(evtClass)				\
        {								\
        SV_RTP_EVT_5_T evt;						\
        evt.args [0] = (_Vx_usr_arg_t)ARG1;				\
        evt.args [1] = (_Vx_usr_arg_t)ARG2;				\
        evt.args [2] = (_Vx_usr_arg_t)ARG3;				\
        evt.args [3] = (_Vx_usr_arg_t)ARG4;				\
        evt.args [4] = (_Vx_usr_arg_t)ARG5;				\
        (void)eventPointSwHandle(evtId, &evt, sizeof evt);		\
        }								\
} while ((0))

/*
*
* SV_RTP_EVT_6 - SV event logging with six arguments
*
*/

typedef struct
    {
    unsigned long      	args [6];
    } SV_RTP_EVT_6_T;

#define SV_RTP_EVT_6(evtId, evtClass, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)   	\
do {									 	\
     SV_RTP_ACTION_IS_SET(evtClass)					\
        {									\
        SV_RTP_EVT_6_T evt;							\
        evt.args [0] = (_Vx_usr_arg_t)ARG1;					\
        evt.args [1] = (_Vx_usr_arg_t)ARG2;					\
        evt.args [2] = (_Vx_usr_arg_t)ARG3;					\
        evt.args [3] = (_Vx_usr_arg_t)ARG4;					\
        evt.args [4] = (_Vx_usr_arg_t)ARG5;					\
        evt.args [5] = (_Vx_usr_arg_t)ARG6;					\
        (void)eventPointSwHandle(evtId, &evt, sizeof evt);			\
        }									\
} while ((0))

#ifdef __cplusplus
}
#endif


#endif /* __eventPh */

