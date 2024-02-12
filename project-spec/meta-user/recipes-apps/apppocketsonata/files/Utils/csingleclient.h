/*
 * 본 문서는 시스템을 정의하는 테이블과 운영체계 또는 컴파일러에 의존하여 정의한다.
 * */

#pragma once

#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>


#elif defined( __VXWORKS__)
#include <arpa/inet.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

#endif

#include "../Include/system.h"

#include "../Utils/cthread.h"
#include "../Utils/clog.h"
#include "../Thread/coperationconsole.h"

/**
 *
 * @brief	  단일 서버/클라리언트 생성하여 랜 메시지를 처리하는 클래스 입니다.
 * @details	  신호분석 연동 제어 기능을 수행한다
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 10:54:00
 * @warning
 *
 */
class CSingleClient : public CThread
{
private:
    void *m_pParent;

    bool m_bServer;									///< 서버/클라이언트 여부 플레그
    bool m_bConnected;								///< 연결 여부 플레그

    static bool m_bDebugConnected;

    string m_strConnectedAddress;

    vector<string> m_vecServerAddress;

    unsigned short m_usPort;						///< 포트 번호
    SOCKET m_soSocket;						///< 소켓 번호

    STR_MessageData *m_pMsg;						///< CThread 에서 사용하는 단일 메시지 데이터 포인터

    char *m_pszLanData;								///< 수신 메시지 데이터를 임시 저장하기 위한 저장소

    COperationConsole *m_ptheOperationConsole;				///< ES/EA통합운용콘솔 관련 메시지를 송/수신 처리하기 위한 객체

public:
    CSingleClient( int iKeyId, const char *pThreadName, COperationConsole *ptheOperationConsole, unsigned short iPort, char *pClientAddress=NULL, void *pParent=NULL );	///< 초기 멤버 변수값등을 설정하는 객체 생성자 입니다.
    ~CSingleClient();																				        ///< 종료 메시지와 메머리 해지를 처리하는 객체 소먈자 입니다.

    void Run( key_t key );																					///< CThread 클래스의 Run() 함수를 호출하여 쓰레드를 생성하게 합니다.

	void Init();																							///< 메모리를 할당하고 변수를 초기화한다.
	int SendLan(UINT uiOpCode, void *pData, size_t szLength, BOOL bSwap=TRUE );								///< 연결된 서버에 데이터를 송신한다.
    int SendStringLan( UINT uiOpCode, const char *pstring );                                                ///< 연결된 서버에 데이터를 송신한다.
	void CloseSocket(struct sockaddr_in *pAddress, int *pClientSocket);										///< 소켓을 닫을 때 이 함수를 호출한다.
	void CloseSocket( bool bEnableLog=true );																///< 소켓을 닫을 때 이 함수를 호출한다.

	inline bool IsConnected() { return m_bConnected; }														///< 랜 연결 여부를 리턴합니다.
    inline void Connected( bool bConnected, struct sockaddr_in *pAddr=NULL ) {
        m_bConnected = bConnected;
        if( bConnected == true ) {
            m_strConnectedAddress = inet_ntoa( pAddr->sin_addr );
        }
        else {
            m_strConnectedAddress.clear();
        }
    }

    void _routine();																				        ///< 쓰레드에서 서버 또는 클라이언트를 실행하게 한다.
    const char *GetThreadName() { return m_szThreadName; }												    ///< 쓰레드명을 리턴합니다.
    STR_MessageData *GetParentMessage() { return m_pMsg; }                                                  ///< 메시지 데이터를 리턴 합니다.

    const char *GetConnectedAddress() { return m_strConnectedAddress.c_str(); }
    
private:
    void RunServer();																						///< 랜 소켓 서버 실행시 소켓으로부터 수신 메시지를 확인한다.
    void RunClient();																						///< 랜 소켓 클라이언트 실행시 소켓으로부터 수신 메시지를 확인한다.
    void SetSocketOption();
    void OnConnect( struct sockaddr_in *pAddr=NULL );														///< 연결시 이벤트를 발생한다.
    int ConnectTimeout( SOCKET soSock, struct sockaddr_in *pAddress, long timeout_milli );			        ///< 설정한 시간만큼 서버와 연결을 시도한다.
    void OnDisconnected( const char *pServerIPAddress );													///< 랜 소켓이 끊어졌을때 이벤트를 발생합니다.

    void Alloc();																							///< 객체에 필요한 메모리를 할당한다.
    void Free();																							///< 객체 메모리를 해지한다.

    void DisplayMsg(STR_LAN_HEADER *pHeader, const void *pData, bool bSend );								///< 랜 메시지를 출력합니다.

};

extern CSingleClient *g_pTheCCUSocket;
extern CSingleClient *g_pTheCCUDebugSocket;

extern void SendLan( UINT uiOpCode, void *pData, size_t szDataLength, BOOL bSwap = TRUE );
extern void SendStringLan( UINT uiOpCode, const char *pData, ... );
