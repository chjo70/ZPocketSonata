/****************************************************************************************
 파 일 명 : cmultiserver.cpp
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : 다중 클라리언트 랜 소켓 클래스
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 :
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#include "pch.h"

#include <errno.h>

#ifdef __linux__
#include <arpa/inet.h>

#elif defined(_MSC_VER)
#include <mstcpip.h>

#endif


#include "cmultiserver.h"

#include "ccommonutils.h"
// #include "../Include/globals.h"

/**
 * @brief CMultiServer::CMultiServer
 * @param iKeyId
 * @param pClassName
 */
CMultiServer::CMultiServer( int iKeyId, char *pClassName, int iPort, void *pParent ) : CThread( iKeyId, pClassName, false )
{
    m_iPort = iPort;

    m_pParent = pParent;

    Alloc();
    Init();


}

/**
 * @brief CMultiServer::~CMultiServer
 */
CMultiServer::~CMultiServer()
{
    //LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );

    Free();
}

/**
 * @brief     Init
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 16:05:38
 * @warning
 */
void CMultiServer::Init()
{
    int i;

    m_vClientSock.reserve( MAX_CLIENTS );

    m_QIndex.Init( MAX_CLIENTS );
    for( i=0 ; i < MAX_CLIENTS ; ++i ) {
        m_QIndex.Push( i );
    }

    //InitOfTCPIP();



//     if( m_iPort == CCU_PORT ) {
//         m_ptheRecLan = RECCCU;
//     }
//     else if( m_iPort == PORT ) {
//         m_ptheRecLan = RECZYNQ;
//     }
//     else {
//         m_ptheRecLan = NULL;
//     }

}

/**
 * @brief     InitOfTCPIP
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 16:01:10
 * @warning
 */
void CMultiServer::InitOfTCPIP()
{
    int iOption = 1;
    int	sizeOfLanBuf;
    struct linger LINGER;

    struct STR_TCP_KEEPALIVE {
        unsigned long onoff;
        unsigned long keepalivetime;
        unsigned long keepaliveinterval;

    } ;

    //initialise all client_socket[] to 0 so not checked
    m_vClientSock.clear();

    m_iServerType = _SERVER_TYPE;

    // 소켓 생성
    m_MasterSock = socket( AF_INET, SOCK_STREAM, 0 );
    if( m_MasterSock > 0 ) {
        setsockopt( m_MasterSock, SOL_SOCKET, SO_REUSEADDR, ( char* ) &iOption, sizeof( iOption ) );
        LINGER.l_onoff = TRUE;
        LINGER.l_linger = 0;
        setsockopt( m_MasterSock, SOL_SOCKET, SO_LINGER, ( char* ) &LINGER, sizeof( LINGER ) );
        sizeOfLanBuf = 10240;
        setsockopt( m_MasterSock, SOL_SOCKET, SO_SNDBUF, ( char* ) &sizeOfLanBuf, sizeof( sizeOfLanBuf ) );
        setsockopt( m_MasterSock, SOL_SOCKET, SO_RCVBUF, ( char* ) &sizeOfLanBuf, sizeof( sizeOfLanBuf ) );

        // IP 와 PORT 설정
        m_SockaddrInternet.sin_addr.s_addr = htonl( INADDR_ANY );
        m_SockaddrInternet.sin_family = AF_INET;
        m_SockaddrInternet.sin_port = htons( m_iPort );

        // 서버로서의 bind -> listen -> accept 처리
        if( !bind( m_MasterSock, ( struct sockaddr* ) &m_SockaddrInternet, sizeof( m_SockaddrInternet ) ) ) {
            listen( m_MasterSock, 5 );
        }
        else {
            perror( "bind 에러" );
        }
    }
    else {
        perror( "socket 에러" );
    }
}

/**
 * @brief		Alloc
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/09 10:04:42
 * @warning
 */
void CMultiServer::Alloc()
{
    int i;

    for( i=0 ; i < MAX_CLIENTS ; ++i ) {
        m_szRcvStat[i].pszLanData = ( char * ) malloc( sizeof(char) * _MAX_LANDATA );
        m_pstLanData[i] = ( STR_LAN_DATA * ) malloc( sizeof( struct STR_LAN_DATA ) );
    }

    m_ptheSBC = new CSBC( g_iKeyId++, ( char * ) "SBCCON", true, m_pParent );
    m_ptheSBC->Run();

}

/**
 * @brief		Free
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/09 10:04:31
 * @warning
 */
void CMultiServer::Free()
{
    int i;

    for( i=0 ; i < MAX_CLIENTS ; ++i ) {
        free( m_szRcvStat[i].pszLanData );
        free( m_pstLanData[i] );
    }

    delete m_ptheSBC;

}

/**
 * @brief     쓰레드를 실행하게 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 12:04:52
 * @warning
 */
void CMultiServer::Run()
{
    // 소켓 모드 설정
    //m_enSocketMode = enSocketMode;

    CThread::Run();

}

UINT CMultiServer::WinRun( LPVOID pParam )
{

    //CThread::CallBack( pParam );

    return 0;
}

/**
 * @brief     _routine
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 12:15:36
 * @warning
 */
void CMultiServer::_routine()
{
    //LOGENTRY;

    int s, addlen;
    SOCKET iMaxSock;

    fd_set readfd;

    STR_CLIENT_SOCKET stConnectedClientSocket;

    addlen = sizeof( sockaddr_in );

    InitOfTCPIP();

#ifdef __linux__
    bool bHeader[MAX_CLIENTS];
    UINT uiTotalRead[MAX_CLIENTS];

    STR_LAN_HEADER strLanHeader[MAX_CLIENTS];

    int opt = true, addrlen, i, iActivity, iRead;
    int iClientSocket[MAX_CLIENTS];
    int iMasterSocket, iMaxSocket, iSocket, iNewSocket;

    struct sockaddr_in address;

    char *pLanData;

    //set of socket descriptors
    fd_set readfds;

    STR_MessageData sndMsg;

    LOGMSG( enDebug, "[서버] ZYNQ 서버 소켓을 설정 합니다." );

    //initialise all client_socket[] to 0 so not checked
    for( i=0 ; i < MAX_CLIENTS ; i++) {
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
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( m_iPort );

    if( bind( iMasterSocket, (struct sockaddr *)&address, sizeof(address)) < 0 ) {
        perror( "Bind 실패");
    }
    printf( " Listener on port %d\n", m_iPort );

    //try to specify maximum of 3 pending connections for the master socket
    if( listen( iMasterSocket, 3 ) < 0 ) {
        perror( "Listen 실패" );
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts( " Waiting for connections ..." );

    while( true ) {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET( iMasterSocket, &readfds);
        iMaxSocket = iMasterSocket;

        //add child sockets to set
        for( i=0 ; i < MAX_CLIENTS ; i++ ) {
            //socket descriptor
            iSocket = iClientSocket[i];

            //if valid socket descriptor then add to read list
            if( iSocket > 0) {
                FD_SET( iSocket , &readfds);
            }

            //highest file descriptor number, need it for the select function
            if(iSocket > iMaxSocket) {
                iMaxSocket = iSocket;
            }
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        iActivity = select( iMaxSocket + 1 , &readfds , NULL , NULL , NULL);

        if ((iActivity < 0) && (errno!=EINTR) ) {
            perror( "select 에러" );
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(iMasterSocket, &readfds)) {
            if ((iNewSocket = accept(iMasterSocket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0 ) {
                perror( "Accept 실패" );
            }

            //add new socket to array of sockets
            for (i = 0; i < MAX_CLIENTS; i++) {
                //if position is empty
                if( iClientSocket[i] == 0 ) {
                    iClientSocket[i] = iNewSocket;
                    bHeader[i] = true;
                    uiTotalRead[i] = 0;

                    LOGMSG3( enDebug, "연결 성공(%d), ip %s , port %d" , i, inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                    //LOGMSG1( enDebug, "Adding to list of sockets as %d" , i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for ( i = 0; i < MAX_CLIENTS; i++ ) {
            iSocket = iClientSocket[i];

            //Check if it was for closing , and also read the
            //incoming message
            if (FD_ISSET( iSocket , &readfds)) {
                if( bHeader[i] == true ) {
                    pLanData = (char *) & strLanHeader[i];
                    if (( iRead = recv( iSocket , & pLanData[uiTotalRead[i]], sizeof( struct STR_LAN_HEADER)-uiTotalRead[i], MSG_DONTWAIT ) ) == 0 ) {
                        CloseSocket( iSocket, & address, & iClientSocket[i] );
                    }
                    //Echo back the message that came in
                    else {
                        uiTotalRead[i] += iRead;
                        if( uiTotalRead[i] == sizeof( struct STR_LAN_HEADER) ) {
                            bHeader[i] = false;
                            uiTotalRead[i] = 0;
                        }
                    }
                }
                else {
                    pLanData = (char *) & m_pszLanData[i];
                    if (( iRead = recv( iSocket , & pLanData[uiTotalRead[i]], strLanHeader[i].uiLength-uiTotalRead[i], MSG_DONTWAIT ) ) == 0 ) {
                        CloseSocket( iSocket, & address, & iClientSocket[i] );
                    }
                    else {
                        uiTotalRead[i] += iRead;
                        if( uiTotalRead[i] == strLanHeader[i].uiLength ) {
                            bHeader[i] = true;
                            uiTotalRead[i] = 0;

                            sndMsg.mtype = 1;
                            sndMsg.uiOpCode = strLanHeader[i].uiOpCode;
                            sndMsg.iSocket = iSocket;
                            sndMsg.uiDataLength = strLanHeader[i].uiLength;

                            memcpy( & sndMsg.x.szData[0], pLanData, sndMsg.uiDataLength );

                            if( msgsnd( RECZYNQ->GetKeyId(), (void *)& sndMsg, sizeof( struct STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
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
    while( m_bThreadLoop ) {
        FD_ZERO( &readfd );

        FD_SET( m_MasterSock, &readfd );

        iMaxSock = m_MasterSock;
        for( const STR_CLIENT_SOCKET & stClientSocket : m_vClientSock ) {
            FD_SET( stClientSocket.iSocket, &readfd );

            if( stClientSocket.iSocket > iMaxSock ) {
                iMaxSock = stClientSocket.iSocket;
            }
        }

        s = select( (int) ( iMaxSock + 1 ), &readfd, NULL, NULL, NULL );
        if( ( s < 0 ) && ( errno != EINTR ) ) {
            perror( "select error" );
        }

        if( FD_ISSET( m_MasterSock, &readfd ) == 1 ) {
            // 랜 소켓 인증
            stConnectedClientSocket.iSocket = accept( m_MasterSock, ( sockaddr* ) &stConnectedClientSocket.socketAddress, ( socklen_t * ) &addlen );
            if( stConnectedClientSocket.iSocket < 0 ) {
                perror( "accept error" );
                break;
            }

            Connect( & stConnectedClientSocket );
        }
        else {
            for( const STR_CLIENT_SOCKET &stClientSocket : m_vClientSock ) {
                STR_LAN_HEADER *pstLanHeader;
                STR_LAN_DATA *pUniLanData;

                STR_CLIENT_RECVSTAT *pRcvStat;

                pRcvStat = &m_szRcvStat[stClientSocket.iIndex];
                pstLanHeader = ( STR_LAN_HEADER * ) & pRcvStat->pszLanData[stClientSocket.iIndex];
                pUniLanData = m_pstLanData[stClientSocket.iIndex];

                if( FD_ISSET( stClientSocket.iSocket, &readfd ) == 1 ) {
                    int iRead;

                    iRead = recv( stClientSocket.iSocket, ( char * ) & pRcvStat->pszLanData[pRcvStat->iTotalRead], _MAX_LANDATA /*( int ) ( sizeof( struct STR_LAN_HEADER ) - pRcvStat->iTotalRead )*/, MSG_DONTWAIT );
                    if( iRead <= 0 ) {
                        //perror( "recv 에러" );
                        CloseSocket( & stClientSocket );
                        continue;
                    }
                    else {
                        pRcvStat->iTotalRead += iRead;

                        while( true ) {
#ifdef _MSC_VER
                            TRACE( "\nIDX[%d]: DL[%d]", stClientSocket.iIndex, pRcvStat->iTotalRead );
#endif

                            if( pRcvStat->bHeader == false && pRcvStat->iTotalRead >= sizeof( struct STR_LAN_HEADER ) ) {
                                pRcvStat->bHeader = true;

                                // 헤더 복사
                                memcpy( & pUniLanData->stLanHeader, &pRcvStat->pszLanData[0], sizeof( struct STR_LAN_HEADER ) );

                                CCommonUtils::AllSwapData16( & pUniLanData->stLanHeader.usOpCode, ( unsigned int ) sizeof( unsigned short ) );
                                CCommonUtils::AllSwapData32( & pUniLanData->stLanHeader.uiLength, ( unsigned int ) sizeof( unsigned int ) );

                                pRcvStat->iTotalRead -= sizeof( struct STR_LAN_HEADER );
                                memcpy( pRcvStat->pszLanData, & pRcvStat->pszLanData[sizeof( struct STR_LAN_HEADER )], pRcvStat->iTotalRead );
                            }

                            else if( pRcvStat->iTotalRead >= (int) pUniLanData->stLanHeader.uiLength ) {
                                // 데이터 복사
                                memcpy( & pUniLanData->stLanData, pRcvStat->pszLanData, pUniLanData->stLanHeader.uiLength );

                                // 명령 처리
                                ProcessLANMessage( stClientSocket.iIndex );
                                pRcvStat->iTotalRead -= ( (int) pUniLanData->stLanHeader.uiLength );
                                memcpy( pRcvStat->pszLanData, & pRcvStat->pszLanData[pUniLanData->stLanHeader.uiLength], pRcvStat->iTotalRead );

                                pRcvStat->bHeader = false;
                            }
                            else {
#ifdef _MSC_VER
                                TRACE( "\n break while..." );
#endif
                                break;
                            }
                        }
                    }
                }

            }
        }

    }

#endif

}

/**
 * @brief     Connect
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 12:18:14
 * @warning
 */
void CMultiServer::Connect( STR_CLIENT_SOCKET* pClientSocket )
{
    DWORD  dwRet;
    tcp_keepalive tcpkl;
    STR_CLIENT_RECVSTAT *pRecvStat;

    TRACE( "\n멀티서버 연결: 소켓 ID(%d), IP 어드레스(%s), 포트 : %5d\n", pClientSocket->iSocket, inet_ntoa( pClientSocket->socketAddress.sin_addr ), ntohs( pClientSocket->socketAddress.sin_port ) );

    if( true == m_QIndex.Pop( & pClientSocket->iIndex ) ) {
        pRecvStat = &m_szRcvStat[pClientSocket->iIndex];

        pRecvStat->bHeader = false;
        pRecvStat->iTotalRead = 0;

        m_vClientSock.push_back( *pClientSocket );

        // Keep Alive 옵션 설정
        tcpkl.onoff = 1;
        tcpkl.keepalivetime = 2000;         // 2초 마다 KeepAlive 신호를 전송합니다.
        tcpkl.keepaliveinterval = 1000;     // 응답이 없으면, 1초마다 재 전송합니다.

        WSAIoctl( pClientSocket->iSocket, SIO_KEEPALIVE_VALS, & tcpkl, sizeof( tcp_keepalive ), 0, 0, &dwRet, NULL, NULL  );
        if( dwRet != 0  ) {
            AfxMessageBox( "소켓 옵션(KeepAlive)을 설정하는데 에러가 발생합니다." );
        }

    //     if( setsockopt( m_MasterSock, SOL_SOCKET, TCP_KEEPIDLE, ( const char * ) &iOption, sizeof( iOption ) ) < 0 ) {
    //         perror( "소켓 옵션(TCP_KEEPIDLE)" );
    //     }

#ifdef _MSC_VER
        STR_CLIENT_SOCKET stClientSocket;

        memcpy( & stClientSocket, pClientSocket, sizeof( STR_CLIENT_SOCKET ) );
        m_ptheSBC->QMsgSnd( ON_CONNECT, & stClientSocket, sizeof( STR_CLIENT_SOCKET ), GetThreadName() );

#endif
    }
    else {
        AfxMessageBox( "연결 관리가 깨졌습니다 !" );

    }

}

/**
 * @brief     Close
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 12:18:16
 * @warning
 */
void CMultiServer::CloseSocket( const STR_CLIENT_SOCKET *pstClientSocket )
{
    bool bRet = false;
    //STR_CLIENT_SOCKET stClientSocket;

    if( m_vClientSock.size() > 0 ) {
        m_QIndex.Push( pstClientSocket->iIndex  );

        TRACE( "\n멀티서버 단락: 소켓 ID(%d), IP 어드레스(%s), 포트 : %5d\n", pstClientSocket->iSocket, inet_ntoa( pstClientSocket->socketAddress.sin_addr ), ntohs( pstClientSocket->socketAddress.sin_port ) );

        shutdown( pstClientSocket->iSocket, SD_BOTH );
        closesocket( pstClientSocket->iSocket );
        //close( stClientSocket.iSocket );

        // 삭제하기
        int idxClientSock = 0;
        for( const STR_CLIENT_SOCKET stClientSocket : m_vClientSock ) {
            if( stClientSocket.socketAddress.sin_port == pstClientSocket->socketAddress.sin_port ) {
#ifdef _MSC_VER
                m_ptheSBC->QMsgSnd( ON_DISCONNECT, ( void * ) pstClientSocket, sizeof( STR_CLIENT_SOCKET ), GetThreadName() );

#else


#endif

                m_vClientSock.erase( m_vClientSock.begin() + idxClientSock );
                bRet = true;
                break;
            }
            ++ idxClientSock;

        }

        if( bRet == false ) {
            TRACE( "구조가 잘못됨 !" );
        }




    }

}

/**
 * @brief     ProcessLANMessage
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 13:59:20
 * @warning
 */
void CMultiServer::ProcessLANMessage( int iIndex )
{
#ifdef _MSC_VER

    STR_LAN_DATA *pLanData;

    //ProcessLANMessage( m_pstLanData[iIndex] );

    pLanData = m_pstLanData[iIndex];

    TRACE( "\nLanMessage...[0x%x, %d]" , pLanData->stLanHeader.usOpCode, pLanData->stLanHeader.uiLength );
    m_ptheSBC->QMsgSnd( ( unsigned int ) pLanData->stLanHeader.usOpCode, & pLanData->stLanData, pLanData->stLanHeader.uiLength, GetThreadName() );

#endif

}

/**
 * @brief CMySocket::CloseSocket
 * @param iSocket
 * @param pAddress
 * @param pClientSocket
 */
void CMultiServer::CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket )
{

#ifdef __linux__
    int addrlen;

    addrlen = sizeof(sockaddr_in);
    //Somebody disconnected , get his details and print
    getpeername(iSocket , (struct sockaddr*) pAddress , (socklen_t*)&addrlen);
    LOGMSG2( enDebug, "연결 단절: ip %s , port %d" , inet_ntoa(pAddress->sin_addr) , ntohs(pAddress->sin_port));

    //Close the socket and mark as 0 in list for reuse
    close( iSocket );

    if( pClientSocket != NULL ) {
        *pClientSocket = 0;
    }
#endif

}

/**
 * @brief CMultiServer::SendLan
 * @param uiOpCode
 * @param uiLength
 * @param pData
 * @return
 */
int CMultiServer::SendLan( unsigned short usOpCode, void *pData, UINT uiLength )
{
    int iRet1, iRet2=0;
    STR_LAN_HEADER strLanHeader;

    // 랜 헤더 송신
    strLanHeader.ucDestination = 0;
    strLanHeader.ucSource = 0;
    strLanHeader.usOpCode = usOpCode;
    strLanHeader.uiLength = uiLength;

#ifdef __linux__
    iRet1 = send( m_iSocket, (char *) & strLanHeader, sizeof( struct STR_LAN_HEADER), MSG_DONTWAIT );
#else
    iRet1 = 0;
#endif

    if( iRet1 > 0 ) {
#ifdef __linux__
        iRet2 = send( m_iSocket, (char *) pData, strLanHeader.uiLength, MSG_DONTWAIT );
#else
        iRet2 = 0;

#endif
    }
    else {
        perror( "send() 에러");
    }

    return iRet1 + iRet2;

}

/**
 * @brief     SendLan
 * @param     void * pData
 * @param     unsigned int uiLength
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 17:27:00
 * @warning
 */
int CMultiServer::Send( const void *pData, unsigned int uiLength )
{
    int iRet;

    if( m_vClientSock.size() == 0 ) {
        iRet = -1;
    }
    else {
        for( const STR_CLIENT_SOCKET & stClientSocket : m_vClientSock ) {
            iRet = send( stClientSocket.iSocket, ( char * ) pData, uiLength, MSG_DONTWAIT );
        }
    }

    return iRet;
}
