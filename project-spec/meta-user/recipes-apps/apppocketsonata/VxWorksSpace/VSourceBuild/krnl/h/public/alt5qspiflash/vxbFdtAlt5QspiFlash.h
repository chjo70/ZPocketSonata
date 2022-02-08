/*  vxbFdtAlt5QspiFlash.h - Altera Soc Gen 5 QSPI Flash Head File */

/*
 * Copyright (c) 2014-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
22jan17,ffu  fixed controller registers access issues (V7STO-523)
13may15,txu  fix V7STO-358 : wrong include after extern "C"
29aug14,txu  modify to remove compile warning (US43884)
15may14,ywu  Created from sysQspiFlashMem.h (US38998)
*/

#ifndef __INCvxbFdtAlt5QspiFlashh
#define __INCvxbFdtAlt5QspiFlashh

#include <vxbFlash.h>
#include <vxbFlashCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/*
 * The following defines are for N25Q00AA only, customer may need to change them
 * with replaced flash chip
*/

#define QSPIFLASH_CHIP_NAME "Micron N25Q00AA"

#define ENABLE_4BYTES_MODE

/* qspi flash controller timeout value */

#define QSPI_TIMEOUT    50000

/* 3s for sector erase */

#define QSPI_TIMEOUT_SECTORERASE        3000000

/* 0.8s for subsector erase */

#define QSPI_TIMEOUT_SUBSECTORERASE     800000

/* 480s for die erase */

#define QSPI_TIMEOUT_DIEERASE           480000000
#define QSPI_TIMEOUT_READ               5000            /* 5ms for read */

/* 5ms for page write */

#define QSPI_TIMEOUT_PAGEWRITE          5000

#define QSPI_FLASH_MEM_SIZE                  (0x08000000)   /* SZ_128M */
#define QSPI_FLASH_SECTOR_SIZE               (0x00010000)   /* SZ_64K */
#define QSPI_FLASH_PAGE_SIZE                 (0x100)
#define QSPI_FLASH_DEVICE_SUBSECTOR_SIZE     (0x1000)

/* Common defines */

/* Flash Command in Execute status */

#define QSPI_FLASH_CMD_CTRL_EXEC_STAT   0x2

#define QSPI_IND_WR_XFER_EN             0x1
#define QSPI_IND_WR_XFER_CANCEL         (0x1 << 1)
#define QSPI_IND_WR_XFER_DONE           (0x1 << 5)



#define QSPI_IRQ_MASK_UNDER             (0x1 << 1)
#define QSPI_IRQ_MASK_IND_DONE          (0x1 << 2)
#define QSPI_IRQ_MASK_IND_RD_REJECT     (0x1 << 3)
#define QSPI_IRQ_MASK_WATERMARK         (0x1 << 6)
#define QSPI_IRQ_MASK_IND_RD_OVER       (0x1 << 12)
#define QSPI_IRQ_MASK_WR_PROTECT        (0x1 << 12)

#define QSPI_IRQ_MASK_RD                (QSPI_IRQ_MASK_IND_DONE | \
                                        QSPI_IRQ_MASK_IND_RD_REJECT | \
                                        QSPI_IRQ_MASK_WATERMARK | \
                                        QSPI_IRQ_MASK_IND_RD_OVER)

#define QSPI_IRQ_MASK_WR                (QSPI_IRQ_MASK_WR_PROTECT | \
                                        QSPI_IRQ_MASK_IND_DONE         | \
                                        QSPI_IRQ_MASK_WATERMARK        | \
                                        QSPI_IRQ_MASK_UNDER)

#define QSPI_SRAM_FILL_RD_MASK          0xFFFF
#define QSPI_SRAM_FILL_WR_MASK          0xFFFF0000

#define QSPI_DEV_SIZE_MASK              0xF
#define QSPI_DEV_SIZE_4BYTES            0x3
#define QSPI_DEV_SIZE_3BYTES            0x2

