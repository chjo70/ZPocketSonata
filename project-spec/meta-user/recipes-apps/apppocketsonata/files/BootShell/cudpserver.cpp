
#include "pch.h"

#include <stdio.h>
#include <malloc.h>
#include <errno.h>

#ifdef __linux__
#include <arpa/inet.h>
#elif __VXWORKS__
#include <sys/select.h>

#endif

#include "cudpserver.h"

/**
 * @brief CUDPServer::CUDPServer
 * @param iKeyId
 * @param pClassName
 * @param iPort
 */
CUDPServer::CUDPServer( int iPort )
{
    m_iPort = iPort;

    Init();

    Alloc();
}


/**
 * @brief CMultiServer::~CMultiServer
 */
CUDPServer::~CUDPServer()
{
    printf( "객체를 종료 처리 합니다..." );

    Free();
}

/**
 * @brief CUDPServer::Init
 */
void CUDPServer::Init()
{


}

/**
 * @brief CUDPServer::Alloc
 */
void CUDPServer::Alloc()
{
    //m_pszLanData = ( char * ) malloc( sizeof(char) * MAX_MSG );

}

/**
 * @brief CMultiServer::Free
 */
void CUDPServer::Free()
{

    //free( m_pszLanData );

}

/**
 * @brief     Run
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2023-05-24, 22:06
 * @warning
 */
void CUDPServer::Run()
{
    int i;
    int opt = true, addrlen, iActivity, iRead;
    int iMasterSocket, iMaxSocket, iNewSocket;
    int iSocket;

    struct sockaddr_in sockAddress;

    struct timeval stTimeOut;

    int iClientSocket[MAX_CLIENTS];

    fd_set readfds;

    char szMessage[MAX_MSG];

    stTimeOut.tv_sec = 10;
    stTimeOut.tv_usec = 0;

    printf( "\n[서버] 소켓을 설정 합니다..." );

    //initialise all client_socket[] to 0 so not checked 
    for( i = 0; i < MAX_CLIENTS; i++ ) {
        iClientSocket[i] = 0;
    }

    //create a master socket
    if( ( iMasterSocket = socket( AF_INET, SOCK_STREAM, 0 ) ) == 0 ) {
        perror( "Master Socket 실패" );
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if( setsockopt(iMasterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 ) {
        perror( "Master Socket 소켓 옵션");
    }

    //type of socket created
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_addr.s_addr = INADDR_ANY;
    sockAddress.sin_port = htons( m_iPort );

    if( bind( iMasterSocket, (struct sockaddr *)&sockAddress, sizeof(sockAddress)) < 0 ) {
        perror( "Bind 실패");
    }
    printf( " Listener on port %d\n", m_iPort );

    //try to specify maximum of 3 pending connections for the master socket
    if( listen( iMasterSocket, 3 ) < 0 ) {
        perror( "Listen 실패" );
    }

    //accept the incoming connection
    addrlen = sizeof(sockAddress);
    puts( " Waiting for connections ..." );

    while( true ) {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET( iMasterSocket, &readfds);
        iMaxSocket = iMasterSocket;

        //add child sockets to set
        for( i = 0; i < MAX_CLIENTS; i++ ) {
            //socket descriptor 
            iSocket = iClientSocket[i];

            //if valid socket descriptor then add to read list 
            if( iSocket > 0 ) {
                FD_SET( iSocket, &readfds );
            }

            //highest file descriptor number, need it for the select function 
            if( iSocket > iMaxSocket ) {
                iMaxSocket = iSocket;
            }
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        iActivity = select( iMaxSocket + 1 , &readfds , NULL , NULL , &stTimeOut );

        if ((iActivity < 0) && (errno!=EINTR) ) {
            perror( "select 에러" );

        }
        else if( iActivity == 0 ) {
            printf( "\n timeout..." );
            break;
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(iMasterSocket, &readfds)) {
            if ((iNewSocket = accept(iMasterSocket, (struct sockaddr *)&sockAddress, (socklen_t*)&addrlen)) < 0 ) {
                perror( "Accept 실패" );
                break;
            }
            else {

                printf( "\n연결 성공: ip %s , port %d" , inet_ntoa(sockAddress.sin_addr) , ntohs(sockAddress.sin_port));

                //add new socket to array of sockets 
                for( i = 0; i < MAX_CLIENTS ; i++ ) {
                    //if position is empty 
                    if( iClientSocket[i] == 0 )
                    {
                        iClientSocket[i] = iNewSocket;
                        break;
                    }
                }
            }
        }

        for( i = 0; i < MAX_CLIENTS; i++ ) {
            iSocket = iClientSocket[i];
            if (FD_ISSET( iSocket , &readfds)) {
                iRead = ReadBytes( iSocket, szMessage, 5 );
                printf( "\n reading..." );
            }
        }

    }
     

}

    /**
 * @brief     ReadBytes
 * @param     unsigned char * pchData
 * @param     int length
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2023-05-24, 21:38
 * @warning
 */
    int CUDPServer::ReadBytes( int iSocket, char *pchData, int length )
    {
        char message[MAX_MSG];

        int size;
        int maxSize = ( length > MAX_MSG ) ? MAX_MSG : length;
        int bytesRead = 0;

        while( bytesRead < length )
        {
            size = recv( iSocket, message, maxSize, 0 );
            if( size <= 0 ) {
                //throw CLIENT_DISCONNECTED;
            }
            else {
                memcpy( pchData + bytesRead, message, size );
                bytesRead += size;
                maxSize = ( length - bytesRead > MAX_MSG ) ? MAX_MSG : length - bytesRead;
            }
        }
        return 1;
    }



/**
 * @brief CMySocket::CloseSocket
 * @param iSocket
 * @param pAddress
 * @param pClientSocket
 */
void CUDPServer::CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket )
{
    int addrlen;

    addrlen = sizeof(sockaddr_in);
    //Somebody disconnected , get his details and print
    getpeername(iSocket , (struct sockaddr*) pAddress , (socklen_t*)&addrlen);
    printf( "\n연결 단절: ip %s , port %d" , inet_ntoa(pAddress->sin_addr) , ntohs(pAddress->sin_port));

    //Close the socket and mark as 0 in list for reuse
    closesocket( iSocket );

    if( pClientSocket != NULL ) {
        *pClientSocket = 0;
    }

}

