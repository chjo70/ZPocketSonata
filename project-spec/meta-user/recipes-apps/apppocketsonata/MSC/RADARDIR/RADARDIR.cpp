// RADARDIR.cpp : �ش� DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"

#define _MAIN_
#define _MAIN_GLOBALS_

#include "../../files/Anal/OFP_Main.h"


// #include "../OFP/Anal/INC/PDW.h"
// #include "../OFP/Anal/SigAnal/_.h"
// #include "../OFP/Anal/SigAnal/_Macro.h"
// 
#include "../../files/Include/globals.h"

#include "RADARDIR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: �� DLL�� MFC DLL�� ���� �������� ��ũ�Ǿ� �ִ� ���
//		MFC�� ȣ��Ǵ� �� DLL���� ���������� ��� �Լ���
//		���� �κп� AFX_MANAGE_STATE ��ũ�ΰ�
//		��� �־�� �մϴ�.
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �Ϲ����� �Լ� ������ ���⿡ �ɴϴ�.
//		}
//
//		�� ��ũ�δ� MFC�� ȣ���ϱ� ����
//		�� �Լ��� �ݵ�� ��� �־�� �մϴ�.
//		��, ��ũ�δ� �Լ��� ù ��° ���̾�� �ϸ� 
//		��ü ������ �����ڰ� MFC DLL��
//		ȣ���� �� �����Ƿ� ��ü ������ ����Ǳ� ����
//		���;� �մϴ�.
//
//		�ڼ��� ������
//		MFC Technical Note 33 �� 58�� �����Ͻʽÿ�.
//

// CRADARDIRApp

BEGIN_MESSAGE_MAP(CRADARDIRApp, CWinApp)
END_MESSAGE_MAP()


// CRADARDIRApp ����

CRADARDIRApp::CRADARDIRApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CRADARDIRApp ��ü�Դϴ�.

CRADARDIRApp theApp;


// CRADARDIRApp �ʱ�ȭ

BOOL CRADARDIRApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
