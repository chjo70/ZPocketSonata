#ifndef CMULTISERVER_H
#define CMULTISERVER_H

#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#endif


#include "../Include/system.h"

#include "../Utils/cthread.h"

#include "../Thread/creclan.h"



class CMultiServer : public CThread
{
private:
    int m_iPort;
    int m_iSocket;

    char *m_pszLanData[MAX_CLIENTS];

    CRecLan *m_ptheRecLan;

public:
    CMultiServer( int iKeyId, char *pClassName, int iPort );
    virtual ~CMultiServer();

    void Run( key_t key );
    virtual void _routine();
    virtual const char *GetThreadName() { return m_szThreadName; }

private:
    void Init();
    void Alloc();
    void Free();
    void CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket );

public:
    int SendLan( UINT uiOpCode, void *pData, UINT uiLength );


};

#endif // CMULTISERVER_H
