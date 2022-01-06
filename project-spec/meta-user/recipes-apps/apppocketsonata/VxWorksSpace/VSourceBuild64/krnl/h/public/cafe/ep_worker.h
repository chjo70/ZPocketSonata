/* ep_worker.h - public interface for event processor worker thread library. */

/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCep_worker_h
#define INCep_worker_h


#include <cafe/stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

struct cafe_ep_worker;

/*******************************************************************************
*
* cafe_ep_worker_create - create a new worker thread
*
* This routine creates a new worker thread instance.
*
* NOTE: This routine requires CAFE_LOCK to be taken.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_ep_worker_create
	(
	const char *thread_name,
	struct cafe_ep_inst *inst,
	void (*client_func)(void *client_data),
	void *client_data,
	struct cafe_ep_worker **result
	);

/*******************************************************************************
*
* cafe_ep_worker_delete - delete worker thread
*
* This routine deletes worker thread instance.
*
* NOTE: This routine requires CAFE_LOCK to be taken.  It may
* temporarily release the CAFE_LOCK while waiting for the worker
* thread to finish.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
void cafe_ep_worker_delete
	(
	struct cafe_ep_worker *worker
	);

int cafe_ep_worker_start
	(
	struct cafe_ep_worker *worker
	);

int cafe_ep_worker_stop
	(
	struct cafe_ep_worker *worker
	);

void cafe_ep_worker_abort
	(
	struct cafe_ep_worker *worker
	);

int cafe_ep_worker_wait(
	struct cafe_ep_worker *worker);

bool cafe_ep_worker_isrunning
	(
	struct cafe_ep_worker *worker
	);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCep_worker_h */
