/**

    @file      CSYSCONFIG.H
    @brief
    @details   ~
    @author    조철희
    @date      2.05.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once



#include "../Anal/INC/system.h"

#include <string.h>

//#ifndef _MSC_VER
#include "../MinIni/minIni.h"
//#endif


#include "../Utils/clog.h"

#include "csharedmemory.h"

struct STR_SYSCONFIG {
    /**
     * @brief 보드 ID
     */
    ENUM_BoardID enBoardID;

    /**
     * @brief 프로그램 버젼 정보
     */
    char szProgramVersion[50];

    /**
     * @brief 최소 분석 개수
     */
    unsigned int uiMinAnalPulse;

    /**
     * @brief 기본 삭제 시간 [초]
     */
    int iEmitterDeleteTime;

    //!< 탐지 분석에서 최대 LOB 개수
    unsigned int uiMaxCountOfLOB;

	/**
		 * @brief 방위 그룹화 범위
	*/
	float fAOAGroup[enMAXPRC - 1];

    /**
         * @brief 주파수 그룹화 범위
    */
    float fFRQGroup[enMAXPRC - 1];

    /**
     * @brief 대역별 임계값
     */
    float fRxThreshold[enMAXPRC - 1];


    //!<  Fixed 주파수, 규칙성 펄스열 DTOA 마진 값 정의
    float fMargin[2];

    //!<     그룹화 마진 정의
    unsigned int uiAOAGroupMargin;

    //!<     고정형 최소 신호세기 정의
    int iMinSteadyPAAmplitude;

    //!<     CONICAL 최소 스캔 주기 정의 [ms]
    unsigned int uiMinConicalPeriod;

    //!<     CONICAL 최대 스캔 주기 정의 [ms]
    unsigned int uiMaxConicalPeriod;

    //! @brief 방위 필터 마진
    float fWindowCellDOARange;

    //! @brief 주파수 필터 마진
    float fWindowCellFRQRange;

    //! @brief 주파수 호핑 필터 마진
    float fWindowCellFRQHoppingRatio;

    /**
     * @brief 대역별 병합 방위 오차
     */
    float fReceiverDOAError[enMAXPRC-1];

    /**
     * @brief 최근 연결된 서버 IP 주소
     */
    char szRecentServer[30];

    /**
    * @brief 운용 서버 IP 주소
    */
    //char szSecondServer[30];

    /**
     * @brief 최근 연결된 CCU 서버 IP 주소
     */
    char szCCUServer[30];

    /**
     * @brief 최근 연결된 Debug 서버 IP 주소
     */
    char szDebugServer[30];

    /**
     * @brief 장치 내의 SBC 시작 IP 주소
     */
    int iSBCFromIP;

    /**
     * @brief 장치 내의 SBC 종료 IP 주소
     */
    int iSBCToIP;

    /**
     * @brief TFFS 옵션 설정
     */
    int iTFFSBoot;

    /**
     * @brief 장비 모드 상태
     */
    //ENUM_MODE enMode;

    /**
     * @brief IPL 버젼 정보
     */
    UINT uiIPLVersion;

    /**
     * @brief CPU 온도 경고 임계값
     */
    UINT uiCPUTempWarning;

    /**
     * @brief IP 어드레스
     */
    char szLocalIPAddress[30];

    // 탐지/추적/스캔 채널 정보
    /**
     * @brief 탐지 채널 정보
     */
    STR_WINDOWCELL strDetectWindowCell[CO_DEFAULT_DETECT_CHANNEL];

    /**
     * @brief 추적 채널 정보
     */
    STR_WINDOWCELL strTrackWindowCell[CO_DEFAULT_TRACK_CHANNEL];

    /**
     * @brief 스캔 채널 정보
     */
    STR_WINDOWCELL strScanWindowCell[CO_DEFAULT_SCAN_CHANNEL];

    /**
     * @brief 사용자 채널 정보
     */
    STR_WINDOWCELL strUserWindowCell[CO_DEFAULT_USER_CHANNEL];

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
    minIni m_theMinIni;

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


    void SetNetworkIP();
    bool GetIPAddress( char *pIPAddress, char *pNetworkName );

public:
    void LoadINI();
    void DisplaySystemVar();
    void SetWindowCell( unsigned int uiCh, STR_WINDOWCELL *pWindowCell );

    void WritePrimeServerIPAddress( char *pIPAddress );

    void WritePresentTime( char *pPresentTime );
    void GetPresentTime( struct timespec *pTime );

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
    void SetIPLVersion( unsigned int uiIPLVersion ) {
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

    unsigned int GetCPUTempWarning() { return m_strConfig.uiCPUTempWarning; };
    void SetCPUTempWarning( unsigned int uiCPUTempWarning )
    {
        m_strConfig.uiCPUTempWarning = uiCPUTempWarning;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };


    char *GetProgramVersion() { return m_strConfig.szProgramVersion; };
    void SetProgramVersion( const char *pProgramVersion ) {
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

    unsigned int GetMaxCountOfLOB() { return m_strConfig.uiMaxCountOfLOB; };
    void SetMaxCountOfLOB( unsigned int uiMaxCountOfLOB )
    {
        m_strConfig.uiMaxCountOfLOB = uiMaxCountOfLOB;
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );

    };

    float* GetReceiverDOAError() { return & m_strConfig.fReceiverDOAError[0]; }
    float GetReceiverDOAError(ENUM_BoardID enBoardID) {
        float fValue= m_strConfig.fReceiverDOAError[enPRC1];

        if(enBoardID >= enPRC1 && enBoardID <= enPRC5 ) {
            fValue = m_strConfig.fReceiverDOAError[enBoardID- enPRC1];
        }

        return fValue;

    };
    void SetReceiverDOAError(float *fValue) {
        memcpy(m_strConfig.fReceiverDOAError, fValue, sizeof(m_strConfig.fReceiverDOAError ));
        m_pSharedMemory->copyToSharedMemroy(&m_strConfig);
    };

    float *GetAOAGroup() { return & m_strConfig.fAOAGroup[0]; }
	void SetAOAGroup(float *fValue) {
		memcpy(m_strConfig.fAOAGroup, fValue, sizeof(m_strConfig.fAOAGroup));
		m_pSharedMemory->copyToSharedMemroy(&m_strConfig);
	};

    float *GetFRQGroup() { return & m_strConfig.fFRQGroup[0]; }
    void SetFRQGroup( float *fValue )
    {
        memcpy( m_strConfig.fFRQGroup, fValue, sizeof( m_strConfig.fFRQGroup ) );
        m_pSharedMemory->copyToSharedMemroy( &m_strConfig );
    };


    unsigned int GetAOAGroupMargin() { return m_strConfig.uiAOAGroupMargin; }
    void SetAOAGroupMargin( unsigned int uiValue )
    {
        m_strConfig.uiAOAGroupMargin = uiValue;
        m_pSharedMemory->copyToSharedMemroy( &m_strConfig );
    };

    int GetSteadyMinPA() { return m_strConfig.iMinSteadyPAAmplitude; }
    void SetSteadyMinPA( int iValue )
    {
        m_strConfig.iMinSteadyPAAmplitude = iValue;
        m_pSharedMemory->copyToSharedMemroy( &m_strConfig );
    };

    unsigned int GetConcalMinPeriod() { return m_strConfig.uiMinConicalPeriod; }
    void SetConcalMinPeriod( unsigned int uiValue )
    {
        m_strConfig.uiMinConicalPeriod = uiValue;
        m_pSharedMemory->copyToSharedMemroy( &m_strConfig );
    };

    unsigned int GetConcalMaxPeriod() { return m_strConfig.uiMaxConicalPeriod; }
    void SetConcalMaxPeriod( unsigned int uiValue )
    {
        m_strConfig.uiMaxConicalPeriod = uiValue;
        m_pSharedMemory->copyToSharedMemroy( &m_strConfig );
    };

    float GetWindowCellDOARange() { return m_strConfig.fWindowCellDOARange; }
    void SetWindowCellDOARange( float fValue )
    {
        m_strConfig.fWindowCellDOARange = fValue;
        m_pSharedMemory->copyToSharedMemroy( &m_strConfig );
    };

    float GetWindowCellFRQRange() { return m_strConfig.fWindowCellFRQRange; }
    void SetWindowCellFRQRange( float fValue )
    {
        m_strConfig.fWindowCellFRQRange = fValue;
        m_pSharedMemory->copyToSharedMemroy( &m_strConfig );
    };

    float GetWindowCellFRQHoppingRatio() { return m_strConfig.fWindowCellFRQHoppingRatio; }
    void SetWindowCellFRQHoppingRatio( float fValue )
    {
        m_strConfig.fWindowCellFRQHoppingRatio = fValue;
        m_pSharedMemory->copyToSharedMemroy( &m_strConfig );
    };


    float *GetMargin() { return & m_strConfig.fMargin[0]; }
    float GetMargin(unsigned int uiIndex) { return m_strConfig.fMargin[uiIndex]; }
    void SetMargin( float *pfValue )
    {
        memcpy( m_strConfig.fMargin, pfValue, sizeof( m_strConfig.fMargin ) );
        m_pSharedMemory->copyToSharedMemroy( &m_strConfig );
    };

    float *GetRxThreshold() { return & m_strConfig.fRxThreshold[0]; };
    void SetRxThreshold( float *fValue) {
        memcpy( m_strConfig.fRxThreshold, fValue, sizeof(m_strConfig.fRxThreshold) );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    };

    char *GetRecentConnectionOfNetwork() { return & m_strConfig.szRecentServer[0]; };
    void SetPrimeServerOfNetwork( const char *pPrimeServer, bool bINI=false ) {
        strcpy( m_strConfig.szRecentServer, pPrimeServer );
        if( bINI == true ) {
#ifdef _MSC_VER
            WritePrivateProfileString( "NETWORK" , "PRIME_SERVER", pPrimeServer, m_szIniFileName );
#else
            m_theMinIni.put( "NETWORK" , "PRIME_SERVER" , pPrimeServer );
#endif
        }
    };

//     char *GetSecondServerOfNetwork() { return & m_strConfig.szSecondServer[0]; };
//     void SetSecondServerOfNetwork( const char *pSecondServer, bool bINI = false )
//     {
//         strcpy( m_strConfig.szSecondServer, pSecondServer );
//         if( bINI == true ) {
// #ifdef _MSC_VER
//             WritePrivateProfileString( "NETWORK", "SECOND_SERVER", pSecondServer, m_szIniFileName );
// #else
//             m_theMinIni.put( "NETWORK", "SECOND_SERVER", pSecondServer );
// #endif
//         }
//     };

    char *GetCCUServerOfNetwork() { return & m_strConfig.szCCUServer[0]; };
    void SetCCUServerOfNetwork( const char *pCCUServer, bool bINI = false )
    {
        strcpy( m_strConfig.szCCUServer, pCCUServer );
        if( bINI == true ) {
#ifdef _MSC_VER
            WritePrivateProfileString( "NETWORK", "CCU_SERVER_IP_ADDRESS", pCCUServer, m_szIniFileName );
#else
            m_theMinIni.put( "NETWORK", "CCU_SERVER_IP_ADDRESS", pCCUServer );
#endif
        }
    };

    char *GetDebugServerOfNetwork() { return & m_strConfig.szDebugServer[0]; };
    void SetDebugServerOfNetwork( const char *pDebugServer, bool bINI = false )
    {
        strcpy( m_strConfig.szDebugServer, pDebugServer );
        if( bINI == true ) {
#ifdef _MSC_VER
            WritePrivateProfileString( "NETWORK", "DEBUG_SERVER_IP_ADDRESS", pDebugServer, m_szIniFileName );
#else
            m_theMinIni.put( "NETWORK", "DEBUG_SERVER_IP_ADDRESS", pDebugServer );
#endif
        }
    };

    int GetSBCFromIP() { return m_strConfig.iSBCFromIP; };
    void SetSBCFromIP( const int iValue )
    {
        m_strConfig.iSBCFromIP = iValue;
    };

    int GetSBCToIP() { return m_strConfig.iSBCToIP; };
    void SetSBCToIP( const int iValue )
    {
        m_strConfig.iSBCToIP = iValue;
    };

    int GetTFFSBoot() { return m_strConfig.iTFFSBoot; };
    void SetTFFSBoot( const int iValue )
    {
        m_strConfig.iTFFSBoot = iValue;
    };

    //ENUM_MODE GetMode() { return m_strConfig.enMode; };
//     void SetMode(ENUM_MODE enMode) {
//         if( enMode == enANAL_Mode ) {
//             m_strConfig.enMode = ( ENUM_MODE ) ( (unsigned int) m_strConfig.enMode | (unsigned int) enANAL_Mode );
//         }
//         else {
//             m_strConfig.enMode = enMode;
//         }
//
//         m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
//     };

    char *GetLocalIPAddress() { return m_strConfig.szLocalIPAddress; };
    void SetLocalIPAddress( const char *pIPAddress ) {
        strcpy( m_strConfig.szLocalIPAddress, pIPAddress );
    } ;

    STR_WINDOWCELL *GetDetectWindowCell( unsigned int uiCh ) { return & m_strConfig.strDetectWindowCell[uiCh]; }
    void SetDetectWindowCell( unsigned int uiCh, STR_WINDOWCELL *pWindowCell ) {
        memcpy( & m_strConfig.strDetectWindowCell[uiCh], pWindowCell, sizeof( STR_WINDOWCELL) );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    STR_WINDOWCELL *GetTrackWindowCell( unsigned int uiCh ) { return & m_strConfig.strTrackWindowCell[uiCh]; }
    void SetTrackWindowCell( unsigned int uiCh, STR_WINDOWCELL *pWindowCell ) {
        memcpy( & m_strConfig.strTrackWindowCell[uiCh], pWindowCell, sizeof( STR_WINDOWCELL) );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    STR_WINDOWCELL *GetScanWindowCell( unsigned int uiCh ) { return & m_strConfig.strScanWindowCell[uiCh]; }
    void SetScanWindowCell( unsigned int uiCh, STR_WINDOWCELL *pWindowCell ) {
        memcpy( & m_strConfig.strScanWindowCell[uiCh], pWindowCell, sizeof( STR_WINDOWCELL) );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    STR_WINDOWCELL *GetUserWindowCell( unsigned int uiCh ) { return & m_strConfig.strUserWindowCell[uiCh]; }
    void SetUserWindowCell( unsigned int uiCh, STR_WINDOWCELL *pWindowCell ) {
        memcpy( & m_strConfig.strUserWindowCell[uiCh], pWindowCell, sizeof( STR_WINDOWCELL) );
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    void SetColHisto() {
        m_pSharedMemory->copyToSharedMemroy( & m_strConfig );
    }

    unsigned char (*GetColHisto()) [(MAX_FREQ_MHZ-MIN_FREQ_MHZ)/COLHISTO_WIDTH_MHZ] { return m_strConfig.ucColHisto; }


};


