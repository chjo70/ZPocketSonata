/* vxbNorFlash.h - NOR-Flash Driver Head File */

/*
 * Copyright (c) 2011, 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
21nov16,ffu  add LP64 support in TFFS layer (F4496)
03mar16,dee  fix diab compiler warning
10feb14,ywu  fix improper use of _WRS_CONFIG_FDT
16jan14,ywu  adopt to vxBus gen2
30dec11,x_z  created.
*/

#ifndef __INCvxbNorFlashh
#define __INCvxbNorFlashh

#ifdef __cplusplus
extern "C" {
#endif

/* port/Chip Width/Mode */

#define NOR_FLASH_WIDTH_CODE(width) ((width) >> 3)
#define NOR_FLASH_WIDTH(code)       ((code) << 3)
#define NOR_FLASH_WIDTH_8BIT        8
#define NOR_FLASH_WIDTH_16BIT       16
#define NOR_FLASH_WIDTH_32BIT       32

#define NOR_FLASH_WIDTH_8BIT_CODE   NOR_FLASH_WIDTH_CODE (8)
#define NOR_FLASH_WIDTH_16BIT_CODE  NOR_FLASH_WIDTH_CODE (16)
#define NOR_FLASH_WIDTH_32BIT_CODE  NOR_FLASH_WIDTH_CODE (32)

#define NOR_FLASH_MIN_WIDTH         NOR_FLASH_WIDTH_8BIT
#define NOR_FLASH_MAX_WIDTH         NOR_FLASH_WIDTH_32BIT

#define NOR_FLASH_MIN_WIDTH_CODE    NOR_FLASH_WIDTH_8BIT_CODE
#define NOR_FLASH_MAX_WIDTH_CODE    NOR_FLASH_WIDTH_32BIT_CODE

/* byte Swap  */

#if (_BYTE_ORDER == _BIG_ENDIAN)

#define CPU_TO_NOR_FLASH_16(bigEndian, x) \
    ((bigEndian != 0) ? (UINT16) (x) : vxbSwap16 (x))
#define CPU_TO_NOR_FLASH_32(bigEndian, x) \
    ((bigEndian != 0) ? (UINT32) (x) : vxbSwap32 (x))

#define NOR_FLASH_LE16_TO_CPU(x)  vxbSwap16 (x)
#define NOR_FLASH_LE32_TO_CPU(x)  vxbSwap32 (x)
#else
#define CPU_TO_NOR_FLASH_16(bigEndian, x) \
    ((bigEndian == 0) ? (UINT16) (x) : vxbSwap16 (x))
#define CPU_TO_NOR_FLASH_32(bigEndian, x) \
    ((bigEndian == 0) ? (UINT32) (x) : vxbSwap32 (x))

#define NOR_FLASH_LE16_TO_CPU(x)  ((UINT16) (x))
#define NOR_FLASH_LE32_TO_CPU(x)  ((UINT32) (x))
#endif /* _BIG_ENDIAN */

#define NOR_FLASH_16_TO_CPU(bigEndian, x) CPU_TO_NOR_FLASH_16 (bigEndian, x)
#define NOR_FLASH_32_TO_CPU(bigEndian, x) CPU_TO_NOR_FLASH_32 (bigEndian, x)

/* Flash Device Region Descriptor */

#define NOR_FLASH_REGION_NUM_MAX    8
typedef struct nor_flash_reg_desc
    {
    ULONG   start;
    ULONG   size;
    UINT32  blkSize;
    } NOR_FLASH_REG_DESC;

/* NOR Flash Information */

typedef struct nor_flash_info
    {

    /* generic information */
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    VXB_DEV_ID              pDev;
#else
    VXB_DEVICE_ID           pDev;
#endif
    UINT8                   chipName[FLASH_CHIP_NAME_LEN];

    /* vxBus driver information */

    ULONG                   baseAdrs;   /* flash base address */
    UINT32                  maxSize; /* address space size */
    UINT32                  cfiPrior; /* default probe mode */

    /* Chip information */

    /* Default configuration */

    UINT32                  portWidthDef; /* system bus width */
    UINT32                  chipWidthDef; /* maximum chip bus width supported */
    UINT32                  chipNumDef;   /* number for interleaving chips  */
    UINT32                  bigEndianDef; /* CFI endian */

    /* Runtime configuration */

    UINT8                   portWidth;
    UINT8                   chipWidth;
    UINT8                   chipNum;
    UINT8                   chipMode;   /* current chip work mode */
    UINT32                  bigEndian;

    /* Chip features */

    UINT32                  eraseSize;  /* size of fixed erase block in byte */
    UINT32                  chipSize;   /* Flash chip size in byte */
    UINT32                  wrBufSize;  /* size of fixed write buffer in byte */
    UINT32                  wrBufWordCntMin;    /* mimnum word count for */
                                                /* write to buffer operation */
    NOR_FLASH_REG_DESC      regTbl[NOR_FLASH_REGION_NUM_MAX];
    void *                  pCmdSetInfo;  /* command set information */

    /* routines for vxBus driver */

    void (*rst)
        (
        struct nor_flash_info * pFlashInfo
        );

    STATUS (*pg)
        (
        struct nor_flash_info * pFlashInfo,
        ULONG                   adrs,   /* offset to Flash */
        UINT32                  data    /* data to be written */
        );

    STATUS (*bufWr)
        (
        struct nor_flash_info * pFlashInfo,
        ULONG                   blkAdrs,    /* block address to Flash */
        ULONG                   adrs,       /* start address to Flash */
        UINT32                  cnt,        /* word count */
        char *                  pBuf        /* buffer to be written */
        );

    STATUS (*blkEra)
        (
        struct nor_flash_info * pFlashInfo,
        ULONG                   blkAdrs /* block address to Flash */
        );

    STATUS (*blkLock)
        (
        struct nor_flash_info * pFlashInfo,
        ULONG                   blkAdrs, /* block address to Flash */
        BOOL                    lock     /* TRUE- lock FALSE - unlock */
        );

    STATUS (*blkLockQry)
        (
        struct nor_flash_info * pFlashInfo,
        ULONG                   blkAdrs, /* block address to Flash */
        BOOL *                  pLock    /* TRUE- lock FALSE - unlock */
        );

    /* routines  for libraries */

    STATUS  (*probe)
        (
        struct nor_flash_info * pFlashInfo
        );

    STATUS  (*chipEna)
        (
        struct nor_flash_info * pFlashInfo,
        BOOL                    enable  /* TRUE- enable FALSE - disable*/
        );

    void    (*dataWr)
        (
        struct nor_flash_info * pFlashInfo,
        ULONG                   adrs,   /* actual address */
        UINT32                  data    /* actual data */
        );

    UINT32  (*dataRd)
        (
        struct nor_flash_info * pFlashInfo,
        ULONG                   adrs,   /* actual address */
        UINT32                  flag    /* access type defined later */
        );

    STATUS  (*dataComp)
        (
        struct nor_flash_info * pFlashInfo,
        ULONG                   adrs,   /* source address */
        UINT32                  cnt,    /* word count */
        char *                  pBuf,   /* buffer to be compared */
        UINT32                  flag    /* access type defined later */
        );
    } NOR_FLASH_INFO;

#define NOR_FLASH_ACCESS_TYPE_IO    0x1 /* access to IO(Flash) */
#define NOR_FLASH_ACCESS_TYPE_SWAP  0x2 /* access with swapped data */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbNorFlashh */

