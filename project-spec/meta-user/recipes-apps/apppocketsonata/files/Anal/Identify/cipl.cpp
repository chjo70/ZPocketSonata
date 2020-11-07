#include "cipl.h"

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

}
