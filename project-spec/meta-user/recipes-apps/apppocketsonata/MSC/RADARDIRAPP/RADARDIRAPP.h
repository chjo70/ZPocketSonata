
// RADARDIRAPP.h : RADARDIRAPP 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.

#include "MainFrm.h"
#include "RADARDIRAPPDoc.h"

// CRADARDIRAPPApp:
// 이 클래스의 구현에 대해서는 RADARDIRAPP.cpp을 참조하십시오.
//

class CRADARDIRAPPApp : public CWinAppEx
{
private:
	CMainFrame *m_pMainFrame;
	CRADARDIRAPPDoc *m_pDoc;

	CString m_strIniFile;

	// INI
	CString m_strInitPath;

public:
	CRADARDIRAPPApp();

	void OnFileOpen();
	bool OpenFile( CString &strPathname, CString &strFileName);
	void InitApp(void);

	void SaveProfile();
	void LoadProfile();


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
	//afx_msg void OnFileOpen();
	afx_msg void OnFileContiOpen();
	afx_msg void OnSWInit();
};

extern CRADARDIRAPPApp theApp;
