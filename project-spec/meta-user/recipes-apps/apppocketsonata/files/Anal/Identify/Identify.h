/**

    @file      Identify.h
    @brief     신호 식별 헤더 파일 입니다.
    @details   ~
    @author    조철희
    @date      13.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

#include "define.h"
#include "structs.h"
#include "../SigAnal/_Macro.h"

#include "./ELUtil.h"

#include "../EmitterMerge/ELStringDefn.h"


#include "../EmitterMerge/PositionEstimationAlg.h"
#include "../EmitterMerge/ELGMIMsgDefn.h"
#include "../EmitterMerge/ELEmitterDataType.h"
#include "../EmitterMerge/ELPosEstDataType.h"
//#include "../EmitterMerge/ELOperationCtrlDataType.h"
#include "../EmitterMerge/ElintTaskDataTypedb.h"
#include "../EmitterMerge/ElintRsltDataTypedb.h"

#include "../EmitterMerge/ELEnvironVariableMngr.h"

#include "../EmitterMerge/InverseMethod/CInverseMethod.h"


#include "../../Utils/clock.h"

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

/**
    @enum  ENUM_FREQTYPE_IDTABLE
    @brief 주파수 형태에 따른 식별 방법
**/
enum ENUM_FREQTYPE_IDTABLE { FFixedFixed=1, FFixedHopping, FFixedPattern, FHoppingHopping, FPatternPattern, FAgilePattern, FAgileAgile, FIgnoreFreqType, EndOfIdentifyFrq } ; //!<

/**
    @enum  ENUM_PRITYPE_IDTABLE
    @brief PRI 형태에 따른 식별 방법
**/
enum ENUM_PRITYPE_IDTABLE  { PStableStable=1, PStableStagger, PStableDwell, PStablePStable, PStaggerStagger, PStaggerJitter, PStaggerPStagger, \
	PDwellDwell, PDwellPDwell, PJitterStagger, PJitterJitter, PJitterPattern, PPatternPattern, \
	PStablePStagger, PStablePDwell, FIgnorePRIType, EndOfIdentifyPri };

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

#include "../../Utils/clog.h"
//#include "../../Utils/clogname.h"

#if defined(_POCKETSONATA_) || defined(_712_)
#define FLIB_FREQ_RES_MHZ               (1)

#else
//#if defined(_ELINT_) || defined(_XBAND_) || defined(_701_)
#define FLIB_FREQ_RES_MHZ               (10)

#endif

