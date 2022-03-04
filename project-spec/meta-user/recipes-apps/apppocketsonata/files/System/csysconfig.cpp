// CSysConfig.cpp: implementation of the CSysConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

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

CSharedMemroy* CSysConfig::m_pSharedMemory = NULL;

static char g_szDeviceName[5][10] = { "eth1", "wlo1", "enp0s8" } ;

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
//#ifndef _XBAND_
    m_pSharedMemory->close();
    delete m_pSharedMemory;
//#endif

}

/**
 * @brief CSysConfig::LoadINI
 */
void CSysConfig::LoadINI()
{
#ifndef _CGI_LIST_
    int i, iValue;
    float fValue;
    string strValue;
    char szHomeDirectory[100];

    float fRxThreshold[5];

    // INI 파일 로딩하기
    strcpy( szHomeDirectory, INI_FOLDER /* getenv("HOME") */ );
    strcat( szHomeDirectory, INI_FILENAME );

    m_theMinIni.setfilename( szHomeDirectory );

    ///////////////////////////////////////////////////////////////////////////////
    // RX Threshold 값 로딩
    i = 0;
    fValue = m_theMinIni.getf( "RXTHRESHOLD" , "Band1" , _RXTHRESHOLD_BAND1_ );
    fRxThreshold[i++] = fValue;
    fValue = m_theMinIni.getf( "RXTHRESHOLD" , "Band2" , _RXTHRESHOLD_BAND2_ );
    fRxThreshold[i++] = fValue;
    fValue = m_theMinIni.getf( "RXTHRESHOLD" , "Band3" , _RXTHRESHOLD_BAND3_ );
    fRxThreshold[i++] = fValue;
    fValue = m_theMinIni.getf( "RXTHRESHOLD" , "Band4" , _RXTHRESHOLD_BAND4_ );
    fRxThreshold[i++] = fValue;
    fValue = m_theMinIni.getf( "RXTHRESHOLD" , "Band5" , _RXTHRESHOLD_BAND5_ );
    fRxThreshold[i++] = fValue;

    SetRxThreshold( fRxThreshold );

    // 네크워크 환경 설정
    strValue = m_theMinIni.gets( "NETWORK" , "PRIME_SERVER" , "192.168.1.12" );
    SetPrimeServerOfNetwork( strValue.c_str() );

    ///////////////////////////////////////////////////////////////////////////////
    // 최소 펄스 개수
    _spAnalMinPulseCount = (unsigned int) m_theMinIni.geti( "ANAL" , "MIN_ANALPULSE" , _ANAL_MIN_PULSECOUNT_ );
    SetMinAnalPulse( _spAnalMinPulseCount );

    // 신호 삭제 시간
    iValue = m_theMinIni.geti( "ANAL" , "DEFAULT_DELETE_TIMESEC" , _DEFAULT_DELETETIME_ );
    SetEmmgEmitterDeleteTimeSec( iValue );

    // 프로그램 버젼 정보
    SetProgramVersion( _GetProgramVersion() );

    // 위협 라이브러리 버젼 정보
    iValue = m_theMinIni.geti( "IPL" , "VERSION" , _DEFAULT_LIB_VERSION_ );
    SetIPLVersion( _abs(iValue) );


#endif

}

/**
 * @brief CSysConfig::InitVar
 */
void CSysConfig::InitVar()
{

    // 네트워크 얻기
    SetNetworkIP();

#ifdef _POCKETSONATA_
    // 보드 세팅
    m_strConfig.enBoardID = enMaster;
    m_strConfig.enMode = enREADY_MODE;


    // 수집 채널 초기화
    memset( m_strConfig.strDetectWindowCell, 0, sizeof(STR_WINDOWCELL) * DETECT_CHANNEL );
    memset( m_strConfig.strTrackWindowCell, 0, sizeof(STR_WINDOWCELL) * TRACK_CHANNEL );
    memset( m_strConfig.strScanWindowCell, 0, sizeof(STR_WINDOWCELL) * SCAN_CHANNEL );
    memset( m_strConfig.strUserWindowCell, 0, sizeof(STR_WINDOWCELL) * USER_CHANNEL );

    // 수집 히스토그램 초기화
    memset( m_strConfig.ucColHisto, 0, sizeof(m_strConfig.ucColHisto) );

//     _spOneSec = 20000000.;
//     _spOneMilli = FDIV( _spOneSec, 1000. );
//     _spOneMicrosec = FDIV( _spOneMilli, 1000. );
//     _spOneNanosec = FDIV( _spOneMicrosec, 1000. );
// 
//     _spAOAres = (float) ( 0.351562 );
//     _spAMPres = (float) (0.351562);
//     _spPWres = _spOneMicrosec;

#elif defined(_ELINT_) || defined(_XBAND_)
//     _spOneSec = FDIV( 1000000000, _toaRes[0] );
//     _spOneMilli = FDIV( 1000000, _toaRes[0] );
//     _spOneMicrosec = FDIV( 1000, _toaRes[0] );
//     _spOneNanosec = FDIV( 1, _toaRes[0] );
// 
//     _spAOAres = (float) 0.01;
//     _spAMPres = (float) (0.25);
//     _spPWres = _spOneMicrosec;

#else


#endif

    _spAnalMinPulseCount = 6;


}

/**
 * @brief CSysConfig::SetNetworkIP
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
void CSysConfig::SetWindowCell( unsigned int uiCh, STR_WINDOWCELL *pWindowCell )
{

    if( uiCh < DETECT_CHANNEL ) {
        SetDetectWindowCell( uiCh, pWindowCell );
    }
    else if( uiCh < DETECT_CHANNEL+TRACK_CHANNEL ) {
        SetTrackWindowCell( uiCh-DETECT_CHANNEL, pWindowCell );
    }
    else if( uiCh < DETECT_CHANNEL+TRACK_CHANNEL+SCAN_CHANNEL ) {
        SetScanWindowCell( uiCh-DETECT_CHANNEL-TRACK_CHANNEL, pWindowCell );
    }
    else {
        SetUserWindowCell( uiCh-DETECT_CHANNEL-TRACK_CHANNEL-SCAN_CHANNEL, pWindowCell );
    }

}
