/* semPxShow.h - posix semaphore show routines */

/*
 * Copyright (c) 1993, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
19feb15,pad  Removed K&R style prototypes. Included header files for types.
06apr93,smb written
*/

#ifndef __INCsemPxShowh
#define __INCsemPxShowh

#include <semaphore.h>          /* for sem_t */
#include <types/vxTypesOld.h>   /* for STATUS */

#ifdef __cplusplus
extern "C" {
#endif

/* Function declarations */

extern STATUS semPxShow (sem_t * semDesc, int level);
extern STATUS semPxShowInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCsemPxShowh*/
