/* dataCollectorShow.h - data collector show routines */

/*
 * Copyright (c) 2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,21may08,tcr  rename file
01a,08may08,tcr  created
*/

#ifndef __dataCollectorShowh
#define __dataCollectorShowh

#include <dataCollectorLib.h>

#ifdef __cplusplus
extern "C" {
#endif

STATUS dataCollectorShowInit (void);
STATUS dataCollectorShow (DATA_COLLECTOR_ID pCollector, int verbosity);
STATUS dataCollectorShowAll (int verbosity);

#ifdef __cplusplus
}
#endif

#endif /* __dataCollectorShowh */

