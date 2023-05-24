﻿/*****************************************************************************************

    @file      curbit.cpp
    @brief     자체점검을 처리하는 쓰레드 입니다.
    @details   ~
    @author    조철희
    @date      10.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

*****************************************************************************************/

#include "stdafx.h"

#include "curbit.h"
#include "ccgi.h"

#ifdef __VXWORKS__
#include <hwif/vxBus.h>
#include <hwif/vxbus/vxbLib.h>

#include "vxbM85xxI2c.h"
#include "vxbAdt7481Temp.h"

extern "C" {

    // BSP 수록... 변수명이 global 하게 안 보입니다.
    // extern VXB_DEV_ID pAdt7481Inst;
}

#endif


//#include "../Utils/chwio.h"
#include "../Utils/ccommonutils.h"
#include "../Include/globals.h"




#define _DEBUG_

/**
 * @brief     자체점검 객체를 생성합니다.
 * @param     int iKeyId
 * @param     const char * pClassName
 * @param     bool bArrayLanData
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-02 10:00:08
 * @warning
 */
CUrBit::CUrBit( int iKeyId, const char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
    LOGENTRY;

    Init();

}

/**
 * @brief     자체점검 객체를 소멸합니다.
 * @param     void
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-02 10:00:46
 * @warning
 */
CUrBit::~CUrBit( void )
{
}

/**
 * @brief     Run
 * @param     key_t key
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-02 09:59:56
 * @warning
 */
void CUrBit::Run( key_t key )
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief     메시지 처리를 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-02 09:59:33
 * @warning
 */
