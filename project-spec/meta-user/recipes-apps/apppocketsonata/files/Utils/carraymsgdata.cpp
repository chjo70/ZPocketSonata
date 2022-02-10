
#include "stdafx.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "carraymsgdata.h"

#include "../Include/globals.h"

/**
 * @brief CArrayMsgData::CArrayMsgData
 */
CArrayMsgData::CArrayMsgData( bool bArrayLanData )
{
    m_bArrayLanData = bArrayLanData;

    Init();

    Alloc();

}

/**
 * @brief CArrayMsgData::~CArrayMsgData
 */
CArrayMsgData::~CArrayMsgData()
{
    Free();
}

/**
 * @brief CArrayMsgData::Init
 */
void CArrayMsgData::Init()
{
    m_ucPushIndex = 0;
    m_ucPopIndex = 0;

}

/**
 * @brief CMultiServer::Alloc
 */
void CArrayMsgData::Alloc()
{
    int i;

    if( m_bArrayLanData == true ) {        
        for( i=0 ; i < SIZE_OF_MSGDATA_ARRAY ; ++i ) {
            m_pszArray[i] = ( unsigned char * ) malloc( sizeof(char) * _MAX_LANDATA );            
            SetMark( i );
        }
    }
    else {
        for( i=0 ; i < SIZE_OF_MSGDATA_ARRAY ; ++i ) {
            m_pszArray[i] = NULL;
        }
    }

}

/**
 * @brief CMultiServer::Free
 */
void CArrayMsgData::Free()
{
    int i;

    if( m_bArrayLanData == true ) {
        //TRACE( "\ndelete in the thread m_pszArray[i]=0x%p" , m_pszArray[0] );
        for( i=0 ; i < SIZE_OF_MSGDATA_ARRAY ; ++i ) {
            _SAFE_FREE( m_pszArray[i] );
        }
    }

}

/**
 * @brief CArrayMsgData::SetMark
 * @param iIndex
 */
void CArrayMsgData::SetMark( int iIndex )
{
    m_pszArray[iIndex][0] = ARARAY_MARK_UPPER;
    m_pszArray[iIndex][1] = ARARAY_MARK_LOWER;

}

/**
 * @brief CArrayMsgData::PushLanData
 */
int CArrayMsgData::PushLanData( void *pData, unsigned int uiLength )
{
    int iRet;

    ++ m_ucPushIndex;
    if( m_ucPushIndex >= SIZE_OF_MSGDATA_ARRAY ) {
        m_ucPushIndex = 0;
    }
    iRet = (int) m_ucPushIndex;

    // 메시지 처리 대기
    int i=0;
    while( m_pszArray[m_ucPushIndex][0] != ARARAY_MARK_UPPER && m_pszArray[m_ucPushIndex][1] != ARARAY_MARK_LOWER ) {
        Sleep( 1000 );

        if( i++ >= MAX_TRY_MARK ) {
            break;
        }
    }

    if( m_pszArray[m_ucPushIndex][0] != ARARAY_MARK_UPPER && m_pszArray[m_ucPushIndex][1] != ARARAY_MARK_LOWER ) {
        //LOGMSG( enError, "ArrayBuffer 가 손상 되었습니다 !!" );
        LOGMSG2( enError, "[%s] 가 죽었거나 메시지 처리를 못해서 타스크 관리자에게 요청 합니다[%d]. !!" , GetThreadName(), enERROR_OF_ARRAY_MARK );

        SendTaskMngr( enERROR_OF_ARRAY_MARK, GetThreadName() );

        iRet = -1;
    }
    else {
	if( uiLength > _MAX_LANDATA ) {
		TRACE( "\n************** 버퍼가 작습니다. _MAX_LANDATA 값을 늘려 주세요..." );
		exit( 1 );
	}

    memcpy( m_pszArray[m_ucPushIndex], pData, uiLength );
    }

    return iRet;
}

/**
 * @brief CArrayMsgData::PopLanData
 * @param pData
 * @param iIndex
 * @param uiLength
 */
void CArrayMsgData::PopLanData( void *pData, int iIndex, unsigned int uiLength )
{

    if( iIndex >= 0 && iIndex < SIZE_OF_MSGDATA_ARRAY ) {
        memcpy( pData, m_pszArray[iIndex], uiLength );
        SetMark( iIndex );
    }
    else {
        // LOGMSG1( enError, "ArrayBuffer 인덱스[%d]가 잘못 되었습니다." , iIndex );
    }

    return;
}
