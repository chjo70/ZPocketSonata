// RADARANL.h : RADARANL DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CRADARANLApp
// �� Ŭ������ ������ ������ RADARANL.cpp�� �����Ͻʽÿ�.
//

class CRADARANLApp : public CWinApp
{
public:
	CRADARANLApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
