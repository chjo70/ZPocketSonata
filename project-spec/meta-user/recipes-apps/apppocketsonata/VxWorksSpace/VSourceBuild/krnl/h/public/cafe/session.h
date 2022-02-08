/* session.h - public interface for a cafe session. */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCsession_h
#define INCsession_h

#ifdef __cplusplus
extern "C" {
#endif

/* Configuration sessions. */

/*******************************************************************************
*
* cafe_instrument_create - create a new session
*
* This routine creates a new session.
*
* Must be called with the cafe system lock acquired.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_instrument_create
	(
	const char *name,
	struct cafe_instrument **result
	);

/*******************************************************************************
*
* cafe_instrument_delete - delete a session
*
* This routine deletes a session.
*
* Must be called with the cafe system lock acquired.
*
* NOTE: In case this function needs to wait for any reason, then the
* cafe system lock will temporarily be release during the wait.  Care
* must be taken by callers to not expect the state of the cafe data
* structures to be the same before and after calling this function.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_instrument_delete
	(
	struct cafe_instrument *session
	);

/*******************************************************************************
*
* cafe_instrument_start - start all instances in session
*
* This routine starts all instances in the provided session.  All
* instances are stopped in case of error.
*
* Must be called with the cafe system lock acquired.
*
* NOTE: In case this function needs to wait for any reason, then the
* cafe system lock will temporarily be release during the wait.  Care
* must be taken by callers to not expect the state of the cafe data
* structures to be the same before and after calling this function.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_instrument_start
	(
	struct cafe_instrument *session
	);

/*******************************************************************************
*
* cafe_instrument_stop - stop all instances in session
*
* This routine stops all instances in the provided session.
*
* Must be called with the cafe system lock acquired.
*
* NOTE: In case this function needs to wait for any reason, then the
* cafe system lock will temporarily be release during the wait.  Care
* must be taken by callers to not expect the state of the cafe data
* structures to be the same before and after calling this function.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_instrument_stop
	(
	struct cafe_instrument *session
	);

/*******************************************************************************
*
* cafe_instrument_add_delete_listener - add callback when an instrument is deleted
*
* The listener routine is called to notify clients that an instrument
* is deleted.  Called with CAFE_LOCK taken.
*/
typedef void (*cafe_instrument_delete_listener)(struct cafe_instrument *session);
extern void cafe_instrument_add_delete_listener
	(
	cafe_instrument_delete_listener listener
	);

/*******************************************************************************
*
* cafe_instrument_disconnect_inst - disconnect all instances in session
*
* This routine disconnects all instances in the provided session.
*
* Must be called with the cafe system lock acquired.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern void cafe_instrument_disconnect_inst
	(
	struct cafe_instrument *session
	);

/*******************************************************************************
*
* cafe_instrument_delete_inst - delete all instances in session
*
* This routine deletes all instances in the provided session.
*
* Must be called with the cafe system lock acquired.
*
* NOTE: In case this function needs to wait for any reason, then the
* cafe system lock will temporarily be release during the wait.  Care
* must be taken by callers to not expect the state of the cafe data
* structures to be the same before and after calling this function.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_instrument_delete_inst
	(
	struct cafe_instrument *session
	);

extern struct cafe_instrument *cafe_instrument_iter_first
	(
	struct cafe_instrument_iter *iter
	);

extern struct cafe_instrument *cafe_instrument_iter_next
	(
	struct cafe_instrument_iter *iter
	);

extern int cafe_instrument_refresh_output_event_actions
	(
	struct cafe_instrument *session
	);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCsession_h */
