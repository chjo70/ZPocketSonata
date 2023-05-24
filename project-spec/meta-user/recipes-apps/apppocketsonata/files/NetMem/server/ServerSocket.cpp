/**

    @file      ServerSocket.cpp
    @brief
    @details   ~
    @author    조철희
    @date      16.04.2023
    @copyright ? Cool Guy, 2023. All right reserved.

**/

#include "pch.h"

#ifdef __VXWORKS__
#include <taskLib.h>

#endif


#include "../utils/PortableSocket.h"
#include "ServerSocket2.h"
#include "ClientSocket2.h"

#include <iostream>
#include <cstring>

#include "../../BootShell/BootShellMain.h"

using namespace std;


/**
 * @brief     ServerSocket
 * @param     int noPages
 * @param     int lenght
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-16 17:58:24
 * @warning
 */
ServerSocket::ServerSocket(int noPages, int lenght)
{
    m_bThreadLoop = true;

	//threadSocket = NULL;
#ifdef _MSC_VER
    m_hThread = 0;
    m_pThreadFunc = ServerSocket::EntryPoint;
#else
    m_iPriority = 200;

#endif

	this->noPages=noPages;
	this->lengthPage=lenght;
	InitPages();
}

/**
 * @brief     InitPages
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-16 17:58:25
 * @warning
 */
int ServerSocket::InitPages()
{
	for (int i=0;i<noPages;i++)
	{
		pages.push_back(new MemoryPage(lengthPage,1));
	}
	return 1;
}

/**
 * @brief     ~ServerSocket
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-16 17:58:27
 * @warning
 */
ServerSocket::~ServerSocket()
{
    m_bThreadLoop = false;

	//if (threadSocket) delete(threadSocket);
#ifdef _MSC_VER
    if( m_hThread ) {
        
        Sleep( 1 );
        TerminateThread( m_hThread, 0 ); //DWORD(-1));
    }

#elif defined(__VXWORKS__)
#else
#endif

	for (int i=0;i<noPages;i++)
	{
		delete (pages[i]);
	}
}

/**
 * @brief     CleanUpClient
 * @param     int & clientId
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-16 17:52:37
 * @warning
 */
void ServerSocket::CleanUpClient(int &clientId)
{
	for (int i=0;i<noPages;i++)
	{
		pages[i]->Unlock(0,clientId);
	}
}

/**
 * @brief     operator()
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-16 17:52:40
 * @warning
 */
void ServerSocket::RunServerSocket()
{
	static int clientIds=0;
	int connectSocket;
	unsigned short int listenPort;
	socklen_t clientAddressLength;
	struct sockaddr_in clientAddress, serverAddress;

	listenPort = m_iPort;

 	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
 	if (listenSocket < 0)
	{
    	cerr << "cannot create listen socket";
        //i = WSAGetLastError();
        //printf( "\n Error : %d ", WSAGetLastError() );
    	return;
 	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(listenPort);

	if (bind(listenSocket,(struct sockaddr *) &serverAddress,sizeof(serverAddress)) < 0)
	{
    	printf( "\n 스켓을 바인드 할 수 없습니다..." );
    	return;
	}

	listen(listenSocket, 5);

	while ( m_bThreadLoop ) {
		{
			//boost::lock_guard<boost::mutex> lock(mutex);
            printf( "\n 포트[%d]에 접속 대기를 합니다.", listenPort );
		}

		clientAddressLength = sizeof(clientAddress);
		connectSocket = accept(listenSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
		if (connectSocket < 0)
		{
            printf( "\n 접속을 닫습니다." );
			return;
		}

		{
			//boost::lock_guard<boost::mutex> lock(mutex);
			// cout << "  connected to " << inet_ntoa(clientAddress.sin_addr);
            printf( "\n 컴퓨터[%s:%d]에 연결 성공합니다." , inet_ntoa( clientAddress.sin_addr ), ntohs( clientAddress.sin_port ) );
			// cout << ":" << ntohs(clientAddress.sin_port) << "\n";
		}

		ClientSocket * cs = new ClientSocket(clientIds++,connectSocket,this);
		cs->StartThreadSocket();
	}

}


/**
 * @brief     StartThreadSocket
 * @param     int port
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-16 17:57:21
 * @warning
 */
int ServerSocket::StartThreadSocket(int port)
{
	this->m_iPort=port;

    //if (threadSocket) delete(threadSocket);
#ifdef _MSC_VER
    if( m_hThread ) {
        TerminateThread( m_hThread, 0 ); //DWORD(-1));
    }

#elif defined(__VXWORKS__)
	taskDelete( m_TaskID );

#else
#endif

	// threadSocket = new boost::thread (boost::ref(*this));
#ifdef _MSC_VER
    m_hThread = CreateThread( NULL, 0, m_pThreadFunc, this, 0, & m_dwTID );

#elif defined(__VXWORKS__)
	//m_TaskID = taskSpawn( "tServerSocket", tSERVER_SOCKET, VX_STDIO | VX_SUPERVISOR_MODE, 64000, ( FUNCPTR ) this->Run, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 );

#endif

	return 1;
}

/**
 * @brief     StopSocket
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-16 17:54:29
 * @warning
 */
int ServerSocket::StopSocket()
{
	closesocket(listenSocket);
	return 0;
}

/**
 * @brief     Join
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-16 17:55:58
 * @warning
 */
void ServerSocket::Join()
{
	//if (threadSocket) threadSocket->join();
}


/**
 * @brief     Run
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 15:08:01
 * @warning
 */
void ServerSocket::Run()
{
    RunServerSocket();

}
