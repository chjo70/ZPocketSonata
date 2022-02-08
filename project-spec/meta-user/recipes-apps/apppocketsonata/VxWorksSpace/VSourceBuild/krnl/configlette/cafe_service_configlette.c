/* cafe_service_configlette.c - Configlette for CAFE */

/*
 * Copyright (c) 2011, 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
20jan15,tle  Remove misleading static qualifier from VX_TASK macro (V7COR-2371)
13may14,sdt  Rename cafe tasks to tAnalysis* - US37854
07feb14,sdt  Rename cafe task name - WB4-2607
11dec13,rlp  Changes TCF event task name (WIND00439058).
*/

#include <vxWorks.h>
#include <taskLib.h>
#include <logLib.h>
#include <vxworks/cafe_vx_types.h>
#include <cafe/ep/config_service.h>
#include <tcfLib.h>

#define VX_TCF_TASK_OPTIONS	(VX_FP_TASK | VX_UNBREAKABLE)
#define EVENT_STACK_SIZE	(8*1024)

VX_TASK(tAnalysisAgentEvents, EVENT_STACK_SIZE);


void cafe_service_init(unsigned int tcf_priority)
{
	TASK_ID_TYPE event_task;

	tcf_init_service(ini_cafe_config_service);

	event_task = VX_TASK_INSTANTIATE(tAnalysisAgentEvents, tcf_priority + 1,
					 VX_TCF_TASK_OPTIONS,
					 EVENT_STACK_SIZE, cafe_event_thread,
					 0,1,2,3,4,5,6,7,8,9);

	if (event_task == TASK_ID_ERROR)
		logMsg("Error starting Cafe TCF service task: %u\n",
		       errno, 2,3,4,5,6);
}
