/* mmuPpcLib.h - mmu library for PowerPC */

/* Copyright 1995, 2003-2006, 2008  Wind River Systems, Inc. */

/*
modification history
--------------------
01g,21jan08,pch  Change order of SR union so initialization in ppcArchVars.c
		 produces correct results
01f,24aug06,to   change ea from struct to union
01e,04aug05,pch  _WRS_MMU_64BIT fixes
01d,15mar04,rec  PPC970 merge from T2
01c,11jul03,pcs  Port to Base 6.
01b,07jul03,pad  Added exclusion of C code for inclusion in assembly files.
01a,11sep95,tpr	 written.
*/

#ifndef __INCmmuPpcLibh
#define __INCmmuPpcLibh

#ifdef __cplusplus
extern "C" {
#endif

/* page table related definitions */

#define MMU_PG_TBL_PTE_VALID_SHIFT		29

#define MMU_LVL_2_DESC_NB                       0x00000400
#define MMU_LVL_1_DESC_NB                       MMU_LVL_2_DESC_NB

#define MMU_LVL_1_L2BA_MSK                      0xfffff000
#define MMU_RPN_SHIFT				12

#if ((CPU == PPC603) || (CPU == PPCEC603))
#define FULL_HASH_TBL_BYPASS  TRUE
#else
#define FULL_HASH_TBL_BYPASS  FALSE
#endif

#define MMU_PAGE_SIZE           0x1000          /* pages are 4K bytes */


#ifdef	_WRS_MMU_64BIT

/* 64-bit implementation see Programming Environments table 7-26 */

#define MMU_HASH_DIVISOR	0x01000000	/* 64 bit page table uses */

#define MMU_SDR1_HTABORG_16M	0xfffc0000	/* HTABORG value for 16M */
#define MMU_SDR1_HTABORG_32M	0xfff80000	/* HTABORG value for 32M */
#define MMU_SDR1_HTABORG_64M	0xfff00000	/* HTABORG value for 64M */
#define MMU_SDR1_HTABORG_128M	0xffe00000	/* HTABORG value for 128M */
#define MMU_SDR1_HTABORG_256M	0xffc00000	/* HTABORG value for 256M */
#define MMU_SDR1_HTABORG_512M	0xff800000	/* HTABORG value for 512M */
#define MMU_SDR1_HTABORG_1G	0xff000000	/* HTABORG value for 1G */
#define MMU_SDR1_HTABORG_2G	0xfe000000	/* HTABORG value for 2G */
#define MMU_SDR1_HTABORG_4G	0xfc000000	/* HTABORG value for 4G */

#define MMU_SDR1_HTABSIZE_16M	0x00000000	/* HTABSIZE value for 16M */
#define MMU_SDR1_HTABSIZE_32M	0x00000001	/* HTABSIZE value for 32M */
#define MMU_SDR1_HTABSIZE_64M	0x00000002	/* HTABSIZE value for 64M */
#define MMU_SDR1_HTABSIZE_128M	0x00000003	/* HTABSIZE value for 128M */
#define MMU_SDR1_HTABSIZE_256M	0x00000004	/* HTABSIZE value for 256M */
#define MMU_SDR1_HTABSIZE_512M	0x00000005	/* HTABSIZE value for 512M */
#define MMU_SDR1_HTABSIZE_1G	0x00000006	/* HTABSIZE value for 1G */
#define MMU_SDR1_HTABSIZE_2G	0X00000007	/* HTABSIZE value for 2G */
#define MMU_SDR1_HTABSIZE_4G	0x00000008	/* HTABSIZE value for 4G */
#define MMU_SDR1_HTABMASK_16M	MMU_SDR1_HTABSIZE_16M
#define MMU_SDR1_HTABMASK_32M	MMU_SDR1_HTABSIZE_32M
#define MMU_SDR1_HTABMASK_64M	MMU_SDR1_HTABSIZE_64M
#define MMU_SDR1_HTABMASK_128M	MMU_SDR1_HTABSIZE_128M
#define MMU_SDR1_HTABMASK_256M	MMU_SDR1_HTABSIZE_256M
#define MMU_SDR1_HTABMASK_512M	MMU_SDR1_HTABSIZE_512M
#define MMU_SDR1_HTABMASK_1G	MMU_SDR1_HTABSIZE_1G
#define MMU_SDR1_HTABMASK_2G	MMU_SDR1_HTABSIZE_2G
#define MMU_SDR1_HTABMASK_4G	MMU_SDR1_HTABSIZE_4G


#define MMU_PTE_MIN_SIZE_16M	0x00040000	/* 256k min size */
#define MMU_PTE_MIN_SIZE_32M	0x00080000	/* 512k min size */
#define MMU_PTE_MIN_SIZE_64M	0x00100000	/*   1M min size */
#define MMU_PTE_MIN_SIZE_128M	0x00200000	/*   2M min size */
#define MMU_PTE_MIN_SIZE_256M	0x00400000	/*   4M min size */
#define MMU_PTE_MIN_SIZE_512M	0x00800000	/*   8M min size */
#define MMU_PTE_MIN_SIZE_1G	0x01000000	/*  16M min size */
#define MMU_PTE_MIN_SIZE_2G	0x02000000	/*  32M min size */
#define MMU_PTE_MIN_SIZE_4G	0x04000000	/* 128k min size */

#define MMU_EA_BYTE_OFFSET	0x00000fff	/* Byte Offset in E.A */
#define MMU_EA_API		0x0000f800	/* abbreviated page index */
						/* see PEM, fig. 7-17 */
#define MMU_EA_API_SHIFT	11		/* api shift in page index */

#define MMU_SR_NB_SHIFT		28
#define MMU_EA_PAGE_INDEX	0x0ffff000	/* Page Index in E.A. */
#define MMU_EA_PAGE_INDEX_SHIFT	12		/* Page Index shift */

#define MMU_VSID_PRIM_HASH	0x000fffff	/* primary hash value in VSID */
						/* NOTE: this is not correct. */
						/* see PEM, fig. 7-29 */
#define MMU_HASH_VALUE_LOW	0x000007ff

#define MMU_HASH_VALUE_HIGH	0xfffff800

#define MMU_HASH_VALUE_HIGH_SHIFT	11

#define MMU_PTE_HASH_VALUE_HIGH_SHIFT	18
#define MMU_PTE_HASH_VALUE_LOW_SHIFT	7

#define MMU_PTE_VSID_SHIFT	12
#define MMU_PTE_API		0x00000f80	/* API field in PTE */
#define MMU_PTE_API_SHIFT	7		/* API shift in PTE */
#define MMU_PTE_H		0x00000002
#define MMU_PTE_H_SHIFT		1
#define MMU_PTE_V		0x00000001

#else	/* not _WRS_MMU_64BIT */

/* 32-bit implementation see Programming Environments table 7-27 */

#define MMU_HASH_DIVISOR	0x00800000
#define MMU_SDR1_HTABORG_MASK	0xffff0000	/* HTABORG mask */
#define MMU_SDR1_HTABORG_8M	0xffff0000	/* HTABORG value for 8M */
#define MMU_SDR1_HTABORG_16M	0xfffe0000	/* HTABORG value for 16M */
#define MMU_SDR1_HTABORG_32M	0xfffc0000	/* HTABORG value for 32M */
#define MMU_SDR1_HTABORG_64M	0xfff80000	/* HTABORG value for 64M */
#define MMU_SDR1_HTABORG_128M	0xfff00000	/* HTABORG value for 128M */
#define MMU_SDR1_HTABORG_256M	0xffe00000	/* HTABORG value for 256M */
#define MMU_SDR1_HTABORG_512M	0xffc00000	/* HTABORG value for 512M */
#define MMU_SDR1_HTABORG_1G	0xff800000	/* HTABORG value for 1G */
#define MMU_SDR1_HTABORG_2G	0xff000000	/* HTABORG value for 2G */
#define MMU_SDR1_HTABORG_4G	0xfe000000	/* HTABORG value for 4G */

#define MMU_SDR1_HTABMASK_MASK	0x000001ff	/* HTABMASK mask */
#define MMU_SDR1_HTABMASK_SHIFT	16		/* HTABMASK shift */
#define MMU_SDR1_HTABMASK_8M	0x00000000	/* HTABMASK value for 8M */
#define MMU_SDR1_HTABMASK_16M	0x00000001	/* HTABMASK value for 16M */
#define MMU_SDR1_HTABMASK_32M	0x00000003	/* HTABMASK value for 32M */
#define MMU_SDR1_HTABMASK_64M	0x00000007	/* HTABMASK value for 64M */
#define MMU_SDR1_HTABMASK_128M	0x0000000f	/* HTABMASK value for 128M */
#define MMU_SDR1_HTABMASK_256M	0x0000001f	/* HTABMASK value for 256M */
#define MMU_SDR1_HTABMASK_512M	0x0000003f	/* HTABMASK value for 512M */
#define MMU_SDR1_HTABMASK_1G	0x0000007f	/* HTABMASK value for 1G */
#define MMU_SDR1_HTABMASK_2G	0x000000ff	/* HTABMASK value for 2G */
#define MMU_SDR1_HTABMASK_4G	0x000001ff	/* HTABMASK value for 4G */

#define MMU_PTE_MIN_SIZE_8M	0x00010000	/*  64k min size */ 
#define MMU_PTE_MIN_SIZE_16M	0x00020000	/* 128k min size */ 
#define MMU_PTE_MIN_SIZE_32M	0x00040000	/* 256k min size */ 
#define MMU_PTE_MIN_SIZE_64M	0x00080000	/* 512k min size */ 
#define MMU_PTE_MIN_SIZE_128M	0x00100000	/*   1M min size */ 
#define MMU_PTE_MIN_SIZE_256M	0x00200000	/*   2M min size */ 
#define MMU_PTE_MIN_SIZE_512M	0x00400000	/*   4M min size */ 
#define MMU_PTE_MIN_SIZE_1G	0x00800000	/*   8M min size */ 
#define MMU_PTE_MIN_SIZE_2G	0x01000000	/*  16M min size */ 
#define MMU_PTE_MIN_SIZE_4G	0x02000000	/*  32M min size */ 

#define MMU_EA_SR		0xf0000000	/* SR field in E.A. */
#define MMU_EA_SR_SHIFT		28		/* */
#define MMU_EA_PAGE_INDEX	0x0ffff000	/* Page Index in E.A. */
#define MMU_EA_PAGE_INDEX_SHIFT	12		/* Page Index shift */
#define MMU_EA_BYTE_OFFSET	0x00000fff	/* Byte Offset in E.A */
#define MMU_EA_API		0x0000fc00	/* abbreviated page index */
#define MMU_EA_API_SHIFT	10		/* api shift in page index */

#define MMU_SR_VSID_MASK	0x00ffffff	/* virtual segment ID */
#define MMU_SR_NB_SHIFT		28

#define MMU_VSID_PRIM_HASH	0x000fffff	/* primary hash value in VSID */

#define MMU_HASH_VALUE_LOW	0x000003ff

#define MMU_HASH_VALUE_HIGH	0x0007fc00

#define MMU_HASH_VALUE_HIGH_SHIFT	10

#define MMU_PTE_HASH_VALUE_HIGH_SHIFT	16
#define MMU_PTE_HASH_VALUE_LOW_SHIFT	6

#define MMU_PTE_VSID_SHIFT	7
#define MMU_PTE_V		0x80000000
#define MMU_PTE_H		0x00000040
#define MMU_PTE_H_SHIFT		6
#define MMU_PTE_API		0x0000003f	/* API field in PTE */
#define MMU_PTE_API_SHIFT	0		/* API shift in PTE */

#endif	/* _WRS_MMU_64BIT */

#define MMU_PTE_RPN		0xfffff000
#define MMU_PTE_RPN_SHIFT	12

#define MMU_PTE_BY_PTEG		0x08

#define MMU_I_ADDR_TRANS	0
#define MMU_D_ADDR_TRANS	1

#define MMU_INST		0x01
#define MMU_DATA		0x02

/*
 * NOTE: this doesn't match with 64-bit implementations,
 * but we use it as is so that valid bit doesn't override PP bits.
 */
#define MMU_STATE_VALID				0x80000000

#define MMU_STATE_VALID_NOT			0x00000000
#define MMU_STATE_WRITABLE			0x00000002
#define MMU_STATE_WRITABLE_NOT			0x00000003
#define MMU_STATE_CACHEABLE			0x00000000
#define MMU_STATE_CACHEABLE_COPYBACK		0x00000000
#define MMU_STATE_CACHEABLE_WRITETHROUGH	0x00000040
#define MMU_STATE_CACHEABLE_NOT			0x00000020
#define MMU_STATE_MEM_COHERENCY			0x00000010
#define MMU_STATE_MEM_COHERENCY_NOT		0x00000000
#define MMU_STATE_GUARDED			0x00000008
#define MMU_STATE_GUARDED_NOT			0x00000000

#define MMU_STATE_SUP_RWX                       0x00000000
#define MMU_STATE_USR_EXE_SUP_RWX               0x00000001
#define MMU_STATE_USR_SUP_RWX                   0x00000002
#define MMU_STATE_USR_SUP_EXE                   0x00000003

/* 
 * the 3 following mask are not supported by the MMU for now
 */
#define MMU_STATE_ACCESS_NOT			0x00000000
#define MMU_STATE_EXECUTE			0x00000000
#define MMU_STATE_EXECUTE_NOT			0x10000000

#define MMU_STATE_MASK_VALID			0x80000000
#define MMU_STATE_MASK_WRITABLE			0x00000003
#define MMU_STATE_MASK_PROTECTION               0x00000003

#define MMU_STATE_MASK_CACHEABLE		0x00000060
#define MMU_STATE_MASK_MEM_COHERENCY		0x00000010
#define MMU_STATE_MASK_GUARDED			0x00000008
#define MMU_STATE_MASK_EXECUTE			0x10000000
#define MMU_STATE_MASK_WIMG_AND_WRITABLE	0x0000007B
#define MMU_STATE_MASK_WIMG                     0x00000078
#define MMU_STATE_MASK_HASH_LEVEL               0x00000040

#define MMU_PPC_PAGE_SIZE			0x00001000


/* Segment Registers */

/* Note: for 64 bit implementations, SR is accessed the same as 32 bit format */

#define MMU_PPC_SEG_REG_NUM     0x00000010

#define MMU_PPC_SR_T            0x80000000      /* T=0 for page, T=1 for I/O */
#define MMU_PPC_SR_KS           0x40000000      /* sup-state protect   (T=0) */
#define MMU_PPC_SR_KP           0x20000000      /* user-state protect  (T=0) */
#define MMU_PPC_SR_N            0x10000000      /* no-execute protect  (T=0) */

#define MMU_PPC_SR_VSID_MASK    0x00ffffff      /* virtual segment ID  (T=0) */
#define MMU_PPC_SR_VSID_SHIFT   0

/*
 * The 603 and 604 use a different VSID generation mechanism.  This is
 * because the 603 does not use a hash table, while the 604 does.  For
 * more information on this look in mmuPpcLib.c
 */

#if ((CPU == PPC603) || (CPU == PPCEC603))
#define MMU_SR_VSID_INCREMENT   0x10
#else
#define MMU_SR_VSID_INCREMENT   0x1
#endif

#define MMU_KERNEL_SR0_VAL      (MMU_PPC_SR_KP | (0 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR1_VAL      (MMU_PPC_SR_KP | (1 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR2_VAL      (MMU_PPC_SR_KP | (2 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR3_VAL      (MMU_PPC_SR_KP | (3 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR4_VAL      (MMU_PPC_SR_KP | (4 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR5_VAL      (MMU_PPC_SR_KP | (5 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR6_VAL      (MMU_PPC_SR_KP | (6 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR7_VAL      (MMU_PPC_SR_KP | (7 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR8_VAL      (MMU_PPC_SR_KP | (8 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR9_VAL      (MMU_PPC_SR_KP | (9 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR10_VAL     (MMU_PPC_SR_KP | (10 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR11_VAL     (MMU_PPC_SR_KP | (11 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR12_VAL     (MMU_PPC_SR_KP | (12 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR13_VAL     (MMU_PPC_SR_KP | (13 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR14_VAL     (MMU_PPC_SR_KP | (14 * MMU_SR_VSID_INCREMENT))
#define MMU_KERNEL_SR15_VAL     (MMU_PPC_SR_KP | (15 * MMU_SR_VSID_INCREMENT))

#define MMU_SR_INVALID_VSID     0x00ffffff

/*
 * XXX - tam - Temporary defines for VmWorks
 * This should be removed when context creation routine vmCtxCreate()
 * takes 2 more arguments: start of VM context and size of VM context.
 */

#define APPL_PD_BASE_ADRS       0x20000000
#define APPL_PD_SIZE            0x40000000

#define APPL_PD_END_ADRS        (APPL_PD_BASE_ADRS + APPL_PD_SIZE - 1)

#define SR_REG_NO_GET(addr)     (((UINT) (addr)) >> MMU_SR_NB_SHIFT)
#define SR_REG_NO_LOW           (SR_REG_NO_GET(APPL_PD_BASE_ADRS))
#define SR_REG_NO_HIGH          (SR_REG_NO_GET(APPL_PD_END_ADRS))

/*
 * IMPORTANT:  If the definition of MMU_PAGE_TBL changes so must this macro.
 * Please don't ignore this!
 */

 /* #define MMU_PPC_PG_TBL_GET(pPageTbl) ((UINT *)(pPageTbl->l1TblPtr.pL1Desc))
  */

#define MMU_PPC_PG_TBL_GET(pPageTbl) ((UINT *)(((MMU_PAGE_TBL *) pPageTbl)->l1TblPtr.pL1Desc))

#define MMU_PPC_TRANS_TBL_NEXT_GET(addr) ((UINT) (addr + (MMU_PPC_SEG_REG_NUM * sizeof(int))))

#ifndef _ASMLANGUAGE

/* Effective Address Definition */

typedef union effectiveAddr             /* effective Address structure */
    {
    void * effAddr;

    struct
	{
	u_int l1index:10;               /* Level 1 Index */
	u_int l2index:10;               /* Level 2 Index */
	u_int po:12;                    /* Page Offset */
	} field;

    } EFFECTIVE_ADDR;

/* Real Address Definition */

typedef union   realAddress     /* Real Address Structure */
    {
    void * realAddr;            /* Real Address */

    struct                      /* Bit field description */
	{
	u_int rpn:20;           /* Real Page Number */
	u_int po:12;            /* Page Offset */
	}field;

    } REAL_ADDRESS;

/* Level 1 Descriptor Definition */

typedef union level_1_desc      /* Level 1 descriptor format */
    {
    u_int l1desc;               /* Level 1 descriptor */

    struct                      /* Bit field desciption */
	{
	u_int l2ba:20;          /* Level 2 table Base Address */
	u_int reserved:11;      /* Reserved */
	u_int v:1;              /* Segment Valid bit */
	} field;

    } LEVEL_1_DESC;

/* Level 1 Table pointer definition */

typedef union   level_1_tbl_ptr /* Level 1 Table pointer structure */
    {
    LEVEL_1_DESC * pL1Desc;     /* Level 1 descriptor table pointer */

    struct                      /* Bit field description */
	{
	u_int l1tb:20;          /* Level 1 table Base */
	u_int l1index:10;       /* Level 1 table Index */
	u_int reserved:2;       /* Reserved */
	} field;

    } LEVEL_1_TBL_PTR;

/* Level 2 descriptor definition */

typedef union level_2_desc      /* Level 2 descriptor format */
    {
    u_int l2desc;               /* Level 2 descriptor */

    struct                      /* Bit field desciption */
	{
	u_int rpn:20;           /* Real Page Number */
	u_int reserved:5;       /* reserved */
	u_int wimg:4;           /* Memory/cache control bit */
	u_int v:1;              /* Page Valid bit */
	u_int pp:2;             /* Page Protection */
	} field;

    } LEVEL_2_DESC;

/* Level 2 Table pointer definition */

typedef union   level_2_tbl_ptr /* Level 2 Table pointer structure */
    {
    LEVEL_2_DESC * pL2Desc;     /* Level 2 descriptor table pointer */

    struct                      /* Bit field description */
	{
	u_int l2tb:20;          /* Level 2 Table Base */
	u_int l2index:10;       /* Level 2 table Index */
	u_int reserved:2;       /* Reserved */
	} field;

    } LEVEL_2_TBL_PTR;

/* Page Table Definition */

/*
 * IMPORTANT:  If the defintion of this structure changes so must the macro
 * MMU_PPC_PG_TBL_GET().
 */

typedef struct mmuPageTblStruct
    {
    LEVEL_1_TBL_PTR     l1TblPtr;
    } MMU_PAGE_TBL;

#ifdef _WRS_MMU_64BIT

/* PTE for 64-bit implementations */

typedef union pte		/* PTE structure */
    {
    struct			/* bit field description */
	{
	u_int hvsid;		/* Virtual Segment ID (high word) */
	u_int vsid:20;		/* Virtual Segment ID */
	u_int api:5;		/* Abbreviated page index */
	u_int reserved0:5;	/* reserved */
	u_int h:1;		/* Hash function identifier */
	u_int v:1;		/* entry valid (v=1) or invalid (v=0) */
	u_int hrpn;		/* Physical page number (high word) */
	u_int rpn:20;		/* Physical page number */
	u_int reserved1:3;	/* reserved */
	u_int r:1;		/* Referenced bit */
	u_int c:1;		/* Changed bit */
	u_int wimg:4;		/* Memory/cache control bit */
	u_int reserved2:1;	/* reserved */
	u_int pp:2;		/* Page protection bits */
	} field;
    struct			/* word description */
	{
	u_int hword0;		/* hword 0 */
	u_int word0;		/* word 0 */
	u_int hword1;		/* hword 1 */
	u_int word1;		/* word 1 */
	} bytes;
    } PTE;
#else	/* !_WRS_MMU_64BIT */

/* PTE for 32-bit implementations */

typedef union pte		/* PTE structure */
    {
    struct			/* bit field desciption */
	{
	u_int v:1;		/* entry valid (v=1) or invalid (v=0) */
	u_int vsid:24;		/* Virtual Segment ID */
	u_int h:1;		/* Hash function identifier */
	u_int api:6;		/* Abbreviated page index */
	u_int rpn:20;		/* Physical page number */
	u_int reserved1:3;	/* reserved */
	u_int r:1;		/* Referenced bit */
	u_int c:1;		/* Changed bit */
	u_int wimg:4;		/* Memory/cache control bit */
	u_int reserved2:1;	/* reserved */
	u_int pp:2;		/* Page protection bits */
	} field;
    struct			/* word description */
	{
	u_int word0;		/* word 0 */
	u_int word1;		/* word 1 */
	} bytes;
    } PTE;
#endif	/* _WRS_MMU_64BIT */

typedef struct pteg		/* PTEG structure */
    {
    PTE pte[MMU_PTE_BY_PTEG];
    } PTEG;

typedef union sr
    {
    u_int value;                        /* SR value */

    struct
	{
	u_int t:1;                      /* SR format flag */
	u_int ks:1;                     /* Supervisor-state protection key */
	u_int kp:1;                     /* User-state protection key */
	u_int n:1;                      /* No-execute protection */
	u_int reserved:4;               /* reserved */
	u_int vsid:24;                  /* Virtual segment Id */
	} bit;

    } SR;

typedef struct mmuTransTblStruct
    {
	u_int   vsidBaseNum;

	/*
	 * XXX - tam -
	 * DO NOT CHANGE THE ORDER of the following array declarations.
	 * Some code in src/arch/ppc/ depend on scSrTable following srTable
	 * and pPageTbl following scSrTable.
	 */

	SR      srTable[MMU_PPC_SEG_REG_NUM];   /* default SR table */
	SR      scSrTable[MMU_PPC_SEG_REG_NUM]; /* SR table for system calls */

	MMU_PAGE_TBL * pageTbl;                /* two level page table */

    } MMU_TRANS_TBL;

typedef struct mmuHashTblStruct
    {
	u_int   hTabOrg;
	u_int   hTabMask;		/* HTABSIZE for _WRS_MMU_64BIT */
	u_int   pteTableSize;
    } MMU_HASH_TBL;


typedef union ea
    {
    u_int effAddr;			/* effective address */

    struct
	{
	u_int srSelect:4;		/* SR select */
	u_int pageIndex:16;		/* Page index */
	u_int byteOffset:12;		/* Byte offset */
	} field;

    } EA;

void mmuPpcInstMissHandler (void);
void mmuPpcDataLoadMissHandler (void);
void mmuPpcDataStoreMissHandler (void);

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuPpcLibh */
