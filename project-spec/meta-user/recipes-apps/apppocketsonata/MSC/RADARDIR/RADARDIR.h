// RADARDIR.h : RADARDIR DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CRADARDIRApp
// �� Ŭ������ ������ ������ RADARDIR.cpp�� �����Ͻʽÿ�.
//

class CRADARDIRApp : public CWinApp
{
public:
	CRADARDIRApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
