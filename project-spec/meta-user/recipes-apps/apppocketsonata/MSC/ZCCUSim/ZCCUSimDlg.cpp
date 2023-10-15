
// ZCCUSimDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ZCCUSim.h"
#include "ZCCUSimDlg.h"
#include "afxdialogex.h"

#define _MAIN_
#define _MAIN_GLOBALS_

#include <algorithm>

ENUM_UnitType g_enUnitType;


#include "../../files/Anal/SigAnal/_Struct.h"
#include "../../files/Include/globals.h"

#include "../../files/Utils/ccommonutils.h"

#include "../../files/Anal/MIDAS/RawFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_LOB_LIST            (100)


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
int g_iKeyId = 1;

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
public:


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


// CZCCUSimDlg 대화 상자





CZCCUSimDlg::CZCCUSimDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZCCUSIM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZCCUSimDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange( pDX );
    DDX_Control( pDX, IDC_STATIC_CONNECT_1, m_CStaticConnectMessage[0] );
    DDX_Control( pDX, IDC_STATIC_CONNECT_2, m_CStaticConnectMessage[1] );
    DDX_Control( pDX, IDC_STATIC_CONNECT_3, m_CStaticConnectMessage[2] );
    DDX_Control( pDX, IDC_STATIC_CONNECT_4, m_CStaticConnectMessage[3] );
    DDX_Control( pDX, IDC_STATIC_CONNECT_5, m_CStaticConnectMessage[4] );
    DDX_Control( pDX, IDC_STATIC_LED, m_CStaticLED );
    DDX_Control( pDX, IDC_BUTTON_REQ_START, m_CButtonReqStart );
    DDX_Control( pDX, IDC_LIST_AET, m_CListCtrlAET );
    DDX_Control( pDX, IDC_LIST_ABT, m_CListCtrlABT );
    DDX_Control( pDX, IDC_EDIT_ERRORMESSAGE, m_CStaticError );
    DDX_Control( pDX, IDC_LIST_LOB, m_CListCtrlLOB );
}

BEGIN_MESSAGE_MAP(CZCCUSimDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED( IDC_BUTTON_REQ_START, &CZCCUSimDlg::OnBnClickedButtonReqStart )
	ON_BN_CLICKED( IDC_BUTTON_REQ_RESTART, &CZCCUSimDlg::OnBnClickedButtonReqRestart )
	ON_BN_CLICKED( IDC_BUTTON_REQ_OPVAR, &CZCCUSimDlg::OnBnClickedButtonReqOpvar )
	ON_BN_CLICKED( IDC_BUTTON_REQ_DISCONNECT, &CZCCUSimDlg::OnBnClickedButtonReqDisconnect )
	ON_BN_CLICKED( IDC_BUTTON_REQ_DOWNLOAD, &CZCCUSimDlg::OnBnClickedButtonReqDownload )
    ON_BN_CLICKED( IDC_BUTTON_REQ_OPVAR_SETTING, &CZCCUSimDlg::OnBnClickedButtonReqOpvarSetting )
    ON_BN_CLICKED( IDC_BUTTON_REQ_DELETE, &CZCCUSimDlg::OnBnClickedButtonReqDelete )
    ON_BN_CLICKED( IDC_BUTTON_REQ_SCAN, &CZCCUSimDlg::OnBnClickedButtonReqScan )
    ON_NOTIFY( NM_CLICK, IDC_LIST_AET, &CZCCUSimDlg::OnNMClickListAet )
    ON_NOTIFY( NM_CLICK, IDC_LIST_ABT, &CZCCUSimDlg::OnNMClickListAbt )
    ON_COMMAND( IDCLOSE, &CZCCUSimDlg::OnIDClose )
END_MESSAGE_MAP()


// CZCCUSimDlg 메시지 처리기

BOOL CZCCUSimDlg::OnInitDialog()
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

	//ShowWindow(SW_MAXIMIZE);

	//ShowWindow(SW_MINIMIZE);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    //_CrtSetBreakAlloc(783); // 116 번째 메모리 생성시 프레이크 걸리도록 추가

	m_bmpLampBigOn.LoadBitmap( IDB_BIGON );
	m_bmpLampBigOff.LoadBitmap( IDB_BIGOFF );
	m_bmpLampConnect[0].LoadBitmap( IDB_BIGOFF );
	m_bmpLampConnect[1].LoadBitmap( IDB_1_CONNECT );
	m_bmpLampConnect[2].LoadBitmap( IDB_2_CONNECT );
	m_bmpLampConnect[3].LoadBitmap( IDB_3_CONNECT );
	m_bmpLampConnect[4].LoadBitmap( IDB_4_CONNECT );
	m_bmpLampConnect[5].LoadBitmap( IDB_BIGON );

	Init();
	// InitView();

    m_vClientSock.clear();


    m_pTheMULSRV = new CMultiServer( g_iKeyId++, ( char * ) "MULSRV", CCU_PORT, this );
    m_pTheMULSRV->Run();

    // 쓰레드 실행합니다.
	//m_pThread = AfxBeginThread( CMultiServer::WinRun, m_pTheMultiServer );
	//m_pTheMultiServer->Run();

	//Run();


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

/**
 * @brief     Init
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 10:59:17
 * @warning
 */
void CZCCUSimDlg::Init()
{
    int i;

    for( i = MAX_CLIENTS - 1; i >= 0; --i ) {
        m_QBoard.push( i );
    }

	m_enMode = enREADY_MODE;

    m_vecAETID.reserve( 10000 );
    m_vecABTID.reserve( 10000 );
    m_vecLOBID.reserve( 10000 );

    memset( & m_stCountOfButton, 0, sizeof( STR_BUTTON_COUNT ) );

    InitView();
    InitViewVariable();

    DisplayButtonCount();

	//m_pTheMultiServer = new CMultiServer( g_iKeyId++, ( char* ) "CCUTCP", CCU_PORT );

}

#define _TEXT_WIDTH							(8)
#define	_COLUMNS_OF_LIST_					(13)

/**
 * @brief     InitView
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 15:49:43
 * @warning
 */
void CZCCUSimDlg::InitView()
{
    int i;

    char szAETList[_COLUMNS_OF_LIST_][40] = { "방사체#", "누적LOB", "최근접촉시간    ", "방위[도]          ", "주파수[MHz]           ", "PRI[us]            ", "펄스폭[us]      ", "신호세기[dBm]  ", "레이더명    ", "카테고리", "ELNOT   ", "기타" };
    char szABTList[_COLUMNS_OF_LIST_][40] = { "방사체/빔#", "신/형", "최근접촉시간    ", "방위[도]          ", "주/형[ms]     ", "주파수[MHz]            ", "P/형[ms]      ", "PRI[us]               ", "펄스폭[us]    ", "스/형[ms/Hz]  ", "신호세기[dBm] ", "레이더/모드/위협" };
    char szLOBList[_COLUMNS_OF_LIST_][40] = { "방사체/빔#", "LOB #","신/형", "최근접촉시간    ", "방위[도]          ", "주/형[ms]    ", "주파수[MHz]            ", "P/형[ms]      ", "PRI[us]              ", "펄스폭[us]  ", "신호세기[dBm]", "기타     ", "호핑/스태거" };

	UpdateStaticMessage( NULL, true );

	AllButtonEnable( FALSE );

    m_font.CreatePointFont( 80, "굴림체" );

    // 방사체
    m_CListCtrlAET.SetFont( & m_font );
    for( i = 0; i < _COLUMNS_OF_LIST_; ++i ) {
        m_CListCtrlAET.InsertColumn( i, szAETList[i], LVCFMT_LEFT, _TEXT_WIDTH * (int) strlen( szAETList[i] ) );
    }

    // 빔
    m_CListCtrlABT.SetFont( & m_font );
    for( i = 0; i < _COLUMNS_OF_LIST_; ++i ) {
        m_CListCtrlABT.InsertColumn( i, szABTList[i], LVCFMT_LEFT, _TEXT_WIDTH * (int) strlen( szABTList[i] ) );
    }

    // LOB
    m_CListCtrlLOB.SetFont( & m_font );
    for( i = 0; i < _COLUMNS_OF_LIST_; ++i ) {
        m_CListCtrlLOB.InsertColumn( i, szLOBList[i], LVCFMT_LEFT, _TEXT_WIDTH * ( int ) strlen( szLOBList[i] ) );
    }

}

/**
 * @brief     OnSysCommand
 * @param     UINT nID
 * @param     LPARAM lParam
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 14:10:46
 * @warning
 */
void CZCCUSimDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CZCCUSimDlg::OnPaint()
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
HCURSOR CZCCUSimDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



/**
 * @brief     창이 닫힐때 호출합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 10:59:06
 * @warning
 */
void CZCCUSimDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
    delete m_pTheMULSRV;


	Free();


}

/**
 * @brief     메모리 해지를 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 10:59:04
 * @warning
 */
void CZCCUSimDlg::Free()
{
	//delete m_pTheMultiServer;
}

/**
 * @brief     ConnectMessage
 * @param     CLIENT_SOCKET * pClientSocket
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 15:40:06
 * @warning
 */
void CZCCUSimDlg::ConnectMessage( STR_CLIENT_SOCKET* pClientSocket )
{
    AddClientSocket( pClientSocket );

	UpdateStaticMessage( pClientSocket, true );
	UpdateLEDSwitch();

	AllButtonEnable( TRUE );

    UpdateLEDSwitch();
}

/**
 * @brief     DisConnectMessage
 * @param     CLIENT_SOCKET * pClientSocket
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 16:28:51
 * @warning
 */
void CZCCUSimDlg::DisConnectMessage( STR_CLIENT_SOCKET* pClientSocket )
{
	m_enMode = enREADY_MODE;

    RemoveClientSocket( pClientSocket );

	//m_vClientSock.clear();
    UpdateStaticMessage( pClientSocket, false );
    UpdateLEDSwitch( );

	UpdateReqStartButton();

	//
    if( m_vClientSock.size() == 0 ) {
	    AllButtonEnable( FALSE );
    }

}

/**
 * @brief     AllButtonEnable
 * @param     BOOL bEnable
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 15:13:12
 * @warning
 */
void CZCCUSimDlg::AllButtonEnable( BOOL bEnable )
{
	GetDlgItem( IDC_BUTTON_REQ_START )->EnableWindow( bEnable );
	GetDlgItem( IDC_BUTTON_REQ_RESTART )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_REQ_DOWNLOAD )->EnableWindow( bEnable );
	GetDlgItem( IDC_BUTTON_REQ_DOWNLOAD )->EnableWindow( bEnable );
	GetDlgItem( IDC_BUTTON_REQ_OPVAR_SETTING )->EnableWindow( bEnable );
	GetDlgItem( IDC_BUTTON_REQ_OPVAR )->EnableWindow( bEnable );
    GetDlgItem( IDC_BUTTON_REQ_SCAN )->EnableWindow( bEnable );
    GetDlgItem( IDC_BUTTON_REQ_DELETE )->EnableWindow( bEnable );

	// GetDlgItem( IDC_BUTTON_REQ_DISCONNECT )->EnableWindow( bEnable );

}

/**
 * @brief     ProcessLANMessage
 * @param     STR_LAN_DATA * pLanMessage
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 14:22:45
 * @warning
 */
void CZCCUSimDlg::ProcessLANMessage( STR_LAN_DATA *pLanMessage )
{
//	char buffer[100];

// 	switch( pLanMessage->stLanHeader.usOpCode ) {
// 		case enRES_OP_START:
// 			ResultOPStart( & pLanMessage->stLanData );
// 			break;
//
// 		case enRES_OP_SHUTDOWN:
// 			ResultOPShutdown( &pLanMessage->stLanData );
// 			break;
//
// 		case enRES_OP_RESTART :
// 			ResultOPRestart( &pLanMessage->stLanData );
// 			break;
//
// 		case enNUP_THREAT_DATA:
// 			ResultThreatData( &pLanMessage->stLanData );
// 			break;
//
//         case enDEL_THREAT_DATA :
//             DeleteThreatData( &pLanMessage->stLanData );
//             break;
//
//         case enDEL_BEAM_DATA:
//             DeleteBeamData( &pLanMessage->stLanData );
//             break;
//
//         case enRES_RELOAD_LIBRARY:
//             ResultReloadLibrary( &pLanMessage->stLanData );
//             break;
//
//         case enRES_SETSYS :
//             ResultSetSys( &pLanMessage->stLanData );
//             break;
//
//         case enRES_SYS:
//             ResultSys( &pLanMessage->stLanData, pLanMessage->stLanHeader.uiLength );
//             break;
//
//
//         case enRES_SYSERROR:
// 			// strcpy( pLanMessage->stLanData.szString, "위협 라이브러리를 복사하지 못했습니다 !" );
// 			//pLanMessage->stLanData.szString[pLanMessage->stLanHeader.uiLength] = 0;
// 			UTF8ToANSI( buffer, pLanMessage->stLanData.szString );
// 			strcpy( pLanMessage->stLanData.szString, buffer );
//
//             ResultSysError( &pLanMessage->stLanData );
//             break;
//
// 		default :
// 			TRACE( "\n[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), pLanMessage->stLanHeader.usOpCode );
// 			break;
// 	}

}

/**
 * @brief     ReceiveThreatData
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-13 14:31:05
 * @warning
 */
void CZCCUSimDlg::ResultOfThreatData( UNI_LAN_DATA *pLanData )
{
    int iFind;
    char buffer[100];

    // LOB 데이터 변환
	CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.uiPDWID, sizeof( UINT )*6 );
    CCommonUtils::AllSwapData16( & pLanData->stAET.stLOBData.tiContactTimems, sizeof( short ) );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.fDOAMean, sizeof( UINT ) * 6 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.fFreqPatternPeriod, sizeof( UINT ) * 6 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.fFreqSeq, sizeof( UINT ) * MAX_FREQ_PRI_STEP );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.fPRIPatternPeriod, sizeof( UINT ) * 7 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.fPRISeq, sizeof( UINT ) * MAX_FREQ_PRI_STEP );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.fPWMean, sizeof( UINT ) * 10 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.fMeanScanPeriod, sizeof( UINT ) * 1 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.fMOPMaxFreq, sizeof( UINT ) * 4 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.uiNumOfCollectedPDW, sizeof( UINT ) * 2 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.uiRadarModeIndex, sizeof( UINT ) * 3 );

    // 빔 데이터 변환
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.uiABTID, sizeof( UINT ) * 2 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.uiCoLOB, sizeof( UINT ) * 5 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.fDOAMean, sizeof( UINT ) * 4 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.fFreqPatternPeriodMean, sizeof( UINT ) * 7 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.fFreqSeq, sizeof( UINT ) * MAX_FREQ_PRI_STEP );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.fPRIPatternPeriodMean, sizeof( UINT ) * 8 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.fPRISeq, sizeof( UINT ) * MAX_FREQ_PRI_STEP );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.fPWMean, sizeof( UINT ) * 8 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.fMeanScanPeriod, sizeof( UINT ) * 3 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.fMaxIntraMod, sizeof( UINT ) * 2 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.fLatitude, sizeof( UINT ) * 8 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stABTData.uiTotaOfPDW, sizeof( UINT ) * 4 );

    // 방사체 데이터 변환
    CCommonUtils::AllSwapData32( & pLanData->stAET.stAETData.uiAETID, sizeof( UINT ) * 3 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stAETData.uiPinNum, sizeof( UINT ) * 1 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stAETData.uiRadarModePriority, sizeof( UINT ) * 5 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stAETData.fDOAMean, sizeof( UINT ) * 4 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stAETData.fFreqMean, sizeof( UINT ) * 19 );
    CCommonUtils::AllSwapData32( & pLanData->stAET.stAETData.fLatitude, sizeof( UINT ) * 8 );

    iFind = ManageAETID( pLanData->stAET.stAETData.uiAETID );
    if( iFind >= 0 ) {
        unsigned int uiRows;

        uiRows = GetRows( pLanData->stAET.stAETData.uiAETID );
        UpdateAETList( uiRows, pLanData );

        uiRows = GetRows( pLanData->stAET.stABTData.uiAETID, pLanData->stAET.stABTData.uiABTID );
        UpdateABTList( uiRows, pLanData );

    }
    else {
        sprintf_s( buffer, sizeof( buffer ), "%04d", pLanData->stAET.stAETData.uiAETID );
        m_CListCtrlAET.InsertItem( m_uiCoAETListItems, buffer );

        UpdateAETList( m_uiCoAETListItems, pLanData );

        sprintf_s( buffer, sizeof( buffer ), "%04d/%04d", pLanData->stAET.stABTData.uiAETID, pLanData->stAET.stABTData.uiABTID );
        m_CListCtrlABT.InsertItem( m_uiCoAETListItems, buffer );

        UpdateABTList( m_uiCoAETListItems, pLanData );

        ++ m_uiCoAETListItems;
        ++ m_uiCoABTListItems;
    }

    InsertLOBList( pLanData );

    UpdateWindow();

	TRACE( "\n 위협 번호[%d/%d/%d]", pLanData->stAET.stLOBData.uiAETID, pLanData->stAET.stLOBData.uiABTID, pLanData->stAET.stLOBData.uiLOBID );
}

