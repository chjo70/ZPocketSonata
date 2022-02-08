/* vxbQorIQTgtId.h - Target IDs for QorIQ */

/*
 * Copyright (c) 2008, 2011, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
25apr14,fao  merged this file from vx6.9.3.3 and corrected the modify history
08aug11,b_m  add new target IDs on P5020/P3041.
02dec08,wap  written
*/

#ifndef __INCvxbQorIQTgtIdh
#define __INCvxbQorIQTgtIdh

#ifdef __cplusplus
extern "C" {
#endif

					/* source/target */

#define QORIQ_TGTID_PCIE0	0x00	/* PCI Express1 */
#define QORIQ_TGTID_PCIE1	0x01	/* PCI Express2 */
#define QORIQ_TGTID_PCIE2	0x02	/* PCI Express3 */
#define QORIQ_TGTID_PCIE3	0x03	/* PCI Express4 */
#define QORIQ_TGTID_RIO1	0x08	/* RapidIO 1 */
#define QORIQ_TGTID_RIO2	0x09	/* RapidIO 2 */
#define QORIQ_TGTID_LOCAL	0x0F	/* rsvd / Local Space */
#define QORIQ_TGTID_DDR0	0x10	/* rsvd / DDR Memory 1 */
#define QORIQ_TGTID_DDR1	0x11	/* rsvd / DDR Memory 2 */
#define QORIQ_TGTID_IDDR	0x14	/* rsvd / Interleaved DDR Memory 1/2 */
#define	QORIQ_TGTID_BMAN	0x18	/* BufMan control / BufMan SW portal */
#define QORIQ_TGTID_PAMU	0x1C	/* rsvd/rsvd */
#define QORIQ_TGTID_DCSR	0x1D	/* rsvd/DDA access via LAW */
#define QORIQ_TGTID_CCSR	0x1E	/* rsvd/rsvd */
#define QORIQ_TGTID_ELBC	0x1F	/* enhanced local bus controller */
#define QORIQ_TGTID_PME		0x20	/* rsvd/rsvd */
#define QORIQ_TGTID_SEC40	0x21	/* Security 4.0 */
#define QORIQ_TGTID_RAID	0x28	/* RAID */
#define QORIQ_TGTID_QMAN	0x3C	/* QueueMan control / QueueMan SW portal */
#define QORIQ_TGTID_USB0	0x40	/* USB1/rsvd */
#define QORIQ_TGTID_USB1	0x41	/* USB2/rsvd */
#define QORIQ_TGTID_ESDHC	0x44	/* rsvd/rsvd */
#define QORIQ_TGTID_PBL		0x48	/* pre-boot loader */
#define QORIQ_TGTID_SAP		0x49 	/* rsvd/rsvd */
#define QORIQ_TGTID_NPC		0x4B 	/* Nexus port controller */
#define QORIQ_TGTID_RIOMU	0x4D	/* RapidIO message unit */
#define QORIQ_TGTID_RIODU	0x4E	/* RapidIO doorbell unit */
#define QORIQ_TGTID_RIOEPWU	0x4F	/* RapidIO error/portwrite unit */
#define QORIQ_TGTID_RIOMM	0x5D	/* RapidIO message manager */
#define QORIQ_TGTID_SATA1	0x60	/* SATA 1 */
#define QORIQ_TGTID_SATA2	0x61	/* SATA 2 */
#define QORIQ_TGTID_DMA1	0x70	/* DMA 1 */
#define QORIQ_TGTID_DMA2	0x71	/* DMA 2 */
#define QORIQ_TGTID_COREI0	0x80	/* Core 0 (instruction) */
#define QORIQ_TGTID_CORED0	0x81	/* Core 0 (data) */
#define QORIQ_TGTID_COREI1	0x82	/* Core 1 (instruction) */
#define QORIQ_TGTID_CORED1	0x83	/* Core 1 (data) */
#define QORIQ_TGTID_COREI2	0x84	/* Core 2 (instruction) */
#define QORIQ_TGTID_CORED2	0x85	/* Core 2 (data) */
#define QORIQ_TGTID_COREI3	0x86	/* Core 3 (instruction) */
#define QORIQ_TGTID_CORED3	0x87	/* Core 3 (data) */
#define QORIQ_TGTID_COREI4	0x88	/* Core 4 (instruction) */
#define QORIQ_TGTID_CORED4	0x89	/* Core 4 (data) */
#define QORIQ_TGTID_COREI5	0x8A	/* Core 5 (instruction) */
#define QORIQ_TGTID_CORED5	0x8B	/* Core 5 (data) */
#define QORIQ_TGTID_COREI6	0x8C	/* Core 6 (instruction) */
#define QORIQ_TGTID_CORED6	0x8D	/* Core 6 (data) */
#define QORIQ_TGTID_COREI7	0x8E	/* Core 7 (instruction) */
#define QORIQ_TGTID_CORED7	0x8F	/* Core 7 (data) */
#define QORIQ_TGTID_FM0ID00	0xC0	/* Frame manager 0 ID 0 */
#define QORIQ_TGTID_FM0ID01	0xC1	/* Frame manager 0 ID 1 */
#define QORIQ_TGTID_FM0ID02	0xC2	/* Frame manager 0 ID 2 */
#define QORIQ_TGTID_FM0ID03	0xC3	/* Frame manager 0 ID 3 */
#define QORIQ_TGTID_FM0ID04	0xC4	/* Frame manager 0 ID 4 */
#define QORIQ_TGTID_FM0ID05	0xC5	/* Frame manager 0 ID 5 */
#define QORIQ_TGTID_FM0ID06	0xC6	/* Frame manager 0 ID 6 */
#define QORIQ_TGTID_FM0ID07	0xC7	/* Frame manager 0 ID 7 */
#define QORIQ_TGTID_FM0ID08	0xC8	/* Frame manager 0 ID 8 */
#define QORIQ_TGTID_FM0ID09	0xC9	/* Frame manager 0 ID 9 */
#define QORIQ_TGTID_FM0ID10	0xCA	/* Frame manager 0 ID 10 */
#define QORIQ_TGTID_FM0ID11	0xCB	/* Frame manager 0 ID 11 */
#define QORIQ_TGTID_FM0ID12	0xCC	/* Frame manager 0 ID 12 */
#define QORIQ_TGTID_FM0ID13	0xCD	/* Frame manager 0 ID 13 */
#define QORIQ_TGTID_FM0ID14	0xCE	/* Frame manager 0 ID 14 */
#define QORIQ_TGTID_FM0ID15	0xCF	/* Frame manager 0 ID 15 */
#define QORIQ_TGTID_FM1ID00	0xD0	/* Frame manager 1 ID 0 */
#define QORIQ_TGTID_FM1ID01	0xD1	/* Frame manager 1 ID 1 */
#define QORIQ_TGTID_FM1ID02	0xD2	/* Frame manager 1 ID 2 */
#define QORIQ_TGTID_FM1ID03	0xD3	/* Frame manager 1 ID 3 */
#define QORIQ_TGTID_FM1ID04	0xD4	/* Frame manager 1 ID 4 */
#define QORIQ_TGTID_FM1ID05	0xD5	/* Frame manager 1 ID 5 */
#define QORIQ_TGTID_FM1ID06	0xD6	/* Frame manager 1 ID 6 */
#define QORIQ_TGTID_FM1ID07	0xD7	/* Frame manager 1 ID 7 */
#define QORIQ_TGTID_FM1ID08	0xD8	/* Frame manager 1 ID 8 */
#define QORIQ_TGTID_FM1ID09	0xD9	/* Frame manager 1 ID 9 */
#define QORIQ_TGTID_FM1ID10	0xDA	/* Frame manager 1 ID 10 */
#define QORIQ_TGTID_FM1ID11	0xDB	/* Frame manager 1 ID 11 */
#define QORIQ_TGTID_FM1ID12	0xDC	/* Frame manager 1 ID 12 */
#define QORIQ_TGTID_FM1ID13	0xDD	/* Frame manager 1 ID 13 */
#define QORIQ_TGTID_FM1ID14	0xDE	/* Frame manager 1 ID 14 */
#define QORIQ_TGTID_FM1ID15	0xDF	/* Frame manager 1 ID 15 */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbQorIQTgtIdh */

