/*
 * hw_interface.c
 *
 *  Created on: 2020. 8. 6.
 *      Author: LIGNEX1
 */

#include <string.h>
#include <stdio.h>
#include <fcntl.h>		// open() �Լ�
#include <sys/mman.h>   // mmap() �Լ�
#include <stdlib.h>
#include <unistd.h> // read, write
#include <endian.h>
#include <sys/errno.h> // ENOMSG
#include <sys/ioctl.h>
#include <math.h>
#include "hw_interface.h"
#include "api/dma.h"

#define _HW_INTER_

#define ERROR					-1
#define	OK						0
#define THREAD_CREATE_FAIL		ERROR

pthread_t 	g_pThread_ID_ISR[XUIO_INTR_COUNT];

//void reg_write_64(ui64 *logical, ui32 offset, ui32 value)
//{
//	*(volatile ui64 *)(logical + (offset/8)) = value;
//}
//
//ui64 reg_read_64(ui64 *logical, ui32 offset)
//{
//	return *(volatile ui64 *)(logical + (offset/8));
//}

/*****************************************************************
* Fpga Register R/W
******************************************************************/
void reg_write(uint8_t sel, uint32_t offset, ui32 value)
{
    if (sel >= XMEM_COUNT || xmem[sel].logical == 0) return;

//    printf( "reg_write=%d\n" , sel );
	*(volatile ui32 *)(xmem[sel].logical + (offset)) = value;
}

ui32 reg_read(uint8_t sel, uint32_t offset)
{
    if (sel >= XMEM_COUNT || xmem[sel].logical == 0) return 0;

//    printf( "reg_read=%d\n" , sel );
	return *(volatile ui32 *)(xmem[sel].logical + (offset));
}

/*****************************************************************
* Mem Offset
******************************************************************/
xmem_t *mem_get_mem(uint8_t sel)
{
    xmem_t *pRet;

    if (sel >= XMEM_COUNT && xmem[sel].logical == 0) {
        printf( "\n error of mem_get_mem" );
        pRet = NULL;
    }
    else {
        pRet =  & xmem[sel];
//        printf( "mem_get_mem:%p\n" , pRet );
    }

    return pRet;
}

xmem_t mem_offset( xmem_t *mem, uint32_t offset )
{
	xmem_t ret;
	ret.physical = mem->physical + offset;
	ret.logical = mem->logical + offset;
	ret.size = 0;

	return ret;
}

/**
 * @brief GPIO device �� xuio_t Ÿ���� ���� device �ν��Ͻ� ������ ����
 * @param sel �������� GPIO device �߿� ������ device ��(mem.h �� uio_dev_t ������ Ÿ��)
 * @return GPIO device �� xuio_t Ÿ���� ���� device �ν��Ͻ� ������ ����
 */
xuio_t *uio_get_uio(uint8_t sel)
{

	if (sel >= XUIO_COUNT && xuio[sel].logical == 0) return NULL;

    printf( " xuio = %d\n" , sel );
    printf( " \tfd=%d\n" , xuio[sel].fd );
    printf( " \tphysical=%lx\n" , xuio[sel].physical );
    printf( " \tlogical=%lx\n" , xuio[sel].logical );
    printf( " \tsize=%d\n" , xuio[sel].size );
    printf( " \tdev=%s\n" , xuio[sel].dev );

	return &xuio[sel];
}

/**
	@brief		프로그램의 기본 정보를 디스플레이한다.
	@param
	@return
	@exception
*/

