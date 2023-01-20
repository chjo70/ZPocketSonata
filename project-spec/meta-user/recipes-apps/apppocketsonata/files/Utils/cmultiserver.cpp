#include "stdafx.h"

#include <errno.h>

#ifdef __linux__
#include <arpa/inet.h>
#endif


#include "cmultiserver.h"


// #include "../Thread/csi.h"

#include "../Include/globals.h"

/**
 * @brief CMultiServer::CMultiServer
 * @param iKeyId
 * @param pClassName
 */
CMultiServer::CMultiServer( int iKeyId, char *pClassName, int iPort ) : CThread( iKeyId, pClassName, false )
{
    m_iPort = iPort;

    Init();
}

/**
 * @brief CMultiServer::~CMultiServer
 */
CMultiServer::~CMultiServer()
{
    LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );

    Free();
}

/**
 * @brief CMultiServer::Init
 */
void CMultiServer::Init()
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
 * @brief CMultiServer::Alloc
 */
void CMultiServer::Alloc()
{
    int i;

    for( i=0 ; i < MAX_CLIENTS ; ++i ) {
        m_pszLanData[i] = ( char * ) malloc( sizeof(char) * _MAX_LANDATA );
    }

}

/**
 * @brief CMultiServer::Free
 */
void CMultiServer::Free()
{
    int i;

    for( i=0 ; i < MAX_CLIENTS ; ++i ) {
        free( m_pszLanData[i] );
    }

}

/**
 * @brief CMultiServer::Run
 * @param enSocketMode
 */
void CMultiServer::Run( key_t key )
{
    // 소켓 모드 설정
    //m_enSocketMode = enSocketMode;

    CThread::Run( key );

}

/**
 * @brief CMultiServer::_routine
 */
void CMultiServer::_routine()
{
    LOGENTRY;

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
    while( true ) {
        sleep( 1000 );
    }


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
    int addrlen;

#ifdef __linux__
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
