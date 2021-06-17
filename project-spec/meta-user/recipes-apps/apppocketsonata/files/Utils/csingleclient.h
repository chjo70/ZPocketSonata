#ifndef CSINGLECLIENT_H
#define CSINGLECLIENT_H

#ifdef __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#endif


#include "../Include/system.h"

#include "../Utils/cthread.h"

#include "../Thread/creclan.h"

// 클라이언트로 서버를 연결 횟수
#define NUM_OF_SERVER       (4)

class CSingleClient : public CThread
{
private:
    bool m_bServer;
    bool m_bConnected;
    char m_szServerAddress[NUM_OF_SERVER][100];

    int m_iPort;
    int m_iSocket;

    STR_MessageData *m_pMsg;

    char *m_pszLanData;

    CRecLan *m_ptheRecLan;

    // 랜 송신시 데이터
    STR_LAN_HEADER m_strLanHeader;
    unsigned int *m_puiData;

public:
    CSingleClient( int iKeyId, char *pClassName, int iPort, char *pServerAddress=NULL );
    virtual ~CSingleClient();

    void Run( key_t key );
    virtual void _routine();
    virtual const char *GetThreadName() { return m_szClassName; }

private:
    void RunServer();
    void RunClient();
    void OnConnect( struct sockaddr_in *pAddr=NULL );
    int ConnectTimeout( int sock, struct sockaddr_in *pAddress, unsigned long timeout_milli );
    void OnDisconnected( char *pServerIPAddress );

    void Alloc();
    void Free();

    void DisplayMsg();

public:
    void Init();
    int SendLan( UINT uiOpCode, void *pData, UINT uiLength );
    void CloseSocket( struct sockaddr_in *pAddress, int *pClientSocket );
    void CloseSocket();



    inline bool IsConnected() { return m_bConnected; }

};


#endif // CSINGLESERVER_H
