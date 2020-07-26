#include <errno.h>
#include <arpa/inet.h>

#include "csingleserver.h"
#include "./Utils/clog.h"


#include "./Thread/creclan.h"

/**
 * @brief CSingleServer::CSingleServer
 * @param iKeyId
 * @param pClassName
 * @param iPort
 */
CSingleServer::CSingleServer( int iKeyId, char *pClassName, int iPort ) : CThread( iKeyId, pClassName )
{
    m_iPort = iPort;
}


/**
 * @brief CMultiServer::~CMultiServer
 */
CSingleServer::~CSingleServer()
{
    LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );
}

/**
 * @brief CMultiServer::Run
 * @param enSocketMode
 */
void CSingleServer::Run()
{
    // 소켓 모드 설정
    //m_enSocketMode = enSocketMode;

    CThread::Run();

}

/**
 * @brief CMultiServer::_routine
 */
void CSingleServer::_routine()
{
    bool bHeader;
    UINT uiTotalRead;

    STR_LAN_HEADER strLanHeader;
    char szLanData;

    int opt = true, addrlen, iActivity, iRead;
    int iClientSocket;
    int iMasterSocket, iMaxSocket, iNewSocket;

    char *pLanData;

    struct sockaddr_in sockAddress;

    //set of socket descriptors
    fd_set readfds;

    STR_MessageData sndMsg;

    LOGMSG( enDebug, "[서버] CCU 서버로 소켓을 설정 합니다." );

    //initialise all client_socket[] to 0 so not checked
    iClientSocket = 0;

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
                        CloseSocket( m_iSocket, & sockAddress, & iClientSocket );
                    }
                    //Echo back the message that came in
                    else {
                        uiTotalRead += iRead;
                        if( uiTotalRead == sizeof(STR_LAN_HEADER) ) {
                            bHeader = false;
                            uiTotalRead = 0;
                        }
                    }
                }
                else {
                    pLanData = (char *) & szLanData;
                    if (( iRead = recv( m_iSocket , & pLanData[uiTotalRead], strLanHeader.uiLength-uiTotalRead, MSG_DONTWAIT ) ) == 0 ) {
                        CloseSocket( m_iSocket, & sockAddress, & iClientSocket );
                    }
                    else {
                        uiTotalRead += iRead;
                        if( uiTotalRead == strLanHeader.uiLength ) {
                            bHeader = true;
                            uiTotalRead = 0;

                            sndMsg.mtype = 1;
                            sndMsg.opCode = strLanHeader.opCode;
                            sndMsg.iSocket = m_iSocket;
                            sndMsg.iLength = strLanHeader.uiLength;

                            memcpy( & sndMsg.szMessage[0], pLanData, strLanHeader.uiLength );

                            if( msgsnd( RECCCU->GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
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
 * @brief CMySocket::CloseSocket
 * @param iSocket
 * @param pAddress
 * @param pClientSocket
 */
void CSingleServer::CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket )
{
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

}

/**
 * @brief CRecLan::SendQMessage
 */
int CSingleServer::SendLan( UINT uiOpCode, UINT uiLength, void *pData )
{
    int iRet1, iRet2;
    STR_LAN_HEADER strLanHeader;

    // 랜 헤더 송신
    strLanHeader.opCode = uiOpCode;
    strLanHeader.uiLength = uiLength;

    iRet1 = send( m_iSocket, (char *) & strLanHeader, sizeof(STR_LAN_HEADER), MSG_DONTWAIT );

    if( iRet1 > 0 ) {
        iRet2 = send( m_iSocket, (char *) pData, strLanHeader.uiLength, MSG_DONTWAIT );
    }
    else {
        perror( "send() 에러");
    }

    return iRet1 + iRet2;

}
