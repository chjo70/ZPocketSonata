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

/**
    @brief		프로그램의 기본 정보를 디스플레이한다.
    @param
    @return
    @exception
*/
void Disp_SysInfo(void)
{
    printf("\r\n\r\n");
    printf(" ############################################################\r\n");
    printf(" - ProjectName Application Program\r\n");
    printf(" - Version : 20201215_1\r\n");
    printf(" - Date : %s, Time : %s\r\n", __DATE__, __TIME__);
    //dp(" ############################################################\r\n");
}

void Hw_Init(void)
{
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
    reg_write(BRAM_CTRL_0,ILA_CH_SEL1,0x10);
    reg_write(BRAM_CTRL_0,DMA_TEST_D_ON,0x0);
    reg_write(BRAM_CTRL_PPFLT,DF_WAIT_T,0xA00); // 방탐데이터 기다리는 시간 입력
    reg_write(BRAM_CTRL_PPFLT,MON_CH_SEL,0x0);
    reg_write(BRAM_CTRL_PPFLT,CFAR_nCLR,0);
    reg_write(BRAM_CTRL_PPFLT,CFAR_BEATN,0x7F00);
    reg_write(BRAM_CTRL_PPFLT,CFAR_MODE_ON,0);
    reg_write(BRAM_CTRL_PPFLT,DET_THD_COR,50);
    reg_write(BRAM_CTRL_PPFLT,DET_THD_MAG,50);
    reg_write(BRAM_CTRL_PPFLT,DET_ONLY_COR,0x0);
    reg_write(BRAM_CTRL_PPFLT,PW_AUTO_THD_MIN,0x0);
    reg_write(BRAM_CTRL_PPFLT,PPF_SLICE,0x2);
    reg_write(BRAM_CTRL_PPFLT,PPF_SLICE_FFT,0x3);
    reg_write(BRAM_CTRL_0,DMA_BURST_SIZE,PDW_GATHER_SIZE);
//	reg_write(BRAM_CTRL_0,DMA_BURST_SIZE,3);

    reg_write(BRAM_CTRL_0,TEST_DATA_WRITE,0x12345678);

    ui32 temp = reg_read(BRAM_CTRL_0,TEST_DATA_READ);
    printf("AXI BUS TEST : 0x%08X\n", temp);

    //DF_RX & GenTech Init Check
    //ui32 rd_temp;
    //float	uiTimeRes = 0.488;	// 		샘플률 2048 MHz = 488 ps
// by yohan's
//	reg_write(BRAM_DF_RX, DF_RX_SLICE_DF_IN, 3);

//    rd_temp = reg_read(BRAM_DF_RX,DF_RX_FW_VER); 	printf("DF_RX FW_VER : 0x%08X[%d]\n", rd_temp, rd_temp);
//    rd_temp = reg_read(BRAM_TECH,GenTech_FW_VER); 	printf("DF_RX FW_VER : 0x%08X[%d]\n", rd_temp, rd_temp);
//
//    rd_temp = reg_read(BRAM_DF_RX,DF_RX_RD_TEST); 	printf("DF_RX RD_TEST : 0x%08X\n", rd_temp);
//    rd_temp = reg_read(BRAM_TECH,GenTech_RD_TEST); 	printf("DF_RX RD_TEST : 0x%08X\n", rd_temp);

    // by yohan's
//    // GenTech Gen Pulse
//	reg_write(BRAM_TECH, GenTech_SET_DAC_MUX, 1);
//	reg_write(BRAM_TECH, GenTech_SET_PRI, (ui32)(1000000/uiTimeRes));  // PRI = 1ms
//	reg_write(BRAM_TECH, GenTech_SET_PW, (ui32)(1000/uiTimeRes));		 // PW = 1us
//	reg_write(BRAM_TECH, GenTech_SET_PH_INCR, 0x00A00000);	// 5 MHz = 0x00A0_0000
    // by yohan's end
//	reg_write(BRAM_TECH, GenTech_PULSE_EN, 1);

//    // DF_RX Init
    // NCO GEN
    // by yohan's
//	reg_write(BRAM_DF_RX, DF_RX_PH_INCR, 0x00800000);	// 4 MHz = 0x0080_0000
    // by yohan's end
    //	reg_write(BRAM_DF_RX, DF_RX_PH_INCR, 0xFF800000);	// -4 MHz = 0xFF80_0000

}

int main()
{
    Disp_SysInfo();

    hw_open();
    Hw_Init();
    startISR();

    while(1)
    {

    }

    return 0;
}
