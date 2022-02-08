/* hpc_ep.h - Cafe Hardware Performance Counter Event Processor */

/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_hpc_ep_h
#define INChpc_hpc_ep_h

#include <cafe/cafe.h>
#include <cafe/list.h>

#include <hpc/hpc_drv/hpcHwDrvApi.h>
#include <hpc/drv_evt_cfg/hpcDrvEvtCfg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int HPC_DRIVER_IDX;

extern int hpc_init(void *(* hpc_malloc)(size_t),
			   void (* hpc_free)(void *), int);
extern int hpc_finit(void);
extern int hpc_hw_driver_register(struct hpcDriverConfig *);
extern int hpc_hw_driver_unregister(struct hpcDriverConfig *);
extern int hpc_register_configuration(void);
extern int hpc_unregister_configuration(void);
extern void hpc_force_shutdown(void);
extern int hpc_vc_check_period(void);

extern void hpc_driver_list_show(void);
extern void hpc_driver_show(HPC_DRIVER_IDX driver);
extern void hpc_driver_show_all(void);
extern void hpc_count_show(void);
extern int hpc_vc_show(void);
extern int hpc_inst_show(void);

#ifdef __cplusplus
}
#endif
#endif /* INChpc_hpc_ep_h */
