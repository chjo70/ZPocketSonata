#include "ccommonutils.h"

#include "../System/csysconfig.h"

#include "../Utils/csingleserver.h"
#include "../Utils/cmultiserver.h"

extern CMultiServer *g_pTheZYNQSocket;
extern CSingleServer *g_pTheCCUSocket;
extern CSingleServer *g_pThePMCSocket;

/**
 * @brief 생성자를 수행합니다.
 */
CCommonUtils::CCommonUtils()
{

}

/**
 * @brief opcode, data 를 입력받아서 랜으로 송신한다.
 * @param uiOpCode
 * @param uiLength
 * @param pData
 */
void CCommonUtils::SendLan( UINT uiOpCode, void *pData, UINT uiLength )
{
    // 마스터 보드에서는 랜 메시지를 CCU 장치로 전송한다.
    if( g_enBoardId == enMaster ) {
        if( g_pTheCCUSocket != NULL ) {
            g_pTheCCUSocket->SendLan( uiOpCode, pData, uiLength );
        }

        // EA 경우에 AET 관련 메세지를 전달한다.
        if( g_pThePMCSocket != NULL && ( uiOpCode == esAET_NEW_CCU || uiOpCode == esAET_UPD_CCU || uiOpCode == esAET_DEL_CCU ) ) {

        }

    }
    // 클라이언트 보드 인 경우에는 랜 메시지를 마스터 보드에 전달한다.
    else {
        if( g_pTheZYNQSocket != NULL ) {
            g_pTheZYNQSocket->SendLan( uiOpCode, pData, uiLength );
        }
        else {

        }
    }

}

/**
 * @brief CCommonUtils::IsValid
 * @param pMsg
 * @return
 */
bool CCommonUtils::IsValidLanData( STR_MessageData *pMsg )
{
    bool bRet=true;
    ENUM_MODE enMode, enModeOfMessage;

    enMode = GP_SYSCFG->GetMode();
    switch( pMsg->uiOpCode ) {
        case enREQ_MODE :
            enModeOfMessage = (ENUM_MODE) pMsg->x.szData[0];

            if( enMode == enREADY_MODE && enMode == enModeOfMessage  ) {
                bRet = false;
            }
            break;
        case enREQ_ANAL_START :
            if( enMode == enES_MODE || enMode == enEW_MODE  ) {
            }
            else {
                bRet = false;
            }
            break;

        case enREQ_IBIT :
        case enREQ_UBIT :
        case enREQ_CBIT :
            if( enMode == enES_MODE || enMode == enEW_MODE  ) {
            }
            else {
                bRet = false;
            }
            break;

        case enREQ_SBIT :
            if( enMode == enES_MODE || enMode == enEW_MODE  ) {
            }
            else {
                bRet = false;
            }
            break;

        case enREQ_SIM_PDWDATA :
            if( enMode == enREADY_MODE ) {
                bRet = false;
            }
            break;

        case enREQ_IPL_START :
        case enREQ_IPL_DOWNLOAD :
        case enREQ_IPL_END :
            if( enMode == enES_MODE || enMode == enEW_MODE || enMode == enREADY_MODE ) {
            }
            else {
                bRet = false;
            }
            break;

        case enREQ_RELOAD_LIBRARY :
        case enREQ_IPL_VERSION :
            break;

        default:
            break;

    }

    return bRet;
}

/**
 * @brief CCommonUtils::timespec_diff
 * @param result
 * @param start
 * @param stop
 */
void CCommonUtils::DiffTimespec(struct timespec *result, struct timespec *start, struct timespec *stop )
{
    struct timespec tsNow;

    if( stop != NULL ) {
        tsNow.tv_sec = stop->tv_sec;
        tsNow.tv_nsec = stop->tv_nsec;
    }
    else {
        clock_gettime( CLOCK_REALTIME, & tsNow );
    }

    if ((tsNow.tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = tsNow.tv_sec - start->tv_sec - 1;
        result->tv_nsec = tsNow.tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = tsNow.tv_sec - start->tv_sec;
        result->tv_nsec = tsNow.tv_nsec - start->tv_nsec;
    }

    return;
}
