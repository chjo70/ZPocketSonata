#ifndef CRECLAN_H
#define CRECLAN_H

#include "./Include/sysmsg.h"
#include "./Utils/cthread.h"

class CRecLan : public CThread
{
private:
    static CRecLan *pInstance[2];

    STR_MessageData *m_pMsg;
    int m_iIndex;

private:


public:
    CRecLan( int iKeyId, int iIndex, char *pClassName=NULL );
    ~CRecLan();

    void Run();
    void ReleaseInstance();

    // 명령에 대한 처리 함수 정의
    void DumpList();


    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

    static CRecLan* GetInstance( int iIndex )
    { // 게으른 초기화
        if(pInstance[iIndex] == NULL) {
            pInstance[iIndex] = new CRecLan( g_iKeyId++, iIndex, (char*)"CRecLan" );
        }
        return pInstance[iIndex];
    }

public:
    int SendLan( int iSocket, UINT uiOpCode, UINT uiLength, void *pData );

};

#define RECZYNQ     CRecLan::GetInstance(0)
#define RECCCU      CRecLan::GetInstance(1)

#endif // CRECLAN_H
