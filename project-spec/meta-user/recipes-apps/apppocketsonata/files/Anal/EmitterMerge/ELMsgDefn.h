/**

    @file      ELMsgDefn.h
    @brief
    @details   ~
    @author    조철희
    @date      16.06.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


#include <vector>
using namespace std;

#include "../INC/OS.h"
#include "../INC/PDW.h"

#include "../Identify/ELCEDLibDataType2.h"

#include "ELStringDefn.h"

//#define XOR_I_DATA			(0x8A5A)
//#define XOR_Q_DATA			(0x8A5A)


#define LENGTH_OF_TASK_ID		(19+1)		//과제ID 문자열 길이 (TBD)
#define MAX_IDCANDIDATE			(10)

#define THREE_LEVEL_IDCANDIDATE         (3)


/**
    @brief
    @tparam T     -
    @param  tObjp -
    @retval       -
**/
template <class T>
static T SwapEndian (T* tObjp)
{
    unsigned char *puchMem=reinterpret_cast<unsigned char*>(tObjp);
        //reverse(puchMem, puchMem+sizeof(T));
	return *tObjp;
}

#pragma pack( push, 1 )

//#include "LOBABTAET.h"

/*! 항공에서 수신되는 LOB 메시지의 Data 구조체
 * @struct  SRxLOBData
 * @brief		위협 데이터
 */
#ifndef _SRxLOBHeader
#define _SRxLOBHeader
struct SRxLOBHeader
{
    unsigned int uiNumOfLOB;

#if defined(_POCKETSONATA_) || defined(_712_)
    unsigned int uiEWRecProc;   // EW수신처리판 번호
#endif

};
#endif


#ifndef MAX_FREQ_PRI_STEP
#define MAX_FREQ_PRI_STEP                   (MAX_STAGGER_LEVEL_POSITION)
#endif


#ifndef _SRxLOBData_STRUCT
#define _SRxLOBData_STRUCT
struct SRxLOBData {
    unsigned int uiPDWID;

    unsigned int uiPLOBID;

	unsigned int uiLOBID;
	unsigned int uiABTID;
	unsigned int uiAETID;

	unsigned int tiContactTime;			// _USE_32BIT_TIME_T 로 선언하면 32비트, 없으면 64비트로 설정됨.

#if defined(_POCKETSONATA_) || defined(_712_)
	unsigned short tiContactTimems;
#else
    unsigned int tiContactTimems;
#endif

	char szPrimaryELNOT[_MAX_ELNOT_STRING_SIZE_];
	char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1번째 ELNOT

	char szSecondaryELNOT[_MAX_ELNOT_STRING_SIZE_];
	char szSecondaryModeCode[_MAX_SIZE_OF_MODECODE];							// 2번째 ELNOT

	char szTertiaryELNOT[_MAX_ELNOT_STRING_SIZE_];												// 3번째 ELNOT
	char szTertiaryModeCode[_MAX_SIZE_OF_MODECODE];

	char szModulationCode[_MAX_MODECODE_STRING_SIZE_];

#if defined(_XBAND_) || defined(_ELINT_)
	char szRadarName[_MAX_RADARMODE_NAME_SIZE];
	char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
#endif

	char szNickName[_MAX_NICKNAME_STRING_SIZE_];

#ifdef _ELINT_
	int iPolarization;          // 극성
	int iRatioOfPOL;            // 극성 신뢰도

#endif

#if defined(_POCKETSONATA_) || defined(_712_)
	unsigned char vSignalType;
#else
    unsigned int vSignalType;
#endif

	float fDOAMean;             // [0.1도]
	float fDOAMax;
	float fDOAMin;
	float fDOADeviation;		// [0.1도]
    float fDOAMode;             // DOA 최빈수

	unsigned int uiDIRatio;					// [1 %]

    ENUM_AET_FRQ_TYPE vFreqType;
    ENUM_AET_FREQ_PRI_PATTERN_TYPE vFreqPatternType;

	float fFreqPatternPeriod;                       // [us]
	float fFreqMean;				// [10KHz]
	float fFreqMax;
	float fFreqMin;
	float fFreqDeviation;
    float fFreqMode;            // Freq 최빈수

#if defined(_POCKETSONATA_) || defined(_712_)
    unsigned char vFreqPositionCount;
    unsigned char vFreqElementCount;
#else
	int vFreqPositionCount;
	int vFreqElementCount;
#endif

	float fFreqSeq[MAX_FREQ_PRI_STEP];	// 주파수 단값

    ENUM_AET_PRI_TYPE vPRIType;
    ENUM_AET_FREQ_PRI_PATTERN_TYPE vPRIPatternType;

	float fPRIPatternPeriod;		// [us]
	float fPRIMean;				// [1ns]
	float fPRIMax;
	float fPRIMin;
	float fPRIDeviation;		// [1ns]
    float fPRIMode;             // PRI 최빈수
	float fPRIJitterRatio;		// [%]

#if defined(_POCKETSONATA_) || defined(_712_)
    unsigned char vPRIPositionCount;
    unsigned char vPRIElementCount;
#else
	int vPRIPositionCount;
	int vPRIElementCount;
#endif

	float fPRISeq[MAX_FREQ_PRI_STEP];

	float fPWMean;				// 1ns
	float fPWMax;
	float fPWMin;
	float fPWDeviation;
    float fPWMode;              // 펄스폭 최빈수

	float fPAMean;
	float fPAMax;
	float fPAMin;
	float fPADeviation;
    float fPAMode;              // 신호세기 최빈수

#if defined(_XBAND_) || defined(_ELINT_)
#elif defined(_POCKETSONATA_) || defined(_712_)
    ENUM_AET_SCAN_TYPE vScanType;
	float fMeanScanPeriod;			// [msec]

