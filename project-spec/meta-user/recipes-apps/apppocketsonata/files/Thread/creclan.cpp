
#include <sys/types.h>
#include <sys/socket.h>


#include "creclan.h"
#include "../Utils/clog.h"

#include "ctaskmngr.h"
#include "csignalcollect.h"

#include "../Utils/ccommonutils.h"

#define _DEBUG_


// 클래스 내의 정적 멤버변수 값 정의
CRecLan* CRecLan::pInstance[2] = { nullptr, nullptr } ;


/**
 * @brief CRecLan::CRecLan
 * @param iKeyId
 */
CRecLan::CRecLan( int iKeyId, int iIndex, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
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
    if(pInstance[m_iIndex])
    {
        int iIndex;

        LOGMSG1( enDebug, "[%s] 를 종료 처리 합니다...", ChildClassName() );

        iIndex = m_iIndex;
        delete pInstance[iIndex];
        pInstance[iIndex] = NULL;
    }
}


/**
 * @brief CRecLan::Run
 */
void CRecLan::Run()
{
    LOGENTRY;

    CThread::Run();

}

/**
 * @brief CRecLan::_routine
 */
void CRecLan::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    m_pMsg = GetDataMessage();

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            perror( "error ");
        }

        if( CCommonUtils::IsValidLanData( m_pMsg ) == true ) {
            switch( m_pMsg->ucOpCode ) {
                // 기존 SONATA 체계 명령어
                case enREQ_MODE :
                case enREQ_ANAL_START :
                    TMNGR->QMsgSnd( m_pMsg );
                    break;

                case enREQ_URBIT :
                    //SendQMessage();
                    break;

                // 추가 명령어
                case enREQ_SIM_PDWDATA :
                    SIGCOL->QMsgSnd( m_pMsg, GetArrayMsgData(m_pMsg->iArrayIndex) );
                    break;

                case enREQ_DUMP_LIST :
                    DumpList();
                    break;

                case enTHREAD_REQ_SHUTDOWN :
                    LOGMSG1( enDebug, "[%s]를 Shutdown 메시지를 처리합니다...", ChildClassName() );
                    bWhile = false;
                    break;

                default:
                    LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->ucOpCode );
                break;
            }
        }
    }

}

/**
 * @brief CRecLan::DumpList
 */
void CRecLan::DumpList()
{
    UINT uiStartAddress;

    STR_LAN_HEADER strLanHeader;
    UNI_LAN_DATA uniLanData;

    STR_REQ_DUMP_LIST *pData= ( STR_REQ_DUMP_LIST * ) m_pMsg->x.szData;

    int iRet;
    char *pAddress;

#ifdef _DEBUG_
    char *pBuffer;
    pBuffer = pAddress = (char *) malloc( 16 * 1000 );
#else
    pAddress = (char *) uiStartAddress;
#endif

    // 랜 헤더 송신
    strLanHeader.ucOpCode = enRES_DUMP_LIST;
    strLanHeader.uiLength = DUMP_DATA_SIZE;

    iRet = send( m_pMsg->iSocket, (char *) & strLanHeader, sizeof(STR_LAN_HEADER), MSG_DONTWAIT );

    // 랜 데이터 송신
    memcpy( & uniLanData.strResDumpList.strReqDumpList, pData, sizeof(STR_REQ_DUMP_LIST) );
    memcpy( uniLanData.strResDumpList.cData, pBuffer, DUMP_DATA_SIZE );

    iRet = send( m_pMsg->iSocket, (char *) & uniLanData, (int) strLanHeader.uiLength, MSG_DONTWAIT );

#ifdef _DEBUG_
    free( pBuffer );
#endif
}

