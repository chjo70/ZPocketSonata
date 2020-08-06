#ifndef CMULTISERVER_H
#define CMULTISERVER_H

#include <sys/socket.h>
#include <netinet/in.h>


#include "../Include/system.h"

#include "../Utils/cthread.h"

//#define MAX_LAN_DATA    (1024)


class CMultiServer : public CThread
{
private:
    int m_iPort;
    int m_iSocket;

    char *m_pszLanData[MAX_CLIENTS];

public:
    CMultiServer( int iKeyId, char *pClassName, int iPort );
    virtual ~CMultiServer();

    void Run();
    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

private:
    void Init();
    void Alloc();
    void Free();
    void CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket );

public:
    int SendLan( UINT uiOpCode, void *pData, UINT uiLength );


};

#endif // CMULTISERVER_H
