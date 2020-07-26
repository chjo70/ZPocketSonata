#include "../utils/PortableSocket.h"
#include "NetworkMemory.h"

using namespace std;

#include <iostream>
#include <cstring>

#define MAX_MSG 20000
#define LINE_ARRAY_SIZE (MAX_MSG+1)

int NetworkMemory::noInstances;
boost::mutex NetworkMemory::cacheMutex;

NetworkMemory::NetworkMemory(char * host, int serverPort)
{
	this->host = 0;
	connectSocket = -1;
	if(!InitSocket(host,serverPort)) throw NO_SERVER_CONNECTION;
	if(!InitPages()) throw NO_PAGES_INIT;
	if(!CheckVersions()) throw NO_COMPATIBLE_SERVER_VERSIONS;
	
	this->port = serverPort;
	this->host = (char *)malloc(strlen(host)+1);
	strcpy(this->host,host);
	
	noInstances=1;
	instanceId=1;
}

NetworkMemory::NetworkMemory(NetworkMemory * netMem)
{
	boost::mutex::scoped_lock tmpLock(cacheMutex);
	
	this->host = 0;
	connectSocket = -1;
	if(!InitSocket(netMem->host,netMem->port)) throw NO_SERVER_CONNECTION;
	
	//use the same cache
	for (int i=0;i<netMem->pages.size();i++)
	{
		pages.push_back(netMem->pages[i]);
	}
	this->port = netMem->port;
	this->host = (char *)malloc(strlen(netMem->host)+1);
	strcpy(this->host,netMem->host);
	
	noInstances++;
	instanceId=noInstances;
}

int NetworkMemory::CheckVersions()
{
	long version = GetServerVersion();
	unsigned short serverApiVersion = version>>16;
	unsigned short clientApiVersion = (API_NET_MEM_MAJOR_VERSION<<8)+API_NET_MEM_MINOR_VERSION;
	
	if (serverApiVersion==clientApiVersion) return 1;
	return 0;
}

int NetworkMemory::InitSocket(char * host, int serverPort)
{
	struct sockaddr_in serverAddress;
	struct hostent *hostInfo;

	hostInfo = gethostbyname(host);
	if (hostInfo == NULL) 
	{
		cout << "problem interpreting host: " << host << "\n";
		return 0;
	}

	connectSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (connectSocket < 0) 
	{
		cerr << "cannot create socket\n";
		return 0;
	}

	serverAddress.sin_family = hostInfo->h_addrtype;
	memcpy((char *) &serverAddress.sin_addr.s_addr,hostInfo->h_addr_list[0], hostInfo->h_length);
	serverAddress.sin_port = htons(serverPort);
				
	if (connect(connectSocket,(struct sockaddr *) &serverAddress,sizeof(serverAddress)) < 0) 
	{
		cerr << "cannot connect\n";
		return 0;
	}
	return 1;
}

NetworkMemory::~NetworkMemory()
{
	boost::mutex::scoped_lock tmpLock(cacheMutex);
	
	CloseConnection();
	if (host) free(host);
	
	noInstances--;
	
	if (noInstances==0)
	{
		for (int i=0;i<pages.size();i++)
		{
			delete (pages[i]);
		}
	}
}

int NetworkMemory::GetParams(NetMemCommand * response)
{
	if (!response) return 0;
	NetMemCommand command;
	command.type = GET_PARAMS;
	SendCommand(&command);
	return ReadCommand(response);
}

ClientMemoryPage * NetworkMemory::LockPage(NetMemCommand * command)
{
	NetMemCommand response;
	if (!command) return 0;
	if (command->offset>pages.size()) return 0;
	MemoryPage * cachePage = pages[command->offset];
	
	command->type = LOCK_PAGE;
	command->version=cachePage->version;

	SendCommand(command);
	//REFACTOR to set command->type to an error code for every case
	if (!ReadCommand(&response)) return NULL;
	if (response.type!=LOCK_PAGE) return NULL;
	if (response.offset>pages.size()) return NULL;

	
	ClientMemoryPage * newPage = new ClientMemoryPage(cachePage->length, command->offset, response.version);

	if (response.length)
	{
		memcpy(newPage->data, response.data,response.length);
		newPage->version=response.version;	
		cachePage->Update(response.data,response.version,instanceId);
		
	}
	else
	{
		cachePage->Read(newPage->data);
	}
	
	return newPage;
}

int NetworkMemory::ReadPage(NetMemCommand * command)
{
	NetMemCommand response;

	if (!command) return 0;
	if (command->offset>pages.size()) return 0;
	
	MemoryPage * cachePage = pages[command->offset];
	command->type = READ_PAGE;
	command->version=cachePage->version;
	SendCommand(command);
	
	//REFACTOR to set command->type to an error code for every case
	if (!ReadCommand(&response)) return 0;
	if (response.type!=READ_PAGE) return 0;
	if (response.offset>pages.size()) return 0;

	if (response.length)
	{
		//the version is different, must update the page
		cachePage->Update(response.data,response.version,instanceId);
	}

	if (command->data) free(command->data);
	command->data =(unsigned char *)malloc(cachePage->length);
	cachePage->Read(command->data);
	command->version=cachePage->version;
	
	return 1;

}

