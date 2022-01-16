#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport)

#else
#define MATHFUNCSDLL_API __declspec(dllimport)
#endif


#define WM_USER_LOGMSG				(7011)

#include "RadarDirAlgorithm.h"

//
// RADARDIR 프로젝트 내에서 최소 내용만 구조체 정의를 복사한 것임.


#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
	en5MHZ_BW=0,
	en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif

#ifndef _STR_LOBHEADER
#define _STR_LOBHEADER
typedef struct 
{
	int iNumOfLOB;

} SRxLOBHeader;
#endif

#define MAX_LOB_DATA			(100)

#ifndef _STR_LOBDATA
#define _STR_LOBDATA
typedef struct {
	SRxLOBHeader stLOBHeader;

	SRxLOBData stLOBData[MAX_LOB_DATA];

} STR_LOBDATA ;
#endif

#ifndef _STR_ABTHEADER
#define _STR_ABTHEADER
struct SRxABTHeader
{
	int iNumOfABT;

};
#endif


#define _MAX_RADARMODENAME_STRING_SIZE_								(30+_NULL_CHAR_)

#define _MAX_STATUS_STRING_SIZE_									(20+_NULL_CHAR_)

#define _MAX_BE_NUMBER_STRING_SIZE_									(12+_NULL_CHAR_)
#define _MAX_USER_COUNTRY_STRING_SIZE_								(4+_NULL_CHAR_)
#define _MAX_PRIMARY_FUNCTION_STRING_SIZE_                          (4+_NULL_CHAR_)
#define _MAX_FRIEND_OR_FOE_STRING_SIZE_								(12+_NULL_CHAR_)
#define _MAX_ADA_STRING_SIZE_										(8+_NULL_CHAR_)
#define _MAX_DATETIME_STRING_SIZE_									(40+_NULL_CHAR_)
#define _MAX_DISTINCTION_STRING_SIZE_								(12+_NULL_CHAR_)
#define _MAX_SYMBOLCODE_STRING_SIZE_								(20+_NULL_CHAR_)
#define _MAX_LATITUDE_STRING_SIZE_									(15+_NULL_CHAR_)
#define _MAX_LONGITUDE_STRING_SIZE_									(15+_NULL_CHAR_)

#define _MAX_WEAPON_STRING_SIZE_									(40+_NULL_CHAR_)
#define _MAX_PLATFORM_STRING_SIZE_									(40+_NULL_CHAR_)

#define _MAX_SIZE_OF_THREATNAME_									(70+_NULL_CHAR_)
#define _MAX_SIZE_OF_KOREASITENAME_									(70+_NULL_CHAR_)
#define _MAX_SIZE_OF_FACILITYNAME_									(72+_NULL_CHAR_)

//#define _MAX_SIZE_OF_MODECODE                                       (4)
#define _MAX_PLATFORM_NAME_SIZE                                     (10)

#ifndef _STR_ABTDATA_STRUCT
#define _STR_ABTDATA_STRUCT
struct SRxABTData {
    unsigned int uiABTID;
    unsigned int uiAETID;

    int iSignalType;

    unsigned int uiCoLOB;

    time_t /* __time32_t */ tiFirstSeenTime;				// 32비트 time_t 로 선언해야 함.
    time_t /* __time32_t */ tiLastSeenTime;

    char szPrimaryELNOT[_MAX_ELNOT_STRING_SIZE_];
    char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1번째 ELNOT

    char szModulationCode[_MAX_MODECODE_STRING_SIZE_];
    char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];
    char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
    char szPlatform[_MAX_PLATFORM_NAME_SIZE];
    char szNickName[_MAX_NICKNAME_STRING_SIZE_];
    char szPlaceNameKor[_MAX_SIZE_OF_KOREASITENAME_];

    int iRadarModePriority;
    int iRadarPriority;

    int iPolarization;

#if defined(_POCKETSONATA_) || defined(_ELINT_)
    float fDOAMean;                                 // [0.1도]
    float fDOAMax;
    float fDOAMin;
    float fDOADeviation;				// [0.1도]
#endif

    int iFreqType;
    int iFreqPatternType;
    float fFreqPatternPeriodMean;	  // [us]
    float fFreqPatternPeriodMin;	  // [us]
    float fFreqPatternPeriodMax;	  // [us]
    float fFreqMean;										// [10KHz]
    float fFreqMax;
    float fFreqMin;
    float fFreqDeviation;
    int iFreqPositionCount;
    int iFreqElementCount;
    float fFreqSeq[MAX_FREQ_PRI_STEP];	// 주파수 단값

    int iPRIType;
    int iPRIPatternType;
    float fPRIPatternPeriodMean;							// [us]
    float fPRIPatternPeriodMin;							// [us]
    float fPRIPatternPeriodMax;							// [us]
    float fPRIMean;											// [1ns]
    float fPRIMax;
    float fPRIMin;
    float fPRIDeviation;			// [1ns]
    float fPRIJitterRatio;							// [%]
    int iPRIPositionCount;
    int iPRIElementCount;
    float fPRISeq[MAX_FREQ_PRI_STEP];

    float fPWMean;											// 1ns
    float fPWMax;
    float fPWMin;
    float fPWDeviation;

    float fPAMean;											// 기존대로
    float fPAMax;
    float fPAMin;
    float fPADeviation;

    int iScanType;
    float fMeanScanPeriod;			// [usec]
    float fMaxScanPeriod;			// [usec]
    float fMinScanPeriod;			// [usec]

    int iHasIntraMod;
    float fMaxIntraMod;
    float fMinIntraMod;

    int iPEValid;
    float fLatitude;							// [deg]
    float fLongitude;							// [deg]
    float fHeight;
    float fCEP;										// [m]
    float fMajorAxis;							// [m]
    float fMinorAxis;							// [m]
    float fTheta;									// [0.1도]
    float fDistanceErrorOfThreat;	// [m]

    int iValidity;

    unsigned int uiTotalOfPDW;

    int iRadarModeIndex;
    int iThreatIndex;

    int iIsManualInput;

    __time32_t tiFinalAlarmTime;

    int iStat;

    char aucRadarName[_MAX_RADARNAME_SIZE];

}  ;
#endif

#define MAX_ABT_DATA			(100)

#ifndef _STR_ABTDATA
#define _STR_ABTDATA
typedef struct {
	SRxABTHeader stABTHeader;

	SRxABTData stABTData[MAX_ABT_DATA];

} STR_ABTDATA ;
#endif


//////////////////////////////////////////////////////////////////////////
// 컴파일 방법

/* 이 헤더파일을 프로젝트 폴더에 복사하고 아래 함수를 호출하려고 하는 소스에 아래와 같이 include 한다.

#include "RadarAnlAlgorithm.h"

:
:

RadarAnlAlgotirhm::RadarAnlAlgotirhm::Init();

:
:

RadarAnlAlgotirhm::RadarAnlAlgotirhm::Close();

*/

//////////////////////////////////////////////////////////////////////////
// 실행 방법

/* 1. 시작시 한번만 호출하면 됩니다.
	 응용 프로그램에서 초기화시에 아래 루틴을 한번 호출하면 됩니다.
   RadarAnlAlgotirhm::RadarAnlAlgotirhm::Init();

	 2. 프로그램 종료시 한번만 호출하면 됩니다.
	 RadarAnlAlgotirhm::RadarAnlAlgotirhm::Close();

	 3. 위협 관리 호출시 STR_LOBDATA 구조에 아래와 같이 데이터가 있어야 합니다.

STR_LOBDATA stLOBData;

typedef struct 
{
	int iNumOfLOB;													<---- LOB 개수, 최대 100개 까지이다.
} SRxLOBHeader;

typedef struct {
	SRxLOBHeader stLOBHeader;								<---- LOB 헤더 구조체
	SRxLOBData stLOBData[100];							<---- LOB 데이터

} STR_LOBDATA ;

RadarAnlAlgotirhm::RadarAnlAlgotirhm::Start( & stLOBData );

		4. 분석 결과는 아래 함수를 호출하여 LOB 개수와 데이터를 얻는다.
		
		STR_LOBDATA stResLOBData;
		STR_ABTDATA stResABTData;

		RadarAnlAlgotirhm::RadarAnlAlgotirhm::GetLOBData( & stResLOBData );			<---- LOB 결과
		RadarAnlAlgotirhm::RadarAnlAlgotirhm::GetABTData( & stResABTData );			<---- ABT 결과

		stResLOBData 구조체와 stResABTData 구조체를 보고 이용하면 됩니다.

		*주의 사항 : 위협 관리 호출시 LOB 개수가 100 개 초과이면 위협 관리를 중단한다. 과제 정보가 없는 ...
								 현재 입력 LOB 결과가 10개 이면 LOB 개수 결과는 10개 이어야 하고 ABT 결과는 10 개 미만이어야 함.
								 추후, LOB 클러스터링을 추가하게 되면 LOB 개수 결과와 빔 결과 개수는 10개 이상/최대 10개 미만 일 수 있습니다.

		5. CED 및 EOB 라이브러리가 변경됐을때 위협 관리시 CED/EOB를 로딩해야 한다는 플레그를 세팅해주는 함수이다.
		   CED 및 EOB 라이브러리가 변경된 경우 운용 소프트웨어는 레이더 분석에게 알려주고 레이더 분석에서는 이 함수를 호출해야 합니다.

		RadarAnlAlgotirhm::RadarAnlAlgotirhm::UpdateCEDEOBLibrary();						<---- CED/EOB 업데이트를 알려준다.


		6. 운용 초기화 운용 초기화시에 방사체 및 빔/LOB 번호를 1번 부터 재시작하며 위협 관리 테이블도 초기화하여 처음부터 분석을 시작한다.
		RadarAnlAlgotirhm::RadarAnlAlgotirhm::SWInit();													<---- 운용 초기화를 수행한다.

*/

namespace RadarAnlAlgotirhm
{
	// This class is exported from the MathFuncsDll.dll
	class RadarAnlAlgotirhm
	{
	public: 
		static MATHFUNCSDLL_API void Init( HWND hWnd=0, bool bDBThread=true, bool bLocal=false );
		static MATHFUNCSDLL_API void Close();

		static MATHFUNCSDLL_API void Start( STR_LOBDATA *pLOBData );
		static MATHFUNCSDLL_API void SWInit();
		static MATHFUNCSDLL_API void UpdateCEDEOBLibrary();

		static MATHFUNCSDLL_API bool GetLOBData( STR_LOBDATA *pLOBData );
		static MATHFUNCSDLL_API bool GetABTData( STR_ABTDATA *pABTData );

#pragma data_seg( ".ioshare" )
        // static CLog *g_pTheLog;
#pragma data_seg()

	};
}



