#include "cipl.h"

//#include "../../System/csysconfig.h"

CIPL::CIPL()
{
    InitVar();
}

/**
 * @brief CIPL::InitVar
 */
void CIPL::InitVar()
{
    memset( & m_strIPLStart, 0, sizeof(STR_IPL_START) );

    m_strIPLStart.uiIPLVersion = GP_SYSCFG->GetIPLVersion();

}
