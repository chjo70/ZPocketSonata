/* vxbQorIQFman.h - Freescale QorIQ frame manager hardware definitions */

/*
 * Copyright (c) 2009-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
28dec17,lyx  supported new version of dpaa for t1024(F4843)
05may17,wch  added support for ARM (F8333)
29jun15,xms  fixed compiler warning. (F2518)
21nov14,wap  Merge in multi-instance/multi-queue support
29aug13,dlk  Frame queue ID usage conventions supporting per-CPU queues
             for each ethernet port.
19aug14,fao  fixed static analysis issues and compiler warnings. (V7PRO-1187)
06aug14,fao  add V3L support.(US40505)
12mar14,fao  corrected the modify history
25jan13,wap  Update copyright
17jan13,wap  Increase FIFO sizes for 10GbE interfaces for Fman_v3
26oct12,wyt  Add definitions of revision registers
11oct12,wap  Allow each Fman to have a different Fman clock
09oct12,wap  Add new Fman_v3 registers
10aug12,wap  Update for T4240
26oct12,wyt  Add definitions of revision registers
18aug11,wap  Add support for 5th DTSEC port available on P3041/P5020 DPAA
12apr11,tlu  Add APIs to get/set S-TPID for a port
16dec10,wap  Correct some coarse classifier codes (WIND00239875)
10jun10,wap  Add API to get/set buffer pool IDs for a port
11may10,wap  Add routines to manage the keygen port partition configuration
29apr10,wap  Correct offset of FMKG_SE_MV register
26mar10,wap  Increase TX FIFO size for 10GbE/TGEC ports to fix jumbo frame
             support
12mar10,wap  Allow initialization of parse results
11feb10,wap  Add soft parser support
28jan10,wap  Clean up policer and timestamp configuration
19jan10,wap  Add some additional coarse classification parser codes
19nov09,wap  Add more policer register/structure definitions
27oct09,wap  Adjust FIFO sizes so that jumbo frames to work with DTSEC
             ports
16oct09,wap  Allow default action descriptors in classifier configurations
             to also chain to additional nested lookups
13oct09,wap  Add keygen and classifier register definitions and structures
17sep09,wap  Add structure definitions for Fman microcode (not used yet,
             but may be needed in the future), correct FMFP_EE register
             definition, add some additional register definitions
16jul09,wap  written
*/

#ifndef __INCvxbQorIQFmanh
#define __INCvxbQorIQFmanh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Frame manager memory map.
 *
 * There are two frame managers at CCSR base addresses 0x400000, and 0x500000.
 * The layout of each frame manager's memory map is as follows:
 *
 * Range              Size      Description
 * -----              ----      -----------
 * 0x00000-0x7FFFF    512KB     Direct frame manager memory access (MURAM)
 *                              (Note: only 160KB currently implemented)
 *
 * 0x80000-0xBFFFF    256KB     BMI, QMI and Parser registers
 *                              Space is divided into 4K pages based
 *                              on port ID, 0x00 through 0x3F.
 *                              Each page is subdivided as follows:
 *                              0x000-0x3FF BMI
 *                              0x400-0x7FF QMI
 *                              0x800-0xBFF Parser
 *
 * 0xC0000-0xC0FFF    4KB       Policer
 *
 * 0xC1000-0xC1FFF    4KB       Key generator
 *
 * 0xC2000-0xC2FFF    4KB       Fman DMA
 *
 * 0xC3000-0xC3FFF    4KB       Frame processing manager (FPM)
 *
 * 0xC4000-0xC6FFF    12KB      Instruction RAM/microcode loading
 *
 * 0xC7000-0xC77FF    2KB       Direct parser memory access
 *
 * 0xC7800-0xC7FFF    2KB       Parser global configuration registers
 *
 * 0xC8000-0xDFFFF    96KB      Reserved
 *
 * 0xE0000-0xE0FFF    4KB       dTSEC1
 *
 * 0xE1000-0xE1FFF    4KB       MDIO for dTSEC1
 *
 * 0xE2000-0xE2FFF    4KB       dTSEC2
 *
 * 0xE3000-0xE2FFF    4KB       MDIO for dTSEC2
 *
 * 0xE4000-0xE4FFF    4KB       dTSEC3
 *
 * 0xE5000-0xE5FFF    4KB       MDIO for dTSEC3
 *
 * 0xE6000-0xE6FFF    4KB       dTSEC4
 *
 * 0xE7000-0xE7FFF    4KB       MDIO for dTSEC4
 *
 * 0xE8000-0xE8FFF    4KB       dTSEC5    (P3041/P5020)
 *
 * 0xE9000-0xE9FFF    4KB       MDIO for dTSEC5
 *
 * 0xEA000-0xEAFFF    4KB       dTSEC6    (future expansion)
 *
 * 0xEB000-0xEBFFF    4KB       MDIO for dTSEC6
 *
 * 0xEC000-0xECFFF    4KB       dTSEC7    (future expansion)
 *
 * 0xED000-0xEDFFF    4KB       MDIO for dTSEC7
 *
 * 0xEE000-0xEEFFF    4KB       dTSEC8    (future expansion)
 *
 * 0xEF000-0xEFFFF    4KB       MDIO for dTSEC8
 *
 * 0xF0000-0xF0FFF    4KB       10GbE MAC
 *
 * 0xF1000-0xF1FFF    4KB       MDIO for 10GbE MAC
 *
 * 0xF2000-0xF2FFF    4KB       10GbE MAC (T4240)
 *
 * 0xF3000-0xF3FFF    4KB       MDIO for 10GbE MAC
 *
 * 0xF4000-0xFBFFF    32KB      Reserved
 *
 * 0xFC000-0xFCFFF    4KB       Fman_V3 dedicated MDIO0
 * 
 * 0xFD000-0xFDFFF    4KB       Fman_V3 dedicated MDIO1
 *
 * 0xFE000-0xFEFFF    4KB       IEEE 1588 registers
 *
 * 0xFF000-0xFFFFF    4KB       Reserved
 */

#define FMAN_PORTS                  64

#define FMAN_PN_BASE                0x80000
#define FMAN_BM_BASE                0x00000
#define FMAN_QM_BASE                0x00400
#define FMAN_PR_BASE                0x00800
#define FMAN_PL_BASE                0xC0000
#define FMAN_KG_BASE                0xC1000
#define FMAN_DM_BASE                0xC2000
#define FMAN_FP_BASE                0xC3000
#define FMAN_IR_BASE                0xC4000
#define FMAN_PRD_BASE               0xC7000
#define FMAN_PRG_BASE               0xC7800

/*
 * These are the assigned port ID values for use with the
 * BMI/QMI setup registers. Among other things, these are
 * used to connect a given port ID to a frame queue in
 * the queue manager.
 *
 * Note: the DPAA design potentially allows for up to 8
 * DTSEC ports in a single Frame Manager instance, however
 * the actual number of DTSECs available varies depending
 * on the specific device. The P4080 supports only 4 DTSECs,
 * but the P3041 and P5020 have 5. We include definitions
 * for all 8 DTSEC RX and TX port IDs, for future expansion.
 */

#define FMAN_PORTID_OFFLINE1        0x01
#define FMAN_PORTID_OFFLINE2        0x02
#define FMAN_PORTID_OFFLINE3        0x03
#define FMAN_PORTID_OFFLINE4        0x04
#define FMAN_PORTID_OFFLINE5        0x05
#define FMAN_PORTID_OFFLINE6        0x06
#define FMAN_PORTID_OFFLINE7        0x07
#define FMAN_PORTID_DTSEC_RX0       0x08
#define FMAN_PORTID_DTSEC_RX1       0x09
#define FMAN_PORTID_DTSEC_RX2       0x0A
#define FMAN_PORTID_DTSEC_RX3       0x0B
#define FMAN_PORTID_DTSEC_RX4       0x0C
#define FMAN_PORTID_DTSEC_RX5       0x0D
#define FMAN_PORTID_DTSEC_RX6       0x0E
#define FMAN_PORTID_DTSEC_RX7       0x0F
#define FMAN_PORTID_10GBE_RX        0x10
#define FMAN_PORTID_10GBE_RX0       FMAN_PORTID_10GBE_RX
#define FMAN_PORTID_10GBE_RX1       0x11
#define FMAN_PORTID_DTSEC_TX0       0x28
#define FMAN_PORTID_DTSEC_TX1       0x29
#define FMAN_PORTID_DTSEC_TX2       0x2A
#define FMAN_PORTID_DTSEC_TX3       0x2B
#define FMAN_PORTID_DTSEC_TX4       0x2C
#define FMAN_PORTID_DTSEC_TX5       0x2D
#define FMAN_PORTID_DTSEC_TX6       0x2E
#define FMAN_PORTID_DTSEC_TX7       0x2F
#define FMAN_PORTID_10GBE_TX        0x30
#define FMAN_PORTID_10GBE_TX0       FMAN_PORTID_10GBE_TX
#define FMAN_PORTID_10GBE_TX1       0x31

/* Fman V3 (T4240) port definitions */

#define FMAN_PORTID_MEMAC_RX0       0x08
#define FMAN_PORTID_MEMAC_RX1       0x09
#define FMAN_PORTID_MEMAC_RX2       0x0A
#define FMAN_PORTID_MEMAC_RX3       0x0B
#define FMAN_PORTID_MEMAC_RX4       0x0C
#define FMAN_PORTID_MEMAC_RX5       0x0D
#define FMAN_PORTID_MEMAC_RX6       0x0E
#define FMAN_PORTID_MEMAC_RX7       0x0F
#define FMAN_PORTID_MEMAC_RX8       0x10
#define FMAN_PORTID_MEMAC_RX9       0x11

#define FMAN_PORTID_MEMAC_TX0       0x28
#define FMAN_PORTID_MEMAC_TX1       0x29
#define FMAN_PORTID_MEMAC_TX2       0x2A
#define FMAN_PORTID_MEMAC_TX3       0x2B
#define FMAN_PORTID_MEMAC_TX4       0x2C
#define FMAN_PORTID_MEMAC_TX5       0x2D
#define FMAN_PORTID_MEMAC_TX6       0x2E
#define FMAN_PORTID_MEMAC_TX7       0x2F
#define FMAN_PORTID_MEMAC_TX8       0x30
#define FMAN_PORTID_MEMAC_TX9       0x31

/*
 * Different DPAA implementations have different amounts
 * of internal memory. The known cases are:
 *
 * P4080, P2040/P2041, P2031, P5020:160KB
 * P1023:                           64KB
 * Fman V3H (T4240):                384KB
 * Fman V3L:                        192KB
 */

/*
 * Values for Fman V3H fman
 * On T4240, there are 6 available 1GBps ports and two
 * 10Gbps ports.
 */

#define FMAN_V3H_USED_PORTS         (7 + 6 + 6 + 2 + 2)
#define FMAN_V3H_TOTAL_SIZE         0x60000
#define FMAN_V3H_MURAM_SIZE         0x30000
#define FMAN_V3H_FBP_SIZE           0x30000

#define FMAN_V3H_RX_FIFO_SIZE_1G    0x2B00 /* x 6 == 0x10200 */
#define FMAN_V3H_RX_FIFO_SIZE_10G   0x2B00 /* x 2 == 0x15800 */
#define FMAN_V3H_OFL_FIFO_SIZE      0x0B00 /* x 7 == 0x1A500 */
#define FMAN_V3H_TX_FIFO_SIZE_1G    0x2B00 /* x 6 == 0x2A700 */
#define FMAN_V3H_TX_FIFO_SIZE_10G   0x2C00 /* x 2 == 0x2FF00 */

#define FMAN_V3H_RX_EXFIFO_SIZE_1G  0x0980
#define FMAN_V3H_RX_EXFIFO_SIZE_10G 0x0980

#define FMAN_V3L_TOTAL_SIZE         0x30000
#define FMAN_V3L_MURAM_SIZE         0x10000
#define FMAN_V3L_FBP_SIZE           0x20000
                
#define FMAN_V3L_RX_FIFO_SIZE_1G    0x2B00 /* x 6 == 0x10200 */
#define FMAN_V3L_RX_FIFO_SIZE_10G   0x2B00 /* x 2 == 0x15800 */
#define FMAN_V3L_OFL_FIFO_SIZE      0x0B00 /* x 7 == 0x1A500 */
#define FMAN_V3L_TX_FIFO_SIZE_1G    0x2B00 /* x 6 == 0x2A700 */
#define FMAN_V3L_TX_FIFO_SIZE_10G   0x2C00 /* x 2 == 0x2FF00 */
                
#define FMAN_V3L_RX_EXFIFO_SIZE_1G  0x0980
#define FMAN_V3L_RX_EXFIFO_SIZE_10G 0x0980

#define FMAN_MAX_ETH_1GBIT          8
#define FMAN_MAX_ETH_10GBIT         2
#define FMAN_MAX_ETH_DEVS           (FMAN_MAX_ETH_1GBIT + FMAN_MAX_ETH_10GBIT)

#define FMAN_FQID_BASE              0x100  /* must be multiple of 32 */

/* Total amount of Fman memory (160KB) */

#define FMAN_TOTAL_SIZE             0x28000

/* Values for original P4080 Fman. */

/* Amount of BMI free pool memory (128KB) */

#define FMAN_P4080_FBP_SIZE         0x20000

/* Amount of Fman memory to be used as MURAM (32KB) */

#define FMAN_P4080_MURAM_SIZE       0x8000

/* Amount of BMI free pool memory (32KB) */

#define FMAN_P1023_FBP_SIZE         0x8000

/* Amount of Fman memory to be used as MURAM (32KB) */

#define FMAN_P1023_MURAM_SIZE       0x8000


/* Amount of BMI free pool memory (32KB) */

#define FMAN_P1023_FBP_SIZE         0x8000

/* Amount of Fman memory to be used as MURAM (32KB) */

#define FMAN_P1023_MURAM_SIZE       0x8000


/* Values for P3041/P5020 Fman */

/* Amount of BMI free pool memory (129KB) */

#define FMAN_FBP_SIZE               0x21000

/* Amount of Fman memory to be used as MURAM (31KB) */

#define FMAN_MURAM_SIZE             0x7000

/* Allow up to 8 excess buffers */

#define FMAN_EXBS                   8

/* Total number of ports (OH + 1G RX + 1G TX + 10G RX + 10G TX) */

#define FMAN_USED_PORTS             (7 + 4 + 4 + 1 + 1)

/* Available space per FIFO */

#define FMAN_FIFO_SIZE              (FMAN_FBP_SIZE/FMAN_USED_PORTS)

/*
 * FIFO usage per port type
 * The P4080 manual describes FIFO initialization requirements
 * in "24.18.4.4 Internal FIFO Configuration Requirements."
 *
 * For RX ports, IFSZ must be:
 * FMBM_EBMPI[PBS], rounded up to a 256-byte boundary) + 7*256 bytes
 *
 * For TX ports, IFSZ must be:
 * at least ((frame size rounded up to 256) + 3 * 256 + DPDE * 256)
 *
 * For offline ports, IFSZ must be:
 * at least ((frame size rounded up to 256) + 1 * 256 + MXT * 256) bytes,
 * if BMI must bring entire frame, or at least (2 * 256 + MXT * 256)
 * bytes if BMI brings in only the header of the frame.
 *
 * The values below are selected to allow the DTSEC and TGEC ports to
 * support jumbo frames. The offline ports are set to only support
 * normal size frames. Unfortunately, we don't have enough Fman memory
 * available to set them all for jumbo support, so the offline ports
 * end up short changed.
 *
 * Since there are 7 available offline ports, it's possible to allow
 * at least some of them to support jumbo frames if not all offline
 * ports will be needed in a given application.
 */

/* Values for original P4080 Fman. */

#define FMAN_P4080_RX_FIFO_SIZE_1G  0x2B00 /* x 4 == 0xAC00 */
#define FMAN_P4080_RX_FIFO_SIZE_10G 0x2B00 /* x 1 == 0xD700 */
#define FMAN_P4080_OFL_FIFO_SIZE    0x0B00 /* x 7 == 0x12400 */
#define FMAN_P4080_TX_FIFO_SIZE_1G  0x2800 /* x 4 == 0x1C400 */
#define FMAN_P4080_TX_FIFO_SIZE_10G 0x2B00 /* x 1 == 0x1EF00 */

/* Extra FIFO usage per port (0x1200 bytes left from 0x20000) */

#define FMAN_P4080_RX_EXFIFO_SIZE_1G    0x0900
#define FMAN_P4080_RX_EXFIFO_SIZE_10G   0x0900

/* Values for P3041/P5020 Fman */

#define FMAN_RX_FIFO_SIZE_1G        0x2B00 /* x 5 == 0xD700 */
#define FMAN_RX_FIFO_SIZE_10G       0x2B00 /* x 1 == 0x10200 */
#define FMAN_OFL_FIFO_SIZE          0x0000 /* x 7 == N/A */
#define FMAN_TX_FIFO_SIZE_1G        0x2800 /* x 5 == 0x1D900 */
#define FMAN_TX_FIFO_SIZE_10G       0x2B00 /* x 1 == 0x20400 */

/* Values for P1023 Fman */

#define FMAN_P1023_RX_FIFO_SIZE_1G  0x0A00
#define FMAN_P1023_TX_FIFO_SIZE_1G  0x0A00
#define FMAN_P1023_RX_FIFO_SIZE_10G 0x0000
#define FMAN_P1023_TX_FIFO_SIZE_10G 0x0000
#define FMAN_P1023_OFL_FIFO_SIZE    0x0000

/* Extra FIFO usage per port (0x0C00 bytes left from 0x21000) */

#define FMAN_RX_EXFIFO_SIZE_1G      0x0600
#define FMAN_RX_EXFIFO_SIZE_10G     0x0600
#define FMAN_OFL_EXFIFO_SIZE        0x0000
#define FMAN_TX_EXFIFO_SIZE_1G      0x0000
#define FMAN_TX_EXFIFO_SIZE_10G     0x0000

