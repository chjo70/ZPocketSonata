/* rtpVarLib.h - header for RTP variables */

/* Copyright 2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,02mar04,kk  written
*/

#ifndef __INCrtpVarLibh
#define __INCrtpVarLibh

#include "rtpLib.h"
#include "rtpVarLibCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* RTP variable structure */

typedef struct rtp_var
    {
    struct rtp_var *	next;	/* link the RTP vars */
    RTP_VAR_ADDR	addr;   /* address of variable to switch */
    RTP_VAR		value;	/* value of variable */
    } RTP_VAR_INFO;

extern STATUS 	rtpVarAdd (RTP_VAR_ADDR pVar, RTP_VAR value, RTP_ID rtpId);
extern STATUS   rtpVarDelete (RTP_VAR_ADDR pVar, RTP_ID rtpId);
extern STATUS 	rtpVarDeleteAll (RTP_ID rtpId);

#ifdef __cplusplus
}
#endif

#endif /* __INCrtpVarLibh */
