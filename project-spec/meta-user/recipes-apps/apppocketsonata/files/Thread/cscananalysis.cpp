// CScanAnalysis.cpp: implementation of the CScanAnalysis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "cscananalysis.h"
#include "cemittermerge.h"

#include "../Utils/csingleserver.h"
//#include "../Utils/cmultiserver.h"

#include "../Include/globals.h"

#define _DEBUG_



/**
 * @brief     스캔 주기/형태 분석 초기화 생성자 클래스 입니다.
 * @param     int iKeyId
 * @param     char * pClassName
 * @param     bool bArrayLanData
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-04 16:44:46
 * @warning
 */
CScanAnalysis::CScanAnalysis( int iThreadPriority, const char *pClassName, bool bArrayLanData ) : CThread( iThreadPriority, pClassName, bArrayLanData )
{

#ifdef _SQLITE_
    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy(szSQLiteFileName, EMITTER_SQLITE_FOLDER);
    strcat(szSQLiteFileName, "/");
#ifdef _MSC_VER
    char szSrcSQLiteFileName[100];

    sprintf( szSrcSQLiteFileName, "%s_%d.sqlite3", EMITTER_SQLITE_FILENAME, g_enBoardId );
    strcat( szSQLiteFileName, szSrcSQLiteFileName );
#else
    strcat( szSQLiteFileName, EMITTER_SQLITE_FILEEXTNAME );
#endif

    m_pTheScanSigAnal = new CScanSigAnal(SCN_COLLECT_PDW, false, szSQLiteFileName);
#else
    m_pTheScanSigAnal = new CScanSigAnal( SCN_COLLECT_PDW, false);

#endif

    _SAFE_NEW( m_pTheSysPara, CSysPara() )

    InitScanAnalysis();
}


/**
 * @brief CScanAnalysis::~CScanAnalysis
 */
CScanAnalysis::~CScanAnalysis(void)
{

    _SAFE_DELETE(m_pTheScanSigAnal)

    _SAFE_DELETE(m_pTheSysPara)

}


/**
 * @brief CScanAnalysis::Run
 */
void CScanAnalysis::Run(key_t msgQ)
{
    //LOGENTRY;

    CThread::Run();

}

/**
 * @brief     스캔 분석을 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-04 17:24:29
 * @warning
 */
void CScanAnalysis::_routine()
{
    //LOGENTRY;

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
                // 운용 제어 관련 메시지 처리
                case enREQ_OP_START:
                    // QMsgClear();
                    InitScanAnalysis();
                    break;

                case enTHREAD_DISCONNECTED:
                case enREQ_OP_SHUTDOWN:
                    //QMsgClear();
                    //InitScanAnalysis();
                    break;

                case enREQ_OP_RESTART:
                    //QMsgClear();
                    InitScanAnalysis();
                    break;

                // 신호 분석 곤련 메시지 처리
                case enTHREAD_SCANANAL_START :
                    InitOfMessageData();
                    AnalysisStart();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    Log( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                    //bWhile = false;
                    break;

                 default:
                    Log( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                    break;
            }

        }
    }

}

/**
 * @brief     PDW 와 빔 정보를 기반으로 스캔 분석을 시작한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-19, 17:43
 * @warning
 */
void CScanAnalysis::AnalysisStart()
{
    //LOGENTRY;

    STR_SCANRESULT *pScanResult;

    Log( enDebug, "스캔 : 위협[%d/%d] 에 대해서, 채널[%d], 스캔분석 요청주기 [%d ms] 에서 PDW[%d 개] 를 분석합니다.", m_pRecvScanAnalInfo->uiAETID, m_pRecvScanAnalInfo->uiABTID, m_pRecvScanAnalInfo->uiCh, m_pRecvScanAnalInfo->uiReqScanPeriod, m_pScnPDWData->strPDW.GetTotalPDW() );

    //CCommonUtils::Disp_FinePDW( ( STR_PDWDATA *) GetRecvData() );

    // 1. 스캔 신호 분석을 호출한다.
    m_pTheScanSigAnal->Start( & m_pScnPDWData->strPDW, & m_pScnPDWData->strABTData, m_pRecvScanAnalInfo->uiScanStep, m_pRecvScanAnalInfo->uiReqScanPeriod, & m_pRecvScanAnalInfo->stScanResult );

    // 2. 분석 결과를 병합/식별 쓰레드에 전달한다.
    pScanResult = & m_pRecvScanAnalInfo->stScanResult; //  m_pTheScanSigAnal->GetScanResult();
    m_pstrScanAnalInfo->Set( m_pRecvScanAnalInfo->uiCh, m_pRecvScanAnalInfo->enCollectBank, m_pRecvScanAnalInfo->uiAETID, m_pRecvScanAnalInfo->uiABTID, m_pRecvScanAnalInfo->uiABTIndex, 0, m_pRecvScanAnalInfo->uiScanStep, pScanResult );

    if( pScanResult->enResult == EN_SCANRESULT::_spAnalSuc ) {
        MakeLOBData();

        //?     LOB 데이터화 해서 병합으로 보내는게 좋지 않을까 ? 아니면 분석 결과면 보내는게 낳을까 ?
        //date 	2023-03-21 09:39:53
        g_pTheEmitterMerge->QMsgSnd( enTHREAD_SCANANAL_RESULT, & m_stLOBData, _spOne, sizeof( struct SRxLOBData ), GetUniMessageData(), sizeof( UNI_MSG_DATA ), GetThreadName() );
    }
    else {
        g_pTheEmitterMerge->QMsgSnd( enTHREAD_SCANANAL_FAIL, GetUniMessageData(), sizeof( union UNI_MSG_DATA ), GetThreadName() );
    }

}

