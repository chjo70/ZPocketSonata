/****************************************************************************************
 파 일 명 : caaraymsgdata.cpp
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : 다중 클라리언트 랜 소켓 클래스
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 :
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/


#include "pch.h"


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
 * @brief     초기화를 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-04 18:47:01
 * @warning
 */
void CArrayMsgData::Init()
{
    m_ucPushIndex = 0;
    m_ucPopIndex = 0;

}

/**
 * @brief     메모리를 할당한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-04 18:47:25
 * @warning
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
 * @brief     메모리를 해지한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-04 18:47:42
 * @warning
 */
void CArrayMsgData::Free()
{
    int i;

    if( m_bArrayLanData == true ) {
        //TRACE( "\ndelete in the thread m_pszArray[i]=0x%p" , m_pszArray[0] );
        for( i=0 ; i < SIZE_OF_MSGDATA_ARRAY ; ++i ) {
            _SAFE_FREE( m_pszArray[i] )
        }
    }

}

/**
 * @brief     SetMark
 * @param     int iIndex
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-02 13:43:28
 * @warning
 */
void CArrayMsgData::SetMark( int iIndex )
{
    m_pszArray[iIndex][0] = ARARAY_MARK_UPPER;
    m_pszArray[iIndex][1] = ARARAY_MARK_LOWER;

}

/**
 * @brief     PushLanData
 * @param     void * pData
 * @param     unsigned int uiLength
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-02 13:43:24
 * @warning
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
        msSleep( 1000 );

        if( i++ >= MAX_TRY_MARK ) {
            break;
        }
    }

    if( m_pszArray[m_ucPushIndex][0] != ARARAY_MARK_UPPER && m_pszArray[m_ucPushIndex][1] != ARARAY_MARK_LOWER ) {
        //LOGMSG( enError, "ArrayBuffer 가 손상 되었습니다 !!" );
        //Log( enError, "[%s] 가 죽었거나 메시지 처리를 못해서 타스크 관리자에게 요청 합니다[%d]. !!" , GetThreadName(), enERROR_OF_ARRAY_MARK );
        WhereIs;
        WhereIs;
        SendTaskMngr( enERROR_OF_ARRAY_MARK, GetThreadName() );

        iRet = -1;
    }
    else {
	    if( uiLength > _MAX_LANDATA ) {
            //Log( enError, "************** 버퍼가 작습니다. _MAX_LANDATA 값을 늘려 주세요..." );
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
