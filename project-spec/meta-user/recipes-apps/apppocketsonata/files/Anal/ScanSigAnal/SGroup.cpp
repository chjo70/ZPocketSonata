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
CSGroup::CSGroup( void *pParent, unsigned int uicoMaxPdw ) : CGroup(uicoMaxPdw)
{
	m_pScanSigAnal = ( CScanSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pScanSigAnal)
}

/**
 * @brief     ~CSGroup
 * @return    
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-21 14:11:15
 * @warning
 */
CSGroup::~CSGroup()
{

}

/**
 * @brief     스캔 분석의 PDW 개수를 리턴한다.
 * @return    int
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-27 11:20:12
 * @warning
 */
unsigned int CSGroup::GetColPdw()
{
	return m_pScanSigAnal->GetColPdw(); 
}

/**
 * @brief     강제로 하나의 그룹화로 생성한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2009-03-03 17:07:20
 * @warning
 */
void CSGroup::MakeOneGroup()
{
	unsigned int i;
	PDWINDEX *pPdwIndex;

	m_FrqAoaPwIdx.uiCount = m_uiCoPdw;

	pPdwIndex = m_FrqAoaPwIdx.pIndex;
	for( i=0 ; i < m_uiCoPdw ; ++i ) {
		*pPdwIndex++ = i;

	}

}
