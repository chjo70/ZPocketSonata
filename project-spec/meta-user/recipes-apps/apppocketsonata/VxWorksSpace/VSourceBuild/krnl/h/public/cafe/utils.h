/* utils.h - Wind River Common Analysis Framework Utilities Library. */

/*
 * Copyright (c) 2010-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCcafe_utils_h
#define INCcafe_utils_h

#include <cafe/cafe.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__
char *cafe_mprintf(const struct cafe_allocator *allocator,
		   const char *fmt, ...)
	__attribute__((format(printf, 2, 3)));
#endif

extern char *cafe_mprintf
	(
	const struct cafe_allocator *allocator,
	const char *fmt, ...
	);

extern int cafe_inst_enable_all_output_events(
	struct cafe_ep_inst *inst);

extern int cafe_type_list_parse(
	struct cafe_instrument *session,
	const char *s,
	struct cafe_event_descr **result);


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INCcafe_utils_h */
