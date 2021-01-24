#include <errno.h>
#include <arpa/inet.h>


#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#include "csingleclient.h"

#include "../Thread/creclan.h"
#include "../Thread/ctaskmngr.h"
#include "../Utils/clog.h"


#include "../Utils/ccommonutils.h"

/**
 * @brief CSingleClient::CSingleServer
 * @param iKeyId
 * @param pClassName
 * @param iPort
 */
CSingleClient::CSingleClient( int iKeyId, char *pClassName, int iPort, char *pServerAddress ) : CThread( iKeyId, pClassName )
{
    int i=0;

    m_iPort = iPort;

    if( pServerAddress == NULL ) {
        m_bServer = true;
        m_szServerAddress[i][0] = 0;
    }
    else {
        m_bServer = false;
        strcpy( m_szServerAddress[i], pServerAddress );
    }

    ++i;
    strcpy( m_szServerAddress[i], HOST_SERVER );
    ++i;
    strcpy( m_szServerAddress[i], DEV_SERVER );
    ++i;
    strcpy( m_szServerAddress[i], DEV2_SERVER );

    Init();
}


/**
 * @brief CSingleClient::~CMultiServer
 */
CSingleClient::~CSingleClient()
{
    LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );

    Free();
}

/**
 * @brief CSingleServer::Init
 */
void CSingleClient::Init()
{
    Alloc();

    if( m_iPort == CCU_PORT ) {
        m_ptheRecLan = RECCCU;
    }
    else if( m_iPort == PORT ) {
        m_ptheRecLan = RECZYNQ;
    }
    else {
        m_ptheRecLan = NULL;
    }

}

/**
 * @brief CSingleServer::Alloc
 */
void CSingleClient::Alloc()
{
    m_pszLanData = ( char * ) malloc( sizeof(char) * _MAX_LANDATA );

}

/**
 * @brief CMultiServer::Free
 */
void CSingleClient::Free()
{

    free( m_pszLanData );

}

/**
 * @brief CMultiServer::Run
 * @param enSocketMode
 */
void CSingleClient::Run( key_t key )
{
    // 소켓 모드 설정
    //m_enSocketMode = enSocketMode;

    CThread::Run( key );

}

/**
 * @brief CMultiServer::_routine
 */
void CSingleClient::_routine()
{

    if( m_bServer == true ) {
        LOGMSG( enDebug, "[서버] 소켓을 설정 합니다." );
        RunServer();
    }
    else {
        int i, iIndex=0;
        char buffer[100];

        for( i=0 ; i < NUM_OF_SERVER-1 ; ++i ) {
            iIndex += sprintf( & buffer[iIndex], "%s/" , m_szServerAddress[i] );
        }
        sprintf( & buffer[iIndex], "%s" , m_szServerAddress[i] );

        LOGMSG2( enDebug, "[클라이언트] [%s,%d] 연결하려 합니다.", buffer, m_iPort );
        RunClient();
    }

}

/**
 * @brief CSingleClient::RunClient
 */
