
// RADARDIRAPP.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "RADARDIRAPP.h"
#include "MainFrm.h"

#include "../RadarDIR/RadarDirAlgorithm.h"

#include "RADARDIRAPPDoc.h"
#include "RADARDIRAPPView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern HWND sthWnd;


// CRADARDIRAPPApp

BEGIN_MESSAGE_MAP(CRADARDIRAPPApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CRADARDIRAPPApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FILE_OPEN, &CRADARDIRAPPApp::OnFileOpen)
	ON_COMMAND(ID_FILE_CONTI_OPEN, &CRADARDIRAPPApp::OnFileContiOpen)
	ON_COMMAND(ID_SW_INIT, &CRADARDIRAPPApp::OnSWInit)
END_MESSAGE_MAP()


// CRADARDIRAPPApp ����

CRADARDIRAPPApp::CRADARDIRAPPApp()
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
	SetAppID(_T("RADARDIRAPP.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CRADARDIRAPPApp ��ü�Դϴ�.

CRADARDIRAPPApp theApp;


// CRADARDIRAPPApp �ʱ�ȭ

BOOL CRADARDIRAPPApp::InitInstance()
{
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

    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    //_CrtSetBreakAlloc(18304);
    
	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CRADARDIRAPPDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CRADARDIRAPPView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
 	if (!ProcessShellCommand(cmdInfo))
 		return FALSE;


	InitApp();

	//
	m_pMainFrame=(CMainFrame *) AfxGetApp()->m_pMainWnd;
	m_pDoc = ( CRADARDIRAPPDoc * ) m_pMainFrame->GetActiveDocument();

	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  SDI ���� ���α׷������� ProcessShellCommand �Ŀ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
	return TRUE;
}

int CRADARDIRAPPApp::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	AfxOleTerm(FALSE);

	RadarDirAlgotirhm::RadarDirAlgotirhm::Close();

	SaveProfile();

	return CWinAppEx::ExitInstance();
}

// CRADARDIRAPPApp �޽��� ó����


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
void CRADARDIRAPPApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CRADARDIRAPPApp ����� ���� �ε�/���� �޼���

void CRADARDIRAPPApp::PreLoadState()
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

void CRADARDIRAPPApp::LoadCustomState()
{
}

void CRADARDIRAPPApp::SaveCustomState()
{
}

// CRADARDIRAPPApp �޽��� ó����





void CRADARDIRAPPApp::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString strPathName;

	RadarDirAlgotirhm::RadarDirAlgotirhm::SetMute( false );

	if( true == OpenFile( strPathName ) ) {
		m_pDoc->OpenFile( strPathName );
	}
}

bool CRADARDIRAPPApp::OpenFile( CString &strPathname )
{
	bool bRet = true;
	CFileDialog *pWndFile;

	// �α� ������ ������ FILE Dialogâ�� �����Ѵ�.
	pWndFile = new CFileDialog(TRUE, NULL, NULL, OFN_ENABLESIZING | OFN_NONETWORKBUTTON | OFN_SHOWHELP | OFN_HIDEREADONLY, _T("PDW/IQ ���ϵ� (*.spdw,*.pdw;*.npw;*.epdw;*.xpdw;*.iq;*.siq)|*.spdw;*.pdw;*.npw;*.epdw;*.xpdw;*.iq;*.siq|PDW ���ϵ� (*.pdw;*.npw;*.spdw;*.epdw;*.xpdw)|*.pdw;*.npw;*.spdw;*.epdw;*.xpdw|IQ ���ϵ� (*.iq;*.siq;*.eiq)|*.iq;*.siq;*.eiq|All Files (*.*)|*.*||") );

	// Initializes m_ofn structure
	pWndFile->m_ofn.lpstrTitle = _T("PDW ���� �о����...");

	// Call DoModal
	if (pWndFile->DoModal() == IDOK) {
		//m_strWindowtitle = pWndFile->GetFileTitle() + '.' + pWndFile->GetFileExt();
		strPathname = pWndFile->GetPathName();

		// �� ���� ���� �׼� ó��
		//GetDlgItem(IDC_BUTTON_STEPANAL)->EnableWindow();

		// PDW ������ ���� �б�
		//OpenPdwFile(strPathname);

	}
	else {
		bRet = false;
	}

	delete pWndFile;

	return bRet;

}

void CRADARDIRAPPApp::InitApp(void)
{
 	CMainFrame *pMainFrame=( CMainFrame * ) AfxGetMainWnd();

 	RadarDirAlgotirhm::RadarDirAlgotirhm::Init( pMainFrame->GetOutputWnd()->GetSafeHwnd(), true );

    RadarDirAlgotirhm::RadarDirAlgotirhm::LoadCEDLibrary();

	m_strIniFile = AfxGetApp()->m_pszHelpFilePath;
	m_strIniFile.Replace(".HLP", ".ini");

	LoadProfile();

	//POSITION pos;
	//CRADARDIRAPPDoc *pDoc;
	//CRADARDIRAPPView *pView;
	//CChildFrame *pChild;
	//CDocTemplate *pDocTemplate=nullptr;	

	//pos = GetFirstDocTemplatePosition();

	//pDocTemplate = GetNextDocTemplate( pos );

	//pDoc= ( CRADARDIRAPPDoc *) pDocTemplate->OpenDocumentFile(NULL);

	//pChild = ( CChildFrame * ) pMainFrame->GetActiveFrame();
	//pView = (CRADARDIRAPPView *) pChild->GetActiveView();

	//pView->InitView();

}

/**
 * @brief     LoadProfile
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-14, 14:51
 * @warning
 */
void CRADARDIRAPPApp::LoadProfile()
{
	char szBuffer[100];

	::GetPrivateProfileString( "Settings", "FOLDER", "C:\\", szBuffer, 100, m_strIniFile);
	m_strInitPath = szBuffer;

	//::GetPrivateProfileString( "SQL_SERVER", "IP", "C:\\", szBuffer, 100, m_strIniFile);
	//m_strInitPath = szBuffer;
}

/**
 * @brief     SaveProfile
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-14, 14:51
 * @warning
 */
void CRADARDIRAPPApp::SaveProfile()
{
	//char szBuffer[100];

	//sprintf_s(szBuffer, sizeof(szBuffer), "ON");
	::WritePrivateProfileString( "Settings", "FOLDER", (LPSTR) (LPCTSTR) m_strInitPath, m_strIniFile);
}

/**
 * @brief     OnSWInit
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-14, 14:51
 * @warning
 */
void CRADARDIRAPPApp::OnSWInit()
{
	RadarDirAlgotirhm::RadarDirAlgotirhm::SWInit();
}

/**
 * @brief     OnFileContiOpen
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-14, 14:51
 * @warning
 */
void CRADARDIRAPPApp::OnFileContiOpen()
{

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	RadarDirAlgotirhm::RadarDirAlgotirhm::SetMute( true );

	// ���� ���� ���̾�α�
	CFolderPickerDialog Picker(m_strInitPath, OFN_FILEMUSTEXIST, NULL, 0);
	if (Picker.DoModal() == IDOK)
	{
		// ���õ� ���� ��ξ���
		CString strFolderPath = Picker.GetPathName();

		m_strInitPath = strFolderPath;

		//�˻� Ŭ����
		CFileFind finder;

		strFolderPath = strFolderPath + "\\*.EPDW";

		//CFileFind�� ����, ���͸��� �����ϸ� TRUE �� ��ȯ��
		BOOL bWorking = finder.FindFile(strFolderPath); //

		CString fileName;
		CString DirName;

		while (bWorking)
		{
			//���� ���� / ���� �� �����ϸ�ٸ� TRUE ��ȯ
			bWorking = finder.FindNextFile();

			if ( finder.IsDots() || finder.IsDirectory() ) {
				continue;
			}

			//���� �϶�
			//else if (finder.IsArchived())
			{
				//������ �̸�
				CString _fileName =  finder.GetFilePath();

// 				// �������� �������� ����������� ����
// 				if( _fileName == _T(".") || 
// 					_fileName == _T("..")|| 
// 					_fileName == _T("Thumbs.db") ) continue;

				//fileName =  finder.GetFileTitle();

				m_pDoc->OpenFile( _fileName );
				Sleep( 100 );
			}

		}

	}

	RadarDirAlgotirhm::RadarDirAlgotirhm::SetMute( false );

	AfxMessageBox( "������ ��� �м� �Ϸ��߽��ϴ�." );

}
