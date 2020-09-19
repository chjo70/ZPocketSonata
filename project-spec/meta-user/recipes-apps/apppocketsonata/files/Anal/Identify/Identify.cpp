// Identify.cpp: implementation of the CELSignalIdentifyAlg class.
//
//////////////////////////////////////////////////////////////////////

#include "../SigAnal/stdafx.h"

#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

//#include "../OFP_Main.h"
#include "../SigAnal/_SigAnal.h"

#include "../EmitterMerge/ELStringDefn.h"
// #include "../EmitterMerge/Geo2UTM.h"
// #include "../EmitterMerge/VincentyParam.h"
// #include "../EmitterMerge/CInverseMethod.h"
// #include "../EmitterMerge/ELCEDLibMngr2.h"
// #include "../../../ELINT/MNGR/ELElintUtilMngr.h"
// #include "../../../COMMON\MNGR\GRTestParamMngr.h"
// #include "../../../COMMON\MNGR\GRLogMngr.h"
#include "Identify.h"
#include "../EmitterMerge/CInverseMethod.h"
// #include "../../DATATYPE\ELCEDLibDataType.h"

// #include "atlstr.h"
//
// #include "../../MNGR/Codec/ELDecoder.h"
#include "./ELUtil.h"

#define MAX_SIZE_OF_CONDITION					(300)

#define DEFAULT_SYMBOL_CODE		"SFPP-----------"

// 정적 초기화
int  CELSignalIdentifyAlg::m_CoInstance = 0;

bool CELSignalIdentifyAlg::m_bInitTable = false;
STR_FLIB *CELSignalIdentifyAlg::m_pFLib = NULL;

STR_HOWTO_IDENTIFY CELSignalIdentifyAlg::m_HowToId[MAX_FRQTYPE][MAX_PRITYPE];

unsigned char CELSignalIdentifyAlg::m_FrqIdCallFunc[MAX_FRQTYPE][MAX_FRQTYPE];
unsigned char CELSignalIdentifyAlg::m_PriIdCallFunc[MAX_PRITYPE][MAX_PRITYPE];

bool CELSignalIdentifyAlg::m_bLoadedDB;

// 시스템 변수의 설정 값
//SOCSystemVariable CELSignalIdentifyAlg::m_stSystemVar[3];
//SELDBEnvVarIdnf *CELSignalIdentifyAlg::m_pSELDBEnvVarIdnf;
SEnvironVariable *CELSignalIdentifyAlg::m_pSEnvironVariable;			///< 시스템 설정값 환경 포인터

vector<STR_H000> CELSignalIdentifyAlg::m_vecH000;

int CELSignalIdentifyAlg::m_iH000;

int CELSignalIdentifyAlg::m_iRadarMode;
SRadarMode *CELSignalIdentifyAlg::m_pRadarMode;

int CELSignalIdentifyAlg::m_iThreat;
SThreat *CELSignalIdentifyAlg::m_pThreat;

STR_EOB_RESULT *CELSignalIdentifyAlg::m_pEOBResult;			///< EOB 식별 결과를 저장하기 위한 임시 저장소
STR_LIB_IDRESULT *CELSignalIdentifyAlg::m_pIdResult;			///< CED 식별 결과를 저장하기 위한 임시 저장소
STR_CEDEOB_RESULT *CELSignalIdentifyAlg::m_pCEDEOBResult;			///< CED/EOB 식별 결과

char *CELSignalIdentifyAlg::m_pszSQLString;

//vector<SDeviceData> CELSignalIdentifyAlg::m_vecDeviceData;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * @brief     생성자로서 메모리 할당, 초기화, 고속으로 신호 식별하기 위한 함수 포인터 정의 등을 수행한다.
 * @param     void
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-19, 오후 5:10
 * @warning
 */
CELSignalIdentifyAlg::CELSignalIdentifyAlg( const char *pFileName ) : Database( pFileName, SQLite::OPEN_READWRITE )
{
    //m_pMyODBC = pMyODBC;

    ++ m_CoInstance;

    if( m_CoInstance == _spOne ) {
        MallocBuffer();
        InitVar();

        InitIdentifyTable();

        //////////////////////////////////////////////////////////////////////////
        // 식별 콜함수 정의
        // 주파수 식별 매칭 정의
        IdentifyFrq[FFixedFixed] = & CELSignalIdentifyAlg::FIdentifyFixFix;
        IdentifyFrq[FFixedHopping] = & CELSignalIdentifyAlg::FIdentifyFixHop;
        IdentifyFrq[FFixedPattern] = & CELSignalIdentifyAlg::FIdentifyFixPat;
        IdentifyFrq[FHoppingHopping] = & CELSignalIdentifyAlg::FIdentifyHopHop;
        IdentifyFrq[FPatternPattern] = & CELSignalIdentifyAlg::FIdentifyPatPat;
        IdentifyFrq[FAgilePattern] = & CELSignalIdentifyAlg::FIdentifyAgiPat;
        IdentifyFrq[FIgnoreFreqType] = & CELSignalIdentifyAlg::FIdentifyFreq;

        // PRI 식별 매칭 정의
        IdentifyPri[PStableStable] = & CELSignalIdentifyAlg::PIdentifyStbStb;
        IdentifyPri[PStableDwell] = & CELSignalIdentifyAlg::PIdentifyStbDwl;
        IdentifyPri[PStaggerStagger] = & CELSignalIdentifyAlg::PIdentifyStgStg;
        IdentifyPri[PDwellDwell] = & CELSignalIdentifyAlg::PIdentifyDwlDwl;
        IdentifyPri[PJitterStagger] = & CELSignalIdentifyAlg::PIdentifyJitStg;
        IdentifyPri[PJitterJitter] = & CELSignalIdentifyAlg::PIdentifyJitJit;
        IdentifyPri[PJitterPattern] = & CELSignalIdentifyAlg::PIdentifyJitPat;
        IdentifyPri[PPatternPattern] = & CELSignalIdentifyAlg::PIdentifyPatPat;
        IdentifyPri[FIgnorePRIType] = & CELSignalIdentifyAlg::PIdentifyPRI;

        m_pSEnvironVariable = GP_ENVI_VAR->GetEnvrionVariable();
    }

}

/**
 * @brief     소멸자로 메모리를 해지한다.
 * @param     void
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-19, 오후 5:28
 * @warning
 */
CELSignalIdentifyAlg::~CELSignalIdentifyAlg()
{
    -- m_CoInstance;

    if( m_CoInstance == 0 ) {
        //GP_ENVI_VAR->ReleaseInstance();
        GP_ENVI_VAR->ReleaseInstance();

        Destory();
    }
}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     신호 식별 객체를 삭제할 때 관련 메모리를 해지한다.
 * @param     void
 * @return    void
 * @version   0.0.1
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-08-08 오후 1:23
 * @warning
 */
void CELSignalIdentifyAlg::Destory()
{
    free( m_pFLib );
    m_pFLib = NULL;

    free( m_pEOBResult );
    m_pEOBResult = NULL;

    free( m_pIdResult );
    m_pIdResult = NULL;

    free( m_pCEDEOBResult );
    m_pCEDEOBResult = NULL;

    delete [] m_pRadarMode;
    m_pRadarMode = NULL;

    delete [] m_pThreat;
    m_pThreat = NULL;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    객체에 사용할 변수를 초기화 를 수행한다.
        \author   조철희
        \return   void
        \version  0.0.30
        \date     2008-07-17 10:22:28
        \warning
*/
void CELSignalIdentifyAlg::InitVar()
{

// 	m_optParameter.freq.bCheckRange = true;
// 	m_optParameter.pri.bCheckRange = true;
// 	m_optParameter.pw.bCheckRange = true;

    m_total_ced = 0;
    m_total_eob = 0;

    if( m_CoInstance == 1 ) {
        m_vecH000.clear();
        m_iH000 = 0;
    }

    InitIdentifyTable();

    // 시스템 변수 초기화
// 	if( CELEnvironVariableMngr::IsReadyInstance() == true ) {
// 		m_pSELDBEnvVarIdnf = GP_MGR_ENVI_VAR->GetIdnfEnvVars();
// 	}

}

/**
 * @brief     DB 서버의 CED 라이브러리를 읽어 온다.
 * @param     eLibType 로딩할 기본형 또는 실무형을 선택한다.
 * @return    항상 true 로 리턴한다.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-08-21, 오후 1:23
 * @warning
 */
bool CELSignalIdentifyAlg::LoadCEDLibrary2()
{
#ifdef _WIN32
    DWORD dwTime=GetTickCount();
#endif
    vector<SRadarMode_Sequence_Values*> vecRadarMode_Sequence_Values;

    InitRadarModeData();

    // 레이더모드 및 PRI 시퀀스 테이블 로딩
    LoadRadarModeData( & m_iRadarMode, m_pRadarMode, MAX_RADARMODE );

    LoadRadarMode_RFSequence( & vecRadarMode_Sequence_Values, m_iRadarMode );
    MakeRadarMode( & vecRadarMode_Sequence_Values, enRFSequenceValue );

    LoadRadarMode_PRISequence( & vecRadarMode_Sequence_Values, m_iRadarMode );
    MakeRadarMode( & vecRadarMode_Sequence_Values, enPRISequenceValue );

    // 주파수 식별 테이블화를 구성한다.
    MakeFreqBand();

    // 식별 테이블화에 해당 빔 번호를 저장하게 한다.
    //dwTime2=GetTickCount();
    MakeFreqLibTable();
    //LogPrint("========================================== MakeFreqLibTable 시간 : %d ms\n", (int)((GetTickCount() - dwTime2) / 1));

    //LogPrint("\n===================== 식별 데이터를 로딩했습니다. !! 시간 : %d ms\n", (int)((GetTickCount() - dwTime) / 1));

    DeletePointers( vecRadarMode_Sequence_Values );

    return true;
}

/**
 * @brief CELSignalIdentifyAlg::InitRadarModeData
 */
void CELSignalIdentifyAlg::InitRadarModeData()
{
    int i;

    SRadarMode *pRadarMode;

    pRadarMode = m_pRadarMode;
    for( i=0 ; i < MAX_RADARMODE ; ++i ) {
        pRadarMode->vecRadarMode_PRISequenceValues.clear();
        pRadarMode->vecRadarRF_Values.clear();

        ++ pRadarMode;
    }
}

/**
  * @brief		DB 테이블로부터 로딩한 데이터를 기반으로 레이더 모드를 구성한다
  * @return 	void
  * @date			2019/04/24 16:21
*/
void CELSignalIdentifyAlg::MakeRadarMode( vector<SRadarMode_Sequence_Values*> *pVecRadarMode_Sequence_Values, ENUM_Sequence enSeq )
{
    int i;
    vector<SRadarMode_Sequence_Values*>::pointer pRadarMode_Sequence;

    SRadarMode *pRadarMode;
    SRadarMode_Sequence_Values stRadarMode_SequenceValues;

    UINT uiRadarMode_Sequence=0, uiSizeOfRadarMode_Sequence;

    pRadarMode_Sequence = pVecRadarMode_Sequence_Values->data();
    uiSizeOfRadarMode_Sequence = pVecRadarMode_Sequence_Values->size();

    pRadarMode = m_pRadarMode;

    uiSizeOfRadarMode_Sequence = pVecRadarMode_Sequence_Values->size();

    if( uiSizeOfRadarMode_Sequence != 0 ) {
        if( enSeq == enRFSequenceValue ) {
            for( i=0 ; i < m_iRadarMode ; ) {
                // 다음번으로 이동
                while( uiRadarMode_Sequence < uiSizeOfRadarMode_Sequence && (*pRadarMode_Sequence)->iRadarModeIndex < pRadarMode->iRadarModeIndex ) {
                    ++ uiRadarMode_Sequence;
                    ++ pRadarMode_Sequence;
                }

                while( uiRadarMode_Sequence < uiSizeOfRadarMode_Sequence && (*pRadarMode_Sequence)->iRadarModeIndex == pRadarMode->iRadarModeIndex ) {
                    stRadarMode_SequenceValues.iRadarModeIndex = (*pRadarMode_Sequence)->iRadarModeIndex;
                    stRadarMode_SequenceValues.i_Index = (*pRadarMode_Sequence)->i_Index;
                    stRadarMode_SequenceValues.f_Min = (*pRadarMode_Sequence)->f_Min;
                    stRadarMode_SequenceValues.f_Max = (*pRadarMode_Sequence)->f_Max;

                     pRadarMode->vecRadarMode_RFSequenceValues.push_back( stRadarMode_SequenceValues );

                    ++ uiRadarMode_Sequence;
                    ++ pRadarMode_Sequence;
                }

                ++ i;
                ++ pRadarMode;

            }
        }
        else if( enSeq == enPRISequenceValue ) {
            for( i=0 ; i < m_iRadarMode ; ) {
                // 다음번으로 이동
                while( uiRadarMode_Sequence < uiSizeOfRadarMode_Sequence && (*pRadarMode_Sequence)->iRadarModeIndex < pRadarMode->iRadarModeIndex ) {
                    ++ uiRadarMode_Sequence;
                    ++ pRadarMode_Sequence;
                }

                while( uiRadarMode_Sequence < uiSizeOfRadarMode_Sequence && (*pRadarMode_Sequence)->iRadarModeIndex == pRadarMode->iRadarModeIndex ) {
                    stRadarMode_SequenceValues.iRadarModeIndex = (*pRadarMode_Sequence)->iRadarModeIndex;
                    stRadarMode_SequenceValues.i_Index = (*pRadarMode_Sequence)->i_Index;
                    stRadarMode_SequenceValues.f_Min = (*pRadarMode_Sequence)->f_Min;
                    stRadarMode_SequenceValues.f_Max = (*pRadarMode_Sequence)->f_Max;

                     pRadarMode->vecRadarMode_PRISequenceValues.push_back( stRadarMode_SequenceValues );

                    ++ uiRadarMode_Sequence;
                    ++ pRadarMode_Sequence;
                }

                ++ i;
                ++ pRadarMode;

            }
        }
    }

}

/**
 * @brief     EOB 라이브러를 불러온다.
 * @param     EnumLibType eCEDLibType
 * @param     EnumLibType eEOBLibType
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-07-05, 오후 5:21
 * @warning
 */
bool CELSignalIdentifyAlg::LoadEOBLibrary2()
{
    //GP_MNGR_CED_LIB2->RTGetAllDeviceData( NULL, (char*) NULL, eEOBLibType );
    LoadThreatData( & m_iThreat, m_pThreat, MAX_RADARMODE );
    return true;

}

/**
 * @brief     이 객체에서 사용할 메모리를 할당한다.
 * @param     void
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-07-17 11:46:07
 * @warning
 */
void CELSignalIdentifyAlg::MallocBuffer()
{

    if( m_pFLib == NULL ) {
        m_pFLib = ( STR_FLIB * ) malloc( sizeof( STR_FLIB ) * ( NO_FLIB_BAND + 1 ) );

        if( m_pFLib == NULL ) { //DTEC_NullPointCheck
            printf( "\n [W] 식별 테이블 저장소를 할당하지 못했습니다 !" );
        }
        else {
            memset( m_pFLib, 0, sizeof(STR_FLIB) * ( NO_FLIB_BAND + 1 ) );
        }

    }

    if( m_pRadarMode == NULL ) {
        m_pRadarMode = new SRadarMode [MAX_RADARMODE];
    }

    if( m_pThreat == NULL ) {
        m_pThreat = new SThreat [MAX_RADARMODE];
    }

    if( m_pEOBResult == NULL ) {
        m_pEOBResult = ( STR_EOB_RESULT * ) malloc( sizeof( STR_EOB_RESULT ) * MAX_ELINT_LIBRARY );
    }

    if( m_pIdResult == NULL ) {
        m_pIdResult = ( STR_LIB_IDRESULT *) malloc( sizeof(STR_LIB_IDRESULT) * MAX_ELINT_LIBRARY );
    }

    if( m_pCEDEOBResult == NULL ) {
        m_pCEDEOBResult = ( STR_CEDEOB_RESULT * ) malloc( sizeof( STR_CEDEOB_RESULT ) * MAX_IDCANDIDATE );
    }

    if( m_pszSQLString == NULL ) {
        m_pszSQLString = ( char * ) malloc( sizeof(char) * MAX_SQL_SIZE );
    }

}

/**
 * @brief     이 객체에서 사용할 변수들을 초기화 한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-08-01 11:10:06
 * @warning
 */
void CELSignalIdentifyAlg::Init()
{
    m_nCoIdEOB = 0;
    m_fromLib = _spZero;
    m_toLib = _spZero;
    m_nCoIdResult = _spZero;
    memset( m_pIdResult, 0, sizeof( LIBINDEX ) * MAX_ELINT_LIBRARY );

    // EOB 기반 초기화
    m_pEOBResult->nThreatIndex = 0;
    m_pEOBResult->nDeviceIndex = 0;
    m_pEOBResult->nRadarIndex = 0;

    m_pEOBResult->dDistance = -1.0;

    m_CEDEOBResult.chELNOT[0] = 0;

    m_CEDEOBResult.nThreatIndex = 0;
    m_CEDEOBResult.nDeviceIndex = 0;

    m_pSEnvironVariable = GP_ENVI_VAR->GetEnvrionVariable();

}
//
/**
 * @brief     신호 식별을 수행하기 위한 식별 테이블 함수를 정의한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-08-01 11:17:46
 * @warning
 */
void CELSignalIdentifyAlg::InitIdentifyTable()
{
    UINT *pFrqType, *pPriType;

    if( m_bInitTable != true ) {
        m_bInitTable = true;

        memset( & m_HowToId, 0xFF, sizeof( m_HowToId ) );

        ////////////////////////////////////////////////////////////////////////////
        // 1. 주파수 Fixed 에 대한 식별 테이블 정의
        // Fixed, Stable
        pFrqType = & m_HowToId[_FIXED][_STABLE].frq[0];
        pPriType = & m_HowToId[_FIXED][_STABLE].pri[0];
        /*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2014-02-02 11:45:32
        */
        *pFrqType = (int) _FIXED,				*pPriType = (int) _STABLE,										++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _FIXED, 				*pPriType = (int) _DWELL,										++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING, 			*pPriType = (int) _STABLE,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING, 			*pPriType = (int) _DWELL,

        // Fixed, Stagger
        pFrqType = & m_HowToId[_FIXED][_STAGGER].frq[0];
        pPriType = & m_HowToId[_FIXED][_STAGGER].pri[0];
        /*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2014-02-02 11:45:32
        */
        *pFrqType = (int) _FIXED, 				*pPriType = (int) _STAGGER,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING, 			*pPriType = (int) _STAGGER;

        // Fixed, Jitter
        pFrqType = & m_HowToId[_FIXED][_JITTER_RANDOM].frq[0];
        pPriType = & m_HowToId[_FIXED][_JITTER_RANDOM].pri[0];
        /*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2014-02-02 11:45:32
        */
        *pFrqType = (int) _FIXED, 			*pPriType = (int) _JITTER_RANDOM,							++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING, 		*pPriType = (int) _JITTER_RANDOM;


        // Fixed, Pattern
        pFrqType = & m_HowToId[_FIXED][_JITTER_PATTERN].frq[0];
        pPriType = & m_HowToId[_FIXED][_JITTER_PATTERN].pri[0];
        *pFrqType = (int) _FIXED, 			*pPriType = (int) _JITTER_PATTERN,						++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING, 		*pPriType = (int) _JITTER_PATTERN;

        // Fixed, Dwell
        pFrqType = & m_HowToId[_FIXED][_DWELL].frq[0];
        pPriType = & m_HowToId[_FIXED][_DWELL].pri[0];
        *pFrqType = (int) _FIXED,       *pPriType = (int) _DWELL,											++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,     *pPriType = (int) _DWELL;

        // Fixed, PRI 무시
        pFrqType = & m_HowToId[_FIXED][_IGNORE_PRI].frq[0];
        pPriType = & m_HowToId[_FIXED][_IGNORE_PRI].pri[0];
        *pFrqType = (int) _FIXED,					*pPriType = (int) _DWELL,										++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _FIXED,					*pPriType = (int) _STABLE,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _FIXED,					*pPriType = (int) _JITTER_RANDOM,						++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _FIXED,					*pPriType = (int) _STAGGER,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _FIXED,					*pPriType = (int) _JITTER_PATTERN,					++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _DWELL,										++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _STABLE,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _JITTER_RANDOM,						++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _STAGGER,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _JITTER_PATTERN;

        ////////////////////////////////////////////////////////////////////////////
        // 2. 주파수 Random Agile 에 대한 식별 테이블 정의
        // Random Agile, Stable
        pFrqType = & m_HowToId[_RANDOM_AGILE][_STABLE].frq[0];
        pPriType = & m_HowToId[_RANDOM_AGILE][_STABLE].pri[0];
        *pFrqType = (int) _RANDOM_AGILE,	*pPriType = (int) _DWELL,										++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,	*pPriType = (int) _STABLE,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _DWELL,										++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _STABLE;

        // Random Agile, Stagger
        pFrqType = & m_HowToId[_RANDOM_AGILE][_STAGGER].frq[0];
        pPriType = & m_HowToId[_RANDOM_AGILE][_STAGGER].pri[0];
        *pFrqType = (int) _RANDOM_AGILE,  *pPriType = (int) _STAGGER,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE, *pPriType = (int) _STAGGER;

        // Random Agile, Jitter
        pFrqType = & m_HowToId[_RANDOM_AGILE][_JITTER_RANDOM].frq[0];
        pPriType = & m_HowToId[_RANDOM_AGILE][_JITTER_RANDOM].pri[0];
        *pFrqType = (int) _RANDOM_AGILE,  *pPriType = (int) _JITTER_RANDOM,						++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE, *pPriType = (int) _JITTER_RANDOM;


        // Random Agile, Pattern
        pFrqType = & m_HowToId[_RANDOM_AGILE][_JITTER_PATTERN].frq[0];
        pPriType = & m_HowToId[_RANDOM_AGILE][_JITTER_PATTERN].pri[0];
        *pFrqType = (int) _RANDOM_AGILE,  *pPriType = (int) _JITTER_PATTERN,					++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE, *pPriType = (int) _JITTER_PATTERN;

        // Random Agile, Dwell
        pFrqType = & m_HowToId[_RANDOM_AGILE][_DWELL].frq[0];
        pPriType = & m_HowToId[_RANDOM_AGILE][_DWELL].pri[0];
        *pFrqType = (int) _RANDOM_AGILE,  *pPriType = (int) _DWELL,										++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE, *pPriType = (int) _DWELL;

        // Random Agile, PRI 무시
        pFrqType = & m_HowToId[_RANDOM_AGILE][_IGNORE_PRI].frq[0];
        pPriType = & m_HowToId[_RANDOM_AGILE][_IGNORE_PRI].pri[0];
        *pFrqType = (int) _RANDOM_AGILE,				*pPriType = (int) _DWELL,							++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,				*pPriType = (int) _STABLE,						++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,				*pPriType = (int) _JITTER_RANDOM,			++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,				*pPriType = (int) _STAGGER,						++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,				*pPriType = (int) _JITTER_PATTERN,		++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,				*pPriType = (int) _DWELL,							++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,				*pPriType = (int) _STABLE,						++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,				*pPriType = (int) _JITTER_RANDOM,			++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,				*pPriType = (int) _STAGGER,						++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,				*pPriType = (int) _JITTER_PATTERN;

        ////////////////////////////////////////////////////////////////////////////
        // 3. 주파수 Hopping 에 대한 식별 테이블 정의
        // Hopping, Stable
        pFrqType = & m_HowToId[_HOPPING][_STABLE].frq[0];
        pPriType = & m_HowToId[_HOPPING][_STABLE].pri[0];
        /*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2014-02-02 11:45:32
        */
        *pFrqType = (int) _HOPPING,     *pPriType = (int) _STABLE,										++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,     *pPriType = (int) _DWELL;

        // Hopping, Stagger
        pFrqType = & m_HowToId[_HOPPING][_STAGGER].frq[0];
        pPriType = & m_HowToId[_HOPPING][_STAGGER].pri[0];
        *pFrqType = (int) _HOPPING,     *pPriType = (int) _STAGGER;

        // Hopping, Jitter
        pFrqType = & m_HowToId[_HOPPING][_JITTER_RANDOM].frq[0];
        pPriType = & m_HowToId[_HOPPING][_JITTER_RANDOM].pri[0];
        *pFrqType = (int) _HOPPING,       *pPriType = (int) _JITTER_RANDOM;

        // Hopping, Pattern
        pFrqType = & m_HowToId[_HOPPING][_JITTER_PATTERN].frq[0];
        pPriType = & m_HowToId[_HOPPING][_JITTER_PATTERN].pri[0];
        *pFrqType = (int) _HOPPING,       *pPriType = (int) _JITTER_PATTERN;

        // Hopping, Dwell
        pFrqType = & m_HowToId[_HOPPING][_DWELL].frq[0];
        pPriType = & m_HowToId[_HOPPING][_DWELL].pri[0];
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _DWELL;

        // Hopping, PRI 무시
        pFrqType = & m_HowToId[_HOPPING][_IGNORE_PRI].frq[0];
        pPriType = & m_HowToId[_HOPPING][_IGNORE_PRI].pri[0];
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _DWELL,										++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _STABLE,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _JITTER_RANDOM,						++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _STAGGER,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _JITTER_PATTERN;

        ////////////////////////////////////////////////////////////////////////////
        // 4. 주파수 Pattern Agile 에 대한 식별 테이블 정의
        // Pattern Agile, Stable
        pFrqType = & m_HowToId[_PATTERN_AGILE][_STABLE].frq[0];
        pPriType = & m_HowToId[_PATTERN_AGILE][_STABLE].pri[0];
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _STABLE,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _DWELL;

        // Pattern Agile, Stagger
        pFrqType = & m_HowToId[_PATTERN_AGILE][_STAGGER].frq[0];
        pPriType = & m_HowToId[_PATTERN_AGILE][_STAGGER].pri[0];
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _STAGGER;

        // Pattern Agile, Jitter
        pFrqType = & m_HowToId[_PATTERN_AGILE][_JITTER_RANDOM].frq[0];
        pPriType = & m_HowToId[_PATTERN_AGILE][_JITTER_RANDOM].pri[0];
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _JITTER_RANDOM;


        // Pattern Agile, Pattern
        pFrqType = & m_HowToId[_PATTERN_AGILE][_JITTER_PATTERN].frq[0];
        pPriType = & m_HowToId[_PATTERN_AGILE][_JITTER_PATTERN].pri[0];
        *pFrqType = _PATTERN_AGILE,	*pPriType = _JITTER_PATTERN;

        // Pattern Agile, Dwell
        pFrqType = & m_HowToId[_PATTERN_AGILE][_DWELL].frq[0];
        pPriType = & m_HowToId[_PATTERN_AGILE][_DWELL].pri[0];
        *pFrqType = (int) _PATTERN_AGILE, *pPriType = (int) _DWELL,									++ pFrqType,  ++ pPriType;

        // Pattern Agile, PRI 무시
        pFrqType = & m_HowToId[_PATTERN_AGILE][_IGNORE_PRI].frq[0];
        pPriType = & m_HowToId[_PATTERN_AGILE][_IGNORE_PRI].pri[0];
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _DWELL,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _STABLE,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _JITTER_RANDOM,					++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _STAGGER,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _JITTER_PATTERN;

        ////////////////////////////////////////////////////////////////////////////
        // 5. 주파수 무시 에 대한 식별 테이블 정의
        // 주파수 무시, Stable
        pFrqType = & m_HowToId[_IGNORE_FREQ][_STABLE].frq[0];
        pPriType = & m_HowToId[_IGNORE_FREQ][_STABLE].pri[0];
        *pFrqType = (int) _FIXED,					*pPriType = (int) _DWELL,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _FIXED,					*pPriType = (int) _STABLE,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,	*pPriType = (int) _DWELL,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,	*pPriType = (int) _STABLE,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _DWELL,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _STABLE,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE, *pPriType = (int) _DWELL,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _STABLE;

        // 주파수 무시, Stagger
        pFrqType = & m_HowToId[_IGNORE_FREQ][_STAGGER].frq[0];
        pPriType = & m_HowToId[_IGNORE_FREQ][_STAGGER].pri[0];
        *pFrqType = (int) _FIXED,					*pPriType = (int) _STAGGER,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,  *pPriType = (int) _STAGGER,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _STAGGER,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _STAGGER;

        // 주파수 무시, Jitter
        pFrqType = & m_HowToId[_IGNORE_FREQ][_JITTER_RANDOM].frq[0];
        pPriType = & m_HowToId[_IGNORE_FREQ][_JITTER_RANDOM].pri[0];
        *pFrqType = (int) _FIXED,					*pPriType = (int) _JITTER_RANDOM,					++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _FIXED,					*pPriType = (int) _JITTER_PATTERN,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _FIXED,					*pPriType = (int) _STAGGER,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,  *pPriType = (int) _JITTER_RANDOM,					++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,  *pPriType = (int) _JITTER_PATTERN,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,  *pPriType = (int) _STAGGER,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _JITTER_RANDOM,					++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _JITTER_PATTERN,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _STAGGER,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _JITTER_RANDOM,					++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _JITTER_PATTERN,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _STAGGER;

        // 주파수 무시, Pattern
        pFrqType = & m_HowToId[_IGNORE_FREQ][_JITTER_PATTERN].frq[0];
        pPriType = & m_HowToId[_IGNORE_FREQ][_JITTER_PATTERN].pri[0];
        *pFrqType = (int) _FIXED,					*pPriType = (int) _JITTER_PATTERN,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,  *pPriType = (int) _JITTER_PATTERN,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _JITTER_PATTERN,								++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _JITTER_PATTERN,

        // 주파수 무시, Dwell
        pFrqType = & m_HowToId[_IGNORE_FREQ][_DWELL].frq[0];
        pPriType = & m_HowToId[_IGNORE_FREQ][_DWELL].pri[0];
        *pFrqType = (int) _FIXED,					*pPriType = (int) _DWELL,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _RANDOM_AGILE,  *pPriType = (int) _DWELL,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _DWELL,									++ pFrqType,  ++ pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _DWELL,

        // 주파수 무시, PRI 무시
        pFrqType = & m_HowToId[_IGNORE_FREQ][_IGNORE_PRI].frq[0];
        pPriType = & m_HowToId[_IGNORE_FREQ][_IGNORE_PRI].pri[0];
        *pFrqType = (int) _FIXED,					*pPriType = (int) _STABLE,								++ pFrqType,  ++pPriType;
        *pFrqType = (int) _FIXED,					*pPriType = (int) _JITTER_RANDOM,					++ pFrqType,  ++pPriType;
        *pFrqType = (int) _FIXED,					*pPriType = (int) _DWELL,									++ pFrqType,  ++pPriType;
        *pFrqType = (int) _FIXED,					*pPriType = (int) _STAGGER,								++ pFrqType,  ++pPriType;
        *pFrqType = (int) _FIXED,					*pPriType = (int) _JITTER_PATTERN,				++ pFrqType,  ++pPriType;
        *pFrqType = (int) _RANDOM_AGILE,	*pPriType = (int) _STABLE,								++ pFrqType,  ++pPriType;
        *pFrqType = (int) _RANDOM_AGILE,	*pPriType = (int) _JITTER_RANDOM,					++ pFrqType,  ++pPriType;
        *pFrqType = (int) _RANDOM_AGILE,	*pPriType = (int) _DWELL,									++ pFrqType,  ++pPriType;
        *pFrqType = (int) _RANDOM_AGILE,	*pPriType = (int) _STAGGER,								++ pFrqType,  ++pPriType;
        *pFrqType = (int) _RANDOM_AGILE,	*pPriType = (int) _JITTER_PATTERN,				++ pFrqType,  ++pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _STABLE,								++ pFrqType,  ++pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _JITTER_RANDOM,					++ pFrqType,  ++pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _DWELL,									++ pFrqType,  ++pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _STAGGER,								++ pFrqType,  ++pPriType;
        *pFrqType = (int) _HOPPING,				*pPriType = (int) _JITTER_PATTERN,				++ pFrqType,  ++pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _STABLE,								++ pFrqType,  ++pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _JITTER_RANDOM,					++ pFrqType,  ++pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _DWELL,									++ pFrqType,  ++pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _STAGGER,								++ pFrqType,  ++pPriType;
        *pFrqType = (int) _PATTERN_AGILE,	*pPriType = (int) _JITTER_PATTERN;

        //////////////////////////////////////////////////////////////////////////
        //
        memset( m_FrqIdCallFunc, FIgnoreFreqType, sizeof( m_FrqIdCallFunc ) );
        memset( m_PriIdCallFunc, FIgnorePRIType, sizeof( m_PriIdCallFunc ) );

        // 주파수 식별에 대한 함수 콜 넘버 정의
        m_FrqIdCallFunc[_FIXED][_FIXED] = FFixedFixed;
        m_FrqIdCallFunc[_FIXED][_HOPPING] = FFixedHopping;
        m_FrqIdCallFunc[_HOPPING][_HOPPING] = FHoppingHopping;
        m_FrqIdCallFunc[_PATTERN_AGILE][_PATTERN_AGILE] = FPatternPattern;
        m_FrqIdCallFunc[_RANDOM_AGILE][_PATTERN_AGILE] = FAgilePattern;
        m_FrqIdCallFunc[_RANDOM_AGILE][_RANDOM_AGILE] = FAgilePattern;

        // PRI 식별에 대한 함수 콜 넘버 정의
        m_PriIdCallFunc[_STABLE][_STABLE] = PStableStable;
        m_PriIdCallFunc[_STABLE][_DWELL] = PStableDwell;
        m_PriIdCallFunc[_STAGGER][_STAGGER] = PStaggerStagger;
        m_PriIdCallFunc[_DWELL][_DWELL] = PDwellDwell;
        m_PriIdCallFunc[_JITTER_RANDOM][_STAGGER] = PJitterStagger;
        m_PriIdCallFunc[_JITTER_RANDOM][_JITTER_RANDOM] = PJitterJitter;
        m_PriIdCallFunc[_JITTER_RANDOM][_JITTER_PATTERN] = PJitterPattern;
        m_PriIdCallFunc[_JITTER_PATTERN][_JITTER_PATTERN] = PPatternPattern;
    }

}

// //////////////////////////////////////////////////////////////////////////
// /*! \brief    입력한 방사체 정보로 CED 및 EOB 신호 식별을 수행한다.
// 		\author   조철희
// 		\param    pNewAet 식별할 STE_NEWAET 포인터
// 		\param    eCEDLibType CED 라이브러리의 기본형 또는 실무형 선택
// 		\param    eEOBLibType EOB 라이브러리의 기본형 또는 실무형 선택
// 		\return   void
// 		\version  0.0.31
// 		\date     2008-07-18 22:44:57
// 		\warning
// */
// void CELSignalIdentifyAlg::Identify( STR_NEWAET *pNewAet, EnumLibType eCEDLibType, EnumLibType eEOBLibType )
// {
//
// 	// CED/EOB 라이브러리 로드
//
// 	// 식별 관련 변수 초기화
// 	Init();
//
// 	// 신호 식별 수행
// 	if( m_total_ced != _spZero ) {
// 		ConvertToIdentifyAet( pNewAet );
// 		IdentifyFreqPRI( pNewAet, eCEDLibType  );
// 	}
//
// 	// 3. 펄스폭 식별
// 	IdentifyPW();
//
// 	// 4. 스캔 식별
// 	//IdentifyScan();
//
// 	// 6. 우선 순위 식별
// 	IdentifyPriority();
//
// 	// 7. 일치율 식별
// 	IdentifyMatchRatio();
//
// 	// 8. 후보를 정렬한다.
// 	SortThreatLevel();
//
// }
//
// /**
//  * @brief     빔 정보를 기반으로 CED/EOB 신호 식별을 수행한다.
//  * @param     pABTData CED 신호 식별할 빔 데이터
//  * @param     pLOBDataExt CED 신호 식별할 빔 확장 데이터
//  * @param     pstPosData EOB 식별할 위치 산출 값
//  * @param     nLinkNum 링크 번호
//  * @param     bMakeH0000 미식별 인덱스 증가여부를 결정
//  * @param     eCEDLibType 기본형 또는 실무형 라이브러리를 선택
//  * @param     eEOBLibType 기본형 또는 실무형 라이브러리를 선택
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-28, 오후 5:14
//  * @warning
//  */
// void CELSignalIdentifyAlg::Identify( SELABTDATA *pABTData, SELABTDATA_EXT *pABTExtData, SELLOBDATA_EXT *pLOBDataExt, int nLinkNum, BOOL bMakeH0000, EnumLibType eCEDLibType, EnumLibType eEOBLibType, bool bIDExecute )
// {
// 	SPosEstData tempPosEst;
//
// 	STR_CEDEOBID_INFO *pABTIDInfo;
//
// 	pABTIDInfo = & pABTData->idInfo;
//
// 	// 1. 데이터 변환
// 	ConvertToIdentifyAet( pABTData );
//
// 	// 항공기 시스템 변수 번호 저장
// 	pLOBDataExt->aetAnal.iLinkNum = nLinkNum;
// 	m_nLinkNum = nLinkNum;
//
// 	// 2. 식별 관련 변수 초기화
// 	Init();
//
// 	if( bIDExecute == true ) {
// 		// 4. 위협 데이터의 신호 식별
// 		if( m_total_ced != _spZero ) {
// 			// 4.1 신호 형태, MOP, 극성, 주파수 및 PRI 식별
// 			IdentifyFreqPRI( eCEDLibType );
// 		}
//
// 		// 5. 펄스폭 식별
// 		// IdentifyPW();
//
// 		// 6. 스캔 식별
// 		// IdentifyScan();
//
// 		// 7. 우선 순위 식별
// 		IdentifyPriority();
//
// 		// 8. 일치율 식별
// 		IdentifyMatchRatio();
//
// 		// 9. 후보를 정렬한다.
// 		SortThreatLevel();
//
// 	}
//
// 	// 10. 위치 산출의 신호 식별
// 	if( pABTData->bValidity == true ) {
// 		// EOB 전체 대해서 위치 산출한 정보를 이용하여 신호 식별한다.
// 		tempPosEst.dCEP = (double) pABTData->peInfo.iCEP;
// 		IdentifyPosition( & pABTData->idInfo, & m_IdAet.ext.posEst, & tempPosEst, eCEDLibType, eEOBLibType );
//
// 		// EOB 식별 결과를 저장한다.
// 		pABTIDInfo->nThreatIndex = tempPosEst.nThreatIndex;
// 		pABTIDInfo->nDeviceIndex = tempPosEst.nDeviceIndex;
//
// 	}
//
// 	if( pABTExtData != NULL ) {
// 		pABTExtData->nCoIdEOB = min( m_nCoIdEOB, MAX_CANDIDATE_EOB );
// 		memcpy( & pABTExtData->stEOBResult[0], m_pEOBResult, sizeof(STR_EOB_RESULT)*pABTExtData->nCoIdEOB );
// 	}
//
// 	// 11. CED 식별한 정보와 비교하여 위치 산출한다.
// 	IdentifyCEDEOB( m_eCEDLibType, m_eEOBLibType );
//
// 	// 12. 신호 정보 저장
// 	CopyAmbiguity( & pLOBDataExt->aetAnal, & pLOBDataExt->aetData, bMakeH0000 );
//
// }
//
// /**
//  * @brief     방사체 정보에 대해서 기반으로 CED/EOB 신호 식별을 수행한다.
//  * @param     pAETData 방사체 신호를 식별할 SELAETDATA 포인터
//  * @param     pAETDataExt 방사체 정보의 추가 정보 데이터
//  * @param     nLinkNum 링크 번호
//  * @param     bMakeH0000 미식별 인덱스 증가여부를 결정
//  * @param     eCEDLibType 기본형 또는 실무형 라이브러리를 선택
//  * @param     eEOBLibType 기본형 또는 실무형 라이브러리를 선택
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-04, 오후 1:04
//  * @warning
//  */
//void CELSignalIdentifyAlg::IdentifyAET( SELAETDATA *pAETData, SELAETDATA_EXT *pAETDataExt, int nLinkNum, EnumLibType eCEDLibType, EnumLibType eEOBLibType, SELABTDATA *pABTData )
//{
// 	STR_CEDEOBID_INFO *pAETIDInfo;
//
// 	pAETIDInfo = & pAETData->idInfo;

// 	// 항공기 시스템 변수 번호 저장
// 	m_nLinkNum = nLinkNum;

// 	// EOB 라이브러리 로드
// 	GP_MNGR_CED_LIB2->RqstEOBLibData( eEOBLibType );
//
// 	// CED/EOB 라이브러리 형태
// 	m_eCEDLibType = eCEDLibType;
// 	m_eEOBLibType = eEOBLibType;
//
// 	// 식별 관련 변수 초기화
    //Init();

    // 1. 위치 산출의 신호 식별
// 	if( pAETData->bValidity == true ) {
// 		SPosEstData tempPosEst;
//
// 		// EOB 전체 대해서 위치 산출한 정보를 이용하여 신호 식별한다.
// 		m_IdAet.ext.posEst.dEstLatitude = DLONGITUDE2LONG( pAETData->peInfo.iLatitude );
// 		m_IdAet.ext.posEst.dEstLongitude = DLONGITUDE2LONG( pAETData->peInfo.iLongitude );
//
// 		tempPosEst.dCEP = (double) pAETData->peInfo.iCEP;
// 		IdentifyPosition( & pAETData->idInfo, & m_IdAet.ext.posEst, & tempPosEst, eEOBLibType, eEOBLibType );
//
// 		// EOB 식별 결과를 저장한다.
// 		pAETIDInfo->nThreatIndex = tempPosEst.nThreatIndex;
// 		pAETIDInfo->nDeviceIndex = tempPosEst.nDeviceIndex;
//
// 	}

    // 2. 신호 정보 저장
//    SetIDResult( pAETData, pAETDataExt, NULL, eCEDLibType, eEOBLibType );

 //}

// /**
//  * @brief     식별 정보를 저장한다.
//  * @param     pAETData 식별 정보를 저장할 방사체 데이터 포인터
//  * @param     pAETDataExt 방사체 정보의 추가 정보 데이터
//  * @param     eCEDLibType 기본형 또는 실무형 라이브러리를 선택
//  * @param     eEOBLibType 기본형 또는 실무형 라이브러리를 선택
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-07, 오전 11:01
//  * @warning
//  */
// void CELSignalIdentifyAlg::SetIDResult( SELAETDATA *pAETData, SELAETDATA_EXT *pAETDataExt, SELABTDATA_EXT *pABTExtData, EnumLibType eCEDLibType, EnumLibType eEOBLibType, bool bManualEdited )
// {
// 	int i;
// 	bool bRet;
// 	SDevice *pDevice;
// 	STR_CEDEOBID_INFO *pIDInfo, idTemp;
//
// 	SRadarMode *pRadarMode;
//
//  	pIDInfo = & pAETData->idInfo;
//
// 	memcpy( & idTemp, pIDInfo, sizeof(STR_CEDEOBID_INFO) );
//
// 	// CED 가 식별 되지 않을 경우,
// 	if( pIDInfo->nCoRadarIndex == _spZero ) {
// 		pIDInfo->eIdResult = E_EL_UNK_ID;
//
//  	}
// 	// CED 가 식별될 경우,
//  	else {
// 		// CED와 EOB가 매칭된 경우
// 		if( pAETData->peInfo.enValid != E_EL_PESTAT_SUCCESS && bManualEdited == false ) {
// 			pIDInfo->eIdResult = E_EL_UNK_ID;
// 		}
// 		else {
// 			if( pIDInfo->nThreatIndex == _spZero && bManualEdited == false ) {
// 				pIDInfo->eIdResult = E_EL_NEW_ID;
// 			}
// 			else {
// 				for( i=0 ; i < pIDInfo->nCoRadarIndex ; ++i ) {
// 					pRadarMode = GP_MNGR_CED_LIB2->RTGetRadarDataFromMemory( pIDInfo->nRadarIndex[i], eCEDLibType );
//
// 					if( pRadarMode != NULL ) {
//
// 						bRet = GetRadarModeASameELNOTInEOBResult( & idTemp, pABTExtData, pRadarMode->szELNOT, eEOBLibType );
//
// 						// 신출보다 기성이 우선한다.
// 						if( bRet == true ) {
// 							pIDInfo->eIdResult = E_EL_OLD_ID;
// 							break;
// 						}
// 						else {
// 							pIDInfo->eIdResult = E_EL_NEW_ID;
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
//
// 	//
// 	pDevice = GP_MNGR_CED_LIB2->RTGetDeviceData( pIDInfo->nThreatIndex, pIDInfo->nDeviceIndex, eEOBLibType );
// 	if( pDevice != NULL ) {
// 		strcpy_s( pAETDataExt->szEOBELNOT, pDevice->szELNOT );
// 	}
// 	else {
// 		pAETDataExt->szEOBELNOT[0] = NULL;
// 	}
//
// }
//
// /**
//  * @brief     LOB 정보에 대해서 기반으로 CED/EOB 신호 식별을 수행한다.
//  * @param     *pLOBDataGrp 식별할 LOB 데이터
//  * @param     *pLOBDataExt 식별할 LOB 추가 정보 데이터
//  * @param     *pstPosData 식별할 위치 산출 데이터
//  * @param     nLinkNum 링크 번호
//  * @param     bMakeH0000 미식별 인덱스 증가여부를 결정
//  * @param     eCEDLibType 기본형 또는 실무형 라이브러리를 선택
//  * @param     eEOBLibType 기본형 또는 실무형 라이브러리를 선택
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-02-16, 오후 1:26
//  * @warning
//  */
void CELSignalIdentifyAlg::Identify( SRxLOBData *pLOBData, SELLOBDATA_EXT *pLOBDataExt, SPosEstData *pstPosData, BOOL bMakeH0000 )
{

    m_pLOBData = pLOBData;

    // 항공기 시스템 변수 번호 저장
    //pLOBDataExt->aetAnal.iLinkNum = nLinkNum;
    //m_nLinkNum = nLinkNum;

    // 2. 식별 관련 변수 초기화
    Init();

    // 3. 위협 데이터의 신호 식별
    if( m_total_ced != _spZero ) {
        // 3-1. 신호 형태, MOP, 극성, 주파수 및 PRI 식별
        IdentifyFreqPRI( pLOBData );
    }

    // 5. 펄스폭 식별
    // IdentifyPW();

    // 6. 스캔 식별
    //IdentifyScan();

    // 7. 우선 순위 식별
    IdentifyPriority();

    // 8. 일치율 식별
    IdentifyMatchRatio();

    // 9. 후보를 정렬한다.
    SortThreatLevel();

    // 10. 위치 산출의 신호 식별
    // EOB 전체 대해서 위치 산출한 정보를 이용하여 신호 식별한다.
    //IdentifyPosition( NULL, & m_IdAet.ext.posEst, pstPosData );

    // 11. CED 식별한 정보와 비교하여 위치 산출한다.
    //IdentifyCEDEOB( m_eCEDLibType, m_eEOBLibType );

    // 12. 신호 정보 저장
    CopyAmbiguity( & pLOBDataExt->aetAnal, & pLOBDataExt->aetData, bMakeH0000 );

}

/**
 * @brief CELSignalIdentifyAlg::Identify
 * @param pABTData
 * @param pABTExtData
 * @param pLOBDataExt
 * @param bIDExecute
 * @param bMakeH0000
 */
void CELSignalIdentifyAlg::Identify( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, SELLOBDATA_EXT *pLOBDataExt, bool bIDExecute, bool bMakeH0000 )
{
    int nThreatIndex=0;

    //STR_CEDEOBID_INFO *pABTIDInfo;

    //pABTIDInfo = & pABTData->idInfo;

    // 2. 식별 관련 변수 초기화
    Init();

    if( bIDExecute == true ) {
        // 4. 위협 데이터의 신호 식별
        if( m_total_ced != _spZero ) {
            // 4.1 신호 형태, MOP, 극성, 주파수 및 PRI 식별
            //IdentifyFreqPRI( pABTData );
        }

        // 5. 펄스폭 식별
        // IdentifyPW();
//
// 		// 6. 스캔 식별
// 		// IdentifyScan();
//
// 		// 7. 우선 순위 식별
        IdentifyPriority();

        // 8. 일치율 식별
        IdentifyMatchRatio();

        // 9. 후보를 정렬한다.
        SortThreatLevel();

    }
    else {
        pABTData->iRadarModeIndex = m_pLOBData->iRadarModeIndex;
    }

    // 10. 위치 산출의 신호 식별
    if( pABTData->iPEValid == _spOne ) {
        // EOB 전체 대해서 위치 산출한 정보를 이용하여 신호 식별한다.
        // tempPosEst.dCEP = (double) pABTData->fCEP;
        nThreatIndex = IdentifyPosition( pABTData );
    }
    else {
        pABTData->fDistanceErrorOfThreat = -1.0;
    }

    if( pABTExtData != NULL ) {
        //pABTExtData->nCoIdEOB = min( m_nCoIdEOB, MAX_CANDIDATE_EOB );
        //memcpy( & pABTExtData->stEOBResult[0], m_pEOBResult, sizeof(STR_EOB_RESULT)*pABTExtData->nCoIdEOB );

        if( nThreatIndex != 0 ) {
            pABTExtData->enPlatform = m_pThreat[nThreatIndex-1].enPlatform;
        }
        else {
            pABTExtData->enPlatform = enPlatform_UNKNOWN;
        }
    }

    // 11. CED 식별한 정보와 비교하여 위치 산출한다.
    //IdentifyCEDEOB();

    // 12. 신호 정보 저장
    CopyAmbiguity( & pLOBDataExt->aetAnal, & pLOBDataExt->aetData, bMakeH0000 );

}

// /**
//  * @brief     CED 식별 결과와 EOB 식별 결과를 종합하여 식별 정보를 결정한다.
//  * @param     eCEDLibType 기본형 또는 실무형 라이브러리를 선택
//  * @param     eEOBLibType 기본형 또는 실무형 라이브러리를 선택
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2015-10-28, 오후 8:07
//  * @warning
//  */
// void CELSignalIdentifyAlg::IdentifyCEDEOB( EnumLibType eCEDLibType, EnumLibType eEOBLibType )
// {
// 	int i, j, nRadarIndex, nEOBRadarIndex;
//
// 	SRadarMode *pRadarMode;
//
// 	STR_EOB_RESULT *pEOBResult;
//
// 	STR_LIB_IDRESULT *pCEDResult = m_pIdResult;
//
// 	STR_CEDEOB_RESULT *pCEDEOBResult = m_pCEDEOBResult;
//
// 	m_nCoCEDEOB = 0;
//
// 	// 빔/방사체 EOB 식별시 첫번째 CED 식별만 적용함.
// 	for( i=0 ; i < m_nCoIdResult && i < _spOne ; ++i )
// 	{
// 		pRadarMode = pCEDResult->pIdxRadarMode;
//
// 		if( pRadarMode == NULL ) {
// 			continue;
// 		}
//
// 		nRadarIndex = pRadarMode->nRadarIndex;
//
// 		if( ( nRadarIndex == 0 ) || ( strlen(pRadarMode->szELNOT) == 0 ) ) {
// 			continue;
// 		}
//
// 		pEOBResult = m_pEOBResult;
// 		for( j=0 ; j < m_nCoIdEOB ; ++j ) {
// 			char *pszEOBELNOT;
//
// 			pszEOBELNOT = GP_MNGR_CED_LIB2->RTGetELNOTFromDeviceMemory( pEOBResult->nThreatIndex, pEOBResult->nDeviceIndex );
// 			nEOBRadarIndex = GP_MNGR_CED_LIB2->RTGetRadarIndexFromThreatMemory( pszEOBELNOT, _spZero );
//
// 			// 현재 위협에서 레이더가 존재한 경우에만 비교함.
// 			if( pszEOBELNOT != NULL && nRadarIndex == nEOBRadarIndex ) {
// 				pCEDEOBResult->nThreatIndex = pEOBResult->nThreatIndex;
// 				pCEDEOBResult->nDeviceIndex = pEOBResult->nDeviceIndex;
//
// 				pCEDEOBResult->nRadarIndex = pRadarMode->nRadarIndex;
// 				pCEDEOBResult->nRadarModeIndex = pRadarMode->nRadarModeIndex;
//
// 				++ m_nCoCEDEOB;
// 				++ pCEDEOBResult;
// 				break;
// 			}
//
// 			++ pEOBResult;
//
// 		}
//
// 		++ pCEDResult;
// 	}
//
// }
//
// /**
//  * @brief     지정한 위협/장비 인덱스로 EOB 데이터를 얻어온다.
//  * @param     int nThreatIndex
//  * @param     int nThreatIndex
//  * @return    BOOL
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-06-07, 오후 5:07
//  * @warning
//  */
// BOOL CELSignalIdentifyAlg::FindEOB( int nThreatIndex, int nDeviceIndex )
// {
// 	int i;
// 	BOOL bRet=FALSE;
//
// 	STR_EOB_RESULT *pEOBResult;
//
// 	pEOBResult = m_pEOBResult;
// 	for( i=0 ; i < m_nCoIdEOB ; ++i ) {
// 		if( pEOBResult->nThreatIndex == nThreatIndex && pEOBResult->nDeviceIndex == nDeviceIndex ) {
// 			bRet = TRUE;
// 			break;
// 		}
//
// 		++ pEOBResult;
// 	}
//
// 	return bRet;
// }
//
// /**
//  * @brief     CED의 ELNOT과 동일한 명칭을 EOB에서 찾아서 Device 포인터를 리턴한다.
//  * @param     *pStrELNOT ELNOT 데이터
//  * @param     eEOBLibType 기본형 또는 실무형 라이브러리를 선택
//  * @return    *SDevice 장비를 리턴한다.
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2015-10-28, 오후 9:03
//  * @warning
//  */
// bool CELSignalIdentifyAlg::GetRadarModeASameELNOTInEOBResult( STR_CEDEOBID_INFO *pIDInfo, SELABTDATA_EXT *pABTExtData, char *pszELNOT, EnumLibType eEOBLibType )
// {
// 	int i, iSize;
// 	bool bRet=false;
// 	STR_EOB_RESULT *pEOBResult;
// 	char *pszDeviceELNOT;
//
// 	if( pABTExtData == NULL ) {
// 		pEOBResult = m_pEOBResult;
// 		iSize = m_nCoCEDEOB;
// 	}
// 	else {
// 		pEOBResult = pABTExtData->stEOBResult;
// 		iSize = pABTExtData->nCoIdEOB;
// 	}
//
// 	for( i=0 ; i < iSize ; ++i, ++ pEOBResult ) {
// 		pszDeviceELNOT = GP_MNGR_CED_LIB2->RTGetELNOTFromDeviceMemory( pEOBResult->nThreatIndex, pEOBResult->nDeviceIndex );
//
// 		if( pszDeviceELNOT == NULL ) {
// 			continue;
// 		}
//
// 		if( strcmp( pszDeviceELNOT, pszELNOT ) == 0 ) {
// 			pIDInfo->nThreatIndex = pEOBResult->nThreatIndex;
// 			pIDInfo->nDeviceIndex = pEOBResult->nDeviceIndex;
//
//  			bRet = true;
//  			break;
//  		}
//
// 	}
//
// 	return bRet;
// }
//
// //////////////////////////////////////////////////////////////////////////
// /*!
//  * @brief			거리에 대해서 정렬하기 위한 함수이다.
//  * @param     *arg1 비교할 인자1
//  * @param     *arg2 비교할 인자2
//  * @return    같으면 0, 인자1이 크면 1, 인자2가 크면 -1을 리턴한다.
//  * @version   0.0.1
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @date      2013-12-23 오후 8:16
//  * @warning
//  */
// int incDistanceCompare( const void *arg1, const void *arg2 )
// {
// 	int iRet=0;
// 	const STR_EOB_RESULT *p1, *p2;
//
// 	p1 = (STR_EOB_RESULT *) const_cast<void*>(arg1);
// 	p2 = (STR_EOB_RESULT *) const_cast<void*>(arg2);
//
// 	if( ( ( ( p1->dDistance > p2->dDistance ) && ( p1->dDistance < p2->dDistance ) ) == false ) && ( p1->nThreatIndex == p2->nThreatIndex ) ) {
// 		if( p1->nDeviceIndex > p2->nDeviceIndex ) {
// 			iRet = 1;
// 		}
// 	}
// 	else {
// 		if( p1->dDistance > p2->dDistance ) {
// 			iRet = 1;
// 		}
// 		else if( p1->dDistance < p2->dDistance ) {
// 			iRet = -1;
// 		}
// 		else {
// 			// iRet = 0;
// 		}
// 	}
//
// 	return iRet;
//
// }
//
/**
 * @brief     위치 산출을 입력으로 신호 식별을 수행한다.
 * @param     *pPosEstData 위치 산출 값에 대해서 식별할 포인터
 * @param     *pstPosData 식별 결과가 저장할 포인터
 * @param     eEOBIdentifyDefaultLib 기본형 또는 실무형 라이브러리를 선택
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2013-12-23 오후 7:01
 * @warning
 */
int CELSignalIdentifyAlg::IdentifyPosition( SRxABTData *pABTData )
{
    int i;

    double dDistance, dMixDistance;

    // 1. 거리별로 모든 EOB를 계산한다.
    SThreat *pThreat;

    double dEobIndfRangeKM = m_pSEnvironVariable->fEobIndfRangeMeters;
    dMixDistance = dEobIndfRangeKM;

    pThreat = m_pThreat;
    for( i=0 ; i < (int) m_iThreat ; ++i ) {
// 				eob_latitude = pDeviceData->eob_latitude / 10000.;
// 				eob_longitude = pDeviceData->eob_longitude / 10000.;
//
            //ST_IMA->VincentyInverse( & distlob, eob_latitude, eob_longitude, res_latitude, res_longitude );
        dDistance = ST_IMA->GCDistance( (double) pThreat->fLatitude, (double) pThreat->fLongitude, (double) pABTData->fLatitude, (double) pABTData->fLongitude );

        //printf( "\nDist from Th[%d] : %f [m]", pThreat->iThreatIndex, dDistance );
        //Log( enNormal, "Dist from Th[%d] : %f [m]", pThreat->iThreatIndex, dDistance );

        if( /*i == 0 || */ ( dMixDistance > dDistance && dDistance <= pThreat->fIdRange ) ) {
            pABTData->iThreatIndex = pThreat->iThreatIndex;
            pABTData->fDistanceErrorOfThreat = (float) dDistance;

            dMixDistance = dDistance;
        }

        ++ pThreat;

    }

    if( dEobIndfRangeKM < pABTData->fDistanceErrorOfThreat ) {
        pABTData->iThreatIndex = 0;
        pABTData->fDistanceErrorOfThreat = -1.0;
    }

// 				iDistance = (int) ( distlob.dDistance + 0.5 );
// 				iDistance = M2NM( iDistance );
//
// 				// 식별 옵션 추가 비교
// 				if( fDist > 0.0 || fDist < 0.0 ) {
// 					dThreshold = (double) fDist;
// 				}
// 				else {
// 					if( pDeviceData->nIdentificationRange <= 0 ) {
// 						dThreshold = m_pSELDBEnvVarIdnf->iEobIndfRangeNM;
// 					}
// 					else {
// 						dThreshold = pDeviceData->nIdentificationRange;
// 					}
// 				}
//
// 				if( m_optParameter.dist.bCheckType == false || dThreshold > iDistance ) { // m_optParameter.dist.iMaxDistance >= iDistance ) {
// 					pEOBResult->nThreatIndex = pDeviceData->nThreatIndex;
// 					pEOBResult->nDeviceIndex = pDeviceData->nDeviceIndex;
// 					pEOBResult->nRadarIndex = 0;
//
// 					pEOBResult->dDistance = distlob.dDistance;
//
// 					++ pEOBResult;
// 					++ m_nCoIdEOB;
// 				}
//
// 				++ pDeviceData;
//
// 		}

    return pABTData->iThreatIndex;

}
//
// //////////////////////////////////////////////////////////////////////////
// /*! \brief    식별 할 데이터를 식별하기 위한 값으로 변환한다.
// 		\author   조철희
// 		\param    *pNewAet 식별할 데이터
// 		\return   void
// 		\version  0.0.35
// 		\date     2008-08-07 15:21:39
// 		\warning
// */
// void CELSignalIdentifyAlg::ConvertToIdentifyAet( STR_NEWAET *pNewAet )
// {
// 	int i;
//
// 	m_IdAet.aet.ucSignalType = pNewAet->aet.ucSignalType;
//
// 	// 주파수 변환
// 	m_IdAet.aet.Frequency.type = pNewAet->aet.Frequency.type;
// 	m_IdAet.aet.Frequency.band = -1;
//
// 	m_IdAet.aet.Frequency.mean = (int) ( ELDecoder::DecodeFrq( pNewAet->aet.Frequency.mean ) + 0.5 );
// 	m_IdAet.aet.Frequency.imin = (int) ( ELDecoder::DecodeFrq( pNewAet->aet.Frequency.imin ) + 0.5 );
// 	m_IdAet.aet.Frequency.imax = (int) ( ELDecoder::DecodeFrq( pNewAet->aet.Frequency.imax ) + 0.5 );
//
// 	m_IdAet.aet.Frequency.patType = pNewAet->aet.Frequency.patType;
// 	m_IdAet.aet.Frequency.patPrd = pNewAet->aet.Frequency.patPrd;
// 	m_IdAet.aet.Frequency.position_count = pNewAet->aet.Frequency.position_count;
// 	for( i=0 ; i < m_IdAet.aet.Frequency.position_count ; ++i ) {
// 		// 주파수 스위치 레벨 값은 변환 값으로 저장하도록 한다.
// 		m_IdAet.aet.Frequency.swtVal[i] = pNewAet->aet.Frequency.swtVal[i];
// 	}
//
// 	// PRI 변환
// 	m_IdAet.aet.PRI.type = pNewAet->aet.PRI.type;
// 	m_IdAet.aet.PRI.mean = IDIV( ELDecoder::DecodeToa( (unsigned long long int) pNewAet->aet.PRI.mean ), 1000. );
// 	m_IdAet.aet.PRI.imin = (int) IDIV( ELDecoder::DecodeToa( (unsigned long long int) pNewAet->aet.PRI.imin ), 1000. );
// 	m_IdAet.aet.PRI.imax = (int) ( IDIV( ELDecoder::DecodeToa( (unsigned long long int) pNewAet->aet.PRI.imax ), 1000. ) );
// 	m_IdAet.aet.PRI.patType = pNewAet->aet.PRI.patType;
// 	m_IdAet.aet.PRI.patPrd = pNewAet->aet.PRI.patPrd;
// 	m_IdAet.aet.PRI.position_count = pNewAet->aet.PRI.position_count;
// 	for( i=0 ; i < m_IdAet.aet.PRI.position_count ; ++i ) {
// 		m_IdAet.aet.PRI.swtVal[i] = (int) TOAnsCNV( pNewAet->aet.PRI.swtVal[i] );
// 	}
//
// 	// PW 변환
// 	m_IdAet.aet.PW.imin = pNewAet->aet.PW.imin;
// 	m_IdAet.aet.PW.imax = pNewAet->aet.PW.imax;
//
// 	// 스캔 변환
// 	m_IdAet.aet.Scan.prd = (int) TOAnsCNV( pNewAet->aet.Scan.prd );
// 	m_IdAet.aet.Scan.istat = pNewAet->aet.Scan.istat;
// 	m_IdAet.aet.Scan.itype = pNewAet->aet.Scan.itype;
//
// 	// 신호 세기 변환-거리 측정
// 	//m_IdAet.aet.PA.mean = PACNV( pNewAet->aet.PA.mean );
//
// }
//
// /**
//  * @brief     빔 정보를 식별하기 위해서 식별 하기 위한 단위로 변환함.
//  * @param     *pABTData 식별할 데이터 포인터
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-28, 오후 5:26
//  * @warning
//  */
// void CELSignalIdentifyAlg::ConvertToIdentifyAet( SELABTDATA *pABTData )
// {
// 	int i;
//
// 	//////////////////////////////////////////////////////////////////////////
// 	// 위협 데이터를 신호 식별하기 위한 내부 변수 복사
// 	//
// 	m_IdAet.aet.GABTID = pABTData->uiAETID;
//
// 	// newaet 구조체로 입력되지 않을 경우에, 아래를 수행하여 각 속성값을 복사한다.
// 	// 식별할 속성 단위로 RES. 화하여 값을 변환함.
// 	m_IdAet.aet.ucSignalType = (unsigned char ) ( pABTData->sigInfo.iSignalType );
//
// 	// MOP 형태 저장
// 	m_IdAet.aet.Mop.type = (unsigned char ) ( pABTData->intraInfo.iType );
//
// 	// 주파수 세부 정보
// 	m_IdAet.aet.Frequency.type = pABTData->freqDInfo.iType;
// 	m_IdAet.aet.Frequency.band = -1;
// 	m_IdAet.aet.Frequency.imax = (int) pABTData->freqInfo.iMax;
// 	m_IdAet.aet.Frequency.mean = (int) pABTData->freqInfo.iMean;
// 	m_IdAet.aet.Frequency.imin = (int) pABTData->freqInfo.iMin;
// 	m_IdAet.aet.Frequency.patPrd = (float) pABTData->freqDInfo.iChangePeriod;
// 	m_IdAet.aet.Frequency.patType = pABTData->freqDInfo.iPatternType;
// 	m_IdAet.aet.Frequency.position_count = pABTData->freqDInfo.iPositionCount;
// 	for( i=0 ; i < MAX_FREQ_PRI_STEP ; ++i ) {
// 		m_IdAet.aet.Frequency.swtVal[i] = IDIV( pABTData->freqDInfo.iSeq[i], 1000 );
// 	}
//
// 	// PRI 세부 정보
// 	m_IdAet.aet.PRI.type = pABTData->priDInfo.iType;
// 	m_IdAet.aet.PRI.imax = pABTData->priInfo.iMax;
// 	m_IdAet.aet.PRI.mean = pABTData->priInfo.iMean;
// 	m_IdAet.aet.PRI.imin = pABTData->priInfo.iMin;
// 	m_IdAet.aet.PRI.jtrPer = (float) pABTData->priDInfo.iPRIJitterRatio;
// 	m_IdAet.aet.PRI.patPrd = (float) pABTData->priDInfo.iChangePeriod;
// 	m_IdAet.aet.PRI.patType = pABTData->priDInfo.iPatternType;
// 	m_IdAet.aet.PRI.position_count = pABTData->priDInfo.iPositionCount;
// 	for( i=0 ; i < MAX_FREQ_PRI_STEP ; ++i ) {
// 		m_IdAet.aet.PRI.swtVal[i] = IDIV( pABTData->priDInfo.iSeq[i], 1000 );
// 	}
// 	//memcpy( m_IdAet.aet.PRI.swtVal, pABTData->priDInfo.iSeq, sizeof(pABTData->priDInfo.iSeq) );
//
// 	// PW 변환
// 	m_IdAet.aet.PW.imax = (int) ( pABTData->pwInfo.iMax + 0.5);
// 	m_IdAet.aet.PW.mean = (int) ( pABTData->pwInfo.iMean + 0.5);
// 	m_IdAet.aet.PW.imin = (int) ( pABTData->pwInfo.iMin + 0.5);
//
// 	// 스캔 변환
// 	m_IdAet.aet.Scan.istat = 0;
// 	m_IdAet.aet.Scan.itype = pABTData->scanInfo.iType;
// 	m_IdAet.aet.Scan.prd = pABTData->scanInfo.iPeriod;
//
// 	//////////////////////////////////////////////////////////////////////////
// 	// 위치 산출
// 	if( pABTData->peInfo.enValid == E_EL_PESTAT_SUCCESS ) {
// 		m_IdAet.ext.posEst.dEstLatitude = DLATITUDE2LAT( pABTData->peInfo.iLatitude );
// 		m_IdAet.ext.posEst.dEstLongitude = DLONGITUDE2LONG( pABTData->peInfo.iLongitude );
// 	}
// 	else {
// 		/*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
// 		*/
// 		//m_IdAet.ext.posEst.dEstLatitude = m_IdAet.ext.posEst.dEstLongitude = -180.0;
// 		m_IdAet.ext.posEst.dEstLongitude = -180.0;
// 		m_IdAet.ext.posEst.dEstLatitude = -180.0;
// 	}
//
// 	// 후보 개수 클리어
// 	m_IdAet.ext.id.usCoCandidate = 0;
//
// 	//////////////////////////////////////////////////////////////////////////
// 	//
// 	SetOptionParameter( pABTData );
// }
//
// /**
//  * @brief     LOB 정보를 식별하기 위해서 식별할 단위로 변환한다.
//  * @param     *pLOBDataGroup 식별할 LOB 데이터
//  * @param     *pstPosData 위치 산출 값
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-02-16, 오후 1:34
//  * @warning
//  */
// void CELSignalIdentifyAlg::ConvertToIdentifyAet( SRxLOBDataGroup *pLOBDataGroup, SPosEstData *pstPosData )
// {
// 	int i;
//
// 	//////////////////////////////////////////////////////////////////////////
// 	// 위협 데이터를 신호 식별하기 위한 내부 변수 복사
// 	//
// 	m_IdAet.aet.GABTID = pLOBDataGroup->uiAETID;
//
// 	// newaet 구조체로 입력되지 않을 경우에, 아래를 수행하여 각 속성값을 복사한다.
// 	// 식별할 속성 단위로 RES. 화하여 값을 변환함.
// 	m_IdAet.aet.ucSignalType = (unsigned char ) ( pLOBDataGroup->iSignalType );
//
// 	// MOP 형태 저장
// 	m_IdAet.aet.Mop.type = (unsigned char) pLOBDataGroup->iMOPType;
//
// 	// 주파수 세부 정보
// 	m_IdAet.aet.Frequency.type = pLOBDataGroup->iFreqType;
// 	m_IdAet.aet.Frequency.band = -1;
// 	m_IdAet.aet.Frequency.imax = pLOBDataGroup->iMaxFreq;
// 	m_IdAet.aet.Frequency.mean = pLOBDataGroup->iMeanFreq;
// 	m_IdAet.aet.Frequency.imin = pLOBDataGroup->iMinFreq;
// 	m_IdAet.aet.Frequency.patPrd = (float) pLOBDataGroup->iFreqChangePeriod;
// 	m_IdAet.aet.Frequency.patType = pLOBDataGroup->iFreqPatternType;
// 	m_IdAet.aet.Frequency.position_count = pLOBDataGroup->iFreqPositionCount;
// 	for( i=0 ; i < MAX_FREQ_PRI_STEP ; ++i ) {
// 		m_IdAet.aet.Frequency.swtVal[i] = IDIV( pLOBDataGroup->iFreqSeq[i], 1000 );
// 	}
//
// 	// PRI 세부 정보
// 	m_IdAet.aet.PRI.type = pLOBDataGroup->iPRIType;
// 	m_IdAet.aet.PRI.imax = pLOBDataGroup->iMaxPRI;
// 	m_IdAet.aet.PRI.mean = pLOBDataGroup->iMeanPRI;
// 	m_IdAet.aet.PRI.imin = pLOBDataGroup->iMinPRI;
// 	m_IdAet.aet.PRI.jtrPer = (float) ( pLOBDataGroup->iPRIJitterRatio / 10. );
// 	m_IdAet.aet.PRI.patPrd = (float) pLOBDataGroup->iPRIChangePeriod;
// 	m_IdAet.aet.PRI.patType = pLOBDataGroup->iPRIPatternType;
// 	m_IdAet.aet.PRI.position_count = pLOBDataGroup->iPRIPositionCount;
// 	// memcpy( m_IdAet.aet.PRI.swtVal, pLOBDataGroup->iPRISeq, sizeof( int ) * MAX_FREQ_PRI_STEP );
// 	for( i=0 ; i < MAX_FREQ_PRI_STEP ; ++i ) {
// 		m_IdAet.aet.PRI.swtVal[i] = IDIV( pLOBDataGroup->iPRISeq[i], 1000 );
// 	}
//
// 	m_IdAet.aet.iPulsePerGroup = pLOBDataGroup->iPulsePerGrp;
//
// 	// PW 변환
// 	m_IdAet.aet.PW.imax = pLOBDataGroup->iMaxPW;
// 	m_IdAet.aet.PW.mean = pLOBDataGroup->iMeanPW;
// 	m_IdAet.aet.PW.imin = pLOBDataGroup->iMinPW;
//
// 	// 스캔 변환
// 	m_IdAet.aet.Scan.istat = 0;
// 	m_IdAet.aet.Scan.itype = pLOBDataGroup->iScanType;
// 	m_IdAet.aet.Scan.prd = pLOBDataGroup->iScanPeriod;
//
// 	// 후보 개수 클리어
// 	m_IdAet.ext.id.usCoCandidate = 0;
//
// 	//////////////////////////////////////////////////////////////////////////
// 	//
// 	SetOptionParameter( pLOBDataGroup );
//
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CED 레이더모드 주파수 범위별로 레이더 모드를 테이블화한다.
        \author   조철희
        \return   void
        \version  0.0.33
        \date     2008-07-22 12:51:07
        \warning
*/
void CELSignalIdentifyAlg::MakeFreqBand()
{
    UINT i, j, l;
    UINT istart, iend, iHistSize;

    UINT total_bin_count;
    UINT *pHist;

    STR_FLIB *theFLib;

    theFLib = m_pFLib;

    /*! \bug  	음수값을 unsigned type으로 변환을 자제해야 한다.
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2014-02-02 13:53:04
    */
    int freq_low;
    UINT opt_count, total_count;

    int preRadarModeIndex;

    memset( theFLib, _spZero, sizeof( STR_FLIB ) * ( NO_FLIB_BAND + 1 ) );

    iHistSize = ( MAX_FRQ_MHZ / FLIB_FREQ_RES_MHZ ) + 1;
    pHist = ( UINT * ) malloc( (UINT)( iHistSize * sizeof(int) ) );
    if( pHist == NULL ) { //DTEC_NullPointCheck
        printf( "\n 메모리가 부족해서 히스토그램을 위한 메모리를 할당하지 못했습니다 !" );
    }
    else {
        memset( pHist, _spZero, iHistSize * sizeof(int) );

        /*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2014-01-24 17:11:34
        */
        m_total_ced = 0;
        total_bin_count = 0;

        // DB로부터 CED 라이브러리 테이블화 작업
        SRadarMode *pRadarMode;

        pRadarMode = m_pRadarMode;
        UINT uiSize = (UINT) m_iRadarMode;

        if( uiSize != 0 ) {
            preRadarModeIndex = -1;

            for( i=0 ; i < uiSize ; ++i ) {
                // 이전 레이더 모드 인덱스 값과 다른지를 검사
                if( pRadarMode->iRadarModeIndex != preRadarModeIndex ) {
                    if( pRadarMode->fRF_TypicalMin > 0 && pRadarMode->fRF_TypicalMax > 0 ) {
                        istart = F_NDIV( pRadarMode->fRF_TypicalMin, FLIB_FREQ_RES_MHZ );
                        iend   = C_NDIV( pRadarMode->fRF_TypicalMax, FLIB_FREQ_RES_MHZ );

                        for( l=istart ; l <= iend ; ++l ) {
                            if( l >= iHistSize ) {
                                ++ pHist[ iHistSize - 1 ];
                            }
                            else {
                                ++ pHist[ l ];
                            }

                            ++ total_bin_count;
                        }

                        ++ m_total_ced;

                    }
                    else {
                        TRACE( "\n:::::" );
                    }

                    preRadarModeIndex = pRadarMode->iRadarModeIndex;
                }

                ++ pRadarMode;
            }
        }

        /*! \bug  UDF 개수와 주파수 밴드 개수를 비교함.
                \date 2008-11-05 21:25:02, 조철희
        */
        // 주파수 식별 밴드 개수 보다 많을 경우에는 개수를 optimal 하게 나눠서 하게 한다.
        if( total_bin_count >= NO_FLIB_BAND ) {
            UINT freq_div = UDIV( UDIV(MAX_FRQ_MHZ,1000), NO_FLIB_BAND );

            opt_count = C_NDIV( total_bin_count, NO_FLIB_BAND );
            /*! \bug  	음수값을 unsigned type으로 변환을 자제해야 한다.
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2014-02-02 13:57:06
            */
            if( opt_count == (UINT) _spZero ) {
                opt_count = 1;
            }

            /*! \bug  	음수값을 unsigned type으로 변환을 자제해야 한다.
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2014-02-02 13:57:06
            */
            freq_low = (int) _spZero;

            total_count = 0L;
            /*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2014-01-24 17:10:50
            */
            j = 0;
            for( i=0 ; i < iHistSize ; ++i ) {
                total_count += pHist[i];

                if( total_count >= opt_count ) {
                    /*! \bug  	음수값을 unsigned type으로 변환을 자제해야 한다.
                            \author 조철희 (churlhee.jo@lignex1.com)
                            \date 	2014-02-02 13:56:11
                    */
                    //if( j >= NO_FLIB_BAND ) {
                    if( j >= (int) NO_FLIB_BAND ) { //DTEC_Else
                        continue;
                    }

                    theFLib[j].frq.ilow = freq_low;
                    theFLib[j].frq.ihgh = IMUL( ( j + 1 ), freq_div );

                    freq_low = theFLib[j].frq.ihgh + 1;

                    total_count -= opt_count;

                    ++ j;
                }
            }
        }
        // 주파수 식별 밴드 개수 보다 적을 경우에는 고정 주파수 대역으로 나눈다.
        else {
            UINT freq_div = UDIV( (MAX_FRQ_MHZ - MIN_FRQ_MHZ), NO_FLIB_BAND );

            freq_low = _spZero;
            /*! \bug  	음수값을 unsigned type으로 변환을 자제해야 한다.
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2014-02-02 13:55:06
            */
            for( i=0 ; i < (int) NO_FLIB_BAND ; ++i ) {
                theFLib[i].frq.ilow = freq_low;
                theFLib[i].frq.ihgh = freq_low + (int) freq_div;

                freq_low = theFLib[i].frq.ihgh + 1;
            }
        }

        free( pHist );
    }
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    식별 테이블화를 구성한다.
        \author   조철희
        \return   void
        \version  0.0.34
        \date     2008-07-31 06:40:48
        \warning
*/
void CELSignalIdentifyAlg::MakeFreqLibTable()
{
    int l;
    STR_FLOWHIGH band=STR_FLOWHIGH();

    UINT i, in, inSum, uicount;

    STR_FLIB *theFLib;

    int preRadarModeIndex;

    if( m_total_ced != _spZero ) {
        UINT uiSize;
        SRadarMode *pRadarMode;

        pRadarMode = m_pRadarMode;
        uiSize = (UINT) m_iRadarMode;

        if( uiSize != 0 ) {
            preRadarModeIndex = -1;
            for( i=0 ; i < uiSize ; ++i ) {
                band.ilow = (int) BandSelect( 0, (UINT) NO_FLIB_BAND-1, (int) F_UDIV( pRadarMode->fRF_TypicalMin, 1 ) );
                band.ihgh = (int) BandSelect( 0, (UINT) NO_FLIB_BAND-1, (int) F_UDIV( pRadarMode->fRF_TypicalMax, 1 ) );

                if( pRadarMode->iRadarModeIndex != preRadarModeIndex ) {
                    theFLib = & m_pFLib[band.ilow];
                    for( l=band.ilow ; l <= band.ihgh ; ++l ) {
                        theFLib->pIdxRadarMode[ theFLib->uicount++ ] = pRadarMode;

                        ++ theFLib;
                    }

                    preRadarModeIndex = pRadarMode->iRadarModeIndex;
                }

                ++ pRadarMode;

            }
        }

        theFLib = & m_pFLib[0];
        for( i=0 ; i <= NO_FLIB_BAND ; ++i ) {
            inSum = _spZero;
            uicount = theFLib->uicount;

            // 주파수 Fixed에 대해서 식별 테이블화 구성
            in = ArrangeLib2( & theFLib->pIdxRadarMode[inSum], uicount, _FIXED, theFLib->pLib[_FIXED] );
            inSum += in;

            // 주파수 Agile에 대해서 식별 테이블화 구성
            uicount -= in;
            in = ArrangeLib2( & theFLib->pIdxRadarMode[inSum], uicount, _RANDOM_AGILE, theFLib->pLib[_RANDOM_AGILE] );
            inSum += in;

            // 주파수 패턴에 대해서 식별 테이블화 구성
            uicount -= in;
            in = ArrangeLib2( & theFLib->pIdxRadarMode[inSum], uicount, _PATTERN_AGILE, theFLib->pLib[_PATTERN_AGILE] );
            inSum += in;

            // 주파수 호핑에 대해서 식별 테이블화 구성
            uicount -= in;
            in = ArrangeLib2( & theFLib->pIdxRadarMode[inSum], uicount, _HOPPING, theFLib->pLib[_HOPPING] );
            inSum += in;

            // 주파수 Unknown에 대해서 식별 테이블화 구성
            uicount -= in;
            in = ArrangeLib2( & theFLib->pIdxRadarMode[inSum], uicount, _UNKNOWN_FT, theFLib->pLib[_UNKNOWN_FT] );
            inSum += in;

            ++ theFLib;
        }
    }
    else {
        printf( "\t [W] CED 데이터베이스에 항목이 없어서 주파수 테이블화 작업을 할 수 없습니다.\n" );
        Log( enError, "[W] RADARMODE 테이블에 항목이 없어서 주파수 테이블화 작업을 할 수 없습니다." );
    }
}

/**
 * @brief     주파수 및 PRI 형태를 참고하여 식별 테이블화를 구성한다.
 * @param     SRadarMode * inLib
 * @param     UINT count
 * @param     FREQ_TYPE frqType
 * @param     STR_LIB_RANGE * pLibRange
 * @param     EnumLibType eLibType
 * @return    UINT
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-01-31, 오후 9:10
 * @warning
 */
UINT CELSignalIdentifyAlg::ArrangeLib2( SRadarMode **inLib, UINT uicount, FREQ_TYPE frqType, STR_LIB_RANGE *pLibRange )
{
    UINT i;
    UINT incNoEid=_spZero;

    SRadarMode *bkupLIBINDEX;

    SRadarMode **pLibIndex, **pFrqEid;

    if( uicount != 0 ) {
        // 1. D&S 에 대한 정렬
        pLibIndex = inLib;
        pFrqEid = inLib;
        (pLibRange+_DWELL)->from = pFrqEid;
        (pLibRange+_DWELL)->uicount = _spZero;
        for( i=0 ; i < uicount ; ++i, ++pLibIndex ) {
            if( *pLibIndex == NULL || CheckFreqType( frqType, *pLibIndex ) != TRUE ) { //DTEC_NullPointCheck
                continue;
            }

            // D&S 에 개한 규칙성 추가
            if( (*pLibIndex)->ePRI_Type == RadarModePRIType::enumDwellSWITCH ) {
                bkupLIBINDEX = *pFrqEid;
                *pFrqEid = *pLibIndex;
                *pLibIndex = bkupLIBINDEX;

                ++ pFrqEid;
                ++ incNoEid;

                ++ (pLibRange+_DWELL)->uicount;	// count of IPL(Stable)
            }

        }

        // 2. Stable 에 대한 정렬
        pLibIndex = pFrqEid;
        (pLibRange+_STABLE)->from = pFrqEid;
        (pLibRange+_STABLE)->uicount = _spZero;
        for( i=incNoEid ; i < uicount ; ++i, ++pLibIndex ) {
            if( *pLibIndex == NULL || CheckFreqType( frqType, *pLibIndex ) != TRUE ) { //DTEC_NullPointCheck
                continue;
            }

            // Stable 에 개한 규칙성 추가
            if( (*pLibIndex)->ePRI_Type == RadarModePRIType::enumStable ) {
                    bkupLIBINDEX = *pFrqEid;
                    *pFrqEid = *pLibIndex;
                    *pLibIndex = bkupLIBINDEX;

                    ++ pFrqEid;
                    ++ incNoEid;

                    ++ ( (pLibRange+_STABLE)->uicount );
            }
        }

        // 3. Stagger 에 대한 정렬
        pLibIndex = pFrqEid;
        (pLibRange+_STAGGER)->from = pFrqEid;
        (pLibRange+_STAGGER)->uicount = _spZero;
        for( i=incNoEid ; i < uicount ; ++i, ++pLibIndex ) {
            if( *pLibIndex == NULL || CheckFreqType( frqType, *pLibIndex ) != TRUE ) { //DTEC_Else
                continue;
            }

            // Stagger 에 개한 규칙성 추가
            if( (*pLibIndex)->ePRI_Type == RadarModePRIType::enumSTAGGER ) {
                bkupLIBINDEX = *pFrqEid;
                *pFrqEid = *pLibIndex;
                *pLibIndex = bkupLIBINDEX;

                ++ pFrqEid;
                ++ incNoEid;                    // next loop initial val.

                ++ (pLibRange+_STAGGER)->uicount;    // count of IPL(Stable)
            }
        }

        // 4. 패턴 에 대한 정렬
        pLibIndex = pFrqEid;
        (pLibRange+_JITTER_PATTERN)->from = pFrqEid;		// Jitter IPL range
        (pLibRange+_JITTER_PATTERN)->uicount = _spZero;		// Jitter IPL range
        for( i=incNoEid ; i < uicount ; ++i, ++pLibIndex ) {
            if( *pLibIndex == NULL || CheckFreqType( frqType, *pLibIndex ) != TRUE ) { //DTEC_NullPointCheck
                continue;
            }

            // 패턴 에 개한 규칙성 추가
            // Sliding
            if( (*pLibIndex)->ePRI_Type == RadarModePRIType::enumPATTERN ) {
                bkupLIBINDEX = *pFrqEid;
                *pFrqEid = *pLibIndex;
                *pLibIndex = bkupLIBINDEX;

                ++ pFrqEid;
                ++ incNoEid;

                ++ (pLibRange+_JITTER_PATTERN)->uicount;
            }
        }

        // 5. 지터 에 대한 식별
        pLibIndex = pFrqEid;
        (pLibRange+_JITTER_RANDOM)->from = pFrqEid;		// Pattern IPL range
        (pLibRange+_JITTER_RANDOM)->uicount = _spZero;
        for( i=incNoEid ; i < uicount ; ++i, ++pLibIndex ) {
            if( *pLibIndex == NULL || CheckFreqType( frqType, *pLibIndex ) != TRUE ) { //DTEC_NullPointCheck
                continue;
            }

            if( (*pLibIndex)->ePRI_Type == RadarModePRIType::enumJITTER ) {
                bkupLIBINDEX = *pFrqEid;
                *pFrqEid = *pLibIndex;
                *pLibIndex = bkupLIBINDEX;

                ++ pFrqEid;
                ++ incNoEid;

                ++ (pLibRange+_JITTER_RANDOM)->uicount;
            }
        }

        // 7. enumUndefinedPRI_LegacyType 에 대한 식별
        pLibIndex = pFrqEid;
        (pLibRange+_IGNORE_PRI)->from = pFrqEid;		// Pattern IPL range
        (pLibRange+_IGNORE_PRI)->uicount = _spZero;
        if( incNoEid < uicount ) {
            LogPrint( "\n 미정의된 레이더 모드[%d] 주파수 형태[%d] : " , uicount, frqType );
            for( i=incNoEid ; i < uicount ; ++i, ++pLibIndex ) {
                if( *pLibIndex == NULL || CheckFreqType( frqType, *pLibIndex ) != TRUE ) { //DTEC_NullPointCheck
                    if( *pLibIndex == NULL ) {
                        LogPrint( "잘못된 인덱스 !!!" );
                    }
                    else {
                        LogPrint( "[%d]" , (*pLibIndex)->iRadarModeIndex );
                    }
                    continue;
                }

                if( true /* || (*pLibIndex)->ePRI_LagacyType == enumUndefinedPRI_LegacyType */ ) {
                    bkupLIBINDEX = *pFrqEid;
                    *pFrqEid = *pLibIndex;
                    *pLibIndex = bkupLIBINDEX;

                    ++ pFrqEid;
                    ++ incNoEid;

                    ++ (pLibRange+_IGNORE_PRI)->uicount;
                }
            }
        }
    }

    return incNoEid;
}

/**
 * @brief     레이더 모드에서 입력한 형태별로 검증한다.
 * @param     FREQ_TYPE frqType
 * @param     SRadarMode * pRadarMode
 * @param     frqType
 * @return    BOOL
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-10-24, 오후 8:37
 * @warning
 */
BOOL CELSignalIdentifyAlg::CheckFreqType( FREQ_TYPE frqType, SRadarMode *pRadarMode )
{
    //char *pMopCode1;
    BOOL bRet = FALSE;

    //pMopCode1 = pRadarMode->strModulationCode.GetBuffer();

    switch( frqType ) {
        //case _CHIRP_UP :
        //case _CHIRP_DN :
        //case _PMOP :
        //case _UNKNOWN_FT :
        case MAX_FRQTYPE :
        case _IGNORE_FREQ :
            { //DTEC_Else

            }
            break;

        case _FIXED :
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumFIXED ) {
                bRet = TRUE;
            }
            break;

        case _RANDOM_AGILE :
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumAGILE ) {
                bRet = TRUE;
            }
            break;

        case _HOPPING :
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumHOPPING ) {
                bRet = TRUE;
            }
            break;

        case _PATTERN_AGILE :
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumPATTERN ) {
                bRet = TRUE;
            }
            break;

        default :
            { //DTEC_Else
                bRet = TRUE;
                //, , , _IGNORE_FREQ, _CHIRP_UP, _CHIRP_DN, _PMOP, _UNKNOWN_FT, MAX_FRQTYPE
            }
            break;
    }

    return bRet;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    입력한 주파수 범위에 따라서 식별 테이블화의 인덱스를 얻는다.
        \author   조철희
        \param    from 인자형태 UINT
        \param    to 인자형태 UINT
        \param    searchVal 인자형태 int
        \return   UINT
        \version  0.0.34
        \date     2008-07-31 06:56:18
        \warning
*/
UINT CELSignalIdentifyAlg::BandSelect( int from, int to, int searchVal ) //#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found)
{
    UINT band, div2;

    div2 = ( to + from ) / 2;

    if( abs( (int)(from-to) ) <= 1 ) {
        if( m_pFLib[from].frq.ihgh < searchVal ) {
            return to;
        }
        else {
            return from;
        }

    }

    if( m_pFLib[div2].frq.ilow >= searchVal ) {
        band = BandSelect( from, div2, searchVal );
    }
    else {
        band = BandSelect( div2, to, searchVal );
    }

    return band;
}

/*!
 * @brief     레이더 모드의 우선 순위로 식별 결과를 정렬한다.
 * @return    void
 * @param     void
 * @version   1.0
 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희
 * @date      2015-01-04 오후 2:07
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyPriority()
{
    UINT i, j;

    j = 0;
    for( i=0 ; i < m_toLib ; ++i ) {
        SRadarMode* pRadarMode;

        pRadarMode = m_pIdResult[i].pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( true /* m_optParameter.tl.iThreatLevel <= (int) pRadarMode->nPriority */ ) {
            m_pIdResult[j].pIdxRadarMode = m_pIdResult[i].pIdxRadarMode;
            ++ j;
        }

    }

    m_toLib = j;

}

/**
 * @brief     최종 식별된 위협 정보를 입력 위협 데이터에 저장한다. (수신 위협 데이테에 따른)
 * @param     I_AET_ANAL * pIAetAnal
 * @param     I_AET_DATA * pIAetData
 * @param     BOOL bMakeH0000
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-02-16, 오후 3:39
 * @warning
 */
void CELSignalIdentifyAlg::CopyAmbiguity( I_AET_ANAL *pIAetAnal, I_AET_DATA *pIAetData, BOOL bMakeH0000 )
{
    STR_CEDEOBID_INFO *pLOBDataIdInfo;

    pLOBDataIdInfo = & pIAetAnal->idInfo;

    memset( pLOBDataIdInfo, _spZero, sizeof( STR_CEDEOBID_INFO ) );
    pLOBDataIdInfo->eIdResult = E_EL_PE_UNK_ID;

    pIAetAnal->bCompFreq = true;
    pIAetAnal->bCompPRI = true;

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

        pIAetAnal->bOverCount = false;

        pLOBDataIdInfo->nThreatIndex = m_pEOBResult->nThreatIndex;
        pLOBDataIdInfo->nDeviceIndex = m_pEOBResult->nDeviceIndex;

        //memset( & pIAetAnal->iIdRatio[0], _spZero, sizeof( pIAetAnal->iIdRatio ) );

        //m_IdAet.ext.id.usCoCandidate = 0;

        // 위협 레벨 초기화
        //pIAetAnal->usPriorityLevel = 0;

    }
    else {
        int i, j;
        SRadarMode* pRadarMode;
        //STR_CEDEOB_RESULT *pCEDEOBResult;

        char szELNOT[_MAX_ELNOT_STRING_SIZE_];

        pIAetAnal->bOverCount = ( m_toLib > MAX_IDCANDIDATE );
        /*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2014-01-24 17:08:42
        */
        //pIAetAnal->usCoCandidate = (int) min( m_toLib, MAX_IDCANDIDATE );
        m_nCoIdResult = (int) _min( m_toLib, MAX_IDCANDIDATE );
        //m_IdAet.ext.id.usCoCandidate = pIAetAnal->usCoCandidate;
        pLOBDataIdInfo->nCoRadarModeIndex = m_nCoIdResult;

        for( i=0 ; i < m_nCoIdResult ; ++i ) {
            pLOBDataIdInfo->nRadarModeIndex[i] = m_pIdResult[i].pIdxRadarMode->iRadarModeIndex;
        }

        // 식별 후버 정보
        memset( szELNOT, 0, sizeof(szELNOT) );
        memset( pLOBDataIdInfo->n3LevelRadarModeIndex, 0, sizeof(pLOBDataIdInfo->n3LevelRadarModeIndex) );
        for( i=j=0 ; i < m_nCoIdResult ; ++i ) {
            int iRadarModeIndex;

            iRadarModeIndex = m_pIdResult[i].pIdxRadarMode->iRadarModeIndex;
            pRadarMode = & m_pRadarMode[iRadarModeIndex-1];
            if( pLOBDataIdInfo->n3LevelRadarModeIndex[0] == 0 ||
                ( pLOBDataIdInfo->n3LevelRadarModeIndex[1] == 0 && pLOBDataIdInfo->n3LevelRadarModeIndex[0] != pRadarMode->iRadarIndex ) ||
                ( pLOBDataIdInfo->n3LevelRadarModeIndex[2] == 0 && ( pLOBDataIdInfo->n3LevelRadarModeIndex[0] != pRadarMode->iRadarIndex && pLOBDataIdInfo->n3LevelRadarModeIndex[1] != pRadarMode->iRadarIndex ) ) ) {
                pLOBDataIdInfo->n3LevelRadarModeIndex[j++] = iRadarModeIndex;
                if( j >= THREE_LEVEL_IDCANDIDATE-1 ) {
                    break;
                }
            }
        }

        // 위협 관리를 하기위한 식별 정보를 추가 저장하도록함.
        //pIAetAnal->usEnemyIdentify = false;

        // 위협 ID
        //pIAetAnal->usNoThreat = 0;

    }

}

