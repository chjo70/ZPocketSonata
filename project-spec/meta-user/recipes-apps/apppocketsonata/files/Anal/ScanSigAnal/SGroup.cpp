// SGroup.cc: implementation of the CSGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../OFP_Main.h"

#include <stdio.h>

#include "ScanSigAnal.h"
#include "SGroup.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * @brief CSGroup::CSGroup
 * @param pParent
 * @param coMaxPdw
 */
CSGroup::CSGroup( void *pParent, int coMaxPdw ) : CGroup( coMaxPdw )
{
	m_pScanSigAnal = ( CScanSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pScanSigAnal);
}

/**
 * @brief CSGroup::~CSGroup
 */
CSGroup::~CSGroup()
{

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSGroup::GetColPdw
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-27 11:20:12
//
int CSGroup::GetColPdw()
{
	return m_pScanSigAnal->GetColPdw(); 
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSGroup::MakeOneGroup
		\author   조철희
		\return   void
		\version  0.0.73
		\date     2009-03-03 17:07:20
		\warning
*/
void CSGroup::MakeOneGroup()
{
	int i;
	PDWINDEX *pPdwIndex;

	m_FrqAoaPwIdx.uiCount = m_nCoPdw;

	pPdwIndex = m_FrqAoaPwIdx.pIndex;
	for( i=0 ; i < m_nCoPdw ; ++i ) {
		*pPdwIndex++ = i;

	}

}
