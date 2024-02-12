/**

    @file      cdetectanalysis.cpp
    @brief     탐지 신호 분석 쓰레드
    @details   ~
    @author    조철희
    @date      15.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "stdafx.h"

#include "cdetectanalysis.h"
#include "cemittermerge.h"
#include "csignalcollect.h"

//#include "../Utils/csingleserver.h"

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
CDetectAnalysis::CDetectAnalysis( int iThreadPriority, const char *pThreadName, bool bArrayLanData ) : CThread( iThreadPriority, pThreadName, bArrayLanData )
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

    m_pTheNewSigAnal = new CNewSigAnal( NEW_COLLECT_PDW, false, szSQLiteFileName, CThread::GetThreadName() );
#else
    m_pTheNewSigAnal = new CNewSigAnal( NEW_COLLECT_PDW, false, NULL, GetThreadName() );

#endif

    m_pTheSysPara = NULL;
    _SAFE_NEW( m_pTheSysPara, CSysPara )

    m_PDWData.pstPDW = NULL;
    m_PDWData.pstPDW = new _PDW [sizeof( _PDW ) * MAX_PDW];

    m_pMsg = NULL;

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
    StopThread();

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
    //LOGENTRY;

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
    //LOGENTRY;

    m_pMsg = GetRecvDataMessage();

#if 0

    while( true ) {
        STR_PDWDATA stPDWDATA;
        unsigned int iPLOBID = 0;

        stPDWDATA.SetTotalPDW( 100 );
        m_pTheNewSigAnal->InsertToDB_RAW( & stPDWDATA, iPLOBID );
        TRACE( "\n CDetectAnalysis" );

        g_pTheSysConfig->IncOpInitID();

        ++ iPLOBID;
    }

#endif

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
            if( m_pMsg != NULL ) {
                switch( m_pMsg->uiOpCode ) {
#ifdef _MSC_VER
                    case enTHREAD_TIMER:
                        break;

#endif
                    // 운용 제어 관련 메시지
                    case enREQ_OP_START:
                        // QMsgClear();
                        InitDetectAnalysis();
                        break;

                    case enTHREAD_DISCONNECTED:
                    case enREQ_OP_SHUTDOWN:
                        //QMsgClear();
                        //InitDetectAnalysis();
                        break;

                    case enREQ_OP_RESTART:
                        //QMsgClear();
                        InitDetectAnalysis();
                        break;

                    ///////////////////////////////////////////////////////////////////////////////////
                    // 위협 정보 관련 메시지
                    case enTHREAD_DETECTANAL_START :
                        MakePDWData();
                        AnalysisStart();
                        break;

                    case enTHREAD_REQ_SHUTDOWN :
                        Log( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                        break;

                    case enTHREAD_REQ_SET_TRACKWINDOWCELL :
                        Log( enDebug, "윈도우 셀을 설정합니다." );
                        break;

                    default:
                        Log( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                        break;
                }
            }

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
    if( m_pMsg != NULL ) {
        m_pTheNewSigAnal->MakeDirectory( m_pMsg->x.tiNow, enDetectCollectBank );
    }

    CThread::Clear();

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
    //LOGENTRY;

    //Log( enDebug, "탐지 : 채널[%2d]에서, PDW[%d] 를 수집했습니다." , m_pMsg->x.strCollectInfo.uiReqStatus, m_pMsg->x.strCollectInfo.uiTotalPDW );

    // 1. 탐지 신호 분석을 호출한다.
    m_pTheNewSigAnal->Start( & m_PDWData, true );

    // 3. 분석 결과를 병합/식별 쓰레드에 전달한다.
    unsigned int uiTotalLOB=(unsigned int) m_pTheNewSigAnal->GetCoLOB();

#if 0
    SRxLOBData stLOBData[5];

    uiTotalLOB = 2;
    SRxLOBData *pLOBData = stLOBData;

    memset( pLOBData, 0, sizeof( SRxLOBData ) * uiTotalLOB );
    pLOBData->vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    pLOBData->fFreqMax = 9449.;
    pLOBData->fFreqMin = 9000.;
    pLOBData->fFreqMean = 9106.;

    pLOBData->vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    pLOBData->fPRIMax = 703.;
    pLOBData->fPRIMin = 297.;
    pLOBData->fPRIMean = 500.;
    pLOBData->vPRIPositionCount = 6;
    pLOBData->fPRISeq[0] = 296.9;
    pLOBData->fPRISeq[1] = 703.1;
    pLOBData->fPRISeq[2] = 296.9;
    pLOBData->fPRISeq[3] = 703.1;
    pLOBData->fPRISeq[4] = 296.9;
    pLOBData->fPRISeq[5] = 703.1;

    ++ pLOBData;

    pLOBData->vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    pLOBData->fFreqMax = 9449;
    pLOBData->fFreqMin = 9250;
    pLOBData->fFreqMean = 9347;

    pLOBData->vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    pLOBData->fPRIMax = 500.;
    pLOBData->fPRIMin = 500.;
    pLOBData->fPRIMean = 500.;


#endif

    if( uiTotalLOB >= _spOne ) {
        //! LOB 크기는 내부 메시지 크기로 개수를 정합니다.
        //? #주의 : 메시지 크기 제한, QMsgSnd() 함수에서 Array 버퍼 크기 제한으로 상한값을 설정 해야 함.
        uiTotalLOB = min( MAX_LOB, uiTotalLOB);

        GetDetectAnalInfo()->Set( m_pMsg->x.strCollectInfo.enPCIDriver, uiTotalLOB, m_pMsg->x.strCollectInfo.uiReqStatus[0], m_pMsg->x.strCollectInfo.enCollectBank, 0, 0, 0 );

#if 0
        //! #디버깅 : 시험 신호(40번)에 대해서 Jitter 로 보고 될때 디버깅
        SRxLOBData *pLOBData = m_pTheNewSigAnal->GetLOBData();
        pLOBData->vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;

#endif

        g_pTheEmitterMerge->QMsgSnd( enTHREAD_DETECTANAL_RESULT, m_pTheNewSigAnal->GetLOBData(), sizeof( struct SRxLOBData), uiTotalLOB, GetUniMessageData(), sizeof( UNI_MSG_DATA ), GetThreadName() );

#ifdef _HARMONIC_GENPDW_
        g_pTheSignalCollect->m_bHarmonic = true;
#endif

    }
#ifdef _SERIAL_DETECT_FLOW_
    else {
        g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_DETECTWINDOWCELL, & m_pMsg->x.strCollectInfo, sizeof( STR_COLLECT_INFO ), GetThreadName() );
    }
#else
    g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SET_DETECTWINDOWCELL, & m_pMsg->x.strCollectInfo, sizeof( STR_COLLECT_INFO ), GetThreadName() );

#endif


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
    unsigned int uiTotalPDW;

    STR_STATIC_PDWDATA *pStaticPDWData;

    _PDW *pPDWSrc, *pPDWDest;

    pStaticPDWData = ( STR_STATIC_PDWDATA * ) GetRecvData();

    // 헤더 복사
    memcpy( & m_PDWData.x, & pStaticPDWData->x, sizeof( UNION_HEADER) );

    // 데이터 복사
    pPDWSrc = & pStaticPDWData->stPDW[0];
    pPDWDest = & m_PDWData.pstPDW[0];
    uiTotalPDW = pStaticPDWData->GetTotalPDW();

    memcpy( pPDWDest, pPDWSrc, uiTotalPDW * sizeof( _PDW ) );

}


