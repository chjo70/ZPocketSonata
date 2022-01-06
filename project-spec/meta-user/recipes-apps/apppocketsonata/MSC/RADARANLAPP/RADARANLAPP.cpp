
// RADARANLAPP.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"

#include <crtdbg.h>


#include "afxwinappex.h"
#include "afxdialogex.h"
#include "RADARANLAPP.h"
#include "MainFrm.h"


#include "ChildFrm.h"
#include "RADARANLAPPDoc.h"
#include "RADARANLAPPView.h"

#include "../RadarAnl/RadarAnlAlgorithm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRADARANLAPPApp

BEGIN_MESSAGE_MAP(CRADARANLAPPApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CRADARANLAPPApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	//ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_OPEN, &CRADARANLAPPApp::OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, &CRADARANLAPPApp::OnFileNew)
END_MESSAGE_MAP()


// CRADARANLAPPApp ����

CRADARANLAPPApp::CRADARANLAPPApp()
{
	m_bHiColorIcons = TRUE;

	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���� ���α׷��� ���� ��� ��Ÿ�� ������ ����Ͽ� ������ ���(/clr):
	//     1) �� �߰� ������ �ٽ� ���� ������ ������ ����� �۵��ϴ� �� �ʿ��մϴ�.
	//     2) ������Ʈ���� �����Ϸ��� System.Windows.Forms�� ���� ������ �߰��ؾ� �մϴ�.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: �Ʒ� ���� ���α׷� ID ���ڿ��� ���� ID ���ڿ��� �ٲٽʽÿ�(����).
	// ���ڿ��� ���� ����: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("RADARANLAPP.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CRADARANLAPPApp ��ü�Դϴ�.

CRADARANLAPPApp theApp;


// CRADARANLAPPApp �ʱ�ȭ

BOOL CRADARANLAPPApp::InitInstance()
{
	//_CrtSetBreakAlloc(4480);
	//_CrtMemDumpAllObjectsSince(0); 

	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit ��Ʈ���� ����Ϸ���  AfxInitRichEdit2()�� �־�� �մϴ�.	
	// AfxInitRichEdit2();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
// 	CMultiDocTemplate* pDocTemplate;
// 	pDocTemplate = new CMultiDocTemplate(IDR_RADARANLAPPTYPE,
// 		RUNTIME_CLASS(CRADARANLAPPDoc),
// 		RUNTIME_CLASS(CChildFrame), // ����� ���� MDI �ڽ� �������Դϴ�.
// 		RUNTIME_CLASS(CLOBTableView));
// 	if (!pDocTemplate)
// 		return FALSE;
// 	AddDocTemplate(pDocTemplate);

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_RADARANLAPPTYPE,
		RUNTIME_CLASS(CRADARANLAPPDoc),
		RUNTIME_CLASS(CChildFrame), // ����� ���� MDI �ڽ� �������Դϴ�.
		RUNTIME_CLASS(CLOBTableView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// �� MDI ������ â�� ����ϴ�.
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  MDI ���� ���α׷������� m_pMainWnd�� ������ �� �ٷ� �̷��� ȣ���� �߻��ؾ� �մϴ�.

	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	InitApp();


	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	//if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;

	m_pMainFrame=(CMainFrame *) AfxGetApp()->m_pMainWnd;

	// �� â�� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CRADARANLAPPApp::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	AfxOleTerm(FALSE);

	RadarAnlAlgotirhm::RadarAnlAlgotirhm::Close();

	return CWinAppEx::ExitInstance();
}

// CRADARANLAPPApp �޽��� ó����


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CRADARANLAPPApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CRADARANLAPPApp ����� ���� �ε�/���� �޼���

void CRADARANLAPPApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CRADARANLAPPApp::LoadCustomState()
{
}

void CRADARANLAPPApp::SaveCustomState()
{
}

// CRADARANLAPPApp �޽��� ó����



void CRADARANLAPPApp::InitApp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	bool bRet=false;
	CString strPathName;
	CDocTemplate *pDocTemplate=nullptr;	
	//TCHAR warningMessage[100];

	int i;

	POSITION pos;
	CMainFrame *pMainFrame=( CMainFrame * ) AfxGetMainWnd();
	CRADARANLAPPDoc *pDoc;
	CRADARANLAPPView *pView;
	CChildFrame *pChild;

	SetWindowHandler( pMainFrame->GetOutputWnd()->GetSafeHwnd() );

	RadarAnlAlgotirhm::RadarAnlAlgotirhm::Init( pMainFrame->GetOutputWnd()->GetSafeHwnd(), true, true );

	for( i=0 ; i < CHILD_WINDOWS ; ++i ) {
		pos = GetFirstDocTemplatePosition();

		pDocTemplate = GetNextDocTemplate( pos );

		pDoc= ( CRADARANLAPPDoc *) pDocTemplate->OpenDocumentFile(NULL);

		pChild = ( CChildFrame * ) pMainFrame->GetActiveFrame();
		pChild->SetWindowText( "ACDDD" );
		pView = (CRADARANLAPPView *) pChild->GetActiveView();

		pView->InitView();
	}

}

void CRADARANLAPPApp::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CChildFrame *pChild;
	//CRADARANLAPPView *pView;
	CRADARANLAPPDoc *pDoc;
	
	pChild = ( CChildFrame * ) m_pMainFrame->GetActiveFrame();
	pDoc = (CRADARANLAPPDoc *) pChild->GetActiveDocument();

	pDoc->OnFileOpen();

}


void CRADARANLAPPApp::OnFileNew()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

}


