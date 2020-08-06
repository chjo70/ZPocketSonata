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

    void Run();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CSignalCollect* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CSignalCollect( g_iKeyId++, (char*)"CSignalCollect", true );
        }
        return pInstance;
    }

    void ReleaseInstance()
    {
        if(pInstance)
        {
            LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );

            delete pInstance;
            pInstance = NULL;
        }
    }

};

#define SIGCOL     CSignalCollect::GetInstance()

#endif // CSIGNALCOLLECT_H
