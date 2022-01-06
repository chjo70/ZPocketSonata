/* elog_native_cfg.h - */

/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#if !defined(__elog_native_cfg_h)
#define __elog_native_cfg_h

#if defined(__cplusplus)
extern "C" {
#endif


extern const char elog_native_cfg_name[];

/* customizable parameters */
extern const char elog_native_cfg_param_log_size[];
extern const char elog_native_cfg_param_record_overflows[];


#if defined(__cplusplus)
}	/* extern "C" */
#endif

#endif  /* if !defined(__elog_native_cfg_h) */
