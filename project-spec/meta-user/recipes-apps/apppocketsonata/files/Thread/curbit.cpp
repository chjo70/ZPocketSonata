/*****************************************************************************************

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
#include <sntpcLib.h>
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

#include "../BootSHell/ManSbc.h"

extern CManSbc *g_theManSbc;
extern vector<CThread *> g_vecThread;

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
    //LOGENTRY;

    m_stBIT.bTemp = true;
    m_stBIT.bTask = true;

    m_uiCoURBITTimer = 0;

#ifdef _MSC_VER
    m_strSQLiteFileName = string_format( "%s/%s_%d.sqlite3", EMITTER_SQLITE_FOLDER, EMITTER_SQLITE_FILENAME, g_enBoardId );
#else
    m_strSQLiteFileName = string_format( "%s/%s", EMITTER_SQLITE_FOLDER, EMITTER_SQLITE_FILEEXTNAME );

#endif

    m_strSQLiteFolder = string_format( "%s", SD_CARD );
    //printf( "\n m_strSQLiteFolder=[%s]", m_strSQLiteFolder.c_str() );

    // DMA 설정
    InitHW();

    //GetBoardID();
    InitIBit();

    Init();

    m_enLogType = enNormal;

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
    StopThread();
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
    //LOGENTRY;

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
    //LOGENTRY;

    bool bCGIRunning;

    m_pMsg = GetRecvDataMessage();
    m_pLanData = GeLanData();

    while( m_bThreadLoop ) {
        if( QMsgRcv( enTIMER, OS_SEC( URBIT_TIMER )) == -1 ) {
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
            case enREQ_OP_START :
                Init();
                break;

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
                RunTimer();
                break;

            case enCGI_REQ_SBIT:
            case enTHREAD_REQ_SBIT:
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
    if( g_pTheTaskMngr != NULL && g_pTheTaskMngr->GetMode() == enOP_Mode ) {
        m_enLogType = enNormal;
    }
    else {
        m_enLogType = enNull;
    }

    Log( m_enLogType, "EW신호처리판#%d에서 주기적으로 자체점검을 수행합니다. !!", (int) g_enBoardId );

    ++ m_uiCoURBITTimer;
    if( m_uiCoURBITTimer >= SNTP_TIMER / URBIT_TIMER ) {
        m_uiCoURBITTimer = 0;

        // 시간을 동기화 합니다.
        SyncSNMP();

// #ifdef __VXWORKS__
//         WhereIs;
//         m_stBIT.bSNMP = g_theManSbc->SetTimeBySNMP();
//
// #endif

    }

    // 보드 온도를 체크 합니다.
    CheckSBCTemp();

    // 타스크(프로세스) 상태를 체크 합니다.
    CheckTasks();

    // 데이터베이스를 관리 합니다.
    CheckDatabase();

    // 외부 인터페이스를 체크 합니다.
    CheckLinkStatus();

    // 저장 데이터를 서버에 백업 합니다.
    BackupStorage();

    // 로그 형식 복귀
    m_enLogType = enNormal;

}

/**
 * @brief     SyncSNMP
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-25 12:25:14
 * @warning
 */
void CUrBit::SyncSNMP()
{
#ifdef _MSC_VER

#else
    STATUS sntpc_status = -1;
    struct timespec tspec;

    // 이놈의 vxworks 7은 왜 2번을 수행해야 얻어 오는지....
    if( g_pTheSysConfig->GetDevelop() == 1 ) {
        Log( m_enLogType, "n##### SNTP 프로토콜을 사용해서 타임 서버[%s]로 SBC 현재 시간을 설정하려 합니다...", g_pTheSysConfig->GetDebugServerOfNetwork() );

        sntpc_status = sntpcTimeGet( g_pTheSysConfig->GetDebugServerOfNetwork(), 3 * OS_ONE_SEC, & tspec );
    }
    else {
        Log( m_enLogType, "##### SNTP 프로토콜을 사용해서 타임 서버[%s]로 SBC 현재 시간을 설정하려 합니다...", g_pTheSysConfig->GetCCUServerOfNetwork() );

        sntpc_status = sntpcTimeGet( g_pTheSysConfig->GetCCUServerOfNetwork(), 3 * OS_ONE_SEC, & tspec );

//         if( sntpc_status != OK ) {
//             Log( m_enLogType, "##### SNTP 프로토콜을 사용해서 타임 서버[%s]로 SBC 현재 시간을 설정하려 합니다...", g_pTheSysConfig->GetDebugServerOfNetwork() );
//
//             sntpc_status = sntpcTimeGet( g_pTheSysConfig->GetDebugServerOfNetwork(), 3 * OS_ONE_SEC, & tspec );
//         }
    }


    if( sntpc_status == OK ) {
        STATUS settime_status;

        settime_status = clock_settime( CLOCK_REALTIME, & tspec );
        if( settime_status != OK ) {
            Log( enError, "Returned settime_status: %i errno: %s", settime_status, strerror( errno ) );
        }
        else {
            struct tm *pstTime;
            char buffer[100];

            time_t ti = time( NULL );

            pstTime = localtime( & ti );
            strftime( buffer, 100, "%Y-%m-%d %H:%M:%S", pstTime );

            Log( m_enLogType, "시간 동기화[%s]에 성공 했습니다 !" , buffer );
        }
    }
    else {
        Log( enError, "시간 동기화에 실패 했습니다 !" );
    }

#endif

}

/**
 * @brief     CheckDatabase
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-28 10:34:06
 * @warning
 */
void CUrBit::CheckDatabase()
{
    unsigned long long int ullFileSize, ullFreeSpace;

    ullFileSize = CCommonUtils::GetRawFileSize( m_strSQLiteFileName.c_str() );
    ullFreeSpace = CCommonUtils::DiskFreeSpace( m_strSQLiteFolder.c_str() );

    Log( enNormal, "램 드라이브 저장 공간{%llu[KB]}, SQLite 파일 크기{%llu[KB]}", ullFreeSpace/1024, ullFileSize/1024 );

    if( ullFreeSpace < MINIMUM_FREESPACE_OF_RAMDRIVE ) {
        // g_pTheEmitterMerge->QMsgSnd( enTHREAD_REQ_CLEANUP );

    }

}

/**
 * @brief     CheckLinkStatus
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-18 11:25:42
 * @warning
 */
void CUrBit::CheckLinkStatus()
{
    if( g_pTheCCUSocket->IsConnected() == true ) {
        Log( enNormal, "랜 연결 상태 : [%s]와 정상 연결됐습니다.", g_pTheCCUSocket->GetConnectedAddress() );
    }
    else {
        Log( enNormal, "랜 연결 상태 : 연결된 상태가 아닙니다." );
    }
}

/**
 * @brief     CheckTasks
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-19 13:13:18
 * @warning
 */
void CUrBit::CheckTasks()
{

    m_stBIT.bTask = true;

    for( const auto &cThread : g_vecThread ) {
#ifdef __VXWORKS__
        TASK_DESC taskDesc;

        cThread->GetTaskInfo( &taskDesc );

        // printf( "\n [%s] task status[%d] ", cThread->GetThreadName(), taskDesc.td_status );
        if( taskDesc.td_status == 16 ) {
            m_stBIT.bTask = false;
            Log( enError, "타스크[%s]에서 이상 운용됩니다. 관리자에게 문의하세요 !", cThread->GetThreadName() );

            SendStringLan( enREQ_SYSERROR, ( const char * ) "EW신호처리판 [#%d]에서 타스크[%s]에서 이상 동작합니다. 확인하세요 !", ( int ) g_enBoardId, cThread->GetThreadName() );

            break;
        }
#endif

    }

#ifdef __VXWORKS__
    if( m_stBIT.bTask == true ) {
        Log( enNormal, "[%d] 개의 타스크가 정상 운용 중입니다." , g_vecThread.size() );
    }
    else {

    }
#endif

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

    if( uiBoardTemp > g_pTheSysConfig->GetCPUTempWarning() ) {
        SendStringLan( enREQ_SYSERROR, ( const char * ) "EW신호처리판 [#%d]에서 보드 온도[%d]도, CPU 온도[%d]도 를 초과했습니다 ! 장치 전원을 차단하세요 !", ( int ) g_enBoardId, uiBoardTemp, uiCPUTemp );

        Log( enError, "%s", "EW신호처리판 [#%d]에서 보드 온도[%d]도, CPU 온도[%d]도 를 초과했습니다 ! 장치 전원을 차단하세요 !", ( int ) g_enBoardId, uiBoardTemp, uiCPUTemp );

        m_stBIT.bTemp = false;
    }
    else {
        Log( enNormal, "보드 온도 [%d]도, CPU 온도 [%d]도 로 정상 운용 입니다.", uiBoardTemp, uiCPUTemp );
    }

#else
    m_stBIT.bTemp = true;

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

/**
 * @brief     BackupStorage
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-27 14:25:04
 * @warning
 */
void CUrBit::BackupStorage()
{
    int iCopy;
    string strSrcFileName, strDestFilename;
    char buffer[100];

    if( g_pTheTaskMngr != NULL ) {
        time_t ti = g_pTheTaskMngr->OPStartTime();

        if( ti != 0 ) {
            // 목적지 디렉토리 생성
            CCommonUtils::getFileNamingDesignatedTime( buffer, sizeof( buffer ), ti );

            strSrcFileName = string_format( "%s%s/%s/%s", RAMDRV, RAMDRV_NO, SQLITE_DIRECTORY, EMITTER_SQLITE_FILEEXTNAME );
            strDestFilename = string_format( "%s/BRD_%d/%s/#%d_%s_%s", SHARED_DATA_DIRECTORY, g_enBoardId, SQLITE_DIRECTORY, ( int ) g_enBoardId, buffer, EMITTER_SQLITE_FILEEXTNAME );

            printf( "\n %s...%s", strSrcFileName.c_str(), strDestFilename.c_str() );
            iCopy = CCommonUtils::CopySrcToDstFile( strSrcFileName.c_str(), strDestFilename.c_str(), 1, 0077 );
            if( iCopy <= 0 ) {
                Log( enError, "소스[%s]에서 타겟[%s]으로 복사하지 못했습니다 ! 담당자에게 문의하세요 !" , strSrcFileName.c_str(), strDestFilename.c_str() );
            }
            else {
                Log( enNormal, "소스[%s]에서 타겟[%s]으로 정상적으로 복사했습니다.", strSrcFileName.c_str(), strDestFilename.c_str() );
            }
        }
        else {
            // printf( "\n 시간 정보가 ZERO 입니다. 시간 설정이 되지 않았습니다. !", buffer );
        }
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
