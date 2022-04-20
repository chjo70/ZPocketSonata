// Group.cpp: implementation of the CGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef _MSC_VER
// PC용 상위 클래스에 전달하기 위한 선언
//#include "../../A50SigAnal/stdafx.h"

#endif

#include "../OFP_Main.h"

#if defined(_ELINT_) || defined(_XBAND_)
//#include "../OFP_Main.h"

#elif defined(_POCKETSONATA_)
#include "../Identify/ELUtil.h"

#else
#error "컴파일러에 DEFINE 을 추가해야 합니다."

#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Group.h"

#include "../../Include/globals.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::CGroup
// 함 수 인 자  : int coMaxPdw /*=NSP_MAX_PDW*/
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-28 13:19:06
//
//##ModelId=426C87D70034
CGroup::CGroup( unsigned int uiCoMaxPdw )
{
    int i=0;
    BOOL bRet=TRUE;

    m_uiMaxPdw = _min( uiCoMaxPdw, MAX_PDW );

	// 주파수 해상도 계산용, HARMONIC MARGIN
#if defined(_ELINT_) || defined(_XBAND_)
	m_stSigma1Aoa[0] = KHARM_AOA_MAR;
	m_stSigma1Aoa[1] = KHARM_AOA_MAR;
	m_stSigma1Aoa[2] = KHARM_AOA_MAR;
	m_stSigma1Aoa[3] = KHARM_AOA_MAR;
	m_stSigma1Aoa[4] = KHARM_AOA_MAR;

#ifdef _XBAND_
	strcpy( m_szPulseType[i++], "CW" );
	strcpy( m_szPulseType[i++], "NP" );
#else
	strcpy( m_szPulseType[i++], "--" );
	strcpy( m_szPulseType[i++], "NP" );
	strcpy( m_szPulseType[i++], "CW" );
	strcpy( m_szPulseType[i++], "--" );
	strcpy( m_szPulseType[i++], "--" );
	strcpy( m_szPulseType[i++], "FM" );
	strcpy( m_szPulseType[i++], "--" );
	strcpy( m_szPulseType[i], "SP" );

#endif

#elif _POCKETSONATA_
	m_stSigma1Aoa[enPRC_Unknown] = 0;
	m_stSigma1Aoa[enPRC1] = KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC2] = KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC3] = KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC4] = KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC5] = KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC6] = KHARM_AOA_MAR;

	strcpy( m_szPulseType[i++], "--" );
	strcpy( m_szPulseType[i++], "NP" );
	strcpy( m_szPulseType[i++], "CW" );
	strcpy( m_szPulseType[i++], "--" );
	strcpy( m_szPulseType[i++], "--" );
	strcpy( m_szPulseType[i++], "FM" ); 
	strcpy( m_szPulseType[i++], "--" );
	strcpy( m_szPulseType[i++], "SP" );
	strcpy( m_szPulseType[i++], "CD" );
	strcpy( m_szPulseType[i], "CU" );

#else
	m_stSigma1Aoa[0] = KHARM_AOA_MAR_LOW;
	m_stSigma1Aoa[1] = KHARM_AOA_MAR_MID;
	m_stSigma1Aoa[2] = KHARM_AOA_MAR_HGH;

#endif

    for( i=0 ; i < TOTAL_BAND ; ++i ) {
        m_Band[i].pIndex = ( PDWINDEX * ) malloc( m_uiMaxPdw * sizeof( PDWINDEX ) );
        if( m_Band[i].pIndex == NULL ) {
            bRet = FALSE;
            printf( "\n [W] Memory allocation error !" );
            WhereIs;
        }
    }

    // 멤버 변수 메모리 할당
    for( i=0 ; i < MAX_STAT ; ++i ) {
        m_GrStat[i].pIndex = ( PDWINDEX * ) malloc( sizeof( PDWINDEX ) * m_uiMaxPdw );
        if( m_GrStat[i].pIndex == NULL ) {
            bRet = FALSE;
            printf( "\n [W] m_GrStat[%d].pIndex's Memory allocation error !" , i );
            WhereIs;
        }
    }

    for( i=0 ; i < MAX_AGRT ; ++i ) {
        m_AoaGroups.aoa[i].pIndex = ( PDWINDEX * ) malloc( sizeof( PDWINDEX ) * m_uiMaxPdw );
        if( m_AoaGroups.aoa[i].pIndex == NULL ) {
            bRet = FALSE;
            printf( "\n [W] m_AoaGroups.aoa[%d]'s Memory allocation error !" , i );
            WhereIs;
        }
    }

    m_FrqAoaPwIdx.pIndex = ( PDWINDEX * ) malloc( sizeof( PDWINDEX ) * m_uiMaxPdw );
    if( m_FrqAoaPwIdx.pIndex == NULL ) {
        bRet = FALSE;
        printf( "\n [W] m_FrqAoaPwIdx.pIndex's Memory allocation error !" );
        WhereIs;
    }

    m_pCluster = ( STR_CLUSTER * ) malloc( sizeof( STR_CLUSTER ) * MAX_AGRT );
    if( m_pCluster == NULL ) {
        bRet = FALSE;
        printf( "\n [W] m_pCluster's Memory allocation error !" );
        WhereIs;
    }

    if( bRet == FALSE )
        printf( "\n 그룹화 클래스 생성자 실패 !" );

    m_PwGroups.uiCount = 0;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::~CGroup
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-26 09:20:40
//
//##ModelId=426C87D70035
CGroup::~CGroup()
{
    int i;

    for( i=0 ; i < MAX_STAT ; ++i )
        free( m_GrStat[i].pIndex );

    for( i=0 ; i < MAX_AGRT ; ++i ) {
        free( m_AoaGroups.aoa[i].pIndex );
    }

    free( m_FrqAoaPwIdx.pIndex );

    for( i=0 ; i < TOTAL_BAND ; ++i ) {
        free( m_Band[i].pIndex );
    }

    free( m_pCluster );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::Init
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-26 18:18:23
//
//##ModelId=42757D4D0221
void CGroup::Init()
{
    // 펄스 수집 개수
    m_nCoPdw = GetColPdw();

    // PDW STAT 별 초기화
    for( int i=0 ; i < MAX_STAT ; ++i )
        m_GrStat[i].uiCount = 0;

    // 방위 및 주파수 필터링할 인덱스 카운터 초기화
    m_uiCoFrqAoaPwIdx = 0;

    // 탐지분석판 필터판 정보 플레그 설정
    m_FrqAoaPeak.enable = FALSE;

    // 그룹화 클러스터링 개수 초기화
    m_uiClusters = 0;
}

#ifdef _A50_RWR
//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::MakePDWArray
// 반환되는 형  : void
// 함 수 인 자  : _PDW *pdw
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-01 15:02:38
//
void CGroup::MakePDWArray( _PDW *pdw, int iCount, int iDummy )
{
    int i;

    UINT firstToa;

    UINT *pToa, *pPa, *pAoa, *pPw, *pFreq;

    UCHAR *pStat, *pBand, *pPmop, *pFmop, *pMaxChannel;
    USHORT *pMark;

    pToa = & TOA[0];
    pStat = & STAT[0];
    pPa = & PA[0];
    pPmop = & PMOP[0];
    pFmop = & FMOP[0];
    pAoa = & AOA[0];
    pPw = & PW[0];
    pFreq = & FREQ[0];
    pMark = & MARK[0];
    pBand = & BAND[0];
    pMaxChannel = & MAXCHANNEL[0];

    firstToa = pdw->x.toa;

    for( i=0 ; i < count ; ++i, ++pdw )	{
        *pToa++ = pdw->x.toa - firstToa;

        *pStat++ = pdw->x.stat;
        *pPa++   = pdw->x.pa;
        *pFmop++ = pdw->x.fdiff;
        *pAoa++  = pdw->x.aoa;
        *pPw++   = pdw->x.pw;
        *pFreq++ = pdw->x.freq;
        *pMark++ = UnMark;
        *pMaxChannel++ = pdw->x.max_channel;

        // *pPmop++ = pdw->item.pmop;
        // *pBand++ = pdw->item.band;
        *pBand++ = pdw->x.band;
    }
}

#elif defined(_ELINT_) || defined(_POCKETSONATA_) || defined(_XBAND_)
//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::MakePDWArray
// 반환되는 형  : void
// 함 수 인 자  : _PDW *pdw
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-01 15:02:38
//
bool CGroup::MakePDWArray( _PDW *pdw, unsigned int uiCount, int iBand )
{
    bool bRet=true;

    unsigned int i;
    _TOA templlTOA, prevllTOA;

    BOOL flagBand;

    _TOA firstToaBand;

    _TOA *pToa;
    int *pPa;
    UINT *pAoa, *pPw, *pFreq;

    UCHAR *pStat, *pBand;
    USHORT *pMark;

#ifdef _POCKETSONATA_
    UCHAR *pPmop, *pFmop, *pMaxChannel;

    pPmop = & m_pPMOP[0];
    pFmop = & m_pFMOP[0];
    pMaxChannel = & m_pMAXCHANNEL[0];

#endif
    
    pToa = & m_pTOA[0];
    pStat = & m_pSTAT[0];
    pPa = & m_pPA[0];
    pAoa = & m_pAOA[0];
    pPw = & m_pPW[0];
    pFreq = & m_pFREQ[0];
    pMark = & m_pMARK[0];
    pBand = & m_pBAND[0];


    // 첫번째 TOA 얻기
    _EQUALS4( firstToaBand, prevllTOA, templlTOA, pdw->ullTOA )

    flagBand = FALSE;

    for( i=0 ; i < uiCount; ++i, ++pdw )	{
        templlTOA = pdw->ullTOA;

        if( firstToaBand > templlTOA ) {
#ifdef _POCKETSONATA_
            *pToa++ = templlTOA + ( 0x100000000000 - firstToaBand );
#else
            *pToa++ = templlTOA - firstToaBand;
#endif
        }
        else {
            *pToa++ = templlTOA - firstToaBand;
        }

        *pStat++ = (unsigned char) pdw->iPulseType;
        *pPa++   = pdw->uiPA;
        *pAoa++ = pdw->uiAOA;
        *pPw++ = pdw->uiPW;
        *pFreq++ = pdw->uiFreq;
        *pMark++ = UnMark;

#ifdef _POCKETSONATA_
        *pPmop++ = (unsigned char) pdw->iPMOP;
        *pFmop++ = (unsigned char) pdw->iFMOP;
        *pMaxChannel++ = (unsigned char) pdw->iChannel;
#endif

        *pBand++ = iBand; // 0; // g_enBoardId;


    }

    return bRet;
}
#else

#endif

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : FrqGrpCompare
// 반환되는 형  : int
// 함 수 인 자  : const void *arg1
// 함 수 인 자  : const void *arg2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-14 15:58:55
//
int FrqGrpCompare(const void *arg1, const void *arg2) 
{
    int iRet=0;
    STR_FRQ_GROUP *p1, *p2;

    p1 = (STR_FRQ_GROUP *) arg1;
    p2 = (STR_FRQ_GROUP *) arg2;

    if( p1->narrow_wide > p2->narrow_wide ) {
        iRet = 1;
    }
    if( p1->narrow_wide < p2->narrow_wide ) {
        iRet = -1;
    }

    return iRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::MakeGroup
// 반환되는 형  : BOOL
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-26 18:30:50
//
//##ModelId=42757D4D0217
BOOL CGroup::MakeGroup()
{
    int i;

    // 방위 및 주파수 그룹화 초기화
    m_AoaGroups.uiCount = 0;
    m_AoaGroups.coAnal = 0;
    m_FrqGroups.uiCount = 0;
    m_FrqGroups.coAnal = 0;
    m_PwGroups.uiCount = 0;
    m_PwGroups.coAnal = 0;

    MakeBandGroup();

    // 밴드별 PDW STAT 그룹화
    //for( i=ALL_BAND-1 ; i >= BAND1 ; --i ) {
    {
        i = BAND0;
        MakeStatGroup( & m_Band[i] );

#ifdef _POCKETSONATA_
        m_nBand = g_enBoardId;
#else
        m_nBand = i;
#endif

        if( m_GrStat[STAT_CW].uiCount > _sp.cm.uiCw_Min_Cnt ) {
            m_nStat = STAT_CW;

            // 방위 그룹화 만들기
            MakeAOAGroup( & m_GrStat[STAT_CW], true );

            MakeFreqGroup( true );

            MakePWGroup( true );
        }
        else {
            // PDW 상태별 그룹화
            for( int j=0 ; j < MAX_STAT ; ++j ) {
                if( j == STAT_CW ) {
                    continue;
                }

                m_nStat = j;
                // 방위 그룹화 만들기
                MakeAOAGroup( & m_GrStat[j] );
            }

            /*! \bug  펄스폭 그룹화를 추가해서 De-interleaving을 가능케한다.
                                그룹화 내에서 지터 신호가 여러가 있으면 펄스열 추출이 불가능하다.
                                그래서 펄스폭을 이용해서 신호를 분리해서 분석하게 한다.
                \date 2006-06-02 17:55:44, 조철희
            */
            /*! \bug  방위 -> 펄스폭 -> 주파수 순으로 그룹화하게 되면 펄스폭 단계에서 하나의 그룹이 될 수 있기 때문에
                                방위 -> 주파수 -> 펄스폭 순으로 그룹화하게 되면 주파수 측면에서 그룹화가 먼저 되기 때문에 펄스폭 그룹화의 효용이 더 클 수 있다.
                \date 2006-08-17 15:35:25, 조철희
            */
            MakeFreqGroup();

            MakePWGroup( true );
        }
    }

    PrintAllGroup();

    return m_AoaGroups.uiCount != 0;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::PrintAllGroup
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2007-06-18 09:02:18
//
void CGroup::PrintAllGroup()
{
#ifdef _MSC_VER
    int IdxFrqAoaPw=0;

    STR_AOA_GROUP *pAoaGroup;
    STR_FRQ_GROUP *pFrqGr;
    STR_PW_GROUP *pPwGr;

    if( ! IsLastGroup(IdxFrqAoaPw) ) {
        //printf( "\n //////////////////////////////////////////////////////////////////////////"	);
        //printf( "\n 그룹화 총 개수 : %d" , m_PwGroups.count );
        Log( enNormal, "Group : %d" , m_PwGroups.uiCount );
    }

    while( ! IsLastGroup(IdxFrqAoaPw) ) {
        int nBand;

        // 다음 FGRT 선택
        pPwGr = & m_PwGroups.pw[ IdxFrqAoaPw ];
        pFrqGr = & m_FrqGroups.frq[ pPwGr->frq_idx ];
        pAoaGroup = & m_AoaGroups.aoa[ pFrqGr->aoa_idx ];

#ifdef _POCKETSONATA_
        nBand = g_enBoardId;
#else
        nBand = pAoaGroup->band;
#endif

        // 방위, 주파수, 펄스폭 그룹화 영역 필터링
        FilterParam( pAoaGroup, & m_pFREQ[0], & m_pPW[0], pFrqGr, pPwGr, & m_FrqAoaPwIdx );

        // 방위 그룹화 출력
        if( pFrqGr->narrow_wide == FALSE ) {
            //printf( "\n\t [%d] 방위 및 주파수 협대역 그룹화, 신호 개수(%3d), 방위(%3d-%3d), 주파수[MHz](%4d-%4d), 펄스폭[us](%4d-%4d)" , IdxFrqAoaPw, m_FrqAoaPwIdx.count, AOACNV( pAoaGroup->from_aoa ), AOACNV( pAoaGroup->to_aoa ), FRQMhzCNV( nBand, pFrqGr->from_frq ), FRQMhzCNV( nBand, pFrqGr->to_frq ), PWCNV( pPwGr->from_pw ), PWCNV( pPwGr->to_pw ) );
            Log( enNormal, "\t[%d] Narrow %s[%d]: Co(%3d), A(%3d-%3d), F[MHz](%4d-%4d), PW[ns](%6d-%6d)" , IdxFrqAoaPw, m_szPulseType[pAoaGroup->stat], pAoaGroup->stat, m_FrqAoaPwIdx.uiCount, I_AOACNV( pAoaGroup->from_aoa ), I_AOACNV( pAoaGroup->to_aoa ), I_FRQMhzCNV( nBand, pFrqGr->from_frq ), I_FRQMhzCNV( nBand, pFrqGr->to_frq ), I_PWCNV( pPwGr->from_pw ), I_PWCNV( pPwGr->to_pw ) );
        }
        else {
            //printf( "\n\t [%d] 방위 및 주파수 광대역 그룹화, 펄스(%d), 신호 개수(%3d), 방위(%.1f-%.1f), 주파수[MHz](%4d-%4d), 펄스폭[us](%4d-%4d)" , IdxFrqAoaPw, m_nStat, m_FrqAoaPwIdx.count, CPOCKETSONATAPDW::DecodeDOA( pAoaGroup->from_aoa ), CPOCKETSONATAPDW::DecodeDOA( pAoaGroup->to_aoa ), CPOCKETSONATAPDW::DecodeFREQMHz(pFrqGr->from_frq), CPOCKETSONATAPDW::DecodeFREQMHz(pFrqGr->to_frq), CPOCKETSONATAPDW::DecodePWus( pPwGr->from_pw ), CPOCKETSONATAPDW::DecodePWus( pPwGr->to_pw ) );
            Log( enNormal, "\t[%d] Wide   %s[%d]: Co(%3d), A(%3d-%3d), F[MHz](%4d-%4d), PW[us](%6d-%6d)" , IdxFrqAoaPw, m_szPulseType[pAoaGroup->stat], pAoaGroup->stat, m_FrqAoaPwIdx.uiCount, I_AOACNV( pAoaGroup->from_aoa ), I_AOACNV( pAoaGroup->to_aoa ), I_FRQMhzCNV( nBand, pFrqGr->from_frq), I_FRQMhzCNV( nBand, pFrqGr->to_frq), I_PWCNV( pPwGr->from_pw ), I_PWCNV( pPwGr->to_pw ) );
        }

#if defined(_ELINT_) || defined(_XBAND_)

#elif defined(_POCKETSONATA_)
        //printf( "주파수[MHz](%4d-%4d), " , CPOCKETSONATAPDW::DecodeFREQMHz(pFrqGr->from_frq), CPOCKETSONATAPDW::DecodeFREQMHz(pFrqGr->to_frq) );
#else
        if( nBand == BAND2 || nBand == BAND3 ) {
            printf( "주파수[MHz](%4d-%4d), " , FRQMhzCNV( nBand, pFrqGr->to_frq ), FRQMhzCNV( nBand, pFrqGr->from_frq ) );
        }
        else {
            printf( "주파수[MHz](%4d-%4d), " , FRQMhzCNV( nBand, pFrqGr->from_frq ), FRQMhzCNV( nBand, pFrqGr->to_frq ) );
        }
#endif

        ++ IdxFrqAoaPw;
    }
#endif

}

/**
 * @brief     PrintGroup
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-07, 14:11
 * @warning
 */
void CGroup::PrintGroup()
{
    STR_AOA_GROUP *pAoaGroup;
    STR_FRQ_GROUP *pFrqGr;
    STR_PW_GROUP *pPwGr;

    pPwGr = & m_PwGroups.pw[ m_uiCoFrqAoaPwIdx ];
    pFrqGr = & m_FrqGroups.frq[ pPwGr->frq_idx ];
    pAoaGroup = & m_AoaGroups.aoa[ pFrqGr->aoa_idx ];

    //Log( enDebug, "=====================================================================================================" );
    //printf( "\n [%d]번째 그룹화: 개수(%3d), 방위(%3d-%3d), 주파수[MHz](%4d-%4d), 펄스폭[us](%4d-%4d)" , m_CoFrqAoaPwIdx, m_FrqAoaPwIdx.count, AOACNV( pAoaGroup->from_aoa ), AOACNV( pAoaGroup->to_aoa ), FRQMhzCNV( m_nBand, pFrqGr->from_frq ), FRQMhzCNV( m_nBand, pFrqGr->to_frq ), PWCNV( pPwGr->from_pw ), PWCNV( pPwGr->to_pw ) );
    Log( enDebug, " [%d] GR: Co(%3d), A(%3d-%3d), F[MHz](%5d-%5d), PW[us](%6d-%6d)" , m_uiCoFrqAoaPwIdx, m_FrqAoaPwIdx.uiCount, I_AOACNV( pAoaGroup->from_aoa ), I_AOACNV( pAoaGroup->to_aoa ), I_FRQMhzCNV( m_nBand, pFrqGr->from_frq ), I_FRQMhzCNV( m_nBand, pFrqGr->to_frq ), I_PWCNV( pPwGr->from_pw ), I_PWCNV( pPwGr->to_pw ) );

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CGroup::MakeFreqGroup
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-07-27 16:29:47
//! \warning
//
void CGroup::MakeFreqGroup( bool bForce1Group )
{
    unsigned int j;

    /*! \bug  주파수 그룹화는 좁게와 넓게로 구분해서 그룹화한다.
            \date 2006-05-30 18:40:11, 조철희
    */
    // 주파수 그룹 범위테이블 만들기
    for( j=m_AoaGroups.coAnal ; j < m_AoaGroups.uiCount ; ++j ) {
#ifdef _FREQ_WIDE_NARROW_GROUP_
        int noGroups;

        noGroups = MakeFreqGroup( NARROW, j );
        m_FrqGroups.coAnal = m_FrqGroups.uiCount;

        if( noGroups >= 2 ) {
            MakeFreqGroup( WIDE, j, 0, bForce1Group );

            m_FrqGroups.coAnal = m_FrqGroups.uiCount;
        }
#else
        MakeFreqGroup( _WIDE, j, 0, bForce1Group );

#endif
    }

    m_AoaGroups.coAnal = m_AoaGroups.uiCount;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::MakeBandGroup
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-27 10:53:30
//
//##ModelId=42E85F3903A0
void CGroup::MakeBandGroup()
{
    int i;
    UCHAR *pBand;

    // 밴드 그룹화 초기화
    for( i=0 ; i < TOTAL_BAND ; ++i ) {
        m_Band[i].uiCount = 0;
    }

    // 밴드 그룹화
    pBand = & m_pBAND[0];
    for( i=0 ; i < m_nCoPdw ; ++i ) {
        m_Band[ *pBand ].pIndex[ m_Band[ *pBand ].uiCount++ ] = i;	// Band 그룹화
        //m_Band[ 0 ].pIndex[ m_Band[ 0 ].count++ ] = i;	// Band 그룹화
        ++ pBand;
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::MakeStatGroup
// 반환되는 형  : void
// 함 수 인 자  : STR_PDWINDEX *pBand
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-26 21:24:25
//
//##ModelId=42757D4D0203
void CGroup::MakeStatGroup( STR_PDWINDEX *pBand )
{
    unsigned int i;

    PDWINDEX *pPdwIndex;
    PDWINDEX *pCWPdwIndex;
    PDWINDEX *pNormalPdwIndex;
        
    // 밴드 STAT 별 PDW 인덱스 포인터
#ifdef _ELINT_
    PDWINDEX *pFmopPdwIndex;
    PDWINDEX *pShortPdwIndex;

    pNormalPdwIndex = m_GrStat[STAT_NORMAL].pIndex;
    pFmopPdwIndex = m_GrStat[STAT_FMOP].pIndex;
    pShortPdwIndex = m_GrStat[STAT_SHORTP].pIndex;
    pCWPdwIndex = m_GrStat[STAT_CW].pIndex;

#elif defined(_XBAND_)
	pNormalPdwIndex = m_GrStat[STAT_NORMAL].pIndex;
	pCWPdwIndex = m_GrStat[STAT_CW].pIndex;

#elif defined(_POCKETSONATA_)
    PDWINDEX *pChirpDnPdwIndex;
    PDWINDEX *pChirpUpPdwIndex;
    PDWINDEX *pPmopPdwIndex;

    pNormalPdwIndex = m_GrStat[STAT_NORMAL].pIndex;
    pCWPdwIndex = m_GrStat[STAT_CW].pIndex;
    pChirpDnPdwIndex = m_GrStat[STAT_CHIRPDN].pIndex;
    pChirpUpPdwIndex = m_GrStat[STAT_CHIRPUP].pIndex;
    pPmopPdwIndex = m_GrStat[STAT_PMOP].pIndex;

#else
    PDWINDEX *pFmopPdwIndex;

    pNormalPdwIndex = m_GrStat[STAT_NORMAL].pIndex;
    pCWPdwIndex = m_GrStat[STAT_CW].pIndex;
    pChirpDnPdwIndex = m_GrStat[STAT_FMOP].pIndex;
    pPmopPdwIndex = m_GrStat[STAT_PMOP].pIndex;
    pBitPdwIndex = m_GrStat[STAT_BIT].pIndex;
#endif

    for( i=0 ; i < MAX_STAT ; ++i ) {
        m_GrStat[i].uiCount = 0;
    }

    pPdwIndex = pBand->pIndex;

    for( i=0 ; i < pBand->uiCount ; ++i, ++pPdwIndex ) {
        switch( m_pSTAT[ *pPdwIndex ] ) {
            case STAT_NORMAL :
                *pNormalPdwIndex++ = *pPdwIndex;
                ++ m_GrStat[STAT_NORMAL].uiCount;
                break;

            case STAT_CW :
                *pCWPdwIndex++ = *pPdwIndex;
                ++ m_GrStat[STAT_CW].uiCount;
                break;

#ifdef _ELINT_
            case STAT_FMOP :
                *pFmopPdwIndex++ = *pPdwIndex;
                ++ m_GrStat[STAT_FMOP].uiCount;
                break;

            case STAT_SHORTP :
                *pShortPdwIndex++ = *pPdwIndex;
                ++ m_GrStat[STAT_SHORTP].uiCount;
                break;
#elif _XBAND_
#elif defined(_POCKETSONATA_)
            case STAT_CHIRPDN :
                *pChirpDnPdwIndex++ = *pPdwIndex;
                ++ m_GrStat[STAT_CHIRPDN].uiCount;
                break;

            case STAT_CHIRPUP :
                *pChirpUpPdwIndex++ = *pPdwIndex;
                ++ m_GrStat[STAT_CHIRPUP].uiCount;
                break;

            case STAT_PMOP :
                *pPmopPdwIndex++ = *pPdwIndex;
                ++ m_GrStat[STAT_PMOP].uiCount;
                break;
#else
            case STAT_CHIRPDN :
                *pChirpDnPdwIndex++ = *pPdwIndex;
                ++ m_GrStat[STAT_CHIRPDN].uiCount;
                break;

            case STAT_CHIRPUP :
                *pChirpUpPdwIndex++ = *pPdwIndex;
                ++ m_GrStat[STAT_CHIRPUP].uiCount;
                break;

            case STAT_PMOP :
                *pPmopPdwIndex++ = *pPdwIndex;
                ++ m_GrStat[STAT_PMOP].uiCount;
                break;

            case STAT_BIT :
                *pBitPdwIndex++ = *pPdwIndex;
                ++ m_GrStat[STAT_BIT].uiCount;
                break;
#endif

            default :
                // printf( "\n invalid pdw stat[%d]" , STAT[*pPdwIndex] );
                break;
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::MakeAOAGroup
// 반환되는 형  : void
// 함 수 인 자  : STR_PDWINDEX *pStatGrPdwIndex
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-26 22:25:31
//
//##ModelId=42757D4D01EF
void CGroup::MakeAOAGroup(STR_PDWINDEX *pStatGrPdwIndex, bool bForce1Group )
{
    STR_AOA_GROUP *pAoaGroup;

#ifdef _ISODATA_AOA_GROUP_
    unsigned int i;
    int diffVal, overVal, meanVal, frstVal;

    if( bForce1Group == true ) {
        PDWINDEX *pIndex=pStatGrPdwIndex->pIndex;

        pAoaGroup = & m_AoaGroups.aoa[ m_AoaGroups.uiCount ];

        pAoaGroup->to_aoa = -9999999;
        pAoaGroup->from_aoa = 0xffffff;

        meanVal = 0;
        frstVal = (int) m_pAOA[ *pIndex ];
        for( i=0 ; i < pStatGrPdwIndex->uiCount ; ++i ) {
            diffVal = (int) m_pAOA[ *pIndex++ ] - frstVal;
            overVal = _abs( diffVal );
            if( overVal > MAX_AOA/2 ) {
                if( frstVal > MAX_AOA/2 )
                    diffVal = diffVal + MAX_AOA;
                else
                    diffVal = diffVal - MAX_AOA;
            }

            meanVal += diffVal;

            pAoaGroup->to_aoa = _max( pAoaGroup->to_aoa, diffVal );
            pAoaGroup->from_aoa = _min( pAoaGroup->from_aoa, diffVal );
        }

        pAoaGroup->to_aoa = ( MAX_AOA + pAoaGroup->to_aoa + frstVal ) % MAX_AOA;
        pAoaGroup->from_aoa = ( MAX_AOA + pAoaGroup->from_aoa + frstVal ) % MAX_AOA;

        pAoaGroup->from_bin = pAoaGroup->from_aoa >> _sp.np.Aoa_Shift_Cnt;
        pAoaGroup->to_bin = pAoaGroup->to_aoa >> _sp.np.Aoa_Shift_Cnt;

        memcpy( pAoaGroup->pIndex, pStatGrPdwIndex->pIndex, sizeof(PDWINDEX)*pStatGrPdwIndex->uiCount );
        pAoaGroup->iCount = pStatGrPdwIndex->uiCount;

        pAoaGroup->bOverAoa = FALSE;

        pAoaGroup->stat = m_nStat;
        pAoaGroup->band = m_nBand;

        ++ m_AoaGroups.uiCount;

    }
    else {
        STR_CLUSTER *pCluster;

        // ISODATA - 클러스터링 알고리즘을 사용한 방위 클러스터링...
        //-- 조철희 2006-01-04 11:24:36 --//
        ISODATA( pStatGrPdwIndex, & m_pAOA[0] );

        pCluster = & m_pCluster[0];
        pAoaGroup = & m_AoaGroups.aoa[ m_AoaGroups.uiCount ];
        for( i=0 ; i < m_uiClusters ; ++i ) {
            pAoaGroup->bOverAoa = FALSE;

            // 방위 그룹화의 방위 영역 설정
            pAoaGroup->from_aoa = pCluster->aoa.iLow;
            pAoaGroup->to_aoa = pCluster->aoa.iHgh;
            pAoaGroup->from_bin = pCluster->aoa.iLow >> _sp.np.Aoa_Shift_Cnt;
            pAoaGroup->to_bin = pCluster->aoa.iHgh >> _sp.np.Aoa_Shift_Cnt;

            memcpy( pAoaGroup->pIndex, pCluster->index, sizeof(PDWINDEX)*pCluster->iCount );
            pAoaGroup->iCount = pCluster->iCount;

            pAoaGroup->stat = m_nStat;
            pAoaGroup->band = m_nBand;

            ++ pAoaGroup;
            ++ pCluster;
        }

        m_AoaGroups.uiCount += m_uiClusters;
    }

#else
    BOOL bRet;

    int peak_index;
    int peak_count;

    // 방위 히스토그램 계산
    MakeHist( pStatGrPdwIndex, & AOA[0], _sp.np.Aoa_Shift_Cnt, & m_AoaHist );

    for( ;; ) {
        pAoaGroup = & m_AoaGroups.aoa[ m_AoaGroups.uiCount ];

        if( m_AoaGroups.uiCount > MAX_AOA_GROUP ) {
            printf( "\n Over Aoa Group exceed !" );
            WhereIs;
            break;
        }

        peak_index = FindPeakInHist( m_AoaHist.bin_count, & m_AoaHist.hist[0] );
        if( peak_index < 0 ) {
            break;
        }
        peak_count = m_AoaHist.hist[ peak_index ];

        // 종료 조건
        if( peak_count < _spAnalMinPulseCount  ) {
            break;
        }

        // 방위 범위 구하기
        bRet = GetAOARange( peak_index, _sp.np.Aoa_Shift_Cnt, pAoaGroup );

        FilterParam( pStatGrPdwIndex, & AOA[0], pAoaGroup );

        ReDrawAoaHist( pAoaGroup );

        ++ m_AoaGroups.uiCount;

        if( bRet && pAoaGroup->iCount >= _spAnalMinPulseCount ) {
            break;
        }
    }

#endif

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::FindPeakInHist
// 반환되는 형  : int
// 함 수 인 자  : int count
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-27 19:46:09
//
//##ModelId=42757D4D0113
int CGroup::FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex)
{
    unsigned int ui;
    int peak_index, peak_count;

    peak_index = -1;
    peak_count = 0;

    for( ui=0 ; ui < uiCount; ++ui ) {
        if( peak_count < *pPdwIndex ) {
            peak_index = (int) ui;
            peak_count = *pPdwIndex;
        }
        ++ pPdwIndex;
    }

    return peak_index;
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CGroup::MakePWGroup
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-07-28 17:28:12
//! \warning
//
void CGroup::MakePWGroup( bool bForce1Group )
{
    unsigned int i;

    for( i=m_FrqGroups.coAnal ; i < m_FrqGroups.uiCount ; ++i ) {
        MakePWGroup( i, bForce1Group );
    }

    m_FrqGroups.coAnal = m_FrqGroups.uiCount;
}

/////////////////////////////////////////////////////////////////////
//
//! \brief    CGroup::MakePWGroup
//! \author   조철희
//! \param    frqidx 인자형태 int
//! \return   void
//! \version  1.37
//! \date		 2006-06-02 14:53:08
//! \warning
//
void CGroup::MakePWGroup( int frqidx, bool bForce1Group )
{
    int peak_index;

    STR_AOA_GROUP *pAoaGroup;
    STR_PW_GROUP *pPwGroup;
    STR_FRQ_GROUP *pFrqGroup;

    if( m_PwGroups.uiCount >= MAX_PGRT ) {
        printf( "\n [W] 펄스폭 그룹화 인덱스의 최대 개수[%d]를 초과했습니다." , m_PwGroups.uiCount );
        return;
    }

    pFrqGroup = & m_FrqGroups.frq[ frqidx ];
    pAoaGroup = & m_AoaGroups.aoa[ pFrqGroup->aoa_idx ];

    if( bForce1Group == true ) {
        int i;
        PDWINDEX *pIndex;

        pPwGroup = & m_PwGroups.pw[ m_PwGroups.uiCount ];

        pPwGroup->frq_idx = frqidx;
        pPwGroup->from_bin = 0;
        pPwGroup->to_bin = 0xFFFFFF;
        pIndex = pAoaGroup->pIndex;
        pPwGroup->from_pw = m_pPW[ *pIndex ];
        pPwGroup->to_pw = m_pPW[ *pIndex ];
        for( i=0 ; i < pAoaGroup->iCount ; ++i ) {
            pPwGroup->from_pw = _min( pPwGroup->from_pw, m_pPW[ *pIndex ] );
            pPwGroup->to_pw = _max( pPwGroup->to_pw, m_pPW[ *pIndex ] );

            ++ pIndex;
        }

        ++ m_PwGroups.uiCount;
    }
    else {
        MakeHist( pFrqGroup, pAoaGroup, PW_SHIFT_CNT, & m_PwHist );

        for( ;; ) {
            // 펄스폭 그룹화 포인터 초기화
            pPwGroup = & m_PwGroups.pw[ m_PwGroups.uiCount ];

            // 방위 그룹화 PDW STAT, 밴드, 오버방위 저장
            pPwGroup->frq_idx = frqidx;

            // 주파수 그룹화의 나머지 주파수 범위 계산
            // 주파수 히스토그램에서 최대값 찾기
            peak_index = FindPeakInHist( m_PwHist.bin_count, & m_PwHist.hist[0] );

            int sum_peak;
            /*! \bug  피크의 이웃점 체크
                    \date 2006-08-16 14:02:10, 조철희
            */
            if( peak_index >= 0 && peak_index < (int) sizeof( m_PwHist.hist ) ) {
                if( peak_index == 0 ) {
                    sum_peak = m_PwHist.hist[ 0 ] + m_PwHist.hist[ 1 ];
                }
                else if( peak_index == m_PwHist.bin_count-1 ) {
                    sum_peak = m_PwHist.hist[ peak_index ] + m_PwHist.hist[ peak_index - 1 ];
                }
                else if( peak_index > 0 ) {
                    sum_peak = m_PwHist.hist[ peak_index ] + m_PwHist.hist[ peak_index - 1 ] + m_PwHist.hist[ peak_index + 1 ];
                }
                else {
                    sum_peak = 0;
                }
            }
            else {
                sum_peak = 0;
            }

            // 종료 조건, 다음 방위 그룹 선택
            if( peak_index < 0 || ( sum_peak <= (int) _spAnalMinPulseCount ) ) {
                break;
            }

            // 펄스폭 범위 구하기
            GetPwRange( peak_index, PW_SHIFT_CNT, pPwGroup );

            ReDrawPwHist( pPwGroup );

            // 다음 펄스폭 그룹화 테이블 증가
            ++ m_PwGroups.uiCount;

            if( m_PwGroups.uiCount >= MAX_PGRT ) {
                printf( "\n [W] 펄스폭 그룹화 인덱스의 최대 개수[%d]를 초과했습니다." , m_PwGroups.uiCount );
                break;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::ReDrawPwHist
// 반환되는 형  : void
// 함 수 인 자  : STR_PW_GROUP *pPwGroup
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-06-16 15:42:21
//
void CGroup::ReDrawPwHist( STR_PW_GROUP *pPwGroup )
{
    register UINT i;
    PDWINDEX *pPdwIndex;

    pPdwIndex = & m_PwHist.hist[pPwGroup->from_bin];
    for( i=pPwGroup->from_bin ; i <= pPwGroup->to_bin ; ++i )
        *pPdwIndex++ = 0;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::GetPwRange
// 반환되는 형  : void
// 함 수 인 자  : int peak_index
// 함 수 인 자  : int nShift
// 함 수 인 자  : STR_PW_GROUP *pPwGroup
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-06-16 15:05:25
//
void CGroup::GetPwRange( int peak_index, int nShift, STR_PW_GROUP *pPwGroup )
{
    int i;
    int pw_bin;
    UINT max_pw_diff;

    max_pw_diff = UMUL(PW_GROUP_DIFF, _spOneMicrosec);

    //////////////////////////////////////////////////////////////////////
    // peak부터 좌로 범위를 설정
    // 좌측의 경계 찾기 (start)
    for( i=peak_index-1 ; i >= 0 ; --i ) {
        // 경계 조건
        if( m_PwHist.hist[i] <= 0 )
            break;

        // 좌 최대 범위, PW_GROUP_DIFF = 30 us
        if( ( ( peak_index - (i+1) ) << nShift ) >= (int) max_pw_diff )
        {
            printf(" \n [W] %d us를 초과했습니다." , PW_GROUP_DIFF );
            WhereIs;
            break;
        }
    }
    pw_bin = _min( i+1 , (int) m_PwHist.bin_count );

    /*! \bug  펄스폭 bin 값은 히스트그램 상에서 찾은 경계값까지 정한다.
            \date 2006-06-02 14:40:08, 조철희
    */
    // margin에 의한 경계 찾기
    pPwGroup->from_pw = _max( 0, pw_bin << nShift ); // _max( 0, ( frq_bin << nShift ) - freq_margin );
    pPwGroup->from_bin = pw_bin; /* pPwGroup->from_frq >> nShift; */

    //////////////////////////////////////////////////////////////////////
    // peak부터 우로 범위를 설정
    for( i=peak_index+1 ; i < (int) m_PwHist.bin_count ; ++i ) {
        // 경계 조건
        if( m_PwHist.hist[i] <= 0 )
            break;

        // 우 최대 범위, PW_GROUP_DIFF = 30 us
        if( ( ( i - peak_index ) << nShift ) > (int) max_pw_diff ) {
            //printf(" \n [W] %d us를 초과했습니다." , PW_GROUP_DIFF );
            Log( enError, "[W] It was excedd the PRI Diff %d[us]." , PW_GROUP_DIFF );
            WhereIs;
            break;
        }
    }
    pw_bin = _max(0, i-1 );

    /*! \bug  주파수 bin 값은 히스트그램 상에서 찾은 경계값까지 정한다.
        \date 2006-06-02 14:41:03, 조철희
    */
    // margin에 의한 경계 찾기
    pPwGroup->to_pw = _min( MAX_PW, ( pw_bin+1 ) << nShift );
    pPwGroup->to_bin = pw_bin; // pFrqGroup->to_frq >> nShift;

    return;
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CGroup::MakeFreqGroup
//! \author   조철희
//!	\param		door	인자형태 int
//!	\param		aoaidx	인자형태 int
//!	\param		frqidx	인자형태 int
//! \return   UINT
//! \version  1.37
//! \date     2005-04-28 09:37:14
//!						2006-06-01 15:46:14, pwidx 추가
//! \warning
//
UINT CGroup::MakeFreqGroup( int door, int aoaidx, int frqidx, bool bForce1Group )
{
    int iRet=0;
    int nShift;
    int freqdiff;

    int peak_index;

    int band;

    STR_AOA_GROUP *pAoaGroup;
    STR_FRQ_GROUP *pFrqGroup;

    int pre_CoFrqGroups;

    if( m_FrqGroups.uiCount >= MAX_FGRT ) {
        printf( "\n [W] 주파수 그룹화 인덱스의 최대 개수[%d]를 초과했습니다." , m_FrqGroups.uiCount );
        return 0;
    }

    if( bForce1Group == true ) {
        int i;
        PDWINDEX *pIndex;

        pFrqGroup = & m_FrqGroups.frq[ m_FrqGroups.uiCount ];

        pFrqGroup->aoa_idx = aoaidx;
        pFrqGroup->narrow_wide = door;
        pFrqGroup->end_of_aoagroup = FALSE;

        pAoaGroup = & m_AoaGroups.aoa[ aoaidx ];
        pFrqGroup->from_bin = 0;
        pFrqGroup->to_bin = 0xFFFFFF;
        pIndex = pAoaGroup->pIndex;
        pFrqGroup->from_frq = m_pFREQ[ *pIndex ];
        pFrqGroup->to_frq = m_pFREQ[ *pIndex ];
        for( i=0 ; i < pAoaGroup->iCount ; ++i ) {
            pFrqGroup->from_frq = _min( pFrqGroup->from_frq, m_pFREQ[ *pIndex ] );
            pFrqGroup->to_frq = _max( pFrqGroup->to_frq, m_pFREQ[ *pIndex ] );

            ++ pIndex;
        }

        ++ m_FrqGroups.uiCount;

        iRet = m_FrqGroups.uiCount;
    }
    else {
        // 주파수 그룹화 이전 개수 보관.
        pre_CoFrqGroups = m_FrqGroups.uiCount;

        pAoaGroup = & m_AoaGroups.aoa[ aoaidx ];

        band = pAoaGroup->band;
        if( door == NARROW ) {
            nShift = GetFreqShift( band, FREQ_NARR_MHZ );
            freqdiff = NARROW_FREQ_GROUP;
        }
        else {
            nShift = GetFreqShift( band, FREQ_WIDE_MHZ );
            freqdiff = WIDE_FREQ_GROUP;
        }

        //주파수 히스토그램 작성
        MakeHist( pAoaGroup, & m_pFREQ[0], nShift, & m_FrqHist );

        for( ;; ) {
            // 주파수 그룹화 초기화
            pFrqGroup = & m_FrqGroups.frq[ m_FrqGroups.uiCount ];

            // 방위 그룹화 PDW STAT, 밴드, 오버방위 저장
            pFrqGroup->aoa_idx = aoaidx;
            pFrqGroup->narrow_wide = door;
            pFrqGroup->end_of_aoagroup = FALSE;

            // 주파수 그룹화의 나머지 주파수 범위 계산
            // 주파수 히스토그램에서 최대값 찾기
            peak_index = FindPeakInHist( m_FrqHist.bin_count, & m_FrqHist.hist[0] );

            /*! \bug  peak_index에서 bin count 값이 _spAnalMinPulseCount(6) 이하일 때 그룹화 루프를 벗어나도록 했는데
                                여기서 이웃점들이 있을 때 그 개수가 최대 18개 가 있을 수 있다.
                    \date 2006-05-15 15:23:02, 조철희
            */
            int sum_peak;

            if( peak_index >= 0 && peak_index < (int) sizeof(m_FrqHist.hist) ) {
                if( peak_index == 0 ) {
                    sum_peak = m_FrqHist.hist[ 0 ] + m_FrqHist.hist[ 1 ];
                }
                else if( peak_index == m_FrqHist.bin_count-1 ) {
                    sum_peak = m_FrqHist.hist[ peak_index ] + m_FrqHist.hist[ peak_index - 1 ];
                }
                else if( peak_index > 0 ) {
                    sum_peak = m_FrqHist.hist[ peak_index ] + m_FrqHist.hist[ peak_index - 1 ] + m_FrqHist.hist[ peak_index + 1 ];
                }
                else {
                    sum_peak = 0;
                }
            }
            else {
                sum_peak = 0;
            }

            // 종료 조건, 다음 방위 그룹 선택
            if( peak_index < 0 || ( sum_peak /* m_FrqHist.hist[ peak_index ] */ <= (int) _spAnalMinPulseCount ) ) {
                if( m_FrqGroups.uiCount > 0 ) {
                    -- pFrqGroup;
                }
                pFrqGroup->end_of_aoagroup = TRUE;
                iRet = m_FrqGroups.uiCount - pre_CoFrqGroups;
                break;
            }

            // 주파수 범위 구하기
            GetFrqRange( peak_index, nShift, freqdiff, pFrqGroup );

            ReDrawFrqHist( pFrqGroup );

            // 다음 주파수 그룹화 테이블 증가
            ++ m_FrqGroups.uiCount;

            if( m_FrqGroups.uiCount >= MAX_FGRT ) {
                printf( "\n [W] 주파수 그룹화 인덱스의 최대 개수[%d]를 초과했습니다." , m_FrqGroups.uiCount );

                if( m_FrqGroups.uiCount > 0 ) {
                    -- pFrqGroup;
                }
                pFrqGroup->end_of_aoagroup = TRUE;
                iRet = m_FrqGroups.uiCount - pre_CoFrqGroups;
                break;
            }

            // 최초 그룹화 범위를 저장한다.
            // 최초의 그룹( 최대 개수의 주파수 그룹 )
            SaveFrqAoaPeak();
        }
    }

    return iRet;

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CGroup::GetFreqShift
//! \author   조철희
//! \param    band 인자형태 int
//! \param    freq 인자형태 int
//! \return   int
//! \version  1.37
//! \date     2006-08-21 08:51:38
//! \warning
//
int CGroup::GetFreqShift( int band, int freq )
{
    int i;
    int power=1;

#if defined(_ELINT_) || defined(_XBAND_)
    for( i=1 ; i <= 30 ; ++i ) {
        if( power >= freq ) {
            break;
        }
        power *= 2;
    }
#elif defined(_POCKETSONATA_)
    //float freq_res = gFreqRes[band+1].res;
    //freq_res = freq_res > 0 ? freq_res : -freq_res;
    for( i=1 ; i <= 30 ; ++i ) {
        if( power >= freq ) {
            break;
        }
        power *= 2;
    }

#else

    for( i=1 ; i <= 30 ; ++i ) {
        if( power >= freq )
            break;
        power *= 2;
    }

#endif

    return i-1;
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CGroup::MakeHist
//! \author   조철희
//! \param    pPwGroup 인자형태 STR_PW_GROUP *
//! \param    pAoaGroup 인자형태 STR_AOA_GROUP *
//! \param    nShift 인자형태 UINT
//! \param    pHist 인자형태 STR_FRQAOAPWHISTOGRAM *
//! \return   void
//! \version  1.37
//! \date     2006-08-07 10:06:15
//! \warning
//
void CGroup::MakeHist( STR_PW_GROUP *pPwGroup, STR_AOA_GROUP *pAoaGroup, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist )
{
    int i;
    int index;
    int pw;

    PDWINDEX *pIndex;

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

    // bin 개수 구하기
    SetHistBinCount( nShift, pHist );

    pIndex = & pAoaGroup->pIndex[0];
    // 대상 index의 파라메터에 대한 히스토그램 만들기
    for( i=0 ; i < pAoaGroup->iCount; ++i ) {
        pw = m_pPW[ *pIndex ];

        if( CompMarginDiff<unsigned int>( pw, pPwGroup->from_pw, pPwGroup->to_pw, 0 ) == TRUE ) {
            index = m_pFREQ[ *pIndex ] >> nShift;
            if( index >= pHist->bin_count ) {
                printf( "\n [W] 히스토그램 생성에서 에러 발생함 !" );
                WhereIs;
            }
            else {
                ++ pHist->hist[index];
            }
        }

        ++ pIndex;
    }
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CGroup::MakeHist
//! \author   조철희
//! \param    pFrqGroup 인자형태 STR_FRQ_GROUP *
//! \param    pAoaGroup 인자형태 STR_AOA_GROUP *
//! \param    nShift 인자형태 UINT
//! \param    pHist 인자형태 STR_FRQAOAPWHISTOGRAM *
//! \return   void
//! \version  1.37
//! \date     2006-08-17 16:10:42
//! \warning
//
void CGroup::MakeHist( STR_FRQ_GROUP *pFrqGroup, STR_AOA_GROUP *pAoaGroup, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist )
{
    int i;
    int index;
    int freq;

    PDWINDEX *pIndex;

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

    // bin 개수 구하기
    SetHistBinCount( nShift, pHist );

    pIndex = & pAoaGroup->pIndex[0];
    // 대상 index의 파라메터에 대한 히스토그램 만들기
    for( i=0 ; i < pAoaGroup->iCount; ++i ) {
        freq = m_pFREQ[ *pIndex ];

        if( CompMarginDiff<unsigned int>( freq, pFrqGroup->from_frq, pFrqGroup->to_frq, 0 ) == TRUE ) {
            index = m_pPW[ *pIndex ] >> nShift;
            if( index >= pHist->bin_count ) {
                printf( "\n [W] 펄스폭 히스토그램 생성에서 에러 발생함 !" );
                WhereIs;
            }
            else {
                ++ pHist->hist[index];
            }
        }

        ++ pIndex;
    }
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 펄스폭 히스토그램 생성
//!	\author  조철희
//!	\param	 pFrqGroup	인자형태 STR_FRQ_GROUP *
//!	\param	 pAoaGroup	인자형태 STR_AOA_GROUP *
//!	\param	 pFreq	인자형태 UINT *
//!	\param	 pPW	인자형태 UINT *
//!	\param	 nShift	인자형태 UINT
//!	\param	 pHist	인자형태 STR_FRQAOAPWHISTOGRAM *
//!	\return	 void
//! \version 1.0
//! \date		 2006-06-02 17:18:17
//! \warning
//
void CGroup::MakeHist( STR_FRQ_GROUP *pFrqGroup, STR_AOA_GROUP *pAoaGroup, UINT *pFreq, UINT *pPW, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist )
{
    int i;
    int index;
    int frq;

    int nFrqShift;

    PDWINDEX *pIndex;

    if( pFrqGroup->narrow_wide == _WIDE )
        nFrqShift = FREQ_WIDE_SHIFT_CNT;
    else
        nFrqShift = FREQ_NARR_SHIFT_CNT;

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

    pHist->bin_count = ( MAX_PW / ( 1 << nShift ) );

    pIndex = & pAoaGroup->pIndex[0];
    // 대상 index의 파라메터에 대한 히스토그램 만들기
    for( i=0 ; i < pAoaGroup->iCount; ++i, ++pIndex ) {
        frq = pFreq[ *pIndex ];
        frq = frq >> nFrqShift;

        if( CompMarginDiff<unsigned int>( frq, pFrqGroup->from_bin, pFrqGroup->to_bin, 0 ) == TRUE ) {
            index = pPW[ *pIndex ];
            index = index >> nShift;

            if( index >= pHist->bin_count ) {
                printf( "\n [W] 히스토그램 생성에서 에러 발생함 !" );
                WhereIs;
            }
            else
                ++ pHist->hist[index];
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CGroup::MakeHist
//!	\author  조철희
//!	\param	 pFrqGroup	인자형태 STR_FRQ_GROUP *
//!	\param	 pAoaGroup	인자형태 STR_AOA_GROUP *
//!	\param	 pPdw	인자형태 UINT *
//!	\param	 nShift	인자형태 UINT
//!	\param	 pHist	인자형태 STR_FRQAOAPWHISTOGRAM *
//!	\return	 void
//! \version 1.0
//! \date		 2006-06-01 19:00:53
//! \warning
//
void CGroup::MakeHist( STR_FRQ_GROUP *pFrqGroup, STR_AOA_GROUP *pAoaGroup, UINT *pPdw, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist )
{
    int i;
    int index;
    int frq;

    int nFrqShift;

    PDWINDEX *pIndex;

    if( pFrqGroup->narrow_wide == _WIDE )
        nFrqShift = FREQ_WIDE_SHIFT_CNT;
    else
        nFrqShift = FREQ_NARR_SHIFT_CNT;

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

    // bin 개수 구하기
    SetHistBinCount( nShift, pHist );

    pIndex = & pAoaGroup->pIndex[0];
    // 대상 index의 파라메터에 대한 히스토그램 만들기
    for( i=0 ; i < pAoaGroup->iCount; ++i ) {
        _EQUALS3( index, frq, pPdw[*pIndex] )
        ++ pIndex;

        index = index >> nShift;
        frq = frq >> nFrqShift;
        if( CompMarginDiff<unsigned int>( frq, pFrqGroup->from_bin, pFrqGroup->to_bin, 0 ) == TRUE ) {
            if( index >= pHist->bin_count ) {
                printf( "\n [W] 히스토그램 생성에서 에러 발생함 !" );
                WhereIs;
            }
            else {
                ++ pHist->hist[index];
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::MakeHist
// 반환되는 형  : void
// 함 수 인 자  : STR_AOA_GROUP *pAoaGroups
// 함 수 인 자  : UINT *pPdw
// 함 수 인 자  : UINT nShift
// 함 수 인 자  : STR_FRQAOAPWHISTOGRAM *pHist
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-28 10:09:49
//
//##ModelId=42757D4D00E1
void CGroup::MakeHist( STR_AOA_GROUP *pAoaGroup, UINT *pPdw, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist)
{
    int i;
    int index;

    PDWINDEX *pIndex;

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

    /*! \bug  주파수/방위/펄스폭의 히스토그램의 BIN 개수를 정한다.
        \date 2006-07-27 14:39:03, 조철희
    */
    // bin 개수 구하기
    SetHistBinCount( nShift, pHist );

    pIndex = & pAoaGroup->pIndex[0];
    // 대상 index의 파라메터에 대한 히스토그램 만들기
    for( i=0 ; i < pAoaGroup->iCount; ++i ) {
        // 고속 계산을 하기 위해서 나누기 대신에 Shift 연산으로 변경
        //index = ( *( pPdw + *pIndex++ ) ) >> nShift;
        index = pPdw[*pIndex++ ] >> nShift;
        //index = ( *( pPdw + *pIndex++ ) ) >> nShift;
        if( index >= pHist->bin_count ) {
            printf( "\n [W] 방위 및 주파수 히스토그램 생성에서 에러 발생함 !" );
            WhereIs;
        }
        else {
            ++ pHist->hist[index];
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::MakeHist
// 반환되는 형  : void
// 함 수 인 자  : STR_PDWINDEX *pSrcIndex
// 함 수 인 자  : UINT *pPdw
// 함 수 인 자  : UINT nShift
// 함 수 인 자  : STR_FRQAOAPWHISTOGRAM *pHist
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-26 22:40:18
//
//##ModelId=42757D4D01B3
void CGroup::MakeHist( STR_PDWINDEX *pSrcIndex, UINT *pPdw, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist )
{
    unsigned int i;
    int index;
    PDWINDEX *pIndex;

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

    SetHistBinCount( nShift, pHist );

    pIndex = & pSrcIndex->pIndex[0];
    for( i=0 ; i < pSrcIndex->uiCount; ++i ) {	// 대상 index의 파라메터에 대한 히스토그램 만들기
        int iIndex;

        //index = ( *( pPdw + (*pIndex++) ) ) >> nShift;
        iIndex = (*pIndex++);
        index = ( pPdw[ iIndex ] ) >> nShift;
        if( index > pHist->bin_count ) {
            printf( "\n [W] 히스토그램 생성에서 에러 발생함 !" );
            WhereIs;
        }
        else
            ++ pHist->hist[index];
    }
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CGroup::SetHistBinCount
//! \author   조철희
//! \param    nShift 인자형태 UINT
//! \param    pHist 인자형태 STR_FRQAOAPWHISTOGRAM *
//! \return   void
//! \version  1.37
//! \date     2006-08-18 15:57:23
//! \warning
//
void CGroup::SetHistBinCount( UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist )
{
    if( pHist == & m_AoaHist ) {
        pHist->bin_count = ( MAX_AOA / ( 1 << nShift ) );
        if( pHist->bin_count > TOTAL_FRQAOAPWBIN || pHist->bin_count == 0 ) {
            //printf( "\n [W] 방위 히스토그램 BIN 개수 초과(%d) !", pHist->bin_count );
            Log( enError, "\n [W] Over the BIN(%d) of AOA Histogram !", pHist->bin_count );
            WhereIs;
        }
    }
    else if( pHist == & m_FrqHist ) {
        pHist->bin_count = ( MAX_FREQ / ( 1 << nShift ) );
        if( pHist->bin_count > TOTAL_FRQAOAPWBIN || pHist->bin_count == 0 ) {
            //printf( "\n [W] 주파수 히스토그램 BIN 개수 초과(%d) !", pHist->bin_count );
            Log( enError, "\n [W] Over the BIN(%d) of Freq Histogram !", pHist->bin_count );
            WhereIs;
        }
    }
    else {
        pHist->bin_count = ( MAX_PW / ( 1 << nShift ) );
        if( pHist->bin_count > TOTAL_FRQAOAPWBIN || pHist->bin_count == 0 ) {
            //printf( "\n [W] 펄스폭 히스토그램 BIN 개수 초과(%d) !", pHist->bin_count );
            Log( enError, "\n [W] Over the BIN(%d) of PW Histogram !", pHist->bin_count );
            WhereIs;
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::MakeHist
// 반환되는 형  : int
// 함 수 인 자  : STR_PDWINDEX *pSrcIndex
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-09-30 16:52:28
//
int CGroup::CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex ) {
    unsigned int i;
    int frstAoa, diffAoa, overAoa;
    PDWINDEX *pPdwIndex;

    int bin, bin_low, bin_mid, bin_hgh;

    int sum_item, filted_count;

    // 방위 히스토그램을 작성한다.
    MakeHist( pSrcIndex, & m_pAOA[0], SHIFT_COUNT_BY_HIST, & m_AoaHist );

    // 히스토그램 상중에서 가장 큰 피크값을 찾는다.
    bin_mid = FindPeakInHist( m_AoaHist.bin_count, & m_AoaHist.hist[0] );
    if( bin_mid-1 < 0 )
        bin_low = ( MAX_AOA >> SHIFT_COUNT_BY_HIST ) - 1;
    else
        bin_low = bin_mid - 1;
    bin_hgh = ( bin_mid + 1 ) % ( MAX_AOA  >> SHIFT_COUNT_BY_HIST );

    // 찾은 피크점에 대한 실 방위 정보들에 대한 평균값을 계산한다.
    frstAoa = -1;
    pPdwIndex = pSrcIndex->pIndex;
    _EQUALS4( sum_item, filted_count, diffAoa, 0 )
    for( i=0 ; i < pSrcIndex->uiCount ; ++i ) {
        bin = m_pAOA[ *pPdwIndex ] >> SHIFT_COUNT_BY_HIST;
        if( bin == bin_low || bin == bin_mid || bin == bin_hgh ) {
            if( frstAoa == -1 ) {
                frstAoa = m_pAOA[ *pPdwIndex ];
            }
            else {
                diffAoa = (int) m_pAOA[ *pPdwIndex ] - frstAoa;
                overAoa = _abs( diffAoa );
                if( overAoa > MAX_AOA/2 ) {
                    if( frstAoa > MAX_AOA/2 )
                        diffAoa = diffAoa + MAX_AOA;
                    else
                        diffAoa = diffAoa - MAX_AOA;
                }
            }
            sum_item += diffAoa;
            ++ filted_count;
        }
        ++ pPdwIndex;
    }

    if( filted_count == 0 ) {
        printf( "\n [W] 에미터 생성시에 방위 평균값을 잘못 계산됨!" );
        WhereIs;
        return -1;
    }
    else {
        return ( MAX_AOA + IDIV( sum_item, filted_count ) + frstAoa ) % MAX_AOA;
    }
}

#ifndef _ISODATA_AOA_GROUP_
//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::GetAOARange
// 반환되는 형  : BOOL ; TRUE이면 전방위 그룹화 FALSE 이면 단일 방위 그룹화
// 함 수 인 자  : int peak_index
// 함 수 인 자  : int nShift
// 함 수 인 자  : STR_AOA_GROUP *pAoaGroup
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-27 01:32:33
//
//##ModelId=42757D4D0163
BOOL CGroup::GetAOARange( int peak_index, int nShift, STR_AOA_GROUP *pAoaGroup )
{
    int i;

    int aoa_bin;
    int from_bin, to_bin;

    int co_thresh;

    int thr;

    // 4 시그마 범위
    thr = ( m_stSigma1Aoa[m_nBand] * 4 ) >> nShift;

    // 전방위 그룹화 될 때의 방위 그룹화 범위
    pAoaGroup->from_bin = 0;
    pAoaGroup->to_bin = m_AoaHist.bin_count - 1;
    pAoaGroup->from_aoa = 0;
    pAoaGroup->to_aoa = MAX_AOA  - 1;
    pAoaGroup->stat = m_nStat;
    pAoaGroup->bOverAoa = FALSE;
    pAoaGroup->band = m_nBand;

    //////////////////////////////////////////////////////////////////////
    // peak부터 좌로 범위를 설정
    // 좌측의 경계 찾기 (from_val)
    co_thresh = 0;
    for( i=(int) ( peak_index-1) ;; --i ) {
        // 좌측의 끝에 도달 overgroup 발생
        if( i < 0 ) {
            i += m_AoaHist.bin_count;
            pAoaGroup->bOverAoa = TRUE;
        }

        // 전방위 그룹화 체크
        if( i == (int) peak_index )
            return TRUE;

        // 방위 좌측 값 체크
        // 경계 조건
        if( m_AoaHist.hist[i] <= _sp.np.Aoa_Hist_Thr )
            ++ co_thresh;
        else
            co_thresh = 0;

        //-- 조철희 2005-11-22 11:14:47 --//
        if( co_thresh >= MIN_CONTI_THRESHOLD_AOA )
            break;
    }

    // 좌 최소범위 경계조건
    // 4 시그마 이하
    aoa_bin = i;
    if( peak_index > i ) {
        if( peak_index - i < thr ) {
            aoa_bin = peak_index - thr;
        }
    }
    else {
        if( peak_index + (int) ( m_AoaHist.bin_count - i ) < thr ) {
            aoa_bin = peak_index - thr ;
        }
    }
    // 좌측의 끝에 도달 overgroup 발생
    if( aoa_bin < 0 )	{
        pAoaGroup->bOverAoa = TRUE;
        aoa_bin += m_AoaHist.bin_count;
    }
    from_bin = aoa_bin;

    //////////////////////////////////////////////////////////////////////
    // peak 부터 우로 범위를 설정
    // 우측의 경계 찾기 (to_val)
    co_thresh = 0;
    for( i=peak_index+1 ;; ++i ) {
        // 우측의 끝에 도달 overgroup 발생
        if( i >= (int) m_AoaHist.bin_count ) {
            i -= m_AoaHist.bin_count;
            pAoaGroup->bOverAoa = TRUE;
        }

        // 전방위 그룹화
        // 시작 점인 peak_index 까지 해도 되지만 앞에서 찾았기 때문에
        // 계산한 좌측 범위 까지 검사한다.
        //-- 조철희 2005-04-27 18:17:04 --//
        if( i == aoa_bin )
            return TRUE;

        // 경계 조건
    if( m_AoaHist.hist[i] <= _sp.np.Aoa_Hist_Thr )
            ++ co_thresh;
        else
            co_thresh = 0;

        //-- 조철희 2005-11-22 11:14:58 --//
        if( co_thresh >= MIN_CONTI_THRESHOLD_AOA )
            break;
    }

    // 우 최소범위 경계조건 // 000210
    aoa_bin = i;
    if( peak_index < i ) {
        // 4시그마 이하
        if( i - peak_index < thr ) {
            aoa_bin = peak_index + thr;
        }
    }
    else if( peak_index > i ) {
        // 4 시그마 이하
        if( (int) ( m_AoaHist.bin_count - i ) - peak_index < thr ) {
            aoa_bin = peak_index + thr;
        }
    }
    // 우측의 끝에 도달 overgroup 발생
    if( aoa_bin >= (int) m_AoaHist.bin_count ) {
        aoa_bin -= m_AoaHist.bin_count;
        pAoaGroup->bOverAoa = TRUE;
    }
    to_bin = aoa_bin;

    // margin에 의한 전방위그룹 체크
    if( pAoaGroup->bOverAoa && ( to_bin >= from_bin ) )
        return TRUE;

    pAoaGroup->from_bin = from_bin;
    pAoaGroup->to_bin = to_bin;
    pAoaGroup->from_aoa = from_bin << nShift;
    pAoaGroup->to_aoa = to_bin << nShift;

    pAoaGroup->stat = m_nStat;
    pAoaGroup->band = m_nBand;

    return FALSE;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::ReDrawAoaHist
// 반환되는 형  : void
// 함 수 인 자  : STR_AOA_GROUP *pAoaGroup
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-27 18:53:03
//
//##ModelId=42757D4D0159
void CGroup::ReDrawAoaHist(STR_AOA_GROUP *pAoaGroup)
{
    UINT i;

    if (pAoaGroup->bOverAoa) {
        for (i = pAoaGroup->from_bin; i <= (UINT)(m_AoaHist.bin_count - 1); ++i)
            m_AoaHist.hist[i] = 0;
        for (i = 0; i <= pAoaGroup->to_bin; ++i)
            m_AoaHist.hist[i] = 0;
    }
    else {
        for (i = pAoaGroup->from_bin; i <= pAoaGroup->to_bin; ++i)
            m_AoaHist.hist[i] = 0;
    }
}

#endif

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::GetFrqRange
// 반환되는 형  : BOOL
// 함 수 인 자  : int peak_index
// 함 수 인 자  : int nShift
// 함 수 인 자  : int freqdiff
// 함 수 인 자  : STR_FRQ_GROUP *pFrqGroup
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-28 10:50:05
//
//##ModelId=42757D4D00C3
BOOL CGroup::GetFrqRange( int peak_index, int nShift, int freqdiff, STR_FRQ_GROUP *pFrqGroup )
{
    int i;
    int frq_bin;
    UINT max_freq_diff;

    // 1 GHz 주파수 값
#if defined(_ELINT_) || defined(_XBAND_)
    max_freq_diff = IFRQMhzCNV( 0, MAX_FREQ_DIFF );
#elif defined(_POCKETSONATA_)
    max_freq_diff = I_IFRQCNV( g_enBoardId, MAX_FREQ_DIFF );
#else
    max_freq_diff = abs( (int) IDIV( MAX_FREQ_DIFF, gFreqRes[ m_nBand+1 ].fRes ) );
#endif

    //////////////////////////////////////////////////////////////////////
    // peak부터 좌로 범위를 설정
    // 좌측의 경계 찾기 (start)
    for( i=peak_index-1 ; i >= 0 ; --i ) {
        // 경계 조건
        if( m_FrqHist.hist[i] <= _sp.np.Freq_Hist_Thr )
            break;

        // 좌 최대 범위
        if( ( ( peak_index - (i+1) ) << nShift ) >= (int) max_freq_diff )	// 1GHz 이상
        {
            printf( "\n [O] OverLeft1GHz");		WhereIs;
            break;
        }
    }
    frq_bin = _min( i+1 , (int) m_FrqHist.bin_count );

    /*! \bug  주파수 bin 값은 히스트그램 상에서 찾은 경계값까지 정한다.
            \date 2006-06-02 14:40:08, 조철희
    */
    // margin에 의한 경계 찾기
    pFrqGroup->from_frq = _max( 0, frq_bin << nShift );
    pFrqGroup->from_bin = frq_bin; /* pFrqGroup->from_frq >> nShift; */

    //////////////////////////////////////////////////////////////////////
    // peak부터 우로 범위를 설정
    for( i=peak_index+1 ; i < (int) m_FrqHist.bin_count ; ++i ) {
        // 경계 조건
        if( m_FrqHist.hist[i] <= _sp.np.Freq_Hist_Thr )
            break;

        // 우 최대 범위
        if( ( ( i - peak_index ) << nShift ) > (int) max_freq_diff ) {
            printf(" \n [O] OverRight1GHz" );		WhereIs;
            break;
        }
    }
    frq_bin = _max(0, i-1 );

    /*! \bug  주파수 bin 값은 히스트그램 상에서 찾은 경계값까지 정한다.
        \date 2006-06-02 14:41:03, 조철희
    */
    // margin에 의한 경계 찾기
    pFrqGroup->to_frq = _min( MAX_FREQ, ( frq_bin+1 ) << nShift );
    pFrqGroup->to_bin = frq_bin; // pFrqGroup->to_frq >> nShift;

    return TRUE;
}


//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::FilterParam
// 반환되는 형  : void
// 함 수 인 자  : STR_PDWINDEX *pGrPdwIndex
// 함 수 인 자  : UINT *pParam
// 함 수 인 자  : STR_AOA_GROUP *pAoaGroup
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-27 19:21:20
//
//##ModelId=42757D4D0131
void CGroup::FilterParam(STR_PDWINDEX *pGrPdwIndex, UINT *pParam, STR_AOA_GROUP *pAoaGroup )
{
    unsigned int i;
    USHORT index;
    PDWINDEX *pPdwIndex;
    PDWINDEX *pAoaPdwIndex;

    UINT low, high;

    low = pAoaGroup->from_aoa;
    high = pAoaGroup->to_aoa;

    // 초기화
    pAoaGroup->iCount = 0;
    pAoaPdwIndex = pAoaGroup->pIndex;

    pPdwIndex = pGrPdwIndex->pIndex;
    if( pAoaGroup->bOverAoa ) {
        for( i=0 ; i < pGrPdwIndex->uiCount ; i++ )	{
            index = *pPdwIndex++;

            // 추출된 펄스가 아니면 통과
            if( m_pMARK[ index ] != EXTRACT_MARK ) {
                // 범위 조사
                if( pParam[index] >= low || pParam[index] <= high ) {
                    *pAoaPdwIndex++ = index;
                    ++ pAoaGroup->iCount;
                }
            }
        }
    }
    else {
        for( i=0 ; i < pGrPdwIndex->uiCount ; i++ )	{
            index = *pPdwIndex++;

            // 추출된 펄스가 아니면 통과
            if( m_pMARK[ index ] != EXTRACT_MARK ) {
                // 범위 조사
                if( pParam[index] >= low && pParam[index] <= high ) {
                    *pAoaPdwIndex++ = index;
                    ++ pAoaGroup->iCount;
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::FilterParam
// 반환되는 형  : void
// 함 수 인 자  : STR_AOA_GROUP *pAoaGroup
// 함 수 인 자  : UINT *pParam
// 함 수 인 자  : STR_FRQ_GROUP *pFrqGroup
// 함 수 인 자  : STR_PDWINDEX *pFrqAoaPwIndex
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-28 16:47:38
//
//##ModelId=42757D4D007D
void CGroup::FilterParam(STR_AOA_GROUP *pAoaGroup, UINT *pParam1, UINT *pParam2, STR_FRQ_GROUP *pFrqGroup, STR_PW_GROUP *pPwGroup, STR_PDWINDEX *pFrqAoaPwIndex )
{
    int i;
    PDWINDEX *pPdwIndex;
    PDWINDEX *pDstIndex;

    pFrqAoaPwIndex->uiCount = 0;	// 초기화
    pPdwIndex = pAoaGroup->pIndex;
    pDstIndex = pFrqAoaPwIndex->pIndex;
    for( i=0 ; i < pAoaGroup->iCount ; i++, ++pPdwIndex ) {
        // 추출된 펄스가 아니면 통과
        // if( MARK[ *pPdwIndex ] != EXTRACT_MARK )
        {
            // 범위 조사
            if( ( pParam1[*pPdwIndex] >= pFrqGroup->from_frq && pParam1[*pPdwIndex] <= pFrqGroup->to_frq ) &&
                    ( pParam2[*pPdwIndex] >= pPwGroup->from_pw && pParam2[*pPdwIndex] <= pPwGroup->to_pw ) ) {
                *pDstIndex++ = *pPdwIndex;
                ++ pFrqAoaPwIndex->uiCount;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::ReDrawFrqHist
// 반환되는 형  : void
// 함 수 인 자  : STR_FRQ_GROUP *pFrqGroup
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-28 15:20:08
//
//##ModelId=42757D4D00B0
void CGroup::ReDrawFrqHist( STR_FRQ_GROUP *pFrqGroup )
{
    //구한 범위내의 히스토값의 삭제
    for( UINT i=pFrqGroup->from_bin ; i <= pFrqGroup->to_bin ; ++i )
        m_FrqHist.hist[i] = 0;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::MakeGrIndex
// 반환되는 형  : BOOL
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-28 15:58:25
//
//##ModelId=42757D4D00AF
BOOL CGroup::MakeGrIndex()
{
    STR_AOA_GROUP *pAoaGroup;
    STR_FRQ_GROUP *pFrqGr;
    STR_PW_GROUP *pPwGr;

    // 그룹화열 초기화
    m_FrqAoaPwIdx.uiCount = 0;

    // 다음 FGRT 선택
    pPwGr = & m_PwGroups.pw[ m_uiCoFrqAoaPwIdx ];
    pFrqGr = & m_FrqGroups.frq[ pPwGr->frq_idx ];
    pAoaGroup = & m_AoaGroups.aoa[ pFrqGr->aoa_idx ];

    m_nBand = pAoaGroup->band;
    m_nStat = pAoaGroup->stat;

    // 방위, 주파수, 펄스폭 그룹화 영역 필터링
    FilterParam( pAoaGroup, & m_pFREQ[0], & m_pPW[0], pFrqGr, pPwGr, & m_FrqAoaPwIdx );

    PrintGroup();

#ifdef _MSC_VER
    // 방위 그룹화 출력
// 	printf( "\n //////////////////////////////////////////////////////////////////////////"	);
// 	if( pFrqGr->narrow_wide == FALSE )
// 		printf( "\n\t 방위 및 주파수 협대역 그룹화[%d]" , m_CoFrqAoaPwIdx );
// 	else
// 		printf( "\n\t 방위 및 주파수 광대역 그룹화[%d]" , m_CoFrqAoaPwIdx );
// 	printf( "\n\t\t 신호 개수(%3d), " , m_FrqAoaPwIdx.count );
// 	printf( "방위(%3d-%3d), " , AOACNV( pAoaGroup->from_aoa ), AOACNV( pAoaGroup->to_aoa ) );
// 	if( m_nBand == BAND2 || m_nBand == BAND3 || m_nBand == BAND5 )
// 		printf( "주파수[MHz](%4d-%4d), " , FRQMhzCNV( m_nBand, pFrqGr->to_frq ), FRQMhzCNV( m_nBand, pFrqGr->from_frq ) );
// 	else
// 		printf( "주파수[MHz](%4d-%4d), " , FRQMhzCNV( m_nBand, pFrqGr->from_frq ), FRQMhzCNV( m_nBand, pFrqGr->to_frq ) );
// 	printf( "펄스폭[us](%4d-%4d)" , PWCNV( pPwGr->from_pw ), PWCNV( pPwGr->to_pw ) );

#endif

    ++ m_uiCoFrqAoaPwIdx;

    return m_FrqAoaPwIdx.uiCount != _spZero;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 그룹화할 인덱스인 m_CoFrqAoaIdx의 방위 그룹화 인덱스와 입력 변수인
//!					 nAoaIdx과 같은 값인지를 리턴한다.
//!	\author  조철희
//!	\param	 nAoaIdx	인자형태 int
//!	\param	 narrow_or_wide	인자형태 int
//!	\return	 BOOL
//! \version 1.0
//! \date		 2006-06-01 10:41:54
//! \warning
//
// bool CGroup::IsSameAoaIdx( int nAoaIdx, UINT narrow_or_wide )
// {
//     bool bRet;
//     STR_FRQ_GROUP *pFrqGr;
// 
//     if( m_uiCoFrqAoaPwIdx >= m_FrqGroups.uiCount ) {
//         bRet = false;
//     }
//     else {
//         pFrqGr = & m_FrqGroups.frq[m_uiCoFrqAoaPwIdx];
// 
//         if( pFrqGr->narrow_wide != (char) narrow_or_wide ) {
//             printf( "\n\n //////////////////////////////////////////////////////////////////////////"	);
//             printf( "\n\t 방위 그룹화 인덱스 없음." );
// 
//             bRet = false;
//         }
//         else {
//             printf( "\n\n //////////////////////////////////////////////////////////////////////////"	);
//             printf( "\n\t 방위 그룹화 인덱스: %d" , nAoaIdx );
// 
//             bRet = ( pFrqGr->aoa_idx == nAoaIdx );
//         }
// 
//     return bRet;
// 
// }

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CGroup::IsLastGroup
//!	\author  조철희
//!	\return	 BOOL
//! \version 1.0
//! \date		 2006-06-01 10:49:47
//! \warning
//
bool CGroup::IsLastGroup()
{
    bool bRet=false;

    if( m_uiCoFrqAoaPwIdx >= m_PwGroups.uiCount ) {
        bRet = true;
    }

    return bRet;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::IsLastGroup
// 반환되는 형  : BOOL
// 함 수 인 자  : int index
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2007-06-18 09:09:01
//
bool CGroup::IsLastGroup( unsigned int uiIndex )
{
    bool bRet=false;

    if( uiIndex >= m_PwGroups.uiCount ) {
        bRet = true;
    }

    return bRet;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::SaveFrqAoaPeak
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-24 00:19:05
//
//##ModelId=429A5BDD0021
void CGroup::SaveFrqAoaPeak()
{
    if( m_FrqAoaPeak.enable == FALSE ) {
        m_FrqAoaPeak.aoa.iLow = m_AoaGroups.aoa[0].from_aoa;
        m_FrqAoaPeak.aoa.iHgh = m_AoaGroups.aoa[0].to_aoa;
        m_FrqAoaPeak.frq.iLow = m_FrqGroups.frq[0].from_frq;
        m_FrqAoaPeak.frq.iHgh = m_FrqGroups.frq[0].to_frq;
        m_FrqAoaPeak.band	= m_nBand;
        m_FrqAoaPeak.tot_cnt = m_nCoPdw;
        m_FrqAoaPeak.count = m_FrqAoaPwIdx.uiCount;

        m_FrqAoaPeak.enable = TRUE;
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::LastOneAoaGroup
// 반환되는 형  : BOOL
// 함 수 인 자  : int noGroup
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-14 19:07:51
//
//##ModelId=42E85F3903C8
BOOL CGroup::LastOneAoaGroup( int noGroup )
{
    return m_FrqGroups.frq[ noGroup ].end_of_aoagroup;
}

//////////////////////////////////////////////////////////////////////
// 아래 함수들은 추적에서 사용할 그룹화 멤버 함수들입니다.

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::MakeFreqAoaPwGroup
// 반환되는 형  : void
// 함 수 인 자  : STR_PDWINDEX *pStatGrPdwIndex
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-27 15:57:06
//
//##ModelId=42E85F390333
void CGroup::MakeFreqAoaPwGroup( STR_PDWINDEX *pStatGrPdwIndex )
{
    STR_AOA_GROUP *pAoaGroup;
    STR_FRQ_GROUP *pFrqGroup;
    STR_PW_GROUP *pPwGroup;

    // 방위 그룹화 기록
    pAoaGroup = & m_AoaGroups.aoa[ m_AoaGroups.uiCount ];

    // 전방위 그룹화 될 때의 방위 그룹화 범위
    _EQUALS3( pAoaGroup->from_bin, pAoaGroup->from_aoa, 0 )
    _EQUALS3( pAoaGroup->to_bin, pAoaGroup->to_aoa, MAX_AOA-1 )
    pAoaGroup->stat = m_nStat;
    pAoaGroup->bOverAoa = FALSE;
    pAoaGroup->band = m_nBand;

    FilterParam( pStatGrPdwIndex, & m_pAOA[0], pAoaGroup );

    // 펄스폭 그룹화 기록
    pPwGroup = & m_PwGroups.pw[ m_PwGroups.uiCount ];
    pPwGroup->from_bin = 0;
    pPwGroup->to_bin = ( MAX_PW - 1 ) >> PW_SHIFT_CNT;
    pPwGroup->from_pw = 0;
    pPwGroup->to_pw = MAX_PW - 1;

    pPwGroup->frq_idx = m_FrqGroups.uiCount;

    // 주파수 그룹화 초기화
    pFrqGroup = & m_FrqGroups.frq[ m_FrqGroups.uiCount ];

    // 방위 그룹화 PDW STAT, 밴드, 오버방위 저장
    pFrqGroup->aoa_idx = m_AoaGroups.uiCount;
    pFrqGroup->narrow_wide = _FULL;
    pFrqGroup->end_of_aoagroup = FALSE;
    _EQUALS3( pFrqGroup->from_frq, pFrqGroup->from_bin, 0 )
    _EQUALS3( pFrqGroup->to_frq, pFrqGroup->to_bin, MAX_FREQ )

    ++ m_AoaGroups.uiCount;
    ++ m_FrqGroups.uiCount;
    ++ m_PwGroups.uiCount;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::ISODATA
// 반환되는 형  : void
// 함 수 인 자  : STR_PDWINDEX *pSrcIndex
// 함 수 인 자  : UINT *pPdw
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-28 13:23:43
//
#if defined(_ELINT_) || defined(_XBAND_)
#define		MAXIMUM_STANDARD_DEVIATION		UMUL( 2, _spRxdfAoa )		// 대역중에서 가장 큰 방위 오차
#define		MAXIMUM_DISTANCE_OF_CLUSTERS	UMUL( 2, _spRxdfAoa )		// 클러스터 사이간의 최대 길이

#elif defined(_POCKETSONATA_)
#define		MAXIMUM_STANDARD_DEVIATION		UMUL( 2, KHARM_AOA_MAR )		// 대역중에서 가장 큰 방위 오차
#define		MAXIMUM_DISTANCE_OF_CLUSTERS	UMUL( 2, KHARM_AOA_MAR )		// 클러스터 사이간의 최대 길이

#else
#define		MAXIMUM_STANDARD_DEVIATION		UMUL( 2, _spRxdfAoaLow )		// 대역중에서 가장 큰 방위 오차
#define		MAXIMUM_DISTANCE_OF_CLUSTERS	UMUL( 2, _spRxdfAoaLow )		// 클러스터 사이간의 최대 길이
#endif

#define		NUMBER_OF_CLUSTER							( MAX_AOA_GROUP )						// 최대 클러스터 개수
#define		MINIMUM_NUMBER_OF_SAMPLES			( RJGPC )										// 클러스터 내의 가장 작은 샘플 개수
#define		NUMBER_OF_ITERATIONS					( 7 )
#define		SPLIT_RATIO										( 0.6 )
void CGroup::ISODATA( STR_PDWINDEX *pSrcIndex, UINT *pPdw )
{
    unsigned int i, j, k;
    int nSplitCluster;

    STR_CLUSTER *pCluster;

    //-- 조철희 2006-01-05 10:54:31 --//
    if( pSrcIndex->uiCount <= MINIMUM_NUMBER_OF_SAMPLES ) {
        m_uiClusters = 0;
        return;
    }

    // 초기화
    m_pPdwParam = pPdw;
    m_uiClusters = _spOne;
    pCluster = & m_pCluster[0];
    pCluster->iCount = pSrcIndex->uiCount;
    memcpy( pCluster->index, pSrcIndex->pIndex, sizeof(PDWINDEX)*pCluster->iCount );

    CalClusterInfo( pCluster );

    // 클러스터링 시작
    for( i=0 ; i < NUMBER_OF_ITERATIONS ; ++i ) {
        //
        nSplitCluster = 0;
        pCluster = & m_pCluster[0];
        for( j=0 ; j < m_uiClusters ; ++j ) {
            if( TRUE == SplitCenter( pCluster, & m_pCluster[MAX_AGRT-2] ) ) {
                for( k=m_uiClusters+nSplitCluster-1 ; k >= j+nSplitCluster+1 ; --k ) {
                    memcpy( & m_pCluster[k+1], & m_pCluster[k], sizeof( STR_CLUSTER ) );
                }
                memcpy( pCluster++, & m_pCluster[MAX_AGRT-1], sizeof( STR_CLUSTER ) );
                memcpy( pCluster++, & m_pCluster[MAX_AGRT-2], sizeof( STR_CLUSTER ) );

                ++ nSplitCluster;
            }
            else {
                ++ pCluster;
            }
        }

        if( nSplitCluster == 0 )
            break;

        m_uiClusters = m_uiClusters + nSplitCluster;
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::SplitCenter
// 반환되는 형  : void
// 함 수 인 자  : STR_CLUSTER *pCluster
// 함 수 인 자  : STR_CLUSTER *pDstCluster
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-28 16:28:43
//
BOOL CGroup::SplitCenter( STR_CLUSTER *pCluster, STR_CLUSTER *pDstCluster )
{
    STR_CLUSTER *pCluster1, *pCluster2;

    /*! \bug  방위 그룹화 범위를 체크해서 빈 영역이 없는지를 검사한다.
        \date 2006-08-18 10:25:24, 조철희
    */
    pCluster1 = ( STR_CLUSTER * ) ( pDstCluster - pCluster );
    if( pCluster1 <= (STR_CLUSTER *) 1 ) {
        printf( "\n [W] 클러스터링 버퍼가 부족합니다." );
        return FALSE;
    }

    pCluster1 = pDstCluster++;
    pCluster2 = pDstCluster;

    if( pCluster->deviation > (float) MAXIMUM_STANDARD_DEVIATION ) {
        pCluster1->center = AddAOA( pCluster->center, UMUL( pCluster->deviation, SPLIT_RATIO ) );
        pCluster2->center = SubAOA( pCluster->center, UMUL( pCluster->deviation, SPLIT_RATIO ) );

        ReCluster( pCluster1, pCluster2, pCluster );
        CalClusterInfo( pCluster1 );
        CalClusterInfo( pCluster2 );

        // 클러스터 내의 모든 개수가 최소 클러스터 개수보다 커야 분리된다.
        // if( pCluster1->count > MINIMUM_NUMBER_OF_SAMPLES && pCluster2->count > MINIMUM_NUMBER_OF_SAMPLES )
        //-- 조철희 2006-01-04 15:52:41 --//
        return TRUE;
    }

    return FALSE;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::ReCluster
// 반환되는 형  : void
// 함 수 인 자  : STR_CLUSTER *pDstCluster1
// 함 수 인 자  : STR_CLUSTER *pDstCluster2
// 함 수 인 자  : STR_CLUSTER *pSrcCluster
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-29 10:39:58
//
void CGroup::ReCluster( STR_CLUSTER *pDstCluster1, STR_CLUSTER *pDstCluster2, STR_CLUSTER *pSrcCluster )
{
    int i;
    int diff1, diff2;
    int center1, center2;

    int overVal;

    PDWINDEX *pCIndex;
    PDWINDEX *pDstCIndex1, *pDstCIndex2;

    pCIndex = & pSrcCluster->index[0];
    pDstCIndex1 = & pDstCluster1->index[0];
    pDstCIndex2 = & pDstCluster2->index[0];

    _EQUALS3( pDstCluster1->iCount, pDstCluster2->iCount, 0 )
    center1 = pDstCluster1->center;
    center2 = pDstCluster2->center;
    for( i=0 ; i < pSrcCluster->iCount ; ++i ) {
        diff1 = (int) m_pAOA[ *pCIndex ] - center1;
        overVal = _abs( diff1 );
        if( overVal > MAX_AOA/2 ) {
            if( center1 > MAX_AOA/2 )
                diff1 = diff1 + MAX_AOA;
            else
                diff1 = diff1 - MAX_AOA;
        }
        diff1 = _abs( diff1 );

        diff2 = (int) m_pAOA[ *pCIndex ] - center2;
        overVal = _abs( diff2 );
        if( overVal > MAX_AOA/2 ) {
            if( center2 > MAX_AOA/2 )
                diff2 = diff2 + MAX_AOA;
            else
                diff2 = diff2 - MAX_AOA;
        }
        diff2 = _abs( diff2 );

        if( diff1 < diff2 ) {
            *pDstCIndex1++ = *pCIndex++;
            ++ pDstCluster1->iCount;
        }
        else {
            *pDstCIndex2++ = *pCIndex++;
            ++ pDstCluster2->iCount;
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::CalClusterInfo
// 반환되는 형  : void
// 함 수 인 자  : STR_CLUSTER *pCluster
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-28 14:39:14
//
void CGroup::CalClusterInfo( STR_CLUSTER *pCluster )
{
    int i;
    int diffVal, overVal, meanVal, frstVal;

    double dMeanVal;
    PDWINDEX *pCIndex;

    // 방위 평균 계산
    pCluster->aoa.iHgh = -9999999;
    pCluster->aoa.iLow = 0xffffff;

    meanVal = 0;
    pCIndex = & pCluster->index[0];
    frstVal = m_pPdwParam[ *pCIndex++ ];
    for( i=1 ; i < pCluster->iCount ; ++i ) {
        diffVal = (int) m_pAOA[ *pCIndex++ ] - frstVal;
        overVal = _abs( diffVal );
        if( overVal > MAX_AOA/2 ) {
            if( frstVal > MAX_AOA/2 ) {
                diffVal = diffVal + MAX_AOA;
            }
            else {
                diffVal = diffVal - MAX_AOA;
            }
        }

        meanVal += diffVal;

        pCluster->aoa.iHgh = _max( pCluster->aoa.iHgh, diffVal );
        pCluster->aoa.iLow = _min( pCluster->aoa.iLow, diffVal );
    }
    pCluster->aoa.iHgh = ( MAX_AOA + pCluster->aoa.iHgh + frstVal ) % MAX_AOA;
    pCluster->aoa.iLow = ( MAX_AOA + pCluster->aoa.iLow + frstVal ) % MAX_AOA;
    pCluster->center = ( MAX_AOA + IDIV( meanVal, pCluster->iCount ) + frstVal ) % MAX_AOA;

    // 방위 거리 계산
    meanVal = 0;
    frstVal = pCluster->center;
    pCIndex = & pCluster->index[0];
    for( i=0 ; i < pCluster->iCount ; ++i ) {
        diffVal = (int) m_pAOA[ *pCIndex++ ] - frstVal;
        overVal = _abs( diffVal );
        if( overVal > MAX_AOA/2 ) {
            if( frstVal > MAX_AOA/2 )
                diffVal = diffVal + MAX_AOA;
            else
                diffVal = diffVal - MAX_AOA;
        }

        meanVal += _abs( diffVal );
    }
    pCluster->distance = FDIV( meanVal, pCluster->iCount );

    // 방위 편차 계산
    dMeanVal = 0.;
    frstVal = pCluster->center;
    pCIndex = & pCluster->index[0];
    for( i=0 ; i < pCluster->iCount ; ++i ) {
        diffVal = (int) m_pAOA[ *pCIndex++ ] - frstVal;
        overVal = _abs( diffVal );
        if( overVal > MAX_AOA/2 ) {
            if( frstVal > MAX_AOA/2 )
                diffVal = diffVal + MAX_AOA;
            else
                diffVal = diffVal - MAX_AOA;
        }

        dMeanVal += ( diffVal * diffVal );
    }
    if( dMeanVal < 0 ) {
        //printf( "\n [W] 방위 분산 계산 에러 !!!" );
        Log( enError, "[W] Error of AOA Deviation !!!" );
    }
    pCluster->deviation = (float) ( sqrt( dMeanVal / (double) pCluster->iCount ) );
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CGroup::IsSameAoaIdx
//! \author   조철희
//! \param    nAoaIdx 인자형태 int
//! \return   BOOL
//! \version  1.37
//! \date     2006-07-28 16:42:28
//! \warning
//
// bool CGroup::IsSameAoaIdx( int nAoaIdx )
// {
//     bool bRet;
//     STR_FRQ_GROUP *pFrqGroup;
// 
//     if( IsLastGroup() ) {
//         bRet = false;
//     }
//     else {
// 
//         pFrqGroup = & m_FrqGroups.frq[ m_uiCoFrqAoaPwIdx ];
// 
//         bRet = ( pFrqGroup->aoa_idx == nAoaIdx );
//     }
// 
//     return bRet;
// }

//////////////////////////////////////////////////////////////////////
//
//! \brief    펄스열 분리도를 높게 하기 위해서 주파수 그룹화를 세밀하게 수행한다.
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-18 12:11:12
//! \warning
//
// void CGroup::FineFreqGroup()
// {
//     int peak_index;
// 
//     MakeHist( & m_FrqAoaPwIdx, & m_pFREQ[0], FREQ_NARR_SHIFT_CNT, & m_FrqHist );
// 
//     // for( ;; ) {
//     {
//         peak_index = FindPeakInHist( m_FrqHist.bin_count, & m_FrqHist.hist[0] );
//     }
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGroup::CompMarginDiff
        \author   조철희
        \param    x 인자형태 int
        \param    y1 인자형태 int
        \param    y2 인자형태 int
        \param    thresh 인자형태 int
        \return   BOOL
        \version  0.0.1
        \date     2008-01-03 15:20:55
        \warning
*/
// BOOL CGroup::CompMarginDiff(int x, int y1, int y2, int thresh)
// {
//     BOOL bRet;
// 
//     if( x >= y1-thresh && x <= y2+thresh ) {
//         bRet = TRUE;
//     }
//     else {
//         bRet = FALSE;
//     }
// 
//     return bRet;
// }
// 
