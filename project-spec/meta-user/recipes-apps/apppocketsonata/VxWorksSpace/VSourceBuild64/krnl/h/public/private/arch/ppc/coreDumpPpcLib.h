/* coreDumpPpcLib.h - PPC core dump header file */

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
01jul15,jmp  Set PPC64 ISA to "PPC" (US61521).
13feb15,jmp  Fixed PC Dwarf ID.
16jan15,jmp  Added architecture string and ISA information.
16jan15,afi  added reg defs.
19dec14,jmp  written.
*/

#ifndef __INCcoreDumpPpcLibh
#define __INCcoreDumpPpcLibh

#ifdef _WRS_CONFIG_LP64

/* define architecture type */
#define CORE_DUMP_ARCH  "ppc64"

/* Define ISA parameters for architecture */
#define CORE_DUMP_ISA_DEF "PPC"
#define CORE_DUMP_ISA_MAX_INST_SIZE (sizeof(INSTR) * 4)

/* Dwarf IDs */
#define DWARF_ID_R0      0
#define DWARF_ID_R1      1
#define DWARF_ID_R2      2
#define DWARF_ID_R3      3
#define DWARF_ID_R4      4
#define DWARF_ID_R5      5
#define DWARF_ID_R6      6
#define DWARF_ID_R7      7
#define DWARF_ID_R8      8
#define DWARF_ID_R9      9
#define DWARF_ID_R10    10
#define DWARF_ID_R11    11
#define DWARF_ID_R12    12
#define DWARF_ID_R13    13
#define DWARF_ID_R14    14
#define DWARF_ID_R15    15
#define DWARF_ID_R16    16
#define DWARF_ID_R17    17
#define DWARF_ID_R18    18
#define DWARF_ID_R19    19
#define DWARF_ID_R20    20
#define DWARF_ID_R21    21
#define DWARF_ID_R22    22
#define DWARF_ID_R23    23
#define DWARF_ID_R24    24
#define DWARF_ID_R25    25
#define DWARF_ID_R26    26
#define DWARF_ID_R27    27
#define DWARF_ID_R28    28
#define DWARF_ID_R29    29
#define DWARF_ID_R30    30
#define DWARF_ID_R31    31

#define DWARF_ID_PC     67
#define DWARF_ID_MSR    66
#define DWARF_ID_LR    108
#define DWARF_ID_CTR   109
#define DWARF_ID_CR     64
#define DWARF_ID_XER   101

/* name, size, dwarf_id, role */

static CORE_DUMP_REGISTERS_DEF coreDumpRegistersDef[] = {
    {"r0",  8, DWARF_ID_R0},
    {"r1",  8, DWARF_ID_R1, VALID_IN_SYSCALL,"SP"},
    {"r2",  8, DWARF_ID_R2},
    {"r3",  8, DWARF_ID_R3},
    {"r4",  8, DWARF_ID_R4},
    {"r5",  8, DWARF_ID_R5},
    {"r6",  8, DWARF_ID_R6},
    {"r7",  8, DWARF_ID_R7},
    {"r8",  8, DWARF_ID_R8},
    {"r9",  8, DWARF_ID_R9},
    {"r10", 8, DWARF_ID_R10},
    {"r11", 8, DWARF_ID_R11},
    {"r12", 8, DWARF_ID_R12},
    {"r13", 8, DWARF_ID_R13},
    {"r14", 8, DWARF_ID_R14},
    {"r15", 8, DWARF_ID_R15},
    {"r16", 8, DWARF_ID_R16},
    {"r17", 8, DWARF_ID_R17},
    {"r18", 8, DWARF_ID_R18},
    {"r19", 8, DWARF_ID_R19},
    {"r20", 8, DWARF_ID_R20},
    {"r21", 8, DWARF_ID_R21},
    {"r22", 8, DWARF_ID_R22},
    {"r23", 8, DWARF_ID_R23},
    {"r24", 8, DWARF_ID_R24},
    {"r25", 8, DWARF_ID_R25},
    {"r26", 8, DWARF_ID_R26},
    {"r27", 8, DWARF_ID_R27},
    {"r28", 8, DWARF_ID_R28},
    {"r29", 8, DWARF_ID_R29},
    {"r30", 8, DWARF_ID_R30},
    {"r31", 8, DWARF_ID_R31},
    {"pc",  8, DWARF_ID_PC, VALID_IN_SYSCALL,"PC"},
    {"msr", 8, DWARF_ID_MSR},
    {"lr",  8, DWARF_ID_LR, VALID_IN_SYSCALL,"LR"},
    {"ctr", 8, DWARF_ID_CTR},
    {"cr",  8, DWARF_ID_CR},
    {"xer", 8, DWARF_ID_XER},
    {NULL},
};

