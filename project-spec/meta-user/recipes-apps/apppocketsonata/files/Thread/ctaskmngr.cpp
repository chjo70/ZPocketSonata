/*
 * 모든 타스크를 관리해 주는 입니다.
 * */

#include <signal.h>
#include <cassert>

#include "ctaskmngr.h"
#include "cjamtech.h"
#include "cpulsetrk.h"
#include "csignalcollect.h"
#include "cdetectanalysis.h"
#include "ctrackanalysis.h"
#include "cscananalysis.h"
#include "cemittermerge.h"

#include "curbit.h"
#include "cprompt.h"
#include "creclan.h"

#include "../Utils/clog.h"
#include "../System/csysconfig.h"

#include "../Utils/ccommonutils.h"



#define _DEBUG_




// 클래스 내의 정적 멤버변수 값 정의
CTaskMngr* CTaskMngr::m_pInstance = nullptr;

/**
 * @brief CTaskMngr::CTaskMngr
 */
CTaskMngr::CTaskMngr( int iKeyId, char *pClassName, bool bArrayLanData, const char *pFileName ) : CThread( iKeyId, pClassName, bArrayLanData ), Database( pFileName, SQLite::OPEN_READWRITE )
{
    LOGENTRY;

    Init();

}

/**
 * @brief CTaskMngr::~CTaskMngr
 */
CTaskMngr::~CTaskMngr(void)
{
    // 객체를 소멸하게 한다.
    GP_SYSCFG->ReleaseInstance();
}

/**
 * @brief 초기화를 수행합니다.
 */
void CTaskMngr::Init()
{
    LOGENTRY;

    InitVar();

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
    GP_SYSCFG->SetBoardID( GetBoardID() );

}

/**
 * @brief CMain::Run
 */
void CTaskMngr::Run( key_t key )
{
    LOGENTRY;

    CThread::Run( key );

}

/**
 * @brief CMain::_routine
 */
void CTaskMngr::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    //UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    //pLanData = ( UNI_LAN_DATA * ) & m_pMsg->msg[0];

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv() 에러");
        }
        else {
        if( CCommonUtils::IsValidLanData( m_pMsg ) == true ) {
            switch( m_pMsg->uiOpCode ) {
                case enTHREAD_MODE :
                    SetMode();
                    break;

                case enTHREAD_DETECTANAL_START :
                    AnalysisStart();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    Shutdown();
                    bWhile = false;
                    break;

                case enTHREAD_REQ_IPLVERSION :
                    ReqIPLVersion();
                    break;

                case enREQ_IPL_START :
                case enREQ_IPL_DOWNLOAD :
                case enREQ_IPL_END :
                    IPLDownload();
                    break;

                default:
                    LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
                    break;
            }
        }
        else {
            // 아래 메시지는 랜이 끊어진 경우에 에러 메시지를 보여준다.
            //LOGMSG1( enError, "메시지 흐름[0x%X]이 잘못 됐습니다. !!", m_pMsg->ucOpCode );
            }
        }
    }

}

/**
 * @brief 모드 명령을 처리한다.
 */
void CTaskMngr::SetMode()
{
    ENUM_MODE enMode;

    enMode = (ENUM_MODE) m_pMsg->x.szData[0];

    LOGMSG1( enDebug, "모드(%d)를 설정합니다.", enMode );

    switch( enMode ) {
        case enES_MODE :
            break;
        case enEW_MODE :
            break;
        case enREADY_MODE :
            CreateAllAnalysisThread( false );
            ProcessSummary();
            break;

        default :
            break;
    }

    GP_SYSCFG->SetMode( enMode );

    CCommonUtils::SendLan( enRES_MODE, & enMode, sizeof(int) );

}

/**
 * @brief 분석 시작 명령을 처리한다.
 */
void CTaskMngr::AnalysisStart()
{
    time_t tiNow;

    // 분석 관련 쓰레드를 삭제한다.
    CreateAllAnalysisThread();

    GP_SYSCFG->SetMode( enANAL_Mode );

    // 시간 정보로 설정한 후에 시작 명령을 처리한다.
    tiNow = (time_t) m_pMsg->x.szData[0];
    // 환경 변수로 타겟 보드일때만 아래 함수를 수행한다.
    //stime( & tiNow );

    SIGCOL->QMsgSnd( m_pMsg );

}

/**
 * @brief 분석 관련 쓰레드를 생성하거나 삭제 한다.
 * @param bCreate
 */
void CTaskMngr::CreateAllAnalysisThread( bool bCreate )
{

    if( bCreate == true ) {
        LOGMSG1( enDebug, "분석 관련 쓰레드를 구동하여 분석을 준비한다[%d].", bCreate );

        g_AnalLoop = true;

        EMTMRG->Run();
        SIGCOL->Run();
        DETANL->Run();
        TRKANL->Run();
        SCANANL->Run();

    }
    else {
        LOGMSG1( enDebug, "분석 관련 쓰레드를 삭제한다[%d].", bCreate );

        g_AnalLoop = false;

        // 1. 먼저 관련 분석 쓰레드를 삭제한다.
        EMTMRG_RELEASE;
        SIGCOL_RELEASE;
        DETANL_RELEASE;
        TRKANL_RELEASE;
        SCANANL_RELEASE;


    }

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

        if( strcmp( pEnv, "ubuntu" ) == 0 ) {
            enBoardID = enMaster;
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
 * @brief CTaskMngr::Shutdown
 */
void CTaskMngr::Shutdown()
{
    // 모든 쓰레드에세 SHUTDOWN 메시지를 전송한다.


    //sleep( 1 );

    // 쓰레드 객체를 소멸한다.
    //JAMTEC->ReleaseInstance();
    //PULTRK->ReleaseInstance();
    //SIGCOL->ReleaseInstance();
    //URBIT->ReleaseInstance();
    //PROMPT->ReleaseInstance();
    //RECLAN->ReleaseInstance();

    //ReleaseInstance();

    QMsgSnd( JAMTEC->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
    QMsgSnd( URBIT->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
    QMsgSnd( PULTRK->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
    QMsgSnd( SIGCOL->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
    QMsgSnd( RECCCU->GetKeyId(), enTHREAD_REQ_SHUTDOWN );

    g_Loop = false;

}

/**
 * @brief 시스템의 자원과 운용 소프트웨어 상에서 자원 정보를 출력한다.
 */
void CTaskMngr::ProcessSummary()
{
    LOGMSG( enDebug, "--------------------------------------------------------" );
    LOGMSG2( enDebug, "  총 타스크 개수 : %d\t   총 메시지 큐 개수 : %d" , GetCoThread(), GetCoThread() );
    LOGMSG( enDebug, "--------------------------------------------------------" );
}

/**
 * @brief CTaskMngr::IPLVersion
 */
void CTaskMngr::ReqIPLVersion()
{
    STR_IPL_VERSION strIPLVersion;

    strIPLVersion.uiIPLVersion = (m_theIPL.getIPLStart())->uiIPLVersion;
    strIPLVersion.uiStatus = strIPLVersion.uiIPLVersion != _spZero ? _spPass : _spFail;
    CCommonUtils::SendLan( esIPL_VERSION, & strIPLVersion, sizeof(strIPLVersion) );
}

/**
 * @brief CTaskMngr::IPLDownload
 */
void CTaskMngr::IPLDownload()
{
    int iWriteStatus;
    UNI_LAN_DATA *pLanData;

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    switch( m_pMsg->uiOpCode ) {
        case enREQ_IPL_START :
            m_theIPL.setIPLStart( & pLanData->strIPLStart );
            DeleteIPL();
            break;

        case enREQ_IPL_DOWNLOAD :
            m_theIPL.setIPL( (STR_IPL *) GetArrayMsgData(m_pMsg->iArrayIndex) );
            InsertIPL( m_iTotalIPL );
            ++ m_iTotalIPL;

            CCommonUtils::SendLan( esIPL_WRITESTATUS, & iWriteStatus, sizeof(int) );
            break;

        case enREQ_IPL_END :
            if( EMTMRG_IS ) { EMTMRG->QMsgSnd( m_pMsg ); }
            break;

        default :
            break;

    }
}

/**
 * @brief CTaskMngr::DeleteIPL
 */
void CTaskMngr::DeleteIPL()
{

    // 레이더
    sprintf( m_szSQLString, "DELETE FROM RADAR" );
    exec( m_szSQLString );

    // 레이더 모드
    sprintf( m_szSQLString, "DELETE FROM RADAR_MODE" );
    exec( m_szSQLString );

    // 레이더 & 레이더 모드 관계
    sprintf( m_szSQLString, "DELETE FROM RADAR_MODELIFECYCLE" );
    //exec( m_szSQLString );

    m_iTotalIPL = 0;

}

/**
 * @brief CTaskMngr::InsertIPL
 */
void CTaskMngr::InsertIPL( int iIndex )
{
    STR_IPL *pstrIPL;
    char szDate[100];

    pstrIPL = m_theIPL.getIPL( iIndex );

    // 레이더
    sprintf( m_szSQLString, "INSERT INTO RADAR ( RADAR_INDEX, ELNOT, NICKNAME, FUNCTION_CODE, PRIORITY ) VALUES \
                             ( %d, '%s', 'NICK%d', 'ZZ', %d )" , \
                             pstrIPL->noIPL, pstrIPL->elintNot, pstrIPL->noIPL, pstrIPL->thrLev );
    exec( m_szSQLString );

    // 레이더 모드
    getStringPresentTime( szDate );
    sprintf( m_szSQLString, "INSERT INTO RADAR_MODE ( RADAR_MODE_INDEX, FUNCTION_CODE, SIGNAL_TYPE, \
DATE_CREATED, \
RF_TYPICAL_MIN, RF_TYPICAL_MAX, RF_NUM_POSITIONS, RF_PATTERN_PERIOD_MIN, RF_PATTERN_PERIOD_MAX, \
PRI_TYPICAL_MIN, PRI_TYPICAL_MAX, PRI_NUM_POSITIONS, PRI_PATTERN_PERIOD_MIN, PRI_PATTERN_PERIOD_MAX, \
PRIORITY, RF_TYPE, PRI_TYPE ) VALUES \
( %d, 'ZZ', '%s', \
'%s', \
%d, %d, %d, %d, %d, \
%d, %d, %d, %d, %d, \
%d, 1, 1 )" , \
    pstrIPL->noIPL, ipl_signal_type[pstrIPL->sigType], \
    szDate, \
    pstrIPL->frq.low, pstrIPL->frq.hgh, pstrIPL->frq.swtLev, pstrIPL->frq.ppLow, pstrIPL->frq.ppHgh, \
    pstrIPL->pri.low, pstrIPL->pri.hgh, pstrIPL->pri.swtLev, pstrIPL->pri.ppLow, pstrIPL->pri.ppHgh, \
    pstrIPL->thrLev, pstrIPL->frq.type, pstrIPL->pri.type );

    exec( m_szSQLString );

}

