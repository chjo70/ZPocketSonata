// SysPara.h: interface for the CSysPara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSPARA_H__F1289AFE_DED3_42FA_926B_BD19E087C182__INCLUDED_)
#define AFX_SYSPARA_H__F1289AFE_DED3_42FA_926B_BD19E087C182__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_Type.h"
#include "_Macro.h"

#include "../INC/structs.h"

#include "_Define.h"
#include "_Struct.h"

#include "_SigAnal.h"

#ifdef __cplusplus

class CSysPara
{
public:
	void Init();
	void LoadDefaultSysParameter( void );
	CSysPara();
	virtual ~CSysPara();

};

#endif

#endif // !defined(AFX_SYSPARA_H__F1289AFE_DED3_42FA_926B_BD19E087C182__INCLUDED_)
