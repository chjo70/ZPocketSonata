/*
 * 자체점검 Process : 자체점검을 처리하는 쓰레드 입니다.
 *
 * */


#include "curbit.h"
#include "../Utils/clog.h"


#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CUrBit* CUrBit::pInstance = nullptr;

/**
 * @brief CUrBit::CUrBit
 * @param iKeyId
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
void CUrBit::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CUrBit::_routine
 */
void CUrBit::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }

        switch( m_pMsg->ucOpCode ) {
            case enREQ_URBIT :
                LOGMSG1( enNormal, "URBIT[%d]를 수행합니다 !!" , pLanData->uiUnit );

                while( true ) {
                    puts( "." );
                }
                //m_theGPIO.SetDirection( 309, 1, char *direction)
                break;

            case enTHREAD_REQ_SHUTDOWN :
                LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", ChildClassName() );
                bWhile = false;
                break;

            default:
                //Log( enNormal, "AAA" );
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

}