void CSingleClient::RunClient()
{
    int iServerSwitch=0;
    bool bHeader;
    UINT uiTotalRead;

    STR_LAN_HEADER strLanHeader;

    int iActivity, iRead;
    int iMaxSocket;

    char *pLanData;

    struct sockaddr_in sockAddress;

    m_pMsg = GetDataMessage();

    //set of socket descriptors
    fd_set readfds;

    STR_MessageData sndMsg;

    //initialise all client_socket[] to 0 so not checked
    m_iSocket = 0;

    m_bConnected = false;

    while( true ) {
        iServerSwitch = ( iServerSwitch+1 >= NUM_OF_SERVER ? iServerSwitch=0 : iServerSwitch+1 );

        LOGMSG2( enDebug, "[클라이언트] [%s/%d] 연결하려 합니다.", m_szServerAddress[iServerSwitch], m_iPort );

        //type of socket created
        bzero((char *)&sockAddress, sizeof(sockAddress));
        sockAddress.sin_family = AF_INET;
        sockAddress.sin_addr.s_addr = inet_addr(m_szServerAddress[iServerSwitch] );
        sockAddress.sin_port = htons( m_iPort );

        //create a master socket
        if( ( m_iSocket = socket( AF_INET, SOCK_STREAM, 0 ) ) == 0 ) {
            perror( "Master Socket 실패" );
            continue;
        }

        //set master socket to allow multiple connections ,
        //this is just a good habit, it will work without this
        int sizeOfLanBuf = 10240;
        if( setsockopt( m_iSocket, SOL_SOCKET, SO_SNDBUF, (char *)&sizeOfLanBuf, sizeof(sizeOfLanBuf)) < 0 ) {
            perror( "Master Socket 소켓 옵션");
        }
        if( setsockopt( m_iSocket, SOL_SOCKET, SO_RCVBUF, (char *)&sizeOfLanBuf, sizeof(sizeOfLanBuf)) < 0 ) {
            perror( "Master Socket 소켓 옵션");
        }

        //LOGMSG2( enDebug, "Try Connection to [%s/%d]...", m_szServerAddress, m_iPort );
        if( ConnectTimeout( m_iSocket, & sockAddress, 10 ) < 0 ) {
            sleep( 1 );
        }
        else {
            LOGMSG2( enDebug, "[%s/%d]으로 연결 성공했습니다.", m_szServerAddress[iServerSwitch], m_iPort );
            bHeader = true;
            uiTotalRead = 0;

            while( true ) {
                //clear the socket set
                FD_ZERO(&readfds);

                //add master socket to set
                FD_SET( m_iSocket, &readfds);
                iMaxSocket = m_iSocket;

                //wait for an activity on one of the sockets , timeout is NULL ,
                //so wait indefinitely
                iActivity = select( iMaxSocket + 1 , &readfds , NULL , NULL , NULL);

                if ((iActivity < 0) && (errno!=EINTR) ) {
                    perror( "select 에러" );
                    OnDisconnected( & m_szServerAddress[iServerSwitch][0] );
                    break;
                }

                if( bHeader == true ) {
                    pLanData = (char *) & strLanHeader;
                    iRead = recv( m_iSocket , & pLanData[uiTotalRead], sizeof(STR_LAN_HEADER)-uiTotalRead, MSG_DONTWAIT );
                    if( iRead == 0 ) {
                        perror( "recv 에러" );
                        OnDisconnected( & m_szServerAddress[iServerSwitch][0] );
                        break;
                    }
                    //Echo back the message that came in
                    else {
                        CCommonUtils::AllSwapData32( & pLanData[uiTotalRead], iRead );
                        uiTotalRead += iRead;
                        if( uiTotalRead == sizeof(STR_LAN_HEADER) ) {
                            if( strLanHeader.uiLength == 0 ) {
                                bHeader = true;
                                uiTotalRead = 0;

                                sndMsg.mtype = 1;
                                sndMsg.uiOpCode = strLanHeader.uiOpCode;
                                sndMsg.iSocket = m_iSocket;
                                sndMsg.iArrayIndex = -1;
                                sndMsg.uiArrayLength = 0;
                                sndMsg.uiDataLength = 0;

                                if( msgsnd( m_ptheRecLan->GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
                                    perror( "msgsnd 실패" );
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
                    pLanData = (char *) & m_pszLanData[0];
                    if (( iRead = recv( m_iSocket , & pLanData[uiTotalRead], strLanHeader.uiLength-uiTotalRead, MSG_DONTWAIT ) ) == 0 ) {
                        perror( "recv 에러" );
                        OnDisconnected( & m_szServerAddress[iServerSwitch][0] );
                        break;
                    }
                    else {
                        CCommonUtils::AllSwapData32( & pLanData[uiTotalRead], iRead );
                        uiTotalRead += iRead;
                        if( uiTotalRead == strLanHeader.uiLength ) {
                            bHeader = true;
                            uiTotalRead = 0;

                            sndMsg.mtype = 1;
                            sndMsg.uiOpCode = strLanHeader.uiOpCode;
                            sndMsg.iSocket = m_iSocket;
                            sndMsg.iArrayIndex = -1;
                            sndMsg.uiArrayLength = 0;
                            sndMsg.uiDataLength = 0;

                            if( strLanHeader.uiLength < sizeof(UNI_MSG_DATA) ) {
                                sndMsg.uiDataLength = strLanHeader.uiLength;
                                memcpy( & sndMsg.x.szData[0], pLanData, sndMsg.uiDataLength );
                            }
                            else {
                                sndMsg.uiArrayLength = strLanHeader.uiLength;
                                sndMsg.iArrayIndex = m_ptheRecLan->PushLanData( pLanData, sndMsg.uiArrayLength );
                            }

/*
 *                             if( sndMsg.uiOpCode == enREQ_SIM_PDWDATA || sndMsg.uiOpCode == enREQ_IPL_DOWNLOAD || sndMsg.uiOpCode == enREQ_SET_CONFIG ) {
                                sndMsg.uiArrayLength = strLanHeader.uiLength;
                                sndMsg.iArrayIndex = m_ptheRecLan->PushLanData( pLanData, sndMsg.uiArrayLength );
                            }
                            else {
                                if( strLanHeader.uiLength < sizeof(UNI_MSG_DATA) ) {
                                    sndMsg.uiDataLength = strLanHeader.uiLength;
                                    memcpy( & sndMsg.x.szData[0], pLanData, sndMsg.uiDataLength );
                                }
                                else {
                                    LOGMSG1( enError, "랜 수신 데이터(0x%x)를 초과했습니다. PushLanData()를 이용해서 저장해야 합니다. !!", m_pMsg->uiOpCode );
                                }
                            }           */

                            if( msgsnd( m_ptheRecLan->GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
                                perror( "msgsnd 실패" );
                            }
                            else {
                                if( sndMsg.uiOpCode == enREQ_MODE && sndMsg.x.uiData == enREADY_MODE ) {
                                   // LOGMSG( enError, "대기 명령으로 소켓을 닫습니다." );
                                   // break;
                                }
                                // DisplayMsg( & sndMsg );

                            }

                        }
                    }
                }
            }

            // LOGMSG2( enDebug, "[서버] 클라이언트로 [%s/%d] 재연결하려 합니다.", m_szServerAddress[iServerSwitch], m_iPort );
        }

        // 소켓을 닫는다.
        CloseSocket();

    }
}

/**
 * @brief CSingleClient::OnDisconnected
 */
void CSingleClient::OnDisconnected( char *pServerIPAddress )
{
    STR_MessageData sndMsg;

    CloseSocket();

    LOGMSG1( enError, "서버(%s)가 끊겼습니다.", pServerIPAddress );

    sndMsg.mtype = 1;
    sndMsg.uiOpCode = enREQ_MODE;
    sndMsg.iSocket = m_iSocket;
    sndMsg.iArrayIndex = -1;
    sndMsg.uiArrayLength = 0;
    sndMsg.uiDataLength = sizeof(int);

    sndMsg.x.uiData = enREADY_MODE;

    if( msgsnd( m_ptheRecLan->GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
        perror( "msgsnd 실패" );
    }

}

/**
 * @brief CSingleClient::ConnectTimeout
 * @param sock
 * @param res
 * @param timeout_milli
 * @return
 */
int CSingleClient::ConnectTimeout( int sock, struct sockaddr_in *pAddr, unsigned long timeout_milli )
{
    int iRet=0, err;
    socklen_t len;
    fd_set writefds;
    struct timeval timeout;
    int flags;

    FD_ZERO(&writefds);
    flags = fcntl(sock, F_GETFL);
    flags = (flags | O_NONBLOCK);
    if(fcntl(sock, F_SETFL, flags) != 0) {
        perror( "fcntl() error" );
        iRet = -1;
    }
    else {
        if(connect(sock, (struct sockaddr *) pAddr, sizeof(sockaddr_in) ) != 0 ) {
            if (errno != EINPROGRESS) {
                perror("connect() error\n");
                iRet = -1;
            }
        }

        timeout.tv_sec = timeout_milli / 1000;
        timeout.tv_usec = (timeout_milli % 1000) * 1000;
        FD_SET(sock, &writefds);
        if(select(sock+1, NULL, &writefds, NULL, &timeout) <= 0 ) {
            //perror("connection timeout\n");
            iRet = -1;
        }
        else {
            len = sizeof(err);
            getsockopt(sock, SOL_SOCKET, SO_ERROR, (char *)&err, &len);
            if (err) {
                //perror( "getsockopt()" );
                iRet = -1;
            }

            fcntl(sock, F_GETFL);
            flags = (flags & ~O_NONBLOCK);
            if (fcntl(sock, F_SETFL, flags) != 0) {
                perror( "fcntl() error" );
                iRet = -1;
            }
        }
    }

    if( iRet != -1 ) {
        m_bConnected = true;
        OnConnect( pAddr );
    }

    return iRet;
}


/**
 * @brief CSingleClient::RunServer
 */
void CSingleClient::RunServer()
{
    bool bHeader;
    UINT uiTotalRead;

    STR_LAN_HEADER strLanHeader;

    int opt = true, addrlen, iActivity, iRead;
    int iClientSocket;
    int iMasterSocket, iMaxSocket, iNewSocket;

    char *pLanData;

    struct sockaddr_in sockAddress;

    m_pMsg = GetDataMessage();

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
        {
            //socket descriptor
            m_iSocket = iClientSocket;

            //if valid socket descriptor then add to read list
            if( m_iSocket > 0) {
                FD_SET( m_iSocket , &readfds);
            }

            //highest file descriptor number, need it for the select function
            if(m_iSocket > iMaxSocket) {
                iMaxSocket = m_iSocket;
            }
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        iActivity = select( iMaxSocket + 1 , &readfds , NULL , NULL , NULL);

        if ((iActivity < 0) && (errno!=EINTR) ) {
            perror( "select 에러" );
            //break;
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(iMasterSocket, &readfds)) {
            if ((iNewSocket = accept(iMasterSocket, (struct sockaddr *)&sockAddress, (socklen_t*)&addrlen)) < 0 ) {
                perror( "Accept 실패" );
            }
            else {
                //if position is empty
                iClientSocket = iNewSocket;
                bHeader = true;
                uiTotalRead = 0;

                LOGMSG2( enDebug, "연결 성공: ip %s , port %d" , inet_ntoa(sockAddress.sin_addr) , ntohs(sockAddress.sin_port));
            }
        }

        //else its some IO operation on some other socket
        {
            m_iSocket = iClientSocket;

            //Check if it was for closing , and also read the
            //incoming message
            if (FD_ISSET( m_iSocket , &readfds)) {
                if( bHeader == true ) {
                    pLanData = (char *) & strLanHeader;
                    if (( iRead = recv( m_iSocket , & pLanData[uiTotalRead], sizeof(STR_LAN_HEADER)-uiTotalRead, MSG_DONTWAIT ) ) == 0 ) {
                        CloseSocket( & sockAddress, & iClientSocket );
                    }
                    //Echo back the message that came in
                    else {
                        uiTotalRead += iRead;
                        if( uiTotalRead == sizeof(STR_LAN_HEADER) ) {
                            if( strLanHeader.uiLength == 0 ) {
                                bHeader = true;
                                uiTotalRead = 0;

                                sndMsg.mtype = 1;
                                sndMsg.uiOpCode = strLanHeader.uiOpCode;
                                sndMsg.iSocket = m_iSocket;
                                sndMsg.iArrayIndex = -1;
                                sndMsg.uiArrayLength = 0;
                                sndMsg.uiDataLength = 0;

                                if( msgsnd( m_ptheRecLan->GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
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
                    pLanData = (char *) & m_pszLanData[0];
                    if (( iRead = recv( m_iSocket , & pLanData[uiTotalRead], strLanHeader.uiLength-uiTotalRead, MSG_DONTWAIT ) ) == 0 ) {
                        CloseSocket( & sockAddress, & iClientSocket );
                    }
                    else {
                        uiTotalRead += iRead;
                        if( uiTotalRead == strLanHeader.uiLength ) {
                            bHeader = true;
                            uiTotalRead = 0;

                            sndMsg.mtype = 1;
                            sndMsg.uiOpCode = strLanHeader.uiOpCode;
                            sndMsg.iSocket = m_iSocket;
                            sndMsg.iArrayIndex = -1;
                            sndMsg.uiArrayLength = 0;
                            sndMsg.uiDataLength = 0;

                            if( strLanHeader.uiLength < sizeof(UNI_MSG_DATA) ) {
                                sndMsg.uiDataLength = strLanHeader.uiLength;
                                memcpy( & sndMsg.x.szData[0], pLanData, sndMsg.uiDataLength );
                            }
                            else {
                                sndMsg.uiArrayLength = strLanHeader.uiLength;
                                sndMsg.iArrayIndex = m_ptheRecLan->PushLanData( pLanData, sndMsg.uiArrayLength );
                            }

                            if( msgsnd( m_ptheRecLan->GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
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
}

/**
 * @brief CSingleClient::OnConnect
 * @param pAddr
 */
void CSingleClient::OnConnect( struct sockaddr_in *pAddr )
{
    char *pIPAddress;

    if( pAddr != NULL ) {
        pIPAddress = inet_ntoa( pAddr->sin_addr );
        GP_SYSCFG->SetPrimeServerOfNetwork( pIPAddress, true );
    }

}

/**
 * @brief CSingleClient::CloseSocket
 * @param iSocket
 * @param pAddress
 * @param pClientSocket
 */
void CSingleClient::CloseSocket( struct sockaddr_in *pAddress, int *pClientSocket )
{
    int addrlen;

    addrlen = sizeof(sockaddr_in);
    //Somebody disconnected , get his details and print
    getpeername( m_iSocket , (struct sockaddr*) pAddress , (socklen_t*)&addrlen);
    LOGMSG2( enDebug, "연결 단절: ip %s , port %d" , inet_ntoa(pAddress->sin_addr) , ntohs(pAddress->sin_port));

    //Close the socket and mark as 0 in list for reuse
    CloseSocket();

    if( pClientSocket != NULL ) {
        *pClientSocket = 0;
    }

    UINT uiMode=enREADY_MODE;
    QMsgSnd( TMNGR->GetKeyId(), enREQ_MODE, & uiMode, sizeof(int) );

}

/**
 * @brief CSingleClient::SendLan
 */
int CSingleClient::SendLan( UINT uiOpCode, void *pData, UINT uiDataLength )
{
    int iRet;

    if( IsConnected() == true ) {
        int iRet1, iRet2=0;

        // 랜 헤더 송신
        m_strLanHeader.uiOpCode = uiOpCode;
        m_strLanHeader.uiLength = uiDataLength;

        CCommonUtils::AllSwapData32( & m_strLanHeader, sizeof(STR_LAN_HEADER) );
        iRet1 = send( m_iSocket, (char *) & m_strLanHeader, sizeof(STR_LAN_HEADER), MSG_DONTWAIT );
        CCommonUtils::AllSwapData32( & m_strLanHeader, sizeof(STR_LAN_HEADER) );

        if( iRet1 > 0 && uiDataLength != 0 ) {
            CCommonUtils::AllSwapData32( pData, uiDataLength );
            iRet2 = send( m_iSocket, (char *) pData, uiDataLength, MSG_DONTWAIT );
            CCommonUtils::AllSwapData32( pData, uiDataLength );

            m_puiData = (unsigned int *) pData;
            DisplayMsg();

        }
        else {
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
 * @brief CSingleClient::DisplayMsg
 */
void CSingleClient::DisplayMsg()
{
    char szOpcode[50];

    switch( m_strLanHeader.uiOpCode ) {
        case enRES_MODE :
            strcpy( szOpcode, "운용 모드" );
            break;

        // 분석 관련 메시지
        case enRES_IBIT :
            strcpy( szOpcode, "초기자체점검" );
            break;

        case enRES_UBIT :
            strcpy( szOpcode, "장비자체점검" );
            break;

        case enRES_CBIT :
            strcpy( szOpcode, "연속자체점검" );
            break;

        // 분석 관련 메시지
        case esAET_NEW_CCU :
            strcpy( szOpcode, "신규" );
            break;

        case esAET_UPD_CCU :
            strcpy( szOpcode, "변경" );
            break;

        case esAET_LST_CCU :
            strcpy( szOpcode, "소실" );
            break;

        case esAET_DEL_CCU :
            strcpy( szOpcode, "삭제" );
            break;

        // IPL 관련 메시지
        case esIPL_VERSION :
            strcpy( szOpcode, "IPL 버젼" );
            break;

        case esIPL_WRITESTATUS :
            strcpy( szOpcode, "IPL 기록상태" );
            break;

        default :
            strcpy( szOpcode, "이름 없음" );
            break;
    }

    LOGMSG4( enDebug, "$랜 송신: Op[%s:0x%04X], Len[%d], Data32[0x%x]" , szOpcode, m_strLanHeader.uiOpCode, m_strLanHeader.uiLength, *m_puiData );

}

/**
 * @brief CSingleClient::SocketClose
 * @return
 */
void CSingleClient::CloseSocket()
{
    m_bConnected = false;

    if( m_iSocket > 0 ) {
        LOGMSG( enNormal, "소켓을 정상적으로 닫습니다." );
        close( m_iSocket );
    }
    else {
        LOGMSG( enError, "두번 이상 소켓을 닫았습니다." );
    }

    m_iSocket = -1;

}
