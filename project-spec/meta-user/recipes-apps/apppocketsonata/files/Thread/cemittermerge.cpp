#include "cemittermerge.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CEmitterMerge* CEmitterMerge::pInstance = nullptr;

CEmitterMerge::CEmitterMerge( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
   LOGENTRY;

   //Init();
   m_pTheEmitterMergeMngr = new CELEmitterMergeMngr( true, EMITTER_SQLITE_FILENAME );

}

/**
 * @brief CEmitterMerge::~CEmitterMerge
 */
CEmitterMerge::~CEmitterMerge()
{
    delete m_pTheEmitterMergeMngr;
}

/**
 * @brief CEmitterMerge::Run
 */
void CEmitterMerge::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CEmitterMerge::_routine
 */
void CEmitterMerge::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }

        switch( m_pMsg->ucOpCode ) {
        case enTHREAD_ANAL_START :
            MergeEmitter();
            break;

        case enTHREAD_REQ_SHUTDOWN :
            LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );
            bWhile = false;
            break;

        case enTHREAD_REQ_SETWINDOWCELL :
            LOGMSG( enDebug, "윈도우 셀을 설정합니다." );
            break;

        default:
            LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->ucOpCode );
            break;
    }
}
}

/**
 * @brief CEmitterMerge::MergeEmitter
 */
void CEmitterMerge::MergeEmitter()
{
    LOGENTRY;

    LOGMSG2( enDebug, "%d 대역에서 LOB : %d 개의 위협 관리를 수행합니다." , m_pMsg->x.strAnalInfo.uiBand, m_pMsg->x.strAnalInfo.uiTotalLOB );

    // 1. LOB 데이터를 갖고온다.
    PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );

    // 2. 위협 관리를 호출한다.
    //m_pTheEmitterMergeMngr->ManageThreat();
    //m_pTheNewSigAnal->Start( ( STR_PDWDATA *) m_uniLanData.szFile );

}
