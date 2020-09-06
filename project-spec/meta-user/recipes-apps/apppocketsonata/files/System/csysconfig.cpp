#include <stdio.h>

#include "csysconfig.h"

#include "../Anal/SigAnal/_Macro.h"

CSysConfig* CSysConfig::m_pInstance = NULL;

CSysConfig::CSysConfig(void)
    :m_enBoardID(enMaster),
     m_enMode(enREADY_MODE)
{
    _spOneSec = 20000000.;
    _spOneMilli = FDIV( _spOneSec, 1000. );
    _spOneMicrosec = FDIV( _spOneMilli, 1000. );
    _spOneNanosec = FDIV( _spOneMicrosec, 1000. );

    _spAOAres = (float) ( 0.351562 );
    _spAMPres = (float) (0.351562);
    _spPWres = _spOneMicrosec;
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
