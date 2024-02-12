/*
 * 본 문서는 시스템의 정의문을 정의합니다.
 * */


#ifndef _DEFINES_H
#define _DEFINES_H

////////////////////////////////////////////////////////////////////////////////
// 아래는 문자열에 관련된 정의를 나열합니다.

#define PROGRAM_NAME        "PocketSonata"
//#define PROGRAM_VERSION     "0.9a"


#define _spPass     (0)
#define _spFail     (1)


// 변수 타입을 정의합니다.
typedef unsigned int UINT;
typedef unsigned char UCHAR;

#ifndef _TOA_
//typedef unsigned long long int _TOA;
#endif


#ifdef _MSC_VER

#else
// MFC에서 정의된 define 문을 아래에 정의한다.
#define MAX_PATH        (1024)

#endif


// 포토 를 정의합니다.
#define MAX_CLIENTS     (5)
#define PORT            (8888)

#define NETWORK_CLASSC  (const char *) ( "192.168.0" )



#define _DEFAULT_BOARDID                    6


#ifdef _SIM_SERVER_
#define _DEFAULT_RECENT_SERVER              (const char *) ( "127.0.0.1" )
#define _DEFAULT_CCU_SERVER_IP_ADDRESS      (const char *) ( "127.0.0.1" )
#define _DEFAULT_DEBUG_SERVER_IP_ADDRESS    (const char *) ( "127.0.0.1" )
#define DEV_SERVER                          (const char *) ( "127.0.0.1" )
#define DEV2_SERVER                         (const char *) ( "127.0.0.1" )

#else

#define _DEFAULT_RECENT_SERVER              (const char *) ( "192.168.0.200" )
#define _DEFAULT_CCU_SERVER_IP_ADDRESS      (const char *) ( "127.0.0.1" )
#define _DEFAULT_DEBUG_SERVER_IP_ADDRESS    (const char *) ( "192.168.0.200" )
#define DEV_SERVER                          (const char *) ( "192.168.0.11" )
#define DEV2_SERVER                         (const char *) ( "192.168.0.12" )

#endif

#define _DEFAULT_SBC_FROM_IP                (110)
#define _DEFAULT_SBC_TO_IP                  (114)

#define _DEFAULT_TFFS_BOOT                  (0)
#define _DEFAULT_DEVELOP_BOOT               (1)

#define _DEFAULT_PRESENT_TIME               (const char *) ( "2023_1_1_0_0_0" )


// 제어조종장치 서버
#ifdef __linux__
//#define CCU_SERVER      (char *) ( "127.0.0.1" )
#else
//#define CCU_SERVER      (char *) ( "192.168.1.245" )
#endif

#ifdef __ZYNQ_BOARD__
#define CCU_PORT                    (6600)
#define CCU_DEBUG_PORT              (6700)     // 13030
#else
#define CCU_PORT                    (6600)     // 13030
#define CCU_DEBUG_PORT              (6700)     // 13030
#endif

// 재밍신호관리장치 서버
//#define PMC_SERVER                  (char *) ( "192.168.1.245" )
//#define PMC_PORT                    (13040)


#define TEST_PORT                   (13090)

/////////////////////////////////////////////////////////////////////////////////

#define CO_DEFAULT_DETECT_CHANNEL	(1)                         // 탐지용 채널은 1개로 설정함. 현재 PL 전처리필터의 채널이 1개임.
#define CO_DEFAULT_TRACK_CHANNEL	(256)
#define CO_DEFAULT_SCAN_CHANNEL		(256)
#define CO_DEFAULT_USER_CHANNEL		(16)
#define TOTAL_DEFAULT_CHANNELS		(CO_DEFAULT_DETECT_CHANNEL+CO_DEFAULT_TRACK_CHANNEL+CO_DEFAULT_SCAN_CHANNEL+CO_DEFAULT_USER_CHANNEL)


/////////////////////////////////////////////////////////////////////////////////
#ifdef __linux__
//#define CString QString

#elif _MSC_VER

#else
//#define CString QString
#define _MBCS
#define _T(A)           (A)

#if	!defined(TRUE) || (TRUE!=(1))
#define TRUE            (true)
#endif

#if	!defined(FALSE) || (FALSE!=(0))
#define FALSE           (false)
#endif

//#define bool            bool

#endif



#endif // _DEFINES_H