/**
 * @brief     GetRows
 * @param     unsigned int uiAETID
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-25 15:18:12
 * @warning
 */
unsigned int CZCCUSimDlg::GetRows( unsigned int uiAETID )
{
    unsigned int i;
    CString strString;

    for( i=0 ; i < m_uiCoAETListItems ; ++i ) {
        strString = m_CListCtrlAET.GetItemText( i, 0 );
        if( atoi( (LPTSTR)(LPCTSTR) strString ) == uiAETID ) {
            break;
        }
    }

    return i;

}

/**
 * @brief     GetRows
 * @param     unsigned int uiAETID
 * @param     unsigned int uiABTID
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-25 16:07:42
 * @warning
 */
unsigned int CZCCUSimDlg::GetRows( unsigned int i_uiAETID, unsigned int i_uiABTID )
{
    unsigned int i, uiAETID, uiABTID;
    CString strString;

    for( i=0 ; i < m_uiCoABTListItems ; ++i ) {
        strString = m_CListCtrlABT.GetItemText( i, 0 );
        sscanf( ( LPTSTR ) ( LPCTSTR ) strString, "%d/%d", & uiAETID, & uiABTID );

        if( ( i_uiAETID == uiAETID ) && ( i_uiABTID == uiABTID || i_uiABTID == 0 ) ) {
            break;
        }
    }

    return i;

}



/**
 * @brief     UpdateAETList
 * @param     unsigned int uiItems
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-25 14:55:53
 * @warning
 */
void CZCCUSimDlg::UpdateAETList( unsigned int uiItems, UNI_LAN_DATA *pLanData )
{
    int iCol=1;

    char buffer[100];

    SRxAETData *pAETData;

    char szCategory[6][20] = { "미식별", "항공", "해상", "잠수함", "육상" };

    pAETData = & pLanData->stAET.stAETData;

    sprintf_s( buffer, sizeof( buffer ), "%d", pAETData->uiCoLOB );
    m_CListCtrlAET.SetItemText( uiItems, iCol++, buffer );

    CCommonUtils::getStringDesignatedDate( buffer, sizeof( buffer ), pAETData->tiLastSeenTime );
    m_CListCtrlAET.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%06.2f[%06.2f~%06.2f]", pAETData->fDOAMean, pAETData->fDOAMin, pAETData->fDOAMax );
    m_CListCtrlAET.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f[%05.2f~%05.2f]", pAETData->fFreqMean, pAETData->fFreqMin, pAETData->fFreqMax );
    m_CListCtrlAET.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f[%05.2f~%05.2f]", pAETData->fPRIMean, pAETData->fPRIMin, pAETData->fPRIMax );
    m_CListCtrlAET.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f~%05.2f", pAETData->fPWMin, pAETData->fPWMax );
    m_CListCtrlAET.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f~%05.2f", pAETData->fPAMin, pAETData->fPAMax );
    m_CListCtrlAET.SetItemText( uiItems, iCol++, buffer );

    char szAnsi[100];
    UTF8ToANSI( szAnsi, pAETData->szRadarName );
    sprintf_s( buffer, sizeof( buffer ), "%s", szAnsi );
    m_CListCtrlAET.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%s[%d]", szCategory[pAETData->vCategory], pAETData->vCategory );
    m_CListCtrlAET.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%s", pAETData->szPrimaryELNOT );
    m_CListCtrlAET.SetItemText( uiItems, iCol++, buffer );

    Invalidate();

}

/**
 * @brief     InsertLOBList
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-29 14:52:40
 * @warning
 */
