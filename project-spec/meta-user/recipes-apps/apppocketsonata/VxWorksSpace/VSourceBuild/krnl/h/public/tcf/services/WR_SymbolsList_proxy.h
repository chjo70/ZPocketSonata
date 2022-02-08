/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * TCF WR_SymbolsList service - proxy version.
 *
 */

#ifndef WR_SYMBOLS_LIST_PROXY_H
#define WR_SYMBOLS_LIST_PROXY_H

#include <tcf/framework/channel.h>

#define SEARCH_NAME_CONTAIN	"Contain"
#define SEARCH_NAME_MATCH	"Match"
#define SEARCH_NAME_START_WITH	"StartWith"

#define VISIBILITY_GLOBAL	"Global"
#define VISIBILITY_LOCAL	"Local"

#define KIND_FUNCTION		"Function"
#define KIND_VARIABLE		"Variable"

/*
 * Get address of symbol with name 'name'
 */
extern int wr_get_symbol_addr(pid_t pid, const char * name, const char * kind, const char * visibility, ContextAddress * addr);

#endif /* WR_SYMBOLS_LIST_PROXY_H */
