/*******************************************************************************
 * Copyright (c) 2015 Wind River Systems, Inc. and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 * The Eclipse Public License is available at
 * http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 * http://www.eclipse.org/org/documents/edl-v10.php.
 * You may elect to redistribute this code under either of these licenses.
 *
 * Contributors:
 *     Wind River Systems - initial API and implementation
 *******************************************************************************/

/*
 * Extension point definitions for breakpoint.c.
 *
 * BREAKPOINT_ADDR_ADJUST - adjust breakpoint address if needed.
 */
#if ENABLE_Symbols && (CPU_FAMILY == PPC) && defined (_WRS_CONFIG_LP64)
#define BREAKPOINT_ADDR_ADJUST {                                               \
    ContextAddress sym_addr;                                                   \
    Symbol * symbol = NULL;                                                    \
    SymbolProperties props;                                                    \
    int class = SYM_CLASS_UNKNOWN;                                             \
                                                                               \
    /*                                                                         \
     * If the line addrs matches addrs of a FUNCTION, we may adjust the        \
     * location using the symbol offset. This is to use Local Entry Point      \
     * (LEP) on PPC64 instead of Global entry point (GEP).                     \
     */                                                                        \
    if (find_symbol_by_addr(args->ctx, STACK_NO_FRAME, addr,                   \
                            &symbol) < 0) return;                              \
    if (get_symbol_address(symbol, &sym_addr) < 0) return;                     \
    if (get_symbol_class(symbol, &class) < 0) return;                          \
                                                                               \
    if (sym_addr == addr && class == SYM_CLASS_FUNCTION) {                     \
        /* We want to add the LocalEntryOffset */                              \
        (void)get_symbol_props(symbol, &props);                                \
        /*                                                                     \
         * If the symbol is not a PPC64 function, offset should be 0,          \
         * so it is safe to add.                                               \
         */                                                                    \
        addr += props.local_entry_offset;                                      \
    }                                                                          \
}
#else
#define BREAKPOINT_ADDR_ADJUST do {} while(0)
#endif