void CZCCUSimDlg::InsertLOBList( UNI_LAN_DATA *pLanData )
{
    int iCol = 1, i, iBuffer;

    char buffer[400];

    SRxLOBData *pLOBData;

    char szAetFreqType[( int ) ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE][10] = { "고정" , "호핑" , "변경" , "패턴", "모름" };
    char szAetPriType[( int ) ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE][10] = { "고정" , "지터", "드웰" , "스태거" , "지터", "모름" };
    char szAetPatternType[( int ) ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_MAX_FREQ_PRI_PATTERN_TYPE][10] = { "모름" , "사인형", "증가형" , "감소형" , "톱니파" };


    pLOBData = & pLanData->stAET.stLOBData;

    if( m_uiCoLOBListItems > MAX_LOB_LIST ) {
        m_uiCoLOBListItems = 0;
        m_CListCtrlLOB.DeleteAllItems();
    }

    sprintf_s( buffer, sizeof( buffer ), "%04d/%04d", pLOBData->uiAETID, pLOBData->uiABTID );
    m_CListCtrlLOB.InsertItem( m_uiCoLOBListItems, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%04d", pLOBData->uiLOBID );
    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%s", g_szAetSignalType[pLOBData->vSignalType] );
    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    CCommonUtils::getStringDesignatedDate( buffer, sizeof( buffer ), pLOBData->tiContactTime );
    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%06.2f[%06.2f~%06.2f]", pLOBData->fDOAMean, pLOBData->fDOAMin, pLOBData->fDOAMax );
    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    switch( pLOBData->vFreqType ) {
        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING:
            sprintf_s( buffer, sizeof( buffer ), "%s[%0d단]", szAetFreqType[( int ) pLOBData->vFreqType], pLOBData->vFreqPositionCount );
            break;
        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN:
            sprintf_s( buffer, sizeof( buffer ), "%s/%s/%.1f", szAetFreqType[( int ) pLOBData->vFreqType], szAetPatternType[( int ) pLOBData->vFreqPatternType], FDIV( pLOBData->fFreqPatternPeriod, 1000. ) );
            break;
        default:
            sprintf_s( buffer, sizeof( buffer ), "%s", szAetFreqType[( int ) pLOBData->vFreqType] );
            break;
    }
    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f[%05.2f~%05.2f]", pLOBData->fFreqMean, pLOBData->fFreqMin, pLOBData->fFreqMax );
    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    switch( pLOBData->vPRIType ) {
        case ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN:
            sprintf_s( buffer, sizeof( buffer ), "%s/%s[%.1f,%.1f%%]", szAetPriType[( int ) pLOBData->vPRIType], szAetPatternType[( int ) pLOBData->vPRIPatternType], pLOBData->fPRIPatternPeriod, pLOBData->fPRIJitterRatio );
            break;
        case ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER:
        case ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH:
            sprintf_s( buffer, sizeof( buffer ), "%s[%0d단,%.1f%%]", szAetPriType[( int ) pLOBData->vPRIType], pLOBData->vPRIPositionCount, pLOBData->fPRIJitterRatio );
            break;
        case ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER:
            sprintf_s( buffer, sizeof( buffer ), "%s [%.1f%%]", szAetPriType[( int ) pLOBData->vPRIType], pLOBData->fPRIJitterRatio );
            break;
        default:
            sprintf_s( buffer, sizeof( buffer ), "%s", szAetPriType[( int ) pLOBData->vPRIType] );
            break;
    }
    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f[%05.2f~%05.2f]", pLOBData->fPRIMean, pLOBData->fPRIMin, pLOBData->fPRIMax );
    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f~%05.2f", pLOBData->fPWMin, pLOBData->fPWMax );
    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f~%05.2f", pLOBData->fPAMin, pLOBData->fPAMax );
    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%3d/%3d", pLOBData->uiNumOfAnalyzedPDW, pLOBData->uiNumOfCollectedPDW );
    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    iBuffer = 0;
    buffer[0] = NULL;
    if( pLOBData->vFreqPositionCount >= 2 ) {
        iBuffer += sprintf_s( & buffer[iBuffer], sizeof(buffer)-iBuffer, "[" );

        for( i = 0; i < pLOBData->vFreqPositionCount-1 ; ++i ) {
            iBuffer += sprintf_s( & buffer[iBuffer], sizeof( buffer ) - iBuffer, "%.1f,", pLOBData->fFreqSeq[i] );
        }
        iBuffer += sprintf_s( & buffer[iBuffer], sizeof( buffer ) - iBuffer, "%.1f]", pLOBData->fFreqSeq[i] );
    }
    if( pLOBData->vPRIPositionCount >= 2 ) {
        iBuffer += sprintf_s( & buffer[iBuffer], sizeof( buffer ) - iBuffer, "[" );

        for( i = 0; i < pLOBData->vPRIPositionCount-1 ; ++i ) {
            iBuffer += sprintf_s( & buffer[iBuffer], sizeof( buffer ) - iBuffer, "%.1f,", pLOBData->fPRISeq[i] );
        }
        iBuffer += sprintf_s( & buffer[iBuffer], sizeof( buffer ) - iBuffer, "%.1f]", pLOBData->fPRISeq[i] );
    }

    m_CListCtrlLOB.SetItemText( m_uiCoLOBListItems, iCol++, buffer );

    ++ m_uiCoLOBListItems;

    Invalidate();

}

/**
 * @brief     UpdateABTList
 * @param     unsigned int uiItems
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-25 15:43:08
 * @warning
 */
void CZCCUSimDlg::UpdateABTList( unsigned int uiItems, UNI_LAN_DATA *pLanData )
{
    int iCol=1;

    char buffer[100];

    char szAetFreqType[( int ) ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE][10] = { "고정" , "호핑" , "변경" , "패턴", "모름" };
    char szAetPriType[( int ) ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE][10] = { "고정" , "지터", "드웰" , "스태거" , "지터", "모름" };
    char szAetPatternType[( int ) ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_MAX_FREQ_PRI_PATTERN_TYPE][10] = { "모름" , "사인형", "증가형" , "감소형" , "톱니파" };

    sprintf_s( buffer, sizeof( buffer ), "%s", g_szAetSignalType[pLanData->stAET.stABTData.vSignalType] );
    m_CListCtrlABT.SetItemText( uiItems, iCol++, buffer );

    CCommonUtils::getStringDesignatedDate( buffer, sizeof( buffer ), pLanData->stAET.stABTData.tiLastSeenTime );
    m_CListCtrlABT.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%06.2f[%06.2f~%06.2f]", pLanData->stAET.stABTData.fDOAMean, pLanData->stAET.stABTData.fDOAMin, pLanData->stAET.stABTData.fDOAMax );
    m_CListCtrlABT.SetItemText( uiItems, iCol++, buffer );

    switch( pLanData->stAET.stABTData.vFreqType ) {
        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING :
            sprintf_s( buffer, sizeof( buffer ), "%s/%02d", szAetFreqType[(int)pLanData->stAET.stABTData.vFreqType], pLanData->stAET.stABTData.vFreqPositionCount );
            break;
        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN:
            sprintf_s( buffer, sizeof( buffer ), "%s/%s/%.1f", szAetFreqType[( int ) pLanData->stAET.stABTData.vFreqType], szAetPatternType[( int ) pLanData->stAET.stABTData.vFreqPatternType], FDIV( pLanData->stAET.stABTData.fFreqPatternPeriodMean, 1000. ) );
            break;
        default:
            sprintf_s( buffer, sizeof( buffer ), "%s", szAetFreqType[( int ) pLanData->stAET.stABTData.vFreqType] );
            break;
    }
    m_CListCtrlABT.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f[%05.2f~%05.2f]", pLanData->stAET.stABTData.fFreqMean, pLanData->stAET.stABTData.fFreqMin, pLanData->stAET.stABTData.fFreqMax );
    m_CListCtrlABT.SetItemText( uiItems, iCol++, buffer );

    switch( pLanData->stAET.stABTData.vPRIType ) {
        case ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN:
            sprintf_s( buffer, sizeof( buffer ), "%s/%s[%.1f,%.1f%%]", szAetPriType[( int ) pLanData->stAET.stABTData.vPRIType], szAetPatternType[( int ) pLanData->stAET.stABTData.vPRIPatternType], FDIV( pLanData->stAET.stABTData.fPRIPatternPeriodMean, 1000. ), pLanData->stAET.stABTData.fPRIJitterRatio );
            break;
        case ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER:
        case ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH :
            sprintf_s( buffer, sizeof( buffer ), "%s[%d단,%.1f%%]", szAetPriType[( int ) pLanData->stAET.stABTData.vPRIType], pLanData->stAET.stABTData.vPRIPositionCount, pLanData->stAET.stABTData.fPRIJitterRatio );
            break;
        case ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER:
            sprintf_s( buffer, sizeof( buffer ), "%s [%.1f%%]", szAetPriType[( int ) pLanData->stAET.stABTData.vPRIType], pLanData->stAET.stABTData.fPRIJitterRatio );
            break;
        default :
            sprintf_s( buffer, sizeof( buffer ), "%s", szAetPriType[( int ) pLanData->stAET.stABTData.vPRIType] );
            break;
    }
    m_CListCtrlABT.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f[%05.2f~%05.2f]", pLanData->stAET.stABTData.fPRIMean, pLanData->stAET.stABTData.fPRIMin, pLanData->stAET.stABTData.fPRIMax );
    m_CListCtrlABT.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f~%05.2f", pLanData->stAET.stABTData.fPWMin, pLanData->stAET.stABTData.fPWMax );
    m_CListCtrlABT.SetItemText( uiItems, iCol++, buffer );

    if( pLanData->stAET.stABTData.fMeanScanPeriod != 0 ) {
        sprintf_s( buffer, sizeof( buffer ), "%s/%.2f[%.2fHz]", g_szAetScanType[( int ) pLanData->stAET.stABTData.vScanType], pLanData->stAET.stABTData.fMeanScanPeriod, FDIV( 1000., pLanData->stAET.stABTData.fMeanScanPeriod ) );
    }
    else {
        sprintf_s( buffer, sizeof( buffer ), "%s/%.2f[---Hz]", g_szAetScanType[( int ) pLanData->stAET.stABTData.vScanType], pLanData->stAET.stABTData.fMeanScanPeriod );
    }

    m_CListCtrlABT.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05.2f~%05.2f", pLanData->stAET.stABTData.fPAMin, pLanData->stAET.stABTData.fPAMax );
    m_CListCtrlABT.SetItemText( uiItems, iCol++, buffer );

    sprintf_s( buffer, sizeof( buffer ), "%05d/%05d/%05d", pLanData->stAET.stABTData.uiRadarIndex, pLanData->stAET.stABTData.uiRadarModeIndex, pLanData->stAET.stABTData.uiThreatIndex );
    m_CListCtrlABT.SetItemText( uiItems, iCol++, buffer );

    Invalidate();
}

/**
 * @brief     ManageAETID
 * @param     unsigned int uiAETID
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-25 14:55:51
 * @warning
 */
int CZCCUSimDlg::ManageAETID( unsigned int uiAETID )
{
    int iFind=-1;

    auto it = find( m_vecAETID.begin(), m_vecAETID.end(), uiAETID );
    if( it != m_vecAETID.end() ) {
        iFind = (int) ( it - m_vecAETID.begin() );
    }
    else {
        m_vecAETID.emplace_back( uiAETID );
    }

    return iFind;
}

/**
 * @brief     DeleteThreatData
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-25 11:23:24
 * @warning
 */
void CZCCUSimDlg::DeleteThreatData( UNI_LAN_DATA *pLanData )
{
    unsigned int uiRows;

    CCommonUtils::AllSwapData32( pLanData, sizeof( UINT ) );
    TRACE( "\n 방사체 삭제 [%d]", pLanData->stDelete.uiAET );

    uiRows = GetRows( pLanData->stDelete.uiAET );
    m_CListCtrlAET.DeleteItem( uiRows );

    -- m_uiCoAETListItems;

    uiRows = GetRows( pLanData->stDelete.uiAET, pLanData->stDelete.uiABT );
    m_CListCtrlABT.DeleteItem( uiRows );

    -- m_uiCoABTListItems;

}

/**
 * @brief     DeleteThreatData
 * @param     UINT uiAETID
 * @param     UINT uiABTID
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-28 15:26:02
 * @warning
 */
void CZCCUSimDlg::DeleteThreatData( UINT uiAET, UINT uiABT )
{
    unsigned int uiRows;

    TRACE( "\n 방사체[%d]/빔[%d] 삭제...", uiAET, uiABT );

    uiRows = GetRows( uiAET );
    m_CListCtrlAET.DeleteItem( uiRows );

    -- m_uiCoAETListItems;

    uiRows = GetRows( uiAET, uiABT );
    m_CListCtrlABT.DeleteItem( uiRows );

    -- m_uiCoABTListItems;

}

/**
 * @brief     DeleteBeamData
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-25 11:26:13
 * @warning
 */
void CZCCUSimDlg::DeleteBeamData( UNI_LAN_DATA *pLanData )
{
    CCommonUtils::AllSwapData32( & pLanData->stDelete, sizeof( SELDELETE ) );
    TRACE( "\n 방사체/빔 삭제 [%d]", pLanData->stDelete.uiAET, pLanData->stDelete.uiABT );

}

/**
 * @brief     ResultOPStart
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 14:29:53
 * @warning
 */
void CZCCUSimDlg::ResultOfOPStart( UNI_MSG_DATA *pLanData )
{
	CCommonUtils::AllSwapData32( pLanData, sizeof( UINT ) );
	if( pLanData->uiData == TRUE ) {
        char buffer[100];

        ++ m_stResultMessage.uiCoStart;
		m_enMode = enOP_Mode;

        AllButtonEnable( TRUE );

        sprintf( buffer, "시작 요청을 정상 수신[%d] 하였습니다 !", m_stResultMessage.uiCoStart );
        m_CStaticError.SetWindowTextA( buffer );


        if( m_stResultMessage.uiCoStart == m_vClientSock.size() ) {
            GetDlgItem( IDC_BUTTON_REQ_RESTART )->EnableWindow( TRUE );
        }


        InitViewVariable();

        UpdateReqStartButton();
	}
	else {
        m_CStaticError.SetWindowTextA( "시작 요청을 정상적으로 처리하지 못했습니다. 관리자에게 문의하세요 !" );
	}

    UpdateWindow();

}

/**
 * @brief     ResultOPShutdown
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 14:39:15
 * @warning
 */
void CZCCUSimDlg::ResultOfOPShutdown( UNI_MSG_DATA *pLanData )
{
	CCommonUtils::AllSwapData32( pLanData, sizeof( UINT ) );
    if( pLanData->uiData == TRUE ) {
        m_enMode = enREADY_MODE;

		GetDlgItem( IDC_BUTTON_REQ_START )->EnableWindow( TRUE );
        GetDlgItem( IDC_BUTTON_REQ_RESTART )->EnableWindow( FALSE );

        m_CStaticError.SetWindowTextA( "종료 요청을 정상 처리하였습니다 !" );

    }
    else {
        m_CStaticError.SetWindowTextA( "종료 요청을 처리하지 못했습니다. 관리자에게 문의하세요 !" );
    }

    UpdateReqStartButton();

    UpdateWindow();

}

/**
 * @brief     ResultOPRestart
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 14:43:57
 * @warning
 */
void CZCCUSimDlg::ResultOfOPRestart( UNI_MSG_DATA *pLanData )
{
	CCommonUtils::AllSwapData32( pLanData, sizeof( UINT ) );
    if( pLanData->uiData == TRUE ) {
        m_enMode = enOP_Mode;

        InitViewVariable();

        GetDlgItem( IDC_BUTTON_REQ_RESTART )->EnableWindow( TRUE );

        m_CStaticError.SetWindowTextA( "재시작 요청을 정상 처리하였습니다 !" );

    }
    else {
        m_CStaticError.SetWindowTextA( "재시작 요청을 정상적으로 처리하지 못했습니다. 관리자에게 문의하세요 !" );
    }

    // UpdateReqStartButton();

    UpdateWindow();

}


/**
 * @brief     ResultOPReloadLibrary
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-07 09:55:28
 * @warning
 */
void CZCCUSimDlg::ResultOfReloadLibrary( UNI_MSG_DATA *pLanData )
{
    ++ m_stResultMessage.uiCoDownload;
    CCommonUtils::AllSwapData32( pLanData, sizeof( UINT ) );
    if( pLanData->uiData == TRUE ) {
        char buffer[100];

        sprintf( buffer, "CED/EOB 라이브러리를 정상 수신[%d]하여 업데이트 했습니다 !", m_stResultMessage.uiCoDownload );
        m_CStaticError.SetWindowTextA( buffer );
    }
    else {

    }

    if( m_stResultMessage.uiCoDownload == m_vClientSock.size() ) {
        GetDlgItem( IDC_BUTTON_REQ_DOWNLOAD )->EnableWindow( TRUE );
    }

    UpdateWindow();

}

/**
 * @brief     ResultSys
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-09 10:17:29
 * @warning
 */
void CZCCUSimDlg::ResultOfSys( UNI_LAN_DATA *pLanData, unsigned int uiDataLength )
{
    int iRet;

    // INI 파일 읽기
    CRawFile theRawFile;

    char pstPathname[100];
    char buffer[200];

    if( uiDataLength != 0 ) {
        ++ m_stResultMessage.uiCoRequestOpVar;

        sprintf( pstPathname, "c:/sysconfig.ini" );

        if( theRawFile.RawOpenFile( pstPathname, O_CREAT | O_BINARY | O_RDWR ) ) {
            theRawFile.Write( pLanData, uiDataLength );
            theRawFile.CloseFile();

            iRet = TRUE;
            sprintf( buffer, "신호분석 운용 변수 설정을 정상 수신[%d]하여 [%s]에 [%d] 바이트를 정상 기록했습니다.", m_stResultMessage.uiCoRequestOpVar, pstPathname, uiDataLength );

        }
        else {
            sprintf( buffer, "신호분석 운용 변수 값을 지정된 경로[%s]에 문제가 있어서 저장하지 못했습니다 !", pstPathname );
        }

        m_CStaticError.SetWindowTextA( buffer );
    }
    else {
        m_CStaticError.SetWindowTextA( "신호분석 운용 변수 값을 수신하지 못하였습니다. 관리자에게 문의하세요 !" );
    }

    if( m_stResultMessage.uiCoRequestOpVar == m_vClientSock.size() ) {
        GetDlgItem( IDC_BUTTON_REQ_OPVAR )->EnableWindow( TRUE );
    }

    UpdateWindow();

}

/**
 * @brief     ResultSetSys
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-09 10:12:32
 * @warning
 */
void CZCCUSimDlg::ResultOfSetSys( UNI_MSG_DATA *pLanData )
{
    ++ m_stResultMessage.uiCoReqOpVarSetting;

    CCommonUtils::AllSwapData32( pLanData, sizeof( UINT ) );
    if( pLanData->uiData == TRUE ) {
        char buffer[200];

        sprintf( buffer, "신호분석 운용 변수 값을 정상 수신[%d] 하여 처리했습니다.", m_stResultMessage.uiCoReqOpVarSetting );
        m_CStaticError.SetWindowTextA( buffer );
    }
    else {
        m_CStaticError.SetWindowTextA( "신호분석 운용 변수 값을 수신하지 못하였거나 문제가 발생했습니다 !" );
    }

    if( m_stResultMessage.uiCoReqOpVarSetting == m_vClientSock.size() ) {
        GetDlgItem( IDC_BUTTON_REQ_OPVAR_SETTING )->EnableWindow( TRUE );
    }

    UpdateWindow();

}

/**
 * @brief     ResultUserScan
 * @param     UNI_MSG_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-27 19:43:55
 * @warning
 */
void CZCCUSimDlg::ResultOfUserScan( UNI_MSG_DATA *pLanData )
{
    CCommonUtils::AllSwapData32( pLanData, sizeof( UINT ) );
    switch( pLanData->enUserScanStat ) {
        case ENUM_AET_USER_SCAN_STAT::E_AET_USER_SCAN_PROCESSING :
            m_CStaticError.SetWindowTextA( "사용자 스캔 분석 요구할 방사체/빔 번호를 정상 처리했습니다." );
            break;

        case ENUM_AET_USER_SCAN_STAT::E_AET_USER_SCAN_ALREADYPROCESSING :
            m_CStaticError.SetWindowTextA( "사용자 스캔 분석 요구할 방사체/빔 번호가 이미 스캔 중에 있습니다 !" );
            break;

        case ENUM_AET_USER_SCAN_STAT::E_AET_USER_SCAN_CANT:
            m_CStaticError.SetWindowTextA( "사용자 스캔 분석 요구할 방사체/빔 번호가 이미 삭제되어 스캔을 시도 할 수 없습니다 !" );
            break;

        default:
            break;
    }

    GetDlgItem( IDC_BUTTON_REQ_SCAN )->EnableWindow( TRUE );

    UpdateWindow();

}

/**
 * @brief     ResultOfScanData
 * @param     UNI_MSG_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-28 14:13:02
 * @warning
 */
void CZCCUSimDlg::ResultOfScanData( UNI_MSG_DATA *pLanData )
{
    char buffer[200];

    CCommonUtils::AllSwapData32( & pLanData->stUserScanResult.uiAET, sizeof( UINT )*2 );
    CCommonUtils::AllSwapData32( & pLanData->stUserScanResult.fScanPeriod, sizeof( float ) );

    sprintf( buffer, "사용자 스캔 분석 요구한 방사체[%d]/빔[%d] 번호를 스캔 정보[%s, %.2f ms]를 분석 했습니다.", pLanData->stUserScanResult.uiAET, pLanData->stUserScanResult.uiAET, g_szAetScanType[(int)pLanData->stUserScanResult.enScanType], pLanData->stUserScanResult.fScanPeriod );
    m_CStaticError.SetWindowTextA( buffer );


    GetDlgItem( IDC_BUTTON_REQ_SCAN )->EnableWindow( TRUE );

    UpdateWindow();

}

/**
 * @brief     ResultOfDelete
 * @param     UNI_MSG_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-27 19:43:54
 * @warning
 */
void CZCCUSimDlg::ResultOfDelete( UNI_MSG_DATA *pLanData )
{
    CCommonUtils::AllSwapData32( pLanData, sizeof( UINT ) );
    if( pLanData->uiData == TRUE ) {
        TRACE( "\n 삭제 요구할 방사체/빔 번호를 정상 처리했습니다 !" );
    }
    else {
        TRACE( "\n 삭제 요구할 방사체/빔 번호가 잘못 됐습니다 !" );
    }

    //GetDlgItem( IDC_BUTTON_REQ_OPVAR_SETTING )->EnableWindow( TRUE );

    UpdateWindow();

}

/**
 * @brief     ResultOfDeleteThreatData
 * @param     UNI_MSG_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-28 15:17:00
 * @warning
 */
void CZCCUSimDlg::ResultOfDeleteThreatData( UNI_MSG_DATA *pLanData )
{
    CCommonUtils::AllSwapData32( pLanData, sizeof( UINT )*2 );

    DeleteThreatData( pLanData->stDelete.uiAET, pLanData->stDelete.uiABT );

    GetDlgItem( IDC_BUTTON_REQ_DELETE )->EnableWindow( TRUE );

    UpdateWindow();

}

/**
 * @brief     ResultOfDeleteThreatData
 * @param     UNI_MSG_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-12 14:40:13
 * @warning
 */
void CZCCUSimDlg::ResultOfUserDeleteThreatData( UNI_MSG_DATA *pLanData )
{
    char buffer[200];

    CCommonUtils::AllSwapData32( pLanData, sizeof( UINT )*2 );

    sprintf( buffer, "삭제 요구할 방사체/빔[%d/%d] 번호를 정상 처리했습니다 !", pLanData->stDelete.uiAET, pLanData->stDelete.uiABT );
    m_CStaticError.SetWindowTextA( buffer );

    DeleteThreatData( pLanData->stDelete.uiAET, pLanData->stDelete.uiABT );

    GetDlgItem( IDC_BUTTON_REQ_DELETE )->EnableWindow( TRUE );

    UpdateWindow();

}

/**
 * @brief     ResultOfDeleteBeamData
 * @param     UNI_MSG_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-28 17:16:08
 * @warning
 */
void CZCCUSimDlg::ResultOfDeleteBeamData( UNI_MSG_DATA *pLanData )
{
    char buffer[200];

    CCommonUtils::AllSwapData32( pLanData, sizeof( SELDELETE ) );

    sprintf( buffer, "삭제 요구할 방사체[%d]/빔[%d] 번호를 정상 처리했습니다 !", pLanData->stDelete.uiAET, pLanData->stDelete.uiABT );
    m_CStaticError.SetWindowTextA( buffer );

    DeleteThreatData( pLanData->stDelete.uiAET, pLanData->stDelete.uiABT );

    GetDlgItem( IDC_BUTTON_REQ_DELETE )->EnableWindow( TRUE );

    UpdateWindow();

}

/**
 * @brief     ResultSysError
 * @param     UNI_LAN_DATA * pLanData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-07 10:10:00
 * @warning
 */
void CZCCUSimDlg::ResultOfSysError( UNI_LAN_DATA *pLanData )
{
    m_CStaticError.SetWindowTextA( pLanData->szString );

    GetDlgItem( IDC_BUTTON_REQ_DOWNLOAD )->EnableWindow( TRUE );

    UpdateWindow();
}

/**
 * @brief     ClearErrorMessage
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-07 10:39:59
 * @warning
 */
void CZCCUSimDlg::ClearErrorMessage()
{
    m_CStaticError.SetWindowTextA( "" );

}

/**
 * @brief     UpdateStaticMessage
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 15:41:32
 * @warning
 */
void CZCCUSimDlg::UpdateStaticMessage( STR_CLIENT_SOCKET* pClientSocket, bool bInsert )
{
	int iIndex = 0;
	char buffer[100];

 	if( pClientSocket == NULL || true ) {
 		for( STR_CLIENT_SOCKET stClientSocket : m_vClientSock ) {
 			//sprintf( buffer, "연결: %s[%5d]", stClientSocket.iSocket, inet_ntoa( stClientSocket.socketAddress.sin_addr ), ntohs( stClientSocket.socketAddress.sin_port ) );
#ifdef _WIN64
             sprintf( buffer, "연결: %s[%5lld]", inet_ntoa( stClientSocket.socketAddress.sin_addr ), stClientSocket.iSocket );
#else
            sprintf( buffer, "연결: %s[%5d]", inet_ntoa( stClientSocket.socketAddress.sin_addr ), stClientSocket.iSocket );
#endif
 			m_CStaticConnectMessage[iIndex].SetWindowText( buffer );
 			++iIndex;
 		}

		for( ; iIndex < MAX_CLIENTS; ++iIndex ) {
			m_CStaticConnectMessage[iIndex].SetWindowText( "미연결" );
		}
	}
 	else {
		if( bInsert == true ) {
			iIndex = m_QBoard.top();
			m_QBoard.pop();

#ifdef _WIN64
            sprintf( buffer, "연결: %s [%5lld]", inet_ntoa( pClientSocket->socketAddress.sin_addr ), pClientSocket->iSocket );
#else
			sprintf( buffer, "연결: %s [%5d]", inet_ntoa( pClientSocket->socketAddress.sin_addr ), pClientSocket->iSocket );
#endif
 			m_CStaticConnectMessage[iIndex].SetWindowText( buffer );
 		}
		else {
			CString strBuffer;
			int iSocket;

			for( iIndex = 0; iIndex < MAX_CLIENTS ; ++iIndex ) {
				m_CStaticConnectMessage[iIndex].GetWindowText( strBuffer );

				sscanf( (LPSTR)(LPCTSTR) strBuffer, "연결: %s [%d]", buffer, & iSocket );

				if( pClientSocket->iSocket == iSocket ) {
					m_QBoard.push( iIndex );

					m_CStaticConnectMessage[iIndex].SetWindowText( "미연결" );
					break;
				}
			}
		}
 	}

    UpdateWindow();

}

/**
 * @brief     UpdateLEDSwitch
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 15:41:31
 * @warning
 */
void CZCCUSimDlg::UpdateLEDSwitch()
{
	size_t iSize = m_vClientSock.size();

	m_CStaticLED.SetBitmap( HBITMAP( m_bmpLampConnect[iSize] ) );

}

/**
 * @brief     시작 요청을 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 17:11:19
 * @warning
 */
void CZCCUSimDlg::OnBnClickedButtonReqStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_stResultMessage.uiCoStart = 0;
    ++ m_stCountOfButton.uiCoStartButton;

	GetDlgItem( IDC_BUTTON_REQ_START )->EnableWindow( FALSE );

	if( m_enMode == enREADY_MODE ) {
		// 운용 시작 명령을 발사합니다.
		m_strLanHeader.usOpCode = enREQ_OP_START;
		m_strLanHeader.uiLength = 0;

	}
	else {
        // 운용 시작 명령을 발사합니다.
        m_strLanHeader.usOpCode = enREQ_OP_SHUTDOWN;
        m_strLanHeader.uiLength = 0;

        GetDlgItem( IDC_BUTTON_REQ_RESTART )->EnableWindow( FALSE );

	}

	Send();

    DisplayButtonCount();

}

