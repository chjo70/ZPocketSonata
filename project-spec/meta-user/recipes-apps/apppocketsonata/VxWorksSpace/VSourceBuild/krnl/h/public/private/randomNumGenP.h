/* randomNumGenP.h - private random number generator header file */

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
24jun14,jpb  US34996: implement a random number generator
*/

#ifndef __INCrandomNumGenPh
#define __INCrandomNumGenPh

#include <randomNumGen.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
    {
    STATUS (*pRandBytesRtn)
	(
	unsigned char *buf, 
	int num
	);
    STATUS (*pRandPseudoBytesRtn)
	(
	unsigned char *buf, 
	int num
	);
    STATUS (*pRandAddRtn)
	(
	const void *buf, 
	int num, 
	int entropy
	);
    RANDOM_NUM_GEN_STATUS (*pRandStatusRtn)
	(
	void
	);
    } RANDOM_NUM_GEN_LIB_FUNCS;
    
RANDOM_NUM_GEN_LIB_FUNCS randomNumGenLibFuncs;

void   randomAddTimeStamp (void);
void   randomSWNumGenInit (void);

extern void    (*_func_randomAddTimeStamp)(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCrandomNumGenPh */
