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

#ifndef _ENUM_DataType
#define _ENUM_DataType
typedef enum {
    en_UnknownData = 0,

    en_PDW_DATA,
    en_IQ_DATA,
    en_IF_DATA,

} ENUM_DataType;
#endif

#ifndef _ENUM_UnitType
#define _ENUM_UnitType
typedef enum {
    en_UnknownUnit = 0,

    en_SONATA,
    en_SONATA_SHU,
    en_ELINT,
    en_XBAND,
    en_701,
    en_KFX,
    en_ZPOCKETSONATA,

    en_MIDAS,

} ENUM_UnitType;
#endif

#if TOOL==diab 
#pragma pack( 1 )
#else
#pragma pack( push, 1 )
#endif

#ifndef _PDW_STRUCT
#define _PDW_STRUCT
typedef struct {
    unsigned long long int ullTOA;

    int iPulseType;

    unsigned int uiAOA;
    unsigned int uiFreq;
    unsigned int uiPA;
    unsigned int uiPW;

    int iPFTag;

#if defined(_ELINT_)
    float fPh1;
    float fPh2;
    float fPh3;
    float fPh4;

#elif defined(_XBAND_)
    float fPh1;
    float fPh2;
    float fPh3;
    float fPh4;
    float fPh5;

#elif _POCKETSONATA_
    int iPMOP;
    int iFMOP;

    int iChannel;
#endif

    unsigned long long int GetTOA() {
        return ullTOA;
    }

    int GetChannel() {
#ifdef _POCKETSONATA_
        return iChannel;
#else
        return 0;
#endif
    }

    unsigned int GetFrequency( int iCh=0 ) {
        return uiFreq;
    }

    unsigned int GetPulsewidth() {
        return uiPW;
    }

    unsigned int GetAOA() {
        return uiAOA;
    }

    unsigned int GetPulseamplitude() {
        return uiPA;

    }

    int GetPulsetype() {
        return iPulseType;
    }

} _PDW;
#endif

#if TOOL==diab 
#pragma pack( 4 )
#else
#pragma pack( pop )
#endif

#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
	en5MHZ_BW=0,
	en50MHZ_BW,

    enUnknown_BW=-1

} ENUM_BANDWIDTH ;
#endif

#ifndef _STR_COMMON_HEADER_
#define _STR_COMMON_HEADER_
// 아래는 공용 정보
typedef struct {
    UINT uiTotalPDW;
    __time32_t tColTime;
    UINT uiColTimeMs;
    UINT _dummy;

} STR_COMMON_HEADER ;
#endif

