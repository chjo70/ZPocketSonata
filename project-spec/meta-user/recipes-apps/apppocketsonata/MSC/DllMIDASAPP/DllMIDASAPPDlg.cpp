
// DllMIDASAPPDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DllMIDASAPP.h"
#include "DllMIDASAPPDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDllMIDASAPPDlg 대화 상자



CDllMIDASAPPDlg::CDllMIDASAPPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLLMIDASAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDllMIDASAPPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDllMIDASAPPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_CLOSE()
    ON_BN_CLICKED( IDC_BUTTON_MIDAS, &CDllMIDASAPPDlg::OnBnClickedButtonMidas )
END_MESSAGE_MAP()


// CDllMIDASAPPDlg 메시지 처리기

BOOL CDllMIDASAPPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
    BlueMIDAS::BlueMIDAS::Init( GetSafeHwnd(), true );



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDllMIDASAPPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDllMIDASAPPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDllMIDASAPPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



/**
 * @brief     OnClose
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-05 11:50:50
 * @warning
 */
void CDllMIDASAPPDlg::OnClose()
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

    BlueMIDAS::BlueMIDAS::Close();

    CDialogEx::OnClose();
}


/**
 * @brief     OnBnClickedButtonMidas
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-06 16:41:19
 * @warning
 */
void CDllMIDASAPPDlg::OnBnClickedButtonMidas()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString strSourceFilename;

    char buffer[100];

    if( true == FileDialog( strSourceFilename ) ) {
        CString strOutputFilename;

        SEL_KEYWORD_VALUE stValue;

        //
        strOutputFilename = strSourceFilename;

        if( strOutputFilename.Find( ".dat" ) != 0 ) {
            strOutputFilename.Replace( ".dat", ".xpdw" );

            MakePDWInitValueOfMIDAS( & stValue );
            BlueMIDAS::BlueMIDAS::PDW2MIDAS( ( LPSTR ) ( LPCTSTR ) strSourceFilename, ( LPSTR ) ( LPCTSTR ) strOutputFilename, & stValue );

        }
        else {
            sprintf( buffer, "파일[%s]이 PDW 파일이 아닙니다." , ( LPSTR ) ( LPCTSTR ) strSourceFilename );
            AfxMessageBox( buffer );
        }

    }
    else {
        AfxMessageBox( "파일 변환을 취소 했습니다." );
    }

}

/**
 * @brief     FileDialog
 * @param     CString & strPathname
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-07 17:26:01
 * @warning
 */
bool CDllMIDASAPPDlg::FileDialog( CString &strPathname )
{
    bool bRet=true;
    CFileDialog *pWndFile;

#ifdef _DEBUG
    const BOOL VistaStyle = FALSE;
#else
    const BOOL VistaStyle = TRUE;
#endif

    pWndFile = new CFileDialog( TRUE, NULL, NULL, OFN_ENABLESIZING | OFN_NONETWORKBUTTON | OFN_SHOWHELP | OFN_HIDEREADONLY, _T( "PDW/IQ 파일들 (*.dat)|*.dat;|PDW 파일들 (*.dat)|*.dat;|IQ 파일들 (*.dat)|*.dat;|IF 파일들 (*.)|*.|All Files (*.*)|*.*||" ), NULL, 0, VistaStyle );
    if( pWndFile->DoModal() == IDOK ) {
        strPathname = pWndFile->GetPathName();

    }
    else {
        bRet = false;
    }

    delete pWndFile;

    return bRet;
}



#define DEF_OF_RES_WB_TOA							6.48824 //nano sec
#define DEF_OF_RES_NB_TOA							14.0625 //nano sec

/**
 * @brief     MakePDWInitValueOfMIDAS
 * @param     SEL_KEYWORD_VALUE * pstValue
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-06 17:25:16
 * @warning
 */
void CDllMIDASAPPDlg::MakePDWInitValueOfMIDAS( SEL_KEYWORD_VALUE *pstValue )
{
    // 수집 시간은 현재 시간으로 설정하는데 PDW 데이터 파일의 헤더 수집 시간 정보를 입력하면 됩니다.
    memset( pstValue, 0, sizeof( SEL_KEYWORD_VALUE ) );

    time( & pstValue->tiCollectionTime );

    int nYear = 0;
    int nMonth = 0;
    int nDay = 0;
    int nHour = 0;
    int nMinute = 0;
    int nSecond = 0;
    int nMilliseconds = 0;

    struct tm *timeinfo;

    timeinfo = localtime( & pstValue->tiCollectionTime );

    // 수집 데이터의 지정된 시간으로 설정
    nYear = timeinfo->tm_year + 1900;
    nMonth = timeinfo->tm_mon + 1;
    nDay = timeinfo->tm_mday;
    nHour = timeinfo->tm_hour;
    nMinute = timeinfo->tm_min;
    nSecond = timeinfo->tm_sec;
    CTime time1( nYear, nMonth, nDay, nHour, nMinute, nSecond );
    pstValue->tiTime = time1.GetTime();

    // 과제 중심 주파수 [Hz]
    pstValue->dRF = 9000000000.;

    // 과제 대역폭
    pstValue->dBW = 20000000.;

    // 과제 증폭
    pstValue->gain_mode = 1;			// 자동일때(AGC)는 0, 수동일때는 1

    // 수집 데이터 : PDW 개수
    pstValue->uiNumberOfData = 100;

    // DR의 샘플링 타임
    pstValue->dSamplingPeriod = DEF_OF_RES_NB_TOA * 1e-9;

}
