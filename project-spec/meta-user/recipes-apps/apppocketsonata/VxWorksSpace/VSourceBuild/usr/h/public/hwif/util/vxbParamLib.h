/* vxbParamLib.h - vxBus parameter library header file*/

/*
 * Copyright (c) 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
10oct16,g_x  include vxbLib.h (V7PRO-3348)
13may16,wap  Add initialization routine
01jan15,l_z  created
*/

#ifndef _INC_vxbParamLibh
#define _INC_vxbParamLibh

#include <hwif/vxbus/vxbLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* define parameter types */

#define VXB_PARAM_END_OF_LIST   0x0000
#define VXB_PARAM_INT32         0x0001
#define VXB_PARAM_INT64         0x0002
#define VXB_PARAM_STRING        0x0003
#define VXB_PARAM_POINTER       0x0004

typedef union vxbParamValue
    {
    void *	pValue;
    UINT32	int32Val;
    UINT64	int64Val;
    char *	stringVal;
    } VXB_PARAM_VALUE;

/* driver default parameter values */

typedef struct vxbParams
    {
    char *		paramName;
    UINT32		paramType;
    VXB_PARAM_VALUE  	value;
    } VXB_PARAMS;

/* Function prototypes */

STATUS vxbParamTableCreate (VXB_DEV_ID pDev);
void vxbParamTableDestroy (VXB_DEV_ID pDev);

STATUS vxbParamGet
    (
    VXB_DEV_ID		pDev,
    char *		paramName,
    UINT32		paramType,
    VXB_PARAM_VALUE *	pValue
    );

STATUS vxbParamSet
    (
    VXB_DEV_ID		pDev,
    char *		paramName,
    UINT32		paramType,
    VXB_PARAM_VALUE *	pValue
    );

IMPORT void vxbParamLibInit (void);

#ifdef __cplusplus
}
#endif

#include <hwif/methods/vxbParamMethod.h>

#endif /* _INC_vxbParamLibh */

