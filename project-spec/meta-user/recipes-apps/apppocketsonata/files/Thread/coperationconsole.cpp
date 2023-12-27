#include "stdafx.h"

#ifdef _MSC_VER

#elif defined(__linux__)
#include <sys/socket.h>
#endif

#include <sys/types.h>

#include "coperationconsole.h"


#include "ctaskmngr.h"
#include "csignalcollect.h"
#include "cemittermerge.h"
#include "curbit.h"
#include "cusercollect.h"

#include "../Utils/ccommonutils.h"

#include "../Include/globals.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
//COperationConsole* COperationConsole::m_pInstance[2] = { nullptr, nullptr } ;


/**
 * @brief     COperationConsole
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
COperationConsole::COperationConsole( int iKeyId, const char *pThreadName, bool bArrayLanData ) : CThread( iKeyId, pThreadName, bArrayLanData, true )
{
   //LOGENTRY;

   //m_iIndex = iIndex;

}

/**
 * @brief     ~COperationConsole
 * @param     void
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 10:19:22
 * @warning
 */
COperationConsole::~COperationConsole(void)
{
}

/**
 * @brief     ReleaseInstance
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 10:19:17
 * @warning
 */
// void COperationConsole::ReleaseInstance()
// {
//     if(m_pInstance)
//     {
//         //LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );
// 
//         delete m_pInstance;
//         m_pInstance = NULL;
//     }
// }


/**
 * @brief CRecLan::Run
 */
void COperationConsole::Run()
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
void COperationConsole::_routine()
{
    //LOGENTRY;
    m_pMsg = GetRecvDataMessage();

    while( true ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv");
            //break;
        }
        else {
            if( IsValidLanData( m_pMsg ) == true ) {
                switch( m_pMsg->uiOpCode ) {
                    case enREQ_OP_START :
                        g_pTheTaskMngr->QMsgSnd( m_pMsg, GetThreadName() );
                        break;

                    case enREQ_OP_SHUTDOWN :
                        g_pTheTaskMngr->QMsgSnd( m_pMsg, GetThreadName() );
                        break;

                    case enREQ_OP_RESTART :
                        g_pTheTaskMngr->QMsgSnd( m_pMsg, GetThreadName() );
                        break;

                    case enREQ_IBIT :
                    case enREQ_UBIT :
                    case enREQ_CBIT :
                    case enREQ_SBIT :
                        if( g_pTheUrBit != NULL ) {
                            g_pTheUrBit->QMsgSnd( m_pMsg, GetThreadName() );
                        }
                        break;

                    case enREQ_RELOAD_LIBRARY :
                        if( g_pTheEmitterMerge != NULL ) {
                            g_pTheEmitterMerge->QMsgSnd( m_pMsg );
                        }
                        else {
                            // LOGMSG1( enError, "Invalid the flow[0x%X] !!", m_pMsg->uiOpCode );
                        }
                        break;

                    /////////////////////////////////////////////////////////////////////////////////////////
                    // 수집 제어 관련 메시지
                    case enREQ_INIT :
                    case enREQ_SET_CONFIG :
                    case enREQ_COL_START :
                    case enREQ_RAWDATA :
                        g_pTheUserCollect->QMsgSnd( m_pMsg, GetRecvData(), GetThreadName() );
                        break;

                    case enREQ_STOP :
                        if( g_pTheTaskMngr != NULL ) {
                            g_pTheTaskMngr->QMsgSnd( m_pMsg, GetRecvData(), GetThreadName() );
                        }
                        break;

                    /////////////////////////////////////////////////////////////////////////////////////////
                    case enREQ_ANAL_SCAN:
                    case enREQ_DELETE_THREAT_DATA:
                        if( g_pTheEmitterMerge != NULL ) {
                            g_pTheEmitterMerge->QMsgSnd( m_pMsg );
                        }
                        else {
                            // LOGMSG1( enError, "Invalid the flow[0x%X] !!", m_pMsg->uiOpCode );
                        }
                        break;

                    /////////////////////////////////////////////////////////////////////////////////////////
                    // 운용변수 설정
                    case enREQ_SET_SYS :
                        if( g_pTheTaskMngr != NULL ) {
                            g_pTheTaskMngr->QMsgSnd( m_pMsg, GetRecvData(), GetThreadName() );
                        }
                        break;

                    case enREQ_SYS:
                        if( g_pTheTaskMngr != NULL ) {
                            g_pTheTaskMngr->QMsgSnd( m_pMsg, GetRecvData(), GetThreadName() );
                        }
                        break;

                    // 추가 명령어
                    case enREQ_SIM_PDWDATA :
                        if( g_pTheTaskMngr != NULL ) {
                            g_pTheSignalCollect->QMsgSnd( m_pMsg, GetRecvData(), GetThreadName() );
                        }
                        break;

                    case enREQ_DUMP_LIST :
                        // DumpList();
                        break;

                    ///////////////////////////////////////////////////////////////////////////////////
                    // 쓰레드 관련 메시지 처리
                    case enTHREAD_DISCONNECTED :
                        g_pTheTaskMngr->QMsgSnd( m_pMsg, GetThreadName() );
                        break;

                    default:
                        //LOGMSG2( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                        break;
                }
            }
            else {
                Log( enError, "메시지 흐름 또는 운용 모드[%d]에 잘못된 명령[0x%X]을 수신했습니다 !", g_pTheTaskMngr->GetMode(), m_pMsg->uiOpCode );
            }
        }
    }

}

/**
 * @brief CRecLan::DumpList
 */
// void COperationConsole::DumpList()
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
bool COperationConsole::IsValidLanData( STR_MessageData *pMsg )
{
    bool bRet = true;

#ifndef _CGI_LIST_
    ENUM_MODE enMode; //, enModeOfMessage;

    enMode = g_pTheTaskMngr->GetMode();
    switch( pMsg->uiOpCode ) {
    case enREQ_OP_START:
        if( enMode == enREADY_MODE ) {
        }
        else {
            bRet = false;
        }
        break;

    case enREQ_OP_SHUTDOWN :
        if( enMode == enOP_Mode ) {
        }
        else {
            bRet = false;
        }
        break;

    case enREQ_IBIT:
    case enREQ_UBIT:
        //             if( enMode == enES_MODE || enMode == enEW_MODE  ) {
        //
        //             }
        //             else {
        //                 bRet = false;
        //             }
        bRet = true;
        break;

    case enREQ_CBIT:
        break;

    case enREQ_SBIT:
        if( enMode == enOP_Mode ) {
        }
        else {
            bRet = false;
        }
        break;

    case enREQ_SIM_PDWDATA:
        if( enMode == enREADY_MODE ) {
            bRet = false;
        }
        break;

    case enREQ_RELOAD_LIBRARY:
        break;

    case enREQ_ANAL_SCAN:
    case enREQ_DELETE_THREAT_DATA:
        if( enMode == enREADY_MODE ) {
            bRet = false;
        }
        else {

        }
        break;

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
