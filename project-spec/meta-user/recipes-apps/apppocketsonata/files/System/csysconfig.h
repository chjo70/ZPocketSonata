#ifndef CSYSCONFIG_H
#define CSYSCONFIG_H

#include <string.h>

#include "../Anal/INC/system.h"

#ifndef _MSC_VER
#include "../MinIni/minIni.h"
#endif


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
    unsigned int uiMinAnalPulse;

    /**
     * @brief 기본 삭제 시간 [초]
     */
    int iEmitterDeleteTime;

    /**
     * @brief 대역별 임계값
     */
    float fRxThreshold[enMAXPRC - 1];

    /**
     * @brief 대역별 병합 방위 오차
     */
    float fMergeAOADiff[enMAXPRC-1];

    /**
     * @brief 최근 연결된 서버 IP 주소
     */
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

    // 탐지/추적/스캔 채널 정보
    /**
     * @brief 탐지 채널 정보
     */
    STR_WINDOWCELL strDetectWindowCell[DETECT_CHANNEL];

    /**
     * @brief 추적 채널 정보
     */
    STR_WINDOWCELL strTrackWindowCell[TRACK_CHANNEL];

    /**
     * @brief 스캔 채널 정보
     */
    STR_WINDOWCELL strScanWindowCell[SCAN_CHANNEL];

    /**
     * @brief 사용자 채널 정보
     */
    STR_WINDOWCELL strUserWindowCell[USER_CHANNEL];

    unsigned char ucColHisto[COLHISTO_TIME][COLHISTO_CELLS];

} ;


/**
 * @brief 시스템 설정 관련 클래스 임.
 */
class CSysConfig
{
private:
    static CSharedMemroy* m_pSharedMemory;

    STR_SYSCONFIG m_strConfig;

#ifndef _MSC_VER
    minIni m_theMinIni;
#else
    
#endif

    char m_szIniFileName[200];

	/**
	 * @brief 분석 초기화 순번
	 */
	unsigned int m_uiOpInitID;

public:
    CSysConfig(void);
    virtual ~CSysConfig(void);

private:
    void InitVar();
    void LoadINI();

    void SetNetworkIP();
    bool GetIPAddress( char *pIPAddress, char *pNetworkName );

    void DisplaySystemVar();

public:
    void SetWindowCell( unsigned int uiCh, STR_WINDOWCELL *pWindowCell );

public:
    inline STR_SYSCONFIG *GetSysConfig() { return & m_strConfig; }

	inline UINT GetOpInitID() { return m_uiOpInitID; };
	inline void IncOpInitID() {
		++m_uiOpInitID;
	};


    ENUM_BoardID GetBoardID() { return m_strConfig.enBoardID; };
    void SetBoardID(ENUM_BoardID enBoardID) {
        m_strConfig.enBoardID = enBoardID;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };

    unsigned int GetIPLVersion() { return m_strConfig.uiIPLVersion; };
    void SetIPLVersion( const unsigned int uiIPLVersion ) {
        m_strConfig.uiIPLVersion = uiIPLVersion;
#ifdef _MSC_VER
        char szBuffer[100];

        sprintf_s( szBuffer , "%d", uiIPLVersion );
        WritePrivateProfileString( "IPL", "VERSION", szBuffer, m_szIniFileName );
#else
        m_theMinIni.put( "IPL", "VERSION", (int) uiIPLVersion );
#endif
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };


    char *GetProgramVersion() { return m_strConfig.szProgramVersion; };
    void SetProgramVersion(char *pProgramVersion ) {
        strcpy( m_strConfig.szProgramVersion, pProgramVersion );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };

    unsigned int GetMinAnalPulse() { return m_strConfig.uiMinAnalPulse; };
    void SetMinAnalPulse(unsigned int uiMinAnalPulse ) {
        m_strConfig.uiMinAnalPulse = uiMinAnalPulse;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };

    int GetEmmgEmitterDeleteTimeSec() { return m_strConfig.iEmitterDeleteTime; };
    void SetEmmgEmitterDeleteTimeSec(int iDeleteTime  ) {
        m_strConfig.iEmitterDeleteTime = iDeleteTime;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };

    float GetMergeAOADiff(ENUM_BoardID enBoardID) { 
        float fValue= m_strConfig.fMergeAOADiff[enPRC1];

        if(enBoardID >= enPRC1 && enBoardID <= enPRC5 )
            fValue = m_strConfig.fMergeAOADiff[enBoardID- enPRC1]; 

        return fValue;

    };
    void SetMergeAOADiff(float *fValue) {
        memcpy(m_strConfig.fMergeAOADiff, fValue, sizeof(m_strConfig.fMergeAOADiff));
        m_pSharedMemory->copyToSharedMemroy(&m_strConfig);
    };

    float *GetRxThreshold() { return & m_strConfig.fRxThreshold[0]; };
    void SetRxThreshold( float *fValue) {
        memcpy( m_strConfig.fRxThreshold, fValue, sizeof(m_strConfig.fRxThreshold) );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    };

    char *GetPrimeServerOfNetwork() { return & m_strConfig.szPrimeServer[0]; };
    void SetPrimeServerOfNetwork( const char *pPrimeServer, bool bINI=false ) {
        strcpy( m_strConfig.szPrimeServer, pPrimeServer );
        if( bINI == true ) {
#ifdef _MSC_VER
            WritePrivateProfileString( "NETWORK" , "PRIME_SERVER", pPrimeServer, m_szIniFileName );
#else
            m_theMinIni.put( "NETWORK" , "PRIME_SERVER" , pPrimeServer );
#endif
        }
    };

    ENUM_MODE GetMode() { return m_strConfig.enMode; };
    void SetMode(ENUM_MODE enMode) {
        if( enMode == enANAL_Mode ) {
            m_strConfig.enMode = ( ENUM_MODE ) ( (unsigned int) m_strConfig.enMode | (unsigned int) enANAL_Mode );
        }
        else {
            m_strConfig.enMode = enMode;
        }

        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    };

    char *GetLocalIPAddress() { return m_strConfig.szLocalIPAddress; };
    void SetLocalIPAddress( const char *pIPAddress ) {
        strcpy( m_strConfig.szLocalIPAddress, pIPAddress );
    } ;

    STR_WINDOWCELL *GetDetectWindowCell( unsigned int uiCh ) { return & m_strConfig.strDetectWindowCell[uiCh]; }
    void SetDetectWindowCell( unsigned int uiCh, STR_WINDOWCELL *pWindowCell ) {
        memcpy( & m_strConfig.strDetectWindowCell[uiCh], pWindowCell, sizeof(STR_WINDOWCELL) );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    STR_WINDOWCELL *GetTrackWindowCell( unsigned int uiCh ) { return & m_strConfig.strTrackWindowCell[uiCh]; }
    void SetTrackWindowCell( unsigned int uiCh, STR_WINDOWCELL *pWindowCell ) {
        memcpy( & m_strConfig.strTrackWindowCell[uiCh], pWindowCell, sizeof(STR_WINDOWCELL) );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    STR_WINDOWCELL *GetScanWindowCell( unsigned int uiCh ) { return & m_strConfig.strScanWindowCell[uiCh]; }
    void SetScanWindowCell( unsigned int uiCh, STR_WINDOWCELL *pWindowCell ) {
        memcpy( & m_strConfig.strScanWindowCell[uiCh], pWindowCell, sizeof(STR_WINDOWCELL) );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    STR_WINDOWCELL *GetUserWindowCell( unsigned int uiCh ) { return & m_strConfig.strUserWindowCell[uiCh]; }
    void SetUserWindowCell( unsigned int uiCh, STR_WINDOWCELL *pWindowCell ) {
        memcpy( & m_strConfig.strUserWindowCell[uiCh], pWindowCell, sizeof(STR_WINDOWCELL) );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    void SetColHisto() {
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    unsigned char (*GetColHisto()) [(MAX_FREQ_MHZ-MIN_FREQ_MHZ)/COLHISTO_WIDTH_MHZ] { return m_strConfig.ucColHisto; }


};

#endif // CSYSCONFIG_H
