
// RADARDIRAPP.h : RADARDIRAPP ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.

#include "MainFrm.h"
#include "RADARDIRAPPDoc.h"

// CRADARDIRAPPApp:
// �� Ŭ������ ������ ���ؼ��� RADARDIRAPP.cpp�� �����Ͻʽÿ�.
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
	//afx_msg void OnFileOpen();
	afx_msg void OnFileContiOpen();
	afx_msg void OnSWInit();
};

extern CRADARDIRAPPApp theApp;
