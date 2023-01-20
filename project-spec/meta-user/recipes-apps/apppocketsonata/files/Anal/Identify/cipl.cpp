
#include "stdafx.h"


#include "cipl.h"


#include "../../Include/globals.h"

/**
 * @brief     기존 IPL 을 데이터 로딩 및 데이터 관리하기 위한 객체를 생성한다.
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 10:35
 * @warning
 */
CIPL::CIPL()
{
    InitVar();
}

/**
 * @brief     객체내의 변수를 초기화한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 10:27
 * @warning
 */
void CIPL::InitVar()
{
    memset( & m_strIPLStart, 0, sizeof(STR_IPL_START) );

    m_strIPLStart.uiIPLVersion = g_pTheSysConfig->GetIPLVersion();

}


/**
 * @brief		IPL 데이터의 시작 위치를 설정한다.
 * @param		STR_IPL_START * pIPLStart
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/23 15:32:01
 * @warning		
 */
void CIPL::setIPLStart( STR_IPL_START *pIPLStart ) 
{
    memcpy( & m_strIPLStart, pIPLStart, sizeof(STR_IPL_START) );

    g_pTheSysConfig->SetIPLVersion( m_strIPLStart.uiIPLVersion );

    m_iTotalIPL = 0;
} ;

