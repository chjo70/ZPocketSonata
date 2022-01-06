/* cafe_vx_funcbind.h - */

/*
 * Copyright (c) 2011-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
28nov14,wzc  Support shared libraries.(V7COR-2268)
*/

#ifndef __cafe_vx_funcbindh
#define __cafe_vx_funcbindh


#include <vxWorks.h>
#include <cafe/stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

struct vxworks_event_handle;
struct cafe_ep_inst;

extern int (*func_cafe_vx_enumerate_rtp_info)(struct vxworks_event_handle *h,
					      struct cafe_ep_inst *inst);
extern int (*func_cafe_vx_enumerate_rtp_shl_info)(struct vxworks_event_handle *h,
					      struct cafe_ep_inst *inst);
extern int (*func_cafe_vx_install_rtp_unload_hook)(struct vxworks_event_handle *h,
						   struct cafe_ep_inst *inst);
extern int (*func_cafe_vx_rtp_load_handler)(struct vxworks_event_handle *h,
					    RTP_ID rtp);
extern void (*func_cafe_rtp_memevents_enable)(bool is_enabled);


#ifdef __cplusplus
}
#endif


#endif /* __cafe_vx_funcbindh */
