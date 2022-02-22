
// RADARDIRAPP.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FILE_OPEN, &CRADARDIRAPPApp::OnFileOpen)
	ON_COMMAND(ID_FILE_CONTI_OPEN, &CRADARDIRAPPApp::OnFileContiOpen)
	ON_COMMAND(ID_SW_INIT, &CRADARDIRAPPApp::OnSWInit)
END_MESSAGE_MAP()


// CRADARDIRAPPApp 생성

CRADARDIRAPPApp::CRADARDIRAPPApp()
{
	m_bHiColorIcons = TRUE;

	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 응용 프로그램을 공용 언어 런타임 지원을 사용하여 빌드한 경우(/clr):
	//     1) 이 추가 설정은 다시 시작 관리자 지원이 제대로 작동하는 데 필요합니다.
	//     2) 프로젝트에서 빌드하려면 System.Windows.Forms에 대한 참조를 추가해야 합니다.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 아래 응용 프로그램 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("RADARDIRAPP.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CRADARDIRAPPApp 개체입니다.

CRADARDIRAPPApp theApp;


// CRADARDIRAPPApp 초기화

BOOL CRADARDIRAPPApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면  AfxInitRichEdit2()가 있어야 합니다.	
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.

    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    //_CrtSetBreakAlloc(18304);
    
	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 응용 프로그램의 문서 템플릿을 등록합니다. 문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CRADARDIRAPPDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CRADARDIRAPPView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
 	if (!ProcessShellCommand(cmdInfo))
 		return FALSE;


	InitApp();

	//
	m_pMainFrame=(CMainFrame *) AfxGetApp()->m_pMainWnd;
	m_pDoc = ( CRADARDIRAPPDoc * ) m_pMainFrame->GetActiveDocument();

	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 접미사가 있을 경우에만 DragAcceptFiles를 호출합니다.
	//  SDI 응용 프로그램에서는 ProcessShellCommand 후에 이러한 호출이 발생해야 합니다.
	return TRUE;
}

int CRADARDIRAPPApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	AfxOleTerm(FALSE);

	RadarDirAlgotirhm::RadarDirAlgotirhm::Close();

	SaveProfile();

	return CWinAppEx::ExitInstance();
}

// CRADARDIRAPPApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CRADARDIRAPPApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CRADARDIRAPPApp 사용자 지정 로드/저장 메서드

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

// CRADARDIRAPPApp 메시지 처리기





void CRADARDIRAPPApp::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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

	// 로그 파일을 오픈할 FILE Dialog창을 생성한다.
	pWndFile = new CFileDialog(TRUE, NULL, NULL, OFN_ENABLESIZING | OFN_NONETWORKBUTTON | OFN_SHOWHELP | OFN_HIDEREADONLY, _T("PDW/IQ 파일들 (*.spdw,*.pdw;*.npw;*.epdw;*.xpdw;*.iq;*.siq)|*.spdw;*.pdw;*.npw;*.epdw;*.xpdw;*.iq;*.siq|PDW 파일들 (*.pdw;*.npw;*.spdw;*.epdw;*.xpdw)|*.pdw;*.npw;*.spdw;*.epdw;*.xpdw|IQ 파일들 (*.iq;*.siq;*.eiq)|*.iq;*.siq;*.eiq|All Files (*.*)|*.*||") );

	// Initializes m_ofn structure
	pWndFile->m_ofn.lpstrTitle = _T("PDW 파일 읽어오기...");

	// Call DoModal
	if (pWndFile->DoModal() == IDOK) {
		//m_strWindowtitle = pWndFile->GetFileTitle() + '.' + pWndFile->GetFileExt();
		strPathname = pWndFile->GetPathName();

		// 뷰 관련 파일 액션 처리
		//GetDlgItem(IDC_BUTTON_STEPANAL)->EnableWindow();

		// PDW 데이터 파일 읽기
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
 * @author    조철희 (churlhee.jo@lignex1.com)
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
 * @author    조철희 (churlhee.jo@lignex1.com)
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
 * @author    조철희 (churlhee.jo@lignex1.com)
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
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-14, 14:51
 * @warning
 */
void CRADARDIRAPPApp::OnFileContiOpen()
{

	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	RadarDirAlgotirhm::RadarDirAlgotirhm::SetMute( true );

	// 폴더 선택 다이얼로그
	CFolderPickerDialog Picker(m_strInitPath, OFN_FILEMUSTEXIST, NULL, 0);
	if (Picker.DoModal() == IDOK)
	{
		// 선택된 폴더 경로얻음
		CString strFolderPath = Picker.GetPathName();

		m_strInitPath = strFolderPath;

		//검색 클래스
		CFileFind finder;

		strFolderPath = strFolderPath + "\\*.EPDW";

		//CFileFind는 파일, 디렉터리가 존재하면 TRUE 를 반환함
		BOOL bWorking = finder.FindFile(strFolderPath); //

		CString fileName;
		CString DirName;

		while (bWorking)
		{
			//다음 파일 / 폴더 가 존재하면다면 TRUE 반환
			bWorking = finder.FindNextFile();

			if ( finder.IsDots() || finder.IsDirectory() ) {
				continue;
			}

			//파일 일때
			//else if (finder.IsArchived())
			{
				//파일의 이름
				CString _fileName =  finder.GetFilePath();

// 				// 현재폴더 상위폴더 썸네일파일은 제외
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

	AfxMessageBox( "폴더를 모두 분석 완료했습니다." );

}
