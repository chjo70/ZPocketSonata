/**

    @file      ClientSocket.cpp
    @brief
    @details   ~
    @author    조철희
    @date      16.04.2023

**/


#include "pch.h"

#ifdef __VXWORKS__
#include <taskLib.h>

#endif

#include "../../BootShell/BootShellMain.h"

#include "../utils/PortableSocket.h"
#include "ClientSocket2.h"
//#include "../../tests/testing/BlockTrace.h"

#include <iostream>
#include <cstring>

//#include "boost/ref.hpp"
//#include "boost/bind.hpp"
//#include "boost/function.hpp"

using namespace std;

#define MAX_MSG 20000

static void Run();

/**
 * @brief     ClientSocket
 * @param     int id
 * @param     int socket
 * @param     ServerSocket * server
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-17 11:23:58
 * @warning
 */
ClientSocket::ClientSocket(int id, int socket,ServerSocket *server)
{
	connectSocket = socket;
	//threadSocket = NULL;

#ifdef _MSC_VER
    m_hThread = 0;
    m_pThreadFunc = ClientSocket::EntryPoint;
#else

#endif

	this->server = server;
	this->id = id;

	response_m.data = (unsigned char *) malloc(server->lengthPage);
	command_m.data= (unsigned char *) malloc(server->lengthPage);

}

/**
 * @brief     ~ClientSocket
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 15:09:22
 * @warning
 */
ClientSocket::~ClientSocket()
{
#ifdef _MSC_VER
    if( m_hThread ) {

        TerminateThread( m_hThread, 0 ); //DWORD(-1));
    }
#elif defined(__VXWORKS__)
	taskDelete( m_TaskID );

#else
#endif

	if (connectSocket)
	{
		closesocket(connectSocket);
	}

}

/**
 * @brief     RunServerSocket
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-17 11:25:44
 * @warning
 */
void ClientSocket::RunClientSocket( ClientSocket *pObject )
{
//	BlockTrace trace("ClientSocket::operator()", this->id);
	while ( true ) {
		try
		{
            pObject->ReadCommand(&pObject->command_m);
            pObject->ExecuteCommand(&pObject->command_m);
		}
		catch(int err)
		{
			//REFACTOR make an int to string error code function
			cout<<GetErrorMessage(err)<<"\n";
			break;
		}
	}

	// boost::thread t (boost::bind(&ClientSocket::Destroy, boost::ref(*this)));
}

/**
 * @brief     Destroy
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 15:09:30
 * @warning
 */
void ClientSocket::Destroy()
{
	{
		//boost::lock_guard<boost::mutex> lock(mutex);
//		BlockTrace trace("ClientSocket::Destroy", this->id);
		server->CleanUpClient(id);
		//threadSocket->join();
	}
	delete this;
}

/**
 * @brief     ReadCommand
 * @param     NetMemCommand * command
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 15:09:33
 * @warning
 */
int ClientSocket::ReadCommand(NetMemCommand *command)
{
//	BlockTrace trace("ClientSocket::ReadCommand", this->id);
	unsigned char charCommand[SIZEOF_NETMEM_COMMAND];
	ReadBytes(charCommand,SIZEOF_NETMEM_COMMAND);

	command->type=charCommand[0];
	command->offset = ntohl(*(unsigned long*)(charCommand+1));
	command->length = ntohl(*(unsigned long*)(charCommand+5));
	command->version = ntohl(*(unsigned long*)(charCommand+9));

	if (command->type == UNLOCK_PAGE || command->type == UPDATE_PAGE)
	{
		ReadBytes(command->data,command->length);
	}
	return 1;
}

/**
 * @brief     ReadBytes
 * @param     unsigned char * bytes
 * @param     int length
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 15:09:35
 * @warning
 */
int ClientSocket::ReadBytes(unsigned char * bytes, int length)
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
			//throw CLIENT_DISCONNECTED;
		}
		else
		{
			memcpy(bytes+bytesRead,message,size);
			bytesRead+=size;
			maxSize = (length-bytesRead>MAX_MSG)?MAX_MSG:length-bytesRead;
		}
	}
	return 1;
}

/**
 * @brief     ExecuteCommand
 * @param     NetMemCommand * command
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 15:09:38
 * @warning
 */
