// KGroup.cpp: implementation of the CKGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../OFP_Main.h"

#include <stdio.h>

#include "KnownSigAnal.h"
#include "KGroup.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup
// 반환되는 형  : CKGroup::CKGroup(int coMaxPdw) :
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 14:09:58
//
//##ModelId=42E85F3500C0
CKGroup::CKGroup( void *pParent, int coMaxPdw ) : CGroup( coMaxPdw )
{
	m_pKnownSigAnal = ( CKnownSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pKnownSigAnal)
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKGroup::~CKGroup
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 17:25:06
//
//##ModelId=42E85F3500C1
CKGroup::~CKGroup()
{

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNGroup::Init
        \author   조철희
        \return   void
        \version  0.0.34
        \date     2008-07-30 13:26:21
        \warning
*/
void CKGroup::Init()
{
    /*! \bug  하위 그룹에서 초기화하는 것으로 수정함.
        \date 2008-07-30 13:25:17, 조철희
    */
    CGroup::Init();
}


//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKGroup::MakeGroup
// 반환되는 형  : void
// 함 수 인 자  : BOOL
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 17:25:17
//
//##ModelId=42E98F30008A
BOOL CKGroup::MakeKnownGroup()
{
	// 방위 및 주파수 그룹화 초기화
	m_stAOAGroups.uiCount = 0;
	m_stAOAGroups.uiCoAnal = 0;
	m_stFrqGroups.uiCount = 0;
	m_stFrqGroups.uiCoAnal = 0;
	m_PwGroups.uiCount = 0;
	m_PwGroups.coAnal = 0;

	MakeBandGroup();

	// 수집한 펄스에서 특정 밴드, 상태별 그룹화
    m_nBand = m_pBAND[0];
#ifdef _A50_RWR
	if( STAT[0] == PDW_CW || STAT[0] == PDW_CW_FMOP )
		m_nStat = STAT_CW;
	else
		m_nStat = STAT[0];

#elif _POCKETSONATA_
    m_nStat = m_pSTAT[0];

#else
    m_nStat = stStat2GrStat[ m_pSTAT[0] ];

#endif

    MakeStatGroup( & m_Band[m_nBand] );

	CGroup::MakeFreqAoaPwGroup( & m_GrStat[m_nStat] );

	return m_stAOAGroups.uiCount != 0;	
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKGroup::GetColPdw
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 09:42:07
//
int CKGroup::GetColPdw()
{ 
	return m_pKnownSigAnal->GetColPdw(); 
}