#ifdef ENABLE_4BYTES_MODE
#   define QSPI_DEV_ADDRESS_SIZE    QSPI_DEV_SIZE_4BYTES
#else
#   define QSPI_DEV_ADDRESS_SIZE    QSPI_DEV_SIZE_3BYTES
#endif /* ENABLE_4BYTES_MODE */

#define QSPI_DEV_SIZEDEFAULT    (QSPI_DEV_ADDRESS_SIZE | \
                                (pDrvCtrl->mtd.uPageSize << 4) | \
                                (QSPI_FLASH_DEVICE_SUBSECTOR_SIZE << 8))

/* spi command instruction */

#define QSPI_FLASH_SR_WIP          0x01  /* write in progress */
#define QSPI_FLASH_SR_WEL          0x02  /* Flash Commands */
#define QSPI_FLASH_CMD_WRSR        0x01  /* Write status register */
#define QSPI_FLASH_CMD_PP          0x02  /* Page program */
#define QSPI_FLASH_CMD_READ        0x03  /* Normal read data bytes */
#define QSPI_FLASH_CMD_WRDS        0x04  /* Write disable */
#define QSPI_FLASH_CMD_RDSR        0x05  /* Read status register */
#define QSPI_FLASH_CMD_WE          0x06  /* Write enable */
#define QSPI_FLASH_CMD_FAST_READ   0x0B  /* Fast read data bytes */
#define QSPI_FLASH_CMD_BE_4K       0x20  /* Erase 4KiB block */
#define QSPI_FLASH_CMD_DUAL_READ   0x3B  /* Dual read data bytes */
#define QSPI_FLASH_CMD_BE_32K      0x52  /* Erase 32KiB block */
#define QSPI_FLASH_CMD_QUAD_READ   0x6B  /* Quad read data bytes */
#define QSPI_FLASH_CMD_ERASE_SUS   0x75  /* Erase suspend */
#define QSPI_FLASH_CMD_ERASE_RES   0x7A  /* Erase resume */
#define QSPI_FLASH_CMD_RDID        0x9F  /* Read JEDEC ID */
#define QSPI_FLASH_CMD_BE          0xC7  /* Erase whole flash block */
#define QSPI_FLASH_CMD_SE          0xD8  /* Sector erase (64KB) */
#define QSPI_FLASH_CMD_DE          0xC4  /* Die erase (32MB) */
#define QSPI_FLASH_CMD_READ_FLAG_STATUS         0x70  /* Read Flag Status */
#define QSPI_FLASH_CMD_RDFLAG_4BYTES            0x1   /* 4 Bytes Mode Bit */
#define QSPI_FLASH_CMD_RDSR_WEL    0x02  /* Write Enable Latch Bit */
#define QSPI_FLASH_CMD_ENTER4BYTES 0xB7  /* Enter 4 Bytes Mode */
#define QSPI_FLASH_CMD_EXIT4BYTES  0xE9  /* EXIT 4 Bytes Mode */
#define QSPI_FLASH_CMD_RESET_ENABLE     0x66 /* Flash Reset Enable */
#define QSPI_FLASH_CMD_RESET_MEMORY     0x99 /* Flash Reset Memory */

/* Flag Status Register Bit Ready */

#define QSPI_FLASH_CMD_FLAG_STATUS_READY        0x80

/* register definition */

