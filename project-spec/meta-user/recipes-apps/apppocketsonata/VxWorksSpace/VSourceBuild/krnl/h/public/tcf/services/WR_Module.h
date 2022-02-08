/*
 * Copyright (c) 2012-2013,2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef WR_MODULE_SERVICE_H
#define WR_MODULE_SERVICE_H

#include <tcf/config.h>
#include <tcf/framework/protocol.h>
#include <tcf/framework/cpudefs.h>
#include <tcf/framework/context.h>
#include <vxWorks.h>
#include <loadLib.h>
#include <unldLib.h>
#include <moduleLib.h>
#include <private/moduleLibP.h>
#include <private/moduleHookLibP.h>

extern void ini_wr_module_service(Protocol * proto, TCFBroadcastGroup * bcg);
extern void add_private_modules_info (MODULE_ID modId, MemoryRegion *r);
extern void notify_module_loaded(MODULE_ID modId);

#endif /* WR_MODULE_SERVICE_H */
