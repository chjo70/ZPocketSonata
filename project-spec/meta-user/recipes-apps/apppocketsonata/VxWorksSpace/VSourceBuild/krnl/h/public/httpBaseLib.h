/* httpBaseLib.h - Hyper Text Transfer Protocol library header file */

/*
 * Copyright (C) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
28may16,dlk  Renaming as httpBaseLib.h, since httpLib.h already exists
             in the WEBCLI_HTTP layer.
26jan16,kjn  written
*/

#ifndef __INChttpBaseLibh
#define __INChttpBaseLibh

/* includes */

#include <stddef.h>
#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

/* typedefs */

struct httpCtx;
struct httpReq;
struct httpRes;

typedef struct httpCtx * HTTP_ID;
typedef struct httpReq * HTTP_REQ;
typedef struct httpRes * HTTP_RES;

typedef enum httpMethod
    {
    HTTP_M_GET,         /* The GET method means retrieve whatever information */
                        /* (in the form of an entity) is identified by the */
                        /* Request-URI. If the Request-URI refers to a */
                        /* data-producing process, it is the produced data */
                        /* which shall be returned as the entity in the */
                        /* response and not the source text of the process, */
                        /* unless that text happens to be the output of the */
                        /* process.  */
    HTTP_M_POST,        /* The POST method is used to request that the origin */
                        /* server accept the entity enclosed in the request */
                        /* as a new subordinate of the resource identified by */
                        /* the Request-URI in the Request-Line. */
    HTTP_M_HEAD,        /* The HEAD method is identical to GET except that */
                        /* the server MUST NOT return a message-body in the */
                        /* response. The metainformation contained in the */
                        /* HTTP headers in response to a HEAD request SHOULD */
                        /* be identical to the information sent in response */
                        /* to a GET request. */
    HTTP_M_OPTIONS,     /* The OPTIONS method represents a request for */
                        /* information about the communication options */
                        /* available on the request/response chain identified */
                        /* by the Request-URI. This method allows the client */
                        /* to determine the options and/or requirements */
                        /* associated with a resource, or the capabilities of */
                        /* a server, without implying a resource action or */
                        /* initiating a resource retrieval. */
    HTTP_M_PUT,         /* The PUT method requests that the enclosed entity */
                        /* be stored under the supplied Request-URI. If the */
                        /* Request-URI refers to an already existing */
                        /* resource, the enclosed entity SHOULD be considered */
                        /* as a modified version of the one residing on the */
                        /* origin server. */
    HTTP_M_DELETE,      /* The DELETE method requests that the origin server */
                        /* delete the resource identified by the Request-URI. */
    HTTP_M_TRACE,       /* The TRACE method is used to invoke a remote, */
                        /* application-layer loop- back of the request */
                        /* message. */
    HTTP_M_CONNECT,     /* This specification reserves the method name */
                        /* CONNECT for use with a proxy that can dynamically */
                        /* switch to being a tunnel */
    } HTTP_MTD;

typedef enum httpRequestTargetForm
    {
    HTTP_RTF_ORIGIN,    /* RFC7230 chapter 5.3.1 */
    HTTP_RTF_ABSOLUTE,  /* RFC7230 chapter 5.3.2 */
    HTTP_RTF_AUTHORITY, /* RFC7230 chapter 5.3.3 */
    HTTP_RTF_ASTRISK    /* RFC7230 chapter 5.3.4 */
    } HTTP_REQ_TGT_FRM;

typedef struct httpVersion
    {
    UINT8       major;
    UINT8       minor;
    } HTTP_VER;


/*
 * All header fields registered with IANA,
 * http://www.iana.org/assignments/message-headers/message-headers.txt
 */

