// NGroup.cpp: implementation of the NGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "../SigAnal/stdafx.h"

#ifdef _MSC_VER
// PC용 상위 클래스에 전달하기 위한 선언
//#include "../../A50SigAnal/stdafx.h"

#endif

#ifdef _ELINT_
#include "../OFP_Main.h"
#endif

#include <stdio.h>

// 사용자 헤더파일 정의
//#include "../INC/_define.h"
#include "../INC/PDW.h"

#include "../SigAnal/_Macro.h"

#include "NGroup.h"
#include "NewSigAnal.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup
// 반환되는 형  : CNGroup::CNGroup(void *pParent, int coMaxPdw) :
// 함 수 인 자  : void *pParent
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-20 19:01:00
//
CNGroup::CNGroup( void *pParent, int coMaxPdw ) : CGroup( coMaxPdw )
{
    m_pNewSigAnal = ( CNewSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pNewSigAnal)

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNGroup::~CNGroup
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-20 19:01:03
//
CNGroup::~CNGroup()
{

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNGroup::GetColPdw
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-20 19:01:05
//
int CNGroup::GetColPdw()
{
    return m_pNewSigAnal->GetColPdw();
}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CNGroup::Init
        \author   조철희
        \return   void
        \version  0.0.34
        \date     2008-07-30 13:26:21
        \warning
*/
void CNGroup::Init()
{
    /*! \bug  하위 그룹에서 초기화하는 것으로 수정함.
        \date 2008-07-30 13:25:17, 조철희
    */
    CGroup::Init();
}
