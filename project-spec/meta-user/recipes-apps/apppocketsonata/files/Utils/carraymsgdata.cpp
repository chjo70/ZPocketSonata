#include <stdlib.h>
#include <string.h>

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
            m_pszArray[i] = ( char * ) malloc( sizeof(char) * _MAX_LANDATA );
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
 * @brief CArrayMsgData::PushLanData
 */
int CArrayMsgData::PushLanData( void *pData, unsigned int uiLength )
{
    ++ m_ucPushIndex;

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

    memcpy( pData, m_pszArray[iIndex], uiLength );
    return;
}
