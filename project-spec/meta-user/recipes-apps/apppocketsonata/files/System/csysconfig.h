#ifndef CSYSCONFIG_H
#define CSYSCONFIG_H

#include "../Anal/INC/system.h"

#include "../MinIni/minIni.h"
#include "csharedmemory.h"

struct STR_SYSCONFIG {
    /**
     * @brief 보드 ID
     */
    ENUM_BoardID enBoardID;

    /**
     * @brief 프로그램 버젼 정보
     */
    char szProgramVersion[10];

    /**
     * @brief 최소 분석 개수
     */
    int iMinAnalPulse;

    /**
     * @brief 기본 삭제 시간 [초]
     */
    int iEmitterDeleteTime;

    /**
     * @brief 대역별 임계값
     */
    float fRxThreshold[5];

    char szPrimeServer[30];

    /**
     * @brief 장비 모드 상태
     */
    ENUM_MODE enMode;

    /**
     * @brief IPL 버젼 정보
     */
    UINT uiIPLVersion;

    /**
     * @brief IP 어드레스
     */
    char szLocalIPAddress[30];

    void *m_pTheDetectCollectBank[DETECT_CHANNEL];
    void *m_pTheTrackCollectBank[TRACK_CHANNEL];
    void *m_pTheScanCollectBank[SCAN_CHANNEL];
    void *m_pTheUserCollectBank[USER_CHANNEL];

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

    minIni m_theMinIni;

public:
    CSysConfig(void);
    virtual ~CSysConfig(void);

    static CSysConfig* getInstance();
    static void ReleaseInstance();

private:
    void InitVar();
    void LoadINI();

    void SetNetworkIP();
    bool GetIPAddress( char *pIPAddress, char *pNetworkName );

public:
    ENUM_BoardID GetBoardID() { return m_strConfig.enBoardID; };
    void SetBoardID(ENUM_BoardID enBoardID) {
        m_strConfig.enBoardID = enBoardID;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };

    unsigned int GetIPLVersion() { return m_strConfig.uiIPLVersion; };
    void SetIPLVersion( const unsigned int uiIPLVersion ) {
        m_strConfig.uiIPLVersion = uiIPLVersion;
        m_theMinIni.put( "IPL", "VERSION", (int) uiIPLVersion );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };


    char *GetProgramVersion() { return m_strConfig.szProgramVersion; };
    void SetProgramVersion(char *pProgramVersion ) {
        strcpy( m_strConfig.szProgramVersion, pProgramVersion );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };

    int GetMinAnalPulse() { return m_strConfig.iMinAnalPulse; };
    void SetMinAnalPulse(int iMinAnalPulse ) {
        m_strConfig.iMinAnalPulse = iMinAnalPulse;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };

    int GetEmmgEmitterDeleteTimeSec() { return m_strConfig.iEmitterDeleteTime; };
    void SetEmmgEmitterDeleteTimeSec(int iDeleteTime  ) {
        m_strConfig.iEmitterDeleteTime = iDeleteTime;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };

    float *GetRxThreshold() { return & m_strConfig.fRxThreshold[0]; };
    void SetRxThreshold( float *fRxThreshold ) {
        memcpy( m_strConfig.fRxThreshold, fRxThreshold, sizeof(m_strConfig.fRxThreshold) );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    };

    char *GetPrimeServerOfNetwork() { return & m_strConfig.szPrimeServer[0]; };
    void SetPrimeServerOfNetwork( const char *pPrimeServer, bool bINI=false ) {
        strcpy( m_strConfig.szPrimeServer, pPrimeServer );
        if( bINI == true ) {
            m_theMinIni.put( "NETWORK" , "PRIME_SERVER" , pPrimeServer );
        }
    };

    ENUM_MODE GetMode() { return m_strConfig.enMode; };
    void SetMode(ENUM_MODE enMode) {
        if( enMode == enANAL_Mode ) {
            m_strConfig.enMode = ( ENUM_MODE ) ( m_strConfig.enMode | enANAL_Mode );
        }
        else {
            m_strConfig.enMode = enMode;
        }

        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    };

    char *GetLocalIPAddress() { return m_strConfig.szLocalIPAddress; };
    void SetLocalIPAddress( char *pIPAddress ) {
        strcpy( m_strConfig.szLocalIPAddress, pIPAddress );
    } ;

    void *GetDetectCollectBnk( int iCh ) { return m_strConfig.m_pTheDetectCollectBank[iCh]; }
    void SetDetectCollectBank( int iCh, void *pCollectBank ) {
        m_strConfig.m_pTheDetectCollectBank[iCh] = pCollectBank;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    void *GetTrackCollectBnk( int iCh ) { return m_strConfig.m_pTheTrackCollectBank[iCh]; }
    void SetTrackCollectBank( int iCh, void *pCollectBank ) {
        m_strConfig.m_pTheTrackCollectBank[iCh] = pCollectBank;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    void *GetScanCollectBnk( int iCh ) { return m_strConfig.m_pTheScanCollectBank[iCh]; }
    void SetScanCollectBank( int iCh, void *pCollectBank ) {
        m_strConfig.m_pTheScanCollectBank[iCh] = pCollectBank;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    void *GetUserCollectBnk( int iCh ) { return m_strConfig.m_pTheUserCollectBank[iCh]; }
    void SetUserCollectBank( int iCh, void *pCollectBank ) {
        m_strConfig.m_pTheUserCollectBank[iCh] = pCollectBank;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

};

#define GP_SYSCFG CSysConfig::getInstance()

#endif // CSYSCONFIG_H
