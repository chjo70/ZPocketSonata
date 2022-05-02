#include "stdafx.h"

#ifdef _MSC_VER

#elif __linux__
#include <sys/socket.h>
#endif

#include <sys/types.h>

#include "creclan.h"
//#include "../Utils/clog.h"

#include "ctaskmngr.h"
#include "csignalcollect.h"
#include "cemittermerge.h"
#include "curbit.h"
#include "cusercollect.h"

#include "../Utils/ccommonutils.h"

#include "../Include/globals.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CRecLan* CRecLan::m_pInstance[2] = { nullptr, nullptr } ;


/**
 * @brief CRecLan::CRecLan
 * @param iKeyId
 */
CRecLan::CRecLan( int iKeyId, int iIndex, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData, true )
{
   LOGENTRY;

   m_iIndex = iIndex;
}

/**
 * @brief CRecLan::~CUrBit
 */
CRecLan::~CRecLan(void)
{
}

/**
 * @brief CRecLan::ReleaseInstance
 */
void CRecLan::ReleaseInstance()
{
    if(m_pInstance[m_iIndex])
    {
        int iIndex;

        LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );

        iIndex = m_iIndex;
        delete m_pInstance[iIndex];
        m_pInstance[iIndex] = NULL;
    }
}


/**
 * @brief CRecLan::Run
 */
void CRecLan::Run( key_t key )
{
    LOGENTRY;

    CThread::Run( key );

}

/**
 * @brief CRecLan::_routine
 */
void CRecLan::_routine()
{
    LOGENTRY;
    m_pMsg = GetDataMessage();

    while( true ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv");
            //break;
        }
        else {            
            if( IsValidLanData( m_pMsg ) == true ) {
                switch( m_pMsg->uiOpCode ) {
                    // 기존 SONATA 체계 명령어
                    case enREQ_MODE :
                    case enREQ_ANAL_START :
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

                    case enREQ_IPL_VERSION :
                        if( g_pTheTaskMngr != NULL ) {
                            g_pTheTaskMngr->QMsgSnd( m_pMsg );
                        }
                        break;

                    case enREQ_IPL_START :
                    case enREQ_IPL_END :
                        if( g_pTheTaskMngr != NULL ) {
                            g_pTheTaskMngr->QMsgSnd( m_pMsg );
                        }
                        break;

                    case enREQ_IPL_DOWNLOAD :
                        if( g_pTheTaskMngr != NULL ) {
                            g_pTheTaskMngr->QMsgSnd( m_pMsg, GetRecvData(), GetThreadName() );
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
                    // 오디오 제어 관련 메시지
                    case enREQ_AUDIO :
                    case enREQ_AUDIO_PARAM :
                        if( g_pTheTaskMngr != NULL ) {
                            g_pTheTaskMngr->QMsgSnd( m_pMsg, GetRecvData(), GetThreadName() );
                        }
                        break;

                    // 수신기 설정 관련 메시지
                    case enREQ_Band_Enable :
                    case enREQ_FMOP_Threshold :
                    case enREQ_PMOP_Threshold :
                    case enREQ_RX_Threshold :
                        if( g_pTheTaskMngr != NULL ) {
                            g_pTheTaskMngr->QMsgSnd( m_pMsg, GetRecvData(), GetThreadName() );
                        }
                        break;

                    case enREQ_SYS :
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
                        DumpList();
                        break;

                    default:
                        LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
                        break;
                }
            }
            else {
                LOGMSG1( enError, "Invalid the flow[0x%X] !!", m_pMsg->uiOpCode );
                }
            }
    }

}

/**
 * @brief CRecLan::DumpList
 */
void CRecLan::DumpList()
{
#ifdef _MSC_VER

#else
    // UINT uiStartAddress;

    STR_LAN_HEADER strLanHeader;
    UNI_LAN_DATA uniLanData;

    STR_REQ_DUMP_LIST *pData= ( STR_REQ_DUMP_LIST * ) m_pMsg->x.szData;

    //int iRet;
    char *pAddress;

#ifdef _DEBUG_
    char *pBuffer;
    pAddress = (char *) malloc( 16 * 1000 );
    pBuffer = pAddress;
#else
    pAddress = (char *) uiStartAddress;
#endif

    // 랜 헤더 송신
    strLanHeader.uiOpCode = enRES_DUMP_LIST;
    strLanHeader.uiLength = DUMP_DATA_SIZE;

#ifdef __linux__
    int iRet = send( m_pMsg->uiSocket, (char *) & strLanHeader, sizeof(STR_LAN_HEADER), MSG_DONTWAIT );
#endif

    // 랜 데이터 송신
    memcpy( & uniLanData.strResDumpList.strReqDumpList, pData, sizeof(STR_REQ_DUMP_LIST) );
    memcpy( uniLanData.strResDumpList.cData, pBuffer, DUMP_DATA_SIZE );

#ifdef __linux__
    iRet = send( m_pMsg->uiSocket, (char *) & uniLanData, (int) strLanHeader.uiLength, MSG_DONTWAIT );
#endif

#ifdef _DEBUG_
    free( pBuffer );
#endif

#endif
}

/**
 * @brief CCommonUtils::IsValid
 * @param pMsg
 * @return
 */
bool CRecLan::IsValidLanData( STR_MessageData *pMsg )
{
    bool bRet = true;

#ifndef _CGI_LIST_
    ENUM_MODE enMode, enModeOfMessage;

    enMode = g_pTheSysConfig->GetMode();
    switch( pMsg->uiOpCode ) {
    case enREQ_MODE:
        enModeOfMessage = ( ENUM_MODE ) pMsg->x.szData[0];

        if( enMode == enREADY_MODE && enMode == enModeOfMessage ) {
            // bRet = false;
        }
        break;
    case enREQ_ANAL_START:
        if( enMode == enES_MODE || enMode == enEW_MODE ) {
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
        if( enMode == enES_MODE || enMode == enEW_MODE ) {
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

    case enREQ_IPL_START:
    case enREQ_IPL_DOWNLOAD:
    case enREQ_IPL_END:
        if( enMode == enES_MODE || enMode == enEW_MODE || enMode == enREADY_MODE ) {
        }
        else {
            //bRet = false;
        }
        break;

    case enREQ_RELOAD_LIBRARY:
        if( enMode == enES_MODE || enMode == enEW_MODE || enMode == enREADY_MODE ) {
        }
        else {
            bRet = false;
        }
        break;

    case enREQ_IPL_VERSION:
        break;

    case enREQ_SYS:
        break;

    case enREQ_INIT:
    case enREQ_SET_CONFIG:
    case enREQ_STOP:
        break;

    case enSYSERROR:
        break;

    default:
        break;

    }
#endif

    return bRet;
}