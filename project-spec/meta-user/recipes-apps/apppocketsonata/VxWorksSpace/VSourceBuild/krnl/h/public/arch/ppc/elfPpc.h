/* elfPpc.h - PowerPC specific elf loader header */

/* 
 * Copyright (c) 1994-2005,2009, 2014-2015 Wind River Systems, Inc. 
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement. 
 */

/*
modification history
--------------------
27mar15,vhe  Additional relocation types for ELFv2 (F1122)
03feb15,vhe  Added _WRS_LOADER_USES_TOC (US50408) 
05jan15,vhe  Added PowerPC64 relocation (US50408)
16dec14,my_  added EM_ARCH_MACHINE_3 definition (US: F2518)
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
#define _WRS_LOADER_USES_TOC
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


/* 
 * The relocation types whose Field column entry contains an asterisk (*) 
 * are subject to failure if the value computed does not fit in the 
 * allocated bits.
 */

/*      Name                   Value        Field         Calculation */ 
#define R_PPC64_NONE               0   /*   none          none */
#define R_PPC64_ADDR32             1   /*   word32*       S + A */
#define R_PPC64_ADDR24             2   /*   low24*        (S + A) >> 2 */
#define R_PPC64_ADDR16             3   /*   half16*       S + A */
#define R_PPC64_ADDR16_LO          4   /*   half16        #lo(S + A) */
#define R_PPC64_ADDR16_HI          5   /*   half16*       #hi(S + A) */
#define R_PPC64_ADDR16_HA          6   /*   half16*       #ha(S + A) */
#define R_PPC64_ADDR14             7   /*   low14*        (S + A) >> 2 */
                                       /* value 8-9 not used */ 
#define R_PPC64_REL24              10  /*   low24*        (S + A - P) >> 2 */
#define R_PPC64_REL14              11  /*   low14*        (S + A - P) >> 2 */
                                       /* value 12-13 not used */ 
#define R_PPC64_GOT16              14  /*   half16*       G */
#define R_PPC64_GOT16_LO           15  /*   half16        #lo(G) */
#define R_PPC64_GOT16_HI           16  /*   half16        #hi(G) */
#define R_PPC64_GOT16_HA           17  /*   half16        #ha(G) */
                                       /* value 18 not used */ 
#define R_PPC64_COPY               19  /*   none          none */
#define R_PPC64_GLOB_DAT           20  /*   doubleword64  S + A */
#define R_PPC64_JMP_SLOT           21  /*   none          special semantics */
#define R_PPC64_RELATIVE           22  /*   doubleword64  B + A */
                                       /* value 23 not used */ 
#define R_PPC64_UADDR32            24  /*   word32*       S + A */
#define R_PPC64_UADDR16            25  /*   half16*       S + A */
#define R_PPC64_REL32              26  /*   word32*       S + A - P */
#define R_PPC64_PLT32              27  /*   word32*       L */
#define R_PPC64_PLTREL32           28  /*   word32*       L - P */
#define R_PPC64_PLT16_LO           29  /*   half16        #lo(L) */
#define R_PPC64_PLT16_HI           30  /*   half16        #hi(L) */
#define R_PPC64_PLT16_HA           31  /*   half16        #ha(L) */
                                       /* value 32 not used */ 
