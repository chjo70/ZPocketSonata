/* svRtpLibP.h - VxWorks user WindView RTP library interface header */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
30oct14,wzc  created
*/

#ifndef __INCsvRtpLibP_h
#define __INCsvRtpLibP_h

#ifdef __cplusplus
extern "C" {
#endif

/* Global var declarations */

/* Function declarations */
extern STATUS svRtpInstNodeAdd(RTP_ID pid, unsigned int * evtActionAddr);
extern STATUS svRtpEvtActionSet(RTP_ID rtpId, unsigned int svEvtAction);
extern void svRtpsInstSetAll(unsigned int mode);
extern STATUS svRtpInstsInit();

#ifdef __cplusplus
}
#endif

#endif /* __INCsvRtpLibP_h */
