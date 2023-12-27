/**

    @file      cudpserver.cpp
    @brief
    @details   ~
    @author    조철희
    @date      31.05.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

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

#elif defined(_MSC_VER)
#include <io.h>
#include <winsock.h>
#include <ws2tcpip.h>


#endif

#include "cudpserver.h"

#include "../System/csysconfig.h"


extern CSysConfig *g_pTheSysConfig;

/**
 * @brief CUDPServer::CUDPServer
 * @param iKeyId
 * @param pClassName
 * @param iPort
 */
CUDPServer::CUDPServer( char *szIPAddress, int iPort )
{
    //
    strcpy( m_szIPAddress, szIPAddress );

    m_iPort = iPort++;

    // 체크 서버/클라이언트 포트 번호 할당
    m_iServerPort = iPort++;
    m_iClientPort = iPort++;
    m_iCheckServerPort = iPort++;

    m_bGetKey = true;

    printf( "\n UDP서버 포트[%s:%d]에서 대기하고 있습니다...", szIPAddress, m_iServerPort );

#ifdef __VXWORKS__
    m_tThread = taskSpawn( (char *) "tUDPServer", tUDP_SERVER, VX_STDIO | VX_SUPERVISOR_MODE | VX_FP_TASK | VX_ALTIVEC_TASK, 64000, ( FUNCPTR ) ThreadRoutine, (_Vx_usr_arg_t) this, 0, 0, 0, 0, 0, 0, 0, 0, 0 );

#elif _MSC_VER
    m_tThread = thread( ThreadRoutine, this );

    // m_tThread.join();
#endif

    Init();

    Alloc();

}

/**
 * @brief     ~CUDPServer
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-31 10:00:40
 * @warning
 */
CUDPServer::~CUDPServer()
{

    printf( "\n[CUDPServer]객체를 종료 처리 합니다..." );

#ifdef __VXWORKS__
    printf( "\ntUDPServer를 종료합니다." );
    taskDelete( m_tThread );

#elif _MSC_VER
    printf( "\ntUDPServer를 종료합니다." );
    m_tThread.detach();

#endif

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
void CUDPServer::RunServer()
{
#ifdef __VXWORKS__
    int opt = true, /* addresslen, */ iActivity, iRead, stdInFd;
    socklen_t addresslen;

#else
    int opt = true, addresslen, iActivity, iRead, stdInFd;

#endif

    char cChar;

    struct sockaddr_in sockAddress, clientAddress;

    struct timeval stTimeOut;

    fd_set readfds;

    char szReceiveMessage[MAX_MSG];

    // 수신 명령어 또는 키보드 저장소 클리어
    m_szMessage[0] = 0;

#ifdef _MSC_VER
    stTimeOut.tv_sec = 5000;
#else
    stTimeOut.tv_sec = 3;
#endif
    stTimeOut.tv_usec = 0;

    // stdout input key 얻기
    stdInFd = SaveStdInOption();

    CreateServer( m_iServerPort );

    // printf( "\n UDP서버 포트[%d/%d]에서 대기하고 있습니다...", m_iServerPort, stdInFd );

    addresslen = sizeof(sockAddress);

    while( true ) {
        FD_ZERO( & readfds );

        if( m_bGetKey == true ) {
#ifdef _MSC_VER
            // FD_SET( stdInFd, &readfds );
#else
            FD_SET( stdInFd, &readfds );
#endif
        }

        FD_SET( m_iServerSocket, &readfds);

#ifdef _MSC_VER
#else
        ioctl( stdInFd, FIORFLUSH, 0 );
#endif

        iActivity = select( (int)( m_iServerSocket + (SOCKET) 1 ) , &readfds , NULL, NULL , &stTimeOut );

        if ((iActivity < 0) && (errno!=EINTR) ) {
            ReStoreStdInOption( stdInFd );
            perror( "select 에러" );
            break;
        }
        else if( iActivity == 0 ) {
            ReStoreStdInOption( stdInFd );

            stTimeOut.tv_sec = 100000;

            // printf( "\n [클라이언트] 타임아웃...그리고 UDP 서버 종료..." );

            m_bGetKey = false;
            m_szMessage[0] = KEY_TIMEOUT;
        }

        // 포트에서 수신되는 메시지 처리
        if( FD_ISSET( m_iServerSocket, &readfds ) ) {
            char buffer[100];

            ReStoreStdInOption( stdInFd );

            FD_CLR( m_iServerSocket, &readfds );
            iRead = recvfrom( m_iServerSocket, szReceiveMessage, MAX_MSG, 0, ( struct sockaddr * ) & clientAddress, & addresslen );
            inet_ntop( AF_INET, &clientAddress.sin_addr, buffer, sizeof( buffer ) );
            printf( "\n read data...from[%s]", buffer );

            m_szMessage[0] = szReceiveMessage[0];

        }
        else if( FD_ISSET( stdInFd, &readfds ) ) {
#ifdef _MSC_VER
            _read( stdInFd, &cChar, 1 );
#else
            read( stdInFd, &cChar, 1 );
#endif
            printf( "\n readfds..." );

            ReStoreStdInOption( stdInFd );

            m_szMessage[0] = cChar;

            SendAllUDPServer();

            stTimeOut.tv_sec = 100000;

            m_bGetKey = false;
        }
        else {

        }

    }

    // ReStoreStdInOption( stdInFd );
#if 0
    while( true ) {
        printf( "\n Out of key..." );   WhereIs;
    }
#else
    // WhereIs;
    WhereIs;

#endif

    CloseSocket( m_iServerSocket );

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
//     int tShell_priority;
//     taskPriorityGet( 0, & tShell_priority );

    stdInFd = ioTaskStdGet( taskNameToId( ( char * ) "tShell0" ), 0 );

    /* Save options */
    m_iStdinOption = ioctl( stdInFd, FIOGETOPTIONS, 0 ); /* current console */

    // printf( "\n save_options[%x], new_option[%x]" , save_options, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );
    ioctl( stdInFd, FIOSETOPTIONS, OPT_TERMINAL & ~OPT_LINE & ~OPT_ECHO );

    m_ShellTaskID = taskNameToId( ( char * ) "tShell0" );
    if( TASK_ID_ERROR != m_ShellTaskID ) {
    	taskSuspend( m_ShellTaskID );
    }

    ioctl( stdInFd, FIORFLUSH, 0 );

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
void CUDPServer::ReStoreStdInOption( int stdInFd )
{
#ifdef __VXWORKS__
    ioctl( stdInFd, FIOSETOPTIONS, m_iStdinOption );
    ioctl( stdInFd, FIOFLUSH, 0 );

    if( TASK_ID_ERROR != m_ShellTaskID ) {
        taskResume( m_ShellTaskID );
    }

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
#ifdef _MSC_VER
            int errorCode = WSAGetLastError();
#endif
            bRet = false;
            //throw ENUM_ERROF_OF_SOCKET;
        }

        if( setsockopt( m_iServerSocket, SOL_SOCKET, SO_REUSEADDR, ( char * ) &opt, sizeof( opt ) ) < 0 ) {
            bRet = false;
            //throw ENUM_ERROF_OF_SOCKETOPT;
        }

        sockAddress.sin_family = AF_INET;
        sockAddress.sin_addr.s_addr = INADDR_ANY;
        sockAddress.sin_port = htons( iPort );

        if( bind( m_iServerSocket, ( struct sockaddr * ) &sockAddress, sizeof( sockAddress ) ) < 0 ) {
            bRet = false;
            //throw ENUM_ERROF_OF_BIND;
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
 * @brief     SendAllUDPServer
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-31 10:02:44
 * @warning
 */
void CUDPServer::SendAllUDPServer()
{
    int i, iRet;
    SOCKET iClientSocket;
    struct sockaddr_in clientAddress;

    char szInetAddress[100];

    iClientSocket = socket( AF_INET, SOCK_DGRAM, 0 );
#ifdef _MSC_VER
    ZeroMemory( & clientAddress, sizeof( clientAddress ) );

#else
    memset( & clientAddress, 0, sizeof( clientAddress ) );

#endif

    int iStart = g_pTheSysConfig->GetSBCFromIP();
    int iEnd = g_pTheSysConfig->GetSBCToIP();

    for( i=iStart ; i <= iEnd ; ++i ) {
#ifdef _MSC_VER
        sprintf( szInetAddress, "10.29.245.%d", 51 + 0 );
#else
        sprintf( szInetAddress, "192.168.0.%d", i );

#endif

        if( strcmp( m_szIPAddress, szInetAddress ) == 0 ) {
            continue;
        }
        else {
            clientAddress.sin_family = AF_INET;
            clientAddress.sin_addr.s_addr = inet_addr( szInetAddress );
            clientAddress.sin_port = htons( m_iClientPort );

            iRet = sendto( iClientSocket, m_szMessage, (int) strlen( m_szMessage ), 0, ( struct sockaddr * ) & clientAddress, sizeof( struct sockaddr ) );
            if( iRet > 0 ) {
                printf( "\n[%s:%d]에 메시지[%d]를 전송합니다.", szInetAddress, m_iClientPort, m_szMessage[0] );
            }
            else {
                printf( "*" );
            }
        }

    }

}

/**
 * @brief     CloseSocket
 * @param     int iSocket
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-04 14:51:15
 * @warning
 */
void CUDPServer::CloseSocket( SOCKET iSocket )
{
#ifdef _MSC_VER
    closesocket( iSocket );
#else

    shutdown( iSocket, SHUT_RDWR );
    close( iSocket );

#endif
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
#ifdef __VXWORKS__
	int /* iAddresslen, */ iActivity, iRead;
	socklen_t iAddresslen;
#else
    int iAddresslen, iActivity, iRead;

#endif

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

            iActivity = select( (int)( m_iServerSocket + (SOCKET) 1), &readfds, NULL, NULL, &stTimeOut );

            if( ( iActivity < 0 ) && ( errno != EINTR ) ) {
                perror( "select 에러" );
                break;
            }
            else if( iActivity == 0 ) {
                printf( "\n [서버] timeout..." );
                break;
            }

            // 포트에서 수신되는 메시지 처리
            if( FD_ISSET( m_iServerSocket, &readfds ) ) {
                char buffer[100];

                FD_CLR( m_iServerSocket, &readfds );
                iRead = recvfrom( m_iServerSocket, szReceiveMessage, MAX_MSG, 0, ( struct sockaddr * ) & clienAddress, & iAddresslen );
                inet_ntop( AF_INET, &clienAddress.sin_addr, buffer, sizeof( buffer ) );
                printf( "\n read data from[%s]", buffer );

                sendto( m_iServerSocket, szSendMessage, (int) strlen( szSendMessage ), 0, ( struct sockaddr * ) & clienAddress, sizeof( struct sockaddr ) );
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
#ifdef __VXWORKS__
    socklen_t addrlen;
#else
    int addrlen;
#endif


    addrlen = sizeof(sockaddr_in);
    //Somebody disconnected , get his details and print
#ifdef __VXWORKS__
    getpeername(iSocket , (struct sockaddr*) pAddress , &addrlen);
#else
    getpeername(iSocket , (struct sockaddr*) pAddress , (int *)&addrlen);
#endif

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

