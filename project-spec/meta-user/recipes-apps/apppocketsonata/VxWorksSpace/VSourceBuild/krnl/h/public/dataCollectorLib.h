/* dataCollectorLib.h - data collector library header file */

/*
 * Copyright (c) 2008, 2010, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20oct15,gxu  dataCollectorLib cannot log without System Viewer(US68020).
29apr10,pad  Moved extern C statement after include statements.
10feb10,tcr  update for 64bit
25sep08,tcr  add support for ANY_EVENT triggers
19aug08,tcr  add function list
14aug08,tcr  remove surplus fields
16jul08,tcr  rename node
09jun08,tcr  remove DL_NODE
13may08,tcr  add typedef for data collector function
01may08,tcr  provide means of getting all collectors
01may08,aim  added dataCollectorStateSet()
18apr08,tcr  created
*/

#ifndef __dataCollectorLibh
#define __dataCollectorLibh

#include <vxWorks.h>
#include <private/eventDefsP.h>		/* event_t */


#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef struct data_collector * DATA_COLLECTOR_ID;

typedef void (DATA_COLLECTOR_FUNC_T)(DATA_COLLECTOR_ID dataCollector,
                                     const void * args, size_t size);

typedef int (DATA_COLLECTOR_FILTER_FUNC_T)(DATA_COLLECTOR_ID dataCollector,
                                           const void * args, size_t size);

typedef struct data_collector
    {
    struct list_node *          pListNode;
    event_t                     evtId;
    DATA_COLLECTOR_FUNC_T *     pDataCollector;
    size_t                      size;
    void *                      pWorkArea;
    DATA_COLLECTOR_FILTER_FUNC_T * pFilter;
    int                         enabled;
    const char *                pClientName;
    } DATA_COLLECTOR_T;

typedef struct
    {
    DATA_COLLECTOR_ID (*_func_dcCreate) (event_t evtId,
                       DATA_COLLECTOR_FUNC_T * pDataCollector, size_t size,
                       void * pWorkArea, DATA_COLLECTOR_FILTER_FUNC_T *pFilter,
                       int enabled, const char *client);
    STATUS (* _func_dcDelete) (DATA_COLLECTOR_ID pCollector);
    STATUS (* _func_dcRegister) (DATA_COLLECTOR_ID dataCollector);
    STATUS (* _func_dcUnregister)(DATA_COLLECTOR_ID pCollector);
    STATUS (* _func_dcStateSet) (DATA_COLLECTOR_ID pDataCollector, int enable);
    } DATA_COLLECTOR_FUNC_LIST_T;
    
/* function declarations */

extern STATUS dataCollectorLibInit (void);
extern DATA_COLLECTOR_ID dataCollectorFirstGet (event_t evtId);
extern DATA_COLLECTOR_ID dataCollectorNextGet (DATA_COLLECTOR_ID collector);

extern DATA_COLLECTOR_ID dataCollectorCreate (event_t evtId,
    DATA_COLLECTOR_FUNC_T * pDataCollector, size_t size, void * pWorkArea,
    DATA_COLLECTOR_FILTER_FUNC_T *pFilter, int enabled, const char *client);
extern STATUS dataCollectorRegister (DATA_COLLECTOR_ID dataCollector);
extern STATUS dataCollectorUnregister (DATA_COLLECTOR_ID pCollector);
extern STATUS dataCollectorDelete (DATA_COLLECTOR_ID pCollector);
extern DATA_COLLECTOR_ID dataCollectorEach (BOOL (*callee)(DATA_COLLECTOR_ID id,
                                                    int arg), int arg);
extern STATUS dataCollectorStateSet (DATA_COLLECTOR_ID pDataCollector, int enable);
extern void dataCollectorOn (void);
extern void dataCollectorOff (void);


/* allows quick check for presence of ANY_EVENT handlers */
    
extern int dataCollectorTrigAnyCnt;

#ifdef __cplusplus
}
#endif

#endif /* __dataCollectorLibh */

