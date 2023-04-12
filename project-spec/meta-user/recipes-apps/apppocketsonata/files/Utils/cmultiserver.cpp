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
#endif


#include "cmultiserver.h"

#include "ccommonutils.h"
// #include "../Include/globals.h"

/**
 * @brief CMultiServer::CMultiServer
 * @param iKeyId
 * @param pClassName
 */
CMultiServer::CMultiServer( int iKeyId, char *pClassName, int iPort ) : CThread( iKeyId, pClassName, false )
{
    m_iPort = iPort;

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
    m_vClientSock.reserve( MAX_CLIENTS );

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
        sizeOfLanBuf = 1024;
        setsockopt( m_MasterSock, SOL_SOCKET, SO_SNDBUF, ( char* ) &sizeOfLanBuf, sizeof( sizeOfLanBuf ) );
        setsockopt( m_MasterSock, SOL_SOCKET, SO_RCVBUF, ( char* ) &sizeOfLanBuf, sizeof( sizeOfLanBuf ) );

//         struct STR_TCP_KEEPALIVE tcpkl;
//         tcpkl.onoff = 1;
//         tcpkl.keepalivetime = 5500;
//         tcpkl.keepaliveinterval = 3000;

        if( setsockopt( m_MasterSock, SOL_SOCKET, TCP_KEEPIDLE, ( const char * ) &iOption, sizeof( iOption ) ) < 0 ) {
            perror( "소켓 옵션(TCP_KEEPIDLE)" );
        }

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
        m_pstLanData[i] = ( STR_LAN_DATA * ) malloc( sizeof( STR_LAN_DATA ) );
    }



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

    UINT uiDataLength;

    fd_set writefd, readfd, exceptfd;

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
                    if (( iRead = recv( iSocket , & pLanData[uiTotalRead[i]], sizeof(STR_LAN_HEADER)-uiTotalRead[i], MSG_DONTWAIT ) ) == 0 ) {
                        CloseSocket( iSocket, & address, & iClientSocket[i] );
                    }
                    //Echo back the message that came in
                    else {
                        uiTotalRead[i] += iRead;
                        if( uiTotalRead[i] == sizeof(STR_LAN_HEADER) ) {
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

                            if( msgsnd( RECZYNQ->GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
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
        //clear the socket set
        FD_ZERO( &readfd );

        //add master socket to set
        FD_SET( m_MasterSock, &readfd );

        iMaxSock = m_MasterSock;
        for( const STR_CLIENT_SOCKET & stClientSocket : m_vClientSock ) {
            //if valid socket descriptor then add to read list
            FD_SET( stClientSocket.iSocket, &readfd );

            //highest file descriptor number, need it for the select function
            if( stClientSocket.iSocket > iMaxSock ) {
                iMaxSock = stClientSocket.iSocket;
            }
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        s = select( iMaxSock + 1, &readfd, NULL, NULL, NULL );
        if( ( s < 0 ) && ( errno != EINTR ) ) {
            perror( "select error" );
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if( FD_ISSET( m_MasterSock, &readfd ) == 1 ) {
            // 랜 소켓 인증
            stConnectedClientSocket.iSocket = accept( m_MasterSock, ( sockaddr* ) &stConnectedClientSocket.socketAddress, ( socklen_t * ) &addlen );
            if( stConnectedClientSocket.iSocket < 0 ) {
                perror( "accept error" );
                break;
            }

            //inform user of socket number - used in send and receive commands
            Connect( & stConnectedClientSocket );

        }
        else {
            int iIndex = 0;
            for( const STR_CLIENT_SOCKET &stClientSocket : m_vClientSock ) {
                STR_CLIENT_RECVSTAT *pRcvStat;

                pRcvStat = &m_szRcvStat[iIndex];
                if( FD_ISSET( stClientSocket.iSocket, &readfd ) == 1 ) {
                    int iRead;

                    if( pRcvStat->bHeader == true ) {

                        if( ( int ) ( sizeof( STR_LAN_HEADER ) - pRcvStat->iTotalRead ) >= 1 ) {
                            iRead = recv( stClientSocket.iSocket, ( char * ) & pRcvStat->pszLanData[pRcvStat->iTotalRead], ( int ) ( sizeof( STR_LAN_HEADER ) - pRcvStat->iTotalRead ), MSG_DONTWAIT );
                            if( iRead <= 0 ) {
                                perror( "recv 에러" );
                                CloseSocket( iIndex );
                                continue;
                            }
                            else {
                                pRcvStat->iTotalRead += iRead;
                                if( pRcvStat->iTotalRead == sizeof( STR_LAN_HEADER ) ) {
                                    STR_LAN_HEADER *pstLanHeader;

                                    pstLanHeader = ( STR_LAN_HEADER * ) & pRcvStat->pszLanData[0];
                                    uiDataLength = pstLanHeader->uiLength;
                                    CCommonUtils::AllSwapData32( &pRcvStat->pszLanData[0], ( unsigned int ) sizeof( STR_LAN_HEADER ) );

                                    memcpy( &m_pstLanData[iIndex]->stLanHeader, &pRcvStat->pszLanData[0], sizeof( STR_LAN_HEADER ) );

                                    if( pstLanHeader->uiLength == 0 ) {
                                        pRcvStat->bHeader = true;
                                        pRcvStat->iTotalRead = 0;

                                        // 명령 처리
                                        ProcessLANMessage( iIndex );

                                    }
                                    else {
                                        pRcvStat->bHeader = false;
                                        pRcvStat->iTotalRead = 0;
                                    }

                                }
                            }
                        }
                        else {

                        }
                    }
                    else {
                        int iRemaindedByte = (int) m_pstLanData[iIndex]->stLanHeader.uiLength - pRcvStat->iTotalRead;
                        if( iRemaindedByte >= 1 ) {
                            iRead = recv( stClientSocket.iSocket, &pRcvStat->pszLanData[pRcvStat->iTotalRead], iRemaindedByte, MSG_DONTWAIT );

                            TRACE( "[D%d]", iRead );
                            if( iRead <= 0 ) {
                                perror( "recv 에러" );
                                CloseSocket( iIndex );
                                break;
                            }
                            else {
                                pRcvStat->iTotalRead += iRead;
                                if( pRcvStat->iTotalRead == m_pstLanData[iIndex]->stLanHeader.uiLength ) {
                                    // CCommonUtils::AllSwapData32( &pRcvStat->pszLanData[0], ( unsigned int ) pRcvStat->iTotalRead );

                                    memcpy( &m_pstLanData[iIndex]->stLanData, &pRcvStat->pszLanData[0], pRcvStat->iTotalRead );

                                    // 명령 처리
                                    ProcessLANMessage( iIndex );

                                    pRcvStat->bHeader = true;
                                    pRcvStat->iTotalRead = 0;

                                }
#ifdef _WIN32
                                // CCommonUtils::AllSwapData32( &pLanData[pRcvStat->iTotalRead], ( unsigned int ) iRead );
#endif

                            }


                        }
                        else {
                            TRACE( "\n ... " );
//                             iRead = recv( stClientSocket.iSocket, m_pszLanData, ( int ) _MAX_LANDATA, MSG_DONTWAIT );
//                             if( iRead <= 0 ) {
//                                 LOGMSG( enError, "recv()::data 부분에서 데이터 길이가 잘못됐습니다 !" );
//                                 perror( "recv()::data 부분에서 데이터 길이가 잘못됐습니다 !!" );
//                                 break;
//                             }

                        }
                    }
                }

                ++iIndex;
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
    STR_CLIENT_RECVSTAT *pRecvStat;

    TRACE( "연결: 소켓 ID(%d), IP 어드레스(%s), 포트 : %5d\n", pClientSocket->iSocket, inet_ntoa( pClientSocket->socketAddress.sin_addr ), ntohs( pClientSocket->socketAddress.sin_port ) );

    int iSize = m_vClientSock.size();

    pRecvStat = &m_szRcvStat[iSize];

    pRecvStat->bHeader = true;
    pRecvStat->iTotalRead = 0;

    m_vClientSock.push_back( *pClientSocket );

#ifdef _MFC_VER
    ConnectMessage( pClientSocket );

#endif

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
void CMultiServer::CloseSocket( int idxClientSock )
{
    STR_CLIENT_SOCKET stClientSocket;

    if( m_vClientSock.size() > 0 ) {
        stClientSocket = m_vClientSock.at( idxClientSock );
        TRACE( "단락: 소켓 ID(%d), IP 어드레스(%s), 포트 : %5d\n", stClientSocket.iSocket, inet_ntoa( stClientSocket.socketAddress.sin_addr ), ntohs( stClientSocket.socketAddress.sin_port ) );

        shutdown( stClientSocket.iSocket, SD_BOTH );
        closesocket( stClientSocket.iSocket );
        //close( stClientSocket.iSocket );
        m_vClientSock.erase( m_vClientSock.begin() + idxClientSock );

#ifdef _MFC_VER
        DisConnectMessage( &stClientSocket );

#endif
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
#ifdef _MFC_VER
    ProcessLANMessage( m_pstLanData[iIndex] );

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
int CMultiServer::SendLan( UINT uiOpCode, void *pData, UINT uiLength )
{
    int iRet1, iRet2=0;
    STR_LAN_HEADER strLanHeader;

    // 랜 헤더 송신
    strLanHeader.uiOpCode = uiOpCode;
    strLanHeader.uiLength = uiLength;

#ifdef __linux__
    iRet1 = send( m_iSocket, (char *) & strLanHeader, sizeof(STR_LAN_HEADER), MSG_DONTWAIT );
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