#define FMAN_MU(x)                  ((ULONG)(x) & 0xFFFFF)

/*
 * NIA
 * Next Invoked Action is a way for the frame manager to control
 * the flow of data between different frame manager engines. Fman modules
 * will usually have an NIA register that allows software to configure
 * what the next action will be for a port ID.
 */

#define FMAN_NIA_AC                 0x0003FFFF    /* Action code */
#define FMAN_NIA_ENG                0x007C0000    /* Engine */
#define FMAN_NIA_ORR                0x00800000    /* Order restoration required */

/* Action codes */

/* Fman controller */

#define NIA_AC_CTL_CC               0x00000006    /* Coarse classification */
#define NIA_AC_CTL_ITX              0x00000008    /* Independent mode TX */
#define NIA_AC_CTL_IRX              0x0000000A    /* Independent mode RX */
#define NIA_AC_CTL_HC               0x0000000C    /* Host commands */

/* Keygen */

#define NIA_AC_KG_SCHM              0x0000001F    /* Scheme ID */
#define NIA_AC_KG_SS                0x00000100    /* Scheme select enable */
#define NIA_AC_KG_CCEN              0x00000200    /* Coarse classify enable */

/* Policer */

#define NIA_AC_PL_ABS               0x00008000    /* Absolute profile # */
#define NIA_AC_PL_PFN               0x000000FF    /* Profile number */

/* BMI */

#define NIA_AC_BMI_ENQ              0x00000002    /* Enqueue frame */
#define NIA_AC_BMI_TXI              0x00000010    /* Independent TX, no DMA */
#define NIA_AC_BMI_TXIR             0x00000050    /* Indp. TX, no DMA, release int */
#define NIA_AC_BMI_RLS              0x000000C0    /* Release buffers */
#define NIA_AC_BMI_DSC              0x000000C1    /* Discard frame */
#define NIA_AC_BMI_TXIT             0x000000D0    /* Indp. TX, no DMA, release, term. */
#define NIA_AC_BMI_FTHE             0x00000208    /* Fetch frame hdr + execute */
#define NIA_AC_BMI_FTE              0x0000020C    /* Fetch frame + execute */
#define NIA_AC_BMI_TXR              0x000002C0    /* Normal TX, release */
#define NIA_AC_BMI_TX               0x00000274    /* Normal TX */

/* Engine codes */

#define NIA_ENG_CTL                 0x00000000    /* Fman Controller */
#define NIA_ENG_PARSER              0x00440000    /* Parser */
#define NIA_ENG_KEYGEN              0x00480000    /* Key generator */
#define NIA_ENG_POLICER             0x004C0000    /* Policer */
#define NIA_ENG_BMI                 0x00500000    /* BMI */
#define NIA_ENG_QMI_EQ              0x00540000    /* QMI enqueue */
#define NIA_ENG_QMI_DQ              0x00580000    /* QMI dequeue */

/* Shortcuts */

#define FMAN_NIA_CC                 (NIA_ENG_CTL | NIA_AC_CTL_CC)
#define FMAN_NIA_BMIEQ              (NIA_ENG_BMI | NIA_AC_BMI_ENQ)
#define FMAN_NIA_BMIDSC             (NIA_ENG_BMI | NIA_AC_BMI_DSC)
#define FMAN_NIA_KG                 (NIA_ENG_KEYGEN | NIA_AC_KG_SS | \
                                     NIA_AC_KG_CCEN)
#define FMAN_NIA_PR                 (NIA_ENG_PARSER)
#define FMAN_NIA_PL                 (NIA_ENG_POLICER)

/*
 * BMI registers
 */

/* BMI common registers */

#define FMBM_INIT                   0x000    /* BMI initialization */
#define FMBM_CFG1                   0x004    /* Configuration register 1 */
#define FMBM_CFG2                   0x008    /* Configuration register 2 */
#define FMBM_ISR                    0x020    /* Interrupt status register */
#define FMBM_IER                    0x024    /* Interrupt enable register */
#define FMBM_IFR                    0x028    /* Interrupt force register */
#define FMBM_ARB0                   0x040    /* BMI arbitration */
#define FMBM_ARB1                   0x044    /* BMI arbitration */
#define FMBM_ARB2                   0x048    /* BMI arbitration */
#define FMBM_ARB3                   0x04C    /* BMI arbitration */
#define FMBM_ARB4                   0x050    /* BMI arbitration */
#define FMBM_ARB5                   0x054    /* BMI arbitration */
#define FMBM_ARB6                   0x058    /* BMI arbitration */
#define FMBM_ARB7                   0x05C    /* BMI arbitration */
#define FMBM_DTC0                   0x090    /* Debug trap counter */
#define FMBM_DTC1                   0x094    /* Debug trap counter */
#define FMBM_DTC2                   0x098    /* Debug trap counter */
#define FMBM_DVC0_0                 0x0A0    /* Debug compare value */
#define FMBM_DVC0_1                 0x0A4    /* Debug compare value */
#define FMBM_DVC0_2                 0x0A8    /* Debug compare value */
#define FMBM_DVC1_0                 0x0AC    /* Debug compare value */
#define FMBM_DVC1_1                 0x0B0    /* Debug compare value */
#define FMBM_DVC1_2                 0x0B4    /* Debug compare value */
#define FMBM_DVC2_0                 0x0B8    /* Debug compare value */
#define FMBM_DVC2_1                 0x0BC    /* Debug compare value */
#define FMBM_DVC2_2                 0x0C0    /* Debug compare value */
#define FMBM_DVC3_0                 0x0C4    /* Debug compare value */
#define FMBM_DVC3_1                 0x0C8    /* Debug compare value */
#define FMBM_DVC3_2                 0x0CC    /* Debug compare value */
#define FMBM_DVM0_0                 0x0D0    /* Debug mask value */
#define FMBM_DVM0_1                 0x0D4    /* Debug mask value */
#define FMBM_DVM0_2                 0x0D8    /* Debug mask value */
#define FMBM_DVM1_0                 0x0DC    /* Debug mask value */
#define FMBM_DVM1_1                 0x0E0    /* Debug mask value */
#define FMBM_DVM1_2                 0x0E4    /* Debug mask value */
#define FMBM_DVM2_0                 0x0E8    /* Debug mask value */
#define FMBM_DVM2_1                 0x0EC    /* Debug mask value */
#define FMBM_DVM2_2                 0x0F0    /* Debug mask value */
#define FMBM_DVM3_0                 0x0F4    /* Debug mask value */
#define FMBM_DVM3_1                 0x0F8    /* Debug mask value */
#define FMBM_DVM3_2                 0x0FC    /* Debug mask value */
#define FMBM_GDE                    0x100    /* Global debug enable */
#define FMBM_PP1                    0x104    /* BMI port parameters */
#define FMBM_PP63                   0x1FC    /* BMI port parameters */
#define FMBM_PFS1                   0x204    /* BMI port FIFO size */
#define FMBM_PFS63                  0x2FC    /* BMI port FIFO size */
#define FMBM_PPID1                  0x304    /* BMI port partition ID */
#define FMBM_PPID63                 0x3FC    /* BMI port partition ID */

/* BMI initialization register */

#define FMBM_INIT_STR               0x80000000    /* Start */

/* BMI configuration register 1 */

#define FMBM_CFG1_FBPO              0x000003FF    /* Free buffer pool offset */
#define FMBM_CFG1_FBPS              0x03FF0000    /* Free buffer pool size */

#define FMBM_FBPO(x)                ((x) & FMBM_CFG1_FBPO)
#define FMBM_FBPS(x)                (((x) << 16) & FMBM_CFG1_FBPS)

/* BMI configuration register 2 */

#define FMBM_CFG2_TDMA              0x0000003F    /* Total DMAs */
#define FMBM_CFG2_TTSKS             0x007F0000    /* Total tasks */

#define FMBM_TDMA(x)                ((x) & FMBM_CFG2_TDMA)
#define FMBM_TTSKS(x)               (((x) << 16) & FMBM_CFG2_TTSKS)

/* BMI ISR register */

#define FMBM_ISR_SEC                0x20000000    /* Stats RAM ECC Error */
#define FMBM_ISR_LEC                0x20000000    /* Linked list RAM ECC Error */
#define FMBM_ISR_PEC                0x20000000    /* Pipeline table RAM ECC Error */

/* Global debug enable */

#define FMBM_GDE_IDE                0x40000000    /* Internal debug enable */
#define FMBM_GDE_EDE                0x80000000    /* External debug enable */

/* Port parameters */

#define FMBM_PP_EXD                 0x0000000F    /* Extra DMA */
#define FMBM_PP_MXD                 0x00000F00    /* Max DMA */
#define FMBM_PP_EXT                 0x000F0000    /* Extra tasks */
#define FMBM_PP_MXT                 0x3F000000    /* Maximum tasks */

/* Port FIFO size */

#define FMBM_PFS_IFSZ               0x000003FF    /* Internal FIFO size */
#define FMBM_PFS_EXBS               0x03FF0000    /* Excess buffer size */

#define FMBM_IFSZ(x)                ((((x) / 256) - 1) & FMBM_PFS_IFSZ)
#define FMBM_EXBS(x)                ((((x) / 256) << 16) & FMBM_PFS_EXBS)

/* BMI RX port registers */

#define FMBM_RCFG                   0x000    /* RX configuration */
#define FMBM_RST                    0x004    /* RX status */
#define FMBM_RDA                    0x008    /* RX DMA attributes */
#define FMBM_RFP                    0x00C    /* RX FIFO parameters */
#define FMBM_RFED                   0x010    /* RX frame end data */
#define FMBM_RICP                   0x014    /* RX internal context parameters */
#define FMBM_RIM                    0x018    /* RX internal margins */
#define FMBM_REBM                   0x01C    /* RX external buffer margins */
#define FMBM_RFNE                   0x020    /* RX next frame engine */
#define FMBM_RFCA                   0x024    /* RX frame attributes */
#define FMBM_RFPNE                  0x028    /* RX frame parser next engine */
#define FMBM_RPSO                   0x02C    /* RX parser start offset */
#define FMBM_RPP                    0x030    /* RX policer profile */
#define FMBM_RCCB                   0x034    /* RX coarse classification base */
#define FMBM_RPRAI0                 0x040    /* RX parse results array init */
#define FMBM_RPRAI8                 0x05C    /* RX parse results array init */
#define FMBM_RFQID                  0x060    /* RX frame queue ID */
#define FMBM_REFQID                 0x064    /* RX error frame queue ID */
#define FMBM_RFSDM                  0x068    /* RX frame status discard mask */
#define FMBM_RFSEM                  0x06C    /* RX frame status error mask */
#define FMBM_RFENE                  0x070    /* RX frame enqueue next engine */
#define FMBM_EBMPI0                 0x100    /* buffer manager pool info */
#define FMBM_EBMPI7                 0x11C    /* buffer manager pool info */
#define FMBM_ACNT0                  0x120    /* Allocate counter */
#define FMBM_ACNT7                  0x13C    /* Allocate counter */
#define FMBM_CGM0                   0x160    /* Congestion group map */
#define FMBM_CGM7                   0x17C    /* Congestion group map */
#define FMBM_MPD                    0x180    /* BMan pool depletion */
#define FMBM_RSTC                   0x200    /* RX statistics counters */
#define FMBM_RFRC                   0x204    /* RX frame counter */
#define FMBM_RBFC                   0x208    /* RX bad frames counter */
#define FMBM_RLFC                   0x20C    /* RX large frames counter */
#define FMBM_RFFC                   0x210    /* RX filter frames counter */
#define FMBM_RFDC                   0x214    /* RX frame discard counter */
#define FMBM_RFLDEC                 0x218    /* RX frames list DMA error counter */
#define FMBM_RODC                   0x220    /* RX out of buffers discard counter */
#define FMBM_RBDC                   0x224    /* RX buffers deallocate counter */
#define FMBM_RPC                    0x280    /* RX performance counters */
#define FMBM_RPCP                   0x284    /* RX performance count params */
#define FMBM_RCCN                   0x288    /* RX cycle counter */
#define FMBM_RTUC                   0x28C    /* RX tasks utilization counter */
#define FMBM_RRQUC                  0x290    /* RX queue utilization counter */
#define FMBM_RDUC                   0x294    /* RX DMA utilization counter */
#define FMBM_RFUC                   0x298    /* RX FIFO utilization counter */
#define FMBM_RPAC                   0x29C    /* RX pause activation counter */
#define FMBM_RDCFG0                 0x300    /* RX debug configuration */
#define FMBM_RDCFG2                 0x308    /* RX debug configuration */

/* RX configuration */

#define FMBM_RCFG_EN                0x80000000    /* Enable */
#define FMBM_RCFG_FDOVR             0x02000000    /* Frame discard override */
#define FMBM_RCFG_IM                0x01000000    /* Independent mode */

/* RX status */

#define FMBM_RST_BSY                0x80000000    /* port is busy */

/* RX FIFO parameters */

#define FMBM_RFP_FTH                0x000003FF    /* FIFO threshold */
#define FMBM_RFP_PEL                0x03FF0000    /* Priority elevation threshold */

#define FMBM_TFH(x)                 ((x) & FMBM_RFP_FTH)
#define FMBM_PEL(x)                 (((x) << 16) & FMBM_RFP_PEL)

/* RX frame end data */

#define FMBM_RFED_CFED              0x001F0000    /* Chop frame's end data */
#define FMBM_RFED_CSI               0x1F000000    /* Checksum ignore */

#define FMBM_CFED(x)                (((x) << 16) & FMBM_RFED_CFED)
#define FMBM_CSI(x)                 (((x) << 24) & FMBM_RFED_CSI)

/* RX internal context parameters */

#define FMBM_RICP_ICEOF             0x001F0000    /* IntCtx. Offset */
#define FMBM_RICP_ICIOF             0x00000F00    /* IntCtx. internal offset */
#define FMBM_RICP_ICSZ              0x0000001F    /* IntCtx. copy size */

/* All fields have 16 byte granularity */

#define FMBM_ICEOF(x)               ((((x / 16)) << 16) & FMBM_RICP_ICEOF)
#define FMBM_ICIOF(x)               ((((x / 16)) << 8) & FMBM_RICP_ICIOF)
#define FMBM_ICSZ(x)                (((x / 16)) & FMBM_RICP_ICSZ)

/* RX internal margins */

#define FMBM_RIM_FOF                0xF0000000    /* Frame offset */

/* Frame offset */

#define FMBM_FOF(x)                 (((x) << 28) & FMBM_RIM_FOF)

/* RX external buffer margins */

#define FMBM_REBM_BSM               0x01FF0000    /* Buffer start margin */
#define FMBM_REBM_BEM               0x000001FF    /* Buffer end margin */

#define FMBM_BSM(x)                 (((x) << 16) & FMBM_REBM_BSM)
#define FMBM_BEM(x)                 ((x) & FMBM_REBM_BEM)

/* RX frame attributes */

#define FMBM_RFCA_OR                0x80000000    /* Order definition needed */
#define FMBM_RFCA_COLOR             0x0C000000    /* Default color */
#define FMBM_RFCA_SYNC              0x03000000    /* Synchronization attributes */
#define FMBM_RFCA_MR                0x003F0000    /* Mode attributes */

#define FBMB_COLOR_GREEN            0x00000000
#define FBMB_COLOR_YELLOW           0x04000000
#define FBMB_COLOR_RED              0x08000000

#define FMBM_SYNC_INACTIVE          0x00000000
#define FMBM_SYNC_REQUESTED         0x02000000

/* Buffer manager pool information */

#define FMBM_EBMPI_VAL              0x80000000    /* Valid */
#define FMBM_EBMPI_ACE              0x40000000    /* Allocate cntr enable */
#define FMBM_EBMPI_BPID             0x003F0000    /* Buffer pool ID */
#define FMBM_EBMPI_PBS              0x0000FFFF    /* Pool buffer size */

#define FMBM_BPID(x)                (((x) << 16) & FMBM_EBMPI_BPID)
#define FMBM_PBS(x)                 ((x) & FMBM_EBMPI_PBS)

/* Statistics counter enable */

#define FMBM_RSTC_STEN              0x80000000    /* enable stats counters */

/* BMI TX port registers */

#define FMBM_TCFG                   0x000    /* TX configuration */
#define FMBM_TST                    0x004    /* TX status */
#define FMBM_TDA                    0x008    /* TX DMA attributes */
#define FMBM_TFP                    0x00C    /* TX FIFO parameters */
#define FMBM_TFED                   0x010    /* TX frame end data */
#define FMBM_TICP                   0x014    /* TX internal context parameters */
#define FMBM_TFDNE                  0x018    /* TX frame dequeue next engine */
#define FMBM_TFCA                   0x01C    /* TX frame attributes */
#define FMBM_TCFQID                 0x020    /* TX done queue frame queue ID */
#define FMBM_TEFQID                 0x024    /* TX error frame queue ID */
#define FMBM_TFENE                  0x028    /* TX frame enqueue next engine */
#define FMBM_TRLMTS                 0x02C    /* TX rate limiter scale */
#define FMBM_TRLMT                  0x030    /* TX rate limiter */
#define FMBM_TFNE                   0x070    /* TX frame next engine */
#define FMBM_TCMFNE                 0x07C    /* TX frame continuous mode next engine */
#define FMBM_TSTC                   0x200    /* TX statistics counter */
#define FMBM_TFRC                   0x204    /* TX frame counter */
#define FMBM_TFDC                   0x208    /* TX frames discarded counter */
#define FMBM_TFLEDC                 0x20C    /* TX frame length error discard ctr */
#define FMBM_TFUFDC                 0x210    /* TX frame format error discard ctr */
#define FMBM_TBDC                   0x214    /* TX buffer deallocate counter */
#define FMBM_TPC                    0x280    /* TX performance counters */
#define FMBM_TPCP                   0x284    /* TX performance count params */
#define FMBM_TTUC                   0x28C    /* TX tasks utilization counter */
#define FMBM_TTCQUC                 0x290    /* TX done queue utilization ctr */
#define FMBM_TDUC                   0x294    /* TX DMA utilization counter */
#define FMBM_TFUC                   0x298    /* TX FIFO utilization counter */
#define FMBM_TDCFG0                 0x300    /* TX debug configuration */
#define FMBM_TDCFG2                 0x308    /* TX debug configuration */

