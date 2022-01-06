/* b_pthread_once_t.h - base type pthread_once_t definition header */

/*
 * Copyright (c) 2006-2007, 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software 
 * may be licensed only pursuant to the terms of an applicable Wind River 
 * license agreement. 
 */

/*
modification history
--------------------
01i,26jan11,pad  To abide by the POSIX namespace rules include types/vxWind.h
		 instead of types/vxTypesOld.h to get the definition of
		 _Vx_SEM_ID.
01h,29jul10,pad  Moved extern C statement after include statements.
01g,16aug07,jpb  Re-introduce onceMutex field in pthread_once_t structure
01f,09aug07,pad  Fixed declaration of the pthread_once_t type when
                 _POSIX_C_SOURCE is defined. Used the new _Vx_BOOL type
                 instead of _Bool (different size, defect 100623).
01e,18jul07,jpb  Added field to pthread_once_t.
01d,13mar06,mil  Moved inclusion of b_BOOL.h to non-POSIX block.
01c,01mar06,pes  Added cancellation indicator in POSIX version of
                 pthrad_once_t struct.
01b,27feb06,v_r  Added cancellation indicator in control variable (for
                 SPR#117700 fix).
01a,16feb06,pes  Created.
*/

#ifndef __INCb_pthread_once_th
#define __INCb_pthread_once_th

#ifndef _DEFINED_pthread_once_t
#define _DEFINED_pthread_once_t

#include <types/vxWind.h>
#include <base/b_BOOL.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

/*
 * This structure's content should not be referenced directly. Use the
 * PTHREAD_ONCE_INIT macro instead.
 */

typedef struct {
	BOOL	onceInitialized;	/* TRUE if initialized once */
	BOOL	onceDone;		/* TRUE if init func returned */
	TASK_ID	onceMyTid;		/* ID of task calling the init func */
	SEM_ID	onceMutex;		/* TRUE if canceled during init rtn */
	BOOL 	onceCanceled;	/* TRUE if init func returned or canceled */
	} pthread_once_t;

#else   /* _POSIX_xxx_SOURCE */

#undef onceInitialized
#undef onceDone
#undef onceMyTid
#undef onceMutex
#undef onceCanceled
#undef onceInitFlag

/*
 * This structure's content should not be referenced directly. Use the
 * PTHREAD_ONCE_INIT macro instead.
 */

typedef struct {
	_Vx_BOOL onceInitialized;	/* TRUE if initialized once */
	_Vx_BOOL onceDone;		/* TRUE if init func returned */
	_Vx_TASK_ID onceMyTid;		/* ID of task calling the init func */
	_Vx_SEM_ID onceMutex;		/* TRUE if canceled during init rtn */
	_Vx_BOOL onceCanceled;	/* TRUE if init func returned or canceled */
	} pthread_once_t;

#endif  /* _POSIX_xxx_SOURCE */
#endif /* _DEFINED_pthread_once_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_pthread_once_th */
