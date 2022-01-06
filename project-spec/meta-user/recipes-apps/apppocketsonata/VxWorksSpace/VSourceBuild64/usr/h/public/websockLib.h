/* websockLib.h - web socket library header file */

/*
 * Copyright (C) 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
28may16,dlk  Rename httpLib ==> httpBaseLib, since httpLib.[ch] already exist
             in the WEBCLI_HTTP layer.
18dec15,kjn  written
*/

#ifndef __INCwebsockLibh
#define __INCwebsockLibh

/* includes */

#include <httpBaseLib.h>
#include <stdlib.h>
#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

/* typedefs */

struct wsCtx;			/* forward declaration to allow definition */
                                /* of WS_CTX */

typedef struct wsCtx *	WS_ID;	/* represent a single websocket connection */

/*
 * WebSocket session ready state
 */

typedef enum
    {
    WS_RS_CONNECTING,   /* the connection has not yet been established. */
    WS_RS_OPEN,         /* the WebSocket connection is established and */
                        /* communication is possible. */
    WS_RS_CLOSING,      /* the connection is going through the closing */
                        /* handshake. */
    WS_RS_CLOSED        /* the connection has been closed or could not be */
                        /* opened. */
    } WS_READY_STATE;

/*
 * Endpoints MAY use the following pre-defined status codes when sending a
 * Close frame.
 */

typedef enum
    {
    WS_SC_OK         =    1000, /* indicates a normal closure, meaning that */
                                /* the purpose for which the connection was */
                                /* established has been fulfilled */
    WS_SC_GOING_AWAY =    1001, /* endpoint is "going away", such as a server */
                                /* going down or a browser having navigated */
                                /* away from a page */
    WS_SC_PROTO_ERR  =    1002, /* endpoint is terminating the connection due */
                                /* to a protocol error */
    WS_SC_TERMINATE  =    1003, /* endpoint is terminating the connection */
                                /* because it has received a type of data it */
                                /* cannot accept (e.g., an endpoint that */
                                /* understands only text data MAY send this if */
                                /* it receives a binary message) */
    WS_SC_NO_STATUS     = 1005, /* reserved value and MUST NOT be set as a */
                                /* status code in a Close control frame by an */
                                /* endpoint.  It is designated for use in */
                                /* applications expecting a status code to */
                                /* indicate that no status code was actually */
                                /* present. */
    WS_SC_UNEXPECTED_EOF = 1006, /* reserved value and MUST NOT be set as a */
                                /* status code in a Close control frame by an */
                                /* endpoint.  It is designated for use in */
                                /* applications expecting a status code to */
                                /* indicate that the connection was closed */
                                /* abnormally, e.g., without sending or */
                                /* receiving a Close control frame */
    WS_SC_INCONSISTENT = 1007, /* endpoint is terminating the connection */
                               /* because it has received data within a */
                               /* message that was not consistent with the */
                               /* type of the message (e.g., non-UTF-8 */
                               /* [RFC3629] data within a text message) */
    WS_SC_POLICY       = 1008, /* endpoint is terminating the connection */
                               /* because it has received a message that */
                               /* violates its policy.  This is a generic */
                               /* status code that can be returned when there */
                               /* is no other more suitable status code (e.g., */
                               /* 1003 or 1009) or if there is a need to hide */
                               /* specific details about the policy */
    WS_SC_TOO_BIG      = 1009, /* endpoint is terminating the connection */
                               /*  because it has received a message that is */
                               /* too big for it to process */
    WS_SC_CLIENT       = 1010, /* endpoint (client) is terminating the */
                               /* connection because it has expected the */
                               /* server to negotiate one or  more extension, */
                               /* but the server didn't return them in the */
                               /* response message of the WebSocket handshake. */
                               /* The list of extensions that are needed */
                               /* SHOULD appear in the /reason/ part of the */
                               /* Close frame. Note that this status code is */
                               /* not used by the server, because it can fail */
                               /* the WebSocket handshake instead. */
    WS_SC_SERVER       = 1011, /* server is terminating the connection because */
                               /* it encountered an unexpected condition that */
                               /* prevented it from fulfilling the request */
    WS_SC_TLS_HANDSHAKE = 1015, /* reserved value and MUST NOT be set as a */
                                /* status code in a Close control frame by an */
                                /* endpoint.  It is designated for use in */
                                /* applications expecting a status code to */
                                /* indicate that the connection was closed due */
                                /* to a failure to perform a TLS handshake */
                                /* (e.g., the server certificate can't be */
                                /* verified). */
  } WS_STATUS_CODE;

/*
 * WebSocket message type
 */

typedef enum
    {
    WS_MT_TEXT,         /* message is UTF-8 encoded text */
    WS_MT_BINARY        /* message is a opaque sequence of octets */
    } WS_MSG_TYPE;

/*
 * return codes from the WS_OPEN_RTN routine
 */

typedef enum
    {
    WS_OC_OK,		/* accept this set of parameters */
    WS_OC_NOT_FOUND,	/* the requested resource name is not available */
    WS_OC_FORBIDDEN,	/* the request origin is not accepted */
    WS_OC_UNSUPP_PROTO	/* the subprotocol is not supported */
    } WS_OPEN_CODE;

typedef WS_OPEN_CODE (*WS_OPEN_RTN)   (WS_ID ws,
                                       const HTTP_REQ req,
                                       const char * subprotocol);
typedef void         (*WS_MSG_RTN)    (WS_ID ws,
                                       const void * data,
                                       size_t dataLen,
                                       WS_MSG_TYPE type);
typedef void         (*WS_ERR_RTN)    (WS_ID ws,
                                       UINT32 error);
typedef void         (*WS_CLOSE_RTN)  (WS_ID ws,
                                       WS_STATUS_CODE statusCode);


/* function declarations */

extern WS_ID            wsCreate        (const HTTP_REQ req,
                                         HTTP_RES res,
                                         WS_OPEN_RTN onOpen,
                                         WS_MSG_RTN onMessage,
                                         WS_ERR_RTN onError,
                                         WS_CLOSE_RTN onClose,
                                         void * usrWs);
extern void             wsDelete        (WS_ID ws);
extern STATUS           wsClose         (WS_ID ws);
extern STATUS           wsSend          (WS_ID ws,
                                         const void * data,
                                         size_t dataLen,
                                         WS_MSG_TYPE type);
extern STATUS           wsProcess       (WS_ID ws);

extern void *           wsUsrCtxGet     (WS_ID ws);
extern WS_READY_STATE   wsReadyStateGet (const WS_ID ws);
extern int              wsSockGet       (const WS_ID ws);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCwebsockLibh */
