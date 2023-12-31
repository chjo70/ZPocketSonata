/**

    @file      csingleclient.cpp
    @brief
    @details   ~
    @author    조철희
    @date      10.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "pch.h"


#ifdef _MSC_VER
#include "MSIGA.h"
#include "MSIGADlg.h"

#elif defined(__linux__)
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#elif defined(__VXWORKS__)
#include <arpa/inet.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#else
#include <unistd.h>

#endif

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include "csingleclient.h"

//#include "../Thread/creclan.h"
#include "../Thread/ctaskmngr.h"


#include "../Utils/ccommonutils.h"

#include "../Include/globals.h"

#ifdef _MSC_VER
#define USR_FD_SET(fd, set) do { \
u_int __i = 0; \
( ( fd_set FAR * )( set ) )->fd_array[__i] = ( fd ); \
( ( fd_set FAR * )( set ) )->fd_count++; \
} while( 0 )

#endif

bool CSingleClient::m_bDebugConnected = false;

/**
 * @brief     SendLan
 * @param     UINT uiOpCode
 * @param     void * pData
 * @param     UINT uiDataLength
 * @param     BOOL bSwap
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-11-05 19:15:02
 * @warning
 */
void SendLan( UINT uiOpCode, void *pData, size_t szDataLength, BOOL bSwap )
{

    g_pTheCCUSocket->SendLan( uiOpCode, pData, szDataLength, bSwap );
    if( g_pTheCCUDebugSocket != NULL ) {
        g_pTheCCUDebugSocket->SendLan( uiOpCode, pData, szDataLength, bSwap );
    }

}

/**
 * @brief     SendStringLan
 * @param     UINT uiOpCode
 * @param     const char * pData
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-11-05 19:15:01
 * @warning
 */
void SendStringLan( UINT uiOpCode, const char *pData )
{
    g_pTheCCUSocket->SendStringLan( uiOpCode, pData );
    if( g_pTheCCUDebugSocket != NULL ) {
        g_pTheCCUDebugSocket->SendStringLan( uiOpCode, pData );
    }

}


/**
 * @brief     초기 멤버 변수값등을 설정하는 객체 생성자 입니다.
 * @param     int iKeyId
 * @param     const char * pClassName
 * @param     unsigned short usPort
 * @param     char * pServerAddress
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 10:54:00
 * @warning
 */
CSingleClient::CSingleClient( int iKeyId, const char *pClassName, COperationConsole *ptheOperationConsole, unsigned short usPort, char *pClientAddress, void *pParent ) : CThread( iKeyId, pClassName )
{
    string strIPAddress;

    m_ptheOperationConsole = ptheOperationConsole;

#ifdef _MSC_VER
    TRACE( "\n m_ptheOperationConsole[%p]", m_ptheOperationConsole );
#endif

    m_pParent = pParent;

    m_usPort = usPort;

    m_bServer = false;

    m_bConnected = false;

    if( pClientAddress == NULL ) {
#ifdef __VXWORKS__
        //m_vecServerAddress.push_back( g_pTheSysConfig->GetRecentConnectionOfNetwork() );

        m_vecServerAddress.push_back( g_pTheSysConfig->GetDebugServerOfNetwork() );
        m_vecServerAddress.push_back( g_pTheSysConfig->GetCCUServerOfNetwork() );
#else
        m_vecServerAddress.push_back( g_pTheSysConfig->GetDebugServerOfNetwork() );
#endif

    }
    else {
        m_vecServerAddress.push_back( pClientAddress );
    }

#if 0
    int j = 0;

    char *pIPAddress = g_pTheSysConfig->GetCCUServerOfNetwork();

    for( i = 2; i < NUM_OF_SERVER + 2; ++i ) {
        char buffer[100];

        if( j == 0 ) {
            strcpy( m_szServerAddress[j], pIPAddress );
        }
        else {
            sprintf( buffer, "192.168.0.%d", i );
            strcpy( m_szServerAddress[j], buffer );

        }

        ++j;
    }

#endif

    Init();

#if 0
    unsigned long long x;

    x = FIONBIO;
#endif

    m_ptheOperationConsole->Run();

}


/**
 * @brief     종료 메시지와 메머리 해지를 처리하는 객체 소먈자 입니다.
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 15:32:42
 * @warning
 */
CSingleClient::~CSingleClient()
{
    //LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );

    Free();
}

/**
 * @brief     메모리를 할당하고 변수를 초기화한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 15:33:16
 * @warning
 */
void CSingleClient::Init()
{
    Alloc();

}

/**
 * @brief     객체에 필요한 메모리를 할당한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-10-24 10:45:44
 * @warning
 */
void CSingleClient::Alloc()
{
    m_pszLanData = ( char * ) malloc( sizeof( char ) * _MAX_LANDATA );

}

/**
 * @brief     객체 메모리를 해지한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-10-24 10:46:03
 * @warning
 */
void CSingleClient::Free()
{

    free( m_pszLanData );

    _SAFE_DELETE( m_ptheOperationConsole )

}

/**
 * @brief     CThread 클래스의 Run() 함수를 호출하여 쓰레드를 생성하게 합니다.
 * @param     key_t key
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-10-24 10:48:42
 * @warning
 */
void CSingleClient::Run( key_t key )
{
    // 소켓 모드 설정
    //m_enSocketMode = enSocketMode;

    CThread::Run();

}

/**
 * @brief     쓰레드에서 서버 또는 클라이언트를 실행하게 한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-10-24 10:49:05
 * @warning
 */
void CSingleClient::_routine()
{

    if( m_bServer == true ) {
        Log( enDebug, "[서버] 소켓을 설정 합니다." );
        RunServer();
    }
    else {
        //         int i, iIndex=0;
        //         char buffer[100];
        //
        //         for( i=0 ; i < NUM_OF_SERVER-1 ; ++i ) {
        //             iIndex += sprintf( & buffer[iIndex], "%s/" , m_szServerAddress[i] );
        //         }
        //         sprintf( & buffer[iIndex], "%s" , m_szServerAddress[i] );

                //Log( enDebug, "[클라이언트:%s] [%s,%d] 연결하려 합니다.", GetThreadName(), buffer, m_iPort );
        RunClient();
    }

}

/**
 * @brief     랜 소켓 클라이언트 실행시 소켓으로부터 수신 메시지를 확인한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-10-24 10:59:18
 * @warning
 */
void CSingleClient::RunClient()
{
    bool bHeader;
    int iTotalRead;

    STR_LAN_HEADER strLanHeader;

    int iActivity, iRead;
    SOCKET soMaxSocket;

    char *pLanData;

    struct sockaddr_in sockAddress;
    unsigned int uiTryConnect = 0;

    m_pMsg = GetRecvDataMessage();

    fd_set readfds;

    STR_MessageData sndMsg;

    m_soSocket = 0;

    m_bConnected = false;

    // 10 초 후에 랜 대기를 수행하게 한다.
    while( g_pTheTaskMngr->GetMode() != enREADY_MODE ) {
        // TRACE( "." );
        Sleep( 1 );
    }

    //size_t uiCoServerList = m_vecServerAddress.size();

    while( m_bThreadLoop ) {
        string strServerIPAdddress;

        for( const auto & strServerIPAddress : m_vecServerAddress ) {

#ifdef __VXWORKS__
            if( uiTryConnect++ % 3000 == 0 ) {
                TRACE( "\n[클라이언트:%s] [%s/%d] 연결하려 합니다.\n", GetThreadName(), strServerIPAddress.c_str(), m_usPort );
            }
#else
            //TRACE( "\n[클라이언트:%s] [%s/%d] 연결하려 합니다.\n", GetThreadName(), strServerIPAddress.c_str(), m_usPort );
#endif

#ifdef _MSC_VER
            memset( ( char * ) &sockAddress, 0, sizeof( sockAddress ) );
#else
            bzero( ( char * ) &sockAddress, sizeof( sockAddress ) );
#endif

            sockAddress.sin_family = AF_INET;
            sockAddress.sin_addr.s_addr = inet_addr( strServerIPAddress.c_str() );
            sockAddress.sin_port = htons( m_usPort );

            //create a master socket
            m_soSocket = socket( AF_INET, SOCK_STREAM, 0 );
            if( m_soSocket == 0 ) {
                perror( "Master Socket 실패" );
                continue;
            }

            SetSocketOption();

            //LOGMSG2( enDebug, "Try Connection to [%s/%d]...", m_szServerAddress, m_iPort );
            if( ConnectTimeout( m_soSocket, & sockAddress, 1 ) < 0 ) {
                CloseSocket( false );
#ifndef _MSC_VER
                // sleep( 1 );
#endif
            }
            else {
                if( strcmp( strServerIPAddress.c_str(), g_pTheSysConfig->GetDebugServerOfNetwork() ) == 0 ) {
                    m_bDebugConnected = true;
                }

                Log( enNormal, "[%s/%d/%d]으로 연결 성공했습니다.", strServerIPAddress.c_str(), m_usPort, (int) m_soSocket );
                bHeader = true;
                iTotalRead = 0;

                while( true ) {
                    FD_ZERO( &readfds );

#ifdef _MSC_VER
                	USR_FD_SET( m_soSocket, &readfds );
#else
                	FD_SET( m_soSocket, &readfds );
#endif
                    soMaxSocket = m_soSocket;

                    //wait for an activity on one of the sockets , timeout is NULL ,
                    //so wait indefinitely
                    iActivity = select( ( int ) ( soMaxSocket + 1 ), &readfds, NULL, NULL, NULL );

                    if( ( iActivity < 0 ) && ( errno != EINTR ) ) {
                        perror( "select 에러" );
                        OnDisconnected( strServerIPAddress.c_str() );
                        break;
                    }

                    // 랜 헤더 메시지 수신
                    if( bHeader == true ) {
                        pLanData = ( char * ) & strLanHeader;

                        if( ( int ) ( sizeof( struct STR_LAN_HEADER ) - iTotalRead ) >= 1 ) {
                            iRead = recv( m_soSocket, & pLanData[iTotalRead], ( int ) ( sizeof( struct STR_LAN_HEADER ) - iTotalRead ), MSG_DONTWAIT );
#ifdef _MSC_VER
                            //TRACE( "[H%d]" , iRead );
#endif
                            if( iRead <= 0 ) {
#ifdef _MSC_VER
                                perror( "recv 에러" );
#endif
                                OnDisconnected( strServerIPAddress.c_str() );
                                break;
                            }
                            else {
                                iTotalRead += iRead;
                                //printf( "#[%d/%d]" , uiTotalRead, strLanHeader.uiLength );
                                if( iTotalRead == sizeof( struct STR_LAN_HEADER ) ) {
#ifdef _MSC_VER
                                    CCommonUtils::AllSwapData16( & strLanHeader.usOpCode, ( unsigned int ) sizeof( unsigned short ) );
                                    CCommonUtils::AllSwapData32( & strLanHeader.uiLength, ( unsigned int ) sizeof( unsigned int ) );
#endif
                                    if( strLanHeader.uiLength == 0 ) {
                                        bHeader = true;
                                        iTotalRead = 0;
#ifdef __linux__
                                        sndMsg.mtype = 1;
#endif
                                        sndMsg.uiOpCode = strLanHeader.usOpCode;
                                        sndMsg.soSocket = m_soSocket;
                                        sndMsg.iArrayIndex = -1;
                                        sndMsg.uiArrayLength = 0;
                                        sndMsg.uiDataLength = 0;

#if defined(_MSC_VER) || defined(__VXWORKS__)
                                        //TRACE( "\n m_ptheOperationConsole[%p]", m_ptheOperationConsole );
                                        m_ptheOperationConsole->QMsgSnd( & sndMsg, ( void * ) NULL, GetThreadName() );

#elif defined(__linux__)
                                        if( msgsnd( m_ptheOperationConsole->GetKeyId(), ( void * ) & sndMsg, sizeof( struct STR_MessageData ) - sizeof( long ), IPC_NOWAIT ) < 0 ) {
                                            perror( "msgsnd 실패" );
                                            Log( enError, "msgsnd 실패" );
                                        }
#else
                                        Log( enError, "타스크/쓰레드간 메시지 통신방안을 구성해야 합니다." );
#endif
                                    }
                                    else {
                                        bHeader = false;
                                        iTotalRead = 0;
                                    }
                                }
                            }
                        }
                        else {
                            perror( "recv()::header 부분에서 데이터 길이가 잘못됐습니다 !!" );
                            Log( enError, "recv()::header 부분에서 데이터 길이가 잘못됐습니다 !!" );
                        }
                    }
                    else {
                        if( ( int ) strLanHeader.uiLength - iTotalRead >= 1 ) {
                            pLanData = ( char * ) & m_pszLanData[0];
                            iRead = recv( m_soSocket, & pLanData[iTotalRead], ( int ) strLanHeader.uiLength - iTotalRead, MSG_DONTWAIT );

                            TRACE( "[D%d]", iRead );
                            if( iRead <= 0 ) {
                                perror( "recv 에러" );
                                OnDisconnected( strServerIPAddress.c_str() );
                                break;
                            }
                            else {
                                iTotalRead += iRead;
#ifdef _WIN32
                                CCommonUtils::AllSwapData32( & pLanData[iTotalRead], ( unsigned int ) strLanHeader.uiLength );
#endif

                                //printf( "*[%d/0x%X/%d]" , uiTotalRead, strLanHeader.uiOpCode, strLanHeader.uiLength );
                                if( iTotalRead == ( int ) strLanHeader.uiLength ) {
                                    bHeader = true;
                                    iTotalRead = 0;
#ifdef __linux__
                                    sndMsg.mtype = 1;
#endif
                                    sndMsg.uiOpCode = strLanHeader.usOpCode;
                                    sndMsg.soSocket = m_soSocket;
                                    sndMsg.iArrayIndex = -1;
                                    sndMsg.uiArrayLength = 0;
                                    sndMsg.uiDataLength = 0;

                                    if( strLanHeader.uiLength < sizeof( union UNI_MSG_DATA ) ) {
                                        sndMsg.uiDataLength = strLanHeader.uiLength;
                                        memcpy( & sndMsg.x.szData[0], pLanData, sndMsg.uiDataLength );
                                    }
                                    else {
                                        sndMsg.uiArrayLength = strLanHeader.uiLength;
                                        sndMsg.iArrayIndex = m_ptheOperationConsole->PushLanData( pLanData, sndMsg.uiArrayLength );
                                    }

                                    /*
                                     *                             if( sndMsg.uiOpCode == enREQ_SIM_PDWDATA || sndMsg.uiOpCode == enREQ_IPL_DOWNLOAD || sndMsg.uiOpCode == enREQ_SET_CONFIG ) {
                                                                    sndMsg.uiArrayLength = strLanHeader.uiLength;
                                                                    sndMsg.iArrayIndex = m_ptheRecLan->PushLanData( pLanData, sndMsg.uiArrayLength );
                                                                }
                                                                else {
                                                                    if( strLanHeader.uiLength < sizeof(union UNI_MSG_DATA) ) {
                                                                        sndMsg.uiDataLength = strLanHeader.uiLength;
                                                                        memcpy( & sndMsg.x.szData[0], pLanData, sndMsg.uiDataLength );
                                                                    }
                                                                    else {
                                                                        LOGMSG1( enError, "랜 수신 데이터(0x%x)를 초과했습니다. PushLanData()를 이용해서 저장해야 합니다. !!", m_pMsg->uiOpCode );
                                                                    }
                                                                }           */

#if defined(_MSC_VER) || defined(__VXWORKS__)
                                    TRACE( "\n m_ptheOperationConsole[%p]", m_ptheOperationConsole );
                                    m_ptheOperationConsole->QMsgSnd( & sndMsg, ( void * ) NULL, GetThreadName() );

#elif defined(__linux__)
                                    if( msgsnd( m_ptheOperationConsole->GetKeyId(), ( void * ) & sndMsg, sizeof( struct STR_MessageData ) - sizeof( long ), IPC_NOWAIT ) < 0 ) {
                                        perror( "msgsnd 실패" );
                                    }
                                    else {
                                        if( sndMsg.uiOpCode == enREQ_MODE && sndMsg.x.uiData == enREADY_MODE ) {
                                            // Log( enError, "대기 명령으로 소켓을 닫습니다." );
                                            // break;
                                        }
                                        // DisplayMsg( & sndMsg );

                                    }
#else
                                    Log( enError, "타스크/쓰레드간 메시지 통신방안을 구성해야 합니다." );
#endif
                                }
                            }
                        }
                        else {
                            iRead = recv( m_soSocket, m_pszLanData, ( int ) _MAX_LANDATA, MSG_DONTWAIT );
                            if( iRead <= 0 ) {
                                Log( enError, "recv()::data 부분에서 데이터 길이가 잘못됐습니다 !!" );
                                perror( "recv()::data 부분에서 데이터 길이가 잘못됐습니다 !!" );
                                break;
                            }

                        }
                    }
                }

                // LOGMSG2( enDebug, "[서버] 클라이언트로 [%s/%d] 재연결하려 합니다.", m_szServerAddress[iServerSwitch], m_iPort );

                // 소켓을 닫는다.
                CloseSocket();
            }

        }

    }


}

/**
 * @brief     소켓 옵션(LINGER, REUSEADDRESS, 송수신 버퍼 크기 등)을 설정합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-02 10:53:18
 * @warning
 */
void CSingleClient::SetSocketOption()
{
    // 아래는 소켓 옵셥을 설정합니다.
    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    int iOptval = 1;
    int sizeOfLanBuf = 10240;

    struct linger stLINGER;

    // close() 될때 소켓 버퍼에 남아 있는 데이터를 버리는 비정상 종료를 수행합니다.
    stLINGER.l_onoff = TRUE;
    stLINGER.l_linger = 0;
    //setsockopt( m_hClientSocket, SOL_SOCKET, SO_LINGER, ( char* ) &LINGER, sizeof( struct LINGER ) );
    if( setsockopt( m_soSocket, SOL_SOCKET, SO_LINGER, ( char * ) &stLINGER, sizeof( linger ) ) < 0 ) {
        perror( "소켓 옵션(SO_LINGER)" );
    }
    //     if( setsockopt( m_uiSocket, SOL_SOCKET, SO_REUSEADDR, ( char* ) &iOptval, sizeof( iOptval ) ) < 0 ) {
    //         perror( "소켓 옵션(SO_REUSEADDR)" );
    //     }
    if( setsockopt( m_soSocket, SOL_SOCKET, SO_SNDBUF, ( char * ) &sizeOfLanBuf, sizeof( sizeOfLanBuf ) ) < 0 ) {
        perror( "소켓 옵션(SO_SNDBUF)" );
    }
    if( setsockopt( m_soSocket, SOL_SOCKET, SO_RCVBUF, ( char * ) &sizeOfLanBuf, sizeof( sizeOfLanBuf ) ) < 0 ) {
        perror( "소켓 옵션(SO_RCVBUF)" );
    }

    if( setsockopt( m_soSocket, SOL_SOCKET, SO_KEEPALIVE, ( const char * ) &iOptval, sizeof( iOptval ) ) < 0 ) {
        perror( "소켓 옵션(SO_KEEPALIVE)" );
    }

#ifdef _MSC_VER
    int iFlags = 10;
    if( setsockopt( m_soSocket, SOL_SOCKET, TCP_KEEPIDLE, ( const char * ) &iFlags, sizeof( iFlags ) ) < 0 ) {
        perror( "소켓 옵션(TCP_KEEPIDLE)" );
    }
#endif

}

/**
 * @brief     랜 소켓이 끊어졌을때 이벤트를 발생합니다.
 * @param     char * pServerIPAddress
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-10-24 11:00:40
 * @warning
 */
void CSingleClient::OnDisconnected( const char *pServerIPAddress )
{
    STR_MessageData sndMsg;

    Log( enError, "서버(%s)가 끊겼습니다.", pServerIPAddress );

    CloseSocket();

    //TRACE( "서버가 끊겼습니다." );

#ifdef __linux__
    sndMsg.mtype = 1;
#endif

    sndMsg.uiOpCode = enTHREAD_DISCONNECTED;
    sndMsg.soSocket = m_soSocket;
    sndMsg.iArrayIndex = -1;
    sndMsg.uiArrayLength = 0;
    sndMsg.uiDataLength = sizeof( int );

#ifdef _MSC_VER
    m_ptheOperationConsole->QMsgSnd( & sndMsg, ( void * ) NULL, GetThreadName() );

#elif defined(__VXWORKS__)
    m_ptheOperationConsole->QMsgSnd( & sndMsg, ( void * ) NULL, GetThreadName() );

#elif defined(__linux__)
    if( msgsnd( m_ptheOperationConsole->GetKeyId(), ( void * ) & sndMsg, sizeof( struct STR_MessageData ) - sizeof( long ), IPC_NOWAIT ) < 0 ) {
        perror( "msgsnd 실패" );
    }
#endif

    // 디버그 포트 연결 여부
    if( strcmp( pServerIPAddress, g_pTheSysConfig->GetDebugServerOfNetwork() ) == 0 ) {
        m_bDebugConnected = false;
    }


}

/**
 * @brief     설정한 시간만큼 서버와 연결을 시도한다.
 * @param     unsigned int uiSock
 * @param     struct sockaddr_in * pAddr
 * @param     long timeout_milli
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-10-24 11:00:56
 * @warning
 */
int CSingleClient::ConnectTimeout( SOCKET soSock, struct sockaddr_in *pAddr, long timeout_milli )
{
    int iRet = 0;

    int err;

    socklen_t len;
    fd_set writefds;
    struct timeval timeout;

    FD_ZERO( &writefds );

#ifdef _MSC_VER
    u_long block = 1;

    //unsigned long ullfionbio = (unsigned long) FIONBIO;
    unsigned long ullfionbio = 0x8004667e;
    if( ioctlsocket( soSock, ( long ) ullfionbio, & block ) != 0 ) {
        perror( "fcntl() error" );
        iRet = -1;
    }
    else {
        if( connect( soSock, ( struct sockaddr * ) pAddr, sizeof( sockaddr_in ) ) != 0 ) {
#ifdef _MSC_VER
#else
            if( errno != EINPROGRESS ) {
                perror( "connect() error\n" );
                iRet = -1;
            }
#endif
        }

        timeout.tv_sec = timeout_milli / ( long ) 1000;
        timeout.tv_usec = ( timeout_milli % 1000 ) * ( long ) 1000;

#ifdef _MSC_VER
        USR_FD_SET( soSock, &writefds );
#else
        FD_SET( soSock, &writefds );
#endif


        if( select( ( int ) soSock + 1, NULL, &writefds, NULL, &timeout ) <= 0 ) {
            //perror("connection timeout\n");
            iRet = -1;
        }
        else {
            len = sizeof( err );
            getsockopt( soSock, SOL_SOCKET, SO_ERROR, ( char * ) &err, &len );
            //             if (err) {
            //                 //perror( "getsockopt()" );
            //                 //iRet = -1;
            //             }


            block = 0;
            if( ioctlsocket( soSock, ( long ) ullfionbio, & block ) != 0 ) {
                perror( "ioctlsocket() error" );
                iRet = -1;
            }
        }
    }

#elif defined(__VXWORKS__)

    int iOn;

    iOn = 1;
    if( ioctl( soSock, FIONBIO, & iOn ) != 0 ) {
        perror( "ioctl() error" );
        iRet = -1;
    }
    else {
        if( connect( soSock, ( struct sockaddr * ) pAddr, sizeof( struct sockaddr_in ) ) != 0 ) {
            if( errno != EINPROGRESS ) {
                perror( "connect() error" );
                iRet = -1;
            }
        }

        timeout.tv_sec = timeout_milli / 1000;
        timeout.tv_usec = ( timeout_milli % 1000 ) * 1000;
        FD_SET( soSock, &writefds );
        if( select( soSock + 1, NULL, &writefds, NULL, &timeout ) <= 0 ) {
            // perror("select");
            iRet = -1;
        }
        else {
            len = sizeof( err );
            getsockopt( soSock, SOL_SOCKET, SO_ERROR, ( char * ) &err, &len );
            if( err ) {
                //perror( "getsockopt() error" );
                iRet = -1;
            }

            iOn = 0;
            if( ioctl( soSock, FIONBIO, & iOn ) != 0 ) {
                perror( "ioctl() error" );
                iRet = -1;
            }
        }
    }

#else
    int flags;

    flags = fcntl( uiSock, F_GETFL );
    flags = ( flags | O_NONBLOCK );

    if( fcntl( uiSock, F_SETFL, flags ) != 0 ) {
        perror( "fcntl() error" );
        iRet = -1;
    }
    else {
        if( connect( uiSock, ( struct sockaddr * ) pAddr, sizeof( struct sockaddr_in ) ) != 0 ) {
            if( errno != EINPROGRESS ) {
                perror( "connect() error" );
                iRet = -1;
            }
        }

        timeout.tv_sec = timeout_milli / 1000;
        timeout.tv_usec = ( timeout_milli % 1000 ) * 1000;
        FD_SET( uiSock, &writefds );
        if( select( uiSock + 1, NULL, &writefds, NULL, &timeout ) <= 0 ) {
            perror( "select" );
            iRet = -1;
        }
        else {
            len = sizeof( err );
            getsockopt( uiSock, SOL_SOCKET, SO_ERROR, ( char * ) &err, &len );
            if( err ) {
                perror( "getsockopt()" );
                iRet = -1;
            }

            fcntl( uiSock, F_GETFL );
            flags = ( flags & ~O_NONBLOCK );
            if( fcntl( uiSock, F_SETFL, flags ) != 0 ) {
                perror( "fcntl() error" );
                iRet = -1;
            }
        }
    }
#endif

    if( iRet != -1 ) {
        m_bConnected = true;
        OnConnect( pAddr );
    }

    return iRet;

}

/**
 * @brief     랜 소켓 서버 실행시 소켓으로부터 수신 메시지를 확인한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-10-24 11:02:01
 * @warning
 */
void CSingleClient::RunServer()
{
#ifdef __linux__
    bool bHeader;
    UINT uiTotalRead;

    STR_LAN_HEADER strLanHeader;

    int opt = true, addrlen, iActivity, iRead;
    int iClientSocket;
    int iMasterSocket, iMaxSocket, iNewSocket;

    char *pLanData;

    struct sockaddr_in sockAddress;

    m_pMsg = GetRecvDataMessage();

    //set of socket descriptors
    fd_set readfds;

    STR_MessageData sndMsg;

    //initialise all client_socket[] to 0 so not checked
    iClientSocket = 0;

    m_bConnected = false;

    //create a master socket
    if( ( iMasterSocket = socket( AF_INET, SOCK_STREAM, 0 ) ) == 0 ) {
        perror( "Master Socket 실패" );
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if( setsockopt( iMasterSocket, SOL_SOCKET, SO_REUSEADDR, ( char * ) &opt, sizeof( opt ) ) < 0 ) {
        perror( "Master Socket 소켓 옵션" );
    }

    //type of socket created
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_addr.s_addr = INADDR_ANY;
    sockAddress.sin_port = htons( m_usPort );

    if( bind( iMasterSocket, ( struct sockaddr * ) &sockAddress, sizeof( sockAddress ) ) < 0 ) {
        perror( "Bind 실패" );
    }
    printf( " Listener on port %d\n", m_usPort );

    //try to specify maximum of 3 pending connections for the master socket
    if( listen( iMasterSocket, 3 ) < 0 ) {
        perror( "Listen 실패" );
    }

    //accept the incoming connection
    addrlen = sizeof( sockAddress );
    puts( " Waiting for connections ..." );

    while( true ) {
        //clear the socket set
        FD_ZERO( &readfds );

        //add master socket to set
        FD_SET( iMasterSocket, &readfds );
        iMaxSocket = iMasterSocket;

        //add child sockets to set
        {
            //socket descriptor
            m_uiSocket = iClientSocket;

            //if valid socket descriptor then add to read list
            if( m_uiSocket > 0 ) {
                FD_SET( m_uiSocket, &readfds );
            }

            //highest file descriptor number, need it for the select function
            if( m_uiSocket > iMaxSocket ) {
                iMaxSocket = m_uiSocket;
            }
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        iActivity = select( iMaxSocket + 1, &readfds, NULL, NULL, NULL );

        if( ( iActivity < 0 ) && ( errno != EINTR ) ) {
            perror( "select 에러" );
            //break;
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if( FD_ISSET( iMasterSocket, &readfds ) ) {
            if( ( iNewSocket = accept( iMasterSocket, ( struct sockaddr * ) &sockAddress, ( socklen_t * ) &addrlen ) ) < 0 ) {
                perror( "Accept 실패" );
            }
            else {
                //if position is empty
                iClientSocket = iNewSocket;
                bHeader = true;
                uiTotalRead = 0;

                LOGMSG2( enDebug, "연결 성공: ip %s , port %d", inet_ntoa( sockAddress.sin_addr ), ntohs( sockAddress.sin_port ) );
            }
        }

        //else its some IO operation on some other socket
        {
            m_uiSocket = iClientSocket;

            //Check if it was for closing , and also read the
            //incoming message
            if( FD_ISSET( m_uiSocket, &readfds ) ) {
                if( bHeader == true ) {
                    pLanData = ( char * ) & strLanHeader;
                    if( ( iRead = recv( m_uiSocket, & pLanData[uiTotalRead], sizeof( struct STR_LAN_HEADER ) - uiTotalRead, MSG_DONTWAIT ) ) == 0 ) {
                        CloseSocket( & sockAddress, & iClientSocket );
                    }
                    //Echo back the message that came in
                    else {
                        uiTotalRead += iRead;
                        if( uiTotalRead == sizeof( struct STR_LAN_HEADER ) ) {
                            if( strLanHeader.uiLength == 0 ) {
                                bHeader = true;
                                uiTotalRead = 0;

                                sndMsg.mtype = 1;
                                sndMsg.uiOpCode = strLanHeader.usOpCode;
                                sndMsg.uiSocket = m_uiSocket;
                                sndMsg.iArrayIndex = -1;
                                sndMsg.uiArrayLength = 0;
                                sndMsg.uiDataLength = 0;

                                if( msgsnd( m_ptheOperationConsole->GetKeyId(), ( void * ) & sndMsg, sizeof( struct STR_MessageData ) - sizeof( long ), IPC_NOWAIT ) < 0 ) {
                                    perror( "msgsnd 실패" );
                                }
                                else {
                                    // DisplayMsg( & sndMsg );
                                }

                            }
                            else {
                                bHeader = false;
                                uiTotalRead = 0;
                            }
                        }
                    }
                }
                else {
                    pLanData = ( char * ) & m_pszLanData[0];
                    if( ( iRead = recv( m_uiSocket, & pLanData[uiTotalRead], strLanHeader.uiLength - uiTotalRead, MSG_DONTWAIT ) ) == 0 ) {
                        CloseSocket( & sockAddress, & iClientSocket );
                    }
                    else {
                        uiTotalRead += iRead;
                        if( uiTotalRead == strLanHeader.uiLength ) {
                            bHeader = true;
                            uiTotalRead = 0;

                            sndMsg.mtype = 1;
                            sndMsg.uiOpCode = strLanHeader.usOpCode;
                            sndMsg.uiSocket = m_uiSocket;
                            sndMsg.iArrayIndex = -1;
                            sndMsg.uiArrayLength = 0;
                            sndMsg.uiDataLength = 0;

                            if( strLanHeader.uiLength < sizeof( union UNI_MSG_DATA ) ) {
                                sndMsg.uiDataLength = strLanHeader.uiLength;
                                memcpy( & sndMsg.x.szData[0], pLanData, sndMsg.uiDataLength );
                            }
                            else {
                                sndMsg.uiArrayLength = strLanHeader.uiLength;
                                sndMsg.iArrayIndex = m_ptheOperationConsole->PushLanData( pLanData, sndMsg.uiArrayLength );
                            }

                            if( msgsnd( m_ptheOperationConsole->GetKeyId(), ( void * ) & sndMsg, sizeof( struct STR_MessageData ) - sizeof( long ), IPC_NOWAIT ) < 0 ) {
                                perror( "msgsnd 실패" );
                            }
                            else {
                                // DisplayMsg( & sndMsg );

                            }

                        }
                    }
                }
            }
        }
    }
#else
    while( true ) {
        sleep( 10 );

    }

#endif

}

/**
 * @brief     연결시 이벤트를 발생한다.
 * @param     struct sockaddr_in * pAddr
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-10-24 11:02:29
 * @warning
 */
void CSingleClient::OnConnect( struct sockaddr_in *pAddr )
{
    char *pIPAddress;

    if( pAddr != NULL ) {
        pIPAddress = inet_ntoa( pAddr->sin_addr );
        g_pTheSysConfig->SetPrimeServerOfNetwork( pIPAddress, true );

        g_pTheSysConfig->WritePrimeServerIPAddress( pIPAddress );

#ifdef __VXWORKS__
        if( strcmp( pIPAddress, g_pTheSysConfig->GetCCUServerOfNetwork() ) == 0 ) {
            Log( enDebug, "디버그 콘솔을 구동 합니다." );
            g_pTheCCUDebugSocket->Run( _MSG_CCU_DEBUG_KEY );
            WhereIs;
        }
        else {
            // Log( enNormal, "디버그 콘솔을 구동하지 않습니다" );
        }
#endif

    }

#ifdef _MSC_VER
    CMSIGADlg *pDlg;

    pDlg = ( CMSIGADlg * ) m_pParent;
    pDlg->OnConnect( pAddr );

#endif

}

/**
 * @brief     소켓을 닫을 때 이 함수를 호출한다.
 * @param     struct sockaddr_in * pAddress
 * @param     int * pClientSocket
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-10-24 11:02:46
 * @warning
 */
void CSingleClient::CloseSocket( struct sockaddr_in *pAddress, int *pClientSocket )
{
#ifdef __linux__
    int addrlen;

    addrlen = sizeof( sockaddr_in );
    //Somebody disconnected , get his details and print
    getpeername( m_uiSocket, ( struct sockaddr * ) pAddress, ( socklen_t * ) &addrlen );
    LOGMSG2( enDebug, "연결 단절: ip %s , port %d", inet_ntoa( pAddress->sin_addr ), ntohs( pAddress->sin_port ) );

    //Close the socket and mark as 0 in list for reuse
    CloseSocket();

    if( pClientSocket != NULL ) {
        *pClientSocket = 0;
    }

    UINT uiMode = enREADY_MODE;
    QMsgSnd( g_pTheTaskMngr->GetKeyId(), enREQ_MODE, & uiMode, sizeof( int ) );
#endif

}

/**
 * @brief     SendLan
 * @param     UINT uiOpCode
 * @param     char * pData
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-09 15:18:43
 * @warning
 */
int CSingleClient::SendStringLan( UINT uiOpCode, const char *pData )
{
    int iRet;
    unsigned int uiDataLength;

    STR_LAN_HEADER strLanHeader;

    if( IsConnected() == true ) {
        int iRet1, iRet2 = 0;

        memset( & strLanHeader, 0, sizeof( strLanHeader ) );

        uiDataLength = ( unsigned int ) strlen( pData );

        // 랜 헤더 송신
        strLanHeader.usOpCode = uiOpCode;
        strLanHeader.uiLength = uiDataLength;

#ifdef _MSC_VER
        CCommonUtils::AllSwapData16( &strLanHeader.usOpCode, sizeof( unsigned short ) );
        CCommonUtils::AllSwapData32( &strLanHeader.uiLength, sizeof( unsigned int ) );
#endif
        iRet1 = send( m_soSocket, ( char * ) & strLanHeader, sizeof( struct STR_LAN_HEADER ), MSG_DONTWAIT );

#ifdef _MSC_VER
        CCommonUtils::AllSwapData16( &strLanHeader.usOpCode, sizeof( unsigned short ) );
        CCommonUtils::AllSwapData32( &strLanHeader.uiLength, sizeof( unsigned int ) );
#endif

        if( iRet1 > 0 && uiDataLength != 0 ) {
            // 문자열이니 마지막에 NULL 을 삽입해서 전송합니다.
            //pData[uiDataLength + 1] = 0;

#ifdef _MSC_VER

#endif

            iRet2 = send( m_soSocket, ( const char * ) pData, ( int ) ( uiDataLength ), MSG_DONTWAIT );
            if( iRet2 <= 0 ) {
                perror( "send()" );
            }
            else {
#ifdef __VXWORKS__
                DisplayMsg( & strLanHeader, pData, true );
#endif
            }

        }
        else {
            WhereIs;
            // TaskMngr () Send Error 발생시 Lock 이 됨.
            perror( "send()" );
        }

        iRet = iRet1 + iRet2;
    }
    else {
        iRet = -1;
    }

    return iRet;

}

/**
 * @brief     연결된 서버에 데이터를 송신한다.
 * @param     UINT uiOpCode
 * @param     void * pData
 * @param     UINT uiDataLength
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-10-24 11:03:06
 * @warning
 */
int CSingleClient::SendLan( UINT uiOpCode, void *pData, size_t szDataLength, BOOL bSwap )
{
    int iRet;

    STR_LAN_HEADER strLanHeader;

    if( IsConnected() == true ) {
        int iRet1, iRet2 = 0;

        strLanHeader.ucSource = 0;
        strLanHeader.ucDestination = 0;

        // 랜 헤더 송신
        strLanHeader.usOpCode = uiOpCode;
        strLanHeader.uiLength = (unsigned int) szDataLength;

#ifdef _WIN32
        CCommonUtils::AllSwapData16( &strLanHeader.usOpCode, sizeof( unsigned short ) );
        CCommonUtils::AllSwapData32( &strLanHeader.uiLength, sizeof( unsigned int ) );
#endif
        iRet1 = send( m_soSocket, ( char * ) & strLanHeader, sizeof( struct STR_LAN_HEADER ), MSG_DONTWAIT );

#ifdef _WIN32
        CCommonUtils::AllSwapData16( &strLanHeader.usOpCode, sizeof( unsigned short ) );
        CCommonUtils::AllSwapData32( &strLanHeader.uiLength, sizeof( unsigned int ) );
#endif

        if( iRet1 > 0 && szDataLength != 0 ) {
            if( bSwap == TRUE ) {
#ifdef _WIN32
                CCommonUtils::AllSwapData32( pData, szDataLength );
#endif
            }

            iRet2 = send( m_soSocket, ( char * ) pData, ( int ) szDataLength, MSG_DONTWAIT );
            if( iRet2 <= 0 ) {
                perror( "send()" );
            }

            if( bSwap == TRUE ) {
#ifdef _WIN32
                CCommonUtils::AllSwapData32( pData, szDataLength );
#endif
            }

#ifdef __VXWORKS__
            DisplayMsg( & strLanHeader, pData, true );
#endif

            iRet = iRet1 + iRet2;
        }
        else {
            WhereIs;
            // TaskMngr () Send Error 발생시 Lock 이 됨.
            perror( "send()" );
            iRet = -1;
        }

    }
    else {
        iRet = -1;
    }

    return iRet;

}

/**
 * @brief     헤더와 메시지 데이터를 출력합니다.
 * @param     STR_LAN_HEADER * pHeader
 * @param     void * pData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-04 14:33:19
 * @warning
 */
void CSingleClient::DisplayMsg( STR_LAN_HEADER *pHeader, const void *pData, bool bSend )
{
#ifdef __VXWORKS__
    std::string strMessage;

    // 랜 메시지 출력시 반대로 해서 설정하여 출력 합니다.
    CCommonUtils::MakeStringMessage( &strMessage, pHeader->usOpCode, ! bSend );

    if( pHeader->usOpCode == enRES_SYSERROR ) {
        Log( enDebug, "$랜 송신: Op[%s:0x%04X], Len[%d], [%s]", strMessage.c_str(), pHeader->usOpCode, pHeader->uiLength, ( const char * ) pData );
    }
    else {
        Log( enDebug, "$랜 송신: Op[%s:0x%04X], Len[%d]", strMessage.c_str(), pHeader->usOpCode, pHeader->uiLength );
    }
#endif

}

/**
 * @brief     CloseSocket
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 13:19:24
 * @warning
 */
void CSingleClient::CloseSocket( bool bEnableLog )
{
    m_bConnected = false;

    if( m_soSocket > 0 ) {
        SOCKET soSocket = m_soSocket;
        m_soSocket = 0;

        if( bEnableLog == true ) {
            Log( enNormal, "소켓을 정상적으로 닫습니다." );
        }

#ifdef _MSC_VER
        shutdown( soSocket, SD_BOTH );
        closesocket( soSocket );
        //_close( uiSocket );
#else
        close( soSocket );
#endif
    }
    else {
        Log( enError, "두번 이상 소켓을 닫았습니다." );
    }

    // m_uiSocket = 0;

}
