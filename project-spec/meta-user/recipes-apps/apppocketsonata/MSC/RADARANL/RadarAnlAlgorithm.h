#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport)

#else
#define MATHFUNCSDLL_API __declspec(dllimport)
#endif


#define WM_USER_LOGMSG				(7011)

#include "RadarDirAlgorithm.h"

//
// RADARDIR ������Ʈ ������ �ּ� ���븸 ����ü ���Ǹ� ������ ����.


#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
	en5MHZ_BW=0,
	en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif

#ifndef _STR_LOBHEADER
#define _STR_LOBHEADER
typedef struct 
{
	int iNumOfLOB;

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

#ifndef _STR_ABTHEADER
#define _STR_ABTHEADER
struct SRxABTHeader
{
	int iNumOfABT;

};
#endif


#define _MAX_RADARMODENAME_STRING_SIZE_								(30+_NULL_CHAR_)

#define _MAX_STATUS_STRING_SIZE_									(20+_NULL_CHAR_)

#define _MAX_BE_NUMBER_STRING_SIZE_									(12+_NULL_CHAR_)
#define _MAX_USER_COUNTRY_STRING_SIZE_								(4+_NULL_CHAR_)
#define _MAX_PRIMARY_FUNCTION_STRING_SIZE_                          (4+_NULL_CHAR_)
#define _MAX_FRIEND_OR_FOE_STRING_SIZE_								(12+_NULL_CHAR_)
#define _MAX_ADA_STRING_SIZE_										(8+_NULL_CHAR_)
#define _MAX_DATETIME_STRING_SIZE_									(40+_NULL_CHAR_)
#define _MAX_DISTINCTION_STRING_SIZE_								(12+_NULL_CHAR_)
#define _MAX_SYMBOLCODE_STRING_SIZE_								(20+_NULL_CHAR_)
#define _MAX_LATITUDE_STRING_SIZE_									(15+_NULL_CHAR_)
#define _MAX_LONGITUDE_STRING_SIZE_									(15+_NULL_CHAR_)

#define _MAX_WEAPON_STRING_SIZE_									(40+_NULL_CHAR_)
#define _MAX_PLATFORM_STRING_SIZE_									(40+_NULL_CHAR_)

#define _MAX_SIZE_OF_THREATNAME_									(70+_NULL_CHAR_)
#define _MAX_SIZE_OF_KOREASITENAME_									(70+_NULL_CHAR_)
#define _MAX_SIZE_OF_FACILITYNAME_									(72+_NULL_CHAR_)

//#define _MAX_SIZE_OF_MODECODE                                       (4)
#define _MAX_PLATFORM_NAME_SIZE                                     (10)

#ifndef _STR_ABTDATA_STRUCT
#define _STR_ABTDATA_STRUCT
struct SRxABTData {
    unsigned int uiABTID;
    unsigned int uiAETID;

    int iSignalType;

    unsigned int uiCoLOB;

    time_t /* __time32_t */ tiFirstSeenTime;				// 32��Ʈ time_t �� �����ؾ� ��.
    time_t /* __time32_t */ tiLastSeenTime;

    char szPrimaryELNOT[_MAX_ELNOT_STRING_SIZE_];
    char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1��° ELNOT

    char szModulationCode[_MAX_MODECODE_STRING_SIZE_];
    char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];
    char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
    char szPlatform[_MAX_PLATFORM_NAME_SIZE];
    char szNickName[_MAX_NICKNAME_STRING_SIZE_];
    char szPlaceNameKor[_MAX_SIZE_OF_KOREASITENAME_];

    int iRadarModePriority;
    int iRadarPriority;

    int iPolarization;

#if defined(_POCKETSONATA_) || defined(_ELINT_)
    float fDOAMean;                                 // [0.1��]
    float fDOAMax;
    float fDOAMin;
    float fDOADeviation;				// [0.1��]
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
    float fTheta;									// [0.1��]
    float fDistanceErrorOfThreat;	// [m]

    int iValidity;

    unsigned int uiTotalOfPDW;

    int iRadarModeIndex;
    int iThreatIndex;

    int iIsManualInput;

    __time32_t tiFinalAlarmTime;

    int iStat;

    char aucRadarName[_MAX_RADARNAME_SIZE];

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


//////////////////////////////////////////////////////////////////////////
// ������ ���

/* �� ��������� ������Ʈ ������ �����ϰ� �Ʒ� �Լ��� ȣ���Ϸ��� �ϴ� �ҽ��� �Ʒ��� ���� include �Ѵ�.

#include "RadarAnlAlgorithm.h"

:
:

RadarAnlAlgotirhm::RadarAnlAlgotirhm::Init();

:
:

RadarAnlAlgotirhm::RadarAnlAlgotirhm::Close();

*/

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

		5. CED �� EOB ���̺귯���� ��������� ���� ������ CED/EOB�� �ε��ؾ� �Ѵٴ� �÷��׸� �������ִ� �Լ��̴�.
		   CED �� EOB ���̺귯���� ����� ��� ��� ����Ʈ����� ���̴� �м����� �˷��ְ� ���̴� �м������� �� �Լ��� ȣ���ؾ� �մϴ�.

		RadarAnlAlgotirhm::RadarAnlAlgotirhm::UpdateCEDEOBLibrary();						<---- CED/EOB ������Ʈ�� �˷��ش�.


		6. ��� �ʱ�ȭ ��� �ʱ�ȭ�ÿ� ���ü �� ��/LOB ��ȣ�� 1�� ���� ������ϸ� ���� ���� ���̺� �ʱ�ȭ�Ͽ� ó������ �м��� �����Ѵ�.
		RadarAnlAlgotirhm::RadarAnlAlgotirhm::SWInit();													<---- ��� �ʱ�ȭ�� �����Ѵ�.

*/

namespace RadarAnlAlgotirhm
{
	// This class is exported from the MathFuncsDll.dll
	class RadarAnlAlgotirhm
	{
	public: 
		static MATHFUNCSDLL_API void Init( HWND hWnd=0, bool bDBThread=true, bool bLocal=false );
		static MATHFUNCSDLL_API void Close();

		static MATHFUNCSDLL_API void Start( STR_LOBDATA *pLOBData );
		static MATHFUNCSDLL_API void SWInit();
		static MATHFUNCSDLL_API void UpdateCEDEOBLibrary();

		static MATHFUNCSDLL_API bool GetLOBData( STR_LOBDATA *pLOBData );
		static MATHFUNCSDLL_API bool GetABTData( STR_ABTDATA *pABTData );

#pragma data_seg( ".ioshare" )
        // static CLog *g_pTheLog;
#pragma data_seg()

	};
}