/* TX configuration */

#define FMBM_TCFG_EN                0x80000000    /* Enable */
#define FMBM_TCFG_IM                0x01000000    /* Independent mode */

/* TX status */

#define FMBM_TST_BSY                0x80000000    /* Port is busy */

/* TX DMA attributes */

#define FMBM_TDA_SWAP               0xC0000000    /* Swap payload data */
#define FMBM_TDA_ICC                0x30000000    /* IC write cache attributes */

/* TX FIFO parameters */

#define FMBM_TFP_FLCL               0x000003FF    /* FIFO low comfort level */
#define FMBM_TFP_DPDE               0x0000F000    /* Dequeue pipeline depth */
#define FMBM_TFP_MFL                0x03FF0000    /* Minimum fill level */

#define FMBM_FLCL(x)                (((x / 256)) & FMBM_TFP_FLCL)
#define FMBM_DPDE(x)                (((x) << 12) & FMBM_TFP_DPDE)
#define FMBM_MFL(x)                 ((((x / 256)) << 16) & FMBM_TFP_MFL)

/* TX frame next engine (new in Fman_v3) */

#define FMBM_TFNE_EBD               0x80000000 /* Enable buffer deallocate */
#define FMBM_TFNE_NL                0x40000000 /* Not last (continuous mode) */
#define FMBM_TFNE_VSPE              0x01000000 /* Virtual storage profile enable */

#define FMBM_TFNE_NIA               0x00FFFFFF /* Next invoked action */

/* TX frame continuous mode next engine (new in Fman_v3) */

#define FMBM_TCMFNE_NIA             0x00FFFFFF /* Next invoked action */

/* Statistics counter enable */

#define FMBM_TSTC_STEN              0x80000000    /* enable stats counters */

/* BMI offline parsing/host command registers */

#define FMBM_OCFG                   0x000    /* O/H configuration */
#define FMBM_OST                    0x004    /* O/H status */
#define FMBM_ODA                    0x008    /* O/H DMA attributes */
#define FMBM_OICP                   0x00C    /* O/H internal context parameters */
#define FMBM_OFDNE                  0x010    /* O/H frame dequeue next engine */
#define FMBM_OFNE                   0x014    /* O/H frame next engine */
#define FMBM_OFCA                   0x018    /* O/H frame attributes */
#define FMBM_OFPNE                  0x01C    /* O/H frame parser next engine */
#define FMBM_OPSO                   0x020    /* O/H parser start offset */
#define FMBM_OPP                    0x024    /* O/H policer profile */
#define FMBM_OCCB                   0x028    /* O/H coarse classification base */
#define FMBM_OIM                    0x02C    /* O/H internal margins */
#define FMBM_OPRAI0                 0x040    /* O/H parse results array init */
#define FMBM_OPRAI8                 0x05C    /* O/H parse results array init */
#define FMBM_OFQID                  0x060    /* O/H frame queue ID */
#define FMBM_OEFQID                 0x064    /* O/H error frame queue ID */
#define FMBM_OFSDM                  0x068    /* O/H frame status discard mask */
#define FMBM_OFSEM                  0x06C    /* O/H frame status error mask */
#define FMBM_OFENE                  0x070    /* O/H frame enqueue next engine */
#define FMBM_ORLMTS                 0x074    /* O/H rate limiter scale */
#define FMBM_ORLMT                  0x078    /* O/H rate limiter */
#define FMBM_OSTS                   0x200    /* O/H statistics counters */
#define FMBM_OFRC                   0x204    /* O/H frame counter */
#define FMBM_OBFC                   0x208    /* O/H bad frames counter */
#define FMBM_OLFC                   0x20C    /* O/H large frames counter */
#define FMBM_OFFC                   0x210    /* O/H filter frames counter */
#define FMBM_OFDC                   0x214    /* O/H frame discard counter */
#define FMBM_OFLDEC                 0x218    /* O/H frames list DMA error counter */
#define FMBM_OBDC                   0x220    /* O/H buffers deallocate counter */
#define FMBM_OPC                    0x280    /* O/H performance counters */
#define FMBM_OPCP                   0x284    /* O/H performance count params */
#define FMBM_OCCN                   0x288    /* O/H cycle counter */
#define FMBM_OTUC                   0x28C    /* O/H tasks utilization counter */
#define FMBM_ODUC                   0x290    /* O/H DMA utilization counter */
#define FMBM_OFUC                   0x294    /* O/H FIFO utilization counter */
#define FMBM_ODCFG0                 0x300    /* O/H debug configuration */
#define FMBM_ODCFG2                 0x308    /* O/H debug configuration */

/*
 * QMI registers
 */

#define FMQM_GC                     0x000    /* General configuration */
#define FMQM_EISR                   0x008    /* Error interrupt event register */
#define FMQM_EIMR                   0x00C    /* Error interrupt mask register */
#define FMQM_EIF                    0x010    /* Error interrupt force register */
#define FMQM_ISR                    0x014    /* Interrupt event register */
#define FMQM_IMR                    0x018    /* Interrupt mask register */
#define FMQM_IFR                    0x01C    /* Interrupt force register */
#define FMQM_GS                     0x020    /* Global status */
#define FMQM_TS                     0x024    /* Task status */
#define FMQM_ETFC                   0x028    /* Enqueue total frame count */
#define FMQM_DTFC                   0x02C    /* Dequeue total frame count */
#define FMQM_DC0                    0x030    /* Dequeue count 0 */
#define FMQM_DC1                    0x034    /* Dequeue count 1 */
#define FMQM_DC2                    0x038    /* Dequeue count 2 */
#define FMQM_DC3                    0x03C    /* Dequeue count 3 */
#define FMQM_DFNOC                  0x040    /* Dequeue FQID not override count */
#define FMQM_DFCC                   0x044    /* Dequeue FQID from context count */
#define FMQM_DFFC                   0x048    /* Dequeue FQID from FD count */
#define FMQM_DCC                    0x050    /* Dequeue confirm count */
#define FMQM_DTRC                   0x080    /* Debug trace configuration */
#define FMQM_EFDDD                  0x084    /* Enqueue frame desc dynamic debug */
#define FMQM_DTCA1                  0x090    /* Dbg trap config A1 */
#define FMQM_DTVA1                  0x094    /* Dbg trap value A1 */
#define FMQM_DTMA1                  0x098    /* Dbg trap mask A1 */
#define FMQM_DTCA                   0x09C    /* Dbg trap counter A */
#define FMQM_DTCA2                  0x0A0    /* Dbg trap config A2 */
#define FMQM_DTVA2                  0x0A4    /* Dbg trap value A2 */
#define FMQM_DTMA2                  0x0A8    /* Dbg trap mask A2 */
#define FMQM_DTCB1                  0x0B0    /* Dbg trap config B1 */
#define FMQM_DTVB1                  0x0B4    /* Dbg trap value B1 */
#define FMQM_DTMB1                  0x0B8    /* Dbg trap mask B1 */
#define FMQM_DTCB                   0x0BC    /* Dbg trap counter B */
#define FMQM_DTCB2                  0x0C0    /* Dbg trap config B2 */
#define FMQM_DTVB2                  0x0C4    /* Dbg trap value B2 */
#define FMQM_DTMB2                  0x0C8    /* Dbg trap mask B2 */
#define FMQM_DTCC1                  0x0D0    /* Dbg trap config C1 */
#define FMQM_DTVC1                  0x0D4    /* Dbg trap value C1 */
#define FMQM_DTMC1                  0x0D8    /* Dbg trap mask C1 */
#define FMQM_DTCC                   0x0DC    /* Dbg trap counter C */
#define FMQM_DTCC2                  0x0D0    /* Dbg trap config C2 */
#define FMQM_DTVC2                  0x0D4    /* Dbg trap value C2 */
#define FMQM_DTMC2                  0x0D8    /* Dbg trap mask C2 */

/* General configuration register */

#define FMQM_GC_DEQ_THR             0x0000003F    /* Dequeue threshold */
#define FMQM_GC_ENQ_THR             0x00003F00    /* Enqueue threshold */
#define FMQM_GC_SRST                0x01000000    /* Soft reset */
#define FMQM_GC_STEN                0x10000000    /* stats enable */
#define FMQM_GC_DQ_EN               0x40000000    /* Dequeue enable */
#define FMQM_GC_EQ_EN               0x80000000    /* Enqueue enable */

/* Error interrupt event register */

#define FMQM_EISR_DFUPE             0x40000000    /* DQ from unknown port */
#define FMQM_EISR_DEE               0x80000000    /* 2-bit ECC error on QMI RAM */

/* Interrupt event register */

#define FMQM_ISR_SEE                0x80000000    /* 1-bit ECC error on QMI RAM */

/* Global status register */

#define FMQM_GS_SRS                 0x00010000    /* Soft reset sequence */
#define FMQM_GS_BSY_EF              0x10000000    /* QMI busy enqueue FD */
#define FMQM_GS_BSY_DF              0x20000000    /* QMI busy dequeue FD */
#define FMQM_GS_BSY_ET              0x40000000    /* QMI busy enqueue Tnum */
#define FMQM_GS_BSY_TT              0x80000000    /* QMI busy dequeue Tnum */

/* Task status register */

#define FMQM_TS_DFS                 0x0000007F    /* Dequeue FD status */
#define FMQM_TS_DTS                 0x00007F00    /* Dequeue Tnum status */
#define FMQM_TS_ETS                 0x7F000000    /* Enqueue Tnum status */


/* Port registers (RX, TX, Offline parsing/host command) */

#define FMQM_PC                     0x000    /* Port configuration */
#define FMQM_PS                     0x004    /* Port status */
#define FMQM_PTS                    0x008    /* Port task status */
#define FMQM_PEN                    0x01C    /* Enqueue NIA */
#define FMQM_PETFC                  0x020    /* Enqueue total frame count */
#define FMQM_PDN                    0x02C    /* Dequeue NIA */
#define FMQM_PDC                    0x030    /* Dequeue config */
#define FMQM_PDTFC                  0x034    /* Dequeue total frame count */
#define FMQM_PDFNOC                 0x038    /* Dequeue FQID not override count */
#define FMQM_PDCC                   0x03C    /* Dequeue confirm count */

/* Port configuration register */

#define FMQM_PC_STEN                0x10000000    /* Stats enable */
#define FMQM_PC_EN                  0x80000000    /* Port enable */

/* Port status register */

#define FMQM_PS_BSY_DF              0x20000000    /* Busy dequeue FD */
#define FMQM_PS_BSY_ET              0x40000000    /* Busy enqueue Tnum */
#define FMQM_PS_BSY_DT              0x80000000    /* Busy dequeue Tnum */

/* Port task status */

#define FMQM_TS_PDFS                FMQM_TS_DFS
#define FMQM_TS_PDTS                FMQM_TS_DTS
#define FMQM_TS_PETS                FMQM_TS_ETS

/* Port dequeue config register */

#define FMQM_PDC_BC                 0x0000FFFF    /* Byte count level control */
#define FMQM_PDC_SP                 0x00F00000    /* Sub-portal/channel num */
#define FMQM_PDC_FRM                0x01000000    /* Frame count */
#define FMQM_PDC_PF                 0x02000000    /* Pre-fetch control */
#define FMQM_PDC_OPT                0x70000000    /* Opts for dq src and type */
#define FMQM_PDC_PRI                0x80000000    /* Priority option */

#define FMQM_SP(x)                  (((x) << 20) & FMQM_PDC_SP)

/*
 * Parser internal memory offsets
 */

#define FMPR_HXS                    0x000    /* Header examination sequences */
#define FMPR_SP_START               0x040    /* Soft parser instructions */
#define FMPR_SP_MBO0                0x3FE    /* Must be 0 */
#define FMPR_SP_MBO1                0x3FF    /* Must be 0 */
#define FMPR_SP_END                 0x7FF    /* Soft parser instructions end */

#define FMPR_SP_SIZE                0x7C0    /* 1984 bytes */

#define FMPR_SP_PAW0                0x800    /* Soft parse parameter array 0 */
#define FMPR_SP_PAW15               0x83C    /* Soft parse parameter array 15 */

/*
 * Per-port Parser registers
 */

#define FMPR_SSA0                   0x000    /* Parser soft sequence attachment */
#define FMPR_LCVM0                  0x004    /* Line-up enable confirmation vector mask */
#define FMPR_SSA15                  0x078    /* Parser soft sequence attachment */
#define FMPR_LCVM15                 0x07C    /* Line-up enable confirmation vector mask */
#define FMPR_CAC                    0x3F8    /* Config access control */
#define FMPR_CTPID                  0x3FC    /* Configured TPID */

/* Soft sequence attachment */

#define FMPR_SSA_CFG                0xFFFFF000    /* HXS configuration */
#define FMPR_SSA_ERM                0x00000800    /* Error reporting enable */
#define FMPR_SSA_EN                 0x00000400    /* Soft sequence enable */
#define FMPR_SSA_START              0x000003FF    /* Soft sequence program start */

/* Config access control */

#define FMPR_CAC_PSTOP              0x00000001    /* Stop port */
#define FMPR_CAC_PSTAT              0x00000100    /* Port status */

/* Sequence attachment/line-up config vector offsets */

#define FMPR_HDR_ETH                0
#define FMPR_HDR_LLC                1
#define FMPR_HDR_VLAN               2
#define FMPR_HDR_PPPOE              3
#define FMPR_HDR_MPLS               4
#define FMPR_HDR_IPV4               5
#define FMPR_HDR_IPV6               6
#define FMPR_HDR_GRE                7
#define FMPR_HDR_MINE               8
#define FMPR_HDR_OL3                9
#define FMPR_HDR_TCP                10
#define FMPR_HDR_UDP                11
#define FMPR_HDR_IPSEC              12
#define FMPR_HDR_SCTP               13
#define FMPR_HDR_DCCP               14
#define FMPR_HDR_OL4                15

#define FMPR_HDR_CNT                16

/* Compatibility with FMC tool */

#define HEADER_TYPE_ETH             FMPR_HDR_ETH
#define HEADER_TYPE_SNAP            FMPR_HDR_LLC
#define HEADER_TYPE_VLAN            FMPR_HDR_VLAN
#define HEADER_TYPE_PPPoE           FMPR_HDR_PPPOE
#define HEADER_TYPE_MPLS            FMPR_HDR_MPLS
#define HEADER_TYPE_IPv4            FMPR_HDR_IPV4
#define HEADER_TYPE_IPv6            FMPR_HDR_IPV6
#define HEADER_TYPE_GRE             FMPR_HDR_GRE
#define HEADER_TYPE_MINENCAP        FMPR_HDR_MINE
#define HEADER_TYPE_TCP             FMPR_HDR_TCP
#define HEADER_TYPE_UDP             FMPR_HDR_UDP
#define HEADER_TYPE_IPSEC_AH        FMPR_HDR_IPSEC
#define HEADER_TYPE_IPSEC_ESP       FMPR_HDR_IPSEC
#define HEADER_TYPE_SCTP            FMPR_HDR_SCTP
#define HEADER_TYPE_DCCP            FMPR_HDR_DCCP
#define HEADER_TYPE_USER_DEFINED_L3 FMPR_HDR_OL3
#define HEADER_TYPE_USER_DEFINED_L4 FMPR_HDR_OL4

typedef struct fman_sp_label
    {
    UINT32      fman_label_offset;    /* Instruction offset */
    UINT32      fman_label_hdrtype;    /* Header type */
    UINT8       fman_label_index;    /* Per-header index */
    } FMAN_SP_LABEL;

#define FMPR_LABEL_CNT              32
#define FMPR_LABEL_NONE             255

typedef struct fman_sp_params
    {
    BOOL            fman_sparam_override;
    UINT32          fman_sparam_size;    /* Parser code size */
    UINT16          fman_sparam_base;    /* Base address (in words) */
    UINT8 *         fman_sparam_code;    /* Parser code */
    UINT32          fman_sparam_param[FMPR_HDR_CNT];
    UINT8           fman_sparam_labelcnt;/* Number of labels */
    FMAN_SP_LABEL   fman_sparam_labels[FMPR_LABEL_CNT];
    } FMAN_SP_PARAMS;

/*
 * Line-up configuration vector mask values for the header types
 * defined above. Note that these are user-defined: the values I have
 * selected here ensure that a unique bit will be set in the LCV
 * field of the parser result to indicate that a given header was
 * successfully detected and parsed in the arriving frame. These are
 * used by the VxWorks dTSEC and TGEC drivers, which use the parser
 * results to implement TCP/IP checksum validation offload for
 * received frames.
 */

#define FMPR_LCV_ETH                0x00000001
#define FMPR_LCV_LLC                0x00000002
#define FMPR_LCV_VLAN               0x00000004
#define FMPR_LCV_PPPOE              0x00000008
#define FMPR_LCV_MPLS               0x00000010
#define FMPR_LCV_IPV4               0x00000020
#define FMPR_LCV_IPV6               0x00000040
#define FMPR_LCV_GRE                0x00000080
#define FMPR_LCV_MINE               0x00000100
#define FMPR_LCV_OL3                0x00000200
#define FMPR_LCV_TCP                0x00000400
#define FMPR_LCV_UDP                0x00000800
#define FMPR_LCV_IPSEC              0x00001000
#define FMPR_LCV_SCTP               0x00002000
#define FMPR_LCV_DCCP               0x00004000
#define FMPR_LCV_OL4                0x00008000

