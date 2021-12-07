/*
 * 재밍 기법을 처리하는 쓰레드 입니다.
 * */

#include "cjamtech.h"

#include "../Include/globals.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CJamTech* CJamTech::m_pInstance = nullptr;

/**
 * @brief CJamTech::CJamTech
 * @param iKeyId
 * @param pClassName
 */
CJamTech::CJamTech( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{

}

/**
 * @brief CJamTech::~CJamTech
 */
CJamTech::~CJamTech(void)
{
}

/**
 * @brief CJamTech::Run
 */
void CJamTech::Run(key_t key)
{
    LOGENTRY;

    CThread::Run( key );

}

/**
 * @brief CJamTech::_routine
 */
void CJamTech::_routine()
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
                LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", GetThreadName() );
                bWhile = false;
                break;

            default:
                //Log( enNormal, "AAA" );
                break;
            }
        }
    }

}
