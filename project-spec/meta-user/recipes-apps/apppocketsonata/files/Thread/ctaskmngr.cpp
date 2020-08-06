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

#include "curbit.h"
#include "cprompt.h"
#include "creclan.h"

#include "../Utils/clog.h"
#include "../System/csysconfig.h"

#include "../Utils/ccommonutils.h"



#define _DEBUG_




// 클래스 내의 정적 멤버변수 값 정의
CTaskMngr* CTaskMngr::pInstance = nullptr;

/**
 * @brief CTaskMngr::CTaskMngr
 */
CTaskMngr::CTaskMngr( int iKeyId, char *pClassName ) : CThread( iKeyId, pClassName )
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
* @brief CTaskMngr::ReleaseInstance
*/
void CTaskMngr::ReleaseInstance()
{
   if(pInstance)
   {
       LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );

       delete pInstance;
       pInstance = NULL;
   }
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
void CTaskMngr::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CMain::_routine
 */
void CTaskMngr::_routine()
{
    LOGENTRY;
    //UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    //pLanData = ( UNI_LAN_DATA * ) & m_pMsg->msg[0];

    while( true ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv() 에러");
        }

        switch( m_pMsg->ucOpCode ) {
            case enTHREAD_MODE :
                SetMode();
                break;

            case enTHREAD_ANAL_START :
                AnalysisStart();
                break;

            case enTHREAD_REQ_SHUTDOWN :
                Shutdown();
                break;

            default:
                LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->ucOpCode );
                break;
        }
    }

}

/**
 * @brief 모드 명령을 처리한다.
 */
void CTaskMngr::SetMode()
{
    ENUM_MODE enMode;

    enMode = (ENUM_MODE) m_pMsg->szMessage[0];

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
    CreateAllAnalysisThread( true );

    // 시간 정보로 설정한 후에 시작 명령을
    tiNow = (time_t) m_pMsg->szMessage[0];

    SIGCOL->QMsgSnd( m_pMsg );

}

/**
 * @brief 분석 관련 쓰레드를 생성하거나 삭제 한다.
 * @param bCreate
 */
void CTaskMngr::CreateAllAnalysisThread( bool bCreate )
{
    LOGMSG1( enDebug, "분석 관련 쓰레드를 삭제하고 재구동하여 분석을 준비한다[%d].", bCreate );

    // 1. 먼저 관련 분석 쓰레드를 삭제한다.
    SIGCOL->ReleaseInstance();
    DETANL->ReleaseInstance();
    TRKANL->ReleaseInstance();
    SCANANL->ReleaseInstance();

    // 플레그에 따라서 생성한다.
    if( bCreate == true ) {
        SIGCOL->Run();
        DETANL->Run();
        TRKANL->Run();
        SCANANL->Run();
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

    //QMsgSnd( JAMTEC->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
    //QMsgSnd( PULTRK->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
    //QMsgSnd( SIGCOL->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
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
