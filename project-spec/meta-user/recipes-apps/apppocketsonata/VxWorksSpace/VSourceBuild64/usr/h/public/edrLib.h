/* edrLib.h - Error Detection and Reporting subsystem */

/*
 * Copyright (c) 2004, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08sep15,pcs  Static analysis fix.
14dec04,aeg  added _edrErrorInject/edrIsDebugMode prototypes (SPR #105335).
21may04,md   add inject options
22apr04,md   enabled traceback support
02feb04,md   created
*/

#ifndef __INCedrLib_h
#define __INCedrLib_h

#include <stdlib.h>
#include <setjmp.h>
#include "vxWorks.h"
#include "edrLibCommon.h"
#include "regs.h"

#ifdef __cplusplus
extern "C" {
#endif


/* user generated ED&R messages */

#define EDR_USER_INFO_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_INFO, EDR_FACILITY_USER, 0, trace, msg)

#define EDR_USER_WARNING_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_WARNING, EDR_FACILITY_USER, 0, trace, msg)
    
#define EDR_USER_FATAL_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_FATAL, EDR_FACILITY_USER, 0, trace, msg)
    

/* system generated RTP ED&R messages */

#define EDR_RTP_INFO_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_INFO, EDR_FACILITY_RTP, 0, trace, msg)

#define EDR_RTP_WARNING_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_WARNING, EDR_FACILITY_RTP, 0, trace, msg)
    
#define EDR_RTP_FATAL_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_FATAL, EDR_FACILITY_RTP, 0, trace, msg)


#define EDR_INJECT(kind, file, line, pRegs, addr, msg)	\
     edrErrorInject (kind, file, line, pRegs, addr, msg)

#define EDR_INJECT_TRACE(sev, fac, opt, trace, msg) \
    do { \
	REG_SET *pRegs = NULL; \
	REG_SET  regs; \
	if ((trace != 0) && (saveRegs(&regs) == 0)) { pRegs = &regs; } \
	    (void) EDR_INJECT(sev | fac | opt , __FILE__, __LINE__, pRegs, \
            NULL, msg); \
    } while ((0))

extern STATUS edrErrorInject
    (
    int			kind,		/* severity | facility | option	*/
    const char *	fileName,	/* name of source file		*/
    int			lineNumber,	/* line number of source code	*/
    REG_SET *		pRegs,		/* pointer to register set	*/
    void*		addr,		/* faulting address (e.g. PC)	*/
    const char *	textPayload	/* additional text string	*/
    );

extern BOOL edrIsDebugMode (void);


/* system call function prototypes */

extern STATUS _edrErrorInject
    (
    int			kind,		/* severity | facility | option	*/
    const char *	fileName,	/* name of source file		*/
    int			lineNumber,	/* line number of source code	*/
    REG_SET *		pRegs,		/* pointer to register set	*/
    void*		addr,		/* faulting address (e.g. PC)	*/
    const char *	textPayload	/* additional text string	*/
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCedrLib_h */
