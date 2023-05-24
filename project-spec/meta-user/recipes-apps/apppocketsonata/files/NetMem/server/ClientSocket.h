#pragma once
#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "../utils/ApiNetMem.h"
#include "ServerSocket2.h"
//#include <boost/thread/thread.hpp>
//#include <boost/thread/mutex.hpp>

using namespace ApiNetMem;

class ClientSocket
{
public:
	ClientSocket(int id, int socket,ServerSocket *server);
	~ClientSocket();
	void operator()();
	int StartThreadSocket();
	void Join();
	int id;

    static void RunClientSocket( ClientSocket *pObject );

    void Run();

#ifdef _MSC_VER
    static DWORD WINAPI EntryPoint( LPVOID pArg )
    {
        ClientSocket *pParent = reinterpret_cast< ClientSocket * >( pArg );

        //pParent->ThreadCtor();

        pParent->Run();

        //pParent->ThreadDtor();

        return STILL_ACTIVE;
    }
#endif


private:
    //boost::thread *threadSocket;
#ifdef _MSC_VER
    HANDLE m_hThread;
    DWORD  m_dwTID;
    LPTHREAD_START_ROUTINE	m_pThreadFunc;	//	The Worker Thread Function Pointer

#elif defined(__VXWORKS__)
    TASK_ID m_TaskID;
    int m_iPriority;
#else

#endif

	//boost::mutex mutex;
#ifdef _MSC_VER
    CMutex _rwMutex;
#else
    sem_t rwMutex;
#endif

	int  connectSocket;
	int ExecuteCommand(NetMemCommand *command);
	int ReadCommand(NetMemCommand *command);
	int ReadBytes(unsigned char * bytes, int length);
	int SendCommand(NetMemCommand * command);
	void Destroy();
	ServerSocket *server;
	NetMemCommand response_m;
	NetMemCommand command_m;
};

#endif /*CLIENTSOCKET_H*/
