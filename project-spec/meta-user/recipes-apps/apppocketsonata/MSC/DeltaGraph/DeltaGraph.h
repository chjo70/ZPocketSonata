
// DeltaGraph.h : DeltaGraph ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


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
// �� Ŭ������ ������ ���ؼ��� DeltaGraph.cpp�� �����Ͻʽÿ�.
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


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
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
