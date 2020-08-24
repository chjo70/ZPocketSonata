#ifndef CSIGNALCOLLECT_H
#define CSIGNALCOLLECT_H


#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Collect/ccollectbank/ccollectbank.h"
#include "../Collect/DataFile/DataFile.h"



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

public:
    static CSignalCollect *pInstance;

    STR_MessageData *m_pMsg;

private:
    void Init();
    void AnalysisStart();

    void CloseDetectCollectBank();
    void CloseTrackCollectBank();
    void CloseScanCollectBank();
    void CloseUserCollectBank();

    int CheckCollectBank( ENUM_COLLECTBANK enCollectBank );

    void SimPDWData();

public:
    CSignalCollect( int iKeyId, char *pClassName=NULL, bool bArrayLanData=false );
    virtual ~CSignalCollect(void);

    THREAD_STANDARD_FUNCTION( CSignalCollect )

};

#define SIGCOL          CSignalCollect::GetInstance()
#define SIGCOL_RELEASE  CSignalCollect::ReleaseInstance()

#endif // CSIGNALCOLLECT_H
