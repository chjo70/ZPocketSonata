

#ifndef _H_EL_MSG_DEFN
#define _H_EL_MSG_DEFN

#pragma once


#include <vector>
using namespace std;

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
#ifndef _STR_LOBHEADER
#define _STR_LOBHEADER
struct SRxLOBHeader
{
    int iNumOfLOB;

};
#endif


/*! 
 * @struct    SRxLOBData
 * @brief			항공에서 수신되는 LOB 메시지의 Data Group 구조체
 * @author    이정남 (jeongnam.lee@lignex1.com)
 * @date      2016-02-16 오후 12:06 
 */
#define MAX_RADARNAME						(9+1)
#define MAX_FREQ_PRI_STEP                   (16*2)


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

    int iPolarization;                              // 극성
    int iRatioOfPOL;                                // 극성 신뢰도

    int iSignalType;

    float fMeanDOA;                                 // [0.1도]
    float fMaxDOA;
    float fMinDOA;
    float fDeviationDOA;				// [0.1도]
    float fSDeviationDOA;

    int iDIRatio;					// [1 %]

    int iFreqType;
    int iFreqPatternType;
    float fFreqPatternPeriod;                       // [us]
    float fMeanFreq;				// [10KHz]
    float fMaxFreq;
    float fMinFreq;
    float fFreqDeviation;                           //
    int iFreqPositionCount;
    int iFreqElementCount;
    float fFreqSeq[MAX_FREQ_PRI_STEP];	// 주파수 단값

    int iPRIType;
    int iPRIPatternType;
    float fPRIPatternPeriod;		// [us]
    float fMeanPRI;				// [1ns]
    float fMaxPRI;
    float fMinPRI;
    float fPRIDeviation;			// [1ns]
    float fPRIJitterRatio;			// [%]
    int iPRIPositionCount;
    int iPRIElementCount;
    float fPRISeq[MAX_FREQ_PRI_STEP];

    float fMeanPW;				// 1ns
    float fMaxPW;
    float fMinPW;
    float fPWDeviation;

    float fMeanPA;				// 기존대로
    float fMaxPA;
    float fMinPA;
    float fPADeviation;			// 기존대로

    int iScanType;
    //int iDetailScanType;
    float fScanPeriod;			// [usec]

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

    int iIsStoreData;
    int iNumOfPDW;
    int iNumOfIQ;

    float fRadarLatitude;
    float fRadarLongitude;

    int iRadarModeIndex;
    int iThreatIndex;

#ifndef _POCKETSONATA_
	char	aucTaskID[LENGTH_OF_TASK_ID];
#endif

}  ;
#endif

#ifndef _STR_ABTHEADER
#define _STR_ABTHEADER
struct SRxABTHeader
{
	int iNumOfABT;

};
#endif

#ifndef _STR_ABTDATA_STRUCT
#define _STR_ABTDATA_STRUCT
struct SRxABTData {
    unsigned int uiABTID;
    unsigned int uiAETID;

    int iSignalType;

    unsigned int uiCoLOB;

    __time32_t tiFirstSeenTime;				// 32비트 time_t 로 선언해야 함.
    __time32_t tiLastSeenTime;

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

#ifdef _POCKETSONATA_
    float fMeanDOA;                                 // [0.1도]
    float fMaxDOA;
    float fMinDOA;
    float fDeviationDOA;				// [0.1도]
    float fSDeviationDOA;
#endif

    int iFreqType;
    int iFreqPatternType;
    float fFreqPatternPeriodMean;	  // [us]
    float fFreqPatternPeriodMin;	  // [us]
    float fFreqPatternPeriodMax;	  // [us]
    float fMeanFreq;										// [10KHz]
    float fMaxFreq;
    float fMinFreq;
    float fFreqDeviation;
    int iFreqPositionCount;
    int iFreqElementCount;
    float fFreqSeq[MAX_FREQ_PRI_STEP];	// 주파수 단값

    int iPRIType;
    int iPRIPatternType;
    float fPRIPatternPeriodMean;							// [us]
    float fPRIPatternPeriodMin;							// [us]
    float fPRIPatternPeriodMax;							// [us]
    float fMeanPRI;											// [1ns]
    float fMaxPRI;
    float fMinPRI;
    float fPRIDeviation;			// [1ns]
    float fPRIJitterRatio;							// [%]
    int iPRIPositionCount;
    int iPRIElementCount;
    float fPRISeq[MAX_FREQ_PRI_STEP];

    float fMeanPW;											// 1ns
    float fMaxPW;
    float fMinPW;
    float fPWDeviation;

    float fMeanPA;											// 기존대로
    float fMaxPA;
    float fMinPA;
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
    char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
    char szNickName[_MAX_NICKNAME_STRING_SIZE_];
    char szPlaceNameKor[_MAX_SIZE_OF_KOREASITENAME_];

    int iPlatformType;
    int iPinNum;
    char szThreatFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];

    int iRadarModePriority;
    int iRadarPriority;
    int iThreatPriority;

    __time32_t tiFirstSeenTime;				// 32비트 time_t 로 선언해야 함.
    __time32_t tiLastSeenTime;

    int iValidity;

#ifdef _POCKETSONATA_
    float fMeanDOA;                                 // [0.1도]
    float fMaxDOA;
    float fMinDOA;
    float fDeviationDOA;				// [0.1도]
#endif

    int iFreqType;
    int iFreqPatternType;
    float fFreqPatternPeriodMean;	  // [us]
    float fFreqPatternPeriodMin;	  // [us]
    float fFreqPatternPeriodMax;	  // [us]
    int iFreqPositionCount;
    float fMeanFreq;										// [10KHz]
    float fMaxFreq;
    float fMinFreq;
    float fDeviationFreq;

    int iPRIType;
    int iPRIPatternType;
    float fPRIPatternPeriodMean;							// [us]
    float fPRIPatternPeriodMin;							// [us]
    float fPRIPatternPeriodMax;							// [us]
    float fMeanPRI;											// [1ns]
    float fMaxPRI;
    float fMinPRI;
    float fPRIJitterRatio;
    float fDeviationPRI;// [%]
    int iPRIPositionCount;

    float fMeanPW;											// 1ns
    float fMaxPW;
    float fMinPW;
    float fDeviationPW;

    float fMeanPA;											// 기존대로
    float fMaxPA;
    float fMinPA;
    float fDeviationPA;

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

    __time32_t tiFinalAlarmTime;

    //int iManualLatitude;
    //int iManualLongitude;

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

}  ;

struct SCollectingList
{
	unsigned int uiNumOfList;
	SCollectingData stCollectingData[MAX_COLLECTING_LIST];
};


#endif