#define QSPI_CONFIG                     0x00
#define QSPI_DEV_RD_CFG                 0x04
#define QSPI_DEV_WR_CFG                 0x08
#define QSPI_DEV_DELAY                  0x0C
#define QSPI_RD_DATA_CAPTURE            0x10
#define QSPI_DEV_SIZE                   0x14
#define QSPI_SRAM_PART_CFG              0x18
#define QSPI_IND_AHB_ADDR_TRIGGER       0x1C
#define QSPI_DMA_PERIPH_CONFIG          0x20
#define QSPI_REMAP_ADDR                 0x24
#define QSPI_MODE_BIT_CONFIG            0x28
#define QSPI_SRAM_FILL                  0x2C
#define QSPI_TX_THRESH                  0x30
#define QSPI_RX_THRESH                  0x34
#define QSPI_IRQ_STATUS                 0x40
#define QSPI_IRQ_MASK                   0x44
#define QSPI_LOWER_WR_PROT              0x50
#define QSPI_UPPER_WR_PROT              0x54
#define QSPI_WR_PROT_CTRL               0x58
#define QSPI_IND_RD_XFER                0x60
#define QSPI_IND_RD_XFER_WATERMARK      0x64
#define QSPI_IND_RD_XFER_START          0x68
#define QSPI_IND_RD_XFER_NUM_BYTES      0x6C
#define QSPI_IND_WR_XFER                0x70
#define QSPI_IND_WR_XFER_WATERMARK      0x74
#define QSPI_IND_WR_XFER_START          0x78
#define QSPI_IND_WR_XFER_NUM_BYTES      0x7C
#define QSPI_FLASH_CMD_CTRL             0x90
#define QSPI_FLASH_CMD_ADDR             0x94
#define QSPI_FLASH_RD_DATA_LOWER        0xA0
#define QSPI_FLASH_RD_DATA_UPPER        0xA4
#define QSPI_FLASH_WR_DATA_LOWER        0xA8
#define QSPI_FLASH_WR_DATA_UPPER        0XAC
#define QSPI_MODULE_ID                  0xFC


#define QSPI_CONFIG_EN                  (0x1 << 0)
#define QSPI_CONFIG_CLK_POL             (0x1 << 1)
#define QSPI_CONFIG_CLK_PHASE           (0x1 << 2)
#define QSPI_CONFIG_DIRECT_ACCESS       (0x1 << 7)
#define QSPI_CONFIG_LEGACY              (0x1 << 8)
#define QSPI_CONFIG_SEL4TO16            (0x1 << 9)
#define QSPI_CONFIG_PERI_CS_SHIFT_MSK   (0xF << 10)
#define QSPI_CONFIG_PERI_CS_SHIFT(n)    ((n & 0xF) << 10)
#define QSPI_CONFIG_WP                  (0x1 << 14)
#define QSPI_CONFIG_DMA                 (0x1 << 15)

#define QSPI_CONFIG_EN_REMAP            (0x1 << 16)
#define QSPI_CONFIG_ENTERXIPNEXTRD      (0x1 << 17)
#define QSPI_CONFIG_ENTERXIPIMM         (0x1 << 18)
#define QSPI_CONFIG_BAUD_MSK            (0xF << 19)
#define QSPI_CONFIG_BAUD(n)             ((n & 0xF) << 19)

#define QSPI_CONFIG_IDLE                (0x1U << 31)

#define QSPI_CS_SHIFT_DEFAULT           14
#define QSPI_CONFIG_DEFAULT             (QSPI_CONFIG_CLK_POL | \
                                         QSPI_CONFIG_CLK_PHASE | \
										 QSPI_CONFIG_PERI_CS_SHIFT(QSPI_CS_SHIFT_DEFAULT))

#define QSPI_CONFIG_DEFAULT_MSK         (QSPI_CONFIG_EN |  \
										QSPI_CONFIG_CLK_POL |  \
										QSPI_CONFIG_CLK_PHASE |  \
										QSPI_CONFIG_DIRECT_ACCESS |  \
										QSPI_CONFIG_LEGACY |  \
										QSPI_CONFIG_SEL4TO16 |  \
										QSPI_CONFIG_PERI_CS_SHIFT_MSK |  \
										QSPI_CONFIG_WP |  \
										QSPI_CONFIG_DMA |  \
										QSPI_CONFIG_EN_REMAP |  \
										QSPI_CONFIG_ENTERXIPNEXTRD |  \
										QSPI_CONFIG_ENTERXIPIMM |  \
										QSPI_CONFIG_BAUD_MSK)

