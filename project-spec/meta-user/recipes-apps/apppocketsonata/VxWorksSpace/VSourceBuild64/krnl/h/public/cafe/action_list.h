/* action_list.h - public api for cafe action lists */

/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCaction_list_h
#define INCaction_list_h

#ifdef __cplusplus
extern "C" {
#endif

#define CAFE_EAL_HANDLE_NULL	0

/*******************************************************************************
*
* cafe_event_action_list_alloc - allocate an empty list of actions
*
* This function also allocates a handle for the list in the event
* action list locking table.  This list should be deleted using
* cafe_event_action_list_release().
*
* Must be called with the cafe system lock acquired.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* SEE ALSO: cafe_strerror(), cafe_event_action_list_release()
*/
extern int cafe_event_action_list_alloc
	(
	const struct cafe_ep_inst *inst,
	struct cafe_event_descr *event,
	struct cafe_event_action_list **list_result,
	cafe_eal_handle_t *handle_result
	);

/*******************************************************************************
*
* cafe_event_action_list_release - release a reference to this list
*
* SEE ALSO: cafe_event_action_list_alloc()
*/
extern void cafe_event_action_list_release
	(
	cafe_eal_handle_t *handle
	);

/*******************************************************************************
*
* cafe_event_action_list_swap - atomically swap this list with a new list
*
* SEE ALSO: cafe_strerror(), cafe_event_action_list_release(),
* cafe_event_action_list_read_lock(), cafe_event_action_list_read_unlock()
*/
extern void cafe_event_action_list_swap
	(
	cafe_eal_handle_t *a,
	cafe_eal_handle_t b
	);

/*******************************************************************************
*
* cafe_event_action_list_read_lock - retrieve actions list and lock for reading
*
* Retrieve actions and lock for reading.
*
* RETURNS: event action list and a handle to use when unlocking the
* list.
*
* ERRNO: CAFE_OK on success, or a Cafe error code
*
* SEE ALSO: cafe_event_action_list_read_unlock()
*/
extern int cafe_event_action_list_read_lock
	(
	const cafe_eal_handle_t *action_list_handle,
	cafe_eal_handle_t *unlock_handle,
	struct cafe_event_action_list **action_list_ptr
	);

/*******************************************************************************
*
* cafe_event_action_list_read_unlock - unlock actions read lock
*
* Unlock actions read lock.
*
* RETURNS: event action list
*
* ERRNO: N/A
*/
extern void cafe_event_action_list_read_unlock
	(
	cafe_eal_handle_t action_list_handle
	);

/*******************************************************************************
*
* cafe_event_action_list_gc - garbage collect list instances
*
* Must be called with the cafe system lock acquired.
*
* ERRNO: N/A
*/
extern void cafe_event_action_list_gc(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INCaction_list_h */
