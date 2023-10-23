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

class CUDPServer
{
private:
    int m_iPort;
    int m_iSocket;


    char m_szMessage[MAX_MSG];

public:
    CUDPServer( int iPort );
    virtual ~CUDPServer();

private:
    void Alloc();
    void Free();
    int ReadBytes( int iSocket, char *pchData, int length );

public:
    void Init();
    void Run();
    void CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket );

};


#endif // CSINGLESERVER_H
