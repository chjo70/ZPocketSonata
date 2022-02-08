/* smaEndPktLib.h - header file for SMA agents END based packet driver */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
23dec14,elp  added smaEndPktDevIpAddrFlush().
18aug14,elp  created from WDB.
*/

#ifndef __INCsmaEndPktLibh
#define __INCsmaEndPktLibh

/* includes */

#include <end.h>
#include <smaMbufLib.h>
#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define STOP_MODE_AGENT_END_PKT_MTU     1500	/* MTU of this driver */
#define SMAPORT                         smaPort

/* typedef  */

extern UINT16    smaPort;
extern uint_t    smaCommMtu;

/* function prototypes */

#if defined(__STDC__)

extern STATUS smaEndPktDevInit
    (
    char *	pDevice,	/* Device (ln, ie, etc.) that we wish to */
    				/* bind to. */
    int         unit            /* unit number (0, 1, etc.) */
    );
extern void smaEndPktDevIpAddrFlush (void);

#else   /* __STDC__ */

extern STATUS   smaEndPktDevInit ();
extern void     smaEndPktDevIpAddrFlush ();

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif  /* __INCsmaEndPktLibh */

