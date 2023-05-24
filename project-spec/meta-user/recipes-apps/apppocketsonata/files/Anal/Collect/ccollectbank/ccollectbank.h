/**

    @file      ccollectbank.h
    @brief     수집 뱅크 구헤더 파일 입니다.
    @details   ~
    @author    조철희
    @date      24.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/


#pragma once


#include "../../../Include/system.h"

#include "../../../Anal/EmitterMerge/Stack.h"

#include "../../../Anal/INC/PDW.h"

#include "../../../Utils/PCIDriver.h"


#define DETECT_COLLECTION_MEMORY_SIZE          (NEW_COLLECT_PDW)
#define TRACK_COLLECTION_MEMORY_SIZE           (KWN_COLLECT_PDW)
#define SCAN_COLLECTION_MEMORY_SIZE            (SCN_COLLECT_PDW)        //
#define USER_COLLECTION_MEMORY_SIZE            (USR_COLLECT_PDW)

#define MAX_LOGIC_MEMORY_SIZE                   ( 8192 )

// 스캔 최대 수집 단계 개수
#define SCANCOLLECTION_STEP                     (4)

class CCollectBank
{
private:
    ENUM_PCI_DRIVER m_enPCIDriver;

    unsigned int m_uiTotalChannels;
    unsigned int m_uiDetectChannel;
    unsigned int m_uiTrackChannel;
    unsigned int m_uiScanChannel;

    STR_WINDOWCELL **m_pstrWindowCell;

    Queue<int> m_theQueueTrackChannel;
    Queue<int> m_theQueueScanChannel;

    SRxABTData* m_ABTData;       // 추적/스캔 채널에 대한 대상 위협 정보

    unsigned int m_uiScanCollectionTimems[SCANCOLLECTION_STEP+1];

public:
    CPCIDriver *m_pThePCI;
    static STR_COLLECT_PCIADDRESS *m_pstrCollectPCIAddress;

public:
    CCollectBank( unsigned int iDetectChannel, unsigned int iTracnChannel, unsigned int iScanChannel, ENUM_PCI_DRIVER enPCIDriver );
    ~CCollectBank( );

private:
    void Alloc();
    void Free();
    void Init();
    void InitWindowCell( unsigned int uiCh );

    bool IsValidChannel();

    void ShowAllScanCahennelInfo();
    void ShowScanCahennelInfo( STR_WINDOWCELL *pstrWindowCell );

    ///////////////////////////////////////////////////////////////////////////////////
    // 탐지 신호 수집 설정


    // 추적 신호 수집 설정


    // 스캔 신호 수집 설정
    void CalScanWindowCell( STR_WINDOWCELL *pstrWindowCell, SRxABTData *pABTData, SRadarMode *pRadarMode, unsigned int uiScanStep );

    // 공통 관련 함수 설정
    unsigned int GetStat( SRxABTData *pABTData );


public:
    ENUM_COLLECTBANK GetEnumCollectBank( unsigned int uiCh ) const;

    // 신호 수집 시작 설정
    void StartCollecting();
    void EndCollecting();

    // 수집 종료
    void CloseCollectBanks();
    void CloseCollectBank( unsigned int uiCh, unsigned int uiTotalPDW );

    // void UpdateWindowCell( unsigned int uiCh  );
    bool IsCompleteCollect( unsigned int uiCh );

    void StartWindowCell( STR_WINDOWCELL* pstWindowCell );

    ///////////////////////////////////////////////////////////////////////////////////
    // 탐지 신호 수집 설정
    void StartDetectChannel( unsigned int uiCh );
    void CalDetectWindowCell( STR_WINDOWCELL *pstWindowCell );

    // 추적 신호 수집 설정


    // 스캔 신호 수집 설정
    int StartScanChennel( SRxABTData *pABTData, SRadarMode *pRadarMode, unsigned int uiScanStep );

    void CloseTrackWindowCell();

    void SetCollectUpdateTime( unsigned int uiCh );

    // 기타 관련 함수
    void SaveCollectCahnnelInfo( unsigned int uiCh, SRxABTData *pABTData, unsigned int uiABTINdex, unsigned int uiScanStep );

    void GetPDWData( STR_UZPOCKETPDW *pPDWData, unsigned int uiCh, unsigned int uiTotalPDW );


	// 인라인 함수 모음
    inline void SetCollectMode( unsigned int uiCh, ENUM_COLLECT_MODE enMode ) { GetWindowCell( uiCh )->enCollectMode = enMode; }
//     inline int GetChannelNo() { return m_iChannelNo; }
    inline unsigned int GetTotalPDW( unsigned int uiCh ) { return GetWindowCell( uiCh )->uiTotalPDW; }
//     inline STR_WINDOWCELL *GetWindowCell() { return & m_strWindowCell; }
    inline STR_UZPOCKETPDW *GetPDWData( unsigned int uiCh ) { return &GetWindowCell( uiCh )->strPDW; }
    inline bool IsSave( unsigned int uiCh ) { return GetWindowCell(uiCh)->enCollectMode == enCollecting; }

    inline STR_WINDOWCELL* GetWindowCell( unsigned int uiCh ) { return m_pstrWindowCell[uiCh]; }

    inline SRxABTData *GetChannel2ABTData( unsigned int uiCh ) { return & GetWindowCell(uiCh)->stABTData; }
    inline unsigned int GetChannel2ABTIndex( unsigned int uiCh )
    {
        return GetWindowCell( uiCh )->uiABTIndex;
    }

#ifdef _SIM_PDW_
    // 모의 관련 함수
    void SimCollectMode( unsigned int uiCh );
    bool IsFiltered( unsigned int uiCh, _PDW *pstPDW );
    int CheckCollectBank( ENUM_COLLECTBANK enCollectBank );
    void SimFilter( STR_PDWDATA *pPDWData );

    //void PushPDWData( STR_PDWDATA *pstrArrayPDW );
    void PushPDWData( unsigned int uiCh, _PDW *pstPDW, UNION_HEADER *pHeader );


#endif

};



