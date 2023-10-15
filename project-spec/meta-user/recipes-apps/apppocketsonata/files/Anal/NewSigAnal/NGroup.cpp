// NGroup.cpp: implementation of the NGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#if defined(_ELINT_) || defined(_XBAND_)
#include "../OFP_Main.h"
#endif

#include <stdio.h>

// 사용자 헤더파일 정의
#include "../INC/PDW.h"

#include "../SigAnal/_Macro.h"

#include "NGroup.h"
#include "NewSigAnal.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * @brief     신호탐지분석의 그룹화 생성자 처리한다.
 * @param     void * pParent
 * @param     unsigned int uiCoMaxPdw
 * @return    
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-20 19:01:00
 * @warning
 */
CNGroup::CNGroup( void *pParent, unsigned int uiCoMaxPdw ) : CGroup(uiCoMaxPdw)
{
    m_pNewSigAnal = ( CNewSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pNewSigAnal)

}

/**
 * @brief     소멸자 처리를 수행한다.
 * @return    
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-20 19:01:03
 * @warning
 */
CNGroup::~CNGroup()
{

}

/**
 * @brief     신호탐지분석의 펄스열 개수를 리턴한다.
 * @return    int
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-28 16:16:32
 * @warning
 */
unsigned int CNGroup::GetColPdw()
{
    return m_pNewSigAnal->GetColPdw();
}


/**
 * @brief     신호탐지분석의 그룹화를 수행한다.
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-28 16:16:14
 * @warning
 */
void CNGroup::Init()
{
    /*! \bug  하위 그룹에서 초기화하는 것으로 수정함.
        \date 2008-07-30 13:25:17, 조철희
    */
    CGroup::Init();
}


#ifdef _LOG_ANALTYPE_
/**
 * @brief     GetLogAnalType
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-21 11:56:37
 * @warning
 */
bool CNGroup::GetLogAnalType()
{
    return m_pNewSigAnal->GetLogAnalType();
}

#endif