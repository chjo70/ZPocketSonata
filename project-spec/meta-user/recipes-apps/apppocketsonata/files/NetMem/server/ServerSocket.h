#pragma once
#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "MemoryPage.h"
#include <boost/thread/thread.hpp>

#define NET_MEM_SERVER_MAJOR_VERSION 0
#define NET_MEM_SERVER_MINOR_VERSION 2

using namespace std;
#include <vector>

class ServerSocket
{
public:
	ServerSocket(int noPages, int lenght);
	~ServerSocket();
	void operator()();
	int StartThreadSocket(int port);
	int StopSocket();
	void Join();
	vector<MemoryPage *> pages;
	int noPages;
	int lengthPage;
	int InitPages();
	void CleanUpClient(int &clientId);
	boost::mutex mutex;
private:
	int port;
	boost::thread *threadSocket;
	int listenSocket;
};

#endif /*SERVERSOCKET_H*/
