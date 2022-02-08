/* randomNumGen.h - random number generator header file */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
23jul15,rr   Corrected compiler error for cpp (V7COR-3273)
14aug14,jpb  US34996: implement a random number generator
*/

#ifndef __INCrandomNumGenh
#define __INCrandomNumGenh

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { 
    RANDOM_NUM_GEN_NO_ENTROPY, 
    RANDOM_NUM_GEN_NOT_ENOUGH_ENTROPY, 
    RANDOM_NUM_GEN_ENOUGH_ENTROPY, 
    RANDOM_NUM_GEN_MAX_ENTROPY,
    RANDOM_NUM_GEN_ERROR
} RANDOM_NUM_GEN_STATUS;

STATUS randBytes (unsigned char *randBuf, int numOfBytes);
STATUS randPseudoBytes (unsigned char *randBuf, int numOfBytes);
STATUS randAdd (const void *buf, int num, int entropy);
RANDOM_NUM_GEN_STATUS randStatus (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCrandomNumGenh */
