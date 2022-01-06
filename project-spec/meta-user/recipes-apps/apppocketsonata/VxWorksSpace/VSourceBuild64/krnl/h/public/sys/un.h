/* un.h - AF_LOCAL (Unix) header file */

/* Copyright 2003-2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,19feb04,bwa  updated copyright
01b,04dec03,bwa  removed UN_PROTO_COMP definition; removed debugging help
01a,10oct03,bwa  written
*/

#ifndef __INCunh
#define __INCunh

#ifdef __cplusplus
extern "C" {
#endif
     
/* defines */

#define UN_PROTO_MAX         1   /* max nb of protos in AF_LOCAL protosw */

#define UN_SOCKADDR_UN_SIZE  sizeof (struct sockaddr_un)

/* data structures */

struct sockaddr_un              /* LOCAL (UNIX) family address */
    {                           /* --------------------------- */
    uint8_t  sun_len;           /* 0x00: structure size        */
    uint8_t  sun_family;        /* 0x01: address family        */
    char     sun_path [104];    /* 0x02: actual address        */
    };                          /* 0x6A: TOTAL SIZE            */

#ifdef __cplusplus
}
#endif
    
#endif  /* __INCunh */