/* Parse array offsets */

#define FMPR_PROFF_SHIM1            16    /* Shim 1 offset */
#define FMPR_PROFF_SHIM2            17    /* Shim 2 offset */
#define FMPR_PROFF_IPPID            18    /* IP PID offset */
#define FMPR_PROFF_ETH              19    /* Ethernet offset */
#define FMPR_PROFF_LLCSNAP          20    /* LLC/SNAP offset */
#define FMPR_PROFF_VTCI1            21    /* VLAN TCI 1 offset */
#define FMPR_PROFF_VTCIN            22    /* VLAN TCI N offset */
#define FMPR_PROFF_ETYPEN           23    /* ETYPE N offset */
#define FMPR_PROFF_PPPOE            24    /* PPPOE offset */
#define FMPR_PROFF_MPLS1            25    /* MPLS 1 offset */
#define FMPR_PROFF_MPLSN            26    /* MPLS N offset */
#define FMPR_PROFF_IP1              27    /* IP 1 offset */
#define FMPR_PROFF_IPN              28    /* IP N offset */
#define FMPR_PROFF_MINENCAP         28    /* MinEncap offset */
#define FMPR_PROFF_GRE              29    /* GRE offset */
#define FMPR_PROFF_L4               30    /* Layer 4 offset */
#define FMPR_PROFF_NXTHDROFF        31    /* NextHeader offset */

/*
 * Global parser configuration registers
 */

#define FMPRG_SXPAW0                0x000    /* Soft examination parameter array */
#define FMPRG_SXPAW1                0x004    /* Soft examination parameter array */
#define FMPRG_SXPAW2                0x008    /* Soft examination parameter array */
#define FMPRG_SXPAW3                0x00C    /* Soft examination parameter array */
#define FMPRG_SXPAW4                0x010    /* Soft examination parameter array */
#define FMPRG_SXPAW5                0x014    /* Soft examination parameter array */
#define FMPRG_SXPAW6                0x018    /* Soft examination parameter array */
#define FMPRG_SXPAW7                0x01C    /* Soft examination parameter array */
#define FMPRG_SXPAW8                0x020    /* Soft examination parameter array */
#define FMPRG_SXPAW9                0x024    /* Soft examination parameter array */
#define FMPRG_SXPAW10               0x028    /* Soft examination parameter array */
#define FMPRG_SXPAW11               0x02C    /* Soft examination parameter array */
#define FMPRG_SXPAW12               0x030    /* Soft examination parameter array */
#define FMPRG_SXPAW13               0x034    /* Soft examination parameter array */
#define FMPRG_SXPAW14               0x038    /* Soft examination parameter array */
#define FMPRG_SXPAW15               0x03C    /* Soft examination parameter array */
#define FMPRG_RPCLIM                0x040    /* RX parsing cycle limit */
#define FMPRG_RPIMAC                0x044    /* Parse int. memory access control */
#define FMPRG_PMEEC                 0x048    /* Parse mem ECC error capture */

#define FMPRG_RPIMAC_PEN            0x00000001 /* Start parser */
#define FMPRG_RPIMAC_STAT           0x00000100 /* Port status */

/* Parser result structure */

typedef struct fman_pr
    {
    volatile UINT8      fman_pr_portid;    /* Logical port ID */
    volatile UINT8      fman_pr_shimr;    /* Shim header result */
    volatile UINT16     fman_pr_l2r;    /* Layer 2 result */

    volatile UINT16     fman_pr_l3r;    /* Layer 3 result */
    volatile UINT8      fman_pr_l4r;    /* Layer 4 result */
    volatile UINT8      fman_pr_cplan;    /* Classification plan */

    volatile UINT16     fman_pr_nhtype;    /* Next header type */
    volatile UINT16     fman_pr_runsum;    /* Running sum */

    volatile UINT32     fman_pr_lcv;    /* Line-up confirmation vector */

    volatile UINT8      fman_pr_shoff[2];/* Shim offsets */
    volatile UINT8      fman_pr_ip_pid;    /* IP protocol ID */
    volatile UINT8      fman_pr_ethoff;    /* Ethernet header offset */

    volatile UINT8      fman_pr_snoff;    /* LLC/SNAP header offset */
    volatile UINT8      fman_pr_vloff1;    /* VLAN TCI offset 1 */
    volatile UINT8      fman_pr_vloffn;    /* Last VLAN TCI offset */
    volatile UINT8      fman_pr_etoff;    /* Last ethertype offset */

    volatile UINT8      fman_pr_poeoff; /* PPPoE header offset */
    volatile UINT8      fman_pr_mpls1;    /* MPLS header offset 1 */
    volatile UINT8      fman_pr_mplsn;    /* Last MPLS header offset */
    volatile UINT8      fman_pr_ipoff1;    /* IP header offset 1 */

    volatile UINT8      fman_pr_ipoffn;    /* Last IP header offset */
    volatile UINT8      fman_pr_greoff;    /* GRE header offset */
    volatile UINT8      fman_pr_l4off;    /* L4 header offset */
    volatile UINT8      fman_pr_nhoff;    /* Next header offset */
    } FMAN_PR;

/* L2 result field */

#define FMPR_L2R_TYPE               0xF800    /* L2 type */
#define FMPR_L2R_INFO               0x07E0    /* Info field */
#define FMPR_L2R_ERROR              0x001F    /* Error field */

#define FML2R_TYPE_ETH              0x8000    /* Ethernet present */
#define FML2R_TYPE_VLAN             0x4000    /* VLAN present */
#define FML2R_TYPE_SNAP             0x2000    /* LLC+SNAP present */
#define FML2R_TYPE_MPLS             0x1000    /* MPLS present */
#define FML2R_TYPE_PPP              0x0800    /* PPPoE+PPP present */

#define FML2R_INFO_CFI              0x0400    /* CFI bit in VLAN frame set */
#define FML2R_INFO_ULLC             0x0200    /* Unkown LLC/OUI */
#define FML2R_INFO_SVL              0x0100    /* Stacked VLAN */
#define FML2R_INFO_UNP              0x0080    /* Unknown protocol */
#define FML2R_INFO_FT               0x0060    /* Frame type */

#define FML2R_FT_UCAST              0x0000
#define FML2R_FT_RSVD               0x0020
#define FML2R_FT_MCAST              0x0040
#define FML2R_FT_BCAST              0x0060

#define FML2R_ERR_OK                0x0000    /* No error */
#define FML2R_ERR_ETHX              0x0001    /* Eth Parse exceeded 256 bytes */
#define FML2R_ERR_ETHT              0x0002    /* Eth Frame truncation */
#define FML2R_ERR_VLNX              0x0003    /* VLAN Parse exceeded 256 bytes */
#define FML2R_ERR_VLNT              0x0004    /* VLAN Frame truncation */
#define FML2R_ERR_SNX               0x0005    /* LLC/SNAP Parse exceeded 256 bytes */
#define FML2R_ERR_SNT               0x0006    /* LLC/SNAP Frame truncation */
#define FML2R_ERR_8023T             0x0007    /* 802.3 truncation */
#define FML2R_ERR_MPLX              0x0008    /* MPLS Parse exceeded 256 bytes */
#define FML2R_ERR_MPLT              0x0009    /* MPLS Frame truncation */
#define FML2R_ERR_PPPX              0x000A    /* PPPoE Parse exceeded 256 bytes */
#define FML2R_ERR_PPPT              0x000B    /* PPPoE Frame truncation */
#define FML2R_ERR_PPPM              0x000C    /* PPPoE MTU violated */
#define FML2R_ERR_PPPV              0x000D    /* PPPoE VER field invalid */
#define FML2R_ERR_PPPTY             0x000E    /* PPPoE TYPE field invalid */
#define FML2R_ERR_PPPC              0x000F    /* PPPoE CODE field invalid */
#define FML2R_ERR_PPPS              0x0010    /* PPPoE session ID invalid */
#define FML2R_ERR_SOFTX             0x001E    /* Soft parser exceeded 256 bytes */
#define FML2R_ERR_SOFTT             0x001F    /* Soft parser frame truncated */

/* L3 result field */

#define FMPR_L3R_TYPE               0xFC00    /* L3 type */
#define FMPR_L3R_RTYPE1             0x0200    /* 1st result type */
#define FMPR_L3R_RES1               0x01F0    /* 1st result */
#define FMPR_L3R_RTYPEL             0x0008    /* last result type */
#define FMPR_L3R_RESL               0x0007    /* last result */

#define FML3R_TYPE_IP4F             0x8000    /* 1st IPv4 present */
#define FML3R_TYPE_IP6F             0x4000    /* 1st IPv6 present */
#define FML3R_TYPE_GRE              0x2000    /* GRE present */
#define FML3R_TYPE_MINC             0x1000    /* MinEnc present */
#define FML3R_TYPE_IP4L             0x0800    /* Last IPv4 present */
#define FML3R_TYPE_IP6L             0x0400    /* Last IPv6 present */

#define FML3R_RT1_INFO              0x0000
#define FML3R_RT1_ERR               0x0200

#define FML3R_RTL_INFO              0x0000
#define FML3R_RTL_ERR               0x0008

/* INFO code definitions */

/* first result IPv4 info codes */

#define FML3R_R1I4_OPT              0x0100    /* IP option present */
#define FML3R_R1I4_UNK              0x0080    /* Unknown proto */
#define FML3R_R1I4_FRG              0x0040    /* Packet is a fragment */
#define FML3R_R1I4_PTY              0x0030  /* Packet type */

/* IPv4 packet type */

#define FML3R_1T4_UCAST             0x0000
#define FML3R_1T4_RSVD              0x0010
#define FML3R_1T4_MCAST             0x0020
#define FML3R_1T4_BCAST             0x0030

/* first result IPv6 info codes */

#define FML3R_R1I6_HH               0x0100    /* Hop-by-hop options present */
#define FML3R_R1I6_UNK              0x0080    /* Unknown next header */
#define FML3R_R1I6_FRG              0x0040    /* Packet is a fragment */
#define FML3R_R1I6_PTY              0x0020  /* Packet type */
#define FML3R_R1I6_HHO              0x0010     /* Hop-by-hop options present */

/* IPv6 packet type */

#define FML3R_1T6_UCAST             0x0000
#define FML3R_1T6_MCAST             0x0010

/* last result IPv4 info codes */

#define FML3R_RLI4_FRG              0x0004    /* packet is a fragment */
#define FML3R_RLI4_PTY              0x0003    /* packet type */

/* IPv4 packet type */

#define FML3R_LT4_UCAST             0x0000
#define FML3R_LT4_RSVD              0x0001
#define FML3R_LT4_MCAST             0x0002
#define FML3R_LT4_BCAST             0x0003

/* last result IPv6 info codes */

#define FML3R_RLI6_FRG              0x0004    /* packet is a fragment */
#define FML3R_RLI6_PTY              0x0002    /* packet type */

/* IPv6 packet type */

#define FML3R_LT6_UCAST             0x0000
#define FML3R_LT6_MCAST             0x0002

/* last result GRE info codes */

#define FML3R_RLIG_1701             0x0004    /* RFC1701 R bit set */
#define FML3R_RLIG_UNK              0x0002    /* Unknown protocole */
#define FML3R_RLIG_RSVD             0x0001

/* last result MinEncap info codes */

#define FML3R_RLIM_OSAP             0x0004    /* Orig. src address present */
#define FML3R_RLIM_UNK              0x0002    /* Unknown protocol */
#define FML3R_RLIM_RSVD             0x0001

/* ERROR code definitions */

/* Common error codes */

#define FML3R_RE_OK                 0x0100    /* No error */
#define FML3R_RE_X                  0x0080    /* Exceeds 256 bytes */
#define FML3R_RE_T                  0x0040    /* Frame truncation */

/* IPv4 error codes */

#define FML3R_RE_4T                 0x0020    /* IPv4 truncation */
#define FML3R_RE_4CSUM              0x0010    /* IPv4 checksum error */
#define FML3R_RE_4VER               0x0004    /* IPv4 version error */
#define FML3R_RE_4SIZE              0x0002    /* IPv4 frag size error */
#define FML3R_RE_4HLEN              0x0001    /* Header length error */

/* IPv6 error codes */

#define FML3R_RE_6T                 0x0020    /* IPv6 truncation */
#define FML3R_RE_6EHV               0x0010    /* Extention header violation */
#define FML3R_RE_6VER               0x0004    /* IPv6 version error */
#define FML3R_RE_6RHE               0x0002    /* Routing header error */

/* GRE error codes */

#define FML3R_RE_GVE                0x0020    /* GRE version error */

/* MinEnc error codes */

#define FML3R_RE_MCSUM              0x0010    /* Mininum encapsulation csum error */

/* Layer 4 field */

#define FMPR_L4_TYPE                0xE0    /* Layer 4 type */
#define FMPR_L4_RTYPE               0x10    /* Result type */
#define FMPR_L4_RES                 0x0F    /* result/error code */

/* Layer 4 type codes */

#define FML4R_L4T_NONE              0x10    /* No parsing or soft parsing */
#define FML4R_L4T_TCP               0x20
#define FML4R_L4T_UDP               0x40
#define FML4R_L4T_IPSEC             0x60
#define FML4R_L4T_SCTP              0x80
#define FML4R_L4T_DCCP              0xA0

/* Result/type indicator */

#define FML4R_RT_INFO               0x00    /* info bitfield */
#define FML4R_RT_ERROR              0x10    /* error code */

/* 'None' info */

/* user defined */

/* 'None' errors */

#define FML4R_REN_X                 0x00    /* Exceeds 256 bytes */
#define FML4R_REN_T                 0x01    /* Frame truncation */

/* TCP info */

#define FML4R_RIT_OPT               0x08    /* Option present */
#define FML4R_RIT_CTL1              0x04    /* Control bits 6-11 set */
#define FML4R_RIT_CTL2              0x02    /* Control bits 3-5 set */
#define FML4R_RIT_CSUM              0x01    /* Checksum validation done */

/* TCP errors */

#define FML4R_RET_OFF               0x02    /* Invalid offset */
#define FML4R_RET_TRUNC             0x03    /* data offset > IP len */
#define FML4R_RET_CSUM              0x04    /* Bad checksum */
#define FML4R_RET_FLAGS             0x05    /* bad flags */

/* UDP info */

#define FML4R_RIU_CSNZ              0x08    /* checksum non-zero */
#define FML4R_RIU_CSUM              0x01    /* checksum validation done */

/* UDP errors */

#define FML4R_REU_LEN               0x02    /* Length error */
#define FML4R_REU_CSUM              0x04    /* Bad checksum */

/* IPSec info */

/* user defined */

/* IPSec errors */

/* user defined */


/* SCTP info */

/* user defined */

/* SCTP errors */

/* user defined */


/* DCCP info */

/* user defined */

/* DCCP errors */

/* user defined */



/*
 * Policer
 */

/* General configuration registers */

#define FMPL_GCR                    0x000    /* General configuration */
#define FMPL_GSR                    0x004    /* General status */
#define FMPL_ISR                    0x008    /* Interrupt status register */
#define FMPL_IMR                    0x00C    /* Interrupt mask register */
#define FMPL_IFR                    0x010    /* Interrupt force register */
#define FMPL_EISR                   0x014    /* Error interrupt */
#define FMPL_EIMR                   0x018    /* Error interrupt enable */

/* General configuration */

#define FMPL_GCR_EN                 0x80000000    /* Enable policer */
#define FMPL_GCR_STEN               0x40000000    /* Statistics enable */
#define FMPL_GCR_DAR                0x20000000    /* Disable auto refresh */
#define FMPL_GCR_NIA                0x00FFFFFF    /* Default NIA */

/* General status */

#define FMPL_GSR_BSY                0x80000000    /* Policer busy */
#define FMPL_GSR_DQS                0x40000000    /* Input queue status */
#define FMPL_GSR_RPB                0x20000000    /* Processor busy */
#define FMPL_GSR_LPALG              0x0000C000    /* Last profile algorith */
#define FMPL_GSR_LPCA               0x00003000    /* Last prof. color action */
#define FMPL_GSR_LPNUM              0x000000FF    /* Last profile number */

/* Last profile algorithm */

#define FMPL_LPALG_PASSTHRU         0x00000000
#define FMPL_LPALG_RFC2698          0x00004000
#define FMPL_LPALG_RFC4115          0x00008000

/* Last profile coloring action */

#define FMPL_LPCA_NOCHANGE          0x00000000
#define FMPL_LPCA_G2Y               0x00001000 /* green to yellow */
#define FMPL_LPCA_G2R               0x00002000 /* green to red */
#define FMPL_LPCA_Y2R               0x00003000 /* yellow to red */

/* Policer event register */

#define FMPL_ISR_PSIC               0x80000000 /* PRAM self-test done */
#define FMPL_ISR_AAC                0x40000000 /* Atomic action complete */

/* Policer error event register */

#define FMPL_EISR_DEEC              0x80000000    /* Double ECC error */
#define FMPL_EISR_IEE               0x40000000    /* Init entry error */

/* Global stats counters */

#define FMPL_RPC                    0x020    /* RED packet count  */
#define FMPL_YPC                    0x024    /* YELLOW packet count */
#define FMPL_RRPC                   0x028    /* Recolored RED count */
#define FMPL_RYPC                   0x02C    /* Recolored YELLOW count */
#define FMPL_TPC                    0x030    /* Total packet count */
#define FMPL_FLMC                   0x024    /* Frame length mismatch count */

/* RAM access registers */

#define FMPL_PAR                    0x08C    /* Profile action register */

