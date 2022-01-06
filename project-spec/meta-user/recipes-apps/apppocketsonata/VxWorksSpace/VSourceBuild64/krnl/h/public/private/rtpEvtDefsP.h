/* eventDefsP.h - user-level System Viewer event definitions */

/*
 * Copyright (c) 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01nov14,wzc  add share_h directory.(US46321)
21oct10,tcr  created
*/

#ifndef __eventDefsPh
#define __eventDefsPh

#ifdef __cplusplus
extern "C" {
#endif

#define SV_EVENT_USERLEVEL_START	15000
#define SV_EVENT_USERLEVEL(n)	        (SV_EVENT_USERLEVEL_START + n)

#define SV_EVENT_RTP_MEMALLOC		SV_EVENT_USERLEVEL(0)

typedef struct event_rtp_memalloc
    {
    unsigned long	pPartition;
    unsigned long	addr;
    unsigned long	bytesReq;
    unsigned long	bytesAlloc;
    } EVENT_RTP_MEMALLOC_T;

#define SV_EVENT_RTP_MEMFREE		SV_EVENT_USERLEVEL(1)

typedef struct event_rtp_memfree
    {
    unsigned long	pPartition;
    unsigned long	addr;
    unsigned long	bytesFree;
    } EVENT_RTP_MEMFREE_T;

#define SV_EVENT_RTP_MEMPARTCREATE	SV_EVENT_USERLEVEL(2)

typedef struct event_rtp_mempartcreate
    {
    unsigned long	pPartition;
    unsigned long	pPool;
    unsigned long	poolSize;
    } EVENT_RTP_MEMPARTCREATE_T;


#define SV_EVENT_RTP_MEMREALLOC		SV_EVENT_USERLEVEL(3)

typedef struct event_rtp_memrealloc
    {
    unsigned long	pPartition;
    unsigned long	bytesReq;
    unsigned long	bytesAlloc;
    unsigned long	addr;
    unsigned long	prevAddr;
} EVENT_RTP_MEMPARTREALLOC_T;


#define SV_EVENT_RTP_MEMADDTOPOOL	SV_EVENT_USERLEVEL(4)

typedef struct event_rtp_memalltopool
{
unsigned long	pPartition;
    unsigned long	pPool;
    unsigned long	poolSize;
} EVENT_RTP_MEMPARTADDTOPOOL_T;

/*
 *in RTP space, the event Id is an integer type. 
 *But in kernel space event type is a short integer type.
 *So we may use a unused number as the event to transfer the addresses of
 *wvEvtAction.
 */
#define EVENT_RTP_INSTRUMENTED_INIT 0x10000

typedef struct
    {
    unsigned int * wvEvtActionAddr;
    } SV_RTP_INST_INIT_T;

#ifdef __cplusplus
}
#endif


#endif /* __eventDefsPh */

