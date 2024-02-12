/**

    @file      csbc.cpp
    @brief
    @details   ~
    @author    조철희
    @date      22.08.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "pch.h"
#include "framework.h"
#include "ZCCUSim.h"
#include "ZCCUSimDlg.h"
#include "afxdialogex.h"

#ifdef _MSC_VER

#elif defined(__linux__)
#include <sys/socket.h>
#endif

#include <sys/types.h>

#include "csbc.h"

#include "../../files/Utils/ccommonutils.h"

#include "../../files/Include/globals.h"

#include "../../files/Utils/cmultiserver.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CSBC* CSBC::m_pInstance[2] = { nullptr, nullptr } ;


/**
 * @brief     CSBC
 * @param     int iKeyId
 * @param     int iIndex
 * @param     char * pClassName
 * @param     bool bArrayLanData
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 10:19:09
 * @warning
 */
CSBC::CSBC( int iKeyId, char *pClassName, bool bArrayLanData, void *pParent ) : CThread( iKeyId, pClassName, bArrayLanData, true )
{
   //LOGENTRY;

    m_pParent = pParent;

}

/**
 * @brief     ~CSBC
 * @param     void
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 10:19:22
 * @warning
 */
CSBC::~CSBC(void)
{
    //CThread::StopThread();

}


/**
 * @brief CRecLan::Run
 */
void CSBC::Run()
{
    //LOGENTRY;

    CThread::Run();

}

/**
 * @brief     쓰레드 루틴이며 명령을 수신하고 절절한 함수를 호출한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 11:30:31
 * @warning
 */
void CSBC::_routine()
{
    //LOGENTRY;

    m_pMsg = GetRecvDataMessage();

    STR_CLIENT_SOCKET *pClientSocket;

    pClientSocket = ( STR_CLIENT_SOCKET *) & m_pMsg->x.szData[0];

    while( m_bThreadLoop ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv");
        }
        else {
            if( IsValidLanData( m_pMsg ) == true ) {
                switch( m_pMsg->uiOpCode ) {
                    ///////////////////////////////////////////////////////////////////////////////////
                    // 랜 이벤트 처리
                    case ON_CONNECT :
                        TRACE( "\n SBC 연결-소켓[%d]", pClientSocket->iSocket );
                        OnConnect();
                        break;

                    case ON_DISCONNECT:
                        TRACE( "\n SBC 단란-소켓[%d]", pClientSocket->iSocket );
                        OnDisConnect();
                        break;

                    ///////////////////////////////////////////////////////////////////////////////////
                    // 운용 제어 메시지 처리
                    case enRES_OP_START:
                        ResultOfOPStart();
                        break;

                    case enRES_OP_SHUTDOWN:
                        ResultOfOPShutdown();
                        break;

                    case enRES_OP_RESTART:
                        ResultOfOPRestart();
                        break;

                    case enRES_RELOAD_LIBRARY :
                        ResultOfReloadLibrary();
                        break;

                    ///////////////////////////////////////////////////////////////////////////////////
                    // 운용 변수 설정 관련 메시지
                    case enRES_SETSYS :
                        ResultOfSetSys();
                        break;

                    case enRES_SYS:
                        ResultOfSys();
                        break;

                    ///////////////////////////////////////////////////////////////////////////////////
                    // 위협 결과 메시지 처리
                    case enNUP_THREAT_DATA :
                        ResultOfUpdateThreatData();
                        break;

                    case enDEL_THREAT_DATA :
                        ResultOfDeleteThreatData( m_pMsg->uiDataLength );
                        break;

                    case enDEL_BEAM_DATA:
                        ResultOfDeleteBeamData();
                        break;

                    case enRES_SCAN_DATA:
                        ResultOfScanData();
                        break;

                    case enRES_USERSCAN:
                        ResultOfUserScan();
                        break;

                    case enRES_USER_DELETE_THREAT_DATA:
                        ResultOfUserDeleteThreatData();
                        break;

                    case enLST_THREAT_DATA:
                        ResultOfLostBeamData();
                        break;

                    case enLST_BEAM_DATA :
                        ResultOfLostBeamData();
                        break;

                    ///////////////////////////////////////////////////////////////////////////////////
                    // 에러 메시지 처리
                    case enRES_SYSERROR:
                        ResultOfSysError();
                        break;

                    default:
                        //LOGMSG2( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                        TRACE( "\n m_pMsg->uiOpCode=0x%x", m_pMsg->uiOpCode );
                        break;
                }
            }
            else {
                Log( enError, "메시지 흐름에 잘못된 명령[0x%X]을 수신했습니다 !", m_pMsg->uiOpCode );
            }
        }
    }

}

/**
 * @brief CRecLan::DumpList
 */
