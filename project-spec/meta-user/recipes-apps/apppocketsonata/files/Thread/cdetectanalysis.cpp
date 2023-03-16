/**

    @file      cdetectanalysis.cpp
    @brief     탐지 신호 분석 쓰레드
    @details   ~
    @author    조철희
    @date      15.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "stdafx.h"

#include "stdafx.h"


#include "cdetectanalysis.h"
#include "cemittermerge.h"
#include "csignalcollect.h"

#include "../Utils/csingleserver.h"

#include "../Utils/ccommonutils.h"

#include "../Include/globals.h"

#define _DEBUG_

/**
 * @brief     객체를 생성 합니다.
 * @param     int iKeyId
 * @param     const char * pClassName
 * @param     bool bArrayLanData
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-15 10:46:11
 * @warning
 */
CDetectAnalysis::CDetectAnalysis( int iKeyId, const char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
#ifdef _SQLITE_
    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, EMITTER_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
    strcat( szSQLiteFileName, EMITTER_SQLITE_FILENAME );

    m_pTheNewSigAnal = new CNewSigAnal( NEW_COLLECT_PDW, false, szSQLiteFileName );
#else
    m_pTheNewSigAnal = new CNewSigAnal( KWN_COLLECT_PDW, false );

#endif

    m_pTheSysPara = NULL;
    _SAFE_NEW( m_pTheSysPara, CSysPara )

    m_PDWData.pstPDW = NULL;
    m_PDWData.pstPDW = new _PDW [sizeof(_PDW) * MAX_PDW];

    InitDetectAnalysis();

}

/**
 * @brief     ~CDetectAnalysis
 * @param     void
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-15 10:54:48
 * @warning
 */
CDetectAnalysis::~CDetectAnalysis(void)
{
	_SAFE_DELETE( m_pTheNewSigAnal )

	_SAFE_DELETE( m_pTheSysPara )

    _SAFE_DELETE( m_PDWData.pstPDW )
}

/**
 * @brief     쓰레드를 호출 합니다.
 * @param     key_t key
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-15 10:54:54
 * @warning
 */
void CDetectAnalysis::Run(key_t key)
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief     메시지를 수신하여 명령을 처리 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-15 10:55:10
 * @warning
 */