void CUrBit::_routine()
{
    LOGENTRY;

    bool bCGIRunning;

    m_pMsg = GetRecvDataMessage();
    m_pLanData = GeLanData();

    while( m_bThreadLoop ) {
        if( QMsgRcv( enTIMER, OS_SEC( 100 ) ) == -1 ) {
            // if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv(CUrBit)" );
        }

        // CGI 실행 플레그 설정
        if( m_pMsg->uiOpCode == ( unsigned int ) enCGI_REQ_IBIT || m_pMsg->uiOpCode == ( unsigned int ) enCGI_REQ_UBIT || m_pMsg->uiOpCode == ( unsigned int ) enCGI_REQ_CBIT || m_pMsg->uiOpCode == ( unsigned int ) enCGI_REQ_SBIT ) {
            bCGIRunning = true;
        }
        else {
            bCGIRunning = false;
        }

        switch( m_pMsg->uiOpCode ) {
            ///////////////////////////////////////////////////////////////////////////////////
            // 운용 제어 관련 메시지 처리
            case enCGI_REQ_IBIT:
            case enTHREAD_REQ_IBIT:
                RunIBit( bCGIRunning );
                break;

            case enCGI_REQ_CBIT:
            case enTHREAD_REQ_CBIT:
                RunCBit( bCGIRunning );
                break;

            case enTHREAD_TIMER:
                Log( enNormal, "주기적으로 자체점검을 수행합니다. !!", m_pLanData->uiUnit );
                RunTimer();
                break;

            case enCGI_REQ_SBIT:
            case enTHREAD_REQ_SBIT:
                RunTimer();
                Log( enNormal, "SRBIT[%d]를 수행합니다 !!", m_pLanData->uiUnit );
                break;

            case enCGI_REQ_UBIT:
            case enTHREAD_REQ_UBIT:
                RunUBit( bCGIRunning );
                break;

            case enTHREAD_REQ_SHUTDOWN:
                Log( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                break;

            default:
                Log( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                break;
        }
    }

}

/**
 * @brief     RunTimer
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-30 12:01:12
 * @warning
 */
void CUrBit::RunTimer()
{
    // 보드 온도를 체크 합니다.
    CheckSBCTemp();


}

/**
 * @brief     CheckSBCTemp
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-30 13:04:20
 * @warning
 */
void CUrBit::CheckSBCTemp()
{
#ifdef __VXWORKS__
    // VXB_ADT7481_TEMP_DRV *pDrvCtrl = ( VXB_ADT7481_TEMP_DRV * ) vxbDevSoftcGet( pAdt7481Inst );

    unsigned int uiBoardTemp, uiCPUTemp;

    GetTemperature( & uiBoardTemp, & uiCPUTemp );

    Log( enNormal, "보드 온도 [%d]도, CPU 온도 [%d]도 체크 합니다." , uiBoardTemp, uiCPUTemp );


#endif
}

/**
 * @brief     Init
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-30 12:01:06
 * @warning
 */
void CUrBit::Init()
{

#ifdef __ZYNQ_BOARD__
    //
    m_theGPIO.OpenChannel( 309 );
#endif

    // DMA 설정
    InitHW();

    //GetBoardID();
    InitIBit();

}

/**
 * @brief     SBC 및 관련 CCA 구성품들을 초기화 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 17:20:55
 * @warning
 */
void CUrBit::InitHW()
{
#ifdef __ZYNQ_BOARD__
    CHWIO::OpenHW();

    //CHWIO::WriteReg( BRAM_CTRL_0, ADC_BIT_SLICE, 0x2 );
    //CHWIO::WriteReg( BRAM_CTRL_0, IQ_SOURCE_SW, 0x0 );
    //CHWIO::WriteReg( BRAM_CTRL_0, ILA_CH_SEL1, 0x1 );
    //CHWIO::WriteReg( BRAM_CTRL_0, DMA_TEST_D_ON, 0x0 );
    //CHWIO::WriteReg( BRAM_CTRL_PPFLT, MON_CH_SEL, 0x0 );
    //CHWIO::WriteReg( BRAM_CTRL_PPFLT, DET_THD_COR, 0x300 );
    //CHWIO::WriteReg( BRAM_CTRL_PPFLT, DET_THD_MAG, 0x300 );
    //CHWIO::WriteReg( BRAM_CTRL_PPFLT, DET_ONLY_COR, 0x0 );
    //CHWIO::WriteReg( BRAM_CTRL_0, DMA_BURST_SIZE, PDW_GATHER_SIZE );

    CHWIO::WriteReg( BRAM_CTRL_0, ADC_BIT_SLICE, 0x2 );
    CHWIO::WriteReg( BRAM_CTRL_0, IQ_SOURCE_SW, 0x0 );
    CHWIO::WriteReg( BRAM_CTRL_0, ILA_CH_SEL1, 0x10 );
    CHWIO::WriteReg( BRAM_CTRL_0, DMA_TEST_D_ON, 0x0 );
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, DF_WAIT_T, 0xA00 ); // 방탐데이터 기다리는 시간 입력
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, MON_CH_SEL, 0x0 );
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, CFAR_nCLR, 0 );
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, CFAR_BEATN, 0x7F00 );
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, CFAR_MODE_ON, 0 );
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, DET_THD_COR, 50 );
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, DET_THD_MAG, 50 );
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, DET_ONLY_COR, 0x0 );
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, PW_AUTO_THD_MIN, 0x0 );
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, PPF_SLICE, 0x2 );
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, PPF_SLICE_FFT, 0x3 );
    CHWIO::WriteReg( BRAM_CTRL_0, DMA_BURST_SIZE, PDW_GATHER_SIZE );

    RunAXIBusBIT();

#endif

    //     {
    //         _TOA sToa;
    //         UZPOCKETPDW s_pdw_reg_t;
    //
    //         s_pdw_reg_t.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H = 0x123B167;
    //         s_pdw_reg_t.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L = 0x3A60;
    //         sToa	= ( (_TOA) s_pdw_reg_t.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H << 16) | s_pdw_reg_t.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L;
    //
    //         printf(">> toa		= %015.3f[ms](0x%llX)(0x%X:0x%X)\n", sToa*PDW_TIME_RES/1000., sToa, s_pdw_reg_t.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H, s_pdw_reg_t.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L  ); //us
    //     }

}

/**
 * @brief     초기 자체 점검을 수행 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 17:22:01
 * @warning
 */
void CUrBit::InitIBit()
{
    //     m_stESIbit.w32 = 0;
    //
    //     LOGMSG( enDebug, _T("Starting the Init-BIT...") );
}

/**
 * @brief     초기 자체점검을 수행합니다.
 * @param     bool bCGIRunning
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 17:22:46
 * @warning
 */
void CUrBit::RunIBit( bool bCGIRunning )
{
    Log( enNormal, "IBIT를 수행합니다 !!" );

    sleep( 1 );

    //     if( bCGIRunning == true ) {
    //         LOGMSG( enDebug, "IBIT 결과는 정상 입니다." );
    // #ifdef __linux__
    //         QMsgSnd( CGI->GetKeyId(), enRES_IBIT, & m_stESIbit, sizeof(m_stESIbit) );
    // #else
    // 		printf( "\n QMsgSnd..." );
    // #endif
    //
    //     }
    //     else {
    // #ifndef _CGI_LIST_
    //         CCommonUtils::SendLan( enRES_IBIT, & m_stESIbit, sizeof(m_stESIbit) );
    // #endif
    //     }
}

/**
 * @brief     연속 자체점검을 수행합니다.
 * @param     bool bCGIRunning
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 17:23:02
 * @warning
 */
void CUrBit::RunCBit( bool bCGIRunning )
{
    Log( enNormal, "CRBIT[%d]를 수행합니다 !!", m_pLanData->uiUnit );
    //     sleep( 2 );
    //
    //     //
    //     memset( & m_stESCbit, 0, sizeof(m_stESCbit) );
    //
    //     if( bCGIRunning == true ) {
    //         LOGMSG( enDebug, "CBIT 결과는 정상 입니다." );
    //     }
    //     else {
    // #ifndef _CGI_LIST_
    //         CCommonUtils::SendLan( enRES_CBIT, & m_stESCbit, sizeof(m_stESCbit) );
    // #endif
    //     }


}

/**
 * @brief     장치 자체점검을 수행합니다.
 * @param     bool bCGIRunning
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 17:23:08
 * @warning
 */
void CUrBit::RunUBit( bool bCGIRunning )
{
    Log( enNormal, "URBIT[%d]를 수행합니다 !!", m_pLanData->uiUnit );
    //
//     sleep( 10 );
//
//     memset( & m_stESCbit, 0, sizeof(m_stESCbit) );
//     if( bCGIRunning == true ) {
//         LOGMSG( enDebug, "UBIT 결과는 정상 입니다." );
//
//     }
//     else {
// #ifndef _CGI_LIST_
//         CCommonUtils::SendLan( enRES_UBIT, & m_stESCbit, sizeof(m_stESCbit) );
// #endif
//     }
}

#ifdef __ZYNQ_BOARD__
/**
 * @brief CUrBit::RunAXIBusBIT
 */
bool CUrBit::RunAXIBusBIT()
{
    bool bRet = true;
    uint32_t temp;

    // 메모리 읽고 쓰기 체크
    if( true == CHWIO::WriteReg( BRAM_CTRL_0, TEST_DATA_WRITE, _AXI_DATATEST_ ) ) {
        temp = CHWIO::ReadReg( BRAM_CTRL_0, TEST_DATA_READ );

        if( temp != _AXI_DATATEST_ ) {
            Log( enError, "Error AXI BUS TEST : 0x%08X", temp );
            bRet = false;
        }
        else {
            LOGMSG( enNormal, "RunAXIBusBIT() is OK...\n" );
        }
    }
    else {
        LOGMSG( enError, "Error of RunAXIBusBIT !!!" );
        bRet = false;
    }

    return bRet;

}
#else


#endif
