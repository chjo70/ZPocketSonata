/*
 * 펄스추적 Process : 펄스추적을 처리하는 쓰레드 입니다.
 *
 * */

#include "cpulsetrk.h"
//#include "../Utils/clog.h"

#include "../Include/globals.h"

#define _DEBUG_

// 클래스 내의 정적 멤버변수 값 정의
CPulseTrk* CPulseTrk::m_pInstance = nullptr;

CPulseTrk::CPulseTrk( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
    LOGENTRY;
}


/**
 * @brief CPulseTrk::~CPulseTrk
 */
CPulseTrk::~CPulseTrk(void)
{
}

/**
 * @brief CPulseTrk::Run
 */
void CPulseTrk::Run(key_t key)
{
    LOGENTRY;

    CThread::Run( key );

}

/**
 * @brief CPulseTrk::_routine
 */
void CPulseTrk::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            //perror( "QMsgRcv() 에러");
            break;
        }
        else {
        switch( m_pMsg->uiOpCode ) {
            case enTHREAD_REQ_SHUTDOWN :
                LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", GetThreadName() );
                bWhile = false;
                break;

            default:
                //Log( enNormal, "AAA" );
                break;
            }
        }
    }

}
