
// MSIGADlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MSIGA.h"
#include "MSIGADlg.h"
#include "afxdialogex.h"

#include <string>

#include "../../files/Include/globals.h"

#include "../../files/Utils/ccommonutils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMSIGADlg 대화 상자




CMSIGADlg::CMSIGADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMSIGADlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMSIGADlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange( pDX );
    DDX_Control( pDX, IDC_COMBO_FREQTYPE, m_ComboFreqType );
    DDX_Control( pDX, IDC_COMBO_PRITYPE, m_ComboPRIType );
    DDX_Control( pDX, IDC_COMBO_DOATYPE, m_ComboDOAType );
    DDX_Control( pDX, IDC_COMBO_FREQPATTERNTYPE, m_ComboFreqPatternType );
    DDX_Control( pDX, IDC_COMBO_PRIPATTERNTYPE, m_ComboPRIPatternType );
    DDX_Control( pDX, IDC_COMBO_FREQLEVEL, m_ComboFreqLevel );
    DDX_Control( pDX, IDC_COMBO_PRILEVEL, m_ComboPRILevel );
    DDX_Control( pDX, IDC_COMBO_PRIJITTER, m_ComboPRIJitter );
    DDX_Control( pDX, IDC_COMBO_SCANTYPE, m_ComboScanType );
    DDX_Control( pDX, IDC_EDIT_DOA, m_CEditDOA );
    DDX_Control( pDX, IDC_EDIT_FREQ, m_CEditFreq );
    DDX_Control( pDX, IDC_EDIT_PRI, m_CEditPRI );
    DDX_Control( pDX, IDC_EDIT_PW, m_CEditPW );
    DDX_Control( pDX, IDC_EDIT_MISSINGPERCENT, m_CEditMissingPercent );
    DDX_Control( pDX, IDC_EDIT_SCANPERIOD, m_CEditScanPeriod );
    DDX_Control( pDX, IDC_EDIT_SIGNALINTENSITY, m_CEditSignalIntensity );
    DDX_Control( pDX, IDC_EDIT_DDROFFSET, m_CEditDDROffset );
    DDX_Control( pDX, IDC_EDIT_PULSEPERLOBE, m_CEditPulsePerLobe );
    DDX_Control( pDX, IDC_EDIT_AMPLITUDE, m_CEditAmplitude );
    DDX_Control( pDX, IDC_EDIT_FREQBW, m_CEditFreqBW );
    DDX_Control( pDX, IDC_EDIT_PRIPERIOD, m_CEditPRIPeriod );
    DDX_Control( pDX, IDC_EDIT_FREQPERIOD, m_CEditFreqPeriod );
    DDX_Control( pDX, IDC_EDIT_DOARANGE, m_CEditDOARange );
    DDX_Control( pDX, IDC_EDIT_FREQ_PULSEPERLOBE, m_CEditFreqPulsePerLobe );
    DDX_Control( pDX, IDC_EDIT_FREQ_PULSEPERLOBE2, m_CEditPRIPulsePerLobe );
    DDX_Control( pDX, IDC_COMBO_RADAR_TEST, m_ComboRadarTest );
    DDX_Control( pDX, IDC_COMBO_SIGTYPE, m_ComboSignalType );
}

