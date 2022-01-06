/* cafe_print.h - Print routines for Wind River Common Analysis Framework */

/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef __cafe_showh
#define __cafe_showh

#ifdef __cplusplus
extern "C" {
#endif


#include <cafe/types.h>


struct cafe_ep_spec;
struct cafe_ep_inst;
struct cafe_value_type;

extern int cafe_ep_spec_print(const struct cafe_ep_spec *spec, int flags);
extern int cafe_ep_spec_print_all(int flags);

extern int cafe_instrument_print_all(int flags);
extern int cafe_instrument_print(const struct cafe_instrument *session,
				 int flags, bool lock_taken);

extern int cafe_ep_inst_print_chain(const struct cafe_ep_inst *sink,
				    int flags, bool lock_taken);
extern int cafe_ep_inst_print(const struct cafe_ep_inst *inst, int flags,
			      bool lock_taken);
extern int cafe_ep_inst_print_all(struct cafe_instrument *session,
				  int flags);
extern int cafe_event_data_print(struct cafe_value_type *vt,
				 const void *data);

enum {
	CAFE_CFG_PRINT_INPUT = 0x1,
	CAFE_CFG_PRINT_OUTPUT = 0x2,
	CAFE_CFG_PRINT_FUNCS = 0x4
};

#ifdef __cplusplus
}
#endif


#endif /* __cafe_showh */
