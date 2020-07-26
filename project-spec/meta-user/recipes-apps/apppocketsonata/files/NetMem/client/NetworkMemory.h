#pragma once
#ifndef NETWORKMEMORY_H
#define NETWORKMEMORY_H

#include "../utils/ApiNetMem.h"
#include "ClientMemoryPage.h"
#include "../server/MemoryPage.h"

#include <vector>
using namespace std;
using namespace ApiNetMem;
#include <boost/thread/mutex.hpp>

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

	vector<MemoryPage *> pages;
	int  connectSocket;
	
	//server coordinates
	int port;
	char * host;
	
	//the numbers of instances that share the same cache
	static int noInstances;
	static boost::mutex cacheMutex;
	
	int instanceId;

public:	
	int GetParams(NetMemCommand * command);
	ClientMemoryPage * LockPage(NetMemCommand * command);
	int ReadPage(NetMemCommand * command);
	int UnlockPage(ClientMemoryPage * page);
	int UpdatePage(NetMemCommand * command);
	long GetServerVersion();

};

#endif /*NETWORKMEMORY_H*/
