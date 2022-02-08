/* top */

/*
 * Copyright (c) 2008, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05mar14,wzc  change XXX to WRS_XXX in comments.(WB4-2879)
27may08,aim  created
*/

#ifndef __INCtopLibh
#define __INCtopLibh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/*
 * The maximum number of tasks the top daemon and therefore any top
 * client can monitor.
 */

#ifndef TOP_MAX_TASKS
#define TOP_MAX_TASKS  128
#endif

typedef enum
    {
    TOP_IDLE    = 0,
    TOP_INTR    = 1,
    TOP_TASK    = 2,
    TOP_NSTATES = 3
    } TOP_STATE_T;

/* WRS_XXX: currently a 64-bit value but typedef'ed here in case we change
 * our mind.
 */
typedef UINT64 topTick_t;

/* Opaque handle for top clients. */

typedef struct topClient TOP_CLIENT_ID;

typedef struct
    {
    int		tid;		 /* task id */
    topTick_t	totalTicks;	 /* total ticks */
    topTick_t   incTicks;	 /* incremental ticks */
    topTick_t   totalTaskEPHits; /* total event points hit */
    topTick_t   incTaskEPHits;	 /* incremental event points hit */
    } TOP_TASK_DATA_T;

typedef struct
    {
    topTick_t		totalTicks      [TOP_NSTATES];
    topTick_t		sumTotalTicks;
    topTick_t		totalEPHits     [TOP_NSTATES];
    topTick_t		sumTotalEPHits;
    topTick_t		incEPHits       [TOP_NSTATES];
    topTick_t		sumIncEPHits;
    topTick_t		incTicks        [TOP_NSTATES];
    topTick_t		sumIncTicks;
    int			nTasks;	/* number of tasks in taskList[] */
    TOP_TASK_DATA_T	taskList        [TOP_MAX_TASKS];
    int			totalTasksCreated; /* total tasks created */
    int			totalTasksDeleted; /* total tasks deleted */
    int			incTasksCreated; /* inc new tasks */
    int			incTasksDeleted; /* inc deleted tasks */
    } TOP_PERF_DATA_T;


extern STATUS   topLibInit  (void);
extern STATUS   topShowInit (void);

extern int      topClkStop (void);
extern STATUS   topClkStart (FUNCPTR printRtn);
extern BOOL     topClkIsRunning (void);

extern STATUS   topClientCreate (TOP_CLIENT_ID **ppClient);

extern STATUS	topClientUpdate (TOP_CLIENT_ID *pClient,
				 TOP_PERF_DATA_T *pPerfData);

extern STATUS	topClientDelete (TOP_CLIENT_ID **ppClient);

extern void	topTaskListSort (TOP_TASK_DATA_T array[], int length);

#ifdef __cplusplus
}
#endif

#endif /* __INCtopLibh */