#define R_PPC64_SECTOFF            33  /*   half16*       R + A */
#define R_PPC64_SECTOFF_LO         34  /*   half16        #lo(R + A) */
#define R_PPC64_SECTOFF_HI         35  /*   half16        #hi(R + A) */
#define R_PPC64_SECTOFF_HA         36  /*   half16        #ha(R + A) */
#define R_PPC64_ADDR30             37  /*   word30        (S + A - P) >> 2 */
#define R_PPC64_ADDR64             38  /*   doubleword64  S + A */
#define R_PPC64_ADDR16_HIGHER      39  /*   half16        #higher(S + A) */
#define R_PPC64_ADDR16_HIGHERA     40  /*   half16        #highera(S + A) */
#define R_PPC64_ADDR16_HIGHEST     41  /*   half16        #highest(S + A) */
#define R_PPC64_ADDR16_HIGHESTA    42  /*   half16        #highesta(S + A) */
#define R_PPC64_UADDR64            43  /*   doubleword64  S + A */
#define R_PPC64_REL64              44  /*   doubleword64  S + A - P */
#define R_PPC64_PLT64              45  /*   doubleword64  L */
#define R_PPC64_PLTREL64           46  /*   doubleword64  L - P */
#define R_PPC64_TOC16              47  /*   half16*       S + A - .TOC. */
#define R_PPC64_TOC16_LO           48  /*   half16        #lo(S + A - .TOC.) */
#define R_PPC64_TOC16_HI           49  /*   half16        #hi(S + A - .TOC.) */
#define R_PPC64_TOC16_HA           50  /*   half16        #ha(S + A - .TOC.) */
#define R_PPC64_TOC                51  /*   doubleword64  .TOC. */
#define R_PPC64_PLTGOT16           52  /*   half16*       M */
#define R_PPC64_PLTGOT16_LO        53  /*   half16        #lo(M) */
#define R_PPC64_PLTGOT16_HI        54  /*   half16        #hi(M) */
#define R_PPC64_PLTGOT16_HA        55  /*   half16        #ha(M) */
#define R_PPC64_ADDR16_DS          56  /*   half16ds*     (S + A) >> 2 */
#define R_PPC64_ADDR16_LO_DS       57  /*   half16ds      #lo(S + A) >> 2 */
#define R_PPC64_GOT16_DS           58  /*   half16ds*     G >> 2 */
#define R_PPC64_GOT16_LO_DS        59  /*   half16ds      #lo(G) >> 2 */
#define R_PPC64_PLT16_LO_DS        60  /*   half16ds      #lo(L) >> 2 */
#define R_PPC64_SECTOFF_DS         61  /*   half16ds*     (R + A) >> 2 */
#define R_PPC64_SECTOFF_LO_DS      62  /*   half16ds      #lo(R + A) >> 2 */
#define R_PPC64_TOC16_DS           63  /*   half16ds*     (S + A - .TOC.) >> 2 */
#define R_PPC64_TOC16_LO_DS        64  /*   half16ds      #lo(S + A - .TOC.) >> 2 */
#define R_PPC64_PLTGOT16_DS        65  /*   half16ds*     M >> 2 */
#define R_PPC64_PLTGOT16_LO_DS     66  /*   half16ds      #lo(M) >> 2 */
#define R_PPC64_TLS                67  /*   none          none */
#define R_PPC64_DTPMOD64           68  /*   doubleword64  @dtpmod */
#define R_PPC64_TPREL16            69  /*   half16*       @tprel */
#define R_PPC64_TPREL16_LO         70  /*   half16        #lo(@tprel) */
#define R_PPC64_TPREL16_HI         71  /*   half16        #hi(@tprel) */
#define R_PPC64_TPREL16_HA         72  /*   half16        #ha(@tprel) */
#define R_PPC64_TPREL64            73  /*   doubleword64  @tprel */
#define R_PPC64_DTPREL16           74  /*   half16*       @dtprel */
#define R_PPC64_DTPREL16_LO        75  /*   half16        #lo(@dtprel) */
#define R_PPC64_DTPREL16_HI        76  /*   half16        #hi(@dtprel) */
#define R_PPC64_DTPREL16_HA        77  /*   half16        #ha(@dtprel) */
#define R_PPC64_DTPREL64           78  /*   doubleword64  @dtprel */
#define R_PPC64_GOT_TLSGD16        79  /*   half16*       @got@tlsgd */
#define R_PPC64_GOT_TLSGD16_LO     80  /*   half16        #lo(@got@tlsgd) */
#define R_PPC64_GOT_TLSGD16_HI     81  /*   half16        #hi(@got@tlsgd) */
#define R_PPC64_GOT_TLSGD16_HA     82  /*   half16        #ha(@got@tlsgd) */
#define R_PPC64_GOT_TLSLD16        83  /*   half16*       @got@tlsld */
#define R_PPC64_GOT_TLSLD16_LO     84  /*   half16        #lo(@got@tlsld) */
#define R_PPC64_GOT_TLSLD16_HI     85  /*   half16        #hi(@got@tlsld) */
#define R_PPC64_GOT_TLSLD16_HA     86  /*   half16        #ha(@got@tlsld) */
#define R_PPC64_GOT_TPREL16_DS     87  /*   half16ds*     @got@tprel */
#define R_PPC64_GOT_TPREL16_LO_DS  88  /*   half16ds      #lo(@got@tprel) */
#define R_PPC64_GOT_TPREL16_HI     89  /*   half16        #hi(@got@tprel) */
#define R_PPC64_GOT_TPREL16_HA     90  /*   half16        #ha(@got@tprel) */
#define R_PPC64_GOT_DTPREL16_DS    91  /*   half16ds*     @got@dtprel */
#define R_PPC64_GOT_DTPREL16_LO_DS 92  /*   half16ds      #lo(@got@dtprel) */
#define R_PPC64_GOT_DTPREL16_HI    93  /*   half16        #hi(@got@dtprel) */
#define R_PPC64_GOT_DTPREL16_HA    94  /*   half16        #ha(@got@dtprel) */
#define R_PPC64_TPREL16_DS         95  /*   half16ds*     @tprel */
#define R_PPC64_TPREL16_LO_DS      96  /*   half16ds      #lo(@tprel) */
#define R_PPC64_TPREL16_HIGHER     97  /*   half16        #higher(@tprel) */
#define R_PPC64_TPREL16_HIGHERA    98  /*   half16        #highera(@tprel) */
#define R_PPC64_TPREL16_HIGHEST    99  /*   half16        #highest(@tprel) */
#define R_PPC64_TPREL16_HIGHESTA   100 /*   half16        #highesta(@tprel) */
#define R_PPC64_DTPREL16_DS        101 /*   half16ds*     @dtprel */
#define R_PPC64_DTPREL16_LO_DS     102 /*   half16ds      #lo(@dtprel) */
#define R_PPC64_DTPREL16_HIGHER    103 /*   half16        #higher(@dtprel) */
#define R_PPC64_DTPREL16_HIGHERA   104 /*   half16        #highera(@dtprel) */
#define R_PPC64_DTPREL16_HIGHEST   105 /*   half16        #highest(@dtprel) */
#define R_PPC64_DTPREL16_HIGHESTA  106 /*   half16        #highesta(@dtprel) */
/* ELFv2 definitions */ 
#define R_PPC64_TLSGD              107 /*   none          none */
#define R_PPC64_TLSLD              108 /*   none          none */
#define R_PPC64_TOCSAVE            109 /*   none          none */
#define R_PPC64_ADDR16_HIGH        110 /*   half16        #high(S + A) */
#define R_PPC64_ADDR16_HIGHA       111 /*   half16        #higha(S + A) */
#define R_PPC64_TPREL16_HIGH       112 /*   half16        #high(@tprel) */
#define R_PPC64_TPREL16_HIGHA      113 /*   half16        #higha(@tprel) */
#define R_PPC64_DTPREL16_HIGH      114 /*   half16        #high(@dtprel) */
#define R_PPC64_DTPREL16_HIGHA     115 /*   half16        #higha(@dtprel) */
#define R_PPC64_REL24_NOTOC        116 /*   low24*        (S + A - P) >> 2 */
#define R_PPC64_ADDR64_LOCAL       117 /*   doubleword64  S + A (note)  */
#define R_PPC64_IRELATIVE          248 /*   doubleword64  (note) */
#define R_PPC64_REL16              249 /*   half16*       S + A - P */
#define R_PPC64_REL16_LO           250 /*   half16        #lo(S + A - P) */
#define R_PPC64_REL16_HI           251 /*   half16*       #hi(S + A - P) */
#define R_PPC64_REL16_HA           252 /*   half16*       #ha(S + A - P) */
#define R_PPC64_GNU_VTINHERIT      253 /*   */ 
#define R_PPC64_GNU_VTENTRY        254 /*   */

/* 
 * Offset used for calculation of the TOC base.
 * The TOC base is typically the first address in the TOC plus 0x8000 
 */

#define TOC_OFFSET          0x8000
                 
#ifdef __cplusplus
}
#endif

#endif /* __INCelfPpcLibh */
