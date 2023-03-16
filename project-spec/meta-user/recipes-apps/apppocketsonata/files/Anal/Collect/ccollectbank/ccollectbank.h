#ifndef CCOLLECTBANK_H
#define CCOLLECTBANK_H

#include "../../../Include/system.h"

#include "../../../Anal/EmitterMerge/Stack.h"

#include "../../../Anal/INC/PDW.h"

#include "../../../Utils/PCIDriver.h"

#define CO_DETECT_CHANNEL	(1)                         // 탐지용 채널은 1개로 설정함. 현재 PL 전처리필터의 채널이 1개임.
#define CO_TRACK_CHANNEL	(8)
#define CO_SCAN_CHANNEL		(8)
#define CO_USER_CHANNEL		(0)
#define TOTAL_CHANNELS		(CO_DETECT_CHANNEL+CO_TRACK_CHANNEL+CO_SCAN_CHANNEL+CO_USER_CHANNEL)

class CCollectBank
{
private:
    const ENUM_PCI_DRIVER m_enPCIDriver;

    const unsigned int m_uiTotalChannels;
    const unsigned int m_uiDetectChannle;
    const unsigned int m_uiTrackChannle;
    const unsigned int m_uiScanChannle;

    STR_WINDOWCELL **m_pstrWindowCell;

    // STR_PDWDATA m_strPDW;

    //SRxABTData *m_ABTData[CO_SCAN_CHANNEL + CO_TRACK_CHANNEL];       // 추적/스캔 채널에 대한 대상 위협 정보
    SRxABTData* m_ABTData;       // 추적/스캔 채널에 대한 대상 위협 정보

public:
    CPCIDriver *m_pThePCI;

public:
    CCollectBank( unsigned int iDetectChannel, unsigned int iTracnChannel, unsigned int iScanChannel, ENUM_PCI_DRIVER enPCIDriver );
    ~CCollectBank( );

private:
    void Alloc();
    void Free();
    void Init();
    void InitWindowCell( unsigned int uiCh );

    bool IsValidChannel();

    ENUM_COLLECTBANK GetEnumCollectBank( unsigned int uiCh ) const;

public:
    // 신호 수집 시작 설정
    void StartCollecting();

    // 수집 종료
    void CloseCollectBanks();
    void CloseCollectBank( unsigned int uiCh );

    // void UpdateWindowCell( unsigned int uiCh  );
    bool IsCompleteCollect( unsigned int uiCh );

    void SetWindowCell( STR_WINDOWCELL* pstWindowCell );

    ///////////////////////////////////////////////////////////////////////////////////
    // 탐지 신호 수집 설정
    void StartDetectChannel( unsigned int uiCh );
    void CalDetectWindowCell( STR_WINDOWCELL *pstWindowCell );


    // 추적 신호 수집 설정

    //void PushPDWData( STR_PDWDATA *pstrArrayPDW );
    void PushPDWData( unsigned int uiCh, _PDW *pstPDW, UNION_HEADER *pHeader );
    void UpdateWindowCell( unsigned int uiCh, STR_WINDOWCELL *pstrWindowCell );
    void CloseTrackWindowCell();

    bool IsFiltered( unsigned int uiCh, _PDW *pstPDW );

    void SetCollectUpdateTime( unsigned int uiCh );


	// 인라인 함수 모음
    inline void SetCollectMode( unsigned int uiCh, ENUM_COLLECT_MODE enMode ) { GetWindowCell( uiCh )->enCollectMode = enMode; }
//     inline int GetChannelNo() { return m_iChannelNo; }
    inline unsigned int GetTotalPDW( unsigned int uiCh ) { return GetWindowCell( uiCh )->uiTotalPDW; }
//     inline STR_WINDOWCELL *GetWindowCell() { return & m_strWindowCell; }
    inline STR_PDWDATA *GetPDWData( unsigned int uiCh ) { return &GetWindowCell( uiCh )->strPDW; }
    inline bool IsSave( unsigned int uiCh ) { return GetWindowCell(uiCh)->enCollectMode == enCollecting; }

    inline STR_WINDOWCELL* GetWindowCell( unsigned int uiCh ) { return m_pstrWindowCell[uiCh]; }

#ifdef _SIM_PDW_
    // 모의 관련 함수
    void SimCollectMode( unsigned int uiCh );

    int CheckCollectBank( ENUM_COLLECTBANK enCollectBank );

#endif

};


#endif // CCOLLECTBANK_H
