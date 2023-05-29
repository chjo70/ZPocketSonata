
#include "pch.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>


#ifdef __linux__
#include <arpa/inet.h>

#elif __VXWORKS__
#include <taskLib.h>
#include <ioLib.h>
#include <arpa/inet.h>
#include <sys/select.h>

#elif _MSC_VER
#include <io.h>
#include <winsock.h>
#include <ws2tcpip.h>

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

    // 체크 서버/클라이언트 포트 번호 할당
    m_iCheckServerPort = m_iPort + 1;

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
    int opt = true, addresslen, iActivity, iRead, stdInFd;
    int iMasterSocket;

    char cChar;

    struct sockaddr_in sockAddress, clienAddress;

    struct timeval stTimeOut;

    fd_set readfds, writefds, original_socket;

    char szReceiveMessage[MAX_MSG];

    stTimeOut.tv_sec = 5;
    stTimeOut.tv_usec = 0;

    printf( "\n[서버] 소켓을 설정 합니다..." );

    stdInFd = SaveStdInOption();

    //create a master socket
    if( ( iMasterSocket = socket( AF_INET, SOCK_DGRAM, 0 ) ) <= 0 ) {
#ifdef _MFC_VER
        int errorCode = WSAGetLastError();
#endif
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
    if( setsockopt( iMasterSocket, SOL_SOCKET, SO_KEEPALIVE, ( const char * ) &opt, sizeof( opt ) ) < 0 ) {
        perror( "소켓 옵션(SO_KEEPALIVE)" );
    }
    else {
#ifdef _MSC_VER
        int optionVal;

        optionVal = 60;
        setsockopt( iMasterSocket, IPPROTO_UDP, TCP_KEEPCNT, ( const char * ) &optionVal, sizeof( optionVal ) );

        optionVal = 5;
        setsockopt( iMasterSocket, IPPROTO_UDP, TCP_KEEPIDLE, ( const char * ) &optionVal, sizeof( optionVal ) );

        optionVal = 5;
        setsockopt( iMasterSocket, IPPROTO_UDP, TCP_KEEPINTVL, ( const char * ) &optionVal, sizeof( optionVal ) );
#endif

    }


    printf( "\n 포트[%d]에서 대기하고 있습니다...", m_iPort );

    //accept the incoming connection
    addresslen = sizeof(sockAddress);
    puts( " Waiting for connections ..." );

    while( true ) {
        //clear the socket set
        FD_ZERO( &original_socket );

        FD_ZERO( & readfds );
        FD_ZERO( & writefds );

#ifdef _MSC_VER
#else
        FD_SET( stdInFd, &readfds );
#endif

        FD_SET( iMasterSocket, &readfds);
        FD_SET( iMasterSocket, &writefds );

        iActivity = select( iMasterSocket + 1 , &readfds , NULL, NULL , &stTimeOut );

        if ((iActivity < 0) && (errno!=EINTR) ) {
            perror( "select 에러" );

        }
        else if( iActivity == 0 ) {
            printf( "\n timeout..." );
            // break;
        }

        // 포트에서 수신되는 메시지 처리
        if( FD_ISSET( iMasterSocket, &readfds ) ) {
            char buffer[100];

            FD_CLR( iMasterSocket, &readfds );
            iRead = recvfrom( iMasterSocket, szReceiveMessage, MAX_MSG, 0, ( struct sockaddr * ) & clienAddress, & addresslen );
            inet_ntop( AF_INET, &clienAddress.sin_addr, buffer, sizeof( buffer ) );
            printf( "\n read data...from[%s]", buffer );

        }
//         else if( FD_ISSET( iMasterSocket, &writefds ) ) {
//             printf( "\n writefds..." );
//         }
        else if( FD_ISSET( stdInFd, &readfds ) ) {
            printf( "\n readfds..." );
#ifdef _MSC_VER
            _read( stdInFd, &cChar, 1 );           /* read the key just hit */
#else
            read( stdInFd, &cChar, 1 );           /* read the key just hit */
#endif
        }
        else {

        }

    }

    ReStoreStdInOption();

}

/**
 * @brief     SaveStdInOption
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-27 17:22:25
 * @warning
 */
int CUDPServer::SaveStdInOption()
{
    int stdInFd;

#ifdef __VXWORKS__
    int tShell_priority;

    taskPriorityGet( 0, & tShell_priority );

    stdInFd = ioTaskStdGet( taskNameToId( ( char * ) "tShell0" ), 0 );

    /* Save options */
    m_iStdinOption = ioctl( stdInFd, FIOGETOPTIONS, 0 ); /* current console */

    // printf( "\n save_options[%x], new_option[%x]" , save_options, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );
    ioctl( stdInFd, FIOSETOPTIONS, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );

#else
    stdInFd = _fileno( stdin );

#endif

    return stdInFd;

}

/**
 * @brief     ReStoreStdInOption
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-27 17:22:24
 * @warning
 */
void CUDPServer::ReStoreStdInOption()
{
#ifdef __VXWORKS__
    /* Leave raw mode */
    ioctl( stdInFd, FIOSETOPTIONS, m_iStdinOption );
    ioctl( stdInFd, FIOFLUSH, 0 );

#endif

}

