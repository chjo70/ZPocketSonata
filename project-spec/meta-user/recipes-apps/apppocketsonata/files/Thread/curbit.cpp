/*
 * 자체점검 Process : 자체점검을 처리하는 쓰레드 입니다.
 *
 * */


#include "stdafx.h"



#include "curbit.h"
#include "../Utils/clog.h"

#include "../Utils/chwio.h"
//#include "../Test/hw_interface.h"
#include "../Utils/ccommonutils.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CUrBit* CUrBit::m_pInstance = nullptr;

/**
 * @brief CUrBit::CUrBit
 * @param iKeyId
 * @param pClassName
 * @param bArrayLanData
 */
CUrBit::CUrBit( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
    LOGENTRY;

    Init();

}

/**
 * @brief CUrBit::~CUrBit
 */
CUrBit::~CUrBit(void)
{
}



/**
 * @brief CUrBit::Run
 */
void CUrBit::Run( key_t key )
{
    LOGENTRY;

    CThread::Run( key );

}

/**
 * @brief CUrBit::_routine
 */
void CUrBit::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    bool bCGIRunning;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            //perror( "error ");
            break;
        }

        // CGI 실행 플레그 설정
        if( m_pMsg->uiOpCode == enCGI_REQ_IBIT || m_pMsg->uiOpCode == enCGI_REQ_UBIT || m_pMsg->uiOpCode == enCGI_REQ_CBIT || m_pMsg->uiOpCode == enCGI_REQ_SBIT ) {
            bCGIRunning = true;
        }
        else {
            bCGIRunning = false;
        }

        switch( m_pMsg->uiOpCode ) {
            case enCGI_REQ_IBIT :
            case enTHREAD_REQ_IBIT :
                LOGMSG1( enNormal, "IBIT[%d]를 수행합니다 !!" , pLanData->uiUnit );
                RunIBit( bCGIRunning );
                break;

            case enCGI_REQ_CBIT :
            case enTHREAD_REQ_CBIT :
                LOGMSG1( enNormal, "CRBIT[%d]를 수행합니다 !!" , pLanData->uiUnit );
                RunCBit( bCGIRunning );
                break;

            case enCGI_REQ_SBIT :
            case enTHREAD_REQ_SBIT :
                LOGMSG1( enNormal, "SRBIT[%d]를 수행합니다 !!" , pLanData->uiUnit );
                break;

            case enCGI_REQ_UBIT :
            case enTHREAD_REQ_UBIT :            
                LOGMSG1( enNormal, "URBIT[%d]를 수행합니다 !!" , pLanData->uiUnit );
                RunCBit( bCGIRunning );
                break;

            case enTHREAD_REQ_SHUTDOWN :
                LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", ChildClassName() );
                bWhile = false;
                break;

            default:
                LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
                break;
        }
    }

}

/**
 * @brief CUrBit::Init
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
 * @brief CUrBit::InitHW
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
    CHWIO::WriteReg( BRAM_CTRL_0, DMA_TEST_D_ON,0x0 );
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
    CHWIO::WriteReg( BRAM_CTRL_PPFLT, PPF_SLICE_FFT,0x3 );
    CHWIO::WriteReg( BRAM_CTRL_0,DMA_BURST_SIZE,PDW_GATHER_SIZE);

    RunAXIBusBIT();

#endif

    {
        _TOA sToa;
        UZPOCKETPDW s_pdw_reg_t;

        s_pdw_reg_t.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H = 0x123B167;
        s_pdw_reg_t.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L = 0x3A60;
        sToa	= ( (_TOA) s_pdw_reg_t.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H << 16) | s_pdw_reg_t.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L;

        printf(">> toa		= %015.3f[ms](0x%llX)(0x%X:0x%X)\n", sToa*PDW_TIME_RES/1000., sToa, s_pdw_reg_t.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H, s_pdw_reg_t.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L  ); //us
    }

}

/**
 * @brief CUrBit::InitIBit
 */
void CUrBit::InitIBit()
{
    m_stESIbit.w32 = 0;

    LOGMSG( enDebug, _T("IBIT를 시작 합니다....") );
}

/**
 * @brief CUrBit::RunIBit
 */
void CUrBit::RunIBit( bool bCGIRunning )
{
    LOGMSG( enDebug, "비트 결과는 입니다." );
    sleep( 1 );

    if( bCGIRunning == true ) {
        printf( "IBIT 결과는 정상 입니다." );
        QMsgSnd( _MSG_CGI_KEY, enRES_IBIT, & m_stESIbit, sizeof(m_stESIbit) );
    }
    else {
#ifndef _CGI_LIST_
        CCommonUtils::SendLan( enRES_IBIT, & m_stESIbit, sizeof(m_stESIbit) );
#endif
    }
}

/**
 * @brief CUrBit::RunCBit
 */
void CUrBit::RunCBit( bool bCGIRunning )
{
    LOGMSG( enDebug, "비트 결과는 입니다." );

    //
    memset( & m_stESCbit, 0, sizeof(m_stESCbit) );
    sleep( 2 );


    if( bCGIRunning == true ) {
        printf( "CBIT 결과는 정상 입니다." );
    }
    else {
#ifndef _CGI_LIST_
        CCommonUtils::SendLan( enRES_CBIT, & m_stESCbit, sizeof(m_stESCbit) );
#endif
    }
}

/**
 * @brief CUrBit::RunUBit
 * @param bCGIRunning
 */
void CUrBit::RunUBit( bool bCGIRunning )
{
    //
    memset( & m_stESCbit, 0, sizeof(m_stESCbit) );
    sleep( 10 );

    LOGMSG( enDebug, "비트 결과는 입니다." );

    if( bCGIRunning == true ) {

    }
    else {
#ifndef _CGI_LIST_
        CCommonUtils::SendLan( enRES_UBIT, & m_stESCbit, sizeof(m_stESCbit) );
#endif
    }
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
            LOGMSG1( enError, "Error AXI BUS TEST : 0x%08X", temp );
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