BEGIN_MESSAGE_MAP(CMSIGADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_NCDESTROY()
    ON_BN_CLICKED(ID_SIM_START, &CMSIGADlg::OnBnClickedSimStart)
	ON_BN_CLICKED( ID_SIM_LIBRARY, &CMSIGADlg::OnBnClickedSimLibrary )
    ON_CBN_SELCHANGE( IDC_COMBO_FREQTYPE, &CMSIGADlg::OnSelchangeComboFreqType )
    ON_CBN_SELCHANGE( IDC_COMBO_FREQPATTERNTYPE, &CMSIGADlg::OnSelchangeComboFreqPatternType )
    ON_CBN_SELCHANGE( IDC_COMBO_PRITYPE, &CMSIGADlg::OnSelchangeComboPRIType )
    ON_CBN_SELCHANGE( IDC_COMBO_SCANTYPE, &CMSIGADlg::OnSelchangeComboScanType )
    ON_CBN_SELCHANGE( IDC_COMBO_PRIPATTERNTYPE, &CMSIGADlg::OnSelchangeComboPRIPatternType )
    ON_CBN_SELCHANGE( IDC_COMBO_RADAR_TEST, &CMSIGADlg::OnSelchangeComboRadarTest )
    ON_BN_CLICKED( IDOK_SAVE, &CMSIGADlg::OnBnClickedSave )
    //ON_BN_CLICKED( IDOK, &CMSIGADlg::OnBnClickedOk )
    ON_BN_CLICKED( ID_STOPSIGGEN, &CMSIGADlg::OnBnClickedStopSigGen )
END_MESSAGE_MAP()


// 외부 함수 정의
extern void Start( int iArgc, char *iArgv[], void *pParent );
extern void StopSigGen( bool bEnable );
extern void End();
extern void ss();

extern void SIM_Start( bool bReqStart );
extern void SIM_Library();

#ifdef _LOG_ANALTYPE_
extern CRITICAL_SECTION g_CSTrace;

#endif


// CMSIGADlg 메시지 처리기

BOOL CMSIGADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	//ShowWindow(SW_MINIMIZE);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    m_bStopSigGen = true;
    OnBnClickedStopSigGen();

    unsigned int i;
    char buffer[100];

    m_ComboDOAType.AddString( "고정" );
    m_ComboDOAType.AddString( "멀티" );
    m_ComboDOAType.AddString( "가우시안" );

    m_ComboFreqType.AddString( "고정" );
    m_ComboFreqType.AddString( "호핑" );
    m_ComboFreqType.AddString( "어자일" );
    m_ComboFreqType.AddString( "패턴" );

    m_ComboFreqPatternType.AddString( "사인형" );
    m_ComboFreqPatternType.AddString( "슬라이드(+)" );
    m_ComboFreqPatternType.AddString( "슬라이드(-)" );
    m_ComboFreqPatternType.AddString( "톱니파" );

    m_ComboSignalType.AddString( "NORMAL" );
    m_ComboSignalType.AddString( "CW" );
    m_ComboSignalType.AddString( "FMOP(TRI)" );
    m_ComboSignalType.AddString( "FMOP(증가)" );
    m_ComboSignalType.AddString( "FMOP(감소)" );
    m_ComboSignalType.AddString( "FMOP(모름)" );
    m_ComboSignalType.AddString( "CW FMOP(TRI)" );
    m_ComboSignalType.AddString( "CW FMOP(증가)" );
    m_ComboSignalType.AddString( "CW FMOP(감소)" );
    m_ComboSignalType.AddString( "CW FMOP(모름)" );
    m_ComboSignalType.AddString( "PMOP" );
    m_ComboSignalType.AddString( "CW PMOP" );
    m_ComboSignalType.AddString( "SHORT" );
    m_ComboSignalType.AddString( "DOPPLER" );
    m_ComboSignalType.AddString( "HIGHPRF" );

    for( i = 2; i <= MAX_STAGGER_LEVEL_POSITION; ++i ) {
        sprintf( buffer, "%d", i );
        m_ComboFreqLevel.AddString( buffer );
        m_ComboPRILevel.AddString( buffer );
    }

    for( i = 1; i <= 27; ++i ) {
        sprintf( buffer, "%d", i );
        m_ComboPRIJitter.AddString( buffer );
    }

    m_ComboRadarTest.AddString( "#--" );
    for( i = 1; i <= 50 ; ++i ) {
        sprintf( buffer, "#%02d", i );
        m_ComboRadarTest.AddString( buffer );
    }

    m_ComboPRIType.AddString( "고정" );
    m_ComboPRIType.AddString( "지터" );
    m_ComboPRIType.AddString( "드웰" );
    m_ComboPRIType.AddString( "스태거" );
    m_ComboPRIType.AddString( "패턴" );

    m_ComboPRIPatternType.AddString( "사인형" );
    m_ComboPRIPatternType.AddString( "슬라이드(+)" );
    m_ComboPRIPatternType.AddString( "슬라이드(-)" );
    m_ComboPRIPatternType.AddString( "톱니파" );

    m_ComboScanType.AddString( "원형[초]" );
    m_ComboScanType.AddString( "UNI-Directional[초]" );
    m_ComboScanType.AddString( "BI-Directional[초]" );
    m_ComboScanType.AddString( "Conical[Hz]" );
    m_ComboScanType.AddString( "Steady" );

    //_CrtSetBreakAlloc(223); // 116 번째 메모리 생성시 프레이크 걸리도록 추가
    strcpy( m_szIniFileName, "./RadarPDW.ini" );

    LoadINI( m_szIniFileName );

    UpdateRadarPDW();

    LoadRadarPDW();

    OnSelchangeComboFreqType();
    OnSelchangeComboPRIType();
    OnSelchangeComboScanType();

	m_bReqStart = true;

    srand( 0 );

#ifdef _LOG_ANALTYPE_
    InitializeCriticalSection( & g_CSTrace );

#endif

    Start( __argc, __argv, this );

	std::string strBuffer;

    strBuffer = string_format( (const char *) "EW신호처리판#%d", g_enBoardId );
	SetWindowText( strBuffer.c_str() );

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMSIGADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
    else if( nID == SC_CLOSE ) {
        AfxGetMainWnd()->PostMessageA( WM_CLOSE );
    }
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMSIGADlg::OnPaint()
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
HCURSOR CMSIGADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMSIGADlg::OnNcDestroy()
{
    CDialogEx::OnNcDestroy();

    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
    End();

}

/**
 * @brief     OnBnClickedSimStart
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-12 16:07:42
 * @warning
 */
void CMSIGADlg::OnBnClickedSimStart()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem( ID_SIM_START )->EnableWindow( FALSE );

    m_bStopSigGen = false;
    OnBnClickedStopSigGen();

    if( m_bReqStart ) {
        ++ m_uiCoStart;

        LoadRadarPDW();

        SaveINI( m_szIniFileName, 1 );

        GetDlgItem( ID_SIM_START )->SetWindowTextA( "운용제어/종료요청" );
    }
    else {
		GetDlgItem( ID_SIM_START )->SetWindowTextA( "운용제어/시작요청" );
    }

    SIM_Start( m_bReqStart );

	m_bReqStart = !m_bReqStart;

    GetDlgItem( ID_SIM_START )->EnableWindow( TRUE );

}

/**
 * @brief     UpdateRadarPDW
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-17 15:39:31
 * @warning
 */
void CMSIGADlg::UpdateRadarPDW( int iRadarTest )
{
    char buffer[100];
    sprintf_s( buffer, 100, "%.1f", g_stRadarPDW.fDOA );
    m_CEditDOA.SetWindowTextA( buffer );

    sprintf_s( buffer, 100, "%.1f", g_stRadarPDW.fFreq );
    m_CEditFreq.SetWindowTextA( buffer );

    sprintf_s( buffer, 100, "%.1f", g_stRadarPDW.fPRI );
    m_CEditPRI.SetWindowTextA( buffer );

    sprintf_s( buffer, 100, "%.1f", g_stRadarPDW.fPW );
    m_CEditPW.SetWindowTextA( buffer );

    sprintf_s( buffer, 100, "%d", g_stRadarPDW.iMissingPercent );
    m_CEditMissingPercent.SetWindowTextA( buffer );

    sprintf_s( buffer, 100, "%.1f", g_stRadarPDW.fScanPeriod );
    m_CEditScanPeriod.SetWindowTextA( buffer );

    sprintf( buffer, "%d", g_stRadarPDW.iSignalIntensity );
    m_CEditSignalIntensity.SetWindowTextA( buffer );

    sprintf( buffer, "%d", g_stRadarPDW.iAmplitude );
    m_CEditAmplitude.SetWindowTextA( buffer );

    sprintf( buffer, "%d", g_stRadarPDW.iCoPulsePerLobe );
    m_CEditPulsePerLobe.SetWindowTextA( buffer );

    sprintf( buffer, "%d", g_stRadarPDW.iDDROffset );
    m_CEditDDROffset.SetWindowTextA( buffer );

    sprintf( buffer, "%d", g_stRadarPDW.iFreqBW );
    m_CEditFreqBW.SetWindowTextA( buffer );

    sprintf_s( buffer, 100, "%.1f", g_stRadarPDW.fPRIPeriod );
    m_CEditPRIPeriod.SetWindowTextA( buffer );

    sprintf_s( buffer, 100, "%.1f", g_stRadarPDW.fFreqPeriod );
    m_CEditFreqPeriod.SetWindowTextA( buffer );

    sprintf_s( buffer, 100, "%.1f", g_stRadarPDW.fDOARange );
    m_CEditDOARange.SetWindowTextA( buffer );

    sprintf_s( buffer, 100, "%d", g_stRadarPDW.iFreqPulsePerLobe );
    m_CEditFreqPulsePerLobe.SetWindowTextA( buffer );

    sprintf_s( buffer, 100, "%d", g_stRadarPDW.iPRIPulsePerLobe );
    m_CEditPRIPulsePerLobe.SetWindowTextA( buffer );


    m_ComboDOAType.SetCurSel( ( int ) g_stRadarPDW.enDOA );

    m_ComboFreqType.SetCurSel( ( int ) g_stRadarPDW.enFreqType );
    m_ComboFreqPatternType.SetCurSel( ( int ) g_stRadarPDW.enFreqPatternType - 1 );
    m_ComboFreqLevel.SetCurSel( ( int ) g_stRadarPDW.iCoFreqHoopingPositions - 2 );

    m_ComboPRIType.SetCurSel( ( int ) g_stRadarPDW.enPRIType );
    m_ComboPRIPatternType.SetCurSel( ( int ) g_stRadarPDW.enPRIPatternType - 1 );
    m_ComboPRILevel.SetCurSel( ( int ) g_stRadarPDW.iCoPRIDwellStaggerPositions - 2 );
    m_ComboPRIJitter.SetCurSel( ( int ) ( ( g_stRadarPDW.iJitterRatio ) - 1 ) );

    m_ComboScanType.SetCurSel( ( int ) g_stRadarPDW.enScanType - 1 );

    m_ComboRadarTest.SetCurSel( iRadarTest );

    m_ComboSignalType.SetCurSel( g_stRadarPDW.iSignalType );

}

/**
 * @brief     UpdateRadarPDW
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-17 15:35:23
 * @warning
 */
void CMSIGADlg::LoadRadarPDW()
{
    CString strData;

    g_stRadarPDW.iNoRadar = m_ComboRadarTest.GetCurSel();

    g_stRadarPDW.iSignalType = m_ComboSignalType.GetCurSel();
    g_stRadarPDW.fFMOPBW = 40.0;

    g_stRadarPDW.enDOA = ( ENUM_AET_AOA ) m_ComboDOAType.GetCurSel();
    m_CEditDOA.GetWindowText( strData );
    g_stRadarPDW.fDOA = ( float ) atof( strData );
    m_CEditDOARange.GetWindowText( strData );
    g_stRadarPDW.fDOARange = ( float ) atof( strData );

    g_stRadarPDW.enFreqType = ( ENUM_AET_FRQ_TYPE ) m_ComboFreqType.GetCurSel();
    g_stRadarPDW.enFreqPatternType = ( ENUM_AET_FREQ_PRI_PATTERN_TYPE ) ( m_ComboFreqPatternType.GetCurSel() + 1 );
    m_ComboFreqLevel.GetWindowText( strData );
    g_stRadarPDW.iCoFreqHoopingPositions = atoi( strData );
    m_CEditFreq.GetWindowText( strData );
    g_stRadarPDW.fFreq = ( float ) atof( strData );
    m_CEditFreqBW.GetWindowText( strData );
    g_stRadarPDW.iFreqBW = atoi( strData );
    m_CEditFreqPeriod.GetWindowText( strData );
    g_stRadarPDW.fFreqPeriod = ( float ) atof( strData );
    m_CEditFreqPulsePerLobe.GetWindowText( strData );
    g_stRadarPDW.iFreqPulsePerLobe = atoi( strData );

    g_stRadarPDW.enPRIType = ( ENUM_AET_PRI_TYPE ) m_ComboPRIType.GetCurSel();
    g_stRadarPDW.enPRIPatternType = ( ENUM_AET_FREQ_PRI_PATTERN_TYPE ) ( m_ComboPRIPatternType.GetCurSel() + 1 );
    m_ComboPRILevel.GetWindowText( strData );
    g_stRadarPDW.iCoPRIDwellStaggerPositions = atoi( strData );
    m_CEditPRI.GetWindowText( strData );
    g_stRadarPDW.fPRI = ( float ) atof( strData );
    m_CEditPRIPeriod.GetWindowText( strData );
    g_stRadarPDW.fPRIPeriod = ( float ) atof( strData );
    m_ComboPRIJitter.GetWindowText( strData );
    g_stRadarPDW.iJitterRatio = atoi( strData );
    m_CEditPRIPulsePerLobe.GetWindowText( strData );
    g_stRadarPDW.iPRIPulsePerLobe = atoi( strData );

    if( g_stRadarPDW.enPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER ) {
        switch( g_stRadarPDW.iCoPRIDwellStaggerPositions ) {
            case 2:
                {
                    float fStaggerPositions[2] = { 770, 777 };

                    memcpy( g_stRadarPDW.fStaggerPositions, fStaggerPositions, sizeof( float ) * (size_t) g_stRadarPDW.iCoPRIDwellStaggerPositions );
                }
                break;

            case 3:
                {
                    // 스태거 3단 엘리먼트 값 정의
                    float fStaggerPositions[3] = { 100, 125, 100 };

                    memcpy( g_stRadarPDW.fStaggerPositions, fStaggerPositions, sizeof( float ) * ( size_t ) g_stRadarPDW.iCoPRIDwellStaggerPositions );
                }
                break;

            case 4:
                {
                    if( g_stRadarPDW.enFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN ) {
                        if( m_uiCoStart % 2 == 0 ) {
                            // 스태거 4단 엘리먼트 값 정의
                            float fStaggerPositions[4] = { 356, 364, 349, 365 };

                            memcpy( g_stRadarPDW.fStaggerPositions, fStaggerPositions, sizeof( float ) * 4 );
                        }
                        else {
                            // 스태거 4단 엘리먼트 값 정의
                            float fStaggerPositions[4] = { 556, 564, 549, 565 };

                            memcpy( g_stRadarPDW.fStaggerPositions, fStaggerPositions, sizeof( float ) * 4 );

                        }
                    }
                    else {
                        // 스태거 4단 엘리먼트 값 정의
                        float fStaggerPositions[4] = { 650, 657, 680, 672 };

                        memcpy( g_stRadarPDW.fStaggerPositions, fStaggerPositions, sizeof( float ) * 4 );
                    }
                }
                break;

            case 6:
                {
                    // 스태거 6단 엘리먼트 값 정의
                    float fStaggerPositions[6] = { 1899, 1899, 2099, 2099, 1999, 1999 };

                    memcpy( g_stRadarPDW.fStaggerPositions, fStaggerPositions, sizeof( float ) * ( size_t ) g_stRadarPDW.iCoPRIDwellStaggerPositions );
                }
                break;

            case 8:
                {
                    // 스태거 8단 엘리먼트 값 정의
                    float fStaggerPositions[8] = { 527, 516, 538, 504, 522, 511, 532, 507 };

                    memcpy( g_stRadarPDW.fStaggerPositions, fStaggerPositions, sizeof( float ) * ( size_t ) g_stRadarPDW.iCoPRIDwellStaggerPositions );
                }
                break;

            case 12:
                {
                    // 스태거 12단 엘리먼트 값 정의
                    float fStaggerPositions[12] = { 3484, 3502, 3489, 3502, 3489, 3502, 3489, 3497, 3489, 3502, 3489, 3502 };

                    memcpy( g_stRadarPDW.fStaggerPositions, fStaggerPositions, sizeof( float ) * ( size_t ) g_stRadarPDW.iCoPRIDwellStaggerPositions );
                }
                break;

            case 26:
                {
                    // 스태거 26단 엘리먼트 값 정의
                    float fStaggerPositions[26] = { 3484, 3502, 3489, 3502, 3489, 3502, 3489, 3497, 3489, 3502, 3489, 3502, 3498, \
                                                    3484, 3502, 3489, 3502, 3489, 3502, 3489, 3497, 3489, 3502, 3489, 3502, 3494 };

                    memcpy( g_stRadarPDW.fStaggerPositions, fStaggerPositions, sizeof( float ) * ( size_t ) g_stRadarPDW.iCoPRIDwellStaggerPositions );
                }
                break;

            default:
                {
                    // 스태거 32단 엘리먼트 값 정의
                    float fStaggerPositions[32] = { 180, 195, 210, 190, 180, 210, 220, 190, \
                                                    195, 210, 195, 180, 210, 220, 190, 180, \
                                                    215, 210, 190, 180, 200, 210, 180, 170, \
                                                    185, 210, 180, 210, 180, 210, 190, 210 };

                    g_stRadarPDW.iCoPRIDwellStaggerPositions = 32;
                    memcpy( g_stRadarPDW.fStaggerPositions, fStaggerPositions, sizeof( float ) * ( size_t ) g_stRadarPDW.iCoPRIDwellStaggerPositions );

                }
                break;

        }

        g_stRadarPDW.fPRI = TMeanInArray<float>( g_stRadarPDW.fStaggerPositions, (unsigned int) g_stRadarPDW.iCoPRIDwellStaggerPositions );

    }


    g_stRadarPDW.enScanType = ( ENUM_AET_SCAN_TYPE ) ( m_ComboScanType.GetCurSel() + 1 );

    m_CEditAmplitude.GetWindowText( strData );
    g_stRadarPDW.iAmplitude = atoi( strData );

    m_CEditSignalIntensity.GetWindowText( strData );
    g_stRadarPDW.iSignalIntensity = atoi( strData );
    m_CEditScanPeriod.GetWindowText( strData );
    g_stRadarPDW.fScanPeriod = ( float ) atof( strData );

    m_CEditPW.GetWindowText( strData );
    g_stRadarPDW.fPW = ( float ) atof( strData );

    m_CEditMissingPercent.GetWindowText( strData );
    g_stRadarPDW.iMissingPercent = atoi( strData );
    m_CEditDDROffset.GetWindowText( strData );
    g_stRadarPDW.iDDROffset = atoi( strData );

}


/**
 * @brief     OnBnClickedSimLibrary
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-12 16:07:38
 * @warning
 */
void CMSIGADlg::OnBnClickedSimLibrary()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SIM_Library();

}


/**
 * @brief     OnSelchangeComboFreqType
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-08 10:57:30
 * @warning
 */
void CMSIGADlg::OnSelchangeComboFreqType()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    ENUM_AET_FRQ_TYPE enFreqType = ( ENUM_AET_FRQ_TYPE ) m_ComboFreqType.GetCurSel();

    switch( enFreqType ) {
        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED:
            m_ComboFreqPatternType.EnableWindow( FALSE );
            m_ComboFreqLevel.EnableWindow( FALSE );
            m_CEditFreqBW.EnableWindow( FALSE );
            m_CEditFreqPeriod.EnableWindow( FALSE );
            m_CEditFreqPulsePerLobe.EnableWindow( FALSE );

            GetDlgItem( ID_SIM_START )->EnableWindow( TRUE );
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING:
            m_ComboFreqPatternType.EnableWindow( FALSE );
            m_ComboFreqLevel.EnableWindow( TRUE );
            m_CEditFreqBW.EnableWindow( FALSE );
            m_CEditFreqPeriod.EnableWindow( FALSE );
            m_CEditFreqPulsePerLobe.EnableWindow( TRUE );

            GetDlgItem( ID_SIM_START )->EnableWindow( TRUE );
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE:
            m_ComboFreqPatternType.EnableWindow( FALSE );
            m_ComboFreqLevel.EnableWindow( FALSE );
            m_CEditFreqBW.EnableWindow( TRUE );
            m_CEditFreqPeriod.EnableWindow( FALSE );
            m_CEditFreqPulsePerLobe.EnableWindow( FALSE );

            GetDlgItem( ID_SIM_START )->EnableWindow( TRUE );
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN:
            m_ComboFreqPatternType.EnableWindow( TRUE );
            m_ComboFreqLevel.EnableWindow( FALSE );
            m_CEditFreqBW.EnableWindow( TRUE );
            m_CEditFreqPeriod.EnableWindow( TRUE );
            m_CEditFreqPulsePerLobe.EnableWindow( TRUE );

            GetDlgItem( ID_SIM_START )->EnableWindow( TRUE );
            break;

        default:
            break;

    }

}


/**
 * @brief     OnSelchangeComboFreqPatternType
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-08 11:03:51
 * @warning
 */
void CMSIGADlg::OnSelchangeComboFreqPatternType()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    // ENUM_AET_FRQ_TYPE enFreqType = ( ENUM_AET_FRQ_TYPE ) m_ComboFreqType.GetCurSel();
}


/**
 * @brief     OnSelchangeComboPRIType
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-08 11:28:57
 * @warning
 */
void CMSIGADlg::OnSelchangeComboPRIType()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    ENUM_AET_PRI_TYPE enPRIType = ( ENUM_AET_PRI_TYPE ) m_ComboPRIType.GetCurSel();

    switch( enPRIType ) {
        case ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED:
            m_ComboPRIPatternType.EnableWindow( FALSE );
            m_ComboPRILevel.EnableWindow( FALSE );
            m_ComboPRIJitter.EnableWindow( FALSE );
            m_CEditPRI.EnableWindow( TRUE );
            m_CEditPRIPeriod.EnableWindow( FALSE );
            m_CEditPRIPulsePerLobe.EnableWindow( FALSE );

            GetDlgItem( ID_SIM_START )->EnableWindow( TRUE );
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER:
            m_ComboPRIPatternType.EnableWindow( FALSE );
            m_ComboPRILevel.EnableWindow( FALSE );
            m_ComboPRIJitter.EnableWindow( TRUE );
            m_CEditPRI.EnableWindow( TRUE );
            m_CEditPRIPeriod.EnableWindow( FALSE );
            m_CEditPRIPulsePerLobe.EnableWindow( FALSE );

            GetDlgItem( ID_SIM_START )->EnableWindow( TRUE );
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH:
            m_ComboPRIPatternType.EnableWindow( FALSE );
            m_ComboPRILevel.EnableWindow( TRUE );
            m_ComboPRIJitter.EnableWindow( FALSE );
            m_CEditPRI.EnableWindow( FALSE );
            m_CEditPRIPeriod.EnableWindow( FALSE );
            m_CEditPRIPulsePerLobe.EnableWindow( TRUE );

            GetDlgItem( ID_SIM_START )->EnableWindow( TRUE );
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER:
            m_ComboPRIPatternType.EnableWindow( FALSE );
            m_ComboPRILevel.EnableWindow( TRUE );
            m_ComboPRIJitter.EnableWindow( FALSE );
            m_CEditPRI.EnableWindow( FALSE );
            m_CEditPRIPeriod.EnableWindow( FALSE );
            m_CEditPRIPulsePerLobe.EnableWindow( FALSE );

            GetDlgItem( ID_SIM_START )->EnableWindow( TRUE );
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN:
            m_ComboPRIPatternType.EnableWindow( TRUE );
            m_ComboPRILevel.EnableWindow( FALSE );
            m_ComboPRIJitter.EnableWindow( TRUE );
            m_CEditPRI.EnableWindow( TRUE );
            m_CEditPRIPeriod.EnableWindow( TRUE );

            if( m_ComboPRIPatternType.GetCurSel() != 0 ) {
                m_CEditPRIPulsePerLobe.EnableWindow( TRUE );
            }
            else {
                m_CEditPRIPulsePerLobe.EnableWindow( FALSE );
            }

            GetDlgItem( ID_SIM_START )->EnableWindow( TRUE );
            break;

        default:
            break;

    }
}


/**
 * @brief     OnSelchangeComboPRIPatternType
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-17 14:41:55
 * @warning
 */
void CMSIGADlg::OnSelchangeComboPRIPatternType()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    ENUM_AET_FREQ_PRI_PATTERN_TYPE enPRIPatternType = ( ENUM_AET_FREQ_PRI_PATTERN_TYPE ) ( m_ComboPRIPatternType.GetCurSel() + 1 );

    switch( enPRIPatternType ) {
        case ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SLIDE_INC:
        case ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SLIDE_DEC:
        case ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SAW_TRI:
            m_CEditPRIPulsePerLobe.EnableWindow( TRUE );
            break;

        default:
            m_CEditPRIPulsePerLobe.EnableWindow( FALSE );
            break;
    }
}


/**
 * @brief     OnSelchangeComboScanType
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-10 11:49:25
 * @warning
 */
void CMSIGADlg::OnSelchangeComboScanType()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    ENUM_AET_SCAN_TYPE enScanType = ( ENUM_AET_SCAN_TYPE ) ( m_ComboScanType.GetCurSel() + 1 );

    switch( enScanType ) {
        case ENUM_AET_SCAN_TYPE::E_AET_SCAN_UNKNOWN :
            m_CEditScanPeriod.EnableWindow( FALSE );
            m_CEditAmplitude.EnableWindow( FALSE );
            m_CEditPulsePerLobe.EnableWindow( FALSE );
            GetDlgItem( IDC_STATIC_SCANPERIOD )->SetWindowTextA( "주기[ms]" );
            break;

        case ENUM_AET_SCAN_TYPE::E_AET_SCAN_CIRCULAR:
            m_CEditScanPeriod.EnableWindow( TRUE );
            m_CEditAmplitude.EnableWindow( TRUE );
            m_CEditPulsePerLobe.EnableWindow( TRUE );
            GetDlgItem( IDC_STATIC_SCANPERIOD )->SetWindowTextA( "주기[초]" );
            break;

        case ENUM_AET_SCAN_TYPE::E_AET_SCAN_UNI_DIRECTIONAL:
            m_CEditScanPeriod.EnableWindow( TRUE );
            m_CEditAmplitude.EnableWindow( TRUE );
            m_CEditPulsePerLobe.EnableWindow( TRUE );
            GetDlgItem( IDC_STATIC_SCANPERIOD )->SetWindowTextA( "주기[초]" );
            break;

        case ENUM_AET_SCAN_TYPE::E_AET_SCAN_BI_DIRECTIONAL:
            m_CEditScanPeriod.EnableWindow( TRUE );
            m_CEditAmplitude.EnableWindow( TRUE );
            m_CEditPulsePerLobe.EnableWindow( TRUE );
            GetDlgItem( IDC_STATIC_SCANPERIOD )->SetWindowTextA( "주기[초]" );
            break;

        case ENUM_AET_SCAN_TYPE::E_AET_SCAN_CONICAL:
            m_CEditScanPeriod.EnableWindow( TRUE );
            m_CEditAmplitude.EnableWindow( TRUE );
            m_CEditPulsePerLobe.EnableWindow( FALSE );
            GetDlgItem( IDC_STATIC_SCANPERIOD )->SetWindowTextA( "주기[Hz]" );
            break;

        case ENUM_AET_SCAN_TYPE::E_AET_SCAN_STEADY:
            m_CEditScanPeriod.EnableWindow( FALSE );
            m_CEditAmplitude.EnableWindow( FALSE );
            m_CEditPulsePerLobe.EnableWindow( FALSE );
            GetDlgItem( IDC_STATIC_SCANPERIOD )->SetWindowTextA( "주기[초]" );
            break;

        default:
            break;
    }
}



/**
 * @brief     LoadINI
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-08 11:52:03
 * @warning
 */