#define FMPL_PE_MODE                0x090    /* Profile entry mode */
#define FMPL_PE_GNIA                0x094    /* Profile entry GREEN NIA */
#define FMPL_PE_YNIA                0x098    /* Profile entry YELLOW NIA */
#define FMPL_PE_RNIA                0x09C    /* Profile entry RED NIA */
#define FMPL_PE_CIR                 0x0A0    /* Committed info rate */
#define FMPL_PE_CBS                 0x0A4    /* Committed burst size */
#define FMPL_PE_PIR_EIR             0x0A8    /* Peak/Excess info rate */
#define FMPL_PE_PBS_EBS             0x0AC    /* Peak/Excess burst size */
#define FMPL_PE_LTS                 0x0B0    /* Last timestamp */
#define FMPL_PE_CTS                 0x0B4    /* Committed token status */
#define FMPL_PE_PTS_ETS             0x0B8    /* Peak/Excess token status */
#define FMPL_PE_GPC                 0x0BC    /* GREEN packet count */
#define FMPL_PE_YPC                 0x0C0    /* YELLOW packet count */
#define FMPL_PE_RPC                 0x0C4    /* RED packet count */
#define FMPL_PE_RYPC                0x0C8    /* Recolored YELLOW count */
#define FMPL_PE_RRPC                0x0CC    /* Recolored RED count */

#define FMPL_DPMR                   0x200    /* Default profile mapping */
#define FMPL_PMR1                   0x204    /* Profile mapping port 1 */
#define FMPL_PMR12                  0x240    /* Profile mapping port 12 */

/* Action register */

#define FMPL_PAR_GO                 0x80000000    /* Activate access */
#define FMPL_PAR_RW                 0x40000000    /* Access is read/write */
#define FMPL_PAR_PSI                0x20000000    /* PRAM self-init */
#define FMPL_PAR_PNUM               0x00FF0000    /* Profile number */
#define FMPL_PAR_PWSEL              0x0000FFFF    /* Profile write select */

#define FMPL_PAR_READ               0x40000000
#define FMPL_PAR_WRITE              0x00000000

#define FMPL_PNUM(x)                (((x) << 16) & FMPL_PAR_PNUM)
#define FMPL_PWSEL(x)               ((x) & FMKG_PAR_PWSEL)

/* Profile entry mode */

#define FMPL_PE_MODE_PI             0x80000000    /* Profile init */
#define FMPL_PE_MODE_CBLND          0x40000000    /* Color blind mode */
#define FMPL_PE_MODE_ALG            0x30000000    /* Algorithm */
#define FMPL_PE_MODE_DEFCLR         0x0C000000    /* Default color */
#define FMPL_PE_MODE_OVCLR          0x03000000    /* Override color */
#define FMPL_PE_MODE_PKT            0x00800000    /* Packet mode */
#define FMPL_PE_MODE_FPP            0x003F0000    /* Fixed point position */
#define FMPL_PE_MODE_FLS            0x0000F000    /* Frame length selection */
#define FMPL_PE_MODE_RBFLS          0x00000800    /* Roll back frame len sel */
#define FMPL_PE_MODE_TRA            0x00000004    /* Trap profile flow A */
#define FMPL_PE_MODE_TRB            0x00000002    /* Trap profile flow B */
#define FMPL_PE_MODE_TRC            0x00000001    /* Trap profile flow C */

#define FMPL_ALG_PASSTHRU           0x00000000
#define FMPL_ALG_RFC2698            0x10000000
#define FMPL_ALG_RFC4115            0x20000000

#define FMPL_DEFCLR_GREEN           0x00000000
#define FMPL_DEFCLR_YELLOW          0x04000000
#define FMPL_DEFCLR_RED             0x08000000

#define FMPL_OVCLR_GREEN            0x00000000
#define FMPL_OVCLR_YELLOW           0x01000000
#define FMPL_OVCLR_RED              0x02000000
#define FMPL_OVCLR_GREEN_NC         0x03000000

#define FMPL_PKTMODE_BYTE           0x00000000
#define FMPL_PKTMODE_PACKET         0x00800000

#define FMPL_FPP(x)                 (((x) << 16) & FMPL_PE_MODE_FPP)

#define FMPL_FLS_L2                 0x00003000
#define FMPL_FLS_L3                 0x0000B000
#define FMPL_FLS_L4                 0x0000E000
#define FMPL_FLS_FULL               0x0000F000

#define FMPL_RBFLS_L2               0x00000000
#define FMPL_RBFLS_FULL             0x00000800

/* Profile entry green NIA */

#define FMPL_PE_GNIA_VALID          0x80000000    /* NIA is valid */
#define FMPL_PE_GNIA_NIA            0x00FFFFFF    /* Nia code */

/* Profile entry yellow NIA */

#define FMPL_PE_YNIA_VALID          0x80000000    /* NIA is valid */
#define FMPL_PE_YNIA_NIA            0x00FFFFFF    /* Nia code */

/* Profile entry red NIA */

#define FMPL_PE_RNIA_VALID          0x80000000    /* NIA is valid */
#define FMPL_PE_RNIA_NIA            0x00FFFFFF    /* Nia code */

/* default profile mapping registers */

#define FMPL_DPMR_VALID             0x80000000    /* Profile valid */
#define FMPL_DPMR_BRN               0x000F0000    /* Bit replacement number */
#define FMPL_DPMR_PBNUM             0x000000FF    /* Profile base number */

/*
 * The policer supports 256 profile entries.
 * Note: the committed info rate (CIR) and peak info rate/excess info rate
 * (PIR_EIR) fields in the profile entry represent fixed point values.
 * The upper 16 bits represent the integer portion of the rate, and the
 * lower 16 bits represent the fractional portion.
 */

#define FMAN_PROFILE_CNT            256

typedef struct fman_pl_entry
    {
    UINT32        fmpl_mode;
    UINT32        fmpl_gnia;
    UINT32        fmpl_ynia;
    UINT32        fmpl_rnia;
    union
    {
    UINT32        fmpl_cir;
    struct
        {
        UINT16    fmpl_cir_int;
        UINT16    fmpl_cir_frac;
        } s_cir;
    } u_cir;
    UINT32        fmpl_cbs;
    union
    {
    UINT32        fmpl_pir_eir;
    struct
        {
        UINT16    fmpl_pir_eir_int;
        UINT16    fmpl_pir_eir_frac;
        } s_pir_eir;
    } u_pir_eir;
    UINT32        fmpl_pbs_ebs;
    UINT32        fmpl_lts;
    UINT32        fmpl_cts;
    UINT32        fmpl_pts_ets;
    UINT32        fmpl_gpc;
    UINT32        fmpl_rpc;
    UINT32        fmpl_ypc;
    UINT32        fmpl_rypc;
    UINT32        fmpl_rrpc;
    } FMAN_PL_ENTRY;

#define fmpl_cir            u_cir.fmpl_cir
#define fmpl_cir_int        u_cir.s_cir.fmpl_cir_int
#define fmpl_cir_frac       u_cir.s_cir.fmpl_cir_frac

#define fmpl_pir_eir        u_pir_eir.fmpl_pir_eir
#define fmpl_pir_eir_int    u_pir_eir.s_pir_eir.fmpl_pir_eir_int
#define fmpl_pir_eir_frac   u_pir_eir.s_pir_eir.fmpl_pir_eir_frac

/*
 * Key generator
 */

/* General configuration registers */

#define FMKG_GCR                    0x000    /* General configuration */
#define FMKG_EISR                   0x00C    /* Error event register */
#define FMKG_EIMR                   0x010    /* Error mask register */
#define FMKG_SEISR                  0x01C    /* Scheme error event register */
#define FMKG_SEIMR                  0x020    /* Scheme error mask */
#define FMKG_TPC                    0x028    /* Total packet count */
#define FMKG_SERC                   0x02C    /* Soft error capture */
#define FMKG_FDO                    0x040    /* Frame data offset */
#define FMKG_GDVR0                  0x044    /* Global default value 0 */
#define FMKG_GDVR1                  0x048    /* Global default value 1 */
#define FMKG_IFR                    0x064    /* Force error event */

/* General configuration */

#define FMKG_GCR_EN                 0x80000000    /* Enable keygen */
#define FMKG_GCR_NIA                0x00FFFFFF    /* Default NIA */

/* Error event */

#define FMKG_EISR_DECC              0x80000000    /* Double-bit ECC error */
#define FMKG_EISR_KSO               0x40000000    /* Key size overflow */

/* Global keygen status register */

#define FMKG_GSR_BSY                0x80000000    /* Keygen busy indication */

/* Soft error capture */

#define FMKG_SERC_CAP               0x80000000    /* Capture */
#define FMKG_SERC_CNT               0x00FF0000    /* Soft error count */
#define FMKG_SERC_ADDR              0x0000FFFF    /* ECC error memory address */

/* Frame data offset register */

#define FMKG_FDOR_OFF               0x000000FF    /* Data extraction offset */

/* Action register */

#define FMKG_AR_GO                  0x80000000    /* Activate access */
#define FMKG_AR_RW                  0x40000000    /* Access is read/write */
#define FMKG_AR_ER                  0x20000000    /* Access error indication */
#define FMKG_AR_SEL                 0x03000000    /* Access selector */
#define FMKG_AR_NUM                 0x001F0000    /* Access offset */
#define FMKG_AR_WSEL                0x0000FF00    /* Word select */
#define FMKG_AR_PORTSEL             0x0000003F    /* Port ID */

#define FMKG_AR_READ                0x40000000
#define FMKG_AR_WRITE               0x00000000

#define FMKG_SEL_SNUM               0x00000000    /* Scheme number */
#define FMKG_SEL_CPG                0x01000000    /* Classification plan grp */
#define FMKG_SEL_PE                 0x02000000    /* Port entry */

#define FMKG_NUM(x)                 (((x) << 16) & FMKG_AR_NUM)
#define FMKG_WSEL(x)                (((x) << 8) & FMKG_AR_WSEL)

#define FMKG_WSEL_SE_SPC            0x00004000
#define FMKG_WSEL_PE_CPP            0x00004000
#define FMKG_WSEL_PE_SP             0x00008000

/* Scheme configuration RAM registers */

#define FMKG_SE_MODE                0x100    /* MODE */
#define FMKG_SE_EKFC                0x104    /* Extract known fields command */
#define FMKG_SE_EKDV                0x108    /* Extract known default value */
#define FMKG_SE_BMCH                0x10C    /* Bit mask command high */
#define FMKG_SE_BMCL                0x110    /* Bit mask command low */
#define FMKG_SE_FQB                 0x114    /* Frame queue base */
#define FMKG_SE_HC                  0x118    /* Hash command */
#define FMKG_SE_PPC                 0x11C    /* Policer profile command */
#define FMKG_SE_GEC0                0x120    /* Generic extract cmd 0 */
#define FMKG_SE_GEC1                0x124    /* Generic extract cmd 1 */
#define FMKG_SE_GEC2                0x128    /* Generic extract cmd 2 */
#define FMKG_SE_GEC3                0x12C    /* Generic extract cmd 3 */
#define FMKG_SE_GEC4                0x130    /* Generic extract cmd 4 */
#define FMKG_SE_GEC5                0x134    /* Generic extract cmd 5 */
#define FMKG_SE_GEC6                0x138    /* Generic extract cmd 6 */
#define FMKG_SE_GEC7                0x13C    /* Generic extract cmd 7 */
#define FMKG_SE_SPC                 0x140    /* Scheme entry pkt counter */
#define FMKG_SE_DV0                 0x144    /* Scheme entry default val 0 */
#define FMKG_SE_DV1                 0x148    /* Scheme entry default val 1 */
#define FMKG_SE_CCBS                0x14C    /* Scheme coarse class bit select */
#define FMKG_SE_MV                  0x150    /* Match entry vector */

/* MODE register */

#define FMKG_SE_MODE_SI             0x80000000 /* Scheme init */
#define FMKG_SE_MODE_PL             0x40000000 /* Policer type */
#define FMKG_SE_MODE_CCOB           0x0F000000 /* CC offset base */
#define FMKG_SE_MODE_NIA            0x00FFFFFF /* NIA */

#define FMKG_MODE_CCOB(x)           (((x) << 24) FMKG_SE_MODE_CCOB)

/* Extract known fields */

#define FMKG_SE_EKFC_PORTID         0x80000000 /* Port ID */
#define FMKG_SE_EKFC_MACDST         0x40000000 /* Destination MAC addr */
#define FMKG_SE_EKFC_MACSRC         0x20000000 /* Source MAC addr */
#define FMKG_SE_EKFC_VLANTCI1       0x10000000 /* VLAN TCI 1 */
#define FMKG_SE_EKFC_VLANTCIN       0x08000000 /* VLAN TCI N */
#define FMKG_SE_EKFC_ETYPE          0x04000000 /* ethernet frame type */
#define FMKG_SE_EKFC_PPPSID         0x02000000 /* PPPoE session ID */
#define FMKG_SE_EKFC_PPPPID         0x01000000 /* PPPoE protocol ID */
#define FMKG_SE_EKFC_MPLSL1         0x00800000 /* MPLS layer 1 */
#define FMKG_SE_EKFC_MPLSL2         0x00400000 /* MPLS layer 2 */
#define FMKG_SE_EKFC_MPLSLN         0x00200000 /* MPLS layer N */
#define FMKG_SE_EKFC_IPSRC1         0x00100000 /* IP source 1 */
#define FMKG_SE_EKFC_IPDST1         0x00080000 /* IP destination 1 */
#define FMKG_SE_EKFC_IPTYPE1        0x00040000 /* IP type 1 */
#define FMKG_SE_EKFC_IPTOS1         0x00020000 /* IP TOS/TC 1 */
#define FMKG_SE_EKFC_IP6FL1         0x00010000 /* IPv6 flow label 1 */
#define FMKG_SE_EKFC_IPSRCN         0x00008000 /* IP source N */
#define FMKG_SE_EKFC_IPDSTN         0x00004000 /* IP destination N */
#define FMKG_SE_EKFC_IPTYPEN        0x00002000 /* IP type N */
#define FMKG_SE_EKFC_IPTOSN         0x00001000 /* IP TOS/TC N */
#define FMKG_SE_EKFC_IP6FLN         0x00000800 /* IPv6 flow label N */
#define FMKG_SE_EKFC_GRETYPE        0x00000400 /* GRE protocol type */
#define FMKG_SE_EKFC_IPSECSPI       0x00000200 /* IPSec SPI */
#define FMKG_SE_EKFC_IPSECNH        0x00000100 /* IPSec next header */
#define FMKG_SE_EKFC_L4PSRC         0x00000004 /* TCP/UDP/SCTP/DCCP source port */
#define FMKG_SE_EKFC_L4PDST         0x00000002 /* TCP/UDP/SCTP/DCCP dst. port */
#define FMKG_SE_EKFC_TFLG           0x00000001 /* TCP flags */

/* Extract known default value */

#define FMKG_SE_EKDV_MACADV         0xC0000000 /* MAC address */
#define FMKG_SE_EKDV_VLANTCIDV      0x30000000 /* VLANTCI */
#define FMKG_SE_EKDV_ETYPEDV        0x0C000000 /* ETYPE */
#define FMKG_SE_EKDV_PPPSIDDV       0x03000000 /* PPPoE session */
#define FMKG_SE_EKDV_PPPPIDDV       0x00C00000 /* PPPoE protocol */
#define FMKG_SE_EKDV_MPLSLDV        0x00300000 /* MPLS label */
#define FMKG_SE_EKDV_IPADV          0x000C0000 /* IP address */
#define FMKG_SE_EKDV_PTYPEDV        0x00030000 /* IP protocol type */
#define FMKG_SE_EKDV_IPTOSDV        0x0000C000 /* IP TOS/TC */
#define FMKG_SE_EKDV_IP6FLDV        0x00003000 /* IPv6 flow label */
#define FMKG_SE_EKDV_IPSECSPIDV     0x00000C00 /* IPSec SPI */
#define FMKG_SE_EKDV_L4PDV          0x00000300 /* Layer 4 port  */
#define FMKG_SE_EKDV_TGLGDV         0x000000C0 /* TCP flag */

#define FMKG_DV_GDV0                0x00000000 /* Use global DV0 */
#define FMKG_DV_GDV1                0x00000001 /* Use global DV1 */
#define FMKG_DV_SEDV0               0x00000002 /* Use SE DV0 */
#define FMKG_DV_SEDV1               0x00000003 /* Use SE DV1 */

#define FMKG_EKDV_GLOBAL0           0x00000000
#define FMKG_EKDV_GLOBAL1           0x55555550
#define FMKG_EKDV_SCHEME0           0xAAAAAAA0
#define FMKG_EKDV_SCHEME1           0xFFFFFFF0

/* Scheme bit mask control high */

#define FMKG_SE_BMCH_MCS0           0xFC000000 /* Mask command sel 0 */
#define FMKG_SE_BMCH_MCS1           0x03F00000 /* Mask command sel 1 */
#define FMKG_SE_BMCH_MO0            0x000F0000 /* Mask offset 0 */
#define FMKG_SE_BMCH_MCS2           0x0000FC00 /* Mask command sel 2 */
#define FMKG_SE_BMCH_MCS3           0x000003F0 /* Mask command sel 3 */
#define FMKG_SE_BMCH_MO1            0x0000000F /* Mask offset 1 */

/* Scheme bit mask control low */

#define FMKG_SE_BMCL_BM0            0xFF000000 /* Bit mask 0 */
#define FMKG_SE_BMCL_BM1            0x00FF0000 /* Bit mask 1 */
#define FMKG_SE_BMCL_BM2            0x0000FF00 /* Bit mask 2 */
#define FMKG_SE_BMCL_BM3            0x000000FF /* Bit mask 3 */

/* Frame queue base */

