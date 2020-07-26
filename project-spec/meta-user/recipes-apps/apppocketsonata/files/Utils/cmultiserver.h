#ifndef CMULTISERVER_H
#define CMULTISERVER_H

#include <sys/socket.h>
#include <netinet/in.h>


#include "./Include/system.h"

#include "./Utils/cthread.h"

#define MAX_LAN_DATA    (1024)


class CMultiServer : public CThread
{
private:
    int m_iPort;
    int m_iSocket;

public:
    CMultiServer( int iKeyId, char *pClassName, int iPort );
    virtual ~CMultiServer();

    void Run();
    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

private:
    void CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket );

public:
    int SendLan( UINT uiOpCode, UINT uiLength, void *pData );


};

#endif // CMULTISERVER_H
