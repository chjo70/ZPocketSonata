/* datasetP.h - dataset utility header */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
18dec13,cww  made this file private
01b,22sep13,x_z  code cleaned.
01a,18apr13,l_z  created
*/

#ifndef __INCdatasetPh
#define __INCdatasetPh

#include <vxWorks.h>
#include <vsbConfig.h>

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

/* dataset defines */

#define DATASET_NAME_LEN     31
#define DATASET_ORDER_MIN    0
#define DATASET_ORDER_MAX    32

typedef struct dataset
    {
    char 	name[DATASET_NAME_LEN + 1];
    int 	order;
    void *	pData;
    } DATASET;

#ifdef _WRS_CONFIG_LP64
#define DATA_SET(set, order, data)                      \
    __attribute__((section(".data.set"), aligned(8)))   \
    DATASET __dataset__##set##_##data =                 \
    {                                                   \
    #set,                                               \
    order,                                              \
    (void *) &data                                      \
    };
#else
#define DATA_SET(set, order, data)                      \
    __attribute__((section(".data.set"), aligned(4)))   \
    DATASET __dataset__##set##_##data =                 \
    {                                                   \
    #set,                                               \
    order,                                              \
    (void *) &data                                      \
    };
#endif

typedef STATUS DATASET_CALLBACK_RTN
    (
    void *  pArg,   /* pointer to parameter from caller */
    void *  pData   /* data pointer of dataset          */
    );

/* dataset utility routine */

void datasetIterate
    (
    char *                  pName,      /* dataset name                 */
    int                     orderMin,   /* start order                  */
    int                     orderMax,   /* end order                    */
    DATASET_CALLBACK_RTN *  pRtn,       /* call back routine            */
    void *                  pArg        /* call back routine parameter  */
    );

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */
#endif /* __INCdatasetPh */