typedef enum httpHeaderField
    {
    HTTP_HF_A_IM,                        /* RFC4229 */
    HTTP_HF_ACCEPT,                      /* RFC7231, Section 5.3.2 */
    HTTP_HF_ACCEPT_ADDITIONS,            /* RFC4229 */
    HTTP_HF_ACCEPT_CHARSET,              /* RFC7231, Section 5.3.3 */
    HTTP_HF_ACCEPT_DATETIME,             /* RFC7089 */
    HTTP_HF_ACCEPT_ENCODING,             /* RFC7231, Section 5.3.4, RFC7694, Section 3 */
    HTTP_HF_ACCEPT_FEATURES,             /* RFC4229 */
    HTTP_HF_ACCEPT_LANGUAGE,             /* RFC7231, Section 5.3.5 */
    HTTP_HF_ACCEPT_PATCH,                /* RFC5789 */
    HTTP_HF_ACCEPT_RANGES,               /* RFC7233, Section 2.3 */
    HTTP_HF_AGE,                         /* RFC7234, Section 5.1 */
    HTTP_HF_ALLOW,                       /* RFC7231, Section 7.4.1 */
    HTTP_HF_ALPN,                        /* RFC7639, Section 2 */
    HTTP_HF_ALTERNATES,                  /* RFC4229 */
    HTTP_HF_APPLY_TO_REDIRECT_REF,       /* RFC4437 */
    HTTP_HF_AUTHENTICATION_INFO,         /* RFC7615, Section 3 */
    HTTP_HF_AUTHORIZATION,               /* RFC7235, Section 4.2 */
    HTTP_HF_C_EXT,                       /* RFC4229 */
    HTTP_HF_C_MAN,                       /* RFC4229 */
    HTTP_HF_C_OPT,                       /* RFC4229 */
    HTTP_HF_C_PEP,                       /* RFC4229 */
    HTTP_HF_C_PEP_INFO,                  /* RFC4229 */
    HTTP_HF_CACHE_CONTROL,               /* RFC7234, Section 5.2 */
    HTTP_HF_CALDAV_TIMEZONES,            /* RFC-ietf-tzdist-caldav-timezone-ref-05, Section 7.1 */
    HTTP_HF_CLOSE,                       /* RFC7230, Section 8.1 */
    HTTP_HF_CONNECTION,                  /* RFC7230, Section 6.1 */
    HTTP_HF_CONTENT_BASE,                /* RFC2068, RFC2616 */
    HTTP_HF_CONTENT_DISPOSITION,         /* RFC6266 */
    HTTP_HF_CONTENT_ENCODING,            /* RFC7231, Section 3.1.2.2 */
    HTTP_HF_CONTENT_ID,                  /* RFC4229 */
    HTTP_HF_CONTENT_LANGUAGE,            /* RFC7231, Section 3.1.3.2 */
    HTTP_HF_CONTENT_LENGTH,              /* RFC7230, Section 3.3.2 */
    HTTP_HF_CONTENT_LOCATION,            /* RFC7231, Section 3.1.4.2 */
    HTTP_HF_CONTENT_MD5,                 /* RFC4229 */
    HTTP_HF_CONTENT_RANGE,               /* RFC7233, Section 4.2 */
    HTTP_HF_CONTENT_SCRIPT_TYPE,         /* RFC4229 */
    HTTP_HF_CONTENT_STYLE_TYPE,          /* RFC4229 */
    HTTP_HF_CONTENT_TYPE,                /* RFC7231, Section 3.1.1.5 */
    HTTP_HF_CONTENT_VERSION,             /* RFC4229 */
    HTTP_HF_COOKIE,                      /* RFC6265 */
    HTTP_HF_COOKIE2,                     /* RFC2965, RFC6265 */
    HTTP_HF_DASL,                        /* RFC5323 */
    HTTP_HF_DAV,                         /* RFC4918 */
    HTTP_HF_DATE,                        /* RFC7231, Section 7.1.1.2 */
    HTTP_HF_DEFAULT_STYLE,               /* RFC4229 */
    HTTP_HF_DELTA_BASE,                  /* RFC4229 */
    HTTP_HF_DEPTH,                       /* RFC4918 */
    HTTP_HF_DERIVED_FROM,                /* RFC4229 */
    HTTP_HF_DESTINATION,                 /* RFC4918 */
    HTTP_HF_DIFFERENTIAL_ID,             /* RFC4229 */
    HTTP_HF_DIGEST,                      /* RFC4229 */
    HTTP_HF_ETAG,                        /* RFC7232, Section 2.3 */
    HTTP_HF_EXPECT,                      /* RFC7231, Section 5.1.1 */
    HTTP_HF_EXPIRES,                     /* RFC7234, Section 5.3 */
    HTTP_HF_EXT,                         /* RFC4229 */
    HTTP_HF_FORWARDED,                   /* RFC7239 */
    HTTP_HF_FROM,                        /* RFC7231, Section 5.5.1 */
    HTTP_HF_GETPROFILE,                  /* RFC4229 */
    HTTP_HF_HOBAREG,                     /* RFC7486, Section 6.1.1 */
    HTTP_HF_HOST,                        /* RFC7230, Section 5.4 */
    HTTP_HF_HTTP2_SETTINGS,              /* RFC7540, Section 3.2.1 */
    HTTP_HF_IM,                          /* RFC4229 */
    HTTP_HF_IF,                          /* RFC4918 */
    HTTP_HF_IF_MATCH,                    /* RFC7232, Section 3.1 */
    HTTP_HF_IF_MODIFIED_SINCE,           /* RFC7232, Section 3.3 */
    HTTP_HF_IF_NONE_MATCH,               /* RFC7232, Section 3.2 */
    HTTP_HF_IF_RANGE,                    /* RFC7233, Section 3.2 */
    HTTP_HF_IF_SCHEDULE_TAG_MATCH,       /* RFC6638 */
    HTTP_HF_IF_UNMODIFIED_SINCE,         /* RFC7232, Section 3.4 */
    HTTP_HF_KEEP_ALIVE,                  /* RFC4229 */
    HTTP_HF_LABEL,                       /* RFC4229 */
    HTTP_HF_LAST_MODIFIED,               /* RFC7232, Section 2.2 */
    HTTP_HF_LINK,                        /* RFC5988 */
    HTTP_HF_LOCATION,                    /* RFC7231, Section 7.1.2 */
    HTTP_HF_LOCK_TOKEN,                  /* RFC4918 */
    HTTP_HF_MAN,                         /* RFC4229 */
    HTTP_HF_MAX_FORWARDS,                /* RFC7231, Section 5.1.2 */
    HTTP_HF_MEMENTO_DATETIME,            /* RFC7089 */
    HTTP_HF_METER,                       /* RFC4229 */
    HTTP_HF_MIME_VERSION,                /* RFC7231, Appendix A.1 */
    HTTP_HF_NEGOTIATE,                   /* RFC4229 */
    HTTP_HF_OPT,                         /* RFC4229 */
    HTTP_HF_ORDERING_TYPE,               /* RFC4229 */
    HTTP_HF_ORIGIN,                      /* RFC6454 */
    HTTP_HF_OVERWRITE,                   /* RFC4918 */
    HTTP_HF_P3P,                         /* RFC4229 */
    HTTP_HF_PEP,                         /* RFC4229 */
    HTTP_HF_PICS_LABEL,                  /* RFC4229 */
    HTTP_HF_PEP_INFO,                    /* RFC4229 */
    HTTP_HF_POSITION,                    /* RFC4229 */
    HTTP_HF_PRAGMA,                      /* RFC7234, Section 5.4 */
    HTTP_HF_PREFER,                      /* RFC7240 */
    HTTP_HF_PREFERENCE_APPLIED,          /* RFC7240 */
    HTTP_HF_PROFILEOBJECT,               /* RFC4229 */
    HTTP_HF_PROTOCOL,                    /* RFC4229 */
    HTTP_HF_PROTOCOL_INFO,               /* RFC4229 */
    HTTP_HF_PROTOCOL_QUERY,              /* RFC4229 */
    HTTP_HF_PROTOCOL_REQUEST,            /* RFC4229 */
    HTTP_HF_PROXY_AUTHENTICATE,          /* RFC7235, Section 4.3 */
    HTTP_HF_PROXY_AUTHENTICATION_INFO,   /* RFC7615, Section 4 */
    HTTP_HF_PROXY_AUTHORIZATION,         /* RFC7235, Section 4.4 */
    HTTP_HF_PROXY_FEATURES,              /* RFC4229 */
    HTTP_HF_PROXY_INSTRUCTION,           /* RFC4229 */
    HTTP_HF_PUBLIC,                      /* RFC4229 */
    HTTP_HF_PUBLIC_KEY_PINS,             /* RFC7469 */
    HTTP_HF_PUBLIC_KEY_PINS_REPORT_ONLY, /* RFC7469 */
    HTTP_HF_RANGE,                       /* RFC7233, Section 3.1 */
    HTTP_HF_REDIRECT_REF,                /* RFC4437 */
    HTTP_HF_REFERER,                     /* RFC7231, Section 5.5.2 */
    HTTP_HF_RETRY_AFTER,                 /* RFC7231, Section 7.1.3 */
    HTTP_HF_SAFE,                        /* RFC4229 */
    HTTP_HF_SCHEDULE_REPLY,              /* RFC6638 */
    HTTP_HF_SCHEDULE_TAG,                /* RFC6638 */
    HTTP_HF_SEC_WEBSOCKET_ACCEPT,        /* RFC6455 */
    HTTP_HF_SEC_WEBSOCKET_EXTENSIONS,    /* RFC6455 */
    HTTP_HF_SEC_WEBSOCKET_KEY,           /* RFC6455 */
    HTTP_HF_SEC_WEBSOCKET_PROTOCOL,      /* RFC6455 */
    HTTP_HF_SEC_WEBSOCKET_VERSION,       /* RFC6455 */
    HTTP_HF_SECURITY_SCHEME,             /* RFC4229 */
    HTTP_HF_SERVER,                      /* RFC7231, Section 7.4.2 */
    HTTP_HF_SET_COOKIE,                  /* RFC6265 */
    HTTP_HF_SET_COOKIE2,                 /* RFC2965, RFC6265 */
    HTTP_HF_SETPROFILE,                  /* RFC4229 */
    HTTP_HF_SLUG,                        /* RFC5023 */
    HTTP_HF_SOAPACTION,                  /* RFC4229 */
    HTTP_HF_STATUS_URI,                  /* RFC4229 */
    HTTP_HF_STRICT_TRANSPORT_SECURITY,   /* RFC6797 */
    HTTP_HF_SURROGATE_CAPABILITY,        /* RFC4229 */
    HTTP_HF_SURROGATE_CONTROL,           /* RFC4229 */
    HTTP_HF_TCN,                         /* RFC4229 */
    HTTP_HF_TE,                          /* RFC7230, Section 4.3 */
    HTTP_HF_TIMEOUT,                     /* RFC4918 */
    HTTP_HF_TRAILER,                     /* RFC7230, Section 4.4 */
    HTTP_HF_TRANSFER_ENCODING,           /* RFC7230, Section 3.3.1 */
    HTTP_HF_URI,                         /* RFC4229 */
    HTTP_HF_UPGRADE,                     /* RFC7230, Section 6.7 */
    HTTP_HF_USER_AGENT,                  /* RFC7231, Section 5.5.3 */
    HTTP_HF_VARIANT_VARY,                /* RFC4229 */
    HTTP_HF_VARY,                        /* RFC7231, Section 7.1.4 */
    HTTP_HF_VIA,                         /* RFC7230, Section 5.7.1 */
    HTTP_HF_WWW_AUTHENTICATE,            /* RFC7235, Section 4.1 */
    HTTP_HF_WANT_DIGEST,                 /* RFC4229 */
    HTTP_HF_WARNING,                     /* RFC7234, Section 5.5 */
    HTTP_HF_X_FRAME_OPTIONS,             /* RFC7034 */

    HTTP_HF_MAX                          /* must be last, number of header */
                                         /* fields known by this implementation */
    } HTTP_HF;

