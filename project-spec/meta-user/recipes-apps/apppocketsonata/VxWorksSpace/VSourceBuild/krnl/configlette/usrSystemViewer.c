/* usrSystemViewer.c - System Viewer's tcf service */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14may15,sai  delete _wvNetDInit. (WB4-5490)
02Apr15,sai  extern _pmValidate for pm validate.(WB4-5231)
12dec14,wzc  fix building warnings.(V7COR-2317)
*/


#include <sysviewer.h>
#include <sv_symbol.h>

#ifdef INCLUDE_EDR_PM
extern void * pmDefaultArena(size_t*);
extern void * pmRegionAddr(PmDefaultArena arena, int region);
extern ssize_t pmFreeSpace(PmDefaultArena arena);
extern int pmRegionOpen(PmDefaultArena arena, const char * key);
extern ssize_t pmRegionSize(PmDefaultArena arena, int region);
extern int pmRegionCreate(PmDefaultArena arena, const char * key, size_t size, int mode);
extern STATUS pmRegionClose(PmDefaultArena arena, int region);
#ifdef INCLUDE_EDR_ERRLOG
extern void * edrPmArena(size_t*);
#endif
#endif

#ifdef INCLUDE_WVNETD
extern int wvNetDConfigure(int, int, int);
#endif

#ifdef INCLUDE_SV_ST
extern STATUS wvCallStackSetLevel(int, int);
extern STATUS wvCallStackSetEvent(event_t, int);
extern STATUS wvCallStackDepthSet(unsigned int);
extern STATUS wvTaskCallStackSet(TASK_ID *, int);
extern STATUS wvTaskCallStackClear(void);
extern STATUS wvCallStackFilterSet(int);
extern int wvObjStacktrace(enum windObjClassType type, void *objId, BOOL evtLoggingOn);
#endif

#ifdef INCLUDE_WVTIPC
extern int wvTipcConfigure(int, int, int);
extern void wvTipcInit(void);
#endif

#ifdef INCLUDE_USB
extern UINT32 usb2WvFilter;
extern UINT32 usbPeriphWvFilter;
#endif

static void init_pointers(void) {
#ifdef INCLUDE_EDR_PM
    _pmDefaultArena = pmDefaultArena;
    _pmRegionAddr = pmRegionAddr;
    _pmFreeSpace = pmFreeSpace;
    _pmRegionOpen = pmRegionOpen;
    _pmRegionSize = pmRegionSize;
    _pmRegionCreate = pmRegionCreate;
    _pmRegionClose = pmRegionClose;
    _pmValidate = pmValidate;
#ifdef INCLUDE_EDR_ERRLOG
    _edrPmArena =  edrPmArena;
    _edrEnabled = 1;
#endif
#endif

#ifdef INCLUDE_WVNETD
    _wvNetDConfigure = wvNetDConfigure;
#endif

#ifdef INCLUDE_SV_ST
    _wvCallStackSetLevel = wvCallStackSetLevel;
    _wvCallStackSetEvent = wvCallStackSetEvent;
    _wvCallStackDepthSet = wvCallStackDepthSet;
    _wvTaskCallStackSet = wvTaskCallStackSet;
    _wvTaskCallStackClear = wvTaskCallStackClear;
    _wvCallStackFilterSet = wvCallStackFilterSet;
    _wvObjStacktrace = wvObjStacktrace;
#endif

#ifdef INCLUDE_WVTIPC
    _wvTipcConfigure = wvTipcConfigure;
    _wvTipcInit = wvTipcInit;
#endif

#ifdef INCLUDE_SIGNALS
    _sigEnabled = 1;
#endif

#ifdef INCLUDE_VXEVENTS
    _evtEnabled = 1;
#endif

#ifdef INCLUDE_SAL_CLIENT 
    _salEnabled = 1;
#endif

#ifdef INCLUDE_SAL_SERVER
    _salEnabled = 1;
#endif

#ifdef INCLUDE_WINDVIEW
    _mscEnabled = 1;
#endif

#ifdef INCLUDE_USB
    _usb2WvFilter = &usb2WvFilter;
    _usbPeriphWvFilter = &usbPeriphWvFilter;
#endif
}

void init_system_viewer(void) {
    if(is_symbol_api_enabled()) {
        init_symbols();
    } else {
        init_pointers();
    }
    tcf_init_service(ini_sysviewer_service);
}