/**
 * @brief     OnBnClickedButtonReqRestart
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-08 14:48:32
 * @warning
 */
void CZCCUSimDlg::OnBnClickedButtonReqRestart()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    ++ m_stCountOfButton.uiCoRestartButton;

    GetDlgItem( IDC_BUTTON_REQ_RESTART )->EnableWindow( FALSE );

    m_strLanHeader.usOpCode = enREQ_OP_RESTART;
    m_strLanHeader.uiLength = 0;

 	Send();

    DisplayButtonCount();

}

/**
 * @brief     UpdateReqStartButton
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 17:55:50
 * @warning
 */
void CZCCUSimDlg::UpdateReqStartButton()
{
	switch( m_enMode ) {
	case enREADY_MODE :
		m_CButtonReqStart.SetWindowText( "시작 요청" );
		break;

    case enOP_Mode:
		m_CButtonReqStart.SetWindowText( "종료 요청" );
        break;

	default:
		break;

	}

    // ClearErrorMessage();

}

/**
 * @brief     Send
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-03 17:24:48
 * @warning
 */
void CZCCUSimDlg::Send( void *pLanData, BOOL bSwap )
{
	unsigned int uiLength = m_strLanHeader.uiLength;

	CCommonUtils::swapByteOrder( m_strLanHeader.usOpCode );
	CCommonUtils::swapByteOrder( m_strLanHeader.uiLength );
    m_pTheMULSRV->Send( & m_strLanHeader, sizeof( STR_LAN_HEADER ) );

	if( uiLength ) {
		unsigned int i;

        if( bSwap == TRUE ) {
		    for( i = 0; i < uiLength / sizeof( int ); ++i ) {
			    CCommonUtils::swapByteOrder( m_uniLanData.uiINT32[i] );
		    }
        }

        if( pLanData == NULL ) {
            m_pTheMULSRV->Send( &m_uniLanData, uiLength );
        }
        else {
            m_pTheMULSRV->Send( pLanData, uiLength );
        }
	}

    ClearErrorMessage();

}

