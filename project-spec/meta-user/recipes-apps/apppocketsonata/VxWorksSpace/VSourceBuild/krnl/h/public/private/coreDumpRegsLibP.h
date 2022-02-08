/* coreDumpRegsLibP.h - core dump registers definition header */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
19dec14,jmp  written.
*/

#ifndef __INCcoreDumpRegsLibPh
#define __INCcoreDumpRegsLibPh

/* includes */

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef struct coreDumpRegistersDef {
    const char * name;     /* pointer to register name */
    size_t       size;     /* register size in bytes */
    int16_t      dwarf_id; /* ID of the register in DWARF sections, or -1 */
    BOOL         syscall;  /* Available if task in in a system call? */
    const char * role;     /* role the register plays in a program execution */
    UINT64       value;    /* register value */
} CORE_DUMP_REGISTERS_DEF;

/* defines */

#define VALID_IN_SYSCALL        TRUE

#ifdef __cplusplus
}
#endif

#endif /* __INCcoreDumpRegsLibPh */