#define FMKG_SE_FQB_M02             0xF0000000 /* Mask offset 2 */
#define FMKG_SE_FQB_MO3             0x0F000000 /* Mask offser 3 */
#define FMKG_SE_FQB_FQBASE          0x00FFFFFF /* frame queue base */

/* Hash configuration */

#define FMKG_SE_HC_HSHIFT1          0x3F000000 /* Hash shift right */
#define FMKG_SE_HC_HMASK            0x00FFFFFF /* hash mask */

/* Policer profile command */

#define FMKG_SE_PPC_PPSH            0x80000000 /* Profile shift high */
#define FMKG_SE_PPC_PPMASK          0x00FF0000 /* Profile mask */
#define FMKG_SE_PPC_PPSL            0x0000F000 /* Profile shift low */
#define FMKG_SE_PPC_PPBASE          0x000000FF /* Profile base */

/* Generic extract command */

#define FMKG_SE_GEC_V               0x80000000 /* Valid */
#define FMKG_SE_GEC_DV              0x60000000 /* Default value */
#define FMKG_SE_GEC_SIZE            0x1F000000 /* rotate/size */
#define FMKG_SE_GEC_MASK            0x00FF0000 /* Bit mask */
#define FMKG_SE_GEC_TYPE            0x00008000 /* Command type */
#define FMKG_SE_GEC_HT              0x00007F00 /* Header type */
#define FMKG_SE_GEC_EO              0x000000FF /* Extract offset */

#define FMKG_GEC_TYPE_GEC           0x00000000 /* Generic extract command */
#define FMKG_GEC_TYPE_ORC           0x00008000 /* Or extract command */

#define FMKG_HT(x)                  (((x) << 8) & FMKG_SE_GEC_HT)

#define FMKG_HT_SHIM1               0x70
#define FMKG_HT_DEFAULT             0x10 /* Default value */
#define FMKG_HT_PR_0_16             0x20 /* Parse result first 16 bytes */
#define FMKG_HT_PR_16_32            0x30 /* Parse result second 16 bytes */
#define FMKG_HT_SOF                 0x40 /* Start of frame */
#define FMKG_HT_SHIM2               0x71
#define FMKG_HT_SHIM3               0x72
#define FMKG_HT_IP_PID              0x72 /* IP protocol ID */
#define FMKG_HT_ETH_V               0x03 /* Ethernet, validated */
#define FMKG_HT_ETH_NV              0x73 /* Ethernet, not validated */
#define FMKG_HT_SNAP_V              0x04 /* SNAP, validated */
#define FMKG_HT_SNAP_NV             0x74 /* SNAP, not validated */
#define FMKG_HT_VTCI1_V             0x05 /* VLAN TCI1, validated */
#define FMKG_HT_VTCI1_NV            0x75 /* VLAN TCI1, not validated */
#define FMKG_HT_VTCIN_V             0x05 /* VLAN TCIN, validated */
#define FMKG_HT_VTCIN_NV            0x75 /* VLAN TCIN, not validated */
#define FMKG_HT_ETYPE_V             0x07 /* Ethertype, validated */
#define FMKG_HT_ETYPE_NV            0x77 /* Ethertype, not validated */
#define FMKG_HT_PPPOE_V             0x08 /* PPPOE, validated */
#define FMKG_HT_PPPOE_N             0x78 /* PPPOE, not validated */
#define FMKG_HT_MPLS1_V             0x09 /* MPLS1, validated */
#define FMKG_HT_MPLS1_NV            0x79 /* MPLS1, not validated */
#define FMKG_HT_MPLS2_V             0x19 /* MPLS2, validated */
#define FMKG_HT_MPLS3_V             0x19 /* MPLS3, validated */
#define FMKG_HT_MPLSN_V             0x0A /* MPLSN, validated */
#define FMKG_HT_MPLSN_NV            0x7A /* MPLSN, not validated */
#define FMKG_HT_IPV4                0x0B /* IPv4, validated */
#define FMKG_HT_IPV6                0x1B /* IPv4, validated */
#define FMKG_HT_IPO_NV              0x7B /* IP other, not validated */
#define FMKG_HT_IPV4_2_V            0x0C /* IPV4 2, validated */
#define FMKG_HT_IPV6_2_V            0x1C /* IPV6 2, validated */
#define FMKG_HT_MINENCAP_V          0x2C /* Min encapsulation, validated */
#define FMKG_HT_IPO2_NV             0x7C /* IP other 2, not validated */
#define FMKG_HT_GRE_V               0x0D /* GRE, validated */
#define FMKG_HT_GRE_NV              0x7D /* GRE, not validated */
#define FMKG_HT_TCP_V               0x0E /* TCP, validated */
#define FMKG_HT_UDP_V               0x1E /* UDP, validated */
#define FMKG_HT_IPSECAH_V           0x2E /* IPSec AH, validated */
#define FMKG_HT_SCTP_V              0x3E /* SCTP, validated */
#define FMKG_HT_DCCP_V              0x4E /* DCCP, validated */
#define FMKG_HT_IPSECESP_V          0x6E /* IPSec ESP, validated */
#define FMKG_HT_L4O_NV              0x7E /* L4 other, not validated */
#define FMKG_HT_NXTHDRO_NV          0x7F /* NXTHDRO, not validated */

/* Classification plan access */

#define FMKG_CPE0                   0x100    /* Classification plan entry 0 */
#define FMKG_CPE1                   0x104    /* Classification plan entry 1 */
#define FMKG_CPE2                   0x108    /* Classification plan entry 2 */
#define FMKG_CPE3                   0x10C    /* Classification plan entry 3 */
#define FMKG_CPE4                   0x110    /* Classification plan entry 4 */
#define FMKG_CPE5                   0x114    /* Classification plan entry 5 */
#define FMKG_CPE6                   0x118    /* Classification plan entry 6 */
#define FMKG_CPE7                   0x11C    /* Classification plan entry 7 */

/* Port partition configuration */

#define FMKG_SE_SP                  0x100    /* Port entry scheme partition */
#define FMKG_SE_CPP                 0x104    /* Port entry class. plan partition */

/* Classification plan partition */

#define FMKG_CPP_CPGBASE            0x0000001F
#define FMKG_CPP_CPGMASK            0x001F0000

#define FMKG_CPGBASE(x)             ((x) & FMKG_CPP_CPGBASE)
#define FMKG_CPGMASK(x)             (((x) << 16) & FMKG_CPP_CPGBASE)

/* Indirect access register */

#define FMKG_AR                     0x1FC    /* Keygen action register */

/*
 * The hardware supports a total of 32 schemes and
 * 16 classification plans
 */

#define FMAN_SCHEME_CNT             32
#define FMAN_CPLAN_CNT              16
#define FMAN_CPE_CNT                8

typedef struct fman_kg_scheme
    {
    UINT32        fmks_mode;
    UINT32        fmks_ekfc;
    UINT32        fmks_ekdv;
    UINT32        fmks_bmch;
    UINT32        fmks_bmcl;
    UINT32        fmks_fqb;
    UINT32        fmks_hc;
    UINT32        fmks_ppc;
    UINT32        fmks_gec0;
    UINT32        fmks_gec1;
    UINT32        fmks_gec2;
    UINT32        fmks_gec3;
    UINT32        fmks_gec4;
    UINT32        fmks_gec5;
    UINT32        fmks_gec6;
    UINT32        fmks_gec7;
    UINT32        fmks_spc;
    UINT32        fmks_dv0;
    UINT32        fmks_dv1;
    UINT32        fmks_ccbs;
    UINT32        fmks_mv;
    } FMAN_KG_SCHEME;

typedef struct fman_kg_cplan
    {
    UINT32 fmkp_cpe[FMAN_CPE_CNT];
    } FMAN_KG_CPLAN;

/*
 * DMA
 */

#define FMDM_SR                     0x000    /* Status register */
#define FMDM_MR                     0x004    /* Mode register */
#define FMDM_TR                     0x008    /* Bus threshold */
#define FMDM_HY                     0x00C    /* Hysteresis */
#define FMDM_SETR                   0x010    /* SOS emergency threshold */
#define FMDM_TAH                    0x014    /* xfer bus address high */
#define FMDM_TAL                    0x018    /* xfer bus address low */
#define FMDM_TCID                   0x01C    /* xfer bus comm. ID */
#define FMDM_RA                     0x020    /* bus internal RAM addr */
#define FMDM_RD                     0x024    /* bus internal RAM data */
#define FMDM_DCR                    0x054    /* Debug counter */
#define FMDM_EMSR                   0x058    /* Emergency smoother */
#define FMDM_PLR0                   0x060    /* PartID/LIODN mapping 0 */
#define FMDM_PLR31                  0x0DC    /* PartID/LIODN mapping 31 */

/* Status register */

#define FMDM_SR_SPD_FCC             0x00100000    /* Single port data EFF, Fman */
#define FMDM_SR_DPD_FCC             0x00200000    /* Dual port data ECC, Fman */
#define FMDM_SR_DPD_SCC             0x00400000    /* Dual port data ECC, system */
#define FMDM_SR_DPX_FCC             0x00800000    /* Dual port ext. add ECC, Fman */
#define FMDM_SR_DPX_SCC             0x01000000    /* Dual port ext. add ECC, system */
#define FMDM_SR_WRB_FCC             0x02000000    /* Write buffer ECC error, Fman */
#define FMDM_SR_WRB_SCC             0x04000000    /* Write buffer ECC error, system */
#define FMDM_SR_RDB_ECC             0x04000000    /* Read buffer ECC error */
#define FMDM_SR_BER                 0x08000000    /* Bus error event */
#define FMDM_SR_CMDQNE              0x10000000    /* Command queue not empty */

/* Mode register */

#define FMDM_MR_AID                 0x00000010    /* AID mode */
#define FMDM_MR_ECCMSK              0x00000020    /* Mask ECC errors */
#define FMDM_MR_BMIEMR              0x00000040    /* BMI emergency */
#define FMDM_MR_DBCCNT              0x00000380    /* Debug count signal */
#define FMDM_MR_PROT2               0x00000400    /* Bus protection type */
#define FMDM_MR_PROT0               0x00001000    /* Bus protection priv */
#define FMDM_MR_EBEME               0x00030000    /* External bus priority */
#define FMDM_MR_ERWEEME             0x00040000    /* Set emerg on Fman write piort */
#define FMDM_MR_EERDEME             0x00080000    /* Set emerg on Fman read port */
#define FMDM_MR_EBMSK               0x00100000    /* Mask external bus errors */
#define FMDM_MR_BERMSK              0x00200000    /* Mask bus errors */
#define FMDM_MR_ERWRMSK             0x00400000    /* Mask emerg on Fman write port */
#define FMDM_MR_ERRDMSK             0x00800000    /* Mask emerg on Fman read port */
#define FMDM_MR_AXIDBG              0x0F000000    /* Debug beats */
#define FMDM_MR_SBER                0x10000000    /* Stop ad bus error */
#define FMDM_MR_AIDOVR              0x20000000    /* AID override */
#define FMDM_MR_CHOVR               0x40000000    /* Cache override */

/*
 * Frame processor manager
 */

#define FMFP_TNC                    0x000    /* Task num control */
#define FMFP_PRC                    0x004    /* Port ID control */
#define FMFP_FLC                    0x00C    /* Flush control */
#define FMFP_DIST1                  0x010    /* Dispatch 1 thresholds */
#define FMFP_DIST2                  0x014    /* Dispatch 2 thresholds */
#define FMFP_EPI                    0x018    /* Error pending interrupts */
#define FMFP_RIE                    0x01C    /* Rams interrupt enable */
#define FMFP_FISR0                  0x020    /* Fman controller event */
#define FMFP_FISR1                  0x024    /* Fman controller event */
#define FMFP_FISR2                  0x028    /* Fman controller event */
#define FMFP_FISR3                  0x02C    /* Fman controller event */
#define FMFP_FIMR0                  0x040    /* Fman controller mask */
#define FMFP_FIMR1                  0x044    /* Fman controller mask */
#define FMFP_FIMR2                  0x048    /* Fman controller mask */
#define FMFP_FIMR3                  0x04C    /* Fman controller mask */
#define FMFP_TSC1                   0x060    /* Timestamp control 1 */
#define FMFP_TSC2                   0x064    /* Timestamp control 2 */
#define FMFP_TSP                    0x068    /* Time stamp */
#define FMFP_TSF                    0x06C    /* Time stamp fraction */
#define FMFP_RCR                    0x070    /* Rams control and event */
#define FMFP_DRD0                   0x080    /* Data_ram data */
#define FMFP_DRD1                   0x084    /* Data_ram data */
#define FMFP_DRD2                   0x088    /* Data_ram data */
#define FMFP_DRD3                   0x08C    /* Data_ram data */
#define FMFP_DRA                    0x0C0    /* Data RAM access */
#define FMFP_IP_REV1                0x0C4    /* IP revision 1 */
#define FMFP_IP_REV2                0x0C8    /* IP revision 2 */
#define FMFP_RSTC                   0x0CC    /* Fman reset control */
#define FMFP_CLDC                   0x0D0    /* Classifier debug control */
#define FMFP_NPI                    0x0D4    /* Normal pending interrupts */
#define FMFP_EE                     0x0DC    /* FPM event and enable */
#define FMFP_CEV0                   0x0E0    /* CPU event */
#define FMFP_CEV1                   0x0E4    /* CPU event */
#define FMFP_CEV2                   0x0E8    /* CPU event */
#define FMFP_CEV3                   0x0EC    /* CPU event */
#define FMFP_PS0                    0x100    /* Port ID status */
#define FMFP_PS48                   0x1C0    /* Port ID status */
#define FMFP_CLFABC                 0x200    /* Classifier flow AB control */
#define FMFP_CLFCC                  0x204    /* Classifier flow C control */
#define FMFP_CLFAVAL                0x208    /* Classifier flow A value */
#define FMFP_CLFBVAL                0x20C    /* Classifier flow B value */
#define FMFP_CLFCVAL                0x210    /* Classifier flow C value */
#define FMFP_CLFAMSK                0x214    /* Classifier A mask */
#define FMFP_CLFBMSK                0x218    /* Classifier B mask */
#define FMFP_CLFCMSK                0x21C    /* Classifier C mask */
#define FMFP_CLFAMATCH              0x220    /* Classifier A match */
#define FMFP_CLFBMATCH              0x224    /* Classifier B match */
#define FMFP_CLFCMATCH              0x228    /* Classifier C match */

/*
The FPM allocates and de-allocates TNUMs automatically.
The only registers required to be configured are FMFP_FLC, FMFP_DIST1, FMFP_DIST2, FM_RIE,
FMFP_TSC1, FMFP_TSC2, FM_RCR, FMFP_EE.
Other registers are for debug or might be used by FMan controllers.
*/

/* Flush control */

#define FMFP_FLC_DISPLIM            0x1F000000    /* Dispatch limit */

#define FMFP_FDISPLIM(x)            (((x) << 24) & FMFP_FLC_DISPLIM)

/* Dispatch limit 1 */

#define FMFP_DIST1_BMITHR           0x000000FF    /* BMI queue threshold */
#define FMFP_DIST1_POLTHR           0x0000FF00    /* policer queue threshold */
#define FMFP_DIST1_KGNTHR           0x00FF0000    /* keygen queue threshold */
#define FMFP_DIST1_PARTHR           0xFF000000    /* parser queue threshold */

/* Dispatch limit 2 */

#define FMFP_DIST2_QDEQTHR          0x000000FF    /* QMI dequeue threshold */
#define FMFP_DIST2_FMC2THR          0x0000FF00    /* FMan ctlr 2 threshold */
#define FMFP_DIST2_FMC1THR          0x00FF0000    /* Fman ctlr 1 threshold */
#define FMFP_DIST2_QENQTHR          0xFF000000    /* QMI enqueue threshold */

#define FMFP_DIST_LIM0(x)           ((x) & 0xFF)
#define FMFP_DIST_LIM1(x)           (((x) < 8) & 0xFF00)
#define FMFP_DIST_LIM2(x)           (((x) < 16) & 0xFF0000)
#define FMFP_DIST_LIM3(x)           (((x) < 24) & 0xFF000000)

/* Timestamp control 1 */

#define FMFP_TSC1_TEN               0x80000000    /* Timestamp enable */
#define FMFP_TSC1_TSPV              0x0000FFFF    /* Timestamp prescale value */

/* Timestamp control 2 */

#define FMFP_TSC2_TSIV_INT          0x00FF0000    /* TS increment int bits */
#define FMFP_TSC2_TSIV_FRAC         0x0000FFFF    /* TS increment fraction bits */

#define FMFP_TSIV_INT(x)            (((x) << 16) & FMFP_TSC2_TSIV_INT)

/* Rams control and event register */

#define FMFP_RCR_FEE                0x80000000    /* FMAN RAM ECC enable */
#define FMFP_RCR_IEE                0x40000000    /* Instruction ECC enable */
#define FMFP_RCR_MET                0x20000000    /* MURAM ECC test enable */
#define FMFP_RCR_IET                0x10000000    /* Inst. RAM ECC test enable */
#define FMFP_RCR_SFE                0x08000000    /* Fman RAM ECC source */
#define FMFP_RCR_MDEC               0x00008000    /* MURAM double ECC error */
#define FMFP_RCR_IDEC               0x00004000    /* Inst. double ECC error */

/* IP Block revision 1 */

#define FMAN_IP_ID                  0xFFFF0000    /* IP identifier */
#define FMAN_IP_MJ                  0x0000FF00    /* Major revision */
#define FMAN_IP_MN                  0x000000FF    /* Minor revision */

#define FMAN_ID(x)                  (((x) & FMAN_IP_ID) >> 16)
#define FMAN_MJ(x)                  (((x) & FMAN_IP_MJ) >> 8)
#define FMAN_MN(x)                  ((x) & FMAN_IP_MN)