#else
/* define architecture type */
#define CORE_DUMP_ARCH  "ppc32"

/* Define ISA parameters for architecture */
#define CORE_DUMP_ISA_DEF "PPC32"
#define CORE_DUMP_ISA_MAX_INST_SIZE (sizeof(INSTR) * 4)

/* Dwarf IDs */
#define DWARF_ID_R0      0
#define DWARF_ID_R1      1
#define DWARF_ID_R2      2
#define DWARF_ID_R3      3
#define DWARF_ID_R4      4
#define DWARF_ID_R5      5
#define DWARF_ID_R6      6
#define DWARF_ID_R7      7
#define DWARF_ID_R8      8
#define DWARF_ID_R9      9
#define DWARF_ID_R10    10
#define DWARF_ID_R11    11
#define DWARF_ID_R12    12
#define DWARF_ID_R13    13
#define DWARF_ID_R14    14
#define DWARF_ID_R15    15
#define DWARF_ID_R16    16
#define DWARF_ID_R17    17
#define DWARF_ID_R18    18
#define DWARF_ID_R19    19
#define DWARF_ID_R20    20
#define DWARF_ID_R21    21
#define DWARF_ID_R22    22
#define DWARF_ID_R23    23
#define DWARF_ID_R24    24
#define DWARF_ID_R25    25
#define DWARF_ID_R26    26
#define DWARF_ID_R27    27
#define DWARF_ID_R28    28
#define DWARF_ID_R29    29
#define DWARF_ID_R30    30
#define DWARF_ID_R31    31

#define DWARF_ID_PC    110
#define DWARF_ID_MSR    66
#define DWARF_ID_LR    108
#define DWARF_ID_CTR   109
#define DWARF_ID_CR     64
#define DWARF_ID_XER   101

/* name, size, dwarf_id, role */

static CORE_DUMP_REGISTERS_DEF coreDumpRegistersDef[] = {
    {"r0",  4, DWARF_ID_R0},
    {"r1",  4, DWARF_ID_R1, VALID_IN_SYSCALL,"SP"},
    {"r2",  4, DWARF_ID_R2},
    {"r3",  4, DWARF_ID_R3},
    {"r4",  4, DWARF_ID_R4},
    {"r5",  4, DWARF_ID_R5},
    {"r6",  4, DWARF_ID_R6},
    {"r7",  4, DWARF_ID_R7},
    {"r8",  4, DWARF_ID_R8},
    {"r9",  4, DWARF_ID_R9},
    {"r10", 4, DWARF_ID_R10},
    {"r11", 4, DWARF_ID_R11},
    {"r12", 4, DWARF_ID_R12},
    {"r13", 4, DWARF_ID_R13},
    {"r14", 4, DWARF_ID_R14},
    {"r15", 4, DWARF_ID_R15},
    {"r16", 4, DWARF_ID_R16},
    {"r17", 4, DWARF_ID_R17},
    {"r18", 4, DWARF_ID_R18},
    {"r19", 4, DWARF_ID_R19},
    {"r20", 4, DWARF_ID_R20},
    {"r21", 4, DWARF_ID_R21},
    {"r22", 4, DWARF_ID_R22},
    {"r23", 4, DWARF_ID_R23},
    {"r24", 4, DWARF_ID_R24},
    {"r25", 4, DWARF_ID_R25},
    {"r26", 4, DWARF_ID_R26},
    {"r27", 4, DWARF_ID_R27},
    {"r28", 4, DWARF_ID_R28},
    {"r29", 4, DWARF_ID_R29},
    {"r30", 4, DWARF_ID_R30},
    {"r31", 4, DWARF_ID_R31},
    {"pc",  4, DWARF_ID_PC, VALID_IN_SYSCALL,"PC"},
    {"msr", 4, DWARF_ID_MSR},
    {"lr",  4, DWARF_ID_LR, VALID_IN_SYSCALL,"LR"},
    {"ctr", 4, DWARF_ID_CTR},
    {"cr",  4, DWARF_ID_CR},
    {"xer", 4, DWARF_ID_XER},
    {NULL},
};

#endif  /* _WRS_CONFIG_LP64 */
#endif  /* __INCcoreDumpPpcLibh */
