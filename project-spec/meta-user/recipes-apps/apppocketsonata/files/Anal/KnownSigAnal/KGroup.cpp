// KGroup.cpp: implementation of the CKGroup class.
//
//////////////////////////////////////////////////////////////////////

// PC용 상위 클래스에 전달하기 위한 선언
#ifdef _MSC_VER
#include "../../A50SigAnal/stdafx.h"
//#include "../../AdvSigAnal/AdvSigAnal.h"

//#include "../../AdvSigAnal/MainFrm.h"
//#include "../../AdvSigAnal/AdvSigAnalDoc.h"
//#include "../../AdvSigAnal/AdvSigAnalView.h"
#endif

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

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKGroup::MakeGroup
// 반환되는 형  : void
// 함 수 인 자  : BOOL
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 17:25:17
//
//##ModelId=42E98F30008A
BOOL CKGroup::MakeGroup()
{
	// 방위 및 주파수 그룹화 초기화
	m_AoaGroups.count = 0;
	m_AoaGroups.coAnal = 0;
	m_FrqGroups.count = 0;
	m_FrqGroups.coAnal = 0;
	m_PwGroups.count = 0;
	m_PwGroups.coAnal = 0;

	MakeBandGroup();

	// 수집한 펄스에서 특정 밴드, 상태별 그룹화
    m_nBand = m_pBAND[0];
#ifdef _A50_RWR
	if( STAT[0] == PDW_CW || STAT[0] == PDW_CW_FMOP )
		m_nStat = STAT_CW;
	else
		m_nStat = STAT[0];

#else
    m_nStat = stStat2GrStat[ m_pSTAT[0] ];
#endif

    MakeStatGroup( & m_Band[m_nBand] );

	CGroup::MakeFreqAoaPwGroup( & m_GrStat[m_nStat] );

	return m_AoaGroups.count != 0;	
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

