﻿// KGroup.cpp: implementation of the CKGroup class.
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
CKGroup::CKGroup( void *pParent, unsigned int uiCoMaxPdw, const char *pThreadName ) : CGroup(uiCoMaxPdw, pThreadName )
{
    SetAnalType( enTRK_ANAL );

	m_pKnownSigAnal = ( CKnownSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pKnownSigAnal)

#ifdef _MSC_VER
    //! #동적 시험으로 함수를 타기위해서 그냥 호출
    CKGroup::GetColPDW();

#endif
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
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-07-28 17:25:17
 * @warning
 */
bool CKGroup::MakeKnownGroup()
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

#elif defined(_POCKETSONATA_) || defined(_712_)
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
unsigned int CKGroup::GetColPDW()
{
	return m_pKnownSigAnal->GetColPdw();
}

/**
 * @brief     GetCoPDW
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-11 18:41:37
 * @warning
 */
unsigned int CKGroup::GetCoPDW()
{
    return m_pKnownSigAnal->GetCoPdw();
}

