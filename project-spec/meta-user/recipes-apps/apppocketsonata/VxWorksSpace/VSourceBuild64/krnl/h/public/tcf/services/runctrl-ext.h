/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * Extension point definitions for runctrl.c.
 *
 */

#if ENABLE_WR_LivePatchProxy
#include <system/VxWorks/tcf/context-vxworks.h>

extern int check_skip_function (Context * ctx, ContextAddress addr);

#define HIDDEN_HOOK { \
    int skip = check_skip_function(ctx, ip); \
    if (skip == 1) \
         return (skip); \
}
#else
#define HIDDEN_HOOK do {} while(0)
#endif