struct STR_HOPPINGDWELL_INDEX {
    unsigned char index[MAX_FREQ_PRI_STEP];

};

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
class CELSignalIdentifyAlg : public CLogName
#endif
{
 protected:
#ifdef _SQLITE_
    char m_szSQLString[MAX_SQL_SIZE];
    wchar_t m_szSQLString16[MAX_SQL_SIZE];

    static Kompex::CSQLiteDatabase *m_pDatabase;

#elif _MSSQL_
    char m_szSQLString[MAX_SQL_SIZE];

#endif

    static CLock m_cs;

    static bool m_bInitTable;											///< 식별 테이블 로딩하기 위한 플레그

    static STR_HOWTO_IDENTIFY m_HowToId[(int)ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE][( int ) ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE];		///< 식별 함수 테이블

    static unsigned char m_FrqIdCallFunc[( int ) ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE][( int ) ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE];		///< 주파수 식별 함수 테이블
    static unsigned char m_PriIdCallFunc[( int ) ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE][( int ) ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE];		///< PRI 식별 함수 테이블

    static bool m_bLoadedDB;											///< CED/EOB 테이블 로딩 여부 플레스

    static int m_CoInstance;											///< 인스턴스 생성 개수

    // 미식별 번호 관리
    static STR_FLIB *m_pFLib;											///< 주파수 테이블화 저장소, 기본형-0, 실무형-1

    static unsigned int m_uiRadar;
    static unsigned int m_uiRadarMode;
    static unsigned int m_uiThreat;

    static SEnvironVariable *m_pSEnvironVariable;			            ///< 시스템 설정값 환경 포인터

    static std::vector<SRadarMode> m_vecRadarMode;						///< 레이더 모드 구조체

    static std::vector<SThreat> m_vecThreat;			                ///< EOB 식별하기 위한 장비 목록 값

    int m_iH000;													    ///< 미식별 번호

    STR_EOB_RESULT *m_pEOBResult;			                            ///< EOB 식별 결과를 저장하기 위한 임시 저장소

    STR_LIB_IDRESULT *m_pIdResult;			                                        ///< CED 식별 결과를 저장하기 위한 임시 저장소
    //vector< STR_LIB_IDRESULT> m_vecIdResult;

    STR_CEDEOB_RESULT *m_pCEDEOBResult;			                                   ///< CED/EOB 식별 결과

    vector<STR_HOPPINGDWELL_INDEX> m_vecMatchIndex;

private:
    // EOB 식별 결과 저장소
    int m_nCoIdEOB;																	///< EOB 개수

    // CED 식별 결과 저장소
    int m_nCoIdResult;															    ///< CED 개수

    // CED/EOB 메칭 결과 저장소
    int m_nCoCEDEOB;																///< CED/EOB 메칭 갯수

    // 최종 CED/EOB 식별 결과
    STR_CEDEOB_FINAL_RESULT m_CEDEOBResult;					                        ///< 최종 CED/EOB 식별 결과

    UINT m_fromLib;																	///< 식별시 시작 인덱스
    UINT m_toLib;																	///< 식별시 종료 인덱스

    CInverseMethod m_theInverseMethod;

    SRxLOBData *m_pLOBData;
    SRxABTData *m_pABTData;

    STR_IDENTIFY *m_pstIdentify;                                                    ///< 식별 데이터 결과

    SELABTDATA_EXT *m_pABTDataExt;                                                  ///< LOB 데이터 확장

 public:
    UINT m_total_ced;																///< CED의 레이더 모드 총 갯수
    UINT m_total_eob;																///< EOB의 위협 총 갯수

    void (CELSignalIdentifyAlg::*IdentifyFrq[EndOfIdentifyFrq])( void *pLOBData, bool bLOB );
    void (CELSignalIdentifyAlg::*IdentifyPri[EndOfIdentifyPri])( void *pLOBData, bool bLOB );


private:
    float CalcFreqMatchRatio(EnumMATCHRATIO enMatchRatio, SRadarMode *pRadarMode);
    float CalcPRIMatchRatio(EnumMATCHRATIO enMatchRatio, SRadarMode *pRadarMode);

    inline SRadarMode *GetRadarMode( unsigned int uiRadarModeIndex ) { return uiRadarModeIndex == 0 ? NULL : & m_vecRadarMode[uiRadarModeIndex - 1]; }
    inline SThreat *GetThreat( unsigned int uiIndex ) { return uiIndex == 0 ? NULL : &m_vecThreat[uiIndex - 1]; }


 public:
     bool LoadRadarModeData( unsigned int *pnRadarMode );

    void IdentifyLOB( STR_IDENTIFY *pstIdentify, SRxLOBData *pLOBData );
    void IdentifyABT( STR_IDENTIFY *pstABTIdentify, SRxABTData *pABTData, STR_IDENTIFY *pstLOBIdentify );

    // 식별 함수 정의
 	void PIdentifyPRI(void *pData, bool bLOB);
	void PIdentifyPatPat(void *pData, bool bLOB);
	void PIdentifyJitPat(void *pData, bool bLOB);
	void PIdentifyJitJit(void *pData, bool bLOB);
	void PIdentifyJitStg(void *pData, bool bLOB);
	void PIdentifyDwlDwl(void *pData, bool bLOB);
	void PIdentifyStgStg(void *pData, bool bLOB);
	void PIdentifyStgJit(void *pData, bool bLOB);
	void PIdentifyStbDwl(void *pData, bool bLOB);
	void PIdentifyStbStb(void *pData, bool bLOB);
    void FIdentifyAgiAgi(void *pData, bool bLOB);
	void FIdentifyAgiPat(void *pData, bool bLOB);
	void FIdentifyPatPat(void *pData, bool bLOB);
	// void ConvertToIdentifyAet( SRxLOBData *pLOBData );
	void FIdentifyHopHop(void *pData, bool bLOB);
	//void FIdentifyFixPat(void *pData, bool bLOB );
	void FIdentifyFixHop(void *pData, bool bLOB );
 	void FIdentifyFixFix( void *pData, bool bLOB );
 	void FIdentifyFreq(void *pData, bool bLOB);
 	bool IdentifyPRI_PatternRange( SRadarMode *pRadarMode, SRxLOBData *pLOBData );
    bool IdentifyPRI_PatternRange( SRadarMode *pRadarMode, SRxABTData *pABTData );
    bool IdentifyRF_PatternRange( SRadarMode *pRadarMode, SRxLOBData *pLOBData );
    bool IdentifyRF_PatternRange( SRadarMode *pRadarMode, SRxABTData *pABTData );
 	void CallFreqFunc( unsigned char nCall, SRxLOBData *pLOBData ) { (this->*IdentifyFrq[nCall])( pLOBData, true ); }		//!< http://izeph.com/tt/blog/155 참조.
 	void CallPriFunc( unsigned char nCall, SRxLOBData *pLOBData ) { (this->*IdentifyPri[nCall])( pLOBData, true); }

	void CallFreqFunc(unsigned char nCall, SRxABTData *pABTData) { (this->*IdentifyFrq[nCall])(pABTData, false); }		//!< http://izeph.com/tt/blog/155 참조.
	void CallPriFunc(unsigned char nCall, SRxABTData *pABTData) { (this->*IdentifyPri[nCall])(pABTData, false); }

 	void IdentifySigType( int iSignalType );
    void IdentifyMOPType( ENUM_MOP_TYPE enMOPType );
 	void FilterBand( STR_LIB_RANGE *pFrqLow, STR_LIB_RANGE *pFrqHgh, STR_FLOWHIGH *pBand, UINT *cotoIpl );
 	void InitIdentifyTable();
	void InitFixedFreqIdentifyTable();
	void InitRandomAgileFreqIdentifyTable();
	void InitHopingFreqIdentifyTable();
	void InitPatternAgileFreqIdentifyTable();
	void InitIgnoreFreqIdentifyTable();


 	void Init();
 	//void CopyAmbiguity( SRxABTData *pABTData );
 	void IdentifyFreqPRI( SRxLOBData *pLOBData );
	void IdentifyFreqPRI( SRxABTData *pABTData );

 	void SortThreatLevel();
 	void IdentifyPriority();
 	void IdentifyMatchRatio();
 	UINT ArrangeLib2( SRadarMode **inLib, UINT count, ENUM_AET_FRQ_TYPE enFrqType, STR_LIB_RANGE *pLibRange );
 	UINT BandSelect( int from, int to, int searchVal );
 	void MakeFreqLibTable();
 	void MakeFreqBand();
    void IdentifyScan( ENUM_AET_SCAN_TYPE enScanType, float fScanPeriod, float fThreshold );
    void IdentifyPW( float fPWMin, float fPWMax );

    // EOB 데이터 로딩 관련 함수
    bool LoadEOBLibrary();
    void InitDeviceData();
    bool LoadDeviceData( unsigned int *pnThreat );

    // CED 데이터 로딩 관련 함수
 	bool LoadCEDLibrary();
    void MakeRadarMode(vector<SRadarMode_Spot_Values> *pVecRadarMode_Spot_Values, ENUM_SequenceSpot enSeqSpot);
    void MakeRadarMode( vector<SRadarMode_Sequence_Values> *pVecRadarMode_PRISequence_Values, ENUM_SequenceSpot enSeqSpot);

    char *GetRadarModeName( unsigned int uiRadarModeIndex );

	inline SThreat *GetThreatData( unsigned int uiThreatIndex ) { return &m_vecThreat[uiThreatIndex -1]; }

 	void MallocBuffer();
	void MallocStaticBuffer();
 	void InitVar();
 	void Destory();
 	bool CompSwitchLevel( float fVal, vector <SRadarRF_Values> *pvecRadarRF_Values, SRadarRF_SequenceNumIndex *pRF_SequenceNumIndex, UINT coSeries, SRadarMode *pRadarMode );
    bool CompSwitchLevel( float fVal, vector <SRadarMode_Sequence_Values> *pvecRadarPRI_Values, SRadarPRI_SequenceNumIndex *pPRI_SequenceNumIndex, UINT coSeries, SRadarMode *pRadarMode );
    bool CompSwitchLevel( float *series, unsigned int uiCoSeries, vector <SRadarMode_Sequence_Values> *pvecRadarPRI_Values, SRadarPRI_SequenceNumIndex *pPRI_SequenceNumIndex, int coNumIndex );
    bool CompSwitchLevel( float *series, unsigned int uiCoSeries, vector <SRadarMode_Sequence_Values> *pvecRadarPRI_Values, float fMarginError, unsigned char *pidxHopping );
    bool CompSwitchLevel( float *series, unsigned int uiCoSeries, vector <SRadarMode_Sequence_Values> *pvecRadarPRI_Values, unsigned int uiSizeOfRadarMode_Sequence, float fMarginError, unsigned char *pidxHopping );
    bool CompSwitchLevel( float fVal, vector <SRadarMode_Sequence_Values> *pvecRadar_Values, float fMarginFrqError, unsigned char *pidxHopping );

    bool CompHoppingDwellLevel( float *series, unsigned int uiCoSeries, vector <SRadarMode_Sequence_Values> *pvecRadarRF_Values, float fMarginError, unsigned char *pidxHopping=NULL );
	bool CheckThereFreqRange( vector<SRadarMode *> *pVecMatchRadarMode, UINT uiFreqMin, UINT uiFreqMax );

    char *GetFunctionCode( EnumFunctionCodes eFunctionCode );

    SRadarMode *IGetRadarMode( unsigned int uiRadarModeIndex, bool bMaster=true );
    SThreat *IGetThreat( unsigned int uiIndex, bool bMaster=true );

    template <typename T>
    void Identify( T *pData, bool bIdentifyScan=true )
    {
        if( pData != NULL ) {
            // 3. 위협 데이터의 신호 식별
            IdentifyFreqPRI( pData );

            // 5. 펄스폭 식별
            IdentifyPW( pData->fPWMin, pData->fPWMax );

            // 6. 스캔 식별
            if( bIdentifyScan == true ) {
#if defined(_POCKETSONATA_) || defined(_712_)
                IdentifyScan( pData->vScanType, FMUL(pData->fMeanScanPeriod, 1000) , FMUL( pData->fPRIMean, (float) 2. ) );
#else
                IdentifyScan( pData->iScanType, pData->fMeanScanPeriod, FDIV( pData->fPRIMean * ( float ) 2., 1000. ) );
#endif
            }

            // 8. 일치율 식별
            IdentifyMatchRatio();

            // 9. 후보를 정렬한다.
            SortThreatLevel();
        }

    }

    template <typename T>
    void CopyAmbiguity( T *pData )
    {
        STR_CEDEOBID_INFO *pCEDEOBInfo;

        pCEDEOBInfo = & m_pstIdentify->idInfo;

        memset( pCEDEOBInfo, _spZero, sizeof( struct STR_CEDEOBID_INFO ) );
        pCEDEOBInfo->eIdResult = E_EL_PE_UNK_ID;

        //pIAetAnal->bCompFreq = true;
        //pIAetAnal->bCompPRI = true;

        // 2. 식별 정보 저장
        // 식별이 안 되었을 때, 아래 사항을 처리
        if( m_toLib == _spZero ) {
            //pLOBDataIdInfo->eIdResult = E_EL_UNK_ID;

            //pIAetAnal->chELNOT[0] = 0;
            //pIAet->stAet.usThreatId = pIAet->stAet.usEmitterId = pIAet->stAet.usBeamId = 0;
            //pIAetData->usThreatId = 0;
            //pIAetData->usEmitterId = 0;
            //pIAetData->usBeamId = 0;

            // 식별 후보 초기화
            m_nCoIdResult = 0;
            //pIAetAnal->usCoCandidate = 0;

            m_pstIdentify->bOverCount = false;

            pCEDEOBInfo->nThreatIndex = m_pEOBResult->nThreatIndex;
            pCEDEOBInfo->nDeviceIndex = m_pEOBResult->nDeviceIndex;

            //memset( & pIAetAnal->iIdRatio[0], _spZero, sizeof( pIAetAnal->iIdRatio ) );

            //m_IdAet.ext.id.usCoCandidate = 0;

            // 위협 레벨 초기화
            //pIAetAnal->usPriorityLevel = 0;

        }
        else {
            int i, j, k;
            SRadarMode *pRadarMode, *pRadarModeLevel;

            unsigned int uiRadarModeIndex;
            //unsigned int *p3LevelRadarModeIndex;
            //STR_CEDEOB_RESULT *pCEDEOBResult;

            m_pstIdentify->bOverCount = ( m_toLib > MAX_IDCANDIDATE );
            /*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2014-01-24 17:08:42
            */
            //pIAetAnal->usCoCandidate = (int) min( m_toLib, MAX_IDCANDIDATE );
            m_nCoIdResult = min( (int) m_toLib, MAX_IDCANDIDATE );

            //m_IdAet.ext.id.usCoCandidate = pIAetAnal->usCoCandidate;
            pCEDEOBInfo->uiCoRadarModeIndex = ( unsigned int ) m_nCoIdResult;

            for( i = 0; i < m_nCoIdResult; ++i ) {
                pCEDEOBInfo->uiRadarModeIndex[i] = m_pIdResult[i].pIdxRadarMode->uiRadarModeIndex;
            }

            // 3순위 식별 후보 선정 합니다.
            k = 1;
            memset( pCEDEOBInfo->ui3LevelRadarModeIndex, 0, sizeof( pCEDEOBInfo->ui3LevelRadarModeIndex ) );
            pCEDEOBInfo->ui3LevelRadarModeIndex[0] = pCEDEOBInfo->uiRadarModeIndex[0];
            for( i = 1; i < m_nCoIdResult && k < THREE_LEVEL_IDCANDIDATE; ++i ) {
                uiRadarModeIndex = pCEDEOBInfo->uiRadarModeIndex[i];

                pRadarMode = GetRadarMode( uiRadarModeIndex );

                for( j = 0; j < THREE_LEVEL_IDCANDIDATE; ++j ) {
                    pRadarModeLevel = GetRadarMode( pCEDEOBInfo->ui3LevelRadarModeIndex[j] );
                    if( pRadarModeLevel != NULL ) {
                        if( pRadarModeLevel->uiRadarIndex != pRadarMode->uiRadarIndex ) {
                            pCEDEOBInfo->ui3LevelRadarModeIndex[k] = uiRadarModeIndex;
                            ++ k;
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
            }

            // 위협 관리를 하기위한 식별 정보를 추가 저장하도록함.
            //pIAetAnal->usEnemyIdentify = false;

            // 위협 ID
            //pIAetAnal->usNoThreat = 0;

            // 호핑 레벨 인덱스 생성
            MakeHoppingLevelIndex<T>( pData );

            // 드웰 레벨 인덱스 생성
            MakeDwellLevelIndex<T>( pData );
        }

    }

    template <typename T>
    void MakeHoppingLevelIndex( T *pData )
    {
        SRadarMode *pRadarMode;

        if( m_toLib != _spZero ) {
            pRadarMode = m_pIdResult[0].pIdxRadarMode;

            if( pData->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED ) {
                //TODO: 32비트 Alignment 하기 위해서 temp 변수로 복사하여 콜한다.
                //date 	2023-08-11 19:08:58
#ifdef __VXWORKS__
                float fVal = pData->fFreqMean;
                CompHoppingDwellLevel( & fVal, _spOne, & pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError, m_pstIdentify->idxHopping );
#else
                CompHoppingDwellLevel( & pData->fFreqMean, _spOne, & pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError, m_pstIdentify->idxHopping );
#endif

            }

            else if( pData->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING ) {
                unsigned int i;
                unsigned char iMinValue, iIdxMin;

                float fSeq[MAX_FREQ_PRI_STEP];
                unsigned char idxHoppingDwell[MAX_FREQ_PRI_STEP];

                memcpy( fSeq, pData->fFreqSeq, sizeof( float ) * MAX_FREQ_PRI_STEP );

                if( true == CompHoppingDwellLevel( fSeq, ( unsigned int ) pData->vFreqPositionCount, & pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError, m_pstIdentify->idxHopping ) ) {
                    iMinValue = UINT8_MAX;
                    iIdxMin = 0;
                    for( i = 0; i < (unsigned int) pData->vFreqPositionCount; ++i ) {
                        if( m_pstIdentify->idxHopping[i] < iMinValue ) {
                            iMinValue = m_pstIdentify->idxHopping[i];
                            iIdxMin = i;
                        }
                    }

                    memset( fSeq, 0, sizeof( fSeq ) );
                    memset( idxHoppingDwell, 0, sizeof( idxHoppingDwell ) );
                    for( i = 0; i < ( unsigned int ) pData->vFreqPositionCount; ++i ) {
                        fSeq[i] = pData->fFreqSeq[(i+iIdxMin) % pData->vFreqPositionCount];
                        idxHoppingDwell[i] = m_pstIdentify->idxHopping[( i + iIdxMin ) % pData->vFreqPositionCount];
                    }
                    memcpy( pData->fFreqSeq, fSeq, sizeof( float ) * pData->vFreqPositionCount );
                    memcpy( m_pstIdentify->idxHopping, idxHoppingDwell, sizeof( char ) * pData->vFreqPositionCount );
                    //qsort( m_pstIdentify->idxHopping, ( size_t ) pData->vFreqPositionCount, sizeof( unsigned char ), incIndexCompare );
                }

            }

            else {

            }

        }

    }

    template <typename T>
    void MakeDwellLevelIndex( T *pData )
    {
        SRadarMode *pRadarMode;

        if( m_toLib != _spZero ) {
            pRadarMode = m_pIdResult[0].pIdxRadarMode;

            if( pData->vPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED ) {
                //TODO: 32비트 Alignment 하기 위해서 temp 변수로 복사하여 콜한다.
                //date 	2023-08-11 19:08:58
#ifdef __VXWORKS__
                float fVal = pData->fPRIMean;
                CompHoppingDwellLevel( & fVal, _spOne, & pRadarMode->vecRadarMode_PRISequenceValues, m_pSEnvironVariable->fMarginPriError, m_pstIdentify->idxDwell );
#else
                CompHoppingDwellLevel( & pData->fPRIMean, _spOne, & pRadarMode->vecRadarMode_PRISequenceValues, m_pSEnvironVariable->fMarginPriError, m_pstIdentify->idxDwell );
#endif

            }

            else if( pData->vPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH ) {
                unsigned int i;
                unsigned char iMinValue, iIdxMin;

                float fSeq[MAX_FREQ_PRI_STEP];
                unsigned char idxHoppingDwell[MAX_FREQ_PRI_STEP];

                memcpy( fSeq, pData->fFreqSeq, sizeof( float ) * MAX_FREQ_PRI_STEP );
                if( true == CompHoppingDwellLevel( fSeq, ( unsigned int ) pData->vPRIPositionCount, & pRadarMode->vecRadarMode_PRISequenceValues, m_pSEnvironVariable->fMarginPriError, m_pstIdentify->idxDwell ) ) {
                    iMinValue = UINT8_MAX;
                    iIdxMin = 0;
                    for( i = 0; i < ( unsigned int ) pData->vPRIPositionCount; ++i ) {
                        if( m_pstIdentify->idxDwell[i] < iMinValue ) {
                            iMinValue = m_pstIdentify->idxDwell[i];
                            iIdxMin = i;
                        }
                    }

                    memset( fSeq, 0, sizeof( fSeq ) );
                    memset( idxHoppingDwell, 0, sizeof( idxHoppingDwell ) );
                    for( i = 0; i < ( unsigned int ) pData->vPRIPositionCount; ++i ) {
                        fSeq[i] = pData->fPRISeq[( i + iIdxMin ) % pData->vPRIPositionCount];
                        idxHoppingDwell[i] = m_pstIdentify->idxDwell[( i + iIdxMin ) % pData->vPRIPositionCount];
                    }
                    memcpy( pData->fPRISeq, fSeq, sizeof( float ) * pData->vPRIPositionCount );
                    memcpy( m_pstIdentify->idxDwell, idxHoppingDwell, sizeof( char ) * pData->vPRIPositionCount );
                    //qsort( m_pstIdentify->idxHopping, ( size_t ) pData->vFreqPositionCount, sizeof( unsigned char ), incIndexCompare );
                }

            }

            else {

            }

        }

    }

	template <typename T>
	bool TCompSwitchLevel( T *series, vector <SRadarRF_Values> *pvecRadarRF_Values, SRadarRF_SequenceNumIndex *pRF_SequenceNumIndex, UINT coSeries )
	{
		UINT i, j;
		UINT index;

		bool bRet=false;
		SRadarRF_SequenceNumIndex *pTempRF_SequenceNumIndex;

		for( i=0 ; i < coSeries ; ++i ) {
			pTempRF_SequenceNumIndex = pRF_SequenceNumIndex;
			for( j=i ; j < coSeries+i ; ++j ) {
				SRadarRF_Values *pRadarRF_Values;

				pRadarRF_Values = & pvecRadarRF_Values->at( (UINT) pTempRF_SequenceNumIndex->nRF_Index - 1 );

				index = j % coSeries;

				bRet = CompMarginDiff22( series[index], pRadarRF_Values->fRF_Min, pRadarRF_Values->fRF_Max, (float) m_pSEnvironVariable->fMarginFrqError );
				if( false == bRet ) {
					break;
				}

				++ pTempRF_SequenceNumIndex;

			}

			if( true == bRet ) {
				// bRet = true;
				break;
			}
		}

		return bRet;

	}

	template <typename T>
	bool TCompSwitchLevel( T *pSeries1, T *pSeries2, int coSeries, T margin )
	{
		int i, j, k;
		int index1;

		T tDiff;
		T *pSeries;

		bool bRet=false;

		if( coSeries != 0 ) {
			for( i=0 ; i < coSeries ; ++i ) {
				bRet = true;
				tDiff = 0;
				for( j=i ; j < coSeries+i ; ++j ) {
					pSeries = pSeries2;
					for( k=j ; k < coSeries+j ; ++k ) {
						index1 = k % coSeries;
						bRet = TCompMeanDiff<T>( pSeries1[index1], *pSeries, margin );
						if( false == bRet ) {
							break;
						}
						tDiff += _diffabs<T>( pSeries1[index1], *pSeries );
						++ pSeries;
					}
				}

				if( true == bRet ) {
					break;
				}
			}
		}

		return bRet;

	}


 	unsigned int IdentifyPosition( SRxABTData *pABTData );

 	inline UINT GetCoIdCandi() { return m_toLib; }
 	//inline void ClearH000() { m_vecH000.clear(); }

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
    PlatformCode::EnumPlatformCode GetPlatformFromRadarMode( unsigned int uiRadarModeIndex );
    const char *GetPlatformCode(PlatformCode::EnumPlatformCode ePlatform);


 	double GetInActivatedTime( unsigned int uiIndex );

// 	// EOB 관련 함수
// 	void GetEOBLatLong( int *pLatitude, int *pLongitude, int nThreatIndex, int nDeviceIndex, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL );
// 	float GetEOBFLongitude( int nThreatIndex, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL );
// 	float GetEOBFLatitude( int nThreatIndex, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL );
// 	UINT GetEOBPinNumber( int nThreatIndex, EnumLibType enLibType=E_EL_LIB_TYPE_NORMAL );
// 	int CalDistanceNM( int iLat1, int iLong1, int iLat2, int iLong2 );
// 	bool IsFindELNOTInThreat( CString *pStrELNOT, EnumLibType eEOBLibType );
//
// 	void IdentifyCEDEOB( EnumLibType eCEDLibType, EnumLibType eEOBLibType );
// 	bool CELSignalIdentifyAlg::FindEOB( int nThreatIndex, int nDeviceIndex );
// 	bool GetRadarModeASameELNOTInEOBResult( STR_CEDEOBID_INFO *pIDInfo, SELABTDATA_EXT *pABTExtData, char *pszELNOT, EnumLibType eEOBLibType );
 	bool IsSortELNOT( SRadarMode* pRadarModeRef, SRadarMode *pRadarModeNxt );

	bool UpdateToDB_SeenTimeOfRadar(SRxAETData *pABTData);
    bool UpdateToDB_SeenTimeOfRadarMode(SRxABTData *pABTData, bool bFirstSeen);

// 	SOCSystemVariable *GetSystemVar( int nLinkNum );
// 	SRadarMode *GetRadarModeData( int nRadarModeIndex, EnumLibType enLibType );
// 	void SortRadarIndex( int *pCount, int *pIndex, int nMax=100 );
// 	void RemoveDuplicateIndex( int *pCount, int *pIndex, int nMax );

#if defined(_SQLITE_)
    CELSignalIdentifyAlg( const char *pFileName, const char *pThreadName=NULL );
#elif _MSSQL_
    CELSignalIdentifyAlg( CODBCDatabase *pODBCDataBase, const char *pThreadName=NULL );
#else
    CELSignalIdentifyAlg( const char *pFileName, const char *pThreadName );
#endif

	virtual ~CELSignalIdentifyAlg();

protected:
	void CalcMatchRatio();
 	float CalcMatchRatio( EnumMATCHRATIO enMatchRatio, SRadarMode *pRadarMode=NULL );

    float CalcFreqTypeMatchRatio(SRadarMode *pRadarMode);
    float CalcPRITypeMatchRatio(SRadarMode *pRadarMode);

	bool CheckFreqType(ENUM_AET_FRQ_TYPE enFrqType, SRadarMode *pRadarMode );

	void InitRadarModeData();

    //bool LoadRadarModeData( unsigned int *pnRadarMode );
#ifdef _SQLITE_
	void GetRadarModeFromStatement(SRadarMode *pRadarMode, Kompex::SQLiteStatement *pStatment);
    void GetThreatFromStatement( SThreat *pThreat, Kompex::SQLiteStatement *pStatment );
    void GetColumnString( char *pszString, size_t szSize, Kompex::SQLiteStatement *pStatment, int iColumn );
#elif _MSSQL_
    void GetRadarModeFromStatement( SRadarMode *pRadarMode, CODBCRecordset *ptheRS );

#endif

    bool LoadRadarMode_RFSequence( vector<SRadarMode_Sequence_Values> *pVecRadarMode_RFSequence );
    bool LoadRadarMode_PRISequence( vector<SRadarMode_Sequence_Values> *pVecRadarMode_PRISequence );

    bool LoadRadarMode_RFSpot(vector<SRadarMode_Spot_Values> *pVecRadarMode_RFSpot, unsigned int uiMaxRadarMode);
    bool LoadRadarMode_PRISpot(vector<SRadarMode_Spot_Values> *pVecRadarMode_PRISpot, unsigned int uiMaxRadarMode);

    //bool LoadThreatData( int *pnThreat, SThreat *pThreat, int iMaxItems );

    // 변환 코드
    EnumFunctionCodes GetFunctionCodes( const char *pData );
    CEDSignalType::EnumSignalType GetSignalType( const char *pData );
    PolizationCode::EnumPolizationCode GetPolarizationCodes( int iPolization );
    PlatformCode::EnumPlatformCode GetPlatformCode( int iPlatform );
    PatternCode::EnumPatternCode GetPatternCode( int iPattern );
    RadarModeFreqType::EnumRadarModeFreqType GetFreqType( int iFreqType );
    RadarModePRIType::EnumRadarModePRIType GetPRIType( int iPRIType );
    ScanType::EnumScanType GetScanType( int iScanType );
    EnumValidationCode GetValidationCode( int iValidation );

};


