// SysPara.h: interface for the CSysPara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSPARA_H__F1289AFE_DED3_42FA_926B_BD19E087C182__INCLUDED_)
#define AFX_SYSPARA_H__F1289AFE_DED3_42FA_926B_BD19E087C182__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "_Macro.h"


#include "../INC/System.h"
#include "../../Include/Defines.h"
#include "../SigAnal/_Define.h"
#include "../INC/PDW.h"

#ifdef _MIDAS_

#else
#include "../EmitterMerge/ELMsgDefn.h"
#include "../INC/AetIPL.h"
#endif


#include "_Define.h"
#include "_Struct.h"

#include "_SigAnal.h"

#include "_Type.h"

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
