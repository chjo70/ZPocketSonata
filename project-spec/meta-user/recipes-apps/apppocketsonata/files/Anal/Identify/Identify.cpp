/**

    @file      Identify.cpp
    @brief     CED/EOB 신호 식별하기 위한 클래스 입니다.
    @details   ~
    @author    Cool Guy
    @date      13.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "stdafx.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef __VXWORKS__
#include <memory.h>
#endif


#include "../SigAnal/_SigAnal.h"

#include "Identify.h"
#include "../EmitterMerge/InverseMethod/CInverseMethod.h"

#include "../../Utils/ccommonutils.h"

#include "../../Include/globals.h"

#define MAX_SIZE_OF_CONDITION					(300)


#define SWAP( A, B, C ) {   \
            A = B;          \
            B = C;          \
            C = A;          \
        }

static char _FunctionCodes[enumXP_Experimental_or_Trainer + 1][4] =
{
    "AA", "AB", "AI", "AL", "AM", "AT", "AV", \
    "BN", "BS", \
    "CA", "CI", "CS", \
    "DC", "DT", \
    "ES", "EW", \
    "FC", \
    "GB", "GM", "GT", \
    "HF", "HS", \
    "IF", "IL", "IS", "IT", \
    "JB", "JC", "JD", "JF", "JG", "JN", "JP", "JR", "JS", "JT", \
    "MA", "MC", "MD", "ME", "MF", "MG", "MH", "MT",
    "NA", "ND", "NT", "NW", \
    "PF", \
    "RI", "RO", "RS", \
    "SB", "SP", "SS", "ST", \
    "TA", "TI", "TT", "TV", \
    "UN", \
    "VR", \
    "XP"
};

// 정적 초기화
int  CELSignalIdentifyAlg::m_CoInstance = 0;

bool CELSignalIdentifyAlg::m_bInitTable = false;
STR_FLIB *CELSignalIdentifyAlg::m_pFLib = NULL;

unsigned int CELSignalIdentifyAlg::m_uiRadar = 0;
unsigned int CELSignalIdentifyAlg::m_uiRadarMode = 0;
unsigned int CELSignalIdentifyAlg::m_uiThreat = 0;

STR_HOWTO_IDENTIFY CELSignalIdentifyAlg::m_HowToId[(int)ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE][(int)ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE];

unsigned char CELSignalIdentifyAlg::m_FrqIdCallFunc[(int)ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE][(int)ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE];
unsigned char CELSignalIdentifyAlg::m_PriIdCallFunc[(int)ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE][(int)ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE];

bool CELSignalIdentifyAlg::m_bLoadedDB;

// 시스템 변수의 설정 값
//SOCSystemVariable CELSignalIdentifyAlg::m_stSystemVar[3];
//SELDBEnvVarIdnf *CELSignalIdentifyAlg::m_pSELDBEnvVarIdnf;
SEnvironVariable *CELSignalIdentifyAlg::m_pSEnvironVariable;			///< 시스템 설정값 환경 포인터

//vector<STR_H000> CELSignalIdentifyAlg::m_vecH000;

std::vector<SRadarMode> CELSignalIdentifyAlg::m_vecRadarMode;

//int CELSignalIdentifyAlg::m_iThreat;
std::vector<SThreat> CELSignalIdentifyAlg::m_vecThreat;

//STR_EOB_RESULT *CELSignalIdentifyAlg::m_pEOBResult;			///< EOB 식별 결과를 저장하기 위한 임시 저장소
//STR_LIB_IDRESULT *CELSignalIdentifyAlg::m_pIdResult;			///< CED 식별 결과를 저장하기 위한 임시 저장소
//STR_CEDEOB_RESULT *CELSignalIdentifyAlg::m_pCEDEOBResult;			///< CED/EOB 식별 결과


//vector<SDeviceData> CELSignalIdentifyAlg::m_vecDeviceData;

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

    p1 = ( const STR_LIB_IDRESULT * ) arg1;
    p2 = ( const STR_LIB_IDRESULT * ) arg2;

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

/**
 * @brief     incIndexCompare
 * @param     const void * arg1
 * @param     const void * arg2
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-26 14:12:19
 * @warning
 */
int incIndexCompare( const void *arg1, const void *arg2 )
{
    int iRet;
    const unsigned char *p1, *p2;

    p1 = ( const unsigned char * ) arg1;
    p2 = ( const unsigned char * ) arg2;

    if( *p1 > *p2 ) {
        iRet = 1;
    }
    else if( *p1 < *p2 ) {
        iRet = -1;
    }
    else {
        iRet = 0;
    }

    return iRet;
}


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
#ifdef _MSSQL_
CELSignalIdentifyAlg::CELSignalIdentifyAlg( CODBCDatabase *pMyODBC, const char *pThreadName ) : CMSSQL( pMyODBC )
#else
CELSignalIdentifyAlg::CELSignalIdentifyAlg( const char *pFileName, const char *pThreadName )
#endif
{

    SetThreadName( pThreadName );

    ++ m_CoInstance;

    //////////////////////////////////////////////////////////////////////////
    // 식별 콜함수 정의
    // 주파수 식별 매칭 정의
    IdentifyFrq[FFixedFixed] = & CELSignalIdentifyAlg::FIdentifyFixFix;
    IdentifyFrq[FFixedHopping] = & CELSignalIdentifyAlg::FIdentifyFixHop;
    //IdentifyFrq[FFixedPattern] = & CELSignalIdentifyAlg::FIdentifyFixPat;
    IdentifyFrq[FHoppingHopping] = & CELSignalIdentifyAlg::FIdentifyHopHop;
    IdentifyFrq[FPatternPattern] = & CELSignalIdentifyAlg::FIdentifyPatPat;
    IdentifyFrq[FAgileAgile] = & CELSignalIdentifyAlg::FIdentifyAgiAgi;
    IdentifyFrq[FAgilePattern] = &CELSignalIdentifyAlg::FIdentifyAgiPat;
    IdentifyFrq[FIgnoreFreqType] = & CELSignalIdentifyAlg::FIdentifyFreq;

    // PRI 식별 매칭 정의
    IdentifyPri[PStableStable] = & CELSignalIdentifyAlg::PIdentifyStbStb;
    IdentifyPri[PStableDwell] = & CELSignalIdentifyAlg::PIdentifyStbDwl;
    IdentifyPri[PStaggerStagger] = & CELSignalIdentifyAlg::PIdentifyStgStg;
    IdentifyPri[PStaggerJitter] = &CELSignalIdentifyAlg::PIdentifyStgJit;
    IdentifyPri[PDwellDwell] = & CELSignalIdentifyAlg::PIdentifyDwlDwl;
    IdentifyPri[PJitterStagger] = & CELSignalIdentifyAlg::PIdentifyJitStg;
    IdentifyPri[PJitterJitter] = & CELSignalIdentifyAlg::PIdentifyJitJit;
    IdentifyPri[PJitterPattern] = & CELSignalIdentifyAlg::PIdentifyJitPat;
    IdentifyPri[PPatternPattern] = & CELSignalIdentifyAlg::PIdentifyPatPat;
    IdentifyPri[FIgnorePRIType] = & CELSignalIdentifyAlg::PIdentifyPRI;

    InitVar();
    if( m_CoInstance == _spOne ) {
        InitIdentifyTable();

        MallocStaticBuffer();
        MallocBuffer();
        InitIdentifyTable();

        m_pSEnvironVariable = GlobalMemberFunction::GetEnvrionVariable();

#ifdef _SQLITE_
        // printf( "\n pFileName[%s]" , pFileName );

        try {
            m_pDatabase = new Kompex::CSQLiteDatabase( pFileName, SQLITE_OPEN_READWRITE, 0 );

        }
        catch( Kompex::SQLiteException &sException ) {
            m_pDatabase = NULL;
            //std::cerr << "\nException Occured" << std::endl;
            //sException.Show();
            //std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
            Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );
        }
#elif _MSSQL_
        // MSSQL 연결
        CMSSQL::Init();

#endif
    }
    else {
        MallocBuffer();


#ifdef _SQLITE_
        m_pDatabase = NULL;
#else
#endif
    }


#if 0
    SRxLOBData stLOBData;

    MakeHoppingLevelIndex2<SRxLOBData>( & stLOBData );

    float series[2] = { 400, 500 };

    SRadarMode_Sequence_Values stSRadarMode_Sequence_Values;

    stSRadarMode_Sequence_Values.f_Min = 500.;
    stSRadarMode_Sequence_Values.f_Max = 500.;

    TCompMarginDiff<float>( series[0], stSRadarMode_Sequence_Values.f_Min, stSRadarMode_Sequence_Values.f_Max, 400 );

#else

#endif

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

    Destory();

#ifdef _SQLITE_
    delete m_pDatabase;
#endif

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

    _SAFE_FREE( m_pEOBResult )

    _SAFE_FREE( m_pIdResult )

    _SAFE_FREE( m_pCEDEOBResult )

    if( m_CoInstance == 0 ) {
        _SAFE_FREE( m_pFLib )

    }

}

/**
 * @brief     객체에 사용할 변수를 초기화 를 수행한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-07-17 10:22:28
 * @warning
 */
void CELSignalIdentifyAlg::InitVar()
{

    m_total_ced = 0;
    m_total_eob = 0;

    if( m_CoInstance == 1 ) {
        //ClearH000();
        m_iH000 = 0;
    }

    //InitIdentifyTable();

    //m_pRadarMode = NULL;
    //m_pThreat = NULL;

    m_pEOBResult = NULL;
    m_pIdResult = NULL;
    m_pCEDEOBResult = NULL;

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
bool CELSignalIdentifyAlg::LoadCEDLibrary()
{
    bool bRet=true;

    vector<SRadarMode_Sequence_Values> vecRadarMode_Sequence_Values;
    vector<SRadarMode_Spot_Values> vecRadarMode_Spot_Values;

    Log( enDebug, "CED 라이브러리를 로딩합니다." );

    //Lock();

    InitRadarModeData();

#ifdef _SQLITE_
    try {
#endif
        // 레이더모드 및 PRI 시퀀스 테이블 로딩
        LoadRadarModeData( & m_uiRadarMode );

        //
        vecRadarMode_Spot_Values.reserve( ( size_t ) m_uiRadarMode * (size_t) MAX_FREQ_PRI_STEP );
        vecRadarMode_Sequence_Values.reserve( ( size_t ) m_uiRadarMode * ( size_t ) MAX_FREQ_PRI_SPOT );

        // 시퀀스(포지션 값만) 로딩
        LoadRadarMode_RFSequence( & vecRadarMode_Sequence_Values );
        MakeRadarMode( & vecRadarMode_Sequence_Values, enRFSequenceValue );

        LoadRadarMode_PRISequence( & vecRadarMode_Sequence_Values );
        MakeRadarMode( & vecRadarMode_Sequence_Values, enPRISequenceValue );

        // SPOT 값 로딩
        LoadRadarMode_RFSpot( &vecRadarMode_Spot_Values, m_uiRadarMode );
        MakeRadarMode( &vecRadarMode_Spot_Values, enRFSpotValue );

        LoadRadarMode_PRISpot( &vecRadarMode_Spot_Values, m_uiRadarMode );
        MakeRadarMode( &vecRadarMode_Spot_Values, enPRISpotValue );

        ///////////////////////////////////////////////////////////////////////////////////
        // 주파수 식별 테이블화를 구성한다.
        MakeFreqBand();

        // 식별 테이블화에 해당 빔 번호를 저장하게 한다.
        //dwTime2=GetTickCount();
        MakeFreqLibTable();
        //LogPrint("========================================== MakeFreqLibTable 시간 : %d ms\n", (int)((GetTickCount() - dwTime2) / 1));

        //LogPrint("\n===================== 식별 데이터를 로딩했습니다. !! 시간 : %d ms\n", (int)((GetTickCount() - dwTime) / 1));

        Log( enNormal, "레이더 모드[%d]를 로딩했습니다...", m_uiRadarMode );

#ifdef _SQLITE_

    }

    catch( Kompex::SQLiteException &sException ) {
        m_uiRadarMode = 0;

        bRet = false;

        Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );

        //Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );
        KOMPEX_O_EXCEPT( "레이더 모드가 잘못 됐거나 쿼리문이 잘못 됐습니다 !", -1 );
    }
#endif

    //vecRadarMode_Sequence_Values.clear();
    //vecRadarMode_Spot_Values.clear();

    //UnLock();

    return bRet;
}

/**
 * @brief     레이더모드 데이터를 초기화한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-06-22 16:25:29
 * @warning
 */
void CELSignalIdentifyAlg::InitRadarModeData()
{

    m_vecRadarMode.clear();
    m_vecRadarMode.reserve( MAX_RADARMODE );

    //    int i;
    //    SRadarMode *pRadarMode;
    //     pRadarMode = m_pRadarMode;
    //     for( i=0 ; i < MAX_RADARMODE ; ++i ) {
    // 		pRadarMode->vecRadarMode_RFSequenceValues.clear();
    // 		pRadarMode->vecRadarRF_SpotValues.clear();
    //
    //         pRadarMode->vecRadarMode_PRISequenceValues.clear();
    //         pRadarMode->vecRadarPRI_SpotValues.clear();
    //
    //         ++ pRadarMode;
    //     }

}

/**
 * @brief     SPOT 값을 레이더모드에 결합한다.
 * @param     vector<SRadarMode_Spot_Values> * pVecRadarMode_Spot_Values
 * @param     ENUM_Sequence enSeq
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-10 11:39:05
 * @warning
 */
void CELSignalIdentifyAlg::MakeRadarMode( vector<SRadarMode_Spot_Values> *pVecRadarMode_Spot_Values, ENUM_SequenceSpot enSeqSpot )
{
    unsigned int j;
    SRadarMode_Spot_Values *pstSRadarMode_Spot_Values;

    //SRadarMode *pRadarMode;
    SRadarMode_Spot_Values stRadarMode_SpotValues;

    UINT uiRadarMode_Spot = 0;
    size_t uiSizeOfRadarMode_Spot;

    char szTarget[2][20] = { "PRI", "주파수" };

    uiSizeOfRadarMode_Spot = pVecRadarMode_Spot_Values->size();

    if( uiSizeOfRadarMode_Spot > 0 ) {
        j = 0;
        pstSRadarMode_Spot_Values = &pVecRadarMode_Spot_Values->at( j++ );

        for( auto &stRadarMode : m_vecRadarMode ) {
            //pRadarMode = &m_vecRadarMode.at(i);

            while( j < uiSizeOfRadarMode_Spot && ( unsigned int ) pstSRadarMode_Spot_Values->iRadarModeIndex < stRadarMode.uiRadarModeIndex ) {
                pstSRadarMode_Spot_Values = &pVecRadarMode_Spot_Values->at( j++ );
            }

            while( j <= uiSizeOfRadarMode_Spot && ( unsigned int ) pstSRadarMode_Spot_Values->iRadarModeIndex == stRadarMode.uiRadarModeIndex ) {
                stRadarMode_SpotValues.iRadarModeIndex = pstSRadarMode_Spot_Values->iRadarModeIndex;
                stRadarMode_SpotValues.f_Min = pstSRadarMode_Spot_Values->f_Min;
                stRadarMode_SpotValues.f_Max = pstSRadarMode_Spot_Values->f_Max;

                if( enSeqSpot == enRFSpotValue ) {
#ifdef __VXWORKS__
                    stRadarMode.vecRadarRF_SpotValues.push_back( stRadarMode_SpotValues );
#else
                    stRadarMode.vecRadarRF_SpotValues.emplace_back( stRadarMode_SpotValues );
#endif
                }
                else {
#ifdef __VXWORKS__
                    stRadarMode.vecRadarPRI_SpotValues.push_back( stRadarMode_SpotValues );
#else
                    stRadarMode.vecRadarPRI_SpotValues.emplace_back( stRadarMode_SpotValues );
#endif

                }

                if( j == uiSizeOfRadarMode_Spot ) {
                    break;
                }
                else {
                    pstSRadarMode_Spot_Values = &pVecRadarMode_Spot_Values->at( j++ );
                    ++uiRadarMode_Spot;
                }
            }

            //++i;
            // ++pRadarMode;

        }
    }

    Log( enNormal, "레이더 모드의 %s SPOT 값을 [%d]개 로딩했습니다...", szTarget[( int ) ( enSeqSpot == enRFSpotValue )], uiRadarMode_Spot );


}

/**
 * @brief     시퀀스 값을 레이더모드에 결합한다.
 * @param     vector<SRadarMode_Sequence_Values> * pVecRadarMode_Sequence_Values
 * @param     ENUM_SequenceSpot enSeqSpot
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2019/04/24 16:21
 * @warning
 */
void CELSignalIdentifyAlg::MakeRadarMode( vector<SRadarMode_Sequence_Values> *pVecRadarMode_Sequence_Values, ENUM_SequenceSpot enSeqSpot )
{
    unsigned int j;
    SRadarMode_Sequence_Values *pstSRadarMode_Sequence_Values;

    SRadarMode_Sequence_Values stRadarMode_SequenceValues;

    UINT uiRadarMode_Sequence = 0;
    size_t uiSizeOfRadarMode_Sequence;

    uiSizeOfRadarMode_Sequence = pVecRadarMode_Sequence_Values->size();

    char szTarget[2][20] = { "PRI", "주파수" };

    uiSizeOfRadarMode_Sequence = pVecRadarMode_Sequence_Values->size();

    if( uiSizeOfRadarMode_Sequence > _spZero ) {
        j = 0;
        pstSRadarMode_Sequence_Values = & pVecRadarMode_Sequence_Values->at( j++ );

        for( auto &stRadarMode : m_vecRadarMode ) {
            while( j < uiSizeOfRadarMode_Sequence && ( unsigned int ) pstSRadarMode_Sequence_Values->iRadarModeIndex < stRadarMode.uiRadarModeIndex ) {
                pstSRadarMode_Sequence_Values = & pVecRadarMode_Sequence_Values->at( j++ );
            }

            while( j <= uiSizeOfRadarMode_Sequence && ( unsigned int ) pstSRadarMode_Sequence_Values->iRadarModeIndex == stRadarMode.uiRadarModeIndex ) {
                stRadarMode_SequenceValues.iRadarModeIndex = pstSRadarMode_Sequence_Values->iRadarModeIndex;
                stRadarMode_SequenceValues.i_Index = pstSRadarMode_Sequence_Values->i_Index;
                stRadarMode_SequenceValues.f_Min = pstSRadarMode_Sequence_Values->f_Min;
                stRadarMode_SequenceValues.f_Max = pstSRadarMode_Sequence_Values->f_Max;

                if( enSeqSpot == enRFSequenceValue ) {
                    stRadarMode.vecRadarMode_RFSequenceValues.push_back( stRadarMode_SequenceValues );
                }
                else {
                    stRadarMode.vecRadarMode_PRISequenceValues.push_back( stRadarMode_SequenceValues );
                }

                if( j == uiSizeOfRadarMode_Sequence ) {
                    break;
                }
                else {
                    pstSRadarMode_Sequence_Values = & pVecRadarMode_Sequence_Values->at( j++ );
                    ++ uiRadarMode_Sequence;
                }
            }

            if( stRadarMode.vecRadarMode_RFSequenceValues.size() > MAX_FREQ_PRI_STEP ) {
                Log( enError, "이 레이더 모드[%d]에서, %s 호핑 레벨이 [%Iu]단 이상 입니다 ! 관리자에게 문의하세요 !!", stRadarMode.uiRadarModeIndex, szTarget[( int ) ( enSeqSpot == enRFSequenceValue )], stRadarMode.vecRadarMode_RFSequenceValues.size() );
            }
        }
    }

    Log( enDebug, "레이더 모드의 %s 시퀀스 값을 [%d]개 로딩했습니다...", szTarget[( int ) ( enSeqSpot == enRFSequenceValue )], uiRadarMode_Sequence );

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
bool CELSignalIdentifyAlg::LoadEOBLibrary()
{
    Log( enDebug, "EOB 라이브러리를 로딩합니다." );

    InitDeviceData();

    // 위협+장비 테이블 로딩
    LoadDeviceData( & m_uiThreat );

    //MakeDevice();
    Log( enDebug, "위협/장비를 [%d]개 로딩했습니다...", m_uiThreat );

    return true;

}

/**
 * @brief     InitDeviceData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-24 11:17:35
 * @warning
 */
void CELSignalIdentifyAlg::InitDeviceData()
{
    m_vecThreat.clear();
    m_vecThreat.reserve( MAX_THREAT );

}

/**
 * @brief     LoadDeviceData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-24 11:28:32
 * @warning
 */
bool CELSignalIdentifyAlg::LoadDeviceData( unsigned int *pnThreat )
{

    *pnThreat = 0;

    m_vecThreat.clear();

#ifdef _SQLITE_
    bool bRet = true;

#ifdef _XBAND_
    sprintf( m_szSQLString, "SELECT RM_RADAR_MODE_INDEX, RM_FUNCTION_CODE, RM_SIGNAL_TYPE, RM_POLARIZATION, RM_PLATFORM, RM_VALIDATION, \
                             RM_RF_TYPE, RM_RF_TYPICAL_MIN, RM_RF_TYPICAL_MAX, RM_RF_PATTERN, RM_RF_NUM_ELEMENTS, RM_RF_NUM_POSITIONS, RM_RF_PATTERN_PERIOD_MIN, RM_RF_PATTERN_PERIOD_MAX, RM_RF_MEAN_MIN, RM_RF_MEAN_MAX, \
                             RM_PRI_TYPE, RM_PRI_TYPICAL_MIN, RM_PRI_TYPICAL_MAX, RM_PRI_PATTERN, RM_PRI_NUM_ELEMENTS, RM_PRI_NUM_POSITIONS, RM_PRI_PATTERN_PERIOD_MIN, RM_PRI_PATTERN_PERIOD_MAX, RM_PRI_MEAN_MIN, RM_PRI_MEAN_MAX, \
                             RM_PD_TYPICAL_MIN, RM_PD_TYPICAL_MAX, \
                             RM_SCAN_PRIMARY_TYPE, RM_SCAN_PRIMARY_TYPICAL_MIN, RM_SCAN_PRIMARY_TYPICAL_MAX, RM_SCAN_SECONDARY_TYPE, RM_SCAN_SECONDARY_TYPICAL_MIN, RM_SCAN_SECONDARY_TYPICAL_MAX, RM_MODULATION_CODE, RM_PRIORITY, \
                             RML_RADAR_INDEX, RML_RADAR_MODE_NAME, RML_MODE_CODE, \
                             R_PRIORITY, R_ELNOT, R_NICKNAME, R_TIME_INACTIVATED, \
                             D_THREAT_INDEX, D_DEVICE_INDEX, D_ELNOT \
                             FROM VEL_RADARMODE_LIST ORDER BY RM_RADAR_MODE_INDEX" );

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.Sql( m_szSQLString );

        while( stmt.FetchRow() ) {
            int iValue;
            //char buffer[100];
            const char *p;

            i = 0;

            pRadarMode->uiRadarModeIndex = stmt.GetColumnInt( i++ );

            p = stmt.GetColumnName( i++ );
            pRadarMode->eFunctionCode = GetFunctionCodes( p );

            p = ( char * ) stmt.GetColumnName( i++ );
            pRadarMode->eSignalType = GetSignalType( p );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->ePolarization = GetPolarizationCodes( iValue );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->ePlatform = GetPlatformCode( iValue );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->eValidation = GetValidationCode( iValue );

            // 주파수 정보
            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->eRF_Type = GetFreqType( iValue );

            pRadarMode->fRF_TypicalMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fRF_TypicalMax = ( float ) stmt.GetColumnDouble( i++ );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->eRF_Pattern = GetPatternCode( iValue );

            pRadarMode->nRF_NumElements = stmt.GetColumnInt( i++ );
            pRadarMode->nRF_NumPositions = stmt.GetColumnInt( i++ );

            pRadarMode->fRF_PatternPeriodMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fRF_PatternPeriodMax = ( float ) stmt.GetColumnDouble( i++ );

            pRadarMode->fRF_MeanMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fRF_MeanMax = ( float ) stmt.GetColumnDouble( i++ );

            // PRI 정보
            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->ePRI_Type = GetPRIType( iValue );

            pRadarMode->fPRI_TypicalMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fPRI_TypicalMax = ( float ) stmt.GetColumnDouble( i++ );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->ePRI_Pattern = GetPatternCode( iValue );

            pRadarMode->nPRI_NumElements = stmt.GetColumnInt( i++ );
            pRadarMode->nPRI_NumPositions = stmt.GetColumnInt( i++ );

            pRadarMode->fPRI_PatternPeriodMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fPRI_PatternPeriodMax = ( float ) stmt.GetColumnDouble( i++ );

            pRadarMode->fPRI_MeanMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fPRI_MeanMax = ( float ) stmt.GetColumnDouble( i++ );

            // 펄스폭 정보
            pRadarMode->fPD_TypicalMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fPD_TypicalMax = ( float ) stmt.GetColumnDouble( i++ );

            // 스캔 정보
            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->eScanPrimaryType = GetScanType( iValue );
            pRadarMode->fScanPrimaryTypicalMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fScanPrimaryTypicalMax = ( float ) stmt.GetColumnDouble( i++ );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->eScanSecondaryType = GetScanType( iValue );
            pRadarMode->fScanSecondaryTypicalMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fScanSecondaryTypicalMax = ( float ) stmt.GetColumnDouble( i++ );

            // 기타 정보
            //pRadarMode->nAssocIndex	= query.getColumn(i++).getInt();													//모드 간 연관관계에 대한 링크

            p = ( char * ) stmt.GetColumnCString( i++ );
            if( p != NULL ) {
                strcpy( pRadarMode->szModulationCode, p );
            }
            else {
                pRadarMode->szModulationCode[0] = 0;
            }

            pRadarMode->uiRadarModePriority = stmt.GetColumnInt( i++ );

            // 레이더 정보
            pRadarMode->uiRadarIndex = stmt.GetColumnInt( i++ );
            //strcpy( pRadarMode->szRadarModeName, stmt.GetColumnName(i++) );
            p = ( char * ) stmt.GetColumnCString( i++ );
            if( p != NULL ) {
                strcpy( pRadarMode->szRadarModeName, p );
            }
            else {
                pRadarMode->szRadarModeName[0] = 0;
            }

            //strcpy( pRadarMode->szModeCode, stmt.GetColumnName(i++) );
            p = ( char * ) stmt.GetColumnCString( i++ );
            if( p != NULL ) {
                strcpy( pRadarMode->szModeCode, p );
            }
            else {
                pRadarMode->szModeCode[0] = 0;
            }

            pRadarMode->iRadarPriority = stmt.GetColumnInt( i++ );
            //strcpy( pRadarMode->szELNOT, stmt.GetColumnName(i++) );
            p = ( char * ) stmt.GetColumnCString( i++ );
            if( p != NULL ) {
                strcpy( pRadarMode->szELNOT, p );
            }
            else {
                pRadarMode->szELNOT[0] = 0;
            }

            //strcpy( pRadarMode->szNickName, stmt.GetColumnName(i++) );
            p = ( char * ) stmt.GetColumnCString( i++ );
            if( p != NULL ) {
                strcpy( pRadarMode->szNickName, p );
            }
            else {
                pRadarMode->szNickName[0] = 0;
            }

            pRadarMode->iTimeInactivated = stmt.GetColumnInt( i++ );

            pRadarMode->iThreatIndex = stmt.GetColumnInt( i++ );
            pRadarMode->iDeviceIndex = stmt.GetColumnInt( i++ );

            if( pRadarMode->eValidation == enumValidated ) {
                ++ *pnRadarMode;
                ++pRadarMode;
            }

            if( iMaxItems != 0 && *pnRadarMode >= iMaxItems ) {
                break;
            }

        }

        // do not forget to clean-up
        stmt.FreeQuery();

    }

#elif defined(_POCKETSONATA_) || defined(_712_)
    // 뷰 테이블에서 정렬 적용함.
    sprintf( m_szSQLString, "SELECT THREAT_INDEX, DEVICE_INDEX, THREAT_NAME, DEVICE_NAME, ELNOT, \
            SITE_NAME, PIN, PLACE_NAME_KOR, FRIEND_OR_FOE, PRIORITY, CATEGORY, PLATFORM_TYPE, \
            SYMBOL_CODE, IDENTIFICATION_RANGE, LATITUDE, LONGITUDE, ELEVATION \
            FROM VEL_DEVICE_LIST;" );

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.Sql( m_szSQLString );

        while( stmt.FetchRow() ) {
            SThreat stThreat;

            GetThreatFromStatement( &stThreat, &stmt );

            ++ *pnThreat;

#ifdef __VXWORKS__
            m_vecThreat.push_back( stThreat );
#else
            m_vecThreat.emplace_back( stThreat );
#endif


        }

        // do not forget to clean-up
        stmt.FreeQuery();
    }