/**
 * @brief     OnBnClickedButtonReqDisconnect
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-05 16:13:05
 * @warning
 */
void CZCCUSimDlg::OnBnClickedButtonReqDisconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem( IDC_BUTTON_REQ_DISCONNECT )->EnableWindow( FALSE );
    //int iIndex;
    int iCoClient = (int) m_vClientSock.size();
    TRACE( "\n[%d]개의 클라이언트 접속을 강제 해지 합니다.", m_vClientSock.size() );

	for( STR_CLIENT_SOCKET stClientSocket : m_vClientSock ) {
        //TRACE( "\n강제 단락: 소켓 ID(%d), IP 어드레스(%s), 포트 : %5d\n", stClientSocket.iSocket, inet_ntoa( stClientSocket.socketAddress.sin_addr ), ntohs( stClientSocket.socketAddress.sin_port ) );

		shutdown( stClientSocket.iSocket, SD_BOTH );
		//closesocket( stClientSocket.iSocket );
	}

    //Sleep( 3 );

	//DisConnectMessage( NULL );

	GetDlgItem( IDC_BUTTON_REQ_DISCONNECT )->EnableWindow( TRUE );


    ClearErrorMessage();
    DisplayButtonCount();

}

/**
 * @brief     OnBnClickedButtonReqDownload
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-07 09:46:31
 * @warning
 */
