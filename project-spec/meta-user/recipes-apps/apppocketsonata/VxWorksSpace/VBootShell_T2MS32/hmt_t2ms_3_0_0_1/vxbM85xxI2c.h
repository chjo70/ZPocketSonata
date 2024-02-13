/* COPYRIGHT *****************************************************************
 *
 *   Copyright (c) 2015 Curtiss-Wright. All rights reserved. 
 *   This Source Code is the Property of Curtiss-Wright and can only be
 *   used in accordance with Source Code License Agreement(s) of Curtiss-Wright
 *   or any of its subsidiaries.
 *   
 * END COPYRIGHT *************************************************************/

/* FILE HEADER ***************************************************************
 * Product Name:
 *
 * %name:          vxbM85xxI2c.h %
 * %version:       64_1 %
 * %instance:      kanata_1 %
 * %created_by:    tissa %
 * %date_created:  Mon Dec 07 17:30:25 2015 %
 *
 * Originator:     tissa
 * Date created:   Mon Jun 16 14:26:35 2009
 *
 * Description: Freescale M85xx CPU family I2C Module driver header file.
 *
 * Notes:
 *
 * History:
 *      08-Dec-2015 TI; Task #47642; CR#49630
 *         Port to 64bit
 *      04-Mar-2015 WW; Task#46371 ; CR#48098 
 *         Port to VxWorks 7  
 *      20-Mar-2013 TI/WW; Task #41527; CR#34373
 *         Added Alert Response Address (ARA) read needed for the LF varaint
 *      18-Aug-2011 TI; Task kanata#36490 CR#35476  
 *         Enhanced I2C Read/Write error handling.
 *      17-Aug-2011 TI; Task kanata#36487 CR#37904 
 *         Added M85XX_I2C_MAX_TOGGLE, and M85XX_I2C_HW_INIT_DELAY.
 *      16-Feb-2010 TI; Task#30906 ; CR#28282 
 *         -Moved the I2C bus specific data structure to be an element in the
 *          driver module structure sM85xx_I2C_DRV.
 *         -Moved the structure sM85xx_I2C_DRV definition from driver's source code
 *          file vxbM85xxI2c.c
 *      08-Sep-2009 TI; Task #29223; CR#28282
 *         Added M85XX_I2C_MPX_FREQ_DIVIDER_1 & M85XX_I2C_MPX_FREQ_DIVIDER_2
 *      17-JUL-2009 TI; Task#28873 ; CR#28281
 *         Created based on _dsmI2c8641.h v6
 *
 * END FILE HEADER ***********************************************************/
#ifndef _vxbM85xxI2c_H
#define _vxbM85xxI2c_H

