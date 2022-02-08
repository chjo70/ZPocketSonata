/* vxworks_kernel.h - vxworks kernel event processor types */

/*
 * Copyright (c) 2010-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


#ifndef __vxworks_kernelh
#define __vxworks_kernelh

#include <cafe/atomic.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_ROOT_INSTANCES	8

struct data_collector;

struct vxworks_dc_event_handle {
	void (*dc_func)(struct data_collector *dc, const void *args, size_t size);
	struct data_collector *dc;
};

struct cafe_user_event_handle {
	unsigned int refcnt;
	const char *vt2str;
	const struct cafe_allocator *allocator;
	struct cafe_list_head list;
};

struct vxworks_event_handle {
	unsigned long change_count[NUM_ROOT_INSTANCES];
	cafe_eal_handle_t sink_actions[NUM_ROOT_INSTANCES];
	cafe_atomic_val skipcount_value[NUM_ROOT_INSTANCES];
	cafe_atomic_val skipcount_limit[NUM_ROOT_INSTANCES];
	char statedump_request[NUM_ROOT_INSTANCES];
	int event_id;
	int (*state_dump)(struct vxworks_event_handle *h, struct cafe_ep_inst *inst);
	union {
		struct vxworks_dc_event_handle dc;
		struct cafe_user_event_handle user;
	} event_type;
};

extern int cafe_cfg_vxworks_kernel_init_cafe(void);
extern void cafe_cfg_vxworks_cur_int_num_get (int * pIntLevel, int * pIntNum);
extern void cafe_cfg_vxworks_kernel_delete(void);
extern void cafe_cfg_vxworks_ev_process_id(int id, void *args,
					   struct cafe_ep_inst *inst);
extern int cafe_cfg_vxworks_kernel_connect_event(struct cafe_ep_spec_output_evt *evt);
extern int cafe_ep_vxworks_kernel_enable_event(struct vxworks_event_handle *evt);
extern void cafe_ep_vxworks_kernel_disable_event(struct vxworks_event_handle *evt);

extern void cafe_cfg_vxworks_ev_process_handle(struct vxworks_event_handle *h, void *args,
					       struct cafe_ep_inst *inst);
extern int cafe_cfg_vxworks_inst_start(struct cafe_ep_inst *inst);
extern int cafe_cfg_vxworks_inst_stop(struct cafe_ep_inst *inst);
extern int cafe_cfg_vxworks_kernel_delete_internal(void);
extern unsigned long long cafe_cfg_vxworks_orth_data_ts(void);
extern int cafe_cfg_vxworks_orth_data_coreid(void);
extern int cafe_cfg_vxworks_emit_state_events(struct cafe_ep_inst *inst);
extern int cafe_cfg_vxworks_post_timestamp_config(struct vxworks_event_handle *event_handle,
						  struct cafe_ep_inst *inst);
extern int cafe_cfg_vxworks_post_core_count(struct vxworks_event_handle *event_handle,
					    struct cafe_ep_inst *inst);
extern int cafe_cfg_vxworks_post_initial_task(struct vxworks_event_handle *event_handle,
					      struct cafe_ep_inst *inst);

#ifdef __cplusplus
}
#endif


#endif /* __vxworks_kernelh */