#define FMAN_REVISION2              0x02        /* P4080 */
#define FMAN_REVISION3              0x03        /* P2040, P3041, P5020 */
#define FMAN_REVISION4              0x04        /* P1023 */
#define FMAN_REVISION6              0x06        /* Fman V3H/V3L (T4240) */

#define FMAN_MINOR_0                0x00        /* Fman V3H == 1 */
#define FMAN_MINOR_1                0x01        /* Fman V3L == 0 */
#define FMAN_MINOR_3                0x03        /* T4240 Rev2 is 3 */
#define FMAN_MINOR_4                0x04        /* T1024 Rev is 4 */

/* Reset control */

#define FMFP_RSTC_RFM               0x80000000    /* Reset entire Fman */
#define FMFP_RSTC_R1G0              0x40000000    /* Reset 1Gb MAC 0 */
#define FMFP_RSTC_R1G1              0x20000000    /* Reset 1Gb MAC 1 */
#define FMFP_RSTC_R1G2              0x08000000    /* Reset 1Gb MAC 2 */
#define FMFP_RSTC_R1G3              0x04000000    /* Reset 1Gb MAC 3 */
#define FMFP_RSTC_R10G              0x02000000    /* Reset 10Gb MAC */
#define FMFP_RSTC_R1G4              0x01000000    /* Reset 1Gb MAC 4 */
#define FMFP_RSTC_R1G5              0x00800000    /* Reset 1Gb MAC 5 */
#define FMFP_RSTC_R1G6              0x00400000    /* Reset 1Gb MAC 6 */
#define FMFP_RSTC_R1G7              0x00200000    /* Reset 1Gb MAC 7 */

/* Event and enable register */

#define FMFP_EE_DER                 0x00000001    /* DMA error behavior */
#define FMFP_EE_CER                 0x00000002    /* Catastrophic error */
#define FMFP_EE_UEC                 0x00000004    /* Unrecoverable error */
#define FMFP_EE_EHM                 0x00000008    /* External halt mask */
#define FMFP_EE_SECC_EN             0x00002000    /* Single ECC error */
#define FMFP_EE_STL_EN              0x00004000    /* Stall of task */
#define FMFP_EE_DECC_EN             0x00008000    /* Double ECC error */
#define FMFP_EE_RFM                 0x00010000    /* Release FMAN halt */
#define FMFP_EE_SECC                0x20000000    /* Single ECC error */
#define FMFP_EE_STL                 0x40000000    /* Stall of task */
#define FMFP_EE_DECC                0x80000000    /* Double ECC error */

/* Timestamp frequency in Hz */

#define FMAN_TS_FREQ                256000000

/* IRAM section, for loading microcode */

#define FMIR_IADD                   0x000    /* IRAM instruction address */
#define FMIR_IDATA                  0x004    /* IRAM instruction data */
#define FMIR_ITCFG                  0x008    /* Timing configuration */
#define FMIR_IREADY                 0x00C    /* IRAM ready */

/* Instruction address register */

#define FMIR_IADD_AIE               0x80000000    /* Enable */

/* IREADY register */

#define FMIR_IREADY_READY           0x80000000    /* Patch is ready  */

/*
 * Internal frame context structure (added to frames by BMI)
 */

typedef struct fman_ifc
    {
    volatile QPORTAL_FDESC  fman_ifc_fd;        /* Frame descriptor */
    volatile UINT32         fman_ifc_ad[2];     /* Action descriptor */
    volatile UINT32         fman_ifc_ccbase;    /* Coarse class. base */
    volatile UINT8          fman_ifc_keysz;     /* Keygen key size */
    volatile UINT8          fman_ifc_hpnia[3];  /* hard parser NIA */
    volatile FMAN_PR        fman_ifc_pr;        /* Parser result */
    volatile UINT32         fman_ifc_ts[2];     /* Timestamp */
    volatile UINT64         fman_ifc_hash;      /* hash */
    volatile UINT8          fman_ifc_key[56];   /* key */
    volatile UINT32         fman_ifc_rsvd[2];   /* reserved */
    volatile UINT32         fman_ifc_dbg[28];   /* debug */
    } FMAN_IFC;

/*
 * Frame descriptor status fields
 */

/* RX FD status */

#define FMAN_RXFS_DCL4C             0x10000000 /* Didn't check L4 csum  */
#define FMAN_RXFS_UFD               0x04000000 /* Unsupported fd format */
#define FMAN_RXFS_LGE               0x02000000 /* Large frame error (giant) */
#define FMAN_RXFS_DME               0x01000000 /* DMA error */
#define FMAN_RXFS_FPE               0x00080000 /* Physical error */
#define FMAN_RXFS_FSE               0x00040000 /* Frame size error */
#define FMAN_RXFS_DIS               0x00020000 /* Discarded */
#define FMAN_RXFS_EOF               0x00008000 /* Key extract out of frame */
#define FMAN_RXFS_NSS               0x00004000 /* No scheme selected */
#define FMAN_RXFS_KSO               0x00002000 /* Key size overflow */
#define FMAN_RXFS_FCL               0x00000C00 /* Frame color */
#define FMAN_RXFS_IPP               0x00000200 /* Illegal policer profile */
#define FMAN_RXFS_FLM               0x00000100 /* Frame length mismatch */
#define FMAN_RXFS_PTE               0x00000080 /* Parser timeout exceeded */
#define FMAN_RXFS_ISP               0x00000040 /* Invalid soft parse selection */
#define FMAN_RXFS_PHE               0x00000020 /* Parser header error */
#define FMAN_RXFS_FRDR              0x00000010 /* Frame drop */

#define FMAN_RXFS_ERRS              (FMAN_RXFS_DME | FMAN_RXFS_FPE | \
                                     FMAN_RXFS_FSE |  FMAN_RXFS_DIS| \
                                     FMAN_RXFS_EOF | FMAN_RXFS_NSS | \
                                     FMAN_RXFS_IPP | FMAN_RXFS_PTE | \
                                     FMAN_RXFS_ISP | FMAN_RXFS_PHE)

/* TX FD command */

#define FMAN_TXFC_FCO               0x80000000 /* FQ context override */
#define FMAN_TXFC_RPD               0x40000000 /* Read prepended data */
#define FMAN_TXFC_UPD               0x20000000 /* Update prepended data */
#define FMAN_TXFC_DTC               0x10000000 /* Do TCP checksum */
#define FMAN_TXFC_CFQ               0x00FFFFFF /* Confirmation frame queue */

/* TX FD confirmation status */

#define FMAN_TXFS_FCO               0x80000000 /* FQ context override */
#define FMAN_TXFS_RPD               0x40000000 /* Read prepended data */
#define FMAN_TXFS_UPD               0x20000000 /* Update prepended data */
#define FMAN_TXFS_DTC               0x10000000 /* Do TCP checksum */
#define FMAN_TXFS_UFD               0x04000000 /* Unsupported fd format */
#define FMAN_TXFS_LGE               0x02000000 /* Large frame error (giant) */
#define FMAN_TXFS_DME               0x01000000 /* DMA error */
#define FMAN_TXFS_CFQ               0x00FFFFFF /* Confirmation frame queue */

/*
 * Frame queue descriptor contextA fields.
 * With the Fman_v3 in the T4240 and similar devices, the contextA
 * fields used when creating a frame queue targeted at one of the
 * Fman direct connect portals has special meaning. The Fman can
 * decode the contextA fields from the frame queue descriptor and
 * use them to control certain Fman behavior. These are called
 * the A0, A1 and A2 fields. The contextA field is 64-bits in size.
 * The VxQorks qportalFqInit() API allows the caller to specify them
 * in terms of two 32-bit values (ctxAHi and ctxALo). We define the
 * A0, A1 and A2 fields here as two 32-bit register values for
 * compatibility with this API.
 */

/*
 * Fman ctxAHi fields
 */

#define FMAN_CAH_OVFQ               0x80000000    /* Override frame queue */
#define FMAN_CAH_ICMD               0x40000000    /* Invalidate FD[command] field */
#define FMAN_CAH_A1V                0x20000000    /* A1 field valid */
#define FMAN_CAH_A2V                0x10000000    /* A2 field valid */
#define FMAN_CAH_A0V                0x08000000    /* A0 field valid */
#define FMAN_CAH_B0V                0x04000000    /* B0 valid (ICAD) */
#define FMAN_CAH_OVOM               0x02000000    /* Override operational mode bits */
#define FMAN_CAH_A0                 0x00FF0000
#define FMAN_CAH_A1                 0x0000FFFF

#define FMAN_A0(x)                  (((x) << 16) & FMAN_CAH_A0)
#define FMAN_A1(x)                  ((x) & FMAN_CAH_A1)
/*
 * Fman ctxALo fields
 */

#define FMAN_CAL_A2                 0xFF000000

#define FMAN_A2(x)                  (((UINT8)(x) << 24) & FMAN_CAL_A2)

/* A0 definition for TX ports */

#define FMAN_A0_FQIDTYPE            0x80    /* FmanV3 only */
#define FMAN_A0_A0VV                0x80    /* P1023 only */
#define FMAN_A0_TXCT                0x40    /* TX confirmation type */
#define FMAN_A0_MCV                 0x10    /* MACsec command valid */
#define FMAN_A0_MACCMD              0x0F    /* MACsec command (secure chan select) */

/* A0 definition for offline ports */

#define FMAN_A0_PPID                0xFF    /* Policer profile ID */

/* A2 definition for TX ports */

#define FMAN_A2_EBD                 0x80    /* External buffer deallocation */
#define FMAN_A2_NL                  0x10    /* Not last (continuous mode */
#define FMAN_A2_VSPE                0x01    /* Virtual storage profile enable */

/*
 * A2 definition for offline port (includes above bits
 * plus the ones defined below)
 */

#define FMAN_A2_EBAD                0x40    /* External buffer allocation */
#define FMAN_A2_FWD                 0x20    /* Frame write disable */
#define FMAN_A2_CWD                 0x08    /* Context write disable */
#define FMAN_A2_NENQ                0x04    /* No ENQueue */

/* B0 definition for contextB field */

#define FMAN_B0_ASPID               0xFF000000 /* Absolute virtual storage profile ID */
#define FMAN_B0_FQID                0x00FFFFFF /* Frame queue ID */

#define FMAN_ASPID(x)               (((x) << 24) & FMAN_B0_ASPID)

/* Microcode structure definition */

typedef struct QE_FIRMWARE
    {
    struct qe_header
    {
    UINT32          qe_len;         /* Length of struct */
    UINT8           qe_magic[3];    /* 'Q', 'E', 'F' */
    UINT8           qe_vers;        /* version (1) */
    } qe_header;
    UINT8           qe_id[62];      /* Identifier string */
    UINT8           qe_split;       /* 0 = shared IRAM, 1 = split */
    UINT8           qe_count;       /* # of ucode structrs */
    struct qe_soc
    {
    UINT16          qe_model;       /* SOC model */
    UINT8           qe_major;       /* SOC rev major */
    UINT8           qe_minor;       /* SOC rev minor */
    } qe_soc;
    UINT8           qe_pad[4];
    UINT64          qe_extended_modes;  /* Extended modes */
    UINT32          qe_vtraps[8];       /* Virtual trap addrs */
    UINT8           qe_rsvd[4];
    struct qe_ucode
    {
    UINT8           qe_id[32];      /* Identifier string */
    UINT32          qe_traps[16];   /* Trap addrs, 0 == none */
    UINT32          qe_eccr;        /* ECCR reg value */
    UINT32          qe_iram_offset; /* IRAM code offset */
    UINT32          qe_count;       /* # of 32 bit words */
    UINT32          qe_code_offset; /* ucode offset */
    UINT8           qe_major;       /* ucode major */
    UINT8           qe_minor;       /* ucode minor */
    UINT8           qe_revision;    /* ucode rev */
    UINT8           qe_pad;
    UINT8           qe_rsvd[4];
    } qe_ucode[1];
    } QE_FIRMWARE;

/* Coarse classifier action descriptor structures */

typedef struct fman_ccad_ncr
    {
    volatile UINT8  ncr_type_dbg;  /* type/dbg */
    volatile UINT8  ncr_fqid_hi;   /* fqid */
    volatile UINT16 ncr_fqid_lo;   /* fqid */
    volatile UINT8  ncr_pp;        /* policer profile */
    volatile UINT8  ncr_rsvd0;
    volatile UINT16 ncr_rsvd1;
    volatile UINT32 ncr_nia;       /* next invoked action */
    volatile UINT32 ncr_rsvd2;
    } FMAN_CCAD_NCR;

#define FMAN_CCADNCR_TYPEDBG_DFAM   0x04 /* Debug flow A mark */
#define FMAN_CCADNCR_TYPEDBG_DFBM   0x02 /* Debug flow B mark */
#define FMAN_CCADNCR_TYPEDBG_DFCM   0x01 /* Debug flow C mark */

typedef struct fman_ccad_kcr
    {
    volatile UINT8      kcr_type_pd;   /* type/policer disable */
    volatile UINT8      kcr_rsvd0;
    volatile UINT16     kcr_rsvd1;
    volatile UINT32     kcr_rsvd2;
    volatile UINT32     kcr_nia;
    volatile UINT32     kcr_rsvd3;
    } FMAN_CCAD_KCR;

#define FMAN_CCADKCR_TYPEPD_PD      0x20 /* Policer disabled */

typedef struct fman_ccad_td
    {
    volatile UINT8      td_type_klen;  /* type/key length */
    volatile UINT8      td_ccadb_hi;   /* action descriptor base hi */
    volatile UINT16     td_ccadb_lo;   /* action descriptor base lo */
    volatile UINT8      td_mte;        /* match table entries */
    volatile UINT8      td_mtp_hi;     /* match table base (hi 7 bits) */
    volatile UINT16     td_mtp_lo;     /* match table base (low 16 bits) */
    volatile UINT8      td_opr;        /* parser result offset */
    volatile UINT8      td_offset;     /* offset of key from frame start */
    volatile UINT8      td_rsvd0;
    volatile UINT8      td_pcode;      /* parse code */
    volatile UINT32     td_gmask;      /* global mask */
    } FMAN_CCAD_TD;

#define FMAN_CCADTD_TYPEKLEN_TYPE       0xC0
#define FMAN_CCADTD_TYPEKLEN_KEYLEN     0x3F

/* Local mask bit */

#define FMAN_CCADTD_LM              0x80

/* Coarse classification action descriptor type codes */

#define FMAN_CCAD_TYPE_NCR          0x00 /* New classification result */
#define FMAN_CCAD_TYPE_TD           0x40 /* Table descriptor */
#define FMAN_CCAD_TYPE_KCR          0x80 /* Keep classification result */
#define FMAN_CCAD_TYPE_DISABLE      0xC0 /* For dynamic updates */

/* Table descriptor parse codes */

#define FMAN_CC_PC_ETHDST           0x00 /* Ethernet dst addr, 8 bytes */
#define FMAN_CC_PC_ETHSRC           0x01 /* Ethernet src addr, 8 bytes */
#define FMAN_CC_PC_ETYPE            0x02 /* Ethernet type, 2 bytes */
#define FMAN_CC_PC_VTCI1            0x03 /* VLAN TCI 1, 2 bytes */
#define FMAN_CC_PC_VTCIN            0x04 /* VLAN TCI N, 2 bytes */
#define FMAN_CC_PC_PPPOEPID         0x05 /* PPPOE PID, 2 bytes */
#define FMAN_CC_PC_MPLS             0x06 /* MPLS, 4 bytes */
#define FMAN_CC_PC_MPLSBN           0x07 /* Last MPLS, 4 bytes */
#define FMAN_CC_PC_IPV4DST          0x08 /* IPv4 dst, 4 bytes */
#define FMAN_CC_PC_IPV4TOS          0x09 /* IPv4 TOS, 1 byte */
#define FMAN_CC_PC_IPV4PROT         0x0A /* IPv4 protocol, 1 byte */
#define FMAN_CC_PC_IPV4SRC          0x0B /* IPv4 src, 4 bytes */
#define FMAN_CC_PC_IPV4SRCDST       0x0C /* IPv4 src + dst, 8 bytes */
#define FMAN_CC_PC_IPV6CLSFLW       0x0D /* IPv6 class/flow, 4 bytes */
#define FMAN_CC_PC_IPV6NXTHDR       0x0E /* IPv6 nexthdr, 1 byte */
#define FMAN_CC_PC_IPV6DST          0x0F /* IPv6 dst, 16 bytes */
#define FMAN_CC_PC_IPV6SRC          0x10 /* IPv6 src, 16 bytes */
#define FMAN_CC_PC_GREPROT          0x11 /* GRE protocol type, 2 bytes */
#define FMAN_CC_PC_MINPROTO         0x12 /* MinEnc protocol, 1 bytes */
#define FMAN_CC_PC_MINIPDST         0x13 /* MinEnc IP dst, 4 bytes */
#define FMAN_CC_PC_MINIPSRC         0x14 /* MinEnc IP src, 4 bytes */
#define FMAN_CC_PC_MINIPSRCDST      0x15 /* MinEnc IP src + dst, 8 bytes */
#define FMAN_CC_PC_TUNIP4DST        0x16 /* TunIPv4 dst, 4 bytes */
#define FMAN_CC_PC_TUNIP4TOS        0x17 /* TunIPv4 TOS, 1 bytes */
#define FMAN_CC_PC_TUNIP4PROT       0x18 /* TunIPv4 proto, 1 byte */
#define FMAN_CC_PC_TUNIP4SRC        0x19 /* TunIPv4 src, 4 bytes */
#define FMAN_CC_PC_TUNIP4SRCDST     0x1A /* TunIPv4 src + dst, 8 bytes */
#define FMAN_CC_PC_TUNIP6CLSFLW     0x1B /* TunIPv6 class/flow, 4 bytes */
#define FMAN_CC_PC_TUNIP6NXTHDR     0x1C /* TunIPv6 nexthdr, 1 byte */
#define FMAN_CC_PC_TUNIP6DST        0x1D /* TunIPv6 dst, 16 bytes */
#define FMAN_CC_PC_TUNIP6SRC        0x1E /* TunIPv6 src, 16 bytes */
#define FMAN_CC_PC_L4SRCPORT        0x1F /* TCP/UDP src port, 2 bytes */
#define FMAN_CC_PC_L4DDTPORT        0x20 /* TCP/UDP src port, 2 bytes */
#define FMAN_CC_PC_L4DSRCDSTORT     0x21 /* TCP/UDP src + dst port, 4 bytes */
#define FMAN_CC_PC_SHIM1            0x22 /* Shim1, use keylen in AD */
#define FMAN_CC_PC_SHIM2            0x23 /* Shim2, use keylen in AD */
#define FMAN_CC_PC_SHIM3            0x24 /* Shim3, use keylen in AD */
#define FMAN_CC_PC_GENPROFFGM1      0x25 /* Generic parse result offset 1, use keylen in AD */
#define FMAN_CC_PC_GENPROFFGM2      0x26 /* Generic parse result offset 2, use keylen in AD */
#define FMAN_CC_PC_GENOFF3          0x27 /* Generic 3, use keylen in AD */
#define FMAN_CC_PC_GENOFFGM4        0x28 /* Generic 4, use keylen in AD */
#define FMAN_CC_PC_IPV4TTL          0x29 /* IPv4 TTL > 1 */
#define FMAN_CC_PC_IPV6HL           0x2A /* IPv6 hop limit */
#define FMAN_CC_PC_GENOFFICGM5      0x2B /* Generic 5, use internal frame context */
#define FMAN_CC_PC_HASH             0x2C /* Hash key lookup */
#define FMAN_CC_PC_GENOFFICAM6      0x2D /* Generic 6, IFC lookup, age mask */

