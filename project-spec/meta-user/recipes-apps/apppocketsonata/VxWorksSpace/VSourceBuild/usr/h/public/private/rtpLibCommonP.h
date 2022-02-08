/* rtpLibCommonP.h - common RTP management private definitions */

/* 
 * Copyright (c) 2015 Wind River Systems, Inc. 
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
29oct15,rr   created
*/

#ifndef __INCrtpLibCommonPh
#define __INCrtpLibCommonPh

#include <vxWorks.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

#ifndef _ASMLANGUAGE

/* forward declarations */

extern STATUS _rtpTaskExitRegister(void * funcPtr);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCrtpLibCommonPh */
