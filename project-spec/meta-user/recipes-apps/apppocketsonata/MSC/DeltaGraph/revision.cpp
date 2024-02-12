
#include "stdafx.h"
#include "MainFrm.h"
#include "ClassView.h"
#include "Resource.h"
#include "DeltaGraph.h"


//////////////////////////////////////////////////////////////////////
// »ý¼º/¼Ò¸ê
//////////////////////////////////////////////////////////////////////

const TCHAR *GetRevision()
{
	static TCHAR st_szRev[100] = { _T("6bcc9b31b7762fa25393b8d4e53cb0a8e4c75071") };
	return st_szRev;
}

const TCHAR *GetBuildDate()
{
	static TCHAR st_szDate[100] = { _T("2024/01/27 11:25:20") };
	return st_szDate;
}