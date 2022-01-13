#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport)

#else
#define MATHFUNCSDLL_API __declspec(dllimport)
#endif


#define WM_USER_LOGMSG				(7011)



//
// RADARDIR ������Ʈ ������ �ּ� ���븸 ����ü ���Ǹ� ������ ����.


#define LENGTH_OF_TASK_ID			(19+1)		//����ID ���ڿ� ���� (TBD)

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


#ifndef SRxLOBData_STRUCT
#define SRxLOBData_STRUCT
struct SRxLOBData {
    unsigned int uiLOBID;
    unsigned int uiABTID;
    unsigned int uiAETID;

    __time32_t tiContactTime;			// 32��Ʈ time_t �� �����ؾ� ��.
    unsigned int tiContactTimems;

    char szPrimaryELNOT[_MAX_ELNOT_STRING_SIZE_];
    char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1��° ELNOT

    char szSecondaryELNOT[_MAX_ELNOT_STRING_SIZE_];
    char szSecondaryModeCode[_MAX_SIZE_OF_MODECODE];							// 2��° ELNOT

    char szTertiaryELNOT[_MAX_ELNOT_STRING_SIZE_];												// 3��° ELNOT
    char szTertiaryModeCode[_MAX_SIZE_OF_MODECODE];

    char szModulationCode[_MAX_MODECODE_STRING_SIZE_];
    char szRadarModeName[_MAX_RADARMODE_NAME_SIZE];
    char szFuncCode[_MAX_FUNCTIONCODE_STRING_SIZE_];
    char szNickName[_MAX_NICKNAME_STRING_SIZE_];

#ifndef _XBAND_
    int iPolarization;                              // �ؼ�
    int iRatioOfPOL;                                // �ؼ� �ŷڵ�

#endif

    int iSignalType;

    float fDOAMean;                                 // [0.1��]
    float fDOAMax;
    float fDOAMin;
    float fDOADeviation;							// [0.1��]
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
    float fFreqSeq[MAX_FREQ_PRI_STEP];	// ���ļ� �ܰ�

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

    float fPAMean;				// �������
    float fPAMax;
    float fPAMin;
    float fPADeviation;			// �������

#ifndef _XBAND_
    int iScanType;
    //int iDetailScanType;
    float fScanPeriod;			// [msec]

    int iMOPType;				// ��Ʈ�� Ÿ��
    int iDetailMOPType;			// ��Ʈ�� ���� Ÿ��. �װ����� �� �� �ִ°�����(?)
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
// ������ ���

/* �� ��������� ������Ʈ ������ �����ϰ� �Ʒ� �Լ��� ȣ���Ϸ��� �ϴ� �ҽ��� �Ʒ��� ���� include �Ѵ�.

#include "RadarDirAlgorithm.h"

:
:

RadarDirAlgotirhm::RadarDirAlgotirhm::Init();

:
:

RadarDirAlgotirhm::RadarDirAlgotirhm::Close();

*/

//////////////////////////////////////////////////////////////////////////
// ���� ���

/* 1. ���۽� �ѹ��� ȣ���ϸ� �˴ϴ�.
	 ���� ���α׷����� �ʱ�ȭ�ÿ� �Ʒ� ��ƾ�� �ѹ� ȣ���ϸ� �˴ϴ�.
   RadarDirAlgotirhm::RadarDirAlgotirhm::Init();

	 2. ���α׷� ����� �ѹ��� ȣ���ϸ� �˴ϴ�.
	 RadarDirAlgotirhm::RadarDirAlgotirhm::Close();


	 3. ��ȣ �м��� PDWDATA ������ �Ʒ��� ���� �����Ͱ� �־�� �մϴ�.

typedef struct {
	char aucTaskID[LENGTH_OF_TASK_ID];			<---- ���� ����
	unsigned int iIsStorePDW;								<---- ���� ����. �ϴ� �׻� 1�� ��.
	int iCollectorID;												<---- ������ ��ġ. �ҹ�� �мҴ� 1, ���� ���żҴ� 2, �ź� ���̴�#1/�ź� ���̴�#2 �� 3/4 �� �Ҵ�
	ENUM_BANDWIDTH enBandWidth;							<---- ������ PDW�� �������� ���� �뿪���� ����

	UINT count;															<---- PDW ���� ����
	_PDW stPDW[_MAX_PDW];										<---- PDW ������

} STR_PDWDATA ;

RadarDirAlgotirhm::RadarDirAlgotirhm::Start( & stPDWData );

		4. �м� ����� �Ʒ� �Լ��� ȣ���Ͽ� LOB ������ �����͸� ��´�.
		
		int nCoLOB=RadarDirAlgotirhm::RadarDirAlgotirhm::GetCoLOB();							<-- LOB ����
		SRxLOBData *pLOBData=RadarDirAlgotirhm::RadarDirAlgotirhm::GetLOBData();	<--- LOB ������

		pLOBData[0] �� ù��° LOB ������, pLOBData[1] �� �ι�° LOB ������ ������ ����ϸ� �˴ϴ�. 

		*���� ���� : PDWDATA ����ü�� ���� ������ ���ų� PDW ���������� 4096 �� �ʰ��Ǹ� Start()���� �ٷ� �����Ѵ�. LOB ������ 0 ���� �����Ѵ�.

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