void CMSIGADlg::LoadINI( char *pszIniFileName )
{
    char szBuffer[100];

    g_stRadarPDW.iNoRadar = ( int ) GetPrivateProfileInt( "TEST", "NO", ( int ) -1, pszIniFileName );

    ///////////////////////////////////////////////////////////////////////////////////
    // 신호 형태
    g_stRadarPDW.iSignalType = (int) GetPrivateProfileInt( "SIGNAL", "TYPE", ( int ) ENUM_SIGNAL_TYPE::ST_NORMAL_PULSE, pszIniFileName );

    ///////////////////////////////////////////////////////////////////////////////////
    // 방위
    g_stRadarPDW.enDOA = ( ENUM_AET_AOA ) GetPrivateProfileInt( "DOA", "TYPE", ( int ) ENUM_AET_AOA::E_AET_DOA_FIXED, pszIniFileName );
    GetPrivateProfileString( "DOA", "VALUE", "0.0", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.fDOA = (float) atof( szBuffer );
    GetPrivateProfileString( "DOA", "RANGE", "2.0", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.fDOARange = ( float ) atof( szBuffer );

    ///////////////////////////////////////////////////////////////////////////////////
    // 주파수
    g_stRadarPDW.enFreqType = ( ENUM_AET_FRQ_TYPE ) GetPrivateProfileInt( "FREQ", "TYPE", ( int ) ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED, pszIniFileName );
    g_stRadarPDW.enFreqPatternType = ( ENUM_AET_FREQ_PRI_PATTERN_TYPE ) GetPrivateProfileInt( "FREQ", "PATTERNTYPE", ( int ) ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SINE, pszIniFileName );
    g_stRadarPDW.iCoFreqHoopingPositions = (int) GetPrivateProfileInt( "FREQ", "LEVEL", 2, pszIniFileName );
    GetPrivateProfileString( "FREQ", "VALUE", "9000.0", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.fFreq = ( float ) atof( szBuffer );
    GetPrivateProfileString( "FREQ", "PERIOD", "30.0", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.fFreqPeriod = ( float ) atof( szBuffer );
    g_stRadarPDW.iFreqBW = (int) GetPrivateProfileInt( "FREQ", "BW", 100, pszIniFileName );
    g_stRadarPDW.iFreqPulsePerLobe = ( int ) GetPrivateProfileInt( "FREQ", "PULSEPERLOBE", 40, pszIniFileName );

    ///////////////////////////////////////////////////////////////////////////////////
    // PRI
    g_stRadarPDW.enPRIType = ( ENUM_AET_PRI_TYPE ) GetPrivateProfileInt( "PRI", "TYPE", (int) ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED, pszIniFileName );
    g_stRadarPDW.enPRIPatternType = ( ENUM_AET_FREQ_PRI_PATTERN_TYPE ) GetPrivateProfileInt( "PRI", "PATTERNTYPE", ( int ) ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SINE, pszIniFileName );
    g_stRadarPDW.iCoPRIDwellStaggerPositions = (int) GetPrivateProfileInt( "PRI", "LEVEL", 2, pszIniFileName );
    g_stRadarPDW.iJitterRatio = (int) GetPrivateProfileInt( "PRI", "JITTER", 2, pszIniFileName );
    GetPrivateProfileString( "PRI", "VALUE", "1000.0", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.fPRI = ( float ) atof( szBuffer );
    GetPrivateProfileString( "PRI", "PERIOD", "10.0", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.fPRIPeriod = ( float ) atof( szBuffer );
    g_stRadarPDW.iPRIPulsePerLobe = ( int ) GetPrivateProfileInt( "PRI", "PULSEPERLOBE", 40, pszIniFileName );

    ///////////////////////////////////////////////////////////////////////////////////
    // 펄스폭
    GetPrivateProfileString( "PW", "VALUE", "1.0", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.fPW = ( float ) atof( szBuffer );

    ///////////////////////////////////////////////////////////////////////////////////
    // 스캔
    g_stRadarPDW.enScanType = ( ENUM_AET_SCAN_TYPE ) GetPrivateProfileInt( "SCAN", "TYPE", ( int ) ENUM_AET_SCAN_TYPE::E_AET_SCAN_STEADY, pszIniFileName );
    GetPrivateProfileString( "SCAN", "VALUE", "1.0", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.fScanPeriod = ( float ) atof( szBuffer );
    GetPrivateProfileString( "SCAN", "SIGNAL_INTENSITY", "-40", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.iSignalIntensity = atoi( szBuffer );
    GetPrivateProfileString( "SCAN", "AMPLITUDE", "10", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.iAmplitude = atoi( szBuffer );
    GetPrivateProfileString( "SCAN", "PULSEPERLOBE", "30", szBuffer, 100, m_szIniFileName );
    g_stRadarPDW.iCoPulsePerLobe = atoi( szBuffer );


    ///////////////////////////////////////////////////////////////////////////////////
    // 기타
    GetPrivateProfileString( "ETC", "MISSING_PERCENT", "10", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.iMissingPercent = atoi( szBuffer );
    GetPrivateProfileString( "ETC", "DDR_OFFSET", "100", szBuffer, 100, pszIniFileName );
    g_stRadarPDW.iDDROffset = atoi( szBuffer );

}

/**
 * @brief     SaveINI
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-08 11:56:05
 * @warning
 */
void CMSIGADlg::SaveINI( char *pszIniFileName, int iComboRadarTest )
{
    CString strData;

    strData.Format( "%d", g_stRadarPDW.iNoRadar );
    WritePrivateProfileString( "TEST", "NO", strData, "RadarNo.ini" );

    ///////////////////////////////////////////////////////////////////////////////////
    // 시험 신호 #
    strData.Format( "%d", g_stRadarPDW.iNoRadar );
    WritePrivateProfileString( "TEST", "NO", strData, pszIniFileName );

    ///////////////////////////////////////////////////////////////////////////////////
    // 신호 형태
    strData.Format( "%d", g_stRadarPDW.iSignalType );
    WritePrivateProfileString( "SIGNAL", "TYPE", strData, pszIniFileName );

    ///////////////////////////////////////////////////////////////////////////////////
    // 방위
    strData.Format( "%d", g_stRadarPDW.enDOA );
    WritePrivateProfileString( "DOA", "TYPE", strData, pszIniFileName );

    strData.Format( "%.1f", g_stRadarPDW.fDOA );
    WritePrivateProfileString( "DOA", "VALUE", strData, pszIniFileName );

    strData.Format( "%.1f", g_stRadarPDW.fDOARange );
    WritePrivateProfileString( "DOA", "RANGE", strData, pszIniFileName );

    ///////////////////////////////////////////////////////////////////////////////////
    // 주파수
    strData.Format( "%d", g_stRadarPDW.enFreqType );
    WritePrivateProfileString( "FREQ", "TYPE", strData, pszIniFileName );

    strData.Format( "%d", g_stRadarPDW.enFreqPatternType );
    WritePrivateProfileString( "FREQ", "PATTERNTYPE", strData, pszIniFileName );

    strData.Format( "%d", g_stRadarPDW.iCoFreqHoopingPositions );
    WritePrivateProfileString( "FREQ", "LEVEL", strData, pszIniFileName );

    strData.Format( "%.1f", g_stRadarPDW.fFreq );
    WritePrivateProfileString( "FREQ", "VALUE", strData, pszIniFileName );

    strData.Format( "%d", g_stRadarPDW.iFreqBW );
    WritePrivateProfileString( "FREQ", "BW", strData, pszIniFileName );

    strData.Format( "%f", g_stRadarPDW.fFreqPeriod );
    WritePrivateProfileString( "FREQ", "PERIOD", strData, pszIniFileName );

    strData.Format( "%d", g_stRadarPDW.iFreqPulsePerLobe );
    WritePrivateProfileString( "FREQ", "PULSEPERLOBE", strData, pszIniFileName );

    ///////////////////////////////////////////////////////////////////////////////////
    // PRI
    strData.Format( "%d", g_stRadarPDW.enPRIType );
    WritePrivateProfileString( "PRI", "TYPE", strData, pszIniFileName );

    strData.Format( "%d", g_stRadarPDW.enPRIPatternType );
    WritePrivateProfileString( "PRI", "PATTERNTYPE", strData, pszIniFileName );

    strData.Format( "%d", g_stRadarPDW.iCoPRIDwellStaggerPositions );
    WritePrivateProfileString( "PRI", "LEVEL", strData, pszIniFileName );

    strData.Format( "%d", g_stRadarPDW.iJitterRatio );
    WritePrivateProfileString( "PRI", "JITTER", strData, pszIniFileName );

    strData.Format( "%.1f", g_stRadarPDW.fPRI );
    WritePrivateProfileString( "PRI", "VALUE", strData, pszIniFileName );

    strData.Format( "%.1f", g_stRadarPDW.fPRIPeriod );
    WritePrivateProfileString( "PRI", "PERIOD", strData, pszIniFileName );

    strData.Format( "%d", g_stRadarPDW.iPRIPulsePerLobe );
    WritePrivateProfileString( "PRI", "PULSEPERLOBE", strData, pszIniFileName );

    ///////////////////////////////////////////////////////////////////////////////////
    // 펄스폭
    strData.Format( "%.1f", g_stRadarPDW.fPW );
    WritePrivateProfileString( "PW", "VALUE", strData, pszIniFileName );

    ///////////////////////////////////////////////////////////////////////////////////
    // 스캔
    strData.Format( "%d", g_stRadarPDW.enScanType );
    WritePrivateProfileString( "SCAN", "TYPE", strData, pszIniFileName );
    strData.Format( "%.1f", g_stRadarPDW.fScanPeriod );
    WritePrivateProfileString( "SCAN", "VALUE", strData, pszIniFileName );
    strData.Format( "%d", g_stRadarPDW.iSignalIntensity );
    WritePrivateProfileString( "SCAN", "SIGNAL_INTENSITY", strData, pszIniFileName );
    strData.Format( "%d", g_stRadarPDW.iAmplitude );
    WritePrivateProfileString( "SCAN", "AMPLITUDE", strData, pszIniFileName );
    strData.Format( "%d", g_stRadarPDW.iCoPulsePerLobe );
    WritePrivateProfileString( "SCAN", "PULSEPERLOBE", strData, pszIniFileName );


    ///////////////////////////////////////////////////////////////////////////////////
    // 기타
    strData.Format( "%d", g_stRadarPDW.iMissingPercent );
    WritePrivateProfileString( "ETC", "MISSING_PERCENT", strData, pszIniFileName );
    strData.Format( "%d", g_stRadarPDW.iDDROffset );
    WritePrivateProfileString( "ETC", "DDR_OFFSET", strData, pszIniFileName );

}

/**
 * @brief     OnConnect
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-12 18:10:46
 * @warning
 */
void CMSIGADlg::OnConnect( struct sockaddr_in *pAddr )
{


}

/**
 * @brief     OnDisConnect
 * @param     struct sockaddr_in * pAddr
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-12 18:12:48
 * @warning
 */
void CMSIGADlg::OnDisConnect( struct sockaddr_in *pAddr )
{


}

/**
 * @brief     OnSelchangeComboRadarTest
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-17 15:23:01
 * @warning
 */
void CMSIGADlg::OnSelchangeComboRadarTest()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    char szIniFileName[100];

    int iComboRadarTest = m_ComboRadarTest.GetCurSel();

    sprintf( szIniFileName, "./RadarPDW_%02d.ini", iComboRadarTest );
    LoadINI( szIniFileName );

    UpdateRadarPDW( iComboRadarTest );

    OnSelchangeComboFreqType();
    OnSelchangeComboPRIType();
    OnSelchangeComboScanType();

}

/**
 * @brief     OnBnClickedSave
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-17 15:28:16
 * @warning
 */
void CMSIGADlg::OnBnClickedSave()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    char szIniFileName[100];
    char buffer[100];
    int iComboRadarTest = m_ComboRadarTest.GetCurSel();

    sprintf( buffer, "레이더 시험 신호[#%02d] 발생 파일에 저장하시겠습니까 ? ", iComboRadarTest );

    if( IDYES == AfxMessageBox( buffer, MB_YESNO ) ) {
        LoadRadarPDW();

        sprintf( szIniFileName, "./RadarPDW_%02d.ini", iComboRadarTest );
        SaveINI( szIniFileName, iComboRadarTest );
    }
}


/**
 * @brief     OnBnClickedOk
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-16 13:58:19
 * @warning
 */
void CMSIGADlg::OnBnClickedOk()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    //CDialogEx::OnOK();
}


/**
 * @brief     OnBnClickedStopSigGen
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-16 11:52:58
 * @warning
 */
void CMSIGADlg::OnBnClickedStopSigGen()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if( m_bStopSigGen == false ) {
        GetDlgItem( ID_STOPSIGGEN )->SetWindowTextA( "신호 발생 정지" );
        StopSigGen( m_bStopSigGen );
    }
    else {
        GetDlgItem( ID_STOPSIGGEN )->SetWindowTextA( "신호 발생 시작" );
        StopSigGen( m_bStopSigGen );
    }

    m_bStopSigGen = ! m_bStopSigGen;

}

/**
 * @brief     PreTranslateMessage
 * @param     MSG * pMsg
 * @return    BOOL
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-16 16:10:08
 * @warning
 */
BOOL CMSIGADlg::PreTranslateMessage( MSG *pMsg )
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    BOOL bRet=FALSE;

    if( pMsg->message == WM_KEYDOWN ) {
        if( pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE ) {
            bRet = TRUE;
        }

    }

    if( bRet == FALSE ) {
        bRet = CDialogEx::PreTranslateMessage( pMsg );
    }

    return bRet;
}
