#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport)

#else
#define MATHFUNCSDLL_API __declspec(dllimport)
#endif

using namespace std;

#include <vector>


#define WM_USER_LOGMSG				(7011)

#include "RadarDirAlgorithm.h"




//
// RADARDIR 프로젝트 내에서 최소 내용만 구조체 정의를 복사한 것임.


namespace ELINT {
#ifndef _ELINT_ENUM_BANDWIDTH_
#define _ELINT_ENUM_BANDWIDTH_
    typedef enum {
        en5MHZ_BW = 0,
        en50MHZ_BW,

        enUnknown_BW = 2,

    } ENUM_BANDWIDTH;
#endif
}

namespace XBAND {
#ifndef _XBAND_ENUM_BANDWIDTH_
#define _XBAND_ENUM_BANDWIDTH_
    typedef enum {
        en5MHZ_BW = 0,
        en120MHZ_BW,

        enUnknown_BW = 2,

    } ENUM_BANDWIDTH;
#endif
}

#ifndef _SRxLOBHeader
#define _SRxLOBHeader
typedef struct 
{
	int iNumOfLOB;

#ifdef _POCKETSONATA_
    unsigned int uiEWRecProc;   // EW수신처리판 번호
#endif

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

#ifndef _SRxABTHeader
#define _SRxABTHeader
struct SRxABTHeader
{
	int iNumOfABT;

};
#endif


// CED 레이더모드의 문자열 길이 정의 호출
// 아래 파일은 ../../files/Anal/SigAnal/_CED_Define.h 에 있는 파일을 복사해야 합니다.

#include "_CED_Define.h"






#ifndef _SRxABTData
#define _SRxABTData
struct SRxABTData { // 레이더 분석
	unsigned int uiABTID;
	unsigned int uiAETID;

	int iSignalType;

	unsigned int uiCoLOB;

	time_t tiFirstSeenTime;				// 64비트 time_t 로 선언해야 함.
	time_t tiLastSeenTime;

	int iRadarModePriority;
	int iRadarPriority;

#if defined(_ELINT_)
	int iPolarization;

#endif

	float fDOAMean;                                 // [0.1도]
	float fDOAMax;
	float fDOAMin;
	float fDOADeviation;				// [0.1도]

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

#if defined(_POCKETSONATA_) || defined(_ELINT_)
	int iScanType;
	float fMeanScanPeriod;			// [usec]
	float fMaxScanPeriod;			// [usec]
	float fMinScanPeriod;			// [usec]

	int iHasIntraMod;
	float fMaxIntraMod;
	float fMinIntraMod;
#endif

	int iPEValid;
	float fLatitude;							// [deg]
	float fLongitude;							// [deg]
	float fAltitude;
	float fCEP;										// [m]
	float fMajorAxis;							// [m]
	float fMinorAxis;							// [m]
	float fTheta;									// [0.1도]
	float fDistanceErrorOfThreat;	// [m]

	int iValidity;

	unsigned int uiTotalOfPDW;

	int iRadarModeIndex;
	int iThreatIndex;

#if defined(_ELINT_)
	int iIsManualInput;

	time_t tiFinalAlarmTime;
#endif

	int iStat;

#if defined(_XBAND_) || defined(_ELINT_)
	char szRadarName[_MAX_RADARNAME_SIZE];
#endif

	char szPrimaryELNOT[_MAX_ELNOT_STRING_SIZE_];
	char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1번째 ELNOT

	char szModulationCode[_MAX_MODECODE_STRING_SIZE_];
	char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];

#if defined(_XBAND_) || defined(_ELINT_)
	char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
	char szPlatform[_MAX_PLATFORM_NAME_SIZE];
#endif


	char szNickName[_MAX_NICKNAME_STRING_SIZE_];
	char szPlaceNameKor[_MAX_SIZE_OF_KOREASITENAME_];
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



#ifndef _STR_AETDATA_STRUCT
#define _STR_AETDATA_STRUCT
struct SRxAETData {
	unsigned int uiAETID;

	unsigned int uiCoABT;
	unsigned int uiCoLOB;

	char szPrimaryELNOT[_MAX_ELNOT_STRING_SIZE_];
	char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1번째 ELNOT

	char szModulationCode[_MAX_MODECODE_STRING_SIZE_];
	char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];

#if defined(_XBAND_) || defined(_ELINT_)
	char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
#endif

	char szNickName[_MAX_NICKNAME_STRING_SIZE_];
	char szPlaceNameKor[_MAX_SIZE_OF_KOREASITENAME_];

	int iPlatformType;
	int iPinNum;

#if defined(_XBAND_) || defined(_ELINT_)
	char szThreatFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
#endif

	int iRadarModePriority;
	int iRadarPriority;
	int iThreatPriority;

	time_t tiFirstSeenTime;				// 64비트 time_t 로 선언해야 함.
	time_t tiLastSeenTime;

	int iValidity;

#if defined(_POCKETSONATA_) || defined(_ELINT_) || defined(_XBAND_)
	float fDOAMean;                                 // [0.1도]
	float fDOAMax;
	float fDOAMin;
	float fDOADeviation;				// [0.1도]
#endif

	float fFreqMean;
	float fFreqMax;
	float fFreqMin;
	float fFreqDeviation;

	float fPRIMean;											// [1ns]
	float fPRIMax;
	float fPRIMin;
	float fPRIDeviation;// [%]

	float fPWMean;											// 1ns
	float fPWMax;
	float fPWMin;
	float fPWDeviation;

	float fPAMean;											// 기존대로
	float fPAMax;
	float fPAMin;
	float fPADeviation;

	int iRadarIndex;

	int iRadarModeIndex;
	int iThreatIndex;

	int iPEValid;
	float fLatitude;							// [deg]
	float fLongitude;							// [deg]
	float fAltidude;							// [deg]
	float fCEP;										// [m]
	float fMajorAxis;							// [m]
	float fMinorAxis;							// [m]
	float fTheta;									// [0.1도]
	float fDistanceErrorOfThreat;	// [m]

	char szIDInfo[_MAX_SIZE_OF_IDINFO];

#if defined(_XBAND_) || defined(_ELINT_)
	__time32_t tiFinalAlarmTime;

#endif

	int iStat;
    

};
#endif




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

	5. CED 및 EOB 라이브러리가 변경됐을때 이를 위협 관리.식별 모듈에 알려주기 위함이다.

		RadarAnlAlgotirhm::RadarAnlAlgotirhm::UpdateCEDEOBLibrary();						<---- CED/EOB 업데이트를 알려준다.


		6. 운용 초기화 운용 초기화시에 방사체 및 빔/LOB 번호를 1번 부터 재시작하며 위협 관리 테이블도 초기화하여 처음부터 분석을 시작한다.

		RadarAnlAlgotirhm::RadarAnlAlgotirhm::SWInit();													<---- 운용 초기화를 수행한다.

