#ifndef CSIGNALCOLLECT_H
#define CSIGNALCOLLECT_H


#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Collect/ccollectbank/ccollectbank.h"
#include "../Collect/DataFile/DataFile.h"

#include "../Anal/Identify/Identify.h"

/**
 * @brief The CSignalCollect class
 */
class CSignalCollect : public CThread
{
private:
    CDataFile m_theDataFile;

    UNI_LAN_DATA m_uniLanData;

    CCollectBank *m_pTheDetectCollectBank[DETECT_CHANNEL];
    CCollectBank *m_pTheTrackCollectBank[TRACK_CHANNEL];
    CCollectBank *m_pTheScanCollectBank[SCAN_CHANNEL];
    CCollectBank *m_pTheUserCollectBank[USER_CHANNEL];

    Queue<unsigned int> m_theTrackChannel;

    CELSignalIdentifyAlg *m_pIdentifyAlg;		///< CED/EOb 신호 식별 객체

    STR_WINDOWCELL *m_pStrWindowCell;
    CCollectBank *m_pTheCollectBank;

public:
    static CSignalCollect *pInstance;

    STR_MessageData *m_pMsg;

private:
    void Init();
    void AnalysisStart();

    void CloseCollectBank();
    void SetupDetectCollectBank( int iCh );

    int CheckCollectBank( ENUM_COLLECTBANK enCollectBank );

    void SendEndCollect();

    // 윈도우셀 모의
    void ReqSetWindowCell();
    void ReqSetWindowCell( SRxABTData *pABTData, UINT uiCh );
    void NewTrackWindowCell( SRxABTData *pABTData );
    void StartTrackWindowCell();
    void CalTrackWindowCell( SRxABTData *pABTData );
    void UpdateTrackWindowCell( SRxABTData *pABTData );
    bool IsValidChannle();


    void SimPDWData();
    unsigned int SimFilter( STR_PDWDATA *pPDWData );
    bool IsFiltered( _PDW *pstPDW, STR_WINDOWCELL *pWindowCell );

    ENUM_COLLECTBANK GetEnumCollectBank( unsigned int uiCh ) {
        ENUM_COLLECTBANK enCollectBank=enUnknownCollectBank;

        if( uiCh < DETECT_CHANNEL )
            enCollectBank = enDetectCollectBank;
        else if( uiCh < DETECT_CHANNEL+TRACK_CHANNEL )
            enCollectBank = enDetectCollectBank;
        else if( uiCh < DETECT_CHANNEL+TRACK_CHANNEL+SCAN_CHANNEL )
            enCollectBank = enDetectCollectBank;
        else
            enCollectBank = enUserCollectBank;

        return enCollectBank;
    }

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
    CSignalCollect( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CSignalCollect(void);

    THREAD_STANDARD_FUNCTION( CSignalCollect )

};

#define SIGCOL          CSignalCollect::GetInstance()
#define SIGCOL_RELEASE  CSignalCollect::ReleaseInstance()

#endif // CSIGNALCOLLECT_H