void CZCCUSimDlg::OnBnClickedButtonReqDownload()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_stResultMessage.uiCoDownload = 0;

    ++ m_stCountOfButton.uiCoDownloadButton;

    GetDlgItem( IDC_BUTTON_REQ_DOWNLOAD )->EnableWindow( FALSE );

    m_strLanHeader.usOpCode = enREQ_RELOAD_LIBRARY;
    m_strLanHeader.uiLength = 0;

    Send();

    DisplayButtonCount();

}

/**
 * @brief     OnBnClickedButtonReqOpvarSetting
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-07 20:14:27
 * @warning
 */
void CZCCUSimDlg::OnBnClickedButtonReqOpvarSetting()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    ++ m_stCountOfButton.uiCoRequestButton;

    unsigned int uiLength = 0;

    // INI 파일 읽기
    CRawFile theRawFile;

    char pstPathname[100];

    sprintf( pstPathname, "../../files/sysconfig.ini" );
    if( theRawFile.RawOpenFile( pstPathname, O_BINARY | O_RDWR ) ) {
        unsigned long long int ullFileSize;

        ullFileSize = theRawFile.GetRawFileSize();

        uiLength = (unsigned int) min( ullFileSize, _MAX_LANDATA );

        theRawFile.Read( m_uniLanData.szString, uiLength );

        theRawFile.CloseFile();

        if( uiLength > 0 ) {
            m_stResultMessage.uiCoReqOpVarSetting = 0;

            GetDlgItem( IDC_BUTTON_REQ_OPVAR_SETTING )->EnableWindow( FALSE );

            m_strLanHeader.usOpCode = enREQ_SET_SYS;
            m_strLanHeader.uiLength = uiLength;

            Send( m_uniLanData.szString, FALSE );

        }
    }

    //ClearErrorMessage();

    DisplayButtonCount();

}