#define QSPI_DEV_RD_CFG_RD              0x3
#define QSPI_DEV_RD_CFG_FAST_RD         0xb
#define QSPI_DEV_RD_CFG_QUAD_FAST_RD    0x6b
#define QSPI_DEV_RD_CFG_QUAD_IO_FAST_RD 0xeb

#define QSPI_DEV_RD_CFG_INST_SINGLE     (0x0 << 8)
#define QSPI_DEV_RD_CFG_INST_DUAL       (0x1 << 8)
#define QSPI_DEV_RD_CFG_INST_QUAD       (0x2 << 8)

#define QSPI_DEV_RD_CFG_ADDR_SINGLE     (0x0 << 12)
#define QSPI_DEV_RD_CFG_ADDR_DUAL       (0x1 << 12)
#define QSPI_DEV_RD_CFG_ADDR_QUAD       (0x2 << 12)

#define QSPI_DEV_RD_CFG_DATA_SINGLE     (0x0 << 16)
#define QSPI_DEV_RD_CFG_DATA_DUAL       (0x1 << 16)
#define QSPI_DEV_RD_CFG_DATA_QUAD       (0x2 << 16)

#define QSPI_DEV_RD_CFG_NOODER          (0x0 << 20)
#define QSPI_DEV_RD_CFG_ODER            (0x1 << 20)
#define QSPI_DEV_RD_CFG_DUMMY(n)        (n << 24)

#define QSPI_DEV_RD_CFG_DEFAULT         (QSPI_DEV_RD_CFG_RD | \
                                        QSPI_DEV_RD_CFG_INST_SINGLE | \
                                        QSPI_DEV_RD_CFG_ADDR_SINGLE | \
                                        QSPI_DEV_RD_CFG_DATA_SINGLE | \
                                        QSPI_DEV_RD_CFG_ODER | \
                                        QSPI_DEV_RD_CFG_DUMMY(9))

#define QSPI_DEV_RD_CFG_QUAD_IO_FAST    (QSPI_DEV_RD_CFG_QUAD_IO_FAST_RD | \
                                        QSPI_DEV_RD_CFG_INST_SINGLE | \
                                        QSPI_DEV_RD_CFG_ADDR_QUAD | \
                                        QSPI_DEV_RD_CFG_DATA_QUAD | \
                                        QSPI_DEV_RD_CFG_DUMMY(10))

#define QSPI_DEV_WR_CFG_OP              0x2

#define QSPI_DEV_WR_CFG_ADDR_SINGLE     (0x0 << 12)
#define QSPI_DEV_WR_CFG_ADDR_DUAL       (0x1 << 12)
#define QSPI_DEV_WR_CFG_ADDR_QUAD       (0x2 << 12)

#define QSPI_DEV_WR_CFG_DATA_SINGLE     (0x0 << 16)
#define QSPI_DEV_WR_CFG_DATA_DUAL       (0x1 << 16)
#define QSPI_DEV_WR_CFG_DATA_QUAD       (0x2 << 16)
#define QSPI_DEV_WR_CFG_DUMMY(n)        (n << 24)

#define QSPI_DEV_WR_CFG_DEFAULT         (QSPI_DEV_WR_CFG_OP | \
                                         QSPI_DEV_WR_CFG_ADDR_SINGLE | \
                                         QSPI_DEV_WR_CFG_DATA_SINGLE | \
                                         QSPI_DEV_WR_CFG_DUMMY(9))

#define QSPI_IND_RD_XFER_EN             0x1
#define QSPI_IND_RD_XFER_CANCEL         (0x1 << 1)
#define QSPI_IND_RD_XFER_FULL           (0x1 << 3)
#define QSPI_IND_RD_XFER_DONE           (0x1 << 5)

