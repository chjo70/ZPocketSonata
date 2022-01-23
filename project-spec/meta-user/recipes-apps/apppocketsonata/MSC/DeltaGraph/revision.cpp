
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
	static TCHAR st_szRev[100] = { _T("039a27912f07cfb903f782dc304a40cbcdbf0713") };
	return st_szRev;
}

const TCHAR *GetBuildDate()
{
	static TCHAR st_szDate[100] = { _T("2020/03/08 18:24:09") };
	return st_szDate;
}