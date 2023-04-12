
// ZCCUSimDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ZCCUSim.h"
#include "ZCCUSimDlg.h"
#include "afxdialogex.h"

#define _MAIN_GLOBALS_

ENUM_UnitType g_enUnitType;

#include "../../files/Include/globals.h"

#include "../../files/Utils/ccommonutils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	: CDialogEx(IDD_ZCCUSIM_DIALOG, pParent), CMultiServer( 0, "CCUSIM", CCU_PORT )
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

	m_bmpLampBigOn.LoadBitmap( IDB_BIGON );
	m_bmpLampBigOff.LoadBitmap( IDB_BIGOFF );
	m_bmpLampConnect[0].LoadBitmap( IDB_BIGOFF );
	m_bmpLampConnect[1].LoadBitmap( IDB_1_CONNECT );
	m_bmpLampConnect[2].LoadBitmap( IDB_2_CONNECT );
	m_bmpLampConnect[3].LoadBitmap( IDB_3_CONNECT );
	m_bmpLampConnect[4].LoadBitmap( IDB_4_CONNECT );
	m_bmpLampConnect[5].LoadBitmap( IDB_BIGON );

	Init();
	InitView();
	//CreateThread();

	// 쓰레드 실행합니다.
	//m_pThread = AfxBeginThread( CMultiServer::WinRun, m_pTheMultiServer );
	//m_pTheMultiServer->Run();

	Run();


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

	//m_pTheMultiServer = new CMultiServer( g_iKeyId++, ( char* ) "CCUTCP", CCU_PORT );
}

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
	UpdateStaticMessage( NULL, true );

	AllButtonEnable( FALSE );
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

	UpdateStaticMessage( pClientSocket, true );
	UpdateLEDSwitch();

	AllButtonEnable( TRUE );

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

	m_vClientSock.clear();

    UpdateStaticMessage( pClientSocket, false );
    UpdateLEDSwitch( );

	UpdateReqStartButton();

	//
	AllButtonEnable( FALSE );
	

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
	GetDlgItem( IDC_BUTTON_REQ_RESTART )->EnableWindow( bEnable );
	GetDlgItem( IDC_BUTTON_REQ_DOWNLOAD )->EnableWindow( bEnable );
	GetDlgItem( IDC_BUTTON_REQ_DOWNLOAD )->EnableWindow( bEnable );
	GetDlgItem( IDC_BUTTON_REQ_OPVAR_SETTING )->EnableWindow( bEnable );
	GetDlgItem( IDC_BUTTON_REQ_OPVAR )->EnableWindow( bEnable );
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

	switch( pLanMessage->stLanHeader.uiOpCode ) {
		case enRES_OP_START:
			ResultOPStart( & pLanMessage->stLanData );
			break;

		case enRES_OP_SHUTDOWN:
			ResultOPShutdown( &pLanMessage->stLanData );
			break;

		case enRES_OP_RESTART :
			ResultOPRestart( &pLanMessage->stLanData );
			break;

		case enNUP_THREAT_DATA:
			ReceiveThreatData( &pLanMessage->stLanData );
			break;

		default :
			TRACE( "\n[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), pLanMessage->stLanHeader.uiOpCode );
			break;
	}

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
void CZCCUSimDlg::ReceiveThreatData( UNI_LAN_DATA *pLanData )
{

	CCommonUtils::AllSwapData32( & pLanData->stAET.stLOBData.uiPDWID, sizeof( UINT )*6 );


	TRACE( "\n 방사체 번호[%d]", pLanData->stAET.stAETData.uiAETID );

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
void CZCCUSimDlg::ResultOPStart( UNI_LAN_DATA *pLanData )
{
	CCommonUtils::AllSwapData32( pLanData, sizeof( UINT ) );
	if( pLanData->uiUnit == TRUE ) {
		m_enMode = enOP_Mode;

		GetDlgItem( IDC_BUTTON_REQ_START )->EnableWindow( TRUE );
	}
	else {

	}

	UpdateReqStartButton();

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
void CZCCUSimDlg::ResultOPShutdown( UNI_LAN_DATA *pLanData )
{
	CCommonUtils::AllSwapData32( pLanData, sizeof( UINT ) );
    if( pLanData->uiUnit == TRUE ) {
        m_enMode = enREADY_MODE;

		GetDlgItem( IDC_BUTTON_REQ_START )->EnableWindow( TRUE );

    }
    else {

    }

    UpdateReqStartButton();

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
void CZCCUSimDlg::ResultOPRestart( UNI_LAN_DATA *pLanData )
{
	CCommonUtils::AllSwapData32( pLanData, sizeof( UINT ) );
    if( pLanData->uiUnit == TRUE ) {
        m_enMode = enOP_Mode;

    }
    else {

    }

    // UpdateReqStartButton();

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

	if( pClientSocket == NULL ) {		
		for( STR_CLIENT_SOCKET stClientSocket : m_vClientSock ) {
			//sprintf( buffer, "연결: %s[%5d]", stClientSocket.iSocket, inet_ntoa( stClientSocket.socketAddress.sin_addr ), ntohs( stClientSocket.socketAddress.sin_port ) );
			sprintf( buffer, "연결: %s[%5d]", inet_ntoa( stClientSocket.socketAddress.sin_addr ), stClientSocket.iSocket );
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

			sprintf( buffer, "연결: %s [%5d]", inet_ntoa( pClientSocket->socketAddress.sin_addr ), pClientSocket->iSocket );
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
	int iSize = m_vClientSock.size();

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
	GetDlgItem( IDC_BUTTON_REQ_START )->EnableWindow( FALSE );
	
	if( m_enMode == enREADY_MODE ) {
		// 운용 시작 명령을 발사합니다.
		m_strLanHeader.uiOpCode = enREQ_OP_START;
		m_strLanHeader.uiLength = 0;

	}
	else {
        // 운용 시작 명령을 발사합니다.
        m_strLanHeader.uiOpCode = enREQ_OP_SHUTDOWN;
        m_strLanHeader.uiLength = 0;

	}

	Send();

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

    m_strLanHeader.uiOpCode = enREQ_OP_RESTART;
    m_strLanHeader.uiLength = 0;

	Send();
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
void CZCCUSimDlg::Send()
{
	unsigned int uiLength = m_strLanHeader.uiLength;

	CCommonUtils::swapByteOrder( m_strLanHeader.uiOpCode );
	CCommonUtils::swapByteOrder( m_strLanHeader.uiLength );
	CMultiServer::Send( & m_strLanHeader, sizeof( STR_LAN_HEADER ) );

	if( uiLength ) {
		unsigned int i;

		for( i = 0; i < uiLength / sizeof( int ); ++i ) {
			CCommonUtils::swapByteOrder( m_uniLanData.uiINT32[i] );
		}
		
		CMultiServer::Send( &m_uniLanData, uiLength );
	}

}




void CZCCUSimDlg::OnBnClickedButtonReqOpvar()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CZCCUSimDlg::OnBnClickedButtonReqDisconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//GetDlgItem( IDC_BUTTON_REQ_DISCONNECT )->EnableWindow( FALSE );

	for( STR_CLIENT_SOCKET stClientSocket : m_vClientSock ) {
		shutdown( stClientSocket.iSocket, SD_BOTH );
		closesocket( stClientSocket.iSocket );
	}

    //Sleep( 3 );

	DisConnectMessage( NULL );

	//GetDlgItem( IDC_BUTTON_REQ_DISCONNECT )->EnableWindow( TRUE );

}


void CZCCUSimDlg::OnBnClickedButtonReqDownload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    m_strLanHeader.uiOpCode = enREQ_RELOAD_LIBRARY;
    m_strLanHeader.uiLength = 0;

    Send();
}
