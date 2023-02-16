#include <errno.h>

#ifdef __linux__
#include <arpa/inet.h>
#elif __VXWORKS__
#include <sys/select.h>

#endif

#include "csingleserver.h"

#include "../Thread/creclan.h"
#include "../Thread/ctaskmngr.h"


#include "../Utils/ccommonutils.h"

#include "../Include/globals.h"

/**
 * @brief CSingleServer::CSingleServer
 * @param iKeyId
 * @param pClassName
 * @param iPort
 */
CSingleServer::CSingleServer( int iKeyId, char *pClassName, int iPort ) : CThread( iKeyId, pClassName )
{
    m_iPort = iPort;

    Init();
}


/**
 * @brief CMultiServer::~CMultiServer
 */
CSingleServer::~CSingleServer()
{
    LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );

    Free();
}

/**
 * @brief CSingleServer::Init
 */
void CSingleServer::Init()
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
void CSingleServer::Alloc()
{
    m_pszLanData = ( char * ) malloc( sizeof(char) * _MAX_LANDATA );

}

/**
 * @brief CMultiServer::Free
 */
void CSingleServer::Free()
{

    free( m_pszLanData );

}

/**
 * @brief CMultiServer::Run
 * @param enSocketMode
 */
void CSingleServer::Run( key_t key )
{
    // 소켓 모드 설정
    //m_enSocketMode = enSocketMode;

    CThread::Run( key );

}

/**
 * @brief CMultiServer::_routine
 */
void CSingleServer::_routine()
{
#ifdef __MINGW32__
    while( true ) {
        sleep( 10000 );
    }

#else
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
                            if( strLanHeader.uiLength == 0 ) {
                                bHeader = true;
                                uiTotalRead = 0;

#ifdef __linux__                                
                                sndMsg.mtype = 1;
#endif                                
                                sndMsg.uiOpCode = strLanHeader.uiOpCode;
                                sndMsg.uiSocket = m_iSocket;
                                sndMsg.iArrayIndex = -1;
                                sndMsg.uiArrayLength = 0;
                                sndMsg.uiDataLength = 0;

#ifdef __linux__                                
                                if( msgsnd( m_ptheRecLan->GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
                                    perror( "msgsnd 실패" );
                                }
                                else {
                                    // DisplayMsg( & sndMsg );
                                }
#else
                                
#endif

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
                        CloseSocket( m_iSocket, & sockAddress, & iClientSocket );
                    }
                    else {
                        uiTotalRead += iRead;
                        if( uiTotalRead == strLanHeader.uiLength ) {
                            bHeader = true;
                            uiTotalRead = 0;

#ifdef __linux__                            
                            sndMsg.mtype = 1;
#endif
                            
                            sndMsg.uiOpCode = strLanHeader.uiOpCode;
                            sndMsg.uiSocket = m_iSocket;
                            sndMsg.iArrayIndex = -1;
                            sndMsg.uiArrayLength = 0;
                            sndMsg.uiDataLength = 0;

                            if( sndMsg.uiOpCode == enREQ_SIM_PDWDATA ) {
                                sndMsg.uiArrayLength = strLanHeader.uiLength;
                                sndMsg.iArrayIndex = m_ptheRecLan->PushLanData( pLanData, sndMsg.uiArrayLength );
                            }
                            else if( sndMsg.uiOpCode == enREQ_IPL_DOWNLOAD ) {
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
                            }

#ifdef __linux__                                
                            if( msgsnd( m_ptheRecLan->GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) < 0 ) {
                                perror( "msgsnd 실패" );
                            }
                            else {
                                // DisplayMsg( & sndMsg );

                            }
#else
                            
#endif                            

                        }
                    }
                }
            }
        }

    }

#endif

}


/**
 * @brief CMySocket::CloseSocket
 * @param iSocket
 * @param pAddress
 * @param pClientSocket
 */
void CSingleServer::CloseSocket( int iSocket, struct sockaddr_in *pAddress, int *pClientSocket )
{
#ifdef __MINGW32__

#else
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

    UINT uiMode=enREADY_MODE;
    g_pTheTaskMngr->QMsgSnd( enREQ_MODE, NULL, 0, & uiMode, sizeof(int) );
#endif

}

/**
 * @brief CRecLan::SendQMessage
 */
int CSingleServer::SendLan( UINT uiOpCode, void *pData, UINT uiLength )
{
    int iRet1, iRet2=0;
    STR_LAN_HEADER strLanHeader;

    // 랜 헤더 송신
    strLanHeader.uiOpCode = uiOpCode;
    strLanHeader.uiLength = uiLength;

#ifdef __MINGW32__
    iRet1 = 0;

#else
    //CCommonUtils::AllSwapData32( & strLanHeader, sizeof(STR_LAN_HEADER) );
    iRet1 = send( m_iSocket, (char *) & strLanHeader, sizeof(STR_LAN_HEADER), MSG_DONTWAIT );

    if( iRet1 > 0 ) {
        //CCommonUtils::AllSwapData32( pData, strLanHeader.uiLength );
        iRet2 = send( m_iSocket, (char *) pData, strLanHeader.uiLength, MSG_DONTWAIT );
    }
    else {
        // TaskMngr () Send Error 발생시 Lock 이 됨.
        //perror( "send() 에러");
    }
#endif

    return iRet1 + iRet2;

}
