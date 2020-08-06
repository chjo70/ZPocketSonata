/*
 * 재밍 기법을 처리하는 쓰레드 입니다.
 * */

#include "cjamtech.h"
#include "../Utils/clog.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CJamTech* CJamTech::pInstance = nullptr;

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
 * @brief CSysConfig::ReleaseInstance
 */
void CJamTech::ReleaseInstance()
{
    if(pInstance)
    {
        LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );

        delete pInstance;
        pInstance = NULL;
    }
}



/**
 * @brief CJamTech::Run
 */
void CJamTech::Run()
{
    LOGENTRY;

    CThread::Run();

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

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->szMessage[0];

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }

        switch( m_pMsg->ucOpCode ) {
            case enTHREAD_REQ_SHUTDOWN :
                LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );
                bWhile = false;
                break;

            default:
                //Log( enNormal, "AAA" );
                break;
        }
    }

}
