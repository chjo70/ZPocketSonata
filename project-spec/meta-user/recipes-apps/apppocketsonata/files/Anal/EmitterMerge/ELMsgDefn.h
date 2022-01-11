
#pragma once


#include <vector>
using namespace std;

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
#ifndef _STR_LOBHEADER
#define _STR_LOBHEADER
struct SRxLOBHeader
{
    int iNumOfLOB;

};
#endif


/*! 
 * @struct  SRxLOBData
 * @brief   항공에서 수신되는 LOB 메시지의 Data Group 구조체
 * @author  이정남 (jeongnam.lee@lignex1.com)
 * @date    2016-02-16 오후 12:06 
 */
#define MAX_FREQ_PRI_STEP                   (MAX_STAGGER_LEVEL_ELEMENT)


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

#ifndef _ONPOOM_
	int iPolarization;                              // 극성
#endif

	int iRatioOfPOL;                                // 극성 신뢰도

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

#ifndef _ONPOOM_
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

	char aucRadarName[_MAX_RADARMODE_NAME_SIZE];
	int iRadarModeIndex;
	//int iThreatIndex;


#ifdef _POCKETSONATA_

#elif _ELINT_
	double	dRadarCollectionLatitude;
	double	dRadarCollectionLongitude;	

	int	iCollectorID;

	unsigned int uiSeqNum;
	char aucTaskID[LENGTH_OF_TASK_ID];

#else

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

    time_t /* __time32_t */ tiFirstSeenTime;				// 32비트 time_t 로 선언해야 함.
    time_t /* __time32_t */ tiLastSeenTime;

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

    char aucRadarName[_MAX_RADARMODE_NAME_SIZE];

    char szPrimaryELNOT[_MAX_ELNOT_STRING_SIZE_];
    char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1번째 ELNOT

    char szModulationCode[_MAX_MODECODE_STRING_SIZE_];
    char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];
    char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
    char szPlatform[_MAX_PLATFORM_NAME_SIZE];
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
    char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
    char szNickName[_MAX_NICKNAME_STRING_SIZE_];
    char szPlaceNameKor[_MAX_SIZE_OF_KOREASITENAME_];

    int iPlatformType;
    int iPinNum;
    char szThreatFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];

    int iRadarModePriority;
    int iRadarPriority;
    int iThreatPriority;

    time_t tiFirstSeenTime;				// 32비트 time_t 로 선언해야 함.
    time_t tiLastSeenTime;

    int iValidity;

#if defined(_POCKETSONATA_) || defined(_ELINT_)
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

} ;

#ifndef SRxScanData_STRUCT
#define SRxScanData_STRUCT
struct SRxScanData {
    UINT uiABTID;
    UINT uiAETID;

    UINT uiResult;

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
    STR_PDWDATA strPDW;

    SRxABTData strABTData;

}  ;