void hw_open(void)
{

//    printf( "uint64_t=%ld\n" , sizeof(uint64_t) );

    /**
     * dev/mem open
     */
    int fd = open("/dev/mem", O_RDWR | O_SYNC );
    if (fd < 0) {
        perror( "open" );
        return;
    }
    else {
        int i;
        for (i=0; i<XMEM_COUNT; i++)
        {
            if (xmem[i].physical > 0)
            {
                xmem[i].logical = (uint64_t)mmap(0, xmem[i].size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, xmem[i].physical);
            }
        }
        close( fd );

        /**
         * UIO open
         */
        xuio_t *uio;
        uio = NULL;
        for (i=0; i<XUIO_COUNT; i++)
        {
            uio = uio_get_uio(i);

            if(uio->fd == -1 ) {
                uio->fd = open(uio->dev, O_RDWR);
//                printf( " uio->fd[%d]\n" , uio->fd );

                if ( uio->fd != -1 )
                {
                    if (uio->physical > 0) {
                        uio->logical = (uint64_t)mmap(0, uio->size, PROT_READ | PROT_WRITE, MAP_SHARED, uio->fd, 0);
//                        printf( " logical[%ld]\n" , uio->logical );
                    }
                    else {
                        perror( "uio->physical" );
                    }
                }
                else {
                    char buffer[100];

                    sprintf( buffer, "open(%s)" , uio->dev );
                    perror( buffer );
                }
            }
            else {
                printf( "error of uio->fd[%d]\n" , uio->fd );
            }
        }

        printf( "dma_init...\n" );
        dma_init( dma_dev_1, REG_UIO_DMA_1 );
    }
}

void hw_close(void)
{
    int i;
    for (i=0; i<XMEM_COUNT; i++)
    {
    	if (xmem[i].logical > 0)
    	{
    		munmap((void *)xmem[i].logical, xmem[i].size);
        	xmem[i].logical = 0;
    	}
    }

   xuio_t *uio;
   uio = NULL;
   for (i=0; i<XUIO_COUNT; i++)
	{
		uio = uio_get_uio(i);

		if ( uio->fd != -1 )
		{
			if (uio->logical > 0)
			{
				munmap((void *)uio->logical, uio->size);
				uio->logical = 0;
			}
			close(uio->fd);
		}
	}
}

/**
 * @brief PL�κ��� ���ŵǴ�  GPIO ���ͷ�Ʈ��  read �Լ� wrapping �Լ�
 * @param fd GPIO file descriptor
 */
bool PendingFromInterrupt(xuio_t *uio)
{
	int pending = 0;

	// block on the file waiting for an interrupt */
	(void)read(uio->fd, (void *)&pending, sizeof(int));

    return true;
}

/**
 * @brief PL�κ��� ���ŵ�  UIO ���ͷ�Ʈ ��Ȱ��ȭ
 * @param uio 		UIO ����ü ������
 */
void uio_re_enable_Interrupt(xuio_t *uio)
{
	int reenable = 1;

	// ���ͷ�Ʈ ��Ȱ��ȭ
	write(uio->fd, (void *)&reenable, sizeof(int));
}

/**
 * @brief PL�κ��� ���ŵ�  UIO ���ͷ�Ʈ ����
 * @param uio 		UIO ����ü ������
 * @param uiChNum 	���ŵ� ���ͷ�Ʈ ��ȣ(0, 1)
 */
void ClearInterrupt(xuio_t *uio)
{
	switch(uio->physical)
	{
	case UIO_DMA_1_ADDR :
	{
		dma_s2mm_stop(dma_dev_1);
		dma_s2mm_irq_clear(dma_dev_1);
	}
	break;
	default :
	{

	}
	break;
	}
}

static void *ISRhandler(void* arg)
{
//	i32 irtnvalue = 0;
//
//	ui32 reg;

	xuio_t *s_uio = (xuio_t*)arg;

	pdw_reg_t s_pdw_reg_t;

	ui32 DataCount = PDW_GATHER_SIZE; //������ ����
	ui32 DumpLen = 0; //Byte ����
	ui32 sFreq = 0;
	ui64 sToa = 0;
	ui64 sToa_H = 0;
	ui64 DeltaToa = 0;
	ui32 rFreq = 0;
	double dPa = 0;
	ui8 pbuf_t[32] = {0, };
	char chno = 0;
	ui32 sPrintCnt = 0;
	ui32 k = 0;

	DumpLen = sizeof(ui8)*DataCount;

	memset(&s_pdw_reg_t, 0, sizeof(s_pdw_reg_t));
	ui8 *pbuf = NULL;

	while(1)
	{
		xmem_t *mem = mem_get_mem(DMA_1_MEM);

		dma_s2mm_reset(dma_dev_1);
		dma_s2mm_start(dma_dev_1, mem, DumpLen, false);

		PendingFromInterrupt(s_uio);

		switch(s_uio->physical)
		{
			case UIO_DMA_1_ADDR :
			{
				ClearInterrupt(s_uio);

				pbuf = (ui8 *) malloc(DataCount);
				memcpy((void *)pbuf,(void *)(mem->logical),DataCount);

				for(k = 0; k < PDW_GATHER_SIZE/32; k++)
				{
					for(int i = 31; i >= 0; i--)
					{
	//					printf("%02X",pbuf[i+(32*k)]);
						pbuf_t[31-i] = pbuf[i+(32*k)];
					}
					memcpy(&s_pdw_reg_t, &pbuf_t, sizeof(s_pdw_reg_t));

					s_pdw_reg_t.uniPdw_status.pdw_status = __bswap_32(s_pdw_reg_t.uniPdw_status.pdw_status);
					s_pdw_reg_t.uniPdw_dir_pa.pdw_dir_pa = __bswap_32(s_pdw_reg_t.uniPdw_dir_pa.pdw_dir_pa);
					s_pdw_reg_t.uniPdw_pw_freq.pdw_pw_freq = __bswap_32(s_pdw_reg_t.uniPdw_pw_freq.pdw_pw_freq);
					s_pdw_reg_t.uniPdw_freq_toa.pdw_freq_toa = __bswap_32(s_pdw_reg_t.uniPdw_freq_toa.pdw_freq_toa);
					s_pdw_reg_t.uniPdw_toa_edge.pdw_toa_edge = __bswap_32(s_pdw_reg_t.uniPdw_toa_edge.pdw_toa_edge);
					s_pdw_reg_t.uniPdw_index.pdw_index = __bswap_32(s_pdw_reg_t.uniPdw_index.pdw_index);

					sToa_H = s_pdw_reg_t.uniPdw_toa_edge.stPdw_toa_edge.toa_H;
					sFreq 	= (s_pdw_reg_t.uniPdw_freq_toa.stPdw_freq_toa.frequency_H << 8) | s_pdw_reg_t.uniPdw_pw_freq.stPdw_pw_freq.frequency_L;
					sToa	= (sToa_H << 16) | s_pdw_reg_t.uniPdw_freq_toa.stPdw_freq_toa.toa_L;

					dPa = s_pdw_reg_t.uniPdw_dir_pa.stPdw_dir_pa.pa;
					dPa = PDW_PA_INIT + 20*log10(dPa);
					chno = s_pdw_reg_t.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch;
					if(chno < 7)
					{
						if(sFreq & 0x8000)
						{
							sFreq = 0x10000 - sFreq;
							rFreq = (ui32)(CENT_FREQ + (PH_WIDTH_FREQ * chno) - (sFreq*PDW_FREQ_RES));
						}
						else
						{
							rFreq = (ui32)(CENT_FREQ + (PH_WIDTH_FREQ * chno) + (sFreq*PDW_FREQ_RES));
						}
					}
					else
					{
						chno = 15 - s_pdw_reg_t.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch;
						if(sFreq & 0x8000)
						{
							sFreq = 0x10000 - sFreq;
							rFreq = (ui32)(CENT_FREQ - (PH_WIDTH_FREQ * chno) - (sFreq*PDW_FREQ_RES));
						}
						else
						{
							rFreq = (ui32)(CENT_FREQ - (PH_WIDTH_FREQ * chno) + (sFreq*PDW_FREQ_RES));
						}
					}
					printf("\n");
					printf(">> pdw_index	= %d\n", s_pdw_reg_t.uniPdw_index.stPdw_index.index);
					printf(">> ph_ch	= %d\n", s_pdw_reg_t.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch);
					printf(">> cw_pulse 	= %d\n", s_pdw_reg_t.uniPdw_status.stPdw_status.cw_pulse);
					printf(">> pmop_flag	= %d\n", s_pdw_reg_t.uniPdw_status.stPdw_status.pmop);
					printf(">> fmop_flag	= %d\n", s_pdw_reg_t.uniPdw_status.stPdw_status.fmop);
					printf(">> false_pdw	= %d\n", s_pdw_reg_t.uniPdw_status.stPdw_status.false_pdw);
					printf(">> fmop_dir 	= %d\n", s_pdw_reg_t.uniPdw_status.stPdw_status.fmop_dir);
					printf(">> fmop_bw 	= %f\n", s_pdw_reg_t.uniPdw_status.stPdw_status.fmop_bw*PDW_FREQ_RES);
					printf(">> doa 		= %f\n", s_pdw_reg_t.uniPdw_dir_pa.stPdw_dir_pa.doa*PDW_AOA_RES); //deg
					printf(">> di	 	= %d\n", s_pdw_reg_t.uniPdw_dir_pa.stPdw_dir_pa.di);
					printf(">> pa 		= %5.2f[%d]\n", dPa, s_pdw_reg_t.uniPdw_dir_pa.stPdw_dir_pa.pa);
					printf(">> pw		= %f[ns]\n", s_pdw_reg_t.uniPdw_pw_freq.stPdw_pw_freq.pulse_width*PDW_TIME_RES); //ns
					printf(">> frequency	= %d[MHz]\n", rFreq);
					printf(">> Dtoa		= %f[us]\n", sToa*PDW_TIME_RES/1000 - DeltaToa); //us
					DeltaToa = sToa*PDW_TIME_RES/1000;
					printf(">> toa		= %f[us]\n", sToa*PDW_TIME_RES/1000); //us
					printf(">> edge		= %d\n", s_pdw_reg_t.uniPdw_toa_edge.stPdw_toa_edge.edge);

//					sPrintCnt++;
				}
				printf(">> pdw_index	= %d, sPrintCnt = %d\n", s_pdw_reg_t.uniPdw_index.stPdw_index.index, sPrintCnt);
//				if(k == PDW_GATHER_SIZE/32)
//				{
//					printf(">> pdw_index	= %d, k = %d\n", s_pdw_reg_t.uniPdw_index.stPdw_index.index, k);
//				}
			}
			break;

			default : 	{ 	} 	break;
		}
		uio_re_enable_Interrupt(s_uio);
	}

	return NULL;
}

i32 startISR(void)
{
	i32 iRtnValue = 0;

	xuio_t *uio;
	uio = NULL;

	uio = uio_get_uio((uint8_t)REG_UIO_DMA_1);
	iRtnValue = pthread_create(&g_pThread_ID_ISR[(uint64_t)REG_UIO_DMA_1], NULL, ISRhandler, (void*)uio);
//	iRtnValue = pthread_create(&g_pThread_ID_ISR[(uint32_t)REG_UIO_DMA_1], NULL, ISRhandler, (void*)uio);
	if(iRtnValue == ERROR)
	{
		goto ERROR_PATH;
	}
	return iRtnValue;

ERROR_PATH:
	return iRtnValue;
}

//void SetInterruptRegister(void *irq_ptr)
//{
//	gpio_write(irq_ptr, GPIO_TRI_OFFSET,0xF);  // IO pin configured as input
//	gpio_write(irq_ptr, GPIO_GLOBAL_IRQ,0x80000000);  // global interrupt enable
//	gpio_write(irq_ptr, GPIO_IRQ_CONTROL,1);
//}
