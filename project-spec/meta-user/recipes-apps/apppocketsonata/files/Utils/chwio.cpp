
#include "stdafx.h"

#include <string.h>
#include <stdio.h>
#include <fcntl.h>		// open() �Լ�
#include <stdlib.h>

#ifdef __linux__
#include <unistd.h>
#include <endian.h>
#include <sys/mman.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#endif

#ifndef __ZYNQ_BOARD__
#define _SIM_USER_COLLECT_
#endif



#include "chwio.h"
#include "./DMA/dma.h"


#include "../Utils/clog.h"

#include "../Include/globals.h"

xuio_t CHWIO::m_xuio[XUIO_COUNT] = {
    { -1, 0x1000, UIO_DMA_1_ADDR, 0U, "/dev/uio4" }, //DMA 0 Control Register
};

unsigned int CHWIO::m_uiCoInterrupt=0;

CHWIO::CHWIO()
{
    // m_uiCoInterrupt = 0;
}

/**
 * @brief CHWIO::OpenHW
 */
void CHWIO::OpenHW()
{
    
#ifdef __linux__
    xuio_t *pUIO;

    /**
     * dev/mem open
     */
    int fd = open("/dev/mem", O_RDWR | O_SYNC );
    if (fd < 0) {
        perror( "open" );

#ifdef _SIM_USER_COLLECT_
        pUIO = uio_get_uio(0);
        //pUIO->fd = open("/home/chjo70/test", O_RDWR);
#endif
    }
    else {
        int i;
        for (i=0; i<XMEM_COUNT; i++)
        {
            if (xmem[i].ulphysical > 0) {
                xmem[i].ullogical = (uint64_t)mmap(0, xmem[i].uisize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, xmem[i].ulphysical);
            }
        }
        close( fd );

        /**
         * UIO open
         */

        pUIO = NULL;
        for (i=0; i<XUIO_COUNT; i++)
        {
            pUIO = uio_get_uio(i);

            if(pUIO->iFd == -1 ) {
                pUIO->iFd = open(pUIO->pszDev, O_RDWR);
                printf( " uio->fd[%d]\n" , pUIO->iFd );

                if ( pUIO->iFd != -1 ) {
                    if (pUIO->ullPhysical > 0) {
                        pUIO->ullLogical = (uint64_t)mmap(0, pUIO->size, PROT_READ | PROT_WRITE, MAP_SHARED, pUIO->iFd, 0);
                        printf( " logical[%ld]\n" , pUIO->ullLogical );
                    }
                }
                else {
                    char buffer[100];

                    sprintf( buffer, "open(%s)" , pUIO->pszDev );
                    perror( buffer );
                }
            }
            else {
                // printf( "error of \n uio->fd[%d]" , uio->fd );
            }
        }

        dma_init( dma_dev_1, REG_UIO_DMA_1 );
    }
#endif


}

/**
 * @brief CHWIO::WriteReg
 * @param sel
 * @param offset
 * @param value
 */
bool CHWIO::WriteReg(uint8_t sel, uint32_t offset, uint32_t value)
{
    bool bRet = true;

    if( sel >= XMEM_COUNT || xmem[sel].ullogical == 0) {
        LOGMSG3( enError, "Error of WriteReg(%d, %d) = 0x%X !!!" , sel, offset, value );
        bRet = false;
    }
    else {
        *(volatile uint32_t *)(xmem[sel].ullogical + (offset)) = value;
        LOGMSG3( enNormal, "WriteReg(%d, %d) = 0x%X !!!" , sel, offset, value );

    }

    return bRet;
}

/**
 * @brief ReadReg
 * @param sel
 * @param offset
 * @return
 */
uint32_t CHWIO::ReadReg(uint8_t sel, uint32_t offset)
{
    uint32_t uiVal = 0;

    if (sel >= XMEM_COUNT || xmem[sel].ullogical == 0) {

    }
    else {
        uiVal = *(volatile uint32_t *)(xmem[sel].ullogical + (offset));
    }

    return uiVal;
}

/**
 * @brief CHWIO::uio_get_uio
 * @param sel
 * @return
 */
xuio_t *CHWIO::uio_get_uio(uint8_t sel)
{
    if (sel >= XUIO_COUNT && m_xuio[sel].ullLogical == 0) { printf( "\n error of uio_get_uio" ); return NULL; }
    return & m_xuio[sel];
}

/**
 * @brief mem_get_mem
 * @param sel
 * @return
 */
xmem_t *CHWIO::mem_get_mem(uint8_t sel)
{
    xmem_t *pRet;

    if (sel >= XMEM_COUNT && xmem[sel].ullogical == 0) {
        printf( "\n error of mem_get_mem" );
        pRet = NULL;
    }
    else {
        pRet =  & xmem[sel];
        //printf( "mem_get_mem:%p\n" , pRet );
    }

    return pRet;
}

/**
 * @brief mem_offset
 * @param mem
 * @param offset
 * @return
 */
xmem_t CHWIO::mem_offset( xmem_t *mem, uint32_t offset )
{
    xmem_t ret;
    ret.ulphysical = mem->ulphysical + offset;
    ret.ullogical = mem->ullogical + offset;
    ret.uisize = 0;

    return ret;
}

/**
 * @brief CHWIO::PendingFromInterrupt
 * @param uio
 */
bool CHWIO::PendingFromInterrupt(xuio_t *uio)
{
    bool bRet=true;

    int pending = 0;
    
    //printf( "\n uio->fd[%d]\n", uio->fd );
    if( uio->iFd != -1 ) {
#ifdef __linux__
        struct timeval timeout;
        int rv;
        fd_set set;

        FD_ZERO( & set ); /* clear the set */
        FD_SET( uio->iFd, & set ); /* add our file descriptor to the set */

        timeout.tv_sec = 10;
        timeout.tv_usec = 00000;

        rv = select( uio->iFd + 1, & set, NULL, NULL, & timeout );
        if( rv == -1 ) {
            perror( "select" ); /* an error accured */
        }
        else if( rv == 0 ) {
            LOGMSG( enNormal, "PendingFromInterrupt() .........timeout" );
            bRet = false;
        }
        else {
            (void) read(uio->iFd, (void *)&pending, sizeof(int));
        }
#endif
    }
    else {
#ifdef _SIM_USER_COLLECT_
        int iModular;

        iModular = m_uiCoInterrupt % 50;

        if( iModular <= 40 ) {
            bRet = true;
        }
        else {
            bRet = false;
        }
#else
        LOGMSG1( enError, "VME 인터럽트 핸들러 에러[%d] !!!" , uio->fd );
        bRet = false;
#endif

    }

    ++ m_uiCoInterrupt;

    return bRet;

}

/**
 * @brief CHWIO::ClearInterrupt
 * @param uio
 */
void CHWIO::ClearInterrupt(xuio_t *uio)
{

    switch( uio->ullPhysical ) {
        case UIO_DMA_1_ADDR :
            {
#ifdef __ZYNQ_BOARD__
                //printf( "dma_s2mm_stop .........\n" );
                dma_s2mm_stop( dma_dev_1 );

                //printf( "dma_s2mm_irq_clear .........\n" );
                dma_s2mm_irq_clear( dma_dev_1 );
#endif
            }
            break;

        default :
            {
                printf( " switch default...\n" );
            }
            break;
    }

}

/**
 * @brief CHWIO::uio_re_enable_Interrupt
 * @param uio
 */
void CHWIO::uio_re_enable_Interrupt( ENUM_UIO_DEV enUIO )
{
#ifndef _SIM_USER_COLLECT_
    int reenable = 1;
    xuio_t *pUIO = (xuio_t*) CHWIO::uio_get_uio( (uint8_t) enUIO );

    // ���ͷ�Ʈ ��Ȱ��ȭ
    write(pUIO->iFd, (void *)& reenable, sizeof(int) );
#endif
}

/**
 * @brief CHWIO::StopCollecting
 */
void CHWIO::StopCollecting( ENUM_UIO_DEV enUIO )
{
    xuio_t *pUIO = (xuio_t*) CHWIO::uio_get_uio( (uint8_t) enUIO );

    if( pUIO != NULL ) {
        printf( "\n StopCollecting[%d]::::::::::::::::\n ", pUIO->iFd );
    }
    else {
        printf( "\n StopCollecting[NULL]::::::::::::::::\n " );
    }

    //close( pUIO->fd );
    //pUIO->fd = -1;

}

/**
 * @brief CHWIO::StartCollecting
 * @param enUIO
 */
void CHWIO::StartCollecting( ENUM_UIO_DEV enUIO )
{
    xuio_t *pUIO = (xuio_t*) CHWIO::uio_get_uio( (uint8_t) enUIO );

    // 재 파일을 오픈합니다.

    //pUIO->fd = open( pUIO->dev, O_RDWR);
    if( pUIO != NULL ) {
        printf( "\n StartCollecting[%d]::::::::::::::::\n", pUIO->iFd );
    }
    else {
        printf( "\n StartCollecting[NULL]::::::::::::::::\n" );
    }


}