#ifndef _STR_ELINT_HEADER_
#define _STR_ELINT_HEADER_
typedef struct {
    unsigned char aucTaskID[LENGTH_OF_TASK_ID];
    unsigned int iIsStorePDW;
    int iCollectorID;
    ENUM_BANDWIDTH enBandWidth;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    unsigned int GetTotalPDW() {
        return stCommon.uiTotalPDW;
    }

    void SetTotalPDW( unsigned uiTotalPDW ) {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

} STR_ELINT_HEADER ;
#endif

#ifndef _POCKETSONATA_HEADER_
#define _POCKETSONATA_HEADER_
typedef struct {
    unsigned int uiBoardID;
    unsigned int iBank;
    unsigned int uiBand;                // 주파수 대역
    unsigned int iIsStorePDW;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    unsigned int GetTotalPDW() {
        return stCommon.uiTotalPDW;
    }

    void SetTotalPDW( unsigned uiTotalPDW ) {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

} POCKETSONATA_HEADER ;
#endif

#ifndef _SONATA_HEADER_
#define _SONATA_HEADER_
typedef struct {
    unsigned int uiBand;
    unsigned int iIsStorePDW;

    // 아래는 공용 정보
    STR_COMMON_HEADER stCommon;

    unsigned int GetTotalPDW() {
        return stCommon.uiTotalPDW;
    }

    void SetTotalPDW( unsigned uiTotalPDW ) {
        stCommon.uiTotalPDW = uiTotalPDW;
    }

} SONATA_HEADER ;
#endif

#ifndef _UNION_HEADER_
#define _UNION_HEADER_
typedef union {
        STR_ELINT_HEADER el;

        POCKETSONATA_HEADER ps;

        SONATA_HEADER so;

    unsigned int GetTotalPDW( ENUM_UnitType enUnitType ) {
        unsigned int uiTotalPDW;

        switch( enUnitType ) {
            case en_ZPOCKETSONATA :
                uiTotalPDW = ps.stCommon.uiTotalPDW;
                break;

            case en_ELINT :
            case en_XBAND :
                uiTotalPDW = el.stCommon.uiTotalPDW;
                break;

            case en_SONATA :
                uiTotalPDW = so.stCommon.uiTotalPDW;
                break;

        }
        return uiTotalPDW;

    }

} UNION_HEADER;
#endif

#ifndef _STR_PDWDATA
#define _STR_PDWDATA
struct STR_PDWDATA {
    UNION_HEADER x;

    _PDW *pstPDW;

    unsigned int GetHeader() {
        unsigned int uiHeader;

#ifdef _POCKETSONATA_
        uiHeader = sizeof( POCKETSONATA_HEADER );
#elif defined(_ELINT_) || defined(_XBAND_)
        uiHeader = sizeof( STR_ELINT_HEADER );
#else
        uiHeader = sizeof( SONATA_HEADER );
#endif
        return uiHeader;

    }

    unsigned int GetTotalPDW() {
        unsigned int uiTotalPDW;

#ifdef _POCKETSONATA_
        uiTotalPDW = x.ps.stCommon.uiTotalPDW;
#elif defined(_ELINT_) || defined(_XBAND_)
        uiTotalPDW = x.el.stCommon.uiTotalPDW;
#else
        uiTotalPDW = x.so.stCommon.uiTotalPDW;
#endif
        return uiTotalPDW;

    }

    void SetTotalPDW( unsigned int uiTotalPDW ) {
#ifdef _POCKETSONATA_
        x.ps.stCommon.uiTotalPDW = uiTotalPDW;
#elif defined(_ELINT_) || defined(_XBAND_)
        x.el.stCommon.uiTotalPDW = uiTotalPDW;;
#else
        x.so.stCommon.uiTotalPDW = uiTotalPDW;;
#endif
        return;

    }

    void SetColTime( __time32_t tColTime, UINT uiColTimeMs ) {

#ifdef _POCKETSONATA_
        x.ps.stCommon.tColTime = tColTime;
        x.ps.stCommon.uiColTimeMs = uiColTimeMs;
#elif defined(_ELINT_) || defined(_XBAND_)
        x.el.stCommon.tColTime = tColTime;
        x.el.stCommon.uiColTimeMs = uiColTimeMs;
#else
        x.so.stCommon.tColTime = tColTime;
        x.so.stCommon.uiColTimeMs = uiColTimeMs;
#endif
        return;

    }

    __time32_t GetColTime() {
        __time32_t retTime;

#ifdef _POCKETSONATA_
        retTime = x.ps.stCommon.tColTime;
#elif defined(_ELINT_) || defined(_XBAND_)
        retTime = x.el.stCommon.tColTime;
#else
        retTime = x.so.stCommon.tColTime;
#endif
        return retTime;

    }

    int GetStorePDW() {
        int iStorePDW;

#ifdef _POCKETSONATA_
        iStorePDW = x.ps.iIsStorePDW;
#elif defined(_ELINT_) || defined(_XBAND_)
        iStorePDW = x.el.iIsStorePDW;
#else
        iStorePDW = x.so.iIsStorePDW;
#endif
        return iStorePDW;
    }

    ENUM_BANDWIDTH GetBandWidth()
    {
        ENUM_BANDWIDTH enBandwidth;

#ifdef _POCKETSONATA_
        enBandwidth = enUnknown_BW;
#elif defined(_ELINT_) || defined(_XBAND_)
        enBandwidth = x.el.enBandWidth;
#else
        enBandwidth = enUnknown_BW;
#endif
        return enBandwidth;
    }

}  ;
#endif

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
    unsigned int uiPDWID;

    unsigned int uiPLOBID;

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
	char szRadarName[_MAX_RADARMODE_NAME_SIZE];
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

#if defined(_XBAND_) || defined(_ELINT_)
#else
    int iScanType;
    //int iDetailScanType;
    float fScanPeriod;			// [msec]

    int iMOPType;				// 인트라 타입
    int iDetailMOPType;			// 인트라 세부 타입. 항공에서 줄 수 있는것인지(?)
    float fMOPMaxFreq;			// ??
    float fMOPMinFreq;
    float fMOPMeanFreq;
    float fMOPFreqDeviation;

    float fPitchAngle;
    float fRollAngle;
    float fHeadingAngle;
    float fAltitude;
    int iValidity;
#endif

    int iIsStoreData;
    int iNumOfPDW;
    int iNumOfIQ;

	char szRadarModeName[_MAX_RADARNAME_SIZE];
    int iRadarModeIndex;
    //int iThreatIndex;

    float fLatitude;
    float fLongitude;		

    char aucTaskID[LENGTH_OF_TASK_ID];

#ifdef _POCKETSONATA_


#elif defined(_ELINT_) || defined(_XBAND_)
    int	iCollectorID;

    unsigned int uiSeqNum;

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



