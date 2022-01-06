/* semEvLib.h - semaphore events library header file */

/*
 * Copyright (c) 2001, 2010, 2015 Wind River Systems, Inc.
 * 
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
19feb15,pad  Removed K&R style prototypes. Included header files for types.
29apr10,pad  Moved extern C statement after include statements.
20sep01.bwa  Initial creation.
*/

#ifndef __INCsemEvLibh
#define __INCsemEvLibh

#include <vxWorks.h>
#include <semLib.h>
#include <types/vxTypesOld.h>   /* for STATUS, UINT32 and UINT8 */
#include <types/vxWind.h>       /* for SEM_ID */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* function declarations */

extern STATUS 	semEvStart (SEM_ID semId, UINT32 events, UINT8 options);
extern STATUS	semEvStop  (SEM_ID semId);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsemEvLibh */

