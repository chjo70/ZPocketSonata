#ifndef CSIGNALCOLLECT_H
#define CSIGNALCOLLECT_H


#include "../Include/system.h"
#include "../Utils/cthread.h"

#include "../Collect/ccollectbank/ccollectbank.h"



/**
 * @brief The CSignalCollect class
 */
class CSignalCollect : public CThread
{
private:
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

public:
    CSignalCollect( int iKeyId, char *pClassName=NULL );
    virtual ~CSignalCollect(void);

    void Run();
    void ReleaseInstance();

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CSignalCollect* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CSignalCollect( g_iKeyId++, (char*)"CSignalCollect" );
        }
        return pInstance;
    }
};

#define SIGCOL     CSignalCollect::GetInstance()

#endif // CSIGNALCOLLECT_H
