
#pragma once


#include <vector>
using namespace std;

#include "../INC/OS.h"
#include "../INC/PDW.h"

#include "../Identify/ELCEDLibDataType2.h"

//#define XOR_I_DATA			(0x8A5A)
//#define XOR_Q_DATA			(0x8A5A)


#define LENGTH_OF_TASK_ID		(19+1)		//과제ID 문자열 길이 (TBD)
#define MAX_IDCANDIDATE			(10)
#define MAX_COLLECTING_LIST		(100)

#define THREE_LEVEL_IDCANDIDATE         (3)


#define MAX_LOB_ITEMS					50		//

//추가됨
template <class T>
static T SwapEndian (T* tObjp)
{
    unsigned char *puchMem=reinterpret_cast<unsigned char*>(tObjp);
        //reverse(puchMem, puchMem+sizeof(T));
	return *tObjp;
}

/*! 항공에서 수신되는 LOB 메시지의 Data 구조체
 * @struct  SRxLOBData
 * @brief		위협 데이터	
 */
#ifndef _SRxLOBHeader
#define _SRxLOBHeader
struct SRxLOBHeader
{
    unsigned int uiNumOfLOB;

#ifdef _POCKETSONATA_
    unsigned int uiEWRecProc;   // EW수신처리판 번호
#endif


};
#endif




#define MAX_FREQ_PRI_STEP                   (MAX_STAGGER_LEVEL_ELEMENT)



// ELMsgDefn.h
#ifndef _SRxLOBData_STRUCT
#define _SRxLOBData_STRUCT
struct SRxLOBData {
    unsigned int uiPDWID;

    unsigned int uiPLOBID;

	unsigned int uiLOBID;
	unsigned int uiABTID;
	unsigned int uiAETID;

	time_t tiContactTime;			// _USE_32BIT_TIME_T 로 선언하면 32비트, 없으면 64비트로 설정됨.
	unsigned int tiContactTimems;

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

	int iSignalType;

	float fDOAMean;             // [0.1도]
	float fDOAMax;
	float fDOAMin;
	float fDOADeviation;		// [0.1도]
    float fDOAMode;             // DOA 최빈수

	int iDIRatio;					// [1 %]

	int iFreqType;
	int iFreqPatternType;
	float fFreqPatternPeriod;                       // [us]
	float fFreqMean;				// [10KHz]
	float fFreqMax;
	float fFreqMin;
	float fFreqDeviation;       
    float fFreqMode;            // Freq 최빈수
	int iFreqPositionCount;
	int iFreqElementCount;
	float fFreqSeq[MAX_FREQ_PRI_STEP];	// 주파수 단값

	int iPRIType;
	int iPRIPatternType;
	float fPRIPatternPeriod;		// [us]
	float fPRIMean;				// [1ns]
	float fPRIMax;
	float fPRIMin;
	float fPRIDeviation;		// [1ns]
    float fPRIMode;             // PRI 최빈수
	float fPRIJitterRatio;		// [%]
	int iPRIPositionCount;
	int iPRIElementCount;
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
#elif defined(_POCKETSONATA_)
	int iScanType;
	float fScanPeriod;			// [msec]

	int iMOPType;				// 인트라 타입
	int iDetailMOPType;			// 인트라 세부 타입. 항공에서 줄 수 있는것인지(?)
	float fMOPMaxFreq;			// ??
	float fMOPMinFreq;
	float fMOPMeanFreq;
	float fMOPFreqDeviation;

#else
	int iScanType;
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

    int iTotalOfPDW;			// 신호 수집 개수
	int iNumOfPDW;

#if defined(_XBAND_) || defined(_ELINT_)
	int iNumOfIQ;
#endif

	char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];
	int iRadarModeIndex;

	float fCollectLatitude;
	float fCollectLongitude;		

#ifdef _POCKETSONATA_


#elif defined(_ELINT_) || defined(_XBAND_) || defined(_701_)
	char aucTaskID[LENGTH_OF_TASK_ID];
	int	iCollectorID;
	unsigned int uiSeqNum;

#else
#endif

#if defined(_ELINT_) || defined(_XBAND_)
	unsigned int uiOpInitID;

#endif

}  ;
#endif

#ifndef _SRxABTHeader
#define _SRxABTHeader
struct SRxABTHeader
{
	int iNumOfABT;

};
#endif

#ifndef _SRxABTData
#define _SRxABTData
struct SRxABTData {
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
    time_t tiFinalAlarmTime;

#endif

	int iStat;
    

}  ;
#endif

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

#ifndef SRxScanData_STRUCT
#define SRxScanData_STRUCT
struct SRxScanData {
    UINT uiABTID;
    UINT uiAETID;

    EN_SCANRESULT enResult;

    float fScnPrd;     //! 스캔 주기값
    UINT uiScnTyp;     //! 스캔 형태
};
#endif

struct SCollectingList
{
	unsigned int uiNumOfList;
	SCollectingData stCollectingData[MAX_COLLECTING_LIST];
};

struct STR_TRKSCNPDWDATA {
    STR_STATIC_PDWDATA strPDW;

    SRxABTData strABTData;

}  ;