    ENUM_MOP_TYPE enMOPType;				// 인트라 타입
    unsigned char ucDetailMOPType;			// 인트라 세부 타입.
	float fMOPMaxFreq;
	float fMOPMinFreq;
	float fMOPMeanFreq;
	float fMOPFreqDeviation;

#else
    ENUM_AET_SCAN_TYPE vScanType;
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

#if defined(_XBAND_) || defined(_ELINT_)
	int iIsStoreData;
#endif

    unsigned int uiNumOfCollectedPDW;			// 신호 수집 개수
	unsigned int uiNumOfAnalyzedPDW;             // 분석된 PDW 개수

#if defined(_XBAND_) || defined(_ELINT_)
	int iNumOfIQ;
#endif

	char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];
	unsigned int uiRadarModeIndex;

    unsigned int uiRadarIndex;                  // 레이더 인덱스 : ELNOT

	float fCollectLatitude;
	float fCollectLongitude;

#if defined(_POCKETSONATA_) || defined(_712_)

#elif defined(_ELINT_) || defined(_XBAND_) || defined(_701_)
	char aucTaskID[LENGTH_OF_TASK_ID];
	int	iCollectorID;
	unsigned int uiSeqNum;

#else
#endif

#if defined(_ELINT_) || defined(_XBAND_)
	unsigned int uiOpInitID;

#endif

} ;
#endif

#ifndef _SRxABTHeader
#define _SRxABTHeader
struct SRxABTHeader
{
	int iNumOfABT;

};
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

    float fDOAMean;
    float fDOAMax;
    float fDOAMin;
    float fDOADeviation;

    ENUM_AET_FRQ_TYPE vFreqType;
    ENUM_AET_FREQ_PRI_PATTERN_TYPE vFreqPatternType;

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

    ENUM_AET_PRI_TYPE vPRIType;
    ENUM_AET_FREQ_PRI_PATTERN_TYPE vPRIPatternType;

    float fPRIPatternPeriodMean;							// [us]
    float fPRIPatternPeriodMin;							// [us]
    float fPRIPatternPeriodMax;							// [us]
    float fPRIMean;											// [1ns]
    float fPRIMax;
    float fPRIMin;
    float fPRIDeviation;			// [1ns]
    float fPRIJitterPercent;							// [%]

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

    float fMeanScanPeriod;          // [usec]
    float fMaxScanPeriod;			// [usec]
    float fMinScanPeriod;			// [usec]

#if defined(_POCKETSONATA_) || defined(_712_)
    ENUM_AET_SCAN_STAT vScanStat;
#endif

#if defined(_POCKETSONATA_) || defined(_712_)
    //bool bHasIntraMod;
    ENUM_MOP_TYPE enMOPType;
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

}  ;
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

}  ;
#endif

//
///////////////////////////////////////////////////////////////////////////////////

struct SAETData {
    SRxLOBData stLOBData;
    SRxABTData stABTData;
    SRxAETData stAETData;

} ;

struct SCollectingData {
	char aucTaskID[LENGTH_OF_TASK_ID];
	unsigned int uiSearchStartFrequency;
	unsigned int uiSearchEndFrequency;
	unsigned int uiRxPath;
	unsigned int uiDetectIFBandwidth;
	unsigned int uiHighGainIFBandwidth;
	unsigned int uiNBDRBandwidth;
	unsigned int uiRxThresholdMode;
	int iRxThresholdValue;
	unsigned int uiCWDecisionPW;
	unsigned int uiNumOfCWChopping;
	unsigned int uiCWChoppingInterval;
	unsigned int uiSignalCheckTime;
	unsigned int uiSignalCheckPulseNumber;
	unsigned int uiNumOfAcqTimes;
	unsigned int uiAcquisitionTime;
	unsigned int uiNumOfAcqPulse;
	unsigned int uiUseFMOPLimit;
	unsigned int uiFMOPLimit;
	unsigned int uiUsePMOPLimit;
	unsigned int uiPMOPLimit;
	unsigned int uiUseDetectMinPW;
	unsigned int uiDetectMinPW;
	unsigned int uiRecord_AnalysisResult;
	unsigned int uiRecord_PDW;
	unsigned int uiRecord_IF;
	unsigned int uiRecord_Spectrum;
	unsigned int uiFilterType;
	unsigned int uiIsCWFilterApply;
	unsigned int uiIsFreqFilterApply;
	unsigned int uiFilterMinFreq;
	unsigned int uiFilterMaxFreq;
	unsigned int uiIsPAFilterApply;
	int iFilterMinPA;
	unsigned int iFilterMaxPA;
	unsigned int uiIsPWFilterApply;
	unsigned int uiFilterMinPW;
	unsigned int uiFilterMaxPW;
	unsigned int uiIsDOAFilterApply;
	unsigned int uiFilterMinDOA;
	unsigned int uiFilterMaxDOA;
	unsigned int uiIsDVEnable;
	unsigned int uiIsPolarizationFilterApply;

} ;





// struct SCollectingList
// {
// 	unsigned int uiNumOfList;
// 	SCollectingData stCollectingData[MAX_COLLECTING_LIST];
// };

/**
    @struct STR_TRKSCNPDWDATA
    @brief  추적 및 스캔용 PDW 데이터 와 빔 정보 저장소
**/
struct STR_TRKSCNPDWDATA {
    SRxABTData strABTData;

    STR_STATIC_PDWDATA strPDW;

}  ;


#pragma pack( pop )

