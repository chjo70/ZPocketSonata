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

/**
 * @brief     그룹화 객체 수행시 내부 변수, 메모리를 할당한다.
 * @param     void * pParent
 * @param     int coMaxPdw
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-08, 12:45
 * @warning
 */
CKGroup::CKGroup( void *pParent, unsigned int uiCoMaxPdw ) : CGroup(uiCoMaxPdw)
{
	m_pKnownSigAnal = ( CKnownSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pKnownSigAnal)
}

/**
 * @brief     소멸자 처리를 수행한다.
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-07-28 17:25:06
 * @warning
 */
CKGroup::~CKGroup()
{

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    초기화를 수행한다.
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

/**
 * @brief     추적 신호를 그룹화하기 위해 초기화를 수행한다.
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-07-28 17:25:17
 * @warning
 */
BOOL CKGroup::MakeKnownGroup()
{
	// 방위 및 주파수 그룹화 초기화
    m_AoaGroups.uiCount = 0;
    m_AoaGroups.uiCoAnal = 0;
	m_FrqGroups.uiCount = 0;
	m_FrqGroups.uiCoAnal = 0;
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

	return m_AoaGroups.uiCount != 0;
}

/**
 * @brief     수집한 PDW 개수를 리턴한다.
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 09:42:07
 * @warning
 */
unsigned int CKGroup::GetColPdw()
{
	return m_pKnownSigAnal->GetColPdw(); 
}

