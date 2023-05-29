

#ifndef CUDPSERVER_H
#define CUDPSERVER_H

#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#elif defined(__VXWORKS__)
#include <netinet/in.h>
#else
#endif

#define     MAX_MSG            (100)
#define     MAX_CLIENTS         (5)

#define     CHECK_SERVER_TIME   (10)


enum ENUM_SOCKET_ERROR {
    ENUM_ERROF_OF_SOCKET = 0,
    ENUM_ERROF_OF_BIND,
    ENUM_ERROF_OF_SOCKETOPT,

    ENUM_ERROF_OF_THREATINFO,

};

class CUDPServer
{
private:
    int m_iPort;
    int m_iCheckServerPort;
    int m_iSocket;

#ifdef __VXWORKS__
    int m_iStdinOption;
#endif

    int m_iServerSocket;

    char m_szMessage[MAX_MSG];

public:
    CUDPServer( int iPort );
    virtual ~CUDPServer();

private:
    void Alloc();
    void Free();
    int ReadBytes( int iSocket, char *pchData, int length );


    bool CreateServer( int iPort );

    // 키보드 옵션 저장하기 및 불러오기
    int SaveStdInOption();
    void ReStoreStdInOption();

public:
    void Init();
    void Run();
    void CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket );

    void CheckServer();

};


#endif // CSINGLESERVER_H
