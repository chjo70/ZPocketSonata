/**

    @file      clogname.cpp
    @brief
    @details   ~
    @author    조철희
    @date      5.11.2023
    @copyright © LIGNex1, 2023. All right reserved.

**/

#include "pch.h"

#include "clogname.h"

// CLogName 에 있는 클래스의 전역 변수 선언 합니다.
char CLogName::m_szName[enETC_ANAL+1][10];

/**
 * @brief     CLogName
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-29 15:40:44
 * @warning
 */
CLogName::CLogName()
{
    m_pThreadName = NULL;
    m_enAnalType = enETC_ANAL;

    if( m_szName[0][0] == 0 ) {
        strcpy( m_szName[enCLEAR_ANAL], "배포" );

        strcpy( m_szName[enDET_ANAL], "탐지" );
        strcpy( m_szName[enTRK_ANAL], "추적" );
        strcpy( m_szName[enDETTRK_ANAL], "탐지/추적" );
        strcpy( m_szName[enDETTRK_ANAL], "탐지/추적" );
        strcpy( m_szName[enSCN_ANAL], "스캔" );
        strcpy( m_szName[enDETSCN_ANAL], "탐지/스캔" );
        strcpy( m_szName[enDETTRKSCN_ANAL], "탐지/추적/스캔" );

        strcpy( m_szName[enETC_ANAL], "기타" );
    }

}

/**
 * @brief     CLogName
 * @param     const char * pThreadName
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-29 16:23:34
 * @warning
 */
CLogName::CLogName( const char *pThreadName )
{
    CLogName();

    SetThreadName( pThreadName );
}

/**
 * @brief     ~CLogName
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-29 15:40:45
 * @warning
 */
CLogName::~CLogName()
{


}
