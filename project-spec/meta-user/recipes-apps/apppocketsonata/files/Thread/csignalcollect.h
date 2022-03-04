#ifndef CSIGNALCOLLECT_H
#define CSIGNALCOLLECT_H


//#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Anal/Collect/ccollectbank/ccollectbank.h"
#include "../Anal/Collect/DataFile/DataFile.h"

#include "../Anal/Identify/Identify.h"

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
#ifdef _SQLITE_
    char m_szSQLString[4000];

    Kompex::SQLiteDatabase *m_pDatabase;

#elif defined(_MSSQL_)
    CODBCDatabase m_theMyODBC;
#else
#endif

    STR_STATIC_PDWDATA m_stPDWData;

    CDataFile m_theDataFile;

    UNI_LAN_DATA m_uniLanData;

    SRxABTData m_ABTData[SCAN_CHANNEL+TRACK_CHANNEL];       // 추적/스캔 채널에 대한 대상 위협 정보

    static CCollectBank *m_pTheDetectCollectBank[DETECT_CHANNEL];
    static CCollectBank *m_pTheTrackCollectBank[TRACK_CHANNEL];
    static CCollectBank *m_pTheScanCollectBank[SCAN_CHANNEL];
    static CCollectBank *m_pTheUserCollectBank[USER_CHANNEL];

    Queue<unsigned int> m_theTrackChannel;
    Queue<unsigned int> m_theScanChannel;

    CELSignalIdentifyAlg *m_pIdentifyAlg;		///< CED/EOb 신호 식별 객체

    CCollectBank *m_pTheCollectBank;

    bool m_bSendEnd;

    STR_TRKSCNPDWDATA m_theTrkScnPDW;

public:
    STR_MessageData *m_pMsg;

private:
    void Init();
    void AnalysisStart();
    void RoutineForDetectAnal();

    void CloseCollectBank();
    void SetupDetectCollectBank( int iCh );

    int CheckCollectBank( ENUM_COLLECTBANK enCollectBank );

    void SendEndCollect();

    // 탐지 채널 관련 함수
    void ReqTrackWindowCell();
    void CloseTrackWindowCell();
    void NewTrackWindowCell( SRxABTData *pABTData );
    void StartTrackWindowCell();
    void CalTrackWindowCell( STR_WINDOWCELL *pstWindowCell, SRxABTData *pABTData );
    void UpdateTrackWindowCell( SRxABTData *pABTData );
    void CloseTrackWindowCell( SRxABTData *pABTData );

    // 스캔 채널 관련 함수
    void ReqScanWindowCell();
    void CloseScanWindowCell();
    void NewScanWindowCell( SRxABTData *pABTData );
    void CalScanWindowCell( STR_WINDOWCELL *pstrWindowCell, SRxABTData *pABTData );
    void UpdateScanWindowCell( SRxABTData *pABTData );


    void SimPDWData();
    void SimFilter( STR_PDWDATA *pPDWData );

    inline SRxABTData *GetABTData( int iIndex ) { return & m_ABTData[iIndex]; }
    inline void ClearEndCollect() { m_bSendEnd = false; }

    CCollectBank *GetCollectBank( unsigned int uiCh ) {
        CCollectBank *pCCollectBank=NULL;

        if( uiCh < DETECT_CHANNEL )
            pCCollectBank = m_pTheDetectCollectBank[uiCh];
        else if( uiCh < DETECT_CHANNEL+TRACK_CHANNEL )
            pCCollectBank = m_pTheTrackCollectBank[uiCh-DETECT_CHANNEL];
        else if( uiCh < DETECT_CHANNEL+TRACK_CHANNEL+SCAN_CHANNEL )
            pCCollectBank = m_pTheScanCollectBank[uiCh-DETECT_CHANNEL-TRACK_CHANNEL];
        else
            pCCollectBank = m_pTheUserCollectBank[uiCh-DETECT_CHANNEL-TRACK_CHANNEL-SCAN_CHANNEL];

        return pCCollectBank;

    }

public:
#ifdef _MSSQL_
    CSignalCollect( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
#else
    CSignalCollect( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
#endif

    
    virtual ~CSignalCollect(void);

    void Run( key_t key=IPC_PRIVATE );
    void MakeStaticPDWData( STR_PDWDATA *pPDWData );

    virtual void _routine();
    virtual const char *GetThreadName() { return m_szThreadName; }

};


#endif // CSIGNALCOLLECT_H
