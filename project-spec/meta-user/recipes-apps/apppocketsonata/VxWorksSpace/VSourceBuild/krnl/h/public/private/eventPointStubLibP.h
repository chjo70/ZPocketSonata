/* eventPointStubLibP.h - eventpoint stub library header file */

/*
 * Copyright (c) 2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,10feb10,tcr  update for 64bit
01f,23jul09,tcr  change return type of eventPointSwStubConnect() to allow
                 chaining
01f,30mar09,mcm  Updates for the LP64 data model
01e,19aug08,tcr  update heading
01d,03jul08,tcr  add connect function, correct condition
01c,24jun08,tcr  add extern
01b,09may08,tcr  change function name
01a,24apr08,tcr  created
*/

#ifndef __eventPointStubLibPh
#define __eventPointStubLibPh

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*EVENT_POINT_HANDLER_T)(event_t eventId, void * args, size_t size);

extern STATUS eventPointStubLibInit (void);

extern void eventPointSwHandle (event_t evtId, void * data, size_t length);
extern EVENT_POINT_HANDLER_T
    eventPointSwStubConnect (EVENT_POINT_HANDLER_T newHandler);
#ifdef __cplusplus
}
#endif


#endif /* __eventPointStubLibPh */

