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


#ifdef _MSC_VER

#elif defined(__VXWORKS__)

    if( sem_init( & m_mutex, 1, 1 ) < 0 ) {
        perror( "세마포어 실패" );
    }

#elif defined(__linux__)

    if( sem_init( & m_mutex, 1, 1 ) < 0 ) {
        perror( "세마포어 실패" );
    }

#else
#error 이 소스는 현재 플레폼에 지원하지 않습니다. 개발자에게 문의하세요..
#endif


    Init();

    CArrayMsgData::Alloc();

}

/**
 * @brief     ~CArrayMsgData
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-16 13:47:12
 * @warning
 */
CArrayMsgData::~CArrayMsgData()
{
    Free();

#ifdef __linux__
    sem_destroy( & m_mutex );

#elif defined(_MSC_VER)

#elif defined(__VXWORKS__)
    sem_destroy( & m_mutex );


#else

#endif
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
    //m_ucPopIndex = 0;

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
            SetMark( i, false );
        }
    }
    else {
        for( i=0 ; i < SIZE_OF_MSGDATA_ARRAY ; ++i ) {
            m_pszArray[i] = NULL;
        }
    }

}

/**
 * @brief     Clear
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-27 15:08:49
 * @warning
 */
void CArrayMsgData::Clear()
{
    int i;

    for( i = 0 ; i < SIZE_OF_MSGDATA_ARRAY ; ++i ) {
        SetMark( i, false );
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
void CArrayMsgData::SetMark( int iIndex, bool bLog )
{
    m_pszArray[iIndex][0] = ARARAY_MARK_UPPER;
    m_pszArray[iIndex][1] = ARARAY_MARK_LOWER;
    m_pszArray[iIndex][2] = 0;

    if( bLog == true ) {
#ifdef _WIN64
        // TRACE( "SetMark [%5s:%3d]\n", GetThreadName(), iIndex );
#endif
    }

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
    int ucPushIndex;

    m_theLock.Lock();
    ++ m_ucPushIndex;
    if( m_ucPushIndex >= SIZE_OF_MSGDATA_ARRAY ) {
        m_ucPushIndex = 0;
    }
    ucPushIndex = ( int ) m_ucPushIndex;

    // 메시지 처리 대기
    int i=0;

#ifdef _LOG_
    if( this != g_pTheLog ) {
#endif
        if( m_pszArray[ucPushIndex][0] != ARARAY_MARK_UPPER && m_pszArray[ucPushIndex][1] != ARARAY_MARK_LOWER ) {

            //int iPriority = _GetPriority();
            //_ChangeTaskPriority( TASK_LOWEST_PRIORITY );
            do {
#ifdef __VXWORKS__
                taskDelay( 2 * 77 );
#else
                Sleep( 2 );
#endif
                PrintDebug( ( unsigned int ) ucPushIndex );

                TRACE( "!" );
                if( i++ >= MAX_TRY_MARK ) {
                    break;
                }
            } while( m_pszArray[ucPushIndex][0] != ARARAY_MARK_UPPER && m_pszArray[ucPushIndex][1] != ARARAY_MARK_LOWER );

        }
#ifdef _LOG_
    }
#endif

#ifdef _LOG_
    else {
        if( m_pszArray[ucPushIndex][0] != ARARAY_MARK_UPPER && m_pszArray[ucPushIndex][1] != ARARAY_MARK_LOWER ) {
            WhereIs;
            PrintDebug( (unsigned int) ucPushIndex );



#ifdef __VXWORKS__

            do {
                taskDelay( 10L );
                printf( "?" );
            } while( m_pszArray[ucPushIndex][0] != ARARAY_MARK_UPPER && m_pszArray[ucPushIndex][1] != ARARAY_MARK_LOWER );
#else
            do {
                Sleep( 1 );
                TRACE( "?" );

            } while( m_pszArray[ucPushIndex][0] != ARARAY_MARK_UPPER && m_pszArray[ucPushIndex][1] != ARARAY_MARK_LOWER );
#endif
        }
    }

#endif

    if( m_pszArray[ucPushIndex][0] != ARARAY_MARK_UPPER && m_pszArray[ucPushIndex][1] != ARARAY_MARK_LOWER ) {
        //LOGMSG( enError, "ArrayBuffer 가 손상 되었습니다 !!" );
        TRACE( "\n[%s] 가 죽었거나 메시지 처리를 못하고 있습니다. 관리자에게 문의하세요[%d] !" , GetThreadName(), ucPushIndex );
        //ShowTaskMessae( 0 );
        //WhereIs;
        SendTaskMngr( enERROR_OF_ARRAY_MARK, GetThreadName() );
        //PrintDebug( ucPushIndex );

        ucPushIndex = -1;
    }
    else {
	    if( uiLength > _MAX_LANDATA ) {
            TRACE( "************** 버퍼가 작습니다. _MAX_LANDATA 값을 늘려 주세요..." );
		    exit( 1 );
	    }

        memcpy( m_pszArray[ucPushIndex], pData, uiLength );

//         if( m_pszArray[ucPushIndex][0] == 0x0A ) {
//             TRACE( "*" );
//         }

    }

    m_theLock.UnLock();

    return ucPushIndex;
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
        SetMark( iIndex, true );

    }
    else {
        TRACE( "ArrayBuffer 인덱스[%d]가 잘못 되었습니다." , iIndex );
    }

    return;
}

/**
 * @brief     PrintDebug
 * @param     unsigned int ucPushIndex
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-03 14:01:23
 * @warning
 */
void CArrayMsgData::PrintDebug( unsigned int ucPushIndex )
{
    int i;

    if( (int) ucPushIndex >= 0 ) {
        TRACE( "ucPushIndex=%d\n", ucPushIndex );
    }
    else {

    }

    for( i = 0; i < SIZE_OF_MSGDATA_ARRAY; ++i ) {
        TRACE( "%d=0x%x\t", i, m_pszArray[i][0] );
//         if( m_pszArray[i][0] != ARARAY_MARK_UPPER ) {
//             TRACE( "\n m_pszArray[%d][0]=%s", i, (char *) m_pszArray[i][0] );
//         }
    }
    TRACE( "\n" );

}