/* typedef */
typedef union
    {
    UINT32 data;
    struct
        {
#ifdef ARMBE8
        UINT32 cmd_opcode_fld :8;        /* 31:24 */
        UINT32 enb_read_data_fld :1;     /* 23    */
        UINT32 num_rd_data_bytes_fld :3; /* 22:20 */
        UINT32 enb_comd_addr_fld :1;     /* 19    */
        UINT32 enb_mode_bit_fld :1;      /* 18    */
        UINT32 num_addr_bytes_fld :2;    /* 17:16 */
        UINT32 enb_write_data_fld :1;    /* 15    */
        UINT32 num_wr_data_bytes_fld :3; /* 14:12 */
        UINT32 num_dummy_bytes_fld :5;   /* 11:7  */
        UINT32 resv_fld :5;              /* 6:2   */
        UINT32 cmd_exec_status_fld :1;   /* 1     */
        UINT32 cmd_exec_fld :1;          /* 0     */
#else
        UINT32 cmd_exec_fld :1;          /* 0     */
        UINT32 cmd_exec_status_fld :1;   /* 1     */
        UINT32 resv_fld :5;              /* 6:2   */
        UINT32 num_dummy_bytes_fld :5;   /* 11:7  */
        UINT32 num_wr_data_bytes_fld :3; /* 14:12 */
        UINT32 enb_write_data_fld :1;    /* 15    */
        UINT32 num_addr_bytes_fld :2;    /* 17:16 */
        UINT32 enb_mode_bit_fld :1;      /* 18    */
        UINT32 enb_comd_addr_fld :1;     /* 19    */
        UINT32 num_rd_data_bytes_fld :3; /* 22:20 */
        UINT32 enb_read_data_fld :1;     /* 23    */
        UINT32 cmd_opcode_fld :8;        /* 31:24 */
#endif /* ARMBE8 */
        } val;
    } MAP_flash_cmd_ctrl_reg_t;

/* SPI_NOR_FLASH device struct */

typedef struct qspi_flash_dev
    {
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    VXB_DEV_ID    pDev;
#else
    VXB_DEVICE_ID pDev;
#endif
    void *                      pRegHandle;
    void *                      pCsHandle;
    ULONG                       uRegBase;   /* register base */
    ULONG                       uCsBase;    /* CS base */
    char                        type [MAX_DRV_NAME_LEN];
    SEM_ID                      muteSem;    /* operation semaphore */
    FLASH_CHIP                  mtd;        /* FileSystem used */
    } QSPI_FLASH_DEV;

#define QSPI_REG_READ_32(pDrvCtrl, member)                                     \
    vxbRead32 ((pDrvCtrl)->pRegHandle,                                         \
        (void *)((pDrvCtrl)->uRegBase + (ULONG) (member)))

#define QSPI_REG_WRITE_32(pDrvCtrl, member, data)                              \
    vxbWrite32 ((pDrvCtrl)->pRegHandle,                                        \
        (void *)((pDrvCtrl)->uRegBase + (ULONG) (member)),                     \
        (ULONG) (data))

#define QSPI_DATA_READ_32(pDrvCtrl)                                     \
    vxbRead32 ((pDrvCtrl)->pCsHandle,                                         \
        (void *)((pDrvCtrl)->uCsBase))

#define QSPI_DATA_WRITE_32(pDrvCtrl, data)                              \
    vxbWrite32 ((pDrvCtrl)->pCsHandle,                                        \
        (void *)((pDrvCtrl)->uCsBase),                     \
        (ULONG) (data))

#define QSPI_SEM_TAKE(sem)      \
        do { \
           if (sem != NULL)    \
           (void) semTake (sem, WAIT_FOREVER);    \
        } while (0)

#define QSPI_SEM_GIVE(sem)      \
        do { \
           if (sem != NULL)    \
           (void) semGive (sem);      \
        } while (0)

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbFdtAlt5QspiFlashh */
