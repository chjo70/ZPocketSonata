/* secPbkdf2.h - PBKDF2 library header file */

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

#ifndef __INCsecPbkdf2h
#define __INCsecPbkdf2h

/* includes */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

/* typedefs */

/* function declarations */
STATUS secPbkdf2Hmac
    (
    const char *pw, 
    int pwLen,
    const unsigned char *salt,
    int saltLen, 
    int c,
    const SEC_HASH_TEMPLATE *hash,
    int keyLen,
    unsigned char *key
    );


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCsecPbkdf2h */