int NetworkMemory::UpdatePage(NetMemCommand * command)
{
	NetMemCommand response;

	if (!command) return 0;
	if (command->offset>pages.size()) return 0;
	
	MemoryPage * cachePage = pages[command->offset];
	command->type = UPDATE_PAGE;
	command->length = cachePage->length;
	SendCommand(command);
	
	//REFACTOR to set command->type to an error code for every case
	if (!ReadCommand(&response)) return 0;
	if (response.type!=UPDATE_PAGE) return 0;
	if (response.offset>pages.size()) return 0;
	
	cachePage->Update(command->data,response.version,instanceId);
	return 1;

}

int NetworkMemory::UnlockPage(ClientMemoryPage * page)
{
	NetMemCommand response;
	NetMemCommand command;

	if (!page) return 0;
	
	//fill the command with the data
	command.type = UNLOCK_PAGE;
	command.offset=page->offset;
	command.length=page->length;
	command.version=page->version;
	command.data = (unsigned char *)malloc(page->length);
	memcpy(command.data, page->data,page->length);

	SendCommand(&command);

	//the corresponding cache page memory
	MemoryPage * cachePage = pages[page->offset];

	//REFACTOR to set command->type to an error code for every case
	if (!ReadCommand(&response)) return 0;
	if (response.type!=UNLOCK_PAGE) return 0;
	if (response.offset>pages.size()) return 0;

	cachePage->Update(page->data,page->version,instanceId);
	delete page;
	return 1;
}

int NetworkMemory::InitPages()
{
	NetMemCommand response;
	if (!GetParams(&response)) return 0;
	for (int i=0;i<response.offset;i++)
	{
		//0 version means uninitialized - must be initialized at first READ or LOCK
		// WARN - response.version contains the length of the page!!!!
		// because if response.length is not zero that means more bytes is comming - sea ReadCommand method
		pages.push_back(new MemoryPage(response.version,0));
	}
	return 1;
}

long NetworkMemory::GetServerVersion()
{
	NetMemCommand command;
	command.type = GET_VERSION;
	SendCommand(&command);
	ReadCommand(&command);
	return command.version;
}

int NetworkMemory::SendCommand(NetMemCommand * command)
{
	int res;
	char *message;
	
	if (command->type == UNLOCK_PAGE || command->type == UPDATE_PAGE)
	{
		message = (char *)malloc(SIZEOF_NETMEM_COMMAND+command->length);
	}
	else
	{
		message = (char *)malloc(SIZEOF_NETMEM_COMMAND);
	}
	
	memcpy(message,(char *)&command->type,sizeof(char));

	int tmp=htonl(command->offset);
	memcpy(message+1,(char *)&tmp,sizeof(int));

	tmp=htonl(command->length);
	memcpy(message+5,(char *)&tmp,sizeof(int));

	tmp=htonl(command->version);
	memcpy(message+9,(char *)&tmp,sizeof(int));
	
	if (command->type == UNLOCK_PAGE || command->type == UPDATE_PAGE)
	{
		memcpy(message+13, (char *)command->data,command->length);
		res = send(connectSocket, message, SIZEOF_NETMEM_COMMAND+command->length, 0);
		if (res == SOCKET_ERROR)
		{
			free(message);
			throw SERVER_DISCONNECTED;
			return 0;
		}
	}
	else
	{
		res = send(connectSocket, message, SIZEOF_NETMEM_COMMAND, 0);
		if (res == SOCKET_ERROR)
		{
			free(message);
			throw SERVER_DISCONNECTED;
			return 0;
		}
	}

	free(message);
	return 1;
}

int NetworkMemory::ReadBytes(unsigned char * bytes, int length)
{
	char message[MAX_MSG];
	int size;
	int maxSize = (length>MAX_MSG)?MAX_MSG:length;
	int bytesRead=0;
	while(bytesRead<length)
	{
		size=recv(connectSocket, message, maxSize, 0);
		if (size<=0)
		{
			throw SERVER_DISCONNECTED;
			return 0;
		}
		memcpy(bytes+bytesRead,message,size);
		bytesRead+=size;
		maxSize = (length-bytesRead>MAX_MSG)?MAX_MSG:length-bytesRead;
	}
	return 1;
}

void NetworkMemory::CloseConnection()
{
	closesocket(connectSocket);
}

int NetworkMemory::ReadCommand(NetMemCommand * response)
{
	unsigned char charCommand[SIZEOF_NETMEM_COMMAND];
	if (!ReadBytes(charCommand,SIZEOF_NETMEM_COMMAND))
		return 0;

	response->type=charCommand[0];
	response->offset = ntohl(*(unsigned long*)(charCommand+1));
	response->length = ntohl(*(unsigned long*)(charCommand+5));
	response->version = ntohl(*(unsigned long*)(charCommand+9));

	//after response there is other data - for instance the page data  
	if (response->length)
	{
		response->data = (unsigned char *)malloc(response->length);
		ReadBytes(response->data,response->length);
	}
	return 1;
}

