/**

    @file      csignalcollect.h
    @brief     신호 수집 헤더 파일
    @details   ~
    @author    조철희
    @date      11.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

#include "../Utils/cthread.h"

#include "../Anal/Collect/ccollectbank/ccollectbank.h"
#include "../Anal/Collect/DataFile/DataFile.h"

#include "../Anal/Identify/Identify.h"

#include "../Utils/PCIDriver.h"

#include "../Utils/clog.h"


/**
 * @brief The CSignalCollect class
 */
#ifdef _MSSQL_
class CSignalCollect : public CThread, public CMSSQL
#else
class CSignalCollect : public CThread
#endif
{
private:
    unsigned int m_uiPDWID;

    Queue<UNI_MSG_DATA> m_theQueueScanAnal;

#ifdef _SIM_PDW_
    char *m_pstrPDWWithFileHeader;

    SIGAPDW *m_pSIGAPDW;
    UNION_HEADER *m_pUniHeader;

    unsigned int m_uiCoSim;
    _TOA m_ullTOA;
    unsigned int m_uiIndex;

#endif


#ifdef _SQLITE_

#elif defined(_MSSQL_)
    CODBCDatabase m_theMyODBC;
#else
#endif

    STR_STATIC_PDWDATA m_stPDWData;

    UNI_LAN_DATA m_uniLanData;

    bool m_bSendEnd;

    STR_TRKSCNPDWDATA m_theTrkScnPDW;

    CELSignalIdentifyAlg *m_pIdentifyAlg;		///< CED/EOb 신호 식별 객체

    SRxABTData m_stABTData;                     //< 신호 수집시 ABT 데이터를 갖고 오기 위한 저장소

#ifdef _SIM_PDW_
    CDataFile m_theDataFile;

#endif

public:
    CCollectBank *m_pTheLeftCollectBank;
    CCollectBank *m_pTheRigtCollectBank;

    STR_MessageData *m_pMsg;


private:
    void Alloc();
    void Free();

    void InitOfMessageData();
    void InitSignalCollect();
    void AnalysisStart();
    //void RoutineForSimPDW();

    void SendEndCollect();

    // 신호 수집 완료 관련 함수
    void CompleteCollecting();

    // 탐지 채널 관련 함수
    void StartDetectChannel( unsigned int uiCh, ENUM_PCI_DRIVER enPCIDriver );
    void ReqDetectWindowCell( );
    void CloseDetectChannel( unsigned int uiCh, ENUM_PCI_DRIVER enPCIDriver, unsigned int uiTotalPDW );

    // 추적 채널 관련 함수
    void ReqTrackWindowCell();
    void CloseTrackWindowCell();
    void NewTrackWindowCell( SRxABTData *pABTData );
    void StartTrackWindowCell();
    void CalTrackWindowCell( STR_WINDOWCELL *pstWindowCell, SRxABTData *pABTData );
    void UpdateTrackWindowCell( SRxABTData *pABTData );
    void CloseTrackWindowCell( SRxABTData *pABTData );

    // 스캔 채널 관련 함수
    void StartScanChannel();
    void ReqScanWindowCell();
    void CloseScanWindowCell();
    void UpdateScanWindowCell( SRxABTData *pABTData );
    void CloseScanChannel( unsigned int uiCh, ENUM_PCI_DRIVER enPCIDriver, unsigned int uiTotalPDW );

    // 공통 채널 관련 함수
    void CloseCollectBank();
    void StartCollecting();
    void GetPDWDataFromDetectChannel();

    // 위협 관리에서 관리되고 있는 최신의 빔 데이터를 얻는다.
    bool CopyFromEmitterABTData( SRxABTData *pABTData );
    bool IsValidABT();
    ENUM_PCI_DRIVER WhichPCIDriver();

    //inline SRxABTData *GetABTData( unsigned int uiIndex ) { return & m_ABTData[uiIndex]; }
    inline void ClearEndCollect() { m_bSendEnd = false; }


public:
#ifdef _MSSQL_
    CSignalCollect( int iThreadPriority, const char *pClassName=NULL, bool bArrayLanData=false );
#else
    CSignalCollect( int iThreadPriority, const char *pClassName=NULL, bool bArrayLanData=false );
#endif


    virtual ~CSignalCollect(void);

    void Run( key_t key=IPC_PRIVATE );
    void MakeStaticPDWData( STR_STATIC_PDWDATA *pStaticPDWData, STR_UZPOCKETPDW *pPDWData, bool bAutoIncPDWID=false );

    void _routine();
    char *GetThreadName() { return m_szThreadName; }
    STR_MessageData *GetParentMessage() { return m_pMsg; }                          ///< 메시지 데이터를 리턴 합니다.

    CCollectBank *GetCollectBank( ENUM_PCI_DRIVER enPCIDriver );

#ifdef _SIM_PDW_
    void MakeSIMPDWData();

    void SimPDWData();
    void SimFilter( STR_PDWDATA *pPDWData, ENUM_PCI_DRIVER enPCIDriver );

    void CheckAllCollectBank();
    int CheckCollectBank( ENUM_COLLECTBANK enCollectBank, ENUM_PCI_DRIVER enPCIDriver );
    void CheckDetectCollectBank( ENUM_PCI_DRIVER enPCIDriver );
    void CheckScanCollectBank( ENUM_PCI_DRIVER enPCIDriver );

#endif

};



