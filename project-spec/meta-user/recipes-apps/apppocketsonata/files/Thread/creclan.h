#ifndef CRECLAN_H
#define CRECLAN_H

//#include "../Include/system.h"
#include "../Utils/cthread.h"

static char gszClassName[2][10] = { "RECZYNQ", "RECCCU" };

class CRecLan : public CThread
{
private:
    static CRecLan *m_pInstance[2];

    STR_MessageData *m_pMsg;
    int m_iIndex;

private:


public:
    CRecLan( int iKeyId, int iIndex, char *pClassName=NULL, bool bArrayLanData=false );
    ~CRecLan();

    void Run( key_t key );
    void ReleaseInstance();

    // 명령에 대한 처리 함수 정의
    void DumpList();


    virtual void _routine();
    virtual const char *GetThreadName() { return m_szThreadName; }

    static CRecLan* GetInstance( int iIndex )
    { // 게으른 초기화
        if(m_pInstance[iIndex] == NULL) {
            m_pInstance[iIndex] = new CRecLan( g_iKeyId++, iIndex, (char*) gszClassName[iIndex], true );
        }
        return m_pInstance[iIndex];
    }

public:
    int SendLan( int iSocket, UINT uiOpCode, UINT uiLength, void *pData );

};

#define RECZYNQ     CRecLan::GetInstance(0)
#define RECCCU      CRecLan::GetInstance(1)

#endif // CRECLAN_H
