/* sv_symbol.h - all function/var pointers which are dangling are declared here
 and initialized in System Viewer TCF service's configlette: usrSystemViewer.c */

/*
 * Copyright (c) 2012-2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
/*
modification history
--------------------
14may15,sai  delete _wvNetDInit. (WB4-5490)
11May15,sai  add _pmInit. (WB4-5352)
*/
#ifndef SYSVIEWER_SYMBOL_H
#define SYSVIEWER_SYMBOL_H
#include <wvLib.h>
#include <taskLib.h>
#define INCLUDE_SV_ST 1

extern void init_symbols(void);
extern int is_symbol_api_enabled(void);

/** BEGIN INCLUDE_EDR_PM */
typedef void * (*PmDefaultArena)(size_t *);
typedef void * (*PmRegionAddr)(PmDefaultArena arena, int region);
typedef ssize_t (*PmFreeSpace)(PmDefaultArena arena);
typedef int (*PmRegionOpen)(PmDefaultArena arena, const char * key);
typedef ssize_t (*PmRegionSize)(PmDefaultArena arena, int region);
typedef int (*PmRegionCreate)(PmDefaultArena arena, const char * key, size_t size, int mode);
typedef STATUS (*PmRegionClose)(PmDefaultArena arena, int region);
typedef STATUS (*PmValidate)(PmDefaultArena arena);
typedef STATUS (*PmInit)(PmDefaultArena arena);
typedef void * (*EdrPmArena)(size_t *);

extern PmDefaultArena _pmDefaultArena;
extern PmRegionAddr _pmRegionAddr;
extern PmFreeSpace _pmFreeSpace;
extern PmRegionOpen _pmRegionOpen;
extern PmRegionSize _pmRegionSize;
extern PmRegionCreate _pmRegionCreate;
extern PmRegionClose _pmRegionClose;
extern PmValidate _pmValidate;
extern PmInit _pmInit;
extern EdrPmArena _edrPmArena;
/** END INCLUDE_EDR_PM */

/** BEGIN INCLUDE_WVNETD */
typedef int (*WvNetDConfigure)(int, int, int);

extern WvNetDConfigure _wvNetDConfigure;
/** END INCLUDE_WVNETD */

/** BEGIN INCLUDE_SV_ST */
typedef STATUS (*WvCallStackSetLevel)(int, int);
typedef STATUS (*WvCallStackSetEvent)( event_t, int);
typedef STATUS (*WvCallStackDepthSet)(unsigned int);
typedef STATUS (*WvTaskCallStackSet)(TASK_ID *, int);
typedef STATUS (*WvTaskCallStackClear)(void);
typedef STATUS (*WvCallStackFilterSet)(int);
typedef int (*WvObjStacktrace)(enum windObjClassType type, void *objId, BOOL evtLoggingOn);

extern WvCallStackSetLevel _wvCallStackSetLevel;
extern WvCallStackSetEvent _wvCallStackSetEvent;
extern WvCallStackDepthSet _wvCallStackDepthSet;
extern WvTaskCallStackSet _wvTaskCallStackSet;
extern WvTaskCallStackClear _wvTaskCallStackClear;
extern WvCallStackFilterSet _wvCallStackFilterSet;
extern WvObjStacktrace _wvObjStacktrace;
/** END INCLUDE_SV_ST */

/** BEGIN INCLUDE_WVTIPC */
typedef int (*WvTipcConfigure)(int, int, int);
typedef void (*WvTipcInit)(void);

extern WvTipcConfigure _wvTipcConfigure;
extern WvTipcInit _wvTipcInit;
/** END INCLUDE_WVTIPC */

/** BEGIN lib_events */
extern int _sigEnabled;
extern int _evtEnabled;
extern int _salEnabled;
extern int _edrEnabled;
extern int _mscEnabled;
/** END lib_events */

/** BEGIN INCLUDE_USB */
extern UINT32 * _usb2WvFilter;
extern UINT32 * _usbPeriphWvFilter;
/** END INCLUDE_USB */

extern BOOL wvEvtBufferFullNotify;
#endif
