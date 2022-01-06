/* classLib.h - object class management library header file */

/* Copyright 1984-2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01l,29apr10,pad  Moved extern C statement after include statements.
01k,23apr04,dcc  removed inclusion of objLib.h and memLib.h
01j,25jun03,dcc  removed non-ANSI prototypes.
01i,14mar03,dcc  moved CLASS_ID definition to types/vxWind.h
01h,15oct93,cd   added #ifndef _ASMLANGUAGE.
01g,22sep92,rrr  added support for c++
01f,04jul92,jcf  cleaned up.
01e,26may92,rrr  the tree shuffle
01d,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01c,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
		 added copyright notice.
01b,26jun90,jcf  added object allocation/termination/etc. count
01a,10dec89,jcf  written.
*/

#ifndef __INCclassLibh
#define __INCclassLibh

#include "vxWorks.h"
#include "vwModNum.h"

#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

#define S_classLib_CLASS_ID_ERROR		(M_classLib | 1)
#define S_classLib_NO_CLASS_DESTROY		(M_classLib | 2)

#ifndef _ASMLANGUAGE

/* Note that CLASS_ID is declared in types/vxWind.h */

extern CLASS_ID classClassId;			/* class object class id */

/* function declarations */

extern STATUS 	classLibInit (void);
extern STATUS 	classMemPartIdSet (CLASS_ID classId, PART_ID memPartId);
extern void 	classShowInit (void);
extern STATUS 	classShow (CLASS_ID classId, int level);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCclassLibh */
