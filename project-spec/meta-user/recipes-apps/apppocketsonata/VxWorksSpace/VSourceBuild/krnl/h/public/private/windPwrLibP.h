/* windPwrLibP.h - VxWorks power library private header file */

/*
 * Copyright (c) 2002-2003, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,09aug11,rbc  WIND00238999 - Fix build error for windPwrDown()
01d,29apr10,pad  Moved extern C statement after include statements.
01c,02oct09,zl   removed unnecessary header files
01b,01jul03,rec  code review comments
01a,29apr02,rec  Created
*/

#ifndef __INCwindPwrLibPh
#define __INCwindPwrLibPh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* variable declarations */

extern BOOL     windPwrOffState;

/* function declarations */

#ifndef _WRS_ARCH_HAS_WIND_PWR_DOWN
#define WIND_PWR_DOWN()
#else
extern void windPwrDown (void);
extern void windPwrUp (void);
#endif /* _WRS_ARCH_HAS_WIND_PWR_DOWN */


#ifdef __cplusplus
}
#endif

#endif /* __INCwindPwrLibPh */
