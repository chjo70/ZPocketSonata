#ifndef CSINGLESERVER_H
#define CSINGLESERVER_H

#include <sys/socket.h>
#include <netinet/in.h>


#include "../Include/system.h"

#include "../Utils/cthread.h"


class CSingleServer : public CThread
{
private:
    int m_iPort;
    int m_iSocket;

    STR_MessageData *m_pMsg;

public:
    CSingleServer( int iKeyId, char *pClassName, int iPort );
    virtual ~CSingleServer();

    void Run();
    virtual void _routine();
    virtual const char *ChildClassName() { return m_szClassName; }

public:
    int SendLan( UINT uiOpCode, void *pData, UINT uiLength );
    void CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket );

};


#endif // CSINGLESERVER_H
