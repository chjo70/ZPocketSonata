#pragma once
#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "../utils/ApiNetMem.h"
#include "ServerSocket.h"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

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
private:
	boost::thread *threadSocket;
	boost::mutex mutex;
	
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