/**
 * @brief     OnBnClickedButtonReqOpvar
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-05 16:13:07
 * @warning
 */
void CZCCUSimDlg::OnBnClickedButtonReqOpvar()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_stResultMessage.uiCoRequestOpVar = 0;

    ++ m_stCountOfButton.uiCoRequestConfigButton;

    GetDlgItem( IDC_BUTTON_REQ_OPVAR )->EnableWindow( FALSE );

    m_strLanHeader.usOpCode = enREQ_SYS;
    m_strLanHeader.uiLength = 0;

    Send();

    DisplayButtonCount();

}

/**
 * @brief     InitMode
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-25 11:57:49
 * @warning
 */
void CZCCUSimDlg::InitViewVariable()
{

    m_vecAETID.clear();
    m_vecABTID.clear();
    m_vecLOBID.clear();

    m_uiCoAETListItems = 0;
    m_uiCoABTListItems = 0;
    m_uiCoLOBListItems = 0;

    m_CListCtrlAET.DeleteAllItems();
    m_CListCtrlABT.DeleteAllItems();
    m_CListCtrlLOB.DeleteAllItems();


}

/**
 * @brief     OnBnClickedButtonReqDelete
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-25 16:44:16
 * @warning
 */
void CZCCUSimDlg::OnBnClickedButtonReqDelete()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    ++ m_stCountOfButton.uiCoRequestDeleteButton;

    m_strLanHeader.usOpCode = enREQ_DELETE_THREAT_DATA;
    m_strLanHeader.uiLength = sizeof( SELDELETE );

    CString strAETID, strABTID;

    GetDlgItem( IDC_EDIT_AETID )->GetWindowText( strAETID );
    GetDlgItem( IDC_EDIT_ABTID )->GetWindowText( strABTID );

    unsigned int uiAETID = ( unsigned int ) atoi( CStringA( strAETID ) );
    unsigned int uiABTID = ( unsigned int ) atoi( CStringA( strABTID ) );

    if( uiAETID != 0 && uiABTID != 0 ) {
        m_uniLanData.stDelete.uiAET = uiAETID;
        m_uniLanData.stDelete.uiABT = uiABTID;

        Send();
    }
    else {
        AfxMessageBox( "삭제 요구할 방사체/빔 번호가 잘못 됐습니다 !" );
    }

    DisplayButtonCount();

}


/**
 * @brief     OnBnClickedButtonReqScan
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-20 17:44:56
 * @warning
 */
void CZCCUSimDlg::OnBnClickedButtonReqScan()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    ++ m_stCountOfButton.uiCoRequestUserScanButton;

    m_strLanHeader.usOpCode = enREQ_ANAL_SCAN;
    m_strLanHeader.uiLength = sizeof( SELREQSCAN );

    CString strAETID, strABTID;

    GetDlgItem( IDC_EDIT_AETID )->GetWindowText( strAETID );
    GetDlgItem( IDC_EDIT_ABTID )->GetWindowText( strABTID );

    unsigned int uiAETID = ( unsigned int ) atoi( CStringA( strAETID ) );
    unsigned int uiABTID = ( unsigned int ) atoi( CStringA( strABTID ) );

    if( uiAETID != 0 && uiABTID != 0 ) {
        GetDlgItem( IDC_BUTTON_REQ_SCAN )->EnableWindow( FALSE );

        m_uniLanData.stReqScan.uiAET = uiAETID;
        m_uniLanData.stReqScan.uiABT = uiABTID;

        Send();
    }
    else {
        char szBuffer[100];
        sprintf( szBuffer, "스캔 분석 요구할 방사체/빔[%d/%d] 번호가 0 으로 잘못 됐습니다 !", uiAETID, uiABTID );
        AfxMessageBox( szBuffer );
    }

    DisplayButtonCount();

}

/**
 * @brief     OnNMClickListAet
 * @param     NMHDR * pNMHDR
 * @param     LRESULT * pResult
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-22 11:15:14
 * @warning
 */
void CZCCUSimDlg::OnNMClickListAet( NMHDR *pNMHDR, LRESULT *pResult )
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>( pNMHDR );
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    NM_LISTVIEW *pNMListView = ( NM_LISTVIEW * ) pNMHDR;
    char szBuffer[100];

    int iIdx = pNMListView->iItem;
    CString strAETID = m_CListCtrlAET.GetItemText( iIdx, 0 );

    unsigned int uiAETID = ( unsigned int ) atoi( CStringA( strAETID ) );
    sprintf( szBuffer, "%d", uiAETID );

    if( uiAETID != 0 ) {
        GetDlgItem( IDC_EDIT_AETID )->SetWindowText( szBuffer );
    }

    *pResult = 0;
}


/**
 * @brief     OnNMClickListAbt
 * @param     NMHDR * pNMHDR
 * @param     LRESULT * pResult
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-22 11:24:14
 * @warning
 */
void CZCCUSimDlg::OnNMClickListAbt( NMHDR *pNMHDR, LRESULT *pResult )
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>( pNMHDR );
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    NM_LISTVIEW *pNMListView = ( NM_LISTVIEW * ) pNMHDR;
    char szBuffer[100];

    int iIdx = pNMListView->iItem;
    CString strAETIDABTID = m_CListCtrlABT.GetItemText( iIdx, 0 );

    unsigned int uiAETID, uiABTID;

    if( strAETIDABTID.IsEmpty() != true ) {
        sscanf( CStringA( strAETIDABTID ), "%d/%d", & uiAETID, & uiABTID );

        sprintf( szBuffer, "%d", uiAETID );
        GetDlgItem( IDC_EDIT_AETID )->SetWindowText( szBuffer );

        sprintf( szBuffer, "%d", uiABTID );
        GetDlgItem( IDC_EDIT_ABTID )->SetWindowText( szBuffer );
    }

    *pResult = 0;
}

/**
 * @brief     AddClientSocket
 * @param     STR_CLIENT_SOCKET * pClientSocket
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-22 17:02:42
 * @warning
 */
void CZCCUSimDlg::AddClientSocket( STR_CLIENT_SOCKET *pClientSocket )
{

    m_vClientSock.push_back( *pClientSocket );

}

/**
 * @brief     RemoveClientSocket
 * @param     STR_CLIENT_SOCKET * pClientSocket
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-22 17:02:51
 * @warning
 */
void CZCCUSimDlg::RemoveClientSocket( STR_CLIENT_SOCKET *pClientSocket )
{
    bool bRet=false;
    unsigned int idxClientSock=0;

    for( const STR_CLIENT_SOCKET stClientSocket : m_vClientSock ) {
        if( stClientSocket.socketAddress.sin_port == pClientSocket->socketAddress.sin_port ) {
            m_vClientSock.erase( m_vClientSock.begin() + idxClientSock );
            bRet = true;
            TRACE( "\n 삭제-소켓[%d], 포트[%d]", pClientSocket->iSocket, pClientSocket->socketAddress.sin_port );
            break;
        }
        ++ idxClientSock;

    }

    if( bRet == false ) {
        TRACE( "구조가 잘못됨 !" );
    }

}

/**
 * @brief     DisplayButtonCount
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-31 10:55:24
 * @warning
 */
void CZCCUSimDlg::DisplayButtonCount()
{
    string strWindowText;

    strWindowText = string_format( "시작: %d, 재시작: %d, 설정 요청: %d, 요청: %d, 스캔: %d, 삭제: %d ", m_stCountOfButton.uiCoStartButton, m_stCountOfButton.uiCoRestartButton, m_stCountOfButton.uiCoRequestConfigButton, m_stCountOfButton.uiCoRequestButton, m_stCountOfButton.uiCoRequestUserScanButton, m_stCountOfButton.uiCoRequestDeleteButton );

    //CMainFrame *pFrame;
    //pFrame = ( CMainFrame * ) AfxGetMainWnd();

    SetWindowText( strWindowText.c_str() );

}

void CZCCUSimDlg::OnIDClose()
{
    // TODO: 여기에 명령 처리기 코드를 추가합니다.
}
