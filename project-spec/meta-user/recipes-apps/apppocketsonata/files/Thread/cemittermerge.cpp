#include "cemittermerge.h"

#include "csignalcollect.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CEmitterMerge* CEmitterMerge::pInstance = nullptr;

CEmitterMerge::CEmitterMerge( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
   LOGENTRY;

    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, getenv("HOME") );
    strcat( szSQLiteFileName, EMITTER_SQLITE_FILENAME );

    //Init();
    m_pTheEmitterMergeMngr = new CELEmitterMergeMngr( false, szSQLiteFileName );

    InitData();

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

    while( g_AnalLoop ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv" );
        }
        else {
            switch( m_pMsg->ucOpCode ) {
                case enTHREAD_DETECTANAL_START :
                    MergeEmitter();
                    break;

                case enTHREAD_KNOWNANAL_START :
                    MergeEmitter();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, " [%s]를 Shutdown 메시지를 처리합니다...", ChildClassName() );
                    bWhile = false;
                    break;

                case enTHREAD_DETECTANAL_END :
                    LOGMSG( enDebug, " 탐지 수집/분석 완료를 수신했습니다." );

                    // 탐지 분석 완료로 이 시그널을 이용하여 위협 사이클 관리를 수행하고...
                    break;

                default:
                    LOGMSG1( enError, " 잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->ucOpCode );
                    break;
            }
        }
    }
}


/**
 * @brief CEmitterMerge::InitData
 */
void CEmitterMerge::InitData()
{
    m_sLOBOtherInfo.bUpdate = false;
}

/**
 * @brief CEmitterMerge::MergeEmitter
 */
void CEmitterMerge::MergeEmitter()
{
    LOGENTRY;

    int i;
    bool bMerge, bTrkLOB=false;

    STR_ANALINFO strAnalInfo;
    SRxLOBHeader strLOBHeader;

    SRxLOBData *pLOBData;

    LOGMSG4( enDebug, " [%d] 대역, [%d/%d] 채널/빔 번호 에서 [%d] 개의 위협 관리를 수행합니다." , m_pMsg->x.strAnalInfo.uiBand, m_pMsg->x.strAnalInfo.uiCh, m_pMsg->x.strAnalInfo.uiABTID, m_pMsg->x.strAnalInfo.uiTotalLOB );

    memcpy( & strAnalInfo, & m_pMsg->x.strAnalInfo, sizeof(STR_ANALINFO) );

    // 위협 관리 초기화
    m_pTheEmitterMergeMngr->Start();

    // 1. LOB 데이터를 갖고온다.
    PopLanData( m_uniLanData.szFile, m_pMsg->iArrayIndex, m_pMsg->uiArrayLength );

    // 2. 위협 관리를 호출한다.
    strLOBHeader.iNumOfLOB = m_pMsg->x.strAnalInfo.uiTotalLOB;
    pLOBData = ( SRxLOBData *) m_uniLanData.szFile;
    for( i=0 ; i < strLOBHeader.iNumOfLOB ; ++i ) {

        // 2.1 분석된 LOB 데이터를 병합 관리한다.
        bMerge = m_pTheEmitterMergeMngr->ManageThreat( & strLOBHeader, pLOBData, & m_sLOBOtherInfo );

        // 2.2 병합 관리된 빔 및 AET 정보를 처리한다.
        strAnalInfo.uiBand = 0;
        strAnalInfo.uiCh = ( bMerge == true ? m_pMsg->x.strAnalInfo.uiCh : _spZero );
        strAnalInfo.uiTotalLOB = _spOne;
        strAnalInfo.uiAETID = m_pTheEmitterMergeMngr->GetAETID();
        strAnalInfo.uiABTID = m_pTheEmitterMergeMngr->GetABTID();
        SIGCOL->QMsgSnd( enTHREAD_REQ_SETWINDOWCELL, m_pTheEmitterMergeMngr->GetABTData(), sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );

        if( strAnalInfo.uiABTID == m_pMsg->x.strAnalInfo.uiABTID && m_pMsg->x.strAnalInfo.uiABTID != 0 ) {
            bTrkLOB = true;
        }

        ++ pLOBData;
    }

    // 3. 추적 채널 경우에는 재시도 또는 추적 채널을 닫는다.
    ENUM_COLLECTBANK enCollectBank;
    enCollectBank = SIGCOL->GetEnumCollectBank( m_pMsg->x.strAnalInfo.uiCh );

    if( enCollectBank == enTrackCollectBank && bTrkLOB == false ) {
        strAnalInfo.uiBand = 0;
        strAnalInfo.uiCh = m_pMsg->x.strAnalInfo.uiCh;
        strAnalInfo.uiTotalLOB = _spOne;
        strAnalInfo.uiAETID = m_pMsg->x.strAnalInfo.uiAETID;
        strAnalInfo.uiABTID = m_pMsg->x.strAnalInfo.uiABTID;

        SRxABTData *pABTData = m_pTheEmitterMergeMngr->GetABTData(strAnalInfo.uiAETID, strAnalInfo.uiABTID);

        SIGCOL->QMsgSnd( enTHREAD_REQ_SETWINDOWCELL, pABTData, sizeof(SRxABTData), & strAnalInfo, sizeof(STR_ANALINFO) );
    }

}