#define QORIQ_FMAN_NAME             "QorIQFman"
#define FMAN_TIMEOUT                10000

/*
 * The following structure is used by the coarse classifier API
 * and is not defined by hardware. The coarse classifier operates
 * using action descriptor structures, which are always 16 bytes,
 * at matching table structures, which vary in size. This structure
 * allows the caller to provide the largest possible keys, but the
 * actual matching table derived from the user-supplied data will
 * be different.
 */

#define FMAN_KEYLEN_CNT             56
#define FMAN_KEYCNT_CNT             256
#define FMAN_CC_CNT                 32

/* forward declaration */

struct fman_cc_config;

typedef struct fman_cc_key
    {
    UINT8                   fmcc_key[FMAN_KEYLEN_CNT];
    UINT8                   fmcc_mask[FMAN_KEYLEN_CNT];
    struct fman_cc_config * fmcc_chain; /* next classification stage */
    UINT32                  fmcc_fqid;  /* fqid for this key */
    UINT32                  fmcc_nia;   /* NIA for this key */
    } FMAN_CC_KEY;

typedef struct fman_cc_config
    {
    UINT8                   fmcc_pcode;     /* Parser code */
    UINT32                  fmcc_gmask;     /* global mask */
    UINT8                   fmcc_offset;    /* offset (for generic extract) */
    UINT8                   fmcc_ph_offset; /* parse header offset */
    UINT8                   fmcc_key_cnt;   /* number of keys */
    UINT8                   fmcc_key_len;   /* length of keys */
    UINT32                  fmcc_miss_fqid; /* default fqid  */
    UINT32                  fmcc_miss_nia;  /* default NIA */
    struct fman_cc_config * fmcc_miss_chain;/* next classification stage */
    BOOL                    fmcc_localmask; /* use local masks */
    FMAN_CC_KEY             fmcc_keys[FMAN_KEYCNT_CNT];
    } FMAN_CC_CONFIG;

/*
 * Number of bytes from the start of a received frame buffer
 * to the start of the frame data. This determines how many
 * bytes of the internal frame context is prepended to received
 * frames.
 *
 * We program the frame manager to return 128 bytes of the
 * internal frame context immediately before each frame. (This
 * includes everything except the frame descriptor, which we
 * end up getting when we dequeue the frame from the Qman
 * anyway.) We also insert two pad bytes between the IFC
 * and the start of the frame, in order to (hopefully)
 * align the frame payload on a longword boundary.
 *
 * The FMAN_PKT_DATA() macro returns a pointer to the start
 * of the frame data. FMAN_PKT_IFC() returns a pointer to the
 * start of the internal frame context. The fman_ifc_fd field
 * in the IFC is invalid and should not be referenced.
 */

#define FMAN_PKT_OFF                128
#define FMAN_PKT_ALIGN              2
#define FMAN_PKT_DATA(x)            ((char *)(x) + (FMAN_PKT_OFF + FMAN_PKT_ALIGN))
#define FMAN_PKT_IFC(x)             (FMAN_IFC *)((char *)(x) - 16)

/*
 * With newer chips, each Fman might have a different clock
 * frequency, so allow specification of the Fman unit when
 * calling the frequency get function.
 */

typedef UINT32 (*fmanFreqGetFunc)(int unit);

typedef struct fman_pr_sw_ssa
    {
    UINT16    fman_ssa_off[FMPR_HDR_CNT];
    } FMAN_PR_SW_SSA;

typedef struct fman_pr_sp_prog
    {
    UINT16      fman_off;
    UINT16      fman_size;
    UINT8       fman_header;
    char *      fman_code;
    } FMAN_PR_SP_PROG;

#define FMAN_POOL_CNT_P4080         8
#define FMAN_POOL_CNT_T4240         4

typedef struct fman_pool_info
    {
    int         fman_bpcnt;
    int         fman_bpsz[FMAN_POOL_CNT_P4080];
    UINT8       fman_bpid[FMAN_POOL_CNT_P4080];
    } FMAN_POOL_INFO;

typedef struct fman_drv_ctrl
    {
    VXB_DEV_ID          fmanDev;
    VXB_RESOURCE *      pRes;
    void *              fmanBar;
    void *              fmanHandle;
    void *              fmanBmBar[FMAN_PORTS]; /* BMI */
    void *              fmanQmBar[FMAN_PORTS]; /* QMI */
    void *              fmanPrBar[FMAN_PORTS]; /* parser */
    void *              fmanPrdBar;     /* parser direct memory access */
    void *              fmanPrgBar;     /* parser global config */
    void *              fmanPlBar;      /* policer */
    void *              fmanKgBar;      /* keygen */
    void *              fmanDmBar;      /* DMA */
    void *              fmanFpBar;      /* processing manager */
    void *              fmanIrBar;      /* instruction RAM */
    SEM_ID              fmanSem;
    int                 fmanCnt;
    FMAN_CC_CONFIG *    fmanCcCfg[FMAN_CC_CNT];
    UINT32              fmanMuRam;      /* Multi-user RAM */
    char *              fmanMuRamPtr;
    UINT32              fmanSpRam;      /* Soft parser RAM */
    char *              fmanSpRamPtr;
    FMAN_SP_LABEL       fmanSpLabels[FMPR_LABEL_CNT];
    int                 fmanSpLabelCnt;
    FMAN_PR_SW_SSA      fmanSpSsa[FMAN_PORTS];
    UINT32              fmanFpPeriod;
    BOOL                fmanSavedPrValid[FMAN_PORTS];
    FMAN_PR             fmanSavedPr[FMAN_PORTS];
    int                 fmanPoolCnt;
    UINT32              fmanRev;
    UINT32              unit;
    } FMAN_DRV_CTRL;

#define FMAN_BAR(p)             ((FMAN_DRV_CTRL *)(p))->fmanBar
#define FMAN_BM_BAR(p, i)       ((FMAN_DRV_CTRL *)(p))->fmanBmBar[i]
#define FMAN_QM_BAR(p, i)       ((FMAN_DRV_CTRL *)(p))->fmanQmBar[i]
#define FMAN_PR_BAR(p, i)       ((FMAN_DRV_CTRL *)(p))->fmanPrBar[i]
#define FMAN_PRD_BAR(p)         ((FMAN_DRV_CTRL *)(p))->fmanPrdBar
#define FMAN_PRG_BAR(p)         ((FMAN_DRV_CTRL *)(p))->fmanPrgBar
#define FMAN_PL_BAR(p)          ((FMAN_DRV_CTRL *)(p))->fmanPlBar
#define FMAN_KG_BAR(p)          ((FMAN_DRV_CTRL *)(p))->fmanKgBar
#define FMAN_DM_BAR(p)          ((FMAN_DRV_CTRL *)(p))->fmanDmBar
#define FMAN_FP_BAR(p)          ((FMAN_DRV_CTRL *)(p))->fmanFpBar
#define FMAN_IR_BAR(p)          ((FMAN_DRV_CTRL *)(p))->fmanIrBar
#define FMAN_HANDLE(p)          ((FMAN_DRV_CTRL *)(p))->fmanHandle

#define FMAN_BM_READ(pDev, port, addr)              \
        vxbRead32 (FMAN_HANDLE(pDev),               \
                   (UINT32 *)((char *)FMAN_BM_BAR(pDev, port) + addr))

#define FMAN_BM_WRITE(pDev, port, addr, data)       \
        vxbWrite32 (FMAN_HANDLE(pDev),              \
                    (UINT32 *)((char *)FMAN_BM_BAR(pDev, port) + addr), data)

#define FMAN_QM_READ(pDev, port, addr)              \
        vxbRead32 (FMAN_HANDLE(pDev),               \
                   (UINT32 *)((char *)FMAN_QM_BAR(pDev, port) + addr))

#define FMAN_QM_WRITE(pDev, port, addr, data)       \
        vxbWrite32 (FMAN_HANDLE(pDev),              \
                    (UINT32 *)((char *)FMAN_QM_BAR(pDev, port) + addr), data)

#define FMAN_PR_READ(pDev, port, addr)              \
        vxbRead32 (FMAN_HANDLE(pDev),               \
                   (UINT32 *)((char *)FMAN_PR_BAR(pDev, port) + addr))

#define FMAN_PR_WRITE(pDev, port, addr, data)       \
        vxbWrite32 (FMAN_HANDLE(pDev),              \
                    (UINT32 *)((char *)FMAN_PR_BAR(pDev, port) + addr), data)

#define FMAN_READ(pDev, addr)                       \
        vxbRead32 (FMAN_HANDLE(pDev),               \
                   (UINT32 *)((char *)FMAN_BAR(pDev) + addr))

#define FMAN_WRITE(pDev, addr, data)                \
        vxbWrite32 (FMAN_HANDLE(pDev),              \
                    (UINT32 *)((char *)FMAN_BAR(pDev) + addr), data)

#define FMAN_DM_READ(pDev, addr)                    \
        vxbRead32 (FMAN_HANDLE(pDev),               \
                   (UINT32 *)((char *)FMAN_DM_BAR(pDev) + addr))

#define FMAN_DM_WRITE(pDev, addr, data)             \
        vxbWrite32 (FMAN_HANDLE(pDev),              \
                    (UINT32 *)((char *)FMAN_DM_BAR(pDev) + addr), data)

#define FMAN_PRD_READ(pDev, addr)                   \
        vxbRead32 (FMAN_HANDLE(pDev),               \
                   (UINT32 *)((char *)FMAN_PRD_BAR(pDev) + addr))

#define FMAN_PRD_WRITE(pDev, addr, data)            \
        vxbWrite32 (FMAN_HANDLE(pDev),              \
                    (UINT32 *)((char *)FMAN_PRD_BAR(pDev) + addr), data)

#define FMAN_PRG_READ(pDev, addr)                   \
        vxbRead32 (FMAN_HANDLE(pDev),               \
                   (UINT32 *)((char *)FMAN_PRG_BAR(pDev) + addr))

#define FMAN_PRG_WRITE(pDev, addr, data)            \
        vxbWrite32 (FMAN_HANDLE(pDev),              \
                    (UINT32 *)((char *)FMAN_PRG_BAR(pDev) + addr), data)

#define FMAN_FP_READ(pDev, addr)                    \
        vxbRead32 (FMAN_HANDLE(pDev),               \
                   (UINT32 *)((char *)FMAN_FP_BAR(pDev) + addr))

#define FMAN_FP_WRITE(pDev, addr, data)             \
        vxbWrite32 (FMAN_HANDLE(pDev),              \
                    (UINT32 *)((char *)FMAN_FP_BAR(pDev) + addr), data)

#define FMAN_IR_READ(pDev, addr)                    \
        vxbRead32 (FMAN_HANDLE(pDev),               \
                   (UINT32 *)((char *)FMAN_IR_BAR(pDev) + addr))

#define FMAN_IR_WRITE(pDev, addr, data)             \
        vxbWrite32 (FMAN_HANDLE(pDev),              \
                    (UINT32 *)((char *)FMAN_IR_BAR(pDev) + addr), data)

#define FMAN_KG_READ(pDev, addr)                    \
        vxbRead32 (FMAN_HANDLE(pDev),               \
                   (UINT32 *)((char *)FMAN_KG_BAR(pDev) + addr))

#define FMAN_KG_WRITE(pDev, addr, data)             \
        vxbWrite32 (FMAN_HANDLE(pDev),              \
                    (UINT32 *)((char *)FMAN_KG_BAR(pDev) + addr), data)

#define FMAN_PL_READ(pDev, addr)                    \
        vxbRead32 (FMAN_HANDLE(pDev),               \
                   (UINT32 *)((char *)FMAN_PL_BAR(pDev) + addr))

#define FMAN_PL_WRITE(pDev, addr, data)             \
        vxbWrite32 (FMAN_HANDLE(pDev),              \
                    (UINT32 *)((char *)FMAN_PL_BAR(pDev) + addr), data)

#define FMAN_SETBIT(pDev, offset, val)              \
        FMAN_WRITE(pDev, offset, FMAN_READ(pDev, offset) | (val))

#define FMAN_CLRBIT(pDev, offset, val)              \
        FMAN_WRITE(pDev, offset, FMAN_READ(pDev, offset) & ~(val))

/* QMI/BMI API */

IMPORT STATUS fmanQmiPortConfig (VXB_DEV_ID, UINT8, UINT8, UINT8);
IMPORT STATUS fmanQmiPortHalt (VXB_DEV_ID, UINT8, UINT8);

IMPORT STATUS fmanBmiPortConfig (VXB_DEV_ID, UINT8, UINT8,
                                 UINT32, UINT32, UINT32, UINT16);
IMPORT STATUS fmanBmiPortHalt (VXB_DEV_ID, UINT8, UINT8);
IMPORT STATUS fmanBmiPoolInfoGet (VXB_DEV_ID, UINT8, FMAN_POOL_INFO *);
IMPORT STATUS fmanBmiPoolInfoSet (VXB_DEV_ID, UINT8, FMAN_POOL_INFO *);

/* Keygen API */

IMPORT STATUS fmanKgSchemeRead (VXB_DEV_ID, int, FMAN_KG_SCHEME *);
IMPORT STATUS fmanKgSchemeWrite (VXB_DEV_ID, int, FMAN_KG_SCHEME *);
IMPORT STATUS fmanKgPlanRead (VXB_DEV_ID, int, FMAN_KG_CPLAN *);
IMPORT STATUS fmanKgPlanWrite (VXB_DEV_ID, int, FMAN_KG_CPLAN *);
IMPORT STATUS fmanKgPartConfRead (VXB_DEV_ID, int, BOOL, UINT32 *);
IMPORT STATUS fmanKgPartConfWrite (VXB_DEV_ID, int, BOOL, UINT32);
IMPORT STATUS fmanKgPortConfig (VXB_DEV_ID, UINT32, int);
IMPORT STATUS fmanKgPortHalt (VXB_DEV_ID, UINT32, int);
IMPORT UINT64 fmanKgHash (UINT8 *, int);

/* Coarse classifier API */

IMPORT STATUS fmanCcPortConfig (VXB_DEV_ID, UINT32);
IMPORT STATUS fmanCcPortHalt (VXB_DEV_ID, UINT32);
IMPORT STATUS fmanCcConfigAdd (VXB_DEV_ID, FMAN_CC_CONFIG *, UINT32);
IMPORT VOID   fmanCcConfigFlush (VXB_DEV_ID);

/* Policer API */

IMPORT STATUS fmanPlProfileRead (VXB_DEV_ID, int, FMAN_PL_ENTRY *);
IMPORT STATUS fmanPlProfileWrite (VXB_DEV_ID, int, FMAN_PL_ENTRY *);
IMPORT STATUS fmanPlPramFlush (VXB_DEV_ID);
IMPORT STATUS fmanPlPortConfig (VXB_DEV_ID, UINT32, UINT32, UINT32);
IMPORT STATUS fmanPlPortHalt (VXB_DEV_ID, UINT32, UINT32);
IMPORT STATUS fmanPlRatesCalc (UINT32, UINT32, UINT32, UINT32, FMAN_PL_ENTRY *);

/* Parser API */

IMPORT STATUS fmanPrPortConfig (VXB_DEV_ID, UINT8, FMAN_PR *);
IMPORT STATUS fmanPrPortHalt (VXB_DEV_ID, UINT8);

IMPORT STATUS fmanPrSpFmcProgLoad (VXB_DEV_ID, FMAN_SP_PARAMS *);
IMPORT STATUS fmanPrSpAsmProgLoad (VXB_DEV_ID, UINT8, UINT32, char *, UINT8 *);
IMPORT STATUS fmanPrSpProgFlush (VXB_DEV_ID);
IMPORT STATUS fmanPrSpPortConfig (VXB_DEV_ID, UINT8, UINT8, UINT8);

IMPORT STATUS fmanPrPortTpidSet (VXB_DEV_ID, UINT8, UINT32);
IMPORT STATUS fmanPrPortTpidGet (VXB_DEV_ID, UINT8, UINT32 *);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbQorIQFmanh */
