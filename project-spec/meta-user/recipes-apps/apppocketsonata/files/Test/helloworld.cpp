/*
 * Copyright (c) 2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <stdio.h>
#include "hw_interface.h"
#include "api/dma.h"
#include "unistd.h"

extern pthread_t 			g_pThread_ID_ISR[XUIO_INTR_COUNT];

int main()
{
    printf("Hello World\n");

    hw_open();

// ****************************************************************
//    1. ADC_BITSlice 	: ( 16>>3 )
//    2. IQ Switch		: 1:test / 0:normal
//    3. DMA_TEST_D SEL 	: 1:test / 0:normal
//    4. ILA_CH_SEL		: ILA_CH_SEL1 <= D(7 downto 4) , ILA_CH_SEL0<=D(3 downto 0);
//    5. DMA_TEST_D_ON 	: 1:test DATA / 0:PDW DATA
//    6. DET_THD_COR		: 16bit, res = ??
//    7. DET_THD_MAG		: 16bit, res = ??
//    8. DET_ONLY_COR		: 1bit, res = ??

	reg_write(BRAM_CTRL_0,ADC_BIT_SLICE,0x2);
	reg_write(BRAM_CTRL_0,IQ_SOURCE_SW,0x0);
	reg_write(BRAM_CTRL_0,ILA_CH_SEL1,0x1);
	reg_write(BRAM_CTRL_0,DMA_TEST_D_ON,0x0);
	reg_write(BRAM_CTRL_PPFLT,MON_CH_SEL,0x0);
	reg_write(BRAM_CTRL_PPFLT,DET_THD_COR,0x300);
	reg_write(BRAM_CTRL_PPFLT,DET_THD_MAG,0x300);
	reg_write(BRAM_CTRL_PPFLT,DET_ONLY_COR,0x0);
	reg_write(BRAM_CTRL_0,DMA_BURST_SIZE,PDW_GATHER_SIZE);
//	reg_write(BRAM_CTRL_0,DMA_BURST_SIZE,3);

    reg_write(BRAM_CTRL_0,TEST_DATA_WRITE,0x12345678);
    ui32 temp = reg_read(BRAM_CTRL_0,TEST_DATA_READ);
    printf("AXI BUS TEST : 0x%08X\n", temp);

    startISR();


    while(1)
    {

    }

    return 0;
}
