#ifndef CSYSCONFIG_H
#define CSYSCONFIG_H

#include "../Include/system.h"


/**
 * @brief 시스템 설정 관련 클래스 임.
 */
class CSysConfig
{
private:
    static CSysConfig* m_pInstance;

public:
    CSysConfig(void);
    virtual ~CSysConfig(void);

    static CSysConfig* getInstance();
    static void ReleaseInstance();

private:
    /**
     * @brief 보드 ID
     */
    ENUM_BoardID m_enBoardID;

    /**
     * @brief 장비 모드 상태
     */
    ENUM_MODE m_enMode;

public:
    ENUM_BoardID GetBoardID() { return m_enBoardID; };
    void SetBoardID(ENUM_BoardID enBoardID) { m_enBoardID = enBoardID; };

    ENUM_MODE GetMode() { return m_enMode; };
    void SetMode(ENUM_MODE enMode) { m_enMode = enMode; };


};

#define GP_SYSCFG CSysConfig::getInstance()

#endif // CSYSCONFIG_H
