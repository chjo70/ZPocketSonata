/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* Public Cafe types. */

#ifndef INCtypes_h
#define INCtypes_h

#include <stdlib.h>		/* size_t */
#include <limits.h>
#include <cafe/ccdiff.h>
#include <cafe/list.h>
#include <cafe/value_type.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cafe_ep_inst;
struct cafe_event_action_info;

typedef void (*CAFE_ACTION_HANDLER)(struct cafe_event_action_info *event_info,
				    void **event_data);

/* eal = Event Action List */
typedef unsigned long cafe_eal_handle_t;

struct cafe_event_descr {
	unsigned int num_types;
	struct cafe_value_type *types[1];
};

struct cafe_event_descr_list {
	unsigned int max;
	unsigned int ind;
	struct cafe_event_descr **list;
};

struct cafe_enabled_event {
	struct cafe_event_descr *event;
	void *impl_data;
};

struct cafe_enabled_event_list {
	unsigned int max;
	unsigned int ind;
	struct cafe_enabled_event *list;
};

struct cafe_event_action {
	CAFE_ACTION_HANDLER handler;
	struct cafe_event_action_info *info;
};

struct cafe_event_action_list {
	struct cafe_event_descr *event;
	unsigned int max;
	unsigned int ind;
	struct cafe_event_action *list;
	const struct cafe_allocator *allocator;
};

enum {
	CAFE_ODMAP_NONE = (INT_MAX),
	CAFE_ODMAP_LAST = (INT_MAX-1)
};

struct cafe_event_action_info {
	struct cafe_ep_inst *inst;
	struct cafe_event_descr *event;
	unsigned int *odmap;
	void *impl_data;
	cafe_eal_handle_t sink_actions;
};

struct cafe_event_action_info_list {
	unsigned int max;
	unsigned int ind;
	struct cafe_event_action_info **list;
};

struct cafe_value_type_pair {
	const char *str;
	struct cafe_value_type *vt;
};

struct cafe_cfg_setting {
	const char *name;
	cafe_any_value value;
};

