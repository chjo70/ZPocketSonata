

#ifndef _H_EL_MSG_DEFN
#define _H_EL_MSG_DEFN

#pragma once


#include <vector>
using namespace std;

//#define XOR_I_DATA			(0x8A5A)
//#define XOR_Q_DATA			(0x8A5A)


#define LENGTH_OF_TASK_ID			(19+1)		//과제ID 문자열 길이 (TBD)
#define MAX_IDCANDIDATE				(10)
#define MAX_COLLECTING_LIST		(100)


#define MAX_LOB_ITEMS					50		//

//추가됨
template <class T>
static T SwapEndian (T* tObjp)
{
	UCHAR *puchMem=reinterpret_cast<UCHAR*>(tObjp);
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
#define MAX_FREQ_PRI_STEP				(16)
//#define MAX_PRI_PER_GROUP				(32)
//#define MAX_PADIFF_PER_GROUP		(32)

#ifndef SRxLOBData_STRUCT
#define SRxLOBData_STRUCT
struct SRxLOBData {
	unsigned int uiLOBID;
	unsigned int uiABTID;
	unsigned int uiAETID;

	__time32_t tiContactTime;				// 32비트 time_t 로 선언해야 함. 
	unsigned int tiContactTimems;

	int iSignalType;	

	float	fMeanDOA;										// [0.1도]
	float fMaxDOA;
	float fMinDOA;

	int iDIRatio;										// [1 %]

	int		iFreqType;
	int		iFreqPatternType;			
	float fFreqPatternPeriod;	  // [us]
	float fMeanFreq;										// [10KHz]
	float fMaxFreq;
	float fMinFreq;
	int		iFreqPositionCount;
	float fFreqSeq[MAX_FREQ_PRI_STEP];	// 주파수 단값

	int		iPRIType;
	int		iPRIPatternType;
	float	fPRIPatternPeriod;							// [us]
	float	fMeanPRI;											// [1ns]
	float	fMaxPRI;
	float	fMinPRI;
	float	fPRIJitterRatio;							// [%]
	int		iPRIPositionCount;
	float	fPRISeq[MAX_FREQ_PRI_STEP];

	float	fMeanPW;											// 1ns
	float fMaxPW;
	float fMinPW;

	float fMeanPA;											// 기존대로
	float fMaxPA;
	float fMinPA;

	int		iIsStorePDW;
	int		iNumOfPDW;
	int		iCollectorID;

	double	dRadarCollectionLatitude;
	double	dRadarCollectionLongitude;	

	char aucRadarName[MAX_RADARNAME];
	int iRadarModeIndex;
	int iThreatIndex;

	unsigned int uiSeqNum;
	char	aucTaskID[LENGTH_OF_TASK_ID];

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

	int iValidity;

	int		iFreqType;
	int		iFreqPatternType;			
	float fFreqPatternPeriodMean;	  // [us]
	float fFreqPatternPeriodMin;	  // [us]
	float fFreqPatternPeriodMax;	  // [us]
	int		iFreqPositionCount;
	float fFreqSeq[MAX_FREQ_PRI_STEP];	// 주파수 단값
	float fMeanFreq;										// [10KHz]
	float fMaxFreq;
	float fMinFreq;

	int		iPRIType;
	int		iPRIPatternType;
	float	fPRIPatternPeriodMean;							// [us]
	float	fPRIPatternPeriodMin;							// [us]
	float	fPRIPatternPeriodMax;							// [us]
	float	fMeanPRI;											// [1ns]
	float	fMaxPRI;
	float	fMinPRI;
	float	fPRIJitterRatio;							// [%]
	int		iPRIPositionCount;
	float	fPRISeq[MAX_FREQ_PRI_STEP];

	float	fMeanPW;											// 1ns
	float fMaxPW;
	float fMinPW;

	float fMeanPA;											// 기존대로
	float fMaxPA;
	float fMinPA;

	unsigned int uiTotalOfPDW;

	int iRadarModeIndex;
	int iThreatIndex;

	int iPEValid;
	double dLatitude;							// [deg]
	double dLongitude;							// [deg]
	float fCEP;										// [m]
	float fMajorAxis;							// [m]
	float fMinorAxis;							// [m]
	float fTheta;									// [0.1도]
	float fDistanceErrorOfThreat;	// [m]

	__time32_t tiFinalAlarmTime;

	int iStat;

	char aucRadarName[MAX_RADARNAME];

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
