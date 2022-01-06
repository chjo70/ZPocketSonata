/* coreDumpSimntLib.h - SIMNT core dump header file */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16jan15,jmp  Added architecture string and ISA information.
16jan15,afi  added reg defs.
19dec14,jmp  written.
*/

#ifndef __INCcoreDumpSimntLibh
#define __INCcoreDumpSimntLibh

#ifdef _WRS_CONFIG_LP64

/* define architecture type */
#define CORE_DUMP_ARCH  "x86-64"

/* Define ISA parameters for architecture */
#define CORE_DUMP_ISA_DEF "X86_64"
#define CORE_DUMP_ISA_MAX_INST_SIZE (sizeof(INSTR) * 15)

/* Dwarf IDs */
#define DWARF_ID_RAX    0
#define DWARF_ID_RDX    1
#define DWARF_ID_RCX    2
#define DWARF_ID_RBX    3
#define DWARF_ID_RSI    4
#define DWARF_ID_RDI    5
#define DWARF_ID_RBP    6
#define DWARF_ID_RSP    7
#define DWARF_ID_R8     8
#define DWARF_ID_R9     9
#define DWARF_ID_R10    10
#define DWARF_ID_R11    11
#define DWARF_ID_R12    12
#define DWARF_ID_R13    13
#define DWARF_ID_R14    14
#define DWARF_ID_R15    15
#define DWARF_ID_RIP    16
#define DWARF_ID_RFLAGS 49

/* name, size, dwarf_id, role */

static CORE_DUMP_REGISTERS_DEF coreDumpRegistersDef[] = {
    {"rax", 8, DWARF_ID_RAX},
    {"rdx", 8, DWARF_ID_RDX},
    {"rcx", 8, DWARF_ID_RCX},
    {"rbx", 8, DWARF_ID_RBX},
    {"rsi", 8, DWARF_ID_RSI},
    {"rdi", 8, DWARF_ID_RDI},
    {"rbp", 8, DWARF_ID_RBP, VALID_IN_SYSCALL, "FP"},
    {"rsp", 8, DWARF_ID_RSP, VALID_IN_SYSCALL, "SP"},
    {"r8",  8, DWARF_ID_R8},
    {"r9",  8, DWARF_ID_R9},
    {"r10", 8, DWARF_ID_R10},
    {"r11", 8, DWARF_ID_R11},
    {"r12", 8, DWARF_ID_R12},
    {"r13", 8, DWARF_ID_R13},
    {"r14", 8, DWARF_ID_R14},
    {"r15", 8, DWARF_ID_R15},
    {"rip", 8, DWARF_ID_RIP, VALID_IN_SYSCALL, "PC"},
    {"rflags", 8, DWARF_ID_RFLAGS},
    {NULL},
};

#else

/* define architecture type */
#define CORE_DUMP_ARCH  "x86"

/* Define ISA parameters for architecture */
#define CORE_DUMP_ISA_DEF "386"
#define CORE_DUMP_ISA_MAX_INST_SIZE (sizeof(INSTR) * 15)

/* Dwarf IDs */
#define DWARF_ID_EAX    0
#define DWARF_ID_ECX    1
#define DWARF_ID_EDX    2
#define DWARF_ID_EBX    3
#define DWARF_ID_ESP    4
#define DWARF_ID_EBP    5
#define DWARF_ID_ESI    6
#define DWARF_ID_EDI    7
#define DWARF_ID_EIP    8
#define DWARF_ID_EFLAGS 9

/* name, size, dwarf_id, role */

static CORE_DUMP_REGISTERS_DEF coreDumpRegistersDef[] = {
    {"eax", 4, DWARF_ID_EAX},
    {"ecx", 4, DWARF_ID_ECX},
    {"edx", 4, DWARF_ID_EDX},
    {"ebx", 4, DWARF_ID_EBX},
    {"esp", 4, DWARF_ID_ESP, VALID_IN_SYSCALL, "SP"},
    {"ebp", 4, DWARF_ID_EBP, VALID_IN_SYSCALL, "FP"},
    {"esi", 4, DWARF_ID_ESI},
    {"edi", 4, DWARF_ID_EDI},
    {"eip", 4, DWARF_ID_EIP, VALID_IN_SYSCALL, "PC"},
    {"eflags", 4, DWARF_ID_EFLAGS},
    {NULL},
};
#endif
#endif  /* __INCcoreDumpSimntLibh */
