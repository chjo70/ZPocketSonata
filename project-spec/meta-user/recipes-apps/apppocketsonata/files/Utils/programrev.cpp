/****************************************************************************************
 파 일 명 : programrev.c
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : RSA 분석 표시용 컴파일 일자 등록 프로그램
 가    정 :
 저 자 명 : 조철희
 변 경 자 : 
 변경내용 : (목적)
 변경일시 : 
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#include "stdafx.h"

#include <time.h>
#include <stdio.h>

#include "../Include/system.h"

#include "../System/csysconfig.h"

#include "clog.h"

#include "../Include/globals.h"

//#include "../INC/_common.h"
//#include "../BSP/sbc_str.h"

// 업데이트 버젼
// Ver 1.05 : 2005-12-19 4:20오후
//					  .스캔필터판의 필터판 채널 값을 확인해서 잘못된 채널값일 때 처리를 안하게 한다.
//						.SBIT 요청시에 SP에서 수신기 응답 메시지를 수신한 1.5초 후에 SBIT를 실시한다.
//						.Fixed일 때 추적윈도우 셀 설정시 마진 값 범위를 4*시그마 에서 2*시그마로 수정했음.
// Ver 1.04 : 2005-07-27 10:14오전
//						.오디오 방위 영역이 0 - 360 도이면 방위 전체 범위 값으로 한다.
// Ver 1.03 : 2005-07-21 8:20오전
//						.IPL을 측정하여 잘못된 정보는 없앤다.
//						.VME SBC 통신시에 통신시 세마포아를 체크해서 이상시 메시지를 송신하지 
//						 않은 것을 강제 송신하도록 설정.
//						.Hopping/Dwell 업데이트 변경시에 주파수, PRI 최소,최대값이 각 단의 레벨 
//					  .범위 안에 포함되도록 함.
//						
// Ver 1.02 : .매 방위 측정된 방위값들에 대한 평균값을 측정해서 제어저종으로 전송한다.
// Ver 1.01 : .방위 계산안을 방안3으로 적용함.
// Ver 1.0  : .05년 05월 버젼을 1.0으로 한다.
// Ver 1.1  : .스캔필터판의 Phase 에러일 때 PDW 정보 프린트
//						.스캔필터판에서 잘못된 Pseudo 채널 응답시 채널 값 확인해서 수집 종료 처리
//
// Ver 1.2  : .함정용에서 주파수 Agile 식별시에 식별 정보를 근거하여 윈도우 셀을 설정한다.
//						.기지용에서 JitJit 식별을 10을 기준으로 마진 값을 변경하게 헸다.
//						.로브 판단에서 index 를 잘못하여 로브 판단이 잘못됨.
// Ver 1.3  : 2006-05-08 3:02오후
//						.제어조종컴퓨터에 의한 에미터 삭제시 이중 삭제가 될수 있음. 이를 위해서 에미터 변수
//						 번호 등록시에 삭제되 에미토  


#ifdef __cplusplus
extern "C"
{
#endif

void _ShowProgramTitle( void );
char *_GetProgramVersion();

#ifdef __cplusplus
}
#endif

static char g_szVersion[100];
 

/**
 * @brief ShowProgramTitle
 */
void _ShowProgramTitle( void )
{
    time_t timer;
    struct tm* t;
    //struct timeval tv;

    char szDate[LOG_DIR_SIZE];

    memset( g_szVersion, 0, sizeof(g_szVersion) );

#ifdef _POCKETSONATA_
    LOGMSG( enNormal, "--------------------------------------------------------------------------" );
    LOGMSG( enNormal, " ZZZZZZZZ    PPPPPPPP   OOOOO    CCCCCC  KK    KK  EEEEEE  TTTTTTTTT" );
    LOGMSG( enNormal, "      ZZ     PP    PP  OO   OO  CC       KK  KK    EE         TT" );
    LOGMSG( enNormal, "    ZZ       PPPPPPPP  OO   OO  CC       KKKK      EEEEEE     TT" );
    LOGMSG( enNormal, "  ZZ         PP        OO   OO  CC       KK  KK    EE         TT" );
    LOGMSG1( enNormal, " ZZZZZZZZ    PP         OOOOO    CCCCCC  KK    KK  EEEEEE     TT  Ver %s" , PROGRAM_VERSION );
    LOGMSG( enNormal, "---------------------------------------------------------------------------" );

#elif defined(_ELINT_)

#elif defined(_XBAND_)
	LOGMSG( enNormal, "--------------------------------------------------------------------------" );
	LOGMSG( enNormal, " XXXXXXXX    BBBBBBB    OOOOO   NN   NN  DDDDDDD   " );
	LOGMSG( enNormal, " XX   XX     BB    BB  OO   OO  NNN  NN  DD    DD  " );
	LOGMSG( enNormal, "   XXX       BBBBBBB   OO   OO  NN N NN  DD    DD  " );
	LOGMSG( enNormal, "  XX  XX     BB    BB  OO   OO  NN  NNN  DD    DD  " );
	LOGMSG1( enNormal, " XXXXXXXX    BBBBBBB    OOOOO   NN   NN  DDDDDDD   Ver %s" , PROGRAM_VERSION );
	LOGMSG( enNormal, "---------------------------------------------------------------------------" );

#else

#endif

    timer = time( NULL );
    t = localtime(&timer);

    if( t != NULL ) {
        sprintf( szDate, "%d/%0d/%0d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
    }
    else {
        strcpy( szDate, "2022/04/01 12:34:56" );
    }

    LOGMSG3( enNormal, "Starting the [%s:%s] Program on the (%s)...", PROGRAM_NAME, PROGRAM_VERSION, szDate );
//     }
//     else {
//         LOGMSG3( enNormal, "Starting the [%s:%s] Program on the (%s)...", PROGRAM_NAME, PROGRAM_VERSION, "INVALID_DATE" );
//     }

#ifdef _SQLITE_
    LOGMSG2( enNormal, "The CED/EOB Database is positioned at [%s] and the file name is [%s].", CEDEOB_SQLITE_FOLDER, CEDEOB_SQLITE_FILENAME );
    LOGMSG2( enNormal, "The Emitter Database is positioned at [%s] and the file name is [%s].", EMITTER_SQLITE_FOLDER, EMITTER_SQLITE_FILENAME );
#endif

    LOGMSG2( enNormal, "The INI is positioned at [%s], and the file name is [%s].", INI_FOLDER, INI_FILENAME );
    LOGMSG1( enNormal, "The MIDAS folder is at [%s].", SHARED_DATA_DIRECTORY );

    //LOG_LINEFEED;

#ifdef _POCKETSONATA_
#elif defined(_ELINT_) || defined(_XBAND_)
#else
	if( gnoPrc == prc_CIP ) {
#ifndef _TESTBIT_
        int i;
		for( i=prc_CIP ; i <= _spCoSbc ; ++i ) {
			pDebug = (STR_DEBUG *) ( ahwVME_CMS + aDebug );
			pDebug = pDebug + i;
			memcpy( str1, pDebug->_date, sizeof( __DATE__ ) );
			memcpy( str2, pDebug->_time, sizeof( __TIME__ ) );
#ifndef __VXWORKS__
			printf( "\n  Prc[%d] Compile Date[%s" , i, str1 );
			printf( ", %s]" , str2 );
#endif
		}
    }
#endif
#endif

}

/**
 * @brief GetProgramVersion
 * @param pszVersion
 */
char *_GetProgramVersion()
{

    //memset( g_szVersion, 0, sizeof(g_szVersion) );
    strcat( g_szVersion, PROGRAM_VERSION );

    //sscanf( __DATE__, "%s %d %d" , szMon, & iDate, & iYear );
    //strcat( g_szVersion, __DATE__ );

    return g_szVersion;
}
