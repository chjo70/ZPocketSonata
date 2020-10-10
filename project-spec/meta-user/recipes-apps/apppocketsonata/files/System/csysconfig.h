#ifndef CSYSCONFIG_H
#define CSYSCONFIG_H

#include "../Include/system.h"

#include "csharedmemory.h"

struct STR_SYSCONFIG {
    /**
     * @brief 보드 ID
     */
    ENUM_BoardID enBoardID;

    /**
     * @brief 장비 모드 상태
     */
    ENUM_MODE enMode;
} ;


/**
 * @brief 시스템 설정 관련 클래스 임.
 */
class CSysConfig
{
private:
    static CSysConfig* m_pInstance;
    static CSharedMemroy* m_pSharedMemory;

    STR_SYSCONFIG m_strConfig;

public:
    CSysConfig(void);
    virtual ~CSysConfig(void);

    static CSysConfig* getInstance();
    static void ReleaseInstance();

private:

public:
    ENUM_BoardID GetBoardID() { return m_strConfig.enBoardID; };
    void SetBoardID(ENUM_BoardID enBoardID) {
        m_strConfig.enBoardID = enBoardID;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };

    ENUM_MODE GetMode() { return m_strConfig.enMode; };
    void SetMode(ENUM_MODE enMode) {
        m_strConfig.enMode = enMode;

        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    };


};

#define GP_SYSCFG CSysConfig::getInstance()

#endif // CSYSCONFIG_H
