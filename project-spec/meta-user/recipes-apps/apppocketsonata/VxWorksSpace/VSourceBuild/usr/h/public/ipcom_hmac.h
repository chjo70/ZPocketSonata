/*
 ******************************************************************************
 *                     INTERPEAK API HEADER FILE
 *
 *   Document no: @(#) $Name:  $ $RCSfile$ $Revision$
 *   $Source$
 *   $Author$ $Date$
 *   $State$ $Locker$
 *
 *   INTERPEAK_COPYRIGHT_STRING
 *   Design and implementation by Roger Boden <roger.boden@windriver.com>
 ******************************************************************************
 */
#ifndef IPCOM_HMAC_H
#define IPCOM_HMAC_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

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

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */
#define IPCOM_HMAC_MAX_DIGEST 64

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */
    struct Ipcom_hmac_hash_ctx_st
    {
        size_t ctx_len;
        int unsigned digest_len;
        int (*init)(void* hash_ctx);
        int (*update)(void* hash_ctx, const void *data, int count);
        int (*final)(void* hash_ctx, unsigned char *md);
        void (*cleanup)(void* hash_ctx);
    };
    typedef struct Ipcom_hmac_hash_ctx_st Ipcom_hmac_hash_ctx;

    struct Ipcom_hmac_ctx_st
    {
        int hash_id;
        int key_len;
        unsigned char k_ipad[64];
        unsigned char k_opad[64];
        const Ipcom_hmac_hash_ctx* hash_ctx;
        void* hash_ctx_data;
    };
    typedef struct Ipcom_hmac_ctx_st Ipcom_hmac_ctx;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

     unsigned char *ipcom_hmac(const Ipcom_hmac_hash_ctx *hash_ctx, const void* key,
                                        int key_len, const unsigned char *d, int n,
                                        unsigned char *digest, unsigned int *digest_len);

    /* Each call to ipcom_hmac_init must be matched by a call to ipcom_hmac_cleanup */
     void ipcom_hmac_ctx_init(Ipcom_hmac_ctx *ctx);

     void ipcom_hmac_init(Ipcom_hmac_ctx *ctx, const void *key, int key_len,
                         const Ipcom_hmac_hash_ctx *md);
     void ipcom_hmac_update(Ipcom_hmac_ctx *ctx, const unsigned char *data, int len);
     void ipcom_hmac_final(Ipcom_hmac_ctx *ctx, unsigned char *md, unsigned int *len);

     void ipcom_hmac_ctx_cleanup(Ipcom_hmac_ctx *ctx);

     Ipcom_hmac_hash_ctx* ipcom_sha256(void);

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
