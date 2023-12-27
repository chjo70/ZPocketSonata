// CTrackAnalysis.cpp: implementation of the CTrackAnalysis class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"


#include "ctrackanalysis.h"
#include "cemittermerge.h"

//#include "../Utils/csingleserver.h"
#include "../Utils/csingleclient.h"
//#include "../Utils/cmultiserver.h"

#include "../Utils/ccommonutils.h"

#include "../Include/globals.h"

#define _DEBUG_


/**
 * @brief CTrackAnalysis::CTrackAnalysis
 * @param iKeyId
 * @param pClassName
 */
CTrackAnalysis::CTrackAnalysis( int iThreadPriority, const char *pThreadName, bool bArrayLanData ) : CThread( iThreadPriority, pThreadName, bArrayLanData )
{

#ifdef _SQLITE_
    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, EMITTER_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
#ifdef _MSC_VER
    char szSrcSQLiteFileName[100];

    sprintf( szSrcSQLiteFileName, "%s_%d.sqlite3", EMITTER_SQLITE_FILENAME, g_enBoardId );
    strcat( szSQLiteFileName, szSrcSQLiteFileName );
#else
    strcat( szSQLiteFileName, EMITTER_SQLITE_FILEEXTNAME );
#endif

    m_pTheKnownSigAnal = new CKnownSigAnal( KWN_COLLECT_PDW, false, szSQLiteFileName, CThread::GetThreadName() );
#else
    m_pTheKnownSigAnal = new CKnownSigAnal( KWN_COLLECT_PDW, false, NULL, GetThreadName() );

#endif

    //m_pTheSysPara = new CSysPara();
    _SAFE_NEW( m_pTheSysPara, CSysPara() )

    InitTrackAnalysis();

}


/**
 * @brief CTrackAnalysis::~CTrackAnalysis
 */
CTrackAnalysis::~CTrackAnalysis(void)
{
    _SAFE_DELETE( m_pTheKnownSigAnal )

    _SAFE_DELETE( m_pTheSysPara )
}


/**
 * @brief CTrackAnalysis::Run
 */
void CTrackAnalysis::Run(key_t key)
{
    //LOGENTRY;

    CThread::Run();

}

/**
 * @brief CTrackAnalysis::_routine
 */
/**
 * @brief     _routine
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 15:46:47
 * @warning
 */
void CTrackAnalysis::_routine()
{
    //LOGENTRY;
    //bool bWhile=true;

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
                case enREQ_OP_START:
                    // QMsgClear();
                    InitTrackAnalysis();
                    break;

                case enTHREAD_DISCONNECTED:
                case enREQ_OP_SHUTDOWN:
                    //QMsgClear();
                    //InitTrackAnalysis();
                    break;

				case enREQ_OP_RESTART:
					//QMsgClear();
					InitTrackAnalysis();
					break;

                case enTHREAD_KNOWNANAL_START :
                    AnalysisStart();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    Log( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                    break;

                default:
                    Log( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                    break;
            }

        }
    }
}

/**
 * @brief     AnalysisStart
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-24, 17:57
 * @warning
 */
void CTrackAnalysis::AnalysisStart()
{
    //LOGENTRY;
    int iCoLOB;

    SRxLOBData *pLOBData;

    STR_TRKSCNPDWDATA *pTrkPDWData;

    // Log( enDebug, " 추적: Analyzing the PDW[%d] in the Ch[%d] for the B[%d]..." , m_pMsg->x.strCollectInfo.uiTotalPDW, m_pMsg->x.strCollectInfo.uiReqStatus, m_pMsg->x.strCollectInfo.uiABTID );
    //CCommonUtils::Disp_FinePDW( ( STR_PDWDATA *) GetRecvData() );

    // 1. 추적 신호 분석을 호출한다.
    pTrkPDWData = ( STR_TRKSCNPDWDATA *) GetRecvData();
    m_pTheKnownSigAnal->Start( & pTrkPDWData->strPDW, & pTrkPDWData->strABTData, m_pRecvTrackAnalInfo->enRobustAnal, m_pRecvTrackAnalInfo->uiGlobalCh );

    // 2. 추적 성공한 LOB 에 대해서 해당 방사체/빔 번호를 할당 합니다. 나머지 LOB들에 대해서는 0 /0 으로 초기화된 LOB 들을 신규 처리하도록 합니다.
    iCoLOB = m_pTheKnownSigAnal->GetCoLOB();

    pLOBData = m_pTheKnownSigAnal->GetLOBData();
    if( pLOBData != NULL ) {
        if( m_pTheKnownSigAnal->IsTrackSuccess() ) {
            pLOBData->uiABTID = m_pRecvTrackAnalInfo->uiABTID;
            pLOBData->uiAETID = m_pRecvTrackAnalInfo->uiAETID;

        }

        //! LOB 개수 설정
        m_pRecvTrackAnalInfo->uiTotalLOB = (unsigned int) iCoLOB;

        // 3.1 추적에서 분석된 LOB 들을 위협 관리로 전송합니다.
        if( iCoLOB > 0 ) {
            // QMsgSnd() 함수에서 Array 버퍼 크기 제한으로 상한값을 설정 함.
            iCoLOB = min( (int) (_MAX_LANDATA / sizeof( struct SRxLOBData) - 1), iCoLOB );

            g_pTheEmitterMerge->QMsgSnd( enTHREAD_KNOWNANAL_START, pLOBData, sizeof( struct SRxLOBData), (unsigned int) iCoLOB, m_pRecvTrackAnalInfo, sizeof( STR_TRKANAL_INFO ), GetThreadName() );
        }
        // 3.2 추적 분석에서 수집이 안되서 분석이 전혀 없거나 수집은 충분히 되었지만 분석이 안 된 경우, 추적 채널을 재할당합니다.
        else {
            m_pstrTrackAnalInfo->Set( m_pRecvTrackAnalInfo->uiGlobalCh, m_pRecvTrackAnalInfo->enPCIDriver, 0, enTrackCollectBank, m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID, enNO_ROBUST_ANALYSIS );
            g_pTheEmitterMerge->QMsgSnd( enTHREAD_KNOWNANAL_FAIL, GetUniMessageData(), sizeof( union UNI_MSG_DATA ), GetThreadName() );

        }
    }
    else {

    }

}

/**
 * @brief     InitTrackAnalysis
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 15:54:42
 * @warning
 */
void CTrackAnalysis::InitTrackAnalysis()
{
    CThread::Clear();

}
