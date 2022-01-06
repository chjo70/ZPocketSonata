/* wvModuleLibP - VxWorks user WindView module library interface header */

/* Copyright (c) 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
19may14,sdt  created
*/

#ifndef __INCwvModuleLibP_h
#define __INCwvModuleLibP_h

#include <private/wvLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef STATUS (*WV_MODULE_INFO_PRESERVE_HANDLER_T)(WV_LOG * pWvLog);

/* Global var declarations */

extern WV_MODULE_INFO_PRESERVE_HANDLER_T _func_moduleInfoPreserve;

/* Function declarations */

extern void wvModuleLibInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCwvModuleLibP_h */
