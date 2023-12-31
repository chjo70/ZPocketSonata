/**

    @file      cemittermerge.h
    @brief     위협 관리 ㅁ치 신호 식별 관련 헤더 파일
    @details   ~
    @author    조철희
    @date      19.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/EmitterMerge/ELEmitterMergeMngr.h"

#include "../Utils/clog.h"

typedef enum {
    ABNORMAL_TRACK_CLOSE=0,
    NORMAL_TRACK_CLOSE_DELETE,
    NORMAL_TRACK_CLOSE

} ENUM_TRACK_CLOSE;

/**
*
* @brief	  식별/위협 관리를 처리하는 클래스 입니다.
* @details	  신호분석 연동 제어 기능을 수행한다
* @author    조철희 (churlhee.jo@lignex1.com)
* @version   1.0.0
* @date      2023-01-16 10:54:00
* @warning
*
*/

#ifdef _MSSQL_
class CEmitterMerge : public CThread, public CMSSQL
#else
class CEmitterMerge : public CThread
#endif
{
private:

#ifdef _MSSQL_
    CODBCDatabase m_theMyODBC;
#endif

    // 랜 메시지 처리
    										///< 쓰레드 간의 메시지 에서 이 쓰레드에서 사용할 메시지의 데이터 저장소 입니다.
#ifdef __VXWORKS__
	// 32 -> 16비트 강제 packed 구조체 정의
    alignas(16) UNI_LAN_DATA m_uniLanData;							///< 랜 메시지 데이터 입니다.
#else
    UNI_LAN_DATA m_uniLanData;										///< 랜 메시지 데이터 입니다.
#endif

    CELEmitterMergeMngr *m_pTheEmitterMergeMngr;					///< 식별/위협을 처리하는 클래스 입니다.

    SLOBOtherInfo m_sLOBOtherInfo;									///< 식별/위협을 처리하는 추가 페라미터 변수 모음 입니다.

    SRxLOBData *m_pLOBData;                                         ///< 메시지의 빔 데이터 포인터

    Queue<unsigned int> m_theQueueTrackChannel[en_ELEMENT_PCI_DRIVER];       ///< 추적 채널 번호 큐 저장소

public:
    STR_MessageData *m_pMsg;										///< CThread 에서 사용하는 단일 메시지 데이터 포인터 입니다.

private:
    void InitEmitterMerge();
    void MergeEmitter();
    //void MergeTrackEmitter();
    void TrackEmitter();
    void DeleteThreat();
    void RemoveThreat();

    void InitOfMessageData();

#if CO_SCAN_CHANNEL > 0
    void UpdateScanResult();
    void UpdateScanFail();
    void UpdateScanError();
    void UserRequestScan();
    void SendUserReqScanResult();
    void SendSelfScanResult();
    void SwapScanResult( SELUSERSCANRESULT *pstUserScanResult );

#endif

    // 수집 쓰레드에 추적/스캔 요청을 전송한다.
    void RequestTrackCollect( SRxLOBData *pLOBData, ENUM_COLLECTBANK enCollectBank, SRxABTData *pABTData=NULL, SELABTDATA_EXT *pABTExtData=NULL );
    void RequestTrackClose( ENUM_TRACK_CLOSE enTrackClose, STR_TRKANAL_INFO *pstTRKAnalInfo=NULL, SELABTDATA_EXT *pABTExtData=NULL );
    void RequestAbnormalTrackClose();
    void RequestNormalTrackClose();
    void RequestTrackLostDelete();
    void RequestScanCollect( unsigned int uiAETID, unsigned int uiABTID );
    void RequestScanReCollect();

    void ReloadLibrary();

    void SendNewUpd( unsigned int uiOpCode );
    void SendDelete( unsigned int uiAETID );
    void SendLanByTime( unsigned int uiOpcode, SAETData *pData, SELABTDATA_EXT *pABTExtData );
    void SendLanByTime( unsigned int uiOpcode, SELLOST *pData, SELABTDATA_EXT *pABTExtData );
    void SendLanByTime( unsigned int uiOpcode, STR_TRKANAL_INFO *pRecvTrackAnalInfo, unsigned int uiDataSize, SELABTDATA_EXT *pABTExtData );
    void SwapAETData( SAETData *pstAET );

    void CleanupDatabase();
    void BackupDatabase();

    void MakeLOBData( SRxLOBData *pLOBData );

public:
    CEmitterMerge( int iThreadPriority, const char *pThreadName, bool bArrayLanData );
    virtual ~CEmitterMerge(void);

    void Init();

    inline CELEmitterMergeMngr *GetEmitterMergeMngr() { return m_pTheEmitterMergeMngr; }	///< 객체 포인터를 리턴합니다.

    void SetSaveFile( bool bSaveFile );

    void Run( key_t key=IPC_PRIVATE );
    void _routine();
    const char *GetThreadName() { return m_szThreadName; }								///< 쓰레드명을 리턴합니다.
    STR_MessageData *GetParentMessage() { return m_pMsg; }                          ///< 메시지 데이터를 리턴 합니다.


    /**
     * @brief     GetABTData
     * @param     unsigned uiIndex
     * @return    SRxABTData *
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-14 15:23:13
     * @warning
     */
    SRxABTData *GetABTData( unsigned uiIndex ) {
        SRxABTData *pABTData = NULL;

        if( uiIndex != 0 ) {
            pABTData = m_pTheEmitterMergeMngr->GetABTData( uiIndex );
        }

        return pABTData;
    }


    /**
     * @brief     GetABTData
     * @param     ENUM_COLLECTBANK enCollectBank
     * @return    SRxABTData *
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-14 15:23:16
     * @warning
     */
    SRxABTData *GetABTData( ENUM_COLLECTBANK enCollectBank, SRxLOBData *pLOBData=NULL ) {
        SRxABTData *pABTData = NULL;

        if( enCollectBank == enDetectCollectBank ) {
            if( pLOBData != NULL ) {
                pABTData = m_pTheEmitterMergeMngr->FindABTData( pLOBData->uiAETID, pLOBData->uiABTID );
            }
            else {
                pABTData = m_pTheEmitterMergeMngr->GetABTData();
            }
        }
        else {
            if( m_pRecvTrackAnalInfo->uiAETID != 0 ) {
                pABTData = m_pTheEmitterMergeMngr->FindABTData( m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID );
            }
            else {
                pABTData = m_pTheEmitterMergeMngr->GetABTData();
            }
        }

        return pABTData;
    }

    /**
     * @brief     GetABTExtData
     * @param     ENUM_COLLECTBANK enCollectBank
     * @return    SELABTDATA_EXT *
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-14 15:25:24
     * @warning
     */
    SELABTDATA_EXT *GetABTExtData( ENUM_COLLECTBANK enCollectBank, SRxLOBData *pLOBData=NULL )
    {
        SELABTDATA_EXT *pABTExtData = NULL;

        if( enCollectBank == enDetectCollectBank ) {
            if( pLOBData != NULL ) {
                pABTExtData = m_pTheEmitterMergeMngr->FindABTExtData( pLOBData->uiAETID, pLOBData->uiABTID );
            }
            else {
                pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData();
            }
        }
        else {
            if( m_pRecvTrackAnalInfo->uiAETID != 0 ) {
                pABTExtData = m_pTheEmitterMergeMngr->FindABTExtData( m_pRecvTrackAnalInfo->uiAETID, m_pRecvTrackAnalInfo->uiABTID );
            }
            else {
                pABTExtData = m_pTheEmitterMergeMngr->GetABTExtData();
            }
        }

        return pABTExtData;
    }


};



