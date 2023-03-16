// Group.cpp: implementation of the CGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#ifdef _MSC_VER
// PC용 상위 클래스에 전달하기 위한 선언
//#include "../../A50SigAnal/stdafx.h"

#endif



#if defined(_ELINT_) || defined(_XBAND_)
//#include "../OFP_Main.h"

#elif defined(_POCKETSONATA_)
#include "../Identify/ELUtil.h"

#else

#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "Group.h"

#include "../OFP_Main.h"

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

    m_uiMaxPdw = (UINT) min( (int) uiCoMaxPdw, (int) MAX_PDW );

	// 주파수 해상도 계산용, HARMONIC MARGIN
#if defined(_ELINT_) || defined(_XBAND_) || defined(_701_)
	m_stSigma1Aoa[0] = ( unsigned int ) KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC1] = ( unsigned int ) KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC2] = ( unsigned int ) KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC3] = ( unsigned int ) KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC4] = ( unsigned int ) KHARM_AOA_MAR;

#ifdef _XBAND_
	strcpy( m_szPulseType[i++], "CW" );
	strcpy( m_szPulseType[i], "NP" );
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
	m_stSigma1Aoa[enPRC1] = (unsigned int) KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC2] = ( unsigned int ) KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC3] = ( unsigned int ) KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC4] = ( unsigned int ) KHARM_AOA_MAR;
	m_stSigma1Aoa[enPRC5] = ( unsigned int ) KHARM_AOA_MAR;

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
        m_AoaGroups.stAOA[i].pPDWIndex = ( PDWINDEX * ) malloc( sizeof( PDWINDEX ) * m_uiMaxPdw );
        if( m_AoaGroups.stAOA[i].pPDWIndex == NULL ) {
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
        free( m_AoaGroups.stAOA[i].pPDWIndex );
    }

    free( m_FrqAoaPwIdx.pIndex );

    for( i=0 ; i < TOTAL_BAND ; ++i ) {
        free( m_Band[i].pIndex );
    }

    free( m_pCluster );
}

/**
 * @brief     그룹화 객체를 초기화한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-04-26 18:18:23
 * @warning
 */
void CGroup::Init()
{
    // 펄스 수집 개수
    m_uiCoPdw = GetColPdw();

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
        *pMark++ = enUnMark;
        *pMaxChannel++ = pdw->x.max_channel;

        // *pPmop++ = pdw->item.pmop;
        // *pBand++ = pdw->item.band;
        *pBand++ = pdw->x.band;
    }
}

//#elif defined(_ELINT_) || defined(_POCKETSONATA_) || defined(_XBAND_)
#else
/**
 * @brief     PDW 구조체 데이터를 각 항목별로 어레이로 복사한다.
 * @param     _PDW * pPDW
 * @param     unsigned int uiCount
 * @param     int iBand
 * @return    bool
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-11-01 15:02:38
 * @warning
 */
bool CGroup::MakePDWArray( _PDW *pPDW, unsigned int uiCount, unsigned int uiBand )
{
    bool bRet=true;

    unsigned int i;
	//_TOA templlTOA; // , prevllTOA;

    BOOL flagBand;

    _TOA *pToa;
    int *pPa;
    UINT *pAoa, *pPw, *pFreq;

    UCHAR *pStat, *pBand;
    USHORT *pMark;

    UCHAR *pPmop, *pFmop, *pMaxChannel;

    pPmop = & m_pPMOP[0];
    pFmop = & m_pFMOP[0];
    pMaxChannel = & m_pMAXCHANNEL[0];
   
    pToa = & m_pTOA[0];
    pStat = & m_pSTAT[0];
    pPa = & m_pPA[0];
    pAoa = & m_pAOA[0];
    pPw = & m_pPW[0];
    pFreq = & m_pFREQ[0];
    pMark = & m_pMARK[0];
    pBand = & m_pBAND[0];


    // 첫번째 TOA 얻기
	//templlTOA = pPDW->ullTOA;

    flagBand = FALSE;

    for( i=0 ; i < uiCount; ++i, ++pPDW )	{
        //templlTOA = pPDW->ullTOA;

        *pToa++ = pPDW->ullTOA;

        *pStat++ = (unsigned char) pPDW->iPulseType;
        *pPa++ = ( int ) pPDW->uiPA;
        *pAoa++ = pPDW->uiAOA;
        *pPw++ = pPDW->uiPW;
        *pFreq++ = pPDW->uiFreq;
        *pMark++ = ( USHORT ) enUnMark;

        if( g_enUnitType == en_ZPOCKETSONATA ) {
            *pPmop++ = ( unsigned char ) pPDW->x.ps.iPMOP;
            *pFmop++ = ( unsigned char ) pPDW->x.ps.iFMOP;
            *pMaxChannel++ = ( unsigned char ) pPDW->x.ps.iChannel;
        }

        *pBand++ = (UCHAR) uiBand; // 0; // g_enBoardId;


    }

    return bRet;
}

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
    const STR_FRQ_GROUP *p1, *p2;

    p1 = (const STR_FRQ_GROUP *) arg1;
    p2 = ( const STR_FRQ_GROUP *) arg2;

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
    m_AoaGroups.uiCoAnal = 0;
    m_FrqGroups.uiCount = 0;
    m_FrqGroups.uiCoAnal = 0;
    m_PwGroups.uiCount = 0;
    m_PwGroups.coAnal = 0;

    MakeBandGroup();

    // 밴드별 PDW STAT 그룹화
#ifdef _SONATA_
    for (i = ALL_BAND - 1; i >= BAND1; --i) {
        m_nBand = i;
        MakeStatGroup(&m_Band[i]);

        if (m_GrStat[STAT_CW].uiCount > _sp.cm.uiCw_Min_Cnt) {
            m_nStat = STAT_CW;

            // 방위 그룹화 만들기
            MakeAOAGroup(&m_GrStat[STAT_CW], true);

            MakeFreqGroup(true);

            MakePWGroup(true);
        }
        else {
            // PDW 상태별 그룹화
            for (int j = 0; j < MAX_STAT; ++j) {
                if (j == STAT_CW) {
                    continue;
                }

                m_nStat = j;
                // 방위 그룹화 만들기
                MakeAOAGroup(&m_GrStat[j]);
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

            MakePWGroup(true);
        }
    }

#else

#ifdef _POCKETSONATA_
    m_nBand = g_enBoardId;
#else
    m_nBand = 0;
#endif

    i = GetBand();
    MakeStatGroup(&m_Band[i]);

    if (m_GrStat[STAT_CW].uiCount > _sp.cm.uiCw_Min_Cnt) {
        m_nStat = STAT_CW;

        // 방위 그룹화 만들기
        MakeAOAGroup(&m_GrStat[STAT_CW], true);

        MakeFreqGroup(true);

        MakePWGroup(true);
    }
    else {
        // PDW 상태별 그룹화
        for (int j = 0; j < MAX_STAT; ++j) {
            if (j == STAT_CW) {
                continue;
            }

            m_nStat = j;
            // 방위 그룹화 만들기
            MakeAOAGroup(&m_GrStat[j]);
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

        MakePWGroup(true);

    }

#endif

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
    unsigned int uiIdxFrqAoaPw=0;

    STR_AOA_GROUP *pAoaGroup;
    STR_FRQ_GROUP *pFrqGr;
    STR_PW_GROUP *pPwGr;

    if( ! IsLastGroup( uiIdxFrqAoaPw ) ) {
        Log( enDebug, "=====================================================================================================" );
        Log( enNormal, "그룹화 총 개수 : %d" , m_PwGroups.uiCount );

        while (!IsLastGroup( uiIdxFrqAoaPw )) {
            int nBand;

            // 다음 FGRT 선택
            pPwGr = &m_PwGroups.pw[uiIdxFrqAoaPw];
            pFrqGr = &m_FrqGroups.stFreq[pPwGr->frq_idx];
            pAoaGroup = &m_AoaGroups.stAOA[pFrqGr->iIdxAOA];

#ifdef _POCKETSONATA_
            nBand = g_enBoardId;
#else
            nBand = pAoaGroup->uiBand;
#endif

            // 방위, 주파수, 펄스폭 그룹화 영역 필터링
            FilterParam(pAoaGroup, &m_pFREQ[0], &m_pPW[0], pFrqGr, pPwGr, &m_FrqAoaPwIdx);

            // 방위 그룹화 출력
            if (pFrqGr->narrow_wide == FALSE) {
                //printf( "\n\t [%d] 방위 및 주파수 협대역 그룹화, 신호 개수(%3d), 방위(%3d-%3d), 주파수[MHz](%4d-%4d), 펄스폭[us](%4d-%4d)" , IdxFrqAoaPw, m_FrqAoaPwIdx.count, AOACNV( pAoaGroup->from_aoa ), AOACNV( pAoaGroup->to_aoa ), FRQMhzCNV( nBand, pFrqGr->from_frq ), FRQMhzCNV( nBand, pFrqGr->to_frq ), PWCNV( pPwGr->from_pw ), PWCNV( pPwGr->to_pw ) );
                Log(enDebug, "\t\t[%ld] 협대역 %s[%d]: Co(%3d), A(%3d-%3d), F[MHz](%4d-%4d), PW[ns](%6d-%6d)", uiIdxFrqAoaPw, m_szPulseType[pAoaGroup->uiStat], pAoaGroup->uiStat, m_FrqAoaPwIdx.uiCount, I_AOACNV(pAoaGroup->iFromAOA), I_AOACNV(pAoaGroup->iToAOA), I_FRQMhzCNV(nBand, pFrqGr->uiFromFRQ), I_FRQMhzCNV(nBand, pFrqGr->uiToFRQ), IPWCNV( (int) pPwGr->uiFromPW), IPWCNV((int) pPwGr->uiToPW));
            }
            else {
                //printf( "\n\t [%d] 방위 및 주파수 광대역 그룹화, 펄스(%d), 신호 개수(%3d), 방위(%.1f-%.1f), 주파수[MHz](%4d-%4d), 펄스폭[us](%4d-%4d)" , IdxFrqAoaPw, m_nStat, m_FrqAoaPwIdx.count, CPOCKETSONATAPDW::DecodeDOA( pAoaGroup->from_aoa ), CPOCKETSONATAPDW::DecodeDOA( pAoaGroup->to_aoa ), CPOCKETSONATAPDW::DecodeFREQMHz(pFrqGr->from_frq), CPOCKETSONATAPDW::DecodeFREQMHz(pFrqGr->to_frq), CPOCKETSONATAPDW::DecodePWus( pPwGr->from_pw ), CPOCKETSONATAPDW::DecodePWus( pPwGr->to_pw ) );
                Log(enDebug, "\t\t[%ld] 광대역 %s[%d]: Co(%3d), A(%3d-%3d), F[MHz](%4d-%4d), PW[ns](%6d-%6d)", uiIdxFrqAoaPw, m_szPulseType[pAoaGroup->uiStat], pAoaGroup->uiStat, m_FrqAoaPwIdx.uiCount, I_AOACNV(pAoaGroup->iFromAOA), I_AOACNV(pAoaGroup->iToAOA), I_FRQMhzCNV(nBand, pFrqGr->uiFromFRQ), I_FRQMhzCNV(nBand, pFrqGr->uiToFRQ), IPWCNV( (int) pPwGr->uiFromPW), IPWCNV((int) pPwGr->uiToPW));
            }

#if defined(_ELINT_) || defined(_XBAND_) || defined(_701_)

#elif defined(_POCKETSONATA_)
            //printf( "주파수[MHz](%4d-%4d), " , CPOCKETSONATAPDW::DecodeFREQMHz(pFrqGr->from_frq), CPOCKETSONATAPDW::DecodeFREQMHz(pFrqGr->to_frq) );
#else
            if (nBand == BAND2 || nBand == BAND3) {
                printf("주파수[MHz](%4d-%4d), ", FRQMhzCNV(nBand, pFrqGr->uiToFRQ), FRQMhzCNV(nBand, pFrqGr->uiFromFRQ));
            }
            else {
                printf("주파수[MHz](%4d-%4d), ", FRQMhzCNV(nBand, pFrqGr->uiFromFRQ), FRQMhzCNV(nBand, pFrqGr->uiToFRQ));
            }
#endif

            ++uiIdxFrqAoaPw;
        }

    }
    else {
        Log( enDebug, "그룹화 총 개수 없음 !!!");
    }
#endif
    
}

/**
 * @brief     현재 그룹화 인덱스를 중심으로 그룹화 정보를 출력한다.
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
    pFrqGr = & m_FrqGroups.stFreq[ pPwGr->frq_idx ];
    pAoaGroup = & m_AoaGroups.stAOA[ pFrqGr->iIdxAOA ];

    Log( enDebug, "=====================================================================================================" );
    //printf( "\n [%d]번째 그룹화: 개수(%3d), 방위(%3d-%3d), 주파수[MHz](%4d-%4d), 펄스폭[us](%4d-%4d)" , m_CoFrqAoaPwIdx, m_FrqAoaPwIdx.count, AOACNV( pAoaGroup->from_aoa ), AOACNV( pAoaGroup->to_aoa ), FRQMhzCNV( m_nBand, pFrqGr->from_frq ), FRQMhzCNV( m_nBand, pFrqGr->to_frq ), PWCNV( pPwGr->from_pw ), PWCNV( pPwGr->to_pw ) );
    //LOG_LINEFEED;
    Log( enDebug, " [%d] GR: Co(%3d), A(%3d-%3d), F[MHz](%5d-%5d), PW[us](%6d-%6d)" , m_uiCoFrqAoaPwIdx, m_FrqAoaPwIdx.uiCount, I_AOACNV( pAoaGroup->iFromAOA ), I_AOACNV( pAoaGroup->iToAOA ), I_FRQMhzCNV( m_nBand, pFrqGr->uiFromFRQ ), I_FRQMhzCNV( m_nBand, pFrqGr->uiToFRQ ), IPWCNV((int)pPwGr->uiFromPW ), IPWCNV((int)pPwGr->uiToPW ) );

}

/**
 * @brief     주파수 그룹화를 수행한다.
 * @param     bool bForce1Group
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-07-27 16:29:47
 * @warning
 */
void CGroup::MakeFreqGroup( bool bForce1Group )
{
    int j;

    /*! \bug  주파수 그룹화는 좁게와 넓게로 구분해서 그룹화한다.
            \date 2006-05-30 18:40:11, 조철희
    */
    // 주파수 그룹 범위테이블 만들기
    for( j= ( int ) m_AoaGroups.uiCoAnal ; j < ( int ) m_AoaGroups.uiCount ; ++j ) {
#ifdef _FREQ_WIDE_NARROW_GROUP_
        int noGroups;

        noGroups = MakeFreqGroup( NARROW, j );
        m_FrqGroups.uiCoAnal = m_FrqGroups.uiCount;

        if( noGroups >= 2 ) {
            MakeFreqGroup( WIDE, j, 0, bForce1Group );

            m_FrqGroups.uiCoAnal = m_FrqGroups.uiCount;
        }
#else
        MakeFreqGroup( _WIDE, j, 0, bForce1Group );

#endif
    }

    m_AoaGroups.uiCoAnal = m_AoaGroups.uiCount;
}

/**
 * @brief     대역 그룹화를 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-07-27 10:53:30
 * @warning
 */
void CGroup::MakeBandGroup()
{
    unsigned int i;
    UCHAR *pBand;

    // 밴드 그룹화 초기화
    for( i=0 ; i < (unsigned int) TOTAL_BAND ; ++i ) {
        m_Band[i].uiCount = 0;
    }

    // 밴드 그룹화
    pBand = & m_pBAND[0];
    for( i=0 ; i < m_uiCoPdw ; ++i ) {
        if (m_pMARK[i] != enEXTRACT_MARK) {
            m_Band[*pBand].pIndex[m_Band[*pBand].uiCount++] = (PDWINDEX) i;	// Band 그룹화
            
        }
        ++pBand;
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
#if defined(_ELINT_) || defined(_701_)
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

    for( i=0 ; i < (unsigned int) MAX_STAT ; ++i ) {
        m_GrStat[i].uiCount = 0;
    }

    pPdwIndex = pBand->pIndex;

    for( i=0 ; i < pBand->uiCount ; ++i, ++pPdwIndex ) {
        if( m_pMARK[ *pPdwIndex ] != enEXTRACT_MARK) {
            switch (m_pSTAT[*pPdwIndex]) {
                case STAT_NORMAL:
                    *pNormalPdwIndex++ = *pPdwIndex;
                    ++m_GrStat[STAT_NORMAL].uiCount;
                    break;

                case STAT_CW:
                    *pCWPdwIndex++ = *pPdwIndex;
                    ++m_GrStat[STAT_CW].uiCount;
                    break;

#ifdef _ELINT_
                case STAT_FMOP:
                    *pFmopPdwIndex++ = *pPdwIndex;
                    ++m_GrStat[STAT_FMOP].uiCount;
                    break;

                case STAT_SHORTP:
                    *pShortPdwIndex++ = *pPdwIndex;
                    ++m_GrStat[STAT_SHORTP].uiCount;
                    break;
#elif defined(_XBAND_)
#elif defined(_POCKETSONATA_)
                case STAT_CHIRPDN:
                    *pChirpDnPdwIndex++ = *pPdwIndex;
                    ++m_GrStat[STAT_CHIRPDN].uiCount;
                    break;

                case STAT_CHIRPUP:
                    *pChirpUpPdwIndex++ = *pPdwIndex;
                    ++m_GrStat[STAT_CHIRPUP].uiCount;
                    break;

                case STAT_PMOP:
                    *pPmopPdwIndex++ = *pPdwIndex;
                    ++m_GrStat[STAT_PMOP].uiCount;
                    break;

#elif defined(_701_)
#else
                case STAT_CHIRPDN:
                    *pChirpDnPdwIndex++ = *pPdwIndex;
                    ++m_GrStat[STAT_CHIRPDN].uiCount;
                    break;

                case STAT_CHIRPUP:
                    *pChirpUpPdwIndex++ = *pPdwIndex;
                    ++m_GrStat[STAT_CHIRPUP].uiCount;
                    break;

                case STAT_PMOP:
                    *pPmopPdwIndex++ = *pPdwIndex;
                    ++m_GrStat[STAT_PMOP].uiCount;
                    break;

                case STAT_BIT:
                    *pBitPdwIndex++ = *pPdwIndex;
                    ++m_GrStat[STAT_BIT].uiCount;
                    break;
#endif

                default:
                    // printf( "\n invalid pdw stat[%d]" , STAT[*pPdwIndex] );
                    break;
            }
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

    if( pStatGrPdwIndex->uiCount > _spOne ) {
#ifdef _ISODATA_AOA_GROUP_
        unsigned int i;
        int diffVal, overVal, meanVal, frstVal;

        if( bForce1Group == true ) {
            PDWINDEX *pIndex = pStatGrPdwIndex->pIndex;

            pAoaGroup = &m_AoaGroups.stAOA[m_AoaGroups.uiCount];

            pAoaGroup->iToAOA = -9999999;
            pAoaGroup->iFromAOA = 0xffffff;

            meanVal = 0;
            frstVal = ( int ) m_pAOA[*pIndex];
            for( i = 0 ; i < pStatGrPdwIndex->uiCount ; ++i ) {
                diffVal = ( int ) m_pAOA[*pIndex++] - frstVal;
                overVal = _abs( diffVal );
                if( overVal > MAX_AOA / 2 ) {
                    if( frstVal > MAX_AOA / 2 )
                        diffVal = diffVal + MAX_AOA;
                    else
                        diffVal = diffVal - MAX_AOA;
                }

                meanVal += diffVal;

                pAoaGroup->iToAOA = _max( pAoaGroup->iToAOA, diffVal );
                pAoaGroup->iFromAOA = _min( pAoaGroup->iFromAOA, diffVal );
            }

            pAoaGroup->iToAOA = (MAX_AOA + pAoaGroup->iToAOA + frstVal) % MAX_AOA;
            pAoaGroup->iFromAOA = (MAX_AOA + pAoaGroup->iFromAOA + frstVal) % MAX_AOA;

            pAoaGroup->uiFromBin = (( UINT ) pAoaGroup->iFromAOA) >> AOA_SHIFT_COUNT;
            pAoaGroup->uiToBin = (( UINT ) pAoaGroup->iToAOA) >> AOA_SHIFT_COUNT;

            memcpy( pAoaGroup->pPDWIndex, pStatGrPdwIndex->pIndex, sizeof( PDWINDEX )*pStatGrPdwIndex->uiCount );
            pAoaGroup->iCount = pStatGrPdwIndex->uiCount;

            pAoaGroup->bOverAoa = false;

            pAoaGroup->uiStat = (UINT) m_nStat;
            pAoaGroup->uiBand = (UINT)m_nBand;

            ++m_AoaGroups.uiCount;

        }
        else {
            STR_CLUSTER *pCluster;

            // ISODATA - 클러스터링 알고리즘을 사용한 방위 클러스터링...
            //-- 조철희 2006-01-04 11:24:36 --//
            ISODATA( pStatGrPdwIndex, &m_pAOA[0] );

            pCluster = &m_pCluster[0];
            pAoaGroup = &m_AoaGroups.stAOA[m_AoaGroups.uiCount];
            for( i = 0 ; i < m_uiClusters ; ++i ) {
                pAoaGroup->bOverAoa = false;

                // 방위 그룹화의 방위 영역 설정
                pAoaGroup->iFromAOA = pCluster->stAOA.iLow;
                pAoaGroup->iToAOA = pCluster->stAOA.iHgh;
                pAoaGroup->uiFromBin = pCluster->stAOA.iLow >> AOA_SHIFT_COUNT;
                pAoaGroup->uiToBin = pCluster->stAOA.iHgh >> AOA_SHIFT_COUNT;

                memcpy( pAoaGroup->pPDWIndex, pCluster->pIndex, size_t( sizeof( PDWINDEX )*pCluster->iCount ) );
                pAoaGroup->iCount = pCluster->iCount;

                pAoaGroup->uiStat = m_nStat;
                pAoaGroup->uiBand = m_nBand;

                ++pAoaGroup;
                ++pCluster;
            }

            m_AoaGroups.uiCount += m_uiClusters;
        }

#else
        bool bRet;

        int peak_index;
        PDWINDEX peak_count;

        // 방위 히스토그램 계산
        MakeHist( pStatGrPdwIndex, &m_pAOA[0], (unsigned int) AOA_SHIFT_COUNT, &m_AoaHist );

        for( ;; ) {
            pAoaGroup = &m_AoaGroups.stAOA[m_AoaGroups.uiCount];

            if( m_AoaGroups.uiCount > MAX_AGRT ) {
				Log( enError, "방위 그룹이 초과 됐습니다.");
                break;
            }

            peak_index = FindPeakInHist( m_AoaHist.uiBinCount, &m_AoaHist.hist[0] );
            if( peak_index < 0 ) {
                break;
            }
            peak_count = m_AoaHist.hist[peak_index];

            // 종료 조건
            if( peak_count < _spAnalMinPulseCount ) {
                break;
            }

            // 방위 범위 구하기
            bRet = GetAOARange( peak_index, AOA_SHIFT_COUNT, pAoaGroup );

            FilterParam( pStatGrPdwIndex, &m_pAOA[0], pAoaGroup );

            ReDrawAoaHist( pAoaGroup );

            ++m_AoaGroups.uiCount;

            if( bRet == true && pAoaGroup->iCount >= (int) _spAnalMinPulseCount ) {
                break;
            }
        }

#endif

    }

}

/**
 * @brief     히스토그램에서 가장큰 피크 값을 찾는다.
 * @param     unsigned int uiCount
 * @param     PDWINDEX * pPdwIndex
 * @return    int
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-04-27 19:46:09
 * @warning
 */
int CGroup::FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex)
{
    unsigned int ui;
    int peak_index=-1, peak_count;

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

/**
 * @brief     모든 주파수 그룹화 결과에서 펄스폭 그룹화를 수행한다.
 * @param     bool bForce1Group
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-07-28 17:28:12
 * @warning
 */
void CGroup::MakePWGroup( bool bForce1Group )
{
    unsigned int i;

    for( i=m_FrqGroups.uiCoAnal ; i < m_FrqGroups.uiCount ; ++i ) {
        MakePWGroup( (int) i, bForce1Group );
    }

    m_FrqGroups.uiCoAnal = m_FrqGroups.uiCount;
}

/**
 * @brief     펄스폭 그룹화를 수행한다.
 * @param     int frqidx
 * @param     bool bForce1Group
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-06-02 14:53:08
 * @warning
 */
void CGroup::MakePWGroup( int frqidx, bool bForce1Group )
{
    STR_AOA_GROUP *pAoaGroup;
    STR_PW_GROUP *pPwGroup;
    STR_FRQ_GROUP *pFrqGroup;

    if( m_PwGroups.uiCount >= MAX_PGRT ) {
        Log( enError, "펄스폭 그룹화 인덱스의 최대 개수[%d]를 초과했습니다." , m_PwGroups.uiCount );
    }
	else {
		pFrqGroup = &m_FrqGroups.stFreq[frqidx];
		pAoaGroup = &m_AoaGroups.stAOA[pFrqGroup->iIdxAOA];

#ifndef _PW_GROUP_
		int i;
		PDWINDEX *pIndex;

		pPwGroup = &m_PwGroups.pw[m_PwGroups.uiCount];

		pPwGroup->frq_idx = frqidx;
		pPwGroup->uiFromBin = 0;
		pPwGroup->uiToBin = 0xFFFFFF;
		pIndex = pAoaGroup->pPDWIndex;
		pPwGroup->uiFromPW = m_pPW[*pIndex];
		pPwGroup->uiToPW = m_pPW[*pIndex];
		for (i = 0; i < pAoaGroup->iCount; ++i) {
			pPwGroup->uiFromPW = _min(pPwGroup->uiFromPW, m_pPW[*pIndex]);
			pPwGroup->uiToPW = _max(pPwGroup->uiToPW, m_pPW[*pIndex]);

			++pIndex;
		}

		++m_PwGroups.uiCount;

#else
		int peak_index;

		if (bForce1Group == true) {
			int i;
			PDWINDEX *pIndex;

			pPwGroup = &m_PwGroups.pw[m_PwGroups.uiCount];

			pPwGroup->frq_idx = frqidx;
			pPwGroup->uiFromBin = 0;
			pPwGroup->uiToBin = 0xFFFFFF;
			pIndex = pAoaGroup->pPDWIndex;
			pPwGroup->uiFromPW = m_pPW[*pIndex];
			pPwGroup->uiToPW = m_pPW[*pIndex];
			for (i = 0; i < pAoaGroup->iCount; ++i) {
				pPwGroup->uiFromPW = _min(pPwGroup->uiFromPW, m_pPW[*pIndex]);
				pPwGroup->uiToPW = _max(pPwGroup->uiToPW, m_pPW[*pIndex]);

				++pIndex;
			}

			++m_PwGroups.uiCount;
		}
		else {
			MakeHist(pFrqGroup, pAoaGroup, PW_SHIFT_CNT, &m_PwHist);

			for (;; ) {
				// 펄스폭 그룹화 포인터 초기화
				pPwGroup = &m_PwGroups.pw[m_PwGroups.uiCount];

				// 방위 그룹화 PDW STAT, 밴드, 오버방위 저장
				pPwGroup->frq_idx = frqidx;

				// 주파수 그룹화의 나머지 주파수 범위 계산
				// 주파수 히스토그램에서 최대값 찾기
				peak_index = FindPeakInHist(m_PwHist.uiBinCount, &m_PwHist.hist[0]);

				int sum_peak;
				/*! \bug  피크의 이웃점 체크
						\date 2006-08-16 14:02:10, 조철희
				*/
				if (peak_index >= 0 && peak_index < (int)m_PwHist.uiBinCount) {
					if (peak_index == 0) {
						sum_peak = m_PwHist.hist[0] + m_PwHist.hist[1];
					}
					else if (peak_index == (int)(m_PwHist.uiBinCount - 1) && peak_index < TOTAL_FRQAOAPWBIN) {
						sum_peak = m_PwHist.hist[(UINT)peak_index] + m_PwHist.hist[(UINT)(peak_index - 1)];
					}
					else {
						sum_peak = m_PwHist.hist[(UINT)peak_index] + m_PwHist.hist[(UINT)(peak_index - 1)] + m_PwHist.hist[(UINT)(peak_index + 1)];
					}
				}
				else {
					sum_peak = 0;
				}

				// 종료 조건, 다음 방위 그룹 선택
				if (peak_index < 0 || (sum_peak <= (int)_spAnalMinPulseCount)) {
					break;
				}

				// 펄스폭 범위 구하기
				GetPwRange(peak_index, PW_SHIFT_CNT, pPwGroup);

				ReDrawPwHist(pPwGroup);

				// 다음 펄스폭 그룹화 테이블 증가
				++m_PwGroups.uiCount;

				if (m_PwGroups.uiCount >= MAX_PGRT) {
					Log(enError, "펄스폭 그룹화 인덱스의 최대 개수[%d]를 초과했습니다.", m_PwGroups.uiCount);
					break;
				}
			}
		}
#endif

	}
}

/**
 * @brief     펄스폭 히스토그램을 재계산한다.
 * @param     STR_PW_GROUP * pPwGroup
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-06-16 15:42:21
 * @warning
 */
void CGroup::ReDrawPwHist( STR_PW_GROUP *pPwGroup )
{
    register UINT i;
    PDWINDEX *pPdwIndex;

    pPdwIndex = & m_PwHist.hist[pPwGroup->uiFromBin];
	for (i = pPwGroup->uiFromBin; i <= pPwGroup->uiToBin; ++i) {
		*pPdwIndex++ = 0;
	}
}

/**
 * @brief     펄스폭 범위를 얻는다.
 * @param     int peak_index
 * @param     int nShift
 * @param     STR_PW_GROUP * pPwGroup
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-06-16 15:05:25
 * @warning
 */
void CGroup::GetPwRange( int peak_index, int nShift, STR_PW_GROUP *pPwGroup )
{
    int i;
    int pw_bin;
    UINT uiMaxPWDiff;

	uiMaxPWDiff = UMUL(PW_GROUP_DIFF, _spOneMicrosec);

    //////////////////////////////////////////////////////////////////////
    // peak부터 좌로 범위를 설정
    // 좌측의 경계 찾기 (start)
    for( i=peak_index-1 ; i >= 0 ; --i ) {
        // 경계 조건
        if (m_PwHist.hist[i] <= 0) {
            break;
        }

        // 좌 최대 범위, PW_GROUP_DIFF = 30 us
        if( ( (unsigned int) ( peak_index - (i+1) ) << (unsigned int) nShift ) >= uiMaxPWDiff ) {
			Log(enError, "[W] %d us를 초과했습니다.", PW_GROUP_DIFF);
            break;
        }
    }
    pw_bin = min( i+1 , (int) m_PwHist.uiBinCount );

    /*! \bug  펄스폭 bin 값은 히스트그램 상에서 찾은 경계값까지 정한다.
            \date 2006-06-02 14:40:08, 조철희
    */
    // margin에 의한 경계 찾기
    pPwGroup->uiFromPW = (unsigned int) ( (unsigned int) pw_bin << (unsigned int) nShift ); // _max( 0, ( frq_bin << nShift ) - freq_margin );
    pPwGroup->uiFromBin = (unsigned int) pw_bin; /* pPwGroup->from_frq >> nShift; */

    //////////////////////////////////////////////////////////////////////
    // peak부터 우로 범위를 설정
    for( i=peak_index+1 ; i < (int) m_PwHist.uiBinCount ; ++i ) {
        // 경계 조건
        if (m_PwHist.hist[i] <= 0) {
            break;
        }

        // 우 최대 범위, PW_GROUP_DIFF = 30 us
        if( ( (unsigned int) ( i - peak_index ) << (unsigned int) nShift ) > uiMaxPWDiff) {
            Log(enError, "[W] %d us를 초과했습니다.", PW_GROUP_DIFF);
            break;
        }
    }
    pw_bin = max(0, i-1 );

    /*! \bug  주파수 bin 값은 히스트그램 상에서 찾은 경계값까지 정한다.
        \date 2006-06-02 14:41:03, 조철희
    */
    // margin에 의한 경계 찾기
    pPwGroup->uiToPW = (unsigned int) min( (unsigned int) MAX_PW, (unsigned int) ((unsigned int) ( pw_bin+1 ) << (unsigned int) nShift ) );
    pPwGroup->uiToBin = (unsigned int) pw_bin; // pFrqGroup->to_frq >> nShift;

    return;
}

/**
 * @brief     주파수 그룹화를 수행한다.
 * @param     int door
 * @param     int aoaidx
 * @param     int frqidx
 * @param     bool bForce1Group
 * @return    UINT
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-04-28 09:37:14
 * @warning
 */
UINT CGroup::MakeFreqGroup( int door, int aoaidx, int frqidx, bool bForce1Group )
{
    unsigned int uiRet=0;
    unsigned int uiShift;
    int freqdiff;

    int peak_index;

    unsigned int uiBand;

    STR_AOA_GROUP *pAoaGroup;
    STR_FRQ_GROUP *pFrqGroup;

    unsigned int pre_CoFrqGroups;

    if( m_FrqGroups.uiCount >= MAX_FGRT ) {
        printf( "\n [W] 주파수 그룹화 인덱스의 최대 개수[%d]를 초과했습니다." , m_FrqGroups.uiCount );
    }
	else {
		if (bForce1Group == true) {
			int i;
			PDWINDEX *pIndex;

			pFrqGroup = &m_FrqGroups.stFreq[m_FrqGroups.uiCount];

			pFrqGroup->iIdxAOA = aoaidx;
			pFrqGroup->narrow_wide = door;
			pFrqGroup->end_of_aoagroup = FALSE;

			pAoaGroup = &m_AoaGroups.stAOA[aoaidx];
			pFrqGroup->uiFromBIN = 0;
			pFrqGroup->uiToBIN = 0xFFFFFF;
			pIndex = pAoaGroup->pPDWIndex;
			pFrqGroup->uiFromFRQ = m_pFREQ[*pIndex];
			pFrqGroup->uiToFRQ = m_pFREQ[*pIndex];
			for (i = 0; i < pAoaGroup->iCount; ++i) {
				pFrqGroup->uiFromFRQ = _min(pFrqGroup->uiFromFRQ, m_pFREQ[*pIndex]);
				pFrqGroup->uiToFRQ = _max(pFrqGroup->uiToFRQ, m_pFREQ[*pIndex]);

				++pIndex;
			}

			++m_FrqGroups.uiCount;

            uiRet = m_FrqGroups.uiCount;
		}
		else {
			// 주파수 그룹화 이전 개수 보관.
			pre_CoFrqGroups = m_FrqGroups.uiCount;

			pAoaGroup = &m_AoaGroups.stAOA[aoaidx];

            uiBand = pAoaGroup->uiBand;
			if (door == NARROW) {
				uiShift = (unsigned int) GetFreqShift( (int) uiBand, (int) FREQ_NARR_MHZ);
				freqdiff = NARROW_FREQ_GROUP;
			}
			else {
                uiShift = (unsigned int) GetFreqShift((int) uiBand, (int) FREQ_WIDE_MHZ);
				freqdiff = WIDE_FREQ_GROUP;
			}

			// 방위 히스토그램 작성
			MakeHist(pAoaGroup, &m_pFREQ[0], uiShift, & m_FrqHist);

			for (;; ) {
				// 주파수 그룹화 초기화
				pFrqGroup = &m_FrqGroups.stFreq[m_FrqGroups.uiCount];

				// 방위 그룹화 PDW STAT, 밴드, 오버방위 저장
				pFrqGroup->iIdxAOA = aoaidx;
				pFrqGroup->narrow_wide = door;
				pFrqGroup->end_of_aoagroup = FALSE;

				// 주파수 그룹화의 나머지 주파수 범위 계산
				// 주파수 히스토그램에서 최대값 찾기
				peak_index = FindPeakInHist(m_FrqHist.uiBinCount, &m_FrqHist.hist[0]);

				/*! \bug  peak_index에서 bin count 값이 _spAnalMinPulseCount(6) 이하일 때 그룹화 루프를 벗어나도록 했는데
									여기서 이웃점들이 있을 때 그 개수가 최대 18개 가 있을 수 있다.
						\date 2006-05-15 15:23:02, 조철희
				*/
				int sum_peak;

				if (peak_index >= 0 && peak_index < (int) m_FrqHist.uiBinCount ) {
					if (peak_index == 0) {
						sum_peak = m_FrqHist.hist[0] + m_FrqHist.hist[1];
					}
					else if (peak_index == (int) m_FrqHist.uiBinCount - 1) {
						sum_peak = m_FrqHist.hist[(UINT)peak_index] + m_FrqHist.hist[(UINT)(peak_index - 1)];
					}
					else {
						sum_peak = m_FrqHist.hist[(UINT)peak_index] + m_FrqHist.hist[(UINT)(peak_index - 1)] + m_FrqHist.hist[(UINT)(peak_index + 1)];
					}
				}
				else {
					sum_peak = 0;
				}

				// 종료 조건, 다음 방위 그룹 선택
				if (peak_index < 0 || (sum_peak /* m_FrqHist.hist[ peak_index ] */ <= (int)_spAnalMinPulseCount)) {
					if (m_FrqGroups.uiCount > 0) {
						--pFrqGroup;
					}
					pFrqGroup->end_of_aoagroup = TRUE;
                    uiRet = m_FrqGroups.uiCount - pre_CoFrqGroups;
					break;
				}

				// 주파수 범위 구하기
				GetFrqRange(peak_index, (int) uiShift, freqdiff, pFrqGroup);

				ReDrawFrqHist(pFrqGroup);

				// 다음 주파수 그룹화 테이블 증가
				++m_FrqGroups.uiCount;

				if (m_FrqGroups.uiCount >= MAX_FGRT) {
					printf("\n [W] 주파수 그룹화 인덱스의 최대 개수[%d]를 초과했습니다.", m_FrqGroups.uiCount);

					if (m_FrqGroups.uiCount > 0) {
						--pFrqGroup;
					}
					pFrqGroup->end_of_aoagroup = TRUE;
					uiRet = m_FrqGroups.uiCount - pre_CoFrqGroups;
					break;
				}

				// 최초 그룹화 범위를 저장한다.
				// 최초의 그룹( 최대 개수의 주파수 그룹 )
				SaveFrqAoaPeak();
			}
		}
	}

    return uiRet;

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
    unsigned int uiIndex, uiPW;

    PDWINDEX *pIndex;

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

    // bin 개수 구하기
    bool bRet=SetHistBinCount( nShift, pHist );

    if (bRet == true) {
        pIndex = &pAoaGroup->pPDWIndex[0];
        // 대상 index의 파라메터에 대한 히스토그램 만들기
        for (i = 0; i < pAoaGroup->iCount; ++i) {
            uiPW = m_pPW[*pIndex];

            if (CompMarginDiff<unsigned int>(uiPW, pPwGroup->uiFromPW, pPwGroup->uiToPW, 0) == TRUE) {
                uiIndex = m_pFREQ[*pIndex] >> nShift;
                if (uiIndex >= pHist->uiBinCount) {
                    printf("\n [W] 히스토그램 생성에서 에러 발생함 !");
                    WhereIs;
                }
                else {
                    ++pHist->hist[uiIndex];
                }
            }

            ++pIndex;
        }
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
    unsigned int uiIndex;
    unsigned int uiFreq;

    PDWINDEX *pIndex;

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

    // bin 개수 구하기
    bool bRet=SetHistBinCount( nShift, pHist );

    if (bRet == true) {
        pIndex = &pAoaGroup->pPDWIndex[0];
        // 대상 index의 파라메터에 대한 히스토그램 만들기
        for (i = 0; i < pAoaGroup->iCount; ++i) {
			uiFreq = m_pFREQ[*pIndex];

            if (CompMarginDiff<unsigned int>(uiFreq, pFrqGroup->uiFromFRQ, pFrqGroup->uiToFRQ, 0) == TRUE) {
                uiIndex = m_pPW[*pIndex] >> nShift;
                if (uiIndex >= pHist->uiBinCount) {
                    printf("\n [W] 펄스폭 히스토그램 생성에서 에러 발생함 !");
                    WhereIs;
                }
                else {
                    ++pHist->hist[uiIndex];
                }
            }

            ++pIndex;
        }
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
    unsigned int uiIndex;
    unsigned int uiFreq;

    int nFrqShift;

    PDWINDEX *pIndex;

	if (pFrqGroup->narrow_wide == _WIDE) {
		nFrqShift = (int)FREQ_WIDE_SHIFT_CNT;
	}
	else {
		nFrqShift = (int)FREQ_NARR_SHIFT_CNT;
	}

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

	unsigned uiShift = ((unsigned int)1 << (unsigned int)nShift);
	if (uiShift != 0) {
		pHist->uiBinCount = (unsigned int) MAX_PW / uiShift;

		pIndex = &pAoaGroup->pPDWIndex[0];
		// 대상 index의 파라메터에 대한 히스토그램 만들기
		for (i = 0; i < pAoaGroup->iCount; ++i, ++pIndex) {
			uiFreq = pFreq[*pIndex];
			uiFreq = uiFreq >> (unsigned int) nFrqShift;

			if (CompMarginDiff<unsigned int>(uiFreq, pFrqGroup->uiFromBIN, pFrqGroup->uiToBIN, 0) == TRUE) {
				uiIndex = pPW[*pIndex];
				uiIndex = uiIndex >> nShift;

				if (uiIndex >= pHist->uiBinCount) {
					printf("\n [W] 히스토그램 생성에서 에러 발생함 !");
					WhereIs;
				}
				else {
					++pHist->hist[uiIndex];
				}
			}
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
    unsigned int uiIndex;
    unsigned int uiFreq;

    int nFrqShift;

    PDWINDEX *pIndex;

    if( pFrqGroup->narrow_wide == _WIDE )
        nFrqShift = (int) FREQ_WIDE_SHIFT_CNT;
    else
        nFrqShift = (int) FREQ_NARR_SHIFT_CNT;

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

    // bin 개수 구하기
    bool bRet=SetHistBinCount( nShift, pHist );

    if (bRet == true) {
        pIndex = &pAoaGroup->pPDWIndex[0];
        // 대상 index의 파라메터에 대한 히스토그램 만들기
        for (i = 0; i < pAoaGroup->iCount; ++i) {
            _EQUALS3(uiIndex, uiFreq, pPdw[*pIndex])
            ++pIndex;

            uiIndex = uiIndex >> nShift;
			uiFreq = uiFreq >> (unsigned int) nFrqShift;
            if (CompMarginDiff<unsigned int>(uiFreq, pFrqGroup->uiFromBIN, pFrqGroup->uiToBIN, 0) == TRUE) {
                if (uiIndex >= pHist->uiBinCount) {
                    Log(enError, "\n [W] 히스토그램 생성에서 에러 발생함 !");
                    WhereIs;
                }
                else {
                    ++pHist->hist[uiIndex];
                }
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
void CGroup::MakeHist( STR_AOA_GROUP *pAoaGroup, UINT *pPdw, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist)
{
    int i;
    unsigned int uiIndex;

    PDWINDEX *pIndex;

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

    /*! \bug  주파수/방위/펄스폭의 히스토그램의 BIN 개수를 정한다.
        \date 2006-07-27 14:39:03, 조철희
    */
    // bin 개수 구하기
    bool bRet=SetHistBinCount( nShift, pHist );

    if (bRet == true) {
        pIndex = &pAoaGroup->pPDWIndex[0];
        // 대상 index의 파라메터에 대한 히스토그램 만들기
        for (i = 0; i < pAoaGroup->iCount; ++i) {
            // 고속 계산을 하기 위해서 나누기 대신에 Shift 연산으로 변경
            uiIndex = pPdw[*pIndex++] >> nShift;
            if (uiIndex >= pHist->uiBinCount) {
                //Log( enError, "\n [W] 히스토그램 생성에서 에러 발생함 !", pHist->bin_count );
                //printf( "\n [W] 방위 및 주파수 히스토그램 생성에서 에러 발생함 !" );
                ++pHist->hist[pHist->uiBinCount - 1];
            }
            else {
                ++pHist->hist[uiIndex];
            }
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
    unsigned int uiIndex;
    PDWINDEX *pIndex;

    // 히스토그램 초기화
    memset( pHist, 0, sizeof( STR_FRQAOAPWHISTOGRAM ) );

    bool bRet = SetHistBinCount( nShift, pHist );

    if (bRet == true) {
        pIndex = &pSrcIndex->pIndex[0];
        for (i = 0; i < pSrcIndex->uiCount; ++i) {	// 대상 index의 파라메터에 대한 히스토그램 만들기
            int iIndex;

            //index = ( *( pPdw + (*pIndex++) ) ) >> nShift;
            iIndex = (*pIndex++);
            uiIndex = (pPdw[iIndex]) >> nShift;
            if (uiIndex > pHist->uiBinCount) {
                //printf( "\n [W] 히스토그램 생성에서 에러 발생함 !" );
                Log(enError, "\n [W] 히스토그램 생성에서 에러 발생함 !", pHist->uiBinCount);
                WhereIs;
            }
            else {
                ++pHist->hist[uiIndex];
            }
        }
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
bool CGroup::SetHistBinCount( UINT uiShift, STR_FRQAOAPWHISTOGRAM *pHist )
{
    bool bRet = true;
	unsigned int ui1Shift = (unsigned int)1 << uiShift;

	if ( ui1Shift != 0) {
		if( pHist == & m_AoaHist ) {
			pHist->uiBinCount = ( (unsigned int) MAX_AOA / ui1Shift);
#if MAX_AOA < TOTAL_FRQAOAPWBIN
			if ( pHist->uiBinCount == 0) {
				bRet = false;

				Log(enError, "[W] 방위 히스토그램의 BIN(%d)가 초과됐습니다. !", pHist->uiBinCount);
				WhereIs;
			}
#else
			if( pHist->uiBinCount > (unsigned int) TOTAL_FRQAOAPWBIN || pHist->uiBinCount == 0 ) {
				bRet = false;

				Log( enError, "[W] 방위 히스토그램의 BIN(%d)가 초과됐습니다. !", pHist->uiBinCount );
				WhereIs;            
			}
#endif
		}
		else if( pHist == & m_FrqHist ) {
			int iMax = MAX_FREQ;
			pHist->uiBinCount = ((unsigned int) MAX_FREQ / ui1Shift );
			if( pHist->uiBinCount > (unsigned int) TOTAL_FRQAOAPWBIN || pHist->uiBinCount == 0 ) {
				bRet = false;

				Log(enError, "[W] 주파수 히스토그램의 BIN(%d)가 초과됐습니다. !", pHist->uiBinCount);
				WhereIs;
			}
		}
		else {
			pHist->uiBinCount = ((unsigned int)MAX_PW / ui1Shift);
			if (pHist->uiBinCount > (unsigned int) TOTAL_FRQAOAPWBIN || pHist->uiBinCount == 0) {
				bRet = false;

				Log(enError, "[W] 펄스폭 히스토그램의 BIN(%d)가 초과됐습니다. !", pHist->uiBinCount);
				WhereIs;
			}
		}
    }
	else {
		Log(enError, "[W] BIN 크기를 결정할 쉬프트 값(%d)이 잘못 됐습니다. !", uiShift );
		WhereIs;
	}

    return bRet;
}

/**
 * @brief     CalcAoaMeanByHistAoa
 * @param     STR_PDWINDEX * pSrcIndex
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-09-30 16:52:28
 * @warning
 */
int CGroup::CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex ) 
{
	int iRet;
    unsigned int i;
    int frstAoa, diffAoa, overAoa;
    PDWINDEX *pPdwIndex;

    int iBin, bin_low, bin_mid, bin_hgh;

    int sum_item, filted_count;

    // 방위 히스토그램을 작성한다.
    MakeHist( pSrcIndex, & m_pAOA[0], SHIFT_COUNT_BY_HIST, & m_AoaHist );

    // 히스토그램 상중에서 가장 큰 피크값을 찾는다.
    bin_mid = FindPeakInHist( m_AoaHist.uiBinCount, & m_AoaHist.hist[0] );
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
        iBin = (int) ( m_pAOA[ *pPdwIndex ] >> SHIFT_COUNT_BY_HIST );

        if(iBin == bin_low || iBin == bin_mid || iBin == bin_hgh ) {
            if( frstAoa == -1 ) {
                frstAoa = (int) m_pAOA[ *pPdwIndex ];
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
        iRet = -1;
    }
    else {
        iRet = ( MAX_AOA + IDIV( sum_item, filted_count ) + frstAoa ) % MAX_AOA;
    }

	return iRet;
}

#ifndef _ISODATA_AOA_GROUP_
/**
 * @brief     방위 그룹화된 정보로 필터링해서 PDWINDEX 를 구성한다.
 * @param     int peak_index
 * @param     int nShift
 * @param     STR_AOA_GROUP * pAoaGroup
 * @return    BOOL
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-04-27 01:32:33
 * @warning
 */
bool CGroup::GetAOARange( int peak_index, int nShift, STR_AOA_GROUP *pAoaGroup )
{
    int i;

    int aoa_bin;
    int from_bin, to_bin;

    int co_thresh;

    int thr;

	bool bRet;

    // 4 시그마 범위
    thr = (int) ( ( m_stSigma1Aoa[m_nBand] * 4 ) >> (unsigned int) nShift );

    // 전방위 그룹화 될 때의 방위 그룹화 범위
    pAoaGroup->uiFromBin = 0;
    pAoaGroup->uiToBin = m_AoaHist.uiBinCount - 1;
    pAoaGroup->iFromAOA = 0;
    pAoaGroup->iToAOA = MAX_AOA  - 1;
    pAoaGroup->uiStat = (unsigned int) m_nStat;
    pAoaGroup->bOverAoa = false;
    pAoaGroup->uiBand = (unsigned int) m_nBand;

    //////////////////////////////////////////////////////////////////////
    // peak부터 좌로 범위를 설정
    // 좌측의 경계 찾기 (from_val)
	bRet = false;
    co_thresh = 0;
    for( i=(int) ( peak_index-1) ;; --i ) {
        // 좌측의 끝에 도달 overgroup 발생
        if( i < 0 ) {
            i += (int) m_AoaHist.uiBinCount;
            pAoaGroup->bOverAoa = true;
        }

        // 전방위 그룹화 체크
		if (i == (int)peak_index) {
			bRet = true;
			break;
			// return TRUE;
		}

        // 방위 좌측 값 체크
        // 경계 조건
        if( m_AoaHist.hist[i] <= _sp.np.Aoa_Hist_Thr )
            ++ co_thresh;
        else
            co_thresh = 0;

        //-- 조철희 2005-11-22 11:14:47 --//
        if (co_thresh >= MIN_CONTI_THRESHOLD_AOA) {
            break;
        }
    }

	if (bRet == false) {
		// 좌 최소범위 경계조건
		// 4 시그마 이하
		aoa_bin = i;
		if (peak_index > i) {
			if (peak_index - i < thr) {
				aoa_bin = peak_index - thr;
			}
		}
		else {
			if (peak_index + (int)(m_AoaHist.uiBinCount - (unsigned int)i) < thr) {
				aoa_bin = peak_index - thr;
			}
		}
		// 좌측의 끝에 도달 overgroup 발생
		if (aoa_bin < 0) {
			pAoaGroup->bOverAoa = true;
			aoa_bin += (int)m_AoaHist.uiBinCount;
		}
		from_bin = aoa_bin;

		//////////////////////////////////////////////////////////////////////
		// peak 부터 우로 범위를 설정
		// 우측의 경계 찾기 (to_val)
		co_thresh = 0;
		for (i = peak_index + 1;; ++i) {
			// 우측의 끝에 도달 overgroup 발생
			if (i >= (int)m_AoaHist.uiBinCount) {
				i -= (int)m_AoaHist.uiBinCount;
				pAoaGroup->bOverAoa = true;
			}

			// 전방위 그룹화
			// 시작 점인 peak_index 까지 해도 되지만 앞에서 찾았기 때문에
			// 계산한 좌측 범위 까지 검사한다.
			//-- 조철희 2005-04-27 18:17:04 --//
			if (i == aoa_bin) {
				bRet = true;
				break;
				//return true;
			}

			// 경계 조건
			if (m_AoaHist.hist[i] <= _sp.np.Aoa_Hist_Thr) {
				++co_thresh;
			}
			else {
				co_thresh = 0;
			}

			//-- 조철희 2005-11-22 11:14:58 --//
			if (co_thresh >= MIN_CONTI_THRESHOLD_AOA) {
				break;
			}
		}

		if (bRet == false) {
			// 우 최소범위 경계조건 // 000210
			aoa_bin = i;
			if (peak_index < i) {
				// 4시그마 이하
				if (i - peak_index < thr) {
					aoa_bin = peak_index + thr;
				}
			}
			else if (peak_index > i) {
				// 4 시그마 이하
				if ((int)(m_AoaHist.uiBinCount - (unsigned int)i) - peak_index < thr) {
					aoa_bin = peak_index + thr;
				}
			}
			else {

			}

			// 우측의 끝에 도달 overgroup 발생
			if (aoa_bin >= (int)m_AoaHist.uiBinCount) {
				aoa_bin -= (int) m_AoaHist.uiBinCount;
				pAoaGroup->bOverAoa = true;
			}
			to_bin = aoa_bin;

			// margin에 의한 전방위그룹 체크
			if (pAoaGroup->bOverAoa && (to_bin >= from_bin)) {
				bRet = true;
			}
			else {
				pAoaGroup->uiFromBin = (unsigned int) from_bin;
				pAoaGroup->uiToBin = ( unsigned int ) to_bin;
				pAoaGroup->iFromAOA = (int) ( (unsigned int) from_bin << ( unsigned int ) nShift );
				pAoaGroup->iToAOA = (int) ( ( unsigned int ) to_bin << (unsigned int) nShift );

				pAoaGroup->uiStat = (UINT)m_nStat;
				pAoaGroup->uiBand = (UINT)m_nBand;
			}
		}
	}

	return bRet;
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
        for (i = pAoaGroup->uiFromBin; i <= (UINT)(m_AoaHist.uiBinCount - 1); ++i)
            m_AoaHist.hist[i] = 0;
        for (i = 0; i <= pAoaGroup->uiToBin; ++i)
            m_AoaHist.hist[i] = 0;
    }
    else {
        for (i = pAoaGroup->uiFromBin; i <= pAoaGroup->uiToBin; ++i)
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
BOOL CGroup::GetFrqRange( int iPeakIndex, int nShift, int freqdiff, STR_FRQ_GROUP *pFrqGroup )
{
    int i;
    UINT uiFreqBin;
    UINT uiMaxFreqDiff;

    // 1 GHz 주파수 값
    uiMaxFreqDiff = IFRQMhzCNV( m_nBand, MAX_FREQ_DIFF );
    // max_freq_diff = I_IFRQCNV( g_enBoardId, MAX_FREQ_DIFF );
    //max_freq_diff = abs( (int) IDIV( MAX_FREQ_DIFF, gFreqRes[ m_nBand+1 ].fRes ) );

    //////////////////////////////////////////////////////////////////////
    // peak부터 좌로 범위를 설정
    // 좌측의 경계 찾기 (start)
    for( i=iPeakIndex-1 ; i >= 0 ; --i ) {
        // 경계 조건
        if( m_FrqHist.hist[i] <= _sp.np.Freq_Hist_Thr ) {
            break;
        }

        // 좌 최대 범위
        if( ( (unsigned int) ( iPeakIndex - (i+1) ) << (unsigned int) nShift ) >= uiMaxFreqDiff ) {	// 1GHz 이상
            TRACE( "\n [O] OverLeft1GHz");
            WhereIs;
            break;
        }
    }
    uiFreqBin = min( (UINT) (i+1) , m_FrqHist.uiBinCount );

    /*! \bug  주파수 bin 값은 히스트그램 상에서 찾은 경계값까지 정한다.
            \date 2006-06-02 14:40:08, 조철희
    */
    // margin에 의한 경계 찾기
    //pFrqGroup->uiFromFRQ = max( (unsigned int) 0, uiFreqBin << (unsigned int) nShift );
    pFrqGroup->uiFromFRQ = uiFreqBin << ( unsigned int ) nShift;
    pFrqGroup->uiFromBIN = uiFreqBin; /* pFrqGroup->from_frq >> nShift; */

    //////////////////////////////////////////////////////////////////////
    // peak부터 우로 범위를 설정
    for( i=iPeakIndex+1 ; i < (int) m_FrqHist.uiBinCount ; ++i ) {
        // 경계 조건
        if( m_FrqHist.hist[i] <= _sp.np.Freq_Hist_Thr )
            break;

        // 우 최대 범위
        if( ( (unsigned int) ( i - iPeakIndex ) << ( unsigned int ) nShift ) > uiMaxFreqDiff ) {
            TRACE( "\n [O] OverRight1GHz" );
            WhereIs;
            break;
        }
    }
    //uiFreqBin = max( (unsigned int) 0, (unsigned int) i-1 );
    uiFreqBin = ( unsigned int ) ( i - 1 );

    /*! \bug  주파수 bin 값은 히스트그램 상에서 찾은 경계값까지 정한다.
        \date 2006-06-02 14:41:03, 조철희
    */
    // margin에 의한 경계 찾기
    pFrqGroup->uiToFRQ = min( MAX_FREQ, (unsigned int) ( uiFreqBin+1 ) << (unsigned int) nShift );
    pFrqGroup->uiToBIN = uiFreqBin; // pFrqGroup->to_frq >> nShift;

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

    UINT uiLow, uiHigh;

	uiLow = (unsigned int) pAoaGroup->iFromAOA;
	uiHigh = (unsigned int) pAoaGroup->iToAOA;

    // 초기화
    pAoaGroup->iCount = 0;
    pAoaPdwIndex = pAoaGroup->pPDWIndex;

    pPdwIndex = pGrPdwIndex->pIndex;
    if( pAoaGroup->bOverAoa ) {
        for( i=0 ; i < pGrPdwIndex->uiCount ; i++ )	{
            index = *pPdwIndex++;

            // 추출된 펄스가 아니면 통과
            if( m_pMARK[ index ] != enEXTRACT_MARK) {
                // 범위 조사
                if( pParam[index] >= uiLow || pParam[index] <= uiHigh ) {
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
            if( m_pMARK[ index ] != enEXTRACT_MARK) {
                // 범위 조사
                if( pParam[index] >= uiLow && pParam[index] <= uiHigh ) {
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
    pPdwIndex = pAoaGroup->pPDWIndex;
    pDstIndex = pFrqAoaPwIndex->pIndex;
    for( i=0 ; i < pAoaGroup->iCount ; i++, ++pPdwIndex ) {
        // 추출된 펄스가 아니면 통과
        // if( MARK[ *pPdwIndex ] != EXTRACT_MARK )
        {
            // 범위 조사
            if( ( pParam1[*pPdwIndex] >= pFrqGroup->uiFromFRQ && pParam1[*pPdwIndex] <= pFrqGroup->uiToFRQ ) &&
                    ( pParam2[*pPdwIndex] >= pPwGroup->uiFromPW && pParam2[*pPdwIndex] <= pPwGroup->uiToPW ) ) {
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
    for( UINT i=pFrqGroup->uiFromBIN ; i <= pFrqGroup->uiToBIN ; ++i )
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
    pFrqGr = & m_FrqGroups.stFreq[ pPwGr->frq_idx ];
    pAoaGroup = & m_AoaGroups.stAOA[ pFrqGr->iIdxAOA ];

    m_nBand = (int) pAoaGroup->uiBand;
    m_nStat = (int) pAoaGroup->uiStat;

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

    /*! \debug  0 보다 크면
    	\author 조철희 (churlhee.jo@lignex1.com)
    	\date 	2022-04-27 15:18:02
    */
    if( uiIndex == m_PwGroups.uiCount ) {
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
        m_FrqAoaPeak.stAOA.iLow = m_AoaGroups.stAOA[0].iFromAOA;
        m_FrqAoaPeak.stAOA.iHgh = m_AoaGroups.stAOA[0].iToAOA;
        m_FrqAoaPeak.stFrq.iLow = (int) m_FrqGroups.stFreq[0].uiFromFRQ;
        m_FrqAoaPeak.stFrq.iHgh = (int) m_FrqGroups.stFreq[0].uiToFRQ;
        m_FrqAoaPeak.band	= (UINT) m_nBand;
        m_FrqAoaPeak.tot_cnt = m_uiCoPdw;
        m_FrqAoaPeak.uiCount = m_FrqAoaPwIdx.uiCount;

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
    return m_FrqGroups.stFreq[ noGroup ].end_of_aoagroup;
}

//////////////////////////////////////////////////////////////////////
// 아래 함수들은 추적에서 사용할 그룹화 멤버 함수들입니다.

/**
 * @brief     주파수, 방위, 펄스폭 그룹화를 수행한다.
 * @param     STR_PDWINDEX * pStatGrPdwIndex
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-07-27 15:57:06
 * @warning
 */
void CGroup::MakeFreqAoaPwGroup( STR_PDWINDEX *pStatGrPdwIndex )
{
    STR_AOA_GROUP *pAoaGroup;
    STR_FRQ_GROUP *pFrqGroup;
    STR_PW_GROUP *pPwGroup;

    // 방위 그룹화 기록
    pAoaGroup = & m_AoaGroups.stAOA[ m_AoaGroups.uiCount ];

    // 전방위 그룹화 될 때의 방위 그룹화 범위
    pAoaGroup->iFromAOA = (int) 0;
    pAoaGroup->uiFromBin = (UINT) 0;
    // _EQUALS3( pAoaGroup->uiFromBin, pAoaGroup->iFromAOA, (UINT) 0 )
    pAoaGroup->iToAOA = (int)(MAX_AOA - 1);
    pAoaGroup->uiToBin = (unsigned int)(MAX_AOA - 1);
    //_EQUALS3( pAoaGroup->uiToBin, pAoaGroup->iToAOA, (UINT)( MAX_AOA-1 ) )
    pAoaGroup->uiStat = (UINT) m_nStat;
    pAoaGroup->bOverAoa = FALSE;
    pAoaGroup->uiBand = (UINT) m_nBand;

    FilterParam( pStatGrPdwIndex, & m_pAOA[0], pAoaGroup );

    // 펄스폭 그룹화 기록
    pPwGroup = & m_PwGroups.pw[ m_PwGroups.uiCount ];
    pPwGroup->uiFromBin = 0;
    pPwGroup->uiToBin = ( MAX_PW - 1 ) >> PW_SHIFT_CNT;
    pPwGroup->uiFromPW = 0;
    pPwGroup->uiToPW = MAX_PW - 1;

    pPwGroup->frq_idx = (int) m_FrqGroups.uiCount;

    // 주파수 그룹화 초기화
    pFrqGroup = & m_FrqGroups.stFreq[ m_FrqGroups.uiCount ];

    // 방위 그룹화 PDW STAT, 밴드, 오버방위 저장
    pFrqGroup->iIdxAOA = (int) m_AoaGroups.uiCount;
    pFrqGroup->narrow_wide = _FULL;
    pFrqGroup->end_of_aoagroup = FALSE;
    _EQUALS3( pFrqGroup->uiFromFRQ, pFrqGroup->uiFromBIN, 0 )
    _EQUALS3( pFrqGroup->uiToFRQ, pFrqGroup->uiToBIN, MAX_FREQ )

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
#if defined(_ELINT_) || defined(_XBAND_) || defined(_701_)
#define		MAXIMUM_STANDARD_DEVIATION		UMUL( 1, _spRxdfAoa )		// 대역중에서 가장 큰 방위 오차
#define		MAXIMUM_DISTANCE_OF_CLUSTERS	UMUL( 1, _spRxdfAoa )		// 클러스터 사이간의 최대 길이

#elif defined(_POCKETSONATA_)
#define		MAXIMUM_STANDARD_DEVIATION		UMUL( 1, KHARM_AOA_MAR )		// 대역중에서 가장 큰 방위 오차
#define		MAXIMUM_DISTANCE_OF_CLUSTERS	UMUL( 1, KHARM_AOA_MAR )		// 클러스터 사이간의 최대 길이

#else
#define		MAXIMUM_STANDARD_DEVIATION		UMUL( 1, _spRxdfAoaLow )		// 대역중에서 가장 큰 방위 오차
#define		MAXIMUM_DISTANCE_OF_CLUSTERS	UMUL( 1, _spRxdfAoaLow )		// 클러스터 사이간의 최대 길이
#endif

#define		NUMBER_OF_CLUSTER				( MAX_AOA_GROUP )						// 최대 클러스터 개수
#define		MINIMUM_NUMBER_OF_SAMPLES		( RJGPC )										// 클러스터 내의 가장 작은 샘플 개수
#define		NUMBER_OF_ITERATIONS			( 7 )
#define		SPLIT_RATIO						( 0.6 )
void CGroup::ISODATA( STR_PDWINDEX *pSrcIndex, UINT *pPdw )
{
    unsigned int i, j, k;
    int nSplitCluster;

    STR_CLUSTER *pCluster;

    //-- 조철희 2006-01-05 10:54:31 --//
    if( pSrcIndex->uiCount <= MINIMUM_NUMBER_OF_SAMPLES ) {
        m_uiClusters = 0;
    }
    else {
        // 초기화
        m_pPDWParam = pPdw;
        m_uiClusters = _spOne;
        pCluster = &m_pCluster[0];
        pCluster->iCount = (int) pSrcIndex->uiCount;
        pCluster->bSplit = true;

        memcpy(pCluster->pIndex, pSrcIndex->pIndex, sizeof(PDWINDEX)*(size_t) pCluster->iCount);

        CalClusterInfo(pCluster);

        // 클러스터링 시작
        for (i = 0; i < NUMBER_OF_ITERATIONS; ++i) {
            //
            nSplitCluster = 0;
            pCluster = &m_pCluster[0];
            for (j = 0; j < m_uiClusters; ++j) {
                if (TRUE == SplitCenter(pCluster, &m_pCluster[MAX_AGRT - 2])) {
                    for (k = (UINT)( ( m_uiClusters + (UINT) nSplitCluster ) - 1 ) ; k >= j + (unsigned int) nSplitCluster + 1; --k) {
                        memcpy(&m_pCluster[k + 1], &m_pCluster[k], sizeof(STR_CLUSTER));
                    }
                    memcpy(pCluster++, &m_pCluster[MAX_AGRT - 1], sizeof(STR_CLUSTER));
                    memcpy(pCluster++, &m_pCluster[MAX_AGRT - 2], sizeof(STR_CLUSTER));

                    ++nSplitCluster;
                }
                else {
                    ++pCluster;
                }
            }

            if( nSplitCluster == 0 ) {
                break;
            }

            m_uiClusters = m_uiClusters + (UINT) nSplitCluster;
        }
    }
}

/**
 * @brief     클러스터링 값을 분리한다.
 * @param     STR_CLUSTER * pCluster
 * @param     STR_CLUSTER * pDstCluster
 * @return    BOOL
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-12-28 16:28:43
 * @warning
 */
BOOL CGroup::SplitCenter( STR_CLUSTER *pCluster, STR_CLUSTER *pDstCluster )
{
    BOOL bRet=FALSE;
    STR_CLUSTER *pCluster1, *pCluster2;

    //int i = MAXIMUM_STANDARD_DEVIATION;

    /*! \bug  방위 그룹화 범위를 체크해서 빈 영역이 없는지를 검사한다.
        \date 2006-08-18 10:25:24, 조철희
    */
    pCluster1 = ( STR_CLUSTER * ) ( pDstCluster - pCluster );
    if( pCluster1 <= (STR_CLUSTER *) 1 ) {
        printf( "\n [W] 클러스터링 버퍼가 부족합니다." );
    }
    else {
        pCluster1 = pDstCluster++;
        pCluster2 = pDstCluster;

        // 클러스터 내의 표준편차 이상이고 개수 이상 일때 분리한다.
        if ( pCluster->bSplit == true && ( pCluster->fDeviation > (float)MAXIMUM_STANDARD_DEVIATION /* && pCluster->iCount > MINIMUM_NUMBER_OF_SAMPLES */ ) ) {
            pCluster1->iCenter = (int) AddAOA(pCluster->iCenter, IMUL(pCluster->fDeviation, SPLIT_RATIO));
            pCluster2->iCenter = ( int ) SubAOA(pCluster->iCenter, IMUL(pCluster->fDeviation, SPLIT_RATIO));

            ReCluster(pCluster1, pCluster2, pCluster);
            CalClusterInfo(pCluster1);
            CalClusterInfo(pCluster2);

            // 개수가 적어도 원 클러스터 의 분산 값이 크면 분리하도록 함.
            if( true /* pCluster1->iCount > MINIMUM_NUMBER_OF_SAMPLES && pCluster2->iCount > MINIMUM_NUMBER_OF_SAMPLES */ ) {
                pCluster1->bSplit = true;
                pCluster2->bSplit = true;
                // 클러스터 내의 모든 개수가 최소 클러스터 개수보다 커야 분리된다.
                // if( pCluster1->count > MINIMUM_NUMBER_OF_SAMPLES && pCluster2->count > MINIMUM_NUMBER_OF_SAMPLES )
                //-- 조철희 2006-01-04 15:52:41 --//
                bRet = TRUE;
            }
            else {
                pCluster1->bSplit = false;
            }
        }
    }

    return bRet;
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

    UINT *pDstValue1, *pDstValue2;

    int overVal;

    PDWINDEX *pCIndex;
    PDWINDEX *pDstCIndex1, *pDstCIndex2;

    pCIndex = & pSrcCluster->pIndex[0];
    pDstCIndex1 = & pDstCluster1->pIndex[0];
    pDstValue1 = &pDstCluster1->uiValue[0];
    pDstCIndex2 = & pDstCluster2->pIndex[0];
    pDstValue2 = &pDstCluster2->uiValue[0];

    _EQUALS3( pDstCluster1->iCount, pDstCluster2->iCount, 0 )
    center1 = pDstCluster1->iCenter;
    center2 = pDstCluster2->iCenter;
    for( i=0 ; i < pSrcCluster->iCount ; ++i ) {
        diff1 = (int) m_pPDWParam[ *pCIndex ] - center1;
        overVal = _abs( diff1 );
        if( overVal > MAX_AOA/2 ) {
            if( center1 > MAX_AOA/2 )
                diff1 = diff1 + MAX_AOA;
            else
                diff1 = diff1 - MAX_AOA;
        }
        diff1 = _abs( diff1 );

        diff2 = (int) m_pPDWParam[ *pCIndex ] - center2;
        overVal = _abs( diff2 );
        if( overVal > MAX_AOA/2 ) {
            if( center2 > MAX_AOA/2 )
                diff2 = diff2 + MAX_AOA;
            else
                diff2 = diff2 - MAX_AOA;
        }
        diff2 = _abs( diff2 );

        if( diff1 < diff2 ) {
            *pDstValue1++ = m_pPDWParam[*pCIndex];
            *pDstCIndex1++ = *pCIndex++;            
            ++ pDstCluster1->iCount;
        }
        else {
            *pDstValue2++ = m_pPDWParam[*pCIndex];
            *pDstCIndex2++ = *pCIndex++;
            ++ pDstCluster2->iCount;
        }
    }
}

/**
 * @brief     클러스터링 계산을 수행해서 업데이트한다.
 * @param     STR_CLUSTER * pCluster
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-12-28 14:39:14
 * @warning
 */
void CGroup::CalClusterInfo( STR_CLUSTER *pCluster )
{
    int i;
    int diffVal, overVal, meanVal, frstVal;

    double dMeanVal;
    PDWINDEX *pCIndex;

    pCIndex = &pCluster->pIndex[0];

    // 방위 평균 계산
    pCluster->stAOA.iHgh = -INT32_MAX;
    pCluster->stAOA.iLow = +INT32_MAX;

    meanVal = 0;    
    frstVal = (int) m_pPDWParam[ *pCIndex ];
    for( i=0 ; i < pCluster->iCount ; ++i ) {
        diffVal = (int) m_pPDWParam[ *pCIndex++ ] - frstVal;
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

        pCluster->stAOA.iHgh = _max( pCluster->stAOA.iHgh, diffVal );
        pCluster->stAOA.iLow = _min( pCluster->stAOA.iLow, diffVal );
    }
    pCluster->stAOA.iHgh = ( MAX_AOA + pCluster->stAOA.iHgh + frstVal ) % MAX_AOA;
    pCluster->stAOA.iLow = ( MAX_AOA + pCluster->stAOA.iLow + frstVal ) % MAX_AOA;
    pCluster->iCenter = ( MAX_AOA + IDIV( meanVal, pCluster->iCount ) + frstVal ) % MAX_AOA;

    // 방위 거리 계산
    meanVal = 0;
    frstVal = pCluster->iCenter;
    pCIndex = & pCluster->pIndex[0];
    for( i=0 ; i < pCluster->iCount ; ++i ) {
        diffVal = (int) m_pPDWParam[ *pCIndex++ ] - frstVal;
        overVal = _abs( diffVal );
        if( overVal > MAX_AOA/2 ) {
            if( frstVal > MAX_AOA/2 )
                diffVal = diffVal + MAX_AOA;
            else
                diffVal = diffVal - MAX_AOA;
        }

        meanVal += _abs( diffVal );
    }
    pCluster->fDistance = FDIV( meanVal, pCluster->iCount );

    // 방위 편차 계산
    dMeanVal = 0.;
    frstVal = pCluster->iCenter;
    pCIndex = & pCluster->pIndex[0];
    for( i=0 ; i < pCluster->iCount ; ++i ) {
        diffVal = (int) m_pPDWParam[ *pCIndex++ ] - frstVal;
        overVal = _abs( diffVal );
        if( overVal > MAX_AOA/2 ) {
            if( frstVal > MAX_AOA/2 )
                diffVal = diffVal + MAX_AOA;
            else
                diffVal = diffVal - MAX_AOA;
        }

        dMeanVal += ( diffVal * diffVal );
    }

    pCluster->fDeviation = (float) ( sqrt( dMeanVal / (double) pCluster->iCount ) );
}
