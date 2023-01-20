#ifndef CSINGLESERVER_H
#define CSINGLESERVER_H

#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#elif __VXWORKS__
#include <netinet/in.h>
#else
#endif


#include "../Include/system.h"

#include "../Utils/cthread.h"

#include "../Thread/coperationconsole.h"

class CSingleServer : public CThread
{
private:
    int m_iPort;
    int m_iSocket;

    STR_MessageData *m_pMsg;

    char *m_pszLanData;

	COperationConsole *m_ptheRecLan;

public:
    CSingleServer( int iKeyId, char *pClassName, int iPort );
    virtual ~CSingleServer();

    void Run( key_t key );
    virtual void _routine();
    virtual char *GetThreadName() { return m_szThreadName; }

private:
    void Alloc();
    void Free();

public:
    void Init();
    int SendLan( UINT uiOpCode, void *pData, UINT uiLength );
    void CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket );

};


#endif // CSINGLESERVER_H
