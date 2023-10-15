/**

    @file      cudpserver.h
    @brief
    @details   ~
    @author    조철희
    @date      30.05.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#elif defined(__VXWORKS__)
#include <netinet/in.h>
#elif defined(_MSC_VER)
#include <thread>

using std::thread;

#endif

#include "../Anal/INC/OS.h"

#define MAX_MSG                 (10)
#define MAX_CLIENTS             (5)

#define CHECK_SERVER_TIME       (10)

#define KEY_TIMEOUT             (1)


enum ENUM_SOCKET_ERROR {
    ENUM_ERROF_OF_SOCKET = 0,
    ENUM_ERROF_OF_BIND,
    ENUM_ERROF_OF_SOCKETOPT,

};

class CUDPServer
{
private:
    char m_szIPAddress[100];

    int m_iPort;
    int m_iServerPort;
    int m_iClientPort;

    int m_iCheckServerPort;

    SOCKET m_iServerSocket;

    bool m_bGetKey;

#ifdef _MSC_VER
    thread m_tThread;

#elif defined( __VXWORKS__)
    TASK_ID m_tThread;

#endif

#ifdef __VXWORKS__
    int m_iStdinOption;
    TASK_ID m_ShellTaskID;
#endif

    char m_szMessage[MAX_MSG];

public:
    CUDPServer( char *szIPAddress, int iPort );
    virtual ~CUDPServer();

private:
    void Alloc();
    void Free();
    int ReadBytes( int iSocket, char *pchData, int length );

    bool CreateServer( int iPort );
    void CloseSocket( SOCKET iSocket );

    // 키보드 옵션 저장하기 및 불러오기
    int SaveStdInOption();
    void ReStoreStdInOption( int stdInFd );

public:
    void Init();
    void RunServer();
    void CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket );

    // UDP 서버에게 메시지를 전달합니다.
    void SendAllUDPServer();


    void CheckServer();

    /**
     * @brief     ThreadRoutine
     * @param     void * pArg
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-05-31 09:20:08
     * @warning
     */
    static void ThreadRoutine( void *pArg )
    {
        CUDPServer *pCUDPServer = ( CUDPServer * ) pArg;

        pCUDPServer->RunServer();

    }

    inline char GetKey() { return m_szMessage[0]; }

};


