// CTrackAnalysis.cpp: implementation of the CTrackAnalysis class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"


#include "ctrackanalysis.h"
#include "cemittermerge.h"

#include "../Utils/csingleserver.h"
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
CTrackAnalysis::CTrackAnalysis( int iKeyId, const char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{

#ifdef _SQLITE_
    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, EMITTER_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
    strcat( szSQLiteFileName, EMITTER_SQLITE_FILENAME );

    m_pTheKnownSigAnal = new CKnownSigAnal( KWN_COLLECT_PDW, false, szSQLiteFileName );
#else
    m_pTheKnownSigAnal = new CKnownSigAnal( KWN_COLLECT_PDW, false );

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
    LOGENTRY;

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
    LOGENTRY;
    bool bWhile=true;

    m_pMsg = GetDataMessage();

    while( g_AnalLoop ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv" );
        }
        else {
            switch( m_pMsg->uiOpCode ) {
                case enREQ_OP_START:
                    // QMsgClear();
                    InitTrackAnalysis();
                    break;

                case enTHREAD_DISCONNECTED:
                case enREQ_OP_SHUTDOWN:
                    QMsgClear();
                    InitTrackAnalysis();
                    break;

				case enREQ_OP_RESTART:
					QMsgClear();
					InitTrackAnalysis();
					break;

                case enTHREAD_KNOWNANAL_START :
                    AnalysisStart();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                    bWhile = false;
                    break;

                default:
                    LOGMSG2( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                    break;
            }

            SendEchoMessage();
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
    LOGENTRY;
    int iCoLOB;

    STR_TRKSCNPDWDATA *pTrkPDWData;

    LOGMSG3( enDebug, " TRK: Analyzing the PDW[%d] in the Ch[%d] for the B[%d]..." , m_pMsg->x.strCollectInfo.uiTotalPDW, m_pMsg->x.strCollectInfo.uiCh, m_pMsg->x.strCollectInfo.uiABTID );

    //CCommonUtils::Disp_FinePDW( ( STR_PDWDATA *) GetRecvData() );

    // 1. 추적 신호 분석을 호출한다.
    pTrkPDWData = ( STR_TRKSCNPDWDATA *) GetRecvData();
    m_pTheKnownSigAnal->Start( & pTrkPDWData->strPDW, & pTrkPDWData->strABTData );

    // 2. 분석 결과를 병합/식별 쓰레드에 전달한다.
    STR_ANALINFO strAnalInfo;

    iCoLOB = m_pTheKnownSigAnal->GetCoLOB();

    // QMsgSnd() 함수에서 Array 버퍼 크기 제한으로 상한값을 설정 함.
    iCoLOB = min( (int) (_MAX_LANDATA / sizeof(SRxLOBData) - 1), iCoLOB);

    strAnalInfo.enBoardID = g_enBoardId;
    strAnalInfo.uiTotalLOB = (unsigned int)iCoLOB;
    strAnalInfo.uiCh = m_pMsg->x.strCollectInfo.uiCh;
    strAnalInfo.uiAETID = m_pMsg->x.strAnalInfo.uiAETID;
    strAnalInfo.uiABTID = m_pMsg->x.strCollectInfo.uiABTID;

    // PDW 헤더 정보 저장
    memcpy(&strAnalInfo.uniPDWHeader, &pTrkPDWData->strPDW.x, sizeof(UNION_HEADER));

    SRxLOBData *pLOBData = m_pTheKnownSigAnal->GetLOBData();

    g_pTheEmitterMerge->QMsgSnd( enTHREAD_KNOWNANAL_START, m_pTheKnownSigAnal->GetLOBData(), sizeof(SRxLOBData), (unsigned int) iCoLOB, & strAnalInfo, sizeof(STR_ANALINFO), GetThreadName() );

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


}