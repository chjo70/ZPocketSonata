/* ppcE6500Compat.h - PowerPC E6500 L2 Cache specific header */

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
22jul14,ylu  created.
*/

#ifndef __INCppcE6500Compath
#define __INCppcE6500Compath
#if (CPU == PPCE6500)
/* L2 Cache register defines*/

#define L2CACHE_REG_BASE	0xC20000
#define L2CSR0_OFFSET		0x000
#define L2CSR1_OFFSET		0x004
#define L2CFG0_OFFSET		0x008
#define L2ERRINJCTL_OFFSET	0xE08
#define L2CAPTDATAHI_OFFSET	0xE20
#define L2CAPTDATALO_OFFSET	0xE24
#define L2CAPTECC_OFFSET	0xE28
#define L2ERRDET_OFFSET		0xE40
#define L2ERRINTEN_OFFSET	0xE48
#define L2ERRATTR_OFFSET	0xE4C
#define L2ERRADDR_OFFSET	0xE50
#define L2ERRCTL_OFFSET		0xE58
#define L2C_REG_INTERVAL	0x40000
#define L2C_REG_ADDR(cluster, ccsbar, offset) \
	(CAST(VUINT32 *)(ccsbar + L2CACHE_REG_BASE + offset + \
			 (cluster * L2C_REG_INTERVAL)))

#define L2C_REG_ADDR_OFFSET(cluster, offset) \
	 (L2CACHE_REG_BASE + offset + (cluster * L2C_REG_INTERVAL))

#define L2CSR0(cluster, ccsbar) L2C_REG_ADDR(cluster, ccsbar, L2CSR0_OFFSET)
#define L2CSR1(cluster, ccsbar) L2C_REG_ADDR(cluster, ccsbar, L2CSR1_OFFSET)
#define L2CFG0(cluster, ccsbar) L2C_REG_ADDR(cluster, ccsbar, L2CFG0_OFFSET)
#define L2ERRINJCTL(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRINJCTL_OFFSET)

#define L2ERRINJCTL_CLUSTER_OFFSET(cluster) (L2CACHE_REG_BASE + L2ERRINJCTL_OFFSET + (cluster * L2C_REG_INTERVAL))

#define L2CAPTDATAHI(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2CAPTDATAHI_OFFSET)
#define L2CAPTDATALO(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2CAPTDATALO_OFFSET)
#define L2CAPTECC(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2CAPTECC_OFFSET)
#define L2ERRDET(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRDET_OFFSET)
#define L2ERRINTEN(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRINTEN_OFFSET)
#define L2ERRATTR(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRATTR_OFFSET)
#define L2ERRADDR(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRADDR_OFFSET)
#define L2ERRCTL(cluster, ccsbar)	L2C_REG_ADDR(cluster, ccsbar, L2ERRCTL_OFFSET)

/* L2CSR0 BIT MASKS and BIT SHIFTS */

#define L2CSR0_L2E_BIT      0             /* L2 Enable */
#define L2CSR0_L2PE_BIT     1             /* L2 Parity Enable */
#define L2CSR0_L2FI_BIT     10            /* L2 Flash Invalidate */
#define L2CSR0_L2REP_BIT    19            /* L2 Line Replcmnt Algo. (2) */
#define L2CSR0_L2FL_BIT     20            /* L2 Flush */
#define L2CSR0_L2LFC_BIT    21            /* L2 Lock Flush Clear */
#define L2CSR0_L2LOA_BIT    24            /* L2 Lock Overflow Allocate */
#define L2CSR0_L2LO_BIT     26            /* L2 Lock Overflow */

#define L2CSR0_L2E_MSK      (1U << (31 - L2CSR0_L2E_BIT))
#define L2CSR0_L2PE_MSK     (1U << (31 - L2CSR0_L2PE_BIT))
#define L2CSR0_L2FI_MSK     (1U << (31 - L2CSR0_L2FI_BIT))
#define L2CSR0_L2REP_MSK    (3U << (31 - L2CSR0_L2REP_BIT))
#define L2CSR0_L2FL_MSK     (1U << (31 - L2CSR0_L2FL_BIT))
#define L2CSR0_L2LFC_MSK    (1U << (31 - L2CSR0_L2LFC_BIT))
#define L2CSR0_L2LOA_MSK    (1U << (31 - L2CSR0_L2LOA_BIT))
#define L2CSR0_L2LO_MSK     (1U << (31 - L2CSR0_L2LO_BIT))

/* L2CSR1 BIT MASKS and BIT SHIFTS */

#define L2CSR1_DYNAMICHARVARD_BIT 0	/* Dynamic harvard mode */
#define L2CSR1_L2BHM_BIT          1	/* Bank hash mode */
#define L2CSR1_L2STASHRSRV_BIT    3	/* L2 stashing reserved resources */
#define L2CSR1_L2STASHID_BIT      24	/* L2 cache stash ID */

#define L2CSR1_DYNAMICHARVARD_MSK (1U << (31 - L2CSR1_DYNAMICHARVARD_BIT))
#define L2CSR1_L2BHM_MSK          (1U << (31 - L2CSR1_L2BHM_BIT))
#define L2CSR1_L2CSR1_MSK         (3U << (31 - L2CSR1_L2STASHRSRV_BIT))
#define L2CSR1_L2STASHID_MSK      (255U < (31 - L2CSR1_L2STASHID_MSK))

/* L3 Cache register defines */

#define CPCCSR0(addr, cpcNum)   (CAST(VUINT32 *) (addr + 0x010000  \
                                          +(cpcNum * 0x001000)))

#define CPCPAR(addr, cpcNum,n)  (CAST(VUINT32 *) (addr + 0x010000  \
                                          +(cpcNum * 0x001000)     \
                                          + 0x000208  + n*0x10 ))

#define CPCEWCR(addr, cpcNum,n) (CAST(VUINT32 *) (addr + 0x010000  \
                                          +(cpcNum * 0x001000)     \
                                          + 0x000010  + n*0x10 ))

#define CPCEWBAR(addr, cpcNum,n)(CAST(VUINT32 *) (addr + 0x010000  \
                                          +(cpcNum * 0x001000)     \
                                          + 0x000014  + n*0x10 ))

#define CPCHDBCR(addr, cpcNum)  (CAST(VUINT32 *) (addr + 0x010000  \
                                          +(cpcNum * 0x001000)     \
                                          + 0x000F00  ))

#define CPC_ENABLE          0x80000000  /* CPCCSR0_CPCE */
#define CPC_FLUSH           0x00000800  /* CPCCSR0_CPCFL */
#define CPC_INVALIDATE      0x00200400  /* CPCCSR0_CPCFI | CPCCSR0_CPCLFC */
#define CPC_CLEAR_LOCKS     0x00000400  /* CPCCSR0_CPCLFC */

#define CPC_MODE_WRITE_THROUGH  0x00080000  /* CPCCSR0_CPCWT */

/* Per sect 8.2.9  (sect. 2.7.3 set reserved = 0) */

#define CPCPAR_RESET_VALUE  0x000003fb

#define CPC1_BASE_ADDR		0x010000
#define CPC2_BASE_ADDR		0x011000
#define CPC3_BASE_ADDR		0x012000

#define CPCEWCR0(x)		    (x + 0x010)
#define CPCEWBAR0(x)        (x + 0x014)
#define CPCEWCR1(x)		    (x + 0x020)
#define CPCEWBAR1(x)	    (x + 0x024)
#define CPCSRCR1(x)		    (x + 0x100)
#define CPCSRCR0(x)		    (x + 0x104)
#define CPCPIR(x,y)		    (x + 0x200 + y * 0x10)
#define CPCPWR(x,y)		    (x + 0x20C + y * 0x10)
#define CPCERRINJHI(x)		(x + 0xE00)
#define CPCERRINJLO(x)		(x + 0xE04)
#define CPCERRINJCTL(x)		(x + 0xE08)
#define CPCCAPTDATAHI(x)	(x + 0xE20)
#define CPCCAPTDATALOW(x)	(x + 0xE24)
#define CPCCAPTECC(x)		(x + 0xE28)
#define CPCERRDET(x)		(x + 0xE40)
#define CPCERRDIS(x)		(x + 0xE44)
#define CPCERRINTEN(x)		(x + 0xE48)
#define CPCERRATTR(x)		(x + 0xE4C)
#define CPCERREADDR(x)		(x + 0xE50)
#define CPCERRADDR(x)		(x + 0xE54)
#define CPCERRCTL(x)		(x + 0xE58)

#define CPCCSR0_CPCE_BIT	0 	/* CPC enable */
#define CPCCSR0_CPCPE_BIT	1 	/* CPC parity/ECC enable */
#define CPCCSR0_CPCFI_BIT	10 	/* CPC flash invalidate */
#define CPCCSR0_CPCWT_BIT	12 	/* CPC write-through mode */
#define CPCCSR0_CPCREP_BIT	18 	/* CPC line replacement algorithm (2) */
#define CPCCSR0_CPCFL_BIT	20 	/* CPC flush */
#define CPCCSR0_CPCLFC_BIT	21 	/* CPC lock flash clear */
#define CPCCSR0_CPCLOA_BIT	24 	/* CPC lock overflow allocate */
#define CPCCSR0_CPCLO_BIT	26 	/* CPC lock overflow */

#define CPCCSR0_CPCE_MSK	(1U << (31 - CPCCSR0_CPCE_BIT))
#define CPCCSR0_CPCPE_MSK	(1U << (31 - CPCCSR0_CPCPE_BIT))
#define CPCCSR0_CPCFI_MSK	(1U << (31 - CPCCSR0_CPCFI_BIT))
#define CPCCSR0_CPCWT_MSK	(1U << (31 - CPCCSR0_CPCWT_BIT))
#define CPCCSR0_CPCREP_MSK	(3U << (31 - CPCCSR0_CPCREP_BIT - 1))
#define CPCCSR0_CPCFL_MSK	(1U << (31 - CPCCSR0_CPCFL_BIT))
#define CPCCSR0_CPCLFC_MSK	(1U << (31 - CPCCSR0_CPCLFC_BIT))
#define CPCCSR0_CPCLOA_MSK	(1U << (31 - CPCCSR0_CPCLOA_BIT))
#define CPCCSR0_CPCLO_MSK	(1U << (31 - CPCCSR0_CPCLO_BIT))

#define CPC_WRITE_MODE_WT   0x00080000  /* CPCCSR0_CPCWT */
#define CPC_WRITE_MODE_CB   0

/* CPCEWCRn field definitions */

#define CPCEWCRN_E_BIT		0	/* Enable */
#define CPCEWCRN_LOCK_BIT	1	/* Lock */
#define CPCEWCRN_SIZE_BIT	10	/* Size (6) 2^(size + 6) */
#define CPCEWCRN_EADDRBASE_BIT	16	/* Extended base address (16) */
#endif /* PPCE6500 */
#endif /* __INCppcE6500Compath */