// void CSBC::DumpList()
// {
// #ifdef _MSC_VER
//
// #else
//     // UINT uiStartAddress;
//
//     STR_LAN_HEADER strLanHeader;
//     UNI_LAN_DATA uniLanData;
//
//     STR_REQ_DUMP_LIST *pData= ( STR_REQ_DUMP_LIST * ) m_pMsg->x.szData;
//
//     //int iRet;
//     char *pAddress;
//
// #ifdef _DEBUG_
//     char *pBuffer;
//     pAddress = (char *) malloc( 16 * 1000 );
//     pBuffer = pAddress;
// #else
//     pAddress = (char *) uiStartAddress;
// #endif
//
//     // 랜 헤더 송신
//     strLanHeader.uiOpCode = enRES_DUMP_LIST;
//     strLanHeader.uiLength = DUMP_DATA_SIZE;
//
// #ifdef __linux__
//     int iRet = send( m_pMsg->uiSocket, (char *) & strLanHeader, sizeof(struct STR_LAN_HEADER), MSG_DONTWAIT );
// #endif
//
//     // 랜 데이터 송신
//     memcpy( & uniLanData.strResDumpList.strReqDumpList, pData, sizeof(struct STR_REQ_DUMP_LIST) );
//     memcpy( uniLanData.strResDumpList.cData, pBuffer, DUMP_DATA_SIZE );
//
// #ifdef __linux__
//     iRet = send( m_pMsg->uiSocket, (char *) & uniLanData, (int) strLanHeader.uiLength, MSG_DONTWAIT );
// #endif
//
// #ifdef _DEBUG_
//     free( pBuffer );
// #endif
//
// #endif
// }

/**
 * @brief CCommonUtils::IsValid
 * @param pMsg
 * @return
 */
bool CSBC::IsValidLanData( STR_MessageData *pMsg )
{
    bool bRet = true;

#ifndef _CGI_LIST_

    switch( pMsg->uiOpCode ) {
    case enREQ_SET_SYS :
    case enREQ_SYS:
        break;

    case enREQ_INIT:
    case enREQ_SET_CONFIG:
    case enREQ_STOP:
        break;

    case enREQ_SYSERROR:
        break;

    case enTHREAD_DISCONNECTED :
        break;

    default:
        break;

    }
#endif

    return bRet;
}

/**
 * @brief     OnConnect
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-22 16:15:29
 * @warning
 */
void CSBC::OnConnect()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->ConnectMessage( ( STR_CLIENT_SOCKET * ) m_pMsg->x.szData );

}

/**
 * @brief     OnDisConnect
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-22 16:56:38
 * @warning
 */
void CSBC::OnDisConnect()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->DisConnectMessage( ( STR_CLIENT_SOCKET * ) m_pMsg->x.szData );

}

/**
 * @brief     ResultOfOPStart
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-22 17:36:13
 * @warning
 */
void CSBC::ResultOfOPStart()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->ResultOfOPStart( GeUniMsgData() );

}

/**
 * @brief     ResultOPShutdown
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-27 17:21:16
 * @warning
 */
void CSBC::ResultOfOPShutdown()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->ResultOfOPShutdown( GeUniMsgData() );

}

/**
 * @brief     ResultOPRestart
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-27 17:27:37
 * @warning
 */
void CSBC::ResultOfOPRestart()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->ResultOfOPRestart( GeUniMsgData() );

}

/**
 * @brief     ResultReloadLibrary
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-27 17:34:27
 * @warning
 */
void CSBC::ResultOfReloadLibrary()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->ResultOfReloadLibrary( GeUniMsgData() );

}

/**
 * @brief     ResultSetSys
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-27 17:51:28
 * @warning
 */
void CSBC::ResultOfSetSys()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->ResultOfSetSys( GeUniMsgData() );

}

/**
 * @brief     ResultSys
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-27 17:56:18
 * @warning
 */
void CSBC::ResultOfSys()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->ResultOfSys( ( UNI_LAN_DATA * ) GetRecvData(), m_pMsg->uiArrayLength );

}

/**
 * @brief     ResultOfScanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-28 14:12:31
 * @warning
 */
void CSBC::ResultOfScanData()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->ResultOfScanData( GeUniMsgData() );

}

/**
 * @brief     ResultOfDelete
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-27 19:38:18
 * @warning
 */
void CSBC::ResultOfUserScan()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->ResultOfUserScan( GeUniMsgData() );

}

/**
 * @brief     ResultOfDelete
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-28 15:13:57
 * @warning
 */
void CSBC::ResultOfDelete()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->ResultOfDelete( GeUniMsgData() );

}

/**
 * @brief     ResultOfLostBeamData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-16 17:05:13
 * @warning
 */
void CSBC::ResultOfLostBeamData()
{
    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;
    pDlg->ResultOfLostBeamData( GeUniMsgData() );

}

/**
 * @brief     ResultThreatData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-27 11:41:01
 * @warning
 */
void CSBC::ResultOfUpdateThreatData()
{

    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;

    pDlg->ResultOfThreatData( ( UNI_LAN_DATA *) GetRecvData() );

}

/**
 * @brief     ResultOfDeleteThreatData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-28 15:13:32
 * @warning
 */
void CSBC::ResultOfDeleteThreatData( unsigned int uiDataLength )
{

    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;

    pDlg->ResultOfDeleteThreatData( GeUniMsgData(), uiDataLength );

}

/**
 * @brief     ResultOfUserDeleteThreatData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-12 14:39:59
 * @warning
 */
void CSBC::ResultOfUserDeleteThreatData()
{

    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;

    pDlg->ResultOfUserDeleteThreatData( GeUniMsgData() );

}

/**
 * @brief     ResultOfDeleteBeamData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-28 17:15:44
 * @warning
 */
void CSBC::ResultOfDeleteBeamData()
{

    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;

    pDlg->ResultOfDeleteBeamData( GeUniMsgData() );

}

/**
 * @brief     ResultOfSysError
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-28 13:58:57
 * @warning
 */
void CSBC::ResultOfSysError()
{

    CZCCUSimDlg *pDlg;

    pDlg = ( CZCCUSimDlg * ) m_pParent;

    UNI_LAN_DATA *pUNIData = ( UNI_LAN_DATA * ) GeLanData();

    pDlg->ResultOfSysError( GeLanData() );

}

