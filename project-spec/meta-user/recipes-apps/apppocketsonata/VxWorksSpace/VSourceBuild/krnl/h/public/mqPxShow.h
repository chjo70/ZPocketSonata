/* mqPxShow.h - private POSIX message queue library header */

/* Copyright 1984-1992, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,02dec93,dvs  written
*/

#ifndef __INCmqPxShowh
#define __INCmqPxShowh

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS	mqPxShowInit (void);

#else	/* __STDC__ */

extern STATUS	mqPxShowInit ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCmqPxShowh */
