
#include "stdafx.h"


#include "cipl.h"


#include "../../Include/globals.h"

/**
 * @brief     CIPL
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
 * @brief     InitVar
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
 * @brief		setIPLStart
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

