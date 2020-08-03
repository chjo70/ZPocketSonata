#include "ccommonutils.h"

#include "../Utils/csingleserver.h"
#include "../Utils/cmultiserver.h"

extern CMultiServer *g_pTheZYNQSocket;
extern CSingleServer *g_pTheCCUSocket;

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
        else {

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
