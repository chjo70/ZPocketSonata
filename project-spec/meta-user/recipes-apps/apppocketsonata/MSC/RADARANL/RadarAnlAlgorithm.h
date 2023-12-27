

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


#pragma pack( push, 1 )


#ifndef _SRxLOBHeader
#define _SRxLOBHeader
typedef struct
{
	int iNumOfLOB;

#if defined(_POCKETSONATA_) || defined(_712_)
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

#ifndef _SRxAETHeader
#define _SRxAETHeader
struct SRxAETHeader {
    int iNumOfAET;

};
#endif


// CED 레이더모드의 문자열 길이 정의 호출
// 아래 파일은 ../../files/Anal/SigAnal/_CED_Define.h 에 있는 파일을 복사해야 합니다.


#ifdef _USRDLL
#include "../../files/Anal/SigAnal/_CED_Define.h"

#else
#include "./_CED_Define.h"

#endif



// 빔 데이터 구조체 입니다.
#ifndef _SRxABTData
#define _SRxABTData
struct SRxABTData {
    unsigned int uiABTID;
    unsigned int uiAETID;

#if defined(_POCKETSONATA_) || defined(_712_)
    unsigned char vSignalType;
#else
    unsigned int vSignalType;
#endif

    unsigned int uiCoLOB;

    unsigned int tiFirstSeenTime;				// 64비트 time_t 로 선언해야 함.
    unsigned int tiLastSeenTime;

    unsigned int uiRadarModePriority;
    unsigned int uiRadarPriority;

#if defined(_ELINT_)
    int iPolarization;

#endif

    float fDOAMean;                                 // [0.1도]
    float fDOAMax;
    float fDOAMin;
    float fDOADeviation;				// [0.1도]

#if defined(_POCKETSONATA_) || defined(_712_)
    ENUM_AET_FRQ_TYPE vFreqType;
    ENUM_AET_FREQ_PRI_PATTERN_TYPE vFreqPatternType;
#else
    int vFreqType;
    int vFreqPatternType;
#endif

    float fFreqPatternPeriodMean;	  // [us]
    float fFreqPatternPeriodMin;	  // [us]
    float fFreqPatternPeriodMax;	  // [us]
    float fFreqMean;										// [10KHz]
    float fFreqMax;
    float fFreqMin;
    float fFreqDeviation;

#if defined(_POCKETSONATA_) || defined(_712_)
    unsigned char vFreqPositionCount;
    unsigned char vFreqElementCount;
#else
    int vFreqPositionCount;
    int vFreqElementCount;
#endif

    float fFreqSeq[MAX_FREQ_PRI_STEP];	// 주파수 단값

#if defined(_POCKETSONATA_) || defined(_712_)
    ENUM_AET_PRI_TYPE vPRIType;
    ENUM_AET_FREQ_PRI_PATTERN_TYPE vPRIPatternType;
#else
    int vPRIType;
    int vPRIPatternType;
#endif

    float fPRIPatternPeriodMean;							// [us]
    float fPRIPatternPeriodMin;							// [us]
    float fPRIPatternPeriodMax;							// [us]
    float fPRIMean;											// [1ns]
    float fPRIMax;
    float fPRIMin;
    float fPRIDeviation;			// [1ns]
    float fPRIJitterRatio;							// [%]

#if defined(_POCKETSONATA_) || defined(_712_)
    unsigned char vPRIPositionCount;
    unsigned char vPRIElementCount;
#else
    int vPRIPositionCount;
    int vPRIElementCount;
#endif

    float fPRISeq[MAX_FREQ_PRI_STEP];

    float fPWMean;
    float fPWMax;
    float fPWMin;
    float fPWDeviation;

    float fPAMean;
    float fPAMax;
    float fPAMin;
    float fPADeviation;

#if defined(_POCKETSONATA_) || defined(_ELINT_) || defined(_701_) || defined(_SONATA_) || defined(_712_)

#if defined(_POCKETSONATA_) || defined(_712_)
    ENUM_AET_SCAN_TYPE vScanType;
#else
    int vScanType;
#endif

    float fMeanScanPeriod;
    float fMaxScanPeriod;               // [ms]
    float fMinScanPeriod;

#if defined(_POCKETSONATA_) || defined(_712_)
    ENUM_AET_SCAN_STAT vScanStat;
#endif

#if defined(_POCKETSONATA_) || defined(_712_)
    bool ucMOPType;
#else
    bool iHasIntraMod;
#endif

    float fMaxIntraMod;
    float fMinIntraMod;
#endif

#if defined(_POCKETSONATA_) || defined(_712_)
    unsigned char ucPEValid;
#else
    int iPEValid;
#endif

    float fLatitude;							// [deg]
    float fLongitude;							// [deg]
    float fAltitude;
    float fCEP;										// [m]
    float fMajorAxis;							// [m]
    float fMinorAxis;							// [m]
    float fTheta;									// [0.1도]
    float fDistanceErrorOfThreat;	// [m]

#if defined(_POCKETSONATA_) || defined(_712_)
    bool bValidity;
#else
    int bValidity;
#endif

    unsigned int uiTotaOfPDW;

    unsigned int uiRadarIndex;                  // 레이더 인덱스 : ELNOT

    unsigned int uiRadarModeIndex;              // 레이더모드 인덱스
    unsigned int uiThreatIndex;                 // 위협 인덱스

#if defined(_ELINT_)
    int iIsManualInput;

    unsigned int tiFinalAlarmTime;
#endif

#if defined(_POCKETSONATA_) || defined(_712_)
#else
    int iStat;
#endif

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

};
#endif


// 방사체 구조체 입니다.
#ifndef _STR_AETDATA_STRUCT
#define _STR_AETDATA_STRUCT
struct SRxAETData {
    unsigned int uiAETID;

    unsigned int uiCoABT;
    unsigned int uiCoLOB;

    char szPrimaryELNOT[_MAX_ELNOT_STRING_SIZE_];
    char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1번째 ELNOT

    char szModulationCode[_MAX_MODECODE_STRING_SIZE_];
    char szRadarName[_MAX_RADARNAME_SIZE];

#if defined(_XBAND_) || defined(_ELINT_)
    char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
#endif

    char szNickName[_MAX_NICKNAME_STRING_SIZE_];
    char szPlaceNameKor[_MAX_SIZE_OF_KOREASITENAME_];

#if defined(_POCKETSONATA_) || defined(_712_)
    unsigned char vCategory;
#else
    int vCategory;
#endif

    unsigned int uiPinNum;

#if defined(_XBAND_) || defined(_ELINT_)
    char szThreatFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
#endif

    unsigned int uiRadarModePriority;
    unsigned int uiRadarPriority;
    unsigned int uiThreatPriority;

    unsigned int tiFirstSeenTime;				// 64비트 time_t 로 선언해야 함.
    unsigned int tiLastSeenTime;

#if defined(_POCKETSONATA_) || defined(_712_)
    unsigned char ucValidity;
#else
    int ucValidity;
#endif

#if defined(_POCKETSONATA_) || defined(_ELINT_) || defined(_XBAND_) || defined(_SONATA_) || defined(_712_)
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

    unsigned int uiRadarIndex;
    unsigned int uiRadarModeIndex;
    unsigned int uiThreatIndex;

#if defined(_POCKETSONATA_) || defined(_712_)
    unsigned char ucPEValid;
#else
    int ucPEValid;
#endif

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
    unsigned int tiFinalAlarmTime;

#endif

#if defined(_POCKETSONATA_) || defined(_712_)
#else
    int iStat;
#endif

};
#endif

#define MAX_ABT_DATA			(100)

#ifndef _STR_ABTDATA
#define _STR_ABTDATA
typedef struct {
    SRxABTHeader stABTHeader;

    SRxABTData stABTData[MAX_ABT_DATA];

} STR_ABTDATA;
#endif

#define MAX_AET_DATA			(MAX_ABT_DATA)


#ifndef _SRxAETHeader
#define _SRxAETHeader
struct SRxAETHeader {
    int iNumOfAET;

};
#endif

#ifndef _STR_AETDATA
#define _STR_AETDATA
typedef struct {
    SRxAETHeader stAETHeader;

    SRxAETData stAETData[MAX_AET_DATA];

} STR_AETDATA;
#endif


#pragma pack( pop )

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


#if defined(_POCKETSONATA_) || defined(_712_)
        // 운용 소프트웨어에서 입력한 LOB 데이터에 대한 결과 정보를 얻는다.
        static MATHFUNCSDLL_API bool GetResult( std::vector<SRxLOBData> *pVecLOBData, std::vector<SRxABTData> *pVecABTData, std::vector<SRxAETData> *pVecAETData );

		static MATHFUNCSDLL_API bool GetLOBData( STR_LOBDATA *pLOBData );
		static MATHFUNCSDLL_API bool GetABTData( STR_ABTDATA *pABTData );
        static MATHFUNCSDLL_API bool GetAETData( STR_AETDATA *pAETData );

        static MATHFUNCSDLL_API unsigned int GetOpInitID();

        static MATHFUNCSDLL_API std::vector<SRxLOBData> *GetLOBData();
        static MATHFUNCSDLL_API std::vector<SRxABTData> *GetABTData();
        static MATHFUNCSDLL_API std::vector<SRxAETData> *GetAETData();
#else
		static MATHFUNCSDLL_API bool GetLOBData( STR_LOBDATA *pLOBData );
		static MATHFUNCSDLL_API bool GetABTData( STR_ABTDATA *pABTData );
        static MATHFUNCSDLL_API bool GetAETData( STR_AETDATA *pAETData );

        static MATHFUNCSDLL_API unsigned int GetOpInitID();

#endif

        static MATHFUNCSDLL_API const char *GetThreadName() { return NULL; }

#pragma data_seg( ".ioshare" )
        // static CLog *g_pTheLog;
#pragma data_seg()

	};
}