typedef enum httpStatusCode
    {
    HTTP_SC_CONTINUE            = 100,  /* RFC7231 chapter 6.2.1 */
    HTTP_SC_SWITCHING_PROTOCOLS = 101,  /* RFC7231 chapter 6.2.2 */

    HTTP_SC_OK                  = 200,  /* RFC7231 chapter 6.3.1 */
    HTTP_SC_CREATED             = 201,  /* RFC7231 chapter 6.3.2 */
    HTTP_SC_ACCEPTED            = 202,  /* RFC7231 chapter 6.3.3 */
    HTTP_SC_NON_AUTHORITATIVE_INFORMATION = 203, /* RFC7231 chapter 6.3.4 */
    HTTP_SC_NO_CONTENT          = 204,  /* RFC7231 chapter 6.3.5 */
    HTTP_SC_RESET_CONTENT       = 205,  /* RFC7231 chapter 6.3.6 */

    HTTP_SC_MULTIPLE_CHOICES    = 300,  /* RFC7231 chapter 6.4.1 */
    HTTP_SC_MOVED_PERMANENTLY   = 301,  /* RFC7231 chapter 6.4.2 */
    HTTP_SC_FOUND               = 302,  /* RFC7231 chapter 6.4.3 */
    HTTP_SC_SEE_OTHER           = 303,  /* RFC7231 chapter 6.4.4 */
    HTTP_SC_USE_PROXY           = 305,  /* RFC7231 chapter 6.4.5 */
    HTTP_SC_TEMPORARY_REDIRECT  = 307,  /* RFC7231 chapter 6.4.7 */

    HTTP_SC_BAD_REQUEST         = 400,  /* RFC7231 chapter 6.5.1 */
    HTTP_SC_PAYMENT_REQUIRED    = 402,  /* RFC7231 chapter 6.5.2 */
    HTTP_SC_FORBIDDEN           = 403,  /* RFC7231 chapter 6.5.3 */
    HTTP_SC_NOT_FOUND           = 404,  /* RFC7231 chapter 6.5.4 */
    HTTP_SC_METHOD_NOT_ALLOWED  = 405,  /* RFC7231 chapter 6.5.5 */
    HTTP_SC_NOT_ACCEPTABLE      = 406,  /* RFC7231 chapter 6.5.6 */
    HTTP_SC_REQUEST_TIMEOUT     = 408,  /* RFC7231 chapter 6.5.7 */
    HTTP_SC_CONFLICT            = 409,  /* RFC7231 chapter 6.5.8 */
    HTTP_SC_GONE                = 410,  /* RFC7231 chapter 6.5.9 */
    HTTP_SC_LENGTH_REQUIRED     = 411,  /* RFC7231 chapter 6.5.10 */
    HTTP_SC_PAYLOAD_TOO_LARGE   = 413,  /* RFC7231 chapter 6.5.11 */
    HTTP_SC_URI_TOO_LONG        = 414,  /* RFC7231 chapter 6.5.12 */
    HTTP_SC_UNSUPPORTED_MEDIA_TYPE = 415, /* RFC7231 chapter 6.5.13 */
    HTTP_SC_EXPECTATION_FAILED  = 417,  /* RFC7231 chapter 6.5.14 */
    HTTP_SC_UPGRADE_REQUIRED    = 426,  /* RFC7231 chapter 6.5.15 */

    HTTP_SC_INTERNAL_SERVER_ERROR = 500, /* RFC7231 chapter 6.6.1 */
    HTTP_SC_NOT_IMPLEMENTED     = 501,  /* RFC7231 chapter 6.6.2 */
    HTTP_SC_BAD_GATEWAY         = 502,  /* RFC7231 chapter 6.6.3 */
    HTTP_SC_SERVICE_UNAVAILABLE = 503,  /* RFC7231 chapter 6.6.4 */
    HTTP_SC_GATEWAY_TIMEOUT     = 504,  /* RFC7231 chapter 6.6.5 */
    HTTP_SC_HTTP_VERSION_NOT_SUPPORTED = 505, /* RFC7231 chapter 6.6.6 */

    } HTTP_SC;

typedef void    (*HTTP_REQ_RTN)         (const HTTP_REQ req, HTTP_RES res);
typedef void    (*HTTP_CLOSE_RTN)       (HTTP_RES res);
typedef void    (*HTTP_FINISH_RTN)      (HTTP_RES res);

/* function declarations */

extern HTTP_ID          httpCreate              (int sock, HTTP_REQ_RTN reqRtn);
extern void             httpDelete              (HTTP_ID ctx);
extern void             httpProcess             (HTTP_ID ctx);
extern void             httpDoneSet             (HTTP_ID ctx);
extern BOOL             httpIsSessionActive     (const HTTP_ID ctx);
extern BOOL             httpRdCheck             (const HTTP_ID ctx);
extern BOOL             httpWrCheck             (const HTTP_ID ctx);
extern int              httpErrnoGet            (const HTTP_ID ctx);
extern int              httpSockGet             (const HTTP_ID ctx);
extern void *           httpUsrCtxGet           (HTTP_ID ctx);
extern void             httpUsrCtxSet           (HTTP_ID ctx, void * usrCtx);

extern HTTP_MTD         httpMethodGet           (const HTTP_REQ req);
extern const char *     httpRequestTargetGet    (const HTTP_REQ req);
extern HTTP_REQ_TGT_FRM httpRequestTargetFormGet (const HTTP_REQ req);
extern HTTP_VER         httpVersionGet          (const HTTP_REQ req);
extern const char *     httpHeaderFieldGet      (const HTTP_REQ req, HTTP_HF hf);
extern const void *     httpPayloadGet          (const HTTP_REQ req, size_t * payloadLen);

extern HTTP_ID          httpIdGet               (HTTP_RES res);
extern void             httpVersionSet          (HTTP_RES res, const HTTP_VER * ver);
extern void             httpStatusCodeSet       (HTTP_RES res, HTTP_SC sc);
extern void             httpCloseRtnSet         (HTTP_RES res, HTTP_CLOSE_RTN closeRtn);
extern void             httpFinishRtnSet        (HTTP_RES res, HTTP_FINISH_RTN closeRtn);
extern void             httpHeaderFieldSet      (HTTP_RES res, HTTP_HF hf, const char * val);
extern BOOL             httpWrite               (HTTP_RES res, const void * data, size_t dataLen);
extern BOOL             httpEnd                 (HTTP_RES res);
extern BOOL             httpWriteAndEnd         (HTTP_RES res, const void * data, size_t dataLen);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INChttpBaseLibh */
