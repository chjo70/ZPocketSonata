
// DeltaGraph.h : DeltaGraph 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


#include "../../Files/Anal/SigAnal/_Struct.h"

#include "../../Files/Anal/EmitterMerge/ELMsgDefn.h"
#include "../../Files/Anal/Collect/DataFile/DataFile.h"

//
//////////////////////////////////////////////////////////////////////////

typedef enum {
	enOpenPDW = 0,
	enOpenXLS,
	enSavePDW,
	enSaveXLS

} ENUM_OPENTYPE;

//
//////////////////////////////////////////////////////////////////////////


// CDeltaGraphApp:
// 이 클래스의 구현에 대해서는 DeltaGraph.cpp을 참조하십시오.
//

class CDeltaGraphApp : public CWinAppEx
{
private:
	UINT m_uiWindowNumber;
	CString m_strArgument;

	CMapData m_theMapData;

private:
	bool OpenFile( CString &strPathname, TCHAR *pTitle, ENUM_OPENTYPE enOpenType=enOpenPDW );
	void RawDataOpen( CString *pStrPathname );
	ENUM_DataType GetDataType(CString &strPathName);
	bool IsExistFile( CString &strPathname );

public:
	CDeltaGraphApp();

	inline void CloseMapData( CString *pStrPathname ) { m_theMapData.CloseMapData( pStrPathname ); }
	inline CDataFile *FindMapData( CString *pStrPathname ) { return m_theMapData.FindMapData( pStrPathname ); }
	inline void AddMapData( CString *pStrPathname, CDataFile *pDataFile ) { m_theMapData.AddMapData( pStrPathname, pDataFile ); }

	inline void IncWindowNumber( CDataFile *pDataFile ) { return m_theMapData.IncWindowNumber( pDataFile ); }


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnFileOpen();
};

extern CDeltaGraphApp theApp;
