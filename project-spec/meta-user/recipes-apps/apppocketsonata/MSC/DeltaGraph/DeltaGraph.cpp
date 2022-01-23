
// DeltaGraph.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "DeltaGraph.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "DeltaGraphDoc.h"
#include "DeltaGraphView.h"
#include "DeltaGraphView2.h"
#include "revision.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

map<CString, CData *> CMapData::m_gMapData;


// CDeltaGraphApp

BEGIN_MESSAGE_MAP(CDeltaGraphApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CDeltaGraphApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CDeltaGraphApp::OnFileOpen)
END_MESSAGE_MAP()


// CDeltaGraphApp ����

CDeltaGraphApp::CDeltaGraphApp()
{
	m_uiWindowNumber = 0;

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
	SetAppID(_T("DeltaGraph.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CDeltaGraphApp ��ü�Դϴ�.

CDeltaGraphApp theApp;


// CDeltaGraphApp �ʱ�ȭ

BOOL CDeltaGraphApp::InitInstance()
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

	EnableTaskbarInteraction();

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


	//////////////////////////////////////////////////////////////////////////
	//
	Log( enNormal, _T("DeltaGraph+++++++++++++++++++++++++++++++++++++++++++") );

	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_DeltaGraphTYPE,
		RUNTIME_CLASS(CDeltaGraphDoc),
		RUNTIME_CLASS(CChildFrame), // ����� ���� MDI �ڽ� �������Դϴ�.
		RUNTIME_CLASS(CDeltaGraphView2));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	pDocTemplate = new CMultiDocTemplate(IDR_DeltaGraphTYPE,
		RUNTIME_CLASS(CDeltaGraphDoc),
		RUNTIME_CLASS(CChildFrame), // ����� ���� MDI �ڽ� �������Դϴ�.
		RUNTIME_CLASS(CDeltaGraphView));
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

	if( true == cmdInfo.m_strFileName.IsEmpty() ) {
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	}
	else {
		m_strArgument = cmdInfo.m_strFileName;

		OnFileOpen();
		//cmdInfo.m_nShellCommand = CCommandLineInfo::FileOpen;
	}


	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
// 	if (!ProcessShellCommand(cmdInfo))
// 		return FALSE;


	// �� â�� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	pMainFrame->ShowWindow( SW_SHOWMAXIMIZED /* m_nCmdShow */ );
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CDeltaGraphApp::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	AfxOleTerm(FALSE);

	m_theMapData.CloseMapData( NULL );

	TRACE( "\n ExitInstance..ȣ��" );

	//CDeltaGraphDoc::CloseMapData();

	return CWinAppEx::ExitInstance();
}

// CDeltaGraphApp �޽��� ó����


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
public:
	virtual BOOL OnInitDialog();
	CStatic m_CStaticRevDate;
	CStatic m_CStaticRev;
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_REV, m_CStaticRevDate);
	DDX_Control(pDX, IDC_STATIC_REV_DATE, m_CStaticRev);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CDeltaGraphApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


/**
 * @brief     
 * @return    BOOL
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/08 21:48:30
 * @warning   
 */
BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString strRev;

	strRev.Format( _T("SVN Date %s") , GetBuildDate() );
	m_CStaticRev.SetWindowText( strRev );

	strRev.Format( _T("SVN Rev %s") , GetRevision() );
	m_CStaticRevDate.SetWindowText( strRev );
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

// CDeltaGraphApp ����� ���� �ε�/���� �޼���

void CDeltaGraphApp::PreLoadState()
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

void CDeltaGraphApp::LoadCustomState()
{
}

void CDeltaGraphApp::SaveCustomState()
{
}

// CDeltaGraphApp �޽��� ó����

#define PDW_MULTI_WINDOWS			(2)//(1)
#define IQ_MULTI_WINDOWS			(2)//(5)
void CDeltaGraphApp::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString strPathName;

	if( m_strArgument.IsEmpty() == true ) {
		if( true == OpenFile( strPathName, _T("PDW �� IQ ���� �о����...") ) ) {
			RawDataOpen( & strPathName );
		}
	}
	else {
		strPathName = m_strArgument;
		RawDataOpen( & strPathName );
		m_strArgument.Empty();
	}

}

/**
 * @brief     
 * @param     CString * pStrPathname
 * @return    void
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/08 21:43:12
 * @warning   
 */
void CDeltaGraphApp::RawDataOpen( CString *pStrPathname )
{
	int i;

	CDocTemplate *pDocTemplate=nullptr;	
	TCHAR warningMessage[200];

	POSITION pos;
	CMainFrame *pMainFrame=( CMainFrame * ) AfxGetMainWnd();
	CDeltaGraphDoc *pDoc;
	//CDeltaGraphView *pView;
	//CChildFrame *pChild;

 	//ENUM_GRAPH_VIEW viewPDWGraph[PDW_MULTI_WINDOWS] = { enGraphPulseInfo, enGRAPH_PIE, enGRAPH_POLAR, enGRAPH_2D, enGRAPH_MULTI, enGRAPH_3D } ;
	ENUM_SUB_GRAPH viewPDWSubGraph[PDW_MULTI_WINDOWS] = { enSubMenu_1, enSubMenu_1 } ; //, enSubMenu_1, enSubMenu_3, enSubMenu_1, enSubMenu_1 } ;
// 
// 	ENUM_GRAPH_VIEW viewIQGraph[IQ_MULTI_WINDOWS] = { enGraphPulseInfo, enGRAPH_2D, enGRAPH_2D, enGRAPH_2D, enGRAPH_2D } ;
// 	ENUM_SUB_GRAPH viewIQSubGraph[IQ_MULTI_WINDOWS] = { enSubMenu_1, enSubMenu_2, enSubMenu_3, enSubMenu_4, enSubMenu_1 } ;
// 
// 	OnMenuCloseAll();
// 

	if( true == IsExistFile( *pStrPathname ) ) {
		++ m_uiWindowNumber;

		pos = GetFirstDocTemplatePosition();

		for( i=0 ; i < IQ_MULTI_WINDOWS ; ++i ) {
 			pDocTemplate = GetNextDocTemplate( pos );
 
 			pDoc = ( CDeltaGraphDoc *) pDocTemplate->OpenDocumentFile(*pStrPathname);

		}

		::PostMessage( m_pMainWnd->m_hWnd, WM_COMMAND, ID_WINDOW_TILE_HORZ, NULL );

	}
	else {
		wsprintf( warningMessage, _T("���ϸ�[%s]�� �߸� �Է��߽��ϴ�.") , *pStrPathname );
		AfxMessageBox( warningMessage );
	}


}



/**
 * @brief     
 * @param     CString & strPathname
 * @return    bool
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/02/01 16:31:42
 * @warning   
 */
bool CDeltaGraphApp::IsExistFile( CString &strPathname )
{
	bool bRet;
	CFileStatus fs;

	if( CFile::GetStatus( strPathname, fs ) == TRUE ) {
		bRet = true;
	}
	else {
		bRet = false;
	}
	return bRet;
}

/**
 * @brief     
 * @param     CString & strPathName
 * @return    ENUM_DataType
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/08 22:03:45
 * @warning   
 */
ENUM_DataType CDeltaGraphApp::GetDataType(CString &strPathName)
{
	ENUM_DataType enDataType=en_UnknownData;

	strPathName.MakeLower();
	if( 0 != strcmp( strPathName.GetBuffer(), "pdw" ) || 0 != strcmp( strPathName.GetBuffer(), "npw" ) || 0 != strcmp( strPathName.GetBuffer(), "dat" ) ) {
		enDataType = en_PDW_DATA;
	}

	if( 0 != strcmp( strPathName.GetBuffer(), "iq" ) ) {
		enDataType = en_IQ_DATA;
	}

	return enDataType;

}

/**
 * @brief     
 * @param     CString & strPathname
 * @param     TCHAR * pTitle
 * @param     ENUM_OPENTYPE enOpenType
 * @return    bool
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/08 21:43:08
 * @warning   
 */
bool CDeltaGraphApp::OpenFile( CString &strPathname, TCHAR *pTitle, ENUM_OPENTYPE enOpenType )
{
	bool bRet = true;
	CFileDialog *pWndFile;
	TCHAR szinitDir[MAX_PATH];

	CString strFilepath;

	strFilepath = GetFilePath();

#ifdef _DEBUG
	const BOOL VistaStyle=FALSE;
#else
	const BOOL VistaStyle=TRUE;
#endif

	// �α� ������ ������ FILE Dialogâ�� �����Ѵ�.
	switch( enOpenType ) {
	case enOpenPDW :
		pWndFile = new CFileDialog(TRUE, NULL, NULL, OFN_ENABLESIZING | OFN_NONETWORKBUTTON | OFN_SHOWHELP | OFN_HIDEREADONLY, _T("PDW/IQ ���ϵ� (*.spdw,*.pdw;*.npw;*.epdw;*.kpdw;*.zpdw;*.iq;*.eiq;*.siq;*.dat;*.midas)|*.spdw;*.pdw;*.npw;*.epdw;*.kpdw;*.zpdw;*.iq;*.eiq;*.siq;*.dat;*.midas|PDW ���ϵ� (*.pdw;*.npw;*.spdw;*.epdw;*.kpdw;*.zpdw;*.dat)|*.pdw;*.npw;*.spdw;*.epdw;*.kpdw;*.zpdw;*.dat|IQ ���ϵ� (*.iq;*.siq;*.eiq)|*.iq;*.siq;*.eiq|MIDAS ���ϵ� (*.midas)|*.midas|All Files (*.*)|*.*||"), NULL, 0, VistaStyle );
		szinitDir[0] = NULL;
		break;

	case enOpenXLS :
		pWndFile = new CFileDialog(TRUE, NULL, NULL, OFN_ENABLESIZING | OFN_NONETWORKBUTTON | OFN_SHOWHELP | OFN_HIDEREADONLY, _T("���� ��� ���ϵ� (*.xls)|*.xls*|All Files (*.*)|*.*||"), NULL, 0, VistaStyle );

		_tcscpy_s( szinitDir, MAX_PATH, strFilepath.GetBuffer(0) );
		strFilepath.ReleaseBuffer();
		break;

	case enSavePDW :
		pWndFile = new CFileDialog(FALSE, NULL, NULL, OFN_ENABLESIZING | OFN_NONETWORKBUTTON | OFN_SHOWHELP | OFN_HIDEREADONLY, _T("PDW/IQ ���ϵ� (*.spdw,*.pdw;*.npw;*.epdw;*.iq;*.eiq;*.siq)|*.spdw;*.pdw;*.npw;*.epdw;*.iq;*.eiq;*.siq|PDW ���ϵ� (*.pdw;*.npw;*.spdw;*.epdw;*.dat)|*.pdw;*.npw;*.spdw;*.epdw;*.dat|IQ ���ϵ� (*.iq;*.siq;*.eiq)|*.iq;*.eiq;*.siq|All Files (*.*)|*.*||"), NULL, 0, VistaStyle );
		szinitDir[0] = NULL;
		break;

	case enSaveXLS :
		pWndFile = new CFileDialog(FALSE, NULL, NULL, OFN_ENABLESIZING | OFN_NONETWORKBUTTON | OFN_SHOWHELP | OFN_HIDEREADONLY, _T("���� ��� ���ϵ� (*.xls)|*.xls*|All Files (*.*)|*.*||"), NULL, 0, VistaStyle );

		_tcscpy_s( szinitDir, MAX_PATH, strFilepath.GetBuffer(0) );
		strFilepath.ReleaseBuffer();
		break;

	default :
		break;
	}


	// Initializes m_ofn structure
	pWndFile->m_ofn.lpstrTitle = pTitle;			// Ÿ��Ʋ��
	pWndFile->m_ofn.lpstrInitialDir = szinitDir;			// Ÿ��Ʋ��

	// Call DoModal
	if (pWndFile->DoModal() == IDOK) {
		//m_strWindowtitle = pWndFile->GetFileTitle() + '.' + pWndFile->GetFileExt();
		strPathname = pWndFile->GetPathName();

	}
	else {
		bRet = false;
	}

	delete pWndFile;

	return bRet;

}



