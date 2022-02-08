/* vxbMiiClause45.h - MII Clause 45 definitions for vxBus */

/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
15mar16,wap  Add PCS MMD definitons
08mar16,wap  Written
*/

/*
DESCRIPTION

This header contains register definitions for the IEEE 802.3 clause 45
MDIO interface. Unlike the clause 22 MDIO protocol, which allows for 32
devices, each with 32 registers, the clause 45 protocol allows for 32
devices, each with 32 sub-devices, each with 65536 registers.

As the specification is quite extensive, only a subset of the complete
interface is defined here. Additional registers may be added as the need
arises.

Note that all MMDs contain registers 5 and 6. Registers 2 and 3 (vendor
and device intenfiers) are usually also present.

SEE ALSO:

\tb "IEEE Standard for Ethernet http://standards.ieee.org/getieee802/download/802.3-2012.zip"
*/

#ifndef __INCvxbMiiClause45h
#define __INCvxbMiiClause45h

#ifdef __cplusplus
extern "C" {
#endif

#define MII45_MMD_RSVD		0	/* Reserved */
#define MII45_MMD_PMAPMD	1	/* Physical Media Attachment/Dependent */
#define MII45_MMD_WIS		2	/* WAN Interface Sublayer */
#define MII45_MMD_PCS		3	/* Physical Coding Sublayer */
#define MII45_MMD_PHYXS		4	/* PHY Extenter Sublayer */
#define MII45_MMD_DTEXS		5	/* DTE Extenter Sublayer */
#define MII45_MMD_TC		6	/* Transmission Convergence */
#define MII45_MMD_AUTONEG	7	/* Autonegotiation */
#define MII45_MMD_SPMA1		8	/* Separated PMA (1) */
#define MII45_MMD_SPMA2		9	/* Separated PMA (2) */
#define MII45_MMD_SPMA3		10	/* Separated PMA (3) */
#define MII45_MMD_SPMA4		11	/* Separated PMA (4) */
#define MII45_MMD_CL22EXT	29	/* Clause 22 extention */
#define MII45_MMD_VSPEC1	30	/* Vendor-specific 1 */
#define MII45_MMD_VSPEC2	32	/* Vendor-specific 2 */

/* Registers common to all MMDs */

#define MII45_VID		0x0002
#define MII45_DID		0x0003
#define MII45_DPKG1		0x0005
#define MII45_DPKG2		0x0006

/* Devices in package register 1 */

#define MII45_DPKG1_CLAUSE22	0x0001	/* Clause 22 MMD present */
#define MII45_DPKG1_PMAPMD	0x0002	/* PMA/PMD present */
#define MII45_DPKG1_WIS		0x0004	/* WIS present */
#define MII45_DPKG1_PCS		0x0008	/* PCS present */
#define MII45_DPKG1_PHYXS	0x0010  /* PHY XS present */
#define MII45_DPKG1_DTEXS	0x0020  /* DTS XS present */
#define MII45_DPKG1_TC		0x0040  /* TC present */
#define MII45_DPKG1_AUTONEG	0x0080  /* Autoneg present */
#define MII45_DPKG1_SPMA1	0x0100  /* Separated PMA (1) present */
#define MII45_DPKG1_SPMA2	0x0200	/* Separated PMA (2) present */
#define MII45_DPKG1_SPMA3	0x0400  /* Separated PMA (3) present */
#define MII45_DPKG1_SPMA4	0x0800  /* Separated PMA (4) present */

/* Devices in package register 2 */

#define MII45_DPKG2_CL22EXT	0x2000	/* Clause 22 extension present */
#define MII45_DPKG2_VSPEC1	0x4000	/* Vendor-specific 1 present */
#define MII45_DPKG2_VSPEC2	0x8000	/* Vendor-specific 1 present */

/************************ PMA/PMD MMD registers *******************************/

#define MII45_PMAPMD_CTL0	0x0000	/* PMA/PMD control 1 */
#define MII45_PMAPMD_STS0	0x0001	/* PMA/PMD status 1 */
#define MII45_PMAPMD_PKGID0	0x0002	/* PMA/PMD Package ID1 */
#define MII45_PMAPND_PKGID1	0x0003	/* PMA/PMD Package ID2 */
#define MII45_PMAPMD_SPEED	0x0004	/* Speed ability */
#define MII45_PMAPMD_CTL1	0x0007	/* PMA/PMD control 2 */
#define MII45_PMAPMD_STS1	0x0008	/* PMA/PMD status 2 */
#define MII45_PMAPMD_TXDIS	0x0009	/* Transmit disable */
#define MII45_PMAPMD_RXDET	0x000A	/* RX signal detect */
#define MII45_PMAPMD_EXT	0x000B  /* Extended ability register */

/* PMA/PMD control register 1 */

#define MII45_PMAPMDCTL0_LCL_LOOP	0x0001	/* Enable local loopback */
#define MII45_PMAPMDCTL0_RMT_LOOP	0x0002	/* Enable remove loopback */
#define MII45_PMAPMDCTL0_SPEEDSEL0	0x003C	/* SPEEDSEL0 */
#define MII45_PMAPMDCTL0_SPEEDSEL1	0x0040  /* SPEEDSEL MSB */
#define MII45_PMAPMDCTL0_LOWPWR		0x0080	/* Low power mode */
#define MII45_PMAPMDCTL0_SPEEDSEL2	0x2000	/* SPEEDSEL LSB */
#define MII45_PMAPMDCTL0_RESET		0x8000	/* RESET */

#define MII45_PMAPMDSPEEDSEL(x) ((x) &		\
	(MII45_PMAPMDCTL0_SPEEDSEL0 |		\
	MII45_PMAPMDCTL0_SPEEDSEL1 |		\
	MII45_PMAPMDCTL0_SPEEDSEL2)

#define MII45_PMAPMDSPEEDSEL_10MBPS	0x0000	/* 10 MBps */
#define MII45_PMAPMDSPEEDSEL_100MBPS	0x2000	/* 100 MBps */
#define MII45_PMAPMDSPEEDSEL_1000MBPS	0x0040	/* 1 Gbps */
#define MII45_PMAPMDSPEEDSEL_10GBPS	0x2040	/* 10 Gbps */
#define MII45_PMAPMDSPEEDSEL_10PS2TL	0x2044	/* 10PASS-TS/2BASE-TL */
#define MII45_PMAPMDSPEEDSEL_40GBPS	0x2048	/* 40 Gbps */
#define MII45_PMAPMDSPEEDSEL_100GBPS	0x204C	/* 100 Gbps */

/* PMA/PMD status register 1 */

#define MII45_PMAPMDSTS0_LOWPWR		0x0002	/* Low power ability */
#define MII45_PMAPMDSTS0_LINKSTS	0x0004	/* RX link status */
#define MII45_PMAPMDSTS0_FAULT		0x0080	/* Fault detected */

/* PMA/PMD speed ability */

#define MII45_PMAPMDSPEED_10G		0x0001	/* 10G capable */
#define MII45_PMAPMDSPEED_2BASETL	0x0002	/* 10BASE-TL capable */
#define MII45_PMAPMDSPEED_10PASSTS	0x0004	/* 10PASS-TS capable */
#define MII45_PMAPMDSPEED_1G		0x0010	/* 1000Mbps capable */
#define MII45_PMAPMDSPEED_100M		0x0020	/* 100Mbps capable */
#define MII45_PMAPMDSPEED_10M		0x0040	/* 10Mbps capable */
#define MII45_PMAPMDSPEED_10G1G		0x0080	/* 10G/1G capable */
#define MII45_PMAPMDSPEED_40G		0x0100	/* 40G capable */
#define MII45_PMAPMDSPEED_100G		0x0200	/* 100G capable */

/* PMA/PMD control register 2 */

#define MII45_PMAPMDCTL1_TYPESEL	0x003F	/* Type selection */

#define MII45_PMAPMDTYPE_10GBASECX4	0x0000
#define MII45_PMAPMDTYPE_10GBASEEW	0x0001
#define MII45_PMAPMDTYPE_10GBASELW	0x0002
#define MII45_PMAPMDTYPE_10GBASESW	0x0003
#define MII45_PMAPMDTYPE_10GBASELX4	0x0004
#define MII45_PMAPMDTYPE_10GBASEER	0x0005
#define MII45_PMAPMDTYPE_10GBASELR	0x0006
#define MII45_PMAPMDTYPE_10GBASESR	0x0007
#define MII45_PMAPMDTYPE_10GBASELRM	0x0008
#define MII45_PMAPMDTYPE_10GBASET	0x0009
#define MII45_PMAPMDTYPE_10GBASEKX4	0x000A
#define MII45_PMAPMDTYPE_10GBASEKR	0x000B
#define MII45_PMAPMDTYPE_1000BASET	0x000C
#define MII45_PMAPMDTYPE_1000BASEKX	0x000D
#define MII45_PMAPMDTYPE_100BASETX	0x000E
#define MII45_PMAPMDTYPE_10BASET	0x000F
#define MII45_PMAPMDTYPE_10G1GBASEPRXD1	0x0010
#define MII45_PMAPMDTYPE_10G1GBASEPRXD2	0x0011
#define MII45_PMAPMDTYPE_10G1GBASEPRXD3	0x0012
#define MII45_PMAPMDTYPE_10GBASEPRD1	0x0013
#define MII45_PMAPMDTYPE_10GBASEPRD2	0x0014
#define MII45_PMAPMDTYPE_10GBASEPRD3	0x0015
#define MII45_PMAPMDTYPE_10G1GBASEPRXU1	0x0016
#define MII45_PMAPMDTYPE_10G1GBASEPRXU2	0x0017
#define MII45_PMAPMDTYPE_10G1GBASEPRXU3	0x0018
#define MII45_PMAPMDTYPE_10GBASEPRU1	0x0019
#define MII45_PMAPMDTYPE_10GBASEPRU3	0x001A
#define MII45_PMAPMDTYPE_40GBASEKR4	0x0020
#define MII45_PMAPMDTYPE_40GBASECR4	0x0021
#define MII45_PMAPMDTYPE_40GBASESR4	0x0022
#define MII45_PMAPMDTYPE_40GBASELR4	0x0023
#define MII45_PMAPMDTYPE_40GBASEFR	0x0024
#define MII45_PMAPMDTYPE_100GBASECR10	0x0028
#define MII45_PMAPMDTYPE_100GBASESR10	0x0029
#define MII45_PMAPMDTYPE_100GBASELR4	0x002A
#define MII45_PMAPMDTYPE_100GBASEER4	0x002B

/* PMA/PMD status register 2 */

#define MII45_PMAPMDSTS1_LCL_LOOP	0x0001	/* Local loopback ability */
#define MII45_PMAPMDSTS1_10GBASEEW	0x0002
#define MII45_PMAPMDSTS1_10GBASELW	0x0004
#define MII45_PMAPMDSTS1_10GBASESW	0x0008
#define MII45_PMAPMDSTS1_10GBASELX4	0x0010
#define MII45_PMAPMDSTS1_10GBASEER	0x0020
#define MII45_PMAPMDSTS1_10GBASELR	0x0040
#define MII45_PMAPMDSTS1_10GBASESR	0x0080
#define MII45_PMAPMDSTS1_TXDIS		0x0100
#define MII45_PMAPMDSTS1_EXTABIL	0x0200
#define MII45_PMAPMDSTS1_RXFAULT	0x0400
#define MII45_PMAPMDSTS1_TXFAULT	0x0800
#define MII45_PMAPMDSTS1_RXFAULTABIL	0x1000
#define MII45_PMAPMDSTS1_TXFAULTABIL	0x2000
#define MII45_PMAPMDSTS1_DEVPRESENT	0xC000

#define MII45_DEVPRESENT_RESPONDING	0x8000

/* PMA/PMD extended ability register */

#define MII45_PMAPMDEXT_10GBASECX4	0x0001
#define MII45_PMAPMDEXT_10GBASELRM	0x0002
#define MII45_PMAPMDEXT_10GBASET	0x0004
#define MII45_PMAPMDEXT_10GBASEKX4	0x0008
#define MII45_PMAPMDEXT_10GBASEKR	0x0010
#define MII45_PMAPMDEXT_1000BASET	0x0020
#define MII45_PMAPMDEXT_1000BASEKX	0x0040
#define MII45_PMAPMDEXT_100BASETX	0x0080
#define MII45_PMAPMDEXT_10BASET		0x0100
#define MII45_PMAPMDEXT_P2MP		0x0200
#define MII45_PMAPMDEXT_40G100GEXT	0x2000

/**************************** PCS MMD registers *******************************/

#define MII45_PCS_CTL0		0x0000	/* PCS control 1 */
#define MII45_PCS_STS0		0x0001	/* PCS status 1 */
#define MII45_PCS_PKGID0	0x0002	/* PCS Package ID1 */
#define MII45_PCS_PKGID1	0x0003	/* PCS Package ID2 */
#define MII45_PCS_SPEED		0x0004	/* PCS speed ability */
#define MII45_PCS_CTL1		0x0007	/* PMA/PMD control 2 */
#define MII45_PCS_STS1		0x0008	/* PMA/PMD status 2 */

/* PCS control register 1 */

#define MII45_PCSCTL0_SPEEDSEL0		0x003C	/* SPEEDSEL0 */
#define MII45_PCSCTL0_SPEEDSEL1		0x0040  /* SPEEDSEL1 */
#define MII45_PCSCTL0_CLKSTOP		0x0080	/* Clock can stop during LPI */
#define MII45_PCSCTL0_LOWPRW		0x0100	/* Low power mode enable */
#define MII45_PCSCTL0_SPEEDSEL2		0x3000	/* SPEEDSEL2 */
#define MII45_PCSCTL0_LOOPBK		0x4000	/* Loopback enable */
#define MII45_PCSCTL0_RESET		0x8000	/* RESET */

#define MII45_PCSDSPEEDSEL(x) ((x) &		\
	(MII45_PCSCTL0_SPEEDSEL0 |		\
	MII45_PCSCTL0_SPEEDSEL1 |		\
	MII45_PCSCTL0_SPEEDSEL2)

#define MII45_PCSSPEEDSEL_10GBPS	0x2040	/* 10 Gbps */
#define MII45_PCSSPEEDSEL_10PS2TL	0x2044	/* 10PASS-TS/2BASE-TL */
#define MII45_PCSSPEEDSEL_10G1G		0x2048	/* 10Gbps/1Gbps */
#define MII45_PCSSPEEDSEL_40GBPS	0x204C	/* 40 Gbps */
#define MII45_PCSSPEEDSEL_100GBPS	0x2050	/* 100 Gbps */

/* PCS status register 1 */

#define MII45_PCSSTS0_LOWPWR		0x0002	/* Low power supported */
#define MII45_PCSSTS0_LINKSTS		0x0004	/* Link status */
#define MII45_PCSSTS0_CLKSTOP		0x0040	/* Clock can stop during LPI */
#define MII45_PCSSTS0_FAULT		0x0080	/* Fault detected */
#define MII45_PCSSTS0_RXLPI_IND		0x0100	/* RX PCS is receiving LPI */
#define MII45_PCSSTS0_TXLPI_IND		0x0200	/* TX PCS is receiving LPI */
#define MII45_PCSSTS0_RXLPI		0x0400 	/* RX PCS has received LPI */
#define MII45_PCSSTS0_TXLPI		0x0800 	/* TX PCS has received LPI */

/* PCS speed ability register */

#define MII45_PCSSPEED_10G		0x0001	/* 10G capable */
#define MII45_PCSSPEED_10PS2TL		0x0002	/* 10PASS-TS/20BASE-TL */
#define MII45_PCSSPEED_40G		0x0004	/* 40G capable */
#define MII45_PCSSPEED_100G		0x0008	/* 100G capable */

/* PCS control register 2 */

#define MII45_PCSCTL1_TYPESEL		0x0007	/* Type selection */

#define MII45_PCSTYPE_10GBASESR		0x0000	/* 10GBase-SR */
#define MII45_PCSTYPE_10GBASEX		0x0001	/* 10GBase-X */
#define MII45_PCSTYPE_10GBASEW		0x0002	/* 10GBase-W */
#define MII45_PCSTYPE_10GBASET		0x0003	/* 10GBase-T */
#define MII45_PCSTYPE_40GBASER		0x0004	/* 40GBase-R */
#define MII45_PCSTYPE_100GBASER		0x0005	/* 100GBase-R */

/* PCS status register 2 */

#define MII45_PCSSTS1_10GBASER		0x0001	/* 10GBase-R capable */
#define MII45_PCSSTS1_10GBASEX		0x0002	/* 10GBase-X capable */
#define MII45_PCSSTS1_10GBASEW		0x0004	/* 10GBase-W capable */
#define MII45_PCSSTS1_10GBASET		0x0008	/* 10GBase-T capable */
#define MII45_PCSSTS1_40GBASER		0x0010	/* 40GBase-R capable */
#define MII45_PCSSTS1_100GBASER		0x0020	/* 100GBase-R capable */
#define MII45_PCSSTS1_RXFAULT		0x0400	/* Receive fault */
#define MII45_PCSSTS1_TXFAULT		0x0800	/* Transmit fault */
#define MII45_PCSSTS1_DEVPRESENT	0xC000	/* Device present */

/************************ Autoneg MMD registers *******************************/

#define MII45_AUTONEG_CTL	0x0000	/* AN control */
#define MII45_AUTONEG_STS	0x0001	/* AN status */
#define MII45_AUTONEG_PKGID0	0x000E  /* Package ID 1 */
#define MII45_AUTONEG_PKGID1	0x000F  /* Package ID 2 */
#define MII45_AUTONEG_ANAR0	0x0010  /* Advertisement 0 */
#define MII45_AUTONEG_ANAR1	0x0011  /* Advertisement 1 */
#define MII45_AUTONEG_ANAR2	0x0012  /* Advertisement 2 */
#define MII45_AUTONEG_LPAR0	0x0013 	/* Link partner ability 0 */
#define MII45_AUTONEG_LPAR1	0x0014 	/* Link partner ability 1 */
#define MII45_AUTONEG_LPAR2	0x0015 	/* Link partner ability 2 */
#define MII45_AUTONEG_XNPTX0	0x0016
#define MII45_AUTONEG_XNPTX1	0x0017
#define MII45_AUTONEG_XNPTX2	0x0018
#define MII45_AUTONEG_XNPLP0	0x0019
#define MII45_AUTONEG_XNPLP1	0x001A
#define MII45_AUTONEG_XNPLP2	0x001B
#define MII45_AUTONEG_10GBTCTL	0x0020	/* 10GBaseT AN control */
#define MII45_AUTONEG_10GBTSTS	0x0021	/* 10GBaseT AN status */
#define MII45_AUTONEG_BRSTS	0x0030  /* BASE-R status */
#define MII45_AUTONEG_EEEANAR	0x003C	/* EEE advertisement */
#define MII45_AUTONEG_EEELPAR	0x003D	/* EEE link partner ability */


#ifdef __cplusplus
}
#endif

#endif /* __INCvxbMiiClause45h */
