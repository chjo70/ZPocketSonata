/*
 * 자체점검 Process : 자체점검을 처리하는 쓰레드 입니다.
 *
 * */


#include "curbit.h"
#include "../Utils/clog.h"

#include "../Utils/ccommonutils.h"


#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CUrBit* CUrBit::m_pInstance = nullptr;

/**
 * @brief CUrBit::CUrBit
 * @param iKeyId
 * @param pClassName
 * @param bArrayLanData
 */
CUrBit::CUrBit( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
    LOGENTRY;

    Init();

}

/**
 * @brief CUrBit::~CUrBit
 */
CUrBit::~CUrBit(void)
{
}



/**
 * @brief CUrBit::Run
 */
void CUrBit::Run( key_t key )
{
    LOGENTRY;

    CThread::Run( key );

}

/**
 * @brief CUrBit::_routine
 */
void CUrBit::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    bool bCGIRunning;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }

        // CGI 실행 플레그 설정
        if( m_pMsg->uiOpCode == enCGI_REQ_IBIT || m_pMsg->uiOpCode == enCGI_REQ_UBIT || m_pMsg->uiOpCode == enCGI_REQ_CBIT || m_pMsg->uiOpCode == enCGI_REQ_SBIT ) {
            bCGIRunning = true;
        }
        else {
            bCGIRunning = false;
        }

        switch( m_pMsg->uiOpCode ) {
            case enCGI_REQ_IBIT :
            case enTHREAD_REQ_IBIT :
                LOGMSG1( enNormal, "IBIT[%d]를 수행합니다 !!" , pLanData->uiUnit );
                RunIBit( bCGIRunning );
                break;

            case enCGI_REQ_CBIT :
            case enTHREAD_REQ_CBIT :
                LOGMSG1( enNormal, "CRBIT[%d]를 수행합니다 !!" , pLanData->uiUnit );
                RunCBit( bCGIRunning );
                break;

            case enCGI_REQ_SBIT :
            case enTHREAD_REQ_SBIT :
                LOGMSG1( enNormal, "SRBIT[%d]를 수행합니다 !!" , pLanData->uiUnit );
                break;

            case enCGI_REQ_UBIT :
            case enTHREAD_REQ_UBIT :            
                LOGMSG1( enNormal, "URBIT[%d]를 수행합니다 !!" , pLanData->uiUnit );
                RunCBit( bCGIRunning );
                break;

            case enTHREAD_REQ_SHUTDOWN :
                LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", ChildClassName() );
                bWhile = false;
                break;

            default:
                LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
                break;
        }
    }

}

/**
 * @brief CUrBit::Init
 */
void CUrBit::Init()
{

    // 멤버 클래스 초기화
    m_theGPIO.OpenChannel( 309 );

    //GetBoardID();
    InitIBit();

}

/**
 * @brief CUrBit::InitIBit
 */
void CUrBit::InitIBit()
{
    m_stESIbit.w32 = 0;

    LOGMSG( enDebug, "IBIT를 시작 합니다...." );
}

/**
 * @brief CUrBit::RunIBit
 */
void CUrBit::RunIBit( bool bCGIRunning )
{
    LOGMSG( enDebug, "비트 결과는 입니다." );
    sleep( 1 );

    if( bCGIRunning == true ) {
        printf( "IBIT 결과는 정상 입니다." );
        QMsgSnd( _MSG_CGI_KEY, enRES_IBIT, & m_stESIbit, sizeof(m_stESIbit) );
    }
    else {
#ifndef _CGI_
        CCommonUtils::SendLan( enRES_IBIT, & m_stESIbit, sizeof(m_stESIbit) );
#endif
    }
}

/**
 * @brief CUrBit::RunCBit
 */
void CUrBit::RunCBit( bool bCGIRunning )
{
    LOGMSG( enDebug, "비트 결과는 입니다." );

    //
    memset( & m_stESCbit, 0, sizeof(m_stESCbit) );
    sleep( 2 );


    if( bCGIRunning == true ) {
        printf( "CBIT 결과는 정상 입니다." );
    }
    else {
#ifndef _CGI_
        CCommonUtils::SendLan( enRES_CBIT, & m_stESCbit, sizeof(m_stESCbit) );
#endif
    }
}

/**
 * @brief CUrBit::RunUBit
 * @param bCGIRunning
 */
void CUrBit::RunUBit( bool bCGIRunning )
{
    //
    memset( & m_stESCbit, 0, sizeof(m_stESCbit) );
    sleep( 10 );

    LOGMSG( enDebug, "비트 결과는 입니다." );

    if( bCGIRunning == true ) {

    }
    else {
#ifndef _CGI_
        CCommonUtils::SendLan( enRES_UBIT, & m_stESCbit, sizeof(m_stESCbit) );
#endif
    }
}
