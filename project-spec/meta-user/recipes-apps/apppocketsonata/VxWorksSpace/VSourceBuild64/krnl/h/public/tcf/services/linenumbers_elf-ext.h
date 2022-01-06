/*
 * Copyright (c) 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if SERVICE_WR_LivePatch

#include <tcf/services/patch_linenumbers_elf.h>

#define UNIT_TO_LINE_ADDR_LOCALS_HOOK \
        patch_info * patch = NULL; \

#define UNIT_TO_LINE_ADDR_HOOK \
        patch = get_latest_patch_by_adress (ctx->id, addr, addr + 1); \
        if (patch != NULL) { \
            call_client_patch(ctx, unit, state, code_next, text_next, addr, client, args, patch); \
        } else  \
        /* would call call_client. Ugly mess */ \

#define ADDR_TO_LINE_HOOK  \
        patch_info * patch = get_latest_patch_by_adress (ctx->id, addr0, addr1); \
        if (patch != NULL) { \
            call_client_patch(ctx, unit, state, code_next, text_next, state->mAddress - range->mAddr + range_rt_addr, client, args, patch); \
        } else  \
        /* would call call_client. Ugly mess */ \


#define LINE_TO_ADDR_HOOK_0 \
    CompUnit * patch_unit = NULL; \

/* Theses hooks have 2 purposes:
 * 1/ From renamed name -> find the original name.
 * 2/ Do NOT consider original names for patches since they ALL point to the genuine source :
 *    Only consider the latest patch !!!
 */

#define LINE_TO_ADDR_HOOK_1  \
    if (fnm != NULL) { \
        ContextAddress range_rt_addr = 0; \
        patch_cache * patch = get_latest_patch_by_name (ctx->id, fnm); \
        if (patch != NULL) { \
            LINK * range_node = NULL; \
            list_foreach(range_node, (LINK *) &patch->ranges) { \
                range_cache * cur_range = (range_cache *) range_node; \
                ContextAddress start = cur_range->start; \
                ContextAddress end = cur_range->end; \
                UnitAddressRange * range = elf_find_unit(ctx, start , end - 1, &range_rt_addr); \
                if (range != NULL) { \
                    /* found matching range */ \
                    fnm = canonic_path_map_file_name(patch->genuine_source); \
                    patch_unit = range->mUnit; \
                    break; \
                } \
            } \
        } \
    } \

#define LINE_TO_ADDR_HOOK_2 \
    if (patch_unit != NULL) { \
        if (unit != patch_unit) { \
            f = f->mNextInHash; \
            continue; \
        } \
    } \

#define LINE_TO_ADDR_HOOK_BP \
    if (patch_unit) { \
        /* Only consider if object_patch matches the region */ \
        if (strcmp (patch_unit->mFile->name, r->file_name) != 0) { \
            clear_trap(&trap);  \
            continue; \
        } \
    } \
    else if (is_intermediate_patch(ctx->id, r->file_name, file_name)) { \
        clear_trap(&trap); \
        continue; \
    } \


#else
#define ADDR_TO_LINE_HOOK do {} while(0);
#define LINE_TO_ADDR_HOOK_0 do {} while(0);
#define LINE_TO_ADDR_HOOK_1 do {} while(0);
#define LINE_TO_ADDR_HOOK_2 do {} while(0);
#define LINE_TO_ADDR_HOOK_BP do {} while(0);
#define UNIT_TO_LINE_ADDR_LOCALS_HOOK do {} while(0);
#define UNIT_TO_LINE_ADDR_HOOK do {} while(0);
#endif
