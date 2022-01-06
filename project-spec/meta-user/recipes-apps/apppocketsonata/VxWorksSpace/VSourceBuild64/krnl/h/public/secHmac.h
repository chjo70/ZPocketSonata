/* secHmac.h - HMAC library header file */

/*
 * Copyright (C) 2015 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
18sep15,rbo  Created
*/

#ifndef __INCsecHmach
#define __INCsecHmach

/* includes */
#include <secHash.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */
#define SEC_HMAC_MAX_BLOCK 128

/* typedefs */
struct SEC_HMAC_CTX_ST
    {
    SEC_HASH_CTX hashCtx;
    unsigned char k_ipad[SEC_HMAC_MAX_BLOCK];
    unsigned char k_opad[SEC_HMAC_MAX_BLOCK];
    unsigned int keyLen;
    };
typedef struct SEC_HMAC_CTX_ST SEC_HMAC_CTX;

/* function declarations */
STATUS secHmacInit(SEC_HMAC_CTX* ctx, const unsigned char* key, int keyLen, const SEC_HASH_TEMPLATE* hashTemplate);
STATUS secHmacUpdate(SEC_HMAC_CTX* ctx, const unsigned char* data, unsigned int dataLen);
STATUS secHmacFinal(SEC_HMAC_CTX* ctx, unsigned char* hmac, unsigned int* hmacLen);
void secHmacCleanup(SEC_HMAC_CTX* ctx);
STATUS secHmac(const unsigned char* key, int keyLen, unsigned char* data, unsigned int dataLen,
               unsigned char* hmac, unsigned int* hmacLen, const SEC_HASH_TEMPLATE* hashTemplate);
STATUS secHmacCopy(SEC_HMAC_CTX* copy, SEC_HMAC_CTX* org);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCsecHmach */
