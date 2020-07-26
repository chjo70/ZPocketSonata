#ifndef CURBIT_H
#define CURBIT_H


#include "./Include/sysmsg.h"
#include "./Utils/cthread.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// 아래는 이 쓰레드에서 사용하는 클래스를 정의합니다.
#include "./Utils/cgpio.h"

/**
 * @brief 자체점검 쓰레드 입니다.
 */
class CUrBit : public CThread
{
private:
    int m_nBoardID;

    CGPIO m_theGPIO;

public:
    static CUrBit *pInstance;

    STR_MessageData *m_pMsg;

private:
    void Init();

public:
    CUrBit( int iKeyId, char *pClassName=NULL );
    ~CUrBit();

    void Run();
    void ReleaseInstance();

    //

    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CUrBit* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CUrBit( g_iKeyId++, (char*)"CUrBit" );
        }
        return pInstance;
    }
};

#define URBIT     CUrBit::GetInstance()

#endif // CURBIT_H
