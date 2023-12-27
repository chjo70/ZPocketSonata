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
#define SCAN_COLLECTION_MEMORY_SIZE            (SCN_COLLECT_PDW)
#define USER_COLLECTION_MEMORY_SIZE            (USR_COLLECT_PDW)

#define MAX_LOGIC_MEMORY_SIZE                  ( 128*1024 )

// 원형/고정형 경걔값
#define STEADY_SCAN_STEP                        (2)

class CCollectBank : public CLogName
{
private:
    unsigned int m_uiDetectChannel;
    unsigned int m_uiPreFilterChannel;
    unsigned int m_uiTrackChannel;
    unsigned int m_uiScanChannel;

    unsigned int m_uiTotalChannels;


    ENUM_PCI_DRIVER m_enPCIDriver;

    STR_WINDOWCELL **m_pstrWindowCell;

    Queue<int> m_theQueueScanChannel;

    SRxABTData* m_ABTData;       // 추적/스캔 채널에 대한 대상 위협 정보

public:
    CPCIDriver *m_pThePCI;
    static STR_COLLECT_PCIADDRESS *m_pstrCollectPCIAddress;
    static STR_COLLECT_PCIADDRESS *m_pstrPreFilterPCIAddress;

public:
    CCollectBank( unsigned int iDetectChannel, unsigned int iPreFilterChannel, unsigned int iTracnChannel, unsigned int iScanChannel, ENUM_PCI_DRIVER enPCIDriver, const char *pThreadName=NULL );
    virtual ~CCollectBank( );

private:
    void Alloc();
    void Free();
    void Init();
    void InitWindowCell( unsigned int uiCh );

    void DisplayPCIAddress();

    bool IsValidChannel();

    void ShowAllScanCahennelInfo();
    void ShowScanCahennelInfo( STR_WINDOWCELL *pstrWindowCell );

    ///////////////////////////////////////////////////////////////////////////////////
    // 탐지 신호 수집 설정


    // 추적 신호 수집 설정
    void CalTrackWindowCell( STR_WINDOWCELL *pstrWindowCell, SRxABTData *pABTData, SRadarMode *pRadarMode, STR_WINDOWCELL_INFO *pstTrackWindowCellInfo );
    unsigned int CalTrackCollecingPDW( SRxABTData *pABTData );

    // 스캔 신호 수집 설정
    void CalScanWindowCell( STR_WINDOWCELL *pstrWindowCell, SRxABTData *pABTData, SRadarMode *pRadarMode, unsigned int uiReqScanPeriod, unsigned int uiScanStep, STR_SCANRESULT *pstScanResult );
    void CheckScanPAFilter( STR_LOWHIGH *pstrPA, SRxABTData *pABTData, unsigned int uiReqScanPeriod, unsigned int uiScanStep, STR_SCANRESULT *pstScanResult );


public:
    ENUM_COLLECTBANK GetEnumCollectBank( unsigned int uiGlobalCh ) const;

    // 신호 수집 시작 설정
    void StartCollecting();
    void EndCollecting();

    // 수집 종료
    void CloseCollectBanks();
    void CloseCollectingInterrupt();
    void UpdateCollectBank( unsigned int uiCh, unsigned int uiColPDW );
    void CloseCollectBank( unsigned int uiCh, unsigned int uiColPDW=0 );

    // void UpdateWindowCell( unsigned int uiCh  );
    bool IsCompleteCollect( unsigned int uiCh );

    void StartWindowCell( STR_WINDOWCELL* pstWindowCell );

    ///////////////////////////////////////////////////////////////////////////////////
    // 탐지 신호 수집 설정
    void StartDetectChannel( unsigned int uiCh );
    void CalDetectWindowCell( STR_WINDOWCELL *pstWindowCell );

    // 추적 신호 수집 설정
    void StartTrackChannel( unsigned int uiCh, SRxABTData *pABTData, SRadarMode *pRadarMode, STR_WINDOWCELL_INFO *pstTrackWindowCellInfo );

    // 스캔 신호 수집 설정
    int StartScanChennel( SRxABTData *pABTData, SRadarMode *pRadarMode, unsigned int uiReqScanPeriod, unsigned int uiScanStep, STR_SCANRESULT *pstScanResult );

    void CloseTrackWindowCell();

    void SetCollectUpdateTime( unsigned int uiCh );

    // 기타 관련 함수
    void SaveCollectCahnnelInfo( unsigned int uiCh, SRxABTData *pABTData, unsigned int uiABTINdex=(unsigned int)-1, unsigned int uiScanStep=(unsigned int) -1, ENUM_ROBUST_ANAL enRobustAnal= enNO_ROBUST_ANALYSIS );

    void GetPDWData( STR_UZPOCKETPDW *pPDWData, unsigned int uiCh, unsigned int uiTotalPDW );


	// 인라인 함수 모음
    inline void SetCollectMode( unsigned int uiCh, ENUM_COLLECT_MODE enMode ) { GetWindowCell( uiCh )->enCollectMode = enMode; }
    inline unsigned int GetTotalPDW( unsigned int uiCh ) { return GetWindowCell( uiCh )->uiColPDW; }
    inline void SetTotalPDW( unsigned int uiCh, unsigned int uiTotalPDW ) { GetWindowCell( uiCh )->uiColPDW = uiTotalPDW; }
    inline STR_UZPOCKETPDW *GetPDWData( unsigned int uiCh ) { return &GetWindowCell( uiCh )->strPDW; }
    inline bool IsSave( unsigned int uiCh ) { return GetWindowCell(uiCh)->enCollectMode == enCollecting; }
    inline STR_WINDOWCELL* GetWindowCell( unsigned int uiGlobalCh ) { return m_pstrWindowCell[uiGlobalCh]; }
    inline SRxABTData *GetChannel2ABTData( unsigned int uiGlobalCh ) { return & GetWindowCell( uiGlobalCh )->stABTData; }
    inline ENUM_ROBUST_ANAL GetChannel2RobustMode( unsigned int uiGlobalCh ) { return GetWindowCell( uiGlobalCh )->enRobustAnal; }
    inline unsigned int GetChannel2ABTIndex( unsigned int uiGlobalCh )
    {
        return GetWindowCell( uiGlobalCh )->uiABTIndex;
    }

    inline bool IsFullOfCollecting( float fCoScanCollectingPDW )
    {
        return fCoScanCollectingPDW > 0.8;
    }

    inline bool IsFullOfDuration( float fScanDurationms )
    {
        return fScanDurationms > 0.8;
    }

    // 공통 관련 함수 설정
    /**
     * @brief     MakeSignalTypeOfWindowCell
     * @param     SRxABTData * pABTData
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-13 15:10:11
     * @warning
     */
    static unsigned int MakeSignalTypeOfWindowCell( SRxABTData *pABTData )
    {
        unsigned int uiStat = FILTER_SIGNALTYPE_NORMAL;

        if( pABTData->vSignalType == E_AET_SIGNAL_PULSE ) {
        }
        else {
            uiStat = FILTER_SIGNALTYPE_CW;
        }

        return uiStat;

    }

    /**
     * @brief     MakeBypassOfWindowCell
     * @param     SRxABTData * pABTData
     * @return    unsigned int
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-12-13 15:10:08
     * @warning
     */
    static unsigned int MakeByPassOfWindowCell( SRxABTData *pABTData )
    {
        unsigned int uiByPass = FILT_BYPASS_ALL;

        return uiByPass;

    }


#ifdef _SIM_PDW_
    // 모의 관련 함수
    void SimCollectMode( unsigned int uiCh );
    bool IsFiltered( unsigned int uiCh, _PDW *pstPDW );
    int CheckCollectBank( ENUM_COLLECTBANK enCollectBank );
    void SimFilter( STR_PDWDATA *pPDWData, bool bOnly );

    //void PushPDWData( STR_PDWDATA *pstrArrayPDW );
    void PushPDWData( unsigned int uiCh, _PDW *pstPDW, UNION_HEADER *pHeader );


#endif

};



