#pragma once
#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "MemoryPage2.h"
// #include <boost/thread/thread.hpp>

#ifdef _MSC_VER
#include <afxmt.h>

#define getcwd  _getcwd
#define mkdir   _mkdir
#define open    _open
#define write   _write
//#define closeSharedMemory   _close

#else
#include <semaphore.h>

#endif

#define NET_MEM_SERVER_MAJOR_VERSION 0
#define NET_MEM_SERVER_MINOR_VERSION 2

using namespace std;
#include <vector>

class ServerSocket
{
public:
	ServerSocket(int noPages, int length);
	~ServerSocket();
	void RunServerSocket();
	int StartThreadSocket(int port);
	int StopSocket();
	void Join();
	vector<MemoryPage *> pages;
	int noPages;
	int lengthPage;
	int InitPages();
	void CleanUpClient(int &clientId);

    void Run();

#ifdef _MSC_VER
    static DWORD WINAPI EntryPoint( LPVOID pArg )
    {
        ServerSocket *pParent = reinterpret_cast< ServerSocket * >( pArg );

        //pParent->ThreadCtor();

        pParent->Run();

        //pParent->ThreadDtor();

        return STILL_ACTIVE;
    }

	//boost::mutex mutex;

    CMutex m_Mutex;
    CSingleLock *m_theMutex;

#else
    sem_t m_Mutex;
#endif

private:
    bool m_bThreadLoop;

	int m_iPort;

    // boost::thread *threadSocket;
#ifdef _MSC_VER
    HANDLE m_hThread;
    DWORD  m_dwTID;
    LPTHREAD_START_ROUTINE	m_pThreadFunc;	//	The Worker Thread Function Pointer

#elif defined(__VXWORKS__)
    TASK_ID m_TaskID;
    int m_iPriority;
#else

#endif

	int listenSocket;
};

#endif /*SERVERSOCKET_H*/
