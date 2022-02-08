/* elfPpc.h - PowerPC specific elf loader header */

/* 
 * Copyright (c) 1994-2005,2009, 2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement. 
 */

/*
modification history
--------------------
16dec14,my_  added EM_ARCH_MACHINE3 definition (US: F2518)
14dec09,pgh  Add EM_ARCH_MACHINE_x macro definition.
25jul05,v_r  Updated copyright.
18sep04,jn   Move towards shared code between host and target loaders
12jul04,jn   Source sanitization
12apr04,jn   Cleaning up header files after merge of AE loader work into
             Base 6
08mar04,pad  Renamed the relocation type R_PPC_PLT24 into R_PPC_PLTREL24
	 to match the ABI.
27feb04,pad  Renamed relocation type R_PPC_SDAREL into R_PPC_SDAREL16 to
	 match ABI.
31mar95,yao  added greenhill bug related definitions.
24mar95,yao  updated relocation type to EABI version 1.0. rename the
	 definitions conflicted with 1.0 in draft1.1 from
	 R_PPC_XXX to R_PPC_XXX_OLD.
06dec94,yao  created.
*/

#ifndef __INCelfPpch
#define __INCelfPpch

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * The following macros define the ELF machine type values that can be loaded
 * into a PowerPC CPU.
 */

#define EM_ARCH_MACHINE_1   EM_PPC
#define EM_ARCH_MACHINE_2   EM_PPC_OLD
#define EM_ARCH_MACHINE_3   EM_PPC64

#ifdef _WRS_CONFIG_LP64
#define EM_ARCH_MACHINE     EM_PPC64
#else
#define EM_ARCH_MACHINE		EM_PPC
#define EM_ARCH_MACH_ALT	EM_PPC_OLD
#endif

/* The following defines which if the compiler conforms with EABI
 * release.  LD_NO_BUGS - use the EABI standard, LD_OLD_VER_BUG - use
 * the old EABI draft 1.1, and the incorrect relocation information
 * is generated with the old machine magic value EM_PPC_OLD(17), 
 * the correct relocation information is genreated with the updated
 * machine magic number EM_PPC(20). LD_ALWAYS_BUG - the compiler always
 * generate the incorrect relocation information.  This should be
 * removed finally when the compiler venders do the job correctly.
 */

#define LD_NO_BUGS	0
#define LD_OLD_VER_BUG	1
#define	LD_ALWAYS_BUG	2

/* relocation type definition */

#define	R_PPC_NONE		0
#define	R_PPC_ADDR32		1
#define R_PPC_ADDR24		2
#define R_PPC_ADDR16		3
#define R_PPC_ADDR16_LO		4
#define R_PPC_ADDR16_HI		5
#define R_PPC_ADDR16_HA		6
#define R_PPC_ADDR14		7
#define R_PPC_ADDR14_BRTAKEN	8
#define R_PPC_ADDR14_BRNTAKEN	9
#define R_PPC_REL24		10
#define R_PPC_REL14		11
#define R_PPC_REL14_BRTAKEN	12
#define R_PPC_REL14_BRNTAKEN	13
#define R_PPC_GOT16		14
#define R_PPC_GOT16_LO		15
#define R_PPC_GOT16_HI		16
#define R_PPC_GOT16_HA		17
#define R_PPC_PLTREL24		18
#define R_PPC_COPY		19
#define R_PPC_JMP_SLOT		21
#define R_PPC_RELATIVE		22
#define R_PPC_LOCAL24PC		23
#define R_PPC_UADDR32		24
#define R_PPC_UADDR16		25
#define R_PPC_REL32		26
#define R_PPC_PLT32		27
#define R_PPC_PLTREL32		28
#define R_PPC_PLT16_LO		29
#define R_PPC_PLT16_HI		30
#define R_PPC_PLT16_HA		31
#define R_PPC_SDAREL16		32

/* EABI relocation types */

#define R_PPC_EMB_NADDR32	101
#define R_PPC_EMB_NADDR16	102
#define R_PPC_EMB_NADDR16_LO	103
#define R_PPC_EMB_NADDR16_HI	104
#define R_PPC_EMB_NADDR16_HA	105
#define R_PPC_EMB_SDAI16	106
#define R_PPC_EMB_SDA2I16	107
#define R_PPC_EMB_SDA2REL	108
#define R_PPC_EMB_SDA21		109
#define R_PPC_EMB_MRKREF	110
#define R_PPC_EMB_RELSEC16	111
#define R_PPC_EMB_RELST_LO	112
#define R_PPC_EMB_RELST_HI	113
#define R_PPC_EMB_RELST_HA	114
#define R_PPC_EMB_BIT_FLD	115
#define R_PPC_EMB_RELSDA	116

#ifdef __cplusplus
}
#endif

#endif /* __INCelfPpcLibh */
