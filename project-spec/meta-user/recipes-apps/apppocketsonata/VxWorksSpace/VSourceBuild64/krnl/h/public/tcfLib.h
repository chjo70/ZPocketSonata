/* tcfLib.h - TCF Agent library header file */

/*
 * Copyright (c) 2010-2011, 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if !defined(__tcfLib_h)
#define __tcfLib_h

#if defined(__cplusplus)
extern "C" {
#endif


#include <tcf/framework/protocol.h>

extern void tcf_init_service (void (*init_func) (Protocol *));
extern void tcf_init2_service (void (*init_func) (Protocol *, TCFBroadcastGroup *));
extern void tcfLibInit (unsigned int task_priority);
extern void tcfLibStart (char * config, unsigned int * pStarted,
                         unsigned int verbose);
extern void tcfServicesInit (void);

extern void tcf_init_rtp_funcbind(void);
#if defined(__cplusplus)
}
#endif

#endif  /* if !defined(__tcfLib_h) */
