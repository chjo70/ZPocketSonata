#pragma once


//#include "../Include/system.h"
#include "../Utils/cthread.h"

static char gszClassName[2][10] = { "RECZYNQ", "RECCCU" };

/**
 *
 * @brief	  ES/EA통합운용콘솔 간의 메시지 송수신 처리를 수행합니다.
 * @details	  신호분석 연동 제어 기능을 수행한다
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 10:54:00
 * @warning
 *
 */
class COperationConsole : public CThread
{
private:
    static COperationConsole *m_pInstance[2];											///< 싱글톤 객체 입니다.

    STR_MessageData *m_pMsg;															///< 수신 메시지 데이터를 임시 저장하기 위한 저장소
    int m_iIndex;																		///< 싱글톤 인덱스

private:


public:
    COperationConsole( int iKeyId, int iIndex, char *pClassName=NULL, bool bArrayLanData=false );	///< 초기 멤버 변수값등을 설정하는 객체 생성자 입니다.
    ~COperationConsole();																			///< 종료 메시지와 메머리 해지를 처리하는 객체 소먈자 입니다.

    //void Run( key_t key );															///< CThread 클래스의 Run() 함수를 호출하여 쓰레드를 생성하게 합니다.
    void Run();																            ///< CThread 클래스의 Run() 함수를 호출하여 쓰레드를 생성하게 합니다.
    void ReleaseInstance();																///< 싱글톤을 메모리 해지하기 위한 함수 입니다.

    // 명령에 대한 처리 함수 정의
    //void DumpList();

    bool IsValidLanData( STR_MessageData *pMsg );										///< 운용 모드와 랜 메시지의 OPCODE에 따라 수행 여부를 리턴합니다.


    virtual void _routine();															///< 쓰레드에서 서버 또는 클라이언트를 실행하게 한다.
    virtual char *GetThreadName() { return m_szThreadName; }							///< 쓰레드명을 리턴합니다.

    static COperationConsole* GetInstance( int iIndex )									///< 싱글톤을 생성하기 위한 처리 입니다.
    { // 게으른 초기화
        if(m_pInstance[iIndex] == NULL) {
            m_pInstance[iIndex] = new COperationConsole( g_iKeyId++, iIndex, (char*) gszClassName[iIndex], true );
        }
        return m_pInstance[iIndex];
    }

    STR_MessageData *GetParentMessage() {
        return m_pMsg;
    }

public:
    int SendLan( int iSocket, UINT uiOpCode, UINT uiLength, void *pData );				///< 연결된 서버에 데이터를 송신한다.

};

#define RECZYNQ     COperationConsole::GetInstance(0)
#define RECCCU      COperationConsole::GetInstance(1)


