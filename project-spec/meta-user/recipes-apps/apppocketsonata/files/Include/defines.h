/*
 * 본 문서는 시스템의 정의문을 정의합니다.
 * */


#ifndef _DEFINES_H
#define _DEFINES_H

////////////////////////////////////////////////////////////////////////////////
// 아래는 문자열에 관련된 정의를 나열합니다.
#define PROGRAM_NAME        "PocketSonata"
#define PROGRAM_VERSION     "0.1a"




// 변수 타입을 정의합니다.
typedef unsigned int UINT;
typedef unsigned char UCHAR;

#ifndef _TOA_
typedef unsigned long long int _TOA;
#endif


#ifdef _MSC_VER

#else
// MFC에서 정의된 define 문을 아래에 정의한다.
#define MAX_PATH        (1024)

#endif


// 포토 를 정의합니다.
#define MAX_CLIENTS     (30)
#define PORT            (8888)

#define NETWORK_CLASSC  (const char *) ( "192.168.0" )


#ifdef _SIM_SERVER_
#define HOST_SERVER     (const char *) ( "127.0.0.1" )
#define DEV_SERVER      (const char *) ( "127.0.0.1" )
#define DEV2_SERVER     (const char *) ( "127.0.0.1" )

#else

#define HOST_SERVER     (const char *) ( "192.168.10.245" )
#define DEV_SERVER      (const char *) ( "192.168.10.11" )
#define DEV2_SERVER     (const char *) ( "192.168.10.12" )

#endif



// 제어조종장치 서버
#ifdef __linux__
//#define CCU_SERVER      (char *) ( "127.0.0.1" )
#else
//#define CCU_SERVER      (char *) ( "192.168.1.245" )
#endif

#ifdef __ZYNQ_BOARD__
#define CCU_PORT        (13030)
#else
#define CCU_PORT        (13030)
#endif

// 재밍신호관리장치 서버
#define PMC_SERVER      (char *) ( "192.168.1.245" )
#define PMC_PORT        (13040)


#define TEST_PORT       (13090)

/////////////////////////////////////////////////////////////////////////////////

#define DETECT_CHANNEL  (1)
#define TRACK_CHANNEL   (256)
#define SCAN_CHANNEL    (256)
#define USER_CHANNEL    (16)
#define TOTAL_CHANNELS  (DETECT_CHANNEL+TRACK_CHANNEL+SCAN_CHANNEL+USER_CHANNEL)


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

#define bool            bool

#endif



#endif // _DEFINES_H