/**
 * @brief     CreateServer
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-27 17:27:09
 * @warning
 */
bool CUDPServer::CreateServer( int iPort )
{
    bool bRet = true;
    struct sockaddr_in sockAddress;

    int opt = 1;
    try {
        if( ( m_iServerSocket = socket( AF_INET, SOCK_DGRAM, 0 ) ) <= 0 ) {
#ifdef _MFC_VER
            int errorCode = WSAGetLastError();
#endif
            throw ENUM_ERROF_OF_SOCKET;
        }

        //set master socket to allow multiple connections ,
        //this is just a good habit, it will work without this
        if( setsockopt( m_iServerSocket, SOL_SOCKET, SO_REUSEADDR, ( char * ) &opt, sizeof( opt ) ) < 0 ) {
            throw ENUM_ERROF_OF_SOCKETOPT;
        }

        //type of socket created
        sockAddress.sin_family = AF_INET;
        sockAddress.sin_addr.s_addr = INADDR_ANY;
        sockAddress.sin_port = htons( iPort );

        if( bind( m_iServerSocket, ( struct sockaddr * ) &sockAddress, sizeof( sockAddress ) ) < 0 ) {
            throw ENUM_ERROF_OF_BIND;
        }
#if 0
        if( setsockopt( m_iServerSocket, SOL_SOCKET, SO_KEEPALIVE, ( const char * ) &opt, sizeof( opt ) ) < 0 ) {
            throw ENUM_ERROF_OF_SOCKETOPT;
        }
        else {
#ifdef _MSC_VER
            int optionVal;

            optionVal = 60;
            if( setsockopt( m_iServerSocket, IPPROTO_UDP, TCP_KEEPCNT, ( const char * ) &optionVal, sizeof( optionVal ) ) < 0 ) {
                throw ENUM_ERROF_OF_SOCKETOPT;
            }

            optionVal = 5;
            if( setsockopt( m_iServerSocket, IPPROTO_UDP, TCP_KEEPIDLE, ( const char * ) &optionVal, sizeof( optionVal ) ) < 0 ) {
                throw ENUM_ERROF_OF_SOCKETOPT;
            }

            optionVal = 5;
            if( setsockopt( m_iServerSocket, IPPROTO_UDP, TCP_KEEPINTVL, ( const char * ) &optionVal, sizeof( optionVal ) ) < 0 ) {
                throw ENUM_ERROF_OF_SOCKETOPT;
            }
#endif
        }

#endif

    }
    catch( ENUM_SOCKET_ERROR enSocketError ) {
        bRet = false;
        printf( "\n CreateServer() 에러 코드[%d]가 발생했습니다.", enSocketError );
    }

    return true;

}

/**
 * @brief     CheckServer
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-27 17:32:08
 * @warning
 */
void CUDPServer::CheckServer()
{
    int iAddresslen, iActivity, iRead;

    struct sockaddr_in sockAddress, clienAddress;

    struct timeval stTimeOut;

    fd_set readfds;

    char szReceiveMessage[MAX_MSG], szSendMessage[MAX_MSG];

    stTimeOut.tv_sec = CHECK_SERVER_TIME;
    stTimeOut.tv_usec = 0;

    printf( "\n[서버] 소켓을 설정 합니다..." );

    sprintf( szSendMessage, "OK" );

    if( true == CreateServer( m_iCheckServerPort ) ) {
        printf( "\n 포트[%d]에서 대기하고 있습니다...", m_iCheckServerPort );

        iAddresslen = sizeof( sockAddress );
        puts( " Waiting for connections ..." );

        while( true ) {
            FD_ZERO( & readfds );

            FD_SET( m_iServerSocket, &readfds );

            iActivity = select( m_iServerSocket + 1, &readfds, NULL, NULL, &stTimeOut );

            if( ( iActivity < 0 ) && ( errno != EINTR ) ) {
                perror( "select 에러" );
                break;
            }
            else if( iActivity == 0 ) {
                printf( "\n timeout..." );
                break;
            }

            // 포트에서 수신되는 메시지 처리
            if( FD_ISSET( m_iServerSocket, &readfds ) ) {
                char buffer[100];

                FD_CLR( m_iServerSocket, &readfds );
                iRead = recvfrom( m_iServerSocket, szReceiveMessage, MAX_MSG, 0, ( struct sockaddr * ) & clienAddress, & iAddresslen );
                inet_ntop( AF_INET, &clienAddress.sin_addr, buffer, sizeof( buffer ) );
                printf( "\n read data from[%s]", buffer );

                sendto( m_iServerSocket, szSendMessage, strlen( szSendMessage ), 0, ( struct sockaddr * ) & clienAddress, sizeof( struct sockaddr ) );
            }
        }
    }
    else {
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
    getpeername(iSocket , (struct sockaddr*) pAddress , (int *)&addrlen);
    printf( "\n연결 단절: ip %s , port %d" , inet_ntoa(pAddress->sin_addr) , ntohs(pAddress->sin_port));

    //Close the socket and mark as 0 in list for reuse
#ifdef _MSC_VER
    closesocket( iSocket );

#else
    close( iSocket );

#endif


    if( pClientSocket != NULL ) {
        *pClientSocket = 0;
    }

}

