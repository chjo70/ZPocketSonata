#include <stdio.h>

#include "csysconfig.h"

CSysConfig* CSysConfig::m_pInstance = NULL;

CSysConfig::CSysConfig(void)
    :m_enBoardID(enMaster),
     m_enMode(enREADY_MODE)
{

}

/**
 * @brief CSysConfig::~CSysConfig
 */
CSysConfig::~CSysConfig(void)
{
}

/**
 * @brief CSysConfig::getInstance
 * @return
 */
CSysConfig* CSysConfig::getInstance()
{
    if(!m_pInstance)
    {
        m_pInstance = new CSysConfig;
    }
    return m_pInstance;
}

/**
 * @brief CSysConfig::ReleaseInstance
 */
void CSysConfig::ReleaseInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}
