
// RADARANLAPP.h : RADARANLAPP ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.

#include "MainFrm.h"
#include "RADARANLAPPDoc.h"

#define CHILD_WINDOWS			(2)


// CRADARANLAPPApp:
// �� Ŭ������ ������ ���ؼ��� RADARANLAPP.cpp�� �����Ͻʽÿ�.
//

class CRADARANLAPPApp : public CWinAppEx
{
private:
	CMainFrame *m_pMainFrame;

public:
	CRADARANLAPPApp();

	void InitApp();


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
	afx_msg void OnFileNew();
};

extern CRADARANLAPPApp theApp;
