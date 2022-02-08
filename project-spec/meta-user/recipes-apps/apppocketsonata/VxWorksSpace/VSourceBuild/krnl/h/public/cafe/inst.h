/* inst.h - configuration instance public interface */

/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCinst_h
#define INCinst_h

#ifdef __cplusplus
extern "C" {
#endif

/* Configuration instances. */

extern int cafe_ep_inst_create
	(
	struct cafe_instrument *session,
	const struct cafe_ep_spec *spec,
	unsigned int n_settings,
	const struct cafe_cfg_setting *settings,
	struct cafe_ep_inst **result
	);

/*******************************************************************************
*
* cafe_ep_inst_delete - deleted EP instance
*
* This routine will delete the specified EP instance.
*
* Must be called with the cafe system lock acquired.
*
* NOTE: In case deleting the EP instance needs to wait for any reason,
* then the cafe system lock will temporarily be release during the
* wait.  Care must be taken by callers to not expect the state of the
* cafe data structures to be the same before and after calling this
* function.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/

extern int cafe_ep_inst_delete
	(
	struct cafe_ep_inst *inst
	);

/*******************************************************************************
*
* cafe_ep_inst_connect - connect two Cafe configurations together
*
* This routine connects the output of one configuration to the input of
* another.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_ep_inst_connect
	(
	struct cafe_ep_inst *source,
	struct cafe_ep_inst *sink
	);

/*******************************************************************************
*
* cafe_ep_inst_disconnect - disconnect two Cafe configurations
*
* This routine disconnects two configuratiuons.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_ep_inst_disconnect
	(
	struct cafe_ep_inst *source,
	struct cafe_ep_inst *sink
	);

/*******************************************************************************
*
* cafe_ep_inst_disconnect_all - disconnect all connections for instance
*
* This routine disconnects connections to all source and sink
* instances for the provided instance.
*
* RETURNS:
*
* ERRNO:
*/
extern void cafe_ep_inst_disconnect_all
	(
	struct cafe_ep_inst *inst
	);

extern struct cafe_ep_inst * cafe_ep_inst_iter_first
	(
	struct cafe_instrument *session,
	struct cafe_ep_inst_iter *iter
	);

extern struct cafe_ep_inst *cafe_ep_inst_iter_next
	(
	struct cafe_ep_inst_iter *iter
	);

/*******************************************************************************
*
* cafe_ep_inst_start - start EP instance
*
* This routine will start the specified EP instance.  The
* start_notifier callback in struct cafe_instrument is called to
* notify that the instance was started.
*
* Must be called with the cafe system lock acquired.
*
* NOTE: In case starting the EP instance needs to wait for any reason,
* then the cafe system lock will temporarily be release during the
* wait.  Care must be taken by callers to not expect the state of the
* cafe data structures to be the same before and after calling this
* function.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/

extern int cafe_ep_inst_start
	(
	struct cafe_ep_inst *inst
	);

/*******************************************************************************
*
* cafe_ep_inst_stop - stop EP instance
*
* This routine will stop the specified EP instance.  The stop_notifier
* callback in struct cafe_instrument is called to notify that the
* instance was stopped.
*
* Must be called with the cafe system lock acquired.
*
* NOTE: In case stopping the EP instance needs to wait for any reason,
* then the cafe system lock will temporarily be release during the
* wait.  Care must be taken by callers to not expect the state of the
* cafe data structures to be the same before and after calling this
* function.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/

extern int cafe_ep_inst_stop
	(
	struct cafe_ep_inst *inst
	);

/*******************************************************************************
*
* cafe_ep_inst_state_started - EP callback function to notify that EP is started
*
* This routine is used by event point implementations with a defined
* start handler to notify that the EP instance is started.
*
* Must be called with the cafe system lock acquired.
*
* RETURNS:
*
* ERRNO:
*/

extern void cafe_ep_inst_state_started
	(
	struct cafe_ep_inst *inst
	);

/*******************************************************************************
*
* cafe_ep_inst_state_stopped - EP callback function to notify that EP is stopped
*
* This routine is used by event point implementations with a defined
* stop handler to notify that the EP instance is stopped.
*
* Must be called with the cafe system lock acquired.
*
* RETURNS:
*
* ERRNO:
*/

extern void cafe_ep_inst_state_stopped
	(
	struct cafe_ep_inst *inst
	);

/*******************************************************************************
*
* cafe_ep_inst_event_action_info_find - get existing event action info for event
*
* This function returns an instance and event description specific
* event action info struct, if one exists.
*
* RETURNS: Pointer to struct, or NULL
*
* ERRNO:
*/

struct cafe_event_action_info *cafe_ep_inst_event_action_info_find(
	const struct cafe_ep_inst *inst, const struct cafe_event_descr *event);


/*******************************************************************************
*
* cafe_ep_inst_event_action_info_get - get instance event action info for event
*
* This function returns an instance and event description specific
* object to be passed to the event action handler.  Multiple calls to
* this function with the same inst and event arguments will return the
* same object.
*
* The resulting event action object contains a orthogoal data map
* (odmap) from the expected order of the input event to the actual
* order of the generated event.  It also contains a copy of the
* impl_data pointer from the matching entry in the input_events list.
*
* The returned object is deleted when the instance is deleted.
*
* Must be called with the cafe system lock acquired.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_ep_inst_event_action_info_get(
	struct cafe_ep_inst *inst,
	struct cafe_event_descr *event,
	struct cafe_event_action_info **result);

extern int cafe_ep_inst_event_action_info_get2(
	struct cafe_ep_inst *inst,
	struct cafe_event_descr *event,
	struct cafe_event_descr *input_event,
	void *impl_data,
	struct cafe_event_action_info **result);

/*******************************************************************************
*
* cafe_ep_inst_get_sink_event_actions - get event actions for connected sinks
*
* This function iterates over all direct sinks to add event action
* handler to the provided list.
*
* The instance argument is usually the same instance that created the
* event action list, but they may be different when an immediate sink
* want to propagate the action to its sinks without taking any action.
*
* Must be called with the cafe system lock acquired.
*
* RETURNS: CAFE_OK, or Cafe error code
*
* ERRNO:
*/
extern int cafe_ep_inst_get_sink_event_actions(
	struct cafe_ep_inst *inst,
	struct cafe_event_action_list *actions);

extern int cafe_ep_inst_enable_output_event(
	struct cafe_ep_inst *inst,
	struct cafe_event_descr *event);

extern int cafe_ep_inst_disable_output_event(
	struct cafe_ep_inst *inst,
	const struct cafe_event_descr *event);

extern int cafe_ep_inst_inject_event(
	struct cafe_ep_inst *inst,
	struct cafe_event_descr *event,
	void *data[]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCinst_h */
