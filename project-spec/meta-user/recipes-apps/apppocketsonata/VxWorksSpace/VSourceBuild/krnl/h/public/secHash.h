/* secHash.h - SEC_HASH library header file */

/*
 * Copyright (C) 2015, 2017 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
18oct17,rjq  Should not use C++ keyword template. (V7SEC-512)
18sep15,rbo  Added PKCS5 PBKDF2 and HMAC APIs.
09jan15,rbo  Created
*/

/* includes */

#ifndef __INCsecHashh
#define __INCsecHashh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

/* typedefs */

/* function declarations */

#include <vxWorks.h>

#define SEC_HASH_ID_BASE   0
#define SEC_HASH_ID_MD5    1 + SEC_HASH_ID_BASE
#define SEC_HASH_ID_SHA1   2 + SEC_HASH_ID_BASE
#define SEC_HASH_ID_SHA256 3 + SEC_HASH_ID_BASE
#define SEC_HASH_ID_SHA384 4 + SEC_HASH_ID_BASE
#define SEC_HASH_ID_SHA512 5 + SEC_HASH_ID_BASE
#define SEC_HASH_ID_RMD    6 + SEC_HASH_ID_BASE
#define SEC_HASH_ID_WHIRLPOOL 6 + SEC_HASH_ID_BASE

#define SEC_HASH_DIGEST_LEN_MD5    16
#define SEC_HASH_DIGEST_LEN_RMD    20
#define SEC_HASH_DIGEST_LEN_SHA1   20
#define SEC_HASH_DIGEST_LEN_SHA256 32
#define SEC_HASH_DIGEST_LEN_SHA384 48
#define SEC_HASH_DIGEST_LEN_SHA512 64
#define SEC_HASH_DIGEST_LEN_WHIRLPOOL 64
#define SEC_HASH_DIGEST_LEN_MAX    64

struct SEC_HASH_CTX_ST;
struct SEC_HASH_TEMPLATE_ST;

typedef struct SEC_HASH_TEMPLATE_ST
    {
    int type;
    int md_size;
    int blockSize;
    STATUS (*init)(struct SEC_HASH_CTX_ST* ctx, const struct SEC_HASH_TEMPLATE_ST* hash_template);
    STATUS (*update)(struct SEC_HASH_CTX_ST* ctx,const void* data,size_t count);
    STATUS (*final)(struct SEC_HASH_CTX_ST* ctx,unsigned char* digest, unsigned int* digestLen);
    STATUS (*ctrl)(struct SEC_HASH_CTX_ST* ctx, int type, void* arg, unsigned int* len);
    STATUS (*copy)(struct SEC_HASH_CTX_ST* copy, struct SEC_HASH_CTX_ST* org);
    void (*cleanup)(struct SEC_HASH_CTX_ST* ctx);
} SEC_HASH_TEMPLATE;

typedef struct SEC_HASH_CTX_ST
 {
     const SEC_HASH_TEMPLATE* hash;
     unsigned long flags;
     char* data;
} SEC_HASH_CTX;

    /* Use secHash() if you have one consecutive memory segment to hash */
STATUS secHash(const void* data, size_t len, unsigned char* digest, unsigned int *out_len, const SEC_HASH_TEMPLATE* hash_template);

    /* Use secHashInit(), secHashUpdate(), secHashFinal(), and secHashCleanup() if the memory you need to hash
     * is divided into two or more segments. Note that each call to secHashInit() must be matched by a 
     * call to secHashCleanup(). 
     *
     * A normal call sequence would be:
     * SEC_HASH_CTX ctx;
     * secHashInit(&ctx, secHashSha256Templ());
     * secHashUpdate(&ctx, data1, len1);
     * secHashUpdate(&ctx, data2, len2);
     * secHashUpdate(&ctx, data3, len3);
     * secHashFinal(&ctx, digest, &dgst_len);
     * secHashCleanup(&ctx);
     */
STATUS secHashInit(SEC_HASH_CTX* ctx, const SEC_HASH_TEMPLATE* hash_template);
STATUS secHashUpdate(SEC_HASH_CTX* ctx, const void* data, size_t count);
STATUS secHashFinal(SEC_HASH_CTX* ctx, unsigned char* digest, unsigned int* digestLen);
STATUS secHashCtrl(struct SEC_HASH_CTX_ST* ctx, int type, void* arg, unsigned int* len);
void secHashCleanup(SEC_HASH_CTX* ctx);

    /* Use secHashCopy if you need to pre-compute some hashes, and re-use the pre-computed hashes.
     * Note that every call to secHashCopy, must be matched by a call to secHashCleanup().
     *
     * A normal call sequence would be:
     * SEC_HASH_CTX ctx, ctx2;
     * secHashInit(&ctx, secHashSha256Templ());
     * secHashUpdate(&ctx, data1, len1);
     * secHashCopy(&ctx2, &ctx);
     * secHashUpdate(&ctx, data2, len2);
     * secHashFinal(&ctx, digest, &dgst_len);
     * secHashCleanup(&ctx);
     *
     * secHashUpdate(&ctx2, data3, len3);
     * secHashFinal(&ctx2, digest2, &dgst_len2);
     * secHashCleanup(&ctx2);
     *
     * The hash result in digest2 is the same as if the following code had been used:
     * SEC_HASH_CTX, ctx2;
     * secHashInit(&ctx2, secHashSha256Templ());
     * secHashUpdate(&ctx2, data1, len1);
     * secHashUpdate(&ctx2, data3, len3);
     * secHashFinal(&ctx, digest2, &dgst_len2);
     * secHashCleanup(&ctx2);
     */

STATUS secHashCopy(SEC_HASH_CTX* copy, SEC_HASH_CTX* org);

    /* Sets the default template functions. These APIs are used to register a new provider
     * of a hash algorithm  */
void secHashMd5TemplateSet(const SEC_HASH_TEMPLATE* ctx);
void secHashRmdTemplateSet(const SEC_HASH_TEMPLATE* ctx);
void secHashSha1TemplateSet(const SEC_HASH_TEMPLATE* ctx);
void secHashSha256TemplateSet(const SEC_HASH_TEMPLATE* ctx);
void secHashSha384TemplateSet(const SEC_HASH_TEMPLATE* ctx);
void secHashSha512TemplateSet(const SEC_HASH_TEMPLATE* ctx);
void secHashWhirlpoolTemplateSet(const SEC_HASH_TEMPLATE* ctx);

    /* These APIs are used to fetch the default template for hash algorithms */
const SEC_HASH_TEMPLATE* secHashMd5TemplateGet(void);
const SEC_HASH_TEMPLATE* secHashRmdTemplateGet(void);
const SEC_HASH_TEMPLATE* secHashSha1TemplateGet(void);
const SEC_HASH_TEMPLATE* secHashSha256TemplateGet(void);
const SEC_HASH_TEMPLATE* secHashSha384TemplateGet(void);
const SEC_HASH_TEMPLATE* secHashSha512TemplateGet(void);
const SEC_HASH_TEMPLATE* secHashWhirlpoolTemplateGet(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCsecHashh */
