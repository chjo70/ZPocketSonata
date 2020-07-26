#include "../utils/PortableSocket.h"
#include "ServerSocket.h"
#include "ClientSocket.h"

#include <iostream>
#include <cstring>

using namespace std;


ServerSocket::ServerSocket(int noPages, int lenght)
{
	threadSocket = NULL;
	this->noPages=noPages;
	this->lengthPage=lenght;
	InitPages();
}

int ServerSocket::InitPages()
{
	for (int i=0;i<noPages;i++)
	{
		pages.push_back(new MemoryPage(lengthPage,1));
	}
	return 1;
}

ServerSocket::~ServerSocket()
{
	if (threadSocket) delete(threadSocket);

	for (int i=0;i<noPages;i++)
	{
		delete (pages[i]);
	}
}

void ServerSocket::CleanUpClient(int &clientId)
{
	for (int i=0;i<noPages;i++)
	{
		pages[i]->Unlock(0,clientId);
	}
}

void ServerSocket::operator()()
{
	static int clientIds=0;
	int connectSocket;
	unsigned short int listenPort;
	socklen_t clientAddressLength;
	struct sockaddr_in clientAddress, serverAddress;

	listenPort=port;
  
 	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
 	if (listenSocket < 0) 
	{
    	cerr << "cannot create listen socket";
    	return;
 	}
 
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(listenPort);
  
	if (bind(listenSocket,(struct sockaddr *) &serverAddress,sizeof(serverAddress)) < 0) 
	{
    	cerr << "cannot bind socket";
    	return;
	}

	listen(listenSocket, 5);
  
	while (1) 
	{
		{
			boost::lock_guard<boost::mutex> lock(mutex);	
			cout << "Waiting for TCP connection on port " << listenPort << " ...\n";
		}

		clientAddressLength = sizeof(clientAddress);
		connectSocket = accept(listenSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
		if (connectSocket < 0) 
		{
			cerr << "connection closed";
			return;
		}

		{
			boost::lock_guard<boost::mutex> lock(mutex);	
			cout << "  connected to " << inet_ntoa(clientAddress.sin_addr);
			cout << ":" << ntohs(clientAddress.sin_port) << "\n";
		}
		
		ClientSocket * cs = new ClientSocket(clientIds++,connectSocket,this);
		cs->StartThreadSocket();
	}
}


int ServerSocket::StartThreadSocket(int port)
{	
	this->port=port;
	if (threadSocket) delete(threadSocket);
	threadSocket = new boost::thread (boost::ref(*this));
	return 1;
}

int ServerSocket::StopSocket()
{
	closesocket(listenSocket);
	return 0;
}

void ServerSocket::Join()
{
	if (threadSocket) threadSocket->join();
}