*/

namespace RadarAnlAlgotirhm
{
	
	class RadarAnlAlgotirhm
	{
	public: 
        // 운용 소프트웨어 실행시 위협 병합 및 식별 라이브러리를 초기화하기 위해서 아래 함수를 호출해야 합니다.
		static MATHFUNCSDLL_API void Init( HWND hWnd=0, bool bDBThread=false, bool bLocal=false );

        // 운용 소프트웨어 닫을시 아래 함수를 호출해서 위협 관리 /식별 모듈을 닫는다.
		static MATHFUNCSDLL_API void Close();

        // 운용 소프트웨어 에서 위협 병합 및 식별 을 하기 위해서 아래 함수를 호출합니다.
		static MATHFUNCSDLL_API bool Start( STR_LOBDATA *pLOBData );

        // 운용 소프트웨어 에서 위협 병합 및 식별 라이브러리를 초기화하혀고 할 때 아래 함수를 호출한다.
		static MATHFUNCSDLL_API void SWInit();

        // 운용 소프트웨어 에서 CED/EOB 변경시 아래 함수를 호출해서 CED/EOB 로딩하도록 한다.
		static MATHFUNCSDLL_API void UpdateCEDEOBLibrary();


#ifdef _POCKETSONATA_
        // 운용 소프트웨어에서 입력한 LOB 데이터에 대한 결과 정보를 얻는다.
        static MATHFUNCSDLL_API bool GetResult( std::vector<SRxLOBData> *pVecLOBData, std::vector<SRxABTData> *pVecABTData, std::vector<SRxAETData> *pVecAETData );

		static MATHFUNCSDLL_API bool GetLOBData( STR_LOBDATA *pLOBData );
		static MATHFUNCSDLL_API bool GetABTData( STR_ABTDATA *pABTData );

        static MATHFUNCSDLL_API unsigned int GetOpInitID();
#else
		static MATHFUNCSDLL_API bool GetLOBData( STR_LOBDATA *pLOBData );
		static MATHFUNCSDLL_API bool GetABTData( STR_ABTDATA *pABTData );

        static MATHFUNCSDLL_API unsigned int GetOpInitID();

#endif        

#pragma data_seg( ".ioshare" )
        // static CLog *g_pTheLog;
#pragma data_seg()

	};
}