/**
 * @brief     MakeLOBData
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-19 18:46:14
 * @warning
 */
void CScanAnalysis::MakeLOBData()
{
    SRxLOBData *pLOBData;

    pLOBData = m_pTheScanSigAnal->GetLOBData( 0 );
    memcpy( & m_stLOBData, pLOBData, sizeof( SRxLOBData ) );

    m_stLOBData.uiPDWID = 0;
    m_stLOBData.uiPLOBID = 0;

    // 방사체/빔 번호 저장
    m_stLOBData.uiAETID = m_pRecvScanAnalInfo->uiAETID;
    m_stLOBData.uiABTID = m_pRecvScanAnalInfo->uiABTID;
    m_stLOBData.uiLOBID = 0;

    CCommonUtils::GetCollectTime( &m_stLOBData.tiContactTime, &m_stLOBData.tiContactTimems );

    m_stLOBData.uiNumOfCollectedPDW = m_pScnPDWData->strPDW.GetTotalPDW();

//     if( m_pstABTData != NULL ) {
//     STR_SCANRESULT *pScanResult = m_pTheScanSigAnal->GetScanResult();
//         strcpy( m_stLOBData.szPrimaryELNOT, m_pstABTData->szPrimaryELNOT );
//         strcpy( m_stLOBData.szPrimaryModeCode, m_pstABTData->szPrimaryModeCode );
//
//         strcpy( m_stLOBData.szModulationCode, m_pstABTData->szModulationCode );
//
//         strcpy( m_stLOBData.szNickName, m_pstABTData->szNickName );
//
//         // 신호 형태 저장
//         m_stLOBData.vSignalType = m_pstABTData->vSignalType;
//
//         // 주파수 정보 저장
//         m_stLOBData.vFreqType = m_pstABTData->vFreqType;
//         m_stLOBData.vFreqPatternType = m_pstABTData->vFreqPatternType;
//
//         // PRI 정보 저장
//         m_stLOBData.vPRIType = m_pstABTData->vPRIType;
//         m_stLOBData.vPRIType = m_pstABTData->vPRIType;
//
//         // PA 정보 저장
//         m_stLOBData.fPAMin = 0;
//         m_stLOBData.fPAMax = 0;
//         m_stLOBData.fPAMean = 0;
//
//         // 스캔 정보 저장
//         m_stLOBData.vScanType = pScanResult->enScanType;
//         m_stLOBData.fMeanScanPeriod = pScanResult->fScanPeriod;
//
//         // 식별 정보 저장
//         m_stLOBData.uiRadarModeIndex = m_pstABTData->uiRadarModeIndex;
//         strcpy( m_stLOBData.szRadarModeName, m_pstABTData->szRadarModeName );
//     }

}



/**
 * @brief     InitScanAnalysis
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 15:50:24
 * @warning
 */
void CScanAnalysis::InitScanAnalysis()
{
    m_pScnPDWData = NULL;

    m_pstABTData = NULL;

    // 테이블 삭제하기
    Log( enNormal, "테이블을 삭제합니다." );
    m_pTheScanSigAnal->DeleteDB_RAW( "RAWDATA" );

}

/**
 * @brief     InitOfMessageData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-21 09:54:03
 * @warning
 */
void CScanAnalysis::InitOfMessageData()
{
    m_pScnPDWData = ( STR_TRKSCNPDWDATA * ) GetRecvData();

    if( m_pScnPDWData != NULL ) {
        m_pstABTData = & m_pScnPDWData->strABTData;
    }
    else {
        m_pstABTData = NULL;
    }

}