#define CAFE_INPEV_INIT(EVENT_NAME)				\
	{CAFE_NELEMENTS(EVENT_NAME##_TYPE), EVENT_NAME##_TYPE}

#define CAFE_INPEV_INIT2(EVENT_NAME, IMPL_DATA)				\
	{CAFE_NELEMENTS(EVENT_NAME##_TYPE), EVENT_NAME##_TYPE, IMPL_DATA}

struct cafe_ep_spec_input_evt {
	unsigned int num_types;
	const char **type;
	void *impl_data;
};

struct cafe_ep_spec_output_od_set {
	int length;
	int *od_items;
};

#define CAFE_OUTEV_INIT(TYPE) {(TYPE)}

#define CAFE_OUTEV_INIT2(TYPE, IMPL_DATA) {(TYPE), (IMPL_DATA), 0}

#define CAFE_OUTEV_INIT3(TYPE, IMPL_DATA, OD_SET_IDX) {(TYPE), (IMPL_DATA), OD_SET_IDX}

struct cafe_ep_spec_output_evt {
	const char *type;
	void *impl_data;
	int od_set_idx;
};

struct cafe_ep_inst_edge {
	struct cafe_ep_inst		*source;
	struct cafe_ep_inst		*sink;
	struct cafe_list_head		source_list;
	struct cafe_list_head		sink_list;
};


enum cafe_log_level {
	CAFE_LOG_ERROR,
	CAFE_LOG_WARNING,
	CAFE_LOG_INFO
};


struct cafe_instrument {
	const struct cafe_allocator	*allocator;
	char				*name;
	struct cafe_namespace		*ns;
	struct cafe_value_type		*wildcard_type;
	struct cafe_event_descr_list	events;
	struct cafe_list_head		session_list;
	struct cafe_list_head		inst_list_head;
	unsigned long			output_event_action_change_count;

	/* Called when the instance state becomes
	 * CAFE_EP_INST_STATE_STARTED.  Called with CAFE_LOCK
	 * taken. */
	void (*start_notifier)(struct cafe_ep_inst *inst);

	/* Called when the instance state becomes
	 * CAFE_EP_INST_STATE_STOPPED.  Called with CAFE_LOCK
	 * taken. */
	void (*stop_notifier)(struct cafe_ep_inst *inst);

	/* Called when error occurs during event dispatch.  Called on
	 * the input execution context of the instance. Error is a
	 * cafe error. */
	void (*error_notifier)(struct cafe_ep_inst *inst, int error);

	/* Called when an instance wants to announce a status message during
	   event dispatch */
	void (*status_notifier)(struct cafe_ep_inst *inst,
				enum cafe_log_level l, const char *msg);
};

enum {
	CAFE_EP_INST_STATE_INIT,
	CAFE_EP_INST_STATE_STOPPED,
	CAFE_EP_INST_STATE_STARTED,
	CAFE_EP_INST_STATE_STOPPING,
	CAFE_EP_INST_STATE_STARTING,
	CAFE_EP_INST_STATE_DELETING
};

enum {
	CAFE_EP_INST_FLAG_INPUT_ANY_CTX = 1,
	CAFE_EP_INST_FLAG_OUTPUT_INST_THREAD = CAFE_EP_INST_FLAG_INPUT_ANY_CTX*2,
	CAFE_EP_INST_FLAG_OUTPUT_SESSION_THREAD = CAFE_EP_INST_FLAG_OUTPUT_INST_THREAD*2
};

#define CAFE_EXEC_CTX_ANY ((struct cafe_ep_inst *)1)
#define CAFE_EXEC_CTX_SESSION ((struct cafe_ep_inst *)2)

struct cafe_ep_inst {
	const struct cafe_allocator	*allocator;
	const struct cafe_ep_spec	*spec;
	struct cafe_instrument		*session;
	volatile int			state;
	int				order;
	int				flags;
	struct cafe_ep_inst		*input_ctx;
	struct cafe_ep_inst		*output_ctx;

	/* Type of workarea, same as workarea->type. */
	struct cafe_value_type		*workarea_type;

	/* Workarea data structure. */
	struct cafe_value_data		*workarea;

	struct cafe_list_head		source_list_head;
	struct cafe_list_head		sink_list_head;
	void				*client_data;
	struct cafe_enabled_event_list	enabled_output_events;
	struct cafe_list_head		session_inst_list;
	struct cafe_event_action_info_list event_action_data_list;

	/* Array of input event descriptors.  The size and order are
	 * the same as input_events in cafe_ep_spec */
	struct cafe_event_descr		**input_events;

	/* Array of output event types.  The size and order are
	 * same as output_events in cafe_ep_spec */
	struct cafe_value_type		**output_events;

	/* Array of output orthogonal data types.  The size and order
	 * are the same as output_odata in cafe_ep_spec */
	struct cafe_value_type		**output_odata;
};

struct cafe_ep_spec {
	const char			*name;
	int  (*create_inst)(struct cafe_ep_inst *);
	void (*delete_inst)(struct cafe_ep_inst *);
	int  (*start)(struct cafe_ep_inst *);
	int  (*stop)(struct cafe_ep_inst *);
	int  (*get_input_event_actions)(struct cafe_ep_inst *,
					struct cafe_event_descr *event,
					struct cafe_event_action_list *actions);
	int  (*update_output_event_actions)(struct cafe_ep_inst *);
	int  (*inject_event)(struct cafe_ep_inst *inst,
			     struct cafe_event_descr *event,
			     void *data[]);
	const char			*types;
	const char			*workarea;
	unsigned int			 n_input_events;
	struct cafe_ep_spec_input_evt	*input_events;
	unsigned int			 n_output_events;
	struct cafe_ep_spec_output_evt	*output_events;
	unsigned int			 n_output_odata;
	const char			**output_odata;

	/* Flush pre-commit values to the workarea in an EP-specific manner.
	 * EPs which don't need to process setting values should leave this as
	 * NULL. */
	int (*settings_commit)          (struct cafe_ep_inst *,
					 unsigned int num_settings,
					 const struct cafe_cfg_setting []);
	/* State changed on input context instance. This routine is
	 * called on the thread that is used to dispatch any other
	 * events for the input_ctx EP instance.  For start, it will
	 * be called before any events are dispatched and for stop, it
	 * will be called when no more events will be dispatched. */
	void (*input_state_change)(struct cafe_ep_inst *);
	unsigned int                     n_output_odata_sets;
	struct cafe_ep_spec_output_od_set *output_odata_sets;

	struct cafe_list_head		spec_list;
	int (*dynamic_output_events)(struct cafe_ep_inst *inst, char **typep);
	/* Request event dispatching to be stopped.  This routine is
	 * typically called from an event sink while processing a
	 * dispatched event.  The routine cafe_ep_inst_stop() cannot
	 * be used as it waits for the stop to complete and therefore
	 * would cause deadlock. */
	int (*stop_dispatch)(struct cafe_ep_inst *inst);
};

struct cafe_ep_spec_iter {
	/* The following fields are private and read-only.
	 * Don't modify them. */
	struct cafe_ep_spec *current_spec;
};

struct cafe_instrument_iter {
	/* The following fields are private and read-only.
	 * Don't modify them. */
	struct cafe_instrument *current_session;
};

struct cafe_ep_inst_iter {
	/* The following fields are private and read-only.
	 * Don't modify them. */
	struct cafe_list_head *list_head;
	struct cafe_list_head *list_entry;
};

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INCtypes_h */
