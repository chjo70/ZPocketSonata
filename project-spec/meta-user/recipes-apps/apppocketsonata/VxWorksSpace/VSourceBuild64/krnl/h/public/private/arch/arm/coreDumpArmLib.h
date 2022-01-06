/* coreDumpArmLib.h - ARM core dump header file */

/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17oct16,sdt  Added ARMARCH8 support
18jan16,jmp  Fixed cpsr DwarfID (V7COR-3933).
09feb15,elp  Added cpsr alias for ARMARCH7M.
16jan15,jmp  Added architecture string and ISA information.
16jan15,afi  added reg defs.
19dec14,jmp  written.
*/

#ifndef __INCcoreDumpArmLibh
#define __INCcoreDumpArmLibh

/* define architecture type */
#define CORE_DUMP_ARCH  "arm"

/* Define ISA parameters for architecture */
#define CORE_DUMP_ISA_DEF "ARM"
#define CORE_DUMP_ISA_MAX_INST_SIZE (sizeof(INSTR) * 4)


#if CPU == ARMARCH8A

#define cpsr    pstate

/* Dwarf IDs */
#define DWARF_ID_R0    0
#define DWARF_ID_R1    1
#define DWARF_ID_R2    2
#define DWARF_ID_R3    3
#define DWARF_ID_R4    4
#define DWARF_ID_R5    5
#define DWARF_ID_R6    6
#define DWARF_ID_R7    7
#define DWARF_ID_R8    8
#define DWARF_ID_R9    9
#define DWARF_ID_R10  10
#define DWARF_ID_R11  11
#define DWARF_ID_R12  12
#define DWARF_ID_R13  13
#define DWARF_ID_R14  14
#define DWARF_ID_R15  15
#define DWARF_ID_R16  16
#define DWARF_ID_R17  17
#define DWARF_ID_R18  18
#define DWARF_ID_R19  19
#define DWARF_ID_R20  20
#define DWARF_ID_R21  21
#define DWARF_ID_R22  22
#define DWARF_ID_R23  23
#define DWARF_ID_R24  24
#define DWARF_ID_R25  25
#define DWARF_ID_R26  26
#define DWARF_ID_R27  27
#define DWARF_ID_R28  28
#define DWARF_ID_FP   29
#define DWARF_ID_LR   30
#define DWARF_ID_SP   31
#define DWARF_ID_PC   33
#define DWARF_ID_PSTATE 128

/* name, size, dwarf_id, role */

static CORE_DUMP_REGISTERS_DEF coreDumpRegistersDef[] = {
    {"r0",   8, DWARF_ID_R0},
    {"r1",   8, DWARF_ID_R1},
    {"r2",   8, DWARF_ID_R2},
    {"r3",   8, DWARF_ID_R3},
    {"r4",   8, DWARF_ID_R4},
    {"r5",   8, DWARF_ID_R5},
    {"r6",   8, DWARF_ID_R6},
    {"r7",   8, DWARF_ID_R7},
    {"r8",   8, DWARF_ID_R8},
    {"r9",   8, DWARF_ID_R9},
    {"r10",  8, DWARF_ID_R10},
    {"r11",  8, DWARF_ID_R11},
    {"r12",  8, DWARF_ID_R12},
    {"r13",  8, DWARF_ID_R13},
    {"r14",  8, DWARF_ID_R14},
    {"r15",  8, DWARF_ID_R15},
    {"r16",  8, DWARF_ID_R16},
    {"r17",  8, DWARF_ID_R17},
    {"r18",  8, DWARF_ID_R18},
    {"r19",  8, DWARF_ID_R19},
    {"r20",  8, DWARF_ID_R20},
    {"r21",  8, DWARF_ID_R21},
    {"r22",  8, DWARF_ID_R22},
    {"r23",  8, DWARF_ID_R23},
    {"r24",  8, DWARF_ID_R24},
    {"r25",  8, DWARF_ID_R25},
    {"r26",  8, DWARF_ID_R26},
    {"r27",  8, DWARF_ID_R27},
    {"r28",  8, DWARF_ID_R28},
    {"r29",  8, DWARF_ID_FP, VALID_IN_SYSCALL,"FP"},
    {"r30",  8, DWARF_ID_LR, VALID_IN_SYSCALL,"LR"},
    {"r31",  8, DWARF_ID_SP, VALID_IN_SYSCALL,"SP"},
    {"r33",  8, DWARF_ID_PC, VALID_IN_SYSCALL,"PC"},
    {"pstate", 8, DWARF_ID_PSTATE, VALID_IN_SYSCALL,"CPSR"},
    {NULL},
};

#else

#if CPU==ARMARCH7M
#define cpsr    psr
#endif

/* Dwarf IDs */
#define DWARF_ID_R0    0
#define DWARF_ID_R1    1
#define DWARF_ID_R2    2
#define DWARF_ID_R3    3
#define DWARF_ID_R4    4
#define DWARF_ID_R5    5
#define DWARF_ID_R6    6
#define DWARF_ID_R7    7
#define DWARF_ID_R8    8
#define DWARF_ID_R9    9
#define DWARF_ID_R10  10
#define DWARF_ID_FP   11
#define DWARF_ID_R12  12
#define DWARF_ID_SP   13
#define DWARF_ID_LR   14
#define DWARF_ID_PC   15
#define DWARF_ID_CPSR 128

/* name, size, dwarf_id, role */

static CORE_DUMP_REGISTERS_DEF coreDumpRegistersDef[] = {
    {"r0",   4, DWARF_ID_R0},
    {"r1",   4, DWARF_ID_R1},
    {"r2",   4, DWARF_ID_R2},
    {"r3",   4, DWARF_ID_R3},
    {"r4",   4, DWARF_ID_R4},
    {"r5",   4, DWARF_ID_R5},
    {"r6",   4, DWARF_ID_R6},
    {"r7",   4, DWARF_ID_R7},
    {"r8",   4, DWARF_ID_R8},
    {"r9",   4, DWARF_ID_R9},
    {"r10",  4, DWARF_ID_R10},
    {"r11",  4, DWARF_ID_FP, VALID_IN_SYSCALL,"FP"},
    {"r12",  4, DWARF_ID_R12},
    {"r13",  4, DWARF_ID_SP, VALID_IN_SYSCALL,"SP"},
    {"r14",  4, DWARF_ID_LR, VALID_IN_SYSCALL,"LR"},
    {"r15",  4, DWARF_ID_PC, VALID_IN_SYSCALL,"PC"},
    {"cpsr", 4, DWARF_ID_CPSR, VALID_IN_SYSCALL,"CPSR"},
    {NULL},
};

#endif /* CPU == ARMARCH8A */

#endif  /* __INCcoreDumpArmLibh */
