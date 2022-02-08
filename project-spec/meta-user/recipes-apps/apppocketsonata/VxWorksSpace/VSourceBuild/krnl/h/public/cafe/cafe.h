/* cafe.h - Wind River Common Analysis FramEwork */

/*
 * Copyright (c) 2010-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCcafe_h
#define INCcafe_h

/*
DESCRIPTION

The Cafe analysis framework provides a means of getting information
out of a running system. Actions can be attached to particular events,
which can result in aggregation of large quantities of data into
manageable information.

INCLUDE FILES: cafe/cafe.h

SEE ALSO: dict, inst, value_type, dict, session
*/

#include <cafe/allocator.h>
#include <cafe/ccdiff.h>	/* C compiler differences */
#include <cafe/inttypes.h>	/* C9x integer types */
#include <cafe/stdbool.h>	/* C9x boolean type */
#include <cafe/library.h>	/* general Cafe library functions */
#include <cafe/types.h>		/* Cafe public data types */
#include <cafe/session.h>	/* Configuration session */
#include <cafe/spec.h>		/* Configuration specification */
#include <cafe/inst.h>		/* Configuration instance */
#include <cafe/action_list.h>	/* Cafe action lists */
#include <cafe/lock.h>		/* Cafe lock/unlock functions */
#include <cafe/value_type.h>
#include <cafe/dict.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The CAFE_VERSION_NUMBER resolves to an integer with the value
 * (X*1000000 + Y*1000 + Z) where X, Y, and Z are the major version,
 * minor version, and micro number.
 */
#define CAFE_MAJOR_VER_NUMBER	0
#define CAFE_MINOR_VER_NUMBER	1
#define CAFE_MICRO_VER_NUMBER	0

#define CAFE_VERSION_NUMBER			\
	((CAFE_MAJOR_VER_NUMBER * 1000000) +	\
	 (CAFE_MINOR_VER_NUMBER * 1000) +	\
	 CAFE_MICRO_VER_NUMBER)

#define CAFE_NELEMENTS(A) ((sizeof((A)) / sizeof((A))[0]))

/**
 *  Cafe-specific version of the stdlib strdup() routine.
 */
static inline
char *CAFE_STRDUP(const struct cafe_allocator *a, const char *str)
{
	size_t len = strlen(str);
	char *new_str = (char *) CAFE_ALLOC(a, len + 1);

	if (new_str == NULL)
		return NULL;

	memcpy(new_str, str, len);
	new_str[len] = 0;
	return new_str;
}


/* List node accessors. */

#define SOURCE_LIST_NODE_ENTRY(PTR)					\
	CAFE_LIST_ENTRY((PTR), struct cafe_ep_inst_edge, source_list)

#define SINK_LIST_NODE_ENTRY(PTR)					\
	CAFE_LIST_ENTRY((PTR), struct cafe_ep_inst_edge, sink_list)

#define SESSION_INST_LIST_ENTRY(PTR)					\
	CAFE_LIST_ENTRY((PTR), struct cafe_ep_inst, session_inst_list)

/* Cafe error codes. */

enum {
	CAFE_OK				= 0,
	CAFE_ERROR			= 1,
	CAFE_NOMEM			= 2,
	CAFE_INVALID_VALUE_TYPE_STR	= 3,
	CAFE_NAMESPACE_NOT_FOUND	= 4,
	CAFE_NAMESPACE_EXISTS		= 5,
	CAFE_SESSION_BUSY		= 6,
	CAFE_INVALID_INITIALIZER	= 7,
	CAFE_INVALID_STATE		= 8,
	CAFE_UNUSED_9			= 9,
	CAFE_INVALID_CONNECTION		= 10,
	CAFE_UNRESOLVED_VALUE_TYPE	= 11,
	CAFE_REDECL_VALUE_TYPE		= 12,
	CAFE_EAL_STALE_HANDLE		= 13,
	CAFE_EAL_TOO_MANY_REFERENCES	= 14,
	CAFE_EAL_TABLE_FULL		= 15,
	CAFE_UNINITIALIZED		= 16,
	CAFE_SYNTAX			= 17,
	CAFE_STACK_OVERFLOW		= 18,
	CAFE_TYPE_MISMATCH		= 19,
	CAFE_TIMESTAMP_NOT_RUNNING	= 20,
	CAFE_RESOURCE_UNAVAILABLE	= 21
};

/* There are a few places where we allocate automatic variables for capturing
   event types or event data.  This sets an upper bound on the size of these
   arrays */
#ifndef CAFE_MAX_EVENT_TYPES
#define CAFE_MAX_EVENT_TYPES  (32)
#endif

/*******************************************************************************
*
* CAFE_STACK_MARKER - Values placed inside a cafe-generated callstack denoting
* the address space which the following addresses belong within
*/
static const unsigned long long CAFE_STACK_MARKER_KERNEL =
	(unsigned long long) -128;
static const unsigned long long CAFE_STACK_MARKER_USER =
	(unsigned long long) -512;

extern int cafe_cfg_get_event
	(
	struct cafe_instrument *session,
	unsigned int num_types,
	struct cafe_value_type **types,
	struct cafe_event_descr **result
	);

/*******************************************************************************
*
* cafe_dispatch_event - call event handlers for a given event
*
* This function calls all event handlers previously returned by
* cafe_ep_inst_get_sink_event_actions().
*
* NOTE: If an error is returned by any handler the dispatch is
* aborted.  Is this the right approach?  It might be better to not
* return any status and instead on error stop the configuration and
* record a stop reason in the instance object.
*
* RETURNS: N/A
*
* ERRNO:
*/
extern void cafe_dispatch_event
	(
	cafe_eal_handle_t *action_list_handle,
	void **event_data
	);

/*******************************************************************************
*
* cafe_dispatch_event_unlocked - call event handlers for a given event
*
* This function is the same as cafe_dispatch_event() except that it
* expects the caller to aquire the read lock.
*
* RETURNS: N/A
*
* ERRNO:
*/
extern void cafe_dispatch_event_unlocked
	(
	const struct cafe_event_action_list *actions,
	void **event_data
	);


/*******************************************************************************
*
* cafe_dispatch_error - register error while dispatching an event
*
* This function should be called from an event action handler to
* register an error during the handling of an event.
*
* RETURNS: N/A
*
* ERRNO:
*/
extern void cafe_dispatch_error(struct cafe_ep_inst *inst, int error);

extern void cafe_dispatch_status(struct cafe_ep_inst *inst,
				 enum cafe_log_level, const char *msg);

extern int cafe_add_event_action(
	struct cafe_ep_inst *inst,
	struct cafe_event_action_list *actions,
	CAFE_ACTION_HANDLER handler,
	struct cafe_event_action_info *client_data);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INCcafe_h */
