/* assAltern.h - alternative assert code */

/* Copyright 1999, 2010 Wind River Systems, Inc. */

/* 
modification history:
--------------------
01b,27may10,pad  Added 'extern C' statement and protection against multiple
                 inclusions of this header file
01a,31jul99,jkf  T2 merge, tidiness & spelling.
*/

#ifndef __INCassertAlternh
#define __INCassertAlternh

#ifdef ASSERT_SUSP
#include <vxWorks.h>
#include <stdioLib.h>
#include <taskLib.h>

#ifdef assert
#undef assert
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define assert(a)	 if(!(a))\
    {\
    int tId=taskIdSelf();\
    fdprintf(2, "Assertion failed: %s ; task ID: 0x%x\n\
     file: "__FILE__", line: %d.  Task suspended\a\n",\
             #a, tId, __LINE__);\
    taskSuspend(tId);\
    }

#ifdef __cplusplus
    }
#endif

#else /* !ASSERT_SUSP */

#include <assert.h>

#endif	/* ASSERT_SUSP */

#endif /* __INCassertAlternh */