#ifdef __cplusplus
extern "C" {
#endif

    /*
     * Global I2C defines
     */
    #define M85XX_I2C_ADDR_RW_SHIFT       1
    #define M85XX_I2C_ADDR_RW_BIT         1
    #define M85XX_I2C_READ                1
    #define M85XX_I2C_WRITE               0
    /*
     * Misc constants and values.
     */
    #define M85XX_I2C_START_SETUP    3  /* It could be 1.6us according to 400Khz spec */
    #define M85XX_I2C_STOP_SETUP     3  /* It could be 1.6us according to 400Khz spec */
    #define M85XX_I2C_TRANS_SETUP    10 /* 10 uS setup time */
    #define M85XX_I2C_TIMEOUT        10 /* 10mS timeout */
    #define M85XX_I2C_MAX_VALUE      0x7FFFFFFF
    #define M85XX_I2C_NUM_DIVIDER    0x40
    #define M85XX_I2C_MAX_TOGGLE     10 /* 10 times */  
    #define M85XX_I2C_HW_INIT_DELAY  1000 /* 1 msec */    

    /*
     * Alert reponse address
     */
    #define M85XX_I2C_ALERT_RESPONSE_ADRESS  0x0C

    /*
     * I2C module register map.
     */
    typedef struct _sM85XX_I2C_REGS{
        volatile UINT8 I2CADR;   /* I2C slave address register */
        UINT8 _PADDING0[3];
        volatile UINT8 I2CFDR;   /* I2C frequency divider */
        UINT8 _PADDING1[3];
        volatile UINT8 I2CCR;    /* I2C control register */
        UINT8 _PADDING2[3];
        volatile UINT8 I2CSR;    /* I2C status register */
        UINT8 _PADDING3[3];
        volatile UINT8 I2CDR;    /* I2C data register */
        UINT8 _PADDING4[3];
        volatile UINT8 I2CDFSRR; /* I2C digital filter sampling rate register */
    } sM85XX_I2C_REGS;

    /*
     * Needed default values.
     */
    #define M85XX_I2C_ADR_DEFAULT        0x00
    #define M85XX_I2C_DEFAULT_FREQ       400000  /* Go at 400kHz */
    #define M85XX_I2C_CTRL_ADDR_OFFSET   0x100


    /*
     * Reigster bit fields.
     */
    #define M85XX_I2C_SR_MCF     0x80    /* Data transfer in progress */
    #define M85XX_I2C_SR_MAAS    0x40    /* Addressed as slave device */
    #define M85XX_I2C_SR_MBB     0x20    /* Bus busy */
    #define M85XX_I2C_SR_MAL     0x10    /* Arbitration lost */
    #define M85XX_I2C_SR_BCSTM   0x08    /* Broadcast match */
    #define M85XX_I2C_SR_SRW     0x04    /* Slave read/write */
    #define M85XX_I2C_SR_MIF     0x02    /* Module interrupt pending */
    #define M85XX_I2C_SR_RXAK    0x01    /* Received ack */

    #define M85XX_I2C_CR_MEN     0x80    /* Module enable */
    #define M85XX_I2C_CR_MIEN    0x40    /* Module interrupt enable */
    #define M85XX_I2C_CR_MSTA    0x20    /* Master mode - Generate START condition */
    #define M85XX_I2C_CR_MTX     0x10    /* Transmit receive mode select */
    #define M85XX_I2C_CR_TXAK    0x08    /* Transfer ack enable */
    #define M85XX_I2C_CR_RSTA    0x04    /* Repeated start */
    #define M85XX_I2C_CR_BCST    0x01    /* Broadcast enable */

    /* valid bus: 0 - 1 */
    typedef enum eI2C_BUSES {
       I2C_BUS_0,
       I2C_BUS_1,
       I2C_BUS_MAX
    } eI2C_BUS;

    /* valid frequency: 100KHZ, 400KHZ */
    typedef enum eI2C_RATES {
       I2C_100KHZ = 100000,
       I2C_400KHZ = 400000
    } eI2C_RATE;

    /* valid offset: 0 - 255 */
    typedef enum eI2C_OFFSETS {
       I2C_OFFSET_MAX = 256,
       I2C_NO_OFFSET = 0xFFFFFFFF
    } eI2C_OFFSET;


    typedef struct _sBSP_I2C_PARAMS{
        void*   pBuffer;
        UINT8   size;
        UINT8   address;
        UINT8   offset;
        UINT32  freq;
    } sBSP_I2C_PARAMS;


    struct _sM85xx_I2C_DRV;
    
    /* I2C Controller DATA structure */
    typedef struct _sBSP_I2C_CTRL
        {
            UINT32  busNum ;
            VIRT_ADDR  baseAdrs ;
            UINT32  busFreq;
            struct _sM85xx_I2C_DRV *pM85xxI2cDrv;
            VIRT_ADDR  regBase;
            VXB_RESOURCE_ADR * pResAdr;
        } sBSP_I2C_CTRL ;

    /* I2C Module DATA structure */
    typedef struct _sM85xx_I2C_DRV
        {
        VXB_DEV_ID        pM85xxI2cModule;
        SEM_ID            m85xxI2cModuleAccessSem;
        UINT32            m85xxMpxClkDivider;
        sBSP_I2C_CTRL *   m85xxI2cCtrlData;
        }sM85xx_I2C_DRV;
        
    /* Default frequencies */
    #define I2C_BUS0_DEFAULT_FREQ  I2C_400KHZ
    #define I2C_BUS1_DEFAULT_FREQ  I2C_400KHZ

    /* function declarations */

    void bspI2cHwInit(void);

    STATUS bspI2cRead  (
                       UINT32  bus,
                       UINT32  devAddr,
                       UINT32  offset,
                       UINT8   *buf,
                       UINT32  len
                       );

    STATUS bspI2cWrite (
                       UINT32  bus,
                       UINT32  devAddr,
                       UINT32  offset,
                       UINT8   *buf,
                       UINT32  len
                       );

    STATUS bspI2cAraRead  (
                       UINT32  bus,
                       UINT8   *buf
                       ); 


/* Everything else goes here */

#ifdef __cplusplus
}
#endif

#endif /* _vxbM85xxI2c_H */

/* END OF FILE */