int ClientSocket::ExecuteCommand(NetMemCommand *command)
{
//	BlockTrace trace("ClientSocket::ExecuteCommand", this->id);
	MemoryPage * currentPage;

	response_m.type = command->type;
	response_m.length=0;

	int res;

	switch(command->type)
	{
	case GET_VERSION:
		response_m.version=(NET_MEM_SERVER_MAJOR_VERSION<<8)+NET_MEM_SERVER_MINOR_VERSION+
							(API_NET_MEM_MAJOR_VERSION<<24)+(API_NET_MEM_MINOR_VERSION<<16);
		break;
	case GET_PARAMS:
		response_m.offset=server->noPages;
		response_m.version=server->lengthPage;
		break;
	case READ_PAGE:
		if (command->offset > server->pages.size())
		{
			response_m.type = NO_SUCH_PAGE;
			break;
		}
		currentPage = server->pages[command->offset];

		response_m.offset=command->offset;

		//REFACTOR version read in a synchronized way in the Read method of the MemoryPage maybe
		response_m.version=currentPage->version;

		if (currentPage->version == command->version) break;

		response_m.length=currentPage->length;
		currentPage->Read(response_m.data);
		break;

	case LOCK_PAGE:
		if (command->offset > server->pages.size())
		{
			response_m.type = NO_SUCH_PAGE;
			break;
		}
		currentPage = server->pages[command->offset];

		currentPage->Lock(this->id);

		response_m.offset=command->offset;

		response_m.version=currentPage->version;
		if (currentPage->version == command->version) break;

		response_m.length=currentPage->length;
		memcpy(response_m.data, currentPage->data, currentPage->length);
		break;
	case UNLOCK_PAGE:
		if (command->offset > server->pages.size())
		{
			response_m.type = NO_SUCH_PAGE;
			break;
		}

		currentPage = server->pages[command->offset];

		response_m.offset=command->offset;
		res = currentPage->Unlock(command->data,this->id);

		if (res<0)
		{
			response_m.type = PAGE_NOT_LOCKED;
		}
		response_m.version=res;
		break;
	case UPDATE_PAGE:
		if (command->offset > server->pages.size())
		{
			response_m.type = NO_SUCH_PAGE;
			break;
		}

		currentPage = server->pages[command->offset];

		response_m.offset=command->offset;

		res = currentPage->Update(command->data,command->version,this->id);
		response_m.version=res;
		break;
	}
	return SendCommand(&response_m);
}


/**
 * @brief     SendCommand
 * @param     NetMemCommand * command
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 15:09:43
 * @warning
 */
int ClientSocket::SendCommand(NetMemCommand * command)
{
	int res;
	char *message;

	if (command->length > 0)
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

	if (command->length >0)
	{
		memcpy(message+13, (char *)command->data,command->length);
		res = send(connectSocket, message, SIZEOF_NETMEM_COMMAND+command->length, 0);
		if (res == SOCKET_ERROR)
		{
			free(message);
			//throw CLIENT_DISCONNECTED;
			return 0;
		}
	}
	else
	{
		res = send(connectSocket, message, SIZEOF_NETMEM_COMMAND, 0);
		if (res == SOCKET_ERROR)
		{
			free(message);
			//throw CLIENT_DISCONNECTED;
			return 0;
		}
	}
	free(message);
	return 1;
}

/**
 * @brief     StartThreadSocket
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 15:09:46
 * @warning
 */
int ClientSocket::StartThreadSocket()
{
	//boost::lock_guard<boost::mutex> lock(mutex);

    //BlockTrace trace("ClientSocket::StartThreadSocket", this->id);
	//if (threadSocket) return 0;
	//threadSocket = new boost::thread (boost::ref(*this));

#ifdef _MSC_VER
    m_hThread = CreateThread( NULL, 0, m_pThreadFunc, this, 0, & m_dwTID );

#elif defined(__VXWORKS__)
    //taskSpawn( "tClientSocket", tCLIENT_SOCKET, VX_STDIO | VX_SUPERVISOR_MODE, 64000, ( FUNCPTR ) ClientSocket::RunClientSocket, (int) this, 0, 0, 0, 0, 0, 0, 0, 0, 0 );

#endif


	return 1;
}

/**
 * @brief     Join
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 15:07:13
 * @warning
 */
void ClientSocket::Join()
{
	//if (threadSocket) threadSocket->join();
}

/**
 * @brief     Run
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 15:07:12
 * @warning
 */
void ClientSocket::Run()
{
    RunClientSocket( this );

}
