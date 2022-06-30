// Identify.h: interface for the CELSignalIdentifyAlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDENTIFY_H__5E200D86_A36B_4CDA_98C5_5DB9FA9D1A97__INCLUDED_)
#define AFX_IDENTIFY_H__5E200D86_A36B_4CDA_98C5_5DB9FA9D1A97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define CEDEOBLIB

#include "define.h"
#include "structs.h"
#include "../SigAnal/_Macro.h"

#include "./ELUtil.h"

#include "../EmitterMerge/ELStringDefn.h"


#include "../EmitterMerge/PositionEstimationAlg.h"
#include "../EmitterMerge/ELGMIMsgDefn.h"
#include "../EmitterMerge/ELEmitterDataType.h"
#include "../EmitterMerge/ELPosEstDataType.h"
#include "../EmitterMerge/ELOperationCtrlDataType.h"
#include "../EmitterMerge/ElintTaskDataTypedb.h"
#include "../EmitterMerge/ElintRsltDataTypedb.h"
 
#include "../EmitterMerge/ELEnvironVariableMngr.h"

#include "../EmitterMerge/InverseMethod/CInverseMethod.h"

// #define FILTER_LONGLAT_RANGE					(3)								
// 
// #define M2NMM(A)				(int) ( ( A / 1.852 ) + 0.5 )
// #define M2NM(A)					(int) ( ( A / 1852. ) + 0.5 )
#define NM2M(A)					(int) ( ( A * 1852. ) + 0.5 )
#define NM2KM(A)				(int) ( ( A * 1.852 ) + 0.5 )
// 
// #define DISTANCE_KM__PER_ONE_MM_DEG_LONGITUDE			(88.0/1000.)
// #define DISTANCE_KM__PER_ONE_MM_DEG_LATITUDE			(114.64/1000.)
// 
// #define DISTANCE_PER_ONE_DEG_IN_LONGITUDE					(133.333)
// #define DISTANCE_PER_ONE_DEG_IN_LATITUDE					(111.322)
// 
// #define LIB_DEFAULT_GROUP							(1)
// 
// // EOB를 측정하기 위한 최대 허용 오차
// #define MAX_ALLOWABLE_EOB_DISTANCE		(10000)			// 단위 : m

// 주파수 형태에 따른 식별 방법
/// 
enum { FFixedFixed=1, FFixedHopping, FFixedPattern, FHoppingHopping, FPatternPattern, FAgilePattern, FAgileAgile, FIgnoreFreqType, EndOfIdentifyFrq } ;
 
 
// PRI 형태에 따른 식별 방법
// 
enum { PStableStable=1, PStableStagger, PStableDwell, PStablePStable, PStaggerStagger, PStaggerJitter, PStaggerPStagger, \
	PDwellDwell, PDwellPDwell, PJitterStagger, PJitterJitter, PJitterPattern, PPatternPattern, \
	PStablePStagger, PStablePDwell, FIgnorePRIType, EndOfIdentifyPri
};
// 
// _UNMATCHRATIO_ 는 일치율을 계산하지 않기 위한 값임.
enum EnumMATCHRATIO { 
	_UNMATCHRATIO_=0, 
	_SIG_TYPE_MATCHRATIO_=0x100, 

	_POL_TYPE_MATCHRATIO_, 

	_FREQ_TYPE_MATCHRATIO_, 
	_FREQ_RANGE_MATCHRATIO_,
	_FREQ_PERIOD_MATCHRATIO_,
	_FREQ_POSITION_MATCHRATIO_,
	_FREQ_MAIN_RANGE_MATCHRATIO_,

	_PRI_TYPE_MATCHRATIO_, 
	_PRI_RANGE_MATCHRATIO_,
	_PRI_PERIOD_MATCHRATIO_,
	_PRI_POSITION_MATCHRATIO_,
	_PRI_MAIN_RANGE_MATCHRATIO_,

	_PW_MATCHRATIO_,

    _SCANTYPE_MATCHRATIO_,
    _SCANPRD_MATCHRATIO_,
	//_MOP_MATCHRATIO_,

	_POSITION_MATCHRATIO_	 
} ;
// 
 /*!
  * @typedef		STR_H000
  * @brief			미식별 번호를 AET 번호와 테이블화해서 관리
  * @author    조철희
  * @date      2015-02-06 
  */
struct STR_H000 {
	int iAETID;
	int iABTID;
	int iH000;

}  ;

//#define MAX_RADARMODE			(1000)
//#define MAX_THREAT				(500)


#ifdef _SQLITE_
#include "../../SQLite/KompexSQLiteDatabase.h"
#include "../../SQLite/KompexSQLiteStatement.h"
#include "../../SQLite/KompexSQLiteException.h"
#include "../../SQLite/KompexSQLiteStreamRedirection.h"
#include "../../SQLite/KompexSQLiteBlob.h"

#elif _MSSQL_
#include "../../ODBC/mssql.h"
#include "../../ODBC/odbccore.h"

#else

#endif

#if defined(_ELINT_) || defined(_XBAND_)
#define FLIB_FREQ_RES_MHZ               (10)

#elif defined(_POCKETSONATA_)
#define FLIB_FREQ_RES_MHZ               (1)

#else

#endif


/**
* [식별자 : CLS-GMU-EL-L-SIM]
*
* [추적성 : SRS-G-SAFR-013]
*
* @class	CELSignalIdentifyAlg
* @brief	CED/EOB 신호 식별 클래스
*
* (1) 클래스 설명
* - 본 클래스는 LOB 및 빔 그리고 인터 신호 분석한 LOB 에 대해서 CED/EOB 신호 식별을 수행하는 클래스이다.
*
* (2) 설계결정사항
* - 해당사항 없음
*
* (3) 제한 및 예외처리
* - 해당사항 없음
*/
#ifdef _MSSQL_
class CELSignalIdentifyAlg : CMSSQL
#else
class CELSignalIdentifyAlg
#endif
{
 protected:
#ifdef _SQLITE_
    char m_szSQLString[MAX_SQL_SIZE];
    Kompex::SQLiteDatabase *m_pDatabase;

#elif _MSSQL_
     char m_szSQLString[MAX_SQL_SIZE];

#endif
    static bool m_bInitTable;												///< 식별 테이블 로딩하기 위한 플레그

    static STR_HOWTO_IDENTIFY m_HowToId[MAX_FRQTYPE][MAX_PRITYPE];		///< 식별 함수 테이블

    static unsigned char m_FrqIdCallFunc[MAX_FRQTYPE][MAX_FRQTYPE];		///< 주파수 식별 함수 테이블
    static unsigned char m_PriIdCallFunc[MAX_PRITYPE][MAX_PRITYPE];		///< PRI 식별 함수 테이블

    static bool m_bLoadedDB;												///< CED/EOB 테이블 로딩 여부 플레스

    static int m_CoInstance;												///< 인스턴스 생성 개수

    // 미식별 번호 관리
    static STR_FLIB *m_pFLib;											///< 주파수 테이블화 저장소, 기본형-0, 실무형-1

    //vector<STR_H000> m_vecH000;							                ///< 미식별 번호 관리하기 위한 테이블
    int m_iH000;													///< 미식별 번호

    //static SELDBEnvVarIdnf *m_pSELDBEnvVarIdnf;			///< 시스템 설정값 환경 포인터
    static SEnvironVariable *m_pSEnvironVariable;			///< 시스템 설정값 환경 포인터

    //static vector<SThreat> m_vecThreatData;			///< EOB 식별하기 위한 장비 목록 값

    int m_iRadar;
    int m_iRadarMode;
    static SRadarMode *m_pRadarMode;												///< 레이더 모드 구조체

    int m_iThreat;
    static SThreat *m_pThreat;															///< 위협 구조체

    STR_EOB_RESULT *m_pEOBResult;			///< EOB 식별 결과를 저장하기 위한 임시 저장소
    STR_LIB_IDRESULT *m_pIdResult;			///< CED 식별 결과를 저장하기 위한 임시 저장소
    STR_CEDEOB_RESULT *m_pCEDEOBResult;			///< CED/EOB 식별 결과

private:
    // EOB 식별 결과 저장소
    int m_nCoIdEOB;																	///< EOB 개수

    // CED 식별 결과 저장소
    int m_nCoIdResult;															///< CED 개수

    // CED/EOB 메칭 결과 저장소
    int m_nCoCEDEOB;																///< CED/EOB 메칭 갯수


    // 최종 CED/EOB 식별 결과
    STR_CEDEOB_FINAL_RESULT m_CEDEOBResult;					///< 최종 CED/EOB 식별 결과

    UINT m_fromLib;																	///< 식별시 시작 인덱스
    UINT m_toLib;																		///< 식별시 종료 인덱스

    CInverseMethod m_theInverseMethod;

 public:
    UINT m_total_ced;																///< CED의 레이더 모드 총 갯수
    UINT m_total_eob;																///< EOB의 위협 총 갯수

    SRxLOBData *m_pLOBData;

    void (CELSignalIdentifyAlg::*IdentifyFrq[EndOfIdentifyFrq])( SRxLOBData *pNewAet );
    void (CELSignalIdentifyAlg::*IdentifyPri[EndOfIdentifyPri])( SRxLOBData *pNewAet );

private:
    float CalcFreqMatchRatio(EnumMATCHRATIO enMatchRatio, SRadarMode *pRadarMode);
    float CalcPRIMatchRatio(EnumMATCHRATIO enMatchRatio, SRadarMode *pRadarMode);

 public:
    void Identify( SRxLOBData *pLOBData, SELLOBDATA_EXT *pThreatDataExt, SPosEstData *pstPosData, BOOL bMakeH0000 );
    void Identify( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, SELLOBDATA_EXT *pLOBDataExt, bool bIDExecute=true, bool bMakeH0000=true );

    // 식별 함수 정의
 	void PIdentifyPRI( SRxLOBData *pLOBData );
	void PIdentifyPatPat( SRxLOBData *pLOBData );
	void PIdentifyJitPat( SRxLOBData *pLOBData );
	void PIdentifyJitJit( SRxLOBData *pLOBData );
	void PIdentifyJitStg( SRxLOBData *pLOBData );
	void PIdentifyDwlDwl( SRxLOBData *pLOBData );
	void PIdentifyStgStg( SRxLOBData *pLOBData );
	void PIdentifyStgJit(SRxLOBData *pLOBData);
	void PIdentifyStbDwl( SRxLOBData *pLOBData );
	void PIdentifyStbStb( SRxLOBData *pLOBData );
    void FIdentifyAgiAgi( SRxLOBData *pLOBData );
	void FIdentifyAgiPat( SRxLOBData *pLOBData );
	void FIdentifyPatPat( SRxLOBData *pLOBData );
	// void ConvertToIdentifyAet( SRxLOBData *pLOBData );
	void FIdentifyHopHop( SRxLOBData *pLOBData );
	void FIdentifyFixPat( SRxLOBData *pLOBData );
	void FIdentifyFixHop( SRxLOBData *pLOBData );
 	void FIdentifyFixFix( SRxLOBData *pLOBData );  
 	void FIdentifyFreq( SRxLOBData *pLOBData );
 	BOOL IdentifyPatternRange( SRadarMode *pRadarMode );
 	void CallFreqFunc( unsigned char nCall, SRxLOBData *pLOBData ) { (this->*IdentifyFrq[nCall])( pLOBData ); }		//!< http://izeph.com/tt/blog/155 참조.
 	void CallPriFunc( unsigned char nCall, SRxLOBData *pLOBData ) { (this->*IdentifyPri[nCall])( pLOBData ); }
	
 	void IdentifySigType( int iSignalType );
 	void FilterBand( STR_LIB_RANGE *pFrqLow, STR_LIB_RANGE *pFrqHgh, STR_FLOWHIGH *pBand, UINT *cotoIpl );
 	void InitIdentifyTable();
 	void Init();
 	void CopyAmbiguity( I_AET_ANAL *pIAetAnal, I_AET_DATA *pIAetData, BOOL bMakeH0000 );
 	void IdentifyFreqPRI( SRxLOBData *pLOBData );
 	void SortThreatLevel();
 	void IdentifyPriority();
 	void IdentifyMatchRatio();
 	UINT ArrangeLib2( SRadarMode **inLib, UINT count, ENUM_AET_FRQ_TYPE enFrqType, STR_LIB_RANGE *pLibRange );
 	UINT BandSelect( int from, int to, int searchVal );
 	void MakeFreqLibTable();
 	void MakeFreqBand();
    void IdentifyScan();
    void IdentifyPW();

 	bool LoadCEDLibrary();
 	bool LoadEOBLibrary();
    void MakeRadarMode( vector<SRadarMode_Sequence_Values> *pVecRadarMode_PRISequence_Values, ENUM_Sequence enSeq );
    char *GetRadarModeName( int iRadarModeIndex );

	inline SThreat *GetThreatData( int iThreatIndex ) { return & m_pThreat[iThreatIndex-1]; }

 	void MallocBuffer();
 	void InitVar();
 	void Destory();
 	//BOOL CompSwitchLevel( int *series, vector <SRadarRF_Values> *pvecRadarRF_Values, SRadarRF_SequenceNumIndex *pRF_SequenceNumIndex, UINT coSeries );
 	BOOL CompSwitchLevel( float fVal, vector <SRadarRF_Values> *pvecRadarRF_Values, SRadarRF_SequenceNumIndex *pRF_SequenceNumIndex, UINT coSeries, SRadarMode *pRadarMode );
    BOOL CompSwitchLevel( float fVal, vector <SRadarMode_Sequence_Values> *pvecRadarPRI_Values, SRadarPRI_SequenceNumIndex *pPRI_SequenceNumIndex, UINT coSeries, SRadarMode *pRadarMode );
    BOOL CompSwitchLevel( float *series, int coSeries, vector <SRadarMode_Sequence_Values> *pvecRadarPRI_Values, SRadarPRI_SequenceNumIndex *pPRI_SequenceNumIndex, int coNumIndex );
    BOOL CompSwitchLevel( float *series, int coSeries, vector <SRadarMode_Sequence_Values> *pvecRadarPRI_Values );
 	//BOOL CompSwitchLevel( int *pSeries1, int *pSeries2, int coSeries, int margin );

	bool CheckThereFreqRange( vector<SRadarMode *> *pVecMatchRadarMode, UINT uiFreqMin, UINT uiFreqMax );

    char *GetFunctionCode( EnumFunctionCodes eFunctionCode );

	template <typename T>
	BOOL CompSwitchLevel( T *series, vector <SRadarRF_Values> *pvecRadarRF_Values, SRadarRF_SequenceNumIndex *pRF_SequenceNumIndex, UINT coSeries )
	{
		UINT i, j;
		UINT index;

		BOOL bRet=FALSE;
		SRadarRF_SequenceNumIndex *pTempRF_SequenceNumIndex;

		for( i=0 ; i < coSeries ; ++i ) {
			pTempRF_SequenceNumIndex = pRF_SequenceNumIndex;
			for( j=i ; j < coSeries+i ; ++j ) {
				SRadarRF_Values *pRadarRF_Values;

				pRadarRF_Values = & pvecRadarRF_Values->at( (UINT) pTempRF_SequenceNumIndex->nRF_Index - 1 );

				index = j % coSeries;

				bRet = CompMarginDiff22( series[index], pRadarRF_Values->fRF_Min, pRadarRF_Values->fRF_Max, (float) m_pSEnvironVariable->fMarginFrqError );
				if( FALSE == bRet ) {
					break;
				}

				++ pTempRF_SequenceNumIndex;

			}

			if( TRUE == bRet ) {
				// bRet = TRUE;
				break;
			}
		}

		return bRet;

	}

	template <typename T>
	BOOL CompSwitchLevel( T *pSeries1, T *pSeries2, int coSeries, T margin )
	{
		int i, j, k;
		int index1;

		T tDiff;
		T *pSeries;

		BOOL bRet=FALSE;

		if( coSeries != 0 ) {
			for( i=0 ; i < coSeries ; ++i ) {
				bRet = TRUE;
				tDiff = 0;
				for( j=i ; j < coSeries+i ; ++j ) {
					pSeries = pSeries2;
					for( k=j ; k < coSeries+j ; ++k ) {
						index1 = k % coSeries;
						bRet = CompMeanDiff<T>( pSeries1[index1], *pSeries, margin );
						if( FALSE == bRet ) {
							break;
						}
						tDiff += _diffabs( pSeries1[index1], *pSeries );
						++ pSeries;
					}
				}

				if( TRUE == bRet ) {
					break;
				}
			}
		}

		return bRet;

	}


 	int IdentifyPosition( SRxABTData *pABTData );
 
 	inline UINT GetCoIdCandi() { return m_toLib; }
 	//inline void ClearH000() { m_vecH000.clear(); }

    inline SRadarMode * GetRadarMode( int iRadarModeIndex ) { return iRadarModeIndex==0 ? NULL : & m_pRadarMode[iRadarModeIndex-1]; }
    inline SThreat * GetThreat( int iIndex ) { return iIndex==0 ? NULL : & m_pThreat[iIndex-1]; }

// 
// 	// CED 관련 함수
// 	char *GetElintNotation( int nRadarModeIndex, int iAETID, int iABTID, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL, bool bGround=false );									// ELINT Notation
// 	char * GetPlatformCode( int nRadarModeIndex, EnumLibType enLibType );
// 	char *GetModulationCode( int nRadarModeIndex, EnumLibType enLibType );
// 	char *GetNickName( int nThreatIndex, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL );
// 	void SortRadarModePriority( STR_CEDEOBID_INFO *pIDInfo, EnumLibType eLibType=E_EL_LIB_TYPE_NORMAL );
// 	int GetRadarPriority( int nRadarIndex, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL );									// 에미터의 우선 순위
// 
// 	// EOB 관련 함수
// 	char *GetPlatformName( int nThreatIndex, int nDeviceIndex, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL );										// 플레폼
// 	char *GetIdInfo( int nThreatIndex, int nDeviceIndex, EnumLibType enLibType );
    PlatformCode::EnumPlatformCode GetPlatformFromRadarMode( int iRadarModeIndex );
    char *GetPlatformCode(PlatformCode::EnumPlatformCode ePlatform);

 	time_t GetUnknownEmitterTime( int nRadarModeIndex );
// 	UINT Get2ndCandidate();
// 
// 	// EOB 관련 함수
// 	void GetEOBLatLong( int *pLatitude, int *pLongitude, int nThreatIndex, int nDeviceIndex, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL );
// 	float GetEOBFLongitude( int nThreatIndex, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL );
// 	float GetEOBFLatitude( int nThreatIndex, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL );
// 	UINT GetEOBPinNumber( int nThreatIndex, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL );
// 	int CalDistanceNM( int iLat1, int iLong1, int iLat2, int iLong2 );
// 	BOOL IsFindELNOTInThreat( CString *pStrELNOT, EnumLibType eEOBLibType );
// 
// 	void IdentifyCEDEOB( EnumLibType eCEDLibType, EnumLibType eEOBLibType );
// 	BOOL CELSignalIdentifyAlg::FindEOB( int nThreatIndex, int nDeviceIndex );
// 	bool GetRadarModeASameELNOTInEOBResult( STR_CEDEOBID_INFO *pIDInfo, SELABTDATA_EXT *pABTExtData, char *pszELNOT, EnumLibType eEOBLibType );
 	bool IsSortELNOT( SRadarMode* pRadarModeRef, SRadarMode *pRadarModeNxt );
// 
// 	SOCSystemVariable *GetSystemVar( int nLinkNum );
// 
// 	SRadarMode *GetRadarModeData( int nRadarModeIndex, EnumLibType enLibType );
// 
// 	void SortRadarIndex( int *pCount, int *pIndex, int nMax=100 );
// 	void RemoveDuplicateIndex( int *pCount, int *pIndex, int nMax );

#if defined(_SQLITE_)
    CELSignalIdentifyAlg( const char *pFileName );
#elif _MSSQL_
    CELSignalIdentifyAlg( CODBCDatabase *pODBCDataBase );
#else
    CELSignalIdentifyAlg( const char *pFileName );
#endif

    // CELSignalIdentifyAlg();
	virtual ~CELSignalIdentifyAlg();

protected:
	void CalcMatchRatio();
 	float CalcMatchRatio( EnumMATCHRATIO enMatchRatio, SRadarMode *pRadarMode=NULL );

    float CalcFreqTypeMatchRatio(SRadarMode *pRadarMode);
    float CalcPRITypeMatchRatio(SRadarMode *pRadarMode);

	BOOL CheckFreqType(ENUM_AET_FRQ_TYPE enFrqType, SRadarMode *pRadarMode );

	void InitRadarModeData();

    bool LoadRadarModeData( int *pnRadarMode, SRadarMode *pRadarMode, int iMaxItems );
    bool LoadRadarMode_RFSequence( vector<SRadarMode_Sequence_Values> *pVecRadarMode_RFSequence, int nMaxRadarMode );
    bool LoadRadarMode_PRISequence( vector<SRadarMode_Sequence_Values> *pVecRadarMode_PRISequence, int nMaxRadarMode );
    bool LoadThreatData( int *pnThreat, SThreat *pThreat, int iMaxItems );

    // 변환 코드
    EnumFunctionCodes GetFunctionCodes( char *pData );
    SignalType::EnumSignalType GetSignalType( char *pData );
    PolizationCode::EnumPolizationCode GetPolarizationCodes( int iPolization );
    PlatformCode::EnumPlatformCode GetPlatformCode( int iPlatform );
    PatternCode::EnumPatternCode GetPatternCode( int iPattern );
    RadarModeFreqType::EnumRadarModeFreqType GetFreqType( int iFreqType );
    RadarModePRIType::EnumRadarModePRIType GetPRIType( int iPRIType );
    ScanType::EnumScanType GetScanType( int iScanType );
    EnumValidationCode GetValidationCode( int iValidation );


};

#endif // !defined(AFX_IDENTIFY_H__5E200D86_A36B_4CDA_98C5_5DB9FA9D1A97__INCLUDED_)
