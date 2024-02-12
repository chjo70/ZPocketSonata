// CSysConfig.cpp: implementation of the CSysConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef __linux__
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#endif

#include "csysconfig.h"

#include "../Anal/SigAnal/_Macro.h"
#include "../Anal/SigAnal/_Struct.h"

#include "../Include/globals.h"

#include "../gen-versioninfo.h"

CSharedMemroy *CSysConfig::m_pSharedMemory = NULL;

unsigned int _spAnalMinPulseCount;

static char g_szDeviceName[5][10] = { "eth1", "wlo1", "enp0s8" } ;

#ifdef __VXWORKS__
MSG_Q_ID g_ShmMemMsgQID;
#define _SHM_MEMORY_KEY             g_ShmMemMsgQID

#endif

#ifdef __cplusplus
extern "C"
{
#endif

    extern void ProgramRevision( void );



#ifdef __cplusplus
}
#endif


/**
 * @brief     CSysConfig
 * @param     void
 * @return
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-21, 14:47
 * @warning
 */
CSysConfig::CSysConfig( void )
{

    // 공유 메모리 설정
    if( m_pSharedMemory == NULL ) {
        m_pSharedMemory = new CSharedMemroy( _SHM_MEMORY_KEY, sizeof( STR_SYSCONFIG ) );
    }

    InitVar();

    LoadINI();

}

/**
 * @brief     ~CSysConfig
 * @param     void
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-03 11:06:58
 * @warning
 */
CSysConfig::~CSysConfig( void )
{

    // m_pSharedMemory->closeSharedMemory();
    _SAFE_DELETE( m_pSharedMemory )

}

#ifdef __VXWORKS__
BOOL vx_access( const char *pFilename );

BOOL vx_access( const char *pFilename )
{
    FILE *file;
    BOOL bRet = FALSE;

    file = fopen( pFilename, "r" );

    if( file != NULL ) {
        fclose( file );
        // printf( "\n match !!" );
        bRet = TRUE;
    }

    return bRet;

}
#endif

/**
 * @brief     CheckDirectory
 * @param     const char * pFilename
 * @return    BOOL
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-14 10:50:39
 * @warning
 */
BOOL CheckDirectory( const char *pFilename )
{
    struct stat st;
    BOOL bRet=FALSE;

    if( stat( pFilename, & st ) == 0 ) {
        if( ( st.st_mode & S_IFMT ) == S_IFDIR ) {
            bRet = TRUE;
            printf( "\n Directory match !!" );
        }
        else {
            printf( "\n Directory not match !!" );
        }
    }

    return bRet;

}

/**
 * @brief     CheckBoardID
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-12 20:42:19
 * @warning
 */
ENUM_BoardID CSysConfig::CheckBoardID()
{
    ENUM_BoardID enBoardId;

#ifdef __VXWORKS__
    int i;
    char szIniFileName[200];

    for( i = ( int ) enPRC1; i <= ( int ) enPRC5; ++i ) {
        //         sprintf( szIniFileName, "%s/%s_%d", INI_BOARDID_FOLDER, INI_BOARDID_DIRECTORY, i );
        //         printf( "\n directory[%s]  !", szIniFileName );
        //         if( TRUE == CheckDirectory( szIniFileName ) ) {
        //             break;
        //         }

        sprintf( szIniFileName, "%s/%s_%d", INI_FOLDER, INI_FILENAME_BOARDID, i );
#ifdef __VXWORKS__
        if( vx_access( szIniFileName ) == TRUE ) {
#else
        if( _access( szIniFileName, 0 ) != -1 ) {
#endif
            // printf( "\n %s file is exist !", szIniFileName );
            break;
        }
        else {
        }

    }

    enBoardId = ( ENUM_BoardID ) i;

#else
    enBoardId = enPRC1;

#endif

    return enBoardId;

}

/**
 * @brief     INI 파일 로딩하기
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-04 09:00:12
 * @warning
 */
void CSysConfig::LoadINI()
{
#ifndef _CGI_LIST_
    int i, iValue;
    unsigned int uiValue;

    float fValue;

    string strValue;

    float fValueArray[enMAXPRC - 1];

    // 보드 ID 얻기
#ifdef _MSC_VER
    SetBoardID( g_enBoardId );

#else
    SetBoardID( CheckBoardID() );

#endif

    // INI 파일 로딩하기
    strcpy( m_szIniFileName, INI_FOLDER );
    strcat( m_szIniFileName, "/" );
    strcat( m_szIniFileName, INI_FILENAME );

#if defined(_MSC_VER) && !defined(_MSC_BOOTSHELL_)
    char szBuffer[400], szDefault[400];

    ///////////////////////////////////////////////////////////////////////////////////
    // 네트워크 환경 설정
    GetPrivateProfileString( "NETWORK", "RECENT_SERVER", _DEFAULT_RECENT_SERVER, szBuffer, 100, m_szIniFileName );
    SetRecentConnectionOfNetwork( szBuffer );

    //GetPrivateProfileString( "NETWORK", "SECOND_SERVER", _DEFAULT_PRIME_SERVER, szBuffer, 100, m_szIniFileName );
    //SetSecondServerOfNetwork( szBuffer );

    GetPrivateProfileString( "NETWORK", "CCU_SERVER_IP_ADDRESS", _DEFAULT_CCU_SERVER_IP_ADDRESS, szBuffer, 100, m_szIniFileName );
    SetCCUServerOfNetwork( szBuffer );

    GetPrivateProfileString( "NETWORK", "DEBUG_SERVER_IP_ADDRESS", _DEFAULT_DEBUG_SERVER_IP_ADDRESS, szBuffer, 100, m_szIniFileName );
    SetDebugServerOfNetwork( szBuffer );

    iValue = (int) GetPrivateProfileInt( "NETWORK", "SBC_FROM_IP", _DEFAULT_SBC_FROM_IP, m_szIniFileName );
    SetSBCFromIP( iValue );

    iValue = (int) GetPrivateProfileInt( "NETWORK", "SBC_TO_IP", _DEFAULT_SBC_TO_IP, m_szIniFileName );
    SetSBCToIP( iValue );

    ///////////////////////////////////////////////////////////////////////////////
    // 부팅 옵션
    iValue = ( int ) GetPrivateProfileInt( "BOOT", "TFFS_BOOT", _DEFAULT_TFFS_BOOT, m_szIniFileName );
    SetTFFSBoot( iValue );

    ///////////////////////////////////////////////////////////////////////////////
    // 개발용
    iValue = ( int ) GetPrivateProfileInt( "BOOT", "DEVELOP", _DEFAULT_DEVELOP_BOOT, m_szIniFileName );
    SetDevelop( iValue );

    ///////////////////////////////////////////////////////////////////////////////
    // 최소 펄스 개수
    iValue = (int) GetPrivateProfileInt( "ANAL", "MIN_ANALPULSE", _DEFAULT_ANAL_MINPULSECOUNT_, m_szIniFileName );
    _spAnalMinPulseCount = ( unsigned int ) iValue;
    SetMinAnalPulse( _spAnalMinPulseCount );

    // 신호 삭제 시간
    iValue = (int) GetPrivateProfileInt( "ANAL", "DEFAULT_DELETE_TIMESEC", _DEFAULT_DELETETIME_, m_szIniFileName );
    SetEmmgEmitterDeleteTimeSec( iValue );

    // 탐지 분석에서 최대 LOB 개수 정의
    uiValue = GetPrivateProfileInt( "ANAL", "MAX_COUNT_OF_LOB", _DEFAULT_COUNT_OF_LOB_, m_szIniFileName );
    SetMaxCountOfLOB( uiValue );

    ///////////////////////////////////////////////////////////////////////////////////
    // 고정형 STABLE MARGIN, 주파수 범위값 정의
    i = 0;
    sprintf( szDefault, "%f", _DEFAULT_FREQ_MARGIN_ );
    GetPrivateProfileString( "MARGIN", "FIXED_FREQ_MARGIN", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i++] = ( float ) atof( szBuffer );
    sprintf( szDefault, "%f", _DEFAULT_STABLE_MARGIN_ );
    GetPrivateProfileString( "AOA", "STABLE_MARGIN", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i] = ( float ) atof( szBuffer );
    SetMargin( fValueArray );

    ///////////////////////////////////////////////////////////////////////////////////
    // 그룹화 정의
    uiValue = GetPrivateProfileInt( "GROUP", "AOA_GROUP_MARGIN", _DEFAULT_AOA_GROUP_MARGIN_, m_szIniFileName );
    SetAOAGroupMargin( uiValue );

    // 고정형 신호 최소 세기 정의
    iValue = (int) GetPrivateProfileInt( "SCAN", "STEADY_MIN_PA_DBM", _DEFAULT_STEADY_MIN_PA_DBM, m_szIniFileName );
    SetSteadyMinPA( iValue );

    // 원추형 주기 정의
    uiValue = GetPrivateProfileInt( "SCAN", "CONICAL_MIN_PERIOD_MS", _DEFAULT_CONICAL_MIN_PERIOD_MS, m_szIniFileName );
    SetConicalMinPeriod( uiValue );

    uiValue = GetPrivateProfileInt( "SCAN", "CONICAL_MAX_PERIOD_MS", _DEFAULT_CONICAL_MAX_PERIOD_MS, m_szIniFileName );
    SetConicalMaxPeriod( uiValue );


    ///////////////////////////////////////////////////////////////////////////////////
    // 필터 범위 정의
    sprintf( szDefault, "%f", _DEFAULT_WINDOWCELL_DOA_RANGE_ );
    GetPrivateProfileString( "WINDOWCELL", "DOA_RANGE", szDefault, szBuffer, 100, m_szIniFileName );
    fValue = ( float ) atof( szBuffer );
    SetWindowCellDOARange( fValue );

    sprintf( szDefault, "%f", _DEFAULT_WINDOWCELL_FRQ_RANGE_ );
    GetPrivateProfileString( "WINDOWCELL", "FRQ_RANGE", szDefault, szBuffer, 100, m_szIniFileName );
    fValue = ( float ) atof( szBuffer );
    SetWindowCellFRQRange( fValue );

    sprintf( szDefault, "%f", _DEFAULT_WINDOWCELL_FRQ_HOPPING_RATIO_ );
    GetPrivateProfileString( "WINDOWCELL", "FRQ_HOPPING_RATIO", szDefault, szBuffer, 100, m_szIniFileName );
    fValue = ( float ) atof( szBuffer );
    SetWindowCellFRQHoppingRatio( fValue );



    ///////////////////////////////////////////////////////////////////////////////
    // 수신기 Threshold 값 로딩
    i = 0;
	sprintf( szDefault, "%f" , _DEFAULT_RXTHRESHOLD_BAND1_ );
	GetPrivateProfileString( "RECEIVER_THREAHOLD", "PRC_1", szDefault, szBuffer, 100, m_szIniFileName );
	fValueArray[i++] = (float) atof( szBuffer );
	sprintf( szDefault, "%f" , _DEFAULT_RXTHRESHOLD_BAND2_ );
	GetPrivateProfileString( "RECEIVER_THREAHOLD", "PRC_2", szDefault, szBuffer, 100, m_szIniFileName );
	fValueArray[i++] = (float) atof( szBuffer );
	sprintf( szDefault, "%f" , _DEFAULT_RXTHRESHOLD_BAND3_ );
	GetPrivateProfileString( "RECEIVER_THREAHOLD", "PRC_3", szDefault, szBuffer, 100, m_szIniFileName );
	fValueArray[i++] = (float) atof( szBuffer );
	sprintf( szDefault, "%f" , _DEFAULT_RXTHRESHOLD_BAND4_ );
	GetPrivateProfileString( "RECEIVER_THREAHOLD", "PRC_4", szDefault, szBuffer, 100, m_szIniFileName );
	fValueArray[i++] = (float) atof( szBuffer );
	sprintf( szDefault, "%f" , _DEFAULT_RXTHRESHOLD_BAND5_ );
	GetPrivateProfileString( "RECEIVER_THREAHOLD", "PRC_5", szDefault, szBuffer, 100, m_szIniFileName );
	fValueArray[i] = (float) atof( szBuffer );
	SetRxThreshold( fValueArray );

    ///////////////////////////////////////////////////////////////////////////////////
    // 수신기 방위 오차 정의
    i = 0;
    sprintf( szDefault, "%f", _DEFAULT_RECEIVER_AOA_ERROR_ );
    GetPrivateProfileString( "RECEIVER_AOA_ERROR", "PRC_1", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i++] = ( float ) atof( szBuffer );
    GetPrivateProfileString( "RECEIVER_AOA_ERROR", "PRC_2", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i++] = ( float ) atof( szBuffer );
    GetPrivateProfileString( "RECEIVER_AOA_ERROR", "PRC_3", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i++] = ( float ) atof( szBuffer );
    GetPrivateProfileString( "RECEIVER_AOA_ERROR", "PRC_4", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i++] = ( float ) atof( szBuffer );
    GetPrivateProfileString( "RECEIVER_AOA_ERROR", "PRC_5", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i] = ( float ) atof( szBuffer );
    SetReceiverDOAError( fValueArray );

	///////////////////////////////////////////////////////////////////////////////////
    // 방위 그룹화시 피크에서 좌우 반경 범위로 설정 정의
    i = 0;
    sprintf(szDefault, "%f", _DEFAULT_AOA_GROUP_ );
    GetPrivateProfileString("AOA_GROUP", "PRC_1", szDefault, szBuffer, 100, m_szIniFileName);
    fValueArray[i++] = (float)atof(szBuffer);
    GetPrivateProfileString("AOA_GROUP", "PRC_2", szDefault, szBuffer, 100, m_szIniFileName);
    fValueArray[i++] = (float)atof(szBuffer);
    GetPrivateProfileString("AOA_GROUP", "PRC_3", szDefault, szBuffer, 100, m_szIniFileName);
    fValueArray[i++] = (float)atof(szBuffer);
    GetPrivateProfileString("AOA_GROUP", "PRC_4", szDefault, szBuffer, 100, m_szIniFileName);
    fValueArray[i++] = (float)atof(szBuffer);
    GetPrivateProfileString("AOA_GROUP", "PRC_5", szDefault, szBuffer, 100, m_szIniFileName);
    fValueArray[i] = (float)atof(szBuffer);
    SetAOAGroup(fValueArray);

    ///////////////////////////////////////////////////////////////////////////////////
    // 주파수 그룹화시 피크에서 좌우 반경 범위로 설정 정의
    i = 0;
    sprintf( szDefault, "%f", _DEFAULT_FRQ_GROUP_ );
    GetPrivateProfileString( "FRQ_GROUP", "PRC_1", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i++] = ( float ) atof( szBuffer );
    GetPrivateProfileString( "FRQ_GROUP", "PRC_2", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i++] = ( float ) atof( szBuffer );
    GetPrivateProfileString( "FRQ_GROUP", "PRC_3", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i++] = ( float ) atof( szBuffer );
    GetPrivateProfileString( "FRQ_GROUP", "PRC_4", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i++] = ( float ) atof( szBuffer );
    GetPrivateProfileString( "FRQ_GROUP", "PRC_5", szDefault, szBuffer, 100, m_szIniFileName );
    fValueArray[i] = ( float ) atof( szBuffer );
    SetFRQGroup( fValueArray );


    // 프로그램 버젼 정보
    SetProgramVersion( GEN_VER_VERSION_STRING );

    // 위협 라이브러리 버젼 정보
    sprintf( szDefault, "%d" , _DEFAULT_LIB_VERSION_ );
    GetPrivateProfileString( "IPL" , "VERSION" , szDefault, szBuffer, 100, m_szIniFileName );
    //iValue = atoi( szBuffer );
    // uiValue = (unsigned int) abs( iValue );
    // SetIPLVersion( uiValue );

    uiValue = GetPrivateProfileInt( "SBC_CPU_TEMP_WARNING", "CPU_TEMP", _DEFAULT_CPU_TEMP_WARNING_, m_szIniFileName );
    SetCPUTempWarning( uiValue );

#else
    m_theMinIni.setfilename( m_szIniFileName );

    ///////////////////////////////////////////////////////////////////////////////
    // 네트워크 환경 설정
    strValue = m_theMinIni.gets( "NETWORK", "RECENT_SERVER", _DEFAULT_RECENT_SERVER );
    SetRecentConnectionOfNetwork( strValue.c_str() );

    strValue = m_theMinIni.gets( "NETWORK", "CCU_SERVER_IP_ADDRESS", _DEFAULT_CCU_SERVER_IP_ADDRESS );
    SetCCUServerOfNetwork( strValue.c_str() );

    strValue = m_theMinIni.gets( "NETWORK", "DEBUG_SERVER_IP_ADDRESS", _DEFAULT_DEBUG_SERVER_IP_ADDRESS );
    SetDebugServerOfNetwork( strValue.c_str() );

    iValue = m_theMinIni.geti( "NETWORK", "SBC_FROM_IP", _DEFAULT_SBC_FROM_IP );
    SetSBCFromIP( iValue );

    iValue = m_theMinIni.geti( "NETWORK", "SBC_TO_IP", _DEFAULT_SBC_TO_IP );
    SetSBCToIP( iValue );

    ///////////////////////////////////////////////////////////////////////////////
    // 부팅 옵션
    iValue = m_theMinIni.geti( "BOOT", "TFFS_BOOT", _DEFAULT_TFFS_BOOT );
    SetTFFSBoot( iValue );

    ///////////////////////////////////////////////////////////////////////////////
    // 개발용
    iValue = m_theMinIni.geti( "BOOT", "DEVELOP", _DEFAULT_DEVELOP_BOOT );
    SetDevelop( iValue );

    ///////////////////////////////////////////////////////////////////////////////
    // 최소 펄스 개수
    _spAnalMinPulseCount = ( unsigned int ) m_theMinIni.geti( "ANAL", "MIN_ANALPULSE", _DEFAULT_ANAL_MINPULSECOUNT_ );
    SetMinAnalPulse( _spAnalMinPulseCount );

    // 신호 삭제 시간
    iValue = m_theMinIni.geti( "ANAL", "DEFAULT_DELETE_TIMESEC", _DEFAULT_DELETETIME_ );
    SetEmmgEmitterDeleteTimeSec( iValue );

    // 탐지 분석에서 최대 LOB 개수 정의
    uiValue = (unsigned int) m_theMinIni.geti( "ANAL", "MAX_COUNT_OF_LOB", _DEFAULT_COUNT_OF_LOB_ );
    SetMaxCountOfLOB( uiValue );

    ///////////////////////////////////////////////////////////////////////////////
    // 수신기 Threshold 값 로딩
    i = 0;
    fValueArray[i++] = m_theMinIni.getf( "RECEIVER_THREAHOLD" , "PRC_1" , _DEFAULT_RXTHRESHOLD_BAND1_ );
    fValueArray[i++] = m_theMinIni.getf( "RECEIVER_THREAHOLD" , "PRC_2" , _DEFAULT_RXTHRESHOLD_BAND2_ );
    fValueArray[i++] = m_theMinIni.getf( "RECEIVER_THREAHOLD" , "PRC_3" , _DEFAULT_RXTHRESHOLD_BAND3_ );
    fValueArray[i++] = m_theMinIni.getf( "RECEIVER_THREAHOLD" , "PRC_4" , _DEFAULT_RXTHRESHOLD_BAND4_ );
    fValueArray[i] = m_theMinIni.getf( "RECEIVER_THREAHOLD" , "PRC_5" , _DEFAULT_RXTHRESHOLD_BAND5_ );
    SetRxThreshold( fValueArray );

    ///////////////////////////////////////////////////////////////////////////////////
    // 수신기 방위 오차 정의
    i = 0;
    fValueArray[i++] = m_theMinIni.getf("RECEIVER_AOA_ERROR", "PRC_1", _DEFAULT_RECEIVER_AOA_ERROR_ );
    fValueArray[i++] = m_theMinIni.getf("RECEIVER_AOA_ERROR", "PRC_2", _DEFAULT_RECEIVER_AOA_ERROR_ );
    fValueArray[i++] = m_theMinIni.getf("RECEIVER_AOA_ERROR", "PRC_3", _DEFAULT_RECEIVER_AOA_ERROR_ );
    fValueArray[i++] = m_theMinIni.getf("RECEIVER_AOA_ERROR", "PRC_4", _DEFAULT_RECEIVER_AOA_ERROR_ );
    fValueArray[i] = m_theMinIni.getf("RECEIVER_AOA_ERROR", "PRC_5", _DEFAULT_RECEIVER_AOA_ERROR_ );
    SetReceiverDOAError(fValueArray);

    ///////////////////////////////////////////////////////////////////////////////////
    // 방위 그룹화시 피크에서 좌우 반경 범위로 설정 정의
    i = 0;
    fValueArray[i++] = m_theMinIni.getf("AOA_GROUP", "PRC_1", _DEFAULT_AOA_GROUP_);
    fValueArray[i++] = m_theMinIni.getf("AOA_GROUP", "PRC_2", _DEFAULT_AOA_GROUP_);
    fValueArray[i++] = m_theMinIni.getf("AOA_GROUP", "PRC_5", _DEFAULT_AOA_GROUP_);
    fValueArray[i++] = m_theMinIni.getf("AOA_GROUP", "PRC_4", _DEFAULT_AOA_GROUP_);
    fValueArray[i] = m_theMinIni.getf("AOA_GROUP", "PRC_5", _DEFAULT_AOA_GROUP_);
    SetAOAGroup(fValueArray);

    ///////////////////////////////////////////////////////////////////////////////////
    // 주파수 그룹화시 피크에서 좌우 반경 범위로 설정 정의
    i = 0;
    fValueArray[i++] = m_theMinIni.getf( "FRQ_GROUP", "PRC_1", _DEFAULT_AOA_GROUP_ );
    fValueArray[i++] = m_theMinIni.getf( "FRQ_GROUP", "PRC_2", _DEFAULT_AOA_GROUP_ );
    fValueArray[i++] = m_theMinIni.getf( "FRQ_GROUP", "PRC_5", _DEFAULT_AOA_GROUP_ );
    fValueArray[i++] = m_theMinIni.getf( "FRQ_GROUP", "PRC_4", _DEFAULT_AOA_GROUP_ );
    fValueArray[i] = m_theMinIni.getf( "FRQ_GROUP", "PRC_5", _DEFAULT_AOA_GROUP_ );
    SetFRQGroup( fValueArray );

    ///////////////////////////////////////////////////////////////////////////////////
    // 고정형 STABLE MARGIN, 주파수 범위값 정의
    i = 0;
    fValueArray[i++] = m_theMinIni.getf( "MARGIN", "FIXED_FREQ_MARGIN", _DEFAULT_FREQ_MARGIN_ );
    fValueArray[i] = m_theMinIni.getf( "MARGIN", "STABLE_MARGIN", _DEFAULT_STABLE_MARGIN_ );
    SetMargin( fValueArray );

    ///////////////////////////////////////////////////////////////////////////////////
    // 그룹화 정의
    uiValue = m_theMinIni.geti( "GROUP", "AOA_GROUP_MARGIN", _DEFAULT_AOA_GROUP_MARGIN_ );
    SetAOAGroupMargin( uiValue );

    // 고정형 신호 최소 세기 정의
    iValue = m_theMinIni.geti( "SCAN", "STEADY_MIN_PA_DBM", _DEFAULT_STEADY_MIN_PA_DBM );
    SetSteadyMinPA( iValue );

    // 스캔 정의
    uiValue = m_theMinIni.geti( "SCAN", "CONICAL_MIN_PERIOD_MS", _DEFAULT_CONICAL_MIN_PERIOD_MS );
    SetConicalMinPeriod( uiValue );
    uiValue = m_theMinIni.geti( "SCAN", "CONICAL_MAX_PERIOD_MS", _DEFAULT_CONICAL_MAX_PERIOD_MS );
    SetConicalMaxPeriod( uiValue );

    ///////////////////////////////////////////////////////////////////////////////////
    // 필터 범위 정의
    fValue = m_theMinIni.getf( "WINDOWCELL", "DOA_RANGE", _DEFAULT_WINDOWCELL_DOA_RANGE_ );
    SetWindowCellDOARange( fValue );
    //
    fValue = m_theMinIni.getf( "WINDOWCELL", "FRQ_RANGE", _DEFAULT_WINDOWCELL_FRQ_RANGE_ );
    SetWindowCellFRQRange( fValue );

    fValue = m_theMinIni.getf( "WINDOWCELL", "FRQ_HOPPING_RATIO", _DEFAULT_WINDOWCELL_FRQ_HOPPING_RATIO_ );
    SetWindowCellFRQHoppingRatio( fValue );


    ///////////////////////////////////////////////////////////////////////////////
    // 프로그램 버젼 정보
    SetProgramVersion( GEN_VER_VERSION_STRING );

    ///////////////////////////////////////////////////////////////////////////////
    // 위협 라이브러리 버젼 정보
    iValue = m_theMinIni.geti( "IPL" , "VERSION" , _DEFAULT_LIB_VERSION_ );
    SetIPLVersion( (unsigned int) _abs(iValue) );

    iValue = m_theMinIni.geti( "SBC_CPU_TEMP_WARNING", "CPU_TEMP", _DEFAULT_CPU_TEMP_WARNING_ );
    SetCPUTempWarning( iValue );

    // m_theMinIni.put( "NETWORK", "CCU_SERVER_IP_ADDRESS", "127.0.0.2" );

#endif

#endif

}

/**
 * @brief     InitVar
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-03 11:06:45
 * @warning
 */
void CSysConfig::InitVar()
{

    // 네트워크 얻기
    SetNetworkIP();

	// 초기화 순번
	m_uiOpInitID = 0;

    // 보드 세팅
    m_strConfig.enBoardID = enMaster;
    //m_strConfig.enMode = enREADY_MODE;

#if defined(_POCKETSONATA_) || defined(_712_)

    // 수집 채널 초기화
    memset( m_strConfig.strDetectWindowCell, 0, sizeof( STR_WINDOWCELL) * CO_DETECT_CHANNEL );
    memset( m_strConfig.strTrackWindowCell, 0, sizeof( STR_WINDOWCELL) * CO_TRACK_CHANNEL );
    memset( m_strConfig.strScanWindowCell, 0, sizeof( STR_WINDOWCELL) * CO_SCAN_CHANNEL );
    memset( m_strConfig.strUserWindowCell, 0, sizeof( STR_WINDOWCELL) * CO_USER_CHANNEL );

    // 수집 히스토그램 초기화
    memset( m_strConfig.ucColHisto, 0, sizeof(m_strConfig.ucColHisto) );


#elif defined(_ELINT_) || defined(_XBAND_)


#else


#endif

    m_szIniFileName[0] = (char) '\0';


}

/**
 * @brief     SetNetworkIP
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-24 13:29:25
 * @warning
 */
void CSysConfig::SetNetworkIP()
{
    int i=0;
    char szIPAddress[100];

    szIPAddress[0] = 0;
    while( g_szDeviceName[i][0] != 0 ) {
        GetIPAddress( szIPAddress, (char *) g_szDeviceName[i] );
        if( szIPAddress[0] != 0 ) {
            SetLocalIPAddress( szIPAddress );
            break;
        }
        ++ i;
    }

    if( szIPAddress[0] == 0 ) {
        SetLocalIPAddress( NETWORK_CLASSC );
        //int a_IP, b_IP, c_IP, d_IP;
        //sscanf( szIPAddress, "%d.%d.%d.%d" , & a_IP, & b_IP, & c_IP, & d_IP );
        //SetLocalIPAddress( szIPAddress );

    }

}

/**
 * @brief CSysConfig::GetIPAddress
 * @param pNetworkName
 */
bool CSysConfig::GetIPAddress( char *pIPAddress, char *pNetworkName )
{
    bool bRet=false;

#ifdef __linux__
    struct ifreq ifr;

    char szError[100];

    int s;

    bRet = true;

    s = socket( AF_INET, SOCK_DGRAM, 0 );
    strncpy( ifr.ifr_name, pNetworkName, IFNAMSIZ );
    if( ioctl(s, SIOCGIFADDR, &ifr ) < 0 ) {
        sprintf( szError, "네트워크[%s]" , pNetworkName );
        perror( szError );
        pIPAddress[0] = 0;
        bRet = false;
    }
    else {
        inet_ntop( AF_INET, ifr.ifr_addr.sa_data+2, pIPAddress, sizeof(struct sockaddr));

        sprintf( pIPAddress, "%u.%u.%u" , (unsigned char) ifr.ifr_addr.sa_data[2], (unsigned char) ifr.ifr_addr.sa_data[3], (unsigned char) ifr.ifr_addr.sa_data[4] );
        //sscanf( pIPAddress, "%d.%d.%d.%d" , & a_IP, & b_IP, & c_IP, & d_IP );
        //sprintf( pIPAddress, "%d.%d.%d.%d" , & a_IP, & b_IP, & c_IP, & d_IP );
        //printf("myOwn IP Address is %s\n", ipstr);
    }
#elif _MSC_VER
    WORD wVersionRequested;
    WSADATA wsaData;
    char name[255];
    PHOSTENT hostinfo;

    wVersionRequested = MAKEWORD(2, 0);

    if( WSAStartup(wVersionRequested, &wsaData) == 0) {
        if( gethostname(name, sizeof(name)) == 0 ) {
            hostinfo = gethostbyname(name);
            if( hostinfo != NULL ) {
                struct in_addr *pIpAddr;
                // strIpAddress = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
                pIpAddr = (struct in_addr *) (*hostinfo->h_addr_list);
                sprintf( pIPAddress, "%d.%d.%d.%d" , (unsigned char) pIpAddr->S_un.S_un_b.s_b1, (unsigned char) pIpAddr->S_un.S_un_b.s_b2, (unsigned char) pIpAddr->S_un.S_un_b.s_b3, (unsigned char) pIpAddr->S_un.S_un_b.s_b4 );
            }
        }
        WSACleanup();
    }

#endif

    return bRet;
}

/**
 * @brief CSysConfig::SetWindowCell
 * @param uiCh
 * @param pWindowCell
 */
void CSysConfig::SetWindowCell( unsigned int uiGlobalCh, STR_WINDOWCELL *pWindowCell )
{

    if( uiGlobalCh < CO_DETECT_CHANNEL ) {
        SetDetectWindowCell( uiGlobalCh, pWindowCell );
    }
#if CO_TRACK_CHANNEL > 0
    else if( uiGlobalCh < CO_DETECT_CHANNEL+CO_TRACK_CHANNEL ) {
        SetTrackWindowCell( uiGlobalCh -CO_DETECT_CHANNEL, pWindowCell );
    }
#endif

#if CO_SCAN_CHANNEL > 0
    else if( uiGlobalCh < CO_DETECT_CHANNEL+CO_TRACK_CHANNEL+CO_SCAN_CHANNEL ) {
        SetScanWindowCell( uiGlobalCh -CO_DETECT_CHANNEL-CO_TRACK_CHANNEL, pWindowCell );
    }
#endif
    else {
        SetUserWindowCell( uiGlobalCh -CO_DETECT_CHANNEL-CO_TRACK_CHANNEL-CO_SCAN_CHANNEL, pWindowCell );
    }

}

/**
 * @brief		DisplaySystemVar
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/03/23 15:11:11
 * @warning
 */
void CSysConfig::DisplaySystemVar()
{
    char szTFFSBoot[2][30] = { "StandAlone(ROM 부팅)", "디버깅(TFTP 부팅)" };
    char szDevelop[2][30] = { "체계 시험용", "개발용" };

    TRACE( "\n" );
    TRACE( "\n################################ 시스템 환경 설정 값 ################################" );

    TRACE( "\n\t.프로그램 버젼 (git 태그)                 : %s", m_strConfig.szProgramVersion );
    TRACE( "\n\t.보드 식별자 (EW신호처리판)               : %d" , m_strConfig.enBoardID );
    TRACE( "\n\t.최근 연동 컴퓨터 (SBC 간 연결 IP)        : %s" , GetRecentConnectionOfNetwork() );
    //TRACE( "\n\t.개발 컴퓨터 (개발 컴퓨터 IP)             : %s" , m_strConfig.szSecondServer );
    TRACE( "\n\t.운용 제어 콘솔 (운용 제어 콘솔)          : %s", GetCCUServerOfNetwork() );
    TRACE( "\n\t.디버그 컴퓨터 (위협 정보 디버깅 컴)      : %s", GetDebugServerOfNetwork() );
    TRACE( "\n\t.장치 내 내부 SBC IP 범위                 : %d/%d", m_strConfig.iSBCFromIP, m_strConfig.iSBCToIP );

    TRACE( "\n" );
    //Log( enNormal, "\t.장비 모드           : %d" , m_strConfig.enMode );
    TRACE( "\n\t.부팅 옵션                                : %s(%d)" , szTFFSBoot[m_strConfig.iTFFSBoot], m_strConfig.iTFFSBoot );
    TRACE( "\n\t.개발용                                   : %s(%d)" , szDevelop[m_strConfig.iDevelop], m_strConfig.iDevelop );
    TRACE( "\n\t.CPU 온도 경고 임계값(이상시 자동 부팅)   : %d [도]", m_strConfig.uiCPUTempWarning );

    TRACE( "\n" );
    TRACE( "\n\t.최소 펄스수 (LOB 생성 최소 펄스열 개수)  : %d [개]" , m_strConfig.uiMinAnalPulse );
    TRACE( "\n\t.기본 위협 삭제 시간 (미식별시 삭제 시간) : %d [초]" , m_strConfig.iEmitterDeleteTime );
    TRACE( "\n\t.고정 주파수 범위                         : %.1f [MHz]", m_strConfig.fMargin[0] );
    TRACE( "\n\t.규칙성 펄스열 추출 마진                  : %.1f [us]", m_strConfig.fMargin[1] );
    TRACE( "\n\t.대역별 방위 그룹화 마진                  : %.2f/%.2f/%.2f/%.2f/%.2f [도]", m_strConfig.fAOAGroup[0], m_strConfig.fAOAGroup[1], m_strConfig.fAOAGroup[2], m_strConfig.fAOAGroup[3], m_strConfig.fAOAGroup[4] );
    //TRACE( "\n\t.대역별 주파수 그룹화 마진  : %.2f/%.2f/%.2f/%.2f/%.2f [MHz]", m_strConfig.fFRQGroup[0], m_strConfig.fFRQGroup[1], m_strConfig.fFRQGroup[2], m_strConfig.fFRQGroup[3], m_strConfig.fFRQGroup[4] );

    TRACE( "\n" );
    TRACE( "\n\t.고정형 최소 신호 세기 (Steady 판단 세기) : %d [dBM]", m_strConfig.iMinSteadyPAAmplitude );
    TRACE( "\n\t.원추형 최소/최대 스캔 주기               : %d ~ %d [ms]", m_strConfig.uiMinConicalPeriod, m_strConfig.uiMaxConicalPeriod );

    TRACE( "\n" );
    TRACE( "\n\t.WC 방위 필터 마진 (위협 최대 이동 고려)  : %.2f [도]" , GetWindowCellDOARange() );
    TRACE( "\n\t.WC 주파수 필터 마진                      : %.2f [도]", GetWindowCellFRQRange() );
    TRACE( "\n\t.WC 주파수 호핑률 (미식별 호핑 주파수 율) : %.2f [도]", GetWindowCellFRQHoppingRatio() );

    TRACE( "\n" );
    TRACE( "\n\t.탐지/추적 신규 LOB 개수 (탐지/추적 LOB)  : %d [개]", m_strConfig.uiMaxCountOfLOB );

    TRACE( "\n" );
    TRACE( "\n\t.대역별 수신기 방위 오차                  : %.2f/%.2f/%.2f/%.2f/%.2f [도]", m_strConfig.fReceiverDOAError[0], m_strConfig.fReceiverDOAError[1], m_strConfig.fReceiverDOAError[2], m_strConfig.fReceiverDOAError[3], m_strConfig.fReceiverDOAError[4] );
    TRACE( "\n\t.대역별 기본 수신 임계값                  : %.2f/%.2f/%.2f/%.2f/%.2f [dBm]", m_strConfig.fRxThreshold[0], m_strConfig.fRxThreshold[1], m_strConfig.fRxThreshold[2], m_strConfig.fRxThreshold[3], m_strConfig.fRxThreshold[4] );
    TRACE( "\n" );

    TRACE( "\n####################################################################################" );

    TRACE( "\n\n" );

}

/**
 * @brief     WriteServerIPAddress
 * @param     char * pIPAddress
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-22 10:34:09
 * @warning
 */
void CSysConfig::WritePrimeServerIPAddress( char *pIPAddress )
{
#ifdef _MSC_VER
    WritePrivateProfileString( "NETWORK", "PRIME_SERVER", pIPAddress, m_szIniFileName );

#else
    m_theMinIni.put( "NETWORK", "PRIME_SERVER", pIPAddress );

#endif

}

/**
 * @brief     WritePresentTime
 * @param     char * pPresentTime
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-26 17:38:06
 * @warning
 */
void CSysConfig::WritePresentTime( char *pPresentTime )
{
#ifdef _MSC_VER
    WritePrivateProfileString( "NETWORK", "PRESENT_TIME", pPresentTime, m_szIniFileName );

#else
    m_theMinIni.put( "NETWORK", "PRESENT_TIME", pPresentTime );

#endif

    printf( "현재 시간[%s]을 기록합니다.\n", pPresentTime );

}

/**
 * @brief     GetPresentTime
 * @param     time_t * pTime
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-26 17:44:21
 * @warning
 */
void CSysConfig::GetPresentTime( struct timespec *pTime )
{
    struct tm stTM;

    memset( & stTM, 0, sizeof( tm ) );

#if defined(_MSC_VER) && !defined(_MSC_BOOTSHELL_)
    char szBuffer[100];

    GetPrivateProfileString( "NETWORK", "PRESENT_TIME", _DEFAULT_PRESENT_TIME, szBuffer, 100, m_szIniFileName );
    sscanf( szBuffer, "%d_%d_%d_%d_%d_%d", & stTM.tm_year, & stTM.tm_mon, & stTM.tm_mday, & stTM.tm_hour, & stTM.tm_min, & stTM.tm_sec );

#else
    string strBuffer;

    strBuffer = m_theMinIni.gets( "NETWORK", "PRESENT_TIME", _DEFAULT_PRESENT_TIME );

    printf( "\n기록된 시간을 불러 옵니다[%s]", strBuffer.c_str() );
    sscanf( strBuffer.c_str(), "%d_%d_%d_%d_%d_%d", & stTM.tm_year, & stTM.tm_mon, & stTM.tm_mday, & stTM.tm_hour, & stTM.tm_min, & stTM.tm_sec );

//     struct tm *timeinfo;
//     time_t rawtime;
//
//     time( & rawtime );
//     timeinfo = localtime( & rawtime );
//     printf( "\n %d-%d-%d_%d:%d:%d", timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec );

#endif

    stTM.tm_year -= 1900;
    stTM.tm_mon --;
    (*pTime).tv_sec = (long) mktime( & stTM );

#ifdef _MSC_VER
    ( *pTime ).tv_usec = 0;
#else
    (*pTime).tv_nsec = 0;
#endif

}
