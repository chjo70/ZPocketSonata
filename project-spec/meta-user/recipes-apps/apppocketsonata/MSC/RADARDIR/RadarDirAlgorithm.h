#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport)

#else
#define MATHFUNCSDLL_API __declspec(dllimport)
#endif


#define WM_USER_LOGMSG				(7011)



//
// RADARDIR 프로젝트 내에서 최소 내용만 구조체 정의를 복사한 것임.


#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)

#ifndef MAX_PDW
#define MAX_PDW							(4096)
#endif

#ifndef _PDW_STRUCT
#define _PDW_STRUCT
typedef struct {
    unsigned long long int ullTOA;

    int iFreq;
    int iPulseType;
    int iPA;
    int iPW;
    int iPFTag;
    int iAOA;

#if defined(_ELINT_) || defined(_XBAND_)
    float fPh1;
    float fPh2;
    float fPh3;
    float fPh4;

#elif _POCKETSONATA_
    int iPMOP;
    int iFMOP;

    int iChannel;
#endif

} _PDW;
#endif

#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
	en5MHZ_BW=0,
	en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif


#ifndef _STR_ELINT_HEADER_
#define _STR_ELINT_HEADER_
typedef struct {
    unsigned char aucTaskID[LENGTH_OF_TASK_ID];
    unsigned int iIsStorePDW;
    int iCollectorID;
    ENUM_BANDWIDTH enBandWidth;

    unsigned int uiCount;

    int dummy;

} STR_ELINT_HEADER ;
#endif

#ifndef _POCKETSONATA_HEADER_
#define _POCKETSONATA_HEADER_
typedef struct {
    unsigned int iBoardID;
    unsigned int iBank;
    unsigned int iIsStorePDW;

} POCKETSONATA_HEADER ;
#endif

#ifndef _SONATA_HEADER_
#define _SONATA_HEADER_
typedef struct {
    unsigned int uiBand;
    unsigned int iIsStorePDW;

} SONATA_HEADER ;
#endif

#ifndef _STR_PDWDATA
#define _STR_PDWDATA
struct STR_PDWDATA {
    union UNION_HEADER {
        STR_ELINT_HEADER el;

        POCKETSONATA_HEADER ps;

        SONATA_HEADER so;
    } x;

    UINT uiTotalPDW;
    int _dummy;

    _PDW stPDW[MAX_PDW];

}  ;
#endif

#define MAX_RADARNAME					(8)

#ifndef MAX_FREQ_PRI_STEP
#define MAX_FREQ_PRI_STEP				(32)
#endif

#ifndef _NULL_CHAR_
#define _NULL_CHAR_						(1)
#endif

#ifndef _MAX_ELNOT_STRING_SIZE_
#define _MAX_ELNOT_STRING_SIZE_			(7+_NULL_CHAR_)
#endif

#ifndef _MAX_SIZE_OF_MODECODE
#define _MAX_SIZE_OF_MODECODE           (4)
#endif

#ifndef _MAX_MODECODE_STRING_SIZE_
#define _MAX_MODECODE_STRING_SIZE_		(3+_NULL_CHAR_)
#endif

#ifndef _MAX_RADARMODE_NAME_SIZE
#define _MAX_RADARMODE_NAME_SIZE		(12)
#endif

#ifndef _MAX_FUNCTIONCODE_STRING_SIZE_
#define _MAX_FUNCTIONCODE_STRING_SIZE_	(3+_NULL_CHAR_)
#endif

#ifndef _MAX_NICKNAME_STRING_SIZE_
#define _MAX_NICKNAME_STRING_SIZE_		(27+_NULL_CHAR_)
#endif

#ifndef _MAX_RADARNAME_SIZE
#define _MAX_RADARNAME_SIZE											(8)
#endif


#ifndef SRxLOBData_STRUCT
#define SRxLOBData_STRUCT
struct SRxLOBData {
    unsigned int uiLOBID;
    unsigned int uiABTID;
    unsigned int uiAETID;

    __time32_t tiContactTime;			// 32비트 time_t 로 선언해야 함.
    unsigned int tiContactTimems;

    char szPrimaryELNOT[_MAX_ELNOT_STRING_SIZE_];
    char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1번째 ELNOT

    char szSecondaryELNOT[_MAX_ELNOT_STRING_SIZE_];
    char szSecondaryModeCode[_MAX_SIZE_OF_MODECODE];							// 2번째 ELNOT

    char szTertiaryELNOT[_MAX_ELNOT_STRING_SIZE_];												// 3번째 ELNOT
    char szTertiaryModeCode[_MAX_SIZE_OF_MODECODE];

    char szModulationCode[_MAX_MODECODE_STRING_SIZE_];
    char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];
    char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
    char szNickName[_MAX_NICKNAME_STRING_SIZE_];

#ifndef _XBAND_
    int iPolarization;                              // 극성
    int iRatioOfPOL;                                // 극성 신뢰도

#endif

    int iSignalType;

    float fDOAMean;                                 // [0.1도]
    float fDOAMax;
    float fDOAMin;
    float fDOADeviation;							// [0.1도]
    float fDOASDeviation;

    int iDIRatio;					// [1 %]

    int iFreqType;
    int iFreqPatternType;
    float fFreqPatternPeriod;                       // [us]
    float fFreqMean;				// [10KHz]
    float fFreqMax;
    float fFreqMin;
    float fFreqDeviation;                           //
    int iFreqPositionCount;
    int iFreqElementCount;
    float fFreqSeq[MAX_FREQ_PRI_STEP];	// 주파수 단값

    int iPRIType;
    int iPRIPatternType;
    float fPRIPatternPeriod;		// [us]
    float fPRIMean;				// [1ns]
    float fPRIMax;
    float fPRIMin;
    float fPRIDeviation;			// [1ns]
    float fPRIJitterRatio;			// [%]
    int iPRIPositionCount;
    int iPRIElementCount;
    float fPRISeq[MAX_FREQ_PRI_STEP];

    float fPWMean;				// 1ns
    float fPWMax;
    float fPWMin;
    float fPWDeviation;

    float fPAMean;				// 기존대로
    float fPAMax;
    float fPAMin;
    float fPADeviation;			// 기존대로

#ifndef _XBAND_
    int iScanType;
    //int iDetailScanType;
    float fScanPeriod;			// [msec]

    int iMOPType;				// 인트라 타입
    int iDetailMOPType;			// 인트라 세부 타입. 항공에서 줄 수 있는것인지(?)
    float fMOPMaxFreq;			// ??
    float fMOPMinFreq;
    float fMOPMeanFreq;
    float fMOPFreqDeviation;


    float fShipLatitude;
    float fShipLongitude;
    float fPitchAngle;
    float fRollAngle;
    float fHeadingAngle;
    float fAltitude;
    int iValidity;
#endif

    int iIsStoreData;
    int iNumOfPDW;
    int iNumOfIQ;

    char aucRadarName[_MAX_RADARNAME_SIZE];
    int iRadarModeIndex;
    //int iThreatIndex;


#ifdef _POCKETSONATA_
	float fRadarLatitude;
	float fRadarLongitude;		

#elif defined(_ELINT_) || defined(_XBAND_)
	float fRadarLatitude;
	float fRadarLongitude;		

    int	iCollectorID;

    unsigned int uiSeqNum;
    char aucTaskID[LENGTH_OF_TASK_ID];

#else

#endif

}  ;
#endif



//////////////////////////////////////////////////////////////////////////
// 컴파일 방법

/* 이 헤더파일을 프로젝트 폴더에 복사하고 아래 함수를 호출하려고 하는 소스에 아래와 같이 include 한다.

#include "RadarDirAlgorithm.h"

:
:

RadarDirAlgotirhm::RadarDirAlgotirhm::Init();

:
:

RadarDirAlgotirhm::RadarDirAlgotirhm::Close();

*/

//////////////////////////////////////////////////////////////////////////
// 실행 방법

/* 1. 시작시 한번만 호출하면 됩니다.
	 응용 프로그램에서 초기화시에 아래 루틴을 한번 호출하면 됩니다.
   RadarDirAlgotirhm::RadarDirAlgotirhm::Init();

	 2. 프로그램 종료시 한번만 호출하면 됩니다.
	 RadarDirAlgotirhm::RadarDirAlgotirhm::Close();


	 3. 신호 분석시 PDWDATA 구조에 아래와 같이 데이터가 있어야 합니다.

typedef struct {
	char aucTaskID[LENGTH_OF_TASK_ID];			<---- 과제 정보
	unsigned int iIsStorePDW;								<---- 저장 여부. 일단 항상 1로 함.
	int iCollectorID;												<---- 수집소 위치. 소방대 분소는 1, 관제 수신소는 2, 신불 레이더#1/신불 레이더#2 은 3/4 로 할당
	ENUM_BANDWIDTH enBandWidth;							<---- 수집한 PDW의 수집과제 에서 대역폭을 저장

	UINT count;															<---- PDW 수집 개수
	_PDW stPDW[_MAX_PDW];										<---- PDW 데이터

} STR_PDWDATA ;

RadarDirAlgotirhm::RadarDirAlgotirhm::Start( & stPDWData );

		4. 분석 결과는 아래 함수를 호출하여 LOB 개수와 데이터를 얻는다.
		
		int nCoLOB=RadarDirAlgotirhm::RadarDirAlgotirhm::GetCoLOB();							<-- LOB 개수
		SRxLOBData *pLOBData=RadarDirAlgotirhm::RadarDirAlgotirhm::GetLOBData();	<--- LOB 데이터

		pLOBData[0] 로 첫번째 LOB 데이터, pLOBData[1] 로 두번째 LOB 데이터 등으로 사용하면 됩니다. 

		*주의 사항 : PDWDATA 구조체에 과제 정보가 없거나 PDW 수집개수가 4096 개 초과되면 Start()에서 바로 리턴한다. LOB 개수는 0 으로 리턴한다.

*/
namespace RadarDirAlgotirhm
{
	// This class is exported from the MathFuncsDll.dll
	class RadarDirAlgotirhm
	{
	public: 
		static MATHFUNCSDLL_API void Init( HWND hWnd=0, bool bLocal=false );
		static MATHFUNCSDLL_API void SetMute( bool bEnable );
		static MATHFUNCSDLL_API void SWInit();

		static MATHFUNCSDLL_API void Close();

		static MATHFUNCSDLL_API void Start( STR_PDWDATA *pPDWData );
        static MATHFUNCSDLL_API void LoadCEDLibrary();

		static MATHFUNCSDLL_API int GetCoLOB();
		static MATHFUNCSDLL_API SRxLOBData *GetLOBData();

#pragma data_seg( ".ioshare" )
        // static CLog *g_pTheLog;
#pragma data_seg()

		//static MATHFUNCSDLL_API void Log( int nType, const char *fmt, ... );
	};

}



