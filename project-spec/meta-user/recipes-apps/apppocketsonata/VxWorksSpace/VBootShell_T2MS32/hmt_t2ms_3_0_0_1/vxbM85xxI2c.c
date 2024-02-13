/* vxbM85xxI2c.c - VxBus Driver for M85xx I2C Module */

/* COPYRIGHT *****************************************************************
 *
 *   Copyright (c) 2016 Curtiss-Wright. All rights reserved. 
 *   This Source Code is the Property of Curtiss-Wright and can only be
 *   used in accordance with Source Code License Agreement(s) of Curtiss-Wright
 *   or any of its subsidiaries.
 *   
 * END COPYRIGHT *************************************************************/

#define __CMFILE__  "%filespec: vxbM85xxI2c.c~133_vx7_64_3 %"

/* FILE HEADER ***************************************************************
 * Product Name:
 *
 * %name:          vxbM85xxI2c.c %
 * %version:       133_vx7_64_3 %
 * %instance:      kanata_1 %
 * %created_by:    tissa %
 * %date_created:  Mon Feb 01 12:16:42 2016 %
 *
 * Originator:     tissa
 * Date created:   Mon Jun 16 14:24:42 2009
 *
 * Description:  Freescale M85xx CPU family I2C Module driver.
 *
 * Notes:
 *
 * History:
 *      01-Feb-2016 TI; Task #47773; CR#50044
 *         Added the function vxbM85xxI2cObjLink
 *      08-Dec-2015 TI; Task #47642; CR#49630
 *         Port to 64bit
 *      24-Mar-2015 WW; Task #46560; CR#48269
 *         Updates after code review 
 *      23-Mar-2015 WW; Task #46546; CR#48267
 *         Fix GNU warnings 
 *      18-Mar-2015 WW; Task#46493 ; CR#48098
 *         Remove creating of child instances
 *      09-Mar-2015 WW; Task#46371 ; CR#48098
 *         Rename probe and attach function to fix build error
 *      04-Mar-2015 WW; Task#46371 ; CR#48098 
 *         Port to VxWorks 7  
 *      20-Mar-2013 TI/WW; Task #41527; CR#34373
 *         Added Alert Response Address (ARA) read needed for the LF variant
 *      18-Aug-2011 TI; Task kanata#36490 CR#35476  
 *         Enhanced I2C Read/Write error handling.
 *      17-Aug-2011 TI; Task kanata#36487 CR#37904 
 *         Updated the I2C bus busy lockup fix to match U-BOOT.
 *      24-Jan-2011 TI; Task kanata#34224 CR#35240
 *         -Fixed the I2C bus busy lockup problem.
 *         -Added DEBUG_M85xxI2C
 *      01-Jun-2010 TI; Task kanata#31966 CR#29425
 *         Added support for optional ERRNO reporting.
 *      27-Apr-2010 TI; Task kanata#31634 CR#31156
 *         Addressed the reported Coverity issues.
 *      16-Mar-2010 TI; Task #30990 CR#30240
 *         Modified to use sysBusFreqGet().
 *      16-Feb-2010 TI; Task#30906 ; CR#28282 
 *         -Moved the I2C bus specific data structure to be an element in the
 *          driver module structure sM85xx_I2C_DRV.
 *         -Moved the structure sM85xx_I2C_DRV definition to driver's header
 *          file vxbM85xxI2c.h
 *         -Updated the comments and function headers.
 *      02-Feb-2010 BJ; Task #30577; CR#29813
 *         Save in UNIX format
 *      29-Jan-2010 JAK; Task #30514; CR#29813
 *         Make Man cleanup
 *      28-JAN-2010 BJ; Task#30486; CR#29813
 *         Update function headers for docs
 *      15-JAN-2010 BJ; Task#30320; CR#29813
 *         Update function headers for docs
 *      08-SEP-2009 TI; Task#29223 ; CR#28282
 *         Get the platform's MPX frequency divider from hwconf.c and use it
 *          to calculate the I2CFDR
 *      11-AUG-2009 TI; Task#29043 ; CR#28281
 *         -Read the I2C Frequency from hwconf.c
 *         -Save pDrvCtrl in VXB_DEVICE structure
 *         -Remove unused function m85xxI2C_Read_RXAK
 *      17-JUL-2009 TI; Task#28873 ; CR#28281
 *         Created based on dsmI2c8641.c v13
 *
 * END FILE HEADER ***********************************************************/


/*

DESCRIPTION

The Freescale M85xx I2C Module BSP driver is an Application Programming Interface 
that allows the application to send/receive to/from a device on the two I2C bus 
controllers 0 and 1. Each I2C controller supports one I2C bus.

Methods:
\ts
vxbDevProbe       | probe device for driver
vxbDevAttach      | attach driver to device
vxbFdtDevGet      | get the child device information
vxbResourceAlloc  | allocate resource for child device
\te

This driver is bound to device tree, and the device tree node must specify
below parameters:

\is

\i <#address-cells>
This parameter specifies the number of address cells specified by reg.

\i <#size-cells>
This parameter specifies the number of size cells specified by reg.

\i <compatible>
This parameter specifies the name of the I2C driver. It must be "m85xxI2c".

\i <reg>
This parameter specifies the register base address and length of this module.
    
\i <i2c-ctrl0-freq>
The M85xx I2C Module Controller 0 Frequency.

\i <i2c-ctrl1-freq>
The M85xx I2C Module Controller 1 Frequency.

\i <m85xx-mpx-clk-divider>
The M85xx I2C Module MPX Clock Divider.

\ie

An example of device node is shown below:

\cs
        i2c0: i2c@118000 {
            #address-cells = <1>;
            #size-cells = <0>;
            cell-index = <0>;
            compatible = "m85xxI2c";
            reg = <0x118000 0x100>;            
            i2c-ctrl0-freq = <400000>;
            i2c-ctrl1-freq = <400000>;
            m85xx-mpx-clk-divider = <1>;
        
            ds3231@68 {
                compatible = "ds3231Rtc";
                rtc-slave-address = <0x68>;
                rtc-bus-number = <0x1>;
                interrupts = <32 0>;
                interrupt-parent = <&fpgaIntCtrl>;  
            };
        };        
\ce

NOTES:
This M85xx I2C VxBus Module driver is designed to be a hybrid driver which provides 
the minimum VxBus required initialization routines and keeps the prior VxBus API interface.
Hence the driver doesn't support multi instances and has only one instance to interface to one 
M85xx I2C module with up to two I2C controllers.

INCLUDE FILES: vxbM85xxI2c.h

*/

/* Includes */
#include <vxWorks.h>
#include <hwif/vxBus.h>
#include <hwif/vxbus/vxbLib.h>
#include <hwif/buslib/vxbFdtLib.h>
#include <subsys/int/vxbIntLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <taskLib.h>
#include "semLib.h"
#include "vxbM85xxI2c.h"
//#include "cwBoard.h"
#include "bsp.h"

#ifdef BSP_ERRNO_SUPPORT
    #include "errnoLib.h"
    #include "sysBspErrno.h"
    #define ERRNOSET(errno) errnoSet(errno)
#else
    #define ERRNOSET(errno)
#endif

/* Local definitions */

LOCAL STATUS m85xxI2cProbe (VXB_DEV_ID pDev);
LOCAL STATUS m85xxI2cAttach (VXB_DEV_ID pDev);

LOCAL void m85xxI2cCtrlFreqSet
(
    sM85XX_I2C_REGS *pRegs,
    UINT32 freq,
    UINT32 mpxClkDivider
);

LOCAL  void vxbM85xxI2cCtrlHwInit
(
    sBSP_I2C_CTRL * pM85xxI2cCtrlData
);

/* Driver methods */
LOCAL VXB_DRV_METHOD    m85xxI2cMethodsList[] = 
{
    /* Standard DMA class driver methods */
    { VXB_DEVMETHOD_CALL(vxbDevProbe),          m85xxI2cProbe},
    { VXB_DEVMETHOD_CALL(vxbDevAttach),         m85xxI2cAttach}, 
    VXB_DEVMETHOD_END
};

VXB_DRV vxbM85xxI2cDrv =
{
    { NULL } ,
    "m85xxI2c",             /* Name */
    "M85XX I2C Driver",     /* Description */
    VXB_BUSID_FDT,          /* Class */
    0,                      /* Flags */
    0,                      /* Reference count */
    (VXB_DRV_METHOD *)&m85xxI2cMethodsList       /* Method table */
};

VXB_DRV_DEF(vxbM85xxI2cDrv)

LOCAL const VXB_FDT_DEV_MATCH_ENTRY fsSocDmaMatch[] =
{
    {"m85xxI2c", (void *)NULL},
    {} /* Empty terminated list */
};    

LOCAL VXB_DEV_ID    pI2CModuleInst;

/*
 * Array of divider values, index is to be put in I2CFDR.
 * Taken from the 8641D Manual Rev.E
 * This assumes a default digital filter setting.
 */
LOCAL const UINT32 dividerArray[M85XX_I2C_NUM_DIVIDER] =
{
384, 416, 480, 576, 640, 704, 832, 1024,
1152, 1280, 1536, 1920, 2304, 2560, 3072, 3840,
4608, 5120, 6144, 7680, 9216, 10240, 12288, 15360,
18432, 20480, 24576, 30720, 36864, 40960, 49152, 61440,
256, 288, 320, 352, 384, 448, 512, 576,
640, 768, 896, 1024, 1280, 1536, 1792, 2048,
2560, 3072, 3584, 4096, 5120, 6144, 7168, 8192,
10240, 12288, 14336, 16384, 20480, 24576, 28672, 32768
};

IMPORT void sysMsDelay(UINT delay);
IMPORT void sysUsDelay(UINT delay);
IMPORT UINT32 sysBusFreqGet(void);
IMPORT void sysMsDelay(UINT delay);
IMPORT void sysUsDelay(UINT delay);

typedef struct i2cDevInfo
{
    struct vxbFdtDev  vxbFdtDev;
    VXB_RESOURCE_LIST vxbResList;
} I2C_DEV_INFO;  

#undef DEBUG_M85xxI2C

/******************************************************************************
*
* m85xxI2cProbe - probe the M85XX I2C
*
* Check for M85XX I2C (or compatible) at the specified
* base address.  We assume one is present at that address, but we need to verify.
*
* RETURNS: OK if probe passes. ERROR otherwise.
*
* ERRNO
*
* \NOMANUAL
*/

LOCAL STATUS m85xxI2cProbe
(
    struct vxbDev * pDev /* Device information */
)
{
    VXB_FDT_DEV_MATCH_ENTRY *pMatch;
    
    if (vxbFdtDevMatch (pDev, fsSocDmaMatch, &pMatch) == ERROR)
        return ERROR;

    return OK;
}

/******************************************************************************
*
* m85xxI2cAttach - attach M85XX I2C
*
* This routine initialize and attach M85XX I2C
*
* RETURNS: OK or ERROR when initialize failed
*
* ERRNO
*
* \NOMANUAL
*/

LOCAL STATUS m85xxI2cAttach
(
    VXB_DEV_ID pM85xxI2cModule
)
{
    sM85xx_I2C_DRV * pDrvModule;
    sBSP_I2C_CTRL * pM85xxI2cCtrlData;
    UINT32 ctrlNum;    
    VXB_FDT_DEV * pFdtDev;
    int proplen = 0;
    const void *prop;      
    VXB_RESOURCE * pRes;
    VXB_RESOURCE_ADR * pResAdr = NULL;   
    
    if ( pM85xxI2cModule == NULL )
    {
        return ERROR;
    }
    
    if ( (pFdtDev = (VXB_FDT_DEV *)(vxbFdtDevGet(pM85xxI2cModule))) == NULL)
    {
        return ERROR;    
    }
    
    /* allocate the memory for the structure */
    pDrvModule = (sM85xx_I2C_DRV *) vxbMemAlloc (sizeof(sM85xx_I2C_DRV));
    
    /* check if memory allocation is successful */
    if (pDrvModule == NULL)
    {
        return ERROR;
    }

    /* initialize pDrvModule */
    bzero((char *)pDrvModule, sizeof(*pDrvModule)); 
    
     /* Allocate memory for the I2C controller data structures */
    pM85xxI2cCtrlData = (sBSP_I2C_CTRL *) vxbMemAlloc(sizeof(sBSP_I2C_CTRL)* I2C_BUS_MAX);
    
    /* check if memory allocation is successful */
    if (pM85xxI2cCtrlData == NULL)
    {
        vxbMemFree(pDrvModule);    
        return ERROR;
    }

    /* initialize pDrvModule */
    bzero((char *)pM85xxI2cCtrlData, sizeof(sBSP_I2C_CTRL)* I2C_BUS_MAX);
    
    /* M85xxI2C DRV Module structure has a pointer to the first I2C Controller DATA structure*/
    pDrvModule->m85xxI2cCtrlData = pM85xxI2cCtrlData;
     
    for(ctrlNum = 0; ctrlNum <I2C_BUS_MAX; ctrlNum ++)
    {
        /* Get the I2C DATA structure of this I2C controller */
        pM85xxI2cCtrlData = &pDrvModule->m85xxI2cCtrlData[ctrlNum];
        
        /* Set a pointer to the driver structure */
        pM85xxI2cCtrlData->pM85xxI2cDrv = pDrvModule;
        
        /* Since the I2C busNum matches the I2C ctrlNum, Save the busNum in the current 
             controller data structure*/
        pM85xxI2cCtrlData->busNum = ctrlNum;
        
        pRes = vxbResourceAlloc(pM85xxI2cModule, VXB_RES_MEMORY, 0);
    
        if(pRes == NULL)
        {
            vxbMemFree(pM85xxI2cCtrlData);
            vxbMemFree(pDrvModule);            
            return ERROR;
        }
    
        pResAdr = (VXB_RESOURCE_ADR *)pRes->pRes;
    
        if (pResAdr == NULL)
        {
            vxbMemFree(pM85xxI2cCtrlData);
            vxbMemFree(pDrvModule);            
            return ERROR;
        }
    
        pM85xxI2cCtrlData->pResAdr = pResAdr;
        pM85xxI2cCtrlData->regBase = pResAdr->virtual;        
        
        /* Save the base address in the current controller data struct*/
        pM85xxI2cCtrlData->baseAdrs = pM85xxI2cCtrlData->regBase +\
                                               M85XX_I2C_CTRL_ADDR_OFFSET * ctrlNum;
                 
        switch(ctrlNum)
        {
            case I2C_BUS_0:
            default: 
            { 
                /* Get the M85xx I2C controller 0 default frequency */
                pM85xxI2cCtrlData->busFreq = (UINT32)I2C_BUS0_DEFAULT_FREQ;                
                
                /*
                 * resourceDesc {
                 * The m85xxI2cCtrl0Freq resource specifies the M85xx I2C controller 0 frequency
                 * in the system.}
                 */                
                prop = vxFdtPropGet(pFdtDev->offset, "i2c-ctrl0-freq", &proplen);
                if (prop != NULL)
                {    
                    pM85xxI2cCtrlData->busFreq = vxFdt32ToCpu(*(UINT32 *)prop);
                }
                
                
                break;
                
            }
            case I2C_BUS_1:
            {
                /* Get the M85xx I2C controller 1 frequency */
                pM85xxI2cCtrlData->busFreq = (UINT32)I2C_BUS1_DEFAULT_FREQ;                
                prop = vxFdtPropGet(pFdtDev->offset, "i2c-ctrl1-freq", &proplen);
                if (prop != NULL)
                {    
                    pM85xxI2cCtrlData->busFreq = vxFdt32ToCpu(*(UINT32 *)prop);
                }        
                break;
            } 
        }        
    } 
     
    /* save instance ID */
    pDrvModule->pM85xxI2cModule = pM85xxI2cModule;

    /*
     * save device ID as a global
     * Note: This is okay since we have one instance and support only one M85xx I2C Module
     */
    pI2CModuleInst = pM85xxI2cModule;
     
    /* Get the platforms MPX Clock freq divider */
    pDrvModule->m85xxMpxClkDivider = (UINT32)PLATFORM_I2C_MPX_FREQ_DIVIDER;
    prop = vxFdtPropGet(pFdtDev->offset, "m85xx-mpx-clk-divider", &proplen);
    if (prop != NULL)
    {    
        pDrvModule->m85xxMpxClkDivider = vxFdt32ToCpu(*(UINT32 *)prop);
    }     
    
    /* save pDrvModule in VXB_DEVICE structure */
    vxbDevSoftcSet(pM85xxI2cModule, (void *)pDrvModule);           
    
     /* Initialize the HW */
    for(ctrlNum=0; ctrlNum < I2C_BUS_MAX; ctrlNum++)
    {
         /* Get the data structure of the current I2C Controller */
         pM85xxI2cCtrlData = &pDrvModule->m85xxI2cCtrlData[ctrlNum];
         /* Initialize  the current I2C Controller HW*/
         vxbM85xxI2cCtrlHwInit(pM85xxI2cCtrlData);
    }     

    /*
    * Create a semaphore (mutex) for the I2C module access protection.
    */
    pDrvModule->m85xxI2cModuleAccessSem = semOpen ("/I2Csem",
                                      SEM_TYPE_MUTEX,
                                      0,
                                      SEM_Q_PRIORITY |SEM_INVERSION_SAFE,
                                      OM_CREATE ,
                                      NULL); 
        
    return OK;
}

/******************************************************************************
*
* m85xxI2c_DisableRxAck - disable acknowledge on receive
*
* This routine disables acknowledge on receive.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \ie
*
* RETURNS: N/A
*
*/
LOCAL void m85xxI2c_DisableRxAck
     (
     sM85XX_I2C_REGS *pRegs
     )
{
    pRegs->I2CCR |= M85XX_I2C_CR_TXAK;
    WRS_ASM("isync;sync;eieio");
}

/******************************************************************************
*
* m85xxI2c_StopCondition - issue STOP condition to the bus
*
* This routine issues the STOP condition to the bus.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \ie
*
* RETURNS: N/A
*
*/
LOCAL void m85xxI2c_StopCondition
     (
     sM85XX_I2C_REGS *pRegs
     )
{
    pRegs->I2CCR &= (UINT8)(~M85XX_I2C_CR_MSTA);
    WRS_ASM("isync;sync;eieio");
}
/* END OF FUNCTION m85xxI2c_StopCondition() */



/******************************************************************************
*
* m85xxI2c_ForceSclGen - Force the I2C to generate the SCL
*
* This routine forces the I2C module to generate the SCL to clear any existing 
* I2C bus busy lockup.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \ie
*
* RETURNS: N/A
*
*/
LOCAL void m85xxI2c_ForceSclGen
     (
     sM85XX_I2C_REGS *pRegs
     )
{
    UINT8 dummy __attribute__ ((unused));

    /*  Disable the I2C module (I2CCR[MEN] = 0) and change to master mode (I2CCR[MSTA] = 1) by
    programming the value 0x20 into I2CCR */
    pRegs->I2CCR = M85XX_I2C_CR_MSTA;
    WRS_ASM("isync;sync;eieio");
    sysUsDelay(M85XX_I2C_START_SETUP ); /* let it shutdown in peace */
        
    /* Clear the SR */
    pRegs->I2CSR =0; 
     
    /*  Re-enable the I2C module (I2CCR[MEN] = 1) by programming the value 0xA0 into I2CCR */
    pRegs->I2CCR = M85XX_I2C_CR_MSTA | M85XX_I2C_CR_MEN;
    WRS_ASM("isync;sync;eieio");
    
    /*  Disable the I2C module (I2CCR[MEN] = 0) and change to master mode (I2CCR[MSTA] = 1) by
    programming the value 0x20 into I2CCR */
    pRegs->I2CCR = M85XX_I2C_CR_MSTA;
    WRS_ASM("isync;sync;eieio");
    sysUsDelay(M85XX_I2C_START_SETUP ); /* let it shutdown in peace */
      
    /*  Re-enable the I2C module (I2CCR[MEN] = 1) by programming the value 0xA0 into I2CCR */
    pRegs->I2CCR = M85XX_I2C_CR_MSTA | M85XX_I2C_CR_MEN;
    WRS_ASM("isync;sync;eieio");  
    
    /* Read I2CDR */
    dummy= pRegs->I2CDR;
    WRS_ASM("isync;sync;eieio");
    
    /* Return the I2C module to slave mode (I2CCR[MSTA] = 0) by programming the value 0x80 into
    I2CCR. */
    pRegs->I2CCR = M85XX_I2C_CR_MEN;
    WRS_ASM("isync;sync;eieio");
}
/****************************************************************************************
*
* Function Name: m85xxI2c_ReadByte - read a byte from the I2C bus
*
* This routine sets up the direction and reads a byte from the I2C bus. 
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \i 'pByte'
* Pointer to byte buffer.
* \ie
*
* RETURNS: N/A
*/
LOCAL void m85xxI2c_ReadByte
     (
     sM85XX_I2C_REGS *pRegs,
     UINT8 *pByte
     )
{
    /*
     * Set direction: READ
     */
    pRegs->I2CCR &= (UINT8)(~M85XX_I2C_CR_MTX);
    WRS_ASM("isync;sync;eieio");

    /*
     * Read byte from the I2C bus.
     */
    *pByte = pRegs->I2CDR;
    WRS_ASM("isync;sync;eieio");

}

/****************************************************************************************
*
* m85xxI2c_RepeatedStart - issue a repeated START to the bus
*
* This routine issues a repeated START to the bus.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \ie
*
* RETURNS: N/A
*
*/
LOCAL void m85xxI2c_RepeatedStart
     (
     sM85XX_I2C_REGS *pRegs
     )
{
    pRegs->I2CCR |= M85XX_I2C_CR_RSTA;
    WRS_ASM("isync;sync;eieio");
}
/* END OF FUNCTION m85xxI2c_RepeatedStart() */

/****************************************************************************************
*
* m85xxI2c_IsInterruptActive - get state of interrupt bit
*
* This routine returns the state of the interrupt bit and RXACK for the I2C write.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \ie
*
* RETURNS: TRUE is the interrupt bit is set with no errors,
*         FALSE if the interrupt bit is not set, 
*         the interrupt bit is set and MAL bit is set, 
*         the interrupt bit is set and the MCF data transfer is not set, or            
*         the interrupt bit is set and the RXACK was not detected for write transactions.
*
*
*/
LOCAL BOOL m85xxI2c_IsInterruptActive
     (
     sM85XX_I2C_REGS *pRegs,
     UINT32 direction
     )
{
    BOOL returnValue;
    volatile UINT32 csr;
    
    /* Read the I2C SR Register */
    csr = pRegs->I2CSR;
    WRS_ASM("isync;sync;eieio");
    
    /* Check the MIF interrupt bit*/
    if ((csr & M85XX_I2C_SR_MIF) == M85XX_I2C_SR_MIF)
    {
 
        /* Check the MAL arbitration bit*/
        if (csr & M85XX_I2C_SR_MAL)
            /* Arbitration is lost. */ 
            return(FALSE);
        
        /* Check the MCF data transfer bit */
        if (!(csr & M85XX_I2C_SR_MCF))
            /* A byte transfer is in progress.. */ 
            return(FALSE);
        
        /* Check the RXACK bit for the write transactions */
        if((direction == M85XX_I2C_WRITE) && (csr & M85XX_I2C_SR_RXAK))
            /* No acknowledge signal has been received. */
            returnValue = FALSE;
        else 
           /* An acknowledge signal has been received. */
            returnValue = TRUE;
    }
    else
    {
        returnValue = FALSE;
    }

    return returnValue;
}

/****************************************************************************************
*
* m85xxI2c_EnableRxAck - enable acknowledge on receive
*
* This routine enables acknowledge on receive.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \ie
*
* RETURNS: N/A
*
*/
LOCAL void m85xxI2c_EnableRxAck
      (
      sM85XX_I2C_REGS *pRegs
      )
{

    pRegs->I2CCR &= (UINT8)(~M85XX_I2C_CR_TXAK);
    WRS_ASM("isync;sync;eieio");
}

/****************************************************************************************
*
* m85xxI2c_StartCondition - issue a START to the bus
*
* This routine issues a START to the bus.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \ie
*
* RETURNS: N/A
*
*/
LOCAL void m85xxI2c_StartCondition
     (
     sM85XX_I2C_REGS *pRegs
     )
{
    pRegs->I2CCR |= M85XX_I2C_CR_MSTA;
    WRS_ASM("isync;sync;eieio");
}

/****************************************************************************************
*
* m85xxI2c_WriteByte - write a byte to the I2C bus
*
* This routine sets up the direction and writes a byte to the I2C bus.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \i 'byte'
* Byte to write.
* \ie
*
* RETURNS: N/A
*
*/
LOCAL void m85xxI2c_WriteByte
     (
      sM85XX_I2C_REGS *pRegs,
      UINT8 byte
      )
{
    /*
     * Set direction: WRITE
     */
    pRegs->I2CCR |= M85XX_I2C_CR_MTX;
    WRS_ASM("isync;sync;eieio");

    /*
     * Issue byte on the I2C bus.
     */
    pRegs->I2CDR = byte;
    WRS_ASM("isync;sync;eieio");
}
/* END OF FUNCTION m85xxI2c_WriteByte() */

/****************************************************************************************
*
* m85xxI2c_ClearInt - clear a pending interrupt.
*
* This routine clears a pending interrupt.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \ie
*
* RETURNS: N/A
*/
LOCAL void m85xxI2c_ClearInt
     (
     sM85XX_I2C_REGS *pRegs
     )
{
    pRegs->I2CSR &= (UINT8)(~M85XX_I2C_SR_MIF);
    WRS_ASM("isync;sync;eieio");
}
/* END OF FUNCTION m85xxI2c_ClearInt() */

/****************************************************************************************
*
* m85xxI2cCtrlDisable - Disable the specified I2C controller
*
* This routine Disables the I2C controller.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \ie
*
* RETURNS: N/A
*
*/
LOCAL void m85xxI2cCtrlDisable
     (
     sM85XX_I2C_REGS *pRegs
     )
{

    /*
     * Disable the I2C controller.
     */
    pRegs->I2CCR &= (UINT8)(~M85XX_I2C_CR_MEN);
    WRS_ASM("isync;sync;eieio");
}
/****************************************************************************************
*
* m85xxI2cCtrlEnable - enable the specified I2C controller
*
* This routine enables the I2C controller.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \ie
*
* RETURNS: N/A
*
*/
LOCAL void m85xxI2cCtrlEnable
     (
     sM85XX_I2C_REGS *pRegs
     )
{
    pRegs->I2CADR = M85XX_I2C_ADR_DEFAULT;
    WRS_ASM("isync;sync;eieio");

    /*
     * Enable the I2C controller.
     */
    pRegs->I2CCR = M85XX_I2C_CR_MEN;
    WRS_ASM("isync;sync;eieio");
}


/****************************************************************************************
*
* m85xxI2cCtrlFreqSet - set the I2C controller's bus frequency
*
* This routine sets the I2C controller's bus frequency using the closest divider.
*
* PARAMETERS:
* \is
* \i 'pRegs'
* Pointer to register structure.
* \i 'freq'
* Desired I2C controller frequency.
* \i 'mpxClkDivider'
* Clock divider.
* \ie
*
* RETURNS: N/A
*
* NOTE: Uses the bus speed from sysBusFreqGet.
*
*/
LOCAL void m85xxI2cCtrlFreqSet
     (
     sM85XX_I2C_REGS *pRegs,
     UINT32 freq,
     UINT32 mpxClkDivider
     )
{
    UINT32      busFreq;
    register UINT32 divider;
    register UINT8  dividerIndex = 0;
    register INT32  diff;
    register INT32  oldDiff = M85XX_I2C_MAX_VALUE;  /* Max 32-bit signed value */
    register UINT8  i;

    /*
     * This clock drives the I2C clock.
     */
    busFreq = sysBusFreqGet();

    /* Divide by the platform clock frequency divider */
    busFreq /= mpxClkDivider;

    /*
     * Divider is the bus freq divided by desired freq.
     */
    divider = busFreq / freq;

    /*
     * Scan array to find closest fit.
     */
    for(i=0; i<M85XX_I2C_NUM_DIVIDER; i++)
    {
        diff = dividerArray[i] - divider;

        /*
         * If divider diff is bigger than zero
         * but smaller than our closest match
         * we store the new closest match.
         */
        if ((diff > 0) && (diff < oldDiff))
        {
            oldDiff = diff;
            dividerIndex = i;
        }
    }

    /*
     * Write the closest (slower than) fit
     * in divider register.
     */
    pRegs->I2CFDR = dividerIndex;
    WRS_ASM("isync;sync;eieio");    /* Doc recommends to isync;sync;eieio every RMW */

}

/****************************************************************************************
*
* vxbM85xxI2cCtrlHwInit - initialize the M85xx I2C Controller hardware
*
* This routine initializes the M85xx I2C Controller hardware
*
* PARAMETERS:
* \is
* \i 'pM85xxI2cModule'
* Pointer to I2C Module structure.
* \ie
*
* RETURNS: N/A
*
*/
LOCAL  void vxbM85xxI2cCtrlHwInit
    (
    sBSP_I2C_CTRL * pM85xxI2cCtrlData
    )
{
    sM85XX_I2C_REGS *pRegs ;
    UINT32 toggleAttempt;
    UINT8 dummy __attribute__ ((unused));
    UINT8 srRegVal = 0;
    sM85xx_I2C_DRV * pDrvModule = pM85xxI2cCtrlData->pM85xxI2cDrv;
    
    pRegs = (sM85XX_I2C_REGS *)pM85xxI2cCtrlData->baseAdrs;
        
    /* Set the current controller bus frequency */
    m85xxI2cCtrlFreqSet((sM85XX_I2C_REGS *)pM85xxI2cCtrlData->baseAdrs,\
                             pM85xxI2cCtrlData->busFreq,\
                             pDrvModule->m85xxMpxClkDivider);
        
    /* Disable the current I2C controller HW */
    m85xxI2cCtrlDisable((sM85XX_I2C_REGS *)pM85xxI2cCtrlData->baseAdrs);
        
    /* Set the device to Master Mode */
    m85xxI2c_StartCondition((sM85XX_I2C_REGS *)pM85xxI2cCtrlData->baseAdrs);
          
    /* Clear the SR */
    pRegs->I2CSR =0; 
    WRS_ASM("isync;sync;eieio");
        
    /* Enable the current I2C controller HW */
    m85xxI2cCtrlEnable((sM85XX_I2C_REGS *)pM85xxI2cCtrlData->baseAdrs);
        
    /* Read I2CDR */
    dummy = pRegs->I2CDR;
    WRS_ASM("isync;sync;eieio");
       
    /* wait 1 msec */
    sysUsDelay(M85XX_I2C_HW_INIT_DELAY);
        
    /* Read I2CSR */
    srRegVal = pRegs->I2CSR;
    WRS_ASM("isync;sync;eieio");
        
    /* If the bus is busy (could indicate a bus lockup), attempt to recover by 
           toggling slave to master mode, up to 10 times */
    toggleAttempt  = (UINT32)M85XX_I2C_MAX_TOGGLE;
    while((srRegVal & M85XX_I2C_SR_MBB) && (toggleAttempt>0))
    {
         /* Clear any I2C bus busy lockup by forcing the I2C module to generate the SCL */
         m85xxI2c_ForceSclGen((sM85XX_I2C_REGS *)pM85xxI2cCtrlData->baseAdrs);
              
         /* wait 1 msec */
         sysUsDelay(M85XX_I2C_HW_INIT_DELAY);
            
         /* Read I2CSR */
         srRegVal = pRegs->I2CSR;
         WRS_ASM("isync;sync;eieio");
              
         toggleAttempt--;
    }

    /* Clear the SR */
    pRegs->I2CSR =0; 
    WRS_ASM("isync;sync;eieio");
}

/****************************************************************************************
*
* m85xxI2cRead - read from an I2C device
*
* This routine reads from an I2C device.
*
* PARAMETERS:
* \is
* \i 'busNum'
* I2C controller bus number(I2C_BUS_0 or I2C_BUS_1).
* \i 'pArgs'
* Pointer to data buffer.
* \ie
*
* RETURNS:
* \ml
* \m -
* OK, function completed normally
* \m -
* DSM_UNIMPLEMENTED, service not supported
* \m -
* ERROR, error while attempting to execute the I2C read service
* \me
*/
LOCAL STATUS m85xxI2cRead
     (
     UINT32  busNum,
     void *pArgs
     )
{

    sM85xx_I2C_DRV * pDrvModule = (sM85xx_I2C_DRV *)vxbDevSoftcGet(pI2CModuleInst);
    sBSP_I2C_CTRL * pM85xxI2cCtrlData = &pDrvModule->m85xxI2cCtrlData[busNum];
    sM85XX_I2C_REGS *pRegs = (sM85XX_I2C_REGS *)pM85xxI2cCtrlData->baseAdrs;
    sBSP_I2C_PARAMS         *pParams = pArgs;
    UINT8                   *pBuffer = pParams->pBuffer;
    UINT8 dummy = 0;
    UINT32 i = 0;
    UINT32 eTimeout =0;

    if ( pDrvModule == NULL )
    {
        return ERROR;
    }
    
    /*
     * Enable Acknowledge on receive
     */
    m85xxI2c_EnableRxAck(pRegs);

    /*
     * Start condition
     * Wakes up all slaves to listen for a slave address.
     */
    m85xxI2c_StartCondition(pRegs);

    /*
     * Start condition
     * Wait the usual 5uS setup time after a START.
     */
    sysUsDelay(M85XX_I2C_START_SETUP);

    /*
     * Addressing cycle.
     * Issue address on the I2C bus.
     * ~M85XX_I2C_ADDR_RW_BIT means Write Access
     */
    m85xxI2c_WriteByte(pRegs, ((UINT8)(pParams->address << M85XX_I2C_ADDR_RW_SHIFT) & ~M85XX_I2C_ADDR_RW_BIT));


    /*
     * Wait for the transaction to begin.
     */
    sysUsDelay(M85XX_I2C_TRANS_SETUP);
    
    /*
     * Addressing cycle
     * Wait for interrupt to happen.
     * If interrupt, address ack'ed, if no interrupt, timeout.
     */
    eTimeout = 0;
    while(!(m85xxI2c_IsInterruptActive(pRegs, M85XX_I2C_WRITE)))
    {
         sysMsDelay(1);
        if(eTimeout == M85XX_I2C_TIMEOUT)
        {
#if defined(DEBUG_M85xxI2C)
            printf("I2CSR=0x%x, LineNum = %d\n",pRegs->I2CSR, __LINE__);
#endif    
            /* Recover before returning ERROR */
            m85xxI2c_ClearInt(pRegs);
            m85xxI2c_StopCondition(pRegs);
            sysUsDelay(M85XX_I2C_STOP_SETUP);
            
            /* Reinitialize the controller to clear any bus lockup */
            vxbM85xxI2cCtrlHwInit(pM85xxI2cCtrlData);
            
            return(ERROR);
        }
        else
            eTimeout++;
    }

    /*
     * Clear interrupt
     */
    m85xxI2c_ClearInt(pRegs);

    /*
     * Command/Offset cycle
     * Issue command/offset on the I2C bus.
     */
    m85xxI2c_WriteByte(pRegs, pParams->offset);

    /*
     * Command/Offset cycle
     * Wait for interrupt to happen.
     * If interrupt, address ack'ed, if no interrupt, timeout.
     */
    eTimeout = 0;
    while(!(m85xxI2c_IsInterruptActive(pRegs, M85XX_I2C_WRITE)))
    {
        sysMsDelay(1);
        if(eTimeout == M85XX_I2C_TIMEOUT)
        {
#if defined(DEBUG_M85xxI2C)
            printf("I2CSR=0x%x, LineNum = %d\n",pRegs->I2CSR, __LINE__);
#endif 
  
            /* Recover before returning ERROR */
            m85xxI2c_ClearInt(pRegs);
            m85xxI2c_StopCondition(pRegs);
            sysUsDelay(M85XX_I2C_STOP_SETUP);
            
            /* Reinitialize the controller to clear any bus lockup */
            vxbM85xxI2cCtrlHwInit(pM85xxI2cCtrlData);
            return(ERROR);
        }
        else
            eTimeout++;
    }

    /*
     * Clear interrupt
     */
    m85xxI2c_ClearInt(pRegs);

    /*
     * Read cycle.
     * Repeated start
     */
    m85xxI2c_RepeatedStart(pRegs);

    /*
     * Read cycle.
     * Addressing cycle.
     * Issue address on the I2C bus.
     * M85XX_I2C_ADDR_RW_BIT means Read Access.
     */
    m85xxI2c_WriteByte(pRegs, ((UINT8)(pParams->address << M85XX_I2C_ADDR_RW_SHIFT) | M85XX_I2C_ADDR_RW_BIT));

    /*
     * Addressing cycle
     * Wait for interrupt to happen.
     * If interrupt, address ack'ed, if no interrupt, timeout.
     */
    eTimeout = 0;
    
    while(!(m85xxI2c_IsInterruptActive(pRegs, M85XX_I2C_WRITE)))
    {
        sysMsDelay(1);
        if(eTimeout == M85XX_I2C_TIMEOUT)
        {
#if defined(DEBUG_M85xxI2C)
            printf("I2CSR=0x%x, LineNum = %d\n",pRegs->I2CSR, __LINE__);
#endif  
            /* Recover before returning ERROR */
            m85xxI2c_ClearInt(pRegs);
            m85xxI2c_StopCondition(pRegs);
            sysUsDelay(M85XX_I2C_STOP_SETUP);
            
            /* Reinitialize the controller to clear any bus lockup */
            vxbM85xxI2cCtrlHwInit(pM85xxI2cCtrlData);
            return(ERROR);
        }
        else
            eTimeout++;
    }

    /*
     * Clear interrupt
     */
    m85xxI2c_ClearInt(pRegs);

    if (pParams->size == 1)
    {
        /*
         * This should end the transfer and
         * generate a STOP condition automatically.
         */
        m85xxI2c_DisableRxAck(pRegs);
    }

    /*
     * Dummy read to trigger SCL
     */
    m85xxI2c_ReadByte(pRegs, &dummy);

    for(i=0; i < pParams->size; i++)
    {
        eTimeout = 0;
        while(!(m85xxI2c_IsInterruptActive(pRegs, M85XX_I2C_READ)))
        {
            sysMsDelay(1);
            if(eTimeout == M85XX_I2C_TIMEOUT)
            {
#if defined(DEBUG_M85xxI2C)
                printf("I2CSR=0x%x, LineNum = %d\n",pRegs->I2CSR, __LINE__);
#endif  
                /* Recover before returning ERROR */
                m85xxI2c_ClearInt(pRegs);
                m85xxI2c_StopCondition(pRegs);
                sysUsDelay(M85XX_I2C_STOP_SETUP);
                
                /* Reinitialize the controller to clear any bus lockup */
                vxbM85xxI2cCtrlHwInit(pM85xxI2cCtrlData);
                return(ERROR);
            }
            else
                eTimeout++;
        }

        /*
         * Clear interrupt
         */
        m85xxI2c_ClearInt(pRegs);

        /*
         * For the last byte, we disable the ack on Rx.
         */
        if ((pParams->size - i) == 2)
        {
            /*
             * This should end the transfer and
             * generate a STOP condition automatically.
             */
            m85xxI2c_DisableRxAck(pRegs);
        }

        if ((pParams->size - i) == 1)
        {
            /*
             * File stop condition on the bus.
             */
            m85xxI2c_StopCondition(pRegs);
        }

        m85xxI2c_ReadByte(pRegs, &(pBuffer[i]));
    }

    /*
     * Stop condition
     * Wait some setup time after a STOP.
     */
    sysUsDelay(M85XX_I2C_STOP_SETUP);

    return(OK);
}

/****************************************************************************************
*
* m85xxI2cAraRead - Issue an I2C ARA (Alert Response Address) on the I2C bus
*
* This routine performs an ARA on the I2C bus.
*
* PARAMETERS:
* \is
* \i 'busNum'
* I2C controller bus number(I2C_BUS_0 or I2C_BUS_1).
* \i 'pArgs'
* Pointer to data buffer.
* \ie
*
* RETURNS:
* \ml
* \m -
* OK, function completed normally
* \m -
* DSM_UNIMPLEMENTED, service not supported
* \m -
* ERROR, error while attempting to execute the I2C read service
* \me
*/
LOCAL STATUS m85xxI2cAraRead
     (
     UINT32  busNum,
     void *pArgs
     )
{

    sM85xx_I2C_DRV * pDrvModule = (sM85xx_I2C_DRV *)vxbDevSoftcGet(pI2CModuleInst);
    sBSP_I2C_CTRL * pM85xxI2cCtrlData = &pDrvModule->m85xxI2cCtrlData[busNum];
    sM85XX_I2C_REGS *pRegs = (sM85XX_I2C_REGS *)pM85xxI2cCtrlData->baseAdrs;
    UINT8 dummy = 0;
    UINT32 eTimeout =0;
    UINT8                   *pAlertAddress = pArgs;    

    if ( pDrvModule == NULL )
    {
        return ERROR;
    }
    
    /*
     * Disable Acknowledge on receive
     */
    m85xxI2c_DisableRxAck(pRegs);

    /*
     * Start condition
     * Wakes up all slaves to listen for a slave address.
     */
    m85xxI2c_StartCondition(pRegs);

    /*
     * Start condition
     * Wait the usual 5uS setup time after a START.
     */
    sysUsDelay(M85XX_I2C_START_SETUP);

    /*
     * Addressing cycle.
     * Issue alert response address.
     */
    m85xxI2c_WriteByte(pRegs, ((M85XX_I2C_ALERT_RESPONSE_ADRESS << M85XX_I2C_ADDR_RW_SHIFT) | M85XX_I2C_ADDR_RW_BIT));

#if 0
    /*
     * Wait for the transaction to begin.
     */
    sysUsDelay(M85XX_I2C_TRANS_SETUP);
#endif    
    /*
     * Addressing cycle
     * Wait for interrupt to happen.
     * If interrupt, address ack'ed, if no interrupt, timeout.
     */
    eTimeout = 0;
    while(!(m85xxI2c_IsInterruptActive(pRegs, M85XX_I2C_WRITE)))
    {
         sysMsDelay(1);
        if(eTimeout == M85XX_I2C_TIMEOUT)
        {
#if defined(DEBUG_M85xxI2C)
            printf("I2CSR=0x%x, LineNum = %d\n",pRegs->I2CSR, __LINE__);
#endif    
            /* Recover before returning ERROR */
            m85xxI2c_ClearInt(pRegs);
            m85xxI2c_StopCondition(pRegs);
            sysUsDelay(M85XX_I2C_STOP_SETUP);
            
            /* Reinitialize the controller to clear any bus lockup */
            vxbM85xxI2cCtrlHwInit(pM85xxI2cCtrlData);
            
            return(ERROR);
        }
        else
            eTimeout++;
    }

    /*
     * Clear interrupt
     */
    m85xxI2c_ClearInt(pRegs);

    /*
     * Dummy read to trigger SCL
     */
    m85xxI2c_ReadByte(pRegs, &dummy);

    eTimeout = 0;
    while(!(m85xxI2c_IsInterruptActive(pRegs, M85XX_I2C_READ)))
    {
        sysMsDelay(1);
        if(eTimeout == M85XX_I2C_TIMEOUT)
        {
#if defined(DEBUG_M85xxI2C)
            printf("I2CSR=0x%x, LineNum = %d\n",pRegs->I2CSR, __LINE__);
#endif  
            /* Recover before returning ERROR */
            m85xxI2c_ClearInt(pRegs);
            m85xxI2c_StopCondition(pRegs);
            sysUsDelay(M85XX_I2C_STOP_SETUP);
            
            /* Reinitialize the controller to clear any bus lockup */
            vxbM85xxI2cCtrlHwInit(pM85xxI2cCtrlData);
            return(ERROR);
        }
        else
            eTimeout++;
    }

    /*
     * Clear interrupt
     */
    m85xxI2c_ClearInt(pRegs);

    /*
     * File stop condition on the bus.
     */
    m85xxI2c_StopCondition(pRegs);        

    /*
     * Read alerting device slave address.
     */
    m85xxI2c_ReadByte(pRegs, pAlertAddress);        
    
    /*
     * Clear interrupt
     */
    m85xxI2c_ClearInt(pRegs);    

    /*
     * Stop condition
     * Wait some setup time after a STOP.
     */
    sysUsDelay(M85XX_I2C_STOP_SETUP);

    return(OK);
}


/****************************************************************************************
*
* m85xxI2cWrite - write to an I2C device
*
* This routine writes to an I2C device.
*
* PARAMETERS:
* \is
* \i 'busNum'
* I2C controller bus number(I2C_BUS_0 or I2C_BUS_1).
* \i 'pArgs'
* Pointer to data buffer.
* \ie
*
* RETURNS:
* \ml
* \m -
* OK, function completed normally
* \m -
* DSM_UNIMPLEMENTED, service not supported
* \m -
* ERROR, error while attempting to execute the I2C write service
* \me
*/
LOCAL STATUS m85xxI2cWrite
     (
     UINT32  busNum,
     void *pArgs
     )
{

    sM85xx_I2C_DRV * pDrvModule = (sM85xx_I2C_DRV *)vxbDevSoftcGet(pI2CModuleInst);
    sBSP_I2C_CTRL * pM85xxI2cCtrlData = &pDrvModule->m85xxI2cCtrlData[busNum];
    sM85XX_I2C_REGS *pRegs = (sM85XX_I2C_REGS *)pM85xxI2cCtrlData->baseAdrs;
    sBSP_I2C_PARAMS         *pParams = pArgs;
    UINT8                   *pBuffer = pParams->pBuffer;
    UINT32 i = 0;
    UINT32 eTimeout =0;
    
    if ( pDrvModule == NULL )
    {
        return ERROR;    
    }
    
    /*
     * Enable Acknowledge on receive
     */
    m85xxI2c_EnableRxAck(pRegs);

    /*
     * Start condition
     * Wakes up all slaves to listen for a slave address.
     */
    m85xxI2c_StartCondition(pRegs);

    /*
     * Start condition
     * Wait the usual 5uS setup time after a START.
     */
    sysUsDelay(M85XX_I2C_START_SETUP);

    /*
     * Addressing cycle.
     * Issue address on the I2C bus.
     */
    m85xxI2c_WriteByte(pRegs, ((UINT8)(pParams->address << M85XX_I2C_ADDR_RW_SHIFT) & ~M85XX_I2C_ADDR_RW_BIT));

    /*
     * Wait for the transaction to begin.
     */
    sysUsDelay(M85XX_I2C_TRANS_SETUP);
    
    /*
     * Addressing cycle
     * Wait for interrupt to happen.
     * If interrupt, address ack'ed, if no interrupt, timeout.
     */
        eTimeout = 0;
        while(!(m85xxI2c_IsInterruptActive(pRegs, M85XX_I2C_WRITE)))
        {
            sysMsDelay(1);
            if(eTimeout == M85XX_I2C_TIMEOUT)
            {
#if defined(DEBUG_M85xxI2C)
                printf("I2CSR=0x%x, LineNum = %d\n",pRegs->I2CSR, __LINE__);
#endif  
                /* Recover before returning ERROR */
                m85xxI2c_ClearInt(pRegs);
                m85xxI2c_StopCondition(pRegs);
                sysUsDelay(M85XX_I2C_STOP_SETUP);
                
                /* Reinitialize the controller to clear any bus lockup */
                vxbM85xxI2cCtrlHwInit(pM85xxI2cCtrlData);
                return(ERROR);
            }
            else
                eTimeout++;
        }

    /*
     * Clear interrupt
     */
    m85xxI2c_ClearInt(pRegs);

    /*
     * Command/Offset cycle
     * Issue command/offset on the I2C bus.
     */
    m85xxI2c_WriteByte(pRegs, pParams->offset);

    /*
     * Command/Offset cycle
     * Wait for interrupt to happen.
     * If interrupt, address ack'ed, if no interrupt, timeout.
     */
        eTimeout = 0;
        while(!(m85xxI2c_IsInterruptActive(pRegs, M85XX_I2C_WRITE)))
        {
            sysMsDelay(1);
            if(eTimeout == M85XX_I2C_TIMEOUT)
            {
#if defined(DEBUG_M85xxI2C)
                printf("I2CSR=0x%x, LineNum = %d\n",pRegs->I2CSR, __LINE__);
#endif  
                /* Recover before returning ERROR */
                m85xxI2c_ClearInt(pRegs);
                m85xxI2c_StopCondition(pRegs);
                sysUsDelay(M85XX_I2C_STOP_SETUP);
                
                /* Reinitialize the controller to clear any bus lockup */
                vxbM85xxI2cCtrlHwInit(pM85xxI2cCtrlData);
                return(ERROR);
            }
            else
                eTimeout++;
        }

    /*
     * Clear interrupt
     */
    m85xxI2c_ClearInt(pRegs);

    /*
     * Data write cycle
     */
    for(i=0; i < pParams->size; i++)
    {
        m85xxI2c_WriteByte(pRegs, pBuffer[i]);

        eTimeout = 0;
        while(!(m85xxI2c_IsInterruptActive(pRegs, M85XX_I2C_WRITE)))
        {
            sysMsDelay(1);
            if(eTimeout == M85XX_I2C_TIMEOUT)
            {
    #if defined(DEBUG_M85xxI2C)
                printf("I2CSR=0x%x, LineNum = %d\n",pRegs->I2CSR, __LINE__);
    #endif  
                /* Recover before returning ERROR */
                m85xxI2c_ClearInt(pRegs);
                m85xxI2c_StopCondition(pRegs);
                sysUsDelay(M85XX_I2C_STOP_SETUP);
                
                /* Reinitialize the controller to clear any bus lockup */
                vxbM85xxI2cCtrlHwInit(pM85xxI2cCtrlData);
                return(ERROR);
            }
            else
                eTimeout++;
        }

        /*
         * Clear interrupt
         */
        m85xxI2c_ClearInt(pRegs);
    }

    /*
     * File stop condition on the bus.
     */
    m85xxI2c_StopCondition(pRegs);

    /*
     * Stop condition
     * Wait some setup time after a STOP.
     */
    sysUsDelay(M85XX_I2C_STOP_SETUP);

    return(OK);
}
/***************************************************************************
*
* bspI2cWrite - I2C bus write
*
* This routine writes to a device on an I2C bus.
*
* PARAMETERS:
* \is
* \i 'bus'
* Bus number (I2C_BUS_0, I2C_BUS_1)
* \i 'devAddr'
* I2C device address
* \i 'offset'
* I2C offset (0 - 255 or I2C_NO_OFFSET)
* \i 'buf'
* buffer pointer
* \i 'len'
* number of bytes
* \ie
* RETURNS: OK, or ERROR
*
* ERRNO:
*  S_bspI2c_INVALID_PARAMETER
*  S_bspI2c_SEM_FAILED
*
* SOURCE FILES:${BSP_DIR}/vxbM85xxI2c.c, ${BSP_DIR}/vxbM85xxI2c.h
*
* RELATED FUNCTIONS: bspI2cRead()
*/
STATUS bspI2cWrite
   (
   UINT32  bus,
   UINT32  devAddr,
   UINT32  offset,
   UINT8   *buf,
   UINT32  len
   )
{
    sM85xx_I2C_DRV * pDrvModule = (sM85xx_I2C_DRV *)vxbDevSoftcGet(pI2CModuleInst);
    sBSP_I2C_PARAMS sI2cParams;
    STATUS stat;
    
    if ( pDrvModule == NULL )
    {
        return ERROR;    
    }
    
    if ((bus >= I2C_BUS_MAX) ||
       (offset >= I2C_OFFSET_MAX) ||
       (buf == NULL) ||
       (len == 0))
    {
        ERRNOSET(S_bspI2c_INVALID_PARAMETER);
        return ERROR;
    }

    if (OK != semTake(pDrvModule->m85xxI2cModuleAccessSem, WAIT_FOREVER))
    {
        ERRNOSET(S_bspI2c_SEM_FAILED);
        return(ERROR);
    }
       /*
     * Setup the parameter structure.
     */
    sI2cParams.pBuffer = buf;
    sI2cParams.size = (UINT8)len;
    sI2cParams.address = (UINT8)devAddr;
    sI2cParams.offset = (UINT8)offset;

    stat = m85xxI2cWrite(bus,&sI2cParams);

    if (OK != semGive(pDrvModule->m85xxI2cModuleAccessSem))
    {
        ERRNOSET(S_bspI2c_SEM_FAILED);
        return(ERROR);
    }

    return (stat);
}

/***************************************************************************
*
* bspI2cRead - I2C bus read
*
* This routine reads from a device on an I2C bus.
*
* PARAMETERS:
* \is
* \i 'bus'
* Bus number (I2C_BUS_0, I2C_BUS_1)
* \i 'devAddr'
* I2C device address
* \i 'offset'
* I2C offset (0 - 255, I2C_NO_OFFSET: don't use offset)
* \i 'buf'
* buffer pointer
* \i 'len'
* number of bytes
* \ie
* RETURNS: OK, or ERROR
*
* ERRNO:
*  S_bspI2c_INVALID_PARAMETER
*  S_bspI2c_SEM_FAILED
*
* SOURCE FILES:${BSP_DIR}/vxbM85xxI2c.c, ${BSP_DIR}/vxbM85xxI2c.h
*
* RELATED FUNCTIONS: bspI2cWrite()
*/
STATUS bspI2cRead
   (
   UINT32  bus,
   UINT32  devAddr,
   UINT32  offset,
   UINT8   *buf,
   UINT32  len
   )
{
    sM85xx_I2C_DRV * pDrvModule = (sM85xx_I2C_DRV *)vxbDevSoftcGet(pI2CModuleInst);
    sBSP_I2C_PARAMS sI2cParams;
    STATUS stat;

    if ( pDrvModule == NULL )
    {
        return ERROR;
    }
    
    if ((bus >= I2C_BUS_MAX) ||
       (offset >= I2C_OFFSET_MAX) ||
       (buf == NULL) ||
       (len == 0))
    {
        ERRNOSET(S_bspI2c_INVALID_PARAMETER);
        return ERROR;
    }

    if (OK != semTake(pDrvModule->m85xxI2cModuleAccessSem, WAIT_FOREVER))
    {
        ERRNOSET(S_bspI2c_SEM_FAILED);
        return(ERROR);
    }
       /*
     * Setup the parameter structure.
     */
    sI2cParams.pBuffer = buf;
    sI2cParams.size = (UINT8)len;
    sI2cParams.address = (UINT8)devAddr;
    sI2cParams.offset = (UINT8)offset;

    stat = m85xxI2cRead(bus,&sI2cParams);

    if (OK != semGive(pDrvModule->m85xxI2cModuleAccessSem))
    {
        ERRNOSET(S_bspI2c_SEM_FAILED);
        return(ERROR);
    }

    return (stat);
}

/***************************************************************************
*
* bspI2cAraRead - I2C ARA (Alert Response Address)
*
* This routine issues an ARA on an I2C bus.
*
* PARAMETERS:
* \is
* \i 'bus'
* Bus number (I2C_BUS_0, I2C_BUS_1)
* \i 'buf'
* buffer pointer
* \ie
* RETURNS: OK, or ERROR
*
* ERRNO:
*  S_bspI2c_INVALID_PARAMETER
*  S_bspI2c_SEM_FAILED
*
* SOURCE FILES:${BSP_DIR}/vxbM85xxI2c.c, ${BSP_DIR}/vxbM85xxI2c.h
*
* RELATED FUNCTIONS: bspI2cWrite()
*/
STATUS bspI2cAraRead
   (
   UINT32  bus,
   UINT8   *buf 
   )
{
    sM85xx_I2C_DRV * pDrvModule = (sM85xx_I2C_DRV *)vxbDevSoftcGet(pI2CModuleInst);
    STATUS stat;
   
    if ( pDrvModule == NULL )
    {
        return ERROR;
    }
    
    if ((bus >= I2C_BUS_MAX) ||
       (buf == NULL))
    {
        ERRNOSET(S_bspI2c_INVALID_PARAMETER);
        return ERROR;
    }

    if (OK != semTake(pDrvModule->m85xxI2cModuleAccessSem, WAIT_FOREVER))
    {
        ERRNOSET(S_bspI2c_SEM_FAILED);
        return(ERROR);
    }      

    stat = m85xxI2cAraRead(bus,buf);

    if (OK != semGive(pDrvModule->m85xxI2cModuleAccessSem))
    {
        ERRNOSET(S_bspI2c_SEM_FAILED);
        return(ERROR);
    }

    return (stat);
}


/******************************************************************************
*
* vxbM85xxI2cObjLink - Function used to allow object file import into Kernel
*
* \NOMANUAL
*/
STATUS vxbM85xxI2cObjLink(void) {
    return OK;
}
#undef __CMFILE__
/* END OF FILE */

