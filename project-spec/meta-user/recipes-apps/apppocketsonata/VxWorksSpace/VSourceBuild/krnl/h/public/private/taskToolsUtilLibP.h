/* taskToolsUtilLibP.h - private task tool utilities header */

/*
 * Copyright (c) 2007-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01e,29apr10,pad  Moved extern C statement after include statements.
01d,22apr09,pcs  Update to add support for LP64 data model.
01c,27aug08,jpb  Renamed VSB header file
01b,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01a,19mar07,gls  written
*/

#ifndef __INCtaskToolsUtilLibPh
#define __INCtaskToolsUtilLibPh

	
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* task status values */

#define TASK_LIB_CPU_NO_INFO           0x00
#define TASK_LIB_CPU_HOLDS_SPINLOCK    0x01
#define TASK_LIB_CPU_HOLDS_KERNEL_LOCK 0x02

#ifndef _ASMLANGUAGE

/* function declarations */

#ifdef	_WRS_CONFIG_SMP
extern STATUS taskInfoByCpuGet (int cpuNum, TASK_ID *pTid, int *pStateInfo);
#endif

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskToolsUtilLibPh */
