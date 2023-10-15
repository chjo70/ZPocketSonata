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

#include "pch.h"

#include <time.h>
#include <stdio.h>

#include "../Include/system.h"

#include "../System/csysconfig.h"

#include "clog.h"

#include "../Include/globals.h"

#include "ccommonutils.h"

#include "../gen-versioninfo.h"


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

//void _ShowProgramTitle( void );
//const char *_GetProgramVersion();

#ifdef __cplusplus
}
#endif

static std::string g_strVersion;


/**
 * @brief     _ShowProgramTitle
 * @param     void
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-04 10:37:55
 * @warning
 */
void _ShowProgramTitle( void )
{
    char szDate[100], szHeader[200]={0};
    CCommonUtils::getStringPresentTime( szDate, sizeof( szDate ) );

    CCommonUtils::WallMakePrint( szHeader, '~' );
    Log( enNormal, "%s", szHeader);
    Log( enNormal, "[%s] 프로그램 시작 시간 [%s] 버젼 (%s)...", PROGRAM_NAME, szDate, GEN_VER_VERSION_STRING );

#ifdef _POCKETSONATA_
    Log( enNormal, "%s", szHeader );
    Log( enNormal, " ZZZZZZZZ    PPPPPPPP   OOOOO    CCCCCC  KK    KK  EEEEEE  TTTTTTTTT" );
    Log( enNormal, "      ZZ     PP    PP  OO   OO  CC       KK  KK    EE         TT" );
    Log( enNormal, "    ZZ       PPPPPPPP  OO   OO  CC       KKKK      EEEEEE     TT" );
    Log( enNormal, "  ZZ         PP        OO   OO  CC       KK  KK    EE         TT" );
    Log( enNormal, " ZZZZZZZZ    PP         OOOOO    CCCCCC  KK    KK  EEEEEE     TT" );
    Log( enNormal, "%s", szHeader );

#elif defined(_712_)
    Log( enNormal, "%s", szHeader );
    Log( enNormal, " 77777777    11      22222           EEEEEE  LL      II  N      N TTTTTT  " );
    Log( enNormal, "      77     111         22          EE      LL      II  N NN   N   TT   " );
    Log( enNormal, "    77       11       22      ====   EEEEEE  LL      II  N  NN  N   TT   " );
    Log( enNormal, "  77         11     22               EE      LL      II  N   NN N   TT   " );
    Log( enNormal, " 77          11     2222222          EEEEEE  LLLLLL  II  N    NNN   TT   " );
    Log( enNormal, "%s", szHeader );

#elif defined(_ELINT_)
    Log( enNormal, "%s", szHeader );

    Log( enNormal, "%s", szHeader );


#elif defined(_XBAND_)
    Log( enNormal, "%s", szHeader );
    Log( enNormal, " XXXXXXXX    BBBBBBB      AA    NN   NN  DDDDDDD   " );
    Log( enNormal, " XX   XX     BB    BB    A  A   NNN  NN  DD    DD  " );
    Log( enNormal, "   XXX       BBBBBBB    AAAAAA  NN N NN  DD    DD  " );
    Log( enNormal, "  XX  XX     BB    BB   A    A  NN  NNN  DD    DD  " );
    Log( enNormal, " XXXXXXXX    BBBBBBB    A    A  NN   NN  DDDDDDD   " );
    Log( enNormal, "%s", szHeader );

#else
    _MSG( "장비 헤더 메시지를 생성해야 합니다." );

#endif


}

/**
 * @brief GetProgramVersion
 * @param pszVersion
 */
const char *_GetProgramVersion()
{

    //memset( g_szVersion, 0, sizeof(g_szVersion) );
    g_strVersion = GEN_VER_VERSION_STRING;

    //sscanf( __DATE__, "%s %d %d" , szMon, & iDate, & iYear );
    //strcat( g_szVersion, __DATE__ );

    return g_strVersion.c_str();
}
