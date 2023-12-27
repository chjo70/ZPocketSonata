#ifndef CMULTISERVER_H
#define CMULTISERVER_H

#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#endif


#include "../Include/system.h"

#include "../Utils/cthread.h"

//#include "../Thread/coperationconsole.h"

#include "../../MSC/ZCCUSIM/csbc.h"

enum ENUM_TCPIP_EVENT {
    ON_CONNECT=0xC0,
    ON_DISCONNECT,
    ON_RECEIVE,

};


enum ENUM_TCPIP_TYPE {
    _SERVER_TYPE = 0,
    _CLIENT_TYPE
};

struct STR_CLIENT_SOCKET {
    SOCKET iSocket;
    sockaddr_in socketAddress;

    int iIndex;

};

struct STR_CLIENT_RECVSTAT {
    bool bHeader;
    int iTotalRead;

    char *pszLanData;

} ;


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

    struct sockaddr_in m_SockaddrInternet;         ///< 소켓 주소
    SOCKET m_MasterSock;                    ///< 마스터 소켓
    int m_iServerType;                      ///< TCPIP 형태

    Queue<int> m_QIndex;

    STR_CLIENT_RECVSTAT m_szRcvStat[MAX_CLIENTS];

    STR_LAN_DATA *m_pstLanData[MAX_CLIENTS];                                           ///< 랜 메시지를 처리하기 위한 저장소

	CSBC *m_ptheSBC;

    void *m_pParent;

public:
    std::vector<STR_CLIENT_SOCKET> m_vClientSock;

public:
    CMultiServer( int iKeyId, char *pClassName, int iPort, void *pParent );			///< 초기 멤버 변수값 등을 설정하는 객체 생성자 입니다.
    virtual ~CMultiServer();											///< 종료 메시지와 메모리 해지를 처리하는 객체 소먈자 입니다.

    void InitOfTCPIP();                                                 ///< TCPIP 초기화 관련 함수 수행

    void Run();												///< CThread 클래스의 Run() 함수를 호출하여 쓰레드를 생성하게 합니다.
    virtual void _routine();											///< 쓰레드에서 서버 또는 클라이언트를 실행하게 한다.
    //virtual char *GetThreadName() { return m_szThreadName; }			///< 쓰레드명을 리턴합니다.


    // 상속 받았을 때 부모 클래스에서 호출
    int Send( const void *pData, unsigned int uiLength );

    // 상속 받았을 때 부모 클래스 호출
    //virtual void ConnectMessage( STR_CLIENT_SOCKET* pClientSocket ) = 0;
    //virtual void DisConnectMessage( STR_CLIENT_SOCKET* pClientSocket ) = 0;
    //virtual void ProcessLANMessage( STR_LAN_DATA *pLanMessage ) = 0;

    static UINT WinRun( LPVOID pParam );

private:
    void Init();														///< 메모리를 할당하고 변수를 초기화한다.
    void Alloc();														///< 객체에 필요한 메모리를 할당한다.
    void Free();														///< 객체 메모리를 해지한다.

    void Connect( STR_CLIENT_SOCKET* pClientSocket );
    void ProcessLANMessage( int iIndex );

    void CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket );	///< 소켓을 닫을 때 이 함수를 호출한다.

public:
    int SendLan( unsigned short usOpCode, void *pData, UINT uiLength );			///< 연결된 서버에 데이터를 송신한다.

    void CloseSocket( const STR_CLIENT_SOCKET *pstClientSocket );

    STR_MessageData *GetParentMessage() { return NULL; }              ///< 메시지 데이터를 리턴 합니다.


};

#endif // CMULTISERVER_H
