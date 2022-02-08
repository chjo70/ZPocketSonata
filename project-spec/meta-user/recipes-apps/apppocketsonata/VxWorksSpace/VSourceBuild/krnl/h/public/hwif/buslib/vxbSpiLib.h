/* vxbSpiLib.h - SPI bus header file for vxBus */

/*
 * Copyright (c) 2012-2013, 2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07jul17,msx  add dummy and address length in struct SPI_TRANSFER
             add data stripe mode (F9215)
13jun17,l_z  add rxNbits to SPI_TRANSFER (F9216)
12jan17,mw1  add field "base" in struct "spiTransfer" (US89250)
16mar15,y_f  added SPI mode defines. (V7PRO-1908)
22nov13,hll  Remove not necessary definiton of vxbFdtLib.h(WIND00445019).
22oct12,y_y  created
*/

#ifndef __INCvxbSpiLibh
#define __INCvxbSpiLibh

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

/* defines */

/* SPI device mode defines */

/* clock phase */

#define SPI_CKPHA           0x01

/* clock polarity */

#define SPI_CKPOL           0x02

#define SPI_MODE_0          (0 | 0)

#define SPI_MODE_1          (0 | SPI_CKPHA)

#define SPI_MODE_2          (SPI_CKPOL | 0)

#define SPI_MODE_3          (SPI_CKPOL | SPI_CKPHA)

/* CS active high: active-low; normal */

#define SPI_CSPOL_HIGH      0x04

#define SPI_LSB_FIRST       0x08

#define SPI_LOOP            0x10

#define SPI_FULL_DUPLEX     0x20

/* SPI controller works at polling mode */

#define SPI_POLLING         0x40

/* two or more SPI devices are connected in parallel */

#define SPI_PARALLEL        0x80

/* address for readm command is single bit transfer */

#define SPI_READ_11X        0x100

/* data stripe for dual parallel flash data transfer */

#define SPI_DATA_STRIPE     0x200


/* Ceiling division - not the fastest way, but safer in terms of overflow */

#define DIV_CEIL(x,y)       (((x)/(y)) + ((((((x)/(y)))*(y)) == (x)) ? 0 : 1))

/* typedefs */

/* SPI Bit Order */

/* 
 * Reverse data mode. Determines the receive and transmit character bit order.
 */

typedef enum spiBitOrder
    {
    MSB_FIRST = 1,
    LSB_FIRST = 0
    } spiBitOrder;

/* CS Polarity */

typedef enum spiCsPol
    {
    HIGH_ACTIVE = 1,
    LOW_ACTIVE = 0
    } spiCsPol;

/*
 * The vxbSpiDevInfo struct used to store the SPI device feature, such as
 * chipSelect, spi_device mode,etc.
 */

typedef struct vxbSpiDevInfo
    {
    /* SPI device name, used for match the corresponding driver */

    char *  deviceName;

   /* connect on which CS */

    UINT8   chipSelect;

    /* the bit width per words */

    UINT8   bitWidth;

    /* the maximum work frequency of the SPI device */

    UINT32  devFreq;

    /* device mode - see SPI device mode defines */

    UINT32  mode;

    /* the number of SPI devices in a group */

    UINT32  chipNum;

    /*
     * used data lines
     * For SPI devices, the value must be 1. For QSPI devices, the value
     * can be 1, 2 and 4.
     */

    UINT32  dataLines;
    }SPI_HARDWARE;

/*
 * The spiTransfer struct used to store the SPI transfer data info,
 * the spi device driver will fill this struct.
 */

typedef struct spiTransfer 
    {
    UINT8 * txBuf;    /* data to be written, or NULL */
    UINT8 * rxBuf;    /* data to be read, or NULL */
    UINT32  txLen;    /* size of tx buffers in bytes */
    UINT32  rxLen;    /* size of rx buffers in bytes */
    UINT32  rxNbits;  /* receive number bits */
    UINT32  addrLen;  /* address width:3 bytes or 4 bytes */
    UINT32  dummy;    /* dummy clock cycles */
    UINT32  usDelay;
    UINT32  base;     /* flash base address of transfer */
    } SPI_TRANSFER;

/* This struct saves SPI master constraints */

#define SPI_MASTER_TRANS_LIMIT  0x01    /* have trans length limit */
#define SPI_MASTER_LINEAR_READ  0x02    /* support linear read mode */

#define SPI_TRANS_LIMIT         SPI_MASTER_TRANS_LIMIT  /* for compatibility */

typedef struct vxbSpiMasterSpecial
    {
    UINT32  flag;
    UINT32  windowSize;
    char *  linearBase;
    size_t  linearSize;
    void *  pArg;
    }VXB_SPI_MAST_SPEC;
    
IMPORT STATUS vxbSpiDevXfer(VXB_DEV_ID pDev, SPI_HARDWARE * pChild, SPI_TRANSFER * transfer);

/* function declarations */

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#include <hwif/methods/vxbSpiMethod.h>

#endif /* __INCvxbSpiLibh */
