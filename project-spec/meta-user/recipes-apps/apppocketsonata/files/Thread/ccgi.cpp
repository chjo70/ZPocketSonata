#include "ccgi.h"
#include "../Utils/clog.h"

#ifndef _CGI_LIST_
#include "curbit.h"
#include "cusercollect.h"
#endif

#include "../Include/globals.h"


// 클래스 내의 정적 멤버변수 값 정의
CCGI* CCGI::m_pInstance = nullptr;


/**
 * @brief CCGI::CCGI
 * @param iKeyId
 * @param pClassName
 * @param bArrayLanData
 */
CCGI::CCGI( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
    LOGENTRY;

    Init();

}

/**
 * @brief CCGI::~CCGI
 */
CCGI::~CCGI(void)
{
}


/**
 * @brief CUrBit::Run
 */
void CCGI::Run( key_t key )
{
    LOGENTRY;

    CThread::Run( key );

}

/**
 * @brief CCGI::_routine
 */
void CCGI::_routine()
{
    LOGENTRY;
    bool bWhile=true;

    bool bCGIRunning;

    m_pMsg = GetDataMessage();

    //pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            //perror( "error ");
            break;
        }

        // CGI 실행 플레그 설정
        if( m_pMsg->uiOpCode == enCGI_REQ_IBIT || m_pMsg->uiOpCode == enCGI_REQ_UBIT || m_pMsg->uiOpCode == enCGI_REQ_CBIT || m_pMsg->uiOpCode == enCGI_REQ_SBIT ) {
            bCGIRunning = true;
        }
        else {
            bCGIRunning = false;
        }

        switch( m_pMsg->uiOpCode ) {
            //////////////////////////////////////////////////////////////////////////////////////
            // 메인 운용 소프트웨어에서 수신 처리 부분
            case enCGI_REQ_IBIT :
                LOGMSG1( enNormal, "IBIT[%d]를 수행합니다 !!" , m_pMsg->x.uiData );
#ifndef _CGI_LIST_
                g_pTheUrBit->QMsgSnd( m_pMsg );
#endif
                break;

            case enCGI_REQ_CBIT :
                LOGMSG1( enNormal, "CRBIT[%d]를 수행합니다 !!" , m_pMsg->x.uiData );
#ifndef _CGI_LIST_
                g_pTheUrBit->QMsgSnd( m_pMsg );
#endif
                break;

            case enCGI_REQ_UBIT :
            case enCGI_REQ_SBIT :
                LOGMSG1( enNormal, "URBIT[%d]를 수행합니다 !!" , m_pMsg->x.uiData );
#ifndef _CGI_LIST_
                g_pTheUrBit->QMsgSnd( m_pMsg );
#endif
                break;

            //////////////////////////////////////////////////////////////////////////////////////
            // CGI 프로그램에서 수신 처리 부분
            case enRES_IBIT :
                printf( "\n enRES_IBIT" );
                break;

            case enCGI_FETCH :
                break;

            case enCGI_REQ_SPECTRUM :
#ifndef _CGI_LIST_
                g_pTheUserCollect->QMsgSnd( m_pMsg );
#endif
                break;

            default:
                LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
                break;
        }
    }

}
