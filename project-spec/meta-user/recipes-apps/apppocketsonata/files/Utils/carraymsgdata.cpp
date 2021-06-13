#ifdef _MSC_VER
#include "stdafx.h"

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clog.h"

#include "carraymsgdata.h"

/**
 * @brief CArrayMsgData::CArrayMsgData
 */
CArrayMsgData::CArrayMsgData( bool bArrayLanData )
{
    m_bArrayLanData = bArrayLanData;

    Init();

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

    Alloc();

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
        for( i=0 ; i < SIZE_OF_MSGDATA_ARRAY ; ++i ) {
            free( m_pszArray[i] );
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
    ++ m_ucPushIndex;

    if( m_pszArray[m_ucPushIndex][0] != ARARAY_MARK_UPPER && m_pszArray[m_ucPushIndex][1] != ARARAY_MARK_LOWER ) {
        LOGMSG( enError, "ArrayBuffer 가 손상 되었습니다 !!" );
    }

    memcpy( m_pszArray[m_ucPushIndex], pData, uiLength );
    return m_ucPushIndex;
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
