
// MSIGA.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMSIGAApp:
// �� Ŭ������ ������ ���ؼ��� MSIGA.cpp�� �����Ͻʽÿ�.
//

class CMSIGAApp : public CWinApp
{
public:
	CMSIGAApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMSIGAApp theApp;