void CDetectAnalysis::_routine()
{
    LOGENTRY;

    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( m_bThreadLoop ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv" );
        }
        else {
            switch( m_pMsg->uiOpCode ) {
                // 운용 제어 관련 메시지
                case enREQ_OP_START:
                    // QMsgClear();
                    InitDetectAnalysis();
                    break;

                case enTHREAD_DISCONNECTED:
                case enREQ_OP_SHUTDOWN:
                    QMsgClear();
                    InitDetectAnalysis();
                    break;

                case enREQ_OP_RESTART:
                    QMsgClear();
                    InitDetectAnalysis();
                    break;

                // 위협 정보 관련 메시지
                case enTHREAD_DETECTANAL_START :
                    MakePDWData();
                    AnalysisStart();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                    break;

                case enTHREAD_REQ_SET_TRACKWINDOWCELL :
                    LOGMSG( enDebug, "윈도우 셀을 설정합니다." );
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
 * @brief     객체를 초기화 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 15:45:45
 * @warning
 */
void CDetectAnalysis::InitDetectAnalysis()
{

}

/**
 * @brief     입력 PDW 데이터로 신호 분석을 수행합니다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-08, 14:25
 * @warning
 */
void CDetectAnalysis::AnalysisStart()
{
    LOGENTRY;

    LOGMSG2( enDebug, " 탐지 : %d[Ch]에서, PDW[%d] 를 수집했습니다." , m_pMsg->x.strCollectInfo.uiCh, m_pMsg->x.strCollectInfo.uiTotalPDW );

    //CCommonUtils::Disp_FinePDW( ( STR_PDWDATA *) GetRecvData() );

    // 1. 탐지 신호 분석을 호출한다.
    m_pTheNewSigAnal->Start( & m_PDWData );
    //SIGCOL->QMsgSnd( enTHREAD_DETECTANAL_END );

    // 3. 분석 결과를 병합/식별 쓰레드에 전달한다.
    unsigned int uiTotalLOB=(unsigned int) m_pTheNewSigAnal->GetCoLOB();

    if( uiTotalLOB >= _spOne ) {
        STR_ANALINFO strAnalInfo;
        //STR_COLLECTINFO strCollectInfo;

        memset( & strAnalInfo, 0, sizeof(STR_ANALINFO) );

        // QMsgSnd() 함수에서 Array 버퍼 크기 제한으로 상한값을 설정 함.
        uiTotalLOB = min( ( _MAX_LANDATA / sizeof(SRxLOBData)-1), uiTotalLOB);

        strAnalInfo.enBoardID = g_enBoardId;
        strAnalInfo.uiTotalLOB = uiTotalLOB;
        strAnalInfo.uiCh = m_pMsg->x.strCollectInfo.uiCh;

        // PDW 헤더 정보 저장
        memcpy(&strAnalInfo.uniPDWHeader, & m_PDWData.x, sizeof(UNION_HEADER) );

        g_pTheEmitterMerge->QMsgSnd( enTHREAD_DETECTANAL_START, NO_ECHO, m_pTheNewSigAnal->GetLOBData(), sizeof(SRxLOBData), uiTotalLOB, & strAnalInfo, sizeof(STR_ANALINFO), GetThreadName() );

        //memcpy( &strCollectInfo, &m_pMsg->x.strCollectInfo, sizeof( STR_COLLECTINFO ) );
        g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_DETECTWINDOWCELL, &m_pMsg->x.strCollectInfo, sizeof( STR_COLLECTINFO ) );

    }

}

/**
 * @brief     신호 분석하기 위해 PDW 데이터를 파싱하여 분석에 용이하도록 변환합니다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-03, 14:51
 * @warning
 */
void CDetectAnalysis::MakePDWData()
{
    unsigned int i, uiTotalPDW;

    STR_STATIC_PDWDATA *pStaticPDWData;

    _PDW *pPDWSrc, *pPDWDest;

    pStaticPDWData = ( STR_STATIC_PDWDATA * ) GetRecvData();

    // 헤더 복사
    memcpy( & m_PDWData.x, & pStaticPDWData->x, sizeof(UNION_HEADER) );

    // 데이터 복사
    pPDWSrc = & pStaticPDWData->stPDW[0];
    pPDWDest = & m_PDWData.pstPDW[0];
    uiTotalPDW = pStaticPDWData->GetTotalPDW();
    for( i=0 ; i < uiTotalPDW ; ++i ) {
        pPDWDest->ullTOA = pPDWSrc->ullTOA;

        pPDWDest->iPulseType = pPDWSrc->iPulseType;

        pPDWDest->uiAOA = pPDWSrc->uiAOA;
        pPDWDest->uiFreq = pPDWSrc->uiFreq;
        pPDWDest->uiPA = pPDWSrc->uiPA;
        pPDWDest->uiPW = pPDWSrc->uiPW;

        pPDWDest->iPFTag = pPDWSrc->iPFTag;

        memcpy( &pPDWDest->x, &pPDWSrc->x, sizeof( UNI_PDW_ETC ) );

// #if defined(_ELINT_)
//         pPDWDest->fPh1 = pPDWSrc->fPh1;
//         pPDWDest->fPh2 = pPDWSrc->fPh2;
//         pPDWDest->fPh3 = pPDWSrc->fPh3;
//         pPDWDest->fPh4 = pPDWSrc->fPh4;
//
// #elif defined(_XBAND_)
//         pPDWDest->fPh1 = pPDWSrc->fPh1;
//         pPDWDest->fPh2 = pPDWSrc->fPh2;
//         pPDWDest->fPh3 = pPDWSrc->fPh3;
//         pPDWDest->fPh4 = pPDWSrc->fPh4;
//         pPDWDest->fPh5 = pPDWSrc->fPh5;
//
// #elif _POCKETSONATA_
//         pPDWDest->iPMOP = pPDWSrc->iPMOP;
//         pPDWDest->iFMOP = pPDWSrc->iFMOP;
//         pPDWDest->iChannel = pPDWSrc->iChannel;
//
// #endif

        ++ pPDWSrc;
        ++ pPDWDest;
    }

}