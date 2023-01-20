#ifndef CMULTISERVER_H
#define CMULTISERVER_H

#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#endif


#include "../Include/system.h"

#include "../Utils/cthread.h"

#include "../Thread/coperationconsole.h"


/**
 *
 * @brief	  다중 서버 생성하여 랜 메시지를 처리하는 클래스 입니다.
 * @details	  신호분석 연동 제어 기능을 수행한다
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 10:54:00
 * @warning
 *
 */
class CMultiServer : public CThread
{
private:
    int m_iPort;							///< 포트 번호
    int m_iSocket;							///< 소켓 번호

    char *m_pszLanData[MAX_CLIENTS];		///< 수신 메시지 데이터를 임시 저장하기 위한 저장소

	COperationConsole *m_ptheRecLan;

public:
    CMultiServer( int iKeyId, char *pClassName, int iPort );			///< 초기 멤버 변수값 등을 설정하는 객체 생성자 입니다.
    virtual ~CMultiServer();											///< 종료 메시지와 메모리 해지를 처리하는 객체 소먈자 입니다.

    void Run( key_t key );												///< CThread 클래스의 Run() 함수를 호출하여 쓰레드를 생성하게 합니다.
    virtual void _routine();											///< 쓰레드에서 서버 또는 클라이언트를 실행하게 한다.
    virtual char *GetThreadName() { return m_szThreadName; }			///< 쓰레드명을 리턴합니다.

private:
    void Init();														///< 메모리를 할당하고 변수를 초기화한다.
    void Alloc();														///< 객체에 필요한 메모리를 할당한다.
    void Free();														///< 객체 메모리를 해지한다.
    void CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket );	///< 소켓을 닫을 때 이 함수를 호출한다.

public:
    int SendLan( UINT uiOpCode, void *pData, UINT uiLength );			///< 연결된 서버에 데이터를 송신한다.


};

#endif // CMULTISERVER_H