// //////////////////////////////////////////////////////////////////////////
// /*!
//  * @brief			거리에 대해서 정렬하기 위한 함수이다.
//  * @param     *arg1 비교할 인자1
//  * @param     *arg2 비교할 인자2
//  * @return    같으면 0, 인자1이 크면 1, 인자2가 크면 -1을 리턴한다.
//  * @version   0.0.1
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @date      2013-12-23 오후 8:16
//  * @warning
//  */
// int incIntCompare( const void *arg1, const void *arg2 )
// {
// 	int iRet=0;
// 	const int *p1, *p2;
//
// 	p1 = (int *) const_cast<void*>(arg1);
// 	p2 = (int *) const_cast<void*>(arg2);
//
// 	return *p1 - *p2;
//
// }
//
// /**
//  * @brief     식별 결과에서 레이더 인덱스 순으로 정렬한다.
//  * @param     int * pIndex
//  * @param     int * pCount
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-05, 오후 5:21
//  * @warning
//  */
// void CELSignalIdentifyAlg::SortRadarIndex( int *pCount, int *pIndex, int nMax )
// {
// 	int i, j;
// 	int nCount, nTotal, nMemmove, nLoop;
//
// 	int refPriority, cmpPriority;
//
// 	int nRadarIndex, swapIndex;
//
// 	// 1. 중복된 레이더 인덱스를 제거함.
// 	if( ( pCount != NULL ) && ( pIndex != NULL ) ) {
// 		nLoop = *pCount;
// 		nTotal = *pCount;
//
// 		// qsort( pIndex, (size_t) *pCount, sizeof(int), incIntCompare );
// 		for( i=0 ; i < nLoop-1 ; ++i ) {
// 			nRadarIndex = pIndex[i];
// 			j = i + 1;
// 			nCount = 0;
// 			while( nRadarIndex == pIndex[j++] ) {
// 				++ nCount;
// 				if( j >= nLoop || j >= nMax ) {
// 					break;
// 				}
// 			}
//
// 			nLoop -= nCount;
// 			if( nCount != 0 ) {
// 				nMemmove = nTotal - nCount - ( i + 1 );
// 				memmove( & pIndex[i+1], & pIndex[j-1], (UINT)nMemmove*sizeof(int) );
// 				nTotal -= nCount;
// 			}
//
// 		}
// 		*pCount = nLoop;
//
// 		// 2. 레이더 우선순위로 정렬
// 		for( i=0 ; i < *pCount ; ++i ) {
// 			refPriority = GetRadarPriority( pIndex[i], m_eCEDLibType );
// 			for( j=1 ; j < *pCount ; ++j ) {
// 				cmpPriority = GetRadarPriority( pIndex[j], m_eCEDLibType );
// 				if( refPriority > cmpPriority ) {
// 					swapIndex = pIndex[i];
// 					pIndex[i] = pIndex[j];
// 					pIndex[j] = swapIndex;
//
// 					refPriority = GetRadarPriority( pIndex[i], m_eCEDLibType );
// 				}
// 			}
// 		}
// 	}
//
// }
//
// /**
//  * @brief     중복 데이터를 제거한다.
//  * @param     int * pCount
//  * @param     int * pIndex
//  * @param     int nMax
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @warning
// */
// void CELSignalIdentifyAlg::RemoveDuplicateIndex( int *pCount, int *pIndex, int nMax )
// {
// 	int i, j;
// 	int nCount, nTotal, nMemmove, nLoop;
//
// 	int nIndex;
//
// 	LogPrint( "\n 중복 제거 전 레이더 인덱스[%d] :" , *pCount );
// 	for( i=0 ; i < *pCount ; ++i ) {
// 		LogPrint( "[%d]" , pIndex[i] );
// 	}
//
// 	// 1. 중복된 레이더 인덱스를 제거함.
// 	if( ( pCount != NULL ) && ( pIndex != NULL ) ) {
// 		nLoop = *pCount;
// 		nTotal = *pCount;
//
// 		qsort( pIndex, (size_t) *pCount, sizeof(int), incIntCompare );
// 		for( i=0 ; i < nLoop-1 ; ++i ) {
// 			nIndex = pIndex[i];
// 			j = i + 1;
// 			nCount = 0;
// 			while( nIndex == pIndex[j++] ) {
// 				++ nCount;
// 				if( j >= nLoop || j >= nMax ) {
// 					break;
// 				}
// 			}
//
// 			nLoop -= nCount;
// 			if( nCount != 0 ) {
// 				nMemmove = nTotal - nCount - ( i + 1 );
// 				memmove( & pIndex[i+1], & pIndex[j-1], (UINT)nMemmove*sizeof(int) );
// 				nTotal -= nCount;
// 			}
//
// 		}
// 		*pCount = nLoop;
//
// 	}
//
// 	LogPrint( "\n 중복 제거 후 레이더 인덱스[%d] :" , *pCount );
// 	for( i=0 ; i < *pCount ; ++i ) {
// 		LogPrint( "[%d]" , pIndex[i] );
// 	}
//
// }
//
//////////////////////////////////////////////////////////////////////////
/*! \brief    식별 결과에서 위협 레벨 순으로 정렬한다.
        \author   조철희
        \param    noEMT 인자형태 UINT
        \return   void
        \version  0.0.34
        \date     2008-07-31 10:41:49
        \warning
*/
void CELSignalIdentifyAlg::SortThreatLevel()
{
    //UINT i, j;
    //UINT temp;
    //SRadarMode *pTempRadarMode;

    //bool sorted;

    // 위협 후보 식별을 정렬한다.
    m_nCoIdResult = (int) m_toLib;
// 	for( i=m_toLib ; i > 0 ; --i ) {
// 		sorted = true;
//
// 		for( j=0 ; j < m_toLib-1 ; ++j ) {
// 			SRadarMode* pRadarModeRef, *pRadarModeNxt;
//
// 			pRadarModeRef = m_pIdResult[j].pIdxRadarMode;
// 			if( pRadarModeRef == NULL ) { //DTEC_NullPointCheck
// 				continue;
// 			}
//
// 			pRadarModeNxt = m_pIdResult[j+1].pIdxRadarMode;
// 			if( pRadarModeNxt == NULL ) { //DTEC_NullPointCheck
// 				continue;
// 			}
//
// 			if( m_pIdResult[j].uRatio == m_pIdResult[j+1].uRatio ) {
// 				// 1 순위 : 레이더 우선순위
// 				if( pRadarModeRef->nPriority < pRadarModeNxt->nPriority /* && ( pRadarModeRef->nPriority > 0 && pRadarModeNxt->nPriority > 0 ) */ ) {
// 					pTempRadarMode = m_pIdResult[j+1].pIdxRadarMode;
// 					m_pIdResult[j+1].pIdxRadarMode = m_pIdResult[j].pIdxRadarMode;
// 					m_pIdResult[j].pIdxRadarMode = pTempRadarMode;
//
// 					sorted = false;
//
// 				}
// 				// 2 순위 : 레이더모드 우선순위
// 				else if( pRadarModeRef->nPriority == pRadarModeNxt->nPriority /* || pRadarModeNxt->nPriority <= 0 || pRadarModeNxt->nPriority */ ) {
// 					if( pRadarModeRef->nRadarModenPriority < pRadarModeNxt->nRadarModenPriority /* && ( pRadarModeNxt->nRadarModenPriority > 0 && pRadarModeRef->nRadarModenPriority > 0 ) */ ) {
// 						pTempRadarMode = m_pIdResult[j].pIdxRadarMode;
// 						m_pIdResult[j].pIdxRadarMode = m_pIdResult[j+1].pIdxRadarMode;
// 						m_pIdResult[j+1].pIdxRadarMode = pTempRadarMode;
//
// 						sorted = false;
// 					}
// 					else if( pRadarModeRef->nRadarModenPriority == pRadarModeNxt->nRadarModenPriority /* || pRadarModeNxt->nRadarModenPriority <= 0 || pRadarModeNxt->nRadarModenPriority */ ) {
// 						// 레이더 모드 인데스에서 ELNOT 순으로 정렬
// 						if( IsSortELNOT( pRadarModeRef, pRadarModeNxt ) == true ) {
// 						//if( pRadarModeRef->nRadarModeIndex > pRadarModeNxt->nRadarModeIndex ) {
// 							pTempRadarMode = m_pIdResult[j].pIdxRadarMode;
// 							m_pIdResult[j].pIdxRadarMode = m_pIdResult[j+1].pIdxRadarMode;
// 							m_pIdResult[j+1].pIdxRadarMode = pTempRadarMode;
//
// 							sorted = false;
// 						}
// 					}
// 					else { //DTEC_ELSE
//
// 					}
// 				}
// 				else { //DTEC_ELSE
//
// 				}
// 			}
//
// 		}
//
// 	}

}
//
// //////////////////////////////////////////////////////////////////////////
// /*! \brief    주파수 및 PRI 식별을 수행한다.
// 		\author   조철희
// 		\param    pNewAet 인자형태 STR_NEWAET *
// 		\return   void
// 		\version  0.0.34
// 		\date     2008-08-01 11:08:21
// 		\warning
// */
// void CELSignalIdentifyAlg::IdentifyFreqPRI( STR_NEWAET *pNewAet, EnumLibType eLibType )
// {
// 	STR_LOWHIGH band=STR_LOWHIGH();
//
// 	int *pFrqType, *pPriType;
//
// 	band.ilow = (int) BandSelect( 0, (UINT) NO_FLIB_BAND-1, pNewAet->aet.Frequency.imin*10 );
// 	band.ihgh = (int) BandSelect( 0, (UINT) NO_FLIB_BAND-1, pNewAet->aet.Frequency.imax*10 );
//
// 	// Normal Type에 대해서 비교
// 	if( pNewAet->aet.ucSignalType != ST_CW && pNewAet->aet.ucSignalType != ST_CW_FMOP ) {
// 		pFrqType = & m_HowToId[pNewAet->aet.Frequency.type][pNewAet->aet.PRI.type].frq[0];
// 		pPriType = & m_HowToId[pNewAet->aet.Frequency.type][pNewAet->aet.PRI.type].pri[0];
//
// 		while( *pFrqType >= 0  && *pPriType >= 0 ) { //#FA_C_PotentialUnboundedLoop_T1
// 			if( *pFrqType < 0 || *pPriType < 0 ) { //DTEC_Else
// 				printf( "\n\t [W] Invalid Freq[%d], PRI[%d]" , *pFrqType, *pPriType );
// 				WhereIs;
// 			}
//
// 			FilterBand( & m_theFLib[band.ilow].pLib[*pFrqType][*pPriType], & m_theFLib[band.ihgh].pLib[*pFrqType][*pPriType], & band, & m_toLib );
//
// 			if( m_fromLib != m_toLib ) {
// 				unsigned char nCallFunc;
//
// 				IdentifySigType();
//
// 				nCallFunc = m_FrqIdCallFunc[pNewAet->aet.Frequency.type][*pFrqType];
// 				CallFreqFunc( nCallFunc, pNewAet );
//
// 				nCallFunc = m_PriIdCallFunc[pNewAet->aet.PRI.type][*pPriType];
// 				CallPriFunc( nCallFunc, pNewAet );
//
// 				m_fromLib = m_toLib;
// 			}
//
// 			++ pFrqType;
// 			++ pPriType;
// 		}
// 	}
// 	else {
// 		pFrqType = & m_HowToId[pNewAet->aet.Frequency.type][pNewAet->aet.PRI.type].frq[0];
// 		pPriType = & m_HowToId[pNewAet->aet.Frequency.type][pNewAet->aet.PRI.type].pri[0];
//
// 		while( *pFrqType >= 0  && *pPriType >= 0 ) {
// 			if( *pFrqType < 0 || *pPriType < 0 ) { //DTEC_Else
// 				printf( "\n\t [W] Invalid Freq[%d], PRI[%d]" , *pFrqType, *pPriType );
// 				WhereIs;
// 			}
//
// 			for( int i=0 ; i < MAX_PRITYPE ; ++i ) {
// 				FilterBand( & m_theFLib[band.ilow].pLib[*pFrqType][i], & m_theFLib[band.ihgh].pLib[*pFrqType][i], & band, & m_toLib );
// 			}
//
// 			if( m_fromLib != m_toLib ) {
// 				unsigned char nCallFunc;
//
// 				IdentifySigType();
//
// 				nCallFunc = m_FrqIdCallFunc[pNewAet->aet.Frequency.type][*pFrqType];
// 				CallFreqFunc( nCallFunc, pNewAet );
//
// 				m_fromLib = m_toLib;
// 			}
//
// 			/*! \bug  	음수값을 unsigned type으로 변환을 자제해야 한다.
// 					\author 조철희 (churlhee.jo@lignex1.com)
// 					\date 	2014-02-02 13:39:05
// 			*/
// 			int frqType = *pFrqType;
// 			while( *pFrqType == frqType ) { //#FA_C_PotentialUnboundedLoop_T1
// 				++ pFrqType;
// 				++ pPriType;
// 			}
// 		}
// 	}
// }

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     위협 에미터의 주파수/PRI 식별을 수행한다.
 * @param     I_AET * pIAet
 * @return    void
 * @version   0.0.1
 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-10-09 오후 1:27
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyFreqPRI( SRxLOBData *pLOBData )
{
    STR_FLOWHIGH band=STR_FLOWHIGH();

    unsigned char nCallFunc;

    int *pFrqType = NULL;
    int *pPriType = NULL;

    band.ilow = (int) BandSelect( 0, (UINT)NO_FLIB_BAND-1, (int) F_UDIV( pLOBData->fMinFreq, 1 ) );
    band.ihgh = (int) BandSelect( 0, (UINT)NO_FLIB_BAND-1, (int) C_UDIV( pLOBData->fMaxFreq, 1 ) );

    // 주파수 및 PRI 형태 식별 여부
    if( ( pLOBData->iFreqType > 0 && pLOBData->iFreqType > MAX_FRQTYPE ) ||
        ( pLOBData->iPRIType > 0 && pLOBData->iPRIType > MAX_PRITYPE ) ) { //DTEC_NullPointCheck
        pFrqType = NULL;
        pPriType = NULL;
    }
    else {
        pFrqType = (int *) & m_HowToId[pLOBData->iFreqType][pLOBData->iPRIType].frq[0];
        pPriType = (int *) & m_HowToId[pLOBData->iFreqType][pLOBData->iPRIType].pri[0];
    }

    // 예외처리. 2015.1.22. 이정남  -> 원복. QAC 에러
    if( pFrqType == NULL || pPriType == NULL || pLOBData->iFreqType < 0 || pLOBData->iPRIType < 0) { //DTEC_NullPointCheck
    }
    else {
        while( *pFrqType >= 0  && *pPriType >= 0 ) { //#FA_C_PotentialUnboundedLoop_T2
            if( *pFrqType < 0 || *pPriType < 0 ) { //DTEC_Else
                printf( "\n\t [W] Invalid Freq[%d], PRI[%d]" , *pFrqType, *pPriType );
                WhereIs;
            }
            else {
                // 범위 체크한 경우, 주파수 범위에 밴드를 필터링 하게 함.
                FilterBand( & m_pFLib[band.ilow].pLib[*pFrqType][*pPriType], & m_pFLib[band.ihgh].pLib[*pFrqType][*pPriType], & band, & m_toLib );

                // 식별 테스트 하기위해서 무조건 식별 성공으로 함.
                if( m_fromLib != m_toLib ) {
                    // 1. 신호 형태 식별
                    IdentifySigType( pLOBData->iSignalType );

                    // 4. 주파수 식별
                    nCallFunc = m_FrqIdCallFunc[pLOBData->iFreqType][*pFrqType];
                    CallFreqFunc( nCallFunc, pLOBData );

                    // 5. PRI 식별
                    nCallFunc = m_PriIdCallFunc[pLOBData->iPRIType][*pPriType];
                    CallPriFunc( nCallFunc, pLOBData );

                    // 6. PPG 식별
                    //IdentifyPPG();

                    m_fromLib = m_toLib;
                }
            }

            ++ pFrqType;
            ++ pPriType;
        }
    }
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    주파수 범위 안에 속하는 식별 후보를 찾는다.
        \author   조철희
        \param    frqLow 인자형태 STR_LIB_RANGE *
        \param    frqHgh 인자형태 STR_LIB_RANGE *
        \param    band 인자형태 STR_LOWHIGH *
        \param    cotoIpl 인자형태 UINT *
        \return   void
        \version  0.0.34
        \date     2008-08-01 11:55:08
        \warning
*/
void CELSignalIdentifyAlg::FilterBand( STR_LIB_RANGE *pFrqLow, STR_LIB_RANGE *pFrqHgh, STR_FLOWHIGH *pBand, UINT *pIdxLib )
{
    UINT i, j;
    int refnoIpl;

    SRadarMode **pLeftLib = NULL;
    SRadarMode **pRightLib = NULL;

    pLeftLib = pFrqLow->from;
    pRightLib = pFrqHgh->from;

    // 주파수 테이블화에 데이터가 없을 때 식별 결과는 변경 사항 없이 리턴한다.
    /*! \bug  신뢰성: NULL 체크하여 예외 처리
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2015-10-6 14:07:27
    */
    if( pLeftLib == NULL || pRightLib == NULL || pBand == NULL || *pLeftLib == NULL || *pRightLib == NULL ) { //DTEC_NullPointCheck
        // return;
    }
    else {
        SRadarMode *pRadarMode;

        if( pBand->ihgh == pBand->ilow ) {
            for( i=0 ; i < pFrqLow->uicount ; ++i ) {
                pRadarMode = *pLeftLib;
                if( pRadarMode == NULL ) { //DTEC_NullPointCheck
                    continue;
                }

                pLeftLib++;

                m_pIdResult[(*pIdxLib)++].pIdxRadarMode = pRadarMode;
            }
        }
        else {
            if( pFrqLow->uicount > pFrqHgh->uicount ) {
                for( i=0 ; i < pFrqLow->uicount ; ++i ) {
                    pRadarMode = *pLeftLib;
                    if( pRadarMode == NULL ) { //DTEC_NullPointCheck
                        continue;
                    }

                    pLeftLib++;

                    refnoIpl = pRadarMode->iRadarModeIndex;
                    pRightLib = pFrqHgh->from;
                    for( j=0 ; j < pFrqHgh->uicount ; ++j ) {
                        pRadarMode = *pRightLib;
                        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
                            continue;
                        }

                        pRightLib++;
                        if( refnoIpl == pRadarMode->iRadarModeIndex ) {
                            m_pIdResult[(*pIdxLib)++].pIdxRadarMode = pRadarMode;
                        }
                    }
                }
            }
            else {
                for( i=0 ; i < pFrqHgh->uicount ; ++i ) {
                    pRadarMode = *pRightLib;
                    if( pRadarMode == NULL ) { //DTEC_NullPointCheck
                        continue;
                    }

                    pRightLib++;

                    refnoIpl = pRadarMode->iRadarModeIndex;
                    pLeftLib = pFrqLow->from;
                    for( j=0 ; j < pFrqLow->uicount ; ++j ) {
                        pRadarMode = *pLeftLib;
                        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
                            continue;
                        }

                        pLeftLib++;

                        if( refnoIpl == pRadarMode->iRadarModeIndex ) {
                            m_pIdResult[(*pIdxLib)++].pIdxRadarMode = pRadarMode;
                        }
                    }
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    신호 형태로 신호 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.34
        \date     2008-08-01 12:46:52
        \warning
*/
void CELSignalIdentifyAlg::IdentifySigType( int iSignalType )
{
    UINT i;
    STR_LIB_IDRESULT *pIdxLibAmbi;
    UINT toLib;

    toLib = m_fromLib;
    pIdxLibAmbi = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLibAmbi ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLibAmbi->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        switch( iSignalType ) {
            case SignalType::enumPulsed :
                if( pRadarMode->eSignalType != SignalType::enumPulsed )
                    continue;
                break;

            case SignalType::enumCW :
                if( pRadarMode->eSignalType != SignalType::enumCW )
                    continue;
                break;

            default:
                { //DTEC_Else
                }
                break;
        }

        // 빔 번호 추가
        m_pIdResult[toLib++].pIdxRadarMode = pIdxLibAmbi->pIdxRadarMode;
    }

    m_toLib = toLib;

}

// /*!
//  * @brief     그룹화 펄스 수로 식별을 수행한다.
//  * @return    void
//  * @param     void
//  * @version   1.0
//  예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
//  * @author    조철희
//  * @date      2014-12-30 오후 3:32
//  * @warning
//  */
// void CELSignalIdentifyAlg::IdentifyPPG()
// {
// 	UINT i;
// 	STR_LIB_IDRESULT *pIdxLib;
// 	UINT idxMatch;
//
// 	BOOL bRet = FALSE;
//
// 	idxMatch = m_fromLib;
// 	pIdxLib = & m_pIdResult[m_fromLib];
//
// 	for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
// 		SRadarMode* pRadarMode;
//
// 		pRadarMode = pIdxLib->pIdxRadarMode;
// 		if( pRadarMode == NULL ) { //DTEC_NullPointCheck
// 			continue;
// 		}
//
// 		// 그룹당 PRI 비교 추가
// 		if( pRadarMode->fPRI_PPG_Min < 1.0 || pRadarMode->fPRI_PPG_Max < 1.0 ) {
// 			bRet = CompMarginDiff2( m_optParameter.pulse_per_group, 1.0, 1.0, 0 );
// 		}
// 		else {
// 			bRet = CompMarginDiff2( m_optParameter.pulse_per_group, pRadarMode->fPRI_PPG_Min, pRadarMode->fPRI_PPG_Max, 0 );
// 		}
//
// 		if( bRet == FALSE ) {
// 			continue;
// 		}
// 		else {
// 			m_pIdResult[idxMatch++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
// 		}
// 	}
//
// 	m_toLib = idxMatch;
//
// }
//
// /*!
//  * @brief     MOP 식별을 수행한다.
//  * @return    void
//  * @param     void
//  * @version   1.0
//  예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
//  * @author    조철희
//  * @date      2014-12-30 오후 3:32
//  * @warning
//  */
// void CELSignalIdentifyAlg::IdentifyMOPType()
// {
// 	UINT i;
// 	STR_LIB_IDRESULT *pIdxLibAmbi;
// 	UINT idxMatch;
//
// 	bool bRet = false;
//
// 	// MOP 형태가 Unknown 이면 식별 비교를 무시한다.
// 	if( m_optParameter.mod.bCheckType == false || m_optParameter.mod.iType == E_AET_MOP_UNK )
// 		return;
//
// 	idxMatch = m_fromLib;
// 	pIdxLibAmbi = & m_pIdResult[m_fromLib];
//
// 	for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLibAmbi ) {
// #ifdef CEDEOBLIB
// 		SRadarMode* pRadarMode;
// 		SRadarMOP_CW *pSRadarMOP_CW;
// 		map<int, SRadarMOP_CW>* pMapRadarMOP_CW;
//
// 		if( m_optParameter.mod.bCheckType == true ) {
// 			//pRadarMode = GP_MNGR_CED_LIB2->RTGetRadarModeDataFromMemory( pIdxLibAmbi->nRadarModeIndex, m_eCEDLibType );
// 			pRadarMode = pIdxLibAmbi->pIdxRadarMode;
// 			if( pRadarMode == nullptr ) { //DTEC_NullPointCheck
// 				continue;
// 			}
//
// 			pMapRadarMOP_CW = & pRadarMode->mapRadarMOP_CW;
//
// 			if( pMapRadarMOP_CW->size() == 0 )
// 				bRet = false;
// 			else {
// 				bRet = false;
// 				// 레이더 모드 중에서 에러 상태를 확인함.
// 				for( auto iter = pMapRadarMOP_CW->begin() ; iter != pMapRadarMOP_CW->end()  ; iter++ ) {
// 					pSRadarMOP_CW = & (*iter).second;
//
// 					// CED에 극성 정보가 없을 때, 식별 비교를 무시한다.
// 					if( pSRadarMOP_CW->eMOP_CW_ModulationType != MOP_CW_ModulationType::enumUnknown ) {
// 						switch( m_optParameter.mod.iType ) {
// 							case E_AET_MOP_UNK :
// 								bRet = true;
// 								break;
//
// 							case E_AET_MOP_NM :
// 								if( pSRadarMOP_CW->eMOP_CW_ModulationType == MOP_CW_ModulationType::enumUnModulated )
// 									bRet = true;
// 								break;
//
// 							case E_AET_MOP_PSK :
// 								if( pSRadarMOP_CW->eMOP_CW_ModulationType == MOP_CW_ModulationType::enumPhase )
// 									bRet = true;
// 								break;
//
// 							case E_AET_MOP_FSK :
// 							case E_AET_MOP_LFM :
// 							case E_AET_MOP_NLFM :
// 								if( pSRadarMOP_CW->eMOP_CW_ModulationType == MOP_CW_ModulationType::enumFrequency )
// 									bRet = true;
// 								break;
// 						}
// 					}
// 					else {
// 						bRet = true;
// 					}
// 				}
// 			}
// 		}
// #else
// 		SCEDBeamData *pBeamData;
//
// 		bRet = true;
// 		if( m_optParameter.mod.bCheckType == true ) {
// 			pBeamData = GP_MNGR_CED_LIB->GetBeamData( pIdxLibAmbi->nRadarModeIndex, m_eCEDLibType );
//
// 			switch( m_optParameter.mod.iType ) {
// 				case E_AET_MOP_NM :
// 					if( pBeamData->eMOPType != E_EL_MOP_NON_MODULATION )
// 						continue;
// 					break;
//
// 				case E_AET_MOP_PSK :
// 					if( pBeamData->eMOPType != E_EL_MOP_PMOP_PSK && pBeamData->eMOPType != E_EL_MOP_UNKNOWN )
// 						continue;
// 					break;
//
// 				case E_AET_MOP_FSK :
// 					if( pBeamData->eMOPType != E_EL_MOP_FMOP_FSK && pBeamData->eMOPType != E_EL_MOP_UNKNOWN )
// 						continue;
// 					break;
//
// 				case E_AET_MOP_LFM :
// 					if( pBeamData->eMOPType != E_EL_MOP_FMOP_LFM && pBeamData->eMOPType != E_EL_MOP_UNKNOWN )
// 						continue;
// 					break;
//
// 				case E_AET_MOP_NLFM :
// 					if( pBeamData->eMOPType != E_EL_MOP_FMOP_NLFM && pBeamData->eMOPType != E_EL_MOP_UNKNOWN )
// 						continue;
// 					break;
// 				}
// 		}
// #endif
//
// 		// 2. 빔 번호 추가
// 		if( bRet == true ) {
// 			m_pIdResult[idxMatch++].pIdxRadarMode = pIdxLibAmbi->pIdxRadarMode;
// 		}
// 	}
//
// 	m_toLib = idxMatch;
// }
//
// /*!
//  * @brief     극성 신호 식별을 수행한다.
//  * @return    void
//  * @param     void
//  * @version   1.0
//  예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
//  * @author    조철희
//  * @date      2014-12-31 오전 9:23
//  * @warning
//  */
// void CELSignalIdentifyAlg::IdentifyPololizationType()
// {
// 	UINT i;
// 	STR_LIB_IDRESULT *pIdxLibAmbi;
// 	UINT idxMatch;
//
// 	// POL 형태가 Unknown 이면 식별 비교를 무시한다.
// 	if( m_optParameter.pol.bCheckType == false || m_optParameter.pol.iType == E_AET_POLIZATION_UNK ) {
// 		// return;
// 	}
// 	else {
// 		idxMatch = m_fromLib;
// 		pIdxLibAmbi = & m_pIdResult[m_fromLib];
//
// 		for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLibAmbi ) {
// 			SRadarMode* pRadarMode;
//
// 			pRadarMode = pIdxLibAmbi->pIdxRadarMode;
// 			if( pRadarMode == NULL ) { //DTEC_NullPointCheck
// 				continue;
// 			}
//
// 			// 2. 빔 번호 추가
// 			m_pIdResult[idxMatch++].pIdxRadarMode = pIdxLibAmbi->pIdxRadarMode;
// 		}
//
// 		m_toLib = idxMatch;
// 	}
//
// }

/*!
 * @brief     주파수 형태를 무시한 경우의 주파수 범위에 대한 식별 처리를 수행한다.
 * @return    void
 * @param     STR_NEWAET * pNewAet
 * @version   1.0
 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희
 * @date      2014-12-28 오후 1:47
 * @warning
 */
void CELSignalIdentifyAlg::FIdentifyFreq( SRxLOBData *pLOBData )
{
    UINT i, toLib;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
            SRadarMode* pRadarMode;

            pRadarMode = pIdxLib->pIdxRadarMode;
            if( pRadarMode == NULL ) { //DTEC_NullPointCheck
                continue;
            }

            /*! \todo   주파수를 곱해서 연산하는데 주파수 테이블부터 연산을 고려하여 테이블하도록 수정
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2015-10-20 02:08:45
            */
            if( CompMarginDiff<float>( pLOBData->fMinFreq, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == TRUE ||
                CompMarginDiff<float>( pLOBData->fMaxFreq, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == TRUE ) {
                ; //bret = true;
            }
            else {
                continue;
            }

    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    주파수 고정-고정 신호에 대해서 신호 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.34
        \date     2008-08-01 14:51:01
        \warning
*/
void CELSignalIdentifyAlg::FIdentifyFixFix( SRxLOBData *pLOBData )
{
    UINT i, toLib;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        /*! \todo   주파수를 곱해서 연산하는데 주파수 테이블부터 연산을 고려하여 테이블하도록 수정
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2015-10-20 02:08:45
        */
        if( CompMarginDiff<float>( pLOBData->fMeanFreq, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == TRUE ||
                CompMarginDiff<float>( pLOBData->fMeanFreq, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == TRUE ) {
            ; //bret = true;
        }
        else {
            continue;
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    주파수 고정-호핑 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.34
        \date     2008-08-01 16:04:10
        \warning
*/
void CELSignalIdentifyAlg::FIdentifyFixHop( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;
    STR_LIB_IDRESULT *pIdxLib;

    BOOL bret;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[ m_fromLib ];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        bret = FALSE;
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        // 주파수 호핑 특성 여부
// 		for( auto iter = pRadarMode->mapRadarRF_Sequence.begin(); iter != pRadarMode->mapRadarRF_Sequence.end(); iter++ ) { //#FA_C_PotentialUnboundedLoop_T3
// 			SRadarRF_Sequence *pstSRadarRF_Sequence = & (*iter).second;
//
// 			SRadarRF_SequenceNumIndex *pRF_SequenceNumIndex;
// 			vector<SRadarRF_SequenceNumIndex> *pvecRF_NumIndex;
//
// 			pvecRF_NumIndex = & pstSRadarRF_Sequence->vecRF_NumIndex;
// 			pRF_SequenceNumIndex = & pvecRF_NumIndex->at(0);
//
// 			bret = CompSwitchLevel( pLOBData->fMinFreq, & pRadarMode->vecRadarRF_Values, pRF_SequenceNumIndex, pvecRF_NumIndex->size(), pRadarMode );
// 			if( bret == FALSE ) {
// 				continue;
// 			}
// 			bret = CompSwitchLevel( pLOBData->fMaxFreq, & pRadarMode->vecRadarRF_Values, pRF_SequenceNumIndex, pvecRF_NumIndex->size(), pRadarMode );
// 			if( bret == FALSE ) {
// 				continue;
// 			}
//
// 			break;
//
// 		}
// 		if( bret == FALSE ) {
// 			continue;
// 		}

        // 식별값 저장
        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    주파수 고정-패턴 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.35
        \date     2008-08-07 13:18:09
        \warning
*/
void CELSignalIdentifyAlg::FIdentifyFixPat( SRxLOBData *pLOBData )
{

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    주파수 패턴-패턴 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.35
        \date     2008-08-07 13:20:20
        \warning
*/
void CELSignalIdentifyAlg::FIdentifyHopHop( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;
    //BOOL bret;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;

    pIdxLib = & m_pIdResult[m_fromLib];

    // 호핑 단수와 레벨 값 비교 추가
    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        BOOL bMatch=FALSE;
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

// 		for( auto iter = pRadarMode->mapRadarRF_Sequence.begin(); iter != pRadarMode->mapRadarRF_Sequence.end(); iter++ ) { //#FA_C_PotentialUnboundedLoop_T3
// 			SRadarRF_Sequence *pstSRadarRF_Sequence = & (*iter).second;
//
// 			bMatch = TRUE;
// 			if( pstSRadarRF_Sequence->vecRF_NumIndex.size() == (unsigned int) pLOBData->iFreqPositionCount ) {
// 				if( pLOBData->fFreqSeq[0] != 0 ) {
// 					SRadarRF_SequenceNumIndex *pRF_SequenceNumIndex;
// 					vector<SRadarRF_SequenceNumIndex> *pvecRF_NumIndex;
//
// 					pvecRF_NumIndex = & pstSRadarRF_Sequence->vecRF_NumIndex;
// 					pRF_SequenceNumIndex = & pvecRF_NumIndex->at(0);
//
// 					bret = CompSwitchLevel( pLOBData->fFreqSeq, & pRadarMode->vecRadarRF_Values, pRF_SequenceNumIndex, pvecRF_NumIndex->size() );
//
// 					if( bret == TRUE )
// 						break;
// 				}
// 				else {
// 					break;
// 				}
// 			}
// 			else {
// 				bMatch = FALSE;
// 				break;
// 			}
//
// 			bMatch = FALSE;
// 		}
//
// 		if( bMatch == FALSE ) {
// 			continue;
// 		}

        // 식별 값 저장
        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     PRI 레벨 값을 참조하여 신호 식별을 수행한다.
 * @param     int * series
 * @param     vector<SRadarPRI_Values>* pvecRadarPRI_Values
 * @param     SRadarPRI_SequenceNumIndex * pPRI_SequenceNumIndex
 * @param     int coSeries
 * @return    BOOL
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-10-27, 오전 12:20
 * @warning
 */
BOOL CELSignalIdentifyAlg::CompSwitchLevel( float *series, int coSeries, vector <SRadarMode_Sequence_Values> *pvecRadarPRI_Values, SRadarPRI_SequenceNumIndex *pPRI_SequenceNumIndex, int coNumIndex )
{
    int i, l;

    SRadarMode_Sequence_Values *pRadarPRI_Values;

    BOOL bRet=FALSE;
    SRadarPRI_SequenceNumIndex *pTempPRI_SequenceNumIndex, *pTempPRI_SequenceNumIndex2;

    if( coSeries == 0 ) {
        // bRet = FALSE;
    }
    else {
        if( pvecRadarPRI_Values->size() > 0 ) {
            pTempPRI_SequenceNumIndex = pPRI_SequenceNumIndex;

            for( i=0 ; i < coNumIndex ; ++i ) {
                if( pTempPRI_SequenceNumIndex->nPRI_Index - 1 < (int) pvecRadarPRI_Values->size() ) {
                    pRadarPRI_Values = & pvecRadarPRI_Values->at( (UINT) pTempPRI_SequenceNumIndex->nPRI_Index - 1 );

                    bRet = CompMarginDiff<float>( series[0], pRadarPRI_Values->f_Min, pRadarPRI_Values->f_Max, (float) m_pSEnvironVariable->fMarginPriError );
                    if( TRUE == bRet ) {
                        pTempPRI_SequenceNumIndex2 = pTempPRI_SequenceNumIndex + 1;
                        // 나머지 레벨 값을 비교.
                        for( l=1 ; l < coSeries ; ++l ) {
                            pRadarPRI_Values = & pvecRadarPRI_Values->at( (UINT) pTempPRI_SequenceNumIndex->nPRI_Index - 1 );
                            if( pTempPRI_SequenceNumIndex2 >= pPRI_SequenceNumIndex+coNumIndex ) {
                                pTempPRI_SequenceNumIndex2 = pPRI_SequenceNumIndex;
                            }

                            if( pTempPRI_SequenceNumIndex2->nPRI_Index - 1 < (int) pvecRadarPRI_Values->size() ) {
                                pRadarPRI_Values = & pvecRadarPRI_Values->at( (UINT) pTempPRI_SequenceNumIndex2->nPRI_Index - 1 );
                                bRet = CompMarginDiff<float>( series[l], pRadarPRI_Values->f_Min, pRadarPRI_Values->f_Max, (float) m_pSEnvironVariable->fMarginFrqError );
                                if( FALSE == bRet ) {
                                    break;
                                }
                            }
                            else {
                                bRet = FALSE;
                                break;
                            }

                            ++ pTempPRI_SequenceNumIndex2;
                        }

                    }

                    ++ pTempPRI_SequenceNumIndex;

                    if( TRUE == bRet ) {
                        break;
                    }
                }
                else {
                    LogPrint( "\n AAAAAA ");
                    // LogPrint( "\n 잘못된 레이더 번호[%d]" , pRadarMode->nRadarModeIndex );
                }
            }
        }
        else { //DTEC_Else
            // GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEO_DEVICE, enumGMEI_DEVICE, "PRI 하부 레벨 값이 없어서 검사를 하지 못합니다." );

        }
    }

    return bRet;

}

/**
  * @brief
  * @param		float * series
  * @param		int coSeries
  * @param		vector <SRadarMode_PRISequence_Values> * pvecRadarPRI_Values
  * @return 	BOOL
  * @date			2019/04/25 10:19
*/
BOOL CELSignalIdentifyAlg::CompSwitchLevel( float *series, int coSeries, vector <SRadarMode_Sequence_Values> *pVecRadarMode_PRISequence_Values )
{
    UINT i, l;

    BOOL bRet=FALSE;
    UINT uiSizeOfRadarMode_PRISequence;
    SRadarMode_Sequence_Values pRadarMode_PRISequence_Values;
    vector<SRadarMode_Sequence_Values>::pointer pRadarMode_PRISequence;

    if( coSeries == 0 ) {
        bRet = FALSE;
    }
    else {
        uiSizeOfRadarMode_PRISequence = pVecRadarMode_PRISequence_Values->size();

        if( uiSizeOfRadarMode_PRISequence > 0 ) {
            for( i=0 ; i < uiSizeOfRadarMode_PRISequence ; ++i ) {
                pRadarMode_PRISequence = pVecRadarMode_PRISequence_Values->data();

                bRet = CompMarginDiff<float>( series[i], (*pRadarMode_PRISequence).f_Min, (*pRadarMode_PRISequence).f_Max, (float) m_pSEnvironVariable->fMarginPriError );
                if( TRUE == bRet ) {
                    // 나머지 레벨 값을 비교.
                    for( l=i+1 ; l < uiSizeOfRadarMode_PRISequence+i ; ++l ) {
                        ++ pRadarMode_PRISequence;

                        bRet = CompMarginDiff<float>( series[l%uiSizeOfRadarMode_PRISequence], (*pRadarMode_PRISequence).f_Min, (*pRadarMode_PRISequence).f_Max, (float) m_pSEnvironVariable->fMarginPriError );
                        if( FALSE == bRet ) {
                            break;
                        }

                    }

                    if( TRUE == bRet ) {
                        break;
                    }
                }
            }
        }
        else { //DTEC_Else
            // GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEO_DEVICE, enumGMEI_DEVICE, "PRI 하부 레벨 값이 없어서 검사를 하지 못합니다." );

        }
    }

    return bRet;

}

/**
 * @brief     두 스위치 레벨간의 값을 병합 비교한다.
 * @param     int * pSeries1
 * @param     int * pSeries2
 * @param     int coSeries
 * @param     int margin
 * @return    BOOL
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-08, 오후 2:20
 * @warning
 */


// BOOL CELSignalIdentifyAlg::CompSwitchLevel( float *pSeries1, float *pSeries2, int coSeries, float margin )
// {
// 	int i, j, k, iDiff;
// 	int index1;
//
// 	float *pSeries;
//
// 	BOOL bRet=FALSE;
//
// 	if( coSeries != 0 ) {
// 		for( i=0 ; i < coSeries ; ++i ) {
// 			bRet = TRUE;
// 			iDiff = 0;
// 			for( j=i ; j < coSeries+i ; ++j ) {
// 				pSeries = pSeries2;
// 				for( k=j ; k < coSeries+j ; ++k ) {
// 					index1 = k % coSeries;
// 					bRet = CompMeanDiff( pSeries1[index1], *pSeries, margin );
// 					if( FALSE == bRet ) {
// 						break;
// 					}
// 					iDiff += _diffabs( pSeries1[index1], *pSeries );
// 					++ pSeries;
// 				}
// 			}
//
// 			if( TRUE == bRet ) {
// 				break;
// 			}
// 		}
// 	}
//
// 	return bRet;
//
// }

/**
 * @brief     주파수 레벨 값을 참조하여 신호 식별을 수행한다.
 * @param     int val
 * @param     vector<SRadarRF_Values>* pvecRadarRF_Values
 * @param     SRadarRF_SequenceNumIndex * pRF_SequenceNumIndex
 * @param     int coSeries
 * @return    BOOL
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-10-26, 오후 11:20
 * @warning
 */
BOOL CELSignalIdentifyAlg::CompSwitchLevel( float fVal, vector <SRadarRF_Values> *pvecRadarRF_Values, SRadarRF_SequenceNumIndex *pRF_SequenceNumIndex, UINT coSeries, SRadarMode *pRadarMode )
{
    UINT i;

    BOOL bRet=FALSE;

    int nSizeRadarRF_Values = (int) pvecRadarRF_Values->size();

    for( i=0 ; i < coSeries ; ++i ) {
        SRadarRF_Values *pRadarRF_Values;

        if( nSizeRadarRF_Values > pRF_SequenceNumIndex->nRF_Index - 1 ) {
            pRadarRF_Values = & pvecRadarRF_Values->at( (UINT) pRF_SequenceNumIndex->nRF_Index - 1 );

            bRet = CompMarginDiff<float>( fVal, pRadarRF_Values->fRF_Min, pRadarRF_Values->fRF_Max, 0 );
            if( TRUE == bRet ) {
                break;
            }
        }
        else {
            LogPrint( "\n 레이더 모드[%d] 에서 주파수 레벨 값이 잘못됐습니다." , pRadarMode->iRadarModeIndex );
        }

        ++ pRF_SequenceNumIndex;

    }

    return bRet;

}

/**
 * @brief     PRI 레벨 값을 참조하여 신호 식별을 수행한다.
 * @param     int val
 * @param     vector<SRadarPRI_Values>* pvecRadarPRI_Values
 * @param     SRadarPRI_SequenceNumIndex * pPRI_SequenceNumIndex
 * @param     int coSeries
 * @return    BOOL
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-10-27, 오전 12:04
 * @warning
 */
BOOL CELSignalIdentifyAlg::CompSwitchLevel( float fVal, vector <SRadarMode_Sequence_Values> *pvecRadarPRI_Values, SRadarPRI_SequenceNumIndex *pPRI_SequenceNumIndex, UINT coSeries, SRadarMode *pRadarMode )
{
    UINT i;

    BOOL bRet=FALSE;
    int nSizeRadarPRI_Values = (int) pvecRadarPRI_Values->size();

    for( i=0 ; i < coSeries ; ++i ) {
        SRadarMode_Sequence_Values *pRadarPRI_Values;

        if( nSizeRadarPRI_Values > pPRI_SequenceNumIndex->nPRI_Index - 1 ) {
            pRadarPRI_Values = & pvecRadarPRI_Values->at( (UINT) pPRI_SequenceNumIndex->nPRI_Index - 1 );

            bRet = CompMarginDiff<float>( fVal, pRadarPRI_Values->f_Min, pRadarPRI_Values->f_Max, 0 );
            if( TRUE == bRet ) {
                break;
            }
        }
        else {
            LogPrint( "\n 레이더 모드[%d] 에서 PRI 레벨 값이 잘못됐습니다." , pRadarMode->iRadarModeIndex );
        }

        ++ pPRI_SequenceNumIndex;

    }

    return bRet;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    주파수 패턴-패턴 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.35
        \date     2008-08-07 16:56:56
        \warning
*/
void CELSignalIdentifyAlg::FIdentifyPatPat( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;
    BOOL bret;
    STR_LIB_IDRESULT *pIdxLib;

    int diff;
    float fOverlapValue;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        fOverlapValue = FDIV( m_pSEnvironVariable->fMarginFrqModPeriodErrorRatio * ( pRadarMode->fRF_TypicalMax - pRadarMode->fRF_TypicalMin ), 100.0 );
        bret = IsOverlapSpace( pLOBData->fMinFreq, pLOBData->fMaxFreq, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, fOverlapValue );
        if( bret == _spFalse ) {
            continue;
        }

        // 주파수 범위 체크
        bret = CompMarginDiff<float>( pLOBData->fMinFreq, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
        if( bret == _spFalse ) {
            continue;
        }

        bret = CompMarginDiff<float>( pLOBData->fMaxFreq, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
        if( bret == _spFalse ) {
            continue;
        }

        // 주파수 변경 주기 체크
        diff = IDIV( m_pSEnvironVariable->fMarginMinRqdFrqRangeNestedRatio * pLOBData->fFreqPatternPeriod, 100 );

        bret = CompMarginDiff( pLOBData->fFreqPatternPeriod, pRadarMode->fPRI_PatternPeriodMin, pRadarMode->fPRI_PatternPeriodMax, m_pSEnvironVariable->fMarginFrqError );
        if( bret == _spFalse ) {
            continue;
        }

        // 식별 값 저장
        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    주파수 어자일-패턴 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.35
        \date     2008-08-07 18:00:42
        \warning
*/
void CELSignalIdentifyAlg::FIdentifyAgiPat( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;
    BOOL bret;
    STR_LIB_IDRESULT *pIdxLib;

    float fOverlapValue;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];
    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdFrqRangeNestedRatio * ( pRadarMode->fRF_TypicalMax - pRadarMode->fRF_TypicalMin ), 100.0 );
        bret = IsOverlapSpace( pLOBData->fMinFreq, pLOBData->fMaxFreq, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, fOverlapValue );
        if( bret == _spFalse ) {
            continue;
        }

        bret = CompMarginDiff<float>( pLOBData->fMinFreq, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
        if( bret == _spFalse ) {
            continue;
        }

        bret = CompMarginDiff<float>( pLOBData->fMaxFreq, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
        if( bret == _spFalse ) {
            continue;
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     두 범위 간의 중첩을 계산한다.
 * @param     low1 1번째 최소값
 * @param     hgh1 1번째 최대값
 * @param     low2 2번째 최소값
 * @param     hgh2 2번째 최소값
 * @param     nRatio 허용 중첩값 [%]
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-08-08, 오후 10:29
 * @warning
 */
bool CELSignalIdentifyAlg::IsOverlapSpace( float flow1, float fhgh1, float flow2, float fhgh2, float nRatio )
{
    float fOverlapSpace;

    fOverlapSpace = CalOverlapSpace<float>( fhgh1, flow1, fhgh2, flow2 );
    return fOverlapSpace >= nRatio;
}

/**
 * @brief     두 범위 간의 중첩을 계산한다.
 * @param     low1 1번째 최소값
 * @param     hgh1 1번째 최대값
 * @param     low2 2번째 최소값
 * @param     hgh2 2번째 최소값
 * @param     nRatio 허용 중첩값 [%]
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-08-08, 오후 10:29
 * @warning
 */
bool CELSignalIdentifyAlg::IsOverlapSpace( int low1, int hgh1, int low2, int hgh2, int nRatio )
{
    UINT nOverlapSpace;

    nOverlapSpace = CalOverlapSpace<UINT>( hgh1, low1, hgh2, low2 );
    return (int) nOverlapSpace >= nRatio;
}

/*!
 * @brief     PRI 형태를 무시한 경우의 PRI 범위에 대한 식별 처리를 수행한다.
 * @return    void
 * @param     STR_NEWAET * pNewAet
 * @version   1.0
 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희
 * @date      2014-12-28 오후 1:49
 * @warning
 */
void CELSignalIdentifyAlg::PIdentifyPRI( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;
    BOOL bret;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( ( pRadarMode->fPRI_TypicalMin > 0 || pRadarMode->fPRI_TypicalMin < 0 ) || ( pRadarMode->fPRI_TypicalMax > 0 || pRadarMode->fPRI_TypicalMax < 0 ) ) {
            bret = ( CompMarginDiff<float>( pLOBData->fMinPRI, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) == TRUE ||
                             CompMarginDiff<float>( pLOBData->fMaxPRI, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) == TRUE );

            if( bret == _spFalse ) {
                continue;
            }

            // 그룹당 PRI 비교 추가
// 			if( pRadarMode->fPRI_PPG_Min > _spOne ) {
// 				bret = CompMarginDiff2( m_optParameter.pulse_per_group, pRadarMode->fPRI_PPG_Min, pRadarMode->fPRI_PPG_Max, 0 );
//
// 				if( bret == _spFalse ) {
// 					continue;
// 				}
// 			}
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    PRI Stable-Stable 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.35
        \date     2008-08-07 18:36:06
        \warning
*/
void CELSignalIdentifyAlg::PIdentifyStbStb( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;
    BOOL bret;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( ( pRadarMode->fPRI_TypicalMin > 0 || pRadarMode->fPRI_TypicalMin < 0 ) || ( pRadarMode->fPRI_TypicalMax > 0 || pRadarMode->fPRI_TypicalMax < 0 ) ) {
            bret = ( CompMarginDiff<float>( pLOBData->fMinPRI, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) == TRUE ||
                             CompMarginDiff<float>( pLOBData->fMinPRI, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) == TRUE );

            if( bret == _spFalse ) {
                continue;
            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    PRI Stable-Dwell 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.35
        \date     2008-08-07 18:41:55
        \warning
*/
void CELSignalIdentifyAlg::PIdentifyStbDwl( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        BOOL bret=FALSE;
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        // Dwell 특성 여부
// 		for( auto iter = pRadarMode->mapRadarPRI_Sequence.begin(); iter != pRadarMode->mapRadarPRI_Sequence.end(); iter++ ) { //#FA_C_PotentialUnboundedLoop_T3
// 			SRadarPRI_Sequence *pstSRadarPRI_Sequence = & (*iter).second;
//
// 			SRadarPRI_SequenceNumIndex *pPRI_SequenceNumIndex;
// 			vector<SRadarPRI_SequenceNumIndex> *pvecPRI_NumIndex;
//
// 			pvecPRI_NumIndex = & pstSRadarPRI_Sequence->vecPRI_NumIndex;
// 			pPRI_SequenceNumIndex = & pvecPRI_NumIndex->at(0);
//
// 			bret = CompSwitchLevel( pLOBData->fMinPRI, & pRadarMode->vecRadarMode_PRISequenceValues, pPRI_SequenceNumIndex, pvecPRI_NumIndex->size(), pRadarMode );
// 			if( bret == FALSE ) {
// 				continue;
// 			}
// 			bret = CompSwitchLevel( pLOBData->fMaxPRI, & pRadarMode->vecRadarMode_PRISequenceValues, pPRI_SequenceNumIndex, pvecPRI_NumIndex->size(), pRadarMode );
// 			if( bret == FALSE ) {
// 				continue;
// 			}
//
// 			break;
//
// 		}

        if( bret == FALSE ) {
            continue;
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    PRI 스태거-스태거 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.34
        \date     2008-08-07 21:51:48
        \warning
*/
void CELSignalIdentifyAlg::PIdentifyStgStg( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;
    BOOL bMatch, bret;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        // 스태거 단수와 레벨 값 비교 추가
        bret = FALSE;
        bMatch = false;

        if( pRadarMode->vecRadarMode_PRISequenceValues.size() == (UINT) pLOBData->iPRIPositionCount ) {
            if( pLOBData->fPRISeq[0] != 0 ) {
                bret = CompSwitchLevel( pLOBData->fPRISeq, pLOBData->iPRIPositionCount, & pRadarMode->vecRadarMode_PRISequenceValues ); //, pPRI_SequenceNumIndex, (int) pvecPRI_NumIndex->size() );

                if( bret == TRUE ) {
                    m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
                }
            }
        }

    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    PRI 드웰-드웰 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.35
        \date     2008-08-07 22:17:18
        \warning
*/
void CELSignalIdentifyAlg::PIdentifyDwlDwl( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;
    BOOL bret, bMatch;
    STR_LIB_IDRESULT *pIdxLib;

    SRadarMode* pRadarMode;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        bMatch = FALSE;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        // D&S 단수와 레벨 값 비교 추가
        if( pRadarMode->nPRI_NumPositions == (UINT) pLOBData->iPRIPositionCount ) {
            if( pLOBData->fPRISeq[0] != 0 ) {
                bret = CompSwitchLevel( pLOBData->fPRISeq, pLOBData->iPRIPositionCount, & pRadarMode->vecRadarMode_PRISequenceValues );

                if( bret == FALSE ) {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        else {
            continue;
        }

        m_pIdResult[toLib].pIdxRadarMode = pIdxLib->pIdxRadarMode;

        ++ toLib;

    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    PRI 지터-스태거 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.35
        \date     2008-08-07 23:01:38
        \warning
*/
void CELSignalIdentifyAlg::PIdentifyJitStg( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;

    STR_LIB_IDRESULT *pIdxLib;
    float fOverlapValue;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * ( pRadarMode->fPRI_TypicalMax - pRadarMode->fPRI_TypicalMin ), 100.0 );
        if( false == IsOverlapSpace( pLOBData->fMinPRI, pLOBData->fMaxPRI, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, fOverlapValue ) ) {
            continue;
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    PRI 지터-지터 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.35
        \date     2008-08-07 23:13:18
        \warning
*/
void CELSignalIdentifyAlg::PIdentifyJitJit( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;

    //int iOverlapValue;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        SRadarMode* pRadarMode;
        BOOL bret;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        bret = CompMarginDiff<float>( pLOBData->fMinPRI, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError );
        if( bret == FALSE ) {
            continue;
        }
        bret = CompMarginDiff<float>( pLOBData->fMaxPRI, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError );
        if( bret == FALSE ) {
            continue;
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    PRI 지터-패턴 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.35
        \date     2008-08-07 23:39:05
        \warning
*/
void CELSignalIdentifyAlg::PIdentifyJitPat( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;
    STR_LIB_IDRESULT *pIdxLib;

    float fOverlapValue;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * ( pRadarMode->fPRI_TypicalMax - pRadarMode->fPRI_TypicalMin ), 100.0 );
        if( false == IsOverlapSpace( pLOBData->fMinPRI, pLOBData->fMaxPRI, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, fOverlapValue ) ) {
            continue;
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    PRI 패턴-패턴 신호에 대해서 식별을 수행한다.
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.35
        \date     2008-08-07 23:58:04
        \warning
*/
void CELSignalIdentifyAlg::PIdentifyPatPat( SRxLOBData *pLOBData )
{
    UINT i;
    UINT toLib;
    STR_LIB_IDRESULT *pIdxLib;

    m_pLOBData = pLOBData;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];
    for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
        //if( m_optParameter.pri.bCheckRange == true ) {
            //if( m_optParameter.ppattern.bCheckType == true ) {
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        // PRI 범위 체크
        if( FALSE == IdentifyPatternRange( pRadarMode ) ) {
            continue;
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     패턴 범위를 체크하여 식별한다.
 * @param     SRadarMode * pRadarMode
 * @return    BOOL
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-11-01, 오후 5:59
 * @warning
 */
BOOL CELSignalIdentifyAlg::IdentifyPatternRange( SRadarMode *pRadarMode ) //#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found)
{
    BOOL bret;
    //int diff;

    /*! \bug  신뢰성: NULL 체크하여 예외처리하게 함.
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2015-10-6 13:56:40
    */
    if( pRadarMode == NULL ) { //DTEC_NullPointCheck
        return FALSE;
    }

    if( _spFalse == IsOverlapSpace( m_pLOBData->fMinPRI, m_pLOBData->fMaxPRI, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, 200. ) ||
            _spFalse == CompMarginDiff<float>( m_pLOBData->fMinPRI, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) ||
        _spFalse == CompMarginDiff<float>( m_pLOBData->fMaxPRI, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) ) {
        return FALSE;
    }

// 	bret = IsOverlapSpace( m_optParameter.pri.fLow, m_optParameter.pri.fHigh, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_optParameter.pri.iOverlapRatio );
// 	if( bret == _spFalse ) {
// 		return FALSE;
// 	}
//
// 	bret = CompMarginDiffFFF( m_optParameter.pri.fLow, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_optParameter.pri.fRangeError );
// 	if( bret == _spFalse ) {
// 		return FALSE;
// 	}
//
// 	bret = CompMarginDiffFFF( m_optParameter.pri.fHigh, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_optParameter.pri.fRangeError );
// 	if( bret == _spFalse ) {
// 		return FALSE;
// 	}

    /*! \todo		패턴 형태 비교 추가
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2015-03-25 20:53:54
    */
// 	if( ( pRadarMode->ePRI_JITTER_PATTERN != PatternCode::enumPatterned ) && ( m_optParameter.ppattern.iType > E_EL_PPT_UNKNOWN ) ) {
// 		return FALSE;
// 	}

    // PRI 변경 주기 체크
    //diff = IDIV( m_pSEnvironVariable->fMarginPriError * m_optParameter.ppattern.iValue, 100 );

    bret = CompMarginDiff<float>( m_pLOBData->fPRIPatternPeriod, pRadarMode->fPRI_PatternPeriodMin, pRadarMode->fPRI_PatternPeriodMax, m_pSEnvironVariable->fMarginPriModPeriodErrorRatio );
    if( bret == _spFalse ) {
        return FALSE;
    }

    return TRUE;

}

// //////////////////////////////////////////////////////////////////////////
// /*! \brief    펄스폭 식별을 수행한다.
// 		\author   조철희
// 		\param    pNewAet 인자형태 STR_NEWAET *
// 		\return   void
// 		\version  0.0.35
// 		\date     2008-08-08 00:07:38
// 		\warning
// */
// void CELSignalIdentifyAlg::IdentifyPW()
// {
// 	UINT i;
// 	UINT toLib;
// 	STR_LIB_IDRESULT *pIdxLib;
//
// 	toLib = 0;
// 	pIdxLib = & m_pIdResult[0];
//
// 	for( i=0 ; i < m_toLib ; ++i, ++pIdxLib ) {
// 		SRadarMode* pRadarMode;
//
// 		pRadarMode = pIdxLib->pIdxRadarMode;
// 		if( pRadarMode == NULL ) { //DTEC_NullPointCheck
// 			continue;
// 		}
//
// 		if( m_optParameter.pw.bCheckRange == true ) {
// 			float fDiffPW;
// 			float fDiff;
//
// 			// 펄스폭 최소, 최대 값이 0 일때는 펄스폭 비교는 무시한다.
// 			//if( pRadarMode->fPD_TypicalMin != 0.0 && pRadarMode->fPD_TypicalMax != 0.0 ) {
// 			if( Is_FNotZero( pRadarMode->fPD_TypicalMin ) == true && Is_FNotZero( pRadarMode->fPD_TypicalMax ) == true ) {
// 				fDiff = abs( m_optParameter.pw.fHigh - m_optParameter.pw.fLow );
// 				fDiffPW = FDIV( fDiff*m_optParameter.pw.fRatioError, 100 );
// 				fDiffPW = m_optParameter.pw.fRangeError + fDiffPW;
//
// 				// 범위 안에 평균이 들어가지 않으면 실패
// 				if( CompMarginDiffFFF( m_optParameter.pw.fMean, 0, pRadarMode->fPD_TypicalMax, fDiffPW ) == _spFalse ) {
// 					continue;
// 				}
// 			}
// 		}
//
// 		m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
// 	}
//
// 	m_toLib = toLib;
// }
//
// /**
//  * @brief     스캔 형태에 대해서 신호 식별 결과를 알려준다.
//  * @param     ScanType::EnumScanType eScanType
//  * @param     int aetAspiType
//  * @return    BOOL
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2015-10-21, 오후 10:56
//  * @warning
//  */
// BOOL CELSignalIdentifyAlg::CheckScanType( ScanType::EnumScanType eScanType, int aetAspiType )
// {
// 	BOOL bRet=TRUE;
//
// 	if( aetAspiType != E_AET_SCAN_UNKNOWN ) {
// 		if( ( eScanType != ScanType::enumUndefinedScanType ) && ( eScanType != ScanType::enumZ_Undetermined ) ) {
// 			switch( aetAspiType ) {
// 				case E_AET_SCAN_SEARCH :
// 					if( ( eScanType == ScanType::enumF_Conical ) || ( eScanType == ScanType::enumG_Lobe_Switching ) ) {
// 						bRet = FALSE;
// 					}
// 					break;
//
// 				case E_AET_SCAN_TRACKING :
// 					if( ( ( eScanType == ScanType::enumA_Circular ) == true ) ||
// 							( ( eScanType == ScanType::enumB_Horizontal_Sector_Bi_directional ) == true ) || ( ( eScanType == ScanType::enumC_Vertical_Sector_Bi_directional ) == true ) ||
// 							( ( eScanType == ScanType::enumJ_Raster ) == true ) || ( ( eScanType == ScanType::enumK_Spiral ) == true ) || ( ( eScanType == ScanType::enumL_Helical ) == true ) ||
// 							( ( eScanType == ScanType::enumO_Sector_Uni_or_Bi_Directional ) == true ) || ( ( eScanType == ScanType::enumS_Vertical_Sector_Uni_Directional ) == true ) ||
// 							( ( eScanType == ScanType::enumT_Horizontal_Sector ) == true ) || ( ( eScanType == ScanType::enumU_Uni_Directional_Sector_Plane_Undertermined ) == true ) ||
// 							( ( eScanType == ScanType::enumV_Bi_Directional_Sector_Plane_Undetermined ) == true ) ) {
// 						bRet = FALSE;
// 					}
// 					break;
//
// 				case E_AET_SCAN_SECTOR :
// 					if( ( ( eScanType == ScanType::enumF_Conical ) == true ) || ( ( eScanType == ScanType::enumG_Lobe_Switching ) == true ) ) {
// 						bRet = FALSE;
// 					}
// 					break;
//
// 				default :
// 					break;
// 				}
// 		}
// 		else {
// 			bRet = FALSE;
// 		}
// 	}
//
// 	return bRet;
// }
//
// /**
//  * @brief     신호 식별하기 위해서 LOB 데이터를 신호 식별 입력값으로 변환한다.
//  * @param     SRxLOBDataGroup * pLOBDataGroup
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-01, 오후 2:39
//  * @warning
//  */
// void CELSignalIdentifyAlg::SetOptionParameter( SRxLOBDataGroup *pLOBDataGroup )
// {
// 	float fscanPeriod;
//
// 	memset( & m_optParameter, 0, sizeof(SELIDENTIFICATIONOPTION_PARAMETER) );
//
// 	// 신호 형태
// 	m_optParameter.st.bCheckType = true;
// 	m_optParameter.st.iSignalType = pLOBDataGroup->iSignalType;
//
// 	// 변조
// 	m_optParameter.mod.bCheckType = true;
// 	m_optParameter.mod.iType = pLOBDataGroup->iMOPType;
//
// 	// 극성
// 	m_optParameter.pol.bCheckType = true;
// 	m_optParameter.pol.iType = pLOBDataGroup->iPolarization;
//
// 	// 위협 레벨
// 	m_optParameter.tl.bCheckType = true;
// 	//m_optParameter.tl.iThreatLevel = 0;
//
// 	// EOB - 거리 오차
// 	m_optParameter.dist.bCheckType = true;
// 	m_optParameter.dist.iMaxDistance = 10000;
//
// 	// 주파수
// 	m_optParameter.freq.bCheckType = true;
// 	m_optParameter.freq.bCheckRange = true;
// 	m_optParameter.freq.iType = pLOBDataGroup->iFreqType;
// 	m_optParameter.freq.fLow = FDIV( pLOBDataGroup->iMinFreq, DEF_OF_RES_FREQ2 );
// 	m_optParameter.freq.fHigh = FDIV( pLOBDataGroup->iMaxFreq, DEF_OF_RES_FREQ2 );
// 	m_optParameter.freq.fRangeError = m_pSELDBEnvVarIdnf->fMarginFrqError;
// 	m_optParameter.freq.fOverlapRatio = m_pSELDBEnvVarIdnf->fMarginMinRqdFrqRangeNestedRatio;
//
// 	// 주파수 레벨
// 	m_optParameter.flevel.bCheckLevel = true;
// 	m_optParameter.flevel.nElement = pLOBDataGroup->iFreqElementCount;
// 	m_optParameter.flevel.nPosition = pLOBDataGroup->iFreqPositionCount;
//
// 	// 주파수 패턴
// 	m_optParameter.fpattern.bCheckType = true;
// 	m_optParameter.fpattern.iType = pLOBDataGroup->iFreqPatternType;
// 	m_optParameter.fpattern.bCheckRange = true;
// 	m_optParameter.fpattern.iValue = pLOBDataGroup->iFreqChangePeriod;
// 	m_optParameter.fpattern.fRangeError = m_pSELDBEnvVarIdnf->fMarginFrqModPeriodErrorRatio;
//
// 	// PRI
// 	m_optParameter.pri.bCheckType = true;
// 	m_optParameter.pri.bCheckRange = true;
// 	m_optParameter.pri.iType = pLOBDataGroup->iPRIType;
// 	m_optParameter.pri.fLow = FDIV( pLOBDataGroup->iMinPRI , 1000 );
// 	m_optParameter.pri.fHigh = FDIV( pLOBDataGroup->iMaxPRI, 1000 );
// 	m_optParameter.pri.fRangeError = (float) m_pSELDBEnvVarIdnf->fMarginPriError;
// 	m_optParameter.pri.fOverlapRatio = m_pSELDBEnvVarIdnf->fMarginMinRqdPriRangeNestedRatio;
//
// 	// PRI 레벨
// 	m_optParameter.plevel.bCheckLevel = true;
// 	m_optParameter.plevel.nElement = pLOBDataGroup->iPRIElementCount;
// 	m_optParameter.plevel.nPosition = pLOBDataGroup->iPRIPositionCount;
//
// 	// PRI 패턴
// 	m_optParameter.ppattern.bCheckType = true;
// 	m_optParameter.ppattern.bCheckRange = true;
// 	m_optParameter.ppattern.iType = pLOBDataGroup->iPRIPatternType;
// 	m_optParameter.ppattern.iValue = pLOBDataGroup->iPRIChangePeriod;
// 	m_optParameter.ppattern.fRangeError = m_pSELDBEnvVarIdnf->fMarginPriModPeriodErrorRatio;
//
// 	// 펄스수 그룹
// 	m_optParameter.pulse_per_group = pLOBDataGroup->iPulsePerGrp;
//
// 	// 펄스폭
// 	m_optParameter.pw.bCheckRange = true;
// 	m_optParameter.pw.fLow = (float) ( ( pLOBDataGroup->iMinPW * DEF_OF_RES_PW ) / 1000. );
// 	m_optParameter.pw.fHigh = (float) ( ( pLOBDataGroup->iMaxPW * DEF_OF_RES_PW ) / 1000. );
// 	m_optParameter.pw.fMean = (float) ( ( pLOBDataGroup->iMeanPW * DEF_OF_RES_PW ) / 1000. );
// 	m_optParameter.pw.fRangeError = m_pSELDBEnvVarIdnf->fMarginPwError;
// 	m_optParameter.pw.fRatioError = m_pSELDBEnvVarIdnf->fMarginErrorRatioCompareToPw;
//
// 	// 스캔 주기
// 	m_optParameter.asp.bCheckType = true;
// 	m_optParameter.asp.bCheckRange = true;
// 	m_optParameter.asp.iType = pLOBDataGroup->iScanType;
// 	m_optParameter.asp.fLow = FDIV( pLOBDataGroup->iScanPeriod, 1000000. );
// 	m_optParameter.asp.fHigh = FDIV( pLOBDataGroup->iScanPeriod, 1000000. );
// 	fscanPeriod = FDIV( ( m_optParameter.asp.fLow + m_optParameter.asp.fHigh ), 2. );
// 	m_optParameter.asp.fRangeError = FDIV( ( fscanPeriod * m_pSELDBEnvVarIdnf->fMarginScanPeriodErrorRatio ), 100 );
//
// 	// 공통 설정 값
// 	CommonSetOptionParameter();
//
// 	// 환경 변수에 의한 설정
// 	SetOptionParameterByEnvVarIdnf();
//
// }
//
// /**
//  * @brief     신호 식별하기 위해서 빔 데이터를 신호 식별 입력값으로 변환한다.
//  * @param     SELABTDATA * pABTData
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-29, 오전 8:54
//  * @warning
//  */
// void CELSignalIdentifyAlg::SetOptionParameter( SELABTDATA *pABTData )
// {
// 	float fscanPeriod;
//
// 	memset( & m_optParameter, 0, sizeof(SELIDENTIFICATIONOPTION_PARAMETER) );
//
// 	// 신호 형태
// 	m_optParameter.st.bCheckType = true;
// 	m_optParameter.st.iSignalType = pABTData->sigInfo.iSignalType;
//
// 	// 변조
// 	m_optParameter.mod.bCheckType = true;
// 	m_optParameter.mod.iType = pABTData->intraInfo.iType;
//
// 	// 극성
// 	//m_optParameter.pol.bCheckType = false;
// 	//m_optParameter.pol.iType = 0;
//
// 	// 위협 레벨
// 	m_optParameter.tl.bCheckType = true;
// 	//m_optParameter.tl.iThreatLevel = 0;
//
// 	// EOB - 거리 오차
// 	m_optParameter.dist.bCheckType = true;
// 	m_optParameter.dist.iMaxDistance = 10000;
//
// 	// 주파수
// 	m_optParameter.freq.bCheckType = true;
// 	m_optParameter.freq.bCheckRange = true;
// 	m_optParameter.freq.iType = pABTData->freqDInfo.iType;
// 	m_optParameter.freq.fLow = FDIV( pABTData->freqInfo.iMin, DEF_OF_RES_FREQ2 );
// 	m_optParameter.freq.fHigh = FDIV( pABTData->freqInfo.iMax, DEF_OF_RES_FREQ2 );
// 	m_optParameter.freq.fRangeError = (float) m_pSELDBEnvVarIdnf->fMarginFrqError;
// 	m_optParameter.freq.fOverlapRatio = m_pSELDBEnvVarIdnf->fMarginMinRqdFrqRangeNestedRatio;
//
// 	// 주파수 레벨
// 	m_optParameter.flevel.bCheckLevel = true;
// 	m_optParameter.flevel.nElement = pABTData->freqDInfo.iElementCount;
// 	m_optParameter.flevel.nPosition = pABTData->freqDInfo.iPositionCount;
//
// 	// 주파수 패턴
// 	m_optParameter.fpattern.bCheckType = true;
// 	m_optParameter.fpattern.iType = pABTData->freqDInfo.iPatternType;
// 	m_optParameter.fpattern.bCheckRange = true;
// 	m_optParameter.fpattern.iValue = pABTData->freqDInfo.iChangePeriodMin;
// 	//m_optParameter.fpattern.iHigh = pABTData->freqDInfo.iChangePeriodMax;
// 	m_optParameter.fpattern.fRangeError = m_pSELDBEnvVarIdnf->fMarginFrqModPeriodErrorRatio;
//
// 	// PRI
// 	m_optParameter.pri.bCheckType = true;
// 	m_optParameter.pri.bCheckRange = true;
// 	m_optParameter.pri.iType = pABTData->priDInfo.iType;
// 	m_optParameter.pri.fLow = FDIV( pABTData->priInfo.iMin , 1000 );
// 	m_optParameter.pri.fHigh = FDIV( pABTData->priInfo.iMax, 1000 );
// 	m_optParameter.pri.fRangeError = (float) m_pSELDBEnvVarIdnf->fMarginPriError;
// 	m_optParameter.pri.fOverlapRatio = m_pSELDBEnvVarIdnf->fMarginMinRqdPriRangeNestedRatio;
//
// 	// PRI 레벨
// 	m_optParameter.plevel.bCheckLevel = true;
// 	m_optParameter.plevel.nElement = pABTData->priDInfo.iElementCount;
// 	m_optParameter.plevel.nPosition = pABTData->priDInfo.iPositionCount;
//
// 	// PRI 패턴
// 	m_optParameter.ppattern.bCheckType = true;
// 	m_optParameter.ppattern.bCheckRange = true;
// 	m_optParameter.ppattern.iType = pABTData->priDInfo.iType;
// 	m_optParameter.ppattern.iValue = pABTData->priDInfo.iChangePeriodMin;
// 	m_optParameter.ppattern.fRangeError = m_pSELDBEnvVarIdnf->fMarginPriModPeriodErrorRatio;
//
// 	// 펄스수 그룹
// 	m_optParameter.pulse_per_group = pABTData->pulseDInfo.iPulsePerGrp;
//
// 	// 펄스폭
// 	m_optParameter.pw.bCheckRange = true;
// 	m_optParameter.pw.fLow = (float) ( ( pABTData->pwInfo.iMin * DEF_OF_RES_PW ) / 1000. );
// 	m_optParameter.pw.fHigh = (float) ( ( pABTData->pwInfo.iMax * DEF_OF_RES_PW ) / 1000. );
// 	m_optParameter.pw.fMean = (float) ( ( pABTData->pwInfo.iMean * DEF_OF_RES_PW ) / 1000. );
// 	m_optParameter.pw.fRangeError = m_pSELDBEnvVarIdnf->fMarginPwError;
// 	m_optParameter.pw.fRatioError = m_pSELDBEnvVarIdnf->fMarginErrorRatioCompareToPw;
//
// 	// 스캔 주기
// 	m_optParameter.asp.bCheckType = true;
// 	m_optParameter.asp.bCheckRange = true;
// 	m_optParameter.asp.iType = pABTData->scanInfo.iType;
// 	m_optParameter.asp.fLow = FDIV( pABTData->scanInfo.iPeriodMin, 1000000. );
// 	m_optParameter.asp.fHigh = FDIV( pABTData->scanInfo.iPeriodMax, 1000000. );
// 	fscanPeriod = FDIV( ( m_optParameter.asp.fLow + m_optParameter.asp.fHigh ), 2. );
// 	m_optParameter.asp.fRangeError = FDIV( ( fscanPeriod * m_pSELDBEnvVarIdnf->fMarginScanPeriodErrorRatio ), 100 );
//
// 	// 공통 설정 값
// 	CommonSetOptionParameter();
//
// 	SetOptionParameterByEnvVarIdnf();
// }
//
// /**
//  * @brief     신호 식별하기 위한 입력 값으로 설정한다.
//  * @param     void
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-07-05, 오후 3:59
//  * @warning
//  */
// void CELSignalIdentifyAlg::CommonSetOptionParameter()
// {
// 	// EOB 식별시 반경
// 	m_optParameter.dist.iMaxDistance *= 1000;
//
// 	// 일치율 식별
// 	m_optParameter.mr.bCheckType = true;
// 	m_optParameter.mr.iMatchRatio = GP_MGR_TEST_PARAM->GetMinIDMatchRatio();
//
// }
//
// /**
//  * @brief     신호 식별하기 위한 설정 값 등을 설정한다.
//  * @param     void
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-04-28, 오후 4:26
//  * @warning
//  */
// void CELSignalIdentifyAlg::SetOptionParameterByEnvVarIdnf()
// {
// 	float fscanPeriod;
//
// 	m_optParameter.freq.fRangeError = (float) m_pSELDBEnvVarIdnf->fMarginFrqError;
// 	m_optParameter.freq.fOverlapRatio = m_pSELDBEnvVarIdnf->fMarginMinRqdFrqRangeNestedRatio;
//
// 	m_optParameter.fpattern.fRangeError = m_pSELDBEnvVarIdnf->fMarginFrqModPeriodErrorRatio;
//
// 	m_optParameter.pri.fRangeError = (float) m_pSELDBEnvVarIdnf->fMarginPriError;
// 	m_optParameter.pri.fOverlapRatio = m_pSELDBEnvVarIdnf->fMarginMinRqdPriRangeNestedRatio;
//
// 	m_optParameter.ppattern.fRangeError = m_pSELDBEnvVarIdnf->fMarginPriModPeriodErrorRatio;
//
// 	m_optParameter.pw.fRangeError = m_pSELDBEnvVarIdnf->fMarginPwError;
// 	m_optParameter.pw.fRatioError = m_pSELDBEnvVarIdnf->fMarginErrorRatioCompareToPw;
//
// 	fscanPeriod = FDIV( ( m_optParameter.asp.fLow + m_optParameter.asp.fHigh ), 2. );
// 	m_optParameter.asp.fRangeError = FDIV( ( fscanPeriod * m_pSELDBEnvVarIdnf->fMarginScanPeriodErrorRatio ), 100 );
//
// }
//
// //////////////////////////////////////////////////////////////////////////
// /*!
//  * @brief     ELINT Notation을 읽어 온다.
//  * @param     int iBeamID
//  * @param     EnumLibType enLibType
//  * @param     bool bGround
//  * @return    char *
//  * @version   0.0.1
//  예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @date      2013-10-10 오전 11:28
//  * @warning
//  */
// char *CELSignalIdentifyAlg::GetElintNotation( int nRadarModeIndex, int iAETID, int iABTID, EnumLibType enLibType, bool bGround )//#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found)
// {
// 	if( nRadarModeIndex == 0 ) {
// 		if( bGround == true )
// 			sprintf_s( m_H0000, 10, "-" );
// 		else {
// 			vector<STR_H000>::iterator itFind, itLast;
// 			STR_FindAETID tFindAETID;
//
// 			tFindAETID.iCompareAETID = iAETID;
// 			tFindAETID.iCompareABTID = iABTID;
// 			itFind = std::find_if( m_vecH000.begin(), m_vecH000.end(), tFindAETID );
// 			if( itFind != m_vecH000.end() ) {
// 				char alphabet;
//
// 				alphabet = (char) ( 'A' + ( itFind->iH000 / 1000 ) );
// 				sprintf_s( m_H0000, 10, "H%03d%1c", itFind->iH000 % 1000, alphabet );
// 			}
// 			// 등록되지 않은 미식별 번호에 대해서는 기본값으로 리턴한다.
// 			else {
// 				sprintf_s( m_H0000, 10, "H000A" ); //2015.07.08.이정남. "L"붙임.
//
// 			}
// 			return m_H0000;
// 		}
// 	}
// 	else {
// 		bool bRet;
//
// 		bRet = GP_MNGR_CED_LIB2->RTGetRadarDataFromRadarModeIndex( & m_stRadar, nRadarModeIndex, enLibType );
//
// 		if( bRet == false ) { //DTEC_Else
// 			return "(null)";
// 		}
// 		else {
// 			return m_stRadar.szELNOT;
// 		}
//
// 	}
//
// 	return m_H0000;
// }
//
// /**
//  * @brief     특정 레이더 모드 데이터에 대해서 변조 코드를 리턴한다.
//  * @param     int nRadarModeIndex
//  * @param     EnumLibType enLibType
//  * @return    char *
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-01, 오전 10:51
//  * @warning
//  */
// char *CELSignalIdentifyAlg::GetModulationCode( int nRadarModeIndex, EnumLibType enLibType )
// {
// 	char *pRet=_stNullStr2;
//
// 	if( nRadarModeIndex != 0 ) {
// 		bool bRet;
//
// 		bRet = GP_MNGR_CED_LIB2->RTGetModulationCode( & m_stRadarMode, nRadarModeIndex, enLibType );
// 		if( bRet == true ) {
// 			pRet = m_stRadarMode.strModulationCode.GetBuffer();
// 		}
// 	}
//
// 	return pRet;
// }
//
// /*!
//  * @brief     빔 번호를 입력으로 해당 에미터의 플레폼 명을 리턴한다.
//  * @return    char *
//  * @param     int iBeamID
//  * @version   1.0
//  예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
//  * @author    조철희
//  * @date      2014-10-09 오후 8:02
//  * @warning
//  */
// char *CELSignalIdentifyAlg::GetPlatformName( int nThreatIndex, int nDeviceIndex, EnumLibType enLibType )
// {
// 	char *pRet=_stNullStr;
//
// 	if( nThreatIndex <= 0 || nDeviceIndex <= 0 ) {
// 		// pRet = _stNullStr;
// 	}
// 	else {
// 		SDevice *pDevice;
//
// 		pDevice = GP_MNGR_CED_LIB2->GetDeviceData( nThreatIndex, nDeviceIndex, enLibType );
// 		if( pDevice != nullptr ) { //DTEC_NullPointCheck
// 			pRet = GP_MNGR_CED_LIB2->m_CELCEDComon.GetSZPlatformCode(pDevice->ePlatform);
// 		}
//
// 	}
//
// 	return pRet;
// }
//
// /**
//  * @brief     플레폼 코드에 해당하는 문자열을 리턴한다.
//  * @param     int nRadarModeIndex
//  * @param     EnumLibType enLibType
//  * @return    char *
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-19, 오전 11:49
//  * @warning
//  */
// char * CELSignalIdentifyAlg::GetPlatformCode( int nRadarModeIndex, EnumLibType enLibType )
// {
// 	char *pChar;
//
// 	if( nRadarModeIndex == 0 ) {
// 		pChar = GP_MNGR_CED_LIB2->m_CELCEDComon.GetSZPlatformCode( PlatformCode::enumUndefinedPlatformCode );
// 	}
// 	else {
// 		SRadarMode *pRadarMode;
//
// 		pRadarMode = GP_MNGR_CED_LIB2->RTGetRadarModeDataFromMemory( nRadarModeIndex, enLibType );
// 		if( pRadarMode == nullptr ) { //DTEC_Else
// 			pChar = GP_MNGR_CED_LIB2->m_CELCEDComon.GetSZPlatformCode( PlatformCode::enumUndefinedPlatformCode );
// 		}
// 		else {
// 			pChar = GP_MNGR_CED_LIB2->m_CELCEDComon.GetSZPlatformCode( pRadarMode->ePlatform );
// 		}
//
// 	}
//
// 	return pChar;
// }

/**
 * @brief CELSignalIdentifyAlg::GetPlatform
 * @param iRadarModeIndex
 * @return
 */
PlatformCode::EnumPlatformCode CELSignalIdentifyAlg::GetPlatformFromRadarMode( int iRadarModeIndex )
{
    SRadarMode *pRadarMode;
    PlatformCode::EnumPlatformCode enPlatform;

    if( iRadarModeIndex >= 1 && iRadarModeIndex < MAX_RADARMODE ) {
        pRadarMode = GetRadarMode( iRadarModeIndex );
        enPlatform = pRadarMode->ePlatform;
    }
    else {
        enPlatform = PlatformCode::enumUnKnown;
    }

    return enPlatform;
}

/**
 * @brief     레이더 모드 인덱스에 해당하는 식별 시간 값을 리턴한다.
 * @param     int nRadarModeIndex
 * @param     EnumLibType enLibType
 * @return    int
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-25, 오전 9:41
 * @warning
 */
time_t CELSignalIdentifyAlg::GetUnknownEmitterTime( int nRadarModeIndex )
{
    time_t tiRet=0;

// 	if( nRadarModeIndex > 0 ) {
// 		SRadarMode *pRadarMode;
//
// 		pRadarMode = GP_MNGR_CED_LIB2->RTGetRadarModeDataFromMemory( nRadarModeIndex, enLibType );
// 		if( pRadarMode != NULL ) {
// 			tiRet = pRadarMode->nUnknownEmitterTime_ForGUI;
// 		}
//
// 	}

    return tiRet;
}

// /*!
//  * @brief     빔 번호에 해당되는 에미터의 우선 순위를 얻어온다.
//  * @param     int nRadarModeIndex
//  * @param     EnumLibType enLibType
//  * @return    int
//  * @version   1.0
//  예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
//  * @author    조철희
//  * @date      2014-10-09 오후 7:46
//  * @warning
//  */
// int CELSignalIdentifyAlg::GetRadarPriority( int nRadarIndex, EnumLibType enLibType )
// {
// 	int iRet=-1;
// 	SRadarMode *pRadarMode;
//
// 	if( nRadarIndex != 0 ) {
// 		pRadarMode = GP_MNGR_CED_LIB2->RTGetRadarDataFromMemory( nRadarIndex, enLibType );
// 		if( pRadarMode != NULL ) {
// 			iRet = pRadarMode->nPriority;
// 		}
// 		else {
// 			iRet = -1;
// 		}
// 	}
//
// 	return iRet;
// }
//
//
// /*!
//  * @brief     특정 레이더 모드에 해당하는 닉네임명을 리턴한다.
//  * @param     int iBeamID
//  * @return    char *
//  * @version   0.0.1
//  예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @date      2013-12-21 오전 10:48
//  * @warning
//  */
// char *CELSignalIdentifyAlg::GetNickName( int nRadarModeIndex, EnumLibType enLibType )
// {
// 	char *pRet = _stNullStr;
//
// 	if( nRadarModeIndex > 0 ) {
// 		bool bRet;
//
// 		bRet = GP_MNGR_CED_LIB2->RTGetRadarDataFromRadarModeIndex( & m_stRadar, nRadarModeIndex, enLibType );
//
// 		if( bRet == true ) {
// 			pRet = m_stRadar.szNickName;
// 		}
// 	}
//
// 	return pRet;
// }
//
// /**
//  * @brief     링크 1 또는 2에 해당하는 시스템 변수 값을 리턴한다.
//  * @param     int nLinkNum
//  * @return    SOCSystemVariable *
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-02-16, 오후 12:01
//  * @warning
//  */
// SOCSystemVariable *CELSignalIdentifyAlg::GetSystemVar( int nLinkNum )
// {
// 	SOCSystemVariable *pSystemVar;
//
// 	if( nLinkNum == -1 ) { //DTEC_Else
// 		pSystemVar = & m_stSystemVar[0];
// 	}
// 	else {
// 		pSystemVar = & m_stSystemVar[nLinkNum];
// 	}
//
// 	return pSystemVar;
// }
//
// /*!
//  * @brief     EOB 라이브러리에서 특정 EOBID의 Pin Number를 얻어온다.
//  * @return    UINT
//  * @param     int nThreatIndex
//  * @param     EnumLibType enLibType
//  * @version   1.0
//  예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
//  * @author    조철희
//  * @date      2014-12-29 오전 9:44
//  * @warning
//  */
// UINT CELSignalIdentifyAlg::GetEOBPinNumber( int nThreatIndex, EnumLibType enLibType )
// {
// 	UINT uRet=0;
//
// 	if( nThreatIndex > 0 ) {
// 		SThreat *pThreat;
//
// 		pThreat = GP_MNGR_CED_LIB2->RTGetThreatData( nThreatIndex, enLibType );
// 		if( pThreat == nullptr ) { //DTEC_NullPointCheck
// 			uRet = 0;
// 		}
// 		else {
// 			uRet = (UINT) pThreat->nPin;
// 		}
//
// 	}
//
// 	return uRet;
//
// }
//
// /**
//  * @brief     EOB의 위/경도 값을 리턴한다.
//  * @param     int * pLatitude
//  * @param     int * pLongitude
//  * @param     int nThreatIndex
//  * @param     int nDeviceIndex
//  * @param     EnumLibType enLibType
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-16, 오후 8:32
//  * @warning
//  */
// void CELSignalIdentifyAlg::GetEOBLatLong( int *pLatitude, int *pLongitude, int nThreatIndex, int nDeviceIndex, EnumLibType enLibType )
// {
// 	double dValue;
//
// 	*pLatitude = -1;
// 	*pLongitude = -1;
//
// 	SThreat *pThreat;
//
// 	pThreat = GP_MNGR_CED_LIB2->RTGetThreatData( nThreatIndex, enLibType );
// 	if( pThreat != nullptr ) {
// 		*pLatitude = pThreat->GetILatitude();
// 		dValue = *pLatitude / 10000.;
// 		dValue = DegMinSec2Degree( dValue );
// 		*pLatitude = (int) ( dValue * 1000000. + 0.5 );
//
// 		*pLongitude = pThreat->GetILongitude();
// 		dValue = *pLongitude / 10000.;
// 		dValue = DegMinSec2Degree( dValue );
// 		*pLongitude = (int) ( dValue * 1000000. + 0.5 );
// 	}
//
// 	return;
//
// }
//
// /**
//  * @brief     특정 위협의 경도 값을 리턴한다.
//  * @param     int nThreatIndex
//  * @param     EnumLibType enLibType
//  * @return    float
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2015-01-14, 오후 7:46
//  * @warning
//  */
// float CELSignalIdentifyAlg::GetEOBFLongitude( int nThreatIndex, EnumLibType enLibType )
// {
// 	float fRet;
//
// 	if( nThreatIndex <= 0 ) {
// 		fRet = -1.0;
// 	}
// 	else {
// 		SDevice *pDevice;
//
// 		pDevice = GP_MNGR_CED_LIB2->GetDeviceData( nThreatIndex, 1, enLibType );
// 		if( pDevice == nullptr ) { //DTEC_Else
// 			fRet = -1.0;
// 		}
// 		else {
// 			fRet = (float) pDevice->GetILongitude();
// 		}
// 	}
//
// 	return fRet;
// }
// /**
//  * @brief     특정 위협의 위도 값을 리턴한다.
//  * @param     int iEOBID
//  * @param     EnumLibType enLibType
//  * @return    float
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-12-08, 오후 8:25
//  * @warning
//  */
// float CELSignalIdentifyAlg::GetEOBFLatitude( int nThreatIndex, EnumLibType enLibType )
// {
// 	float fRet;
//
// 	if( nThreatIndex <= 0 ) {
// 		fRet = -1.0;
// 	}
// 	else {
// 		SDevice *pDevice;
//
// 		pDevice = GP_MNGR_CED_LIB2->GetDeviceData( nThreatIndex, 1, enLibType );
// 		if( pDevice == nullptr ) { //DTEC_NullPointCheck
// 			fRet = -1.0;
// 		}
// 		else  {
// 			fRet = (float) pDevice->GetLatitude();
// 		}
//
// 	}
//
// 	return fRet;
//
// }
// /*!
//  * @brief     시스템 변수를 입력 값으로 업데이트 한다.
//  * @return    void
//  * @param     int i_nLinkNo
//  * @param     SOCSystemVariable & i_stData
//  * @version   1.0
//  예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
//  * @author    유령$!
//  * @date      2014-10-14 오후 5:14
//  * @warning
//  */
// void CELSignalIdentifyAlg::SetSystemVariable( int i_nLinkNo, SOCSystemVariable &i_stData )
// {
// 	if( i_nLinkNo == 1 || i_nLinkNo == 2 ) {
// 		// m_pSystemVar[i_nLinkNo] = & i_stData;
// 		memcpy( & m_stSystemVar[i_nLinkNo], & i_stData, sizeof(SOCSystemVariable) );
// 	}
// 	else { //DTEC_Else
// 		TRACE( _T("시스템 변수에 잘못된 항공기 번호(%d)를 설정했습니다."), i_nLinkNo );
// 	}
// }

/**
 * @brief     식별 일치율에 대한 정렬 함수를 정의한다.
 * @param     const void * arg1
 * @param     const void * arg2
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-08, 오후 9:46
 * @warning
 */
int incRatioCompare( const void *arg1, const void *arg2 )
{
    int iRet;
    const STR_LIB_IDRESULT *p1, *p2;

    p1 = (const STR_LIB_IDRESULT *) arg1;
    p2 = (const STR_LIB_IDRESULT *) arg2;

    if( p1->uRatio < p2->uRatio ) {
        iRet = 1;
    }
    else if( p1->uRatio > p2->uRatio ) {
        iRet = -1;
    }
    else {
        iRet = 0;
    }

    return iRet;
}

/*!
 * @brief     식별 일치율을 계산하고 일치율 식별한다.
 * @return    void
 * @param     void
 * @version   1.0
 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희
 * @date      2015-01-04 오후 2:08
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyMatchRatio()
{
    UINT i, toLib;

    STR_LIB_IDRESULT *pIdxLib;

    // 1. 식별 후보의 일치율 계산
    CalcMatchRatio();

    // 2. 일치율 정렬
    qsort( m_pIdResult, (size_t) m_toLib, sizeof( STR_LIB_IDRESULT ), incRatioCompare );

    // 3. 일치율 식별
    toLib = 0;
    pIdxLib = & m_pIdResult[0];
    for( i=0 ; i < m_toLib ; ++i, ++pIdxLib ) {
        if( (int) pIdxLib->uRatio < m_pSEnvironVariable->iMatchRatio ) {
            break;
        }
    }

    m_toLib = i;


}

/*!
 * @brief     후보 식별의 모든 식별율을 계산한다.
 * @return    void
 * @param     void
 * @version   1.0
 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희
 * @date      2015-01-04 오후 2:15
 * @warning
 */
void CELSignalIdentifyAlg::CalcMatchRatio()
{
    UINT i;

    STR_LIB_IDRESULT *pIdxLib;

    pIdxLib = m_pIdResult;

    for( i=0 ; i < m_toLib ; ++i ) {
        float fRatio;
        SRadarMode* pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) {
            printf( "레이더 모드가 존재하지 않습니다." );
            continue;
        }

        // 신호 형태
        fRatio  = CalcMatchRatio( _SIG_TYPE_MATCHRATIO_, pRadarMode );

        // 주파수 형태
        fRatio += CalcMatchRatio( _FREQ_TYPE_MATCHRATIO_, pRadarMode );

        // 주파수 범위
        fRatio += CalcMatchRatio( _FREQ_RANGE_MATCHRATIO_, pRadarMode );

        // 주파수 변조 주기
        fRatio += CalcMatchRatio( _FREQ_PERIOD_MATCHRATIO_, pRadarMode );

        // 주파수 변조 포지션수
        fRatio += CalcMatchRatio( _FREQ_POSITION_MATCHRATIO_, pRadarMode );

        // 주파수 변조 엘리먼트 수
        //fRatio += CalcMatchRatio( _FREQ_ELEMENT_MATCHRATIO_, pRadarMode );

        // 주파수 주관측값
        fRatio += CalcMatchRatio( _FREQ_MAIN_RANGE_MATCHRATIO_, pRadarMode );

        // PRI 형태
        fRatio += CalcMatchRatio( _PRI_TYPE_MATCHRATIO_, pRadarMode );

        // PRI 범위
        fRatio += CalcMatchRatio( _PRI_RANGE_MATCHRATIO_, pRadarMode );

        // PRI 변조 주기
        fRatio += CalcMatchRatio( _PRI_PERIOD_MATCHRATIO_, pRadarMode );

        // PRI 포지션수
        fRatio += CalcMatchRatio( _PRI_POSITION_MATCHRATIO_, pRadarMode );

        // PRI 엘리먼트수
        //fRatio += CalcMatchRatio( _PRI_ELEMENT_MATCHRATIO_, pRadarMode );

        // PRI 주관측값
        //fRatio += CalcMatchRatio( _PRI_MAIN_RANGE_MATCHRATIO_, pRadarMode );

        // 펄스폭 비교
        fRatio += CalcMatchRatio( _PW_MATCHRATIO_, pRadarMode );

        pIdxLib->uRatio = (int) fRatio;
        ++ pIdxLib;

    }

}

/**
 * @brief     일치율 속송에 따라서 일치율 값을 리턴한다.
 * @param     EnumMATCHRATIO enMatchRatio
 * @param     SRadarMode * pRadarMode
 * @return    float
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-10-21, 오후 1:34
 * @warning
 */
float CELSignalIdentifyAlg::CalcMatchRatio( EnumMATCHRATIO enMatchRatio, SRadarMode *pRadarMode )
{
    //int i;
    float frate = 0.0; //, fDiff;

    //bool bret;

    //vector<SRadarRF_SpotValues>::pointer pRadarRF_SpotValues;
    //vector<SRadarPRI_SpotValues>::pointer pRadarPRI_SpotValues;

    //SOCSystemVariable *pSystemVar= GetSystemVar( m_nLinkNum );

    /*! \bug  신뢰성: 포인터 확인하여 예외처리 하게함.
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2015-10-5 17:37:35
    */
    if( pRadarMode != NULL ) { //DTEC_NullPointCheck
        switch( enMatchRatio ) {
            case _POSITION_MATCHRATIO_ :
            case _UNMATCHRATIO_ :
                // 식별 매칭율을 계산할 필요가 없음.
                break;

            // 신호 형태 비교
            case _SIG_TYPE_MATCHRATIO_ :
                frate = _DEFAULT_SIGNAL_TYPE_RATE;
                break;

            // 주파수 형태 비교
            case _FREQ_TYPE_MATCHRATIO_ :
                switch( m_pLOBData->iFreqType ) {
                case E_AET_FRQ_FIXED :
                    if( pRadarMode->eRF_Type == RadarModeFreqType::enumFIXED ) {
                        frate = _DEFAULT_FREQ_TYPE_RATE;
                    }
                    break;

                case E_AET_FRQ_AGILE :
                    if( pRadarMode->eRF_Type == RadarModeFreqType::enumAGILE ) {
                        frate = _DEFAULT_FREQ_TYPE_RATE;
                    }
                    break;

                case E_AET_FRQ_HOPPING :
                    // 비주기
                    if( pRadarMode->eRF_Type == RadarModeFreqType::enumHOPPING ) {
                        frate = _DEFAULT_FREQ_TYPE_RATE;
                    }

                    // 주기
                    if( pRadarMode->eRF_Type == RadarModeFreqType::enumHOPPING ) {
                        frate = _DEFAULT_FREQ_TYPE_RATE;
                    }
                    break;

                case E_AET_FRQ_PATTERN :
                    if( pRadarMode->eRF_Type == RadarModeFreqType::enumPATTERN ) {
                        frate = _DEFAULT_FREQ_TYPE_RATE;
                    }
                    break;

                default:
                    { //DTEC_Else
                    }
                    break;

                }

            // PRI 형태 비교
            case _PRI_TYPE_MATCHRATIO_ :
                switch( m_pLOBData->iPRIType ) {
                case E_AET_PRI_FIXED :
                    if( pRadarMode->ePRI_Type == RadarModePRIType::enumStable ) {
                        frate = _DEFAULT_PRI_TYPE_RATE;
                    }
                    break;

                case E_AET_PRI_STAGGER :
                    if( pRadarMode->ePRI_Type == RadarModePRIType::enumSTAGGER ) {
                        frate = _DEFAULT_PRI_TYPE_RATE;
                    }
                    break;

                case E_AET_PRI_DWELL_SWITCH :
                    if( pRadarMode->ePRI_Type == RadarModePRIType::enumDwellSWITCH ) {
                        frate = _DEFAULT_PRI_TYPE_RATE;
                    }
                    break;

                case E_AET_PRI_PATTERN :
                    if( pRadarMode->ePRI_Type == RadarModePRIType::enumPATTERN ) {
                        frate = _DEFAULT_PRI_TYPE_RATE;
                    }
                    break;

                case E_AET_PRI_JITTER :
                    if( pRadarMode->ePRI_Type == RadarModePRIType::enumJITTER ) {
                        frate = _DEFAULT_PRI_TYPE_RATE;
                    }
                    break;

                default:
                    { //DTEC_Else
                    }
                    break;
                }

                break;

            // 주파수 범위 비교
            case _FREQ_RANGE_MATCHRATIO_ :
                frate = (float) m_pSEnvironVariable->iWeightFrqRange;
                break;

            case _FREQ_PERIOD_MATCHRATIO_ :
                if( m_pLOBData->fFreqPatternPeriod > 0 ) {
                    frate = (float) m_pSEnvironVariable->iWeightFrqModPeriod;
                }
                break;

                // 주파수 포지션 비교
            case _FREQ_POSITION_MATCHRATIO_ :
                if( m_pLOBData->iFreqPositionCount > 0 && pRadarMode->nRF_NumPositions > 0 ) {
                    if( m_pLOBData->iFreqPositionCount == pRadarMode->nRF_NumPositions ) {
                        frate = (float) m_pSEnvironVariable->iWeightFrqModElement;
                    }
                    else {
                        frate = FDIV( m_pSEnvironVariable->iWeightFrqModElement, 2.0 );
                    }
                }
                break;

            case _FREQ_MAIN_RANGE_MATCHRATIO_ :
// 				pRadarRF_SpotValues = pRadarMode->vecRadarRF_SpotValues.data();
// 				for( i=0 ; i < (int) pRadarMode->vecRadarRF_SpotValues.size() ; ++i ) { //#FA_C_PotentialUnboundedLoop_T2
// 					if( CompMarginDiffFFF( m_optParameter.freq.fLow , (*pRadarRF_SpotValues).fRF_Min, (*pRadarRF_SpotValues).fRF_Max, m_optParameter.freq.fRangeError ) == TRUE ||
// 							CompMarginDiffFFF( m_optParameter.freq.fHigh, (*pRadarRF_SpotValues).fRF_Min, (*pRadarRF_SpotValues).fRF_Max, m_optParameter.freq.fRangeError ) == TRUE ) {
// 						frate = (float) m_pSELDBEnvVarIdnf->iWeightFrqMainObservedValue;
// 						break;
// 					}
//
// 					++ pRadarRF_SpotValues;
// 				}
                break;

                // PRI 범위 비교
            case _PRI_RANGE_MATCHRATIO_ :
                frate = (float) m_pSEnvironVariable->iWeightPriRange;
                break;

            case _PRI_PERIOD_MATCHRATIO_ :
                if( m_pLOBData->fPRIPatternPeriod > 0 ) {
                    frate = (float) m_pSEnvironVariable->iWeightPriModPeriod;
                }
                break;

            // PRI 포지션 비교
            case _PRI_POSITION_MATCHRATIO_ :
                if( m_pLOBData->iPRIPositionCount > 0 && pRadarMode->nPRI_NumPositions > 0 ) {
                    if( m_pLOBData->iPRIPositionCount == pRadarMode->nPRI_NumPositions ) {
                        frate = (float) m_pSEnvironVariable->iWeightPriModPosCount;
                    }
                    else {
                        frate = FDIV( m_pSEnvironVariable->iWeightPriModPosCount, 2.0 );
                    }
                }
                break;

// 			case _PRI_MAIN_RANGE_MATCHRATIO_ :
// 				pRadarPRI_SpotValues = pRadarMode->vecRadarPRI_SpotValues.data();
// 				for( i=0 ; i < (int) pRadarMode->vecRadarPRI_SpotValues.size() ; ++i ) { //#FA_C_PotentialUnboundedLoop_T2
// 					if( CompMarginDiffFFF( m_optParameter.pri.fLow , (*pRadarPRI_SpotValues).fPRI_Min, (*pRadarPRI_SpotValues).fPRI_Max, m_optParameter.pri.fRangeError ) == TRUE ||
// 							CompMarginDiffFFF( m_optParameter.pri.fHigh, (*pRadarPRI_SpotValues).fPRI_Min, (*pRadarPRI_SpotValues).fPRI_Max, m_optParameter.pri.fRangeError ) == TRUE ) {
// 						frate = (float) m_pSELDBEnvVarIdnf->iWeightPriMainObservedValue;
// 						break;
// 					}
//
// 					++ pRadarPRI_SpotValues;
// 				}
// 				break;

            // 펄스폭 범위
            case _PW_MATCHRATIO_ :
                if( Is_FNotZero( pRadarMode->fPD_TypicalMin ) == true && Is_FNotZero( pRadarMode->fPD_TypicalMax ) == true ) {
                    if( CompMarginDiff<float>( m_pLOBData->fMeanPW, pRadarMode->fPD_TypicalMin, pRadarMode->fPD_TypicalMax, 0 ) == _spTrue ) {
                        frate = (float) _DEFAULT_PW_RANGE_RATE;
                    }
                }
                break;

            default:
                { //DTEC_Else
                }
                break;
        }
    }

    return frate;
}
//
// /**
//  * @brief     식별할 주파수/PRI 속성 값을 참조하여 변조 코드를 생성한다.
//  * @param     char * pModeCode
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-02-16, 오후 3:52
//  * @warning
//  */
// void CELSignalIdentifyAlg::MakeModulationCode( char *pModeCode )
// {
// 	int ftype, ptype;
//
// 	ftype = m_IdAet.aet.Frequency.type;
// 	ptype = m_IdAet.aet.PRI.type;
//
// 	// Normal
// 	if( m_IdAet.aet.ucSignalType == ST_NORMAL_PULSE ) {
// 		// 1st Position 기록하기
// 		switch( ftype ) {
// 		case _FIXED :
//
// 			if( m_IdAet.aet.Mop.type == E_AET_MOP_FSK || m_IdAet.aet.Mop.type == E_AET_MOP_LFM || m_IdAet.aet.Mop.type == E_AET_MOP_NLFM ) {
// 				*pModeCode = 'K';
// 			}
// 			else if( m_IdAet.aet.Mop.type == E_AET_MOP_PSK ) {
// 				*pModeCode = 'L';
// 			}
// 			else {
// 				*pModeCode = 'B';
// 			}
// 			break;
//
// 		case _RANDOM_AGILE :
// 			*pModeCode = 'O';
// 			break;
//
// 		case _PATTERN_AGILE :
// 			if( m_IdAet.aet.Frequency.patType == UNK ) {
// 				*pModeCode = 'N';
// 			}
// 			else {
// 				*pModeCode = 'U';
// 			}
// 			break;
//
// 		case _HOPPING :
// 			*pModeCode = 'V';
// 			break;
//
// 		default :
// 			{ //DTEC_Else
// 				*pModeCode = ' ';
// 			}
//
// 			break;
// 		}
//
// 		++ pModeCode;
//
// 		// 2nd Position 기록하기
// 		switch( ptype ) {
// 		case _STABLE :
// 			*pModeCode = 'D';
// 			break;
//
// 		case _DWELL :
// 			*pModeCode = 'S';
// 			break;
//
// 		case _STAGGER :
// 			*pModeCode = 'M';
// 			break;
//
// 		case _JITTER_RANDOM :
// 			*pModeCode = 'C';
// 			break;
//
// 		case _JITTER_PATTERN :
// 			if( m_IdAet.aet.Frequency.patType == SINE ) {
// 				*pModeCode = 'V';
// 			}
// 			else if( m_IdAet.aet.Frequency.patType == SLD_INC || m_IdAet.aet.Frequency.patType == SLD_DEC ) {
// 				*pModeCode = 'T';
// 			}
// 			else if( m_IdAet.aet.Frequency.patType == UNK ) {
// 				*pModeCode = 'N';
// 			}
// 			else {
// 				*pModeCode = 'N';
// 			}
// 			break;
//
// 		default :
// 			{ //DTEC_Else
// 				*pModeCode = ' ';
// 			}
// 			break;
// 		}
// 	}
// 	else {
// 		// 1st Position 기록하기
// 		switch( m_IdAet.aet.Mop.type ) {
// 		case E_AET_MOP_NM :
// 			*pModeCode = 'C';
// 			break;
//
// 		case E_AET_MOP_PSK :
// 			*pModeCode = 'P';
// 			break;
//
// 		case E_AET_MOP_FSK :
// 			*pModeCode = 'F';
// 			break;
//
// 		case E_AET_MOP_LFM :
// 		case E_AET_MOP_NLFM :
// 			*pModeCode = 'F';
// 			break;
//
// 		case E_AET_MOP_UNK :
// 			*pModeCode = 'D';
// 			break;
//
// 		default :
// 			{ //DTEC_Else
// 				*pModeCode = ' ';
// 			}
// 			break;
// 		}
//
// 		++ pModeCode;
//
// 		// 2nd Position 기록하기
// 		switch( m_IdAet.aet.Mop.type ) {
// 		case E_AET_MOP_NM :
// 			*pModeCode = 'U';
// 			break;
//
// 		case E_AET_MOP_PSK :
// 			*pModeCode = 'Z';
// 			break;
//
// 		case E_AET_MOP_FSK :
// 			*pModeCode = 'S';
// 			break;
//
// 		case E_AET_MOP_LFM :
// 		case E_AET_MOP_NLFM :
// 		case E_AET_MOP_UNK :
// 			*pModeCode = 'Z';
// 			break;
//
// 		default :
// 			{ //DTEC_Else
// 				*pModeCode = ' ';
// 			}
// 			break;
// 		}
//
// 	}
//
// }
//
// /**
//  * @brief     입력한 RadarModeIndex에 따른 RadarModeData 포인터를 리턴한다.
//  * @param     int nRadarModeIndex
//  * @param     EnumLibType enLibType
//  * @return    SRadarMode *
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-07, 오후 5:29
//  * @warning
//  */
// SRadarMode *CELSignalIdentifyAlg::GetRadarModeData( int nRadarModeIndex, EnumLibType enLibType )
// {
// 	SRadarMode *pRadarMode;
// 	SRadarMode *pRet = NULL;
//
// 	if( nRadarModeIndex != 0 ) {
// 		pRadarMode = GP_MNGR_CED_LIB2->RTGetRadarModeDataFromMemory( nRadarModeIndex, enLibType );
// 		pRet = pRadarMode;
// 	}
//
// 	return pRet;
// }
//
// /**
//  * @brief     입력한 두 지점 사이의 거리를 계산한다.
//  * @param     int iLat1
//  * @param     int iLong1
//  * @param     int iLat2
//  * @param     int iLong2
//  * @return    int
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-16, 오후 8:38
//  * @warning
//  */
// int CELSignalIdentifyAlg::CalDistanceNM( int iLat1, int iLong1, int iLat2, int iLong2 )
// {
// 	int iDistance;
// 	SELDISTLOB distlob;
//
// 	if( iLat1 > 0 && iLong1 > 0 && iLat2 > 0 && iLong2 > 0 ) {
// 		ST_IMA->VincentyInverse( & distlob, DLATITUDE2LAT(iLat1), DLONGITUDE2LONG(iLong1), DLATITUDE2LAT(iLat2), DLONGITUDE2LONG(iLong2) );
//
// 		iDistance = (int) ( distlob.dDistance + 0.5 );
// 		iDistance = M2NMM( iDistance );
// 	}
// 	else { //DTEC_Else
// 		iDistance = -1;
// 	}
// 	return iDistance;
//
// }

/**
 * @brief     두 레이더모드의 전정보호의 알파벳 순을 확인한다.
 * @param     SRadarMode* pRadarModeRef
 * @param			SRadarMode *pRadarModeNxt
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-16, 오후 8:38
 * @warning
 */
bool CELSignalIdentifyAlg::IsSortELNOT( SRadarMode* pRadarModeRef, SRadarMode *pRadarModeNxt )
{
    bool bRet = true;
// 	int iCmp = strcmp( pRadarModeRef->szELNOT, pRadarModeNxt->szELNOT );
//
// 	if( iCmp < 0 ) {
// 		bRet = false;
// 	}
// 	else if( iCmp == 0 ) {
// 		if( pRadarModeRef->nRadarModeIndex <= pRadarModeNxt->nRadarModeIndex ) {
// 			bRet = false;
// 		}
// 	}

    return bRet;
}

/**
  * @brief
  * @param		int iRadarModeIndex
  * @return 	char *
  * @return		성공시 true, 실패시 false
  * @date		2019/04/25 14:55
*/
char *CELSignalIdentifyAlg::GetRadarModeName( int iRadarModeIndex )
{
    int i;
    char *pRadarName=NULL;
    SRadarMode *pRadarMode=m_pRadarMode;

    for( i=0 ; i < m_iRadarMode ; ++i ) {
        if( pRadarMode->iRadarModeIndex == iRadarModeIndex ) {
            pRadarName = pRadarMode->szRadarModeName;
            break;
        }
        ++ pRadarMode;
    }

    return pRadarName;

}

/**
 * @brief CELSignalIdentifyAlg::IsThereFreqRange
 * @param puiCoKnownRadarMode
 * @param pMatchRadarMode
 * @param uiFreqMin
 * @param uiFreqMax
 * @return
 */
bool CELSignalIdentifyAlg::IsThereFreqRange( UINT *puiCoKnownRadarMode, SRadarMode **pMatchRadarMode, UINT uiFreqMin, UINT uiFreqMax )
{
    UINT i, j;
    bool bRet=false;
    STR_FLOWHIGH band=STR_FLOWHIGH();

    STR_FLIB *pFLib;
    SRadarMode *pRadarMode;

    SRadarMode **pBackupMatchRadarMode;

    UINT _uiFreqMin, _uiFreqMax;

    pBackupMatchRadarMode = pMatchRadarMode;

    *puiCoKnownRadarMode = 0;

    _uiFreqMin = FRQMhzCNV( 0, uiFreqMin );
    _uiFreqMax = FRQMhzCNV( 0, uiFreqMax );

    band.ilow = (int) BandSelect( 0, (UINT)NO_FLIB_BAND-1, (int) _uiFreqMin );
    band.ihgh = (int) BandSelect( 0, (UINT)NO_FLIB_BAND-1, (int) _uiFreqMax );

    pFLib = & m_pFLib[band.ilow];
    for( i=(UINT) band.ilow ; i <= (UINT) band.ihgh ; ++i ) {
        pRadarMode = pFLib->pIdxRadarMode[0];
        for( j=0 ; j < pFLib->uicount ; ++ j ) {
            if( CalOverlapSpace<float>( (float) _uiFreqMax, (float) _uiFreqMin, pRadarMode->fRF_TypicalMax, pRadarMode->fRF_TypicalMin ) > 0 ) {
                    //CompMarginDiff<float>( (float) _uiFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == TRUE &&
                    //CompMarginDiff<float>( (float) _uiFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == TRUE ) {

                *pBackupMatchRadarMode = pRadarMode;

                ++ *puiCoKnownRadarMode;

                ++ pBackupMatchRadarMode;

                bRet = true;
            }
            ++ pRadarMode;
        }
        ++ pFLib;
    }

    if( bRet == true ) {
        char buffer[200];
        int iCnt=0;

        //printf( "\n ***라이브러리 기반 분석" );
        //Log( enNormal, "***라이브러리 기반 분석" );
        pBackupMatchRadarMode = pMatchRadarMode;
        for( i=0 ; i < *puiCoKnownRadarMode ; ++i ) {
#ifdef _WIN32
            iCnt += sprintf_s( & buffer[iCnt], sizeof(buffer)-iCnt, "(%s, %s)", aet_freq_type[(*pBackupMatchRadarMode)->eFreqType], aet_pri_type[(*pBackupMatchRadarMode)->ePRIType] );
#else
            iCnt += sprintf( & buffer[iCnt], "(%s, %s)", aet_freq_type[(*pBackupMatchRadarMode)->eRF_Type], aet_pri_type[(*pBackupMatchRadarMode)->ePRI_Type] );
#endif
            ++ pBackupMatchRadarMode;

            if( iCnt >= (int) sizeof(buffer)-40 ) {
                break;
            }

        }
        printf( "\n 레이더 모드 매칭 결과[%d] : %s" , *puiCoKnownRadarMode, buffer );
        Log( enNormal, "레이더 모드 매칭 결과[%d] : %s" , *puiCoKnownRadarMode, buffer );
    }

    return bRet;

}

/**
 * @brief CELSignalIdentifyAlg::LoadRadarModeData
 * @param pnRadarMode
 * @param pRadarMode
 * @param iMaxItems
 * @return
 */
void CELSignalIdentifyAlg::LoadRadarModeData( int *pnRadarMode, SRadarMode *pRadarMode, int iMaxItems )
{
    *pnRadarMode = 0;

#ifdef _SQLITE_
    int i;
    Database *pDatabase;

    pDatabase = GetDatabase();

    sprintf( m_pszSQLString, "SELECT RM_RADAR_MODE_INDEX, RM_FUNCTION_CODE, RM_SIGNAL_TYPE, RM_POLARIZATION, RM_PLATFORM, RM_VALIDATION, \
                             RM_RF_TYPE, RM_RF_TYPICAL_MIN, RM_RF_TYPICAL_MAX, RM_RF_PATTERN, RM_RF_NUM_ELEMENTS, RM_RF_NUM_POSITIONS, RM_RF_PATTERN_PERIOD_MIN, RM_RF_PATTERN_PERIOD_MAX, RM_RF_MEAN_MIN, RM_RF_MEAN_MAX, \
                             RM_PRI_TYPE, RM_PRI_TYPICAL_MIN, RM_PRI_TYPICAL_MAX, RM_PRI_PATTERN, RM_PRI_NUM_ELEMENTS, RM_PRI_NUM_POSITIONS, RM_PRI_PATTERN_PERIOD_MIN, RM_PRI_PATTERN_PERIOD_MAX, RM_PRI_MEAN_MIN, RM_PRI_MEAN_MAX, \
                             RM_PD_TYPICAL_MIN, RM_PD_TYPICAL_MAX, \
                             RM_SCAN_PRIMARY_TYPE, RM_SCAN_PRIMARY_TYPICAL_MIN, RM_SCAN_PRIMARY_TYPICAL_MAX, RM_SCAN_SECONDARY_TYPE, RM_SCAN_SECONDARY_TYPICAL_MIN, RM_SCAN_SECONDARY_TYPICAL_MAX, RM_MODULATION_CODE, RM_PRIORITY, \
                             RML_RADAR_INDEX, RML_RADAR_MODE_NAME, RML_MODE_CODE, \
                             R_PRIORITY, R_ELNOT, R_NICKNAME, R_TIME_INACTIVATED, \
                             D_THREAT_INDEX, D_DEVICE_INDEX, D_ELNOT \
                             FROM VEL_RADARMODE_LIST ORDER BY RM_RADAR_MODE_INDEX" );
    SQLite::Statement query( *pDatabase, m_pszSQLString );

    while( query.executeStep() ) {
        int iValue;
        char buffer[100];

        i = 0;

        pRadarMode->iRadarModeIndex = query.getColumn(i++).getInt();

        strcpy( buffer, query.getColumn(i++).getText() );
        pRadarMode->eFunctionCode = GetFunctionCodes( buffer );

        strcpy( buffer, query.getColumn(i++).getText() );
        pRadarMode->eSignalType = GetSignalType( buffer );

        iValue = query.getColumn(i++).getInt();
        pRadarMode->ePolarization = GetPolarizationCodes( iValue );

        iValue = query.getColumn(i++).getInt();
        pRadarMode->ePlatform = GetPlatformCode( iValue );

        iValue = query.getColumn(i++).getInt();
        pRadarMode->eValidation = GetValidationCode( iValue );

        // 주파수 정보
        iValue = query.getColumn(i++).getInt();
        pRadarMode->eRF_Type = GetFreqType( iValue );

        pRadarMode->fRF_TypicalMin = (float) query.getColumn(i++).getDouble();
        pRadarMode->fRF_TypicalMax = (float) query.getColumn(i++).getDouble();

        iValue = query.getColumn(i++).getInt();
        pRadarMode->eRF_Pattern = GetPatternCode( iValue );

        pRadarMode->nRF_NumElements = query.getColumn(i++).getInt();
        pRadarMode->nRF_NumPositions = query.getColumn(i++).getInt();

        pRadarMode->fRF_PatternPeriodMin = (float) query.getColumn(i++).getDouble();
        pRadarMode->fRF_PatternPeriodMax = (float) query.getColumn(i++).getDouble();

        pRadarMode->fRF_MeanMin = (float) query.getColumn(i++).getDouble();
        pRadarMode->fRF_MeanMax = (float) query.getColumn(i++).getDouble();

        // PRI 정보
        iValue = query.getColumn(i++).getInt();
        pRadarMode->ePRI_Type = GetPRIType( iValue );

        pRadarMode->fPRI_TypicalMin = (float) query.getColumn(i++).getDouble();
        pRadarMode->fPRI_TypicalMax = (float) query.getColumn(i++).getDouble();

        iValue = query.getColumn(i++).getInt();
        pRadarMode->ePRI_Pattern = GetPatternCode( iValue );

        pRadarMode->nPRI_NumElements = query.getColumn(i++).getInt();
        pRadarMode->nPRI_NumPositions = query.getColumn(i++).getInt();

        pRadarMode->fPRI_PatternPeriodMin = (float) query.getColumn(i++).getDouble();
        pRadarMode->fPRI_PatternPeriodMax = (float) query.getColumn(i++).getDouble();

        pRadarMode->fPRI_MeanMin = (float) query.getColumn(i++).getDouble();
        pRadarMode->fPRI_MeanMax = (float) query.getColumn(i++).getDouble();

        // 펄스폭 정보
        pRadarMode->fPD_TypicalMin = (float) query.getColumn(i++).getDouble();
        pRadarMode->fPD_TypicalMax = (float) query.getColumn(i++).getDouble();

        // 스캔 정보
        iValue = query.getColumn(i++).getInt();
        pRadarMode->eScanPrimaryType = GetScanType( iValue );
        pRadarMode->fScanPrimaryTypicalMin = (float) query.getColumn(i++).getDouble();
        pRadarMode->fScanPrimaryTypicalMax = (float) query.getColumn(i++).getDouble();

        iValue = query.getColumn(i++).getInt();
        pRadarMode->eScanSecondaryType = GetScanType( iValue );
        pRadarMode->fScanSecondaryTypicalMin = (float) query.getColumn(i++).getDouble();
        pRadarMode->fScanSecondaryTypicalMax = (float) query.getColumn(i++).getDouble();

        // 기타 정보
        //pRadarMode->nAssocIndex	= query.getColumn(i++).getInt();													//모드 간 연관관계에 대한 링크
        strcpy( pRadarMode->szModulationCode, query.getColumn(i++).getText() );
        pRadarMode->iRadarModePriority = query.getColumn(i++).getInt();

        // 레이더 정보
        pRadarMode->iRadarIndex = query.getColumn(i++).getInt();
        strcpy( pRadarMode->szRadarModeName, query.getColumn(i++).getText() );
        strcpy( pRadarMode->szModeCode, query.getColumn(i++).getText() );

        pRadarMode->iRadarPriority = query.getColumn(i++).getInt();
        strcpy( pRadarMode->szELNOT, query.getColumn(i++).getText() );
        strcpy( pRadarMode->szNickName, query.getColumn(i++).getText() );
        pRadarMode->iTimeInactivated = query.getColumn(i++).getInt();

        pRadarMode->iThreatIndex = query.getColumn(i++).getInt();
        pRadarMode->iDeviceIndex = query.getColumn(i++).getInt();

        if( pRadarMode->eValidation == enumValidated ) {
            ++ *pnRadarMode;
            ++ pRadarMode;
        }

        if( iMaxItems != 0 && *pnRadarMode >= iMaxItems ) {
            break;
        }

    }
#else
    DECLARE_BEGIN_CHECKODBC
    int index;

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    sprintf_s( m_pszSQLString, MAX_SQL_SIZE,  "SELECT * FROM RADARMODE ORDER BY RADAR_MODE_INDEX" );

    theRS.Open( m_pszSQLString );

    while (!theRS.IsEof()) {
        index = 0;

        theRS.GetFieldValue( index++, & pRadarMode->iRadarModeIndex );

        theRS.GetFieldValue( index++, pRadarMode->szRadarName );

        theRS.GetFieldTimeValue( index++, & pRadarMode->tiCreated );
        theRS.GetFieldTimeValue( index++, & pRadarMode->tiLastUpdated );

        theRS.GetFieldTimeValue( index++, & pRadarMode->tiFirstSeen );
        theRS.GetFieldTimeValue( index++, & pRadarMode->tiLastSeen );

        theRS.GetFieldValue( index++, (int *) & pRadarMode->ePlatform );

        theRS.GetFieldValue( index++, (int *) & pRadarMode->eSignalType );

        theRS.GetFieldValue( index++, (int *) & pRadarMode->eFreqType );
        theRS.GetFieldValue( index++, & pRadarMode->fRF_TypicalMin );
        theRS.GetFieldValue( index++, & pRadarMode->fRF_TypicalMax );
        theRS.GetFieldValue( index++, (int *) & pRadarMode->eRF_PatternType );
        theRS.GetFieldValue( index++, & pRadarMode->nRF_NumPositions );
        theRS.GetFieldValue( index++, & pRadarMode->fRF_PatternPeriodMin );
        theRS.GetFieldValue( index++, & pRadarMode->fRF_PatternPeriodMax );

        theRS.GetFieldValue( index++, (int *) & pRadarMode->ePRIType );
        theRS.GetFieldValue( index++, & pRadarMode->fPRI_TypicalMin );
        theRS.GetFieldValue( index++, & pRadarMode->fPRI_TypicalMax );
        theRS.GetFieldValue( index++, (int *) & pRadarMode->ePRI_PatternType );
        theRS.GetFieldValue( index++, & pRadarMode->nPRI_NumPositions );
        theRS.GetFieldValue( index++, & pRadarMode->fPRI_PatternPeriodMin );
        theRS.GetFieldValue( index++, & pRadarMode->fPRI_PatternPeriodMax );

        theRS.GetFieldValue( index++, & pRadarMode->fPD_TypicalMin );
        theRS.GetFieldValue( index++, & pRadarMode->fPD_TypicalMax );

        theRS.GetFieldValue( index++, (int *) & pRadarMode->eValidation );

        if( pRadarMode->eValidation == enumValidated ) {
            ++ *pnRadarMode;
            ++ pRadarMode;
        }

        if( iMaxItems != 0 && *pnRadarMode >= iMaxItems ) {
            break;
        }

        theRS.MoveNext();
    }

    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN
#endif

}

void CELSignalIdentifyAlg::LoadRadarMode_RFSequence( vector<SRadarMode_Sequence_Values*> *pVecRadarMode_RFSequence, int nMaxRadarMode )
{
    SRadarMode_Sequence_Values *pRadarMode_RFSequence_Values;

#ifdef _SQLITE_
    int i;
    Database *pDatabase;

    pDatabase = GetDatabase();

    sprintf( m_pszSQLString, "SELECT RADAR_MODE_INDEX, RF_INDEX, RF_MIN, RF_MAX FROM VEL_RADAR_RF_SEQENCE ORDER BY RADAR_MODE_INDEX, RF_SEQ_ID" );
    SQLite::Statement query( *pDatabase, m_pszSQLString );

    pVecRadarMode_RFSequence->clear();
    pVecRadarMode_RFSequence->reserve( nMaxRadarMode * MAX_FREQ_PRI_STEP );

    while( query.executeStep() ) {
        i = 0;

        pRadarMode_RFSequence_Values = new SRadarMode_Sequence_Values;

        pRadarMode_RFSequence_Values->iRadarModeIndex = query.getColumn(i++).getInt();
        pRadarMode_RFSequence_Values->i_Index = query.getColumn(i++).getInt();

        pRadarMode_RFSequence_Values->f_Min = (float) query.getColumn(i++).getDouble();
        pRadarMode_RFSequence_Values->f_Max = (float) query.getColumn(i++).getDouble();

        pVecRadarMode_RFSequence->push_back( pRadarMode_RFSequence_Values );

    }

#else
    DECLARE_BEGIN_CHECKODBC
    int index;



    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "SELECT RADAR_MODE_INDEX, PRI_SEQ_ID, PRI_MIN, PRI_MAX FROM RADARMODE_PRI_SEQUENCE ORDER BY RADAR_MODE_INDEX ASC, PRI_SEQ_ID ASC" );
    theRS.Open( m_pszSQLString );

    pVecRadarMode_PRISequence->reserve( nMaxRadarMode * MAX_FREQ_PRI_STEP );
    DeletePointers( *pVecRadarMode_PRISequence );

    while (!theRS.IsEof()) {
        index = 0;

        pRadarMode_PRISequence_Values = new SRadarMode_PRISequence_Values;

        theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->iRadarModeIndex );
        theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->iPRI_Index );

        theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->fPRI_Min );
        theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->fPRI_Max );

        pVecRadarMode_PRISequence->push_back( pRadarMode_PRISequence_Values );

        theRS.MoveNext();

    }

    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN
#endif

}

/**
 * @brief CELSignalIdentifyAlg::LoadRadarMode_PRISequence
 * @param pVecRadarMode_PRISequence
 * @param nMaxRadarMode
 */
void CELSignalIdentifyAlg::LoadRadarMode_PRISequence( vector<SRadarMode_Sequence_Values*> *pVecRadarMode_PRISequence, int nMaxRadarMode )
{
    SRadarMode_Sequence_Values *pRadarMode_PRISequence_Values;

#ifdef _SQLITE_
    int i;
    Database *pDatabase;

    pDatabase = GetDatabase();

    sprintf( m_pszSQLString, "SELECT RADAR_MODE_INDEX, PRI_INDEX, PRI_MIN, PRI_MAX FROM VEL_RADAR_PRI_SEQENCE ORDER BY RADAR_MODE_INDEX, PRI_SEQ_ID" );
    SQLite::Statement query( *pDatabase, m_pszSQLString );

    pVecRadarMode_PRISequence->clear();
    pVecRadarMode_PRISequence->reserve( nMaxRadarMode * MAX_FREQ_PRI_STEP );

    while( query.executeStep() ) {
        i = 0;

        pRadarMode_PRISequence_Values = new SRadarMode_Sequence_Values;

        pRadarMode_PRISequence_Values->iRadarModeIndex = query.getColumn(i++).getInt();
        pRadarMode_PRISequence_Values->i_Index = query.getColumn(i++).getInt();

        pRadarMode_PRISequence_Values->f_Min = (float) query.getColumn(i++).getDouble();
        pRadarMode_PRISequence_Values->f_Max = (float) query.getColumn(i++).getDouble();

        pVecRadarMode_PRISequence->push_back( pRadarMode_PRISequence_Values );

    }

#else
    DECLARE_BEGIN_CHECKODBC
    int index;



    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "SELECT RADAR_MODE_INDEX, PRI_SEQ_ID, PRI_MIN, PRI_MAX FROM RADARMODE_PRI_SEQUENCE ORDER BY RADAR_MODE_INDEX ASC, PRI_SEQ_ID ASC" );
    theRS.Open( m_pszSQLString );

    pVecRadarMode_PRISequence->reserve( nMaxRadarMode * MAX_FREQ_PRI_STEP );
    DeletePointers( *pVecRadarMode_PRISequence );

    while (!theRS.IsEof()) {
        index = 0;

        pRadarMode_PRISequence_Values = new SRadarMode_PRISequence_Values;

        theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->iRadarModeIndex );
        theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->iPRI_Index );

        theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->fPRI_Min );
        theRS.GetFieldValue( index++, & pRadarMode_PRISequence_Values->fPRI_Max );

        pVecRadarMode_PRISequence->push_back( pRadarMode_PRISequence_Values );

        theRS.MoveNext();

    }

    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN
#endif

}


bool CELSignalIdentifyAlg::LoadThreatData( int *pnThreat, SThreat *pThreat, int iMaxItems )
{
    bool bRet=true;
    return bRet;
}

/**
 * @brief CELSignalIdentifyAlg::GetFunctionCodes
 * @param pData
 * @return
 */
EnumFunctionCodes CELSignalIdentifyAlg::GetFunctionCodes( char *pData )
{
    CString sTemp ="";
    EnumFunctionCodes eFunctionCodes_ForGUI = enumUndefinedFunctionCode;

    if ( pData != NULL ) {
        for (int i = (int)enumAA_Anti_Aircraft_Fire_Control; i <= (int)enumXP_Experimental_or_Trainer; i++) {
            if( pData[0] == _FunctionCodes[i][0] && pData[1] == _FunctionCodes[i][1] )
            {
                eFunctionCodes_ForGUI = (EnumFunctionCodes)i;
                break;
            }
        }
    }

    return eFunctionCodes_ForGUI;
}

/**
 * @brief CELSignalIdentifyAlg::GetFunctionCodes
 * @param eFunctionCode
 * @return
 */
char *CELSignalIdentifyAlg::GetFunctionCode( EnumFunctionCodes eFunctionCode )
{

    if( eFunctionCode >= enumAA_Anti_Aircraft_Fire_Control && eFunctionCode <= enumXP_Experimental_or_Trainer ) {
    }
    else {
        eFunctionCode = enumAA_Anti_Aircraft_Fire_Control;
    }

    return _FunctionCodes[eFunctionCode];

}


/**
 * @brief CELSignalIdentifyAlg::GetSignalType
 * @param pData
 * @return
 */
SignalType::EnumSignalType CELSignalIdentifyAlg::GetSignalType( char *pData )
{
    SignalType::EnumSignalType eSignalType = SignalType::enumPulsed;

    if ( pData != NULL ) {
        for (int i = (int)SignalType::enumPulsed; i <= (int)SignalType::enumEA; i++) {
            if (strcmp( pData, _SignalType[i] ) == 0 ) {
                eSignalType = (SignalType::EnumSignalType)i;
                break;
            }
        }
    }

    return eSignalType;
}

/**
 * @brief CELSignalIdentifyAlg::GetPolarizationCodes
 * @param iPolization
 * @return
 */
PolizationCode::EnumPolizationCode CELSignalIdentifyAlg::GetPolarizationCodes( int iPolization )
{
    PolizationCode::EnumPolizationCode ePolarization = PolizationCode::enumUndefinedPolization;

    if ( iPolization >= PolizationCode::enumC_Diverse_Agile_or_adaptive_Capable_of_pulse_to_pulse_agility && \
         iPolization <= PolizationCode::enumZ_Undetermined ) {
        ePolarization = (PolizationCode::EnumPolizationCode) iPolization;
    }

    return ePolarization;
}

/**
 * @brief CELSignalIdentifyAlg::GetPlatformCode
 * @param iPlatform
 * @return
 */
PlatformCode::EnumPlatformCode CELSignalIdentifyAlg::GetPlatformCode( int iPlatform )
{
    PlatformCode::EnumPlatformCode ePlatform = PlatformCode::enumUndefinedPlatformCode;

    if ( iPlatform >= PlatformCode::enumUndefinedPlatformCode && iPlatform <= PlatformCode::enumAir ) {
        ePlatform = (PlatformCode::EnumPlatformCode) iPlatform;
    }

    return ePlatform;
}

/**
 * @brief CELSignalIdentifyAlg::GetPlatformCode
 * @param ePlatform
 * @return
 */
char *CELSignalIdentifyAlg::GetPlatformCode( PlatformCode::EnumPlatformCode ePlatform )
{
    char *pChar = _PlatformCodes[PlatformCode::enumUnKnown];

    if ( ePlatform >= PlatformCode::enumUnKnown && ePlatform <= PlatformCode::enumAir ) {
        pChar = _PlatformCodes[ePlatform];
    }

    return pChar;
}

/**
 * @brief CELSignalIdentifyAlg::GetPatternCode
 * @param iPattern
 * @return
 */
PatternCode::EnumPatternCode CELSignalIdentifyAlg::GetPatternCode( int iPattern )
{
    PatternCode::EnumPatternCode ePattern = PatternCode::enumUndefinedPatternCode;

    if ( iPattern >= PatternCode::enumUndefinedPatternCode && iPattern <= PatternCode::enumUnmodulated ) {
        ePattern = (PatternCode::EnumPatternCode) iPattern;
    }

    return ePattern;
}

/**
 * @brief CELSignalIdentifyAlg::GetFreqType
 * @param iFreqType
 * @return
 */
RadarModeFreqType::EnumRadarModeFreqType CELSignalIdentifyAlg::GetFreqType( int iFreqType )
{
    RadarModeFreqType::EnumRadarModeFreqType eFreqType = RadarModeFreqType::enumFIXED;

    if ( iFreqType >= RadarModeFreqType::enumFIXED && iFreqType <= RadarModeFreqType::enumPATTERN ) {
        eFreqType = (RadarModeFreqType::EnumRadarModeFreqType) iFreqType;
    }

    return eFreqType;
}

/**
 * @brief CELSignalIdentifyAlg::GetPRIType
 * @param iPRIType
 * @return
 */
RadarModePRIType::EnumRadarModePRIType CELSignalIdentifyAlg::GetPRIType( int iPRIType )
{
    RadarModePRIType::EnumRadarModePRIType ePRIType = RadarModePRIType::enumStable;

    if ( iPRIType >= RadarModePRIType::enumStable && iPRIType <= RadarModePRIType::enumPATTERN ) {
        ePRIType = (RadarModePRIType::EnumRadarModePRIType) iPRIType;
    }

    return ePRIType;
}

/**
 * @brief CELSignalIdentifyAlg::GetScanType
 * @param iScanType
 * @return
 */
ScanType::EnumScanType CELSignalIdentifyAlg::GetScanType( int iScanType )
{
    ScanType::EnumScanType eScanType = ScanType::enumUndefinedScanType;

    if ( iScanType >= ScanType::enumA_Circular && iScanType <= ScanType::enumZ_Undetermined ) {
        eScanType = (ScanType::EnumScanType) iScanType;
    }

    return eScanType;
}

/**
 * @brief CELSignalIdentifyAlg::GetValidation
 * @param iValidation
 * @return
 */
EnumValidationCode CELSignalIdentifyAlg::GetValidationCode( int iValidation )
{
    EnumValidationCode eValidation = enumUndefinedValidationCode;

    if ( iValidation >= enumUnvalidated && iValidation <= enumPostulated ) {
        eValidation = (EnumValidationCode) iValidation;
    }

    return eValidation;
}

/**
 * @brief CELSignalIdentifyAlg::UpdateRadarMode
 */
void CELSignalIdentifyAlg::UpdateRadarMode( SRxLOBData *pLOBData )
{
    char buffer[100];
    struct tm stTime;

    __time32_t nowTime=_time32(NULL);

    _localtime32_s( & stTime, & nowTime );
    strftime( buffer, 100, "%Y-%m-%d %H:%M:%S", & stTime);

    // RADARMODE 테이블에 DATE_LAST_SEEN에 현재 날짜 및 시간을 업데이트 함.
    sprintf_s( m_pszSQLString, "UPDATE RADAR_MODE SET DATE_LAST_SEEN='%s' where RADAR_MODE_INDEX=%d", buffer, pLOBData->iRadarModeIndex );
    exec( m_pszSQLString );

    // RADARMODE 테이블에 DATE_FIRST_SEEN에 현재 날짜 및 시간을 업데이트 함.
#ifdef _SQLITE_
    sprintf_s( m_pszSQLString, "UPDATE RADAR_MODE SET DATE_FIRST_SEEN='%s' where ( RADAR_MODE_INDEX=%d and DATE_FIRST_SEEN == '1970/01/01 0:00:00.000' )", buffer, pLOBData->iRadarModeIndex );
#else
    sprintf_s( m_pszSQLString, "UPDATE RADAR_MODE SET DATE_FIRST_SEEN='%s' where ( RADAR_MODE_INDEX=%d and ISNULL( DATE_FIRST_SEEN, '')='' )", buffer, pLOBData->iRadarModeIndex );
#endif
    exec( m_pszSQLString );

}
