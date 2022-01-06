/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if SERVICE_WR_LivePatch

#include <tcf/services/linenumbers.h>
#include <tcf/services/dwarfcache.h>
#include <tcf/services/WR_LivePatch.h>

extern void call_client_patch(Context * ctx, CompUnit * unit, LineNumbersState * state,
                        LineNumbersState * code_next, LineNumbersState * text_next,
                        ContextAddress state_addr, LineNumbersCallBack * client, void * args, patch_info * patch);

#endif /* SERVICE_LineNumbers && !ENABLE_LineNumbersProxy && ENABLE_ELF */
