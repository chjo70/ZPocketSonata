#include "csignalcollect.h"
#include "../Utils/clog.h"

#include "cdetectanalysis.h"
#include "ctrackanalysis.h"
#include "cscananalysis.h"

#include "../Utils/csingleserver.h"
#include "../Utils/cmultiserver.h"
#include "../Utils/ccommonutils.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CSignalCollect* CSignalCollect::pInstance = nullptr;

/**
 * @brief CSignalCollect::CSignalCollect
 * @param iKeyId
 * @param pClassName
 */
CSignalCollect::CSignalCollect( int iKeyId, char *pClassName ) : CThread( iKeyId, pClassName )
{
    int i;

    for( i=0 ; i < DETECT_CHANNEL ; ++i ) {
        m_pTheDetectCollectBank[i] = new CCollectBank(TOTAL_CHANNELS, i );
    }

    for( i=0 ; i < TRACK_CHANNEL ; ++i ) {
        m_pTheTrackCollectBank[i] = new CCollectBank(TOTAL_CHANNELS, i );
    }

    for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
        m_pTheScanCollectBank[i] = new CCollectBank(TOTAL_CHANNELS, i );
    }

    for( i=0 ; i < USER_CHANNEL ; ++i ) {
        m_pTheUserCollectBank[i] = new CCollectBank(TOTAL_CHANNELS, i );
    }

}


/**
 * @brief CSignalCollect::~CJamTech
 */
CSignalCollect::~CSignalCollect(void)
{
    int i;

    for( i=0 ; i < DETECT_CHANNEL ; ++i ) {
        delete m_pTheDetectCollectBank[i];
    }
    for( i=0 ; i < TRACK_CHANNEL ; ++i ) {
        delete m_pTheTrackCollectBank[i];
    }
    for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
        delete m_pTheScanCollectBank[i];
    }
    for( i=0 ; i < USER_CHANNEL ; ++i ) {
        delete m_pTheUserCollectBank[i];
    }

}

/**
 * @brief CSignalCollect::ReleaseInstance
 */
void CSignalCollect::ReleaseInstance()
{
    if(pInstance)
    {
        LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );

        delete pInstance;
        pInstance = NULL;
    }
}


/**
 * @brief CSignalCollect::Run
 */
void CSignalCollect::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CSignalCollect::_routine
 */
void CSignalCollect::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->szMessage[0];

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }

        switch( m_pMsg->ucOpCode ) {
            case enTHREAD_ANAL_START :
                AnalysisStart();
                break;

            case enTHREAD_REQ_SHUTDOWN :
                LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );
                bWhile = false;
                break;

            case enTHREAD_REQ_SETWINDOWCELL :
                LOGMSG( enDebug, "윈도우 셀을 설정합니다." );
                break;

            case enTHREAD_REQ_SIM_PDWDATA :
                break;

            default:
                LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->ucOpCode );
                break;
        }
    }

}

/**
 * @brief 객체를 초기화 합니다.
 */
void CSignalCollect::Init()
{
    // 추적 윈도우 셀을 닫는다.
    CloseTrackCollectBank();

    // 스캔 윈도우 셀을 닫는다.
    CloseScanCollectBank();

    // 탐지 분석판을
    //m_pTheDetectCollectBank[0]->SetWindowCell( );
}

/**
 * @brief 추적 윈도우셀을 닫는다.
 */
void CSignalCollect::CloseTrackCollectBank()
{
    int i;

    for( i=0 ; i < TRACK_CHANNEL ; ++i ) {
        m_pTheTrackCollectBank[i]->CloseCollectBank();
    }
}

/**
 * @brief 스캔 윈도우셀을 닫는다.
 */
void CSignalCollect::CloseScanCollectBank()
{
    int i;

    for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
        m_pTheScanCollectBank[i]->CloseCollectBank();
    }
}

/**
 * @brief 분석 시작을 처리한다.
 */
void CSignalCollect::AnalysisStart()
{
    LOGENTRY;

    int iCh;

    Init();

    while( true ) {
        // 탐지 채널 버퍼 체크
        iCh = CheckCollectBank( enDetectCollectBank );
        if( iCh >= 0 ) {
            QMsgSnd( DETANL->GetKeyId(), enTHREAD_ANAL_START, & iCh, sizeof(int) );
        }

        // 추적 채널 버퍼 체크
        iCh = CheckCollectBank( enTrackCollectBank );
        if( iCh >= 0 ) {
            QMsgSnd( TRKANL->GetKeyId(), enTHREAD_ANAL_START, & iCh, sizeof(int) );
        }

        // 스캔 채널 버퍼 체크
        iCh = CheckCollectBank( enScanCollectBank );
        if( iCh >= 0 ) {
            QMsgSnd( SCANANL->GetKeyId(), enTHREAD_ANAL_START, & iCh, sizeof(int) );
        }

        // 사용자 채널 버퍼 체크
        iCh = CheckCollectBank( enUserCollectBank );
        if( iCh >= 0 ) {
            CCommonUtils::SendLan( enREQ_MODE, & iCh, sizeof(int) );
        }

        sleep( 1 );
        printf( "." );
    }

}

/**
 * @brief 탐지 뱅크에 저장된 PDW 들을 검사하여 수집 완료된 채널을 리턴한다.
 * @return
 */
int CSignalCollect::CheckCollectBank( ENUM_COLLECTBANK enCollectBank )
{
    int i, iCh=-1;

    // 채널을 랜덤 또는 증가/감소 교대로 번갈아 가며 체크한다.
    switch( enCollectBank ) {
        case enDetectCollectBank :
            for( i=0 ; i < DETECT_CHANNEL ; ++i ) {
                if( true == m_pTheDetectCollectBank[i]->IsCompleteCollect() ) {
                    iCh = m_pTheDetectCollectBank[i]->GetChannelNo();

                    LOGMSG3( enDebug, "\n %s 뱅크[%d]에서 [%d] 채널에서 수집 완료히었습니다." , g_szCollectBank[enDetectCollectBank], i, iCh );
                    break;
                }
            }
            break;

        case enTrackCollectBank :
            for( i=0 ; i < TRACK_CHANNEL ; ++i ) {
                if( true == m_pTheTrackCollectBank[i]->IsCompleteCollect() ) {
                    iCh = m_pTheTrackCollectBank[i]->GetChannelNo();

                    LOGMSG3( enDebug, "\n %s 뱅크[%d]에서 [%d] 채널에서 수집 완료히었습니다." , g_szCollectBank[enDetectCollectBank], i, iCh );
                    break;
                }
            }
            break;

        case enScanCollectBank :
            for( i=0 ; i < SCAN_CHANNEL ; ++i ) {
                if( true == m_pTheScanCollectBank[i]->IsCompleteCollect() ) {
                    iCh = m_pTheScanCollectBank[i]->GetChannelNo();

                    LOGMSG3( enDebug, "\n %s 뱅크[%d]에서 [%d] 채널에서 수집 완료히었습니다." , g_szCollectBank[enDetectCollectBank], i, iCh );
                    break;
                }
            }
            break;

        case enUserCollectBank :
            for( i=0 ; i < USER_CHANNEL ; ++i ) {
                if( true == m_pTheUserCollectBank[i]->IsCompleteCollect() ) {
                    iCh = m_pTheUserCollectBank[i]->GetChannelNo();

                    LOGMSG3( enDebug, "\n %s 뱅크[%d]에서 [%d] 채널에서 수집 완료히었습니다." , g_szCollectBank[enDetectCollectBank], i, iCh );
                    break;
                }
            }
            break;

        default :
            break;

    }

    return iCh;
}
