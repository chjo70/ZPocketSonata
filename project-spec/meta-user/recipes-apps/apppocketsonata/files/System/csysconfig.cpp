#include <stdio.h>

#include "csysconfig.h"

#include "../Anal/SigAnal/_Macro.h"

CSysConfig* CSysConfig::m_pInstance = NULL;
CSharedMemroy* CSysConfig::m_pSharedMemory = NULL;

CSysConfig::CSysConfig(void)
{
    m_strConfig.enBoardID = enMaster;
    m_strConfig.enMode = enREADY_MODE;

    _spOneSec = 20000000.;
    _spOneMilli = FDIV( _spOneSec, 1000. );
    _spOneMicrosec = FDIV( _spOneMilli, 1000. );
    _spOneNanosec = FDIV( _spOneMicrosec, 1000. );

    _spAOAres = (float) ( 0.351562 );
    _spAMPres = (float) (0.351562);
    _spPWres = _spOneMicrosec;


    // ���� �޸� ����
    m_pSharedMemory = new CSharedMemroy( _SHM_MEMORY_KEY, sizeof(STR_SYSCONFIG) );

}

/**
 * @brief CSysConfig::~CSysConfig
 */
CSysConfig::~CSysConfig(void)
{
    m_pSharedMemory->close();
    delete m_pSharedMemory;
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
