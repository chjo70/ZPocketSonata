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
// RADARDIR ������Ʈ ������ �ּ� ���븸 ����ü ���Ǹ� ������ ����.


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
    unsigned int uiEWRecProc;   // EW����ó���� ��ȣ
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


// CED ���̴������ ���ڿ� ���� ���� ȣ��
// �Ʒ� ������ ../../files/Anal/SigAnal/_CED_Define.h �� �ִ� ������ �����ؾ� �մϴ�.

#include "_CED_Define.h"






#ifndef _SRxABTData
#define _SRxABTData
struct SRxABTData { // ���̴� �м�
	unsigned int uiABTID;
	unsigned int uiAETID;

	int iSignalType;

	unsigned int uiCoLOB;

	time_t tiFirstSeenTime;				// 64��Ʈ time_t �� �����ؾ� ��.
	time_t tiLastSeenTime;

	int iRadarModePriority;
	int iRadarPriority;

#if defined(_ELINT_)
	int iPolarization;

#endif

	float fDOAMean;                                 // [0.1��]
	float fDOAMax;
	float fDOAMin;
	float fDOADeviation;				// [0.1��]

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
	float fFreqSeq[MAX_FREQ_PRI_STEP];	// ���ļ� �ܰ�

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

	float fPAMean;											// �������
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
	float fTheta;									// [0.1��]
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
	char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1��° ELNOT

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
	char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1��° ELNOT

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

	time_t tiFirstSeenTime;				// 64��Ʈ time_t �� �����ؾ� ��.
	time_t tiLastSeenTime;

	int iValidity;

#if defined(_POCKETSONATA_) || defined(_ELINT_) || defined(_XBAND_)
	float fDOAMean;                                 // [0.1��]
	float fDOAMax;
	float fDOAMin;
	float fDOADeviation;				// [0.1��]
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

	float fPAMean;											// �������
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
	float fTheta;									// [0.1��]
	float fDistanceErrorOfThreat;	// [m]

	char szIDInfo[_MAX_SIZE_OF_IDINFO];

#if defined(_XBAND_) || defined(_ELINT_)
	__time32_t tiFinalAlarmTime;

#endif

	int iStat;
    

};
#endif




//////////////////////////////////////////////////////////////////////////
// ���� ���

/* 1. ���۽� �ѹ��� ȣ���ϸ� �˴ϴ�.
	 ���� ���α׷����� �ʱ�ȭ�ÿ� �Ʒ� ��ƾ�� �ѹ� ȣ���ϸ� �˴ϴ�.

   RadarAnlAlgotirhm::RadarAnlAlgotirhm::Init();

	 2. ���α׷� ����� �ѹ��� ȣ���ϸ� �˴ϴ�.

	 RadarAnlAlgotirhm::RadarAnlAlgotirhm::Close();

	 3. ���� ���� ȣ��� STR_LOBDATA ������ �Ʒ��� ���� �����Ͱ� �־�� �մϴ�.

STR_LOBDATA stLOBData;

typedef struct 
{
	int iNumOfLOB;													<---- LOB ����, �ִ� 100�� �����̴�.
} SRxLOBHeader;

typedef struct {
	SRxLOBHeader stLOBHeader;								<---- LOB ��� ����ü
	SRxLOBData stLOBData[100];							<---- LOB ������

} STR_LOBDATA ;

RadarAnlAlgotirhm::RadarAnlAlgotirhm::Start( & stLOBData );

		4. �м� ����� �Ʒ� �Լ��� ȣ���Ͽ� LOB ������ �����͸� ��´�.
		
		STR_LOBDATA stResLOBData;
		STR_ABTDATA stResABTData;

		RadarAnlAlgotirhm::RadarAnlAlgotirhm::GetLOBData( & stResLOBData );			<---- LOB ���
		RadarAnlAlgotirhm::RadarAnlAlgotirhm::GetABTData( & stResABTData );			<---- ABT ���

		stResLOBData ����ü�� stResABTData ����ü�� ���� �̿��ϸ� �˴ϴ�.

		*���� ���� : ���� ���� ȣ��� LOB ������ 100 �� �ʰ��̸� ���� ������ �ߴ��Ѵ�. ���� ������ ���� ...
								 ���� �Է� LOB ����� 10�� �̸� LOB ���� ����� 10�� �̾�� �ϰ� ABT ����� 10 �� �̸��̾�� ��.
								 ����, LOB Ŭ�����͸��� �߰��ϰ� �Ǹ� LOB ���� ����� �� ��� ������ 10�� �̻�/�ִ� 10�� �̸� �� �� �ֽ��ϴ�.

	5. CED �� EOB ���̺귯���� ��������� �̸� ���� ����.�ĺ� ��⿡ �˷��ֱ� �����̴�.

		RadarAnlAlgotirhm::RadarAnlAlgotirhm::UpdateCEDEOBLibrary();						<---- CED/EOB ������Ʈ�� �˷��ش�.


		6. ��� �ʱ�ȭ ��� �ʱ�ȭ�ÿ� ���ü �� ��/LOB ��ȣ�� 1�� ���� ������ϸ� ���� ���� ���̺� �ʱ�ȭ�Ͽ� ó������ �м��� �����Ѵ�.

		RadarAnlAlgotirhm::RadarAnlAlgotirhm::SWInit();													<---- ��� �ʱ�ȭ�� �����Ѵ�.

*/

namespace RadarAnlAlgotirhm
{
	
	class RadarAnlAlgotirhm
	{
	public: 
        // ��� ����Ʈ���� ����� ���� ���� �� �ĺ� ���̺귯���� �ʱ�ȭ�ϱ� ���ؼ� �Ʒ� �Լ��� ȣ���ؾ� �մϴ�.
		static MATHFUNCSDLL_API void Init( HWND hWnd=0, bool bDBThread=false, bool bLocal=false );

        // ��� ����Ʈ���� ������ �Ʒ� �Լ��� ȣ���ؼ� ���� ���� /�ĺ� ����� �ݴ´�.
		static MATHFUNCSDLL_API void Close();

        // ��� ����Ʈ���� ���� ���� ���� �� �ĺ� �� �ϱ� ���ؼ� �Ʒ� �Լ��� ȣ���մϴ�.
		static MATHFUNCSDLL_API bool Start( STR_LOBDATA *pLOBData );

        // ��� ����Ʈ���� ���� ���� ���� �� �ĺ� ���̺귯���� �ʱ�ȭ������ �� �� �Ʒ� �Լ��� ȣ���Ѵ�.
		static MATHFUNCSDLL_API void SWInit();

        // ��� ����Ʈ���� ���� CED/EOB ����� �Ʒ� �Լ��� ȣ���ؼ� CED/EOB �ε��ϵ��� �Ѵ�.
		static MATHFUNCSDLL_API void UpdateCEDEOBLibrary();


#ifdef _POCKETSONATA_
        // ��� ����Ʈ����� �Է��� LOB �����Ϳ� ���� ��� ������ ��´�.
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



