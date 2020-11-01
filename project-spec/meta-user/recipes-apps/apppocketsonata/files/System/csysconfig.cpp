#include <stdio.h>
#include <stdlib.h>

#include "csysconfig.h"

#include "../Anal/SigAnal/_Macro.h"

CSysConfig* CSysConfig::m_pInstance = NULL;
CSharedMemroy* CSysConfig::m_pSharedMemory = NULL;

#ifdef __cplusplus
extern "C"
{
#endif

extern void ProgramRevision( void );

#ifdef __cplusplus
}
#endif

CSysConfig::CSysConfig(void)
{

    // 공유 메모리 설정
    m_pSharedMemory = new CSharedMemroy( _SHM_MEMORY_KEY, sizeof(STR_SYSCONFIG) );

    InitVar();

    LoadINI();



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

/**
 * @brief CSysConfig::LoadINI
 */
void CSysConfig::LoadINI()
{
    int i;
    string strValue;
    char szHomeDirectory[100];

    float fRxThreshold[5];

    // INI 파일 로딩하기
    strcpy( szHomeDirectory, getenv("HOME") );
    strcat( szHomeDirectory, INI_FILENAME );

    m_theMinIni.setfilename( szHomeDirectory );
    //m_theMinIni.put( "RXTHRESHOLD" , "Band1" , "-70.0" );

    // RX Threshold 값 로딩
    i = 0;
    strValue = m_theMinIni.gets( "RXTHRESHOLD" , "Band1" , "-60.0" );
    fRxThreshold[i++] = atof( strValue.c_str() );
    strValue = m_theMinIni.gets( "RXTHRESHOLD" , "Band2" , "-65.0" );
    fRxThreshold[i++] = atof( strValue.c_str() );
    strValue = m_theMinIni.gets( "RXTHRESHOLD" , "Band3" , "-65.0" );
    fRxThreshold[i++] = atof( strValue.c_str() );
    strValue = m_theMinIni.gets( "RXTHRESHOLD" , "Band4" , "-64.0" );
    fRxThreshold[i++] = atof( strValue.c_str() );
    strValue = m_theMinIni.gets( "RXTHRESHOLD" , "Band5" , "-60.0" );
    fRxThreshold[i++] = atof( strValue.c_str() );

    SetRxThreshold( fRxThreshold );

    // 최소 펄스 개수
    strValue = m_theMinIni.geti( "ANAL" , "MIN_ANALPULSE" , _spAnalMinPulseCount );
    SetMinAnalPulse( _spAnalMinPulseCount );

    // 프로그램 버젼 정보
    SetProgramVersion( _GetProgramVersion() );
}

/**
 * @brief CSysConfig::InitVar
 */
void CSysConfig::InitVar()
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

    _spAnalMinPulseCount = 6;
}
