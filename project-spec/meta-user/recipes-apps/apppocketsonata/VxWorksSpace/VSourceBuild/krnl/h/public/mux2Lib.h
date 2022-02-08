/* mux2Lib.h - mux2 Lib handling API */

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
05may14,rjq  Decouple COREIP with END. (V7NET-105)
*/

/*
DESCRIPTION
This file includes function prototypes for the MUX.

INCLUDE FILES:
*/
 
#ifndef __INCmux2Libh
#define __INCmux2Libh


/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <vsbConfig.h>
#include <muxLib.h>


#ifdef _WRS_KERNEL
#include <end.h>
#else
#include <endCommon.h>
#endif /* _WRS_KERNEL */
#include <ipcom_pkt.h>


#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

IMPORT NET_POOL_ID _end2_linkBufPool;

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/* Routines for mux2Bind() protocols and END2-style devices */

void mux2LibInit (void);

/*
 * Function prototype definitions.
 */
typedef BOOL   (*mux_stackRcvRtn) (void * callbackArg, struct Ipcom_pkt_struct * pkt);
typedef STATUS (*mux_stackShutdownRtn) (PROTO_COOKIE cookie, void * callbackArg);
typedef STATUS (*mux_stackTxRestartRtn) (void * callbackArg);
typedef void   (*mux_stackErrorRtn) (void * callbackArg, END_ERR * err);

void * mux2Bind (char * name, int unit,
	 BOOL   (*stackRcvRtn) (void * callbackArg,
				struct Ipcom_pkt_struct * pkt),
	 STATUS (*stackShutdownRtn) (PROTO_COOKIE cookie, void * callbackArg),
	 STATUS (*stackTxRestartRtn) (void * callbackArg),
	 void   (*stackErrorRtn) (void * callbackArg, END_ERR * err),
	 unsigned short type, char * pProtoName, void * callbackArg);

IMPORT int mux2Send (END_OBJ * pEnd, struct Ipcom_pkt_struct * pkt);
IMPORT int mux2PollSend (END_OBJ * pEnd, struct Ipcom_pkt_struct * pkt);
IMPORT int mux2PollReceive (END_OBJ * pEnd, struct Ipcom_pkt_struct * pkt);


void    end2LibInit (void);


/* Routines called (mostly) by network device drivers */

IMPORT void mux2Receive (END_OBJ * pEnd, struct Ipcom_pkt_struct * pkt);
int    end2EtherHdrParse (END_OBJ * pEnd, struct Ipcom_pkt_struct * pkt);
int    end2EtherIIFormLinkHdr (END_OBJ * pEnd, struct Ipcom_pkt_struct * pkt,
			       UINT8 * dstAddr, UINT8 * srcAddr,
			       UINT16 netType);
void   end2BufferPoolConfig (size_t alignment, size_t extra_space);


/* cross protocol / device */

IMPORT void muxOverEnd2Init (void);
IMPORT void mux2OverEndInit (void);

/*
 ****************************************************************************
 * 8                    VARIABLES
 ****************************************************************************
 */

#ifdef __cplusplus
}
#endif

#endif /* __INCmux2Libh */


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
