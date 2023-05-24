/**

    @file      NetworkMemory.h
    @brief
    @details   ~
    @author    Cool Guy
    @date      17.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


#include "../utils/ApiNetMem.h"
#include "ClientMemoryPage.h"
#include "../server/MemoryPage2.h"

#include <vector>
using namespace std;
using namespace ApiNetMem;
//#include <boost/thread/mutex.hpp>

#define NET_MEM_CLIENT_MAJOR_VERSION 0
#define NET_MEM_CLIENT_MINOR_VERSION 1

class NetworkMemory
{
public:
	NetworkMemory(char * host, int serverPort);
	NetworkMemory(NetworkMemory * netMem);
	~NetworkMemory();
private:
	int InitSocket(char * host, int serverPort);

	void CloseConnection();
	int SendCommand(NetMemCommand * command);
	int ReadCommand(NetMemCommand * response);
	int ReadBytes(unsigned char * bytes, int length);
	int InitPages();
	int CheckVersions();

	vector<MemoryPage *> m_VecMemoryPage;
	int  m_iConnectSocket;

	//server coordinates
	int m_iPort;
	char * m_pHost;

	//the numbers of instances that share the same cache
	static int noInstances;

	//static boost::mutex cacheMutex;
#ifdef _MSC_VER
    static CMutex _cacheMutex;

#elif defined(__VXWORKS__)
	static sem_t cacheMutex;

#elif defined(__linux__)
    static sem_t cacheMutex;

#endif

	int instanceId;

public:
	int GetParams(NetMemCommand * command);
	ClientMemoryPage * LockPage(NetMemCommand * command);
	int ReadPage(NetMemCommand * command);
	int UnlockPage(ClientMemoryPage * page);
	int UpdatePage(NetMemCommand * command);
	long GetServerVersion();

};


