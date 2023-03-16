// IntraSigAnal.h: interface for the CIntraSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTRASIGANAL_H__30606F89_0BF4_4C89_B5CD_4E9700CBE5E4__INCLUDED_)
#define AFX_INTRASIGANAL_H__30606F89_0BF4_4C89_B5CD_4E9700CBE5E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "../../Utils/ccommonutils.h"

#include "../SigAnal/SigAnal.h"



/**
*
* @brief	  추출한 PDW 데이터를 입력으로 인트라 분석을 수행합니다.
* @details	  펄스 내 분석 기능을 수행한다
* @author    조철희 (churlhee.jo@lignex1.com)
* @version   1.0.0
* @date      2023-01-16 10:54:00
* @warning
*
*/
class CIntraSigAnal
{
private:


public:

protected:

public:
	CIntraSigAnal();																			///< 초기 멤버 변수값 등을 설정하는 객체 생성자 입니다.	
    CIntraSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName = NULL);		///< 초기 멤버 변수값 등을 설정하는 객체 생성자 입니다.	
    virtual ~CIntraSigAnal();																	///< 메모리 해지 등을 처리하고 객체를 소멸합니다.

	void AnalysisStart();																		///< 입력 PDW 데이터로 펄스 간 분석을 수행합니다.


};

#endif // !defined(AFX_IntraSIGANAL_H__30606F89_0BF4_4C89_B5CD_4E9700CBE5E4__INCLUDED_)
