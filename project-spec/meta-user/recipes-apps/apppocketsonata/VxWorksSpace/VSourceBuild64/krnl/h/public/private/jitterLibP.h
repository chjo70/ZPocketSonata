/* jitterLibP.h - response time jitter measurement tool header */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,03jun11,zl   created
*/

#ifndef __INCjitterLibPh
#define __INCjitterLibPh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

typedef struct jitter_data
    {
    UINT samples;
    UINT isrMax;
    UINT isrAvg;
    UINT taskMax;
    UINT taskAvg;
    } JITTER_DATA;
    
extern JITTER_DATA jitterData;

STATUS jitterLibInit (void);
STATUS jitterClkStart (int clockRate, int jitterTaskPrio);
STATUS jitterClkStop (void);
STATUS jitterReport (void);


#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCjitterLibPh */
