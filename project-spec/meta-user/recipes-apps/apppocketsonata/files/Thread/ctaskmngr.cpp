/**

    @file      ctaskmngr.cpp
    @brief     모든 타스크를 관리하는 타스크 입니다.
    @details   ~
    @author    조철희
    @date      9.06.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

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



#ifdef __VXWORKS__
extern bool g_bSNTP;

#endif

#define _DEBUG_

/**
 * @brief CTaskMngr::CTaskMngr
 */
#ifdef _MSSQL_
CTaskMngr::CTaskMngr( int iThreadPriority, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData ), CMSSQL( & m_theMyODBC )
#else
CTaskMngr::CTaskMngr( int iThreadPriority, const char *pClassName, bool bArrayLanData, const char *pFileName ) : CThread( iThreadPriority, pClassName, bArrayLanData )
#endif
{
    //LOGENTRY;

    g_pTheSysConfig->SetBoardID( GetBoardID() );

    SetMode( enNOT_READY_MODE );

    CThread::Init();

#ifdef _SQLITE_
    try {
        m_pDatabase = new Kompex::CSQLiteDatabase( pFileName, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0 );
    }
    catch( Kompex::SQLiteException &sException) {
        //std::cerr << "\nException Occured" << std::endl;
		//sException.Show();
        //std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
        Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );
    }
#elif _MSSQL_
    // MSSQL 연결
    CMSSQL::Init();

#else

#endif

}

/**
 * @brief     ~CTaskMngr
 * @param     void
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-09 09:29:13
 * @warning
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
 * @brief     초기화를 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-09 15:05:01
 * @warning
 */
void CTaskMngr::Init()
{
    //LOGENTRY;

    InitVar();

    //CThread::Init();

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

        if(msgsnd( theThread1.GetKeyId(), (void *)& sndMsg, sizeof(struct STR_MessageData)-sizeof(long), IPC_NOWAIT) <0)
        {
            perror("msg snd error" );
            printf("KeyID[%d]\n", theThread1.GetKeyId() );

        }
        if(msgsnd( theThread2.GetKeyId(), (void *)& sndMsg, sizeof(struct STR_MessageData)-sizeof(long), IPC_NOWAIT) <0)
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
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-07 15:10:17
 * @warning
 */
void CTaskMngr::InitVar()
{
    // 보드 ID를 설정한다.
    g_pTheSysConfig->SetBoardID( GetBoardID() );

    m_enMode = enREADY_MODE;

}

/**
 * @brief     쓰레드를 실행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-07 15:10:27
 * @warning
 */
void CTaskMngr::Run()
{
    //LOGENTRY;

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
    //LOGENTRY;

    SetMode( enREADY_MODE );

    m_pMsg = GetRecvDataMessage();

    while( m_bThreadLoop ) {
#ifdef _MSC_VER
        if( QMsgRcv( enTIMER, OS_MILLISEC( 1000 ) ) == -1 ) {
            perror( "QMsgRcv" );
        }
#else
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv" );
        }

#endif
        else {
            switch( m_pMsg->uiOpCode ) {
#ifdef _MSC_VER
                case enTHREAD_TIMER:
                    break;

#endif

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
                    AnalysisReStart();
                    break;

                // 수집 제어 관련 메시지
                case enREQ_STOP :
                    StopUserCollecting();
                    break;

                ///////////////////////////////////////////////////////////////////////////////////
                //  운용변수 설정
                // 시스템 변수 관련 메시지
                case enREQ_SET_SYS :
                    ReqSetSystemVar();
                    break;

                // 시스템 변수 관련 메시지
                case enREQ_SYS:
                    ReqSystemVar();
                    break;

                case enREQ_SYSERROR:
                    printf( "\n[%d]", m_pMsg->uiOpCode );
                    WhereIs;
                    break;

                ///////////////////////////////////////////////////////////////////////////////////
                // 쓰레드 관련 메시지 처리
                case enTHREAD_DISCONNECTED:
                    Shutdown( true );       // 비정상 종료에 대한 처리
                    break;

                default:
                    Log( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                    break;
            }
        }
//         else {
//             // 아래 메시지는 랜이 끊어진 경우에 에러 메시지를 보여준다.
//                  Log( enError, "메시지 흐름[0x%X]이 잘못 됐습니다. !!", m_pMsg->uiOpCode );
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
    Log( enDebug, "[운용제어/시작 요청]" );

    g_pTheCCUSocket->StopThread();

    g_pTheSignalCollect->QMsgSnd( m_pMsg, GetThreadName() );
#ifdef _MSC_VER
    g_pTheUserCollect->QMsgSnd( enTHREAD_REQ_COLEND, GetThreadName() );
#endif
    TaskSummary();

    g_pTheCCUSocket->SendLan( enRES_OP_START, NULL, 0 );

    g_pTheCCUSocket->CloseSocket();

    //g_pTheCCUSocket->Run( _MSG_CCU_KEY );
    Log( enDebug, "================================================================" );

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
//     Log( enDebug, "Set Mode[%d]", enMode );
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
//             Log( enDebug, "================================================================" );
//             break;
//
//         default :
//             break;
//     }
//
// }

/**
 * @brief     AnalysisReStart
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-25 20:44:53
 * @warning
 */
void CTaskMngr::AnalysisReStart()
{
    AnalysisStart( false );

    BOOL bResult = TRUE;
    g_pTheCCUSocket->SendLan( enRES_OP_RESTART, & bResult, sizeof( bResult ) );

}

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
    char buffer[200];

    TRACE( "\n" );
    sprintf( buffer, "[운용제어/시작 요청]-시작 " );
    CCommonUtils::WallMakePrint( buffer, '#' );
    Log( enNormal, "%s", buffer);

    SetMode( enOP_Mode );

    g_pTheSysConfig->LoadINI();
    g_pTheSysConfig->DisplaySystemVar();

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
    struct timespec time_spec;

    if( m_pMsg->x.tiNow != 0 ) {
        time_spec.tv_sec = m_pMsg->x.tiNow;
        time_spec.tv_nsec = 0;
        clock_settime( CLOCK_REALTIME, &time_spec );
    }
    else {
        if( g_bSNTP == false ) {
            Log( enError, "SBC 시간을 부팅시에 설정하지 못했습니다 ! 네트워크 망을 확인하거나 SNTP 서비스가 서버에 실행되는지를 확인하세요." );
            g_pTheCCUSocket->SendStringLan( enREQ_SYSERROR, (const char *) "SBC 시간을 설정하지 못했습니다 !" );
        }
    }

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
    WhereIs;
    g_pTheEmitterMerge->QMsgSnd( enREQ_OP_START );
    g_pTheSignalCollect->QMsgSnd( enREQ_OP_START );
    g_pTheTrackAnalysis->QMsgSnd( enREQ_OP_START );
    g_pTheScanAnalysis->QMsgSnd( enREQ_OP_START );
    g_pTheDetectAnalysis->QMsgSnd( enREQ_OP_START );
    g_pTheLog->QMsgSnd( enREQ_OP_START );

#ifdef __VXWORKS__
    ChangeTaskPriority( iPriority );

#elif defined(_MSC_VER)
    Sleep( REQ_OP_START_DELAY );

#endif

#ifdef __ZYNQ_BOARD__
    CHWIO::StartCollecting( REG_UIO_DMA_1 );
#endif

    sprintf( buffer, "[운용제어/시작 요청]-종료 " );
    CCommonUtils::WallMakePrint( buffer, '#' );
    Log( enNormal, "%s", buffer );

    if( bOut == true ) {
        BOOL bResult=TRUE;
        g_pTheCCUSocket->SendLan( enRES_OP_START, & bResult, sizeof( bResult ) );
    }

    //g_pTheClockTimer->Start();

}

/**
 * @brief     ZYNC 보드의 ID 값을 리턴한다.
 * @return    ENUM_BoardID
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-09 09:28:53
 * @warning
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
    char buffer[200];

    TRACE( "\n" );
    // 로그 출력
    if( bAbnormalEvent ) {
        sprintf( buffer, "[비정상 처리]-시작 " );
    }
    else {
        sprintf( buffer, "[운용제어/운용 종료]-시작 " );
    }
    CCommonUtils::WallMakePrint( buffer, '#', MAX_SCREEN_COLUMNS );
    Log( enNormal, "%s", buffer );

    SetMode( enREADY_MODE );

#ifdef __ZYNQ_BOARD__
    QMsgSnd( JAMTEC->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
    QMsgSnd( PULTRK->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
#endif

    Log( enDebug, "타스크 우선순위를 낮게 설정합니다." );

    // 모든 쓰레드에세 SHUTDOWN 메시지를 전송한다.
    g_pTheDetectAnalysis->QMsgSnd( enREQ_OP_SHUTDOWN );
    g_pTheTrackAnalysis->QMsgSnd( enREQ_OP_SHUTDOWN );
    g_pTheScanAnalysis->QMsgSnd( enREQ_OP_SHUTDOWN );
    g_pTheEmitterMerge->QMsgSnd( enREQ_OP_SHUTDOWN );
    g_pTheSignalCollect->QMsgSnd( enREQ_OP_SHUTDOWN );

    SetSendDisable();

    // 모든 타스트의 메시지 비우기
    while( g_pTheSignalCollect->QMsgRcvSize() != 0 ) {
        Sleep( REQ_OP_STOP_DELAY );
#ifdef _MSC_VER
        g_pTheSignalCollect->FlushEvent();

#endif
        WhereIs;
    }

    while( g_pTheDetectAnalysis->QMsgRcvSize() != 0 ) {
        Sleep( REQ_OP_STOP_DELAY );
#ifdef _MSC_VER
        g_pTheDetectAnalysis->FlushEvent();

#endif

        WhereIs;
    }

    while( g_pTheTrackAnalysis->QMsgRcvSize() != 0 ) {
        Sleep( REQ_OP_STOP_DELAY );
#ifdef _MSC_VER
        g_pTheTrackAnalysis->FlushEvent();

#endif
        WhereIs;
    }

    while( g_pTheScanAnalysis->QMsgRcvSize() != 0 ) {
        Sleep( REQ_OP_STOP_DELAY );
        WhereIs;
    }

    while( g_pTheEmitterMerge->QMsgRcvSize() != 0 ) {
        Sleep( REQ_OP_STOP_DELAY );
        WhereIs;
    }

    while( g_pTheLog->QMsgRcvSize() != 0 ) {
        Sleep( REQ_OP_STOP_DELAY );
        WhereIs;
    }

    TRACE( "\n\n" );

    Init();

    Log( enDebug, "타스크 우선순위를 높게 설정합니다." );

    Sleep( REQ_OP_STOP_DELAY );

    SetSendEnable();

    if( bAbnormalEvent == false && bOut == true ) {
        unsigned int uiResult = TRUE;
        g_pTheCCUSocket->SendLan( enRES_OP_SHUTDOWN, &uiResult, sizeof( uiResult ) );
    }

    if( bAbnormalEvent ) {
        sprintf( buffer, "[비정상 처리]-종료 " );
    }
    else {
        sprintf( buffer, "[운용제어/운용 종료]-종료 " );
    }
    CCommonUtils::WallMakePrint( buffer, '#', MAX_SCREEN_COLUMNS );
    Log( enNormal, "%s", buffer );

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
    char buffer[200] = { 0 };

    CCommonUtils::WallMakePrint( buffer, '*', MAX_MESSAGE_COLUMNS );
    Log( enNormal, "%s", buffer );

    Log( enNormal, "타스크(쓰레드) 총 개수\t\t: %d [개]" , GetCoThread() );
    for( const auto &cThread : g_vecThread ) {
        //cThread->ShowTaskMessae();
    }

    Log( enNormal, "메시지 큐 총 개수\t\t\t: %d [개]", GetCoMsgQueue() );

    for( const auto &cThread : g_vecThread ) {
        //cThread->ShowQueueMessae();
    }

    //CCommonUtils::WallMakePrint( buffer, '*', MAX_MESSAGE_COLUMNS );
    Log( enNormal, "%s", buffer );

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
        //std::cerr << "\nException Occured" << std::endl;
        //sException.Show();
        //std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
        Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );
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
    Log( enDebug, " 수집 설정을 종료합니다." );

#ifdef __ZYNQ_BOARD__
    CHWIO::StopCollecting( REG_UIO_DMA_1 );
#endif

}

/**
 * @brief     ReqSetSystemVar
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-09 09:21:43
 * @warning
 */
void CTaskMngr::ReqSetSystemVar()
{
    int iRet=0;

    char szDstFilename[100];

    Log( enNormal, "신호분석 운용 변수 설정 요청을 수신했습니다." );

    iRet = TRUE;

#ifdef __VXWORKS__
    sprintf( szDstFilename, "%s/%s/%s", ATADRV, INI_DIRECTORY, INI_FILENAME );

#elif defined(_MSC_VER)
    sprintf( szDstFilename, "%s/%s", CEDEOB_SQLITE_FOLDER, INI_FILENAME );

#else
    sprintf( szDstFilename, "%s/%s", CEDEOB_SQLITE_FOLDER, INI_FILENAME );

#endif

    if( m_theRawFile.RawOpenFile( szDstFilename, O_CREAT | O_RDWR ) ) {
        m_theRawFile.Write( GetRecvData(), m_pMsg->uiArrayLength );
        m_theRawFile.CloseFile();

        iRet = TRUE;
        Log( enDebug, "신호분석 운용 변수 설정 요청 크기[%d]를 [%s]에 정상 기록했습니다." , m_pMsg->uiArrayLength, szDstFilename );
    }
    else {
        Log( enError, "TFFS 드라이브가 잘못됐거나 INI 파일 크기가 잘못 됐습니다. 관리자에게 문의하세요 !" );
    }

    g_pTheSysConfig->LoadINI();
    g_pTheSysConfig->DisplaySystemVar();

    g_pTheCCUSocket->SendLan( enRES_SETSYS, & iRet, sizeof( int ) );

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
    //STR_SYSCONFIG *pstrSysConfig;

    Log( enNormal, "신호분석 운용 변수 요청했습니다." );

    unsigned int uiLength = 0;

    char szSrcFilename[100];
    char *pszData= NULL;

#ifdef __VXWORKS__
    sprintf( szSrcFilename, "%s/%s/%s", ATADRV, INI_DIRECTORY, INI_FILENAME );

#elif defined(_MSC_VER)
    sprintf( szSrcFilename, "%s/%s", CEDEOB_SQLITE_FOLDER, INI_FILENAME );

#else
    sprintf( szSrcFilename, "%s/%s", CEDEOB_SQLITE_FOLDER, INI_FILENAME );

#endif

    if( m_theRawFile.RawOpenFile( szSrcFilename, O_TEXT | O_RDONLY ) ) {
        unsigned long long int ullFileSize;

        ullFileSize = m_theRawFile.GetRawFileSize();

        uiLength = ( unsigned int ) min( ullFileSize, _MAX_LANDATA );

        if( uiLength != 0 ) {
            pszData = ( char * ) malloc( uiLength * sizeof( char ) );
            if( pszData != NULL ) {
                m_theRawFile.Read( pszData, uiLength );
            }
            else {

            }
        }
        else {
            pszData = NULL;
        }

        m_theRawFile.CloseFile();
    }

    if( pszData != NULL ) {
        g_pTheCCUSocket->SendLan( enRES_SYS, pszData, uiLength, false );
        Log( enNormal, "신호분석 운용 변수 내용을 [%d]바이트 전송합니다.", uiLength );
        free( pszData );
    }
    else {
        g_pTheCCUSocket->SendStringLan( enREQ_SYSERROR, (const char *) "INI 파일을 읽지 못했거나 드라이브가 잘못 됐습니다." );

        Log( enError, "INI 파일[%s]이 손상됐거나 존재하지 않습니다. 담당자에게 문의하세요 !" , szSrcFilename );

    }

}