#endif

    catch( Kompex::SQLiteException &sException ) {
        bRet = false;

        Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );

        KOMPEX_O_EXCEPT( "레이더 모드가 잘못 됐거나 쿼리문이 잘못 됐습니다 !", -1 );
    }

    return bRet;

#elif defined(_MSSQL_)
    DECLARE_BEGIN_CHECKODBC
    //int i;

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    //sprintf_s( m_szSQLString, MAX_SQL_SIZE,  "SELECT * FROM RADARMODE WHERE VALIDATION = '1' ORDER BY RADARMODE_INDEX" );
    sprintf_s( m_szSQLString, MAX_SQL_SIZE, "SELECT THREAT_INDEX, DEVICE_INDEX, THREAT_NAME, DEVICE_NAME, ELNOT, \
            SITE_NAME, PIN, PLACE_NAME_KOR, FRIEND_OR_FOE, PRIORITY, CATEGORY, PLATFORM_TYPE, \
            SYMBOL_CODE, IDENTIFICATION_RANGE, LATITUDE, LONGITUDE, ELEVATION \
            FROM VEL_DEVICE_LIST;" );

    theRS.Open( m_szSQLString );

    while( !theRS.IsEof() ) {
        SThreat stThreat;

        theRS.MoveNext();
    }

    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN

#else

    return true;

#endif

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
    size_t szSize;

    szSize = CCommonUtils::CheckMultiplyOverflow( ( int ) sizeof( struct STR_EOB_RESULT ), MAX_THREAT );
    _SAFE_MALLOC( m_pEOBResult, STR_EOB_RESULT, szSize )

        szSize = CCommonUtils::CheckMultiplyOverflow( ( int ) sizeof( struct STR_LIB_IDRESULT ), MAX_RADARMODE );
    _SAFE_MALLOC( m_pIdResult, STR_LIB_IDRESULT, szSize )

        szSize = CCommonUtils::CheckMultiplyOverflow( ( int ) sizeof( struct STR_CEDEOB_RESULT ), MAX_IDCANDIDATE );
    _SAFE_MALLOC( m_pCEDEOBResult, STR_CEDEOB_RESULT, szSize )

}

/**
 * @brief     MallocStaticBuffer
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-31 17:17:39
 * @warning
 */
void CELSignalIdentifyAlg::MallocStaticBuffer()
{
    size_t szSize;

    szSize = CCommonUtils::CheckMultiplyOverflow( ( int ) sizeof( struct STR_FLIB ), NO_FLIB_BAND + 1 );
    _SAFE_MALLOC( m_pFLib, STR_FLIB, szSize )
        if( m_pFLib != NULL ) {
            memset( m_pFLib, 0, sizeof( struct STR_FLIB ) * ( NO_FLIB_BAND + 1 ) );
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
    memset( m_pIdResult, 0, sizeof( LIBINDEX ) * MAX_RADARMODE );

    // EOB 기반 초기화
    m_pEOBResult->nThreatIndex = 0;
    m_pEOBResult->nDeviceIndex = 0;
    m_pEOBResult->nRadarIndex = 0;

    m_pEOBResult->dDistance = -1.0;

    m_CEDEOBResult.chELNOT[0] = 0;

    m_CEDEOBResult.nThreatIndex = 0;
    m_CEDEOBResult.nDeviceIndex = 0;

    memset( m_pstIdentify->idxHopping, UINT8_MAX, sizeof( m_pstIdentify->idxHopping ) );
    memset( m_pstIdentify->idxDwell, UINT8_MAX, sizeof( m_pstIdentify->idxDwell ) );

}

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
    if( m_bInitTable != true ) {
        m_bInitTable = true;

        memset( & m_HowToId, 0xFF, sizeof( m_HowToId ) );

        ////////////////////////////////////////////////////////////////////////////
        // 1. 주파수 Fixed 에 대한 식별 테이블 정의
        InitFixedFreqIdentifyTable();

        ////////////////////////////////////////////////////////////////////////////
        // 2. 주파수 Random Agile 에 대한 식별 테이블 정의
        InitRandomAgileFreqIdentifyTable();

        ////////////////////////////////////////////////////////////////////////////
        // 3. 주파수 Hopping 에 대한 식별 테이블 정의
        InitHopingFreqIdentifyTable();

        ////////////////////////////////////////////////////////////////////////////
        // 4. 주파수 Pattern Agile 에 대한 식별 테이블 정의
        InitPatternAgileFreqIdentifyTable();

        ////////////////////////////////////////////////////////////////////////////
        // 5. 주파수 무시 에 대한 식별 테이블 정의

        //////////////////////////////////////////////////////////////////////////
        //
        memset( m_FrqIdCallFunc, FIgnoreFreqType, sizeof( m_FrqIdCallFunc ) );
        memset( m_PriIdCallFunc, FIgnorePRIType, sizeof( m_PriIdCallFunc ) );

        // 2차원 배열로 1차 값은 위협 관련 주파수/PRI 형태, 2차 값은 CED(IPL) 관련 주파수/PRI 형태 값 입니다.
        // 주파수 식별에 대한 함수 콜 넘버 정의
        m_FrqIdCallFunc[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED] = FFixedFixed;
        m_FrqIdCallFunc[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING] = FFixedHopping;
        m_FrqIdCallFunc[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING] = FHoppingHopping;
        m_FrqIdCallFunc[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN] = FPatternPattern;
        m_FrqIdCallFunc[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN] = FAgilePattern;
        m_FrqIdCallFunc[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE] = FAgileAgile;

        // PRI 식별에 대한 함수 콜 넘버 정의
        m_PriIdCallFunc[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED] = PStableStable;
        m_PriIdCallFunc[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH] = PStableDwell;
        m_PriIdCallFunc[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER] = PStaggerStagger;
        m_PriIdCallFunc[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER] = PStaggerJitter;
        m_PriIdCallFunc[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH] = PDwellDwell;
        m_PriIdCallFunc[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER] = PJitterStagger;
        m_PriIdCallFunc[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER] = PJitterJitter;
        m_PriIdCallFunc[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN] = PJitterPattern;
        m_PriIdCallFunc[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN] = PPatternPattern;
    }

}


/**
 * @brief     InitFixedFreqIdentifyTable
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-02 15:27:24
 * @warning
 */
void CELSignalIdentifyAlg::InitFixedFreqIdentifyTable()
{
    UINT *pFrqType, *pPriType;

    // Fixed, Stable
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].pri[0];

    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;

    // Fixed, Stagger
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;

    // Fixed, Jitter
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;

    // Fixed, Pattern
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;

    // Fixed, Dwell
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;

    // Fixed, PRI 무시
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_UNKNOWN].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_UNKNOWN].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;


}


/**
 * @brief     InitRandomAgileFreqIdentifyTable
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-02 15:29:03
 * @warning
 */
void CELSignalIdentifyAlg::InitRandomAgileFreqIdentifyTable()
{
    UINT *pFrqType, *pPriType;

    // Random Agile, Stable
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;

    // Random Agile, Stagger
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;

    // Random Agile, Jitter
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;

    // Random Agile, Pattern
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;

    // Random Agile, Dwell
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;

    // Random Agile, PRI 무시
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_UNKNOWN].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_UNKNOWN].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;

}

/**
 * @brief     InitHopingFreqIdentifyTable
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-02 15:33:25
 * @warning
 */
void CELSignalIdentifyAlg::InitHopingFreqIdentifyTable()
{
    UINT *pFrqType, *pPriType;

    // Hopping, Stable
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].pri[0];

    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;

    // Hopping, Stagger
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].pri[0];
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;

    // Hopping, Jitter
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;

    // Hopping, Pattern
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].pri[0];
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;

    // Hopping, Dwell
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].pri[0];
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;

    // Hopping, PRI 무시
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_UNKNOWN].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_UNKNOWN].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
}

/**
 * @brief     InitPatternAgileFreqIdentifyTable
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-21 19:42:06
 * @warning
 */
void CELSignalIdentifyAlg::InitPatternAgileFreqIdentifyTable()
{
    UINT *pFrqType, *pPriType;

    // Pattern Agile, Stable
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;

    // Pattern Agile, Stagger
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;

    // Pattern Agile, Jitter
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;

    // Pattern Agile, Pattern
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].pri[0];
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;

    // Pattern Agile, Dwell
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].pri[0];
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;

    // Pattern Agile, PRI 무시
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_UNKNOWN].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_UNKNOWN].pri[0];
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;

}

/**
 * @brief     InitIgnoreFreqIdentifyTable
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-21 19:42:11
 * @warning
 */
void CELSignalIdentifyAlg::InitIgnoreFreqIdentifyTable()
{
    UINT *pFrqType, *pPriType;

    // 주파수 무시, Stable
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;

    // 주파수 무시, Stagger
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;

    // 주파수 무시, Jitter
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;

    // 주파수 무시, Pattern
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;

    // 주파수 무시, Dwell
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;

    // 주파수 무시, PRI 무시
    pFrqType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_UNKNOWN].frq[0];
    pPriType = &m_HowToId[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE][( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_UNKNOWN].pri[0];
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    *pFrqType++ = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType++ = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    *pFrqType = ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    *pPriType = ( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;

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
// void CELSignalIdentifyAlg::Identify( SELABTDATA *pABTData, SELABTDATA_EXT *pABTExtData, SELLOBDATA_EXT *pLOBDataExt, int nLinkNum, bool bMakeH0000, EnumLibType eCEDLibType, EnumLibType eEOBLibType, bool bIDExecute )
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
// 		memcpy( & pABTExtData->stEOBResult[0], m_pEOBResult, sizeof(struct STR_EOB_RESULT)*pABTExtData->nCoIdEOB );
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
// 	memcpy( & idTemp, pIDInfo, sizeof(struct STR_CEDEOBID_INFO) );
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

/**
 * @brief     LOB 정보에 대해서 기반으로 CED/EOB 신호 식별을 수행한다.
 * @param     *pLOBDataGrp 식별할 LOB 데이터
 * @param     *pLOBDataExt 식별할 LOB 추가 정보 데이터
 * @param     *pstPosData 식별할 위치 산출 데이터
 * @param     nLinkNum 링크 번호
 * @param     bMakeH0000 미식별 인덱스 증가여부를 결정
 * @param     eCEDLibType 기본형 또는 실무형 라이브러리를 선택
 * @param     eEOBLibType 기본형 또는 실무형 라이브러리를 선택
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-02-16, 오후 1:26
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyLOB( STR_IDENTIFY *pstIdentify, SRxLOBData *pLOBData )
{

    // 1. 식별 관련 변수 초기화
    m_pLOBData = pLOBData;

    m_pstIdentify = pstIdentify;

    // 2. 식별 관련 변수 초기화
    Init();

    Identify<SRxLOBData>( pLOBData );

#ifdef MSC_VER


#endif

    // 10. 위치 산출의 신호 식별
    // EOB 전체 대해서 위치 산출한 정보를 이용하여 신호 식별한다.
    //IdentifyPosition( NULL, & m_IdAet.ext.posEst, pstPosData );

    // 11. CED 식별한 정보와 비교하여 위치 산출한다.
    //IdentifyCEDEOB( m_eCEDLibType, m_eEOBLibType );

    // 12. 신호 정보 저장
    CopyAmbiguity<SRxLOBData>( pLOBData );

}

/**
 * @brief     빔 정보로 식별을 수행한다.
 * @param     SRxABTData * pABTData
 * @param     SELABTDATA_EXT * pABTExtData
 * @param     SELLOBDATA_EXT * pLOBDataExt
 * @param     bool bIDExecute
 * @param     bool bMakeH0000
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-24 11:14:49
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyABT( STR_IDENTIFY *pstABTIdentify, SRxABTData *pABTData, STR_IDENTIFY *pstLOBIdentify )
{
    // unsigned int uiThreatIndex = 0;

    // 1. 입력 데이터 초기화
    m_pABTData = pABTData;
    m_pstIdentify = pstABTIdentify;

    // 2. 식별 관련 변수 초기화
    Init();

    if( pABTData != NULL ) {

        if( pstLOBIdentify == NULL ) {
            bool bIdentigyScan = ( pABTData->vScanStat == ENUM_AET_SCAN_STAT::E_AET_SELF_SCAN_SUCCESS ) || ( pABTData->vScanStat == ENUM_AET_SCAN_STAT::E_AET_USER_SCAN_SUCCESS );
            Identify<SRxABTData>( pABTData, bIdentigyScan );

        }
        else {
            //MakeIdetifyForReferToLOBIdentify();
            m_toLib = 0;
        }

        // 10. 위치 산출의 신호 식별
        if( m_pABTData->ucPEValid == _spOne ) {
            // EOB 전체 대해서 위치 산출한 정보를 이용하여 신호 식별한다.
            // tempPosEst.dCEP = (double) pABTData->fCEP;
            // uiThreatIndex = IdentifyPosition( m_pABTData );
			IdentifyPosition( m_pABTData );
        }
        else {
#if defined(_POCKETSONATA_) || defined(_712_)
            // 식별 결과가 지상용 플레폼인 경우, Line Of Bearing 값으로 위치를 추정하여 위협을 식별함.

#endif
            pABTData->fDistanceErrorOfThreat = -1.0;

        }

        CopyAmbiguity<SRxABTData>( pABTData );
    }

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
//  * @return    bool
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-06-07, 오후 5:07
//  * @warning
//  */
// bool CELSignalIdentifyAlg::FindEOB( int nThreatIndex, int nDeviceIndex )
// {
// 	int i;
// 	bool bRet=false;
//
// 	STR_EOB_RESULT *pEOBResult;
//
// 	pEOBResult = m_pEOBResult;
// 	for( i=0 ; i < m_nCoIdEOB ; ++i ) {
// 		if( pEOBResult->nThreatIndex == nThreatIndex && pEOBResult->nDeviceIndex == nDeviceIndex ) {
// 			bRet = true;
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
unsigned int CELSignalIdentifyAlg::IdentifyPosition( SRxABTData *pABTData )
{
    //int i;

    double dDistance, dMixDistance;

    // 1. 거리별로 모든 EOB를 계산한다.

    double dEobIndfRangeKM = m_pSEnvironVariable->fEobIndfRangeMeters;
    dMixDistance = dEobIndfRangeKM;

    for( const auto &stThreat : m_vecThreat ) {
        // 				eob_latitude = pDeviceData->eob_latitude / 10000.;
        // 				eob_longitude = pDeviceData->eob_longitude / 10000.;
        //
                    //ST_IMA->VincentyInverse( & distlob, eob_latitude, eob_longitude, res_latitude, res_longitude );
        dDistance = m_theInverseMethod.GCDistance( ( double ) stThreat.fLatitude, ( double ) stThreat.fLongitude, ( double ) pABTData->fLatitude, ( double ) pABTData->fLongitude );

        //printf( "\nDist from Th[%d] : %f [m]", pThreat->iThreatIndex, dDistance );
        //Log( enNormal, "Dist from Th[%d] : %f [m]", pThreat->iThreatIndex, dDistance );

        if( /*i == 0 || */ ( dMixDistance > dDistance && dDistance <= stThreat.fIdentificationRange ) ) {
            pABTData->uiThreatIndex = stThreat.uiThreatIndex;
            pABTData->fDistanceErrorOfThreat = ( float ) dDistance;

            dMixDistance = dDistance;
        }

    }

    if( dEobIndfRangeKM < pABTData->fDistanceErrorOfThreat ) {
        pABTData->uiThreatIndex = 0;
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

    return pABTData->uiThreatIndex;

}

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

/**
 * @brief     CED 레이더모드 주파수 범위별로 레이더 모드를 테이블화한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-07-22 12:51:07
 * @warning
 */
void CELSignalIdentifyAlg::MakeFreqBand()
{
    UINT i, j, l;
    UINT istart, iend, uiHistSize;

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

    // int preRadarModeIndex;

    memset( theFLib, _spZero, sizeof( struct STR_FLIB ) * ( NO_FLIB_BAND + 1 ) );

    uiHistSize = ( int ) ( MAX_FREQ_MHZ / FLIB_FREQ_RES_MHZ ) + 1;
    pHist = ( UINT * ) malloc( ( UINT ) ( uiHistSize * sizeof( int ) ) );
    if( pHist == NULL ) { //DTEC_NullPointCheck
        printf( "\n 메모리가 부족해서 히스토그램을 위한 메모리를 할당하지 못했습니다 !" );
    }
    else {
        memset( pHist, _spZero, uiHistSize * sizeof( int ) );

        /*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2014-01-24 17:11:34
        */
        m_total_ced = 0;
        total_bin_count = 0;

        // DB로부터 CED 라이브러리 테이블화 작업
        //SRadarMode *pRadarMode;

        //pRadarMode = m_pRadarMode;
        //UINT uiSize = (UINT) m_iRadarMode;

        // if( uiSize != 0 )
        {
            //preRadarModeIndex = -1;

            //  for( i=0 ; i < uiSize ; ++i ) {
            for( auto &stRadarMode : m_vecRadarMode ) {
                // 이전 레이더 모드 인덱스 값과 다른지를 검사
                //if( pRadarMode->uiRadarModeIndex != preRadarModeIndex ) {
                if( stRadarMode.fRF_TypicalMin > 0 && stRadarMode.fRF_TypicalMax > 0 ) {
                    istart = F_NDIV( stRadarMode.fRF_TypicalMin, FLIB_FREQ_RES_MHZ );
                    iend = C_NDIV( stRadarMode.fRF_TypicalMax, FLIB_FREQ_RES_MHZ );

                    for( l = istart; l <= iend; ++l ) {
                        if( l >= uiHistSize ) {
                            ++ pHist[uiHistSize - 1];
                        }
                        else {
                            ++ pHist[l];
                        }

                        ++ total_bin_count;
                    }

                    ++ m_total_ced;

                }
                else {
                    TRACE( "\n [W] 잘못된 레이더 모드[%d]", stRadarMode.uiRadarModeIndex );
                }

                //preRadarModeIndex = stRadarMode.uiRadarModeIndex;
            // }

            // ++ pRadarMode;
            }
        }

        /*! \bug  UDF 개수와 주파수 밴드 개수를 비교함.
                \date 2008-11-05 21:25:02, 조철희
        */
        // 주파수 식별 밴드 개수 보다 많을 경우에는 개수를 optimal 하게 나눠서 하게 한다.
        if( total_bin_count >= NO_FLIB_BAND ) {
            //UINT freq_div = UDIV( UDIV(MAX_FREQ_MHZ,1000), NO_FLIB_BAND );

            opt_count = C_NDIV( total_bin_count, NO_FLIB_BAND );
            /*! \bug  	음수값을 unsigned type으로 변환을 자제해야 한다.
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2014-02-02 13:57:06
            */
            //             if( opt_count == (UINT) _spZero ) {
            //                 opt_count = 1;
            //             }

                        /*! \bug  	음수값을 unsigned type으로 변환을 자제해야 한다.
                                \author 조철희 (churlhee.jo@lignex1.com)
                                \date 	2014-02-02 13:57:06
                        */
            freq_low = ( int ) _spZero;

            total_count = 0L;
            /*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2014-01-24 17:10:50
            */
            j = 0;
            for( i = 0; i < uiHistSize; ++i ) {
                total_count += pHist[i];

                if( total_count >= opt_count ) {
                    /*! \bug  	음수값을 unsigned type으로 변환을 자제해야 한다.
                            \author 조철희 (churlhee.jo@lignex1.com)
                            \date 	2014-02-02 13:56:11
                    */
                    //if( j >= NO_FLIB_BAND ) {
                    if( j >= ( int ) NO_FLIB_BAND ) { //DTEC_Else
                        continue;
                    }

                    theFLib[j].frq.ilow = freq_low;
                    theFLib[j].frq.ihgh = ( int ) ( ( i + 1 ) * FLIB_FREQ_RES_MHZ );        //IMUL( ( j + 1 ), freq_div );

                    freq_low = theFLib[j].frq.ihgh + 1;

                    total_count -= opt_count;

                    ++ j;
                }
            }

            // 나머지 잔여 추가
            if( j >= NO_FLIB_BAND ) {
                //theFLib[NO_FLIB_BAND-1].frq.ilow = freq_low;
                theFLib[NO_FLIB_BAND - 1].frq.ihgh = ( int ) ( i * FLIB_FREQ_RES_MHZ );        //IMUL( ( j + 1 ), freq_div );
            }
            else {
                theFLib[j].frq.ilow = freq_low;
                theFLib[j].frq.ihgh = ( int ) ( i * FLIB_FREQ_RES_MHZ );        //IMUL( ( j + 1 ), freq_div );
            }

        }
        // 주파수 식별 밴드 개수 보다 적을 경우에는 고정 주파수 대역으로 나눈다.
        else {
            UINT freq_div;

            freq_low = _spZero; /* MIN_FREQ_MHZ */

            freq_div = UDIV( ( MAX_FREQ_MHZ - freq_low ), NO_FLIB_BAND );

            /*! \bug  	음수값을 unsigned type으로 변환을 자제해야 한다.
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2014-02-02 13:55:06
            */
            for( i = 0; i < ( int ) NO_FLIB_BAND; ++i ) {
                theFLib[i].frq.ilow = freq_low;
                theFLib[i].frq.ihgh = freq_low + ( int ) freq_div;

                freq_low = theFLib[i].frq.ihgh + 1;
            }
        }

        free( pHist );
    }
}

/**
 * @brief     식별 테이블화를 구성한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-07-31 06:40:48
 * @warning
 */
void CELSignalIdentifyAlg::MakeFreqLibTable()
{
    int l;
    STR_FLOWHIGH band = STR_FLOWHIGH();

    UINT i, in, inSum, uicount;

    STR_FLIB *theFLib;

    if( m_total_ced != _spZero ) {

        //for( auto &stRadarMode : m_vecRadarMode ) {
        for( i = 0; i < m_vecRadarMode.size(); ++i ) {
            SRadarMode *pstRadarMode;

            pstRadarMode = & m_vecRadarMode[i];
            if( pstRadarMode->eRF_Type == RadarModeFreqType::enumFreqUnknown ) {
                theFLib = & m_pFLib[0];
                for( l = 0; l < NO_FLIB_BAND; ++l ) {
                    theFLib->pIdxRadarMode[theFLib->uicount++] = pstRadarMode;
                    ++ theFLib;
                }
            }
            else {
                band.ilow = ( int ) BandSelect( 0, ( UINT ) NO_FLIB_BAND - 1, ( int ) F_UDIV( pstRadarMode->fRF_TypicalMin, FLIB_FREQ_RES_MHZ ) );
                band.ihgh = ( int ) BandSelect( 0, ( UINT ) NO_FLIB_BAND - 1, ( int ) F_UDIV( pstRadarMode->fRF_TypicalMax, FLIB_FREQ_RES_MHZ ) );

                theFLib = & m_pFLib[band.ilow];
                for( l = band.ilow; l <= band.ihgh; ++l ) {
                    theFLib->pIdxRadarMode[theFLib->uicount++] = pstRadarMode;

                    ++ theFLib;
                }

            }

        }

        theFLib = & m_pFLib[0];
        for( i = 0; i < NO_FLIB_BAND; ++i ) {
            inSum = _spZero;
            uicount = theFLib->uicount;

            // 주파수 Fixed에 대해서 식별 테이블화 구성
            in = ArrangeLib2( & theFLib->pIdxRadarMode[inSum], uicount, ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED, theFLib->pLib[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED] );
            inSum += in;

            // 주파수 Agile에 대해서 식별 테이블화 구성
            uicount -= in;
            in = ArrangeLib2( & theFLib->pIdxRadarMode[inSum], uicount, ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE, theFLib->pLib[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE] );
            inSum += in;

            // 주파수 패턴에 대해서 식별 테이블화 구성
            uicount -= in;
            in = ArrangeLib2( & theFLib->pIdxRadarMode[inSum], uicount, ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN, theFLib->pLib[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN] );
            inSum += in;

            // 주파수 호핑에 대해서 식별 테이블화 구성
            uicount -= in;
            in = ArrangeLib2( & theFLib->pIdxRadarMode[inSum], uicount, ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING, theFLib->pLib[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING] );
            inSum += in;

            // 주파수 Unknown에 대해서 식별 테이블화 구성
            uicount -= in;
            in = ArrangeLib2( & theFLib->pIdxRadarMode[inSum], uicount, ENUM_AET_FRQ_TYPE::E_AET_FRQ_UNKNOWN, theFLib->pLib[( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_UNKNOWN] );
            inSum += in;

            ++ theFLib;
        }
    }
    else {
        //printf( "\t [W] CED 데이터베이스에 항목이 없어서 주파수 테이블화 작업을 할 수 없습니다.\n" );
        Log( enNormal, "CED 데이터베이스에 항목이 없어서 주파수 테이블화 작업을 할 수 없습니다." );
    }
}

/**
 * @brief     주파수 및 PRI 형태를 참고하여 식별 테이블화를 구성한다.
 * @param     SRadarMode * inLib
 * @param     UINT count
 * @param     ENUM_AET_FRQ_TYPE enFrqType
 * @param     STR_LIB_RANGE * pLibRange
 * @param     EnumLibType eLibType
 * @return    UINT
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-01-31, 오후 9:10
 * @warning
 */
UINT CELSignalIdentifyAlg::ArrangeLib2( SRadarMode **inLib, UINT uicount, ENUM_AET_FRQ_TYPE enFrqType, STR_LIB_RANGE *pLibRange )
{
    UINT i;
    UINT incNoEid = _spZero;

    SRadarMode *bkupLIBINDEX;

    SRadarMode **pLibIndex, **pFrqEid;

    if( uicount != 0 ) {
        // 1. D&S 에 대한 정렬
        pLibIndex = inLib;
        pFrqEid = inLib;

        pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].from = pFrqEid;
        pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].uicount = _spZero;
        for( i = 0; i < uicount; ++i, ++pLibIndex ) {
            if( CheckFreqType( enFrqType, *pLibIndex ) != true ) { //DTEC_NullPointCheck
                continue;
            }

            // D&S 에 개한 규칙성 추가
            if( ( *pLibIndex )->ePRI_Type == RadarModePRIType::enumDwellSWITCH ) {
                bkupLIBINDEX = *pFrqEid;
                *pFrqEid = *pLibIndex;
                *pLibIndex = bkupLIBINDEX;

                ++ pFrqEid;
                ++ incNoEid;

                ++ pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH].uicount;
            }

        }

        // 2. Stable 에 대한 정렬
        pLibIndex = pFrqEid;

        pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].from = pFrqEid;
        pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].uicount = _spZero;
        for( i = incNoEid; i < uicount; ++i, ++pLibIndex ) {
            if( CheckFreqType( enFrqType, *pLibIndex ) != true ) { //DTEC_NullPointCheck
                continue;
            }

            // Stable 에 개한 규칙성 추가
            if( ( *pLibIndex )->ePRI_Type == RadarModePRIType::enumStable ) {
                bkupLIBINDEX = *pFrqEid;
                *pFrqEid = *pLibIndex;
                *pLibIndex = bkupLIBINDEX;

                ++ pFrqEid;
                ++ incNoEid;

                ++ pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED].uicount;
            }
        }

        // 3. Stagger 에 대한 정렬
        pLibIndex = pFrqEid;
        pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].from = pFrqEid;
        pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].uicount = _spZero;
        for( i = incNoEid; i < uicount; ++i, ++pLibIndex ) {
            if( CheckFreqType( enFrqType, *pLibIndex ) != true ) { //DTEC_Else
                continue;
            }

            // Stagger 에 개한 규칙성 추가
            if( ( *pLibIndex )->ePRI_Type == RadarModePRIType::enumSTAGGER ) {
                bkupLIBINDEX = *pFrqEid;
                *pFrqEid = *pLibIndex;
                *pLibIndex = bkupLIBINDEX;

                ++ pFrqEid;
                ++ incNoEid;                    // next loop initial val.

                //++ (pLibRange+ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER)->uicount;    // count of IPL(Stable)
                ++ pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER].uicount;
            }
        }

        // 4. 패턴 에 대한 정렬
        pLibIndex = pFrqEid;
        pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].from = pFrqEid;
        pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].uicount = _spZero;
        for( i = incNoEid; i < uicount; ++i, ++pLibIndex ) {
            if( CheckFreqType( enFrqType, *pLibIndex ) != true ) { //DTEC_NullPointCheck
                continue;
            }

            // 패턴 에 개한 규칙성 추가
            // Sliding
            if( ( *pLibIndex )->ePRI_Type == RadarModePRIType::enumPATTERN ) {
                bkupLIBINDEX = *pFrqEid;
                *pFrqEid = *pLibIndex;
                *pLibIndex = bkupLIBINDEX;

                ++ pFrqEid;
                ++ incNoEid;

                //++ (pLibRange+ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN)->uicount;
                ++ pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN].uicount;
            }
        }

        // 5. 지터 에 대한 식별
        pLibIndex = pFrqEid;
        pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].from = pFrqEid;
        pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].uicount = _spZero;
        for( i = incNoEid; i < uicount; ++i, ++pLibIndex ) {
            if( CheckFreqType( enFrqType, *pLibIndex ) != true ) { //DTEC_NullPointCheck
                continue;
            }

            if( ( *pLibIndex )->ePRI_Type == RadarModePRIType::enumJITTER ) {
                bkupLIBINDEX = *pFrqEid;
                *pFrqEid = *pLibIndex;
                *pLibIndex = bkupLIBINDEX;

                ++ pFrqEid;
                ++ incNoEid;

                ++ pLibRange[( int ) ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER].uicount;
            }
        }

        // 6. enumUndefinedPRI_LegacyType 에 대한 식별
        pLibIndex = pFrqEid;
        //(pLibRange+_UNKNOWN_PRI)->from = pFrqEid;		// Pattern IPL range
        pLibRange[_UNKNOWN_PRI].from = pFrqEid;
        //(pLibRange+_UNKNOWN_PRI)->uicount = _spZero;
        pLibRange[_UNKNOWN_PRI].uicount = _spZero;
        for( i = incNoEid; i < uicount; ++i, ++pLibIndex ) {
            if( CheckFreqType( enFrqType, *pLibIndex ) != true ) { //DTEC_NullPointCheck
                continue;
            }

            if( ( *pLibIndex )->ePRI_Type == RadarModePRIType::enumPRIUnknown ) {
                bkupLIBINDEX = *pFrqEid;
                *pFrqEid = *pLibIndex;
                *pLibIndex = bkupLIBINDEX;

                ++ pFrqEid;
                ++ incNoEid;

                //++ (pLibRange+_UNKNOWN_PRI)->uicount;
                ++ pLibRange[_UNKNOWN_PRI].uicount;
            }
        }

        // 7. PRI 타입이 잘못된 레이더 모드 출력
//         for( i=incNoEid ; i < uicount ; ++i, ++pLibIndex ) {
//             bool bRet=true;
//             if( pLibIndex != NULL && CheckFreqType( frqType, *pLibIndex ) != true ) { //DTEC_NullPointCheck
//                 if( *pLibIndex == NULL ) {
//                     if( bRet == true ) {
//                         Log( enNormal, " Invalid RadarMode[%d] Freq Type[%d] : " , uicount, frqType );
//                         bRet = false;
//                     }
//                     Log( enNoLineFeed, "Invalid Index !!!" );
//                 }
//                 else {
//                     if( bRet == true ) {
//                         Log( enNormal, " Invalid RadarMode[%d] Freq Type[%d] : " , uicount, frqType );
//                         bRet = false;
//                     }
//                     Log( enNoLineFeed, "[%d]" , (*pLibIndex)->iRadarModeIndex );
//                 }
//                 continue;
//             }
//         }
    }

    return incNoEid;
}

/**
 * @brief     레이더 모드에서 입력한 형태별로 검증한다.
 * @param     NUM_AET_FRQ_TYPE enFrqType
 * @param     SRadarMode * pRadarMode
 * @param     frqType
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-10-24, 오후 8:37
 * @warning
 */
bool CELSignalIdentifyAlg::CheckFreqType( ENUM_AET_FRQ_TYPE enFrqType, SRadarMode *pRadarMode )
{
    //char *pMopCode1;
    bool bRet = false;

    //pMopCode1 = pRadarMode->strModulationCode.GetBuffer();

    switch( enFrqType ) {
        //case _CHIRP_UP :
        //case _CHIRP_DN :
        //case _PMOP :
        //case (int)ENUM_AET_FRQ_TYPE::E_AET_FRQ_UNKNOWN :
        //case MAX_FRQTYPE :
        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE:
            { //DTEC_Else

            }
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED:
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumFIXED ) {
                bRet = true;
            }
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE:
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumAGILE ) {
                bRet = true;
            }
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING:
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumHOPPING ) {
                bRet = true;
            }
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN:
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumPATTERN ) {
                bRet = true;
            }
            break;

        default:
            { //DTEC_Else
                bRet = true;
                //, , , ENUM_AET_FRQ_TYPE::E_AET_FRQ_IGNORE, _CHIRP_UP, _CHIRP_DN, _PMOP, (int)ENUM_AET_FRQ_TYPE::E_AET_FRQ_UNKNOWN, MAX_FRQTYPE
            }
            break;
    }

    return bRet;

}

/**
 * @brief     입력한 주파수 범위에 따라서 식별 테이블화의 인덱스를 얻는다.
 * @param     int from
 * @param     int to
 * @param     int searchVal
 * @return    UINT
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-07-31 06:56:18
 * @warning
 */
UINT CELSignalIdentifyAlg::BandSelect( int from, int to, int searchVal ) //#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found)
{
    UINT uiRet;
    int div2;

    div2 = ( ( to + from ) / 2 );

    if( abs( ( int ) ( from - to ) ) <= 1 ) {
        if( m_pFLib[from].frq.ihgh < searchVal ) {
            uiRet = ( UINT ) to;
        }
        else {
            uiRet = ( UINT ) from;
        }
    }
    else {
        if( m_pFLib[div2].frq.ilow >= searchVal ) {
            uiRet = BandSelect( from, div2, searchVal );
        }
        else {
            uiRet = BandSelect( div2, to, searchVal );
        }
    }

    return uiRet;
}

/**
 * @brief     레이더 모드의 우선 순위로 식별 결과를 정렬한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2015-01-04 오후 2:07
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyPriority()
{
    UINT i, j;

    j = 0;
    for( i = 0; i < m_toLib; ++i ) {
        SRadarMode *pRadarMode;

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
    UINT i, j;

    SRadarMode *pTempRadarMode;

    // 위협 후보 식별을 정렬한다.
    m_nCoIdResult = ( int ) m_toLib;
    for( i = m_toLib; i > 0; --i ) {
        //sorted = true;

        for( j = 0; j < m_toLib - 1; ++j ) {
            SRadarMode *pRadarModeRef, *pRadarModeNxt;

            pRadarModeRef = m_pIdResult[j].pIdxRadarMode;
            if( pRadarModeRef == NULL ) { //DTEC_NullPointCheck
                continue;
            }

            pRadarModeNxt = m_pIdResult[j + 1].pIdxRadarMode;
            if( pRadarModeNxt == NULL ) { //DTEC_NullPointCheck
                continue;
            }

            // 0 순위 : 사전에 식별율로 정렬되었기 때문에, 동일할 때만 나머지 정렬 기준으로 정렬
            if( m_pIdResult[j].uRatio == m_pIdResult[j + 1].uRatio ) {
                // 1 순위 : 레이더 우선순위, 우선순의는 큰 값이 크다.
                if( pRadarModeRef->uiRadarPriority < pRadarModeNxt->uiRadarPriority /* && ( pRadarModeRef->nPriority > 0 && pRadarModeNxt->nPriority > 0 ) */ ) {
                    SWAP( pTempRadarMode, m_pIdResult[j + 1].pIdxRadarMode, m_pIdResult[j].pIdxRadarMode )
                }
                // 2 순위 : 레이더모드 우선순위, 우선순의는 큰 값이 크다.
                else if( pRadarModeRef->uiRadarPriority == pRadarModeNxt->uiRadarPriority /* || pRadarModeNxt->nPriority <= 0 || pRadarModeNxt->nPriority */ ) {
                    if( pRadarModeRef->uiRadarModePriority < pRadarModeNxt->uiRadarModePriority /* && ( pRadarModeNxt->nRadarModenPriority > 0 && pRadarModeRef->nRadarModenPriority > 0 ) */ ) {
                        SWAP( pTempRadarMode, m_pIdResult[j + 1].pIdxRadarMode, m_pIdResult[j].pIdxRadarMode )
                    }
                    else if( pRadarModeRef->uiRadarModePriority == pRadarModeNxt->uiRadarModePriority /* || pRadarModeNxt->nRadarModenPriority <= 0 || pRadarModeNxt->nRadarModenPriority */ ) {
#if 1
                        // 레이더 모드 인데스에서 ELNOT 순으로 정렬
                        if( IsSortELNOT( pRadarModeRef, pRadarModeNxt ) == true ) {
#else
                        if( pRadarModeRef->uiRadarModeIndex > pRadarModeNxt->uiRadarModeIndex ) {
#endif
                            SWAP( pTempRadarMode, m_pIdResult[j + 1].pIdxRadarMode, m_pIdResult[j].pIdxRadarMode )
                        }
                    }
                    else { //DTEC_ELSE

                    }
                }
                else { //DTEC_ELSE

                }
            }
        }

    }

}

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

/**
 * @brief     위협 에미터의 주파수/PRI 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2013-10-09 오후 1:27
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyFreqPRI( SRxLOBData *pLOBData )
{
    STR_FLOWHIGH band = STR_FLOWHIGH();

    unsigned char nCallFunc;

    int *pFrqType = NULL;
    int *pPriType = NULL;

    band.ilow = ( int ) BandSelect( 0, ( UINT ) NO_FLIB_BAND - 1, ( int ) F_UDIV( pLOBData->fFreqMin, 1 ) );
    band.ihgh = ( int ) BandSelect( 0, ( UINT ) NO_FLIB_BAND - 1, ( int ) C_UDIV( pLOBData->fFreqMax, 1 ) );

    // 주파수 및 PRI 형태 식별 여부
    if( ( pLOBData->vFreqType > ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE ) || ( pLOBData->vPRIType > ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE ) ) { //DTEC_NullPointCheck
        pFrqType = NULL;
        pPriType = NULL;
    }
    else {
        pFrqType = ( int * ) & m_HowToId[( int ) pLOBData->vFreqType][( int ) pLOBData->vPRIType].frq[0];
        pPriType = ( int * ) & m_HowToId[( int ) pLOBData->vFreqType][( int ) pLOBData->vPRIType].pri[0];

        while( *pFrqType >= 0 && *pPriType >= 0 ) { //#FA_C_PotentialUnboundedLoop_T2
            if( *pFrqType < 0 || *pPriType < 0 ) { //DTEC_Else
                printf( "\n\t [W] Invalid Freq[%d], PRI[%d]", *pFrqType, *pPriType );
                WhereIs;
                break;
            }
            else {
                // 범위 체크한 경우, 주파수 범위에 밴드를 필터링 하게 함.
                FilterBand( &m_pFLib[band.ilow].pLib[*pFrqType][*pPriType], &m_pFLib[band.ihgh].pLib[*pFrqType][*pPriType], &band, &m_toLib );

                // 식별 테스트 하기위해서 무조건 식별 성공으로 함.
                if( m_fromLib != m_toLib ) {

                    // 1. 신호 형태 식별
                    IdentifySigType( pLOBData->vSignalType );

                    // 2. MOP 식별
                    IdentifyMOPType( pLOBData->enMOPType );

                    // 4. 주파수 식별
                    nCallFunc = m_FrqIdCallFunc[( int ) pLOBData->vFreqType][*pFrqType];
                    CallFreqFunc( nCallFunc, pLOBData );

                    // 5. PRI 식별
                    if( pLOBData->vSignalType != ST_CW ) {
                        nCallFunc = m_PriIdCallFunc[( int ) pLOBData->vPRIType][*pPriType];
                        CallPriFunc( nCallFunc, pLOBData );
                    }

                    // 6. PPG 식별
                    //IdentifyPPG();

                    m_fromLib = m_toLib;
                }
            }

            ++pFrqType;
            ++pPriType;
        }
    }
}

/**
 * @brief     빔 정보에 대해서 주파수/PRI 식별을 수행
 * @param     SRxABTData * pABTData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-12-05 16:59:39
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyFreqPRI( SRxABTData *pABTData )
{
    STR_FLOWHIGH band = STR_FLOWHIGH();

    unsigned char nCallFunc;

    int *pFrqType = NULL;
    int *pPriType = NULL;

    band.ilow = ( int ) BandSelect( 0, ( UINT ) NO_FLIB_BAND - 1, ( int ) F_UDIV( pABTData->fFreqMin, 1 ) );
    band.ihgh = ( int ) BandSelect( 0, ( UINT ) NO_FLIB_BAND - 1, ( int ) C_UDIV( pABTData->fFreqMax, 1 ) );

    // 주파수 및 PRI 형태 식별 여부
    if( ( pABTData->vFreqType > ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE ) || ( pABTData->vPRIType > ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE ) ) { //DTEC_NullPointCheck
        pFrqType = NULL;
        pPriType = NULL;
    }
    else {
        pFrqType = ( int * ) & m_HowToId[( int ) pABTData->vFreqType][( int ) pABTData->vPRIType].frq[0];
        pPriType = ( int * ) & m_HowToId[( int ) pABTData->vFreqType][( int ) pABTData->vPRIType].pri[0];

        while( *pFrqType >= 0 && *pPriType >= 0 ) { //#FA_C_PotentialUnboundedLoop_T2
            if( *pFrqType < 0 || *pPriType < 0 ) { //DTEC_Else
                printf( "\n\t [W] Invalid Freq[%d], PRI[%d]", *pFrqType, *pPriType );
                WhereIs;
            }
            else {
                // 범위 체크한 경우, 주파수 범위에 밴드를 필터링 하게 함.
                FilterBand( &m_pFLib[band.ilow].pLib[*pFrqType][*pPriType], &m_pFLib[band.ihgh].pLib[*pFrqType][*pPriType], &band, &m_toLib );

                // 식별 테스트 하기위해서 무조건 식별 성공으로 함.
                if( m_fromLib != m_toLib ) {
                    // 1. 신호 형태 식별
                    IdentifySigType( pABTData->vSignalType );

                    // 2. MOP 식별
                    IdentifyMOPType( pABTData->enMOPType );

                    // 4. 주파수 식별
                    nCallFunc = m_FrqIdCallFunc[( int ) pABTData->vFreqType][*pFrqType];
                    CallFreqFunc( nCallFunc, pABTData );

                    // 5. PRI 식별
                    if( pABTData->vSignalType != ST_CW ) {
                        nCallFunc = m_PriIdCallFunc[( int ) pABTData->vPRIType][*pPriType];
                        CallPriFunc( nCallFunc, pABTData );
                    }

                    // 6. PPG 식별
                    //IdentifyPPG();

                    m_fromLib = m_toLib;
                }
            }

            ++pFrqType;
            ++pPriType;
        }
    }
}

/**
 * @brief     주파수 범위 안에 속하는 식별 후보를 찾는다.
 * @param     STR_LIB_RANGE * pFrqLow
 * @param     STR_LIB_RANGE * pFrqHgh
 * @param     STR_FLOWHIGH * pBand
 * @param     UINT * pIdxLib
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-08-01 11:55:08
 * @warning
 */
void CELSignalIdentifyAlg::FilterBand( STR_LIB_RANGE *pFrqLow, STR_LIB_RANGE *pFrqHgh, STR_FLOWHIGH *pBand, UINT *pIdxLib )
{
    UINT i, j;
    unsigned int uiRefnoIpl;

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

    }
    else {
        SRadarMode *pRadarMode;

        if( pBand->ihgh == pBand->ilow ) {
            for( i = 0; i < pFrqLow->uicount; ++i ) {
                pRadarMode = *pLeftLib;
                if( pRadarMode == NULL ) { //DTEC_NullPointCheck
                    continue;
                }

                pLeftLib++;

                m_pIdResult[( *pIdxLib )++].pIdxRadarMode = pRadarMode;
            }
        }
        else {
            if( pFrqLow->uicount > pFrqHgh->uicount ) {
                for( i = 0; i < pFrqLow->uicount; ++i ) {
                    pRadarMode = *pLeftLib;
                    if( pRadarMode == NULL ) { //DTEC_NullPointCheck
                        continue;
                    }

                    pLeftLib++;

                    uiRefnoIpl = pRadarMode->uiRadarModeIndex;
                    pRightLib = pFrqHgh->from;
                    for( j = 0; j < pFrqHgh->uicount; ++j ) {
                        pRadarMode = *pRightLib;
                        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
                            continue;
                        }

                        pRightLib++;
                        if( uiRefnoIpl == pRadarMode->uiRadarModeIndex ) {
                            m_pIdResult[( *pIdxLib )++].pIdxRadarMode = pRadarMode;
                        }
                    }
                }
            }
            else {
                for( i = 0; i < pFrqHgh->uicount; ++i ) {
                    pRadarMode = *pRightLib;
                    if( pRadarMode == NULL ) { //DTEC_NullPointCheck
                        continue;
                    }

                    pRightLib++;

                    uiRefnoIpl = pRadarMode->uiRadarModeIndex;
                    pLeftLib = pFrqLow->from;
                    for( j = 0; j < pFrqLow->uicount; ++j ) {
                        pRadarMode = *pLeftLib;
                        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
                            continue;
                        }

                        pLeftLib++;

                        if( uiRefnoIpl == pRadarMode->uiRadarModeIndex ) {
                            m_pIdResult[( *pIdxLib )++].pIdxRadarMode = pRadarMode;
                        }
                    }
                }
            }
        }
    }
}


/**
 * @brief     IdentifyMOPType
 * @param     int iMOPType
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-09 15:37:13
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyMOPType( ENUM_MOP_TYPE enMOPType )
{
    UINT i;
    STR_LIB_IDRESULT *pIdxLibAmbi;
    UINT toLib;

    toLib = m_fromLib;
    pIdxLibAmbi = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLibAmbi ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLibAmbi->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( enMOPType == E_MOP_FMOP ) {
            if( pRadarMode->eSignalType != CEDSignalType::enumFMOP ) {
                continue;
            }
        }
        else if( enMOPType == E_MOP_PMOP ) {
            if( pRadarMode->eSignalType != CEDSignalType::enumPMOP ) {
                continue;
            }
        }
        else {

        }

        // 빔 번호 추가
        m_pIdResult[toLib++].pIdxRadarMode = pIdxLibAmbi->pIdxRadarMode;
    }

    m_toLib = toLib;

}

/**
 * @brief     신호 형태로 신호 식별을 수행한다.
 * @param     int iSignalType
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-08-01 12:46:52
 * @warning
 */
void CELSignalIdentifyAlg::IdentifySigType( int iSignalType )
{
    UINT i;
    STR_LIB_IDRESULT *pIdxLibAmbi;
    UINT toLib;

    toLib = m_fromLib;
    pIdxLibAmbi = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLibAmbi ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLibAmbi->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        //printf( "\n iSignalType[%d], SignalType::enumPulsed[%d], pRadarMode->eSignalType[%d]" , iSignalType, SignalType::enumPulsed, pRadarMode->eSignalType );
        if( iSignalType == ST_NORMAL_PULSE ) {
            if( pRadarMode->eSignalType != CEDSignalType::enumPulsed && \
                pRadarMode->eSignalType != CEDSignalType::enumFMOP && \
                pRadarMode->eSignalType != CEDSignalType::enumPMOP ) {
                continue;
            }
        }
        else if( iSignalType == ST_CW ) {
            if( pRadarMode->eSignalType != CEDSignalType::enumCW ) {
                continue;
            }
        }
        else {
            // 도플러, HIGH PRF는 미식별로 함.
            continue;
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
// 	bool bRet = false;
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
// 		if( bRet == false ) {
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


/**
 * @brief     주파수 형태를 무시한 경우의 주파수 범위에 대한 식별 처리를 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2014-12-28 오후 1:47
 * @warning
 */
void CELSignalIdentifyAlg::FIdentifyFreq( void *pData, bool bLOB )
{
    UINT i, toLib;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        bool bRet1;

        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

            /*! \todo   주파수를 곱해서 연산하는데 주파수 테이블부터 연산을 고려하여 테이블하도록 수정
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2015-10-20 02:08:45
            */
            bRet1 = TCompMarginDiff<float>( pLOBData->fFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == true || \
                    TCompMarginDiff<float>( pLOBData->fFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == true;
            if( bRet1 == true ) {
            }
            else {
                continue;
            }
        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

            /*! \todo   주파수를 곱해서 연산하는데 주파수 테이블부터 연산을 고려하여 테이블하도록 수정
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2015-10-20 02:08:45
            */
            bRet1 = TCompMarginDiff<float>( pABTData->fFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == true || \
                    TCompMarginDiff<float>( pABTData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == true;
            if(  bRet1 == true ) {
            }
            else {
                continue;
            }
        }
    }

    m_toLib = toLib;
}

/**
 * @brief     주파수 고정-고정 신호에 대해서 신호 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-08-01 14:51:01
 * @warning
 */
void CELSignalIdentifyAlg::FIdentifyFixFix( void *pData, bool bLOB )
{
    UINT i, toLib;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        bool bCheck;

        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

            /*! \todo   주파수를 곱해서 연산하는데 주파수 테이블부터 연산을 고려하여 테이블하도록 수정
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2015-10-20 02:08:45
            */

            bCheck = TCompMarginDiff<float>( pLOBData->fFreqMean, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == true || \
                     TCompMarginDiff<float>( pLOBData->fFreqMean, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == true;
            if( bCheck == false  ) {
                continue;
            }
            else {
                /*! \debug  범위 식별을 추가함.
                	\author 조철희 (churlhee.jo@lignex1.com)
                	\date 	2023-11-10 20:25:41
                */

                bCheck = TCompMarginDiff<float>( pLOBData->fFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
                if( bCheck == false ) {
                    continue;
                }

                bCheck = TCompMarginDiff<float>( pLOBData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
                if( bCheck == false ) {
                    continue;
                }

            }

        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

            /*! \todo   주파수를 곱해서 연산하는데 주파수 테이블부터 연산을 고려하여 테이블하도록 수정
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2015-10-20 02:08:45
            */
            bCheck = TCompMarginDiff<float>( pABTData->fFreqMean, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == true || \
                     TCompMarginDiff<float>( pABTData->fFreqMean, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) == true;
            if( bCheck == false ) {
                continue;
            }
            else {
                /*! \debug  범위 식별을 추가함.
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2023-11-10 20:25:41
                */

                bCheck = TCompMarginDiff<float>( pABTData->fFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
                if( bCheck == false ) {
                    continue;
                }

                bCheck = TCompMarginDiff<float>( pABTData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
                if( bCheck == false ) {
                    continue;
                }

            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     주파수 고정-호핑 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-08-01 16:04:10
 * @warning
 */
void CELSignalIdentifyAlg::FIdentifyFixHop( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;
    STR_LIB_IDRESULT *pIdxLib;

    bool bret;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

#ifdef __VXWORKS__
            float fFreqMean = pLOBData->fFreqMean;

            bret = CompHoppingDwellLevel( & fFreqMean, _spOne, &pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError );
#else
            bret = CompHoppingDwellLevel( & pLOBData->fFreqMean, _spOne, &pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError );
#endif
            if( bret == false ) {
                continue;
            }
        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

#ifdef __VXWORKS__
            float fFreqMean = pABTData->fFreqMean;
            bret = CompHoppingDwellLevel( & fFreqMean, _spOne, &pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError );
#else
            bret = CompHoppingDwellLevel( & pABTData->fFreqMean, _spOne, &pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError );
#endif
            if( bret == false ) {
                continue;
            }

        }

        // 식별값 저장
        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     FIdentifyFixPat
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-08-07 13:18:09
 * @warning
 */
 // void CELSignalIdentifyAlg::FIdentifyFixPat( void *pLOBData, bool bLOB)
 // {
 //
 // }

 /**
  * @brief     주파수 패턴-패턴 신호에 대해서 식별을 수행한다.
  * @param     SRxLOBData * pLOBData
  * @return    void
  * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
  * @author    조철희 (churlhee.jo@lignex1.com)
  * @version   1.0.0
  * @date      2008-08-07 13:20:20
  * @warning
  */
void CELSignalIdentifyAlg::FIdentifyHopHop( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;

    bool bret;

    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;

    pIdxLib = & m_pIdResult[m_fromLib];

    // 호핑 단수와 레벨 값 비교 추가
    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        // bool bMatch=false;
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;
#ifdef __VXWORKS__
            float fFreqSeg[MAX_FREQ_PRI_STEP];

            memcpy( fFreqSeg, pLOBData->fFreqSeq, sizeof( float ) * pLOBData->vFreqPositionCount );
            bret = CompHoppingDwellLevel( fFreqSeg, pLOBData->vFreqPositionCount, &pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError );
#else
            bret = CompHoppingDwellLevel( pLOBData->fFreqSeq, pLOBData->vFreqPositionCount, &pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError );
#endif

            if( bret == false ) {
#ifdef _DEBUG
                CompHoppingDwellLevel( pLOBData->fFreqSeq, pLOBData->vFreqPositionCount, &pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError );
#endif
                continue;
            }

        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;
#ifdef __VXWORKS__
            float fFreqSeg[MAX_FREQ_PRI_STEP];
            memcpy( fFreqSeg, pABTData->fFreqSeq, sizeof( float ) * pABTData->vFreqPositionCount );
            bret = CompHoppingDwellLevel( fFreqSeg, pABTData->vFreqPositionCount, &pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError );
#else
            bret = CompHoppingDwellLevel( pABTData->fFreqSeq, pABTData->vFreqPositionCount, &pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError );
#endif
            if( bret == false ) {
#ifdef _DEBUG
                CompHoppingDwellLevel( pABTData->fFreqSeq, pABTData->vFreqPositionCount, &pRadarMode->vecRadarMode_RFSequenceValues, m_pSEnvironVariable->fMarginFrqError );
#endif
                continue;
            }

        }

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
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-10-27, 오전 12:20
 * @warning
 */
bool CELSignalIdentifyAlg::CompSwitchLevel( float *fSeries, unsigned int uiCoSeries, vector <SRadarMode_Sequence_Values> *pvecRadarPRI_Values, SRadarPRI_SequenceNumIndex *pPRI_SequenceNumIndex, int coNumIndex )
{
    int i, l;

    SRadarMode_Sequence_Values *pRadarPRI_Values;

    bool bRet = false;
    SRadarPRI_SequenceNumIndex *pTempPRI_SequenceNumIndex, *pTempPRI_SequenceNumIndex2;

    if( uiCoSeries == 0 ) {
        // bRet = false;
    }
    else {
        if( pvecRadarPRI_Values->size() > 0 ) {
            pTempPRI_SequenceNumIndex = pPRI_SequenceNumIndex;

            for( i = 0; i < coNumIndex; ++i ) {
                if( pTempPRI_SequenceNumIndex->nPRI_Index - 1 < ( int ) pvecRadarPRI_Values->size() ) {
                    pRadarPRI_Values = & pvecRadarPRI_Values->at( ( UINT ) pTempPRI_SequenceNumIndex->nPRI_Index - 1 );

                    bRet = TCompMarginDiff<float>( fSeries[0], pRadarPRI_Values->f_Min, pRadarPRI_Values->f_Max, ( float ) m_pSEnvironVariable->fMarginPriError );
                    if( true == bRet ) {
                        pTempPRI_SequenceNumIndex2 = & pTempPRI_SequenceNumIndex[1];
                        // 나머지 레벨 값을 비교.
                        for( l = 1; l < ( int ) uiCoSeries; ++l ) {
                            pRadarPRI_Values = & pvecRadarPRI_Values->at( ( UINT ) pTempPRI_SequenceNumIndex->nPRI_Index - 1 );
                            if( pTempPRI_SequenceNumIndex2 >= & pPRI_SequenceNumIndex[coNumIndex] ) {
                                pTempPRI_SequenceNumIndex2 = pPRI_SequenceNumIndex;
                            }

                            if( pTempPRI_SequenceNumIndex2->nPRI_Index - 1 < ( int ) pvecRadarPRI_Values->size() ) {
                                pRadarPRI_Values = & pvecRadarPRI_Values->at( ( UINT ) pTempPRI_SequenceNumIndex2->nPRI_Index - 1 );
                                bRet = TCompMarginDiff<float>( fSeries[l], pRadarPRI_Values->f_Min, pRadarPRI_Values->f_Max, ( float ) m_pSEnvironVariable->fMarginFrqError );
                                if( false == bRet ) {
                                    break;
                                }
                            }
                            else {
                                bRet = false;
                                break;
                            }

                            ++ pTempPRI_SequenceNumIndex2;
                        }

                    }

                    ++ pTempPRI_SequenceNumIndex;

                    if( true == bRet ) {
                        break;
                    }
                }
                else {
                    LogPrint( "\n AAAAAA " );
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
 * @brief     CompHoppingDwellLevel
 * @param     float * series
 * @param     unsigned int uiCoSeries
 * @param     vector <SRadarMode_Sequence_Values> * pVecRadarMode_PRISequence_Values
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-21 16:48:18
 * @warning
 */
bool CELSignalIdentifyAlg::CompHoppingDwellLevel( float *fSeries, unsigned int uiCoSeries, vector <SRadarMode_Sequence_Values> *pvecRadar_Values, float fMarginError, unsigned char *pidxHoppingDwell )
{
    bool bRet = false, bMatch = false;
    size_t szSizeOfRadarMode_Sequence;
    SRadarMode_Sequence_Values pRadarMode_Sequence_Values;

    SRadarMode_Sequence_Values stSRadarMode_Sequence_Values;

    STR_HOPPINGDWELL_INDEX stHopping;

    memset( & stHopping, 0, sizeof( stHopping ) );

    m_vecMatchIndex.clear();

    if( uiCoSeries == 0 ) {

    }
    else if( uiCoSeries == 1 ) {
        bMatch = CompSwitchLevel( *fSeries, pvecRadar_Values, fMarginError, (unsigned char *) pidxHoppingDwell );

    }
    else {
        szSizeOfRadarMode_Sequence = pvecRadar_Values->size();

        if( uiCoSeries == (unsigned int) szSizeOfRadarMode_Sequence ) {
            bMatch = CompSwitchLevel( fSeries, uiCoSeries, pvecRadar_Values, fMarginError, pidxHoppingDwell );

        }
        else if( uiCoSeries < (unsigned int) szSizeOfRadarMode_Sequence ) {
            bMatch = CompSwitchLevel( fSeries, uiCoSeries, pvecRadar_Values, (unsigned int) szSizeOfRadarMode_Sequence, fMarginError, pidxHoppingDwell );

        }

        else {

            //bRet = CompSwitchLevel( series, uiCoSeries, pvecRadar_Values );

        }
    }

    if( pidxHoppingDwell ) {
        unsigned int uiIndex, uiSize;

        uiSize = (unsigned int) m_vecMatchIndex.size();
        if( uiSize != 0 ) {
            uiIndex = (unsigned int) rand() % uiSize;

            memcpy( pidxHoppingDwell, & m_vecMatchIndex[uiIndex], sizeof( STR_HOPPINGDWELL_INDEX ) );

            bMatch = true;
        }
        else {
            bMatch = false;
        }

    }

    bRet = bMatch;

    return bRet;

}

/**
 * @brief     스태거 단을 비교한다., 순서에 맞는 단을 식별 합니다.
 * @param     float * series
 * @param     int coSeries
 * @param     vector <SRadarMode_Sequence_Values> * pVecRadarMode_PRISequence_Values
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2019/04/25 10:19
 * @warning
 */
bool CELSignalIdentifyAlg::CompSwitchLevel( float *fSeries, unsigned int uiCoSeries, vector <SRadarMode_Sequence_Values> *pvecRadar_Values, float fMarginError, unsigned char *pidxHopping )
{
    UINT i, l, ii;

    bool bRet = false, bMatch;
    size_t uiSizeOfRadarMode_PRISequence;
    SRadarMode_Sequence_Values pRadarMode_PRISequence_Values;

    UINT j = 0;
    SRadarMode_Sequence_Values stSRadarMode_Sequence_Values;

    STR_HOPPINGDWELL_INDEX stHopping;

    if( uiCoSeries == 0 ) {
        bRet = false;
    }
    else {
        uiSizeOfRadarMode_PRISequence = pvecRadar_Values->size();

        if( uiSizeOfRadarMode_PRISequence > 0 ) {
            for( i = 0; i < uiCoSeries; ++i ) {
                //WhereIs;
                j = 0;
                stSRadarMode_Sequence_Values = pvecRadar_Values->at( j++ );
                //TRACE( "\n stSRadarMode_Sequence_Values[%f, %f]", stSRadarMode_Sequence_Values.f_Min, stSRadarMode_Sequence_Values.f_Max );
                //TRACE( "\n stSRadarMode_Sequence_Values[%f, %f, %f]", fSeries[i], stSRadarMode_Sequence_Values.f_Min, stSRadarMode_Sequence_Values.f_Max );

                bMatch = TCompMarginDiff<float>( fSeries[i], stSRadarMode_Sequence_Values.f_Min, stSRadarMode_Sequence_Values.f_Max, fMarginError );
                //WhereIs;

                if( true == bMatch ) {
                    if( pidxHopping ) {
                        stHopping.index[0] = i;
                    }

                    // 나머지 레벨 값을 비교.
                    ii = 1;
                    for( l = i + 1; l < uiSizeOfRadarMode_PRISequence + i; ++l ) {
                        stSRadarMode_Sequence_Values = pvecRadar_Values->at( j++ );

                        bMatch = TCompMarginDiff<float>( fSeries[l % uiSizeOfRadarMode_PRISequence], stSRadarMode_Sequence_Values.f_Min, stSRadarMode_Sequence_Values.f_Max, fMarginError );
                        if( false == bMatch ) {
                            break;
                        }
                        else {
                            if( pidxHopping ) {
                                stHopping.index[ii] = ( l % uiCoSeries );
                                ++ ii;
                            }
                        }

                    }

                    if( true == bMatch ) {
                        if( pidxHopping ) {
                            m_vecMatchIndex.push_back( stHopping );
                        }
                        else {
                            bRet = true;
                            break;
                        }
                    }
                }
            }
        }
        else {

        }
    }

    return bRet;

}

/**
 * @brief     CompSwitchLevel
 * @param     float * fSeries
 * @param     unsigned int uiCoSeries
 * @param     vector <SRadarMode_Sequence_Values> * pvecRadar_Values
 * @param     unsigned int uiSizeOfRadarMode_Sequence
 * @param     float fMarginError
 * @param     unsigned char * pidxHoppingDwell
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-16 10:17:17
 * @warning
 */
bool CELSignalIdentifyAlg::CompSwitchLevel( float *fSeries, unsigned int uiCoSeries, vector <SRadarMode_Sequence_Values> *pvecRadar_Values, unsigned int uiSizeOfRadarMode_Sequence,  float fMarginError, unsigned char *pidxHoppingDwell )
{
    bool bMatch, bRet;

    unsigned int i, ii, k, j;

    STR_HOPPINGDWELL_INDEX stHopping;

    bMatch = false;

    SRadarMode_Sequence_Values stSRadarMode_Sequence_Values;

    j = 0;
    for( i = 0; i < uiSizeOfRadarMode_Sequence; ++i ) {
        stSRadarMode_Sequence_Values = pvecRadar_Values->at( i );
        bRet = TCompMarginDiff<float>( fSeries[0], stSRadarMode_Sequence_Values.f_Min, stSRadarMode_Sequence_Values.f_Max, fMarginError );

        if( bRet == true ) {

            if( pidxHoppingDwell ) {
                stHopping.index[0] = i;
            }

            ii = 1;
            k = 1;
            bMatch = false;
            for( j = 1; j < uiSizeOfRadarMode_Sequence; ++j ) {
                stSRadarMode_Sequence_Values = pvecRadar_Values->at( ( i + j ) % uiSizeOfRadarMode_Sequence );
                bRet = TCompMarginDiff<float>( fSeries[k], stSRadarMode_Sequence_Values.f_Min, stSRadarMode_Sequence_Values.f_Max, fMarginError );
                if( bRet == true ) {
                    ++ k;
                    if( pidxHoppingDwell ) {
                        stHopping.index[ii] = ( unsigned char ) ( ( i + j ) % uiSizeOfRadarMode_Sequence );
                        ++ ii;
                    }

                    if( k >= uiCoSeries ) {
                        bMatch = true;
                        break;
                    }
                }
            }

            if( bMatch == true ) {
                if( pidxHoppingDwell ) {
                    m_vecMatchIndex.push_back( stHopping );
                }
                else {
                    bMatch = true;
                    break;
                }
            }

        }
    }

    return bMatch;

}

/**
 * @brief     두 스위치 레벨간의 값을 병합 비교한다.
 * @param     int * pSeries1
 * @param     int * pSeries2
 * @param     int coSeries
 * @param     int margin
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-08, 오후 2:20
 * @warning
 */
 // bool CELSignalIdentifyAlg::CompSwitchLevel( float *pSeries1, float *pSeries2, int coSeries, float margin )
 // {
 // 	int i, j, k, iDiff;
 // 	int index1;
 //
 // 	float *pSeries;
 //
 // 	bool bRet=false;
 //
 // 	if( coSeries != 0 ) {
 // 		for( i=0 ; i < coSeries ; ++i ) {
 // 			bRet = true;
 // 			iDiff = 0;
 // 			for( j=i ; j < coSeries+i ; ++j ) {
 // 				pSeries = pSeries2;
 // 				for( k=j ; k < coSeries+j ; ++k ) {
 // 					index1 = k % coSeries;
 // 					bRet = CompMeanDiff( pSeries1[index1], *pSeries, margin );
 // 					if( false == bRet ) {
 // 						break;
 // 					}
 // 					iDiff += _diffabs( pSeries1[index1], *pSeries );
 // 					++ pSeries;
 // 				}
 // 			}
 //
 // 			if( true == bRet ) {
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
  * @return    bool
  * @author    조철희 (churlhee.jo@lignex1.com)
  * @version   0.0.1
  * @date      2015-10-26, 오후 11:20
  * @warning
  */
bool CELSignalIdentifyAlg::CompSwitchLevel( float fVal, vector <SRadarRF_Values> *pvecRadarRF_Values, SRadarRF_SequenceNumIndex *pRF_SequenceNumIndex, UINT coSeries, SRadarMode *pRadarMode )
{
    UINT i;

    bool bRet = false;

    int nSizeRadarRF_Values = ( int ) pvecRadarRF_Values->size();

    for( i = 0; i < coSeries; ++i ) {
        SRadarRF_Values *pRadarRF_Values;

        if( nSizeRadarRF_Values > pRF_SequenceNumIndex->nRF_Index - 1 ) {
            pRadarRF_Values = & pvecRadarRF_Values->at( ( UINT ) pRF_SequenceNumIndex->nRF_Index - 1 );

            bRet = TCompMarginDiff<float>( fVal, pRadarRF_Values->fRF_Min, pRadarRF_Values->fRF_Max, 0 );
            if( true == bRet ) {
                break;
            }
        }
        else {
            LogPrint( "\n 레이더 모드[%d] 에서 주파수 레벨 값이 잘못됐습니다.", pRadarMode->uiRadarModeIndex );
        }

        ++ pRF_SequenceNumIndex;

    }

    return bRet;

}

/**
 * @brief     CompSwitchLevel
 * @param     float fVal
 * @param     vector <SRadarMode_Sequence_Values> * pvecRadarPRI_Values
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-07 16:48:16
 * @warning
 */
bool CELSignalIdentifyAlg::CompSwitchLevel( float fVal, vector <SRadarMode_Sequence_Values> *pvecRadar_Values, float fMarginError, unsigned char *pidxHopping )
{
    bool bMatch = false, bRet = false;

    UINT i;
    size_t uiSizeOfRadarMode_Sequence;

    SRadarMode_Sequence_Values stSRadarMode_Sequence_Values;

    STR_HOPPINGDWELL_INDEX stHopping;

    uiSizeOfRadarMode_Sequence = pvecRadar_Values->size();

    m_vecMatchIndex.clear();

    for( i = 0; i < uiSizeOfRadarMode_Sequence; ++i ) {
        stSRadarMode_Sequence_Values = pvecRadar_Values->at( i );

        bRet = TCompMarginDiff<float>( fVal, stSRadarMode_Sequence_Values.f_Min, stSRadarMode_Sequence_Values.f_Max, fMarginError );
        if( true == bRet ) {

            if( pidxHopping ) {
                stHopping.index[0] = i;
                m_vecMatchIndex.push_back( stHopping );
            }
            else {
                bMatch = true;
                break;

            }
        }
    }

    return bMatch;
}

/**
 * @brief     PRI 레벨 값을 참조하여 신호 식별을 수행한다.
 * @param     int val
 * @param     vector<SRadarPRI_Values>* pvecRadarPRI_Values
 * @param     SRadarPRI_SequenceNumIndex * pPRI_SequenceNumIndex
 * @param     int coSeries
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-10-27, 오전 12:04
 * @warning
 */
bool CELSignalIdentifyAlg::CompSwitchLevel( float fVal, vector <SRadarMode_Sequence_Values> *pvecRadarPRI_Values, SRadarPRI_SequenceNumIndex *pPRI_SequenceNumIndex, UINT coSeries, SRadarMode *pRadarMode )
{
    UINT i;

    bool bRet = false;
    int nSizeRadarPRI_Values = ( int ) pvecRadarPRI_Values->size();

    for( i = 0; i < coSeries; ++i ) {
        SRadarMode_Sequence_Values *pRadarPRI_Values;

        if( nSizeRadarPRI_Values > pPRI_SequenceNumIndex->nPRI_Index - 1 ) {
            pRadarPRI_Values = & pvecRadarPRI_Values->at( ( UINT ) pPRI_SequenceNumIndex->nPRI_Index - 1 );

            bRet = TCompMarginDiff<float>( fVal, pRadarPRI_Values->f_Min, pRadarPRI_Values->f_Max, 0 );
            if( true == bRet ) {
                break;
            }
        }
        else {
            LogPrint( "\n 레이더 모드[%d] 에서 PRI 레벨 값이 잘못됐습니다.", pRadarMode->uiRadarModeIndex );
        }

        ++ pPRI_SequenceNumIndex;

    }

    return bRet;

}

/**
 * @brief     주파수 패턴-패턴 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-08-07 16:56:56
 * @warning
 */
void CELSignalIdentifyAlg::FIdentifyPatPat( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

            if( false == IdentifyRF_PatternRange( pRadarMode, pLOBData ) ) {
                continue;
            }

        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

            if( false == IdentifyRF_PatternRange( pRadarMode, pABTData ) ) {
                continue;
            }

        }

        // 식별 값 저장
        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     IdentifyRF_PatternRange
 * @param     SRadarMode * pRadarMode
 * @param     SRxLOBData * pLOBData
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-23 10:41:55
 * @warning
 */
bool CELSignalIdentifyAlg::IdentifyRF_PatternRange( SRadarMode *pRadarMode, SRxLOBData *pLOBData ) //#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found)
{
    bool bret = true, bRet1;

    /*! \bug  신뢰성: NULL 체크하여 예외처리하게 함.
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2015-10-6 13:56:40
    */
    if( pRadarMode == NULL ) { //DTEC_NullPointCheck
        bret = false;
    }
    else {
        bRet1 = TIsOverlapSpace<float>( pLOBData->fFreqMin, pLOBData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
        if( true != bRet1) {
            bRet1 = TCompMarginDiff<float>( pLOBData->fFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError );
            if( true != bRet1 ) {
                if( true != TCompMarginDiff<float>( pLOBData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) ) {
                    bret = false;
                }
            }
        }

        /*! \todo		패턴 형태 비교 추가
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2015-03-25 20:53:54
        */
        else if( pRadarMode->eRF_Pattern != 0 && ( ( int ) pLOBData->vFreqPatternType != ( int ) pRadarMode->eRF_Pattern ) ) {
            bret = false;
        }

        else if( TCompMarginDiff<float>( pLOBData->fFreqPatternPeriod, pRadarMode->fRF_PatternPeriodMin, pRadarMode->fRF_PatternPeriodMax, m_pSEnvironVariable->fMarginPriModPeriodErrorRatio ) == _spFalse ) {
            bret = false;
        }

        else {

        }

    }

    return bret;

}

/**
 * @brief     IdentifyRF_PatternRange
 * @param     SRadarMode * pRadarMode
 * @param     SRxABTData * pABTData
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-23 10:41:52
 * @warning
 */
bool CELSignalIdentifyAlg::IdentifyRF_PatternRange( SRadarMode *pRadarMode, SRxABTData *pABTData ) //#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found)
{
    bool bret = true, bRet1;

    /*! \bug  신뢰성: NULL 체크하여 예외처리하게 함.
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2015-10-6 13:56:40
    */
    if( pRadarMode == NULL ) { //DTEC_NullPointCheck
        bret = false;
    }
    else {
        bRet1 = TIsOverlapSpace<float>( pABTData->fFreqMin, pABTData->fPRIMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
        if( true != bRet1 ) {
            bRet1 = TCompMarginDiff<float>( pABTData->fFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError );
            if( true != bRet1 ) {
                if( true != TCompMarginDiff<float>( pABTData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, m_pSEnvironVariable->fMarginFrqError ) ) {
                    bret = false;
                }
            }
        }

        /*! \todo		패턴 형태 비교 추가
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2015-03-25 20:53:54
        */
        else if( pRadarMode->eRF_Pattern != 0 && ( ( int ) pABTData->vFreqPatternType != ( int ) pRadarMode->eRF_Pattern ) ) {
            bret = false;
        }

        else if( TCompMarginDiff<float>( pABTData->fFreqPatternPeriodMean, pRadarMode->fRF_PatternPeriodMin, pRadarMode->fRF_PatternPeriodMax, m_pSEnvironVariable->fMarginPriModPeriodErrorRatio ) == _spFalse ) {
            bret = false;
        }

        else {

        }

    }

    return bret;

}

/**
 * @brief     주파수 어자일-어자일 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-08-07 18:00:42
 * @warning
 */
void CELSignalIdentifyAlg::FIdentifyAgiAgi( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;
    bool bret;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = &m_pIdResult[m_fromLib];
    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( bLOB == true ) {
            //float fOverlapValue;
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

//             fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdFrqRangeNestedRatio * ( pRadarMode->fRF_TypicalMax - pRadarMode->fRF_TypicalMin ), 100.0 );
//             bret = TIsOverlapSpace<float>( pLOBData->fFreqMin, pLOBData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, fOverlapValue );
//             if( bret == false ) {
//                 continue;
//             }

            bret = TCompMarginDiff<float>( pLOBData->fFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
            if( bret == false ) {
                continue;
            }

            bret = TCompMarginDiff<float>( pLOBData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
            if( bret == false ) {
                continue;
            }
        }
        else {
            SRxABTData *pABTData = (SRxABTData *)pData;

            bret = TCompMarginDiff<float>( pABTData->fFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
            if( bret == false ) {
                continue;
            }

            bret = TCompMarginDiff<float>( pABTData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
            if( bret == false ) {
                continue;
            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     주파수 어자일-패턴 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-05, 11:18
 * @warning
 */
void CELSignalIdentifyAlg::FIdentifyAgiPat( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;
    bool bret;
    STR_LIB_IDRESULT *pIdxLib;

    float fOverlapValue;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];
    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

            fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdFrqRangeNestedRatio * ( pRadarMode->fRF_TypicalMax - pRadarMode->fRF_TypicalMin ), 100.0 );
            bret = TIsOverlapSpace<float>( pLOBData->fFreqMin, pLOBData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, fOverlapValue );
            if( bret == _spFalse ) {
                continue;
            }

            bret = TCompMarginDiff<float>( pLOBData->fFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
            if( bret == _spFalse ) {
                continue;
            }

            bret = TCompMarginDiff<float>( pLOBData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
            if( bret == _spFalse ) {
                continue;
            }
        }
        else {
            SRxABTData *pABTData = (SRxABTData *)pData;

            fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdFrqRangeNestedRatio * ( pRadarMode->fRF_TypicalMax - pRadarMode->fRF_TypicalMin ), 100.0 );
            bret = TIsOverlapSpace<float>( pABTData->fFreqMin, pABTData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, fOverlapValue );
            if( bret == _spFalse ) {
                continue;
            }

            bret = TCompMarginDiff<float>( pABTData->fFreqMin, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
            if( bret == _spFalse ) {
                continue;
            }

            bret = TCompMarginDiff<float>( pABTData->fFreqMax, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, 0 );
            if( bret == _spFalse ) {
                continue;
            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     PRI 형태를 무시한 경우의 PRI 범위에 대한 식별 처리를 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2014-12-28 오후 1:49
 * @warning
 */
void CELSignalIdentifyAlg::PIdentifyPRI( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;
    bool bret;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( ( pRadarMode->fPRI_TypicalMin > 0 || pRadarMode->fPRI_TypicalMin < 0 ) || ( pRadarMode->fPRI_TypicalMax > 0 || pRadarMode->fPRI_TypicalMax < 0 ) ) {
            if( bLOB == true ) {
                SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

                bret = ( TCompMarginDiff<float>( pLOBData->fPRIMin, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) == true ||
                    TCompMarginDiff<float>( pLOBData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) == true );

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
            else {
                // SRxABTData *pABTData = (SRxABTData *)pData;
            }

        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     PRI Stable-Stable 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-08-07 18:36:06
 * @warning
 */
void CELSignalIdentifyAlg::PIdentifyStbStb( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;
    bool bret;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

            if( ( pRadarMode->fPRI_TypicalMin > 0 /* || pRadarMode->fPRI_TypicalMin < 0 */ ) || ( pRadarMode->fPRI_TypicalMax > 0 /* || pRadarMode->fPRI_TypicalMax < 0 */ ) ) {
                bret = ( TCompMarginDiff<float>( pLOBData->fPRIMin, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) == true ||
                    TCompMarginDiff<float>( pLOBData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) == true );

                if( bret == _spFalse ) {
                    continue;
                }
            }
        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

            if( ( pRadarMode->fPRI_TypicalMin > 0 /* || pRadarMode->fPRI_TypicalMin < 0 */ ) || ( pRadarMode->fPRI_TypicalMax > 0 /* || pRadarMode->fPRI_TypicalMax < 0 */ ) ) {
                bret = ( TCompMarginDiff<float>( pABTData->fPRIMin, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) == true ||
                    TCompMarginDiff<float>( pABTData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) == true );

                if( bret == _spFalse ) {
                    continue;
                }
            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     PRI Stable-Dwell 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-08-07 18:41:55
 * @warning
 */
void CELSignalIdentifyAlg::PIdentifyStbDwl( void *pData, bool bLOB )
{
    //     UINT i;
    //     UINT toLib;
    //     STR_LIB_IDRESULT *pIdxLib;
    //
    //     toLib = m_fromLib;
    //     pIdxLib = & m_pIdResult[m_fromLib];
    //
    //     for( i=m_fromLib ; i < m_toLib ; ++i, ++pIdxLib ) {
    //         bool bret=false;
    //         SRadarMode* pRadarMode;
    //
    //         pRadarMode = pIdxLib->pIdxRadarMode;
    //         if( pRadarMode == NULL ) { //DTEC_NullPointCheck
    //             continue;
    //         }
    //
    // 		if (bLOB == true) {
    // 			//SRxLOBData *pLOBData = (SRxLOBData *)pData;
    //
    // 			// Dwell 특성 여부
    // // 			for (auto iter = pRadarMode->mapRadarPRI_Sequence.begin(); iter != pRadarMode->mapRadarPRI_Sequence.end(); iter++) { //#FA_C_PotentialUnboundedLoop_T3
    // // 				SRadarPRI_Sequence *pstSRadarPRI_Sequence = &(*iter).second;
    // //
    // // 				SRadarPRI_SequenceNumIndex *pPRI_SequenceNumIndex;
    // // 				vector<SRadarPRI_SequenceNumIndex> *pvecPRI_NumIndex;
    // //
    // // 				pvecPRI_NumIndex = &pstSRadarPRI_Sequence->vecPRI_NumIndex;
    // // 				pPRI_SequenceNumIndex = &pvecPRI_NumIndex->at(0);
    // //
    // // 				bret = CompSwitchLevel(pLOBData->fPRIMin, &pRadarMode->vecRadarMode_PRISequenceValues, pPRI_SequenceNumIndex, pvecPRI_NumIndex->size(), pRadarMode);
    // // 				if (bret == false) {
    // // 					continue;
    // // 				}
    // // 				bret = CompSwitchLevel(pLOBData->fPRIMax, &pRadarMode->vecRadarMode_PRISequenceValues, pPRI_SequenceNumIndex, pvecPRI_NumIndex->size(), pRadarMode);
    // // 				if (bret == false) {
    // // 					continue;
    // // 				}
    // //
    // // 				break;
    // // 			}
    // 		}
    // 		else {
    // 			//SRxABTData *pABTData = (SRxABTData *)pData;
    // 		}
    //
    //         if( bret == false ) {
    //             continue;
    //         }
    //
    //         //m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    //     }
    //
    //     m_toLib = toLib;
}

/**
 * @brief     PRI 스태거-스태거 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-08-07 21:51:48
 * @warning
 */
void CELSignalIdentifyAlg::PIdentifyStgStg( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;
    bool /* bMatch, */ bret;
    STR_LIB_IDRESULT *pIdxLib;

#ifdef __VXWORKS__
    float fPRISeq[MAX_FREQ_PRI_STEP];
#endif

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) {
            continue;
        }

        // 스태거 단수와 레벨 값 비교 추가
        bret = false;

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

            if( pRadarMode->vecRadarMode_PRISequenceValues.size() == ( UINT ) pLOBData->vPRIPositionCount ) {
#ifdef __VXWORKS__
                //TRACE( "\n pLOBData->fPRISeq[%d] : %.1f, %.1f, %.1f, %.1f", pLOBData->vPRIPositionCount, pLOBData->fPRISeq[0], pLOBData->fPRISeq[1], pLOBData->fPRISeq[2], pLOBData->fPRISeq[3] );
                //TRACE( "\n pRadarMode->uiRadarModeIndex[%d]", pRadarMode->uiRadarModeIndex );
                memcpy( fPRISeq, pLOBData->fPRISeq, pLOBData->vPRIPositionCount * sizeof( float ) );
                bret = CompSwitchLevel( fPRISeq, pLOBData->vPRIPositionCount, & pRadarMode->vecRadarMode_PRISequenceValues, m_pSEnvironVariable->fMarginPriError, NULL );
#else
                bret = CompSwitchLevel( pLOBData->fPRISeq, pLOBData->vPRIPositionCount, & pRadarMode->vecRadarMode_PRISequenceValues, m_pSEnvironVariable->fMarginPriError, NULL );
#endif

                if( bret == true ) {
                    m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
                }
            }
        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

            if( pRadarMode->vecRadarMode_PRISequenceValues.size() == ( UINT ) pABTData->vPRIPositionCount ) {
#ifdef __VXWORKS__
                memcpy( fPRISeq, pABTData->fPRISeq, pABTData->vPRIPositionCount * sizeof( float ) );
                bret = CompSwitchLevel( fPRISeq, pABTData->vPRIPositionCount, & pRadarMode->vecRadarMode_PRISequenceValues, m_pSEnvironVariable->fMarginPriError, NULL );
#else
                bret = CompSwitchLevel( pABTData->fPRISeq, pABTData->vPRIPositionCount, & pRadarMode->vecRadarMode_PRISequenceValues, m_pSEnvironVariable->fMarginPriError, NULL );
#endif

                if( bret == true ) {
                    m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
                }
            }
        }

    }

    m_toLib = toLib;
}

/**
 * @brief     PRI 스태거-지터 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-27 17:52:17
 * @warning
 */
void CELSignalIdentifyAlg::PIdentifyStgJit( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;

    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = &m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) {
            continue;
        }

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

            if( false == TCompJitJit<float>( ( float ) _spOne, pLOBData->fPRIMin, pLOBData->fPRIMax, ( float ) _spOne, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, 1 ) ) {
                continue;
            }
            // 		fOverlapValue = FDIV(m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * (pRadarMode->fPRI_TypicalMax - pRadarMode->fPRI_TypicalMin), 100.0);
            // 		if (false == IsOverlapSpace<float>(pLOBData->fPRIMin, pLOBData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, fOverlapValue)) {
            // 			continue;
            // 		}

        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

            if( false == TCompJitJit<float>( ( float ) _spOne, pABTData->fPRIMin, pABTData->fPRIMax, ( float ) _spOne, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, 1 ) ) {
                continue;
            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;

    }

    m_toLib = toLib;
}

/**
 * @brief     PRI 드웰-드웰 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-08-07 22:17:18
 * @warning
 */
void CELSignalIdentifyAlg::PIdentifyDwlDwl( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;
    bool bret;
    STR_LIB_IDRESULT *pIdxLib;

    SRadarMode *pRadarMode;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        //bMatch = false;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        // D&S 단수와 레벨 값 비교 추가
        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

            bret = CompHoppingDwellLevel( pLOBData->fPRISeq, pLOBData->vPRIPositionCount, &pRadarMode->vecRadarMode_PRISequenceValues, m_pSEnvironVariable->fMarginPriError );
            if( bret == false ) {
                continue;
            }
        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

            bret = CompHoppingDwellLevel( pABTData->fPRISeq, pABTData->vPRIPositionCount, &pRadarMode->vecRadarMode_PRISequenceValues, m_pSEnvironVariable->fMarginPriError );
            if( bret == false ) {
                continue;
            }

        }

        m_pIdResult[toLib].pIdxRadarMode = pIdxLib->pIdxRadarMode;

        ++ toLib;

    }

    m_toLib = toLib;
}

/**
 * @brief     PRI 지터-스태거 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-08-07 23:01:38
 * @warning
 */
void CELSignalIdentifyAlg::PIdentifyJitStg( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;

    STR_LIB_IDRESULT *pIdxLib;
    float fOverlapValue;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * ( pRadarMode->fPRI_TypicalMax - pRadarMode->fPRI_TypicalMin ), 100.0 );

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;
            if( false == TIsOverlapSpace<float>( pLOBData->fPRIMin, pLOBData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, fOverlapValue ) ) {
                continue;
            }
        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

            if( false == TIsOverlapSpace<float>( pABTData->fPRIMin, pABTData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, fOverlapValue ) ) {
                continue;
            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     PRI 지터-지터 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-08-07 23:13:18
 * @warning
 */
void CELSignalIdentifyAlg::PIdentifyJitJit( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;

    //int iOverlapValue;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;
        bool bret;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

            bret = TCompMarginDiff<float>( pLOBData->fPRIMin, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError );
            if( bret == false ) {
                continue;
            }
            bret = TCompMarginDiff<float>( pLOBData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError );
            if( bret == false ) {
                continue;
            }
        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

            bret = TCompMarginDiff<float>( pABTData->fPRIMin, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError );
            if( bret == false ) {
                continue;
            }
            bret = TCompMarginDiff<float>( pABTData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError );
            if( bret == false ) {
                continue;
            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     PRI 지터-패턴 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-08-07 23:39:05
 * @warning
 */
void CELSignalIdentifyAlg::PIdentifyJitPat( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;
    STR_LIB_IDRESULT *pIdxLib;

    float fOverlapValue;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];

    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * ( pRadarMode->fPRI_TypicalMax - pRadarMode->fPRI_TypicalMin ), 100.0 );

        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

            if( false == TIsOverlapSpace<float>( pLOBData->fPRIMin, pLOBData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, fOverlapValue ) ) {
                continue;
            }
        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

            if( false == TIsOverlapSpace<float>( pABTData->fPRIMin, pABTData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, fOverlapValue ) ) {
                continue;
            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     PRI 패턴-패턴 신호에 대해서 식별을 수행한다.
 * @param     SRxLOBData * pLOBData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-08-07 23:58:04
 * @warning
 */
void CELSignalIdentifyAlg::PIdentifyPatPat( void *pData, bool bLOB )
{
    UINT i;
    UINT toLib;
    STR_LIB_IDRESULT *pIdxLib;

    //m_pLOBData = pLOBData;

    toLib = m_fromLib;
    pIdxLib = & m_pIdResult[m_fromLib];
    for( i = m_fromLib; i < m_toLib; ++i, ++pIdxLib ) {
        //if( m_optParameter.pri.bCheckRange == true ) {
            //if( m_optParameter.ppattern.bCheckType == true ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        // PRI 범위 체크
        if( bLOB == true ) {
            SRxLOBData *pLOBData = ( SRxLOBData * ) pData;

            if( false == IdentifyPRI_PatternRange( pRadarMode, pLOBData ) ) {
                continue;
            }
        }
        else {
            SRxABTData *pABTData = ( SRxABTData * ) pData;

            if( false == IdentifyPRI_PatternRange( pRadarMode, pABTData ) ) {
                continue;
            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;
    }

    m_toLib = toLib;
}

/**
 * @brief     패턴 범위를 체크하여 식별한다.
 * @param     SRadarMode * pRadarMode
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-11-01, 오후 5:59
 * @warning
 */
bool CELSignalIdentifyAlg::IdentifyPRI_PatternRange( SRadarMode *pRadarMode, SRxLOBData *pLOBData ) //#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found)
{
    bool bret = true;

    /*! \bug  신뢰성: NULL 체크하여 예외처리하게 함.
        \author 조철희 (churlhee.jo@lignex1.com)
        \date 	2015-10-6 13:56:40
    */
    if( pRadarMode == NULL ) { //DTEC_NullPointCheck
        bret = false;
    }
    else {
        bool bRet = ( ( true != TIsOverlapSpace<float>( pLOBData->fPRIMin, pLOBData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, 200. ) ) &&
            ( true != TCompMarginDiff<float>( pLOBData->fPRIMin, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) ) &&
            ( true != TCompMarginDiff<float>( pLOBData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) ) );

        if( bRet == true ) {
            bret = false;
        }

        /*! \todo		패턴 형태 비교 추가
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2015-03-25 20:53:54
        */
        else if( pRadarMode->ePRI_Pattern != 0 && ( ( int ) pLOBData->vPRIPatternType != ( int ) pRadarMode->ePRI_Pattern ) ) {
            bret = false;
        }

        else if( is_not_zero<float>( pRadarMode->fPRI_PatternPeriodMin ) &&
                 is_not_zero<float>( pRadarMode->fPRI_PatternPeriodMax ) ) {
            if( TCompMarginDiff<float>( pLOBData->fPRIPatternPeriod, pRadarMode->fPRI_PatternPeriodMin, pRadarMode->fPRI_PatternPeriodMax, m_pSEnvironVariable->fMarginPriModPeriodErrorRatio ) == _spFalse ) {
                bret = false;
            }
        }

        else {

        }

    }

    return bret;

}

/**
 * @brief     IdentifyPatternRange
 * @param     SRadarMode * pRadarMode
 * @param     SRxABTData * pABTData
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-20 15:50:00
 * @warning
 */
bool CELSignalIdentifyAlg::IdentifyPRI_PatternRange( SRadarMode *pRadarMode, SRxABTData *pABTData ) //#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found)
{
    bool bret = true;
    //int diff;

    /*! \bug  신뢰성: NULL 체크하여 예외처리하게 함.
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2015-10-6 13:56:40
    */
    if( pRadarMode == NULL ) { //DTEC_NullPointCheck
        bret = false;
    }
    else {
        bool bCheck = ( ( true != TIsOverlapSpace<float>( pABTData->fPRIMin, pABTData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, 200. ) ) && \
                      ( true != TCompMarginDiff<float>( pABTData->fPRIMin, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) ) && \
                      ( true != TCompMarginDiff<float>( pABTData->fPRIMax, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax, m_pSEnvironVariable->fMarginPriError ) ) );

        if( bCheck == true  ) {
            bret = false;
        }
        /*! \todo		패턴 형태 비교 추가
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2015-03-25 20:53:54
        */
        else if( pRadarMode->ePRI_Pattern != 0 && ( ( int ) pABTData->vPRIPatternType != ( int ) pRadarMode->ePRI_Pattern ) ) {
            bret = false;
        }

        else if( is_not_zero<float>( pRadarMode->fPRI_PatternPeriodMin ) && is_not_zero<float>( pRadarMode->fPRI_PatternPeriodMax ) ) {
            if( TCompMarginDiff<float>( pABTData->fPRIPatternPeriodMean, pRadarMode->fPRI_PatternPeriodMin, pRadarMode->fPRI_PatternPeriodMax, m_pSEnvironVariable->fMarginPriModPeriodErrorRatio ) == _spFalse ) {
                bret = false;
            }
        }

        else {

        }
    }

    return bret;

}

/**
 * @brief     펄스폭 식별을 수행한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-08-08 00:07:38
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyPW( float fPWMin, float fPWMax )
{
    UINT i;
    UINT toLib;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = 0;
    pIdxLib = & m_pIdResult[0];

    for( i = 0; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

        // 펄스폭 최소, 최대 값이 0 일때는 펄스폭 비교는 무시한다.
        if( is_not_zero<float>( pRadarMode->fPD_TypicalMax ) == true ) {
            // 범위 안에 평균이 들어가지 않으면 실패

//             if( TCompMarginDiff<float>( fPWMin, 0, pRadarMode->fPD_TypicalMax, 0 ) == _spFalse ||
//                 TCompMarginDiff<float>( fPWMax, 0, pRadarMode->fPD_TypicalMax, 0 ) == _spFalse ) {

            bool bCheck = ( TCompMarginDiff<float>( fPWMin, 0, pRadarMode->fPD_TypicalMax, 0 ) == _spFalse ) || \
                          ( TCompMarginDiff<float>( fPWMax, 0, pRadarMode->fPD_TypicalMax, 0 ) == _spFalse );
            if( bCheck == true ) {
                continue;
            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;

    }

    m_toLib = toLib;
}

/**
 * @brief     스캔 식별을 수행한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:22:25
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyScan( ENUM_AET_SCAN_TYPE enScanType, float fScanPeriod, float fThreshold )
{
#ifndef _XBAND_
    UINT i;
    UINT toLib;
    STR_LIB_IDRESULT *pIdxLib;

    toLib = 0;
    pIdxLib = & m_pIdResult[0];

    for( i = 0; i < m_toLib; ++i, ++pIdxLib ) {
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) { //DTEC_NullPointCheck
            continue;
        }

#if defined(_POCKETSONATA_) || defined(_712_)
        switch( m_pLOBData->vScanType ) {
#else
        switch( m_pLOBData->iScanType ) {
#endif

            case ENUM_AET_SCAN_TYPE::E_AET_SCAN_STEADY:
                if( pRadarMode->eScanPrimaryType != ScanType::enumD_Non_Scanning ) {
                    continue;
                }
                break;

            case ENUM_AET_SCAN_TYPE::E_AET_SCAN_UNI_DIRECTIONAL:
                if( pRadarMode->eScanPrimaryType != ScanType::enumU_Uni_Directional_Sector_Plane_Undertermined ) {
                    continue;
                }
                break;

            case ENUM_AET_SCAN_TYPE::E_AET_SCAN_BI_DIRECTIONAL:
                if( pRadarMode->eScanPrimaryType != ScanType::enumV_Bi_Directional_Sector_Plane_Undetermined ) {
                    continue;
                }
                break;

            case ENUM_AET_SCAN_TYPE::E_AET_SCAN_CONICAL:
                if( pRadarMode->eScanPrimaryType != ScanType::enumF_Conical ) {
                    continue;
                }
                break;

            case ENUM_AET_SCAN_TYPE::E_AET_SCAN_CIRCULAR:
                if( pRadarMode->eScanPrimaryType != ScanType::enumA_Circular && \
                    pRadarMode->eScanPrimaryType != ScanType::enumV_Bi_Directional_Sector_Plane_Undetermined && \
                    pRadarMode->eScanPrimaryType != ScanType::enumV_Bi_Directional_Sector_Plane_Undetermined ) {
                    continue;
                }
                break;

            case ENUM_AET_SCAN_TYPE::E_AET_SCAN_SCANFAIL:
            case ENUM_AET_SCAN_TYPE::E_AET_SCAN_UNKNOWN:
                break;

            default:
                break;

        }

        // 범위 안에 평균이 들어가지 않으면 실패
        if( ( enScanType >= ENUM_AET_SCAN_TYPE::E_AET_SCAN_CIRCULAR && enScanType <= ENUM_AET_SCAN_TYPE::E_AET_SCAN_STEADY ) && \
            ( pRadarMode->eScanPrimaryType != ScanType::enumUndefinedScanType ) ) {
            if( TCompMarginDiff<float>( fScanPeriod, pRadarMode->fScanPrimaryTypicalMin, pRadarMode->fScanPrimaryTypicalMax, fThreshold ) == _spFalse ) {
                continue;
            }
        }

        m_pIdResult[toLib++].pIdxRadarMode = pIdxLib->pIdxRadarMode;

    }

    m_toLib = toLib;

#endif

}

// /**
//  * @brief     스캔 형태에 대해서 신호 식별 결과를 알려준다.
//  * @param     ScanType::EnumScanType eScanType
//  * @param     int aetAspiType
//  * @return    bool
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2015-10-21, 오후 10:56
//  * @warning
//  */
// bool CELSignalIdentifyAlg::CheckScanType( ScanType::EnumScanType eScanType, int aetAspiType )
// {
// 	bool bRet=true;
//
// 	if( aetAspiType != E_AET_SCAN_UNKNOWN ) {
// 		if( ( eScanType != ScanType::enumUndefinedScanType ) && ( eScanType != ScanType::enumZ_Undetermined ) ) {
// 			switch( aetAspiType ) {
// 				case E_AET_SCAN_SEARCH :
// 					if( ( eScanType == ScanType::enumF_Conical ) || ( eScanType == ScanType::enumG_Lobe_Switching ) ) {
// 						bRet = false;
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
// 						bRet = false;
// 					}
// 					break;
//
// 				case E_AET_SCAN_SECTOR :
// 					if( ( ( eScanType == ScanType::enumF_Conical ) == true ) || ( ( eScanType == ScanType::enumG_Lobe_Switching ) == true ) ) {
// 						bRet = false;
// 					}
// 					break;
//
// 				default :
// 					break;
// 				}
// 		}
// 		else {
// 			bRet = false;
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
// 	memset( & m_optParameter, 0, sizeof(struct SELIDENTIFICATIONOPTION_PARAMETER) );
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
// 	memset( & m_optParameter, 0, sizeof(struct SELIDENTIFICATIONOPTION_PARAMETER) );
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
// 				sprintf_s( m_H0000, 10, "H000A" );
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
 * @brief     식별된 레이더모드의 플레폼 코드를 리턴한다.
 * @param     int iRadarModeIndex
 * @return    PlatformCode
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:22:48
 * @warning
 */
PlatformCode::EnumPlatformCode CELSignalIdentifyAlg::GetPlatformFromRadarMode( unsigned int uiRadarModeIndex )
{
    SRadarMode *pRadarMode;
    PlatformCode::EnumPlatformCode enPlatform;

    if( uiRadarModeIndex >= 1 && uiRadarModeIndex < MAX_RADARMODE ) {
        pRadarMode = GetRadarMode( uiRadarModeIndex );
        enPlatform = pRadarMode->ePlatform;
    }
    else {
        enPlatform = PlatformCode::enumUnKnown;
    }

    return enPlatform;
}

/**
 * @brief     레이더 모드 인덱스에 해당하는 식별 시간 값을 리턴한다.
 * @param     int iIndex
 * @param     bool bRadarMode
 * @return    double
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-25, 오전 9:41
 * @warning
 */
double CELSignalIdentifyAlg::GetInActivatedTime( unsigned int uiIndex )
{
    SRadarMode *pRadarMode;

    double dInActivatedTime;

    pRadarMode = GetRadarMode( uiIndex );
    if( pRadarMode != NULL ) {
        dInActivatedTime = pRadarMode->iTimeInactivated;
    }
    else {
        dInActivatedTime = ( double ) g_pTheSysConfig->GetEmmgEmitterDeleteTimeSec();
    }

    // 삭제 시간 기준 값이 0 이면 미식별 삭제 시간으로 설정한다.
    if( dInActivatedTime <= 0 ) {
        dInActivatedTime = ( double ) g_pTheSysConfig->GetEmmgEmitterDeleteTimeSec();
    }

    return dInActivatedTime;
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
// 		memcpy( & m_stSystemVar[i_nLinkNo], & i_stData, sizeof(struct SOCSystemVariable) );
// 	}
// 	else { //DTEC_Else
// 		TRACE( _T("시스템 변수에 잘못된 항공기 번호(%d)를 설정했습니다."), i_nLinkNo );
// 	}
// }

/**
 * @brief     식별율을 계산한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:24:27
 * @warning
 */
void CELSignalIdentifyAlg::IdentifyMatchRatio()
{
    UINT i; // , toLib;

    STR_LIB_IDRESULT *pIdxLib;

    // 1. 식별 후보의 일치율 계산
    CalcMatchRatio();

    // 2. 일치율 정렬
    qsort( m_pIdResult, ( size_t ) m_toLib, sizeof( struct STR_LIB_IDRESULT ), incRatioCompare );

    // 3. 일치율 식별
    //toLib = 0;
    pIdxLib = & m_pIdResult[0];
    for( i = 0; i < m_toLib; ++i, ++pIdxLib ) {
        if( ( int ) pIdxLib->uRatio < m_pSEnvironVariable->iMatchRatio ) {
            break;
        }
    }

    m_toLib = i;


}

/**
 * @brief     후보 식별의 모든 식별율을 계산한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2015-01-04 오후 2:15
 * @warning
 */
void CELSignalIdentifyAlg::CalcMatchRatio()
{
    UINT i;

    STR_LIB_IDRESULT *pIdxLib;

    pIdxLib = m_pIdResult;

    for( i = 0; i < m_toLib; ++i ) {
        float fRatio;
        SRadarMode *pRadarMode;

        pRadarMode = pIdxLib->pIdxRadarMode;
        if( pRadarMode == NULL ) {
            printf( "레이더 모드가 존재하지 않습니다." );
            continue;
        }

        // 신호 형태
        fRatio = CalcMatchRatio( _SIG_TYPE_MATCHRATIO_, pRadarMode );

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

        // 스캔 형태값
        fRatio += CalcMatchRatio( _SCANTYPE_MATCHRATIO_, pRadarMode );

        // 스캔 주기
        fRatio += CalcMatchRatio( _SCANPRD_MATCHRATIO_, pRadarMode );

        pIdxLib->uRatio = ( int ) fRatio;
        ++ pIdxLib;

    }

}

/**
 * @brief     주파수 형태에 대한 식별율을 계산한다.
 * @param     SRadarMode * pRadarMode
 * @return    float
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-19, 17:01
 * @warning
 */
float CELSignalIdentifyAlg::CalcFreqTypeMatchRatio( SRadarMode * pRadarMode )
{
    float frate = 0.0;

    switch( m_pLOBData->vFreqType ) {
        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED:
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumFIXED ) {
                frate = _DEFAULT_FREQ_TYPE_RATE;
            }
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE:
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumAGILE ) {
                frate = _DEFAULT_FREQ_TYPE_RATE;
            }
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING:
            // 비주기
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumHOPPING ) {
                frate = _DEFAULT_FREQ_TYPE_RATE;
            }

            // 주기
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumHOPPING ) {
                frate = _DEFAULT_FREQ_TYPE_RATE;
            }
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN:
            if( pRadarMode->eRF_Type == RadarModeFreqType::enumPATTERN ) {
                frate = _DEFAULT_FREQ_TYPE_RATE;
            }
            break;

        default:
            break;

    }

    return frate;
}

/**
 * @brief     PRI 형태에 대한 식별율을 계산한다.
 * @param     SRadarMode * pRadarMode
 * @return    float
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-19, 17:02
 * @warning
 */
float CELSignalIdentifyAlg::CalcPRITypeMatchRatio( SRadarMode * pRadarMode )
{
    float frate = 0.0;

    switch( m_pLOBData->vPRIType ) {
        case ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED:
            if( pRadarMode->ePRI_Type == RadarModePRIType::enumStable ) {
                frate = _DEFAULT_PRI_TYPE_RATE;
            }
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER:
            if( pRadarMode->ePRI_Type == RadarModePRIType::enumSTAGGER ) {
                frate = _DEFAULT_PRI_TYPE_RATE;
            }
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH:
            if( pRadarMode->ePRI_Type == RadarModePRIType::enumDwellSWITCH ) {
                frate = _DEFAULT_PRI_TYPE_RATE;
            }
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN:
            if( pRadarMode->ePRI_Type == RadarModePRIType::enumPATTERN ) {
                frate = _DEFAULT_PRI_TYPE_RATE;
            }
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER:
            if( pRadarMode->ePRI_Type == RadarModePRIType::enumJITTER ) {
                frate = _DEFAULT_PRI_TYPE_RATE;
            }
            break;

        default:
            break;
    }

    return frate;
}

/**
 * @brief     주파수 범위에 대한 식별율을 계산한다.
 * @param     EnumMATCHRATIO enMatchRatio
 * @param     SRadarMode * pRadarMode
 * @return    float
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 13:43
 * @warning
 */
float CELSignalIdentifyAlg::CalcFreqMatchRatio( EnumMATCHRATIO enMatchRatio, SRadarMode * pRadarMode )
{
    float fRate = 0.0;

    if( pRadarMode != NULL ) {
        switch( enMatchRatio ) {
            // 주파수 형태 비교
            case _FREQ_TYPE_MATCHRATIO_:
                fRate = CalcFreqTypeMatchRatio( pRadarMode );
                break;

                // PRI 형태 비교
            case _PRI_TYPE_MATCHRATIO_:
                fRate = CalcPRITypeMatchRatio( pRadarMode );
                break;

                // 주파수 범위 비교
            case _FREQ_RANGE_MATCHRATIO_:
                fRate = ( float ) m_pSEnvironVariable->iWeightFrqRange;
                break;

            case _FREQ_PERIOD_MATCHRATIO_:
                if( m_pLOBData->fFreqPatternPeriod > 0 ) {
                    fRate = ( float ) m_pSEnvironVariable->iWeightFrqModPeriod;
                }
                break;

                // 주파수 포지션 비교
            case _FREQ_POSITION_MATCHRATIO_:
                if( m_pLOBData->vFreqPositionCount > 0 && pRadarMode->nRF_NumPositions > 0 ) {
                    if( m_pLOBData->vFreqPositionCount == pRadarMode->nRF_NumPositions ) {
                        fRate = ( float ) m_pSEnvironVariable->iWeightFrqModElement;
                    }
                    else {
                        fRate = FDIV( m_pSEnvironVariable->iWeightFrqModElement, 2.0 );
                    }
                }
                break;

                //             case _FREQ_MAIN_RANGE_MATCHRATIO_ :
                // // 				pRadarRF_SpotValues = pRadarMode->vecRadarRF_SpotValues.data();
                // // 				for( i=0 ; i < (int) pRadarMode->vecRadarRF_SpotValues.size() ; ++i ) { //#FA_C_PotentialUnboundedLoop_T2
                // // 					if( CompMarginDiffFFF( m_optParameter.freq.fLow , (*pRadarRF_SpotValues).fRF_Min, (*pRadarRF_SpotValues).fRF_Max, m_optParameter.freq.fRangeError ) == true ||
                // // 							CompMarginDiffFFF( m_optParameter.freq.fHigh, (*pRadarRF_SpotValues).fRF_Min, (*pRadarRF_SpotValues).fRF_Max, m_optParameter.freq.fRangeError ) == true ) {
                // // 						frate = (float) m_pSELDBEnvVarIdnf->iWeightFrqMainObservedValue;
                // // 						break;
                // // 					}
                // //
                // // 					++ pRadarRF_SpotValues;
                // // 				}
                //                 break;
            default:
                break;

        }
    }

    return fRate;

}

/**
 * @brief     PRI 범위에 대한 식별율을 계산한다.
 * @param     EnumMATCHRATIO enMatchRatio
 * @param     SRadarMode * pRadarMode
 * @return    float
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 13:45
 * @warning
 */
float CELSignalIdentifyAlg::CalcPRIMatchRatio( EnumMATCHRATIO enMatchRatio, SRadarMode * pRadarMode )
{
    float fRate = 0.0;

    if( pRadarMode != NULL ) {
        switch( enMatchRatio ) {
            // PRI 범위 비교
            case _PRI_RANGE_MATCHRATIO_:
                fRate = ( float ) m_pSEnvironVariable->iWeightPriRange;
                break;

                // PRI 패턴 주기 비교
            case _PRI_PERIOD_MATCHRATIO_:
                if( m_pLOBData->fPRIPatternPeriod > 0 ) {
                    fRate = ( float ) m_pSEnvironVariable->iWeightPriModPeriod;
                }
                break;

                // PRI 포지션 비교
            case _PRI_POSITION_MATCHRATIO_:
                if( m_pLOBData->vPRIPositionCount > 0 && pRadarMode->nPRI_NumPositions > 0 ) {
                    if( m_pLOBData->vPRIPositionCount == pRadarMode->nPRI_NumPositions ) {
                        fRate = ( float ) m_pSEnvironVariable->iWeightPriModPosCount;
                    }
                    else {
                        fRate = FDIV( m_pSEnvironVariable->iWeightPriModPosCount, 2.0 );
                    }
                }
                break;

                // 			case _PRI_MAIN_RANGE_MATCHRATIO_ :
                // 				pRadarPRI_SpotValues = pRadarMode->vecRadarPRI_SpotValues.data();
                // 				for( i=0 ; i < (int) pRadarMode->vecRadarPRI_SpotValues.size() ; ++i ) { //#FA_C_PotentialUnboundedLoop_T2
                // 					if( CompMarginDiffFFF( m_optParameter.pri.fLow , (*pRadarPRI_SpotValues).fPRI_Min, (*pRadarPRI_SpotValues).fPRI_Max, m_optParameter.pri.fRangeError ) == true ||
                // 							CompMarginDiffFFF( m_optParameter.pri.fHigh, (*pRadarPRI_SpotValues).fPRI_Min, (*pRadarPRI_SpotValues).fPRI_Max, m_optParameter.pri.fRangeError ) == true ) {
                // 						frate = (float) m_pSELDBEnvVarIdnf->iWeightPriMainObservedValue;
                // 						break;
                // 					}
                //
                // 					++ pRadarPRI_SpotValues;
                // 				}
                // 				break;

            default:
                break;

        }
    }

    return fRate;
}

/**
 * @brief     각 항목에 따라서 일치율 값을 리턴한다.
 * @param     EnumMATCHRATIO enMatchRatio
 * @param     SRadarMode * pRadarMode
 * @return    float
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-10-21, 오후 1:34
 * @warning
 */
float CELSignalIdentifyAlg::CalcMatchRatio( EnumMATCHRATIO enMatchRatio, SRadarMode * pRadarMode )
{
    float fRate = 0.0;

    //vector<SRadarRF_SpotValues>::pointer pRadarRF_SpotValues;
    //vector<SRadarPRI_SpotValues>::pointer pRadarPRI_SpotValues;

    if( pRadarMode != NULL ) {
        switch( enMatchRatio ) {
            // 신호 형태 비교
            case _SIG_TYPE_MATCHRATIO_:
                fRate = _DEFAULT_SIGNAL_TYPE_RATE;
                break;

                // 펄스폭 범위
            case _PW_MATCHRATIO_:
                if( is_not_zero<float>( pRadarMode->fPD_TypicalMin ) == true && is_not_zero<float>( pRadarMode->fPD_TypicalMax ) == true ) {
                    if( TCompMarginDiff<float>( m_pLOBData->fPWMean, pRadarMode->fPD_TypicalMin, pRadarMode->fPD_TypicalMax, 0 ) == _spTrue ) {
                        fRate = ( float ) _DEFAULT_PW_RANGE_RATE;
                    }
                }
                break;

                // 스캔 형태 및 주기
            case _SCANTYPE_MATCHRATIO_:
                fRate = _DEFAULT_SCAN_TYPE_RATE;
                break;

            case _SCANPRD_MATCHRATIO_:
                fRate = _DEFAULT_SCAN_TYPE_RATE;
                break;

            default:
                break;
        }
    }

    fRate += CalcFreqMatchRatio( enMatchRatio, pRadarMode );
    fRate += CalcPRIMatchRatio( enMatchRatio, pRadarMode );

    return fRate;
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
// 	if( m_IdAet.aet.ucSignalType == SignalType::enumPulsed ) {
// 		// 1st Position 기록하기
// 		switch( ftype ) {
// 		case ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED :
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
// 		case ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE :
// 			*pModeCode = 'O';
// 			break;
//
// 		case ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN :
// 			if( m_IdAet.aet.Frequency.patType == UNK ) {
// 				*pModeCode = 'N';
// 			}
// 			else {
// 				*pModeCode = 'U';
// 			}
// 			break;
//
// 		case ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING :
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
// 		case ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED :
// 			*pModeCode = 'D';
// 			break;
//
// 		case ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH :
// 			*pModeCode = 'S';
// 			break;
//
// 		case ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER :
// 			*pModeCode = 'M';
// 			break;
//
// 		case ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER :
// 			*pModeCode = 'C';
// 			break;
//
// 		case ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN :
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
bool CELSignalIdentifyAlg::IsSortELNOT( SRadarMode * pRadarModeRef, SRadarMode * pRadarModeNxt )
{
    bool bRet;

	int iCmp = strcmp( pRadarModeRef->szELNOT, pRadarModeNxt->szELNOT );

	if( iCmp < 0 ) {
		bRet = false;
	}
    else {
        bRet = true;
    }

    return bRet;
}

/**
 * @brief     레이더모드명을 리턴한다.
 * @param     int iRadarModeIndex
 * @return    char *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2019/04/25 14:55
 * @warning
 */
char *CELSignalIdentifyAlg::GetRadarModeName( unsigned int uiRadarModeIndex )
{
    SRadarMode *pRadarMode;
    char *pszRadarModeName = NULL;

    pRadarMode = GetRadarMode( uiRadarModeIndex );

    //     for( auto &stRadarMode : m_vecRadarMode ) {
    //         if( stRadarMode.uiRadarModeIndex == uiRadarModeIndex ) {
    //             pRadarName = stRadarMode.szRadarModeName;
    //             break;
    //         }
    //     }

    if( pRadarMode != NULL ) {
        pszRadarModeName = pRadarMode->szRadarModeName;
    }
    else {

    }

    return pszRadarModeName;

}

/**
 * @brief     위협 라이브러리에서 주파수 최소/최대 범위에 겹친 위협을 찾아서 벡터에 넣는다.
 * @param     vector<SRadarMode * > * pVecMatchRadarMode
 * @param     UINT uiFreqMin
 * @param     UINT uiFreqMax
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-30, 17:49
 * @warning
 */
bool CELSignalIdentifyAlg::CheckThereFreqRange( vector<SRadarMode *> *pVecMatchRadarMode, UINT uiFreqMin, UINT uiFreqMax )
{
    UINT i, j;
    bool bRet = false;
    STR_FLOWHIGH band = STR_FLOWHIGH();

    STR_FLIB *pFLib;

    SRadarMode **ppRadarMode;

    pVecMatchRadarMode->clear();

    band.ilow = ( int ) BandSelect( 0, ( UINT ) NO_FLIB_BAND - 1, ( int ) F_UDIV( uiFreqMin, FLIB_FREQ_RES_MHZ ) );
    band.ihgh = ( int ) BandSelect( 0, ( UINT ) NO_FLIB_BAND - 1, ( int ) F_UDIV( uiFreqMax, FLIB_FREQ_RES_MHZ ) );

    pFLib = & m_pFLib[band.ilow];
    for( i = ( UINT ) band.ilow; i <= ( UINT ) band.ihgh; ++i ) {
        ppRadarMode = & pFLib->pIdxRadarMode[0];
        for( j = 0; j < pFLib->uicount; ++ j ) {
            if( ( *ppRadarMode )->eRF_Type != RadarModeFreqType::enumFreqUnknown && ( *ppRadarMode )->ePRI_Type != RadarModePRIType::enumPRIUnknown &&
                TCalOverlapSpace<float>( ( float ) uiFreqMin, ( float ) uiFreqMax, ( *ppRadarMode )->fRF_TypicalMin, ( *ppRadarMode )->fRF_TypicalMax ) > 0 ) {
                pVecMatchRadarMode->push_back( *ppRadarMode );

                bRet = true;
            }
            ++ ppRadarMode;
        }

        sort( pVecMatchRadarMode->begin(), pVecMatchRadarMode->end() );
        pVecMatchRadarMode->erase( unique( pVecMatchRadarMode->begin(), pVecMatchRadarMode->end() ), pVecMatchRadarMode->end() );

        ++ pFLib;
    }

    return bRet;

}

/**
 * @brief     레이더모드 데이터를 테이블로부터 로딩한다.
 * @param     int * pnRadarMode
 * @param     SRadarMode * pRadarMode
 * @param     int iMaxItems
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:27:33
 * @warning
 */
bool CELSignalIdentifyAlg::LoadRadarModeData( unsigned int *pnRadarMode )
{

    *pnRadarMode = 0;

    m_vecRadarMode.clear();

#ifdef _SQLITE_
    bool bRet = true;

#ifdef _XBAND_
    sprintf( m_szSQLString, "SELECT RM_RADAR_MODE_INDEX, RM_FUNCTION_CODE, RM_SIGNAL_TYPE, RM_POLARIZATION, RM_PLATFORM, RM_VALIDATION, \
                             RM_RF_TYPE, RM_RF_TYPICAL_MIN, RM_RF_TYPICAL_MAX, RM_RF_PATTERN, RM_RF_NUM_ELEMENTS, RM_RF_NUM_POSITIONS, RM_RF_PATTERN_PERIOD_MIN, RM_RF_PATTERN_PERIOD_MAX, RM_RF_MEAN_MIN, RM_RF_MEAN_MAX, \
                             RM_PRI_TYPE, RM_PRI_TYPICAL_MIN, RM_PRI_TYPICAL_MAX, RM_PRI_PATTERN, RM_PRI_NUM_ELEMENTS, RM_PRI_NUM_POSITIONS, RM_PRI_PATTERN_PERIOD_MIN, RM_PRI_PATTERN_PERIOD_MAX, RM_PRI_MEAN_MIN, RM_PRI_MEAN_MAX, \
                             RM_PD_TYPICAL_MIN, RM_PD_TYPICAL_MAX, \
                             RM_SCAN_PRIMARY_TYPE, RM_SCAN_PRIMARY_TYPICAL_MIN, RM_SCAN_PRIMARY_TYPICAL_MAX, RM_SCAN_SECONDARY_TYPE, RM_SCAN_SECONDARY_TYPICAL_MIN, RM_SCAN_SECONDARY_TYPICAL_MAX, RM_MODULATION_CODE, RM_PRIORITY, \
                             RML_RADAR_INDEX, RML_RADAR_MODE_NAME, RML_MODE_CODE, \
                             R_PRIORITY, R_ELNOT, R_NICKNAME, R_TIME_INACTIVATED, \
                             D_THREAT_INDEX, D_DEVICE_INDEX, D_ELNOT \
                             FROM VEL_RADARMODE_LIST ORDER BY RM_RADAR_MODE_INDEX" );

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.Sql( m_szSQLString );

        while( stmt.FetchRow() ) {
            int iValue;
            //char buffer[100];
            const char *p;

            i = 0;

            pRadarMode->uiRadarModeIndex = stmt.GetColumnInt( i++ );

            p = stmt.GetColumnName( i++ );
            pRadarMode->eFunctionCode = GetFunctionCodes( p );

            p = ( char * ) stmt.GetColumnName( i++ );
            pRadarMode->eSignalType = GetSignalType( p );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->ePolarization = GetPolarizationCodes( iValue );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->ePlatform = GetPlatformCode( iValue );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->eValidation = GetValidationCode( iValue );

            // 주파수 정보
            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->eRF_Type = GetFreqType( iValue );

            pRadarMode->fRF_TypicalMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fRF_TypicalMax = ( float ) stmt.GetColumnDouble( i++ );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->eRF_Pattern = GetPatternCode( iValue );

            pRadarMode->nRF_NumElements = stmt.GetColumnInt( i++ );
            pRadarMode->nRF_NumPositions = stmt.GetColumnInt( i++ );

            pRadarMode->fRF_PatternPeriodMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fRF_PatternPeriodMax = ( float ) stmt.GetColumnDouble( i++ );

            pRadarMode->fRF_MeanMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fRF_MeanMax = ( float ) stmt.GetColumnDouble( i++ );

            // PRI 정보
            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->ePRI_Type = GetPRIType( iValue );

            pRadarMode->fPRI_TypicalMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fPRI_TypicalMax = ( float ) stmt.GetColumnDouble( i++ );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->ePRI_Pattern = GetPatternCode( iValue );

            pRadarMode->nPRI_NumElements = stmt.GetColumnInt( i++ );
            pRadarMode->nPRI_NumPositions = stmt.GetColumnInt( i++ );

            pRadarMode->fPRI_PatternPeriodMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fPRI_PatternPeriodMax = ( float ) stmt.GetColumnDouble( i++ );

            pRadarMode->fPRI_MeanMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fPRI_MeanMax = ( float ) stmt.GetColumnDouble( i++ );

            // 펄스폭 정보
            pRadarMode->fPD_TypicalMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fPD_TypicalMax = ( float ) stmt.GetColumnDouble( i++ );

            // 스캔 정보
            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->eScanPrimaryType = GetScanType( iValue );
            pRadarMode->fScanPrimaryTypicalMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fScanPrimaryTypicalMax = ( float ) stmt.GetColumnDouble( i++ );

            iValue = stmt.GetColumnInt( i++ );
            pRadarMode->eScanSecondaryType = GetScanType( iValue );
            pRadarMode->fScanSecondaryTypicalMin = ( float ) stmt.GetColumnDouble( i++ );
            pRadarMode->fScanSecondaryTypicalMax = ( float ) stmt.GetColumnDouble( i++ );

            // 기타 정보
            //pRadarMode->nAssocIndex	= query.getColumn(i++).getInt();													//모드 간 연관관계에 대한 링크

            p = ( char * ) stmt.GetColumnCString( i++ );
            if( p != NULL ) {
                strcpy( pRadarMode->szModulationCode, p );
            }
            else {
                pRadarMode->szModulationCode[0] = 0;
            }

            pRadarMode->uiRadarModePriority = stmt.GetColumnInt( i++ );

            // 레이더 정보
            pRadarMode->uiRadarIndex = stmt.GetColumnInt( i++ );
            //strcpy( pRadarMode->szRadarModeName, stmt.GetColumnName(i++) );
            p = ( char * ) stmt.GetColumnCString( i++ );
            if( p != NULL ) {
                strcpy( pRadarMode->szRadarModeName, p );
            }
            else {
                pRadarMode->szRadarModeName[0] = 0;
            }

            //strcpy( pRadarMode->szModeCode, stmt.GetColumnName(i++) );
            p = ( char * ) stmt.GetColumnCString( i++ );
            if( p != NULL ) {
                strcpy( pRadarMode->szModeCode, p );
            }
            else {
                pRadarMode->szModeCode[0] = 0;
            }

            pRadarMode->iRadarPriority = stmt.GetColumnInt( i++ );
            //strcpy( pRadarMode->szELNOT, stmt.GetColumnName(i++) );
            p = ( char * ) stmt.GetColumnCString( i++ );
            if( p != NULL ) {
                strcpy( pRadarMode->szELNOT, p );
            }
            else {
                pRadarMode->szELNOT[0] = 0;
            }

            //strcpy( pRadarMode->szNickName, stmt.GetColumnName(i++) );
            p = ( char * ) stmt.GetColumnCString( i++ );
            if( p != NULL ) {
                strcpy( pRadarMode->szNickName, p );
            }
            else {
                pRadarMode->szNickName[0] = 0;
            }

            pRadarMode->iTimeInactivated = stmt.GetColumnInt( i++ );

            pRadarMode->iThreatIndex = stmt.GetColumnInt( i++ );
            pRadarMode->iDeviceIndex = stmt.GetColumnInt( i++ );

            if( pRadarMode->eValidation == enumValidated ) {
                ++ *pnRadarMode;
                ++ pRadarMode;
            }

        }

        // do not forget to clean-up
        stmt.FreeQuery();

    }

#elif defined(_POCKETSONATA_) || defined(_712_)
    //sprintf(m_szSQLString, "SELECT * FROM VEL_RADARMODE_LIST ORDER BY RADARMODE_INDEX ASC;" );
    // 뷰 테이블에서 정렬 적용함.
    sprintf( m_szSQLString, "SELECT RADAR_INDEX, RADARMODE_INDEX, RADAR_PRIORITY, RADAR_ELNOT, NICK_NAME, \
            TIME_INACTIVATED, SIGNAL_TYPE, RF_TYPE, RF_RANGE_MIN, RF_RANGE_MAX, RF_PATTERN, RF_NUM_ELEMENTS, \
            RF_NUM_POSITIONS, RF_PATTERN_PERIOD_MIN, RF_PATTERN_PERIOD_MAX, RF_MEAN_MIN, RF_MEAN_MAX, \
            PRI_TYPE, PRI_RANGE_MIN, PRI_RANGE_MAX, PRI_PATTERN, PRI_NUM_ELEMENTS, PRI_NUM_POSITIONS, \
            PRI_PATTERN_PERIOD_MIN, PRI_PATTERN_PERIOD_MAX, PRI_MEAN_MIN, PRI_MEAN_MAX, PD_RANGE_MIN, \
            PD_RANGE_MAX, SCAN_PRIMARY_TYPE, SCAN_PRIMARY_RANGE_MIN, SCAN_PRIMARY_RANGE_MAX, \
            SCAN_SECONDARY_TYPE, SCAN_SECONDARY_RANGE_MIN, SCAN_SECONDARY_RANGE_MAX, MODULATION_CODE, \
            PRIORITY, VALIDATION, RADARMODE_NAME, MODECODE, CATEGORY FROM VEL_RADARMODE_LIST;" );

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.Sql( m_szSQLString );

        //int iPrevTimeInactivatedOfRadar=-1;
        //char szPrevELNOT[_MAX_ELNOT_STRING_SIZE_];

        //szPrevELNOT[0] = NULL;
        while( stmt.FetchRow() ) {
            SRadarMode stRadarMode;

            GetRadarModeFromStatement( & stRadarMode, &stmt );

            // 예외 처리
// 			if (strcmp(szPrevELNOT, stRadarMode.szELNOT) != 0) {
//                 stRadarMode.iTimeInactivatedOfRadar = stRadarMode.iTimeInactivated;
// 			}
// 			else {
//                 stRadarMode.iTimeInactivatedOfRadar = max( stRadarMode.iTimeInactivated, iPrevTimeInactivatedOfRadar);
// 			}


            if( stRadarMode.eValidation == enumValidated ) {
                //strcpy(szPrevELNOT, stRadarMode.szELNOT);
                //iPrevTimeInactivatedOfRadar = stRadarMode.iTimeInactivatedOfRadar;

                ++ *pnRadarMode;

#ifdef __VXWORKS__
                m_vecRadarMode.push_back( stRadarMode );
#else
                m_vecRadarMode.emplace_back( stRadarMode );
#endif

            }

        }

        // do not forget to clean-up
        stmt.FreeQuery();

    }

#endif
    catch( Kompex::SQLiteException &sException ) {
        bRet = false;
        //std::cerr << "\nException Occured" << std::endl;
        //sException.Show();
        //std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
        Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );

        KOMPEX_O_EXCEPT( "레이더 모드가 잘못 됐거나 쿼리문이 잘못 됐습니다 !", -1 );
    }

    return bRet;

#elif defined(_MSSQL_)
    DECLARE_BEGIN_CHECKODBC

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    //sprintf_s( m_szSQLString, MAX_SQL_SIZE,  "SELECT * FROM RADARMODE WHERE VALIDATION = '1' ORDER BY RADARMODE_INDEX" );
    sprintf_s( m_szSQLString, MAX_SQL_SIZE, "SELECT * FROM VEL_RADARMODE_LIST ORDER BY RADAR_INDEX ASC, RADARMODE_INDEX ASC;" );

    theRS.Open( m_szSQLString );

    while( !theRS.IsEof() ) {
        SRadarMode stRadarMode;

        GetRadarModeFromStatement( & stRadarMode, &theRS );

        if( stRadarMode.eValidation == enumValidated ) {
            ++ *pnRadarMode;

#ifdef __VXWORKS__
            m_vecRadarMode.push_back( stRadarMode );
#else
            m_vecRadarMode.emplace_back( stRadarMode );
#endif
        }

        theRS.MoveNext();
    }

    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN

#else

    return true;

#endif

}

#ifdef _SQLITE_
/**
 * @brief     GetRadarModeFromStatement
 * @param     SRadarMode * pRadarMode
 * @param     Kompex::SQLiteStatement * pStatment
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 10:04:32
 * @warning
 */
void CELSignalIdentifyAlg::GetRadarModeFromStatement( SRadarMode * pRadarMode, Kompex::SQLiteStatement * pStatment )
{
    int i = 0;
    int iValue;

#ifdef _MSC_VER
    const wchar_t *p;
#else
    const unsigned char *p;
#endif

    // 레이더 정보
    // 레이더 인덱스
    pRadarMode->uiRadarIndex = ( unsigned int ) pStatment->GetColumnInt( i++ );

    // 레이더 모드 인덱스
    pRadarMode->uiRadarModeIndex = ( unsigned int ) pStatment->GetColumnInt( i++ );

    // 레이더 우선순위
    pRadarMode->uiRadarPriority = ( unsigned int ) pStatment->GetColumnInt( i++ );

#ifdef _MSC_VER
    p = pStatment->GetColumnCString16( i++ );
    UTF8ToMultibyte( pRadarMode->szELNOT, sizeof( pRadarMode->szELNOT ), p );

    p = pStatment->GetColumnCString16( i++ );
    UTF8ToMultibyte( pRadarMode->szNickName, sizeof( pRadarMode->szNickName ), p );

#else
    p = pStatment->GetColumnCString( i++ );
    if( p != NULL ) {
        strcpy( pRadarMode->szELNOT, ( char * ) p );
    }
    else {
#ifdef __VXWORKS__
        pRadarMode->szELNOT[0] = ( char ) 0;
#else
        pRadarMode->szELNOT[0] = NULL;
#endif
    }

    p = pStatment->GetColumnCString( i++ );
    if( p != NULL ) {
        strcpy( pRadarMode->szNickName, ( char * ) p );
    }
    else {
#ifdef __VXWORKS__
        pRadarMode->szNickName[0] = ( char ) 0;
#else
        pRadarMode->szNickName[0] = NULL;
#endif
    }

#endif

    pRadarMode->iTimeInactivated = pStatment->GetColumnInt( i++ );

    pRadarMode->eSignalType = ( CEDSignalType::EnumSignalType ) pStatment->GetColumnInt( i++ );

    // 주파수 정보
    iValue = pStatment->GetColumnInt( i++ );
    pRadarMode->eRF_Type = GetFreqType( iValue );

    pRadarMode->fRF_TypicalMin = ( float ) pStatment->GetColumnDouble( i++ );
    pRadarMode->fRF_TypicalMax = ( float ) pStatment->GetColumnDouble( i++ );

    iValue = pStatment->GetColumnInt( i++ );
    pRadarMode->eRF_Pattern = GetPatternCode( iValue );

    pRadarMode->nRF_NumElements = pStatment->GetColumnInt( i++ );
    pRadarMode->nRF_NumPositions = pStatment->GetColumnInt( i++ );

    pRadarMode->fRF_PatternPeriodMin = ( float ) pStatment->GetColumnDouble( i++ );
    pRadarMode->fRF_PatternPeriodMax = ( float ) pStatment->GetColumnDouble( i++ );

    pRadarMode->fRF_MeanMin = ( float ) pStatment->GetColumnDouble( i++ );
    pRadarMode->fRF_MeanMax = ( float ) pStatment->GetColumnDouble( i++ );

    // PRI 정보
    iValue = pStatment->GetColumnInt( i++ );
    pRadarMode->ePRI_Type = GetPRIType( iValue );

    pRadarMode->fPRI_TypicalMin = ( float ) pStatment->GetColumnDouble( i++ );
    pRadarMode->fPRI_TypicalMax = ( float ) pStatment->GetColumnDouble( i++ );

    iValue = pStatment->GetColumnInt( i++ );
    pRadarMode->ePRI_Pattern = GetPatternCode( iValue );

    pRadarMode->nPRI_NumElements = pStatment->GetColumnInt( i++ );
    pRadarMode->nPRI_NumPositions = pStatment->GetColumnInt( i++ );

    pRadarMode->fPRI_PatternPeriodMin = ( float ) pStatment->GetColumnDouble( i++ );
    pRadarMode->fPRI_PatternPeriodMax = ( float ) pStatment->GetColumnDouble( i++ );

    pRadarMode->fPRI_MeanMin = ( float ) pStatment->GetColumnDouble( i++ );
    pRadarMode->fPRI_MeanMax = ( float ) pStatment->GetColumnDouble( i++ );

    // 펄스폭 정보
    pRadarMode->fPD_TypicalMin = ( float ) pStatment->GetColumnDouble( i++ );
    pRadarMode->fPD_TypicalMax = ( float ) pStatment->GetColumnDouble( i++ );

    // 스캔 정보
    iValue = pStatment->GetColumnInt( i++ );
    pRadarMode->eScanPrimaryType = GetScanType( iValue );
    pRadarMode->fScanPrimaryTypicalMin = ( float ) pStatment->GetColumnDouble( i++ );
    pRadarMode->fScanPrimaryTypicalMax = ( float ) pStatment->GetColumnDouble( i++ );

    iValue = pStatment->GetColumnInt( i++ );
    pRadarMode->eScanSecondaryType = GetScanType( iValue );
    pRadarMode->fScanSecondaryTypicalMin = ( float ) pStatment->GetColumnDouble( i++ );
    pRadarMode->fScanSecondaryTypicalMax = ( float ) pStatment->GetColumnDouble( i++ );

#ifdef _MSC_VER
    p = pStatment->GetColumnCString16( i++ );
    UTF8ToMultibyte( pRadarMode->szModulationCode, sizeof( pRadarMode->szModulationCode ), p );
#else
    p = pStatment->GetColumnCString( i++ );
    if( p != NULL ) {
        strcpy( pRadarMode->szModulationCode, ( char * ) p );
    }
    else {
#ifdef __VXWORKS__
        pRadarMode->szModulationCode[0] = ( char ) 0;
#else
        pRadarMode->szModulationCode[0] = NULL;
#endif

    }
#endif

    pRadarMode->uiRadarModePriority = ( unsigned int ) pStatment->GetColumnInt( i++ );

    // View 테이블에서 '1' 만 갖고 오는 것이기에 읽어도 1 입니다.
    pRadarMode->eValidation = ( EnumValidationCode ) pStatment->GetColumnInt( i++ );

    ///////////////////////////////////////////////////////////////////////////////////


    // 한글 입력일떄 아래 함수로 인자를 더 두어서 호출
#ifdef _MSC_VER
    p = pStatment->GetColumnCString16( i++ );
    UTF8ToMultibyte( pRadarMode->szRadarModeName, sizeof( pRadarMode->szRadarModeName ), p );
#else
    p = pStatment->GetColumnCString( i++ );
    if( p != NULL ) {
        strcpy( pRadarMode->szRadarModeName, ( char * ) p );
    }
    else {
#ifdef __VXWORKS__
        pRadarMode->szRadarModeName[0] = ( char ) 0;
#else
        pRadarMode->szRadarModeName[0] = NULL;
#endif

    }
#endif

#ifdef _MSC_VER
    p = pStatment->GetColumnCString16( i++ );
    UTF8ToMultibyte( pRadarMode->szModeCode, sizeof( pRadarMode->szModeCode ), p );
#else
    p = pStatment->GetColumnCString( i++ );
    if( p != NULL ) {
        strcpy( pRadarMode->szModeCode, ( char * ) p );
    }
    else {
#ifdef __VXWORKS__
        pRadarMode->szModeCode[0] = ( char ) 0;
#else
        pRadarMode->szModeCode[0] = NULL;
#endif

    }
#endif

    pRadarMode->iCategory = pStatment->GetColumnInt( i++ );

}

/**
 * @brief     GetColumnString
 * @param     char * pszString
 * @param     Kompex::SQLiteStatement * pStatment
 * @param     int iColumn
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-24 16:11:59
 * @warning
 */
void CELSignalIdentifyAlg::GetColumnString( char *pszString, size_t szSize, Kompex::SQLiteStatement * pStatment, int iColumn )
{
#ifdef _MSC_VER
    const wchar_t *p;

    p = pStatment->GetColumnCString16( iColumn );
    UTF8ToMultibyte( pszString, szSize, p );

#else
    const unsigned char *p;

    p = pStatment->GetColumnCString( iColumn );
    if( p != NULL ) {
        strcpy( pszString, ( char * ) p );
    }
    else {
#ifdef __VXWORKS__
        pszString[0] = ( char ) 0;
#else
        pszString[0] = NULL;
#endif
    }

#endif

}

/**
 * @brief     GetThreatFromStatement
 * @param     SThreat * pThreat
 * @param     Kompex::SQLiteStatement * pStatment
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-24 15:53:46
 * @warning
 */
void CELSignalIdentifyAlg::GetThreatFromStatement( SThreat * pThreat, Kompex::SQLiteStatement * pStatment )
{
    int i = 0;
    //int iValue;

#ifdef _MSC_VER
    //const wchar_t *p;
#else
    //const unsigned char *p;
#endif

    // 위협 정보
    // 위협 인덱스
    pThreat->uiThreatIndex = ( unsigned int ) pStatment->GetColumnInt( i++ );
    // 장비 인덱스
    pThreat->uiDeviceIndex = ( unsigned int ) pStatment->GetColumnInt( i++ );
    // 위협명
    GetColumnString( pThreat->szThreatName, sizeof( pThreat->szThreatName ), pStatment, i++ );
    // 장비명
    GetColumnString( pThreat->szDeviceName, sizeof( pThreat->szDeviceName ), pStatment, i++ );
    // ELNOT
    GetColumnString( pThreat->szELNOT, sizeof( pThreat->szELNOT ), pStatment, i++ );
    // 싸이트명
    GetColumnString( pThreat->szSiteName, sizeof( pThreat->szSiteName ), pStatment, i++ );
    // PIN 번호
    pThreat->uiPinNum = ( unsigned int ) pStatment->GetColumnInt( i++ );
    // 한국지명
    GetColumnString( pThreat->szPlaceNameKor, sizeof( pThreat->szPlaceNameKor ), pStatment, i++ );
    // 적아
    pThreat->eFriendOrFOE = ( FriendOrFOE::EnumFriendOrFOE ) pStatment->GetColumnInt( i++ );
    // 우선순위
    pThreat->uiPriority = ( unsigned int ) pStatment->GetColumnInt( i++ );
    // 카테고리
    pThreat->iCategory = pStatment->GetColumnInt( i++ );
    // 플레폼 형태
    pThreat->enPlatform = ( ENUM_THREAT_PLATFORM ) pStatment->GetColumnInt( i++ );
    // 심벌 코드
    GetColumnString( pThreat->szSymbolCode, sizeof( pThreat->szSymbolCode ), pStatment, i++ );
    // 식별 반경
    pThreat->fIdentificationRange = ( float ) pStatment->GetColumnDouble( i++ );
    // 위도
    pThreat->fLatitude = ( float ) pStatment->GetColumnDouble( i++ );
    // 경도
    pThreat->fLongitude = ( float ) pStatment->GetColumnDouble( i++ );
    // 고도
    pThreat->fElevation = ( float ) pStatment->GetColumnDouble( i++ );

}

#elif defined(_MSSQL_)

/**
 * @brief     GetRadarModeFromStatement
 * @param     SRadarMode * pRadarMode
 * @param     CODBCRecordset * ptheRS
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-02 16:48:37
 * @warning
 */
void CELSignalIdentifyAlg::GetRadarModeFromStatement( SRadarMode * pRadarMode, CODBCRecordset * ptheRS )
{
    short i = 0;
    int iValue;

    // 레이더 정보
    // 레이더 인덱스
    ptheRS->GetFieldValue( i++, & pRadarMode->uiRadarIndex );

    // 레이더 모드 인덱스
    ptheRS->GetFieldValue( i++, & pRadarMode->uiRadarModeIndex );

    // 레이더 우선순위
    ptheRS->GetFieldValue( i++, & pRadarMode->uiRadarPriority );

    ptheRS->GetFieldValue( i++, pRadarMode->szELNOT );

    ptheRS->GetFieldValue( i++, pRadarMode->szNickName );

    ptheRS->GetFieldValue( i++, & pRadarMode->iTimeInactivated );

    ptheRS->GetFieldValue( i++, ( int * ) & pRadarMode->eSignalType );

    // 주파수 정보
    ptheRS->GetFieldValue( i++, & iValue );
    pRadarMode->eRF_Type = GetFreqType( iValue );

    ptheRS->GetFieldValue( i++, & pRadarMode->fRF_TypicalMin );
    ptheRS->GetFieldValue( i++, & pRadarMode->fRF_TypicalMax );

    ptheRS->GetFieldValue( i++, & iValue );
    pRadarMode->eRF_Pattern = GetPatternCode( iValue );

    ptheRS->GetFieldValue( i++, & pRadarMode->nRF_NumElements );
    ptheRS->GetFieldValue( i++, & pRadarMode->nRF_NumPositions );

    ptheRS->GetFieldValue( i++, & pRadarMode->fRF_PatternPeriodMin );
    ptheRS->GetFieldValue( i++, & pRadarMode->fRF_PatternPeriodMax );

    ptheRS->GetFieldValue( i++, & pRadarMode->fRF_MeanMin );
    ptheRS->GetFieldValue( i++, & pRadarMode->fRF_MeanMax );

    // PRI 정보
    ptheRS->GetFieldValue( i++, & iValue );
    pRadarMode->ePRI_Type = GetPRIType( iValue );

    ptheRS->GetFieldValue( i++, & pRadarMode->fPRI_TypicalMin );
    ptheRS->GetFieldValue( i++, & pRadarMode->fPRI_TypicalMax );

    ptheRS->GetFieldValue( i++, & iValue );
    pRadarMode->ePRI_Pattern = GetPatternCode( iValue );

    ptheRS->GetFieldValue( i++, & pRadarMode->nPRI_NumElements );
    ptheRS->GetFieldValue( i++, & pRadarMode->nPRI_NumPositions );

    ptheRS->GetFieldValue( i++, & pRadarMode->fPRI_PatternPeriodMin );
    ptheRS->GetFieldValue( i++, & pRadarMode->fPRI_PatternPeriodMax );

    ptheRS->GetFieldValue( i++, & pRadarMode->fPRI_MeanMin );
    ptheRS->GetFieldValue( i++, & pRadarMode->fPRI_MeanMax );

    // 펄스폭 정보
    ptheRS->GetFieldValue( i++, & pRadarMode->fPD_TypicalMin );
    ptheRS->GetFieldValue( i++, & pRadarMode->fPD_TypicalMax );

    // 스캔 정보
    ptheRS->GetFieldValue( i++, & iValue );
    pRadarMode->eScanPrimaryType = GetScanType( iValue );
    ptheRS->GetFieldValue( i++, & pRadarMode->fScanPrimaryTypicalMin );
    ptheRS->GetFieldValue( i++, & pRadarMode->fScanPrimaryTypicalMax );

    ptheRS->GetFieldValue( i++, & iValue );
    pRadarMode->eScanSecondaryType = GetScanType( iValue );
    ptheRS->GetFieldValue( i++, & pRadarMode->fScanSecondaryTypicalMin );
    ptheRS->GetFieldValue( i++, & pRadarMode->fScanSecondaryTypicalMax );

    ptheRS->GetFieldValue( i++, pRadarMode->szModulationCode );

    ptheRS->GetFieldValue( i++, & pRadarMode->uiRadarModePriority );

    // View 테이블에서 '1' 만 갖고 오는 것이기에 읽어도 1 입니다.
    ptheRS->GetFieldValue( i++, ( int * ) & pRadarMode->eValidation );

    ///////////////////////////////////////////////////////////////////////////////////


    // 한글 입력일떄 아래 함수로 인자를 더 두어서 호출
    ptheRS->GetFieldValue( i++, pRadarMode->szRadarModeName );

    ptheRS->GetFieldValue( i++, pRadarMode->szRadarModeName );

}

#else

#endif

/**
 * @brief     레이더모드의 주파수 SPOT 데이터를 로딩한다.
 * @param     vector<SRadarMode_Spot_Values> * pVecRadarMode_RFSpot
 * @param     int nMaxRadarMode
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-10 11:30:10
 * @warning
 */
bool CELSignalIdentifyAlg::LoadRadarMode_RFSpot( vector<SRadarMode_Spot_Values> *pVecRadarMode_RFSpot, unsigned int uiMaxRadarMode )
{

#ifdef _SQLITE_
    bool bRet = true;
    SRadarMode_Spot_Values stRadarMode_RFSpot_Values;

    int i;

    // 뷰 테이블에서 정렬 적용함.
    sprintf( m_szSQLString, "SELECT RADARMODE_INDEX, RF_MIN, RF_MAX FROM RADAR_RF_SPOT_VALUES ORDER BY RADARMODE_INDEX" );

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.Sql( m_szSQLString );

        pVecRadarMode_RFSpot->clear();

        while( stmt.FetchRow() ) {
            i = 0;

            stRadarMode_RFSpot_Values.iRadarModeIndex = stmt.GetColumnInt( i++ );

            stRadarMode_RFSpot_Values.f_Min = ( float ) stmt.GetColumnDouble( i++ );
            stRadarMode_RFSpot_Values.f_Max = ( float ) stmt.GetColumnDouble( i++ );

            pVecRadarMode_RFSpot->push_back( stRadarMode_RFSpot_Values );
        }

        // do not forget to clean-up
        stmt.FreeQuery();

    }
    catch( Kompex::SQLiteException &sException ) {
        bRet = false;
        //std::cerr << "\nException Occured" << std::endl;
        //sException.Show();
        //std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
        Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );

        KOMPEX_O_EXCEPT( "레이더 모드가 잘못 됐거나 쿼리문이 잘못 됐습니다 !", -1 );
    }

    return bRet;

#elif _MSSQL_
    DECLARE_BEGIN_CHECKODBC
    short i;
    SRadarMode_Spot_Values stRadarMode_RFSpot_Values;

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    sprintf_s( m_szSQLString, MAX_SQL_SIZE, "SELECT RADARMODE_INDEX, RF_MIN, RF_MAX FROM RADAR_RF_SPOT_VALUES ORDER BY RADARMODE_INDEX ASC" );
    theRS.Open( m_szSQLString );

    pVecRadarMode_RFSpot->reserve( nMaxRadarMode * MAX_FREQ_PRI_STEP );
    pVecRadarMode_RFSpot->clear();
    //DeletePointers( *pVecRadarMode_RFSequence );

    while( !theRS.IsEof() ) {
        i = 0;

        theRS.GetFieldValue( i++, &stRadarMode_RFSpot_Values.iRadarModeIndex );

        theRS.GetFieldValue( i++, &stRadarMode_RFSpot_Values.f_Min );
        theRS.GetFieldValue( i++, &stRadarMode_RFSpot_Values.f_Max );

        pVecRadarMode_RFSpot->push_back( stRadarMode_RFSpot_Values );

        theRS.MoveNext();

    }

    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN
#else
    return true;

#endif

}

/**
 * @brief     레이더모드의 PRI SPOT 데이터를 로딩한다.
 * @param     vector<SRadarMode_Spot_Values> * pVecRadarMode_PRISpot
 * @param     int nMaxRadarMode
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-10 12:39:38
 * @warning
 */
bool CELSignalIdentifyAlg::LoadRadarMode_PRISpot( vector<SRadarMode_Spot_Values> *pVecRadarMode_PRISpot, unsigned int uiMaxRadarMode )
{

#ifdef _SQLITE_
    bool bRet = true;
    SRadarMode_Spot_Values stRadarMode_PRISpot_Values;

    int i;

    // 뷰 테이블에서 정렬 적용함.
    sprintf( m_szSQLString, "SELECT RADARMODE_INDEX, PRI_MIN, PRI_MAX FROM RADAR_PRI_SPOT_VALUES ORDER BY RADARMODE_INDEX" );

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.Sql( m_szSQLString );

        pVecRadarMode_PRISpot->clear();

        while( stmt.FetchRow() ) {
            i = 0;

            stRadarMode_PRISpot_Values.iRadarModeIndex = stmt.GetColumnInt( i++ );

            stRadarMode_PRISpot_Values.f_Min = ( float ) stmt.GetColumnDouble( i++ );
            stRadarMode_PRISpot_Values.f_Max = ( float ) stmt.GetColumnDouble( i++ );

            pVecRadarMode_PRISpot->push_back( stRadarMode_PRISpot_Values );
        }

        // do not forget to clean-up
        stmt.FreeQuery();

    }
    catch( Kompex::SQLiteException &sException ) {
        bRet = false;
        Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );

        KOMPEX_O_EXCEPT( "레이더 모드가 잘못 됐거나 쿼리문이 잘못 됐습니다 !", -1 );
    }


    return bRet;

#elif _MSSQL_
    DECLARE_BEGIN_CHECKODBC
    short i;
    SRadarMode_Spot_Values stRadarMode_PRISpot_Values;

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    sprintf_s( m_szSQLString, MAX_SQL_SIZE, "SELECT RADARMODE_INDEX, PRI_MIN, PRI_MAX FROM RADAR_PRI_SPOT_VALUES ORDER BY RADARMODE_INDEX ASC" );
    theRS.Open( m_szSQLString );

    pVecRadarMode_PRISpot->reserve( nMaxRadarMode * MAX_FREQ_PRI_STEP );
    pVecRadarMode_PRISpot->clear();
    //DeletePointers( *pVecRadarMode_RFSequence );

    while( !theRS.IsEof() ) {
        i = 0;

        theRS.GetFieldValue( i++, &stRadarMode_PRISpot_Values.iRadarModeIndex );

        theRS.GetFieldValue( i++, &stRadarMode_PRISpot_Values.f_Min );
        theRS.GetFieldValue( i++, &stRadarMode_PRISpot_Values.f_Max );

        pVecRadarMode_PRISpot->push_back( stRadarMode_PRISpot_Values );

        theRS.MoveNext();

    }

    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN
#else
    return true;

#endif

}

/**
 * @brief     레이더모드의 주파수 시퀀스 데이터를 로딩한다.
 * @param     vector<SRadarMode_Sequence_Values * > * pVecRadarMode_RFSequence
 * @param     int nMaxRadarMode
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-04, 17:37
 * @warning
 */
bool CELSignalIdentifyAlg::LoadRadarMode_RFSequence( vector<SRadarMode_Sequence_Values> *pVecRadarMode_RFSequence )
{

#ifdef _SQLITE_
    bool bRet = true;
    SRadarMode_Sequence_Values stRadarMode_RFSequence_Values;

    int i;

    // 뷰 테이블에서 정렬 적용함.
    sprintf( m_szSQLString, "SELECT RADARMODE_INDEX, RF_INDEX, RF_MIN, RF_MAX FROM VEL_RADAR_RF_SEQENCE" );

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.Sql( m_szSQLString );

        pVecRadarMode_RFSequence->clear();

        while( stmt.FetchRow() ) {
            i = 0;

            stRadarMode_RFSequence_Values.iRadarModeIndex = stmt.GetColumnInt( i++ );
            stRadarMode_RFSequence_Values.i_Index = stmt.GetColumnInt( i++ );

            stRadarMode_RFSequence_Values.f_Min = ( float ) stmt.GetColumnDouble( i++ );
            stRadarMode_RFSequence_Values.f_Max = ( float ) stmt.GetColumnDouble( i++ );

            pVecRadarMode_RFSequence->push_back( stRadarMode_RFSequence_Values );
        }

        // do not forget to clean-up
        stmt.FreeQuery();

    }
    catch( Kompex::SQLiteException &sException ) {
        bRet = false;
        Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );

        KOMPEX_O_EXCEPT( "레이더 모드가 잘못 됐거나 쿼리문이 잘못 됐습니다 !", -1 );

    }

    return bRet;

#elif _MSSQL_
    DECLARE_BEGIN_CHECKODBC
    short i;
    SRadarMode_Sequence_Values stRadarMode_RFSequence_Values;

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    sprintf_s( m_szSQLString, MAX_SQL_SIZE, "SELECT RADARMODE_INDEX, RF_INDEX, RF_MIN, RF_MAX FROM VEL_RADAR_RF_SEQENCE ORDER BY RADARMODE_INDEX ASC, RF_SEQ_ID ASC" );
    theRS.Open( m_szSQLString );

    // pVecRadarMode_RFSequence->reserve( nMaxRadarMode * MAX_FREQ_PRI_STEP );
    pVecRadarMode_RFSequence->clear();
    //DeletePointers( *pVecRadarMode_RFSequence );

    while( !theRS.IsEof() ) {
        i = 0;

        theRS.GetFieldValue( i++, & stRadarMode_RFSequence_Values.iRadarModeIndex );
        theRS.GetFieldValue( i++, & stRadarMode_RFSequence_Values.i_Index );

        theRS.GetFieldValue( i++, & stRadarMode_RFSequence_Values.f_Min );
        theRS.GetFieldValue( i++, & stRadarMode_RFSequence_Values.f_Max );

        pVecRadarMode_RFSequence->push_back( stRadarMode_RFSequence_Values );

        theRS.MoveNext();

    }

    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN
#else
    return true;

#endif

}

/**
 * @brief     레이더모드의 PRI 시퀀스 데이터를 로딩한다.
 * @param     vector<SRadarMode_Sequence_Values> * pVecRadarMode_PRISequence
 * @param     int nMaxRadarMode
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:28:15
 * @warning
 */
bool CELSignalIdentifyAlg::LoadRadarMode_PRISequence( vector<SRadarMode_Sequence_Values> *pVecRadarMode_PRISequence )
{

#ifdef _SQLITE_
    bool bRet = true;
    int i;

    SRadarMode_Sequence_Values stRadarMode_PRISequence_Values;

    // 뷰 테이블에서 정렬 적용함.
    sprintf( m_szSQLString, "SELECT RADARMODE_INDEX, PRI_INDEX, PRI_MIN, PRI_MAX FROM VEL_RADAR_PRI_SEQENCE" );

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.Sql( m_szSQLString );
        //SQLite::Statement query( *pDatabase, m_szSQLString );

        pVecRadarMode_PRISequence->clear();
        pVecRadarMode_PRISequence->reserve( ( unsigned int ) ( m_uiRadarMode * MAX_FREQ_PRI_STEP ) );

        while( stmt.FetchRow() ) {
            i = 0;

            stRadarMode_PRISequence_Values.iRadarModeIndex = stmt.GetColumnInt( i++ );
            stRadarMode_PRISequence_Values.i_Index = stmt.GetColumnInt( i++ );

            stRadarMode_PRISequence_Values.f_Min = ( float ) stmt.GetColumnInt( i++ );
            stRadarMode_PRISequence_Values.f_Max = ( float ) stmt.GetColumnInt( i++ );

            pVecRadarMode_PRISequence->push_back( stRadarMode_PRISequence_Values );
        }

        // do not forget to clean-up
        stmt.FreeQuery();

    }
    catch( Kompex::SQLiteException &sException ) {
        bRet = false;
        Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );

        KOMPEX_O_EXCEPT( "레이더 모드가 잘못 됐거나 쿼리문이 잘못 됐습니다 !", -1 );
    }

    return bRet;

#elif _MSSQL_
    DECLARE_BEGIN_CHECKODBC
    short index;

    SRadarMode_Sequence_Values stRadarMode_PRISequence_Values;

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    sprintf_s( m_szSQLString, MAX_SQL_SIZE, "SELECT RADARMODE_INDEX, PRI_SEQ_ID, PRI_MIN, PRI_MAX FROM VEL_RADAR_PRI_SEQENCE ORDER BY RADARMODE_INDEX ASC, PRI_SEQ_ID ASC" );
    theRS.Open( m_szSQLString );

    //pVecRadarMode_PRISequence->reserve( nMaxRadarMode * MAX_FREQ_PRI_STEP );
    pVecRadarMode_PRISequence->clear();
    //DeletePointers( *pVecRadarMode_PRISequence );

    while( !theRS.IsEof() ) {
        index = 0;

        theRS.GetFieldValue( index++, & stRadarMode_PRISequence_Values.iRadarModeIndex );
        theRS.GetFieldValue( index++, & stRadarMode_PRISequence_Values.i_Index );

        theRS.GetFieldValue( index++, & stRadarMode_PRISequence_Values.f_Min );
        theRS.GetFieldValue( index++, & stRadarMode_PRISequence_Values.f_Max );

        pVecRadarMode_PRISequence->push_back( stRadarMode_PRISequence_Values );

        theRS.MoveNext();

    }

    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN
#else
    return false;
#endif

}


/**
 * @brief     LoadThreatData
 * @param     int * pnThreat
 * @param     SThreat * pThreat
 * @param     int iMaxItems
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:28:33
 * @warning
 */
 // bool CELSignalIdentifyAlg::LoadThreatData( int *pnThreat, SThreat *pThreat, int iMaxItems )
 // {
 //     bool bRet=true;
 //     return bRet;
 // }

 /**
  * @brief     레이더모드의 기능 코드를 리턴한다.
  * @param     const char * pData
  * @return    EnumFunctionCodes
  * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
  * @author    조철희 (churlhee.jo@lignex1.com)
  * @version   1.0.0
  * @date      2022-08-25 19:29:19
  * @warning
  */
EnumFunctionCodes CELSignalIdentifyAlg::GetFunctionCodes( const char *pData )
{
    CString sTemp = "";
    EnumFunctionCodes eFunctionCodes_ForGUI = enumUndefinedFunctionCode;

    if( pData != NULL ) {
        for( int i = ( int ) enumAA_Anti_Aircraft_Fire_Control; i <= ( int ) enumXP_Experimental_or_Trainer; i++ ) {
            if( pData[0] == _FunctionCodes[i][0] && pData[1] == _FunctionCodes[i][1] ) {
                eFunctionCodes_ForGUI = ( EnumFunctionCodes ) i;
                break;
            }
        }
    }

    return eFunctionCodes_ForGUI;
}

/**
 * @brief     레이더모드의 기능 코드를 리턴한다.
 * @param     EnumFunctionCodes eFunctionCode
 * @return    char *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-04, 13:42
 * @warning
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
 * @brief     신호 형태가 정의된 문자열에 해당하는 enum 값을 리턴한다.
 * @param     const char * pData
 * @return    SignalType
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-05 19:15:56
 * @warning
 */
#ifdef _XBAND_
CEDSignalType::EnumSignalType CELSignalIdentifyAlg::GetSignalType( const char *pData )
{
    CEDSignalType::EnumSignalType eSignalType = CEDSignalType::enumPulsed;

    if( pData != NULL ) {
        for( int i = ( int ) CEDSignalType::enumPulsed; i <= ( int ) CEDSignalType::enumEA; i++ ) {
            if( strcmp( pData, _SignalType[i] ) == 0 ) {
                eSignalType = ( CEDSignalType::EnumSignalType ) i;
                break;
            }
        }
    }

    return eSignalType;
}
#endif

/**
 * @brief     레이더모드의 극성 코드를 리턴한다.
 * @param     int iPolization
 * @return    PolizationCode
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:29:53
 * @warning
 */
PolizationCode::EnumPolizationCode CELSignalIdentifyAlg::GetPolarizationCodes( int iPolization )
{
    PolizationCode::EnumPolizationCode ePolarization = PolizationCode::enumUndefinedPolization;

    if( iPolization >= PolizationCode::enumC_Diverse_Agile_or_adaptive_Capable_of_pulse_to_pulse_agility && \
        iPolization <= PolizationCode::enumZ_Undetermined ) {
        ePolarization = ( PolizationCode::EnumPolizationCode ) iPolization;
    }

    return ePolarization;
}

/**
 * @brief     레이더모드의 플래폼 코드를 리턴한다.
 * @param     int iPlatform
 * @return    PlatformCode
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:31:05
 * @warning
 */
PlatformCode::EnumPlatformCode CELSignalIdentifyAlg::GetPlatformCode( int iPlatform )
{
    PlatformCode::EnumPlatformCode ePlatform = PlatformCode::enumUndefinedPlatformCode;

    if( iPlatform >= PlatformCode::enumUndefinedPlatformCode && iPlatform <= PlatformCode::enumAir ) {
        ePlatform = ( PlatformCode::EnumPlatformCode ) iPlatform;
    }

    return ePlatform;
}

/**
 * @brief     레이더모드의 플래폼 코드를 리턴한다.
 * @param     PlatformCode::EnumPlatformCode ePlatform
 * @return    char *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:31:27
 * @warning
 */
const char *CELSignalIdentifyAlg::GetPlatformCode( PlatformCode::EnumPlatformCode ePlatform )
{
    const char *pChar = _PlatformCodes[PlatformCode::enumUnKnown];

    if( ePlatform >= PlatformCode::enumUnKnown && ePlatform <= PlatformCode::enumAir ) {
        pChar = _PlatformCodes[ePlatform];
    }

    return pChar;
}

/**
 * @brief     레이더모드의 패턴 코드를 리턴한다.
 * @param     int iPattern
 * @return    PatternCode
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:31:39
 * @warning
 */
PatternCode::EnumPatternCode CELSignalIdentifyAlg::GetPatternCode( int iPattern )
{
    PatternCode::EnumPatternCode ePattern = PatternCode::enumUndefinedPatternCode;

    if( iPattern >= PatternCode::enumUndefinedPatternCode && iPattern <= PatternCode::enumUnmodulated ) {
        ePattern = ( PatternCode::EnumPatternCode ) iPattern;
    }

    return ePattern;
}

/**
 * @brief     입력 주파수 형태를 체크하여 지정한 주파수 타입 형태로 리턴한다.
 * @param     int iFreqType
 * @return    RadarModeFreqType
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:31:52
 * @warning
 */
RadarModeFreqType::EnumRadarModeFreqType CELSignalIdentifyAlg::GetFreqType( int iFreqType )
{
    RadarModeFreqType::EnumRadarModeFreqType eFreqType = RadarModeFreqType::enumFIXED;

    if( iFreqType >= RadarModeFreqType::enumFIXED && iFreqType < RadarModeFreqType::enumFreqUnknown ) {
        eFreqType = ( RadarModeFreqType::EnumRadarModeFreqType ) iFreqType;
    }

    return eFreqType;
}

/**
 * @brief     입력 PRI 형태를 체크하여 지정한 PRI 타입 형태로 리턴한다.
 * @param     int iPRIType
 * @return    RadarModePRIType
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:32:10
 * @warning
 */
RadarModePRIType::EnumRadarModePRIType CELSignalIdentifyAlg::GetPRIType( int iPRIType )
{
    RadarModePRIType::EnumRadarModePRIType ePRIType = RadarModePRIType::enumStable;

    if( iPRIType >= RadarModePRIType::enumStable && iPRIType < RadarModePRIType::enumPRIUnknown ) {
        ePRIType = ( RadarModePRIType::EnumRadarModePRIType ) iPRIType;
    }

    return ePRIType;
}

/**
 * @brief     입력 스캔 형태를 체크하여 지정한 스캔 타입 형태로 리턴한다.
 * @param     int iScanType
 * @return    ScanType
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:34:10
 * @warning
 */
ScanType::EnumScanType CELSignalIdentifyAlg::GetScanType( int iScanType )
{
    ScanType::EnumScanType eScanType = ScanType::enumUndefinedScanType;

    if( iScanType >= ScanType::enumA_Circular && iScanType <= ScanType::enumD_Non_Scanning ) {
        eScanType = ( ScanType::EnumScanType ) iScanType;
    }

    return eScanType;
}

/**
 * @brief     입력 Validation 형태를 체크하여 지정한 Validation 타입 형태로 리턴한다.
 * @param     int iValidation
 * @return    EnumValidationCode
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:23:48
 * @warning
 */
EnumValidationCode CELSignalIdentifyAlg::GetValidationCode( int iValidation )
{
    EnumValidationCode eValidation = enumUndefinedValidationCode;

    if( iValidation >= enumUnvalidated && iValidation <= enumPostulated ) {
        eValidation = ( EnumValidationCode ) iValidation;
    }

    return eValidation;
}

/**
 * @brief     레이더의 DATE_ACTIVATED 필드에 최근 접촉 시간을 업데이트 한다.
 * @param     SRxAETData * pABTData
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-24 11:03:55
 * @warning
 */
bool CELSignalIdentifyAlg::UpdateToDB_SeenTimeOfRadar( SRxAETData * pAETData )
{
    bool bRet = true;

#if ( defined(_POCKETSONATA_) || defined(_712_) ) && defined(_MSC_VER)

#else
    unsigned int uiRadarIndex;

    uiRadarIndex = pAETData->uiRadarIndex;

    if( uiRadarIndex > _spZero ) {
        char buffer1[100], buffer2[100];

        CCommonUtils::getStringDesignatedDate( buffer1, sizeof( buffer1 ), pAETData->tiLastSeenTime );
        CCommonUtils::getStringPresentTime( buffer2, sizeof( buffer2 ) );


#if defined(_MSSQL_)

#elif defined(_SQLITE_)
        sprintf( m_szSQLString, "UPDATE RADAR SET DATE_ACTIVATED='%s', DATE_INACTIVATED='%s' WHERE RADAR_INDEX=%d", buffer1, buffer2, uiRadarIndex );

#endif

        // 여기서 부터 SQL 문을 실행 합니다.
#ifdef _MSSQL_
        if( m_szSQLString[0] != NULL ) {
            DECLARE_BEGIN_CHECKODBC

            CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

            theRS.Open( m_szSQLString );
            Log( enDebug, ".UpdateRM[I%d]", uiRadarIndex );

            theRS.Close();

            DECLARE_END_CHECKODBC
        }
        else {
            bRet = false;
        }

#elif _SQLITE_
#ifdef __VXWORKS__
        if( m_szSQLString[0] != '\0' ) {
#else
        if( m_szSQLString[0] != NULL ) {
#endif
            try {
                Kompex::SQLiteStatement stmt( m_pDatabase );

                if( 0 != MultiByteToUTF8( m_szSQLString16, m_szSQLString ) ) {
                    stmt.SqlStatement( m_szSQLString16 );
                    Log( enDebug, ".UpdateRadar[I%d]", uiRadarIndex );
                }
                else {
                    Log( enError, "LOB SQL의 버퍼 사이즈가 너무 적습니다 !!!" );
                }

                // do not forget to clean-up
                stmt.FreeQuery();
            }
            catch( Kompex::SQLiteException &sException ) {
                // LOGMSG1( enError, " m_szSQLString[%s]" , m_szSQLString );
                bRet = false;
                //std::cerr << "\nException Occured" << std::endl;
                //sException.Show();
                //std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
                Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );
            }
        }
        else {
            bRet = false;
        }

#else

#endif

        }
#endif

    return bRet;

    }

/**
 * @brief     레이더 모드 테이블에 LAST_SEEN_TIME 필드에 초근 접촉 시간을 업데이트 합니다.
 * @param     SRxABTData * pABTData
 * @param     bool bFirstSeen
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-23 12:34:27
 * @warning
 */
bool CELSignalIdentifyAlg::UpdateToDB_SeenTimeOfRadarMode( SRxABTData * pABTData, bool bFirstSeen )
{
    bool bRet = true;

#if ( defined(_POCKETSONATA_) || defined(_712_) ) && defined(_MSC_VER)

#else
    unsigned int uiRadarModeIndex;

    if( pABTData != NULL ) {
        uiRadarModeIndex = pABTData->uiRadarModeIndex;
    }
    else {
        uiRadarModeIndex = 2001;
    }

    if( uiRadarModeIndex > _spZero ) {
        char buffer[100] = { 0 };

        if( pABTData != NULL ) {
            if( bFirstSeen == true ) {
                CCommonUtils::getStringDesignatedDate( buffer, sizeof( buffer ), pABTData->tiFirstSeenTime );
            }
            else {
                CCommonUtils::getStringDesignatedDate( buffer, sizeof( buffer ), pABTData->tiLastSeenTime );
            }
        }
        else {
            CCommonUtils::getStringDesignatedDate( buffer, sizeof( buffer ), 100000 );
        }


#if defined(_MSSQL_)

#elif defined(_SQLITE_)
        if( pABTData != NULL ) {
            if( bFirstSeen == true ) {
                sprintf( m_szSQLString, "UPDATE RADARMODE SET DATE_FIRST_SEEN='%s' WHERE RADARMODE_INDEX=%d AND ( DATE_FIRST_SEEN='' OR DATE_FIRST_SEEN IS NULL )", buffer, pABTData->uiRadarModeIndex );
            }
            else {
                sprintf( m_szSQLString, "UPDATE RADARMODE SET DATE_LAST_SEEN='%s' WHERE RADARMODE_INDEX=%d", buffer, uiRadarModeIndex );
            }
        }
        else {
            if( bFirstSeen == true ) {
                //sprintf(m_szSQLString, "UPDATE RADARMODE SET DATE_FIRST_SEEN='%s' WHERE RADARMODE_INDEX=%d AND ( DATE_FIRST_SEEN='' OR DATE_FIRST_SEEN IS NULL )", buffer, 2001 );
                sprintf( m_szSQLString, "UPDATE RADARMODE SET DATE_LAST_SEEN='%s' WHERE RADARMODE_INDEX=%d", buffer, 2001 );
            }
            else {
                sprintf( m_szSQLString, "UPDATE RADARMODE SET DATE_LAST_SEEN='%s' WHERE RADARMODE_INDEX=%d", buffer, 2001 );
            }

        }

#endif


        // 여기서 부터 SQL 문을 실행 합니다.
#ifdef _MSSQL_
        if( m_szSQLString[0] != NULL ) {
            DECLARE_BEGIN_CHECKODBC

            CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

            theRS.Open( m_szSQLString );
            Log( enDebug, ".UpdateRM[I%d]", uiRadarModeIndex );

            theRS.Close();

            DECLARE_END_CHECKODBC
        }
        else {
            bRet = false;
        }

#elif _SQLITE_
#ifdef __VXWORKS__
        if( m_szSQLString[0] != '\0' ) {
#else
        if( m_szSQLString[0] != NULL ) {
#endif
            try {
                Kompex::SQLiteStatement stmt( m_pDatabase );

                stmt.SqlStatement( m_szSQLString );
                Log( enDebug, ".UpdateRM[I%d]", uiRadarModeIndex );

                // do not forget to clean-up
                stmt.FreeQuery();
            }
            catch( Kompex::SQLiteException &sException ) {
                Log( enError, " m_szSQLString[%s]", m_szSQLString );
                bRet = false;
                //std::cerr << "\nException Occured" << std::endl;
                //sException.Show();
                //std::cerr << "SQLite result code: " << sException.GetSqliteResultCode() << std::endl;
                Log( enError, "SQLite 에러[%d] : %s", sException.GetSqliteResultCode(), sException.GetErrorDescription().c_str() );
            }
        }
        else {
            bRet = false;
        }

#else

#endif

        }

#endif

    return bRet;

}

/**
 * @brief     IGetRadarMode
 * @param     unsigned int uiRadarModeIndex
 * @return    SRadarMode *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-11-06 14:09:34
 * @warning
 */
SRadarMode *CELSignalIdentifyAlg::IGetRadarMode( unsigned int uiRadarModeIndex )
{
    SRadarMode *pRadarMode = NULL;

    if( IsLocked() == true ) {

    }
    else {
        pRadarMode = uiRadarModeIndex == 0 || uiRadarModeIndex > m_uiRadarMode ? NULL : & m_vecRadarMode[uiRadarModeIndex - 1];
    }

    return pRadarMode;
}


/**
 * @brief     IGetThreat
 * @param     unsigned int uiIndex
 * @return    SThreat *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-11-06 14:09:39
 * @warning
 */
SThreat *CELSignalIdentifyAlg::IGetThreat( unsigned int uiThreadIndex )
{
    SThreat *pThreat = NULL;

    if( IsLocked() == true ) {

    }
    else {
        pThreat = uiThreadIndex == 0 || uiThreadIndex > m_uiThreat ? NULL : & m_vecThreat[uiThreadIndex - 1];
    }

    return pThreat;

}



