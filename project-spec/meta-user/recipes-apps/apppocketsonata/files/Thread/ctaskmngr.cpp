// CTaskMngr.cpp: implementation of the CTaskMngr class.
//
//////////////////////////////////////////////////////////////////////

/*
 * 모든 타스크를 관리해 주는 입니다.
 * */

#include "stdafx.h"

#include <signal.h>
#include <cassert>
#include <stdlib.h>

#include "ctaskmngr.h"

#ifdef __ZYNQ_BOARD__

#endif


#include "csignalcollect.h"
#include "cdetectanalysis.h"
#include "ctrackanalysis.h"
#include "cscananalysis.h"
#include "cemittermerge.h"
#include "cusercollect.h"

#include "curbit.h"


#include "../System/csysconfig.h"

#include "../Utils/csingleclient.h"
#include "../Utils/ccommonutils.h"

#include "../Include/globals.h"



#define _DEBUG_

/**
 * @brief CTaskMngr::CTaskMngr
 */
#ifdef _MSSQL_
CTaskMngr::CTaskMngr( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData ), CMSSQL( & m_theMyODBC )
#else
CTaskMngr::CTaskMngr( int iKeyId, const char *pClassName, bool bArrayLanData, const char *pFileName ) : CThread( iKeyId, pClassName, bArrayLanData )
#endif
{
    LOGENTRY;

    Init();

#ifdef _SQLITE_
    try {
        m_pDatabase = new Kompex::CSQLiteDatabase( pFileName, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0 );
    }
    catch( Kompex::SQLiteException &sException) {
        std::cerr << "\nException Occured" << std::endl;
		sException.Show();
        std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
    }
#elif _MSSQL_
    // MSSQL 연결
    CMSSQL::Init();

#else

#endif

}

/**
 * @brief CTaskMngr::~CTaskMngr
 */
CTaskMngr::~CTaskMngr(void)
{

    //GP_SYSCFG->SetMode( enMode );
    //CreateAllAnalysisThread( false );

#ifdef _SQLITE_
    delete m_pDatabase;

#elif _MSSQL_
    m_theMyODBC.Close();


#else

#endif

}

/**
 * @brief 초기화를 수행합니다.
 */
void CTaskMngr::Init()
{
    LOGENTRY;

    InitVar();

    CThread::Init();

    //STR_MessageData sndMsg;

    //CThread theThread1(10), theThread2(11);

    /*

    theThread1.Run( thread_routine );
    theThread2.Run( thread_routine );

    sndMsg.mtype = 1;
    sndMsg.x.opCode = 0x1234;

    int i=0;

    printf("\ntid:%lx\n",pthread_self());
    while( true ){
        printf("main:%d\n",i);
        i++;
        sleep(1);

        if(msgsnd( theThread1.GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) <0)
        {
            perror("msg snd error" );
            printf("KeyID[%d]\n", theThread1.GetKeyId() );

        }
        if(msgsnd( theThread2.GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) <0)
        {
            perror("msg snd error" );
            printf("KeyID[%d]\n", theThread2.GetKeyId() );
        }

        //theThread1.Pend();
        //theThread1.Stop();

    }

    */

}

/**
 * @brief 변수를 초기화 한다.
 */
void CTaskMngr::InitVar()
{
    // 보드 ID를 설정한다.
    g_pTheSysConfig->SetBoardID( GetBoardID() );

    m_enMode = enREADY_MODE;

}

/**
 * @brief CMain::Run
 */
void CTaskMngr::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief     _routine
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-23 15:38:06
 * @warning
 */
void CTaskMngr::_routine()
{
    LOGENTRY;

    m_pMsg = GetRecvDataMessage();

    while( m_bThreadLoop ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv() 에러");
        }
        else {
            //if( IsValidLanData( m_pMsg ) == true ) {
            switch( m_pMsg->uiOpCode ) {
                ///////////////////////////////////////////////////////////////////////////////////
                // 운용 제어 관련 메시지 처리
                case enREQ_OP_START:
                    AnalysisStart();
                    break;

                case enREQ_OP_SHUTDOWN:
                    Shutdown();
                    break;

                case enREQ_OP_RESTART:
                    Shutdown( false, false );
                    AnalysisStart( false );
                    break;

                // 수집 제어 관련 메시지
                case enREQ_STOP :
                    StopUserCollecting();
                    break;

                // 시스템 변수 관련 메시지
                case enREQ_SYS :
                    ReqSystemVar();
                    break;

                case enSYSERROR :
                    printf( "****************************************************************" );
                    break;

                ///////////////////////////////////////////////////////////////////////////////////
                // 쓰레드 관련 메시지 처리
                case enTHREAD_DISCONNECTED:
                    Shutdown( true );       // 비정상 종료에 대한 처리
                    break;

                default:
                    LOGMSG2( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                    break;
            }
        }
//         else {
//             // 아래 메시지는 랜이 끊어진 경우에 에러 메시지를 보여준다.
//                  LOGMSG1( enError, "메시지 흐름[0x%X]이 잘못 됐습니다. !!", m_pMsg->uiOpCode );
//             }
//         }
    }

}

/**
 * @brief     시작 요청에 대한 처리를 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-02 14:41:27
 * @warning
 */
void CTaskMngr::Start()
{
    LOGMSG( enDebug, "[운용제어/시작 요청]" );

    g_pTheCCUSocket->StopThread();

    g_pTheSignalCollect->QMsgSnd( m_pMsg, GetThreadName() );
#ifdef _MSC_VER
    g_pTheUserCollect->QMsgSnd( enTHREAD_REQ_COLEND, GetThreadName() );
#endif
    TaskSummary();

    CCommonUtils::SendLan( enRES_OP_START );

    CCommonUtils::CloseSocket();

    //g_pTheCCUSocket->Run( _MSG_CCU_KEY );
    LOGMSG( enDebug, "================================================================" );

}

/**
 * @brief       모드 명령을 처리한다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/22 15:52:21
 * @warning
 */
// void CTaskMngr::SetMode()
// {
//     ENUM_MODE enMode, enMode2;
//
//     _EQUALS3( enMode2, enMode, (ENUM_MODE) m_pMsg->x.uiData )
//
//     LOGMSG1( enDebug, "Set Mode[%d]", enMode );
//
//     g_pTheSysConfig->SetMode( enMode );
//
//     switch( enMode ) {
//         case enES_MODE :
//         case enEW_MODE :
//             CCommonUtils::SendLan( enRES_MODE, & enMode, sizeof(int) );
//             break;
//
//         case enREADY_MODE :
//             //g_pTheCCUSocket->StopThread();
//
//             g_pTheSignalCollect->QMsgSnd( m_pMsg, GetThreadName() );
// #ifdef _MSC_VER
//             g_pTheUserCollect->QMsgSnd( enTHREAD_REQ_COLEND, GetThreadName() );
// #endif
//             ProcessSummary();
//
//             CCommonUtils::SendLan( enRES_MODE, & enMode, sizeof(int) );
//
//             CCommonUtils::CloseSocket();
//
//             //g_pTheCCUSocket->Run( _MSG_CCU_KEY );
//             LOGMSG( enDebug, "================================================================" );
//             break;
//
//         default :
//             break;
//     }
//
// }

/**
 * @brief     분석 시작 명령을 처리한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-09 10:07:30
 * @warning
 */
void CTaskMngr::AnalysisStart( bool bOut )
{
    LOGMSG( enDebug, "[운용제어/시작 요청]-시작====================================" );

    SetMode( enOP_Mode );

	g_pTheSysConfig->IncOpInitID();

    // g_pTheSysConfig->SetMode( m_enMode );

#ifdef _MSC_VER
	// 수집 시작
    // g_pTheUserCollect->QMsgSnd( enTHREAD_REQ_COLSTART, GetThreadName() );
#endif

    // 분석 관련 쓰레드를 삭제한다.
    // CreateAllAnalysisThread();

    // 시간 정보로 설정한 후에 시작 명령을 처리한다.
#ifdef _MSC_VER

#elif defined(__VXWORKS__)
    // time_t tiNow = (time_t) m_pMsg->x.tiNow;

    struct timespec time_spec;

    time_spec.tv_sec = m_pMsg->x.tiNow;
    clock_settime( CLOCK_REALTIME, &time_spec );

#elif defined(__linux__)
    // tiNow = (time_t) m_pMsg->x.tiNow;

    // 환경 변수로 타겟 보드일때만 아래 함수를 수행한다.
    stime( & m_pMsg->x.tiNow );

#else

#endif

    // 프로세스 상태를 전시한다.
    TaskSummary();

#ifdef __VXWORKS__
    int iPriority = GetPriority();
    ChangeTaskPriority( TASK_LOWEST_PRIORITY );

#endif

    // 신호 수집 시작
    SendThreadMessage( g_pTheDetectAnalysis );
    SendThreadMessage( g_pTheTrackAnalysis );
    SendThreadMessage( g_pTheScanAnalysis );
    SendThreadMessage( g_pTheEmitterMerge );
    SendThreadMessage( g_pTheSignalCollect );

#ifdef __VXWORKS__
    ChangeTaskPriority( iPriority );

#elif defined(_MFC_VER)
    Sleep( REQ_OP_START_DELAY );

#endif

#ifdef __ZYNQ_BOARD__
    CHWIO::StartCollecting( REG_UIO_DMA_1 );
#endif

    if( bOut == true ) {
        BOOL bResult=true;
        g_pTheCCUSocket->SendLan( enRES_OP_START, & bResult, sizeof( bResult ) );
    }

    LOGMSG( enDebug, "[운용제어/시작 요청]-종료==================================" );

}

/**
 * @brief ZYNC 보드의 ID 값을 리턴한다.
 */
ENUM_BoardID CTaskMngr::GetBoardID()
{
    ENUM_BoardID enBoardID=enMaster;

#ifdef _AUTO_ID_

    STR_CONFIG_VAR g_strConfigVar;

#else

    if( g_enBoardId == enPRC_Unknown ) {
        char *pEnv=getenv( "DESKTOP_SESSION" );

        if( pEnv != NULL ) {
            if( strcmp( pEnv, "ubuntu" ) == 0 ) {
                enBoardID = enMaster;
            }
            else {
                enBoardID = enPRC1;
            }
        }
        else {
            enBoardID = enPRC1;
        }
    }
    else {
        enBoardID = g_enBoardId;
    }

    return enBoardID;

#endif

}

/**
 * @brief     분석 종료 처리를 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 12:57:42
 * @warning
 */
void CTaskMngr::Shutdown( bool bAbnormalEvent, bool bOut )
{
    // 로그 출력
    if( bAbnormalEvent ) {
        LOGMSG( enDebug, "[비정상 처리]-시작====================================================" );
    }
    else {
        LOGMSG( enDebug, "[운용제어/운용 종료]-시작===============================================" );
    }

    SetMode( enREADY_MODE );

#ifdef __ZYNQ_BOARD__
    QMsgSnd( JAMTEC->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
    QMsgSnd( PULTRK->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
#endif

#ifdef __VXWORKS__
    TRACE( "\n 타스크 우선순위를 낮게 설정합니다." );
#endif

    // 모든 쓰레드에세 SHUTDOWN 메시지를 전송한다.
    SendThreadMessage( g_pTheSignalCollect );
    SendThreadMessage( g_pTheDetectAnalysis );
    SendThreadMessage( g_pTheTrackAnalysis );
    SendThreadMessage( g_pTheScanAnalysis );
    SendThreadMessage( g_pTheEmitterMerge );

    SetSendDisable();

    while( g_pTheSignalCollect->QMsgRcvSize() != 0 ) {
        Sleep( REQ_OP_STOP_DELAY );
    }

    while( g_pTheDetectAnalysis->QMsgRcvSize() != 0 ) {
        Sleep( REQ_OP_STOP_DELAY );
    }

    while( g_pTheTrackAnalysis->QMsgRcvSize() != 0 ) {
        Sleep( REQ_OP_STOP_DELAY );
    }

    while( g_pTheScanAnalysis->QMsgRcvSize() != 0 ) {
        Sleep( REQ_OP_STOP_DELAY );
    }

    while( g_pTheEmitterMerge->QMsgRcvSize() != 0 ) {
        Sleep( REQ_OP_STOP_DELAY );
    }

    Init();
    g_pTheSignalCollect->Init();
    g_pTheDetectAnalysis->Init();
    g_pTheTrackAnalysis->Init();
    g_pTheScanAnalysis->Init();
    g_pTheEmitterMerge->Init();

    //TRACE( "\n 타스크 우선순위를 높게 설정합니다." );
    Sleep( REQ_OP_STOP_DELAY );

    SetSendEnable();

    if( bAbnormalEvent == false && bOut == true ) {
        BOOL bResult = TRUE;
        g_pTheCCUSocket->SendLan( enRES_OP_SHUTDOWN, &bResult, sizeof( bResult ) );
    }

    if( bAbnormalEvent ) {
        LOGMSG( enDebug, "[비정상 처리]-종료=======================================================" );
    }
    else {
        LOGMSG( enDebug, "[운용제어/운용 종료]-종료================================================" );
    }

}

/**
 * @brief     시스템의 자원과 운용 소프트웨어 상에서 자원 정보를 출력한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 11:54:29
 * @warning
 */
void CTaskMngr::TaskSummary()
{
    LOGMSG( enNormal, "--------------------------------------------------------" );

    LOGMSG1( enNormal, "타스크(쓰레드) 총 개수\t\t: %d [개]" , GetCoThread() );
    for( const auto &cThread : g_vecThread ) {
        cThread->ShowTaskMessae();
    }

    LOGMSG1( enNormal, "메시지 큐 총 개수\t\t : %d [개]", GetCoMsgQueue() );

    for( const auto &cThread : g_vecThread ) {
        cThread->ShowQueueMessae();
    }

    LOGMSG( enNormal, "--------------------------------------------------------" );

}

/**
 * @brief     ELNOT 정보 존재 여부를 리턴한다.
 * @param     char * pszELNOT
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-23 10:31:52
 * @warning
 */
int CTaskMngr::IsThrereELNOT( char *pszELNOT )
{
    int iRadarIndex=-1;

#ifdef _SQLITE_
    try {
        Kompex::SQLiteStatement stmt(m_pDatabase);

        sprintf( m_szSQLString, "SELECT RADAR_INDEX FROM RADAR WHERE ELNOT='%s'", pszELNOT);
        mbstowcs( m_szSQLString16, m_szSQLString, sizeof(m_szSQLString16) );
        //swprintf(m_szSQLString16, MAX_SQL_SIZE, L"SELECT RADAR_INDEX FROM RADAR WHERE ELNOT='%s'", pszELNOT);
        stmt.SqlStatement(m_szSQLString16);

        if (stmt.FetchRow()) {
            iRadarIndex = stmt.GetColumnInt(0);
        }

        // do not forget to clean-up
        stmt.FreeQuery();

    }
    catch (Kompex::SQLiteException &sException) {
        std::cerr << "\nException Occured" << std::endl;
        sException.Show();
        std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
    }

#elif _MSSQL_


#endif

    return iRadarIndex;
}

/**
 * @brief CTaskMngr::StopUserCollecting
 */
void CTaskMngr::StopUserCollecting()
{
    LOGMSG( enDebug, " 수집 설정을 종료합니다." );

#ifdef __ZYNQ_BOARD__
    CHWIO::StopCollecting( REG_UIO_DMA_1 );
#endif

}

/**
 * @brief		시스템 변수 정보를 회신합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/23 19:55:29
 * @warning
 */
void CTaskMngr::ReqSystemVar()
{
    STR_SYSCONFIG *pstrSysConfig;

    pstrSysConfig = g_pTheSysConfig->GetSysConfig();
    CCommonUtils::SendLan( enRES_SETSYS, pstrSysConfig, sizeof(STR_SYSCONFIG) );
}

