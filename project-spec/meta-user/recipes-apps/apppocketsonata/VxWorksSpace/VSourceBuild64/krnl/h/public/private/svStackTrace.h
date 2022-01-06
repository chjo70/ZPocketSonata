/* svStackTrace.h - Stack trace library (System Viewer) */

/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* typedefs */
typedef struct sv_stacktrace_node
{
    event_t     evtId;
    unsigned short  flag; /* 0 disable, 1 enable */    
}SV_STACKTRACE_NODE;

typedef struct sv_list_node
{
    struct sv_list_node *  pNext;
    SV_STACKTRACE_NODE     stEnable;
} SV_LIST_NODE_T;


#define STACKTRACE_LIST_SIZE 128

#define EVENT_ID_TO_LIST(evtId) (evtId % (STACKTRACE_LIST_SIZE))

#define SV_MAX_CALLSTACK             128
#define SV_DEFAULT_CALLSTACK         32
#define SV_EVENT_CALLSTACK           1

STATUS stackTraceDestory(event_t evtId);

int    stackTraceFlagGet(event_t evtId);

STATUS stackTraceFlagSet(event_t evtId, int stFlag);

void stackTraceFilterStateSet(int enable);

int stackTraceFilterStateGet(void);

STATUS svStackTraceDepthSet(const unsigned int depth);

STATUS svStackTraceFilterTaskSet(TASK_ID tid);

STATUS svStackTraceFilterTaskClear();

size_t svStackTraceGet(void *data);
